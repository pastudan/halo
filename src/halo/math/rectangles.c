/* Offset a 2D rectangle by (dx, dy) (0x108a70).
 * rect layout: {top, left, bottom, right} as int16_t[4]. */
void rect2d_offset(int16_t *rect, int16_t dx, int16_t dy)
{
  rect[1] += dx;
  rect[3] += dx;
  rect[0] += dy;
  rect[2] += dy;
}

/* Compute floor(log2(value)) (0x108db0).
 * Returns 0 for value <= 1. */
int16_t FUN_00108db0(unsigned int value)
{
  int result = 0;
  if (value != 0) {
    while (value != 1) {
      value >>= 1;
      result++;
    }
  }
  return (int16_t)result;
}
/* --- rectangles.obj batch drafts (2026-07-26) --- */

/* 0x107c30 */
void FUN_00107c30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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
  FUN_00107520();
  /* test (char)eax, (char)eax -> je 0x107d34 */
  /* cmp (int16_t)edi, (int16_t)esi -> jl 0x107d00 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x107d40 */
void FUN_00107d40(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x107db0 */
void FUN_00107db0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x107ec0 */
void get_edge_vertex(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x108060 */
short FUN_00108060(int16_t count, void *records, int a3, uint16_t *scratch, int max_count, uint16_t *out_list, uint32_t seed)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x108270 */
void get_face_vertex(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

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

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x108400 */
void subdivide_triangle(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1087b0 */
void *FUN_001087b0(int type)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1089a0 */
void FUN_001089a0(int *bounds, int y0, int x0, int h, int w)
{
  /* relift: no calls detected — manual review */
}

/* 0x1089d0 */
void FUN_001089d0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x1089f0 */
void FUN_001089f0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108a10 */
void FUN_00108a10(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108a30 */
void FUN_00108a30(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108a50 */
void FUN_00108a50(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108a90 */
void FUN_00108a90(void)
{
  int eax = 0;

  csprintf((char *)0x005ab100, (char *)0x0028c678);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);

  (void)eax;
}

/* 0x108bc0 */
void FUN_00108bc0(void)
{
  int eax = 0;
  int edx = 0;

  /* cmp (int16_t)eax, (int16_t)edx -> jge 0x108c44 */
  csmemset((void *)(uintptr_t)eax, 0, 0);

  (void)eax;
  (void)edx;
}

/* 0x108c60 */
void FUN_00108c60(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108cd0 */
void FUN_00108cd0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108d00 */
void FUN_00108d00(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108d40 */
void FUN_00108d40(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108d80 */
void FUN_00108d80(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108dd0 */
void FUN_00108dd0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108df0 */
void FUN_00108df0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108e20 */
void FUN_00108e20(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x108e40 */
void FUN_00108e40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
