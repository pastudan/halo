/* kb object: <common> -> kb_common_stubs.c */

/* --- <common> batch drafts (2026-07-26) --- */

/* 0x67710 */
void FUN_00067710(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x67760 */
void FUN_00067760(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  __lseek();
  /* cmp eax, ecx -> jne 0x677c0 */
  __write();
  /* cmp eax, esi -> jne 0x677c0 */
  /* mem[0x003340b0] = eax */
  TIFFDefaultDirectory();
  FUN_00068a30(0, (char *)0x0025fe08);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x677f0 */
void FUN_000677f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  __lseek();
  __lseek();
  __write();
  /* cmp eax, 8 -> je 0x6785f */
  FUN_00068a30(0, (char *)0x0025fe8c);
  __lseek();
  /* cmp eax, ecx -> jne 0x6793f */
  __read();
  /* cmp eax, 2 -> jne 0x6793f */
  /* relift: test byte ptr [esi + 0xa], (char)ebx -> je 0x678b8 */
  FUN_0006f1b0();
  __lseek();
  __read();
  /* cmp eax, 4 -> jne 0x6792d */
  /* relift: test byte ptr [esi + 0xa], (char)ebx -> je 0x678f8 */
  FUN_0006f1d0();
  /* test ecx, ecx -> jne 0x67870 */
  __lseek();
  __write();
  /* cmp eax, 4 -> je 0x67934 */
  FUN_00068a30(0x002ca124, (char *)0x0025fe2c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x67960 */
void FUN_00067960(void)
{
  TIFFDefaultDirectory();
  FUN_0006f9d0();
  FUN_001d9068();
  FUN_00067760();
}

/* 0x679f0 */
void FUN_000679f0(void)
{
  int eax = 0;
  int esi = 0;

  FUN_00067760();
  /* test eax, eax -> je 0x67a59 */
  /* cmp esi, eax -> jl 0x67a22 */

  (void)eax;
  (void)esi;
}

/* 0x67a70 */
void FUN_00067a70(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  csstrlen((char *)(uintptr_t)esi);
  FUN_00067760();
  /* test eax, eax -> jne 0x67aab */
  csmemcpy((void *)(uintptr_t)edi, (void *)0, 0);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x67ac0 */
void FUN_00067ac0(void)
{
  FUN_00067760();
}

/* 0x67b40 */
void FUN_00067b40(void)
{
  FUN_00067760();
}

/* 0x67b80 */
void FUN_00067b80(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  debug_malloc(eax, 0, (char *)0x0025fefc, 634);
  FUN_001d9068();
  /* cmp ebx, edi -> jl 0x67bc0 */
  FUN_00067760();
  debug_free((void *)(uintptr_t)esi, (char *)0x0025fefc, 641);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x67c10 */
void FUN_00067c10(void)
{
  FUN_00067760();
}

/* 0x67c50 */
void FUN_00067c50(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp (int16_t)ecx, 1 -> jbe 0x67cf1 */
  _TIFFgetfield();
  _TIFFgetfield();
  FUN_00067ac0();
  /* test eax, eax -> jne 0x67d31 */
  _TIFFgetfield();
  /* relift: cmp word ptr [esi + 0xc4], 0x4d4d -> jne 0x67d3d */
  /* cmp (int16_t)ecx, 1 -> jbe 0x67dbf */
  _TIFFgetfield();
  _TIFFgetfield();
  FUN_00067b40();
  /* test eax, eax -> jne 0x67d31 */
  _TIFFgetfield();
  /* cmp (int16_t)ecx, 1 -> jbe 0x67e3c */
  _TIFFgetfield();
  _TIFFgetfield();
  FUN_00067b80();
  /* test eax, eax -> jne 0x67d31 */
  _TIFFgetfield();
  FUN_00067960();
  /* test eax, eax -> jne 0x67d31 */
  /* cmp (int16_t)ecx, 1 -> jbe 0x67ef2 */
  _TIFFgetfield();
  _TIFFgetfield();
  FUN_00067760();
  /* test eax, eax -> jne 0x67d31 */
  _TIFFgetfield();
  _TIFFgetfield();
  FUN_00067a70();
  /* test eax, eax -> jne 0x67d31 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x67f70 */
void FUN_00067f70(void)
{
  int ebx = 0;

  _TIFFgetfield();
  /* test ebx, ebx -> jle 0x67fb7 */
  FUN_00067760();

  (void)ebx;
}

/* 0x68030 */
void FUN_00068030(void)
{
  int ebx = 0;

  _TIFFgetfield();
  /* relift: cmp word ptr [ebx + 0xc4], 0x4d4d -> jne 0x68080 */

  (void)ebx;
}

/* 0x680a0 */
void FUN_000680a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp word ptr [ebx + 6], (int16_t)edi -> jne 0x680be */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x68106 */
  /* cmp eax, edi -> je 0x68106 */
  /* test eax, eax -> jne 0x68106 */
  FUN_00068a30(0, (char *)0x0025ffc4);
  /* cmp eax, edi -> je 0x68116 */
  /* cmp eax, edi -> je 0x68126 */
  /* relift: cmp dword ptr [ebx + 0x138], edi -> jle 0x68153 */
  TIFFFlushData1();
  /* test eax, eax -> jne 0x68153 */
  FUN_00068a30(0, (char *)0x0025ff98);
  /* relift: test byte ptr [ebx + 0xa], 0x40 -> je 0x68182 */
  /* cmp eax, edi -> je 0x68182 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025fefc, 154);
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x681ba */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x681df */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x68201 */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x68226 */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x6824b */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x68270 */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x68295 */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x682ba */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x682df */
  /* relift: test dword ptr [ebx + ecx*4 + 0x14], edx -> je 0x68304 */
  /* cmp ecx, 0x3b -> jbe 0x68195 */
  debug_malloc(edi, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x0025ff70);
  /* test eax, eax -> jne 0x6836b */
  FUN_000677f0();
  /* test eax, eax -> je 0x6834d */
  /* mem[0x003340b0] = eax */
  /* mem[0x003340b0] = eax */
  __lseek();
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)esi, 0);
  /* test (char)eax, 4 -> je 0x683d2 */
  /* relift: cmp word ptr [esi + 0x60], 0 -> jne 0x683d2 */
  /* relift: cmp word ptr [0x2c9a98], 0 -> je 0x68636 */
  /* cmp (int16_t)ecx, 0xffff -> je 0x68625 */
  /* relift: test dword ptr [ebp + ecx*4 - 0x28], edx -> je 0x68625 */
  /* cmp ecx, 0x2b -> ja 0x685df */
  /* cmp ecx, edx -> jne 0x68625 */
  /* cmp ecx, edx -> jne 0x68625 */
  FUN_00067b40();
  FUN_000679f0();
  FUN_00067710();
  FUN_00067710();
  FUN_00067710();
  FUN_00067710();
  FUN_00067960();
  /* test eax, eax -> je 0x686b6 */
  FUN_00067960();
  /* test eax, eax -> je 0x686b6 */
  FUN_00067960();
  /* test eax, eax -> je 0x686b6 */
  FUN_00067f70();
  /* test eax, eax -> je 0x686b6 */
  FUN_00068030();
  FUN_00067c50();
  /* test eax, eax -> je 0x686b6 */
  __lseek();
  __write();
  /* cmp eax, 2 -> je 0x6866e */
  __write();
  /* cmp eax, esi -> je 0x6868e */
  __write();
  /* cmp eax, 4 -> je 0x686d5 */
  FUN_00068a30(0, (char *)0x0025fe6c);
  debug_free((void *)(uintptr_t)edx, (char *)0x0025fefc, 353);
  TIFFFreeDirectory(0);
  debug_free((void *)(uintptr_t)edi, (char *)0x0025fefc, 339);
  FUN_00066190();
  /* cmp eax, ecx -> jle 0x687b1 */
  TIFFFlushData1();
  /* test eax, eax -> jne 0x687b1 */
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, edi);
  /* test (char)eax, 0x10 -> je 0x68828 */
  /* cmp eax, 0x10 -> je 0x68811 */
  /* cmp eax, 0x20 -> jne 0x68828 */
  FUN_0006f220();
  FUN_0006f1f0();
  TIFFFlushData1();
  /* test eax, eax -> je 0x68879 */
  /* test ebx, ebx -> jg 0x687c0 */
  /* cmp eax, edi -> jge 0x688c2 */
  FUN_00068a30(0, (char *)0x0025fff0);
  /* cmp eax, ebx -> je 0x688db */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, edi);
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x68914 */
  /* cmp eax, 0x10 -> je 0x68903 */
  /* cmp eax, 0x20 -> jne 0x68914 */
  FUN_0006f220();
  FUN_0006f1f0();
  /* test eax, eax -> je 0x689dd */
  crt_fprintf((void *)0x00331070, (char *)0x00259f68);
  FUN_001d9850();
  crt_fprintf((void *)0x00331070, (char *)0x00260020);
  /* mem[0x002ca1f4] = ecx */
  /* test eax, eax -> je 0x68a4d */
  /* cmp ecx, 7 -> ja 0x68a9f */
  /* test ecx, ecx -> jle 0x68ba8 */
  /* test eax, eax -> jg 0x68b65 */
  /* test dl, 0x40 -> je 0x68aea */
  /* test eax, eax -> jg 0x68b6c */
  /* test dl, 0x20 -> je 0x68af9 */
  /* test eax, eax -> jg 0x68b73 */
  /* test dl, 0x10 -> je 0x68b08 */
  /* test eax, eax -> jg 0x68b7a */
  /* test dl, 8 -> je 0x68b17 */
  /* test eax, eax -> jg 0x68b81 */
  /* test dl, 4 -> je 0x68b26 */
  /* test eax, eax -> jg 0x68b88 */
  /* test dl, 2 -> je 0x68b35 */
  /* test eax, eax -> jg 0x68b8f */
  /* test dl, 1 -> je 0x68b44 */
  /* test eax, eax -> jle 0x68a9f */
  /* cmp esi, 0xc -> jl 0x68b5c */
  /* cmp eax, 1 -> je 0x68b96 */
  /* test ecx, ecx -> jle 0x68c6a */
  FUN_00068a30(0, (char *)0x00260084);
  FUN_0006f890();
  TIFFScanlineSize();
  /* test (char)eax, 1 -> jne 0x68cca */
  /* relift: cmp word ptr [esi + 0x3a], 4 -> jne 0x68cd1 */
  debug_malloc(ebx, 0, (char *)0x00260058, 252);
  FUN_00068a30(0x00260024, (char *)0x00260034);
  /* relift: test byte ptr [esi + 0x68], 1 -> jne 0x68d57 */
  /* relift: cmp word ptr [esi + 0x3a], 4 -> je 0x68d57 */
  /* cmp esi, ebx -> jne 0x68dae */
  FUN_00068c70();
  /* cmp esi, ebx -> jne 0x68dae */
  /* cmp ecx, ebx -> jle 0x68df3 */
  /* relift: test byte ptr [edi + 9], 2 -> jne 0x68e15 */
  FUN_00068a70();
  /* relift: test byte ptr [edi + 0x68], 1 -> je 0x68e15 */
  FUN_00068bd0();
  /* cmp edx, eax -> jge 0x68e57 */
  /* cmp edx, 8 -> jl 0x68e96 */
  /* relift: cmp word ptr [edx + 2], 0 -> je 0x68ee7 */
  /* test ecx, ecx -> jle 0x68f48 */
  /* cmp (int16_t)ecx, 1 -> je 0x68f50 */
  /* cmp (int16_t)ecx, 0xd2 -> je 0x68f56 */
  /* cmp (int16_t)ecx, 0x40 -> jge 0x68ec0 */
  /* relift: cmp word ptr [esi + 2], 0 -> je 0x68f99 */
  /* test ecx, ecx -> jle 0x68ffb */
  /* cmp (int16_t)ecx, 1 -> je 0x69003 */
  /* cmp (int16_t)ecx, 0xd2 -> je 0x69009 */
  /* cmp (int16_t)ecx, 0x40 -> jl 0x6900e */
  /* relift: cmp (int16_t)edx, word ptr [eax + 4] -> jne 0x69051 */
  FUN_00068eb0();
  FUN_00068f60();
  /* cmp esi, -4 -> je 0x6914b */
  /* cmp esi, -3 -> je 0x69122 */
  /* cmp esi, -1 -> je 0x690ae */
  /* cmp ecx, eax -> jle 0x6907d */
  /* test esi, esi -> jle 0x6909d */
  /* relift: cmp word ptr [ebp - 4], 0 -> je 0x69097 */
  FUN_00068e20();
  /* cmp ebx, eax -> jge 0x690ce */
  FUN_00068a30(0x002ec384, (char *)0x0026010c);
  /* relift: test byte ptr [edi + 9], 2 -> jne 0x690de */
  FUN_00068a70();
  /* relift: test byte ptr [edi + 9], 4 -> je 0x690ed */
  /* relift: test byte ptr [edi + 9], 8 -> je 0x69112 */
  /* test (char)ecx, 1 -> je 0x69112 */
  FUN_0006f9d0();
  FUN_00068a30(0x002ec384, (char *)0x002600bc);
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x69196 */
  /* cmp (int16_t)ecx, 7 -> jle 0x691c1 */
  /* test ecx, ecx -> jle 0x691eb */
  /* cmp ebx, eax -> jbe 0x6927c */
  /* relift: cmp ecx, dword ptr [edi + 0x130] -> jl 0x6923e */
  TIFFFlushData1();
  /* cmp ebx, eax -> ja 0x69215 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x692f2 */
  /* relift: cmp eax, dword ptr [edi + 0x130] -> jl 0x692bc */
  TIFFFlushData1();
  FUN_00069200();
  FUN_00069200();
  /* cmp esi, 0xa40 -> jge 0x69330 */
  /* cmp esi, 0x40 -> jl 0x69387 */
  FUN_00069200();
  FUN_00069200();
  /* cmp eax, 4 -> je 0x693e1 */
  FUN_00069200();
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6940f */
  FUN_00069200();
  /* test esi, esi -> jne 0x6946d */
  FUN_00068c70();
  /* test esi, esi -> jne 0x69448 */
  /* relift: cmp word ptr [esi + 4], 0 -> jne 0x6945f */
  /* test ecx, ecx -> jle 0x694b9 */
  /* relift: cmp word ptr [edi + 2], 8 -> je 0x69582 */
  /* relift: cmp eax, dword ptr [esi + 0x130] -> jl 0x6954c */
  TIFFFlushData1();
  /* relift: test byte ptr [esi + 9], 1 -> jne 0x695b9 */
  FUN_000693b0();
  FUN_00069520();
  /* test eax, eax -> je 0x695ee */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260058, 1077);
  /* test edx, edx -> jle 0x69645 */
  /* cmp eax, edi -> jle 0x69630 */
  /* cmp eax, edx -> jle 0x69636 */
  /* cmp ecx, 8 -> jl 0x6967f */
  /* cmp edx, 8 -> jl 0x69666 */
  /* cmp ecx, 8 -> jl 0x69679 */
  /* cmp edx, 8 -> jge 0x69650 */
  /* test edx, edx -> jle 0x69679 */
  /* cmp ecx, edx -> jle 0x69677 */
  FUN_00069600();
  /* test (int16_t)eax, (int16_t)eax -> je 0x69703 */
  /* cmp (int16_t)eax, 7 -> jle 0x69732 */
  /* test eax, eax -> jle 0x69a5c */
  FUN_00069600();
  FUN_00069600();
  FUN_00069600();
  /* test (int16_t)edi, (int16_t)edi -> je 0x69820 */
  /* test esi, esi -> jge 0x69812 */
  FUN_00068e20();
  /* relift: cmp (int16_t)edx, word ptr [ebx + 4] -> jne 0x69844 */
  FUN_00068eb0();
  FUN_00068f60();
  FUN_00068f60();
  FUN_00068eb0();
  /* cmp edx, eax -> jle 0x69867 */
  /* relift: cmp word ptr [ebp - 4], 0 -> je 0x6987d */
  FUN_00068e20();
  /* cmp ecx, eax -> jle 0x6988d */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x698a1 */
  FUN_00068e20();
  FUN_00069600();
  FUN_00069600();
  /* test esi, esi -> jge 0x6992b */
  FUN_00068e20();
  /* test esi, esi -> jge 0x69960 */
  FUN_00069180();
  /* cmp ecx, 0xc -> ja 0x69a40 */
  /* cmp eax, ebx -> jle 0x699b3 */
  FUN_00068bd0();
  /* test eax, eax -> je 0x69a38 */
  /* relift: cmp word ptr [ebp - 0x10], 8 -> jl 0x69960 */
  /* relift: cmp esi, dword ptr [ebp + 0x10] -> jge 0x69aea */
  /* relift: test byte ptr [edi + 9], 2 -> jne 0x69ace */
  FUN_0006f9d0();
  FUN_00068a70();
  FUN_00068a30(0x002ec394, (char *)0x00260178);
  /* relift: test byte ptr [edi + 9], 2 -> jne 0x69af7 */
  FUN_00068a70();
  FUN_00068a30(0x002ec394, (char *)0x00260148);
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jge 0x69c2a */
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jge 0x69c2a */
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jl 0x69bd0 */
  FUN_00069600();
  /* cmp ecx, eax -> je 0x69cb0 */
  FUN_00069600();
  /* test dl, 1 -> jne 0x69d07 */
  FUN_00069600();
  /* cmp esi, ebx -> jl 0x69e2e */
  /* cmp eax, -3 -> jl 0x69d63 */
  /* cmp eax, 3 -> jg 0x69d63 */
  FUN_00069200();
  /* test dl, 1 -> jne 0x69d8b */
  FUN_00069600();
  FUN_00069200();
  /* test eax, eax -> je 0x69e01 */
  /* cmp eax, ecx -> je 0x69e01 */
  FUN_00069310();
  FUN_00069310();
  FUN_00069310();
  FUN_00069200();
  /* relift: cmp eax, dword ptr [ebp + 0x14] -> jge 0x69f1c */
  FUN_00069600();
  FUN_00069600();
  FUN_00069600();
  /* cmp eax, 4 -> je 0x69f7e */
  FUN_00069200();
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6a02e */
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6a02e */
  FUN_00069b90();
  /* test eax, eax -> je 0x6a067 */
  FUN_00069c40();
  /* test eax, eax -> je 0x6a067 */
  /* relift: cmp word ptr [esi + 0x24], 0 -> jne 0x6a018 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  FUN_00069b90();
  /* test eax, eax -> je 0x6a067 */
  csmemset((void *)(uintptr_t)ebx, 0, eax);
  /* test eax, eax -> jle 0x6a171 */
  /* test eax, eax -> jne 0x6a0b8 */
  FUN_00069020();
  FUN_000696d0();
  /* test eax, eax -> je 0x6a17b */
  /* relift: test byte ptr [esi + 0x68], 1 -> je 0x6a159 */
  /* relift: cmp word ptr [eax + 2], 0 -> jne 0x6a110 */
  /* test ecx, ecx -> jle 0x6a110 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)ebx, edx);
  /* test (char)eax, 8 -> je 0x6a249 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x6a24e */
  /* test eax, eax -> je 0x6a24e */
  /* test eax, eax -> jne 0x6a24e */
  TIFFFlushData1();
  /* relift: cmp word ptr [esi + 6], 0 -> je 0x6a293 */
  FUN_0006a210();
  /* test eax, eax -> je 0x6a28e */
  /* relift: test byte ptr [esi + 0xa], 2 -> je 0x6a293 */
  /* relift: tail-call FUN_000680a0(); */
  /* test eax, eax -> jne 0x6a293 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* test eax, eax -> jg 0x6a2b0 */
  FUN_0006f9d0();
  FUN_00064ec0(0, 0, 0);
  /* cmp eax, 7 -> ja 0x6a35e */
  FUN_0006f9d0();
  FUN_0006f9d0();
  /* mem[0xa35e0006] = eax */
  /* mem[0x90900006] = eax */
  debug_malloc(eax, 0, (char *)0, 0);
  /* mem[0x003340c8] = eax */
  FUN_00068a30(0, (char *)0x00260244);
  /* cmp edi, 7 -> ja 0x6a591 */
  /* cmp edx, 0x100 -> jl 0x6a402 */
  debug_malloc(eax, 0, (char *)0, 0);
  /* mem[0x003340c4] = edx */
  FUN_00068a30(0, (char *)0x00260294);
  /* cmp edx, 7 -> ja 0x6a8ca */
  /* cmp eax, 0x100 -> jl 0x6a632 */
  /* test eax, eax -> jbe 0x6a98f */
  /* test esi, esi -> jbe 0x6a979 */
  /* test ebx, ebx -> je 0x6aa20 */
  /* cmp edi, 4 -> jb 0x6aabb */
  /* test edi, edi -> jbe 0x6aaf0 */
  /* cmp edi, 8 -> jb 0x6abbb */
  /* test edi, edi -> jbe 0x6ac1c */
  /* cmp edi, 6 -> ja 0x6ac1c */
  /* test eax, eax -> jbe 0x6acb4 */
  /* test edx, edx -> jbe 0x6aca8 */
  /* cmp edi, 8 -> jb 0x6ad6b */
  /* test edi, edi -> jbe 0x6adcc */
  /* cmp edi, 6 -> ja 0x6adcc */
  /* cmp edi, 4 -> jb 0x6ae8b */
  /* test edi, edi -> jbe 0x6aec0 */
  /* test ebx, ebx -> je 0x6af60 */
  /* test eax, eax -> jbe 0x6b08c */
  /* test edi, edi -> jbe 0x6aff8 */
  /* test eax, eax -> jbe 0x6b08c */
  /* test edi, edi -> jbe 0x6b07e */
  /* test esi, esi -> jbe 0x6b18b */
  /* test edi, edi -> jbe 0x6b116 */
  /* test ecx, ecx -> jbe 0x6b18b */
  /* test edx, edx -> jbe 0x6b17e */
  /* test ecx, ecx -> jbe 0x6b2c3 */
  /* test eax, eax -> jbe 0x6b2c3 */
  /* test ebx, ebx -> jbe 0x6b2b1 */
  /* test edi, edi -> je 0x6b376 */
  /* test edx, edx -> jbe 0x6b3df */
  /* test ebx, ebx -> jbe 0x6b357 */
  /* test edx, edx -> jbe 0x6b3df */
  /* test ebx, ebx -> jbe 0x6b3cd */
  /* test ebx, ebx -> jle 0x6b5ea */
  /* test (char)eax, 0x41 -> jne 0x6b545 */
  /* test (char)eax, 0x41 -> jne 0x6b57a */
  /* test (char)eax, 0x41 -> jne 0x6b5af */
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  /* cmp esi, ebx -> jl 0x6b4e1 */
  FUN_0006b440();
  /* test ebx, ebx -> jbe 0x6b6d0 */
  FUN_0006b440();
  /* test eax, eax -> jbe 0x6b76a */
  FUN_0006b440();
  /* test ebx, ebx -> jbe 0x6b76a */
  FUN_0006b440();
  /* cmp eax, 6 -> ja 0x6b825 */
  /* relift: cmp word ptr [0x3340fc], 8 -> jne 0x6b7ab */
  /* cmp eax, 7 -> ja 0x6b825 */
  /* cmp eax, 7 -> ja 0x6b825 */
  /* relift: cmp word ptr [0x3340fc], 8 -> jne 0x6b825 */
  /* test esi, esi -> jne 0x6b838 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* test esi, esi -> jne 0x6b8da */
  FUN_00068a30(0, (char *)0x002602d0);
  FUN_0006b780();
  FUN_0006f910();
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x002602e8);
  TIFFGetField();
  TIFFGetField();
  FUN_0006a310();
  /* cmp edx, ebx -> jbe 0x6b9ae */
  /* test edi, edi -> jbe 0x6ba2d */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6b9e3 */
  /* test eax, eax -> jne 0x6ba27 */
  /* cmp esi, edi -> jb 0x6b9b8 */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6ba39 */
  debug_free((void *)(uintptr_t)edx, (char *)0x00260264, 346);
  /* test eax, eax -> jne 0x6bac8 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* test eax, eax -> jne 0x6bac8 */
  FUN_0006f910();
  debug_malloc(ecx, 0, (char *)0x00260264, 376);
  FUN_00068a30(0, (char *)0x002602e8);
  TIFFGetField();
  TIFFGetField();
  FUN_0006a310();
  /* cmp edx, esi -> jbe 0x6bb8d */
  /* test edi, edi -> jbe 0x6bc69 */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6bbc7 */
  /* test eax, eax -> jne 0x6bc63 */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6bbed */
  /* test eax, eax -> jne 0x6bc63 */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6bc13 */
  /* test eax, eax -> jne 0x6bc63 */
  /* cmp esi, edi -> jb 0x6bb9b */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6bc75 */
  debug_free((void *)(uintptr_t)ecx, (char *)0x00260264, 412);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x6bcb0 */
void FUN_0006bcb0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  FUN_0006b780();
  FUN_0006f180();
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x00260304);
  FUN_0006a310();
  FUN_00064ec0(0, 0, 0);
  TIFFGetField();
  TIFFScanlineSize();
  /* cmp ebx, eax -> jae 0x6bd79 */
  /* test eax, eax -> jbe 0x6be1e */
  /* cmp edx, eax -> jbe 0x6bd9e */
  FUN_0006f0d0();
  FUN_0006ede0();
  /* test eax, eax -> jge 0x6bdd2 */
  /* test eax, eax -> jne 0x6be1b */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6be03 */
  debug_free((void *)(uintptr_t)esi, (char *)0x00260264, 459);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0x6be40 */
void FUN_0006be40(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_0006f180();
  debug_malloc(eax, edi, (char *)0x00260264, 487);
  /* relift: cmp dword ptr [ebp - 4], edi -> jne 0x6bee2 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* cmp eax, edi -> jne 0x6bee2 */
  FUN_00068a30(0, (char *)0x002602d0);
  FUN_0006a310();
  FUN_00064ec0(0, 0, 0);
  TIFFGetField();
  TIFFScanlineSize();
  /* cmp edi, eax -> jae 0x6bf48 */
  /* test esi, esi -> jbe 0x6c055 */
  /* cmp edx, esi -> jbe 0x6bf6e */
  FUN_0006f0d0();
  FUN_0006ede0();
  /* test eax, eax -> jge 0x6bfa8 */
  /* test eax, eax -> jne 0x6c055 */
  FUN_0006f0d0();
  FUN_0006ede0();
  /* test eax, eax -> jge 0x6bfd6 */
  /* test eax, eax -> jne 0x6c055 */
  FUN_0006f0d0();
  FUN_0006ede0();
  /* test eax, eax -> jge 0x6c004 */
  /* test eax, eax -> jne 0x6c055 */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6c03d */
  debug_free((void *)(uintptr_t)edx, (char *)0x00260264, 517);

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x6c080 */
void FUN_0006c080(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  TIFFFlushData();
  /* relift: cmp word ptr [ebp - 8], 0 -> jne 0x6c119 */
  /* relift: cmp word ptr [ebp - 4], 0xff -> je 0x6c32d */
  debug_malloc(eax, 0, (char *)0x00260264, 0);
  FUN_00068a30(0, (char *)0x00260340);
  /* relift: cmp word ptr [0x3340f4], (int16_t)ecx -> jne 0x6c18e */
  /* test esi, esi -> jl 0x6c1b9 */
  /* test esi, esi -> jl 0x6c1ab */
  /* relift: cmp word ptr [0x3340f4], 2 -> je 0x6c32a */
  /* relift: cmp word ptr [0x3340fc], 8 -> ja 0x6c32a */
  FUN_0006a3b0();
  /* test eax, eax -> je 0x6c227 */
  debug_free((void *)(uintptr_t)esi, (char *)0x00260264, 202);
  TIFFGetField();
  /* test eax, eax -> jne 0x6c230 */
  FUN_00068a30(0, (char *)0x00260320);
  FUN_0006a2a0();
  /* cmp eax, 0x10 -> jne 0x6c2fd */
  /* test ebx, ebx -> jle 0x6c2fd */
  /* test ebx, ebx -> jg 0x6c280 */
  /* relift: cmp word ptr [0x3340fc], 8 -> ja 0x6c32d */
  FUN_0006a5d0();
  /* test eax, eax -> je 0x6c227 */
  TIFFGetField();
  /* relift: cmp word ptr [ebp - 0xc], 2 -> jne 0x6c383 */
  /* relift: cmp word ptr [0x3340f8], 1 -> jbe 0x6c383 */
  TIFFIsTiled();
  FUN_0006ba70();
  FUN_0006be40();
  TIFFIsTiled();
  /* test eax, eax -> je 0x6c3a4 */
  FUN_0006b8e0();
  FUN_0006bcb0();
  debug_free((void *)(uintptr_t)esi, (char *)0x00260264, 248);
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
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  TIFFGetField();
  TIFFGetField();
  /* mem[0x003340e0] = ecx */
  /* mem[0x003340c8] = 0 */
  /* mem[0x003340c4] = 0 */
  /* relift: tail-call FUN_0006c080(); */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260264, 125);
  /* test eax, eax -> je 0x6c584 */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260264, 127);
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  FUN_00068a30(0, (char *)0x00260480);
  /* relift: cmp word ptr [eax + 0x5e], 1 -> jne 0x6c611 */
  /* cmp ecx, 8 -> je 0x6c645 */
  /* cmp ecx, 0x10 -> je 0x6c63d */
  FUN_00068a30(0, (char *)0x00260438);
  /* test ecx, ecx -> je 0x6c679 */
  FUN_0006f890();
  TIFFScanlineSize();
  /* cmp edi, ecx -> jle 0x6c6cf */
  /* cmp ecx, 4 -> ja 0x6c6a0 */
  /* test esi, esi -> jle 0x6c6b0 */
  /* test edi, edi -> jg 0x6c694 */
  /* cmp eax, edx -> jle 0x6c760 */
  /* cmp edx, 4 -> ja 0x6c71c */
  /* test esi, esi -> jle 0x6c730 */
  /* test eax, eax -> jg 0x6c710 */
  FUN_0006f9d0();
  /* test (char)ecx, 2 -> je 0x6c80a */
  /* cmp ebx, 8 -> jl 0x6c7fc */
  /* cmp ebx, 8 -> jl 0x6c82e */
  /* cmp edi, ecx -> jle 0x6c8b8 */
  /* cmp ecx, 4 -> ja 0x6c884 */
  /* test esi, esi -> jle 0x6c899 */
  /* test edi, edi -> jg 0x6c878 */
  /* cmp eax, edx -> jle 0x6c940 */
  /* cmp edx, 4 -> ja 0x6c8fc */
  /* test esi, esi -> jle 0x6c910 */
  /* test eax, eax -> jg 0x6c8f0 */
  TIFFFlushData1();
  TIFFFlushData1();
  /* cmp edx, 8 -> jl 0x6ca09 */
  /* test edx, edx -> je 0x6ca21 */
  /* test eax, eax -> je 0x6caee */
  debug_free((void *)(uintptr_t)eax, (char *)0x002604d8, 925);
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
  FUN_0006cb00();
  /* test eax, eax -> je 0x6cd2f */
  FUN_0006cb00();
  /* test eax, eax -> jne 0x6cd6d */
  /* test edi, edi -> jle 0x6cd8e */
  /* test edi, edi -> jg 0x6cd75 */
  /* cmp eax, -1 -> je 0x6cdc5 */
  FUN_0006c960();
  FUN_0006c960();
  /* test ecx, ecx -> jne 0x6ce0b */
  /* relift: cmp eax, dword ptr [esi + 0x24] -> jg 0x6ce4c */
  FUN_0006ca50();
  FUN_0006c960();
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
  FUN_0006cfa0();
  /* test edi, edi -> jle 0x6d1bc */
  /* test edi, edi -> jg 0x6d1a0 */
  FUN_0006cfa0();
  /* test esi, esi -> jne 0x6d279 */
  debug_malloc(30068, esi, (char *)0x002604d8, 619);
  FUN_00068a30(0x00260594, (char *)0x00260574);
  FUN_0006c5e0();
  /* test eax, eax -> je 0x6d22a */
  /* test eax, eax -> je 0x6d279 */
  FUN_0006ca50();
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
  /* cmp (char)ecx, 0x61 -> je 0x6d579 */
  /* cmp (char)ecx, 0x72 -> je 0x6d568 */
  /* cmp (char)ecx, 0x77 -> je 0x6d579 */
  FUN_00068a30(0, (char *)0x002605d0);
  /* cmp (char)ecx, 0x2b -> jne 0x6d588 */
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
  /* relift: cmp word ptr [ecx + 0x5e], 1 -> jne 0x6d83c */
  /* cmp (char)ecx, 0x61 -> je 0x6d954 */
  /* cmp (char)ecx, 0x72 -> je 0x6d910 */
  /* cmp (char)ecx, 0x77 -> je 0x6d954 */
  FUN_00068a30(0x002ec960, (char *)0x002605d0);
  /* cmp (char)ecx, 0x2b -> jne 0x6d91f */
  __open();
  /* test eax, eax -> jge 0x6d965 */
  FUN_00068a30(0x002ec960, (char *)0x002606dc);
  TIFFFdOpen();
  FUN_0006f890();
  TIFFScanlineSize();
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
  /* test edx, edx -> jle 0x6dcbb */
  /* cmp esi, 0x80 -> jl 0x6dc3d */
  /* test esi, esi -> jge 0x6dc8a */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)ebx, esi);
  /* test eax, eax -> jg 0x6dc20 */
  FUN_00068a30(0, (char *)0x002606ec);
  FUN_0006d9c0();
  /* test eax, eax -> jl 0x6dd48 */
  /* test ebx, ebx -> jg 0x6dd20 */
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
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260bd8);
  /* test (char)eax, 4 -> je 0x6e20d */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260bc8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260bb0);
  /* relift: test dword ptr [esi + 0x14], 0x20000000 -> je 0x6e257 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ba0);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dac);
  /* test ebx, eax -> je 0x6e281 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260b60);
  /* relift: test dword ptr [esi + 0x14], 0x40000000 -> je 0x6e29f */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260b50);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260b38);
  /* relift: test byte ptr [esi + 0x18], 1 -> je 0x6e2d6 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260b20);
  /* relift: test byte ptr [esi + 0x18], 2 -> je 0x6e2f1 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260b0c);
  /* relift: test dword ptr [esi + 0x14], ebx -> je 0x6e30b */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260af4);
  /* test (char)eax, 0x10 -> je 0x6e328 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ad8);
  /* test (char)eax, 0x20 -> je 0x6e345 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ac8);
  /* test (char)eax, 0x40 -> je 0x6e362 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ab8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260aa8);
  /* cmp (int16_t)eax, 9 -> jae 0x6e39c */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c60);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  /* relift: test dword ptr [esi + 0x14], 0x10000 -> je 0x6e3cb */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a90);
  /* relift: test dword ptr [esi + 0x14], 0x20000 -> je 0x6e409 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a80);
  /* cmp eax, -1 -> jne 0x6e3fa */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a74);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a70);
  /* relift: test dword ptr [esi + 0x14], 0x40000 -> je 0x6e424 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a58);
  /* relift: test dword ptr [esi + 0x14], 0x80000 -> je 0x6e43f */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a40);
  /* relift: test dword ptr [esi + 0x14], 0x100000 -> je 0x6e489 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260a24);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002609f8);
  /* relift: test dword ptr [esi + 0x14], 0x200000 -> je 0x6e4a7 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002609e4);
  /* relift: test dword ptr [esi + 0x14], 0x400000 -> je 0x6e521 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002609d0);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002609c0);
  /* relift: test byte ptr [esi + 0x68], 4 -> je 0x6e4f9 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002609ac);
  /* relift: test byte ptr [esi + 0x68], 2 -> je 0x6e50e */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260998);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f24);
  /* relift: test byte ptr [esi + 0x18], 0x10 -> je 0x6e574 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260988);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260978);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260944);
  /* relift: test byte ptr [esi + 0x18], 8 -> je 0x6e58c */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x0026092c);
  /* relift: test byte ptr [esi + 0x18], 0x20 -> je 0x6e5a5 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260908);
  /* relift: test dword ptr [esi + 0x14], 0x800000 -> je 0x6e5e4 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002608f4);
  /* test (char)eax, 2 -> je 0x6e5d1 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002608e0);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f24);
  /* relift: test dword ptr [esi + 0x14], 0x2000000 -> je 0x6e605 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002608c8);
  /* relift: test dword ptr [esi + 0x14], 0x10000000 -> je 0x6e698 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002608b8);
  /* test (char)eax, 4 -> je 0x6e68a */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x002608a0);
  /* cmp ebx, eax -> jl 0x6e650 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260894);
  /* relift: test byte ptr [ebp + 0x10], 1 -> je 0x6e70e */
  /* relift: test dword ptr [esi + 0x14], 0x8000000 -> je 0x6e70e */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260878);
  /* test eax, eax -> jbe 0x6e70e */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260860);
  /* cmp ebx, eax -> jb 0x6e6e0 */
  __lseek();
  /* cmp eax, edx -> je 0x6e78a */
  FUN_00068a30(0, (char *)0x00260fcc);
  __read();
  /* cmp eax, ebx -> je 0x6e7c0 */
  FUN_00068a30(0, (char *)0x00260fac);
  __lseek();
  /* cmp eax, edx -> je 0x6e821 */
  FUN_00068a30(0, (char *)0x00261018);
  __read();
  /* cmp eax, ebx -> je 0x6e85e */
  FUN_00068a30(0, (char *)0x00260ff4);
  /* test eax, eax -> je 0x6e8a4 */
  /* relift: test byte ptr [esi + 0xa], 0x40 -> je 0x6e89a */
  debug_free((void *)(uintptr_t)eax, (char *)0x00261070, 515);
  /* test eax, eax -> je 0x6e8ba */
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0x002ecb1c, (char *)0x00261044);
  /* test eax, eax -> je 0x6e97a */
  /* test eax, eax -> jne 0x6e97a */
  /* test eax, eax -> je 0x6e9f8 */
  /* test eax, eax -> jne 0x6e9f8 */
  /* relift: cmp word ptr [eax + 6], 1 -> jne 0x6ea1a */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)(uintptr_t)ecx);
  /* relift: cmp word ptr [esi + 6], 1 -> jne 0x6ea74 */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)0x0026109c);
  /* cmp edi, eax -> jb 0x6eab8 */
  FUN_00068a30(0, (char *)0x00261110);
  /* cmp eax, -1 -> je 0x6ead0 */
  /* cmp eax, ebx -> jae 0x6ead0 */
  FUN_0006e740();
  /* relift: cmp ebx, dword ptr [esi + 0x130] -> jbe 0x6eb56 */
  FUN_00068a30(0x002ecaec, (char *)0x00261130);
  FUN_0006e870();
  /* test eax, eax -> je 0x6eb33 */
  FUN_0006e740();
  /* cmp eax, ebx -> jne 0x6eb33 */
  /* cmp ecx, edx -> je 0x6eb93 */
  /* relift: test byte ptr [edi + 0xa], 0x20 -> jne 0x6eb93 */
  FUN_0006f260();
  FUN_0006e930();
  /* relift: cmp word ptr [esi + 6], 1 -> jne 0x6ebd4 */
  FUN_00068a30(0, (char *)0x002610f4);
  /* test (char)ecx, 1 -> je 0x6ebf9 */
  FUN_00068a30(0, (char *)0x002610c8);
  /* cmp edi, eax -> jb 0x6ec20 */
  FUN_00068a30(0, (char *)0x0026115c);
  /* cmp eax, ebx -> jae 0x6ec38 */
  FUN_0006e7d0();
  /* relift: cmp ebx, dword ptr [esi + 0x130] -> jbe 0x6ecb6 */
  FUN_00068a30(0x002ecb0c, (char *)0x0026117c);
  FUN_0006e870();
  /* test eax, eax -> je 0x6ec93 */
  FUN_0006e7d0();
  /* cmp eax, ebx -> jne 0x6ec93 */
  /* cmp ecx, edx -> je 0x6ecf3 */
  /* relift: test byte ptr [edi + 0xa], 0x20 -> jne 0x6ecf3 */
  FUN_0006f260();
  FUN_0006e980();
  /* cmp ebx, eax -> jb 0x6ed2c */
  FUN_00068a30(0, (char *)0x00261200);
  /* relift: cmp word ptr [edi + 0x5e], 2 -> jne 0x6ed64 */
  /* cmp ecx, eax -> jb 0x6ed50 */
  FUN_00068a30(0, (char *)0x002611e0);
  /* relift: cmp eax, dword ptr [edi + 0xdc] -> je 0x6ed82 */
  FUN_0006eaf0();
  /* test eax, eax -> jne 0x6ed99 */
  /* relift: cmp ebx, dword ptr [edi + 0xd4] -> jae 0x6ed99 */
  FUN_0006e930();
  /* cmp ebx, eax -> je 0x6edc2 */
  /* test ecx, ecx -> je 0x6edc8 */
  /* test eax, eax -> je 0x6edd8 */
  FUN_00068a30(0, (char *)0x002611a8);
  FUN_0006f180();
  /* relift: cmp word ptr [esi + 6], 1 -> jne 0x6ee0d */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)0x0026109c);
  /* cmp ebx, ecx -> jb 0x6ee51 */
  FUN_00068a30(0, (char *)0x00261110);
  /* cmp edi, -1 -> je 0x6ee5e */
  /* cmp edi, eax -> jbe 0x6ee60 */
  FUN_0006eaf0();
  /* test eax, eax -> je 0x6ee93 */
  /* test eax, eax -> je 0x6ee93 */
  FUN_00068a30(0, (char *)0x002610f4);
  /* test (char)ecx, 1 -> je 0x6eeef */
  FUN_00068a30(0, (char *)0x002610c8);
  FUN_0006f780();
  /* test eax, eax -> je 0x6eec0 */
  FUN_0006f690();
  /* cmp eax, ecx -> jb 0x6ef43 */
  FUN_00068a30(0, (char *)0x0026115c);
  FUN_0006ec50();
  /* test eax, eax -> je 0x6eec0 */
  /* test eax, eax -> je 0x6eec0 */
  FUN_00068a30(0, (char *)0x002610f4);
  /* test dl, 1 -> je 0x6efcf */
  FUN_00068a30(0, (char *)0x002610c8);
  /* cmp ebx, eax -> jb 0x6eff6 */
  FUN_00068a30(0, (char *)0x0026115c);
  /* cmp edi, -1 -> je 0x6f003 */
  /* cmp edi, ecx -> jbe 0x6f005 */
  FUN_0006ec50();
  /* test eax, eax -> je 0x6f038 */
  /* test eax, eax -> je 0x6f038 */
  /* relift: cmp word ptr [edi + 6], 1 -> jne 0x6f064 */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)0x0026109c);
  FUN_0006ed10();
  /* test eax, eax -> je 0x6f0b7 */
  /* cmp esi, edx -> jb 0x6f108 */
  FUN_00068a30(0, (char *)0x002611e0);
  /* cmp ecx, -1 -> jne 0x6f13c */
  /* cmp esi, -1 -> jne 0x6f162 */
  TIFFScanlineSize();
  /* cmp esi, -1 -> jne 0x6f192 */
  TIFFScanlineSize();
  /* test esi, esi -> jle 0x6f211 */
  /* test esi, esi -> jle 0x6f24e */
  /* cmp esi, 8 -> jle 0x6f2ef */
  /* test esi, esi -> jle 0x6f30f */
  /* relift: cmp eax, dword ptr [ebp + 0x10] -> jge 0x6f4f7 */
  /* test (char)eax, 1 -> je 0x6f399 */
  /* cmp esi, -1 -> jne 0x6f3f7 */
  /* cmp ecx, 2 -> je 0x6f433 */
  /* test (char)ecx, (char)ecx -> je 0x6f42c */
  /* cmp ecx, 2 -> je 0x6f467 */
  /* test (char)ecx, (char)ecx -> je 0x6f460 */
  /* cmp esi, 2 -> je 0x6f4e9 */
  /* cmp ecx, 4 -> je 0x6f4b3 */
  /* test (char)ecx, (char)ecx -> je 0x6f4ac */
  /* cmp esi, 4 -> je 0x6f4e9 */
  /* test (char)ecx, (char)ecx -> je 0x6f4e2 */
  FUN_00068a30(0, (char *)0x00261220);
  FUN_0006f320();
  /* test eax, eax -> je 0x6f65d */
  /* test esi, esi -> jg 0x6f633 */
  /* cmp ebx, -1 -> jne 0x6f6c9 */
  /* cmp edi, -1 -> jne 0x6f6d1 */
  /* cmp esi, -1 -> jne 0x6f6d8 */
  /* test ebx, ebx -> je 0x6f776 */
  /* test edi, edi -> je 0x6f776 */
  /* test esi, esi -> je 0x6f776 */
  /* cmp edx, ecx -> jb 0x6f7a6 */
  FUN_00068a30(0, (char *)0x002612c8);
  /* cmp edx, ecx -> jb 0x6f7c6 */
  FUN_00068a30(0, (char *)0x002612ac);
  /* cmp edx, ecx -> jb 0x6f7e6 */
  FUN_00068a30(0, (char *)0x0026128c);
  /* relift: cmp word ptr [eax + 0x5e], 2 -> jne 0x6f80e */
  /* cmp edx, ecx -> jb 0x6f80e */
  FUN_00068a30(0, (char *)0x0026126c);
  /* cmp edi, -1 -> jne 0x6f83a */
  /* cmp ebx, -1 -> jne 0x6f842 */
  /* cmp esi, -1 -> jne 0x6f84a */
  /* test edi, edi -> je 0x6f886 */
  /* test ebx, ebx -> je 0x6f886 */
  /* test esi, esi -> je 0x6f886 */
  /* test eax, eax -> je 0x6f8c1 */
  /* test edx, edx -> je 0x6f8c1 */
  /* relift: cmp word ptr [ecx + 0x5e], 1 -> jne 0x6f8b9 */
  /* test ecx, ecx -> je 0x6f8ff */
  /* test esi, esi -> je 0x6f8ff */
  FUN_0006f890();
  /* test eax, eax -> je 0x6f941 */
  /* test edi, edi -> je 0x6f941 */
  FUN_0006f890();
  /* test eax, eax -> je 0x6f96d */
  crt_fprintf((void *)0x00331070, (char *)0x00259f68);
  crt_fprintf((void *)0x00331070, (char *)0x002612e4);
  FUN_001d9850();
  crt_fprintf((void *)0x00331070, (char *)0x00260020);
  /* mem[0x002ecfac] = ecx */
  /* test eax, eax -> je 0x6f9ed */
  /* cmp ecx, -1 -> je 0x6fa28 */
  /* test eax, eax -> je 0x6fa28 */
  /* relift: cmp dword ptr [esi + 0x2c], -1 -> je 0x6fa28 */
  /* test eax, eax -> je 0x6fa28 */
  FUN_0006f820();
  debug_malloc(edx, 0, (char *)0, 0);
  debug_malloc(eax, 0, (char *)0, 0);
  /* test eax, eax -> je 0x6fade */
  csmemset((void *)(uintptr_t)ecx, 0, edx);
  csmemset((void *)(uintptr_t)ecx, 0, eax);
  /* relift: cmp word ptr [esi + 6], 0 -> jne 0x6fb0f */
  FUN_00068a30(0, (char *)0x002613f4);
  FUN_00068a30(0, (char *)(uintptr_t)eax);
  /* test (char)eax, 8 -> jne 0x6fbc2 */
  /* test (char)eax, 1 -> jne 0x6fb62 */
  FUN_00068a30(0, (char *)0x00261370);
  /* test eax, 0x100000 -> jne 0x6fb7e */
  FUN_00068a30(0, (char *)0x00261338);
  /* test eax, eax -> jne 0x6fbbe */
  FUN_0006f9f0();
  /* test eax, eax -> jne 0x6fbbe */
  FUN_00068a30(0, (char *)0x0026131c);
  FUN_0006f910();
  TIFFScanlineSize();
  /* cmp edi, 0x2000 -> jge 0x6fc08 */
  debug_malloc(edi, 0, (char *)0x002612f0, 484);
  FUN_00068a30(0, (char *)0x00261414);
  debug_realloc((void *)(uintptr_t)ecx, 0, (char *)0, 0);
  debug_realloc((void *)(uintptr_t)eax, 0, (char *)0, 0);
  /* test eax, eax -> je 0x6fd0b */
  csmemset((void *)(uintptr_t)edx, 0, 0);
  csmemset((void *)(uintptr_t)eax, 0, 0);
  FUN_00068a30(0, (char *)0x00261434);
  /* test eax, eax -> je 0x6fd8b */
  /* test ecx, ecx -> jne 0x6fdb4 */
  /* test eax, eax -> je 0x6fd8b */
  __lseek();
  /* cmp eax, ecx -> je 0x6fda5 */
  FUN_00068a30(0x002ed078, (char *)0x00261478);
  __lseek();
  __write();
  /* cmp eax, ebx -> je 0x6fdea */
  FUN_00068a30(0x002ed078, (char *)0x00261458);
  /* test eax, eax -> jle 0x6fe8e */
  /* cmp ecx, edx -> je 0x6fe43 */
  /* relift: test byte ptr [esi + 0xa], 0x20 -> jne 0x6fe43 */
  FUN_0006f260();
  FUN_0006fd30();
  FUN_0006faf0();
  /* test eax, eax -> jne 0x6fecb */
  /* test (char)ebx, (char)eax -> jne 0x6feed */
  FUN_0006fbd0();
  /* test eax, eax -> je 0x6ff10 */
  /* relift: cmp word ptr [esi + 0x5e], (int16_t)eax -> jne 0x6ff1a */
  FUN_00068a30(0, (char *)0x00261498);
  /* relift: cmp word ptr [esi + 0x5e], (int16_t)eax -> jne 0x6ff6b */
  /* cmp ecx, eax -> jb 0x6ff54 */
  FUN_00068a30(0, (char *)0x002611e0);
  /* relift: cmp ebx, dword ptr [esi + 0xdc] -> je 0x6fff0 */
  /* test eax, eax -> jle 0x6ff97 */
  FUN_0006a210();
  /* test eax, eax -> je 0x6ff10 */
  /* relift: cmp ebx, dword ptr [esi + 0xb4] -> jb 0x6ffc0 */
  /* test eax, eax -> je 0x6ffc0 */
  /* test eax, eax -> je 0x6ff10 */
  /* relift: cmp ebx, dword ptr [esi + 0xb8] -> jb 0x70015 */
  FUN_0006fc60();
  /* test eax, eax -> je 0x6ff10 */
  /* cmp edi, eax -> je 0x7006c */
  /* test ecx, ecx -> je 0x70099 */
  /* cmp edi, eax -> jae 0x7004d */
  /* test eax, eax -> je 0x6ff10 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x74fb0 */
void FUN_00074fb0(void *pixel_data, void *bitmap_data)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x74fea */
  display_assert((char *)0x00261aa4, (char *)0x002616f0, 1529, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x75011 */
  display_assert((char *)0x00261e30, (char *)0x002616f0, 1530, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x75038 */
  display_assert((char *)0x00261e0c, (char *)0x002616f0, 1531, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xa] -> je 0x75062 */
  display_assert((char *)0x00261944, (char *)0x002616f0, 1532, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ecx, word ptr [edi + 4] -> je 0x7508c */
  display_assert((char *)0x00261ddc, (char *)0x002616f0, 1533, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edx, word ptr [edi + 6] -> je 0x750b6 */
  display_assert((char *)0x00261da8, (char *)0x002616f0, 1534, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 8] -> je 0x750e0 */
  display_assert((char *)0x00261d78, (char *)0x002616f0, 1535, 0);
  system_exit(0);
  /* relift: cmp word ptr [edx + 4], 0 -> jne 0x75127 */
  /* cmp (int16_t)eax, 1 -> je 0x75127 */
  /* cmp (int16_t)eax, 6 -> je 0x75127 */
  /* cmp (int16_t)eax, 0xa -> je 0x75127 */
  /* test (char)eax, 0x41 -> jne 0x75175 */
  floor(0.0f);
  FUN_001d9068();
  /* cmp (int16_t)esi, 0xff01 -> jl 0x751ab */
  /* cmp (int16_t)esi, 0xff -> jle 0x751cb */
  display_assert((char *)0x00261d54, (char *)0x002616f0, 1558, 0);
  system_exit(0);
  bitmap_shrink((void *)(uintptr_t)ecx, 0, 0, 0);
  /* test esi, esi -> je 0x7532a */
  /* test eax, eax -> je 0x7532a */
  bitmap_sharpen();
  /* relift: cmp word ptr [eax + 4], 3 -> jne 0x75287 */
  /* test (char)eax, 0x41 -> jne 0x7526d */
  bitmap_fade((void *)(uintptr_t)esi, 0xff7f7f7f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x7529b */
  bitmap_alpha_bleed((void *)(uintptr_t)esi, 0);
  /* relift: cmp word ptr [eax + 4], 2 -> jne 0x752b4 */
  FUN_0007c5f0((void *)(uintptr_t)esi, 0.0f);
  /* relift: cmp word ptr [eax + 4], 5 -> jne 0x752c9 */
  FUN_0007c6c0((void *)(uintptr_t)esi);
  /* relift: test byte ptr [eax + 6], 1 -> je 0x75317 */
  /* cmp (int16_t)eax, 2 -> je 0x75317 */
  /* cmp (int16_t)eax, 4 -> je 0x75317 */
  /* cmp (int16_t)eax, 5 -> je 0x75317 */
  FUN_0007f150();
  FUN_00074210();
  bitmap_delete((void *)(uintptr_t)esi);
  error(0, (char *)0x002617dc);
  /* test eax, eax -> je 0x75372 */
  FUN_00074a30();
  bitmap_delete((void *)(uintptr_t)eax);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x753b8 */
  display_assert((char *)0x00261814, (char *)0x002616f0, 1159, 0);
  system_exit(0);
  FUN_00073fd0((void *)0);
  /* relift: cmp word ptr [edx + 4], 4 -> je 0x7540c */
  bitmap_get_max_mipmap_count((void *)(uintptr_t)edi);
  /* relift: cmp word ptr [edx], 3 -> jne 0x753f4 */
  /* cmp (int16_t)eax, 2 -> jl 0x753f4 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x7540e */
  /* cmp ecx, eax -> jg 0x7540e */
  FUN_00077120((void *)(uintptr_t)edx, 0, 0, 0, 0, 0, 0);
  FUN_00077590((void *)(uintptr_t)edi);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 8 -> je 0x75495 */
  /* test edi, edi -> je 0x75606 */
  /* test eax, eax -> je 0x75606 */
  /* test (char)eax, 0x41 -> jne 0x7554f */
  /* cmp eax, 4 -> ja 0x7552f */
  bitmap_smooth((void *)(uintptr_t)edi, 0.0f);
  crt_fprintf((void *)0x00331050, (char *)0x00261f00);
  crt_fflush((void *)0x00331050);
  crt_fprintf((void *)0x00331050, (char *)0x00261ec8);
  crt_fflush((void *)0x00331050);
  display_assert((char *)0x00261ea0, (char *)0x002616f0, 1232, 0);
  system_exit(0);
  /* relift: tail-call FUN_00074fb0(); */
  bitmap_get_pixel_data_size((void *)0);
  bitmap_format_get_string(0);
  crt_fprintf((void *)0x00331050, (char *)0x00261e70);
  crt_fflush((void *)0x00331050);
  bitmap_get_pixel_data_size((void *)0);
  bitmap_format_get_string(0);
  crt_fprintf((void *)0x00331050, (char *)0x00261e44);
  crt_fflush((void *)0x00331050);
  /* relift: cmp (int16_t)eax, word ptr [0x334138] -> jge 0x757ef */
  /* relift: cmp word ptr [ecx + 4], (int16_t)eax -> jne 0x756c8 */
  /* relift: cmp word ptr [ecx + 4], (int16_t)eax -> jne 0x756ba */
  /* relift: cmp word ptr [ecx + 6], (int16_t)eax -> je 0x756be */
  /* test (char)eax, (char)eax -> je 0x75690 */
  /* test (char)eax, (char)eax -> je 0x756f0 */
  crt_fprintf((void *)0x00331050, (char *)0x00261f68);
  crt_fflush((void *)0x00331050);
  /* test eax, ecx -> je 0x7571b */
  crt_fprintf((void *)0x00331050, (char *)0x00261f30);
  crt_fflush((void *)0x00331050);
  bitmap_3d_new(0, 0, 0, 0, 11);
  /* test ecx, ecx -> je 0x757bd */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x75772 */
  bitmap_cube_map_face_extract((void *)(uintptr_t)eax, (void *)(uintptr_t)ecx, 0, 0);
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x75750 */
  FUN_00075380((void *)0);
  /* cmp (int16_t)esi, -1 -> je 0x757d0 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* relift: cmp word ptr [eax + 0x20], -1 -> jne 0x757b7 */
  error(0, (char *)0x002617dc);
  bitmap_delete((void *)(uintptr_t)eax);
  /* relift: cmp (int16_t)eax, word ptr [0x334138] -> jge 0x7597e */
  /* test edi, edi -> je 0x75868 */
  display_assert((char *)0x0026208c, (char *)0x002616f0, 1944, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ecx + 6] -> jne 0x7588c */
  bitmap_cube_map_new(0, 0, 11);
  crt_fprintf((void *)0x00331050, (char *)0x00262060);
  crt_fflush((void *)0x00331050);
  /* test edi, edi -> je 0x759fa */
  /* test eax, eax -> je 0x759fa */
  /* relift: cmp word ptr [esi + 4], (int16_t)ecx -> jne 0x759d9 */
  /* relift: cmp (int16_t)edx, word ptr [edi + 4] -> jne 0x759b8 */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 6] -> jne 0x759b8 */
  bitmap_cube_map_face_insert();
  /* test (char)eax, (char)eax -> je 0x7590b */
  bitmap_delete((void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x75961 */
  /* cmp (int16_t)ebx, 6 -> jne 0x75961 */
  FUN_00075380((void *)0);
  /* cmp (int16_t)ebx, -1 -> je 0x75954 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp word ptr [eax + 0x20], -1 -> jne 0x75950 */
  bitmap_delete((void *)(uintptr_t)edi);
  bitmap_delete((void *)(uintptr_t)ecx);
  /* test edi, edi -> je 0x759ae */
  /* test (char)eax, (char)eax -> je 0x759a5 */
  crt_fprintf((void *)0x00331050, (char *)0x00262030);
  crt_fflush((void *)0x00331050);
  bitmap_delete((void *)(uintptr_t)edi);
  crt_fprintf((void *)0x00331050, (char *)0x00261ffc);
  crt_fflush((void *)0x00331050);
  crt_fprintf((void *)0x00331050, (char *)0x00261fd0);
  crt_fflush((void *)0x00331050);
  /* test (char)eax, (char)eax -> jne 0x7590b */
  error(0, (char *)0x00261f98);
  /* relift: cmp (int16_t)ebx, word ptr [0x334138] -> jge 0x75ad9 */
  /* test eax, eax -> je 0x75ad2 */
  /* relift: cmp word ptr [eax + 4], (int16_t)ecx -> jg 0x75ab9 */
  /* relift: cmp word ptr [eax + 6], (int16_t)ecx -> jle 0x75ad2 */
  error(0, (char *)0x00262210);
  /* test dl, dl -> jne 0x75a92 */
  /* test dl, dl -> je 0x75b1a */
  /* relift: test byte ptr [ecx + 6], 4 -> je 0x75af8 */
  error(0, (char *)0x00262188);
  FUN_000747d0();
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x1c] -> jge 0x75dc7 */
  bitmap_2d_new(0, 0, 0, 11);
  /* test eax, eax -> je 0x75d61 */
  FUN_00077510((void *)(uintptr_t)esi, 0);
  /* relift: cmp (int16_t)eax, word ptr [0x334138] -> jge 0x75d33 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_0011fef0();
  /* test (char)ebx, 8 -> jne 0x75c23 */
  /* relift: cmp word ptr [edx + 0x30], 1 -> jne 0x75c23 */
  /* cmp (int16_t)ecx, -1 -> jne 0x75ce5 */
  FUN_00072490();
  bitmap_delete((void *)(uintptr_t)ecx);
  FUN_00075380((void *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x75d74 */
  bitmap_delete((void *)(uintptr_t)esi);
  error(0, (char *)0x00262140);
  FUN_0011fd10();
  crt_fprintf((void *)0x00331050, (char *)0x00262110);
  crt_fflush((void *)0x00331050);
  FUN_0011fe80();
  /* test dl, dl -> je 0x75b23 */
  crt_fprintf((void *)0x00331050, (char *)0);
  crt_fflush((void *)0x00331050);
  crt_fprintf((void *)0x00331050, (char *)0x002620cc);
  crt_fflush((void *)0x00331050);
  error(0, (char *)0x002620a0);
  display_assert((char *)0x0026184c, (char *)0x002616f0, 802, 0);
  system_exit(0);
  FUN_00073e40();
  /* test (char)eax, (char)eax -> je 0x762cd */
  bitmap_2d_new(0, 0, 0, 0);
  /* relift: test byte ptr [edx + 6], 8 -> je 0x75f1f */
  bitmap_2d_address((void *)(uintptr_t)ebx, 0, 0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x1a] -> jge 0x760be */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x75fc7 */
  /* cmp eax, ecx -> je 0x75fc5 */
  /* relift: cmp eax, dword ptr [0x334144] -> je 0x75fc5 */
  /* relift: cmp eax, dword ptr [0x334140] -> jne 0x75fc7 */
  /* relift: cmp word ptr [ecx + 4], 0 -> jne 0x76011 */
  /* test esi, 0xff000000 -> jne 0x76011 */
  /* test esi, 0xffffff -> je 0x76011 */
  /* test (char)eax, (char)eax -> jne 0x76011 */
  crt_fprintf((void *)0x00331050, (char *)0x002623f0);
  crt_fflush((void *)0x00331050);
  /* relift: cmp word ptr [ecx + 2], 0 -> jne 0x7607e */
  /* test edi, edi -> je 0x7605a */
  /* cmp edi, 0xff -> je 0x76056 */
  /* test (char)eax, (char)eax -> jne 0x76056 */
  crt_fprintf((void *)0x00331050, (char *)0x00262398);
  crt_fflush((void *)0x00331050);
  /* test edi, edi -> jne 0x76078 */
  /* cmp edx, eax -> je 0x76074 */
  /* test (char)eax, (char)eax -> jne 0x76078 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x76093 */
  /* cmp (int16_t)eax, 1 -> je 0x76093 */
  /* cmp (int16_t)eax, 2 -> jne 0x760a8 */
  /* relift: cmp word ptr [ecx], 4 -> jne 0x760a8 */
  error(0, (char *)0x00262358);
  /* test (int16_t)eax, (int16_t)eax -> je 0x7626a */
  /* cmp (int16_t)eax, 4 -> je 0x7626a */
  /* test (char)ecx, (char)ecx -> jne 0x76146 */
  /* cmp (int16_t)eax, 2 -> jne 0x76120 */
  FUN_00073b00();
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x002622c0);
  bitmap_delete((void *)(uintptr_t)ebx);
  /* cmp (int16_t)eax, 0x400 -> jge 0x7624d */
  /* relift: cmp word ptr [edx], 3 -> jne 0x76116 */
  tag_block_add_element((void *)(uintptr_t)eax);
  /* cmp (int16_t)edi, -1 -> je 0x76235 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  error(0, (char *)0x0026228c);
  error(0, (char *)0x00261798);
  FUN_00075380((void *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x7610d */
  /* relift: cmp word ptr [ecx + 0x20], -1 -> jne 0x7629e */
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x002617dc);
  crt_fprintf((void *)0x00331050, (char *)0x00262254);
  crt_fflush((void *)0x00331050);
  /* test (char)eax, (char)eax -> je 0x76336 */
  error(0, (char *)0x002624b8);
  /* cmp eax, 4 -> ja 0x763d3 */
  tag_block_add_element((void *)(uintptr_t)ecx);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* mem[0x00334158] = eax */
  FUN_00075e70();
  error(0, (char *)0x0026247c);
  error(0, (char *)0x00262444);
  display_assert((char *)0x00261ea0, (char *)0x002616f0, 422, 0);
  system_exit(0);
  display_assert((char *)0x0026253c, (char *)0x002616f0, 564, 0);
  system_exit(0);
  /* cmp (int16_t)esi, (int16_t)edi -> jge 0x7646e */
  display_assert((char *)0x00262530, (char *)0x002616f0, 565, 0);
  system_exit(0);
  /* relift: cmp (int16_t)esi, word ptr [eax + 6] -> jle 0x76499 */
  display_assert((char *)0x0026250c, (char *)0x002616f0, 566, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ebx, word ptr [ecx + 4] -> jge 0x766d6 */
  /* cmp (int16_t)edi, 2 -> je 0x765d1 */
  bitmap_2d_address((void *)(uintptr_t)ecx, 0, 0, 0);
  /* cmp eax, ecx -> jne 0x76531 */
  /* relift: cmp eax, dword ptr [0x33413c] -> je 0x7657f */
  /* cmp (int16_t)esi, (int16_t)eax -> jle 0x76562 */
  /* cmp (int16_t)esi, (int16_t)eax -> jle 0x76577 */
  /* test (char)eax, (char)eax -> jne 0x765a1 */
  /* test (char)eax, (char)eax -> je 0x765ae */
  /* test (char)eax, (char)eax -> jne 0x765ae */
  /* cmp (int16_t)edi, 1 -> jne 0x765c0 */
  /* test (char)eax, (char)eax -> jne 0x765c0 */
  /* relift: cmp (int16_t)ebx, word ptr [ecx + 4] -> jl 0x764e0 */
  /* cmp (int16_t)edi, (int16_t)ecx -> jge 0x7665c */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, ecx -> jne 0x7664c */
  /* relift: cmp (int16_t)esi, word ptr [ebp - 0xa] -> jl 0x76620 */
  /* relift: cmp (int16_t)esi, word ptr [ebp - 0xa] -> jl 0x76659 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0xc] -> jl 0x76610 */
  /* cmp (int16_t)esi, (int16_t)ebx -> jge 0x766b1 */
  bitmap_2d_address((void *)(uintptr_t)ecx, 0, 0, 0);
  /* cmp eax, ecx -> jne 0x766ac */
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x76680 */
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x766b8 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0x18] -> jge 0x76672 */
  FUN_00075e70();
  /* test (char)eax, (char)eax -> jne 0x764a0 */
  /* relift: cmp (int16_t)ecx, word ptr [edx + 6] -> jge 0x76786 */
  FUN_00073960((void *)(uintptr_t)eax);
  FUN_00073a80();
  tag_block_add_element((void *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 0xffff -> je 0x76775 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* mem[0x00334158] = eax */
  FUN_00076410(0, 0);
  error(0, (char *)0x00262544);
  /* test esi, esi -> jne 0x767bc */
  display_assert((char *)0x0026276c, (char *)0x002616f0, 180, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x767ca */
  /* cmp (int16_t)eax, 5 -> jl 0x767ea */
  display_assert((char *)0x0026272c, (char *)0x002616f0, 181, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x767f9 */
  /* cmp (int16_t)eax, 6 -> jl 0x76819 */
  display_assert((char *)0x002626e8, (char *)0x002616f0, 182, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x76828 */
  /* cmp (int16_t)eax, 6 -> jl 0x76848 */
  display_assert((char *)0x002626a8, (char *)0x002616f0, 183, 0);
  system_exit(0);
  debug_malloc(16384, 0, (char *)0x002616f0, 186);
  /* mem[0x00334134] = eax */
  error(0, (char *)0x00262674);
  error(0, (char *)0x00262634);
  tag_block_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x76882 */
  tag_block_resize((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x76882 */
  tag_data_resize((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x76882 */
  /* mem[0x00334158] = 0 */
  /* mem[0x0033414c] = esi */
  bitmap_2d_new(0, 0, 0, 11);
  /* mem[0x00334150] = eax */
  FUN_00119bb0((void *)(uintptr_t)eax, edx);
  display_assert((char *)0x002625e0, (char *)0x002616f0, 260, 0);
  system_exit(0);
  bitmap_mipmap_address((void *)(uintptr_t)ecx, 0);
  FUN_00119bf0((void *)(uintptr_t)eax, edx, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x769cd */
  FUN_00073830();
  /* mem[0x00334154] = ecx */
  FUN_000766e0();
  FUN_00076300();
  bitmap_delete((void *)(uintptr_t)edx);
  /* test (char)ebx, (char)ebx -> je 0x76a2e */
  /* cmp eax, 4 -> ja 0x76a0e */
  error(0, (char *)0x002625a8);
  error(0, (char *)0x00262574);
  FUN_00075630();
  FUN_00075800();
  FUN_00075a20();
  display_assert((char *)0x00261ea0, (char *)0x002616f0, 311, 0);
  system_exit(0);
  /* test eax, eax -> je 0x76a4a */
  debug_free((void *)(uintptr_t)eax, (char *)0x002616f0, 317);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x76aa7 */
  display_assert((char *)0x00262814, (char *)0x002616f0, 131, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x76ace */
  display_assert((char *)0x0026276c, (char *)0x002616f0, 132, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)edi);
  debug_malloc(eax, 0, (char *)0x002616f0, 138);
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  FUN_00119b40(0, 0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x76b76 */
  debug_realloc((void *)(uintptr_t)ecx, 0, (char *)0x002616f0, 144);
  /* test eax, eax -> je 0x76b61 */
  FUN_00076790((void *)(uintptr_t)esi, 0);
  error(0, (char *)0x002627e0);
  error(0, (char *)0x002627ac);
  error(0, (char *)0x00262774);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 48);
  bitmap_delete((void *)(uintptr_t)eax);
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 48);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x76c38 */
  texture_cache_bitmap_new(0, (void *)(uintptr_t)esi);
  /* cmp eax, ecx -> jl 0x76c02 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 64);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 64);
  /* relift: cmp word ptr [ecx], 3 -> jne 0x76cba */
  /* relift: cmp word ptr [ebx + 0x20], 0 -> jne 0x76c9b */
  /* relift: cmp word ptr [ebx + 0x22], 0 -> je 0x76cba */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 64);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 64);
  /* relift: cmp esi, dword ptr [edi] -> jl 0x76c60 */
  /* test eax, eax -> jle 0x76d1a */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  /* relift: cmp word ptr [eax + 0x22], 0 -> jne 0x76d1a */
  /* test ecx, ecx -> jne 0x76d1a */
  tag_block_resize((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x76d1a */
  tag_get_name(0);
  error(0, (char *)0x00263eb4);
  /* test (char)eax, (char)eax -> je 0x76fd7 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 48);
  /* relift: cmp word ptr [edi + 0xc], 3 -> jne 0x76d6f */
  tag_get_name(0);
  error(0, (char *)0x00263e78);
  /* relift: test byte ptr [edi + 0xe], 0x10 -> je 0x76da5 */
  /* test eax, edx -> jne 0x76da5 */
  /* test eax, ecx -> jne 0x76da5 */
  tag_get_name(0);
  error(0, (char *)0x00263e30);
  /* relift: cmp esi, dword ptr [ebx] -> jl 0x76d40 */
  /* cmp ebx, 1 -> jge 0x76ddc */
  tag_get_name(0);
  error(0, (char *)0x00263df4);
  /* cmp eax, 1 -> jge 0x76e0c */
  tag_get_name(0);
  error(0, (char *)0x00263df4);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 64);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 64);
  /* relift: cmp word ptr [eax], 3 -> jne 0x76e8c */
  /* relift: cmp word ptr [ebx + 0x20], 0 -> jne 0x76e6b */
  /* relift: cmp word ptr [ebx + 0x22], 0 -> je 0x76ef8 */
  tag_get_name(0);
  error(0, (char *)0x00263d70);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x76ed0 */
  /* cmp edx, esi -> jge 0x76ed0 */
  /* cmp (int16_t)eax, 1 -> jl 0x76ed0 */
  /* cmp eax, esi -> jg 0x76ed0 */
  /* relift: cmp word ptr [ebp - 0xc], 0 -> jne 0x76ec1 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x76ed0 */
  /* test edx, edx -> je 0x76ef8 */
  /* cmp edx, eax -> je 0x76ef8 */
  tag_get_name(0);
  error(0, (char *)0x00263d20);
  /* cmp (int16_t)ecx, 3 -> jne 0x76f96 */
  /* cmp eax, 1 -> jge 0x76f36 */
  tag_get_name(0);
  error(0, (char *)0x00263cdc);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 32);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x76f64 */
  /* relift: cmp edx, dword ptr [ecx] -> jl 0x76f86 */
  tag_get_name(0);
  error(0, (char *)0x00263c88);
  /* relift: cmp esi, dword ptr [ebx] -> jl 0x76f43 */
  /* test eax, eax -> jle 0x76fbf */
  tag_get_name(0);
  error(0, (char *)0x00263c38);
  /* relift: cmp edi, dword ptr [esi] -> jl 0x76e20 */
  tag_get(0x6269746d, 0);
  /* test ecx, ecx -> je 0x7702f */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x7702f */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 48);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x77063 */
  /* relift: cmp word ptr [ebp + 0x10], (int16_t)eax -> jge 0x77083 */
  display_assert((char *)0x00263ee4, (char *)0x00263f08, 678, 0);
  system_exit(0);
  tag_get('mtib', 0);
  /* test ebx, ebx -> je 0x77115 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x770ce */
  /* relift: cmp dword ptr [eax], 0 -> je 0x770ef */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 32);
  /* cmp (int16_t)edx, -1 -> jne 0x770f2 */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x77115 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 48);
  display_assert((char *)0x0026276c, (char *)0x00263f08, 731, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0xe -> jl 0x771c7 */
  /* cmp (int16_t)edi, 0x10 -> jg 0x771c7 */
  /* cmp (int16_t)edi, 0x11 -> jne 0x771d1 */
  /* cmp (int16_t)edx, 2 -> jne 0x772b3 */
  /* cmp (int16_t)esi, (int16_t)eax -> je 0x772b3 */
  crt_fprintf((void *)0x00331050, (char *)0x00264120);
  crt_fflush((void *)0x00331050);
  /* test edi, ebx -> jne 0x77281 */
  /* cmp (int16_t)edx, 2 -> jne 0x77241 */
  /* cmp (int16_t)esi, (int16_t)eax -> jne 0x77253 */
  crt_fprintf((void *)0x00331050, (char *)0x00264120);
  crt_fflush((void *)0x00331050);
  crt_fprintf((void *)0x00331050, (char *)0x002640e0);
  crt_fflush((void *)0x00331050);
  /* relift: test byte ptr [ebp - 0x26], 1 -> jne 0x772ed */
  /* cmp (int16_t)edx, 4 -> je 0x772ed */
  crt_fprintf((void *)0x00331050, (char *)0x0026409c);
  crt_fflush((void *)0x00331050);
  bitmap_get_pixel_data_size((void *)(uintptr_t)eax);
  tag_block_resize((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x774e0 */
  tag_data_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x774e0 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 48);
  /* test eax, eax -> je 0x77460 */
  /* test eax, eax -> je 0x77390 */
  display_assert((char *)0x00264080, (char *)0x00263f08, 845, 0);
  system_exit(0);
  /* relift: cmp eax, dword ptr [edi + 0x3c] -> jae 0x773c0 */
  display_assert((char *)0x00264040, (char *)0x00263f08, 850, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  /* cmp eax, edx -> jbe 0x773fa */
  display_assert((char *)0x00263fc0, (char *)0x00263f08, 852, 0);
  system_exit(0);
  /* test eax, eax -> je 0x7744d */
  bitmap_get_pixel_data_size((void *)(uintptr_t)eax);
  display_assert((char *)0x00263fa8, (char *)0x00263f08, 859, 0);
  system_exit(0);
  /* test edi, edi -> je 0x7744a */
  error(0, (char *)0x00263f78);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 48);
  /* test esi, esi -> jne 0x774ae */
  display_assert((char *)0x00263f6c, (char *)0x00263f08, 881, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, 48);
  csmemset((void *)(uintptr_t)eax, 0, edx);
  error(0, (char *)0x00263f30);
  tag_block_resize((void *)(uintptr_t)esi, 0);
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)esi);
  /* test eax, eax -> jle 0x7753a */
  bitmap_2d_address((void *)(uintptr_t)edi, 0, 0, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)edi);
  /* test eax, eax -> jle 0x77582 */
  /* test esi, esi -> jne 0x775bc */
  display_assert((char *)0x002641e0, (char *)0x002641f0, 103, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x775e0 */
  display_assert((char *)0x002641c4, (char *)0x002641f0, 104, 0);
  system_exit(0);
  display_assert((char *)0x00261d30, (char *)0x002641f0, 131, 0);
  system_exit(0);
  error(0, (char *)0x00264194);
  bitmap_cube_map_new(0, 0, 0);
  bitmap_3d_new(0, 0, 0, 0, 0);
  bitmap_2d_new(0, 0, 0, 0);
  /* test edi, edi -> je 0x77613 */
  /* test eax, eax -> je 0x77613 */
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  bitmap_get_pixel_data_size((void *)(uintptr_t)edi);
  /* cmp eax, ebx -> je 0x776fb */
  display_assert((char *)0x00264158, (char *)0x002641f0, 141, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, ebx);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7775d */
  display_assert((char *)0x00261aa4, (char *)0x002641f0, 261, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], (int16_t)esi -> je 0x77785 */
  display_assert((char *)0x00264224, (char *)0x002641f0, 262, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, 1 -> jg 0x777ab */
  display_assert((char *)0x0026421c, (char *)0x002641f0, 263, 0);
  system_exit(0);
  bitmap_2d_new(0, 0, 0, 0);
  /* relift: cmp dword ptr [edi + 0x2c], esi -> je 0x77991 */
  bitmap_2d_address((void *)(uintptr_t)edi, 0, 0, 0);
  /* relift: cmp word ptr [ebp - 4], (int16_t)edi -> jle 0x778d3 */
  bitmap_2d_address((void *)(uintptr_t)ecx, 0, 0, 0);
  /* test dl, dl -> jne 0x778c9 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 4] -> jl 0x77870 */
  /* test esi, esi -> je 0x77940 */
  /* test edi, edi -> jge 0x778ff */
  /* cmp edi, 0xff -> jle 0x7790c */
  error(0, (char *)0x00264194);
  bitmap_verify((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0x779ed */
  display_assert((char *)0x00261aa4, (char *)0x002641f0, 349, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 1 -> je 0x77a14 */
  display_assert((char *)0x0026424c, (char *)0x002641f0, 350, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 1 -> jg 0x77a3a */
  display_assert((char *)0x0026421c, (char *)0x002641f0, 351, 0);
  system_exit(0);
  bitmap_3d_new(0, 0, 0, 0, 0);
  /* relift: cmp dword ptr [esi + 0x2c], ecx -> je 0x77cb7 */
  bitmap_3d_address((void *)(uintptr_t)esi, 0, 0, 0, 0);
  /* relift: cmp word ptr [ebp - 4], (int16_t)esi -> jle 0x77bce */
  bitmap_3d_address((void *)(uintptr_t)eax, 0, 0, 0, 0);
  /* test dl, dl -> jne 0x77bbb */
  /* relift: cmp (int16_t)esi, word ptr [ebp - 4] -> jl 0x77b58 */
  /* test edi, edi -> je 0x77c51 */
  /* test esi, esi -> jge 0x77c0d */
  /* cmp esi, 0xff -> jle 0x77c1a */
  error(0, (char *)0x00264194);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x77d08 */
  display_assert((char *)0x00261aa4, (char *)0x002641f0, 443, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 2 -> je 0x77d2f */
  display_assert((char *)0x00264274, (char *)0x002641f0, 444, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 1 -> jg 0x77d58 */
  display_assert((char *)0x0026421c, (char *)0x002641f0, 445, 0);
  system_exit(0);
  bitmap_cube_map_new(0, 0, 11);
  /* test eax, eax -> je 0x77e42 */
  bitmap_2d_new(0, 0, 0, 11);
  /* test ebx, ebx -> je 0x77e21 */
  /* test eax, eax -> je 0x77e21 */
  FUN_0007ea60();
  FUN_00077720(0, (void *)(uintptr_t)eax, 0, 0);
  /* test esi, esi -> je 0x77dfc */
  /* test eax, eax -> je 0x77dfc */
  bitmap_cube_map_face_insert();
  bitmap_delete((void *)(uintptr_t)esi);
  /* cmp (int16_t)edi, 6 -> jl 0x77dbe */
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x00264194);
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x00264194);
  bitmap_verify((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x77e98 */
  display_assert((char *)0x00261814, (char *)0x002641f0, 501, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x77fdf */
  /* test (char)eax, 0x41 -> jne 0x77edc */
  floor(0.0f);
  FUN_001d9068();
  bitmap_mipmap_address((void *)0, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)edx);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7802b */
  display_assert((char *)0x00261814, (char *)0x002641f0, 592, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 0 -> je 0x78052 */
  display_assert((char *)0x00264334, (char *)0x002641f0, 593, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x78079 */
  display_assert((char *)0x00264320, (char *)0x002641f0, 594, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 4], (int16_t)edi -> jl 0x78438 */
  /* relift: cmp word ptr [esi + 6], (int16_t)edi -> jl 0x78438 */
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  debug_malloc(ebx, 0, (char *)0x002641f0, 605);
  debug_free((void *)(uintptr_t)edx, (char *)0x002641f0, 677);
  error(0, (char *)0x002642f0);
  crt_fprintf((void *)0x00331050, (char *)0x002642a8);
  crt_fflush((void *)0x00331050);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7849e */
  display_assert((char *)0x00261814, (char *)0x002641f0, 698, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 1 -> je 0x784c5 */
  display_assert((char *)0x00264354, (char *)0x002641f0, 699, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x784ec */
  display_assert((char *)0x00264320, (char *)0x002641f0, 700, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 4], (int16_t)ebx -> jl 0x78b4e */
  /* relift: cmp word ptr [edi + 6], (int16_t)ebx -> jl 0x78b4e */
  /* relift: cmp word ptr [edi + 8], (int16_t)ebx -> jl 0x78b4e */
  bitmap_get_pixel_data_size((void *)(uintptr_t)edi);
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  debug_malloc(esi, 0, (char *)0x002641f0, 711);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)esi, edx);
  debug_free((void *)(uintptr_t)esi, (char *)0x002641f0, 830);
  error(0, (char *)0x002642f0);
  crt_fprintf((void *)0x00331050, (char *)0x002642a8);
  crt_fflush((void *)0x00331050);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x78bb2 */
  display_assert((char *)0x00261814, (char *)0x002641f0, 851, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 2 -> je 0x78bd9 */
  display_assert((char *)0x0026439c, (char *)0x002641f0, 852, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x78c00 */
  display_assert((char *)0x00264320, (char *)0x002641f0, 853, 0);
  system_exit(0);
  crt_fprintf((void *)0x00331050, (char *)0x00264374);
  crt_fflush((void *)0x00331050);
  bitmap_verify((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0x78c69 */
  display_assert((char *)0x00261814, (char *)0x002641f0, 908, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 0 -> je 0x78c90 */
  display_assert((char *)0x00264334, (char *)0x002641f0, 909, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x78cb7 */
  display_assert((char *)0x002643d0, (char *)0x002641f0, 910, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x78cdb */
  display_assert((char *)0x002643c0, (char *)0x002641f0, 911, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 4], (int16_t)eax -> jl 0x790aa */
  /* relift: cmp word ptr [ebx + 6], (int16_t)eax -> jl 0x790aa */
  bitmap_get_pixel_data_size((void *)(uintptr_t)ebx);
  debug_malloc(eax, 0, (char *)0x002641f0, 920);
  bitmap_2d_address((void *)(uintptr_t)ebx, 0, 0, 0);
  bitmap_2d_address((void *)(uintptr_t)ebx, 0, 0, 0);
  bitmap_2d_address((void *)(uintptr_t)ebx, 0, 0, 0);
  /* cmp ecx, 0xff -> jle 0x78e61 */
  /* cmp ecx, 0xff -> jle 0x78f3f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x7ece0 */
void bitmap_cube_map_face_insert(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7ed18 */
  display_assert((char *)0x0026555c, (char *)0x00264a74, 844, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x14], 0 -> je 0x7ed3f */
  display_assert((char *)0x0026553c, (char *)0x00264a74, 845, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 0 -> je 0x7ed66 */
  display_assert((char *)0x00265518, (char *)0x00264a74, 846, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> je 0x7ed93 */
  display_assert((char *)0x00265758, (char *)0x00264a74, 847, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], 8 -> je 0x7edb9 */
  display_assert((char *)0x002654b4, (char *)0x00264a74, 848, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7ede8 */
  display_assert((char *)0x00261974, (char *)0x00264a74, 850, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 2 -> je 0x7ee0f */
  display_assert((char *)0x00264664, (char *)0x00264a74, 851, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7ee1d */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x14] -> jle 0x7ee3d */
  display_assert((char *)0x002618e8, (char *)0x00264a74, 852, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7ee4b */
  /* cmp (int16_t)eax, 6 -> jl 0x7ee6b */
  display_assert((char *)0x00265708, (char *)0x00264a74, 853, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7ee86 */
  /* cmp eax, ecx -> je 0x7eeb5 */
  display_assert((char *)0x002656b0, (char *)0x00264a74, 854, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7eed0 */
  /* cmp eax, ecx -> je 0x7eeff */
  display_assert((char *)0x00265658, (char *)0x00264a74, 855, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xe], 8 -> je 0x7ef25 */
  display_assert((char *)0x002618ac, (char *)0x00264a74, 856, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  bitmap_cube_map_address((void *)(uintptr_t)edi, 0, 0, 0, 0);
  bitmap_mipmap_address((void *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, esi);
  /* test eax, eax -> jle 0x7ef7f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7ef80 */
void FUN_0007ef80(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x7f150 */
void FUN_0007f150(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7f187 */
  display_assert((char *)0x00261814, (char *)0x002657dc, 48, 0);
  system_exit(0);
  /* test edi, edi -> je 0x7f38c */
  /* relift: cmp word ptr [esi + 0xa], 0 -> jne 0x7f38c */
  debug_malloc(eax, 0, (char *)0, 0);
  debug_malloc(ecx, 0, (char *)0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7f1e6 */
  /* cmp (int16_t)eax, 8 -> jle 0x7f203 */
  display_assert((char *)0x00265788, (char *)0x002657dc, 63, 0);
  system_exit(0);
  FUN_001d9068();
  /* test ebx, ebx -> je 0x7f38b */
  /* test eax, eax -> je 0x7f38b */
  /* test ecx, ecx -> jle 0x7f33f */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* test ecx, ecx -> jle 0x7f2f4 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  FUN_0007ef80();
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  FUN_0007ef80();
  debug_free((void *)(uintptr_t)ebx, (char *)0x002657dc, 115);
  debug_free((void *)(uintptr_t)edx, (char *)0x002657dc, 116);
  display_assert((char *)0x00265878, (char *)0x00265880, 36, 0);
  system_exit(0);
  /* cmp esi, ebx -> jne 0x7f3f6 */
  display_assert((char *)0x00263768, (char *)0x00265880, 37, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], (int16_t)ebx -> je 0x7f419 */
  display_assert((char *)0x00264334, (char *)0x00265880, 38, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xc], 0xa -> je 0x7f43d */
  display_assert((char *)0x00265850, (char *)0x00265880, 39, 0);
  system_exit(0);
  FUN_0019a490((void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x7f561 */
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x7f561 */
  csmemset((void *)(uintptr_t)eax, 0, 18);
  file_write();
  /* test (char)eax, (char)eax -> je 0x7f547 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* test edi, edi -> jne 0x7f4f6 */
  display_assert((char *)0x00265848, (char *)0x00265880, 67, 0);
  system_exit(0);
  file_write();
  /* test (char)eax, (char)eax -> je 0x7f52a */
  /* cmp ebx, eax -> jl 0x7f4c5 */
  file_close((void *)(uintptr_t)edi);
  file_close((void *)(uintptr_t)edi);
  file_close((void *)(uintptr_t)edi);
  file_reference_get_name((void *)(uintptr_t)ecx, 13, (char *)(uintptr_t)eax);
  FUN_0006d8e0((char *)(uintptr_t)eax, (char *)0);
  /* test esi, esi -> je 0x7f5d5 */
  TIFFGetField();
  TIFFGetField();
  FUN_00064ee0(0);
  file_reference_get_name((void *)(uintptr_t)edx, 13, (char *)(uintptr_t)ecx);
  FUN_0006d8e0((char *)(uintptr_t)eax, (char *)0);
  bitmap_format_bits_per_pixel(0);
  debug_malloc(eax, 0, (char *)0x00265914, 0);
  /* test esi, esi -> je 0x7f99c */
  TIFFSetField(0, 256, 0);
  TIFFSetField(0, 257, 0);
  TIFFSetField(0, 259, 0);
  TIFFSetField(0, 262, 0);
  TIFFSetField(0, 284, 0);
  TIFFSetField(0, 277, 0);
  TIFFSetField(0, 258, 0);
  TIFFSetField(0, 274, 0);
  bitmap_2d_address((void *)(uintptr_t)edi, 0, 0, 0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, ecx);
  TIFFWriteScanline(0, (void *)(uintptr_t)esi, 0, 0);
  /* test eax, eax -> jl 0x7f96f */
  debug_free((void *)(uintptr_t)esi, (char *)0x00265914, 231);
  FUN_00064ee0(0);
  FUN_00064ee0(0);
  file_exists((void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x7ff1d */
  file_reference_get_name((void *)(uintptr_t)esi, 13, (char *)(uintptr_t)eax);
  FUN_0006d8e0((char *)(uintptr_t)eax, (char *)0);
  TIFFScanlineSize();
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  TIFFGetField();
  TIFFGetField();
  TIFFGetField();
  TIFFGetField();
  /* cmp eax, ecx -> je 0x7fae1 */
  /* relift: cmp word ptr [ebp - 0x24], (int16_t)edx -> jne 0x7fef8 */
  /* cmp (int16_t)eax, 4 -> je 0x7fb35 */
  /* cmp (int16_t)eax, 3 -> je 0x7fb35 */
  /* cmp (int16_t)eax, 2 -> je 0x7fb35 */
  /* cmp (int16_t)eax, (int16_t)edx -> jne 0x7febf */
  /* cmp (int16_t)eax, 0xffff -> je 0x7fb5f */
  /* cmp (int16_t)eax, 0xb -> je 0x7fb5f */
  FUN_00064ee0(0);
  /* relift: cmp word ptr [ebp - 0x20], (int16_t)edx -> jne 0x7fea5 */
  FUN_00108a10();
  FUN_00108a30();
  /* test (int16_t)esi, (int16_t)esi -> jl 0x7fe8b */
  /* cmp (int16_t)esi, 0x7530 -> jg 0x7fe8b */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7fe8b */
  /* cmp (int16_t)eax, 0x7530 -> jg 0x7fe8b */
  bitmap_2d_new(0, 0, 0, 11);
  debug_malloc(edi, 0, (char *)0x00265914, 319);
  /* test ebx, ebx -> je 0x7fe4a */
  /* test (int16_t)esi, (int16_t)esi -> jge 0x7fbff */
  /* cmp ecx, eax -> ja 0x7fc0c */
  FUN_0006f040();
  /* test eax, eax -> jl 0x7fe3e */
  /* cmp eax, 3 -> ja 0x7fe11 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 2] -> jge 0x7fe2e */
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fc6a */
  /* cmp esi, ecx -> ja 0x7fc77 */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fc61 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fcdd */
  /* cmp esi, ecx -> ja 0x7fcea */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fcd4 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 2] -> jge 0x7fe2e */
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fd51 */
  /* cmp esi, ecx -> ja 0x7fd5e */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fd48 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fdcc */
  /* cmp esi, ecx -> ja 0x7fdd9 */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fdc3 */
  display_assert((char *)0, (char *)0x00265914, 406, 0);
  system_exit(0);
  /* test esi, esi -> je 0x7fe5e */
  bitmap_delete((void *)(uintptr_t)esi);
  /* test ebx, ebx -> je 0x7fe75 */
  debug_free((void *)(uintptr_t)ebx, (char *)0x00265914, 422);
  FUN_00064ee0(0);
  FUN_00064ee0(0);
  FUN_00064ee0(0);
  snprintf((char *)0x00334580, 512, (char *)0x00265990);
  FUN_00064ee0(0);
  FUN_00064ee0(0);
  /* test ebx, ebx -> je 0x7ff5b */
  /* test edi, edi -> jne 0x7ff78 */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 33, 0);
  system_exit(0);
  /* test esi, esi -> je 0x7ffeb */
  /* test ebx, ebx -> jne 0x80008 */
  display_assert((char *)0x00265a84, (char *)0x00265a54, 58, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0 -> je 0x8001c */
  /* relift: cmp word ptr [esi + 2], 0 -> je 0x80037 */
  /* relift: cmp word ptr [esi + 4], 0 -> je 0x80052 */
  /* test edi, edi -> je 0x8008e */
  /* test esi, esi -> je 0x8008e */
  /* test eax, eax -> jne 0x800ab */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 79, 0);
  system_exit(0);
  FUN_0007ffe0();
  FUN_0007ff40();
  /* test ebx, ebx -> je 0x8011f */
  /* test eax, eax -> jne 0x8013c */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 95, 0);
  system_exit(0);
  /* cmp eax, 4 -> jb 0x80153 */
  /* cmp edi, ebx -> jne 0x80246 */
  display_assert((char *)0x00265a90, (char *)0x00265a54, 124, 0);
  system_exit(0);
  /* cmp eax, 4 -> jb 0x80250 */
  /* cmp ecx, 8 -> jb 0x80280 */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 79, 0);
  system_exit(0);
  FUN_0007ffe0();
  FUN_0007ff40();
  /* test eax, eax -> je 0x80311 */
  /* test eax, eax -> je 0x80320 */
  /* cmp (char)eax, 3 -> je 0x8036a */
  display_assert((char *)0x00265b18, (char *)0x00265b5c, 77, 0);
  system_exit(0);
  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)edx, (char *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 0);
  encode_packet_group((void *)0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx, 0);
  encode_packet_group((void *)0x002ee588, (void *)(uintptr_t)eax, (char *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax, 0);
  /* test (char)eax, (char)eax -> je 0x8045b */
  create_message(0, 0, eax, 0, 0);
  /* test eax, eax -> je 0x8045d */
  /* test esi, esi -> je 0x80482 */
  /* test ebx, ebx -> je 0x80482 */
  /* test edi, edi -> jne 0x804a2 */
  display_assert((char *)0x00265b90, (char *)0x00265b5c, 162, 0);
  system_exit(0);
  key_agreement_build_message(0, (void *)(uintptr_t)edx, 0, 0);
  /* test esi, esi -> jne 0x8050a */
  display_assert((char *)0x00265ba4, (char *)0x00265b5c, 179, 0);
  system_exit(0);
  key_agreement_build_message(0, (void *)(uintptr_t)ecx, 0, 0);
  /* test edi, edi -> jne 0x80563 */
  display_assert((char *)0x00265ba8, (char *)0x00265b5c, 196, 0);
  system_exit(0);
  /* test (char)eax, 2 -> je 0x80597 */
  /* cmp dl, 3 -> jne 0x80597 */
  /* test (char)ecx, (char)ecx -> je 0x8058e */
  /* cmp (char)ecx, 1 -> jne 0x80597 */
  FUN_00081170();
  FUN_00081250();
  FUN_00080470();
  /* test esi, esi -> je 0x8060c */
  byte_swap_message_header((void *)0, 0);
  send_endpoint((void *)(uintptr_t)edx, (char *)(uintptr_t)esi, 0);
  /* cmp eax, edi -> je 0x80615 */
  /* test edi, edi -> je 0x8064c */
  /* test ebx, ebx -> je 0x8064c */
  /* test eax, eax -> jne 0x8066c */
  display_assert((char *)0x00265bc0, (char *)0x00265b5c, 261, 0);
  system_exit(0);
  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)esi, (void *)0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x807ad */
  FUN_00081300();
  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)esi, (void *)0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x807ad */
  FUN_00081410();
  FUN_00081410();
  FUN_00081250();
  FUN_000804e0();
  /* test esi, esi -> je 0x807ad */
  byte_swap_message_header((void *)0, 0);
  send_endpoint((void *)(uintptr_t)ecx, (char *)(uintptr_t)esi, 0);
  /* cmp eax, edi -> jne 0x807ad */
  FUN_00081300();
  verify_packet_group_definitions((void *)0x002ee588);
  /* cmp eax, edx -> je 0x80809 */
  /* test eax, eax -> jge 0x8080d */
  /* relift: cmp ecx, dword ptr [ebp + 0xc] -> jl 0x807f0 */
  /* test edi, edi -> jne 0x80974 */
  display_assert((char *)0x00265c1c, (char *)0x00265c2c, 31, 0);
  system_exit(0);
  /* test (char)ebx, 1 -> jne 0x80a2b */
  tea_encrypt((void *)(uintptr_t)esi, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx);
  /* test (int16_t)edx, (int16_t)edx -> je 0x809f2 */
  key_message_xor_keystream(0, 0, 0, 0);
  /* cmp (int16_t)ebx, 3 -> jbe 0x80a18 */
  display_assert((char *)0x00265bec, (char *)0x00265c2c, 76, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x80a74 */
  display_assert((char *)0x00265c1c, (char *)0x00265c2c, 88, 0);
  system_exit(0);
  /* test (char)ebx, 1 -> je 0x80b31 */
  tea_decrypt((void *)(uintptr_t)esi, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx);
  /* test (int16_t)edx, (int16_t)edx -> je 0x80af2 */
  key_message_xor_keystream(0, 0, 0, 0);
  /* cmp (int16_t)ebx, 3 -> jbe 0x80b1e */
  display_assert((char *)0x00265bec, (char *)0x00265c2c, 131, 0);
  system_exit(0);
  display_assert((char *)0x00265cc8, (char *)0x00265ccc, 67, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0xfff -> jbe 0x80b91 */
  display_assert((char *)0x00265c94, (char *)0x00265ccc, 69, 0);
  system_exit(0);
  /* cmp (char)ebx, 4 -> jb 0x80bc9 */
  display_assert((char *)0x00265c64, (char *)0x00265ccc, 70, 0);
  system_exit(0);
  display_assert((char *)0x00265bec, (char *)0x00265ccc, 71, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x80c48 */
  display_assert((char *)0x00265d1c, (char *)0x00265ccc, 80, 0);
  system_exit(0);
  /* cmp eax, 1 -> jne 0x80c5f */
  /* test eax, eax -> jne 0x80c72 */
  display_assert((char *)0x00265d00, (char *)0x00265ccc, 94, 0);
  system_exit(0);
  /* cmp ecx, eax -> jge 0x80cf4 */
  display_assert((char *)0x00265d24, (char *)0x00265ccc, 41, 0);
  system_exit(0);
  debug_malloc(edx, 0, (char *)0, 0);
  /* test esi, esi -> je 0x80d20 */
  build_message_header((void *)(uintptr_t)esi, 0, eax, 0);
  /* test eax, eax -> je 0x80d20 */
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)eax, ecx);
  /* cmp ecx, eax -> jbe 0x80d48 */
  display_assert((char *)0x00265d48, (char *)0x00265d54, 61, 0);
  system_exit(0);
  /* cmp eax, 2 -> jae 0x80da1 */
  debug_malloc(eax, edi, (char *)0x00265d54, 71);
  /* cmp esi, edi -> je 0x80e9b */
  FUN_001d9068();
  /* test ebx, ebx -> jbe 0x80e13 */
  /* relift: cmp dword ptr [esi + ecx*4], eax -> ja 0x80e16 */
  /* test ecx, ecx -> jbe 0x80e61 */
  /* relift: cmp dword ptr [edi], 0 -> je 0x80e51 */
  /* test eax, eax -> je 0x80e49 */
  /* test edx, edx -> jne 0x80e49 */
  /* cmp ecx, ebx -> jb 0x80e32 */
  qsort((void *)(uintptr_t)esi, edi, 0, (void *)0x00080d30);
  /* cmp eax, edi -> jae 0x80e9b */
  debug_realloc((void *)(uintptr_t)esi, 0, (char *)0, 0);
  sieve_of_eratosthenes(ecx, (void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x80eef */
  FUN_00081410();
  debug_free((void *)(uintptr_t)esi, (char *)0x00265d54, 137);
  display_assert((char *)0x0025f120, (char *)0x00265d54, 150, 0);
  system_exit(0);
  sieve_of_eratosthenes(65535, (void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x80f8a */
  FUN_00081410();
  debug_free((void *)(uintptr_t)esi, (char *)0x00265d54, 137);
  FUN_000800d0();
  FUN_0007ff40();
  /* test (char)ebx, 1 -> je 0x81020 */
  FUN_000800d0();
  FUN_00080210();
  FUN_000800d0();
  FUN_00080210();
  /* test ebx, ebx -> jne 0x80ff4 */
  /* test eax, eax -> ja 0x8105c */
  /* cmp eax, -1 -> jbe 0x8107c */
  display_assert((char *)0x00265d88, (char *)0x00265da0, 95, 0);
  system_exit(0);
  /* cmp esi, 2 -> ja 0x810b2 */
  display_assert((char *)0x00265de0, (char *)0x00265da0, 112, 0);
  system_exit(0);
  /* cmp ebx, eax -> jb 0x810d6 */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 113, 0);
  system_exit(0);
  /* cmp edi, esi -> jb 0x810f7 */
  display_assert((char *)0x00265dd4, (char *)0x00265da0, 114, 0);
  system_exit(0);
  /* cmp esi, 2 -> ja 0x81138 */
  display_assert((char *)0x00265de0, (char *)0x00265da0, 133, 0);
  system_exit(0);
  /* cmp edi, eax -> jb 0x8115f */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 134, 0);
  system_exit(0);
  FUN_00080eb0();
  FUN_00080eb0();
  FUN_00081410();
  FUN_00081410();
  /* cmp eax, ecx -> jb 0x8120c */
  display_assert((char *)0x00265e08, (char *)0x00265da0, 162, 0);
  system_exit(0);
  /* cmp eax, edx -> jb 0x81236 */
  display_assert((char *)0x00265de4, (char *)0x00265da0, 163, 0);
  system_exit(0);
  FUN_00081090();
  error(0, (char *)0x00265e2c);
  display_assert((char *)0x00265de0, (char *)0x00265da0, 133, 0);
  system_exit(0);
  /* cmp ebx, ecx -> jb 0x8138a */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 134, 0);
  system_exit(0);
  FUN_00080fc0();
  error(0, (char *)0x00265e68);
  /* test (char)eax, (char)eax -> jne 0x81434 */
  crt_time((void *)0);
  FUN_001d9cf9();
  rand();
  FUN_001d9068();
  /* test ebx, ebx -> je 0x8149e */
  /* test edi, edi -> jne 0x814bb */
  display_assert((char *)0x00265ef0, (char *)0x00265f08, 46, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x814db */
  crt_time((void *)0);
  FUN_001d9cf9();
  rand();
  FUN_001d9068();
  FUN_0007ff40();
  /* cmp eax, ecx -> ja 0x8158a */
  /* relift: cmp ecx, dword ptr [esi] -> jae 0x8158a */
  display_assert((char *)0x00265ed4, (char *)0x00265f08, 58, 0);
  system_exit(0);
  /* relift: cmp edx, dword ptr [ebx + 4] -> jb 0x815b7 */
  /* relift: cmp eax, dword ptr [ebx] -> jbe 0x815b7 */
  display_assert((char *)0x00265eb8, (char *)0x00265f08, 59, 0);
  system_exit(0);
  /* test dl, dl -> je 0x815d6 */
  /* cmp ecx, 0x20 -> jl 0x815c4 */
  /* relift: cmp byte ptr [ecx], 0 -> je 0x81612 */
  /* cmp ecx, 0x334fb4 -> jl 0x81600 */
  /* test edi, edi -> jne 0x8165a */
  display_assert((char *)0x00265f50, (char *)0x00265f5c, 107, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x8167e */
  display_assert((char *)0x00265f3c, (char *)0x00265f5c, 108, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x81695 */
  /* cmp eax, 0x20 -> jl 0x81682 */
  /* test esi, esi -> je 0x81714 */
  CreateThread((void *)0, 16384, (void *)(uintptr_t)edi, (void *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  /* test dl, 2 -> je 0x816d6 */
  /* test dl, 4 -> je 0x816e0 */
  SetThreadPriority(0, 0);
  /* test eax, eax -> je 0x81701 */
  ResumeThread(0);
  /* cmp eax, -1 -> je 0x81701 */
  CloseHandle(0);
  /* test esi, esi -> jne 0x8174e */
  display_assert((char *)0x00265f3c, (char *)0x00265f5c, 152, 0);
  system_exit(0);
  GetExitCodeThread(0, (void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x81769 */
  /* test esi, esi -> jne 0x8179b */
  display_assert((char *)0x00265f3c, (char *)0x00265f5c, 168, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x817c2 */
  display_assert((char *)0x00265f8c, (char *)0x00265f5c, 169, 0);
  system_exit(0);
  CloseHandle(0);
  display_assert((char *)0x00265fb4, (char *)0x00265f5c, 184, 0);
  system_exit(0);
  FUN_000815f0();
  /* test esi, esi -> je 0x8185c */
  /* mem[0x00334988] = eax */
  snprintf((char *)(uintptr_t)edi, 32, (char *)0);
  CreateMutexA();
  /* test esi, esi -> jne 0x8189e */
  display_assert((char *)0x00265fb4, (char *)0x00265f5c, 211, 0);
  system_exit(0);
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x818b5 */
  /* cmp eax, 0x80 -> jne 0x818bb */
  /* test esi, esi -> jne 0x818fb */
  display_assert((char *)0x00265fb4, (char *)0x00265f5c, 230, 0);
  system_exit(0);
  ReleaseMutex(0);
  /* test esi, esi -> jne 0x8193b */
  display_assert((char *)0x00265fb4, (char *)0x00265f5c, 240, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x81962 */
  display_assert((char *)0x00265fc4, (char *)0x00265f5c, 241, 0);
  system_exit(0);
  CloseHandle(0);
  /* test (char)eax, (char)eax -> jne 0x819a9 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 30, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x819ce */
  display_assert((char *)0x00265fdc, (char *)0x00265ffc, 31, 0);
  system_exit(0);
  debug_malloc(24, 0, (char *)0x00265ffc, 33);
  /* test eax, eax -> je 0x81a14 */
  /* test (char)eax, (char)eax -> jne 0x81a49 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 47, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x81a6e */
  display_assert((char *)0x00265fdc, (char *)0x00265ffc, 48, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)esi, (char *)0x00265ffc, 50);
  display_assert((char *)0x00266090, (char *)0x00265ffc, 59, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x81add */
  display_assert((char *)0x0026608c, (char *)0x00265ffc, 60, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x81b03 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 61, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81b27 */
  display_assert((char *)0x00266060, (char *)0x00265ffc, 63, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0x10], 4 -> je 0x81b4b */
  display_assert((char *)0x00266034, (char *)0x00265ffc, 64, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)esi, (void *)(uintptr_t)edi, 0);
  /* test eax, eax -> jne 0x81b80 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0x12] -> jne 0x81b80 */
  /* test esi, esi -> jne 0x81bb8 */
  display_assert((char *)0x002660f8, (char *)0x00265ffc, 74, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81bdc */
  display_assert((char *)0x002660cc, (char *)0x00265ffc, 75, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 4 -> jne 0x81c24 */
  snprintf((char *)0x00334f90, 256, (char *)0x002660b8);
  /* cmp (int16_t)eax, 0x10 -> jne 0x81c6d */
  snprintf((char *)0x00334f90, 256, (char *)0x00266094);
  /* cmp eax, 0x17 -> ja 0x81d42 */
  /* test esi, esi -> jne 0x81de1 */
  display_assert((char *)0x00266450, (char *)0x00266458, 57, 0);
  system_exit(0);
  /* cmp eax, ecx -> jle 0x81df6 */
  /* mem[0x005ab210] = ecx */
  /* mem[0x005ab214] = edx */
  /* mem[0x005ab218] = ecx */
  /* mem[0x005ab21c] = edx */
  /* mem[0x005ab220] = ecx */
  /* mem[0x005ab224] = edx */
  /* relift: FUN_00222de0(0x005ab220, 0x005ab210); */
  /* test eax, eax -> je 0x81e76 */
  display_assert((char *)0x0026649c, (char *)0x00266458, 92, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x81ea6 */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  /* test esi, esi -> jne 0x81eeb */
  display_assert((char *)0x002664e0, (char *)0x00266458, 151, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], 8 -> je 0x81f11 */
  display_assert((char *)0x002664c0, (char *)0x00266458, 152, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)0x005ab228, 0);
  display_assert((char *)0x002664ec, (char *)0x00266458, 163, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x81f83 */
  display_assert((char *)0x002664e0, (char *)0x00266458, 164, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)esi, (void *)(uintptr_t)edi, 0);
  /* test esi, esi -> jne 0x81fcb */
  display_assert((char *)0x002664ec, (char *)0x00266458, 175, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], 8 -> je 0x81ff1 */
  display_assert((char *)0x002664c0, (char *)0x00266458, 176, 0);
  system_exit(0);
  transport_nonce_is_equal();
  /* test (char)eax, (char)eax -> je 0x82058 */
  /* test eax, eax -> jg 0x8203f */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  /* test eax, eax -> jg 0x820b9 */
  display_assert((char *)0x002664a8, (char *)0x00266458, 224, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x820fc */
  display_assert((char *)0x002664a8, (char *)0x00266458, 231, 0);
  system_exit(0);
  XNetGetEthernetLinkStatus();
  error(0, (char *)0x00266534);
  crt_fopen((char *)0x0026651c, (char *)0x002658a4);
  /* cmp esi, ebx -> je 0x82232 */
  error(0, (char *)0x002664f8);
  crt_fclose((void *)(uintptr_t)esi);
  /* relift: FUN_002231f8(0); */
  /* test eax, eax -> jne 0x822a8 */
  /* relift: FUN_00223206(0, 0); */
  /* cmp (int16_t)esi, (int16_t)ebx -> je 0x82271 */
  /* relift: FUN_002232ed(0, 0); */
  winsock_error_report(0);
  system_milliseconds();
  /* relift: FUN_00222ecf(0x005ab230); */
  system_milliseconds();
  /* cmp eax, edi -> ja 0x8229e */
  /* cmp esi, ebx -> je 0x82280 */
  /* cmp esi, 1 -> jne 0x822b4 */
  /* relift: FUN_002232f5(0, 0); */
  /* relift: FUN_002232ed(0, 0); */
  /* relift: FUN_00222e0e(0x005ab228, 0); */
  /* test (char)eax, (char)eax -> je 0x822f2 */
  /* relift: FUN_002232f5(0, 0); */
  /* relift: FUN_002232ed(0, 0); */
  XNetGetEthernetLinkStatus();
  /* test (char)eax, (char)eax -> jne 0x8233c */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 406, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jg 0x82367 */
  display_assert((char *)0x002665c0, (char *)0x00266458, 407, 0);
  system_exit(0);
  debug_malloc(280, 0, (char *)0x00266458, 409);
  /* test esi, esi -> je 0x823df */
  /* cmp (int16_t)edi, 0x40 -> jg 0x823ec */
  debug_malloc(eax, 0, (char *)0x00266458, 0);
  debug_free((void *)(uintptr_t)esi, (char *)0x00266458, 432);
  /* test esi, esi -> je 0x82425 */
  /* test eax, eax -> jne 0x82445 */
  display_assert((char *)0x002665d4, (char *)0x00266458, 443, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x8246e */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 444, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)eax, (char *)0x00266458, 446);
  debug_free((void *)(uintptr_t)esi, (char *)0x00266458, 447);
  /* test ecx, ecx -> je 0x824c5 */
  /* test ecx, ecx -> jne 0x824c5 */
  /* test esi, esi -> jne 0x82504 */
  display_assert((char *)0x00266450, (char *)0x00266458, 477, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x8252d */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 478, 0);
  system_exit(0);
  qsort((void *)(uintptr_t)edx, ecx, 0, (void *)0);
  /* test edx, edx -> jne 0x82599 */
  /* relift: cmp dword ptr [eax + edx*4], 0 -> je 0x82580 */
  /* test ebx, ebx -> jbe 0x825d2 */
  /* relift: cmp dword ptr [ecx], edx -> je 0x825d2 */
  /* relift: cmp eax, dword ptr [esi] -> jb 0x825c6 */
  /* cmp eax, ebx -> jne 0x825ec */
  /* cmp ebx, 0x40 -> jae 0x825ec */
  /* cmp edi, eax -> jle 0x825b0 */
  /* test eax, eax -> jl 0x82638 */
  /* cmp edi, eax -> jle 0x82620 */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)esi, 260);
  /* relift: FUN_002251b8(0); */
  /* test eax, eax -> jle 0x826cc */
  /* test eax, eax -> jl 0x826b9 */
  /* cmp eax, -1 -> je 0x826c1 */
  /* relift: FUN_002235f3(0, 0); */
  /* test eax, eax -> je 0x826ae */
  /* cmp edi, eax -> jle 0x82680 */
  /* cmp eax, -1 -> jne 0x826ec */
  GetLastError();
  winsock_error_report(0);
  /* test esi, esi -> jne 0x82734 */
  display_assert((char *)0x002665ec, (char *)0x00266458, 559, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x8275d */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 560, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x8277e */
  display_assert((char *)0x00266450, (char *)0x00266458, 57, 0);
  system_exit(0);
  /* cmp eax, ecx -> jg 0x82846 */
  /* test edi, edi -> jl 0x82846 */
  /* test ebx, ebx -> jbe 0x827cf */
  /* relift: cmp dword ptr [ecx], edx -> je 0x827cf */
  /* relift: cmp eax, dword ptr [esi] -> jb 0x827c3 */
  /* cmp eax, ebx -> jne 0x82826 */
  /* cmp ebx, 0x40 -> jae 0x82826 */
  /* test ebx, ebx -> jbe 0x8280c */
  /* relift: cmp dword ptr [ecx], edx -> je 0x8280c */
  /* relift: cmp eax, dword ptr [esi] -> jb 0x82800 */
  /* cmp eax, ebx -> jne 0x82826 */
  /* cmp ebx, 0x40 -> jae 0x82826 */
  /* test ebx, ebx -> je 0x82866 */
  /* test esi, esi -> jne 0x82886 */
  display_assert((char *)0x002665ec, (char *)0x00266458, 597, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x828af */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 598, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x828d2 */
  /* relift: cmp dword ptr [eax], ebx -> je 0x828dc */
  /* cmp edi, ecx -> jle 0x828c0 */
  /* test ebx, ebx -> jbe 0x82919 */
  /* relift: cmp dword ptr [ecx], edx -> je 0x828fe */
  /* relift: cmp eax, dword ptr [esi] -> jb 0x828f0 */
  /* cmp eax, ebx -> jae 0x82917 */
  /* cmp eax, edx -> jb 0x82907 */
  /* test esi, esi -> jne 0x8296b */
  display_assert((char *)0x00266450, (char *)0x00266458, 621, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x82994 */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 622, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x829de */
  display_assert((char *)0x00266450, (char *)0x00266458, 634, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x82a07 */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 635, 0);
  system_exit(0);
  /* relift: cmp ecx, dword ptr [esi + 0x10c] -> jg 0x82a29 */
  /* test esi, esi -> jne 0x82a5b */
  display_assert((char *)0x00266450, (char *)0x00266458, 649, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x82a84 */
  display_assert((char *)0x00265fe4, (char *)0x00266458, 650, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x82ade */
  /* test eax, eax -> jg 0x82ac5 */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  /* test eax, eax -> je 0x82b04 */
  display_assert((char *)0x002665f8, (char *)0x00266458, 121, 0);
  system_exit(0);
  /* relift: FUN_00222da0(0, 0); */
  FUN_00081e00();
  /* test (char)eax, (char)eax -> je 0x82b78 */
  /* test eax, eax -> jg 0x82b5f */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  /* test eax, eax -> jg 0x82b9e */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  csmemset((void *)0x005ab204, 0, 0);
  /* test (char)eax, (char)eax -> je 0x82c1c */
  /* test eax, eax -> jg 0x82c03 */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  FUN_00081e00();
  /* relift: FUN_00222e31(0, 0, 0); */
  /* test ecx, ecx -> je 0x82cb6 */
  /* cmp eax, 0x40 -> jge 0x82cd4 */
  /* test ecx, ecx -> jne 0x82ca0 */
  /* cmp eax, 0x40 -> jge 0x82cd4 */
  /* test esi, esi -> jne 0x82d11 */
  display_assert((char *)0x00266610, (char *)0x00266618, 79, 0);
  system_exit(0);
  /* relift: cmp dword ptr [eax*8 + 0x3350a0], esi -> je 0x82d23 */
  /* cmp eax, 0x40 -> jl 0x82d13 */
  /* test eax, eax -> je 0x82d56 */
  /* test (char)ecx, (char)ecx -> je 0x82d56 */
  thread_close((void *)(uintptr_t)eax);
  /* cmp esi, 0x3352a0 -> jl 0x82d36 */
  /* test (char)eax, (char)eax -> jne 0x82da0 */
  display_assert((char *)0x00265fe4, (char *)0x00266618, 206, 0);
  system_exit(0);
  endpoint_pool_cleanup();
  /* cmp ebx, 0x11 -> je 0x82db2 */
  /* cmp ebx, 0x12 -> jne 0x82de0 */
  debug_malloc(0, esi, (char *)0x00266618, 212);
  /* cmp eax, esi -> je 0x82de2 */
  /* test esi, esi -> jne 0x82e1b */
  display_assert((char *)0x00266658, (char *)0x00266618, 300, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x82e44 */
  display_assert((char *)0x00265fe4, (char *)0x00266618, 301, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x82e6b */
  /* test edi, edi -> jg 0x82e8b */
  display_assert((char *)0x0026665c, (char *)0x00266618, 802, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x82eb4 */
  display_assert((char *)0x00265fe4, (char *)0x00266618, 803, 0);
  system_exit(0);
  xnet_recv(0, (void *)(uintptr_t)ebx, 0, 0);
  /* cmp eax, -1 -> jne 0x82f19 */
  GetLastError();
  /* cmp eax, 0x19 -> ja 0x82f02 */
  /* test eax, eax -> jne 0x82f22 */
  /* test ebx, ebx -> je 0x82f6b */
  /* test edi, edi -> jg 0x82f8b */
  display_assert((char *)0x0026665c, (char *)0x00266618, 848, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x82fb4 */
  display_assert((char *)0x00265fe4, (char *)0x00266618, 849, 0);
  system_exit(0);
  xnet_send(0, (char *)(uintptr_t)ebx, 0, 0);
  /* cmp eax, -1 -> jne 0x8300b */
  GetLastError();
  /* cmp eax, 0x19 -> ja 0x83002 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x887e0 */
void FUN_000887e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  player_control_get_unit_camera_info(ecx, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8886b */
  /* test (char)eax, 0x41 -> jne 0x8885a */
  director_set_local_player_context(eax);
  /* test (char)eax, 0x41 -> je 0x8888c */
  /* cmp eax, -1 -> je 0x888c6 */
  angles_to_vector((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx);
  observer_up_from_forward((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  object_get_root_location(0, (float *)(uintptr_t)eax, (float *)0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)eax, (float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x88c40 */
void first_person_camera_new(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x88c68 */
  display_assert((char *)0x00266e9c, (char *)0x0026720c, 24, 0);
  system_exit(0);

  (void)esi;
}

/* 0x88c80 */
void FUN_00088c80(void)
{
  int eax = 0;
  int ebx = 0;

  object_get_and_verify_type(0, 0);
  unit_set_seat_state(0, (float *)(uintptr_t)ebx);
  /* cmp eax, -1 -> je 0x88d47 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x88d47 */
  tag_get('ihev', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  object_get_markers_by_string_id(0, (void *)0x00267238, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x88d47 */

  (void)eax;
  (void)ebx;
}

/* 0x88d50 */
void first_person_camera_for_unit_and_vector(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  observer_up_from_forward((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x88dde */
  display_assert((char *)0x00267248, (char *)0x0026720c, 82, 0);
  system_exit(0);
  /* cmp ebx, -1 -> je 0x88f19 */
  object_get_and_verify_type(0, 0);
  unit_set_seat_state(0, (float *)(uintptr_t)eax);
  object_get_root_location(0, (float *)(uintptr_t)ecx, (float *)0);
  /* cmp eax, -1 -> je 0x88f13 */
  object_try_and_get_and_verify_type(0, 0);
  /* test ebx, ebx -> je 0x88f13 */
  tag_get('ihev', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  object_get_markers_by_string_id(0, (void *)0x00267238, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x88f13 */
  matrix4x3_from_forward_up_position((void *)(uintptr_t)edx, (float *)(uintptr_t)ebx, (float *)0, (float *)0);
  real_matrix4x3_transform_point((void *)(uintptr_t)eax, (void *)(uintptr_t)edi, (void *)(uintptr_t)edi);
  observer_up_from_forward((float *)(uintptr_t)edi, (float *)(uintptr_t)ebx);
  matrix_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (float *)(uintptr_t)edi);
  matrix_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ebx);
  /* test (char)ebx, 1 -> je 0x89237 */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  /* test (char)eax, 1 -> jne 0x8917d */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  /* relift: tail-call first_person_camera_for_unit_and_vector(); */
  player_control_get_unit_index(eax);
  display_assert((char *)0x00266e9c, (char *)0x0026720c, 157, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x892db */
  display_assert((char *)0x0025f120, (char *)0x0026720c, 158, 0);
  system_exit(0);
  player_control_get_facing_direction(edx, (float *)(uintptr_t)ecx);
  /* relift: tail-call first_person_camera_for_unit_and_vector(); */
  player_control_get_field_of_view(eax);
  vector_to_angles((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x893cd */
  display_assert((char *)0x00266e9c, (char *)0x00267284, 41, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x893f1 */
  display_assert((char *)0x002671f8, (char *)0x00267284, 42, 0);
  system_exit(0);
  /* cmp esi, ecx -> jne 0x89419 */
  display_assert((char *)0x0025f120, (char *)0x00267284, 43, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x89467 */
  /* test (char)eax, 0x41 -> jne 0x8945b */
  /* relift: cmp word ptr [0x325716], (int16_t)ecx -> jle 0x89480 */
  angles_to_vector((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax);
  observer_up_from_forward((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax);
  rotate_vector3d_by_sincos((float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, 0.0f, 0.0f);
  /* test (char)ecx, (char)ecx -> je 0x89518 */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)ebx, (float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x89790 */
  /* cmp ecx, 0x7f800000 -> je 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  /* test (char)eax, 1 -> jne 0x89790 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp esi, ebx -> jne 0x8987b */
  display_assert((char *)0x00266e9c, (char *)0x002672ac, 19, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  /* cmp eax, -1 -> je 0x89910 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x89910 */
  tag_get('ihev', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, 0x15 -> je 0x89910 */
  /* test eax, eax -> jne 0x89925 */
  tag_get('tinu', 0);
  /* test (char)eax, 0x41 -> je 0x89973 */
  display_assert((char *)0x002672f4, (char *)0x0025ed80, 1508, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x89996 */
  /* test (char)eax, 1 -> je 0x899b6 */
  display_assert((char *)0x002672d8, (char *)0x0025ed80, 1509, 0);
  system_exit(0);
  FUN_00089940();
  FUN_00089940();
  FUN_00089940();
  /* test eax, eax -> je 0x89ae3 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test eax, eax -> je 0x89ae3 */
  /* cmp eax, -1 -> jne 0x89afd */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get(0x7472616b, 0);
  FUN_001d9068();
  display_assert((char *)0x00267300, (char *)0x002672ac, 86, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x89b8e */
  /* cmp ebx, edx -> jg 0x89b88 */
  /* cmp ecx, ebx -> jle 0x89b8e */
  /* test (int16_t)edi, (int16_t)edi -> jg 0x89b76 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 60);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 60);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 60);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 60);
  FUN_00089a20();
  object_get_and_verify_type(0, 0);
  FUN_000898b0();
  unit_set_seat_state(0, (float *)(uintptr_t)edi);
  FUN_001da0cc();
  camera_track_splut();
  /* test edi, edi -> jne 0x89d00 */
  display_assert((char *)0x00266e9c, (char *)0x002672ac, 138, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x89d27 */
  display_assert((char *)0x0025f120, (char *)0x002672ac, 139, 0);
  system_exit(0);
  player_control_get_unit_camera_info(ecx, (void *)(uintptr_t)eax);
  /* relift: cmp eax, dword ptr [edi + 8] -> jne 0x89d7c */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0xc] -> je 0x89d83 */
  object_get_and_verify_type(0, 0);
  /* test (char)ecx, 3 -> jne 0x89daf */
  /* relift: cmp (char)ecx, byte ptr [edi + 2] -> je 0x89ddb */
  /* test (char)eax, 0x41 -> jne 0x89dd2 */
  /* test (char)eax, (char)eax -> je 0x89e1b */
  /* test (char)eax, 0x41 -> jne 0x89e13 */
  player_control_get_facing_angles(eax);
  /* test (char)eax, 0x41 -> jne 0x89e9b */
  angles_to_vector((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x89f08 */
  display_assert((char *)0x00267330, (char *)0x002672ac, 212, 0);
  system_exit(0);
  camera_track_splut();
  /* test (char)eax, 0x41 -> je 0x89fa5 */
  object_get_root_location(0, (float *)(uintptr_t)eax, (float *)0);
  observer_up_from_forward((float *)(uintptr_t)eax, (float *)(uintptr_t)ebx);
  /* test (char)eax, 1 -> je 0x8a2f5 */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edx, (float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  /* test (char)eax, 1 -> jne 0x8a237 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x8a30b */
  /* cmp (int16_t)esi, 4 -> jl 0x8a328 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, 104);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x8a49b */
  /* cmp (int16_t)edi, 4 -> jl 0x8a4b8 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  observer_result_initialize((void *)0);
  /* cmp (int16_t)edi, 4 -> jl 0x8a490 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x8a4fc */
  /* cmp (int16_t)esi, 4 -> jl 0x8a519 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  scenario_get();
  /* relift: cmp ecx, dword ptr [eax + 0x134] -> jl 0x8a569 */
  display_assert((char *)0x002673d0, (char *)0x002673a8, 301, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x8a583 */
  /* cmp (int16_t)esi, 4 -> jl 0x8a5a0 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* cmp (int16_t)ecx, 5 -> jl 0x8a5c2 */
  local_player_get_player_index(esi);
  /* cmp eax, -1 -> je 0x8a643 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x8a619 */
  /* cmp (int16_t)esi, 4 -> jl 0x8a636 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  scenario_location_from_point((void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)esi, 4 -> jl 0x8a600 */
  /* cmp (int16_t)esi, 4 -> jl 0x8a694 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x8a7d4 */
  /* test (char)eax, 0x41 -> je 0x8a78e */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x1c] -> je 0x8a7af */
  /* cmp (int16_t)ecx, 5 -> jl 0x8a795 */
  csmemset((void *)(uintptr_t)esi, 0, edx);
  /* cmp (int16_t)esi, 4 -> jl 0x8a864 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x8a975 */
  /* relift: cmp (int16_t)ecx, word ptr [esi] -> jl 0x8a920 */
  /* relift: test byte ptr [edx], 2 -> jne 0x8a98b */
  /* test (char)eax, 8 -> je 0x8a99f */
  csmemset((void *)(uintptr_t)ebx, 0, eax);
  /* test ecx, ecx -> je 0x8a9c7 */
  /* relift: cmp word ptr [esi], (int16_t)ecx -> jle 0x8a9c7 */
  /* relift: cmp (int16_t)ecx, word ptr [esi] -> jl 0x8a9b0 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x8aa43 */
  /* cmp (int16_t)esi, 4 -> jl 0x8aa60 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  observer_result_initialize((void *)0);
  normalize3d((float *)0);
  normalize3d((float *)(uintptr_t)ecx);
  rotate_vector3d_by_sincos((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, 0.0f);
  rotate_vector3d_by_sincos((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f);
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x8abd5 */
  display_assert((char *)0x00253440, (char *)0x002673a8, 1204, 0);
  system_exit(0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x8ac2e */
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x8ac58 */
  display_assert((char *)0x00253418, (char *)0x002673a8, 1210, 0);
  system_exit(0);
  FUN_0008ab90((float *)0, 0, (float *)0, (float *)0);
  /* cmp (int16_t)esi, 4 -> jl 0x8ace1 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* test esi, esi -> je 0x8af60 */
  /* relift: test byte ptr [esi], 1 -> je 0x8b01d */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  real_vector3d_valid((float *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  /* test (char)eax, 1 -> jne 0x8af60 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, 0);
  /* cmp (int16_t)esi, 4 -> jl 0x8b094 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* relift: test byte ptr [esi], 1 -> je 0x8b3e2 */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  /* test (char)eax, 1 -> jne 0x8b322 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: test byte ptr [eax], 1 -> je 0x8b45f */
  /* test (char)eax, 1 -> je 0x8b410 */
  /* test (char)eax, 2 -> jne 0x8b442 */
  /* relift: test byte ptr [ecx], 8 -> jne 0x8b43d */
  /* test (char)eax, 0x41 -> jne 0x8b40a */
  /* cmp (int16_t)esi, 4 -> jl 0x8b4a4 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* relift: test byte ptr [eax], 1 -> je 0x8b835 */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  /* test (char)eax, 1 -> jne 0x8b774 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 8], 1 -> je 0x8b9b8 */
  /* test (char)eax, 0x41 -> jne 0x8b9b8 */
  /* test (int16_t)edx, (int16_t)edx -> jne 0x8b99d */
  /* cmp (int16_t)esi, 4 -> jl 0x8ba47 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  csprintf((char *)0x005ab100, (char *)0x0025eb8c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x8bb7e */
  /* relift: test byte ptr [edi + 8], 1 -> je 0x8bb7e */
  /* test (char)eax, 0x41 -> jne 0x8bc10 */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 0x2ee6b8] -> jl 0x8bbc0 */
  /* relift: cmp word ptr [esi + 0x2ee6b8], 0 -> jle 0x8bc41 */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 0x2ee6b8] -> jl 0x8bc20 */
  /* relift: cmp word ptr [ebp - 0x1c], 4 -> jge 0x8bc78 */
  /* relift: cmp word ptr [esi + 0x2ee6b8], (int16_t)ecx -> jle 0x8bd28 */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 0x2ee6b8] -> jl 0x8bc57 */
  rotate_vector3d_by_sincos((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, 0.0f);
  rotate_vector3d_by_sincos((float *)(uintptr_t)edx, (float *)0, 0.0f, 0.0f);
  /* cmp eax, 0x7f800000 -> je 0x8be9c */
  /* cmp ecx, 0x7f800000 -> je 0x8be9c */
  /* cmp edx, 0x7f800000 -> je 0x8be9c */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x8c0a6 */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)eax, (float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x8c11c */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  matrix_from_forward_and_up((float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (float *)(uintptr_t)esi);
  matrix_from_forward_and_up((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ebx);
  quaternion_to_angle_and_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  scenario_location_from_point((void *)(uintptr_t)eax, (void *)(uintptr_t)esi);
  FUN_0018f3e0((void *)(uintptr_t)ecx, (void *)(uintptr_t)esi, (void *)0);
  FUN_0008ab90((float *)0, 0, (float *)0, (float *)0);
  FUN_0008ab90((float *)0, 0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x8c2c8 */
  /* test ebx, ebx -> je 0x8c422 */
  FUN_0008ab90((float *)0, 0, (float *)0, (float *)0);
  /* test (char)ecx, (char)ecx -> je 0x8c37a */
  /* test (char)eax, 1 -> je 0x8c3cc */
  FUN_0008c030((float *)(uintptr_t)eax, (float *)(uintptr_t)eax, (float *)0, (float *)0, (float *)0);
  /* cmp (int16_t)esi, 4 -> jl 0x8c4e4 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x8c542 */
  /* test (char)eax, 1 -> jne 0x8c5ef */
  /* test (char)eax, 1 -> jne 0x8c5ef */
  /* test (char)eax, 1 -> jne 0x8c5ef */
  display_assert((char *)0x002675e8, (char *)0x002673a8, 943, 0);
  system_exit(0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x8c697 */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x8c75a */
  /* test (char)eax, 1 -> jne 0x8c75a */
  /* test (char)eax, 1 -> jne 0x8c75a */
  display_assert((char *)0x00267580, (char *)0x002673a8, 945, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x8c7ae */
  display_assert((char *)0x00267558, (char *)0x002673a8, 946, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x8c804 */
  /* test (char)eax, 0x41 -> jne 0x8c840 */
  /* test (char)eax, 0x41 -> jne 0x8c870 */
  /* test (char)eax, 0x41 -> jne 0x8c8a0 */
  /* test (char)eax, 0x41 -> jne 0x8c8d0 */
  FUN_0008c150((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0.0f, (float *)0, (float *)0);
  scenario_location_from_point((void *)0, (void *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x8c9eb */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x84] -> je 0x8c9dc */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  predicted_resources_precache((void *)(uintptr_t)eax);
  FUN_0018f510((void *)(uintptr_t)edx, (void *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x8cbe7 */
  /* test (char)eax, 1 -> jne 0x8cad4 */
  /* test (char)eax, 1 -> jne 0x8cad4 */
  /* test (char)eax, 1 -> jne 0x8cad4 */
  display_assert((char *)0x00267520, (char *)0x002673a8, 1055, 0);
  system_exit(0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x8cb70 */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x8cbaf */
  display_assert((char *)0x002674f0, (char *)0x002673a8, 1057, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x8cc10 */
  /* test (char)eax, 0x41 -> jne 0x8cc46 */
  /* test (char)eax, 0x41 -> jne 0x8cc7c */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x8ccfb */
  /* cmp (int16_t)esi, 4 -> jl 0x8cd18 */
  display_assert((char *)0x00266fc0, (char *)0x002673a8, 114, 0);
  system_exit(0);
  FUN_0008c440((void *)0, (void *)0, (void *)0);
  /* cmp (int16_t)esi, 4 -> jl 0x8cd6c */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xb3df0 */
void FUN_000b3df0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edi, 0xe -> ja 0xb4082 */
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 0, (wchar_t *)0x0026dafc);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026dacc);
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 0, (wchar_t *)0x0026da9c);
  datum_get((void *)(uintptr_t)eax, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 0, (wchar_t *)0x0026da50);
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 0, (wchar_t *)0x0026d9e0);
  datum_get((void *)(uintptr_t)edx, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 0, (wchar_t *)0x0026d9b0);
  game_engine_get_variant();
  /* relift: cmp dword ptr [eax + 0x4c], 2 -> jne 0xb3ff7 */
  /* cmp (int16_t)esi, 1 -> jne 0xb3fbf */
  game_engine_get_place(0, 0);
  game_engine_place_to_string(0);
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 0, (wchar_t *)0x0026d99c);
  game_engine_get_place(0, 0);
  game_engine_place_to_string(0);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026d984);
  game_engine_get_variant();
  /* cmp ecx, edx -> jle 0xb403c */
  game_engine_get_place(0, 0);
  game_engine_place_to_string(0);
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 0, (wchar_t *)0x0026d958);
  game_engine_get_variant();
  game_engine_get_place(0, 0);
  game_engine_place_to_string(0);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026d938);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test edx, ecx -> jne 0xb4145 */
  display_assert((char *)0x0026db24, (char *)0x0026d8f4, 1062, 0);
  system_exit(0);
  /* test edx, esi -> je 0xb4161 */
  /* cmp ecx, 0x20 -> jl 0xb4155 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ecx, 1 -> jne 0xb419a */
  /* test edx, ebx -> je 0xb41c4 */
  /* test edx, ebx -> je 0xb41d3 */
  /* test edx, ebx -> je 0xb41e1 */
  /* test edx, ebx -> je 0xb41f0 */
  /* test edx, ebx -> je 0xb41ff */
  /* test edx, ebx -> je 0xb420e */
  /* test edx, ebx -> je 0xb421d */
  /* test edx, ebx -> je 0xb422c */
  /* cmp ecx, 0x20 -> jl 0xb41b5 */
  datum_get((void *)(uintptr_t)ecx, 0);
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026c118);
  game_engine_get_variant();
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026db68);
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026db5c);
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026c118);
  FUN_000a95a0();
  /* test (char)eax, (char)eax -> je 0xb439e */
  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_000b3c60(0);
  FUN_000b3c60(0);
  /* test (char)ebx, (char)ebx -> jne 0xb438c */
  /* test (char)eax, (char)eax -> je 0xb4383 */
  display_assert((char *)0x0026db74, (char *)0x0026d8f4, 1165, 0);
  system_exit(0);
  FUN_000ae250(0);
  FUN_000ae250(0);
  global_scenario_get();
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> jle 0xb4473 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 148);
  /* relift: cmp word ptr [eax + 0x10], 4 -> jne 0xb446c */
  /* test ebx, ebx -> jle 0xb442d */
  /* relift: cmp esi, dword ptr [edx + ecx*4] -> je 0xb446c */
  /* cmp ecx, ebx -> jl 0xb4420 */
  /* test ecx, ecx -> je 0xb447c */
  /* cmp esi, eax -> jl 0xb4400 */
  global_scenario_get();
  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0xb4529 */
  /* cmp eax, -1 -> je 0xb44ec */
  object_get_and_verify_type(0, 0);
  /* cmp ebx, 8 -> je 0xb4529 */
  /* test eax, eax -> je 0xb4501 */
  FUN_000b43b0();
  /* cmp eax, -1 -> je 0xb4529 */
  data_iterator_next((void *)0);
  /* test eax, eax -> jne 0xb44d7 */
  /* test ebx, ebx -> jle 0xb45b9 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 148);
  FUN_000b3770(0);
  /* cmp eax, -1 -> je 0xb45b4 */
  object_placement_data_new((void *)(uintptr_t)eax, 0, 0);
  vector3d_from_angle((float *)(uintptr_t)eax, 0.0f);
  object_new((void *)(uintptr_t)ecx);
  /* cmp edi, ebx -> jl 0xb4540 */
  global_scenario_get();
  /* test eax, edx -> je 0xb45ec */
  /* cmp ecx, 0x20 -> jl 0xb45e0 */
  /* relift: cmp dword ptr [ebp + 8], edi -> je 0xb45f8 */
  /* test esi, esi -> jg 0xb461b */
  display_assert((char *)0x0026db9c, (char *)0x0026d8f4, 679, 0);
  system_exit(0);
  get_global_random_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> jle 0xb466b */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 148);
  /* relift: cmp word ptr [eax + 0x10], 3 -> jne 0xb4664 */
  /* relift: cmp ecx, dword ptr [ebp + 8] -> je 0xb4664 */
  /* test ebx, ebx -> je 0xb4697 */
  /* cmp edi, eax -> jl 0xb4640 */
  display_assert((char *)0x0026db88, (char *)0x0026d8f4, 700, 0);
  system_exit(0);
  /* cmp esi, -1 -> jne 0xb468e */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_000b3b30(0, 0);
  /* test (char)eax, (char)eax -> je 0xb47f5 */
  game_engine_post_event(0);
  /* cmp eax, -1 -> jne 0xb4742 */
  game_engine_get_variant();
  /* test ecx, ecx -> jne 0xb4737 */
  display_assert((char *)0x0026dc08, (char *)0x0026d8f4, 723, 0);
  system_exit(0);
  game_engine_get_variant();
  /* relift: cmp dword ptr [eax + 0x4c], 2 -> jne 0xb476e */
  FUN_000b39a0(0);
  FUN_000b45c0(0);
  /* mem[0x00456f94] = eax */
  FUN_000b39a0(0);
  /* test eax, esi -> je 0xb47c0 */
  display_assert((char *)0x0026dbe0, (char *)0x0026d8f4, 745, 0);
  system_exit(0);
  /* test edi, ecx -> je 0xb47f4 */
  display_assert((char *)0x0026dba8, (char *)0x0026d8f4, 749, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  game_engine_state_message(0, 22, 0);
  /* cmp eax, -1 -> je 0xb4897 */
  game_engine_can_score();
  /* test (char)eax, (char)eax -> je 0xb4897 */
  object_get_and_verify_type(0, 0);
  /* cmp ecx, -1 -> je 0xb486d */
  object_get_and_verify_type(0, 0);
  find_netgame_flag((float *)(uintptr_t)eax, 0.0f, 0.0f, 0, 0);
  find_netgame_flag((float *)(uintptr_t)eax, 0.0f, 0.0f, 0, 0);
  /* cmp eax, -1 -> je 0xb4897 */
  race_update_team_score();
  game_time_get();
  /* cmp eax, 2 -> jne 0xb4915 */
  FUN_000b36f0();
  FUN_000b4490();
  FUN_000a95a0();
  game_engine_post_event(0);
  /* test (char)eax, (char)eax -> je 0xb4915 */
  game_engine_get_variant();
  /* cmp eax, 4 -> ja 0xb4915 */
  game_engine_post_event(23);
  game_engine_post_event(24);
  game_engine_post_event(25);
  game_engine_post_event(25);
  FUN_000a95a0();
  /* test (char)eax, (char)eax -> je 0xb4943 */
  FUN_000b3c60(0);
  /* test (char)eax, (char)eax -> jne 0xb492f */
  game_engine_start_over();
  FUN_000b3c60(0);
  game_engine_start_over();
  global_scenario_get();
  FUN_000b3860();
  csmemset((void *)0x00456f10, 0, 208);
  /* mem[0x005aa744] = 0x1e */
  /* test eax, eax -> jle 0xb4a1a */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 148);
  /* relift: cmp word ptr [eax + 0x10], 3 -> jne 0xb4a13 */
  /* cmp (int16_t)ecx, 0x20 -> jl 0xb49da */
  error(0, (char *)0x0026dc60);
  /* cmp ebx, ecx -> jle 0xb49e3 */
  /* mem[0x00456f10] = ecx */
  game_engine_set_goal_position(0, (void *)0, 0.0f, (char *)0, 0, 0, 0);
  /* cmp edi, eax -> jl 0xb49a7 */
  game_engine_get_variant();
  /* relift: cmp dword ptr [eax + 0x4c], 2 -> jne 0xb4a3a */
  FUN_000b45c0(0);
  /* mem[0x00456f94] = eax */
  game_engine_get_variant();
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, edi -> je 0xb4ab5 */
  /* relift: cmp esi, dword ptr [ebp + 8] -> je 0xb4ab5 */
  /* relift: cmp edx, dword ptr [ecx + 0x20] -> je 0xb4ab5 */
  csmemset((void *)0x00456fe0, 0, 64);
  csmemset((void *)0x00457020, 0, 64);
  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_000a95a0();
  game_engine_post_event(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  game_engine_get_variant();
  /* test (char)ecx, (char)ecx -> jne 0xb4c83 */
  /* test (char)eax, 1 -> jne 0xb4c63 */
  /* test (char)eax, 0x41 -> je 0xb4c5e */
  /* test (char)eax, 0x41 -> jne 0xb4c7a */
  game_engine_get_variant();
  /* test (char)ecx, (char)ecx -> jne 0xb4cf0 */
  /* test (char)eax, 0x41 -> jne 0xb4cc6 */
  /* test (char)eax, 0x41 -> jne 0xb4cea */
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, 1 -> jne 0xb4d7b */
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026c118);
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026d36c);
  usprintf((wchar_t *)(uintptr_t)esi, (wchar_t *)0x0026c118);
  datum_get((void *)(uintptr_t)eax, 0);
  data_iterator_new((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  data_iterator_next((void *)(uintptr_t)ecx);
  /* test eax, eax -> je 0xb4f83 */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp esi, edi -> je 0xb4ead */
  /* relift: cmp esi, dword ptr [ebp - 8] -> je 0xb4ead */
  /* relift: cmp ecx, dword ptr [ebx + 0x20] -> je 0xb4ead */
  /* relift: cmp dword ptr [eax + 0x34], -1 -> je 0xb4ead */
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0xb4e72 */
  /* test eax, eax -> jle 0xb4f81 */
  get_global_random_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  data_iterator_new((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  data_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0xb4f61 */
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp esi, edi -> je 0xb4f44 */
  /* relift: cmp esi, dword ptr [ebp - 8] -> je 0xb4f44 */
  /* relift: cmp ecx, dword ptr [ebx + 0x20] -> je 0xb4f44 */
  /* relift: cmp dword ptr [eax + 0x34], -1 -> je 0xb4f44 */
  /* test eax, eax -> je 0xb4f56 */
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0xb4f00 */
  display_assert((char *)0x0026dcb0, (char *)0x0026dcc4, 194, 0);
  system_exit(0);
  game_engine_player_event(0, 30, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> jne 0xb5035 */
  /* cmp esi, -1 -> je 0xb5033 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> jne 0xb5029 */
  FUN_000b4bf0();
  game_engine_get_variant();
  /* test (char)ecx, (char)ecx -> je 0xb5018 */
  /* relift: cmp dword ptr [ebx + 0x88], edi -> jne 0xb5033 */
  find_next_target();
  FUN_000b4d00();
  FUN_000b4d00();
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, 0x1e -> jne 0xb512e */
  game_engine_get_variant();
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 128, (wchar_t *)0x0026dd64);
  datum_get((void *)(uintptr_t)eax, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 128, (wchar_t *)0x0026c118);
  datum_get((void *)(uintptr_t)ecx, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026dd48);
  /* cmp ecx, 0x16 -> je 0xb5141 */
  /* cmp ecx, 0x1e -> je 0xb510c */
  game_engine_get_variant();
  game_engine_get_place(0, 0);
  game_engine_place_to_string(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  game_engine_get_variant();
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 0, (wchar_t *)0x0026dd14);
  game_engine_get_place(0, 0);
  game_engine_place_to_string(0);
  datum_get((void *)(uintptr_t)eax, 0);
  game_engine_get_variant();
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 0, (wchar_t *)0x0026dcf0);
  datum_get((void *)(uintptr_t)eax, 0);
  game_engine_get_variant();
  /* test (char)ecx, (char)ecx -> je 0xb5269 */
  /* test (char)eax, 0x41 -> jne 0xb5269 */
  /* test (char)eax, 0x41 -> je 0xb5266 */
  game_engine_get_variant();
  /* test (char)ecx, (char)ecx -> je 0xb52a9 */
  /* test (char)eax, 0x41 -> jne 0xb52a6 */
  game_engine_get_variant();
  /* test (char)ecx, (char)ecx -> je 0xb5362 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0xb52c4 */
  /* cmp (int16_t)edi, 0x10 -> jl 0xb52e4 */
  display_assert((char *)0x0026dd7c, (char *)0x0026dcc4, 501, 0);
  system_exit(0);
  game_engine_clear_goal_position(0);
  /* cmp eax, -1 -> je 0xb5331 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0xb5331 */
  object_get_and_verify_type(0, 0);
  game_engine_set_goal_position(0, (void *)(uintptr_t)eax, 0.0f, (char *)0, 0, 0, 0);
  /* relift: cmp dword ptr [esi + 0x34], -1 -> je 0xb5345 */
  /* relift: cmp dword ptr [esi + 0x88], -1 -> jne 0xb5345 */
  find_next_target();
  /* cmp esi, -1 -> je 0xb5362 */
  game_engine_man_out(0);
  /* test (char)eax, (char)eax -> je 0xb5362 */
  find_next_target();
  datum_get((void *)(uintptr_t)edx, 0);
  game_engine_get_variant();
  /* cmp (int16_t)esi, -1 -> je 0xb54d6 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb54a9 */
  /* cmp (int16_t)esi, 0x21 -> jl 0xb54c9 */
  display_assert((char *)0x0026df88, (char *)0x0026dfc4, 905, 0);
  system_exit(0);
  game_globals_get();
  /* cmp (int16_t)ebx, 0x23 -> jl 0xb551e */
  display_assert((char *)0x0026dfe8, (char *)0x0026dfc4, 922, 0);
  system_exit(0);
  /* test esi, esi -> je 0xb557c */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 644);
  /* test eax, eax -> je 0xb557c */
  /* test (int16_t)edi, (int16_t)edi -> jge 0xb555e */
  game_difficulty_level_get();
  game_globals_difficulty_scale(0, 0);
  game_difficulty_level_get();
  game_engine_running();
  /* test (char)eax, (char)eax -> je 0xb55d6 */
  game_globals_difficulty_scale(0, 0);
  game_allegiance_get_team_is_friendly(0, eax);
  /* test (char)eax, (char)eax -> jne 0xb55ca */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0xb55f6 */
  /* cmp (int16_t)ebx, 0x23 -> jl 0xb5616 */
  display_assert((char *)0x0026dfe8, (char *)0x0026dfc4, 957, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> jne 0xb5635 */
  game_globals_difficulty_scale(0, 0);
  game_globals_difficulty_scale(0, 0);
  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test esi, esi -> je 0xb56c8 */
  game_time_get();
  data_iterator_next((void *)(uintptr_t)ecx);
  /* test esi, esi -> jne 0xb5680 */
  /* test (char)eax, (char)eax -> je 0xb5981 */
  player_index_from_unit_index(0);
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ecx, esi -> jne 0xb5750 */
  game_allegiance_get_team_is_friendly(ebx, edx);
  game_time_get();
  game_time_get();
  object_get_and_verify_type(0, 0);
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jne 0xb57dd */
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)edi -> je 0xb5801 */
  /* test (char)eax, (char)eax -> je 0xb581b */
  game_allegiance_get_team_is_friendly(edx, ecx);
  /* test (char)eax, (char)eax -> je 0xb581b */
  /* relift: cmp dword ptr [esi], ebx -> jbe 0xb581b */
  /* test (char)eax, 0x41 -> jne 0xb581b */
  /* cmp (int16_t)edi, 4 -> jl 0xb57d0 */
  /* cmp edi, -1 -> je 0xb58f1 */
  datum_get((void *)(uintptr_t)ecx, 0);
  game_allegiance_get_team_is_friendly(eax, edx);
  /* test (char)eax, (char)eax -> je 0xb58e6 */
  /* cmp ecx, eax -> jl 0xb58cf */
  game_time_get();
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0xb5969 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0xc] -> je 0xb5923 */
  /* test (char)eax, 0x41 -> jne 0xb595c */
  /* cmp eax, -1 -> je 0xb595c */
  /* relift: cmp eax, dword ptr [ebp - 8] -> je 0xb595c */
  datum_get((void *)(uintptr_t)edx, 0);
  game_allegiance_get_team_is_friendly(ecx, eax);
  /* test (char)eax, (char)eax -> je 0xb595c */
  /* cmp (int16_t)edi, 4 -> jl 0xb5910 */
  game_engine_player_killed(0, 0, 0, 0);
  /* test eax, eax -> je 0xb59a4 */
  /* relift: cmp byte ptr [eax], 0 -> je 0xb59a4 */
  game_state_malloc((char *)0x0026e030, (char *)0, 32);
  /* mem[0x0045708c] = eax */
  csmemset((void *)(uintptr_t)eax, 0, 32);
  /* test eax, eax -> je 0xb59ee */
  /* relift: cmp byte ptr [eax], 0 -> je 0xb5a13 */
  display_assert((char *)0x0026e044, (char *)0x0026e07c, 131, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 32);
  /* test eax, eax -> je 0xb5a40 */
  /* test eax, eax -> jne 0xb5a8e */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 196, 0);
  system_exit(0);
  /* test eax, eax -> je 0xb5aae */
  /* relift: cmp byte ptr [eax], 0 -> jne 0xb5ad3 */
  display_assert((char *)0x0026e0b0, (char *)0x0026e07c, 463, 0);
  system_exit(0);
  /* test eax, eax -> je 0xb5aee */
  /* relift: cmp byte ptr [eax], 0 -> jne 0xb5b13 */
  display_assert((char *)0x0026e0b0, (char *)0x0026e07c, 471, 0);
  system_exit(0);
  /* test eax, eax -> je 0xb5b2e */
  /* relift: cmp byte ptr [eax], 0 -> jne 0xb5b53 */
  display_assert((char *)0x0026e0b0, (char *)0x0026e07c, 479, 0);
  system_exit(0);
  /* test eax, eax -> je 0xb5b6e */
  /* relift: cmp byte ptr [eax], 0 -> jne 0xb5b93 */
  display_assert((char *)0x0026e0b0, (char *)0x0026e07c, 487, 0);
  system_exit(0);
  /* test eax, eax -> je 0xb5bae */
  /* relift: cmp byte ptr [eax], 0 -> jne 0xb5bce */
  display_assert((char *)0x0026e0b0, (char *)0x0026e07c, 495, 0);
  system_exit(0);
  /* test eax, eax -> jne 0xb5c0e */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 505, 0);
  system_exit(0);
  /* relift: cmp byte ptr [eax], 0 -> je 0xb5c26 */
  /* test (char)ecx, (char)ecx -> je 0xb5c1d */
  /* test eax, eax -> jne 0xb5c5e */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 533, 0);
  system_exit(0);
  /* test eax, eax -> jne 0xb5ca1 */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 541, 0);
  system_exit(0);
  /* test eax, eax -> jne 0xb5cee */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 555, 0);
  system_exit(0);
  /* test eax, eax -> jne 0xb5d39 */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 562, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0xb5dde */
  system_milliseconds();
  /* mem[0x0045706c] = eax */
  system_milliseconds();
  /* mem[0x0045706c] = eax */
  /* relift: cmp (int16_t)ecx, word ptr [0x457074] -> jge 0xb5e20 */
  /* relift: cmp (int16_t)esi, word ptr [0x45707c] -> jle 0xb5e37 */
  /* cmp (int16_t)esi, (int16_t)edx -> jge 0xb5e4d */
  /* relift: cmp (int16_t)edi, word ptr [0x457082] -> jle 0xb5e64 */
  /* relift: cmp (int16_t)edi, word ptr [0x457080] -> jge 0xb5e74 */
  /* relift: cmp (int16_t)ebx, word ptr [0x457088] -> jle 0xb5e8b */
  /* relift: cmp (int16_t)ebx, word ptr [0x457086] -> jge 0xb5e9b */
  /* relift: cmp word ptr [0x457072], 0x3e8 -> jl 0xb5f3e */
  /* relift: cmp word ptr [0x457070], 0 -> jle 0xb5f3e */
  /* test (int16_t)edx, (int16_t)edx -> je 0xb5f2c */
  /* relift: cmp (int16_t)eax, word ptr [ecx + 4] -> je 0xb5ef5 */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 8] -> jge 0xb5f13 */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 8] -> jle 0xb5f13 */
  /* relift: cmp word ptr [ecx + 6], 5 -> jne 0xb5f37 */
  /* test eax, eax -> je 0xb5f4e */
  /* relift: cmp byte ptr [eax], 0 -> jne 0xb5f73 */
  display_assert((char *)0x0026e0b0, (char *)0x0026e07c, 162, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0xb5f9f */
  display_assert((char *)0x0026e0e4, (char *)0x0026e07c, 163, 0);
  system_exit(0);
  /* test eax, eax -> jne 0xb5fc8 */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 562, 0);
  system_exit(0);
  game_connection();
  /* cmp eax, 3 -> ja 0xb6006 */
  /* test ecx, ecx -> jne 0xb6056 */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 205, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0xb6364 */
  /* test (char)eax, 0x41 -> jne 0xb6324 */
  game_connection();
  /* cmp eax, 3 -> ja 0xb612e */
  network_game_server_get();
  FUN_0012d5b0(0);
  game_time_get();
  /* cmp eax, 0x80 -> jbe 0xb60f1 */
  display_assert((char *)0x0026e178, (char *)0x0026e07c, 243, 0);
  system_exit(0);
  /* test edi, edi -> jbe 0xb6127 */
  /* cmp esi, 0x1e -> jge 0xb6115 */
  network_game_server_stalled_on_client((void *)(uintptr_t)ebx, 0);
  network_game_server_stalled_on_client((void *)(uintptr_t)ebx, 0);
  floor(0.0f);
  FUN_001d9068();
  /* test (char)eax, 1 -> jne 0xb61d1 */
  display_assert((char *)0x0026e128, (char *)0x0026e07c, 306, 0);
  system_exit(0);
  game_connection();
  /* cmp (int16_t)eax, 1 -> jne 0xb6268 */
  update_get_maximum_actions();
  /* cmp esi, edi -> jle 0xb6219 */
  /* cmp eax, edi -> jge 0xb6232 */
  /* cmp eax, edi -> jge 0xb623f */
  /* cmp esi, edi -> jle 0xb6268 */
  display_assert((char *)0x0026e100, (char *)0x0026e07c, 339, 0);
  system_exit(0);
  /* test esi, esi -> jle 0xb631b */
  /* relift: cmp ecx, dword ptr [eax + 0x14] -> jge 0xb6286 */
  game_connection();
  network_game_server_get();
  network_game_server_update_ticks(0, 0);
  update_client_apply_actions(esi);
  update_get_game_time();
  /* cmp esi, ecx -> jle 0xb62f9 */
  /* cmp esi, edi -> jg 0xb62d3 */
  /* test edi, edi -> jle 0xb62fb */
  game_tick();
  game_time_statistics_frame(0, 0, 0);
  /* test ecx, ecx -> jne 0xb634e */
  display_assert((char *)0x0026e09c, (char *)0x0026e07c, 555, 0);
  system_exit(0);
  game_frame(0.0f);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb6393 */
  /* cmp (int16_t)esi, 4 -> jl 0xb63b3 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  game_state_malloc((char *)0x0026e210, (char *)0, 272);
  /* mem[0x00457090] = eax */
  /* relift: test byte ptr [eax + 0xc], 1 -> jne 0xb6427 */
  game_time_get_paused();
  /* test (char)eax, (char)eax -> jne 0xb6427 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb6473 */
  /* cmp (int16_t)esi, 4 -> jl 0xb6493 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0xb6529 */
  FUN_001d9068();
  /* test (int16_t)eax, (int16_t)eax -> jge 0xb653a */
  /* cmp eax, esi -> jle 0xb6543 */
  /* test esi, esi -> je 0xb6569 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0xb6569 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jg 0xb6569 */
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 8] -> jl 0xb6589 */
  display_assert((char *)0x0026e228, (char *)0x0026e1e8, 331, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 32);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb65d3 */
  /* cmp (int16_t)esi, 4 -> jl 0xb65f3 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  unit_get_aiming_unit_index(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb6633 */
  /* cmp (int16_t)esi, 4 -> jl 0xb6653 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xb667c */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb66a3 */
  /* cmp (int16_t)esi, 4 -> jl 0xb66c3 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0xb673b */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  unit_get_weapon(0, eax);
  /* cmp eax, -1 -> je 0xb6733 */
  weapon_get_field_of_view(0, 0.0f, edx);
  display_assert((char *)0x0026e274, (char *)0x0026e1e8, 1026, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 4 -> jl 0xb67a2 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  unit_set_seat_state(0, (float *)(uintptr_t)eax);
  /* cmp eax, -1 -> je 0xb6847 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xb6847 */
  tag_get('ihev', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  object_get_and_verify_type(0, 0);
  /* relift: cmp word ptr [esi + 4], -1 -> jne 0xb6866 */
  tag_get('tinu', 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb6883 */
  /* cmp (int16_t)esi, 4 -> jl 0xb68a3 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb68d3 */
  /* cmp (int16_t)esi, 4 -> jl 0xb68f3 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  /* relift: cmp dword ptr [eax], esi -> jne 0xb691f */
  unit_get_weapon(0, edx);
  /* cmp eax, -1 -> jne 0xb6938 */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, eax);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb6953 */
  /* cmp (int16_t)esi, 4 -> jl 0xb6973 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  /* cmp eax, -1 -> je 0xb69c2 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xb69e1 */
  /* cmp (int16_t)esi, 4 -> jl 0xb6a01 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 4 -> jl 0xb69d6 */
  object_get_and_verify_type(0, 0);
  /* cmp eax, -1 -> je 0xb6a65 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0xb6a65 */
  player_control_get_data(eax);
  /* cmp (int16_t)ecx, -1 -> je 0xb6a8c */
  player_control_get_data(ecx);
  /* test (char)eax, (char)eax -> je 0xb6be5 */
  cinematic_can_be_skipped();
  /* test (char)eax, (char)eax -> je 0xb6be5 */
  main_skip_cinematic();
  /* relift: test byte ptr [esi + 0x18], 2 -> je 0xb6bfd */
  /* test (char)eax, (char)eax -> je 0xb6c07 */
  /* test (char)eax, (char)eax -> je 0xb6c11 */
  /* test (char)eax, 0x41 -> jne 0xb6c24 */
  /* test (char)eax, 0x20 -> je 0xb6c2f */
  /* relift: test byte ptr [esi + 0x1c], 4 -> je 0xb6c38 */
  /* test (char)eax, 0x41 -> jne 0xb6c51 */
  /* test (char)eax, 0x41 -> jne 0xb6c83 */
  /* test (char)eax, 0x41 -> jne 0xb6cb4 */
  /* test (char)eax, 0x41 -> jne 0xb6ce5 */
  /* test (char)eax, 1 -> je 0xb6d24 */
  /* relift: test byte ptr [esi + 0x18], 0x40 -> je 0xb6d1b */
  /* test (char)eax, 4 -> jne 0xb6d4c */
  /* test (char)eax, 4 -> je 0xb6d4f */
  /* relift: test byte ptr [esi + 0x18], 0x40 -> je 0xb6d46 */
  /* relift: test byte ptr [ecx + 4], 8 -> jne 0xb6d73 */
  /* test (char)eax, 8 -> je 0xb6dc2 */
  /* relift: test byte ptr [esi + 0x1c], 1 -> je 0xb6d6d */
  /* test (char)eax, 4 -> je 0xb6d9c */
  /* relift: test byte ptr [esi + 0x18], 2 -> je 0xb6d93 */
  /* relift: test byte ptr [ecx + 4], 8 -> jne 0xb6dbf */
  /* test (char)eax, 4 -> je 0xb6dc2 */
  /* relift: test byte ptr [esi + 0x1c], 2 -> je 0xb6db9 */
  /* test (char)eax, 1 -> jne 0xb6dec */
  /* test (char)eax, 0x41 -> jne 0xb6e4f */
  /* test (char)eax, 0x41 -> jne 0xb6e97 */
  /* cmp (int16_t)esi, 4 -> jl 0xb6ed4 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  vector_to_angles((float *)(uintptr_t)edi, (float *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x0025eb8c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  csprintf((char *)0x005ab100, (char *)0x0025eb8c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0xb6fda */
  /* cmp (int16_t)esi, 4 -> jl 0xb6ff9 */
  display_assert((char *)0x00266fc0, (char *)0x0026e1e8, 177, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 64);
  object_get_and_verify_type(0, 0);
  vector_to_angles((float *)(uintptr_t)edi, (float *)(uintptr_t)edx);
  local_player_get_player_index(eax);
  csmemset((void *)(uintptr_t)ebx, 0, 32);
  /* cmp esi, -1 -> je 0xb7dc3 */
  player_control_get_data(ecx);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp (int16_t)esi, -1 -> je 0xb7af6 */
  input_has_gamepad(esi);
  /* test (char)eax, (char)eax -> je 0xb7af6 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  input_get_gamepad_state(0);
  input_abstraction_get_input_state(0);
  object_get_and_verify_type(0, 0);
  /* relift: cmp word ptr [esi + 0x2a0], -1 -> je 0xb7242 */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0xb721a */
  /* test (char)eax, 0x41 -> jne 0xb7242 */
  /* test (char)eax, 0x41 -> jne 0xb72c3 */
  /* test (char)eax, 0x41 -> jne 0xb72c3 */
  /* test (char)eax, 0x41 -> jne 0xb72a6 */
  /* test (char)eax, 0x41 -> jne 0xb72f8 */
  /* test (char)eax, 0x41 -> jne 0xb732e */
  /* relift: test byte ptr [edx + 0xc], 1 -> jne 0xb76f4 */
  game_time_get_paused();
  /* test (char)eax, (char)eax -> jne 0xb76f4 */
  /* test dl, dl -> je 0xb736d */
  /* test (char)eax, (char)eax -> je 0xb736d */
  /* test (char)eax, (char)eax -> je 0xb7396 */
  display_assert((char *)0x0026e324, (char *)0x0026e1e8, 456, 0);
  system_exit(0);
  evaluate_piecewise_linear_function(edx, (float *)(uintptr_t)ecx, 0.0f);
  evaluate_piecewise_linear_function(edx, (float *)0, 0.0f);
  /* cmp (int16_t)ecx, -1 -> je 0xb7440 */
  unit_get_zoom_magnification(0, 0);
  /* relift: cmp dword ptr [ecx + 0x34], -1 -> je 0xb7497 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  object_get_and_verify_type(0, 0);
  /* test (char)eax, 0x41 -> je 0xb74c7 */
  display_assert((char *)0x0026e2fc, (char *)0x0026e1e8, 483, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0xb7533 */
  /* test (char)eax, 0x41 -> jne 0xb750f */
  FUN_000a6470(eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0xb76d7 */
  /* test (char)eax, 0x41 -> jne 0xb76d7 */
  /* test (char)eax, 0x41 -> je 0xb75c3 */
  /* test (char)eax, 0x41 -> je 0xb75c3 */
  /* test (char)eax, 0x41 -> je 0xb75c3 */
  /* test (char)eax, 0x41 -> jne 0xb76d7 */
  game_time_get_speed();
  /* test (char)eax, 0x41 -> jne 0xb75f9 */
  /* test (char)eax, 0x41 -> jne 0xb7637 */
  game_players_are_double_speed();
  /* test (char)eax, 0x41 -> jne 0xb768d */
  /* test (char)eax, 0x41 -> jne 0xb76b9 */
  /* test (int16_t)eax, (int16_t)eax -> je 0xb7848 */
  /* test esi, eax -> je 0xb775d */
  /* test (char)eax, (char)eax -> jne 0xb775d */
  /* test esi, eax -> je 0xb7786 */
  /* relift: cmp byte ptr [edx + ecx], 0 -> jne 0xb7786 */
  /* test esi, eax -> je 0xb77b3 */
  /* test (char)eax, (char)eax -> jne 0xb77b3 */
  /* test esi, eax -> je 0xb77e0 */
  /* test (char)eax, (char)eax -> jne 0xb77e0 */
  /* test esi, eax -> je 0xb780d */
  /* test (char)eax, (char)eax -> jne 0xb780d */
  /* test esi, eax -> je 0xb7839 */
  /* relift: cmp byte ptr [edx + eax + 4], 0 -> jne 0xb7839 */
  /* cmp ecx, 0xc -> jl 0xb7730 */
  /* test eax, ecx -> jne 0xb78bf */
  /* test ecx, esi -> jne 0xb78df */
  /* test ecx, esi -> jne 0xb78fd */
  /* test ecx, esi -> jne 0xb791b */
  /* test ecx, esi -> jne 0xb7939 */
  /* test ecx, esi -> jne 0xb7957 */
  /* cmp edx, 0xc -> jl 0xb7898 */
  /* cmp eax, -1 -> je 0xb79c5 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xb79c5 */
  /* test (char)ecx, (char)ecx -> jne 0xb79b0 */
  /* relift: test byte ptr [eax + 0x424], 1 -> jne 0xb79b0 */
  /* test (char)eax, (char)eax -> je 0xb7a40 */
  /* relift: cmp byte ptr [ebp - 0x47], 1 -> jne 0xb7acc */
  /* relift: test byte ptr [edi + 9], 2 -> jne 0xb7ade */
  /* relift: test byte ptr [edi + 8], 4 -> jne 0xb7cfa */
  FUN_000cf690();
  /* test eax, eax -> je 0xb7cfa */
  /* test (char)eax, (char)eax -> je 0xb7cfa */
  FUN_000cf690();
  input_key_is_down(46);
  input_key_is_down(0);
  input_key_is_down(0);
  input_key_is_down(0);
  /* test (char)eax, 1 -> jne 0xb7ba0 */
  game_time_get_paused();
  /* test (char)eax, (char)eax -> jne 0xb7ba0 */
  input_key_is_down(105);
  input_key_is_down(108);
  input_key_is_down(106);
  input_key_is_down(72);
  input_key_is_down(31);
  input_key_is_down(59);
  input_key_is_down(34);
  input_key_is_down(58);
  input_key_is_down(33);
  /* relift: test dword ptr [ebx + 0x18], esi -> je 0xb7cf1 */
  input_key_is_down(43);
  input_key_is_down(42);
  input_key_is_down(41);
  input_key_is_down(17);
  input_key_is_down(18);
  /* test (char)eax, 0x41 -> jne 0xb7dc1 */
  FUN_000b6bd0((char *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xc0bb0 */
void FUN_000c0bb0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0be5 */
  FUN_00057900(0, edx);
  hs_return(0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0xc0bf0 */
void FUN_000c0bf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0c26 */
  FUN_000579d0(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0c66 */
  FUN_00057aa0(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0ca5 */
  FUN_00057c70(0, edx);
  hs_return(0, 0);
  FUN_00057c60();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0d03 */
  FUN_00057d00(0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0d46 */
  FUN_00057f90(0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0d86 */
  FUN_00057fd0(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0dc6 */
  FUN_00058020(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0e03 */
  FUN_00058070(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0e3f */
  FUN_00058110(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0e83 */
  FUN_000581b0(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0ebf */
  FUN_00058220(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0f05 */
  FUN_00058270(0, edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0f3f */
  FUN_00058310(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0f7f */
  FUN_00058390(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc0fc3 */
  FUN_00058410(eax, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1003 */
  FUN_000584a0(eax, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1046 */
  FUN_00058550(edx, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1082 */
  FUN_00058640(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc10c2 */
  FUN_000586a0(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1103 */
  FUN_00058720(eax, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1145 */
  FUN_000587d0(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1186 */
  FUN_00058860(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc11c5 */
  FUN_00057030(0, edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1205 */
  FUN_000588d0(0, edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc124c */
  FUN_000556f0(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc129d */
  FUN_00057380(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc12ed */
  FUN_00056880(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc133d */
  FUN_00055660(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1385 */
  FUN_00055680(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc13c5 */
  FUN_000556c0(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc140d */
  FUN_00055620(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc145d */
  FUN_00055640(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc149e */
  FUN_000547c0(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc14ed */
  FUN_00057bc0(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc153f */
  FUN_000585d0(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1590 */
  FUN_00058700(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc15e0 */
  FUN_00058710(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1634 */
  FUN_000567e0(eax, edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1671 */
  director_script_camera(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc16b7 */
  FUN_00085260(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc16fd */
  FUN_00085180(0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1733 */
  FUN_00085000(0, (char *)(uintptr_t)edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc176f */
  FUN_000850d0(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc17af */
  FUN_00085110(0);
  hs_return(0, 0);
  FUN_000853a0();
  hs_return(0, 0);
  director_save_camera();
  hs_return(0, 0);
  director_load_camera();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc185f */
  game_time_set_speed(0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc189f */
  game_set_game_variant_from_name((char *)(uintptr_t)edx);
  hs_return(0, 0);
  game_time_get();
  hs_return(0, 0);
  FUN_000A7470();
  hs_return(0, 0);
  game_difficulty_level_get();
  hs_return(0, 0);
  players_unzoom_all();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1981 */
  player_input_enable(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc19ce */
  scripted_player_control_set_camera_control(edx);
  hs_return(0, 0);
  player_control_action_test_reset();
  hs_return(0, 0);
  player_control_action_test_jump();
  hs_return(0, 0);
  player_control_action_test_primary_trigger();
  hs_return(0, 0);
  player_control_action_test_grenade_trigger();
  hs_return(0, 0);
  player_control_action_test_zoom();
  hs_return(0, 0);
  player_control_action_test_action();
  hs_return(0, 0);
  player_control_action_test_accept();
  hs_return(0, 0);
  player_control_action_test_back();
  hs_return(0, 0);
  player_control_action_test_look_relative_up();
  hs_return(0, 0);
  player_control_action_test_look_relative_down();
  hs_return(0, 0);
  player_control_action_test_look_relative_left();
  hs_return(0, 0);
  player_control_action_test_look_relative_right();
  hs_return(0, 0);
  player_control_action_test_look_relative_all_directions();
  hs_return(0, 0);
  player_control_action_test_move_relative_all_directions();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1cac */
  player_add_equipment(0, ecx, edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1ce7 */
  debug_player_teleport(eax, edx);
  hs_return(0, 0);
  main_reset_map();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1d3f */
  main_set_map_name((char *)(uintptr_t)edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1d7f */
  main_set_multiplayer_map_name((char *)(uintptr_t)edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1dc2 */
  main_set_difficulty(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1dff */
  main_crash(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1e42 */
  scenario_switch_structure_bsp(edx);
  hs_return(0, 0);
  global_structure_bsp_index_get();
  hs_return(0, 0);
  main_print_version();
  hs_return(0, 0);
  main_set_game_connection_to_film_playback();
  hs_return(0, 0);
  texture_cache_flush();
  hs_return(0, 0);
  sound_cache_flush();
  hs_return(0, 0);
  FUN_0008f1e0();
  hs_return(0, 0);
  debug_dump_memory_by_file();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1f6f */
  debug_dump_memory_for_file((char *)(uintptr_t)edx);
  hs_return(0, 0);
  hs_return(0, 0);
  FUN_0008f630();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc1fef */
  profile_dump_to_file(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc202f */
  profile_sections_activate(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc206f */
  profile_sections_deactivate(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc20af */
  profile_graph_toggle(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc20f1 */
  debug_pvs(edx);
  hs_return(0, 0);
  hs_return(0, 0);
  hs_return(0, 0);
  hs_return(0, 0);
  FUN_00053890();
  hs_return(0, 0);
  ai_debug_sound_point_set();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc21d3 */
  ai_debug_vocalize(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc220f */
  ai_debug_teleport_to(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc224f */
  ai_debug_speak(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc228f */
  ai_debug_speak_list(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc22e6 */
  player_effect_screen_fade_in(0, 0.0f, 0.0f, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2336 */
  player_effect_screen_fade_out(0, 0.0f, 0.0f, 0);
  hs_return(0, 0);
  cinematic_start();
  hs_return(0, 0);
  cinematic_stop();
  hs_return(0, 0);
  cinematic_skip_start();
  hs_return(0, 0);
  cinematic_skip_stop();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc23f1 */
  cinematic_show_letterbox(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2432 */
  FUN_00093640(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2479 */
  cinematic_set_title_delayed(0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc24b1 */
  cinematic_suppress_bsp_object_creation(0);
  hs_return(0, 0);
  event_manager_tab_process();
  hs_return(0, 0);
  main_won_map();
  hs_return(0, 0);
  FUN_00100380();
  hs_return(0, 0);
  game_safe_to_save();
  hs_return(0, 0);
  game_all_quiet();
  hs_return(0, 0);
  game_safe_to_speak();
  hs_return(0, 0);
  game_is_cooperative();
  hs_return(0, 0);
  main_save_map_safe();
  hs_return(0, 0);
  main_save_cancel();
  hs_return(0, 0);
  main_save_map_no_timeout();
  hs_return(0, 0);
  main_save_map_nonsafe();
  hs_return(0, 0);
  main_saving_map();
  hs_return(0, 0);
  main_revert_map();
  hs_return(0, 0);
  main_load_core();
  hs_return(0, 0);
  main_load_core_at_startup();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc271f */
  main_load_core_name((char *)(uintptr_t)edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc275f */
  main_load_core_name_at_startup((char *)(uintptr_t)edx);
  hs_return(0, 0);
  main_save_core();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc27bf */
  main_save_core_name((char *)(uintptr_t)edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2802 */
  main_skip(edx);
  hs_return(0, 0);
  game_state_reverted();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc287a */
  scripted_sound_new(0, 0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc28ae */
  scripted_sound_time(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc28ef */
  scripted_sound_stop(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc292f */
  scripted_foley_predict(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc297a */
  sound_looping_start(0, 0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc29af */
  sound_looping_stop(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc29f6 */
  scripted_looping_sound_set_scale(0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2a35 */
  scripted_looping_sound_set_alternate(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2a75 */
  debug_sound_classes_enable((char *)(uintptr_t)eax, edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2abf */
  debug_sound_classes_set_distances((char *)(uintptr_t)edx, 0.0f, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2b06 */
  debug_sound_classes_set_wet((char *)(uintptr_t)edx, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2b4d */
  game_sound_set_music_volume((char *)(uintptr_t)eax, 0.0f, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2b81 */
  sound_enable(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2bc5 */
  FUN_001b5610(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2c0e */
  scripted_show_hud(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2c5e */
  scripted_show_hud_help_text(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2ca1 */
  scripted_hud_set_flashing_state(edx);
  hs_return(0, 0);
  scripted_hud_restart_flashing();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2d14 */
  FUN_000d6490(0, 0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2d61 */
  FUN_000d64c0(0, 0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2db7 */
  FUN_000d6220(0, 0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2e04 */
  FUN_000d6250(0, 0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2e46 */
  FUN_000d64f0(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2e83 */
  FUN_000d6520(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2ec7 */
  FUN_000d6450(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2f04 */
  FUN_000d6470(0, 0);
  hs_return(0, 0);
  terminal_show();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2f61 */
  errors_overflow_suppression_enable(edx);
  hs_return(0, 0);
  FUN_001954d0();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc2fcf */
  scripted_player_effect_set_translation(0, 0.0f, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc301f */
  scripted_player_effect_set_rotation(0, 0.0f, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3066 */
  scripted_player_effect_set_rumble(0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc30a6 */
  scripted_player_effect_start(0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc30df */
  scripted_player_effect_stop(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3121 */
  FUN_000d7440(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3161 */
  FUN_000d7470(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc31a1 */
  FUN_000d74a0(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc31e1 */
  FUN_000d74d0(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3221 */
  FUN_000d7500(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3261 */
  FUN_000d7530(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc32a1 */
  FUN_000d8b90(edx);
  hs_return(0, 0);
  scripted_hud_messages_clear();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3302 */
  scripted_hud_set_state_message(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3342 */
  scripted_hud_set_objective(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3387 */
  scripted_hud_set_timer_time(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc33c7 */
  scripted_hud_set_timer_warning_cutoff(0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3410 */
  scripted_hud_set_timer_position(0, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3451 */
  scripted_hud_show_timer(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3491 */
  scripted_hud_pause_timer(edx);
  hs_return(0, 0);
  scripted_hud_get_timer_ticks();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3501 */
  scripted_hud_time_code_show(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3541 */
  scripted_hud_time_code_start(edx);
  hs_return(0, 0);
  scripted_hud_time_code_reset();
  hs_return(0, 0);
  FUN_0017cac0();
  hs_return(0, 0);
  FUN_0017ed30();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc35f6 */
  FUN_0016b270(0, 0.0f, 0.0f, 0.0f);
  hs_return(0, 0);
  FUN_00181150();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3659 */
  FUN_0017d9a0(0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3691 */
  FUN_0017da00(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc36ee */
  FUN_0017da40(0, 0, 0.0f, 0.0f, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3753 */
  FUN_0017dab0(0, 0.0f, 0.0f, 0.0f, 0, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc379f */
  FUN_0017db20(0, 0.0f, 0.0f);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc37e9 */
  rasterizer_screen_effect_set_video(0, 0.0f);
  hs_return(0, 0);
  FUN_0017dc60();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc383f */
  FUN_0017dec0(0);
  hs_return(0, 0);
  FUN_001c58f0();
  hs_return(0, 0);
  FUN_001c4f30();
  hs_return(0, 0);
  player_ui_fast_setup_network_server();
  hs_return(0, 0);
  player_ui_activate_all_solo_levels();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3901 */
  FUN_000e1770(0);
  hs_return(0, 0);
  player0_look_pitch_is_inverted();
  hs_return(0, 0);
  FUN_000e1060();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc39a1 */
  ui_widget_debug_show_path(edx);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc39e2 */
  FUN_000e8e20(0);
  hs_return(0, 0);
  FUN_0012a7a0();
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc3a3f */
  xbox_set_machine_name((char *)(uintptr_t)edx);
  hs_return(0, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 52);
  /* test eax, eax -> jle 0xc3ac9 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 52);
  crt_stricmp((char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0xc3ac9 */
  /* cmp eax, ecx -> jl 0xc3aa8 */
  /* cmp eax, ecx -> jne 0xc3b24 */
  tag_block_add_element((void *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0xc3b20 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 52);
  csstrcpy((char *)(uintptr_t)ebx, (char *)(uintptr_t)edi);
  tag_data_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0xc3b20 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  /* cmp eax, edx -> jl 0xc3a87 */
  tag_block_resize((void *)(uintptr_t)edx, 0);
  global_scenario_get();
  /* test esi, esi -> je 0xc3b89 */
  /* relift: cmp dword ptr [esi + 0x474], 0x5ccac -> je 0xc3c1f */
  data_new((char *)0x0027b8e0, 19001, 20);
  /* mem[0x005aa6c8] = eax */
  data_delete_all((void *)(uintptr_t)eax);
  /* test esi, esi -> je 0xc3c07 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0027b8c8, 336);
  tag_data_resize((void *)(uintptr_t)edx, 1024);
  tag_block_resize((void *)(uintptr_t)esi, 0);
  error(0, (char *)0x0027b8a0);
  hs_runtime_dispose_from_old_map();
  /* test (char)eax, (char)eax -> je 0xc3c6f */
  /* test (char)eax, (char)eax -> je 0xc3c6f */
  profile_enter_private((void *)0x002f1c10);
  hs_runtime_update();
  /* test (char)eax, (char)eax -> je 0xc3c91 */
  /* test (char)eax, (char)eax -> je 0xc3c91 */
  profile_exit_private((void *)0x002f1c10);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> je 0xc3cf6 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 8 -> jne 0xc3ce0 */
  datum_delete((void *)(uintptr_t)edx, 0);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> jne 0xc3cb8 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xc3d14 */
  /* cmp (int16_t)esi, 0x1a2 -> jl 0xc3d41 */
  display_assert((char *)0x0027b8ec, (char *)0x0027b8c8, 522, 0);
  system_exit(0);
  global_scenario_get();
  /* test eax, eax -> jle 0xc3d98 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 92);
  csstrcmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0xc3da1 */
  /* cmp eax, ecx -> jl 0xc3d77 */
  global_scenario_get();
  /* test eax, eax -> jle 0xc3df4 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 40);
  /* cmp ecx, ebx -> je 0xc3dfd */
  /* cmp eax, ecx -> jl 0xc3dd7 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xc3e26 */
  /* relift: cmp (int16_t)esi, word ptr [0x27d504] -> jl 0xc3e53 */
  display_assert((char *)0x0027b928, (char *)0x0027b8c8, 576, 0);
  system_exit(0);
  hs_external_global_get(eax);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  hs_external_global_get(eax);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0xc3f45 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xc3eff */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0xc3f1f */
  display_assert((char *)0x0027b928, (char *)0x0027b8c8, 576, 0);
  system_exit(0);
  crt_stricmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0xc3f9c */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0xc3ef5 */
  global_scenario_get();
  /* test eax, eax -> jle 0xc3f93 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  crt_stricmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0xc3fa7 */
  /* cmp eax, ecx -> jl 0xc3f64 */
  crt_stricmp((char *)(uintptr_t)edx, (char *)(uintptr_t)edi);
  /* test eax, eax -> je 0xc3ffb */
  /* cmp (int16_t)esi, 0x1a2 -> jl 0xc3fd0 */
  crt_stricmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0xc4059 */
  display_assert((char *)0x0027b964, (char *)0x0027b8c8, 666, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [0x46b6cc] -> jge 0xc40a3 */
  csstrlen((char *)(uintptr_t)ecx);
  __strnicmp((char *)(uintptr_t)esi, (char *)(uintptr_t)edx, eax);
  /* test eax, eax -> jne 0xc40a3 */
  /* cmp (int16_t)ecx, (int16_t)eax -> jge 0xc40e0 */
  FUN_000c4030((char *)0);
  /* test eax, eax -> jle 0xc4125 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_000c4030((char *)0);
  /* cmp eax, ecx -> jl 0xc4100 */
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc415b */
  global_scenario_get();
  FUN_000c40f0(ecx, 0, (void *)0);
  FUN_000c4030((char *)(uintptr_t)esi);
  FUN_000c4030((char *)0);
  FUN_000c4030((char *)(uintptr_t)edi);
  FUN_000c4030((char *)(uintptr_t)edi);
  /* test (int16_t)edi, (int16_t)edi -> jl 0xc41fc */
  /* cmp (int16_t)edi, 0x1a2 -> jl 0xc421c */
  display_assert((char *)0x0027b8ec, (char *)0x0027b8c8, 522, 0);
  system_exit(0);
  FUN_000c4030((char *)0);
  /* cmp (int16_t)edi, 0x1a2 -> jl 0xc41f0 */
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4263 */
  global_scenario_get();
  FUN_000c40f0(0, 92, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0xc42c7 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0xc428a */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0xc42aa */
  display_assert((char *)0x0027b928, (char *)0x0027b8c8, 576, 0);
  system_exit(0);
  FUN_000c4030((char *)0);
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0xc4280 */
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc430e */
  global_scenario_get();
  /* test eax, eax -> jle 0xc430d */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 92);
  FUN_000c4030((char *)0);
  /* cmp eax, ecx -> jl 0xc42f0 */
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4346 */
  global_scenario_get();
  FUN_000c40f0(0, 176, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4373 */
  global_scenario_get();
  FUN_000c40f0(0, 96, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc43a3 */
  global_scenario_get();
  FUN_000c40f0(0, 104, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc43d3 */
  global_scenario_get();
  FUN_000c40f0(0, 116, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4403 */
  global_scenario_get();
  FUN_000c40f0(0, 36, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4433 */
  global_scenario_get();
  FUN_000c40f0(0, 96, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4463 */
  global_scenario_get();
  FUN_000c40f0(0, 92, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc4493 */
  global_scenario_get();
  FUN_000c40f0(0, 104, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc44c3 */
  global_scenario_get();
  FUN_000c40f0(0, 96, (void *)0);
  /* relift: cmp dword ptr [0x326a08], -1 -> je 0xc44f3 */
  global_scenario_get();
  FUN_000c40f0(0, 64, (void *)0);
  interface_get_tag_index(0);
  /* cmp eax, -1 -> je 0xc4535 */
  interface_get_tag_index(0);
  tag_get('gduh', 0);
  FUN_000c40f0(0, 104, (void *)0);
  global_scenario_get();
  /* relift: cmp dword ptr [eax + 0x5a0], -1 -> je 0xc4575 */
  global_scenario_get();
  tag_get(' tmh', 0);
  FUN_000c40f0(0, 64, (void *)0);
  /* cmp eax, edi -> je 0xc45b1 */
  display_assert((char *)0x0027b9a4, (char *)0x0027b8c8, 920, 0);
  system_exit(0);
  /* mem[0x0046b6d0] = ecx */
  /* mem[0x0046b6d4] = eax */
  /* mem[0x0046b6d4] = 0x25386f */
  /* relift: cmp dword ptr [esi], 0 -> jne 0xc4615 */
  display_assert((char *)0x0027b980, (char *)0x0027b8c8, 929, 0);
  system_exit(0);
  /* test eax, edx -> je 0xc4627 */
  qsort((void *)(uintptr_t)edx, ecx, 0, (void *)0x000c4010);
  /* mem[0x0046b6d0] = 0 */
  global_scenario_get();
  file_exists((void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0xc475b */
  tag_block_add_element((void *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0xc474c */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 52);
  file_read_into_buffer((void *)(uintptr_t)ebx, (void *)(uintptr_t)ecx);
  /* test edi, edi -> je 0xc4735 */
  tag_data_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0xc471e */
  file_reference_get_name((void *)(uintptr_t)ebx, 0, (char *)(uintptr_t)eax);
  csstrncpy((char *)(uintptr_t)esi, (char *)(uintptr_t)ecx, 31);
  tag_data_get_pointer((void *)(uintptr_t)edx, 0, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)0, 0);
  error(0, (char *)0x0027ba10);
  error(0, (char *)0x0027b9e8);
  error(0, (char *)0x0027b9bc);
  file_reference_get_name((void *)(uintptr_t)ecx, 0, (char *)(uintptr_t)eax);
  file_reference_get_name((void *)(uintptr_t)eax, 0, (char *)(uintptr_t)edx);
  crt_stricmp((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  global_scenario_get();
  tag_block_resize((void *)(uintptr_t)eax, 0);
  tag_get_name(0);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x0027ba58);
  strrchr((char *)(uintptr_t)edx, 92);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x0027ba38, 0);
  file_exists((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0xc4852 */
  hs_load_source_file((void *)0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  find_files(0, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)ecx);
  qsort((void *)(uintptr_t)ecx, eax, 268, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jle 0xc48ec */
  file_reference_get_name((void *)(uintptr_t)ebx, 0, (char *)(uintptr_t)edx);
  csstrcmp((char *)(uintptr_t)eax, (char *)0x0027ba34);
  /* test eax, eax -> jne 0xc48e3 */
  hs_load_source_file((void *)0);
  /* test (char)eax, (char)eax -> jne 0xc48e3 */
  /* test esi, esi -> je 0xc491b */
  crt_strchr((char *)(uintptr_t)esi, 10);
  /* test eax, eax -> je 0xc491b */
  /* test ebx, ebx -> je 0xc4956 */
  /* test eax, eax -> je 0xc4956 */
  /* relift: cmp byte ptr [eax], 0xa -> jne 0xc4936 */
  /* cmp eax, edi -> ja 0xc4930 */
  error(0, (char *)0x0027ba60);
  error(0, (char *)0x00259f2c);
  global_scenario_get();
  hs_syntax_reset(0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 52);
  tag_data_get_pointer((void *)(uintptr_t)esi, 0, 0);
  hs_compile_source(0, (void *)(uintptr_t)eax, (char **)0, (char **)0);
  /* test eax, eax -> je 0xc4a04 */
  tag_data_get_pointer((void *)(uintptr_t)esi, 0, 0);
  hs_report_compile_error((void *)(uintptr_t)edx, (char *)0, (char *)0, (void *)0);
  /* cmp eax, ecx -> jl 0xc49a6 */
  console_printf(0, (char *)0x0027ba74);
  hs_compile_cleanup();
  hs_function_table_get(eax);
  crt_sprintf((char *)(uintptr_t)esi, (char *)0x0027ba9c);
  /* test eax, eax -> je 0xc4a8c */
  csstrlen((char *)(uintptr_t)esi);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  FUN_0008dc30((char *)(uintptr_t)esi, (char *)0x00268580);
  /* relift: cmp word ptr [edi + 0x18], (int16_t)ebx -> jle 0xc4acb */
  FUN_0008dc30((char *)(uintptr_t)esi, (char *)0x0027ba94);
  FUN_0008dc30((char *)(uintptr_t)esi, (char *)(uintptr_t)ecx);
  FUN_0008dc30((char *)(uintptr_t)esi, (char *)0x0027b1f4);
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x18] -> jl 0xc4a95 */
  FUN_0008dc30((char *)(uintptr_t)esi, (char *)0x00268580);
  hs_function_table_get(eax);
  csstrcpy((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  hs_find_script_by_name((char *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0xffff -> je 0xc4b3b */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  hs_runtime_execute(0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc4bab */
  get_global_random_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  hs_return(0, 0);
  hs_macro_function_evaluate(ecx, 0, eax);
  /* test eax, eax -> je 0xc4bfc */
  get_global_random_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xed240 */
void playlist_profile_change_slayer_rules(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 2883, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xed42a */
  /* cmp edi, ebx -> jne 0xed2ac */
  display_assert((char *)0x00286a64, (char *)0x002859a4, 2891, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed2c5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed2ea */
  /* cmp esi, ebx -> jne 0xed2b3 */
  display_assert((char *)0x00286a38, (char *)0x002859a4, 2893, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed32d */
  display_assert((char *)0x002869d4, (char *)0x002859a4, 2902, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed341 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed366 */
  /* cmp esi, ebx -> jne 0xed334 */
  display_assert((char *)0x002869a8, (char *)0x002859a4, 2904, 0);
  system_exit(0);
  /* cmp eax, 0xe -> ja 0xed39e */
  /* cmp esi, ebx -> jne 0xed3ce */
  display_assert((char *)0x00286950, (char *)0x002859a4, 2916, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed3e2 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed402 */
  /* cmp esi, ebx -> jne 0xed3d5 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 2918, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xed470 */
void FUN_000ed470(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 2943, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xed75d */
  /* cmp edi, ebx -> jne 0xed4dc */
  display_assert((char *)0x00286c9c, (char *)0x002859a4, 2951, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed4f5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed51a */
  /* cmp esi, ebx -> jne 0xed4e3 */
  display_assert((char *)0x00286c70, (char *)0x002859a4, 2953, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed560 */
  display_assert((char *)0x00286c10, (char *)0x002859a4, 2962, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed574 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed599 */
  /* cmp esi, ebx -> jne 0xed567 */
  display_assert((char *)0x00286be0, (char *)0x002859a4, 2964, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed5df */
  display_assert((char *)0x00286b80, (char *)0x002859a4, 2973, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed5f3 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed618 */
  /* cmp esi, ebx -> jne 0xed5e6 */
  display_assert((char *)0x00286b54, (char *)0x002859a4, 2975, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed65e */
  display_assert((char *)0x00286af4, (char *)0x002859a4, 2984, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed672 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed697 */
  /* cmp esi, ebx -> jne 0xed665 */
  display_assert((char *)0x00286ac8, (char *)0x002859a4, 2986, 0);
  system_exit(0);
  /* cmp eax, 0x2d -> ja 0xed6d1 */
  /* cmp esi, ebx -> jne 0xed701 */
  display_assert((char *)0x00286950, (char *)0x002859a4, 2998, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed715 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed735 */
  /* cmp esi, ebx -> jne 0xed708 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 3000, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xed7c0 */
void FUN_000ed7c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 3025, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xedc69 */
  /* cmp edi, ebx -> jne 0xed82c */
  display_assert((char *)0x00287034, (char *)0x002859a4, 3033, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed86a */
  /* cmp esi, ebx -> jne 0xed838 */
  display_assert((char *)0x00287004, (char *)0x002859a4, 3035, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0xed892 */
  /* cmp edi, ebx -> jne 0xed8c2 */
  display_assert((char *)0x00286f98, (char *)0x002859a4, 3046, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed8dd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed902 */
  /* cmp esi, ebx -> jne 0xed8d0 */
  display_assert((char *)0x00286f64, (char *)0x002859a4, 3048, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0xed92a */
  /* cmp edi, ebx -> jne 0xed95a */
  display_assert((char *)0x00286efc, (char *)0x002859a4, 3059, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed96e */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed993 */
  /* cmp esi, ebx -> jne 0xed961 */
  display_assert((char *)0x00286ecc, (char *)0x002859a4, 3061, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed9e1 */
  display_assert((char *)0x00286e6c, (char *)0x002859a4, 3071, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed9f5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xeda1a */
  /* cmp esi, ebx -> jne 0xed9e8 */
  display_assert((char *)0x00286e40, (char *)0x002859a4, 3073, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xeda68 */
  display_assert((char *)0x00286de4, (char *)0x002859a4, 3083, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xeda7d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedaa2 */
  /* cmp esi, ebx -> jne 0xeda70 */
  display_assert((char *)0x00286db8, (char *)0x002859a4, 3085, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xedae5 */
  display_assert((char *)0x00286d54, (char *)0x002859a4, 3094, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedafd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedb22 */
  /* cmp esi, ebx -> jne 0xedaf0 */
  display_assert((char *)0x00286d24, (char *)0x002859a4, 3096, 0);
  system_exit(0);
  /* cmp eax, ebx -> jle 0xedb3c */
  /* cmp eax, 0x10 -> jg 0xedb3c */
  /* cmp edi, ebx -> jne 0xedb6c */
  display_assert((char *)0x00286cc0, (char *)0x002859a4, 3121, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedb80 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedba5 */
  /* cmp esi, ebx -> jne 0xedb73 */
  display_assert((char *)0x002869a8, (char *)0x002859a4, 3123, 0);
  system_exit(0);
  /* cmp eax, 0xe -> ja 0xedbdd */
  /* cmp esi, ebx -> jne 0xedc0d */
  display_assert((char *)0x00286950, (char *)0x002859a4, 3135, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedc21 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedc41 */
  /* cmp esi, ebx -> jne 0xedc14 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 3137, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf3c80 */
void FUN_000f3c80(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_loaded(0x75737472, (char *)0x002898a4);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [esi], 2 -> je 0xf3cd6 */
  display_assert((char *)0x00289860, (char *)0x00288938, 1661, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x3e0], 3 -> je 0xf3cff */
  display_assert((char *)0x00289810, (char *)0x00288938, 1662, 0);
  system_exit(0);
  FUN_000f3690(0, 0);
  /* cmp ecx, edx -> je 0xf3d24 */
  /* cmp eax, 0xc -> jl 0xf3d10 */
  multiplayer_game_set_text_box_for_teams_noteams((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp + eax*4 - 0x1c], -1 -> je 0xf41d8 */
  widget_instance_get_nth_child((void *)(uintptr_t)edi, 0);
  tag_get('aLeD', 0);
  /* test ecx, ecx -> jne 0xf3db2 */
  display_assert((char *)0x002897c8, (char *)0x00288938, 1694, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf3de8 */
  display_assert((char *)0x00289688, (char *)0x00288938, 1696, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 0 -> je 0xf3e1e */
  display_assert((char *)0x00289640, (char *)0x00288938, 1698, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf3e54 */
  display_assert((char *)0x002895f0, (char *)0x00288938, 1700, 0);
  system_exit(0);
  /* cmp edx, -1 -> je 0xf3e8d */
  /* relift: cmp dword ptr [eax], edx -> je 0xf3e81 */
  /* cmp eax, 0x5aa3a4 -> jl 0xf3e70 */
  /* test eax, eax -> je 0xf4134 */
  ui_widget_realloc(0, 256, (char *)0x00288938, 1722);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edx, 127);
  ui_widget_realloc(0, 512, (char *)0x00288938, 1729);
  /* test (char)eax, 1 -> je 0xf3f90 */
  /* cmp ecx, 4 -> ja 0xf3f51 */
  /* cmp ecx, -1 -> je 0xf3f84 */
  /* relift: cmp dword ptr [esi + 0x3c], edi -> je 0xf3f84 */
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax, 0);
  /* cmp eax, 4 -> ja 0xf41c8 */
  /* relift: cmp dword ptr [esi + 0x3c], edi -> je 0xf41c8 */
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax, 0);
  /* relift: cmp dword ptr [esi + 0x3c], edi -> je 0xf41c8 */
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)ecx, (wchar_t *)(uintptr_t)eax, 0);
  /* relift: cmp dword ptr [esi + 0x3c], edi -> je 0xf41c8 */
  FUN_0019d420(0, 0);
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax, 0);
  /* relift: cmp dword ptr [esi + 0x3c], edi -> je 0xf41c8 */
  FUN_0019d420(0, 0);
  /* relift: cmp dword ptr [esi + 0x3c], edi -> je 0xf41c8 */
  FUN_0019d420(0, 0);
  ui_widget_realloc(0, 256, (char *)0x00288938, 1873);
  ui_widget_realloc(0, 512, (char *)0x00288938, 1878);
  tag_loaded('rtsu', (char *)0x00289780);
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax, 255);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xfdc90 */
void FUN_000fdc90(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 276);
  object_get_and_verify_type(0, 0);
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xfdd1e */
  /* cmp (int16_t)eax, 3 -> je 0xfdd5a */
  /* cmp (int16_t)eax, 4 -> jne 0xfdd5e */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0xfde34 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 112);
  FUN_000fb370((void *)0, 0);
  /* test (char)eax, (char)eax -> je 0xfddb4 */
  /* relift: cmp (int16_t)edx, word ptr [ebx + 0x32e] -> jge 0xfde38 */
  /* cmp (int16_t)edi, (int16_t)edx -> jge 0xfddc9 */
  /* relift: test byte ptr [esi], 4 -> je 0xfde38 */
  /* test (char)eax, 8 -> je 0xfddea */
  /* test (char)eax, 1 -> je 0xfde38 */
  /* relift: test byte ptr [esi + 4], 1 -> jne 0xfde3b */
  /* test (char)eax, (char)eax -> jne 0xfde1b */
  /* relift: test byte ptr [edx], 2 -> je 0xfde2e */
  /* test (char)eax, (char)eax -> je 0xfde48 */
  /* relift: cmp word ptr [esi + 0xc], 0 -> jg 0xfdf32 */
  get_global_random_seed_address();
  random_seed_step((void *)(uintptr_t)eax);
  /* cmp ecx, eax -> jne 0xfdeb8 */
  /* cmp edx, edi -> jl 0xfdeca */
  /* test eax, edx -> jne 0xfdec0 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 132);
  get_global_random_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x24] -> jne 0xfde9b */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 132);
  /* test (char)eax, 0x41 -> jne 0xfdfd5 */
  /* test (char)eax, 0x41 -> jne 0xfdfd5 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0xfdff1 */
  /* test (char)eax, (char)eax -> je 0xfe00c */
  /* test (char)eax, (char)eax -> je 0xfe2ad */
  /* relift: test byte ptr [esi + 0x1a4], 2 -> je 0xfe093 */
  game_engine_running();
  /* test (char)eax, (char)eax -> je 0xfe093 */
  player_index_from_unit_index(0);
  /* cmp eax, -1 -> je 0xfe093 */
  game_engine_weapon_fired(0);
  game_time_get();
  first_person_weapon_message_from_weapon(0, 0);
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  FUN_000fb320((void *)0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 0x41 -> jne 0xfe121 */
  /* test (char)eax, 0x41 -> jne 0xfe13d */
  /* test (char)eax, 0x41 -> jne 0xfe18a */
  /* test (char)eax, 0x41 -> jne 0xfe1a3 */
  /* test edx, edx -> je 0xfe1d5 */
  /* test (char)eax, (char)eax -> jne 0xfe1d5 */
  /* test (char)eax, 0x41 -> jne 0xfe1d5 */
  weapon_set_animation_state(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0xfe209 */
  /* test (char)eax, (char)eax -> je 0xfe316 */
  /* cmp edi, -1 -> je 0xfe28f */
  /* cmp ebx, -1 -> je 0xfe28f */
  object_get_and_verify_type(0, 0);
  damage_data_new((void *)(uintptr_t)eax, 0);
  object_cause_damage((void *)(uintptr_t)ecx, 0, 0, 0, 0, 0);
  /* relift: cmp word ptr [edx + 0x4e2], 3 -> jne 0xfe2ad */
  /* relift: cmp word ptr [ebp + 0xc], 1 -> jne 0xfe2ad */
  /* test (char)eax, 0x41 -> jne 0xfe340 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  weapon_start_effect(0, 0.0f, 0.0f, 0);
  object_delete(0);
  FUN_000fd570(0, edx);
  ai_handle_unit_effect(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0xfe3a0 */
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe365 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe385 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  /* relift: cmp byte ptr [ecx + 1], 6 -> jne 0xfe3b0 */
  /* test (char)eax, (char)eax -> je 0xfe419 */
  /* relift: test byte ptr [edx], 1 -> je 0xfe40e */
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe3d3 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe3f3 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  FUN_000fcec0(0, 0, 0);
  weapon_start_effect(0, 0.0f, 0.0f, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xfe450 */
void FUN_000fe450(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_000fb370((void *)0, 0);
  /* relift: test byte ptr [edi + 0x1dc], 1 -> je 0xfe4ec */
  FUN_0018f3e0((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)0);
  /* test (char)eax, (char)eax -> jne 0xfe6b5 */
  /* test (char)eax, (char)eax -> je 0xfe6b5 */
  /* test (char)eax, (char)eax -> jne 0xfe6a5 */
  /* test (char)eax, 0x41 -> jne 0xfe623 */
  /* test (char)ecx, 8 -> je 0xfe568 */
  /* test (char)eax, 1 -> jne 0xfe568 */
  FUN_000fdc90();
  /* relift: cmp dword ptr [eax], 1 -> jle 0xfe588 */
  weapon_start_effect(0, 0.0f, 0.0f, 0);
  /* test (char)eax, 0x41 -> jne 0xfe5b3 */
  FUN_000fdc90();
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe5e5 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe605 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0xfe6a5 */
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe667 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe687 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  FUN_000fdc90();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0xfe6c0 */
void FUN_000fe6c0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 276);
  /* cmp ecx, eax -> jge 0xfe715 */
  FUN_000fdc90();
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, 2 -> jl 0xfe763 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xfe790 */
void FUN_000fe790(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0xfe85a */
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, 2 -> jl 0xfe831 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx], 1 -> jle 0xfe86d */
  FUN_000fdc90();
  FUN_000fcec0(0, 0, 0);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xfe890 */
void FUN_000fe890(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  weapon_start_effect(0, 0.0f, 0.0f, 0);
  object_delete(0);

  (void)eax;
}

/* 0xfe910 */
void FUN_000fe910(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  /* test (char)eax, (char)eax -> je 0xfe95d */
  profile_enter_private((void *)0x0031f3c0);
  /* cmp eax, -1 -> je 0xfe981 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> jne 0xfe981 */
  /* cmp eax, -1 -> je 0xfe9c1 */
  animation_update_internal(0, 0, (void *)(uintptr_t)ecx, (void *)0);
  FUN_000fd150(0);
  FUN_000fb990(0);
  /* test (char)eax, 4 -> je 0xfe9de */
  /* relift: cmp dword ptr [ebx + 0xcc], -1 -> jne 0xfe9de */
  item_detonate(0);
  /* test (char)eax, 0x41 -> jne 0xfea57 */
  /* cmp eax, -1 -> je 0xfea2e */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xfea2e */
  /* cmp eax, -1 -> je 0xfea2e */
  tag_get('tinu', 0);
  /* test ecx, 0x800000 -> jne 0xfea57 */
  /* test (char)eax, 0x41 -> jne 0xfebbf */
  /* test (char)eax, 1 -> jne 0xfead9 */
  /* test (char)eax, 1 -> jne 0xfead9 */
  /* relift: cmp word ptr [edi + 0x4e2], 3 -> jne 0xfeaaf */
  /* test (char)eax, 4 -> je 0xfeaaf */
  first_person_weapon_message_from_weapon(0, 15);
  FUN_000fb7d0(0, 0);
  /* test (char)eax, 0x41 -> jne 0xfeb23 */
  /* test (char)ecx, 1 -> je 0xfeb80 */
  /* test (char)ecx, 2 -> jne 0xfeb80 */
  /* test (char)ecx, 1 -> je 0xfebbf */
  effect_stop(0, 0);
  /* test dl, 0x10 -> jne 0xfec12 */
  /* relift: cmp word ptr [ebx + 0x1ea], 0 -> jg 0xfec12 */
  /* test (char)eax, 0x10 -> je 0xfec16 */
  /* test dl, 4 -> je 0xfec16 */
  /* test (char)ecx, (char)ecx -> je 0xfec50 */
  /* test (char)ecx, (char)ecx -> je 0xfec50 */
  /* test eax, eax -> jle 0xfec50 */
  /* relift: cmp dword ptr [ebx + 0x220], 0x3f800000 -> je 0xfec50 */
  /* test dl, 8 -> je 0xfec66 */
  /* test eax, eax -> jle 0xfec66 */
  /* relift: test byte ptr [ebx + 0x1dc], 8 -> je 0xfec7c */
  FUN_000fc990(esi, 0, 0);
  tag_get('paew', 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xfecc0 */
  /* relift: cmp edi, dword ptr [eax + 0x4f0] -> jl 0xfece0 */
  display_assert((char *)0x0028adb8, (char *)0x0028ad48, 1650, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 112);
  /* test (int16_t)eax, (int16_t)eax -> jle 0xfed47 */
  /* relift: cmp (int16_t)edi, word ptr [ecx + 0xa] -> jge 0xfed47 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jl 0xfed39 */
  /* relift: cmp word ptr [esi + 8], (int16_t)ecx -> jle 0xfed47 */
  /* test (int16_t)eax, (int16_t)eax -> je 0xfed57 */
  /* relift: cmp word ptr [esi + 2], 0 -> jne 0xfeda5 */
  FUN_000fcc90(0, 0);
  FUN_000fcbd0(eax, 0);
  /* test ecx, ecx -> jg 0xfeda5 */
  FUN_000fcaf0(0, 0);
  tag_get('paew', 0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0xfee07 */
  /* relift: cmp esi, dword ptr [eax + 0x4fc] -> jl 0xfee27 */
  display_assert((char *)0x0028ad68, (char *)0x0028ad48, 1639, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 276);
  /* relift: test byte ptr [eax + 0x1a4], 2 -> je 0xfee81 */
  /* test (char)eax, 0x41 -> jne 0xfee7b */
  /* test (char)ecx, 0x40 -> je 0xfee97 */
  /* relift: cmp dword ptr [ecx + 0xcc], -1 -> jne 0xfee97 */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0xfeea9 */
  /* relift: test byte ptr [edx], 0x10 -> je 0xfeee1 */
  /* test (char)eax, 2 -> jne 0xfeec2 */
  /* relift: cmp byte ptr [ebp + esi - 8], 0 -> je 0xfeec2 */
  /* test (char)eax, 0x41 -> jne 0xfef1c */
  /* test (char)eax, 0x41 -> jne 0xfef48 */
  /* cmp eax, 8 -> ja 0xff29b */
  /* relift: test byte ptr [ecx + 0x1e0], 0x10 -> jne 0xfefbe */
  /* relift: cmp dword ptr [edx + 0xcc], -1 -> je 0xfefbe */
  /* cmp (int16_t)eax, 0xffff -> je 0xfefbe */
  FUN_000fb370((void *)0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [eax + 0x22] -> jge 0xfef9b */
  /* relift: test byte ptr [eax], 4 -> je 0xfefa6 */
  /* relift: cmp (int16_t)ecx, word ptr [eax + 0x24] -> jl 0xfefa6 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0xfefb8 */
  FUN_000fc990(ecx, 0, 0);
  /* test (char)eax, (char)eax -> je 0xfefe6 */
  FUN_000fb5a0(0, 0);
  /* test (char)eax, (char)eax -> je 0xfefe6 */
  FUN_000fe450();
  /* cmp (char)eax, 0x7f -> jge 0xff14b */
  /* relift: cmp word ptr [edi + 2], (int16_t)ecx -> je 0xff013 */
  FUN_000fe450();
  FUN_000fcec0(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0xff03d */
  FUN_000fe450();
  /* relift: cmp word ptr [edi + 2], (int16_t)ecx -> jne 0xff14b */
  /* relift: cmp (int16_t)edx, word ptr [eax + 0x32e] -> jge 0xff14b */
  FUN_000fe6c0();
  /* relift: cmp word ptr [edi + 2], (int16_t)ecx -> je 0xff0d1 */
  /* test (char)eax, (char)eax -> jne 0xff156 */
  /* test (int16_t)ebx, (int16_t)ebx -> jne 0xff0a7 */
  /* relift: cmp dword ptr [ecx], 1 -> jle 0xff0a7 */
  /* relift: test byte ptr [edi + 4], 0x20 -> jne 0xff0a7 */
  FUN_000fe450();
  FUN_000fcdd0(0, 0);
  /* cmp eax, -1 -> je 0xff14b */
  effect_stop(0, 0);
  FUN_000fcd10(0, 0);
  /* test (char)eax, (char)eax -> je 0xff200 */
  /* relift: cmp word ptr [edi + 2], (int16_t)ecx -> je 0xff1f1 */
  FUN_000fb370((void *)0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [edx + 0x22] -> jge 0xff145 */
  /* relift: test byte ptr [eax], 4 -> jne 0xff145 */
  FUN_000fe790();
  /* test (char)eax, (char)eax -> je 0xff2bd */
  /* test (char)eax, 0x41 -> jne 0xff179 */
  /* relift: test byte ptr [edi + 4], 0x10 -> jne 0xff33a */
  /* test (char)eax, 0x41 -> jne 0xff33a */
  object_get_and_verify_type(0, 0);
  /* test dl, 1 -> je 0xff1ce */
  /* cmp eax, -1 -> je 0xff1ce */
  object_permute_region(0, (char *)(uintptr_t)eax, 0, 0);
  FUN_000fe890();
  FUN_000fe790();
  /* relift: cmp word ptr [edi + 2], (int16_t)ecx -> jne 0xff14b */
  /* relift: test byte ptr [ecx], 8 -> je 0xff273 */
  /* relift: test byte ptr [edx + 0x1a4], 2 -> je 0xff273 */
  /* relift: test byte ptr [edi + 4], 1 -> jne 0xff273 */
  FUN_000fce60(0, 0);
  /* test (char)eax, (char)eax -> je 0xff259 */
  /* relift: cmp dword ptr [eax + 0x200], -1 -> jne 0xff14b */
  FUN_000fd520(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0xff156 */
  FUN_000fcdd0(0, 0);
  /* relift: cmp word ptr [edi + 2], (int16_t)ecx -> jne 0xff14b */
  FUN_000fcdd0(0, 0);
  display_assert((char *)0, (char *)0x0028ad48, 778, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 4], 0x10 -> je 0xff33a */
  object_get_and_verify_type(0, 0);
  /* test dl, 1 -> je 0xff319 */
  /* cmp eax, -1 -> je 0xff319 */
  object_permute_region(0, (char *)(uintptr_t)eax, 0, 0);
  /* cmp (char)eax, 6 -> je 0xff36e */
  /* cmp (char)eax, 4 -> je 0xff36e */
  /* test (char)eax, (char)eax -> jne 0xff36e */
  /* test (char)eax, 0x41 -> jne 0xff38e */
  /* test (char)eax, (char)eax -> je 0xff3c7 */
  profile_exit_private((void *)0x0031f3c0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x104710 */
void FUN_00104710(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jg 0x10473d */
  display_assert((char *)0x0028bc00, (char *)0x0028b838, 428, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x104764 */
  display_assert((char *)0x0028bbf4, (char *)0x0028b838, 429, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x10478b */
  display_assert((char *)0x0028ba70, (char *)0x0028b838, 430, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1047b2 */
  display_assert((char *)0x0028bbe8, (char *)0x0028b838, 431, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x10494b */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028b934);
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028bb64);
  /* test edi, edi -> jle 0x104823 */
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028bb54);
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028bb4c);
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028bbc4);
  /* test edi, edi -> jle 0x10487a */
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028bbb8);
  /* cmp esi, edi -> jl 0x104850 */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028bb4c);
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028bb20);
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028baa8);
  /* test eax, eax -> jle 0x10492b */
  /* test eax, eax -> jle 0x10491f */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028baa4);
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028bba8);
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x00260ee4);
  /* cmp esi, eax -> jl 0x1048d0 */
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028ba88);
  crt_fflush((void *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x104950 */
void FUN_00104950(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x10497a */
  display_assert((char *)0x00263510, (char *)0x0028b838, 669, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x1049c6 */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028bc08);
  FUN_001d9850();
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x00260ee4);
  crt_fflush((void *)(uintptr_t)edx);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1049d0 */
void FUN_001049d0(float *bounds, float *color)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0026184c, (char *)0x0028b838, 491, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x104a26 */
  display_assert((char *)0x00269fd8, (char *)0x0028b838, 492, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x104bbb */
  FUN_00104240(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edi);
  FUN_00104240(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi);
  FUN_00104240(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi);
  FUN_00104240(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edi);
  FUN_00104240(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi);
  FUN_00104240(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi);
  display_assert((char *)0x0028b948, (char *)0x0028b838, 567, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x104c27 */
  display_assert((char *)0x0028b944, (char *)0x0028b838, 568, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x104c4e */
  display_assert((char *)0x00269fd8, (char *)0x0028b838, 569, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x104d2c */
  /* test (char)eax, 0x41 -> jne 0x104c6a */
  /* test (char)eax, 0x41 -> jne 0x104c81 */
  /* test (char)eax, 0x41 -> jne 0x104c9b */
  /* test (char)eax, 0x41 -> jne 0x104cb6 */
  /* test (char)eax, 0x41 -> jne 0x104cd1 */
  /* test (char)eax, 0x41 -> jne 0x104cec */
  /* relift: tail-call FUN_001049d0(); */
  FUN_00103e80((float *)(uintptr_t)esi, (float *)(uintptr_t)edi, (float *)(uintptr_t)ebx);
  display_assert((char *)0x0028b948, (char *)0x0028b838, 597, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x104d97 */
  display_assert((char *)0x0028b944, (char *)0x0028b838, 598, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x104dbe */
  display_assert((char *)0x0028ba10, (char *)0x0028b838, 599, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x104de5 */
  display_assert((char *)0x00269fd8, (char *)0x0028b838, 600, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x104f97 */
  /* test (char)eax, 0x41 -> jne 0x104e01 */
  /* test (char)eax, 0x41 -> jne 0x104e1b */
  /* test (char)eax, 0x41 -> jne 0x104e36 */
  /* test (char)eax, 0x41 -> jne 0x104e54 */
  /* test (char)eax, 0x41 -> jne 0x104e6e */
  /* test (char)eax, 0x41 -> jne 0x104e8d */
  /* test (char)eax, 0x41 -> jne 0x104ead */
  /* test (char)eax, 0x41 -> jne 0x104ed1 */
  /* test (char)eax, 0x41 -> jne 0x104eec */
  /* test (char)eax, 0x41 -> jne 0x104f0b */
  /* test (char)eax, 0x41 -> jne 0x104f2b */
  /* test (char)eax, 0x41 -> jne 0x104f4f */
  /* relift: tail-call FUN_001049d0(); */
  FUN_00104040((float *)(uintptr_t)ebx, (float *)(uintptr_t)edi, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  display_assert((char *)0x0028ba78, (char *)0x0028b838, 627, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x104ff8 */
  display_assert((char *)0x0028ba70, (char *)0x0028b838, 628, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x10501f */
  display_assert((char *)0x00269fd8, (char *)0x0028b838, 629, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 3 -> jl 0x10514a */
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x10514a */
  /* test (char)eax, 0x41 -> jne 0x105083 */
  /* test (char)eax, 0x41 -> je 0x105096 */
  /* test (char)eax, 0x41 -> jne 0x1050a9 */
  /* test (char)eax, 0x41 -> je 0x1050bc */
  /* test (char)eax, 0x41 -> jne 0x1050cd */
  /* test (char)eax, 0x41 -> je 0x1050da */
  /* relift: tail-call FUN_001049d0(); */
  FUN_00104240(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi);
  display_assert((char *)0x0026af40, (char *)0x0028b838, 107, 0);
  system_exit(0);
  valid_real_matrix4x3((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x105540 */
  csprintf((char *)0x005ab100, (char *)0x0028bd6c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d((float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x10523d */
  csprintf((char *)0x005ab100, (char *)0x0028bd4c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d((float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x105293 */
  csprintf((char *)0x005ab100, (char *)0x0028bd2c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d((float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x1052ea */
  csprintf((char *)0x005ab100, (char *)0x0028bd10);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_point3d((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x105341 */
  csprintf((char *)0x005ab100, (char *)0x0028bcec);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp edx, 0x7f800000 -> je 0x10537b */
  csprintf((char *)0x005ab100, (char *)0x0028bca8);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp eax, 0x7f800000 -> je 0x10540f */
  csprintf((char *)0x005ab100, (char *)0x0028bc6c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp ecx, 0x7f800000 -> je 0x1054a5 */
  csprintf((char *)0x005ab100, (char *)0x0028bc2c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_matrix4x3((float *)(uintptr_t)esi);
  csprintf((char *)0x005ab100, (char *)0x0028bc0c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  display_assert((char *)0x0025bb20, (char *)0x0028b838, 119, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1055a0 */
  display_assert((char *)0x00269fd8, (char *)0x0028b838, 120, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x1055fc */
  /* relift: tail-call FUN_001049d0(); */
  display_assert((char *)0x0025bb20, (char *)0x0028b838, 539, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x105666 */
  display_assert((char *)0x00269fd8, (char *)0x0028b838, 540, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x1056d9 */
  /* relift: tail-call FUN_001049d0(); */
  FUN_00105550((float *)(uintptr_t)esi, (float *)(uintptr_t)edi);
  /* test esi, esi -> jne 0x105708 */
  display_assert((char *)0x0028be3c, (char *)0x0028be44, 117, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x10572c */
  display_assert((char *)0x0028be28, (char *)0x0028be44, 118, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x105750 */
  display_assert((char *)0x0028be00, (char *)0x0028be44, 119, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)eax, (char *)0x0028be44, 121);
  debug_free((void *)(uintptr_t)ecx, (char *)0x0028be44, 122);
  debug_free((void *)(uintptr_t)esi, (char *)0x0028be44, 123);
  /* cmp (int16_t)eax, (int16_t)ecx -> jl 0x105885 */
  display_assert((char *)0x0028befc, (char *)0x0028be44, 315, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x105890 */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0xc] -> jle 0x1058b0 */
  display_assert((char *)0x0028becc, (char *)0x0028be44, 316, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1058bb */
  /* relift: cmp (int16_t)esi, word ptr [edi + 0xc] -> jle 0x1058db */
  display_assert((char *)0x0028be9c, (char *)0x0028be44, 317, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1058ea */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jle 0x10590a */
  display_assert((char *)0x0028be64, (char *)0x0028be44, 318, 0);
  system_exit(0);
  normalize3d((float *)(uintptr_t)ecx);
  display_assert((char *)0x0028bf58, (char *)0x0028be44, 346, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x28], 2 -> jg 0x1059e4 */
  display_assert((char *)0x0028bf3c, (char *)0x0028be44, 347, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x20] -> jne 0x105b6e */
  rotate_vector3d_by_sincos((float *)(uintptr_t)esi, (float *)(uintptr_t)edx, 0.0f, 0.0f);
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  /* relift: cmp (int16_t)edi, word ptr [ebp + 8] -> jge 0x105d0f */
  /* cmp eax, -1 -> je 0x105cf6 */
  /* test eax, eax -> je 0x105cd4 */
  /* cmp eax, 1 -> jne 0x105d08 */
  plane2d_from_points((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x105d08 */
  /* cmp (int16_t)esi, 2 -> jl 0x105c90 */
  shell_update(0, (float *)(uintptr_t)edi);
  /* cmp (int16_t)eax, 2 -> jne 0x105f23 */
  /* test (char)eax, 0x41 -> je 0x105dc6 */
  /* test (char)eax, 0x41 -> je 0x105dc6 */
  /* test (char)eax, 0x41 -> jne 0x105dd3 */
  /* test (char)eax, 0x41 -> jne 0x105dd3 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 8] -> jl 0x105d70 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x105e80 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 8] -> jl 0x105e12 */
  /* test (char)eax, 1 -> jne 0x105ecd */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x105f21 */
  /* test (char)ecx, (char)ecx -> je 0x105de0 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x105ff7 */
  /* relift: cmp word ptr [ecx + edi*2], (int16_t)edx -> je 0x105f64 */
  /* test (int16_t)esi, (int16_t)esi -> jg 0x105f50 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 8] -> jl 0x105fa6 */
  display_assert((char *)0x0028bfb8, (char *)0x0028be44, 633, 0);
  system_exit(0);
  /* cmp ebx, eax -> jl 0x105fce */
  display_assert((char *)0x0028bf88, (char *)0x0028be44, 634, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jg 0x105f23 */
  display_assert((char *)0x0028bf70, (char *)0x0028be44, 642, 0);
  system_exit(0);
  /* test eax, eax -> jge 0x10606d */
  FUN_0010c440((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x1061e3 */
  /* cmp (int16_t)edx, 2 -> jle 0x10637e */
  /* test (char)eax, 0x41 -> jne 0x10649b */
  /* test (char)eax, 0x41 -> jne 0x1064ac */
  /* test (char)eax, 0x41 -> jne 0x1064d1 */
  /* test eax, eax -> je 0x1064ee */
  /* test eax, eax -> je 0x1064fa */
  FUN_001d90e0();
  display_assert((char *)0x0028c010, (char *)0x0028be44, 1350, 0);
  system_exit(0);
  /* cmp eax, edi -> je 0x106560 */
  /* relift: cmp dword ptr [ebp + 0xc], esi -> jne 0x1065b2 */
  /* cmp (int16_t)ebx, 0x200 -> jle 0x10658f */
  display_assert((char *)0x0028bff8, (char *)0x0028be44, 1357, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* test (char)eax, 1 -> je 0x1065ec */
  /* test (char)eax, 1 -> je 0x10662e */
  /* test (char)eax, 0x41 -> jne 0x106640 */
  /* relift: cmp (char)eax, byte ptr [ebp - 1] -> je 0x106756 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0x14] -> je 0x106859 */
  /* test eax, eax -> je 0x106674 */
  /* test (char)eax, 0x41 -> jne 0x1066cb */
  /* test (char)eax, 0x41 -> jne 0x106726 */
  /* test (char)eax, 0x41 -> je 0x106752 */
  /* test (char)eax, 0x41 -> jne 0x106753 */
  /* test (char)eax, 0x41 -> jne 0x106753 */
  /* test (char)eax, (char)eax -> je 0x106821 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0x14] -> je 0x106859 */
  /* test eax, eax -> je 0x1067ab */
  /* test eax, eax -> je 0x1067ab */
  /* test (char)eax, 0x41 -> jne 0x1067f1 */
  /* test (char)eax, 0x41 -> je 0x10681d */
  /* test (char)eax, 0x41 -> jne 0x10681e */
  /* test (char)eax, 0x41 -> jne 0x10681e */
  /* cmp (int16_t)edi, -1 -> je 0x10685f */
  /* test (char)eax, (char)eax -> jne 0x1068b1 */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x10686a */
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 0x14] -> jle 0x10688a */
  display_assert((char *)0x0028bfd4, (char *)0x0028be44, 1448, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)edx, ecx);
  /* test eax, eax -> je 0x1068a7 */
  /* test (char)eax, (char)eax -> jne 0x10689b */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1068c3 */
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 0x14] -> jle 0x1068e6 */
  display_assert((char *)0x0028bfd4, (char *)0x0028be44, 1441, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, edx);
  /* cmp edi, 0x7f800000 -> je 0x10694e */
  /* cmp eax, 0x7f800000 -> je 0x10694e */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x106914 */
  FUN_001d90e0();
  display_assert((char *)0x0028c010, (char *)0x0028be44, 1493, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1069ad */
  /* relift: cmp eax, dword ptr [ebp + 0x18] -> jne 0x106a02 */
  /* cmp (int16_t)edi, 0x200 -> jle 0x1069dc */
  display_assert((char *)0x0028bff8, (char *)0x0028be44, 1500, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  /* test (char)eax, 1 -> jne 0x106a40 */
  /* test (char)eax, 1 -> je 0x106a8d */
  /* test (char)eax, 0x41 -> jne 0x106a9f */
  /* relift: cmp byte ptr [ebp + 0x13], (char)ebx -> je 0x106c04 */
  /* relift: cmp (int16_t)esi, word ptr [ebp + 0x14] -> je 0x106d18 */
  /* test eax, eax -> je 0x106ad0 */
  /* test (char)eax, 0x41 -> jne 0x106b3d */
  /* test (char)eax, 0x41 -> jne 0x106bc0 */
  /* test (char)eax, 0x41 -> jne 0x106bc0 */
  /* test (char)eax, 0x41 -> je 0x106c03 */
  /* test (char)eax, 0x41 -> jne 0x106c04 */
  /* test (char)eax, 0x41 -> jne 0x106c04 */
  /* test (char)eax, 0x41 -> jne 0x106c04 */
  /* test (char)eax, (char)eax -> je 0x106cd3 */
  /* relift: cmp (int16_t)esi, word ptr [ebp + 0x14] -> jge 0x106d18 */
  /* test (char)eax, 0x41 -> jne 0x106c8f */
  /* test (char)eax, 0x41 -> jne 0x106c8f */
  /* test (char)eax, 0x41 -> je 0x106cd2 */
  /* test (char)eax, 0x41 -> jne 0x106cd3 */
  /* test (char)eax, 0x41 -> jne 0x106cd3 */
  /* test (char)eax, 0x41 -> jne 0x106cd3 */
  /* cmp (int16_t)esi, -1 -> je 0x106d1b */
  /* test (char)eax, (char)eax -> jne 0x106d0f */
  /* test (char)eax, (char)eax -> jne 0x106d6b */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x106d29 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x14] -> jle 0x106d49 */
  display_assert((char *)0x0028bfd4, (char *)0x0028be44, 1591, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* test (char)eax, (char)eax -> jne 0x106d5d */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x106d79 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x14] -> jle 0x106d9c */
  display_assert((char *)0x0028bfd4, (char *)0x0028be44, 1584, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, ecx);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x106e49 */
  /* cmp ebx, 0x7f800000 -> je 0x106f3a */
  /* cmp ebx, 0x7f800000 -> je 0x106f3a */
  /* cmp ebx, 0x7f800000 -> je 0x106f3a */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x106e38 */
  display_assert((char *)0x0028ba70, (char *)0x0028be44, 1710, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x106fb4 */
  display_assert((char *)0x0028c050, (char *)0x0028be44, 1711, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x106fda */
  display_assert((char *)0x0028c048, (char *)0x0028be44, 1712, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x107001 */
  display_assert((char *)0x0028c03c, (char *)0x0028be44, 1713, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], (int16_t)eax -> jl 0x107514 */
  /* relift: cmp word ptr [ebp + 0x18], 6 -> jl 0x107514 */
  /* relift: cmp word ptr [ebp + 0x20], (int16_t)eax -> jl 0x107514 */
  /* relift: cmp word ptr [ebp + 8], (int16_t)ecx -> jle 0x107512 */
  /* test (char)eax, 0x41 -> jne 0x107050 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp + 8] -> jl 0x107040 */
  /* cmp (int16_t)eax, 0xffff -> je 0x107514 */
  /* cmp (int16_t)edx, -1 -> je 0x107512 */
  /* test (char)eax, 0x41 -> jne 0x107203 */
  /* cmp (int16_t)edx, -1 -> je 0x107512 */
  FUN_001037b0((float *)(uintptr_t)ecx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* relift: cmp word ptr [ebp - 0xc], -1 -> je 0x107514 */
  /* test (char)eax, 0x41 -> je 0x107514 */
  /* test (char)eax, 0x41 -> jne 0x1072f3 */
  FUN_001037b0((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)ecx);
  FUN_001037b0((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_001037b0((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_001037b0((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 6 -> jle 0x1074e9 */
  /* cmp (int16_t)eax, 4 -> jle 0x107509 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x107520 */
void FUN_00107520(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test esi, esi -> jne 0x107552 */
  display_assert((char *)0x0028ba70, (char *)0x0028be44, 1973, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x107578 */
  display_assert((char *)0x0028c050, (char *)0x0028be44, 1974, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x10759e */
  display_assert((char *)0x0028c048, (char *)0x0028be44, 1975, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1075c4 */
  display_assert((char *)0x0028c03c, (char *)0x0028be44, 1976, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1078c2 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 8] -> jge 0x1078c2 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x107627 */
  /* test (char)eax, 0x41 -> je 0x107636 */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x1075f5 */
  /* test (char)eax, (char)eax -> je 0x10767b */
  /* test (char)eax, (char)eax -> je 0x10771f */
  /* test edx, edx -> jl 0x1078c2 */
  /* cmp edx, ebx -> jge 0x1078c2 */
  /* test edi, edi -> jl 0x1078c2 */
  /* cmp edi, ebx -> jge 0x1078c2 */
  /* relift: cmp byte ptr [eax], 0 -> jne 0x1076e8 */
  /* relift: cmp byte ptr [ecx], 0 -> jne 0x1076e8 */
  /* relift: cmp (char)eax, byte ptr [ecx] -> je 0x107719 */
  /* test (char)eax, (char)eax -> jne 0x107705 */
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)edi -> jne 0x107755 */
  display_assert((char *)0x0028c258, (char *)0x0028be44, 2076, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], 0 -> jle 0x107894 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1077ad */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0x18] -> jl 0x1077d3 */
  display_assert((char *)0x0028c230, (char *)0x0028be44, 2098, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 4], ecx -> je 0x107803 */
  /* relift: cmp dword ptr [esi + 8], ecx -> je 0x107803 */
  display_assert((char *)0x0028c1e0, (char *)0x0028be44, 2099, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi], 0 -> je 0x10782f */
  /* cmp (int16_t)eax, 0xffff -> jne 0x107813 */
  /* cmp ebx, esi -> jne 0x107798 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x10785a */
  /* relift: cmp byte ptr [esi + edx*4], 0 -> je 0x1078cb */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x1078b0 */
  /* cmp (int16_t)ecx, (int16_t)edi -> jge 0x1078c2 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1078ef */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x18] -> jl 0x10790f */
  display_assert((char *)0x0028c230, (char *)0x0028be44, 2167, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x107934 */
  display_assert((char *)0x0028c1cc, (char *)0x0028be44, 2168, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x107943 */
  /* cmp eax, edx -> jl 0x107963 */
  display_assert((char *)0x0028c188, (char *)0x0028be44, 2169, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x107972 */
  /* cmp eax, ecx -> jl 0x107992 */
  display_assert((char *)0x0028c140, (char *)0x0028be44, 2170, 0);
  system_exit(0);
  /* cmp edx, ecx -> jne 0x1079cd */
  display_assert((char *)0x0028c0f8, (char *)0x0028be44, 2171, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edx + edi], 0 -> je 0x1079f1 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jl 0x1079d3 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jge 0x1078c2 */
  /* relift: cmp byte ptr [ebx + edi], 0 -> je 0x107a2e */
  /* cmp (int16_t)ecx, (int16_t)edx -> jge 0x1078c2 */
  display_assert((char *)0x0028c0e4, (char *)0x0028be44, 2206, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x107aac */
  /* relift: cmp (int16_t)ecx, word ptr [ebp + 8] -> jl 0x107acc */
  display_assert((char *)0x0028c0a8, (char *)0x0028be44, 2207, 0);
  system_exit(0);
  /* relift: cmp byte ptr [eax], 0 -> jne 0x107af4 */
  display_assert((char *)0x0028c098, (char *)0x0028be44, 2209, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x107b06 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 8] -> jl 0x107b26 */
  display_assert((char *)0x0028c05c, (char *)0x0028be44, 2210, 0);
  system_exit(0);
  FUN_001037b0((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test eax, eax -> jne 0x107c5a */
  display_assert((char *)0x0028ba70, (char *)0x0028be44, 2284, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x107c84 */
  display_assert((char *)0x0028c050, (char *)0x0028be44, 2285, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x107cab */
  display_assert((char *)0x0028c048, (char *)0x0028be44, 2286, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x107cd2 */
  display_assert((char *)0x0028c03c, (char *)0x0028be44, 2287, 0);
  system_exit(0);
  FUN_00106f50(esi, (float *)(uintptr_t)eax, edx, (char *)(uintptr_t)edi, ecx, (char *)(uintptr_t)esi, eax, (char *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x107d34 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x107d2d */
  /* relift: tail-call FUN_00107520(); */
  /* test (char)eax, (char)eax -> je 0x107d34 */
  /* cmp (int16_t)edi, (int16_t)esi -> jl 0x107d00 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x107d92 */
  /* test (char)eax, 0x41 -> je 0x107d9f */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x107d60 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x107e8a */
  /* test (char)eax, 0x41 -> jne 0x107e5c */
  /* test (char)eax, 0x41 -> jne 0x107e73 */
  /* test (char)eax, 0x41 -> je 0x107eb5 */
  /* cmp (int16_t)ecx, (int16_t)ebx -> jl 0x107de0 */
  /* test eax, eax -> je 0x107ea0 */
  /* test eax, eax -> je 0x107eac */
  /* test edi, edi -> jne 0x107f13 */
  display_assert((char *)0x0028be3c, (char *)0x0028be44, 269, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x107f21 */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0xc] -> jl 0x107f44 */
  display_assert((char *)0x0028c2ac, (char *)0x0028be44, 270, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x107f4f */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0xc] -> jl 0x107f72 */
  display_assert((char *)0x0028c284, (char *)0x0028be44, 271, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 8] -> jne 0x107f9b */
  display_assert((char *)0x0028c278, (char *)0x0028be44, 272, 0);
  system_exit(0);
  /* test (int16_t)edx, (int16_t)edx -> jne 0x107fb8 */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> je 0x10804b */
  /* relift: cmp word ptr [edi], (int16_t)esi -> jle 0x108024 */
  calculate_vertex(0, 0, 0, 0, (void *)0, 0);
  /* relift: cmp (int16_t)esi, word ptr [edi] -> jl 0x107ff0 */
  /* test (char)ecx, (char)ecx -> je 0x108041 */
  FUN_001d90e0();
  display_assert((char *)0x0028c330, (char *)0x0028be44, 1016, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1080c8 */
  display_assert((char *)0x0026856c, (char *)0x0028be44, 1017, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jne 0x1080f0 */
  display_assert((char *)0x0028c328, (char *)0x0028be44, 1018, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x108114 */
  display_assert((char *)0x0028c324, (char *)0x0028be44, 1019, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x108139 */
  display_assert((char *)0x0028c31c, (char *)0x0028be44, 1020, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x108160 */
  display_assert((char *)0x0025f120, (char *)0x0028be44, 1021, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], eax -> je 0x10816c */
  /* cmp ebx, eax -> jne 0x10818c */
  display_assert((char *)0x0028c304, (char *)0x0028be44, 1022, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jg 0x1081a0 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x108193 */
  /* cmp eax, edx -> jne 0x1081c0 */
  plane2d_from_points((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test eax, eax -> je 0x10821d */
  convex_polygon2d_clip_to_plane(edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, eax, (float *)(uintptr_t)esi, (void *)0, (void *)0, 0.0f);
  /* cmp (int16_t)edi, -1 -> jne 0x108257 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0x18] -> jle 0x108243 */
  display_assert((char *)0x0028c2d4, (char *)0x0028be44, 1037, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, eax);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108297 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jle 0x1082b7 */
  display_assert((char *)0x0028c3a0, (char *)0x0028be44, 222, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1082c5 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jle 0x1082e8 */
  display_assert((char *)0x0028c378, (char *)0x0028be44, 223, 0);
  system_exit(0);
  /* test (int16_t)edx, (int16_t)edx -> jl 0x1082f6 */
  /* relift: cmp (int16_t)edx, word ptr [edi + 0xc] -> jle 0x10831c */
  display_assert((char *)0x0028c350, (char *)0x0028be44, 224, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x108356 */
  get_edge_vertex();
  /* relift: cmp (int16_t)ebx, word ptr [edi] -> jne 0x108378 */
  get_edge_vertex();
  get_edge_vertex();
  get_edge_vertex();
  get_edge_vertex();
  calculate_vertex(0, 0, 0, 0, (void *)0, 0);
  /* test eax, eax -> jne 0x10843b */
  display_assert((char *)0x0028c5d8, (char *)0x0028be44, 146, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x108462 */
  display_assert((char *)0x0028c5b4, (char *)0x0028be44, 147, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x108489 */
  display_assert((char *)0x0028c598, (char *)0x0028be44, 148, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108497 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jl 0x1084b7 */
  display_assert((char *)0x0028c570, (char *)0x0028be44, 149, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1084c5 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jl 0x1084e5 */
  display_assert((char *)0x0028c548, (char *)0x0028be44, 150, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1084f3 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jl 0x108513 */
  display_assert((char *)0x0028c520, (char *)0x0028be44, 151, 0);
  system_exit(0);
  /* cmp ecx, eax -> jl 0x108541 */
  display_assert((char *)0x0028c4b8, (char *)0x0028be44, 152, 0);
  system_exit(0);
  debug_malloc(edx, 0, (char *)0, 0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x10857e */
  get_face_vertex();
  get_face_vertex();
  get_face_vertex();
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jle 0x10866a */
  display_assert((char *)0x0028c47c, (char *)0x0028be44, 176, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108678 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jle 0x108698 */
  display_assert((char *)0x0028c444, (char *)0x0028be44, 177, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1086a3 */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0xc] -> jle 0x1086c3 */
  display_assert((char *)0x0028c408, (char *)0x0028be44, 178, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jge 0x10876c */
  get_face_vertex();
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jle 0x10875c */
  display_assert((char *)0x0028c3c8, (char *)0x0028be44, 194, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jle 0x1085c0 */
  debug_free((void *)(uintptr_t)edx, (char *)0x0028be44, 200);
  debug_malloc(20, edi, (char *)0x0028be44, 58);
  /* cmp esi, edi -> je 0x108995 */
  debug_malloc(edx, edi, (char *)0, 0);
  debug_malloc(eax, edi, (char *)0, 0);
  debug_malloc(128, edi, (char *)0x0028be44, 69);
  /* relift: cmp dword ptr [esi + 8], edi -> je 0x108956 */
  /* cmp ebx, edi -> je 0x108956 */
  subdivide_triangle();
  /* cmp ecx, eax -> jl 0x10892d */
  display_assert((char *)0x0028c610, (char *)0x0028be44, 98, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xc] -> je 0x108981 */
  display_assert((char *)0x0028c5e8, (char *)0x0028be44, 99, 0);
  system_exit(0);
  /* cmp eax, edi -> je 0x10896a */
  debug_free((void *)(uintptr_t)eax, (char *)0x0028be44, 103);
  /* cmp eax, edi -> je 0x108981 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0028be44, 104);
  /* test ebx, ebx -> je 0x108995 */
  debug_free((void *)(uintptr_t)ebx, (char *)0x0028be44, 107);
  csprintf((char *)0x005ab100, (char *)0x0028c678);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  /* cmp (int16_t)eax, (int16_t)edx -> jge 0x108c44 */
  csmemset((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)esi, (int16_t)edi -> jle 0x108cac */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 2] -> jl 0x108cfc */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 6] -> jge 0x108cfc */
  /* relift: cmp (int16_t)edx, word ptr [ecx] -> jl 0x108cfc */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 4] -> jge 0x108cfc */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 2] -> jl 0x108d36 */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 6] -> jg 0x108d36 */
  /* relift: cmp (int16_t)edx, word ptr [ecx] -> jl 0x108d36 */
  /* relift: cmp (int16_t)eax, word ptr [ecx + 4] -> jg 0x108d36 */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 2] -> jne 0x108d76 */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 6] -> jne 0x108d76 */
  /* relift: cmp (int16_t)edx, word ptr [ecx] -> jne 0x108d76 */
  /* relift: cmp (int16_t)eax, word ptr [ecx + 4] -> jne 0x108d76 */
  /* relift: cmp (int16_t)edx, word ptr [ecx] -> jne 0x108da2 */
  /* relift: cmp (int16_t)eax, word ptr [ecx + 2] -> jne 0x108da2 */
  /* test ecx, ecx -> jbe 0x108dc9 */
  /* cmp ecx, 1 -> je 0x108dc9 */
  /* cmp ecx, 1 -> jne 0x108dc1 */
  /* test eax, eax -> jbe 0x108dea */
  /* cmp eax, 1 -> je 0x108dea */
  /* cmp eax, 1 -> jne 0x108de2 */
  /* cmp ecx, edx -> jle 0x108e06 */
  /* cmp ecx, eax -> jle 0x108e36 */
  /* cmp eax, ecx -> jl 0x108e30 */
  /* cmp ecx, esi -> ja 0x108e5c */
  /* test edx, edx -> jne 0x108e50 */
  /* test esi, esi -> jne 0x108eaa */
  display_assert((char *)0x0028c6c8, (char *)0x0028c6a4, 348, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108ef4 */
  /* test ebx, ebx -> je 0x108edc */
  /* test eax, eax -> je 0x108ee4 */
  /* test edi, edi -> jne 0x108f34 */
  display_assert((char *)0x0028c6c8, (char *)0x0028c6a4, 369, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x108f5b */
  display_assert((char *)0x0025f120, (char *)0x0028c6a4, 370, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x108f8e */
  /* test edi, edi -> je 0x108fb3 */
  /* test esi, esi -> jne 0x108fd3 */
  display_assert((char *)0x0028c6d4, (char *)0x0028c6a4, 387, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x108ffe */
  /* cmp eax, esi -> jle 0x109071 */
  csmemset((void *)(uintptr_t)edx, 0, 52);
  FUN_001093b0((float *)(uintptr_t)edx, (float *)(uintptr_t)eax);
  FUN_001093b0((float *)(uintptr_t)esi, (float *)(uintptr_t)edx);
  /* cmp eax, 0x3f800000 -> je 0x1095b8 */
  /* cmp eax, 0x3f800000 -> je 0x109638 */
  /* cmp eax, 0x3f800000 -> je 0x1097ac */
  /* cmp ecx, eax -> jne 0x109a23 */
  display_assert((char *)0x0028c6e8, (char *)0x0028c704, 787, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 2 -> jge 0x109aeb */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x109af5 */
  /* cmp (int16_t)ecx, 2 -> jge 0x109b05 */
  /* cmp esi, eax -> jne 0x109ca5 */
  /* cmp ecx, eax -> jne 0x109db4 */
  FUN_001da0cc();
  /* test (char)eax, 0x41 -> jne 0x109f9d */
  /* test (char)eax, 0x41 -> jne 0x10a021 */
  /* test (char)eax, 0x41 -> jne 0x10a037 */
  /* test (char)eax, 0x41 -> jne 0x10a050 */
  matrix_from_forward_and_up((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_inverse((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix4x3_multiply((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_00109fc0((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_0010caf0((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)esi);
  real_matrix3x3_transform_vector((void *)0, (void *)0, (void *)0);
  real_matrix3x3_transform_vector((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  real_matrix3x3_transform_vector((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x10a390 */
  /* test (char)eax, 0x41 -> jne 0x10a3a5 */
  /* test (char)eax, 0x41 -> jne 0x10a3bd */
  valid_real_normal3d((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x10a4b5 */
  valid_real_normal3d((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x10a4ed */
  display_assert((char *)0x0028c730, (char *)0x0028c704, 370, 0);
  system_exit(0);
  perpendicular3d((float *)(uintptr_t)esi, (float *)(uintptr_t)edx);
  normalize3d((float *)(uintptr_t)eax);
  matrix_from_forward_and_up((float *)0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x10a5d4 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0028c80c, 122);
  debug_free((void *)(uintptr_t)ecx, (char *)0x0028c80c, 132);
  /* test (int16_t)esi, (int16_t)esi -> jne 0x10a5fb */
  /* cmp (int16_t)esi, 0xc -> jl 0x10a623 */
  display_assert((char *)0x0028c83c, (char *)0x0028c80c, 157, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x10a6fc */
  FUN_001daf7e();
  /* test (char)eax, 0x41 -> jne 0x10a6bf */
  /* test (char)eax, 0x41 -> jne 0x10a702 */
  /* test (char)eax, 0x41 -> jne 0x10a744 */
  /* test (int16_t)esi, (int16_t)esi -> jne 0x10a756 */
  /* cmp (int16_t)esi, 6 -> jl 0x10a77e */
  display_assert((char *)0x0028c880, (char *)0x0028c80c, 216, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x10a81d */
  FUN_001daf7e();
  /* cmp (int16_t)eax, 0x3ff -> jne 0x10a7e2 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  FUN_001d9e70(0.0f, 0.0f);
  FUN_001d9e70(0.0f, 0.0f);
  FUN_001d9e70(0.0f, 0.0f);
  FUN_001d9e70(0.0f, 0.0f);
  display_assert((char *)0, (char *)0x0028c80c, 411, 0);
  system_exit(0);
  FUN_001d9068();
  /* test eax, eax -> jge 0x10aa18 */
  /* cmp eax, 0xff -> jle 0x10aa24 */
  FUN_001d90e0();
  FUN_0010a830((float *)(uintptr_t)edi);
  FUN_001daf7e();
  FUN_001daf7e();
  FUN_001daf7e();
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  FUN_001daf7e();
  display_assert((char *)0, (char *)0x0028c80c, 499, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x10ac3c */
  /* test dl, 0xc0 -> je 0x10ac7a */
  FUN_001d9068();
  /* test eax, eax -> jge 0x10acb7 */
  /* cmp eax, 0xff -> jle 0x10acc3 */
  display_assert((char *)0x0028c8f8, (char *)0x0028c80c, 67, 0);
  system_exit(0);
  get_global_random_seed_address();
  debug_malloc(1024, ebx, (char *)0x0028c80c, 78);
  FUN_0010aa60(0, (void *)(uintptr_t)eax);
  /* cmp (int16_t)edi, 0xc -> jl 0x10ad54 */
  debug_malloc(1024, ebx, (char *)0x0028c80c, 96);
  FUN_0010a930(eax, (void *)0);
  /* cmp (int16_t)edi, 6 -> jl 0x10ad92 */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x10adfa */
  /* cmp (int16_t)edx, (int16_t)eax -> jle 0x10adfa */
  /* cmp (int16_t)ecx, (int16_t)edx -> jl 0x10ae2c */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x10ae2c */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x10ae77 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x10ae77 */
  /* cmp eax, edx -> jle 0x10ae58 */
  FUN_0010ae00(0, 0);
  /* cmp (int16_t)esi, 1 -> jle 0x10ae77 */
  display_assert((char *)0x0028c920, (char *)0x0028c928, 77, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jg 0x10aed1 */
  display_assert((char *)0x00257c5c, (char *)0x0028c928, 78, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x10aef5 */
  display_assert((char *)0x0028c918, (char *)0x0028c928, 79, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x10af17 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x10af53 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jge 0x10af53 */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x10af00 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x10af34 */
  /* cmp edx, ecx -> jl 0x10af3b */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x10af23 */
  /* cmp (int16_t)eax, (int16_t)esi -> jge 0x10af61 */
  display_assert((char *)0x0028c94c, (char *)0x0028c928, 119, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jg 0x10afc1 */
  display_assert((char *)0x00257c5c, (char *)0x0028c928, 120, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x10afe5 */
  display_assert((char *)0x0028c918, (char *)0x0028c928, 121, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x10b014 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x10b044 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jge 0x10b044 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x10b00e */
  /* relift: cmp (int16_t)eax, word ptr [edx - 2] -> jle 0x10b044 */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x10aff0 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x10b03d */
  /* cmp ecx, ebx -> jl 0x10b05b */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x10b025 */
  /* cmp (int16_t)eax, (int16_t)esi -> jl 0x10b048 */
  /* cmp (int16_t)eax, (int16_t)esi -> jge 0x10b085 */
  /* test eax, eax -> jg 0x10b0c6 */
  display_assert((char *)0x0028c958, (char *)0x0028c98c, 41, 0);
  system_exit(0);
  game_engine_running();
  /* test (char)eax, (char)eax -> je 0x10b0ff */
  /* test eax, eax -> je 0x10b0ff */
  display_assert((char *)0x0028c9b0, (char *)0x0028c98c, 56, 0);
  system_exit(0);
  system_seconds();
  system_milliseconds();
  rand();
  system_seconds();
  system_milliseconds();
  rand();
  /* mem[0x0046e3f8] = esi */
  FUN_001087b0(16);
  /* test esi, esi -> jne 0x10b1ac */
  display_assert((char *)0x0028c9f4, (char *)0x0028c98c, 174, 0);
  system_exit(0);
  debug_malloc(eax, 0, (char *)0, 0);
  /* mem[0x0046e3e8] = eax */
  /* relift: cmp word ptr [esi + 0xc], (int16_t)ecx -> jle 0x10b212 */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 0xc] -> jl 0x10b1e4 */
  FUN_001056e0((void *)(uintptr_t)esi);
  debug_free((void *)(uintptr_t)eax, (char *)0x0028c98c, 200);
  display_assert((char *)0x0028ca54, (char *)0x0028c98c, 250, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x10b341 */
  /* relift: cmp (int16_t)esi, word ptr [0x46e3ec] -> jl 0x10b361 */
  display_assert((char *)0x0028ca10, (char *)0x0028c98c, 251, 0);
  system_exit(0);
  random_direction_table_get_element(0, (float *)0);
  FUN_0010c690((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, 0.0f);
  random_direction_table_get_element(0, (float *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x132ca0 */
void FUN_00132ca0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  global_scenario_get();
  /* cmp ecx, -1 -> je 0x132e0c */
  tag_get('galf', 0);
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edx, 0xe1 -> jge 0x132e06 */
  /* cmp (int16_t)eax, 0x28 -> jge 0x132e06 */
  /* cmp ecx, eax -> je 0x132e06 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> jle 0x132dd8 */
  FUN_00131840();
  /* cmp eax, ecx -> jge 0x132dcf */
  /* cmp eax, edx -> jge 0x132dcf */
  telnet_console_print();
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0xe] -> jl 0x132d60 */
  FUN_00131e00();
  FUN_00131ed0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x132e20 */
void FUN_00132e20(void)
{
  int eax = 0;
  int ecx = 0;

  object_get_and_verify_type(0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('galf', 0);
  /* test (char)eax, (char)eax -> jne 0x132e7a */
  FUN_00131fc0();
  flag_render_proper();

  (void)eax;
  (void)ecx;
}

/* 0x132ea0 */
void FUN_00132ea0(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x132f2e */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('galf', 0);
  /* cmp (int16_t)eax, 5 -> jge 0x132f16 */
  FUN_00131fc0();
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp edi, -1 -> jne 0x132ec0 */
  /* test eax, eax -> je 0x132f62 */
  data_delete_all((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x132f72 */
  data_delete_all((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x132f92 */
  data_make_invalid((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x132fa2 */
  data_make_invalid((void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x132fb0 */
void FUN_00132fb0(void)
{
  int eax = 0;
  int ecx = 0;

  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!wlg', 0);
  tag_get('mtib', 0);
  /* relift: cmp word ptr [eax], 3 -> jne 0x133088 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00077040(0, 0, 0);
  FUN_001d9068();

  (void)eax;
  (void)ecx;
}

/* 0x1330a0 */
void FUN_001330a0(void)
{
  int eax = 0;
  int edx = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1330de */
  datum_delete((void *)(uintptr_t)edx, 0);
  datum_delete((void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)edx;
}

/* 0x1330f0 */
#if 0 /* ported in objects.c */
void FUN_001330f0(int glow_widget)
{
  int eax = 0;
  int ecx = 0;

  tag_get(0x676c7721, 0);
  /* test (char)ecx, 8 -> je 0x133165 */
  /* test (char)eax, 0x41 -> jne 0x13315e */

  (void)eax;
  (void)ecx;
}
#endif

/* 0x133170 */
void FUN_00133170(void)
{
  int eax = 0;
  int ecx = 0;

  tag_get(0x676c7721, 0);
  /* test (char)ecx, 0x10 -> je 0x1331c7 */
  /* test (char)eax, 0x41 -> jne 0x1331c1 */

  (void)eax;
  (void)ecx;
}

/* 0x1331d0 */
#if 0 /* ported in objects.c */
void FUN_001331d0(int glow_widget, int particle_ptr)
{
  int eax = 0;
  int ecx = 0;

  tag_get(0x676c7721, 0);
  /* test (char)ecx, 0x20 -> je 0x13323f */
  /* test (char)eax, 0x41 -> jne 0x133224 */

  (void)eax;
  (void)ecx;
}
#endif

/* 0x133260 */
void FUN_00133260(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  tag_get(0x676c7721, 0);
  tag_get('!wlg', 0);
  /* relift: cmp (int16_t)ecx, word ptr [esi + 0x52] -> jle 0x1332fb */
  /* test ecx, ecx -> je 0x1332dc */
  datum_delete((void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x133300 */
#if 0 /* ported in objects.c */
void FUN_00133300(int particle_ptr, int object_handle)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  tag_get(0x676c7721, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x13339b */
  object_get_function_value(0, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x133347 */
  /* relift: test byte ptr [esi + 0x28], 1 -> je 0x133403 */
  /* test (char)eax, 0x41 -> jne 0x13344f */
  /* test (char)eax, 0x41 -> jne 0x13348c */
  data_new_at_index((void *)(uintptr_t)eax);
  /* cmp esi, -1 -> je 0x1334df */
  datum_get((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)esi;
}
#endif

/* 0x1334f0 */
void FUN_001334f0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x133520 */
void FUN_00133520(int object_handle, int widget_datum)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!wlg', 0);
  FUN_0018d2c0((void *)(uintptr_t)edx, ecx, eax, 0x00326a78, 0);
  /* test esi, esi -> je 0x1335bc */
  FUN_0018d6e0((void *)(uintptr_t)eax, 0, 0, 0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f, (float *)0, 0.0f, 0);
  /* test esi, esi -> jne 0x133580 */
  FUN_0018d360((void *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1335e0 — 1D cubic Neville interpolate of (ta,a)..(td,d) at time t. */
__attribute__((noinline)) float FUN_001335e0(float a, float b, float c, float d,
                                             float ta, float tb, float tc,
                                             float td, float t)
{
  float slope_ab;
  float slope_bc;
  float slope_cd;
  float u;
  float v;
  float w;

  if (t < ta || t > td) {
    display_assert((char *)0x29aae4, (char *)0x25ed80, 0x5fa, 1);
    system_exit(-1);
  }

  slope_cd = (d - c) / (td - tc);
  slope_bc = (c - b) / (tc - tb);
  slope_ab = (b - a) / (tb - ta);

  u = (slope_cd - slope_bc) / (td - tb);
  v = (slope_bc - slope_ab) / (tc - ta);
  w = (u - v) / (td - ta);

  return ((w * (t - tc) + v) * (t - tb) + slope_ab) * (t - ta) + a;
}

/* 0x1336a0 — evaluate a 4-point time curve for each XYZ channel via FUN_001335e0. */
void FUN_001336a0(float *out, float *p0, float *p1, float *p2, float *p3, float t0,
                  float t1, float t2, float t3, float time)
{
  out[0] = FUN_001335e0(p0[0], p1[0], p2[0], p3[0], t0, t1, t2, t3, time);
  out[1] = FUN_001335e0(p0[1], p1[1], p2[1], p3[1], t0, t1, t2, t3, time);
  out[2] = FUN_001335e0(p0[2], p1[2], p2[2], p3[2], t0, t1, t2, t3, time);
}

/* 0x1337c0 */
int glow_normal_particle_new(int glow_widget_ptr, short index, short count)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  tag_get(0x676c7721, 0);
  data_new_at_index((void *)(uintptr_t)edx);
  /* cmp ebx, -1 -> je 0x13398a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x80], (int16_t)ebx -> jne 0x133844 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0x9c], (int16_t)ebx -> jne 0x13388f */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0xb0], -1 -> jne 0x133905 */
  /* relift: test byte ptr [esi + 0x28], 1 -> jne 0x133905 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  display_assert((char *)0, (char *)0x0029ab60, 945, 0);
  system_exit(0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0x1339a0 — interpolate a glow particle's world position from widget samples.
 * glow_widget arrives in EAX; particle_ptr / blend weight on the stack. */
void get_particle_world_position(int glow_widget, int particle_ptr, float param_3)
{
  char *glow = (char *)glow_widget;
  char *particle = (char *)particle_ptr;
  int16_t sample_count = *(int16_t *)(glow + 4);
  int16_t index = 0;
  int16_t i;
  float t0, t1, t2, t3;
  float p0[3], p1[3], p2[3], p3[3];
  float q0[3], q1[3], q2[3], q3[3];
  float r0[3], r1[3], r2[3], r3[3];
  float out0[3], out1[3], out2[3];
  float angle, s, c;

  for (i = 0; i < sample_count - 1; i++) {
    if (*(float *)(glow + 0x238 + i * 4) <= *(float *)(particle + 0x28) &&
        *(float *)(glow + 0x23c + i * 4) > *(float *)(particle + 0x28))
      break;
    index = (int16_t)(i + 1);
  }
  if (index >= sample_count - 1) {
    display_assert((char *)0x29aba4, (char *)0x29ab60, 0x437, 1);
    system_exit(-1);
  }
  if (index < 0)
    index = 0;
  else if (index > sample_count - 1)
    index = (int16_t)(sample_count - 1);
  *(int16_t *)(particle + 2) = index;

  if (sample_count <= 1) {
    display_assert((char *)0x29ab88, (char *)0x29ab60, 0x43b, 1);
    system_exit(-1);
  }

  if (sample_count >= 4) {
    int lo = index;
    int hi = index + 1;
    int last = sample_count - 1;
    int span = hi - lo + 1;
    int k;
    while (span < 4) {
      if (lo > 0)
        lo--;
      if (hi < last)
        hi++;
      span = hi - lo + 1;
    }
    for (k = 0; k < 4; k++) {
      int16_t node_i = *(int16_t *)(glow + (lo + k) * 2 + 0x22a);
      char *sample = glow + (int)node_i * 0x6c;
      float *pos = (k == 0) ? p0 : (k == 1) ? p1 : (k == 2) ? p2 : p3;
      float *tan = (k == 0) ? q0 : (k == 1) ? q1 : (k == 2) ? q2 : q3;
      float *nrm = (k == 0) ? r0 : (k == 1) ? r1 : (k == 2) ? r2 : r3;
      float *time = (k == 0) ? &t0 : (k == 1) ? &t1 : (k == 2) ? &t2 : &t3;
      pos[0] = *(float *)(sample + 0x60);
      pos[1] = *(float *)(sample + 0x64);
      pos[2] = *(float *)(sample + 0x68);
      tan[0] = *(float *)(sample + 0x5c);
      tan[1] = *(float *)(sample + 0x60);
      tan[2] = *(float *)(sample + 0x64);
      nrm[0] = *(float *)(sample + 0x44) * tan[2] - *(float *)(sample + 0x4c) * tan[0];
      nrm[1] = *(float *)(sample + 0x4c) * tan[1] - *(float *)(sample + 0x48) * tan[2];
      nrm[2] = *(float *)(sample + 0x48) * tan[0] - *(float *)(sample + 0x44) * tan[1];
      *time = *(float *)(glow + 0x238 + (lo + k) * 4);
    }
  } else {
    p0[0] = *(float *)(glow + 0x68); p0[1] = *(float *)(glow + 0x6c); p0[2] = *(float *)(glow + 0x70);
    p1[0] = *(float *)(glow + 0xd4); p1[1] = *(float *)(glow + 0xd8); p1[2] = *(float *)(glow + 0xdc);
    q0[0] = *(float *)(glow + 0x5c); q0[1] = *(float *)(glow + 0x60); q0[2] = *(float *)(glow + 0x64);
    q1[0] = *(float *)(glow + 0xc8); q1[1] = *(float *)(glow + 0xcc); q1[2] = *(float *)(glow + 0xd0);
    t0 = *(float *)(glow + 0x238);
    t1 = *(float *)(glow + 0x23c);
    if (sample_count == 3) {
      p2[0] = *(float *)(glow + 0x140); p2[1] = *(float *)(glow + 0x144); p2[2] = *(float *)(glow + 0x148);
      q2[0] = *(float *)(glow + 0x134); q2[1] = *(float *)(glow + 0x138); q2[2] = *(float *)(glow + 0x13c);
      t2 = *(float *)(glow + 0x240);
    } else {
      p2[0] = p1[0]; p2[1] = p1[1]; p2[2] = p1[2];
      q2[0] = q1[0]; q2[1] = q1[1]; q2[2] = q1[2];
      t2 = t1;
    }
    p3[0] = p2[0]; p3[1] = p2[1]; p3[2] = p2[2];
    q3[0] = q2[0]; q3[1] = q2[1]; q3[2] = q2[2];
    t3 = t2;
    for (i = 0; i < 3; i++) {
      r0[i] = q0[i]; r1[i] = q1[i]; r2[i] = q2[i]; r3[i] = q3[i];
    }
  }

  FUN_001336a0(out0, p0, p1, p2, p3, t0, t1, t2, t3, *(float *)(particle + 0x28));
  FUN_001336a0(out1, q0, q1, q2, q3, t0, t1, t2, t3, *(float *)(particle + 0x28));
  FUN_001336a0(out2, r0, r1, r2, r3, t0, t1, t2, t3, *(float *)(particle + 0x28));

  angle = param_3 * *(float *)(particle + 0x28) + *(float *)(particle + 8);
  s = sinf(angle);
  c = cosf(angle);
  *(float *)(particle + 0x2c) += (out2[0] * c + out1[0] * s) * *(float *)(particle + 0x1c);
  *(float *)(particle + 0x30) += (out2[1] * c + out1[1] * s) * *(float *)(particle + 0x1c);
  *(float *)(particle + 0x34) += (out2[2] * c + out1[2] * s) * *(float *)(particle + 0x1c);
  (void)out0;
}



/* 0x149c60 */
char FUN_00149c60(int *block_ptr, void *transformed_2c, void *transformed_20, float scale, float best_dist, float *result)
{
  int ecx = 0;

  FUN_00149680((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x149ce0 */
void FUN_00149ce0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x149d14 */
  display_assert((char *)0x00253440, (char *)0x0029ce78, 76, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x149d57 */
  /* test (char)eax, (char)eax -> jne 0x149d57 */
  /* test (char)eax, (char)eax -> je 0x14ad01 */
  /* test (char)eax, (char)eax -> je 0x149d86 */
  /* test (char)eax, (char)eax -> je 0x149d97 */
  /* test (char)eax, (char)eax -> je 0x149da8 */
  /* test (char)eax, (char)eax -> je 0x149db9 */
  /* test (char)eax, (char)eax -> je 0x149dca */
  /* test (char)eax, (char)eax -> je 0x149dde */
  /* test (char)eax, (char)eax -> je 0x149df5 */
  /* test (char)eax, (char)eax -> je 0x149e0c */
  /* test (char)eax, (char)eax -> je 0x149e23 */
  /* test (char)eax, (char)eax -> je 0x149e3a */
  /* test (char)eax, (char)eax -> je 0x149e51 */
  /* test (char)eax, (char)eax -> je 0x149e68 */
  /* test (char)eax, (char)eax -> je 0x149e7f */
  /* test (char)eax, (char)eax -> je 0x149e96 */
  /* test (char)eax, (char)eax -> je 0x149ead */
  /* test (char)eax, (char)eax -> je 0x149ec4 */
  /* test (char)eax, (char)eax -> je 0x149edb */
  /* test (char)eax, (char)eax -> je 0x149ef2 */
  /* test (char)eax, (char)eax -> je 0x149f09 */
  /* test (char)eax, (char)eax -> jne 0x149fb5 */
  local_player_get_player_index(eax);
  /* cmp eax, -1 -> jne 0x149f4a */
  /* mem[0x00324fc8] = eax */
  local_player_get_player_index(ecx);
  datum_get((void *)(uintptr_t)edx, 0);
  /* mem[0x00324fc8] = eax */
  /* mem[0x005a8d00] = ecx */
  /* mem[0x005a8d04] = edx */
  /* mem[0x005a8d08] = eax */
  /* mem[0x005a8cf0] = ecx */
  /* mem[0x005a8cf4] = edx */
  /* mem[0x005a8cf8] = eax */
  breakable_surfaces_get_bsp_surface_data();
  global_collision_bsp_get();
  collision_bsp_test_vector(0, 0, 0, 0, 0, 0, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> je 0x14a0ca */
  FUN_0014ec30(0, (float *)0, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x14a0ca */
  /* mem[0x005a8cc0] = eax */
  /* mem[0x005a8cc4] = ecx */
  /* mem[0x005a8cc8] = edx */
  /* test (char)eax, (char)eax -> je 0x14a32e */
  game_time_get();
  FUN_001daf7e();
  game_time_get();
  FUN_001daf7e();
  game_time_get();
  FUN_001daf7e();
  FUN_00189cb0(0, (void *)0x005a8cc0, (void *)0x0029ce58, 0);
  FUN_00109e90((float *)(uintptr_t)ecx, 0.0f, 0.0f, 0.0f);
  matrix_scale_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x14a829 */
  FUN_0014dc30(0, (float *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x14a3b0 */
  FUN_00189150(0, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189150(0, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  FUN_0014dab0(0, 0);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  FUN_0014df70(esi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14a615 */
  FUN_00189320(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 2 -> jne 0x14a4c3 */
  global_collision_bsp_get();
  /* cmp (int16_t)eax, 3 -> jne 0x14a826 */
  /* relift: cmp word ptr [ebp - 0x82], -1 -> je 0x14a826 */
  FUN_0014c8e0((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x14a826 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test edi, edi -> je 0x14a826 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  render_debug_collision_surface(0, 0, 0, (void *)(uintptr_t)ecx);
  FUN_001d94f0();
  FUN_000b5490(0);
  snprintf((char *)(uintptr_t)ecx, 2048, (char *)0x0029cde4);
  FUN_00189c40(0, (char *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  FUN_00189150(0, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_001506d0();
  FUN_00150550((void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0, 0, 0, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 0, (void *)0);
  FUN_00189320(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  /* cmp (int16_t)edi, 0xe -> jle 0x14a72d */
  display_assert((char *)0x0029cdd8, (char *)0x0029ce78, 297, 0);
  system_exit(0);
  csmemmove((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, edx);
  csmemset((void *)(uintptr_t)edx, 0, 16);
  csmemset((void *)(uintptr_t)eax, 0, 16);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x14a809 */
  FUN_00189150(0, (float *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)ecx);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x14a7e5 */
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)esi, (void *)(uintptr_t)edx);
  FUN_00189320(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  /* cmp (int16_t)ebx, (int16_t)edi -> jl 0x14a7b3 */
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14ac28 */
  FUN_0014dc30(0, (float *)(uintptr_t)ecx, 0);
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x14ab7a */
  render_frustum_get_projection_bounds((void *)0x005065a4, (void *)(uintptr_t)eax);
  matrix_scale_transform_vector((float *)0, (float *)0, (float *)0);
  matrix_scale_transform_vector((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_scale_transform_vector((void *)0x005065e8, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x14ab1f */
  /* relift: test dword ptr [ecx*4 + 0x476120], edx -> je 0x14abf5 */
  FUN_00189150(0, (float *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)edx);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_0014ec30(0, (float *)(uintptr_t)ecx, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x14ad00 */
  FUN_0014c7b0((void *)(uintptr_t)edx);
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x14ad2b */
  display_assert((char *)0x00253418, (char *)0x0029ce78, 443, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 0);
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)0);
  FUN_001896d0(0, (void *)(uintptr_t)eax, (void *)0, 0.0f, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x14aed5 */
  /* cmp (int16_t)edx, 0x100 -> jge 0x14ae75 */
  /* cmp (int16_t)edx, 0x100 -> jge 0x14aed3 */
  /* cmp (int16_t)ecx, 0x100 -> jge 0x14af64 */
  /* test (char)eax, 0x41 -> jne 0x14b20f */
  /* cmp (int16_t)ecx, 0x100 -> jge 0x14afeb */
  perpendicular2d((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  magnitude3d((float *)(uintptr_t)eax);
  FUN_00099220((float *)(uintptr_t)ebx);
  FUN_00099270((float *)(uintptr_t)ebx, eax);
  FUN_00061df0((void *)(uintptr_t)ecx, 0, ecx, (void *)(uintptr_t)edx);
  /* cmp eax, ecx -> jl 0x14b107 */
  FUN_00099220((float *)0);
  FUN_00099270((float *)(uintptr_t)edi, eax);
  FUN_00061df0((void *)(uintptr_t)eax, 0, edx, (void *)(uintptr_t)ecx);
  /* cmp eax, ecx -> jl 0x14b1e2 */
  /* cmp (int16_t)ebx, 8 -> jle 0x14b24e */
  display_assert((char *)0x0029cf04, (char *)0x0029cf34, 241, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x100 -> jge 0x14b3cc */
  FUN_00099220((float *)(uintptr_t)edi);
  FUN_00099270((float *)(uintptr_t)edi, eax);
  FUN_00061df0((void *)(uintptr_t)eax, 0, edx, (void *)(uintptr_t)ecx);
  /* cmp eax, ecx -> jl 0x14b2e5 */
  /* test (char)eax, 0x41 -> jne 0x14b3ca */
  /* relift: cmp word ptr [eax*2 + 0x28cb10], (int16_t)edx -> je 0x14b39d */
  display_assert((char *)0x0029cea8, (char *)0x0029cf34, 283, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x14b3ca */
  /* cmp eax, edx -> jl 0x14b3b0 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 16);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 24);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  /* cmp eax, -1 -> je 0x14b41f */
  /* test eax, eax -> je 0x14b439 */
  matrix_transform_point((float *)(uintptr_t)eax, (float *)(uintptr_t)edi, (float *)(uintptr_t)edx);
  collision_features_from_point(0, 0.0f, 0, 0, 0, edx, ecx, 0, (void *)0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 24);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 16);
  tag_block_get_element((void *)0, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 16);
  triple_product3d((float *)0, (float *)0, (float *)0);
  /* test (char)eax, 0x41 -> je 0x14b597 */
  triple_product3d((float *)0, (float *)0, (float *)0);
  /* cmp eax, ebx -> jne 0x14b5ad */
  /* test esi, esi -> je 0x14b5dd */
  matrix_scale_transform_vector((float *)(uintptr_t)esi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix_transform_point((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  collision_features_from_line((float *)(uintptr_t)eax, (float *)(uintptr_t)edi, 0.0f, 0, 0, 0, edx, ecx, 0, (void *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  collision_surface_polygon(0, 0, (void *)(uintptr_t)ecx);
  bsp3d_get_plane_from_designator(0, eax, (float *)(uintptr_t)edx);
  /* test ebx, ebx -> je 0x14b69b */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x14b68a */
  matrix_transform_point((float *)(uintptr_t)ebx, (float *)(uintptr_t)esi, (float *)(uintptr_t)esi);
  FUN_0010a1c0((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* cmp ecx, -1 -> je 0x14b6a8 */
  FUN_0014b220(0, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, 0, 0, 0, 0, 0, 0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x14b708 */
  /* cmp (int16_t)eax, 0x100 -> jle 0x14b728 */
  display_assert((char *)0x0029d068, (char *)0x0029cf34, 429, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x14b737 */
  /* cmp (int16_t)eax, 0x100 -> jle 0x14b757 */
  display_assert((char *)0x0029cfe0, (char *)0x0029cf34, 430, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x14b766 */
  /* cmp (int16_t)eax, 0x100 -> jle 0x14b786 */
  display_assert((char *)0x0029cf60, (char *)0x0029cf34, 431, 0);
  system_exit(0);
  collision_features_from_vertex(0, 0, 0, 0, 0, 0, (void *)(uintptr_t)edi);
  collision_features_from_polygon(0, 0, 0, 0, 0, 0, (void *)(uintptr_t)edi);
  FUN_0014b620(0, 0, 0, 0, 0, 0, (void *)(uintptr_t)edi);
  /* test (char)eax, 1 -> jne 0x14bad3 */
  /* test (char)eax, 0x41 -> jne 0x14bad3 */
  /* test (char)eax, 0x41 -> jne 0x14ba67 */
  normalize3d((float *)(uintptr_t)edi);
  /* test (char)eax, 1 -> jne 0x14bbfb */
  FUN_00061df0((void *)(uintptr_t)eax, 0, ecx, (void *)0);
  /* test edi, edi -> jle 0x14bbc9 */
  /* cmp eax, edi -> jl 0x14bb80 */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x14bc71 */
  collision_features_from_surface((void *)(uintptr_t)edx, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)0);
  /* test (char)eax, (char)eax -> jne 0x14bccb */
  /* cmp (int16_t)edi, 1 -> jne 0x14bc9f */
  collision_cylinder_test_point((void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)0);
  /* test (char)eax, (char)eax -> jne 0x14bccb */
  /* cmp (int16_t)edi, 2 -> jne 0x14bcfc */
  collision_prism_test_point((void *)(uintptr_t)eax, (void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)0);
  /* test (char)eax, (char)eax -> je 0x14bcfc */
  /* relift: cmp (int16_t)esi, word ptr [eax] -> jl 0x14bc44 */
  /* cmp (int16_t)edi, 3 -> jl 0x14bc30 */
  /* cmp (int16_t)ecx, -1 -> je 0x14bda4 */
  /* test (char)eax, 0x41 -> jne 0x14bf26 */
  /* test (char)eax, 1 -> jne 0x14bf24 */
  normalize3d((float *)0);
  /* test (char)eax, 0x41 -> je 0x14c056 */
  /* test (char)eax, 0x41 -> jne 0x14c0c5 */
  /* test (char)eax, 0x41 -> jne 0x14c12d */
  /* test (char)eax, 0x41 -> jne 0x14c14c */
  /* test (char)eax, 0x41 -> jne 0x14c14c */
  /* test (char)eax, 0x41 -> jne 0x14c189 */
  /* test (char)eax, 0x41 -> je 0x14c058 */
  vector3d_scale_add((float *)(uintptr_t)ecx, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx);
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)esi, 0.0f, (float *)0);
  normalize3d((float *)(uintptr_t)ebx);
  FUN_00013070((float *)(uintptr_t)edi, (float *)(uintptr_t)ebx);
  /* test (char)eax, 0x41 -> jne 0x14c2d6 */
  /* test (char)eax, 0x41 -> jne 0x14c2fe */
  /* test (char)eax, 0x41 -> jne 0x14c300 */
  /* test (char)eax, 0x41 -> jne 0x14c332 */
  /* test (char)eax, 1 -> je 0x14c30d */
  FUN_00061df0((void *)(uintptr_t)ecx, 0, edx, (void *)0);
  FUN_00061df0((void *)(uintptr_t)edx, 0, eax, (void *)(uintptr_t)edx);
  /* test edi, edi -> jle 0x14c477 */
  /* test (char)eax, 0x41 -> jne 0x14c442 */
  /* test (char)eax, 0x41 -> je 0x14c30d */
  /* cmp eax, edi -> jl 0x14c3c2 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x14c51b */
  collision_sphere_test_vector();
  /* test (char)eax, (char)eax -> jne 0x14c574 */
  /* cmp (int16_t)eax, 1 -> jne 0x14c54a */
  collision_cylinder_test_vector();
  /* test (char)eax, (char)eax -> jne 0x14c574 */
  /* cmp (int16_t)eax, 2 -> jne 0x14c5ca */
  collision_prism_test_vector();
  /* test (char)eax, (char)eax -> je 0x14c5ca */
  /* test (char)eax, 0x41 -> jne 0x14c5ca */
  /* relift: cmp dword ptr [edi + 0x24], 8 -> jle 0x14c702 */
  display_assert((char *)0x0029d0ec, (char *)0x0029cf34, 1079, 0);
  system_exit(0);
  project_point2d((float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, edx, ecx, (float *)(uintptr_t)esi);
  /* test esi, esi -> jle 0x14c79f */
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edx, (void *)0);
  /* cmp ecx, esi -> jl 0x14c770 */
  /* relift: cmp word ptr [esi], (int16_t)edi -> jle 0x14c7e2 */
  display_assert((char *)0x0029d1d0, (char *)0x0029cf34, 1108, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], (int16_t)edi -> jle 0x14c808 */
  display_assert((char *)0x0029d178, (char *)0x0029cf34, 1109, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 4], (int16_t)edi -> jle 0x14c82e */
  display_assert((char *)0x0029d128, (char *)0x0029cf34, 1110, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 4], (int16_t)edi -> jle 0x14c863 */
  FUN_0014c6d0(0, (void *)(uintptr_t)eax);
  /* relift: cmp (int16_t)edi, word ptr [esi + 4] -> jl 0x14c840 */
  /* relift: cmp word ptr [esi + 2], (int16_t)edi -> jle 0x14c8a5 */
  FUN_001896d0(0, (void *)(uintptr_t)eax, (void *)0, 0.0f, (void *)0);
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jl 0x14c870 */
  /* relift: cmp word ptr [esi], (int16_t)edi -> jle 0x14c8d9 */
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)0);
  /* relift: cmp (int16_t)edi, word ptr [esi] -> jl 0x14c8b0 */
  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  /* cmp ecx, -1 -> je 0x14c93d */
  tag_get(0x636f6c6c, 0);
  object_get_node_matrices(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp (int16_t)ecx, -1 -> je 0x14c9fb */
  /* cmp (int16_t)ecx, -1 -> je 0x14c9fb */
  /* test eax, eax -> jle 0x14c9fb */
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x14c9b0 */
  /* cmp ecx, eax -> jg 0x14c9ba */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 96);
  /* test eax, eax -> jle 0x14c9fb */
  real_matrix3x3_transform_point((void *)(uintptr_t)esi, (float *)0, (float *)0);
  bsp3d_find_leaf((void *)(uintptr_t)edi, 0, (void *)(uintptr_t)eax);
  /* cmp eax, -1 -> je 0x14ca1e */
  /* relift: cmp esi, dword ptr [eax] -> jl 0x14c977 */
  /* test ecx, ecx -> jle 0x14caef */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp (int16_t)ecx, -1 -> je 0x14cad4 */
  /* cmp (int16_t)ecx, -1 -> je 0x14cad4 */
  /* test eax, eax -> jle 0x14cad4 */
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x14ca8f */
  /* cmp ecx, eax -> jg 0x14ca99 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 96);
  /* test ecx, ecx -> jle 0x14cad4 */
  matrix_inverse((float *)(uintptr_t)esi, (float *)0);
  matrix_transform_point((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* cmp esi, ecx -> jl 0x14ca56 */
  collision_log_add_call(0);
  collision_log_query_counter((void *)0x004761c8);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp (int16_t)eax, 0xffff -> je 0x14cc36 */
  /* test ecx, ecx -> jle 0x14cc36 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x14cb9a */
  /* cmp ebx, ecx -> jle 0x14cba4 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 96);
  /* test eax, eax -> jle 0x14cc36 */
  matrix_inverse((float *)(uintptr_t)esi, (float *)0);
  matrix_transform_point((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_scale_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  collision_bsp_test_vector(0, 0, 0, 0, 0, 0, 0.0f, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14cc36 */
  /* relift: cmp esi, dword ptr [eax] -> jl 0x14cb50 */
  collision_log_add_time(0, eax, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp (int16_t)eax, 0xffff -> je 0x14cda7 */
  /* test ecx, ecx -> jle 0x14cda7 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x14cd02 */
  /* cmp ebx, ecx -> jle 0x14cd0c */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 96);
  /* test eax, eax -> jle 0x14cda7 */
  matrix_inverse((float *)(uintptr_t)esi, (float *)0);
  matrix_transform_point((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_scale_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00149c60((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0.0f, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> je 0x14cda7 */
  /* relift: cmp esi, dword ptr [eax] -> jl 0x14ccb8 */
  FUN_001d90e0();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp (int16_t)ecx, -1 -> je 0x14cee9 */
  /* cmp (int16_t)ecx, -1 -> je 0x14cee9 */
  /* test eax, eax -> jle 0x14cee9 */
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x14ce58 */
  /* cmp ecx, eax -> jg 0x14ce62 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 96);
  /* test eax, eax -> jle 0x14cee9 */
  matrix_inverse((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx);
  matrix_transform_point((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  collision_bsp_test_sphere(0, 0, 0, 0, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x14cee9 */
  collision_features_add(0, (void *)(uintptr_t)eax, 0, 0, 0, 0, (void *)(uintptr_t)edx);
  /* relift: cmp esi, dword ptr [eax] -> jl 0x14ce13 */
  /* test ecx, ecx -> jle 0x14cfd7 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp (int16_t)ecx, -1 -> je 0x14cfbc */
  /* cmp (int16_t)ecx, -1 -> je 0x14cfbc */
  /* test eax, eax -> jle 0x14cfbc */
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x14cf7c */
  /* cmp ecx, eax -> jg 0x14cf86 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 96);
  /* test ecx, ecx -> jle 0x14cfbc */
  /* test ecx, ecx -> jle 0x14cfbc */
  /* test ecx, ecx -> jle 0x14cfbc */
  render_debug_collision_bsp(0, 0);
  /* cmp esi, ecx -> jl 0x14cf43 */
  /* cmp eax, ecx -> jle 0x14cff8 */
  csmemset((void *)0x005a5e40, 0, 8856);
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x14d04e */
  display_assert((char *)0x00253440, (char *)0x0029d32c, 150, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x325058], -1 -> je 0x14d0aa */
  display_assert((char *)0x0029d3a0, (char *)0x0029d32c, 167, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x14d0b5 */
  /* cmp (int16_t)esi, 3 -> jl 0x14d0d5 */
  display_assert((char *)0x0029d358, (char *)0x0029d32c, 168, 0);
  system_exit(0);
  csmemset((void *)0x005a80e0, 0, 2952);
  collision_log_period_helper(0, 0);
  collision_log_period_helper(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x14d151 */
  /* cmp (int16_t)eax, 3 -> jl 0x14d177 */
  display_assert((char *)0x0029d3c8, (char *)0x0029d32c, 198, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x14d1f1 */
  QueryPerformanceFrequency((void *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)edi, (char *)0x0029d438);
  crt_sprintf((char *)(uintptr_t)edi, (char *)0x0025acb8);
  FUN_001d90e0();
  /* test (char)eax, (char)eax -> je 0x14d83a */
  /* cmp (int16_t)edi, 3 -> jl 0x14d265 */
  /* test (char)eax, (char)eax -> je 0x14d80e */
  /* test (char)ebx, (char)ebx -> je 0x14d287 */
  /* test ebx, ebx -> jle 0x14d287 */
  /* test dl, dl -> je 0x14d80e */
  csmemset((void *)(uintptr_t)ecx, 0, 72);
  csmemset((void *)(uintptr_t)edx, 0, 1584);
  /* test (char)ecx, (char)ecx -> je 0x14d3d4 */
  /* test (char)ebx, (char)ebx -> je 0x14d371 */
  qsort((void *)(uintptr_t)edx, 22, 72, (void *)0x0014cfe0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025a2b0);
  /* test (char)eax, (char)eax -> je 0x14d5b4 */
  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025b06c);
  /* test (char)eax, (char)eax -> je 0x14d500 */
  csstrlen((char *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x14d4a0 */
  QueryPerformanceFrequency((void *)(uintptr_t)edx);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x0029d438);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025acb8);
  snprintf((char *)(uintptr_t)edx, ecx, (char *)0);
  /* cmp (int16_t)esi, 3 -> jl 0x14d450 */
  csstrlen((char *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14d557 */
  QueryPerformanceFrequency((void *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0029d438);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acb8);
  snprintf((char *)(uintptr_t)eax, edx, (char *)0x0027ba98);
  FUN_0008dc30((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x14d5d3 */
  /* cmp (int16_t)esi, 0x16 -> jl 0x14d5f3 */
  display_assert((char *)0x0029d440, (char *)0x0029d32c, 342, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi], 0 -> jle 0x14d789 */
  snprintf((char *)(uintptr_t)edx, 512, (char *)0x0027ba98);
  /* test (char)eax, (char)eax -> je 0x14d6e5 */
  csstrlen((char *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14d682 */
  QueryPerformanceFrequency((void *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0029d438);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acb8);
  snprintf((char *)(uintptr_t)edx, ecx, (char *)0);
  /* cmp (int16_t)esi, 3 -> jl 0x14d632 */
  csstrlen((char *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14d735 */
  QueryPerformanceFrequency((void *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0029d438);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acb8);
  snprintf((char *)(uintptr_t)eax, edx, (char *)0x0027ba98);
  FUN_0008dc30((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  interface_draw_text(0, 0, 0, 0, 0, 0);
  draw_string_set_color((void *)(uintptr_t)ecx);
  draw_string_set_tab_stops((void *)0, 0);
  rasterizer_text_draw((void *)(uintptr_t)ecx, (void *)0, (void *)(uintptr_t)eax, 0, (char *)(uintptr_t)edx);
  /* relift: cmp word ptr [0x4761d8], 0 -> jg 0x14d86a */
  display_assert((char *)0x0029d520, (char *)0x0029d32c, 403, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x14d885 */
  /* cmp (int16_t)esi, 0x16 -> jl 0x14d8a5 */
  display_assert((char *)0x0029d4e8, (char *)0x0029d32c, 406, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x14d8b0 */
  /* cmp (int16_t)edi, 8 -> jl 0x14d8d0 */
  display_assert((char *)0x0029d490, (char *)0x0029d32c, 407, 0);
  system_exit(0);
  game_in_progress();
  /* test (char)eax, (char)eax -> je 0x14d92e */
  game_in_editor();
  /* test (char)eax, (char)eax -> jne 0x14d92e */
  /* test (char)eax, (char)eax -> je 0x14d92e */
  /* cmp (int16_t)eax, 0xffff -> jne 0x14d8fe */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x14d909 */
  /* cmp (int16_t)eax, 3 -> jl 0x14d929 */
  display_assert((char *)0x0029d3c8, (char *)0x0029d32c, 424, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  FUN_0014d840(0);
  /* cmp (int16_t)eax, 0xffff -> je 0x14d9c2 */
  FUN_0014d840(0);
  /* cmp (int16_t)eax, 0xffff -> je 0x14da11 */
  /* test (char)eax, (char)eax -> je 0x14da79 */
  csstrlen((char *)(uintptr_t)esi);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x14daab */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_001d90e0();
  FUN_0018e420();
  bsp3d_find_leaf((void *)(uintptr_t)eax, 0, (void *)0);
  /* cmp eax, -1 -> je 0x14db05 */
  breakable_surfaces_get_bsp_surface_data();
  global_collision_bsp_get();
  collision_bsp_test_sphere(0, 0, 0, 0, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x14db05 */
  object_get_and_verify_type(0, 0);
  /* cmp edi, eax -> je 0x14dc0a */
  /* relift: test byte ptr [esi + 4], 1 -> jne 0x14dc0a */
  /* test ecx, eax -> je 0x14dc0a */
  /* test (char)eax, 2 -> je 0x14dbc7 */
  /* relift: test dword ptr [ebp + 0xc], 0x400000 -> je 0x14dbc7 */
  FUN_001509c0((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x14dbe9 */
  FUN_00150ac0((void *)(uintptr_t)edx, (void *)(uintptr_t)ebx);
  FUN_0014c8e0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x14dbe9 */
  FUN_0014c950(0, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x14dc22 */
  /* cmp eax, -1 -> je 0x14dc0a */
  FUN_0014db10(0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x14dc22 */
  /* cmp edi, -1 -> jne 0x14db20 */
  FUN_0018e420();
  bsp3d_find_leaf((void *)(uintptr_t)eax, 0, (void *)0);
  /* test dl, dl -> je 0x14dc6a */
  /* cmp eax, -1 -> je 0x14dccc */
  /* test (char)ecx, (char)ecx -> je 0x14dcc5 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  cluster_partition_object_iter_first((void *)(uintptr_t)eax, eax);
  /* cmp eax, -1 -> je 0x14dcc5 */
  FUN_0014db10(0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x14dccc */
  cluster_partition_object_iter_next((void *)(uintptr_t)ecx);
  /* cmp eax, -1 -> jne 0x14dca4 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x150550 */
int FUN_00150550(void *out_point, float *direction, float *origin, int arg4, int arg5, int arg6, float *out_point2, void *out_arg8, int max_results, void *results)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d90e0();
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x15058a */
  display_assert((char *)0x00253440, (char *)0x0029d5a0, 1214, 0);
  system_exit(0);
  FUN_0014ec30(0, (float *)0, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x15065e */
  FUN_0014f2c0((float *)(uintptr_t)edi, (float *)(uintptr_t)esi, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0, 0);
  display_assert((char *)0x00253418, (char *)0x0029d5a0, 1230, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1506d0 */
void FUN_001506d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_00150550((void *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0, 0, 0, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0, (void *)0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x150710 */
void FUN_00150710(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x150790 */
void FUN_00150790(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> jle 0x150813 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  collision_features_from_point(0, 0.0f, 0, 0, 0, 0, 0, 0, (void *)0);
  /* cmp ecx, edx -> jl 0x1507b0 */
  /* relift: cmp word ptr [eax + 2], 0 -> jne 0x150832 */
  /* relift: cmp word ptr [eax + 4], 0 -> jne 0x150832 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x150840 */
void FUN_00150840(void)
{
  int eax = 0;
  int esi = 0;

  /* cmp (int16_t)esi, -1 -> je 0x1508a5 */
  /* cmp eax, -1 -> je 0x150887 */
  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  tag_get('lloc', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);

  (void)eax;
  (void)esi;
}

/* 0x1508b0 */
void FUN_001508b0(int *state)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  matrix_transform_point((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, (float *)0);
  FUN_0018a990(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  matrix_transform_vector((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix_transform_vector((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189540(0, (void *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)edx);
  FUN_0018a990(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f);
  /* cmp ecx, edx -> jl 0x150920 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x1509c0 */
char FUN_001509c0(int *out, int obj_idx)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  /* cmp ecx, -1 -> je 0x150ab1 */
  tag_get(0x70687973, 0);
  object_get_world_position(0, (void *)(uintptr_t)eax);
  object_get_orientation(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi);
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x150ac0 */
char FUN_00150ac0(int *data, int *point)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  real_matrix3x3_transform_point((void *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* test ecx, ecx -> jle 0x150b4a */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  /* cmp ecx, edx -> jl 0x150af0 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x150b60 */
char FUN_00150b60(void *features, float *origin, float *direction, float *out_t_plane)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  real_matrix3x3_transform_point((void *)(uintptr_t)edi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  real_matrix3x3_transform_vector((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* test ecx, ecx -> jle 0x150c72 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  FUN_0010d380((float *)(uintptr_t)eax, 0.0f, (float *)0, (float *)0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x150c3c */
  /* test (char)eax, 0x41 -> jne 0x150c3c */
  /* cmp ecx, edx -> jl 0x150bb3 */
  /* test (char)ebx, (char)ebx -> je 0x150c69 */
  FUN_0010a1c0((float *)(uintptr_t)eax, (float *)(uintptr_t)esi, (float *)(uintptr_t)esi);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x150c80 */
void compute_ground_plane(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  FUN_0014ec30(49312, (float *)(uintptr_t)edi, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x150d92 */
  collision_features_test_los((void *)(uintptr_t)ecx, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x150d92 */
  FUN_00150840();
  /* relift: test byte ptr [ebp - 8], 8 -> jne 0x150d7e */
  /* cmp eax, -1 -> je 0x150d79 */
  FUN_000f68b0(0);
  /* test dl, 0x40 -> je 0x150d7e */
  /* cmp eax, -1 -> je 0x150d92 */
  FUN_00136b40(0);
  /* cmp (int16_t)ebx, -1 -> je 0x150dc7 */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x150da7 */
  /* cmp (int16_t)ebx, 0x21 -> jl 0x150dc7 */
  display_assert((char *)0x0029d6f0, (char *)0x0029d780, 338, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x150dd0 */
void friction_evaluate(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jne 0x150e09 */
  display_assert((char *)0, (char *)0x0029d780, 383, 0);
  system_exit(0);
  cross_product3d((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_0010b8a0((float *)(uintptr_t)esi, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  FUN_0010b8a0((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x150ed0 */
void FUN_00150ed0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  csmemset((void *)(uintptr_t)edx, 0, ecx);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  /* cmp (int16_t)eax, 0xffff -> je 0x150fa5 */
  /* test ecx, ecx -> je 0x150fa5 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 128);
  matrix_transform_point((float *)(uintptr_t)eax, (float *)0, (float *)0);
  /* test eax, eax -> je 0x15101b */
  matrix4x3_multiply((float *)(uintptr_t)eax, (float *)0, (float *)0);
  matrix_transform_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax);
  matrix_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_transform_vector((float *)(uintptr_t)eax, (float *)0, (float *)0);
  matrix_transform_vector((float *)(uintptr_t)eax, (float *)0, (float *)0);
  scenario_location_from_point((void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  compute_ground_plane();
  FUN_0018f510((void *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x15138f */
  FUN_0018e500(ecx);
  /* test (char)eax, 0x41 -> jne 0x151133 */
  /* test (char)eax, 0x41 -> jne 0x151157 */
  /* test (char)eax, 0x41 -> jne 0x15117e */
  /* test (char)eax, 0x41 -> jne 0x1511a0 */
  /* test (char)eax, 0x41 -> jne 0x1511bc */
  /* relift: test byte ptr [eax + 0x20], 1 -> je 0x151372 */
  FUN_00150710();
  /* test (char)eax, 0x41 -> jne 0x1512e0 */
  friction_evaluate();
  /* test (char)eax, 0x41 -> jne 0x151535 */
  /* test (char)eax, 0x41 -> jne 0x15140b */
  /* test (char)eax, 0x41 -> jne 0x15140b */
  /* test eax, eax -> je 0x151476 */
  /* relift: test byte ptr [eax + 0x20], 2 -> je 0x151476 */
  friction_evaluate();
  /* test eax, eax -> je 0x1515a0 */
  /* relift: test byte ptr [edx + 0x20], 8 -> je 0x151535 */
  /* test eax, eax -> je 0x1515a0 */
  /* relift: test byte ptr [eax + 0x20], 4 -> je 0x1515a0 */
  friction_evaluate();
  /* test esi, esi -> je 0x151653 */
  /* relift: test byte ptr [esi + 0x20], 0x10 -> je 0x151653 */
  /* relift: test byte ptr [esi + 0x20], 0x20 -> je 0x15170e */
  /* relift: test byte ptr [esi + 0x20], 0x40 -> je 0x151844 */
  FUN_0014df70(49312, (float *)(uintptr_t)eax, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x151844 */
  FUN_00150710();
  /* test (char)eax, 0x41 -> jne 0x1517b8 */
  /* cmp edi, ecx -> jl 0x150f42 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x151a50 — resolve biped/vehicle contact: impulse, translate, optional damage. */
char physics_compute_biped_collision(void *physics_ctx, int biped_handle)
{
  char features[0xac98];
  float cam_pos[3];
  float height_offset;
  float camera_height;
  float xy_point[3];
  float z_combined;
  float probe_extent;
  unsigned int tiny_extent = 0x3c800000u;
  float los_hit[16];
  char *vehicle;
  char *biped;
  float *veh_vel;
  float *biped_vel;
  float *biped_pos;
  float *veh_pos;
  float delta[3];
  float speed;
  float scale;
  float impulse[3];
  float hit_point[16];
  char *globals_elem;
  char damage[0x84];
  int damager_handle;
  char *damager_obj;
  char *unit_tag;
  int16_t material;
  float tmp;

  biped_get_camera_height_and_offset(biped_handle, (vector3_t *)cam_pos,
                                    &height_offset, &camera_height);
  if (!FUN_0014c950((int)(uintptr_t)physics_ctx, cam_pos)) {
    collision_features_init(features);
    /* mid-height point: (cam.x, cam.y, cam.z + height*0.5); z span from camera */
    xy_point[0] = cam_pos[0];
    xy_point[1] = cam_pos[1];
    xy_point[2] = cam_pos[2];
    z_combined = cam_pos[2] + height_offset * *(float *)0x253398 + camera_height;
    tmp = camera_height - *(float *)0x282124;
    if (tmp > *(float *)0x282124)
      probe_extent = tmp;
    else
      probe_extent = *(float *)&tiny_extent;
    FUN_0014cde0((int)(uintptr_t)physics_ctx, (int)(uintptr_t)xy_point,
                 z_combined, *(int *)&height_offset, *(int *)&probe_extent,
                 (int)(uintptr_t)features);
    if (!collision_features_test_los(features, cam_pos, los_hit))
      return 0;
  }

  vehicle = (char *)object_get_and_verify_type(*(int *)physics_ctx, 2);
  biped = (char *)object_get_and_verify_type(biped_handle, 1);
  veh_vel = (float *)(vehicle + 0x18);
  veh_pos = (float *)(vehicle + 0x50);
  biped_pos = (float *)(biped + 0x50);
  biped_vel = (float *)(biped + 0x18);

  speed = sqrtf(veh_vel[0] * veh_vel[0] + veh_vel[1] * veh_vel[1] +
                veh_vel[2] * veh_vel[2]);
  delta[0] = biped_pos[0] - veh_pos[0];
  delta[1] = biped_pos[1] - veh_pos[1];
  delta[2] = biped_pos[2] - veh_pos[2];
  normalize3d(delta);
  delta[2] += *(float *)0x2533f0;
  normalize3d(delta);

  scale = (speed > *(float *)0x25496c) ? speed : *(float *)0x25496c;
  impulse[0] = (delta[0] * scale + veh_vel[0]) * *(float *)0x253398;
  impulse[1] = (delta[1] * scale + veh_vel[1]) * *(float *)0x253398;
  impulse[2] = (delta[2] * scale + veh_vel[2]) * *(float *)0x253398;
  /* XBE folds scale*delta into the same slots then half-adds veh_vel via the
   * pre-add before FUN_001a4a70 — structural equivalent impulse. */
  FUN_001a4a70(biped_handle, impulse);

  cam_pos[0] += impulse[0] + impulse[0];
  cam_pos[1] += impulse[1] + impulse[1];
  cam_pos[2] += impulse[2] + impulse[2];
  if (FUN_0014f020(0x20c3a0, cam_pos, height_offset, height_offset,
                   camera_height + camera_height, biped_handle, hit_point)) {
    hit_point[2] -= height_offset;
    object_translate(biped_handle, hit_point, (void *)0);
    if (*(int *)physics_ctx == *(int *)(biped + 0x2dc) &&
        game_time_get() <= *(int *)(biped + 0x2e0) + 0x5a)
      return 1;
    if (!(speed > *(float *)0x253d48))
      goto damage_path;
    if (!(distance_squared3d(veh_vel, biped_vel) > *(float *)0x25620c))
      return 1;
  }

damage_path:
  globals_elem = (char *)tag_block_get_element(
      (char *)game_globals_get() + 0x188, 0, 0x98);
  if (*(int *)(globals_elem + 0x68) != -1) {
    damager_handle = *(int *)physics_ctx;
    damager_obj = vehicle;
    if (*(int *)(vehicle + 0x2d4) != -1) {
      damager_handle = *(int *)(vehicle + 0x2d4);
      damager_obj = (char *)object_get_and_verify_type(damager_handle, -1);
    }
    damage_data_new(damage, *(int *)(globals_elem + 0x68));
    *(unsigned int *)(damage + 4) |= 1;
    *(float *)(damage + 0x40) = 1.0f;
    *(int *)(damage + 8) = *(int *)(damager_obj + 0x70);
    *(int *)(damage + 0xc) = (*(int *)(damager_obj + 0x74) != -1)
                                 ? *(int *)(damager_obj + 0x74)
                                 : damager_handle;
    *(int16_t *)(damage + 0x10) = *(int16_t *)(damager_obj + 0x68);
    *(float *)(damage + 0x1c) = biped_pos[0];
    *(float *)(damage + 0x20) = biped_pos[1];
    *(float *)(damage + 0x24) = biped_pos[2];
    *(float *)(damage + 0x28) = veh_pos[0];
    *(float *)(damage + 0x2c) = veh_pos[1];
    *(float *)(damage + 0x30) = veh_pos[2];
    *(float *)(damage + 0x34) = delta[0];
    *(float *)(damage + 0x38) = delta[1];
    *(float *)(damage + 0x3c) = delta[2];
    normalize3d((float *)(damage + 0x34));
    object_cause_damage(damage, biped_handle, -1, -1, -1, 0);
  }

  if (*(int *)(globals_elem + 0x58) == -1)
    return 1;

  unit_tag = (char *)tag_get(0x756e6974, *(int *)biped); /* 'unit' */
  damage_data_new(damage, *(int *)(globals_elem + 0x58));
  material = *(int16_t *)(unit_tag + 0x298);
  if (material < 0 || (unsigned short)material >= 3) {
    display_assert((char *)0x29d7a8, (char *)0x29d780, 0x33e, 1);
    system_exit(-1);
  }
  *(float *)(damage + 0x40) = *(float *)(0x32514c + (int)material * 4);
  *(float *)(damage + 0x1c) = biped_pos[0];
  *(float *)(damage + 0x20) = biped_pos[1];
  *(float *)(damage + 0x24) = biped_pos[2];
  *(float *)(damage + 0x34) = delta[0] * *(float *)0x255e94;
  *(float *)(damage + 0x38) = delta[1] * *(float *)0x255e94;
  *(float *)(damage + 0x3c) = delta[2] * *(float *)0x255e94;
  object_cause_damage(damage, *(int *)physics_ctx, -1, -1, -1, 0);
  return 1;
}

/* 0x151ec0 */
void FUN_00151ec0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 0);
  object_get_and_verify_type(0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)eax, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)eax, (float *)0, (float *)0);
  /* test (char)eax, 0x41 -> jne 0x15220e */
  /* cmp ecx, edx -> jl 0x151fb0 */
  /* cmp ecx, edx -> jl 0x151f70 */
  /* test (char)ecx, (char)ecx -> je 0x152335 */
  /* test (char)eax, 0x41 -> je 0x152335 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x152350 */
void physics_compute_unit_collisions(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d90e0();
  FUN_0014c8e0((void *)(uintptr_t)eax, 0);
  FUN_001509c0((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1524bf */
  object_get_and_verify_type(0, 0);
  object_find_in_radius(0, eax, (void *)0, (float *)0, 0.0f, (void *)0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1524bf */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, ebx -> je 0x1524a7 */
  FUN_001509c0((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1524a7 */
  object_get_and_verify_type(0, 0);
  /* cmp esi, ecx -> jl 0x15244b */
  /* relift: test byte ptr [eax + 4], 0x20 -> jne 0x15244b */
  /* test (char)eax, 0x41 -> jne 0x1524a7 */
  FUN_00151ec0();
  object_get_and_verify_type(0, 0);
  /* test (char)eax, (char)eax -> jne 0x152491 */
  display_assert((char *)0x0029d800, (char *)0x0029d780, 669, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1524a7 */
  physics_compute_biped_collision((void *)(uintptr_t)esi, edi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1524d0 */
void physics_compute_vehicle_collision(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  normalize3d((float *)(uintptr_t)ecx);
  /* cmp ebx, edi -> jne 0x15251a */
  display_assert((char *)0x0029d844, (char *)0x0029d780, 944, 0);
  system_exit(0);
  /* cmp ecx, esi -> jne 0x152544 */
  display_assert((char *)0x0029d834, (char *)0x0029d780, 945, 0);
  system_exit(0);
  FUN_001092d0((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, 0.0f);
  matrix_scale_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi);
  matrix_scale_transform_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)esi);
  normalize3d((float *)(uintptr_t)edi);
  normalize3d((float *)0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x15266d */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x152680 */
void FUN_00152680(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  /* test (char)eax, 0x41 -> je 0x1526d3 */
  display_assert((char *)0x0029d8d0, (char *)0x0029d780, 986, 0);
  system_exit(0);
  real_vector3d_valid((float *)0);
  /* test (char)eax, (char)eax -> jne 0x152751 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  real_vector3d_valid((float *)0);
  /* test (char)eax, (char)eax -> jne 0x1527cb */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_0010a2c0((float *)0, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_00109c70((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)0);
  FUN_001099f0((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  FUN_00109c70((float *)(uintptr_t)eax, (float *)(uintptr_t)eax, (float *)0);
  FUN_00109d90((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  real_vector3d_valid((float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1528c6 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  real_vector3d_valid((float *)0);
  /* test (char)eax, (char)eax -> jne 0x152940 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  physics_compute_vehicle_collision();
  /* test (char)eax, (char)eax -> je 0x1529b6 */
  object_set_position(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix4x3_from_forward_up_position((void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)0, (float *)0);
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x152b1b */
  /* test (char)eax, 0x41 -> jne 0x152b1b */
  /* relift: cmp edi, dword ptr [eax] -> jl 0x152a51 */
  /* test (char)eax, (char)eax -> je 0x152c86 */
  /* test (char)eax, 0x41 -> je 0x152b97 */
  physics_compute_vehicle_collision();
  /* relift: cmp word ptr [ebp - 0x40], 0 -> jg 0x1529c0 */
  object_set_position(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* relift: cmp word ptr [ebp + 0x14], 3 -> jl 0x152dd4 */
  /* relift: cmp word ptr [ebp - 0x1c], 0 -> jne 0x152dd4 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x152e40 */
void FUN_00152e40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  tag_get('syhp', 0);
  matrix4x3_from_forward_up_position((void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)0, (float *)0);
  FUN_001093b0((float *)(uintptr_t)ebx, (float *)(uintptr_t)eax);
  FUN_00109120((float *)(uintptr_t)ebx);
  /* cmp eax, ecx -> jl 0x152ef3 */
  csmemset((void *)(uintptr_t)edx, 0, ecx);
  /* test ebx, ebx -> je 0x152fea */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x15308e */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  /* cmp (int16_t)eax, 0xffff -> je 0x153103 */
  /* test esi, esi -> je 0x153103 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  matrix4x3_multiply((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)0);
  matrix_transform_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax);
  matrix_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)eax);
  matrix_transform_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax);
  scenario_location_from_point((void *)(uintptr_t)eax, (void *)(uintptr_t)esi);
  compute_ground_plane();
  FUN_0018f510((void *)(uintptr_t)eax, (void *)(uintptr_t)esi);
  /* test (char)eax, 0x41 -> jne 0x153480 */
  /* test (char)eax, 0x41 -> jne 0x153480 */
  /* relift: test byte ptr [eax + 0x20], 1 -> je 0x153441 */
  FUN_00150710();
  /* test (char)eax, 0x41 -> jne 0x1533a6 */
  friction_evaluate();
  /* test (char)eax, 0x41 -> jne 0x15362c */
  /* test (char)eax, 0x41 -> jne 0x1534ff */
  /* test (char)eax, 0x41 -> jne 0x1534ff */
  /* test eax, eax -> je 0x153576 */
  /* relift: test byte ptr [eax + 0x20], 2 -> je 0x153576 */
  friction_evaluate();
  /* test eax, eax -> je 0x15369a */
  /* relift: test byte ptr [eax + 0x20], 8 -> je 0x15362c */
  /* test eax, eax -> je 0x15369a */
  /* relift: test byte ptr [eax + 0x20], 4 -> je 0x15369a */
  friction_evaluate();
  /* relift: test byte ptr [esi + 0x20], 0x10 -> je 0x15374e */
  /* relift: test byte ptr [esi + 0x20], 0x20 -> je 0x15383c */
  /* relift: test byte ptr [esi + 0x20], 0x40 -> je 0x15397d */
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x15397d */
  FUN_00150710();
  /* test (char)eax, 0x41 -> jne 0x1538f6 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_0018f230((void *)0, (void *)0, (void *)0, (void *)0);
  object_translate(0, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  rotate_vector3d_by_sincos((float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, 0.0f);
  rotate_vector3d_by_sincos((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, 0.0f);
  /* relift: cmp eax, dword ptr [ecx] -> jne 0x1540d9 */
  /* relift: cmp word ptr [ebp - 0x44], 3 -> jl 0x1540d9 */
  /* relift: cmp word ptr [ebp - 0x48], 0 -> jne 0x1540d9 */
  /* cmp eax, 0x7f800000 -> je 0x1541ff */
  /* cmp edx, 0x7f800000 -> je 0x1541ff */
  /* cmp eax, 0x7f800000 -> je 0x1541ff */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  tag_get('syhp', 0);
  /* test (char)eax, 0x41 -> jne 0x1542d4 */
  /* relift: tail-call FUN_00152e40(); */
  FUN_001509c0((void *)(uintptr_t)eax, 0);
  /* cmp eax, edi -> je 0x154323 */
  /* relift: cmp dword ptr [ebx + 0x68], edi -> jle 0x154323 */
  FUN_001093b0((float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  FUN_00109120((float *)(uintptr_t)esi);
  /* cmp eax, ecx -> jl 0x1542f2 */
  FUN_00150ed0();
  object_get_and_verify_type(0, 0);
  real_vector3d_valid((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x154411 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test esi, esi -> je 0x1544a2 */
  real_vector3d_valid((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x154488 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_00152680();
  physics_compute_unit_collisions();
  /* test (char)eax, (char)eax -> je 0x154506 */
  /* test (char)eax, 0x41 -> jne 0x154530 */
  /* test (char)eax, (char)eax -> je 0x15452c */
  /* test (char)eax, 0x41 -> jne 0x1545bf */
  /* test (char)eax, 1 -> jne 0x154584 */
  /* test (char)eax, 1 -> jne 0x15459a */
  /* test (char)eax, 1 -> jne 0x1545e5 */
  /* test (char)eax, 0x41 -> je 0x154619 */
  /* test (char)eax, 0x41 -> jne 0x154673 */
  FUN_00154540();
  FUN_00154540();
  /* test (char)eax, 1 -> je 0x154668 */
  FUN_00154540();
  FUN_001544d0((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, eax, 0.0f);
  /* test (char)eax, (char)eax -> je 0x154727 */
  /* test (char)eax, 0x41 -> jne 0x15473c */
  FUN_001546f0();
  FUN_001544d0((float *)(uintptr_t)esi, (float *)(uintptr_t)ebx, edi, 0.0f);
  FUN_001546f0();
  FUN_001546f0();
  FUN_00154540();
  FUN_001544d0((float *)(uintptr_t)edi, (float *)(uintptr_t)esi, ebx, 0.0f);
  FUN_001546f0();
  display_assert((char *)0x0029d978, (char *)0x0029d984, 332, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x154921 */
  display_assert((char *)0x0029d96c, (char *)0x0029d984, 333, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x154941 */
  display_assert((char *)0x0029d958, (char *)0x0029d984, 334, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x154988 */
  display_assert((char *)0x0025f120, (char *)0x0029d984, 335, 0);
  system_exit(0);
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  valid_real_point3d((float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x154abb */
  csprintf((char *)0x005ab100, (char *)0x0026ae04);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  real_vector3d_valid((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x154b15 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test eax, eax -> je 0x154b49 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x154b49 */
  display_assert((char *)0x0029d9c0, (char *)0x0029d984, 187, 0);
  system_exit(0);
  /* test (char)eax, 1 -> je 0x154b79 */
  display_assert((char *)0x0029d9b0, (char *)0x0029d984, 188, 0);
  system_exit(0);
  /* test (char)ecx, 1 -> je 0x154be0 */
  FUN_00190240();
  FUN_00190550();
  /* test (char)ebx, (char)ebx -> je 0x154c16 */
  /* test ecx, ecx -> je 0x154c92 */
  /* test (char)eax, 0x41 -> jne 0x154d0b */
  /* test (char)eax, 2 -> je 0x154d5f */
  /* relift: test byte ptr [ebp + 8], 4 -> jne 0x154d5f */
  display_assert((char *)0x00253440, (char *)0x0029d984, 269, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 0x10], 3 -> jge 0x154f4d */
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x154f23 */
  /* test (char)eax, 0x41 -> jne 0x154e16 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x154e30 */
  /* cmp (int16_t)eax, 2 -> jne 0x154e3f */
  /* test eax, eax -> je 0x154e57 */
  /* test eax, eax -> je 0x154e65 */
  FUN_0010b8a0((float *)(uintptr_t)esi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* cmp eax, -1 -> je 0x154f3c */
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x154f77 */
  display_assert((char *)0x00253418, (char *)0x0029d984, 312, 0);
  system_exit(0);
  FUN_00189150(0, (float *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)eax);
  game_globals_get();
  /* test esi, esi -> jne 0x154fe9 */
  display_assert((char *)0x0029da34, (char *)0x0029da44, 24, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 428);
  /* mem[0x00476204] = eax */
  display_assert((char *)0x0029da1c, (char *)0x0029da44, 26, 0);
  system_exit(0);
  FUN_00181150();
  rasterizer_text_cache_flush();
  FUN_0017d950();
  /* test eax, eax -> je 0x155055 */
  csmemset((void *)(uintptr_t)eax, 0, 16);
  FUN_0017dec0(0);
  /* mem[0x00476204] = 0 */
  FUN_0017d980();
  rasterizer_text_cache_flush();
  /* mem[0x00476204] = 0 */
  /* mem[0x005a5e1c] = eax */
  Direct3D_CreateDevice();
  /* cmp esi, 0x52 -> jge 0x15514b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x155159 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15516e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15517a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x155186 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x155192 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15519e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1551aa */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1551b6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x1551c2 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x1551ce */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x1551da */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1551e6 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x1551f5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x155204 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x155213 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x155222 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x155231 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x155240 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15524f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15525e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15526d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15527c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15528b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15529a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1552a9 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1552b8 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x1552c7 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x1552d5 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x1552ec */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1552f9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x155306 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x155313 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x155320 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_Release();
  D3DDevice_GetDeviceCaps((void *)(uintptr_t)eax);
  D3DDevice_Present((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_GetBackBuffer(0, ecx, (void *)(uintptr_t)eax);
  D3DDevice_CreateTexture(eax, edx, ecx, eax, edx, ecx, (void *)(uintptr_t)eax);
  D3DDevice_CreateVolumeTexture();
  D3DDevice_CreateCubeTexture();
  /* relift: FUN_001eeab0(0, 0, 0); */
  /* mem[0x00476a50] = eax */
  error(0, (char *)0x0029dbd4);
  error(0, (char *)0x0029dba8);
  csmemset((void *)(uintptr_t)eax, 0, 52);
  Direct3D_CreateDevice();
  /* cmp eax, esi -> jl 0x15548b */
  FUN_00167ff0(0, (char *)0x0029db10);
  /* relift: cmp dword ptr [0x476ab0], esi -> jne 0x1554a7 */
  /* test (char)ebx, (char)ebx -> jne 0x1554c5 */
  /* mem[0x00476ab0] = esi */
  error(0, (char *)0x0029dae8);
  D3DDevice_GetDeviceCaps((void *)0x005a59e0);
  D3DDevice_Present((void *)(uintptr_t)esi, (void *)(uintptr_t)esi, (void *)(uintptr_t)esi, (void *)(uintptr_t)esi);
  D3DDevice_Release();
  /* mem[0x00476ab0] = esi */
  /* mem[0x00476a50] = esi */
  D3DDevice_CreatePalette();
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_GetDepthStencilSurface((void *)(uintptr_t)eax);
  D3DDevice_Clear(edx, (void *)(uintptr_t)ecx, eax, edx, 0.0f, eax);
  /* test esi, esi -> jne 0x1555ab */
  display_assert((char *)0x00263768, (char *)0x0029dc0c, 209, 0);
  system_exit(0);
  display_assert((char *)0x00261d30, (char *)0x0029dc0c, 223, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x155611 */
  display_assert((char *)0x0029dbfc, (char *)0x0029dc0c, 226, 0);
  system_exit(0);
  D3DDevice_SetViewport((void *)(uintptr_t)eax);
  /* cmp esi, 0x52 -> jge 0x15564f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x155662 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15567f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15568f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15569f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1556af */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1556bf */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1556cf */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1556df */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x1556ef */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x1556ff */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15570f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15571f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x155732 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x155745 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x155758 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15576b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15577e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x155791 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1557a4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1557b7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1557ca */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1557dd */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1557f0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x155803 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x155816 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x155829 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15583c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15584a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  D3DDevice_SetTexture(ecx, (void *)(uintptr_t)eax);
  D3DDevice_SetPalette();
  /* cmp edx, 0x16 -> jge 0x1558b0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1558c1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1558d2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1558e3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1558f0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShader(eax);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetShaderConstantMode();
  D3DDevice_SetStreamSource(edx, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetIndices();
  D3DDevice_SetPixelShaderProgram((void *)(uintptr_t)eax);
  D3DDevice_SetVerticalBlankCallback();
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* test eax, eax -> jne 0x1559f9 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1331, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x155a2c */
  display_assert((char *)0x0029dc54, (char *)0x0029dc0c, 1440, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x155a69 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1629, 0);
  system_exit(0);
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1648, 0);
  system_exit(0);
  FUN_0016FDD0();
  FUN_0017ff50();
  D3DDevice_SetTexture(esi, (void *)0);
  /* test (char)ebx, (char)ebx -> je 0x155ac0 */
  FUN_00167ff0(0, (char *)0x0029dcfc);
  D3DDevice_SetStreamSource(esi, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> je 0x155af2 */
  FUN_00167ff0(0, (char *)0x0029dcb8);
  D3DDevice_SetIndices();
  FUN_00167ff0(0, (char *)0x0029dc80);
  error(0, (char *)0x0029dc58);
  D3DTexture_GetSurfaceLevel();
  D3DTexture_LockRect((void *)(uintptr_t)ecx, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  rasterizer_memory_pool_delete();
  FUN_0015e9e0();
  FUN_00184690();
  FUN_00178ab0();
  FUN_0017e040();
  FUN_0017ff60();
  rasterizer_text_cache_dispose();
  FUN_0015c680();
  FUN_0016fec0();
  FUN_00165a10();
  FUN_0017d990();
  texture_cache_delete();
  /* test eax, eax -> je 0x155be4 */
  D3DDevice_Release();
  /* mem[0x00476ab0] = 0 */
  /* test eax, eax -> je 0x155bf7 */
  /* mem[0x00476a50] = 0 */
  D3DDevice_SetVerticalBlankCallback();
  /* cmp (int16_t)esi, 4 -> jl 0x155c54 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 1935, 0);
  system_exit(0);
  /* test edi, edi -> je 0x155c84 */
  profile_texture_start();
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)edi, 0, 0);
  profile_texture_end();
  D3DDevice_SetTexture(eax, (void *)(uintptr_t)edi);
  display_assert((char *)0x0029dd68, (char *)0x0029dc0c, 1943, 0);
  error(0, (char *)0x0029dd38);
  D3DVolumeTexture_LockBox();
  /* test (int16_t)edi, (int16_t)edi -> jl 0x155d06 */
  /* cmp (int16_t)edi, 4 -> jl 0x155d26 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 1958, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x155d69 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x155d69 */
  FUN_00076ff0(0, 0);
  /* test eax, eax -> je 0x155d69 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  display_assert((char *)0x0029ddd8, (char *)0x0029dc0c, 1982, 0);
  error(0, (char *)0x0029dd38);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x155db6 */
  /* cmp (int16_t)edi, 4 -> jl 0x155dd6 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 2003, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x155e33 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x155e33 */
  FUN_00076ff0(0, 0);
  /* test esi, esi -> je 0x155e33 */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)esi, 0, 0);
  /* test eax, eax -> je 0x155e2c */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  display_assert((char *)0x0029de10, (char *)0x0029dc0c, 2035, 0);
  error(0, (char *)0x0029dd38);
  /* cmp (int16_t)eax, 4 -> jl 0x155eb6 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 2058, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x155ec7 */
  /* cmp (int16_t)edi, 3 -> jl 0x155ee7 */
  display_assert((char *)0x00264a4c, (char *)0x0029dc0c, 2059, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x155ef5 */
  /* cmp (int16_t)ebx, 4 -> jl 0x155f15 */
  display_assert((char *)0x0029df10, (char *)0x0029dc0c, 2060, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x155f28 */
  /* cmp (int16_t)ebx, 3 -> je 0x155fc0 */
  /* cmp esi, -1 -> je 0x155fc0 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x155fc0 */
  FUN_00076ff0(0, 0);
  /* relift: cmp word ptr [esi + 0xa], (int16_t)edi -> jne 0x155f97 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  bitmap_type_get_string(0);
  bitmap_type_get_string(0);
  error(0, (char *)0x0029ded0);
  /* cmp eax, -1 -> je 0x156024 */
  FUN_00076ff0(0, 0);
  /* test esi, esi -> je 0x156024 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  display_assert((char *)0x0029de9c, (char *)0x0029dc0c, 2117, 0);
  error(0, (char *)0x0029de58);
  D3DCubeTexture_LockRect();
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1560b1 */
  /* cmp (int16_t)eax, 4 -> jl 0x1560d1 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 2142, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1560e2 */
  /* cmp (int16_t)edi, 3 -> jl 0x156102 */
  display_assert((char *)0x00264a4c, (char *)0x0029dc0c, 2143, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x156110 */
  /* cmp (int16_t)ebx, 4 -> jl 0x156130 */
  display_assert((char *)0x0029df10, (char *)0x0029dc0c, 2144, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x15613f */
  /* cmp (int16_t)ebx, 3 -> je 0x1561b0 */
  /* cmp esi, -1 -> je 0x1561b0 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x1561b0 */
  FUN_00076ff0(0, 0);
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)esi, 0, 0);
  /* test eax, eax -> je 0x156204 */
  /* relift: cmp word ptr [esi + 0xa], (int16_t)edi -> je 0x1561da */
  bitmap_type_get_string(0);
  bitmap_type_get_string(0);
  error(0, (char *)0x0029ded0);
  /* cmp eax, -1 -> je 0x15620b */
  FUN_00076ff0(0, 0);
  /* test esi, esi -> je 0x15620b */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  display_assert((char *)0x0029df3c, (char *)0x0029dc0c, 2210, 0);
  error(0, (char *)0x0029de58);
  /* cmp eax, 6 -> ja 0x1563c0 */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x156291 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2232, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x1562c0 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2236, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x1562ef */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2240, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x15631e */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2244, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x15634d */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2248, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x15637c */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2252, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x156393 */
  /* cmp (int16_t)esi, 4 -> jl 0x1563b3 */
  display_assert((char *)0x0029dfa0, (char *)0x0029dc0c, 2256, 0);
  system_exit(0);
  display_assert((char *)0x0029df78, (char *)0x0029dc0c, 2260, 0);
  system_exit(0);
  D3DPalette_Lock();
  /* test (int16_t)edi, (int16_t)edi -> jge 0x15646d */
  display_assert((char *)0x0029e084, (char *)0x0029dc0c, 2613, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x43 -> jl 0x156493 */
  display_assert((char *)0x0029e054, (char *)0x0029dc0c, 2614, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edi, word ptr [0x325164] -> je 0x156505 */
  /* cmp ecx, -1 -> je 0x1564d8 */
  D3DDevice_SetVertexShader(ecx);
  /* mem[0x005a5558] = edx */
  error(0, (char *)0x0029e02c);
  error(0, (char *)0x0029dffc);
  /* test esi, esi -> jne 0x15653f */
  display_assert((char *)0x0029e09c, (char *)0x0029dc0c, 2652, 0);
  system_exit(0);
  D3DDevice_SetRenderState_PSTextureModes();
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb76c] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb778] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb774] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6b8] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb744] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb748] = edi */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  /* test (char)ebx, (char)ebx -> jne 0x15667e */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x15668b */
  D3DDevice_SetRenderStateNotInline();
  /* test (char)eax, (char)eax -> jne 0x156699 */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x1566a6 */
  D3DDevice_SetRenderStateNotInline();
  /* mem[0x005a555c] = edx */
  D3DDevice_SetPixelShaderProgram((void *)(uintptr_t)esi);
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x156704 */
  /* test esi, esi -> jne 0x15673b */
  display_assert((char *)0x0029e128, (char *)0x0029dc0c, 2749, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0 -> jne 0x156760 */
  display_assert((char *)0x0029e110, (char *)0x0029dc0c, 2750, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x15676f */
  /* cmp (int16_t)eax, 0x2c -> jl 0x15678f */
  display_assert((char *)0x0029e0b0, (char *)0x0029dc0c, 2751, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 4], (int16_t)edx -> jle 0x156812 */
  /* relift: cmp (int16_t)edx, word ptr [esi + 4] -> jl 0x156798 */
  D3DDevice_SetVertexShaderConstant(0, (void *)0x00476208, edx);
  /* relift: cmp word ptr [0x3256ba], 0 -> je 0x156848 */
  /* mem[0x005a5550] = ecx */
  /* test edi, edi -> jne 0x15687c */
  display_assert((char *)0x0029e178, (char *)0x0029dc0c, 2826, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x156997 */
  /* cmp esi, eax -> jl 0x1568c5 */
  csprintf((char *)0x005ab100, (char *)0x0029e148);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x1568fe */
  display_assert((char *)0x0029e134, (char *)0x0029dc0c, 2837, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx + 0x1c], 0xbf800000 -> je 0x156985 */
  csmemset((void *)(uintptr_t)esi, 0, 48);
  D3DResource_Release((void *)(uintptr_t)eax);
  /* test esi, esi -> jne 0x156a1b */
  display_assert((char *)0x0029e178, (char *)0x0029dc0c, 2874, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x156a5f */
  csmemset((void *)(uintptr_t)edx, 0, 0);
  D3DSurface_GetDesc((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DSurface_LockRect((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* test ebx, ebx -> jne 0x156ae1 */
  display_assert((char *)0x00291690, (char *)0x0029dc0c, 2896, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x156af0 */
  /* cmp (int16_t)eax, 2 -> jle 0x156b10 */
  display_assert((char *)0x0029e1f8, (char *)0x0029dc0c, 2897, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x156b1f */
  /* cmp (int16_t)eax, 2 -> jle 0x156b3f */
  display_assert((char *)0x0029e190, (char *)0x0029dc0c, 2898, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x156b79 */
  csmemset((void *)(uintptr_t)eax, 0, 176);
  /* relift: cmp word ptr [ebx + 0x40], (int16_t)esi -> jle 0x156b8a */
  rasterizer_set_model_lighting_point_light();
  /* cmp (int16_t)esi, 2 -> jl 0x156b80 */
  FUN_001569f0();
  /* cmp (int16_t)esi, 2 -> jl 0x156bb0 */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 11);
  /* test eax, eax -> jne 0x156c62 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 2967, 0);
  system_exit(0);
  render_camera_hack_frustum_z();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* cmp eax, 0x80 -> jl 0x156da0 */
  /* mem[0x005a5580] = eax */
  /* mem[0x005a5584] = eax */
  /* mem[0x005a5588] = eax */
  /* mem[0x005a558c] = eax */
  /* test eax, eax -> jne 0x156e2f */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 239, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x157940 */
void FUN_00157940(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> jne 0x15796c */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1256, 0);
  system_exit(0);
  FUN_0017dee0();
  /* mem[0x005a5e18] = ecx */
  FUN_0016f730();
  FUN_0017eb90();
  FUN_001792a0();
  FUN_00181180();
  texture_cache_idle();
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* test (char)eax, (char)eax -> je 0x1579c6 */
  FUN_0015b220();
  decals_update();

  (void)eax;
  (void)ecx;
}

/* 0x1579d0 */
void FUN_001579d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test ebx, ebx -> jne 0x1579fe */
  display_assert((char *)0x0029dc54, (char *)0x0029dc0c, 1452, 0);
  system_exit(0);
  /* mem[0x005a5db8] = 0x3f800000 */
  /* test (char)eax, (char)eax -> jne 0x157a6b */
  /* mem[0x005a5db8] = 0 */
  /* mem[0x005a5dbc] = eax */
  /* mem[0x005a5de4] = 0x3f800000 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x157b11 */
  /* relift: test byte ptr [ebx], 4 -> jne 0x157b11 */
  /* test (char)ecx, (char)ecx -> je 0x157b11 */
  /* cmp (int16_t)eax, 2 -> jne 0x157ba7 */
  display_assert((char *)0x0029f0f8, (char *)0x0029dc0c, 1498, 0);
  system_exit(0);
  /* mem[0x005a5dec] = 0x3f800000 */
  FUN_00099490((float *)0, (float *)0, (float *)0);
  /* mem[0x005a5de4] = 0 */
  /* mem[0x005a5de8] = 0x3f800000 */
  /* mem[0x005a5dec] = 0x3f800000 */
  /* mem[0x005a5dd8] = edx */
  /* mem[0x005a5ddc] = eax */
  /* mem[0x005a5de0] = ecx */
  /* mem[0x005a5dc8] = edx */
  /* mem[0x005a5dcc] = eax */
  /* mem[0x005a5dd0] = ecx */
  /* test (char)eax, 1 -> je 0x157bdb */
  display_assert((char *)0x0029f080, (char *)0x0029dc0c, 1511, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x157c0e */
  display_assert((char *)0x0029f040, (char *)0x0029dc0c, 1512, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x157c41 */
  display_assert((char *)0x0029f008, (char *)0x0029dc0c, 1513, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x157d91 */
  /* test (char)eax, 0x41 -> jne 0x157dd2 */
  /* test (char)eax, 0x41 -> jne 0x157e0d */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  FUN_000d1dd0((void *)0x005a5dac);
  D3DDevice_SetRenderState_FogColor();
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1689, 0);
  system_exit(0);
  /* test edi, edi -> je 0x15804a */
  /* test eax, eax -> je 0x15804a */
  /* cmp (int16_t)ecx, 0xb -> je 0x157efd */
  /* cmp (int16_t)ecx, 0xa -> jne 0x158038 */
  /* relift: cmp word ptr [edi + 0x14], 0 -> jne 0x158038 */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x158038 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x158038 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 4] -> jg 0x158038 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 6] -> jg 0x158038 */
  D3DDevice_GetBackBuffer(0, 0, (void *)(uintptr_t)ecx);
  D3DSurface_GetDesc((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* cmp eax, ecx -> jne 0x158031 */
  D3DSurface_LockRect((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)0, 192);
  /* test eax, eax -> je 0x15802a */
  bitmap_format_bits_per_pixel(0);
  /* cmp ecx, eax -> je 0x157fea */
  display_assert((char *)0x0029f268, (char *)0x0029dc0c, 1732, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x158026 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0);
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x157ff3 */
  error(0, (char *)0x0029f1b8);
  D3DDevice_Present((void *)0, (void *)0, (void *)(uintptr_t)eax, (void *)0);
  FUN_00167ff0(0, (char *)0x0029f158);
  /* mem[0x00325668] = edx */
  /* mem[0x0032566c] = ecx */
  error(0, (char *)0x0029f134);
  /* cmp (int16_t)esi, 8 -> jl 0x1580e4 */
  display_assert((char *)0x0029f2d8, (char *)0x0029dc0c, 1907, 0);
  system_exit(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = esi */
  /* cmp eax, 7 -> ja 0x1583ce */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x158188 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2280, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x1581d9 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2287, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x158235 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2293, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x158280 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2298, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x1582cb */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2303, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x158316 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2308, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x158349 */
  /* cmp (int16_t)esi, 4 -> jl 0x158369 */
  display_assert((char *)0x0029dfa0, (char *)0x0029dc0c, 2313, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> je 0x1583b1 */
  display_assert((char *)0x0029dfec, (char *)0x0029dc0c, 2331, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1583ee */
  display_assert((char *)0x0029df78, (char *)0x0029dc0c, 2336, 0);
  system_exit(0);
  /* test (char)ebx, (char)ebx -> je 0x158419 */
  /* test edi, edi -> jne 0x158419 */
  display_assert((char *)0x0029f344, (char *)0x0029dc0c, 2340, 0);
  system_exit(0);
  D3DDevice_SetRenderTarget((void *)(uintptr_t)esi, (void *)(uintptr_t)ebx);
  /* cmp (int16_t)edi, (int16_t)ebx -> jne 0x158459 */
  D3DSurface_GetDesc((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx);
  D3DDevice_SetViewport((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1584ba */
  /* cmp (int16_t)edi, 1 -> jne 0x1584a8 */
  D3DDevice_Clear(ebx, (void *)(uintptr_t)ebx, eax, edx, 0.0f, ebx);
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2415, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1585a2 */
  D3DDevice_GetBackBuffer(0, 0, (void *)(uintptr_t)ecx);
  D3DResource_Release((void *)(uintptr_t)eax);
  /* test eax, eax -> jl 0x158590 */
  FUN_00167ff0(0, (char *)0x0029f454);
  /* test esi, esi -> jne 0x1585d5 */
  display_assert((char *)0x0029f448, (char *)0x0029dc0c, 2499, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x158613 */
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2457, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x158640 */
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2461, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x158670 */
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2465, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x1586a0 */
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2469, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x1586d0 */
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2473, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1586e6 */
  /* cmp (int16_t)edi, 4 -> jle 0x158706 */
  display_assert((char *)0x0029f400, (char *)0x0029dc0c, 2477, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x158736 */
  display_assert((char *)0x0029f480, (char *)0x0029dc0c, 2492, 0);
  system_exit(0);
  display_assert((char *)0x0029df78, (char *)0x0029dc0c, 2496, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 4 -> jle 0x15878e */
  display_assert((char *)0x0029f400, (char *)0x0029dc0c, 2508, 0);
  system_exit(0);
  D3DDevice_SetTexture(edx, (void *)0);
  FUN_00167ff0(0, (char *)0x0029f3a0);
  error(0, (char *)0x0029f368);
  /* test esi, esi -> jne 0x15882e */
  display_assert((char *)0x0026184c, (char *)0x0029dc0c, 2532, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x158857 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 2533, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x158ad5 */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x158ad5 */
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 1 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae0] = 8 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_End();
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 3034, esi);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x158b1f */
  /* relift: cmp (int16_t)edi, word ptr [0x325168] -> je 0x158dd3 */
  /* cmp eax, 5 -> ja 0x158dad */
  D3DDevice_SetRenderState_StencilEnable(0);
  D3DDevice_SetRenderState_StencilEnable(esi);
  D3DDevice_SetRenderState_StencilFail(7680);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a8] = 0x1e00 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7ac] = 0x1e01 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7b0] = 0x207 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7b4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7b8] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7bc] = esi */
  D3DDevice_SetRenderState_StencilEnable(esi);
  D3DDevice_SetRenderState_StencilFail(7680);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a8] = edx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7ac] = 0x1e00 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7b0] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7b4] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7b8] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7bc] = 0 */
  D3DDevice_SetRenderState_StencilEnable(esi);
  D3DDevice_SetRenderState_StencilFail(7680);
  SetRenderStateSmart(68, 7680);
  SetRenderStateSmart(69, 7680);
  SetRenderStateSmart(70, 517);
  SetRenderStateSmart(71, 0);
  SetRenderStateSmart(72, 0);
  SetRenderStateSmart(73, 0);
  SetRenderStateSmart(124, 0);
  SetRenderStateSmart(125, 7680);
  SetRenderStateSmart(68, 7680);
  SetRenderStateSmart(69, 7681);
  SetRenderStateSmart(70, 514);
  SetRenderStateSmart(71, 0);
  SetRenderStateSmart(72, 0);
  SetRenderStateSmart(73, 0);
  SetRenderStateSmart(124, 0);
  SetRenderStateSmart(125, 7680);
  SetRenderStateSmart(68, 7680);
  SetRenderStateSmart(69, 7680);
  SetRenderStateSmart(70, 514);
  SetRenderStateSmart(71, 0);
  SetRenderStateSmart(72, 0);
  SetRenderStateSmart(73, 0);
  display_assert((char *)0x0029f490, (char *)0x0029dc0c, 3099, esi);
  system_exit(0);
  display_assert((char *)0x0029f510, (char *)0x0029dc0c, 1351, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x158e46 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1352, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x476abc], (int16_t)edi -> je 0x158e6a */
  /* relift: cmp word ptr [ebx + 2], (int16_t)edi -> jne 0x158e6a */
  rasterizer_memory_pool_reset();
  FUN_0015d060();
  rasterizer_transparent_geometry_begin();
  FUN_001659f0();
  FUN_001812b0();
  FUN_001792C0(0);
  FUN_001592e0(0);
  FUN_0016f880();
  FUN_00158ae0(0);
  rasterizer_environment_fog_screen_end((void *)(uintptr_t)edx);
  /* relift: cmp word ptr [0x3256bc], 1 -> jne 0x158ed0 */
  FUN_000d1dd0((void *)0x005a5dac);
  /* test (int16_t)eax, (int16_t)eax -> je 0x158f00 */
  /* cmp (int16_t)eax, 1 -> je 0x158f00 */
  FUN_0016f910(0);
  FUN_00158140(0, 0, esi, 0, 0);
  FUN_0016fa40(0);
  /* relift: cmp word ptr [ebx], 0 -> jne 0x158f5f */
  display_assert((char *)0x0029f4b4, (char *)0x0029dc0c, 1415, 0);
  system_exit(0);
  rasterizer_set_frustum_z(0.0f, 0.0f);
  D3DDevice_SetRenderState_FillMode(edx);
  /* test eax, eax -> jne 0x158fbf */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1567, 0);
  system_exit(0);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x158feb */
  /* relift: cmp word ptr [0x3256ea], 0 -> jne 0x158feb */
  D3DDevice_Clear(0, (void *)0, 128, 0, 0.0f, 0);
  /* test (char)eax, (char)eax -> je 0x159018 */
  FUN_00158800((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [0x5a5bc2], -1 -> jne 0x159034 */
  FUN_0017ebb0((void *)0x005a5400);
  FUN_0017ef00();
  /* test (char)eax, (char)eax -> jne 0x159060 */
  FUN_001825d0();
  FUN_0015d160();
  FUN_00184680();
  FUN_00165a00();
  FUN_00181410();
  FUN_0017e030();
  FUN_0017e010();
  FUN_0016FEB0();
  /* test (char)eax, 1 -> jne 0x15909d */
  display_assert((char *)0x00269fe0, (char *)0x00269ffc, 291, 0);
  system_exit(0);
  /* cmp esi, 0x52 -> jge 0x1590fb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x159109 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15911e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15912a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x159136 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x159142 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15914e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15915a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x159166 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x159172 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15917e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15918a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x159196 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x1591a5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x1591b4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x1591c3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1591d2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1591e1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1591f0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1591ff */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15920e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15921d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15922c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15923b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15924a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x159259 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x159268 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x159277 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x159285 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x15929c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1592a9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1592b6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1592c3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1592d0 */
  D3DDevice_SetTextureState_BumpEnv();
  /* cmp esi, 0x52 -> jge 0x15931f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x159332 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15934f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15935f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15936f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15937f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15938f */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15939f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1593af */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x1593bf */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x1593cf */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x1593df */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1593ef */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x159402 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x159415 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x159428 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15943b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15944e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x159461 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x159474 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x159487 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15949a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1594ad */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1594c0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x1594d3 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1594e6 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1594f9 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15950c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15951a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x159530 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x159541 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x159552 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x159563 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x159570 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* test eax, eax -> jne 0x1595ec */
  display_assert((char *)0x0029dc40, (char *)0x0029f570, 41, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1598f3 */
  /* test (char)eax, (char)eax -> je 0x1598f3 */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> je 0x15962d */
  display_assert((char *)0x0029f520, (char *)0x0029f570, 46, 0);
  system_exit(0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 1 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae0] = 8 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00158140(0, 0, 0, 0, 0);
  FUN_00158ae0(0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 320, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 320, 240);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 240);
  D3DDevice_End();
  FUN_00158140(0, 0, 0, 0, 0);
  FUN_00158ae0(0);
  FUN_00158800((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1598ec */
  display_assert((char *)0x0026276c, (char *)0x0029f570, 152, ebx);
  system_exit(0);
  /* test eax, eax -> jne 0x15995c */
  display_assert((char *)0x0029f6b0, (char *)0x0029f570, 153, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x14], (int16_t)ebx -> je 0x159981 */
  display_assert((char *)0x0029f670, (char *)0x0029f570, 154, ebx);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x1599b0 */
  display_assert((char *)0x0029f64c, (char *)0x0029f570, 155, ebx);
  system_exit(0);
  display_assert((char *)0x0029f62c, (char *)0x0029f570, 156, ebx);
  system_exit(0);
  /* test eax, eax -> jne 0x159a07 */
  display_assert((char *)0x0029dc40, (char *)0x0029f570, 157, ebx);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x15a0d8 */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x15a0d8 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x159a5b */
  display_assert((char *)0x0029f600, (char *)0x0029f570, 164, ebx);
  system_exit(0);
  /* relift: test byte ptr [esi], 2 -> je 0x159a7f */
  display_assert((char *)0x0029f5b8, (char *)0x0029f570, 165, ebx);
  system_exit(0);
  rasterizer_set_frustum_z(0.0f, 0.0f);
  /* relift: cmp dword ptr [esi + 0x18], 0x3f800000 -> jne 0x159cb6 */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(edx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00184610((void *)(uintptr_t)esi);
  FUN_00178b40(13, 0, 0);
  FUN_00190e10((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, (float *)0, (float *)0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ae4] = 0x1800 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00174510((void *)(uintptr_t)esi, 0);
  csmemset((void *)(uintptr_t)edx, 0, 40);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);
  csmemset((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> je 0x159d48 */
  csmemset((void *)(uintptr_t)eax, 0, 0);
  rasterizer_psuedo_dynamic_screen_quad_draw(0);
  FUN_0017d1a0(0);
  FUN_0017cbb0((void *)(uintptr_t)ecx, 0);
  FUN_0017cbc0(0, 0, 0, 0, 0, 0, 0);
  FUN_0017cbe0();
  FUN_0017cbf0();
  rasterizer_psuedo_dynamic_screen_quad_draw(0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetRenderState_CullMode(edx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_ZBias(edi);
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 770);
  SetRenderStateSmart(63, 771);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(59, 0);
  FUN_00184610((void *)(uintptr_t)esi);
  FUN_00178b40(64, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x2623 */
  /* mem[0x005a5ba0] = edi */
  /* mem[0x005a5b9c] = 0x11 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0x3420140c */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5b48] = ecx */
  FUN_00159070(0.0f);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0xa0c0000 */
  /* mem[0x005a5ae4] = 0x1100 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00174510((void *)(uintptr_t)esi, 0);
  rasterizer_set_frustum_z(0.0f, 0.0f);
  /* cmp esi, 0x52 -> jge 0x15a0fb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15a109 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15a11e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15a12a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15a136 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15a142 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15a14e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15a15a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15a166 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15a172 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15a17e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15a18a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15a196 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15a1a5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15a1b4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15a1c3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15a1d2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15a1e1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15a1f0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15a1ff */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15a20e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15a21d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15a22c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15a23b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15a24a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15a259 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15a268 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15a277 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15a285 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp esi, 0x52 -> jge 0x15a2bf */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15a2d2 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15a2ef */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15a2ff */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15a30f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15a31f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15a32f */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15a33f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15a34f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15a35f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15a36f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15a37f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15a38f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15a3a2 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15a3b5 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15a3c8 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15a3db */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15a3ee */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15a401 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15a414 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15a427 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15a43a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15a44d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15a460 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15a473 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15a486 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15a499 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15a4ac */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15a4ba */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetVertexData4f(ecx, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_SetVertexDataColor(ecx, eax);
  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* cmp eax, ebx -> jne 0x15a58c */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 19, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x3256dd], (char)ebx -> je 0x15a6f0 */
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(eax);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae0] = 4 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 1 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  /* mem[0x005a5ae4] = 0x1400 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* test eax, eax -> jne 0x15a726 */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 81, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 1 */
  D3DDevice_SetRenderState_ZBias(eax);
  FUN_00178b40(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae0] = 4 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* test ebx, ebx -> je 0x15a80b */
  /* test edi, edi -> jne 0x15a828 */
  display_assert((char *)0x0029f6f8, (char *)0x0029f6c0, 116, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15a84e */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 117, 0);
  system_exit(0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test eax, eax -> je 0x15a8b9 */
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test ebx, ebx -> je 0x15a912 */
  /* test eax, eax -> je 0x15a912 */
  /* test edi, edi -> jne 0x15a932 */
  display_assert((char *)0x0029f70c, (char *)0x0029f6c0, 139, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15a95b */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 140, 0);
  system_exit(0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test eax, eax -> je 0x15a9c6 */
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test eax, eax -> jne 0x15aa6f */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 167, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae0] = 4 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* test edi, edi -> je 0x15abfb */
  /* test eax, eax -> je 0x15abfb */
  /* test esi, esi -> jne 0x15ac1b */
  display_assert((char *)0x0029f6f8, (char *)0x0029f6c0, 221, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ac44 */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 222, 0);
  system_exit(0);
  FUN_000d1dd0((float *)(uintptr_t)esi);
  FUN_000d1dd0((float *)(uintptr_t)esi);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, ebx);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexDataColor(0, edx);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test ebx, ebx -> je 0x15acde */
  /* cmp (int16_t)edi, 1 -> jg 0x15acfe */
  display_assert((char *)0x0029f7c0, (char *)0x0029f6c0, 249, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ad27 */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 250, 0);
  system_exit(0);
  FUN_000d1dd0((float *)(uintptr_t)ebx);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, ebx);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x15ad6c */
  FUN_00167ff0(0, (char *)0x0029f750);
  D3DDevice_End();
  FUN_00167ff0(0, (char *)0x0029f728);
  /* cmp esi, 0x52 -> jge 0x15adbb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15adc9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15adde */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15adea */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15adf6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15ae02 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15ae0e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15ae1a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15ae26 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15ae32 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15ae3e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15ae4a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15ae56 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15ae65 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15ae74 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15ae83 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15ae92 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15aea1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15aeb0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15aebf */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15aece */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15aedd */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15aeec */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15aefb */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15af0a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15af19 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15af28 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15af37 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15af45 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x15af5c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15af69 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x15af76 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15af83 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x15af90 */
  D3DDevice_SetTextureState_BumpEnv();
  lruv_cache_has_query_cb((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x15afd2 */
  display_assert((char *)0x0029f930, (char *)0x0029f95c, 29, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x15b0a1 */
  display_assert((char *)0x0029f924, (char *)0x0029f95c, 30, 0);
  system_exit(0);
  display_assert((char *)0x0029f914, (char *)0x0029f95c, 32, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 1 -> je 0x15b057 */
  /* test (char)eax, (char)eax -> jne 0x15b057 */
  error(0, (char *)0x0029f8b8);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 2 -> je 0x15b095 */
  /* test (char)eax, (char)eax -> jne 0x15b095 */
  error(0, (char *)0x0029f858);
  decal_delete(0);
  /* cmp esi, -1 -> jne 0x15b018 */
  /* test esi, esi -> jne 0x15b127 */
  display_assert((char *)0x0029f924, (char *)0x0029f95c, 71, 0);
  system_exit(0);
  display_assert((char *)0x0029f914, (char *)0x0029f95c, 73, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* mem[0x0032516c] = esi */
  /* cmp esi, -1 -> jne 0x15b105 */
  /* test eax, eax -> jne 0x15b176 */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 116, 0);
  system_exit(0);
  lruv_cache_set_callbacks((void *)(uintptr_t)eax, (void *)0x0015afa0, (void *)0x0015b0c0);
  /* test eax, eax -> jne 0x15b1c9 */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 131, 0);
  system_exit(0);
  decals_update_for_new_map(0);
  lruv_cache_dispose_all((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x15b209 */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 142, 0);
  system_exit(0);
  decals_update_for_new_map(0);
  lruv_cache_dispose_all((void *)(uintptr_t)eax);
  lruv_idle((void *)(uintptr_t)eax);
  /* cmp esi, 0x52 -> jge 0x15b24f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15b262 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15b27f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15b28f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15b29f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15b2af */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15b2bf */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15b2cf */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15b2df */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15b2ef */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15b2ff */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15b30f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15b31f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15b332 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15b345 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15b358 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15b36b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15b37e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15b391 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15b3a4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15b3b7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15b3ca */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15b3dd */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15b3f0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15b403 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15b416 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15b429 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15b43c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15b44a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp ebx, 0x10 -> ja 0x15b48c */
  display_assert((char *)0x0029f9d4, (char *)0x0029f95c, 204, 0);
  system_exit(0);
  /* test (char)ebx, 0xf -> je 0x15b4b1 */
  display_assert((char *)0x0029f9a8, (char *)0x0029f95c, 205, 0);
  system_exit(0);
  FUN_0011de10((void *)(uintptr_t)eax, ebx);
  /* cmp edx, 0x16 -> jge 0x15b4e0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15b4f1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x15b502 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15b513 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x15b520 */
  D3DDevice_SetTextureState_BumpEnv();
  /* cmp esi, -1 -> jne 0x15b55b */
  display_assert((char *)0x0029f9fc, (char *)0x0029f95c, 262, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15b584 */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 263, 0);
  system_exit(0);
  lruv_block_delete((void *)(uintptr_t)eax, 0);
  D3DDevice_DrawVertices(eax, edx, ecx);
  D3DDevice_SetStreamSource(edx, (void *)(uintptr_t)ecx, eax);
  /* cmp (int16_t)eax, 3 -> jne 0x15b602 */
  FUN_00158ae0(0);
  /* cmp (int16_t)eax, 5 -> jge 0x15b63e */
  FUN_0016fa40(ecx);
  D3DDevice_SetVertexData4ub(ecx, eax, edx, ecx, eax);
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DResource_Register((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DVertexBuffer_Lock();
  /* test eax, eax -> jne 0x15b6f6 */
  display_assert((char *)0x0029dc40, (char *)0x0029f95c, 89, 0);
  system_exit(0);
  debug_malloc(12, 0, (char *)0x0029f95c, 91);
  /* mem[0x00476ad8] = eax */
  display_assert((char *)0x0029fa54, (char *)0x0029f95c, 92, 0);
  system_exit(0);
  game_state_gpu_alloc((char *)0x0029fa44, 0, 0x00028000);
  display_assert((char *)0x0029fa24, (char *)0x0029f95c, 96, 0);
  system_exit(0);
  D3DResource_Register((void *)(uintptr_t)ecx, (void *)0);
  lruv_cache_new((char *)0x0029fa10, 2560, 0, 2048, (void *)0x0015afa0, (void *)0x0015b0c0);
  /* mem[0x00476adc] = eax */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 106, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15b809 */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 153, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15b832 */
  display_assert((char *)0x0029fa54, (char *)0x0029f95c, 154, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15b85b */
  display_assert((char *)0x0029dc40, (char *)0x0029f95c, 155, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15b874 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* mem[0x00476ad8] = 0 */
  lruv_cache_dispose((void *)(uintptr_t)eax);
  display_assert((char *)0x0029f9fc, (char *)0x0029f95c, 217, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15b8ec */
  display_assert((char *)0x0029f994, (char *)0x0029f95c, 218, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15b915 */
  display_assert((char *)0x0029dc40, (char *)0x0029f95c, 219, 0);
  system_exit(0);
  lruv_block_get_address((void *)(uintptr_t)eax, 0);
  D3DVertexBuffer_Lock();
  /* cmp eax, ebx -> jne 0x15b9a6 */
  display_assert((char *)0x0029dc40, (char *)0x0029f95c, 283, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x15d8b0 */
void FUN_0015d8b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a0110, 741, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x15dc0c */
  /* cmp edi, -1 -> je 0x15dbf3 */
  /* cmp esi, -1 -> je 0x15dbf3 */
  /* test eax, eax -> jne 0x15d932 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 756, 0);
  system_exit(0);
  /* test edi, edi -> jge 0x15d956 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 759, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [0x47dbe0] -> jl 0x15d97e */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 760, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15d9a2 */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 761, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15d9ca */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 762, 0);
  system_exit(0);
  FUN_00180050(0);
  /* test edi, edi -> jne 0x15da22 */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp edi, 0x476b60 -> jne 0x15da43 */
  /* test eax, eax -> jne 0x15da70 */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 773, 0);
  system_exit(0);
  /* test eax, eax -> jge 0x15da97 */
  display_assert((char *)0x002a04a0, (char *)0x002a0110, 776, 0);
  system_exit(0);
  /* cmp ecx, eax -> jle 0x15dac5 */
  display_assert((char *)0x002a0438, (char *)0x002a0110, 777, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebx], 0 -> jge 0x15daea */
  display_assert((char *)0x002a0784, (char *)0x002a0110, 780, 0);
  system_exit(0);
  /* test edi, edi -> jge 0x15db11 */
  display_assert((char *)0x002a0770, (char *)0x002a0110, 781, 0);
  system_exit(0);
  /* cmp edi, ecx -> jle 0x15db3b */
  display_assert((char *)0x002a0720, (char *)0x002a0110, 782, 0);
  system_exit(0);
  /* cmp edi, 0x2710 -> jle 0x15db48 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)eax, edx);
  /* test (char)eax, (char)eax -> je 0x15db62 */
  FUN_00167ff0(0, (char *)0x002a03e0);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15db8b */
  FUN_00167ff0(0, (char *)0x002a06a0);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15dbc8 */
  FUN_00167ff0(0, (char *)0x002a05a8);
  error(0, (char *)0x002a0560);
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 823, 0);
  system_exit(0);
  /* test esi, esi -> jle 0x15de4e */
  /* cmp edi, -1 -> je 0x15de36 */
  /* test ebx, ebx -> je 0x15de36 */
  /* test eax, eax -> je 0x15de36 */
  /* test eax, eax -> jne 0x15dcab */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 834, 0);
  system_exit(0);
  /* test edi, edi -> jge 0x15dccf */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 837, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [0x47dbe0] -> jl 0x15dcf7 */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 838, 0);
  system_exit(0);
  FUN_00180050(0);
  /* test eax, eax -> jge 0x15dd38 */
  display_assert((char *)0x002a0784, (char *)0x002a0110, 845, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15dd5c */
  display_assert((char *)0x002a0770, (char *)0x002a0110, 846, 0);
  system_exit(0);
  /* cmp esi, ecx -> jle 0x15dd86 */
  display_assert((char *)0x002a0720, (char *)0x002a0110, 847, 0);
  system_exit(0);
  /* cmp esi, 0x2710 -> jle 0x15dd93 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)eax, edx);
  /* test (char)eax, (char)eax -> je 0x15ddad */
  FUN_00167ff0(0, (char *)0x002a09a8);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15ddd4 */
  FUN_00167ff0(0, (char *)0x002a0950);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15de0b */
  FUN_00167ff0(0, (char *)0x002a0868);
  error(0, (char *)0x002a0820);
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 890, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x15e0e2 */
  /* cmp edi, -1 -> je 0x15e0c9 */
  /* test ebx, ebx -> je 0x15e0c9 */
  /* test eax, eax -> je 0x15e0c9 */
  /* test esi, esi -> je 0x15e0c9 */
  /* test eax, eax -> je 0x15e0c9 */
  /* test eax, eax -> jne 0x15df02 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 903, 0);
  system_exit(0);
  /* test edi, edi -> jge 0x15df26 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 906, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [0x47dbe0] -> jl 0x15df4e */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 907, 0);
  system_exit(0);
  FUN_00180050(0);
  FUN_00180050(0);
  /* test eax, eax -> jge 0x15df9c */
  display_assert((char *)0x002a0784, (char *)0x002a0110, 915, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15dfc3 */
  display_assert((char *)0x002a0770, (char *)0x002a0110, 916, 0);
  system_exit(0);
  /* cmp esi, edx -> jle 0x15dfed */
  display_assert((char *)0x002a0720, (char *)0x002a0110, 917, 0);
  system_exit(0);
  /* cmp esi, 0x2710 -> jle 0x15dffa */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ecx, ebx);
  /* test (char)eax, (char)eax -> je 0x15e014 */
  FUN_00167ff0(0, (char *)0x002a0bd8);
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ecx, edx);
  /* test (char)ebx, (char)ebx -> je 0x15e03f */
  FUN_00167ff0(0, (char *)0x002a0b58);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15e066 */
  FUN_00167ff0(0, (char *)0x002a0950);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15e09e */
  FUN_00167ff0(0, (char *)0x002a0a70);
  error(0, (char *)0x002a0a28);
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 963, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x15e42c */
  /* test eax, eax -> je 0x15e413 */
  /* test ecx, ecx -> je 0x15e413 */
  /* cmp esi, -1 -> je 0x15e413 */
  /* test eax, eax -> jne 0x15e18b */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 977, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15e1af */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 980, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15e1d7 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 981, 0);
  system_exit(0);
  FUN_00180050(0);
  /* test edi, edi -> jne 0x15e222 */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp edi, 0x476b60 -> jne 0x15e23e */
  /* test ebx, ebx -> jne 0x15e265 */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 991, 0);
  system_exit(0);
  /* test eax, eax -> jge 0x15e28c */
  display_assert((char *)0x002a04a0, (char *)0x002a0110, 994, 0);
  system_exit(0);
  /* cmp eax, ecx -> jle 0x15e2ba */
  display_assert((char *)0x002a0438, (char *)0x002a0110, 995, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15e2e1 */
  display_assert((char *)0x002a0e84, (char *)0x002a0110, 998, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15e2f2 */
  /* cmp (int16_t)eax, 2 -> jl 0x15e312 */
  display_assert((char *)0x002a0e30, (char *)0x002a0110, 999, 0);
  system_exit(0);
  /* cmp edi, 0x2710 -> jle 0x15e322 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ebx, eax);
  /* test (char)eax, (char)eax -> je 0x15e339 */
  FUN_00167ff0(0, (char *)0x002a03e0);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15e362 */
  FUN_00167ff0(0, (char *)0x002a0d98);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15e3af */
  FUN_00167ff0(0, (char *)0x002a0cc8);
  display_assert((char *)0x002a0c9c, (char *)0x002a0110, 1030, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15e140 */
  error(0, (char *)0x002a0c58);
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 1063, 0);
  system_exit(0);
  /* test esi, esi -> jle 0x15e643 */
  /* test edi, edi -> je 0x15e62b */
  /* test eax, eax -> je 0x15e62b */
  /* test ebx, ebx -> je 0x15e62b */
  /* test eax, eax -> je 0x15e62b */
  /* test eax, eax -> jne 0x15e4d2 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 1073, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15e4f9 */
  display_assert((char *)0x002a0e84, (char *)0x002a0110, 1078, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15e507 */
  /* cmp (int16_t)eax, 2 -> jl 0x15e527 */
  display_assert((char *)0x002a0e30, (char *)0x002a0110, 1079, 0);
  system_exit(0);
  FUN_00180050(0);
  /* cmp esi, 0x2710 -> jle 0x15e542 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ecx, eax);
  /* test (char)eax, (char)eax -> je 0x15e559 */
  FUN_00167ff0(0, (char *)0x002a09a8);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15e57d */
  FUN_00167ff0(0, (char *)0x002a0fa8);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15e5c7 */
  FUN_00167ff0(0, (char *)0x002a0ee8);
  display_assert((char *)0x002a0c9c, (char *)0x002a0110, 1113, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15e47d */
  error(0, (char *)0x002a0ea0);
  /* cmp eax, -1 -> jne 0x15e69d */
  /* cmp eax, -1 -> je 0x15e69d */
  display_assert((char *)0x002a107c, (char *)0x002a0110, 1146, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x15e6e4 */
  /* cmp edi, -1 -> je 0x15e6e4 */
  display_assert((char *)0x002a1014, (char *)0x002a0110, 1150, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x15e71a */
  /* test esi, esi -> je 0x15e703 */
  FUN_0015e430();
  FUN_0015e0f0();
  FUN_0015dc10();
  /* relift: tail-call FUN_0015d8b0(); */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DVertexBuffer_Lock();
  D3DResource_Release((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x15e82c */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 93, 0);
  system_exit(0);
  D3DDevice_CreateIndexBuffer();
  /* test eax, eax -> jl 0x15e84f */
  FUN_00167ff0(0, (char *)0x002a1370);
  /* test eax, eax -> jne 0x15e86c */
  /* test (char)ebx, (char)ebx -> jne 0x15e889 */
  /* mem[0x0047dbe8] = 0 */
  error(0, (char *)0x002a1338);
  /* cmp (int16_t)ecx, 0xc -> jge 0x15e950 */
  FUN_00180050(0);
  D3DDevice_CreateVertexBuffer(eax, 520, 0, 0, (void *)(uintptr_t)edi);
  /* test (char)ebx, (char)ebx -> je 0x15e904 */
  /* test eax, eax -> jl 0x15e904 */
  FUN_00167ff0(0, (char *)0x002a1268);
  /* relift: cmp dword ptr [edi], 0 -> jne 0x15e91d */
  /* test (char)ebx, (char)ebx -> jne 0x15e936 */
  error(0, (char *)0x002a1230);
  /* test (char)ebx, (char)ebx -> je 0x15e9a8 */
  FUN_00180050(0);
  D3DDevice_CreateVertexBuffer(eax, 520, 0, 0, (void *)0);
  /* test eax, eax -> jl 0x15e97d */
  FUN_00167ff0(0, (char *)0x002a1128);
  /* test eax, eax -> jne 0x15e99a */
  /* test (char)ebx, (char)ebx -> jne 0x15e9b7 */
  /* mem[0x0047dbf0] = 0 */
  error(0, (char *)0x002a10ec);
  /* relift: FUN_e912e9e3(0, 0); */
  /* test eax, eax -> jne 0x15ea09 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 263, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15ea27 */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DResource_Release((void *)(uintptr_t)eax);
  /* mem[0x0047dbf0] = 0 */
  /* test eax, eax -> je 0x15ea61 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* mem[0x0047dbe8] = 0 */
  /* test eax, eax -> jne 0x15eaa0 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 331, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15eb78 */
  /* test esi, esi -> jge 0x15ead0 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 337, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47dbe0] -> jl 0x15eaf8 */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 338, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15eb21 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 340, 0);
  system_exit(0);
  display_assert((char *)0x002a14a4, (char *)0x002a0110, 344, 0);
  system_exit(0);
  error(0, (char *)0x002a1468);
  /* test eax, eax -> jne 0x15ebbc */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 373, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15ec3d */
  /* test esi, esi -> jge 0x15ebe9 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 377, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47dbe0] -> jl 0x15ec11 */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 378, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ec4c */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 380, 0);
  system_exit(0);
  error(0, (char *)0x002a14d0);
  /* test eax, eax -> jne 0x15ec81 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 519, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x325652], 0 -> jne 0x15ec9a */
  error(0, (char *)0x002a15d8);
  /* cmp esi, -1 -> je 0x15ee64 */
  /* test esi, esi -> jge 0x15ecca */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 535, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15ecf2 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 536, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ed1b */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 539, 0);
  system_exit(0);
  FUN_00180050(0);
  display_assert((char *)0x002a15b4, (char *)0x002a0110, 544, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0xc -> jl 0x15ed81 */
  display_assert((char *)0x002a1574, (char *)0x002a0110, 545, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15eda8 */
  display_assert((char *)0x002a154c, (char *)0x002a0110, 546, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x15edda */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp ebx, 0x476b60 -> jne 0x15edfb */
  /* test eax, eax -> jne 0x15ee28 */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 551, 0);
  system_exit(0);
  D3DVertexBuffer_Lock();
  error(0, (char *)0x002a1510);
  /* test eax, eax -> jne 0x15eeac */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 582, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15efde */
  /* test esi, esi -> jge 0x15eedd */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 588, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15ef05 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 589, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ef2e */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 591, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15ef45 */
  /* cmp (int16_t)eax, 0xc -> jl 0x15ef65 */
  display_assert((char *)0x002a1668, (char *)0x002a0110, 595, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x15ef96 */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp esi, 0x476b60 -> jne 0x15efb4 */
  /* test esi, esi -> jne 0x15efed */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 600, 0);
  system_exit(0);
  error(0, (char *)0x002a1628);
  /* cmp esi, 0x52 -> jge 0x15f00b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15f019 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15f02e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15f03a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15f046 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15f052 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15f05e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15f06a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15f076 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15f082 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15f08e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15f09a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15f0a6 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15f0b5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15f0c4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15f0d3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15f0e2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15f0f1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15f100 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15f10f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15f11e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15f12d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15f13c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15f14b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15f15a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15f169 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15f178 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15f187 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15f195 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x15f1ac */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15f1b9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x15f1c6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15f1d3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x15f1e0 */
  D3DDevice_SetTextureState_BumpEnv();
  FUN_0016f910(27);
  FUN_0016fa40(27);
  display_assert((char *)0x002a16bc, (char *)0x002a16c4, 220, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x15f273 */
  display_assert((char *)0x002a16ac, (char *)0x002a16c4, 221, 0);
  system_exit(0);
  /* cmp esi, 0x52 -> jge 0x15f33f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15f352 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15f36f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15f37f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15f38f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15f39f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15f3af */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15f3bf */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15f3cf */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15f3df */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15f3ef */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15f3ff */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15f40f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15f422 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15f435 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15f448 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15f45b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15f46e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15f481 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15f494 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15f4a7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15f4ba */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15f4cd */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15f4e0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15f4f3 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15f506 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15f519 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15f52c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15f53a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  display_assert((char *)0x002a1704, (char *)0x002a16c4, 255, 0);
  system_exit(0);
  /* cmp edx, 0x16 -> jge 0x15f580 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15f591 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x15f5a2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15f5b3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x15f5c0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);
  D3DDevice_SetVertexDataColor(ecx, eax);
  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* cmp eax, ebx -> jne 0x15f65f */
  display_assert((char *)0x0029dc40, (char *)0x002a16c4, 38, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x3256d8], (char)ebx -> je 0x15f89b */
  /* relift: test byte ptr [ebp + 0x24], 0x20 -> je 0x15f698 */
  /* relift: cmp word ptr [eax + 0x24], 1 -> je 0x15f698 */
  display_assert((char *)0x002a17a8, (char *)0x002a16c4, 42, 0);
  system_exit(0);
  /* relift: cmp word ptr [ecx + 0x24], 1 -> je 0x15f6bf */
  display_assert((char *)0x002a1780, (char *)0x002a16c4, 44, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0x15f6e5 */
  display_assert((char *)0x002a1774, (char *)0x002a16c4, 52, 0);
  system_exit(0);
  rasterizer_transparent_geometry_group_new();
  /* cmp esi, ebx -> je 0x15f87b */
  /* relift: cmp word ptr [eax + 0x24], 1 -> jne 0x15f814 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 1 -> je 0x15f817 */
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x15f899 */
  /* mem[0x005a5504] = esi */
  /* mem[0x005a5508] = edx */
  /* mem[0x005a550c] = eax */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5510] = ecx */
  /* relift: cmp byte ptr [0x47dbf6], (char)ebx -> jne 0x15f899 */
  error(0, (char *)0x002a1744);
  D3DDevice_SetVertexDataColor(0, eax);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* cmp eax, ebx -> jne 0x15f915 */
  display_assert((char *)0x0029dc40, (char *)0x002a16c4, 756, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x160433 */
  /* relift: cmp word ptr [0x5a5bc0], (int16_t)ebx -> jne 0x160433 */
  display_assert((char *)0x0029f510, (char *)0x002a16c4, 761, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0xc], ebx -> jne 0x15f97d */
  display_assert((char *)0x002a18a4, (char *)0x002a16c4, 763, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x14], ebx -> je 0x15f9a7 */
  /* relift: cmp dword ptr [esi + 0x10], ebx -> jne 0x15f9ac */
  display_assert((char *)0x002a1878, (char *)0x002a16c4, 765, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x10], ebx -> je 0x15f9d0 */
  /* relift: cmp dword ptr [esi], ebx -> je 0x15f9d0 */
  display_assert((char *)0x002a1840, (char *)0x002a16c4, 767, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_001580b0(0);
  /* cmp edx, ebx -> je 0x15fa6f */
  /* cmp edx, ebx -> je 0x15fa91 */
  /* cmp eax, ebx -> je 0x15fc19 */
  /* cmp eax, ebx -> je 0x15fc32 */
  /* cmp eax, ebx -> je 0x15fc4d */
  /* cmp eax, ebx -> je 0x15fc63 */
  /* cmp eax, ebx -> je 0x15fc78 */
  /* cmp eax, ebx -> je 0x15fc8b */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x15fd8e */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp (int16_t)ebx, 3 -> jl 0x15fce1 */
  FUN_00178b40(0, 0, 0);
  /* test edi, edi -> je 0x15ffc7 */
  /* test (char)eax, (char)eax -> jne 0x15fdd0 */
  display_assert((char *)0x002a182c, (char *)0x002a16c4, 886, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x18], 0x3f800000 -> je 0x15fdf8 */
  display_assert((char *)0x002a1814, (char *)0x002a16c4, 887, ebx);
  system_exit(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x8001 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetTextureStageState(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = 0x11104 */
  /* mem[0x005a5ae8] = ecx */
  /* test (char)eax, 0x41 -> je 0x15fec2 */
  FUN_00159070(0.0f);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5ac0] = 0x12081208 */
  /* mem[0x005a5b48] = 0x1120e820 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5b0c] = ecx */
  /* mem[0x005a5ac4] = 0x6c200000 */
  /* mem[0x005a5b2c] = 0xc0 */
  /* mem[0x005a5b4c] = 0x3c011c02 */
  /* mem[0x005a5b78] = edx */
  /* mem[0x005a5af0] = eax */
  /* mem[0x005a5b10] = ecx */
  /* mem[0x005a5ac8] = 0x820b220 */
  /* mem[0x005a5b30] = edx */
  /* mem[0x005a5b7c] = edx */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5af4] = ecx */
  /* mem[0x005a5b14] = edx */
  /* mem[0x005a5acc] = 0x12201120 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0xc200120 */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ae0] = 0xc180000 */
  /* test eax, eax -> je 0x1603ae */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = eax */
  /* test ecx, ecx -> jne 0x160022 */
  /* test ecx, ecx -> jne 0x16003c */
  /* test eax, eax -> je 0x16008a */
  /* test eax, eax -> je 0x1600a2 */
  FUN_000d1c90((float *)(uintptr_t)eax);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1c90((float *)(uintptr_t)ecx);
  /* mem[0x005a5b08] = eax */
  FUN_000d1c90((float *)(uintptr_t)edx);
  /* mem[0x005a5aec] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5af8] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5afc] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5b00] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5b04] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x8010902 */
  /* mem[0x005a5ac0] = 0x18111912 */
  /* mem[0x005a5b4c] = 0xa010804 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ac4] = 0x1a111814 */
  /* mem[0x005a5b2c] = eax */
  /* cmp eax, 5 -> ja 0x160287 */
  /* mem[0x005a5b50] = 0xc200920 */
  /* mem[0x005a5ac8] = 0x1c201920 */
  /* mem[0x005a5b7c] = edi */
  /* mem[0x005a5b50] = 0xc20e920 */
  /* mem[0x005a5ac8] = 0x1c20f920 */
  /* mem[0x005a5b50] = 0xc090000 */
  /* mem[0x005a5b7c] = ebx */
  /* mem[0x005a5ac8] = 0x1c190000 */
  /* mem[0x005a5b30] = ebx */
  /* mem[0x005a5b7c] = 0x20c0 */
  /* mem[0x005a5b50] = 0xc090000 */
  /* mem[0x005a5ac8] = 0x1c190000 */
  /* mem[0x005a5b30] = edi */
  /* mem[0x005a5ac8] = 0x820a920 */
  /* mem[0x005a5b50] = 0x1920b820 */
  /* mem[0x005a5acc] = 0x1c1c0c0c */
  /* mem[0x005a5b34] = 0x24c00 */
  /* mem[0x005a5b54] = eax */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ad0] = 0x5c5c */
  /* mem[0x005a5b38] = 0x4d00 */
  /* mem[0x005a5b58] = eax */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5ad4] = eax */
  /* mem[0x005a5b3c] = edx */
  /* mem[0x005a5b5c] = 0x1ca01da0 */
  /* mem[0x005a5b88] = edx */
  /* mem[0x005a5b30] = edx */
  /* mem[0x005a5b7c] = edx */
  /* test eax, eax -> je 0x16038d */
  /* cmp eax, 4 -> ja 0x16038c */
  /* relift: cmp word ptr [esi + 0x84], 5 -> jne 0x1602d5 */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetRenderState_CullMode(2305);
  FUN_00178b40(0, 0, 0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, ecx);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp esi, 0x52 -> jge 0x16048b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x160499 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1604ae */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1604ba */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1604c6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1604d2 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1604de */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1604ea */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1604f6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x160502 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16050e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16051a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x160526 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x160535 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x160544 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x160553 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x160562 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x160571 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x160580 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16058f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16059e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1605ad */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1605bc */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1605cb */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x1605da */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1605e9 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1605f8 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x160607 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x160615 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16062c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x160639 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x160646 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x160653 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x160660 */
  D3DDevice_SetTextureState_BumpEnv();
  /* cmp esi, 0x52 -> jge 0x16068f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1606a2 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1606bf */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1606cf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1606df */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1606ef */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1606ff */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16070f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16071f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16072f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16073f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16074f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16075f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x160772 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x160785 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x160798 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1607ab */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1607be */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1607d1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1607e4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1607f7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16080a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16081d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x160830 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x160843 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x160856 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x160869 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x16087c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x16088a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  D3DDevice_SetTexture(ecx, (void *)(uintptr_t)eax);
  /* cmp edx, 0x16 -> jge 0x1608b0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1608c1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1608d2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1608e3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1608f0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  FUN_0016fa40(0);
  FUN_0016fa40(0);
  FUN_00158ae0(0);
  FUN_0016fa40(0);
  FUN_0016fa40(11);
  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2163, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x160ba4 */
  /* test (char)eax, (char)eax -> je 0x160ba4 */
  /* test (char)eax, (char)eax -> je 0x160ba4 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x160ba4 */
  /* test (char)eax, (char)eax -> jne 0x160ba4 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2173, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, 0x41 -> je 0x160a83 */
  /* test (char)eax, 0x41 -> jne 0x160ba1 */
  FUN_00178b40(58, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  FUN_00159070(0.0f);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6e0] = esi */
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x160ba1 */
  /* mem[0x005a548c] = eax */
  /* mem[0x005a5488] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5484] = ecx */
  FUN_0016fa40(13);
  FUN_0016f910(14);
  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x160c99 */
  /* cmp (int16_t)eax, 2 -> je 0x160c99 */
  /* cmp (int16_t)eax, 6 -> je 0x160c99 */
  /* cmp (int16_t)eax, 3 -> je 0x160c99 */
  /* cmp (int16_t)eax, 4 -> je 0x160c99 */
  /* cmp (int16_t)eax, 7 -> je 0x160c99 */
  /* cmp (int16_t)eax, 5 -> je 0x160c99 */
  /* cmp (int16_t)eax, 8 -> jne 0x160db3 */
  /* test (char)eax, (char)eax -> je 0x160db3 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1010101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 1 */
  D3DDevice_SetRenderState_ZBias(0);
  /* test eax, eax -> jne 0x160dea */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 68, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x160e23 */
  /* cmp (int16_t)eax, 2 -> je 0x160e23 */
  /* cmp (int16_t)eax, 6 -> je 0x160e23 */
  /* cmp (int16_t)eax, 3 -> je 0x160e23 */
  /* cmp (int16_t)eax, 4 -> je 0x160e23 */
  /* cmp (int16_t)eax, 7 -> je 0x160e23 */
  /* cmp (int16_t)eax, 5 -> je 0x160e23 */
  /* cmp (int16_t)eax, 8 -> jne 0x160f3d */
  /* test (char)eax, (char)eax -> je 0x160f3d */
  /* test esi, esi -> je 0x160ecb */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTexture(0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x160f3c */
  /* cmp (int16_t)eax, 2 -> jne 0x160f09 */
  random_math_real((void *)(uintptr_t)eax);
  random_math_real((void *)(uintptr_t)ecx);
  random_math_real((void *)(uintptr_t)edx);
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 135, ebx);
  system_exit(0);
  /* cmp (int16_t)eax, 9 -> jne 0x161693 */
  /* relift: cmp word ptr [eax], (int16_t)ebx -> jne 0x161ecc */
  /* cmp (int16_t)edx, 0x33 -> jge 0x161ecc */
  /* cmp eax, esi -> je 0x1612f8 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(edi);
  FUN_00178b40(37, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = edx */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* mem[0x005a5b94] = 3 */
  /* mem[0x005a5ae8] = 0xff0000 */
  /* mem[0x005a5b08] = 0xff */
  /* mem[0x005a5b48] = 0x4849484a */
  /* mem[0x005a5b74] = 0x30cd */
  /* mem[0x005a5b4c] = 0xc0c0d0d */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b50] = 0xc010d02 */
  /* mem[0x005a5b7c] = 0xc00 */
  /* mem[0x005a5ae0] = eax */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ae0] = edx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_0015de60();
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x1616c6 */
  /* cmp (int16_t)eax, 2 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 6 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 3 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 4 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 7 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 5 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 8 -> jne 0x161ecc */
  /* test (char)eax, (char)eax -> je 0x161ecc */
  /* relift: cmp dword ptr [ebp + 8], edi -> jne 0x1616f6 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 347, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x1c], edi -> jne 0x161719 */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 348, ebx);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)edx, 0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)eax);
  FUN_00178b40(16, 0, 0);
  /* test (char)ebx, (char)eax -> je 0x161756 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = eax */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [edi + 0x180], (char)ebx -> je 0x161850 */
  SetTextureStageStateSmart(0, 13, 0);
  SetTextureStageStateSmart(0, 14, 0);
  SetTextureStageStateSmart(0, 13, 0);
  SetTextureStageStateSmart(0, 14, 0);
  SetTextureStageStateSmart(0, 15, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x16de60 */
void FUN_0016de60(void)
{
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);

  (void)edx;
}

/* 0x16de80 */
void FUN_0016de80(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_SetVertexData4f(ecx, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x16dee0 */
void FUN_0016dee0(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  interface_get_tag_index(12);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(13);
  FUN_00076ff0(0, 0);
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 27, ebx);
  system_exit(0);
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)esi, 0, ebx);
  /* test eax, eax -> je 0x16e152 */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)edi, 0, ebx);
  /* test eax, eax -> je 0x16e152 */
  FUN_00158140(0, 0, 0, 0, 0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ae0] = 0x8040000 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x16e160 */
void FUN_0016e160(void)
{
  int eax = 0;

  interface_get_tag_index(12);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(13);
  FUN_00076ff0(0, 0);
  /* test eax, eax -> jne 0x16e1bc */
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 109, 0);
  system_exit(0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x16e2ce */
  /* test (char)eax, (char)eax -> je 0x16e2ce */
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();

  (void)eax;
}

/* 0x16e2e0 */
void FUN_0016e2e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  interface_get_tag_index(0);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(0);
  FUN_00076ff0(0, 0);
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 156, esi);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x16ea58 */
  /* test (char)eax, (char)eax -> je 0x16ea2e */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)edi, 0, esi);
  /* test eax, eax -> je 0x16ea2e */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)ebx, 0, esi);
  /* test eax, eax -> je 0x16ea2e */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)edi);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureState_BorderColor(0, 0x46000000);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = esi */
  /* mem[0x005a5b94] = esi */
  /* mem[0x005a5b48] = 0x8040000 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ac0] = 0x18140000 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)ecx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x302 */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = esi */
  /* mem[0x005a5b94] = esi */
  /* mem[0x005a5ae0] = ebx */
  /* mem[0x005a5ae4] = edi */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  FUN_00158140(0, 0, 0, 0, 0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetTextureState_BorderColor(0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 0);
  SetRenderStateSmart(63, 771);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = esi */
  /* mem[0x005a5b94] = esi */
  /* mem[0x005a5ae0] = ebx */
  /* mem[0x005a5ae4] = edi */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  local_player_count();
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  /* test (char)eax, (char)eax -> je 0x16ea58 */
  /* test (char)eax, (char)eax -> je 0x16ea58 */
  FUN_00158140(0, 0, 0, 0, 0);
  /* cmp esi, 0x52 -> jge 0x16ea7b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16ea89 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16ea9e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16eaaa */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16eab6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16eac2 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16eace */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16eada */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16eae6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16eaf2 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16eafe */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16eb0a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16eb16 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x16eb25 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x16eb34 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16eb43 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x16eb52 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16eb61 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x16eb70 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16eb7f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16eb8e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16eb9d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16ebac */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x16ebbb */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x16ebca */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x16ebd9 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x16ebe8 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x16ebf7 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x16ec05 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16ec1c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x16ec29 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x16ec36 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x16ec43 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x16ec50 */
  D3DDevice_SetTextureState_BumpEnv();
  /* cmp esi, 0x52 -> jge 0x16ec7f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16ec92 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16ecaf */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16ecbf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16eccf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16ecdf */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16ecef */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16ecff */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16ed0f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16ed1f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16ed2f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16ed3f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16ed4f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x16ed62 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x16ed75 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16ed88 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x16ed9b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16edae */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x16edc1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16edd4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16ede7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16edfa */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16ee0d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x16ee20 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x16ee33 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x16ee46 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x16ee59 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x16ee6c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x16ee7a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16ee90 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x16eea1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x16eeb2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x16eec3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x16eed0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  /* test eax, eax -> jne 0x16ef1f */
  display_assert((char *)0x0029dc40, (char *)0x002a3a4c, 21, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x16f472 */
  FUN_001906b0((void *)(uintptr_t)eax, 10);
  /* test edx, edx -> je 0x16ef80 */
  /* cmp (int16_t)ecx, 1 -> jl 0x16ef80 */
  /* cmp (int16_t)ecx, 4 -> jg 0x16ef80 */
  /* cmp (int16_t)ecx, 1 -> jl 0x16efaf */
  /* cmp (int16_t)ecx, 4 -> jg 0x16efaf */
  FUN_001d9e70(0.0f, 0.0f);
  /* cmp (int16_t)ecx, 1 -> jl 0x16efd4 */
  /* cmp (int16_t)ecx, 4 -> jg 0x16efd4 */
  FUN_001d9e70(0.0f, 0.0f);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00184610((void *)(uintptr_t)edi);
  FUN_00178b40(15, 0, 0);
  display_assert((char *)0x002a3a18, (char *)0x002a3a4c, 105, 0);
  system_exit(0);
  display_assert((char *)0x002a39e4, (char *)0x002a3a4c, 106, 0);
  system_exit(0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x42 */
  /* mem[0x005a5b94] = 0x104 */
  /* mem[0x005a5ac0] = 0x820a920 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x1920b820 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ac4] = 0x1c1c0c0c */
  /* mem[0x005a5b2c] = 0x24c00 */
  /* mem[0x005a5b4c] = esi */
  /* mem[0x005a5b78] = esi */
  /* mem[0x005a5ac8] = 0x5c5c */
  /* mem[0x005a5b30] = 0x4d00 */
  /* mem[0x005a5b50] = esi */
  /* mem[0x005a5b7c] = esi */
  /* mem[0x005a5acc] = 0x14150000 */
  /* mem[0x005a5b34] = 0x40 */
  /* mem[0x005a5b54] = 0x1c051da0 */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = 0x1c1c1400 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00174510((void *)(uintptr_t)edi, 0);
  /* test esi, esi -> jne 0x16f4a4 */
  display_assert((char *)0x00294af0, (char *)0x002a3ca4, 60, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x16f4f0 */
  /* relift: cmp word ptr [0x47e468], 3 -> jge 0x16f4f0 */
  error(0, (char *)0x002a3c7c);
  error(0, (char *)0x002a3c5c);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x16f5e8 */
  /* cmp (int16_t)esi, 0x1d -> jge 0x16f5e8 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* test (char)ebx, (char)ebx -> je 0x16f579 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x16f692 */
  /* cmp (int16_t)esi, 0x10 -> jge 0x16f692 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* test (char)ebx, 1 -> je 0x16f67b */
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16f6b6 */
  /* test (char)eax, (char)eax -> jne 0x16f6b6 */
  csmemset((void *)0x0047e108, 0, 128);
  csmemset((void *)0x0047e088, 0, 128);
  csmemset((void *)0x0047e008, 0, 128);
  QueryPerformanceFrequency((void *)0x00325178);
  /* cmp eax, ebx -> jne 0x16f760 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 194, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x47e468], (int16_t)esi -> jge 0x16f79a */
  error(0, (char *)0x002a3c5c);
  /* relift: cmp word ptr [0x47e468], (int16_t)esi -> jge 0x16f7d4 */
  error(0, (char *)0x002a3c5c);
  /* relift: cmp word ptr [0x47e468], (int16_t)esi -> jge 0x16f80f */
  error(0, (char *)0x002a3c5c);
  /* relift: cmp byte ptr [0x325704], (char)ebx -> je 0x16f875 */
  /* mem[0x0047e45c] = ebx */
  /* mem[0x0047e440] = ebx */
  /* mem[0x0047e444] = ebx */
  D3DDevice_InsertCallback(ebx, (void *)0x0016f610, eax);
  /* test (char)eax, (char)eax -> je 0x16f8dd */
  /* relift: cmp word ptr [0x47e458], 0 -> jg 0x16f8d4 */
  display_assert((char *)0x002a3d48, (char *)0x002a3ca4, 244, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x47e458], 0x64 -> jl 0x16f907 */
  display_assert((char *)0x002a3d2c, (char *)0x002a3ca4, 249, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16f93c */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 259, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16f953 */
  /* test (char)eax, (char)eax -> je 0x16fa35 */
  /* relift: cmp word ptr [0x325184], 0 -> jne 0x16fa35 */
  /* relift: cmp word ptr [0x47e458], 0 -> jne 0x16fa35 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x16f980 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16f9a0 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 265, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16f9c9 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 266, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  FUN_0016f480((char *)(uintptr_t)ecx, 0, 0);
  D3DDevice_InsertCallback(esi, (void *)0x0016f500, edx);
  /* test eax, eax -> jne 0x16fa6d */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 294, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16fa84 */
  /* test (char)eax, (char)eax -> je 0x16fb72 */
  /* relift: cmp word ptr [0x325184], 0 -> jne 0x16fb72 */
  /* relift: cmp word ptr [0x47e458], 0 -> jne 0x16fb72 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x16fab1 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16fad1 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 300, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16fafa */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 301, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  D3DDevice_InsertCallback(0, (void *)0x0016f500, ebx);
  /* mem[0x0047e45c] = eax */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x16fb93 */
  /* cmp (int16_t)esi, 0x1d -> jl 0x16fbc0 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 363, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x16fcea */
  /* test eax, eax -> jne 0x16fc24 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 375, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x1d -> jne 0x16fc64 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16fc91 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 391, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  /* test edx, eax -> je 0x16fce2 */
  /* test (char)ecx, (char)ecx -> je 0x16fdc4 */
  /* test eax, eax -> jne 0x16fd37 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 415, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x1d -> jne 0x16fd45 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x16fd50 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16fd70 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 430, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  /* test edx, eax -> je 0x16fdc1 */
  /* cmp eax, 0x7fffffff -> jbe 0x16fdc4 */
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16fded */
  /* test (char)eax, (char)eax -> je 0x16fe9d */
  /* test eax, eax -> jne 0x16fe16 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 455, 0);
  system_exit(0);
  /* cmp eax, 0x7fffffff -> jbe 0x16fe41 */
  /* mem[0x0047e448] = eax */
  /* mem[0x0047e44c] = edx */
  D3DDevice_InsertCallback(0, (void *)0x0016f610, ecx);
  FUN_0008f810(0, 0);
  /* cmp esi, 0x52 -> jge 0x16feeb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16fef9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16ff0e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16ff1a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16ff26 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16ff32 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16ff3e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16ff4a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16ff56 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16ff62 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16ff6e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16ff7a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16ff86 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x16ff95 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x16ffa4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16ffb3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x16ffc2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16ffd1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x16ffe0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16ffef */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16fffe */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17000d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17001c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x17002b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x17003a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x170049 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x170058 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x170067 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x170075 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x17008c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x170099 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1700a6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1700b3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1700c0 */
  D3DDevice_SetTextureState_BumpEnv();
  /* test esi, esi -> jne 0x1700f7 */
  display_assert((char *)0x002a3e7c, (char *)0x002a3e80, 30, 0);
  system_exit(0);
  display_assert((char *)0x002a3e60, (char *)0x002a3e80, 31, 0);
  system_exit(0);
  /* cmp esi, 0x52 -> jge 0x17017f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x170192 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1701af */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1701bf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1701cf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1701df */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1701ef */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1701ff */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x17020f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17021f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17022f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17023f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17024f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x170262 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x170275 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x170288 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x17029b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1702ae */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1702c1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1702d4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1702e7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1702fa */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17030d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x170320 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x170333 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x170346 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x170359 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x17036c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x17037a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x170390 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1703a1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1703b2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1703c3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1703d0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* test ebx, ebx -> jne 0x17046d */
  display_assert((char *)0x0029f510, (char *)0x002a3e80, 47, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x170493 */
  display_assert((char *)0x0029dc40, (char *)0x002a3e80, 48, 0);
  system_exit(0);
  /* test eax, eax -> je 0x17051d */
  /* relift: cmp word ptr [ebp + 8], 0 -> jg 0x170519 */
  /* relift: cmp word ptr [ebp + 0xc], (int16_t)edx -> je 0x170519 */
  /* relift: cmp word ptr [ebx + 2], 0 -> je 0x17051d */
  /* test (char)eax, (char)eax -> je 0x170532 */
  /* test (char)eax, (char)eax -> je 0x170549 */
  /* relift: test byte ptr [edi + 0xe], 0x10 -> je 0x1705f1 */
  FUN_001700d0();
  /* relift: test byte ptr [ecx + 0xe], 0x10 -> je 0x170613 */
  FUN_001700d0();
  FUN_001700d0();
  FUN_001700d0();
  /* relift: cmp edi, dword ptr [ebx + 8] -> jne 0x1708c2 */
  /* cmp edx, esi -> jne 0x1708e3 */
  /* relift: cmp edx, dword ptr [ebx + 8] -> jne 0x170918 */
  /* test (char)eax, (char)eax -> je 0x170955 */
  display_assert((char *)0x002a3edc, (char *)0x002a3e80, 176, 0);
  system_exit(0);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x170980 */
  display_assert((char *)0x002a3ec0, (char *)0x002a3e80, 177, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x17098f */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* cmp (int16_t)eax, 2 -> jne 0x170bf6 */
  /* test (char)eax, (char)eax -> je 0x170a8d */
  display_assert((char *)0x002a3edc, (char *)0x002a3e80, 198, 0);
  system_exit(0);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x170ab8 */
  display_assert((char *)0x002a3ec0, (char *)0x002a3e80, 199, 0);
  system_exit(0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* relift: cmp word ptr [ebp + 8], 1 -> jne 0x170c6e */
  /* test (char)eax, (char)eax -> je 0x170c6e */
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x170c2f */
  display_assert((char *)0x002a3ec0, (char *)0x002a3e80, 223, 0);
  system_exit(0);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x0029dc40, (char *)0x002a3e80, 251, 0);
  system_exit(0);
  FUN_0016f910(26);
  rasterizer_screen_effect_get_cinematic_parameters((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 2], 0 -> jne 0x170d1d */
  /* test eax, eax -> jne 0x170d1d */
  /* test (char)eax, 0x41 -> je 0x170d1d */
  /* test (char)eax, 0x41 -> je 0x170d1d */
  /* test (char)eax, (char)eax -> je 0x171b94 */
  /* test (char)eax, (char)eax -> je 0x171b94 */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x171b94 */
  /* test eax, eax -> jne 0x170d77 */
  display_assert((char *)0x002a4460, (char *)0x002a3e80, 276, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x170d9e */
  display_assert((char *)0x002a443c, (char *)0x002a3e80, 277, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0 -> je 0x170dc4 */
  display_assert((char *)0x002a4404, (char *)0x002a3e80, 278, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], 0 -> je 0x170deb */
  display_assert((char *)0x002a43d4, (char *)0x002a3e80, 279, 0);
  system_exit(0);
  display_assert((char *)0x002a439c, (char *)0x002a3e80, 280, 0);
  system_exit(0);
  /* test eax, eax -> je 0x170e42 */
  display_assert((char *)0x002a436c, (char *)0x002a3e80, 281, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], 1 -> jne 0x170e70 */
  /* test eax, eax -> je 0x170e70 */
  display_assert((char *)0x002a4340, (char *)0x002a3e80, 286, 0);
  system_exit(0);
  FUN_00178b40(38, 0, 0);
  /* relift: cmp word ptr [ebp - 0xc], 1 -> jne 0x170ec9 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x170ec1 */
  display_assert((char *)0x002a4338, (char *)0x002a3e80, 313, 0);
  system_exit(0);
  /* test (char)ecx, 1 -> jne 0x170ed7 */
  /* test (char)eax, (char)eax -> je 0x171065 */
  /* cmp (int16_t)ecx, 1 -> je 0x170f1e */
  display_assert((char *)0x002a4330, (char *)0x002a3e80, 334, 0);
  system_exit(0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)ecx);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [edx + 0xe], 0x10 -> je 0x170ffd */
  display_assert((char *)0x002a42fc, (char *)0x002a3e80, 351, 0);
  system_exit(0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: cmp word ptr [esi + 2], 0 -> jne 0x171133 */
  /* relift: cmp word ptr [ebp - 0xc], 1 -> jne 0x1710c6 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1710aa */
  display_assert((char *)0x002a4338, (char *)0x002a3e80, 371, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x1711d4 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)ecx);
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1710de */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x1711d4 */
  /* cmp (int16_t)ecx, 1 -> jne 0x171111 */
  /* test eax, eax -> je 0x1710cb */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x171100 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  /* cmp (int16_t)edi, 1 -> jne 0x1711d4 */
  display_assert((char *)0x002a42b8, (char *)0x002a3e80, 398, 0);
  system_exit(0);
  /* test eax, eax -> je 0x17114c */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x171158 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x171158 */
  /* cmp (int16_t)edi, 1 -> jne 0x171165 */
  /* cmp (int16_t)edi, 2 -> jne 0x171172 */
  /* cmp (int16_t)edi, 3 -> jne 0x1711d4 */
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)edi, 4 -> jl 0x171070 */
  D3DDevice_SetRenderState_CullMode(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_00170440((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)edi, -1 -> je 0x171258 */
  FUN_00158140(0, 0, ebx, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 0);
  /* cmp (int16_t)eax, (int16_t)ebx -> jne 0x1712a9 */
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ae0] = 8 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* cmp (int16_t)eax, 1 -> jne 0x17143f */
  /* mem[0x005a5b98] = 0x421 */
  /* mem[0x005a5b94] = 4 */
  /* test (char)eax, 0x41 -> jne 0x17130a */
  FUN_00159070(0.0f);
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5ac0] = 0x3120111a */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x3120110a */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0xc091c19 */
  /* mem[0x005a5b78] = 0xc4 */
  /* mem[0x005a5b50] = 0x8080000 */
  /* mem[0x005a5b7c] = 0xd0 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jl 0x17137b */
  /* cmp (int16_t)eax, 3 -> jl 0x17139b */
  display_assert((char *)0x002a4230, (char *)0x002a3e80, 497, 0);
  system_exit(0);
  /* mem[0x005a5b54] = 0xd0d0820 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ae0] = 0x2c0d0800 */
  /* mem[0x005a5ae4] = 0x400 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  display_assert((char *)0x002a41f0, (char *)0x002a3e80, 513, 0);
  system_exit(0);
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  csmemset((void *)0x005a5ac0, 0, 0);
  /* relift: cmp word ptr [esi + 2], (int16_t)ebx -> jne 0x171592 */
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)ecx -> jne 0x1714ed */
  /* relift: cmp word ptr [ebp - 8], (int16_t)ebx -> je 0x1714c2 */
  display_assert((char *)0x002a4338, (char *)0x002a3e80, 529, ecx);
  system_exit(0);
  /* mem[0x005a5b98] = ecx */
  /* mem[0x005a5b48] = 0x8200000 */
  /* mem[0x005a5b74] = 0xc0 */
  /* mem[0x005a5ae4] = 0x800 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jne 0x171516 */
  /* mem[0x005a5b98] = ecx */
  /* mem[0x005a5b48] = 0x8200000 */
  /* mem[0x005a5b74] = 0xc0 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jne 0x17156e */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5b74] = 0xc0 */
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b48] = 0x9200000 */
  /* mem[0x005a5ae4] = 0x800 */
  /* mem[0x005a5b48] = 0x8200000 */
  /* mem[0x005a5ae4] = ebx */
  display_assert((char *)0x002a42b8, (char *)0x002a3e80, 584, ecx);
  system_exit(0);
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b48] = 0x89208a20 */
  /* mem[0x005a5b74] = esi */
  FUN_00159070(0.0f);
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5b4c] = 0xcc118b11 */
  /* mem[0x005a5b78] = esi */
  /* mem[0x005a5b50] = 0xcc20a020 */
  /* mem[0x005a5b7c] = esi */
  /* mem[0x005a5b54] = 0x3809180c */
  /* mem[0x005a5b80] = esi */
  /* mem[0x005a5ae4] = 0x800 */
  /* mem[0x005a5b48] = 0x88208920 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0x8a208b20 */
  /* mem[0x005a5b78] = 0x30d00 */
  /* mem[0x005a5b50] = 0xcc20cd20 */
  /* mem[0x005a5b7c] = eax */
  /* mem[0x005a5b54] = 0xcc20a020 */
  /* mem[0x005a5b80] = 0xc00 */
  /* mem[0x005a5ae4] = ebx */
  /* mem[0x005a5ae0] = 0xc */
  FUN_00159070(0.0f);
  FUN_00159070(0.0f);
  /* test (char)eax, 0x41 -> jne 0x171746 */
  /* mem[0x005a5ae0] = 0x3c0c2d00 */
  /* mem[0x005a5ae4] = eax */
  /* cmp edx, ecx -> jne 0x171853 */
  /* test (char)eax, 0x41 -> jne 0x171853 */
  /* test (char)eax, 0x41 -> jne 0x1717b7 */
  FUN_00159070(0.0f);
  FUN_000d1dd0((float *)0);
  /* test (char)eax, (char)eax -> je 0x171821 */
  FUN_000d1dd0((float *)(uintptr_t)eax);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0x1d0f000c */
  /* mem[0x005a5ae4] = ecx */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0x1d0f0c00 */
  /* mem[0x005a5ae4] = eax */
  /* cmp (int16_t)edi, 8 -> jle 0x171879 */
  display_assert((char *)0x002a41bc, (char *)0x002a3e80, 705, 0);
  system_exit(0);
  /* mem[0x005a5b94] = ecx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)esi -> jne 0x1718e5 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0 */
  SetRenderStateSmart(63, 771);
  SetRenderStateSmart(74, 32774);
  /* relift: cmp eax, dword ptr [ebp - 0x10] -> jne 0x17191a */
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 771);
  SetRenderStateSmart(63, 0);
  SetRenderStateSmart(74, 32774);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x1719dd */
  /* relift: cmp word ptr [ebp - 0xc], 1 -> je 0x1719dd */
  D3DDevice_Begin(0);
  /* test (char)eax, (char)eax -> je 0x171a0b */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171a2e */
  FUN_00167ff0(0, (char *)0x002a4168);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171a56 */
  FUN_00167ff0(0, (char *)0x002a4100);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171a7b */
  FUN_00167ff0(0, (char *)0x002a40a8);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171aa0 */
  FUN_00167ff0(0, (char *)0x002a4040);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171ac6 */
  FUN_00167ff0(0, (char *)0x002a3ff0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171aeb */
  FUN_00167ff0(0, (char *)0x002a3f88);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171b0f */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171b34 */
  FUN_00167ff0(0, (char *)0x002a3f20);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x171b54 */
  FUN_00167ff0(0, (char *)0x0029f728);
  FUN_00158140(0, 0, 0, 0, 0);
  FUN_0016fa40(26);
  error(0, (char *)0x002a3ef4);
  /* test eax, eax -> jne 0x171bef */
  display_assert((char *)0x0029dc40, (char *)0x002a3e80, 786, 0);
  system_exit(0);
  FUN_0016f910(28);
  /* test (char)eax, (char)eax -> je 0x1720d3 */
  /* relift: cmp word ptr [0x5a5df8], 0 -> je 0x1720d3 */
  FUN_000d1c90((float *)0);
  FUN_000d1c90((float *)(uintptr_t)ecx);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x800b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x307 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x8002 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8008 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x307 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x8002 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8007 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x307 */
  SetRenderStateSmart(63, 32770);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(75, 0);
  SetRenderStateSmart(62, 0);
  SetRenderStateSmart(63, 32770);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(75, 0);
  display_assert((char *)0x002a4488, (char *)0x002a3e80, 875, edx);
  system_exit(0);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae8] = esi */
  /* mem[0x005a5ac0] = ebx */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = edi */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_End();
  FUN_0016fa40(28);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x196c90 */
short FUN_00196c90(int out_handles, short max_count, void *iter_first, void *iter_next, void *get_bounds, void *needs_update, void *mark)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  scenario_get();
  rendered_cluster_get(0);
  /* cmp esi, -1 -> je 0x196d36 */
  /* test (char)eax, (char)eax -> je 0x196d25 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x196d25 */
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x196d14 */
  render_frustum_sphere_visible((void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  /* test (int16_t)eax, (int16_t)eax -> je 0x196d25 */
  /* cmp esi, -1 -> jne 0x196cd2 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x196d60 */
void FUN_00196d60(float *rect, int16_t *hull)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x196d84 */
  display_assert((char *)0x002b3714, (char *)0x002b36c8, 1231, 0);
  system_exit(0);
  /* test edi, edi -> je 0x196d96 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x196d96 */
  /* cmp (int16_t)eax, 0x100 -> jle 0x196db6 */
  display_assert((char *)0x002b36fc, (char *)0x002b36c8, 1232, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x196dcf */
  /* test (char)eax, 0x41 -> jne 0x196df3 */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jl 0x196dc0 */

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x196e10 */
void FUN_00196e10(uint16_t *sound_list, void *env, float distance)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> je 0x196e4c */
  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* relift: cmp word ptr [edi], (int16_t)esi -> jle 0x196eab */
  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ebx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x196eb0 */
float *FUN_00196eb0(float *parent_bounds, unsigned char *fractions, float *out_bounds)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  scenario_get();
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x19711a */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x197109 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 36);
  FUN_00196a60((float *)0, (float *)0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1970f5 */
  FUN_00196b10((float *)(uintptr_t)eax, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1970f5 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* relift: test dword ptr [edx + 0x5137d0], esi -> je 0x1970e1 */
  /* test esi, ecx -> jne 0x1970e1 */
  /* relift: cmp edx, dword ptr [ebx] -> jl 0x197097 */
  /* cmp eax, ecx -> jl 0x197034 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x002b3798, (char *)0x002b36c8, 752, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1971b5 */
  display_assert((char *)0x002b3788, (char *)0x002b36c8, 753, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1971dc */
  display_assert((char *)0x002b3774, (char *)0x002b36c8, 754, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x197203 */
  display_assert((char *)0x002b3768, (char *)0x002b36c8, 755, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197217 */
  /* relift: cmp ecx, dword ptr [edi + 0x134] -> jl 0x197237 */
  display_assert((char *)0x002b3720, (char *)0x002b36c8, 756, 0);
  system_exit(0);
  /* relift: tail-call FUN_00196eb0(); */
  /* cmp (int16_t)ebx, 2 -> je 0x197275 */
  FUN_00196a60((float *)0, (float *)0);
  FUN_00196b10((float *)(uintptr_t)edx, 0, 0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jle 0x197275 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x197300 */
  /* cmp ebx, eax -> jge 0x197300 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test edx, ecx -> je 0x1972ef */
  /* test edx, ecx -> jne 0x1972ef */
  /* relift: cmp word ptr [ebp + 0x2c], (int16_t)edi -> jge 0x197300 */
  /* cmp ebx, ecx -> jl 0x197294 */
  scenario_get();
  /* test (char)eax, 0x41 -> jne 0x1974d8 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1973ca */
  matrix_transform_point((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  convex_polygon3d_clip_to_plane(eax, (float *)(uintptr_t)ecx, (void *)0x002b35c4, 256, (float *)(uintptr_t)edx, (void *)0, 0.0f, (void *)0);
  display_assert((char *)0x002b37b0, (char *)0x002b36c8, 1157, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], 1 -> jne 0x197432 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 4] -> je 0x1974c5 */
  /* test (char)eax, 0x41 -> je 0x197496 */
  display_assert((char *)0x002b37a8, (char *)0x002b36c8, 1175, 0);
  system_exit(0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 96);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00197310((void *)0x005065a4, (void *)0, (void *)0, (void *)0, 0, 0, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1975d5 */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x197580 */
  FUN_001d90e0();
  scenario_get();
  render_frustum_get_projection_bounds((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)esi, ecx);
  /* relift: cmp dword ptr [eax], 0 -> je 0x19786e */
  /* cmp eax, ebx -> jge 0x197874 */
  /* relift: test dword ptr [ecx], edx -> je 0x197854 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 104);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  FUN_00197310((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)0, (void *)(uintptr_t)edx, 0, 0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x19776b */
  FUN_00108060(eax, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)eax, 256, (void *)(uintptr_t)edx, 0x38d1b717);
  /* cmp (int16_t)eax, 2 -> jne 0x19783d */
  tag_get('rdhs', 0);
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x1977a9 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x197819 */
  error(0, (char *)0x002b37cc);
  /* cmp eax, ecx -> jl 0x1976f1 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  /* test eax, eax -> jne 0x1978ee */
  display_assert((char *)0x002b3788, (char *)0x002b36c8, 683, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x197915 */
  display_assert((char *)0x002b3774, (char *)0x002b36c8, 684, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x19793c */
  display_assert((char *)0x002b3768, (char *)0x002b36c8, 685, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x197964 */
  display_assert((char *)0x002b3798, (char *)0x002b36c8, 686, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* relift: tail-call FUN_00196eb0(); */
  /* cmp (int16_t)edi, 2 -> je 0x1979cd */
  FUN_00196a60((float *)0, (float *)0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x197af1 */
  FUN_00196b10((float *)(uintptr_t)edx, 0, 0);
  /* cmp (int16_t)eax, 2 -> jne 0x1979c6 */
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x1979cd */
  /* test (int16_t)edi, (int16_t)edi -> je 0x197af1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> je 0x197a3f */
  /* relift: cmp byte ptr [edx], 0 -> je 0x197ad4 */
  FUN_001978a0(0, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  /* cmp eax, -1 -> je 0x197ad4 */
  FUN_00197130((float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0, 0);
  FUN_001d90e0();
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 104);
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)ebx, eax);
  /* test eax, eax -> je 0x197b5d */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197b5d */
  /* cmp (int16_t)eax, 0x100 -> jle 0x197b7d */
  display_assert((char *)0x002b3864, (char *)0x002b36c8, 1006, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5137cc], 0x80 -> jl 0x197bd6 */
  display_assert((char *)0x002b3844, (char *)0x002b36c8, 1013, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197be4 */
  /* cmp (int16_t)eax, 0x200 -> jl 0x197c04 */
  display_assert((char *)0x00269e58, (char *)0x002b36c8, 1016, 0);
  system_exit(0);
  rendered_cluster_get(0);
  rendered_cluster_get(0);
  /* relift: cmp word ptr [esi], (int16_t)eax -> je 0x197c95 */
  display_assert((char *)0x002b3814, (char *)0x002b36c8, 1027, 0);
  system_exit(0);
  FUN_00196d60((float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x197cbf */
  ai_debug_highlight_cluster(edx, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x197ce9 */
  FUN_00196e10((void *)0x3d4ccccd, (void *)0, 0.0f);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x197e53 */
  /* cmp eax, edx -> jge 0x197e53 */
  /* relift: test dword ptr [eax + ecx], edx -> jne 0x197e53 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x197e53 */
  FUN_001974f0(ebx, eax, (void *)(uintptr_t)edx);
  /* cmp (int16_t)eax, 2 -> jne 0x197db9 */
  FUN_00197b00(edi, (void *)(uintptr_t)ecx);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x197e53 */
  /* test (char)eax, (char)eax -> jne 0x197de5 */
  FUN_00197570((float *)(uintptr_t)edx, 0, 0.0f);
  /* test (char)eax, (char)eax -> je 0x197e53 */
  FUN_00108060(ecx, (void *)(uintptr_t)eax, 0, (void *)(uintptr_t)ecx, 256, (void *)(uintptr_t)eax, 0x38d1b717);
  FUN_00197b00(edi, (void *)(uintptr_t)edx);
  /* cmp (int16_t)eax, 0xffff -> jne 0x197e53 */
  error(0, (char *)0x002b37f8);
  FUN_00197b00(edi, (void *)(uintptr_t)esi);
  /* cmp eax, edx -> jl 0x197d10 */
  FUN_001d90e0();
  scenario_get();
  display_assert((char *)0x002b38b8, (char *)0x002b36c8, 613, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x197f00 */
  /* test eax, eax -> jne 0x197f00 */
  display_assert((char *)0x002b3888, (char *)0x002b36c8, 614, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, eax);
  /* test edi, edi -> jne 0x197f5f */
  FUN_001978a0(0, (float *)(uintptr_t)ecx, (void *)0, (void *)0, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  /* test eax, eax -> je 0x197fdb */
  FUN_00196fd0((void *)(uintptr_t)ecx, eax, 0, 0, (float *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax, 0, (void *)0);
  scenario_location_from_point((void *)(uintptr_t)edx, (void *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0x198039 */
  structure_find_in_cluster(eax, (float *)(uintptr_t)esi, 0.0f, 512, (void *)(uintptr_t)ecx);
  FUN_00196fd0((void *)(uintptr_t)eax, edx, 0, 0, (float *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)edx, 0, (void *)0);
  FUN_001978a0(0, (float *)(uintptr_t)eax, (void *)0, (void *)0, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  scenario_get();
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x198179 */
  render_frustum_get_projection_bounds((void *)0x005065a4, (void *)(uintptr_t)eax);
  /* mem[0x004d8ed8] = eax */
  csmemset((void *)(uintptr_t)ecx, 0, 64);
  FUN_00197b00(eax, (void *)(uintptr_t)edx);
  /* relift: cmp word ptr [0x5137cc], (int16_t)edi -> jle 0x198178 */
  rendered_cluster_get(0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 104);
  render_camera_build_clipped_frustum_bounds((void *)0x00506550, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  render_camera_build_frustum((void *)0x00506550, (float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, 0);
  /* relift: cmp (int16_t)edi, word ptr [0x5137cc] -> jl 0x198130 */
  scenario_get();
  /* test (char)eax, (char)eax -> je 0x1981ae */
  profile_enter_private((void *)0x0032bd68);
  csmemset((void *)0x0050678c, 0, ecx);
  csmemset((void *)0x005137d0, 0, edx);
  FUN_00198070();
  /* test (char)eax, (char)eax -> je 0x19833c */
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)esi, ecx);
  csmemcpy((void *)0x0050678c, (void *)(uintptr_t)eax, 0);
  /* cmp eax, ebx -> jle 0x19833c */
  /* relift: test dword ptr [eax*4 + 0x50678c], edx -> je 0x19832b */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 104);
  /* relift: cmp word ptr [0x5137cc], 0x80 -> jl 0x1982c5 */
  display_assert((char *)0x002b3844, (char *)0x002b36c8, 280, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1982d1 */
  /* cmp (int16_t)ebx, 0x200 -> jl 0x1982f1 */
  display_assert((char *)0x00269e58, (char *)0x002b36c8, 283, 0);
  system_exit(0);
  rendered_cluster_get(0);
  render_frustum_get_projection_bounds((void *)0x005065a4, (void *)(uintptr_t)eax);
  /* cmp esi, eax -> jl 0x198270 */
  /* test (char)eax, (char)eax -> je 0x19835c */
  profile_exit_private((void *)0x0032bd68);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 104);
  FUN_001966b0(0);
  /* test (char)eax, (char)eax -> jne 0x1983a8 */
  /* test eax, eax -> jle 0x1983a1 */
  error(0, (char *)0x002b38d0);
  FUN_00196850(0);
  structure_detail_objects_initialize();
  structure_detail_objects_initialize_for_new_map();
  structure_runtime_decals_dispose_from_old_map();
  structure_runtime_decals_dispose();
  /* test (char)eax, (char)eax -> je 0x198429 */
  display_assert((char *)0x002b3924, (char *)0x002b3954, 259, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x19846c */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 270, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x19847d */
  /* cmp (int16_t)esi, 0x200 -> jl 0x19849d */
  display_assert((char *)0x00269e58, (char *)0x002b3954, 271, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1984ec */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 286, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1984fd */
  /* cmp (int16_t)esi, 0x200 -> jl 0x19851d */
  display_assert((char *)0x00269e58, (char *)0x002b3954, 287, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x198569 */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 304, 0);
  system_exit(0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp eax, -1 -> je 0x1986ec */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp edx, ecx -> jne 0x1986ec */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  structure_bsp_find_material_for_surface((void *)(uintptr_t)edi, 0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)esi);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x198672 */
  /* cmp (int16_t)eax, 1 -> jne 0x1986e9 */
  FUN_00180500((float *)(uintptr_t)ecx, (float *)0);
  FUN_00180500((float *)(uintptr_t)ecx, (float *)0);
  FUN_00180500((float *)(uintptr_t)ecx, (float *)0);
  FUN_0010d830((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x19870d */
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f4 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 104);
  /* test (char)ecx, (char)ecx -> je 0x198781 */
  FUN_0018e7d0(0);
  /* test eax, eax -> je 0x1987f9 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f9 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f9 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 40);
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f9 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x198999 */
  FUN_0018e420();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00099220((float *)(uintptr_t)esi);
  FUN_00099270((float *)(uintptr_t)esi, eax);
  FUN_00061df0((void *)0, 0, 0, (void *)0);
  /* test eax, eax -> jle 0x19895f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 12);
  FUN_00061df0((void *)(uintptr_t)eax, 0, 0, (void *)0);
  /* cmp eax, ecx -> jl 0x198930 */
  FUN_00106130(ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0.0f);
  /* test (char)eax, (char)eax -> je 0x198999 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  structure_cluster_mark(edi);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)ecx, (int16_t)edi -> jne 0x198a56 */
  structure_cluster_unmarked(edi);
  /* test (char)eax, (char)eax -> je 0x198aa7 */
  structure_get_planar_fog((void *)(uintptr_t)eax, esi, (float *)(uintptr_t)edx, 0.0f);
  /* test (char)eax, (char)eax -> je 0x198aa7 */
  FUN_001989b0(edi, (float *)(uintptr_t)edx, 0.0f, 0, (void *)(uintptr_t)ebx);
  /* cmp eax, edx -> jl 0x198a1f */
  /* test (char)eax, (char)eax -> je 0x198b05 */
  display_assert((char *)0x002b3924, (char *)0x002b3954, 259, 0);
  system_exit(0);
  /* mem[0x004d92e4] = edx */
  scenario_get();
  structure_cluster_mark(esi);
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 0x20] -> jge 0x198c72 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)eax, (int16_t)edi -> jne 0x198bcb */
  structure_cluster_unmarked(edx);
  /* test (char)eax, (char)eax -> je 0x198c4f */
  FUN_00110210((float *)(uintptr_t)esi, 0.0f, (float *)0, (float *)0, 0.0f, 0.0f, 0.0f);
  /* test (char)eax, (char)eax -> je 0x198c4f */
  structure_cluster_mark(eax);
  /* cmp (int16_t)esi, 0x200 -> jl 0x198c3c */
  display_assert((char *)0x002b39ac, (char *)0x002b3954, 245, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x198b94 */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 304, 0);
  system_exit(0);
  display_assert((char *)0x0026856c, (char *)0x002b3954, 392, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d0b */
  display_assert((char *)0x002a3e7c, (char *)0x002b3954, 393, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d32 */
  display_assert((char *)0x002b39ec, (char *)0x002b3954, 394, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d59 */
  display_assert((char *)0x002b39dc, (char *)0x002b3954, 395, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d80 */
  display_assert((char *)0x002b39d8, (char *)0x002b3954, 396, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198da7 */
  display_assert((char *)0x00269cdc, (char *)0x002b3954, 397, 0);
  system_exit(0);
  display_assert((char *)0x00253440, (char *)0x002b3954, 406, 0);
  system_exit(0);
  FUN_0014df70(33, (float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x198ec4 */
  scenario_get();
  structure_render_surface_from_point_and_leaf((void *)(uintptr_t)esi, eax, 0, (void *)0, (void *)0, (void *)0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x198e8d */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  /* relift: cmp word ptr [eax], -1 -> je 0x198e8d */
  /* relift: test byte ptr [ebp - 8], 1 -> je 0x198ec4 */
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x198eee */
  display_assert((char *)0x00253418, (char *)0x002b3954, 426, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x198dc0 */
  scenario_get();
  display_assert((char *)0x0029dc54, (char *)0x002b3954, 497, 0);
  system_exit(0);
  structure_get_planar_fog_definition_index((void *)(uintptr_t)ebx, eax, edi);
  /* cmp edi, -1 -> jne 0x198faa */
  /* cmp (int16_t)eax, 0xffff -> je 0x198f9d */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_0018e7d0(0);
  /* test eax, eax -> je 0x198f9d */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 104);
  tag_get(' gof', 0);
  /* test (char)eax, (char)eax -> je 0x198fe7 */
  /* relift: test byte ptr [eax + 3], 0x80 -> je 0x199032 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_001954e0((void *)0);
  /* test (char)eax, (char)eax -> je 0x19922a */
  /* relift: cmp word ptr [0x50674c], 1 -> jne 0x19922a */
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x19922a */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 104);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 12);
  FUN_0017eb10((float *)0, (float *)0, 0);
  FUN_0017eb10((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0);
  FUN_0017e5b0((float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0, 0);
  FUN_0017e5b0((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0, 0);
  /* test eax, eax -> jne 0x19925a */
  display_assert((char *)0x00267114, (char *)0x002b3954, 134, 0);
  system_exit(0);
  /* test (char)eax, 1 -> je 0x19928a */
  display_assert((char *)0x0029d9b0, (char *)0x002b3954, 135, 0);
  system_exit(0);
  display_assert((char *)0x0028ede8, (char *)0x002b3954, 136, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1992dc */
  display_assert((char *)0x002b39fc, (char *)0x002b3954, 137, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0x199359 */
  /* test (char)eax, 0x41 -> jne 0x199347 */
  structures_cluster_marker_begin();
  FUN_001989b0(esi, (float *)(uintptr_t)ecx, 0.0f, 0, (void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x199338 */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 304, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x199359 */
  /* cmp (int16_t)esi, 2 -> jl 0x199392 */
  display_assert((char *)0x002b3a70, (char *)0x002b3aac, 75, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1993c8 */
  display_assert((char *)0x002b3a40, (char *)0x002b3aac, 76, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0xff -> jbe 0x1993f8 */
  display_assert((char *)0x002b3a10, (char *)0x002b3aac, 77, 0);
  system_exit(0);
  csstrncpy((char *)(uintptr_t)edi, (char *)(uintptr_t)ebx, 255);
  display_assert((char *)0x002b3b10, (char *)0x002b3aac, 91, 0);
  system_exit(0);
  /* cmp (int16_t)edi, -1 -> jl 0x199459 */
  /* cmp (int16_t)edi, 2 -> jl 0x199476 */
  display_assert((char *)0x002b3ad0, (char *)0x002b3aac, 92, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 268);
  display_assert((char *)0x0028ede8, (char *)0x002b3aac, 257, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1994f6 */
  display_assert((char *)0x002b3b18, (char *)0x002b3aac, 258, 0);
  system_exit(0);
  find_files_begin(0, (void *)(uintptr_t)eax);
  /* test ebx, ebx -> jle 0x19952a */
  find_files_next((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x19952a */
  /* cmp esi, ebx -> jl 0x199510 */
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1995af */
  file_get_eof((void *)(uintptr_t)edi);
  debug_malloc(eax, esi, (char *)0x002b3aac, 280);
  /* test esi, esi -> je 0x1995a5 */
  file_read((void *)(uintptr_t)edi, 0, (void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x1995a5 */
  debug_free((void *)(uintptr_t)esi, (char *)0x002b3aac, 286);
  file_close((void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x199616 */
  vsprintf((char *)(uintptr_t)edx, (char *)(uintptr_t)eax, (char *)(uintptr_t)ecx);
  csstrlen((char *)(uintptr_t)ecx);
  file_write();
  file_get_position((void *)(uintptr_t)esi);
  file_set_eof();
  /* test esi, esi -> jne 0x19964b */
  display_assert((char *)0x002b3b10, (char *)0x002b3aac, 508, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x66696c6f -> je 0x199673 */
  display_assert((char *)0x002b3bb0, (char *)0x002b3aac, 509, 0);
  system_exit(0);
  /* relift: test word ptr [esi + 4], 0xfffe -> je 0x19969b */
  display_assert((char *)0x002b3b74, (char *)0x002b3aac, 510, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> jl 0x1996ab */
  /* cmp (int16_t)eax, 2 -> jl 0x1996cb */
  display_assert((char *)0x002b3b28, (char *)0x002b3aac, 511, 0);
  system_exit(0);
  file_reference_verify((void *)(uintptr_t)esi);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)esi, 264);
  file_reference_verify((void *)(uintptr_t)edi);
  display_assert((char *)0x002b3c08, (char *)0x002b3aac, 137, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> je 0x199761 */
  display_assert((char *)0x002b3bdc, (char *)0x002b3aac, 138, 0);
  system_exit(0);
  path_add_directory((char *)(uintptr_t)esi, (char *)0);
  file_reference_verify((void *)(uintptr_t)edi);
  display_assert((char *)0x0028ede0, (char *)0x002b3aac, 151, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1997cd */
  path_remove_filename((char *)(uintptr_t)eax);
  path_add_directory((char *)(uintptr_t)ecx, (char *)(uintptr_t)ebx);
  file_reference_verify((void *)(uintptr_t)eax);
  file_reference_verify((void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x199869 */
  display_assert((char *)0x0028ede0, (char *)0x002b3aac, 185, 0);
  system_exit(0);
  /* relift: test word ptr [ebx + 4], 0xfff0 -> je 0x199891 */
  display_assert((char *)0x002b3cb0, (char *)0x002b3aac, 186, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1998ab */
  /* cmp eax, 9 -> jne 0x1998d3 */
  display_assert((char *)0x002b3c70, (char *)0x002b3aac, 188, 0);
  system_exit(0);
  /* test (char)eax, 2 -> je 0x1998ff */
  display_assert((char *)0x002b3c18, (char *)0x002b3aac, 189, 0);
  system_exit(0);
  path_from_file_reference(eax, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  path_split((char *)(uintptr_t)eax, (char **)(uintptr_t)edx, (char **)(uintptr_t)ecx, (char **)(uintptr_t)eax, (char **)(uintptr_t)edx, 0);
  path_add_directory((char *)(uintptr_t)edi, (char *)(uintptr_t)ecx);
  /* test (char)ebx, 2 -> je 0x19996b */
  path_add_directory((char *)(uintptr_t)edi, (char *)(uintptr_t)edx);
  /* test (char)ebx, 4 -> je 0x19997d */
  path_add_directory((char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  /* test (char)ebx, 8 -> je 0x19998f */
  path_add_extension((char *)(uintptr_t)edi, (char *)(uintptr_t)ecx);
  file_reference_verify((void *)(uintptr_t)eax);
  file_reference_verify((void *)(uintptr_t)ecx);
  /* relift: cmp (int16_t)edx, word ptr [eax + 6] -> jne 0x1999de */
  csstrcmp((char *)(uintptr_t)esi, (char *)0);
  /* test esi, esi -> jne 0x199a18 */
  display_assert((char *)0x002b3b10, (char *)0x002b3aac, 91, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 268);
  file_reference_add_directory((void *)(uintptr_t)esi, (char *)(uintptr_t)eax);
  file_reference_set_name((void *)(uintptr_t)esi, (char *)(uintptr_t)ecx);
  csmemset((void *)(uintptr_t)eax, 0, 268);
  file_reference_add_directory((void *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  file_exists((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x199b05 */
  find_files_begin(0, (void *)(uintptr_t)ecx);
  find_files_next((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x199b14 */
  file_delete((void *)(uintptr_t)eax);
  find_files_next((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> jne 0x199ae0 */
  FUN_0019a490((void *)(uintptr_t)edx);
  display_assert((char *)0x002b3d7c, (char *)0x002b3aac, 369, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x199b81 */
  display_assert((char *)0x002b3d68, (char *)0x002b3aac, 370, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edi], 0 -> jne 0x199ba6 */
  display_assert((char *)0x002b3d50, (char *)0x002b3aac, 371, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x199bcb */
  display_assert((char *)0x002b3d38, (char *)0x002b3aac, 372, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0xff -> jl 0x199bf4 */
  display_assert((char *)0x002b3d14, (char *)0x002b3aac, 373, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)esi);
  /* cmp eax, 0xff -> jb 0x199c24 */
  display_assert((char *)0x002b3ce0, (char *)0x002b3aac, 374, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 268);
  file_reference_set_name((void *)(uintptr_t)ecx, (char *)(uintptr_t)edi);
  file_exists((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x199d2c */
  file_read_into_buffer((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test ebx, ebx -> jne 0x199c96 */
  file_delete((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp - 4], 0x18e70 -> je 0x199cc8 */
  debug_free((void *)(uintptr_t)ebx, (char *)0x002b3aac, 389);
  file_delete((void *)(uintptr_t)eax);
  /* test ebx, ebx -> je 0x199d2c */
  csstrcmp((char *)(uintptr_t)edi, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x199cf7 */
  /* relift: cmp byte ptr [edi], 0 -> je 0x199d19 */
  /* cmp esi, 0xc8 -> jl 0x199cd0 */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, edx);
  debug_free((void *)(uintptr_t)ebx, (char *)0x002b3aac, 416);
  display_assert((char *)0x002b3d7c, (char *)0x002b3aac, 430, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x199da4 */
  display_assert((char *)0x002b3d68, (char *)0x002b3aac, 431, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x199dc9 */
  display_assert((char *)0x002b3d50, (char *)0x002b3aac, 432, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edi], 0 -> jne 0x199dee */
  display_assert((char *)0x002b3d38, (char *)0x002b3aac, 433, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0xff -> jl 0x199e17 */
  display_assert((char *)0x002b3d14, (char *)0x002b3aac, 434, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* cmp eax, 0xff -> jb 0x199e47 */
  display_assert((char *)0x002b3ce0, (char *)0x002b3aac, 435, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 268);
  file_reference_set_name((void *)(uintptr_t)ecx, (char *)(uintptr_t)esi);
  file_exists((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x199ee3 */
  file_read_into_buffer((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x199eb5 */
  file_delete((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp - 8], 0x18e70 -> je 0x199edf */
  debug_free((void *)(uintptr_t)edi, (char *)0x002b3aac, 450);
  file_delete((void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x199f16 */
  debug_malloc(0x00018e70, 0, (char *)0x002b3aac, 461);
  /* test edi, edi -> je 0x199fe7 */
  csmemset((void *)(uintptr_t)edi, 0, 0x00018e70);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x199f47 */
  csstrcmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x199f47 */
  /* cmp esi, 0xc8 -> jl 0x199f20 */
  csstrcpy((char *)(uintptr_t)esi, (char *)0);
  csmemcpy((void *)(uintptr_t)esi, (void *)0, 0);
  file_exists((void *)(uintptr_t)edx);
  FUN_0019a490((void *)(uintptr_t)eax);
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x199fcd */
  file_write();
  file_close((void *)(uintptr_t)eax);
  debug_free((void *)(uintptr_t)edi, (char *)0x002b3aac, 492);
  /* test (char)eax, (char)eax -> jne 0x19a007 */
  display_assert((char *)0x00254818, (char *)0x002b3aac, 495, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  file_reference_verify((void *)(uintptr_t)eax);
  /* test eax, 0xfffffffc -> je 0x19a083 */
  display_assert((char *)0x002b3dbc, (char *)0x002b3dec, 548, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 4], 1 -> je 0x19a0a9 */
  display_assert((char *)0x002b3d90, (char *)0x002b3dec, 549, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x19a0da */
  /* cmp eax, -1 -> je 0x19a0d3 */
  CloseHandle(0);
  /* mem[0x0032cf60] = ecx */
  csstrcpy((char *)0x0032cf68, (char *)(uintptr_t)ebx);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x19a196 */
  csstrlen((char *)(uintptr_t)edi);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0xff -> jbe 0x19a15d */
  display_assert((char *)0x002b3e18, (char *)0x002b3dec, 672, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* cmp esi, edi -> je 0x19a175 */
  csstrlen((char *)(uintptr_t)edi);
  csstrncpy((char *)(uintptr_t)esi, (char *)(uintptr_t)ebx, ecx);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x19a226 */
  csstrlen((char *)(uintptr_t)edi);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0xff -> jbe 0x19a1ed */
  display_assert((char *)0x002b3e50, (char *)0x002b3dec, 696, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* cmp esi, edi -> je 0x19a205 */
  csstrlen((char *)(uintptr_t)edi);
  csstrncpy((char *)(uintptr_t)esi, (char *)(uintptr_t)ebx, ecx);
  csstrlen((char *)(uintptr_t)esi);
  /* relift: cmp word ptr [ebp + 8], 0 -> je 0x19a25d */
  unicode_cursor_backward((char *)(uintptr_t)esi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0x5c -> jne 0x19a243 */
  unicode_cursor_forward((char *)(uintptr_t)esi, (void *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 0x5c -> jne 0x19a27e */
  csstrlen((char *)(uintptr_t)esi);
  unicode_cursor_backward((char *)(uintptr_t)esi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0x2e -> jne 0x19a2ff */
  /* test (char)eax, (char)eax -> je 0x19a33b */
  /* relift: cmp byte ptr [ecx], 0 -> jne 0x19a33b */
  /* relift: cmp byte ptr [edx], 0 -> jne 0x19a33b */
  /* cmp (int16_t)eax, 0x5c -> jne 0x19a33b */
  /* test (char)eax, (char)eax -> je 0x19a327 */
  /* relift: cmp byte ptr [eax], 0 -> jne 0x19a327 */
  /* relift: cmp byte ptr [ecx], 0 -> jne 0x19a33b */
  /* relift: cmp word ptr [ebp + 8], 0 -> jne 0x19a2c3 */
  /* test (char)eax, (char)eax -> je 0x19a357 */
  /* relift: cmp byte ptr [edx], 0 -> jne 0x19a357 */
  /* relift: cmp dword ptr [edi], esi -> je 0x19a360 */
  /* test edi, edi -> jne 0x19a3a3 */
  display_assert((char *)0x002b3e90, (char *)0x002b3dec, 788, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x19a3d6 */
  /* test (char)ecx, (char)ecx -> je 0x19a3d6 */
  /* test (char)ecx, (char)ecx -> je 0x19a3d6 */
  _isalpha();
  /* test eax, eax -> je 0x19a3d6 */
  /* relift: cmp byte ptr [esi + 1], 0x3a -> jne 0x19a3d6 */
  /* relift: cmp byte ptr [esi + 2], 0x5c -> je 0x19a3e4 */
  csstrcpy((char *)(uintptr_t)edi, (char *)0x002b3e8c);
  FUN_0008dc30((char *)(uintptr_t)edi, (char *)(uintptr_t)esi);
  file_reference_verify((void *)(uintptr_t)eax);
  path_from_file_reference(eax, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  file_get_full_attributes((char *)(uintptr_t)ecx);
  /* cmp eax, -1 -> je 0x19a444 */
  file_reference_verify((void *)(uintptr_t)eax);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  path_from_file_reference(ecx, (char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  CreateFileA((char *)(uintptr_t)edx, 0x40000000, 0, 0, 0, 128, 0);
  /* cmp eax, -1 -> je 0x19a51d */
  CloseHandle(0);
  CreateDirectoryA((char *)(uintptr_t)edi, 0);
  /* test eax, eax -> jne 0x19a50a */
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* test (char)eax, 1 -> je 0x19a5df */
  FUN_001d0df0((char *)(uintptr_t)eax, 128);
  /* test eax, eax -> je 0x19a5f8 */
  DeleteFileA((char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x19a5f8 */
  FUN_001d347c((char *)(uintptr_t)edx);
  /* test eax, eax -> je 0x19a5f8 */
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  file_get_full_attributes((char *)(uintptr_t)eax);
  /* cmp eax, -1 -> je 0x19a6a3 */
  xapi_GetLastError();
  /* cmp eax, 2 -> je 0x19a6c6 */
  xapi_GetLastError();
  /* cmp eax, 3 -> je 0x19a6c6 */
  file_error((void *)0x002b3ed4, (char *)0);
  file_reference_verify((void *)(uintptr_t)eax);
  path_from_file_reference(edx, (char *)(uintptr_t)esi, (char *)(uintptr_t)ecx);
  csstrcpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  path_remove_filename((char *)(uintptr_t)edx);
  path_add_directory((char *)(uintptr_t)eax, (char *)(uintptr_t)edi);
  MoveFileA();
  /* test eax, eax -> je 0x19a790 */
  path_remove_filename((char *)(uintptr_t)esi);
  path_add_directory((char *)(uintptr_t)esi, (char *)(uintptr_t)edi);
  file_reference_verify((void *)(uintptr_t)eax);
  display_assert((char *)0x002b3f8c, (char *)0x002b3dec, 308, 0);
  system_exit(0);
  /* test (char)ebx, 3 -> jne 0x19a82a */
  display_assert((char *)0x002b3f48, (char *)0x002b3dec, 309, 0);
  system_exit(0);
  /* test (char)ebx, 4 -> je 0x19a856 */
  display_assert((char *)0x002b3ef0, (char *)0x002b3dec, 310, 0);
  system_exit(0);
  path_from_file_reference(eax, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  /* test edi, edi -> je 0x19a886 */
  CreateFileA((char *)(uintptr_t)ecx, eax, 0, 0, 0, 128, 0);
  /* cmp eax, -1 -> je 0x19a8d9 */
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp eax, -1 -> jne 0x19a91e */
  CloseHandle(0);
  file_reference_verify((void *)(uintptr_t)eax);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)edi);
  CloseHandle(0);
  /* test eax, eax -> je 0x19a967 */
  file_reference_verify((void *)(uintptr_t)edi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)edi);
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp esi, -1 -> jne 0x19a9fa */
  file_reference_verify((void *)(uintptr_t)edi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  SetFilePointer(0, 0, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> jne 0x19aa5f */
  file_reference_verify((void *)(uintptr_t)esi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)edi);
  GetFileSize(0, (void *)0);
  /* cmp esi, -1 -> jne 0x19aac6 */
  file_reference_verify((void *)(uintptr_t)edi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  file_set_position((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x19ab07 */
  SetEndOfFile(0);
  /* test eax, eax -> je 0x19ab07 */
  file_reference_verify((void *)(uintptr_t)esi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  display_assert((char *)0x00267900, (char *)0x002b3dec, 423, 0);
  system_exit(0);
  ReadFile(0, (void *)(uintptr_t)edi, ecx, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x19abbf */
  /* relift: cmp dword ptr [ebp - 4], eax -> jne 0x19abb8 */
  SetLastError(38);
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  display_assert((char *)0x00267900, (char *)0x002b3dec, 451, 0);
  system_exit(0);
  WriteFile(0, (void *)(uintptr_t)edi, ecx, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x19ac68 */
  /* relift: cmp dword ptr [ebp - 4], eax -> jne 0x19ac68 */
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_set_position((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x19ace5 */
  file_read((void *)(uintptr_t)esi, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x19ace5 */
  file_set_position((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x19ad25 */
  file_write();
  /* test (char)eax, (char)eax -> je 0x19ad25 */
  file_reference_verify((void *)(uintptr_t)ebx);
  csmemset((void *)(uintptr_t)edi, 0, 0);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_001d0ee1();
  /* test eax, eax -> je 0x19adb5 */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0);
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  /* test edi, edi -> jne 0x19ae4a */
  display_assert((char *)0x00267f68, (char *)0x002b3dec, 524, 0);
  system_exit(0);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_001d0ee1();
  /* test eax, eax -> je 0x19ae88 */
  file_reference_verify((void *)(uintptr_t)esi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1a4440 — refresh biped forward/up from flying, climb, limp, or default. */
void FUN_001a4440(int unit_handle)
{
  char *unit;
  char *biped_tag;
  unsigned int flags;
  float *forward;
  float *up;
  float *global_up;
  float *global_forward;
  float *global_left;
  float axis[3];
  float temp[3];
  float rotated[3];
  float angle;
  float s;
  float c;
  float dot;

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */
  flags = *(unsigned int *)(biped_tag + 0x2f4);
  forward = (float *)(unit + 0x24);
  up = (float *)(unit + 0x30);

  if ((flags & 4) != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    if (!valid_real_normal3d(forward)) {
      csprintf((char *)0x5ab100, (char *)0x254a24, (char *)0x2b5148,
               (double)forward[0], (double)forward[1], (double)*(float *)(unit + 0x2c));
      display_assert((char *)0x5ab100, (char *)0x2b4d5c, 0xfa5, 1);
      system_exit(-1);
    }

    global_up = *(float **)0x31fc44;
    cross_product3d(global_up, forward, temp);
    cross_product3d(temp, forward, axis);
    if (normalize3d(axis) == 0.0f) {
      global_forward = *(float **)0x31fc3c;
      global_left = *(float **)0x31fc40;
      axis[0] = global_forward[0];
      axis[1] = global_forward[1];
      axis[2] = global_forward[2];
      temp[0] = global_left[0];
      temp[1] = global_left[1];
      temp[2] = global_left[2];
    }

    angle = *(float *)(unit + 0x468);
    c = cosf(angle);
    s = sinf(angle);
    rotated[0] = axis[0] * c;
    rotated[1] = axis[1] * c;
    rotated[2] = axis[2] * c;
    normalize3d(temp);
    up[0] = temp[0] * s + rotated[0];
    up[1] = temp[1] * s + rotated[1];
    up[2] = temp[2] * s + rotated[2];
    FUN_001a2800(unit_handle, (const char *)0x2b5130);
    return;
  }

  if ((flags & 0x40) != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    float desired[3];

    if (*(int *)(unit + 0x430) == -1) {
      desired[0] = up[0];
      desired[1] = up[1];
      desired[2] = up[2];
    } else {
      float *climb = (float *)(unit + 0x46c);
      desired[0] = climb[0];
      desired[1] = climb[1];
      desired[2] = climb[2];
      cross_product3d(up, desired, temp);
      if (normalize3d(temp) == 0.0f) {
        dot = desired[0] * up[0] + desired[1] * up[1] + desired[2] * up[2];
        if (!(dot > 0.0f)) {
          desired[0] = forward[0];
          desired[1] = forward[1];
          desired[2] = forward[2];
        }
      } else {
        double bank = *(double *)0x281138;
        c = (float)cos(bank);
        s = (float)sin(bank);
        rotated[0] = up[0];
        rotated[1] = up[1];
        rotated[2] = up[2];
        rotate_vector3d_by_sincos(rotated, temp, s, c);
        cross_product3d(desired, rotated, axis);
        if (!(axis[0] * temp[0] + axis[1] * temp[1] + axis[2] * temp[2] > 0.0f)) {
          desired[0] = rotated[0];
          desired[1] = rotated[1];
          desired[2] = rotated[2];
        }
      }
    }

    cross_product3d(desired, forward, temp);
    cross_product3d(temp, desired, axis);
    if (normalize3d(axis) == 0.0f) {
      cross_product3d(desired, up, temp);
      cross_product3d(temp, desired, axis);
      if (normalize3d(axis) == 0.0f) {
        global_up = *(float **)0x31fc44;
        global_forward = *(float **)0x31fc3c;
        desired[0] = global_up[0];
        desired[1] = global_up[1];
        desired[2] = global_up[2];
        axis[0] = global_forward[0];
        axis[1] = global_forward[1];
        axis[2] = global_forward[2];
      }
    }
    forward[0] = axis[0];
    forward[1] = axis[1];
    forward[2] = axis[2];
    up[0] = desired[0];
    up[1] = desired[1];
    up[2] = desired[2];
    FUN_001a2800(unit_handle, (const char *)0x2b5118);
    return;
  }

  if ((*(unsigned char *)(unit + 0xb6) & 4) != 0 &&
      (*(unsigned char *)(unit + 0x424) & 1) == 0) {
    float *look = (float *)(unit + 0x46c);

    FUN_001a2800(unit_handle, (const char *)0x2b50fc);
    dot = look[0] * up[0] + look[1] * up[1] + look[2] * up[2];
    if (fabs(dot - 1.0f) >= *(double *)0x2533d0) {
      angle = acosf(dot);
      if (angle != 0.0f) {
        cross_product3d(up, look, temp);
        if (normalize3d(temp) != 0.0f) {
          c = cosf(angle);
          s = sinf(angle);
          rotate_vector3d_by_sincos(up, temp, s, c);
          rotate_vector3d_by_sincos(forward, temp, s, c);
          normalize3d(up);
          normalize3d(forward);
        }
      }
    }
    FUN_001a2800(unit_handle, (const char *)0x2b50e0);
    return;
  }

  forward[2] = 0.0f;
  if (normalize3d(forward) == 0.0f) {
    global_forward = *(float **)0x31fc3c;
    forward[0] = global_forward[0];
    forward[1] = global_forward[1];
    forward[2] = global_forward[2];
  }
  global_up = *(float **)0x31fc44;
  up[0] = global_up[0];
  up[1] = global_up[1];
  up[2] = global_up[2];
  FUN_001a2800(unit_handle, (const char *)0x2b50c8);
}

/* 0x1a4990 — reset biped aim/look caches then refresh orientation. */
char FUN_001a4990(int unit_handle)
{
  char *unit;
  char *biped_tag;
  float *look;

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */

  look = (float *)(unit + 0x46c);
  look[0] = *(float *)0x32513c;
  look[1] = *(float *)0x325140;
  look[2] = *(float *)0x325144;
  look[3] = *(float *)0x325148;
  unit[0x45c] = 0x7f;
  *(int *)(unit + 0x430) = -1;
  *(int *)(unit + 0x434) = -1;
  object_get_world_position(unit_handle, (vector3_t *)(unit + 0x438));
  *(int *)(unit + 0x448) = -1;
  *(int *)(unit + 0x444) = -1;
  *(int *)(unit + 0x44c) = -1;

  if ((*(unsigned char *)(biped_tag + 0x2f4) & 0x40) != 0)
    FUN_001a25e0(unit_handle);

  FUN_001a4440(unit_handle);
  *(int *)(unit + 0x42c) = -1;
  unit[0x42b] = 0;
  return 1;
}

/* 0x1a4a50 */
void FUN_001a4a50(void)
{
  int ebp = 0;

  FUN_001a2800(0x002b5160, (char *)(uintptr_t)ebp);

  (void)ebp;
}

/* 0x1a4a70 — apply an impulse to a biped; optionally randomize lateral kick. */
void FUN_001a4a70(int handle, float *velocity)
{
  char *unit;
  char *biped_tag;
  float *global_up;
  float lateral[3];
  float speed;
  float kick;
  float tmp[3];

  unit = (char *)object_get_and_verify_type(handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */

  /* Skip entirely when the biped is already in a special recovery state. */
  if ((*(unsigned int *)(biped_tag + 0x17c) & 0x100000) != 0)
    return;

  FUN_001a2800(handle, (const char *)0x2b5180);

  if ((*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    velocity[0] *= *(float *)0x253398;
    velocity[1] *= *(float *)0x253398;
    velocity[2] *= *(float *)0x253398;
  }
  if ((*(unsigned char *)(unit + 0xb6) & 4) != 0)
    biped_stop_limp_body_physics(handle);

  *(float *)(unit + 0x18) += velocity[0];
  *(float *)(unit + 0x1c) += velocity[1];
  *(float *)(unit + 0x20) += velocity[2];
  *(int *)(unit + 4) &= ~0x20;
  *(unsigned int *)(unit + 0x424) |= 3;

  if ((*(unsigned char *)(unit + 0xb6) & 4) != 0 ||
      (*(unsigned char *)(biped_tag + 0x2f4) & 0x44) != 0) {
    global_up = *(float **)0x31fc44;
    /* lateral = velocity × up  (same FPU order as XBE) */
    lateral[0] = velocity[2] * global_up[1] - velocity[1] * global_up[2];
    lateral[1] = global_up[2] * velocity[0] - velocity[2] * global_up[0];
    lateral[2] = velocity[1] * global_up[0] - global_up[1] * velocity[0];
    normalize3d(lateral);
    speed = sqrtf(velocity[0] * velocity[0] + velocity[1] * velocity[1] +
                  velocity[2] * velocity[2]);
    kick = random_math_real((unsigned int *)get_global_random_seed_address()) *
           speed * *(float *)0x2568bc;
    *(float *)(unit + 0x3c) += lateral[0] * kick;
    *(float *)(unit + 0x40) += lateral[1] * kick;
    *(float *)(unit + 0x44) += lateral[2] * kick;
  }

  if (*(int *)(unit + 0xcc) == -1) {
    tmp[0] = velocity[0];
    tmp[1] = velocity[1];
    tmp[2] = velocity[2];
    if (normalize3d(tmp) > 0.0f) {
      *(float *)(unit + 0x24) = tmp[0];
      *(float *)(unit + 0x28) = tmp[1];
      *(float *)(unit + 0x2c) = tmp[2];
      FUN_001a4440(handle);
      FUN_001a2800(handle, (const char *)0x2b5174);
    }
  }
}

/* 0x1a4c50 — biped facing / aim-turn update from movement state. */
void FUN_001a4c50(int unit_handle, unsigned char *state)
{
  char *unit;
  char *biped_tag;
  unsigned int tag_flags;
  float *forward;
  float *up;
  float *aim;
  float desired[3];
  float yaw_bounds[4];
  float pitch_scale;
  float yaw_scale;
  float turn;
  float blend;
  float speed_sq;
  float aim_dot;
  float thresh;
  char special;
  char facing_ok;
  float s;
  float c;
  float *global_up;
  float tmp[3];

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */
  tag_flags = *(unsigned int *)(biped_tag + 0x2f4);
  forward = (float *)(unit + 0x24);
  up = (float *)(unit + 0x30);
  aim = (float *)(unit + 0x1d4);

  /* Fast path: biped uses simple pathfinding facing and is alive. */
  if ((tag_flags & 4) != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    speed_sq = *(float *)(unit + 0x18) * *(float *)(unit + 0x18) +
               *(float *)(unit + 0x1c) * *(float *)(unit + 0x1c) +
               *(float *)(unit + 0x20) * *(float *)(unit + 0x20);
    if (!(speed_sq > *(float *)0x253f2c)) {
      speed_sq = *(float *)(unit + 0x3c) * *(float *)(unit + 0x3c) +
                 *(float *)(unit + 0x40) * *(float *)(unit + 0x40) +
                 *(float *)(unit + 0x44) * *(float *)(unit + 0x44);
      if (!(speed_sq > *(float *)0x2b51c4) &&
          !(FUN_00012170((float *)(unit + 0x228)) > *(float *)0x255d1c)) {
        if ((*(unsigned char *)(unit + 0x1b8) & 0x20) != 0) {
          unsigned int bits = 0x3f7d70a4u;
          thresh = *(float *)&bits;
        } else {
          thresh = *(float *)(biped_tag + 0x4c8);
        }
        if (FUN_00013070(aim, forward) > thresh) {
          desired[0] = forward[0];
          desired[1] = forward[1];
          desired[2] = forward[2];
          goto aim_blend;
        }
      }
    }

    desired[0] = aim[0];
    desired[1] = aim[1];
    desired[2] = aim[2];
    turn = *(float *)(biped_tag + 0x330) * *(float *)(unit + 0x230);
    if (turn != 0.0f) {
      desired[2] += turn;
      if (normalize3d(desired) == 0.0f) {
        desired[0] = aim[0];
        desired[1] = aim[1];
        desired[2] = aim[2];
      }
    }

  aim_blend:
    /* Lateral aim error vs unit up, scaled into unit+0x468 throttle. */
    turn = (up[1] * forward[2] - up[2] * forward[1]) * aim[2] +
           (up[2] * forward[0] - up[0] * forward[2]) * aim[1] +
           (up[0] * forward[1] - up[1] * forward[0]) * aim[0];
    turn = turn * *(float *)0x254e6c * *(float *)(unit + 0x228) -
           *(float *)(unit + 0x22c);
    if (turn > *(float *)0x2533ec)
      turn = *(float *)0x2533ec;
    turn *= *(float *)(biped_tag + 0x324);
    if (!(turn * *(float *)(unit + 0x468) > 0.0f)) {
      blend = 1.0f;
    } else {
      blend = *(float *)(unit + 0x468) / turn;
      if (blend > 1.0f)
        blend = 1.0f;
      blend = 1.0f - blend;
    }
    blend = (1.0f - blend) * *(float *)(biped_tag + 0x32c) +
            blend * *(float *)(biped_tag + 0x328);
    if (blend > 0.0f)
      *(float *)(unit + 0x468) =
          *(float *)(unit + 0x468) +
          (turn - *(float *)(unit + 0x468)) * blend * *(float *)0x253394;
    else
      *(float *)(unit + 0x468) = turn;

    {
      unsigned int pi = 0x40490fdbu;
      unsigned int hpi = 0x3fc90fdbu;
      yaw_bounds[0] = -*(float *)&pi;
      yaw_bounds[1] = *(float *)&pi;
      yaw_bounds[2] = -*(float *)&hpi;
      yaw_bounds[3] = *(float *)&hpi;
    }
    pitch_scale = *(float *)(biped_tag + 0x344) * *(float *)0x2546a4;
    yaw_scale = *(float *)(biped_tag + 0x348) * *(float *)0x25620c;
    if (yaw_scale == 0.0f) {
      forward[0] = desired[0];
      forward[1] = desired[1];
      forward[2] = desired[2];
    } else {
      FUN_001b0630(0, forward, desired, (float *)(unit + 0x3c), yaw_bounds,
                   pitch_scale, yaw_scale);
    }
    FUN_001a4440(unit_handle);
    FUN_001a2800(unit_handle, (const char *)0x2b51b4);
    return;
  }

  /* Slow path: seated / special movement facing. */
  if (unit[0x257] == 0)
    return;
  special = (char)(unit[0x257] == 5);

  if ((tag_flags & 0x40) != 0) {
    tmp[0] = *(float *)(unit + 0x1dc) * up[1] - *(float *)(unit + 0x1d8) * up[2];
    tmp[1] = *(float *)(unit + 0x1d4) * up[2] - *(float *)(unit + 0x1dc) * up[0];
    tmp[2] = *(float *)(unit + 0x1d8) * up[0] - *(float *)(unit + 0x1d4) * up[1];
    /* reconstruct facing from aim × up style cross (matches XBE FPU order) */
    desired[0] = tmp[1] * up[2] - tmp[2] * up[1];
    desired[1] = tmp[2] * up[0] - tmp[0] * up[2];
    desired[2] = tmp[0] * up[1] - tmp[1] * up[0];
    if (normalize3d(desired) == 0.0f) {
      desired[0] = forward[0];
      desired[1] = forward[1];
      desired[2] = forward[2];
    }
    aim_dot = desired[0] * forward[0] + desired[1] * forward[1];
  } else {
    desired[0] = aim[0];
    desired[1] = aim[1];
    desired[2] = 0.0f;
    if (magnitude3d(desired) == 0.0f) {
      desired[0] = forward[0];
      desired[1] = forward[1];
      desired[2] = forward[2];
    }
    aim_dot = desired[0] * forward[1] - desired[1] * forward[0];
  }

  facing_ok = 1;
  if (!(aim_dot > 0.0f))
    facing_ok = 0;
  if (aim_dot > *(float *)0x2568c0) {
    if (unit[0x253] == 3)
      facing_ok = 1;
    else if (unit[0x253] == 2)
      facing_ok = 0;
  }

  if (unit[0x42a] == 1 || (tag_flags & 1) != 0) {
    if ((*(unsigned int *)(unit + 0x1b8) & 0x100) != 0)
      return;
    c = cosf(*(float *)(biped_tag + 0x2f0) * *(float *)0x2546a4);
    s = sinf(*(float *)(biped_tag + 0x2f0) * *(float *)0x2546a4);
    if (facing_ok)
      s = -s;
    if ((tag_flags & 0x40) != 0) {
      rotate_vector3d_by_sincos(forward, up, s, c);
      cross_product3d(desired, forward, tmp);
      aim_dot = tmp[0] * up[0] + tmp[1] * up[1] + tmp[2] * up[2];
    } else {
      float nx = s * forward[0] + c * forward[1];
      float ny = c * forward[0] - s * forward[1];
      forward[0] = ny;
      forward[1] = nx;
      aim_dot = desired[0] * forward[1] - desired[1] * forward[0];
    }
    /* XBE: if facing_ok, require aim_dot > 0; else require aim_dot < 0. */
    if (facing_ok ? !(aim_dot > 0.0f) : !(aim_dot < 0.0f))
      goto done_rotate;

    if ((*(unsigned char *)(biped_tag + 0x2f4) & 0x40) != 0) {
      cross_product3d(up, desired, tmp);
      if (normalize3d(tmp) > 0.0f)
        cross_product3d(tmp, up, forward);
    } else {
      forward[0] = desired[0];
      forward[1] = desired[1];
      forward[2] = 0.0f;
      global_up = *(float **)0x31fc44;
      up[0] = global_up[0];
      up[1] = global_up[1];
      up[2] = global_up[2];
    }
    normalize3d(forward);
  done_rotate:
    FUN_001a2800(unit_handle, (const char *)0x2b518c);
    return;
  }

  if (unit[0x42a] != 0 || special ||
      (*(unsigned int *)(unit + 0x1b4) & 0x4000) != 0 ||
      (*(unsigned int *)(unit + 0x1b8) & 0x100) != 0)
    return;

  if ((*(unsigned char *)(unit + 0x1b8) & 0x20) != 0)
    thresh = *(float *)0x28ace8;
  else
    thresh = *(float *)(biped_tag + 0x4c8);
  if (aim_dot > thresh &&
      (*(unsigned int *)(biped_tag + 0x17c) & 0x100000) == 0 && state) {
    *state = (unsigned char)((facing_ok ? 1 : 0) + 2);
  }
  FUN_001a2800(unit_handle, (const char *)0x2b51a0);
}

/* 0x1a5300 */
void FUN_001a5300(int unit_handle, unsigned char *state)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  /* relift: test byte ptr [edi + 0xb6], 4 -> je 0x1a533e */
  /* relift: test byte ptr [edi + 0x248], 4 -> jne 0x1a6277 */
  tag_get(0x62697064, 0);
  /* test (char)ecx, 8 -> je 0x1a53a6 */
  unit_scripting_unit_driver(0, (void *)(uintptr_t)eax);
  biped_get_camera_height_and_offset(0, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1a5514 */
  FUN_000b5590(0);
  /* relift: test byte ptr [ebx + 0x2f4], 4 -> je 0x1a5531 */
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1a5531 */
  /* test (char)eax, 0x41 -> jne 0x1a5585 */
  /* test (char)eax, 0x41 -> jne 0x1a55af */
  /* test (char)eax, 0x41 -> jne 0x1a55af */
  /* test (char)eax, 0x41 -> jne 0x1a55fc */
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1a5677 */
  /* relift: test byte ptr [ebx + 0x2f4], 4 -> jne 0x1a58d8 */
  /* relift: test byte ptr [edi + 0x248], 4 -> jne 0x1a58d8 */
  tag_get('edom', 0);
  tag_get('rtna', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00120590((void *)(uintptr_t)eax, 0, 16);
  FUN_00120590((void *)(uintptr_t)eax, 0, 12);
  FUN_00120590((void *)(uintptr_t)eax, 0, 0);
  rotate_vector3d_by_sincos((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, 0.0f, 0.0f);
  /* test (char)eax, 0x20 -> je 0x1a58ba */
  /* cmp (char)eax, 2 -> je 0x1a57f3 */
  /* cmp (char)eax, 3 -> jne 0x1a58ba */
  FUN_00013070((float *)(uintptr_t)eax, (float *)(uintptr_t)ecx);
  /* test (char)eax, 0x41 -> jne 0x1a58ba */
  cross_product3d((float *)(uintptr_t)eax, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  cross_product3d((float *)(uintptr_t)eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  unit_abort_animation(0);
  FUN_001a4440(0);
  /* test (char)eax, 4 -> je 0x1a5a4b */
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1a5a4b */
  FUN_00012fe0((float *)(uintptr_t)esi);
  /* test (char)eax, 0x41 -> jne 0x1a599c */
  /* relift: cmp dword ptr [edi + 0x464], 0x3f800000 -> jne 0x1a596f */
  /* test (char)eax, 0x41 -> jne 0x1a599c */
  /* test (char)eax, 2 -> je 0x1a5c20 */
  /* relift: cmp byte ptr [edi + 0x253], 0x1c -> je 0x1a5c20 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp eax, -1 -> je 0x1a5aa2 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 0x41 -> jne 0x1a5ae2 */
  /* test (char)eax, 0x41 -> jne 0x1a5b56 */
  game_players_are_double_speed();
  /* test (char)eax, (char)eax -> je 0x1a5c47 */
  /* relift: test byte ptr [edi + 0x424], 3 -> jne 0x1a5c47 */
  /* relift: test byte ptr [edi + 0x424], 1 -> je 0x1a5c85 */
  /* relift: cmp byte ptr [edi + 0x459], 0x16 -> jge 0x1a5c85 */
  /* cmp eax, -1 -> je 0x1a5c85 */
  actor_is_leaping(0);
  /* test (char)eax, (char)eax -> je 0x1a5c85 */
  /* relift: cmp byte ptr [edi + 0x257], 3 -> jne 0x1a5cd9 */
  /* test (char)eax, 0x41 -> jne 0x1a5ccd */
  /* test (char)eax, 0x41 -> jne 0x1a5d4a */
  /* relift: test byte ptr [edi + 0x424], 1 -> je 0x1a5d4a */
  /* test (char)ecx, (char)ecx -> jne 0x1a5d77 */
  /* test (char)eax, 1 -> je 0x1a5d88 */
  /* test (char)eax, 2 -> je 0x1a5d93 */
  /* test (char)eax, 4 -> je 0x1a5d9e */
  /* relift: test byte ptr [ebx + 0x2f4], 4 -> je 0x1a5dd7 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1a5dd7 */
  /* relift: test byte ptr [ebx + 0x2f4], 0x20 -> je 0x1a5de7 */
  /* relift: test byte ptr [ebx + 0x2f4], (char)ecx -> je 0x1a5dfb */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1a5dfb */
  FUN_001a2f40((void *)0);
  /* cmp eax, -1 -> je 0x1a5e1d */
  /* test (char)eax, (char)eax -> jle 0x1a5e31 */
  /* relift: test dword ptr [edi + 0x1b4], 0x1000000 -> je 0x1a5e8f */
  object_translate(0, (float *)(uintptr_t)eax, (void *)0);
  /* test (char)ecx, 4 -> je 0x1a5f1e */
  /* test (char)eax, 0x41 -> jne 0x1a5fac */
  FUN_001a0e00(0.0f, 0);
  /* test (char)ecx, 4 -> jne 0x1a5fbf */
  FUN_001a2b90(0);
  /* relift: cmp byte ptr [edi + 0x239], 3 -> jne 0x1a61ba */
  /* cmp eax, -1 -> je 0x1a61ba */
  object_get_and_verify_type(0, 0);
  display_assert((char *)0x00253440, (char *)0x002b4d5c, 2157, 0);
  system_exit(0);
  fast_vector_intersects_sphere((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, 0.0f);
  /* test (char)eax, (char)eax -> je 0x1a6189 */
  FUN_0014c8e0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1a6189 */
  FUN_0014cb00(0, (void *)0, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1a6189 */
  FUN_0014df70(49824, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1a6189 */
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx);
  FUN_0010a1c0((float *)(uintptr_t)edx, (float *)0, (float *)0);
  plane_negate((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  unit_impact_melee_damage(0, 0, 0, 0, 0, 0, (float *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x1a61b3 */
  display_assert((char *)0x00253418, (char *)0x002b4d5c, 2200, 0);
  system_exit(0);
  FUN_001a0a40(0, 0, (float *)0);
  FUN_001a0be0(0.0f, 0);
  /* relift: test byte ptr [ecx + 0x424], 1 -> jne 0x1a61ff */
  /* relift: test byte ptr [ecx + 0x424], 1 -> jne 0x1a6251 */
  /* relift: test byte ptr [ebp - 0x44], 0x10 -> jne 0x1a6251 */
  object_get_and_verify_type(0, 0);
  tag_get('dpib', 0);
  /* test (char)ecx, 0x20 -> je 0x1a62db */
  /* relift: cmp (char)ecx, byte ptr [esi + 0x47d] -> jae 0x1a62db */
  /* test (char)eax, (char)eax -> jne 0x1a62c6 */
  FUN_001a0680(0);
  FUN_001a2800(0x002b51ec, (char *)0);
  /* relift: cmp byte ptr [esi + 0x459], 3 -> jl 0x1a6317 */
  /* test (char)ecx, 4 -> jne 0x1a6317 */
  /* relift: cmp byte ptr [esi + 0x253], 0x18 -> jne 0x1a62ff */
  FUN_001a2160(0);
  FUN_001a2800(0x002b51d8, (char *)0);
  /* relift: cmp byte ptr [esi + 0x253], 0x18 -> jne 0x1a6333 */
  FUN_001a4440(0);
  FUN_001a2800(0x002b51cc, (char *)0);
  object_get_and_verify_type(0, 0);
  tag_get('dpib', 0);
  /* test (char)eax, (char)eax -> jne 0x1a678d */
  /* test (char)eax, (char)eax -> je 0x1a63a4 */
  /* test (char)eax, (char)eax -> je 0x1a63a4 */
  profile_enter_private((void *)0x0032d1d0);
  FUN_001a2800(0x002b524c, (char *)0);
  /* cmp eax, -1 -> je 0x1a6461 */
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)ecx, 1 -> jne 0x1a6444 */
  object_get_and_verify_type(0, 0);
  FUN_001a1fb0(0);
  /* relift: test byte ptr [esi + 0x1b8], 0x40 -> je 0x1a640b */
  unit_try_and_exit_seat(0);
  /* test (char)eax, (char)eax -> je 0x1a672c */
  /* relift: test byte ptr [ebx + 4], 2 -> je 0x1a672c */
  unit_exit_seat_end(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1a672c */
  FUN_001a4440(0);
  /* test (char)eax, 4 -> jne 0x1a647d */
  /* relift: test byte ptr [ebx + 0x2f4], 0x44 -> jne 0x1a64b8 */
  normalize3d((float *)(uintptr_t)ebx);
  /* cmp eax, 7 -> ja 0x1a64e4 */
  /* test (char)ecx, 1 -> je 0x1a655f */
  /* cmp (char)eax, 0x7f -> jge 0x1a6566 */
  /* test (char)ecx, 2 -> je 0x1a657f */
  /* cmp (char)eax, 0x7f -> jge 0x1a6586 */
  FUN_001a2800(0x002b5240, (char *)0);
  /* test (char)eax, 4 -> jne 0x1a65c7 */
  FUN_001a4c50(0, (unsigned char *)(uintptr_t)ecx);
  FUN_001a2800(0x002b5230, (char *)0);
  /* relift: tail-call FUN_001a5300(); */
  FUN_001a2800(0x002b5224, (char *)0);
  /* test (char)eax, 4 -> je 0x1a65f4 */
  FUN_001a6280(0, (char *)0);
  /* test (char)eax, 1 -> je 0x1a660d */
  FUN_001a2900(0, (char *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 0x460], -1 -> je 0x1a6622 */
  FUN_001a2a60(0, (char *)0);
  /* test (char)eax, 2 -> je 0x1a6632 */
  FUN_001a2b10(0);
  FUN_001a2800(0x002b520c, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x1a6702 */
  /* relift: cmp dword ptr [esi + 0x1c8], -1 -> je 0x1a6719 */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, eax);
  weapon_prevents_melee_attack(0);
  /* test (char)eax, (char)eax -> jne 0x1a6719 */
  /* relift: cmp byte ptr [esi + 0x2d0], 0xff -> jne 0x1a6719 */
  unit_animation_start_action(0, 0);
  weapon_stop_reload(0);
  first_person_weapon_message_from_unit(0, 0);
  weapon_get_animation_frame(0, 0, 13, 0);
  weapon_get_animation_frame(0, 0, 13, 0);
  /* relift: cmp (char)eax, byte ptr [esi + 0x45e] -> jne 0x1a6713 */
  unit_cause_player_melee_damage(0);
  FUN_001a2440(0);
  FUN_001a1e70(0);
  FUN_001a0b30(0);
  FUN_001b0d90(0, (char *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 1 -> jne 0x1a6744 */
  FUN_001a2290(0);
  /* relift: test byte ptr [esi + 0xb6], 4 -> je 0x1a6759 */
  /* relift: test byte ptr [esi + 4], 0x20 -> je 0x1a6759 */
  FUN_001a2800(0x002b5200, (char *)0);
  /* test (char)eax, (char)eax -> je 0x1a678d */
  /* test (char)eax, (char)eax -> je 0x1a678d */
  profile_exit_private((void *)0x0032d1d0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1b8f10 */
void FUN_001b8f10(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  tag_get('syhp', 0);
  /* test (char)eax, 0x41 -> jne 0x1b8f60 */
  FUN_001b69a0(0, 0, 0);
  FUN_001b7020(0);
  FUN_001b6560(0, 0, 0);
  FUN_001b7020(0);

  (void)eax;
}

/* 0x1b8f80 */
void FUN_001b8f80(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  /* test (char)eax, (char)eax -> je 0x1b8fd6 */
  profile_enter_private((void *)0x0032e4a0);
  /* relift: cmp dword ptr [ebx + 0xcc], -1 -> je 0x1b8ffa */
  /* test (char)eax, 1 -> je 0x1b900d */
  /* test (char)eax, 2 -> jne 0x1b9076 */
  /* relift: test byte ptr [edi + 0x2f0], 0x10 -> je 0x1b906d */
  /* test (char)eax, 0x41 -> jne 0x1b9047 */
  /* test (char)eax, 0x41 -> je 0x1b9076 */
  /* test dl, dl -> je 0x1b9278 */
  /* relift: cmp byte ptr [ebx + 0x42a], 0x1e -> jae 0x1b9278 */
  /* cmp dl, 2 -> je 0x1b9137 */
  /* cmp dl, 4 -> je 0x1b9137 */
  /* cmp dl, 3 -> je 0x1b915f */
  cross_product3d((float *)(uintptr_t)edi, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x1b91a7 */
  /* cmp (char)eax, 1 -> jne 0x1b91ef */
  cross_product3d((float *)(uintptr_t)edi, (float *)(uintptr_t)esi, (float *)(uintptr_t)ecx);
  vector3d_scale_add((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, (float *)0);
  FUN_00012fb0((float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1b9255 */
  /* cmp eax, 5 -> jne 0x1b9270 */
  /* test (char)eax, 0x41 -> jne 0x1b923c */
  FUN_00013070((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  FUN_00012fb0((float *)(uintptr_t)edi, 0.0f, (float *)0);
  FUN_00154630();
  FUN_00154630();
  FUN_00154630();
  /* test (char)eax, 0x41 -> jne 0x1b935e */
  FUN_00154750();
  /* test (char)eax, 0x41 -> jne 0x1b93da */
  FUN_00154630();
  /* relift: cmp dword ptr [edi + 0x8c], -1 -> je 0x1b947f */
  /* test (char)ecx, 1 -> je 0x1b941f */
  /* test (char)ecx, 2 -> je 0x1b9433 */
  /* test (char)ecx, 4 -> je 0x1b944b */
  /* test (char)ecx, 8 -> je 0x1b9463 */
  /* test (char)ecx, 0x20 -> je 0x1b947f */
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x1b94a9 */
  display_assert((char *)0x00253440, (char *)0x002b7d78, 308, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x8c], -1 -> je 0x1b9819 */
  /* relift: test byte ptr [ebx + 4], 0x20 -> jne 0x1b9819 */
  FUN_001b5ff0();
  FUN_001b6140();
  FUN_001b6250(0, 0, 0);
  FUN_001b77f0(0, 0, 0);
  FUN_001b74d0(0);
  /* test (char)eax, (char)eax -> jne 0x1b958a */
  FUN_001b72b0(0, 0, 0);
  FUN_001b56b0(0, 0);
  /* test (char)eax, 0x20 -> je 0x1b95b1 */
  /* test eax, 0x1000000 -> jne 0x1b966b */
  /* test dl, 0x28 -> je 0x1b966b */
  scenario_get();
  scenario_get();
  /* test (char)eax, 0x41 -> jne 0x1b966b */
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x1b9698 */
  display_assert((char *)0x00253418, (char *)0x002b7d78, 372, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0x2f0], 0x40 -> je 0x1b971c */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x1b971c */
  /* cmp edi, -1 -> je 0x1b971c */
  object_get_and_verify_type(0, 0);
  damage_data_new((void *)(uintptr_t)edx, 0);
  object_cause_damage((void *)(uintptr_t)eax, 0, 0, 0, 0, 0);
  /* cmp edi, -1 -> jne 0x1b96e2 */
  /* relift: cmp dword ptr [esi + 0x44], -1 -> je 0x1b973d */
  FUN_001b0d90(0, (char *)(uintptr_t)ecx);
  /* cmp (char)ecx, (char)eax -> je 0x1b9845 */
  object_permute_region(0, (char *)0x002b7d70, 0, ecx);
  /* test (char)eax, (char)eax -> je 0x1b983e */
  FUN_001b81d0(0, 0, 0);
  FUN_001b8570(0, 0.0f, 0, 0);
  FUN_001b8f10();
  FUN_00154270(0, 0, 0, 0, 0);
  /* relift: cmp word ptr [ebx + 0x426], 0 -> jle 0x1b966e */
  FUN_001b6ca0(0);
  FUN_001b74d0(0);
  /* test (char)eax, (char)eax -> je 0x1b9867 */
  profile_exit_private((void *)0x0032e4a0);
  sound_cache_close();
  texture_cache_close();
  cache_file_close();
  tags_header_deregister_vertex_and_index_buffers((void *)(uintptr_t)eax);
  /* mem[0x005054f0] = eax */
  /* test (char)eax, (char)eax -> jne 0x1b9912 */
  display_assert((char *)0x002b7da8, (char *)0x002b7dc8, 276, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1b99d2 */
  /* test eax, eax -> jne 0x1b996f */
  display_assert((char *)0x002b7dec, (char *)0x002b7dc8, 295, 0);
  system_exit(0);
  /* test ecx, ecx -> jle 0x1b99d2 */
  /* relift: cmp edi, dword ptr [eax] -> jne 0x1b99a5 */
  crt_stricmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1b99be */
  /* cmp eax, edx -> jl 0x1b9985 */
  physical_memory_protect((void *)0x803a6000, 0x01600000, 0);
  physical_memory_protect((void *)0x803a6000, 0x01600000, 0);
  physical_memory_protect((void *)(uintptr_t)ecx, eax, 0);
  physical_memory_protect((void *)(uintptr_t)eax, edx, 0);
  /* test eax, eax -> je 0x1b9a80 */
  physical_memory_protect((void *)(uintptr_t)edx, ecx, 0);
  physical_memory_protect((void *)(uintptr_t)ecx, eax, 0);
  error(0, (char *)0x002b7e04);
  error(0, (char *)0x002b7e44);
  error(0, (char *)0x002b7e80);
  error(0, (char *)0x002b7ec8);
  error(0, (char *)0x002b7f10);
  error(0, (char *)0x002b7f48);
  error(0, (char *)0x002b7f80);
  error(0, (char *)0x002b7fc0);
  /* cmp ecx, edi -> jge 0x1b9be9 */
  /* cmp edx, -1 -> je 0x1b9be6 */
  /* relift: cmp edx, dword ptr [ecx] -> je 0x1b9be6 */
  /* relift: cmp edx, dword ptr [ecx + 4] -> je 0x1b9be6 */
  /* relift: cmp edx, dword ptr [ecx + 8] -> je 0x1b9be6 */
  /* relift: cmp ecx, dword ptr [edx + 0xc] -> jl 0x1b9ba0 */
  /* test (char)eax, (char)eax -> jne 0x1b9c19 */
  display_assert((char *)0x002b7da8, (char *)0x002b7dc8, 467, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1b9c42 */
  display_assert((char *)0x002b7dec, (char *)0x002b7dc8, 468, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1b9c57 */
  /* cmp eax, edx -> jl 0x1b9c86 */
  csprintf((char *)0x005ab100, (char *)0x002b8000);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test edi, 0xffff0000 -> je 0x1b9cd1 */
  /* relift: cmp dword ptr [esi + 0xc], edi -> je 0x1b9cd1 */
  csprintf((char *)0x005ab100, (char *)0x002b8000);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x7fc], 0x666f6f74 -> jne 0x1b9d93 */
  /* test eax, eax -> jl 0x1b9d93 */
  /* cmp eax, 0x11600000 -> jg 0x1b9d93 */
  csstrlen((char *)(uintptr_t)edi);
  /* cmp eax, 0x1f -> ja 0x1b9d93 */
  /* relift: cmp dword ptr [esi + 4], 5 -> je 0x1b9d4f */
  /* test (char)eax, (char)eax -> je 0x1b9dcc */
  csstrcmp((char *)(uintptr_t)esi, (char *)0x00288bdc);
  /* test eax, eax -> je 0x1b9d8d */
  /* test (char)eax, (char)eax -> je 0x1b9dcc */
  csprintf((char *)0x005ab100, (char *)0x002b804c);
  /* test (char)eax, (char)eax -> je 0x1b9dcc */
  csprintf((char *)0x005ab100, (char *)0x002b8024);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  cache_files_precache_map_loaded((char *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x1b9e00 */
  cache_files_precache_in_progress();
  /* test (char)eax, (char)eax -> je 0x1b9e1b */
  cache_files_precache_is_copying_map((char *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x1b9e1b */
  cache_files_precache_map_end();
  cache_files_precache_in_progress();
  /* test (char)eax, (char)eax -> je 0x1b9e49 */
  cache_files_precache_map_status((float *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 2 -> je 0x1b9e5f */
  /* cmp (int16_t)eax, 1 -> jne 0x1b9e64 */
  cache_files_precache_map_end();
  cache_files_precache_set_priority(0);
  cache_files_precache_map_begin((char *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x1b9e64 */
  display_error_damaged_media();
  tag_name_strip_path((char *)(uintptr_t)edi);
  texture_cache_open();
  FUN_001bdec0();
  cache_file_open();
  /* test (char)eax, (char)eax -> je 0x1b9f91 */
  FUN_001bdd50();
  cache_file_header_verify((void *)0x004e4d04, (char *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1b9f91 */
  csmemset((void *)(uintptr_t)esi, 205, 0x01600000);
  cache_file_read(0, 0, ecx, 0, (char *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x1b9f0c */
  SwitchToThread();
  /* test (char)eax, (char)eax -> je 0x1b9f00 */
  /* mem[0x004e5504] = eax */
  /* cmp ecx, 0x74616773 -> je 0x1b9f69 */
  csprintf((char *)0x005ab100, (char *)0x002b80ac);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* mem[0x005054f0] = ecx */
  tags_header_register_vertex_and_index_buffers((void *)(uintptr_t)eax);
  FUN_001bdd50();
  csmemset((void *)(uintptr_t)ecx, 205, 0);
  cache_file_read(0, 0, edx, 0, (char *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x1ba014 */
  SwitchToThread();
  sound_render_time();
  system_milliseconds();
  /* cmp eax, 0x21 -> jbe 0x1ba00d */
  sound_idle();
  /* test (char)eax, (char)eax -> je 0x1b9ff0 */
  /* mem[0x004e5508] = eax */
  /* relift: cmp dword ptr [eax + 0x14], 0x73627370 -> je 0x1ba04a */
  display_assert((char *)0x002b8128, (char *)0x002b7dc8, 173, 0);
  system_exit(0);
  structure_bsp_header_register_vertex_buffers((void *)(uintptr_t)eax);
  tag_instance_resolve(0);
  /* test eax, eax -> je 0x1ba084 */
  display_assert((char *)0x002b8108, (char *)0x002b7dc8, 183, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x73627370 -> je 0x1ba0ac */
  display_assert((char *)0x002b80dc, (char *)0x002b7dc8, 184, 0);
  system_exit(0);
  structure_bsp_header_deregister_vertex_buffers((void *)(uintptr_t)eax);
  tag_instance_resolve(0);
  /* cmp eax, edi -> jne 0x1ba109 */
  display_assert((char *)0x002b8188, (char *)0x002b7dc8, 205, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x73627370 -> je 0x1ba131 */
  display_assert((char *)0x002b80dc, (char *)0x002b7dc8, 206, 0);
  system_exit(0);
  /* mem[0x004e5508] = edi */
  tag_instance_resolve(0);
  /* cmp eax, ebx -> je 0x1ba1b1 */
  /* relift: cmp dword ptr [esi + 4], ebx -> je 0x1ba1b1 */
  /* relift: cmp dword ptr [esi + 8], ebx -> je 0x1ba1b1 */
  tag_to_string(eax, (void *)(uintptr_t)ecx);
  tag_to_string(ebx, (void *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x002b81cc);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1ba1e6 */
  csprintf((char *)0x005ab100, (char *)0x002b81a4);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  tag_instance_resolve(0);
  tag_instance_resolve(0);
  WaitForSingleObject(0, 0);
  SetThreadPriority(0, 0);
  SetThreadPriority(0, 0);
  SetThreadPriority(0, 0);
  SetThreadPriority(0, 0);
  WaitForSingleObject(0, 0);
  WaitForSingleObject(0, 0);
  /* test eax, eax -> jne 0x1ba5a9 */
  /* test eax, eax -> jne 0x1ba335 */
  display_assert((char *)0x002b8388, (char *)0x002b839c, 524, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x1ba35e */
  display_assert((char *)0x002b8360, (char *)0x002b839c, 525, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1ba385 */
  display_assert((char *)0x00267900, (char *)0x002b839c, 526, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], 0x512000 -> jge 0x1ba3ae */
  display_assert((char *)0x002b8344, (char *)0x002b839c, 527, 0);
  system_exit(0);
  GetFileSize(0, (void *)0);
  /* relift: cmp dword ptr [ebp + 0x14], eax -> je 0x1ba3db */
  display_assert((char *)0x002b8308, (char *)0x002b839c, 528, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba40f */
  display_assert((char *)0x002b82e4, (char *)0x002b839c, 530, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba43e */
  display_assert((char *)0x002b82c4, (char *)0x002b839c, 531, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba46d */
  display_assert((char *)0x002b82a4, (char *)0x002b839c, 532, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba49c */
  display_assert((char *)0x002b8280, (char *)0x002b839c, 533, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba4cb */
  display_assert((char *)0x002b8264, (char *)0x002b839c, 535, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba4fa */
  display_assert((char *)0x002b8244, (char *)0x002b839c, 537, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba529 */
  display_assert((char *)0x002b8224, (char *)0x002b839c, 538, 0);
  system_exit(0);
  csstrcpy((char *)(uintptr_t)eax, (char *)(uintptr_t)edx);
  ResetEvent();
  ResetEvent();
  csmemset((void *)(uintptr_t)eax, 0, 0);
  SetEvent((void *)(uintptr_t)edx);
  display_assert((char *)0x002b81fc, (char *)0x002b839c, 564, 0);
  system_exit(0);
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1ba5f9 */
  SetEvent((void *)(uintptr_t)eax);
  FUN_001155c0(0, (char *)0x0028ce40, 56);
  FUN_00115430(0);
  /* relift: cmp eax, dword ptr [ecx + 0x944] -> jl 0x1ba6ad */
  display_assert((char *)0x002b83d8, (char *)0x002b839c, 701, 0);
  system_exit(0);
  /* cmp esi, ecx -> jbe 0x1ba6fb */
  display_assert((char *)0x002b842c, (char *)0x002b839c, 710, 0);
  system_exit(0);
  physical_memory_protect((void *)(uintptr_t)eax, 0x00512000, 0);
  csmemset((void *)(uintptr_t)ecx, 253, 0x00500000);
  physical_memory_protect((void *)(uintptr_t)edx, 0x00500000, 0);
  csmemset((void *)(uintptr_t)esi, 0, 0);
  CreateFileA((char *)(uintptr_t)esi, 0x80000000, edi, edi, 0, 0x60000000, edi);
  GetFileSize(0, (void *)(uintptr_t)edi);
  csmemset((void *)(uintptr_t)eax, 0, 220);
  /* cmp eax, 0x800 -> jae 0x1ba839 */
  display_assert((char *)0x002b845c, (char *)0x002b839c, 964, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, 0);
  csmemset((void *)(uintptr_t)edx, 0, 0);
  FUN_001d00b9();
  /* test (char)eax, 1 -> je 0x1ba8f1 */
  display_assert((char *)0x002b84a8, (char *)0x002b839c, 1482, 0);
  system_exit(0);
  display_assert((char *)0x002b8488, (char *)0x002b839c, 1483, 0);
  system_exit(0);
  /* test (char)eax, 4 -> jne 0x1ba95b */
  display_assert((char *)0x002b8538, (char *)0x002b839c, 1494, 0);
  system_exit(0);
  FUN_001d00b9();
  /* test (char)eax, 4 -> je 0x1ba99c */
  display_assert((char *)0x002b84f0, (char *)0x002b839c, 1498, 0);
  system_exit(0);
  display_assert((char *)0x002b8488, (char *)0x002b839c, 1499, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + edx*2 + 0xa78], (int16_t)ebx -> jne 0x1baa05 */
  /* relift: test dword ptr [esi + edx*4 + 0x998], eax -> jne 0x1baa13 */
  /* cmp (int16_t)edi, 8 -> jl 0x1ba9e0 */
  physical_memory_protect((void *)(uintptr_t)ecx, 0x00020000, 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1baa67 */
  /* cmp (int16_t)esi, 8 -> jl 0x1baa93 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1606, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1baaab */
  /* cmp (int16_t)esi, 1 -> jl 0x1baad6 */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1baafb */
  /* cmp (int16_t)eax, 1 -> jl 0x1bab1b */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* test esi, esi -> jle 0x1bab58 */
  /* test (char)eax, (char)eax -> jne 0x1bab4e */
  /* relift: cmp dword ptr [edi + ecx*4], 0 -> jne 0x1bab4e */
  /* cmp ecx, esi -> jl 0x1bab40 */
  /* test eax, eax -> je 0x1babb8 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1babb8 */
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> je 0x1bab70 */
  display_assert((char *)0x002b8488, (char *)0x002b839c, 1695, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1babe7 */
  display_assert((char *)0x002b8610, (char *)0x002b839c, 1699, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 0);
  csmemset((void *)0x004e5610, 0, 36);
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  error(0, (char *)0x002b87ac);
  error(0, (char *)0x002b878c);
  error(0, (char *)0x002b876c);
  error(0, (char *)0x002b8750);
  error(0, (char *)0x002b8724);
  error(0, (char *)0x002b8700);
  error(0, (char *)0x002b86d4);
  error(0, (char *)0x002b86a4);
  error(0, (char *)0x002b8684);
  /* test (char)ecx, (char)ecx -> jne 0x1badb4 */
  /* test edi, edi -> jne 0x1badff */
  display_assert((char *)0x002b87d0, (char *)0x002b839c, 574, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x1bae15 */
  FUN_001d0362();
  /* test ebx, ebx -> jne 0x1baed6 */
  /* test ecx, ecx -> je 0x1baed6 */
  /* test ecx, ecx -> jle 0x1baec6 */
  WaitForSingleObject(0, 0);
  WaitForSingleObject(0, 0);
  /* test eax, eax -> jne 0x1baf3d */
  /* test (char)eax, 0x41 -> jne 0x1baeb6 */
  /* test (char)ebx, 2 -> je 0x1baeee */
  /* test (char)ebx, 4 -> je 0x1baeff */
  /* test (char)ebx, 1 -> je 0x1baf17 */
  display_assert((char *)0x00255ee8, (char *)0x002b839c, 626, 0);
  system_exit(0);
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1baf8d */
  SetEvent((void *)(uintptr_t)eax);
  WaitForSingleObject(0, 0);
  /* test (char)eax, (char)eax -> je 0x1baf9b */
  /* test esi, esi -> jl 0x1bb0b9 */
  /* cmp esi, 0xb -> jge 0x1bb029 */
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* cmp esi, 7 -> jg 0x1bb0b9 */
  /* test eax, eax -> jg 0x1bb062 */
  display_assert((char *)0x002b882c, (char *)0x002b839c, 1291, 0);
  system_exit(0);
  ResetEvent();
  SetEvent((void *)(uintptr_t)ecx);
  /* cmp esi, 9 -> jl 0x1bb179 */
  /* test eax, eax -> jg 0x1bb0f8 */
  display_assert((char *)0x002b8804, (char *)0x002b839c, 1300, 0);
  system_exit(0);
  csprintf((char *)0x004e5510, (char *)0x002b87dc);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp esi, 9 -> jl 0x1bb165 */
  QueryPerformanceCounter((void *)0x004e5640);
  display_assert((char *)0x002b8878, (char *)0x002b839c, 1334, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  SleepEx(0, 0);
  SetLastError(0);
  FUN_001d19e7();
  xapi_GetLastError();
  /* test esi, esi -> jne 0x1bb29e */
  /* cmp eax, 0x6f8 -> je 0x1bb222 */
  /* cmp eax, 8 -> je 0x1bb222 */
  /* cmp eax, 0x5aa -> je 0x1bb222 */
  display_assert((char *)0x002b8854, (char *)0x002b839c, 1369, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5614] = ecx */
  QueryPerformanceCounter((void *)0x004e5648);
  display_assert((char *)0x002b8878, (char *)0x002b839c, 1411, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  SleepEx(0, 0);
  SetLastError(0);
  FUN_001d1a38();
  xapi_GetLastError();
  /* test esi, esi -> jne 0x1bb3e1 */
  /* cmp eax, 0x6f8 -> je 0x1bb365 */
  /* cmp eax, 8 -> je 0x1bb365 */
  /* cmp eax, 0x5aa -> je 0x1bb365 */
  display_assert((char *)0x002b88c0, (char *)0x002b839c, 1441, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5618] = ecx */
  FUN_001bb190();
  FUN_001bb2d0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1bb430 */
void FUN_001bb430(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  FUN_001baa50();
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bb463 */
  /* cmp (int16_t)eax, 8 -> jl 0x1bb483 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1516, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax], -1 -> je 0x1bb4ac */
  display_assert((char *)0x002b8918, (char *)0x002b839c, 1517, 0);
  system_exit(0);
  physical_memory_protect((void *)(uintptr_t)ebx, esi, 0);
  FUN_001bb190();
  display_assert((char *)0x002b88e8, (char *)0x002b839c, 1537, 0);
  system_exit(0);
  /* relift: tail-call FUN_001bb430(); */
  /* cmp (int16_t)esi, 8 -> jl 0x1bb586 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1561, 0);
  system_exit(0);
  /* relift: tail-call FUN_001bb430(); */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1bb5a0 */
void acquire_read_request(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, 8 -> jl 0x1bb5e1 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1618, 0);
  system_exit(0);
  /* relift: test dword ptr [ebx], edi -> jne 0x1bb61e */
  display_assert((char *)0x002b8940, (char *)0x002b839c, 1619, 0);
  system_exit(0);
  FUN_001bb430();

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1bb640 */
void FUN_001bb640(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)esi, 1 -> jl 0x1bb678 */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 1 -> jl 0x1bb6ba */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* cmp ebx, 0x400000 -> jl 0x1bb6f8 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bb6d3 */
  /* cmp (int16_t)esi, 1 -> jl 0x1bb6f3 */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bb703 */
  /* cmp (int16_t)esi, 1 -> jl 0x1bb723 */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1654, 0);
  system_exit(0);
  physical_memory_protect((void *)(uintptr_t)edx, 0x00400000, 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bb73e */
  /* cmp (int16_t)esi, 1 -> jl 0x1bb75e */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  FUN_001bb2d0();
  display_assert((char *)0x002b899c, (char *)0x002b839c, 1666, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ebx, 0, 2048);
  FUN_001bb2d0();
  FUN_001ba930();
  /* test ecx, ecx -> je 0x1bb83a */
  display_assert((char *)0x002b89d4, (char *)0x002b839c, 1003, 0);
  system_exit(0);
  FUN_001bb190();
  FUN_001ba8b0();
  cache_file_header_verify((void *)(uintptr_t)ebx, (char *)0x002b89cc, 0);
  /* relift: test dword ptr [esi], ebx -> je 0x1bb8fe */
  display_assert((char *)0x002b8878, (char *)0x002b839c, 1046, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bb909 */
  /* cmp (int16_t)edi, 8 -> jl 0x1bb929 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1561, 0);
  system_exit(0);
  FUN_001bb430();
  /* test eax, eax -> jle 0x1bb9d5 */
  /* test eax, eax -> je 0x1bb9d5 */
  /* test (char)eax, 2 -> je 0x1bb9d5 */
  display_assert((char *)0x002b8ad0, (char *)0x002b839c, 1075, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1bba55 */
  /* test eax, eax -> jne 0x1bba55 */
  /* test eax, eax -> jle 0x1bba55 */
  /* cmp (int16_t)ecx, (int16_t)edi -> je 0x1bba13 */
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xabe] -> jle 0x1bba55 */
  /* cmp (int16_t)ecx, (int16_t)eax -> je 0x1bba2e */
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xabe] -> je 0x1bba37 */
  /* cmp (int16_t)eax, 1 -> jl 0x1bba15 */
  /* relift: tail-call FUN_001bb640(); */
  /* relift: cmp word ptr [esi + 0xabc], (int16_t)edi -> jne 0x1bbb52 */
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jge 0x1bbb52 */
  /* relift: cmp word ptr [esi + ecx*2 + 0xa88], (int16_t)edi -> je 0x1bba87 */
  /* cmp (int16_t)eax, 1 -> jl 0x1bba71 */
  physical_memory_protect((void *)(uintptr_t)eax, 0x00400000, 0);
  /* relift: cmp word ptr [esi + 0xabc], (int16_t)edi -> jne 0x1bbaf0 */
  display_assert((char *)0x002b8aa8, (char *)0x002b839c, 1124, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jle 0x1bbb18 */
  display_assert((char *)0x002b8a70, (char *)0x002b839c, 1125, 0);
  system_exit(0);
  /* cmp edx, eax -> je 0x1bbb52 */
  display_assert((char *)0x002b8a00, (char *)0x002b839c, 1126, 0);
  system_exit(0);
  SleepEx(0, 0);
  FUN_001bb970();
  /* test eax, eax -> jne 0x1bbc7f */
  /* test eax, eax -> je 0x1bbbb4 */
  display_assert((char *)0x002b8b8c, (char *)0x002b839c, 1149, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xac2], 0 -> je 0x1bbbde */
  display_assert((char *)0x002b8b68, (char *)0x002b839c, 1150, 0);
  system_exit(0);
  FUN_001ba9d0();
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bbc21 */
  /* cmp (int16_t)edi, 8 -> jl 0x1bbc41 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1606, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebx + 4], 0x20000 -> je 0x1bbc7f */
  display_assert((char *)0x002b8b40, (char *)0x002b839c, 1163, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bbca9 */
  display_assert((char *)0x002b8b28, (char *)0x002b839c, 1172, 0);
  system_exit(0);
  /* cmp (int16_t)edi, -1 -> je 0x1bbe91 */
  /* test eax, eax -> jne 0x1bbd32 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bbccc */
  /* cmp (int16_t)edi, 1 -> jl 0x1bbcec */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bbd0b */
  /* cmp (int16_t)eax, 1 -> jl 0x1bbd2b */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1bbb71 */
  /* test eax, eax -> je 0x1bbb71 */
  /* test (char)eax, (char)eax -> jne 0x1bbd5d */
  SwitchToThread();
  QueryPerformanceCounter((void *)0x004e5650);
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jle 0x1bbd7a */
  QueryPerformanceCounter((void *)0x004e5658);
  FUN_001155e0(0, 0);
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* mem[0x004e561c] = edx */
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jle 0x1bbdd3 */
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5620] = ecx */
  /* test edi, edi -> je 0x1bbddc */
  /* cmp edi, 1 -> jne 0x1bbe29 */
  /* test eax, eax -> jne 0x1bbe0b */
  acquire_read_request();
  /* test eax, eax -> je 0x1bbe1b */
  /* cmp edi, 1 -> jne 0x1bbb71 */
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1bbe91 */
  /* test eax, eax -> jne 0x1bbe4d */
  csprintf((char *)0x004e5510, (char *)0x002b8af0);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  WaitForSingleObject(0, 0);
  csmemset((void *)0x004e5610, 0, 36);
  QueryPerformanceCounter((void *)0x004e5678);
  FUN_001ba710();
  cache_copy_initialize_and_fill_with_garbage();
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1bc22b */
  QueryPerformanceCounter((void *)0x004e5638);
  cache_copy_initialize_read_data();
  FUN_001155c0(0, (char *)0x0028ce40, 56);
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  /* mem[0x004e5610] = ebx */
  cache_file_header_verify((void *)(uintptr_t)eax, (char *)0x002b8c40, 0);
  /* test (char)eax, (char)eax -> je 0x1bc205 */
  FUN_001bb8a0();
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1bc1db */
  /* relift: cmp dword ptr [esi + 0xa9c], edi -> jle 0x1bc1e1 */
  /* test (char)ebx, (char)ebx -> je 0x1bc1db */
  /* relift: cmp dword ptr [esi + 0x994], edi -> je 0x1bc03b */
  FUN_001ba9d0();
  /* relift: cmp word ptr [esi + 0xabc], -1 -> jne 0x1bc031 */
  /* test (char)eax, (char)eax -> jne 0x1bc086 */
  /* test (char)ebx, (char)ebx -> jne 0x1bc094 */
  display_assert((char *)0x00255ee8, (char *)0x002b839c, 875, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)0x004e5668);
  /* test (char)ebx, (char)ebx -> je 0x1bc09e */
  QueryPerformanceCounter((void *)0x004e5670);
  QueryPerformanceCounter((void *)0x004e5660);
  SetEvent((void *)(uintptr_t)eax);
  FUN_001d00b9();
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5624] = ecx */
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  /* mem[0x004e562c] = eax */
  /* test (char)eax, (char)eax -> je 0x1bc040 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* mem[0x004e5628] = eax */
  display_assert((char *)0x002b8c20, (char *)0x002b839c, 866, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc19d */
  display_assert((char *)0x002b8ba8, (char *)0x002b839c, 849, 0);
  system_exit(0);
  FUN_001bb970();
  FUN_001bbb60();
  WaitForSingleObject(0, 0);
  /* test eax, eax -> jne 0x1bbfe0 */
  /* relift: cmp dword ptr [esi + 0xa9c], edi -> jne 0x1bc205 */
  FUN_001bab60();
  FUN_001bb2d0();
  FUN_00115430(0);
  FUN_001bab60();
  CloseHandle(0);
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  /* mem[0x004e5630] = ecx */
  SetEvent((void *)(uintptr_t)edx);
  QueryPerformanceFrequency((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bc2b6 */
  display_assert((char *)0x002b8c54, (char *)0x002b839c, 487, 0);
  system_exit(0);
  /* mem[0x0032ea9c] = ecx */
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateThread((void *)0, 16384, (void *)0x001bbea0, (void *)0, 0, (void *)0);
  /* relift: cmp word ptr [0x4e9244], -1 -> je 0x1bc38a */
  display_assert((char *)0x002b8c68, (char *)0x002b8c98, 201, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)eax, (char *)0x002b8c98, 203);
  /* test edi, edi -> jne 0x1bc3d7 */
  display_assert((char *)0x002b8d30, (char *)0x002b8c98, 384, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 8], -1 -> jne 0x1bc3fd */
  display_assert((char *)0x002b8d14, (char *)0x002b8c98, 385, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1bc421 */
  display_assert((char *)0x002b8d08, (char *)0x002b8c98, 386, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc448 */
  display_assert((char *)0x00267900, (char *)0x002b8c98, 387, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc46f */
  display_assert((char *)0x002b8cf8, (char *)0x002b8c98, 388, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1bc493 */
  display_assert((char *)0x002b8ce4, (char *)0x002b8c98, 389, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 20);
  SleepEx(0, 0);
  SetLastError(0);
  /* test eax, eax -> jne 0x1bc547 */
  xapi_GetLastError();
  /* cmp eax, 8 -> je 0x1bc523 */
  /* cmp eax, 0x5aa -> je 0x1bc523 */
  /* cmp eax, 0x6f8 -> je 0x1bc523 */
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b8cc4);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  SleepEx(0, 0);
  SetLastError(0);
  /* test eax, eax -> je 0x1bc4d7 */
  /* relift: cmp byte ptr [esi], 0 -> jne 0x1bc578 */
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> jne 0x1bc578 */
  /* relift: cmp byte ptr [esi], 0 -> je 0x1bc560 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc58c */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc5ac */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc5d2 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc5f2 */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* test dl, dl -> je 0x1bc616 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc5c6 */
  /* test (char)ebx, (char)ebx -> jne 0x1bc5c4 */
  /* relift: cmp word ptr [0x4e9244], -1 -> jne 0x1bc64a */
  display_assert((char *)0x002b8d90, (char *)0x002b8c98, 645, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc65c */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc67c */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* relift: cmp byte ptr [eax], 0 -> jne 0x1bc685 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc650 */
  /* relift: cmp word ptr [0x4e9222], -1 -> je 0x1bc6ec */
  tag_name_strip_path((char *)(uintptr_t)eax);
  csstrcmp((char *)0x004e9224, (char *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x1bc6ec */
  /* test (char)eax, (char)eax -> jne 0x1bc719 */
  display_assert((char *)0x002b8dc0, (char *)0x002b8c98, 971, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc72b */
  /* cmp (int16_t)esi, 6 -> jl 0x1bc74b */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc76b */
  /* cmp (int16_t)esi, 6 -> jl 0x1bc78b */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc7ab */
  /* cmp (int16_t)esi, 6 -> jl 0x1bc7cb */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc7eb */
  /* cmp (int16_t)esi, 6 -> jl 0x1bc80b */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1181, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 1 -> jg 0x1bc817 */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b8e24);
  SetEvent((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bc88a */
  display_assert((char *)0x002b8e88, (char *)0x002b8c98, 1336, 0);
  system_exit(0);
  /* relift: cmp eax, dword ptr [esi + 0x14] -> je 0x1bc8b6 */
  display_assert((char *)0x002b8e5c, (char *)0x002b8c98, 1337, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc8dd */
  display_assert((char *)0x002b8e38, (char *)0x002b8c98, 1338, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1bc91a */
  display_assert((char *)0x002b8e88, (char *)0x002b8c98, 1354, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc950 */
  display_assert((char *)0x002b8ea4, (char *)0x002b8c98, 1355, 0);
  system_exit(0);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b8eb8);
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  D3DResource_BlockUntilNotBusy((void *)(uintptr_t)eax);
  D3DResource_Register((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  D3DResource_BlockUntilNotBusy((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [0x4e9244], -1 -> je 0x1bc9d8 */
  FUN_001bc620();
  FUN_001bc5c0();
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bca1d */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x4e9244], -1 -> jne 0x1bca55 */
  display_assert((char *)0x002b8d90, (char *)0x002b8c98, 263, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bca7c */
  display_assert((char *)0x00267900, (char *)0x002b8c98, 266, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1bcaa3 */
  display_assert((char *)0x002b8ed4, (char *)0x002b8c98, 267, 0);
  system_exit(0);
  /* test eax, eax -> jge 0x1bcaca */
  display_assert((char *)0x002b8ec8, (char *)0x002b8c98, 270, 0);
  system_exit(0);
  /* test edi, 0x1ff -> je 0x1bcadc */
  csmemset((void *)(uintptr_t)esi, 0, 20);
  SetEvent((void *)(uintptr_t)eax);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bcb44 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bcb64 */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b8eb8);
  CreateFileA((char *)(uintptr_t)edx, 0x80000000, 0, 0, 0, 0, 0);
  /* cmp esi, -1 -> je 0x1bcc01 */
  ReadFile(0, (void *)(uintptr_t)edi, 2048, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1bcbfb */
  /* relift: cmp dword ptr [ebp - 4], 0x800 -> jne 0x1bcbfb */
  cache_file_header_verify((void *)(uintptr_t)edi, (char *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1bcbfb */
  CloseHandle(0);
  FUN_001bc3b0();
  FUN_001bc3b0();
  SleepEx(0, 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bcc6e */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bcc8e */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x1bcc9d */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bcc62 */
  /* test (char)ebx, (char)ebx -> jne 0x1bcc53 */
  /* test eax, eax -> jle 0x1bcce5 */
  D3DResource_Register((void *)(uintptr_t)eax, (void *)0);
  /* cmp eax, ecx -> jl 0x1bccc3 */
  /* test eax, eax -> jle 0x1bcd08 */
  /* cmp eax, edx -> jl 0x1bccf0 */
  D3DResource_BlockUntilNotBusy((void *)(uintptr_t)edi);
  D3DResource_IsBusy((void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1bcd5d */
  display_assert((char *)0x002b8f1c, (char *)0x002b8c98, 517, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x1bcd24 */
  /* test eax, eax -> jle 0x1bcdb7 */
  D3DResource_BlockUntilNotBusy((void *)(uintptr_t)edi);
  D3DResource_IsBusy((void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1bcdac */
  display_assert((char *)0x002b8ef0, (char *)0x002b8c98, 530, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x1bcd73 */
  /* test eax, eax -> jle 0x1bcdf5 */
  D3DResource_Register((void *)(uintptr_t)eax, (void *)0);
  /* cmp eax, ecx -> jl 0x1bcdd3 */
  /* test eax, eax -> jle 0x1bce22 */
  D3DResource_Register((void *)(uintptr_t)eax, (void *)0);
  /* cmp eax, ecx -> jl 0x1bce00 */
  /* test eax, eax -> jle 0x1bce6a */
  D3DResource_BlockUntilNotBusy((void *)(uintptr_t)edx);
  /* cmp eax, ecx -> jl 0x1bce50 */
  /* test eax, eax -> jle 0x1bce8f */
  D3DResource_BlockUntilNotBusy((void *)(uintptr_t)edx);
  /* cmp eax, ecx -> jl 0x1bce75 */
  /* cmp (int16_t)eax, 0x14 -> jge 0x1bcee7 */
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002b8e24);
  DeleteFileA((char *)(uintptr_t)eax);
  SetLastError(0);
  /* test (char)eax, (char)eax -> jne 0x1bcf2d */
  display_assert((char *)0x002b8dc0, (char *)0x002b8c98, 933, 0);
  system_exit(0);
  cache_copy_get_status();
  /* cmp eax, 4 -> ja 0x1bcf77 */
  FUN_001bc760(0);
  display_assert((char *)0, (char *)0x002b8c98, 962, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 6 -> jl 0x1bcfe6 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  GetLocalTime((void *)0);
  SystemTimeToFileTime((void *)(uintptr_t)ecx, (void *)(uintptr_t)edi);
  SetFileTime(0, (void *)(uintptr_t)edi, (void *)0, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bd039 */
  /* cmp (int16_t)esi, 6 -> jl 0x1bd059 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002b8e24);
  FUN_001d18aa();
  FUN_001bc3b0();
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> jne 0x1bd0ea */
  /* test (char)eax, (char)eax -> je 0x1bd0d0 */
  /* test (char)eax, (char)eax -> je 0x1bd133 */
  cache_file_header_verify((void *)(uintptr_t)esi, (char *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> jne 0x1bd19f */
  csmemset((void *)(uintptr_t)esi, 0, 2048);
  csmemset((void *)(uintptr_t)edx, 0, 0);
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b8f4c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bd176 */
  /* cmp (int16_t)eax, 6 -> jl 0x1bd196 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bd1be */
  /* cmp (int16_t)esi, 6 -> jl 0x1bd1de */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  crt_stricmp((char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bd207 */
  /* cmp (int16_t)esi, 6 -> jl 0x1bd1b3 */
  display_assert((char *)0, (char *)0x002b8c98, 1121, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edi, word ptr [ebp - 8] -> jg 0x1bd367 */
  /* relift: cmp word ptr [0x4e9244], (int16_t)edi -> je 0x1bd355 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bd2a8 */
  /* cmp (int16_t)edi, 6 -> jl 0x1bd2c8 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bd2d3 */
  /* cmp (int16_t)edi, 6 -> jl 0x1bd2f3 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1181, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 1 -> jg 0x1bd300 */
  /* relift: cmp eax, dword ptr [ebp + 8] -> jle 0x1bd355 */
  /* cmp (int16_t)esi, -1 -> je 0x1bd34c */
  FUN_001bc7e0(0);
  FUN_001bc7e0(0);
  /* cmp ecx, eax -> jl 0x1bd34c */
  FUN_001d0669();
  /* test eax, eax -> jle 0x1bd352 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 8] -> jle 0x1bd290 */
  /* relift: cmp word ptr [0x4e9244], (int16_t)esi -> jne 0x1bd390 */
  display_assert((char *)0x002b8f78, (char *)0x002b8c98, 1149, 0);
  system_exit(0);
  FUN_001d00b9();
  /* cmp eax, 0xc0 -> je 0x1bd3a3 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bd3d2 */
  /* cmp (int16_t)edi, 0x200 -> jl 0x1bd3f2 */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x1bd41f */
  /* test (char)ecx, (char)ecx -> jne 0x1bd41f */
  /* test esi, esi -> je 0x1bd41d */
  /* relift: cmp dl, byte ptr [eax + 0x1c] -> jbe 0x1bd41f */
  /* relift: cmp ecx, dword ptr [eax + 8] -> jbe 0x1bd41f */
  /* cmp (int16_t)edi, 0x200 -> jl 0x1bd3c6 */
  /* test esi, esi -> je 0x1bd3a3 */
  /* cmp (int16_t)eax, 6 -> jl 0x1bd464 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  display_assert((char *)0x002b8fb4, (char *)0x002b8c98, 1276, 0);
  system_exit(0);
  FUN_001bc3b0();
  FUN_001bd1b0();
  display_assert((char *)0x002b8fe4, (char *)0x002b8c98, 214, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1bd52a */
  display_assert((char *)0x00265d1c, (char *)0x002b8c98, 215, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x4e9244], -1 -> je 0x1bd554 */
  display_assert((char *)0x002b8c68, (char *)0x002b8c98, 217, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> jne 0x1bd57a */
  display_assert((char *)0x002b8fcc, (char *)0x002b8c98, 218, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 16384);
  /* cmp (int16_t)esi, 6 -> jl 0x1bd5c1 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)ecx, 0);
  FUN_001d90e0();
  FUN_001bcea0(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1bd62b */
  /* cmp (int16_t)ebx, 6 -> jl 0x1bd64b */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b8e24);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1bd672 */
  /* cmp (int16_t)ebx, 6 -> jl 0x1bd692 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1181, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, 1 -> jg 0x1bd6a1 */
  CreateFileA((char *)(uintptr_t)eax, 0xc0000000, 0, 0, 0, 0x60000000, 0);
  xapi_GetLastError();
  /* cmp eax, 0xb7 -> jne 0x1bd708 */
  GetFileSize(0, (void *)0);
  /* relift: cmp eax, dword ptr [ebp - 0x10] -> jne 0x1bd708 */
  /* test (char)eax, (char)eax -> jne 0x1bd71a */
  FUN_001bcea0(0);
  FUN_001bc3b0();
  /* test (char)eax, (char)eax -> jne 0x1bd76a */
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> jne 0x1bd76a */
  /* test (char)eax, (char)eax -> je 0x1bd750 */
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1bd79a */
  SetEndOfFile(0);
  /* test eax, eax -> je 0x1bd79a */
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b9024);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  CloseHandle(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1bd7fd */
  /* cmp (int16_t)ebx, 6 -> jl 0x1bd81d */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  cache_file_read_header_into_slot(0);
  csstrcmp((char *)(uintptr_t)edi, (char *)0);
  /* test eax, eax -> je 0x1bd83c */
  FUN_001bcb80((char *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1bd863 */
  /* relift: cmp eax, dword ptr [ebp - 0x8c8] -> jne 0x1bd863 */
  /* test (char)eax, (char)eax -> jne 0x1bd879 */
  csmemset((void *)(uintptr_t)ecx, 0, 0);
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b8ff4);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  tag_name_strip_path((char *)(uintptr_t)eax);
  FUN_001bd1b0();
  tag_name_strip_path((char *)(uintptr_t)esi);
  tag_name_strip_path((char *)(uintptr_t)esi);
  FUN_001bd1b0();
  /* cmp (int16_t)eax, 0xffff -> jne 0x1bd9f7 */
  FUN_001bcb80((char *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1bda00 */
  FUN_001ba250();
  xbox_texture_cache_steal_memory(edi);
  FUN_001bd210(ecx, 0);
  FUN_001bc720(0);
  csmemset((void *)(uintptr_t)eax, 0, 0);
  csstrncpy((char *)0x004e9224, (char *)(uintptr_t)ebx, 31);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002b8eb8);
  error(0, (char *)0x002b9070);
  FUN_001bc7e0(0);
  FUN_001bc7a0(0);
  FUN_001ba2f0(0, 0, 0, 0, (char *)0);
  error(0, (char *)0x002b904c);
  /* test (char)eax, (char)eax -> je 0x1bda1c */
  display_error_damaged_media();
  /* test (char)eax, (char)eax -> jne 0x1bda59 */
  display_assert((char *)0x002b8dc0, (char *)0x002b8c98, 980, 0);
  system_exit(0);
  FUN_001baf50();
  xbox_texture_cache_return_memory();
  FUN_001bcfb0(0);
  cache_file_read_header_into_slot(0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  /* mem[0x004e9248] = eax */
  display_assert((char *)0x002b90ac, (char *)0x002b8c98, 1202, 0);
  system_exit(0);
  CreateThread((void *)0, 16384, (void *)0x001bd3a0, (void *)0, 0, (void *)0);
  /* mem[0x004e924c] = eax */
  display_assert((char *)0x002b9090, (char *)0x002b8c98, 1206, 0);
  system_exit(0);
  debug_malloc(16384, 0, (char *)0x002b8c98, 183);
  /* mem[0x004e9250] = eax */
  display_assert((char *)0x002b90cc, (char *)0x002b8c98, 184, 0);
  system_exit(0);
  FUN_001bda90();
  FUN_001bd5f0();
  XPhysicalAlloc(0x00345000, 0x00061000, 0, 0);
  /* mem[0x004e9254] = eax */
  display_assert((char *)0x002b91b8, (char *)0x002b9214, 46, 0);
  system_exit(0);
  XPhysicalAlloc(0x01600000, 0x003a6000, 0, 0);
  /* mem[0x004e9258] = eax */
  display_assert((char *)0x002b9158, (char *)0x002b9214, 50, 0);
  system_exit(0);
  XPhysicalAlloc(0x01600000, 0, 0, 1028);
  /* mem[0x004e925c] = eax */
  display_assert((char *)0x002b9120, (char *)0x002b9214, 55, 0);
  system_exit(0);
  XPhysicalAlloc(0x00400000, 0, 0, 0);
  /* mem[0x004e9260] = eax */
  display_assert((char *)0x002b90e8, (char *)0x002b9214, 58, 0);
  system_exit(0);
  /* relift: MmQueryAddressProtect(); */
  /* cmp eax, 4 -> je 0x1bdc9a */
  display_assert((char *)0x002b9240, (char *)0x002b9214, 77, 0);
  system_exit(0);
  /* cmp esi, edx -> jb 0x1bdc72 */
  /* cmp esi, eax -> jae 0x1bdcfe */
  /* relift: MmQueryAddressProtect(); */
  /* cmp eax, 4 -> je 0x1bdce8 */
  display_assert((char *)0x002b9240, (char *)0x002b9214, 86, 0);
  system_exit(0);
  /* cmp esi, ecx -> jb 0x1bdcc0 */
  /* test eax, eax -> je 0x1bdd0f */
  /* relift: MmFreeContiguousMemory(); */
  /* test eax, eax -> je 0x1bdd1e */
  /* relift: MmFreeContiguousMemory(); */
  /* test eax, eax -> je 0x1bdd2d */
  /* relift: MmFreeContiguousMemory(); */
  /* test eax, eax -> je 0x1bdd3c */
  /* relift: MmFreeContiguousMemory(); */
  tag_get(0x736e6421, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 72);
  /* relift: cmp word ptr [edi + 0x2c], (int16_t)esi -> jle 0x1bddf8 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 124);
  sound_cache_request_sound((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0x2c] -> jl 0x1bddd0 */
  /* cmp eax, ecx -> jl 0x1bddb0 */
  /* test eax, eax -> jle 0x1bde7e */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  FUN_001bdd80(0);
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)eax, 0, 0);
  /* cmp eax, ecx -> jl 0x1bde22 */
  data_dispose((void *)(uintptr_t)eax);
  lruv_cache_dispose((void *)(uintptr_t)ecx);
  /* mem[0x004e936c] = 0 */
  data_delete_all((void *)(uintptr_t)eax);
  lruv_idle((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [0x5054ea], 0 -> je 0x1bdf08 */
  display_assert((char *)0x002b9260, (char *)0x002b9288, 148, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1bdf3e */
  display_assert((char *)0x002b92b0, (char *)0x002b9288, 158, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1be07e */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x1bdfee */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  tag_get_name(0);
  csprintf((char *)0x005ab100, (char *)0x002b9320);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x1be06c */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  tag_get_name(0);
  csprintf((char *)0x005ab100, (char *)0x002b92d0);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  lruv_block_delete((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1be0cd */
  error(0, (char *)0x002b9394);
  /* test (char)eax, (char)eax -> jne 0x1be0f4 */
  display_assert((char *)0x002b936c, (char *)0x002b9288, 263, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp (char)ecx, 0xff -> jae 0x1be128 */
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1be167 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1be19f */
  /* test (char)ecx, (char)ecx -> jne 0x1be19f */
  /* test (char)ecx, (char)ecx -> jne 0x1be19f */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x1be1d7 */
  /* test (char)eax, (char)eax -> je 0x1be216 */
  tag_get_name(0);
  csprintf((char *)0x005ab100, (char *)0x002b93e0);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edx + 0x2c], edi -> je 0x1be23e */
  display_assert((char *)0x002b93a8, (char *)0x002b9288, 324, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get_name(0);
  crt_sprintf((char *)0x004e9268, (char *)0x002b9424);
  FUN_0011de10((void *)(uintptr_t)ecx, eax);
  /* cmp edi, -1 -> je 0x1be361 */
  lruv_block_get_address((void *)(uintptr_t)edx, 0);
  data_new_datum((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x002b94cc, (char *)0x002b9288, 368, 0);
  system_exit(0);
  cache_file_read(0, 0, edx, 0, (char *)(uintptr_t)eax, 0);
  system_milliseconds();
  /* cmp eax, 0x2710 -> jbe 0x1be3cd */
  terminal_output((void *)(uintptr_t)edx, (char *)0x002b9488, (char *)0);
  error(0, (char *)0x002b9440);
  terminal_output((void *)(uintptr_t)eax, (char *)0x002b9488, (char *)0);
  FUN_0011db90((char *)0x002b942c, (char *)(uintptr_t)esi, 0, (void *)(uintptr_t)ecx, (void *)0x0018ef30, (void *)0x001be270);
  system_milliseconds();
  /* mem[0x004e9374] = eax */
  data_new((char *)0x002b957c, 512, 12);
  /* mem[0x004e9368] = eax */
  display_assert((char *)0x002b9554, (char *)0x002b9288, 69, 0);
  system_exit(0);
  lruv_new(0x002b9540, 1024, 12, 512, (void *)0x001be1b0, (void *)0x001be170);
  /* mem[0x004e9370] = eax */
  display_assert((char *)0x002b9520, (char *)0x002b9288, 73, 0);
  system_exit(0);
  FUN_001bdd70();
  /* mem[0x004e936c] = eax */
  display_assert((char *)0x002b94f8, (char *)0x002b9288, 76, 0);
  system_exit(0);
  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1be4df */
  /* test (char)ecx, (char)ecx -> jne 0x1be4cf */
  /* test (char)ecx, (char)ecx -> jne 0x1be4cf */
  FUN_001bdf60();
  data_iterator_next((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x1be4b5 */
  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1be52e */
  FUN_001bdf60();
  data_iterator_next((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x1be515 */
  data_make_invalid((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1be588 */
  display_assert((char *)0x002b9604, (char *)0x002b9288, 194, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1be5af */
  display_assert((char *)0x002b95f0, (char *)0x002b9288, 196, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1be5d9 */
  display_assert((char *)0x002b95d4, (char *)0x002b9288, 198, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x2c], -1 -> jne 0x1be5e8 */
  /* test (char)ebx, (char)ebx -> je 0x1be5e8 */
  FUN_001be2b0((void *)0);
  /* cmp eax, -1 -> je 0x1be6a3 */
  lruv_debug_to_file((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> jne 0x1be636 */
  SwitchToThread();
  /* test (char)eax, (char)eax -> jne 0x1be604 */
  /* test (char)eax, (char)eax -> jne 0x1be649 */
  /* test (char)eax, (char)eax -> je 0x1be69a */
  /* test (char)eax, (char)eax -> je 0x1be671 */
  error(0, (char *)0x002b95c0);
  /* relift: cmp byte ptr [edi + 4], 0xff -> jb 0x1be697 */
  display_assert((char *)0x002b9588, (char *)0x002b9288, 236, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1be91c */
  lruv_cache_get_page_usage((void *)(uintptr_t)edx, (unsigned char *)(uintptr_t)ecx);
  /* test dl, (char)eax -> je 0x1be8fc */
  FUN_001be6b0();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  data_dispose((void *)(uintptr_t)eax);
  lruv_cache_dispose((void *)(uintptr_t)ecx);
  data_delete_all((void *)(uintptr_t)eax);
  lruv_idle((void *)(uintptr_t)eax);
  display_assert((char *)0x002b96a8, (char *)0x002b96d8, 157, 0);
  system_exit(0);
  tag_get('mtib', 0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  /* cmp eax, -1 -> je 0x1bea15 */
  lruv_block_delete((void *)(uintptr_t)eax, 0);
  FUN_001bdd60();
  display_assert((char *)0x002b9730, (char *)0x002b96d8, 319, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1beab7 */
  display_assert((char *)0x002b9704, (char *)0x002b96d8, 320, 0);
  system_exit(0);
  lruv_resize((void *)(uintptr_t)edx, 0);
  physical_memory_protect((void *)(uintptr_t)esi, esi, 0);
  physical_memory_protect((void *)(uintptr_t)ebx, 0x00104000, 0);
  physical_memory_protect((void *)(uintptr_t)eax, 0x00104000, 0);
  /* test (char)eax, (char)eax -> jne 0x1beb39 */
  display_assert((char *)0x002b9748, (char *)0x002b96d8, 345, 0);
  system_exit(0);
  lruv_resize((void *)(uintptr_t)eax, 1408);
  FUN_001bdd60();
  physical_memory_protect((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get_name(0);
  /* cmp (int16_t)esi, 0x12 -> jl 0x1bebd4 */
  display_assert((char *)0x00264ad4, (char *)0x002b96d8, 481, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi*4 + 0x2b9618], -1 -> jne 0x1bec01 */
  display_assert((char *)0x002b9774, (char *)0x002b96d8, 482, 0);
  system_exit(0);
  /* relift: test byte ptr [ebp + 0xc], 0x20 -> je 0x1bec1c */
  /* cmp (int16_t)esi, 0xa -> je 0x1bec13 */
  /* cmp (int16_t)esi, 0xb -> jne 0x1bec1c */
  /* cmp (int16_t)esi, 0x12 -> jl 0x1bec64 */
  display_assert((char *)0x00264ad4, (char *)0x002b96d8, 518, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi*4 + 0x2b9660], -1 -> jne 0x1bec91 */
  display_assert((char *)0x002b9774, (char *)0x002b96d8, 519, 0);
  system_exit(0);
  /* relift: test byte ptr [ebp + 0xc], 0x20 -> je 0x1becac */
  /* cmp (int16_t)esi, 0xa -> je 0x1beca3 */
  /* cmp (int16_t)esi, 0xb -> jne 0x1becac */
  FUN_00183290((void *)(uintptr_t)eax);
  FUN_00183290((void *)(uintptr_t)ecx);
  D3DDevice_IsBusy();
  D3DDevice_KickPushBuffer();
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  D3DResource_Register((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_KickPushBuffer();
  D3DDevice_IsBusy();
  lruv_cache_dispose_all((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1bed7c */
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x1bed7c */
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1bedb0 */
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x1bedb0 */
  /* relift: cmp dword ptr [edx + 0x24], esi -> je 0x1bedfc */
  display_assert((char *)0x002b9788, (char *)0x002b96d8, 391, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)edx, 0);
  /* cmp esi, ebx -> jne 0x1bee57 */
  display_assert((char *)0x00263768, (char *)0x002b96d8, 532, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0x1bee7b */
  display_assert((char *)0x0026870c, (char *)0x002b96d8, 533, 0);
  system_exit(0);
  /* test (char)eax, 0x10 -> je 0x1beee0 */
  FUN_001bec30(eax, eax);
  bitmap_mipmap_get_row_pitch((void *)(uintptr_t)esi, 0);
  D3DResource_Register((void *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  FUN_00108db0(eax);
  FUN_00108db0(0);
  FUN_00108db0(0);
  bitmap_format_to_d3d_linear_format(eax, edx);
  FUN_00183120((void *)0);
  D3DResource_Register((void *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  data_new((char *)0x002b983c, 1408, 32);
  /* mem[0x004ea978] = eax */
  display_assert((char *)0x002b9818, (char *)0x002b96d8, 98, 0);
  system_exit(0);
  lruv_new(0x002b9804, 1408, 14, 1408, (void *)0x001bed90, (void *)0x001bed50);
  /* mem[0x004ea980] = eax */
  display_assert((char *)0x002b97e0, (char *)0x002b96d8, 102, 0);
  system_exit(0);
  FUN_001bdd60();
  /* mem[0x004ea97c] = eax */
  display_assert((char *)0x002b97b8, (char *)0x002b96d8, 105, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1bf159 */
  display_assert((char *)0x002b9704, (char *)0x002b96d8, 133, 0);
  system_exit(0);
  D3DDevice_KickPushBuffer();
  D3DDevice_IsBusy();
  lruv_cache_dispose_all((void *)(uintptr_t)eax);
  data_make_invalid((void *)(uintptr_t)ecx);
  FUN_00183290((void *)(uintptr_t)esi);
  /* cmp eax, ecx -> jg 0x1bf19c */
  FUN_0011de10((void *)(uintptr_t)eax, eax);
  /* cmp edi, -1 -> je 0x1bf258 */
  lruv_block_get_address((void *)(uintptr_t)ecx, 0);
  data_new_datum((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, edi -> je 0x1bf217 */
  display_assert((char *)0x002b984c, (char *)0x002b96d8, 431, 0);
  system_exit(0);
  xbox_texture_cache_setup_d3d_texture((void *)0, (void *)0);
  cache_file_read(0, 0, edx, 0, (char *)(uintptr_t)eax, edx);
  lruv_cache_get_page_usage((void *)(uintptr_t)ecx, (unsigned char *)(uintptr_t)eax);
  /* test (char)ecx, dl -> je 0x1bf3ef */
  FUN_001bef80();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* cmp ebx, 3 -> jl 0x1bf300 */
  /* test (char)eax, (char)eax -> je 0x1bf55c */
  data_iterator_new((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  data_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bf45b */
  /* relift: cmp dword ptr [eax + 0x20], -1 -> je 0x1bf44b */
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0x1bf437 */
  FUN_00091ef0((void *)0x004e9378, 0, (void *)0x001becc0);
  interface_get_tag_index(0);
  draw_string_set_tab_stops((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x1bf4a5 */
  FUN_0019B7E0();
  /* test esi, esi -> jl 0x1bf55c */
  lruv_block_touched((void *)(uintptr_t)eax, 0);
  tag_get_name(0);
  FUN_00183290((void *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b9874);
  draw_string_set_color((void *)(uintptr_t)ecx);
  rasterizer_text_draw((void *)(uintptr_t)eax, (void *)0, (void *)0, 0, (char *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1bf5aa */
  display_assert((char *)0x002b9604, (char *)0x002b96d8, 210, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x24], -1 -> jne 0x1bf5d0 */
  /* test (char)ebx, (char)ebx -> je 0x1bf5d0 */
  xbox_texture_cache_request((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> je 0x1bf697 */
  datum_get((void *)(uintptr_t)ecx, 0);
  lruv_debug_to_file((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1bf640 */
  /* test (char)eax, (char)eax -> jne 0x1bf647 */
  /* test (char)eax, (char)eax -> je 0x1bf62b */
  tag_get_name(0);
  console_warning((char *)0x00257984);
  cache_files_io_request_enable(edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c4990 */
void FUN_001c4990(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 774, 0);
  system_exit(0);
  /* test esi, esi -> jl 0x1c49e4 */
  /* cmp esi, 2 -> jl 0x1c4a04 */
  display_assert((char *)0x002ba878, (char *)0x002ba8e8, 777, 0);
  system_exit(0);
  /* test edi, edi -> jl 0x1c4a0d */
  /* cmp edi, 9 -> jl 0x1c4a2d */
  display_assert((char *)0x002ba838, (char *)0x002ba8e8, 778, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x1c4a39 */
  /* cmp eax, 0x64 -> jl 0x1c4a59 */
  display_assert((char *)0x002ba7e8, (char *)0x002ba8e8, 779, 0);
  system_exit(0);
  ustrlen((void *)(uintptr_t)eax);
  /* cmp eax, 0x80 -> jb 0x1c4a8c */
  display_assert((char *)0x002bb7c0, (char *)0x002ba8e8, 781, 0);
  system_exit(0);
  FUN_001c3e40();
  /* test (char)eax, (char)eax -> je 0x1c4d80 */
  /* test eax, eax -> je 0x1c4d8f */
  /* relift: cmp word ptr [eax], 0 -> je 0x1c4d8f */
  ustrcmp((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1c4d8f */
  /* test esi, esi -> jne 0x1c4d67 */
  wide_to_ascii((wchar_t *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  FUN_001d2f22();
  /* test eax, eax -> jne 0x1c4d4f */
  display_assert((char *)0x002bb7a0, (char *)0x002ba8e8, 835, 0);
  system_exit(0);
  snprintf((char *)(uintptr_t)edx, 255, (char *)0x0025bf84);
  snprintf((char *)(uintptr_t)eax, 255, (char *)0x0025bf84);
  FUN_001d21f2();
  /* cmp (char)ebx, 1 -> jne 0x1c4d25 */
  csstrncpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 255);
  crt_strstr((char *)(uintptr_t)edx, (char *)0x002bb788);
  /* test eax, eax -> je 0x1c4b6a */
  FUN_001c0720();
  csstrcat((char *)(uintptr_t)eax, (char *)(uintptr_t)eax, 0);
  FUN_001c0720();
  snprintf((char *)(uintptr_t)edx, 255, (char *)0x0025bf84);
  FUN_001d21f2();
  /* cmp (char)ebx, 1 -> jne 0x1c4d25 */
  FUN_001d3185();
  /* test eax, eax -> je 0x1c4cb9 */
  error(0, (char *)0x002bb728);
  csstrncpy((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx, 255);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)esi, 127);
  FUN_001c4030();
  /* test (char)eax, (char)eax -> jne 0x1c4d8f */
  error(0, (char *)0x002bb6e0);
  /* test (char)ebx, (char)ebx -> jne 0x1c4d8f */
  FUN_001d3185();
  /* test eax, eax -> je 0x1c4d8f */
  error(0, (char *)0x002bb680);
  error(0, (char *)0x002bb608);
  error(0, (char *)0x002bb4f4);
  error(0, (char *)0x002bb5e4);
  display_assert((char *)0x002bb8a0, (char *)0x002ba8e8, 909, 0);
  system_exit(0);
  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 919, 0);
  system_exit(0);
  /* test ebx, ebx -> jl 0x1c4ee9 */
  /* cmp ebx, 9 -> jge 0x1c4ee9 */
  /* test edi, edi -> jl 0x1c4ee9 */
  /* cmp edi, 0x64 -> jge 0x1c4ee9 */
  FUN_001c3e40();
  /* test (char)eax, (char)eax -> je 0x1c4ed1 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1c4e91 */
  csstrncpy((char *)(uintptr_t)esi, (char *)(uintptr_t)ecx, 255);
  crt_strstr((char *)(uintptr_t)esi, (char *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1c4eb6 */
  /* cmp (int16_t)eax, 1 -> jne 0x1c4e9e */
  error(0, (char *)0x002bb880);
  error(0, (char *)0x002bb84c);
  error(0, (char *)0x002bb800);
  error(0, (char *)0x002bb430);
  FUN_001c3a30();
  FUN_001c3c40();
  FUN_001c3250();
  /* test (char)eax, (char)eax -> je 0x1c4ffa */
  /* test esi, esi -> jne 0x1c4ff5 */
  wide_to_ascii((wchar_t *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  FUN_001d3254();
  /* cmp edi, -1 -> je 0x1c4fe2 */
  /* cmp ebx, 0x64 -> jge 0x1c4fc9 */
  FUN_001d3185();
  /* test eax, eax -> je 0x1c4fb8 */
  error(0, (char *)0x002bb8ac);
  FUN_001d335b();
  /* test (char)eax, (char)eax -> jne 0x1c4f90 */
  FUN_001d33a2(0);
  /* test eax, eax -> jne 0x1c4fe2 */
  error(0, (char *)0x002ba984);
  FUN_001c3a30();
  FUN_001c3c40();
  FUN_001c3320();
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c53cf */
  FUN_001c3250();
  /* test (char)eax, (char)eax -> je 0x1c53c0 */
  /* cmp edi, ebx -> jne 0x1c53b9 */
  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  FUN_001d3254();
  /* relift: cmp dword ptr [ebp - 4], 0x64 -> jge 0x1c5389 */
  snprintf((char *)(uintptr_t)eax, 255, (char *)0);
  /* test eax, eax -> jle 0x1c51c6 */
  file_reference_create_from_path((void *)(uintptr_t)edx, (char *)(uintptr_t)ecx, ebx);
  /* test eax, eax -> je 0x1c51c6 */
  file_exists((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c51c6 */
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edx, 127);
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c5350 */
  file_read((void *)(uintptr_t)eax, 512, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c5327 */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)eax, (void *)(uintptr_t)esi, 20);
  /* test eax, eax -> jne 0x1c528c */
  snprintf((char *)(uintptr_t)edx, 255, (char *)0x0025bf84);
  /* test eax, eax -> jle 0x1c5230 */
  file_reference_create_from_path((void *)(uintptr_t)ecx, (char *)(uintptr_t)eax, ebx);
  /* test eax, eax -> je 0x1c5230 */
  file_exists((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c5230 */
  unicode_sprintf((wchar_t *)(uintptr_t)edx, 255, (wchar_t *)0x002bb9d0);
  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 512);
  error(0, (char *)(uintptr_t)eax);
  error(0, (char *)0x002bb000);
  crc_new((void *)(uintptr_t)edx);
  crc_checksum_buffer((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)esi, 0);
  /* test eax, eax -> jne 0x1c5336 */
  error(0, (char *)0x002bb980);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 20);
  file_set_position((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c5336 */
  file_write();
  /* test (char)eax, (char)eax -> je 0x1c5336 */
  error(0, (char *)0x002bb948);
  file_close((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1c535f */
  error(0, (char *)0x002bb8d8);
  FUN_001c33b0();
  FUN_001d335b();
  /* test (char)eax, (char)eax -> jne 0x1c50a1 */
  FUN_001d33a2(0);
  /* test eax, eax -> jne 0x1c53a2 */
  error(0, (char *)0x002ba984);
  FUN_001c3a30();
  FUN_001c3c40();
  FUN_001c3320();
  release_mutex((void *)(uintptr_t)edx);
  /* cmp (int16_t)eax, 0xffff -> je 0x1c540e */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1c5423 */
  /* cmp (int16_t)eax, 4 -> jge 0x1c5423 */
  /* relift: cmp word ptr [ebp + 0xc], 2 -> jae 0x1c5423 */
  /* test eax, eax -> je 0x1c5423 */
  /* test eax, eax -> jne 0x1c5443 */
  display_assert((char *)0x002bba90, (char *)0x002ba8e8, 236, 0);
  system_exit(0);
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c553a */
  /* test (char)eax, (char)eax -> je 0x1c546c */
  FUN_001c5010();
  FUN_001c3610();
  take_mutex((void *)(uintptr_t)ecx, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c5511 */
  FUN_001c3430();
  /* test (char)eax, (char)eax -> je 0x1c5500 */
  /* relift: cmp word ptr [edx], (int16_t)ebx -> jbe 0x1c54f8 */
  /* relift: cmp ebx, dword ptr [ebp + 8] -> jge 0x1c54f8 */
  FUN_001c35a0();
  /* test (char)eax, (char)eax -> je 0x1c54f8 */
  /* cmp eax, edx -> jne 0x1c54ed */
  /* test (char)eax, (char)eax -> jne 0x1c54ed */
  FUN_001c3710();
  /* cmp edi, ecx -> jl 0x1c54a8 */
  FUN_001c3500();
  release_mutex((void *)(uintptr_t)edx);
  error(0, (char *)0x002bae8c);
  release_mutex((void *)(uintptr_t)eax);
  error(0, (char *)0x002bba64);
  /* cmp (int16_t)ebx, 2 -> jae 0x1c5590 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1c5589 */
  /* cmp (int16_t)eax, 4 -> jge 0x1c5590 */
  /* test eax, eax -> jne 0x1c55b0 */
  display_assert((char *)0x002bbd20, (char *)0x002ba8e8, 332, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c55be */
  FUN_001c5010();
  saved_game_perform_file_system_checks();
  display_error_abort_to_dashboard_deferred(33, 0);
  /* test (int16_t)esi, (int16_t)esi -> jne 0x1c58d8 */
  FUN_001c3610();
  /* cmp esi, 0x64 -> jge 0x1c58bc */
  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  FUN_001d2f22();
  /* test eax, eax -> jne 0x1c58a3 */
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edx, 0);
  snprintf((char *)(uintptr_t)edx, 255, (char *)0x0025bf84);
  snprintf((char *)(uintptr_t)ecx, 255, (char *)0x0025bf84);
  FUN_001c0cd0(0);
  /* relift: cmp word ptr [ebp - 0x14], -1 -> je 0x1c5867 */
  file_reference_create_from_path((void *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1c5851 */
  FUN_0019a490((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c5851 */
  file_open((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1c57d0 */
  csmemset((void *)(uintptr_t)ecx, 0, 512);
  saved_game_file_generate_checksum();
  file_write();
  /* test (char)eax, (char)eax -> je 0x1c57b6 */
  file_close((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1c57df */
  error(0, (char *)0x002bbcb0);
  FUN_001c4210();
  /* test (char)eax, (char)eax -> je 0x1c5840 */
  /* relift: cmp dword ptr [ebp + 8], ecx -> je 0x1c5821 */
  display_assert((char *)0x002bbc94, (char *)0x002ba8e8, 434, 0);
  system_exit(0);
  FUN_001c3710();
  error(0, (char *)0x002bbc50);
  error(0, (char *)0x002bbc20);
  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  FUN_001d3185();
  /* test eax, eax -> je 0x1c5899 */
  error(0, (char *)0x002bb55c);
  error(0, (char *)0x002bbbd8);
  error(0, (char *)0x002bbb60);
  display_error_deferred(36, 0, 0, 0);
  csmemset((void *)(uintptr_t)eax, 0, 32);
  xbox_query_global_memory_status((void *)(uintptr_t)ecx);
  /* mem[0x0032eb9c] = edx */
  /* test eax, eax -> je 0x1c5958 */
  /* test (char)eax, (char)eax -> je 0x1c5958 */
  /* test (char)eax, (char)eax -> je 0x1c5978 */
  /* relift: test byte ptr [0x4ead5c], 8 -> je 0x1c5978 */
  /* test edi, edi -> je 0x1c59ec */
  /* test esi, eax -> je 0x1c59ec */
  /* test edi, edi -> jbe 0x1c59ba */
  /* test edi, eax -> je 0x1c59da */
  display_assert((char *)0x002bbe20, (char *)0x002bbe68, 691, 0);
  system_exit(0);
  /* test ebx, ebx -> ja 0x1c5a10 */
  display_assert((char *)0x002bbe0c, (char *)0x002bbe68, 697, 0);
  system_exit(0);
  /* relift: cmp dword ptr [0x4eae2c], ebx -> jae 0x1c5a38 */
  display_assert((char *)0x002bbddc, (char *)0x002bbe68, 698, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1c5a61 */
  display_assert((char *)0x002bbdbc, (char *)0x002bbe68, 699, 0);
  system_exit(0);
  /* mem[0x004eae2c] = eax */
  /* test edi, edi -> je 0x1c5a9f */
  /* cmp ecx, esi -> jl 0x1c5a92 */
  csmemset((void *)(uintptr_t)eax, 0, 32);
  xbox_query_global_memory_status((void *)(uintptr_t)ecx);
  /* mem[0x0032eb9c] = edx */
  /* relift: cmp dword ptr [0x4eacd0], esi -> jne 0x1c5b38 */
  bink_memory_pool_is_empty();
  /* test (char)eax, (char)eax -> jne 0x1c5b1f */
  display_assert((char *)0x002bbf80, (char *)0x002bbe68, 735, 0);
  system_exit(0);
  bink_memory_pool_is_empty();
  /* test (char)eax, (char)eax -> je 0x1c5b38 */
  /* mem[0x004eae30] = esi */
  /* mem[0x004eae28] = ecx */
  /* cmp eax, edx -> ja 0x1c5b61 */
  /* relift: cmp dword ptr [0x4eae30], 0x10 -> jge 0x1c5b61 */
  /* test edx, edx -> jne 0x1c5b8c */
  display_assert((char *)0x002bbf54, (char *)0x002bbe68, 759, 0);
  system_exit(0);
  /* mem[0x004eae28] = eax */
  physical_memory_protect((void *)(uintptr_t)esi, edi, 0);
  /* cmp eax, ecx -> jle 0x1c5bde */
  csprintf((char *)0x005ab100, (char *)0x002bbf00);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp dword ptr [0x4eae30], 0x10 -> jl 0x1c5c07 */
  display_assert((char *)0x002bbed0, (char *)0x002bbe68, 787, 0);
  system_exit(0);
  /* mem[0x004eae30] = eax */
  csmemset((void *)(uintptr_t)eax, 0, 32);
  xbox_query_global_memory_status((void *)(uintptr_t)ecx);
  /* mem[0x0032eb9c] = edx */
  display_assert((char *)0x002bbe90, (char *)0x002bbe68, 799, 0);
  system_exit(0);
  /* mem[0x004eae28] = ecx */
  /* mem[0x004eae28] = eax */
  csmemset((void *)(uintptr_t)eax, 0, 32);
  xbox_query_global_memory_status((void *)(uintptr_t)ecx);
  /* mem[0x0032eb9c] = edx */
  /* relift: cmp dword ptr [eax*4 + 0x4eacd0], edx -> je 0x1c5cf1 */
  /* cmp eax, ecx -> jl 0x1c5ce1 */
  display_assert((char *)0x002bbfbc, (char *)0x002bbe68, 825, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 32);
  xbox_query_global_memory_status((void *)(uintptr_t)ecx);
  /* mem[0x0032eb9c] = edx */
  FUN_001d90e0();
  /* cmp (int16_t)edx, 1 -> jle 0x1c5e45 */
  /* test esi, esi -> je 0x1c5e5d */
  /* cmp (int16_t)edx, 1 -> jle 0x1c5e77 */
  rasterizer_sprites_render((void *)0x004ead98, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c60f6 */
  BinkGetFrameBuffersInfo((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, esi);
  /* test eax, eax -> jge 0x1c5f12 */
  crt_sprintf((char *)0, (char *)0);
  rect2d_offset((void *)(uintptr_t)eax, esi, 32);
  interface_draw_text(0, 0, 0, 0, 0, 0);
  draw_string_set_color((void *)(uintptr_t)ecx);
  draw_string_set_tab_stops((void *)(uintptr_t)edx, 0);
  rasterizer_text_draw((void *)(uintptr_t)edx, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 0, (char *)(uintptr_t)eax);
  BinkGetSummary((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* mem[0x004ead7c] = esi */
  /* mem[0x004ead8c] = edx */
  /* mem[0x004ead90] = ecx */
  /* mem[0x004ead94] = eax */
  /* mem[0x004ead80] = edi */
  /* mem[0x004ead84] = ebx */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002bbff8);
  draw_string_set_color((void *)(uintptr_t)edx);
  rasterizer_text_draw((void *)(uintptr_t)edx, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 0, (char *)(uintptr_t)eax);
  /* test (char)ebx, (char)ebx -> jne 0x1c6141 */
  input_get_gamepad_state(0);
  /* test eax, eax -> je 0x1c613a */
  /* relift: cmp byte ptr [eax + 0x1c], 1 -> je 0x1c6138 */
  /* relift: cmp byte ptr [eax + 0x1d], 1 -> je 0x1c6138 */
  /* relift: cmp byte ptr [edx + eax + 0x10], 1 -> je 0x1c6138 */
  /* cmp (int16_t)ecx, 8 -> jl 0x1c6125 */
  /* cmp (int16_t)esi, 4 -> jl 0x1c6106 */
  D3DResource_Register((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DTexture_LockRect((void *)(uintptr_t)ecx, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  csmemset((void *)0x004ead58, 0, 216);
  BinkSetSoundSystem((void *)0x001c5ab0, (void *)0x001c5ca0);
  /* test (char)eax, (char)eax -> je 0x1c622e */
  /* test eax, eax -> je 0x1c622e */
  bink_memory_pool_is_empty();
  /* test (char)eax, (char)eax -> jne 0x1c620b */
  display_assert((char *)0x002bc0f0, (char *)0x002bbe68, 665, 0);
  system_exit(0);
  xbox_texture_cache_return_memory();
  /* mem[0x004eae24] = 0 */
  /* mem[0x004ead78] = 0 */
  /* mem[0x004eae2c] = 0 */
  BinkDoFrame((void *)(uintptr_t)eax);
  BinkNextFrame((void *)(uintptr_t)ecx);
  D3DTexture_LockRect((void *)(uintptr_t)eax, 0, (void *)(uintptr_t)edx, (void *)0, 0);
  BinkCopyToBuffer((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0, 0, 0, 0, ecx);
  /* test (char)eax, (char)eax -> je 0x1c6301 */
  /* relift: test byte ptr [0x4ead5c], 4 -> je 0x1c62bc */
  event_manager_suppress(0);
  /* test eax, eax -> je 0x1c62d5 */
  BinkClose((void *)(uintptr_t)eax);
  /* mem[0x004ead60] = 0 */
  bink_playback_release_texture_cache();
  /* relift: test byte ptr [0x4ead5c], 0x20 -> je 0x1c62e8 */
  main_menu_load();
  /* mem[0x004ead5c] = 0 */
  /* test (char)eax, (char)eax -> je 0x1c6332 */
  bink_playback_stop();
  csmemset((void *)0x004ead58, 0, 216);
  /* test (char)eax, (char)eax -> je 0x1c63df */
  /* test eax, eax -> je 0x1c63df */
  /* test (char)ecx, (char)ecx -> je 0x1c6380 */
  BinkWait((void *)(uintptr_t)eax);
  BinkWait((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x1c6377 */
  /* test (char)ecx, 2 -> je 0x1c63bf */
  /* test (char)ecx, 0x40 -> je 0x1c63b0 */
  ui_widget_initialization_in_progress();
  /* test (char)eax, (char)eax -> je 0x1c63b9 */
  bink_playback_check_any_button();
  /* test (char)eax, (char)eax -> jne 0x1c63da */
  /* test eax, eax -> je 0x1c63d5 */
  /* test (char)ecx, 1 -> jne 0x1c63df */
  /* test (char)eax, (char)eax -> je 0x1c6439 */
  /* test eax, eax -> je 0x1c6439 */
  /* test (char)eax, (char)eax -> je 0x1c6404 */
  /* test (char)eax, (char)eax -> je 0x1c6419 */
  bink_playback_decode_frame();
  bink_playback_render_frame();
  /* mem[0x004ead88] = ecx */
  csmemset((void *)(uintptr_t)eax, 0, 32);
  xbox_query_global_memory_status((void *)(uintptr_t)ecx);
  /* mem[0x0032eb9c] = edx */
  cache_files_precache_in_progress();
  /* test (char)eax, (char)eax -> jne 0x1c6869 */
  /* relift: cmp dword ptr [0x4ead60], ebx -> je 0x1c64b7 */
  display_assert((char *)0x002bc2c4, (char *)0x002bbe68, 414, 0);
  system_exit(0);
  /* mem[0x004eae2c] = eax */
  /* mem[0x004eae28] = ebx */
  xbox_texture_cache_steal_memory(eax);
  /* mem[0x004eae24] = eax */
  display_assert((char *)0x002bc28c, (char *)0x002bbe68, 424, 0);
  system_exit(0);
  physical_memory_protect((void *)(uintptr_t)edx, ecx, 0);
  /* relift: cmp dword ptr [0x4eae24], ebx -> je 0x1c6855 */
  bink_playback_trace((char *)0x002bc27c);
  bink_get_dsound_handle();
  bink_playback_trace((char *)0x002bc25c);
  BinkSoundUseDirectSound((void *)0x00231e80, (void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1c657b */
  bink_playback_trace((char *)0x002bc240);
  /* cmp (char)eax, (char)ebx -> jne 0x1c659e */
  error(0, (char *)0x002bc21c);
  /* cmp esi, ebx -> je 0x1c65b3 */
  BinkSetMemory(0x00c00000);
  BinkOpen((char *)(uintptr_t)esi, ebx);
  /* mem[0x004ead60] = eax */
  bink_playback_trace((char *)0x002bc20c);
  /* cmp eax, ebx -> je 0x1c6839 */
  bink_memory_pool_alloc(0, 0);
  bink_playback_trace((char *)0x002bc1f4);
  physical_memory_protect((void *)(uintptr_t)edi, esi, 1028);
  bink_playback_trace((char *)0x002bc1dc);
  rand();
  /* mem[0x004ead6c] = ebx */
  /* mem[0x004ead70] = 3 */
  /* mem[0x004ead74] = 4 */
  /* mem[0x004ead78] = 0x4ead40 */
  /* mem[0x004ead40] = 0x40001 */
  /* mem[0x004ead44] = ebx */
  /* mem[0x004ead48] = ebx */
  /* mem[0x004ead50] = ecx */
  /* mem[0x004ead4c] = 0x11e29 */
  D3DResource_Register((void *)0x004ead40, (void *)0);
  csmemset((void *)0x004ead98, 0, 140);
  /* mem[0x004eadd8] = 0x3f800000 */
  /* mem[0x004eaddc] = 0x3f800000 */
  /* mem[0x004eadc0] = 0x3f800000 */
  /* mem[0x004eadc4] = 0x3f800000 */
  /* mem[0x004ead98] = ebx */
  /* mem[0x004ead10] = 0x6269746d */
  bitmap_format_bits_per_pixel(10);
  /* mem[0x004ead2c] = eax */
  /* mem[0x004ead30] = eax */
  /* mem[0x004ead34] = eax */
  /* mem[0x004ead3c] = eax */
  /* mem[0x004ead38] = edx */
  /* mem[0x004eada4] = 0x4ead10 */
  /* mem[0x004ead5c] = eax */
  bink_playback_trace((char *)0x002bc1c8);
  event_manager_flush();
  event_manager_suppress(0);
  bink_playback_trace((char *)0x002bc1b4);
  bink_playback_decode_frame();
  /* mem[0x004ead7c] = ebx */
  /* mem[0x004ead80] = ebx */
  /* mem[0x004ead84] = ebx */
  /* mem[0x004ead88] = ebx */
  /* mem[0x004ead8c] = ebx */
  /* mem[0x004ead90] = ebx */
  /* mem[0x004ead94] = ebx */
  error(0, (char *)0x002bc18c);
  bink_playback_release_texture_cache();
  error(ebx, (char *)0x002bc130);
  bink_playback_release_texture_cache();
  /* test (char)eax, (char)eax -> je 0x1c687e */
  file_open((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x1c68ea */
  file_read_from_position((void *)(uintptr_t)esi, 0, 12, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c68e1 */
  FUN_00118be0((void *)0x0032ebbc, (void *)(uintptr_t)ecx, 0);
  /* cmp eax, 0x464f524d -> jne 0x1c68e1 */
  /* cmp eax, 0x41494646 -> je 0x1c68df */
  /* cmp eax, 0x41494643 -> jne 0x1c68e1 */
  file_close((void *)(uintptr_t)esi);
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6b08 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6af3 */
  FUN_00118be0((void *)0x0032ebe4, (void *)(uintptr_t)ecx, 0);
  /* cmp eax, 0x434f4d4d -> je 0x1c6993 */
  /* test (char)eax, 1 -> je 0x1c6966 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1c6941 */
  file_close((void *)(uintptr_t)edi);
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6af3 */
  FUN_00118be0((void *)0x0032ec18, (void *)(uintptr_t)ecx, 0);
  csmemcmp((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 10);
  /* test eax, eax -> jne 0x1c6a77 */
  /* relift: cmp dword ptr [ebp - 8], 0x12 -> je 0x1c6a63 */
  /* relift: cmp dword ptr [ebp - 0x36], 0x4e4f4e45 -> jne 0x1c6af3 */
  file_close((void *)(uintptr_t)edi);
  csmemcmp((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 10);
  /* test eax, eax -> jne 0x1c6ac9 */
  /* relift: cmp dword ptr [ebp - 8], 0x12 -> je 0x1c6a63 */
  /* relift: cmp dword ptr [ebp - 0x36], 0x4e4f4e45 -> jne 0x1c6af3 */
  file_close((void *)(uintptr_t)edi);
  csmemcmp((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 10);
  file_close((void *)(uintptr_t)edi);
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6be2 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6bbf */
  FUN_00118be0((void *)0x0032ebe4, (void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 1 -> je 0x1c6b85 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1c6b60 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6bbf */
  file_close((void *)(uintptr_t)edi);
  /* test (char)ebx, (char)ebx -> je 0x1c6be2 */
  FUN_00118620((void *)(uintptr_t)edx, 0, 0);
  display_assert((char *)0x002b3b10, (char *)0x002bc328, 18, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1c6c50 */
  display_assert((char *)0x00265878, (char *)0x002bc328, 19, 0);
  system_exit(0);
  FUN_001c6880((void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x1c6c6b */
  FUN_001c6900();
  /* test (char)eax, (char)eax -> jne 0x1c6c8d */
  FUN_001c6d20();
  /* test (char)eax, (char)eax -> je 0x1c6c86 */
  FUN_001c6d90();
  /* test (char)eax, (char)eax -> jne 0x1c6c8d */
  FUN_001c6880((void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x1c6ce0 */
  FUN_001c6b20();
  /* test (char)eax, (char)eax -> je 0x1c6ce0 */
  FUN_001c6bf0();
  FUN_001c6d20();
  /* test (char)eax, (char)eax -> je 0x1c6d11 */
  FUN_001c6ed0();
  /* test (char)eax, (char)eax -> je 0x1c6d11 */
  FUN_001c6fb0();
  file_open((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6d82 */
  file_read_from_position((void *)(uintptr_t)esi, 0, 12, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6d79 */
  FUN_00118be0((void *)0x0032ec44, (void *)(uintptr_t)ecx, 0);
  /* cmp eax, 0x52494646 -> jne 0x1c6d79 */
  /* relift: cmp dword ptr [ebp - 4], 0x57415645 -> jne 0x1c6d79 */
  file_close((void *)(uintptr_t)esi);
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6ebb */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6ea8 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6e13 */
  FUN_00118be0((void *)0x0032ec68, (void *)(uintptr_t)edx, 0);
  /* cmp eax, ebx -> je 0x1c6e3a */
  /* test (char)eax, 1 -> je 0x1c6e0f */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1c6dd6 */
  file_close((void *)(uintptr_t)edi);
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6ea8 */
  /* cmp ecx, 0x2b11 -> je 0x1c6e88 */
  /* cmp ecx, 0x5622 -> je 0x1c6e88 */
  /* cmp ecx, 0xac44 -> je 0x1c6e88 */
  file_close((void *)(uintptr_t)edi);
  file_close((void *)(uintptr_t)edi);
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6f9c */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6f93 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6f50 */
  FUN_00118be0((void *)0x0032ec68, (void *)(uintptr_t)edx, 0);
  /* test (char)eax, 1 -> je 0x1c6f4c */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1c6f10 */
  file_close((void *)(uintptr_t)edi);
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6f93 */
  file_close((void *)(uintptr_t)edi);
  /* cmp (int16_t)eax, 8 -> jne 0x1c7001 */
  /* cmp (int16_t)eax, 0x10 -> je 0x1c7027 */
  display_assert((char *)0x002bc3a4, (char *)0x002bc3cc, 280, 0);
  system_exit(0);
  game_state_data_new((char *)0x002bc410, 1024, 52);
  /* mem[0x005054e4] = eax */
  game_state_malloc((char *)0x002bc3fc, (char *)0, 0);
  /* mem[0x005054e0] = eax */
  /* test eax, eax -> je 0x1c7073 */
  /* mem[0x005054e4] = 0 */
  /* test eax, eax -> je 0x1c70aa */
  data_delete_all((void *)(uintptr_t)eax);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x1c7159 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('dnsl', 0);
  /* cmp eax, edi -> jne 0x1c7128 */
  /* relift: test byte ptr [esi + 4], 0x10 -> jne 0x1c711f */
  display_assert((char *)0x002bc428, (char *)0x002bc464, 175, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1c713c */
  datum_get((void *)(uintptr_t)eax, 0);
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp edi, -1 -> jne 0x1c70d0 */
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> je 0x1c71db */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 0x10 -> je 0x1c71c4 */
  tag_get('dnsl', 0);
  /* test (char)ecx, 2 -> jne 0x1c71b5 */
  datum_delete((void *)(uintptr_t)eax, 0);
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> jne 0x1c7180 */
  FUN_001b9b60(0, 0x736e6421);
  FUN_001b9b80(0);
  tag_get('!dns', 0);
  FUN_001b9b80(0);
  /* cmp eax, -1 -> jne 0x1c7200 */
  /* test edi, edi -> jne 0x1c7263 */
  display_assert((char *)0x002bc488, (char *)0x002bc464, 239, 0);
  system_exit(0);
  /* cmp ebx, -1 -> je 0x1c7320 */
  /* cmp esi, -1 -> je 0x1c7290 */
  object_get_markers_by_string_id(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1c7316 */
  data_new_at_index((void *)(uintptr_t)ecx);
  /* cmp edi, -1 -> je 0x1c730d */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('dnsl', 0);
  /* cmp eax, edi -> jne 0x1c737e */
  display_assert((char *)0x002bc510, (char *)0x002bc464, 280, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x1c73ba */
  datum_get((void *)(uintptr_t)edx, 0);
  /* test eax, eax -> jne 0x1c73ba */
  display_assert((char *)0x002bc498, (char *)0x002bc464, 281, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)eax, 0);
  display_assert((char *)0x0029c114, (char *)0x002bc464, 328, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x1c741f */
  display_assert((char *)0x002bc550, (char *)0x002bc464, 329, 0);
  system_exit(0);
  sound_start(0, (void *)(uintptr_t)ecx, 0, 0, (void *)0, 0);
  /* test (char)eax, 1 -> jne 0x1c74a6 */
  display_assert((char *)0x002bc550, (char *)0x002bc464, 345, 0);
  system_exit(0);
  sound_start(0, (void *)(uintptr_t)ecx, 0, 0, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1c7545 */
  tag_get('!dns', 0);
  /* cmp eax, -1 -> je 0x1c7545 */
  game_time_get();
  /* cmp eax, -1 -> je 0x1c7595 */
  tag_get(0x736e6421, 0);
  /* cmp eax, -1 -> je 0x1c7594 */
  sound_stop_impulse(0);
  /* cmp eax, -1 -> je 0x1c7641 */
  tag_get(0x6c736e64, 0);
  /* test eax, eax -> jle 0x1c763f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 160);
  /* cmp eax, -1 -> je 0x1c7635 */
  tag_get('!dns', 0);
  /* cmp ecx, 1 -> jne 0x1c7635 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 72);
  /* test ecx, ecx -> je 0x1c7635 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 124);
  sound_cache_request_sound((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, ecx -> jl 0x1c75d0 */
  /* cmp eax, -1 -> je 0x1c76be */
  tag_get('dnsl', 0);
  /* cmp eax, -1 -> je 0x1c76be */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, 0x41 -> jne 0x1c76b8 */
  /* cmp eax, -1 -> je 0x1c7708 */
  tag_get('dnsl', 0);
  /* cmp eax, -1 -> je 0x1c7708 */
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get(0x6c736e64, 0);
  game_looping_sound_new(0, 0, (void *)0x0025386f, 0);
  /* cmp esi, -1 -> je 0x1c775c */
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('dnsl', 0);
  /* cmp eax, -1 -> je 0x1c77e7 */
  /* test (char)eax, 1 -> jne 0x1c780b */
  object_get_function_value(0, 0, (void *)(uintptr_t)edx);
  /* test (char)ebx, (char)ebx -> jne 0x1c784c */
  /* cmp (int16_t)eax, 2 -> je 0x1c783a */
  /* test (char)ecx, (char)ecx -> jne 0x1c784c */
  /* cmp (int16_t)eax, 2 -> je 0x1c783a */
  /* cmp eax, -1 -> je 0x1c78dc */
  object_get_node_matrix(0, ecx);
  /* test eax, eax -> jne 0x1c7891 */
  display_assert((char *)0x0029c114, (char *)0x002bc464, 617, 0);
  system_exit(0);
  matrix_transform_point((float *)(uintptr_t)edi, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  matrix_transform_vector((float *)(uintptr_t)edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  object_get_root_location(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 2], (int16_t)ecx -> je 0x1c7900 */
  /* test (char)eax, (char)eax -> je 0x1c7900 */
  sound_refresh_looping(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c783a */
  /* relift: test byte ptr [ebx], 2 -> jne 0x1c7959 */
  display_assert((char *)0x002bc570, (char *)0x002bc464, 655, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1c7834 */
  /* relift: cmp dword ptr [ebx + 0x1c], edi -> jne 0x1c79f0 */
  game_looping_sound_delete(0);
  /* test (char)eax, (char)eax -> je 0x1c79e6 */
  sound_refresh_looping(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> jne 0x1c79e6 */
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1c7834 */
  game_looping_sound_delete(0);
  object_try_and_get_and_verify_type(0, 0);
  display_assert((char *)0x002bc5b4, (char *)0x002bc464, 792, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1c7a77 */
  display_assert((char *)0x00280d08, (char *)0x002bc464, 793, 0);
  system_exit(0);
  /* test edi, edi -> je 0x1c7aef */
  object_get_location(0, (void *)(uintptr_t)ecx);
  /* relift: cmp word ptr [ebp - 4], -1 -> je 0x1c7aef */
  /* cmp (int16_t)eax, 0xffff -> jne 0x1c7aa0 */
  object_get_node_matrix(0, eax);
  matrix_transform_point((float *)(uintptr_t)edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix_transform_vector((float *)(uintptr_t)edi, (float *)(uintptr_t)ebx, (float *)0);
  object_get_root_location(0, (float *)(uintptr_t)esi, (float *)0);
  /* test (char)ecx, (char)ecx -> je 0x1c7b30 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x1c7b2f */
  sound_object_apply_pitch_delta(0, 0.0f);
  scenario_get();
  csmemset((void *)0x005054a0, 0, eax);
  local_player_get_player_index(esi);
  /* cmp eax, -1 -> je 0x1c7c17 */
  observer_get_camera(esi);
  /* test ecx, ecx -> jle 0x1c7c17 */
  structure_bsp_cluster_sound_encoding((void *)(uintptr_t)ebx, edi, ecx);
  /* cmp esi, eax -> jl 0x1c7ba9 */
  /* relift: cmp word ptr [esi + 4], -1 -> jl 0x1c7c48 */
  scenario_get();
  /* relift: cmp ecx, dword ptr [eax + 0x134] -> jl 0x1c7c68 */
  display_assert((char *)0x002bc5c8, (char *)0x002bc464, 868, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1c7c93 */
  /* relift: test dword ptr [eax*4 + 0x5054a0], edx -> je 0x1c7c93 */
  /* cmp eax, -1 -> je 0x1c7cff */
  tag_get(0x6c736e64, 0);
  /* cmp eax, -1 -> je 0x1c7cfd */
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get(0x6c736e64, 0);
  /* test eax, eax -> jle 0x1c7d66 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 160);
  /* cmp eax, -1 -> je 0x1c7d5c */
  tag_get('!dns', 0);
  /* relift: cmp word ptr [eax + 4], 0x20 -> je 0x1c7d6b */
  /* cmp eax, ecx -> jl 0x1c7d30 */
  data_next_index((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp eax, ebx -> jne 0x1c7e0f */
  game_sound_music_has_vehicle_sound(0);
  /* test (char)eax, (char)eax -> je 0x1c7e0f */
  /* cmp eax, ebx -> je 0x1c7e0f */
  tag_get('dnsl', 0);
  /* cmp eax, ebx -> je 0x1c7e0f */
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1c7e61 */
  /* test (char)ecx, (char)ecx -> je 0x1c7e61 */
  game_sound_clear();
  data_make_invalid((void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x1c7eaa */
  display_assert((char *)0x002bc62c, (char *)0x002bc464, 300, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x1c7eca */
  display_assert((char *)0x002bc550, (char *)0x002bc464, 301, 0);
  system_exit(0);
  FUN_001c7a10(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c7f68 */
  sound_start(0, (void *)(uintptr_t)edx, 0, 0x001c7a10, (void *)(uintptr_t)ecx, 28);
  /* cmp edi, -1 -> je 0x1c80db */
  tag_get(0x736e6421, 0);
  sound_stop_impulse(0);
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x1c800d */
  /* cmp esi, -1 -> je 0x1c80c4 */
  object_get_markers_by_string_id(0, (void *)0x002909e4, (void *)(uintptr_t)edx, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1c805b */
  object_impulse_sound_new(0, 0, eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edx, 0.0f);
  /* cmp esi, -1 -> je 0x1c80d3 */
  FUN_0013c980(0, 0, 0);
  sound_impulse_start(0, 0.0f);
  /* cmp eax, -1 -> je 0x1c8138 */
  tag_get(0x6c736e64, 0);
  /* cmp eax, -1 -> je 0x1c8137 */
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  scenario_get_sound_environment((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  sound_manager_set_sound_environment((void *)(uintptr_t)eax);
  FUN_001c7b40();
  /* cmp ecx, -1 -> jne 0x1c81a9 */
  /* cmp eax, -1 -> je 0x1c8225 */
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp eax, -1 -> je 0x1c820c */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, eax -> je 0x1c8225 */
  datum_get((void *)(uintptr_t)eax, 0);
  unattached_looping_sound_start(0, 0, 0x3f800000);
  unattached_looping_sound_start(0, 0, 0x3f800000);
  data_next_index((void *)(uintptr_t)edx, 0);
  /* cmp edi, -1 -> je 0x1c82f9 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> jne 0x1c8260 */
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1c829f */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> jne 0x1c829f */
  tag_get('dnsl', 0);
  /* cmp ecx, edi -> jne 0x1c8294 */
  game_looping_sound_delete(0);
  object_get_and_verify_type(0, 0);
  /* test (char)ecx, 8 -> je 0x1c82de */
  object_get_location(0, (void *)(uintptr_t)eax);
  sound_cluster_is_audible((void *)0);
  /* test (char)eax, (char)eax -> je 0x1c82de */
  FUN_001c77a0();
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> jne 0x1c8243 */
  observer_get_camera(eax);
  display_assert((char *)0x00253440, (char *)0x002bc464, 880, 0);
  system_exit(0);
  display_assert((char *)0x002bc640, (char *)0x002bc464, 885, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x34], (int16_t)ebx -> je 0x1c84ca */
  /* relift: cmp word ptr [edi + 0x10], (int16_t)ebx -> je 0x1c84ca */
  scenario_get();
  structure_bsp_cluster_sound_encoding((void *)(uintptr_t)eax, ecx, edx);
  scenario_get();
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)eax, 0);
  /* test ebx, ecx -> je 0x1c8473 */
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x1c8473 */
  /* test (char)eax, 0x41 -> jne 0x1c84c7 */
  display_assert((char *)0x00253418, (char *)0x002bc464, 924, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x1c8598 */
  tag_get(0x6c736e64, 0);
  sound_looping_stop(0);
  /* cmp eax, -1 -> je 0x1c855b */
  display_assert((char *)0x002bc684, (char *)0x002bc464, 493, 0);
  system_exit(0);
  /* relift: test byte ptr [edi], 4 -> je 0x1c8565 */
  game_sound_music_stop_for_vehicle();
  unattached_looping_sound_start(0, 0, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* test ecx, ecx -> je 0x1c86df */
  /* cmp ecx, esi -> jl 0x1c8629 */
  /* test dl, dl -> jne 0x1c8621 */
  /* test (char)ebx, dl -> je 0x1c8646 */
  /* test dl, dl -> jne 0x1c8640 */
  /* test (char)ebx, 8 -> je 0x1c8655 */
  /* cmp ecx, 0xffff8000 -> jge 0x1c8666 */
  /* test ecx, ecx -> jge 0x1c868c */
  /* relift: cmp dword ptr [edi], 0 -> jne 0x1c8747 */
  /* test ecx, ecx -> je 0x1c887a */
  /* test ecx, ecx -> je 0x1c887a */
  /* test ecx, ecx -> je 0x1c887a */
  /* test (char)ebx, dl -> je 0x1c87d6 */
  /* test (char)ebx, (char)ebx -> jne 0x1c87d0 */
  /* test dl, 8 -> je 0x1c87e5 */
  /* cmp ecx, 0xffff8000 -> jge 0x1c87fb */
  /* test ecx, ecx -> jge 0x1c8824 */
  /* test ecx, ecx -> jne 0x1c8791 */
  FUN_00118be0((void *)0x0032ecf4, (void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)eax, 0x33 -> jl 0x1c8902 */
  display_assert((char *)0x002bcb40, (char *)0x002bcb78, 131, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edx], 0 -> jne 0x1c892e */
  display_assert((char *)0x002bcb1c, (char *)0x002bcb78, 132, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi], 0x10 -> jle 0x1c8954 */
  display_assert((char *)0x002bcac8, (char *)0x002bcb78, 133, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 2], 0x10 -> jle 0x1c897b */
  display_assert((char *)0x002bca68, (char *)0x002bcb78, 134, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d5c66 */
void FUN_001d5c66(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* test eax, eax -> jne 0x1d5c92 */
  /* test (char)ecx, 1 -> jne 0x1d5cbc */
  /* cmp edi, 0x80 -> jae 0x1d5e34 */
  /* relift: cmp dword ptr [eax], eax -> je 0x1d5d4b */
  /* cmp ecx, edi -> jne 0x1d5d27 */
  /* test eax, eax -> je 0x1d5d95 */
  /* test eax, eax -> je 0x1d5dac */
  /* test eax, eax -> je 0x1d5dc3 */
  /* test eax, eax -> je 0x1d5e3d */
  FUN_001d8750(0);
  /* cmp ecx, edx -> jne 0x1d5eac */
  /* relift: cmp edi, dword ptr [esi + 0x1c] -> ja 0x1d629d */
  /* cmp edx, eax -> je 0x1d5e87 */
  /* relift: cmp eax, dword ptr [ebp - 0x28] -> jb 0x1d5e87 */
  /* cmp edx, ecx -> je 0x1d5e87 */
  /* relift: cmp esi, dword ptr [ebp - 0x28] -> jb 0x1d5e83 */
  FUN_001d5411();
  /* test eax, eax -> je 0x1d628e */
  /* test edx, edx -> je 0x1d6238 */
  /* cmp edx, 1 -> jne 0x1d5f00 */
  /* test (char)ecx, 0x10 -> je 0x1d5ff2 */
  /* cmp (int16_t)edx, 0x80 -> jae 0x1d5fa4 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d5f90 */
  /* cmp ecx, eax -> je 0x1d5fce */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jbe 0x1d5fce */
  /* test (char)ecx, 1 -> je 0x1d60c3 */
  /* cmp (int16_t)edx, 0x80 -> jae 0x1d6085 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6071 */
  /* cmp ecx, eax -> je 0x1d60af */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jbe 0x1d60af */
  /* cmp ecx, edi -> jne 0x1d6127 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d6127 */
  /* cmp edx, 0xff00 -> ja 0x1d6215 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d6154 */
  /* cmp (int16_t)edx, 0x80 -> jae 0x1d61d7 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d61b6 */
  /* cmp ecx, eax -> je 0x1d6201 */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jbe 0x1d6201 */
  FUN_001d4cd9();
  /* relift: test byte ptr [esi + 5], 0x10 -> je 0x1d6238 */
  /* relift: test byte ptr [ebp - 0x31], 0x10 -> je 0x1d624a */
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d626c */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d63bb */
  /* relift: test byte ptr [esi + 0x14], 2 -> je 0x1d636c */
  /* test eax, eax -> jl 0x1d6376 */
  /* relift: test byte ptr [ebp + 0xc], 4 -> je 0x1d63b4 */
  FUN_001d63d5();
  __SEH_epilog();
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
  /* relift: tail-call FUN_001d5c66(); */
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
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d7711 */
  /* relift: cmp dword ptr [0x632a08], 0 -> je 0x1d7746 */
  FUN_001d4464();
  /* test eax, eax -> jne 0x1d77a2 */
  /* mem[0x00632a08] = eax */
  /* mem[0x00632a0c] = 1 */
  XAutoPowerDownResetTimer();
  xCompareStringA(0, 0, 0, (char *)(uintptr_t)esi, 0);
  /* test eax, eax -> jne 0x1d7810 */
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1d7808 */
  /* test esi, esi -> je 0x1d7803 */
  /* relift: cmp dl, byte ptr [esi] -> jne 0x1d77fc */
  /* test (char)ecx, (char)ecx -> je 0x1d77f8 */
  /* relift: cmp dl, byte ptr [esi + 1] -> jne 0x1d77fc */
  /* test (char)ecx, (char)ecx -> jne 0x1d77da */
  xCompareStringA(0, 0, 0, (char *)(uintptr_t)esi, 0);
  /* test eax, eax -> jne 0x1d7855 */
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1d784d */
  /* test esi, esi -> je 0x1d7848 */
  crt_stricmp(0, (char *)(uintptr_t)esi);
  FUN_001dd5c8();
  /* test (char)eax, (char)eax -> jne 0x1d7872 */
  __SEH_epilog();
  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 0x10], ebx -> je 0x1d78e1 */
  /* relift: cmp dword ptr [ebp + 0x10], ebx -> je 0x1d78db */
  /* cmp dl, (char)ebx -> je 0x1d78d6 */
  /* relift: cmp dword ptr [ebp + 0x10], ebx -> jne 0x1d78df */
  __SEH_epilog();
  FUN_001dd5c8();
  /* test (char)ecx, (char)ecx -> jne 0x1d7914 */
  /* test (char)ecx, (char)ecx -> jne 0x1d7928 */
  __SEH_epilog();
  FUN_001dd5c8();
  /* test eax, eax -> je 0x1d798d */
  /* test (char)ecx, (char)ecx -> jne 0x1d7973 */
  __SEH_epilog();
  FUN_001d88ef();
  /* test eax, eax -> jne 0x1d79d5 */
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1d79cd */
  /* test esi, esi -> je 0x1d79c8 */
  _wcscmp(0, (wchar_t *)(uintptr_t)esi);
  FUN_001d88ef();
  /* test eax, eax -> jne 0x1d7a1a */
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1d7a12 */
  /* test esi, esi -> je 0x1d7a0d */
  __wcsicmp(0, (wchar_t *)(uintptr_t)esi);
  FUN_001dd5c8();
  _wcscpy();
  __SEH_epilog();
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
  /* cmp edi, ebx -> jl 0x1d7c53 */
  /* test edi, edi -> jl 0x1d7c53 */
  /* test (char)ebx, (char)ebx -> je 0x1d7beb */
  FUN_001d7b37((void *)0, (void *)(uintptr_t)esi);
  /* test dl, 1 -> je 0x1d7c23 */
  /* test edi, edi -> jl 0x1d7c42 */
  /* test edi, edi -> jge 0x1d7b47 */
  /* cmp edi, 0xc000000f -> jne 0x1d7cac */
  /* test esi, esi -> jl 0x1d7d1a */
  FUN_001d7b37((void *)0, (void *)(uintptr_t)eax);
  /* test esi, esi -> jl 0x1d7d7d */
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
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e28);
  XapiMapLetterToDirectory();
  /* test eax, eax -> jl 0x1d81f0 */
  XapiMapLetterToDirectory();
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
  XapiBootToDash();
  /* cmp eax, esi -> jge 0x1d8342 */
  /* cmp eax, 0xc0000035 -> jne 0x1d829d */
  FUN_001d454b();
  /* cmp esi, eax -> jae 0x1d8364 */
  XapiBootToDash();
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
  LocalFree((void *)(uintptr_t)esi);
  /* relift: cmp dword ptr [ebp - 0x14], edi -> jl 0x1d8674 */
  XapiSetLastNTError(0);
  /* test eax, eax -> je 0x1d8697 */
  /* cmp eax, -1 -> je 0x1d8697 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d868a */
  /* test eax, eax -> je 0x1d86b6 */
  /* cmp eax, -1 -> je 0x1d86b6 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d86a9 */
  /* test eax, eax -> je 0x1d86ce */
  /* test eax, eax -> je 0x1d86ed */
  /* cmp eax, -1 -> je 0x1d86ed */
  /* cmp esi, edi -> jb 0x1d86e0 */
  /* cmp eax, edi -> jae 0x1d8718 */
  /* test eax, eax -> je 0x1d8711 */
  /* cmp eax, -1 -> je 0x1d8711 */
  /* cmp esi, edi -> jb 0x1d8704 */
  /* test eax, eax -> je 0x1d873a */
  /* cmp eax, -1 -> je 0x1d873a */
  /* cmp esi, edi -> jb 0x1d872d */
  /* relift: cmp dword ptr [ebp + 0x14], esi -> je 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x10], -1 -> jl 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x18], -1 -> jl 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d88c0 */
  /* test dl, dl -> je 0x1d88a9 */
  /* test (char)ebx, (char)ebx -> je 0x1d88b6 */
  /* test ecx, esi -> je 0x1d883e */
  /* test ecx, edx -> je 0x1d8825 */
  /* cmp esi, edx -> jae 0x1d881a */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d8832 */
  /* test ecx, edx -> je 0x1d8855 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d884f */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d8868 */
  /* test ecx, esi -> jne 0x1d8836 */
  /* test ecx, edx -> jne 0x1d8899 */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x1d888d */
  /* test ecx, esi -> je 0x1d8880 */
  /* test ecx, edx -> je 0x1d888d */
  /* cmp esi, edx -> jb 0x1d88b1 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x1d88c5 */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> jne 0x1d88d1 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d88d1 */
  SetLastError(87);
  /* relift: cmp dword ptr [ebp + 0x14], esi -> je 0x1d8a78 */
  /* relift: cmp dword ptr [ebp + 0x10], -1 -> jl 0x1d8a78 */
  /* relift: cmp dword ptr [ebp + 0x18], -1 -> jl 0x1d8a78 */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d8a59 */
  /* relift: cmp word ptr [edx], (int16_t)esi -> je 0x1d8a42 */
  /* relift: cmp word ptr [edx], (int16_t)esi -> je 0x1d8a4f */
  /* test ecx, esi -> je 0x1d89cf */
  /* test ecx, edx -> je 0x1d89b5 */
  /* cmp esi, edx -> jae 0x1d89aa */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d89c2 */
  /* test ecx, edx -> je 0x1d89e6 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d89e0 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d89ff */
  /* test ecx, esi -> jne 0x1d89c6 */
  /* test ecx, edx -> je 0x1d89ff */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x1d8a24 */
  /* test ecx, esi -> je 0x1d8a17 */
  /* test ecx, edx -> je 0x1d8a24 */
  /* cmp esi, edx -> jb 0x1d8a4a */
  /* relift: cmp word ptr [eax], (int16_t)esi -> je 0x1d8a5e */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> jne 0x1d8a6a */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d8a6a */
  SetLastError(87);
  /* test (char)eax, (char)eax -> jne 0x1d8aeb */
  /* cmp edi, esi -> jb 0x1d8ab3 */
  SetLastError(1168);
  /* test eax, eax -> jge 0x1d8b09 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d8b28 */
  XapiSetLastNTError(0);
  FUN_001d8a88();
  /* cmp eax, -1 -> je 0x1d8b44 */
  FUN_001d8aef();
  FUN_001d8a88();
  /* cmp eax, -1 -> je 0x1d8b5f */
  FUN_001d8b10();
  /* cmp eax, esi -> je 0x1d8b97 */
  FUN_001d0362();
  /* relift: cmp dword ptr [0x4ee4b0], esi -> jne 0x1d8ba7 */
  /* mem[0x004ee4b4] = esi */
  /* relift: FUN_001d8b2e(0, 0); */
  /* relift: FUN_001d8b49(0, 0); */
  /* test eax, eax -> jge 0x1d8ffc */
  /* mem[0x003314a0] = eax */
  /* mem[0x003314a4] = 0x1dded4 */
  /* mem[0x003314a8] = 0x1ddf39 */
  /* mem[0x003314ac] = 0x1dde7c */
  /* mem[0x003314b0] = 0x1ddf1f */
  /* mem[0x003314b4] = eax */
  /* mem[0x004fc000] = ecx */
  FUN_001d9011();
  FUN_001de27a();
  /* test eax, eax -> je 0x1d90c7 */
  /* test edx, 0x7fffffff -> jne 0x1d908b */
  /* test eax, eax -> je 0x1d90ef */
  FUN_001de452();
  __flsbuf();
  FUN_001de452();
  FUN_001de452();
  __flsbuf();
  /* test esi, esi -> je 0x1d91ee */
  /* cmp edi, ecx -> jbe 0x1d925a */
  /* test eax, eax -> jle 0x1d921f */
  /* cmp esi, edi -> jbe 0x1d9210 */
  /* test ebp, ebp -> je 0x1d9252 */
  /* cmp edi, ecx -> ja 0x1d9202 */
  /* cmp eax, 2 -> jb 0x1d94dc */
  /* cmp eax, 8 -> ja 0x1d92ef */
  _shortsort();
  /* test eax, eax -> jle 0x1d932a */
  /* test eax, eax -> jle 0x1d935c */
  /* test eax, eax -> jle 0x1d938a */
  /* cmp edi, ebx -> jbe 0x1d93b0 */
  /* cmp ebx, edi -> jae 0x1d93b0 */
  /* test eax, eax -> jle 0x1d9394 */
  /* cmp edi, ebx -> ja 0x1d93d0 */
  /* cmp ebx, eax -> ja 0x1d93d0 */
  /* test eax, eax -> jle 0x1d93b0 */
  /* cmp esi, edi -> jbe 0x1d93e6 */
  /* test eax, eax -> jg 0x1d93d0 */
  /* cmp ebx, esi -> ja 0x1d942c */
  /* cmp edi, esi -> jne 0x1d9390 */
  /* cmp edi, esi -> jae 0x1d9450 */
  /* cmp esi, edi -> jbe 0x1d9450 */
  /* test eax, eax -> je 0x1d9432 */
  /* cmp edi, esi -> jb 0x1d946a */
  /* cmp esi, eax -> jbe 0x1d946e */
  /* test eax, eax -> je 0x1d9450 */
  /* cmp edi, ecx -> jl 0x1d94ab */
  /* cmp eax, esi -> jae 0x1d9496 */
  /* cmp ebx, edx -> jae 0x1d92c7 */
  /* cmp ebx, edx -> jae 0x1d94c3 */
  /* cmp eax, esi -> jae 0x1d92c7 */
  FUN_001dee48();
  FUN_001d950d();
  __fload_withFB();
  /* relift: cmp word ptr [esp], 0x27f -> je 0x1d9521 */
  FUN_001dedd5();
  /* cmp eax, 0x3ff00000 -> jae 0x1d9555 */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  FUN_001dedec();
  /* test eax, 0xfffff -> jne 0x1d957a */
  /* relift: cmp dword ptr [esp + 8], 0 -> jne 0x1d957a */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  __startOneArgErrorHandling();
  /* test edx, 3 -> je 0x1d95fb */
  /* cmp (char)ecx, (char)ebx -> je 0x1d95c0 */
  /* test (char)ecx, (char)ecx -> je 0x1d9644 */
  /* test edx, 3 -> jne 0x1d95e8 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9685 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d967e */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9677 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9670 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* test dl, dl -> je 0x1d970a */
  /* test (char)edx, (char)edx -> je 0x1d96f7 */
  /* cmp (char)eax, dl -> je 0x1d96ca */
  /* test (char)eax, (char)eax -> je 0x1d96c4 */
  /* cmp (char)eax, dl -> je 0x1d96ca */
  /* test (char)eax, (char)eax -> jne 0x1d96b9 */
  /* cmp (char)eax, (char)edx -> jne 0x1d96bc */
  /* test (char)eax, (char)eax -> je 0x1d9703 */
  /* cmp (char)eax, (char)eax -> jne 0x1d96a8 */
  /* test (char)eax, (char)eax -> je 0x1d9703 */
  /* cmp (char)eax, (char)eax -> je 0x1d96d4 */
  /* relift: cmp byte ptr [edi], (char)eax -> je 0x1d9731 */
  FUN_001df055();
  FUN_001defb3();
  /* test eax, eax -> je 0x1d9756 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d974e */
  FUN_001df055();
  /* mem[0x004fc010] = 1 */
  /* test ecx, ecx -> je 0x1d97b5 */
  /* test eax, eax -> je 0x1d97a0 */
  /* mem[0x00632dcc] = eax */
  /* cmp eax, edi -> jae 0x1d97d4 */
  /* test eax, eax -> je 0x1d97cd */
  /* cmp esi, edi -> jb 0x1d97c5 */
  /* cmp eax, edi -> jae 0x1d97f3 */
  /* test eax, eax -> je 0x1d97ec */
  /* cmp esi, edi -> jb 0x1d97e4 */
  FUN_001defb3();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001d98a3();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001d9901();
  __SEH_epilog();
  __unlock_file();
  /* cmp eax, esi -> jge 0x1d9930 */
  /* mem[0x00632dc4] = eax */
  FUN_001df1bd();
  /* mem[0x00632dc0] = eax */
  /* mem[0x00632dc4] = esi */
  FUN_001df1bd();
  /* mem[0x00632dc0] = eax */
  /* cmp ecx, 0x3312b0 -> jl 0x1d996a */
  /* cmp eax, -1 -> je 0x1d99a7 */
  /* test eax, eax -> jne 0x1d99aa */
  /* cmp edx, 0x3310a0 -> jl 0x1d9987 */
  __flushall();
  /* relift: cmp byte ptr [0x4fc00c], 0 -> je 0x1d99cd */
  /* cmp eax, ecx -> jb 0x1d99f2 */
  /* cmp eax, 0x331290 -> ja 0x1d99f2 */
  FUN_001df055();
  /* cmp eax, 0x14 -> jge 0x1d9a11 */
  FUN_001df055();
  /* cmp eax, ecx -> jb 0x1d9a44 */
  /* cmp eax, 0x331290 -> ja 0x1d9a44 */
  FUN_001defb3();
  /* cmp eax, 0x14 -> jge 0x1d9a63 */
  FUN_001defb3();
  /* cmp (char)ecx, 2 -> jne 0x1d9ac1 */
  /* test (int16_t)eax, 0x108 -> je 0x1d9ac1 */
  /* test edi, edi -> jle 0x1d9ac0 */
  __write();
  /* cmp eax, edi -> jne 0x1d9ab9 */
  __flush();
  /* relift: test byte ptr [esi + 0xd], 0x40 -> je 0x1d9af9 */
  FUN_001df4c4();
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
  __unlock_file2();
  FUN_001d9bc9();
  __SEH_epilog();
  FUN_001defb3();
  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> jne 0x1d9bee */
  _flsall();
  __lock_file();
  __fflush_lk();
  FUN_001d9c18();
  __SEH_epilog();
  __unlock_file();
  _flsall();
  __ctrlfp();
  __sptype();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1e67e7 */
void FUN_001e67e7(void)
{
  __unlock_fhandle();
  FUN_001db777();
  __SEH_epilog();
}

/* 0x1e6805 */
wchar_t *FUN_001e6805(wchar_t *s)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1e6831 */
wchar_t *FUN_001e6831(wchar_t *s)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1e6860 */
void FUN_001e6860(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1e68bb */
void ___loctotime_t(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp esi, 0x46 -> jl 0x1e69c3 */
  /* cmp esi, 0x8a -> jg 0x1e69c3 */
  /* test edx, edx -> jne 0x1e6907 */
  /* test edx, edx -> jne 0x1e6919 */
  /* test edx, edx -> jne 0x1e691f */
  /* cmp ecx, 2 -> jle 0x1e691f */
  FUN_001e1953();
  /* relift: cmp dword ptr [ebp + 0x20], -1 -> jne 0x1e69bd */
  /* relift: cmp dword ptr [0x3317d4], 0 -> je 0x1e69bd */
  FUN_001e1997();

  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}
