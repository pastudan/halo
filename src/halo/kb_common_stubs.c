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

/* FUN_0007ef80 (0x7ef80) — XBE naked draft (batch 299). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0007ef80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jle .LFUN_0007ef80_16\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "decl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_0007ef80_1:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "movl $4, %%edx\n\t"
      ".LFUN_0007ef80_2:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_0007ef80_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0007ef80_5\n\t"
      ".LFUN_0007ef80_3:\n\t"
      "cmpw $0xff, %%ax\n\t"
      "jle .LFUN_0007ef80_4\n\t"
      "movl $0xff, %%eax\n\t"
      "jmp .LFUN_0007ef80_5\n\t"
      ".LFUN_0007ef80_4:\n\t"
      "movswl %%ax, %%eax\n\t"
      ".LFUN_0007ef80_5:\n\t"
      "addl $2, %%esi\n\t"
      "movb %%al, (%%ecx)\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_0007ef80_2\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $4, %%edi\n\t"
      ".LFUN_0007ef80_6:\n\t"
      "movw (%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_0007ef80_7\n\t"
      "movswl %%ax, %%edx\n\t"
      "movzbl -0xc(%%ebp,%%esi,1), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb $8, %%cl\n\t"
      "subb %%dl, %%cl\n\t"
      "shrl %%cl, %%eax\n\t"
      "movl $1, %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "imull $0xff, %%eax, %%eax\n\t"
      "shll %%cl, %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "jmp .LFUN_0007ef80_8\n\t"
      ".LFUN_0007ef80_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0007ef80_8:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movb %%al, -0x20(%%ebp,%%esi,1)\n\t"
      "movb %%al, (%%esi,%%ecx,1)\n\t"
      "incl %%esi\n\t"
      "addl $2, %%ebx\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0007ef80_6\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "subl %%eax, %%edx\n\t"
      "leal 0x8(%%eax), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl $4, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_0007ef80_10\n\t"
      ".LFUN_0007ef80_9:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0007ef80_10:\n\t"
      "movzbw -0x20(%%ebp,%%eax,1), %%di\n\t"
      "movzbw -0xc(%%ebp,%%eax,1), %%si\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "subl %%edi, %%esi\n\t"
      "cmpl -0x14(%%ebp), %%eax\n\t"
      "jge .LFUN_0007ef80_11\n\t"
      "movw (%%edx,%%ecx,1), %%di\n\t"
      "cmpw (%%ebx), %%di\n\t"
      "jle .LFUN_0007ef80_11\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $7, %%eax, %%eax\n\t"
      "cdq\n\t"
      "andl $0xf, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "sarl $4, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "movw %%ax, (%%edx,%%ecx,1)\n\t"
      ".LFUN_0007ef80_11:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0007ef80_14\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "je .LFUN_0007ef80_12\n\t"
      "movw -0x10(%%ecx), %%di\n\t"
      "cmpw (%%ebx), %%di\n\t"
      "jle .LFUN_0007ef80_12\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "cdq\n\t"
      "andl $0xf, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $4, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "movw %%ax, -0x10(%%ecx)\n\t"
      ".LFUN_0007ef80_12:\n\t"
      "movw -0x8(%%ecx), %%di\n\t"
      "cmpw (%%ebx), %%di\n\t"
      "jle .LFUN_0007ef80_13\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "cdq\n\t"
      "andl $0xf, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $4, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "movw %%ax, -0x8(%%ecx)\n\t"
      ".LFUN_0007ef80_13:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpl %%eax, -0x4(%%ebp)\n\t"
      "jge .LFUN_0007ef80_14\n\t"
      "movw (%%ecx), %%di\n\t"
      "cmpw (%%ebx), %%di\n\t"
      "jle .LFUN_0007ef80_14\n\t"
      "movswl %%si, %%eax\n\t"
      "cdq\n\t"
      "andl $0xf, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $4, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "movw %%ax, (%%ecx)\n\t"
      ".LFUN_0007ef80_14:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "addl $2, %%ebx\n\t"
      "addl $2, %%ecx\n\t"
      "decl %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "jne .LFUN_0007ef80_9\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "je .LFUN_0007ef80_15\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      ".LFUN_0007ef80_15:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "incl %%edx\n\t"
      "cmpw 0x10(%%ebp), %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .LFUN_0007ef80_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0007ef80_16:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0007ef80: clang naked draft required"
#endif


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

/* FUN_000887e0 (0x887e0) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b887e0_cb6740)(int16_t local_player_index, void *out_info) = player_control_get_unit_camera_info;
static void (*const b887e0_c86220)(int16_t player_index) = director_set_local_player_context;
static void (*const b887e0_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b887e0_c8aa80)(float *forward, float *up) = observer_up_from_forward;
static void (*const b887e0_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;
static bool (*const b887e0_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b887e0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b887e0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b887e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b887e0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000887e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6740]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000887e0_3\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fadds 0xc(%%edi)\n\t"
      "fstps 0xc(%%edi)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "fcoms 0x267208\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000887e0_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x267208\n\t"
      "jmp .LFUN_000887e0_2\n\t"
      ".LFUN_000887e0_1:\n\t"
      "fcoms 0x267204\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000887e0_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x267204\n\t"
      ".LFUN_000887e0_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "fstps 0x10(%%edi)\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c86220]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000887e0_3:\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x259ec0\n\t"
      "fsubrs 0x4(%%edi)\n\t"
      "fcoms 0x253f3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000887e0_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253f3c\n\t"
      ".LFUN_000887e0_4:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "fstps 0x4(%%edi)\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000887e0_5\n\t"
      "leal 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10cc40]\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8aa80]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140070]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl $1, (%%esi)\n\t"
      ".LFUN_000887e0_5:\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x10(%%esi), %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl 0x2670c8, %%ecx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl 0x2670d0, %%edx\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "testb $1, (%%esi)\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      "movl %%edx, 0x48(%%esi)\n\t"
      "je .LFUN_000887e0_7\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000887e0_6\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000887e0_6\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl 0x2670c8, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x2670c8\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x2670c8\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000887e0_6\n\t"
      "movl 0x2670d0, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_000887e0_6\n\t"
      "flds 0x2670d0\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000887e0_6\n\t"
      "flds 0x2670d0\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_000887e0_7\n\t"
      ".LFUN_000887e0_6:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0x2670d0\n\t"
      "pushl $1\n\t"
      "pushl $0x23b\n\t"
      "pushl $0x267120\n\t"
      "pushl %%eax\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "flds 0x2670c8\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ecx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000887e0_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cb6740] "m"(b887e0_cb6740), [c86220] "m"(b887e0_c86220), [c10cc40] "m"(b887e0_c10cc40), [c8aa80] "m"(b887e0_c8aa80), [c140070] "m"(b887e0_c140070), [c84a70] "m"(b887e0_c84a70), [c84a10] "m"(b887e0_c84a10), [c8d9d0] "m"(b887e0_c8d9d0), [assert] "m"(b887e0_assert), [exitfn] "m"(b887e0_exitfn)
      : "memory");
}
#else
#error "FUN_000887e0: clang naked draft required"
#endif


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

/* FUN_000c0bf0 (0xc0bf0) — XBE naked draft (batch 297). */
#if defined(__clang__)
static int (*const bc0bf0_ccc560)(int16_t function_index, int thread_datum, char init) = hs_macro_function_evaluate;
static void (*const bc0bf0_c579d0)(int encounter_handle, short return_state) = FUN_000579d0;
static void (*const bc0bf0_ccbf80)(int thread_handle, int value) = hs_return;

__attribute__((naked, noinline))
void FUN_000c0bf0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[ccc560]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c0bf0_1\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c579d0]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[ccbf80]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000c0bf0_1:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ccc560] "m"(bc0bf0_ccc560), [c579d0] "m"(bc0bf0_c579d0), [ccbf80] "m"(bc0bf0_ccbf80)
      : "memory");
}
#else
#error "FUN_000c0bf0: clang naked draft required"
#endif


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

/* FUN_000ed470 (0xed470) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const bed470_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static void (*const bed470_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bed470_exitfn)(int) = system_exit;
static void (*const bed470_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000ed470(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000ed470_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb7f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ed470_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000ed470_35\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed470_2\n\t"
      "pushl $1\n\t"
      "pushl $0xb87\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ed470_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed470_4\n\t"
      ".LFUN_000ed470_3:\n\t"
      "movl $2, %%ecx\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed470_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed470_3\n\t"
      ".LFUN_000ed470_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xb89\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286c70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x4c(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed470_6\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000ed470_6\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_7\n\t"
      ".LFUN_000ed470_6:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed470_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed470_8\n\t"
      "pushl $1\n\t"
      "pushl $0xb92\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286c10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed470_10\n\t"
      ".LFUN_000ed470_9:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed470_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed470_9\n\t"
      ".LFUN_000ed470_10:\n\t"
      "pushl $1\n\t"
      "pushl $0xb94\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286be0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_11:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movzbl 0x4e(%%edx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed470_12\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000ed470_13\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_13\n\t"
      ".LFUN_000ed470_12:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ed470_13:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed470_14\n\t"
      "pushl $1\n\t"
      "pushl $0xb9d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286b80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_14:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed470_16\n\t"
      ".LFUN_000ed470_15:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed470_17\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed470_15\n\t"
      ".LFUN_000ed470_16:\n\t"
      "pushl $1\n\t"
      "pushl $0xb9f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286b54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_17:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x4d(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed470_18\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000ed470_18\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_19\n\t"
      ".LFUN_000ed470_18:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed470_19:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed470_20\n\t"
      "pushl $1\n\t"
      "pushl $0xba8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286af4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_20:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed470_22\n\t"
      ".LFUN_000ed470_21:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed470_23\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed470_21\n\t"
      ".LFUN_000ed470_22:\n\t"
      "pushl $1\n\t"
      "pushl $0xbaa\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_23:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x40(%%edx), %%eax\n\t"
      "addl $-5, %%eax\n\t"
      "cmpl $0x2d, %%eax\n\t"
      "ja .LFUN_000ed470_28\n\t"
      "movzbl 0xed790(%%eax), %%eax\n\t"
      "jmp *.LFUN_000ed470_jt(,%%eax,4)\n\t"
      ".LFUN_000ed470_24:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_29\n\t"
      ".LFUN_000ed470_25:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_29\n\t"
      ".LFUN_000ed470_26:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_29\n\t"
      ".LFUN_000ed470_27:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed470_29\n\t"
      ".LFUN_000ed470_28:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed470_29:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed470_30\n\t"
      "pushl $1\n\t"
      "pushl $0xbb6\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed470_30:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed470_32\n\t"
      ".LFUN_000ed470_31:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed470_33\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed470_31\n\t"
      ".LFUN_000ed470_32:\n\t"
      "pushl $1\n\t"
      "pushl $0xbb8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ed470_33:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movzbl 0x1c(%%ecx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed470_34\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "decl %%eax\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ed470_34:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ed470_35:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ed470_jt:\n\t"
      ".long .LFUN_000ed470_28\n\t"
      ".long .LFUN_000ed470_24\n\t"
      ".long .LFUN_000ed470_25\n\t"
      ".long .LFUN_000ed470_26\n\t"
      ".long .LFUN_000ed470_27\n\t"
      ".long .LFUN_000ed470_28\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bed470_ce0ec0), [assert] "m"(bed470_assert), [exitfn] "m"(bed470_exitfn), [c8f390] "m"(bed470_c8f390)
      : "memory");
}
#else
#error "FUN_000ed470: clang naked draft required"
#endif


/* FUN_000ed7c0 (0xed7c0) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const bed7c0_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static void (*const bed7c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bed7c0_exitfn)(int) = system_exit;
static void (*const bed7c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000ed7c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000ed7c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xbd1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ed7c0_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000ed7c0_62\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_2\n\t"
      "pushl $1\n\t"
      "pushl $0xbd9\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287034\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ed7c0_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "movl $2, %%ecx\n\t"
      "je .LFUN_000ed7c0_4\n\t"
      ".LFUN_000ed7c0_3:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_3\n\t"
      ".LFUN_000ed7c0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xbdb\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287004\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x54(%%eax), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ed7c0_9\n\t"
      "jmp *.LFUN_000ed7c0_jt0(,%%eax,4)\n\t"
      ".LFUN_000ed7c0_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_10\n\t"
      ".LFUN_000ed7c0_7:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_10\n\t"
      ".LFUN_000ed7c0_8:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_10\n\t"
      ".LFUN_000ed7c0_9:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_10:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_11\n\t"
      "pushl $1\n\t"
      "pushl $0xbe6\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286f98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_11:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_13\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000ed7c0_12:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_14\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_12\n\t"
      ".LFUN_000ed7c0_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xbe8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286f64\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_14:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x58(%%edx), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ed7c0_18\n\t"
      "jmp *.LFUN_000ed7c0_jt1(,%%eax,4)\n\t"
      ".LFUN_000ed7c0_15:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_19\n\t"
      ".LFUN_000ed7c0_16:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_19\n\t"
      ".LFUN_000ed7c0_17:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_19\n\t"
      ".LFUN_000ed7c0_18:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_19:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_20\n\t"
      "pushl $1\n\t"
      "pushl $0xbf3\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286efc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_20:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_22\n\t"
      ".LFUN_000ed7c0_21:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_23\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_21\n\t"
      ".LFUN_000ed7c0_22:\n\t"
      "pushl $1\n\t"
      "pushl $0xbf5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286ecc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_23:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x50(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed7c0_26\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ed7c0_24\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ed7c0_25\n\t"
      ".LFUN_000ed7c0_24:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_27\n\t"
      ".LFUN_000ed7c0_25:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_27\n\t"
      ".LFUN_000ed7c0_26:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_27:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_28\n\t"
      "pushl $1\n\t"
      "pushl $0xbff\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286e6c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_28:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_30\n\t"
      ".LFUN_000ed7c0_29:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_31\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_29\n\t"
      ".LFUN_000ed7c0_30:\n\t"
      "pushl $1\n\t"
      "pushl $0xc01\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286e40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_31:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x5c(%%edx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed7c0_33\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ed7c0_32\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000ed7c0_33\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_34\n\t"
      ".LFUN_000ed7c0_32:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_34\n\t"
      ".LFUN_000ed7c0_33:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_34:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_35\n\t"
      "pushl $1\n\t"
      "pushl $0xc0b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_35:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_37\n\t"
      "nop\n\t"
      ".LFUN_000ed7c0_36:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_38\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_36\n\t"
      ".LFUN_000ed7c0_37:\n\t"
      "pushl $1\n\t"
      "pushl $0xc0d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286db8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_38:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x4c(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed7c0_39\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_40\n\t"
      ".LFUN_000ed7c0_39:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_40:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_41\n\t"
      "pushl $1\n\t"
      "pushl $0xc16\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286d54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_41:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_43\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000ed7c0_42:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_44\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_42\n\t"
      ".LFUN_000ed7c0_43:\n\t"
      "pushl $1\n\t"
      "pushl $0xc18\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286d24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_44:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x60(%%edx), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jle .LFUN_000ed7c0_45\n\t"
      "cmpl $0x10, %%eax\n\t"
      "jg .LFUN_000ed7c0_45\n\t"
      "movw %%ax, %%dx\n\t"
      "decw %%dx\n\t"
      "movw %%dx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_46\n\t"
      ".LFUN_000ed7c0_45:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_46:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ed7c0_47\n\t"
      "pushl $1\n\t"
      "pushl $0xc31\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286cc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_47:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_49\n\t"
      ".LFUN_000ed7c0_48:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_50\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_48\n\t"
      ".LFUN_000ed7c0_49:\n\t"
      "pushl $1\n\t"
      "pushl $0xc33\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2869a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_50:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x40(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $0xe, %%eax\n\t"
      "ja .LFUN_000ed7c0_55\n\t"
      "movzbl 0xedcbc(%%eax), %%edx\n\t"
      "jmp *.LFUN_000ed7c0_jt2(,%%edx,4)\n\t"
      ".LFUN_000ed7c0_51:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_56\n\t"
      ".LFUN_000ed7c0_52:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_56\n\t"
      ".LFUN_000ed7c0_53:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_56\n\t"
      ".LFUN_000ed7c0_54:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ed7c0_56\n\t"
      ".LFUN_000ed7c0_55:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ed7c0_56:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_57\n\t"
      "pushl $1\n\t"
      "pushl $0xc3f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ed7c0_57:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ed7c0_59\n\t"
      ".LFUN_000ed7c0_58:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ed7c0_60\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ed7c0_58\n\t"
      ".LFUN_000ed7c0_59:\n\t"
      "pushl $1\n\t"
      "pushl $0xc41\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ed7c0_60:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x1c(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ed7c0_61\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "decl %%eax\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ed7c0_61:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ed7c0_62:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ed7c0_jt0:\n\t"
      ".long .LFUN_000ed7c0_9\n\t"
      ".long .LFUN_000ed7c0_6\n\t"
      ".long .LFUN_000ed7c0_7\n\t"
      ".long .LFUN_000ed7c0_8\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ed7c0_jt1:\n\t"
      ".long .LFUN_000ed7c0_18\n\t"
      ".long .LFUN_000ed7c0_15\n\t"
      ".long .LFUN_000ed7c0_16\n\t"
      ".long .LFUN_000ed7c0_17\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ed7c0_jt2:\n\t"
      ".long .LFUN_000ed7c0_55\n\t"
      ".long .LFUN_000ed7c0_51\n\t"
      ".long .LFUN_000ed7c0_52\n\t"
      ".long .LFUN_000ed7c0_53\n\t"
      ".long .LFUN_000ed7c0_54\n\t"
      ".long .LFUN_000ed7c0_55\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bed7c0_ce0ec0), [assert] "m"(bed7c0_assert), [exitfn] "m"(bed7c0_exitfn), [c8f390] "m"(bed7c0_c8f390)
      : "memory");
}
#else
#error "FUN_000ed7c0: clang naked draft required"
#endif


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
  FUN_000fcec0(0, 0);
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
  FUN_000fcec0(0, 0);

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
  FUN_000fcec0(0, 0);
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

/* FUN_00107520 (0x107520) — XBE naked draft (batch 298). */
#if defined(__clang__)
static void (*const b107520_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b107520_exitfn)(int) = system_exit;
static float * (*const b107520_c1037b0)(float *out, float *p0, float *p1, float *p2) = FUN_001037b0;

__attribute__((naked, noinline))
void FUN_00107520(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00107520_1\n\t"
      "pushl $1\n\t"
      "pushl $0x7b5\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28ba70\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_1:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00107520_2\n\t"
      "pushl $1\n\t"
      "pushl $0x7b6\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c050\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_2:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00107520_3\n\t"
      "pushl $1\n\t"
      "pushl $0x7b7\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c048\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_3:\n\t"
      "movl 0x24(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00107520_4\n\t"
      "pushl $1\n\t"
      "pushl $0x7b8\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c03c\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_4:\n\t"
      "movw 0x28(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00107520_34\n\t"
      "cmpw 0x8(%%ebp), %%ax\n\t"
      "jge .LFUN_00107520_34\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%esi,%%eax,4), %%edx\n\t"
      "movw 0x20(%%ebp), %%si\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%si, %%si\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jle .LFUN_00107520_7\n\t"
      ".LFUN_00107520_5:\n\t"
      "movswl %%cx, %%eax\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LFUN_00107520_6\n\t"
      "flds 0xc(%%eax)\n\t"
      "fmuls 0x8(%%edx)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x10(%%eax)\n\t"
      "fcomps 0x31fb3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00107520_8\n\t"
      ".LFUN_00107520_6:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%si, %%cx\n\t"
      "jl .LFUN_00107520_5\n\t"
      ".LFUN_00107520_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00107520_8:\n\t"
      "leal 0x8(%%ebx), %%ecx\n\t"
      "movzwl %%si, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00107520_9:\n\t"
      "movb -0x8(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00107520_12\n\t"
      "flds -0x4(%%ecx)\n\t"
      "fmuls (%%edx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x8(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "flds 0x31fb40\n\t"
      "fchs\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00107520_10\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00107520_11\n\t"
      ".LFUN_00107520_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00107520_11:\n\t"
      "movb %%al, -0x8(%%ecx)\n\t"
      ".LFUN_00107520_12:\n\t"
      "addl $0x1c, %%ecx\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_00107520_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x18(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .LFUN_00107520_20\n\t"
      ".LFUN_00107520_13:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%esi\n\t"
      "shll $5, %%esi\n\t"
      "movb (%%esi,%%ecx,1), %%al\n\t"
      "addl %%ecx, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00107520_19\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl 0x18(%%esi), %%edi\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "imull $0x1c, %%ecx, %%ecx\n\t"
      "addl %%ebx, %%eax\n\t"
      "addl %%ebx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "jl .LFUN_00107520_34\n\t"
      "movswl 0x20(%%ebp), %%ebx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "jge .LFUN_00107520_34\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LFUN_00107520_34\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jge .LFUN_00107520_34\n\t"
      "cmpb $0, (%%eax)\n\t"
      "jne .LFUN_00107520_14\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "jne .LFUN_00107520_14\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .LFUN_00107520_15\n\t"
      ".LFUN_00107520_14:\n\t"
      "movl $1, %%edx\n\t"
      ".LFUN_00107520_15:\n\t"
      "testb %%dl, %%dl\n\t"
      "movb %%dl, (%%esi)\n\t"
      "je .LFUN_00107520_18\n\t"
      "movb (%%eax), %%al\n\t"
      "cmpb (%%ecx), %%al\n\t"
      "je .LFUN_00107520_18\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00107520_16\n\t"
      "movl %%edi, 0x14(%%esi)\n\t"
      "jmp .LFUN_00107520_17\n\t"
      ".LFUN_00107520_16:\n\t"
      "movl %%edi, 0x18(%%esi)\n\t"
      ".LFUN_00107520_17:\n\t"
      "cmpw %%di, -0xc(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%ebx\n\t"
      "jne .LFUN_00107520_19\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00107520_19\n\t"
      ".LFUN_00107520_18:\n\t"
      "movl 0x24(%%ebp), %%ebx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".LFUN_00107520_19:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x18(%%ebp), %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_00107520_13\n\t"
      "cmpw %%di, -0xc(%%ebp)\n\t"
      "jne .LFUN_00107520_21\n\t"
      ".LFUN_00107520_20:\n\t"
      "pushl $1\n\t"
      "pushl $0x81c\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c258\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_21:\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      "jle .LFUN_00107520_32\n\t"
      "movzwl 0x10(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".LFUN_00107520_22:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "je .LFUN_00107520_31\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw 0x4(%%edx), %%di\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%di, %%ebx\n\t"
      ".LFUN_00107520_23:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl %%ebx, %%esi\n\t"
      "shll $5, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00107520_24\n\t"
      "cmpw 0x18(%%ebp), %%di\n\t"
      "jl .LFUN_00107520_25\n\t"
      ".LFUN_00107520_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x832\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c230\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_25:\n\t"
      "cmpl %%ecx, 0x4(%%esi)\n\t"
      "je .LFUN_00107520_26\n\t"
      "cmpl %%ecx, 0x8(%%esi)\n\t"
      "je .LFUN_00107520_26\n\t"
      "pushl $1\n\t"
      "pushl $0x833\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c1e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_26:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "je .LFUN_00107520_29\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_00107520_27\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00107520_28\n\t"
      ".LFUN_00107520_27:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%ecx, 0x4(%%eax)\n\t"
      "sete %%dl\n\t"
      "movl %%ebx, 0xc(%%eax,%%edx,4)\n\t"
      ".LFUN_00107520_28:\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".LFUN_00107520_29:\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "sete %%dl\n\t"
      "movw 0xc(%%esi,%%edx,4), %%di\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x4(%%edx), %%esi\n\t"
      "movswl %%di, %%ebx\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "jne .LFUN_00107520_23\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_00107520_30\n\t"
      "movb $0, (%%edx)\n\t"
      "jmp .LFUN_00107520_31\n\t"
      ".LFUN_00107520_30:\n\t"
      "movswl -0x14(%%ebp), %%esi\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "sete %%dl\n\t"
      "movl %%esi, 0xc(%%eax,%%edx,4)\n\t"
      ".LFUN_00107520_31:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0xc, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .LFUN_00107520_22\n\t"
      ".LFUN_00107520_32:\n\t"
      "movw 0x10(%%ebp), %%di\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "jle .LFUN_00107520_34\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00107520_33:\n\t"
      "movswl %%cx, %%edx\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "cmpb $0, (%%esi,%%edx,4)\n\t"
      "je .LFUN_00107520_35\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .LFUN_00107520_33\n\t"
      ".LFUN_00107520_34:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00107520_35:\n\t"
      "cmpw %%di, %%cx\n\t"
      "jge .LFUN_00107520_34\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      ".LFUN_00107520_36:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "shll $5, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00107520_37\n\t"
      "cmpw 0x18(%%ebp), %%ax\n\t"
      "jl .LFUN_00107520_38\n\t"
      ".LFUN_00107520_37:\n\t"
      "pushl $1\n\t"
      "pushl $0x877\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c230\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_38:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jne .LFUN_00107520_39\n\t"
      "pushl $1\n\t"
      "pushl $0x878\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c1cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_39:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00107520_40\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00107520_41\n\t"
      ".LFUN_00107520_40:\n\t"
      "pushl $1\n\t"
      "pushl $0x879\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c188\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_41:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00107520_42\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00107520_43\n\t"
      ".LFUN_00107520_42:\n\t"
      "pushl $1\n\t"
      "pushl $0x87a\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c140\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_43:\n\t"
      "movl 0x14(%%esi), %%ebx\n\t"
      "movl 0x18(%%esi), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "sete %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%eax, %%edi\n\t"
      "sete %%cl\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .LFUN_00107520_44\n\t"
      "pushl $1\n\t"
      "pushl $0x87b\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c0f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_44:\n\t"
      "movw 0x20(%%ebp), %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00107520_45:\n\t"
      "movl 0x24(%%ebp), %%edi\n\t"
      "movswl %%ax, %%edx\n\t"
      "imull $0x1c, %%edx, %%edx\n\t"
      "cmpb $0, (%%edx,%%edi,1)\n\t"
      "je .LFUN_00107520_46\n\t"
      "incl %%eax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jl .LFUN_00107520_45\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00107520_46:\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jge .LFUN_00107520_34\n\t"
      "movw 0x18(%%ebp), %%dx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jle .LFUN_00107520_34\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "nop\n\t"
      ".LFUN_00107520_47:\n\t"
      "movswl %%cx, %%ebx\n\t"
      "shll $5, %%ebx\n\t"
      "cmpb $0, (%%ebx,%%edi,1)\n\t"
      "je .LFUN_00107520_48\n\t"
      "incl %%ecx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00107520_47\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00107520_48:\n\t"
      "cmpw %%dx, %%cx\n\t"
      "jge .LFUN_00107520_34\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl %%ebx, %%edi\n\t"
      "imull $0x1c, %%edi, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl %%edx, %%edi\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "setne %%al\n\t"
      "movl 0x4(%%esi,%%eax,4), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $-1, 0x18(%%esi)\n\t"
      "leal (%%edx,%%ecx,4), %%ecx\n\t"
      "setne %%al\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%esi,%%eax,4), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%edx,%%eax,4), %%edx\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jne .LFUN_00107520_49\n\t"
      "pushl $1\n\t"
      "pushl $0x89e\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c0e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_49:\n\t"
      "movw 0x2(%%ecx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .LFUN_00107520_50\n\t"
      "cmpw 0x8(%%ebp), %%cx\n\t"
      "jl .LFUN_00107520_51\n\t"
      ".LFUN_00107520_50:\n\t"
      "pushl $1\n\t"
      "pushl $0x89f\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c0a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_51:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "jne .LFUN_00107520_52\n\t"
      "pushl $1\n\t"
      "pushl $0x8a1\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c098\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_52:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw 0x2(%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00107520_53\n\t"
      "cmpw 0x8(%%ebp), %%ax\n\t"
      "jl .LFUN_00107520_54\n\t"
      ".LFUN_00107520_53:\n\t"
      "pushl $1\n\t"
      "pushl $0x8a2\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c05c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00107520_54:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb $1, (%%edi)\n\t"
      "movswl 0x2(%%edx), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal (%%ecx,%%edx,4), %%eax\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x4(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1037b0]\n\t"
      "movswl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "movl %%ecx, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb $1, (%%eax)\n\t"
      "movl 0x18(%%esi), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movswl -0x4(%%ebp), %%edi\n\t"
      "setne %%dl\n\t"
      "movl 0x4(%%esi,%%edx,4), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%edi, 0xc(%%eax)\n\t"
      "cmpl $-1, 0x14(%%esi)\n\t"
      "setne %%dl\n\t"
      "movl 0xc(%%esi,%%edx,4), %%edx\n\t"
      "movl %%edx, 0x10(%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%ebx, 0x14(%%eax)\n\t"
      "movl $0xffffffff, 0x18(%%eax)\n\t"
      "cmpl $-1, 0x14(%%esi)\n\t"
      "setne %%dl\n\t"
      "movl %%ecx, 0xc(%%esi,%%edx,4)\n\t"
      "xorl %%edx, %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpl %%ecx, 0x14(%%esi)\n\t"
      "setne %%dl\n\t"
      "cmpw %%cx, -0x4(%%ebp)\n\t"
      "movl %%ebx, 0x14(%%esi,%%edx,4)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "jne .LFUN_00107520_55\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_00107520_56\n\t"
      ".LFUN_00107520_55:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "shll $5, %%edi\n\t"
      "movl %%ebx, 0x18(%%edi,%%ecx,1)\n\t"
      ".LFUN_00107520_56:\n\t"
      "movw 0x10(%%eax), %%ax\n\t"
      "cmpw -0xc(%%ebp), %%ax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00107520_36\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%esi\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%ecx\n\t"
      "movw 0x28(%%ebp), %%ax\n\t"
      "movw %%ax, 0x2(%%ecx)\n\t"
      "movswl -0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movb $1, (%%ecx)\n\t"
      "shll $5, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      "shll $5, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x18(%%ecx,%%esi,1)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b107520_assert), [exitfn] "m"(b107520_exitfn), [c1037b0] "m"(b107520_c1037b0)
      : "memory");
}
#else
#error "FUN_00107520: clang naked draft required"
#endif


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

/* FUN_001335e0 (0x1335e0) — XBE naked draft (batch 220). */
#if defined(__clang__)
static void (*const b1335e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1335e0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
float FUN_001335e0(float a __attribute__((unused)), float b __attribute__((unused)), float c __attribute__((unused)), float d __attribute__((unused)), float ta __attribute__((unused)), float tb __attribute__((unused)), float tc __attribute__((unused)), float td __attribute__((unused)), float t __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomps 0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001335e0_1\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomps 0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001335e0_2\n\t"
      ".LFUN_001335e0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5fa\n\t"
      "pushl $0x25ed80\n\t"
      "pushl $0x29aae4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001335e0_2:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsubs 0x20(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fsubs 0x20(%%ebp)\n\t"
      "fmulp %%st(1)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      "fmulp %%st(1)\n\t"
      "fadds 0xc(%%ebp)\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      "fmulp %%st(1)\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b1335e0_assert), [exitfn] "m"(b1335e0_exitfn)
      : "memory");
}
#else
#error "FUN_001335e0: clang naked draft required"
#endif


/* FUN_001336a0 (0x1336a0) — XBE naked draft (batch 224). */
#if defined(__clang__)
static float (*const b1336a0_c1335e0)(float a, float b, float c, float d, float ta, float tb, float tc, float td, float t) = FUN_001335e0;

__attribute__((naked, noinline))
void FUN_001336a0(float *out __attribute__((unused)), float *p0 __attribute__((unused)), float *p1 __attribute__((unused)), float *p2 __attribute__((unused)), float *p3 __attribute__((unused)), float t0 __attribute__((unused)), float t1 __attribute__((unused)), float t2 __attribute__((unused)), float t3 __attribute__((unused)), float time __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x24(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x2c(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x28(%%ebp), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1335e0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "fstps (%%ecx)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1335e0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%eax)\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $0x48, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x8(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1335e0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "fstps 0x8(%%edx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [c1335e0] "m"(b1336a0_c1335e0)
      : "memory");
}
#else
#error "FUN_001336a0: clang naked draft required"
#endif


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
#if defined(__clang__)
static void (*const gpwp_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const gpwp_exitfn)(int) = system_exit;
static void (*const gpwp_a336a0)(float *, float *, float *, float *, float *, float, float, float, float, float) = FUN_001336a0;

__attribute__((naked, noinline))
void get_particle_world_position(int glow_widget __attribute__((unused)), int particle_ptr __attribute__((unused)), float param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc4, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "decl %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jle .Lget_particle_world_position_3\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lget_particle_world_position_1:\n\t"
      "flds 0x238(%%esi,%%ecx,4)\n\t"
      "fcomps 0x28(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lget_particle_world_position_2\n\t"
      "flds 0x23c(%%esi,%%ecx,4)\n\t"
      "fcomps 0x28(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lget_particle_world_position_3\n\t"
      ".Lget_particle_world_position_2:\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jl .Lget_particle_world_position_1\n\t"
      ".Lget_particle_world_position_3:\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .Lget_particle_world_position_4\n\t"
      "pushl $1\n\t"
      "pushl $0x437\n\t"
      "pushl $0x29ab60\n\t"
      "pushl $0x29aba4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lget_particle_world_position_4:\n\t"
      "testw %%bx, %%bx\n\t"
      "jge .Lget_particle_world_position_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lget_particle_world_position_6\n\t"
      ".Lget_particle_world_position_5:\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .Lget_particle_world_position_6\n\t"
      "movl %%ecx, %%eax\n\t"
      ".Lget_particle_world_position_6:\n\t"
      "movw %%ax, 0x2(%%edi)\n\t"
      "cmpw $1, 0x4(%%esi)\n\t"
      "jg .Lget_particle_world_position_7\n\t"
      "pushl $1\n\t"
      "pushl $0x43b\n\t"
      "pushl $0x29ab60\n\t"
      "pushl $0x29ab88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lget_particle_world_position_7:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl $2, %%ecx\n\t"
      "je .Lget_particle_world_position_21\n\t"
      "decl %%ecx\n\t"
      "je .Lget_particle_world_position_19\n\t"
      "leal -0x1(%%eax), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .Lget_particle_world_position_10\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .Lget_particle_world_position_8\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lget_particle_world_position_8:\n\t"
      "flds 0x238(%%esi,%%ecx,4)\n\t"
      "fcomps 0x28(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lget_particle_world_position_9\n\t"
      "flds 0x28(%%edi)\n\t"
      "fcomps 0x23c(%%esi,%%ecx,4)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lget_particle_world_position_10\n\t"
      ".Lget_particle_world_position_9:\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jl .Lget_particle_world_position_8\n\t"
      ".Lget_particle_world_position_10:\n\t"
      "movswl %%bx, %%edi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jl .Lget_particle_world_position_11\n\t"
      "pushl $1\n\t"
      "pushl $0x49c\n\t"
      "pushl $0x29ab60\n\t"
      "pushl $0x29aba4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lget_particle_world_position_11:\n\t"
      "testw %%bx, %%bx\n\t"
      "jge .Lget_particle_world_position_12\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lget_particle_world_position_13\n\t"
      ".Lget_particle_world_position_12:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jg .Lget_particle_world_position_13\n\t"
      "movl %%edi, %%eax\n\t"
      ".Lget_particle_world_position_13:\n\t"
      "leal 0x1(%%eax), %%edx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "subl %%edi, %%ebx\n\t"
      "incl %%ebx\n\t"
      "cmpl $4, %%ebx\n\t"
      "jge .Lget_particle_world_position_17\n\t"
      "movswl 0x4(%%esi), %%edi\n\t"
      "decl %%edi\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      ".Lget_particle_world_position_14:\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lget_particle_world_position_15\n\t"
      "decl %%eax\n\t"
      ".Lget_particle_world_position_15:\n\t"
      "cmpl -0x14(%%ebp), %%ecx\n\t"
      "jge .Lget_particle_world_position_16\n\t"
      "incl %%edx\n\t"
      ".Lget_particle_world_position_16:\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "subl %%edi, %%ebx\n\t"
      "incl %%ebx\n\t"
      "cmpl $4, %%ebx\n\t"
      "jl .Lget_particle_world_position_14\n\t"
      ".Lget_particle_world_position_17:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl 0x238(%%esi,%%ecx,4), %%edx\n\t"
      "leal 0x238(%%esi,%%ecx,4), %%eax\n\t"
      "leal 0x22a(%%esi,%%ecx,2), %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%ecx, -0x84(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x88(%%ebp)\n\t"
      "movl $4, -0x14(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lget_particle_world_position_18:\n\t"
      "movl -0x84(%%ebp), %%ecx\n\t"
      "movswl (%%ecx), %%eax\n\t"
      "imull $0x6c, %%eax, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "leal -0x50(%%ebp,%%edx,1), %%edi\n\t"
      "leal 0x68(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "flds 0x60(%%eax)\n\t"
      "fmuls 0x4c(%%eax)\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "flds 0x48(%%eax)\n\t"
      "fmuls 0x64(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ebx, 0x4(%%edi)\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "leal 0x5c(%%eax), %%ecx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "leal -0x80(%%ebp,%%edx,1), %%edx\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl (%%edi), %%ebx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%edi), %%ebx\n\t"
      "movl 0x8(%%edi), %%edi\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl %%edi, 0x8(%%edx)\n\t"
      "movl -0x88(%%ebp), %%edx\n\t"
      "movl -0x84(%%ebp), %%edi\n\t"
      "addl $2, %%edi\n\t"
      "fstps -0xc4(%%ebp,%%edx,1)\n\t"
      "addl $0xc, %%edx\n\t"
      "flds 0x44(%%eax)\n\t"
      "movl %%edi, -0x84(%%ebp)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "movl %%edx, -0x88(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x4c(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xcc(%%ebp,%%edx,1)\n\t"
      "flds 0x48(%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      "flds 0x44(%%eax)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc8(%%ebp,%%edx,1)\n\t"
      "jne .Lget_particle_world_position_18\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jmp .Lget_particle_world_position_24\n\t"
      ".Lget_particle_world_position_19:\n\t"
      "leal 0x68(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "leal 0x140(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "leal 0x5c(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal 0x134(%%esi), %%eax\n\t"
      "movl %%ecx, -0x7c(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x78(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movswl 0x2(%%edi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl 0x238(%%esi), %%ecx\n\t"
      "movl %%edx, -0x58(%%ebp)\n\t"
      "movl 0x240(%%esi), %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .Lget_particle_world_position_20\n\t"
      "decl %%eax\n\t"
      "jne .Lget_particle_world_position_24\n\t"
      "flds 0x23c(%%esi)\n\t"
      "leal 0xd4(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fsubs -0x50(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "fsubs -0x4c(%%ebp)\n\t"
      "leal 0xc8(%%esi), %%ecx\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "fsubs -0x48(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "movl %%ecx, -0x60(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x50(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fsubs -0x80(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fsubs -0x7c(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fsubs -0x78(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x80(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "jmp .Lget_particle_world_position_22\n\t"
      ".Lget_particle_world_position_20:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "leal 0xd4(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "fsubs -0x44(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "fsubs -0x40(%%ebp)\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal 0xc8(%%esi), %%eax\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x74(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "movl 0x23c(%%esi), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "fadds -0x44(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fsubs -0x74(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs -0x70(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fsubs -0x6c(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x74(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x70(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x70(%%ebp)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "jmp .Lget_particle_world_position_23\n\t"
      ".Lget_particle_world_position_21:\n\t"
      "leal 0x68(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "leal 0xd4(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fsubs -0x50(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "fsubs -0x4c(%%ebp)\n\t"
      "leal 0x5c(%%esi), %%ecx\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "fsubs -0x48(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%eax, -0x7c(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "leal 0xc8(%%esi), %%edx\n\t"
      "fmuls 0x25337c\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "fadds -0x50(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "flds 0x25337c\n\t"
      "movl 0x238(%%esi), %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl 0x23c(%%esi), %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x25337c\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x25afcc\n\t"
      "fadds -0x50(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fmuls 0x25afcc\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x25afcc\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fsubs -0x80(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs -0x7c(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fsubs -0x78(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x25337c\n\t"
      "fadds -0x80(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "flds 0x25337c\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x25337c\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x25afcc\n\t"
      "fadds -0x80(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "fmuls 0x25afcc\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x25afcc\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "flds 0x25337c\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls 0x25afcc\n\t"
      ".Lget_particle_world_position_22:\n\t"
      "fadds -0x10(%%ebp)\n\t"
      ".Lget_particle_world_position_23:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lget_particle_world_position_24:\n\t"
      "movl 0x28(%%edi), %%edx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x2c(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[a336a0]\n\t"
      "movl 0x28(%%edi), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[a336a0]\n\t"
      "movl 0x28(%%edi), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x50, %%esp\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xb8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[a336a0]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x28(%%edi)\n\t"
      "addl $0x28, %%esp\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fsin\n\t"
      "fxch %%st(1)\n\t"
      "fcos\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x94(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x1c(%%edi)\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x90(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x1c(%%edi)\n\t"
      "fadds 0x30(%%edi)\n\t"
      "fstps 0x30(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x8c(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x1c(%%edi)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps 0x34(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "fstp %%st(0)\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(gpwp_assert), [exitfn] "m"(gpwp_exitfn), [a336a0] "m"(gpwp_a336a0)
      : "memory");
}
#else
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
#endif




/* 0x149c60 */
char FUN_00149c60(int *block_ptr, void *transformed_2c, void *transformed_20, float scale, float best_dist, float *result)
{
  int ecx = 0;

  FUN_00149680((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* FUN_00149ce0 (0x149ce0) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b149ce0_chkstk)(void) = FUN_001d90e0;
static void (*const b149ce0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b149ce0_exitfn)(int) = system_exit;
static int (*const b149ce0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const b149ce0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b149ce0_c1459e0)(void) = breakable_surfaces_get_bsp_surface_data;
static void *(*const b149ce0_gbsp)(void) = global_collision_bsp_get;
static char (*const b149ce0_c149480)(int collision_flags, int bsp, short flags, int breakable_surfaces, int origin, int direction, float max_t, float *result) = collision_bsp_test_vector;
static bool (*const b149ce0_c4ec30)(int, float *, float, float, float, int, void *) = FUN_0014ec30;
static int (*const b149ce0_gtime)(void) = game_time_get;
static void (*const b149ce0_c1daf7e)(void) = FUN_001daf7e;
static void (*const b149ce0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b149ce0_c109e90)(float *out, float yaw, float pitch, float roll) = FUN_00109e90;
static void (*const b149ce0_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static void (*const b149ce0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static char (*const b149ce0_c4dc30)(int, float *, int) = FUN_0014dc30;
static void (*const b149ce0_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static char (*const b149ce0_c4dab0)(int, int) = FUN_0014dab0;
static void (*const b149ce0_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;
static bool (*const b149ce0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b149ce0_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;
static int (*const b149ce0_c14c8e0)(int *out, int object_handle) = FUN_0014c8e0;
static void *(*const b149ce0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b149ce0_c1475f0)(int bsp, int surface_index, int matrix_or_flag, void *color) = render_debug_collision_surface;
static void (*const b149ce0_c1d94f0)(void) = FUN_001d94f0;
static const char * (*const b149ce0_cb5490)(short material_type) = FUN_000b5490;
static int (*const b149ce0_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void (*const b149ce0_c189c40)(char flag, const char *string) = FUN_00189c40;
static void (*const b149ce0_c1506d0)(void) = FUN_001506d0;
static int (*const b149ce0_c150550)(void *out_point, float *direction, float *origin, int arg4, int arg5, int arg6, float *out_point2, void *out_arg8, int max_results, void *results) = FUN_00150550;
static void (*const b149ce0_c8dae0)(void *dest, const void *src, unsigned int size) = csmemmove;
static void *(*const b149ce0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b149ce0_c185f80)(void *param_1, void *param_2) = render_frustum_get_projection_bounds;
static void (*const b149ce0_c14c7b0)(int16_t *features) = FUN_0014c7b0;

__attribute__((naked, noinline))
void FUN_00149ce0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0xb528, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_00149ce0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4c\n\t"
      "pushl $0x29ce78\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movb 0x5a8d1f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw $0x15, 0x5a8c80(,%%ecx,2)\n\t"
      "jne .LFUN_00149ce0_2\n\t"
      "movb 0x5a8d1e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_2\n\t"
      "movb 0x5a8d1d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_2\n\t"
      "movb 0x4761c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_90\n\t"
      ".LFUN_00149ce0_2:\n\t"
      "movb 0x324fbc, %%cl\n\t"
      "movb 0x5a8d1b, %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "movl %%edx, %%esi\n\t"
      "je .LFUN_00149ce0_3\n\t"
      "orl $2, %%esi\n\t"
      "jmp .LFUN_00149ce0_4\n\t"
      ".LFUN_00149ce0_3:\n\t"
      "andl $0xfffffffd, %%esi\n\t"
      ".LFUN_00149ce0_4:\n\t"
      "movb 0x5a8d1a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_5\n\t"
      "orl $4, %%esi\n\t"
      "jmp .LFUN_00149ce0_6\n\t"
      ".LFUN_00149ce0_5:\n\t"
      "andl $0xfffffffb, %%esi\n\t"
      ".LFUN_00149ce0_6:\n\t"
      "movb 0x324fbd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_7\n\t"
      "orl $8, %%esi\n\t"
      "jmp .LFUN_00149ce0_8\n\t"
      ".LFUN_00149ce0_7:\n\t"
      "andl $0xfffffff7, %%esi\n\t"
      ".LFUN_00149ce0_8:\n\t"
      "movb 0x5a8d19, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_9\n\t"
      "orl $0x10, %%esi\n\t"
      "jmp .LFUN_00149ce0_10\n\t"
      ".LFUN_00149ce0_9:\n\t"
      "andl $0xffffffef, %%esi\n\t"
      ".LFUN_00149ce0_10:\n\t"
      "movb 0x324fbe, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_11\n\t"
      "orl $0x20, %%esi\n\t"
      "jmp .LFUN_00149ce0_12\n\t"
      ".LFUN_00149ce0_11:\n\t"
      "andl $0xffffffdf, %%esi\n\t"
      ".LFUN_00149ce0_12:\n\t"
      "movb 0x324fbf, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_13\n\t"
      "orl $0x40, %%esi\n\t"
      "jmp .LFUN_00149ce0_14\n\t"
      ".LFUN_00149ce0_13:\n\t"
      "andl $0xffffffbf, %%esi\n\t"
      ".LFUN_00149ce0_14:\n\t"
      "movb 0x324fc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_15\n\t"
      "orl $0x80, %%esi\n\t"
      "jmp .LFUN_00149ce0_16\n\t"
      ".LFUN_00149ce0_15:\n\t"
      "andl $0xffffff7f, %%esi\n\t"
      ".LFUN_00149ce0_16:\n\t"
      "movb 0x5a8d18, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_17\n\t"
      "orl $0x100, %%esi\n\t"
      "jmp .LFUN_00149ce0_18\n\t"
      ".LFUN_00149ce0_17:\n\t"
      "andl $0xfffffeff, %%esi\n\t"
      ".LFUN_00149ce0_18:\n\t"
      "movb 0x5a8d17, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_19\n\t"
      "orl $0x200, %%esi\n\t"
      "jmp .LFUN_00149ce0_20\n\t"
      ".LFUN_00149ce0_19:\n\t"
      "andl $0xfffffdff, %%esi\n\t"
      ".LFUN_00149ce0_20:\n\t"
      "movb 0x5a8d16, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_21\n\t"
      "orl $0x400, %%esi\n\t"
      "jmp .LFUN_00149ce0_22\n\t"
      ".LFUN_00149ce0_21:\n\t"
      "andl $0xfffffbff, %%esi\n\t"
      ".LFUN_00149ce0_22:\n\t"
      "movb 0x5a8d15, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_23\n\t"
      "orl $0x800, %%esi\n\t"
      "jmp .LFUN_00149ce0_24\n\t"
      ".LFUN_00149ce0_23:\n\t"
      "andl $0xfffff7ff, %%esi\n\t"
      ".LFUN_00149ce0_24:\n\t"
      "movb 0x5a8d14, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_25\n\t"
      "orl $0x2000, %%esi\n\t"
      "jmp .LFUN_00149ce0_26\n\t"
      ".LFUN_00149ce0_25:\n\t"
      "andl $0xffffdfff, %%esi\n\t"
      ".LFUN_00149ce0_26:\n\t"
      "movb 0x5a8d13, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_27\n\t"
      "orl $0x4000, %%esi\n\t"
      "jmp .LFUN_00149ce0_28\n\t"
      ".LFUN_00149ce0_27:\n\t"
      "andl $0xffffbfff, %%esi\n\t"
      ".LFUN_00149ce0_28:\n\t"
      "movb 0x5a8d12, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_29\n\t"
      "orl $0x8000, %%esi\n\t"
      "jmp .LFUN_00149ce0_30\n\t"
      ".LFUN_00149ce0_29:\n\t"
      "andl $0xffff7fff, %%esi\n\t"
      ".LFUN_00149ce0_30:\n\t"
      "movb 0x5a8d11, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_31\n\t"
      "orl $0x10000, %%esi\n\t"
      "jmp .LFUN_00149ce0_32\n\t"
      ".LFUN_00149ce0_31:\n\t"
      "andl $0xfffeffff, %%esi\n\t"
      ".LFUN_00149ce0_32:\n\t"
      "movb 0x5a8d10, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_33\n\t"
      "orl $0x20000, %%esi\n\t"
      "jmp .LFUN_00149ce0_34\n\t"
      ".LFUN_00149ce0_33:\n\t"
      "andl $0xfffdffff, %%esi\n\t"
      ".LFUN_00149ce0_34:\n\t"
      "movb 0x5a8d0f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_35\n\t"
      "orl $0x40000, %%esi\n\t"
      "jmp .LFUN_00149ce0_36\n\t"
      ".LFUN_00149ce0_35:\n\t"
      "andl $0xfffbffff, %%esi\n\t"
      ".LFUN_00149ce0_36:\n\t"
      "movb 0x5a8d0e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_37\n\t"
      "orl $0x100000, %%esi\n\t"
      "jmp .LFUN_00149ce0_38\n\t"
      ".LFUN_00149ce0_37:\n\t"
      "andl $0xffefffff, %%esi\n\t"
      ".LFUN_00149ce0_38:\n\t"
      "movb 0x5a8d0d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_39\n\t"
      "orl $0x200000, %%esi\n\t"
      "jmp .LFUN_00149ce0_40\n\t"
      ".LFUN_00149ce0_39:\n\t"
      "andl $0xffdfffff, %%esi\n\t"
      ".LFUN_00149ce0_40:\n\t"
      "movb 0x5a8d0c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_41\n\t"
      "orl $0x400000, %%esi\n\t"
      "jmp .LFUN_00149ce0_42\n\t"
      ".LFUN_00149ce0_41:\n\t"
      "andl $0xffbfffff, %%esi\n\t"
      ".LFUN_00149ce0_42:\n\t"
      "movl 0x5a8ccc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_00149ce0_43\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      ".LFUN_00149ce0_43:\n\t"
      "movb 0x5a8d1c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_46\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x506548, %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00149ce0_44\n\t"
      "movl %%eax, 0x324fc8\n\t"
      "jmp .LFUN_00149ce0_45\n\t"
      ".LFUN_00149ce0_44:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x506548, %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0x324fc8\n\t"
      ".LFUN_00149ce0_45:\n\t"
      "movl 0x506550, %%ecx\n\t"
      "movl 0x506554, %%edx\n\t"
      "movl 0x506558, %%eax\n\t"
      "movl %%ecx, 0x5a8d00\n\t"
      "movl 0x50655c, %%ecx\n\t"
      "movl %%edx, 0x5a8d04\n\t"
      "movl 0x506560, %%edx\n\t"
      "movl %%eax, 0x5a8d08\n\t"
      "movl 0x506564, %%eax\n\t"
      "movl %%ecx, 0x5a8cf0\n\t"
      "movl %%edx, 0x5a8cf4\n\t"
      "movl %%eax, 0x5a8cf8\n\t"
      ".LFUN_00149ce0_46:\n\t"
      "movl 0x5a8d00, %%ecx\n\t"
      "flds 0x324fc4\n\t"
      "movl 0x5a8d04, %%edx\n\t"
      "fabs\n\t"
      "movl 0x5a8d08, %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x5a8cf0, %%ecx\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x5a8cf4, %%edx\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "movl 0x5a8cf8, %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movb 0x4761c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "flds -0x40(%%ebp)\n\t"
      "movl 0x324fc8, %%ebx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x4c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_00149ce0_50\n\t"
      "leal -0x538(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1459e0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "call *%[gbsp]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c149480]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_47\n\t"
      "flds -0x48(%%ebp)\n\t"
      "leal -0xb528(%%ebp), %%ecx\n\t"
      "fmuls -0x538(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x3c23d70a\n\t"
      "fadds -0x30(%%ebp)\n\t"
      "pushl $0\n\t"
      "pushl $0x3c23d70a\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x44(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fmuls -0x538(%%ebp)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x538(%%ebp)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "call *%[c4ec30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_47\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movb $1, 0x4761c1\n\t"
      "movl %%eax, 0x5a8cc0\n\t"
      "movl %%ecx, 0x5a8cc4\n\t"
      "movl %%edx, 0x5a8cc8\n\t"
      "jmp .LFUN_00149ce0_48\n\t"
      ".LFUN_00149ce0_47:\n\t"
      "movb 0x4761c1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_50\n\t"
      ".LFUN_00149ce0_48:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x26e2f4\n\t"
      "fldl 0x29ce70\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x29ce68\n\t"
      "fldl 0x29ce70\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x29ce64\n\t"
      "fldl 0x29ce70\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0x2ee6e8, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29ce58\n\t"
      "pushl $0x5a8cc0\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109e90]\n\t"
      "addl $0x20, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $8, %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00149ce0_49:\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x29cd78(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x256140\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0xc, %%esi\n\t"
      "decl %%edi\n\t"
      "fadds 0x5a8cc0\n\t"
      "fstps -0x12c(%%ebp,%%esi,1)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x256140\n\t"
      "fadds 0x5a8cc4\n\t"
      "fstps -0x128(%%ebp,%%esi,1)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x256140\n\t"
      "fadds 0x5a8cc8\n\t"
      "fstps -0x124(%%ebp,%%esi,1)\n\t"
      "jne .LFUN_00149ce0_49\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xfc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xfc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xf0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xcc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xe4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xcc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xf0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xd8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "leal -0xf0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xcc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xfc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "addl $0x40, %%esp\n\t"
      ".LFUN_00149ce0_50:\n\t"
      "movb 0x5a8d1f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_71\n\t"
      "flds 0x324fc4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_54\n\t"
      "flds -0x30(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "fadds -0x48(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fadds -0x44(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x4761b8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_52\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_51\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3dcccccd\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_51:\n\t"
      "movl 0x2ee6d4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3dcccccd\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_52:\n\t"
      "movl 0x4761b8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c4dab0]\n\t"
      "movl 0x4761b8, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "je .LFUN_00149ce0_53\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_53:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_54:\n\t"
      "flds 0x4761b8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_63\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_62\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "movl -0xac(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c189320]\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e000000\n\t"
      "leal -0xa8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e800000\n\t"
      "leal -0x9c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movw -0xc0(%%ebp), %%ax\n\t"
      "addl $0x38, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00149ce0_55\n\t"
      "call *%[gbsp]\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_00149ce0_56\n\t"
      ".LFUN_00149ce0_55:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_00149ce0_70\n\t"
      "cmpw $-1, -0x82(%%ebp)\n\t"
      "je .LFUN_00149ce0_70\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c14c8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_70\n\t"
      "movswl -0x82(%%ebp), %%edx\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "addl $0x28c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl -0x80(%%ebp), %%ecx\n\t"
      "pushl $0x60\n\t"
      "pushl %%ecx\n\t"
      "addl $0x34, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl -0x82(%%ebp), %%esi\n\t"
      "imull $0x34, %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "addl %%eax, %%esi\n\t"
      ".LFUN_00149ce0_56:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00149ce0_70\n\t"
      "movl -0x7c(%%ebp), %%edx\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "leal 0x3c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "movl -0x7c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[c1475f0]\n\t"
      "movb -0x74(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb $8, %%al\n\t"
      "movl $0x25386f, %%esi\n\t"
      "movl $0x29ce4c, -0x8(%%ebp)\n\t"
      "jne .LFUN_00149ce0_57\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      ".LFUN_00149ce0_57:\n\t"
      "testb $4, %%al\n\t"
      "movl $0x29ce40, -0xc(%%ebp)\n\t"
      "jne .LFUN_00149ce0_58\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      ".LFUN_00149ce0_58:\n\t"
      "testb $2, %%al\n\t"
      "movl $0x29ce34, %%ebx\n\t"
      "jne .LFUN_00149ce0_59\n\t"
      "movl %%esi, %%ebx\n\t"
      ".LFUN_00149ce0_59:\n\t"
      "testb $1, %%al\n\t"
      "movl $0x29ce28, %%edi\n\t"
      "jne .LFUN_00149ce0_60\n\t"
      "movl %%esi, %%edi\n\t"
      ".LFUN_00149ce0_60:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jns .LFUN_00149ce0_61\n\t"
      "movl $0x29ce1c, %%esi\n\t"
      ".LFUN_00149ce0_61:\n\t"
      "flds -0x94(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "fmuls 0x29ce18\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb5490]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x7c(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29cde4\n\t"
      "leal -0x920(%%ebp), %%ecx\n\t"
      "pushl $0x800\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "leal -0x920(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189c40]\n\t"
      "addl $0x3c, %%esp\n\t"
      "jmp .LFUN_00149ce0_70\n\t"
      ".LFUN_00149ce0_62:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e000000\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_63:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "flds 0x4761bc\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "testb $0x41, %%ah\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "jp .LFUN_00149ce0_64\n\t"
      "leal -0x3e0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4761b8, %%edx\n\t"
      "pushl $0xe\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1506d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_00149ce0_65\n\t"
      ".LFUN_00149ce0_64:\n\t"
      "leal -0x3e0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x4761b8, %%eax\n\t"
      "pushl $0xe\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4761bc, %%ecx\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c150550]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_00149ce0_65:\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0xe, %%di\n\t"
      "jle .LFUN_00149ce0_66\n\t"
      "pushl $1\n\t"
      "pushl $0x129\n\t"
      "pushl $0x29ce78\n\t"
      "pushl $0x29cdd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_66:\n\t"
      "movswl %%di, %%edx\n\t"
      "imull $0x2c, %%edx, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3e0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x3b4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dae0]\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $0x10\n\t"
      "movl %%edx, -0x3dc(%%ebp)\n\t"
      "leal -0x3d0(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x3d8(%%ebp)\n\t"
      "movl %%ecx, -0x3d4(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "imull $0x2c, %%eax, %%eax\n\t"
      "leal -0x3dc(%%ebp,%%eax,1), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x64(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x60(%%ebp), %%edx\n\t"
      "leal -0x3d0(%%ebp,%%eax,1), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[memset]\n\t"
      "addl $0x24, %%esp\n\t"
      "incl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00149ce0_69\n\t"
      "leal -0x3dc(%%ebp), %%esi\n\t"
      ".LFUN_00149ce0_67:\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3d800000\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_00149ce0_68\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0x2c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00149ce0_68:\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e000000\n\t"
      "leal 0xc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%ebx\n\t"
      "addl $0x2c, %%esi\n\t"
      "cmpw %%di, %%bx\n\t"
      "jl .LFUN_00149ce0_67\n\t"
      ".LFUN_00149ce0_69:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_70:\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_00149ce0_71:\n\t"
      "movb 0x5a8d1e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_88\n\t"
      "flds 0x324fc4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_78\n\t"
      "flds 0x50655c\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x506550\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x506560\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x506554\n\t"
      "flds 0x506564\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x506558\n\t"
      "flds 0x268ed0\n\t"
      "fsubr %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fadds 0x268ed0\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_87\n\t"
      "flds 0x268ed0\n\t"
      "fsubr %%st(1), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fadds 0x268ed0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00149ce0_72:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_77\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs 0x268ed0\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fadds 0x268ed0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00149ce0_73:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_76\n\t"
      ".LFUN_00149ce0_74:\n\t"
      "pushl $-1\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "jne .LFUN_00149ce0_75\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      ".LFUN_00149ce0_75:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d800000\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x255d90\n\t"
      "addl $0x10, %%esp\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149ce0_74\n\t"
      ".LFUN_00149ce0_76:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x255d90\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149ce0_73\n\t"
      ".LFUN_00149ce0_77:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x255d90\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149ce0_72\n\t"
      "jmp .LFUN_00149ce0_88\n\t"
      ".LFUN_00149ce0_78:\n\t"
      "movb 0x5a8d1c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_83\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5065a4\n\t"
      "call *%[c185f80]\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs -0x5c(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "fmuls 0x324fc4\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5065e8\n\t"
      "fmuls 0x25afc0\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0, -0x68(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl $0, -0x60(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fsubs -0x54(%%ebp)\n\t"
      "fmuls 0x324fc4\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls 0x324fc4\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls 0x324fc4\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x324fc4\n\t"
      "fchs\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "call *%[mscale]\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5065e8\n\t"
      "call *%[mscale]\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5065e8\n\t"
      "call *%[mscale]\n\t"
      "addl $0x2c, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl $0x1e, -0x4(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00149ce0_79:\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl $0, -0x6c(%%ebp)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "subl %%esi, %%ebx\n\t"
      "movl $0x28, -0x20(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00149ce0_80:\n\t"
      "fildl -0x6c(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "flds -0x70(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls -0x68(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x506550\n\t"
      ".byte 0xde, 0xc1\n\t"
      "pushl %%ecx\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x64(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_81\n\t"
      "movl %%esi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal 0x476120(,%%edx,4), %%eax\n\t"
      "leal (%%ebx,%%esi,1), %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl -0xa4(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0xa8(%%ebp), %%ecx\n\t"
      "leal 0x4728e0(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0xa0(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x9c(%%ebp), %%eax\n\t"
      "movl -0x98(%%ebp), %%ecx\n\t"
      "leal 0x46f0a0(%%edi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .LFUN_00149ce0_82\n\t"
      ".LFUN_00149ce0_81:\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "leal 0x476120(,%%ecx,4), %%eax\n\t"
      "leal (%%ebx,%%esi,1), %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "notl %%edx\n\t"
      "andl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_00149ce0_82:\n\t"
      "incl -0x6c(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "addl $0xc, %%edi\n\t"
      "incl %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .LFUN_00149ce0_80\n\t"
      "movl -0x24(%%ebp), %%esi\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "addl $8, %%edx\n\t"
      "addl $0x28, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_00149ce0_79\n\t"
      ".LFUN_00149ce0_83:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl $0x1e, -0xc(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00149ce0_84:\n\t"
      "subl %%ebx, %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl $0x28, -0x4(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00149ce0_85:\n\t"
      "leal (%%eax,%%ebx,1), %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, 0x476120(,%%ecx,4)\n\t"
      "je .LFUN_00149ce0_86\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3d000000\n\t"
      "leal 0x4728e0(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d800000\n\t"
      "leal 0x46f0a0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_00149ce0_86:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esi\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00149ce0_85\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "addl $0x28, %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jne .LFUN_00149ce0_84\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "jmp .LFUN_00149ce0_88\n\t"
      ".LFUN_00149ce0_87:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00149ce0_88:\n\t"
      "movb 0x5a8d1d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00149ce0_89\n\t"
      "flds 0x5a8cf0\n\t"
      "movl 0x324fc8, %%eax\n\t"
      "fmuls 0x253398\n\t"
      "movl 0x4761b8, %%ecx\n\t"
      "leal -0xb528(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds 0x5a8d00\n\t"
      "movl 0x4761bc, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x5a8cf4\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "fmuls 0x253398\n\t"
      "fadds 0x5a8d04\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds 0x4761bc\n\t"
      "fmuls 0x253398\n\t"
      "flds 0x5a8cf8\n\t"
      "fmuls 0x253398\n\t"
      "fadds 0x5a8d08\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds 0x5a8cf8\n\t"
      "fmuls 0x5a8cf8\n\t"
      "flds 0x5a8cf4\n\t"
      "fmuls 0x5a8cf4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a8cf0\n\t"
      "fmuls 0x5a8cf0\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fmuls 0x253398\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fadds 0x4761b8\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c4ec30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_89\n\t"
      "leal -0xb528(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c14c7b0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00149ce0_89:\n\t"
      "popl %%esi\n\t"
      ".LFUN_00149ce0_90:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_00149ce0_91\n\t"
      "pushl $1\n\t"
      "pushl $0x1bb\n\t"
      "pushl $0x29ce78\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_91:\n\t"
      "decw 0x4761d8\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b149ce0_chkstk), [assert] "m"(b149ce0_assert), [exitfn] "m"(b149ce0_exitfn), [cba3c0] "m"(b149ce0_cba3c0), [dget] "m"(b149ce0_dget), [c1459e0] "m"(b149ce0_c1459e0), [gbsp] "m"(b149ce0_gbsp), [c149480] "m"(b149ce0_c149480), [c4ec30] "m"(b149ce0_c4ec30), [gtime] "m"(b149ce0_gtime), [c1daf7e] "m"(b149ce0_c1daf7e), [c189cb0] "m"(b149ce0_c189cb0), [c109e90] "m"(b149ce0_c109e90), [mscale] "m"(b149ce0_mscale), [c189270] "m"(b149ce0_c189270), [c4dc30] "m"(b149ce0_c4dc30), [c189150] "m"(b149ce0_c189150), [c4dab0] "m"(b149ce0_c4dab0), [c189540] "m"(b149ce0_c189540), [ray] "m"(b149ce0_ray), [c189320] "m"(b149ce0_c189320), [c14c8e0] "m"(b149ce0_c14c8e0), [elem] "m"(b149ce0_elem), [c1475f0] "m"(b149ce0_c1475f0), [c1d94f0] "m"(b149ce0_c1d94f0), [cb5490] "m"(b149ce0_cb5490), [c1d9179] "m"(b149ce0_c1d9179), [c189c40] "m"(b149ce0_c189c40), [c1506d0] "m"(b149ce0_c1506d0), [c150550] "m"(b149ce0_c150550), [c8dae0] "m"(b149ce0_c8dae0), [memset] "m"(b149ce0_memset), [c185f80] "m"(b149ce0_c185f80), [c14c7b0] "m"(b149ce0_c14c7b0)
      : "memory");
}
#else
#error "FUN_00149ce0: clang naked draft required"
#endif


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
void FUN_00150ed0(void *phys_state, void *buffer_a, void *buffer_b, float *out_force, float *out_aux)
{
  (void)phys_state;
  (void)buffer_a;
  (void)buffer_b;
  (void)out_force;
  (void)out_aux;
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

/* physics_compute_biped_collision (0x151a50) — XBE naked draft (batch 224). */
#if defined(__clang__)
static void (*const b151a50_chkstk)(void) = FUN_001d90e0;
static void (*const b151a50_c1a0890)(int unit_handle, vector3_t *out_pos, float *out_height_offset, float *out_camera_height) = biped_get_camera_height_and_offset;
static bool (*const b151a50_c14c950)(int param_1, void *param_2) = FUN_0014c950;
static void (*const b151a50_c14ad40)(void *features) = collision_features_init;
static char (*const b151a50_c14cde0)(int param_1, int param_2, float param_3, int param_4, int param_5, int param_6) = FUN_0014cde0;
static bool (*const b151a50_c14bc10)(void *features, void *los_data, void *out_hit) = collision_features_test_los;
static void *(*const b151a50_get)(int, int) = object_get_and_verify_type;
static float (*const b151a50_norm)(float *) = normalize3d;
static void (*const b151a50_c1a4a70)(int handle, float *velocity) = FUN_001a4a70;
static char (*const b151a50_c14f020)(uint32_t collision_flags, float *point, float vertical_extent, float p4, float p5, int unit_handle, float *point_out) = FUN_0014f020;
static void (*const b151a50_otrans)(int, float *, void *) = object_translate;
static int (*const b151a50_gtime)(void) = game_time_get;
static float (*const b151a50_c121a0)(const float *a, const float *b) = distance_squared3d;
static void * (*const b151a50_c18e450)(void) = game_globals_get;
static void *(*const b151a50_elem)(void *, int, int) = tag_block_get_element;
static void (*const b151a50_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b151a50_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static void *(*const b151a50_tag)(int, int) = tag_get;
static void (*const b151a50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b151a50_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char physics_compute_biped_collision(void *physics_ctx __attribute__((unused)), int biped_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0xac98, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1a0890]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c14c950]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lphysics_compute_biped_collision_3\n\t"
      "leal -0xac98(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c14ad40]\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs 0x282124\n\t"
      "fcoms 0x282124\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lphysics_compute_biped_collision_1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jmp .Lphysics_compute_biped_collision_2\n\t"
      ".Lphysics_compute_biped_collision_1:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3c800000, -0x10(%%ebp)\n\t"
      ".Lphysics_compute_biped_collision_2:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "leal -0xac98(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c14cde0]\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xac98(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c14bc10]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lphysics_compute_biped_collision_14\n\t"
      ".Lphysics_compute_biped_collision_3:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x30(%%ebp)\n\t"
      "call *%[get]\n\t"
      "flds 0x20(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "leal 0x18(%%ebx), %%esi\n\t"
      "flds (%%esi)\n\t"
      "leal 0x50(%%eax), %%edi\n\t"
      "fld %%st(0)\n\t"
      "addl $0x50, %%ebx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "fld %%st(2)\n\t"
      "pushl %%ecx\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%edi)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fadds 0x2533f0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x18, %%esp\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x25496c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lphysics_compute_biped_collision_4\n\t"
      "flds -0x10(%%ebp)\n\t"
      "jmp .Lphysics_compute_biped_collision_5\n\t"
      ".Lphysics_compute_biped_collision_4:\n\t"
      "flds 0x25496c\n\t"
      ".Lphysics_compute_biped_collision_5:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c1a4a70]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x20c3a0\n\t"
      "call *%[c14f020]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lphysics_compute_biped_collision_7\n\t"
      "flds -0x88(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "pushl $0\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "call *%[otrans]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x2dc(%%edx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .Lphysics_compute_biped_collision_6\n\t"
      "call *%[gtime]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl 0x2e0(%%ecx), %%edx\n\t"
      "addl $0x5a, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jle .Lphysics_compute_biped_collision_13\n\t"
      ".Lphysics_compute_biped_collision_6:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x253d48\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lphysics_compute_biped_collision_7\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl $0x18, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x25620c\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lphysics_compute_biped_collision_13\n\t"
      ".Lphysics_compute_biped_collision_7:\n\t"
      "pushl $0x98\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x188, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x68(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .Lphysics_compute_biped_collision_10\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "movl 0x2d4(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "je .Lphysics_compute_biped_collision_8\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      ".Lphysics_compute_biped_collision_8:\n\t"
      "movl 0x68(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c136750]\n\t"
      "movl -0x80(%%ebp), %%edx\n\t"
      "orl $1, %%edx\n\t"
      "movl $0x3f800000, -0x44(%%ebp)\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "movl 0x70(%%esi), %%edx\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "movl 0x74(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lphysics_compute_biped_collision_9\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      ".Lphysics_compute_biped_collision_9:\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "movw 0x68(%%esi), %%cx\n\t"
      "movw %%cx, -0x74(%%ebp)\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c137d20]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lphysics_compute_biped_collision_10:\n\t"
      "cmpl $-1, 0x58(%%eax)\n\t"
      "je .Lphysics_compute_biped_collision_13\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c136750]\n\t"
      "movw 0x298(%%esi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lphysics_compute_biped_collision_11\n\t"
      "cmpw $3, %%ax\n\t"
      "jb .Lphysics_compute_biped_collision_12\n\t"
      ".Lphysics_compute_biped_collision_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x33e\n\t"
      "pushl $0x29d780\n\t"
      "pushl $0x29d7a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lphysics_compute_biped_collision_12:\n\t"
      "movswl 0x298(%%esi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "flds 0x32514c(,%%edx,4)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "pushl $0\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl $-1\n\t"
      "fmuls 0x255e94\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "fmuls 0x255e94\n\t"
      "pushl $-1\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x255e94\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lphysics_compute_biped_collision_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lphysics_compute_biped_collision_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [chkstk] "m"(b151a50_chkstk), [c1a0890] "m"(b151a50_c1a0890), [c14c950] "m"(b151a50_c14c950), [c14ad40] "m"(b151a50_c14ad40), [c14cde0] "m"(b151a50_c14cde0), [c14bc10] "m"(b151a50_c14bc10), [get] "m"(b151a50_get), [norm] "m"(b151a50_norm), [c1a4a70] "m"(b151a50_c1a4a70), [c14f020] "m"(b151a50_c14f020), [otrans] "m"(b151a50_otrans), [gtime] "m"(b151a50_gtime), [c121a0] "m"(b151a50_c121a0), [c18e450] "m"(b151a50_c18e450), [elem] "m"(b151a50_elem), [c136750] "m"(b151a50_c136750), [c137d20] "m"(b151a50_c137d20), [tag] "m"(b151a50_tag), [assert] "m"(b151a50_assert), [exitfn] "m"(b151a50_exitfn)
      : "memory");
}
#else
#error "physics_compute_biped_collision: clang naked draft required"
#endif


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

/* FUN_00152680 (0x152680) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void *(*const b152680_get)(int, int) = object_get_and_verify_type;
static void (*const b152680_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b152680_exitfn)(int) = system_exit;
static int (*const b152680_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b152680_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b152680_c10a2c0)(float *out, float *forward, float *up) = FUN_0010a2c0;
static void *(*const b152680_elem)(void *, int, int) = tag_block_get_element;
static void (*const b152680_c109c70)(float *a, float *b, float *out) = FUN_00109c70;
static void (*const b152680_c1099f0)(float *src, float *dst) = FUN_001099f0;
static void (*const b152680_c109d90)(float *m, float *v, float *out) = FUN_00109d90;
static void (*const b152680_c1524d0)(void) = physics_compute_vehicle_collision;
static void (*const b152680_c143ae0)(int object_handle, float *position, float *forward, float *up) = object_set_position;
static void (*const b152680_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void (*const b152680_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static bool (*const b152680_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;

__attribute__((naked, noinline))
void FUN_00152680(void *phys_state __attribute__((unused)), void *buffer_a __attribute__((unused)), void *buffer_b __attribute__((unused)), float *force __attribute__((unused)), float *aux __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x19c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "movl %%eax, %%esi\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00152680_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3da\n\t"
      "pushl $0x29d780\n\t"
      "pushl $0x29d8d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152680_1:\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x8(%%edx)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00152680_2\n\t"
      "flds -0x24(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3de\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d8b8\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152680_2:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "fadds (%%eax)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00152680_3\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3e2\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d8a4\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152680_3:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fadds 0xc(%%esi)\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "leal -0x14c(%%ebp), %%edx\n\t"
      "fadds 0x10(%%esi)\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, -0x80(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[c10a2c0]\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x24\n\t"
      "addl $0x5c, %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x14c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109c70]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1099f0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109c70]\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109d90]\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00152680_4\n\t"
      "flds -0x34(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3f0\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d88c\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152680_4:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "addl $0x3c, %%esi\n\t"
      "fadds (%%esi)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, -0x48(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00152680_5\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3f4\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d878\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152680_5:\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal -0x8c(%%ebp), %%esi\n\t"
      "leal -0x98(%%ebp), %%edi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "call *%[c1524d0]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movb 0x4761fa, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00152680_6\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x98(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c143ae0]\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_00152680_19\n\t"
      ".LFUN_00152680_6:\n\t"
      "movl $4, -0x40(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00152680_7:\n\t"
      "movl -0x40(%%ebp), %%edi\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x98(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "decl %%edi\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd8(%%ebp), %%eax\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%eax\n\t"
      "movb $0, 0x17(%%ebp)\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "call *%[m4x3]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "flds 0x14(%%eax)\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "fchs\n\t"
      "pushl %%ecx\n\t"
      "flds 0x10(%%eax)\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "pushl %%edx\n\t"
      "flds 0xc(%%eax)\n\t"
      "leal -0xd8(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "pushl %%eax\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "movl -0x5c(%%ebp), %%eax\n\t"
      "movl -0x64(%%ebp), %%ecx\n\t"
      "movl -0x60(%%ebp), %%edx\n\t"
      "movl %%eax, -0xa8(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "addl $0x74, %%eax\n\t"
      "movl %%ecx, -0xb0(%%ebp)\n\t"
      "movl %%edx, -0xac(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%edi, -0x4c(%%ebp)\n\t"
      "jle .LFUN_00152680_17\n\t"
      ".LFUN_00152680_8:\n\t"
      "pushl $0x80\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%edi, %%esi\n\t"
      "imull $0x130, %%esi, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x38, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xd8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[xfrmpt]\n\t"
      "movl (%%ebx), %%edx\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "leal -0x19c(%%ebp), %%ecx\n\t"
      "fsubs (%%eax)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x70(%%ebp), %%ecx\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "pushl $0xc0a1\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0x9c(%%ebp)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00152680_10\n\t"
      "movb 0x17(%%ebp), %%al\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "je .LFUN_00152680_9\n\t"
      "flds -0x114(%%ebp)\n\t"
      "fcomps -0x188(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152680_10\n\t"
      ".LFUN_00152680_9:\n\t"
      "movl -0x6c(%%ebp), %%ecx\n\t"
      "movl -0x70(%%ebp), %%eax\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "movl $0x14, %%ecx\n\t"
      "leal -0x19c(%%ebp), %%esi\n\t"
      "leal -0x128(%%ebp), %%edi\n\t"
      "movb $1, 0x17(%%ebp)\n\t"
      "movl %%eax, -0x7c(%%ebp)\n\t"
      "movl %%edx, -0x74(%%ebp)\n\t"
      "rep movsl\n\t"
      ".LFUN_00152680_10:\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "incl %%ecx\n\t"
      "addl $0x74, %%eax\n\t"
      "movswl %%cx, %%edi\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "cmpl (%%eax), %%edi\n\t"
      "jl .LFUN_00152680_8\n\t"
      "movb 0x17(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00152680_16\n\t"
      "flds -0xfc(%%ebp)\n\t"
      "fmuls -0x74(%%ebp)\n\t"
      "flds -0x100(%%ebp)\n\t"
      "fmuls -0x78(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x104(%%ebp)\n\t"
      "fmuls -0x7c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152680_11\n\t"
      "fabs\n\t"
      "fdivrl 0x29d870\n\t"
      "jmp .LFUN_00152680_12\n\t"
      ".LFUN_00152680_11:\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x29d588\n\t"
      ".LFUN_00152680_12:\n\t"
      "fsubrs -0x114(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00152680_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00152680_13:\n\t"
      "flds -0x100(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0xfc(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x104(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00152680_14\n\t"
      "fld %%st(1)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "fsubs 0x2533c8\n\t"
      ".byte 0xde, 0xc9\n\t"
      "flds -0x104(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "flds -0x100(%%ebp)\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "flds -0xfc(%%ebp)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0xc(%%eax)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x10(%%eax)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x14(%%eax)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "jmp .LFUN_00152680_15\n\t"
      ".LFUN_00152680_14:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152680_15:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "leal -0x8c(%%ebp), %%esi\n\t"
      "leal -0x98(%%ebp), %%edi\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl %%eax, (%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "movl -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "call *%[c1524d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0, -0x40(%%ebp)\n\t"
      "jg .LFUN_00152680_7\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_00152680_18\n\t"
      ".LFUN_00152680_16:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00152680_17:\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "leal -0x98(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c143ae0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00152680_18:\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, 0x478(%%ebx)\n\t"
      ".LFUN_00152680_19:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl 0x74(%%eax), %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%edi, 0x14(%%ebp)\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jle .LFUN_00152680_21\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00152680_20:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "imull $0x130, %%eax, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%eax), %%dl\n\t"
      "movl (%%eax), %%eax\n\t"
      "andl $1, %%edx\n\t"
      "addl %%edx, %%edi\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $2, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "movl %%ebx, 0x14(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "shrl $3, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jl .LFUN_00152680_20\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      ".LFUN_00152680_21:\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "popl %%edi\n\t"
      "jne .LFUN_00152680_22\n\t"
      "cmpw $3, 0x14(%%ebp)\n\t"
      "jl .LFUN_00152680_22\n\t"
      "cmpw $0, -0x1c(%%ebp)\n\t"
      "jne .LFUN_00152680_22\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25620c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00152680_22\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x29d868\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00152680_22\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x29d864\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00152680_22\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x29d860\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00152680_22\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "orl $0x20, %%eax\n\t"
      "jmp .LFUN_00152680_23\n\t"
      ".LFUN_00152680_22:\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      ".LFUN_00152680_23:\n\t"
      "cmpw $0, 0x14(%%ebp)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "jle .LFUN_00152680_24\n\t"
      "orl $2, %%eax\n\t"
      "jmp .LFUN_00152680_25\n\t"
      ".LFUN_00152680_24:\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      ".LFUN_00152680_25:\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "jle .LFUN_00152680_26\n\t"
      "orl $4, %%eax\n\t"
      "jmp .LFUN_00152680_27\n\t"
      ".LFUN_00152680_26:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".LFUN_00152680_27:\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "jle .LFUN_00152680_28\n\t"
      "orl $8, %%eax\n\t"
      "jmp .LFUN_00152680_29\n\t"
      ".LFUN_00152680_28:\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      ".LFUN_00152680_29:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl 0x74(%%eax), %%ecx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "jne .LFUN_00152680_30\n\t"
      "orl $0x10, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00152680_30:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b152680_get), [assert] "m"(b152680_assert), [exitfn] "m"(b152680_exitfn), [c84a10] "m"(b152680_c84a10), [c8d9d0] "m"(b152680_c8d9d0), [c10a2c0] "m"(b152680_c10a2c0), [elem] "m"(b152680_elem), [c109c70] "m"(b152680_c109c70), [c1099f0] "m"(b152680_c1099f0), [c109d90] "m"(b152680_c109d90), [c1524d0] "m"(b152680_c1524d0), [c143ae0] "m"(b152680_c143ae0), [m4x3] "m"(b152680_m4x3), [xfrmpt] "m"(b152680_xfrmpt), [ray] "m"(b152680_ray)
      : "memory");
}
#else
#error "FUN_00152680: clang naked draft required"
#endif


/* FUN_00152e40 (0x152e40) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void *(*const b152e40_get)(int, int) = object_get_and_verify_type;
static void *(*const b152e40_tag)(int, int) = tag_get;
static void (*const b152e40_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void (*const b152e40_c1093b0)(float *out, float *q) = FUN_001093b0;
static void (*const b152e40_c109120)(float *m) = FUN_00109120;
static void *(*const b152e40_memset)(void *, int, unsigned int) = csmemset;
static char * (*const b152e40_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b152e40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b152e40_exitfn)(int) = system_exit;
static void *(*const b152e40_elem)(void *, int, int) = tag_block_get_element;
static void (*const b152e40_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b152e40_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static void (*const b152e40_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static void (*const b152e40_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void (*const b152e40_c150c80)(void) = compute_ground_plane;
static float (*const b152e40_f8510)(void *, void *) = FUN_0018f510;
static void (*const b152e40_c150710)(void) = FUN_00150710;
static void (*const b152e40_c150dd0)(void) = friction_evaluate;
static bool (*const b152e40_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b152e40_c18f230)(void *param_1, void *param_2, void *param_3, void *param_4) = FUN_0018f230;
static void (*const b152e40_otrans)(int, float *, void *) = object_translate;
static void (*const b152e40_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;

__attribute__((naked, noinline))
void FUN_00152e40(int object_handle __attribute__((unused)), void *buffer_a __attribute__((unused)), void *buffer_b __attribute__((unused)), float *force __attribute__((unused)), float *aux __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x16c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "movl %%esi, -0x68(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x8c(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x70687973\n\t"
      "call *%[tag]\n\t"
      "flds 0x32512c\n\t"
      "movl %%eax, %%edi\n\t"
      "fmuls 0x1c(%%edi)\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "leal 0xc(%%esi), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edx\n\t"
      "leal -0x138(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0x50(%%ebp)\n\t"
      "movl %%ebx, -0x44(%%ebp)\n\t"
      "movl %%ebx, -0x48(%%ebp)\n\t"
      "movl %%ebx, -0x4c(%%ebp)\n\t"
      "call *%[m4x3]\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "fchs\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x30(%%ebp)\n\t"
      "movl %%ebx, -0x2c(%%ebp)\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "movl %%ebx, -0x3c(%%ebp)\n\t"
      "movl %%ebx, -0x38(%%ebp)\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "je .LFUN_00152e40_2\n\t"
      "movl 0x68(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ebx, -0x40(%%ebp)\n\t"
      "jle .LFUN_00152e40_2\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00152e40_1:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "leal 0x2c(%%eax), %%ebx\n\t"
      "addl $0x1c, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1093b0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c109120]\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "movl 0x68(%%edi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00152e40_1\n\t"
      ".LFUN_00152e40_2:\n\t"
      "movl 0x74(%%edi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "imull $0x130, %%ecx, %%ecx\n\t"
      "leal 0x74(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00152e40_5\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "je .LFUN_00152e40_3\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      "je .LFUN_00152e40_3\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .LFUN_00152e40_4\n\t"
      ".LFUN_00152e40_3:\n\t"
      "flds 0x8(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x4e7\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d948\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152e40_4:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      ".LFUN_00152e40_5:\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00152e40_8\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      "je .LFUN_00152e40_6\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "je .LFUN_00152e40_6\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "jne .LFUN_00152e40_7\n\t"
      ".LFUN_00152e40_6:\n\t"
      "flds 0x8(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x4ed\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d938\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152e40_7:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_00152e40_8:\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "cmpl $0, (%%edx)\n\t"
      "movl $0, -0x64(%%ebp)\n\t"
      "jle .LFUN_00152e40_40\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00152e40_9:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl $0x80\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "imull $0x130, %%edi, %%edi\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x20(%%ebx), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%edx, %%edi\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00152e40_10\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00152e40_10\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0x80\n\t"
      "pushl %%ecx\n\t"
      "addl $0x68, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "je .LFUN_00152e40_11\n\t"
      "movswl 0x20(%%ebx), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "jmp .LFUN_00152e40_12\n\t"
      ".LFUN_00152e40_10:\n\t"
      "movl $0, 0x18(%%ebp)\n\t"
      ".LFUN_00152e40_11:\n\t"
      "movl $0, 0x14(%%ebp)\n\t"
      ".LFUN_00152e40_12:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl $0, (%%edi)\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "leal 0x4(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x138(%%ebp), %%ecx\n\t"
      "fstps -0x9c(%%ebp)\n\t"
      "flds 0x3c(%%ebx)\n\t"
      "fsubs 0x10(%%eax)\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "flds 0x40(%%ebx)\n\t"
      "fsubs 0x14(%%eax)\n\t"
      "leal -0x9c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "leal -0x138(%%ebp), %%ecx\n\t"
      "je .LFUN_00152e40_13\n\t"
      "leal -0x16c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x2c, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109850]\n\t"
      "leal 0x10(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x44(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x16c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109680]\n\t"
      "leal 0x28(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x16c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109680]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_00152e40_14\n\t"
      ".LFUN_00152e40_13:\n\t"
      "leal 0x10(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x44(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109680]\n\t"
      "leal 0x28(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x138(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109680]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00152e40_14:\n\t"
      "leal 0x34(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c18f180]\n\t"
      "flds (%%esi)\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "fstps 0x3c(%%edi)\n\t"
      "movl %%edi, %%ecx\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x10(%%eax)\n\t"
      "fstps 0x40(%%edi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x14(%%eax)\n\t"
      "fstps 0x44(%%edi)\n\t"
      "flds 0x3c(%%eax)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "flds 0x3c(%%edi)\n\t"
      "fmuls 0x40(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x3c(%%edi)\n\t"
      "fmuls 0x44(%%eax)\n\t"
      "flds 0x3c(%%eax)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x40(%%eax)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      "flds 0x40(%%edi)\n\t"
      "fmuls 0x44(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x48(%%edi)\n\t"
      "fstps 0x4c(%%edi)\n\t"
      "fstps 0x50(%%edi)\n\t"
      "flds 0x48(%%edi)\n\t"
      "fadds 0x18(%%eax)\n\t"
      "fstps 0x48(%%edi)\n\t"
      "flds 0x4c(%%edi)\n\t"
      "fadds 0x1c(%%eax)\n\t"
      "fstps 0x4c(%%edi)\n\t"
      "flds 0x50(%%edi)\n\t"
      "fadds 0x20(%%eax)\n\t"
      "fstps 0x50(%%edi)\n\t"
      "call *%[c150c80]\n\t"
      "leal 0x34(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[f8510]\n\t"
      "fstps 0x7c(%%edi)\n\t"
      "flds 0x74(%%edi)\n\t"
      "addl $0x18, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_20\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "flds 0x24(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_20\n\t"
      "flds 0x50(%%edi)\n\t"
      "movl %%edx, %%eax\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "leal 0x90(%%edi), %%esi\n\t"
      "flds 0x4c(%%edi)\n\t"
      "fmuls 0x64(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x48(%%edi)\n\t"
      "fmuls 0x60(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x32512c\n\t"
      "fdivs 0x24(%%eax)\n\t"
      "fmuls 0x74(%%edi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x28(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fsts 0x80(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x60(%%edi)\n\t"
      "fstps 0x84(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x64(%%edi)\n\t"
      "fstps 0x88(%%edi)\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "fstps 0x8c(%%edi)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fmuls 0x20(%%eax)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "fchs\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x60(%%edi)\n\t"
      "fadds 0x48(%%edi)\n\t"
      "fstps 0x54(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x64(%%edi)\n\t"
      "fadds 0x4c(%%edi)\n\t"
      "fstps 0x58(%%edi)\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "fadds 0x50(%%edi)\n\t"
      "fstps 0x5c(%%edi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x54(%%edi)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x58(%%edi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x5c(%%edi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "je .LFUN_00152e40_17\n\t"
      "testb $1, 0x20(%%eax)\n\t"
      "je .LFUN_00152e40_17\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_17\n\t"
      "movl %%edx, %%eax\n\t"
      "movl 0x2c(%%eax), %%ecx\n\t"
      "movl 0x30(%%eax), %%edx\n\t"
      "movl 0x68(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c150710]\n\t"
      "flds 0x30(%%edi)\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x2c(%%edi)\n\t"
      "fmuls 0x64(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x60(%%edi)\n\t"
      "fmuls 0x28(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00152e40_15\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00152e40_16\n\t"
      ".LFUN_00152e40_15:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_16\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00152e40_16:\n\t"
      "fld %%st(0)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xca\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstp %%st(1)\n\t"
      "flds (%%ecx)\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fsts -0x54(%%ebp)\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls 0x64(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x60(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x60(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x64(%%edi)\n\t"
      "fadds -0x58(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "fadds -0x54(%%ebp)\n\t"
      "fstps -0xac(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fadds 0x54(%%edi)\n\t"
      "fstps 0x54(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fadds 0x58(%%edi)\n\t"
      "fstps 0x58(%%edi)\n\t"
      "flds -0xac(%%ebp)\n\t"
      "fadds 0x5c(%%edi)\n\t"
      "fstps 0x5c(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0xac(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_17:\n\t"
      "cmpw $0x1f, 0x70(%%edi)\n\t"
      "leal 0x10(%%edi), %%ecx\n\t"
      "je .LFUN_00152e40_18\n\t"
      "movl 0x64(%%ebx), %%edx\n\t"
      "movl 0x60(%%ebx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_00152e40_19\n\t"
      ".LFUN_00152e40_18:\n\t"
      "flds 0x64(%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fmuls 0x268ed0\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x60(%%ebx)\n\t"
      "fmuls 0x268ed0\n\t"
      "fstps (%%esp)\n\t"
      ".LFUN_00152e40_19:\n\t"
      "movw 0x5c(%%ebx), %%ax\n\t"
      "leal 0x28(%%edi), %%edx\n\t"
      "call *%[c150dd0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00152e40_20:\n\t"
      "flds 0x7c(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_26\n\t"
      "flds 0x7c(%%edi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fcomps 0x3c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00152e40_21\n\t"
      "flds 0x7c(%%edi)\n\t"
      "fdivs 0x3c(%%ecx)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "jmp .LFUN_00152e40_22\n\t"
      ".LFUN_00152e40_21:\n\t"
      "movl $0x3f800000, -0x40(%%ebp)\n\t"
      ".LFUN_00152e40_22:\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_23\n\t"
      "flds 0x3c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_23\n\t"
      "flds 0x40(%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "fdivs 0x34(%%ebx)\n\t"
      "fmuls 0x2c(%%ebx)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "fmuls -0x60(%%ebp)\n\t"
      "fsts 0xb4(%%edi)\n\t"
      "movl %%eax, 0xb8(%%edi)\n\t"
      "fstps 0xc0(%%edi)\n\t"
      "movl %%eax, 0xbc(%%edi)\n\t"
      ".LFUN_00152e40_23:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00152e40_24\n\t"
      "testb $2, 0x20(%%eax)\n\t"
      "je .LFUN_00152e40_24\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "flds 0x4(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_24\n\t"
      "flds 0x4(%%edx)\n\t"
      "leal 0xc4(%%edi), %%esi\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fadds 0x48(%%edi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fadds 0x4c(%%edi)\n\t"
      "fstps -0xa4(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fadds 0x50(%%edi)\n\t"
      "fstps -0xa0(%%ebp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fmuls 0x38(%%ecx)\n\t"
      "fchs\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps (%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "jmp .LFUN_00152e40_25\n\t"
      ".LFUN_00152e40_24:\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "leal 0xc4(%%edi), %%esi\n\t"
      "fmuls 0x38(%%ecx)\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x48(%%edi)\n\t"
      "fstps (%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4c(%%edi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fmuls 0x50(%%edi)\n\t"
      ".LFUN_00152e40_25:\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0x64(%%ebx), %%ecx\n\t"
      "movl 0x60(%%ebx), %%edx\n\t"
      "movw 0x5c(%%ebx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x28(%%edi), %%edx\n\t"
      "leal 0x10(%%edi), %%ecx\n\t"
      "call *%[c150dd0]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00152e40_27\n\t"
      "testb $8, 0x20(%%eax)\n\t"
      "je .LFUN_00152e40_26\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds 0xc(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_26\n\t"
      "flds 0x50(%%edi)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "flds 0x4c(%%edi)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x48(%%edi)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fabs\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "fmuls 0xc(%%ecx)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%edi)\n\t"
      "fadds 0x10c(%%edi)\n\t"
      "fstps 0x10c(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "fadds 0x110(%%edi)\n\t"
      "fstps 0x110(%%edi)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "fadds 0x114(%%edi)\n\t"
      "fstps 0x114(%%edi)\n\t"
      ".LFUN_00152e40_26:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00152e40_27\n\t"
      "testb $4, 0x20(%%eax)\n\t"
      "je .LFUN_00152e40_27\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_27\n\t"
      "flds 0x8(%%ecx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "leal 0xe8(%%edi), %%esi\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fadds 0x48(%%edi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fadds 0x4c(%%edi)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fadds 0x50(%%edi)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fmuls 0x48(%%edx)\n\t"
      "fchs\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps (%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "jmp .LFUN_00152e40_28\n\t"
      ".LFUN_00152e40_27:\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0x48(%%eax)\n\t"
      "leal 0xe8(%%edi), %%esi\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x48(%%edi)\n\t"
      "fstps (%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4c(%%edi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fmuls 0x50(%%edi)\n\t"
      ".LFUN_00152e40_28:\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0x64(%%ebx), %%ecx\n\t"
      "movl 0x60(%%ebx), %%edx\n\t"
      "movw 0x5c(%%ebx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x28(%%edi), %%edx\n\t"
      "leal 0x10(%%edi), %%ecx\n\t"
      "call *%[c150dd0]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LFUN_00152e40_29\n\t"
      "testb $0x10, 0x20(%%esi)\n\t"
      "je .LFUN_00152e40_29\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_29\n\t"
      "flds 0x50(%%edi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "flds 0x4c(%%edi)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x48(%%edi)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fabs\n\t"
      "fmuls 0x10(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%edi)\n\t"
      "fadds 0x10c(%%edi)\n\t"
      "fstps 0x10c(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "fadds 0x110(%%edi)\n\t"
      "fstps 0x110(%%edi)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "fadds 0x114(%%edi)\n\t"
      "fstps 0x114(%%edi)\n\t"
      ".LFUN_00152e40_29:\n\t"
      "flds 0x50(%%edi)\n\t"
      "fmuls 0x50(%%edi)\n\t"
      "flds 0x4c(%%edi)\n\t"
      "fmuls 0x4c(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x48(%%edi)\n\t"
      "fmuls 0x48(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25620c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "movl (%%edi), %%eax\n\t"
      "jp .LFUN_00152e40_30\n\t"
      "orl $1, %%eax\n\t"
      "jmp .LFUN_00152e40_31\n\t"
      ".LFUN_00152e40_30:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      ".LFUN_00152e40_31:\n\t"
      "flds 0x74(%%edi)\n\t"
      "movl %%eax, (%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "movl (%%edi), %%eax\n\t"
      "jne .LFUN_00152e40_32\n\t"
      "orl $2, %%eax\n\t"
      "jmp .LFUN_00152e40_33\n\t"
      ".LFUN_00152e40_32:\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      ".LFUN_00152e40_33:\n\t"
      "flds 0x7c(%%edi)\n\t"
      "movl %%eax, (%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "movl (%%edi), %%eax\n\t"
      "jne .LFUN_00152e40_34\n\t"
      "orl $8, %%eax\n\t"
      "jmp .LFUN_00152e40_35\n\t"
      ".LFUN_00152e40_34:\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      ".LFUN_00152e40_35:\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb %%al, %%cl\n\t"
      "movl %%eax, (%%edi)\n\t"
      "andl $1, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $2, %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "shrl $3, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "je .LFUN_00152e40_39\n\t"
      "testb $0x20, 0x20(%%esi)\n\t"
      "je .LFUN_00152e40_36\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "flds 0x14(%%edx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fadds 0x10c(%%edi)\n\t"
      "fstps 0x10c(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fadds 0x110(%%edi)\n\t"
      "fstps 0x110(%%edi)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fadds 0x114(%%edi)\n\t"
      "fstps 0x114(%%edi)\n\t"
      ".LFUN_00152e40_36:\n\t"
      "testb $0x40, 0x20(%%esi)\n\t"
      "je .LFUN_00152e40_39\n\t"
      "flds 0x2c(%%esi)\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "fadds 0x68(%%ebx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%eax, -0x7c(%%ebp)\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "fld %%st(0)\n\t"
      "movl %%ecx, -0x84(%%ebp)\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x104(%%ebp), %%ecx\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fld %%st(0)\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0x8c(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xc0a0\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00152e40_39\n\t"
      "flds 0x2c(%%esi)\n\t"
      "movl 0x34(%%esi), %%edx\n\t"
      "fadds 0x68(%%ebx)\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movl 0x30(%%edi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "fmuls -0xf0(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fsubs 0x68(%%ebx)\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "call *%[c150710]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00152e40_37\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fdivs 0x2c(%%esi)\n\t"
      "fsubrs 0x2533c8\n\t"
      "jmp .LFUN_00152e40_38\n\t"
      ".LFUN_00152e40_37:\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00152e40_38:\n\t"
      "fld %%st(0)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0x32512c\n\t"
      "flds -0xdc(%%ebp)\n\t"
      "fmuls 0x4c(%%edi)\n\t"
      "flds -0xd8(%%ebp)\n\t"
      "fmuls 0x50(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xe0(%%ebp)\n\t"
      "fmuls 0x48(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x30(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x18(%%edx)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      ".byte 0xde, 0xca\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fstp %%st(1)\n\t"
      "flds -0xe0(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x10c(%%edi)\n\t"
      "fstps 0x10c(%%edi)\n\t"
      "flds -0xdc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x110(%%edi)\n\t"
      "fstps 0x110(%%edi)\n\t"
      "flds -0xd8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x114(%%edi)\n\t"
      "fstps 0x114(%%edi)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_39:\n\t"
      "flds 0x84(%%edi)\n\t"
      "fadds 0x118(%%edi)\n\t"
      "fstps 0x118(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fadds 0x88(%%edi)\n\t"
      "fstps 0x11c(%%edi)\n\t"
      "flds 0x120(%%edi)\n\t"
      "fadds 0x8c(%%edi)\n\t"
      "fstps 0x120(%%edi)\n\t"
      "flds 0x118(%%edi)\n\t"
      "fadds 0x90(%%edi)\n\t"
      "fstps 0x118(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fadds 0x94(%%edi)\n\t"
      "fstps 0x11c(%%edi)\n\t"
      "flds 0x120(%%edi)\n\t"
      "fadds 0x98(%%edi)\n\t"
      "fstps 0x120(%%edi)\n\t"
      "flds 0x118(%%edi)\n\t"
      "fadds 0xb8(%%edi)\n\t"
      "fstps 0x118(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fadds 0xbc(%%edi)\n\t"
      "fstps 0x11c(%%edi)\n\t"
      "flds 0x120(%%edi)\n\t"
      "fadds 0xc0(%%edi)\n\t"
      "fstps 0x120(%%edi)\n\t"
      "flds 0x118(%%edi)\n\t"
      "fadds 0xc4(%%edi)\n\t"
      "fstps 0x118(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fadds 0xc8(%%edi)\n\t"
      "fstps 0x11c(%%edi)\n\t"
      "flds 0x120(%%edi)\n\t"
      "fadds 0xcc(%%edi)\n\t"
      "fstps 0x120(%%edi)\n\t"
      "flds 0x118(%%edi)\n\t"
      "fadds 0xe8(%%edi)\n\t"
      "fstps 0x118(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fadds 0xec(%%edi)\n\t"
      "fstps 0x11c(%%edi)\n\t"
      "flds 0x120(%%edi)\n\t"
      "fadds 0xf0(%%edi)\n\t"
      "fstps 0x120(%%edi)\n\t"
      "flds 0x10c(%%edi)\n\t"
      "fadds 0x118(%%edi)\n\t"
      "fstps 0x118(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fadds 0x110(%%edi)\n\t"
      "fstps 0x11c(%%edi)\n\t"
      "flds 0x120(%%edi)\n\t"
      "fadds 0x114(%%edi)\n\t"
      "fstps 0x120(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "flds 0x40(%%edi)\n\t"
      "fmuls 0x118(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x118(%%edi)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      "flds 0x3c(%%edi)\n\t"
      "fmuls 0x120(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x40(%%edi)\n\t"
      "fmuls 0x120(%%edi)\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x124(%%edi)\n\t"
      "fstps 0x128(%%edi)\n\t"
      "fstps 0x12c(%%edi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fadds 0x118(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x11c(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x120(%%edi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl -0x64(%%ebp), %%eax\n\t"
      "fadds 0x124(%%edi)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds 0x128(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x12c(%%edi)\n\t"
      "movswl %%ax, %%edi\n\t"
      "cmpl (%%ecx), %%edi\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jl .LFUN_00152e40_9\n\t"
      "movl -0x68(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_00152e40_40:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_41\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x8(%%edi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_41:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00152e40_43\n\t"
      "flds 0x2533c8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_44\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "cmpl $0, (%%edx)\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "movl $0, 0x14(%%ebp)\n\t"
      "jle .LFUN_00152e40_44\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_00152e40_42:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl $0x80\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "imull $0x130, %%ecx, %%ecx\n\t"
      "fmuls 0x44(%%ecx,%%edx,1)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x40(%%ecx,%%edx,1)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x3c(%%ecx,%%edx,1)\n\t"
      "addl %%edx, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x3c(%%ecx)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds 0x40(%%ecx)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fadds 0x44(%%ecx)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "flds 0x68(%%eax)\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(4)\n\t"
      "fmul %%st(5), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x253524\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x2c(%%eax)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "fadds 0xc(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "jl .LFUN_00152e40_42\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_44\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0xc(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      ".LFUN_00152e40_43:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_44:\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_00152e40_45\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_00152e40_45\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jne .LFUN_00152e40_46\n\t"
      ".LFUN_00152e40_45:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x603\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d91c\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152e40_46:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "fadds 0x18(%%esi)\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "fstps 0x18(%%esi)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fadds 0x1c(%%esi)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds 0x20(%%esi)\n\t"
      "fstps 0x20(%%esi)\n\t"
      "je .LFUN_00152e40_47\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_00152e40_47\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jne .LFUN_00152e40_48\n\t"
      ".LFUN_00152e40_47:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x607\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d88c\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152e40_48:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "leal 0x3c(%%esi), %%edi\n\t"
      "fadds (%%edi)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps (%%edi)\n\t"
      "pushl %%eax\n\t"
      "flds -0x38(%%ebp)\n\t"
      "leal -0x6c(%%ebp), %%ecx\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "flds (%%eax)\n\t"
      "fadds 0x18(%%esi)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fadds 0x1c(%%esi)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "fadds 0x20(%%esi)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "call *%[c18f230]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[otrans]\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "addl $0x1c, %%esp\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00152e40_52\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0xc(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00152e40_52\n\t"
      "flds 0xc(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fsin\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcos\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[rots]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x30(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[rots]\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "addl $0x20, %%esp\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00152e40_49\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "jmp .LFUN_00152e40_50\n\t"
      ".LFUN_00152e40_49:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_50:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fadds (%%ebx)\n\t"
      "fstps (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "flds (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00152e40_51\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ebx)\n\t"
      "fstps (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "jmp .LFUN_00152e40_52\n\t"
      ".LFUN_00152e40_51:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_52:\n\t"
      "movswl -0x50(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "cmpl (%%ecx), %%eax\n\t"
      "jne .LFUN_00152e40_53\n\t"
      "cmpw $3, -0x44(%%ebp)\n\t"
      "jl .LFUN_00152e40_53\n\t"
      "cmpw $0, -0x48(%%ebp)\n\t"
      "jne .LFUN_00152e40_53\n\t"
      "flds 0x20(%%esi)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25620c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_00152e40_53\n\t"
      "flds 0x44(%%esi)\n\t"
      "flds 0x40(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x29d868\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_00152e40_53\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x29d864\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00152e40_53\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x29d860\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00152e40_53\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "orl $0x20, %%eax\n\t"
      "jmp .LFUN_00152e40_54\n\t"
      ".LFUN_00152e40_53:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      ".LFUN_00152e40_54:\n\t"
      "cmpw $0, -0x44(%%ebp)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "jle .LFUN_00152e40_55\n\t"
      "orl $2, %%eax\n\t"
      "jmp .LFUN_00152e40_56\n\t"
      ".LFUN_00152e40_55:\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      ".LFUN_00152e40_56:\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "jle .LFUN_00152e40_57\n\t"
      "orl $4, %%edx\n\t"
      "jmp .LFUN_00152e40_58\n\t"
      ".LFUN_00152e40_57:\n\t"
      "andl $0xfffffffb, %%edx\n\t"
      ".LFUN_00152e40_58:\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "jle .LFUN_00152e40_59\n\t"
      "orl $8, %%edx\n\t"
      "jmp .LFUN_00152e40_60\n\t"
      ".LFUN_00152e40_59:\n\t"
      "andl $0xfffffff7, %%edx\n\t"
      ".LFUN_00152e40_60:\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl (%%ecx), %%edx\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "jne .LFUN_00152e40_61\n\t"
      "orl $0x10, %%eax\n\t"
      "jmp .LFUN_00152e40_62\n\t"
      ".LFUN_00152e40_61:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      ".LFUN_00152e40_62:\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "flds 0x28(%%esi)\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .LFUN_00152e40_63\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00152e40_64\n\t"
      "flds 0x38(%%esi)\n\t"
      "flds 0x34(%%esi)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .LFUN_00152e40_63\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00152e40_64\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .LFUN_00152e40_63\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00152e40_65\n\t"
      "jmp .LFUN_00152e40_64\n\t"
      ".LFUN_00152e40_63:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00152e40_64:\n\t"
      "flds 0x38(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x63b\n\t"
      "pushl $0x29d780\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ecx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29d908\n\t"
      "pushl $0x29d8f0\n\t"
      "pushl $0x267490\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00152e40_65:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b152e40_get), [tag] "m"(b152e40_tag), [m4x3] "m"(b152e40_m4x3), [c1093b0] "m"(b152e40_c1093b0), [c109120] "m"(b152e40_c109120), [memset] "m"(b152e40_memset), [c8d9d0] "m"(b152e40_c8d9d0), [assert] "m"(b152e40_assert), [exitfn] "m"(b152e40_exitfn), [elem] "m"(b152e40_elem), [xfrmpt] "m"(b152e40_xfrmpt), [c109850] "m"(b152e40_c109850), [c109680] "m"(b152e40_c109680), [c18f180] "m"(b152e40_c18f180), [c150c80] "m"(b152e40_c150c80), [f8510] "m"(b152e40_f8510), [c150710] "m"(b152e40_c150710), [c150dd0] "m"(b152e40_c150dd0), [ray] "m"(b152e40_ray), [c18f230] "m"(b152e40_c18f230), [otrans] "m"(b152e40_otrans), [rots] "m"(b152e40_rots)
      : "memory");
}
#else
#error "FUN_00152e40: clang naked draft required"
#endif


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

/* FUN_001579d0 (0x1579d0) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b1579d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1579d0_exitfn)(int) = system_exit;
static void (*const b1579d0_c99490)(float *plane, float *point, float *normal) = FUN_00099490;
static void __stdcall (*const b1579d0_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static unsigned int (*const b1579d0_cd1dd0)(float *color) = FUN_000d1dd0;
static void (*const b1579d0_c1e9680)(void) = D3DDevice_SetRenderState_FogColor;

__attribute__((naked, noinline))
void FUN_001579d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_001579d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5ac\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dc54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001579d0_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x14, %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl $0x5a5da8, %%edi\n\t"
      "rep movsl\n\t"
      "flds 0x5a5db8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jp .LFUN_001579d0_2\n\t"
      "movl $0x3f800000, 0x5a5db8\n\t"
      ".LFUN_001579d0_2:\n\t"
      "flds 0x5a5dc0\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001579d0_3\n\t"
      "movb 0x3256df, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001579d0_4\n\t"
      ".LFUN_001579d0_3:\n\t"
      "flds 0x5a5c08\n\t"
      "movl 0x5a5c08, %%eax\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "movl $0, 0x5a5db8\n\t"
      "movl %%eax, 0x5a5dbc\n\t"
      "fstps 0x5a5dc0\n\t"
      ".LFUN_001579d0_4:\n\t"
      "flds 0x5a5de4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001579d0_5\n\t"
      "movl $0x3f800000, 0x5a5de4\n\t"
      ".LFUN_001579d0_5:\n\t"
      "movw 0x5a5dc4, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001579d0_7\n\t"
      "testb $4, (%%ebx)\n\t"
      "jne .LFUN_001579d0_7\n\t"
      "movb 0x3256e0, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001579d0_7\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_001579d0_9\n\t"
      "flds 0x5a5de8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001579d0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x5da\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29f0f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001579d0_6:\n\t"
      "pushl $0x5a5bd4\n\t"
      "pushl $0x5a5bc8\n\t"
      "pushl $0x5a5dc8\n\t"
      "movl $0x3f800000, 0x5a5dec\n\t"
      "call *%[c99490]\n\t"
      "flds 0x5a5dd4\n\t"
      "fadds 0x5a5c08\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001579d0_8\n\t"
      ".LFUN_001579d0_7:\n\t"
      "flds 0x5a5bd0\n\t"
      "movl 0x2ee708, %%ecx\n\t"
      "fmuls 0x5a5bdc\n\t"
      "movw $0, 0x5a5dc4\n\t"
      "flds 0x5a5bcc\n\t"
      "movl $0, 0x5a5de4\n\t"
      "fmuls 0x5a5bd8\n\t"
      "movl $0x3f800000, 0x5a5de8\n\t"
      "movl $0x3f800000, 0x5a5dec\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0x5a5dd8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "flds 0x5a5bc8\n\t"
      "fmuls 0x5a5bd4\n\t"
      "movl 0x5a5bd4, %%edx\n\t"
      "movl %%eax, 0x5a5ddc\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl 0x5a5bd8, %%eax\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl %%ecx, 0x5a5de0\n\t"
      "movl 0x5a5bdc, %%ecx\n\t"
      "movl %%edx, 0x5a5dc8\n\t"
      "movl %%eax, 0x5a5dcc\n\t"
      "movl %%ecx, 0x5a5dd0\n\t"
      ".LFUN_001579d0_8:\n\t"
      "fstps 0x5a5dd4\n\t"
      ".LFUN_001579d0_9:\n\t"
      "flds 0x5a5dc0\n\t"
      "popl %%ebx\n\t"
      "fcomps 0x5a5dbc\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001579d0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x5e7\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29f080\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001579d0_10:\n\t"
      "flds 0x5a5de8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001579d0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x5e8\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29f040\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001579d0_11:\n\t"
      "flds 0x5a5dec\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001579d0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x5e9\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29f008\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001579d0_12:\n\t"
      "flds 0x5a5dc0\n\t"
      "fsubs 0x5a5dbc\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds 0x5a5bd0\n\t"
      "fmuls 0x5a5dd0\n\t"
      "flds 0x5a5bcc\n\t"
      "fmuls 0x5a5dcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bc8\n\t"
      "fmuls 0x5a5dc8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x5a5dd4\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fmuls 0x5a5bdc\n\t"
      "flds 0x5a5bcc\n\t"
      "fmuls 0x5a5bd8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bc8\n\t"
      "fmuls 0x5a5bd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x5a5de8\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x5a5dec\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x5a5bd4\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x5a5dbc\n\t"
      "fadd %%st(2), %%st(0)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fchs\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x5a5dc8\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds 0x5a5dcc\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x5a5dd0\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x5a5dd4\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x5a5bd4\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x5a5db8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001579d0_13\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001579d0_15\n\t"
      ".LFUN_001579d0_13:\n\t"
      "flds 0x5a5db8\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001579d0_14\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001579d0_15\n\t"
      ".LFUN_001579d0_14:\n\t"
      "movl 0x5a5db8, %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      ".LFUN_001579d0_15:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001579d0_16\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001579d0_18\n\t"
      ".LFUN_001579d0_16:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001579d0_17\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001579d0_18\n\t"
      ".LFUN_001579d0_17:\n\t"
      "fstps -0x10(%%ebp)\n\t"
      ".LFUN_001579d0_18:\n\t"
      "flds 0x5a5de4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001579d0_19\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001579d0_21\n\t"
      ".LFUN_001579d0_19:\n\t"
      "flds 0x5a5de4\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001579d0_20\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001579d0_21\n\t"
      ".LFUN_001579d0_20:\n\t"
      "movl 0x5a5de4, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_001579d0_21:\n\t"
      "pushl $4\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x58\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0x5a5dac\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e9680]\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1579d0_assert), [exitfn] "m"(b1579d0_exitfn), [c99490] "m"(b1579d0_c99490), [c1eb8d0] "m"(b1579d0_c1eb8d0), [cd1dd0] "m"(b1579d0_cd1dd0), [c1e9680] "m"(b1579d0_c1e9680)
      : "memory");
}
#else
#error "FUN_001579d0: clang naked draft required"
#endif


/* FUN_0015d8b0 (0x15d8b0) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b15d8b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15d8b0_exitfn)(int) = system_exit;
static int (*const b15d8b0_c180050)(short param_1) = FUN_00180050;
static void __stdcall (*const b15d8b0_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b15d8b0_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b15d8b0_c1e8920)(void) = D3DDevice_SetIndices;
static void (*const b15d8b0_c1ecf90)(void) = D3DDevice_DrawIndexedVertices;
static void (*const b15d8b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0015d8b0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0015d8b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2e5\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0015d8b0_25\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      ".LFUN_0015d8b0_2:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0015d8b0_24\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0015d8b0_24\n\t"
      "movl 0x47dbe8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0015d8b0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2f4\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0194\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .LFUN_0015d8b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2f7\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a07f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_4:\n\t"
      "cmpl 0x47dbe0, %%edi\n\t"
      "jl .LFUN_0015d8b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x2f8\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a07b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_5:\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_0015d8b0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x2f9\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a02d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_6:\n\t"
      "cmpl 0x47abd8, %%esi\n\t"
      "jl .LFUN_0015d8b0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x2fa\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0298\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_7:\n\t"
      "shll $4, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x476bd8, %%esi\n\t"
      "movw (%%esi), %%ax\n\t"
      "leal (%%edi,%%edi,2), %%ebx\n\t"
      "leal 0x47abe0(,%%ebx,4), %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c180050]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl (%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edi\n\t"
      "leal 0x476ae8(,%%edi,4), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0015d8b0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x1f8\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x26276c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_8:\n\t"
      "cmpl $0x476b60, %%edi\n\t"
      "jne .LFUN_0015d8b0_9\n\t"
      "movl 0x325668, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "je .LFUN_0015d8b0_9\n\t"
      "movl 0x47dbf0, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0015d8b0_10\n\t"
      ".LFUN_0015d8b0_9:\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_0015d8b0_10:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0015d8b0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x305\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a04d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_11:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0015d8b0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x308\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a04a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_12:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .LFUN_0015d8b0_13\n\t"
      "pushl $1\n\t"
      "pushl $0x309\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0438\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_13:\n\t"
      "cmpl $0, (%%ebx)\n\t"
      "jge .LFUN_0015d8b0_14\n\t"
      "pushl $1\n\t"
      "pushl $0x30c\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_14:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .LFUN_0015d8b0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x30d\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0770\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_15:\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "subl 0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jle .LFUN_0015d8b0_16\n\t"
      "pushl $1\n\t"
      "pushl $0x30e\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015d8b0_16:\n\t"
      "cmpl $0x2710, %%edi\n\t"
      "jle .LFUN_0015d8b0_17\n\t"
      "movl $0x2710, %%edi\n\t"
      ".LFUN_0015d8b0_17:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1eb2d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0015d8b0_18\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015d8b0_19\n\t"
      ".LFUN_0015d8b0_18:\n\t"
      "pushl $0x2a03e0\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015d8b0_19:\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x47dbe8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e8920]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015d8b0_20\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015d8b0_21\n\t"
      ".LFUN_0015d8b0_20:\n\t"
      "pushl $0x2a06a0\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015d8b0_21:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x1fb494, %%edx\n\t"
      "addl %%ecx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal (%%edi,%%edi,2), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $5\n\t"
      "call *%[c1ecf90]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015d8b0_22\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0015d8b0_23\n\t"
      ".LFUN_0015d8b0_22:\n\t"
      "pushl $0x2a05a8\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015d8b0_23:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "subl %%edi, %%eax\n\t"
      "addl %%edi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jg .LFUN_0015d8b0_2\n\t"
      ".LFUN_0015d8b0_24:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_0015d8b0_25\n\t"
      "pushl $0x2a0560\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015d8b0_25:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b15d8b0_assert), [exitfn] "m"(b15d8b0_exitfn), [c180050] "m"(b15d8b0_c180050), [c1eb2d0] "m"(b15d8b0_c1eb2d0), [c167ff0] "m"(b15d8b0_c167ff0), [c1e8920] "m"(b15d8b0_c1e8920), [c1ecf90] "m"(b15d8b0_c1ecf90), [c8f390] "m"(b15d8b0_c8f390)
      : "memory");
}
#else
#error "FUN_0015d8b0: clang naked draft required"
#endif


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
#if defined(__clang__)
static float (*const a4440_norm)(float *) = normalize3d;
static void (*const a4440_cross)(float *, float *, float *) = cross_product3d;
static bool (*const a4440_vnorm)(float *) = valid_real_normal3d;
static char *(*const a4440_xspr)(char *, const char *, ...) = csprintf;
static void (*const a4440_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const a4440_exitfn)(int) = system_exit;
static void (*const a4440_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void *(*const a4440_get)(int, int) = object_get_and_verify_type;
static void (*const a4440_a2800)(int, const char *) = FUN_001a2800;
static void *(*const a4440_tag)(int, int) = tag_get;
static void (*const a4440_ffloor)(void) = FUN_001d94f0;

__attribute__((naked, noinline))
void FUN_001a4440(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x2f4(%%eax), %%eax\n\t"
      "movb $4, %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%cl\n\t"
      "je .LFUN_001a4440_3\n\t"
      "testb %%cl, 0xb6(%%esi)\n\t"
      "jne .LFUN_001a4440_3\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[vnorm]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a4440_1\n\t"
      "flds 0x2c(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xfa5\n\t"
      "pushl $0x2b4d5c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b5148\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[xspr]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a4440_1:\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4440_2\n\t"
      "movl 0x31fc3c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x31fc40, %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_001a4440_2:\n\t"
      "flds 0x468(%%esi)\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "fcos\n\t"
      "pushl %%ecx\n\t"
      "flds 0x468(%%esi)\n\t"
      "fsin\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x2b5130\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl %%ebx, %%eax\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps 0x34(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps 0x38(%%esi)\n\t"
      "call *%[a2800]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a4440_3:\n\t"
      "testb $0x40, %%al\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "je .LFUN_001a4440_10\n\t"
      "testb %%al, %%cl\n\t"
      "jne .LFUN_001a4440_11\n\t"
      "cmpl $-1, 0x430(%%esi)\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "jne .LFUN_001a4440_4\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%ebx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%ecx\n\t"
      "jmp .LFUN_001a4440_6\n\t"
      ".LFUN_001a4440_4:\n\t"
      "leal 0x46c(%%esi), %%edx\n\t"
      "movl (%%edx), %%ebx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[cross]\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4440_5\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a4440_7\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      ".LFUN_001a4440_5:\n\t"
      "fldl 0x281138\n\t"
      "subl $8, %%esp\n\t"
      "fcos\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fldl 0x281138\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "addl $0x1c, %%esp\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4440_7\n\t"
      "movl -0x38(%%ebp), %%ebx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      ".LFUN_001a4440_6:\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_001a4440_7:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "addl $0x24, %%esi\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4440_8\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4440_8\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0x31fc3c, %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "jmp .LFUN_001a4440_9\n\t"
      ".LFUN_001a4440_8:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      ".LFUN_001a4440_9:\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x2b5118\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "call *%[a2800]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a4440_10:\n\t"
      "testb %%al, %%cl\n\t"
      "je .LFUN_001a4440_13\n\t"
      ".LFUN_001a4440_11:\n\t"
      "testb $1, 0x424(%%esi)\n\t"
      "jne .LFUN_001a4440_13\n\t"
      "pushl $0x2b50fc\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[a2800]\n\t"
      "flds 0x474(%%esi)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "leal 0x46c(%%esi), %%ebx\n\t"
      "flds 0x4(%%ebx)\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "addl $4, %%esp\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a4440_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "call *%[ffloor]\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001a4440_12\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001a4440_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "fcos\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsin\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[rots]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x24, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "pushl %%edi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_001a4440_12:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x2b50e0\n\t"
      "call *%[a2800]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a4440_13:\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0x2c(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4440_14\n\t"
      "movl 0x31fc3c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      ".LFUN_001a4440_14:\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0x30, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "pushl $0x2b50c8\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[a2800]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(a4440_norm), [cross] "m"(a4440_cross), [vnorm] "m"(a4440_vnorm), [xspr] "m"(a4440_xspr), [assert] "m"(a4440_assert), [exitfn] "m"(a4440_exitfn), [rots] "m"(a4440_rots), [get] "m"(a4440_get), [a2800] "m"(a4440_a2800), [tag] "m"(a4440_tag), [ffloor] "m"(a4440_ffloor)
      : "memory");
}
#else
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
#endif


/* FUN_001a4990 (0x1a4990) — XBE naked draft (batch 235). */
#if defined(__clang__)
static void *(*const b1a4990_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a4990_tag)(int, int) = tag_get;
static vector3_t * (*const b1a4990_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b1a4990_c1a25e0)(int unit_handle) = FUN_001a25e0;
static void (*const b1a4990_c1a4440)(int unit_handle) = FUN_001a4440;

__attribute__((naked, noinline))
char FUN_001a4990(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x32513c, %%edx\n\t"
      "leal 0x46c(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x325140, %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x325144, %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x325148, %%eax\n\t"
      "movl %%eax, 0xc(%%ecx)\n\t"
      "leal 0x438(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movb $0x7f, 0x45c(%%esi)\n\t"
      "movl %%ebx, 0x430(%%esi)\n\t"
      "movl %%ebx, 0x434(%%esi)\n\t"
      "call *%[c1412f0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ebx, 0x448(%%esi)\n\t"
      "movl %%ebx, 0x444(%%esi)\n\t"
      "movl %%ebx, 0x44c(%%esi)\n\t"
      "movb 0x2f4(%%edx), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $0x40, %%al\n\t"
      "je .LFUN_001a4990_1\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1a25e0]\n\t"
      ".LFUN_001a4990_1:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a4440]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%ebx, 0x42c(%%esi)\n\t"
      "movb $0, 0x42b(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a4990_get), [tag] "m"(b1a4990_tag), [c1412f0] "m"(b1a4990_c1412f0), [c1a25e0] "m"(b1a4990_c1a25e0), [c1a4440] "m"(b1a4990_c1a4440)
      : "memory");
}
#else
#error "FUN_001a4990: clang naked draft required"
#endif


/* 0x1a4a50 */
void FUN_001a4a50(void)
{
  int ebp = 0;

  FUN_001a2800(0x002b5160, (char *)(uintptr_t)ebp);

  (void)ebp;
}

/* FUN_001a4a70 (0x1a4a70) — XBE naked draft (batch 235). */
#if defined(__clang__)
static void *(*const b1a4a70_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a4a70_tag)(int, int) = tag_get;
static void (*const b1a4a70_c1a2800)(int unit_handle, const char *failure_kind) = FUN_001a2800;
static void (*const b1a4a70_c1a09f0)(int unit_handle) = biped_stop_limp_body_physics;
static float (*const b1a4a70_norm)(float *) = normalize3d;
static int *(*const b1a4a70_gseed)(void) = get_global_random_seed_address;
static float (*const b1a4a70_rmreal)(unsigned int *) = random_math_real;
static void (*const b1a4a70_c1a4440)(int unit_handle) = FUN_001a4440;

__attribute__((naked, noinline))
void FUN_001a4a70(int handle __attribute__((unused)), float *velocity __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl $0x100000, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_001a4a70_6\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2b5180\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_001a4a70_1\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x8(%%edi)\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_001a4a70_2\n\t"
      ".LFUN_001a4a70_1:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1a09f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a4a70_2:\n\t"
      "flds 0x18(%%esi)\n\t"
      "fadds (%%edi)\n\t"
      "fstps 0x18(%%esi)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x20(%%esi)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl 0x424(%%esi), %%ecx\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "andl $0xffffffdf, %%edx\n\t"
      "orl $3, %%ecx\n\t"
      "testb $4, %%al\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl %%ecx, 0x424(%%esi)\n\t"
      "jne .LFUN_001a4a70_3\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "testb $0x44, 0x2f4(%%ecx)\n\t"
      "je .LFUN_001a4a70_4\n\t"
      ".LFUN_001a4a70_3:\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls (%%eax)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x2568bc\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x3c(%%esi)\n\t"
      "fstps 0x3c(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x40(%%esi)\n\t"
      "fstps 0x40(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x44(%%esi)\n\t"
      "fstps 0x44(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a4a70_4:\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "jne .LFUN_001a4a70_5\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4a70_5\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x24, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "call *%[c1a4440]\n\t"
      "pushl $0x2b5174\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a4a70_5:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001a4a70_6:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a4a70_get), [tag] "m"(b1a4a70_tag), [c1a2800] "m"(b1a4a70_c1a2800), [c1a09f0] "m"(b1a4a70_c1a09f0), [norm] "m"(b1a4a70_norm), [gseed] "m"(b1a4a70_gseed), [rmreal] "m"(b1a4a70_rmreal), [c1a4440] "m"(b1a4a70_c1a4440)
      : "memory");
}
#else
#error "FUN_001a4a70: clang naked draft required"
#endif


/* 0x1a4c50 — biped facing / aim-turn update from movement state. */
#if defined(__clang__)
static float (*const a4c50_v2170)(float *) = FUN_00012170;
static float (*const a4c50_mag)(float *) = magnitude3d;
static float (*const a4c50_norm)(float *) = normalize3d;
static float (*const a4c50_v3070)(float *, float *) = FUN_00013070;
static void (*const a4c50_cross)(float *, float *, float *) = cross_product3d;
static void (*const a4c50_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void *(*const a4c50_get)(int, int) = object_get_and_verify_type;
static void (*const a4c50_a2800)(int, const char *) = FUN_001a2800;
static void (*const a4c50_a4440)(int) = FUN_001a4440;
static void (*const a4c50_b0630)(int, float *, float *, float *, float *, float, float) = FUN_001b0630;
static void *(*const a4c50_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_001a4c50(int unit_handle __attribute__((unused)), unsigned char *state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0x2f4(%%edx), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $4, %%bl\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "je .LFUN_001a4c50_16\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "jne .LFUN_001a4c50_16\n\t"
      "flds 0x20(%%esi)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x253f2c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_001a4c50_4\n\t"
      "flds 0x44(%%esi)\n\t"
      "flds 0x40(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2b51c4\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_001a4c50_4\n\t"
      "leal 0x228(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[v2170]\n\t"
      "fcomps 0x255d1c\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a4c50_3\n\t"
      "testb $0x20, 0x1b8(%%esi)\n\t"
      "je .LFUN_001a4c50_1\n\t"
      "movl $0x3f7d70a4, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001a4c50_2\n\t"
      ".LFUN_001a4c50_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x4c8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      ".LFUN_001a4c50_2:\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "leal 0x1d4(%%esi), %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[v3070]\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4c50_3\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "jmp .LFUN_001a4c50_7\n\t"
      ".LFUN_001a4c50_3:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".LFUN_001a4c50_4:\n\t"
      "flds 0x330(%%edx)\n\t"
      "leal 0x1d4(%%esi), %%edi\n\t"
      "fmuls 0x230(%%esi)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "fcoms 0x2533c0\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001a4c50_6\n\t"
      "flds -0x18(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4c50_5\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".LFUN_001a4c50_5:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "jmp .LFUN_001a4c50_7\n\t"
      ".LFUN_001a4c50_6:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a4c50_7:\n\t"
      "flds 0x38(%%esi)\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x34(%%esi)\n\t"
      "fmuls (%%ecx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x254e6c\n\t"
      "fmuls 0x228(%%esi)\n\t"
      "fsubs 0x22c(%%esi)\n\t"
      "fcoms 0x2533ec\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4c50_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533ec\n\t"
      ".LFUN_001a4c50_8:\n\t"
      "fmuls 0x324(%%edx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x468(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001a4c50_9\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_001a4c50_11\n\t"
      ".LFUN_001a4c50_9:\n\t"
      "flds 0x468(%%esi)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4c50_10\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001a4c50_10:\n\t"
      "fsubrs 0x2533c8\n\t"
      ".LFUN_001a4c50_11:\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fmuls 0x32c(%%edx)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x328(%%edx)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4c50_12\n\t"
      "fxch %%st(1)\n\t"
      "fsubs 0x468(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x253394\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fadds 0x468(%%esi)\n\t"
      "jmp .LFUN_001a4c50_13\n\t"
      ".LFUN_001a4c50_12:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a4c50_13:\n\t"
      "fstps 0x468(%%esi)\n\t"
      "movl $0xc0490fdb, -0x30(%%ebp)\n\t"
      "flds 0x344(%%edx)\n\t"
      "movl $0x40490fdb, -0x2c(%%ebp)\n\t"
      "fmuls 0x2546a4\n\t"
      "movl $0xbfc90fdb, -0x28(%%ebp)\n\t"
      "movl $0x3fc90fdb, -0x24(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x348(%%edx)\n\t"
      "fmuls 0x25620c\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4c50_14\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .LFUN_001a4c50_15\n\t"
      ".LFUN_001a4c50_14:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x3c, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[b0630]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_001a4c50_15:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[a4440]\n\t"
      "pushl $0x2b51b4\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[a2800]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a4c50_16:\n\t"
      "movb 0x257(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "je .LFUN_001a4c50_37\n\t"
      "cmpb $5, %%al\n\t"
      "jne .LFUN_001a4c50_17\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".LFUN_001a4c50_17:\n\t"
      "movl %%ebx, %%eax\n\t"
      "andl $0x40, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_001a4c50_19\n\t"
      "flds 0x1dc(%%esi)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x1d8(%%esi)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x1d4(%%esi)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fmuls 0x1dc(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x30(%%esi)\n\t"
      "fmuls 0x1d8(%%esi)\n\t"
      "flds 0x1d4(%%esi)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4c50_18\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".LFUN_001a4c50_18:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "jmp .LFUN_001a4c50_21\n\t"
      ".LFUN_001a4c50_19:\n\t"
      "leal 0x1d4(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a4c50_20\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".LFUN_001a4c50_20:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".LFUN_001a4c50_21:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a4c50_22\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001a4c50_22:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2568c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a4c50_24\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "cmpb $3, %%al\n\t"
      "jne .LFUN_001a4c50_23\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001a4c50_24\n\t"
      ".LFUN_001a4c50_23:\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LFUN_001a4c50_24\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001a4c50_24:\n\t"
      "movb 0x42a(%%esi), %%al\n\t"
      "cmpb $1, %%al\n\t"
      "je .LFUN_001a4c50_28\n\t"
      "testb $1, %%bl\n\t"
      "jne .LFUN_001a4c50_28\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a4c50_37\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a4c50_37\n\t"
      "movl 0x1b4(%%esi), %%eax\n\t"
      "testb $0x40, %%ah\n\t"
      "jne .LFUN_001a4c50_37\n\t"
      "movl 0x1b8(%%esi), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001a4c50_37\n\t"
      "testb $0x20, %%al\n\t"
      "je .LFUN_001a4c50_25\n\t"
      "flds 0x28ace8\n\t"
      "jmp .LFUN_001a4c50_26\n\t"
      ".LFUN_001a4c50_25:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x4c8(%%eax)\n\t"
      ".LFUN_001a4c50_26:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a4c50_27\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testl $0x100000, 0x17c(%%ecx)\n\t"
      "jne .LFUN_001a4c50_27\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "addb $2, %%dl\n\t"
      "movb %%dl, (%%eax)\n\t"
      ".LFUN_001a4c50_27:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x2b51a0\n\t"
      "call *%[a2800]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a4c50_28:\n\t"
      "movl 0x1b8(%%esi), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001a4c50_37\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x2f0(%%ecx)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fmuls 0x2546a4\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fsin\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "je .LFUN_001a4c50_29\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_001a4c50_29:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a4c50_30\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x30(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[rots]\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "addl $0x1c, %%esp\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "jmp .LFUN_001a4c50_31\n\t"
      ".LFUN_001a4c50_30:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".LFUN_001a4c50_31:\n\t"
      "fcomps 0x2533c0\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fnstsw %%ax\n\t"
      "je .LFUN_001a4c50_32\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a4c50_33\n\t"
      "jmp .LFUN_001a4c50_36\n\t"
      ".LFUN_001a4c50_32:\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4c50_36\n\t"
      ".LFUN_001a4c50_33:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0x2f4(%%eax), %%cl\n\t"
      "addl $0x30, %%esi\n\t"
      "testb $0x40, %%cl\n\t"
      "je .LFUN_001a4c50_34\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[cross]\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a4c50_35\n\t"
      "pushl %%edi\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001a4c50_35\n\t"
      ".LFUN_001a4c50_34:\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl $0, 0x8(%%edi)\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      ".LFUN_001a4c50_35:\n\t"
      "pushl %%edi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a4c50_36:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x2b518c\n\t"
      "call *%[a2800]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a4c50_37:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [v2170] "m"(a4c50_v2170), [mag] "m"(a4c50_mag), [norm] "m"(a4c50_norm), [v3070] "m"(a4c50_v3070), [cross] "m"(a4c50_cross), [rots] "m"(a4c50_rots), [get] "m"(a4c50_get), [a2800] "m"(a4c50_a2800), [a4440] "m"(a4c50_a4440), [b0630] "m"(a4c50_b0630), [tag] "m"(a4c50_tag)
      : "memory");
}
#else
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
#endif


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

/* FUN_001b8f80 (0x1b8f80) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b1b8f80_chkstk)(void) = FUN_001d90e0;
static void *(*const b1b8f80_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b8f80_tag)(int, int) = tag_get;
static void (*const b1b8f80_penter)(void *) = profile_enter_private;
static void (*const b1b8f80_cross)(float *, float *, float *) = cross_product3d;
static float *(*const b1b8f80_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const b1b8f80_v2fb0)(float *, float, float *) = FUN_00012fb0;
static float (*const b1b8f80_c13070)(float *a, float *b) = FUN_00013070;
static char (*const b1b8f80_c154630)(float *accum, float *coeffs, float target, float scale) = FUN_00154630;
static char (*const b1b8f80_c154750)(float *accum, float *bounds, char wrap_flag, float target, float scale) = FUN_00154750;
static void (*const b1b8f80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b8f80_exitfn)(int) = system_exit;
static void (*const b1b8f80_c1b5ff0)(int vehicle_handle, void *physics_buffer, void *wheel_state) = FUN_001b5ff0;
static void (*const b1b8f80_c1b6140)(int vehicle_handle, void *physics_buffer, void *wheel_state) = FUN_001b6140;
static void (*const b1b8f80_c1b6250)(int vehicle_handle, void *physics_buffer, void *wheel_state) = FUN_001b6250;
static void (*const b1b8f80_c1b77f0)(int vehicle_handle, void *scratch, void *wheel_state) = FUN_001b77f0;
static char (*const b1b8f80_c1b74d0)(int vehicle_handle) = FUN_001b74d0;
static void (*const b1b8f80_c1b72b0)(int vehicle_handle, void *contact_point, void *wheel_state) = FUN_001b72b0;
static void (*const b1b8f80_c1b56b0)(int vehicle_handle, void *physics_state) = FUN_001b56b0;
static void * (*const b1b8f80_c18e3c0)(void) = scenario_get;
static void * (*const b1b8f80_c18e450)(void) = game_globals_get;
static void *(*const b1b8f80_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b8f80_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1b8f80_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static short (*const b1b8f80_c1b0d90)(int unit_handle, char *anim_state) = FUN_001b0d90;
static void (*const b1b8f80_c1402c0)(int object_handle, const char *marker_name, short region_index, char param_4) = object_permute_region;
static void (*const b1b8f80_c1b81d0)(int object_handle, void *unused_scratch, void *force_buffer) = FUN_001b81d0;
static void (*const b1b8f80_c1b8570)(int object_handle, float dt, void *contact_buf, void *wheel_buf) = FUN_001b8570;
static void (*const b1b8f80_c1b8f10)(void) = FUN_001b8f10;
static void (*const b1b8f80_pphys)(int, void *, void *, float *, float *) = FUN_00154270;
static void (*const b1b8f80_c1b6ca0)(int vehicle_handle) = FUN_001b6ca0;
static void (*const b1b8f80_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
void FUN_001b8f80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x327c, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x449ef1, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_001b8f80_1\n\t"
      "movb 0x32e4a8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b8f80_1\n\t"
      "pushl $0x32e4a0\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b8f80_1:\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "je .LFUN_001b8f80_2\n\t"
      "movl %%esi, 0x3c(%%ebx)\n\t"
      "movl %%esi, 0x40(%%ebx)\n\t"
      "movl %%esi, 0x44(%%ebx)\n\t"
      "movl %%esi, 0x18(%%ebx)\n\t"
      "movl %%esi, 0x1c(%%ebx)\n\t"
      "movl %%esi, 0x20(%%ebx)\n\t"
      "andl $0xffffffdf, 0x4(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_54\n\t"
      ".LFUN_001b8f80_2:\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001b8f80_3\n\t"
      "orb $4, 0x424(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_4\n\t"
      ".LFUN_001b8f80_3:\n\t"
      "andb $0xfb, 0x424(%%ebx)\n\t"
      ".LFUN_001b8f80_4:\n\t"
      "testb $2, %%al\n\t"
      "jne .LFUN_001b8f80_7\n\t"
      "testb $0x10, 0x2f0(%%edi)\n\t"
      "je .LFUN_001b8f80_6\n\t"
      "flds 0x228(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_5\n\t"
      "flds 0x42c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001b8f80_7\n\t"
      ".LFUN_001b8f80_5:\n\t"
      "flds 0x228(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8f80_6\n\t"
      "flds 0x42c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001b8f80_7\n\t"
      ".LFUN_001b8f80_6:\n\t"
      "andb $0xf7, 0x424(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_8\n\t"
      ".LFUN_001b8f80_7:\n\t"
      "orb $8, 0x424(%%ebx)\n\t"
      ".LFUN_001b8f80_8:\n\t"
      "flds 0x34(%%ebx)\n\t"
      "leal 0x24(%%ebx), %%edi\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "leal 0x30(%%ebx), %%esi\n\t"
      "flds 0x4(%%edi)\n\t"
      "movw 0x424(%%ebx), %%cx\n\t"
      "testb $0x10, %%cl\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x1dc(%%ebx)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x1d8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x1d4(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x1dc(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x1d8(%%ebx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x1d4(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fpatan\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "je .LFUN_001b8f80_20\n\t"
      "movb 0x429(%%ebx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_001b8f80_20\n\t"
      "cmpb $0x1e, 0x42a(%%ebx)\n\t"
      "jae .LFUN_001b8f80_20\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fcomps 0x2555d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001b8f80_20\n\t"
      "cmpb $2, %%dl\n\t"
      "je .LFUN_001b8f80_9\n\t"
      "cmpb $4, %%dl\n\t"
      "je .LFUN_001b8f80_9\n\t"
      "fldl 0x2b7da0\n\t"
      "jmp .LFUN_001b8f80_10\n\t"
      ".LFUN_001b8f80_9:\n\t"
      "fldl 0x2b7d98\n\t"
      ".LFUN_001b8f80_10:\n\t"
      "cmpb $4, %%dl\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "je .LFUN_001b8f80_11\n\t"
      "cmpb $3, %%dl\n\t"
      "je .LFUN_001b8f80_11\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001b8f80_12\n\t"
      ".LFUN_001b8f80_11:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001b8f80_12:\n\t"
      "flds 0x38(%%ebx)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fmuls 0x25eeac\n\t"
      "fld %%st(0)\n\t"
      "fcomps 0x340(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8f80_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x340(%%ecx)\n\t"
      "jmp .LFUN_001b8f80_14\n\t"
      ".LFUN_001b8f80_13:\n\t"
      "fcoms 0x344(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_14\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x344(%%ecx)\n\t"
      ".LFUN_001b8f80_14:\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "movb 0x429(%%ebx), %%al\n\t"
      "andl $0xffffffdf, %%edx\n\t"
      "cmpb $2, %%al\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl %%edx, 0x4(%%ebx)\n\t"
      "je .LFUN_001b8f80_15\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LFUN_001b8f80_16\n\t"
      ".LFUN_001b8f80_15:\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fchs\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001b8f80_16:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal 0x3c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[v2fb0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl 0x2f4(%%edx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001b8f80_18\n\t"
      "cmpl $5, %%eax\n\t"
      "jne .LFUN_001b8f80_19\n\t"
      "flds 0x2b22a0\n\t"
      "fcomps 0x20(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_17\n\t"
      "movb 0x42a(%%ebx), %%al\n\t"
      "flds 0x20(%%ebx)\n\t"
      "incb %%al\n\t"
      "fstps 0x20(%%ebx)\n\t"
      "movb %%al, 0x42a(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_21\n\t"
      ".LFUN_001b8f80_17:\n\t"
      "movb 0x42a(%%ebx), %%al\n\t"
      "flds 0x2b22a0\n\t"
      "incb %%al\n\t"
      "fstps 0x20(%%ebx)\n\t"
      "movb %%al, 0x42a(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_21\n\t"
      ".LFUN_001b8f80_18:\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c13070]\n\t"
      "fstps 0x4(%%esp)\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%edi\n\t"
      "call *%[v2fb0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001b8f80_19:\n\t"
      "incb 0x42a(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_21\n\t"
      ".LFUN_001b8f80_20:\n\t"
      "andl $0xffef, %%ecx\n\t"
      "movb $0, 0x42a(%%ebx)\n\t"
      "movb $0, 0x429(%%ebx)\n\t"
      "movw %%cx, 0x424(%%ebx)\n\t"
      ".LFUN_001b8f80_21:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movb 0x424(%%ebx), %%al\n\t"
      "addl $0x2f8, %%edi\n\t"
      "testb $8, %%al\n\t"
      "pushl $0x3f800000\n\t"
      "leal 0x42c(%%ebx), %%esi\n\t"
      "je .LFUN_001b8f80_22\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c154630]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001b8f80_23\n\t"
      ".LFUN_001b8f80_22:\n\t"
      "movl 0x228(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c154630]\n\t"
      "movl 0x22c(%%ebx), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ecx\n\t"
      "addl $0x330, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x430(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c154630]\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_001b8f80_23:\n\t"
      "flds (%%esi)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpw $0, 0x2f4(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "je .LFUN_001b8f80_29\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8f80_24\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_001b8f80_25\n\t"
      ".LFUN_001b8f80_24:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_001b8f80_25:\n\t"
      "flds 0x30c(%%ecx)\n\t"
      "fmuls 0x253d4c\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8f80_26\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_001b8f80_28\n\t"
      ".LFUN_001b8f80_26:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x308(%%ecx)\n\t"
      "fmuls 0x253d4c\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_27\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_001b8f80_28\n\t"
      ".LFUN_001b8f80_27:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001b8f80_28:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "flds 0x314(%%edi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0x253d4c\n\t"
      "pushl %%ecx\n\t"
      "leal 0x308(%%edi), %%ecx\n\t"
      "fmuls 0x2546a4\n\t"
      "leal 0x434(%%ebx), %%esi\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c154750]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001b8f80_34\n\t"
      ".LFUN_001b8f80_29:\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b8f80_30\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "jmp .LFUN_001b8f80_33\n\t"
      ".LFUN_001b8f80_30:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x28ac24\n\t"
      "fcoms 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8f80_31\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_001b8f80_32\n\t"
      ".LFUN_001b8f80_31:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_32\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001b8f80_32:\n\t"
      "fmuls (%%edi)\n\t"
      "pushl $0x40000000\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      ".LFUN_001b8f80_33:\n\t"
      "leal 0x434(%%ebx), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c154630]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001b8f80_34:\n\t"
      "cmpl $-1, 0x8c(%%edi)\n\t"
      "je .LFUN_001b8f80_40\n\t"
      "movl 0x2f0(%%edi), %%ecx\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_001b8f80_35\n\t"
      "flds 0x42c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b8f80_39\n\t"
      ".LFUN_001b8f80_35:\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001b8f80_36\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b8f80_39\n\t"
      ".LFUN_001b8f80_36:\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001b8f80_37\n\t"
      "flds 0x2e8(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b8f80_39\n\t"
      ".LFUN_001b8f80_37:\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_001b8f80_38\n\t"
      "flds 0x2ec(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b8f80_39\n\t"
      ".LFUN_001b8f80_38:\n\t"
      "testb $0x20, %%cl\n\t"
      "je .LFUN_001b8f80_40\n\t"
      "flds 0x430(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b8f80_40\n\t"
      ".LFUN_001b8f80_39:\n\t"
      "andl $0xffffffdf, 0x4(%%ebx)\n\t"
      ".LFUN_001b8f80_40:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_001b8f80_41\n\t"
      "pushl $1\n\t"
      "pushl $0x134\n\t"
      "pushl $0x2b7d78\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b8f80_41:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%edx\n\t"
      "incw %%ax\n\t"
      "movw $0x11, 0x5a8c80(,%%edx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "cmpl $-1, 0x8c(%%edi)\n\t"
      "je .LFUN_001b8f80_61\n\t"
      "testb $0x20, 0x4(%%ebx)\n\t"
      "jne .LFUN_001b8f80_61\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl 0x2f4(%%edi), %%eax\n\t"
      "cmpl $6, %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "ja .LFUN_001b8f80_45\n\t"
      "jmp *.LFUN_001b8f80_jt(,%%eax,4)\n\t"
      ".LFUN_001b8f80_42:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x327c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal -0xc7c(%%ebp), %%edi\n\t"
      "call *%[c1b5ff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001b8f80_46\n\t"
      ".LFUN_001b8f80_43:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x327c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0xc7c(%%ebp), %%edi\n\t"
      "call *%[c1b6140]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001b8f80_46\n\t"
      ".LFUN_001b8f80_44:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x327c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc7c(%%ebp), %%esi\n\t"
      "call *%[c1b6250]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b8f80_45:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_001b8f80_46:\n\t"
      "leal -0x327c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1b77f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b74d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b8f80_47\n\t"
      "leal -0x327c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b72b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001b8f80_47:\n\t"
      "leal -0xc7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x327c(%%ebp), %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1b56b0]\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "je .LFUN_001b8f80_48\n\t"
      "movw $0xf, 0x426(%%ebx)\n\t"
      ".LFUN_001b8f80_48:\n\t"
      "testl $0x1000000, %%eax\n\t"
      "jne .LFUN_001b8f80_50\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb 0x2f4(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $0x28, %%dl\n\t"
      "je .LFUN_001b8f80_50\n\t"
      "call *%[c18e3c0]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[c18e3c0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b8f80_49\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8f80_49\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x14(%%ebx)\n\t"
      "fmuls 0x282124\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x255d90\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x2e8(%%ebx)\n\t"
      "fadds 0x20(%%ebx)\n\t"
      "fstps 0x20(%%ebx)\n\t"
      ".LFUN_001b8f80_49:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b8f80_50\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_50\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fmuls 0x282124\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x255d90\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x2e8(%%ebx)\n\t"
      "fsubrs 0x20(%%ebx)\n\t"
      "fstps 0x20(%%ebx)\n\t"
      ".LFUN_001b8f80_50:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_001b8f80_51:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_001b8f80_52\n\t"
      "pushl $1\n\t"
      "pushl $0x174\n\t"
      "pushl $0x2b7d78\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b8f80_52:\n\t"
      "decw 0x4761d8\n\t"
      "testb $0x40, 0x2f0(%%edi)\n\t"
      "je .LFUN_001b8f80_54\n\t"
      "pushl $0x98\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x188, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds 0x8c(%%eax)\n\t"
      "fchs\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fcomps 0x20(%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8f80_54\n\t"
      "movl 0xc8(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001b8f80_54\n\t"
      ".LFUN_001b8f80_53:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x38(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c137d20]\n\t"
      "movl 0xc4(%%esi), %%edi\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_001b8f80_53\n\t"
      ".LFUN_001b8f80_54:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "cmpl $-1, 0x44(%%esi)\n\t"
      "je .LFUN_001b8f80_55\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x2(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c1b0d90]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b8f80_55:\n\t"
      "flds 0x42c(%%ebx)\n\t"
      "movb $1, -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "flds 0x318(%%esi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001b8f80_56\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      ".LFUN_001b8f80_56:\n\t"
      "movb 0x424(%%ebx), %%al\n\t"
      "movb -0xc(%%ebp), %%cl\n\t"
      "andb $1, %%al\n\t"
      "cmpb %%al, %%cl\n\t"
      "je .LFUN_001b8f80_63\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x2b7d70\n\t"
      "pushl %%edx\n\t"
      "call *%[c1402c0]\n\t"
      "movb -0xc(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b8f80_62\n\t"
      "orb $1, 0x424(%%ebx)\n\t"
      "jmp .LFUN_001b8f80_63\n\t"
      ".LFUN_001b8f80_57:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x327c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b81d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001b8f80_46\n\t"
      ".LFUN_001b8f80_58:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x327c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b8570]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001b8f80_46\n\t"
      ".LFUN_001b8f80_59:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x327c(%%ebp), %%ebx\n\t"
      "leal -0xc7c(%%ebp), %%eax\n\t"
      "call *%[c1b8f10]\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "jmp .LFUN_001b8f80_45\n\t"
      ".LFUN_001b8f80_60:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x327c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[pphys]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001b8f80_46\n\t"
      ".LFUN_001b8f80_61:\n\t"
      "cmpw $0, 0x426(%%ebx)\n\t"
      "jle .LFUN_001b8f80_51\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b6ca0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b74d0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001b8f80_51\n\t"
      ".LFUN_001b8f80_62:\n\t"
      "andb $0xfe, 0x424(%%ebx)\n\t"
      ".LFUN_001b8f80_63:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001b8f80_64\n\t"
      "movb 0x32e4a8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b8f80_64\n\t"
      "pushl $0x32e4a0\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b8f80_64:\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001b8f80_jt:\n\t"
      ".long .LFUN_001b8f80_42\n\t"
      ".long .LFUN_001b8f80_43\n\t"
      ".long .LFUN_001b8f80_44\n\t"
      ".long .LFUN_001b8f80_57\n\t"
      ".long .LFUN_001b8f80_58\n\t"
      ".long .LFUN_001b8f80_59\n\t"
      ".long .LFUN_001b8f80_60\n\t"
      ".text\n\t"
      :
      : [chkstk] "m"(b1b8f80_chkstk), [get] "m"(b1b8f80_get), [tag] "m"(b1b8f80_tag), [penter] "m"(b1b8f80_penter), [cross] "m"(b1b8f80_cross), [vsca] "m"(b1b8f80_vsca), [v2fb0] "m"(b1b8f80_v2fb0), [c13070] "m"(b1b8f80_c13070), [c154630] "m"(b1b8f80_c154630), [c154750] "m"(b1b8f80_c154750), [assert] "m"(b1b8f80_assert), [exitfn] "m"(b1b8f80_exitfn), [c1b5ff0] "m"(b1b8f80_c1b5ff0), [c1b6140] "m"(b1b8f80_c1b6140), [c1b6250] "m"(b1b8f80_c1b6250), [c1b77f0] "m"(b1b8f80_c1b77f0), [c1b74d0] "m"(b1b8f80_c1b74d0), [c1b72b0] "m"(b1b8f80_c1b72b0), [c1b56b0] "m"(b1b8f80_c1b56b0), [c18e3c0] "m"(b1b8f80_c18e3c0), [c18e450] "m"(b1b8f80_c18e450), [elem] "m"(b1b8f80_elem), [c136750] "m"(b1b8f80_c136750), [c137d20] "m"(b1b8f80_c137d20), [c1b0d90] "m"(b1b8f80_c1b0d90), [c1402c0] "m"(b1b8f80_c1402c0), [c1b81d0] "m"(b1b8f80_c1b81d0), [c1b8570] "m"(b1b8f80_c1b8570), [c1b8f10] "m"(b1b8f80_c1b8f10), [pphys] "m"(b1b8f80_pphys), [c1b6ca0] "m"(b1b8f80_c1b6ca0), [pexit] "m"(b1b8f80_pexit)
      : "memory");
}
#else
#error "FUN_001b8f80: clang naked draft required"
#endif


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

/* FUN_001c4990 (0x1c4990) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b1c4990_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c4990_exitfn)(int) = system_exit;
static int (*const b1c4990_c19d8c0)(const unsigned short *s) = ustrlen;
static void (*const b1c4990_c1c3e40)(void) = FUN_001c3e40;
static int (*const b1c4990_c19d810)(const wchar_t *s1, const wchar_t *s2) = ustrcmp;
static char * (*const b1c4990_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b1c4990_c1d2f22)(void) = FUN_001d2f22;
static int (*const b1c4990_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void (*const b1c4990_c1d21f2)(void) = FUN_001d21f2;
static void * (*const b1c4990_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static char * (*const b1c4990_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static const char * (*const b1c4990_c1c0720)(void) = FUN_001c0720;
static char * (*const b1c4990_c8dd30)(char *destination, const char *source, size_t max_size) = csstrcat;
static void (*const b1c4990_c1d3185)(void) = FUN_001d3185;
static void (*const b1c4990_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static wchar_t * (*const b1c4990_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b1c4990_c1c4030)(void) = FUN_001c4030;

__attribute__((naked, noinline))
void FUN_001c4990(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x610, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "movzbl %%ah, %%edi\n\t"
      "sarl $0x10, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "andl $0xf, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "movb $1, %%bl\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_001c4990_1\n\t"
      "pushl $1\n\t"
      "pushl $0x306\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4990_1:\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001c4990_2\n\t"
      "cmpl $2, %%esi\n\t"
      "jl .LFUN_001c4990_3\n\t"
      ".LFUN_001c4990_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x309\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4990_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LFUN_001c4990_4\n\t"
      "cmpl $9, %%edi\n\t"
      "jl .LFUN_001c4990_5\n\t"
      ".LFUN_001c4990_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x30a\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba838\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4990_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001c4990_6\n\t"
      "cmpl $0x64, %%eax\n\t"
      "jl .LFUN_001c4990_7\n\t"
      ".LFUN_001c4990_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x30b\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba7e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4990_7:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d8c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x80, %%eax\n\t"
      "jb .LFUN_001c4990_8\n\t"
      "pushl $1\n\t"
      "pushl $0x30d\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bb7c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4990_8:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x410(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1c3e40]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4990_18\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4990_19\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_001c4990_19\n\t"
      "pushl %%eax\n\t"
      "leal -0x310(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19d810]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4990_19\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001c4990_17\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x7(%%ebp)\n\t"
      "movw %%ax, -0x3(%%ebp)\n\t"
      "movb %%al, -0x208(%%ebp)\n\t"
      "pushl $0x100\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl $0x3f, %%ecx\n\t"
      "leal -0x207(%%ebp), %%edi\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "rep stosl\n\t"
      "leal -0x208(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "stosw\n\t"
      "pushl %%esi\n\t"
      "pushl $8\n\t"
      ".byte 0xaa\n\t"
      "movl 0x32eb94, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2f22]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c4990_16\n\t"
      "movswl -0x210(%%ebp), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001c4990_11\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001c4990_10\n\t"
      "pushl $1\n\t"
      "pushl $0x343\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bb7a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4990_9:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_001c4990_15\n\t"
      ".LFUN_001c4990_10:\n\t"
      "pushl $0x2bb794\n\t"
      "leal -0x208(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25bf84\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl $0xff\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "leal -0x410(%%ebp), %%ecx\n\t"
      "jmp .LFUN_001c4990_12\n\t"
      ".LFUN_001c4990_11:\n\t"
      "pushl $0x2bb788\n\t"
      "leal -0x208(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25bf84\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl $0xff\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $1\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x410(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "call *%[c1d21f2]\n\t"
      "movb %%al, %%bl\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_001c4990_14\n\t"
      "pushl $0xff\n\t"
      "leal -0x410(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x510(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8de70]\n\t"
      "leal -0x510(%%ebp), %%edx\n\t"
      "pushl $0x2bb788\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x411(%%ebp)\n\t"
      "call *%[c1d9690]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4990_9\n\t"
      "pushl $0xff\n\t"
      "movb $0, (%%eax)\n\t"
      "call *%[c1c0720]\n\t"
      "pushl %%eax\n\t"
      "leal -0x510(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dd30]\n\t"
      "movb $0, -0x411(%%ebp)\n\t"
      "call *%[c1c0720]\n\t"
      "pushl %%eax\n\t"
      "leal -0x208(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25bf84\n\t"
      "leal -0x610(%%ebp), %%edx\n\t"
      "pushl $0xff\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x20, %%esp\n\t"
      "leal -0x610(%%ebp), %%eax\n\t"
      "leal -0x510(%%ebp), %%ecx\n\t"
      ".LFUN_001c4990_12:\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d21f2]\n\t"
      "movb %%al, %%bl\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_001c4990_14\n\t"
      "leal -0x310(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3185]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4990_13\n\t"
      "pushl $0x2bb728\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c4990_13:\n\t"
      "pushl $0xff\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x410(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8de70]\n\t"
      "pushl $0x7f\n\t"
      "leal -0x310(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x311(%%ebp)\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x410(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw $0, -0x212(%%ebp)\n\t"
      "call *%[c1c4030]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c4990_19\n\t"
      "pushl $0x2bb6e0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4990_14:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001c4990_19\n\t"
      ".LFUN_001c4990_15:\n\t"
      "pushl %%esi\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3185]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4990_19\n\t"
      "pushl $0x2bb680\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4990_16:\n\t"
      "pushl $0x2bb608\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4990_17:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2bb4f4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4990_18:\n\t"
      "pushl $0x2bb5e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c4990_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c4990_assert), [exitfn] "m"(b1c4990_exitfn), [c19d8c0] "m"(b1c4990_c19d8c0), [c1c3e40] "m"(b1c4990_c1c3e40), [c19d810] "m"(b1c4990_c19d810), [c19f3a0] "m"(b1c4990_c19f3a0), [c1d2f22] "m"(b1c4990_c1d2f22), [c1d9179] "m"(b1c4990_c1d9179), [c1d21f2] "m"(b1c4990_c1d21f2), [c8de70] "m"(b1c4990_c8de70), [c1d9690] "m"(b1c4990_c1d9690), [c1c0720] "m"(b1c4990_c1c0720), [c8dd30] "m"(b1c4990_c8dd30), [c1d3185] "m"(b1c4990_c1d3185), [c8f390] "m"(b1c4990_c8f390), [c19dc90] "m"(b1c4990_c19dc90), [c1c4030] "m"(b1c4990_c1c4030)
      : "memory");
}
#else
#error "FUN_001c4990: clang naked draft required"
#endif


/* FUN_001d5c66 (0x1d5c66) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b1d5c66_c1dd5c8)(void) = FUN_001dd5c8;
static unsigned int (*const b1d5c66_c1d8750)(unsigned int val) = FUN_001d8750;
static void (*const b1d5c66_c1d5411)(void) = FUN_001d5411;
static void (*const b1d5c66_c1d4cd9)(void) = FUN_001d4cd9;
static void (*const b1d5c66_c1d63d5)(void) = FUN_001d63d5;
static void (*const b1d5c66_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001d5c66(void)
{
  __asm__ volatile(
      "pushl $0x178\n\t"
      "pushl $0x2c1ea0\n\t"
      "call *%[c1dd5c8]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, %%ebx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "orl 0x18(%%esi), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d5c66_1\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d5c66_1:\n\t"
      "addl $0x1f, %%eax\n\t"
      "andl $0xfffffff0, %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "testb $1, %%cl\n\t"
      "jne .LFUN_001d5c66_2\n\t"
      "pushl 0x580(%%esi)\n\t"
      "call *0x25309c\n\t"
      "movb $1, -0x1d(%%ebp)\n\t"
      ".LFUN_001d5c66_2:\n\t"
      "cmpl $0x80, %%edi\n\t"
      "jae .LFUN_001d5c66_13\n\t"
      "leal 0x180(%%esi,%%edi,8), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "je .LFUN_001d5c66_4\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "subl $8, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movb 0x5(%%eax), %%dl\n\t"
      "movb %%dl, -0x31(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edi\n\t"
      "movl %%edi, -0x3c(%%ebp)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jne .LFUN_001d5c66_3\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%edi\n\t"
      "shrl $3, %%edi\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edi, -0x44(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%esi,1), %%ecx\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "xorl %%edi, %%ecx\n\t"
      "movl -0x48(%%ebp), %%edi\n\t"
      "movb %%cl, (%%edi)\n\t"
      ".LFUN_001d5c66_3:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "subl %%ecx, 0x30(%%esi)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "andl $0x10, %%edx\n\t"
      "orb $1, %%dl\n\t"
      "movb %%dl, 0x5(%%eax)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "subl 0x10(%%ebp), %%ecx\n\t"
      "movb %%cl, 0x6(%%eax)\n\t"
      "andb $0, 0x7(%%eax)\n\t"
      "jmp .LFUN_001d5c66_43\n\t"
      ".LFUN_001d5c66_4:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $5, %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "leal 0x160(%%esi,%%edx,4), %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "andl $0x1f, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "decl %%eax\n\t"
      "notl %%eax\n\t"
      "andl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "subl $0, %%edx\n\t"
      "je .LFUN_001d5c66_5\n\t"
      "decl %%edx\n\t"
      "je .LFUN_001d5c66_7\n\t"
      "decl %%edx\n\t"
      "je .LFUN_001d5c66_9\n\t"
      "decl %%edx\n\t"
      "je .LFUN_001d5c66_11\n\t"
      "jmp .LFUN_001d5c66_14\n\t"
      ".LFUN_001d5c66_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_6\n\t"
      "leal 0x180(%%esi), %%edi\n\t"
      "jmp .LFUN_001d5c66_12\n\t"
      ".LFUN_001d5c66_6:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      ".LFUN_001d5c66_7:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_8\n\t"
      "leal 0x280(%%esi), %%edi\n\t"
      "jmp .LFUN_001d5c66_12\n\t"
      ".LFUN_001d5c66_8:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      ".LFUN_001d5c66_9:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_10\n\t"
      "leal 0x380(%%esi), %%edi\n\t"
      "jmp .LFUN_001d5c66_12\n\t"
      ".LFUN_001d5c66_10:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      ".LFUN_001d5c66_11:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_14\n\t"
      "leal 0x480(%%esi), %%edi\n\t"
      ".LFUN_001d5c66_12:\n\t"
      "movl %%edi, -0x2c(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c1d8750]\n\t"
      "movsbl %%al, %%eax\n\t"
      "leal (%%edi,%%eax,8), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "subl $8, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jne .LFUN_001d5c66_19\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edi, -0x68(%%ebp)\n\t"
      "leal 0x160(%%edx,%%esi,1), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb (%%esi), %%cl\n\t"
      "xorl %%edi, %%ecx\n\t"
      "movb %%cl, (%%esi)\n\t"
      "jmp .LFUN_001d5c66_19\n\t"
      ".LFUN_001d5c66_13:\n\t"
      "cmpl 0x1c(%%esi), %%edi\n\t"
      "ja .LFUN_001d5c66_46\n\t"
      ".LFUN_001d5c66_14:\n\t"
      "leal 0x180(%%esi), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_001d5c66_17\n\t"
      "addl $-8, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movzwl (%%eax), %%eax\n\t"
      "cmpl -0x28(%%ebp), %%eax\n\t"
      "jb .LFUN_001d5c66_17\n\t"
      "movl (%%edx), %%ecx\n\t"
      ".LFUN_001d5c66_15:\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_001d5c66_17\n\t"
      "leal -0x8(%%ecx), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movzwl (%%eax), %%esi\n\t"
      "cmpl -0x28(%%ebp), %%esi\n\t"
      "jb .LFUN_001d5c66_16\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x70(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, -0x74(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_18\n\t"
      ".LFUN_001d5c66_16:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "jmp .LFUN_001d5c66_15\n\t"
      ".LFUN_001d5c66_17:\n\t"
      "pushl -0x24(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d5411]\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_45\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      ".LFUN_001d5c66_18:\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      ".LFUN_001d5c66_19:\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "movb %%cl, -0x31(%%ebp)\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movb $1, 0x5(%%eax)\n\t"
      "movzwl (%%eax), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "subl 0x10(%%ebp), %%ecx\n\t"
      "movb %%cl, 0x6(%%eax)\n\t"
      "andb $0, 0x7(%%eax)\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001d5c66_42\n\t"
      "cmpl $1, %%edx\n\t"
      "jne .LFUN_001d5c66_20\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "incl %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "addl $0x10, %%ecx\n\t"
      "movb %%cl, 0x6(%%eax)\n\t"
      "jmp .LFUN_001d5c66_42\n\t"
      ".LFUN_001d5c66_20:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "movl %%esi, -0x84(%%ebp)\n\t"
      "movb -0x31(%%ebp), %%cl\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movw -0x28(%%ebp), %%di\n\t"
      "movw %%di, 0x2(%%esi)\n\t"
      "movb 0x4(%%eax), %%al\n\t"
      "movb %%al, 0x4(%%esi)\n\t"
      "movw %%dx, (%%esi)\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_001d5c66_27\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andl $0x10, %%eax\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%dx\n\t"
      "jae .LFUN_001d5c66_22\n\t"
      "movzwl %%dx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "movl %%edi, -0x88(%%ebp)\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d5c66_21\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0x94(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001d5c66_21:\n\t"
      "movl %%edi, -0x98(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x9c(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_36\n\t"
      ".LFUN_001d5c66_22:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0xa0(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LFUN_001d5c66_23:\n\t"
      "movl %%eax, -0xa4(%%ebp)\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001d5c66_24\n\t"
      "leal -0x8(%%eax), %%edi\n\t"
      "movl %%edi, -0xa8(%%ebp)\n\t"
      "cmpw (%%edi), %%dx\n\t"
      "jbe .LFUN_001d5c66_24\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d5c66_23\n\t"
      ".LFUN_001d5c66_24:\n\t"
      "movl %%eax, -0xac(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0xb0(%%ebp)\n\t"
      ".LFUN_001d5c66_25:\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_001d5c66_26:\n\t"
      "addl %%edx, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d5c66_41\n\t"
      ".LFUN_001d5c66_27:\n\t"
      "movl %%edx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_001d5c66_32\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andl $0x10, %%eax\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%dx\n\t"
      "jae .LFUN_001d5c66_29\n\t"
      "movzwl %%dx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "movl %%edi, -0xb8(%%ebp)\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d5c66_28\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0xbc(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, -0xc0(%%ebp)\n\t"
      "movl -0xbc(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0xc4(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0xc4(%%ebp), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001d5c66_28:\n\t"
      "movl %%edi, -0xc8(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0xcc(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_36\n\t"
      ".LFUN_001d5c66_29:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LFUN_001d5c66_30:\n\t"
      "movl %%eax, -0xd4(%%ebp)\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001d5c66_31\n\t"
      "leal -0x8(%%eax), %%edi\n\t"
      "movl %%edi, -0xd8(%%ebp)\n\t"
      "cmpw (%%edi), %%dx\n\t"
      "jbe .LFUN_001d5c66_31\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d5c66_30\n\t"
      ".LFUN_001d5c66_31:\n\t"
      "movl %%eax, -0xdc(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0xe0(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_25\n\t"
      ".LFUN_001d5c66_32:\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xe4(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edi\n\t"
      "movl %%edi, -0xe8(%%ebp)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jne .LFUN_001d5c66_33\n\t"
      "movw (%%eax), %%cx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d5c66_33\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, %%edi\n\t"
      "shrl $3, %%edi\n\t"
      "movl %%edi, -0xec(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edi, -0xf0(%%ebp)\n\t"
      "movl -0xec(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0xf4(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "xorl %%edi, %%ecx\n\t"
      "movl -0xf4(%%ebp), %%edi\n\t"
      "movb %%cl, (%%edi)\n\t"
      ".LFUN_001d5c66_33:\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "movzwl (%%eax), %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "cmpl $0xff00, %%edx\n\t"
      "ja .LFUN_001d5c66_40\n\t"
      "movw %%dx, (%%esi)\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "jne .LFUN_001d5c66_34\n\t"
      "movl %%edx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movw %%dx, 0x2(%%eax,%%esi,1)\n\t"
      ".LFUN_001d5c66_34:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andl $0x10, %%eax\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%dx\n\t"
      "jae .LFUN_001d5c66_37\n\t"
      "movzwl %%dx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "movl %%edi, -0xf8(%%ebp)\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d5c66_35\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0xfc(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, -0x100(%%ebp)\n\t"
      "movl -0xfc(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0x104(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0x104(%%ebp), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001d5c66_35:\n\t"
      "movl %%edi, -0x108(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x10c(%%ebp)\n\t"
      ".LFUN_001d5c66_36:\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "jmp .LFUN_001d5c66_26\n\t"
      ".LFUN_001d5c66_37:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x110(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LFUN_001d5c66_38:\n\t"
      "movl %%eax, -0x114(%%ebp)\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001d5c66_39\n\t"
      "leal -0x8(%%eax), %%edi\n\t"
      "movl %%edi, -0x118(%%ebp)\n\t"
      "cmpw (%%edi), %%dx\n\t"
      "jbe .LFUN_001d5c66_39\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d5c66_38\n\t"
      ".LFUN_001d5c66_39:\n\t"
      "movl %%eax, -0x11c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0x120(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_25\n\t"
      ".LFUN_001d5c66_40:\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4cd9]\n\t"
      ".LFUN_001d5c66_41:\n\t"
      "andb $0, -0x31(%%ebp)\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "je .LFUN_001d5c66_42\n\t"
      "movzbl 0x4(%%esi), %%eax\n\t"
      "movl 0x60(%%ebx,%%eax,4), %%eax\n\t"
      "movl %%eax, -0x124(%%ebp)\n\t"
      "movl %%esi, 0x40(%%eax)\n\t"
      ".LFUN_001d5c66_42:\n\t"
      "testb $0x10, -0x31(%%ebp)\n\t"
      "je .LFUN_001d5c66_43\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "orb $0x10, %%cl\n\t"
      "movb %%cl, 0x5(%%eax)\n\t"
      ".LFUN_001d5c66_43:\n\t"
      "movl -0x4c(%%ebp), %%edi\n\t"
      "addl $0x10, %%edi\n\t"
      "movl %%edi, -0x128(%%ebp)\n\t"
      "cmpb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_001d5c66_44\n\t"
      "pushl 0x580(%%ebx)\n\t"
      "call *0x253098\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      ".LFUN_001d5c66_44:\n\t"
      "testb $8, 0xc(%%ebp)\n\t"
      "je .LFUN_001d5c66_50\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      "jmp .LFUN_001d5c66_50\n\t"
      ".LFUN_001d5c66_45:\n\t"
      "movl $0xc0000017, -0x12c(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_48\n\t"
      ".LFUN_001d5c66_46:\n\t"
      "testb $2, 0x14(%%esi)\n\t"
      "je .LFUN_001d5c66_47\n\t"
      "andl $0, -0x130(%%ebp)\n\t"
      "addl $0x20, -0x24(%%ebp)\n\t"
      "pushl $4\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "notl %%eax\n\t"
      "andl $0x800000, %%eax\n\t"
      "orl $0x1000, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      "movl %%eax, -0x12c(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5c66_48\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl -0x130(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "subl 0x10(%%ebp), %%eax\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x20(%%ecx)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "movb $0xb, 0x25(%%eax)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x18(%%ecx)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%eax)\n\t"
      "addl $0x58, %%esi\n\t"
      "movl %%esi, -0x134(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, -0x138(%%ebp)\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "addl $0x30, %%eax\n\t"
      "movl %%eax, -0x128(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_50\n\t"
      ".LFUN_001d5c66_47:\n\t"
      "movl $0xc0000023, -0x12c(%%ebp)\n\t"
      ".LFUN_001d5c66_48:\n\t"
      "testb $4, 0xc(%%ebp)\n\t"
      "je .LFUN_001d5c66_49\n\t"
      "movl $0xc0000017, -0x188(%%ebp)\n\t"
      "andl $0, -0x180(%%ebp)\n\t"
      "movl $1, -0x178(%%ebp)\n\t"
      "andl $0, -0x184(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl %%eax, -0x174(%%ebp)\n\t"
      "leal -0x188(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530c0\n\t"
      ".LFUN_001d5c66_49:\n\t"
      "andl $0, -0x128(%%ebp)\n\t"
      ".LFUN_001d5c66_50:\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1d63d5]\n\t"
      "movl -0x128(%%ebp), %%eax\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1d5c66_c1dd5c8), [c1d8750] "m"(b1d5c66_c1d8750), [c1d5411] "m"(b1d5c66_c1d5411), [c1d4cd9] "m"(b1d5c66_c1d4cd9), [c1d63d5] "m"(b1d5c66_c1d63d5), [c1dd601] "m"(b1d5c66_c1dd601)
      : "memory");
}
#else
#error "FUN_001d5c66: clang naked draft required"
#endif


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
