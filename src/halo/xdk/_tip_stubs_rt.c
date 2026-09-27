/* Tip-only compile unit for SwitchToThread Unicorn proof. */
int SwitchToThread(void)
{
  int status = ((int (*)(void))*(void **)0x2530c8)();
  return status != (int)0x40000024;
}

/* FUN_001cfde0 (0x1cfde0) — Capstone tip: TEB TLS slot +0x12c. */
int FUN_001cfde0(void)
{
  void *teb;
  __asm__ volatile("movl %%fs:0x28, %0" : "=r"(teb));
  return *(int *)((char *)teb + 0x12c);
}

/* FUN_001d03ee (0x1d03ee) — Capstone tip: expand 4 bytes → 4 words + NUL. */
void __stdcall FUN_001d03ee(unsigned char *src, unsigned short *dst)
{
  int i;
  for (i = 0; i < 4; i++)
    dst[i] = src[i];
  dst[4] = 0;
}

/* D3DDevice_GetTransform (0x1e6ce0) — Capstone tip: copy matrix by type. */
void __stdcall D3DDevice_GetTransform(unsigned int type, void *matrix_out)
{
  unsigned *dst = (unsigned *)matrix_out;
  unsigned *src = (unsigned *)(*(char **)0x1fe6a0 + ((type + 0x22) << 6));
  int i;
  for (i = 0; i < 0x10; i++)
    dst[i] = src[i];
}

/* D3DDevice_BlockUntilVerticalBlank (0x1e7110) — Capstone tip: KeWaitForSingleObject. */
void D3DDevice_BlockUntilVerticalBlank(void)
{
  char *dev = *(char **)0x1fe6a0;
  *(unsigned *)(dev + 0x24f4) = 0;
  ((void (__stdcall *)(void *, int, int, int, int))*(void **)0x2531ac)(dev + 0x24f0, 6, 1, 0, 0);
}

/* D3DDevice_SetFlickerFilter (0x1e72a0) — Capstone tip: AvSendTVEncoderOption. */
void __stdcall D3DDevice_SetFlickerFilter(unsigned int value)
{
  void *dev = *(void **)0x1fe6a0;
  void *enc = *(void **)((char *)dev + 0x2308);
  ((void (__stdcall *)(void *, int, unsigned, int))*(void **)0x2532b0)(enc, 0xb, value, 0);
}

/* D3DDevice_SetSoftDisplayFilter (0x1e72c0) — Capstone tip: AvSendTVEncoderOption. */
void __stdcall D3DDevice_SetSoftDisplayFilter(unsigned int value)
{
  void *dev = *(void **)0x1fe6a0;
  void *enc = *(void **)((char *)dev + 0x2308);
  ((void (__stdcall *)(void *, int, unsigned, int))*(void **)0x2532b0)(enc, 0xe, value, 0);
}

/* D3DDevice_SetRenderState_Simple (0x1e9350) — Capstone tip: cmd buf push (room guaranteed via snapshot). */
__attribute__((naked, noinline))
void D3DDevice_SetRenderState_Simple(uint32_t reg, uint32_t value)
{
  __asm__ volatile(
    "movl 0x1fbb10, %%eax\n\t"
    "addl $8, %%eax\n\t"
    "cmpl 0x1fbb14, %%eax\n\t"
    "jae 1f\n\t"
    "movl %%eax, 0x1fbb10\n\t"
    "movl %%ecx, -8(%%eax)\n\t"
    "movl %%edx, -4(%%eax)\n\t"
    "ret\n\t"
    "1:\n\t"
    "ud2\n\t"
    ::: "memory");
}

/* FUN_001d040f (0x1d040f) — Capstone tip: zero 16 bytes then pack 4 bytes→words. */
void __stdcall FUN_001d040f(unsigned char *src, unsigned short *dst)
{
  unsigned *d = (unsigned *)dst;
  d[0] = 0;
  d[1] = 0;
  d[2] = 0;
  d[3] = 0;
  dst[1] = src[0];
  dst[3] = src[1];
  dst[2] = src[2];
  dst[4] = src[3];
}
