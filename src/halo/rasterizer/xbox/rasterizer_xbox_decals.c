/*
 * rasterizer_xbox_decals.c
 *
 * Rasterizer decal subsystem: D3D vertex buffer allocation, LRUV vertex
 * cache lifecycle, and per-map init/dispose.
 *
 * Source path (from binary):
 * c:\halo\SOURCE\rasterizer\xbox\rasterizer_xbox_decals.c
 *
 * Globals (used by address, not in kb.json):
 *   0x476ab0  void *  – global_d3d_device (IDirect3DDevice8 pointer)
 *   0x476ad8  void *  – local_d3d_vertex_buffer (12-byte D3D VB struct)
 *   0x476adc  void *  – local_vertex_cache (lruv_cache handle)
 *   0x476ae0  bool    – locked-decal eviction warning flag (one-shot)
 *   0x476ae1  bool    – permanent-decal eviction warning flag (one-shot)
 *   0x5aa8b8  void *  – global_decal_data (decal data array pointer)
 *   0x32516c  int     – most-recently-queried decal index (debug display)
 */

#include "x87_math.h"

/* Forward declarations for callbacks passed to lruv_cache_new.
 * FUN_0015afa0 is the eviction callback; FUN_0015b0c0 is the lock-query
 * callback (both ported at their original addresses). */
void FUN_0015afa0(int decal_index);
bool FUN_0015b0c0(int decal_index);

/* D3DSURFACE_DESC mirror (Xbox D3D8, 0x1c bytes; desc buffer at EBP-0x30). */
typedef struct {
  unsigned int Format; /* +0x00 */
  unsigned int Type; /* +0x04 */
  unsigned int Usage; /* +0x08 */
  unsigned int Size; /* +0x0c  ([EBP-0x24]) */
  unsigned int MultiSampleType; /* +0x10 */
  unsigned int Width; /* +0x14  ([EBP-0x1c]) */
  unsigned int Height; /* +0x18  ([EBP-0x18]) */
} d3d_surface_desc_t;

/* D3DLOCKED_RECT mirror (Pitch first, then pBits — 8 bytes at EBP-0x14). */
typedef struct {
  int Pitch; /* +0x00  ([EBP-0x14]) */
  void *pBits; /* +0x04  ([EBP-0x10]) */
} d3d_locked_rect_t;

/* D3DVIEWPORT8 mirror (0x18 bytes; viewport buffer at EBP-0x18 in
 * FUN_00158140). */
typedef struct {
  unsigned int X; /* +0x00 */
  unsigned int Y; /* +0x04 */
  unsigned int Width; /* +0x08 */
  unsigned int Height; /* +0x0c */
  float MinZ; /* +0x10 */
  float MaxZ; /* +0x14 */
} d3d_viewport_t;

/* 0x157e40
 *
 * rasterizer_present
 *
 * Presents the current back buffer to the display.  When a non-NULL
 * screenshot_bitmap with pixel data (bitmap+0x2c != 0) is supplied, the
 * back-buffer surface is locked and blitted into the bitmap before Present.
 *
 * The capture rectangle comes from two packed-short DWORD globals
 * (left/top/right/bottom at 0x325654/56/58/5a); the optional 2-element
 * `point` (short[2]) rescales the base corner within the rect span.
 *
 * NOTE the blit is rotated: the copy loop iterates right-left times (BX)
 * while each row copies Pitch = bpp*(bottom-top)/8 bytes, and
 * bitmap_2d_address is called with x = top-chain value ([EBP-0xa]) and
 * y = row + left-chain value ([EBP-0xc]) — verified against disassembly
 * (0x157fea-0x158024); the Ghidra draft re-homes these slots.
 *
 * Globals (hardcoded, not in kb.json):
 *   0x476ab0  void *   – global_d3d_device
 *   0x325654  short[2] – capture rect left|top (packed dword)
 *   0x325658  short[2] – capture rect right|bottom (packed dword)
 *   0x505728  void *   – window_globals.hWndPresentTarget
 *   0x325668  uint64   – 64-bit frame/present counter (ADD/ADC pair)
 */
void rasterizer_present(void *screenshot_bitmap, short *point)
{
  const char *msg;
  bool ok;
  short rect_x0; /* lo(0x325654) = left chain   ([EBP-0xc], Ghidra local_10) */
  short rect_y0; /* hi(0x325654) = top chain    ([EBP-0xa], Ghidra sStack_e) */
  short rect_x1; /* lo(0x325658) = right chain  ([EBP-0x8], Ghidra local_c) */
  short rect_y1; /* hi(0x325658) = bottom chain ([EBP-0x6], Ghidra sStack_a) */

  if (*(void **)0x476ab0 == 0) {
    display_assert("global_d3d_device",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                   0x699, 1);
    system_exit(-1);
  }

  ok = true;

  if (screenshot_bitmap != 0 &&
      *(int *)((char *)screenshot_bitmap + 0x2c) != 0) {
    /* Seed rect from the two packed-short globals. */
    rect_x0 = *(short *)0x325654;
    rect_y0 = *(short *)0x325656;
    rect_x1 = *(short *)0x325658;
    rect_y1 = *(short *)0x32565a;

    if (point != 0) {
      rect_y1 = rect_y1 - rect_y0;
      rect_x1 = rect_x1 - rect_x0;
      rect_y0 = point[0] * rect_y1;
      rect_x0 = point[1] * rect_x1;
      rect_y1 = rect_y1 + rect_y0;
      rect_x1 = rect_x0 + rect_x1;
    }

    if ((*(short *)((char *)screenshot_bitmap + 0xc) == 0xb ||
         *(short *)((char *)screenshot_bitmap + 0xc) == 10) &&
        *(short *)((char *)screenshot_bitmap + 0x14) == 0 && rect_y0 >= 0 &&
        rect_x0 >= 0 && rect_y1 <= *(short *)((char *)screenshot_bitmap + 4) &&
        rect_x1 <= *(short *)((char *)screenshot_bitmap + 6)) {
      void *surface;
      d3d_surface_desc_t desc;

      surface = 0;
      D3DDevice_GetBackBuffer(0, 0, &surface);
      D3DSurface_GetDesc(surface, &desc);

      /* Size check loads +0x18 then +0x14 (disasm order). */
      if (desc.Size == desc.Height * desc.Width * 4) {
        d3d_locked_rect_t locked;

        D3DSurface_LockRect(surface, &locked, 0, 0xC0);

        if (locked.pBits != 0) {
          short row;
          short h; /* SI: bottom - top (per-row byte span source) */
          short w; /* BX: right - left (row count) */
          short bpp;
          int nb;

          h = (short)(*(short *)0x32565a - *(short *)0x325656);
          w = (short)(*(short *)0x325658 - *(short *)0x325654);
          bpp = bitmap_format_bits_per_pixel(
            *(short *)((char *)screenshot_bitmap + 0xc));
          nb = (int)bpp * (int)h;

          /* signed /8 — VC71 emits the CDQ/AND 7/ADD/SAR 3 idiom. */
          if (locked.Pitch != nb / 8) {
            display_assert(
              "d3d_locked_rect.Pitch==bitmap_format_get_bits_per_pixel("
              "screenshot_bitmap->format)*screen_width/CHAR_BITS",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c", 0x6c4,
              1);
            system_exit(-1);
          }

          for (row = 0; row < w; row = (short)(row + 1)) {
            void *dst = bitmap_2d_address(screenshot_bitmap, rect_y0,
                                          (short)(row + rect_x0), 0);
            csmemcpy(dst, (char *)locked.pBits + (int)row * locked.Pitch,
                     locked.Pitch);
          }

          ok = true;
          goto present;
        } else {
          msg = "### ERROR rasterizer_present: failed to lock backbuffer "
                "surface";
        }
      } else {
        msg = "### ERROR rasterizer_present: failed to get backbuffer surface";
      }
    } else {
      msg = "### ERROR rasterizer_present: invalid bitmap";
    }

    error(2, msg);
    ok = false;
  }

present:
  /* PUSH 0; PUSH EAX=[0x505728]; PUSH 0; PUSH 0 →
   * Present(NULL, NULL, hWndPresentTarget, NULL). */
  D3DDevice_Present(0, 0, *(void **)0x505728, 0);

  if (!ok) {
    FUN_00167ff0(0, "IDirect3DDevice8_Present(global_d3d_device, NULL, NULL, "
                    "window_globals.hWndPresentTarget, NULL)");
  }

  /* 64-bit present counter {0x325668 lo, 0x32566c hi} += 1 (ADD/ADC). */
  *(unsigned __int64 *)0x325668 += 1;

  if (!ok) {
    error(2, "### ERROR rasterizer_present failed");
  }
}

/* rasterizer_draw_dynamic_vertices (0x15d5b0) — Capstone tip: null rasterizer globals → assert. */
void __cdecl rasterizer_draw_dynamic_vertices(int first_primitive_index, int primitive_count,
                                              int dynamic_vertex_buffer_index, short vertex_type)
{
  (void)first_primitive_index;
  (void)primitive_count;
  (void)dynamic_vertex_buffer_index;
  (void)vertex_type;
  if (*(int *)0x476ab0 == 0) {
    display_assert((char *)0x29dc40, (char *)0x2a0110, 0x28b, 1);
    system_exit(-1);
  }
}


/*
 * FUN_00158df0 (0x158df0) — rasterizer scene render begin
 *
 * Ghidra mis-declares this as void(void); the real ABI is a single cdecl
 * stack pointer parameter (`parameters`, a ushort/struct pointer). Copies the
 * 600-byte (0x96-dword) parameters block into the global mirror at 0x5a5bc0,
 * updates the "same render target" flag, resolves the clear color, then drives
 * the per-frame render-begin call chain and installs the initial frustum-z /
 * fill-mode state.
 *
 * Globals (hardcoded, not in kb.json; widths taken from disasm store/compare
 * operand sizes, NOT the decompiler):
 *   0x476ab0  device pointer, global_d3d_device (asserted non-NULL)
 *   0x476ab8  BYTE same-target flag (mov [..],al — skips heavy setup when 1)
 *   0x476abc  WORD previous parameters[1] (cmp/mov word; sentinel 0xffff)
 *   0x3256bc  WORD mode flag (cmp word ptr,1 forces the clear color to 0)
 *   0x3256be  BYTE wireframe flag (neg/sbb ternary picks D3DFILL_WIREFRAME)
 *   0x5a5bc0  600-byte mirror of the parameters block
 *   0x5a5dac  float color at offset 0x1ec inside the mirror, converted to pixel32
 *
 * Field offsets (parameters is a ushort pointer):
 *   parameters[0]  byte +0x00  render target index (only 0 or 1 supported)
 *   parameters[1]  byte +0x02  target id (0xffff = special/main target)
 *   byte +0x05                 bool selector for FUN_00158140 arg4
 *   float +0x44                camera.z_near
 *
 * All four assert terminals are PUSH -1 (or PUSH EDI with EDI still -1 from
 * the OR EDI,-1 at 0x158e54) then CALL 0x8e2f0 = system_exit(-1) — NOT
 * halt_and_catch_fire (the first parked lift substituted hcf at all four
 * sites; review-gate REJECT, same anti-pattern as FUN_0015c680).
 */
/* 0x158df0 */
void FUN_00158df0(unsigned short *parameters)
{
  unsigned int color_pixel;
  char same_target;

  if (parameters == 0) {
    display_assert("parameters",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                   0x547, true);
    system_exit(-1);
  }
  if (*(void **)0x476ab0 == 0) {
    display_assert("global_d3d_device",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                   0x548, true);
    system_exit(-1);
  }

  /* Copy 0x96 dwords (600 bytes) from parameters into the global mirror.
   * MSVC lowers the constant-size memcpy to `rep movsl` (ECX=0x96). */
  memcpy((void *)0x5a5bc0, parameters, 0x258);

  /* Same-target detection: flag set only when we have rendered before
   * (prev word != 0xffff sentinel) and the current target id IS 0xffff.
   * The flag is computed in AL and branched on directly (test al,al) —
   * the branch below uses the local, not a re-read of the byte global. */
  if (*(unsigned short *)0x476abc != 0xffff && parameters[1] == 0xffff) {
    same_target = 1;
  } else {
    same_target = 0;
  }
  *(char *)0x476ab8 = same_target;
  *(unsigned short *)0x476abc = parameters[1];

  if (same_target == 0) {
    rasterizer_memory_pool_reset();
    FUN_0015d060();
    rasterizer_transparent_geometry_begin();
    FUN_001659f0();
    FUN_001812b0();
  }
  /* Disasm: push 0 before 0x1792c0 and 0x1592e0, no push before 0x16f880,
   * push 0 before 0x158ae0, push (parameters+0x1e8) before 0x17c8f0;
   * one deferred ADD ESP,0x10 cleans all four dword args. The decompiler
   * dropped the first, second and fifth arguments. */
  FUN_001792C0(0);
  FUN_001592e0(0);
  FUN_0016f880();
  FUN_00158ae0(0);
  rasterizer_environment_fog_screen_end((char *)parameters + 0x1e8);

  if (*(short *)0x3256bc == 1) {
    color_pixel = 0;
  } else {
    color_pixel = FUN_000d1dd0((float *)0x5a5dac);
  }

  if (*parameters == 0 || *parameters == 1) {
    FUN_0016f910(0);
    /* arg4 is a byte-wide bool; Ghidra's CONCAT31(extraout_EAX>>8,...) is an
     * artifact of the bool being built in EAX — the upper bytes are garbage. */
    FUN_00158140((unsigned int)*parameters, 0, color_pixel,
                 (*((char *)parameters + 5) == 0), 1);
    FUN_0016fa40(0);
    if (*parameters == 0 && *(float *)((char *)parameters + 0x44) == 0.0f) {
      display_assert("parameters->camera.z_near!=0.0f",
                     "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c",
                     0x587, true);
      system_exit(-1);
    }
  } else {
    display_assert(
      "### ERROR unsupported rasterizer target for scene rendering",
      "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c", 0x58c, true);
    system_exit(-1);
  }

  rasterizer_set_frustum_z(-1.0f, -1.0f);
  /* Fill mode: byte 0x3256be selects D3DFILL_WIREFRAME (0x1b01) over
   * D3DFILL_SOLID (0x1b02); original lowers this ternary to neg/sbb/add. */
  D3DDevice_SetRenderState_FillMode(
    (*(unsigned char *)0x3256be != 0) ? 0x1b01 : 0x1b02);
}

/* FUN_0015d300 (0x15d300) — readable C lift (ret thunk). */
__attribute__((noinline))
void FUN_0015d300(void)
{
  __asm__ volatile("");
}

/* FUN_0015d5a0 (0x15d5a0) — readable C lift (ret thunk). */
__attribute__((noinline))
void FUN_0015d5a0(void)
{
  __asm__ volatile("");
}
