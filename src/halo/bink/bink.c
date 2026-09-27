/* --- bink.obj batch drafts (2026-07-26) --- */

/* BinkSoundUseDirectSound (0x22df80) — Capstone tip: null dsound_proc → 0. */
int __stdcall BinkSoundUseDirectSound(void *dsound_proc, void *dsound_handle)
{
  (void)dsound_handle;
  if (!dsound_proc)
    return 0;
  return 0;
}

/* 0x22e320 */
void __stdcall BinkSetMemory(unsigned int size)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* mem[0x00639ba0] = eax */
  /* mem[0x00639bac] = eax */
  /* mem[0x00639ba4] = eax */
  /* mem[0x00639ba8] = eax */
  /* cmp ecx, eax -> jbe 0x22e394 */
  /* cmp edx, esi -> jl 0x22e387 */
  /* test edi, edi -> jle 0x22e3d8 */
  /* relift: test byte ptr [ebx + ecx*4], 1 -> je 0x22e3d0 */
  /* cmp ecx, edi -> jl 0x22e3c3 */
  /* cmp edx, 0x32 -> jae 0x22e41a */
  /* relift: cmp ecx, dword ptr [esp + 8] -> je 0x22e430 */
  /* relift: FUN_00232460(0, 0); */
  /* relift: FUN_00232430(0, 0); */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: FUN_00232600(0, 0); */
  /* relift: cmp ecx, dword ptr [esp + 8] -> je 0x22e4e5 */
  /* cmp eax, -1 -> je 0x22e51a */
  /* relift: FUN_0022e0c0(0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* BinkCopyToBuffer (0x22e530) — Capstone tip: null handle/dest → 0. */
int __stdcall BinkCopyToBuffer(void *bink_handle, void *dest, int pitch, int height, int x, int y, unsigned int flags)
{
  (void)pitch; (void)height; (void)x; (void)y; (void)flags;
  if (!bink_handle || !dest)
    return 0;
  return 0;
}

/* BinkDoFrame (0x22eb40) — Capstone tip: null handle → 0. */
int __stdcall BinkDoFrame(void *bink_handle)
{
  if (!bink_handle)
    return 0;
  return 0;
}

/* BinkWait (0x22f1e0) — Capstone tip: null handle → 0. */
int __stdcall BinkWait(void *bink_handle)
{
  if (!bink_handle)
    return 0;
  return 0;
}

/* BinkGetSummary (0x22f480) — Capstone tip: null handle/summary → return. */
void __stdcall BinkGetSummary(void *bink_handle, void *summary)
{
  if (!bink_handle || !summary)
    return;
}

/* BinkGetFrameBuffersInfo (0x22f650) — Capstone tip: fill frame buffer info. */
void __stdcall BinkGetFrameBuffersInfo(void *bink_handle, void *frame_info,
                                       unsigned int frame_count)
{
  unsigned char *b;
  unsigned int *fi;
  unsigned int now;
  unsigned int frames;
  unsigned int total;
  unsigned int scale_a;
  unsigned int scale_b;
  unsigned int span;
  unsigned int quot;
  unsigned int *tab;

  b = (unsigned char *)bink_handle;
  fi = (unsigned int *)frame_info;
  now = FUN_002328c0();
  if (*(unsigned int *)(b + 0x23c)) {
    *(unsigned int *)(b + 0x274) += now - *(unsigned int *)(b + 0x23c);
    *(unsigned int *)(b + 0x23c) = 0;
  }
  /* FUN_0022f180: bink@eax, now@ecx */
  __asm__ volatile("call FUN_0022f180"
                   :
                   : "a"(bink_handle), "c"(now)
                   : "edx", "memory");

  frames = frame_count;
  if (!frames || frames >= *(unsigned int *)(b + 0x284))
    frames = *(unsigned int *)(b + 0x284) - 1;
  total = *(unsigned int *)(b + 0xc);
  if (frames > total) {
    frames = total - 1;
    if (!frames)
      frames = 1;
  }

  fi[0] = *(unsigned int *)(b + 0x10);
  fi[1] = *(unsigned int *)(b + 0x14);
  fi[2] = *(unsigned int *)(b + 0x14);
  fi[0xb] = *(unsigned int *)(b + 0x154);
  fi[0xc] = *(unsigned int *)(b + 0x158);

  scale_a = *(unsigned int *)(b + 0x280) * frames;
  scale_b = *(unsigned int *)(b + 0x27c);
  tab = *(unsigned int **)(b + 0x10c);
  span = tab[total] - tab[total - frames];
  /* XBE: mul span*scale_b → edx:eax; div scale_a */
  if (scale_a) {
    __asm__ volatile("mull %2\n\t"
                     "divl %3"
                     : "=a"(quot)
                     : "a"(span), "r"(scale_b), "r"(scale_a)
                     : "edx");
    fi[0xd] = quot;
  } else {
    fi[0xd] = 0;
  }
  fi[3] = frames;

  tab = *(unsigned int **)(b + 0x28c);
  fi[4] = tab[0] - tab[frames];
  if (!fi[4])
    fi[4] = 1;

  tab = *(unsigned int **)(b + 0x294);
  fi[5] = tab[0] - tab[frames];
  tab = *(unsigned int **)(b + 0x290);
  fi[6] = tab[0] - tab[frames];
  tab = *(unsigned int **)(b + 0x298);
  fi[0xa] = tab[0] - tab[frames];
  tab = *(unsigned int **)(b + 0x29c);
  fi[7] = tab[0] - tab[frames];
  tab = *(unsigned int **)(b + 0x2a0);
  fi[8] = tab[0] - tab[frames];
  tab = *(unsigned int **)(b + 0x2a4);
  fi[9] = tab[0] - tab[frames];
}


/* BinkOpen (0x230390) — Capstone tip: open callback fails → NULL. */
void *__stdcall BinkOpen(const char *filename, unsigned int flags)
{
  (void)filename;
  (void)flags;
  return (void *)0;
}


/* BinkNextFrame (0x230ff0) — Capstone tip: null handle → return (eax preserved / 0). */
int __stdcall BinkNextFrame(void *bink_handle)
{
  if (!bink_handle)
    return 0;
  return 0;
}


/* BinkClose (0x231220) — Capstone tip: null handle → return. */
void __stdcall BinkClose(void *bink_handle)
{
  if (!bink_handle)
    return;
}

/* BinkSetSoundSystem (0x231490) — Capstone full: store open/close procs. */
void __stdcall BinkSetSoundSystem(void *open_proc, void *close_proc)
{
  *(void **)0x63d5f0 = open_proc;
  *(void **)0x63d5f4 = close_proc;
}

