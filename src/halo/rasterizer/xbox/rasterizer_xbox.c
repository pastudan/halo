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

/* 0x155350 */
void FUN_00155350(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_Present((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_GetBackBuffer(0, ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x155380 */
void FUN_00155380(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_CreateTexture(eax, edx, ecx, eax, edx, ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1553a0 */
void FUN_001553a0(void)
{
  D3DDevice_CreateVolumeTexture();
}

/* 0x1553d0 */
void FUN_001553d0(void)
{
  D3DDevice_CreateCubeTexture();
}

/* 0x155560 */
void FUN_00155560(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_Clear(edx, (void *)(uintptr_t)ecx, eax, edx, 0.0f, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x155880 */
void FUN_00155880(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp edx, 0x16 -> jge 0x1558b0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1558c1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1558d2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1558e3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1558f0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShader(eax);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetShaderConstantMode();
  D3DDevice_SetStreamSource(edx, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetIndices();
  D3DDevice_SetPixelShaderProgram((void *)(uintptr_t)eax);
  D3DDevice_SetVerticalBlankCallback();
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)ecx;
  (void)edx;
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

/* 0x1559d0 */
void _rasterizer_windows_begin(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1559f9 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1331, 0);
  system_exit(0);

  (void)eax;
}

/* 0x155a00 */
void _rasterizer_window_get_fog(void)
{
  int edi = 0;

  /* test edi, edi -> jne 0x155a2c */
  display_assert((char *)0x0029dc54, (char *)0x0029dc0c, 1440, 0);
  system_exit(0);

  (void)edi;
}

/* 0x155a40 */
void _rasterizer_windows_end(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x155a69 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1629, 0);
  system_exit(0);

  (void)eax;
}

/* 0x155a70 */
void _rasterizer_frame_end(void)
{
  int ebx = 0;
  int esi = 0;

  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1648, 0);
  system_exit(0);
  FUN_0016FDD0();
  FUN_0017ff50();
  D3DDevice_SetTexture(esi, (void *)0);
  /* test (char)ebx, (char)ebx -> je 0x155ac0 */
  FUN_00167ff0(0, (char *)0x0029dcfc);
  D3DDevice_SetStreamSource(esi, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> je 0x155af2 */
  FUN_00167ff0(0, (char *)0x0029dcb8);
  D3DDevice_SetIndices();
  FUN_00167ff0(0, (char *)0x0029dc80);
  error(0, (char *)0x0029dc58);
  D3DTexture_GetSurfaceLevel();

  (void)ebx;
  (void)esi;
}

/* 0x155b60 */
void FUN_00155b60(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DTexture_LockRect((void *)(uintptr_t)ecx, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x155b90 */
void _rasterizer_dispose(void)
{
  int eax = 0;

  rasterizer_memory_pool_delete();
  FUN_0015e9e0();
  FUN_00184690();
  FUN_00178ab0();
  FUN_0017e040();
  FUN_0017ff60();
  rasterizer_text_cache_dispose();
  FUN_0015c680();
  FUN_0016fec0();
  FUN_00165a10();
  FUN_0017d990();
  texture_cache_delete();
  /* test eax, eax -> je 0x155be4 */
  D3DDevice_Release();
  /* mem[0x00476ab0] = 0 */
  /* test eax, eax -> je 0x155bf7 */
  /* mem[0x00476a50] = 0 */

  (void)eax;
}

/* 0x155c10 */
void FUN_00155c10(void)
{
  D3DDevice_SetVerticalBlankCallback();
}

/* 0x155c20 */
void rasterizer_set_texture_bitmap_data(int stage, void *bitmap_data)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, 4 -> jl 0x155c54 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 1935, 0);
  system_exit(0);
  /* test edi, edi -> je 0x155c84 */
  profile_texture_start();
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)edi, 0, 0);
  profile_texture_end();
  D3DDevice_SetTexture(eax, (void *)(uintptr_t)edi);
  display_assert((char *)0x0029dd68, (char *)0x0029dc0c, 1943, 0);
  error(0, (char *)0x0029dd38);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x155cc0 */
void FUN_00155cc0(void)
{
  D3DVolumeTexture_LockBox();
}

/* 0x155cf0 */
void rasterizer_set_texture_direct(int stage, int bitmap_tag_index, int frame_index)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0x155d06 */
  /* cmp (int16_t)edi, 4 -> jl 0x155d26 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 1958, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x155d69 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x155d69 */
  FUN_00076ff0(0, 0);
  /* test eax, eax -> je 0x155d69 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  display_assert((char *)0x0029ddd8, (char *)0x0029dc0c, 1982, 0);
  error(0, (char *)0x0029dd38);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x155da0 */
void rasterizer_set_texture_direct_non_blocking(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0x155db6 */
  /* cmp (int16_t)edi, 4 -> jl 0x155dd6 */
  display_assert((char *)0x0029dda4, (char *)0x0029dc0c, 2003, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x155e33 */
  tag_get('mtib', 0);
  /* test ecx, ecx -> jle 0x155e33 */
  FUN_00076ff0(0, 0);
  /* test esi, esi -> je 0x155e33 */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)esi, 0, 0);
  /* test eax, eax -> je 0x155e2c */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  display_assert((char *)0x0029de10, (char *)0x0029dc0c, 2035, 0);
  error(0, (char *)0x0029dd38);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x155e80 */
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

/* 0x156070 */
void FUN_00156070(void)
{
  D3DCubeTexture_LockRect();
}

/* 0x1560a0 */
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

/* 0x156250 */
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
  D3DPalette_Lock();

  (void)eax;
  (void)esi;
  (void)ebp;
}

/* 0x156440 */
void rasterizer_set_vertex_shader(void)
{
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jge 0x15646d */
  display_assert((char *)0x0029e084, (char *)0x0029dc0c, 2613, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x43 -> jl 0x156493 */
  display_assert((char *)0x0029e054, (char *)0x0029dc0c, 2614, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edi, word ptr [0x325164] -> je 0x156505 */
  /* cmp ecx, -1 -> je 0x1564d8 */
  D3DDevice_SetVertexShader(ecx);
  /* mem[0x005a5558] = edx */
  error(0, (char *)0x0029e02c);
  /* relift: relift: mov word ptr [0x325164], (int16_t)edi */
  error(0, (char *)0x0029dffc);

  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x156510 */
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
  D3DDevice_SetRenderState_PSTextureModes();
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
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  /* test (char)ebx, (char)ebx -> jne 0x15667e */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x15668b */
  D3DDevice_SetRenderStateNotInline();
  /* test (char)eax, (char)eax -> jne 0x156699 */
  /* relift: cmp word ptr [ebp - 4], 0 -> jne 0x1566a6 */
  D3DDevice_SetRenderStateNotInline();
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

/* 0x156710 */
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

/* 0x156850 */
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

/* 0x1569f0 */
void FUN_001569f0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x156a1b */
  display_assert((char *)0x0029e178, (char *)0x0029dc0c, 2874, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x156a5f */
  csmemset((void *)(uintptr_t)edx, 0, 0);
  D3DSurface_GetDesc((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x156a90 */
void FUN_00156a90(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DSurface_LockRect((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x156ab0 */
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
  FUN_001569f0();
  /* cmp (int16_t)esi, 2 -> jl 0x156bb0 */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 11);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x156c30 */
void rasterizer_set_frustum_z(float near_z, float far_z)
{
  int eax = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x156c62 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 2967, 0);
  system_exit(0);
  render_camera_hack_frustum_z();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x325168] */

  (void)eax;
  (void)edx;
}

/* 0x156d80 */
void SetupSmartStates(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x156e00 */
void FUN_00156e00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x156e2f */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 239, 0);
  system_exit(0);
  D3DDevice_CreateTexture(0, 0, 0, 0, 0, 0, (void *)(uintptr_t)eax);
  /* test eax, eax -> jl 0x156e4d */
  FUN_00167ff0(0, (char *)0x0029e4b8);
  D3DDevice_CreateVolumeTexture();
  /* test (char)ebx, (char)ebx -> je 0x156e80 */
  /* test eax, eax -> jl 0x156e80 */
  FUN_00167ff0(0, (char *)0x0029e418);
  D3DDevice_CreateCubeTexture();
  /* test (char)ebx, (char)ebx -> je 0x156eab */
  /* test eax, eax -> jge 0x156ebe */
  FUN_00167ff0(0, (char *)0x0029e380);
  /* test eax, eax -> je 0x156fc5 */
  /* test ecx, ecx -> je 0x156fc5 */
  /* test ecx, ecx -> je 0x156fc5 */
  D3DTexture_LockRect((void *)(uintptr_t)eax, 0, (void *)(uintptr_t)ecx, (void *)0, 0);
  D3DVolumeTexture_LockBox();
  D3DCubeTexture_LockRect();
  /* test (char)ebx, (char)ebx -> je 0x156f6f */
  FUN_00167ff0(0, (char *)0x0029e300);
  /* test (char)ebx, (char)ebx -> je 0x156fa4 */
  FUN_00167ff0(0, (char *)0x0029e298);
  display_assert((char *)0x0029e258, (char *)0x0029dc0c, 311, 0);
  system_exit(0);
  /* mem[0x003256a4] = eax */
  /* mem[0x003256a8] = ecx */
  /* mem[0x003256ac] = edx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x157010 */
void FUN_00157010(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (int16_t)ecx, word ptr [0x325688] */
  /* relift: relift: mov word ptr [0x325688], (int16_t)ecx */
  /* relift: relift: mov (int16_t)eax, word ptr [0x32568a] */
  /* cmp (int16_t)eax, (int16_t)esi -> jne 0x157047 */
  /* relift: relift: mov word ptr [0x32568a], (int16_t)eax */
  D3D_SetPushBufferSize();
  /* relift: FUN_001eeab0(0); */
  /* mem[0x00476a50] = eax */
  error(0, (char *)0x0029dbd4);
  /* relift: relift: mov word ptr [0x325654], (int16_t)esi */
  /* relift: relift: mov word ptr [0x325656], (int16_t)esi */
  /* relift: relift: mov word ptr [0x32565a], 0x280 */
  /* relift: relift: mov word ptr [0x325658], 0x1e0 */
  /* relift: relift: mov word ptr [0x32565e], 0x30 */
  /* relift: relift: mov word ptr [0x325662], 0x250 */
  /* relift: relift: mov word ptr [0x32565c], 0x24 */
  /* relift: relift: mov word ptr [0x325660], 0x1bc */
  /* mem[0x00325668] = edi */
  /* mem[0x0032566c] = esi */
  csmemset((void *)(uintptr_t)edx, 0, 52);
  /* relift: relift: mov dl, byte ptr [0x32568c] */
  /* relift: relift: mov (int16_t)ecx, word ptr [0x325690] */
  /* cmp eax, 0x1e -> je 0x15717c */
  /* cmp eax, 0x3c -> je 0x157170 */
  /* cmp (int16_t)ecx, (int16_t)esi -> je 0x157164 */
  error(0, (char *)0x0029efc8);
  /* relift: relift: mov word ptr [0x325690], (int16_t)esi */
  /* relift: relift: mov byte ptr [0x31fa96], 1 */
  /* relift: relift: mov byte ptr [0x31fa96], 1 */
  /* relift: relift: mov byte ptr [0x31fa96], 1 */
  /* relift: relift: mov byte ptr [0x31fa96], 0 */
  Direct3D_CreateDevice();
  /* cmp eax, esi -> jl 0x1571b5 */
  FUN_00167ff0(0, (char *)0x0029db10);
  /* relift: cmp dword ptr [0x476ab0], esi -> jne 0x1571d1 */
  /* test (char)ebx, (char)ebx -> jne 0x1571ef */
  /* mem[0x00476ab0] = esi */
  error(0, (char *)0x0029dae8);
  D3DDevice_GetDeviceCaps((void *)0x005a59e0);
  SetupSmartStates();
  D3DDevice_CreatePalette();
  /* cmp eax, esi -> jl 0x157214 */
  FUN_00167ff0(0, (char *)0x0029ef78);
  D3DPalette_Lock();
  /* test (char)ebx, (char)ebx -> je 0x15723d */
  FUN_00167ff0(0, (char *)0x0029ef3c);
  csmemcpy((void *)(uintptr_t)edx, (void *)0x002ee0a0, 1024);
  /* test (char)ebx, (char)ebx -> je 0x15726b */
  FUN_00167ff0(0, (char *)0x0029ef14);
  D3DDevice_SetPalette();
  /* test (char)ebx, (char)ebx -> je 0x15728f */
  FUN_00167ff0(0, (char *)0x0029eed4);
  D3DDevice_SetPalette();
  /* test (char)ebx, (char)ebx -> je 0x1572b4 */
  FUN_00167ff0(0, (char *)0x0029ee94);
  D3DDevice_SetPalette();
  /* test (char)ebx, (char)ebx -> je 0x1572da */
  FUN_00167ff0(0, (char *)0x0029ee54);
  D3DDevice_SetPalette();
  /* test (char)ebx, (char)ebx -> jne 0x15730e */
  FUN_00167ff0(0, (char *)0x0029ee14);
  D3DDevice_GetBackBuffer(0, esi, (void *)0x00476a5c);
  D3DDevice_GetDepthStencilSurface((void *)0x00476a60);
  /* cmp eax, esi -> jl 0x15732e */
  FUN_00167ff0(0, (char *)0x0029edb0);
  debug_malloc(20, esi, (char *)0x0029dc0c, 562);
  /* mem[0x00476a54] = eax */
  debug_malloc(20, esi, (char *)0x0029dc0c, 563);
  /* mem[0x00476a58] = eax */
  /* cmp eax, esi -> je 0x1573c8 */
  debug_malloc(24, esi, (char *)0x0029dc0c, 610);
  /* mem[0x00476aac] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
