/* kb object: tif_dir.obj -> bitmaps/libtiff/tif_dir.c */

/* --- tif_dir.obj batch drafts (2026-07-26) --- */

/* 0x659f0 */
void TIFFSetField(int file, int field, int value)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, 0x101 -> je 0x65a20 */
  /* relift: test byte ptr [ebx + 0xa], 8 -> je 0x65a20 */
  FUN_00066320();
  /* test eax, eax -> je 0x65a20 */
  /* relift: cmp word ptr [eax + 0xe], (int16_t)edi -> je 0x65a33 */
  FUN_000652f0();
  FUN_00066320();
  /* test eax, eax -> je 0x65a5b */
  FUN_00068a30(0x0025f678, (char *)0x0025f688);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x65a70 */
void TIFFVSetField(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, 0x101 -> je 0x65ace */
  /* relift: test byte ptr [ebx + 0xa], 8 -> je 0x65ace */
  FUN_00066320();
  /* test eax, eax -> je 0x65ace */
  /* relift: cmp word ptr [eax + 0xe], (int16_t)edi -> jne 0x65ace */
  FUN_00066320();
  /* test eax, eax -> je 0x65ac7 */
  FUN_00068a30(0x0025f6b4, (char *)0x0025f688);
  FUN_000652f0();

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x65af0 */
void FUN_00065af0(void)
{
  int ecx = 0;
  int esi = 0;

  /* cmp esi, 0x55 -> ja 0x65d36 */
  TIFFDefaultDirectory();
  FUN_00068a30(0x0025f6c4, (char *)0x0025f6d4);
  /* cmp (int16_t)ecx, 4 -> jne 0x65d79 */

  (void)ecx;
  (void)esi;
}

/* 0x65e90 */
void TIFFGetField(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_00066320();
  /* test eax, eax -> je 0x65ee0 */
  /* cmp (int16_t)eax, 0xffff -> je 0x65ef3 */
  /* relift: test dword ptr [ecx + eax*4 + 0x14], edx -> je 0x65ef3 */
  FUN_00065af0();
  FUN_00068a30(0x0025f704, (char *)0x0025f714);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x65f00 */
void TIFFVGetField(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_00066320();
  /* test eax, eax -> je 0x65f50 */
  /* cmp (int16_t)eax, 0xffff -> je 0x65f63 */
  /* relift: test dword ptr [ecx + eax*4 + 0x14], edx -> je 0x65f63 */
  FUN_00065af0();
  FUN_00068a30(0x0025f704, (char *)0x0025f714);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x65f70 */
void _TIFFgetfield(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x65f90 */
void TIFFFreeDirectory(int file)
{
  int eax = 0;
  int edi = 0;

  /* cmp eax, edi -> je 0x65fbd */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 871);
  /* cmp eax, edi -> je 0x65fe0 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 872);
  /* cmp eax, edi -> je 0x66003 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 873);
  /* cmp eax, edi -> je 0x66026 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 874);
  /* cmp eax, edi -> je 0x66049 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 875);
  /* cmp eax, edi -> je 0x6606c */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 876);
  /* cmp eax, edi -> je 0x6608f */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 877);
  /* cmp eax, edi -> je 0x660b2 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 878);
  /* cmp eax, edi -> je 0x660d5 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 879);
  /* cmp eax, edi -> je 0x660f8 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 880);
  /* cmp eax, edi -> je 0x6611b */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 881);
  /* cmp eax, edi -> je 0x6613e */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 882);
  /* cmp eax, edi -> je 0x66161 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 904);
  /* cmp eax, edi -> je 0x66184 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0025f5c4, 905);

  (void)eax;
  (void)edi;
}

/* 0x66190 */
void FUN_00066190(void)
{
  int esi = 0;

  csmemset((void *)(uintptr_t)esi, 0, 176);
  TIFFSetField(0, 259, 0);

  (void)esi;
}

/* 0x66200 */
void FUN_00066200(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test eax, eax -> je 0x662be */
  __lseek();
  /* cmp eax, ecx -> jne 0x662f8 */
  __read();
  /* cmp eax, 2 -> jne 0x662f8 */
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x66271 */
  FUN_0006f1b0();
  __lseek();
  __read();
  /* cmp eax, 4 -> jne 0x662da */
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x662b2 */
  FUN_0006f1d0();
  /* test ebx, ebx -> jg 0x66220 */
  FUN_00066e70();
  FUN_00068a30(0x002c9a20, (char *)0x0025f750);
  FUN_00068a30(0x002c9a20, (char *)0x0025f72c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x66320 */
void FUN_00066320(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x66380 */
void TIFFDefaultDirectory(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* relift: cmp word ptr [eax], (int16_t)edx -> je 0x663bf */
  /* cmp (int16_t)eax, (int16_t)edx -> je 0x663b7 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x663a4 */
  /* mem[0x003340ac] = ecx */
  /* test eax, eax -> jne 0x663e0 */
  FUN_00068a30(0x0025faa8, (char *)0x0025fabc);
  FUN_001d980b(0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x663f0 */
void FUN_000663f0(void)
{
  int eax = 0;
  int esi = 0;

  debug_malloc(eax, 0, (char *)0x0025faec, 96);
  /* test esi, esi -> jne 0x66423 */
  FUN_00068a30(0, (char *)0x0025fae0);

  (void)eax;
  (void)esi;
}

/* 0x66430 */
void FUN_00066430(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  debug_malloc(0, 0, (char *)0x0025faec, 96);
  /* test ebx, ebx -> jne 0x66465 */
  FUN_00068a30(0, (char *)0x0025fae0);
  FUN_00064f50();
  /* test edi, edi -> jle 0x664bb */
  /* cmp ecx, 4 -> jbe 0x664b5 */
  /* cmp edi, eax -> jbe 0x664fe */
  FUN_00068a30(0, (char *)0x0025fb38);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x66550 */
void FUN_00066550(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  __lseek();
  /* cmp eax, ecx -> jne 0x66593 */
  __read();
  /* cmp eax, edi -> je 0x665b7 */
  TIFFDefaultDirectory();
  FUN_00068a30(0, (char *)0x0025fb68);
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66613 */
  /* cmp eax, 8 -> ja 0x66613 */
  FUN_0006f1f0();
  FUN_0006f220();
  FUN_0006f220();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x66640 */
void FUN_00066640(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int edi = 0;

  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66668 */
  FUN_0006f1d0();
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, edx);
  FUN_00066550();

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)edi;
}

/* 0x666a0 */
void FUN_000666a0(void)
{
  int edx = 0;

  TIFFDefaultDirectory();
  FUN_00068a30(0, (char *)0x0025fb90);
  /* relift: cmp word ptr [edx + 2], 5 -> jne 0x66709 */

  (void)edx;
}

/* 0x66720 */
void FUN_00066720(void)
{
  int eax = 0;

  FUN_00066550();
  /* test eax, eax -> je 0x6675f */
  FUN_000666a0();
  /* test eax, eax -> je 0x6675f */
  /* relift: relift: fld qword ptr [0x2573d8] */

  (void)eax;
}

/* 0x66770 */
void FUN_00066770(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x667d0 */
void FUN_000667d0(void)
{
  int ebx = 0;
  int ecx = 0;

  /* relift: cmp word ptr [ebx + 0xc4], 0x4d4d -> jne 0x6682b */
  /* cmp ecx, 3 -> ja 0x66860 */
  /* cmp ecx, 3 -> ja 0x66860 */
  FUN_00066550();

  (void)ebx;
  (void)ecx;
}

/* 0x668a0 */
void FUN_000668a0(void)
{
  int ebx = 0;

  /* relift: cmp word ptr [ebx + 0xc4], 0x4d4d -> jne 0x668d6 */
  FUN_00066550();

  (void)ebx;
}

/* 0x66900 */
void FUN_00066900(void)
{
  int esi = 0;

  /* relift: cmp dword ptr [esi + 4], 1 -> jne 0x66915 */
  FUN_00066550();

  (void)esi;
}

/* 0x66920 */
void FUN_00066920(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  debug_malloc(eax, ebx, (char *)0x0025faec, 96);
  /* test edi, edi -> jne 0x66976 */
  FUN_00068a30(0, (char *)0x0025fae0);
  FUN_00066550();
  /* test eax, eax -> je 0x669c2 */
  /* test ecx, ecx -> jbe 0x669c2 */
  FUN_000666a0();
  /* cmp ebx, eax -> jb 0x66995 */
  debug_free((void *)(uintptr_t)edi, (char *)0x0025faec, 837);
  FUN_00066550();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x669f0 */
void FUN_000669f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp ecx, 0xa -> ja 0x66c5d */
  FUN_000663f0();
  /* test edi, edi -> je 0x66b0e */
  FUN_000667d0();
  /* test eax, eax -> jne 0x66b49 */
  FUN_000663f0();
  /* test edi, edi -> je 0x66b0e */
  FUN_000668a0();
  /* test eax, eax -> jne 0x66b49 */
  FUN_000663f0();
  /* test edi, edi -> je 0x66b0e */
  FUN_00066900();
  /* test eax, eax -> jne 0x66b49 */
  FUN_000663f0();
  /* test edi, edi -> je 0x66ae1 */
  FUN_00066920();
  /* test eax, eax -> jne 0x66b49 */
  FUN_000663f0();
  /* test edi, edi -> je 0x66b0e */
  FUN_00066550();
  /* test eax, eax -> jne 0x66b49 */
  FUN_000663f0();
  /* test edi, edi -> je 0x66b39 */
  FUN_00066640();
  /* test eax, eax -> jne 0x66b42 */
  TIFFSetField(0, 0, 0);
  /* test edi, edi -> je 0x66c5d */
  debug_free((void *)(uintptr_t)edi, (char *)0x0025faec, 918);
  /* cmp eax, 0xa -> ja 0x66c5d */
  /* relift: cmp word ptr [ebx + 0xc4], 0x4d4d -> jne 0x66bd1 */
  FUN_00066720();
  TIFFSetField(0, 0, 0);
  FUN_00066770();
  TIFFSetField(0, 0, 0);
  FUN_00066640();
  TIFFSetField(0, 0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x66cc0 */
void FUN_00066cc0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp esi, eax -> jne 0x66d2d */
  FUN_000668a0();
  /* test eax, eax -> je 0x66d2d */
  /* cmp esi, eax -> jle 0x66cfc */
  /* relift: cmp word ptr [ebp + eax*2 - 8], (int16_t)ecx -> jne 0x66d0e */
  /* cmp eax, esi -> jl 0x66cf0 */
  TIFFDefaultDirectory();
  FUN_00068a30(0, (char *)0x0025fbdc);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x66d40 */
void FUN_00066d40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ecx -> je 0x66d59 */
  debug_malloc(eax, 0, (char *)0, 0);
  /* test edi, edi -> jne 0x66d92 */
  FUN_00068a30(0, (char *)0x0025fae0);
  FUN_000663f0();
  /* test ebx, ebx -> je 0x66d98 */
  FUN_000668a0();
  /* test esi, esi -> je 0x66dee */
  debug_free((void *)(uintptr_t)ebx, (char *)0x0025faec, 1022);
  /* relift: cmp dword ptr [esi + 4], 1 -> jne 0x66e1f */
  FUN_00066550();
  /* relift: cmp dword ptr [ecx + 4], 1 -> je 0x66e59 */
  FUN_00068a30(0, (char *)0x0025fc3c);
  TIFFSetField(0, 32995, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x66e70 */
void FUN_00066e70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  __lseek();
  /* cmp eax, ecx -> je 0x66ed3 */
  FUN_00068a30(0, (char *)0x0025fde4);
  __read();
  /* cmp eax, 2 -> je 0x66f04 */
  FUN_00068a30(0, (char *)0x0025fdc0);
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66f16 */
  FUN_0006f1b0();
  FUN_000663f0();
  __read();
  /* cmp eax, edx -> je 0x66f73 */
  FUN_00068a30(0, (char *)0x0025fd8c);
  __read();
  /* cmp eax, 4 -> je 0x66f8e */
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66f9d */
  FUN_0006f1d0();
  TIFFFreeDirectory(0);
  FUN_00066190();
  TIFFSetField(0, 284, 0);
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66fed */
  FUN_0006f1f0();
  FUN_0006f220();
  /* relift: cmp (int16_t)eax, word ptr [esi] -> jae 0x67018 */
  /* test eax, eax -> jne 0x67013 */
  FUN_0006f9d0();
  /* test (int16_t)eax, (int16_t)eax -> je 0x67034 */
  /* cmp (int16_t)eax, (int16_t)edx -> jae 0x67069 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x67023 */
  /* test (char)eax, 1 -> jne 0x67186 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x67034 */
  /* cmp (int16_t)eax, (int16_t)edx -> jne 0x67034 */
  /* relift: cmp word ptr [esi + 0xc], 0xffff -> je 0x67039 */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 8] -> je 0x670aa */
  /* test eax, eax -> je 0x670aa */
  /* test (int16_t)eax, (int16_t)eax -> je 0x670c0 */
  /* cmp (int16_t)eax, (int16_t)edx -> jne 0x670c0 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 8] -> jne 0x67088 */
  /* cmp (int16_t)eax, 0xffff -> je 0x670e9 */
  /* cmp (int16_t)eax, 0xfffe -> jne 0x670dd */
  FUN_0006f9d0();
  /* relift: cmp eax, dword ptr [edi + 4] -> jne 0x67039 */
  /* cmp eax, 0x11c -> jg 0x67111 */
  /* cmp eax, 0x17 -> ja 0x6703e */
  /* cmp eax, 0x145 -> jg 0x6715a */
  /* cmp eax, 0x144 -> jge 0x67136 */
  /* cmp eax, 0x142 -> jl 0x6703e */
  /* cmp eax, 0x143 -> jle 0x67170 */
  /* cmp eax, 0x80e5 -> jl 0x6703e */
  /* cmp eax, 0x80e6 -> jg 0x6703e */
  FUN_000669f0();
  /* test eax, eax -> je 0x67586 */
  /* test eax, 0x100000 -> jne 0x67197 */
  /* test (char)eax, 2 -> jne 0x671d5 */
  /* cmp ecx, -1 -> jne 0x671af */
  FUN_0006f820();
  /* test eax, eax -> jbe 0x6723a */
  /* relift: test dword ptr [ebx + 0x14], 0x8000000 -> jne 0x6723a */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
