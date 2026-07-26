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

/* 0x70610 */
void FUN_00070610(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

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

/* 0x708c0 */
void FUN_000708c0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x70a00 */
void FUN_00070a00(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x70b70 */
void FUN_00070b70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> je 0x713f7 */
  /* relift: cmp byte ptr [eax], (char)ebx -> jae 0x70bae */
  /* test ecx, ecx -> je 0x70d1a */
  /* test ebx, ebx -> jle 0x70c22 */
  /* relift: cmp (char)ebx, byte ptr [eax + 1] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax - 1] -> jne 0x70d18 */
  /* test ebx, ebx -> jle 0x70c4d */
  /* relift: cmp (char)ebx, byte ptr [eax + 5] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 4] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 3] -> jne 0x70d18 */
  /* test esi, esi -> jle 0x70c75 */
  /* relift: cmp (char)ebx, byte ptr [eax + 9] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 8] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 7] -> jne 0x70d18 */
  /* test ebx, ebx -> jle 0x70c9c */
  /* relift: cmp (char)ebx, byte ptr [eax + 0xd] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0xc] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0xb] -> jne 0x70d18 */
  /* test ebx, ebx -> jle 0x70cbb */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x11] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x10] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0xf] -> jne 0x70d18 */
  /* test ebx, ebx -> jle 0x70cda */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x15] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x14] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x13] -> jne 0x70d18 */
  /* test ebx, ebx -> jle 0x70cf9 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x19] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x18] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x17] -> jne 0x70d18 */
  /* test ebx, ebx -> jle 0x70d1a */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x1d] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x1c] -> jne 0x70d18 */
  /* relift: cmp (char)ebx, byte ptr [eax + 0x1b] -> je 0x70d1a */
  /* cmp ebx, 0x10 -> jl 0x70bf0 */
  /* test ecx, ecx -> je 0x70d3f */
  FUN_00070a00();
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70de4 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70df9 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70e0f */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70e25 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70e3b */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70e51 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70e67 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70e7d */
  /* cmp ecx, 0xc -> jl 0x70eb0 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70f6a */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70f7d */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70f92 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70fa7 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70fbc */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70fd1 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70fe6 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x70ffb */
  FUN_00070610();
  FUN_00070610();
  /* cmp edx, 3 -> jl 0x710a2 */
  /* cmp edi, 9 -> jl 0x71060 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x71117 */
  FUN_00070a00();
  /* test (char)eax, 0x41 -> jne 0x71130 */
  /* test (char)eax, 0x41 -> jne 0x71146 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_00070a00();
  /* relift: relift: fld dword ptr [0x26151c] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x711fe */
  /* test (char)eax, 0x41 -> jne 0x711fe */
  FUN_000708c0();
  FUN_000706b0();
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* cmp ebx, 0x10 -> je 0x71102 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x713d8 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x7135e */
  /* relift: relift: fld dword ptr [0x254644] */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x713b4 */
  /* relift: relift: fld dword ptr [0x253f40] */
  FUN_001d9068();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

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

/* 0x71d30 */
void FUN_00071d30(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int ebp = 0;

  /* cmp dl, (char)eax -> jbe 0x71d59 */
  /* cmp dl, (char)ecx -> jae 0x71d5f */
  /* cmp dl, (char)eax -> jbe 0x71d67 */
  /* cmp dl, (char)ecx -> jae 0x71d6d */
  /* cmp dl, (char)eax -> jbe 0x71d76 */
  /* cmp dl, (char)ecx -> jae 0x71d7c */
  /* cmp dl, (char)eax -> jbe 0x71d85 */
  /* cmp dl, (char)ecx -> jae 0x71d8b */
  /* cmp dl, (char)eax -> jbe 0x71d94 */
  /* cmp dl, (char)ecx -> jae 0x71d9a */
  /* cmp (char)eax, 0xff -> jne 0x71e92 */
  /* test (char)ecx, (char)ecx -> jne 0x71e92 */
  /* cmp dl, (char)eax -> jae 0x71dc5 */
  /* test dl, dl -> je 0x71dc5 */
  /* cmp dl, (char)ecx -> jbe 0x71dd0 */
  /* cmp dl, 0xff -> je 0x71dd0 */
  /* cmp dl, (char)eax -> jae 0x71ddc */
  /* test dl, dl -> je 0x71ddc */
  /* cmp dl, (char)ecx -> jbe 0x71de7 */
  /* cmp dl, 0xff -> je 0x71de7 */
  /* cmp dl, (char)eax -> jae 0x71df4 */
  /* test dl, dl -> je 0x71df4 */
  /* cmp dl, (char)ecx -> jbe 0x71dff */
  /* cmp dl, 0xff -> je 0x71dff */
  /* cmp dl, (char)eax -> jae 0x71e0c */
  /* test dl, dl -> je 0x71e0c */
  /* cmp dl, (char)ecx -> jbe 0x71e17 */
  /* cmp dl, 0xff -> je 0x71e17 */
  /* cmp dl, (char)eax -> jae 0x71e24 */
  /* test dl, dl -> je 0x71e24 */
  /* cmp dl, (char)ecx -> jbe 0x71e2f */
  /* cmp dl, 0xff -> je 0x71e2f */
  /* cmp dl, (char)eax -> jae 0x71e3c */
  /* test dl, dl -> je 0x71e3c */
  /* cmp dl, (char)ecx -> jbe 0x71e47 */
  /* cmp dl, 0xff -> je 0x71e47 */
  /* cmp dl, (char)eax -> jae 0x71e54 */
  /* test dl, dl -> je 0x71e54 */
  /* cmp dl, (char)ecx -> jbe 0x71e5f */
  /* cmp dl, 0xff -> je 0x71e5f */
  /* cmp dl, (char)eax -> jae 0x71e6c */
  /* test dl, dl -> je 0x71e6c */
  /* cmp dl, (char)ecx -> jbe 0x71e77 */
  /* cmp dl, 0xff -> je 0x71e77 */
  /* cmp (char)eax, (char)ecx -> jae 0x71e8e */
  /* test (char)eax, (char)eax -> jne 0x71ef3 */
  /* cmp (char)eax, 0xff -> jne 0x71eff */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jl 0x71f20 */
  /* test eax, eax -> jle 0x71f2d */
  /* test (char)ecx, 7 -> jne 0x71f5d */
  /* cmp ecx, 8 -> jne 0x71f4b */
  FUN_00070b70();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)ebp;
}

/* 0x71fa0 */
void FUN_00071fa0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x72060 */
void FUN_00072060(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

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

/* 0x73390 */
void FUN_00073390(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  display_assert((char *)0x002616c4, (char *)0x002615b0, 56, 0);
  system_exit(0);
  /* cmp eax, 0xb -> ja 0x73473 */
  csprintf((char *)0x005ab100, (char *)0x00261688);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test eax, eax -> je 0x734e1 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x734b8 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 4] -> jge 0x734c7 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x734d4 */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jge 0x734e1 */
  /* test (char)eax, 0x41 -> jne 0x734fe */
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_00071fa0();
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x18] -> jl 0x7371b */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 4] -> jge 0x7371b */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 0x1c] -> jl 0x7371b */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jge 0x7371b */
  bitmap_2d_address((void *)(uintptr_t)ecx, 0, 0, 0);
  FUN_00072060();
  /* test (char)eax, (char)eax -> je 0x73550 */

  (void)eax;
  (void)ecx;
  (void)ebp;
}

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

/* 0x74a30 */
void FUN_00074a30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x00261d30, (char *)0x002616f0, 1304, 0);
  system_exit(0);
  error(0, (char *)0x00261d04);
  bitmap_cube_map_new(0, 0, 11);
  bitmap_3d_new(0, 0, 0, 0, 11);
  bitmap_2d_new(0, 0, 0, 11);
  /* relift: cmp dword ptr [eax + 0x2c], esi -> je 0x74a71 */
  /* cmp (int16_t)edx, 1 -> jge 0x74b20 */
  /* cmp (int16_t)edx, 1 -> jge 0x74b46 */
  /* cmp (int16_t)eax, 1 -> jge 0x74b6a */
  display_assert((char *)0x00261d30, (char *)0x002616f0, 1346, 0);
  system_exit(0);
  bitmap_cube_map_new(0, 0, 11);
  bitmap_3d_new(0, 0, 0, 0, 11);
  bitmap_2d_new(0, 0, 0, 11);
  /* test ebx, ebx -> je 0x74c05 */
  /* test eax, eax -> je 0x74c05 */
  FUN_000745c0();
  FUN_00074210();
  bitmap_delete((void *)(uintptr_t)ebx);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0x14] -> jle 0x74b01 */
  display_assert((char *)0x00261d30, (char *)0x002616f0, 1383, 0);
  system_exit(0);
  /* test (char)ebx, (char)ebx -> je 0x74c87 */
  /* test (char)ecx, (char)ecx -> je 0x74cd1 */
  /* relift: cmp word ptr [esi + 0x14], (int16_t)edx -> jl 0x74cd1 */
  bitmap_2d_new(0, 0, 0, 11);
  /* test eax, eax -> je 0x74f5b */
  bitmap_mipmap_address((void *)0, 0);
  bitmap_get_pixel_count((void *)(uintptr_t)edi);
  /* test eax, eax -> jle 0x74d2b */
  /* test (char)eax, (char)eax -> je 0x74d3d */
  /* cmp edx, eax -> jg 0x74f6c */
  /* cmp (int16_t)edi, 1 -> jge 0x74d75 */
  /* cmp (int16_t)eax, 1 -> jge 0x74d95 */
  bitmap_2d_new(0, 0, 0, 11);
  /* test esi, esi -> je 0x74f1f */
  /* test eax, eax -> je 0x74f1f */
  display_assert((char *)0x00261d30, (char *)0x002616f0, 1452, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jl 0x74e1b */
  /* relift: cmp word ptr [ebp + 8], (int16_t)edi -> jle 0x74f2e */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
