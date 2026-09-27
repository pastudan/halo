/* Tip-only denser XDK/D3D/XAudio tips. */
#include <stdint.h>

/* D3DDevice_GetVertexShaderType (0x1eb560) — Capstone tip: flags→type; null out ok. */
void __stdcall D3DDevice_GetVertexShaderType(void *shader, unsigned *out_type)
{
  unsigned char flags = *((unsigned char *)shader + 3);
  unsigned type;
  if (flags & 8)
    type = 3;
  else
    type = ((flags & 1) != 0) + 1;
  if (out_type)
    *out_type = type;
}

/* XAudioCreatePcmFormat (0x20ca62) — Capstone tip: fill WAVEFORMATEX-like. */
void __stdcall XAudioCreatePcmFormat(unsigned short channels, unsigned rate,
                                     unsigned short bits, void *fmt)
{
  unsigned short *w = (unsigned short *)fmt;
  unsigned *d = (unsigned *)fmt;
  unsigned bytes;
  w[1] = channels;
  w[7] = bits;
  bytes = (unsigned)channels * (unsigned)bits;
  bytes = bytes / 8;
  w[8] = 0;
  d[1] = rate;
  w[0] = 1;
  w[6] = (unsigned short)bytes;
  d[2] = (unsigned)bytes * rate;
}

/* CDirectSound_GetSpeakerConfig (0x203a07) — Capstone tip: mask speaker flags → 0. */
int __stdcall CDirectSound_GetSpeakerConfig(void *this_ptr, unsigned int *out_cfg)
{
  unsigned v = *(unsigned *)(*(unsigned **)((char *)this_ptr + 8) + 2);
  *out_cfg = v & 0x7fffffffu;
  return 0;
}

/* CMiniport_GetDisplayCapabilities (0x1f4880) — Capstone tip: lazy Av query. */
void *CMiniport_GetDisplayCapabilities(void)
{
  if (*(void **)0x1fb468 == 0) {
    ((void (__stdcall *)(int, int, int, void *))*(void **)0x2532b0)(0, 6, 0, (void *)0x1fb468);
  }
  return *(void **)0x1fb468;
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

/* CMcpxBuffer_SetBufferData (0x20ba90) — Capstone tip: flag4 set → eax=0 ret. */
int __fastcall CMcpxBuffer_SetBufferData(void *this_ptr)
{
  unsigned char *mcp = *(unsigned char **)((char *)this_ptr + 0x148);
  if (mcp[0xe] & 4)
    return 0;
  /* unset path not tip-proven */
  return 0;
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

/* IDirectSound_CommitDeferredSettings (0x204ea1) — Capstone tip: null-safe this-8. */
int __stdcall IDirectSound_CommitDeferredSettings(void *dsound)
{
  unsigned t = (unsigned)(unsigned long)dsound;
  unsigned obj = t - 8;
  unsigned mask = t ? 0xffffffffu : 0u;
  void *p = (void *)(unsigned long)(mask & obj);
  return ((int (__stdcall *)(void *))(void *)0x203da9)(p);
}

/* CDirectSoundStream_AddRef (0x2059f9) — Capstone tip: AddRef(this+4). */
int __stdcall CDirectSoundStream_AddRef(void *this_ptr)
{
  return ((int (__stdcall *)(void *))(void *)0x203936)((char *)this_ptr + 4);
}

/* CDirectSoundStream_Release (0x205a09) — Capstone tip: Release(this+4). */
int __stdcall CDirectSoundStream_Release(void *this_ptr)
{
  return ((int (__stdcall *)(void *))(void *)0x20395b)((char *)this_ptr + 4);
}
