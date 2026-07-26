/* kb object stubs -> xdk/xdk_stubs_rt.c */

#include "xdk_stubs_protos.h"
#include "xdk_cross_protos.h"

/* --- <xdk_stubs> batch drafts (2026-07-26) --- */

/* 0x1cfa3f */

/* --- forward decls (auto) --- */
void SetThreadPriorityBoost(void);
void FUN_001cfa85(void);
void FUN_001cfac6(void);
int ResumeThread(int thread_handle);
void RaiseException(void);
void SwitchToThread(void);
int GetExitCodeThread(int thread_handle, int *exit_code);
void FUN_001cfc1b(void);
void XRegisterThreadNotifyRoutine(void);
void * CreateThread(void *security, int stack_size, void *func, void *param, int flags, int *thread_id);
void FUN_001cfde0(void);
void * CreateEventA(void *security, int manual_reset, int initial_state, const char *name);
void OpenEventA(void);
bool SetEvent(void *handle);
void ResetEvent(void);
void FUN_001cff08(void);
void FUN_001cff63(void);
void CreateMutexA(void);
void FUN_001d003d(void);
int ReleaseMutex(int mutex_handle);
void FUN_001d00b9(void);
void SignalObjectAndWait(void);
void FUN_001d0144(void);
unsigned int SleepEx(unsigned int milliseconds, int alertable);
void FUN_001d0216(void);
void FUN_001d0274(void);
void FUN_001d02d0(void);
int WaitForSingleObject(int handle, int timeout_ms);
void FUN_001d0348(void);
void FUN_001d0362(void);
void OutputDebugStringA(void);
void OutputDebugStringW(void);
void FUN_001d03ee(void);
void FUN_001d040f(void);
void FUN_001d0447(void);
void D3DDevice_CreateTexture(uint32_t width, uint32_t height, uint32_t levels, uint32_t usage, uint32_t format, uint32_t pool, void *out_texture);
void D3DDevice_SetTransform(uint32_t type, void *matrix);
void D3DDevice_GetTransform(uint32_t type, void *matrix_out);
void D3DDevice_BlockUntilVerticalBlank(void);
void D3DDevice_SetRenderTarget(void *render_target, void *depth_stencil);
int D3DDevice_GetBackBuffer(int back_buffer, uint32_t type, void **out_surface);
int D3DDevice_GetDepthStencilSurface(void **out_surface);
void D3DDevice_SetTexture(uint32_t stage, void *texture);
void D3DDevice_SetRenderState_Simple(uint32_t reg, uint32_t value);
void D3DDevice_SetRenderState_Deferred(uint32_t reg_index, uint32_t value);
void D3DDevice_SetTextureStageState(uint32_t stage, uint32_t state, uint32_t value);
void D3DDevice_SetRenderState_CullMode(uint32_t mode);
void D3DDevice_SetTextureState_BorderColor(uint32_t stage, uint32_t color);
void D3DDevice_SetRenderState_ZEnable(uint32_t enable);
void D3DDevice_Clear(uint32_t count, void *rects, uint32_t flags, uint32_t color, float z, uint32_t stencil);
void D3DDevice_SetVertexShader(uint32_t shader);
void D3DDevice_SetPixelShaderProgram(void *program);
void D3DDevice_SetVertexData2f(uint32_t reg, float a, float b);
void D3DDevice_SetVertexData4f(uint32_t reg, float a, float b, float c, float d);
void D3DDevice_SetVertexData2s(unsigned int reg, int a, int b);
void D3DDevice_SetVertexDataColor(unsigned int reg, unsigned int color);
void D3DDevice_Begin(uint32_t primitive_type);
void D3DDevice_End(void);
void D3D_KickOffAndWaitForIdle(void);
int IDirectSoundBuffer_SetVolume(void *buffer, int volume);
int IDirectSoundBuffer_SetPitch(void *buffer, int pitch);
int IDirectSoundBuffer_SetLoopRegion(void *buffer, uint32_t start, uint32_t length);
int IDirectSoundBuffer_SetCurrentPosition(void *buffer, uint32_t position);
int IDirectSoundStream_SetVolume(void *stream, int volume);
int IDirectSoundStream_SetConeAngles(void *stream, int inner_angle, int outer_angle, int deferred);
int IDirectSoundStream_SetConeOutsideVolume(void *stream, int volume, int deferred);
int IDirectSoundStream_SetMaxDistance(void *stream, float distance, int deferred);
int IDirectSoundStream_SetMinDistance(void *stream, float distance, int deferred);
int IDirectSoundStream_SetAllParameters(void *stream, void *params, int deferred);
int IDirectSoundBuffer_Play(void *buffer, uint32_t reserved, uint32_t priority, uint32_t flags);
int IDirectSoundBuffer_SetBufferData(void *buffer, void *data, uint32_t size);
int IDirectSoundStream_SetFrequency(void *stream, int frequency);
int DirectSoundCreateBuffer(void *desc, void **out_buffer);

void SetThreadPriorityBoost(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cfa79 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1cfa85 */
void FUN_001cfa85(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cfaba */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1cfac6 */
void FUN_001cfac6(void)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1cfae5 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1cfaec */
int ResumeThread(int thread_handle)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1cfb0b */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1cfb12 */
void RaiseException(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1cfb98 */
void SwitchToThread(void)
{
  XapiCallThreadNotifyRoutines();
}

/* 0x1cfbbd */
int GetExitCodeThread(int thread_handle, int *exit_code)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> jl 0x1cfbfd */
  /* relift: cmp byte ptr [ecx + 4], 0 -> je 0x1cfbe8 */
  XapiSetLastNTError(0);
  /* mem[0x00632a2c] = ecx */
  return 0;

  (void)eax;
  (void)ecx;
}

/* 0x1cfc1b */
void FUN_001cfc1b(void)
{
  int eax = 0;
  int ebx = 0;

  /* cmp eax, ebx -> jl 0x1cfc97 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebx;
}

/* 0x1cfca4 */
void XRegisterThreadNotifyRoutine(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [esp + 0xc], 0 -> je 0x1cfcd4 */
  /* mem[0x0032fd20] = eax */
  FUN_001dd5c8();
  /* test ecx, ecx -> je 0x1cfd59 */
  XapiCallThreadNotifyRoutines();
  XapiCallThreadNotifyRoutines();
  UnhandledExceptionFilter();

  (void)eax;
  (void)ecx;
}

/* 0x1cfd8c */
void * CreateThread(void *security, int stack_size, void *func, void *param, int flags, int *thread_id)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1cfd9b */
  /* test eax, eax -> jge 0x1cfdd9 */
  XapiSetLastNTError(0);
  return NULL;

  (void)eax;
}

/* 0x1cfde0 */
void FUN_001cfde0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1cfded */
void * CreateEventA(void *security, int manual_reset, int initial_state, const char *name)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x1cfe0b */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1cfe42 */
  /* cmp eax, 0x40000000 -> jne 0x1cfe36 */
  SetLastError(0);
  XapiSetLastNTError(0);
  return NULL;

  (void)eax;
  (void)ebp;
}

/* 0x1cfe4e */
void OpenEventA(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1cfe61 */
  /* test eax, eax -> jge 0x1cfea3 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1cfeaa */
bool SetEvent(void *handle)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cfebf */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1cfeca */
void ResetEvent(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cfedd */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cfefd */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1cff08 */
void FUN_001cff08(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x1cff26 */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1cff57 */
  /* cmp eax, 0x40000000 -> jne 0x1cff4b */
  SetLastError(0);
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1cff63 */
void FUN_001cff63(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1cff76 */
  /* test eax, eax -> jge 0x1cffb8 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cffda */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1cffe5 */
void CreateMutexA(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1d0003 */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1d0031 */
  /* cmp eax, 0x40000000 -> jne 0x1d0025 */
  SetLastError(0);
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d003d */
void FUN_001d003d(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d0050 */
  /* test eax, eax -> jge 0x1d0092 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d0099 */
int ReleaseMutex(int mutex_handle)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d00ae */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1d00b9 */
void FUN_001d00b9(void)
{
  int eax = 0;
  int ebp = 0;

  FUN_001d4436();
  /* test eax, eax -> jl 0x1d00ef */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1d00f8 */
  /* cmp eax, 0x101 -> je 0x1d00cd */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d00fd */
void SignalObjectAndWait(void)
{
  int eax = 0;
  int ebp = 0;

  FUN_001d4436();
  /* test eax, eax -> jl 0x1d0136 */
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x1d013f */
  /* cmp eax, 0x101 -> je 0x1d0111 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d0144 */
void FUN_001d0144(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  /* cmp ecx, 0x40 -> jbe 0x1d0164 */
  XapiSetLastNTError(0xc000000d);
  FUN_001d4436();
  /* test eax, eax -> jl 0x1d01b4 */
  /* relift: cmp dword ptr [ebp + 0x18], 0 -> je 0x1d01bd */
  /* cmp eax, 0x101 -> je 0x1d018c */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ecx;
  (void)ebp;
}

/* 0x1d01c4 */
unsigned int SleepEx(unsigned int milliseconds, int alertable)
{
  int eax = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001d4436();
  /* test esi, esi -> jne 0x1d01e9 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d0202 */
  /* cmp eax, 0x101 -> je 0x1d01e9 */
  return 0;

  (void)eax;
  (void)esi;
  (void)ebp;
}

/* 0x1d0216 */
void FUN_001d0216(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1d0234 */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1d0268 */
  /* cmp eax, 0x40000000 -> jne 0x1d025c */
  SetLastError(0);
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d0274 */
void FUN_001d0274(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d0287 */
  /* test eax, eax -> jge 0x1d02c9 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d02d0 */
void FUN_001d02d0(void)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1d02fd */
  XapiSetLastNTError(0);
  /* cmp eax, 0x40000025 -> jne 0x1d0308 */
  SetLastError(0);
  /* test eax, eax -> jge 0x1d0330 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d0336 */
int WaitForSingleObject(int handle, int timeout_ms)
{
  FUN_001d00b9();
  return 0;
}

/* 0x1d0348 */
void FUN_001d0348(void)
{
  FUN_001d0144();
}

/* 0x1d0362 */
void FUN_001d0362(void)
{
  SleepEx(0, 0);
}

/* 0x1d0370 */
void OutputDebugStringA(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d03a2 */
void OutputDebugStringW(void)
{
  int esi = 0;

  /* test esi, esi -> jge 0x1d03d3 */
  OutputDebugStringA();

  (void)esi;
}

/* 0x1d03ee */
void FUN_001d03ee(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d040f */
void FUN_001d040f(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0447 */
void FUN_001d0447(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d4464();
  /* test eax, eax -> jne 0x1d04ed */
  FUN_001d03ee();
  FUN_001d03ee();
  FUN_001d040f();
  FUN_001d040f();
  FUN_001d4464();
  /* test eax, eax -> jne 0x1d0518 */
  /* relift: test byte ptr [ebp - 4], 2 -> je 0x1d0518 */
  /* test (char)eax, (char)eax -> jne 0x1d0654 */
  XapiSetLastNTError(0xc000000d);
  /* cmp eax, ecx -> ja 0x1d0695 */
  /* cmp edx, esi -> jae 0x1d068b */
  /* cmp eax, ecx -> jb 0x1d069a */
  /* cmp edx, esi -> jbe 0x1d069a */
  FUN_001d0589();
  /* relift: cmp word ptr [esi], 0 -> je 0x1d06f0 */
  SystemTimeToFileTime((void *)(uintptr_t)esi, (void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1d0795 */
  /* relift: cmp eax, dword ptr [ebx + 4] -> jg 0x1d06e9 */
  /* relift: cmp eax, dword ptr [ebx] -> jb 0x1d0795 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1d0795 */
  /* test (char)eax, (char)eax -> jne 0x1d07a1 */
  /* cmp (int16_t)eax, (int16_t)edi -> jle 0x1d07be */
  /* test (char)eax, (char)eax -> je 0x1d0806 */
  /* test (char)eax, (char)eax -> je 0x1d0795 */
  /* cmp ecx, eax -> jl 0x1d0844 */
  /* relift: cmp edx, dword ptr [eax + 4] -> jg 0x1d089d */
  /* relift: cmp edi, dword ptr [eax] -> jae 0x1d089d */
  /* test (char)eax, (char)eax -> jne 0x1d079e */
  /* relift: tail-call FUN_001d0447(); */
  /* cmp eax, ebx -> je 0x1d08d3 */
  SetLastError(eax);
  /* relift: cmp word ptr [esi + 0x46], (int16_t)ebx -> je 0x1d09fd */
  /* relift: cmp word ptr [esi + 0x9a], (int16_t)ebx -> je 0x1d09fd */
  FUN_001d06a0();
  /* test (char)eax, (char)eax -> je 0x1d09fd */
  FUN_001d06a0();
  /* test (char)eax, (char)eax -> je 0x1d09fd */
  __allmul();
  __allmul();
  __allmul();
  /* cmp ebx, edx -> jg 0x1d09e0 */
  /* relift: cmp dword ptr [ebp - 0x18], eax -> jae 0x1d09e0 */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jl 0x1d09db */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x1d09db */
  /* relift: cmp dword ptr [ebp - 4], edx -> jg 0x1d09db */
  /* cmp ecx, eax -> jb 0x1d09fa */
  /* relift: cmp dword ptr [ebp - 4], edx -> jl 0x1d09fa */
  /* cmp ecx, eax -> jb 0x1d09fa */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jg 0x1d09fa */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x1d09db */
  GetTimeZoneInformation();
  __allmul();
  FUN_001d0a06();
  FUN_001d0a06();
  FUN_001d0a06();
  /* cmp edx, ecx -> jae 0x1d0b53 */
  /* test edx, edx -> jne 0x1d0b51 */
  /* relift: cmp dword ptr [ebp + 0xc], edx -> jbe 0x1d0b5b */
  FUN_001d5842();
  /* test esi, esi -> jne 0x1d0b79 */
  SetLastError(0);
  FUN_001d4e37();
  /* test eax, eax -> jne 0x1d0b90 */
  SetLastError(0);
  FUN_001d6ca8();
  FUN_001d5c66();
  /* test (char)eax, 0x40 -> je 0x1d0be3 */
  FUN_001d703b();
  FUN_001d52c4();
  FUN_001d6ca8();
  FUN_001d5c66();
  /* test (char)eax, 0x40 -> je 0x1d0c72 */
  FUN_001d703b();
  /* test eax, eax -> jl 0x1d0cb3 */
  XapiSetLastNTError(0);
  /* relift: test byte ptr [ebp + 0x11], 0x80 -> je 0x1d0cd5 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d0cd5 */
  /* test eax, eax -> jl 0x1d0cef */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0d1c */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0d3e */
  XapiSetLastNTError(0);
  FUN_001d0c91();
  FUN_001d0cbf();
  FUN_001d0cfb();
  /* relift: FUN_001d0d27(0, 0, 0); */
  /* test eax, eax -> jge 0x1d0e43 */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d0e88 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0ed4 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0f57 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d0fb2 */
  /* test esi, esi -> jl 0x1d0feb */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d104c */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d107a */
  XapiSetLastNTError(0);
  /* relift: test word ptr [esp + 4], 0xfff -> je 0x1d1098 */
  /* test eax, eax -> jl 0x1d10a8 */
  XapiSetLastNTError(0);
  /* relift: test byte ptr [esi + 0x38], 0x10 -> je 0x1d1174 */
  FUN_001d10bd();
  /* relift: cmp dword ptr [esi + 0x2c], 0 -> jne 0x1d11a6 */
  /* cmp eax, ebx -> jae 0x1d1195 */
  /* relift: cmp dword ptr [edi], ebx -> jae 0x1d11a6 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jl 0x1d11a8 */
  /* relift: cmp dword ptr [edi], ebx -> jb 0x1d11c9 */
  /* relift: cmp dword ptr [ebp + 0x10], 0xc000000f -> jne 0x1d11e2 */
  /* test esi, esi -> jl 0x1d12b4 */
  /* relift: test byte ptr [ebp - 0x28], 0x10 -> je 0x1d127d */
  /* test esi, esi -> jl 0x1d12b4 */
  FUN_001d10bd();
  /* relift: cmp dword ptr [ebp - 0x2c], 0 -> je 0x1d128a */
  /* test esi, esi -> jge 0x1d12bc */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d1315 */
  /* test esi, esi -> jl 0x1d1352 */
  /* cmp esi, 0xc00000d4 -> jne 0x1d13a2 */
  /* relift: test byte ptr [ebp + 0x18], 2 -> je 0x1d13a2 */
  FUN_001d1f10();
  /* test esi, esi -> je 0x1d139e */
  DeleteFileA((char *)(uintptr_t)ebx);
  /* test eax, eax -> jne 0x1d139e */
  FUN_001d0df0((char *)(uintptr_t)ebx, 128);
  DeleteFileA((char *)(uintptr_t)ebx);
  XapiSetLastNTError(0);
  FUN_001d12c1();
  /* cmp edi, ebx -> je 0x1d13dd */
  /* cmp esi, ebx -> je 0x1d144c */
  /* cmp eax, ebx -> jl 0x1d1437 */
  /* cmp eax, edi -> je 0x1d1437 */
  /* cmp eax, ebx -> je 0x1d1432 */
  /* cmp eax, ecx -> jne 0x1d14a7 */
  /* cmp eax, ebx -> je 0x1d1449 */
  /* cmp eax, 0x103 -> jne 0x1d147c */
  /* cmp eax, ebx -> jl 0x1d1487 */
  /* cmp eax, ebx -> jl 0x1d1487 */
  /* cmp eax, 0xc0000011 -> jne 0x1d1492 */
  /* cmp ecx, 0x80000000 -> jne 0x1d14a7 */
  XapiSetLastNTError(0);
  /* cmp edi, ebx -> je 0x1d14ca */
  /* cmp esi, ebx -> je 0x1d152d */
  /* cmp edx, ecx -> je 0x1d157d */
  /* cmp eax, edi -> je 0x1d157d */
  /* cmp eax, ebx -> je 0x1d1528 */
  /* cmp eax, 0x103 -> jne 0x1d155d */
  /* cmp eax, ebx -> jl 0x1d1568 */
  /* cmp eax, ebx -> jl 0x1d1568 */
  /* cmp ecx, 0x80000000 -> jne 0x1d157d */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d15b5 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d1603 */
  /* test eax, eax -> jl 0x1d1603 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d167c */
  /* test eax, eax -> jge 0x1d1687 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp - 8], 0 -> jae 0x1d16ac */
  /* test ebx, ebx -> jne 0x1d16c0 */
  /* test eax, 0x7fffffff -> je 0x1d16c0 */
  SetLastError(87);
  /* test eax, eax -> jl 0x1d16f4 */
  /* test ebx, ebx -> je 0x1d16e2 */
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x1d16ef */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* test ebx, ebx -> je 0x1d1703 */
  /* test eax, eax -> jl 0x1d17c6 */
  /* test eax, eax -> jl 0x1d17c6 */
  /* test ecx, ecx -> jae 0x1d1796 */
  SetLastError(131);
  /* test eax, eax -> jl 0x1d17c6 */
  /* test eax, eax -> je 0x1d17c1 */
  XapiSetLastNTError(0);
  /* cmp ecx, esi -> je 0x1d1899 */
  /* cmp ecx, esi -> je 0x1d1899 */
  /* cmp ecx, esi -> je 0x1d1899 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d1904 */
  /* test eax, eax -> je 0x1d18db */
  /* test eax, eax -> je 0x1d18ed */
  /* test eax, eax -> je 0x1d18ff */
  XapiSetLastNTError(0);
  /* test eax, eax -> je 0x1d1946 */
  /* test eax, eax -> je 0x1d1958 */
  /* test eax, eax -> jl 0x1d1976 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d199d */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d19d2 */
  XapiSetLastNTError(0);
  /* cmp edx, ecx -> jne 0x1d1a31 */
  XapiSetLastNTError(0);
  /* cmp edx, ecx -> jne 0x1d1a82 */
  XapiSetLastNTError(0);
  /* cmp edx, ecx -> je 0x1d1b11 */
  /* cmp ecx, ebx -> je 0x1d1b11 */
  /* cmp eax, ebx -> jl 0x1d1b79 */
  /* cmp eax, 0x103 -> je 0x1d1b79 */
  /* cmp eax, 0x103 -> jne 0x1d1b56 */
  /* cmp eax, ebx -> jl 0x1d1b64 */
  /* cmp eax, ebx -> jl 0x1d1b64 */
  /* cmp edx, ecx -> je 0x1d1b79 */
  XapiSetLastNTError(0);
  /* cmp edi, ebx -> je 0x1d1b9b */
  /* cmp esi, ebx -> je 0x1d1c0a */
  /* cmp eax, ebx -> jl 0x1d1bf5 */
  /* cmp eax, edi -> je 0x1d1bf5 */
  /* cmp eax, ebx -> je 0x1d1bf0 */
  /* cmp eax, ecx -> jne 0x1d1c65 */
  /* cmp eax, ebx -> je 0x1d1c07 */
  /* cmp eax, 0x103 -> jne 0x1d1c3a */
  /* cmp eax, ebx -> jl 0x1d1c45 */
  /* cmp eax, ebx -> jl 0x1d1c45 */
  /* cmp eax, 0xc0000011 -> jne 0x1d1c50 */
  /* cmp ecx, 0x80000000 -> jne 0x1d1c65 */
  XapiSetLastNTError(0);
  /* cmp edi, ebx -> je 0x1d1c88 */
  /* cmp esi, ebx -> je 0x1d1ceb */
  /* cmp edx, ecx -> je 0x1d1d3b */
  /* cmp eax, edi -> je 0x1d1d3b */
  /* cmp eax, ebx -> je 0x1d1ce6 */
  /* cmp eax, 0x103 -> jne 0x1d1d1b */
  /* cmp eax, ebx -> jl 0x1d1d26 */
  /* cmp eax, ebx -> jl 0x1d1d26 */
  /* cmp ecx, 0x80000000 -> jne 0x1d1d3b */
  XapiSetLastNTError(0);
  FUN_001d19a9();
  /* test eax, eax -> je 0x1d1d7a */
  /* test eax, eax -> je 0x1d1d6b */
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x1d1d7e */
  SetLastError(0);
  XapiSetLastNTError(0xc000000d);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)ebx -> jbe 0x1d1e06 */
  /* relift: cmp byte ptr [eax + edi - 1], 0x5c -> jne 0x1d1e06 */
  /* cmp esi, ebx -> jge 0x1d1ee2 */
  XapiSetLastNTError(0);
  /* cmp esi, 0xc0000035 -> jne 0x1d1ec5 */
  /* cmp esi, 0xc00000ba -> jne 0x1d1edd */
  /* relift: cmp dword ptr [ebp + 8], ebx -> je 0x1d1ed6 */
  SetLastError(0);
  /* relift: cmp dword ptr [ebp + 0x18], 2 -> jne 0x1d1eee */
  /* relift: cmp dword ptr [ebp - 0x10], 3 -> je 0x1d1efa */
  /* relift: cmp dword ptr [ebp + 0x18], 4 -> jne 0x1d1f01 */
  /* relift: cmp dword ptr [ebp - 0x10], 1 -> jne 0x1d1f01 */
  SetLastError(ebx);
  SetLastError(0);
  XapiSetLastNTError(0);
  /* cmp esi, edi -> jge 0x1d2023 */
  /* cmp eax, 3 -> jne 0x1d211f */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* relift: cmp eax, dword ptr [ebp + 0x34] -> jg 0x1d2153 */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* cmp eax, 3 -> jne 0x1d212e */
  /* cmp eax, edi -> je 0x1d205a */
  /* cmp eax, edi -> jne 0x1d214e */
  /* relift: cmp eax, dword ptr [ebp + 0x34] -> jl 0x1d2097 */
  /* relift: cmp eax, dword ptr [ebp + 0x30] -> jb 0x1d2097 */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* cmp esi, edi -> jge 0x1d21de */
  XapiSetLastNTError(0);
  FUN_001d1f10();
  /* cmp (char)eax, 2 -> jae 0x1d223d */
  /* relift: cmp dword ptr [eax + 0x28], 0 -> je 0x1d223d */
  /* cmp (char)eax, 2 -> jae 0x1d2252 */
  /* cmp (char)eax, 2 -> jae 0x1d227a */
  SetLastError(edx);
  /* test eax, eax -> jge 0x1d22dd */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 8], -1 -> je 0x1d231f */
  /* test eax, eax -> jge 0x1d2331 */
  XapiSetLastNTError(0);
  /* test esi, esi -> jne 0x1d231b */
  /* test esi, esi -> je 0x1d2331 */
  XapiSetLastNTError(0xc000000d);
  /* test eax, eax -> jge 0x1d2361 */
  XapiSetLastNTError(0);
  FUN_001d4436();
  /* cmp eax, ecx -> je 0x1d23bb */
  /* cmp eax, ecx -> jne 0x1d23cd */
  SetLastError(ecx);
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [esi], 0x103 -> jne 0x1d241e */
  /* relift: cmp dword ptr [esp + 0x14], 0 -> je 0x1d2402 */
  /* test eax, eax -> jne 0x1d23f8 */
  WaitForSingleObject(0, 0);
  /* cmp eax, 0x102 -> jne 0x1d241a */
  SetLastError(996);
  /* test eax, eax -> jne 0x1d2438 */
  /* test esi, esi -> jl 0x1d2432 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jne 0x1d2475 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d248c */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d250f */
  FUN_001d789a((char *)(uintptr_t)ebx, (char *)(uintptr_t)0, 519);
  /* test (char)ecx, (char)ecx -> jne 0x1d24ee */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)0, 0);
  /* test ecx, ecx -> je 0x1d2574 */
  /* cmp eax, 2 -> je 0x1d253d */
  /* cmp eax, 3 -> je 0x1d253d */
  /* relift: cmp ecx, dword ptr [edx + 8] -> jne 0x1d2574 */
  /* test eax, eax -> je 0x1d2596 */
  FUN_001d243e();
  /* test eax, eax -> jl 0x1d25d5 */
  /* test eax, eax -> je 0x1d25cd */
  /* cmp esi, ebx -> je 0x1d2612 */
  /* cmp (char)eax, 0x44 -> je 0x1d25fe */
  /* cmp (char)eax, 0x64 -> jne 0x1d260a */
  /* relift: cmp byte ptr [esi + 1], 0x3a -> jne 0x1d260a */
  /* relift: cmp byte ptr [esi + 2], 0x5c -> je 0x1d2631 */
  /* cmp eax, ebx -> jl 0x1d26b4 */
  /* cmp ecx, eax -> ja 0x1d269e */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)(uintptr_t)eax, 0);
  /* cmp (char)ecx, (char)ebx -> jne 0x1d26b6 */
  FUN_001d259b();
  /* relift: cmp word ptr [edi], (int16_t)esi -> jne 0x1d270f */
  /* relift: cmp dword ptr [ebp - 0x1c], 0xd48 -> je 0x1d2791 */
  /* relift: cmp dword ptr [ebp - 0xc], esi -> jl 0x1d2911 */
  FUN_001d7a59();
  /* relift: cmp eax, dword ptr [edi - 4] -> jne 0x1d27d5 */
  __wcsicmp((wchar_t *)0, (wchar_t *)(uintptr_t)edi);
  /* relift: cmp dword ptr [ebp - 8], 0x32 -> jb 0x1d27af */
  /* relift: cmp dword ptr [ebp + 0xc], esi -> jne 0x1d2801 */
  FUN_001d7a59();
  /* cmp ecx, 0x32 -> jne 0x1d2810 */
  /* relift: cmp dword ptr [ebp - 0x10], esi -> jne 0x1d2840 */
  /* cmp ecx, esi -> jne 0x1d2844 */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax);
  /* cmp ecx, esi -> je 0x1d2867 */
  /* cmp ecx, eax -> jae 0x1d284d */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, eax);
  FUN_001d7a59();
  /* relift: cmp dword ptr [ebp - 0xc], esi -> jge 0x1d28d2 */
  /* cmp edi, esi -> jl 0x1d2903 */
  FUN_001d7a59();
  /* cmp eax, 0xc0000034 -> je 0x1d2882 */
  /* relift: cmp word ptr [eax], (int16_t)edi -> je 0x1d29bc */
  _wcslen((wchar_t *)(uintptr_t)eax);
  /* cmp eax, edi -> je 0x1d2978 */
  /* relift: cmp edx, dword ptr [ecx + esi + 0xc] -> jne 0x1d29bc */
  /* relift: cmp dword ptr [esi + 4], edi -> jbe 0x1d29b0 */
  __wcsicmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ebx);
  /* relift: cmp edi, dword ptr [esi + 4] -> jb 0x1d2987 */
  /* relift: cmp dword ptr [esi + 8], 0 -> jne 0x1d29ce */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d29ce */
  /* relift: cmp dword ptr [esi + 4], 0x32 -> jb 0x1d2945 */
  _wcscpy();
  /* cmp eax, edi -> jl 0x1d2ac5 */
  FUN_001d0bb9(edi, 3412);
  /* cmp esi, edi -> je 0x1d2a7f */
  /* relift: cmp dword ptr [ebp - 8], ebx -> je 0x1d2a86 */
  FUN_001d292e();
  /* test eax, eax -> jne 0x1d2aac */
  /* relift: cmp dword ptr [ebp + 8], edi -> jge 0x1d2abd */
  /* cmp esi, edi -> je 0x1d2ac5 */
  LocalFree((void *)(uintptr_t)esi);
  /* cmp esi, edi -> je 0x1d2ac5 */
  /* cmp eax, 9 -> jg 0x1d2ae1 */
  __allmul();
  __aullrem();
  __aullshr();
  FUN_001d2ad3();
  /* cmp ebx, 0x2c -> jle 0x1d2b4c */
  SetFilePointer(0, 0, (void *)0, 0);
  ReadFile(0, (void *)(uintptr_t)eax, 0, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1d2baa */
  /* relift: cmp dword ptr [ebp - 8], 2 -> je 0x1d2bb6 */
  /* relift: cmp word ptr [ebp - 4], 0xfeff -> je 0x1d2bb6 */
  _wcslen((wchar_t *)(uintptr_t)0);
  /* relift: cmp dword ptr [ebp - 8], ebx -> jne 0x1d2c1a */
  ReadFile(0, (void *)(uintptr_t)edi, eax, (void *)0, (void *)0);
  /* test eax, eax -> je 0x1d2d3e */
  /* relift: cmp dword ptr [ebp - 0xc], ebx -> je 0x1d2d3e */
  _wcsstr((wchar_t *)(uintptr_t)eax, (wchar_t *)0x002c1cb8);
  /* cmp eax, ebx -> jae 0x1d2c96 */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, esi);
  _wcsstr((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  /* relift: cmp word ptr [ecx + eax], 0x3d -> jne 0x1d2ce5 */
  _wcsstr((wchar_t *)(uintptr_t)edi, (wchar_t *)0x002c1cb8);
  /* cmp edi, eax -> jl 0x1d2d02 */
  _wcsncpy((wchar_t *)(uintptr_t)0, (wchar_t *)0, edi);
  /* cmp esi, ebx -> jae 0x1d2d37 */
  SetFilePointer(0, 0, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x1d2d64 */
  /* test dl, dl -> jne 0x1d2d6e */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d82 */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d98 */
  /* cmp edi, 0x103 -> jae 0x1d2dbf */
  /* cmp edi, 0xf7 -> jge 0x1d2e3e */
  /* test dl, dl -> jne 0x1d2dd9 */
  CreateFileA((char *)(uintptr_t)eax, 0x80000000, 0, 0, 0, ebx, 0);
  FUN_001d2b79();
  FUN_001d2bbd();
  CloseHandle(0);
  CreateFileA((char *)0, 0x80100000, esi, esi, 0, 0, esi);
  /* cmp edi, -1 -> je 0x1d2eb7 */
  FUN_001d2b79();
  /* test eax, eax -> je 0x1d2eaa */
  FUN_001d2bbd();
  /* test eax, eax -> je 0x1d2eaa */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  CloseHandle(0);
  xapi_GetLastError();
  CreateFileA((char *)0, 0xc0000000, 0, 0, 0, 0x02000000, 0);
  /* cmp esi, -1 -> je 0x1d2f1d */
  CloseHandle(0);
  /* test (char)ecx, (char)ecx -> jne 0x1d2f36 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f49 */
  FUN_001d2ae7();
  /* test dl, dl -> jne 0x1d2f73 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f97 */
  FUN_001d2e48();
  /* test eax, eax -> je 0x1d3135 */
  CreateDirectoryA((char *)(uintptr_t)eax, 0);
  /* test eax, eax -> jne 0x1d303e */
  xapi_GetLastError();
  /* test (char)ecx, (char)ecx -> jne 0x1d2ff3 */
  FUN_001d2e48();
  /* test ebx, ebx -> jne 0x1d3039 */
  FUN_001d2ec6();
  /* relift: cmp dword ptr [ebp + 0x10], 1 -> je 0x1d302f */
  /* test ebx, ebx -> je 0x1d3135 */
  /* test (char)ecx, (char)ecx -> jne 0x1d304e */
  /* test eax, eax -> jge 0x1d30bf */
  FUN_001dd6f5();
  _wcslen((wchar_t *)(uintptr_t)eax);
  WriteFile(0, (void *)(uintptr_t)eax, esi, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1d3163 */
  CloseHandle(0);
  /* test esi, esi -> je 0x1d315c */
  FUN_001d789a((char *)(uintptr_t)esi, (char *)(uintptr_t)eax, 0);
  /* cmp edi, ebx -> jae 0x1d315c */
  xapi_GetLastError();
  CloseHandle(0);
  FUN_001d347c((char *)(uintptr_t)eax);
  /* test (char)ecx, (char)ecx -> jne 0x1d31a6 */
  /* test (char)eax, (char)eax -> jne 0x1d31be */
  /* test (char)ecx, (char)ecx -> jne 0x1d31d1 */
  FUN_001d2ae7();
  /* test dl, dl -> jne 0x1d31fb */
  /* test (char)ecx, (char)ecx -> jne 0x1d3216 */
  FUN_001d2e48();
  FUN_001d7cb4((void *)(uintptr_t)eax);
  /* test (char)ecx, (char)ecx -> jne 0x1d3268 */
  /* test (char)ecx, (char)ecx -> jne 0x1d327b */
  /* test dl, dl -> jne 0x1d3297 */
  FUN_001d3576();
  /* cmp edi, -1 -> je 0x1d3352 */
  FUN_001d2d48();
  /* test eax, eax -> jne 0x1d330a */
  FUN_001d3683();
  FUN_001d2d48();
  /* test eax, eax -> jne 0x1d32f4 */
  FUN_001d3683();
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d330a */
  CloseHandle(0);
  SetLastError(0);
  /* cmp edi, -1 -> je 0x1d3352 */
  FUN_001d0bb9(0, 272);
  /* test esi, esi -> je 0x1d3342 */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)0, 260);
  CloseHandle(0);
  SetLastError(0);
  FUN_001d3683();
  /* test edi, edi -> je 0x1d339b */
  FUN_001d2d48();
  /* test eax, eax -> jne 0x1d339a */
  FUN_001d3683();
  /* test edi, edi -> jne 0x1d3377 */
  /* cmp edx, 0x53425645 -> je 0x1d33d4 */
  /* cmp edx, 0xbe4bea00 -> jne 0x1d33e2 */
  LocalFree((void *)(uintptr_t)ecx);
  CloseHandle(0);
  LocalFree((void *)(uintptr_t)ecx);
  /* test eax, eax -> jl 0x1d3470 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d34cf */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d34fd */
  XapiSetLastNTError(0);
  /* relift: cmp byte ptr [edx + eax - 1], 0x5c -> je 0x1d35b9 */
  /* cmp (int16_t)ecx, (int16_t)edi -> je 0x1d3673 */
  /* cmp (int16_t)ecx, 3 -> jne 0x1d3600 */
  /* relift: cmp byte ptr [edx], 0x2a -> jne 0x1d3600 */
  /* relift: cmp byte ptr [edx + 1], 0x2e -> jne 0x1d3600 */
  /* relift: cmp byte ptr [edx + 2], 0x2a -> jne 0x1d3600 */
  /* cmp eax, edi -> jge 0x1d3625 */
  /* cmp esi, edi -> jge 0x1d365f */
  XapiSetLastNTError(0);
  FUN_001d350a();
  SetLastError(87);
  XapiSetLastNTError(0);
  FUN_001d350a();
  /* test esi, esi -> jne 0x1d3710 */
  SetLastError(0);
  /* relift: cmp dword ptr [esp + 8], 0 -> je 0x1d372a */
  /* test eax, eax -> jge 0x1d37a0 */
  XapiSetLastNTError(0);
  xapi_GetLastError();
  /* cmp eax, 2 -> jne 0x1d3799 */
  SetLastError(0);
  /* test esi, esi -> jge 0x1d37cf */
  XapiSetLastNTError(0);
  __allmul();
  __allmul();
  /* test ecx, ecx -> je 0x1d3808 */
  /* test ecx, ecx -> je 0x1d3814 */
  /* test eax, eax -> je 0x1d3823 */
  FUN_001dd5c8();
  /* cmp eax, ebx -> jge 0x1d38a4 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jne 0x1d38b3 */
  /* relift: cmp dword ptr [ebp + 0x14], ebx -> je 0x1d38e3 */
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> je 0x1d38bb */
  FUN_001d5c66();
  /* cmp eax, ebx -> jne 0x1d38e3 */
  /* relift: cmp dword ptr [ebp + 0x20], ebx -> jne 0x1d38f7 */
  /* relift: cmp dword ptr [ebp + 0x18], ebx -> jne 0x1d38f2 */
  /* relift: cmp dword ptr [ebp + 0x1c], ebx -> je 0x1d3941 */
  /* relift: cmp dword ptr [ebp + 0x20], ebx -> je 0x1d38ff */
  FUN_001d5c66();
  /* cmp edi, ebx -> jne 0x1d3944 */
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> je 0x1d3937 */
  FUN_001d6ca8();
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> je 0x1d3968 */
  /* cmp eax, ebx -> jl 0x1d3984 */
  /* cmp edi, ebx -> je 0x1d3992 */
  /* cmp eax, ebx -> jge 0x1d3992 */
  XapiSetLastNTError(0);
  /* cmp esi, ebx -> je 0x1d39c2 */
  /* relift: cmp eax, dword ptr [ebp + 0x10] -> jae 0x1d39de */
  memmove((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 0);
  /* cmp eax, ebx -> je 0x1d39d1 */
  /* relift: cmp dword ptr [ebp + 0x20], ebx -> je 0x1d3a06 */
  /* relift: cmp eax, dword ptr [ebp + 0x24] -> jb 0x1d39ed */
  SetLastError(24);
  memmove((void *)(uintptr_t)0, (void *)(uintptr_t)eax, eax);
  /* cmp eax, ebx -> je 0x1d3a12 */
  /* cmp eax, ebx -> je 0x1d3a1d */
  /* relift: FUN_001d3a62(0, 0); */
  __SEH_epilog();
  XapiSetLastNTError(0xc0000005);
  __local_unwind2();
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> je 0x1d3a7f */
  FUN_001d6ca8();
  /* cmp edi, ebx -> je 0x1d3a90 */
  FUN_001d6ca8();
  /* relift: cmp dword ptr [ebp - 0x34], esi -> jne 0x1d3b43 */
  /* relift: cmp dword ptr [ebp - 0x228], ebx -> je 0x1d3b63 */
  /* cmp eax, 0x29 -> jbe 0x1d3b7b */
  /* test eax, eax -> jbe 0x1d3ba0 */
  /* relift: cmp ebx, dword ptr [edx] -> jne 0x1d3b98 */
  /* relift: cmp dword ptr [edx + 8], 0 -> jne 0x1d3c75 */
  /* cmp ecx, eax -> jb 0x1d3b87 */
  /* test eax, eax -> jbe 0x1d3bd3 */
  /* relift: cmp dword ptr [ecx + 4], 0 -> je 0x1d3bbb */
  /* relift: cmp dword ptr [ecx], esi -> je 0x1d3bc3 */
  /* cmp edx, eax -> jb 0x1d3bb1 */
  /* cmp edx, eax -> jne 0x1d3bca */
  /* cmp esi, eax -> jb 0x1d3ba9 */
  /* test edi, edi -> jne 0x1d3be0 */
  /* cmp edi, ecx -> jb 0x1d3bea */
  /* test ebx, ebx -> je 0x1d3c20 */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, eax);
  XapiSelectCachePartition();
  /* test eax, eax -> jl 0x1d3d6f */
  /* relift: cmp dword ptr [ebp + 8], 0 -> jne 0x1d3cc9 */
  /* relift: cmp dword ptr [ebp - 0xc], 0 -> jne 0x1d3cc9 */
  snprintf((char *)(uintptr_t)eax, 260, (char *)0x002c1de8);
  /* test ebx, ebx -> je 0x1d3d1f */
  XapiFormatFATVolume(0);
  /* test esi, esi -> je 0x1d3d77 */
  FUN_001d7d21((void *)(uintptr_t)eax);
  /* test edi, edi -> jge 0x1d3d4e */
  /* test ebx, ebx -> jne 0x1d3d4a */
  XapiFormatFATVolume(0);
  /* test eax, eax -> je 0x1d3d4a */
  FUN_001d7d21((void *)(uintptr_t)eax);
  /* test edi, edi -> jl 0x1d3d5f */
  /* test esi, esi -> jne 0x1d3d77 */
  XapiSetLastNTError(0);
  /* test edx, edx -> je 0x1d3dcd */
  /* relift: cmp dword ptr [ebp + 0xc], edx -> je 0x1d3dbe */
  /* cmp edi, 0x10 -> jb 0x1d3daa */
  /* cmp edi, esi -> jb 0x1d3dd5 */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e30);
  /* cmp eax, edi -> jge 0x1d3e2a */
  /* cmp esi, edi -> jge 0x1d3e5c */
  /* cmp eax, 9 -> jb 0x1d3edb */
  /* relift: cmp byte ptr [ebp + eax - 0x241], 0x5c -> jne 0x1d3edb */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e28);
  XapiMapLetterToDirectory();
  /* cmp eax, edi -> jl 0x1d3e1e */
  /* cmp (char)ebx, 0x55 -> je 0x1d3e1e */
  /* relift: relift: mov byte ptr [0x4ee168], (char)ebx */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e30);
  /* relift: cmp byte ptr [ebp + 8], 0x58 -> jne 0x1d3f37 */
  /* test eax, eax -> jl 0x1d3f37 */
  /* test eax, eax -> jge 0x1d3fa6 */
  XapiSetLastNTError(0);
  xapi_GetLastError();
  /* cmp eax, 2 -> jne 0x1d3fa2 */
  SetLastError(0);
  /* test esi, esi -> jge 0x1d3fd5 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d4045 */
  XapiSetLastNTError(0);
  xapi_GetLastError();
  /* cmp eax, 2 -> jne 0x1d4041 */
  SetLastError(0);
  /* test esi, esi -> jge 0x1d4074 */
  XapiSetLastNTError(0);
  /* relift: test dword ptr [0x4ee16c], edx -> jne 0x1d409e */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e30);
  /* cmp eax, 0x20 -> jb 0x1d4132 */
  FUN_001d7a59();
  /* relift: cmp dword ptr [ebp + 0xc], 0x40 -> jbe 0x1d416a */
  /* cmp eax, 0x10 -> jb 0x1d4191 */
  XcSHAInit(0);
  XcSHAUpdate(0, 0, 64);
  /* relift: cmp dword ptr [ebp + 0x10], eax -> jbe 0x1d41cf */
  /* cmp eax, 0x10 -> jb 0x1d41f4 */
  XcSHAFinal(0, 0);
  XcSHAInit(0);
  XcSHAUpdate(0, 0, 84);
  XcSHAFinal(0, 0);
  FUN_001d4157();
  XcSHAUpdate(0, 0, 20);
  FUN_001d41be();
  FUN_001d0bb9(0, 124);
  /* test esi, esi -> jne 0x1d4287 */
  SetLastError(0);
  FUN_001d4157();
  XcSHAUpdate(0, 0, 0);
  /* test eax, eax -> je 0x1d4306 */
  /* test esi, esi -> je 0x1d42e4 */
  FUN_001d41be();
  /* test esi, esi -> je 0x1d4306 */
  FUN_001d4230();
  LocalFree((void *)(uintptr_t)edi);
  xapi_GetLastError();
  /* test eax, eax -> je 0x1d4342 */
  XapiInitProcess();
  /* test eax, eax -> je 0x1d435f */
  /* test ecx, ecx -> je 0x1d438c */
  _rtinit();
  _cinit();
  main(0, (const char **)(uintptr_t)0, (const char **)(uintptr_t)0);
  XapiBootToDash();
  /* mem[0x00632a30] = eax */
  CreateThread((void *)(uintptr_t)esi, 0, (void *)0x001d4345, (void *)(uintptr_t)esi, 0, (void *)(uintptr_t)esi);
  /* cmp edi, esi -> jne 0x1d4405 */
  XapiBootToDash();
  CloseHandle(0);
  /* cmp eax, -1 -> jne 0x1d4443 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1e6ae0 */
void D3DDevice_CreateTexture(uint32_t width, uint32_t height, uint32_t levels, uint32_t usage, uint32_t format, uint32_t pool, void *out_texture)
{
  D3D_CreateTexture();
  D3D_CreateTexture();
  D3D_CreateTexture();
  /* relift: FUN_001ef330(0, 0, 0, 0); */
  /* relift: FUN_001ef330(0, 0, 0, 0); */
  D3DDevice_SetRenderStateNotInline();
}

/* 0x1e6bd0 */
void D3DDevice_SetTransform(uint32_t type, void *matrix)
{
  int edx = 0;
  int esi = 0;

  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: cmp dword ptr [edx + 0x3c], esi -> jne 0x1e6cc2 */
  D3D_UpdateProjectionViewportTransform();
  /* relift: FUN_001eb6f0(0, 0); */

  (void)edx;
  (void)esi;
}

/* 0x1e6ce0 */
void D3DDevice_GetTransform(uint32_t type, void *matrix_out)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: FUN_001f2340(0, 0, 0); */
  D3DDevice_SetTransform(esi, (void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1e6e8f */
  /* cmp eax, ecx -> je 0x1e6e9c */
  /* test eax, eax -> jne 0x1e6e81 */
  /* relift: cmp eax, dword ptr [0x1fbb14] -> jae 0x1e6ef5 */
  /* mem[0x001fbb10] = eax */
  CDevice_MakeSpace();
  /* cmp eax, 1 -> jne 0x1e6f7e */
  /* relift: FUN_001f3a90(0, 0); */
  /* mem[0x001fe6a4] = eax */
  /* mem[0x001fe6a0] = eax */
  D3D_BlockOnTime(eax, 0);
  /* test eax, eax -> jne 0x1e7004 */
  /* test ecx, ecx -> je 0x1e707e */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_Clear(edx, (void *)(uintptr_t)ecx, eax, edx, 0.0f, eax);
  D3DDevice_SetViewport((void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1e7110 */
void D3DDevice_BlockUntilVerticalBlank(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  D3DDevice_SetRenderStateNotInline();
  /* test edi, edi -> je 0x1e719d */
  /* test edi, edi -> je 0x1e71da */
  /* test edi, edi -> je 0x1e71ef */
  /* test ecx, ecx -> je 0x1e7255 */
  /* test edi, edi -> je 0x1e727d */
  /* cmp eax, ecx -> je 0x1e733e */
  /* cmp eax, ecx -> jbe 0x1e7307 */
  /* cmp eax, 3 -> jae 0x1e7332 */
  /* mem[0xfd680844] = eax */
  /* mem[0xfd680844] = eax */
  /* mem[0x001fb454] = ecx */
  /* mem[0x001fb450] = ecx */
  /* mem[0x001fb450] = 1 */
  /* test eax, eax -> jne 0x1e7351 */
  D3D_SetFence();
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3d90(0); */
  /* test eax, eax -> jne 0x1e775e */
  /* test eax, eax -> jne 0x1e778c */
  /* test ecx, ecx -> jne 0x1e77bb */
  /* test eax, eax -> jne 0x1e7825 */
  /* cmp eax, 0xc -> je 0x1e781e */
  /* cmp eax, 0xd -> jle 0x1e780a */
  /* cmp eax, 0xf -> jg 0x1e780a */
  /* relift: FUN_001f3d90(0, 0); */
  /* cmp edx, eax -> jbe 0x1e786d */
  /* cmp edx, ecx -> jbe 0x1e7879 */
  /* relift: FUN_001ef590(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001efe30(0, 0); */
  /* test eax, eax -> je 0x1e79c4 */
  /* relift: FUN_001f4840(0); */
  D3D_KickOffAndWaitForIdle();
  CMiniport_IsFlipPending();
  /* test eax, eax -> jne 0x1e7a45 */
  CDevice_FreeFrameBuffers();
  CDevice_InitializeFrameBuffers();
  /* test ebx, ebx -> jge 0x1e7a79 */
  CDevice_FreeFrameBuffers();
  /* relift: FUN_001e77d0(0); */
  /* relift: FUN_001f4918(0, 0, 0, 0); */
  /* test eax, eax -> je 0x1e7ab6 */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)edi, (void *)0);
  D3DDevice_Clear(0, (void *)0, 0, 0, 0.0f, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x1e7af0 */
void D3DDevice_SetRenderTarget(void *render_target, void *depth_stencil)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  /* test eax, eax -> jne 0x1e7b28 */
  /* test eax, eax -> jne 0x1e7b50 */
  /* relift: FUN_001e77d0(0); */
  /* test (char)ecx, 0x30 -> je 0x1e7b97 */
  /* test (char)ecx, 0x10 -> je 0x1e7b97 */
  /* test esi, esi -> je 0x1e7ba5 */
  /* relift: FUN_001e77d0(0); */
  /* relift: FUN_001ed8b0(0); */
  /* test eax, eax -> je 0x1e7bd2 */
  /* test ecx, ecx -> je 0x1e7bc0 */
  /* relift: FUN_001edba0(0); */
  /* test ecx, ecx -> je 0x1e7beb */
  /* relift: FUN_001edba0(0); */
  /* relift: FUN_001ed8b0(0); */
  /* relift: FUN_001f3f80(0, 0); */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1e7c2f */
  /* relift: FUN_001e9f80(0, 0); */
  /* test eax, eax -> je 0x1e7c93 */
  /* test eax, eax -> je 0x1e7c93 */
  /* test eax, eax -> je 0x1e7cb9 */
  /* test eax, eax -> je 0x1e7cb9 */
  /* test (char)eax, 1 -> je 0x1e7cf2 */
  /* cmp ebp, ecx -> jne 0x1e7cf2 */
  /* relift: FUN_001e9fe0(0, 0); */
  /* relift: FUN_001eb6f0(0, 0); */
  D3DDevice_SetViewport((void *)(uintptr_t)ecx);
  D3DDevice_SetRenderStateNotInline();

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1e7d50 */
int D3DDevice_GetBackBuffer(int back_buffer, uint32_t type, void **out_surface)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> je 0x1e7d6b */
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp eax, dword ptr [ecx + 0x21b8] -> jae 0x1e7dc1 */
  /* relift: FUN_001e77d0(0, 0); */
  /* relift: FUN_001e77d0(0); */
  /* relift: FUN_001f3d90(0); */
  /* test (char)eax, (char)eax -> jne 0x1e7e42 */
  /* test eax, eax -> je 0x1e7ea8 */
  /* relift: FUN_001e7830(0); */
  /* test eax, eax -> je 0x1e7ee0 */
  /* test eax, eax -> je 0x1e7f76 */
  /* cmp eax, edi -> jb 0x1e7f82 */
  /* test eax, eax -> je 0x1e7fc3 */
  /* test edi, edi -> jbe 0x1e7fc3 */
  /* relift: FUN_001f55d0(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x1e7eb0 */
  /* test eax, eax -> je 0x1e802e */
  /* relift: FUN_001e7830(0); */
  /* relift: FUN_001f3d90(0, 0); */
  /* cmp ecx, eax -> jbe 0x1e814b */
  /* cmp ecx, eax -> jbe 0x1e815a */
  /* cmp edx, edi -> jne 0x1e818a */
  /* cmp eax, ebx -> jne 0x1e818a */
  /* relift: cmp esi, dword ptr [esp + 0x24] -> jne 0x1e818a */
  /* cmp edx, ecx -> jbe 0x1e81a9 */
  /* cmp eax, ecx -> jbe 0x1e81b6 */
  /* cmp esi, ecx -> jbe 0x1e81bb */
  /* relift: test byte ptr [esi + 0xc], 4 -> je 0x1e8229 */
  /* relift: FUN_001f5480(0); */
  /* relift: FUN_001f5480(0); */
  /* relift: FUN_001ed8f0(0); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1e8270 */
int D3DDevice_GetDepthStencilSurface(void **out_surface)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: FUN_001ed8f0(0); */
  /* test eax, eax -> jne 0x1e8309 */
  /* cmp edx, edi -> jb 0x1e833e */
  /* test eax, eax -> jne 0x1e8335 */
  /* test eax, eax -> jne 0x1e8356 */
  /* cmp ecx, edi -> jae 0x1e836f */
  /* test eax, eax -> jne 0x1e8388 */
  D3D_UpdateProjectionViewportTransform();
  D3DDevice_SetScissors();
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  FUN_001d0bb9(0, eax);
  /* test ebx, ebx -> jne 0x1e8450 */
  /* test ecx, ecx -> je 0x1e8483 */
  LocalFree((void *)(uintptr_t)eax);
  /* relift: FUN_001f2600(0, 0); */
  /* relift: cmp dword ptr [ebx], 2 -> jne 0x1e85c3 */
  /* relift: FUN_001f2440(0, 0, 0); */
  /* relift: FUN_001f3c40(0, 0); */
  /* relift: FUN_001f3c40(0, 0); */
  /* test (char)eax, 1 -> jne 0x1e85a0 */
  /* relift: FUN_001f25c0(0, 0); */
  /* relift: cmp ebx, dword ptr [esi + 0x484] -> jae 0x1e860a */
  /* relift: test byte ptr [ecx + eax + 0x68], 1 -> jne 0x1e8650 */
  D3DDevice_SetLight();
  /* cmp eax, ecx -> je 0x1e868a */
  /* test eax, eax -> jne 0x1e8678 */
  /* test eax, eax -> je 0x1e86b0 */
  /* test eax, eax -> je 0x1e86ea */
  /* relift: FUN_001ed8f0(0); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1e8700 */
void D3DDevice_SetTexture(uint32_t stage, void *texture)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  D3D_DestroyResource((void *)(uintptr_t)eax);
  XMETAL_StartPush();
  /* relift: FUN_001ed8b0(0, 0); */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1e87ff */
  /* relift: FUN_001e77d0(0); */
  /* cmp eax, ebp -> je 0x1e884e */
  /* test eax, eax -> je 0x1e888a */
  /* relift: FUN_001ed8f0(0); */
  /* test eax, eax -> je 0x1e88df */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* relift: FUN_001ed8b0(0, 0); */
  XMETAL_StartPush();
  /* test edi, edi -> je 0x1e8940 */
  /* relift: FUN_001ed8b0(0); */
  /* mem[0x001fb494] = eax */
  /* mem[0x001fb494] = 0 */
  /* test eax, eax -> je 0x1e8998 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x1e89df */
  /* relift: FUN_001ed8f0(0); */
  /* test eax, 0xfffffff -> je 0x1e8a26 */
  XMETAL_StartPush();
  /* relift: FUN_001e6fc0(0, 0); */
  /* test esi, esi -> jne 0x1e8a8a */
  XMETAL_StartPush();
  CDevice_KickOff();
  /* relift: test dword ptr [eax + 0x2510], 0x1200000 -> je 0x1e8b06 */
  XMETAL_StartPush();
  /* test esi, esi -> jne 0x1e8b63 */
  XMETAL_StartPush();
  /* relift: FUN_001ef590(0, 0x00400480, 0); */
  /* relift: FUN_001ef590(0, 0x00400680, 0); */
  /* test esi, esi -> je 0x1e8bbc */
  /* relift: FUN_001efe30(0); */
  /* relift: FUN_001ef590(0, 0, 0); */
  /* test eax, eax -> je 0x1e8cac */
  /* test edi, edi -> jbe 0x1e8cac */
  /* relift: FUN_001ef590(0, 0x00400680, 0); */
  XMETAL_StartPush();
  /* relift: cmp dword ptr [esi + 4], eax -> je 0x1e8db4 */
  /* relift: FUN_001f5e85(0, 0); */
  /* relift: FUN_001f6073(0, 0); */
  /* test esi, esi -> je 0x1e8e79 */
  /* cmp esi, ecx -> jae 0x1e8e4e */
  /* cmp eax, ecx -> jae 0x1e8e72 */
  /* test esi, esi -> jne 0x1e8e30 */
  /* test esi, esi -> je 0x1e8f09 */
  /* cmp esi, ecx -> jae 0x1e8ede */
  /* cmp eax, ecx -> jae 0x1e8f02 */
  /* test esi, esi -> jne 0x1e8ec0 */
  D3D_KickOffAndWaitForIdle();
  /* cmp ebx, ecx -> jae 0x1e8f90 */
  /* cmp edx, ecx -> jae 0x1e8fc0 */
  /* test ecx, ecx -> je 0x1e8fb2 */
  /* test ebx, ebx -> jne 0x1e8f73 */
  XMETAL_StartPush();
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* test eax, eax -> jne 0x1e91c7 */
  CMiniport_IsFlipPending();
  /* test eax, eax -> jne 0x1e91d0 */
  /* test eax, eax -> jne 0x1e9222 */
  /* relift: FUN_001ef3d0(0, 0, 0, 0); */
  /* test eax, eax -> jl 0x1e92ab */
  D3DDevice_CopyRects();
  D3D_KickOffAndWaitForIdle();
  /* relift: FUN_001e77d0(0, 0); */
  /* relift: FUN_001f3cd0(0, 0); */
  /* test esi, esi -> jne 0x1e9260 */
  /* mem[0x0033026c] = eax */
  /* mem[0x00330270] = ecx */
  /* mem[0x00330274] = edx */
  /* mem[0x00330278] = eax */
  /* mem[0x001fb8b0] = ecx */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* mem[0x001fb868] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1e9350 */
void D3DDevice_SetRenderState_Simple(uint32_t reg, uint32_t value)
{
  int eax = 0;

  /* relift: cmp eax, dword ptr [0x1fbb14] -> jae 0x1e936c */
  /* mem[0x001fbb10] = eax */
  CDevice_MakeSpace();

  (void)eax;
}

/* 0x1e9380 */
void D3DDevice_SetRenderState_Deferred(uint32_t reg_index, uint32_t value)
{
  int esi = 0;
  int edi = 0;

  /* cmp esi, 0x52 -> jge 0x1e93c9 */
  D3DDevice_SetRenderState_Simple(edi, 0);
  /* cmp esi, 0x74 -> jge 0x1e93ea */
  D3DDevice_SetRenderStateNotInline();

  (void)esi;
  (void)edi;
}

/* 0x1e9410 */
void D3DDevice_SetTextureStageState(uint32_t stage, uint32_t state, uint32_t value)
{
  int ecx = 0;
  int esi = 0;

  /* mem[0x001fbb18] = esi */
  /* relift: FUN_001f3c30(0, 0); */
  XMETAL_StartPush();
  /* mem[0x001fb8a4] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb8b4] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb870] = ecx */

  (void)ecx;
  (void)esi;
}

/* 0x1e96d0 */
void D3DDevice_SetRenderState_CullMode(uint32_t mode)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  XMETAL_StartPush();
  /* mem[0x001fb894] = ecx */
  /* mem[0x001fb894] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb890] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb880] = ecx */
  /* test eax, eax -> jne 0x1e97ef */
  XMETAL_StartPush();
  /* mem[0x001fb898] = eax */
  /* mem[0x001fb898] = eax */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edi, 0x1ff -> jbe 0x1e983f */
  XMETAL_StartPush();
  /* mem[0x001fb8b8] = ebx */
  /* cmp dl, 0x20 -> jne 0x1e9889 */
  /* cmp edi, ecx -> je 0x1e98cb */
  XMETAL_StartPush();
  /* mem[0x001fb8bc] = ebx */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  /* mem[0x001fb89c] = edi */
  XMETAL_StartPush();
  /* test ecx, ecx -> jne 0x1e998d */
  /* mem[0x001fb8a0] = ecx */
  /* mem[0x001fb8a0] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb874] = ecx */
  /* mem[0x001fb878] = eax */
  XMETAL_StartPush();
  /* mem[0x001fb874] = esi */
  /* mem[0x001fb87c] = eax */
  XMETAL_StartPush();
  /* mem[0x001fb874] = esi */
  XMETAL_StartPush();
  /* mem[0x001fb86c] = ecx */
  /* test ecx, ecx -> je 0x1e9b22 */
  /* cmp ecx, 0x10000 -> jne 0x1e9b44 */
  /* cmp ecx, 0x30000 -> je 0x1e9b52 */
  /* cmp ecx, 0x40000 -> je 0x1e9b4b */
  /* test edx, edx -> jne 0x1e9b6e */
  /* test eax, eax -> je 0x1e9b6e */
  XMETAL_StartPush();
  XMETAL_StartPush();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1e9c20 */
void D3DDevice_SetTextureState_BorderColor(uint32_t stage, uint32_t color)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  XMETAL_StartPush();
  XMETAL_StartPush();
  /* cmp eax, 0x1c -> jne 0x1e9cf9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp eax, 0x1d -> jne 0x1e9d10 */
  /* relift: tail-call D3DDevice_SetTextureState_BorderColor(); */
  /* cmp eax, 0x1e -> jne 0x1e9d27 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp eax, 0x1b -> jg 0x1e9cdf */
  /* relift: cmp dword ptr [0x1fb8a8], edx -> je 0x1e9e3c */
  /* relift: test byte ptr [esi + 4], 6 -> je 0x1e9f34 */
  /* relift: test dword ptr [ecx + 0xc], 0x200 -> jne 0x1e9f18 */
  /* test esi, esi -> jge 0x1e9e6f */
  /* relift: cmp dword ptr [0x1fb884], 2 -> jne 0x1e9fa3 */
  /* test eax, eax -> je 0x1e9fcb */
  /* cmp eax, 0x2d -> je 0x1e9fc5 */
  /* cmp eax, 0x2b -> je 0x1e9fc5 */
  /* cmp eax, 0x31 -> je 0x1e9fc5 */
  /* cmp eax, 0x2f -> jne 0x1e9fcb */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x30 -> je 0x1ea08f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1ea080 */
  /* relift: FUN_001f3c30(0, 0); */
  D3DDevice_SetRenderStateNotInline();
  XMETAL_StartPush();
  /* relift: FUN_001f3e40(0, 0); */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* test ecx, ecx -> je 0x1ea181 */
  /* test ecx, ecx -> je 0x1ea1a4 */
  /* test ecx, ecx -> je 0x1ea1a1 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea1a4 */
  /* test eax, eax -> je 0x1ea227 */
  XMETAL_StartPush();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1ea290 */
void D3DDevice_SetRenderState_ZEnable(uint32_t enable)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1ea2b6 */
  /* test edx, edx -> je 0x1ea2b6 */
  /* mem[0x001fb884] = ecx */
  /* cmp ecx, 2 -> jne 0x1ea2f8 */
  D3D_UpdateProjectionViewportTransform();
  /* relift: FUN_001eb6f0(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9f80(0, 0); */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea31e */
  /* test edx, edx -> je 0x1ea341 */
  /* test edx, edx -> je 0x1ea33e */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea341 */
  /* test edx, edx -> je 0x1ea366 */
  /* test ecx, ecx -> je 0x1ea366 */
  /* mem[0x001fb888] = edx */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea39e */
  /* test edx, edx -> je 0x1ea3c1 */
  /* test edx, edx -> je 0x1ea3be */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea3c1 */
  /* mem[0x001fb88c] = ecx */
  /* mem[0x001fb8c0] = eax */
  XMETAL_StartPush();
  /* relift: FUN_001e9f80(0, 0); */
  /* mem[0x001fb8c4] = eax */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea447 */
  /* test edx, edx -> je 0x1ea46a */
  /* test edx, edx -> je 0x1ea467 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea46a */
  /* mem[0x001fb8c8] = eax */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea4a7 */
  /* test edx, edx -> je 0x1ea4ca */
  /* test edx, edx -> je 0x1ea4c7 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea4ca */
  /* mem[0x001fb8cc] = eax */
  D3D_CommonSetDebugRegisters();
  /* mem[0x001fb8d0] = eax */
  D3D_CommonSetDebugRegisters();
  /* mem[0x001fb8d4] = eax */
  D3D_CommonSetDebugRegisters();
  /* mem[0x001fb8a8] = eax */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* mem[0x001fb8ac] = eax */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1ea650 */
void D3DDevice_Clear(uint32_t count, void *rects, uint32_t flags, uint32_t color, float z, uint32_t stencil)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_001f3e40(0, 0); */
  XMETAL_StartPush();
  /* test dl, 0xf0 -> je 0x1ea71b */
  /* cmp eax, 0x19 -> ja 0x1ea71b */
  /* cmp ebx, ebp -> jne 0x1ea72c */
  /* test dl, 1 -> je 0x1ea820 */
  /* cmp eax, 7 -> ja 0x1ea820 */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp eax, 0xffff -> jle 0x1ea76b */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp eax, 0xffffff -> jle 0x1ea79d */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: cmp dword ptr [esp + 0x18], eax -> jge 0x1ea992 */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  XMETAL_StartPush();
  /* test edi, edi -> je 0x1ea9c4 */
  XMETAL_StartPush();
  /* cmp ecx, 4 -> jne 0x1eaa6d */
  /* test ecx, ecx -> je 0x1eaaa0 */
  /* test (char)ebx, 0x10 -> je 0x1eaab2 */
  /* test (char)ecx, (char)ebx -> je 0x1eaad0 */
  /* cmp edx, 1 -> jne 0x1eabb3 */
  /* cmp ecx, ebx -> je 0x1eacc5 */
  /* cmp ecx, 0x20000000 -> je 0x1eadf6 */
  /* cmp ecx, 0x40000000 -> jne 0x1eacc5 */
  /* test eax, 0x10000000 -> je 0x1ead21 */
  /* test eax, 0x8000000 -> jne 0x1ead1d */
  /* cmp eax, 9 -> jb 0x1ead40 */
  /* cmp eax, 0xc -> ja 0x1ead40 */
  /* cmp eax, 9 -> jb 0x1ead96 */
  /* cmp eax, 0xc -> ja 0x1ead96 */
  /* cmp ecx, 7 -> jne 0x1ead85 */
  /* cmp edi, 0x16 -> jne 0x1ead8f */
  /* cmp eax, 3 -> jne 0x1eada5 */
  /* cmp eax, 4 -> jne 0x1eadb4 */
  /* cmp eax, 7 -> jne 0x1eadc3 */
  /* cmp eax, 8 -> jne 0x1eadd3 */
  /* cmp ecx, 0x80000000 -> je 0x1eae5c */
  /* cmp ecx, 0xe0000000 -> jne 0x1eacc5 */
  /* cmp edx, 0x80000000 -> jne 0x1eaf4b */
  /* test ebp, ebp -> je 0x1eaedc */
  /* test ebp, ebp -> je 0x1eaf2c */
  /* test ebp, ebp -> je 0x1eafa2 */
  /* test ecx, ecx -> je 0x1eafb6 */
  /* relift: FUN_001eae70(0, 0); */
  FUN_001d0bb9(0, eax);
  /* test esi, esi -> jne 0x1eafd9 */
  /* test edi, edi -> je 0x1eb023 */
  /* relift: FUN_001eacb0(0, 0, 0); */
  /* test ebp, ebp -> je 0x1eb076 */
  /* cmp ecx, 0x7378 -> jne 0x1eb052 */
  /* relift: FUN_001eac20(0, 0); */
  /* test edi, edi -> je 0x1eb088 */
  /* relift: FUN_001eae70(0, 0); */
  /* test ecx, ecx -> je 0x1eb135 */
  /* test edi, edi -> je 0x1eb160 */
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  /* relift: FUN_001ef590(0, 0); */
  /* relift: FUN_001ed8b0(0); */
  /* test eax, eax -> je 0x1eb321 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x1eb393 */
  /* relift: FUN_001ed8f0(0); */
  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1eb3e6 */
  /* test (char)eax, 0x10 -> jne 0x1eb421 */
  /* relift: FUN_001eab60(0, 0); */
  /* relift: FUN_001efe30(0, 0); */
  /* test (char)ecx, 0x10 -> jne 0x1eb495 */
  /* relift: FUN_001efe30(0, 0); */
  /* relift: FUN_001eac20(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1eb551 */
  /* test (char)eax, 8 -> je 0x1eb572 */
  /* test ecx, ecx -> je 0x1eb587 */
  XMETAL_StartPush();
  /* relift: FUN_001ef590(0, 0); */
  /* relift: FUN_001ef590(0, 0x00400880, 0x001f9f48); */
  /* relift: FUN_001ef590(0, 0x004008c0, 0x001f9f48); */
  /* relift: FUN_001ef590(0, 0x00400900, 0x001f9f48); */
  XMETAL_StartPush();
  /* relift: FUN_001eac20(0); */
  /* relift: test byte ptr [eax + 4], 2 -> je 0x1eb7ee */
  /* relift: test byte ptr [esi + 0xc], 2 -> je 0x1eb72a */
  /* relift: FUN_001efe30(0, 0); */
  /* relift: cmp dword ptr [0x1fb884], 2 -> jne 0x1eb765 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)ecx, 0x10 -> je 0x1eb7c0 */
  /* relift: cmp dword ptr [0x1fb8a8], ebx -> je 0x1eb7c0 */
  /* cmp edx, ecx -> jne 0x1eb7c0 */
  /* relift: relift: fld dword ptr [0x1f9f98] */
  /* relift: FUN_001eac20(0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1eb7f0 */
void D3DDevice_SetVertexShader(uint32_t shader)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_001eaa20(0, 0); */
  /* test (char)eax, 4 -> je 0x1eb860 */
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001eb6f0(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001efe30(0, 0); */
  /* cmp eax, 0x20 -> jle 0x1eb94e */
  /* cmp eax, 0x20 -> jg 0x1eb935 */
  /* test (char)ecx, 8 -> je 0x1eb991 */
  /* relift: cmp dword ptr [ecx - 4], esi -> jne 0x1eb9f7 */
  /* relift: cmp esi, dword ptr [esp + 0x10] -> jae 0x1eb9f7 */
  /* cmp esi, eax -> jb 0x1eb9f7 */
  /* relift: cmp byte ptr [ecx + 8], 0 -> jne 0x1eb9f7 */
  /* relift: cmp dword ptr [ecx + 4], 2 -> je 0x1eb9f7 */
  /* test esi, esi -> jne 0x1eb9d0 */
  /* relift: cmp dword ptr [esp + 0x10], -1 -> je 0x1ebaa4 */
  /* relift: cmp ecx, dword ptr [esp + 0x18] -> je 0x1eba28 */
  /* test edx, edx -> je 0x1eba4f */
  /* cmp (char)eax, 2 -> jne 0x1ebad7 */
  /* test edx, edx -> je 0x1ebaf0 */
  /* cmp (char)eax, 1 -> jne 0x1ebaf1 */
  /* test edx, edx -> je 0x1ebaf0 */
  /* cmp (char)eax, 2 -> jne 0x1ebb06 */
  /* test edx, edx -> je 0x1ebb22 */
  /* cmp (char)eax, 1 -> jne 0x1ebb23 */
  /* test edx, edx -> je 0x1ebb22 */
  /* cmp (char)eax, 2 -> jne 0x1ebb37 */
  /* test edx, edx -> je 0x1ebb50 */
  /* cmp (char)eax, 1 -> jne 0x1ebb51 */
  /* test edx, edx -> je 0x1ebb50 */
  /* cmp (char)eax, 2 -> jne 0x1ebb66 */
  /* test edx, edx -> je 0x1ebb82 */
  /* cmp (char)eax, 1 -> jne 0x1ebb83 */
  /* test edx, edx -> je 0x1ebb82 */
  /* cmp (char)eax, 2 -> jne 0x1ebb98 */
  /* test edx, edx -> je 0x1ebbb4 */
  /* cmp (char)eax, 1 -> jne 0x1ebbb5 */
  /* test edx, edx -> je 0x1ebbb4 */
  /* cmp (char)eax, 2 -> jne 0x1ebbca */
  /* test edx, edx -> je 0x1ebbe6 */
  /* cmp (char)eax, 1 -> jne 0x1ebbe7 */
  /* test edx, edx -> je 0x1ebbe6 */
  /* cmp (char)eax, 2 -> jne 0x1ebbfc */
  /* test edx, edx -> je 0x1ebc18 */
  /* cmp (char)eax, 1 -> jne 0x1ebc19 */
  /* test edx, edx -> je 0x1ebc18 */
  /* cmp (char)eax, 2 -> jne 0x1ebc2e */
  /* test edx, edx -> je 0x1ebc4a */
  /* cmp (char)eax, 1 -> jne 0x1ebc4b */
  /* test edx, edx -> je 0x1ebc4a */
  /* cmp (char)eax, 2 -> jne 0x1ebc63 */
  /* test edx, edx -> je 0x1ebc82 */
  /* cmp (char)eax, 1 -> jne 0x1ebc83 */
  /* test edx, edx -> je 0x1ebc82 */
  /* cmp (char)eax, 2 -> jne 0x1ebc9b */
  /* test edx, edx -> je 0x1ebcba */
  /* cmp (char)eax, 1 -> jne 0x1ebcbb */
  /* test edx, edx -> je 0x1ebcba */
  /* cmp esi, 0x16 -> jb 0x1ebac4 */
  /* test ecx, ecx -> je 0x1ebd39 */
  /* cmp ebp, 1 -> jne 0x1ebcf8 */
  /* cmp ecx, 0xb80 -> jne 0x1ebd2f */
  /* test edx, edx -> je 0x1ebd2b */
  /* test edx, edx -> jne 0x1ebd68 */
  /* test edx, edx -> jne 0x1eb997 */
  /* relift: test byte ptr [esi + 3], 4 -> jne 0x1ebdbb */
  /* test ecx, ecx -> je 0x1ebe55 */
  /* test (char)eax, 1 -> je 0x1ebe0f */
  /* test edi, edi -> jbe 0x1ebeb6 */
  /* relift: FUN_001ed8b0(0); */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  XMETAL_StartPush();
  /* cmp esi, 9 -> jb 0x1ebf8c */
  /* cmp esi, 0xc -> ja 0x1ebf8c */
  /* cmp esi, 9 -> jb 0x1ebfce */
  /* cmp esi, 0xc -> ja 0x1ebfce */
  /* cmp eax, 9 -> jb 0x1ec00e */
  /* cmp eax, 0xc -> ja 0x1ec00e */
  /* cmp esi, 9 -> jb 0x1ec051 */
  /* cmp esi, 0xc -> ja 0x1ec051 */
  /* cmp esi, 0x10 -> jb 0x1ebf70 */
  FUN_001d0bb9(0, 252);
  /* test eax, eax -> jne 0x1ec0c8 */
  /* test ecx, ecx -> je 0x1ec118 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1ec120 */
void D3DDevice_SetPixelShaderProgram(void *program)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test (char)eax, 0x41 -> jne 0x1ec19b */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edi, 4 -> jb 0x1ec471 */
  /* cmp ebx, edi -> jae 0x1ec532 */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderState_TextureFactor();
  XMETAL_StartPush();
  /* relift: FUN_001e9d40(0, 0); */
  XMETAL_StartPush();
  /* test esi, esi -> jne 0x1ec67f */
  /* relift: FUN_001e9d40(0, 0); */
  /* test ecx, ecx -> je 0x1ec749 */
  /* relift: test byte ptr [ebx + 0xc], 0x10 -> jne 0x1ec76f */
  /* mem[0x001fb868] = eax */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1ec7f2 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1ec825 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* test (char)eax, 0x41 -> jne 0x1ec86c */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* test (char)eax, 0x41 -> jne 0x1ec8b4 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edx, ebp -> jne 0x1ec945 */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x20 -> jb 0x1ec922 */
  /* cmp edx, ebp -> jne 0x1ec971 */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x20 -> jb 0x1ec952 */
  /* cmp edx, ebp -> jne 0x1ec99f */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 8 -> jb 0x1ec980 */
  /* test ebp, ebp -> jne 0x1ec9dc */
  XMETAL_StartPush();
  /* test (char)eax, 0x10 -> je 0x1ecc62 */
  D3D_SetFence();
  CDevice_SetStateUP();
  XMETAL_StartPush();
  /* cmp eax, ecx -> jb 0x1ecd06 */
  /* relift: FUN_001efe30(0, 0); */
  /* test eax, eax -> je 0x1ecd6e */
  /* test (char)eax, 0x10 -> je 0x1ecd95 */
  D3D_SetFence();
  CDevice_SetStateUP();
  XMETAL_StartPush();
  /* cmp eax, ecx -> jb 0x1ece37 */
  /* relift: FUN_001efe30(0); */
  /* test (char)eax, 0x10 -> je 0x1eced1 */
  D3D_SetFence();
  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0, 0); */
  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0); */
  /* test eax, eax -> je 0x1ed035 */
  /* cmp edx, 0x3e -> jb 0x1ed062 */
  /* relift: FUN_001efe30(0, 516); */
  D3D_SetFence();
  CDevice_SetStateVB();
  XMETAL_StartPush();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1ed280 */
void D3DDevice_SetVertexData2f(uint32_t reg, float a, float b)
{
  XMETAL_StartPush();
}

/* 0x1ed2c0 */
void D3DDevice_SetVertexData4f(uint32_t reg, float a, float b, float c, float d)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* cmp ecx, -1 -> jne 0x1ed2dd */

  (void)ecx;
}

/* 0x1ed320 */
void D3DDevice_SetVertexData2s(unsigned int reg, int a, int b)
{
  XMETAL_StartPush();
  XMETAL_StartPush();
  XMETAL_StartPush();
}

/* 0x1ed400 */
void D3DDevice_SetVertexDataColor(unsigned int reg, unsigned int color)
{
  XMETAL_StartPush();
}

/* 0x1ed450 */
void D3DDevice_Begin(uint32_t primitive_type)
{
  int edi = 0;

  /* mem[0x001fbb04] = edi */
  /* relift: FUN_001f1b50(0, 0); */
  XMETAL_StartPush();

  (void)edi;
}

/* 0x1ed490 */
void D3DDevice_End(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* mem[0x001fbb04] = 0 */
  XMETAL_StartPush();
  /* test (char)eax, 0x10 -> je 0x1ed4c8 */
  D3D_SetFence();
  /* relift: cmp dword ptr [esi + 4], ebp -> jne 0x1ed518 */
  /* relift: test byte ptr [esi + 0x1c], 1 -> je 0x1ed50e */
  LocalFree((void *)(uintptr_t)esi);
  /* test esi, esi -> jne 0x1ed4f6 */
  /* cmp eax, 0x30000 -> ja 0x1ed5b6 */
  /* test eax, eax -> je 0x1ed5a6 */
  /* cmp eax, 0x10000 -> je 0x1ed59e */
  /* cmp eax, 0x20000 -> jne 0x1ed5cb */
  /* cmp eax, 0x40000 -> je 0x1ed5ee */
  /* cmp eax, 0x50000 -> je 0x1ed5d8 */
  /* cmp eax, 0x60000 -> je 0x1ed5d0 */
  /* test (char)eax, 4 -> je 0x1ed5fd */
  /* relift: cmp ecx, dword ptr [esp + 0x14] -> jne 0x1ed660 */
  /* test ebx, ebx -> jne 0x1ed647 */
  /* relift: test byte ptr [ebx + 0x1c], 1 -> je 0x1ed682 */
  LocalFree((void *)(uintptr_t)ebx);
  /* cmp ecx, 0x50000 -> jne 0x1ed73a */
  /* test eax, eax -> je 0x1ed7b1 */
  /* relift: cmp ebx, dword ptr [esp + 0x14] -> jne 0x1ed794 */
  /* cmp esi, 0x50000 -> jne 0x1ed7ec */
  D3D_BlockOnResource();
  /* relift: FUN_001ed4e0(0); */
  /* cmp esi, 0x50000 -> jne 0x1ed81f */
  LocalFree((void *)(uintptr_t)edi);
  /* cmp esi, 0x20000 -> jne 0x1ed841 */
  LocalFree((void *)(uintptr_t)edi);
  /* cmp esi, 0x10000 -> je 0x1ed861 */
  /* cmp esi, 0x60000 -> je 0x1ed861 */
  LocalFree((void *)(uintptr_t)edi);
  /* test eax, 0x780000 -> jne 0x1ed898 */
  /* cmp eax, 0x50000 -> jne 0x1ed8a0 */
  /* test eax, eax -> je 0x1ed8a0 */
  /* relift: test dword ptr [eax], 0x780000 -> je 0x1ed8a0 */
  /* cmp ecx, 0x50000 -> jne 0x1ed8db */
  /* test eax, 0x780000 -> jne 0x1ed8db */
  /* test eax, eax -> je 0x1ed8db */
  /* relift: FUN_001ed8b0(0); */
  /* test eax, 0xffff -> jne 0x1ed917 */
  /* cmp eax, 0x50000 -> jne 0x1ed917 */
  /* test eax, eax -> je 0x1ed917 */
  /* relift: FUN_001ed8f0(0); */
  /* cmp ecx, 1 -> jne 0x1ed972 */
  /* cmp eax, 0x50000 -> jne 0x1ed95d */
  /* test eax, eax -> je 0x1ed95d */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* test eax, 0x780000 -> jne 0x1ed972 */
  D3D_DestroyResource((void *)(uintptr_t)esi);
  /* test edx, edx -> je 0x1ed9b9 */
  /* test eax, 0x780000 -> jne 0x1ed9fb */
  /* test edx, edx -> je 0x1ed9b7 */
  /* relift: test dword ptr [edx], 0x780000 -> jne 0x1ed9fb */
  /* test eax, 0x780000 -> jne 0x1ed9fb */
  /* cmp eax, 0x50000 -> jne 0x1ed9dd */
  /* test eax, eax -> je 0x1ed9dd */
  /* relift: test dword ptr [eax], 0x780000 -> jne 0x1ed9fb */
  /* test edx, edx -> je 0x1eda04 */
  D3DDevice_AddRef();
  /* cmp edx, 0x20000 -> je 0x1eda52 */
  /* relift: FUN_001ed780(0, 0, 0, 0); */
  /* test eax, eax -> je 0x1eda7e */
  /* relift: FUN_001ed630(0, 0); */
  FUN_001d0bb9(64, eax);
  /* test ebx, ebx -> jne 0x1eda9f */
  /* mem[0x001fbb08] = ebx */
  /* relift: FUN_001ed780(0, 0); */
  /* test eax, eax -> jne 0x1edb2b */
  /* test edi, edi -> jne 0x1edb45 */
  /* relift: test byte ptr [eax + 0x1c], 1 -> je 0x1edb77 */
  /* cmp ecx, 0x80000 -> jne 0x1edbf7 */
  /* cmp eax, 0x50000 -> jne 0x1edbe4 */
  /* test eax, eax -> je 0x1edbe4 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test eax, 0xffff -> jne 0x1edbf7 */
  D3D_DestroyResource((void *)(uintptr_t)esi);
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef2a0(0, 0, 0, 0); */
  Lock2DSurface((void *)(uintptr_t)ecx, 0, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef2a0(0, 0, 0, 0); */
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef490(0, 0, 0, 0); */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* relift: test dword ptr [esp + 0x20], 0x10000 -> je 0x1ede24 */
  FUN_001d0bb9(64, 20);
  /* test esi, esi -> je 0x1ede55 */
  /* test eax, eax -> jne 0x1ede60 */
  LocalFree((void *)(uintptr_t)esi);
  /* mem[0x001fe6b0] = eax */
  /* mem[0x001fe6ac] = ecx */
  /* test eax, eax -> jne 0x1eded3 */
  /* mem[0x001fe6b0] = 0x80000 */
  /* test eax, eax -> jne 0x1edee6 */
  /* mem[0x001fe6ac] = 0x8000 */
  /* mem[0x001fe6a0] = 0x1fbb10 */
  /* mem[0x001fe6a4] = 0x1fbb10 */
  /* mem[0x001fbf18] = 1 */
  /* mem[0x001fbb1c] = esi */
  /* relift: FUN_001f3580(0); */
  /* test esi, esi -> jge 0x1edf3f */
  /* relift: FUN_001f3a90(0, 0); */
  /* test eax, eax -> je 0x1edf4d */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTexture(ecx, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetVertexShader(eax);
  D3DDevice_SetPixelShader();
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x80 -> jb 0x1ee040 */
  D3DDevice_SetTextureStageStateNotInline();
  /* cmp esi, 0x58 -> jb 0x1ee060 */
  D3DDevice_SetPixelShader();
  D3DDevice_SetVertexShader(260);
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)0);
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTexture(0, (void *)0);
  /* relift: FUN_001f1b50(0, 0); */
  /* relift: FUN_001ed8f0(0, 0, 0, 0); */
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001ed8f0(0); */
  /* cmp eax, 0x80 -> jb 0x1ee180 */
  /* cmp eax, 0x58 -> jb 0x1ee220 */
  /* test eax, eax -> je 0x1ee26d */
  /* cmp eax, 0xe4 -> jb 0x1ee250 */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DResource_Release((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1ee2bf */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DDevice_SetTexture(0, (void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1ee2d7 */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DDevice_SetPixelShader();
  D3DDevice_SetVertexShader(edx);
  D3DDevice_SetViewport((void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageStateNotInline();
  /* test ebp, ebp -> jne 0x1ee31d */
  /* relift: cmp dword ptr [edi + 0x1fa270], 0x52 -> jb 0x1ee32c */
  D3DDevice_SetRenderStateNotInline();
  /* cmp edi, 0x80 -> jb 0x1ee310 */
  D3DDevice_SetTextureStageStateNotInline();
  /* cmp edi, 0x58 -> jb 0x1ee340 */
  /* test ebp, ebp -> je 0x1ee39b */
  /* test eax, eax -> je 0x1ee38d */
  D3DDevice_SetRenderStateNotInline();
  /* cmp edi, 0x39 -> jb 0x1ee370 */
  D3DDevice_SetRenderStateNotInline();
  /* relift: FUN_001eb690(0); */
  /* cmp esi, ebp -> jne 0x1ee403 */
  /* cmp eax, ebp -> je 0x1ee43a */
  /* cmp ecx, ebp -> jl 0x1ee41f */
  /* cmp ebx, ecx -> jl 0x1ee428 */
  /* cmp ecx, ebp -> jl 0x1ee431 */
  /* cmp esi, eax -> jl 0x1ee43a */
  /* relift: cmp dword ptr [esp + 0xc], ebx -> jae 0x1ee63e */
  /* cmp ebp, esi -> jae 0x1ee63e */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* cmp eax, 5 -> jne 0x1ee4d7 */
  /* cmp edi, 2 -> jne 0x1ee4ca */
  /* cmp ecx, 2 -> jne 0x1ee4d7 */
  /* relift: relift: fld dword ptr [0x253398] */
  /* test eax, eax -> jge 0x1ee4e9 */
  /* relift: relift: fld dword ptr [0x1fa210] */
  /* relift: relift: fld dword ptr [0x1fa210] */
  /* relift: cmp dword ptr [esi + 0x2b64], 0x80000000 -> je 0x1ee6a5 */
  /* relift: FUN_001ee100(0); */
  /* test (char)eax, 2 -> je 0x1ee6e8 */
  /* mem[0x001fe6a8] = eax */
  /* relift: FUN_001ee030(0, 0, 0, 0); */
  XMETAL_StartPush();
  /* relift: cmp dword ptr [esi + 0x2b64], 0x80000000 -> jne 0x1ee75f */
  /* relift: FUN_001ee3b0(0, 0, 0, 0); */
  /* relift: cmp dword ptr [esi + 0x2b60], 1 -> jne 0x1ee73c */
  /* relift: FUN_001ee3b0(0); */
  /* relift: FUN_001ee3b0(0); */
  /* relift: FUN_001ee290(0); */
  XMETAL_StartPush();
  /* mem[0x001fe6a8] = ecx */
  /* cmp edi, ecx -> jne 0x1ee903 */
  D3D_SetFence();
  /* cmp ecx, 2 -> jb 0x1ee95c */
  /* relift: FUN_001ef520(0, 0); */
  /* cmp eax, 2 -> jae 0x1ee944 */
  /* test (char)eax, 0x30 -> je 0x1ee978 */
  /* relift: FUN_001ee650(0); */
  /* relift: FUN_001ee830(0, 0); */
  CDevice_KickOff();
  /* test eax, eax -> je 0x1eea9a */
  D3D_KickOffAndWaitForIdle();
  /* relift: test dword ptr [esi + 0x2510], 0x1000000 -> je 0x1ee9e0 */
  D3DDevice_BlockUntilVerticalBlank();
  /* test edi, edi -> jne 0x1ee9e2 */
  /* test dl, 1 -> jne 0x1eea54 */
  /* test edi, edi -> je 0x1eea80 */
  /* test eax, eax -> je 0x1eead0 */
  /* relift: FUN_001f489f(0, 0, 0, 0); */
  CMiniport_GetDisplayCapabilities();
  /* cmp edi, 4 -> jne 0x1eeb44 */
  /* test ecx, 0x60000 -> jne 0x1eeb53 */
  /* test ecx, 0x10000 -> je 0x1eeb53 */
  /* test eax, 0x10000 -> je 0x1eeb6c */
  /* test ebx, ecx -> je 0x1eeb6c */
  /* cmp edi, 4 -> jne 0x1eeb68 */
  /* test ebp, ecx -> jne 0x1eeb68 */
  /* test ecx, 0xe0000 -> jne 0x1eeb6c */
  /* cmp ebp, edx -> je 0x1eeb33 */
  /* relift: FUN_001f489f(0); */
  CMiniport_GetDisplayCapabilities();
  /* cmp edi, 4 -> jne 0x1eebf0 */
  /* test ecx, 0x60000 -> jne 0x1eebff */
  /* test ecx, 0x10000 -> je 0x1eebff */
  /* test eax, 0x10000 -> je 0x1eec23 */
  /* test ebx, ecx -> je 0x1eec23 */
  /* cmp edi, 4 -> jne 0x1eec14 */
  /* test ebp, ecx -> jne 0x1eec14 */
  /* test ecx, 0xe0000 -> jne 0x1eec23 */
  /* cmp ebp, edx -> je 0x1eebdf */
  /* relift: FUN_001f4840(0); */
  /* cmp eax, 3 -> ja 0x1eecc5 */
  /* test eax, eax -> je 0x1eed00 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eed0f */
  D3DDevice_GetDeviceCaps((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1eed50 */
  /* test ecx, ecx -> jne 0x1eed71 */
  /* relift: FUN_001f4840(0); */
  /* test eax, eax -> je 0x1eedd0 */
  /* cmp ecx, eax -> je 0x1eede5 */
  /* relift: cmp dword ptr [esp + 0x14], eax -> jne 0x1eedf3 */
  /* test eax, eax -> je 0x1eee30 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eee3f */
  /* test (char)ecx, dl -> je 0x1eee91 */
  /* test (char)eax, 2 -> je 0x1eee6c */
  /* relift: test byte ptr [ecx + 0x1f9d58], 0x40 -> jne 0x1eee99 */
  /* test (char)eax, 1 -> je 0x1eee84 */
  /* relift: test byte ptr [edx + 0x1f9d58], (char)ecx -> jne 0x1eee99 */
  /* relift: test byte ptr [eax + 0x1f9d58], 0x3c -> jne 0x1eee99 */
  /* test eax, eax -> jne 0x1eeeec */
  /* cmp eax, edx -> je 0x1eeebd */
  /* relift: cmp dword ptr [esp + 0x10], edx -> je 0x1eef11 */
  /* cmp ecx, 0x11 -> je 0x1eef19 */
  /* test ecx, ecx -> je 0x1eef19 */
  /* cmp eax, 0x40000 -> jbe 0x1eeef4 */
  /* cmp eax, edx -> jb 0x1eef11 */
  /* cmp ecx, edx -> jb 0x1eef11 */
  /* cmp eax, 3 -> ja 0x1eef11 */
  /* cmp ecx, 3 -> jbe 0x1eef19 */
  /* test eax, eax -> je 0x1eef30 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eef3f */
  FUN_001d0bb9(0, eax);
  /* test eax, eax -> jne 0x1eef9b */
  D3D_BlockOnResource();
  /* relift: FUN_001ed7c0(0); */
  FUN_001d0bb9(64, 12);
  /* test esi, esi -> je 0x1ef0d3 */
  /* test eax, eax -> jne 0x1ef0dc */
  LocalFree((void *)(uintptr_t)esi);
  XMETAL_StartPush();
  D3D_BlockOnResource();
  /* relift: FUN_001ed7c0(0); */
  D3DResource_GetType();
  FUN_001d0bb9(64, 12);
  /* test edi, edi -> jne 0x1ef189 */
  /* test eax, eax -> jne 0x1ef1be */
  LocalFree((void *)(uintptr_t)edi);
  Get2DSurfaceDesc((void *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  Lock2DSurface((void *)(uintptr_t)eax, 0, 0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* relift: FUN_001f4200(0, 0, 0); */
  Lock3DSurface();
  FUN_001d0bb9(64, 24);
  /* test esi, esi -> jne 0x1ef2b9 */
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  FUN_001d0bb9(64, 24);
  /* test esi, esi -> je 0x1ef38f */
  /* test eax, eax -> jne 0x1ef399 */
  LocalFree((void *)(uintptr_t)esi);
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x1ef41e */
  /* relift: FUN_001ed8f0(0); */
  FUN_001d0bb9(64, 24);
  /* cmp esi, ecx -> jne 0x1ef4ab */
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001ed8f0(0); */
  /* mem[0x001fe6ac] = eax */
  /* cmp eax, edx -> jb 0x1ef75a */
  /* relift: cmp eax, dword ptr [ecx + 0x14] -> jb 0x1ef76e */
  /* cmp eax, esi -> jb 0x1ef78b */
  /* relift: cmp eax, dword ptr [ecx + 0x14] -> jb 0x1ef79f */
  /* cmp esi, 0x80 -> ja 0x1ef80c */
  /* cmp ebx, esi -> jbe 0x1ef836 */
  /* cmp ebx, esi -> ja 0x1ef836 */
  /* relift: test dword ptr [eax + 0x100410], 0x10000 -> jne 0x1ef880 */
  XMETAL_StartPush();
  /* relift: test byte ptr [ecx + 0xc], 4 -> je 0x1ef94c */
  /* relift: test dword ptr [eax + 0x100410], 0x10000 -> jne 0x1ef970 */
  XMETAL_StartPush();
  /* test (char)ebx, 2 -> jne 0x1efa6d */
  CDevice_KickOff();
  /* cmp ecx, edx -> jae 0x1efb3f */
  /* cmp esi, eax -> jne 0x1efabc */
  D3D_SetFence();
  /* relift: FUN_001ef7e0(0, 0); */
  /* relift: FUN_001ef770(0, 0); */
  /* cmp eax, 0x8000 -> jb 0x1efb27 */
  /* relift: FUN_001ef860(0, 0); */
  /* relift: FUN_001ef770(0, 0); */
  /* cmp eax, 0x8000 -> jae 0x1efb45 */
  /* relift: FUN_001ef860(0, 0); */
  /* cmp eax, esi -> jb 0x1efb34 */
  /* test eax, eax -> jne 0x1efb51 */
  /* cmp eax, edx -> ja 0x1efbca */
  /* cmp eax, ecx -> je 0x1efbf0 */
  /* cmp eax, edx -> jb 0x1efc2f */
  /* relift: cmp eax, dword ptr [esi + 0x14] -> jb 0x1efc43 */
  /* cmp ecx, eax -> jae 0x1efd12 */
  /* relift: cmp eax, dword ptr [esp + 8] -> ja 0x1efd12 */
  /* relift: cmp edi, dword ptr [esp + 0x14] -> jae 0x1efc8c */
  /* cmp edi, ebp -> jb 0x1efd3e */
  /* cmp eax, ecx -> je 0x1efcb6 */
  /* cmp ecx, edx -> jb 0x1efc80 */
  /* cmp eax, edx -> jb 0x1efce9 */
  /* relift: cmp eax, dword ptr [esi + 0x14] -> jb 0x1efcfd */
  /* relift: cmp dword ptr [esp + 0x14], eax -> jae 0x1efd09 */
  /* relift: cmp eax, dword ptr [esp + 0x10] -> jbe 0x1efcc0 */
  /* relift: FUN_001ef740(0, 0); */
  CDevice_KickOff();
  D3D_BlockOnTime(ebx, 0);
  D3D_SetFence();
  CDevice_KickOff();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1efd60 */
void D3D_KickOffAndWaitForIdle(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  D3D_BlockOnTime(ecx, 0);
  /* test eax, eax -> je 0x1efdfe */
  /* test edi, edi -> je 0x1efdc6 */
  /* relift: FUN_001ed870(0); */
  /* test eax, eax -> je 0x1efdc4 */
  D3D_BlockOnTime(edx, 0);
  /* relift: FUN_001ed870(0); */
  D3D_BlockOnTime(ecx, 0);
  D3D_BlockOnTime(edi, 0);
  /* relift: cmp eax, dword ptr [ecx + 4] -> jb 0x1efe20 */
  CDevice_MakeSpace();
  CDevice_MakeSpace();
  /* cmp eax, 0x40000000 -> jne 0x1efea9 */
  /* relift: cmp dword ptr [ecx + 0x20c], 0 -> jne 0x1efeff */
  /* cmp eax, edx -> je 0x1efedf */
  /* test edi, edi -> je 0x1efedb */
  /* cmp eax, edx -> jne 0x1efef4 */
  /* test esi, 0x200000 -> je 0x1efef4 */
  /* test edi, edi -> je 0x1efef4 */
  /* test ecx, ecx -> je 0x1f02c7 */
  /* test (char)ecx, 4 -> jne 0x1f02a9 */
  /* test (char)ecx, 8 -> jne 0x1f02b3 */
  /* test (char)ecx, 0x10 -> jne 0x1f02bd */
  /* test (char)ecx, 0x20 -> jne 0x1f02c7 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: FUN_001f2340(0, 0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001ef590(0, 0); */
  XMETAL_StartPush();
  /* test (char)eax, 0x41 -> jne 0x1f064d */
  /* test (char)eax, 0x41 -> jne 0x1f06fe */
  /* relift: relift: fld dword ptr [0x254df8] */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp eax, 0x1ff -> jbe 0x1f0730 */
  /* cmp esi, 0x1fb498 -> je 0x1f07b2 */
  /* cmp edx, 0x19 -> jne 0x1f07a6 */
  /* cmp edx, 0x1a -> jne 0x1f07b2 */
  /* test (char)ecx, 4 -> je 0x1f07c1 */
  /* cmp (char)ecx, 0x30 -> jne 0x1f07d1 */
  /* cmp esi, 0x1fb498 -> jge 0x1f0780 */
  /* test edx, edx -> jne 0x1f0835 */
  /* cmp eax, 4 -> je 0x1f0835 */
  /* cmp eax, 5 -> je 0x1f0835 */
  /* cmp eax, 0xa -> je 0x1f0835 */
  /* cmp eax, 0x11 -> je 0x1f0835 */
  /* cmp eax, 1 -> jb 0x1f087c */
  /* cmp eax, 3 -> ja 0x1f087c */
  /* test (char)eax, 4 -> je 0x1f0855 */
  /* cmp (char)eax, 0x30 -> je 0x1f0875 */
  /* cmp edx, 0x2a00 -> jb 0x1f086e */
  /* cmp edx, 0x3100 -> jbe 0x1f0875 */
  /* cmp eax, 0xd -> je 0x1f0886 */
  /* cmp eax, 0xe -> jne 0x1f0894 */
  XMETAL_StartPush();
  /* relift: FUN_001f7330(0, 0, 0); */
  /* relift: FUN_001f68d0(0, 0, 0, 0); */
  /* cmp ebx, edx -> jne 0x1f091e */
  /* cmp edi, edx -> jne 0x1f092a */
  /* cmp ebx, edx -> je 0x1f092a */
  /* cmp ebp, 3 -> jb 0x1f08f1 */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1f0b5b */
  /* cmp ebx, 3 -> jb 0x1f0bd0 */
  /* cmp eax, 3 -> ja 0x1f0ba9 */
  /* cmp ebx, 3 -> ja 0x1f0ba9 */
  /* test eax, eax -> jne 0x1f0b98 */
  /* cmp eax, 5 -> je 0x1f0bb3 */
  /* cmp ebx, 5 -> jne 0x1f0bbb */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp esi, 0xfffff000 -> jge 0x1f0c10 */
  /* cmp esi, 0xfff -> jle 0x1f0c1d */
  /* relift: cmp dword ptr [edi - 0x2c], 0x19 -> jb 0x1f0c2d */
  XMETAL_StartPush();
  /* relift: FUN_001eb6f0(0, 0); */
  /* test eax, eax -> je 0x1f0e41 */
  /* test eax, eax -> jne 0x1f0d40 */
  /* cmp eax, 3 -> jne 0x1f0d83 */
  /* relift: relift: fld dword ptr [0x1fa748] */
  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1f0e0e */
  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1f0e74 */
  /* test ecx, ecx -> je 0x1f0e74 */
  /* relift: test byte ptr [eax + 4], 6 -> jne 0x1f124d */
  XMETAL_StartPush();
  /* cmp edi, ebx -> jne 0x1f0f19 */
  /* test ecx, 0xffff0000 -> je 0x1f0f2e */
  /* cmp ecx, edx -> jae 0x1f0f47 */
  /* cmp edx, 0x241 -> ja 0x1f10b5 */
  /* test dl, 0xc -> jne 0x1f12b3 */
  /* test dl, 0x30 -> jne 0x1f12e6 */
  /* test dl, 0xc0 -> jne 0x1f131a */
  /* test esi, esi -> je 0x1f1353 */
  /* test ecx, ecx -> je 0x1f14f3 */
  /* relift: FUN_001f2440(0, 0, 0, 0); */
  /* relift: FUN_001f2440(0, 0); */
  /* test ebx, ebx -> je 0x1f1631 */
  /* relift: FUN_001f2440(0, 0, 0); */
  /* relift: FUN_001f2440(0, 0); */
  /* relift: test byte ptr [ebp + 0xc], 0x40 -> jne 0x1f1663 */
  /* relift: test byte ptr [eax + 4], 6 -> jne 0x1f1919 */
  /* relift: cmp dword ptr [0x1fb808], ebx -> je 0x1f1919 */
  XMETAL_StartPush();
  /* relift: cmp dword ptr [0x1fb810], ebx -> je 0x1f16ab */
  /* relift: cmp dword ptr [ebp + 0x488], ebx -> je 0x1f16ab */
  /* relift: FUN_001f1500(0); */
  /* relift: FUN_001f0230(0, 0); */
  /* relift: FUN_001f1360(0); */
  XMETAL_StartPush();
  /* relift: FUN_001f1260(0, 0, 0, 0); */
  /* relift: cmp dword ptr [edi], 3 -> jne 0x1f17df */
  /* relift: FUN_001f22e0(0, 0, 0, 0); */
  /* relift: FUN_001f2600(0); */
  /* relift: FUN_001f2280(0, 0, 0x001fa74c); */
  /* relift: FUN_001f2600(0); */
  /* relift: FUN_001f22e0(0, 0, 0x3f800000); */
  /* cmp eax, 1 -> jne 0x1f1851 */
  /* relift: FUN_001f22e0(0, 0, 0, 0); */
  /* relift: FUN_001f2600(0); */
  /* relift: FUN_001f2250(0, 0, 0); */
  /* test edi, edi -> jne 0x1f1720 */
  XMETAL_StartPush();
  /* relift: test byte ptr [eax + 4], 6 -> jne 0x1f1b3a */
  XMETAL_StartPush();
  /* relift: FUN_001f2340(0, 0, 0); */
  /* relift: FUN_001ef590(0, 0x00400480, 0); */
  /* test eax, eax -> jne 0x1f19db */
  /* test eax, eax -> je 0x1f1a17 */
  /* relift: FUN_001f2650(0, 0, 0); */
  /* test eax, eax -> jne 0x1f1a5a */
  /* relift: FUN_001f2340(0, 0, 0); */
  /* relift: FUN_001ef590(0, 0x00400680, 0); */
  /* relift: FUN_001ef590(0, 0x00400680, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001f2340(0, 0, 0); */
  /* relift: FUN_001ef590(0, 0, 0); */
  /* test eax, eax -> je 0x1f1b25 */
  /* relift: FUN_001f2650(0, 0, 0); */
  /* test ebx, ebx -> je 0x1f1bb7 */
  /* test (char)ebx, 1 -> je 0x1f1b6a */
  D3D_LazySetPointParams();
  /* test (char)ebx, 4 -> je 0x1f1b75 */
  /* relift: FUN_001f0750(0); */
  /* test (char)ebx, 8 -> je 0x1f1b80 */
  /* relift: FUN_001f08d0(0); */
  /* test (char)ebx, 0x10 -> je 0x1f1b8b */
  /* relift: FUN_001f0ad0(0); */
  /* test (char)ebx, 0x40 -> je 0x1f1b96 */
  /* relift: FUN_001f0cd0(0); */
  /* test (char)ebx, 4 -> je 0x1f1ba1 */
  /* relift: FUN_001f0eb0(0); */
  /* test (char)ebx, 0x20 -> je 0x1f1bac */
  /* relift: FUN_001f1640(0); */
  /* test (char)ebx, 2 -> je 0x1f1bb7 */
  /* relift: FUN_001f1960(0); */
  /* relift: FUN_001f1b50(0, 0); */
  /* test eax, 0x40000000 -> jne 0x1f1ea8 */
  /* relift: test byte ptr [esi + 4], 4 -> jne 0x1f1cc3 */
  /* cmp eax, edi -> jae 0x1f1c48 */
  /* cmp ecx, 0x200 -> jb 0x1f1c10 */
  XMETAL_StartPush();
  /* test (char)edx, 4 -> jne 0x1f1c7c */
  /* test (char)edx, 8 -> jne 0x1f1c94 */
  /* test (char)edx, 0x10 -> jne 0x1f1ca8 */
  /* test (char)ecx, 0x20 -> jne 0x1f1cc0 */
  /* relift: cmp dword ptr [ecx], 2 -> jne 0x1f1cdd */
  /* test eax, eax -> jne 0x1f1cd0 */
  XMETAL_StartPush();
  /* relift: cmp dword ptr [ebp + 0x598], edi -> je 0x1f1ea5 */
  XMETAL_StartPush();
  /* relift: cmp dword ptr [edx + 8], 2 -> je 0x1f1e3e */
  /* relift: cmp dword ptr [esi + 8], 2 -> je 0x1f1e95 */
  /* relift: FUN_001f1b50(0); */
  /* test (char)eax, 1 -> je 0x1f2244 */
  /* cmp eax, edi -> jae 0x1f1f38 */
  /* cmp ecx, 0x200 -> jb 0x1f1f00 */
  XMETAL_StartPush();
  /* test (char)edx, 4 -> jne 0x1f1f6c */
  /* test (char)edx, 8 -> jne 0x1f1f84 */
  /* test (char)edx, 0x10 -> jne 0x1f1f98 */
  /* test (char)ecx, 0x20 -> jne 0x1f1fb0 */
  /* cmp ebp, 2 -> je 0x1f200a */
  /* cmp ebp, 2 -> je 0x1f2043 */
  /* cmp ebp, 2 -> je 0x1f207d */
  /* cmp ebp, 2 -> je 0x1f20b7 */
  /* cmp ebp, 2 -> je 0x1f20f1 */
  /* cmp ebp, 2 -> je 0x1f212b */
  /* cmp ebp, 2 -> je 0x1f2165 */
  /* cmp ebp, 2 -> je 0x1f219f */
  XMETAL_StartPush();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x1fa758] */
  /* relift: FUN_001f3c50(0, 0); */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: FUN_001f3cb0(0); */
  /* relift: FUN_001f3c30(0); */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x1fb430] */
  /* relift: relift: fld dword ptr [0x1fb434] */
  /* relift: FUN_001f2530(0); */
  /* relift: FUN_001f2530(0, 0); */
  /* relift: FUN_001f2530(0, 0); */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test eax, eax -> je 0x1f2abf */
  /* relift: FUN_001f2530(0, 0); */
  /* cmp ecx, 0x11 -> je 0x1f2c05 */
  /* test ecx, ecx -> je 0x1f2c05 */
  /* cmp eax, 0x40000 -> jbe 0x1f2be6 */
  /* cmp eax, 1 -> jb 0x1f2bde */
  /* cmp ecx, 1 -> jb 0x1f2bde */
  /* cmp eax, 3 -> ja 0x1f2bde */
  /* cmp ecx, 3 -> ja 0x1f2bde */
  /* cmp eax, 2 -> jbe 0x1f2c14 */
  /* cmp eax, 0x80000000 -> jne 0x1f2bde */
  /* cmp eax, 1 -> je 0x1f2c25 */
  /* cmp eax, 2 -> je 0x1f2c25 */
  /* test eax, eax -> jne 0x1f2bde */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTransform(ecx, (void *)(uintptr_t)eax);
  D3DDevice_SetShaderConstantMode();
  D3DDevice_SetTile();
  /* test eax, eax -> je 0x1f2e74 */
  XMETAL_StartPush();
  XMETAL_StartPush();
  D3DDevice_SetShaderConstantMode();
  XMETAL_StartPush();
  D3DDevice_SetTransform(esi, (void *)0x001f9f48);
  /* cmp esi, 0xa -> jb 0x1f3010 */
  /* cmp esi, 0x134 -> je 0x1f3041 */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x15c -> jb 0x1f3030 */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  /* cmp esi, 0x20 -> jb 0x1f3072 */
  D3DDevice_SetTextureStageStateNotInline();
  /* cmp edi, 4 -> jb 0x1f3070 */
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  /* test eax, eax -> jne 0x1f30e4 */
  /* cmp eax, ebp -> je 0x1f310f */
  /* cmp ecx, ebp -> je 0x1f30f7 */
  /* relift: FUN_001edba0(0); */
  /* cmp eax, ebp -> je 0x1f313a */
  /* cmp ecx, ebp -> je 0x1f3122 */
  /* relift: FUN_001edba0(0); */
  D3DDevice_SetTile();
  /* relift: cmp dword ptr [esi + 0x2144], ebp -> je 0x1f319b */
  D3DDevice_SetTile();
  /* cmp eax, ebp -> je 0x1f31ae */
  /* relift: FUN_001f3cd0(0); */
  /* relift: FUN_001f3cd0(0); */
  /* mem[0x001fb8b0] = eax */
  /* mem[0x001fb8b0] = eax */
  /* cmp ecx, 0x30000 -> ja 0x1f328a */
  /* cmp ecx, 0x10000 -> je 0x1f327c */
  /* cmp ecx, 0x20000 -> jne 0x1f3297 */
  /* cmp ecx, 0x40000 -> jne 0x1f3297 */
  /* relift: FUN_001f3e00(0, 0); */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* test ebx, ebx -> je 0x1f34eb */
  /* relift: FUN_001ef300(0, 0, 0, 0); */
  /* cmp esi, 0x780 -> je 0x1f33ac */
  /* relift: FUN_001e77d0(0); */
  D3DDevice_SetTile();
  /* test ecx, ecx -> je 0x1f348c */
  /* relift: FUN_001f3e00(0, 0); */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* test ebx, ebx -> je 0x1f34eb */
  /* relift: FUN_001ef300(0, 0, 0, 0); */
  /* cmp esi, 0x780 -> je 0x1f348c */
  /* relift: FUN_001e77d0(0); */
  /* cmp (char)ecx, 0x20 -> jne 0x1f3480 */
  D3DDevice_SetTile();
  /* test eax, eax -> je 0x1f3534 */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* test esi, esi -> jne 0x1f34fa */
  /* relift: FUN_001ef300(0, 0, 0, 0); */
  XMETAL_StartPush();
  /* test eax, eax -> jne 0x1f35c7 */
  /* relift: FUN_001ef540(0, 0); */
  CMiniport_InitHardware();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  CMiniport_CreateCtxDmaObject();
  /* relift: FUN_001f5723(8302, 0, 0, 0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5786(0); */
  /* relift: FUN_001f5c30(13, 151, 0); */
  /* relift: FUN_001f5c30(14, 57, 0); */
  /* relift: FUN_001f5c30(16, 159, 0); */
  /* relift: FUN_001f5c30(17, 98, 0); */
  /* mem[0x001fb48c] = edx */
  /* mem[0x001fb488] = ecx */
  /* mem[0x001fb484] = edx */
  /* mem[0x001fb480] = ecx */
  /* mem[0x001fb47c] = edx */
  /* mem[0x001fb478] = ecx */
  /* mem[0x80000000] = edx */
  CDevice_KickOff();
  /* relift: FUN_001ef520(0, 0); */
  /* test edx, 0xfffffff -> jne 0x1f3948 */
  /* mem[0x80000000] = 0xdeadbeef */
  /* relift: FUN_001f2f70(0, 0); */
  CDevice_InitializeFrameBuffers();
  /* test eax, eax -> jl 0x1f3a7c */
  /* relift: FUN_001e77d0(0); */
  /* relift: FUN_001f4918(0, 0, 0, 0); */
  D3DDevice_SetVertexShader(0);
  /* test ecx, ecx -> je 0x1f39ef */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)eax, (void *)0);
  /* relift: FUN_001f3000(0, 0); */
  D3DDevice_Clear(0, (void *)0, 0, 0, 0.0f, 0);
  /* test eax, eax -> je 0x1f3a7a */
  /* test eax, eax -> je 0x1f3a7a */
  /* relift: tail-call D3D_KickOffAndWaitForIdle(); */
  CDevice_KickOff();
  /* test ecx, 0xfffffff -> je 0x1f3aeb */
  /* relift: FUN_001ef520(0, 0); */
  /* test ecx, 0xfffffff -> jne 0x1f3ad0 */
  CMiniport_IsFlipPending();
  /* test eax, eax -> jne 0x1f3af5 */
  CDevice_FreeFrameBuffers();
  /* test eax, eax -> je 0x1f3b2b */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1f3b59 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1f3b79 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1f3ba5 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* cmp edi, 0xc0 -> jb 0x1f3b81 */
  /* test eax, eax -> je 0x1f3bca */
  /* test eax, eax -> je 0x1f3bdd */
  /* test eax, eax -> je 0x1f3be7 */
  LocalFree((void *)(uintptr_t)esi);
  /* test eax, eax -> je 0x1f3c12 */
  /* relift: FUN_001f6135(0, 0); */
  /* relift: test word ptr [ebp - 3], 1 -> je 0x1f3c88 */
  /* relift: test word ptr [ebp - 7], 0x40 -> jne 0x1f3c92 */
  /* cmp ecx, 0x2b -> ja 0x1f3d2f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x204f23 */
int IDirectSoundBuffer_SetVolume(void *buffer, int volume)
{
  CDirectSoundVoice_SetVolume();
  return 0;
}

/* 0x204f3f */
int IDirectSoundBuffer_SetPitch(void *buffer, int pitch)
{
  CDirectSoundVoice_SetPitch();
  CDirectSoundVoice_SetLFO();
  CDirectSoundVoice_SetEG();
  CDirectSoundVoice_SetFilter();
  CDirectSoundVoice_SetHeadroom();
  CDirectSoundVoice_SetMixBinVolumes();
  CDirectSoundVoice_SetAllParameters();
  CDirectSoundVoice_SetConeAngles();
  CDirectSoundBuffer_SetConeOrientation();
  CDirectSoundVoice_SetConeOutsideVolume();
  CDirectSoundBuffer_SetMaxDistance();
  CDirectSoundBuffer_SetMinDistance();
  CDirectSoundVoice_SetMode();
  CDirectSoundBuffer_SetPosition();
  CDirectSoundBuffer_SetVelocity();
  CDirectSoundBuffer_PlayEx();
  CDirectSoundBuffer_StopEx();
  return 0;
}

/* 0x20519e */
int IDirectSoundBuffer_SetLoopRegion(void *buffer, uint32_t start, uint32_t length)
{
  CDirectSoundBuffer_SetLoopRegion();
  CDirectSoundBuffer_GetStatus();
  CDirectSoundBuffer_GetCurrentPosition();
  return 0;
}

/* 0x2051fa */
int IDirectSoundBuffer_SetCurrentPosition(void *buffer, uint32_t position)
{
  CDirectSoundBuffer_SetCurrentPosition();
  CDirectSoundBuffer_Lock();
  CDirectSoundVoice_SetI3DL2Source();
  return 0;
}

/* 0x205266 */
int IDirectSoundStream_SetVolume(void *stream, int volume)
{
  CDirectSoundVoice_SetVolume();
  CDirectSoundVoice_SetPitch();
  CDirectSoundVoice_SetLFO();
  CDirectSoundVoice_SetEG();
  CDirectSoundVoice_SetFilter();
  CDirectSoundVoice_SetHeadroom();
  return 0;
}

/* 0x2052e8 */
int IDirectSoundStream_SetConeAngles(void *stream, int inner_angle, int outer_angle, int deferred)
{
  CDirectSoundVoice_SetConeAngles();
  CDirectSoundVoice_SetConeOrientation();
  CDirectSoundVoice_SetConeOutsideVolume();
  return 0;
}

/* 0x205316 */
int IDirectSoundStream_SetConeOutsideVolume(void *stream, int volume, int deferred)
{
  CDirectSoundVoice_SetConeOutsideVolume();
  CDirectSoundVoice_SetMaxDistance();
  CDirectSoundVoice_SetMinDistance();
  return 0;
}

/* 0x20531b */
int IDirectSoundStream_SetMaxDistance(void *stream, float distance, int deferred)
{
  CDirectSoundStream_SetMaxDistance();
  return 0;
}

/* 0x205333 */
int IDirectSoundStream_SetMinDistance(void *stream, float distance, int deferred)
{
  CDirectSoundStream_SetMinDistance();
  CDirectSoundStream_SetPosition();
  CDirectSoundStream_SetVelocity();
  return 0;
}

/* 0x2053a7 */
int IDirectSoundStream_SetAllParameters(void *stream, void *params, int deferred)
{
  CDirectSoundVoice_SetI3DL2Source();
  IDirectSound_AddRef();
  IDirectSound_AddRef();
  CDirectSound_GetCaps();
  CDirectSound_GetSpeakerConfig();
  CDirectSound_DownloadEffectsImage();
  CDirectSound_GetEffectData();
  CDirectSound_SetEffectData();
  CDirectSound_CommitEffectData();
  CDirectSound_EnableHeadphones();
  CDirectSound_SetMixBinHeadroom();
  CDirectSound_SetAllParameters();
  CDirectSound_SetDistanceFactor();
  CDirectSound_SetDopplerFactor();
  CDirectSound_SetOrientation();
  return 0;
}

/* 0x205b43 */
int IDirectSoundBuffer_Play(void *buffer, uint32_t reserved, uint32_t priority, uint32_t flags)
{
  CDirectSoundBuffer_Play();
  CDirectSoundBuffer_Stop();
  return 0;
}

/* 0x205b7f */
int IDirectSoundBuffer_SetBufferData(void *buffer, void *data, uint32_t size)
{
  CDirectSoundBuffer_SetBufferData();
  CDirectSoundBuffer_SetNotificationPositions();
  return 0;
}

/* 0x205bbf */
int IDirectSoundStream_SetFrequency(void *stream, int frequency)
{
  CDirectSoundVoice_SetFrequency();
  return 0;
}

/* 0x2062d0 */
int DirectSoundCreateBuffer(void *desc, void **out_buffer)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  DirectSoundCreate();
  /* test edi, edi -> jl 0x2062fe */
  IDirectSound_CreateSoundBuffer();
  /* relift: FUN_00205a68(0); */
  DirectSoundCreate();
  /* test edi, edi -> jl 0x20633c */
  IDirectSound_CreateSoundStream();
  /* relift: FUN_00205a68(0); */
  /* cmp edx, eax -> je 0x2063b5 */
  /* relift: FUN_0020639e(0, 0); */
  /* relift: cmp dword ptr [eax], 0 -> je 0x2063fb */
  /* relift: cmp dword ptr [ecx], 0 -> je 0x20640b */
  /* relift: FUN_002063cb(0); */
  /* relift: cmp dword ptr [ecx], 0 -> je 0x206426 */
  /* test eax, eax -> jne 0x206445 */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* cmp esi, edi -> jne 0x20649a */
  /* relift: FUN_0020d4a4(0); */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* relift: test byte ptr [ecx + 0xc], 0x10 -> jne 0x20651c */
  /* cmp (int16_t)edi, (int16_t)eax -> jb 0x20651c */
  /* cmp (int16_t)ecx, (int16_t)eax -> jb 0x2065b3 */
  /* relift: cmp dword ptr [esi + edi*4 + 0x1cc], 0 -> je 0x206560 */
  /* cmp (int16_t)ecx, 0x100 -> jb 0x206549 */
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x2065b8 */
  /* relift: cmp dword ptr [esi + edx*4 + 0x1cc], edi -> je 0x206599 */
  /* cmp (int16_t)eax, 0x40 -> jb 0x206584 */
  /* relift: cmp dword ptr [ebp - 0xc], 0 -> je 0x2065ce */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* cmp ecx, -1 -> je 0x20664d */
  /* cmp ecx, 0x40 -> jae 0x20662d */
  /* cmp eax, ecx -> jb 0x206609 */
  /* cmp edx, esi -> je 0x2066fa */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
