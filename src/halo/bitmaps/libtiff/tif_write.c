/* kb object: tif_write.obj -> bitmaps/libtiff/tif_write.c */

/* --- tif_write.obj batch drafts (2026-07-26) --- */

/* 0x6e740 */
void FUN_0006e740(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;

  __lseek();
  /* cmp eax, edx -> je 0x6e78a */
  FUN_00068a30(0, (char *)0x00260fcc);
  __read();
  /* cmp eax, ebx -> je 0x6e7c0 */
  FUN_00068a30(0, (char *)0x00260fac);

  (void)eax;
  (void)ebx;
  (void)edx;
}

/* 0x6e7d0 */
void FUN_0006e7d0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;

  __lseek();
  /* cmp eax, edx -> je 0x6e821 */
  FUN_00068a30(0, (char *)0x00261018);
  __read();
  /* cmp eax, ebx -> je 0x6e85e */
  FUN_00068a30(0, (char *)0x00260ff4);

  (void)eax;
  (void)ebx;
  (void)edx;
}

/* 0x6e870 */
void FUN_0006e870(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> je 0x6e8a4 */
  /* relift: test byte ptr [esi + 0xa], 0x40 -> je 0x6e89a */
  debug_free((void *)(uintptr_t)eax, (char *)0x00261070, 515);
  /* test eax, eax -> je 0x6e8ba */
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0x002ecb1c, (char *)0x00261044);

  (void)eax;
  (void)esi;
}

/* 0x6e930 */
void FUN_0006e930(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6e980 */
void FUN_0006e980(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> je 0x6e9f8 */
  /* test eax, eax -> jne 0x6e9f8 */
  /* relift: cmp word ptr [eax + 6], 1 -> jne 0x6ea1a */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
}

/* 0x6ea50 */
void FUN_0006ea50(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + 6], 1 -> jne 0x6ea74 */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)0x0026109c);
  /* cmp edi, eax -> jb 0x6eab8 */
  FUN_00068a30(0, (char *)0x00261110);
  /* cmp eax, -1 -> je 0x6ead0 */
  /* cmp eax, ebx -> jae 0x6ead0 */
  FUN_0006e740();

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x6eaf0 */
void FUN_0006eaf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6ebb0 */
void FUN_0006ebb0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + 6], 1 -> jne 0x6ebd4 */
  FUN_00068a30(0, (char *)0x002610f4);
  /* test (char)ecx, 1 -> je 0x6ebf9 */
  FUN_00068a30(0, (char *)0x002610c8);
  /* cmp edi, eax -> jb 0x6ec20 */
  FUN_00068a30(0, (char *)0x0026115c);
  /* cmp eax, ebx -> jae 0x6ec38 */
  FUN_0006e7d0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x6ec50 */
void FUN_0006ec50(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6ed10 */
void FUN_0006ed10(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x6ede0 */
void FUN_0006ede0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x6eea0 */
void FUN_0006eea0(void)
{
  int eax = 0;
  int ecx = 0;

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

  (void)eax;
  (void)ecx;
}

/* 0x6ef80 */
void FUN_0006ef80(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x6f040 */
void FUN_0006f040(void)
{
  int eax = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 6], 1 -> jne 0x6f064 */
  FUN_00068a30(0, (char *)0x002610f4);
  FUN_00068a30(0, (char *)0x0026109c);
  FUN_0006ed10();
  /* test eax, eax -> je 0x6f0b7 */

  (void)eax;
  (void)edi;
}

/* 0x6f0d0 */
void FUN_0006f0d0(void)
{
  int edx = 0;
  int esi = 0;

  /* cmp esi, edx -> jb 0x6f108 */
  FUN_00068a30(0, (char *)0x002611e0);

  (void)edx;
  (void)esi;
}

/* 0x6f120 */
void FUN_0006f120(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f150 */
void FUN_0006f150(void)
{
  int esi = 0;

  /* cmp esi, -1 -> jne 0x6f162 */
  TIFFScanlineSize();

  (void)esi;
}

/* 0x6f180 */
void FUN_0006f180(void)
{
  int esi = 0;

  /* cmp esi, -1 -> jne 0x6f192 */
  TIFFScanlineSize();

  (void)esi;
}

/* 0x6f1b0 */
void FUN_0006f1b0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f1d0 */
void FUN_0006f1d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f1f0 */
void FUN_0006f1f0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f220 */
void FUN_0006f220(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f260 */
void FUN_0006f260(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f320 */
void FUN_0006f320(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x6f620 */
void FUN_0006f620(void)
{
  int eax = 0;
  int esi = 0;

  FUN_0006f320();
  /* test eax, eax -> je 0x6f65d */
  /* test esi, esi -> jg 0x6f633 */

  (void)eax;
  (void)esi;
}

/* 0x6f670 */
void FUN_0006f670(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f690 */
void FUN_0006f690(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f780 */
void FUN_0006f780(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp edx, ecx -> jb 0x6f7a6 */
  FUN_00068a30(0, (char *)0x002612c8);
  /* cmp edx, ecx -> jb 0x6f7c6 */
  FUN_00068a30(0, (char *)0x002612ac);
  /* cmp edx, ecx -> jb 0x6f7e6 */
  FUN_00068a30(0, (char *)0x0026128c);
  /* relift: cmp word ptr [eax + 0x5e], 2 -> jne 0x6f80e */
  /* cmp edx, ecx -> jb 0x6f80e */
  FUN_00068a30(0, (char *)0x0026126c);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x6f820 */
void FUN_0006f820(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f890 */
void FUN_0006f890(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f8d0 */
void FUN_0006f8d0(void)
{
  int ecx = 0;
  int esi = 0;

  /* test ecx, ecx -> je 0x6f8ff */
  /* test esi, esi -> je 0x6f8ff */
  FUN_0006f890();

  (void)ecx;
  (void)esi;
}

/* 0x6f910 */
void FUN_0006f910(void)
{
  int eax = 0;
  int edi = 0;

  /* test eax, eax -> je 0x6f941 */
  /* test edi, edi -> je 0x6f941 */
  FUN_0006f890();

  (void)eax;
  (void)edi;
}

/* 0x6f950 */
void FUN_0006f950(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x6f96d */
  crt_fprintf((void *)0x00331070, (char *)0x00259f68);
  crt_fprintf((void *)0x00331070, (char *)0x002612e4);
  FUN_001d9850();
  crt_fprintf((void *)0x00331070, (char *)0x00260020);

  (void)eax;
}

/* 0x6f9b0 */
void FUN_0006f9b0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f9d0 */
void FUN_0006f9d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6f9f0 */
void FUN_0006f9f0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6faf0 */
void FUN_0006faf0(void)
{
  int eax = 0;
  int esi = 0;

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

  (void)eax;
  (void)esi;
}

/* 0x6fbd0 */
void FUN_0006fbd0(void)
{
  int edi = 0;

  FUN_0006f910();
  TIFFScanlineSize();
  /* cmp edi, 0x2000 -> jge 0x6fc08 */
  debug_malloc(edi, 0, (char *)0x002612f0, 484);
  FUN_00068a30(0, (char *)0x00261414);

  (void)edi;
}

/* 0x6fc60 */
void FUN_0006fc60(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  debug_realloc((void *)(uintptr_t)ecx, 0, (char *)0, 0);
  debug_realloc((void *)(uintptr_t)eax, 0, (char *)0, 0);
  /* test eax, eax -> je 0x6fd0b */
  csmemset((void *)(uintptr_t)edx, 0, 0);
  csmemset((void *)(uintptr_t)eax, 0, 0);
  FUN_00068a30(0, (char *)0x00261434);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x6fd30 */
void FUN_0006fd30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x6fe10 */
void TIFFFlushData1(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jle 0x6fe8e */
  /* cmp ecx, edx -> je 0x6fe43 */
  /* relift: test byte ptr [esi + 0xa], 0x20 -> jne 0x6fe43 */
  FUN_0006f260();
  FUN_0006fd30();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6fea0 */
int TIFFWriteScanline(int file, void *buffer, int row, int sample)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

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
  FUN_00068a30(0, (char *)0x002611a8);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x700c0 */
void TIFFWriteEncodedStrip(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0006faf0();
  /* test eax, eax -> je 0x700fe */
  /* cmp edi, eax -> jb 0x70105 */
  FUN_00068a30(0x002ed020, (char *)0x002614d0);
  /* test (char)ebx, (char)eax -> jne 0x7012f */
  FUN_0006fbd0();
  /* test eax, eax -> jne 0x7012b */
  /* test eax, eax -> je 0x70123 */
  /* test eax, eax -> jne 0x70173 */
  /* test eax, eax -> je 0x70187 */
  /* test eax, eax -> je 0x70123 */
  /* cmp eax, ecx -> je 0x701af */
  /* relift: test byte ptr [esi + 0xa], 0x20 -> jne 0x701af */
  FUN_0006f260();
  /* test ebx, ebx -> jle 0x701d0 */
  FUN_0006fd30();
  /* test eax, eax -> je 0x70123 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x701f0 */
void TIFFWriteRawStrip(void)
{
  int eax = 0;
  int edi = 0;

  FUN_0006faf0();
  /* test eax, eax -> je 0x7022e */
  /* cmp edi, eax -> jb 0x70235 */
  FUN_00068a30(0x002ed038, (char *)0x002614d0);
  FUN_0006fd30();
  /* test eax, eax -> je 0x70250 */

  (void)eax;
  (void)edi;
}

/* 0x70260 */
void TIFFWriteEncodedTile(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_0006faf0();
  /* test eax, eax -> je 0x702a1 */
  /* cmp edi, eax -> jb 0x702a8 */
  FUN_00068a30(0x002ed04c, (char *)0x002614f4);
  /* test (char)ebx, (char)eax -> jne 0x702d2 */
  FUN_0006fbd0();
  /* test eax, eax -> jne 0x702ce */
  /* test eax, eax -> je 0x702c6 */
  /* relift: cmp dword ptr [ebp + 0x14], eax -> jbe 0x7033c */
  /* test eax, eax -> jne 0x70362 */
  /* test eax, eax -> je 0x7037a */
  /* test eax, eax -> je 0x702c6 */
  /* cmp eax, ecx -> je 0x703a2 */
  /* relift: test byte ptr [esi + 0xa], 0x20 -> jne 0x703a2 */
  FUN_0006f260();
  /* test ebx, ebx -> jle 0x703c3 */
  FUN_0006fd30();
  /* test eax, eax -> je 0x702c6 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x703f0 */
void FUN_000703f0(void)
{
  int eax = 0;
  int edi = 0;

  FUN_0006faf0();
  /* test eax, eax -> je 0x70431 */
  /* cmp edi, eax -> jb 0x70438 */
  FUN_00068a30(0x002ed064, (char *)0x002614f4);
  FUN_0006fd30();
  /* test eax, eax -> je 0x70453 */

  (void)eax;
  (void)edi;
}

/* 0x70460 */
void FUN_00070460(void)
{
  int eax = 0;

  FUN_0006f780();
  /* test eax, eax -> jne 0x7048e */
  FUN_0006f690();
  TIFFWriteEncodedTile();

  (void)eax;
}

/* 0x704c0 */
void FUN_000704c0(void)
{
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
}

/* 0x70570 */
void FUN_00070570(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x705b0 */
void FUN_000705b0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00070610 (0x70610) — XBE naked draft (batch 298). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00070610(void)
{
  __asm__ volatile(
      "flds 0x8(%%eax)\n\t"
      "flds 0x4(%%eax)\n\t"
      "flds (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps (%%ecx)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x10(%%eax)\n\t"
      "fadds (%%eax)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x14(%%eax)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "flds 0x20(%%eax)\n\t"
      "fadds (%%eax)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x14(%%eax)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "flds 0x14(%%eax)\n\t"
      "flds 0x10(%%eax)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x10(%%ecx)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x20(%%eax)\n\t"
      "fadds 0x10(%%eax)\n\t"
      "fmuls 0x14(%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x14(%%ecx)\n\t"
      "flds 0x20(%%eax)\n\t"
      "flds 0x14(%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x20(%%ecx)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00070610: clang naked draft required"
#endif


/* 0x706b0 */
void FUN_000706b0(void)
{
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
}

/* FUN_000708c0 (0x708c0) — XBE naked draft (batch 302). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_000708c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, %%ebx\n\t"
      "movl $0x2ed08c, %%eax\n\t"
      "subl %%edx, %%ebx\n\t"
      "subl %%edx, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $3, -0x8(%%ebp)\n\t"
      "nop\n\t"
      ".LFUN_000708c0_1:\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000708c0_2\n\t"
      "movl $1, %%esi\n\t"
      "jmp .LFUN_000708c0_3\n\t"
      ".LFUN_000708c0_2:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000708c0_3:\n\t"
      "flds (%%ebx,%%ecx,1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000708c0_4\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_000708c0_5\n\t"
      ".LFUN_000708c0_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000708c0_5:\n\t"
      "xorl %%eax, %%esi\n\t"
      "je .LFUN_000708c0_8\n\t"
      "flds (%%ebx,%%ecx,1)\n\t"
      "fsubs (%%ecx)\n\t"
      "fdivrs (%%ecx)\n\t"
      "fchs\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000708c0_6\n\t"
      "movl %%edx, %%eax\n\t"
      "jmp .LFUN_000708c0_7\n\t"
      ".LFUN_000708c0_6:\n\t"
      "fsubs 0x2533c8\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_000708c0_7:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds (%%edi)\n\t"
      "fsubs (%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000708c0_8:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds (%%ecx)\n\t"
      "fcomps (%%eax,%%ecx,1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000708c0_9\n\t"
      "movl $1, %%esi\n\t"
      "jmp .LFUN_000708c0_10\n\t"
      ".LFUN_000708c0_9:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000708c0_10:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds (%%ebx,%%ecx,1)\n\t"
      "fcomps (%%eax,%%ecx,1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000708c0_11\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_000708c0_12\n\t"
      ".LFUN_000708c0_11:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000708c0_12:\n\t"
      "xorl %%eax, %%esi\n\t"
      "je .LFUN_000708c0_15\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds (%%eax,%%ecx,1)\n\t"
      "fsubs (%%ecx)\n\t"
      "flds (%%ebx,%%ecx,1)\n\t"
      "fsubs (%%ecx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds (%%ecx)\n\t"
      "fcomps (%%eax,%%ecx,1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000708c0_13\n\t"
      "movl %%edx, %%eax\n\t"
      "jmp .LFUN_000708c0_14\n\t"
      ".LFUN_000708c0_13:\n\t"
      "fsubs 0x2533c8\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_000708c0_14:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds (%%edi)\n\t"
      "fsubs (%%edx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000708c0_15:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_000708c0_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000708c0: clang naked draft required"
#endif


/* FUN_00070a00 (0x70a00) — XBE naked draft (batch 301). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00070a00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movb 0x2(%%edx), %%cl\n\t"
      "movl (%%edx), %%eax\n\t"
      "shrb $3, %%cl\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movzbw %%cl, %%ax\n\t"
      "movb 0x1(%%edx), %%cl\n\t"
      "shrb $2, %%cl\n\t"
      "movzbw %%cl, %%cx\n\t"
      "shll $6, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movb (%%edx), %%cl\n\t"
      "shrb $3, %%cl\n\t"
      "movzbw %%cl, %%cx\n\t"
      "shll $5, %%eax\n\t"
      "movl $0, 0x4(%%esi)\n\t"
      "orl %%ecx, %%eax\n\t"
      "cmpw $0xffff, %%di\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "je .LFUN_00070a00_18\n\t"
      "movl $1, %%eax\n\t"
      "movl $3, %%ecx\n\t"
      "addl $8, %%edx\n\t"
      "movl $2, -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      ".LFUN_00070a00_1:\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_2\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_3\n\t"
      ".LFUN_00070a00_2:\n\t"
      "movl -0x8(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_3:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_4\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_5\n\t"
      ".LFUN_00070a00_4:\n\t"
      "movl -0x4(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_5:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_6\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_7\n\t"
      ".LFUN_00070a00_6:\n\t"
      "movl (%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_7:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_8\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_9\n\t"
      ".LFUN_00070a00_8:\n\t"
      "movl 0x4(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_9:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_10\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_11\n\t"
      ".LFUN_00070a00_10:\n\t"
      "movl 0x8(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_11:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_12\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_13\n\t"
      ".LFUN_00070a00_12:\n\t"
      "movl 0xc(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_13:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_14\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_15\n\t"
      ".LFUN_00070a00_14:\n\t"
      "movl 0x10(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_15:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00070a00_16\n\t"
      "orl %%ecx, 0x4(%%esi)\n\t"
      "jmp .LFUN_00070a00_17\n\t"
      ".LFUN_00070a00_16:\n\t"
      "movl 0x14(%%edx), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00070a00_17:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "shll $1, %%eax\n\t"
      "shll $2, %%ecx\n\t"
      "addl $0x20, %%edx\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00070a00_1\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "shrl $0x10, %%edx\n\t"
      "shrb $3, %%dl\n\t"
      "movzbw %%dl, %%ax\n\t"
      "movb %%ch, %%dl\n\t"
      "shrb $2, %%dl\n\t"
      "movzbw %%dl, %%dx\n\t"
      "shrb $3, %%cl\n\t"
      "movzbw %%cl, %%cx\n\t"
      "shll $6, %%eax\n\t"
      "popl %%ebx\n\t"
      "orl %%edx, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      ".LFUN_00070a00_18:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00070a00: clang naked draft required"
#endif


/* FUN_00070b70 (0x70b70) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b70b70_c70a00)(void) = FUN_00070a00;
static void (*const b70b70_c70610)(void) = FUN_00070610;
static void (*const b70b70_c708c0)(void) = FUN_000708c0;
static void (*const b70b70_c706b0)(void) = FUN_000706b0;
static void (*const b70b70_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void FUN_00070b70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1a8, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00070b70_65\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movb 0x10(%%ebp), %%bl\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x2c(%%ebp)\n\t"
      "leal 0x3f(%%edx), %%eax\n\t"
      "movl $0x10, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00070b70_1:\n\t"
      "shll $1, %%edi\n\t"
      "cmpb %%bl, (%%eax)\n\t"
      "jae .LFUN_00070b70_2\n\t"
      "andl $0xfffe, %%edi\n\t"
      "jmp .LFUN_00070b70_3\n\t"
      ".LFUN_00070b70_2:\n\t"
      "orl $1, %%edi\n\t"
      "incl %%esi\n\t"
      ".LFUN_00070b70_3:\n\t"
      "subl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00070b70_1\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x2c(%%ebp)\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "jne .LFUN_00070b70_4\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw %%si, (%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movw $0xffff, 0x2(%%eax)\n\t"
      "movl $0xffffffff, 0x4(%%eax)\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00070b70_4:\n\t"
      "movl $1, %%ecx\n\t"
      "movl $2, %%esi\n\t"
      "leal -0x3(%%edx), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00070b70_5:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00070b70_14\n\t"
      "leal -0x2(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_6\n\t"
      "movb 0x5(%%eax), %%bl\n\t"
      "cmpb 0x1(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x4(%%eax), %%bl\n\t"
      "cmpb (%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x3(%%eax), %%bl\n\t"
      "cmpb -0x1(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_6:\n\t"
      "leal -0x1(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_7\n\t"
      "movb 0x9(%%eax), %%bl\n\t"
      "cmpb 0x5(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x8(%%eax), %%bl\n\t"
      "cmpb 0x4(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x7(%%eax), %%bl\n\t"
      "cmpb 0x3(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_00070b70_8\n\t"
      "movb 0xd(%%eax), %%bl\n\t"
      "cmpb 0x9(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0xc(%%eax), %%bl\n\t"
      "cmpb 0x8(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0xb(%%eax), %%bl\n\t"
      "cmpb 0x7(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_8:\n\t"
      "leal 0x1(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_9\n\t"
      "movb 0x11(%%eax), %%bl\n\t"
      "cmpb 0xd(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x10(%%eax), %%bl\n\t"
      "cmpb 0xc(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0xf(%%eax), %%bl\n\t"
      "cmpb 0xb(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_9:\n\t"
      "leal 0x2(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_10\n\t"
      "movb 0x15(%%eax), %%bl\n\t"
      "cmpb 0x11(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x14(%%eax), %%bl\n\t"
      "cmpb 0x10(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x13(%%eax), %%bl\n\t"
      "cmpb 0xf(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_10:\n\t"
      "leal 0x3(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_11\n\t"
      "movb 0x19(%%eax), %%bl\n\t"
      "cmpb 0x15(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x18(%%eax), %%bl\n\t"
      "cmpb 0x14(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x17(%%eax), %%bl\n\t"
      "cmpb 0x13(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_11:\n\t"
      "leal 0x4(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_12\n\t"
      "movb 0x1d(%%eax), %%bl\n\t"
      "cmpb 0x19(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x1c(%%eax), %%bl\n\t"
      "cmpb 0x18(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x1b(%%eax), %%bl\n\t"
      "cmpb 0x17(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      ".LFUN_00070b70_12:\n\t"
      "leal 0x5(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00070b70_14\n\t"
      "movb 0x21(%%eax), %%bl\n\t"
      "cmpb 0x1d(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x20(%%eax), %%bl\n\t"
      "cmpb 0x1c(%%eax), %%bl\n\t"
      "jne .LFUN_00070b70_13\n\t"
      "movb 0x1f(%%eax), %%bl\n\t"
      "cmpb 0x1b(%%eax), %%bl\n\t"
      "je .LFUN_00070b70_14\n\t"
      ".LFUN_00070b70_13:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_00070b70_14:\n\t"
      "addl $8, %%esi\n\t"
      "leal -0x2(%%esi), %%ebx\n\t"
      "addl $0x20, %%eax\n\t"
      "cmpl $0x10, %%ebx\n\t"
      "jl .LFUN_00070b70_5\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00070b70_15\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "call *%[c70a00]\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00070b70_15:\n\t"
      "leal 0x2(%%edx), %%eax\n\t"
      "leal -0x1a4(%%ebp), %%ecx\n\t"
      "movl $0x10, %%edx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00070b70_16:\n\t"
      "movzbl -0x2(%%eax), %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movzbl -0x1(%%eax), %%esi\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "fmuls 0x2ed08c\n\t"
      "movzbl (%%eax), %%esi\n\t"
      "addl $4, %%eax\n\t"
      "fmuls 0x261518\n\t"
      "addl $0x10, %%ecx\n\t"
      "decl %%edx\n\t"
      "fstps -0x14(%%ecx)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "fmuls 0x2ed090\n\t"
      "fmuls 0x261518\n\t"
      "fstps -0x10(%%ecx)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x2ed094\n\t"
      "fmuls 0x261518\n\t"
      "fstps -0xc(%%ecx)\n\t"
      "jne .LFUN_00070b70_16\n\t"
      "fildl -0x2c(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "fdivrs 0x2533c8\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00070b70_17:\n\t"
      "movl $0, -0x1c(%%ebp,%%edx,1)\n\t"
      "movl $1, %%eax\n\t"
      "leal -0x198(%%ebp,%%edx,1), %%ecx\n\t"
      "movl $2, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00070b70_18:\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_19\n\t"
      "flds -0x10(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_19:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_20\n\t"
      "flds (%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_20:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_21\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_21:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_22\n\t"
      "flds 0x20(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_22:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_23\n\t"
      "flds 0x30(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_23:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_24\n\t"
      "flds 0x40(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_24:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_25\n\t"
      "flds 0x50(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_25:\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_26\n\t"
      "flds 0x60(%%ecx)\n\t"
      "fadds -0x1c(%%ebp,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp,%%edx,1)\n\t"
      ".LFUN_00070b70_26:\n\t"
      "shll $1, %%eax\n\t"
      "addl $0x80, %%ecx\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_00070b70_18\n\t"
      "fld %%st(0)\n\t"
      "addl $4, %%edx\n\t"
      "cmpl $0xc, %%edx\n\t"
      "fmuls -0x20(%%ebp,%%edx,1)\n\t"
      "fstps -0x20(%%ebp,%%edx,1)\n\t"
      "jl .LFUN_00070b70_17\n\t"
      "fstp %%st(0)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_00070b70_27\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_00070b70_27:\n\t"
      "flds -0x1c(%%ebp,%%ecx,1)\n\t"
      "leal -0x198(%%ebp,%%ecx,1), %%eax\n\t"
      "movl $2, %%edx\n\t"
      ".LFUN_00070b70_28:\n\t"
      "flds -0x10(%%eax)\n\t"
      "addl $0x80, %%eax\n\t"
      "decl %%edx\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x90(%%eax)\n\t"
      "flds -0x80(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x80(%%eax)\n\t"
      "flds -0x70(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x70(%%eax)\n\t"
      "flds -0x60(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x60(%%eax)\n\t"
      "flds -0x50(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x50(%%eax)\n\t"
      "flds -0x40(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x40(%%eax)\n\t"
      "flds -0x30(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x30(%%eax)\n\t"
      "flds -0x20(%%eax)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%eax)\n\t"
      "jne .LFUN_00070b70_28\n\t"
      "addl $4, %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "cmpl $0xc, %%ecx\n\t"
      "jl .LFUN_00070b70_27\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $3, %%ecx\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "leal -0x198(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jge .LFUN_00070b70_40\n\t"
      ".LFUN_00070b70_29:\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "movl $3, %%esi\n\t"
      "subl %%ecx, %%esi\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      ".LFUN_00070b70_30:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl $0, (%%eax)\n\t"
      "movl $1, %%ecx\n\t"
      "movl $2, -0x8(%%ebp)\n\t"
      ".LFUN_00070b70_31:\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_32\n\t"
      "flds -0x10(%%edx)\n\t"
      "fmuls -0x10(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_32:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_33\n\t"
      "flds (%%edx)\n\t"
      "fmuls (%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_33:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_34\n\t"
      "flds 0x10(%%edx)\n\t"
      "fmuls 0x10(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_34:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_35\n\t"
      "flds 0x20(%%edx)\n\t"
      "fmuls 0x20(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_35:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_36\n\t"
      "flds 0x30(%%edx)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_36:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_37\n\t"
      "flds 0x40(%%edx)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_37:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_38\n\t"
      "flds 0x50(%%edx)\n\t"
      "fmuls 0x50(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_38:\n\t"
      "shll $1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%edi, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .LFUN_00070b70_39\n\t"
      "flds 0x60(%%edx)\n\t"
      "fmuls 0x60(%%esi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00070b70_39:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "shll $1, %%ecx\n\t"
      "addl $0x80, %%edx\n\t"
      "addl $0x80, %%esi\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00070b70_31\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "jne .LFUN_00070b70_30\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      ".LFUN_00070b70_40:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "addl $0x10, %%eax\n\t"
      "cmpl $3, %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_00070b70_29\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_00070b70_41\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00070b70_41:\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "call *%[c70610]\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "leal -0xa8(%%ebp), %%eax\n\t"
      "call *%[c70610]\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fadds -0x64(%%ebp)\n\t"
      "fadds -0x74(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00070b70_45\n\t"
      "fdivrs 0x254644\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl $3, %%edx\n\t"
      "leal -0x74(%%ebp), %%esi\n\t"
      "jge .LFUN_00070b70_44\n\t"
      ".LFUN_00070b70_42:\n\t"
      "movl $3, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "jmp .LFUN_00070b70_43\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00070b70_43:\n\t"
      "fld %%st(0)\n\t"
      "addl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "fmuls -0x4(%%eax)\n\t"
      "fstps -0x4(%%eax)\n\t"
      "jne .LFUN_00070b70_43\n\t"
      ".LFUN_00070b70_44:\n\t"
      "incl %%edx\n\t"
      "addl $0x10, %%esi\n\t"
      "cmpl $3, %%edx\n\t"
      "jl .LFUN_00070b70_42\n\t"
      "incl %%edi\n\t"
      "fstp %%st(0)\n\t"
      "cmpl $9, %%edi\n\t"
      "jl .LFUN_00070b70_41\n\t"
      "flds 0x2533c0\n\t"
      "movl -0x70(%%ebp), %%eax\n\t"
      "flds -0x74(%%ebp)\n\t"
      "movl -0x6c(%%ebp), %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0x60(%%ebp), %%edx\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl %%edx, -0x58(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00070b70_47\n\t"
      "fstp %%st(0)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "flds -0x74(%%ebp)\n\t"
      "jmp .LFUN_00070b70_48\n\t"
      ".LFUN_00070b70_45:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00070b70_46:\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "call *%[c70a00]\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00070b70_47:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      ".LFUN_00070b70_48:\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00070b70_49\n\t"
      "fstp %%st(0)\n\t"
      "movl $1, %%ecx\n\t"
      "flds -0x64(%%ebp)\n\t"
      ".LFUN_00070b70_49:\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00070b70_50\n\t"
      "fstp %%st(0)\n\t"
      "movl $2, %%ecx\n\t"
      "flds -0x54(%%ebp)\n\t"
      ".LFUN_00070b70_50:\n\t"
      "fsqrt\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmuls -0x74(%%ebp,%%ecx,4)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls -0x68(%%ebp,%%ecx,4)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fmuls -0x5c(%%ebp,%%ecx,4)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00070b70_51\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "call *%[c70a00]\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00070b70_51:\n\t"
      "flds 0x26151c\n\t"
      "movl $1, %%edx\n\t"
      "movl $0x47c34f80, -0x8(%%ebp)\n\t"
      "leal -0x1a4(%%ebp), %%ecx\n\t"
      "movl $0x10, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00070b70_52:\n\t"
      "movl %%edx, %%eax\n\t"
      "andl %%edi, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00070b70_54\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fdivs -0xc(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00070b70_53\n\t"
      "fsts -0x8(%%ebp)\n\t"
      ".LFUN_00070b70_53:\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00070b70_54\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".LFUN_00070b70_54:\n\t"
      "shll $1, %%edx\n\t"
      "addl $0x10, %%ecx\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_00070b70_52\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "leal -0x84(%%ebp), %%edi\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c708c0]\n\t"
      "movl -0x2c(%%ebp), %%ebx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x84(%%ebp), %%esi\n\t"
      "leal -0x50(%%ebp), %%edi\n\t"
      "call *%[c706b0]\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fsubs -0x50(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fsubs -0x4c(%%ebp)\n\t"
      "fsts -0x24(%%ebp)\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fsubs -0x48(%%ebp)\n\t"
      "fsts -0x28(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00070b70_55\n\t"
      "cmpl $0x10, %%ebx\n\t"
      "je .LFUN_00070b70_46\n\t"
      ".LFUN_00070b70_55:\n\t"
      "movl $0x8000, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0xb4(%%ebp), %%esi\n\t"
      "movl $0x10, %%ebx\n\t"
      "jmp .LFUN_00070b70_57\n\t"
      ".LFUN_00070b70_56:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00070b70_57:\n\t"
      "andl -0x20(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00070b70_63\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "cmpl $0x10, %%eax\n\t"
      "fadds -0x4(%%esi)\n\t"
      "fsts -0x4(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "fsts (%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fsts 0x4(%%esi)\n\t"
      "fxch %%st(2)\n\t"
      "fsubs -0x50(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fsubs -0x4c(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fsubs -0x48(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fdivs -0xc(%%ebp)\n\t"
      "jne .LFUN_00070b70_60\n\t"
      "fmuls 0x2533d8\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00070b70_58\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00070b70_59\n\t"
      ".LFUN_00070b70_58:\n\t"
      "fcoms 0x2533d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00070b70_59\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254644\n\t"
      ".LFUN_00070b70_59:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%ecx, %%edi\n\t"
      "call *%[ftol]\n\t"
      "movl 0x2ed098(,%%eax,4), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "orl %%edi, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "jmp .LFUN_00070b70_64\n\t"
      ".LFUN_00070b70_60:\n\t"
      "fmuls 0x254644\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00070b70_61\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00070b70_62\n\t"
      ".LFUN_00070b70_61:\n\t"
      "fcoms 0x254644\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00070b70_62\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253f40\n\t"
      ".LFUN_00070b70_62:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%ecx, %%edi\n\t"
      "call *%[ftol]\n\t"
      "movl 0x2ed0a8(,%%eax,4), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "orl %%edi, %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "jmp .LFUN_00070b70_64\n\t"
      ".LFUN_00070b70_63:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "orl $3, %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_00070b70_64:\n\t"
      "shrl $1, -0x8(%%ebp)\n\t"
      "subl $0x10, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00070b70_56\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00070b70_65:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c70a00] "m"(b70b70_c70a00), [c70610] "m"(b70b70_c70610), [c708c0] "m"(b70b70_c708c0), [c706b0] "m"(b70b70_c706b0), [ftol] "m"(b70b70_ftol)
      : "memory");
}
#else
#error "FUN_00070b70: clang naked draft required"
#endif


/* 0x71400 */
void FUN_00071400(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x71422 */
  csmemset((void *)(uintptr_t)eax, 0, 64);
  FUN_000705b0();
  /* cmp ecx, 3 -> jl 0x71550 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x715c0 */
void DecodeBlockRGB__single_pixel(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x715e2 */
  csmemset((void *)(uintptr_t)eax, 0, 64);
  FUN_000705b0();
  /* cmp ecx, 3 -> jl 0x71710 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x71742 */
  /* cmp (int16_t)esi, 4 -> jle 0x71762 */
  display_assert((char *)0x00261530, (char *)0x00261540, 773, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x71770 */
  /* cmp (int16_t)ebx, 4 -> jle 0x71790 */
  display_assert((char *)0x00261520, (char *)0x00261540, 774, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x717b0 */
void FUN_000717b0(void)
{
  int esi = 0;

  FUN_00071400();
  /* cmp esi, 4 -> jl 0x717d0 */

  (void)esi;
}

/* 0x71840 */
void FUN_00071840(void)
{
  DecodeBlockRGB__single_pixel();
}

/* 0x71890 */
void FUN_00071890(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_00071400();
  /* test (char)eax, 7 -> jne 0x71a17 */
  /* test eax, eax -> jne 0x71a06 */
  /* test (char)ecx, 7 -> jne 0x71a55 */
  /* test ecx, ecx -> jne 0x71a44 */
  /* test (char)ecx, 7 -> jne 0x71a90 */
  /* test ecx, ecx -> jne 0x71a7f */
  /* test (char)ecx, 7 -> jne 0x71acb */
  /* test ecx, ecx -> jne 0x71aba */
  /* cmp eax, 0x10 -> jl 0x719f0 */

  (void)eax;
  (void)ecx;
}

/* 0x71af0 */
void FUN_00071af0(void)
{
  int edi = 0;

  DecodeBlockRGB__single_pixel();
  /* cmp (int16_t)edi, 2 -> jge 0x71c74 */

  (void)edi;
}

/* 0x71ca0 */
void FUN_00071ca0(void)
{
  FUN_00070b70();
}

/* 0x71cc0 */
void TIFFWriteRawTile(void)
{
  FUN_00070b70();
}

/* FUN_00071d30 (0x71d30) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b71d30_c70b70)(void) = FUN_00070b70;

__attribute__((naked, noinline))
void FUN_00071d30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movb 0x3(%%edi), %%cl\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movb %%cl, %%al\n\t"
      "leal 0xb(%%edi), %%esi\n\t"
      "movl $3, %%ebx\n\t"
      ".LFUN_00071d30_1:\n\t"
      "movb -0x4(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jbe .LFUN_00071d30_2\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_2:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jae .LFUN_00071d30_3\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_3:\n\t"
      "movb (%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jbe .LFUN_00071d30_4\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_4:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jae .LFUN_00071d30_5\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_5:\n\t"
      "movb 0x4(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jbe .LFUN_00071d30_6\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_6:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jae .LFUN_00071d30_7\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_7:\n\t"
      "movb 0x8(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jbe .LFUN_00071d30_8\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_8:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jae .LFUN_00071d30_9\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_9:\n\t"
      "movb 0xc(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jbe .LFUN_00071d30_10\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_10:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jae .LFUN_00071d30_11\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_11:\n\t"
      "addl $0x14, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00071d30_1\n\t"
      "cmpb $0xff, %%al\n\t"
      "jne .LFUN_00071d30_30\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00071d30_30\n\t"
      "leal 0x7(%%edi), %%esi\n\t"
      "movl $2, %%ebx\n\t"
      ".LFUN_00071d30_12:\n\t"
      "movb -0x4(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_13\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_13\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_13:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_14\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_14\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_14:\n\t"
      "movb (%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_15\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_15\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_15:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_16\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_16\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_16:\n\t"
      "movb 0x4(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_17\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_17\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_17:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_18\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_18\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_18:\n\t"
      "movb 0x8(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_19\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_19\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_19:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_20\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_20\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_20:\n\t"
      "movb 0xc(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_21\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_21\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_21:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_22\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_22\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_22:\n\t"
      "movb 0x10(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_23\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_23\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_23:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_24\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_24\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_24:\n\t"
      "movb 0x14(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_25\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_25\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_25:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_26\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_26\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_26:\n\t"
      "movb 0x18(%%esi), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "jae .LFUN_00071d30_27\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00071d30_27\n\t"
      "movb %%dl, %%al\n\t"
      ".LFUN_00071d30_27:\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jbe .LFUN_00071d30_28\n\t"
      "cmpb $0xff, %%dl\n\t"
      "je .LFUN_00071d30_28\n\t"
      "movb %%dl, %%cl\n\t"
      ".LFUN_00071d30_28:\n\t"
      "addl $0x20, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00071d30_12\n\t"
      "cmpb %%cl, %%al\n\t"
      "jae .LFUN_00071d30_29\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00071d30_31\n\t"
      ".LFUN_00071d30_29:\n\t"
      "orb $0xff, %%al\n\t"
      "xorb %%cl, %%cl\n\t"
      ".LFUN_00071d30_30:\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".LFUN_00071d30_31:\n\t"
      "cmpb %%cl, %%al\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movb %%al, (%%ebx)\n\t"
      "movb %%cl, 0x1(%%ebx)\n\t"
      "je .LFUN_00071d30_41\n\t"
      "movzbl %%al, %%esi\n\t"
      "movzbl %%cl, %%eax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "subl %%eax, %%esi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%esi, %%edi\n\t"
      "sarl $1, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "sete %%cl\n\t"
      "leal 0x5(%%ecx,%%ecx,1), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movl $0xf, %%ecx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00071d30_32:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "shll $3, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LFUN_00071d30_34\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb 0x3(%%eax,%%ecx,4), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00071d30_33\n\t"
      "orl $6, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00071d30_37\n\t"
      ".LFUN_00071d30_33:\n\t"
      "cmpb $0xff, %%al\n\t"
      "jne .LFUN_00071d30_34\n\t"
      "orl $7, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00071d30_37\n\t"
      ".LFUN_00071d30_34:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movzbl 0x3(%%edx,%%ecx,4), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "imull 0xc(%%ebp), %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "cdq\n\t"
      "idivl %%esi\n\t"
      "cmpl 0xc(%%ebp), %%eax\n\t"
      "jl .LFUN_00071d30_35\n\t"
      "orl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00071d30_36\n\t"
      ".LFUN_00071d30_35:\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00071d30_36\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "orl %%eax, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00071d30_36:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      ".LFUN_00071d30_37:\n\t"
      "testb $7, %%cl\n\t"
      "jne .LFUN_00071d30_40\n\t"
      "cmpl $8, %%ecx\n\t"
      "jne .LFUN_00071d30_38\n\t"
      "movb %%dl, 0x5(%%ebx)\n\t"
      "shrl $8, %%edx\n\t"
      "movb %%dl, 0x6(%%ebx)\n\t"
      "shrl $8, %%edx\n\t"
      "movb %%dl, 0x7(%%ebx)\n\t"
      "jmp .LFUN_00071d30_39\n\t"
      ".LFUN_00071d30_38:\n\t"
      "movb %%dl, 0x2(%%ebx)\n\t"
      "shrl $8, %%edx\n\t"
      "movb %%dl, 0x3(%%ebx)\n\t"
      "shrl $8, %%edx\n\t"
      "movb %%dl, 0x4(%%ebx)\n\t"
      ".LFUN_00071d30_39:\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00071d30_40:\n\t"
      "decl %%ecx\n\t"
      "jns .LFUN_00071d30_32\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jmp .LFUN_00071d30_42\n\t"
      ".LFUN_00071d30_41:\n\t"
      "movb $0, 0x7(%%ebx)\n\t"
      "movb $0, 0x6(%%ebx)\n\t"
      "movb $0, 0x5(%%ebx)\n\t"
      "movb $0, 0x4(%%ebx)\n\t"
      "movb $0, 0x3(%%ebx)\n\t"
      "movb $0, 0x2(%%ebx)\n\t"
      ".LFUN_00071d30_42:\n\t"
      "pushl $0\n\t"
      "addl $8, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c70b70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c70b70] "m"(b71d30_c70b70)
      : "memory");
}
#else
#error "FUN_00071d30: clang naked draft required"
#endif


/* 0x71fa0 */
void FUN_00071fa0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00072060 (0x72060) — XBE naked draft (batch 303). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00072060(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw (%%ecx), %%si\n\t"
      "pushl %%edi\n\t"
      "movw 0x2(%%ecx), %%di\n\t"
      "cmpw %%di, %%si\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jle .LFUN_00072060_6\n\t"
      "movw 0xe(%%ecx), %%ax\n\t"
      "movw 0x12(%%ecx), %%bx\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jne .LFUN_00072060_2\n\t"
      ".LFUN_00072060_1:\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00072060_2:\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "subl $0, %%edx\n\t"
      "je .LFUN_00072060_4\n\t"
      "subl $2, %%edx\n\t"
      "jne .LFUN_00072060_10\n\t"
      "cmpw $0, 0xc(%%ecx)\n\t"
      "jge .LFUN_00072060_10\n\t"
      "jmp .LFUN_00072060_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_00072060_3:\n\t"
      "movw 0xe(%%ecx), %%dx\n\t"
      "cmpw %%bx, %%dx\n\t"
      "je .LFUN_00072060_10\n\t"
      "movw 0x4(%%ecx), %%ax\n\t"
      "addw %%di, 0xc(%%ecx)\n\t"
      "addw %%dx, %%ax\n\t"
      "movw %%ax, 0xe(%%ecx)\n\t"
      "cmpw $0, 0xc(%%ecx)\n\t"
      "jl .LFUN_00072060_3\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00072060_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%ecx), %%dx\n\t"
      "testw %%dx, %%dx\n\t"
      "jl .LFUN_00072060_5\n\t"
      "movw 0x6(%%ecx), %%bx\n\t"
      "addw %%bx, 0x10(%%ecx)\n\t"
      "subl %%esi, %%edx\n\t"
      "movw %%dx, 0xc(%%ecx)\n\t"
      ".LFUN_00072060_5:\n\t"
      "movw 0x4(%%ecx), %%dx\n\t"
      "addw %%ax, %%dx\n\t"
      "addw %%di, 0xc(%%ecx)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0xe(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00072060_6:\n\t"
      "movw 0x10(%%ecx), %%ax\n\t"
      "movw 0x14(%%ecx), %%bx\n\t"
      "cmpw %%bx, %%ax\n\t"
      "je .LFUN_00072060_1\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "subl $0, %%edx\n\t"
      "je .LFUN_00072060_8\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_00072060_10\n\t"
      "cmpw $0, 0xc(%%ecx)\n\t"
      "jge .LFUN_00072060_10\n\t"
      ".LFUN_00072060_7:\n\t"
      "movw 0x10(%%ecx), %%dx\n\t"
      "cmpw %%bx, %%dx\n\t"
      "je .LFUN_00072060_10\n\t"
      "movw 0x6(%%ecx), %%ax\n\t"
      "addw %%si, 0xc(%%ecx)\n\t"
      "addw %%dx, %%ax\n\t"
      "movw %%ax, 0x10(%%ecx)\n\t"
      "cmpw $0, 0xc(%%ecx)\n\t"
      "jl .LFUN_00072060_7\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00072060_8:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%ecx), %%dx\n\t"
      "testw %%dx, %%dx\n\t"
      "jl .LFUN_00072060_9\n\t"
      "movw 0x4(%%ecx), %%bx\n\t"
      "addw %%bx, 0xe(%%ecx)\n\t"
      "subl %%edi, %%edx\n\t"
      "movw %%dx, 0xc(%%ecx)\n\t"
      ".LFUN_00072060_9:\n\t"
      "movw 0x6(%%ecx), %%dx\n\t"
      "addw %%ax, %%dx\n\t"
      "addw %%si, 0xc(%%ecx)\n\t"
      "movw %%dx, 0x10(%%ecx)\n\t"
      ".LFUN_00072060_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00072060: clang naked draft required"
#endif


/* 0x721a0 */
void FUN_000721a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x00255d94, (char *)0x002615b0, 275, 0);
  system_exit(0);
  /* test eax, eax -> je 0x721fa */
  FUN_00108bc0();
  /* test (char)eax, (char)eax -> je 0x72482 */
  csprintf((char *)0x005ab100, (char *)0x00261578);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x72298 */
  /* test (int16_t)edi, (int16_t)edi -> jge 0x722b6 */
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x722c3 */
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x722d8 */
  /* cmp (int16_t)ecx, (int16_t)eax -> jg 0x722d8 */
  /* relift: cmp word ptr [ebp - 0x2c], 0 -> jge 0x722e8 */
  /* relift: cmp word ptr [ebp - 0x2c], (int16_t)ecx -> jg 0x722f7 */
  bitmap_2d_address((void *)(uintptr_t)ebx, 0, 0, 0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x72470 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x72470 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x72470 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
  (void)ebp;
}

/* 0x72490 */
void FUN_00072490(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edi, edi -> je 0x724a7 */
  /* test ebx, ebx -> jne 0x724c7 */
  display_assert((char *)0x00261670, (char *)0x002615b0, 458, 0);
  system_exit(0);
  FUN_001089a0((void *)(uintptr_t)edx, 0, 0, 0, 0);
  /* test eax, eax -> je 0x724fd */
  FUN_00108bc0();
  FUN_001089d0();
  FUN_001089a0((void *)(uintptr_t)edx, 0, 0, 0, 0);
  /* test eax, eax -> je 0x72544 */
  FUN_00108bc0();
  /* test esi, esi -> je 0x72564 */
  rect2d_offset((void *)(uintptr_t)edx, ecx, eax);
  rect2d_offset((void *)(uintptr_t)edx, ecx, 0);
  FUN_00108bc0();
  /* test (char)eax, (char)eax -> je 0x72f32 */
  FUN_001089d0();
  /* test esi, esi -> je 0x725cc */
  rect2d_offset((void *)(uintptr_t)edx, ecx, eax);
  rect2d_offset((void *)(uintptr_t)edx, ecx, eax);
  /* relift: cmp word ptr [ebp - 0x30], 0 -> jge 0x72607 */
  display_assert((char *)0x00261650, (char *)0x002615b0, 480, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 0x2e], 0 -> jge 0x7262e */
  display_assert((char *)0x00261630, (char *)0x002615b0, 481, 0);
  system_exit(0);
  FUN_00108a10();
  /* cmp ecx, esi -> jle 0x72699 */
  FUN_00108a10();
  csprintf((char *)0x005ab100, (char *)0x00261618);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_00108a30();
  /* cmp eax, esi -> jle 0x72704 */
  FUN_00108a30();
  csprintf((char *)0x005ab100, (char *)0x00261618);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7277c */
  bitmap_format_get_string(0);
  bitmap_format_get_string(0);
  csprintf((char *)0x005ab100, (char *)0x002615d8);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  bitmap_format_bits_per_pixel(0);
  bitmap_2d_address((void *)(uintptr_t)ecx, 0, 0, 0);
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  FUN_00108a10();
  /* cmp ebx, 0xc -> ja 0x72f04 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x72f21 */
  display_assert((char *)0, (char *)0x002615b0, 640, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x72f70 */
void FUN_00072f70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp eax, esi -> je 0x7300a */
  FUN_00108bc0();
  /* test (char)eax, (char)eax -> je 0x73382 */
  tag_get('mtib', 0);
  /* cmp ecx, edx -> jge 0x73382 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* relift: cmp (int16_t)eax, word ptr [edx + 0x22] -> jge 0x73382 */
  /* test ecx, edx -> je 0x73371 */
  FUN_00077040(0, 0, 0);
  /* test dl, 0x20 -> je 0x731fb */
  /* test ecx, ecx -> je 0x7315a */
  /* cmp (int16_t)esi, (int16_t)ecx -> jle 0x7313c */
  /* test ecx, ecx -> je 0x73191 */
  /* cmp (int16_t)esi, (int16_t)ecx -> jle 0x73173 */
  /* test ecx, ecx -> je 0x731c6 */
  /* cmp (int16_t)esi, (int16_t)ecx -> jle 0x731a9 */
  /* test ecx, ecx -> je 0x731fb */
  /* cmp (int16_t)esi, (int16_t)ecx -> jle 0x731de */
  /* test dl, 0x10 -> je 0x73272 */
  /* test ecx, ecx -> je 0x7321e */
  /* test eax, eax -> je 0x7321e */
  /* test eax, eax -> je 0x7323c */
  /* test edx, edx -> je 0x7323c */
  /* test ecx, ecx -> je 0x73257 */
  /* test ecx, ecx -> je 0x73257 */
  /* test eax, eax -> je 0x73272 */
  /* test eax, eax -> je 0x73272 */
  FUN_00108bc0();
  /* test (char)eax, (char)eax -> je 0x73371 */
  FUN_00108a10();
  FUN_00108a30();
  /* relift: cmp dword ptr [ebp + 0x1c], edx -> je 0x732fb */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x73362 */
  FUN_001089d0();
  FUN_00072490();
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x73310 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* FUN_00073390 (0x73390) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b73390_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b73390_exitfn)(int) = system_exit;
static char * (*const b73390_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b73390_ftol)(void) = FUN_001d9068;
static void (*const b73390_c71fa0)(void) = FUN_00071fa0;
static void * (*const b73390_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static void (*const b73390_c72060)(void) = FUN_00072060;

__attribute__((naked, noinline))
void FUN_00073390(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "movw 0x6(%%ebx), %%dx\n\t"
      "pushl %%esi\n\t"
      "movw %%cx, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $0x18, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%dx, -0x8(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%edx\n\t"
      "movl $0xff, %%edi\n\t"
      "subl %%esi, %%edi\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "jne .LFUN_00073390_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38\n\t"
      "pushl $0x2615b0\n\t"
      "pushl $0x2616c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00073390_1:\n\t"
      "movswl 0xc(%%ebx), %%eax\n\t"
      "cmpl $0xb, %%eax\n\t"
      "ja .LFUN_00073390_5\n\t"
      "movzbl 0x73748(%%eax), %%edx\n\t"
      "jmp *.LFUN_00073390_jt0(,%%edx,4)\n\t"
      ".LFUN_00073390_2:\n\t"
      "movl %%esi, %%ebx\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00073390_6\n\t"
      ".LFUN_00073390_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, %%ebx\n\t"
      "shrl $0x10, %%ebx\n\t"
      "andl $0xf8, %%ebx\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $5, %%ebx\n\t"
      "shrl $8, %%ecx\n\t"
      "andl $0xfc, %%ecx\n\t"
      "orl %%ecx, %%ebx\n\t"
      "shrl $3, %%eax\n\t"
      "shll $3, %%ebx\n\t"
      "andl $0x1f, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "orl %%eax, %%ebx\n\t"
      "cmpw $0xff, %%si\n\t"
      "sete %%dl\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "decl %%edx\n\t"
      "andl $3, %%edx\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00073390_6\n\t"
      ".LFUN_00073390_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $0xff, %%si\n\t"
      "sete %%al\n\t"
      "movl %%ecx, %%ebx\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "decl %%eax\n\t"
      "andl $3, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00073390_6\n\t"
      ".LFUN_00073390_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x52\n\t"
      "pushl $0x2615b0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x261688\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00073390_6:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00073390_10\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00073390_7\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      ".LFUN_00073390_7:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%eax), %%cx\n\t"
      "cmpw -0x4(%%ebp), %%cx\n\t"
      "jge .LFUN_00073390_8\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_00073390_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00073390_9\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      ".LFUN_00073390_9:\n\t"
      "movswl 0x4(%%eax), %%eax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jge .LFUN_00073390_10\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_00073390_10:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "fcomps 0x4(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00073390_11\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "movl %%edx, %%ecx\n\t"
      ".LFUN_00073390_11:\n\t"
      "flds (%%ecx)\n\t"
      "call *%[ftol]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "movw %%ax, 0x10(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "flds (%%edx)\n\t"
      "movw %%ax, 0x12(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x14(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "call *%[ftol]\n\t"
      "leal 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%ebp), %%edx\n\t"
      "movw %%ax, 0x16(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c71fa0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00073390_12:\n\t"
      "movl -0x2a(%%ebp), %%ecx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "jl .LFUN_00073390_21\n\t"
      "cmpw -0x4(%%ebp), %%cx\n\t"
      "jge .LFUN_00073390_21\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "cmpw -0x1c(%%ebp), %%ax\n\t"
      "jl .LFUN_00073390_21\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jge .LFUN_00073390_21\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c940]\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $5, %%ecx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "ja .LFUN_00073390_21\n\t"
      "jmp *.LFUN_00073390_jt1(,%%ecx,4)\n\t"
      ".LFUN_00073390_13:\n\t"
      "movb %%bl, (%%eax)\n\t"
      "jmp .LFUN_00073390_21\n\t"
      ".LFUN_00073390_14:\n\t"
      "movw %%bx, (%%eax)\n\t"
      "jmp .LFUN_00073390_21\n\t"
      ".LFUN_00073390_15:\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "jmp .LFUN_00073390_21\n\t"
      ".LFUN_00073390_16:\n\t"
      "movzwl (%%eax), %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "andl $0x3ff, %%edi\n\t"
      "imull %%edx, %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "andl $0x3ff, %%esi\n\t"
      "imull %%ecx, %%esi\n\t"
      "addl %%esi, %%edi\n\t"
      "andl $0x1f, %%eax\n\t"
      "imull %%edx, %%eax\n\t"
      "movl %%ebx, %%esi\n\t"
      "andl $0x1f, %%esi\n\t"
      "imull %%ecx, %%esi\n\t"
      "imull %%ebx, %%ecx\n\t"
      "addl %%esi, %%eax\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "sarl $8, %%edi\n\t"
      "sarl $8, %%eax\n\t"
      "andl $0x1f, %%eax\n\t"
      "andl $0x3e0, %%edi\n\t"
      "orl %%eax, %%edi\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "imull %%eax, %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "sarl $8, %%ecx\n\t"
      "andl $0x7c00, %%ecx\n\t"
      "orl %%ecx, %%edi\n\t"
      "movw %%di, (%%esi)\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "jmp .LFUN_00073390_20\n\t"
      ".LFUN_00073390_17:\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%ecx, %%esi\n\t"
      "andl $0x7ff, %%esi\n\t"
      "imull %%edx, %%esi\n\t"
      "movl %%ebx, %%edi\n\t"
      "andl $0x7ff, %%edi\n\t"
      "imull %%eax, %%edi\n\t"
      "addl %%edi, %%esi\n\t"
      "movl %%ecx, %%edi\n\t"
      "andl $0x1f, %%edi\n\t"
      "imull %%edx, %%edi\n\t"
      "movl %%ebx, %%edx\n\t"
      "andl $0x1f, %%edx\n\t"
      "imull %%eax, %%edx\n\t"
      "imull %%ebx, %%eax\n\t"
      "addl %%edx, %%edi\n\t"
      "sarl $8, %%esi\n\t"
      "sarl $8, %%edi\n\t"
      "andl $0x7e0, %%esi\n\t"
      "andl $0x1f, %%edi\n\t"
      "orl %%edi, %%esi\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movswl %%di, %%edx\n\t"
      "imull %%edx, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "sarl $8, %%ecx\n\t"
      "andl $0xf800, %%ecx\n\t"
      "orl %%ecx, %%esi\n\t"
      "movw %%si, (%%eax)\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "jmp .LFUN_00073390_21\n\t"
      ".LFUN_00073390_18:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movswl %%si, %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $0x18, %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "ja .LFUN_00073390_19\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      ".LFUN_00073390_19:\n\t"
      "movzbl 0xe(%%ebp), %%esi\n\t"
      "imull %%edx, %%esi\n\t"
      "movswl %%di, %%eax\n\t"
      "movzbl 0x12(%%ebp), %%edi\n\t"
      "imull %%eax, %%edi\n\t"
      "sarl $8, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "andl $0xffffff00, %%edi\n\t"
      "addl %%edi, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "movl %%esi, %%edi\n\t"
      "movzbl %%bh, %%esi\n\t"
      "imull %%edx, %%esi\n\t"
      "movzbl %%ch, %%edx\n\t"
      "imull %%eax, %%edx\n\t"
      "andl $0xffffff00, %%edx\n\t"
      "sarl $8, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "orl %%esi, %%edi\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "andl $0xff, %%edx\n\t"
      "imull %%eax, %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "andl $0xff, %%ecx\n\t"
      "imull -0x20(%%ebp), %%ecx\n\t"
      "sarl $8, %%edx\n\t"
      "shrl $8, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "shll $0x18, %%eax\n\t"
      "orl %%edx, %%edi\n\t"
      "orl %%eax, %%edi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      ".LFUN_00073390_20:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      ".LFUN_00073390_21:\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c72060]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00073390_12\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%ebx)\n\t"
      "addl (%%ebx), %%eax\n\t"
      "addl %%eax, (%%ebx)\n\t"
      "addl (%%ebx), %%eax\n\t"
      "addl (%%edx), %%eax\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00073390_jt0:\n\t"
      ".long .LFUN_00073390_2\n\t"
      ".long .LFUN_00073390_3\n\t"
      ".long .LFUN_00073390_4\n\t"
      ".long .LFUN_00073390_5\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00073390_jt1:\n\t"
      ".long .LFUN_00073390_13\n\t"
      ".long .LFUN_00073390_14\n\t"
      ".long .LFUN_00073390_15\n\t"
      ".long .LFUN_00073390_16\n\t"
      ".long .LFUN_00073390_17\n\t"
      ".long .LFUN_00073390_18\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b73390_assert), [exitfn] "m"(b73390_exitfn), [c8d9d0] "m"(b73390_c8d9d0), [ftol] "m"(b73390_ftol), [c71fa0] "m"(b73390_c71fa0), [c7c940] "m"(b73390_c7c940), [c72060] "m"(b73390_c72060)
      : "memory");
}
#else
#error "FUN_00073390: clang naked draft required"
#endif


/* 0x73770 */
void FUN_00073770(void)
{
  FUN_00073390();
  FUN_00073390();
  FUN_00073390();
  FUN_00073390();
}

/* 0x73830 */
void FUN_00073830(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov byte ptr [0x334148], 1 */
  /* relift: relift: mov byte ptr [0x334149], 0 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* mem[0x0033413c] = ecx */
  bitmap_2d_address((void *)(uintptr_t)edx, 0, 0, 0);
  /* mem[0x00334140] = eax */
  bitmap_2d_address((void *)(uintptr_t)ecx, 0, 0, 0);
  /* mem[0x00334144] = eax */
  /* cmp ecx, 0xff -> je 0x738b5 */
  /* relift: relift: mov byte ptr [0x334148], 0 */
  /* relift: cmp dword ptr [0x33413c], ecx -> jne 0x738ce */
  /* mem[0x00334144] = 0xffff */
  /* relift: relift: mov byte ptr [0x334149], 1 */
  /* relift: cmp word ptr [eax + 4], (int16_t)edi -> jle 0x73934 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  bitmap_2d_address((void *)0, 0, 0, 0);
  /* cmp esi, ecx -> je 0x73927 */
  /* relift: cmp eax, dword ptr [0x334140] -> je 0x73927 */
  /* relift: relift: mov byte ptr [0x334148], 0 */
  /* relift: cmp (int16_t)edi, word ptr [eax + 4] -> jl 0x738e0 */
  /* relift: relift: mov (char)eax, byte ptr [0x334148] */
  /* mem[0x00334144] = eax */
  /* mem[0x00334140] = eax */
  /* mem[0x0033413c] = eax */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x73960 */
int FUN_00073960(int *param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x7398e */
  display_assert((char *)0x002616e0, (char *)0x002616f0, 473, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x334149] */
  /* relift: cmp word ptr [eax + 4], (int16_t)esi -> jle 0x739f6 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, ecx -> je 0x739e0 */
  /* relift: cmp (int16_t)esi, word ptr [eax + 4] -> jl 0x739c0 */
  /* test (char)ebx, (char)ebx -> je 0x739f6 */
  /* test (char)eax, (char)eax -> jne 0x73a12 */
  /* relift: cmp (int16_t)edi, word ptr [eax + 6] -> jl 0x739b0 */
  /* relift: cmp (int16_t)esi, word ptr [eax + 6] -> jge 0x73a71 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, ecx -> jne 0x73a53 */
  /* relift: cmp eax, dword ptr [0x334140] -> jne 0x73a5f */
  /* test (char)ebx, (char)ebx -> jne 0x73a71 */
  /* relift: cmp (int16_t)esi, word ptr [eax + 6] -> jl 0x73a30 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x73a80 */
void FUN_00073a80(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0x73af1 */
  /* relift: cmp (int16_t)edi, word ptr [eax + 6] -> jge 0x73af1 */
  /* relift: cmp word ptr [eax + 4], (int16_t)esi -> jle 0x73af0 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, ecx -> jne 0x73acc */
  /* relift: cmp (int16_t)esi, word ptr [eax + 4] -> jl 0x73aa0 */
  crt_fprintf((void *)0x00331050, (char *)0x00261718);
  crt_fflush((void *)0x00331050);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x73b00 */
void FUN_00073b00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  bitmap_verify((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0x73b45 */
  display_assert((char *)0x00261814, (char *)0x002616f0, 706, edi);
  system_exit(0);
  /* test ecx, edx -> jne 0x73e1a */
  /* cmp eax, 0x400 -> jg 0x73dfd */
  /* relift: relift: mov (int16_t)ecx, word ptr [0x334138] */
  /* relift: relift: mov word ptr [0x334138], (int16_t)ecx */
  bitmap_2d_new(0, 0, 0, 0);
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)esi, word ptr [ebp - 0x10] -> jl 0x73d34 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x33415c] */
  error(0, (char *)0x002617dc);
  error(0, (char *)0x00261798);
  error(0, (char *)0x00261750);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x73e40 */
void FUN_00073e40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0026184c, (char *)0x002616f0, 1015, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x73e95 */
  display_assert((char *)0x00261830, (char *)0x002616f0, 1016, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ebx, word ptr [edi + 4] -> jge 0x73fb7 */
  /* relift: cmp (int16_t)edi, word ptr [ecx + 6] -> jge 0x73fac */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x73f9e */
  /* relift: cmp (int16_t)edi, word ptr [eax + 4] -> jge 0x73f9e */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x73f9e */
  /* relift: cmp (int16_t)ebx, word ptr [eax + 6] -> jge 0x73f9e */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: relift: mov dl, byte ptr [0x334148] */
  /* test dl, dl -> je 0x73f47 */
  /* relift: cmp eax, dword ptr [0x33413c] -> je 0x73f99 */
  /* relift: cmp eax, dword ptr [0x334140] -> je 0x73f99 */
  /* relift: cmp eax, dword ptr [0x334144] -> je 0x73f99 */
  /* relift: cmp word ptr [eax + 4], 0 -> jne 0x73f47 */
  /* test ecx, 0xff000000 -> je 0x73f99 */
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x73f79 */
  /* cmp (int16_t)ebx, (int16_t)eax -> jle 0x73f8e */
  /* relift: cmp (int16_t)edi, word ptr [ecx + 6] -> jl 0x73ed5 */
  /* relift: cmp (int16_t)ebx, word ptr [ecx + 4] -> jl 0x73ec1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x73fd0 */
int FUN_00073fd0(void *bitmap)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x74018 */
  display_assert((char *)0x00261814, (char *)0x002616f0, 1065, 0);
  system_exit(0);
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)esi);
  /* test edx, edx -> je 0x74067 */
  /* cmp edx, 0xff -> je 0x7405e */
  /* cmp eax, 0xff000000 -> jne 0x74081 */
  /* cmp (int16_t)edi, 1 -> jg 0x74081 */
  /* cmp ecx, 0xff -> je 0x7409b */
  /* cmp eax, 0xff0000 -> jne 0x740be */
  /* cmp (int16_t)ebx, 1 -> jg 0x740be */
  /* cmp edx, ecx -> je 0x740c6 */
  /* cmp esi, eax -> jl 0x74040 */
  /* cmp eax, 5 -> ja 0x7417c */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7412d */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7415c */
  /* test (int16_t)ebx, (int16_t)ebx -> jne 0x7416a */
  display_assert((char *)0x00261854, (char *)0x002616f0, 1126, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 2 -> je 0x741d9 */
  /* cmp (int16_t)eax, 5 -> jne 0x741e8 */
  /* relift: test byte ptr [ecx + 6], 2 -> jne 0x741e8 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x74210 */
void FUN_00074210(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7424c */
  display_assert((char *)0x00261aa4, (char *)0x002616f0, 1702, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7426a */
  /* cmp ecx, eax -> je 0x74299 */
  display_assert((char *)0x00261a50, (char *)0x002616f0, 1703, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x742b4 */
  /* cmp ecx, eax -> je 0x742e3 */
  display_assert((char *)0x002619f8, (char *)0x002616f0, 1704, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x742fe */
  /* cmp ecx, eax -> je 0x7432d */
  display_assert((char *)0x002619a0, (char *)0x002616f0, 1705, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7435c */
  display_assert((char *)0x00261974, (char *)0x002616f0, 1707, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xa] -> je 0x74386 */
  display_assert((char *)0x00261944, (char *)0x002616f0, 1708, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x74391 */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x14] -> jle 0x743b1 */
  display_assert((char *)0x002618e8, (char *)0x002616f0, 1709, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xe], 8 -> je 0x743d7 */
  display_assert((char *)0x002618ac, (char *)0x002616f0, 1710, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xe], 2 -> je 0x743fe */
  /* relift: relift: mov (char)eax, byte ptr [0x334148] */
  bitmap_compress_to_mipmap();
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)esi);
  palette_find_closest_match();
  display_assert((char *)0x00261888, (char *)0x002616f0, 1772, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x745c0 */
void FUN_000745c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x745fa */
  display_assert((char *)0x00261c58, (char *)0x002616f0, 1785, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x74618 */
  /* cmp ecx, eax -> je 0x74647 */
  display_assert((char *)0x00261c08, (char *)0x002616f0, 1786, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x74662 */
  /* cmp ecx, eax -> je 0x74691 */
  display_assert((char *)0x00261bb8, (char *)0x002616f0, 1787, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x746ac */
  /* cmp ecx, eax -> je 0x746db */
  display_assert((char *)0x00261b68, (char *)0x002616f0, 1788, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7470a */
  display_assert((char *)0x00261b44, (char *)0x002616f0, 1790, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edx, word ptr [edi + 0xa] -> je 0x74734 */
  display_assert((char *)0x00261b14, (char *)0x002616f0, 1791, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7473f */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0x14] -> jle 0x7475f */
  display_assert((char *)0x00261ac8, (char *)0x002616f0, 1792, 0);
  system_exit(0);
  bitmap_3d_compress_to_mipmap();
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)edi);
  /* test edi, edi -> jle 0x747bf */
  bitmap_format_to_a8r8g8b8();
  /* cmp esi, edi -> jl 0x747a0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x747d0 */
void FUN_000747d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)eax, (int16_t)ebx -> jge 0x7489e */
  FUN_0011feb0();
  /* relift: cmp word ptr [edi + 4], (int16_t)eax -> jne 0x74937 */
  /* test esi, esi -> jne 0x7490e */
  /* cmp (int16_t)ebx, (int16_t)ecx -> jg 0x74881 */
  FUN_00108e20();
  /* cmp eax, 0x200 -> jae 0x748b3 */
  FUN_00108e20();
  /* cmp (int16_t)ebx, 0x20 -> jge 0x74994 */
  FUN_00108e20();
  /* cmp eax, 0x200 -> jae 0x748d3 */
  FUN_00108e20();
  FUN_0011fdb0();
  /* test esi, esi -> je 0x7497f */
  FUN_0011feb0();
  FUN_00120250();
  /* cmp eax, -1 -> je 0x7494a */
  FUN_00120400();
  FUN_00120340();
  /* test esi, esi -> je 0x7497f */
  /* test (char)eax, (char)eax -> je 0x7497f */
  FUN_00120400();
  /* relift: cmp edx, dword ptr [eax + 0x54] -> jl 0x747f8 */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x749f9 */
  /* cmp (int16_t)eax, 0x20 -> jl 0x749ed */
  /* cmp (int16_t)ecx, 0x20 -> jl 0x749ed */
  FUN_001204a0();
  /* test (char)eax, (char)eax -> jne 0x749c2 */
  crt_fprintf((void *)0x00331050, (char *)0x00261c80);
  crt_fflush((void *)0x00331050);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* FUN_00074a30 (0x74a30) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b74a30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b74a30_exitfn)(int) = system_exit;
static void (*const b74a30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b74a30_c7e3f0)(unsigned short width, unsigned short mipmap_count, unsigned short format) = bitmap_cube_map_new;
static void * (*const b74a30_c7e230)(unsigned short width, unsigned short height, unsigned short depth, unsigned short mipmap_count, unsigned short format) = bitmap_3d_new;
static void * (*const b74a30_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static void (*const b74a30_c745c0)(void) = FUN_000745c0;
static void (*const b74a30_c74210)(void) = FUN_00074210;
static void (*const b74a30_c7c8f0)(void *) = bitmap_delete;
static void * (*const b74a30_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static int (*const b74a30_c7dfe0)(void *bitmap) = bitmap_get_pixel_count;
static int (*const b74a30_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;
static void * (*const b74a30_c7cdf0)(void *bitmap, short x, short y, short z, short mipmap_index) = bitmap_cube_map_address;
static void * (*const b74a30_c7cb60)(void *bitmap, short x, short y, short face_index, short mipmap_index) = bitmap_3d_address;
static void * (*const b74a30_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b74a30_c1089d0)(void) = FUN_001089d0;
static void (*const b74a30_c72490)(void) = FUN_00072490;
static void (*const b74a30_c77540)(void *bitmap) = FUN_00077540;

__attribute__((naked, noinline))
void FUN_00074a30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movswl 0xa(%%edi), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "je .LFUN_00074a30_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_2\n\t"
      "pushl $1\n\t"
      "pushl $0x518\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00074a30_1:\n\t"
      "pushl $0x261d04\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00074a30_50\n\t"
      ".LFUN_00074a30_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x14(%%edi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%edi), %%cx\n\t"
      "pushl $0xb\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e3f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00074a30_5\n\t"
      ".LFUN_00074a30_3:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x14(%%edi), %%dx\n\t"
      "pushl $0xb\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%edi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7e230]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_5\n\t"
      ".LFUN_00074a30_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x14(%%edi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%edi), %%dx\n\t"
      "pushl $0xb\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00074a30_5:\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_00074a30_1\n\t"
      "cmpl %%esi, 0x2c(%%eax)\n\t"
      "je .LFUN_00074a30_1\n\t"
      "cmpw %%si, 0x14(%%edi)\n\t"
      "pushl %%ebx\n\t"
      "jl .LFUN_00074a30_18\n\t"
      ".LFUN_00074a30_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%si, %%cx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00074a30_7\n\t"
      "movl $1, 0x8(%%ebp)\n\t"
      "jmp .LFUN_00074a30_8\n\t"
      ".LFUN_00074a30_7:\n\t"
      "movw %%si, %%cx\n\t"
      "sarw %%cl, %%ax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".LFUN_00074a30_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%si, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00074a30_9\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00074a30_10\n\t"
      ".LFUN_00074a30_9:\n\t"
      "movw %%si, %%cx\n\t"
      "sarw %%cl, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_00074a30_10:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%edi), %%dx\n\t"
      "movw %%si, %%cx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarw %%cl, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jge .LFUN_00074a30_11\n\t"
      "movl $1, %%edx\n\t"
      "jmp .LFUN_00074a30_12\n\t"
      ".LFUN_00074a30_11:\n\t"
      "movw %%si, %%cx\n\t"
      "sarw %%cl, %%dx\n\t"
      ".LFUN_00074a30_12:\n\t"
      "movswl 0xa(%%edi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00074a30_15\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_13\n\t"
      "pushl $1\n\t"
      "pushl $0x542\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_17\n\t"
      ".LFUN_00074a30_13:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e3f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00074a30_16\n\t"
      ".LFUN_00074a30_14:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7e230]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_16\n\t"
      ".LFUN_00074a30_15:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00074a30_16:\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00074a30_17\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00074a30_17\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c745c0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c74210]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00074a30_17:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw 0x14(%%edi), %%si\n\t"
      "jle .LFUN_00074a30_6\n\t"
      ".LFUN_00074a30_18:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movswl 0xa(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00074a30_21\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_20\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_19\n\t"
      "pushl $1\n\t"
      "pushl $0x567\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_22\n\t"
      ".LFUN_00074a30_19:\n\t"
      "movl $6, %%ecx\n\t"
      "jmp .LFUN_00074a30_22\n\t"
      ".LFUN_00074a30_20:\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "jmp .LFUN_00074a30_22\n\t"
      ".LFUN_00074a30_21:\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_00074a30_22:\n\t"
      "movb 0x14(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00074a30_23\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "addw $3, %%ax\n\t"
      "imull %%ecx, %%eax\n\t"
      "addl $3, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x6(%%esi), %%di\n\t"
      "leal 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jmp .LFUN_00074a30_24\n\t"
      ".LFUN_00074a30_23:\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "imulw %%cx, %%ax\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x6(%%esi), %%di\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      ".LFUN_00074a30_24:\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00074a30_26\n\t"
      "movl $1, %%edx\n\t"
      "cmpw %%dx, 0x14(%%esi)\n\t"
      "jl .LFUN_00074a30_26\n\t"
      "negb %%bl\n\t"
      "sbbl %%ebx, %%ebx\n\t"
      "andl $4, %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      ".LFUN_00074a30_25:\n\t"
      "movw %%dx, %%cx\n\t"
      "movl %%edi, %%ebx\n\t"
      "sarw %%cl, %%bx\n\t"
      "addl -0x10(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "incl %%edx\n\t"
      "cmpw 0x14(%%esi), %%dx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jle .LFUN_00074a30_25\n\t"
      "movb 0x14(%%ebp), %%bl\n\t"
      ".LFUN_00074a30_26:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7e0b0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_00074a30_47\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00074a30_47\n\t"
      "negb %%bl\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "sbbl %%ebx, %%ebx\n\t"
      "andl $4, %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c7dfe0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00074a30_27\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl $0xff, %%eax\n\t"
      "movl %%ebx, %%edi\n\t"
      "rep stosl\n\t"
      ".LFUN_00074a30_27:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00074a30_28:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00074a30_29\n\t"
      "movswl 0x14(%%esi), %%eax\n\t"
      "jmp .LFUN_00074a30_30\n\t"
      ".LFUN_00074a30_29:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00074a30_30:\n\t"
      "movswl %%bx, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jg .LFUN_00074a30_48\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "negb %%al\n\t"
      "movw %%bx, %%cx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $3, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "movl %%eax, %%edi\n\t"
      "sarw %%cl, %%di\n\t"
      "cmpw $1, %%di\n\t"
      "jge .LFUN_00074a30_31\n\t"
      "movl $1, %%edi\n\t"
      "jmp .LFUN_00074a30_32\n\t"
      ".LFUN_00074a30_31:\n\t"
      "movswl %%ax, %%edi\n\t"
      "movb %%dl, %%cl\n\t"
      "sarl %%cl, %%edi\n\t"
      ".LFUN_00074a30_32:\n\t"
      "movswl 0x4(%%esi), %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "movw %%bx, %%cx\n\t"
      "sarw %%cl, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jge .LFUN_00074a30_33\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00074a30_34\n\t"
      ".LFUN_00074a30_33:\n\t"
      "movswl %%si, %%eax\n\t"
      "movb %%dl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00074a30_34:\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c7e0b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00074a30_45\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00074a30_45\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl 0xa(%%ecx), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00074a30_37\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_36\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_35\n\t"
      "pushl $1\n\t"
      "pushl $0x5ac\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_38\n\t"
      ".LFUN_00074a30_35:\n\t"
      "movl $6, 0x8(%%ebp)\n\t"
      "jmp .LFUN_00074a30_38\n\t"
      ".LFUN_00074a30_36:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%ecx), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jl .LFUN_00074a30_37\n\t"
      "movswl %%bx, %%ecx\n\t"
      "sarw %%cl, %%ax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jmp .LFUN_00074a30_38\n\t"
      ".LFUN_00074a30_37:\n\t"
      "movl $1, 0x8(%%ebp)\n\t"
      ".LFUN_00074a30_38:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x8(%%ebp)\n\t"
      "jle .LFUN_00074a30_46\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00074a30_39:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movswl 0xa(%%eax), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00074a30_42\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_41\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00074a30_40\n\t"
      "pushl $1\n\t"
      "pushl $0x5c8\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_44\n\t"
      ".LFUN_00074a30_40:\n\t"
      "pushl %%esi\n\t"
      "call *%[c7e040]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7cdf0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_43\n\t"
      ".LFUN_00074a30_41:\n\t"
      "pushl %%esi\n\t"
      "call *%[c7e040]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c7cb60]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00074a30_43\n\t"
      ".LFUN_00074a30_42:\n\t"
      "pushl %%esi\n\t"
      "call *%[c7e040]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7d000]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00074a30_43:\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d000]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00074a30_44:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1089d0]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c72490]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw %%bx, %%cx\n\t"
      "sarw %%cl, %%dx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "addl $0x28, %%esp\n\t"
      "addl %%ecx, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "incl %%edi\n\t"
      "cmpw 0x8(%%ebp), %%di\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_00074a30_39\n\t"
      "jmp .LFUN_00074a30_46\n\t"
      ".LFUN_00074a30_45:\n\t"
      "pushl $0x261cd4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00074a30_46:\n\t"
      "pushl %%esi\n\t"
      "call *%[c7c8f0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%eax), %%dx\n\t"
      "movw %%bx, %%cx\n\t"
      "sarw %%cl, %%dx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "addl %%esi, %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "incl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_00074a30_28\n\t"
      ".LFUN_00074a30_47:\n\t"
      "pushl $0x261ca4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00074a30_49\n\t"
      ".LFUN_00074a30_48:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_00074a30_49:\n\t"
      "testl %%edi, %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00074a30_50\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x2c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00074a30_50\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00074a30_50\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c77540]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00074a30_50:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7c8f0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b74a30_assert), [exitfn] "m"(b74a30_exitfn), [c8f390] "m"(b74a30_c8f390), [c7e3f0] "m"(b74a30_c7e3f0), [c7e230] "m"(b74a30_c7e230), [c7e0b0] "m"(b74a30_c7e0b0), [c745c0] "m"(b74a30_c745c0), [c74210] "m"(b74a30_c74210), [c7c8f0] "m"(b74a30_c7c8f0), [c7d000] "m"(b74a30_c7d000), [c7dfe0] "m"(b74a30_c7dfe0), [c7e040] "m"(b74a30_c7e040), [c7cdf0] "m"(b74a30_c7cdf0), [c7cb60] "m"(b74a30_c7cb60), [c8e0b0] "m"(b74a30_c8e0b0), [c1089d0] "m"(b74a30_c1089d0), [c72490] "m"(b74a30_c72490), [c77540] "m"(b74a30_c77540)
      : "memory");
}
#else
#error "FUN_00074a30: clang naked draft required"
#endif

