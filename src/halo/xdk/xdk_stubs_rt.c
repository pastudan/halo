/* kb object stubs -> xdk/xdk_stubs_rt.c */

/* --- <xdk_stubs> batch drafts (2026-07-26) --- */

/* 0x1cfa3f */
void SetThreadPriorityBoost(void)
{

}

/* 0x1cfa85 */
void FUN_001cfa85(void)
{

}

/* 0x1cfac6 */
void FUN_001cfac6(void)
{

}

/* 0x1cfaec */
int ResumeThread(int thread_handle)
{
  (void)thread_handle;
  return 0;
}

/* 0x1cfb12 */
void RaiseException(void)
{

}

/* 0x1cfb98 */
void SwitchToThread(void)
{

}

/* 0x1cfbbd */
int GetExitCodeThread(int thread_handle, int *exit_code)
{
  (void)thread_handle;
  (void)exit_code;
  return 0;
}

/* 0x1cfc1b */
void FUN_001cfc1b(void)
{

}

/* 0x1cfca4 */
void XRegisterThreadNotifyRoutine(void)
{

}

/* 0x1cfd8c */
void * CreateThread(void *security, int stack_size, void *func, void *param, int flags, int *thread_id)
{
  (void)security;
  (void)stack_size;
  (void)func;
  (void)param;
  (void)flags;
  (void)thread_id;
  return NULL;
}

/* 0x1cfde0 */
void FUN_001cfde0(void)
{

}

/* 0x1cfded */
void * CreateEventA(void *security, int manual_reset, int initial_state, const char *name)
{
  (void)security;
  (void)manual_reset;
  (void)initial_state;
  (void)name;
  return NULL;
}

/* 0x1cfe4e */
void OpenEventA(void)
{

}

/* 0x1cfeaa */
bool SetEvent(void *handle)
{
  (void)handle;
  return 0;
}

/* 0x1cfeca */
void ResetEvent(void)
{

}

/* 0x1cff08 */
void FUN_001cff08(void)
{

}

/* 0x1cff63 */
void FUN_001cff63(void)
{

}

/* 0x1cffe5 */
void CreateMutexA(void)
{

}

/* 0x1d003d */
void FUN_001d003d(void)
{

}

/* 0x1d0099 */
int ReleaseMutex(int mutex_handle)
{
  (void)mutex_handle;
  return 0;
}

/* 0x1d00b9 */
void FUN_001d00b9(void)
{

}

/* 0x1d00fd */
void SignalObjectAndWait(void)
{

}

/* 0x1d0144 */
void FUN_001d0144(void)
{

}

/* 0x1d01c4 */
unsigned int SleepEx(unsigned int milliseconds, int alertable)
{
  (void)milliseconds;
  (void)alertable;
  return 0;
}

/* 0x1d0216 */
void FUN_001d0216(void)
{

}

/* 0x1d0274 */
void FUN_001d0274(void)
{

}

/* 0x1d02d0 */
void FUN_001d02d0(void)
{

}

/* 0x1d0336 */
int WaitForSingleObject(int handle, int timeout_ms)
{
  (void)handle;
  (void)timeout_ms;
  return 0;
}

/* 0x1d0348 */
void FUN_001d0348(void)
{

}

/* 0x1d0362 */
void FUN_001d0362(void)
{

}

/* 0x1d0370 */
void OutputDebugStringA(void)
{

}

/* 0x1d03a2 */
void OutputDebugStringW(void)
{

}

/* 0x1d03ee */
void FUN_001d03ee(void)
{

}

/* 0x1d040f */
void FUN_001d040f(void)
{

}

/* 0x1d0447 */
void FUN_001d0447(void)
{

}

/* 0x1e6ae0 */
void D3DDevice_CreateTexture(uint32_t width, uint32_t height, uint32_t levels, uint32_t usage, uint32_t format, uint32_t pool, void *out_texture)
{
  (void)width;
  (void)height;
  (void)levels;
  (void)usage;
  (void)format;
  (void)pool;
  (void)out_texture;
}

/* 0x1e6bd0 */
void D3DDevice_SetTransform(uint32_t type, void *matrix)
{
  (void)type;
  (void)matrix;
}

/* 0x1e6ce0 */
void D3DDevice_GetTransform(uint32_t type, void *matrix_out)
{
  (void)type;
  (void)matrix_out;
}

/* 0x1e7110 */
void D3DDevice_BlockUntilVerticalBlank(void)
{

}

/* 0x1e7af0 */
void D3DDevice_SetRenderTarget(void *render_target, void *depth_stencil)
{
  (void)render_target;
  (void)depth_stencil;
}

/* 0x1e7d50 */
int D3DDevice_GetBackBuffer(int back_buffer, uint32_t type, void **out_surface)
{
  (void)back_buffer;
  (void)type;
  (void)out_surface;
  return 0;
}

/* 0x1e8270 */
int D3DDevice_GetDepthStencilSurface(void **out_surface)
{
  (void)out_surface;
  return 0;
}

/* 0x1e8700 */
void D3DDevice_SetTexture(uint32_t stage, void *texture)
{
  (void)stage;
  (void)texture;
}

/* 0x1e9350 */
void D3DDevice_SetRenderState_Simple(uint32_t reg, uint32_t value)
{
  (void)reg;
  (void)value;
}

/* 0x1e9380 */
void D3DDevice_SetRenderState_Deferred(uint32_t reg_index, uint32_t value)
{
  (void)reg_index;
  (void)value;
}

/* 0x1e9410 */
void D3DDevice_SetTextureStageState(uint32_t stage, uint32_t state, uint32_t value)
{
  (void)stage;
  (void)state;
  (void)value;
}

/* 0x1e96d0 */
void D3DDevice_SetRenderState_CullMode(uint32_t mode)
{
  (void)mode;
}

/* 0x1e9c20 */
void D3DDevice_SetTextureState_BorderColor(uint32_t stage, uint32_t color)
{
  (void)stage;
  (void)color;
}

/* 0x1ea290 */
void D3DDevice_SetRenderState_ZEnable(uint32_t enable)
{
  (void)enable;
}

/* 0x1ea650 */
void D3DDevice_Clear(uint32_t count, void *rects, uint32_t flags, uint32_t color, float z, uint32_t stencil)
{
  (void)count;
  (void)rects;
  (void)flags;
  (void)color;
  (void)z;
  (void)stencil;
}

/* 0x1eb7f0 */
void D3DDevice_SetVertexShader(uint32_t shader)
{
  (void)shader;
}

/* 0x1ec120 */
void D3DDevice_SetPixelShaderProgram(void *program)
{
  (void)program;
}

/* 0x1ed280 */
void D3DDevice_SetVertexData2f(uint32_t reg, float a, float b)
{
  (void)reg;
  (void)a;
  (void)b;
}

/* 0x1ed2c0 */
void D3DDevice_SetVertexData4f(uint32_t reg, float a, float b, float c, float d)
{
  (void)reg;
  (void)a;
  (void)b;
  (void)c;
  (void)d;
}

/* 0x1ed320 */
void D3DDevice_SetVertexData2s(unsigned int reg, int a, int b)
{
  (void)reg;
  (void)a;
  (void)b;
}

/* 0x1ed400 */
void D3DDevice_SetVertexDataColor(unsigned int reg, unsigned int color)
{
  (void)reg;
  (void)color;
}

/* 0x1ed450 */
void D3DDevice_Begin(uint32_t primitive_type)
{
  (void)primitive_type;
}

/* 0x1ed490 */
void D3DDevice_End(void)
{

}

/* 0x1efd60 */
void D3D_KickOffAndWaitForIdle(void)
{

}

/* 0x204f23 */
int IDirectSoundBuffer_SetVolume(void *buffer, int volume)
{
  (void)buffer;
  (void)volume;
  return 0;
}

/* 0x204f3f */
int IDirectSoundBuffer_SetPitch(void *buffer, int pitch)
{
  (void)buffer;
  (void)pitch;
  return 0;
}

/* 0x20519e */
int IDirectSoundBuffer_SetLoopRegion(void *buffer, uint32_t start, uint32_t length)
{
  (void)buffer;
  (void)start;
  (void)length;
  return 0;
}

/* 0x2051fa */
int IDirectSoundBuffer_SetCurrentPosition(void *buffer, uint32_t position)
{
  (void)buffer;
  (void)position;
  return 0;
}

/* 0x205266 */
int IDirectSoundStream_SetVolume(void *stream, int volume)
{
  (void)stream;
  (void)volume;
  return 0;
}

/* 0x2052e8 */
int IDirectSoundStream_SetConeAngles(void *stream, int inner_angle, int outer_angle, int deferred)
{
  (void)stream;
  (void)inner_angle;
  (void)outer_angle;
  (void)deferred;
  return 0;
}

/* 0x205316 */
int IDirectSoundStream_SetConeOutsideVolume(void *stream, int volume, int deferred)
{
  (void)stream;
  (void)volume;
  (void)deferred;
  return 0;
}

/* 0x20531b */
int IDirectSoundStream_SetMaxDistance(void *stream, float distance, int deferred)
{
  (void)stream;
  (void)distance;
  (void)deferred;
  return 0;
}

/* 0x205333 */
int IDirectSoundStream_SetMinDistance(void *stream, float distance, int deferred)
{
  (void)stream;
  (void)distance;
  (void)deferred;
  return 0;
}

/* 0x2053a7 */
int IDirectSoundStream_SetAllParameters(void *stream, void *params, int deferred)
{
  (void)stream;
  (void)params;
  (void)deferred;
  return 0;
}

/* 0x205b43 */
int IDirectSoundBuffer_Play(void *buffer, uint32_t reserved, uint32_t priority, uint32_t flags)
{
  (void)buffer;
  (void)reserved;
  (void)priority;
  (void)flags;
  return 0;
}

/* 0x205b7f */
int IDirectSoundBuffer_SetBufferData(void *buffer, void *data, uint32_t size)
{
  (void)buffer;
  (void)data;
  (void)size;
  return 0;
}

/* 0x205bbf */
int IDirectSoundStream_SetFrequency(void *stream, int frequency)
{
  (void)stream;
  (void)frequency;
  return 0;
}

/* 0x2062d0 */
int DirectSoundCreateBuffer(void *desc, void **out_buffer)
{
  (void)desc;
  (void)out_buffer;
  return 0;
}
