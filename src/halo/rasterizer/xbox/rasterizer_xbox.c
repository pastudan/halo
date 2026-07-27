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



/* _rasterizer_frame_end (0x155a70) — XBE naked draft (batch 335). */
#if defined(__clang__)
static void (*const b155a70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b155a70_exitfn)(int) = system_exit;
static void (*const b155a70_c16fdd0)(void) = (void *)FUN_0016FDD0;
static void (*const b155a70_c17ff50)(void) = (void *)FUN_0017ff50;
static void __stdcall (*const b155a70_c1e8700)(uint32_t stage, void *texture) = (void *)D3DDevice_SetTexture;
static void (*const b155a70_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void __stdcall (*const b155a70_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b155a70_c1e8920)(void) = (void *)D3DDevice_SetIndices;
static void (*const b155a70_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void _rasterizer_frame_end(void)
{
  __asm__ volatile(
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "jne .L_rasterizer_frame_end_1\n\t"
      "pushl $1\n\t"
      "pushl $0x670\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".L_rasterizer_frame_end_1:\n\t"
      "call *%[c16fdd0]\n\t"
      "call *%[c17ff50]\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $4, %%edi\n\t"
      "nop\n\t"
      ".L_rasterizer_frame_end_2:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e8700]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .L_rasterizer_frame_end_3\n\t"
      "movb $1, %%bl\n\t"
      "jmp .L_rasterizer_frame_end_4\n\t"
      ".L_rasterizer_frame_end_3:\n\t"
      "pushl $0x29dcfc\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".L_rasterizer_frame_end_4:\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "jne .L_rasterizer_frame_end_2\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x10, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".L_rasterizer_frame_end_5:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1eb2d0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .L_rasterizer_frame_end_6\n\t"
      "movb $1, %%bl\n\t"
      "jmp .L_rasterizer_frame_end_7\n\t"
      ".L_rasterizer_frame_end_6:\n\t"
      "pushl $0x29dcb8\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".L_rasterizer_frame_end_7:\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "jne .L_rasterizer_frame_end_5\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c1e8920]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%ebx\n\t"
      "jne .L_rasterizer_frame_end_8\n\t"
      "pushl $0x29dc80\n\t"
      "pushl $0\n\t"
      "call *%[c167ff0]\n\t"
      "pushl $0x29dc58\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".L_rasterizer_frame_end_8:\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b155a70_assert), [exitfn] "m"(b155a70_exitfn), [c16fdd0] "m"(b155a70_c16fdd0), [c17ff50] "m"(b155a70_c17ff50), [c1e8700] "m"(b155a70_c1e8700), [c167ff0] "m"(b155a70_c167ff0), [c1eb2d0] "m"(b155a70_c1eb2d0), [c1e8920] "m"(b155a70_c1e8920), [c8f390] "m"(b155a70_c8f390)
      : "memory");
}
#else
#error "_rasterizer_frame_end: clang naked draft required"
#endif


/* FUN_00155b60 (0x155b60) — readable C lift. */
int FUN_00155b60(int a, int b)
{
  D3DTexture_LockRect((void *)(unsigned)a, (unsigned int)b, 0, 0, 0);
  return 0;
}

/* _rasterizer_dispose (0x155b90) — XBE naked draft (batch 383). */
#if defined(__clang__)
static void (*const b155b90_c1825e0)(void) = (void *)rasterizer_memory_pool_delete;
static void (*const b155b90_c15e9e0)(void) = (void *)FUN_0015e9e0;
static void (*const b155b90_c184690)(void) = (void *)FUN_00184690;
static void (*const b155b90_c178ab0)(void) = (void *)FUN_00178ab0;
static void (*const b155b90_c17e040)(void) = (void *)FUN_0017e040;
static void (*const b155b90_c17ff60)(void) = (void *)FUN_0017ff60;
static void (*const b155b90_c183720)(void) = (void *)rasterizer_text_cache_dispose;
static void (*const b155b90_c15c680)(void) = (void *)FUN_0015c680;
static void (*const b155b90_c16fec0)(void) = (void *)FUN_0016fec0;
static void (*const b155b90_c165a10)(void) = (void *)FUN_00165a10;
static void (*const b155b90_c17d990)(void) = (void *)FUN_0017d990;
static void (*const b155b90_c1be920)(void) = (void *)texture_cache_delete;
static void (*const b155b90_c1e6f50)(void) = (void *)D3DDevice_Release;

__attribute__((naked, noinline))
void _rasterizer_dispose(void)
{
  __asm__ volatile(
      "call *%[c1825e0]\n\t"
      "call *%[c15e9e0]\n\t"
      "call *%[c184690]\n\t"
      "call *%[c178ab0]\n\t"
      "call *%[c17e040]\n\t"
      "call *%[c17ff60]\n\t"
      "call *%[c183720]\n\t"
      "call *%[c15c680]\n\t"
      "call *%[c16fec0]\n\t"
      "call *%[c165a10]\n\t"
      "call *%[c17d990]\n\t"
      "call *%[c1be920]\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_rasterizer_dispose_1\n\t"
      "call *%[c1e6f50]\n\t"
      "movl $0, 0x476ab0\n\t"
      ".L_rasterizer_dispose_1:\n\t"
      "movl 0x476a50, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_rasterizer_dispose_2\n\t"
      "movl $0, 0x476a50\n\t"
      ".L_rasterizer_dispose_2:\n\t"
      "ret\n\t"
      :
      : [c1825e0] "m"(b155b90_c1825e0), [c15e9e0] "m"(b155b90_c15e9e0), [c184690] "m"(b155b90_c184690), [c178ab0] "m"(b155b90_c178ab0), [c17e040] "m"(b155b90_c17e040), [c17ff60] "m"(b155b90_c17ff60), [c183720] "m"(b155b90_c183720), [c15c680] "m"(b155b90_c15c680), [c16fec0] "m"(b155b90_c16fec0), [c165a10] "m"(b155b90_c165a10), [c17d990] "m"(b155b90_c17d990), [c1be920] "m"(b155b90_c1be920), [c1e6f50] "m"(b155b90_c1e6f50)
      : "memory");
}
#else
#error "_rasterizer_dispose: clang naked draft required"
#endif


/* FUN_00155c10 (0x155c10) — readable C lift. */
void FUN_00155c10(void *callback)
{
  ((void (__stdcall *)(void *))D3DDevice_SetVerticalBlankCallback)(callback);
}



/* rasterizer_set_texture_bitmap_data (0x155c20) — XBE naked draft (batch 345). */
#if defined(__clang__)
static void (*const b155c20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b155c20_exitfn)(int) = system_exit;
static void (*const b155c20_c916e0)(void) = (void *)profile_texture_start;
static void *(*const b155c20_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static void (*const b155c20_c91710)(void) = (void *)profile_texture_end;
static void __stdcall (*const b155c20_c1e8700)(uint32_t stage, void *texture) = (void *)D3DDevice_SetTexture;
static void (*const b155c20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_set_texture_bitmap_data(int stage __attribute__((unused)), void *bitmap_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "jl .Lrasterizer_set_texture_bitmap_data_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lrasterizer_set_texture_bitmap_data_2\n\t"
      ".Lrasterizer_set_texture_bitmap_data_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x78f\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dda4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_bitmap_data_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lrasterizer_set_texture_bitmap_data_3\n\t"
      "call *%[c916e0]\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[xtex]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c91710]\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e8700]\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_bitmap_data_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x797\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dd68\n\t"
      "call *%[assert]\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29dd38\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b155c20_assert), [exitfn] "m"(b155c20_exitfn), [c916e0] "m"(b155c20_c916e0), [xtex] "m"(b155c20_xtex), [c91710] "m"(b155c20_c91710), [c1e8700] "m"(b155c20_c1e8700), [c8f390] "m"(b155c20_c8f390)
      : "memory");
}
#else
#error "rasterizer_set_texture_bitmap_data: clang naked draft required"
#endif


/* FUN_00155cc0 (0x155cc0) — readable C lift. */
int FUN_00155cc0(int a, int b)
{
  ((void (__stdcall *)(int, int, int, int, int))D3DVolumeTexture_LockBox)(a, b, 0, 0, 0);
  return 0;
}

/* rasterizer_set_texture_direct (0x155cf0) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void (*const b155cf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b155cf0_exitfn)(int) = system_exit;
static void *(*const b155cf0_tag)(int, int) = tag_get;
static void * (*const b155cf0_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static void (*const b155cf0_c155c20)(int stage, void *bitmap_data) = rasterizer_set_texture_bitmap_data;
static void (*const b155cf0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_set_texture_direct(int stage __attribute__((unused)), int bitmap_tag_index __attribute__((unused)), int frame_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lrasterizer_set_texture_direct_1\n\t"
      "cmpw $4, %%di\n\t"
      "jl .Lrasterizer_set_texture_direct_2\n\t"
      ".Lrasterizer_set_texture_direct_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x7a6\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dda4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_direct_2:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrasterizer_set_texture_direct_3\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl 0x60(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lrasterizer_set_texture_direct_3\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c76ff0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_set_texture_direct_3\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c155c20]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_direct_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7be\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29ddd8\n\t"
      "call *%[assert]\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29dd38\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b155cf0_assert), [exitfn] "m"(b155cf0_exitfn), [tag] "m"(b155cf0_tag), [c76ff0] "m"(b155cf0_c76ff0), [c155c20] "m"(b155cf0_c155c20), [c8f390] "m"(b155cf0_c8f390)
      : "memory");
}
#else
#error "rasterizer_set_texture_direct: clang naked draft required"
#endif


/* rasterizer_set_texture_direct_non_blocking (0x155da0) — XBE naked draft (batch 335). */
#if defined(__clang__)
static void (*const b155da0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b155da0_exitfn)(int) = system_exit;
static void *(*const b155da0_tag)(int, int) = tag_get;
static void * (*const b155da0_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static void *(*const b155da0_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static void (*const b155da0_c155c20)(int stage, void *bitmap_data) = rasterizer_set_texture_bitmap_data;
static void (*const b155da0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_set_texture_direct_non_blocking(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lrasterizer_set_texture_direct_non_blocking_1\n\t"
      "cmpw $4, %%di\n\t"
      "jl .Lrasterizer_set_texture_direct_non_blocking_2\n\t"
      ".Lrasterizer_set_texture_direct_non_blocking_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x7d3\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dda4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_texture_direct_non_blocking_2:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrasterizer_set_texture_direct_non_blocking_4\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl 0x60(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lrasterizer_set_texture_direct_non_blocking_4\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c76ff0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrasterizer_set_texture_direct_non_blocking_4\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[xtex]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_set_texture_direct_non_blocking_3\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c155c20]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_direct_non_blocking_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_texture_direct_non_blocking_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x7f3\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29de10\n\t"
      "call *%[assert]\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29dd38\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b155da0_assert), [exitfn] "m"(b155da0_exitfn), [tag] "m"(b155da0_tag), [c76ff0] "m"(b155da0_c76ff0), [xtex] "m"(b155da0_xtex), [c155c20] "m"(b155da0_c155c20), [c8f390] "m"(b155da0_c8f390)
      : "memory");
}
#else
#error "rasterizer_set_texture_direct_non_blocking: clang naked draft required"
#endif


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


/* FUN_00156070 (0x156070) — readable C lift. */
int FUN_00156070(int a, int b, int c)
{
  D3DCubeTexture_LockRect(a, b, c, 0, 0, 0);
  return 0;
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


/* rasterizer_get_target (0x156250) — XBE naked draft (batch 318). */
#if defined(__clang__)
static void (*const b156250_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156250_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void rasterizer_get_target(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl $6, %%eax\n\t"
      "ja .Lrasterizer_get_target_16\n\t"
      "jmp *.Lrasterizer_get_target_jt(,%%eax,4)\n\t"
      ".Lrasterizer_get_target_1:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "je .Lrasterizer_get_target_2\n\t"
      "pushl $1\n\t"
      "pushl $0x8b8\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_2:\n\t"
      "movl 0x476a5c, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_3:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "je .Lrasterizer_get_target_4\n\t"
      "pushl $1\n\t"
      "pushl $0x8bc\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_4:\n\t"
      "movl 0x476a6c, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_5:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "je .Lrasterizer_get_target_6\n\t"
      "pushl $1\n\t"
      "pushl $0x8c0\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_6:\n\t"
      "movl 0x476a78, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_7:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "je .Lrasterizer_get_target_8\n\t"
      "pushl $1\n\t"
      "pushl $0x8c4\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_8:\n\t"
      "movl 0x476a80, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_9:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "je .Lrasterizer_get_target_10\n\t"
      "pushl $1\n\t"
      "pushl $0x8c8\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_10:\n\t"
      "movl 0x476a88, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_11:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "je .Lrasterizer_get_target_12\n\t"
      "pushl $1\n\t"
      "pushl $0x8cc\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_12:\n\t"
      "movl 0x476a90, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_13:\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrasterizer_get_target_14\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lrasterizer_get_target_15\n\t"
      ".Lrasterizer_get_target_14:\n\t"
      "pushl $1\n\t"
      "pushl $0x8d0\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dfa0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_get_target_15:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x476a98(,%%eax,4), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_get_target_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x8d4\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29df78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lrasterizer_get_target_jt:\n\t"
      ".long .Lrasterizer_get_target_1\n\t"
      ".long .Lrasterizer_get_target_3\n\t"
      ".long .Lrasterizer_get_target_5\n\t"
      ".long .Lrasterizer_get_target_7\n\t"
      ".long .Lrasterizer_get_target_9\n\t"
      ".long .Lrasterizer_get_target_11\n\t"
      ".long .Lrasterizer_get_target_13\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b156250_assert), [exitfn] "m"(b156250_exitfn)
      : "memory");
}
#else
#error "rasterizer_get_target: clang naked draft required"
#endif


/* rasterizer_set_vertex_shader (0x156440) — XBE naked draft (batch 340). */
#if defined(__clang__)
static void (*const b156440_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156440_exitfn)(int) = system_exit;
static void __stdcall (*const b156440_c1eb7f0)(uint32_t shader) = (void *)D3DDevice_SetVertexShader;
static void (*const b156440_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_set_vertex_shader(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jge .Lrasterizer_set_vertex_shader_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa35\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e084\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_vertex_shader_1:\n\t"
      "cmpw $0x43, %%di\n\t"
      "jl .Lrasterizer_set_vertex_shader_2\n\t"
      "pushl $1\n\t"
      "pushl $0xa36\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e054\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_vertex_shader_2:\n\t"
      "cmpw 0x325164, %%di\n\t"
      "je .Lrasterizer_set_vertex_shader_5\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "movl 0x325208(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lrasterizer_set_vertex_shader_3\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1eb7f0]\n\t"
      "cmpw $0, 0x3256ba\n\t"
      "movb $1, %%al\n\t"
      "je .Lrasterizer_set_vertex_shader_4\n\t"
      "movl 0x5a5558, %%edx\n\t"
      "movl 0x32520c(%%esi), %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl %%edx, 0x5a5558\n\t"
      "jmp .Lrasterizer_set_vertex_shader_4\n\t"
      ".Lrasterizer_set_vertex_shader_3:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29e02c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      ".Lrasterizer_set_vertex_shader_4:\n\t"
      "testb %%al, %%al\n\t"
      "movw %%di, 0x325164\n\t"
      "popl %%esi\n\t"
      "jne .Lrasterizer_set_vertex_shader_5\n\t"
      "pushl $0x29dffc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_set_vertex_shader_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156440_assert), [exitfn] "m"(b156440_exitfn), [c1eb7f0] "m"(b156440_c1eb7f0), [c8f390] "m"(b156440_c8f390)
      : "memory");
}
#else
#error "rasterizer_set_vertex_shader: clang naked draft required"
#endif


/* rasterizer_set_pixel_shader (0x156510) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void (*const b156510_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156510_exitfn)(int) = system_exit;
static void (*const b156510_c1e9320)(void) = (void *)D3DDevice_SetRenderState_PSTextureModes;
static void (*const b156510_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void (*const b156510_c1e93a0)(void) = (void *)D3DDevice_SetRenderStateNotInline;
static void __stdcall (*const b156510_c1ec120)(void *program) = (void *)D3DDevice_SetPixelShaderProgram;

__attribute__((naked, noinline))
void rasterizer_set_pixel_shader(void *state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrasterizer_set_pixel_shader_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa5c\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e09c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_pixel_shader_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0xd4(%%esi), %%al\n\t"
      "andl $0xf, %%eax\n\t"
      "cmpw $6, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jge .Lrasterizer_set_pixel_shader_8\n\t"
      "movl 0xd4(%%esi), %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "shrl $0x10, %%eax\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, 0xb(%%ebp)\n\t"
      "movl 0xd8(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "shrl $0xc, %%ebx\n\t"
      "pushl %%eax\n\t"
      "andb $1, %%bl\n\t"
      "call *%[c1e9320]\n\t"
      "movl 0xd4(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x41e60, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb76c\n\t"
      "movl 0xe0(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x41e78, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb778\n\t"
      "movl 0xdc(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x41e74, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb774\n\t"
      "movl 0x20(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x40288, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb6b8\n\t"
      "movl 0x24(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x4028c, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb6bc\n\t"
      "movl 0xac(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x41e20, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb744\n\t"
      "movl 0xb0(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x41e24, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "movl %%edi, 0x1fb748\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lrasterizer_set_pixel_shader_7\n\t"
      "movl $0x22, %%edi\n\t"
      "addl $0x88, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrasterizer_set_pixel_shader_2:\n\t"
      "movl -0x88(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x22(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e93a0]\n\t"
      "movl -0x20(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e93a0]\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e93a0]\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0xb(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e93a0]\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lrasterizer_set_pixel_shader_3\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_set_pixel_shader_4\n\t"
      ".Lrasterizer_set_pixel_shader_3:\n\t"
      "movl -0x60(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e93a0]\n\t"
      ".Lrasterizer_set_pixel_shader_4:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_set_pixel_shader_5\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_set_pixel_shader_6\n\t"
      ".Lrasterizer_set_pixel_shader_5:\n\t"
      "movl -0x40(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e93a0]\n\t"
      ".Lrasterizer_set_pixel_shader_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "addl $4, %%esi\n\t"
      "incl %%edi\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .Lrasterizer_set_pixel_shader_2\n\t"
      ".Lrasterizer_set_pixel_shader_7:\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "popl %%edi\n\t"
      "jne .Lrasterizer_set_pixel_shader_9\n\t"
      "movzbl 0xb(%%ebp), %%eax\n\t"
      "movzbl %%bl, %%ecx\n\t"
      "leal 0x4(%%eax,%%ecx,1), %%edx\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "movl 0x5a555c, %%ecx\n\t"
      "imull %%eax, %%edx\n\t"
      "leal 0x20(%%ecx,%%edx,4), %%edx\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x5a555c\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_pixel_shader_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ec120]\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .Lrasterizer_set_pixel_shader_9\n\t"
      "addl $0xe4, 0x5a555c\n\t"
      ".Lrasterizer_set_pixel_shader_9:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156510_assert), [exitfn] "m"(b156510_exitfn), [c1e9320] "m"(b156510_c1e9320), [c1e9350] "m"(b156510_c1e9350), [c1e93a0] "m"(b156510_c1e93a0), [c1ec120] "m"(b156510_c1ec120)
      : "memory");
}
#else
#error "rasterizer_set_pixel_shader: clang naked draft required"
#endif


/* rasterizer_set_model_skinning (0x156710) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void (*const b156710_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156710_exitfn)(int) = system_exit;
static void __stdcall (*const b156710_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;

__attribute__((naked, noinline))
void rasterizer_set_model_skinning(void *a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrasterizer_set_model_skinning_1\n\t"
      "pushl $1\n\t"
      "pushl $0xabd\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e128\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_skinning_1:\n\t"
      "cmpl $0, (%%esi)\n\t"
      "jne .Lrasterizer_set_model_skinning_2\n\t"
      "pushl $1\n\t"
      "pushl $0xabe\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e110\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_skinning_2:\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_set_model_skinning_3\n\t"
      "cmpw $0x2c, %%ax\n\t"
      "jl .Lrasterizer_set_model_skinning_4\n\t"
      ".Lrasterizer_set_model_skinning_3:\n\t"
      "pushl $1\n\t"
      "pushl $0xabf\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e0b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_skinning_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, 0x4(%%esi)\n\t"
      "jle .Lrasterizer_set_model_skinning_6\n\t"
      "pushl %%edi\n\t"
      ".Lrasterizer_set_model_skinning_5:\n\t"
      "movl (%%esi), %%edi\n\t"
      "movswl %%dx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "flds (%%ecx,%%edi,1)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%ecx,%%edi,1)\n\t"
      "addl %%edi, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl $0x476208, %%eax\n\t"
      "incl %%edx\n\t"
      "fstps (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x10(%%ecx)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1c(%%ecx)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "movl 0x28(%%ecx), %%edi\n\t"
      "movl %%edi, 0xc(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fstps 0x10(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x14(%%ecx)\n\t"
      "fstps 0x14(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x20(%%ecx)\n\t"
      "fstps 0x18(%%eax)\n\t"
      "movl 0x2c(%%ecx), %%edi\n\t"
      "movl %%edi, 0x1c(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0xc(%%ecx)\n\t"
      "fstps 0x20(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x18(%%ecx)\n\t"
      "fstps 0x24(%%eax)\n\t"
      "fmuls 0x24(%%ecx)\n\t"
      "fstps 0x28(%%eax)\n\t"
      "movl 0x30(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x2c(%%eax)\n\t"
      "cmpw 0x4(%%esi), %%dx\n\t"
      "jl .Lrasterizer_set_model_skinning_5\n\t"
      "popl %%edi\n\t"
      ".Lrasterizer_set_model_skinning_6:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x476208\n\t"
      "pushl $-0x24\n\t"
      "call *%[c1eb8d0]\n\t"
      "cmpw $0, 0x3256ba\n\t"
      "je .Lrasterizer_set_model_skinning_7\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl 0x5a5550, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a5550\n\t"
      ".Lrasterizer_set_model_skinning_7:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156710_assert), [exitfn] "m"(b156710_exitfn), [c1eb8d0] "m"(b156710_c1eb8d0)
      : "memory");
}
#else
#error "rasterizer_set_model_skinning: clang naked draft required"
#endif


/* rasterizer_set_model_lighting_point_light (0x156850) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void (*const b156850_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156850_exitfn)(int) = system_exit;
static char * (*const b156850_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void *(*const b156850_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void rasterizer_set_model_lighting_point_light(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrasterizer_set_model_lighting_point_light_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb0a\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e178\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_lighting_point_light_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrasterizer_set_model_lighting_point_light_6\n\t"
      "testl %%esi, %%esi\n\t"
      "movl 0x5a37e0, %%eax\n\t"
      "jl .Lrasterizer_set_model_lighting_point_light_2\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .Lrasterizer_set_model_lighting_point_light_3\n\t"
      ".Lrasterizer_set_model_lighting_point_light_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xb13\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x29e148\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_lighting_point_light_3:\n\t"
      "imull $0x38, %%esi, %%esi\n\t"
      "addl $0x5a37e4, %%esi\n\t"
      "flds 0x34(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrasterizer_set_model_lighting_point_light_4\n\t"
      "pushl $1\n\t"
      "pushl $0xb15\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e134\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_lighting_point_light_4:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "leal 0x10(%%esi), %%edx\n\t"
      "flds 0x34(%%esi)\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fstps 0xc(%%eax)\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "leal 0x20(%%eax), %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "cmpl $0xbf800000, 0x1c(%%ecx)\n\t"
      "je .Lrasterizer_set_model_lighting_point_light_5\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "popl %%edi\n\t"
      "fsubs 0x20(%%ecx)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fsts 0x1c(%%eax)\n\t"
      "movl (%%esi), %%edx\n\t"
      "fmuls 0x20(%%edx)\n\t"
      "popl %%esi\n\t"
      "fchs\n\t"
      "fstps 0x2c(%%eax)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_model_lighting_point_light_5:\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x1c(%%eax)\n\t"
      "movl $0x3f800000, 0x2c(%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_set_model_lighting_point_light_6:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "pushl $0x30\n\t"
      "leal (%%eax,%%edi,1), %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x1c(%%esi)\n\t"
      "movl $0x3f800000, 0x2c(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156850_assert), [exitfn] "m"(b156850_exitfn), [c8d9d0] "m"(b156850_c8d9d0), [memset] "m"(b156850_memset)
      : "memory");
}
#else
#error "rasterizer_set_model_lighting_point_light: clang naked draft required"
#endif


/* FUN_001569f0 (0x1569f0) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void (*const b1569f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1569f0_exitfn)(int) = system_exit;
static void *(*const b1569f0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_001569f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001569f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb3a\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e178\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001569f0_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001569f0_2\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal 0x3(%%eax), %%edi\n\t"
      "shll $5, %%edi\n\t"
      "leal 0xc(%%ecx), %%edx\n\t"
      "movl (%%edx), %%ebx\n\t"
      "addl %%esi, %%edi\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x4(%%edx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edi)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "shll $5, %%eax\n\t"
      "leal 0x70(%%eax,%%esi,1), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "popl %%ebx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001569f0_2:\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "addl $3, %%edx\n\t"
      "pushl $0x20\n\t"
      "shll $5, %%edx\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1569f0_assert), [exitfn] "m"(b1569f0_exitfn), [memset] "m"(b1569f0_memset)
      : "memory");
}
#else
#error "FUN_001569f0: clang naked draft required"
#endif


/* FUN_00156a90 (0x156a90) — readable C lift. */
int FUN_00156a90(int a)
{
  D3DSurface_LockRect((void *)(unsigned)a, 0, 0, 0);
  return 0;
}

/* rasterizer_set_model_lighting (0x156ab0) — XBE naked draft (batch 319). */
#if defined(__clang__)
static void (*const b156ab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156ab0_exitfn)(int) = system_exit;
static void *(*const b156ab0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b156ab0_c156850)(void) = (void *)rasterizer_set_model_lighting_point_light;
static void (*const b156ab0_c1569f0)(void) = (void *)FUN_001569f0;
static void __stdcall (*const b156ab0_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;

__attribute__((naked, noinline))
void rasterizer_set_model_lighting(void *lighting __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrasterizer_set_model_lighting_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb50\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x291690\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_lighting_1:\n\t"
      "movw 0x40(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lrasterizer_set_model_lighting_2\n\t"
      "cmpw $2, %%ax\n\t"
      "jle .Lrasterizer_set_model_lighting_3\n\t"
      ".Lrasterizer_set_model_lighting_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xb51\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e1f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_lighting_3:\n\t"
      "movw 0xc(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lrasterizer_set_model_lighting_4\n\t"
      "cmpw $2, %%ax\n\t"
      "jle .Lrasterizer_set_model_lighting_5\n\t"
      ".Lrasterizer_set_model_lighting_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xb52\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29e190\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_model_lighting_5:\n\t"
      "flds 0x3256f0\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_set_model_lighting_6\n\t"
      "pushl $0xb0\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "flds 0x3256f0\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jmp .Lrasterizer_set_model_lighting_11\n\t"
      ".Lrasterizer_set_model_lighting_6:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x44(%%ebx), %%edi\n\t"
      ".Lrasterizer_set_model_lighting_7:\n\t"
      "cmpw %%si, 0x40(%%ebx)\n\t"
      "jle .Lrasterizer_set_model_lighting_8\n\t"
      "movl (%%edi), %%eax\n\t"
      "jmp .Lrasterizer_set_model_lighting_9\n\t"
      ".Lrasterizer_set_model_lighting_8:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Lrasterizer_set_model_lighting_9:\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c156850]\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%esi\n\t"
      "addl $4, %%edi\n\t"
      "cmpw $2, %%si\n\t"
      "jl .Lrasterizer_set_model_lighting_7\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x10(%%ebx), %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrasterizer_set_model_lighting_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%si, 0xc(%%ebx)\n\t"
      "leal -0xb0(%%ebp), %%edx\n\t"
      "setle %%al\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "decl %%eax\n\t"
      "andl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1569f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%esi\n\t"
      "addl $0x18, %%edi\n\t"
      "cmpw $2, %%si\n\t"
      "jl .Lrasterizer_set_model_lighting_10\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      ".Lrasterizer_set_model_lighting_11:\n\t"
      "pushl $0xb\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x4f\n\t"
      "call *%[c1eb8d0]\n\t"
      "cmpw $0, 0x3256ba\n\t"
      "popl %%ebx\n\t"
      "je .Lrasterizer_set_model_lighting_12\n\t"
      "addl $0xb0, 0x5a5554\n\t"
      ".Lrasterizer_set_model_lighting_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156ab0_assert), [exitfn] "m"(b156ab0_exitfn), [memset] "m"(b156ab0_memset), [c156850] "m"(b156ab0_c156850), [c1569f0] "m"(b156ab0_c1569f0), [c1eb8d0] "m"(b156ab0_c1eb8d0)
      : "memory");
}
#else
#error "rasterizer_set_model_lighting: clang naked draft required"
#endif


/* rasterizer_set_frustum_z (0x156c30) — XBE naked draft (batch 329). */
#if defined(__clang__)
static void (*const b156c30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b156c30_exitfn)(int) = system_exit;
static void (*const b156c30_c185830)(void) = (void *)render_camera_hack_frustum_z;
static void __stdcall (*const b156c30_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;

__attribute__((naked, noinline))
void rasterizer_set_frustum_z(float near_z __attribute__((unused)), float far_z __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x80, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrasterizer_set_frustum_z_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb97\n\t"
      "pushl $0x29dc0c\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_set_frustum_z_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a5c1c\n\t"
      "call *%[c185830]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x74(%%ebp), %%edi\n\t"
      "movl $0x5a5d70, %%ecx\n\t"
      "movl $4, %%ebx\n\t"
      "jmp .Lrasterizer_set_frustum_z_2\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrasterizer_set_frustum_z_2:\n\t"
      "leal -0xc(%%edi), %%edx\n\t"
      "movl $0x5a5c34, %%eax\n\t"
      "movl $4, %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrasterizer_set_frustum_z_3:\n\t"
      "flds -0x4(%%eax)\n\t"
      "addl $4, %%edx\n\t"
      "fmuls -0x10(%%ecx)\n\t"
      "addl $0xc, %%eax\n\t"
      "decl %%esi\n\t"
      "flds -0x8(%%eax)\n\t"
      "fmuls 0x10(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ecx)\n\t"
      "fmuls -0xc(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x4(%%edx)\n\t"
      "jne .Lrasterizer_set_frustum_z_3\n\t"
      "flds 0x20(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "fadds (%%edi)\n\t"
      "addl $0x10, %%edi\n\t"
      "decl %%ebx\n\t"
      "fstps -0x10(%%edi)\n\t"
      "jne .Lrasterizer_set_frustum_z_2\n\t"
      "movl 0x5a5bc8, %%edx\n\t"
      "movl 0x5a5bcc, %%eax\n\t"
      "movl 0x5a5bd0, %%ecx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0x5a5bd4, %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl 0x5a5c64, %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0x5a5bd8, %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0x5a5bdc, %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x5a5c70, %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x5a5c68, %%eax\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl 0x5a5c6c, %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl $8\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x5a5c74, %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x5a5c78, %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $-0x60\n\t"
      "movl $0x40000000, -0x34(%%ebp)\n\t"
      "movl $0x3f000000, -0x24(%%ebp)\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl $0x437ff000, -0x4(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b156c30_assert), [exitfn] "m"(b156c30_exitfn), [c185830] "m"(b156c30_c185830), [c1eb8d0] "m"(b156c30_c1eb8d0)
      : "memory");
}
#else
#error "rasterizer_set_frustum_z: clang naked draft required"
#endif


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
static void (*const b157010_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b157010_c1e98e0)(uint32_t value) = (void *)D3DDevice_SetRenderState_ZBias;
static void (*const b157010_c1e9380)(uint32_t reg_index, uint32_t value) = D3DDevice_SetRenderState_Deferred;
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

