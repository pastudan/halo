/* kb object: tif_flush.obj -> bitmaps/libtiff/tif_flush.c */

/* --- tif_flush.obj batch drafts (2026-07-26) --- */

/* 0x68780 */
void FUN_00068780(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x68890 */
void FUN_00068890(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, edi -> jge 0x688c2 */
  FUN_00068a30(0, (char *)0x0025fff0);
  /* cmp eax, ebx -> je 0x688db */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, edi);
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x68914 */
  /* cmp eax, 0x10 -> je 0x68903 */
  /* cmp eax, 0x20 -> jne 0x68914 */
  FUN_0006f220();
  FUN_0006f1f0();

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x68940 */
void FUN_00068940(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68970 */
void FUN_00068970(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x689c0 */
void FUN_000689c0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x689dd */
  crt_fprintf((void *)0x00331070, (char *)0x00259f68);
  FUN_001d9850();
  crt_fprintf((void *)0x00331070, (char *)0x00260020);

  (void)eax;
}

/* 0x68a10 */
void FUN_00068a10(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68a30 */
void FUN_00068a30(int param_1, const char *format, ...)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68a50 */
void FUN_00068a50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68a70 */
void FUN_00068a70(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68bd0 */
void FUN_00068bd0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68c40 */
void FUN_00068c40(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68c70 */
void FUN_00068c70(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  FUN_00068a30(0, (char *)0x00260084);
  FUN_0006f890();
  TIFFScanlineSize();
  /* test (char)eax, 1 -> jne 0x68cca */
  /* relift: cmp word ptr [esi + 0x3a], 4 -> jne 0x68cd1 */
  debug_malloc(ebx, 0, (char *)0x00260058, 252);
  FUN_00068a30(0x00260024, (char *)0x00260034);
  /* relift: test byte ptr [esi + 0x68], 1 -> jne 0x68d57 */
  /* relift: cmp word ptr [esi + 0x3a], 4 -> je 0x68d57 */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x68d80 */
void FUN_00068d80(void)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, ebx -> jne 0x68dae */
  FUN_00068c70();
  /* cmp esi, ebx -> jne 0x68dae */
  /* cmp ecx, ebx -> jle 0x68df3 */
  /* relift: test byte ptr [edi + 9], 2 -> jne 0x68e15 */
  FUN_00068a70();
  /* relift: test byte ptr [edi + 0x68], 1 -> je 0x68e15 */
  FUN_00068bd0();

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x68e20 */
void FUN_00068e20(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68eb0 */
void FUN_00068eb0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68f60 */
void FUN_00068f60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x69020 */
void FUN_00069020(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x69180 */
void FUN_00069180(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x69200 */
void FUN_00069200(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp ebx, eax -> jbe 0x6927c */
  /* relift: cmp ecx, dword ptr [edi + 0x130] -> jl 0x6923e */
  TIFFFlushData1();
  /* cmp ebx, eax -> ja 0x69215 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x692f2 */
  /* relift: cmp eax, dword ptr [edi + 0x130] -> jl 0x692bc */
  TIFFFlushData1();
  /* relift: tail-call FUN_00069200(); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x69310 */
void FUN_00069310(void)
{
  int esi = 0;

  FUN_00069200();
  /* cmp esi, 0xa40 -> jge 0x69330 */
  /* cmp esi, 0x40 -> jl 0x69387 */
  FUN_00069200();
  FUN_00069200();

  (void)esi;
}

/* 0x693b0 */
void FUN_000693b0(void)
{
  int eax = 0;

  /* cmp eax, 4 -> je 0x693e1 */
  FUN_00069200();
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6940f */
  FUN_00069200();

  (void)eax;
}

/* 0x69420 */
void FUN_00069420(void)
{
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x6946d */
  FUN_00068c70();
  /* test esi, esi -> jne 0x69448 */
  /* relift: cmp word ptr [esi + 4], 0 -> jne 0x6945f */
  /* test ecx, ecx -> jle 0x694b9 */
  /* relift: relift: fcomp dword ptr [0x260134] */

  (void)ecx;
  (void)esi;
}

/* 0x69520 */
void FUN_00069520(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 2], 8 -> je 0x69582 */
  /* relift: cmp eax, dword ptr [esi + 0x130] -> jl 0x6954c */
  TIFFFlushData1();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x69590 */
void FUN_00069590(void)
{
  int esi = 0;

  /* relift: test byte ptr [esi + 9], 1 -> jne 0x695b9 */
  FUN_000693b0();
  FUN_00069520();

  (void)esi;
}

/* 0x695c0 */
void FUN_000695c0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x695ee */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260058, 1077);

  (void)eax;
}

/* 0x69600 */
void FUN_00069600(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x69690 */
void FUN_00069690(void)
{
  FUN_00069600();
}

/* 0x696d0 */
void FUN_000696d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* relift: relift: mov (char)eax, byte ptr [0x2ec379] */
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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x69b90 */
void FUN_00069b90(void)
{
  int esi = 0;
  int edi = 0;

  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jge 0x69c2a */
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jge 0x69c2a */
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jl 0x69bd0 */

  (void)esi;
  (void)edi;
}

/* 0x69c40 */
void FUN_00069c40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x69f30 */
void FUN_00069f30(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6a070 */
void FUN_0006a070(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6a190 */
void FUN_0006a190(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6a210 */
void FUN_0006a210(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, 8 -> je 0x6a249 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x6a24e */
  /* test eax, eax -> je 0x6a24e */
  /* test eax, eax -> jne 0x6a24e */
  TIFFFlushData1();

  (void)eax;
  (void)ecx;
}

/* 0x6a260 */
int FUN_0006a260(int file)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 6], 0 -> je 0x6a293 */
  FUN_0006a210();
  /* test eax, eax -> je 0x6a28e */
  /* relift: test byte ptr [esi + 0xa], 2 -> je 0x6a293 */
  FUN_000680a0();
  /* test eax, eax -> jne 0x6a293 */
  return 1;

  (void)eax;
  (void)esi;
}

/* 0x6a2a0 */
void FUN_0006a2a0(void)
{
  int eax = 0;
  int edi = 0;

  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* test eax, eax -> jg 0x6a2b0 */
  FUN_0006f9d0();

  (void)eax;
  (void)edi;
}

/* 0x6a310 */
void FUN_0006a310(void)
{
  int eax = 0;

  FUN_00064ec0();
  /* cmp eax, 7 -> ja 0x6a35e */
  FUN_0006f9d0();
  /* relift: relift: mov word ptr [0x3340f0], 4 */
  FUN_0006f9d0();
  /* relift: relift: mov word ptr [0x3340f0], 1 */
  /* mem[0xa35e0006] = eax */
  /* mem[0x90900006] = eax */

  (void)eax;
}

/* 0x6a3b0 */
void FUN_0006a3b0(void)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  debug_malloc(eax, 0, (char *)0, 0);
  /* mem[0x003340c8] = eax */
  FUN_00068a30(0, (char *)0x00260244);
  /* cmp edi, 7 -> ja 0x6a591 */
  /* cmp edx, 0x100 -> jl 0x6a402 */

  (void)eax;
  (void)edx;
  (void)edi;
}

/* 0x6a5d0 */
void FUN_0006a5d0(void)
{
  int eax = 0;
  int edx = 0;

  debug_malloc(eax, 0, (char *)0, 0);
  /* mem[0x003340c4] = edx */
  FUN_00068a30(0, (char *)0x00260294);
  /* cmp edx, 7 -> ja 0x6a8ca */
  /* cmp eax, 0x100 -> jl 0x6a632 */

  (void)eax;
  (void)edx;
}

/* 0x6a910 */
void FUN_0006a910(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6a9a0 */
void FUN_0006a9a0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6aa40 */
void FUN_0006aa40(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6ab10 */
void FUN_0006ab10(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6ac60 */
void FUN_0006ac60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6acc0 */
void FUN_0006acc0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6ae10 */
void FUN_0006ae10(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6aee0 */
void FUN_0006aee0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6af80 */
void FUN_0006af80(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6b0a0 */
void FUN_0006b0a0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6b190 */
void FUN_0006b190(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6b2d0 */
void FUN_0006b2d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6b3f0 */
void TIFFFlushData(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6b440 */
void FUN_0006b440(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test ebx, ebx -> jle 0x6b5ea */
  /* relift: relift: fld dword ptr [0x3340c0] */
  /* relift: relift: fld dword ptr [0x3340b8] */
  /* relift: relift: fld dword ptr [0x3340b4] */
  /* relift: relift: fld dword ptr [0x3340bc] */
  /* relift: relift: fld qword ptr [0x2602c0] */
  /* test (char)eax, 0x41 -> jne 0x6b545 */
  /* relift: relift: fld qword ptr [0x2602b8] */
  /* relift: relift: fld qword ptr [0x2602c0] */
  /* test (char)eax, 0x41 -> jne 0x6b57a */
  /* relift: relift: fld qword ptr [0x2602b8] */
  /* relift: relift: fld qword ptr [0x2602c0] */
  /* test (char)eax, 0x41 -> jne 0x6b5af */
  /* relift: relift: fld qword ptr [0x2602b8] */
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  /* cmp esi, ebx -> jl 0x6b4e1 */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x6b610 */
void FUN_0006b610(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  /* relift: relift: mov (int16_t)ecx, word ptr [0x3340d8] */
  FUN_0006b440();
  /* relift: relift: mov (int16_t)ecx, word ptr [0x3340d8] */
  /* test ebx, ebx -> jbe 0x6b6d0 */
  FUN_0006b440();
  /* relift: relift: mov (int16_t)ecx, word ptr [0x3340d8] */
  /* test eax, eax -> jbe 0x6b76a */
  FUN_0006b440();
  /* relift: relift: mov (int16_t)ecx, word ptr [0x3340d8] */
  /* test ebx, ebx -> jbe 0x6b76a */
  FUN_0006b440();

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x6b780 */
void FUN_0006b780(void)
{
  int eax = 0;
  int esi = 0;

  /* cmp eax, 6 -> ja 0x6b825 */
  /* relift: cmp word ptr [0x3340fc], 8 -> jne 0x6b7ab */
  /* cmp eax, 7 -> ja 0x6b825 */
  /* cmp eax, 7 -> ja 0x6b825 */
  /* relift: cmp word ptr [0x3340fc], 8 -> jne 0x6b825 */
  /* test esi, esi -> jne 0x6b838 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* test esi, esi -> jne 0x6b8da */
  FUN_00068a30(0, (char *)0x002602d0);

  (void)eax;
  (void)esi;
}

/* 0x6b8e0 */
void FUN_0006b8e0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6ba70 */
void FUN_0006ba70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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
  FUN_0006b780();
  FUN_0006f180();
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x00260304);
  FUN_0006a310();
  FUN_00064ec0();
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
  FUN_0006f180();
  debug_malloc(eax, edi, (char *)0x00260264, 487);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
