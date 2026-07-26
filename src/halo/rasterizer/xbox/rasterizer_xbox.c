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

/* rasterizer_set_texture (0x155e80) — XBE naked draft (batch 312). */
#if defined(__clang__)
static void (*const b155e80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b155e80_exitfn)(int) = system_exit;
static void *(*const b155e80_tag)(int, int) = tag_get;
static void * (*const b155e80_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static void (*const b155e80_c155c20)(int stage, void *bitmap_data) = rasterizer_set_texture_bitmap_data;
static const char * (*const b155e80_c7c750)(short type) = bitmap_type_get_string;
static void (*const b155e80_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_set_texture(int stage __attribute__((unused)), int a2 __attribute__((unused)), int bitmap_type __attribute__((unused)), int bitmap_index __attribute__((unused)), int frame_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jl .Lrasterizer_set_texture_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lrasterizer_set_texture_2\n\t"
      ".Lrasterizer_set_texture_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x80a\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dda4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lrasterizer_set_texture_3\n\t"
      "cmpw $3, %%di\n\t"
      "jl .Lrasterizer_set_texture_4\n\t"
      ".Lrasterizer_set_texture_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x80b\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x264a4c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_4:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lrasterizer_set_texture_5\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .Lrasterizer_set_texture_6\n\t"
      ".Lrasterizer_set_texture_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x80c\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29df10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_6:\n\t"
      "movb 0x3256e1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_set_texture_7\n\t"
      "cmpw $3, %%bx\n\t"
      "je .Lrasterizer_set_texture_9\n\t"
      ".Lrasterizer_set_texture_7:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrasterizer_set_texture_9\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl 0x60(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lrasterizer_set_texture_9\n\t"
      "movswl 0x18(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c76ff0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%di, 0xa(%%esi)\n\t"
      "jne .Lrasterizer_set_texture_8\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c155c20]\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%al\n\t"
      "negb %%al\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x476a4c\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x476a4e\n\t"
      "popl %%ebx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x476a4c, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_8:\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c750]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c750]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29ded0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lrasterizer_set_texture_9:\n\t"
      "movl 0x476204, %%edx\n\t"
      "movswl %%di, %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl 0xb8(%%ecx,%%edx,1), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lrasterizer_set_texture_10\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c76ff0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrasterizer_set_texture_10\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c155c20]\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "negb %%al\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x476a4c\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x476a4e\n\t"
      "popl %%ebx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x476a4c, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x845\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29de9c\n\t"
      "call *%[assert]\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29de58\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x24, %%esp\n\t"
      "negb %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x476a4c, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b155e80_assert), [exitfn] "m"(b155e80_exitfn), [tag] "m"(b155e80_tag), [c76ff0] "m"(b155e80_c76ff0), [c155c20] "m"(b155e80_c155c20), [c7c750] "m"(b155e80_c7c750), [c8f390] "m"(b155e80_c8f390)
      : "memory");
}
#else
#error "rasterizer_set_texture: clang naked draft required"
#endif


/* 0x156070 */
void FUN_00156070(void)
{
  D3DCubeTexture_LockRect();
}

/* rasterizer_set_texture_non_blocking (0x1560a0) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b1560a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1560a0_exitfn)(int) = system_exit;
static void *(*const b1560a0_tag)(int, int) = tag_get;
static void * (*const b1560a0_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static void *(*const b1560a0_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static const char * (*const b1560a0_c7c750)(short type) = bitmap_type_get_string;
static void (*const b1560a0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1560a0_c155c20)(int stage, void *bitmap_data) = rasterizer_set_texture_bitmap_data;

__attribute__((naked, noinline))
void rasterizer_set_texture_non_blocking(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lrasterizer_set_texture_non_blocking_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lrasterizer_set_texture_non_blocking_2\n\t"
      ".Lrasterizer_set_texture_non_blocking_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x85e\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dda4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_non_blocking_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lrasterizer_set_texture_non_blocking_3\n\t"
      "cmpw $3, %%di\n\t"
      "jl .Lrasterizer_set_texture_non_blocking_4\n\t"
      ".Lrasterizer_set_texture_non_blocking_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x85f\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x264a4c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_non_blocking_4:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lrasterizer_set_texture_non_blocking_5\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .Lrasterizer_set_texture_non_blocking_6\n\t"
      ".Lrasterizer_set_texture_non_blocking_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x860\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29df10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_non_blocking_6:\n\t"
      "movb 0x3256e1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_set_texture_non_blocking_7\n\t"
      "cmpw $3, %%bx\n\t"
      "je .Lrasterizer_set_texture_non_blocking_8\n\t"
      ".Lrasterizer_set_texture_non_blocking_7:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrasterizer_set_texture_non_blocking_8\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl 0x60(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lrasterizer_set_texture_non_blocking_8\n\t"
      "movswl 0x18(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c76ff0]\n\t"
      "pushl $1\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[xtex]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_set_texture_non_blocking_10\n\t"
      "cmpw %%di, 0xa(%%esi)\n\t"
      "je .Lrasterizer_set_texture_non_blocking_9\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c750]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c750]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29ded0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lrasterizer_set_texture_non_blocking_8:\n\t"
      "movl 0x476204, %%edx\n\t"
      "movswl %%di, %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl 0xb8(%%ecx,%%edx,1), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lrasterizer_set_texture_non_blocking_11\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c76ff0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrasterizer_set_texture_non_blocking_11\n\t"
      ".Lrasterizer_set_texture_non_blocking_9:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c155c20]\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x476a48\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x476a4a\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_non_blocking_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_non_blocking_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x8a2\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29df3c\n\t"
      "call *%[assert]\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29de58\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x24, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1560a0_assert), [exitfn] "m"(b1560a0_exitfn), [tag] "m"(b1560a0_tag), [c76ff0] "m"(b1560a0_c76ff0), [xtex] "m"(b1560a0_xtex), [c7c750] "m"(b1560a0_c7c750), [c8f390] "m"(b1560a0_c8f390), [c155c20] "m"(b1560a0_c155c20)
      : "memory");
}
#else
#error "rasterizer_set_texture_non_blocking: clang naked draft required"
#endif


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

/* FUN_00156e00 (0x156e00) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b156e00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156e00_exitfn)(int) = system_exit;
static void __stdcall (*const b156e00_c1e6ae0)(uint32_t width, uint32_t height, uint32_t levels, uint32_t usage, uint32_t format, uint32_t pool, void *out_texture) = (void *)D3DDevice_CreateTexture;
static void (*const b156e00_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b156e00_c1e6b10)(void) = D3DDevice_CreateVolumeTexture;
static void (*const b156e00_c1e6b40)(void) = D3DDevice_CreateCubeTexture;
static void __stdcall (*const b156e00_c1edc70)(void *texture, unsigned int level, void *locked_rect, void *rect, unsigned int flags) = (void *)D3DTexture_LockRect;
static void (*const b156e00_c1edd80)(void) = D3DVolumeTexture_LockBox;
static void (*const b156e00_c1edd10)(void) = D3DCubeTexture_LockRect;

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
