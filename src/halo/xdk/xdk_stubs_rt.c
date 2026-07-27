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

/* SetThreadPriorityBoost (0x1cfa3f) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void __stdcall (*const b1cfa3f_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void SetThreadPriorityBoost(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x2530ac\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530a8\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LSetThreadPriorityBoost_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0xc(%%ebp)\n\t"
      "setne %%al\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530b4\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "call *0x2530a0\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LSetThreadPriorityBoost_2\n\t"
      ".LSetThreadPriorityBoost_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LSetThreadPriorityBoost_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfa3f_c1d2296)
      : "memory");
}
#else
#error "SetThreadPriorityBoost: clang naked draft required"
#endif


/* FUN_001cfa85 (0x1cfa85) — XBE naked draft (batch 365). */
#if defined(__clang__)
static void __stdcall (*const b1cfa85_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001cfa85(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x2530ac\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530a8\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001cfa85_1\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpb %%al, 0x73(%%ecx)\n\t"
      "setne %%al\n\t"
      "movl %%eax, (%%edx)\n\t"
      "call *0x2530a0\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001cfa85_2\n\t"
      ".LFUN_001cfa85_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001cfa85_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfa85_c1d2296)
      : "memory");
}
#else
#error "FUN_001cfa85: clang naked draft required"
#endif


/* FUN_001cfac6 (0x1cfac6) — XBE naked draft (batch 380). */
#if defined(__clang__)
static void __stdcall (*const b1cfac6_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001cfac6(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530b8\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001cfac6_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .LFUN_001cfac6_2\n\t"
      ".LFUN_001cfac6_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".LFUN_001cfac6_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfac6_c1d2296)
      : "memory");
}
#else
#error "FUN_001cfac6: clang naked draft required"
#endif


/* 0x1cfaec */
int ResumeThread(int thread_handle)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1cfb0b */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* RaiseException (0x1cfb12) — XBE naked draft (batch 332). */
#if defined(__clang__)


__attribute__((naked, noinline))
void RaiseException(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0, -0x48(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "andl $1, %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl $0x1cfb12, -0x44(%%ebp)\n\t"
      "je .LRaiseException_2\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpl $0xf, %%ecx\n\t"
      "jbe .LRaiseException_1\n\t"
      "pushl $0xf\n\t"
      "popl %%ecx\n\t"
      ".LRaiseException_1:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "je .LRaiseException_3\n\t"
      "pushl %%edi\n\t"
      "leal -0x3c(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "jmp .LRaiseException_3\n\t"
      ".LRaiseException_2:\n\t"
      "andl $0, -0x40(%%ebp)\n\t"
      ".LRaiseException_3:\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530c0\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "RaiseException: clang naked draft required"
#endif


/* SwitchToThread (0x1cfb98) — XBE naked draft (batch 331). */
#if defined(__clang__)


__attribute__((naked, noinline))
void SwitchToThread(void)
{
  __asm__ volatile(
      "call *0x2530c8\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $0x40000024, %%eax\n\t"
      "setne %%cl\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "SwitchToThread: clang naked draft required"
#endif


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

/* FUN_001cfc1b (0x1cfc1b) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void __stdcall (*const b1cfc1b_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001cfc1b(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x2530ac\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530a8\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001cfc1b_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x110(%%ecx), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x114(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "cmpb %%bl, 0x4(%%ecx)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "je .LFUN_001cfc1b_1\n\t"
      "movl 0x118(%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x11c(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "jmp .LFUN_001cfc1b_2\n\t"
      ".LFUN_001cfc1b_1:\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl %%ebx, 0x4(%%eax)\n\t"
      ".LFUN_001cfc1b_2:\n\t"
      "movl 0x18(%%ecx), %%eax\n\t"
      "movl 0x2530d0, %%edx\n\t"
      "mull (%%edx)\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl %%ebx, 0x4(%%eax)\n\t"
      "call *0x2530a0\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "popl %%esi\n\t"
      "jmp .LFUN_001cfc1b_4\n\t"
      ".LFUN_001cfc1b_3:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001cfc1b_4:\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfc1b_c1d2296)
      : "memory");
}
#else
#error "FUN_001cfc1b: clang naked draft required"
#endif


/* XRegisterThreadNotifyRoutine (0x1cfca4) — XBE naked draft (batch 356). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XRegisterThreadNotifyRoutine(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl $0x32fd00, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *0x25309c\n\t"
      "cmpl $0, 0xc(%%esp)\n\t"
      "je .LXRegisterThreadNotifyRoutine_1\n\t"
      "movl 0x32fd20, %%ecx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl $0x32fd1c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x32fd20\n\t"
      "jmp .LXRegisterThreadNotifyRoutine_2\n\t"
      ".LXRegisterThreadNotifyRoutine_1:\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LXRegisterThreadNotifyRoutine_2:\n\t"
      "pushl %%esi\n\t"
      "call *0x253098\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XRegisterThreadNotifyRoutine: clang naked draft required"
#endif


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

/* FUN_001cfde0 — implemented in xapilib/xvutil.c */

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

/* OpenEventA (0x1cfe4e) — XBE naked draft (batch 342). */
#if defined(__clang__)
static void __stdcall (*const b1cfe4e_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void OpenEventA(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .LOpenEventA_1\n\t"
      "pushl $0xc000000d\n\t"
      "jmp .LOpenEventA_2\n\t"
      ".LOpenEventA_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl 0x2530e0\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffc, -0x14(%%ebp)\n\t"
      "call *0x2530dc\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LOpenEventA_3\n\t"
      "pushl %%eax\n\t"
      ".LOpenEventA_2:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LOpenEventA_4\n\t"
      ".LOpenEventA_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LOpenEventA_4:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfe4e_c1d2296)
      : "memory");
}
#else
#error "OpenEventA: clang naked draft required"
#endif


/* 0x1cfeaa */
bool SetEvent(void *handle)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cfebf */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* ResetEvent (0x1cfeca) — XBE naked draft (batch 378). */
#if defined(__clang__)
static void __stdcall (*const b1cfeca_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void ResetEvent(void)
{
  __asm__ volatile(
      "pushl 0x4(%%esp)\n\t"
      "call *0x2530ec\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LResetEvent_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LResetEvent_2\n\t"
      ".LResetEvent_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LResetEvent_2:\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfeca_c1d2296)
      : "memory");
}
#else
#error "ResetEvent: clang naked draft required"
#endif


/* FUN_001cff08 (0x1cff08) — XBE naked draft (batch 353). */
#if defined(__clang__)
static void (*const b1cff08_c1d440e)(void) = (void *)XapiFormatObjectAttributes;
static void __stdcall (*const b1cff08_c1d2268)(unsigned int error) = (void *)SetLastError;
static void __stdcall (*const b1cff08_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001cff08(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x14(%%ebp)\n\t"
      "je .LFUN_001cff08_1\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d440e]\n\t"
      "jmp .LFUN_001cff08_2\n\t"
      ".LFUN_001cff08_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001cff08_2:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal 0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530f4\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001cff08_5\n\t"
      "cmpl $0x40000000, %%eax\n\t"
      "jne .LFUN_001cff08_3\n\t"
      "pushl $0xb7\n\t"
      "jmp .LFUN_001cff08_4\n\t"
      ".LFUN_001cff08_3:\n\t"
      "pushl $0\n\t"
      ".LFUN_001cff08_4:\n\t"
      "call *%[c1d2268]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "jmp .LFUN_001cff08_6\n\t"
      ".LFUN_001cff08_5:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001cff08_6:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d440e] "m"(b1cff08_c1d440e), [c1d2268] "m"(b1cff08_c1d2268), [c1d2296] "m"(b1cff08_c1d2296)
      : "memory");
}
#else
#error "FUN_001cff08: clang naked draft required"
#endif


/* FUN_001cff63 (0x1cff63) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void __stdcall (*const b1cff63_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001cff63(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .LFUN_001cff63_1\n\t"
      "pushl $0xc000000d\n\t"
      "jmp .LFUN_001cff63_2\n\t"
      ".LFUN_001cff63_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl 0x2530f8\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffc, -0x14(%%ebp)\n\t"
      "call *0x2530dc\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001cff63_3\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001cff63_2:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001cff63_4\n\t"
      ".LFUN_001cff63_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001cff63_4:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cff63_c1d2296)
      : "memory");
}
#else
#error "FUN_001cff63: clang naked draft required"
#endif


/* CreateMutexA (0x1cffe5) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void (*const b1cffe5_c1d440e)(void) = (void *)XapiFormatObjectAttributes;
static void __stdcall (*const b1cffe5_c1d2268)(unsigned int error) = (void *)SetLastError;
static void __stdcall (*const b1cffe5_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void CreateMutexA(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LCreateMutexA_1\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d440e]\n\t"
      "jmp .LCreateMutexA_2\n\t"
      ".LCreateMutexA_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCreateMutexA_2:\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253100\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LCreateMutexA_5\n\t"
      "cmpl $0x40000000, %%eax\n\t"
      "jne .LCreateMutexA_3\n\t"
      "pushl $0xb7\n\t"
      "jmp .LCreateMutexA_4\n\t"
      ".LCreateMutexA_3:\n\t"
      "pushl $0\n\t"
      ".LCreateMutexA_4:\n\t"
      "call *%[c1d2268]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "jmp .LCreateMutexA_6\n\t"
      ".LCreateMutexA_5:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCreateMutexA_6:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d440e] "m"(b1cffe5_c1d440e), [c1d2268] "m"(b1cffe5_c1d2268), [c1d2296] "m"(b1cffe5_c1d2296)
      : "memory");
}
#else
#error "CreateMutexA: clang naked draft required"
#endif


/* FUN_001d003d (0x1d003d) — XBE naked draft (batch 342). */
#if defined(__clang__)
static void __stdcall (*const b1d003d_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d003d(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d003d_1\n\t"
      "pushl $0xc000000d\n\t"
      "jmp .LFUN_001d003d_2\n\t"
      ".LFUN_001d003d_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl 0x253104\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffc, -0x14(%%ebp)\n\t"
      "call *0x2530dc\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d003d_3\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001d003d_2:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d003d_4\n\t"
      ".LFUN_001d003d_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d003d_4:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d003d_c1d2296)
      : "memory");
}
#else
#error "FUN_001d003d: clang naked draft required"
#endif


/* 0x1d0099 */
int ReleaseMutex(int mutex_handle)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d00ae */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* FUN_001d00b9 (0x1d00b9) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void (*const b1d00b9_c1d4436)(void) = (void *)FUN_001d4436;
static void __stdcall (*const b1d00b9_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d00b9(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d4436]\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_001d00b9_1:\n\t"
      "pushl %%esi\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25310c\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d00b9_2\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LFUN_001d00b9_3\n\t"
      "cmpl $0x101, %%eax\n\t"
      "je .LFUN_001d00b9_1\n\t"
      "jmp .LFUN_001d00b9_3\n\t"
      ".LFUN_001d00b9_2:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LFUN_001d00b9_3:\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4436] "m"(b1d00b9_c1d4436), [c1d2296] "m"(b1d00b9_c1d2296)
      : "memory");
}
#else
#error "FUN_001d00b9: clang naked draft required"
#endif


/* SignalObjectAndWait (0x1d00fd) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void (*const b1d00fd_c1d4436)(void) = (void *)FUN_001d4436;
static void __stdcall (*const b1d00fd_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void SignalObjectAndWait(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d4436]\n\t"
      "movl %%eax, %%esi\n\t"
      ".LSignalObjectAndWait_1:\n\t"
      "pushl %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253110\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LSignalObjectAndWait_2\n\t"
      "cmpl $0, 0x14(%%ebp)\n\t"
      "je .LSignalObjectAndWait_3\n\t"
      "cmpl $0x101, %%eax\n\t"
      "je .LSignalObjectAndWait_1\n\t"
      "jmp .LSignalObjectAndWait_3\n\t"
      ".LSignalObjectAndWait_2:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LSignalObjectAndWait_3:\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4436] "m"(b1d00fd_c1d4436), [c1d2296] "m"(b1d00fd_c1d2296)
      : "memory");
}
#else
#error "SignalObjectAndWait: clang naked draft required"
#endif


/* FUN_001d0144 (0x1d0144) — XBE naked draft (batch 345). */
#if defined(__clang__)
static void __stdcall (*const b1d0144_c1d2296)(int status) = (void *)XapiSetLastNTError;
static void (*const b1d0144_c1d4436)(void) = FUN_001d4436;

__attribute__((naked, noinline))
void FUN_001d0144(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpl $0x40, %%ecx\n\t"
      "jbe .LFUN_001d0144_1\n\t"
      "pushl $0xc000000d\n\t"
      "call *%[c1d2296]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .LFUN_001d0144_5\n\t"
      ".LFUN_001d0144_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "leal -0x108(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "rep movsl\n\t"
      "call *%[c1d4436]\n\t"
      "movsbl 0x8(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, 0x10(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "sete %%bl\n\t"
      ".LFUN_001d0144_2:\n\t"
      "pushl %%edi\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x253114\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d0144_3\n\t"
      "cmpl $0, 0x18(%%ebp)\n\t"
      "je .LFUN_001d0144_4\n\t"
      "cmpl $0x101, %%eax\n\t"
      "je .LFUN_001d0144_2\n\t"
      "jmp .LFUN_001d0144_4\n\t"
      ".LFUN_001d0144_3:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LFUN_001d0144_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001d0144_5:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0144_c1d2296), [c1d4436] "m"(b1d0144_c1d4436)
      : "memory");
}
#else
#error "FUN_001d0144: clang naked draft required"
#endif


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

/* FUN_001d0216 (0x1d0216) — XBE naked draft (batch 351). */
#if defined(__clang__)
static void (*const b1d0216_c1d440e)(void) = XapiFormatObjectAttributes;
static void __stdcall (*const b1d0216_c1d2268)(unsigned int error) = (void *)SetLastError;
static void __stdcall (*const b1d0216_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d0216(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LFUN_001d0216_1\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d440e]\n\t"
      "jmp .LFUN_001d0216_2\n\t"
      ".LFUN_001d0216_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0216_2:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, 0xc(%%ebp)\n\t"
      "sete %%cl\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25311c\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d0216_5\n\t"
      "cmpl $0x40000000, %%eax\n\t"
      "jne .LFUN_001d0216_3\n\t"
      "pushl $0xb7\n\t"
      "jmp .LFUN_001d0216_4\n\t"
      ".LFUN_001d0216_3:\n\t"
      "pushl $0\n\t"
      ".LFUN_001d0216_4:\n\t"
      "call *%[c1d2268]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d0216_6\n\t"
      ".LFUN_001d0216_5:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0216_6:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d440e] "m"(b1d0216_c1d440e), [c1d2268] "m"(b1d0216_c1d2268), [c1d2296] "m"(b1d0216_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0216: clang naked draft required"
#endif


/* FUN_001d0274 (0x1d0274) — XBE naked draft (batch 342). */
#if defined(__clang__)
static void __stdcall (*const b1d0274_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d0274(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d0274_1\n\t"
      "pushl $0xc000000d\n\t"
      "jmp .LFUN_001d0274_2\n\t"
      ".LFUN_001d0274_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl 0x253120\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffc, -0x14(%%ebp)\n\t"
      "call *0x2530dc\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d0274_3\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001d0274_2:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d0274_4\n\t"
      ".LFUN_001d0274_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d0274_4:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0274_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0274: clang naked draft required"
#endif


/* FUN_001d02d0 (0x1d02d0) — XBE naked draft (batch 376). */
#if defined(__clang__)
static void __stdcall (*const b1d02d0_c1d2296)(int status) = (void *)XapiSetLastNTError;
static void __stdcall (*const b1d02d0_c1d2268)(unsigned int error) = (void *)SetLastError;

__attribute__((naked, noinline))
void FUN_001d02d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl $0\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253124\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d02d0_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d02d0_4\n\t"
      ".LFUN_001d02d0_1:\n\t"
      "cmpl $0x40000025, %%eax\n\t"
      "jne .LFUN_001d02d0_2\n\t"
      "pushl $0x32\n\t"
      "jmp .LFUN_001d02d0_3\n\t"
      ".LFUN_001d02d0_2:\n\t"
      "pushl $0\n\t"
      ".LFUN_001d02d0_3:\n\t"
      "call *%[c1d2268]\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d02d0_4:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d02d0_c1d2296), [c1d2268] "m"(b1d02d0_c1d2268)
      : "memory");
}
#else
#error "FUN_001d02d0: clang naked draft required"
#endif


/* WaitForSingleObject — implemented in xapilib/xvutil.c */

/* FUN_001d0348 (0x1d0348) — XBE naked draft (batch 377). */
#if defined(__clang__)
static void (*const b1d0348_c1d0144)(void) = (void *)FUN_001d0144;

__attribute__((naked, noinline))
void FUN_001d0348(void)
{
  __asm__ volatile(
      "pushl $0\n\t"
      "pushl 0x14(%%esp)\n\t"
      "pushl 0x14(%%esp)\n\t"
      "pushl 0x14(%%esp)\n\t"
      "pushl 0x14(%%esp)\n\t"
      "call *%[c1d0144]\n\t"
      "ret\n\t"
      :
      : [c1d0144] "m"(b1d0348_c1d0144)
      : "memory");
}
#else
#error "FUN_001d0348: clang naked draft required"
#endif


/* FUN_001d0362 (0x1d0362) — XBE naked draft (batch 393). */
#if defined(__clang__)
static unsigned int __stdcall (*const b1d0362_c1d01c4)(unsigned int milliseconds, int alertable) = (void *)SleepEx;

__attribute__((naked, noinline))
void FUN_001d0362(void)
{
  __asm__ volatile(
      "pushl $0\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *%[c1d01c4]\n\t"
      "ret\n\t"
      :
      : [c1d01c4] "m"(b1d0362_c1d01c4)
      : "memory");
}
#else
#error "FUN_001d0362: clang naked draft required"
#endif


/* OutputDebugStringA (0x1d0370) — XBE naked draft (batch 336). */
#if defined(__clang__)


__attribute__((naked, noinline))
void OutputDebugStringA(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal 0x1(%%eax), %%ecx\n\t"
      ".LOutputDebugStringA_1:\n\t"
      "movb (%%eax), %%dl\n\t"
      "incl %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LOutputDebugStringA_1\n\t"
      "subl %%ecx, %%eax\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movw %%ax, -0x6(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      ".byte 0xcd, 0x2d\n\t"
      ".byte 0xcc\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "OutputDebugStringA: clang naked draft required"
#endif


/* OutputDebugStringW (0x1d03a2) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void (*const b1d03a2_c1d0370)(void) = OutputDebugStringA;

__attribute__((naked, noinline))
void OutputDebugStringW(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253134\n\t"
      "pushl $1\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253130\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LOutputDebugStringW_1\n\t"
      "movl $0x25386f, -0x4(%%ebp)\n\t"
      ".LOutputDebugStringW_1:\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c1d0370]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "jl .LOutputDebugStringW_2\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25312c\n\t"
      ".LOutputDebugStringW_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d0370] "m"(b1d03a2_c1d0370)
      : "memory");
}
#else
#error "OutputDebugStringW: clang naked draft required"
#endif


/* FUN_001d03ee (0x1d03ee) — XBE naked draft (batch 352). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d03ee(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "pushl $4\n\t"
      "popl %%edx\n\t"
      "pushl %%esi\n\t"
      ".LFUN_001d03ee_1:\n\t"
      "movzbw (%%ecx), %%si\n\t"
      "movw %%si, (%%eax)\n\t"
      "incl %%eax\n\t"
      "incl %%eax\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_001d03ee_1\n\t"
      "andw $0, (%%eax)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d03ee: clang naked draft required"
#endif


/* FUN_001d040f (0x1d040f) — XBE naked draft (batch 357). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d040f(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, %%edi\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movzbw (%%eax), %%dx\n\t"
      "movw %%dx, 0x2(%%ecx)\n\t"
      "movzbw 0x1(%%eax), %%dx\n\t"
      "movw %%dx, 0x6(%%ecx)\n\t"
      "movzbw 0x2(%%eax), %%dx\n\t"
      "movw %%dx, 0x4(%%ecx)\n\t"
      "movzbw 0x3(%%eax), %%ax\n\t"
      "movw %%ax, 0x8(%%ecx)\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d040f: clang naked draft required"
#endif


/* FUN_001d0447 (0x1d0447) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void (*const b1d0447_c1d4464)(void) = FUN_001d4464;
static void (*const b1d0447_c1d03ee)(void) = FUN_001d03ee;
static void (*const b1d0447_c1d040f)(void) = FUN_001d040f;

__attribute__((naked, noinline))
void FUN_001d0447(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x104, %%esp\n\t"
      "pushl $0\n\t"
      "pushl $0x100\n\t"
      "leal -0x104(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xff\n\t"
      "call *%[c1d4464]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d0447_2\n\t"
      "movl -0x100(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xfc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d03ee]\n\t"
      "leal 0x58(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xf8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d03ee]\n\t"
      "leal 0x44(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xec(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d040f]\n\t"
      "leal 0x98(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xe8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d040f]\n\t"
      "movl -0xdc(%%ebp), %%eax\n\t"
      "movl %%eax, 0x54(%%esi)\n\t"
      "movl -0xd8(%%ebp), %%eax\n\t"
      "movl %%eax, 0xa8(%%esi)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "je .LFUN_001d0447_1\n\t"
      "movl -0xac(%%ebp), %%ecx\n\t"
      "shrl $1, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_001d0447_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0447_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4464] "m"(b1d0447_c1d4464), [c1d03ee] "m"(b1d0447_c1d03ee), [c1d040f] "m"(b1d0447_c1d040f)
      : "memory");
}
#else
#error "FUN_001d0447: clang naked draft required"
#endif


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

/* D3DDevice_BlockUntilVerticalBlank (0x1e7110) — XBE naked draft (batch 340). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_BlockUntilVerticalBlank(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "movl $0, 0x24f4(%%eax)\n\t"
      "pushl $6\n\t"
      "addl $0x24f0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531ac\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_BlockUntilVerticalBlank: clang naked draft required"
#endif


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

/* D3DDevice_SetRenderState_Simple (0x1e9350) — XBE naked draft (batch 370). */
#if defined(__clang__)
static void (*const b1e9350_c1efb70)(void) = (void *)CDevice_MakeSpace;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_Simple(uint32_t reg __attribute__((unused)), uint32_t value __attribute__((unused)))
{
  __asm__ volatile(
      ".LD3DDevice_SetRenderState_Simple_1:\n\t"
      "movl 0x1fbb10, %%eax\n\t"
      "addl $8, %%eax\n\t"
      "cmpl 0x1fbb14, %%eax\n\t"
      "jae .LD3DDevice_SetRenderState_Simple_2\n\t"
      "movl %%eax, 0x1fbb10\n\t"
      "movl %%ecx, -0x8(%%eax)\n\t"
      "movl %%edx, -0x4(%%eax)\n\t"
      "ret\n\t"
      ".LD3DDevice_SetRenderState_Simple_2:\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "call *%[c1efb70]\n\t"
      "popl %%ecx\n\t"
      "popl %%edx\n\t"
      "jmp .LD3DDevice_SetRenderState_Simple_1\n\t"
      :
      : [c1efb70] "m"(b1e9350_c1efb70)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_Simple: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_Deferred (0x1e9380) — XBE naked draft (batch 393). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetRenderState_Deferred(uint32_t reg_index __attribute__((unused)), uint32_t value __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x1f9d50(,%%ecx,4), %%eax\n\t"
      "orl %%eax, 0x1fbb18\n\t"
      "movl %%edx, 0x1fb698(,%%ecx,4)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_Deferred: clang naked draft required"
#endif


/* D3DDevice_SetTextureStageState (0x1e9410) — XBE naked draft (batch 360). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetTextureStageState(uint32_t stage __attribute__((unused)), uint32_t state __attribute__((unused)), uint32_t value __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x1fb3d8(,%%edx,4), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fbb18, %%esi\n\t"
      "shll $5, %%ecx\n\t"
      "orl %%eax, %%esi\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "movl %%esi, 0x1fbb18\n\t"
      "movl %%edx, 0x1fb498(,%%ecx,4)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetTextureStageState: clang naked draft required"
#endif


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

/* D3DDevice_End (0x1ed490) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b1ed490_c1efe10)(void) = XMETAL_StartPush;
static void (*const b1ed490_c1ef9e0)(void) = D3D_SetFence;

__attribute__((naked, noinline))
void D3DDevice_End(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl $0, 0x1fbb04\n\t"
      "call *%[c1efe10]\n\t"
      "movl $0x417fc, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LD3DDevice_End_1\n\t"
      "pushl $1\n\t"
      "call *%[c1ef9e0]\n\t"
      ".LD3DDevice_End_1:\n\t"
      "andl $0xffffe7ff, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ed490_c1efe10), [c1ef9e0] "m"(b1ed490_c1ef9e0)
      : "memory");
}
#else
#error "D3DDevice_End: clang naked draft required"
#endif


/* D3D_KickOffAndWaitForIdle (0x1efd60) — XBE naked draft (batch 306). */
#if defined(__clang__)
static void __stdcall (*const b1efd60_c1efa80)(uint32_t time, int param2) = (void *)D3D_BlockOnTime;

__attribute__((naked, noinline))
void D3D_KickOffAndWaitForIdle(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1efa80]\n\t"
      "ret\n\t"
      :
      : [c1efa80] "m"(b1efd60_c1efa80)
      : "memory");
}
#else
#error "D3D_KickOffAndWaitForIdle: clang naked draft required"
#endif


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
