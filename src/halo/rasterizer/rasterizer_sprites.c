#include <stdint.h>
/* Render sprites by forwarding to the dynavob geometry renderer (0x17cfa0). */
void rasterizer_sprites_render(void *render_data, void *vertices)
{
  FUN_0015f8e0(render_data, vertices);
}
/* --- rasterizer_sprites.obj batch drafts (2026-07-26) --- */

/* FUN_0017cd60 (0x17cd60) — XBE naked draft (batch 398). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cd60(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x27, 0x68, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cd60: clang naked draft required"
#endif


/* FUN_0017cd70 (0x17cd70) — XBE naked draft (batch 398). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cd70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x97, 0x6b, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cd70: clang naked draft required"
#endif


/* 0x17cd80 */
void FUN_0017cd80(void)
{
  int eax = 0;

  FUN_0016fa40(11);
  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */

  (void)eax;
}

/* 0x17cd90 */
void FUN_0017cd90(void)
{
  int eax = 0;

  FUN_0016fa40(11);
  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2163, 0);
  system_exit(0);

  (void)eax;
}

/* 0x17cda0 */
void FUN_0017cda0(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x163c69 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1785, 0);
  system_exit(0);
  FUN_0016f910(12);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163fd2 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x163fd2 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x163fd2 */

  (void)eax;
}

/* FUN_0017cdb0 (0x17cdb0) — XBE naked draft (batch 398). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cdb0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x27, 0x72, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cdb0: clang naked draft required"
#endif


/* FUN_0017cdc0 (0x17cdc0) — XBE naked draft (batch 398). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cdc0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x07, 0x73, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cdc0: clang naked draft required"
#endif


/* 0x17cde0 */
void FUN_0017cde0(void)
{
  int eax = 0;

  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2163, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d0] */
  /* test (char)eax, (char)eax -> je 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d2] */

  (void)eax;
}

/* 0x17cdf0 */
void FUN_0017cdf0(void)
{
  int eax = 0;
  int ebx = 0;

  /* cmp eax, ebx -> jne 0x16440c */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2069, 0);
  system_exit(0);
  FUN_0016f910(13);
  /* relift: cmp word ptr [0x3256bc], (int16_t)ebx -> jne 0x164585 */
  /* relift: cmp byte ptr [0x3256d0], (char)ebx -> je 0x164585 */
  /* relift: cmp byte ptr [0x3256d2], (char)ebx -> je 0x164585 */

  (void)eax;
  (void)ebx;
}

/* FUN_0017ce00 (0x17ce00) — XBE naked draft (batch 398). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017ce00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x87, 0x77, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017ce00: clang naked draft required"
#endif


/* FUN_0017ce10 (0x17ce10) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017ce10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x97, 0x3b, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017ce10: clang naked draft required"
#endif


/* 0x17ce30 */
void FUN_0017ce30(void)
{
  FUN_0016fa40(13);
  FUN_0016f910(14);
  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
}

/* 0x17ce40 */
void FUN_0017ce40(void)
{
  FUN_0016f910(14);
  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
}

/* FUN_0017ce50 (0x17ce50) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017ce50(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x37, 0x78, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017ce50: clang naked draft required"
#endif


/* 0x17ce60 */
void FUN_0017ce60(void)
{
  int eax = 0;

  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */

  (void)eax;
}

/* 0x17ce70 */
void FUN_0017ce70(void)
{
  int eax = 0;

  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);

  (void)eax;
}

/* FUN_0017ce80 (0x17ce80) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017ce80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x67, 0x7e, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017ce80: clang naked draft required"
#endif


/* 0x17ce90 */
void FUN_0017ce90(void)
{
  int eax = 0;

  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);

  (void)eax;
}

/* 0x17cea0 */
void FUN_0017cea0(void)
{
  int eax = 0;

  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x160c99 */

  (void)eax;
}

/* FUN_0017ceb0 (0x17ceb0) — readable C lift (auto_lift_trivial). */
void FUN_00165420(void);
void FUN_0017ceb0(void) {
  FUN_00165420();
}



/* 0x17cec0 */
void FUN_0017cec0(void)
{
  int eax = 0;

  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x160c99 */
  /* cmp (int16_t)eax, 2 -> je 0x160c99 */
  /* cmp (int16_t)eax, 6 -> je 0x160c99 */
  /* cmp (int16_t)eax, 3 -> je 0x160c99 */

  (void)eax;
}

/* 0x17ced0 */
void FUN_0017ced0(void)
{
  int eax = 0;

  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x166439 */
  display_assert((char *)0x002a1e14, (char *)0x002a1cc8, 290, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5de8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16646c */

  (void)eax;
}

/* FUN_0017cee0 (0x17cee0) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cee0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xc7, 0x8d, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cee0: clang naked draft required"
#endif


/* 0x17cef0 */
void FUN_0017cef0(void)
{
  int edi = 0;

  FUN_0016fa40(17);
  /* cmp (int16_t)eax, 4 -> jl 0x165e20 */
  display_assert((char *)0x002a1d18, (char *)0x002a1cc8, 484, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x165e47 */

  (void)edi;
}

/* FUN_0017cf00 (0x17cf00) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cf00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xd7, 0x8e, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cf00: clang naked draft required"
#endif


/* FUN_0017cf10 (0x17cf10) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cf10(int pass_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x77, 0x99, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cf10: clang naked draft required"
#endif


/* FUN_0017cf20 (0x17cf20) — readable C lift (auto_lift_trivial). */
void FUN_001677d0(void);
void FUN_0017cf20(void) {
  FUN_001677d0();
}



/* FUN_0017cf30 (0x17cf30) — readable C lift (jmp thunk to 0x167920). */
void FUN_0017cf30(void)
{
  ((void (*)(void))0x167920)();
}

/* 0x17cf40 */
void FUN_0017cf40(void)
{
  FUN_0016f910(27);
  FUN_0016fa40(27);
  display_assert((char *)0x002a16bc, (char *)0x002a16c4, 220, 0);
  system_exit(0);
}

/* FUN_0017cf50 (0x17cf50) — readable C lift (jmp thunk to 0x15f200). */
void FUN_0017cf50(void)
{
  ((void (*)(void))0x15f200)();
}

/* FUN_0017cf60 (0x17cf60) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cf60(uint32_t source __attribute__((unused)), uint32_t param __attribute__((unused)), int arg3 __attribute__((unused)), int arg4 __attribute__((unused)), uint32_t handle __attribute__((unused)), int subcount2 __attribute__((unused)), float *origin __attribute__((unused)), uint32_t widget_flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xc7, 0x26, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cf60: clang naked draft required"
#endif


/* FUN_0017cf70 (0x17cf70) — readable C lift (jmp thunk to 0x15f210). */
void FUN_0017cf70(void)
{
  ((void (*)(void))0x15f210)();
}


/* FUN_0017cf80 (0x17cf80) — XBE naked draft (batch 399). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cf80(int arg1 __attribute__((unused)), int arg2 __attribute__((unused)), uint32_t handle __attribute__((unused)), int subcount2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xb7, 0x25, 0xfe, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cf80: clang naked draft required"
#endif


/* FUN_0017cf90 (0x17cf90) — readable C lift (jmp thunk to 0x15f220). */
void FUN_0017cf90(void)
{
  ((void (*)(void))0x15f220)();
}


/* FUN_0017cfb0 (0x17cfb0) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cfb0(int object_handle __attribute__((unused)), int datum __attribute__((unused)), float *position __attribute__((unused)), int callback __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xd7, 0xde, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cfb0: clang naked draft required"
#endif


/* FUN_0017cfc0 (0x17cfc0) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cfc0(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x37, 0xe0, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cfc0: clang naked draft required"
#endif


/* FUN_0017cfd0 (0x17cfd0) — XBE naked draft (batch 395). */
#if defined(__clang__)


__attribute__((naked, noinline))
char FUN_0017cfd0(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), short param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xa7, 0xe4, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cfd0: clang naked draft required"
#endif


/* FUN_0017cfe0 (0x17cfe0) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017cfe0(int tex_flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x57, 0xe5, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017cfe0: clang naked draft required"
#endif


/* FUN_0017cff0 (0x17cff0) — readable C lift (jmp thunk to 0x17b580). */
void FUN_0017cff0(void)
{
  ((void (*)(void))0x17b580)();
}


/* FUN_0017d000 (0x17d000) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017d000(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xb7, 0xe5, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017d000: clang naked draft required"
#endif


/* FUN_0017d010 (0x17d010) — readable C lift (jmp thunk). */
void FUN_0017d010(float *position, float radius, float *scale2d, float angle, uint32_t color)
{
  FUN_0017b7d0(position, radius, scale2d, angle, color);
}

/* 0x17d020 */
void FUN_0017d020(void)
{
  int eax = 0;

  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* relift: relift: mov (char)eax, byte ptr [0x3256fc] */
  D3DDevice_GetVisibilityTestResult();

  (void)eax;
}

/* FUN_0017d040 (0x17d040) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017d040(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x77, 0xdd, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017d040: clang naked draft required"
#endif


/* 0x17d050 */
void FUN_0017d050(void)
{
  int ebx = 0;

  interface_get_tag_index(12);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(13);
  FUN_00076ff0(0, 0);
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 27, ebx);
  system_exit(0);

  (void)ebx;
}

/* FUN_0017d060 (0x17d060) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017d060(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xf7, 0x10, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017d060: clang naked draft required"
#endif


/* FUN_0017d070 (0x17d070) — XBE naked draft (batch 400). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017d070(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x67, 0x12, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017d070: clang naked draft required"
#endif


/* FUN_0017d080 (0x17d080) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void (*const b17d080_c15a7f0)(float *p0, float *p1, float *color0, float *color1) = (void *)FUN_0015a7f0;

__attribute__((naked, noinline))
void FUN_0017d080(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fmuls 0x253398\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "flds (%%esi)\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c15a7f0]\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fadds 0x4(%%esi)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c15a7f0]\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fadds 0x8(%%esi)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c15a7f0]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c15a7f0] "m"(b17d080_c15a7f0)
      : "memory");
}
#else
#error "FUN_0017d080: clang naked draft required"
#endif


/* FUN_0017d150 (0x17d150) — XBE naked draft (batch 378). */
#if defined(__clang__)
static void (*const b17d150_c15a7f0)(float *p0, float *p1, float *color0, float *color1) = (void *)FUN_0015a7f0;

__attribute__((naked, noinline))
void FUN_0017d150(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fadds (%%eax)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x8(%%eax)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c15a7f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c15a7f0] "m"(b17d150_c15a7f0)
      : "memory");
}
#else
#error "FUN_0017d150: clang naked draft required"
#endif


/* FUN_0017d1a0 (0x17d1a0) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void (*const b17d1a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17d1a0_exitfn)(int) = system_exit;
static bool (*const b17d1a0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b17d1a0_c16b180)(void) = FUN_0016b180;

__attribute__((naked, noinline))
void FUN_0017d1a0(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0017d1a0_4\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_0017d1a0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2e4\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d1a0_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls 0x2af240\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movswl 0x506548, %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls 0x2af240\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds 0x5a5bdc\n\t"
      "movw $0x15, 0x5a8c80(,%%ecx,2)\n\t"
      "fmuls 0x2af240\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a5bc8\n\t"
      "pushl $0xfff80\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017d1a0_2\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%edx, 0x47e4cc\n\t"
      ".LFUN_0017d1a0_2:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_0017d1a0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2f4\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d1a0_3:\n\t"
      "decw 0x4761d8\n\t"
      "pushl %%ebx\n\t"
      "call *%[c16b180]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017d1a0_4:\n\t"
      "pushl %%ebx\n\t"
      "movl $0xffffffff, 0x47e4cc\n\t"
      "call *%[c16b180]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17d1a0_assert), [exitfn] "m"(b17d1a0_exitfn), [ray] "m"(b17d1a0_ray), [c16b180] "m"(b17d1a0_c16b180)
      : "memory");
}
#else
#error "FUN_0017d1a0: clang naked draft required"
#endif


/* FUN_0017d2b0 (0x17d2b0) — XBE naked draft (batch 298). */
#if defined(__clang__)
static void (*const b17d2b0_chkstk)(void) = FUN_001d90e0;
static void (*const b17d2b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17d2b0_exitfn)(int) = system_exit;
static float * (*const b17d2b0_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;
static void (*const b17d2b0_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b17d2b0_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static float (*const b17d2b0_norm)(float *) = normalize3d;
static char * (*const b17d2b0_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const b17d2b0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b17d2b0_c8dc30)(char *destination, const char *source) = FUN_0008dc30;
static void (*const b17d2b0_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static void (*const b17d2b0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;

__attribute__((naked, noinline))
void FUN_0017d2b0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x20280, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .LFUN_0017d2b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x33e\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x25bc3c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_1:\n\t"
      "movb 0x3256bf, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017d2b0_37\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl 0x47e4cc, %%eax\n\t"
      "jne .LFUN_0017d2b0_37\n\t"
      "cmpw $1, 0x44(%%edi)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl $0xffffffff, -0x28(%%ebp)\n\t"
      "je .LFUN_0017d2b0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x359\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af2d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_2:\n\t"
      "movl 0x48(%%edi), %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "jle .LFUN_0017d2b0_28\n\t"
      "leal -0x2025c(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "jmp .LFUN_0017d2b0_4\n\t"
      ".LFUN_0017d2b0_3:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "jmp .LFUN_0017d2b0_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017d2b0_4:\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "movzwl (%%ecx,%%eax,2), %%eax\n\t"
      "movzwl %%ax, %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "shll $5, %%esi\n\t"
      "movsbl 0x1c(%%esi,%%eax,1), %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "movl $0x55555556, %%eax\n\t"
      "imull %%ecx\n\t"
      "movswl 0x1e(%%esi), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movsbl 0x1d(%%esi), %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%edx, %%edi\n\t"
      "movl $0x55555556, %%eax\n\t"
      "fmuls 0x290dd8\n\t"
      "imull %%ecx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x5c(%%ebp)\n\t"
      "movl $0, -0x58(%%ebp)\n\t"
      "movl $0, -0x54(%%ebp)\n\t"
      "movl $0, -0x50(%%ebp)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "movl $0, -0x48(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "movl $0, -0x44(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x3c(%%ebp)\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x74(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x4(%%ecx), %%di\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "jl .LFUN_0017d2b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x36e\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af2a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_5:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpw 0x4(%%edx), %%bx\n\t"
      "jl .LFUN_0017d2b0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x36f\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af280\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_6:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0017d2b0_7\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0017d2b0_8\n\t"
      ".LFUN_0017d2b0_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x370\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_8:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_0017d2b0_9\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movswl %%di, %%edi\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl %%edi, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[mscale]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_0017d2b0_9:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0017d2b0_10\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movswl %%bx, %%edi\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%edi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_0017d2b0_10:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_0017d2b0_21\n\t"
      "leal -0x20280(%%ebp), %%ecx\n\t"
      ".LFUN_0017d2b0_11:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0017d2b0_12\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0017d2b0_12\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x8(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0017d2b0_13\n\t"
      ".LFUN_0017d2b0_12:\n\t"
      "incl %%edi\n\t"
      "addl $0x40, %%ecx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jl .LFUN_0017d2b0_11\n\t"
      "jmp .LFUN_0017d2b0_21\n\t"
      ".LFUN_0017d2b0_13:\n\t"
      "movb 0x3c(%%ecx), %%al\n\t"
      "cmpb $0xc, %%al\n\t"
      "jae .LFUN_0017d2b0_17\n\t"
      "movzbl %%al, %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0017d2b0_16\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0017d2b0_14:\n\t"
      "movw -0x14(%%ebp), %%bx\n\t"
      "cmpw %%bx, 0xc(%%ecx,%%eax,2)\n\t"
      "je .LFUN_0017d2b0_15\n\t"
      "movzbl 0x3c(%%ecx), %%ebx\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_0017d2b0_14\n\t"
      ".LFUN_0017d2b0_15:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_0017d2b0_16:\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_0017d2b0_17\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "movw %%dx, 0xc(%%ecx,%%esi,2)\n\t"
      "incb 0x3c(%%ecx)\n\t"
      ".LFUN_0017d2b0_17:\n\t"
      "movb 0x3d(%%ecx), %%al\n\t"
      "cmpb $0xc, %%al\n\t"
      "jae .LFUN_0017d2b0_21\n\t"
      "movzbl %%al, %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0017d2b0_20\n\t"
      "xorl %%eax, %%eax\n\t"
      "nop\n\t"
      ".LFUN_0017d2b0_18:\n\t"
      "movswl 0x24(%%ecx,%%eax,2), %%ebx\n\t"
      "movzwl -0x10(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "je .LFUN_0017d2b0_19\n\t"
      "movzbl 0x3d(%%ecx), %%ebx\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_0017d2b0_18\n\t"
      ".LFUN_0017d2b0_19:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_0017d2b0_20:\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_0017d2b0_21\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, 0x24(%%ecx,%%esi,2)\n\t"
      "incb 0x3d(%%ecx)\n\t"
      ".LFUN_0017d2b0_21:\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_0017d2b0_27\n\t"
      "cmpl $0x800, %%ebx\n\t"
      "jge .LFUN_0017d2b0_27\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "fsubs 0x5a5bc8\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "leal -0x24(%%ecx), %%eax\n\t"
      "fsubs 0x5a5bcc\n\t"
      "movl %%edx, (%%eax)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "fsubs 0x5a5bd0\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "movw -0x14(%%ebp), %%ax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "fld %%st(2)\n\t"
      "movw %%ax, -0x18(%%ecx)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movb $1, 0x18(%%ecx)\n\t"
      "movb $1, 0x19(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0017d2b0_22\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xcc\n\t"
      "fxch %%st(2)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fxch %%st(2)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "jmp .LFUN_0017d2b0_23\n\t"
      ".LFUN_0017d2b0_22:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0017d2b0_23:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x5a5bd8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmuls 0x5a5bd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls -0x64(%%ebp)\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fxch %%st(2)\n\t"
      "fmuls -0x68(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0017d2b0_24\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0017d2b0_25\n\t"
      ".LFUN_0017d2b0_24:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0017d2b0_26\n\t"
      ".LFUN_0017d2b0_25:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      ".LFUN_0017d2b0_26:\n\t"
      "incl %%ebx\n\t"
      "addl $0x40, %%ecx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      ".LFUN_0017d2b0_27:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x48(%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $2, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_0017d2b0_3\n\t"
      ".LFUN_0017d2b0_28:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "jle .LFUN_0017d2b0_36\n\t"
      "leal -0x20244(%%ebp), %%ebx\n\t"
      "jmp .LFUN_0017d2b0_29\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017d2b0_29:\n\t"
      "cmpl -0x28(%%ebp), %%edi\n\t"
      "leal -0x3c(%%ebx), %%esi\n\t"
      "jne .LFUN_0017d2b0_34\n\t"
      "pushl $0x2af250\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dff0]\n\t"
      "movzbl (%%ebx), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_0017d2b0_31\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017d2b0_30:\n\t"
      "xorl %%edx, %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movswl 0xc(%%esi,%%eax,2), %%eax\n\t"
      "setne %%dl\n\t"
      "leal -0x180(%%ebp), %%ecx\n\t"
      "decl %%edx\n\t"
      "andl $0xfffffff4, %%edx\n\t"
      "addl $0x2c, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2af248\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x180(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movzbl (%%ebx), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0017d2b0_30\n\t"
      ".LFUN_0017d2b0_31:\n\t"
      "pushl $0x2af244\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movzbl 0x3d(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_0017d2b0_33\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0017d2b0_32:\n\t"
      "xorl %%edx, %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movswl 0x24(%%esi,%%eax,2), %%eax\n\t"
      "setne %%dl\n\t"
      "leal -0x280(%%ebp), %%ecx\n\t"
      "decl %%edx\n\t"
      "andl $0xfffffff4, %%edx\n\t"
      "addl $0x2c, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2af248\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x280(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movzbl 0x3d(%%esi), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0017d2b0_32\n\t"
      ".LFUN_0017d2b0_33:\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d000000\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5ab100\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_0017d2b0_35\n\t"
      ".LFUN_0017d2b0_34:\n\t"
      "movl 0x2ee6c4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3d000000\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0017d2b0_35:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%edi\n\t"
      "addl $0x40, %%ebx\n\t"
      "cmpl %%eax, %%edi\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "jl .LFUN_0017d2b0_29\n\t"
      ".LFUN_0017d2b0_36:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017d2b0_37:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b17d2b0_chkstk), [assert] "m"(b17d2b0_assert), [exitfn] "m"(b17d2b0_exitfn), [c17ffc0] "m"(b17d2b0_c17ffc0), [xfrmpt] "m"(b17d2b0_xfrmpt), [mscale] "m"(b17d2b0_mscale), [norm] "m"(b17d2b0_norm), [c8dff0] "m"(b17d2b0_c8dff0), [c1d90f0] "m"(b17d2b0_c1d90f0), [c8dc30] "m"(b17d2b0_c8dc30), [c189150] "m"(b17d2b0_c189150), [c189cb0] "m"(b17d2b0_c189cb0)
      : "memory");
}
#else
#error "FUN_0017d2b0: clang naked draft required"
#endif


/* FUN_0017d8f0 (0x17d8f0) — XBE naked draft (batch 370). */
#if defined(__clang__)
static int (*const b17d8f0_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void FUN_0017d8f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x2546a4\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b17d8f0_gtime)
      : "memory");
}
#else
#error "FUN_0017d8f0: clang naked draft required"
#endif


/* rasterizer_screen_effects_initialize (0x17d910) — XBE naked draft (batch 387). */
#if defined(__clang__)
static void * (*const b17d910_c1bfbf0)(const char *name, const char *a2, int size) = (void *)game_state_malloc;
static void (*const b17d910_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17d910_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void rasterizer_screen_effects_initialize(void)
{
  __asm__ volatile(
      "pushl $0x78\n\t"
      "pushl $0\n\t"
      "pushl $0x2af368\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x47e4d4\n\t"
      "jne .Lrasterizer_screen_effects_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0x36\n\t"
      "pushl $0x2af334\n\t"
      "pushl $0x2af314\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_screen_effects_initialize_1:\n\t"
      "ret\n\t"
      :
      : [c1bfbf0] "m"(b17d910_c1bfbf0), [assert] "m"(b17d910_assert), [exitfn] "m"(b17d910_exitfn)
      : "memory");
}
#else
#error "rasterizer_screen_effects_initialize: clang naked draft required"
#endif


/* FUN_0017d950 (0x17d950) — XBE naked draft (batch 381). */
#if defined(__clang__)
static void *(*const b17d950_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_0017d950(void)
{
  __asm__ volatile(
      "movl 0x47e4d4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017d950_1\n\t"
      "pushl $0x78\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "movl %%ecx, 0x64(%%eax)\n\t"
      "movl %%ecx, 0x68(%%eax)\n\t"
      "movl %%ecx, 0x6c(%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, 0x70(%%eax)\n\t"
      ".LFUN_0017d950_1:\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b17d950_memset)
      : "memory");
}
#else
#error "FUN_0017d950: clang naked draft required"
#endif


/* 0x17d980 */
void FUN_0017d980(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d990 */
void FUN_0017d990(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0017d9a0 (0x17d9a0) — readable C lift. */
void FUN_0017d9a0(short index, float value)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr && index >= 0 && index < 4) {
    *(float *)(spr + 0x64 + (int)index * 4) = value;
  }
}

/* FUN_0017d9d0 (0x17d9d0) — readable C lift. */
float FUN_0017d9d0(short index)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (!spr || index < 0 || index >= 4) {
    return *(float *)0x2533c0;
  }
  return *(float *)(spr + 0x64 + (int)index * 4);
}

/* FUN_0017da00 (0x17da00) — XBE naked draft (batch 381). */
#if defined(__clang__)
static void *(*const b17da00_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_0017da00(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017da00_3\n\t"
      "movb 0x8(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0017da00_1\n\t"
      "movb 0x39(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0017da00_2\n\t"
      ".LFUN_0017da00_1:\n\t"
      "pushl $0x38\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0x39(%%eax)\n\t"
      ".LFUN_0017da00_2:\n\t"
      "movb $1, 0x38(%%eax)\n\t"
      ".LFUN_0017da00_3:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b17da00_memset)
      : "memory");
}
#else
#error "FUN_0017da00: clang naked draft required"
#endif


/* FUN_0017da40 (0x17da40) — XBE naked draft (batch 323). */
#if defined(__clang__)
static int (*const b17da40_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void FUN_0017da40(int a0 __attribute__((unused)), int a1 __attribute__((unused)), float a2 __attribute__((unused)), float a3 __attribute__((unused)), float a4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0017da40_1\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      "movb %%cl, 0x23(%%eax)\n\t"
      "movw %%cx, 0x24(%%eax)\n\t"
      "movl %%ecx, 0x28(%%eax)\n\t"
      "movl %%ecx, 0x2c(%%eax)\n\t"
      "movl %%ecx, 0x30(%%eax)\n\t"
      "movl %%ecx, 0x34(%%eax)\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x3c(%%eax)\n\t"
      "movl %%edx, 0x40(%%eax)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "fmuls 0x2546a4\n\t"
      "fld %%st(0)\n\t"
      "fstps 0x44(%%eax)\n\t"
      "fadds 0x18(%%ebp)\n\t"
      "fstps 0x48(%%eax)\n\t"
      ".LFUN_0017da40_1:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b17da40_gtime)
      : "memory");
}
#else
#error "FUN_0017da40: clang naked draft required"
#endif


/* FUN_0017dab0 (0x17dab0) — XBE naked draft (batch 318). */
#if defined(__clang__)
static int (*const b17dab0_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void FUN_0017dab0(int a0 __attribute__((unused)), float a1 __attribute__((unused)), float a2 __attribute__((unused)), float a3 __attribute__((unused)), int a4 __attribute__((unused)), float a5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_0017dab0_1\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb %%bl, 0x23(%%eax)\n\t"
      "movw %%bx, 0x24(%%eax)\n\t"
      "movl %%ebx, 0x28(%%eax)\n\t"
      "movl %%ebx, 0x2c(%%eax)\n\t"
      "movl %%ebx, 0x30(%%eax)\n\t"
      "movl %%ebx, 0x34(%%eax)\n\t"
      "movl %%ecx, 0x4c(%%eax)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x50(%%eax)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x54(%%eax)\n\t"
      "movl %%edx, 0x58(%%eax)\n\t"
      "call *%[gtime]\n\t"
      "movb 0x18(%%ebp), %%cl\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "fmuls 0x2546a4\n\t"
      "fld %%st(0)\n\t"
      "fstps 0x5c(%%eax)\n\t"
      "fadds 0x1c(%%ebp)\n\t"
      "fstps 0x60(%%eax)\n\t"
      "movb %%cl, 0x20(%%eax)\n\t"
      "movb %%bl, 0x21(%%eax)\n\t"
      "movb %%bl, 0x22(%%eax)\n\t"
      ".LFUN_0017dab0_1:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b17dab0_gtime)
      : "memory");
}
#else
#error "FUN_0017dab0: clang naked draft required"
#endif


/* FUN_0017db20 (0x17db20) — readable C lift. */
void FUN_0017db20(int a, int b, int c)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    *(int *)(spr + 0x14) = a;
    *(int *)(spr + 0x18) = b;
    *(int *)(spr + 0x1c) = c;
  }
}

/* rasterizer_screen_effect_set_video (0x17db40) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b17db40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17db40_exitfn)(int) = system_exit;
static void *(*const b17db40_memset)(void *, int, unsigned int) = csmemset;
static void *(*const b17db40_tag)(int, int) = tag_get;
static void *(*const b17db40_elem)(void *, int, int) = tag_block_get_element;
static void (*const b17db40_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_screen_effect_set_video(int a0 __attribute__((unused)), float a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lrasterizer_screen_effect_set_video_3\n\t"
      "movl 0x476204, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .Lrasterizer_screen_effect_set_video_1\n\t"
      "pushl $1\n\t"
      "pushl $0xe1\n\t"
      "pushl $0x2af334\n\t"
      "pushl $0x29da1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x476204, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_screen_effect_set_video_1:\n\t"
      "cmpl $-1, 0x128(%%eax)\n\t"
      "je .Lrasterizer_screen_effect_set_video_2\n\t"
      "cmpl $-1, 0x138(%%eax)\n\t"
      "je .Lrasterizer_screen_effect_set_video_2\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "pushl $0x38\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x47e4d4, %%eax\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "movl %%esi, 0x3c(%%eax)\n\t"
      "movl %%esi, 0x40(%%eax)\n\t"
      "movl %%esi, 0x44(%%eax)\n\t"
      "movl %%esi, 0x48(%%eax)\n\t"
      "movl %%esi, 0x4c(%%eax)\n\t"
      "movl %%esi, 0x50(%%eax)\n\t"
      "movl %%esi, 0x54(%%eax)\n\t"
      "movl %%esi, 0x58(%%eax)\n\t"
      "movl %%esi, 0x5c(%%eax)\n\t"
      "movl %%esi, 0x60(%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0x23(%%eax)\n\t"
      "movw %%cx, 0x24(%%eax)\n\t"
      "movl 0x476204, %%edx\n\t"
      "movl 0x128(%%edx), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x60, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x47e4d4, %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, 0x28(%%ecx)\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x2c(%%ecx)\n\t"
      "movl $0x3f800000, 0x30(%%ecx)\n\t"
      "movl 0x476204, %%eax\n\t"
      "movl 0x138(%%eax), %%ecx\n\t"
      "pushl $0x30\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x60, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x47e4d4, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0x34(%%edx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_screen_effect_set_video_2:\n\t"
      "pushl $0x2af380\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_screen_effect_set_video_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17db40_assert), [exitfn] "m"(b17db40_exitfn), [memset] "m"(b17db40_memset), [tag] "m"(b17db40_tag), [elem] "m"(b17db40_elem), [c8f390] "m"(b17db40_c8f390)
      : "memory");
}
#else
#error "rasterizer_screen_effect_set_video: clang naked draft required"
#endif


/* FUN_0017dc60 (0x17dc60) — readable C lift. */
void FUN_0017dc60(void)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    spr[0x38] = 0;
  }
}

/* 0x17dc70 */
void *rasterizer_screen_effect_get_cinematic_parameters(void *effect)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp ecx, ebx -> je 0x17deb4 */
  /* relift: cmp byte ptr [ecx + 0x38], (char)ebx -> je 0x17deb4 */
  game_time_get();
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0017d8f0();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> je 0x17dd11 */
  FUN_0017d8f0();
  game_time_get();
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0017d8f0();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> je 0x17dd9e */
  FUN_0017d8f0();
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)eax);
  scalars_interpolate_and_clamp_0_to_1(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)edx);
  scalars_interpolate_and_clamp_0_to_1(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)ecx);
  csmemcmp((void *)(uintptr_t)edx, (void *)0, 0);
  /* test eax, eax -> jne 0x17de29 */
  /* relift: relift: fcomp dword ptr [0x253f44] */
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x17de71 */
  display_assert((char *)0x002af3d0, (char *)0x002af334, 336, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x253f44] */
  /* relift: relift: fcomp dword ptr [0x253f44] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 1 -> jne 0x17dead */
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* FUN_0017dec0 (0x17dec0) — readable C lift. */
void FUN_0017dec0(int value)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    *(int *)(spr + 0x74) = value;
  }
}

/* FUN_0017dee0 (0x17dee0) — readable C lift. */
float FUN_0017dee0(void)
{
  char *spr;
  float v;

  spr = *(char **)0x47e4d4;
  v = *(float *)0x2af1ac;
  if (spr) {
    if (*(float *)(spr + 0x74) > *(float *)0x2533c0) {
      v = *(float *)(spr + 0x74);
    }
  }
  return v;
}

/* FUN_0017df10 (0x17df10) — XBE naked draft (batch 365). */
#if defined(__clang__)
static void (*const b17df10_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_0017df10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpl $0x2000, %%eax\n\t"
      "jge .LFUN_0017df10_1\n\t"
      "cmpl $0x2000, 0x47e4f4\n\t"
      "jge .LFUN_0017df10_1\n\t"
      "leal 0x1(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x47e4f4, %%edx\n\t"
      "incl %%edx\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "movl %%edx, 0x47e4f4\n\t"
      "jne .LFUN_0017df10_3\n\t"
      "incl 0x5a5540\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017df10_1:\n\t"
      "movb 0x47e4f8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0017df10_2\n\t"
      "pushl $0x2af460\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x47e4f8\n\t"
      ".LFUN_0017df10_2:\n\t"
      "movl %%esi, %%eax\n\t"
      ".LFUN_0017df10_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8f390] "m"(b17df10_c8f390)
      : "memory");
}
#else
#error "FUN_0017df10: clang naked draft required"
#endif


/* FUN_0017df80 (0x17df80) — XBE naked draft (batch 384). */
#if defined(__clang__)
static void * (*const b17df80_c8ee60)(uint32_t size, bool zero, const char *file, int line) = (void *)debug_malloc;
static void (*const b17df80_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_0017df80(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl $0x60\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0\n\t"
      "pushl $0x78000\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c8ee60]\n\t"
      "pushl $0x61\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0\n\t"
      "pushl $0x78000\n\t"
      "movl %%eax, 0x47e4dc\n\t"
      "call *%[c8ee60]\n\t"
      "pushl $0x62\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0\n\t"
      "pushl $0x78000\n\t"
      "movl %%eax, 0x47e4e4\n\t"
      "call *%[c8ee60]\n\t"
      "movl 0x47e4dc, %%ecx\n\t"
      "addl $0x30, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x47e4ec\n\t"
      "je .LFUN_0017df80_1\n\t"
      "movl 0x47e4e4, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0017df80_1\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017df80_1\n\t"
      "movb %%bl, 0x47e4d8\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_0017df80_1:\n\t"
      "pushl $0x2af48c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "movb %%al, 0x47e4d8\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b17df80_c8ee60), [c8f390] "m"(b17df80_c8f390)
      : "memory");
}
#else
#error "FUN_0017df80: clang naked draft required"
#endif


/* FUN_0017e010 (0x17e010) — readable C lift. */
void FUN_0017e010(void)
{
  *(int *)0x47e4e0 = 0;
  *(int *)0x47e4e8 = 0;
  *(int *)0x47e4f0 = 0;
  *(int *)0x47e4f4 = 0;
}

/* 0x17e030 */
void FUN_0017e030(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0017e040 (0x17e040) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b17e040_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e040_exitfn)(int) = system_exit;
static void (*const b17e040_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void FUN_0017e040(void)
{
  __asm__ volatile(
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e040_4\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e040_1\n\t"
      "pushl $1\n\t"
      "pushl $0x89\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e040_1:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e040_2\n\t"
      "pushl $1\n\t"
      "pushl $0x8a\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e040_2:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e040_3\n\t"
      "pushl $1\n\t"
      "pushl $0x8b\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e040_3:\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "pushl $0x8d\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "movl 0x47e4e4, %%ecx\n\t"
      "pushl $0x8e\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8ef70]\n\t"
      "movl 0x47e4ec, %%edx\n\t"
      "pushl $0x8f\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x24, %%esp\n\t"
      "movb $0, 0x47e4d8\n\t"
      ".LFUN_0017e040_4:\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e040_assert), [exitfn] "m"(b17e040_exitfn), [c8ef70] "m"(b17e040_c8ef70)
      : "memory");
}
#else
#error "FUN_0017e040: clang naked draft required"
#endif


/* FUN_0017e130 (0x17e130) — XBE naked draft (batch 325). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0017e130(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movb 0x38(%%edx), %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "jne .LFUN_0017e130_3\n\t"
      "pushl %%ebx\n\t"
      "movb 0x38(%%esi), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_0017e130_2\n\t"
      "flds 0x34(%%edx)\n\t"
      "fcomps 0x34(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e130_1\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017e130_1:\n\t"
      "flds 0x34(%%edx)\n\t"
      "fcomps 0x34(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0017e130_5\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017e130_2:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e130_4\n\t"
      ".LFUN_0017e130_3:\n\t"
      "movswl 0x30(%%edx), %%ecx\n\t"
      "negl %%ecx\n\t"
      ".LFUN_0017e130_4:\n\t"
      "movb 0x38(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e130_5\n\t"
      "movswl 0x30(%%esi), %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      ".LFUN_0017e130_5:\n\t"
      "movl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017e130: clang naked draft required"
#endif


/* FUN_0017e190 (0x17e190) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b17e190_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e190_exitfn)(int) = system_exit;
static void __cdecl (*const b17e190_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static int (*const b17e190_rzbuf)(int, int) = rasterizer_widget_set_zbuffer_enable;
static int (*const b17e190_rspr)(int) = rasterizer_widget_draw_sprite3d;
static void * (*const b17e190_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b17e190_rend)(int) = rasterizer_widget_end;
static void (*const b17e190_c15a560)(char additive) = FUN_0015a560;
static void __cdecl (*const b17e190_c15d5b0)(int first_primitive_index, int primitive_count, int dynamic_vertex_buffer_index, short vertices_per_primitive) = rasterizer_draw_dynamic_vertices;
static void (*const b17e190_c15a290)(void) = FUN_0015a290;
static void (*const b17e190_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b17e190_rocc)(int) = rasterizer_widget_submit_occlusion_test;

__attribute__((naked, noinline))
void FUN_0017e190(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_0017e190_25\n\t"
      "movl 0x47e4f4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0017e190_25\n\t"
      "movb 0x3256dd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e190_25\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e190_1\n\t"
      "pushl $1\n\t"
      "pushl $0x140\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_1:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e190_2\n\t"
      "pushl $1\n\t"
      "pushl $0x141\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_2:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e190_3\n\t"
      "pushl $1\n\t"
      "pushl $0x142\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_3:\n\t"
      "movl 0x47e4e0, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl $0x2000, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_0017e190_4\n\t"
      "pushl $1\n\t"
      "pushl $0x143\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af668\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_4:\n\t"
      "cmpl %%esi, 0x47e4e8\n\t"
      "jle .LFUN_0017e190_5\n\t"
      "pushl $1\n\t"
      "pushl $0x144\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af620\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_5:\n\t"
      "cmpl %%esi, 0x47e4f0\n\t"
      "jle .LFUN_0017e190_6\n\t"
      "pushl $1\n\t"
      "pushl $0x145\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af5d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_6:\n\t"
      "cmpl %%esi, 0x47e4f4\n\t"
      "jle .LFUN_0017e190_7\n\t"
      "pushl $1\n\t"
      "pushl $0x146\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af588\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_7:\n\t"
      "movl 0x47e4f0, %%eax\n\t"
      "movl 0x47e4ec, %%ecx\n\t"
      "pushl $0x17e130\n\t"
      "pushl $0x3c\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9260]\n\t"
      "movl 0x47e4e0, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movw $0xd, 0x325652\n\t"
      "jle .LFUN_0017e190_13\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $9\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_0017e190_18\n\t"
      "pushl %%esi\n\t"
      "call *%[rspr]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_0017e190_11\n\t"
      "movl 0x47e4e0, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .LFUN_0017e190_10\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017e190_9\n\t"
      ".LFUN_0017e190_8:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LFUN_0017e190_9:\n\t"
      "movl 0x47e4dc, %%ecx\n\t"
      "movswl 0x30(%%edi,%%ecx,1), %%edx\n\t"
      "leal (%%edi,%%ecx,1), %%esi\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x30(%%esi), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%edx, %%ebx\n\t"
      "addl $0x3c, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_0017e190_8\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_0017e190_10:\n\t"
      "pushl %%esi\n\t"
      "call *%[rend]\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "call *%[c15a560]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "call *%[c15a290]\n\t"
      "jmp .LFUN_0017e190_12\n\t"
      ".LFUN_0017e190_11:\n\t"
      "pushl $0x2af540\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0017e190_12:\n\t"
      "pushl %%esi\n\t"
      "call *%[rocc]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e190_19\n\t"
      ".LFUN_0017e190_13:\n\t"
      "movl 0x47e4e8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0017e190_19\n\t"
      "leal (%%eax,%%eax,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $9\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_0017e190_18\n\t"
      "pushl %%esi\n\t"
      "call *%[rspr]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_0017e190_17\n\t"
      "movl 0x47e4e8, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jle .LFUN_0017e190_16\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017e190_15\n\t"
      ".LFUN_0017e190_14:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017e190_15:\n\t"
      "movl 0x47e4e4, %%edx\n\t"
      "movswl 0x30(%%edi,%%edx,1), %%ecx\n\t"
      "leal (%%edi,%%edx,1), %%esi\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x30(%%esi), %%eax\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x3c, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_0017e190_14\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_0017e190_16:\n\t"
      "pushl %%esi\n\t"
      "call *%[rend]\n\t"
      "pushl $0x10\n\t"
      "pushl $1\n\t"
      "call *%[c15a560]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "call *%[c15a290]\n\t"
      "pushl %%esi\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_19\n\t"
      ".LFUN_0017e190_17:\n\t"
      "pushl $0x2af540\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_19\n\t"
      ".LFUN_0017e190_18:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0017e190_19:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "je .LFUN_0017e190_24\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0017e190_20:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpl 0x47e4f0, %%edx\n\t"
      "jge .LFUN_0017e190_24\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "movswl 0x30(%%ebx,%%eax,1), %%ecx\n\t"
      "leal (%%ebx,%%eax,1), %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $9\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0017e190_22\n\t"
      "pushl %%edi\n\t"
      "call *%[rspr]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017e190_21\n\t"
      "movswl 0x30(%%esi), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl %%edi\n\t"
      "call *%[rend]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c15a560]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x30(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x28, %%esp\n\t"
      "call *%[c15a290]\n\t"
      "pushl %%edi\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_23\n\t"
      ".LFUN_0017e190_21:\n\t"
      "pushl $0x2af540\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_23\n\t"
      ".LFUN_0017e190_22:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0017e190_23:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "incl %%edx\n\t"
      "addl $0x3c, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_0017e190_20\n\t"
      ".LFUN_0017e190_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x325652\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017e190_25:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e190_assert), [exitfn] "m"(b17e190_exitfn), [c1d9260] "m"(b17e190_c1d9260), [rzbuf] "m"(b17e190_rzbuf), [rspr] "m"(b17e190_rspr), [c8e0b0] "m"(b17e190_c8e0b0), [rend] "m"(b17e190_rend), [c15a560] "m"(b17e190_c15a560), [c15d5b0] "m"(b17e190_c15d5b0), [c15a290] "m"(b17e190_c15a290), [c8f390] "m"(b17e190_c8f390), [rocc] "m"(b17e190_rocc)
      : "memory");
}
#else
#error "FUN_0017e190: clang naked draft required"
#endif


/* FUN_0017e5b0 (0x17e5b0) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b17e5b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e5b0_exitfn)(int) = system_exit;
static void (*const b17e5b0_c17df10)(void) = FUN_0017df10;
static unsigned int (*const b17e5b0_d1c90)(float *) = FUN_000d1c90;

__attribute__((naked, noinline))
void FUN_0017e5b0(float *vert_ws __attribute__((unused)), float *vert_offset __attribute__((unused)), int transform_a __attribute__((unused)), int transform_b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e5b0_13\n\t"
      "movb 0x3256dd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e5b0_13\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0017e5b0_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0017e5b0_1\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0017e5b0_2\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_3\n\t"
      "jmp .LFUN_0017e5b0_2\n\t"
      ".LFUN_0017e5b0_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".LFUN_0017e5b0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xab\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af6b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_3:\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0xac\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_4:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0xad\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_5:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_6\n\t"
      "pushl $1\n\t"
      "pushl $0xae\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_6:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017e5b0_7\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e5b0_12\n\t"
      ".LFUN_0017e5b0_7:\n\t"
      "cmpl $0x3f800000, (%%esi)\n\t"
      "jne .LFUN_0017e5b0_8\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "cmpl $0x3f800000, (%%ecx)\n\t"
      "jne .LFUN_0017e5b0_8\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0x47e4e8, %%eax\n\t"
      "jmp .LFUN_0017e5b0_9\n\t"
      ".LFUN_0017e5b0_8:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x47e4f0, %%eax\n\t"
      ".LFUN_0017e5b0_9:\n\t"
      "pushl %%eax\n\t"
      "call *%[c17df10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0017e5b0_12\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x47e4e4, %%ecx\n\t"
      "jne .LFUN_0017e5b0_10\n\t"
      "movl 0x47e4ec, %%ecx\n\t"
      ".LFUN_0017e5b0_10:\n\t"
      "flds 0x5a5bc8\n\t"
      "addl %%ecx, %%eax\n\t"
      "fsubs (%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "movw $2, 0x30(%%esi)\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%ebx), %%edx\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[d1c90]\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e5b0_11\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_0017e5b0_11:\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movb %%dl, 0x38(%%esi)\n\t"
      ".LFUN_0017e5b0_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017e5b0_13:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e5b0_assert), [exitfn] "m"(b17e5b0_exitfn), [c17df10] "m"(b17e5b0_c17df10), [d1c90] "m"(b17e5b0_d1c90)
      : "memory");
}
#else
#error "FUN_0017e5b0: clang naked draft required"
#endif


/* FUN_0017e800 (0x17e800) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b17e800_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e800_exitfn)(int) = system_exit;
static void (*const b17e800_c17df10)(void) = FUN_0017df10;
static unsigned int (*const b17e800_d1c90)(float *) = FUN_000d1c90;

__attribute__((naked, noinline))
void FUN_0017e800(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e800_16\n\t"
      "movb 0x3256dd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e800_16\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0017e800_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017e800_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0017e800_1\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0017e800_2\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017e800_2\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_3\n\t"
      "jmp .LFUN_0017e800_2\n\t"
      ".LFUN_0017e800_1:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      ".LFUN_0017e800_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xe5\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af6d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_3:\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_4\n\t"
      "pushl $1\n\t"
      "pushl $0xe6\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_4:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_5\n\t"
      "pushl $1\n\t"
      "pushl $0xe7\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_5:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_6\n\t"
      "pushl $1\n\t"
      "pushl $0xe8\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_6:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017e800_7\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017e800_7\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_15\n\t"
      ".LFUN_0017e800_7:\n\t"
      "cmpl $0x3f800000, (%%esi)\n\t"
      "jne .LFUN_0017e800_8\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "cmpl $0x3f800000, (%%edx)\n\t"
      "jne .LFUN_0017e800_8\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpl $0x3f800000, (%%eax)\n\t"
      "jne .LFUN_0017e800_8\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0x47e4e0, %%eax\n\t"
      "jmp .LFUN_0017e800_9\n\t"
      ".LFUN_0017e800_8:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x47e4f0, %%eax\n\t"
      ".LFUN_0017e800_9:\n\t"
      "pushl %%eax\n\t"
      "call *%[c17df10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0017e800_15\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x47e4dc, %%ecx\n\t"
      "jne .LFUN_0017e800_10\n\t"
      "movl 0x47e4ec, %%ecx\n\t"
      ".LFUN_0017e800_10:\n\t"
      "flds 0x5a5bc8\n\t"
      "addl %%ecx, %%eax\n\t"
      "fsubs (%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fsubs (%%eax)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "movw $3, 0x30(%%esi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl (%%ebx), %%edx\n\t"
      "leal 0x20(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "call *%[d1c90]\n\t"
      "movl %%eax, 0x2c(%%esi)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_11\n\t"
      "flds -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017e800_12\n\t"
      ".LFUN_0017e800_11:\n\t"
      "fld %%st(0)\n\t"
      ".LFUN_0017e800_12:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_13\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_14\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movb %%al, 0x38(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017e800_13:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".LFUN_0017e800_14:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movb %%al, 0x38(%%esi)\n\t"
      ".LFUN_0017e800_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017e800_16:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e800_assert), [exitfn] "m"(b17e800_exitfn), [c17df10] "m"(b17e800_c17df10), [d1c90] "m"(b17e800_d1c90)
      : "memory");
}
#else
#error "FUN_0017e800: clang naked draft required"
#endif


/* FUN_0017eb10 (0x17eb10) — XBE naked draft (batch 378). */
#if defined(__clang__)
static void (*const b17eb10_c17e5b0)(float *vert_ws, float *vert_offset, int transform_a, int transform_b) = (void *)FUN_0017e5b0;

__attribute__((naked, noinline))
void FUN_0017eb10(float *vert_a __attribute__((unused)), float *vert_b __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17e5b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c17e5b0] "m"(b17eb10_c17e5b0)
      : "memory");
}
#else
#error "FUN_0017eb10: clang naked draft required"
#endif


/* FUN_0017eb30 (0x17eb30) — XBE naked draft (batch 379). */
#if defined(__clang__)
static void (*const b17eb30_c17e800)(void) = (void *)FUN_0017e800;

__attribute__((naked, noinline))
void FUN_0017eb30(float *point0 __attribute__((unused)), float *point1 __attribute__((unused)), float *point2 __attribute__((unused)), void *color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17e800]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c17e800] "m"(b17eb30_c17e800)
      : "memory");
}
#else
#error "FUN_0017eb30: clang naked draft required"
#endif


/* FUN_0017eb50 (0x17eb50) — XBE naked draft (batch 385). */
#if defined(__clang__)
static void * (*const b17eb50_c8ee60)(uint32_t size, bool zero, const char *file, int line) = (void *)debug_malloc;
static void (*const b17eb50_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_0017eb50(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl $0x29\n\t"
      "pushl $0x2af728\n\t"
      "pushl $0\n\t"
      "pushl $0x24000\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x47ec40\n\t"
      "jne .LFUN_0017eb50_1\n\t"
      "pushl $0x2af710\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_0017eb50_1:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b17eb50_c8ee60), [c8f390] "m"(b17eb50_c8f390)
      : "memory");
}
#else
#error "FUN_0017eb50: clang naked draft required"
#endif


/* FUN_0017eb90 (0x17eb90) — readable C lift. */
void FUN_0017eb90(void)
{
  csmemset((void *)0x5a5400, 0, 0x170);
}

/* FUN_0017ebb0 (0x17ebb0) — XBE naked draft (batch 300). */
#if defined(__clang__)
static unsigned int (*const b17ebb0_c8e370)(void) = system_milliseconds;

__attribute__((naked, noinline))
void FUN_0017ebb0(void *param __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "cmpw $0, 0x3256ba\n\t"
      "pushl %%ebx\n\t"
      "je .LFUN_0017ebb0_15\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0017ebb0_15\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e370]\n\t"
      "movw 0x47ed50, %%si\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_0017ebb0_13\n\t"
      "movl 0x47ec60, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl 0x47ed50, %%edx\n\t"
      "decl %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jle .LFUN_0017ebb0_4\n\t"
      "movswl %%dx, %%esi\n\t"
      "leal 0x47ec60(,%%esi,4), %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017ebb0_1:\n\t"
      "cmpw $1, %%dx\n\t"
      "jle .LFUN_0017ebb0_3\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "subl (%%esi), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "ja .LFUN_0017ebb0_2\n\t"
      "movl %%ecx, %%edi\n\t"
      ".LFUN_0017ebb0_2:\n\t"
      "cmpl -0x4(%%ebp), %%ecx\n\t"
      "jbe .LFUN_0017ebb0_3\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_0017ebb0_3:\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "decl %%edx\n\t"
      "subl $4, %%esi\n\t"
      "testw %%dx, %%dx\n\t"
      "jg .LFUN_0017ebb0_1\n\t"
      "movw 0x47ed50, %%si\n\t"
      ".LFUN_0017ebb0_4:\n\t"
      "movl 0x47ec60, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "ja .LFUN_0017ebb0_5\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_5:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_6\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_6:\n\t"
      "fdivrs 0x254cb8\n\t"
      "movswl %%si, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movw %%si, 0x4(%%ebx)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fstps (%%ebx)\n\t"
      "subl 0x47ec5c(,%%edx,4), %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "ja .LFUN_0017ebb0_7\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_7:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fmuls 0x254cb8\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_8\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_8:\n\t"
      "cmpl $1, %%edi\n\t"
      ".byte 0xde, 0xf9\n\t"
      "movl %%edi, %%ecx\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "ja .LFUN_0017ebb0_9\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_9:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_10\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_10:\n\t"
      "fdivrs 0x254cb8\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "popl %%edi\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "ja .LFUN_0017ebb0_11\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_11:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_12\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_12:\n\t"
      "fdivrs 0x254cb8\n\t"
      "fstps 0xc(%%ebx)\n\t"
      ".LFUN_0017ebb0_13:\n\t"
      "movl %%eax, 0x47ec60\n\t"
      "movswl %%si, %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $0x3c, %%eax\n\t"
      "popl %%esi\n\t"
      "jle .LFUN_0017ebb0_14\n\t"
      "movw $0x3c, 0x47ed50\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017ebb0_14:\n\t"
      "movw %%ax, 0x47ed50\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017ebb0_15:\n\t"
      "movw $0, 0x47ed50\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b17ebb0_c8e370)
      : "memory");
}
#else
#error "FUN_0017ebb0: clang naked draft required"
#endif


/* FUN_0017ed30 (0x17ed30) — XBE naked draft (batch 321). */
#if defined(__clang__)
static unsigned int (*const b17ed30_c8e370)(void) = system_milliseconds;

__attribute__((naked, noinline))
void FUN_0017ed30(void)
{
  __asm__ volatile(
      "movb $1, 0x3256b8\n\t"
      "call *%[c8e370]\n\t"
      "movl 0x32566c, %%ecx\n\t"
      "movl %%eax, 0x47ec48\n\t"
      "movl 0x325668, %%eax\n\t"
      "movl $0, 0x47ec4c\n\t"
      "movl %%eax, 0x47ec50\n\t"
      "movl %%ecx, 0x47ec54\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b17ed30_c8e370)
      : "memory");
}
#else
#error "FUN_0017ed30: clang naked draft required"
#endif


/* FUN_0017ed70 (0x17ed70) — readable C lift. */
char FUN_0017ed70(unsigned short a, unsigned short b)
{
  return a > b;
}

/* FUN_0017ed90 (0x17ed90) — readable C lift. */
int FUN_0017ed90(short *a, short *b)
{
  if (!a) {
    return 0;
  }
  if (!b) {
    return 0;
  }
  if (a[0] == 1) {
    return *(int *)(a + 2) + 2;
  }
  if (a[0] == 0) {
    return *(int *)(b + 2);
  }
  return 0;
}

/* rasterizer_frame_statistics_count_static_vertices (0x17edd0) — XBE naked draft (batch 330). */
#if defined(__clang__)
static void * (*const b17edd0_c17c980)(int handle) = rasterizer_widget_begin;
static void (*const b17edd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17edd0_exitfn)(int) = system_exit;
static void * (*const b17edd0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b17edd0_c91da0)(void) = FUN_00091da0;
static void (*const b17edd0_c17c990)(int handle) = rasterizer_widget_set_texture;

__attribute__((naked, noinline))
void rasterizer_frame_statistics_count_static_vertices(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jl .Lrasterizer_frame_statistics_count_static_vertices_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c17c980]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .Lrasterizer_frame_statistics_count_static_vertices_8\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "cmpl $0x6000, %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal (%%esi,%%esi,2), %%edi\n\t"
      "movl $0xffff, %%ebx\n\t"
      "jl .Lrasterizer_frame_statistics_count_static_vertices_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd9\n\t"
      "pushl $0x2af728\n\t"
      "pushl $0x2af788\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_1:\n\t"
      "movl 0x47ec40, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrasterizer_frame_statistics_count_static_vertices_2\n\t"
      "pushl $1\n\t"
      "pushl $0xda\n\t"
      "pushl $0x2af728\n\t"
      "pushl $0x2af760\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_2:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "shll $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%eax\n\t"
      "movl 0x47ec40, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x47ec40, %%edx\n\t"
      "pushl $0x17ed70\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c91da0]\n\t"
      "addl $0x18, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .Lrasterizer_frame_statistics_count_static_vertices_5\n\t"
      "movl 0x47ec40, %%edx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edx,%%ecx,2), %%ax\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .Lrasterizer_frame_statistics_count_static_vertices_4\n\t"
      "movl %%eax, %%ebx\n\t"
      "incl -0x4(%%ebp)\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_4:\n\t"
      "incl %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jl .Lrasterizer_frame_statistics_count_static_vertices_3\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17c990]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_6:\n\t"
      "negl %%eax\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lrasterizer_frame_statistics_count_static_vertices_7\n\t"
      "cmpw $4, %%ax\n\t"
      "je .Lrasterizer_frame_statistics_count_static_vertices_7\n\t"
      "movswl %%ax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_7:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "subl $2, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_frame_statistics_count_static_vertices_8:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c17c980] "m"(b17edd0_c17c980), [assert] "m"(b17edd0_assert), [exitfn] "m"(b17edd0_exitfn), [c8e0b0] "m"(b17edd0_c8e0b0), [c91da0] "m"(b17edd0_c91da0), [c17c990] "m"(b17edd0_c17c990)
      : "memory");
}
#else
#error "rasterizer_frame_statistics_count_static_vertices: clang naked draft required"
#endif


/* FUN_0017ef00 (0x17ef00) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b17ef00_chkstk)(void) = FUN_001d90e0;
static void (*const b17ef00_c108a70)(int16_t *rect, int16_t dx, int16_t dy) = rect2d_offset;
static void (*const b17ef00_cdeda0)(int font_index, int style, int justify, int flags, int color_tag_index, short color_index) = interface_draw_text;
static int (*const b17ef00_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b17ef00_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static void (*const b17ef00_c19b640)(const void *color) = draw_string_set_color;
static void (*const b17ef00_c183e60)(void *screen_pos, short *bounds, const void *color, int flags, const char *text) = rasterizer_text_draw;
static unsigned int (*const b17ef00_c8e370)(void) = system_milliseconds;
static int16_t (*const b17ef00_c100b00)(void) = main_get_window_count;
static __int16 (*const b17ef00_cba4b0)(void) = local_player_count;
static void (*const b17ef00_c16fbd0)(void) = FUN_0016fbd0;
static void (*const b17ef00_c16fcf0)(void) = FUN_0016fcf0;
static void (*const b17ef00_c16fb80)(void) = rasterizer_initialize;
static void __stdcall (*const b17ef00_c1d0da1)(void *status) = (void *)xbox_query_global_memory_status;
static void * (*const b17ef00_c1d9e59)(const char *filename, const char *mode) = crt_fopen;
static void (*const b17ef00_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static int (*const b17ef00_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static int (*const b17ef00_c8df60)(const char *s1) = csstrlen;
static int (*const b17ef00_c1d9bd2)(void *stream) = crt_fflush;
static int (*const b17ef00_c1d9dac)(void *stream) = crt_fclose;

__attribute__((naked, noinline))
void FUN_0017ef00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x3158, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x3256ba\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0017ef00_12\n\t"
      "movl 0x5a549c, %%ecx\n\t"
      "movl 0x5a54ac, %%edx\n\t"
      "movl 0x5a5490, %%ebx\n\t"
      "movl 0x5a5484, %%edi\n\t"
      "leal (%%edx,%%ecx,1), %%esi\n\t"
      "movl 0x5a5478, %%edx\n\t"
      "movl 0x5a546c, %%ecx\n\t"
      "addl %%ebx, %%esi\n\t"
      "movl 0x5a5440, %%ebx\n\t"
      "addl %%edi, %%esi\n\t"
      "movl 0x5a5434, %%edi\n\t"
      "addl %%edx, %%esi\n\t"
      "movl 0x5a5424, %%edx\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "movw %%ax, -0x6(%%ebp)\n\t"
      "movw 0x32565e, %%ax\n\t"
      "addl %%ecx, %%esi\n\t"
      "movl 0x5a54a0, %%ecx\n\t"
      "movw %%ax, -0x14(%%ebp)\n\t"
      "addl 0x5a5460, %%esi\n\t"
      "movl 0x5a54b0, %%eax\n\t"
      "addl %%ebx, %%esi\n\t"
      "movl 0x5a547c, %%ebx\n\t"
      "addl %%edi, %%esi\n\t"
      "leal (%%eax,%%ecx,1), %%edi\n\t"
      "movl 0x5a5494, %%ecx\n\t"
      "movl 0x5a5488, %%eax\n\t"
      "addl %%ecx, %%edi\n\t"
      "movl 0x5a5464, %%ecx\n\t"
      "addl %%eax, %%edi\n\t"
      "movl 0x5a5444, %%eax\n\t"
      "addl %%ebx, %%edi\n\t"
      "movl 0x5a5438, %%ebx\n\t"
      "addl %%edx, %%esi\n\t"
      "addl 0x5a5470, %%edi\n\t"
      "movl 0x5a5428, %%edx\n\t"
      "addl %%ecx, %%edi\n\t"
      "movl 0x5a5498, %%ecx\n\t"
      "addl %%eax, %%edi\n\t"
      "movl 0x5a54b4, %%eax\n\t"
      "addl %%ebx, %%edi\n\t"
      "addl %%edx, %%edi\n\t"
      "movl 0x5a54a8, %%edx\n\t"
      "leal (%%eax,%%edx,1), %%ebx\n\t"
      "movl 0x5a548c, %%eax\n\t"
      "movl 0x5a5480, %%edx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "movl 0x5a5474, %%ecx\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl 0x5a5468, %%eax\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl 0x5a5448, %%edx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "movl 0x5a543c, %%ecx\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl 0x5a542c, %%eax\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl 0x5a54d8, %%edx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "movl 0x5a54e4, %%ecx\n\t"
      "movw $0x64, -0x20(%%ebp)\n\t"
      "movw $0xc8, -0x1e(%%ebp)\n\t"
      "movw $0x12c, -0x1c(%%ebp)\n\t"
      "movw $0x190, -0x1a(%%ebp)\n\t"
      "movw $0x1f4, -0x18(%%ebp)\n\t"
      "movw $0x258, -0x16(%%ebp)\n\t"
      "movl $0x3f800000, -0x38(%%ebp)\n\t"
      "movl $0x3f28f5c3, -0x34(%%ebp)\n\t"
      "movl $0x3f800000, -0x30(%%ebp)\n\t"
      "movl $0x3f28f5c3, -0x2c(%%ebp)\n\t"
      "movl $0x3f800000, -0x48(%%ebp)\n\t"
      "movl $0x3f800000, -0x44(%%ebp)\n\t"
      "movl $0x3f800000, -0x40(%%ebp)\n\t"
      "movl $0x3f800000, -0x3c(%%ebp)\n\t"
      "movl $0x3f800000, -0x78(%%ebp)\n\t"
      "movl $0x3f800000, -0x74(%%ebp)\n\t"
      "movl $0x3f800000, -0x70(%%ebp)\n\t"
      "movl $0x3f800000, -0x6c(%%ebp)\n\t"
      "addl %%eax, %%ebx\n\t"
      "leal (%%ecx,%%edx,1), %%eax\n\t"
      "movl 0x5a54dc, %%ecx\n\t"
      "movl 0x5a54e8, %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl 0x5a54e0, %%ecx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x5a54f0, %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl 0x5a54f8, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "movl 0x5a54fc, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "addl %%edi, %%eax\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl 0x5a5500, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "movl $6, %%ecx\n\t"
      ".LFUN_0017ef00_1:\n\t"
      "addw %%dx, (%%eax)\n\t"
      "addl $2, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_0017ef00_1\n\t"
      "movl 0x32565c, %%ecx\n\t"
      "movl 0x325660, %%edx\n\t"
      "pushl $0x20\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "call *%[c108a70]\n\t"
      "pushl $0\n\t"
      "pushl $5\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $1\n\t"
      "call *%[cdeda0]\n\t"
      "movswl 0x5a5404, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afde8\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "movw -0x14(%%ebp), %%ax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "addl $0x50, %%esp\n\t"
      "decl %%eax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "movb 0x3256b8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017ef00_2\n\t"
      "movl 0x47ec50, %%edx\n\t"
      "movl 0x325668, %%ecx\n\t"
      "movl 0x47ec54, %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl 0x32566c, %%edx\n\t"
      "sbbl %%eax, %%edx\n\t"
      "movl %%ecx, -0x60(%%ebp)\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "call *%[c8e370]\n\t"
      "flds 0x5a5410\n\t"
      "movl 0x47ec48, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "sbbl 0x47ec4c, %%ecx\n\t"
      "subl $0x28, %%esp\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "flds 0x5a540c\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "fildl -0x60(%%ebp)\n\t"
      "fmuls 0x254cb8\n\t"
      "fildl -0x68(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x5a5408\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x5a5400\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2afdc8\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x30, %%esp\n\t"
      "jmp .LFUN_0017ef00_3\n\t"
      ".LFUN_0017ef00_2:\n\t"
      "flds 0x5a5410\n\t"
      "subl $0x20, %%esp\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "flds 0x5a540c\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x5a5408\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x5a5400\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2afdac\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_0017ef00_3:\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl $6\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "movw 0x3256ba, %%ax\n\t"
      "addl $0x20, %%esp\n\t"
      "decl %%ecx\n\t"
      "cmpw $1, %%ax\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "jne .LFUN_0017ef00_4\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b640]\n\t"
      "movl 0x5a5420, %%edx\n\t"
      "movl 0x5a541c, %%eax\n\t"
      "movl 0x5a5418, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5414, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl $0x2afd74\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "movl 0x5a5568, %%edx\n\t"
      "movl 0x5a5564, %%eax\n\t"
      "pushl %%edx\n\t"
      "decl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "movl 0x5a5560, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afd3c\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x4c, %%esp\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "decl %%eax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "call *%[c100b00]\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cba4b0]\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl $0x2afd04\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "addl $0x24, %%esp\n\t"
      "decl %%ecx\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_0017ef00_11\n\t"
      ".LFUN_0017ef00_4:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_0017ef00_5\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afce0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "movw -0x14(%%ebp), %%ax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "decl %%eax\n\t"
      "pushl %%edx\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl $0x2afcc8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "decl %%edx\n\t"
      "pushl $0x2afcac\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "leal 0x19(%%edi), %%esi\n\t"
      "pushl %%ecx\n\t"
      "movw %%si, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "addl $0x48, %%esp\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movl 0x5a54b4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a54b0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a54a8, %%eax\n\t"
      "movl 0x5a54a4, %%ecx\n\t"
      "decl %%edx\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "movl 0x5a54ac, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a54a0, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a549c, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5498, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5494, %%edx\n\t"
      "movl 0x5a5490, %%eax\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a548c, %%ecx\n\t"
      "movl 0x5a5488, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5484, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5480, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a547c, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5478, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5474, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5470, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a546c, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5468, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5464, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5460, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5448, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5444, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5440, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a543c, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5438, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5434, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5430, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a542c, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a5428, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5424, %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afb98\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "addl $0x32, %%edi\n\t"
      "pushl %%eax\n\t"
      "movw %%di, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "addl $0x90, %%esp\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "movl 0x5a5500, %%edx\n\t"
      "movl 0x5a54fc, %%eax\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a54f4, %%edx\n\t"
      "decl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "movl 0x5a54f8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl $0x2afb70\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%ecx\n\t"
      "movw %%si, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "addl $0x48, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a54d4, %%eax\n\t"
      "decl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl $0x2afb54\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl $6\n\t"
      "pushl %%edx\n\t"
      "movw %%si, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "movl 0x5a54f0, %%ecx\n\t"
      "movl 0x5a54ec, %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a54e4, %%ecx\n\t"
      "decl %%eax\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a54e0, %%edx\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "movl 0x5a54e8, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a54dc, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a54d8, %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afb20\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x58, %%esp\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "movw %%di, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "movl 0x5a5454, %%edx\n\t"
      "movl 0x5a5450, %%eax\n\t"
      "pushl %%edx\n\t"
      "decl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "movl 0x5a544c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afb08\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "movw -0x14(%%ebp), %%si\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "movw %%si, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "movl 0x5a553c, %%edx\n\t"
      "movl 0x5a5538, %%eax\n\t"
      "addl $0x4c, %%esp\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5530, %%edx\n\t"
      "decl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "movl 0x5a5534, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl $0x2afae4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%ecx\n\t"
      "movw %%si, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "decl %%edx\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "movl 0x5a554c, %%eax\n\t"
      "movl 0x5a5548, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afabc\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x44, %%esp\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "movw %%si, -0x20(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "decl %%ecx\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_0017ef00_11\n\t"
      ".LFUN_0017ef00_5:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_0017ef00_9\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw %%dx, -0x20(%%ebp)\n\t"
      "leal 0xc8(%%eax), %%ecx\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "addl $0x12c, %%eax\n\t"
      "pushl $0x2afa90\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x1e(%%ebp)\n\t"
      "movw %%ax, -0x1c(%%ebp)\n\t"
      "movw $0x258, -0x1a(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b640]\n\t"
      "addw $-0x1e, -0x6(%%ebp)\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "decl %%edx\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "call *%[c19b640]\n\t"
      "addl $0x2c, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0017ef00_6:\n\t"
      "pushl %%esi\n\t"
      "call *%[c16fbd0]\n\t"
      "fsts -0x24(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%esi\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0017ef00_7\n\t"
      "call *%[c16fcf0]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x254cb8\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c16fb80]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl $0x2afa80\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_0017ef00_8\n\t"
      ".LFUN_0017ef00_7:\n\t"
      "call *%[c16fb80]\n\t"
      "pushl %%eax\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl $0x2afa70\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0017ef00_8:\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "decl %%eax\n\t"
      "incl %%esi\n\t"
      "cmpw $0x1d, %%si\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "jl .LFUN_0017ef00_6\n\t"
      "pushl $0x1d\n\t"
      "call *%[c16fcf0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1d\n\t"
      "call *%[c16fbd0]\n\t"
      "fmuls 0x254cb8\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2afa5c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x2ee6e0, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b640]\n\t"
      "addw $4, -0x10(%%ebp)\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "addl $0x2c, %%esp\n\t"
      "decl %%eax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "jmp .LFUN_0017ef00_11\n\t"
      ".LFUN_0017ef00_9:\n\t"
      "cmpw $4, %%ax\n\t"
      "jne .LFUN_0017ef00_11\n\t"
      "movl $0x10000, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%eax, -0x104(%%ebp)\n\t"
      "movl %%eax, -0xbc(%%ebp)\n\t"
      "movl %%eax, -0xa4(%%ebp)\n\t"
      "movl $0x14000, %%eax\n\t"
      "movl $0x4b000, %%ecx\n\t"
      "movl $0x30000, %%edx\n\t"
      "movl %%eax, -0x98(%%ebp)\n\t"
      "movl %%eax, -0x94(%%ebp)\n\t"
      "movl %%ecx, -0x118(%%ebp)\n\t"
      "movl %%ecx, -0xc4(%%ebp)\n\t"
      "movl $0x8000, %%ecx\n\t"
      "movl $0x1b0000, %%eax\n\t"
      "movl %%edx, -0x128(%%ebp)\n\t"
      "movl %%edx, -0xec(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      "movl %%eax, -0x88(%%ebp)\n\t"
      "movl %%ecx, -0xb0(%%ebp)\n\t"
      "movl %%ecx, -0xac(%%ebp)\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "addl $0x12c, %%edx\n\t"
      "pushl $0x2afa38\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "movl $0x2afa2c, -0x138(%%ebp)\n\t"
      "movl $0x18000, -0x134(%%ebp)\n\t"
      "movl %%ebx, -0x130(%%ebp)\n\t"
      "movl $0x2afa10, -0x12c(%%ebp)\n\t"
      "movl %%ebx, -0x124(%%ebp)\n\t"
      "movl $0x2af9f8, -0x120(%%ebp)\n\t"
      "movl $0x48, -0x11c(%%ebp)\n\t"
      "movl $0x2af9dc, -0x114(%%ebp)\n\t"
      "movl $0x50000, -0x110(%%ebp)\n\t"
      "movl %%ebx, -0x10c(%%ebp)\n\t"
      "movl $0x2af9c0, -0x108(%%ebp)\n\t"
      "movl %%ebx, -0x100(%%ebp)\n\t"
      "movl $0x2af99c, -0xfc(%%ebp)\n\t"
      "movl $0x20000, -0xf8(%%ebp)\n\t"
      "movl %%ebx, -0xf4(%%ebp)\n\t"
      "movl $0x2af988, -0xf0(%%ebp)\n\t"
      "movl %%ebx, -0xe8(%%ebp)\n\t"
      "movl $0x2af96c, -0xe4(%%ebp)\n\t"
      "movl $0xf000, -0xe0(%%ebp)\n\t"
      "movl %%ebx, -0xdc(%%ebp)\n\t"
      "movl $0x2af958, -0xd8(%%ebp)\n\t"
      "movl $0x400, -0xd4(%%ebp)\n\t"
      "movl %%ebx, -0xd0(%%ebp)\n\t"
      "movl $0x2af934, -0xcc(%%ebp)\n\t"
      "movl $0x96000, -0xc8(%%ebp)\n\t"
      "movl $0x2af924, -0xc0(%%ebp)\n\t"
      "movl %%ebx, -0xb8(%%ebp)\n\t"
      "movl $0x2af910, -0xb4(%%ebp)\n\t"
      "movl $0x2af900, -0xa8(%%ebp)\n\t"
      "movl %%ebx, -0xa0(%%ebp)\n\t"
      "movl $0x2af8e8, -0x9c(%%ebp)\n\t"
      "movl $0x2af8d8, -0x90(%%ebp)\n\t"
      "movl $0x2af8b4, -0x84(%%ebp)\n\t"
      "movl $0x8c00, -0x80(%%ebp)\n\t"
      "movl $0x3000, -0x7c(%%ebp)\n\t"
      "movw %%cx, -0x20(%%ebp)\n\t"
      "movw %%dx, -0x1e(%%ebp)\n\t"
      "movw $0x258, -0x1c(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "decl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "call *%[c19b640]\n\t"
      "addl $0x2c, %%esp\n\t"
      "leal -0x134(%%ebp), %%edi\n\t"
      "movl $0x10, -0x14(%%ebp)\n\t"
      ".LFUN_0017ef00_10:\n\t"
      "movl (%%edi), %%esi\n\t"
      "movl -0x4(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl $0x2af8a8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "decl %%ecx\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "addl %%esi, %%ecx\n\t"
      "subl %%eax, %%esi\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "addl $0xc, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_0017ef00_10\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl $0x2af894\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x3158(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "leal -0x158(%%ebp), %%eax\n\t"
      "decl %%edx\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "call *%[c1d0da1]\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b640]\n\t"
      "movl -0x150(%%ebp), %%edx\n\t"
      "shrl $0xa, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "pushl $0x2af87c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x14c(%%ebp), %%edx\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "shrl $0xa, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3158(%%ebp), %%eax\n\t"
      "decl %%ecx\n\t"
      "pushl $0x2af860\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x3158(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-4\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "movl -0x6(%%ebp), %%ecx\n\t"
      "addl $0x44, %%esp\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "decl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "call *%[c19b640]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0017ef00_11:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b640]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0017ef00_12:\n\t"
      "movb 0x325704, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017ef00_22\n\t"
      "movl 0x47ec58, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017ef00_14\n\t"
      "movl 0x325744, %%ecx\n\t"
      "pushl $0x265938\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9e59]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x47ec58\n\t"
      "jne .LFUN_0017ef00_13\n\t"
      "movl 0x325744, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2af828\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x47ec58, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $0, 0x325704\n\t"
      ".LFUN_0017ef00_13:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, 0x47ed58\n\t"
      "movl $0, 0x47ed5c\n\t"
      "je .LFUN_0017ef00_23\n\t"
      ".LFUN_0017ef00_14:\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0017ef00_15:\n\t"
      "pushl %%esi\n\t"
      "call *%[c16fbd0]\n\t"
      "fmuls 0x254cb8\n\t"
      "movswl 0x47ed54, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "addl $0x10, %%edi\n\t"
      "fstps 0x47e500(,%%eax,4)\n\t"
      "cmpw $0x1d, %%si\n\t"
      "jl .LFUN_0017ef00_15\n\t"
      "pushl $0x1d\n\t"
      "call *%[c16fbd0]\n\t"
      "fmuls 0x254cb8\n\t"
      "pushl $0x1d\n\t"
      "fadds 0x47ed58\n\t"
      "fstps 0x47ed58\n\t"
      "call *%[c16fcf0]\n\t"
      "movl 0x47ed5c, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "movw 0x47ed54, %%ax\n\t"
      "addl $8, %%esp\n\t"
      "incw %%ax\n\t"
      "cmpw $0x10, %%ax\n\t"
      "movl %%esi, 0x47ed5c\n\t"
      "movw %%ax, 0x47ed54\n\t"
      "jne .LFUN_0017ef00_23\n\t"
      "movl 0x47ec58, %%ecx\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl $0x47e500, %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0017ef00_16:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c16fb80]\n\t"
      "movl 0x47ec58, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x257984\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c16fb80]\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0x20, %%ax\n\t"
      "jge .LFUN_0017ef00_18\n\t"
      "movl $0x20, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movzwl %%cx, %%edi\n\t"
      "jmp .LFUN_0017ef00_17\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017ef00_17:\n\t"
      "movl 0x47ec58, %%edx\n\t"
      "pushl $0x2af824\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0017ef00_17\n\t"
      ".LFUN_0017ef00_18:\n\t"
      "movl $0x10, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017ef00_19:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0017ef00_20\n\t"
      "flds (%%esi)\n\t"
      "movl 0x47ec58, %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2af81c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0017ef00_21\n\t"
      ".LFUN_0017ef00_20:\n\t"
      "movl 0x47ec58, %%ecx\n\t"
      "pushl $0x2af814\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0017ef00_21:\n\t"
      "addl $4, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0017ef00_19\n\t"
      "movl 0x47ec58, %%edx\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpw $0x1d, %%bx\n\t"
      "jl .LFUN_0017ef00_16\n\t"
      "flds 0x47ed58\n\t"
      "movl 0x47ec58, %%eax\n\t"
      "fmuls 0x255d90\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2af7ec\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x47ed5c, %%eax\n\t"
      "movl 0x47ec58, %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "cdq\n\t"
      "andl $0xf, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2af7c8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x47ec58, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9bd2]\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x47ed54\n\t"
      "movl %%eax, 0x47ed58\n\t"
      "movl %%eax, 0x47ed5c\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017ef00_22:\n\t"
      "movl 0x47ec58, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017ef00_23\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9dac]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0, 0x47ec58\n\t"
      ".LFUN_0017ef00_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b17ef00_chkstk), [c108a70] "m"(b17ef00_c108a70), [cdeda0] "m"(b17ef00_cdeda0), [c1d90f0] "m"(b17ef00_c1d90f0), [c19b560] "m"(b17ef00_c19b560), [c19b640] "m"(b17ef00_c19b640), [c183e60] "m"(b17ef00_c183e60), [c8e370] "m"(b17ef00_c8e370), [c100b00] "m"(b17ef00_c100b00), [cba4b0] "m"(b17ef00_cba4b0), [c16fbd0] "m"(b17ef00_c16fbd0), [c16fcf0] "m"(b17ef00_c16fcf0), [c16fb80] "m"(b17ef00_c16fb80), [c1d0da1] "m"(b17ef00_c1d0da1), [c1d9e59] "m"(b17ef00_c1d9e59), [c8f390] "m"(b17ef00_c8f390), [c1d98ad] "m"(b17ef00_c1d98ad), [c8df60] "m"(b17ef00_c8df60), [c1d9bd2] "m"(b17ef00_c1d9bd2), [c1d9dac] "m"(b17ef00_c1d9dac)
      : "memory");
}
#else
#error "FUN_0017ef00: clang naked draft required"
#endif

/* --- rasterizer_sprites.obj orphan shells (2026-07-26) --- */

/* FUN_0017d030 (0x17d030) — XBE naked draft (batch 395). */
#if defined(__clang__)


__attribute__((naked, noinline))
int FUN_0017d030(float *position __attribute__((unused)), int vis_index __attribute__((unused)), int index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xd7, 0xe9, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0017d030: clang naked draft required"
#endif


