/*
 * rasterizer_preinitialize (0x1553f0)
 *
 * Creates the IDirect3D8 object and performs a probe CreateDevice call to
 * verify that D3D hardware is usable.  The device is created with a fixed
 * 640x480 back-buffer, D3DSWAPEFFECT_DISCARD, fullscreen, auto depth/stencil
 * D3DFMT_D24S8 (0x2a), and BehaviorFlags 0x40
 * (D3DCREATE_HARDWARE_VERTEXPROCESSING on Xbox).  If CreateDevice succeeds,
 * device caps are fetched, Present is called, then the device and IDirect3D8
 * object are released.  On any failure an error is logged.
 *
 * Globals (not in kb.json, hardcoded):
 *   0x476a50  void *  – IDirect3D8 object pointer
 *   0x476ab0  void *  – IDirect3DDevice8 pointer
 *   0x5a59e0  –       – D3DCAPS8 output buffer
 *
 * Present_parameters layout confirmed against D3DPRESENT_PARAMETERS from
 * third_party/xbox/d3d8types.h (0x34 bytes total).
 */

/*
 * Minimal mirror of D3DPRESENT_PARAMETERS fields used here.
 * Layout matches d3d8types.h exactly (4-byte aligned, no pack).
 * Total: 0x34 bytes = 13 DWORD fields.
 */
#pragma pack(push, 4)
typedef struct {
  unsigned int BackBufferWidth; /* +0x00 */
  unsigned int BackBufferHeight; /* +0x04 */
  unsigned int BackBufferFormat; /* +0x08 (D3DFORMAT enum) */
  unsigned int BackBufferCount; /* +0x0c */
  unsigned int MultiSampleType; /* +0x10 (D3DMULTISAMPLE_TYPE) */
  unsigned int SwapEffect; /* +0x14 (D3DSWAPEFFECT enum) */
  void *hDeviceWindow; /* +0x18 (HWND) */
  unsigned int Windowed; /* +0x1c (BOOL) */
  unsigned int EnableAutoDepthStencil; /* +0x20 (BOOL) */
  unsigned int AutoDepthStencilFormat; /* +0x24 (D3DFORMAT enum) */
  unsigned int Flags; /* +0x28 (DWORD) */
  unsigned int FullScreen_RefreshRateInHz; /* +0x2c (UINT) */
  unsigned int FullScreen_PresentationInterval; /* +0x30 (UINT) */
} d3d_present_parameters_t;
#pragma pack(pop)

/* 0x1553f0 */
void rasterizer_preinitialize(void)
{
  int hr;
  d3d_present_parameters_t d3dpp;

  /* 0x1eeab0: stdcall Direct3DCreate(UINT sdkVersion) -> void * (IDirect3D8)
   */
  *(void **)0x476a50 = ((void *(__stdcall *)(unsigned int))0x1eeab0)(0);

  if (*(void **)0x476a50 == 0) {
    error(2, "### ERROR failed to create D3D object");
    error(2, "### ERROR rasterizer_preinitialize failed");
    return;
  }

  /* Zero-fill D3DPRESENT_PARAMETERS (0x34 bytes) then set used fields */
  csmemset(&d3dpp, 0, 0x34);
  d3dpp.BackBufferWidth = 0x280; /* 640 */
  d3dpp.BackBufferHeight = 0x1e0; /* 480 */
  d3dpp.BackBufferFormat = 0x06; /* D3DFMT_A8R8G8B8 */
  d3dpp.SwapEffect = 1; /* D3DSWAPEFFECT_DISCARD */
  d3dpp.Windowed = 0; /* fullscreen */
  d3dpp.EnableAutoDepthStencil = 1;
  d3dpp.AutoDepthStencilFormat = 0x2a; /* D3DFMT_D24S8 */
  d3dpp.Flags = 1;
  d3dpp.FullScreen_PresentationInterval = 0;

  /*
   * 0x1edec0: stdcall IDirect3D8_CreateDevice(
   *   Adapter, DeviceType, hFocusWindow, BehaviorFlags,
   *   pPresentationParameters, ppReturnedDeviceInterface)
   * RET 0x18 confirms 6 args (stdcall).
   */
  hr = ((int(__stdcall *)(unsigned int, unsigned int, void *, unsigned int,
                          d3d_present_parameters_t *, void **))0x1edec0)(
    0, /* D3DADAPTER_DEFAULT */
    1, /* D3DDEVTYPE_HAL */
    0, /* hFocusWindow = NULL (fullscreen) */
    0x40, /* D3DCREATE_HARDWARE_VERTEXPROCESSING */
    &d3dpp, (void **)0x476ab0);

  if (hr < 0) {
    /*
     * 0x167ff0: reports a D3D HRESULT failure with context string and
     * logs via error(). Signature: (HRESULT, const char *context).
     */
    ((void (*)(int, const char *))0x167ff0)(
      hr,
      "IDirect3D8_CreateDevice(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL,"
      " RASTERIZER_DEVICE_CREATION_FLAGS, &d3d_present_parameters,"
      " &global_d3d_device)");
  }

  if (*(void **)0x476ab0 == 0 || hr < 0) {
    *(void **)0x476ab0 = 0;
    error(2, "### ERROR failed to create D3D device");
    error(2, "### ERROR rasterizer_preinitialize failed");
    return;
  }

  /* 0x1e69f0: D3DDevice_GetDeviceCaps(&d3d_caps) — 1 arg (stdcall, RET 0x4) */
  ((void(__stdcall *)(void *))0x1e69f0)((void *)0x5a59e0);

  /* 0x1ee920: D3DDevice_Present(NULL, NULL, NULL, NULL) — 4 args (stdcall, RET
   * 0x10) */
  ((void(__stdcall *)(void *, void *, void *, void *))0x1ee920)(0, 0, 0, 0);

  /* Release device if acquired */
  if (*(void **)0x476ab0 != 0) {
    /* 0x1e6f50: D3DDevice_Release() — no args */
    ((void (*)(void))0x1e6f50)();
    *(void **)0x476ab0 = 0;
  }

  /* Release IDirect3D8 object */
  if (*(void **)0x476a50 != 0) {
    *(void **)0x476a50 = 0;
  }
}

/*
 * rasterizer_get_default_hardware_format (0x155580)
 *
 * Returns the default D3D texture pointer for a bitmap based on its type.
 * Bitmap types 0 (2D) and 1 (volume) map to the 2D default at 0x3256a4.
 * Bitmap type 2 (cubemap) maps to the cubemap default at 0x3256ac.
 * These globals are populated by rasterizer_filthy_bitmap_default_initialize
 * (FUN_00156e00).
 *
 * Globals:
 *   0x3256a4  void *  – default 2D hardware texture format
 *   0x3256a8  void *  – default volume texture format
 *   0x3256ac  void *  – default cubemap texture format
 */
/* 0x155580 */
void *rasterizer_get_default_hardware_format(void *bitmap_data)
{
  short type;
  void *result;

  if (!bitmap_data) {
    display_assert("bitmap",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                   0xd1, true);
    system_exit(-1);
  }

  type = *(short *)((char *)bitmap_data + 0xa);
  if (type != 0 && type != 1) {
    if (type == 2) {
      result = *(void **)0x3256ac;
    } else {
      display_assert("### ERROR unsupported bitmap type",
                     "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                     0xdf, true);
      system_exit(-1);
      result = bitmap_data;
    }
  } else {
    result = *(void **)0x3256a4;
  }

  if (!result) {
    display_assert("hardware_format",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                   0xe2, true);
    system_exit(-1);
  }

  return result;
}
/* --- rasterizer_xbox.obj batch drafts (2026-07-26) --- */

/* FUN_00155350 (0x155350) — readable C lift. */
int FUN_00155350(int a, int b)
{
  D3DDevice_Present((void *)(unsigned)a, (void *)(unsigned)b, 0, 0);
  return 0;
}

/* FUN_00155380 (0x155380) — readable C lift. */
__attribute__((stdcall))
int FUN_00155380(int a, int b, int c, int d, int e)
{
  return D3DDevice_CreateTexture((uint32_t)a, (uint32_t)b, (uint32_t)c, (uint32_t)d, (uint32_t)e, 0, 0);
}



/* FUN_001553a0 (0x1553a0) — readable C lift. */
__attribute__((stdcall))
int FUN_001553a0(int a, int b, int c, int d, int e, int f)
{
  return D3DDevice_CreateVolumeTexture(a, b, c, d, e, f, 0, 0);
}


/* FUN_001553d0 (0x1553d0) — readable C lift. */
__attribute__((stdcall))
int FUN_001553d0(int a, int b, int c, int d)
{
  return D3DDevice_CreateCubeTexture(a, b, c, d, 0, 0);
}



/* FUN_00155560 (0x155560) — readable C lift. */
int FUN_00155560(int a, int b, int c, int d, int e)
{
  D3DDevice_Clear((uint32_t)a, (void *)(unsigned)b, (uint32_t)c, (uint32_t)d, *(float *)&e, 0);
  return 0;
}

/* FUN_00155880 (0x155880) — readable C lift. */
int FUN_00155880(int a /* @<eax> */, int b /* @<ecx> */, int unused, int *out)
{
  int idx;
  (void)unused;
  idx = (a << 5) + b;
  *out = *(int *)(0x1fb498 + idx * 4);
  return 0;
}
/* 0x1559a0 */
void _rasterizer_reset_state(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1559b0 */
void rasterizer_spin_begin(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1559c0 */
void rasterizer_spin_end(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* _rasterizer_windows_begin (0x1559d0) — readable C lift from XBE leaf. */
void _rasterizer_windows_begin(void)
{
  extern char DAT_0029dc40[];
  extern char DAT_0029dc0c[];

  if (*(int *)0x476ab0 == 0) {
    display_assert(DAT_0029dc40, DAT_0029dc0c, 0x533, true);
    system_exit(-1);
  }
}



/* _rasterizer_window_get_fog (0x155a00) — readable C lift from XBE leaf. */
void _rasterizer_window_get_fog(void *out_fog)
{
  extern char DAT_0029dc54[];
  extern char DAT_0029dc0c[];
  int i;
  uint32_t *dst;
  const uint32_t *src;

  if (out_fog == 0) {
    display_assert(DAT_0029dc54, DAT_0029dc0c, 0x5a0, true);
    system_exit(-1);
  }
  dst = (uint32_t *)out_fog;
  src = (const uint32_t *)0x5a5da8;
  for (i = 0; i < 0x14; i++) {
    dst[i] = src[i];
  }
}

/* _rasterizer_windows_end (0x155a40) — readable C lift from XBE leaf. */
void _rasterizer_windows_end(void)
{
  extern char DAT_0029dc40[];
  extern char DAT_0029dc0c[];

  if (*(int *)0x476ab0 == 0) {
    display_assert(DAT_0029dc40, DAT_0029dc0c, 0x65d, true);
    system_exit(-1);
  }
}



/* _rasterizer_frame_end (0x155a70) — readable C lift. */
void _rasterizer_frame_end(void)
{
  int i;
  char ok = 1;

  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x29dc0c, 0x670, 1);
    system_exit(-1);
  }
  FUN_0016FDD0();
  FUN_0017ff50();
  for (i = 0; i < 4; i++) {
    D3DDevice_SetTexture((unsigned int)i, 0);
    if (!ok) {
      ok = 0;
      FUN_00167ff0(0, (const char *)0x29dcfc);
    } else {
      ok = 1;
    }
  }
  for (i = 0; i < 0x10; i++) {
    D3DDevice_SetStreamSource((unsigned int)i, 0, 0);
    if (!ok) {
      ok = 0;
      FUN_00167ff0(0, (const char *)0x29dcb8);
    } else {
      ok = 1;
    }
  }
  D3DDevice_SetIndices(0, 0);
  if (!ok) {
    FUN_00167ff0(0, (const char *)0x29dc80);
    error(2, (const char *)0x29dc58);
  }
}
/* FUN_00155b60 (0x155b60) — readable C lift. */
int FUN_00155b60(int a, int b)
{
  D3DTexture_LockRect((void *)(unsigned)a, (unsigned int)b, 0, 0, 0);
  return 0;
}

/* _rasterizer_dispose (0x155b90) — readable C lift. */
void _rasterizer_dispose(void)
{
  rasterizer_memory_pool_delete();
  FUN_0015e9e0();
  FUN_00184690(0);
  FUN_00178ab0();
  FUN_0017e040();
  FUN_0017ff60();
  rasterizer_text_cache_dispose();
  FUN_0015c680();
  FUN_0016fec0();
  FUN_00165a10();
  FUN_0017d990();
  texture_cache_delete();
  if (*(int *)0x476ab0) {
    D3DDevice_Release();
    *(int *)0x476ab0 = 0;
  }
  if (*(int *)0x476a50)
    *(int *)0x476a50 = 0;
}
/* FUN_00155c10 (0x155c10) — readable C lift. */
void FUN_00155c10(void *callback)
{
  ((void (__stdcall *)(void *))D3DDevice_SetVerticalBlankCallback)(callback);
}



/* rasterizer_set_texture_bitmap_data (0x155c20) — readable C lift. */
char rasterizer_set_texture_bitmap_data(short stage, void *bitmap_data)
{
  void *hw;

  if ((short)stage < 0 || (short)stage >= 4) {
    display_assert((char *)0x29dda4, (char *)0x29dc0c, 0x78f, 1);
    system_exit(-1);
  }
  if (!bitmap_data) {
    display_assert((char *)0x29dd68, (char *)0x29dc0c, 0x797, 1);
    error(2, (const char *)0x29dd38, (int)(short)stage);
    return 1;
  }
  profile_texture_start();
  hw = xbox_texture_cache_get_hardware_format(bitmap_data, 1, 1);
  profile_texture_end();
  D3DDevice_SetTexture((unsigned int)(short)stage, hw);
  return 1;
}
/* FUN_00155cc0 (0x155cc0) — readable C lift. */
int FUN_00155cc0(int a, int b)
{
  ((void (__stdcall *)(int, int, int, int, int))D3DVolumeTexture_LockBox)(a, b, 0, 0, 0);
  return 0;
}

/* rasterizer_set_texture_direct (0x155cf0) — readable C lift. */
char rasterizer_set_texture_direct(short stage, int bitmap_tag_index, short frame_index)
{
  void *tag;
  int count;
  void *bitmap;
  int rem;

  if (stage < 0 || stage >= 4) {
    display_assert((const char *)0x29dda4, (const char *)0x29dc0c, 0x7a6, true);
    system_exit(-1);
  }
  if (bitmap_tag_index != -1) {
    tag = tag_get(0x6269746d, bitmap_tag_index);
    count = *(int *)((char *)tag + 0x60);
    if (count > 0) {
      rem = (int)frame_index % count;
      bitmap = FUN_00076ff0(bitmap_tag_index, (short)rem);
      if (bitmap) {
        rasterizer_set_texture_bitmap_data(stage, bitmap);
        return 1;
      }
    }
  }
  display_assert((const char *)0x29ddd8, (const char *)0x29dc0c, 0x7be, true);
  error(2, (const char *)0x29dd38, (int)stage);
  return 0;
}


/* rasterizer_set_texture_direct_non_blocking (0x155da0) — readable C lift. */
char rasterizer_set_texture_direct_non_blocking(int stage, int bitmap_tag_index, int frame_index)
{
  void *tag;
  int count;
  void *bitmap;
  void *hw;
  char ok = 0;
  int frame;
  int rem;

  if ((short)stage < 0 || (short)stage >= 4) {
    display_assert((char *)0x29dda4, (char *)0x29dc0c, 0x7d3, 1);
    system_exit(-1);
  }
  if (bitmap_tag_index != -1) {
    tag = tag_get(0x6269746d, bitmap_tag_index);
    count = *(int *)((char *)tag + 0x60);
    if (count > 0) {
      frame = (int)(short)frame_index;
      rem = frame % count;
      bitmap = FUN_00076ff0(bitmap_tag_index, (short)rem);
      if (bitmap) {
        hw = xbox_texture_cache_get_hardware_format(bitmap, 0, 1);
        if (!hw)
          return 1;
        rasterizer_set_texture_bitmap_data((short)stage, bitmap);
        return ok;
      }
    }
  }
  display_assert((char *)0x29de10, (char *)0x29dc0c, 0x7f3, 1);
  error(2, (const char *)0x29dd38, (int)(short)stage);
  return ok;
}
/* rasterizer_set_texture (0x155e80) — readable C lift (restored pre-naked). */
void rasterizer_set_texture(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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
  /* relift: relift: mov (char)eax, byte ptr [0x3256e1] */
  /* test (char)eax, (char)eax -> jne 0x155f28 */
  /* cmp (int16_t)ebx, 3 -> je 0x155fc0 */
  /* cmp esi, -1 -> je 0x155fc0 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x155fc0 */
  FUN_00076ff0(0, 0);
  /* relift: cmp word ptr [esi + 0xa], (int16_t)edi -> jne 0x155f97 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  /* relift: relift: mov word ptr [0x476a4c], (int16_t)ecx */
  /* relift: relift: mov word ptr [0x476a4e], (int16_t)edx */
  bitmap_type_get_string(0);
  bitmap_type_get_string(0);
  error(0, (char *)0x0029ded0);
  /* cmp eax, -1 -> je 0x156024 */
  FUN_00076ff0(0, 0);
  /* test esi, esi -> je 0x156024 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  /* relift: relift: mov word ptr [0x476a4c], (int16_t)ecx */
  /* relift: relift: mov word ptr [0x476a4e], (int16_t)edx */
  display_assert((char *)0x0029de9c, (char *)0x0029dc0c, 2117, 0);
  error(0, (char *)0x0029de58);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00156070 (0x156070) — readable C lift. */
int FUN_00156070(int a, int b, int c)
{
  D3DCubeTexture_LockRect(a, b, c, 0, 0, 0);
  return 0;
}


/* rasterizer_set_texture_non_blocking (0x1560a0) — readable C lift (restored pre-naked). */
void rasterizer_set_texture_non_blocking(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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
  /* relift: relift: mov (char)eax, byte ptr [0x3256e1] */
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
  /* relift: relift: mov word ptr [0x476a48], (int16_t)ecx */
  /* relift: relift: mov word ptr [0x476a4a], (int16_t)edx */
  display_assert((char *)0x0029df3c, (char *)0x0029dc0c, 2210, 0);
  error(0, (char *)0x0029de58);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* rasterizer_get_target (0x156250) — readable C lift (restored pre-naked). */
void rasterizer_get_target(void)
{
  int eax = 0;
  int esi = 0;
  int ebp = 0;

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
  ((void(*)(void))D3DPalette_Lock)();

  (void)eax;
  (void)esi;
  (void)ebp;
}



/* rasterizer_set_vertex_shader (0x156440) — readable C lift. */
void rasterizer_set_vertex_shader(short shader_index)
{
  int idx;
  int handle;
  char ok;

  if (shader_index < 0) {
    display_assert((const char *)0x29e084, (const char *)0x29dc0c, 0xa35, true);
    system_exit(-1);
  }
  if (shader_index >= 0x43) {
    display_assert((const char *)0x29e054, (const char *)0x29dc0c, 0xa36, true);
    system_exit(-1);
  }
  if (shader_index == *(short *)0x325164)
    return;
  idx = (int)shader_index;
  handle = *(int *)(0x325208 + (idx << 4));
  if (handle != -1) {
    D3DDevice_SetVertexShader((uint32_t)handle);
    ok = 1;
    if (*(short *)0x3256ba != 0)
      *(int *)0x5a5558 += *(int *)(0x32520c + (idx << 4));
  } else {
    error(2, (const char *)0x29e02c, idx);
    ok = 0;
  }
  *(short *)0x325164 = shader_index;
  if (!ok)
    error(2, (const char *)0x29dffc);
}


/* rasterizer_set_pixel_shader (0x156510) — readable C lift (restored pre-naked). */
void rasterizer_set_pixel_shader(void *state)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test esi, esi -> jne 0x15653f */
  display_assert((char *)0x0029e09c, (char *)0x0029dc0c, 2652, 0);
  system_exit(0);
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
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
  ((void(*)(void))D3DDevice_SetRenderStateNotInline)();
  ((void(*)(void))D3DDevice_SetRenderStateNotInline)();
  ((void(*)(void))D3DDevice_SetRenderStateNotInline)();
  ((void(*)(void))D3DDevice_SetRenderStateNotInline)();
  /* test (char)ebx, (char)ebx -> jne 0x15667e */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x15668b */
  ((void(*)(void))D3DDevice_SetRenderStateNotInline)();
  /* test (char)eax, (char)eax -> jne 0x156699 */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x1566a6 */
  ((void(*)(void))D3DDevice_SetRenderStateNotInline)();
  /* mem[0x005a555c] = edx */
  D3DDevice_SetPixelShaderProgram((void *)(uintptr_t)esi);
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x156704 */

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}



/* rasterizer_set_model_skinning (0x156710) — readable C lift (restored pre-naked). */
void rasterizer_set_model_skinning(void *a1)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)ecx;
  (void)edx;
  (void)esi;
}


/* rasterizer_set_model_lighting_point_light (0x156850) — readable C lift (restored pre-naked). */
void rasterizer_set_model_lighting_point_light(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x15687c */
  display_assert((char *)0x0029e178, (char *)0x0029dc0c, 2826, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x156997 */
  /* cmp esi, eax -> jl 0x1568c5 */
  csprintf((char *)0x005ab100, (char *)0x0029e148);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x1568fe */
  display_assert((char *)0x0029e134, (char *)0x0029dc0c, 2837, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx + 0x1c], 0xbf800000 -> je 0x156985 */
  csmemset((void *)(uintptr_t)esi, 0, 48);
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_001569f0 (0x1569f0) — readable C lift. */
void FUN_001569f0(void *src, short index, void *dst)
{
  int *s;
  int *d1;
  int *d2;
  int idx;
  if (!dst) {
    display_assert((const char *)0x29e178, (const char *)0x29dc0c, 0xb3a, 1);
    system_exit(-1);
  }
  s = (int *)src;
  if (!s)
    return;
  idx = (int)index;
  d1 = (int *)((char *)dst + ((idx + 3) << 5));
  d1[0] = s[3];
  d1[1] = s[4];
  d1[2] = s[5];
  d2 = (int *)((char *)dst + 0x70 + (idx << 5));
  d2[0] = s[0];
  d2[1] = s[1];
  d2[2] = s[2];
}

/* FUN_00156a90 (0x156a90) — readable C lift. */
int FUN_00156a90(int a)
{
  D3DSurface_LockRect((void *)(unsigned)a, 0, 0, 0);
  return 0;
}

/* rasterizer_set_model_lighting (0x156ab0) — readable C lift (restored pre-naked). */
void rasterizer_set_model_lighting(void *lighting)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

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
  /* relift: relift: fld dword ptr [0x3256f0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x156b79 */
  csmemset((void *)(uintptr_t)eax, 0, 176);
  /* relift: relift: fld dword ptr [0x3256f0] */
  /* relift: cmp word ptr [ebx + 0x40], (int16_t)esi -> jle 0x156b8a */
  rasterizer_set_model_lighting_point_light();
  /* cmp (int16_t)esi, 2 -> jl 0x156b80 */
  ((void(*)(void))FUN_001569f0)();
  /* cmp (int16_t)esi, 2 -> jl 0x156bb0 */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 11);

  (void)eax;
  (void)ebx;
  (void)esi;
}



/* rasterizer_set_frustum_z (0x156c30) — readable C lift (restored pre-naked). */
void rasterizer_set_frustum_z(float near_z, float far_z)
{
  int eax = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x156c62 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 2967, 0);
  system_exit(0);
  ((void(*)(void))render_camera_hack_frustum_z)();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x325168] */

  (void)eax;
  (void)edx;
}



/* SetupSmartStates (0x156d80) — readable C lift from XBE leaf. */
void SetupSmartStates(void)
{
  int i;

  csmemcpy((void *)0x5a57a0, (void *)0x1fb698, 0x240);
  for (i = 0; i < 0x80; i += 4) {
    *(int *)(0x5a55a0 + i) = *(int *)(0x1fb498 + i);
    *(int *)(0x5a5620 + i) = *(int *)(0x1fb518 + i);
    *(int *)(0x5a56a0 + i) = *(int *)(0x1fb598 + i);
    *(int *)(0x5a5720 + i) = *(int *)(0x1fb618 + i);
  }
  *(int *)0x5a5580 = 0;
  *(int *)0x5a5584 = 0;
  *(int *)0x5a5588 = 0;
  *(int *)0x5a558c = 0;
}

/* FUN_00156e00 (0x156e00) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b156e00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156e00_exitfn)(int) = system_exit;
static void __stdcall (*const b156e00_c1e6ae0)(uint32_t width, uint32_t height, uint32_t levels, uint32_t usage, uint32_t format, uint32_t pool, void *out_texture) = (void *)D3DDevice_CreateTexture;
static void (*const b156e00_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b156e00_c1e6b10)(void) = (void *)D3DDevice_CreateVolumeTexture;
static void (*const b156e00_c1e6b40)(void) = (void *)D3DDevice_CreateCubeTexture;
static void __stdcall (*const b156e00_c1edc70)(void *texture, unsigned int level, void *locked_rect, void *rect, unsigned int flags) = (void *)D3DTexture_LockRect;
static void (*const b156e00_c1edd80)(void) = (void *)D3DVolumeTexture_LockBox;
static void (*const b156e00_c1edd10)(void) = (void *)D3DCubeTexture_LockRect;

__attribute__((naked, noinline))
void FUN_00156e00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00156e00_1\n\t"
      "pushl $1\n\t"
      "pushl $0xef\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00156e00_1:\n\t"
      "pushl %%ebx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl $4\n\t"
      "call *%[c1e6ae0]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00156e00_2\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00156e00_3\n\t"
      ".LFUN_00156e00_2:\n\t"
      "pushl $0x29e4b8\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00156e00_3:\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl $4\n\t"
      "pushl $4\n\t"
      "call *%[c1e6b10]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00156e00_4\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00156e00_4\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00156e00_5\n\t"
      ".LFUN_00156e00_4:\n\t"
      "pushl $0x29e418\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00156e00_5:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "call *%[c1e6b40]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00156e00_6\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_00156e00_7\n\t"
      ".LFUN_00156e00_6:\n\t"
      "pushl $0x29e380\n\t"
      "pushl %%eax\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00156e00_16\n\t"
      ".LFUN_00156e00_7:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00156e00_16\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00156e00_16\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00156e00_16\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movw $0xf00, -0x4(%%ebp)\n\t"
      "movw $0xf0f0, -0x2(%%ebp)\n\t"
      "call *%[c1edc70]\n\t"
      "pushl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x10, %%ecx\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00156e00_8:\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "movw -0x4(%%ebp,%%edx,2), %%dx\n\t"
      "movw %%dx, (%%esi,%%eax,2)\n\t"
      "incl %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00156e00_8\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1edd80]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x40, %%ecx\n\t"
      ".LFUN_00156e00_9:\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "movw -0x4(%%ebp,%%edx,2), %%dx\n\t"
      "movw %%dx, (%%esi,%%eax,2)\n\t"
      "incl %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00156e00_9\n\t"
      "movb $1, %%bl\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $6, -0x10(%%ebp)\n\t"
      ".LFUN_00156e00_10:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1edd10]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00156e00_11\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00156e00_12\n\t"
      ".LFUN_00156e00_11:\n\t"
      "pushl $0x29e300\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00156e00_12:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x10, %%ecx\n\t"
      ".LFUN_00156e00_13:\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "movw -0x4(%%ebp,%%edx,2), %%dx\n\t"
      "movw %%dx, (%%edi,%%eax,2)\n\t"
      "incl %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00156e00_13\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00156e00_14\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00156e00_15\n\t"
      ".LFUN_00156e00_14:\n\t"
      "pushl $0x29e298\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00156e00_15:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_00156e00_10\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jne .LFUN_00156e00_17\n\t"
      ".LFUN_00156e00_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x137\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e258\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00156e00_17:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, 0x3256a4\n\t"
      "movl %%ecx, 0x3256a8\n\t"
      "movl %%edx, 0x3256ac\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156e00_assert), [exitfn] "m"(b156e00_exitfn), [c1e6ae0] "m"(b156e00_c1e6ae0), [c167ff0] "m"(b156e00_c167ff0), [c1e6b10] "m"(b156e00_c1e6b10), [c1e6b40] "m"(b156e00_c1e6b40), [c1edc70] "m"(b156e00_c1edc70), [c1edd80] "m"(b156e00_c1edd80), [c1edd10] "m"(b156e00_c1edd10)
      : "memory");
}
#else
#error "FUN_00156e00: clang naked draft required"
#endif


/* FUN_00157010 (0x157010) — XBE naked draft (batch 326). */
#if defined(__clang__)
static void (*const b157010_c1edea0)(void) = (void *)D3D_SetPushBufferSize;
static void b157010_c1eeab0_tgt(void) { return; }
static void (*const b157010_c1eeab0)(void) = (void *)b157010_c1eeab0_tgt;
static void (*const b157010_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void *(*const b157010_memset)(void *, int, unsigned int) = csmemset;
static void (*const b157010_c1edec0)(void) = (void *)Direct3D_CreateDevice;
static void (*const b157010_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void __stdcall (*const b157010_c1e69f0)(void *caps) = (void *)D3DDevice_GetDeviceCaps;
static void (*const b157010_c156d80)(void) = (void *)SetupSmartStates;
static void (*const b157010_c1ef170)(void) = (void *)D3DDevice_CreatePalette;
static void (*const b157010_c1eefe0)(void) = (void *)D3DPalette_Lock;
static void * (*const b157010_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b157010_c1e88a0)(void) = (void *)D3DDevice_SetPalette;
static int __stdcall (*const b157010_c1e7d50)(int back_buffer, uint32_t type, void **out_surface) = (void *)D3DDevice_GetBackBuffer;
static int __stdcall (*const b157010_c1e8270)(void **out_surface) = (void *)D3DDevice_GetDepthStencilSurface;
static void * (*const b157010_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void __stdcall (*const b157010_c1e6ae0)(uint32_t width, uint32_t height, uint32_t levels, uint32_t usage, uint32_t format, uint32_t pool, void *out_texture) = (void *)D3DDevice_CreateTexture;
static void (*const b157010_c1edc20)(void) = (void *)D3DTexture_GetSurfaceLevel;
static void (*const b157010_c1eb590)(void) = (void *)D3DDevice_SetShaderConstantMode;
static void __stdcall (*const b157010_c1ea290)(uint32_t enable) = (void *)D3DDevice_SetRenderState_ZEnable;
static void (*const b157010_c1e9350)(uint32_t reg, uint32_t value) = (void *)D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b157010_c1e98e0)(uint32_t value) = (void *)D3DDevice_SetRenderState_ZBias;
static void (*const b157010_c1e9380)(uint32_t reg_index, uint32_t value) = (void *)D3DDevice_SetRenderState_Deferred;
static void (*const b157010_c1e9ae0)(void) = (void *)D3DDevice_SetTextureState_TexCoordIndex;
static void (*const b157010_c1e72a0)(void) = (void *)D3DDevice_SetFlickerFilter;
static void (*const b157010_c1e72c0)(void) = (void *)D3DDevice_SetSoftDisplayFilter;
static void (*const b157010_c156e00)(void) = (void *)FUN_00156e00;
static int (*const b157010_c1824e0)(void) = (void *)rasterizer_memory_pool_new;
static void (*const b157010_c15e800)(void) = (void *)FUN_0015e800;
static int (*const b157010_c184260)(void) = (void *)rasterizer_transparent_geometry_new;
static void (*const b157010_c178850)(void) = (void *)FUN_00178850;
static void (*const b157010_c17df80)(void) = (void *)FUN_0017df80;
static void (*const b157010_c17eb50)(void) = (void *)FUN_0017eb50;
static int (*const b157010_c183650)(void) = (void *)rasterizer_text_cache_initialize;
static char (*const b157010_c15c2d0)(void) = (void *)FUN_0015c2d0;
static void (*const b157010_c16f6c0)(void) = (void *)FUN_0016f6c0;
static char (*const b157010_c1659a0)(void) = FUN_001659a0;
static void (*const b157010_c17d910)(void) = (void *)rasterizer_screen_effects_initialize;
static void (*const b157010_c1bf080)(void) = (void *)texture_cache_new;
static void (*const b157010_c17e010)(void) = (void *)FUN_0017e010;

__attribute__((naked, noinline))
void FUN_00157010(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "movw 0x325688, %%cx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, %%cx\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00157010_1\n\t"
      "movw $0x200, %%cx\n\t"
      "movw %%cx, 0x325688\n\t"
      ".LFUN_00157010_1:\n\t"
      "movw 0x32568a, %%ax\n\t"
      "cmpw %%si, %%ax\n\t"
      "jne .LFUN_00157010_2\n\t"
      "movw $0x20, %%ax\n\t"
      "movw %%ax, 0x32568a\n\t"
      ".LFUN_00157010_2:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "shll $0xa, %%eax\n\t"
      "pushl %%eax\n\t"
      "shll $0xa, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1edea0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1eeab0]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, 0x476a50\n\t"
      "movl $1, %%edi\n\t"
      "jne .LFUN_00157010_3\n\t"
      "pushl $0x29dbd4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00157010_77\n\t"
      ".LFUN_00157010_3:\n\t"
      "pushl $0x34\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movw %%si, 0x325654\n\t"
      "movw %%si, 0x325656\n\t"
      "movw $0x280, 0x32565a\n\t"
      "movw $0x1e0, 0x325658\n\t"
      "movw $0x30, 0x32565e\n\t"
      "movw $0x250, 0x325662\n\t"
      "movw $0x24, 0x32565c\n\t"
      "movw $0x1bc, 0x325660\n\t"
      "movl %%edi, 0x325668\n\t"
      "movl %%esi, 0x32566c\n\t"
      "call *%[memset]\n\t"
      "movb 0x32568c, %%dl\n\t"
      "movswl 0x32565a, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "movswl 0x325656, %%edx\n\t"
      "setne %%al\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movswl 0x325654, %%ecx\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "addl $0x2a, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl 0x325658, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movw 0x325690, %%cx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "movl $6, -0x34(%%ebp)\n\t"
      "je .LFUN_00157010_7\n\t"
      "cmpl $0x1e, %%eax\n\t"
      "je .LFUN_00157010_6\n\t"
      "cmpl $0x3c, %%eax\n\t"
      "je .LFUN_00157010_5\n\t"
      "cmpw %%si, %%cx\n\t"
      "je .LFUN_00157010_4\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29efc8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%si, 0x325690\n\t"
      ".LFUN_00157010_4:\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movb $1, 0x31fa96\n\t"
      "jmp .LFUN_00157010_8\n\t"
      ".LFUN_00157010_5:\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movb $1, 0x31fa96\n\t"
      "jmp .LFUN_00157010_8\n\t"
      ".LFUN_00157010_6:\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      "movb $1, 0x31fa96\n\t"
      "jmp .LFUN_00157010_8\n\t"
      ".LFUN_00157010_7:\n\t"
      "movl $0x80000000, -0xc(%%ebp)\n\t"
      "movb $0, 0x31fa96\n\t"
      ".LFUN_00157010_8:\n\t"
      "pushl $0x476ab0\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x40\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1edec0]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_9\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_10\n\t"
      ".LFUN_00157010_9:\n\t"
      "pushl $0x29db10\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_10:\n\t"
      "cmpl %%esi, 0x476ab0\n\t"
      "jne .LFUN_00157010_11\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00157010_12\n\t"
      ".LFUN_00157010_11:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00157010_13\n\t"
      ".LFUN_00157010_12:\n\t"
      "pushl $0x29dae8\n\t"
      "pushl $2\n\t"
      "movl %%esi, 0x476ab0\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00157010_77\n\t"
      ".LFUN_00157010_13:\n\t"
      "pushl $0x5a59e0\n\t"
      "call *%[c1e69f0]\n\t"
      "call *%[c156d80]\n\t"
      "pushl $0x476ab4\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c1ef170]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_14\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_15\n\t"
      ".LFUN_00157010_14:\n\t"
      "pushl $0x29ef78\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_15:\n\t"
      "movl 0x476ab4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1eefe0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_16\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_17\n\t"
      ".LFUN_00157010_16:\n\t"
      "pushl $0x29ef3c\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_17:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $0x400\n\t"
      "pushl $0x2ee0a0\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_18\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_19\n\t"
      ".LFUN_00157010_18:\n\t"
      "pushl $0x29ef14\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_19:\n\t"
      "movl 0x476ab4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e88a0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_20\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_21\n\t"
      ".LFUN_00157010_20:\n\t"
      "pushl $0x29eed4\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_21:\n\t"
      "movl 0x476ab4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e88a0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_22\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_23\n\t"
      ".LFUN_00157010_22:\n\t"
      "pushl $0x29ee94\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_23:\n\t"
      "movl 0x476ab4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $2\n\t"
      "call *%[c1e88a0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_24\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_25\n\t"
      ".LFUN_00157010_24:\n\t"
      "pushl $0x29ee54\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_25:\n\t"
      "movl 0x476ab4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "call *%[c1e88a0]\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00157010_26\n\t"
      "pushl $0x29ee14\n\t"
      "pushl %%esi\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00157010_77\n\t"
      ".LFUN_00157010_26:\n\t"
      "pushl $0x476a5c\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e7d50]\n\t"
      "pushl $0x476a60\n\t"
      "call *%[c1e8270]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_27\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00157010_28\n\t"
      ".LFUN_00157010_27:\n\t"
      "pushl $0x29edb0\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_28:\n\t"
      "pushl $0x232\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl %%esi\n\t"
      "pushl $0x14\n\t"
      "call *%[c8ee60]\n\t"
      "pushl $0x233\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl %%esi\n\t"
      "pushl $0x14\n\t"
      "movl %%eax, 0x476a54\n\t"
      "call *%[c8ee60]\n\t"
      "movl 0x476a54, %%ecx\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "movl %%eax, 0x476a58\n\t"
      "movl $0x271df27f, %%edi\n\t"
      "movl $0x11229, %%ebx\n\t"
      "je .LFUN_00157010_32\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_00157010_32\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_00157010_29\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00157010_29:\n\t"
      "cmpw $1, %%cx\n\t"
      "movswl %%cx, %%edx\n\t"
      "movl 0x476a54(,%%edx,4), %%eax\n\t"
      "movl $0x40001, (%%eax)\n\t"
      "jne .LFUN_00157010_30\n\t"
      "movl 0x476a5c, %%edx\n\t"
      "movl 0x4(%%edx), %%edx\n\t"
      "jmp .LFUN_00157010_31\n\t"
      ".LFUN_00157010_30:\n\t"
      "xorl %%edx, %%edx\n\t"
      ".LFUN_00157010_31:\n\t"
      "incl %%ecx\n\t"
      "cmpw $2, %%cx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl %%edi, 0x10(%%eax)\n\t"
      "movl %%ebx, 0xc(%%eax)\n\t"
      "jl .LFUN_00157010_29\n\t"
      "jmp .LFUN_00157010_33\n\t"
      ".LFUN_00157010_32:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00157010_33:\n\t"
      "pushl $0x262\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl %%esi\n\t"
      "pushl $0x18\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, 0x476aac\n\t"
      "je .LFUN_00157010_34\n\t"
      "movl 0x476a5c, %%esi\n\t"
      "movl $6, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x476a60, %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl $0x271df27f, %%edi\n\t"
      "jmp .LFUN_00157010_35\n\t"
      ".LFUN_00157010_34:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00157010_35:\n\t"
      "pushl $0x26f\n\t"
      "pushl $0x29dc0c\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x14\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, 0x476aa8\n\t"
      "je .LFUN_00157010_36\n\t"
      "movl $0x40001, (%%eax)\n\t"
      "movl 0x476a60, %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%ebx, 0xc(%%eax)\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl %%edi, 0x10(%%eax)\n\t"
      "jmp .LFUN_00157010_37\n\t"
      ".LFUN_00157010_36:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_37:\n\t"
      "pushl $0x476a64\n\t"
      "pushl %%esi\n\t"
      "pushl $0x12\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl $0xf0\n\t"
      "pushl $0x140\n\t"
      "call *%[c1e6ae0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_38\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_38\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_39\n\t"
      ".LFUN_00157010_38:\n\t"
      "pushl $0x29ecc0\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_39:\n\t"
      "movl 0x476a64, %%eax\n\t"
      "pushl $0x476a6c\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1edc20]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_40\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_40\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_41\n\t"
      ".LFUN_00157010_40:\n\t"
      "pushl $0x29ec50\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_41:\n\t"
      "cmpl %%esi, 0x476a64\n\t"
      "je .LFUN_00157010_42\n\t"
      "cmpl %%esi, 0x476a6c\n\t"
      "jne .LFUN_00157010_43\n\t"
      ".LFUN_00157010_42:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_43:\n\t"
      "pushl $0x476a94\n\t"
      "pushl %%esi\n\t"
      "pushl $6\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl $0x80\n\t"
      "pushl $0x80\n\t"
      "movl %%esi, 0x476a68\n\t"
      "movl %%esi, 0x476a70\n\t"
      "call *%[c1e6ae0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_44\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_44\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_45\n\t"
      ".LFUN_00157010_44:\n\t"
      "pushl $0x29eb60\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_45:\n\t"
      "movl 0x476a94, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00157010_46\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_46:\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_51\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00157010_47:\n\t"
      "cmpw $4, %%di\n\t"
      "jge .LFUN_00157010_51\n\t"
      "movl 0x476a94, %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "leal 0x476a98(,%%eax,4), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1edc20]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_48\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00157010_48\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_49\n\t"
      ".LFUN_00157010_48:\n\t"
      "pushl $0x29eae8\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_49:\n\t"
      "cmpl $0, (%%esi)\n\t"
      "jne .LFUN_00157010_50\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_50:\n\t"
      "incl %%edi\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00157010_47\n\t"
      ".LFUN_00157010_51:\n\t"
      "pushl $0x476a74\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $5\n\t"
      "movl $1, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x80\n\t"
      "pushl $0x80\n\t"
      "call *%[c1e6ae0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_52\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_52\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_53\n\t"
      ".LFUN_00157010_52:\n\t"
      "pushl $0x29ea08\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_53:\n\t"
      "movl 0x476a74, %%edx\n\t"
      "pushl $0x476a78\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1edc20]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_54\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_54\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_55\n\t"
      ".LFUN_00157010_54:\n\t"
      "pushl $0x29e998\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_55:\n\t"
      "cmpl %%esi, 0x476a74\n\t"
      "je .LFUN_00157010_56\n\t"
      "cmpl %%esi, 0x476a78\n\t"
      "jne .LFUN_00157010_57\n\t"
      ".LFUN_00157010_56:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_57:\n\t"
      "pushl $0x476a7c\n\t"
      "pushl %%esi\n\t"
      "pushl $5\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x80\n\t"
      "pushl $0x80\n\t"
      "call *%[c1e6ae0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_58\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_58\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_59\n\t"
      ".LFUN_00157010_58:\n\t"
      "pushl $0x29e8b0\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_59:\n\t"
      "movl 0x476a7c, %%eax\n\t"
      "pushl $0x476a80\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1edc20]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_60\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_60\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_61\n\t"
      ".LFUN_00157010_60:\n\t"
      "pushl $0x29e840\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_61:\n\t"
      "cmpl %%esi, 0x476a7c\n\t"
      "je .LFUN_00157010_62\n\t"
      "cmpl %%esi, 0x476a80\n\t"
      "jne .LFUN_00157010_63\n\t"
      ".LFUN_00157010_62:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_63:\n\t"
      "pushl $0x476a84\n\t"
      "pushl %%esi\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x40\n\t"
      "pushl $0x40\n\t"
      "call *%[c1e6ae0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_64\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_64\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_65\n\t"
      ".LFUN_00157010_64:\n\t"
      "pushl $0x29e768\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_65:\n\t"
      "movl 0x476a84, %%ecx\n\t"
      "pushl $0x476a88\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1edc20]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_66\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_66\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_67\n\t"
      ".LFUN_00157010_66:\n\t"
      "pushl $0x29e6f8\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_67:\n\t"
      "cmpl %%esi, 0x476a84\n\t"
      "je .LFUN_00157010_68\n\t"
      "cmpl %%esi, 0x476a88\n\t"
      "jne .LFUN_00157010_69\n\t"
      ".LFUN_00157010_68:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_69:\n\t"
      "pushl $0x476a8c\n\t"
      "pushl %%esi\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x40\n\t"
      "pushl $0x40\n\t"
      "call *%[c1e6ae0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_70\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_70\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_71\n\t"
      ".LFUN_00157010_70:\n\t"
      "pushl $0x29e620\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_71:\n\t"
      "movl 0x476a8c, %%edx\n\t"
      "pushl $0x476a90\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1edc20]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_72\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00157010_72\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_73\n\t"
      ".LFUN_00157010_72:\n\t"
      "pushl $0x29e5a8\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00157010_73:\n\t"
      "cmpl %%esi, 0x476a8c\n\t"
      "je .LFUN_00157010_74\n\t"
      "cmpl %%esi, 0x476a90\n\t"
      "jne .LFUN_00157010_75\n\t"
      ".LFUN_00157010_74:\n\t"
      "pushl $0x29e578\n\t"
      "pushl $2\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00157010_77\n\t"
      ".LFUN_00157010_75:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00157010_76\n\t"
      "pushl $0x29e578\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00157010_77\n\t"
      ".LFUN_00157010_76:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1eb590]\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c1ea290]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x203, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "movl %%edi, 0x1fb798\n\t"
      "call *%[c1e9350]\n\t"
      "pushl %%esi\n\t"
      "movl $0x203, 0x1fb77c\n\t"
      "call *%[c1e98e0]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x40338, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl %%edi, 0x1fb7dc\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x204, %%edx\n\t"
      "movl $0x4033c, %%ecx\n\t"
      "movl %%esi, 0x1fb788\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40340, %%ecx\n\t"
      "movl $0x204, 0x1fb780\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl %%esi, 0x1fb78c\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x40344, %%ecx\n\t"
      "movl %%esi, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40348, %%ecx\n\t"
      "movl %%edi, 0x1fb790\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x8006, %%edx\n\t"
      "movl $0x40350, %%ecx\n\t"
      "movl %%esi, 0x1fb794\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x52, %%ecx\n\t"
      "movl $0x8006, 0x1fb7c0\n\t"
      "call *%[c1e9380]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x5c, %%ecx\n\t"
      "call *%[c1e9380]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x5d, %%ecx\n\t"
      "call *%[c1e9380]\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e9ae0]\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9ae0]\n\t"
      "pushl $2\n\t"
      "pushl $2\n\t"
      "call *%[c1e9ae0]\n\t"
      "pushl $3\n\t"
      "pushl $3\n\t"
      "call *%[c1e9ae0]\n\t"
      "pushl $5\n\t"
      "call *%[c1e72a0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e72c0]\n\t"
      ".LFUN_00157010_77:\n\t"
      "call *%[c156e00]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c1824e0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c15e800]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c184260]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c178850]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c17df80]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c17eb50]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c183650]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c15c2d0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c16f6c0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "call *%[c1659a0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00157010_78\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00157010_79\n\t"
      ".LFUN_00157010_78:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00157010_79:\n\t"
      "call *%[c17d910]\n\t"
      "call *%[c1bf080]\n\t"
      "call *%[c17e010]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00157010_80\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movb $1, 0x325650\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00157010_80:\n\t"
      "pushl $0x29e54c\n\t"
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
      :
      : [c1edea0] "m"(b157010_c1edea0), [c1eeab0] "m"(b157010_c1eeab0), [c8f390] "m"(b157010_c8f390), [memset] "m"(b157010_memset), [c1edec0] "m"(b157010_c1edec0), [c167ff0] "m"(b157010_c167ff0), [c1e69f0] "m"(b157010_c1e69f0), [c156d80] "m"(b157010_c156d80), [c1ef170] "m"(b157010_c1ef170), [c1eefe0] "m"(b157010_c1eefe0), [c8e0b0] "m"(b157010_c8e0b0), [c1e88a0] "m"(b157010_c1e88a0), [c1e7d50] "m"(b157010_c1e7d50), [c1e8270] "m"(b157010_c1e8270), [c8ee60] "m"(b157010_c8ee60), [c1e6ae0] "m"(b157010_c1e6ae0), [c1edc20] "m"(b157010_c1edc20), [c1eb590] "m"(b157010_c1eb590), [c1ea290] "m"(b157010_c1ea290), [c1e9350] "m"(b157010_c1e9350), [c1e98e0] "m"(b157010_c1e98e0), [c1e9380] "m"(b157010_c1e9380), [c1e9ae0] "m"(b157010_c1e9ae0), [c1e72a0] "m"(b157010_c1e72a0), [c1e72c0] "m"(b157010_c1e72c0), [c156e00] "m"(b157010_c156e00), [c1824e0] "m"(b157010_c1824e0), [c15e800] "m"(b157010_c15e800), [c184260] "m"(b157010_c184260), [c178850] "m"(b157010_c178850), [c17df80] "m"(b157010_c17df80), [c17eb50] "m"(b157010_c17eb50), [c183650] "m"(b157010_c183650), [c15c2d0] "m"(b157010_c15c2d0), [c16f6c0] "m"(b157010_c16f6c0), [c1659a0] "m"(b157010_c1659a0), [c17d910] "m"(b157010_c17d910), [c1bf080] "m"(b157010_c1bf080), [c17e010] "m"(b157010_c17e010)
      : "memory");
}
#else
#error "FUN_00157010: clang naked draft required"
#endif

