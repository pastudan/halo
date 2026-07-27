/* kb object stubs -> xdk/xdk_stubs_xapi.c */

/* --- <xdk_stubs> batch drafts (2026-07-26) --- */

/* 0x001cfb73 */

/* --- forward decls (auto) --- */
int __stdcall XapiFormatFATVolume(void *device_path);
void XcRC4Key(int a, int b, int c);
void XcRC4Crypt(int a, int b, int c);
void XcKeyTable(int a, int b);
void XcBlockCryptCBC(int a, int b, int c, int d);
void XcModExp(int a, int b, int c, int d);
void XcHMAC(int a, int b, int c, int d);
void XcDESKeyParity(int a, int b);
void XcSHAInit(int ctx);
void XcSHAUpdate(int a, int b, int c);
void XcSHAFinal(int a, int b);
void ExQueryNonVolatileSetting(int a, int b, int c, int d);
int DbgPrint(unsigned long fmt, ...);
void QueueUserAPC(void);
void ExitThread(void);
void XapiThreadStartup(void);
void PulseEvent(void);
void MmQueryAllocationSize(void);
void NtDuplicateObject(void);
void RtlLeaveCriticalSection(void);
void RtlEnterCriticalSection(void);
void ObfDereferenceObject(void);
void KeSetBasePriorityThread(void);
void ObReferenceObjectByHandle(void);
void KeQueryBasePriorityThread(void);
void KeSetDisableBoostThread(void);
void NtSuspendThread(void);
void NtResumeThread(void);
void RtlRaiseException(void);
void NtQueueApcThread(void);
void NtYieldExecution(void);
void PsTerminateSystemThread(void);
void PsCreateSystemThreadEx(void);
void NtCreateEvent(void);
void ObOpenObjectByName(void);
void NtSetEvent(void);
void NtClearEvent(void);
void NtPulseEvent(void);
void NtCreateSemaphore(void);
void NtReleaseSemaphore(void);
void NtCreateMutant(void);
void NtReleaseMutant(void);
void NtWaitForSingleObjectEx(void);
void NtSignalAndWaitForSingleObjectEx(void);
void NtWaitForMultipleObjectsEx(void);
void KeDelayExecutionThread(void);
void NtCreateTimer(void);
void NtSetTimerEx(void);
void NtCancelTimer(void);
void RtlFreeAnsiString(void);
void RtlUnicodeStringToAnsiString(void);
void RtlInitUnicodeString(void);
void RtlTimeToTimeFields(void);
void RtlTimeFieldsToTime(void);
void NtAllocateVirtualMemory(void);
void NtFreeVirtualMemory(void);
void NtProtectVirtualMemory(void);
void NtQueryVirtualMemory(void);
void MmQueryStatistics(void);
void NtSetInformationFile(void);
void NtQueryFullAttributesFile(void);
void FscSetCacheSize(void);
void FscGetCacheSize(void);
void NtQueryDirectoryFile(void);
void NtWaitForSingleObject(void);
void NtReadFile(void);
void NtQueryInformationFile(void);
void NtFlushBuffersFile(void);
void NtUserIoApcDispatcher(void);
void NtReadFileScatter(void);
void NtCreateFile(void);
void MmFreeSystemMemory(void);
void MmAllocateSystemMemory(void);
void KeWaitForSingleObject(void);
void KfLowerIrql(void);
void KeRaiseIrqlToDpcLevel(void);
void IoCreateDevice(void);
void ExAllocatePool(void);
void KeSetEvent(void);
void KeInitializeTimerEx(void);
void KeInitializeDpc(void);
void IoInvalidDeviceRequest(void);
void RtlNtStatusToDosError(void);
void NtCreateIoCompletion(void);
void NtSetIoCompletion(void);
void NtRemoveIoCompletion(void);
void KeSetTimer(void);
void KeCancelTimer(void);
void MmPersistContiguousMemory(void);
void MmAllocateContiguousMemory(void);
void HalReturnToFirmware(void);
void NtQuerySymbolicLinkObject(void);
void NtOpenSymbolicLinkObject(void);
void KeQueryPerformanceCounter(void);
void KeQueryPerformanceFrequency(void);
void MmAllocateContiguousMemoryEx(void);
void MmSetAddressProtect(void);
void IoCreateSymbolicLink(void);
void IoDeleteSymbolicLink(void);
void RtlFillMemoryUlong(void);
void RtlCompareMemoryUlong(void);
void RtlCompareMemory(void);
void RtlInitializeCriticalSection(void);
void IoStartPacket(void);
void IofCompleteRequest(void);
void IoStartNextPacket(void);
void ExFreePool(void);
void IoMarkIrpMustComplete(void);
void HalIsResetOrShutdownPending(void);
void KeQueryInterruptTime(void);
void HalInitiateShutdown(void);
void HalGetInterruptVector(void);
void KfRaiseIrql(void);
void HalRegisterShutdownNotification(void);
void KeConnectInterrupt(void);
void KeInitializeInterrupt(void);
void KeStallExecutionProcessor(void);
void RtlEqualString(void);
void XeLoadSection(void);
void XeUnloadSection(void);
void MmGetPhysicalAddress(void);
void MmLockUnlockBufferPages(void);
void KeInsertQueueDpc(void);
void MmLockUnlockPhysicalPage(void);
void AvGetSavedDataAddress(void);
void AvSendTVEncoderOption(void);
void AvSetDisplayMode(void);
void AvSetSavedDataAddress(void);
void KeDisconnectInterrupt(void);
void MmClaimGpuInstanceMemory(void);
void ExQueryPoolBlockSize(void);
void ExAllocatePoolWithTag(void);
void KeRemoveQueueDpc(void);
void KeSynchronizeExecution(void);
void KeSaveFloatingPointState(void);
void KeRestoreFloatingPointState(void);
void PhyGetLinkState(void);
void PhyInitialize(void);
void KeWaitForMultipleObjects(void);
void KeSetTimerEx(void);
void DbgBreakPoint(void);
void KeBugCheck(void);
void RtlAnsiStringToUnicodeString(void);
void D3DDevice_GetDeviceCaps(void *caps);
void D3DDevice_GetCreationParameters(void);
void D3DDevice_SetGammaRamp(void);
void D3DDevice_GetGammaRamp(void);
void D3DDevice_CreateVolumeTexture(void);
void D3DDevice_CreateCubeTexture(void);
void D3DDevice_CreateImageSurface(void);
void D3DDevice_SetRenderState(void);
void D3DDevice_MultiplyTransform(void);
void D3DDevice_GetViewport(void);
void D3DDevice_SetMaterial(void);
void D3DDevice_GetMaterial(void);
void D3DDevice_SetBackMaterial(void);
void D3DDevice_GetBackMaterial(void);
void D3DDevice_GetLight(void);
void D3DDevice_GetLightEnable(void);
void D3DDevice_SwitchTexture(void);
void D3DDevice_AddRef(void);
void D3DDevice_Release(void);
void D3DDevice_BlockOnFence(void);
void D3DDevice_KickPushBuffer(void);
void D3DDevice_GetVisibilityTestResult(void);
void D3DDevice_SetVerticalBlankCallback(void);
void D3DDevice_GetProjectionViewportMatrix(void);
void D3DDevice_GetModelView(void);
void D3DDevice_GetTile(void);
void D3DDevice_GetScissors(void);
void D3DDevice_SetFlickerFilter(void);
void D3DDevice_SetSoftDisplayFilter(void);
void D3DDevice_InsertFence(void);
void D3DResource_AddRef(void);
void D3DBaseTexture_GetLevelCount(void);
void D3DDevice_GetDisplayMode(void);
void D3DDevice_Reset(void);
void D3DDevice_CopyRects(void);
void D3DDevice_GetRenderTarget(void);
void D3DDevice_SetViewport(void *viewport);
void D3DDevice_SetLight(void);
void D3DDevice_LightEnable(void);
void D3DDevice_GetTexture2(void);
void D3DDevice_SetPalette(void);
void D3DDevice_SetIndices(void);
void D3DDevice_IsBusy(void);
void D3DDevice_BeginVisibilityTest(void);
void D3DDevice_EndVisibilityTest(void);
void D3DDevice_GetDisplayFieldStatus(void);
void D3DDevice_FlushVertexCache(void);
void D3DDevice_SetModelView(void);
void D3DDevice_SetTile(void);
void D3DDevice_SetScissors(void);
void D3DDevice_SetRenderState_MultiSampleType(void);
void D3DDevice_SetRenderState_PSTextureModes(void);
void D3DDevice_SetRenderStateNotInline(void);
void D3DDevice_SetRenderState2(void);
void D3DDevice_SetRenderState_EdgeAntiAlias(void);
void D3DDevice_SetRenderState_ShadowFunc(void);
void D3DDevice_SetRenderState_FogColor(void);
void D3DDevice_SetRenderState_FrontFace(void);
void D3DDevice_SetRenderState_NormalizeNormals(void);
void D3DDevice_SetRenderState_TextureFactor(void);
void D3DDevice_SetRenderState_LineWidth(void);
void D3DDevice_SetRenderState_Dxt1NoiseEnable(void);
void D3DDevice_SetRenderState_ZBias(uint32_t value);
void D3DDevice_SetRenderState_LogicOp(void);
void D3DDevice_SetRenderState_FillMode(uint32_t value);
void D3DDevice_SetRenderState_BackFillMode(void);
void D3DDevice_SetRenderState_TwoSidedLighting(void);
void D3DDevice_SetRenderState_VertexBlend(void);
void D3DDevice_SetTextureState_TexCoordIndex(void);
void D3DDevice_SetTextureState_BumpEnv(void);
void D3DDevice_SetTextureState_ColorKeyColor(void);
void D3DDevice_SetTextureStageStateNotInline(void);
void D3D_CommonSetDebugRegisters(void);
void D3DDevice_SetRenderState_StencilEnable(uint32_t value);
void D3DDevice_SetRenderState_StencilFail(uint32_t value);
void D3DDevice_SetRenderState_YuvEnable(void);
void D3DDevice_SetRenderState_OcclusionCullEnable(void);
void D3DDevice_SetRenderState_StencilCullEnable(void);
void D3DDevice_SetRenderState_RopZCmpAlwaysRead(void);
void D3DDevice_SetRenderState_RopZRead(void);
void D3DDevice_SetRenderState_DoNotCullUncompressed(void);
void D3DDevice_SetRenderState_MultiSampleAntiAlias(void);
void D3DDevice_SetRenderState_MultiSampleMask(void);
void D3DDevice_GetShaderConstantMode(void);
void D3DDevice_CreateVertexShader(void);
void D3DDevice_GetVertexShader(void);
void D3DDevice_GetVertexShaderConstant(void);
void D3DDevice_GetVertexShaderInput(void);
void D3DDevice_SetStreamSource(uint32_t stream, void *vertex_buffer, uint32_t stride);
void D3DDevice_RunVertexStateShader(void);
void D3DDevice_LoadVertexShader(void);
void D3DDevice_LoadVertexShaderProgram(void);
void D3DDevice_SelectVertexShader(void);
void D3DDevice_GetVertexShaderSize(void);
void D3DDevice_GetVertexShaderType(void);
void D3DDevice_SetShaderConstantMode(void);
void D3DDevice_DeleteVertexShader(void);
void D3DDevice_SetVertexShaderConstant(int register_index, const void *data, uint32_t count);
void D3DDevice_GetVertexShaderDeclaration(void);
void D3DDevice_GetVertexShaderFunction(void);
void D3DDevice_SetVertexShaderInput(void);
void D3DDevice_CreatePixelShader(void);
void D3DDevice_DeletePixelShader(void);
void D3DDevice_GetPixelShader(void);
void D3DDevice_SetPixelShader(void);
void D3DDevice_SetPixelShaderConstant(void);
void D3DDevice_DrawVerticesUP(void);
void D3DDevice_DrawIndexedVerticesUP(void);
void D3DDevice_DrawVertices(uint32_t primitive_type, uint32_t start_vertex, uint32_t vertex_count);
void D3DDevice_DrawIndexedVertices(void);
void D3DDevice_PrimeVertexCache(void);
void D3DDevice_SetVertexData4s(void);
void D3DDevice_SetVertexData4ub(uint32_t reg, uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void D3DResource_GetType(void);
void D3DTexture_GetSurfaceLevel(void);
void D3DCubeTexture_GetCubeMapSurface(void);
/* D3DCubeTexture_LockRect — see d3d_resource.c */
/* D3DVolumeTexture_LockBox — see d3d_resource.c */
void D3D_CreateTexture(void);
void D3D_SetPushBufferSize(void);
void Direct3D_CreateDevice(void);
void D3DDevice_Present(void *source_rect, void *dest_rect, void *window_override, void *dirty_region);
void D3D_GetAdapterIdentifier(void);
void D3D_GetAdapterModeCount(void);
void D3D_EnumAdapterModes(void);
void D3D_GetDeviceCaps(void);
void D3D_GetAdapterDisplayMode(void);
void D3D_CheckDeviceFormat(void);
void Direct3D_CheckDeviceMultiSampleType(void);
void D3DDevice_CreateIndexBuffer(void);
void D3DPalette_Lock(void);
int D3DDevice_CreateVertexBuffer(uint32_t length, uint32_t usage, uint32_t fvf, uint32_t pool, void **ppVertexBuffer);
void D3DVertexBuffer_Lock(void);
void D3DVertexBuffer_GetDesc(void);
void D3DDevice_CreatePalette(void);
int D3DSurface_GetDesc(void *surface, void *desc);
/* D3DSurface_LockRect — see d3d_resource.c */
void D3DDevice_IsFencePending(void);
void D3DDevice_InsertCallback(uint32_t type, void *callback, uint32_t context);
void CDevice_KickOff(void);
void D3D_SetFence(void);
void CDevice_MakeSpace(void);
void D3D_BlockOnResource(void);
void XMETAL_StartPush(void);
void D3D_UpdateProjectionViewportTransform(void);
void D3D_LazySetPointParams(void);
void CDevice_SetStateVB(void);
void CDevice_SetStateUP(void);
void CDevice_FreeFrameBuffers(void);
void CDevice_InitializeFrameBuffers(void);
void Lock3DSurface(void);
void CMiniport_GetDisplayCapabilities(void);
void CMiniport_IsFlipPending(void);
void D3D_AllocContiguousMemory(void);
void CMiniport_CreateCtxDmaObject(void);
void CMiniport_InitHardware(void);
void D3D_ClearStateBlockFlags(void);
void D3DDevice_BeginStateBlock(void);
void D3DDevice_Suspend(void);
void D3D_RecordStateBlock(void);
void D3DDevice_ApplyStateBlock(void);
void D3DDevice_CaptureStateBlock(void);
void D3DDevice_DeleteStateBlock(void);
void D3DDevice_CreateStateBlock(void);
void D3DDevice_EndStateBlock(void);
void DirectSoundEnterCriticalSection(void);
void CMcpxAPU_ServiceDeferredCommandsLow(void);
void CMcpxVoiceClient_SetVolume(void);
void IDirectSound_AddRef(void);
void IDirectSound_Release(void);
void IDirectSoundBuffer_Unlock(void);
void IDirectSoundBuffer_AddRef(void);
void IDirectSoundBuffer_Release(void);
void DirectSoundGetSampleTime(void);
void DirectSoundUseFullHRTF(void);
void DirectSoundUseLightHRTF(void);
void DSound_CRefCount_AddRef(void);
void DSound_CRefCount_Release(void);
void CDirectSound_GetCaps(void);
void CDirectSound_GetSpeakerConfig(void);
void CDirectSound_DownloadEffectsImage(void);
void CDirectSound_SetEffectData(void);
void CDirectSound_GetEffectData(void);
void CDirectSound_CommitEffectData(void);
void CDirectSound_SetMixBinHeadroom(void);
void CDirectSound_SetAllParameters(void);
void CDirectSound_SetDistanceFactor(void);
void CDirectSound_SetDopplerFactor(void);
void CDirectSound_SetRolloffFactor(void);
void CDirectSound_SetOrientation(void);
void CDirectSound_SetPosition(void);
void CDirectSound_SetVelocity(void);
void CDirectSound_SetI3DL2Listener(void);
void CDirectSound_CommitDeferredSettings(void);
void CDirectSound_GetTime(void);
void CDirectSound_DoWork(void);
void CDirectSound_EnableHeadphones(void);
void CDirectSoundVoice_SetPitch(void);
void CDirectSoundVoice_SetVolume(void);
void CDirectSoundVoice_SetLFO(void);
void CDirectSoundVoice_SetEG(void);
void CDirectSoundVoice_SetFilter(void);
void CDirectSoundVoice_SetHeadroom(void);
void CDirectSoundVoice_SetMixBinVolumes(void);
void CDirectSoundVoice_SetAllParameters(void);
void CDirectSoundVoice_SetConeAngles(void);
void CDirectSoundVoice_SetConeOrientation(void);
void CDirectSoundVoice_SetConeOutsideVolume(void);
void CDirectSoundVoice_SetMaxDistance(void);
void CDirectSoundVoice_SetMinDistance(void);
void CDirectSoundVoice_SetMode(void);
void CDirectSoundVoice_SetPosition(void);
void CDirectSoundVoice_SetVelocity(void);
void CDirectSoundVoice_SetI3DL2Source(void);
void CDirectSoundBuffer_PlayEx(void);
void CDirectSoundBuffer_StopEx(void);
void CDirectSoundBuffer_GetStatus(void);
void CDirectSoundBuffer_SetLoopRegion(void);
void CDirectSoundBuffer_GetCurrentPosition(void);
void CDirectSoundBuffer_Lock(void);
void CDirectSoundBuffer_SetCurrentPosition(void);
void CDirectSoundStream_GetInfo(void);
void CDirectSoundStream_Discontinuity(void);
void CDirectSoundStream_Flush(void);
void CDirectSoundStream_GetStatus__r1(void);
void CDirectSoundStream_Process(void);
void CDirectSoundStream_Pause(void);
void CDirectSoundBuffer_SetVolume(void);
void CDirectSoundBuffer_SetPitch(void);
void CDirectSoundBuffer_SetLFO(void);
void CDirectSoundBuffer_SetEG(void);
void CDirectSoundBuffer_SetFilter(void);
void CDirectSoundBuffer_SetHeadroom(void);
void CDirectSoundBuffer_SetMixBinVolumes(void);
void CDirectSoundBuffer_SetAllParameters(void);
void CDirectSoundBuffer_SetConeAngles(void);
void CDirectSoundBuffer_SetConeOrientation(void);
void CDirectSoundBuffer_SetConeOutsideVolume(void);
void CDirectSoundBuffer_SetMaxDistance(void);
void CDirectSoundBuffer_SetMinDistance(void);
void CDirectSoundBuffer_SetMode(void);
void CDirectSoundBuffer_SetPosition(void);
void CDirectSoundBuffer_SetVelocity(void);
void CDirectSoundBuffer_SetI3DL2Source(void);
void CDirectSoundStream_SetPitch(void);
void CDirectSoundStream_SetVolume(void);
void CDirectSoundStream_SetLFO(void);
void CDirectSoundStream_SetEG(void);
void CDirectSoundStream_SetFilter(void);
void CDirectSoundStream_SetHeadroom(void);
void CDirectSoundStream_SetMixBinVolumes_12(void);
void CDirectSoundStream_SetAllParameters(void);
void CDirectSoundStream_SetConeAngles(void);
void CDirectSoundStream_SetConeOrientation(void);
void CDirectSoundStream_SetConeOutsideVolume(void);
void CDirectSoundStream_SetMaxDistance(void);
void CDirectSoundStream_SetMinDistance(void);
void CDirectSoundStream_SetMode(void);
void CDirectSoundStream_SetPosition(void);
void CDirectSoundStream_SetVelocity(void);
void CDirectSoundStream_SetI3DL2Source(void);
void IDirectSound_GetCaps(void);
void IDirectSound_GetSpeakerConfig(void);
void IDirectSound_DownloadEffectsImage(void);
void IDirectSound_GetEffectData(void);
void IDirectSound_SetEffectData(void);
void IDirectSound_CommitEffectData(void);
void IDirectSound_EnableHeadphones(void);
void IDirectSound_SetMixBinHeadroom(void);
void IDirectSound_SetAllParameters(void);
void IDirectSound_SetDistanceFactor(void);
void IDirectSound_SetDopplerFactor(void);
void IDirectSound_SetOrientation(void);
void IDirectSound_SetPosition(void);
void IDirectSound_SetRolloffFactor(void);
void IDirectSound_SetVelocity(void);
void IDirectSound_CommitDeferredSettings(void);
void IDirectSound_GetTime(void);
void IDirectSound_SetI3DL2Listener(void);
void IDirectSoundBuffer_SetLFO(void);
void IDirectSoundBuffer_SetEG(void);
void IDirectSoundBuffer_SetFilter(void);
void IDirectSoundBuffer_SetHeadroom(void);
void IDirectSoundBuffer_SetMixBinVolumes_12(void);
void IDirectSoundBuffer_SetAllParameters(void);
void IDirectSoundBuffer_SetConeAngles(void);
void IDirectSoundBuffer_SetConeOrientation(void);
void IDirectSoundBuffer_SetConeOutsideVolume(void);
void IDirectSoundBuffer_SetMaxDistance(void);
void IDirectSoundBuffer_SetMinDistance(void);
void IDirectSoundBuffer_SetMode(void);
void IDirectSoundBuffer_SetPosition(void);
void IDirectSoundBuffer_SetVelocity(void);
void IDirectSoundBuffer_PlayEx(void);
void IDirectSoundBuffer_StopEx(void);
void IDirectSoundBuffer_GetStatus(void);
void IDirectSoundBuffer_GetCurrentPosition(void);
void IDirectSoundBuffer_Lock(void);
void IDirectSoundBuffer_SetI3DL2Source(void);
void IDirectSoundStream_SetPitch(void);
void IDirectSoundStream_SetLFO(void);
void IDirectSoundStream_SetEG(void);
void IDirectSoundStream_SetFilter(void);
void IDirectSoundStream_SetHeadroom(void);
void IDirectSoundStream_SetMixBinVolumes_12(void);
void IDirectSoundStream_SetConeOrientation(void);
void IDirectSoundStream_SetMode(void);
void IDirectSoundStream_SetPosition(void);
void IDirectSoundStream_SetVelocity(void);
void IDirectSoundStream_Pause(void);
void DirectSoundDoWork(void);
void CDirectSoundVoice_SetFrequency(void);
void CDirectSoundVoice_SetOutputBuffer(void);
void CDirectSoundVoice_SetMixBins(void);
void CDirectSoundBufferSettings_SetBufferData(void);
void CDirectSoundBuffer_SetBufferData(void);
void CDirectSoundBuffer_Play(void);
void CDirectSoundBuffer_Stop(void);
void CDirectSoundBuffer_SetNotificationPositions(void);
void CDirectSoundBuffer_SetOutputBuffer(void);
void CDirectSoundStream_AddRef(void);
void CDirectSoundStream_Release(void);
void CDirectSoundStream_SetOutputBuffer(void);
void CDirectSoundBuffer_SetFrequency(void);
void CDirectSoundBuffer_SetMixBins(void);
void CDirectSoundStream_SetFrequency(void);
void CDirectSoundStream_SetMixBins(void);
void IDirectSoundBuffer_SetFrequency(void);
void IDirectSoundBuffer_SetOutputBuffer(void);
void IDirectSoundBuffer_SetMixBins(void);
void IDirectSoundBuffer_Stop(void);
void IDirectSoundBuffer_SetNotificationPositions(void);
void IDirectSoundStream_SetOutputBuffer(void);
void IDirectSoundStream_SetMixBins(void);
void CDirectSoundStream_Constructor(void);
void CDirectSound_CreateSoundBuffer(void);
void CDirectSound_CreateSoundStream(void);
void IDirectSound_CreateSoundBuffer(void);
void IDirectSound_CreateSoundStream(void);
void DirectSoundCreate(void);
void DirectSoundCreateStream(void);
void CMcpxAPU_Commit3dSettings(void);
void CMcpxAPU_SetMixBinHeadroom(void);
void CMcpxAPU_Set3dParameters(void);
void CMcpxAPU_Set3dDistanceFactor(void);
void CMcpxAPU_Set3dDopplerFactor(void);
void CMcpxAPU_Set3dRolloffFactor(void);
void CMcpxAPU_Set3dPosition(void);
void CMcpxAPU_Set3dVelocity(void);
void CMcpxAPU_SetI3DL2Listener(void);
void CMcpxVoiceClient_SetFilter(void);
void CMcpxVoiceClient_SetMixBins(void);
void CMcpxVoiceClient_SetPitch(void);
void CMcpxVoiceClient_SetLFO(void);
void CMcpxVoiceClient_SetEG(void);
void CMcpxVoiceClient_Commit3dSettings(void);
void CMcpxVoiceClient_Set3dParameters(void);
void CMcpxVoiceClient_Set3dConeOrientation(void);
void CMcpxVoiceClient_Set3dConeOutsideVolume(void);
void CMcpxVoiceClient_Set3dMaxDistance(void);
void CMcpxVoiceClient_Set3dMinDistance(void);
void CMcpxVoiceClient_Set3dMode(void);
void CMcpxVoiceClient_Set3dPosition(void);
void CMcpxVoiceClient_Set3dVelocity(void);
void CMcpxVoiceClient_SetI3DL2Source(void);
void CSensaura3d_GetFullHRTFFilterPair(void);
void CSensaura3d_GetLiteHRTFFilterPair(void);
void CMcpxBuffer_GetStatus(void);
void CMcpxBuffer_GetCurrentPosition(void);
void CMcpxBuffer_Stop(void);
void CMcpxBuffer_SetCurrentPosition(void);
void CMcpxBuffer_SetBufferData(void);
void CMcpxBuffer_Play(void);
void CMcpxStream_Pause(void);
void CMcpxStream_Flush(void);
void CMcpxStream_Discontinuity(void);
void XAudioCalculatePitch(void);
void XAudioCreatePcmFormat(void);
void XAudioCreateAdpcmFormat(void);
void IsValidFormat(void);
void GetLastError(void);
void ioctlsocket(void);
void listen(void);
int bind(void *xnet, unsigned int socket, const void *name, int namelen);
int connect(void *xnet, unsigned int socket, const void *name, int namelen);
int socket(void *xnet, int af, int type, int protocol);
int recv(void *xnet, unsigned int socket, char *buf, int len, int flags);
int send(void *xnet, unsigned int socket, const char *buf, int len, int flags);
void MU_Init(void);
void IUsbInit_GetMaxDeviceTypeCount(void);
void FUN_0024ba93(void);
void XInitDevices(void);
void XInputOpen(void);
void XInputClose(void);
void XInputGetCapabilities(void);
void XInputGetState(void);
void XInputPoll(void);
void XGetDevices(void);
void XGetDeviceChanges(void);
void XID_fCloseDevice(void);

/* QueueUserAPC (0x1cfb73) — XBE naked draft (batch 367). */
#if defined(__clang__)


__attribute__((naked, noinline))
void QueueUserAPC(void)
{
  __asm__ volatile(
      "pushl $0\n\t"
      "pushl 0x10(%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "pushl $0x1cfb68\n\t"
      "pushl 0x18(%%esp)\n\t"
      "call *0x2530c4\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "setge %%cl\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "QueueUserAPC: clang naked draft required"
#endif


/* ExitThread (0x1cfbab) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b1cfbab_c1cf944)(void) = XapiCallThreadNotifyRoutines;
static void __stdcall (*const b1cfbab_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void ExitThread(void)
{
  __asm__ volatile(
      "pushl $0\n\t"
      "call *%[c1cf944]\n\t"
      "pushl 0x4(%%esp)\n\t"
      "call *0x2530cc\n\t"
      ".byte 0xcc\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x2530ac\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530a8\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LExitThread_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpb $0, 0x4(%%ecx)\n\t"
      "je .LExitThread_1\n\t"
      "movl 0x120(%%ecx), %%eax\n\t"
      "jmp .LExitThread_2\n\t"
      ".LExitThread_1:\n\t"
      "movl $0x103, %%eax\n\t"
      ".LExitThread_2:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "call *0x2530a0\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LExitThread_4\n\t"
      ".LExitThread_3:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LExitThread_4:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1cf944] "m"(b1cfbab_c1cf944), [c1d2296] "m"(b1cfbab_c1d2296)
      : "memory");
}
#else
#error "ExitThread: clang naked draft required"
#endif


/* XapiThreadStartup (0x1cfcf4) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b1cfcf4_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1cfcf4_c1cf944)(void) = XapiCallThreadNotifyRoutines;
static void (*const b1cfcf4_c1cf97c)(void) = UnhandledExceptionFilter;
static void __stdcall (*const b1cfcf4_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void XapiThreadStartup(void)
{
  __asm__ volatile(
      "pushl $0x18\n\t"
      "pushl $0x2c1bd8\n\t"
      "call *%[c1dd5c8]\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "movl 0x28, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x28(%%eax), %%edx\n\t"
      "addl $4, %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x4(%%edx)\n\t"
      "movl 0x2c1e3c, %%ebx\n\t"
      "movl 0x2c1e38, %%esi\n\t"
      "subl %%esi, %%ebx\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $2, %%ecx\n\t"
      "rep movsl\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "movl 0x2c1e48, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LXapiThreadStartup_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ebx,%%edx,1), %%edi\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      ".LXapiThreadStartup_1:\n\t"
      "pushl $1\n\t"
      "call *%[c1cf944]\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *0x8(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "pushl $0\n\t"
      "call *%[c1cf944]\n\t"
      "jmp .LXapiThreadStartup_2\n\t"
      "pushl -0x14(%%ebp)\n\t"
      "call *%[c1cf97c]\n\t"
      "ret\n\t"
      "movl -0x18(%%ebp), %%esp\n\t"
      ".LXapiThreadStartup_2:\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "pushl -0x28(%%ebp)\n\t"
      "call *0x2530cc\n\t"
      ".byte 0xcc\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LXapiThreadStartup_3\n\t"
      "movl 0x10130, %%eax\n\t"
      ".LXapiThreadStartup_3:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl $0x1cfcf4\n\t"
      "pushl $0\n\t"
      "shrl $2, %%ecx\n\t"
      "andl $0xffffff01, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "pushl 0x632a30\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530d4\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LXapiThreadStartup_4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LXapiThreadStartup_5\n\t"
      ".LXapiThreadStartup_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LXapiThreadStartup_5:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1cfcf4_c1dd5c8), [c1cf944] "m"(b1cfcf4_c1cf944), [c1cf97c] "m"(b1cfcf4_c1cf97c), [c1d2296] "m"(b1cfcf4_c1d2296)
      : "memory");
}
#else
#error "XapiThreadStartup: clang naked draft required"
#endif


/* PulseEvent (0x1cfee8) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void __stdcall (*const b1cfee8_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void PulseEvent(void)
{
  __asm__ volatile(
      "pushl $0\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *0x2530f0\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LPulseEvent_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LPulseEvent_2\n\t"
      ".LPulseEvent_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LPulseEvent_2:\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cfee8_c1d2296)
      : "memory");
}
#else
#error "PulseEvent: clang naked draft required"
#endif


/* 0x001d3717 */
void MmQueryAllocationSize(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  ExQueryNonVolatileSetting(0, 0, 0, 0);
  ExQueryNonVolatileSetting(0, 0, 0, 0);
  /* test eax, eax -> jl 0x1d44a7 */
  ExQueryNonVolatileSetting(259, 0, 0, 0);
  /* test eax, eax -> jl 0x1d44d8 */
  ExQueryNonVolatileSetting(0, 0, 0, 0);
  /* test eax, eax -> jl 0x1d4503 */
  ExQueryNonVolatileSetting(0, 0, 0, 0);
  /* test eax, eax -> jge 0x1d4527 */
  /* cmp eax, 3 -> je 0x1d453f */
  /* cmp eax, 6 -> jne 0x1d4546 */
  ExQueryNonVolatileSetting(10, 0, 0, 0);
  /* test eax, eax -> jl 0x1d456c */
  ExQueryNonVolatileSetting(260, 0, 0, 0);
  /* test eax, eax -> jl 0x1d4594 */
  FUN_001dd5c8();
  /* test (char)eax, 1 -> jne 0x1d45d0 */
  /* relift: cmp dword ptr [ebp - 0x28], 0x40 -> jae 0x1d4675 */
  /* test edi, edi -> je 0x1d4656 */
  /* relift: cmp esi, dword ptr [edi + 0x2c] -> jae 0x1d4656 */
  /* relift: test byte ptr [esi + 5], 1 -> jne 0x1d4628 */
  /* relift: test byte ptr [esi + 5], 0x10 -> je 0x1d4652 */
  /* test ebx, ebx -> jne 0x1d4642 */
  /* relift: FUN_001d468d(0, 0); */
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d46a2 */
  /* relift: cmp eax, dword ptr [ecx + 4] -> je 0x1d470f */
  /* test eax, eax -> jge 0x1d46fe */
  /* test eax, eax -> jl 0x1d46f7 */
  /* test eax, eax -> jge 0x1d4764 */
  /* cmp edx, ecx -> jb 0x1d47a3 */
  /* cmp edx, ecx -> ja 0x1d485c */
  /* relift: cmp ecx, dword ptr [ebp + 0xc] -> jne 0x1d4829 */
  FUN_001d47c3();
  /* relift: cmp edi, dword ptr [esi + 0x1c] -> jbe 0x1d482b */
  /* test eax, eax -> jne 0x1d47f5 */
  FUN_001d46a3();
  /* test eax, eax -> je 0x1d4855 */
  /* relift: cmp edi, dword ptr [esi + 0x1c] -> jb 0x1d4855 */
  /* relift: cmp edx, dword ptr [eax + 4] -> jne 0x1d4831 */
  /* relift: cmp eax, dword ptr [esi + 0x1c] -> jbe 0x1d4855 */
  /* relift: cmp dword ptr [esi + 8], eax -> jb 0x1d48a8 */
  /* test ecx, ecx -> je 0x1d48bd */
  /* relift: cmp dword ptr [esi + 4], ecx -> je 0x1d48bd */
  /* test esi, esi -> jne 0x1d489a */
  /* test eax, eax -> je 0x1d48da */
  /* test eax, eax -> jl 0x1d48b4 */
  /* relift: cmp eax, dword ptr [esi + 8] -> jne 0x1d4906 */
  /* relift: cmp ecx, dword ptr [esi + 4] -> je 0x1d4969 */
  /* test ecx, ecx -> jne 0x1d492e */
  /* relift: test byte ptr [ebx + 5], 0x10 -> jne 0x1d4969 */
  /* cmp ebx, ecx -> jae 0x1d495d */
  /* relift: cmp word ptr [ebx], 0 -> je 0x1d495d */
  /* relift: test byte ptr [ebx + 5], 0x10 -> je 0x1d4940 */
  /* relift: cmp ebx, dword ptr [ebp + 0xc] -> jne 0x1d48b4 */
  /* relift: cmp ecx, dword ptr [edi + 0x2c] -> jne 0x1d498a */
  FUN_001d47c3();
  /* relift: cmp dword ptr [edi + 0x1c], 0 -> jne 0x1d48b6 */
  /* relift: cmp edx, dword ptr [edi + 0x1c] -> jb 0x1d49f7 */
  /* test ecx, ecx -> jne 0x1d49ec */
  /* relift: test byte ptr [eax + 0x14], 1 -> jne 0x1d4a2e */
  /* cmp esi, edi -> je 0x1d4b8c */
  /* relift: test byte ptr [esi + 5], 1 -> jne 0x1d4b8c */
  /* cmp ecx, 0xff00 -> ja 0x1d4b8f */
  /* relift: cmp byte ptr [ebp + 0x14], 0 -> je 0x1d4ae6 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d4aab */
  /* test (char)ecx, 4 -> je 0x1d4adc */
  /* test (char)ecx, 2 -> je 0x1d4ac9 */
  /* cmp eax, 4 -> jbe 0x1d4ac9 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d4b1a */
  /* test (char)ecx, 4 -> je 0x1d4b4b */
  /* test (char)ecx, 2 -> je 0x1d4b38 */
  /* cmp eax, 4 -> jbe 0x1d4b38 */
  /* relift: test byte ptr [edi + 5], 0x10 -> jne 0x1d4cd0 */
  /* relift: test byte ptr [esi + 5], 1 -> jne 0x1d4cd0 */
  /* cmp edx, 0xff00 -> ja 0x1d4cd0 */
  /* relift: cmp byte ptr [ebp + 0x14], 0 -> je 0x1d4c2e */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d4bf7 */
  /* test (char)ecx, 4 -> je 0x1d4c28 */
  /* test (char)ecx, 2 -> je 0x1d4c15 */
  /* cmp eax, 4 -> jbe 0x1d4c15 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d4c7b */
  /* test (char)ecx, 4 -> je 0x1d4cac */
  /* test (char)ecx, 2 -> je 0x1d4c99 */
  /* cmp eax, 4 -> jbe 0x1d4c99 */
  /* cmp ecx, 0xff00 -> jbe 0x1d4d35 */
  /* relift: cmp dword ptr [esi], esi -> jne 0x1d4d93 */
  /* relift: cmp (int16_t)ebx, word ptr [esi - 8] -> jbe 0x1d4d93 */
  /* cmp ecx, esi -> jne 0x1d4d87 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d4d11 */
  /* relift: test byte ptr [ebp + 0xf], 0x10 -> jne 0x1d4dcc */
  /* relift: test byte ptr [eax + 5], 8 -> je 0x1d4de2 */
  /* relift: test byte ptr [ecx + 5], 8 -> je 0x1d4e10 */
  /* test edi, edi -> je 0x1d4ebf */
  /* cmp ebx, esi -> jne 0x1d4e4c */
  /* relift: test byte ptr [edi + 0x14], 1 -> jne 0x1d4e79 */
  /* test esi, esi -> jne 0x1d4e82 */
  /* test eax, eax -> je 0x1d4eba */
  FUN_001d4a02();
  /* relift: cmp edx, dword ptr [ebx + 0x1c] -> jbe 0x1d4edf */
  FUN_001d4877();
  /* test eax, eax -> jne 0x1d4f2b */
  FUN_001d4a34();
  /* relift: cmp edx, dword ptr [ebp + 0x18] -> jae 0x1d4f5c */
  FUN_001d4cd9();
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d4fb6 */
  /* test (char)ecx, 4 -> je 0x1d4fe7 */
  /* test (char)ecx, 2 -> je 0x1d4fd4 */
  /* cmp eax, 4 -> jbe 0x1d4fd4 */
  /* relift: test byte ptr [ebp - 2], 2 -> je 0x1d502f */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d50de */
  /* relift: cmp dword ptr [edx], edx -> jne 0x1d50f4 */
  /* relift: cmp (int16_t)ecx, word ptr [edx - 8] -> jbe 0x1d50f4 */
  /* cmp eax, edx -> jne 0x1d50e8 */
  /* test (char)eax, 1 -> je 0x1d5194 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d5175 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d525b */
  /* relift: cmp (int16_t)ecx, word ptr [edi - 8] -> jbe 0x1d525b */
  /* cmp eax, edi -> jne 0x1d517f */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d51c7 */
  /* test (char)ecx, 4 -> je 0x1d51f5 */
  /* test (char)ecx, 2 -> je 0x1d51e5 */
  /* cmp eax, 4 -> jbe 0x1d51e5 */
  /* cmp eax, 0xff00 -> ja 0x1d5273 */
  /* cmp (int16_t)ecx, 0x80 -> jb 0x1d5146 */
  /* relift: cmp (int16_t)ecx, word ptr [edi - 8] -> jbe 0x1d525b */
  /* cmp eax, edi -> jne 0x1d524f */
  FUN_001d4cd9();
  /* test dl, 8 -> je 0x1d52a9 */
  /* cmp ecx, esi -> jbe 0x1d52a9 */
  /* test (char)eax, 1 -> jne 0x1d52d4 */
  /* test (char)eax, 8 -> je 0x1d52e3 */
  /* relift: cmp eax, dword ptr [ebp + 0x18] -> jne 0x1d5329 */
  /* cmp eax, ecx -> jb 0x1d5377 */
  /* relift: cmp eax, dword ptr [ebp + 0x20] -> jae 0x1d5367 */
  /* test eax, eax -> jge 0x1d536e */
  FUN_001d47e4();
  FUN_001d4cd9();
  /* relift: cmp esi, dword ptr [ecx + 0x30] -> ja 0x1d5478 */
  /* relift: cmp eax, dword ptr [ecx + 0x1c] -> ja 0x1d5478 */
  FUN_001d4877();
  /* test eax, eax -> jne 0x1d555b */
  /* relift: cmp byte ptr [ebp - 0xc], 0x40 -> jne 0x1d5478 */
  /* relift: cmp byte ptr [ebp + 0xf], 0x40 -> jb 0x1d5439 */
  /* relift: cmp byte ptr [ebp - 0xc], 0x40 -> je 0x1d558f */
  /* relift: test byte ptr [edi + 0x14], 2 -> je 0x1d558f */
  /* test eax, eax -> jge 0x1d54fb */
  /* relift: cmp dword ptr [ebp + 8], ecx -> je 0x1d54f3 */
  /* relift: cmp dword ptr [ebp + 8], ecx -> jae 0x1d54e0 */
  /* test eax, eax -> jl 0x1d54cd */
  /* test eax, eax -> jl 0x1d558f */
  /* test esi, esi -> jl 0x1d557c */
  FUN_001d52f3();
  /* test (char)eax, (char)eax -> jne 0x1d554f */
  /* test esi, esi -> jl 0x1d557c */
  FUN_001d4a34();
  FUN_001d4cd9();
  /* relift: cmp dword ptr [ebx + 0x584], 0 -> je 0x1d55bc */
  FUN_001d4cd9();
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1d561d */
  /* cmp eax, esi -> jne 0x1d561d */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1d5662 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d5662 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d5831 */
  FUN_001d46a3();
  FUN_001d47c3();
  /* relift: cmp dword ptr [ebp - 0x20], 0 -> jl 0x1d5831 */
  FUN_001d47e4();
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1d577b */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d5737 */
  /* relift: cmp (int16_t)ecx, word ptr [eax - 8] -> jbe 0x1d5757 */
  /* cmp ecx, eax -> jne 0x1d5741 */
  /* test eax, eax -> je 0x1d5788 */
  /* cmp eax, ecx -> jb 0x1d57a1 */
  /* cmp eax, esi -> jae 0x1d57a1 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1d5823 */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d57f5 */
  /* relift: cmp dword ptr [esi], esi -> jne 0x1d580b */
  /* relift: cmp (int16_t)eax, word ptr [esi - 8] -> jbe 0x1d580b */
  /* cmp ecx, esi -> jne 0x1d57ff */
  /* test eax, eax -> je 0x1d583b */
  FUN_001d4cd9();
  FUN_001dd5c8();
  /* cmp eax, esi -> je 0x1d58a5 */
  /* relift: cmp dword ptr [eax], 0x30 -> jne 0x1d587d */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 48);
  /* cmp ebx, esi -> jl 0x1d5bed */
  /* relift: test byte ptr [0x632a22], 0x20 -> je 0x1d58b2 */
  /* relift: cmp dword ptr [ebp - 0x48], esi -> jne 0x1d58bf */
  /* relift: cmp dword ptr [ebp - 0x44], esi -> jne 0x1d58cc */
  /* relift: cmp dword ptr [ebp - 0x40], esi -> jne 0x1d58d9 */
  /* relift: cmp dword ptr [ebp - 0x3c], esi -> jne 0x1d58e6 */
  /* relift: cmp dword ptr [ebp - 0x38], esi -> jne 0x1d58f2 */
  /* relift: cmp dword ptr [ebp - 0x34], esi -> je 0x1d5900 */
  /* relift: cmp dword ptr [ebp - 0x34], 0xff000 -> jbe 0x1d5907 */
  /* cmp eax, esi -> jne 0x1d5934 */
  /* cmp eax, esi -> jne 0x1d5925 */
  /* cmp edx, esi -> jne 0x1d5956 */
  /* relift: test byte ptr [ebp + 8], 1 -> jne 0x1d5986 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> je 0x1d5979 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d5bed */
  /* cmp edi, esi -> je 0x1d5a64 */
  /* relift: cmp dword ptr [ebp - 0x28], esi -> je 0x1d59da */
  /* cmp ebx, esi -> je 0x1d5bed */
  /* cmp eax, esi -> je 0x1d5bed */
  /* cmp ebx, eax -> ja 0x1d5bed */
  /* relift: test byte ptr [ebp + 8], 2 -> jne 0x1d5bed */
  /* test eax, eax -> jl 0x1d5bed */
  /* relift: cmp edi, dword ptr [ebp + 0xc] -> jne 0x1d5bed */
  /* relift: cmp dword ptr [ebp - 0x64], 0x10000 -> je 0x1d5bed */
  /* relift: cmp dword ptr [ebp - 0x64], eax -> jne 0x1d5a50 */
  /* test eax, eax -> jl 0x1d5a55 */
  /* relift: cmp dword ptr [ebp - 0x64], 0x2000 -> jne 0x1d5a55 */
  /* relift: cmp dword ptr [ebp - 0x28], esi -> jne 0x1d5bed */
  /* test eax, eax -> jl 0x1d5bed */
  /* relift: cmp dword ptr [ebp + 0x14], esi -> jne 0x1d5a9a */
  /* relift: cmp dword ptr [ebp - 0x58], ebx -> jne 0x1d5ae5 */
  /* test eax, eax -> jge 0x1d5ae2 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d5bed */
  /* relift: test byte ptr [0x632a21], 8 -> je 0x1d5b3a */
  /* cmp edi, -1 -> jne 0x1d5bc4 */
  FUN_001d52f3();
  /* test (char)eax, (char)eax -> jne 0x1d5bf1 */
  __SEH_epilog();
  FUN_001dd5c8();
  /* test eax, eax -> jne 0x1d5c92 */
  /* test (char)ecx, 1 -> jne 0x1d5cbc */
  /* cmp edi, 0x80 -> jae 0x1d5e34 */
  /* relift: cmp dword ptr [eax], eax -> je 0x1d5d4b */
  /* cmp ecx, edi -> jne 0x1d5d27 */
  /* test eax, eax -> je 0x1d5d95 */
  /* test eax, eax -> je 0x1d5dac */
  /* test eax, eax -> je 0x1d5dc3 */
  /* test eax, eax -> je 0x1d5e3d */
  FUN_001d8750(0);
  /* cmp ecx, edx -> jne 0x1d5eac */
  /* relift: cmp edi, dword ptr [esi + 0x1c] -> ja 0x1d629d */
  /* cmp edx, eax -> je 0x1d5e87 */
  /* relift: cmp eax, dword ptr [ebp - 0x28] -> jb 0x1d5e87 */
  /* cmp edx, ecx -> je 0x1d5e87 */
  /* relift: cmp esi, dword ptr [ebp - 0x28] -> jb 0x1d5e83 */
  FUN_001d5411();
  /* test eax, eax -> je 0x1d628e */
  /* test edx, edx -> je 0x1d6238 */
  /* cmp edx, 1 -> jne 0x1d5f00 */
  /* test (char)ecx, 0x10 -> je 0x1d5ff2 */
  /* cmp (int16_t)edx, 0x80 -> jae 0x1d5fa4 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d5f90 */
  /* cmp ecx, eax -> je 0x1d5fce */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jbe 0x1d5fce */
  /* test (char)ecx, 1 -> je 0x1d60c3 */
  /* cmp (int16_t)edx, 0x80 -> jae 0x1d6085 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6071 */
  /* cmp ecx, eax -> je 0x1d60af */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jbe 0x1d60af */
  /* cmp ecx, edi -> jne 0x1d6127 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d6127 */
  /* cmp edx, 0xff00 -> ja 0x1d6215 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d6154 */
  /* cmp (int16_t)edx, 0x80 -> jae 0x1d61d7 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d61b6 */
  /* cmp ecx, eax -> je 0x1d6201 */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jbe 0x1d6201 */
  FUN_001d4cd9();
  /* relift: test byte ptr [esi + 5], 0x10 -> je 0x1d6238 */
  /* relift: test byte ptr [ebp - 0x31], 0x10 -> je 0x1d624a */
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d626c */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d63bb */
  /* relift: test byte ptr [esi + 0x14], 2 -> je 0x1d636c */
  /* test eax, eax -> jl 0x1d6376 */
  /* relift: test byte ptr [ebp + 0xc], 4 -> je 0x1d63b4 */
  FUN_001d63d5();
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d63e7 */
  FUN_001dd5c8();
  /* cmp eax, 0x7fffffff -> jbe 0x1d641a */
  /* cmp eax, edi -> jne 0x1d6421 */
  /* relift: test dword ptr [ebp + 0xc], 0x3c000100 -> jne 0x1d644a */
  /* relift: cmp dword ptr [esi + 0x17c], edi -> je 0x1d6455 */
  /* relift: test byte ptr [ebp + 0xc], 1 -> jne 0x1d6474 */
  /* cmp ebx, 0x80 -> jae 0x1d668c */
  /* cmp eax, edi -> je 0x1d6541 */
  /* cmp eax, ecx -> jne 0x1d64ea */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d64ea */
  /* test (char)ecx, 4 -> je 0x1d6521 */
  /* test (char)ecx, 2 -> je 0x1d650e */
  /* cmp eax, 4 -> jbe 0x1d650e */
  /* cmp ebx, 0x20 -> jae 0x1d65b4 */
  /* test edx, edx -> jne 0x1d65d6 */
  /* test ecx, ecx -> jne 0x1d6644 */
  /* test ecx, ecx -> jne 0x1d65ff */
  /* test ecx, ecx -> je 0x1d6695 */
  FUN_001d8750(0);
  /* cmp ebx, 0x40 -> jae 0x1d6613 */
  /* test edx, edx -> je 0x1d65dd */
  /* test ecx, ecx -> jne 0x1d6644 */
  /* test ecx, ecx -> je 0x1d6695 */
  FUN_001d8750(0);
  /* cmp ebx, 0x60 -> jae 0x1d6658 */
  /* test eax, eax -> jne 0x1d6672 */
  /* test ecx, ecx -> je 0x1d6695 */
  FUN_001d8750(0);
  /* test eax, eax -> je 0x1d6695 */
  FUN_001d8750(0);
  /* relift: cmp ebx, dword ptr [esi + 0x1c] -> ja 0x1d6b4e */
  /* cmp esi, eax -> je 0x1d66b8 */
  /* cmp ecx, ebx -> jae 0x1d66d0 */
  FUN_001d5411();
  /* test edi, edi -> je 0x1d6b3d */
  /* cmp eax, ecx -> jne 0x1d671c */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d671c */
  /* test (char)ecx, 4 -> je 0x1d6756 */
  /* test (char)ecx, 2 -> je 0x1d6740 */
  /* cmp eax, 4 -> jbe 0x1d6740 */
  /* test ebx, ebx -> je 0x1d6aef */
  /* cmp ebx, 1 -> jne 0x1d67a8 */
  /* test dl, 0x10 -> je 0x1d6887 */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6833 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6863 */
  /* cmp edx, edi -> je 0x1d685d */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d685d */
  /* test (char)ecx, 1 -> je 0x1d694a */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6906 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6936 */
  /* cmp edx, edi -> je 0x1d6930 */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d6930 */
  /* cmp ecx, edx -> jne 0x1d69ae */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d69ae */
  /* test (char)ecx, 4 -> je 0x1d69f1 */
  /* test (char)ecx, 2 -> je 0x1d69d8 */
  /* cmp eax, 4 -> jbe 0x1d69d8 */
  /* cmp ebx, 0xff00 -> ja 0x1d6ac7 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d6a21 */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6a83 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6ab3 */
  /* cmp edx, edi -> je 0x1d6aad */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d6aad */
  FUN_001d4cd9();
  /* relift: test byte ptr [esi + 5], 0x10 -> je 0x1d6aef */
  /* relift: test byte ptr [ebp - 0x3d], 0x10 -> je 0x1d6b01 */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d6b16 */
  /* relift: test byte ptr [edi + 5], 2 -> je 0x1d6c60 */
  FUN_001d4dd3();
  /* relift: test byte ptr [esi + 0x14], 2 -> je 0x1d6c01 */
  /* cmp eax, edi -> jl 0x1d6c0b */
  /* relift: test byte ptr [ebp + 0xc], 4 -> je 0x1d6c60 */
  /* test ecx, ecx -> je 0x1d6c7e */
  /* relift: FUN_001d6c92(0, 0); */
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d6ca7 */
  FUN_001dd5c8();
  /* test ecx, ecx -> jne 0x1d6cd2 */
  /* test (char)eax, 1 -> jne 0x1d6cf3 */
  /* relift: test byte ptr [edi + 5], 8 -> jne 0x1d6e00 */
  FUN_001d4a34();
  /* cmp ecx, 0x80 -> jae 0x1d6d84 */
  /* relift: cmp dword ptr [edx], edx -> jne 0x1d6d63 */
  /* relift: cmp ecx, dword ptr [esi + 0x28] -> jb 0x1d6da0 */
  /* relift: cmp edx, dword ptr [esi + 0x2c] -> jb 0x1d6da0 */
  FUN_001d5598();
  /* cmp ecx, 0xff00 -> ja 0x1d6df6 */
  /* cmp esi, ecx -> je 0x1d6dd8 */
  /* relift: cmp (int16_t)edi, word ptr [edx] -> jbe 0x1d6dd8 */
  FUN_001d4cd9();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d6e2c */
  /* test eax, eax -> jge 0x1d6e4e */
  FUN_001d6e65();
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d6e77 */
  FUN_001dd5c8();
  /* relift: test byte ptr [ebp + 0xc], 1 -> jne 0x1d6ead */
  /* test dl, 1 -> je 0x1d6ff9 */
  /* test (char)ecx, 7 -> jne 0x1d6ff9 */
  /* relift: cmp byte ptr [eax + 4], 0x40 -> jae 0x1d6ff9 */
  /* test dl, 8 -> je 0x1d6f1d */
  /* cmp eax, edi -> jl 0x1d6ff9 */
  FUN_001d4a34();
  /* relift: cmp ecx, dword ptr [esi + 0x28] -> jb 0x1d6f51 */
  /* relift: cmp edx, dword ptr [esi + 0x2c] -> jb 0x1d6f51 */
  FUN_001d5598();
  /* cmp ecx, 0xff00 -> ja 0x1d6fed */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6fab */
  /* relift: cmp dword ptr [edx], edx -> jne 0x1d6fcf */
  /* cmp edi, edx -> je 0x1d6fcc */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d6fcc */
  FUN_001d4cd9();
  /* relift: FUN_001d7028(0, 0); */
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d703a */
  FUN_001dd5c8();
  /* test esi, esi -> je 0x1d706c */
  /* cmp edx, 0x7fffffff -> jbe 0x1d7073 */
  /* test edx, edx -> jne 0x1d7078 */
  /* relift: test dword ptr [ebp + 0xc], 0x3c000100 -> jne 0x1d709b */
  /* relift: cmp dword ptr [eax + 0x17c], 0 -> jne 0x1d709b */
  /* relift: test byte ptr [esi - 0xb], 2 -> je 0x1d70a1 */
  /* relift: test byte ptr [ebp + 0xc], 1 -> jne 0x1d70bf */
  /* test (char)eax, 1 -> je 0x1d76e4 */
  /* cmp edi, edx -> ja 0x1d7525 */
  /* cmp edi, edx -> jne 0x1d7143 */
  /* test (char)ecx, (char)ecx -> je 0x1d7152 */
  /* relift: test byte ptr [ebx + 5], 2 -> je 0x1d7175 */
  /* cmp ecx, esi -> jbe 0x1d71a5 */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d71a5 */
  /* cmp ecx, edx -> je 0x1d7683 */
  /* test (char)eax, 8 -> je 0x1d71ff */
  /* test eax, eax -> jl 0x1d7683 */
  /* test (char)eax, 0x10 -> je 0x1d72c3 */
  /* cmp (int16_t)edi, 0x80 -> jae 0x1d7291 */
  /* relift: cmp dword ptr [eax], eax -> jne 0x1d72b5 */
  /* cmp edx, eax -> je 0x1d72b2 */
  /* relift: cmp (int16_t)edi, word ptr [ecx] -> jbe 0x1d72b2 */
  /* test (char)eax, 1 -> je 0x1d737d */
  /* cmp (int16_t)edi, 0x80 -> jae 0x1d7336 */
  /* relift: cmp dword ptr [eax], eax -> jne 0x1d7369 */
  /* cmp edx, eax -> je 0x1d7363 */
  /* relift: cmp (int16_t)edi, word ptr [ecx] -> jbe 0x1d7363 */
  /* cmp eax, ecx -> jne 0x1d73e3 */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d73e3 */
  /* test (char)ecx, 4 -> je 0x1d7429 */
  /* test (char)ecx, 2 -> je 0x1d7410 */
  /* cmp eax, 4 -> jbe 0x1d7410 */
  /* cmp edi, 0xff00 -> ja 0x1d7516 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d7458 */
  /* cmp (int16_t)edi, 0x80 -> jae 0x1d74bf */
  /* relift: cmp dword ptr [eax], eax -> jne 0x1d74ef */
  /* cmp edx, eax -> je 0x1d74e9 */
  /* relift: cmp (int16_t)edi, word ptr [ecx] -> jbe 0x1d74e9 */
  FUN_001d4cd9();
  /* test (char)ecx, (char)ecx -> jne 0x1d7544 */
  FUN_001d4ec6();
  /* test (char)eax, (char)eax -> jne 0x1d7683 */
  /* relift: test byte ptr [ebp + 0xc], 0x10 -> je 0x1d7553 */
  /* test (char)eax, 2 -> je 0x1d75c1 */
  FUN_001d4dd3();
  /* test (int16_t)eax, (int16_t)eax -> je 0x1d759a */
  /* test (char)eax, (char)eax -> je 0x1d75d1 */
  FUN_001d5c66();
  /* test eax, eax -> je 0x1d7680 */
  /* relift: test byte ptr [eax + 5], 2 -> je 0x1d7628 */
  FUN_001d4dd3();
  /* relift: test byte ptr [ebx + 5], 2 -> je 0x1d7622 */
  FUN_001d4dd3();
  /* cmp eax, esi -> jb 0x1d7631 */
  memmove((void *)0, (void *)(uintptr_t)0, eax);
  /* relift: cmp dword ptr [ebp + 0x14], esi -> jbe 0x1d766c */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d766c */
  FUN_001d6ca8();
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d76e4 */
  /* relift: test byte ptr [ebp + 0xc], 4 -> je 0x1d76e4 */
  FUN_001d76fc();
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d7711 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001d8bd0 */
void NtDuplicateObject(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8bd6 */
void RtlLeaveCriticalSection(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8bdc */
void RtlEnterCriticalSection(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8be2 */
void ObfDereferenceObject(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8be8 */
void KeSetBasePriorityThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8bee */
void ObReferenceObjectByHandle(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8bf4 */
void KeQueryBasePriorityThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8bfa */
void KeSetDisableBoostThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c00 */
void NtSuspendThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c06 */
void NtResumeThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c0c */
void RtlRaiseException(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c12 */
void NtQueueApcThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c18 */
void NtYieldExecution(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c1e */
void PsTerminateSystemThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c24 */
void PsCreateSystemThreadEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c2a */
void NtCreateEvent(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c30 */
void ObOpenObjectByName(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c3c */
void NtSetEvent(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c42 */
void NtClearEvent(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c48 */
void NtPulseEvent(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c4e */
void NtCreateSemaphore(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c54 */
void NtReleaseSemaphore(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c5a */
void NtCreateMutant(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c60 */
void NtReleaseMutant(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c66 */
void NtWaitForSingleObjectEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c6c */
void NtSignalAndWaitForSingleObjectEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c72 */
void NtWaitForMultipleObjectsEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c78 */
void KeDelayExecutionThread(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c7e */
void NtCreateTimer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c84 */
void NtSetTimerEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c8a */
void NtCancelTimer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c90 */
void RtlFreeAnsiString(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c96 */
void RtlUnicodeStringToAnsiString(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8c9c */
void RtlInitUnicodeString(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ca2 */
void RtlTimeToTimeFields(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cae */
void RtlTimeFieldsToTime(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cb4 */
void NtAllocateVirtualMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cba */
void NtFreeVirtualMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cc0 */
void NtProtectVirtualMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cc6 */
void NtQueryVirtualMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ccc */
void MmQueryStatistics(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cd2 */
void NtSetInformationFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cde */
void NtQueryFullAttributesFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ce4 */
void FscSetCacheSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cea */
void FscGetCacheSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cf0 */
void NtQueryDirectoryFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cf6 */
void NtWaitForSingleObject(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8cfc */
void NtReadFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d08 */
void NtQueryInformationFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d14 */
void NtFlushBuffersFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d1a */
void NtUserIoApcDispatcher(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d2c */
void NtReadFileScatter(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d38 */
void NtCreateFile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d3e */
void MmFreeSystemMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d44 */
void MmAllocateSystemMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d4a */
void KeWaitForSingleObject(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d50 */
void KfLowerIrql(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d56 */
void KeRaiseIrqlToDpcLevel(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d5c */
void IoCreateDevice(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d62 */
void ExAllocatePool(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d68 */
void KeSetEvent(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d6e */
void KeInitializeTimerEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d74 */
void KeInitializeDpc(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d7a */
void IoInvalidDeviceRequest(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d80 */
void RtlNtStatusToDosError(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d86 */
void NtCreateIoCompletion(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d8c */
void NtSetIoCompletion(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d92 */
void NtRemoveIoCompletion(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d98 */
void KeSetTimer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8d9e */
void KeCancelTimer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8da4 */
void MmPersistContiguousMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8daa */
void MmAllocateContiguousMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8db6 */
void HalReturnToFirmware(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8dbc */
void NtQuerySymbolicLinkObject(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8dc2 */
void NtOpenSymbolicLinkObject(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8dc8 */
void KeQueryPerformanceCounter(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8dce */
void KeQueryPerformanceFrequency(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8dd4 */
void MmAllocateContiguousMemoryEx(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8de0 */
void MmSetAddressProtect(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8dec */
void IoCreateSymbolicLink(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8df2 */
void IoDeleteSymbolicLink(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e10 */
void RtlFillMemoryUlong(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e16 */
void RtlCompareMemoryUlong(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e1c */
void RtlCompareMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e22 */
void RtlInitializeCriticalSection(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e28 */
void IoStartPacket(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e2e */
void IofCompleteRequest(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e34 */
void IoStartNextPacket(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e3a */
void ExFreePool(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e40 */
void IoMarkIrpMustComplete(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e46 */
void HalIsResetOrShutdownPending(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e4c */
void KeQueryInterruptTime(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e52 */
void HalInitiateShutdown(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e58 */
void HalGetInterruptVector(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e5e */
void KfRaiseIrql(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e64 */
void HalRegisterShutdownNotification(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e6a */
void KeConnectInterrupt(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e70 */
void KeInitializeInterrupt(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e76 */
void KeStallExecutionProcessor(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e7c */
void RtlEqualString(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e82 */
void XeLoadSection(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e88 */
void XeUnloadSection(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e8e */
void MmGetPhysicalAddress(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e94 */
void MmLockUnlockBufferPages(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8e9a */
void KeInsertQueueDpc(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ea0 */
void MmLockUnlockPhysicalPage(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ea6 */
void AvGetSavedDataAddress(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8eac */
void AvSendTVEncoderOption(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8eb2 */
void AvSetDisplayMode(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8eb8 */
void AvSetSavedDataAddress(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ec4 */
void KeDisconnectInterrupt(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8eca */
void MmClaimGpuInstanceMemory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ed0 */
void ExQueryPoolBlockSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ed6 */
void ExAllocatePoolWithTag(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8edc */
void KeRemoveQueueDpc(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ee2 */
void KeSynchronizeExecution(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ee8 */
void KeSaveFloatingPointState(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8eee */
void KeRestoreFloatingPointState(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8ef4 */
void PhyGetLinkState(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8efa */
void PhyInitialize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8f00 */
void KeWaitForMultipleObjects(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001d8f12 */
void KeSetTimerEx(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_001d8b2e(0, 0); */
  /* relift: FUN_001d8b49(0, 0); */
  /* test eax, eax -> jge 0x1d8ffc */
  /* mem[0x003314a0] = eax */
  /* mem[0x003314a4] = 0x1dded4 */
  /* mem[0x003314a8] = 0x1ddf39 */
  /* mem[0x003314ac] = 0x1dde7c */
  /* mem[0x003314b0] = 0x1ddf1f */
  /* mem[0x003314b4] = eax */
  /* mem[0x004fc000] = ecx */
  FUN_001d9011();
  FUN_001de27a();
  /* test eax, eax -> je 0x1d90c7 */
  /* test edx, 0x7fffffff -> jne 0x1d908b */
  /* test eax, eax -> je 0x1d90ef */
  FUN_001de452();
  __flsbuf();
  FUN_001de452();
  FUN_001de452();
  __flsbuf();
  /* test esi, esi -> je 0x1d91ee */
  /* cmp edi, ecx -> jbe 0x1d925a */
  /* test eax, eax -> jle 0x1d921f */
  /* cmp esi, edi -> jbe 0x1d9210 */
  /* test ebp, ebp -> je 0x1d9252 */
  /* cmp edi, ecx -> ja 0x1d9202 */
  /* cmp eax, 2 -> jb 0x1d94dc */
  /* cmp eax, 8 -> ja 0x1d92ef */
  _shortsort();
  /* test eax, eax -> jle 0x1d932a */
  /* test eax, eax -> jle 0x1d935c */
  /* test eax, eax -> jle 0x1d938a */
  /* cmp edi, ebx -> jbe 0x1d93b0 */
  /* cmp ebx, edi -> jae 0x1d93b0 */
  /* test eax, eax -> jle 0x1d9394 */
  /* cmp edi, ebx -> ja 0x1d93d0 */
  /* cmp ebx, eax -> ja 0x1d93d0 */
  /* test eax, eax -> jle 0x1d93b0 */
  /* cmp esi, edi -> jbe 0x1d93e6 */
  /* test eax, eax -> jg 0x1d93d0 */
  /* cmp ebx, esi -> ja 0x1d942c */
  /* cmp edi, esi -> jne 0x1d9390 */
  /* cmp edi, esi -> jae 0x1d9450 */
  /* cmp esi, edi -> jbe 0x1d9450 */
  /* test eax, eax -> je 0x1d9432 */
  /* cmp edi, esi -> jb 0x1d946a */
  /* cmp esi, eax -> jbe 0x1d946e */
  /* test eax, eax -> je 0x1d9450 */
  /* cmp edi, ecx -> jl 0x1d94ab */
  /* cmp eax, esi -> jae 0x1d9496 */
  /* cmp ebx, edx -> jae 0x1d92c7 */
  /* cmp ebx, edx -> jae 0x1d94c3 */
  /* cmp eax, esi -> jae 0x1d92c7 */
  FUN_001dee48();
  FUN_001d950d();
  __fload_withFB();
  /* relift: cmp word ptr [esp], 0x27f -> je 0x1d9521 */
  FUN_001dedd5();
  /* cmp eax, 0x3ff00000 -> jae 0x1d9555 */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  FUN_001dedec();
  /* test eax, 0xfffff -> jne 0x1d957a */
  /* relift: cmp dword ptr [esp + 8], 0 -> jne 0x1d957a */
  /* relift: relift: fld xword ptr [0x3314b8] */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  __startOneArgErrorHandling();
  /* test edx, 3 -> je 0x1d95fb */
  /* cmp (char)ecx, (char)ebx -> je 0x1d95c0 */
  /* test (char)ecx, (char)ecx -> je 0x1d9644 */
  /* test edx, 3 -> jne 0x1d95e8 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9685 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d967e */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9677 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9670 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* test dl, dl -> je 0x1d970a */
  /* test (char)edx, (char)edx -> je 0x1d96f7 */
  /* cmp (char)eax, dl -> je 0x1d96ca */
  /* test (char)eax, (char)eax -> je 0x1d96c4 */
  /* cmp (char)eax, dl -> je 0x1d96ca */
  /* test (char)eax, (char)eax -> jne 0x1d96b9 */
  /* cmp (char)eax, (char)edx -> jne 0x1d96bc */
  /* test (char)eax, (char)eax -> je 0x1d9703 */
  /* cmp (char)eax, (char)eax -> jne 0x1d96a8 */
  /* test (char)eax, (char)eax -> je 0x1d9703 */
  /* cmp (char)eax, (char)eax -> je 0x1d96d4 */
  /* relift: cmp byte ptr [edi], (char)eax -> je 0x1d9731 */
  FUN_001df055();
  FUN_001defb3();
  /* test eax, eax -> je 0x1d9756 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d974e */
  FUN_001df055();
  /* mem[0x004fc010] = 1 */
  /* relift: relift: mov byte ptr [0x4fc00c], (char)ebx */
  /* test ecx, ecx -> je 0x1d97b5 */
  /* test eax, eax -> je 0x1d97a0 */
  /* mem[0x00632dcc] = eax */
  /* cmp eax, edi -> jae 0x1d97d4 */
  /* test eax, eax -> je 0x1d97cd */
  /* cmp esi, edi -> jb 0x1d97c5 */
  /* cmp eax, edi -> jae 0x1d97f3 */
  /* test eax, eax -> je 0x1d97ec */
  /* cmp esi, edi -> jb 0x1d97e4 */
  FUN_001defb3();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001d98a3();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001d9901();
  __SEH_epilog();
  __unlock_file();
  /* cmp eax, esi -> jge 0x1d9930 */
  /* mem[0x00632dc4] = eax */
  FUN_001df1bd();
  /* mem[0x00632dc0] = eax */
  /* mem[0x00632dc4] = esi */
  FUN_001df1bd();
  /* mem[0x00632dc0] = eax */
  /* cmp ecx, 0x3312b0 -> jl 0x1d996a */
  /* cmp eax, -1 -> je 0x1d99a7 */
  /* test eax, eax -> jne 0x1d99aa */
  /* cmp edx, 0x3310a0 -> jl 0x1d9987 */
  __flushall();
  /* relift: cmp byte ptr [0x4fc00c], 0 -> je 0x1d99cd */
  /* cmp eax, ecx -> jb 0x1d99f2 */
  /* cmp eax, 0x331290 -> ja 0x1d99f2 */
  FUN_001df055();
  /* cmp eax, 0x14 -> jge 0x1d9a11 */
  FUN_001df055();
  /* cmp eax, ecx -> jb 0x1d9a44 */
  /* cmp eax, 0x331290 -> ja 0x1d9a44 */
  FUN_001defb3();
  /* cmp eax, 0x14 -> jge 0x1d9a63 */
  FUN_001defb3();
  /* cmp (char)ecx, 2 -> jne 0x1d9ac1 */
  /* test (int16_t)eax, 0x108 -> je 0x1d9ac1 */
  /* test edi, edi -> jle 0x1d9ac0 */
  __write();
  /* cmp eax, edi -> jne 0x1d9ab9 */
  __flush();
  /* relift: test byte ptr [esi + 0xd], 0x40 -> je 0x1d9af9 */
  FUN_001df4c4();
  FUN_001dd5c8();
  FUN_001df055();
  /* relift: cmp esi, dword ptr [0x632dc4] -> jge 0x1d9bae */
  /* cmp eax, edi -> je 0x1d9b95 */
  /* relift: test byte ptr [eax + 0xc], 0x83 -> je 0x1d9b95 */
  __lock_file2();
  /* test (char)ecx, 0x83 -> je 0x1d9b8d */
  /* relift: cmp dword ptr [ebp + 8], edx -> jne 0x1d9b74 */
  __fflush_lk();
  /* cmp eax, -1 -> je 0x1d9b8d */
  /* relift: cmp dword ptr [ebp + 8], edi -> jne 0x1d9b8d */
  /* test (char)ecx, 2 -> je 0x1d9b8d */
  __fflush_lk();
  /* cmp eax, -1 -> jne 0x1d9b8d */
  FUN_001d9b9d();
  __unlock_file2();
  FUN_001d9bc9();
  __SEH_epilog();
  FUN_001defb3();
  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> jne 0x1d9bee */
  _flsall();
  __lock_file();
  __fflush_lk();
  FUN_001d9c18();
  __SEH_epilog();
  __unlock_file();
  _flsall();
  __ctrlfp();
  __sptype();
  /* cmp eax, 2 -> jle 0x1d9c86 */
  /* cmp eax, 3 -> jne 0x1d9c94 */
  __handle_qnan1();
  __ctrlfp();
  FUN_001dfd23();
  __ctrlfp();
  /* test (char)ebx, 0x20 -> jne 0x1d9cc5 */
  FUN_001dfbd2();
  FUN_001dff91();
  FUN_001dff91();
  /* relift: FUN_001e64ec(0, 0, 0, 0); */
  __aulldiv();
  /* test ecx, ecx -> je 0x1d9d5e */
  /* relift: test byte ptr [esi + 0xc], 0x83 -> je 0x1d9da3 */
  __flush();
  __freebuf();
  __close(*(int *)((char *)esi + 0x10));
  /* test eax, eax -> jge 0x1d9d91 */
  /* test eax, eax -> je 0x1d9da3 */
  FUN_001dde24();
  FUN_001dd5c8();
  /* relift: test byte ptr [esi + 0xc], 0x40 -> je 0x1d9dd2 */
  __SEH_epilog();
  __lock_file();
  __fclose_lk();
  FUN_001d9df5();
  __unlock_file();
  FUN_001dd5c8();
  __getstream();
  /* test eax, eax -> jne 0x1d9e24 */
  FUN_001db777();
  __openfile();
  FUN_001d9e4f();
  __SEH_epilog();
  __unlock_file();
  __fsopen();
  FUN_001d9e94();
  __fload_withFB();
  /* relift: cmp word ptr [esp], 0x27f -> je 0x1d9ea8 */
  FUN_001dedd5();
  /* cmp ecx, 0x7ff00000 -> je 0x1d9f5b */
  __fload_withFB();
  /* test eax, 0x7ff00000 -> je 0x1d9fca */
  FUN_001dedc0();
  /* cmp (char)ecx, 1 -> jne 0x1d9eef */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  FUN_001ded6c();
  __fload_withFB();
  /* relift: test byte ptr [esp + 0x16], 8 -> jne 0x1d9f3e */
  /* relift: test byte ptr [esp + 0xe], 8 -> jne 0x1d9f3e */
  __fload_withFB();
  /* cmp eax, 0x7ff00000 -> jne 0x1d9f8f */
  /* test ecx, ecx -> jne 0x1d9f4e */
  FUN_001e07c0();
  /* test eax, eax -> je 0x1dee5e */
  FUN_001da059();
  /* relift: test dword ptr [esp + 0x17], 0x80 -> je 0x1da01a */
  /* relift: relift: fld xword ptr [0x331758] */
  /* test (char)ecx, (char)ecx -> je 0x1da010 */
  /* test (char)ecx, (char)ecx -> je 0x1dee5e */
  FUN_001da059();
  /* test (char)ecx, (char)ecx -> jne 0x1d9ee1 */
  /* relift: relift: fld xword ptr [0x3314b8] */
  FUN_001dd5c8();
  __lock_file();
  FUN_001e0984();
  FUN_001da0c1();
  __SEH_epilog();
  __unlock_file();
  FUN_001dee48();
  FUN_001da0e9();
  __fload_withFB();
  /* relift: cmp word ptr [esp], 0x27f -> je 0x1da0fd */
  FUN_001dedd5();
  /* cmp eax, 0x3ff00000 -> jae 0x1da12f */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  /* relift: relift: fld xword ptr [0x3314c2] */
  FUN_001dedec();
  /* test eax, 0xfffff -> jne 0x1da156 */
  /* relift: cmp dword ptr [esp + 8], 0 -> jne 0x1da156 */
  /* relift: relift: fld xword ptr [0x3314b8] */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  __startOneArgErrorHandling();
  FUN_001e153d();
  FUN_001e153d();
  FUN_001de452();
  __flsbuf();
  FUN_001de452();
  /* cmp edi, esi -> jbe 0x1da2b0 */
  /* cmp edi, eax -> jb 0x1da428 */
  /* test edi, 3 -> jne 0x1da2cc */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* mem[0xa3bc001d] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001e64e7 */
void DbgBreakPoint(void)
{
  int ebx = 0;
  int ecx = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1e65e7 */
  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1e65ae */
  crt_tolower(0);
  crt_tolower(0);
  /* test ebx, ebx -> je 0x1e65de */
  /* cmp ebx, ecx -> je 0x1e65b7 */
  FUN_001dd5c8();
  /* relift: cmp ecx, dword ptr [0x632ca8] -> jae 0x1e67f1 */

  (void)ebx;
  (void)ecx;
  (void)ebp;
}

/* 0x001e657e */
void KeBugCheck(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e658a */
void RtlAnsiStringToUnicodeString(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1e65e7 */
  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1e65ae */
  crt_tolower(0);
  crt_tolower(0);
  /* test ebx, ebx -> je 0x1e65de */
  /* cmp ebx, ecx -> je 0x1e65b7 */
  FUN_001dd5c8();
  /* relift: cmp ecx, dword ptr [0x632ca8] -> jae 0x1e67f1 */
  /* relift: test byte ptr [eax + edi + 4], 1 -> je 0x1e67f1 */
  FUN_001e334f();
  /* relift: test byte ptr [eax + edi + 4], 1 -> jne 0x1e6662 */
  FUN_001db777();
  FUN_001e67e7();
  FUN_001d17d2();
  /* test eax, eax -> jne 0x1e669d */
  xapi_GetLastError();
  __dosmaperr();
  /* relift: test byte ptr [ebp - 0x50], 1 -> je 0x1e66ad */
  FUN_001d0adb();
  /* test eax, eax -> je 0x1e664d */
  FUN_001d0589();
  /* test eax, eax -> je 0x1e664d */
  ___loctotime_t();
  /* relift: cmp dword ptr [ebp - 0x44], edi -> jne 0x1e6712 */
  /* relift: cmp dword ptr [ebp - 0x40], edi -> je 0x1e6764 */
  FUN_001d0adb();
  /* test eax, eax -> je 0x1e664d */
  FUN_001d0589();
  /* test eax, eax -> je 0x1e664d */
  ___loctotime_t();
  /* relift: cmp dword ptr [ebp - 0x4c], edi -> jne 0x1e6776 */
  /* relift: cmp dword ptr [ebp - 0x48], edi -> jne 0x1e6776 */
  FUN_001d0adb();
  /* test eax, eax -> je 0x1e664d */
  FUN_001d0589();
  /* test eax, eax -> je 0x1e664d */
  ___loctotime_t();
  __unlock_fhandle();
  FUN_001db777();
  __SEH_epilog();
  /* cmp (int16_t)edx, 0x41 -> jb 0x1e6828 */
  /* cmp (int16_t)edx, 0x5a -> ja 0x1e6828 */
  /* relift: cmp word ptr [ecx], 0 -> jne 0x1e6811 */
  /* cmp (int16_t)edx, 0x61 -> jb 0x1e6854 */
  /* cmp (int16_t)edx, 0x7a -> ja 0x1e6854 */
  /* relift: cmp word ptr [ecx], 0 -> jne 0x1e683d */
  /* cmp (char)eax, (char)ebx -> jb 0x1e6894 */
  /* cmp (char)eax, (char)ebx -> ja 0x1e6894 */
  /* cmp (char)eax, (char)ebx -> jb 0x1e689e */
  /* cmp (char)eax, (char)ebx -> ja 0x1e689e */
  /* cmp (char)eax, (char)eax -> jne 0x1e68ab */
  /* cmp (char)eax, (char)eax -> je 0x1e68b4 */
  /* cmp esi, 0x46 -> jl 0x1e69c3 */
  /* cmp esi, 0x8a -> jg 0x1e69c3 */
  /* test edx, edx -> jne 0x1e6907 */
  /* test edx, edx -> jne 0x1e6919 */
  /* test edx, edx -> jne 0x1e691f */
  /* cmp ecx, 2 -> jle 0x1e691f */
  FUN_001e1953();
  /* relift: cmp dword ptr [ebp + 0x20], -1 -> jne 0x1e69bd */
  /* relift: cmp dword ptr [0x3317d4], 0 -> je 0x1e69bd */
  FUN_001e1997();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001e69f0 */
void D3DDevice_GetDeviceCaps(void *caps)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* D3DDevice_GetCreationParameters (0x1e6a10) — XBE naked draft (batch 349). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetCreationParameters(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%edx\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "orl $0x40, %%ecx\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      "movb 0xc(%%edx), %%bl\n\t"
      "popl %%esi\n\t"
      "testb $0x10, %%bl\n\t"
      "popl %%ebx\n\t"
      "je .LD3DDevice_GetCreationParameters_1\n\t"
      "orl $0x10, %%ecx\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      ".LD3DDevice_GetCreationParameters_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetCreationParameters: clang naked draft required"
#endif


/* D3DDevice_SetGammaRamp (0x1e6a50) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void b1e6a50_c1eff04_tgt(void) { return; }
static void (*const b1e6a50_c1eff04)(void) = b1e6a50_c1eff04_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetGammaRamp(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "leal 0x2308(%%eax), %%edx\n\t"
      "movl 0x2b60(%%eax), %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "leal 0x214(%%ecx,%%edx,1), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl $0xc0, %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "rep movsl\n\t"
      "testb $2, 0x10(%%esp)\n\t"
      "movl %%eax, 0x81c(%%edx)\n\t"
      "je .LD3DDevice_SetGammaRamp_1\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, %%ecx\n\t"
      "call *%[c1eff04]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LD3DDevice_SetGammaRamp_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, 0x814(%%edx,%%eax,4)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1eff04] "m"(b1e6a50_c1eff04)
      : "memory");
}
#else
#error "D3DDevice_SetGammaRamp: clang naked draft required"
#endif


/* D3DDevice_GetGammaRamp (0x1e6ab0) — XBE naked draft (batch 374). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetGammaRamp(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x2b24(%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "leal 0x251c(%%ecx,%%eax,1), %%esi\n\t"
      "movl $0xc0, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetGammaRamp: clang naked draft required"
#endif


/* D3DDevice_CreateVolumeTexture (0x1e6b10) — XBE naked draft (batch 378). */
#if defined(__clang__)
static void (*const b1e6b10_c1eddd0)(void) = (void *)D3D_CreateTexture;

__attribute__((naked, noinline))
void D3DDevice_CreateVolumeTexture(void)
{
  __asm__ volatile(
      "movl 0x20(%%esp), %%eax\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1c(%%esp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eddd0]\n\t"
      "ret\n\t"
      :
      : [c1eddd0] "m"(b1e6b10_c1eddd0)
      : "memory");
}
#else
#error "D3DDevice_CreateVolumeTexture: clang naked draft required"
#endif


/* D3DDevice_CreateCubeTexture (0x1e6b40) — XBE naked draft (batch 380). */
#if defined(__clang__)
static void (*const b1e6b40_c1eddd0)(void) = (void *)D3D_CreateTexture;

__attribute__((naked, noinline))
void D3DDevice_CreateCubeTexture(void)
{
  __asm__ volatile(
      "movl 0x18(%%esp), %%eax\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eddd0]\n\t"
      "ret\n\t"
      :
      : [c1eddd0] "m"(b1e6b40_c1eddd0)
      : "memory");
}
#else
#error "D3DDevice_CreateCubeTexture: clang naked draft required"
#endif


/* D3DDevice_CreateImageSurface (0x1e6ba0) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void b1e6ba0_c1ef330_tgt(void) { return; }
static void (*const b1e6ba0_c1ef330)(void) = b1e6ba0_c1ef330_tgt;

__attribute__((naked, noinline))
void D3DDevice_CreateImageSurface(void)
{
  __asm__ volatile(
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ef330]\n\t"
      "ret\n\t"
      :
      : [c1ef330] "m"(b1e6ba0_c1ef330)
      : "memory");
}
#else
#error "D3DDevice_CreateImageSurface: clang naked draft required"
#endif


/* D3DDevice_SetRenderState (0x1e6bc0) — XBE naked draft (batch 395). */
#if defined(__clang__)
static void (*const b1e6bc0_c1e93a0)(void) = (void *)D3DDevice_SetRenderStateNotInline;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState(void)
{
  __asm__ volatile(
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e93a0]\n\t"
      "ret\n\t"
      :
      : [c1e93a0] "m"(b1e6bc0_c1e93a0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState: clang naked draft required"
#endif


/* D3DDevice_MultiplyTransform (0x1e6d10) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void b1e6d10_c1f2340_tgt(void) { return; }
static void (*const b1e6d10_c1f2340)(void) = b1e6d10_c1f2340_tgt;
static void __stdcall (*const b1e6d10_c1e6bd0)(uint32_t type, void *matrix) = (void *)D3DDevice_SetTransform;

__attribute__((naked, noinline))
void D3DDevice_MultiplyTransform(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "andl $0xfffffff0, %%esp\n\t"
      "subl $0x88, %%esp\n\t"
      "movl 0x1fe6a0, %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x10, %%ecx\n\t"
      "leal 0x10(%%esp), %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal 0x22(%%esi), %%eax\n\t"
      "shll $6, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x14(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x58(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1f2340]\n\t"
      "leal 0x50(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e6bd0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1f2340] "m"(b1e6d10_c1f2340), [c1e6bd0] "m"(b1e6d10_c1e6bd0)
      : "memory");
}
#else
#error "D3DDevice_MultiplyTransform: clang naked draft required"
#endif


/* D3DDevice_GetViewport (0x1e6d60) — XBE naked draft (batch 381). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetViewport(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "leal 0xb00(%%eax), %%esi\n\t"
      "movl $6, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetViewport: clang naked draft required"
#endif


/* D3DDevice_SetMaterial (0x1e6d80) — XBE naked draft (batch 375). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetMaterial(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0xb18(%%eax), %%edi\n\t"
      "movl $0x11, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "orl $0x20, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetMaterial: clang naked draft required"
#endif


/* D3DDevice_GetMaterial (0x1e6db0) — XBE naked draft (batch 381). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetMaterial(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "leal 0xb18(%%eax), %%esi\n\t"
      "movl $0x11, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetMaterial: clang naked draft required"
#endif


/* D3DDevice_SetBackMaterial (0x1e6dd0) — XBE naked draft (batch 375). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetBackMaterial(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0xb5c(%%eax), %%edi\n\t"
      "movl $0x11, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "orl $0x20, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetBackMaterial: clang naked draft required"
#endif


/* D3DDevice_GetBackMaterial (0x1e6e00) — XBE naked draft (batch 381). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetBackMaterial(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "leal 0xb5c(%%eax), %%esi\n\t"
      "movl $0x11, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetBackMaterial: clang naked draft required"
#endif


/* D3DDevice_GetLight (0x1e6e30) — XBE naked draft (batch 372). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetLight(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%ecx\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x480(%%ecx), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "leal (%%eax,%%eax,8), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%eax, %%esi\n\t"
      "movl $0x1a, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetLight: clang naked draft required"
#endif


/* D3DDevice_GetLightEnable (0x1e6e60) — XBE naked draft (batch 324). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetLightEnable(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x480(%%eax), %%edx\n\t"
      "movl 0x488(%%eax), %%eax\n\t"
      "leal (%%ecx,%%ecx,8), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_GetLightEnable_2\n\t"
      ".LD3DDevice_GetLightEnable_1:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LD3DDevice_GetLightEnable_3\n\t"
      "movl 0x8c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_GetLightEnable_1\n\t"
      ".LD3DDevice_GetLightEnable_2:\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0, (%%ecx)\n\t"
      "ret\n\t"
      ".LD3DDevice_GetLightEnable_3:\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl $1, (%%eax)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetLightEnable: clang naked draft required"
#endif


/* D3DDevice_SwitchTexture (0x1e6ed0) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void (*const b1e6ed0_c1efb70)(void) = (void *)CDevice_MakeSpace;

__attribute__((naked, noinline))
void D3DDevice_SwitchTexture(void)
{
  __asm__ volatile(
      ".LD3DDevice_SwitchTexture_1:\n\t"
      "movl 0x1fbb10, %%eax\n\t"
      "addl $0xc, %%eax\n\t"
      "cmpl 0x1fbb14, %%eax\n\t"
      "jae .LD3DDevice_SwitchTexture_2\n\t"
      "movl %%eax, 0x1fbb10\n\t"
      "movl %%ecx, -0xc(%%eax)\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl %%edx, -0x8(%%eax)\n\t"
      "movl %%ecx, -0x4(%%eax)\n\t"
      "ret\n\t"
      ".LD3DDevice_SwitchTexture_2:\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "call *%[c1efb70]\n\t"
      "popl %%ecx\n\t"
      "popl %%edx\n\t"
      "jmp .LD3DDevice_SwitchTexture_1\n\t"
      :
      : [c1efb70] "m"(b1e6ed0_c1efb70)
      : "memory");
}
#else
#error "D3DDevice_SwitchTexture: clang naked draft required"
#endif


/* D3DDevice_AddRef (0x1e6f30) — XBE naked draft (batch 368). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_AddRef(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x408(%%eax), %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x408(%%eax)\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_AddRef: clang naked draft required"
#endif


/* D3DDevice_Release (0x1e6f50) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void b1e6f50_c1f3a90_tgt(void) { return; }
static void (*const b1e6f50_c1f3a90)(void) = b1e6f50_c1f3a90_tgt;

__attribute__((naked, noinline))
void D3DDevice_Release(void)
{
  __asm__ volatile(
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "movl 0x408(%%edi), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "jne .LD3DDevice_Release_1\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1f3a90]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0xae4, %%ecx\n\t"
      "movl %%eax, 0x1fe6a4\n\t"
      "movl %%eax, 0x1fe6a0\n\t"
      "rep stosl\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LD3DDevice_Release_1:\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x408(%%edi)\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [c1f3a90] "m"(b1e6f50_c1f3a90)
      : "memory");
}
#else
#error "D3DDevice_Release: clang naked draft required"
#endif


/* D3DDevice_BlockOnFence (0x1e6fa0) — XBE naked draft (batch 388). */
#if defined(__clang__)
static void __stdcall (*const b1e6fa0_c1efa80)(uint32_t time, int param2) = (void *)D3D_BlockOnTime;

__attribute__((naked, noinline))
void D3DDevice_BlockOnFence(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1efa80]\n\t"
      "ret\n\t"
      :
      : [c1efa80] "m"(b1e6fa0_c1efa80)
      : "memory");
}
#else
#error "D3DDevice_BlockOnFence: clang naked draft required"
#endif


/* 0x001e6fb0 */
void D3DDevice_KickPushBuffer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* D3DDevice_GetVisibilityTestResult (0x1e7030) — XBE naked draft (batch 329). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVisibilityTestResult(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x1fe6a0, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $8, %%ecx\n\t"
      "andl $0xff, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x48c(%%edx,%%ecx,4), %%esi\n\t"
      "shll $4, %%eax\n\t"
      "movl 0xc(%%eax,%%esi,1), %%ecx\n\t"
      "addl %%esi, %%eax\n\t"
      "cmpl $-1, %%ecx\n\t"
      "popl %%esi\n\t"
      "jne .LD3DDevice_GetVisibilityTestResult_1\n\t"
      "movl $0x88760828, %%eax\n\t"
      "ret\n\t"
      ".LD3DDevice_GetVisibilityTestResult_1:\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_GetVisibilityTestResult_2\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      ".LD3DDevice_GetVisibilityTestResult_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVisibilityTestResult: clang naked draft required"
#endif


/* D3DDevice_SetVerticalBlankCallback (0x1e70e0) — XBE naked draft (batch 393). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetVerticalBlankCallback(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "movl %%eax, 0x24ec(%%ecx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetVerticalBlankCallback: clang naked draft required"
#endif


/* D3DDevice_GetProjectionViewportMatrix (0x1e7140) — XBE naked draft (batch 385). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetProjectionViewportMatrix(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "addl $0x5a0, %%esi\n\t"
      "movl $0x10, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetProjectionViewportMatrix: clang naked draft required"
#endif


/* D3DDevice_GetModelView (0x1e7180) — XBE naked draft (batch 366). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetModelView(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_GetModelView_1\n\t"
      "pushl %%esi\n\t"
      "leal 0x5e0(%%eax), %%esi\n\t"
      "movl $0x10, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%esi\n\t"
      ".LD3DDevice_GetModelView_1:\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetModelView: clang naked draft required"
#endif


/* D3DDevice_GetTile (0x1e7200) — XBE naked draft (batch 377). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetTile(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal 0x21bc(%%ecx,%%eax,8), %%esi\n\t"
      "movl $6, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetTile: clang naked draft required"
#endif


/* D3DDevice_GetScissors (0x1e7230) — XBE naked draft (batch 338). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetScissors(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x1fe6a0, %%eax\n\t"
      "je .LD3DDevice_GetScissors_1\n\t"
      "movl 0x22fc(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LD3DDevice_GetScissors_1:\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_GetScissors_2\n\t"
      "movl 0x2300(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LD3DDevice_GetScissors_2:\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_GetScissors_3\n\t"
      "movl 0x22fc(%%eax), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal 0x227c(%%eax), %%esi\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $2, %%ecx\n\t"
      "rep movsl\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "popl %%esi\n\t"
      ".LD3DDevice_GetScissors_3:\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetScissors: clang naked draft required"
#endif


/* D3DDevice_SetFlickerFilter (0x1e72a0) — XBE naked draft (batch 349). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetFlickerFilter(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "movl 0x2308(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0xb\n\t"
      "pushl %%edx\n\t"
      "call *0x2532b0\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetFlickerFilter: clang naked draft required"
#endif


/* D3DDevice_SetSoftDisplayFilter (0x1e72c0) — XBE naked draft (batch 349). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetSoftDisplayFilter(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "movl 0x2308(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0xe\n\t"
      "pushl %%edx\n\t"
      "call *0x2532b0\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetSoftDisplayFilter: clang naked draft required"
#endif


/* D3DDevice_InsertFence (0x1e73a0) — XBE naked draft (batch 393). */
#if defined(__clang__)
static void (*const b1e73a0_c1ef9e0)(void) = (void *)D3D_SetFence;

__attribute__((naked, noinline))
void D3DDevice_InsertFence(void)
{
  __asm__ volatile(
      "pushl $0\n\t"
      "call *%[c1ef9e0]\n\t"
      "ret\n\t"
      :
      : [c1ef9e0] "m"(b1e73a0_c1ef9e0)
      : "memory");
}
#else
#error "D3DDevice_InsertFence: clang naked draft required"
#endif


/* 0x001e73b0 */
void D3DResource_AddRef(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* D3DBaseTexture_GetLevelCount (0x1e76b0) — XBE naked draft (batch 393). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DBaseTexture_GetLevelCount(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movzbl 0xe(%%eax), %%eax\n\t"
      "andl $0xf, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DBaseTexture_GetLevelCount: clang naked draft required"
#endif


/* D3DDevice_GetDisplayMode (0x1e79d0) — XBE naked draft (batch 346). */
#if defined(__clang__)
static void b1e79d0_c1f4840_tgt(void) { return; }
static void (*const b1e79d0_c1f4840)(void) = b1e79d0_c1f4840_tgt;

__attribute__((naked, noinline))
void D3DDevice_GetDisplayMode(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x21b4(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x21b8(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl 0x2510(%%esi), %%eax\n\t"
      "andl $0x400000, %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xa, %%eax\n\t"
      "addl $0x32, %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl 0x2510(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1f4840]\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movzbl 0x2175(%%esi), %%eax\n\t"
      "movl %%eax, 0x10(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1f4840] "m"(b1e79d0_c1f4840)
      : "memory");
}
#else
#error "D3DDevice_GetDisplayMode: clang naked draft required"
#endif


/* D3DDevice_Reset (0x1e7a30) — XBE naked draft (batch 357). */
#if defined(__clang__)
static void (*const b1e7a30_c1efd60)(void) = (void *)D3D_KickOffAndWaitForIdle;
static void (*const b1e7a30_c1f4aa0)(void) = (void *)CMiniport_IsFlipPending;
static void (*const b1e7a30_c1f30c0)(void) = (void *)CDevice_FreeFrameBuffers;
static void (*const b1e7a30_c1f31c0)(void) = (void *)CDevice_InitializeFrameBuffers;
static void b1e7a30_c1e77d0_tgt(void) { return; }
static void (*const b1e7a30_c1e77d0)(void) = b1e7a30_c1e77d0_tgt;
static void b1e7a30_c1f4918_tgt(void) { return; }
static void (*const b1e7a30_c1f4918)(void) = b1e7a30_c1f4918_tgt;
static void __stdcall (*const b1e7a30_c1e7af0)(void *render_target, void *depth_stencil) = (void *)D3DDevice_SetRenderTarget;
static void __stdcall (*const b1e7a30_c1ea650)(uint32_t count, void *rects, uint32_t flags, uint32_t color, float z, uint32_t stencil) = (void *)D3DDevice_Clear;

__attribute__((naked, noinline))
void D3DDevice_Reset(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "call *%[c1efd60]\n\t"
      "leal 0x2308(%%edi), %%ebp\n\t"
      ".LD3DDevice_Reset_1:\n\t"
      "movl %%ebp, %%ecx\n\t"
      "call *%[c1f4aa0]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_Reset_1\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1f30c0]\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1f31c0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jge .LD3DDevice_Reset_2\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1f30c0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LD3DDevice_Reset_2:\n\t"
      "leal 0x2168(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e77d0]\n\t"
      "movl 0x30(%%esi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ebp, %%ecx\n\t"
      "call *%[c1f4918]\n\t"
      "movl 0x2198(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_Reset_3\n\t"
      "leal 0x219c(%%edi), %%eax\n\t"
      "jmp .LD3DDevice_Reset_4\n\t"
      ".LD3DDevice_Reset_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_Reset_4:\n\t"
      "pushl %%eax\n\t"
      "addl $0x2150, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e7af0]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "pushl $3\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c1ea650]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efd60] "m"(b1e7a30_c1efd60), [c1f4aa0] "m"(b1e7a30_c1f4aa0), [c1f30c0] "m"(b1e7a30_c1f30c0), [c1f31c0] "m"(b1e7a30_c1f31c0), [c1e77d0] "m"(b1e7a30_c1e77d0), [c1f4918] "m"(b1e7a30_c1f4918), [c1e7af0] "m"(b1e7a30_c1e7af0), [c1ea650] "m"(b1e7a30_c1ea650)
      : "memory");
}
#else
#error "D3DDevice_Reset: clang naked draft required"
#endif


/* D3DDevice_CopyRects (0x1e7de0) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void b1e7de0_c1e77d0_tgt(void) { return; }
static void (*const b1e7de0_c1e77d0)(void) = b1e7de0_c1e77d0_tgt;
static void b1e7de0_c1f3d90_tgt(void) { return; }
static void (*const b1e7de0_c1f3d90)(void) = b1e7de0_c1f3d90_tgt;
static void b1e7de0_c1e7830_tgt(void) { return; }
static void (*const b1e7de0_c1e7830)(void) = b1e7de0_c1e7830_tgt;
static void b1e7de0_c1f55d0_tgt(void) { return; }
static void (*const b1e7de0_c1f55d0)(void) = b1e7de0_c1f55d0_tgt;

__attribute__((naked, noinline))
void D3DDevice_CopyRects(void)
{
  __asm__ volatile(
      "subl $0x1a0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1ac(%%esp), %%ebp\n\t"
      "pushl %%esi\n\t"
      "movzbl 0xd(%%ebp), %%esi\n\t"
      "movb 0x1f9d58(%%esi), %%bl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%bl, %%al\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebp\n\t"
      "shrl $3, %%eax\n\t"
      "andl $7, %%eax\n\t"
      "movl %%eax, 0x24(%%esp)\n\t"
      "call *%[c1e77d0]\n\t"
      "movl 0x1c0(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x1c(%%esp)\n\t"
      "call *%[c1e77d0]\n\t"
      "testb $1, %%bl\n\t"
      "movl %%eax, 0x10(%%esp)\n\t"
      "jne .LD3DDevice_CopyRects_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f3d90]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LD3DDevice_CopyRects_1\n\t"
      "movl $0, 0x14(%%esp)\n\t"
      "movl $1, %%esi\n\t"
      "jmp .LD3DDevice_CopyRects_2\n\t"
      ".LD3DDevice_CopyRects_1:\n\t"
      "movl $1, %%esi\n\t"
      "movl %%esi, 0x14(%%esp)\n\t"
      ".LD3DDevice_CopyRects_2:\n\t"
      "movl 0x1bc(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x1fe6a0, %%edx\n\t"
      "movl %%edx, 0x2c(%%esp)\n\t"
      "jne .LD3DDevice_CopyRects_3\n\t"
      "movl %%esi, 0x1bc(%%esp)\n\t"
      ".LD3DDevice_CopyRects_3:\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CopyRects_6\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1e7830]\n\t"
      "cmpl $0x1fc0, %%eax\n\t"
      "movl %%esi, 0x20(%%esp)\n\t"
      "ja .LD3DDevice_CopyRects_4\n\t"
      "leal 0x3f(%%eax), %%ecx\n\t"
      "andl $0xffffffc0, %%ecx\n\t"
      "movl %%eax, 0x1c(%%esp)\n\t"
      "movl %%esi, 0x24(%%esp)\n\t"
      "jmp .LD3DDevice_CopyRects_5\n\t"
      ".LD3DDevice_CopyRects_4:\n\t"
      "movl $0x1000, %%ecx\n\t"
      "shrl $0xc, %%eax\n\t"
      "movl %%ecx, 0x1c(%%esp)\n\t"
      "movl %%eax, 0x24(%%esp)\n\t"
      ".LD3DDevice_CopyRects_5:\n\t"
      "movl %%ecx, 0x18(%%esp)\n\t"
      "movl %%ecx, 0x10(%%esp)\n\t"
      ".LD3DDevice_CopyRects_6:\n\t"
      "movl 0x1bc(%%esp), %%eax\n\t"
      "nop\n\t"
      ".LD3DDevice_CopyRects_7:\n\t"
      "cmpl $0x10, %%eax\n\t"
      "movl $0x10, %%edi\n\t"
      "ja .LD3DDevice_CopyRects_8\n\t"
      "movl %%eax, %%edi\n\t"
      ".LD3DDevice_CopyRects_8:\n\t"
      "subl %%edi, %%eax\n\t"
      "movl %%eax, 0x1bc(%%esp)\n\t"
      "movl 0x1b8(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CopyRects_9\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x100, %%eax\n\t"
      "movl %%eax, 0x1b8(%%esp)\n\t"
      "jmp .LD3DDevice_CopyRects_16\n\t"
      ".LD3DDevice_CopyRects_9:\n\t"
      "testl %%edi, %%edi\n\t"
      "leal 0xb0(%%esp), %%eax\n\t"
      "movl %%eax, 0x28(%%esp)\n\t"
      "jbe .LD3DDevice_CopyRects_15\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal 0xbc(%%esp), %%edx\n\t"
      "movl %%edi, %%ebx\n\t"
      "jmp .LD3DDevice_CopyRects_10\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LD3DDevice_CopyRects_10:\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $0, -0x8(%%edx)\n\t"
      "jne .LD3DDevice_CopyRects_11\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0xf(%%ebp), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "andl $0xf, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "jmp .LD3DDevice_CopyRects_12\n\t"
      ".LD3DDevice_CopyRects_11:\n\t"
      "movl %%esi, %%eax\n\t"
      "shrl $0xc, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "incl %%eax\n\t"
      ".LD3DDevice_CopyRects_12:\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl $0, -0xc(%%edx)\n\t"
      "jne .LD3DDevice_CopyRects_13\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "shrl $0x14, %%ecx\n\t"
      "andl $0xf, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "jmp .LD3DDevice_CopyRects_14\n\t"
      ".LD3DDevice_CopyRects_13:\n\t"
      "movl %%esi, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "incl %%eax\n\t"
      ".LD3DDevice_CopyRects_14:\n\t"
      "movl %%eax, -0x4(%%edx)\n\t"
      "addl $0x10, %%edx\n\t"
      "decl %%ebx\n\t"
      "jne .LD3DDevice_CopyRects_10\n\t"
      ".LD3DDevice_CopyRects_15:\n\t"
      "movl 0x28(%%esp), %%esi\n\t"
      ".LD3DDevice_CopyRects_16:\n\t"
      "movl 0x1c4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CopyRects_17\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0x80, %%eax\n\t"
      "movl %%eax, 0x1c4(%%esp)\n\t"
      "jmp .LD3DDevice_CopyRects_19\n\t"
      ".LD3DDevice_CopyRects_17:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edi, %%edi\n\t"
      "leal 0x30(%%esp), %%edx\n\t"
      "jbe .LD3DDevice_CopyRects_19\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LD3DDevice_CopyRects_18:\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x30(%%esp,%%eax,8)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x34(%%esp,%%eax,8)\n\t"
      "incl %%eax\n\t"
      "addl $0x10, %%ecx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jb .LD3DDevice_CopyRects_18\n\t"
      ".LD3DDevice_CopyRects_19:\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CopyRects_21\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LD3DDevice_CopyRects_21\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      ".LD3DDevice_CopyRects_20:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x8(%%eax)\n\t"
      "movl %%ebx, -0x4(%%eax)\n\t"
      "movl 0x1c(%%esp), %%ebx\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl 0x24(%%esp), %%ebx\n\t"
      "movl %%ebx, 0x4(%%eax)\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LD3DDevice_CopyRects_20\n\t"
      ".LD3DDevice_CopyRects_21:\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c4(%%esp), %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x4(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl 0x28(%%esp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x34(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1f55d0]\n\t"
      "movl 0x1bc(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_CopyRects_7\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%eax\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "je .LD3DDevice_CopyRects_22\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LD3DDevice_CopyRects_22:\n\t"
      "movl 0x1c(%%esp), %%edx\n\t"
      "movl 0x1c(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x1b0(%%esp), %%ecx\n\t"
      "movl 0x14(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CopyRects_23\n\t"
      "movl 0x1c(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "addl $0x1a0, %%esp\n\t"
      "ret\n\t"
      ".LD3DDevice_CopyRects_23:\n\t"
      "movl 0x1c(%%edx), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "addl $0x1a0, %%esp\n\t"
      "ret\n\t"
      :
      : [c1e77d0] "m"(b1e7de0_c1e77d0), [c1f3d90] "m"(b1e7de0_c1f3d90), [c1e7830] "m"(b1e7de0_c1e7830), [c1f55d0] "m"(b1e7de0_c1f55d0)
      : "memory");
}
#else
#error "D3DDevice_CopyRects: clang naked draft required"
#endif


/* D3DDevice_GetRenderTarget (0x1e8250) — XBE naked draft (batch 346). */
#if defined(__clang__)
static void b1e8250_c1ed8f0_tgt(void) { return; }
static void (*const b1e8250_c1ed8f0)(void) = b1e8250_c1ed8f0_tgt;

__attribute__((naked, noinline))
void D3DDevice_GetRenderTarget(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x40c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "je .LD3DDevice_GetRenderTarget_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed8f0]\n\t"
      ".LD3DDevice_GetRenderTarget_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c1ed8f0] "m"(b1e8250_c1ed8f0)
      : "memory");
}
#else
#error "D3DDevice_GetRenderTarget: clang naked draft required"
#endif


/* 0x001e82a0 */
void D3DDevice_SetViewport(void *viewport)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* D3DDevice_SetLight (0x1e8400) — XBE naked draft (batch 310). */
#if defined(__clang__)
static void *__stdcall (*const b1e8400_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;
static void *__stdcall (*const b1e8400_c1d0c16)(void *ptr) = (void *)LocalFree;
static void b1e8400_c1f2600_tgt(void) { return; }
static void (*const b1e8400_c1f2600)(void) = b1e8400_c1f2600_tgt;
static void b1e8400_c1f2440_tgt(void) { return; }
static void (*const b1e8400_c1f2440)(void) = b1e8400_c1f2440_tgt;
static void b1e8400_c1f3c40_tgt(void) { return; }
static void (*const b1e8400_c1f3c40)(void) = b1e8400_c1f3c40_tgt;
static void b1e8400_c1f25c0_tgt(void) { return; }
static void (*const b1e8400_c1f25c0)(void) = b1e8400_c1f25c0_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetLight(void)
{
  __asm__ volatile(
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%esp), %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x484(%%ebp), %%edi\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "movl %%edi, 0x14(%%esp)\n\t"
      "jb .LD3DDevice_SetLight_4\n\t"
      "leal 0x10(%%ebx), %%eax\n\t"
      "andl $0xfffffff0, %%eax\n\t"
      "movl %%eax, 0x10(%%esp)\n\t"
      "leal (%%eax,%%eax,8), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1d0bb9]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LD3DDevice_SetLight_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".LD3DDevice_SetLight_1:\n\t"
      "movl 0x480(%%ebp), %%edx\n\t"
      "movl 0x488(%%ebp), %%ecx\n\t"
      "leal 0x488(%%ebp), %%eax\n\t"
      "movl %%ebx, %%esi\n\t"
      "subl %%edx, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_SetLight_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LD3DDevice_SetLight_2:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x8c(%%ecx), %%edx\n\t"
      "addl %%esi, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "cmpl $0, (%%edx)\n\t"
      "movl %%edx, %%eax\n\t"
      "jne .LD3DDevice_SetLight_2\n\t"
      ".LD3DDevice_SetLight_3:\n\t"
      "movl 0x480(%%ebp), %%esi\n\t"
      "leal (%%edi,%%edi,8), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $2, %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "rep movsl\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "leal (%%edx,%%ebx,1), %%edi\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      "movl 0x480(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0c16]\n\t"
      "movl %%ebx, 0x480(%%ebp)\n\t"
      "movl 0x1c(%%esp), %%ebx\n\t"
      "movl %%esi, 0x484(%%ebp)\n\t"
      ".LD3DDevice_SetLight_4:\n\t"
      "movl 0x480(%%ebp), %%edx\n\t"
      "movl 0x20(%%esp), %%esi\n\t"
      "leal (%%ebx,%%ebx,8), %%ebx\n\t"
      "shll $4, %%ebx\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl $0x1a, %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x68(%%ebx), %%ecx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "orl $3, %%ecx\n\t"
      "cmpl $1, %%eax\n\t"
      "movl %%ecx, 0x68(%%ebx)\n\t"
      "je .LD3DDevice_SetLight_6\n\t"
      "flds 0x40(%%ebx)\n\t"
      "leal 0x6c(%%ebx), %%eax\n\t"
      "fchs\n\t"
      "pushl %%eax\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x44(%%ebx)\n\t"
      "fchs\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0x48(%%ebx)\n\t"
      "fchs\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[c1f2600]\n\t"
      "cmpl $2, (%%ebx)\n\t"
      "jne .LD3DDevice_SetLight_6\n\t"
      "movl 0x50(%%ebx), %%ecx\n\t"
      "leal 0x7c(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "leal 0x78(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1f2440]\n\t"
      "flds (%%edi)\n\t"
      "fadds 0x2533c8\n\t"
      "pushl %%ecx\n\t"
      "fsubs (%%esi)\n\t"
      "fstps 0x80(%%ebx)\n\t"
      "flds 0x60(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c40]\n\t"
      "fstps 0x20(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x64(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c40]\n\t"
      "fsts 0x1c(%%esp)\n\t"
      "fcomps 0x20(%%esp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LD3DDevice_SetLight_5\n\t"
      "flds 0x20(%%esp)\n\t"
      "fmuls 0x2c20e0\n\t"
      "fstps 0x1c(%%esp)\n\t"
      ".LD3DDevice_SetLight_5:\n\t"
      "flds 0x20(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fsubs 0x20(%%esp)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f25c0]\n\t"
      "fsts 0x84(%%ebx)\n\t"
      "fmuls 0x1c(%%esp)\n\t"
      "fchs\n\t"
      "fstps 0x88(%%ebx)\n\t"
      ".LD3DDevice_SetLight_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "orl $0x20, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c1d0bb9] "m"(b1e8400_c1d0bb9), [c1d0c16] "m"(b1e8400_c1d0c16), [c1f2600] "m"(b1e8400_c1f2600), [c1f2440] "m"(b1e8400_c1f2440), [c1f3c40] "m"(b1e8400_c1f3c40), [c1f25c0] "m"(b1e8400_c1f25c0)
      : "memory");
}
#else
#error "D3DDevice_SetLight: clang naked draft required"
#endif


/* D3DDevice_LightEnable (0x1e85e0) — XBE naked draft (batch 335). */
#if defined(__clang__)
static void (*const b1e85e0_c1e8400)(void) = D3DDevice_SetLight;

__attribute__((naked, noinline))
void D3DDevice_LightEnable(void)
{
  __asm__ volatile(
      "subl $0x68, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x70(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "cmpl 0x484(%%esi), %%ebx\n\t"
      "jae .LD3DDevice_LightEnable_1\n\t"
      "movl 0x480(%%esi), %%ecx\n\t"
      "leal (%%ebx,%%ebx,8), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "testb $1, 0x68(%%ecx,%%eax,1)\n\t"
      "jne .LD3DDevice_LightEnable_2\n\t"
      ".LD3DDevice_LightEnable_1:\n\t"
      "pushl %%edi\n\t"
      "leal 0xc(%%esp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%edx\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal 0x10(%%esp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl %%ebx\n\t"
      "movl $3, 0x14(%%esp)\n\t"
      "movl $0x3f800000, 0x5c(%%esp)\n\t"
      "movl $0x3f800000, 0x18(%%esp)\n\t"
      "movl $0x3f800000, 0x1c(%%esp)\n\t"
      "movl $0x3f800000, 0x20(%%esp)\n\t"
      "call *%[c1e8400]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "jne .LD3DDevice_LightEnable_7\n\t"
      ".LD3DDevice_LightEnable_2:\n\t"
      "movl 0x480(%%esi), %%eax\n\t"
      "leal (%%ebx,%%ebx,8), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl 0x68(%%ecx,%%eax,1), %%ebx\n\t"
      "addl %%eax, %%ecx\n\t"
      "orl $4, %%ebx\n\t"
      "movl %%ebx, 0x68(%%ecx)\n\t"
      "movl 0x488(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "leal 0x3fc(%%esi), %%edx\n\t"
      "je .LD3DDevice_LightEnable_5\n\t"
      ".LD3DDevice_LightEnable_3:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LD3DDevice_LightEnable_4\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0x8c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_LightEnable_3\n\t"
      "jmp .LD3DDevice_LightEnable_5\n\t"
      ".LD3DDevice_LightEnable_4:\n\t"
      "movl 0x8c(%%eax), %%eax\n\t"
      "movl %%eax, 0x8c(%%edx)\n\t"
      ".LD3DDevice_LightEnable_5:\n\t"
      "movl 0x78(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_LightEnable_6\n\t"
      "movl 0x488(%%esi), %%edx\n\t"
      "movl %%edx, 0x8c(%%ecx)\n\t"
      "movl %%ecx, 0x488(%%esi)\n\t"
      ".LD3DDevice_LightEnable_6:\n\t"
      "orl $0x20, 0x8(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_LightEnable_7:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "addl $0x68, %%esp\n\t"
      "ret\n\t"
      :
      : [c1e8400] "m"(b1e85e0_c1e8400)
      : "memory");
}
#else
#error "D3DDevice_LightEnable: clang naked draft required"
#endif


/* D3DDevice_GetTexture2 (0x1e86c0) — XBE naked draft (batch 349). */
#if defined(__clang__)
static void b1e86c0_c1ed8f0_tgt(void) { return; }
static void (*const b1e86c0_c1ed8f0)(void) = b1e86c0_c1ed8f0_tgt;

__attribute__((naked, noinline))
void D3DDevice_GetTexture2(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal 0xba0(%%ecx,%%eax,4), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_GetTexture2_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed8f0]\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_GetTexture2_1:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1ed8f0] "m"(b1e86c0_c1ed8f0)
      : "memory");
}
#else
#error "D3DDevice_GetTexture2: clang naked draft required"
#endif


/* D3DDevice_SetPalette (0x1e88a0) — XBE naked draft (batch 331). */
#if defined(__clang__)
static void __stdcall (*const b1e88a0_c1ed7d0)(void *resource) = (void *)D3D_DestroyResource;
static void b1e88a0_c1ed8b0_tgt(void) { return; }
static void (*const b1e88a0_c1ed8b0)(void) = b1e88a0_c1ed8b0_tgt;
static void (*const b1e88a0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetPalette(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "movl 0xbb0(%%edi,%%esi,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_SetPalette_1\n\t"
      "movl 0x1c(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0xbb0(%%edi,%%esi,4), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0xfff80000, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "testl $0x78ffff, %%ecx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "jne .LD3DDevice_SetPalette_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed7d0]\n\t"
      ".LD3DDevice_SetPalette_1:\n\t"
      "movl 0x14(%%esp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%ebx, 0xbb0(%%edi,%%esi,4)\n\t"
      "je .LD3DDevice_SetPalette_2\n\t"
      "pushl %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1ed8b0]\n\t"
      "movl (%%ebx), %%ebp\n\t"
      "pushl %%edi\n\t"
      "shrl $0x1c, %%ebp\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x4(%%ebx), %%ebx\n\t"
      "shll $6, %%esi\n\t"
      "orl %%ebp, %%ebx\n\t"
      "addl $0x41b20, %%esi\n\t"
      "movl %%esi, (%%eax)\n\t"
      "movl %%ebx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "popl %%ebp\n\t"
      ".LD3DDevice_SetPalette_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1ed7d0] "m"(b1e88a0_c1ed7d0), [c1ed8b0] "m"(b1e88a0_c1ed8b0), [c1efe10] "m"(b1e88a0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetPalette: clang naked draft required"
#endif


/* D3DDevice_SetIndices (0x1e8920) — XBE naked draft (batch 339). */
#if defined(__clang__)
static void b1e8920_c1ed8b0_tgt(void) { return; }
static void (*const b1e8920_c1ed8b0)(void) = b1e8920_c1ed8b0_tgt;
static void __stdcall (*const b1e8920_c1ed7d0)(void *resource) = (void *)D3D_DestroyResource;

__attribute__((naked, noinline))
void D3DDevice_SetIndices(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_SetIndices_1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ed8b0]\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x1fb494\n\t"
      "jmp .LD3DDevice_SetIndices_2\n\t"
      ".LD3DDevice_SetIndices_1:\n\t"
      "movl $0, 0x1fb494\n\t"
      ".LD3DDevice_SetIndices_2:\n\t"
      "movl 0x47c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_SetIndices_4\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0xfff80000, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "testl $0x78ffff, %%ecx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "jne .LD3DDevice_SetIndices_3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed7d0]\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl %%edi, 0x47c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x478(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_SetIndices_3:\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "movl %%edi, 0x47c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x478(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_SetIndices_4:\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%edi, 0x47c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x478(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1ed8b0] "m"(b1e8920_c1ed8b0), [c1ed7d0] "m"(b1e8920_c1ed7d0)
      : "memory");
}
#else
#error "D3DDevice_SetIndices: clang naked draft required"
#endif


/* D3DDevice_IsBusy (0x1e8a00) — XBE naked draft (batch 332). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_IsBusy(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x2304(%%eax), %%ecx\n\t"
      "movl 0x404(%%eax), %%edx\n\t"
      "movl 0x44(%%ecx), %%ecx\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "xorl %%ecx, %%eax\n\t"
      "testl $0xfffffff, %%eax\n\t"
      "je .LD3DDevice_IsBusy_1\n\t"
      "movl $1, %%eax\n\t"
      "ret\n\t"
      ".LD3DDevice_IsBusy_1:\n\t"
      "movl 0x400700(%%edx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edx, %%edx\n\t"
      "setne %%al\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_IsBusy: clang naked draft required"
#endif


/* D3DDevice_BeginVisibilityTest (0x1e8a40) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void (*const b1e8a40_c1efe10)(void) = (void *)XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_BeginVisibilityTest(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl $1, %%ecx\n\t"
      "movl $0x817c8, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e8a40_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_BeginVisibilityTest: clang naked draft required"
#endif


/* D3DDevice_EndVisibilityTest (0x1e8a70) — XBE naked draft (batch 329). */
#if defined(__clang__)
static void b1e8a70_c1e6fc0_tgt(void) { return; }
static void (*const b1e8a70_c1e6fc0)(void) = b1e8a70_c1e6fc0_tgt;
static void (*const b1e8a70_c1efe10)(void) = XMETAL_StartPush;
static void (*const b1e8a70_c1ef930)(void) = CDevice_KickOff;

__attribute__((naked, noinline))
void D3DDevice_EndVisibilityTest(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e6fc0]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LD3DDevice_EndVisibilityTest_1\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_EndVisibilityTest_1:\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1efe10]\n\t"
      "andl $0x2ffffff, %%esi\n\t"
      "movl $0x817cc, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "orl $0x1000000, %%esi\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "call *%[c1ef930]\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1e6fc0] "m"(b1e8a70_c1e6fc0), [c1efe10] "m"(b1e8a70_c1efe10), [c1ef930] "m"(b1e8a70_c1ef930)
      : "memory");
}
#else
#error "D3DDevice_EndVisibilityTest: clang naked draft required"
#endif


/* D3DDevice_GetDisplayFieldStatus (0x1e8ad0) — XBE naked draft (batch 327). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetDisplayFieldStatus(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x2b28(%%eax), %%edx\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "testl $0x1200000, 0x2510(%%eax)\n\t"
      "je .LD3DDevice_GetDisplayFieldStatus_1\n\t"
      "movw $0x80c0, %%dx\n\t"
      ".byte 0xec\n\t"
      "shrl $5, %%eax\n\t"
      "notb %%al\n\t"
      "andb $1, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "ret\n\t"
      ".LD3DDevice_GetDisplayFieldStatus_1:\n\t"
      "movl $3, (%%ecx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetDisplayFieldStatus: clang naked draft required"
#endif


/* D3DDevice_FlushVertexCache (0x1e8b10) — XBE naked draft (batch 370). */
#if defined(__clang__)
static void (*const b1e8b10_c1efe10)(void) = (void *)XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_FlushVertexCache(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl $0x41710, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e8b10_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_FlushVertexCache: clang naked draft required"
#endif


/* D3DDevice_SetModelView (0x1e8b40) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void (*const b1e8b40_c1efe10)(void) = XMETAL_StartPush;
static void b1e8b40_c1ef590_tgt(void) { return; }
static void (*const b1e8b40_c1ef590)(void) = b1e8b40_c1ef590_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetModelView(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LD3DDevice_SetModelView_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0x7ffffffd, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LD3DDevice_SetModelView_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "andl $0xfffffffd, %%ecx\n\t"
      "pushl %%edi\n\t"
      "orl $0x80000000, %%ecx\n\t"
      "pushl %%ebp\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $0x400480\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1ef590]\n\t"
      "pushl %%esi\n\t"
      "pushl $0x400680\n\t"
      "leal 0x44(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ef590]\n\t"
      "movl 0x18(%%esp), %%esi\n\t"
      "addl $0x88, %%ebx\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3DDevice_SetModelView_2\n\t"
      "leal 0x4(%%ebx), %%edi\n\t"
      "movl $0x300580, (%%ebx)\n\t"
      "movl $0xc, %%ecx\n\t"
      "rep movsl\n\t"
      "addl $0x34, %%ebx\n\t"
      ".LD3DDevice_SetModelView_2:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "movl $0x10, %%ecx\n\t"
      "testb %%al, %%cl\n\t"
      "movl %%ebx, (%%ebp)\n\t"
      "jne .LD3DDevice_SetModelView_3\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "leal 0x5e0(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      ".LD3DDevice_SetModelView_3:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e8b40_c1efe10), [c1ef590] "m"(b1e8b40_c1ef590)
      : "memory");
}
#else
#error "D3DDevice_SetModelView: clang naked draft required"
#endif


/* D3DDevice_SetTile (0x1e8d30) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void b1e8d30_c1f5e85_tgt(void) { return; }
static void (*const b1e8d30_c1f5e85)(void) = b1e8d30_c1f5e85_tgt;
static void b1e8d30_c1f6073_tgt(void) { return; }
static void (*const b1e8d30_c1f6073)(void) = b1e8d30_c1f6073_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetTile(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%edx\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x24(%%esp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LD3DDevice_SetTile_2\n\t"
      "cmpl %%eax, 0x4(%%esi)\n\t"
      "je .LD3DDevice_SetTile_2\n\t"
      "movl $6, %%ecx\n\t"
      "leal 0x8(%%esp), %%edi\n\t"
      "pushl %%ebx\n\t"
      "rep movsl\n\t"
      "movl 0xc(%%esp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "js .LD3DDevice_SetTile_1\n\t"
      "movl %%eax, 0x20(%%esp)\n\t"
      "movl %%eax, 0x1c(%%esp)\n\t"
      ".LD3DDevice_SetTile_1:\n\t"
      "movl 0x28(%%esp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal 0x21bc(%%edx,%%ecx,8), %%edi\n\t"
      "movl $6, %%ecx\n\t"
      "leal 0xc(%%esp), %%esi\n\t"
      "rep movsl\n\t"
      "movl 0x20(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x20(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x20(%%esp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x24(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x24(%%esp), %%ecx\n\t"
      "andl $0x3ffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x2308(%%edx), %%ecx\n\t"
      "call *%[c1f5e85]\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "ret\n\t"
      ".LD3DDevice_SetTile_2:\n\t"
      "movl 0x24(%%esp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,8), %%esi\n\t"
      "movl 0x21d0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x2308(%%edx), %%ecx\n\t"
      "call *%[c1f6073]\n\t"
      "leal 0x21bc(%%esi), %%edi\n\t"
      "movl $6, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "rep stosl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f5e85] "m"(b1e8d30_c1f5e85), [c1f6073] "m"(b1e8d30_c1f6073)
      : "memory");
}
#else
#error "D3DDevice_SetTile: clang naked draft required"
#endif


/* D3DDevice_SetScissors (0x1e9000) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b1e9000_c1efe10)(void) = XMETAL_StartPush;
static void b1e9000_c1f3c30_tgt(void) { return; }
static void (*const b1e9000_c1f3c30)(void) = b1e9000_c1f3c30_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetScissors(void)
{
  __asm__ volatile(
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x2c(%%esp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LD3DDevice_SetScissors_1\n\t"
      "movl 0xb00(%%ebp), %%eax\n\t"
      "movl 0xb08(%%ebp), %%edx\n\t"
      "movl 0xb04(%%ebp), %%ecx\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%eax, 0x24(%%esp)\n\t"
      "movl 0xb0c(%%ebp), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%ecx, 0x28(%%esp)\n\t"
      "leal 0x24(%%esp), %%ecx\n\t"
      "movl $1, 0x38(%%esp)\n\t"
      "movl %%ebx, 0x3c(%%esp)\n\t"
      "movl 0x38(%%esp), %%ebx\n\t"
      "movl %%edx, 0x2c(%%esp)\n\t"
      "movl %%eax, 0x30(%%esp)\n\t"
      "movl %%ecx, 0x40(%%esp)\n\t"
      ".LD3DDevice_SetScissors_1:\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x3c(%%esp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl $0x402b4, (%%edi)\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl 0x500(%%ebp), %%eax\n\t"
      "movl 0x504(%%ebp), %%ecx\n\t"
      "addl $8, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%eax, 0x10(%%esp)\n\t"
      "movl %%ecx, 0x14(%%esp)\n\t"
      "jbe .LD3DDevice_SetScissors_3\n\t"
      "movl 0x40(%%esp), %%ebx\n\t"
      "movl 0x38(%%esp), %%edx\n\t"
      "addl $4, %%ebx\n\t"
      "movl $0x402e0, %%esi\n\t"
      "movl %%edx, 0x18(%%esp)\n\t"
      ".LD3DDevice_SetScissors_2:\n\t"
      "fildl -0x4(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x14(%%esp)\n\t"
      "fstps 0x20(%%esp)\n\t"
      "fildl 0x4(%%ebx)\n\t"
      "fmuls 0x14(%%esp)\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "flds 0x1c(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x253398\n\t"
      "movl %%eax, 0x24(%%esp)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "movl 0x20(%%esp), %%ecx\n\t"
      "decl %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "leal -0x20(%%esi), %%edx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "fildl (%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x18(%%esp)\n\t"
      "fstps 0x24(%%esp)\n\t"
      "fildl 0x8(%%ebx)\n\t"
      "fmuls 0x18(%%esp)\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "flds 0x20(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x253398\n\t"
      "movl %%eax, 0x20(%%esp)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "movl 0x1c(%%esp), %%ecx\n\t"
      "decl %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "movl %%esi, 0x8(%%edi)\n\t"
      "addl $0x10, %%edi\n\t"
      "addl $4, %%esi\n\t"
      "addl $0x10, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x18(%%esp)\n\t"
      "jne .LD3DDevice_SetScissors_2\n\t"
      "movl 0x38(%%esp), %%ebx\n\t"
      ".LD3DDevice_SetScissors_3:\n\t"
      "movl 0x40(%%esp), %%esi\n\t"
      "movl 0x3c(%%esp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%edi, (%%ebp)\n\t"
      "shrl $2, %%ecx\n\t"
      "leal 0x227c(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, 0x22fc(%%ebp)\n\t"
      "movl %%eax, 0x2300(%%ebp)\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "addl $0x24, %%esp\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9000_c1efe10), [c1f3c30] "m"(b1e9000_c1f3c30)
      : "memory");
}
#else
#error "D3DDevice_SetScissors: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_MultiSampleType (0x1e92f0) — XBE naked draft (batch 383). */
#if defined(__clang__)
static void __stdcall (*const b1e92f0_c1e7af0)(void *render_target, void *depth_stencil) = (void *)D3DDevice_SetRenderTarget;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_MultiSampleType(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl %%ecx, 0x1fb8b0\n\t"
      "movl 0x410(%%eax), %%edx\n\t"
      "movl 0x40c(%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e7af0]\n\t"
      "ret\n\t"
      :
      : [c1e7af0] "m"(b1e92f0_c1e7af0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_MultiSampleType: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_PSTextureModes (0x1e9320) — XBE naked draft (batch 332). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_SetRenderState_PSTextureModes(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "orl $0x400, %%edx\n\t"
      "movl %%ecx, 0x420(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl %%ecx, 0x1fb868\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_PSTextureModes: clang naked draft required"
#endif


/* D3DDevice_SetRenderStateNotInline (0x1e93a0) — XBE naked draft (batch 358). */
#if defined(__clang__)
static void (*const b1e93a0_c1e9350)(uint32_t reg, uint32_t value) = (void *)D3DDevice_SetRenderState_Simple;

__attribute__((naked, noinline))
void D3DDevice_SetRenderStateNotInline(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "cmpl $0x52, %%esi\n\t"
      "jge .LD3DDevice_SetRenderStateNotInline_1\n\t"
      "movl 0x282b90(,%%esi,4), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb698(,%%esi,4)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_SetRenderStateNotInline_1:\n\t"
      "cmpl $0x74, %%esi\n\t"
      "jge .LD3DDevice_SetRenderStateNotInline_2\n\t"
      "movl 0x1f9d50(,%%esi,4), %%eax\n\t"
      "orl %%eax, 0x1fbb18\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl %%ecx, 0x1fb698(,%%esi,4)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_SetRenderStateNotInline_2:\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *0x1f9c58(,%%esi,4)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1e9350] "m"(b1e93a0_c1e9350)
      : "memory");
}
#else
#error "D3DDevice_SetRenderStateNotInline: clang naked draft required"
#endif


/* D3DDevice_SetRenderState2 (0x1e9400) — XBE naked draft (batch 395). */
#if defined(__clang__)
static void (*const b1e9400_c1e93a0)(void) = (void *)D3DDevice_SetRenderStateNotInline;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState2(void)
{
  __asm__ volatile(
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e93a0]\n\t"
      "ret\n\t"
      :
      : [c1e93a0] "m"(b1e9400_c1e93a0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState2: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_EdgeAntiAlias (0x1e9620) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b1e9620_c1efe10)(void) = (void *)XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_EdgeAntiAlias(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0x80320, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x1fb8a4\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9620_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_EdgeAntiAlias: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_ShadowFunc (0x1e9650) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b1e9650_c1efe10)(void) = (void *)XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_ShadowFunc(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0x41e6c, (%%eax)\n\t"
      "leal -0x200(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x1fb8b4\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9650_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_ShadowFunc: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_FogColor (0x1e9680) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b1e9680_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_FogColor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movzbl 0xe(%%esp), %%edx\n\t"
      "movl %%ecx, %%edi\n\t"
      "andl $0xff, %%edi\n\t"
      "shll $0x10, %%edi\n\t"
      "orl %%edi, %%edx\n\t"
      "movl %%ecx, %%edi\n\t"
      "andl $0xff00ff00, %%edi\n\t"
      "orl %%edi, %%edx\n\t"
      "movl $0x402a8, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x1fb870\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9680_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_FogColor: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_FrontFace (0x1e9740) — XBE naked draft (batch 372). */
#if defined(__clang__)
static void (*const b1e9740_c1efe10)(void) = (void *)XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_FrontFace(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0x403a0, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0x1fb894, %%eax\n\t"
      "movl %%ecx, 0x1fb890\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x4(%%esp)\n\t"
      ".byte 0xe9, 0x5c, 0xff, 0xff, 0xff\n\t"
      :
      : [c1efe10] "m"(b1e9740_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_FrontFace: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_NormalizeNormals (0x1e9780) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b1e9780_c1efe10)(void) = (void *)XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_NormalizeNormals(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0x403a4, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "orl $2, 0x8(%%esi)\n\t"
      "movl %%ecx, 0x1fb880\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9780_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_NormalizeNormals: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_TextureFactor (0x1e97b0) — XBE naked draft (batch 331). */
#if defined(__clang__)
static void (*const b1e97b0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_TextureFactor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x414(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_SetRenderState_TextureFactor_1\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl $0x400a60, (%%edx)\n\t"
      "addl $4, %%edx\n\t"
      "movl %%edx, %%edi\n\t"
      "movl $0x10, %%ecx\n\t"
      "rep stosl\n\t"
      "addl $0x40, %%edx\n\t"
      "movl %%edx, (%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x1fb898\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_SetRenderState_TextureFactor_1:\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl %%eax, 0x1fb898\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e97b0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_TextureFactor: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_LineWidth (0x1e9800) — XBE naked draft (batch 328). */
#if defined(__clang__)
static void b1e9800_c1f3c30_tgt(void) { return; }
static void (*const b1e9800_c1f3c30)(void) = b1e9800_c1f3c30_tgt;
static void (*const b1e9800_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_LineWidth(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl 0x8(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl %%ebx, 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%edi\n\t"
      "fmuls 0x508(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f78\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl $0x1ff, %%edi\n\t"
      "jbe .LD3DDevice_SetRenderState_LineWidth_1\n\t"
      "movl $0x1ff, %%edi\n\t"
      ".LD3DDevice_SetRenderState_LineWidth_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%edi, 0x4(%%eax)\n\t"
      "movl $0x40380, (%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, 0x1fb8b8\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1f3c30] "m"(b1e9800_c1f3c30), [c1efe10] "m"(b1e9800_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_LineWidth: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_Dxt1NoiseEnable (0x1e9860) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void (*const b1e9860_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_Dxt1NoiseEnable(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl 0x8(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x40c(%%esi), %%eax\n\t"
      "movzbl 0xd(%%eax), %%ecx\n\t"
      "movb 0x1f9d58(%%ecx), %%dl\n\t"
      "pushl %%edi\n\t"
      "andb $0x3c, %%dl\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpb $0x20, %%dl\n\t"
      "jne .LD3DDevice_SetRenderState_Dxt1NoiseEnable_1\n\t"
      "movl %%ebx, %%edi\n\t"
      ".LD3DDevice_SetRenderState_Dxt1NoiseEnable_1:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "je .LD3DDevice_SetRenderState_Dxt1NoiseEnable_2\n\t"
      "xorl $1, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[c1efe10]\n\t"
      "movl $0x40110, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "movl $0x41d8c, 0x8(%%eax)\n\t"
      "movl %%edi, 0xc(%%eax)\n\t"
      "movl $0x40100, 0x10(%%eax)\n\t"
      "movl $0x31c, 0x14(%%eax)\n\t"
      "addl $0x18, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      ".LD3DDevice_SetRenderState_Dxt1NoiseEnable_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, 0x1fb8bc\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9860_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_Dxt1NoiseEnable: clang naked draft required"
#endif


/* 0x001e98e0 */
void D3DDevice_SetRenderState_ZBias(uint32_t value)
{
  int edi = 0;

  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  /* mem[0x001fb89c] = edi */

  (void)edi;
}

/* D3DDevice_SetRenderState_LogicOp (0x1e9960) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void (*const b1e9960_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_LogicOp(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LD3DDevice_SetRenderState_LogicOp_1\n\t"
      "movl $0x417bc, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x1fb8a0\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_SetRenderState_LogicOp_1:\n\t"
      "movl $0x817bc, (%%eax)\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x1fb8a0\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9960_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_LogicOp: clang naked draft required"
#endif


/* 0x001e99b0 */
void D3DDevice_SetRenderState_FillMode(uint32_t value)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb874] = ecx */

  (void)ecx;
}

/* D3DDevice_SetRenderState_BackFillMode (0x1e99f0) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void (*const b1e99f0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_BackFillMode(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fb874, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x1fb878\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x1fb87c, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x1fb878, %%ecx\n\t"
      "jne .LD3DDevice_SetRenderState_BackFillMode_1\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LD3DDevice_SetRenderState_BackFillMode_1:\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "movl $0x8038c, (%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movl %%esi, 0x1fb874\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e99f0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_BackFillMode: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_TwoSidedLighting (0x1e9a40) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b1e9a40_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_TwoSidedLighting(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "pushl %%esi\n\t"
      "orl $0x20, 0x8(%%eax)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0x1fb874, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x1fb87c\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x1fb87c, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x1fb878, %%ecx\n\t"
      "jne .LD3DDevice_SetRenderState_TwoSidedLighting_1\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LD3DDevice_SetRenderState_TwoSidedLighting_1:\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "movl $0x8038c, (%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movl %%esi, 0x1fb874\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9a40_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_TwoSidedLighting: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_VertexBlend (0x1e9aa0) — XBE naked draft (batch 352). */
#if defined(__clang__)
static void (*const b1e9aa0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_VertexBlend(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "orl $2, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0x40328, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x1fb86c\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9aa0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_VertexBlend: clang naked draft required"
#endif


/* D3DDevice_SetTextureState_TexCoordIndex (0x1e9ae0) — XBE naked draft (batch 306). */
#if defined(__clang__)
static void (*const b1e9ae0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetTextureState_TexCoordIndex(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%esp), %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "shll $7, %%eax\n\t"
      "pushl %%ebp\n\t"
      "movl %%ecx, 0x1fb508(%%eax)\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "andl $0xffff0000, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $0x20000, %%ecx\n\t"
      "pushl %%edi\n\t"
      "ja .LD3DDevice_SetTextureState_TexCoordIndex_3\n\t"
      "je .LD3DDevice_SetTextureState_TexCoordIndex_2\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_SetTextureState_TexCoordIndex_1\n\t"
      "cmpl $0x10000, %%ecx\n\t"
      "jne .LD3DDevice_SetTextureState_TexCoordIndex_4\n\t"
      "movl $0x8511, %%edi\n\t"
      "jmp .LD3DDevice_SetTextureState_TexCoordIndex_7\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_1:\n\t"
      "orl $0x180, 0x8(%%esi)\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LD3DDevice_SetTextureState_TexCoordIndex_8\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_2:\n\t"
      "movl $0x2400, %%edi\n\t"
      "jmp .LD3DDevice_SetTextureState_TexCoordIndex_8\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_3:\n\t"
      "cmpl $0x30000, %%ecx\n\t"
      "je .LD3DDevice_SetTextureState_TexCoordIndex_6\n\t"
      "cmpl $0x40000, %%ecx\n\t"
      "je .LD3DDevice_SetTextureState_TexCoordIndex_5\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_4:\n\t"
      "movl $0x2402, %%edi\n\t"
      "jmp .LD3DDevice_SetTextureState_TexCoordIndex_7\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_5:\n\t"
      "movl $0x2401, %%edi\n\t"
      "jmp .LD3DDevice_SetTextureState_TexCoordIndex_8\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_6:\n\t"
      "movl $0x8512, %%edi\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_7:\n\t"
      "movl $1, %%eax\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_8:\n\t"
      "movl 0x4fc(%%esi), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LD3DDevice_SetTextureState_TexCoordIndex_9\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_SetTextureState_TexCoordIndex_9\n\t"
      "orl $2, 0x8(%%esi)\n\t"
      ".LD3DDevice_SetTextureState_TexCoordIndex_9:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl $1, %%ebp\n\t"
      "shll %%cl, %%ebp\n\t"
      "shll %%cl, %%eax\n\t"
      "pushl %%esi\n\t"
      "notl %%ebp\n\t"
      "andl %%edx, %%ebp\n\t"
      "orl %%eax, %%ebp\n\t"
      "movl %%ebp, 0x4fc(%%esi)\n\t"
      "call *%[c1efe10]\n\t"
      "addl $0xc03c, %%ebx\n\t"
      "movl %%edi, 0x4(%%eax)\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "movl %%edi, 0xc(%%eax)\n\t"
      "shll $4, %%ebx\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "addl $0x10, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "orl $0x194, %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9ae0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetTextureState_TexCoordIndex: clang naked draft required"
#endif


/* D3DDevice_SetTextureState_BumpEnv (0x1e9bc0) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b1e9bc0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetTextureState_BumpEnv(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "movl 0x414(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, %%ebx\n\t"
      "jne .LD3DDevice_SetTextureState_BumpEnv_1\n\t"
      "leal 0x1(%%esi), %%ebx\n\t"
      ".LD3DDevice_SetTextureState_BumpEnv_1:\n\t"
      "testb $3, %%bl\n\t"
      "movl 0x1c(%%esp), %%ebp\n\t"
      "je .LD3DDevice_SetTextureState_BumpEnv_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "shll $4, %%ebx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "leal 0x41ad0(,%%ebx,4), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%ebp, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      ".LD3DDevice_SetTextureState_BumpEnv_2:\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "shll $5, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, 0x1fb498(,%%esi,4)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9bc0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetTextureState_BumpEnv: clang naked draft required"
#endif


/* D3DDevice_SetTextureState_ColorKeyColor (0x1e9c60) — XBE naked draft (batch 352). */
#if defined(__clang__)
static void (*const b1e9c60_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetTextureState_ColorKeyColor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "leal 0x40ae0(,%%ecx,4), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "shll $7, %%ecx\n\t"
      "movl %%edx, 0x1fb510(%%ecx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1e9c60_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetTextureState_ColorKeyColor: clang naked draft required"
#endif


/* D3DDevice_SetTextureStageStateNotInline (0x1e9cb0) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void (*const b1e9cb0_c1e9ae0)(void) = (void *)D3DDevice_SetTextureState_TexCoordIndex;
static void __stdcall (*const b1e9cb0_c1e9c20)(uint32_t stage, uint32_t color) = (void *)D3DDevice_SetTextureState_BorderColor;
static void (*const b1e9cb0_c1e9c60)(void) = (void *)D3DDevice_SetTextureState_ColorKeyColor;

__attribute__((naked, noinline))
void D3DDevice_SetTextureStageStateNotInline(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%eax\n\t"
      "cmpl $0x16, %%eax\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "jge .LD3DDevice_SetTextureStageStateNotInline_2\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "shll $5, %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "movl 0x1fb3d8(,%%eax,4), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl %%esi, 0x1fb498(,%%edx,4)\n\t"
      "orl %%eax, 0x8(%%ecx)\n\t"
      "popl %%esi\n\t"
      ".LD3DDevice_SetTextureStageStateNotInline_1:\n\t"
      "ret\n\t"
      ".LD3DDevice_SetTextureStageStateNotInline_2:\n\t"
      "cmpl $0x1c, %%eax\n\t"
      "jne .LD3DDevice_SetTextureStageStateNotInline_3\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e9ae0]\n\t"
      "ret\n\t"
      ".LD3DDevice_SetTextureStageStateNotInline_3:\n\t"
      "cmpl $0x1d, %%eax\n\t"
      "jne .LD3DDevice_SetTextureStageStateNotInline_4\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e9c20]\n\t"
      "ret\n\t"
      ".LD3DDevice_SetTextureStageStateNotInline_4:\n\t"
      "cmpl $0x1e, %%eax\n\t"
      "jne .LD3DDevice_SetTextureStageStateNotInline_5\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e9c60]\n\t"
      "ret\n\t"
      ".LD3DDevice_SetTextureStageStateNotInline_5:\n\t"
      "cmpl $0x1b, %%eax\n\t"
      "jg .LD3DDevice_SetTextureStageStateNotInline_1\n\t"
      "movl %%eax, 0x8(%%esp)\n\t"
      ".byte 0xe9, 0x8b, 0xfe, 0xff, 0xff\n\t"
      :
      : [c1e9ae0] "m"(b1e9cb0_c1e9ae0), [c1e9c20] "m"(b1e9cb0_c1e9c20), [c1e9c60] "m"(b1e9cb0_c1e9c60)
      : "memory");
}
#else
#error "D3DDevice_SetTextureStageStateNotInline: clang naked draft required"
#endif


/* D3D_CommonSetDebugRegisters (0x1ea1c0) — XBE naked draft (batch 321). */
#if defined(__clang__)
static void (*const b1ea1c0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3D_CommonSetDebugRegisters(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x2b44(%%esi), %%edx\n\t"
      "andl $0xfffffff7, %%edx\n\t"
      "movl %%edx, 0x2b44(%%esi)\n\t"
      "movl 0x1fb8d4, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "je .LD3D_CommonSetDebugRegisters_1\n\t"
      "orl $8, %%eax\n\t"
      "movl %%eax, 0x2b44(%%esi)\n\t"
      ".LD3D_CommonSetDebugRegisters_1:\n\t"
      "movl 0x2b48(%%esi), %%edx\n\t"
      "andl $0xe7efffff, %%edx\n\t"
      "movl %%edx, 0x2b48(%%esi)\n\t"
      "movl 0x1fb8cc, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "je .LD3D_CommonSetDebugRegisters_2\n\t"
      "orl $0x100000, %%eax\n\t"
      "movl %%eax, 0x2b48(%%esi)\n\t"
      ".LD3D_CommonSetDebugRegisters_2:\n\t"
      "movl 0x1fb8d0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_CommonSetDebugRegisters_3\n\t"
      "orl $0x8000000, 0x2b48(%%esi)\n\t"
      ".LD3D_CommonSetDebugRegisters_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl $0x40110, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "movl 0x2b44(%%esi), %%ecx\n\t"
      "movl $0x81d8c, 0x8(%%eax)\n\t"
      "movl $0x400094, 0xc(%%eax)\n\t"
      "movl %%ecx, 0x10(%%eax)\n\t"
      "movl $0x40100, 0x14(%%eax)\n\t"
      "movl $0x320, %%edx\n\t"
      "movl %%edx, 0x18(%%eax)\n\t"
      "movl 0x2b48(%%esi), %%ecx\n\t"
      "movl $0x81d8c, 0x1c(%%eax)\n\t"
      "movl $0x400b80, 0x20(%%eax)\n\t"
      "movl %%ecx, 0x24(%%eax)\n\t"
      "movl $0x40100, 0x28(%%eax)\n\t"
      "movl %%edx, 0x2c(%%eax)\n\t"
      "addl $0x30, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ea1c0_c1efe10)
      : "memory");
}
#else
#error "D3D_CommonSetDebugRegisters: clang naked draft required"
#endif


/* 0x001ea300 */
void D3DDevice_SetRenderState_StencilEnable(uint32_t value)
{
  int ecx = 0;
  int edx = 0;

  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea31e */
  /* test edx, edx -> je 0x1ea341 */
  /* test edx, edx -> je 0x1ea33e */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea341 */
  /* test edx, edx -> je 0x1ea366 */
  /* test ecx, ecx -> je 0x1ea366 */
  /* mem[0x001fb888] = edx */

  (void)ecx;
  (void)edx;
}

/* 0x001ea380 */
void D3DDevice_SetRenderState_StencilFail(uint32_t value)
{
  int ecx = 0;
  int edx = 0;

  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea39e */
  /* test edx, edx -> je 0x1ea3c1 */
  /* test edx, edx -> je 0x1ea3be */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea3c1 */
  /* mem[0x001fb88c] = ecx */

  (void)ecx;
  (void)edx;
}

/* D3DDevice_SetRenderState_YuvEnable (0x1ea3f0) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void (*const b1ea3f0_c1efe10)(void) = (void *)XMETAL_StartPush;
static void b1ea3f0_c1e9f80_tgt(void) { return; }
static void (*const b1ea3f0_c1e9f80)(void) = b1ea3f0_c1e9f80_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_YuvEnable(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x1fb8c0\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9f80]\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ea3f0_c1efe10), [c1e9f80] "m"(b1ea3f0_c1e9f80)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_YuvEnable: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_OcclusionCullEnable (0x1ea420) — XBE naked draft (batch 330). */
#if defined(__clang__)
static void (*const b1ea420_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_OcclusionCullEnable(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x1fb8c4\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x1fb8c8, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_SetRenderState_OcclusionCullEnable_1\n\t"
      "movl $2, %%ecx\n\t"
      ".LD3DDevice_SetRenderState_OcclusionCullEnable_1:\n\t"
      "movl 0x1fb8c4, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_SetRenderState_OcclusionCullEnable_3\n\t"
      "movl 0x1fb888, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_SetRenderState_OcclusionCullEnable_2\n\t"
      "cmpl $0x1e00, 0x1fb88c\n\t"
      "jne .LD3DDevice_SetRenderState_OcclusionCullEnable_3\n\t"
      ".LD3DDevice_SetRenderState_OcclusionCullEnable_2:\n\t"
      "orl $1, %%ecx\n\t"
      ".LD3DDevice_SetRenderState_OcclusionCullEnable_3:\n\t"
      "movl $0x41d84, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ea420_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_OcclusionCullEnable: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_StencilCullEnable (0x1ea480) — XBE naked draft (batch 330). */
#if defined(__clang__)
static void (*const b1ea480_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_StencilCullEnable(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x1fb8c8\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x1fb8c8, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_SetRenderState_StencilCullEnable_1\n\t"
      "movl $2, %%ecx\n\t"
      ".LD3DDevice_SetRenderState_StencilCullEnable_1:\n\t"
      "movl 0x1fb8c4, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_SetRenderState_StencilCullEnable_3\n\t"
      "movl 0x1fb888, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_SetRenderState_StencilCullEnable_2\n\t"
      "cmpl $0x1e00, 0x1fb88c\n\t"
      "jne .LD3DDevice_SetRenderState_StencilCullEnable_3\n\t"
      ".LD3DDevice_SetRenderState_StencilCullEnable_2:\n\t"
      "orl $1, %%ecx\n\t"
      ".LD3DDevice_SetRenderState_StencilCullEnable_3:\n\t"
      "movl $0x41d84, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ea480_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_StencilCullEnable: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_RopZCmpAlwaysRead (0x1ea4e0) — XBE naked draft (batch 393). */
#if defined(__clang__)
static void (*const b1ea4e0_c1ea1c0)(void) = (void *)D3D_CommonSetDebugRegisters;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_RopZCmpAlwaysRead(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, 0x1fb8cc\n\t"
      "call *%[c1ea1c0]\n\t"
      "ret\n\t"
      :
      : [c1ea1c0] "m"(b1ea4e0_c1ea1c0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_RopZCmpAlwaysRead: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_RopZRead (0x1ea500) — XBE naked draft (batch 394). */
#if defined(__clang__)
static void (*const b1ea500_c1ea1c0)(void) = (void *)D3D_CommonSetDebugRegisters;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_RopZRead(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, 0x1fb8d0\n\t"
      "call *%[c1ea1c0]\n\t"
      "ret\n\t"
      :
      : [c1ea1c0] "m"(b1ea500_c1ea1c0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_RopZRead: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_DoNotCullUncompressed (0x1ea520) — XBE naked draft (batch 394). */
#if defined(__clang__)
static void (*const b1ea520_c1ea1c0)(void) = (void *)D3D_CommonSetDebugRegisters;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_DoNotCullUncompressed(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, 0x1fb8d4\n\t"
      "call *%[c1ea1c0]\n\t"
      "ret\n\t"
      :
      : [c1ea1c0] "m"(b1ea520_c1ea1c0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_DoNotCullUncompressed: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_MultiSampleAntiAlias (0x1ea540) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void b1ea540_c1eb6f0_tgt(void) { return; }
static void (*const b1ea540_c1eb6f0)(void) = b1ea540_c1eb6f0_tgt;
static void (*const b1ea540_c1efe10)(void) = XMETAL_StartPush;
static void b1ea540_c1e9db0_tgt(void) { return; }
static void (*const b1ea540_c1e9db0)(void) = b1ea540_c1e9db0_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_MultiSampleAntiAlias(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%eax, 0x1fb8a8\n\t"
      "call *%[c1eb6f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9db0]\n\t"
      "movl 0x1fb8ac, %%ecx\n\t"
      "movl 0x1fb8a8, %%edx\n\t"
      "shll $0x10, %%ecx\n\t"
      "andl $0xf, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl $0x41d7c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1eb6f0] "m"(b1ea540_c1eb6f0), [c1efe10] "m"(b1ea540_c1efe10), [c1e9db0] "m"(b1ea540_c1e9db0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_MultiSampleAntiAlias: clang naked draft required"
#endif


/* D3DDevice_SetRenderState_MultiSampleMask (0x1ea590) — XBE naked draft (batch 369). */
#if defined(__clang__)
static void b1ea590_c1eb6f0_tgt(void) { return; }
static void (*const b1ea590_c1eb6f0)(void) = b1ea590_c1eb6f0_tgt;
static void (*const b1ea590_c1efe10)(void) = (void *)XMETAL_StartPush;
static void b1ea590_c1e9db0_tgt(void) { return; }
static void (*const b1ea590_c1e9db0)(void) = b1ea590_c1e9db0_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetRenderState_MultiSampleMask(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%eax, 0x1fb8ac\n\t"
      "call *%[c1eb6f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9db0]\n\t"
      "movl 0x1fb8a8, %%ecx\n\t"
      "movl 0x1fb8ac, %%edx\n\t"
      "andl $0xf, %%ecx\n\t"
      "shll $0x10, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl $0x41d7c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1eb6f0] "m"(b1ea590_c1eb6f0), [c1efe10] "m"(b1ea590_c1efe10), [c1e9db0] "m"(b1ea590_c1e9db0)
      : "memory");
}
#else
#error "D3DDevice_SetRenderState_MultiSampleMask: clang naked draft required"
#endif


/* D3DDevice_GetShaderConstantMode (0x1eac90) — XBE naked draft (batch 373). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetShaderConstantMode(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x2140(%%eax), %%ecx\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetShaderConstantMode: clang naked draft required"
#endif


/* D3DDevice_CreateVertexShader (0x1eaf70) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void b1eaf70_c1eae70_tgt(void) { return; }
static void (*const b1eaf70_c1eae70)(void) = b1eaf70_c1eae70_tgt;
static void *__stdcall (*const b1eaf70_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;
static void b1eaf70_c1eacb0_tgt(void) { return; }
static void (*const b1eaf70_c1eacb0)(void) = b1eaf70_c1eacb0_tgt;
static void b1eaf70_c1eac20_tgt(void) { return; }
static void (*const b1eaf70_c1eac20)(void) = b1eaf70_c1eac20_tgt;

__attribute__((naked, noinline))
void D3DDevice_CreateVertexShader(void)
{
  __asm__ volatile(
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x14(%%esp), %%ebp\n\t"
      "testl %%ebp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "je .LD3DDevice_CreateVertexShader_1\n\t"
      "movzwl (%%ebp), %%eax\n\t"
      "movzwl 0x2(%%ebp), %%ecx\n\t"
      "movl %%eax, 0xc(%%esp)\n\t"
      "movl %%ecx, 0x18(%%esp)\n\t"
      ".LD3DDevice_CreateVertexShader_1:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ebp, %%ebp\n\t"
      "je .LD3DDevice_CreateVertexShader_2\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "leal 0x7f(%%eax), %%edx\n\t"
      "shrl $7, %%edx\n\t"
      "leal (%%eax,%%edx,4), %%esi\n\t"
      ".LD3DDevice_CreateVertexShader_2:\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_CreateVertexShader_3\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1eae70]\n\t"
      "shll $2, %%eax\n\t"
      ".LD3DDevice_CreateVertexShader_3:\n\t"
      "leal (%%eax,%%esi,1), %%ebx\n\t"
      "leal 0x16c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1d0bb9]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LD3DDevice_CreateVertexShader_4\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      ".LD3DDevice_CreateVertexShader_4:\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x5b, %%ecx\n\t"
      "movl %%esi, %%edi\n\t"
      "rep stosl\n\t"
      "movl 0x24(%%esp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl $1, (%%esi)\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "movl $0x14, %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LD3DDevice_CreateVertexShader_5:\n\t"
      "movl $2, (%%eax)\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LD3DDevice_CreateVertexShader_5\n\t"
      "movl 0x18(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_CreateVertexShader_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%ebp, %%ebp\n\t"
      "sete %%dl\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1eacb0]\n\t"
      ".LD3DDevice_CreateVertexShader_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ebp, %%ebp\n\t"
      "je .LD3DDevice_CreateVertexShader_9\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "orl $4, %%edi\n\t"
      "cmpl $0x2078, %%ecx\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl %%edi, %%eax\n\t"
      "je .LD3DDevice_CreateVertexShader_7\n\t"
      "orl $1, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".LD3DDevice_CreateVertexShader_7:\n\t"
      "cmpl $0x7378, %%ecx\n\t"
      "jne .LD3DDevice_CreateVertexShader_8\n\t"
      "orl $8, 0x4(%%esi)\n\t"
      ".LD3DDevice_CreateVertexShader_8:\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $4, %%ebp\n\t"
      "pushl %%ebp\n\t"
      "leal 0x168(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1eac20]\n\t"
      "subl %%edi, %%eax\n\t"
      "movl 0x18(%%esp), %%edi\n\t"
      "sarl $2, %%eax\n\t"
      ".LD3DDevice_CreateVertexShader_9:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_CreateVertexShader_10\n\t"
      "leal 0x168(%%esi,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1eae70]\n\t"
      ".LD3DDevice_CreateVertexShader_10:\n\t"
      "movl 0x20(%%esp), %%edx\n\t"
      "shrl $2, %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movl $0, 0x168(%%esi,%%eax,4)\n\t"
      "orl $1, %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%esi, (%%edx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      :
      : [c1eae70] "m"(b1eaf70_c1eae70), [c1d0bb9] "m"(b1eaf70_c1d0bb9), [c1eacb0] "m"(b1eaf70_c1eacb0), [c1eac20] "m"(b1eaf70_c1eac20)
      : "memory");
}
#else
#error "D3DDevice_CreateVertexShader: clang naked draft required"
#endif


/* D3DDevice_GetVertexShader (0x1eb0b0) — XBE naked draft (batch 373). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShader(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x474(%%eax), %%ecx\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShader: clang naked draft required"
#endif


/* D3DDevice_GetVertexShaderConstant (0x1eb0d0) — XBE naked draft (batch 358). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShaderConstant(void)
{
  __asm__ volatile(
      "movl 0xc(%%esp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "shll $4, %%ecx\n\t"
      "addl $0x12c, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl %%edi, %%esi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "shrl $2, %%ecx\n\t"
      "rep movsl\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShaderConstant: clang naked draft required"
#endif


/* D3DDevice_GetVertexShaderInput (0x1eb110) — XBE naked draft (batch 321). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShaderInput(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x1fe6a0, %%eax\n\t"
      "je .LD3DDevice_GetVertexShaderInput_1\n\t"
      "movl 0x724(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LD3DDevice_GetVertexShaderInput_1:\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_GetVertexShaderInput_2\n\t"
      "movl 0x720(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LD3DDevice_GetVertexShaderInput_2:\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_GetVertexShaderInput_3\n\t"
      "movl 0x724(%%eax), %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "pushl %%esi\n\t"
      "shrl $2, %%ecx\n\t"
      "leal 0x728(%%eax), %%esi\n\t"
      "rep movsl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "popl %%esi\n\t"
      ".LD3DDevice_GetVertexShaderInput_3:\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "shrl $0x1e, %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShaderInput: clang naked draft required"
#endif


/* 0x001eb2d0 */
void D3DDevice_SetStreamSource(uint32_t stream, void *vertex_buffer, uint32_t stride)
{
  int eax = 0;
  int edi = 0;

  /* relift: FUN_001ed8b0(0); */
  /* test eax, eax -> je 0x1eb321 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x1eb393 */
  /* relift: FUN_001ed8f0(0); */

  (void)eax;
  (void)edi;
}

/* D3DDevice_RunVertexStateShader (0x1eb3b0) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b1eb3b0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_RunVertexStateShader(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_RunVertexStateShader_1\n\t"
      "flds 0xc(%%ecx)\n\t"
      "addl $0x14, %%eax\n\t"
      "flds 0x8(%%ecx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "movl $0x101e80, -0x14(%%eax)\n\t"
      "fstps -0x10(%%eax)\n\t"
      "fstps -0xc(%%eax)\n\t"
      "fstps -0x8(%%eax)\n\t"
      "fstps -0x4(%%eax)\n\t"
      ".LD3DDevice_RunVertexStateShader_1:\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl $0x41e90, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1eb3b0_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_RunVertexStateShader: clang naked draft required"
#endif


/* D3DDevice_LoadVertexShader (0x1eb400) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void b1eb400_c1eab60_tgt(void) { return; }
static void (*const b1eb400_c1eab60)(void) = b1eb400_c1eab60_tgt;
static void b1eb400_c1efe30_tgt(void) { return; }
static void (*const b1eb400_c1efe30)(void) = b1eb400_c1efe30_tgt;

__attribute__((naked, noinline))
void D3DDevice_LoadVertexShader(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl 0x1fe6a0, %%ebx\n\t"
      "movb 0xc(%%ebx), %%al\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "decl %%edi\n\t"
      "testb $0x10, %%al\n\t"
      "jne .LD3DDevice_LoadVertexShader_1\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1eab60]\n\t"
      ".LD3DDevice_LoadVertexShader_1:\n\t"
      "movl 0x14(%%edi), %%esi\n\t"
      "leal 0x2(%%esi), %%ebp\n\t"
      "pushl %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1efe30]\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%esi, %%ecx\n\t"
      "leal 0x168(%%edi), %%esi\n\t"
      "movl $0x41e9c, (%%eax)\n\t"
      "leal 0x8(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "leal (%%eax,%%ebp,4), %%edx\n\t"
      "popl %%ebp\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1eab60] "m"(b1eb400_c1eab60), [c1efe30] "m"(b1eb400_c1efe30)
      : "memory");
}
#else
#error "D3DDevice_LoadVertexShader: clang naked draft required"
#endif


/* D3DDevice_LoadVertexShaderProgram (0x1eb460) — XBE naked draft (batch 328). */
#if defined(__clang__)
static void b1eb460_c1efe30_tgt(void) { return; }
static void (*const b1eb460_c1efe30)(void) = b1eb460_c1efe30_tgt;
static void b1eb460_c1eac20_tgt(void) { return; }
static void (*const b1eb460_c1eac20)(void) = b1eb460_c1eac20_tgt;

__attribute__((naked, noinline))
void D3DDevice_LoadVertexShaderProgram(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movzwl 0x2(%%eax), %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "shll $2, %%ebx\n\t"
      "testb $0x10, %%cl\n\t"
      "jne .LD3DDevice_LoadVertexShaderProgram_1\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x18(%%esp), %%edi\n\t"
      "addl $0x18c, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%ebp, %%edi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LD3DDevice_LoadVertexShaderProgram_1:\n\t"
      "leal 0x13(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1efe30]\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "addl $4, %%edx\n\t"
      "movl $0x41e9c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "pushl %%edx\n\t"
      "addl $8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eac20]\n\t"
      "movl %%eax, (%%ebp)\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efe30] "m"(b1eb460_c1efe30), [c1eac20] "m"(b1eb460_c1eac20)
      : "memory");
}
#else
#error "D3DDevice_LoadVertexShaderProgram: clang naked draft required"
#endif


/* D3DDevice_SelectVertexShader (0x1eb4d0) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b1eb4d0_c1efe10)(void) = XMETAL_StartPush;
static void b1eb4d0_c1e9db0_tgt(void) { return; }
static void (*const b1eb4d0_c1e9db0)(void) = b1eb4d0_c1e9db0_tgt;

__attribute__((naked, noinline))
void D3DDevice_SelectVertexShader(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "je .LD3DDevice_SelectVertexShader_1\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0x1(%%eax), %%edi\n\t"
      "orl $0x3a0, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, 0x470(%%esi)\n\t"
      "movl %%eax, 0x474(%%esi)\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "leal 0xc(%%eax), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl $0x81e94, (%%eax)\n\t"
      "movl $6, 0x4(%%eax)\n\t"
      "call *%[c1e9db0]\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%edi\n\t"
      ".LD3DDevice_SelectVertexShader_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl $0x41ea0, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1eb4d0_c1efe10), [c1e9db0] "m"(b1eb4d0_c1e9db0)
      : "memory");
}
#else
#error "D3DDevice_SelectVertexShader: clang naked draft required"
#endif


/* D3DDevice_GetVertexShaderSize (0x1eb540) — XBE naked draft (batch 362). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShaderSize(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_GetVertexShaderSize_1\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl 0xf(%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LD3DDevice_GetVertexShaderSize_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShaderSize: clang naked draft required"
#endif


/* D3DDevice_GetVertexShaderType (0x1eb560) — XBE naked draft (batch 332). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShaderType(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x3(%%eax), %%eax\n\t"
      "testb $8, %%al\n\t"
      "je .LD3DDevice_GetVertexShaderType_1\n\t"
      "movl $3, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderType_2\n\t"
      ".LD3DDevice_GetVertexShaderType_1:\n\t"
      "testb $1, %%al\n\t"
      "movl $0, %%eax\n\t"
      "setne %%al\n\t"
      "incl %%eax\n\t"
      ".LD3DDevice_GetVertexShaderType_2:\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_GetVertexShaderType_3\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LD3DDevice_GetVertexShaderType_3:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShaderType: clang naked draft required"
#endif


/* D3DDevice_SetShaderConstantMode (0x1eb590) — XBE naked draft (batch 315). */
#if defined(__clang__)
static void (*const b1eb590_c1efe10)(void) = XMETAL_StartPush;
static void b1eb590_c1ef590_tgt(void) { return; }
static void (*const b1eb590_c1ef590)(void) = b1eb590_c1ef590_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetShaderConstantMode(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testb $0x10, %%al\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "je .LD3DDevice_SetShaderConstantMode_1\n\t"
      "orl $0x200, %%ecx\n\t"
      "jmp .LD3DDevice_SetShaderConstantMode_2\n\t"
      ".LD3DDevice_SetShaderConstantMode_1:\n\t"
      "andl $0xfffffdff, %%ecx\n\t"
      ".LD3DDevice_SetShaderConstantMode_2:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movl %%eax, 0x2140(%%ebp)\n\t"
      "jne .LD3DDevice_SetShaderConstantMode_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "orl $0x26, %%edi\n\t"
      "pushl %%ebp\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $0x1f9f48\n\t"
      "movl $0x41ea4, (%%ebx)\n\t"
      "movl $0x3c, 0x4(%%ebx)\n\t"
      "movl $0x300b80, 0x8(%%ebx)\n\t"
      "leal 0xc(%%ebx), %%edi\n\t"
      "pushl $0x400840\n\t"
      "addl $0x3c, %%ebx\n\t"
      "movl $0xc, %%ecx\n\t"
      "movl $0x1f9f9c, %%esi\n\t"
      "pushl %%ebx\n\t"
      "rep movsl\n\t"
      "call *%[c1ef590]\n\t"
      "pushl $0x1f9f48\n\t"
      "pushl $0x400880\n\t"
      "leal 0x44(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ef590]\n\t"
      "pushl $0x1f9f48\n\t"
      "pushl $0x4008c0\n\t"
      "leal 0x88(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ef590]\n\t"
      "pushl $0x1f9f48\n\t"
      "pushl $0x400900\n\t"
      "leal 0xcc(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ef590]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x1009d0, 0x110(%%ebx)\n\t"
      "movl %%eax, 0x114(%%ebx)\n\t"
      "movl %%eax, 0x118(%%ebx)\n\t"
      "movl $0x3f800000, 0x11c(%%ebx)\n\t"
      "movl %%eax, 0x120(%%ebx)\n\t"
      "popl %%edi\n\t"
      "addl $0x124, %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, (%%ebp)\n\t"
      "popl %%ebx\n\t"
      ".LD3DDevice_SetShaderConstantMode_3:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1eb590_c1efe10), [c1ef590] "m"(b1eb590_c1ef590)
      : "memory");
}
#else
#error "D3DDevice_SetShaderConstantMode: clang naked draft required"
#endif


/* D3DDevice_DeleteVertexShader (0x1eb6d0) — XBE naked draft (batch 339). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_DeleteVertexShader(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl -0x1(%%eax), %%ecx\n\t"
      "decl %%eax\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jne .LD3DDevice_DeleteVertexShader_1\n\t"
      "movl %%eax, 0x4(%%esp)\n\t"
      ".byte 0xe9, 0x30, 0x55, 0xfe, 0xff\n\t"
      ".LD3DDevice_DeleteVertexShader_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_DeleteVertexShader: clang naked draft required"
#endif


/* 0x001eb8d0 */
void D3DDevice_SetVertexShaderConstant(int register_index, const void *data, uint32_t count)
{
  int eax = 0;

  /* relift: FUN_001efe30(0, 0); */
  /* cmp eax, 0x20 -> jle 0x1eb94e */
  /* cmp eax, 0x20 -> jg 0x1eb935 */

  (void)eax;
}

/* D3DDevice_GetVertexShaderDeclaration (0x1eb970) — XBE naked draft (batch 297). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShaderDeclaration(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movb 0x3(%%eax), %%cl\n\t"
      "subl $0x10, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_1\n\t"
      "movl 0x1c(%%esp), %%ecx\n\t"
      "movl $0, (%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_2:\n\t"
      "movl 0x18(%%esp), %%ebp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl $0xffffffff, 0x18(%%esp)\n\t"
      "movl %%ebx, 0x14(%%esp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_4:\n\t"
      "movl 0x24(%%esp), %%ecx\n\t"
      "movl $0xffffffff, 0x10(%%esp)\n\t"
      "movl $0x13, %%edi\n\t"
      "addl $0x15b, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_5:\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "cmpl %%esi, -0x4(%%ecx)\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_6\n\t"
      "movl (%%ecx), %%esi\n\t"
      "cmpl 0x10(%%esp), %%esi\n\t"
      "jae .LD3DDevice_GetVertexShaderDeclaration_6\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jb .LD3DDevice_GetVertexShaderDeclaration_6\n\t"
      "cmpb $0, 0x8(%%ecx)\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_6\n\t"
      "cmpl $2, 0x4(%%ecx)\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_6\n\t"
      "movl %%esi, 0x10(%%esp)\n\t"
      "movl %%edi, %%ebp\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_6:\n\t"
      "movl %%edi, %%esi\n\t"
      "decl %%edi\n\t"
      "subl $0x10, %%ecx\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_5\n\t"
      "cmpl $-1, 0x10(%%esp)\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_15\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "cmpl 0x18(%%esp), %%ecx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_8\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%ecx, 0x18(%%esp)\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_7\n\t"
      "orl $0x20000000, %%ecx\n\t"
      "movl %%ecx, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_7:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_8:\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "movl %%edi, %%esi\n\t"
      "subl %%eax, %%esi\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_12\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_9:\n\t"
      "cmpl $0xf, %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "jb .LD3DDevice_GetVertexShaderDeclaration_10\n\t"
      "movl $0xf, %%ecx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_10:\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_11\n\t"
      "movl %%ecx, %%eax\n\t"
      "orl $0x5800, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_11:\n\t"
      "incl %%ebx\n\t"
      "subl %%ecx, %%esi\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_9\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_12:\n\t"
      "movl 0x24(%%esp), %%eax\n\t"
      "leal 0x3(%%ebp), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl -0x1(%%ecx,%%eax,1), %%ecx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_14\n\t"
      "cmpl $0x10, %%ebp\n\t"
      "movl %%ebp, %%eax\n\t"
      "jb .LD3DDevice_GetVertexShaderDeclaration_13\n\t"
      "leal -0x7(%%ebp), %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_13:\n\t"
      "movl %%ecx, %%esi\n\t"
      "orl $0x4000, %%esi\n\t"
      "shll $0x10, %%esi\n\t"
      "orl %%eax, %%esi\n\t"
      "movl %%esi, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_14:\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "andl $0xf, %%eax\n\t"
      "movzbl 0x1f9f88(%%eax), %%eax\n\t"
      "andl $0xf, %%ecx\n\t"
      "movzbl 0x1f9f90(%%ecx), %%ecx\n\t"
      "imull %%ecx, %%eax\n\t"
      "incl %%ebx\n\t"
      "addl %%edi, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_4\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_15:\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $0x10, %%eax\n\t"
      "movl %%eax, 0x14(%%esp)\n\t"
      "jb .LD3DDevice_GetVertexShaderDeclaration_3\n\t"
      "movl 0x24(%%esp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $2, %%esi\n\t"
      "addl $0x33, %%edi\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_16:\n\t"
      "movb (%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_17\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_19\n\t"
      "movl %%ecx, %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_18\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_17:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_20\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_19\n\t"
      "movzbl 0x1(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_18:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_19:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_20:\n\t"
      "movb 0x10(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_21\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_23\n\t"
      "leal -0x1(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_22\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_21:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_24\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_23\n\t"
      "movzbl 0x11(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal -0x1(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_22:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_23:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_24:\n\t"
      "movb 0x20(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_25\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_27\n\t"
      "movl %%esi, %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_26\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_25:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_28\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_27\n\t"
      "movzbl 0x21(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "orl %%esi, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_26:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_27:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_28:\n\t"
      "movb 0x30(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_29\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_31\n\t"
      "leal 0x1(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_30\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_29:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_32\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_31\n\t"
      "movzbl 0x31(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x1(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_30:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_31:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_32:\n\t"
      "movb 0x40(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_33\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_35\n\t"
      "leal 0x2(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_34\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_33:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_36\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_35\n\t"
      "movzbl 0x41(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x2(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_34:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_35:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_36:\n\t"
      "movb 0x50(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_37\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_39\n\t"
      "leal 0x3(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_38\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_37:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_40\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_39\n\t"
      "movzbl 0x51(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x3(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_38:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_39:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_40:\n\t"
      "movb 0x60(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_41\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_43\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_42\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_41:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_44\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_43\n\t"
      "movzbl 0x61(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x4(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_42:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_43:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_44:\n\t"
      "movb 0x70(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_45\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_47\n\t"
      "leal 0x5(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_46\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_45:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_48\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_47\n\t"
      "movzbl 0x71(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x5(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_46:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_47:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_48:\n\t"
      "movb 0x80(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_49\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_51\n\t"
      "leal 0x6(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_50\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_49:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_52\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_51\n\t"
      "movzbl 0x81(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x6(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_50:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_51:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_52:\n\t"
      "movb 0x90(%%edi), %%al\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_53\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_55\n\t"
      "leal 0x7(%%esi), %%eax\n\t"
      "orl $0x70000000, %%eax\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_54\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_53:\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_56\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_55\n\t"
      "movzbl 0x91(%%edi), %%eax\n\t"
      "orl $0x600, %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "leal 0x7(%%esi), %%ebp\n\t"
      "orl %%ebp, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_54:\n\t"
      "movl %%eax, (%%edx,%%ebx,4)\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_55:\n\t"
      "incl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_56:\n\t"
      "addl $0xa, %%esi\n\t"
      "addl $0xa, %%ecx\n\t"
      "addl $0xa0, %%edi\n\t"
      "cmpl $0x16, %%esi\n\t"
      "jb .LD3DDevice_GetVertexShaderDeclaration_16\n\t"
      "movl 0x24(%%esp), %%eax\n\t"
      "addl $0x167, %%eax\n\t"
      "movl %%ecx, 0x18(%%esp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_61\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_57:\n\t"
      "movl %%ecx, %%ebp\n\t"
      "shrl $0x12, %%ebp\n\t"
      "addl $4, %%eax\n\t"
      "cmpl $1, %%ebp\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_58\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%esp)\n\t"
      "jmp .LD3DDevice_GetVertexShaderDeclaration_60\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_58:\n\t"
      "andl $0xffff, %%ecx\n\t"
      "cmpl $0xb80, %%ecx\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_60\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LD3DDevice_GetVertexShaderDeclaration_59\n\t"
      "movl 0x1c(%%esp), %%esi\n\t"
      "movl %%ebp, %%ecx\n\t"
      "andl $0xfffffffc, %%ecx\n\t"
      "orl $0xffffff00, %%ecx\n\t"
      "shll $0x17, %%ecx\n\t"
      "orl %%esi, %%ecx\n\t"
      "movl %%ecx, (%%edx,%%ebx,4)\n\t"
      "movl %%ebp, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0x4(%%edx,%%ebx,4), %%edi\n\t"
      "rep movsl\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_59:\n\t"
      "leal 0x1(%%ebx,%%ebp,1), %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_60:\n\t"
      "movl (%%eax,%%ebp,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal (%%eax,%%ebp,4), %%eax\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_57\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_61:\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_62\n\t"
      "movl 0x2c(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x4(,%%ebx,4), %%ebx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "ja .LD3DDevice_GetVertexShaderDeclaration_63\n\t"
      "movl 0x28(%%esp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LD3DDevice_GetVertexShaderDeclaration_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_62:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl $0xffffffff, (%%edx,%%ebx,4)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      ".LD3DDevice_GetVertexShaderDeclaration_63:\n\t"
      "movl 0x28(%%esp), %%eax\n\t"
      "popl %%edi\n\t"
      "negl %%eax\n\t"
      "popl %%esi\n\t"
      "sbbl %%eax, %%eax\n\t"
      "popl %%ebp\n\t"
      "andl $0x88760867, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShaderDeclaration: clang naked draft required"
#endif


/* D3DDevice_GetVertexShaderFunction (0x1ebda0) — XBE naked draft (batch 313). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetVertexShaderFunction(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "testb $4, 0x3(%%esi)\n\t"
      "jne .LD3DDevice_GetVertexShaderFunction_1\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl $0, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_GetVertexShaderFunction_1:\n\t"
      "movl 0xf(%%esi), %%edx\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%edi\n\t"
      "movl (%%ecx), %%edi\n\t"
      "leal 0x4(%%edx), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jbe .LD3DDevice_GetVertexShaderFunction_2\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "andl $0x88760867, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3DDevice_GetVertexShaderFunction_2:\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_GetVertexShaderFunction_7\n\t"
      "movl 0x3(%%esi), %%eax\n\t"
      "testb $8, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "leal 0x16b(%%esi), %%ebx\n\t"
      "movl $0x2078, %%edi\n\t"
      "je .LD3DDevice_GetVertexShaderFunction_3\n\t"
      "movl $0x7378, %%edi\n\t"
      "jmp .LD3DDevice_GetVertexShaderFunction_4\n\t"
      ".LD3DDevice_GetVertexShaderFunction_3:\n\t"
      "testb $1, %%al\n\t"
      "je .LD3DDevice_GetVertexShaderFunction_4\n\t"
      "movl $0x7778, %%edi\n\t"
      ".LD3DDevice_GetVertexShaderFunction_4:\n\t"
      "movl 0xf(%%esi), %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "leal 0x4(%%ecx), %%edi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%edi, 0x1c(%%esp)\n\t"
      ".LD3DDevice_GetVertexShaderFunction_5:\n\t"
      "cmpl $0x80, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "jb .LD3DDevice_GetVertexShaderFunction_6\n\t"
      "movl $0x80, %%eax\n\t"
      ".LD3DDevice_GetVertexShaderFunction_6:\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%ecx, %%ebp\n\t"
      "shrl $2, %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "rep movsl\n\t"
      "movl %%ebp, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "movl 0x1c(%%esp), %%edi\n\t"
      "addl %%eax, %%edi\n\t"
      "subl %%eax, %%edx\n\t"
      "movl %%edi, 0x1c(%%esp)\n\t"
      "leal 0x4(%%ebx,%%eax,1), %%ebx\n\t"
      "jne .LD3DDevice_GetVertexShaderFunction_5\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      ".LD3DDevice_GetVertexShaderFunction_7:\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetVertexShaderFunction: clang naked draft required"
#endif


/* D3DDevice_SetVertexShaderInput (0x1ebe60) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void b1ebe60_c1ed8b0_tgt(void) { return; }
static void (*const b1ebe60_c1ed8b0)(void) = b1ebe60_c1ed8b0_tgt;
static void __stdcall (*const b1ebe60_c1ed7d0)(void *resource) = (void *)D3D_DestroyResource;
static void (*const b1ebe60_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetVertexShaderInput(void)
{
  __asm__ volatile(
      "pushl %%ecx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "movl %%ebp, 0x4(%%esp)\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0xbfffffff, %%eax\n\t"
      "orl $0x380, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "popl %%ebp\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      ".LD3DDevice_SetVertexShaderInput_1:\n\t"
      "pushl %%ebx\n\t"
      "movl 0x18(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1c(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LD3DDevice_SetVertexShaderInput_3\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl %%edi, 0x1c(%%esp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LD3DDevice_SetVertexShaderInput_2:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ed8b0]\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x1c(%%esp)\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_2\n\t"
      ".LD3DDevice_SetVertexShaderInput_3:\n\t"
      "movl 0x724(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, 0x1c(%%esp)\n\t"
      "jbe .LD3DDevice_SetVertexShaderInput_6\n\t"
      "leal 0x728(%%ebp), %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LD3DDevice_SetVertexShaderInput_4:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0xfff80000, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "testl $0x78ffff, %%ecx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed7d0]\n\t"
      ".LD3DDevice_SetVertexShaderInput_5:\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "movl 0x724(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x1c(%%esp)\n\t"
      "jb .LD3DDevice_SetVertexShaderInput_4\n\t"
      ".LD3DDevice_SetVertexShaderInput_6:\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x720(%%ebp)\n\t"
      "leal (%%edi,%%edi,2), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0xfffffc7f, %%eax\n\t"
      "movl %%edi, 0x724(%%ebp)\n\t"
      "shrl $2, %%ecx\n\t"
      "orl $0x40000000, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%ebx, %%esi\n\t"
      "leal 0x728(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "pushl %%ebp\n\t"
      "rep movsb\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x1c(%%esp)\n\t"
      "movl $0x401720, (%%ecx)\n\t"
      "movl $0x401760, 0x44(%%ecx)\n\t"
      "addl $0x48, %%ecx\n\t"
      "movl $2, %%eax\n\t"
      "addl $0x97, %%edx\n\t"
      "nop\n\t"
      ".LD3DDevice_SetVertexShaderInput_7:\n\t"
      "movl 0x18(%%esp), %%esi\n\t"
      "testb $4, 0x3(%%esi)\n\t"
      "leal -0x70(%%edx), %%edi\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_8\n\t"
      "leal -0x2(%%eax), %%esi\n\t"
      "cmpl $9, %%esi\n\t"
      "jb .LD3DDevice_SetVertexShaderInput_8\n\t"
      "cmpl $0xc, %%esi\n\t"
      "ja .LD3DDevice_SetVertexShaderInput_8\n\t"
      "movl %%edx, %%edi\n\t"
      ".LD3DDevice_SetVertexShaderInput_8:\n\t"
      "movl (%%edi), %%esi\n\t"
      "leal (%%esi,%%esi,2), %%esi\n\t"
      "movl (%%ebx,%%esi,4), %%ebp\n\t"
      "movl 0x4(%%ebp), %%ebp\n\t"
      "addl 0x8(%%ebx,%%esi,4), %%ebp\n\t"
      "leal (%%ebx,%%esi,4), %%esi\n\t"
      "addl 0x4(%%edi), %%ebp\n\t"
      "movl %%ebp, -0x44(%%ecx)\n\t"
      "movl 0x4(%%esi), %%esi\n\t"
      "movl 0x8(%%edi), %%ebp\n\t"
      "shll $8, %%esi\n\t"
      "addl %%ebp, %%esi\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl 0x18(%%esp), %%esi\n\t"
      "testb $4, 0x3(%%esi)\n\t"
      "leal -0x60(%%edx), %%edi\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_9\n\t"
      "leal -0x1(%%eax), %%esi\n\t"
      "cmpl $9, %%esi\n\t"
      "jb .LD3DDevice_SetVertexShaderInput_9\n\t"
      "cmpl $0xc, %%esi\n\t"
      "ja .LD3DDevice_SetVertexShaderInput_9\n\t"
      "leal 0x10(%%edx), %%edi\n\t"
      ".LD3DDevice_SetVertexShaderInput_9:\n\t"
      "movl (%%edi), %%esi\n\t"
      "leal (%%esi,%%esi,2), %%esi\n\t"
      "movl (%%ebx,%%esi,4), %%ebp\n\t"
      "movl 0x4(%%ebp), %%ebp\n\t"
      "addl 0x8(%%ebx,%%esi,4), %%ebp\n\t"
      "leal (%%ebx,%%esi,4), %%esi\n\t"
      "addl 0x4(%%edi), %%ebp\n\t"
      "movl %%ebp, -0x40(%%ecx)\n\t"
      "movl 0x4(%%esi), %%esi\n\t"
      "movl 0x8(%%edi), %%ebp\n\t"
      "shll $8, %%esi\n\t"
      "addl %%ebp, %%esi\n\t"
      "movl %%esi, 0x4(%%ecx)\n\t"
      "movl 0x18(%%esp), %%esi\n\t"
      "testb $4, 0x3(%%esi)\n\t"
      "leal -0x50(%%edx), %%edi\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_10\n\t"
      "cmpl $9, %%eax\n\t"
      "jb .LD3DDevice_SetVertexShaderInput_10\n\t"
      "cmpl $0xc, %%eax\n\t"
      "ja .LD3DDevice_SetVertexShaderInput_10\n\t"
      "leal 0x20(%%edx), %%edi\n\t"
      ".LD3DDevice_SetVertexShaderInput_10:\n\t"
      "movl (%%edi), %%esi\n\t"
      "leal (%%esi,%%esi,2), %%esi\n\t"
      "movl (%%ebx,%%esi,4), %%ebp\n\t"
      "movl 0x4(%%ebp), %%ebp\n\t"
      "addl 0x8(%%ebx,%%esi,4), %%ebp\n\t"
      "leal (%%ebx,%%esi,4), %%esi\n\t"
      "addl 0x4(%%edi), %%ebp\n\t"
      "movl %%ebp, -0x3c(%%ecx)\n\t"
      "movl 0x4(%%esi), %%esi\n\t"
      "movl 0x8(%%edi), %%ebp\n\t"
      "shll $8, %%esi\n\t"
      "addl %%ebp, %%esi\n\t"
      "movl %%esi, 0x8(%%ecx)\n\t"
      "movl 0x18(%%esp), %%esi\n\t"
      "testb $4, 0x3(%%esi)\n\t"
      "leal -0x40(%%edx), %%edi\n\t"
      "jne .LD3DDevice_SetVertexShaderInput_11\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      "cmpl $9, %%esi\n\t"
      "jb .LD3DDevice_SetVertexShaderInput_11\n\t"
      "cmpl $0xc, %%esi\n\t"
      "ja .LD3DDevice_SetVertexShaderInput_11\n\t"
      "leal 0x30(%%edx), %%edi\n\t"
      ".LD3DDevice_SetVertexShaderInput_11:\n\t"
      "movl (%%edi), %%esi\n\t"
      "leal (%%esi,%%esi,2), %%esi\n\t"
      "movl (%%ebx,%%esi,4), %%ebp\n\t"
      "movl 0x4(%%ebp), %%ebp\n\t"
      "addl 0x8(%%ebx,%%esi,4), %%ebp\n\t"
      "leal (%%ebx,%%esi,4), %%esi\n\t"
      "addl 0x4(%%edi), %%ebp\n\t"
      "addl $4, %%eax\n\t"
      "movl %%ebp, -0x38(%%ecx)\n\t"
      "movl 0x4(%%esi), %%esi\n\t"
      "movl 0x8(%%edi), %%ebp\n\t"
      "shll $8, %%esi\n\t"
      "addl %%ebp, %%esi\n\t"
      "movl %%esi, 0xc(%%ecx)\n\t"
      "leal -0x2(%%eax), %%esi\n\t"
      "addl $0x10, %%ecx\n\t"
      "addl $0x40, %%edx\n\t"
      "cmpl $0x10, %%esi\n\t"
      "jb .LD3DDevice_SetVertexShaderInput_7\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0x88, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%ebp\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      :
      : [c1ed8b0] "m"(b1ebe60_c1ed8b0), [c1ed7d0] "m"(b1ebe60_c1ed7d0), [c1efe10] "m"(b1ebe60_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetVertexShaderInput: clang naked draft required"
#endif


/* D3DDevice_CreatePixelShader (0x1ec0b0) — XBE naked draft (batch 357). */
#if defined(__clang__)
static void *__stdcall (*const b1ec0b0_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;

__attribute__((naked, noinline))
void D3DDevice_CreatePixelShader(void)
{
  __asm__ volatile(
      "pushl $0xfc\n\t"
      "pushl $0\n\t"
      "call *%[c1d0bb9]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_CreatePixelShader_1\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "ret\n\t"
      ".LD3DDevice_CreatePixelShader_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0xc(%%eax), %%edi\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "movl $1, (%%eax)\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x3c, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1d0bb9] "m"(b1ec0b0_c1d0bb9)
      : "memory");
}
#else
#error "D3DDevice_CreatePixelShader: clang naked draft required"
#endif


/* D3DDevice_DeletePixelShader (0x1ec100) — XBE naked draft (batch 349). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_DeletePixelShader(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "decl (%%eax)\n\t"
      "jne .LD3DDevice_DeletePixelShader_1\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_DeletePixelShader_1\n\t"
      "movl %%eax, 0x4(%%esp)\n\t"
      ".byte 0xe9, 0xfe, 0x4a, 0xfe, 0xff\n\t"
      ".LD3DDevice_DeletePixelShader_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_DeletePixelShader: clang naked draft required"
#endif


/* D3DDevice_GetPixelShader (0x1ec160) — XBE naked draft (batch 351). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_GetPixelShader(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x414(%%eax), %%ecx\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_GetPixelShader: clang naked draft required"
#endif


/* D3DDevice_SetPixelShader (0x1ec5c0) — XBE naked draft (batch 312). */
#if defined(__clang__)
static void (*const b1ec5c0_c1e97b0)(void) = D3DDevice_SetRenderState_TextureFactor;
static void (*const b1ec5c0_c1efe10)(void) = XMETAL_StartPush;
static void b1ec5c0_c1e9d40_tgt(void) { return; }
static void (*const b1ec5c0_c1e9d40)(void) = b1ec5c0_c1e9d40_tgt;

__attribute__((naked, noinline))
void D3DDevice_SetPixelShader(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x1fe6a0, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x414(%%ebx), %%esi\n\t"
      "movl %%eax, 0x414(%%ebx)\n\t"
      "jne .LD3DDevice_SetPixelShader_2\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "movl 0x418(%%ebx), %%ecx\n\t"
      "orl $0x408, %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movl %%edx, %%eax\n\t"
      "je .LD3DDevice_SetPixelShader_1\n\t"
      "orl $0x40, %%eax\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      ".LD3DDevice_SetPixelShader_1:\n\t"
      "movl 0x1fb898, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e97b0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1e9d40]\n\t"
      "movl $0x41e78, (%%eax)\n\t"
      "movl $0x210000, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LD3DDevice_SetPixelShader_2:\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0x24(%%ecx), %%edx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%edi\n\t"
      "orl 0x20(%%ecx), %%edx\n\t"
      "movl 0x8(%%ebx), %%edi\n\t"
      "movl %%edx, 0x418(%%ebx)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0xec(%%ecx), %%edx\n\t"
      "andl $0x100, %%edx\n\t"
      "movl %%edx, 0x41c(%%ebx)\n\t"
      "movl 0x8(%%eax), %%ebp\n\t"
      "movl 0xd8(%%ebp), %%eax\n\t"
      "orl $0x400, %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x420(%%ebx)\n\t"
      "movl %%edi, 0x8(%%ebx)\n\t"
      "call *%[c1efe10]\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LD3DDevice_SetPixelShader_3\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1e9d40]\n\t"
      ".LD3DDevice_SetPixelShader_3:\n\t"
      "movl $0x200260, (%%eax)\n\t"
      "leal 0x4(%%eax), %%edi\n\t"
      "movl $8, %%ecx\n\t"
      "movl %%ebp, %%esi\n\t"
      "rep movsl\n\t"
      "movl $0x800a60, 0x24(%%eax)\n\t"
      "leal 0x28(%%ebp), %%esi\n\t"
      "leal 0x28(%%eax), %%edi\n\t"
      "movl $0x20, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0xa8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xac(%%eax)\n\t"
      "movl $0x417f8, 0xa8(%%eax)\n\t"
      "movl $0x81e20, 0xb0(%%eax)\n\t"
      "movl 0xac(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xb4(%%eax)\n\t"
      "movl 0xb0(%%ebp), %%edx\n\t"
      "movl %%edx, 0xb8(%%eax)\n\t"
      "movl $0x241e40, 0xbc(%%eax)\n\t"
      "leal 0xb4(%%ebp), %%esi\n\t"
      "leal 0xc0(%%eax), %%edi\n\t"
      "movl $9, %%ecx\n\t"
      "rep movsl\n\t"
      "movl $0x81e74, 0xe4(%%eax)\n\t"
      "movl 0xdc(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xe8(%%eax)\n\t"
      "movl 0xe0(%%ebp), %%edx\n\t"
      "movl %%edx, 0xec(%%eax)\n\t"
      "movl 0x418(%%ebx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LD3DDevice_SetPixelShader_4\n\t"
      "movl $0x80288, 0xf0(%%eax)\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xf4(%%eax)\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl %%edx, 0xf8(%%eax)\n\t"
      "addl $0xfc, %%eax\n\t"
      "jmp .LD3DDevice_SetPixelShader_5\n\t"
      ".LD3DDevice_SetPixelShader_4:\n\t"
      "addl $0xf0, %%eax\n\t"
      ".LD3DDevice_SetPixelShader_5:\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "testb $0x10, 0xc(%%ebx)\n\t"
      "jne .LD3DDevice_SetPixelShader_6\n\t"
      "movl $0x39, %%ecx\n\t"
      "movl %%ebp, %%esi\n\t"
      "movl $0x1fb698, %%edi\n\t"
      "rep movsl\n\t"
      "movl 0xd8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x1fb868\n\t"
      ".LD3DDevice_SetPixelShader_6:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1e97b0] "m"(b1ec5c0_c1e97b0), [c1efe10] "m"(b1ec5c0_c1efe10), [c1e9d40] "m"(b1ec5c0_c1e9d40)
      : "memory");
}
#else
#error "D3DDevice_SetPixelShader: clang naked draft required"
#endif


/* D3DDevice_SetPixelShaderConstant (0x1ec780) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void b1ec780_c1f3c30_tgt(void) { return; }
static void (*const b1ec780_c1f3c30)(void) = b1ec780_c1f3c30_tgt;
static void (*const b1ec780_c1e93a0)(void) = D3DDevice_SetRenderStateNotInline;
static void (*const b1ec780_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetPixelShaderConstant(void)
{
  __asm__ volatile(
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x414(%%esi), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0x20(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, 0x8(%%esp)\n\t"
      "movl %%ecx, 0x10(%%esp)\n\t"
      "jbe .LD3DDevice_SetPixelShaderConstant_19\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x20(%%esp), %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl 0x28(%%esp), %%edi\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, 0x10(%%esp)\n\t"
      "movl %%eax, 0x18(%%esp)\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_2\n\t"
      ".LD3DDevice_SetPixelShaderConstant_1:\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_2\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LD3DDevice_SetPixelShaderConstant_2:\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x24(%%esp)\n\t"
      "flds 0x24(%%esp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_3\n\t"
      "movl $0x3f800000, 0x24(%%esp)\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_4\n\t"
      ".LD3DDevice_SetPixelShaderConstant_3:\n\t"
      "flds 0x24(%%esp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LD3DDevice_SetPixelShaderConstant_4\n\t"
      "movl $0, 0x24(%%esp)\n\t"
      ".LD3DDevice_SetPixelShaderConstant_4:\n\t"
      "flds -0x4(%%edi)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_6\n\t"
      ".LD3DDevice_SetPixelShaderConstant_5:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LD3DDevice_SetPixelShaderConstant_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LD3DDevice_SetPixelShaderConstant_6:\n\t"
      "fmuls 0x2602c8\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "flds (%%edi)\n\t"
      "movb %%al, 0x2c(%%esp)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_8\n\t"
      ".LD3DDevice_SetPixelShaderConstant_7:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LD3DDevice_SetPixelShaderConstant_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LD3DDevice_SetPixelShaderConstant_8:\n\t"
      "fmuls 0x2602c8\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "flds 0x4(%%edi)\n\t"
      "movb %%al, 0x28(%%esp)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_9\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_10\n\t"
      ".LD3DDevice_SetPixelShaderConstant_9:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LD3DDevice_SetPixelShaderConstant_10\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LD3DDevice_SetPixelShaderConstant_10:\n\t"
      "fmuls 0x2602c8\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "flds 0x24(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2602c8\n\t"
      "movb %%al, %%bl\n\t"
      "fadds 0x253398\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "movzbl 0x28(%%esp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb %%al, %%ch\n\t"
      "movzbl %%bl, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "movb 0x2c(%%esp), %%cl\n\t"
      "shll $8, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "movl %%eax, 0x424(%%esi,%%ebp,4)\n\t"
      "movl %%eax, 0x2c(%%esp)\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LD3DDevice_SetPixelShaderConstant_11:\n\t"
      "movl 0x1c(%%esp), %%ebx\n\t"
      "movl 0xe4(%%ebx), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "shrl %%cl, %%edx\n\t"
      "andl $0xf, %%edx\n\t"
      "cmpl %%ebp, %%edx\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_12\n\t"
      "pushl %%eax\n\t"
      "leal 0xa(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e93a0]\n\t"
      "movl 0x2c(%%esp), %%eax\n\t"
      ".LD3DDevice_SetPixelShaderConstant_12:\n\t"
      "addl $4, %%esi\n\t"
      "incl %%edi\n\t"
      "cmpl $0x20, %%esi\n\t"
      "jb .LD3DDevice_SetPixelShaderConstant_11\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LD3DDevice_SetPixelShaderConstant_13:\n\t"
      "movl 0xe8(%%ebx), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "shrl %%cl, %%edx\n\t"
      "andl $0xf, %%edx\n\t"
      "cmpl %%ebp, %%edx\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_14\n\t"
      "pushl %%eax\n\t"
      "leal 0x12(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e93a0]\n\t"
      "movl 0x2c(%%esp), %%eax\n\t"
      ".LD3DDevice_SetPixelShaderConstant_14:\n\t"
      "addl $4, %%esi\n\t"
      "incl %%edi\n\t"
      "cmpl $0x20, %%esi\n\t"
      "jb .LD3DDevice_SetPixelShaderConstant_13\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LD3DDevice_SetPixelShaderConstant_15:\n\t"
      "movl 0xec(%%ebx), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "shrl %%cl, %%edx\n\t"
      "andl $0xf, %%edx\n\t"
      "cmpl %%ebp, %%edx\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_16\n\t"
      "pushl %%eax\n\t"
      "leal 0x2b(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e93a0]\n\t"
      "movl 0x2c(%%esp), %%eax\n\t"
      ".LD3DDevice_SetPixelShaderConstant_16:\n\t"
      "addl $4, %%esi\n\t"
      "incl %%edi\n\t"
      "cmpl $8, %%esi\n\t"
      "jb .LD3DDevice_SetPixelShaderConstant_15\n\t"
      "testl %%ebp, %%ebp\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_17\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "leal 0x4(%%eax), %%ecx\n\t"
      "movl $0xc181c, (%%eax)\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl -0x4(%%ecx), %%edi\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl (%%ecx), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "addl $0x10, %%eax\n\t"
      "movl %%edi, 0x8(%%edx)\n\t"
      "movl %%eax, (%%esi)\n\t"
      "jmp .LD3DDevice_SetPixelShaderConstant_18\n\t"
      ".LD3DDevice_SetPixelShaderConstant_17:\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      ".LD3DDevice_SetPixelShaderConstant_18:\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "addl $0x10, %%ecx\n\t"
      "incl %%ebp\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, 0x10(%%esp)\n\t"
      "movl %%eax, 0x18(%%esp)\n\t"
      "jne .LD3DDevice_SetPixelShaderConstant_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      ".LD3DDevice_SetPixelShaderConstant_19:\n\t"
      "popl %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f3c30] "m"(b1ec780_c1f3c30), [c1e93a0] "m"(b1ec780_c1e93a0), [c1efe10] "m"(b1ec780_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetPixelShaderConstant: clang naked draft required"
#endif


/* D3DDevice_DrawVerticesUP (0x1ecc70) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b1ecc70_c1f1eb0)(void) = CDevice_SetStateUP;
static void (*const b1ecc70_c1efe10)(void) = XMETAL_StartPush;
static void b1ecc70_c1efe30_tgt(void) { return; }
static void (*const b1ecc70_c1efe30)(void) = b1ecc70_c1efe30_tgt;
static void (*const b1ecc70_c1ef9e0)(void) = D3D_SetFence;

__attribute__((naked, noinline))
void D3DDevice_DrawVerticesUP(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c1f1eb0]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl $0x417fc, (%%eax)\n\t"
      "movl 0x7ec(%%edi), %%edx\n\t"
      "movl 0x874(%%edi), %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "addl %%ebx, %%edx\n\t"
      "orl $0x800, %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0x7f0(%%edi), %%edx\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "leal 0x7f4(%%edi), %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x4(%%eax,%%ecx,8)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "cmpl $0x10, %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "ja .LD3DDevice_DrawVerticesUP_1\n\t"
      "movl $0x10, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jmp .LD3DDevice_DrawVerticesUP_3\n\t"
      ".LD3DDevice_DrawVerticesUP_1:\n\t"
      "movl $0x7ff, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl 0x7e8(%%edi)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      ".LD3DDevice_DrawVerticesUP_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "nop\n\t"
      ".LD3DDevice_DrawVerticesUP_3:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LD3DDevice_DrawVerticesUP_4\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LD3DDevice_DrawVerticesUP_4:\n\t"
      "movl 0x7e8(%%edi), %%esi\n\t"
      "imull %%eax, %%esi\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "leal 0x3(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "call *%[c1efe30]\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $0x12, %%esi\n\t"
      "addl $4, %%eax\n\t"
      "addl $0x40001818, %%esi\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LD3DDevice_DrawVerticesUP_5:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LD3DDevice_DrawVerticesUP_6:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "rep movsl\n\t"
      "addl 0x4(%%ebx), %%esi\n\t"
      "addl $8, %%ebx\n\t"
      "decl %%eax\n\t"
      "jne .LD3DDevice_DrawVerticesUP_6\n\t"
      "decl %%edx\n\t"
      "jne .LD3DDevice_DrawVerticesUP_5\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_DrawVerticesUP_7\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "jmp .LD3DDevice_DrawVerticesUP_2\n\t"
      ".LD3DDevice_DrawVerticesUP_7:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl $0x417fc, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LD3DDevice_DrawVerticesUP_8\n\t"
      "pushl $1\n\t"
      "call *%[c1ef9e0]\n\t"
      ".LD3DDevice_DrawVerticesUP_8:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "andl $0xffffe7ff, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1f1eb0] "m"(b1ecc70_c1f1eb0), [c1efe10] "m"(b1ecc70_c1efe10), [c1efe30] "m"(b1ecc70_c1efe30), [c1ef9e0] "m"(b1ecc70_c1ef9e0)
      : "memory");
}
#else
#error "D3DDevice_DrawVerticesUP: clang naked draft required"
#endif


/* D3DDevice_DrawIndexedVerticesUP (0x1ecdb0) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b1ecdb0_c1f1eb0)(void) = CDevice_SetStateUP;
static void (*const b1ecdb0_c1efe10)(void) = XMETAL_StartPush;
static void b1ecdb0_c1efe30_tgt(void) { return; }
static void (*const b1ecdb0_c1efe30)(void) = b1ecdb0_c1efe30_tgt;
static void (*const b1ecdb0_c1ef9e0)(void) = D3D_SetFence;

__attribute__((naked, noinline))
void D3DDevice_DrawIndexedVerticesUP(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[c1f1eb0]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl $0x417fc, (%%eax)\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x7ec(%%edi), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl 0x874(%%edi), %%ecx\n\t"
      "orl $0x800, %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "cmpl $0x10, %%ecx\n\t"
      "movl %%edx, 0xc(%%edi)\n\t"
      "leal 0x7f4(%%edi), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "ja .LD3DDevice_DrawIndexedVerticesUP_1\n\t"
      "movl $0x10, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LD3DDevice_DrawIndexedVerticesUP_3\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_1:\n\t"
      "movl $0x7ff, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl 0x7e8(%%edi)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_3:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LD3DDevice_DrawIndexedVerticesUP_4\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_4:\n\t"
      "movl 0x7e8(%%edi), %%esi\n\t"
      "imull %%eax, %%esi\n\t"
      "leal 0x3(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "call *%[c1efe30]\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $0x12, %%esi\n\t"
      "addl $4, %%eax\n\t"
      "addl $0x40001818, %%esi\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_5:\n\t"
      "movzwl (%%edx), %%esi\n\t"
      "addl $2, %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "imull 0x18(%%ebp), %%esi\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "addl -0xc(%%ebp), %%esi\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_6:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "rep movsl\n\t"
      "addl 0x4(%%ebx), %%esi\n\t"
      "addl $8, %%ebx\n\t"
      "decl %%eax\n\t"
      "jne .LD3DDevice_DrawIndexedVerticesUP_6\n\t"
      "decl 0x14(%%ebp)\n\t"
      "jne .LD3DDevice_DrawIndexedVerticesUP_5\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "je .LD3DDevice_DrawIndexedVerticesUP_7\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "jmp .LD3DDevice_DrawIndexedVerticesUP_2\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_7:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl $0x417fc, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LD3DDevice_DrawIndexedVerticesUP_8\n\t"
      "pushl $1\n\t"
      "call *%[c1ef9e0]\n\t"
      ".LD3DDevice_DrawIndexedVerticesUP_8:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "andl $0xffffe7ff, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1f1eb0] "m"(b1ecdb0_c1f1eb0), [c1efe10] "m"(b1ecdb0_c1efe10), [c1efe30] "m"(b1ecdb0_c1efe30), [c1ef9e0] "m"(b1ecdb0_c1ef9e0)
      : "memory");
}
#else
#error "D3DDevice_DrawIndexedVerticesUP: clang naked draft required"
#endif


/* 0x001ecef0 */
void D3DDevice_DrawVertices(uint32_t primitive_type, uint32_t start_vertex, uint32_t vertex_count)
{
  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0, 0); */
}

/* D3DDevice_DrawIndexedVertices (0x1ecf90) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b1ecf90_c1f1bc0)(void) = CDevice_SetStateVB;
static void b1ecf90_c1efe30_tgt(void) { return; }
static void (*const b1ecf90_c1efe30)(void) = b1ecf90_c1efe30_tgt;
static void (*const b1ecf90_c1ef9e0)(void) = D3D_SetFence;

__attribute__((naked, noinline))
void D3DDevice_DrawIndexedVertices(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0x478(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c1f1bc0]\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl $0x209\n\t"
      "orl $0x800, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[c1efe30]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "addl $8, %%ebx\n\t"
      "movl $0x417fc, -0x8(%%ebx)\n\t"
      "movl %%ebx, %%eax\n\t"
      "negl %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "andl $7, %%eax\n\t"
      "leal 0x3e(%%eax,%%eax,1), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jb .LD3DDevice_DrawIndexedVertices_6\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_DrawIndexedVertices_1\n\t"
      "decl %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $0x12, %%ecx\n\t"
      "addl $0x40001800, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $4, %%edi\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal (,%%eax,4), %%ecx\n\t"
      "addl %%ecx, %%esi\n\t"
      "negl %%eax\n\t"
      "leal 0x4(%%ebx,%%ecx,1), %%ebx\n\t"
      "leal (%%edx,%%eax,2), %%edx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      ".LD3DDevice_DrawIndexedVertices_1:\n\t"
      "movl $0x804021, %%eax\n\t"
      "mull %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "shrl $1, %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "shrl $9, %%ecx\n\t"
      "imull $0x3fe, %%ecx, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "cmpl $0x3e, %%edx\n\t"
      "jb .LD3DDevice_DrawIndexedVertices_2\n\t"
      "shrl $1, %%edx\n\t"
      "incl %%edx\n\t"
      "andl $0xfffffff0, %%edx\n\t"
      "decl %%edx\n\t"
      "jmp .LD3DDevice_DrawIndexedVertices_3\n\t"
      ".LD3DDevice_DrawIndexedVertices_2:\n\t"
      "movl $0x1ff, %%edx\n\t"
      ".LD3DDevice_DrawIndexedVertices_3:\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LD3DDevice_DrawIndexedVertices_4:\n\t"
      "movl %%edx, %%eax\n\t"
      "shll $0x12, %%eax\n\t"
      "addl $0x40001800, %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "subl $0xf, %%ecx\n\t"
      "shrl $4, %%ecx\n\t"
      ".byte 0x0f, 0x18, 0x46, 0x3c\n\t"
      ".byte 0x0f, 0x18, 0x46, 0x5c\n\t"
      "movl (%%esi), %%eax\n\t"
      ".byte 0x0f, 0x6f, 0x4e, 0x04\n\t"
      ".byte 0x0f, 0x6f, 0x56, 0x0c\n\t"
      ".byte 0x0f, 0x6f, 0x5e, 0x14\n\t"
      ".byte 0x0f, 0x6f, 0x66, 0x1c\n\t"
      ".byte 0x0f, 0x6f, 0x6e, 0x24\n\t"
      ".byte 0x0f, 0x6f, 0x76, 0x2c\n\t"
      ".byte 0x0f, 0x6f, 0x7e, 0x34\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      ".byte 0x0f, 0xe7, 0x4f, 0x08\n\t"
      ".byte 0x0f, 0xe7, 0x57, 0x10\n\t"
      ".byte 0x0f, 0xe7, 0x5f, 0x18\n\t"
      ".byte 0x0f, 0xe7, 0x67, 0x20\n\t"
      ".byte 0x0f, 0xe7, 0x6f, 0x28\n\t"
      ".byte 0x0f, 0xe7, 0x77, 0x30\n\t"
      ".byte 0x0f, 0xe7, 0x7f, 0x38\n\t"
      "addl $0x3c, %%esi\n\t"
      "addl $0x40, %%edi\n\t"
      "jmp .LD3DDevice_DrawIndexedVertices_5\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LD3DDevice_DrawIndexedVertices_5:\n\t"
      ".byte 0x0f, 0x18, 0x46, 0x40\n\t"
      ".byte 0x0f, 0x18, 0x46, 0x60\n\t"
      ".byte 0x0f, 0x6f, 0x06\n\t"
      ".byte 0x0f, 0x6f, 0x4e, 0x08\n\t"
      ".byte 0x0f, 0x6f, 0x56, 0x10\n\t"
      ".byte 0x0f, 0x6f, 0x5e, 0x18\n\t"
      ".byte 0x0f, 0x6f, 0x66, 0x20\n\t"
      ".byte 0x0f, 0x6f, 0x6e, 0x28\n\t"
      ".byte 0x0f, 0x6f, 0x76, 0x30\n\t"
      ".byte 0x0f, 0x6f, 0x7e, 0x38\n\t"
      "nop\n\t"
      "nop\n\t"
      ".byte 0x0f, 0xe7, 0x07\n\t"
      ".byte 0x0f, 0xe7, 0x4f, 0x08\n\t"
      ".byte 0x0f, 0xe7, 0x57, 0x10\n\t"
      ".byte 0x0f, 0xe7, 0x5f, 0x18\n\t"
      ".byte 0x0f, 0xe7, 0x67, 0x20\n\t"
      ".byte 0x0f, 0xe7, 0x6f, 0x28\n\t"
      ".byte 0x0f, 0xe7, 0x77, 0x30\n\t"
      ".byte 0x0f, 0xe7, 0x7f, 0x38\n\t"
      "addl $0x40, %%esi\n\t"
      "addl $0x40, %%edi\n\t"
      "decl %%ecx\n\t"
      "jne .LD3DDevice_DrawIndexedVertices_5\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "leal (,%%edx,4), %%eax\n\t"
      "negl %%edx\n\t"
      "leal (%%ecx,%%edx,2), %%edx\n\t"
      "addl %%eax, %%edi\n\t"
      "leal 0x4(%%eax,%%ebx,1), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x204\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "call *%[c1efe30]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $0x3fe, %%eax\n\t"
      "movl $0x1ff, %%edx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jae .LD3DDevice_DrawIndexedVertices_4\n\t"
      ".byte 0x0f, 0x77\n\t"
      "movl %%eax, %%edx\n\t"
      ".LD3DDevice_DrawIndexedVertices_6:\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $1, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $0x12, %%ecx\n\t"
      "addl $0x40001800, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $4, %%edi\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "shll $2, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "testb $1, %%dl\n\t"
      "leal 0x4(%%ebx,%%eax,1), %%ebx\n\t"
      "je .LD3DDevice_DrawIndexedVertices_7\n\t"
      "movzwl (%%ecx), %%eax\n\t"
      "movl $0x41808, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "addl $8, %%ebx\n\t"
      ".LD3DDevice_DrawIndexedVertices_7:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl $0x417fc, (%%ebx)\n\t"
      "movl $0, 0x4(%%ebx)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $8, %%ebx\n\t"
      "testb $0x10, %%ah\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "je .LD3DDevice_DrawIndexedVertices_8\n\t"
      "pushl $1\n\t"
      "call *%[c1ef9e0]\n\t"
      ".LD3DDevice_DrawIndexedVertices_8:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "andl $0xffffe7ff, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1f1bc0] "m"(b1ecf90_c1f1bc0), [c1efe30] "m"(b1ecf90_c1efe30), [c1ef9e0] "m"(b1ecf90_c1ef9e0)
      : "memory");
}
#else
#error "D3DDevice_DrawIndexedVertices: clang naked draft required"
#endif


/* D3DDevice_PrimeVertexCache (0x1ed200) — XBE naked draft (batch 329). */
#if defined(__clang__)
static void (*const b1ed200_c1f1bc0)(void) = CDevice_SetStateVB;
static void (*const b1ed200_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_PrimeVertexCache(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6a0, %%ebp\n\t"
      "movl 0x478(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%ebp, %%ecx\n\t"
      "call *%[c1f1bc0]\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "pushl %%ebp\n\t"
      "shrl $1, %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl %%esi, %%ecx\n\t"
      "shll $0x12, %%ecx\n\t"
      "addl $0x40001800, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "leal (,%%esi,4), %%edx\n\t"
      "movl 0x18(%%esp), %%esi\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "shrl $2, %%ecx\n\t"
      "leal 0x4(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "testb $1, 0x14(%%esp)\n\t"
      "leal 0x4(%%eax,%%edx,1), %%eax\n\t"
      "je .LD3DDevice_PrimeVertexCache_1\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movzwl (%%edx,%%ecx,1), %%ecx\n\t"
      "movl $0x41808, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LD3DDevice_PrimeVertexCache_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ebp)\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1f1bc0] "m"(b1ed200_c1f1bc0), [c1efe10] "m"(b1ed200_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_PrimeVertexCache: clang naked draft required"
#endif


/* D3DDevice_SetVertexData4s (0x1ed360) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b1ed360_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void D3DDevice_SetVertexData4s(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "leal 0x81980(,%%ecx,8), %%edx\n\t"
      "movswl 0x10(%%esp), %%ecx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movzwl 0xc(%%esp), %%edx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movzwl 0x14(%%esp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movswl 0x18(%%esp), %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ed360_c1efe10)
      : "memory");
}
#else
#error "D3DDevice_SetVertexData4s: clang naked draft required"
#endif


/* 0x001ed3b0 */
void D3DDevice_SetVertexData4ub(uint32_t reg, uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  XMETAL_StartPush();
  XMETAL_StartPush();
  /* mem[0x001fbb04] = edi */
  /* relift: FUN_001f1b50(0, 0); */
  XMETAL_StartPush();
  /* mem[0x001fbb04] = 0 */
  XMETAL_StartPush();
  /* test (char)eax, 0x10 -> je 0x1ed4c8 */
  D3D_SetFence();
  /* relift: cmp dword ptr [esi + 4], ebp -> jne 0x1ed518 */
  /* relift: test byte ptr [esi + 0x1c], 1 -> je 0x1ed50e */
  LocalFree((void *)(uintptr_t)esi);
  /* test esi, esi -> jne 0x1ed4f6 */

  (void)eax;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* D3DResource_GetType (0x1ed570) — XBE naked draft (batch 300). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DResource_GetType(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "andl $0x70000, %%eax\n\t"
      "cmpl $0x30000, %%eax\n\t"
      "ja .LD3DResource_GetType_4\n\t"
      "je .LD3DResource_GetType_3\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DResource_GetType_2\n\t"
      "cmpl $0x10000, %%eax\n\t"
      "je .LD3DResource_GetType_1\n\t"
      "cmpl $0x20000, %%eax\n\t"
      "jne .LD3DResource_GetType_5\n\t"
      "movl $8, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_1:\n\t"
      "movl $7, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_2:\n\t"
      "movl $6, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_3:\n\t"
      "movl $9, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_4:\n\t"
      "cmpl $0x40000, %%eax\n\t"
      "je .LD3DResource_GetType_8\n\t"
      "cmpl $0x50000, %%eax\n\t"
      "je .LD3DResource_GetType_7\n\t"
      "cmpl $0x60000, %%eax\n\t"
      "je .LD3DResource_GetType_6\n\t"
      ".LD3DResource_GetType_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_6:\n\t"
      "movl $0xa, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_7:\n\t"
      "movl 0xc(%%ecx), %%eax\n\t"
      "andl $0xf0, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $0x20, %%eax\n\t"
      "seta %%cl\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_8:\n\t"
      "movl 0xc(%%ecx), %%eax\n\t"
      "testb $4, %%al\n\t"
      "je .LD3DResource_GetType_9\n\t"
      "movl $5, %%eax\n\t"
      "ret\n\t"
      ".LD3DResource_GetType_9:\n\t"
      "andl $0xf0, %%eax\n\t"
      "movl $0x20, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "addl $3, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DResource_GetType: clang naked draft required"
#endif


/* D3DTexture_GetSurfaceLevel (0x1edc20) — XBE naked draft (batch 370). */
#if defined(__clang__)
static void b1edc20_c1f4270_tgt(void) { return; }
static void (*const b1edc20_c1f4270)(void) = b1edc20_c1f4270_tgt;
static void b1edc20_c1ef2a0_tgt(void) { return; }
static void (*const b1edc20_c1ef2a0)(void) = b1edc20_c1ef2a0_tgt;

__attribute__((naked, noinline))
void D3DTexture_GetSurfaceLevel(void)
{
  __asm__ volatile(
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "leal 0x14(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x24(%%esp), %%edx\n\t"
      "leal 0x18(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x28(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f4270]\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ef2a0]\n\t"
      "popl %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f4270] "m"(b1edc20_c1f4270), [c1ef2a0] "m"(b1edc20_c1ef2a0)
      : "memory");
}
#else
#error "D3DTexture_GetSurfaceLevel: clang naked draft required"
#endif


/* D3DCubeTexture_GetCubeMapSurface (0x1edcb0) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void b1edcb0_c1f4270_tgt(void) { return; }
static void (*const b1edcb0_c1f4270)(void) = b1edcb0_c1f4270_tgt;
static void b1edcb0_c1ef2a0_tgt(void) { return; }
static void (*const b1edcb0_c1ef2a0)(void) = b1edcb0_c1ef2a0_tgt;

__attribute__((naked, noinline))
void D3DCubeTexture_GetCubeMapSurface(void)
{
  __asm__ volatile(
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "leal 0x14(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x14(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x24(%%esp), %%edx\n\t"
      "leal 0x14(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x24(%%esp), %%eax\n\t"
      "leal 0x28(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f4270]\n\t"
      "movl 0x1c(%%esp), %%ecx\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ef2a0]\n\t"
      "popl %%esi\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f4270] "m"(b1edcb0_c1f4270), [c1ef2a0] "m"(b1edcb0_c1ef2a0)
      : "memory");
}
#else
#error "D3DCubeTexture_GetCubeMapSurface: clang naked draft required"
#endif


/* D3DCubeTexture_LockRect — implemented in rasterizer/xbox/d3d_resource.c */

/* D3DVolumeTexture_LockBox — implemented in rasterizer/xbox/d3d_resource.c */

/* D3D_CreateTexture (0x1eddd0) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void b1eddd0_c1f4630_tgt(void) { return; }
static void (*const b1eddd0_c1f4630)(void) = b1eddd0_c1f4630_tgt;
static void *__stdcall (*const b1eddd0_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;
static void *__stdcall (*const b1eddd0_c1d0c16)(void *ptr) = (void *)LocalFree;

__attribute__((naked, noinline))
void D3D_CreateTexture(void)
{
  __asm__ volatile(
      "movl 0x20(%%esp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x2c(%%esp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal 0x2c(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x2c(%%esp), %%eax\n\t"
      "leal 0x34(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x2c(%%esp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x28(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x28(%%esp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl 0x30(%%esp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x30(%%esp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl $0, (%%ebx)\n\t"
      "call *%[c1f4630]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl $0x10000, 0x20(%%esp)\n\t"
      "je .LD3D_CreateTexture_1\n\t"
      "andl $0xfffffff7, 0x30(%%esp)\n\t"
      ".LD3D_CreateTexture_1:\n\t"
      "pushl $0x14\n\t"
      "pushl $0x40\n\t"
      "call *%[c1d0bb9]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_CreateTexture_2\n\t"
      "pushl $0x404\n\t"
      "pushl $0x80\n\t"
      "pushl $0x3ffb000\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *0x25320c\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3D_CreateTexture_3\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d0c16]\n\t"
      ".LD3D_CreateTexture_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LD3D_CreateTexture_3:\n\t"
      "andl $0x3ffffff, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl $0x1040001, (%%esi)\n\t"
      "movl 0x30(%%esp), %%eax\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movl 0x2c(%%esp), %%ecx\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "movl $0, 0x8(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%esi, (%%ebx)\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1f4630] "m"(b1eddd0_c1f4630), [c1d0bb9] "m"(b1eddd0_c1d0bb9), [c1d0c16] "m"(b1eddd0_c1d0c16)
      : "memory");
}
#else
#error "D3D_CreateTexture: clang naked draft required"
#endif


/* D3D_SetPushBufferSize (0x1edea0) — XBE naked draft (batch 373). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3D_SetPushBufferSize(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl %%eax, 0x1fe6b0\n\t"
      "movl %%ecx, 0x1fe6ac\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3D_SetPushBufferSize: clang naked draft required"
#endif


/* Direct3D_CreateDevice (0x1edec0) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void b1edec0_c1f3580_tgt(void) { return; }
static void (*const b1edec0_c1f3580)(void) = b1edec0_c1f3580_tgt;
static void b1edec0_c1f3a90_tgt(void) { return; }
static void (*const b1edec0_c1f3a90)(void) = b1edec0_c1f3a90_tgt;

__attribute__((naked, noinline))
void Direct3D_CreateDevice(void)
{
  __asm__ volatile(
      "movl 0x1fe6b0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LDirect3D_CreateDevice_1\n\t"
      "movl $0x80000, 0x1fe6b0\n\t"
      ".LDirect3D_CreateDevice_1:\n\t"
      "movl 0x1fe6ac, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LDirect3D_CreateDevice_2\n\t"
      "movl $0x8000, 0x1fe6ac\n\t"
      ".LDirect3D_CreateDevice_2:\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fbb1c, %%esi\n\t"
      "andl $0x10, %%eax\n\t"
      "orl %%eax, %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x1fbb10, %%ecx\n\t"
      "movl $0x1fbb10, 0x1fe6a0\n\t"
      "movl $0x1fbb10, 0x1fe6a4\n\t"
      "movl $1, 0x1fbf18\n\t"
      "movl %%esi, 0x1fbb1c\n\t"
      "call *%[c1f3580]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LDirect3D_CreateDevice_3\n\t"
      "movl $0x1fbb10, %%ecx\n\t"
      "call *%[c1f3a90]\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LDirect3D_CreateDevice_3:\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LDirect3D_CreateDevice_4\n\t"
      "movl $0x1fbb10, (%%eax)\n\t"
      ".LDirect3D_CreateDevice_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1f3580] "m"(b1edec0_c1f3580), [c1f3a90] "m"(b1edec0_c1f3a90)
      : "memory");
}
#else
#error "Direct3D_CreateDevice: clang naked draft required"
#endif


/* 0x001ee920 */
void D3DDevice_Present(void *source_rect, void *dest_rect, void *window_override, void *dirty_region)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* D3D_GetAdapterIdentifier (0x1eeac0) — XBE naked draft (batch 370). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3D_GetAdapterIdentifier(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_GetAdapterIdentifier_1\n\t"
      "movl $0x8876086c, %%eax\n\t"
      "ret\n\t"
      ".LD3D_GetAdapterIdentifier_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "movl $0x10b, %%ecx\n\t"
      "movl $0x1fa2f0, %%esi\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3D_GetAdapterIdentifier: clang naked draft required"
#endif


/* D3D_GetAdapterModeCount (0x1eeaf0) — XBE naked draft (batch 319). */
#if defined(__clang__)
static void b1eeaf0_c1f489f_tgt(void) { return; }
static void (*const b1eeaf0_c1f489f)(void) = b1eeaf0_c1f489f_tgt;
static void (*const b1eeaf0_c1f4880)(void) = CMiniport_GetDisplayCapabilities;

__attribute__((naked, noinline))
void D3D_GetAdapterModeCount(void)
{
  __asm__ volatile(
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0x10(%%esp)\n\t"
      "call *%[c1f489f]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1f4880]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%eax, %%ebp\n\t"
      "andl $0xff, %%edx\n\t"
      "andl $0xff, %%edi\n\t"
      "andl $0xc00000, %%ebx\n\t"
      "andl $0xe0000, %%ebp\n\t"
      "movl %%ebp, 0x14(%%esp)\n\t"
      "jmp .LD3D_GetAdapterModeCount_2\n\t"
      ".LD3D_GetAdapterModeCount_1:\n\t"
      "movl 0x14(%%esp), %%ebp\n\t"
      ".LD3D_GetAdapterModeCount_2:\n\t"
      "cmpl $4, %%edi\n\t"
      "jne .LD3D_GetAdapterModeCount_3\n\t"
      "testl $0x60000, %%ecx\n\t"
      "jne .LD3D_GetAdapterModeCount_4\n\t"
      ".LD3D_GetAdapterModeCount_3:\n\t"
      "testl $0x10000, %%ecx\n\t"
      "je .LD3D_GetAdapterModeCount_4\n\t"
      "testl $0x10000, %%eax\n\t"
      "je .LD3D_GetAdapterModeCount_6\n\t"
      ".LD3D_GetAdapterModeCount_4:\n\t"
      "testl %%ecx, %%ebx\n\t"
      "je .LD3D_GetAdapterModeCount_6\n\t"
      "cmpl $4, %%edi\n\t"
      "jne .LD3D_GetAdapterModeCount_5\n\t"
      "testl %%ecx, %%ebp\n\t"
      "jne .LD3D_GetAdapterModeCount_5\n\t"
      "testl $0xe0000, %%ecx\n\t"
      "jne .LD3D_GetAdapterModeCount_6\n\t"
      ".LD3D_GetAdapterModeCount_5:\n\t"
      "incl 0x10(%%esp)\n\t"
      ".LD3D_GetAdapterModeCount_6:\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl $0xc, %%esi\n\t"
      "movl %%ecx, %%ebp\n\t"
      "andl $0xff, %%ebp\n\t"
      "cmpl %%edx, %%ebp\n\t"
      "je .LD3D_GetAdapterModeCount_1\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "shll $2, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f489f] "m"(b1eeaf0_c1f489f), [c1f4880] "m"(b1eeaf0_c1f4880)
      : "memory");
}
#else
#error "D3D_GetAdapterModeCount: clang naked draft required"
#endif


/* D3D_EnumAdapterModes (0x1eeb90) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void b1eeb90_c1f489f_tgt(void) { return; }
static void (*const b1eeb90_c1f489f)(void) = b1eeb90_c1f489f_tgt;
static void (*const b1eeb90_c1f4880)(void) = CMiniport_GetDisplayCapabilities;
static void b1eeb90_c1f4840_tgt(void) { return; }
static void (*const b1eeb90_c1f4840)(void) = b1eeb90_c1f4840_tgt;

__attribute__((naked, noinline))
void D3D_EnumAdapterModes(void)
{
  __asm__ volatile(
      "subl $8, %%esp\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%esi\n\t"
      "andl $3, %%eax\n\t"
      "shrl $2, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x14(%%esp)\n\t"
      "movl %%ecx, 0x20(%%esp)\n\t"
      "call *%[c1f489f]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1f4880]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%eax, %%ebp\n\t"
      "andl $0xff, %%edx\n\t"
      "andl $0xff, %%edi\n\t"
      "andl $0xc00000, %%ebx\n\t"
      "andl $0xe0000, %%ebp\n\t"
      "movl %%ebp, 0x10(%%esp)\n\t"
      "jmp .LD3D_EnumAdapterModes_2\n\t"
      ".LD3D_EnumAdapterModes_1:\n\t"
      "movl 0x10(%%esp), %%ebp\n\t"
      ".LD3D_EnumAdapterModes_2:\n\t"
      "cmpl $4, %%edi\n\t"
      "jne .LD3D_EnumAdapterModes_3\n\t"
      "testl $0x60000, %%ecx\n\t"
      "jne .LD3D_EnumAdapterModes_4\n\t"
      ".LD3D_EnumAdapterModes_3:\n\t"
      "testl $0x10000, %%ecx\n\t"
      "je .LD3D_EnumAdapterModes_4\n\t"
      "testl $0x10000, %%eax\n\t"
      "je .LD3D_EnumAdapterModes_6\n\t"
      ".LD3D_EnumAdapterModes_4:\n\t"
      "testl %%ecx, %%ebx\n\t"
      "je .LD3D_EnumAdapterModes_6\n\t"
      "cmpl $4, %%edi\n\t"
      "jne .LD3D_EnumAdapterModes_5\n\t"
      "testl %%ecx, %%ebp\n\t"
      "jne .LD3D_EnumAdapterModes_5\n\t"
      "testl $0xe0000, %%ecx\n\t"
      "jne .LD3D_EnumAdapterModes_6\n\t"
      ".LD3D_EnumAdapterModes_5:\n\t"
      "movl 0x20(%%esp), %%ecx\n\t"
      "movl %%ecx, %%ebp\n\t"
      "decl %%ecx\n\t"
      "testl %%ebp, %%ebp\n\t"
      "movl %%ecx, 0x20(%%esp)\n\t"
      "je .LD3D_EnumAdapterModes_7\n\t"
      ".LD3D_EnumAdapterModes_6:\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl $0xc, %%esi\n\t"
      "movl %%ecx, %%ebp\n\t"
      "andl $0xff, %%ebp\n\t"
      "cmpl %%edx, %%ebp\n\t"
      "je .LD3D_EnumAdapterModes_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl $0x8876086c, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".LD3D_EnumAdapterModes_7:\n\t"
      "movzwl 0x4(%%esi), %%eax\n\t"
      "movl 0x24(%%esp), %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movzwl 0x6(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl (%%esi), %%edx\n\t"
      "andl $0x400000, %%edx\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl $0xa, %%edx\n\t"
      "addl $0x32, %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1f4840]\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LD3D_EnumAdapterModes_12\n\t"
      "jmp *.LD3D_EnumAdapterModes_jt(,%%eax,4)\n\t"
      ".LD3D_EnumAdapterModes_8:\n\t"
      "movl $0x1e, 0x10(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".LD3D_EnumAdapterModes_9:\n\t"
      "movl $0x11, 0x10(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".LD3D_EnumAdapterModes_10:\n\t"
      "movl $0x1c, 0x10(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".LD3D_EnumAdapterModes_11:\n\t"
      "movl $0x12, 0x10(%%edi)\n\t"
      ".LD3D_EnumAdapterModes_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LD3D_EnumAdapterModes_jt:\n\t"
      ".long .LD3D_EnumAdapterModes_8\n\t"
      ".long .LD3D_EnumAdapterModes_9\n\t"
      ".long .LD3D_EnumAdapterModes_10\n\t"
      ".long .LD3D_EnumAdapterModes_11\n\t"
      ".text\n\t"
      :
      : [c1f489f] "m"(b1eeb90_c1f489f), [c1f4880] "m"(b1eeb90_c1f4880), [c1f4840] "m"(b1eeb90_c1f4840)
      : "memory");
}
#else
#error "D3D_EnumAdapterModes: clang naked draft required"
#endif


/* D3D_GetDeviceCaps (0x1eecf0) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void __stdcall (*const b1eecf0_c1e69f0)(void *caps) = (void *)D3DDevice_GetDeviceCaps;

__attribute__((naked, noinline))
void D3D_GetDeviceCaps(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_GetDeviceCaps_1\n\t"
      "movl $0x8876086c, %%eax\n\t"
      "ret\n\t"
      ".LD3D_GetDeviceCaps_1:\n\t"
      "cmpl $1, 0x8(%%esp)\n\t"
      "je .LD3D_GetDeviceCaps_2\n\t"
      "movl $0x8876086b, %%eax\n\t"
      "ret\n\t"
      ".LD3D_GetDeviceCaps_2:\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e69f0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c1e69f0] "m"(b1eecf0_c1e69f0)
      : "memory");
}
#else
#error "D3D_GetDeviceCaps: clang naked draft required"
#endif


/* D3D_GetAdapterDisplayMode (0x1eed40) — XBE naked draft (batch 328). */
#if defined(__clang__)
static void b1eed40_c1f4840_tgt(void) { return; }
static void (*const b1eed40_c1f4840)(void) = b1eed40_c1f4840_tgt;

__attribute__((naked, noinline))
void D3D_GetAdapterDisplayMode(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_GetAdapterDisplayMode_1\n\t"
      "movl $0x8876086c, %%eax\n\t"
      "ret\n\t"
      ".LD3D_GetAdapterDisplayMode_1:\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LD3D_GetAdapterDisplayMode_2\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl %%eax, 0xc(%%ecx)\n\t"
      "movl %%eax, 0x10(%%ecx)\n\t"
      "ret\n\t"
      ".LD3D_GetAdapterDisplayMode_2:\n\t"
      "movl 0x21b4(%%ecx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl 0x21b8(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl 0x2510(%%ecx), %%eax\n\t"
      "andl $0x400000, %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xa, %%eax\n\t"
      "addl $0x32, %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movzbl 0x2175(%%ecx), %%edx\n\t"
      "movl %%edx, 0x10(%%esi)\n\t"
      "movl 0x2510(%%ecx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1f4840]\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c1f4840] "m"(b1eed40_c1f4840)
      : "memory");
}
#else
#error "D3D_GetAdapterDisplayMode: clang naked draft required"
#endif


/* D3D_CheckDeviceFormat (0x1eee20) — XBE naked draft (batch 311). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3D_CheckDeviceFormat(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_CheckDeviceFormat_1\n\t"
      "movl $0x8876086c, %%eax\n\t"
      "ret\n\t"
      ".LD3D_CheckDeviceFormat_1:\n\t"
      "cmpl $1, 0x8(%%esp)\n\t"
      "je .LD3D_CheckDeviceFormat_2\n\t"
      "movl $0x8876086b, %%eax\n\t"
      "ret\n\t"
      ".LD3D_CheckDeviceFormat_2:\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movb 0x1f9d58(%%eax), %%dl\n\t"
      "movb $0x80, %%cl\n\t"
      "testb %%dl, %%cl\n\t"
      "je .LD3D_CheckDeviceFormat_5\n\t"
      "movb 0x10(%%esp), %%al\n\t"
      "testb $2, %%al\n\t"
      "je .LD3D_CheckDeviceFormat_3\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "testb $0x40, 0x1f9d58(%%ecx)\n\t"
      "jne .LD3D_CheckDeviceFormat_6\n\t"
      "movl $0x8876086a, %%eax\n\t"
      "ret\n\t"
      ".LD3D_CheckDeviceFormat_3:\n\t"
      "testb $1, %%al\n\t"
      "je .LD3D_CheckDeviceFormat_4\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "testb %%cl, 0x1f9d58(%%edx)\n\t"
      "jne .LD3D_CheckDeviceFormat_6\n\t"
      "movl $0x8876086a, %%eax\n\t"
      "ret\n\t"
      ".LD3D_CheckDeviceFormat_4:\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "testb $0x3c, 0x1f9d58(%%eax)\n\t"
      "jne .LD3D_CheckDeviceFormat_6\n\t"
      ".LD3D_CheckDeviceFormat_5:\n\t"
      "movl $0x8876086a, %%eax\n\t"
      "ret\n\t"
      ".LD3D_CheckDeviceFormat_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3D_CheckDeviceFormat: clang naked draft required"
#endif


/* Direct3D_CheckDeviceMultiSampleType (0x1eeea0) — XBE naked draft (batch 307). */
#if defined(__clang__)


__attribute__((naked, noinline))
void Direct3D_CheckDeviceMultiSampleType(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LDirect3D_CheckDeviceMultiSampleType_2\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .LDirect3D_CheckDeviceMultiSampleType_1\n\t"
      "movl $0x8876086b, %%eax\n\t"
      "ret\n\t"
      ".LDirect3D_CheckDeviceMultiSampleType_1:\n\t"
      "cmpl %%edx, 0x10(%%esp)\n\t"
      "je .LDirect3D_CheckDeviceMultiSampleType_4\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movb 0x1f9d58(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jns .LDirect3D_CheckDeviceMultiSampleType_4\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "cmpl $0x11, %%ecx\n\t"
      "je .LDirect3D_CheckDeviceMultiSampleType_5\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LDirect3D_CheckDeviceMultiSampleType_5\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0xf0000, %%eax\n\t"
      "cmpl $0x40000, %%eax\n\t"
      "jbe .LDirect3D_CheckDeviceMultiSampleType_3\n\t"
      ".LDirect3D_CheckDeviceMultiSampleType_2:\n\t"
      "movl $0x8876086c, %%eax\n\t"
      "ret\n\t"
      ".LDirect3D_CheckDeviceMultiSampleType_3:\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "andl $0xf, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jb .LDirect3D_CheckDeviceMultiSampleType_4\n\t"
      "andl $0xf, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jb .LDirect3D_CheckDeviceMultiSampleType_4\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LDirect3D_CheckDeviceMultiSampleType_4\n\t"
      "cmpl $3, %%ecx\n\t"
      "jbe .LDirect3D_CheckDeviceMultiSampleType_5\n\t"
      ".LDirect3D_CheckDeviceMultiSampleType_4:\n\t"
      "movl $0x8876086a, %%eax\n\t"
      "ret\n\t"
      ".LDirect3D_CheckDeviceMultiSampleType_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "Direct3D_CheckDeviceMultiSampleType: clang naked draft required"
#endif


/* D3DDevice_CreateIndexBuffer (0x1eef80) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void *__stdcall (*const b1eef80_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;

__attribute__((naked, noinline))
void D3DDevice_CreateIndexBuffer(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1d0bb9]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_CreateIndexBuffer_1\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "ret\n\t"
      ".LD3DDevice_CreateIndexBuffer_1:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "leal 0xc(%%eax), %%ecx\n\t"
      "movl $0x1010001, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%eax, (%%edx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c1d0bb9] "m"(b1eef80_c1d0bb9)
      : "memory");
}
#else
#error "D3DDevice_CreateIndexBuffer: clang naked draft required"
#endif


/* D3DPalette_Lock (0x1eefe0) — XBE naked draft (batch 384). */
#if defined(__clang__)
static void (*const b1eefe0_c1efd80)(void) = (void *)D3D_BlockOnResource;
static void b1eefe0_c1ed7c0_tgt(void) { return; }
static void (*const b1eefe0_c1ed7c0)(void) = b1eefe0_c1ed7c0_tgt;

__attribute__((naked, noinline))
void D3DPalette_Lock(void)
{
  __asm__ volatile(
      "testb $0xa0, 0xc(%%esp)\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "jne .LD3DPalette_Lock_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efd80]\n\t"
      ".LD3DPalette_Lock_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ed7c0]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1efd80] "m"(b1eefe0_c1efd80), [c1ed7c0] "m"(b1eefe0_c1ed7c0)
      : "memory");
}
#else
#error "D3DPalette_Lock: clang naked draft required"
#endif


/* 0x001ef0a0 */
int D3DDevice_CreateVertexBuffer(uint32_t length, uint32_t usage, uint32_t fvf, uint32_t pool, void **ppVertexBuffer)
{
  int eax = 0;
  int esi = 0;

  FUN_001d0bb9(64, 12);
  /* test esi, esi -> je 0x1ef0d3 */
  /* test eax, eax -> jne 0x1ef0dc */
  LocalFree((void *)(uintptr_t)esi);
  return 0;

  (void)eax;
  (void)esi;
}

/* D3DVertexBuffer_Lock (0x1ef100) — XBE naked draft (batch 374). */
#if defined(__clang__)
static void (*const b1ef100_c1efe10)(void) = (void *)XMETAL_StartPush;
static void (*const b1ef100_c1efd80)(void) = (void *)D3D_BlockOnResource;
static void b1ef100_c1ed7c0_tgt(void) { return; }
static void (*const b1ef100_c1ed7c0)(void) = b1ef100_c1ed7c0_tgt;

__attribute__((naked, noinline))
void D3DVertexBuffer_Lock(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movb 0x18(%%esp), %%bl\n\t"
      "testb $0x10, %%bl\n\t"
      "pushl %%esi\n\t"
      "jne .LD3DVertexBuffer_Lock_1\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl $0x41710, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      ".LD3DVertexBuffer_Lock_1:\n\t"
      "testb $0xa0, %%bl\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "jne .LD3DVertexBuffer_Lock_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efd80]\n\t"
      ".LD3DVertexBuffer_Lock_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ed7c0]\n\t"
      "addl 0x10(%%esp), %%eax\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ef100_c1efe10), [c1efd80] "m"(b1ef100_c1efd80), [c1ed7c0] "m"(b1ef100_c1ed7c0)
      : "memory");
}
#else
#error "D3DVertexBuffer_Lock: clang naked draft required"
#endif


/* D3DVertexBuffer_GetDesc (0x1ef150) — XBE naked draft (batch 375). */
#if defined(__clang__)
static void (*const b1ef150_c1ed570)(void) = (void *)D3DResource_GetType;

__attribute__((naked, noinline))
void D3DVertexBuffer_GetDesc(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%eax\n\t"
      "movl $0x64, (%%esi)\n\t"
      "call *%[c1ed570]\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1ed570] "m"(b1ef150_c1ed570)
      : "memory");
}
#else
#error "D3DVertexBuffer_GetDesc: clang naked draft required"
#endif


/* D3DDevice_CreatePalette (0x1ef170) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void *__stdcall (*const b1ef170_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;
static void *__stdcall (*const b1ef170_c1d0c16)(void *ptr) = (void *)LocalFree;

__attribute__((naked, noinline))
void D3DDevice_CreatePalette(void)
{
  __asm__ volatile(
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl $0x40\n\t"
      "call *%[c1d0bb9]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LD3DDevice_CreatePalette_1\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LD3DDevice_CreatePalette_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "movl 0x1fa71c(,%%esi,4), %%eax\n\t"
      "pushl $0x404\n\t"
      "pushl $0\n\t"
      "pushl $0x3ffb000\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *0x25320c\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LD3DDevice_CreatePalette_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d0c16]\n\t"
      "popl %%esi\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LD3DDevice_CreatePalette_2:\n\t"
      "shll $0x1e, %%esi\n\t"
      "andl $0x3ffffff, %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "orl $0x1030001, %%esi\n\t"
      "movl %%esi, (%%edi)\n\t"
      "movl %%edi, (%%eax)\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [c1d0bb9] "m"(b1ef170_c1d0bb9), [c1d0c16] "m"(b1ef170_c1d0c16)
      : "memory");
}
#else
#error "D3DDevice_CreatePalette: clang naked draft required"
#endif


/* 0x001ef1e0 */
int D3DSurface_GetDesc(void *surface, void *desc)
{
  int eax = 0;
  int ecx = 0;

  Get2DSurfaceDesc((void *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  return 0;

  (void)eax;
  (void)ecx;
}

/* D3DSurface_LockRect — implemented in rasterizer/xbox/d3d_resource.c */


/* D3DDevice_IsFencePending (0x1ef890) — XBE naked draft (batch 342). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_IsFencePending(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x3f0(%%eax), %%ecx\n\t"
      "movl 0x1c(%%eax), %%eax\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "subl 0x4(%%esp), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_IsFencePending: clang naked draft required"
#endif


/* 0x001ef8c0 */
void D3DDevice_InsertCallback(uint32_t type, void *callback, uint32_t context)
{
  XMETAL_StartPush();
}

/* CDevice_KickOff (0x1ef930) — XBE naked draft (batch 323). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CDevice_KickOff(void)
{
  __asm__ volatile(
      "pushl %%ecx\n\t"
      "movl 0x1fb490, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ecx, (%%esp)\n\t"
      "jne .LCDevice_KickOff_4\n\t"
      "testb $4, 0xc(%%ecx)\n\t"
      "je .LCDevice_KickOff_1\n\t"
      "movl 0x400(%%ecx), %%ecx\n\t"
      "jmp .LCDevice_KickOff_2\n\t"
      ".LCDevice_KickOff_1:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      ".LCDevice_KickOff_2:\n\t"
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x2308(%%eax), %%eax\n\t"
      ".byte 0x0f, 0xae, 0xf8\n\t"
      "movl 0x100410(%%eax), %%edx\n\t"
      "orl $0x10000, %%edx\n\t"
      "movl %%edx, 0x100410(%%eax)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LCDevice_KickOff_3:\n\t"
      "testl $0x10000, 0x100410(%%eax)\n\t"
      "jne .LCDevice_KickOff_3\n\t"
      "movl (%%esp), %%eax\n\t"
      "movl 0x2304(%%eax), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x3ffffff, %%edx\n\t"
      "movl %%edx, 0x40(%%eax)\n\t"
      "movl (%%esp), %%edx\n\t"
      "movl %%ecx, 0x18(%%edx)\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      ".LCDevice_KickOff_4:\n\t"
      "movl 0x2304(%%ecx), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "orl $0x80000000, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl (%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, 0x18(%%eax)\n\t"
      "movl (%%esp), %%eax\n\t"
      "movl 0x1c(%%eax), %%edx\n\t"
      "movl 0x3f0(%%eax), %%eax\n\t"
      "subl $2, %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl (%%esp), %%eax\n\t"
      "movl 0x2b60(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x2518(%%eax)\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CDevice_KickOff: clang naked draft required"
#endif


/* D3D_SetFence (0x1ef9e0) — XBE naked draft (batch 312). */
#if defined(__clang__)
static void (*const b1ef9e0_c1efe10)(void) = XMETAL_StartPush;
static void (*const b1ef9e0_c1ef930)(void) = CDevice_KickOff;

__attribute__((naked, noinline))
void D3D_SetFence(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x1c(%%esi), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      "movl %%ecx, 0x14(%%eax)\n\t"
      "movl $0x41d70, (%%eax)\n\t"
      "movl %%edi, 0x4(%%eax)\n\t"
      "movl $0x41d90, %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl %%edx, 0x10(%%eax)\n\t"
      "movl 0x3e4(%%esi), %%edx\n\t"
      "leal 0x18(%%eax), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%edi, %%ecx\n\t"
      "shrl $1, %%ecx\n\t"
      "andl $0x3f, %%ecx\n\t"
      "leal 0x39(%%ecx,%%ecx,2), %%ebx\n\t"
      "movl %%edi, (%%esi,%%ebx,4)\n\t"
      "movb 0x10(%%esp), %%bl\n\t"
      "testb $1, %%bl\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "leal (%%esi,%%ecx,4), %%ecx\n\t"
      "movl %%eax, 0xe8(%%ecx)\n\t"
      "movl %%edx, 0xec(%%ecx)\n\t"
      "je .LD3D_SetFence_1\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "incl %%ecx\n\t"
      "andl $0xf, %%ecx\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      "pushl %%ebp\n\t"
      "leal 0x9(%%ecx,%%ecx,2), %%ebp\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "leal (%%esi,%%ecx,4), %%ecx\n\t"
      "movl %%edi, (%%esi,%%ebp,4)\n\t"
      "movl %%eax, 0x28(%%ecx)\n\t"
      "movl %%edx, 0x2c(%%ecx)\n\t"
      "popl %%ebp\n\t"
      ".LD3D_SetFence_1:\n\t"
      "testb $2, %%bl\n\t"
      "jne .LD3D_SetFence_2\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1ef930]\n\t"
      ".LD3D_SetFence_2:\n\t"
      "addl $2, 0x1c(%%esi)\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1ef9e0_c1efe10), [c1ef930] "m"(b1ef9e0_c1ef930)
      : "memory");
}
#else
#error "D3D_SetFence: clang naked draft required"
#endif


/* CDevice_MakeSpace (0x1efb70) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void b1efb70_c1ef740_tgt(void) { return; }
static void (*const b1efb70_c1ef740)(void) = b1efb70_c1ef740_tgt;
static void (*const b1efb70_c1ef930)(void) = CDevice_KickOff;
static void __stdcall (*const b1efb70_c1efa80)(uint32_t time, int param2) = (void *)D3D_BlockOnTime;
static void (*const b1efb70_c1ef9e0)(void) = D3D_SetFence;

__attribute__((naked, noinline))
void CDevice_MakeSpace(void)
{
  __asm__ volatile(
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "testb $4, 0xc(%%esi)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "je .LCDevice_MakeSpace_1\n\t"
      "movl 0x3f4(%%esi), %%eax\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl 0x3f8(%%esi), %%edx\n\t"
      "subl %%edi, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl %%edx, 0x3f8(%%esi)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      ".LCDevice_MakeSpace_1:\n\t"
      "movl 0x1fe6ac, %%eax\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "leal (%%eax,%%ecx,1), %%edi\n\t"
      "shrl $1, %%eax\n\t"
      "movl %%edi, 0x8(%%esp)\n\t"
      "addl %%eax, %%edi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "movl %%ecx, 0xc(%%esp)\n\t"
      "jb .LCDevice_MakeSpace_4\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "ja .LCDevice_MakeSpace_2\n\t"
      "movl %%edx, 0x8(%%esp)\n\t"
      "jmp .LCDevice_MakeSpace_4\n\t"
      ".LCDevice_MakeSpace_2:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl (%%esi), %%edx\n\t"
      "subl %%eax, %%ecx\n\t"
      "andl $0xfffffff, %%eax\n\t"
      "movl %%ecx, 0x3e8(%%esi)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x2304(%%esi), %%edx\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "jmp .LCDevice_MakeSpace_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LCDevice_MakeSpace_3:\n\t"
      "movl 0x44(%%edx), %%eax\n\t"
      "orl $0x80000000, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LCDevice_MakeSpace_3\n\t"
      "movl 0x1fe6ac, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%ecx, 0xc(%%esp)\n\t"
      "movl %%eax, 0x8(%%esp)\n\t"
      "movl %%ecx, (%%esi)\n\t"
      ".LCDevice_MakeSpace_4:\n\t"
      "movl 0x3f0(%%esi), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl 0x2304(%%esi), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "orl $0x80000000, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jb .LCDevice_MakeSpace_5\n\t"
      "cmpl 0x14(%%esi), %%eax\n\t"
      "jb .LCDevice_MakeSpace_6\n\t"
      ".LCDevice_MakeSpace_5:\n\t"
      "movl 0x404(%%esi), %%eax\n\t"
      "movl 0x324c(%%eax), %%eax\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "orl $0x80000000, %%eax\n\t"
      ".LCDevice_MakeSpace_6:\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jae .LCDevice_MakeSpace_15\n\t"
      "cmpl 0x8(%%esp), %%eax\n\t"
      "ja .LCDevice_MakeSpace_15\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "movl 0x1fe6b0, %%ebp\n\t"
      "shrl $1, %%ebp\n\t"
      "addl %%ecx, %%ebp\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "leal 0x9(%%eax,%%eax,2), %%ebx\n\t"
      "movl (%%esi,%%ebx,4), %%ebx\n\t"
      "movl %%ecx, %%edx\n\t"
      "subl %%edi, %%edx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%edi\n\t"
      "movl 0x28(%%esi,%%edi,4), %%edi\n\t"
      "jae .LCDevice_MakeSpace_9\n\t"
      "nop\n\t"
      ".LCDevice_MakeSpace_7:\n\t"
      "cmpl 0x14(%%esp), %%edi\n\t"
      "jae .LCDevice_MakeSpace_8\n\t"
      "addl 0x3e8(%%esi), %%edi\n\t"
      ".LCDevice_MakeSpace_8:\n\t"
      "cmpl %%ebp, %%edi\n\t"
      "jb .LCDevice_MakeSpace_16\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "decl %%eax\n\t"
      "andl $0xf, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LCDevice_MakeSpace_9\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl 0x28(%%esi,%%ecx,4), %%edi\n\t"
      "leal 0x9(%%eax,%%eax,2), %%ecx\n\t"
      "movl (%%esi,%%ecx,4), %%ebx\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jb .LCDevice_MakeSpace_7\n\t"
      ".LCDevice_MakeSpace_9:\n\t"
      "movl $0x190, %%ecx\n\t"
      "jmp .LCDevice_MakeSpace_10\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LCDevice_MakeSpace_10:\n\t"
      "movl %%ecx, 0x18(%%esp)\n\t"
      ".LCDevice_MakeSpace_11:\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x18(%%esp)\n\t"
      "jne .LCDevice_MakeSpace_11\n\t"
      "movl 0x2304(%%esi), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "orl $0x80000000, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jb .LCDevice_MakeSpace_12\n\t"
      "cmpl 0x14(%%esi), %%eax\n\t"
      "jb .LCDevice_MakeSpace_13\n\t"
      ".LCDevice_MakeSpace_12:\n\t"
      "movl 0x404(%%esi), %%eax\n\t"
      "movl 0x324c(%%eax), %%eax\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "orl $0x80000000, %%eax\n\t"
      ".LCDevice_MakeSpace_13:\n\t"
      "cmpl %%eax, 0x14(%%esp)\n\t"
      "jae .LCDevice_MakeSpace_14\n\t"
      "cmpl 0x10(%%esp), %%eax\n\t"
      "jbe .LCDevice_MakeSpace_10\n\t"
      ".LCDevice_MakeSpace_14:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1ef740]\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      ".LCDevice_MakeSpace_15:\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $0xfffffdfc, %%ecx\n\t"
      "testb $8, %%ah\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "je .LCDevice_MakeSpace_17\n\t"
      "orl $0x1000, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[c1ef930]\n\t"
      "movl (%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      ".LCDevice_MakeSpace_16:\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1efa80]\n\t"
      "jmp .LCDevice_MakeSpace_14\n\t"
      ".LCDevice_MakeSpace_17:\n\t"
      "pushl $1\n\t"
      "call *%[c1ef9e0]\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1ef930]\n\t"
      "movl (%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      :
      : [c1ef740] "m"(b1efb70_c1ef740), [c1ef930] "m"(b1efb70_c1ef930), [c1efa80] "m"(b1efb70_c1efa80), [c1ef9e0] "m"(b1efb70_c1ef9e0)
      : "memory");
}
#else
#error "CDevice_MakeSpace: clang naked draft required"
#endif


/* D3D_BlockOnResource (0x1efd80) — XBE naked draft (batch 368). */
#if defined(__clang__)
static void b1efd80_c1ed870_tgt(void) { return; }
static void (*const b1efd80_c1ed870)(void) = b1efd80_c1ed870_tgt;
static void __stdcall (*const b1efd80_c1efa80)(uint32_t time, int param2) = (void *)D3D_BlockOnTime;

__attribute__((naked, noinline))
void D3D_BlockOnResource(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_BlockOnResource_4\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "andl $0x70000, %%eax\n\t"
      "cmpl $0x50000, %%eax\n\t"
      "pushl %%edi\n\t"
      "jne .LD3D_BlockOnResource_2\n\t"
      "movl 0x14(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3D_BlockOnResource_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ed870]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3D_BlockOnResource_1\n\t"
      "movl 0x1fe6a0, %%ecx\n\t"
      "movl 0x1c(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1efa80]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3D_BlockOnResource_1:\n\t"
      "movl %%edi, %%esi\n\t"
      ".LD3D_BlockOnResource_2:\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ed870]\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl $0\n\t"
      "je .LD3D_BlockOnResource_3\n\t"
      "movl 0x1fe6a0, %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1efa80]\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LD3D_BlockOnResource_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1efa80]\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      ".LD3D_BlockOnResource_4:\n\t"
      "ret\n\t"
      :
      : [c1ed870] "m"(b1efd80_c1ed870), [c1efa80] "m"(b1efd80_c1efa80)
      : "memory");
}
#else
#error "D3D_BlockOnResource: clang naked draft required"
#endif


/* XMETAL_StartPush (0x1efe10) — XBE naked draft (batch 339). */
#if defined(__clang__)
static void (*const b1efe10_c1efb70)(void) = CDevice_MakeSpace;

__attribute__((naked, noinline))
void XMETAL_StartPush(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "cmpl 0x4(%%ecx), %%eax\n\t"
      "jb .LXMETAL_StartPush_1\n\t"
      "call *%[c1efb70]\n\t"
      ".LXMETAL_StartPush_1:\n\t"
      "ret\n\t"
      :
      : [c1efb70] "m"(b1efe10_c1efb70)
      : "memory");
}
#else
#error "XMETAL_StartPush: clang naked draft required"
#endif


/* D3D_UpdateProjectionViewportTransform (0x1f02d0) — XBE naked draft (batch 307). */
#if defined(__clang__)
static void b1f02d0_c1f2340_tgt(void) { return; }
static void (*const b1f02d0_c1f2340)(void) = b1f02d0_c1f2340_tgt;

__attribute__((naked, noinline))
void D3D_UpdateProjectionViewportTransform(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "andl $0xfffffff0, %%esp\n\t"
      "subl $0x58, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "movl 0xb08(%%esi), %%eax\n\t"
      "fildl 0xb08(%%esi)\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "jge .LD3D_UpdateProjectionViewportTransform_1\n\t"
      "fadds 0x25fb8c\n\t"
      ".LD3D_UpdateProjectionViewportTransform_1:\n\t"
      "fmuls 0x500(%%esi)\n\t"
      "movl 0xb0c(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fmuls 0x253398\n\t"
      "fsts 0x14(%%esp)\n\t"
      "fildl 0xb0c(%%esi)\n\t"
      "jge .LD3D_UpdateProjectionViewportTransform_2\n\t"
      "fadds 0x25fb8c\n\t"
      ".LD3D_UpdateProjectionViewportTransform_2:\n\t"
      "fmuls 0x504(%%esi)\n\t"
      "movl 0x1fb884, %%eax\n\t"
      "cmpl $2, %%eax\n\t"
      "fmuls 0x255964\n\t"
      "fsts 0xc(%%esp)\n\t"
      "fchs\n\t"
      "fstps 0x18(%%esp)\n\t"
      "flds 0xb14(%%esi)\n\t"
      "fsubs 0xb10(%%esi)\n\t"
      "fmuls 0x4f8(%%esi)\n\t"
      "fstps 0x10(%%esp)\n\t"
      "flds 0x4f8(%%esi)\n\t"
      "fmuls 0xb10(%%esi)\n\t"
      "fstps 0x1c(%%esp)\n\t"
      "jne .LD3D_UpdateProjectionViewportTransform_3\n\t"
      "flds 0x4f4(%%esi)\n\t"
      "fmuls 0x4f8(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xca\n\t"
      "flds 0xc(%%esp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x10(%%esp)\n\t"
      "fstps 0x10(%%esp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x14(%%esp)\n\t"
      "fstps 0x14(%%esp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x18(%%esp)\n\t"
      "fstps 0x18(%%esp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x1c(%%esp)\n\t"
      "fstps 0x1c(%%esp)\n\t"
      "jmp .LD3D_UpdateProjectionViewportTransform_4\n\t"
      ".LD3D_UpdateProjectionViewportTransform_3:\n\t"
      "flds 0x2533c8\n\t"
      "flds 0xc(%%esp)\n\t"
      ".LD3D_UpdateProjectionViewportTransform_4:\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "fxch %%st(2)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x10, %%ecx\n\t"
      "leal 0x20(%%esp), %%edi\n\t"
      "rep stosl\n\t"
      "fstps 0x20(%%esp)\n\t"
      "fxch %%st(1)\n\t"
      "fstps 0x34(%%esp)\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "fstps 0x5c(%%esp)\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl %%edx, 0x48(%%esp)\n\t"
      "movl 0x1c(%%esp), %%edx\n\t"
      "movl %%eax, 0x50(%%esp)\n\t"
      "leal 0x20(%%esp), %%eax\n\t"
      "movl %%ecx, 0x54(%%esp)\n\t"
      "pushl %%eax\n\t"
      "leal 0x8c0(%%esi), %%ecx\n\t"
      "movl %%edx, 0x5c(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "leal 0x5a0(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1f2340]\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "orl $2, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1f2340] "m"(b1f02d0_c1f2340)
      : "memory");
}
#else
#error "D3D_UpdateProjectionViewportTransform: clang naked draft required"
#endif


/* D3D_LazySetPointParams (0x1f05e0) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b1f05e0_c1efe10)(void) = XMETAL_StartPush;
static void b1f05e0_c1f3c30_tgt(void) { return; }
static void (*const b1f05e0_c1f3c30)(void) = b1f05e0_c1f3c30_tgt;

__attribute__((naked, noinline))
void D3D_LazySetPointParams(void)
{
  __asm__ volatile(
      "subl $0x14, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x20(%%esp), %%edi\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "andl $0xfffffffe, %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x1fb85c, %%ecx\n\t"
      "movl 0x1fb840, %%edx\n\t"
      "movl %%ecx, 0x20(%%esp)\n\t"
      "movl 0x1fb84c, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1fb844, %%eax\n\t"
      "movl %%eax, 0x8(%%esp)\n\t"
      "movl %%edx, 0xc(%%esp)\n\t"
      "jne .LD3D_LazySetPointParams_3\n\t"
      "flds 0xc(%%esp)\n\t"
      "fmuls 0x508(%%edi)\n\t"
      "fcoms 0x8(%%esp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LD3D_LazySetPointParams_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%esp)\n\t"
      ".LD3D_LazySetPointParams_1:\n\t"
      "fcoms 0x20(%%esp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LD3D_LazySetPointParams_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x20(%%esp)\n\t"
      ".LD3D_LazySetPointParams_2:\n\t"
      "fcoms 0x1fa744\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LD3D_LazySetPointParams_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254df8\n\t"
      "jmp .LD3D_LazySetPointParams_5\n\t"
      ".LD3D_LazySetPointParams_3:\n\t"
      "flds 0x20(%%esp)\n\t"
      "movl 0x1fb854, %%edx\n\t"
      "fsubs 0x8(%%esp)\n\t"
      "movl 0x1fb850, %%eax\n\t"
      "movl %%edx, 0x14(%%esp)\n\t"
      "movl 0xb0c(%%edi), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "fstps 0x20(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl %%eax, 0x10(%%esp)\n\t"
      "movl 0x1fb858, %%eax\n\t"
      "movl %%edx, 0xc(%%esp)\n\t"
      "fildl 0xc(%%esp)\n\t"
      "movl %%eax, 0x18(%%esp)\n\t"
      "jge .LD3D_LazySetPointParams_4\n\t"
      "fadds 0x25fb8c\n\t"
      ".LD3D_LazySetPointParams_4:\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl $0x200a30, (%%esi)\n\t"
      "movl 0x20(%%esp), %%eax\n\t"
      "fdivrs 0x20(%%esp)\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "movl %%edx, 0x20(%%esi)\n\t"
      "addl $0x24, %%esi\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "flds 0x10(%%esp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%esi)\n\t"
      "flds 0x14(%%esp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%esi)\n\t"
      "fmuls 0x18(%%esp)\n\t"
      "fstps -0x18(%%esi)\n\t"
      "flds 0x8(%%esp)\n\t"
      "fdivs 0x20(%%esp)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%esi)\n\t"
      ".LD3D_LazySetPointParams_5:\n\t"
      "fmuls 0x253f78\n\t"
      "movl 0x1fb848, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0x80318, (%%esi)\n\t"
      "fadds 0x253398\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1f3c30]\n\t"
      "cmpl $0x1ff, %%eax\n\t"
      "jbe .LD3D_LazySetPointParams_6\n\t"
      "movl $0x1ff, %%eax\n\t"
      ".LD3D_LazySetPointParams_6:\n\t"
      "movl $0x4043c, 0xc(%%esi)\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "addl $0x14, %%esi\n\t"
      "movl %%esi, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "ret\n\t"
      :
      : [c1efe10] "m"(b1f05e0_c1efe10), [c1f3c30] "m"(b1f05e0_c1f3c30)
      : "memory");
}
#else
#error "D3D_LazySetPointParams: clang naked draft required"
#endif


/* CDevice_SetStateVB (0x1f1bc0) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void b1f1bc0_c1f1b50_tgt(void) { return; }
static void (*const b1f1bc0_c1f1b50)(void) = b1f1bc0_c1f1b50_tgt;
static void (*const b1f1bc0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void CDevice_SetStateVB(void)
{
  __asm__ volatile(
      "pushl %%ecx\n\t"
      "pushl %%ebp\n\t"
      "movl %%ecx, %%ebp\n\t"
      "movl %%ebp, 0x4(%%esp)\n\t"
      "call *%[c1f1b50]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl $0x40000000, %%eax\n\t"
      "jne .LCDevice_SetStateVB_20\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jns .LCDevice_SetStateVB_12\n\t"
      "movl 0x470(%%ebp), %%esi\n\t"
      "andl $0xbfffff7f, %%eax\n\t"
      "orl $0x300, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "testb $4, 0x4(%%esi)\n\t"
      "jne .LCDevice_SetStateVB_8\n\t"
      "movl 0xc(%%esi), %%edi\n\t"
      "leal 0xc0(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LCDevice_SetStateVB_1:\n\t"
      "movl 0x1fb508(%%ecx), %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jae .LCDevice_SetStateVB_2\n\t"
      "shll $4, %%eax\n\t"
      "leal 0x128(%%eax,%%esi,1), %%eax\n\t"
      "movl (%%eax), %%ebp\n\t"
      "leal -0x8(%%edx), %%ebx\n\t"
      "movl %%ebp, (%%ebx)\n\t"
      "movl 0x4(%%eax), %%ebp\n\t"
      "movl %%ebp, 0x4(%%ebx)\n\t"
      "movl 0x8(%%eax), %%ebp\n\t"
      "movl %%ebp, 0x8(%%ebx)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl 0x10(%%esp), %%ebp\n\t"
      "movl %%eax, 0xc(%%ebx)\n\t"
      "jmp .LCDevice_SetStateVB_3\n\t"
      ".LCDevice_SetStateVB_2:\n\t"
      "movl $2, (%%edx)\n\t"
      ".LCDevice_SetStateVB_3:\n\t"
      "addl $0x80, %%ecx\n\t"
      "addl $0x10, %%edx\n\t"
      "cmpl $0x200, %%ecx\n\t"
      "jb .LCDevice_SetStateVB_1\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "testb $4, %%dh\n\t"
      "jne .LCDevice_SetStateVB_4\n\t"
      "movl $0x4194c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateVB_4:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "testb $8, %%dh\n\t"
      "jne .LCDevice_SetStateVB_5\n\t"
      "movl $0x41950, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateVB_5:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "testb $0x10, %%dh\n\t"
      "jne .LCDevice_SetStateVB_6\n\t"
      "movl $0x4195c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateVB_6:\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "testb $0x20, %%ch\n\t"
      "jne .LCDevice_SetStateVB_7\n\t"
      "movl $0x41960, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateVB_7:\n\t"
      "movl %%eax, (%%ebp)\n\t"
      ".LCDevice_SetStateVB_8:\n\t"
      "movl $0xf, %%eax\n\t"
      "leal 0x120(%%esi), %%ecx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LCDevice_SetStateVB_9:\n\t"
      "cmpl $2, (%%ecx)\n\t"
      "jne .LCDevice_SetStateVB_10\n\t"
      "decl %%eax\n\t"
      "subl $0x10, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCDevice_SetStateVB_9\n\t"
      ".LCDevice_SetStateVB_10:\n\t"
      "pushl %%ebp\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "call *%[c1efe10]\n\t"
      "movl $0x401760, (%%eax)\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "movl $2, %%esi\n\t"
      ".LCDevice_SetStateVB_11:\n\t"
      "movl -0x8(%%ecx), %%edx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "movl 0x10(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x18(%%ecx), %%edx\n\t"
      "movl 0x20(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x28(%%ecx), %%edx\n\t"
      "movl 0x30(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl 0x38(%%ecx), %%edx\n\t"
      "movl 0x40(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0x10(%%eax)\n\t"
      "movl 0x48(%%ecx), %%edx\n\t"
      "movl 0x50(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0x14(%%eax)\n\t"
      "movl 0x58(%%ecx), %%edx\n\t"
      "movl 0x60(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0x18(%%eax)\n\t"
      "movl 0x68(%%ecx), %%edx\n\t"
      "movl 0x70(%%ecx), %%edi\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "movl 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "shll $8, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl %%edx, 0x1c(%%eax)\n\t"
      "addl $0x80, %%ecx\n\t"
      "addl $0x20, %%eax\n\t"
      "decl %%esi\n\t"
      "jne .LCDevice_SetStateVB_11\n\t"
      "movl %%eax, (%%ebp)\n\t"
      ".LCDevice_SetStateVB_12:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "movl 0x18(%%esp), %%edi\n\t"
      "jne .LCDevice_SetStateVB_13\n\t"
      "cmpl %%edi, 0x598(%%ebp)\n\t"
      "je .LCDevice_SetStateVB_19\n\t"
      ".LCDevice_SetStateVB_13:\n\t"
      "movl 0x470(%%ebp), %%esi\n\t"
      "andl $0xbffffdff, %%eax\n\t"
      "pushl %%ebp\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%edi, 0x598(%%ebp)\n\t"
      "call *%[c1efe10]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "jne .LCDevice_SetStateVB_16\n\t"
      "movl $0x41720, %%edi\n\t"
      "leal 0x28(%%esi), %%edx\n\t"
      "leal 0x1(%%ecx), %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LCDevice_SetStateVB_14:\n\t"
      "cmpl $2, 0x8(%%edx)\n\t"
      "je .LCDevice_SetStateVB_15\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%esi\n\t"
      "movl 0x1fb8e0(,%%esi,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x1fb8d8(,%%esi,4), %%esi\n\t"
      "je .LCDevice_SetStateVB_15\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "addl 0x4(%%edx), %%ecx\n\t"
      "addl 0x4(%%esi), %%ecx\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateVB_15:\n\t"
      "addl $4, %%edi\n\t"
      "addl $0x10, %%edx\n\t"
      "decl %%ebx\n\t"
      "jne .LCDevice_SetStateVB_14\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%eax, (%%ebp)\n\t"
      "popl %%ebp\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      ".LCDevice_SetStateVB_16:\n\t"
      "movl $0x41720, %%ebx\n\t"
      "addl $0x28, %%esi\n\t"
      "leal 0x1(%%ecx), %%ebp\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LCDevice_SetStateVB_17:\n\t"
      "cmpl $2, 0x8(%%esi)\n\t"
      "je .LCDevice_SetStateVB_18\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%edx\n\t"
      "movl 0x1fb8e0(,%%edx,4), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "leal 0x1fb8d8(,%%edx,4), %%edx\n\t"
      "je .LCDevice_SetStateVB_18\n\t"
      "movl (%%edx), %%ecx\n\t"
      "imull 0x18(%%esp), %%ecx\n\t"
      "addl 0x4(%%edi), %%ecx\n\t"
      "addl 0x4(%%esi), %%ecx\n\t"
      "addl 0x4(%%edx), %%ecx\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateVB_18:\n\t"
      "addl $4, %%ebx\n\t"
      "addl $0x10, %%esi\n\t"
      "decl %%ebp\n\t"
      "jne .LCDevice_SetStateVB_17\n\t"
      "movl 0x10(%%esp), %%ebp\n\t"
      "movl %%eax, (%%ebp)\n\t"
      ".LCDevice_SetStateVB_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LCDevice_SetStateVB_20:\n\t"
      "popl %%ebp\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      :
      : [c1f1b50] "m"(b1f1bc0_c1f1b50), [c1efe10] "m"(b1f1bc0_c1efe10)
      : "memory");
}
#else
#error "CDevice_SetStateVB: clang naked draft required"
#endif


/* CDevice_SetStateUP (0x1f1eb0) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void b1f1eb0_c1f1b50_tgt(void) { return; }
static void (*const b1f1eb0_c1f1b50)(void) = b1f1eb0_c1f1b50_tgt;
static void (*const b1f1eb0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void CDevice_SetStateUP(void)
{
  __asm__ volatile(
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl %%esi, 0x4(%%esp)\n\t"
      "call *%[c1f1b50]\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "je .LCDevice_SetStateUP_21\n\t"
      "andl $0xfffffeff, %%eax\n\t"
      "pushl %%ebx\n\t"
      "orl $0x80, %%eax\n\t"
      "pushl %%ebp\n\t"
      "movl 0x470(%%esi), %%ebp\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "testb $4, 0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "movl %%ebp, 0x18(%%esp)\n\t"
      "jne .LCDevice_SetStateUP_8\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "leal 0xc0(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LCDevice_SetStateUP_1:\n\t"
      "movl 0x1fb508(%%ecx), %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jae .LCDevice_SetStateUP_2\n\t"
      "shll $4, %%eax\n\t"
      "leal 0x128(%%eax,%%ebp,1), %%eax\n\t"
      "movl (%%eax), %%ebx\n\t"
      "leal -0x8(%%edx), %%esi\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%ebx\n\t"
      "movl %%ebx, 0x8(%%esi)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "jmp .LCDevice_SetStateUP_3\n\t"
      ".LCDevice_SetStateUP_2:\n\t"
      "movl $2, (%%edx)\n\t"
      ".LCDevice_SetStateUP_3:\n\t"
      "addl $0x80, %%ecx\n\t"
      "addl $0x10, %%edx\n\t"
      "cmpl $0x200, %%ecx\n\t"
      "jb .LCDevice_SetStateUP_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x4(%%ebp), %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "testb $4, %%dh\n\t"
      "jne .LCDevice_SetStateUP_4\n\t"
      "movl $0x4194c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateUP_4:\n\t"
      "movl 0x4(%%ebp), %%edx\n\t"
      "testb $8, %%dh\n\t"
      "jne .LCDevice_SetStateUP_5\n\t"
      "movl $0x41950, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateUP_5:\n\t"
      "movl 0x4(%%ebp), %%edx\n\t"
      "testb $0x10, %%dh\n\t"
      "jne .LCDevice_SetStateUP_6\n\t"
      "movl $0x4195c, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateUP_6:\n\t"
      "movl 0x4(%%ebp), %%ecx\n\t"
      "testb $0x20, %%ch\n\t"
      "jne .LCDevice_SetStateUP_7\n\t"
      "movl $0x41960, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "addl $8, %%eax\n\t"
      ".LCDevice_SetStateUP_7:\n\t"
      "movl %%eax, (%%esi)\n\t"
      ".LCDevice_SetStateUP_8:\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x7f8(%%eax), %%ecx\n\t"
      "addl $0x7f4, %%eax\n\t"
      "leal 0x3c(%%ebp), %%edx\n\t"
      "movl $2, 0x14(%%esp)\n\t"
      ".LCDevice_SetStateUP_9:\n\t"
      "movl -0xc(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_10\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl -0x10(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_10:\n\t"
      "movl 0x4(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_11\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl (%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_11:\n\t"
      "movl 0x14(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_12\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x10(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_12:\n\t"
      "movl 0x24(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_13\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x20(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_13:\n\t"
      "movl 0x34(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_14\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x30(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_14:\n\t"
      "movl 0x44(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_15\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x40(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_15:\n\t"
      "movl 0x54(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_16\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x50(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_16:\n\t"
      "movl 0x64(%%edx), %%ebp\n\t"
      "cmpl $2, %%ebp\n\t"
      "je .LCDevice_SetStateUP_17\n\t"
      "movl %%ebp, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl 0x1f9f88(%%edi), %%edi\n\t"
      "andl $0xf, %%ebp\n\t"
      "movzbl 0x1f9f90(%%ebp), %%ebp\n\t"
      "imull %%ebp, %%edi\n\t"
      "addl $3, %%edi\n\t"
      "shrl $2, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x60(%%edx), %%ebp\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebp, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $8, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      ".LCDevice_SetStateUP_17:\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "addl $0x80, %%edx\n\t"
      "decl %%edi\n\t"
      "movl %%edi, 0x14(%%esp)\n\t"
      "jne .LCDevice_SetStateUP_9\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "movl 0x7f8(%%edi), %%ecx\n\t"
      "leal 0x7f8(%%edi), %%eax\n\t"
      "movl %%esi, 0x874(%%edi)\n\t"
      "movl %%ebx, 0x7e8(%%edi)\n\t"
      "movl %%ecx, 0x7ec(%%edi)\n\t"
      "movl 0x7ec(%%edi,%%esi,8), %%edx\n\t"
      "movl 0x7f0(%%edi,%%esi,8), %%ebp\n\t"
      "negl %%edx\n\t"
      "shll $2, %%edx\n\t"
      "subl %%ebp, %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl $1, %%esi\n\t"
      "movl %%edx, 0x7f0(%%edi)\n\t"
      "jbe .LCDevice_SetStateUP_19\n\t"
      "decl %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LCDevice_SetStateUP_18:\n\t"
      "movl -0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl (%%eax), %%ebx\n\t"
      "shll $2, %%ecx\n\t"
      "subl %%ecx, %%edx\n\t"
      "subl %%ebx, %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "decl %%esi\n\t"
      "jne .LCDevice_SetStateUP_18\n\t"
      ".LCDevice_SetStateUP_19:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl $0x401760, (%%eax)\n\t"
      "addl $4, %%eax\n\t"
      "addl $0x30, %%ecx\n\t"
      "movl $0x10, %%edx\n\t"
      ".LCDevice_SetStateUP_20:\n\t"
      "movl (%%ecx), %%esi\n\t"
      "movl %%esi, (%%eax)\n\t"
      "addl $4, %%eax\n\t"
      "addl $0x10, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LCDevice_SetStateUP_20\n\t"
      "movl %%eax, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      ".LCDevice_SetStateUP_21:\n\t"
      "popl %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f1b50] "m"(b1f1eb0_c1f1b50), [c1efe10] "m"(b1f1eb0_c1efe10)
      : "memory");
}
#else
#error "CDevice_SetStateUP: clang naked draft required"
#endif


/* CDevice_FreeFrameBuffers (0x1f30c0) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void b1f30c0_c1edba0_tgt(void) { return; }
static void (*const b1f30c0_c1edba0)(void) = b1f30c0_c1edba0_tgt;
static void (*const b1f30c0_c1e8d30)(void) = D3DDevice_SetTile;

__attribute__((naked, noinline))
void CDevice_FreeFrameBuffers(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *0x2532ac\n\t"
      "xorl %%ebp, %%ebp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCDevice_FreeFrameBuffers_1\n\t"
      "movl 0x2308(%%esi), %%eax\n\t"
      "pushl %%ebp\n\t"
      "pushl $1\n\t"
      "pushl $9\n\t"
      "pushl %%eax\n\t"
      "call *0x2532b0\n\t"
      ".LCDevice_FreeFrameBuffers_1:\n\t"
      "movl 0x40c(%%esi), %%eax\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LCDevice_FreeFrameBuffers_3\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "cmpl %%ebp, %%ecx\n\t"
      "je .LCDevice_FreeFrameBuffers_2\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LCDevice_FreeFrameBuffers_2:\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x40c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1edba0]\n\t"
      "movl %%ebp, 0x40c(%%esi)\n\t"
      ".LCDevice_FreeFrameBuffers_3:\n\t"
      "movl 0x410(%%esi), %%eax\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LCDevice_FreeFrameBuffers_5\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "cmpl %%ebp, %%ecx\n\t"
      "je .LCDevice_FreeFrameBuffers_4\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LCDevice_FreeFrameBuffers_4:\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x410(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1edba0]\n\t"
      "movl %%ebp, 0x410(%%esi)\n\t"
      ".LCDevice_FreeFrameBuffers_5:\n\t"
      "cmpl %%ebp, 0x2198(%%esi)\n\t"
      "movl 0x2531f4, %%ebx\n\t"
      "je .LCDevice_FreeFrameBuffers_6\n\t"
      "pushl %%ebp\n\t"
      "pushl $1\n\t"
      "call *%[c1e8d30]\n\t"
      "movl 0x2198(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%ebx\n\t"
      "movl $6, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x219c(%%esi), %%edi\n\t"
      "movl %%ebp, 0x2198(%%esi)\n\t"
      "rep stosl\n\t"
      ".LCDevice_FreeFrameBuffers_6:\n\t"
      "cmpl %%ebp, 0x2144(%%esi)\n\t"
      "je .LCDevice_FreeFrameBuffers_7\n\t"
      "pushl %%ebp\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1e8d30]\n\t"
      "movl 0x2144(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%%ebx\n\t"
      "movl $0x12, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x2150(%%esi), %%edi\n\t"
      "movl %%ebp, 0x2144(%%esi)\n\t"
      "rep stosl\n\t"
      ".LCDevice_FreeFrameBuffers_7:\n\t"
      "movl 0x2148(%%esi), %%eax\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LCDevice_FreeFrameBuffers_8\n\t"
      "pushl %%eax\n\t"
      "call *%%ebx\n\t"
      "movl %%ebp, 0x2148(%%esi)\n\t"
      ".LCDevice_FreeFrameBuffers_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1edba0] "m"(b1f30c0_c1edba0), [c1e8d30] "m"(b1f30c0_c1e8d30)
      : "memory");
}
#else
#error "CDevice_FreeFrameBuffers: clang naked draft required"
#endif


/* CDevice_InitializeFrameBuffers (0x1f31c0) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void b1f31c0_c1f3cd0_tgt(void) { return; }
static void (*const b1f31c0_c1f3cd0)(void) = b1f31c0_c1f3cd0_tgt;
static void b1f31c0_c1f3e00_tgt(void) { return; }
static void (*const b1f31c0_c1f3e00)(void) = b1f31c0_c1f3e00_tgt;
static void b1f31c0_c1f4630_tgt(void) { return; }
static void (*const b1f31c0_c1f4630)(void) = b1f31c0_c1f4630_tgt;
static void b1f31c0_c1ef300_tgt(void) { return; }
static void (*const b1f31c0_c1ef300)(void) = b1f31c0_c1ef300_tgt;
static void b1f31c0_c1e77d0_tgt(void) { return; }
static void (*const b1f31c0_c1e77d0)(void) = b1f31c0_c1e77d0_tgt;
static void (*const b1f31c0_c1e8d30)(void) = D3DDevice_SetTile;
static void (*const b1f31c0_c1efe10)(void) = XMETAL_StartPush;

__attribute__((naked, noinline))
void CDevice_InitializeFrameBuffers(void)
{
  __asm__ volatile(
      "subl $0x48, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x58(%%esp), %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%ebp\n\t"
      "movl $1, 0x18(%%esp)\n\t"
      "jb .LCDevice_InitializeFrameBuffers_1\n\t"
      "movl %%eax, 0x18(%%esp)\n\t"
      ".LCDevice_InitializeFrameBuffers_1:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1f3cd0]\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, 0x3c(%%esp)\n\t"
      "call *%[c1f3cd0]\n\t"
      "movl 0x30(%%esi), %%ecx\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%eax, 0x28(%%esp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%ecx, 0x2b64(%%ebp)\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%eax, 0x21b8(%%ebp)\n\t"
      "movl %%eax, 0x2c(%%esp)\n\t"
      "movl %%ecx, 0x214c(%%ebp)\n\t"
      "movl %%edx, 0x21b4(%%ebp)\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "andl $0x3000, %%edi\n\t"
      "movl %%edx, 0x3c(%%esp)\n\t"
      "movl %%ecx, 0x20(%%esp)\n\t"
      "movl %%eax, 0x1fb8b0\n\t"
      "movl %%edi, 0x30(%%esp)\n\t"
      "jne .LCDevice_InitializeFrameBuffers_2\n\t"
      "movl $0x11, %%eax\n\t"
      "movl %%eax, 0x1fb8b0\n\t"
      ".LCDevice_InitializeFrameBuffers_2:\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xf0000, %%ecx\n\t"
      "cmpl $0x30000, %%ecx\n\t"
      "ja .LCDevice_InitializeFrameBuffers_5\n\t"
      "je .LCDevice_InitializeFrameBuffers_4\n\t"
      "cmpl $0x10000, %%ecx\n\t"
      "je .LCDevice_InitializeFrameBuffers_3\n\t"
      "cmpl $0x20000, %%ecx\n\t"
      "jne .LCDevice_InitializeFrameBuffers_6\n\t"
      "movl $0x11, %%ebx\n\t"
      "jmp .LCDevice_InitializeFrameBuffers_6\n\t"
      ".LCDevice_InitializeFrameBuffers_3:\n\t"
      "movl $0x1c, %%ebx\n\t"
      "jmp .LCDevice_InitializeFrameBuffers_6\n\t"
      ".LCDevice_InitializeFrameBuffers_4:\n\t"
      "movl $0x1e, %%ebx\n\t"
      "jmp .LCDevice_InitializeFrameBuffers_6\n\t"
      ".LCDevice_InitializeFrameBuffers_5:\n\t"
      "cmpl $0x40000, %%ecx\n\t"
      "jne .LCDevice_InitializeFrameBuffers_6\n\t"
      "movl $0x12, %%ebx\n\t"
      ".LCDevice_InitializeFrameBuffers_6:\n\t"
      "movl %%eax, %%esi\n\t"
      "shrl $4, %%esi\n\t"
      "andl $0xf, %%esi\n\t"
      "andl $0xf, %%eax\n\t"
      "imull %%edx, %%esi\n\t"
      "imull 0x2c(%%esp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x2c(%%esp)\n\t"
      "call *%[c1f3e00]\n\t"
      "leal 0x10(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x28(%%esp), %%edx\n\t"
      "leal 0x18(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f4630]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, 0x34(%%esp)\n\t"
      "je .LCDevice_InitializeFrameBuffers_7\n\t"
      "movl $1, 0x1c(%%esp)\n\t"
      "jmp .LCDevice_InitializeFrameBuffers_8\n\t"
      ".LCDevice_InitializeFrameBuffers_7:\n\t"
      "movl 0x20(%%esp), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%esp)\n\t"
      ".LCDevice_InitializeFrameBuffers_8:\n\t"
      "movl 0x1c(%%esp), %%edi\n\t"
      "imull %%eax, %%edi\n\t"
      "pushl $0x404\n\t"
      "pushl $0x4000\n\t"
      "pushl $0x3ffb000\n\t"
      "addl $0x3fff, %%edi\n\t"
      "pushl $0\n\t"
      "andl $0xffffc000, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *0x25320c\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDevice_InitializeFrameBuffers_14\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ebx, 0x2144(%%ebp)\n\t"
      "jbe .LCDevice_InitializeFrameBuffers_10\n\t"
      "leal 0x2150(%%ebp), %%edx\n\t"
      "movl %%edx, 0x1c(%%esp)\n\t"
      "movl %%eax, 0x20(%%esp)\n\t"
      ".LCDevice_InitializeFrameBuffers_9:\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "movl 0x1c(%%esp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ef300]\n\t"
      "movl 0x1c(%%esp), %%ecx\n\t"
      "movl 0x34(%%esp), %%edx\n\t"
      "movl 0x20(%%esp), %%eax\n\t"
      "addl $0x18, %%ecx\n\t"
      "addl %%edx, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, 0x1c(%%esp)\n\t"
      "movl %%eax, 0x20(%%esp)\n\t"
      "jne .LCDevice_InitializeFrameBuffers_9\n\t"
      ".LCDevice_InitializeFrameBuffers_10:\n\t"
      "cmpl $0x780, %%esi\n\t"
      "je .LCDevice_InitializeFrameBuffers_11\n\t"
      "movl 0x2144(%%ebp), %%eax\n\t"
      "leal 0x2150(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0, 0x44(%%esp)\n\t"
      "movl %%eax, 0x48(%%esp)\n\t"
      "movl %%edi, 0x4c(%%esp)\n\t"
      "call *%[c1e77d0]\n\t"
      "leal 0x40(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl %%eax, 0x54(%%esp)\n\t"
      "call *%[c1e8d30]\n\t"
      ".LCDevice_InitializeFrameBuffers_11:\n\t"
      "movl 0x5c(%%esp), %%eax\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCDevice_InitializeFrameBuffers_13\n\t"
      "movl 0x28(%%esp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f3e00]\n\t"
      "leal 0x10(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x18(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%esp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f4630]\n\t"
      "pushl $0x404\n\t"
      "pushl $0x4000\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x3ffb000\n\t"
      "addl $0x3fff, %%edi\n\t"
      "pushl $0\n\t"
      "andl $0xffffc000, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *0x25320c\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDevice_InitializeFrameBuffers_14\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x219c(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, 0x2198(%%ebp)\n\t"
      "call *%[c1ef300]\n\t"
      "cmpl $0x780, %%esi\n\t"
      "je .LCDevice_InitializeFrameBuffers_13\n\t"
      "leal 0x219c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x80000001, 0x44(%%esp)\n\t"
      "movl %%ebx, 0x48(%%esp)\n\t"
      "movl %%edi, 0x4c(%%esp)\n\t"
      "call *%[c1e77d0]\n\t"
      "movl %%eax, 0x4c(%%esp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x54(%%esp)\n\t"
      "movl %%eax, 0x50(%%esp)\n\t"
      "movl 0x28(%%esp), %%eax\n\t"
      "movb 0x1f9d58(%%eax), %%cl\n\t"
      "andb $0x3c, %%cl\n\t"
      "cmpb $0x20, %%cl\n\t"
      "jne .LCDevice_InitializeFrameBuffers_12\n\t"
      "movl $0x84000001, 0x40(%%esp)\n\t"
      ".LCDevice_InitializeFrameBuffers_12:\n\t"
      "leal 0x40(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c1e8d30]\n\t"
      ".LCDevice_InitializeFrameBuffers_13:\n\t"
      "movl 0x30(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCDevice_InitializeFrameBuffers_17\n\t"
      "movl 0x38(%%esp), %%edx\n\t"
      "leal 0x10(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x30(%%esp), %%eax\n\t"
      "leal 0x18(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x44(%%esp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1f4630]\n\t"
      "movl 0x18(%%esp), %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "pushl $0x404\n\t"
      "imull %%ebx, %%edx\n\t"
      "pushl $0x4000\n\t"
      "pushl $0x3ffb000\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *0x25320c\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LCDevice_InitializeFrameBuffers_15\n\t"
      ".LCDevice_InitializeFrameBuffers_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl $0x8007000e, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $0x48, %%esp\n\t"
      "ret\n\t"
      ".LCDevice_InitializeFrameBuffers_15:\n\t"
      "cmpl $1, %%ebx\n\t"
      "movl %%esi, 0x2148(%%ebp)\n\t"
      "jb .LCDevice_InitializeFrameBuffers_17\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "leal 0x2168(%%ebp), %%ebx\n\t"
      "movl %%eax, 0x5c(%%esp)\n\t"
      ".LCDevice_InitializeFrameBuffers_16:\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1ef300]\n\t"
      "movl 0x5c(%%esp), %%eax\n\t"
      "addl %%edi, %%esi\n\t"
      "addl $0x18, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x5c(%%esp)\n\t"
      "jne .LCDevice_InitializeFrameBuffers_16\n\t"
      ".LCDevice_InitializeFrameBuffers_17:\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1efe10]\n\t"
      "movl 0x30(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $2, %%ecx\n\t"
      "jne .LCDevice_InitializeFrameBuffers_18\n\t"
      "movl 0x214c(%%ebp), %%ecx\n\t"
      ".LCDevice_InitializeFrameBuffers_18:\n\t"
      "movl $0xc0120, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      "movl $1, 0x8(%%eax)\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      "popl %%edi\n\t"
      "addl $0x10, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ebp)\n\t"
      "popl %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "addl $0x48, %%esp\n\t"
      "ret\n\t"
      :
      : [c1f3cd0] "m"(b1f31c0_c1f3cd0), [c1f3e00] "m"(b1f31c0_c1f3e00), [c1f4630] "m"(b1f31c0_c1f4630), [c1ef300] "m"(b1f31c0_c1ef300), [c1e77d0] "m"(b1f31c0_c1e77d0), [c1e8d30] "m"(b1f31c0_c1e8d30), [c1efe10] "m"(b1f31c0_c1efe10)
      : "memory");
}
#else
#error "CDevice_InitializeFrameBuffers: clang naked draft required"
#endif


/* Lock3DSurface (0x1f4590) — XBE naked draft (batch 345). */
#if defined(__clang__)
static void (*const b1f4590_c1efd80)(void) = D3D_BlockOnResource;
static void b1f4590_c1f4270_tgt(void) { return; }
static void (*const b1f4590_c1f4270)(void) = b1f4590_c1f4270_tgt;

__attribute__((naked, noinline))
void Lock3DSurface(void)
{
  __asm__ volatile(
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movb 0x20(%%esp), %%bl\n\t"
      "testb $0x20, %%bl\n\t"
      "pushl %%ebp\n\t"
      "movl 0x14(%%esp), %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LLock3DSurface_1\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1efd80]\n\t"
      ".LLock3DSurface_1:\n\t"
      "leal 0x10(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x24(%%esp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x2c(%%esp), %%edx\n\t"
      "leal 0x2c(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%esp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ebp\n\t"
      "call *%[c1f4270]\n\t"
      "testb $0x40, %%bl\n\t"
      "movl 0x2c(%%esp), %%ecx\n\t"
      "je .LLock3DSurface_2\n\t"
      "orl $0xf0000000, %%ecx\n\t"
      ".LLock3DSurface_2:\n\t"
      "movl 0x28(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x1c(%%esp), %%esi\n\t"
      "movl 0x20(%%esp), %%edi\n\t"
      "je .LLock3DSurface_3\n\t"
      "movzbl 0xd(%%ebp), %%edx\n\t"
      "movzbl 0x1f9d58(%%edx), %%edx\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "andl $0x3c, %%edx\n\t"
      "imull %%edi, %%ebx\n\t"
      "imull (%%eax), %%edx\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "imull %%esi, %%eax\n\t"
      "shrl $3, %%edx\n\t"
      "addl %%ebx, %%edx\n\t"
      "addl %%ecx, %%eax\n\t"
      "leal (%%eax,%%edx,1), %%ecx\n\t"
      ".LLock3DSurface_3:\n\t"
      "movl 0x24(%%esp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "popl %%edi\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "popl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c1efd80] "m"(b1f4590_c1efd80), [c1f4270] "m"(b1f4590_c1f4270)
      : "memory");
}
#else
#error "Lock3DSurface: clang naked draft required"
#endif


/* CMiniport_GetDisplayCapabilities (0x1f4880) — XBE naked draft (batch 370). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CMiniport_GetDisplayCapabilities(void)
{
  __asm__ volatile(
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0x1fb468\n\t"
      "jne .LCMiniport_GetDisplayCapabilities_1\n\t"
      "pushl $0x1fb468\n\t"
      "pushl %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "call *0x2532b0\n\t"
      ".LCMiniport_GetDisplayCapabilities_1:\n\t"
      "movl 0x1fb468, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CMiniport_GetDisplayCapabilities: clang naked draft required"
#endif


/* CMiniport_IsFlipPending (0x1f4aa0) — XBE naked draft (batch 393). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CMiniport_IsFlipPending(void)
{
  __asm__ volatile(
      "movl 0x1dc(%%ecx), %%eax\n\t"
      "movl 0x1b4(%%ecx,%%eax,8), %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CMiniport_IsFlipPending: clang naked draft required"
#endif


/* D3D_AllocContiguousMemory (0x1f5390) — XBE naked draft (batch 384). */
#if defined(__clang__)
static void *__stdcall (*const b1f5390_c1d36d4)(size_t size, unsigned int addr, unsigned int alignment, unsigned int protect) = (void *)XPhysicalAlloc;

__attribute__((naked, noinline))
void D3D_AllocContiguousMemory(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "pushl $0x404\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d36d4]\n\t"
      "ret\n\t"
      :
      : [c1d36d4] "m"(b1f5390_c1d36d4)
      : "memory");
}
#else
#error "D3D_AllocContiguousMemory: clang naked draft required"
#endif


/* CMiniport_CreateCtxDmaObject (0x1f5b5b) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void b1f5b5b_c1f5b01_tgt(void) { return; }
static void (*const b1f5b5b_c1f5b01)(void) = b1f5b5b_c1f5b01_tgt;

__attribute__((naked, noinline))
void CMiniport_CreateCtxDmaObject(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[c1f5b01]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal 0x1a0(%%edx), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x1(%%edx), %%ebx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "orl $3, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "decl %%ecx\n\t"
      "decl %%ecx\n\t"
      "je .LCMiniport_CreateCtxDmaObject_2\n\t"
      "decl %%ecx\n\t"
      "je .LCMiniport_CreateCtxDmaObject_1\n\t"
      "subl $0x3a, %%ecx\n\t"
      "jne .LCMiniport_CreateCtxDmaObject_4\n\t"
      "pushl $0x3d\n\t"
      "jmp .LCMiniport_CreateCtxDmaObject_3\n\t"
      ".LCMiniport_CreateCtxDmaObject_1:\n\t"
      "pushl $3\n\t"
      "jmp .LCMiniport_CreateCtxDmaObject_3\n\t"
      ".LCMiniport_CreateCtxDmaObject_2:\n\t"
      "pushl $2\n\t"
      ".LCMiniport_CreateCtxDmaObject_3:\n\t"
      "popl %%esi\n\t"
      ".LCMiniport_CreateCtxDmaObject_4:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "shll $0x14, %%ecx\n\t"
      "orl $0x3000, %%ecx\n\t"
      "orl %%ecx, %%esi\n\t"
      "cmpl $2, -0x4(%%ebp)\n\t"
      "je .LCMiniport_CreateCtxDmaObject_6\n\t"
      "cmpl $3, -0x4(%%ebp)\n\t"
      "jne .LCMiniport_CreateCtxDmaObject_5\n\t"
      "orl $0x30000, %%esi\n\t"
      "jmp .LCMiniport_CreateCtxDmaObject_6\n\t"
      ".LCMiniport_CreateCtxDmaObject_5:\n\t"
      "cmpl $1, -0x4(%%ebp)\n\t"
      "jne .LCMiniport_CreateCtxDmaObject_6\n\t"
      "orl $0x20000, %%esi\n\t"
      ".LCMiniport_CreateCtxDmaObject_6:\n\t"
      "movl %%edx, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "addl %%edi, %%ecx\n\t"
      "movl %%eax, 0x700008(%%ecx)\n\t"
      "movl %%eax, 0x70000c(%%ecx)\n\t"
      "orl $0x8000, %%esi\n\t"
      "leal 0x70000(%%edx), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movl %%esi, (%%eax,%%edi,1)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, 0x700004(%%ecx)\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, %%edi\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andw $0, 0x6(%%ecx)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, 0x8(%%ecx)\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "incl %%eax\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1f5b01] "m"(b1f5b5b_c1f5b01)
      : "memory");
}
#else
#error "CMiniport_CreateCtxDmaObject: clang naked draft required"
#endif


/* CMiniport_InitHardware (0x1f5d4d) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void b1f5d4d_c1f5850_tgt(void) { return; }
static void (*const b1f5d4d_c1f5850)(void) = b1f5d4d_c1f5850_tgt;
static void b1f5d4d_c1f587b_tgt(void) { return; }
static void (*const b1f5d4d_c1f587b)(void) = b1f5d4d_c1f587b_tgt;
static void b1f5d4d_c1f58bc_tgt(void) { return; }
static void (*const b1f5d4d_c1f58bc)(void) = b1f5d4d_c1f58bc_tgt;
static void b1f5d4d_c1f59c6_tgt(void) { return; }
static void (*const b1f5d4d_c1f59c6)(void) = b1f5d4d_c1f59c6_tgt;

__attribute__((naked, noinline))
void CMiniport_InitHardware(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1f52c0\n\t"
      "leal 0x88(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531c8\n\t"
      "andb $0, 0x1f8(%%esi)\n\t"
      "andb $0, 0x1e8(%%esi)\n\t"
      "leal 0x200(%%esi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%eax, 0x204(%%esi)\n\t"
      "movl %%eax, (%%eax)\n\t"
      "leal 0x1f0(%%esi), %%eax\n\t"
      "incl %%ebx\n\t"
      "movl %%esi, %%ecx\n\t"
      "movb $4, 0x1fa(%%esi)\n\t"
      "movl %%ebx, 0x1fc(%%esi)\n\t"
      "movb $4, 0x1ea(%%esi)\n\t"
      "movl %%ebx, 0x1ec(%%esi)\n\t"
      "movl %%eax, 0x1f4(%%esi)\n\t"
      "movl %%eax, (%%eax)\n\t"
      "call *%[c1f5850]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMiniport_InitHardware_2\n\t"
      ".LCMiniport_InitHardware_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LCMiniport_InitHardware_8\n\t"
      ".LCMiniport_InitHardware_2:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1f587b]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMiniport_InitHardware_1\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "call *0x253278\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl -0xc(%%ebp)\n\t"
      "leal 0x18(%%esi), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1f4b20\n\t"
      "pushl %%edi\n\t"
      "call *0x253288\n\t"
      "pushl %%edi\n\t"
      "call *0x253284\n\t"
      "testb %%al, %%al\n\t"
      "jne .LCMiniport_InitHardware_4\n\t"
      ".LCMiniport_InitHardware_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LCMiniport_InitHardware_7\n\t"
      ".LCMiniport_InitHardware_4:\n\t"
      "andl $0, 0x1a8(%%esi)\n\t"
      "leal 0x1a4(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl $0x1f4f90, (%%eax)\n\t"
      "call *0x253280\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1f58bc]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMiniport_InitHardware_3\n\t"
      "leal 0x314(%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $2, -0x8(%%ebp)\n\t"
      "movl $0x100, %%edx\n\t"
      ".LCMiniport_InitHardware_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCMiniport_InitHardware_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl $0xffffff00, %%edi\n\t"
      "movb %%al, (%%edi,%%ecx,1)\n\t"
      "movl $0x100, %%edi\n\t"
      "movb %%al, (%%ecx)\n\t"
      "movb %%al, (%%edi,%%ecx,1)\n\t"
      "incl %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jb .LCMiniport_InitHardware_6\n\t"
      "addl $0x300, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .LCMiniport_InitHardware_5\n\t"
      "movw $0x80c0, %%dx\n\t"
      "movb %%bl, %%al\n\t"
      "movl %%esi, %%ecx\n\t"
      ".byte 0xee\n\t"
      "movl %%ebx, 0xa4(%%esi)\n\t"
      "call *%[c1f59c6]\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      ".LCMiniport_InitHardware_7:\n\t"
      "popl %%edi\n\t"
      ".LCMiniport_InitHardware_8:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1f5850] "m"(b1f5d4d_c1f5850), [c1f587b] "m"(b1f5d4d_c1f587b), [c1f58bc] "m"(b1f5d4d_c1f58bc), [c1f59c6] "m"(b1f5d4d_c1f59c6)
      : "memory");
}
#else
#error "CMiniport_InitHardware: clang naked draft required"
#endif


/* D3D_ClearStateBlockFlags (0x1f9165) — XBE naked draft (batch 337). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3D_ClearStateBlockFlags(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x81, %%ecx\n\t"
      "movl $0x1fe6c0, %%edi\n\t"
      "rep stosl\n\t"
      "movl 0x480(%%edx), %%ecx\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x484(%%edx), %%eax\n\t"
      "cmpl %%esi, (%%eax)\n\t"
      "jbe .LD3D_ClearStateBlockFlags_2\n\t"
      "addl $0x68, %%ecx\n\t"
      ".LD3D_ClearStateBlockFlags_1:\n\t"
      "andl $0xfffffff9, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $0x90, %%ecx\n\t"
      "cmpl (%%eax), %%esi\n\t"
      "jb .LD3D_ClearStateBlockFlags_1\n\t"
      ".LD3D_ClearStateBlockFlags_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "D3D_ClearStateBlockFlags: clang naked draft required"
#endif


/* D3DDevice_BeginStateBlock (0x1f91a1) — XBE naked draft (batch 393). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_BeginStateBlock(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "orl $0x20, 0xc(%%eax)\n\t"
      ".byte 0xe9, 0xb6, 0xff, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_BeginStateBlock: clang naked draft required"
#endif


/* D3DDevice_Suspend (0x1f91af) — XBE naked draft (batch 393). */
#if defined(__clang__)
static void (*const b1f91af_c1f1bc0)(void) = (void *)CDevice_SetStateVB;

__attribute__((naked, noinline))
void D3DDevice_Suspend(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c1f1bc0]\n\t"
      "ret\n\t"
      :
      : [c1f1bc0] "m"(b1f91af_c1f1bc0)
      : "memory");
}
#else
#error "D3DDevice_Suspend: clang naked draft required"
#endif


/* D3D_RecordStateBlock (0x1f92f0) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void b1f92f0_c1ed8f0_tgt(void) { return; }
static void (*const b1f92f0_c1ed8f0)(void) = b1f92f0_c1ed8f0_tgt;
static void (*const b1f92f0_c1e6e60)(void) = D3DDevice_GetLightEnable;
static void *__stdcall (*const b1f92f0_c1d0bb9)(unsigned int flags, unsigned int size) = (void *)FUN_001d0bb9;

__attribute__((naked, noinline))
void D3D_RecordStateBlock(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x1fe6a0, %%edi\n\t"
      "movl 0x480(%%edi), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x3c\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "popl %%ebx\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movl %%esi, (%%eax)\n\t"
      ".LD3D_RecordStateBlock_1:\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "leal 0xba0(%%edi), %%eax\n\t"
      "movl $0x1fe6c0, %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_2:\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LD3D_RecordStateBlock_4\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_3\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "incl (%%esi)\n\t"
      "testl %%eax, %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "je .LD3D_RecordStateBlock_3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed8f0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      ".LD3D_RecordStateBlock_3:\n\t"
      "addl $8, %%ebx\n\t"
      ".LD3D_RecordStateBlock_4:\n\t"
      "incl -0xc(%%ebp)\n\t"
      "pushl $4\n\t"
      "popl %%ecx\n\t"
      "addl %%ecx, -0x14(%%ebp)\n\t"
      "cmpl %%ecx, -0xc(%%ebp)\n\t"
      "jb .LD3D_RecordStateBlock_2\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "je .LD3D_RecordStateBlock_6\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_5\n\t"
      "movl 0x414(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $1, 0x4(%%esi)\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "je .LD3D_RecordStateBlock_5\n\t"
      "incl (%%eax)\n\t"
      ".LD3D_RecordStateBlock_5:\n\t"
      "addl %%ecx, %%ebx\n\t"
      ".LD3D_RecordStateBlock_6:\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "je .LD3D_RecordStateBlock_8\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_7\n\t"
      "movl 0x474(%%edi), %%eax\n\t"
      "testb $1, %%al\n\t"
      "movl $1, 0x8(%%esi)\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "je .LD3D_RecordStateBlock_7\n\t"
      "movl 0x470(%%edi), %%eax\n\t"
      "incl (%%eax)\n\t"
      ".LD3D_RecordStateBlock_7:\n\t"
      "addl %%ecx, %%ebx\n\t"
      ".LD3D_RecordStateBlock_8:\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LD3D_RecordStateBlock_10\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_9\n\t"
      "movl 0x47c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $1, 0xc(%%esi)\n\t"
      "movl 0x478(%%edi), %%ecx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "je .LD3D_RecordStateBlock_9\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed8f0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      ".LD3D_RecordStateBlock_9:\n\t"
      "addl $8, %%ebx\n\t"
      ".LD3D_RecordStateBlock_10:\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "andl $0, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_11:\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LD3D_RecordStateBlock_13\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_12\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x1fb8e0(%%eax), %%eax\n\t"
      "incl 0x10(%%esi)\n\t"
      "testl %%eax, %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x1fb8d8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "je .LD3D_RecordStateBlock_12\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed8f0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      ".LD3D_RecordStateBlock_12:\n\t"
      "addl $0xc, %%ebx\n\t"
      ".LD3D_RecordStateBlock_13:\n\t"
      "addl $0xc, -0x14(%%ebp)\n\t"
      "incl -0xc(%%ebp)\n\t"
      "cmpl $0xc0, -0x14(%%ebp)\n\t"
      "jb .LD3D_RecordStateBlock_11\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal 0xbc0(%%edi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_14:\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LD3D_RecordStateBlock_16\n\t"
      "cmpl $0, 0x414(%%edi)\n\t"
      "je .LD3D_RecordStateBlock_16\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_15\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl 0x14(%%eax)\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_15:\n\t"
      "addl $0x14, %%ebx\n\t"
      "addl $0x14, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_16:\n\t"
      "addl $0x10, -0xc(%%ebp)\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x10, %%ecx\n\t"
      "jb .LD3D_RecordStateBlock_14\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal 0xcc0(%%edi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_17:\n\t"
      "movb (%%edx), %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LD3D_RecordStateBlock_19\n\t"
      "cmpl $0x60, %%ecx\n\t"
      "jb .LD3D_RecordStateBlock_19\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_18\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl 0x18(%%eax)\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_18:\n\t"
      "addl $0x14, %%ebx\n\t"
      "addl $0x14, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_19:\n\t"
      "addl $0x10, -0xc(%%ebp)\n\t"
      "incl %%ecx\n\t"
      "cmpl $0xc0, %%ecx\n\t"
      "jb .LD3D_RecordStateBlock_17\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3D_RecordStateBlock_20:\n\t"
      "movb (%%edx), %%cl\n\t"
      "incl %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LD3D_RecordStateBlock_23\n\t"
      "cmpl $0, 0x414(%%edi)\n\t"
      "jne .LD3D_RecordStateBlock_21\n\t"
      "cmpl $0x38, %%eax\n\t"
      "jbe .LD3D_RecordStateBlock_23\n\t"
      "cmpl $0x74, %%eax\n\t"
      "je .LD3D_RecordStateBlock_23\n\t"
      ".LD3D_RecordStateBlock_21:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_22\n\t"
      "incl 0x1c(%%esi)\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x1fb698(,%%eax,4), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      ".LD3D_RecordStateBlock_22:\n\t"
      "addl $8, %%ebx\n\t"
      ".LD3D_RecordStateBlock_23:\n\t"
      "incl %%eax\n\t"
      "cmpl $0x90, %%eax\n\t"
      "jb .LD3D_RecordStateBlock_20\n\t"
      "andl $0, -0x14(%%ebp)\n\t"
      "movl $0x1fb498, -0x4(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_24:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_25:\n\t"
      "movb (%%edx), %%cl\n\t"
      "incl %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LD3D_RecordStateBlock_27\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_26\n\t"
      "incl 0x20(%%esi)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      ".LD3D_RecordStateBlock_26:\n\t"
      "addl $0xc, %%ebx\n\t"
      ".LD3D_RecordStateBlock_27:\n\t"
      "addl $0x80, -0xc(%%ebp)\n\t"
      "incl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "jb .LD3D_RecordStateBlock_25\n\t"
      "incl -0x14(%%ebp)\n\t"
      "addl $4, -0x4(%%ebp)\n\t"
      "cmpl $0x20, -0x14(%%ebp)\n\t"
      "jb .LD3D_RecordStateBlock_24\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal 0x880(%%edi), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_28:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb (%%eax), %%al\n\t"
      "incl -0x4(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "je .LD3D_RecordStateBlock_30\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_29\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl 0x24(%%eax)\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "pushl $0x10\n\t"
      "popl %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "rep movsl\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_29:\n\t"
      "addl $0x44, %%ebx\n\t"
      "addl $0x44, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_30:\n\t"
      "addl $0x40, -0xc(%%ebp)\n\t"
      "incl %%edx\n\t"
      "cmpl $0xa, %%edx\n\t"
      "jb .LD3D_RecordStateBlock_28\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb (%%eax), %%al\n\t"
      "incl -0x4(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "je .LD3D_RecordStateBlock_32\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_31\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "pushl $6\n\t"
      "addl $0xb00, %%esi\n\t"
      "popl %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "movl $1, 0x28(%%eax)\n\t"
      "rep movsl\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_31:\n\t"
      "addl $0x18, %%ebx\n\t"
      ".LD3D_RecordStateBlock_32:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb (%%eax), %%al\n\t"
      "incl -0x4(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "je .LD3D_RecordStateBlock_34\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_33\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "pushl $0x11\n\t"
      "addl $0xb18, %%esi\n\t"
      "popl %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "movl $1, 0x2c(%%eax)\n\t"
      "rep movsl\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_33:\n\t"
      "addl $0x44, %%ebx\n\t"
      ".LD3D_RecordStateBlock_34:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LD3D_RecordStateBlock_36\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_35\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "pushl $0x11\n\t"
      "addl $0xb5c, %%esi\n\t"
      "popl %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "movl $1, 0x30(%%eax)\n\t"
      "rep movsl\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_35:\n\t"
      "addl $0x44, %%ebx\n\t"
      ".LD3D_RecordStateBlock_36:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%edx, 0x484(%%edi)\n\t"
      "jbe .LD3D_RecordStateBlock_40\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0x68, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_37:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testb $2, (%%eax)\n\t"
      "je .LD3D_RecordStateBlock_39\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_38\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl 0x34(%%eax)\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "pushl $0x1a\n\t"
      "popl %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "rep movsl\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3D_RecordStateBlock_38:\n\t"
      "addl $0x6c, %%ebx\n\t"
      "addl $0x6c, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_39:\n\t"
      "addl $0x90, -0xc(%%ebp)\n\t"
      "incl %%edx\n\t"
      "cmpl 0x484(%%edi), %%edx\n\t"
      "jb .LD3D_RecordStateBlock_37\n\t"
      ".LD3D_RecordStateBlock_40:\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "cmpl $0, 0x484(%%edi)\n\t"
      "jbe .LD3D_RecordStateBlock_44\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0x68, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".LD3D_RecordStateBlock_41:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testb $4, (%%eax)\n\t"
      "je .LD3D_RecordStateBlock_43\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LD3D_RecordStateBlock_42\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl 0x38(%%esi)\n\t"
      "leal 0x4(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "call *%[c1e6e60]\n\t"
      ".LD3D_RecordStateBlock_42:\n\t"
      "addl $8, %%ebx\n\t"
      ".LD3D_RecordStateBlock_43:\n\t"
      "incl -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x90, -0x14(%%ebp)\n\t"
      "cmpl 0x484(%%edi), %%eax\n\t"
      "jb .LD3D_RecordStateBlock_41\n\t"
      ".LD3D_RecordStateBlock_44:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LD3D_RecordStateBlock_45\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d0bb9]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "je .LD3D_RecordStateBlock_46\n\t"
      "pushl $0xf\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "rep stosl\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "leal 0x3c(%%esi), %%ebx\n\t"
      "jmp .LD3D_RecordStateBlock_1\n\t"
      ".LD3D_RecordStateBlock_45:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LD3D_RecordStateBlock_47\n\t"
      ".LD3D_RecordStateBlock_46:\n\t"
      "movl $0x8007000e, %%eax\n\t"
      ".LD3D_RecordStateBlock_47:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1ed8f0] "m"(b1f92f0_c1ed8f0), [c1e6e60] "m"(b1f92f0_c1e6e60), [c1d0bb9] "m"(b1f92f0_c1d0bb9)
      : "memory");
}
#else
#error "D3D_RecordStateBlock: clang naked draft required"
#endif


/* D3DDevice_ApplyStateBlock (0x1f971e) — XBE naked draft (batch 358). */
#if defined(__clang__)
static void __stdcall (*const b1f971e_c1e8700)(uint32_t stage, void *texture) = (void *)D3DDevice_SetTexture;
static void (*const b1f971e_c1ec5c0)(void) = (void *)D3DDevice_SetPixelShader;
static void __stdcall (*const b1f971e_c1eb7f0)(uint32_t shader) = (void *)D3DDevice_SetVertexShader;
static void (*const b1f971e_c1e8920)(void) = (void *)D3DDevice_SetIndices;
static void __stdcall (*const b1f971e_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b1f971e_c1ec780)(void) = (void *)D3DDevice_SetPixelShaderConstant;
static void __stdcall (*const b1f971e_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static void (*const b1f971e_c1e93a0)(void) = (void *)D3DDevice_SetRenderStateNotInline;
static void (*const b1f971e_c1e9cb0)(void) = (void *)D3DDevice_SetTextureStageStateNotInline;
static void __stdcall (*const b1f971e_c1e6bd0)(uint32_t type, void *matrix) = (void *)D3DDevice_SetTransform;
static void __stdcall (*const b1f971e_c1e82a0)(void *viewport) = (void *)D3DDevice_SetViewport;
static void (*const b1f971e_c1e6d80)(void) = (void *)D3DDevice_SetMaterial;
static void (*const b1f971e_c1e6dd0)(void) = (void *)D3DDevice_SetBackMaterial;
static void (*const b1f971e_c1e8400)(void) = (void *)D3DDevice_SetLight;
static void (*const b1f971e_c1e85e0)(void) = (void *)D3DDevice_LightEnable;

__attribute__((naked, noinline))
void D3DDevice_ApplyStateBlock(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "xorl %%ebp, %%ebp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, (%%edi)\n\t"
      "leal 0x3c(%%edi), %%esi\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_2\n\t"
      ".LD3DDevice_ApplyStateBlock_1:\n\t"
      "pushl 0x4(%%esi)\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1e8700]\n\t"
      "addl $8, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl (%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_1\n\t"
      ".LD3DDevice_ApplyStateBlock_2:\n\t"
      "cmpl %%ebp, 0x4(%%edi)\n\t"
      "je .LD3DDevice_ApplyStateBlock_3\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1ec5c0]\n\t"
      "addl $4, %%esi\n\t"
      ".LD3DDevice_ApplyStateBlock_3:\n\t"
      "cmpl %%ebp, 0x8(%%edi)\n\t"
      "je .LD3DDevice_ApplyStateBlock_4\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1eb7f0]\n\t"
      "addl $4, %%esi\n\t"
      ".LD3DDevice_ApplyStateBlock_4:\n\t"
      "cmpl %%ebp, 0xc(%%edi)\n\t"
      "je .LD3DDevice_ApplyStateBlock_5\n\t"
      "pushl (%%esi)\n\t"
      "pushl 0x4(%%esi)\n\t"
      "call *%[c1e8920]\n\t"
      "addl $8, %%esi\n\t"
      ".LD3DDevice_ApplyStateBlock_5:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x10(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_7\n\t"
      ".LD3DDevice_ApplyStateBlock_6:\n\t"
      "pushl 0x4(%%esi)\n\t"
      "pushl 0x8(%%esi)\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1eb2d0]\n\t"
      "addl $0xc, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x10(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_6\n\t"
      ".LD3DDevice_ApplyStateBlock_7:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x14(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_9\n\t"
      ".LD3DDevice_ApplyStateBlock_8:\n\t"
      "pushl $1\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1ec780]\n\t"
      "addl $0x14, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x14(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_8\n\t"
      ".LD3DDevice_ApplyStateBlock_9:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x18(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_11\n\t"
      ".LD3DDevice_ApplyStateBlock_10:\n\t"
      "pushl $1\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "subl $0x60, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eb8d0]\n\t"
      "addl $0x14, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x18(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_10\n\t"
      ".LD3DDevice_ApplyStateBlock_11:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x1c(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_14\n\t"
      ".LD3DDevice_ApplyStateBlock_12:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "cmpl %%ecx, 0x1fb698(,%%eax,4)\n\t"
      "je .LD3DDevice_ApplyStateBlock_13\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e93a0]\n\t"
      ".LD3DDevice_ApplyStateBlock_13:\n\t"
      "addl $8, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x1c(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_12\n\t"
      ".LD3DDevice_ApplyStateBlock_14:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x20(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_17\n\t"
      ".LD3DDevice_ApplyStateBlock_15:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%ecx, %%ebp\n\t"
      "shll $5, %%ebp\n\t"
      "addl %%edx, %%ebp\n\t"
      "cmpl %%eax, 0x1fb498(,%%ebp,4)\n\t"
      "je .LD3DDevice_ApplyStateBlock_16\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e9cb0]\n\t"
      ".LD3DDevice_ApplyStateBlock_16:\n\t"
      "addl $0xc, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x20(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_15\n\t"
      "xorl %%ebp, %%ebp\n\t"
      ".LD3DDevice_ApplyStateBlock_17:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x24(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_19\n\t"
      ".LD3DDevice_ApplyStateBlock_18:\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1e6bd0]\n\t"
      "addl $0x44, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x24(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_18\n\t"
      ".LD3DDevice_ApplyStateBlock_19:\n\t"
      "cmpl %%ebp, 0x28(%%edi)\n\t"
      "je .LD3DDevice_ApplyStateBlock_20\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e82a0]\n\t"
      "addl $0x18, %%esi\n\t"
      ".LD3DDevice_ApplyStateBlock_20:\n\t"
      "cmpl %%ebp, 0x2c(%%edi)\n\t"
      "je .LD3DDevice_ApplyStateBlock_21\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e6d80]\n\t"
      "addl $0x44, %%esi\n\t"
      ".LD3DDevice_ApplyStateBlock_21:\n\t"
      "cmpl %%ebp, 0x30(%%edi)\n\t"
      "je .LD3DDevice_ApplyStateBlock_22\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e6dd0]\n\t"
      "addl $0x44, %%esi\n\t"
      ".LD3DDevice_ApplyStateBlock_22:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x34(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_24\n\t"
      ".LD3DDevice_ApplyStateBlock_23:\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1e8400]\n\t"
      "addl $0x6c, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x34(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_23\n\t"
      ".LD3DDevice_ApplyStateBlock_24:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x38(%%edi)\n\t"
      "jbe .LD3DDevice_ApplyStateBlock_26\n\t"
      ".LD3DDevice_ApplyStateBlock_25:\n\t"
      "pushl 0x4(%%esi)\n\t"
      "pushl (%%esi)\n\t"
      "call *%[c1e85e0]\n\t"
      "addl $8, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x38(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_ApplyStateBlock_25\n\t"
      ".LD3DDevice_ApplyStateBlock_26:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1e8700] "m"(b1f971e_c1e8700), [c1ec5c0] "m"(b1f971e_c1ec5c0), [c1eb7f0] "m"(b1f971e_c1eb7f0), [c1e8920] "m"(b1f971e_c1e8920), [c1eb2d0] "m"(b1f971e_c1eb2d0), [c1ec780] "m"(b1f971e_c1ec780), [c1eb8d0] "m"(b1f971e_c1eb8d0), [c1e93a0] "m"(b1f971e_c1e93a0), [c1e9cb0] "m"(b1f971e_c1e9cb0), [c1e6bd0] "m"(b1f971e_c1e6bd0), [c1e82a0] "m"(b1f971e_c1e82a0), [c1e6d80] "m"(b1f971e_c1e6d80), [c1e6dd0] "m"(b1f971e_c1e6dd0), [c1e8400] "m"(b1f971e_c1e8400), [c1e85e0] "m"(b1f971e_c1e85e0)
      : "memory");
}
#else
#error "D3DDevice_ApplyStateBlock: clang naked draft required"
#endif


/* D3DDevice_CaptureStateBlock (0x1f98a6) — XBE naked draft (batch 305). */
#if defined(__clang__)
static uint32_t __stdcall (*const b1f98a6_c1ed930)(void *resource) = (void *)D3DResource_Release;
static void b1f98a6_c1ed8f0_tgt(void) { return; }
static void (*const b1f98a6_c1ed8f0)(void) = b1f98a6_c1ed8f0_tgt;
static void (*const b1f98a6_c1ec100)(void) = D3DDevice_DeletePixelShader;
static void (*const b1f98a6_c1eb6d0)(void) = D3DDevice_DeleteVertexShader;
static void (*const b1f98a6_c1e6e60)(void) = D3DDevice_GetLightEnable;

__attribute__((naked, noinline))
void D3DDevice_CaptureStateBlock(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x1fe6a0, %%eax\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl $0, (%%esi)\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal 0x3c(%%esi), %%ebx\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_4\n\t"
      ".LD3DDevice_CaptureStateBlock_1:\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl (%%ebx), %%edi\n\t"
      "je .LD3DDevice_CaptureStateBlock_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed930]\n\t"
      ".LD3DDevice_CaptureStateBlock_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xba0(%%eax,%%edi,4), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_CaptureStateBlock_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ed8f0]\n\t"
      ".LD3DDevice_CaptureStateBlock_3:\n\t"
      "movl %%edi, 0x4(%%ebx)\n\t"
      "addl $8, %%ebx\n\t"
      "incl -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl (%%esi), %%eax\n\t"
      "jb .LD3DDevice_CaptureStateBlock_1\n\t"
      ".LD3DDevice_CaptureStateBlock_4:\n\t"
      "cmpl $0, 0x4(%%esi)\n\t"
      "je .LD3DDevice_CaptureStateBlock_7\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CaptureStateBlock_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ec100]\n\t"
      ".LD3DDevice_CaptureStateBlock_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x414(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CaptureStateBlock_6\n\t"
      "incl (%%eax)\n\t"
      ".LD3DDevice_CaptureStateBlock_6:\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "addl $4, %%ebx\n\t"
      ".LD3DDevice_CaptureStateBlock_7:\n\t"
      "cmpl $0, 0x8(%%esi)\n\t"
      "je .LD3DDevice_CaptureStateBlock_10\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LD3DDevice_CaptureStateBlock_8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eb6d0]\n\t"
      ".LD3DDevice_CaptureStateBlock_8:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x474(%%ecx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LD3DDevice_CaptureStateBlock_9\n\t"
      "movl 0x470(%%ecx), %%ecx\n\t"
      "incl (%%ecx)\n\t"
      ".LD3DDevice_CaptureStateBlock_9:\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "addl $4, %%ebx\n\t"
      ".LD3DDevice_CaptureStateBlock_10:\n\t"
      "cmpl $0, 0xc(%%esi)\n\t"
      "je .LD3DDevice_CaptureStateBlock_13\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LD3DDevice_CaptureStateBlock_11\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed930]\n\t"
      ".LD3DDevice_CaptureStateBlock_11:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x47c(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LD3DDevice_CaptureStateBlock_12\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ed8f0]\n\t"
      ".LD3DDevice_CaptureStateBlock_12:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x478(%%eax), %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl %%edi, 0x4(%%ebx)\n\t"
      "addl $8, %%ebx\n\t"
      ".LD3DDevice_CaptureStateBlock_13:\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      "cmpl $0, 0x10(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_17\n\t"
      ".LD3DDevice_CaptureStateBlock_14:\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl (%%ebx), %%edi\n\t"
      "je .LD3DDevice_CaptureStateBlock_15\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed930]\n\t"
      ".LD3DDevice_CaptureStateBlock_15:\n\t"
      "leal (%%edi,%%edi,2), %%edi\n\t"
      "shll $2, %%edi\n\t"
      "movl 0x1fb8e0(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LD3DDevice_CaptureStateBlock_16\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed8f0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LD3DDevice_CaptureStateBlock_16:\n\t"
      "movl 0x1fb8d8(%%edi), %%ecx\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "addl $0xc, %%ebx\n\t"
      "incl -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl 0x10(%%esi), %%eax\n\t"
      "jb .LD3DDevice_CaptureStateBlock_14\n\t"
      ".LD3DDevice_CaptureStateBlock_17:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, 0x14(%%esi)\n\t"
      "pushl $0x14\n\t"
      "popl %%edx\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_19\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LD3DDevice_CaptureStateBlock_18:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl %%edx, -0x8(%%ebp)\n\t"
      "leal 0xbc(%%eax), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "shll $4, %%esi\n\t"
      "addl -0x4(%%ebp), %%esi\n\t"
      "addl %%edx, %%ebx\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "incl %%ecx\n\t"
      ".byte 0xa5\n\t"
      "cmpl 0x14(%%eax), %%ecx\n\t"
      "jb .LD3DDevice_CaptureStateBlock_18\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3DDevice_CaptureStateBlock_19:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, 0x18(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_21\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LD3DDevice_CaptureStateBlock_20:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl %%edx, -0x8(%%ebp)\n\t"
      "leal 0xcc(%%eax), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "shll $4, %%esi\n\t"
      "addl -0x4(%%ebp), %%esi\n\t"
      "addl %%edx, %%ebx\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "incl %%ecx\n\t"
      ".byte 0xa5\n\t"
      "cmpl 0x18(%%eax), %%ecx\n\t"
      "jb .LD3DDevice_CaptureStateBlock_20\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3DDevice_CaptureStateBlock_21:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%ecx, 0x1c(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_23\n\t"
      ".LD3DDevice_CaptureStateBlock_22:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x1fb698(,%%edx,4), %%edx\n\t"
      "movl %%edx, 0x4(%%ebx)\n\t"
      "addl $8, %%ebx\n\t"
      "incl %%eax\n\t"
      "cmpl 0x1c(%%esi), %%eax\n\t"
      "jb .LD3DDevice_CaptureStateBlock_22\n\t"
      ".LD3DDevice_CaptureStateBlock_23:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%ecx, 0x20(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_25\n\t"
      ".LD3DDevice_CaptureStateBlock_24:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "shll $5, %%edx\n\t"
      "addl 0x4(%%ebx), %%edx\n\t"
      "addl $0xc, %%ebx\n\t"
      "movl 0x1fb498(,%%edx,4), %%edx\n\t"
      "movl %%edx, -0x4(%%ebx)\n\t"
      "incl %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "jb .LD3DDevice_CaptureStateBlock_24\n\t"
      ".LD3DDevice_CaptureStateBlock_25:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%ecx, 0x24(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_27\n\t"
      "leal 0x4(%%ebx), %%edx\n\t"
      ".LD3DDevice_CaptureStateBlock_26:\n\t"
      "movl (%%ebx), %%esi\n\t"
      "addl $0x22, %%esi\n\t"
      "shll $6, %%esi\n\t"
      "addl -0x4(%%ebp), %%esi\n\t"
      "pushl $0x10\n\t"
      "movl %%edx, %%edi\n\t"
      "popl %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $0x44, %%ebx\n\t"
      "addl $0x44, %%edx\n\t"
      "incl %%eax\n\t"
      "cmpl 0x24(%%ecx), %%eax\n\t"
      "jb .LD3DDevice_CaptureStateBlock_26\n\t"
      "movl %%ecx, %%esi\n\t"
      ".LD3DDevice_CaptureStateBlock_27:\n\t"
      "cmpl $0, 0x28(%%esi)\n\t"
      "je .LD3DDevice_CaptureStateBlock_28\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0xb00, %%esi\n\t"
      "pushl $6\n\t"
      "movl %%ebx, %%edi\n\t"
      "popl %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0x18, %%ebx\n\t"
      ".LD3DDevice_CaptureStateBlock_28:\n\t"
      "cmpl $0, 0x2c(%%esi)\n\t"
      "je .LD3DDevice_CaptureStateBlock_29\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0xb18, %%esi\n\t"
      "pushl $0x11\n\t"
      "movl %%ebx, %%edi\n\t"
      "popl %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0x44, %%ebx\n\t"
      ".LD3DDevice_CaptureStateBlock_29:\n\t"
      "cmpl $0, 0x30(%%esi)\n\t"
      "je .LD3DDevice_CaptureStateBlock_30\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0xb5c, %%esi\n\t"
      "pushl $0x11\n\t"
      "movl %%ebx, %%edi\n\t"
      "popl %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0x44, %%ebx\n\t"
      ".LD3DDevice_CaptureStateBlock_30:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%edx, 0x34(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_32\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LD3DDevice_CaptureStateBlock_31:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl $0x6c, -0x8(%%ebp)\n\t"
      "leal (%%eax,%%eax,8), %%esi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "shll $4, %%esi\n\t"
      "addl 0x480(%%eax), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x1a\n\t"
      "addl $0x6c, %%ebx\n\t"
      "popl %%ecx\n\t"
      "incl %%edx\n\t"
      "rep movsl\n\t"
      "cmpl 0x34(%%eax), %%edx\n\t"
      "jb .LD3DDevice_CaptureStateBlock_31\n\t"
      "movl %%eax, %%esi\n\t"
      ".LD3DDevice_CaptureStateBlock_32:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, 0x38(%%esi)\n\t"
      "jbe .LD3DDevice_CaptureStateBlock_34\n\t"
      ".LD3DDevice_CaptureStateBlock_33:\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl (%%ebx)\n\t"
      "call *%[c1e6e60]\n\t"
      "addl $8, %%ebx\n\t"
      "incl %%edi\n\t"
      "cmpl 0x38(%%esi), %%edi\n\t"
      "jb .LD3DDevice_CaptureStateBlock_33\n\t"
      ".LD3DDevice_CaptureStateBlock_34:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1ed930] "m"(b1f98a6_c1ed930), [c1ed8f0] "m"(b1f98a6_c1ed8f0), [c1ec100] "m"(b1f98a6_c1ec100), [c1eb6d0] "m"(b1f98a6_c1eb6d0), [c1e6e60] "m"(b1f98a6_c1e6e60)
      : "memory");
}
#else
#error "D3DDevice_CaptureStateBlock: clang naked draft required"
#endif


/* D3DDevice_DeleteStateBlock (0x1f9b53) — XBE naked draft (batch 348). */
#if defined(__clang__)
static uint32_t __stdcall (*const b1f9b53_c1ed930)(void *resource) = (void *)D3DResource_Release;
static void (*const b1f9b53_c1ec100)(void) = D3DDevice_DeletePixelShader;
static void (*const b1f9b53_c1eb6d0)(void) = D3DDevice_DeleteVertexShader;
static void *__stdcall (*const b1f9b53_c1d0c16)(void *ptr) = (void *)LocalFree;

__attribute__((naked, noinline))
void D3DDevice_DeleteStateBlock(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "xorl %%ebp, %%ebp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, (%%edi)\n\t"
      "leal 0x3c(%%edi), %%esi\n\t"
      "jbe .LD3DDevice_DeleteStateBlock_3\n\t"
      ".LD3DDevice_DeleteStateBlock_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $8, %%esi\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LD3DDevice_DeleteStateBlock_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed930]\n\t"
      ".LD3DDevice_DeleteStateBlock_2:\n\t"
      "incl %%ebx\n\t"
      "cmpl (%%edi), %%ebx\n\t"
      "jb .LD3DDevice_DeleteStateBlock_1\n\t"
      ".LD3DDevice_DeleteStateBlock_3:\n\t"
      "cmpl %%ebp, 0x4(%%edi)\n\t"
      "je .LD3DDevice_DeleteStateBlock_4\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $4, %%esi\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LD3DDevice_DeleteStateBlock_4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ec100]\n\t"
      ".LD3DDevice_DeleteStateBlock_4:\n\t"
      "cmpl %%ebp, 0x8(%%edi)\n\t"
      "je .LD3DDevice_DeleteStateBlock_5\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $4, %%esi\n\t"
      "testb $1, %%al\n\t"
      "je .LD3DDevice_DeleteStateBlock_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eb6d0]\n\t"
      ".LD3DDevice_DeleteStateBlock_5:\n\t"
      "cmpl %%ebp, 0xc(%%edi)\n\t"
      "je .LD3DDevice_DeleteStateBlock_6\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $8, %%esi\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LD3DDevice_DeleteStateBlock_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed930]\n\t"
      ".LD3DDevice_DeleteStateBlock_6:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebp, 0x10(%%edi)\n\t"
      "jbe .LD3DDevice_DeleteStateBlock_9\n\t"
      "addl $8, %%esi\n\t"
      ".LD3DDevice_DeleteStateBlock_7:\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "cmpl %%ebp, %%eax\n\t"
      "je .LD3DDevice_DeleteStateBlock_8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed930]\n\t"
      ".LD3DDevice_DeleteStateBlock_8:\n\t"
      "incl %%ebx\n\t"
      "cmpl 0x10(%%edi), %%ebx\n\t"
      "jb .LD3DDevice_DeleteStateBlock_7\n\t"
      ".LD3DDevice_DeleteStateBlock_9:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d0c16]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1ed930] "m"(b1f9b53_c1ed930), [c1ec100] "m"(b1f9b53_c1ec100), [c1eb6d0] "m"(b1f9b53_c1eb6d0), [c1d0c16] "m"(b1f9b53_c1d0c16)
      : "memory");
}
#else
#error "D3DDevice_DeleteStateBlock: clang naked draft required"
#endif


/* D3DDevice_CreateStateBlock (0x1f9be4) — XBE naked draft (batch 318). */
#if defined(__clang__)
static void (*const b1f9be4_c1f9165)(void) = D3D_ClearStateBlockFlags;
static void (*const b1f9be4_c1f92f0)(void) = D3D_RecordStateBlock;

__attribute__((naked, noinline))
void D3DDevice_CreateStateBlock(void)
{
  __asm__ volatile(
      "cmpl $1, 0x4(%%esp)\n\t"
      "pushl %%esi\n\t"
      "movl 0x1fe6a0, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LD3DDevice_CreateStateBlock_3\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl $0x81, %%ecx\n\t"
      "movl $0x1fe6c0, %%edi\n\t"
      "rep stosl\n\t"
      "movl 0x480(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%edx, 0x484(%%esi)\n\t"
      "jbe .LD3DDevice_CreateStateBlock_13\n\t"
      "leal 0x68(%%eax), %%ecx\n\t"
      ".LD3DDevice_CreateStateBlock_1:\n\t"
      "movl (%%ecx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LD3DDevice_CreateStateBlock_2\n\t"
      "orl $6, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LD3DDevice_CreateStateBlock_2:\n\t"
      "incl %%edx\n\t"
      "addl $0x90, %%ecx\n\t"
      "cmpl 0x484(%%esi), %%edx\n\t"
      "jb .LD3DDevice_CreateStateBlock_1\n\t"
      "jmp .LD3DDevice_CreateStateBlock_13\n\t"
      ".LD3DDevice_CreateStateBlock_3:\n\t"
      "call *%[c1f9165]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl $2, 0xc(%%esp)\n\t"
      "jne .LD3DDevice_CreateStateBlock_7\n\t"
      "movb $1, 0x1fe6c4\n\t"
      "movl $0x1fe6d7, %%edi\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_CreateStateBlock_4:\n\t"
      "movzbl 0x1fb3b8(%%eax), %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpl $0x20, %%eax\n\t"
      "movb $1, 0x1fe7a7(%%ecx)\n\t"
      "jb .LD3DDevice_CreateStateBlock_4\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LD3DDevice_CreateStateBlock_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_CreateStateBlock_6:\n\t"
      "movzbl 0x1fb39c(%%eax), %%edx\n\t"
      "incl %%eax\n\t"
      "cmpl $0x1b, %%eax\n\t"
      "movb $1, 0x1fe837(%%ecx,%%edx,4)\n\t"
      "jb .LD3DDevice_CreateStateBlock_6\n\t"
      "incl %%ecx\n\t"
      "cmpl $4, %%ecx\n\t"
      "jb .LD3DDevice_CreateStateBlock_5\n\t"
      "jmp .LD3DDevice_CreateStateBlock_13\n\t"
      ".LD3DDevice_CreateStateBlock_7:\n\t"
      "pushl $0x30\n\t"
      "popl %%ecx\n\t"
      "movl $0x1fe6e7, %%edi\n\t"
      "movb $1, 0x1fe6c5\n\t"
      "rep stosl\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_CreateStateBlock_8:\n\t"
      "movzbl 0x1fb37c(%%eax), %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpl $0x20, %%eax\n\t"
      "movb $1, 0x1fe7a7(%%ecx)\n\t"
      "jb .LD3DDevice_CreateStateBlock_8\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LD3DDevice_CreateStateBlock_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LD3DDevice_CreateStateBlock_10:\n\t"
      "movzbl 0x1fb378(%%eax), %%edx\n\t"
      "incl %%eax\n\t"
      "cmpl $2, %%eax\n\t"
      "movb $1, 0x1fe837(%%ecx,%%edx,4)\n\t"
      "jb .LD3DDevice_CreateStateBlock_10\n\t"
      "incl %%ecx\n\t"
      "cmpl $4, %%ecx\n\t"
      "jb .LD3DDevice_CreateStateBlock_9\n\t"
      "movl 0x480(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%edx, 0x484(%%esi)\n\t"
      "jbe .LD3DDevice_CreateStateBlock_13\n\t"
      "leal 0x68(%%eax), %%ecx\n\t"
      ".LD3DDevice_CreateStateBlock_11:\n\t"
      "movl (%%ecx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LD3DDevice_CreateStateBlock_12\n\t"
      "orl $6, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LD3DDevice_CreateStateBlock_12:\n\t"
      "incl %%edx\n\t"
      "addl $0x90, %%ecx\n\t"
      "cmpl 0x484(%%esi), %%edx\n\t"
      "jb .LD3DDevice_CreateStateBlock_11\n\t"
      ".LD3DDevice_CreateStateBlock_13:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "call *%[c1f92f0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1f9165] "m"(b1f9be4_c1f9165), [c1f92f0] "m"(b1f9be4_c1f92f0)
      : "memory");
}
#else
#error "D3DDevice_CreateStateBlock: clang naked draft required"
#endif


/* D3DDevice_EndStateBlock (0x1f9d0f) — XBE naked draft (batch 393). */
#if defined(__clang__)


__attribute__((naked, noinline))
void D3DDevice_EndStateBlock(void)
{
  __asm__ volatile(
      "movl 0x1fe6a0, %%eax\n\t"
      "andl $0xffffffdf, 0xc(%%eax)\n\t"
      ".byte 0xe9, 0xd3, 0xf5, 0xff, 0xff\n\t"
      :
      :
      : "memory");
}
#else
#error "D3DDevice_EndStateBlock: clang naked draft required"
#endif


/* DirectSoundEnterCriticalSection (0x20368b) — XBE naked draft (batch 319). */
#if defined(__clang__)


__attribute__((naked, noinline))
void DirectSoundEnterCriticalSection(void)
{
  __asm__ volatile(
      "movzbl 0x24, %%eax\n\t"
      "testb %%al, %%al\n\t"
      "je .LDirectSoundEnterCriticalSection_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      ".LDirectSoundEnterCriticalSection_1:\n\t"
      "pushl $0x222674\n\t"
      "call *0x25309c\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "DirectSoundEnterCriticalSection: clang naked draft required"
#endif


/* CMcpxAPU_ServiceDeferredCommandsLow (0x20380b) — XBE naked draft (batch 401). */
#if defined(__clang__)
static void (*const b20380b_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void b20380b_c20376b_tgt(void) { return; }
static void (*const b20380b_c20376b)(void) = b20380b_c20376b_tgt;
static void b20380b_c203995_tgt(void) { return; }
static void (*const b20380b_c203995)(void) = b20380b_c203995_tgt;
static void b20380b_c2037ad_tgt(void) { return; }
static void (*const b20380b_c2037ad)(void) = b20380b_c2037ad_tgt;
static void b20380b_c207aca_tgt(void) { return; }
static void (*const b20380b_c207aca)(void) = b20380b_c207aca_tgt;
static void b20380b_c207b73_tgt(void) { return; }
static void (*const b20380b_c207b73)(void) = b20380b_c207b73_tgt;
static void b20380b_c207876_tgt(void) { return; }
static void (*const b20380b_c207876)(void) = b20380b_c207876_tgt;
static void (*const b20380b_c206dc4)(void) = (void *)CMcpxAPU_SetMixBinHeadroom;
static void (*const b20380b_c207234)(void) = (void *)CMcpxAPU_Set3dParameters;
static void (*const b20380b_c207265)(void) = (void *)CMcpxAPU_Set3dDistanceFactor;
static void (*const b20380b_c207289)(void) = (void *)CMcpxAPU_Set3dDopplerFactor;
static void (*const b20380b_c2072ad)(void) = (void *)CMcpxAPU_Set3dRolloffFactor;
static void b20380b_c2072d1_tgt(void) { return; }
static void (*const b20380b_c2072d1)(void) = b20380b_c2072d1_tgt;
static void (*const b20380b_c207309)(void) = (void *)CMcpxAPU_Set3dPosition;
static void (*const b20380b_c207334)(void) = (void *)CMcpxAPU_Set3dVelocity;
static void (*const b20380b_c20735f)(void) = (void *)CMcpxAPU_SetI3DL2Listener;
static void (*const b20380b_c206a5e)(void) = (void *)CMcpxAPU_Commit3dSettings;
static void b20380b_c2073d9_tgt(void) { return; }
static void (*const b20380b_c2073d9)(void) = b20380b_c2073d9_tgt;
static void b20380b_c206df8_tgt(void) { return; }
static void (*const b20380b_c206df8)(void) = b20380b_c206df8_tgt;
static void (*const b20380b_c209961)(void) = (void *)CMcpxVoiceClient_SetPitch;
static void b20380b_c209880_tgt(void) { return; }
static void (*const b20380b_c209880)(void) = b20380b_c209880_tgt;
static void (*const b20380b_c209c05)(void) = (void *)CMcpxVoiceClient_SetLFO;
static void (*const b20380b_c209d16)(void) = (void *)CMcpxVoiceClient_SetEG;
static void (*const b20380b_c208da2)(void) = (void *)CMcpxVoiceClient_SetFilter;
static void (*const b20380b_c20a0ef)(void) = (void *)CMcpxVoiceClient_Set3dParameters;
static void b20380b_c20a11d_tgt(void) { return; }
static void (*const b20380b_c20a11d)(void) = b20380b_c20a11d_tgt;
static void (*const b20380b_c20a145)(void) = (void *)CMcpxVoiceClient_Set3dConeOrientation;
static void (*const b20380b_c20a16d)(void) = (void *)CMcpxVoiceClient_Set3dConeOutsideVolume;
static void (*const b20380b_c20a18e)(void) = (void *)CMcpxVoiceClient_Set3dMaxDistance;
static void (*const b20380b_c20a1af)(void) = (void *)CMcpxVoiceClient_Set3dMinDistance;
static void (*const b20380b_c20a1d0)(void) = (void *)CMcpxVoiceClient_Set3dMode;
static void (*const b20380b_c20a1f1)(void) = (void *)CMcpxVoiceClient_Set3dPosition;
static void (*const b20380b_c20a219)(void) = (void *)CMcpxVoiceClient_Set3dVelocity;
static void (*const b20380b_c20a241)(void) = (void *)CMcpxVoiceClient_SetI3DL2Source;
static void (*const b20380b_c20baa4)(void) = (void *)CMcpxBuffer_Play;
static void b20380b_c20badd_tgt(void) { return; }
static void (*const b20380b_c20badd)(void) = b20380b_c20badd_tgt;
static void (*const b20380b_c20b873)(void) = (void *)CMcpxBuffer_Stop;
static void (*const b20380b_c20b0ac)(void) = (void *)CMcpxBuffer_GetStatus;
static void b20380b_c204388_tgt(void) { return; }
static void (*const b20380b_c204388)(void) = b20380b_c204388_tgt;
static void b20380b_c20b856_tgt(void) { return; }
static void (*const b20380b_c20b856)(void) = b20380b_c20b856_tgt;
static void (*const b20380b_c20b0f7)(void) = (void *)CMcpxBuffer_GetCurrentPosition;
static void (*const b20380b_c2044b5)(void) = (void *)CDirectSoundBuffer_GetCurrentPosition;
static void (*const b20380b_c20b8d7)(void) = (void *)CMcpxBuffer_SetCurrentPosition;
static void b20380b_c203704_tgt(void) { return; }
static void (*const b20380b_c203704)(void) = b20380b_c203704_tgt;
static void b20380b_c203815_tgt(void) { return; }
static void (*const b20380b_c203815)(void) = b20380b_c203815_tgt;
static void (*const b20380b_c20c752)(void) = (void *)CMcpxStream_Discontinuity;
static void (*const b20380b_c20c3fe)(void) = (void *)CMcpxStream_Flush;
static void b20380b_c20bc71_tgt(void) { return; }
static void (*const b20380b_c20bc71)(void) = b20380b_c20bc71_tgt;
static void b20380b_c20c636_tgt(void) { return; }
static void (*const b20380b_c20c636)(void) = b20380b_c20c636_tgt;
static void (*const b20380b_c20c050)(void) = (void *)CMcpxStream_Pause;
static void (*const b20380b_c204163)(void) = (void *)CDirectSoundVoice_SetConeOrientation;
static void (*const b20380b_c2041f0)(void) = (void *)CDirectSoundVoice_SetMaxDistance;
static void (*const b20380b_c20422f)(void) = (void *)CDirectSoundVoice_SetMinDistance;
static void (*const b20380b_c2042a9)(void) = (void *)CDirectSoundVoice_SetPosition;
static void (*const b20380b_c2042fb)(void) = (void *)CDirectSoundVoice_SetVelocity;
static void (*const b20380b_c203f32)(void) = (void *)CDirectSoundVoice_SetPitch;
static void (*const b20380b_c203f69)(void) = (void *)CDirectSoundVoice_SetVolume;
static void (*const b20380b_c203fa3)(void) = (void *)CDirectSoundVoice_SetLFO;
static void (*const b20380b_c203fd4)(void) = (void *)CDirectSoundVoice_SetEG;
static void (*const b20380b_c204005)(void) = (void *)CDirectSoundVoice_SetFilter;
static void (*const b20380b_c204036)(void) = (void *)CDirectSoundVoice_SetHeadroom;
static void (*const b20380b_c204075)(void) = (void *)CDirectSoundVoice_SetMixBinVolumes;
static void (*const b20380b_c2040e9)(void) = (void *)CDirectSoundVoice_SetAllParameters;
static void (*const b20380b_c204124)(void) = (void *)CDirectSoundVoice_SetConeAngles;
static void (*const b20380b_c2041b5)(void) = (void *)CDirectSoundVoice_SetConeOutsideVolume;
static void (*const b20380b_c20426e)(void) = (void *)CDirectSoundVoice_SetMode;
static void (*const b20380b_c20434d)(void) = (void *)CDirectSoundVoice_SetI3DL2Source;
static void (*const b20380b_c20384b)(void) = (void *)IDirectSound_AddRef;
static void (*const b20380b_c2039b7)(void) = (void *)CDirectSound_GetCaps;
static void (*const b20380b_c203a07)(void) = (void *)CDirectSound_GetSpeakerConfig;
static void (*const b20380b_c203a21)(void) = (void *)CDirectSound_DownloadEffectsImage;
static void (*const b20380b_c203ab0)(void) = (void *)CDirectSound_GetEffectData;
static void (*const b20380b_c203a65)(void) = (void *)CDirectSound_SetEffectData;
static void (*const b20380b_c203af2)(void) = (void *)CDirectSound_CommitEffectData;
static void (*const b20380b_c203e0a)(void) = (void *)CDirectSound_EnableHeadphones;
static void (*const b20380b_c203b25)(void) = (void *)CDirectSound_SetMixBinHeadroom;
static void (*const b20380b_c203b5a)(void) = (void *)CDirectSound_SetAllParameters;
static void (*const b20380b_c203b95)(void) = (void *)CDirectSound_SetDistanceFactor;
static void (*const b20380b_c203bd4)(void) = (void *)CDirectSound_SetDopplerFactor;
static void (*const b20380b_c203c52)(void) = (void *)CDirectSound_SetOrientation;
static void (*const b20380b_c203cba)(void) = (void *)CDirectSound_SetPosition;
static void (*const b20380b_c203c13)(void) = (void *)CDirectSound_SetRolloffFactor;
static void (*const b20380b_c203d0c)(void) = (void *)CDirectSound_SetVelocity;
static void (*const b20380b_c203da9)(void) = (void *)CDirectSound_CommitDeferredSettings;
static void (*const b20380b_c203dd4)(void) = (void *)CDirectSound_GetTime;
static void (*const b20380b_c203d5e)(void) = (void *)CDirectSound_SetI3DL2Listener;
static void (*const b20380b_c203881)(void) = (void *)IDirectSoundBuffer_AddRef;
static void (*const b20380b_c2049aa)(void) = (void *)CDirectSoundBuffer_SetConeOrientation;
static void (*const b20380b_c2049d8)(void) = (void *)CDirectSoundBuffer_SetMaxDistance;
static void (*const b20380b_c2049f0)(void) = (void *)CDirectSoundBuffer_SetMinDistance;
static void (*const b20380b_c204a0d)(void) = (void *)CDirectSoundBuffer_SetPosition;
static void (*const b20380b_c204a36)(void) = (void *)CDirectSoundBuffer_SetVelocity;
static void (*const b20380b_c2043a4)(void) = (void *)CDirectSoundBuffer_PlayEx;
static void (*const b20380b_c2043e1)(void) = (void *)CDirectSoundBuffer_StopEx;
static void (*const b20380b_c204468)(void) = (void *)CDirectSoundBuffer_SetLoopRegion;
static void (*const b20380b_c204437)(void) = (void *)CDirectSoundBuffer_GetStatus;
static void (*const b20380b_c204590)(void) = (void *)CDirectSoundBuffer_SetCurrentPosition;
static void (*const b20380b_c2044ea)(void) = (void *)CDirectSoundBuffer_Lock;
static void (*const b20380b_c204b28)(void) = (void *)CDirectSoundStream_SetConeOrientation;
static void (*const b20380b_c204b6d)(void) = (void *)CDirectSoundStream_SetMaxDistance;
static void (*const b20380b_c204b89)(void) = (void *)CDirectSoundStream_SetMinDistance;
static void (*const b20380b_c204bbd)(void) = (void *)CDirectSoundStream_SetPosition;
static void (*const b20380b_c204bea)(void) = (void *)CDirectSoundStream_SetVelocity;
static void (*const b20380b_c203de3)(void) = (void *)CDirectSound_DoWork;
static void b20380b_c203664_tgt(void) { return; }
static void (*const b20380b_c203664)(void) = b20380b_c203664_tgt;
static void (*const b20380b_c1d4507)(void) = (void *)FUN_001d4507;
static void b20380b_c2047f5_tgt(void) { return; }
static void (*const b20380b_c2047f5)(void) = b20380b_c2047f5_tgt;
static void b20380b_c20480b_tgt(void) { return; }
static void (*const b20380b_c20480b)(void) = b20380b_c20480b_tgt;
static void b20380b_c20484d_tgt(void) { return; }
static void (*const b20380b_c20484d)(void) = b20380b_c20484d_tgt;
static void b20380b_c20cb4b_tgt(void) { return; }
static void (*const b20380b_c20cb4b)(void) = b20380b_c20cb4b_tgt;
static void b20380b_c203f07_tgt(void) { return; }
static void (*const b20380b_c203f07)(void) = b20380b_c203f07_tgt;
static void (*const b20380b_c20c857)(void) = (void *)XAudioCalculatePitch;
static void b20380b_c204821_tgt(void) { return; }
static void (*const b20380b_c204821)(void) = b20380b_c204821_tgt;
static void b20380b_c204862_tgt(void) { return; }
static void (*const b20380b_c204862)(void) = b20380b_c204862_tgt;
static void b20380b_c20478b_tgt(void) { return; }
static void (*const b20380b_c20478b)(void) = b20380b_c20478b_tgt;
static void b20380b_c2047df_tgt(void) { return; }
static void (*const b20380b_c2047df)(void) = b20380b_c2047df_tgt;
static void b20380b_c204877_tgt(void) { return; }
static void (*const b20380b_c204877)(void) = b20380b_c204877_tgt;
static void b20380b_c20488d_tgt(void) { return; }
static void (*const b20380b_c20488d)(void) = b20380b_c20488d_tgt;
static void b20380b_c2048a3_tgt(void) { return; }
static void (*const b20380b_c2048a3)(void) = b20380b_c2048a3_tgt;
static void b20380b_c2048b8_tgt(void) { return; }
static void (*const b20380b_c2048b8)(void) = b20380b_c2048b8_tgt;
static void b20380b_c2090ca_tgt(void) { return; }
static void (*const b20380b_c2090ca)(void) = b20380b_c2090ca_tgt;
static void b20380b_c20552e_tgt(void) { return; }
static void (*const b20380b_c20552e)(void) = b20380b_c20552e_tgt;
static void b20380b_c208f52_tgt(void) { return; }
static void (*const b20380b_c208f52)(void) = b20380b_c208f52_tgt;
static void (*const b20380b_c2097a9)(void) = (void *)CMcpxVoiceClient_SetMixBins;
static void b20380b_c203609_tgt(void) { return; }
static void (*const b20380b_c203609)(void) = b20380b_c203609_tgt;
static void b20380b_c2048cd_tgt(void) { return; }
static void (*const b20380b_c2048cd)(void) = b20380b_c2048cd_tgt;
static void b20380b_c2048e3_tgt(void) { return; }
static void (*const b20380b_c2048e3)(void) = b20380b_c2048e3_tgt;
static void b20380b_c20b46d_tgt(void) { return; }
static void (*const b20380b_c20b46d)(void) = b20380b_c20b46d_tgt;
static void (*const b20380b_c2056a8)(void) = (void *)CDirectSoundBufferSettings_SetBufferData;
static void (*const b20380b_c20ba90)(void) = (void *)CMcpxBuffer_SetBufferData;
static void b20380b_c204637_tgt(void) { return; }
static void (*const b20380b_c204637)(void) = b20380b_c204637_tgt;
static void (*const b20380b_c2055e4)(void) = (void *)CDirectSoundVoice_SetOutputBuffer;
static void b20380b_c2045c1_tgt(void) { return; }
static void (*const b20380b_c2045c1)(void) = b20380b_c2045c1_tgt;
static void b20380b_c204605_tgt(void) { return; }
static void (*const b20380b_c204605)(void) = b20380b_c204605_tgt;
static void b20380b_c2054a8_tgt(void) { return; }
static void (*const b20380b_c2054a8)(void) = b20380b_c2054a8_tgt;
static void b20380b_c2048f9_tgt(void) { return; }
static void (*const b20380b_c2048f9)(void) = b20380b_c2048f9_tgt;
static void b20380b_c20490f_tgt(void) { return; }
static void (*const b20380b_c20490f)(void) = b20380b_c20490f_tgt;
static void (*const b20380b_c203936)(void) = (void *)DSound_CRefCount_AddRef;
static void (*const b20380b_c20395b)(void) = (void *)DSound_CRefCount_Release;
static void b20380b_c204925_tgt(void) { return; }
static void (*const b20380b_c204925)(void) = b20380b_c204925_tgt;
static void (*const b20380b_c203861)(void) = (void *)IDirectSound_Release;
static void (*const b20380b_c203897)(void) = (void *)IDirectSoundBuffer_Release;
static void b20380b_c2058c2_tgt(void) { return; }
static void (*const b20380b_c2058c2)(void) = b20380b_c2058c2_tgt;
static void (*const b20380b_c2055a1)(void) = (void *)CDirectSoundVoice_SetFrequency;
static void (*const b20380b_c205650)(void) = (void *)CDirectSoundVoice_SetMixBins;
static void (*const b20380b_c205894)(void) = (void *)CDirectSoundBuffer_SetOutputBuffer;
static void (*const b20380b_c2057dd)(void) = (void *)CDirectSoundBuffer_Play;
static void (*const b20380b_c20580f)(void) = (void *)CDirectSoundBuffer_Stop;
static void (*const b20380b_c205768)(void) = (void *)CDirectSoundBuffer_SetBufferData;
static void (*const b20380b_c20583f)(void) = (void *)CDirectSoundBuffer_SetNotificationPositions;
static void b20380b_c20547e_tgt(void) { return; }
static void (*const b20380b_c20547e)(void) = b20380b_c20547e_tgt;
static void b20380b_c205a7e_tgt(void) { return; }
static void (*const b20380b_c205a7e)(void) = b20380b_c205a7e_tgt;
static void b20380b_c2047ca_tgt(void) { return; }
static void (*const b20380b_c2047ca)(void) = b20380b_c2047ca_tgt;
static void b20380b_c205a59_tgt(void) { return; }
static void (*const b20380b_c205a59)(void) = b20380b_c205a59_tgt;
static void b20380b_c205547_tgt(void) { return; }
static void (*const b20380b_c205547)(void) = b20380b_c205547_tgt;
static void b20380b_c205c86_tgt(void) { return; }
static void (*const b20380b_c205c86)(void) = b20380b_c205c86_tgt;
static void b20380b_c20571a_tgt(void) { return; }
static void (*const b20380b_c20571a)(void) = b20380b_c20571a_tgt;
static void b20380b_c205cff_tgt(void) { return; }
static void (*const b20380b_c205cff)(void) = b20380b_c205cff_tgt;
static void b20380b_c2070d6_tgt(void) { return; }
static void (*const b20380b_c2070d6)(void) = b20380b_c2070d6_tgt;
static void b20380b_c205580_tgt(void) { return; }
static void (*const b20380b_c205580)(void) = b20380b_c205580_tgt;
static void b20380b_c2059b0_tgt(void) { return; }
static void (*const b20380b_c2059b0)(void) = b20380b_c2059b0_tgt;
static void b20380b_c205979_tgt(void) { return; }
static void (*const b20380b_c205979)(void) = b20380b_c205979_tgt;
static void b20380b_c207141_tgt(void) { return; }
static void (*const b20380b_c207141)(void) = b20380b_c207141_tgt;
static void b20380b_c205d52_tgt(void) { return; }
static void (*const b20380b_c205d52)(void) = b20380b_c205d52_tgt;
static void b20380b_c205d8e_tgt(void) { return; }
static void (*const b20380b_c205d8e)(void) = b20380b_c205d8e_tgt;
static void (*const b20380b_c205e69)(void) = (void *)CDirectSoundStream_Constructor;
static void b20380b_c205eb6_tgt(void) { return; }
static void (*const b20380b_c205eb6)(void) = b20380b_c205eb6_tgt;
static void b20380b_c204837_tgt(void) { return; }
static void (*const b20380b_c204837)(void) = b20380b_c204837_tgt;
static void b20380b_c205c4d_tgt(void) { return; }
static void (*const b20380b_c205c4d)(void) = b20380b_c205c4d_tgt;
static void b20380b_c205ce5_tgt(void) { return; }
static void (*const b20380b_c205ce5)(void) = b20380b_c205ce5_tgt;
static void (*const b20380b_c205f6d)(void) = (void *)CDirectSound_CreateSoundBuffer;
static void (*const b20380b_c205fed)(void) = (void *)CDirectSound_CreateSoundStream;
static void b20380b_c2053f9_tgt(void) { return; }
static void (*const b20380b_c2053f9)(void) = b20380b_c2053f9_tgt;
static void b20380b_c206eb2_tgt(void) { return; }
static void (*const b20380b_c206eb2)(void) = b20380b_c206eb2_tgt;
static void b20380b_c20763c_tgt(void) { return; }
static void (*const b20380b_c20763c)(void) = b20380b_c20763c_tgt;
static int __stdcall (*const b20380b_c205b7f)(void *buffer, void *data, uint32_t size) = (void *)IDirectSoundBuffer_SetBufferData;
static int __stdcall (*const b20380b_c205b43)(void *buffer, uint32_t reserved, uint32_t priority, uint32_t flags) = (void *)IDirectSoundBuffer_Play;
static void b20380b_c20545c_tgt(void) { return; }
static void (*const b20380b_c20545c)(void) = b20380b_c20545c_tgt;
static void b20380b_c20611c_tgt(void) { return; }
static void (*const b20380b_c20611c)(void) = b20380b_c20611c_tgt;
static void (*const b20380b_c206232)(void) = (void *)DirectSoundCreate;
static void (*const b20380b_c2060d4)(void) = (void *)IDirectSound_CreateSoundBuffer;
static void b20380b_c205a68_tgt(void) { return; }
static void (*const b20380b_c205a68)(void) = b20380b_c205a68_tgt;
static void (*const b20380b_c2060f8)(void) = (void *)IDirectSound_CreateSoundStream;
static void b20380b_c20639e_tgt(void) { return; }
static void (*const b20380b_c20639e)(void) = b20380b_c20639e_tgt;
static void b20380b_c2063cb_tgt(void) { return; }
static void (*const b20380b_c2063cb)(void) = b20380b_c2063cb_tgt;
static void b20380b_c20d4a4_tgt(void) { return; }
static void (*const b20380b_c20d4a4)(void) = b20380b_c20d4a4_tgt;
static void b20380b_c20d152_tgt(void) { return; }
static void (*const b20380b_c20d152)(void) = b20380b_c20d152_tgt;
static void b20380b_c20672a_tgt(void) { return; }
static void (*const b20380b_c20672a)(void) = b20380b_c20672a_tgt;
static void b20380b_c20d780_tgt(void) { return; }
static void (*const b20380b_c20d780)(void) = b20380b_c20d780_tgt;
static void b20380b_c20d118_tgt(void) { return; }
static void (*const b20380b_c20d118)(void) = b20380b_c20d118_tgt;
static void b20380b_c20ab80_tgt(void) { return; }
static void (*const b20380b_c20ab80)(void) = b20380b_c20ab80_tgt;
static void b20380b_c2063b8_tgt(void) { return; }
static void (*const b20380b_c2063b8)(void) = b20380b_c2063b8_tgt;
static void (*const b20380b_c209e6d)(void) = (void *)CMcpxVoiceClient_Commit3dSettings;
static void b20380b_c206d25_tgt(void) { return; }
static void (*const b20380b_c206d25)(void) = b20380b_c206d25_tgt;
static void b20380b_c206476_tgt(void) { return; }
static void (*const b20380b_c206476)(void) = b20380b_c206476_tgt;
static void b20380b_c20391d_tgt(void) { return; }
static void (*const b20380b_c20391d)(void) = b20380b_c20391d_tgt;
static void b20380b_c20cc90_tgt(void) { return; }
static void (*const b20380b_c20cc90)(void) = b20380b_c20cc90_tgt;
static void b20380b_c20d988_tgt(void) { return; }
static void (*const b20380b_c20d988)(void) = b20380b_c20d988_tgt;
static void b20380b_c20d92d_tgt(void) { return; }
static void (*const b20380b_c20d92d)(void) = b20380b_c20d92d_tgt;
static void b20380b_c20d731_tgt(void) { return; }
static void (*const b20380b_c20d731)(void) = b20380b_c20d731_tgt;
static void b20380b_c20af71_tgt(void) { return; }
static void (*const b20380b_c20af71)(void) = b20380b_c20af71_tgt;
static void b20380b_c20ba21_tgt(void) { return; }
static void (*const b20380b_c20ba21)(void) = b20380b_c20ba21_tgt;
static void b20380b_c20bbe4_tgt(void) { return; }
static void (*const b20380b_c20bbe4)(void) = b20380b_c20bbe4_tgt;
static void b20380b_c20c0d2_tgt(void) { return; }
static void (*const b20380b_c20c0d2)(void) = b20380b_c20c0d2_tgt;
static void b20380b_c206844_tgt(void) { return; }
static void (*const b20380b_c206844)(void) = b20380b_c206844_tgt;
static void b20380b_c20678c_tgt(void) { return; }
static void (*const b20380b_c20678c)(void) = b20380b_c20678c_tgt;
static void b20380b_c206870_tgt(void) { return; }
static void (*const b20380b_c206870)(void) = b20380b_c206870_tgt;
static void b20380b_c206d0a_tgt(void) { return; }
static void (*const b20380b_c206d0a)(void) = b20380b_c206d0a_tgt;
static void b20380b_c206ca8_tgt(void) { return; }
static void (*const b20380b_c206ca8)(void) = b20380b_c206ca8_tgt;
static void b20380b_c207392_tgt(void) { return; }
static void (*const b20380b_c207392)(void) = b20380b_c207392_tgt;

__attribute__((naked, noinline))
void CMcpxAPU_ServiceDeferredCommandsLow(void)
{
  __asm__ volatile(
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_379\n\t"
      ".byte 0xe9, 0x6b, 0x60, 0x00, 0x00\n\t"
      "movl 0x148(%%ecx), %%eax\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movzwl 0x2(%%ecx), %%edx\n\t"
      "movzwl 0xe(%%ecx), %%eax\n\t"
      "imull %%edx, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $8\n\t"
      "cdq\n\t"
      "popl %%esi\n\t"
      "idivl %%esi\n\t"
      "movzwl 0xc(%%ecx), %%ecx\n\t"
      "popl %%esi\n\t"
      "shll $5, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jg .LCMcpxAPU_ServiceDeferredCommandsLow_1\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_1:\n\t"
      "addl %%eax, %%eax\n\t"
      "ret\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_2:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%ecx)\n\t"
      "ret\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x1c(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_3:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x1c(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%ecx)\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *(%%eax)\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *(%%eax)\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0xfe80200c, %%eax\n\t"
      "ret\n\t"
      "call *%[c20368b]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x20a2f5, 0x222d64\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_4\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_4:\n\t"
      "ret\n\t"
      "call *%[c20368b]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x20a431, 0x222d64\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_5\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_5:\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl $0x2c2610, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_6:\n\t"
      "movl $0x2c2610, (%%ecx)\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_7:\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "incl 0x4(%%ecx)\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_8\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_8:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_9:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "decl 0x4(%%ecx)\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_10\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl $1\n\t"
      "call *(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_10:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_11\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_11:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl $0x2c2610, (%%ecx)\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_12\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%eax, 0x10(%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_13\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_12:\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "leal 0xc(%%ecx), %%edi\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      "popl %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_13:\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c20376b]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_14\n\t"
      "movl 0x222ce8, %%eax\n\t"
      "movl 0x222ce4, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_14:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_15\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_15:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c203995]\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *%[c2037ad]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_16\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_16:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207aca]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_17\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_17:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207b73]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_18\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_18:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c207876]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_19\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_19:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c206dc4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_20\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_20:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207234]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_21\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_21:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207265]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_22\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_22:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207289]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_23\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_23:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c2072ad]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_24\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_24:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c2072d1]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_25\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_25:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207309]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_26\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_26:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207334]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_27\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_27:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "cmpl $-1, 0xc(%%ecx)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_28\n\t"
      "movl $0x88780032, %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_29\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_28:\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c20735f]\n\t"
      "movl %%eax, %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_29:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_30\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_30:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_31\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_31:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *0x25313c\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c2073d9]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_32\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_32:\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "cmpl %%edx, 0xc(%%ebp)\n\t"
      "setne %%dl\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_38\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_33\n\t"
      "orl $0x80000000, %%ebx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_34\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_33:\n\t"
      "andl $0x7fffffff, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_34:\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c206df8]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_37\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%ebx, 0x8(%%eax)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_37\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl $0x34\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207b73]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_37\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_35\n\t"
      "andl $0xfffffffd, -0x28(%%ebp)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_36\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_35:\n\t"
      "orl $2, -0x28(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_36:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "pushl $1\n\t"
      "pushl $0x34\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xd0(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c207aca]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_37:\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_38:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_39\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_39:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x2c261c, (%%eax)\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "subl 0x1c(%%ecx), %%eax\n\t"
      "movl %%eax, 0x18(%%ecx)\n\t"
      "ret\n\t"
      "movl 0x1c(%%ecx), %%eax\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%eax, 0x18(%%ecx)\n\t"
      "movl %%edx, 0x1c(%%ecx)\n\t"
      "ret\n\t"
      "testb $0x10, 0xc(%%ecx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_40\n\t"
      "movl $0x7c0, 0x20(%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_42\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_40:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_41\n\t"
      "movl 0x10(%%ecx), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "movl 0x20f0a8(,%%eax,4), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_41:\n\t"
      "movl %%eax, 0x20(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_42:\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_43:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "movl %%edx, 0x14(%%ecx)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c209961]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_44\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_44:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_45:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%ecx), %%eax\n\t"
      "subl 0x1c(%%eax), %%edx\n\t"
      "movl %%edx, 0x18(%%eax)\n\t"
      "movl 0x14(%%ecx), %%ecx\n\t"
      "call *%[c209880]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_46\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_46:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_47:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c209c05]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_48\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_48:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_49:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c209d16]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_50\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_50:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_51:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c208da2]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_52\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_52:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_53:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "addl %%ecx, 0x18(%%eax)\n\t"
      "movl %%esi, 0x1c(%%eax)\n\t"
      "movl 0x14(%%edx), %%ecx\n\t"
      "call *%[c209880]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_54\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_54:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_55:\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl $0x24\n\t"
      "popl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_56:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "testl %%ebx, 0xc(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_58\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0x10(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_57\n\t"
      "movl (%%edi), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_57:\n\t"
      "movl 0x18(%%edx), %%ecx\n\t"
      "movl %%eax, (%%esi,%%ecx,1)\n\t"
      "addl $4, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_58:\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "testl %%ebx, 0x20(%%eax)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_59\n\t"
      "addl $4, %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_59:\n\t"
      "incl -0x4(%%ebp)\n\t"
      "cmpl $0x20, -0x4(%%ebp)\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_56\n\t"
      "movl 0x14(%%edx), %%ecx\n\t"
      "call *%[c209880]\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_60\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_60:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_61:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a0ef]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_62\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_62:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_63:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a11d]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_64\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_64:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a145]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_65\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_65:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_66:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a16d]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_67\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_67:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c20a18e]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_68\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_68:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c20a1af]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_69\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_69:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_70:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a1d0]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_71\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_71:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a1f1]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_72\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_72:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a219]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_73\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_73:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_74:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a241]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_75\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_75:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_76\n\t"
      "movl 0x4c(%%ecx), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_77\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_76:\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_77:\n\t"
      "movl %%edx, 0x50(%%ecx)\n\t"
      "movl %%eax, 0x54(%%ecx)\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20baa4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_78\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_78:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testb $3, %%al\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_79\n\t"
      "shrl $1, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20badd]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_80\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_79:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b873]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_80:\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_81\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_81:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b0ac]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_82\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_82:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "cmpl 0x50(%%ecx), %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_83\n\t"
      "cmpl 0x54(%%ecx), %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_84\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_83:\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c204388]\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "call *%[c20b856]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_84:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_85\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_85:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b0f7]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_86\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_86:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "testb $1, 0x24(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_87\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c2044b5]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_93\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_87:\n\t"
      "testb $2, 0x24(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_88\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl 0x4c(%%eax), %%eax\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_89\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_88:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_89:\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl 0x48(%%ecx), %%ecx\n\t"
      "addl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl 0x4c(%%ecx), %%ecx\n\t"
      "subl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_90\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_90:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_92\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_92\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jae .LCMcpxAPU_ServiceDeferredCommandsLow_91\n\t"
      "movl 0x1c(%%esi), %%esi\n\t"
      "movl 0x48(%%esi), %%esi\n\t"
      "movl %%esi, (%%edx)\n\t"
      "subl (%%edi), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_92\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_91:\n\t"
      "andl $0, (%%edx)\n\t"
      "andl $0, (%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_92:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_93:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_94\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_94:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b8d7]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_95\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_95:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, 0x24(%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_99\n\t"
      "cmpl %%edi, 0x28(%%esi)\n\t"
      "jbe .LCMcpxAPU_ServiceDeferredCommandsLow_99\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%esp), %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_96:\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "leal (%%eax,%%edi,8), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_97\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "addl %%ebx, %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jae .LCMcpxAPU_ServiceDeferredCommandsLow_98\n\t"
      "pushl $0\n\t"
      "pushl 0x4(%%eax)\n\t"
      "call *0x2530e8\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_97:\n\t"
      "incl %%edi\n\t"
      "cmpl 0x28(%%esi), %%edi\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_96\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_98:\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_99:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%esp), %%edi\n\t"
      "cmpl $0, 0x24(%%edi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_102\n\t"
      "pushl %%esi\n\t"
      "movl 0x28(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jbe .LCMcpxAPU_ServiceDeferredCommandsLow_101\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_100:\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "leal (%%eax,%%esi,8), %%eax\n\t"
      "cmpl $-1, -0x8(%%eax)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_101\n\t"
      "pushl $0\n\t"
      "pushl -0x4(%%eax)\n\t"
      "call *0x2530e8\n\t"
      "decl %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_100\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_101:\n\t"
      "popl %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_102:\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "decl %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jbe .LCMcpxAPU_ServiceDeferredCommandsLow_106\n\t"
      "pushl %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_103:\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "leal (%%eax,%%edx,8), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "leal 0x8(%%eax), %%ecx\n\t"
      "cmpl (%%ecx), %%edi\n\t"
      "jbe .LCMcpxAPU_ServiceDeferredCommandsLow_104\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c203704]\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_105\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_104:\n\t"
      "incl %%edx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_105:\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_103\n\t"
      "popl %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_106:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "movl $0x15, (%%esi)\n\t"
      "movl 0x24(%%edi), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c203815]\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movl 0x20(%%edi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0xc(%%eax), %%eax\n\t"
      "andl $0, 0x8(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_107\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_107:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20c752]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_108\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_108:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20c3fe]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_109\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_109:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20bc71]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_110\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_110:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "call *%[c20bc71]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_111\n\t"
      "movl $0x88780032, %%eax\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_112\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_111:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "call *%[c20c636]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_112:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_113:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20c050]\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0, (%%eax)\n\t"
      "andl $0, 0x4(%%eax)\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "pushl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_114\n\t"
      "movl 0xc(%%eax), %%esi\n\t"
      "movl %%esi, 0xc(%%edx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_114:\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_115\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_115:\n\t"
      "cmpl (%%ecx), %%eax\n\t"
      "popl %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_116\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_116:\n\t"
      "cmpl 0x4(%%ecx), %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_117\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_117:\n\t"
      "andl $0, 0x8(%%eax)\n\t"
      "andl $0, 0xc(%%eax)\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_118\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_118:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_119\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_119:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_120\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_120:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_121\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_121:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_122\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_122:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_123\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x4(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_123:\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_124\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_124:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_125\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_125:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_126\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_126:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_127\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_127:\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_128\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_128:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_129\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_129:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_130\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_130:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_131\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_131:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_132\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_132:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_133\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x8(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_133:\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_134\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_135\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_134:\n\t"
      "movl (%%ecx), %%edx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_135:\n\t"
      "testl %%esi, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_136\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_136:\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_137\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_137:\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl (%%ecx), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_139\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_139\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_138\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_138:\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_141\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_140\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_139:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_140:\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_141:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_2\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_3\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_45\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_43\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_47\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_49\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_51\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_53\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_55\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_61\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_63\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204163]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_66\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c2041f0]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c20422f]\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_70\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c2042a9]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c2042fb]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_74\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f32]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f69]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fa3]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fd4]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204005]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204036]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_142:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204075]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_143:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2040e9]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_144:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c204124]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c204163]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_145:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2041b5]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c2041f0]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c20422f]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_146:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20426e]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c2042a9]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c2042fb]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_147:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20434d]\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c20384b]\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c20384b]\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2039b7]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203a07]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203a21]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203ab0]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203a65]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203af2]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203e0a]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203b25]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203b5a]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203b95]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203bd4]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x24(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0x18, %%esp\n\t"
      "fstps 0x14(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "fstps 0x10(%%esp)\n\t"
      "negl %%ecx\n\t"
      "flds 0x18(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "fstps 0xc(%%esp)\n\t"
      "andl %%eax, %%ecx\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203c52]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203cba]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203c13]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203d0c]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203da9]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203dd4]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203d5e]\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c203881]\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c203881]\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203f69]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203f32]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203fa3]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203fd4]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204005]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204036]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204075]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2040e9]\n\t"
      "ret\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204124]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2049aa]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2041b5]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2049d8]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2049f0]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20426e]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204a0d]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204a36]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2043a4]\n\t"
      "ret\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2043e1]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204468]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204437]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2044b5]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204590]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x24(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x20(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2044ea]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20434d]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f69]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f32]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fa3]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fd4]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204005]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204036]\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_142\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_143\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_144\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204b28]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_145\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c204b6d]\n\t"
      "ret\n\t"
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c204b89]\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_146\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204bbd]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204bea]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_113\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_147\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x222ce0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_148\n\t"
      "pushl %%eax\n\t"
      "call *%[c203de3]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_148:\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_149\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_149:\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $0x2c2610, (%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_150\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_150:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $1, 0x4(%%esi)\n\t"
      "movl $0x2c2628, (%%esi)\n\t"
      "movl 0x222670, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xffff, %%ecx\n\t"
      "cmpl $2, %%ecx\n\t"
      "ja .LCMcpxAPU_ServiceDeferredCommandsLow_151\n\t"
      "testl $0xfffc0000, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_152\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_151:\n\t"
      "call *%[c1d4507]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_152:\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "call *%[c203995]\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $0x2c2610, (%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_153\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_153:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x2c2634, (%%eax)\n\t"
      "andl $0, 0x10(%%eax)\n\t"
      "andl $0, 0x14(%%eax)\n\t"
      "movl %%eax, 0x222ce0\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_7\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x2c2634, (%%esi)\n\t"
      "call *%[c2047f5]\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20480b]\n\t"
      "andl $0, 0x222ce0\n\t"
      "movl $0x2c2610, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%ecx, %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c20484d]\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x82000, %%ecx\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_155\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_154:\n\t"
      "movl %%edi, 0x1c(%%esi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_156\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_155:\n\t"
      "testb $0x10, %%al\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_154\n\t"
      "movl $0x258, 0x1c(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_156:\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_157\n\t"
      "movl $0x20f098, 0x10(%%esi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_158\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_157:\n\t"
      "pushl 0x14(%%esp)\n\t"
      "call *%[c20cb4b]\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x7ff8fff2, %%eax\n\t"
      "addl $0x8007000e, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_159\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_158:\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "negl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "call *%[c203f07]\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "pushl 0x4(%%eax)\n\t"
      "call *%[c20c857]\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_159:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "leal 0x44(%%ecx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c204821]\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *%[c204862]\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_160:\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x10(%%esi), %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "addl $0x10, %%ecx\n\t"
      "movl $0x2c2640, (%%esi)\n\t"
      "call *%[c20478b]\n\t"
      "pushl %%edi\n\t"
      "call *%[c2047df]\n\t"
      "leal 0x14(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204877]\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20488d]\n\t"
      "popl %%edi\n\t"
      "movl $0x2c2610, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c2048a3]\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "call *%[c2048b8]\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_161:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_162\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_162:\n\t"
      "pushl %%eax\n\t"
      "call *%[c20c857]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c203f32]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_163\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_163:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "leal -0x1c(%%esi), %%eax\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "andl %%eax, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_165\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_164\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "call *%[c2090ca]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_165\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_164:\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c20552e]\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_165\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "call *%[c208f52]\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_165:\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_166\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_166:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_167:\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl 0x20(%%ecx), %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_168\n\t"
      "pushl %%edi\n\t"
      "call *%[c203f07]\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "call *%[c2097a9]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_168\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c204075]\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_168:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_169\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_169:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $0x80000000, %%ebx\n\t"
      "testl %%ebx, 0xc(%%esi)\n\t"
      "pushl %%edi\n\t"
      "leal 0x48(%%esi), %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_170\n\t"
      "andl $0, (%%edi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_171\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_170:\n\t"
      "pushl %%edi\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_171:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4c(%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_173\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_172\n\t"
      "orl %%ebx, 0xc(%%esi)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_173\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_172:\n\t"
      "andb $0x7f, 0xf(%%esi)\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c203609]\n\t"
      "movl %%eax, (%%edi)\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x7ff8fff2, %%eax\n\t"
      "addl $0x8007000e, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_174\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_173:\n\t"
      "movl 0x4c(%%esi), %%eax\n\t"
      "andl $0, 0x50(%%esi)\n\t"
      "movl %%eax, 0x54(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_174:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x2c264c, (%%esi)\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2048cd]\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203664]\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2048e3]\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_175\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_175:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%ecx\n\t"
      "popl %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_160\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_7\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_9\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl 0x48(%%eax), %%edi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_176\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpl 0x4c(%%eax), %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_177\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_176:\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "call *%[c20b46d]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_177\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c2056a8]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_177\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_177\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_177\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "call *%[c20ba90]\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_177:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_178\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_178:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl 0x18(%%esp)\n\t"
      "call *%[c2043a4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_179\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_179:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c2043e1]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_180\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_180:\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "addl $0x24, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c203664]\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%edi, 0x28(%%eax)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_181\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl %%edi, %%eax\n\t"
      "shll $3, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203609]\n\t"
      "movl %%eax, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_181\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c204637]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_181:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl 0x10(%%esp)\n\t"
      "call *%[c2055e4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_182\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_182:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_187\n\t"
      "jbe .LCMcpxAPU_ServiceDeferredCommandsLow_183\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c2045c1]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_186\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_183:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c204437]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_186\n\t"
      "testb $4, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_184\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl 0x50(%%eax), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_184\n\t"
      "movl 0x54(%%eax), %%eax\n\t"
      "leal (%%eax,%%ecx,1), %%edx\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jae .LCMcpxAPU_ServiceDeferredCommandsLow_184\n\t"
      "movl %%ecx, %%ebx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_185\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_184:\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl 0x4c(%%eax), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_185:\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c2045c1]\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c2045c1]\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_186:\n\t"
      "movl %%edi, 0x2c(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_187:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_188\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_188:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_189:\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c204605]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_190\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_190:\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x14(%%esi)\n\t"
      "movl %%ecx, %%edi\n\t"
      "pushl 0x8(%%esi)\n\t"
      "pushl (%%esi)\n\t"
      "pushl 0x18(%%esp)\n\t"
      "call *%[c2054a8]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_191\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x48(%%edi)\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4c(%%edi)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x50(%%edi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_191:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x2c2664, -0x4(%%esi)\n\t"
      "movl $0x2c2658, (%%esi)\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2048f9]\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20490f]\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_192\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_192:\n\t"
      "leal -0x4(%%esi), %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "popl %%edi\n\t"
      "andl %%esi, %%ecx\n\t"
      "popl %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_160\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_193:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203936]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_194:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20395b]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_195:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x18(%%eax)\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_196\n\t"
      "pushl 0x14(%%esp)\n\t"
      "addl $4, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c2055e4]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_196:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_197\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_197:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "pushl 0x4(%%esp)\n\t"
      "pushl 0x4(%%ecx)\n\t"
      "call *%[c204925]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_198\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203861]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_198:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_199\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203897]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_199:\n\t"
      "ret\n\t"
      "subl $4, 0x4(%%esp)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_193\n\t"
      "subl $4, 0x4(%%esp)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_194\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_161\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_167\n\t"
      "pushl 0x4(%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c2058c2]\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_189\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2055a1]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205650]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2055a1]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205894]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205650]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_200:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2057dd]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20580f]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_201:\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205768]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20583f]\n\t"
      "ret\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2055a1]\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_195\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205650]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c20547e]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_202\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_202:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c20395b]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $1, %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_203\n\t"
      "addl $0x18, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c205a7e]\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_203:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_204\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_204:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_205:\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "cmpl $0, 0x44(%%esi)\n\t"
      "movl $0x2c261c, (%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_206\n\t"
      "pushl $0\n\t"
      "call *%[c20552e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_206:\n\t"
      "testl $0x82000, 0xc(%%esi)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_207\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_207:\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20480b]\n\t"
      "movl $0x2c2610, (%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $1, 0x4(%%esi)\n\t"
      "movl $0x2c2640, (%%esi)\n\t"
      "call *%[c2047ca]\n\t"
      "pushl %%esi\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "call *%[c205a59]\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c205547]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_208\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_208:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x2c2680, (%%eax)\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl $0\n\t"
      "movl $0x2c2680, (%%esi)\n\t"
      "call *%[c2056a8]\n\t"
      "movl %%esi, %%ecx\n\t"
      "popl %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_205\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x10(%%esi)\n\t"
      "movl %%ecx, %%edi\n\t"
      "pushl 0xc(%%esi)\n\t"
      "pushl 0x4(%%esi)\n\t"
      "pushl 0x18(%%esp)\n\t"
      "call *%[c2054a8]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_211\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "testl $0x80000, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_209\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x58(%%edi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_210\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_209:\n\t"
      "testb $0x20, %%ch\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_210\n\t"
      "movl $0x80000000, 0x58(%%edi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_210:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_211\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c2056a8]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_211:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c205c86]\n\t"
      "movl $0x2c264c, (%%esi)\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c20571a]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_212\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_212:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "call *%[c20368b]\n\t"
      "pushl $0\n\t"
      "pushl $0x5c\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c203609]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_213\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x2c2680, (%%eax)\n\t"
      "movl %%eax, %%ecx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_214\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_213:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_214:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "negl %%edi\n\t"
      "sbbl %%edi, %%edi\n\t"
      "andl $0x7ff8fff2, %%edi\n\t"
      "addl $0x8007000e, %%edi\n\t"
      "movl %%ecx, 0x1c(%%esi)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_218\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%eax)\n\t"
      "call *%[c205cff]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_217\n\t"
      "testb $1, 0x5(%%ebx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_215\n\t"
      "movl $0x205ab2, -0xc(%%ebp)\n\t"
      "movl $0x205ac2, -0x8(%%ebp)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_216\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_215:\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_216:\n\t"
      "leal 0x20(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "pushl 0x1c(%%esi)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c2070d6]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_217\n\t"
      "pushl 0x1c(%%esi)\n\t"
      "pushl (%%ebx)\n\t"
      "pushl %%esi\n\t"
      "call *%[c205580]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_217:\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_218:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_219\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_219:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x2c268c, (%%eax)\n\t"
      "ret\n\t"
      "movl $0x2c268c, (%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_205\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0xc(%%esp)\n\t"
      "leal 0x4(%%esi), %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c205c86]\n\t"
      "movl $0x2c2658, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movl $0x2c2664, (%%esi)\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c2059b0]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_220\n\t"
      "leal -0x4(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_220:\n\t"
      "leal -0x4(%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20368b]\n\t"
      "pushl $0\n\t"
      "pushl $0x54\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c203609]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_221\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movl $0x2c268c, (%%eax)\n\t"
      "movl %%eax, %%ecx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_222\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_221:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_222:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "negl %%edi\n\t"
      "sbbl %%edi, %%edi\n\t"
      "andl $0x7ff8fff2, %%edi\n\t"
      "addl $0x8007000e, %%edi\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_224\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%eax)\n\t"
      "call *%[c205979]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_223\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebx)\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "pushl 0x20(%%esi)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207141]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_223\n\t"
      "pushl 0x20(%%esi)\n\t"
      "addl $4, %%esi\n\t"
      "pushl 0x20(%%esi)\n\t"
      "pushl %%esi\n\t"
      "call *%[c205580]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_223:\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_224:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_225\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_225:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_200\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_201\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x30\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c203609]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_226\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c205d52]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_226:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_227\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c205d8e]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_227\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "addl $0x1c, %%edi\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%edi, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_228\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_227:\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204821]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_228:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_229\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_229:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x28\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c203609]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_230\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c205e69]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_230:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_231\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c205eb6]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_231\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_232\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_231:\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204837]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_232:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_233\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_233:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c205c4d]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_234\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_234:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c205ce5]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_235\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_235:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $0x2c268c, (%%esi)\n\t"
      "call *%[c205c4d]\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_236\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[c203664]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_236:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_237:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205f6d]\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_238:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205fed]\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "call *%[c20368b]\n\t"
      "pushl $0\n\t"
      "pushl $0x14\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c203609]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_239\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c2053f9]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_240\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_239:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_240:\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "negl %%eax\n\t"
      "pushl %%esi\n\t"
      "sbbl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "andl $0x7ff8fff2, %%eax\n\t"
      "movl $0x8007000e, %%edi\n\t"
      "addl %%edi, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_245\n\t"
      "pushl $0\n\t"
      "pushl $0xe78\n\t"
      "call *%[c203609]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_241\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c206eb2]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_242\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_241:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_242:\n\t"
      "movl %%eax, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "movl %%eax, 0xc(%%ebx)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_245\n\t"
      "pushl 0x8(%%ebx)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c20763c]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_245\n\t"
      "pushl $6\n\t"
      "xorl %%eax, %%eax\n\t"
      "andl %%eax, 0x8(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl $0x18, -0x1c(%%ebp)\n\t"
      "movl $0x20f108, -0x10(%%ebp)\n\t"
      "leal 0x18(%%ebx), %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_243:\n\t"
      "cmpl $1, 0x8(%%ebp)\n\t"
      "jae .LCMcpxAPU_ServiceDeferredCommandsLow_245\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl $0x3f, -0xc(%%ebp)\n\t"
      "call *%[c205f6d]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_244\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl $0x20f0c8\n\t"
      "pushl %%eax\n\t"
      "call *%[c205b7f]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_244\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c205b43]\n\t"
      "movl %%eax, %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_244:\n\t"
      "incl 0x8(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LCMcpxAPU_ServiceDeferredCommandsLow_243\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_245:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_246\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_246:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_237\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_238\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x222ce0, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_247\n\t"
      "pushl %%eax\n\t"
      "call *%[c2047ca]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_250\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_247:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x1c\n\t"
      "call *%[c203609]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_248\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c20545c]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_248:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_249\n\t"
      "pushl %%edi\n\t"
      "call *%[c20611c]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_249\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "addl $8, %%edi\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%edi, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_250\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_249:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2047df]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_250:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_251\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_251:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c206232]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_252\n\t"
      "pushl $0\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c2060d4]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_252:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205a68]\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c206232]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_253\n\t"
      "pushl $0\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c2060f8]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_253:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205a68]\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_254:\n\t"
      ".byte 0x0f, 0xb1, 0x11\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_254\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "movzbl 0x24, %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_255\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x4(%%eax)\n\t"
      "movl %%eax, (%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_255:\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl (%%eax), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c20639e]\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movzbl 0x24, %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb $2, %%cl\n\t"
      "cmpb %%cl, %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_256\n\t"
      "call *0x25327c\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb %%al, 0x4(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_256:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "cmpl $0, (%%ecx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_257\n\t"
      "movb 0x4(%%ecx), %%cl\n\t"
      "jmp *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_257:\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c2063cb]\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "cmpl $0, (%%ecx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_258\n\t"
      "movb 0x4(%%ecx), %%cl\n\t"
      "jmp *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_258:\n\t"
      "ret\n\t"
      "addl $1, 0x1c8(%%ecx)\n\t"
      "ret\n\t"
      "subl $1, 0x1c8(%%ecx)\n\t"
      "ret\n\t"
      "movl 0xe0(%%ecx), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_259\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_259:\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "ret\n\t"
      "movl 0xe0(%%ecx), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      "pushl $0\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *%[c203609]\n\t"
      "ret\n\t"
      "pushl $0\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *%[c203609]\n\t"
      "ret\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "leal 0x5cc(%%ebx), %%edi\n\t"
      "movl $3, -0x4(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_260:\n\t"
      "movl (%%edi), %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_262\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_261:\n\t"
      "leal -0xbc(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *0x10(%%eax)\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_262:\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_261\n\t"
      "addl $8, %%edi\n\t"
      "decl -0x4(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_260\n\t"
      "pushl $1\n\t"
      "leal 0x8(%%ebx), %%ecx\n\t"
      "call *%[c20d4a4]\n\t"
      "cmpl $0, -0xc(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_263\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_263:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c2063cb]\n\t"
      "addl $1, 0x1c8(%%esi)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0xe0(%%ebx), %%ecx\n\t"
      "movl 0x10(%%ecx), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "testb $0x10, 0xc(%%ecx)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_264\n\t"
      "movw 0x114(%%esi), %%di\n\t"
      "cmpw %%ax, %%di\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_264\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_264:\n\t"
      "leal 0x116(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%edx), %%cx\n\t"
      "subl %%edi, %%eax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_274\n\t"
      "subw %%di, 0x114(%%esi)\n\t"
      "subl %%eax, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "movw %%cx, (%%edx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_269\n\t"
      "movzwl %%di, %%edx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_265:\n\t"
      "pushl $0x40\n\t"
      "popl %%ecx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_266:\n\t"
      "movzwl %%cx, %%edi\n\t"
      "cmpl $0, 0x1cc(%%esi,%%edi,4)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_267\n\t"
      "incl %%ecx\n\t"
      "cmpw $0x100, %%cx\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_266\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_268\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_267:\n\t"
      "movzwl -0x4(%%ebp), %%edi\n\t"
      "incl -0x4(%%ebp)\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebx,%%edi,4)\n\t"
      "movl %%ebx, 0x1cc(%%esi,%%ecx,4)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_268:\n\t"
      "decl %%edx\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_265\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_269:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_275\n\t"
      "movzwl %%ax, %%ecx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_270:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_271:\n\t"
      "movzwl %%ax, %%edx\n\t"
      "cmpl %%edi, 0x1cc(%%esi,%%edx,4)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_272\n\t"
      "incl %%eax\n\t"
      "cmpw $0x40, %%ax\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_271\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_273\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_272:\n\t"
      "movzwl -0x4(%%ebp), %%edx\n\t"
      "incl -0x4(%%ebp)\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, 0x10(%%ebx,%%edx,4)\n\t"
      "movl %%ebx, 0x1cc(%%esi,%%eax,4)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_273:\n\t"
      "decl %%ecx\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_270\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_275\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_274:\n\t"
      "movl $0x88780032, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_275:\n\t"
      "subl $1, 0x1c8(%%esi)\n\t"
      "cmpl $0, -0xc(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_276\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_276:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "addl $1, 0x1c8(%%esi)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0xe0(%%edx), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_280\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_277:\n\t"
      "leal 0x10(%%edx,%%eax,4), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_280\n\t"
      "orl $0xffffffff, (%%eax)\n\t"
      "andl $0, 0x1cc(%%esi,%%ecx,4)\n\t"
      "cmpl $0x40, %%ecx\n\t"
      "jae .LCMcpxAPU_ServiceDeferredCommandsLow_278\n\t"
      "incw 0x116(%%esi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_279\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_278:\n\t"
      "incw 0x114(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_279:\n\t"
      "movl 0xe0(%%edx), %%ecx\n\t"
      "movl 0x10(%%ecx), %%ecx\n\t"
      "movzwl 0x2(%%ecx), %%ecx\n\t"
      "incl %%edi\n\t"
      "decl %%ecx\n\t"
      "sarl $1, %%ecx\n\t"
      "movzwl %%di, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_277\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_280:\n\t"
      "subl $1, 0x1c8(%%esi)\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_281\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_281:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "addl $1, 0x1c8(%%ecx)\n\t"
      "testl %%edx, %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "leal 0xbc(%%edi), %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_282\n\t"
      "addl $0xbc, %%edx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_283\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_282:\n\t"
      "leal 0x5cc(%%ecx,%%ebx,8), %%edx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_283:\n\t"
      "movl (%%edx), %%esi\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%esi, (%%eax)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movb %%bl, 0xdc(%%edi)\n\t"
      "subl $1, 0x1c8(%%ecx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xe0(%%eax), %%eax\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_284\n\t"
      "movl 0x20(%%edx), %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_284\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl $2, (%%eax)\n\t"
      "movl 0xc0(%%edx), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0x5dc, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_288\n\t"
      "addl $0xffffff44, %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_289\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_284:\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "testl $0x82000, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_285\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl $2, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_287\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_285:\n\t"
      "testb $0x10, %%al\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_286\n\t"
      "movl $1, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_287\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_286:\n\t"
      "movl %%esi, (%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_287:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_288:\n\t"
      "movl %%esi, (%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_289:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl 0x222690, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl 0x24(%%esi), %%edi\n\t"
      "pushl $0x64\n\t"
      "incl %%eax\n\t"
      "popl %%ebp\n\t"
      "movl %%eax, 0x222690\n\t"
      "notl %%eax\n\t"
      "leal 0x8(%%esi), %%ebx\n\t"
      "pushl $1\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "call *%[c20d152]\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "movl %%eax, 0xfe801324\n\t"
      "movl 0x222690, %%eax\n\t"
      "pushl $0\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%eax, 0xfe801334\n\t"
      "call *%[c20d152]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_291\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_290:\n\t"
      "movl %%ebp, %%eax\n\t"
      "decl %%ebp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_292\n\t"
      "pushl $1\n\t"
      "call *0x25328c\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_291:\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl 0x222690, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_290\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_292:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c20672a]\n\t"
      "addl $1, 0x1c8(%%esi)\n\t"
      "leal 0x5cc(%%esi), %%ebx\n\t"
      "movl $3, -0x4(%%ebp)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_294\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_293:\n\t"
      "leal -0xbc(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "call *0x14(%%eax)\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_295\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_294:\n\t"
      "movl (%%ebx), %%edi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_296\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_295:\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_296:\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_293\n\t"
      "addl $8, %%ebx\n\t"
      "decl -0x4(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_294\n\t"
      "leal 0x5e4(%%esi), %%ebx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_298\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_297:\n\t"
      "leal -0xc4(%%eax), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *0x14(%%eax)\n\t"
      "leal 0xc4(%%edi), %%eax\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_298\n\t"
      "pushl %%eax\n\t"
      "call *%[c20639e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_298:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_297\n\t"
      "subl $1, 0x1c8(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal 0x5ec(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl $0, %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_299:\n\t"
      ".byte 0x0f, 0xb1, 0x11\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_299\n\t"
      "orl %%eax, 0x5f4(%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl $0\n\t"
      "leal 0x8(%%esi), %%edi\n\t"
      "pushl $0\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c20d780]\n\t"
      "andl $0xfffffff7, 0x5ec(%%esi)\n\t"
      "andl $0xfffffff7, 0x5f4(%%esi)\n\t"
      "pushl $1\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c20d118]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movzbl 0xdc(%%esi), %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl 0x20f11c(%%eax), %%edx\n\t"
      "movl -0x1800000(%%edx), %%ebx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl 0x20f120(%%eax), %%ebx\n\t"
      "movl -0x1800000(%%ebx), %%ebx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl 0x20f124(%%eax), %%ebx\n\t"
      "movl -0x1800000(%%ebx), %%ebx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "leal 0x5cc(%%edi,%%ecx,8), %%edi\n\t"
      "movl 0xc0(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_300\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      "movl $0xffff, %%ecx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_301\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_300:\n\t"
      "movl 0x24(%%ecx), %%ebx\n\t"
      "movl 0x10(%%ebx), %%ebx\n\t"
      "movzwl 0x2(%%ebx), %%ebx\n\t"
      "addl $0xffffff44, %%ecx\n\t"
      "decl %%ebx\n\t"
      "sarl $1, %%ebx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x10(%%ecx,%%ebx,4), %%ecx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_301:\n\t"
      "movl 0xbc(%%esi), %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_302\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl $0xffff, %%edi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_303\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_302:\n\t"
      "leal -0xbc(%%ebx), %%edi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl 0x10(%%edi), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_303:\n\t"
      "cmpl %%ebx, -0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_304\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x30(%%edx), %%edx\n\t"
      "shll $7, %%ecx\n\t"
      "leal 0x7c(%%ecx,%%edx,1), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "andl $0xffff0000, %%ecx\n\t"
      "orl %%edi, %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_305\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_304:\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "movl %%edi, -0x1800000(%%edx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_305:\n\t"
      "movl 0xe0(%%esi), %%ecx\n\t"
      "movl 0x10(%%ecx), %%ecx\n\t"
      "movzwl 0x2(%%ecx), %%ecx\n\t"
      "decl %%ecx\n\t"
      "sarl $1, %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_314\n\t"
      "leal 0x10(%%esi), %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_306:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "cmpl %%ecx, -0x1c(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_307\n\t"
      "movl $1, -0x14(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_307:\n\t"
      "cmpl %%ecx, -0x20(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_308\n\t"
      "movl $1, -0x18(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_308:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x30(%%edx), %%edx\n\t"
      "movzwl (%%ebx), %%ebx\n\t"
      "shll $7, %%ecx\n\t"
      "leal 0x7c(%%ecx,%%edx,1), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "andl $0xffff0000, %%ecx\n\t"
      "orl %%ebx, %%ecx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "incl -0x8(%%ebp)\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0xe0(%%esi), %%ecx\n\t"
      "movl 0x10(%%ecx), %%ecx\n\t"
      "movzwl 0x2(%%ecx), %%ecx\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%ecx\n\t"
      "sarl $1, %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_306\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, -0x14(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_312\n\t"
      "cmpl %%ecx, -0xc(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_309\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x30(%%ecx), %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "shll $7, %%edi\n\t"
      "movl 0x7c(%%edi,%%ecx,1), %%edi\n\t"
      "movl $0xffff, %%ecx\n\t"
      "andl %%ecx, %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_311\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_310\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_309:\n\t"
      "movl $0xffff, %%edx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_310:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_311:\n\t"
      "movl 0x20f120(%%eax), %%ecx\n\t"
      "movl %%edx, -0x1800000(%%ecx)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_313\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_312:\n\t"
      "cmpl %%ecx, -0x18(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_314\n\t"
      "cmpl %%ecx, -0xc(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_313\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_313:\n\t"
      "movl 0x20f124(%%eax), %%eax\n\t"
      "movl %%edi, -0x1800000(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_314:\n\t"
      "leal 0xbc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20639e]\n\t"
      "orb $0xff, 0xdc(%%esi)\n\t"
      "testl $0x10000000, 0x8(%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_315\n\t"
      "andl $0xefffffff, 0x8(%%esi)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_316\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_315:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x5e8(%%ecx), %%edx\n\t"
      "addl $0x5e4, %%ecx\n\t"
      "leal 0xc4(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_316:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x238, %%esp\n\t"
      "testb $1, 0x222d60\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_317\n\t"
      "orl $1, 0x222d60\n\t"
      "movl $0x108, 0x20f140\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_317:\n\t"
      "addl $0x1b4, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl $0, %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_318:\n\t"
      ".byte 0x0f, 0xb1, 0x11\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_318\n\t"
      "orl %%eax, 0x8(%%ebp)\n\t"
      "testb $0x26, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_319\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x170(%%eax)\n\t"
      "fmuls 0x168(%%eax)\n\t"
      "flds 0x174(%%eax)\n\t"
      "fmuls 0x164(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1b8(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x174(%%eax)\n\t"
      "fmuls 0x160(%%eax)\n\t"
      "flds 0x16c(%%eax)\n\t"
      "fmuls 0x168(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1bc(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x16c(%%eax)\n\t"
      "fmuls 0x164(%%eax)\n\t"
      "flds 0x170(%%eax)\n\t"
      "fmuls 0x160(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1c0(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_319:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb $1, 0x9(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_320\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_320\n\t"
      "movl $0x118, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x238(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207b73]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_320\n\t"
      "leal -0x238(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x184, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20ab80]\n\t"
      "orl $4, -0x228(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "leal -0x228(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl 0xc(%%ecx)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207aca]\n\t"
      "pushl %%edi\n\t"
      "pushl 0x20f140\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%ecx)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207aca]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c207876]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_320:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c2063cb]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_322\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_321:\n\t"
      "pushl %%eax\n\t"
      "call *%[c2063b8]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $0xffffff34, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_322:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x118, %%eax\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_321\n\t"
      "cmpl %%edi, -0x14(%%ebp)\n\t"
      "movl 0x2531b0, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_323\n\t"
      "movb -0x10(%%ebp), %%cl\n\t"
      "call *%%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_323:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_325\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_324:\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0xcc(%%esi), %%ecx\n\t"
      "call *%[c209e6d]\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_325:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_324\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_327\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_326:\n\t"
      "pushl %%esi\n\t"
      "call *%[c20639e]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x11c(%%eax), %%ecx\n\t"
      "addl $0x118, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "leal -0xcc(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%ecx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_327:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_326\n\t"
      "cmpl %%edi, -0x14(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_328\n\t"
      "movb -0x10(%%ebp), %%cl\n\t"
      "call *%%ebx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_328:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "testb $2, 0x8(%%eax)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_329\n\t"
      "movl 0x18(%%eax), %%edx\n\t"
      "movl 0x10(%%edx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1c(%%eax), %%esi\n\t"
      "leal (%%esi,%%edx,2), %%edx\n\t"
      "movl %%eax, 0x664(%%ecx,%%edx,4)\n\t"
      "popl %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_329:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "leal 0x65c(%%edi), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "sete %%bl\n\t"
      "call *%[c20639e]\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_330\n\t"
      "leal 0x618(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531e4\n\t"
      "addl $0x640, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *0x2532d0\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_331\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_330:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_331\n\t"
      "leal 0x640(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x14(%%eax)\n\t"
      "addl $0x618, %%edi\n\t"
      "pushl 0x10(%%eax)\n\t"
      "pushl %%edi\n\t"
      "call *0x2531e0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_331:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x18(%%eax), %%edx\n\t"
      "movl 0x10(%%edx), %%edx\n\t"
      "movl 0x1c(%%eax), %%eax\n\t"
      "leal (%%eax,%%edx,2), %%eax\n\t"
      "andl $0, 0x664(%%ecx,%%eax,4)\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "leal 0x65c(%%ebx), %%edi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_334\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_332:\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25313c\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "cmpl -0x4(%%ebp), %%eax\n\t"
      "jg .LCMcpxAPU_ServiceDeferredCommandsLow_335\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_333\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "cmpl -0x8(%%ebp), %%eax\n\t"
      "ja .LCMcpxAPU_ServiceDeferredCommandsLow_335\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_333:\n\t"
      "andl $0xfffffffd, 0x8(%%esi)\n\t"
      "pushl %%esi\n\t"
      "call *%[c20639e]\n\t"
      "pushl 0x20(%%esi)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl 0x1c(%%esi)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "call *0x18(%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_334:\n\t"
      "movl (%%edi), %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_332\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_336\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_335:\n\t"
      "leal 0x640(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x14(%%esi)\n\t"
      "addl $0x618, %%ebx\n\t"
      "pushl 0x10(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "call *0x2531e0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_336:\n\t"
      "cmpl $0, -0x10(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_337\n\t"
      "movb -0xc(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_337:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_338:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_338\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "andl $7, %%eax\n\t"
      "movl %%eax, 0xfe820280\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0xfe820200, %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_339:\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, 0x4(%%esp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_341\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_340:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxAPU_ServiceDeferredCommandsLow_340\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "andl $7, %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_341:\n\t"
      "addl $4, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $0xfe820280, %%eax\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_339\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "movl $0xffff, %%eax\n\t"
      "andl %%eax, %%ebx\n\t"
      "cmpl $2, %%ebx\n\t"
      "movl $0x80010000, %%esi\n\t"
      "movl $0x10000, %%edx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_342\n\t"
      "andl %%esi, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_342\n\t"
      "andl $0, 0x8(%%ebp)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_343\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_342:\n\t"
      "movl $1, 0x8(%%ebp)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_343:\n\t"
      "movl 0xcc(%%edi), %%ecx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "andl %%eax, %%ebx\n\t"
      "cmpl $2, %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_344\n\t"
      "andl %%esi, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_344\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_345\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_344:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_345:\n\t"
      "cmpl %%eax, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_348\n\t"
      "addl $0x118, %%edi\n\t"
      "movl (%%edi), %%esi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_347\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_346:\n\t"
      "pushl $0xb6\n\t"
      "leal -0xcc(%%esi), %%ecx\n\t"
      "call *%[c209e6d]\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_347:\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_346\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_348:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_349\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_349:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "call *%[c206d25]\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "addl $0xfffff19c, %%ecx\n\t"
      "call *%[c206476]\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c20391d]\n\t"
      "leal 0x8(%%esi), %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c20cc90]\n\t"
      "leal 0x120(%%esi), %%ecx\n\t"
      "movl $0x2c269c, (%%esi)\n\t"
      "movl $0x2c2698, (%%edi)\n\t"
      "call *%[c20d988]\n\t"
      "pushl $3\n\t"
      "leal 0x5cc(%%esi), %%eax\n\t"
      "popl %%ecx\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_350:\n\t"
      "movl %%eax, 0x4(%%eax)\n\t"
      "movl %%eax, (%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_350\n\t"
      "fldz\n\t"
      "andl $0, 0x188(%%esi)\n\t"
      "fstps 0x148(%%esi)\n\t"
      "leal 0x5e4(%%esi), %%eax\n\t"
      "fldz\n\t"
      "movl %%eax, 0x5e8(%%esi)\n\t"
      "fstps 0x14c(%%esi)\n\t"
      "movl %%eax, (%%eax)\n\t"
      "fldz\n\t"
      "leal 0x118(%%esi), %%eax\n\t"
      "movl %%eax, 0x11c(%%esi)\n\t"
      "fstps 0x150(%%esi)\n\t"
      "movl %%eax, (%%eax)\n\t"
      "fldz\n\t"
      "leal 0x65c(%%esi), %%eax\n\t"
      "movl %%eax, 0x660(%%esi)\n\t"
      "fstps 0x154(%%esi)\n\t"
      "pushl $0x40\n\t"
      "fldz\n\t"
      "movl %%eax, (%%eax)\n\t"
      "popl %%eax\n\t"
      "fstps 0x158(%%esi)\n\t"
      "movw %%ax, 0x116(%%esi)\n\t"
      "fldz\n\t"
      "movl %%eax, 0x144(%%esi)\n\t"
      "movl $0xffffd8f0, %%eax\n\t"
      "fstps 0x15c(%%esi)\n\t"
      "movl %%eax, 0x184(%%esi)\n\t"
      "fldz\n\t"
      "movl %%eax, 0x198(%%esi)\n\t"
      "movl %%eax, 0x1a0(%%esi)\n\t"
      "fstps 0x160(%%esi)\n\t"
      "popl %%edi\n\t"
      "fldz\n\t"
      "movw $0xc0, 0x114(%%esi)\n\t"
      "movl $0x3f000000, 0x194(%%esi)\n\t"
      "fstps 0x164(%%esi)\n\t"
      "movl $0x3ca3d70a, 0x19c(%%esi)\n\t"
      "fld1\n\t"
      "movl $0x3d23d70a, 0x1a4(%%esi)\n\t"
      "movl $0x459c4000, 0x1b0(%%esi)\n\t"
      "fstps 0x168(%%esi)\n\t"
      "movl %%esi, %%eax\n\t"
      "fldz\n\t"
      "fstps 0x16c(%%esi)\n\t"
      "fld1\n\t"
      "fstps 0x170(%%esi)\n\t"
      "fldz\n\t"
      "fstps 0x174(%%esi)\n\t"
      "fld1\n\t"
      "fstps 0x178(%%esi)\n\t"
      "fld1\n\t"
      "fstps 0x17c(%%esi)\n\t"
      "fld1\n\t"
      "fstps 0x180(%%esi)\n\t"
      "fldz\n\t"
      "fstps 0x18c(%%esi)\n\t"
      "fld1\n\t"
      "fstps 0x190(%%esi)\n\t"
      "flds 0x253f00\n\t"
      "fsts 0x1a8(%%esi)\n\t"
      "fstps 0x1ac(%%esi)\n\t"
      "fld1\n\t"
      "fstps 0x1b8(%%esi)\n\t"
      "fldz\n\t"
      "fstps 0x1bc(%%esi)\n\t"
      "fldz\n\t"
      "fstps 0x1c0(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x2c269c, (%%esi)\n\t"
      "movl $0x2c2698, 0x8(%%esi)\n\t"
      "call *%[c206476]\n\t"
      "cmpl $0, 0x222cf0\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_351\n\t"
      "pushl $0x222cf0\n\t"
      "call *0x2532c0\n\t"
      "andl $0, 0x222cf0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_351:\n\t"
      "leal 0x618(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531e4\n\t"
      "movl 0x2532d0, %%ebp\n\t"
      "leal 0x5fc(%%esi), %%edi\n\t"
      "cmpw $0x13, (%%edi)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_352\n\t"
      "pushl %%edi\n\t"
      "call *%%ebp\n\t"
      "notw (%%edi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_352:\n\t"
      "leal 0x640(%%esi), %%ebx\n\t"
      "cmpw $0x13, (%%ebx)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_353\n\t"
      "pushl %%ebx\n\t"
      "call *%%ebp\n\t"
      "movw (%%edi), %%ax\n\t"
      "notw %%ax\n\t"
      "movw %%ax, (%%ebx)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_353:\n\t"
      "leal 0xe64(%%esi), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, (%%edi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_354\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *0x253280\n\t"
      "movl %%ebx, (%%edi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_354:\n\t"
      "leal 0x120(%%esi), %%ecx\n\t"
      "call *%[c20d92d]\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "call *%[c20d731]\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%ecx\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_6\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0x230\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c203609]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_355\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c20af71]\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_356\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_355:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_356:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_357\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c20ba21]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_357\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_358\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_357:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2048cd]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_358:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0x220\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c203609]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_359\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c20bbe4]\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_360\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_359:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_360:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "js .LCMcpxAPU_ServiceDeferredCommandsLow_361\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c20c0d2]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCMcpxAPU_ServiceDeferredCommandsLow_361\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_362\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_361:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2048f9]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_362:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x2532d4, %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $0x206818, %%ebp\n\t"
      "movl $0x222cf0, %%ebx\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_366\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_363:\n\t"
      "testb $8, 0x5f4(%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_364\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c206844]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_364:\n\t"
      "testb $0x40, 0x5f4(%%esi)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_365\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20678c]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_365:\n\t"
      "andl $0, 0x5f4(%%esi)\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_366:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%%edi\n\t"
      "testb $1, 0x5f4(%%esi)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_363\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%edx\n\t"
      "movl 0x1cc(%%ecx,%%edx,4), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0xe0(%%eax), %%esi\n\t"
      "movl 0x10(%%esi), %%esi\n\t"
      "movzwl 0x2(%%esi), %%esi\n\t"
      "decl %%esi\n\t"
      "sarl $1, %%esi\n\t"
      "cmpl 0x10(%%eax,%%esi,4), %%edx\n\t"
      "popl %%esi\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_367\n\t"
      "leal 0xbc(%%eax), %%edx\n\t"
      "cmpl %%edx, (%%edx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_367\n\t"
      "pushl %%eax\n\t"
      "call *%[c206870]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_367:\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $0x10\n\t"
      "popl %%ecx\n\t"
      "leal 0x144(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "orb $0xff, 0x1b4(%%eax)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_368\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_368:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $0x60, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x178(%%ecx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_369\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_369:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $0x40, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x180(%%ecx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_370\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_370:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $4, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x17c(%%ecx)\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_371\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_371:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x160(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "leal 0x16c(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orl $0x26, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x14(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_372\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_372:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x148(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orb $0xff, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_373\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_373:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x154(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orl $0x40, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_374\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_374:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "leal 0x184(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "orw $0x180, 0x1b4(%%eax)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_375\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_375:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "testb $2, %%al\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_377\n\t"
      "testb $1, %%al\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_376\n\t"
      "call *%[c206d0a]\n\t"
      "jmp .LCMcpxAPU_ServiceDeferredCommandsLow_377\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_376:\n\t"
      "call *%[c206ca8]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_377:\n\t"
      "andl $0xfffffffd, 0x8(%%esi)\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_378\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_378:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_379:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal 0x664(%%ebx), %%edi\n\t"
      "movl $0x200, %%ebp\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_380:\n\t"
      "movl (%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCMcpxAPU_ServiceDeferredCommandsLow_381\n\t"
      "pushl 0x20(%%esi)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl 0x1c(%%esi)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "call *0x18(%%eax)\n\t"
      "testb $4, 0x8(%%esi)\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_381\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c207392]\n\t"
      ".LCMcpxAPU_ServiceDeferredCommandsLow_381:\n\t"
      "addl $4, %%edi\n\t"
      "decl %%ebp\n\t"
      "jne .LCMcpxAPU_ServiceDeferredCommandsLow_380\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20380b_c20368b), [c20376b] "m"(b20380b_c20376b), [c203995] "m"(b20380b_c203995), [c2037ad] "m"(b20380b_c2037ad), [c207aca] "m"(b20380b_c207aca), [c207b73] "m"(b20380b_c207b73), [c207876] "m"(b20380b_c207876), [c206dc4] "m"(b20380b_c206dc4), [c207234] "m"(b20380b_c207234), [c207265] "m"(b20380b_c207265), [c207289] "m"(b20380b_c207289), [c2072ad] "m"(b20380b_c2072ad), [c2072d1] "m"(b20380b_c2072d1), [c207309] "m"(b20380b_c207309), [c207334] "m"(b20380b_c207334), [c20735f] "m"(b20380b_c20735f), [c206a5e] "m"(b20380b_c206a5e), [c2073d9] "m"(b20380b_c2073d9), [c206df8] "m"(b20380b_c206df8), [c209961] "m"(b20380b_c209961), [c209880] "m"(b20380b_c209880), [c209c05] "m"(b20380b_c209c05), [c209d16] "m"(b20380b_c209d16), [c208da2] "m"(b20380b_c208da2), [c20a0ef] "m"(b20380b_c20a0ef), [c20a11d] "m"(b20380b_c20a11d), [c20a145] "m"(b20380b_c20a145), [c20a16d] "m"(b20380b_c20a16d), [c20a18e] "m"(b20380b_c20a18e), [c20a1af] "m"(b20380b_c20a1af), [c20a1d0] "m"(b20380b_c20a1d0), [c20a1f1] "m"(b20380b_c20a1f1), [c20a219] "m"(b20380b_c20a219), [c20a241] "m"(b20380b_c20a241), [c20baa4] "m"(b20380b_c20baa4), [c20badd] "m"(b20380b_c20badd), [c20b873] "m"(b20380b_c20b873), [c20b0ac] "m"(b20380b_c20b0ac), [c204388] "m"(b20380b_c204388), [c20b856] "m"(b20380b_c20b856), [c20b0f7] "m"(b20380b_c20b0f7), [c2044b5] "m"(b20380b_c2044b5), [c20b8d7] "m"(b20380b_c20b8d7), [c203704] "m"(b20380b_c203704), [c203815] "m"(b20380b_c203815), [c20c752] "m"(b20380b_c20c752), [c20c3fe] "m"(b20380b_c20c3fe), [c20bc71] "m"(b20380b_c20bc71), [c20c636] "m"(b20380b_c20c636), [c20c050] "m"(b20380b_c20c050), [c204163] "m"(b20380b_c204163), [c2041f0] "m"(b20380b_c2041f0), [c20422f] "m"(b20380b_c20422f), [c2042a9] "m"(b20380b_c2042a9), [c2042fb] "m"(b20380b_c2042fb), [c203f32] "m"(b20380b_c203f32), [c203f69] "m"(b20380b_c203f69), [c203fa3] "m"(b20380b_c203fa3), [c203fd4] "m"(b20380b_c203fd4), [c204005] "m"(b20380b_c204005), [c204036] "m"(b20380b_c204036), [c204075] "m"(b20380b_c204075), [c2040e9] "m"(b20380b_c2040e9), [c204124] "m"(b20380b_c204124), [c2041b5] "m"(b20380b_c2041b5), [c20426e] "m"(b20380b_c20426e), [c20434d] "m"(b20380b_c20434d), [c20384b] "m"(b20380b_c20384b), [c2039b7] "m"(b20380b_c2039b7), [c203a07] "m"(b20380b_c203a07), [c203a21] "m"(b20380b_c203a21), [c203ab0] "m"(b20380b_c203ab0), [c203a65] "m"(b20380b_c203a65), [c203af2] "m"(b20380b_c203af2), [c203e0a] "m"(b20380b_c203e0a), [c203b25] "m"(b20380b_c203b25), [c203b5a] "m"(b20380b_c203b5a), [c203b95] "m"(b20380b_c203b95), [c203bd4] "m"(b20380b_c203bd4), [c203c52] "m"(b20380b_c203c52), [c203cba] "m"(b20380b_c203cba), [c203c13] "m"(b20380b_c203c13), [c203d0c] "m"(b20380b_c203d0c), [c203da9] "m"(b20380b_c203da9), [c203dd4] "m"(b20380b_c203dd4), [c203d5e] "m"(b20380b_c203d5e), [c203881] "m"(b20380b_c203881), [c2049aa] "m"(b20380b_c2049aa), [c2049d8] "m"(b20380b_c2049d8), [c2049f0] "m"(b20380b_c2049f0), [c204a0d] "m"(b20380b_c204a0d), [c204a36] "m"(b20380b_c204a36), [c2043a4] "m"(b20380b_c2043a4), [c2043e1] "m"(b20380b_c2043e1), [c204468] "m"(b20380b_c204468), [c204437] "m"(b20380b_c204437), [c204590] "m"(b20380b_c204590), [c2044ea] "m"(b20380b_c2044ea), [c204b28] "m"(b20380b_c204b28), [c204b6d] "m"(b20380b_c204b6d), [c204b89] "m"(b20380b_c204b89), [c204bbd] "m"(b20380b_c204bbd), [c204bea] "m"(b20380b_c204bea), [c203de3] "m"(b20380b_c203de3), [c203664] "m"(b20380b_c203664), [c1d4507] "m"(b20380b_c1d4507), [c2047f5] "m"(b20380b_c2047f5), [c20480b] "m"(b20380b_c20480b), [c20484d] "m"(b20380b_c20484d), [c20cb4b] "m"(b20380b_c20cb4b), [c203f07] "m"(b20380b_c203f07), [c20c857] "m"(b20380b_c20c857), [c204821] "m"(b20380b_c204821), [c204862] "m"(b20380b_c204862), [c20478b] "m"(b20380b_c20478b), [c2047df] "m"(b20380b_c2047df), [c204877] "m"(b20380b_c204877), [c20488d] "m"(b20380b_c20488d), [c2048a3] "m"(b20380b_c2048a3), [c2048b8] "m"(b20380b_c2048b8), [c2090ca] "m"(b20380b_c2090ca), [c20552e] "m"(b20380b_c20552e), [c208f52] "m"(b20380b_c208f52), [c2097a9] "m"(b20380b_c2097a9), [c203609] "m"(b20380b_c203609), [c2048cd] "m"(b20380b_c2048cd), [c2048e3] "m"(b20380b_c2048e3), [c20b46d] "m"(b20380b_c20b46d), [c2056a8] "m"(b20380b_c2056a8), [c20ba90] "m"(b20380b_c20ba90), [c204637] "m"(b20380b_c204637), [c2055e4] "m"(b20380b_c2055e4), [c2045c1] "m"(b20380b_c2045c1), [c204605] "m"(b20380b_c204605), [c2054a8] "m"(b20380b_c2054a8), [c2048f9] "m"(b20380b_c2048f9), [c20490f] "m"(b20380b_c20490f), [c203936] "m"(b20380b_c203936), [c20395b] "m"(b20380b_c20395b), [c204925] "m"(b20380b_c204925), [c203861] "m"(b20380b_c203861), [c203897] "m"(b20380b_c203897), [c2058c2] "m"(b20380b_c2058c2), [c2055a1] "m"(b20380b_c2055a1), [c205650] "m"(b20380b_c205650), [c205894] "m"(b20380b_c205894), [c2057dd] "m"(b20380b_c2057dd), [c20580f] "m"(b20380b_c20580f), [c205768] "m"(b20380b_c205768), [c20583f] "m"(b20380b_c20583f), [c20547e] "m"(b20380b_c20547e), [c205a7e] "m"(b20380b_c205a7e), [c2047ca] "m"(b20380b_c2047ca), [c205a59] "m"(b20380b_c205a59), [c205547] "m"(b20380b_c205547), [c205c86] "m"(b20380b_c205c86), [c20571a] "m"(b20380b_c20571a), [c205cff] "m"(b20380b_c205cff), [c2070d6] "m"(b20380b_c2070d6), [c205580] "m"(b20380b_c205580), [c2059b0] "m"(b20380b_c2059b0), [c205979] "m"(b20380b_c205979), [c207141] "m"(b20380b_c207141), [c205d52] "m"(b20380b_c205d52), [c205d8e] "m"(b20380b_c205d8e), [c205e69] "m"(b20380b_c205e69), [c205eb6] "m"(b20380b_c205eb6), [c204837] "m"(b20380b_c204837), [c205c4d] "m"(b20380b_c205c4d), [c205ce5] "m"(b20380b_c205ce5), [c205f6d] "m"(b20380b_c205f6d), [c205fed] "m"(b20380b_c205fed), [c2053f9] "m"(b20380b_c2053f9), [c206eb2] "m"(b20380b_c206eb2), [c20763c] "m"(b20380b_c20763c), [c205b7f] "m"(b20380b_c205b7f), [c205b43] "m"(b20380b_c205b43), [c20545c] "m"(b20380b_c20545c), [c20611c] "m"(b20380b_c20611c), [c206232] "m"(b20380b_c206232), [c2060d4] "m"(b20380b_c2060d4), [c205a68] "m"(b20380b_c205a68), [c2060f8] "m"(b20380b_c2060f8), [c20639e] "m"(b20380b_c20639e), [c2063cb] "m"(b20380b_c2063cb), [c20d4a4] "m"(b20380b_c20d4a4), [c20d152] "m"(b20380b_c20d152), [c20672a] "m"(b20380b_c20672a), [c20d780] "m"(b20380b_c20d780), [c20d118] "m"(b20380b_c20d118), [c20ab80] "m"(b20380b_c20ab80), [c2063b8] "m"(b20380b_c2063b8), [c209e6d] "m"(b20380b_c209e6d), [c206d25] "m"(b20380b_c206d25), [c206476] "m"(b20380b_c206476), [c20391d] "m"(b20380b_c20391d), [c20cc90] "m"(b20380b_c20cc90), [c20d988] "m"(b20380b_c20d988), [c20d92d] "m"(b20380b_c20d92d), [c20d731] "m"(b20380b_c20d731), [c20af71] "m"(b20380b_c20af71), [c20ba21] "m"(b20380b_c20ba21), [c20bbe4] "m"(b20380b_c20bbe4), [c20c0d2] "m"(b20380b_c20c0d2), [c206844] "m"(b20380b_c206844), [c20678c] "m"(b20380b_c20678c), [c206870] "m"(b20380b_c206870), [c206d0a] "m"(b20380b_c206d0a), [c206ca8] "m"(b20380b_c206ca8), [c207392] "m"(b20380b_c207392)
      : "memory");
}
#else
#error "CMcpxAPU_ServiceDeferredCommandsLow: clang naked draft required"
#endif


/* 0x00203810 */
void CMcpxVoiceClient_SetVolume(void)
{
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: FUN_002063cb(0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x20994d */
  /* relift: FUN_00208000(0); */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x2098c6 */
  /* mem[0xfe8202f8] = edi */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x2098d6 */

  (void)ecx;
  (void)esi;
  (void)edi;
}

/* IDirectSound_AddRef (0x20384b) — XBE naked draft (batch 349). */
#if defined(__clang__)


__attribute__((naked, noinline))
void IDirectSound_AddRef(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "IDirectSound_AddRef: clang naked draft required"
#endif


/* IDirectSound_Release (0x203861) — XBE naked draft (batch 349). */
#if defined(__clang__)


__attribute__((naked, noinline))
void IDirectSound_Release(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%ecx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "IDirectSound_Release: clang naked draft required"
#endif


/* 0x00203877 */
void IDirectSoundBuffer_Unlock(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* IDirectSoundBuffer_AddRef (0x203881) — XBE naked draft (batch 350). */
#if defined(__clang__)


__attribute__((naked, noinline))
void IDirectSoundBuffer_AddRef(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x1c(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "IDirectSoundBuffer_AddRef: clang naked draft required"
#endif


/* IDirectSoundBuffer_Release (0x203897) — XBE naked draft (batch 350). */
#if defined(__clang__)


__attribute__((naked, noinline))
void IDirectSoundBuffer_Release(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "leal -0x1c(%%eax), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%ecx)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "IDirectSoundBuffer_Release: clang naked draft required"
#endif


/* 0x002038d9 */
void DirectSoundGetSampleTime(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* DirectSoundUseFullHRTF (0x2038df) — XBE naked draft (batch 362). */
#if defined(__clang__)
static void (*const b2038df_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;

__attribute__((naked, noinline))
void DirectSoundUseFullHRTF(void)
{
  __asm__ volatile(
      "call *%[c20368b]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x20a2f5, 0x222d64\n\t"
      "je .LDirectSoundUseFullHRTF_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LDirectSoundUseFullHRTF_1:\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2038df_c20368b)
      : "memory");
}
#else
#error "DirectSoundUseFullHRTF: clang naked draft required"
#endif


/* DirectSoundUseLightHRTF (0x2038fe) — XBE naked draft (batch 362). */
#if defined(__clang__)
static void (*const b2038fe_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;

__attribute__((naked, noinline))
void DirectSoundUseLightHRTF(void)
{
  __asm__ volatile(
      "call *%[c20368b]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x20a431, 0x222d64\n\t"
      "je .LDirectSoundUseLightHRTF_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LDirectSoundUseLightHRTF_1:\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2038fe_c20368b)
      : "memory");
}
#else
#error "DirectSoundUseLightHRTF: clang naked draft required"
#endif


/* DSound_CRefCount_AddRef (0x203936) — XBE naked draft (batch 377). */
#if defined(__clang__)
static void (*const b203936_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;

__attribute__((naked, noinline))
void DSound_CRefCount_AddRef(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "incl 0x4(%%ecx)\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "je .LDSound_CRefCount_AddRef_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LDSound_CRefCount_AddRef_1:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203936_c20368b)
      : "memory");
}
#else
#error "DSound_CRefCount_AddRef: clang naked draft required"
#endif


/* DSound_CRefCount_Release (0x20395b) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void (*const b20395b_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;

__attribute__((naked, noinline))
void DSound_CRefCount_Release(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "decl 0x4(%%ecx)\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LDSound_CRefCount_Release_1\n\t"
      "movl (%%ecx), %%eax\n\t"
      "pushl $1\n\t"
      "call *(%%eax)\n\t"
      ".LDSound_CRefCount_Release_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LDSound_CRefCount_Release_2\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LDSound_CRefCount_Release_2:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20395b_c20368b)
      : "memory");
}
#else
#error "DSound_CRefCount_Release: clang naked draft required"
#endif


/* CDirectSound_GetCaps (0x2039b7) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void (*const b2039b7_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b2039b7_c20376b_tgt(void) { return; }
static void (*const b2039b7_c20376b)(void) = b2039b7_c20376b_tgt;

__attribute__((naked, noinline))
void CDirectSound_GetCaps(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c20376b]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCDirectSound_GetCaps_1\n\t"
      "movl 0x222ce8, %%eax\n\t"
      "movl 0x222ce4, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      ".LCDirectSound_GetCaps_1:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDirectSound_GetCaps_2\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_GetCaps_2:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2039b7_c20368b), [c20376b] "m"(b2039b7_c20376b)
      : "memory");
}
#else
#error "CDirectSound_GetCaps: clang naked draft required"
#endif


/* CDirectSound_GetSpeakerConfig (0x203a07) — XBE naked draft (batch 355). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CDirectSound_GetSpeakerConfig(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CDirectSound_GetSpeakerConfig: clang naked draft required"
#endif


/* CDirectSound_DownloadEffectsImage (0x203a21) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void (*const b203a21_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b203a21_c203995_tgt(void) { return; }
static void (*const b203a21_c203995)(void) = b203a21_c203995_tgt;
static void b203a21_c2037ad_tgt(void) { return; }
static void (*const b203a21_c2037ad)(void) = b203a21_c2037ad_tgt;

__attribute__((naked, noinline))
void CDirectSound_DownloadEffectsImage(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c203995]\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *%[c2037ad]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCDirectSound_DownloadEffectsImage_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_DownloadEffectsImage_1:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203a21_c20368b), [c203995] "m"(b203a21_c203995), [c2037ad] "m"(b203a21_c2037ad)
      : "memory");
}
#else
#error "CDirectSound_DownloadEffectsImage: clang naked draft required"
#endif


/* CDirectSound_SetEffectData (0x203a65) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void (*const b203a65_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b203a65_c207aca_tgt(void) { return; }
static void (*const b203a65_c207aca)(void) = b203a65_c207aca_tgt;

__attribute__((naked, noinline))
void CDirectSound_SetEffectData(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207aca]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetEffectData_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetEffectData_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203a65_c20368b), [c207aca] "m"(b203a65_c207aca)
      : "memory");
}
#else
#error "CDirectSound_SetEffectData: clang naked draft required"
#endif


/* CDirectSound_GetEffectData (0x203ab0) — XBE naked draft (batch 346). */
#if defined(__clang__)
static void (*const b203ab0_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b203ab0_c207b73_tgt(void) { return; }
static void (*const b203ab0_c207b73)(void) = b203ab0_c207b73_tgt;

__attribute__((naked, noinline))
void CDirectSound_GetEffectData(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207b73]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_GetEffectData_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_GetEffectData_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203ab0_c20368b), [c207b73] "m"(b203ab0_c207b73)
      : "memory");
}
#else
#error "CDirectSound_GetEffectData: clang naked draft required"
#endif


/* CDirectSound_CommitEffectData (0x203af2) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b203af2_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void b203af2_c207876_tgt(void) { return; }
static void (*const b203af2_c207876)(void) = b203af2_c207876_tgt;

__attribute__((naked, noinline))
void CDirectSound_CommitEffectData(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c207876]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCDirectSound_CommitEffectData_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_CommitEffectData_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203af2_c20368b), [c207876] "m"(b203af2_c207876)
      : "memory");
}
#else
#error "CDirectSound_CommitEffectData: clang naked draft required"
#endif


/* CDirectSound_SetMixBinHeadroom (0x203b25) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b203b25_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b203b25_c206dc4)(void) = (void *)CMcpxAPU_SetMixBinHeadroom;

__attribute__((naked, noinline))
void CDirectSound_SetMixBinHeadroom(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c206dc4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetMixBinHeadroom_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetMixBinHeadroom_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203b25_c20368b), [c206dc4] "m"(b203b25_c206dc4)
      : "memory");
}
#else
#error "CDirectSound_SetMixBinHeadroom: clang naked draft required"
#endif


/* CDirectSound_SetAllParameters (0x203b5a) — XBE naked draft (batch 352). */
#if defined(__clang__)
static void (*const b203b5a_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203b5a_c207234)(void) = CMcpxAPU_Set3dParameters;

__attribute__((naked, noinline))
void CDirectSound_SetAllParameters(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207234]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetAllParameters_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetAllParameters_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203b5a_c20368b), [c207234] "m"(b203b5a_c207234)
      : "memory");
}
#else
#error "CDirectSound_SetAllParameters: clang naked draft required"
#endif


/* CDirectSound_SetDistanceFactor (0x203b95) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b203b95_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203b95_c207265)(void) = CMcpxAPU_Set3dDistanceFactor;

__attribute__((naked, noinline))
void CDirectSound_SetDistanceFactor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207265]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetDistanceFactor_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetDistanceFactor_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203b95_c20368b), [c207265] "m"(b203b95_c207265)
      : "memory");
}
#else
#error "CDirectSound_SetDistanceFactor: clang naked draft required"
#endif


/* CDirectSound_SetDopplerFactor (0x203bd4) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b203bd4_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203bd4_c207289)(void) = CMcpxAPU_Set3dDopplerFactor;

__attribute__((naked, noinline))
void CDirectSound_SetDopplerFactor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207289]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetDopplerFactor_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetDopplerFactor_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203bd4_c20368b), [c207289] "m"(b203bd4_c207289)
      : "memory");
}
#else
#error "CDirectSound_SetDopplerFactor: clang naked draft required"
#endif


/* CDirectSound_SetRolloffFactor (0x203c13) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b203c13_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203c13_c2072ad)(void) = CMcpxAPU_Set3dRolloffFactor;

__attribute__((naked, noinline))
void CDirectSound_SetRolloffFactor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c2072ad]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetRolloffFactor_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetRolloffFactor_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203c13_c20368b), [c2072ad] "m"(b203c13_c2072ad)
      : "memory");
}
#else
#error "CDirectSound_SetRolloffFactor: clang naked draft required"
#endif


/* CDirectSound_SetOrientation (0x203c52) — XBE naked draft (batch 327). */
#if defined(__clang__)
static void (*const b203c52_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b203c52_c2072d1_tgt(void) { return; }
static void (*const b203c52_c2072d1)(void) = b203c52_c2072d1_tgt;

__attribute__((naked, noinline))
void CDirectSound_SetOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c2072d1]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetOrientation_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetOrientation_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203c52_c20368b), [c2072d1] "m"(b203c52_c2072d1)
      : "memory");
}
#else
#error "CDirectSound_SetOrientation: clang naked draft required"
#endif


/* CDirectSound_SetPosition (0x203cba) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void (*const b203cba_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203cba_c207309)(void) = CMcpxAPU_Set3dPosition;

__attribute__((naked, noinline))
void CDirectSound_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207309]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetPosition_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetPosition_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203cba_c20368b), [c207309] "m"(b203cba_c207309)
      : "memory");
}
#else
#error "CDirectSound_SetPosition: clang naked draft required"
#endif


/* CDirectSound_SetVelocity (0x203d0c) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void (*const b203d0c_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203d0c_c207334)(void) = CMcpxAPU_Set3dVelocity;

__attribute__((naked, noinline))
void CDirectSound_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c207334]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSound_SetVelocity_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetVelocity_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203d0c_c20368b), [c207334] "m"(b203d0c_c207334)
      : "memory");
}
#else
#error "CDirectSound_SetVelocity: clang naked draft required"
#endif


/* CDirectSound_SetI3DL2Listener (0x203d5e) — XBE naked draft (batch 351). */
#if defined(__clang__)
static void (*const b203d5e_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b203d5e_c20735f)(void) = CMcpxAPU_SetI3DL2Listener;

__attribute__((naked, noinline))
void CDirectSound_SetI3DL2Listener(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "cmpl $-1, 0xc(%%ecx)\n\t"
      "jne .LCDirectSound_SetI3DL2Listener_1\n\t"
      "movl $0x88780032, %%esi\n\t"
      "jmp .LCDirectSound_SetI3DL2Listener_2\n\t"
      ".LCDirectSound_SetI3DL2Listener_1:\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c20735f]\n\t"
      "movl %%eax, %%esi\n\t"
      ".LCDirectSound_SetI3DL2Listener_2:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCDirectSound_SetI3DL2Listener_3\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_SetI3DL2Listener_3:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203d5e_c20368b), [c20735f] "m"(b203d5e_c20735f)
      : "memory");
}
#else
#error "CDirectSound_SetI3DL2Listener: clang naked draft required"
#endif


/* CDirectSound_CommitDeferredSettings (0x203da9) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b203da9_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b203da9_c206a5e)(void) = (void *)CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CDirectSound_CommitDeferredSettings(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCDirectSound_CommitDeferredSettings_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_CommitDeferredSettings_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203da9_c20368b), [c206a5e] "m"(b203da9_c206a5e)
      : "memory");
}
#else
#error "CDirectSound_CommitDeferredSettings: clang naked draft required"
#endif


/* CDirectSound_GetTime (0x203dd4) — XBE naked draft (batch 394). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CDirectSound_GetTime(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "call *0x25313c\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CDirectSound_GetTime: clang naked draft required"
#endif


/* CDirectSound_DoWork (0x203de3) — XBE naked draft (batch 377). */
#if defined(__clang__)
static void (*const b203de3_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void b203de3_c2073d9_tgt(void) { return; }
static void (*const b203de3_c2073d9)(void) = b203de3_c2073d9_tgt;

__attribute__((naked, noinline))
void CDirectSound_DoWork(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "call *%[c2073d9]\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LCDirectSound_DoWork_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_DoWork_1:\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203de3_c20368b), [c2073d9] "m"(b203de3_c2073d9)
      : "memory");
}
#else
#error "CDirectSound_DoWork: clang naked draft required"
#endif


/* CDirectSound_EnableHeadphones (0x203e0a) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b203e0a_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b203e0a_c206df8_tgt(void) { return; }
static void (*const b203e0a_c206df8)(void) = b203e0a_c206df8_tgt;
static void b203e0a_c207b73_tgt(void) { return; }
static void (*const b203e0a_c207b73)(void) = b203e0a_c207b73_tgt;
static void b203e0a_c207aca_tgt(void) { return; }
static void (*const b203e0a_c207aca)(void) = b203e0a_c207aca_tgt;

__attribute__((naked, noinline))
void CDirectSound_EnableHeadphones(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "cmpl %%edx, 0xc(%%ebp)\n\t"
      "setne %%dl\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LCDirectSound_EnableHeadphones_6\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LCDirectSound_EnableHeadphones_1\n\t"
      "orl $0x80000000, %%ebx\n\t"
      "jmp .LCDirectSound_EnableHeadphones_2\n\t"
      ".LCDirectSound_EnableHeadphones_1:\n\t"
      "andl $0x7fffffff, %%ebx\n\t"
      ".LCDirectSound_EnableHeadphones_2:\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c206df8]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCDirectSound_EnableHeadphones_5\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%ebx, 0x8(%%eax)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LCDirectSound_EnableHeadphones_5\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl $0x34\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207b73]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCDirectSound_EnableHeadphones_5\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "je .LCDirectSound_EnableHeadphones_3\n\t"
      "andl $0xfffffffd, -0x28(%%ebp)\n\t"
      "jmp .LCDirectSound_EnableHeadphones_4\n\t"
      ".LCDirectSound_EnableHeadphones_3:\n\t"
      "orl $2, -0x28(%%ebp)\n\t"
      ".LCDirectSound_EnableHeadphones_4:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "pushl $1\n\t"
      "pushl $0x34\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xd0(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c207aca]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCDirectSound_EnableHeadphones_5:\n\t"
      "popl %%ebx\n\t"
      ".LCDirectSound_EnableHeadphones_6:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCDirectSound_EnableHeadphones_7\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_EnableHeadphones_7:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203e0a_c20368b), [c206df8] "m"(b203e0a_c206df8), [c207b73] "m"(b203e0a_c207b73), [c207aca] "m"(b203e0a_c207aca)
      : "memory");
}
#else
#error "CDirectSound_EnableHeadphones: clang naked draft required"
#endif


/* CDirectSoundVoice_SetPitch (0x203f32) — XBE naked draft (batch 358). */
#if defined(__clang__)
static void (*const b203f32_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b203f32_c209961)(void) = (void *)CMcpxVoiceClient_SetPitch;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetPitch(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "movl %%edx, 0x14(%%ecx)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c209961]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetPitch_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetPitch_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203f32_c20368b), [c209961] "m"(b203f32_c209961)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetPitch: clang naked draft required"
#endif


/* CDirectSoundVoice_SetVolume (0x203f69) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void (*const b203f69_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void b203f69_c209880_tgt(void) { return; }
static void (*const b203f69_c209880)(void) = b203f69_c209880_tgt;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetVolume(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%ecx), %%eax\n\t"
      "subl 0x1c(%%eax), %%edx\n\t"
      "movl %%edx, 0x18(%%eax)\n\t"
      "movl 0x14(%%ecx), %%ecx\n\t"
      "call *%[c209880]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetVolume_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetVolume_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203f69_c20368b), [c209880] "m"(b203f69_c209880)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetVolume: clang naked draft required"
#endif


/* CDirectSoundVoice_SetLFO (0x203fa3) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void (*const b203fa3_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b203fa3_c209c05)(void) = (void *)CMcpxVoiceClient_SetLFO;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetLFO(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c209c05]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetLFO_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetLFO_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203fa3_c20368b), [c209c05] "m"(b203fa3_c209c05)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetLFO: clang naked draft required"
#endif


/* CDirectSoundVoice_SetEG (0x203fd4) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void (*const b203fd4_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b203fd4_c209d16)(void) = (void *)CMcpxVoiceClient_SetEG;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetEG(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c209d16]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetEG_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetEG_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b203fd4_c20368b), [c209d16] "m"(b203fd4_c209d16)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetEG: clang naked draft required"
#endif


/* CDirectSoundVoice_SetFilter (0x204005) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void (*const b204005_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b204005_c208da2)(void) = (void *)CMcpxVoiceClient_SetFilter;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetFilter(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c208da2]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetFilter_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetFilter_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204005_c20368b), [c208da2] "m"(b204005_c208da2)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetFilter: clang naked draft required"
#endif


/* CDirectSoundVoice_SetHeadroom (0x204036) — XBE naked draft (batch 349). */
#if defined(__clang__)
static void (*const b204036_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b204036_c209880_tgt(void) { return; }
static void (*const b204036_c209880)(void) = b204036_c209880_tgt;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetHeadroom(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "addl %%ecx, 0x18(%%eax)\n\t"
      "movl %%esi, 0x1c(%%eax)\n\t"
      "movl 0x14(%%edx), %%ecx\n\t"
      "call *%[c209880]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCDirectSoundVoice_SetHeadroom_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetHeadroom_1:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204036_c20368b), [c209880] "m"(b204036_c209880)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetHeadroom: clang naked draft required"
#endif


/* CDirectSoundVoice_SetMixBinVolumes (0x204075) — XBE naked draft (batch 321). */
#if defined(__clang__)
static void (*const b204075_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b204075_c209880_tgt(void) { return; }
static void (*const b204075_c209880)(void) = b204075_c209880_tgt;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetMixBinVolumes(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl $0x24\n\t"
      "popl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      ".LCDirectSoundVoice_SetMixBinVolumes_1:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "testl %%ebx, 0xc(%%ebp)\n\t"
      "je .LCDirectSoundVoice_SetMixBinVolumes_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0x10(%%ebp)\n\t"
      "je .LCDirectSoundVoice_SetMixBinVolumes_2\n\t"
      "movl (%%edi), %%eax\n\t"
      ".LCDirectSoundVoice_SetMixBinVolumes_2:\n\t"
      "movl 0x18(%%edx), %%ecx\n\t"
      "movl %%eax, (%%esi,%%ecx,1)\n\t"
      "addl $4, %%edi\n\t"
      ".LCDirectSoundVoice_SetMixBinVolumes_3:\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "testl %%ebx, 0x20(%%eax)\n\t"
      "je .LCDirectSoundVoice_SetMixBinVolumes_4\n\t"
      "addl $4, %%esi\n\t"
      ".LCDirectSoundVoice_SetMixBinVolumes_4:\n\t"
      "incl -0x4(%%ebp)\n\t"
      "cmpl $0x20, -0x4(%%ebp)\n\t"
      "jb .LCDirectSoundVoice_SetMixBinVolumes_1\n\t"
      "movl 0x14(%%edx), %%ecx\n\t"
      "call *%[c209880]\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCDirectSoundVoice_SetMixBinVolumes_5\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetMixBinVolumes_5:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204075_c20368b), [c209880] "m"(b204075_c209880)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetMixBinVolumes: clang naked draft required"
#endif


/* CDirectSoundVoice_SetAllParameters (0x2040e9) — XBE naked draft (batch 352). */
#if defined(__clang__)
static void (*const b2040e9_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2040e9_c20a0ef)(void) = CMcpxVoiceClient_Set3dParameters;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetAllParameters(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a0ef]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetAllParameters_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetAllParameters_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2040e9_c20368b), [c20a0ef] "m"(b2040e9_c20a0ef)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetAllParameters: clang naked draft required"
#endif


/* CDirectSoundVoice_SetConeAngles (0x204124) — XBE naked draft (batch 349). */
#if defined(__clang__)
static void (*const b204124_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b204124_c20a11d_tgt(void) { return; }
static void (*const b204124_c20a11d)(void) = b204124_c20a11d_tgt;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetConeAngles(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a11d]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetConeAngles_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetConeAngles_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204124_c20368b), [c20a11d] "m"(b204124_c20a11d)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetConeAngles: clang naked draft required"
#endif


/* CDirectSoundVoice_SetConeOrientation (0x204163) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void (*const b204163_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b204163_c20a145)(void) = CMcpxVoiceClient_Set3dConeOrientation;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetConeOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a145]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetConeOrientation_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetConeOrientation_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204163_c20368b), [c20a145] "m"(b204163_c20a145)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetConeOrientation: clang naked draft required"
#endif


/* CDirectSoundVoice_SetConeOutsideVolume (0x2041b5) — XBE naked draft (batch 352). */
#if defined(__clang__)
static void (*const b2041b5_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2041b5_c20a16d)(void) = CMcpxVoiceClient_Set3dConeOutsideVolume;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetConeOutsideVolume(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a16d]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetConeOutsideVolume_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetConeOutsideVolume_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2041b5_c20368b), [c20a16d] "m"(b2041b5_c20a16d)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetConeOutsideVolume: clang naked draft required"
#endif


/* CDirectSoundVoice_SetMaxDistance (0x2041f0) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b2041f0_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2041f0_c20a18e)(void) = CMcpxVoiceClient_Set3dMaxDistance;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetMaxDistance(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c20a18e]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetMaxDistance_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetMaxDistance_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2041f0_c20368b), [c20a18e] "m"(b2041f0_c20a18e)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetMaxDistance: clang naked draft required"
#endif


/* CDirectSoundVoice_SetMinDistance (0x20422f) — XBE naked draft (batch 347). */
#if defined(__clang__)
static void (*const b20422f_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b20422f_c20a1af)(void) = CMcpxVoiceClient_Set3dMinDistance;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetMinDistance(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "flds 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c20a1af]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetMinDistance_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetMinDistance_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20422f_c20368b), [c20a1af] "m"(b20422f_c20a1af)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetMinDistance: clang naked draft required"
#endif


/* CDirectSoundVoice_SetMode (0x20426e) — XBE naked draft (batch 352). */
#if defined(__clang__)
static void (*const b20426e_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b20426e_c20a1d0)(void) = CMcpxVoiceClient_Set3dMode;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetMode(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a1d0]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetMode_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetMode_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20426e_c20368b), [c20a1d0] "m"(b20426e_c20a1d0)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetMode: clang naked draft required"
#endif


/* CDirectSoundVoice_SetPosition (0x2042a9) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void (*const b2042a9_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2042a9_c20a1f1)(void) = CMcpxVoiceClient_Set3dPosition;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a1f1]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetPosition_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetPosition_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2042a9_c20368b), [c20a1f1] "m"(b2042a9_c20a1f1)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetPosition: clang naked draft required"
#endif


/* CDirectSoundVoice_SetVelocity (0x2042fb) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void (*const b2042fb_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2042fb_c20a219)(void) = CMcpxVoiceClient_Set3dVelocity;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a219]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetVelocity_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetVelocity_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2042fb_c20368b), [c20a219] "m"(b2042fb_c20a219)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetVelocity: clang naked draft required"
#endif


/* CDirectSoundVoice_SetI3DL2Source (0x20434d) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b20434d_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b20434d_c20a241)(void) = CMcpxVoiceClient_SetI3DL2Source;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetI3DL2Source(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "notl %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "call *%[c20a241]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundVoice_SetI3DL2Source_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetI3DL2Source_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20434d_c20368b), [c20a241] "m"(b20434d_c20a241)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetI3DL2Source: clang naked draft required"
#endif


/* CDirectSoundBuffer_PlayEx (0x2043a4) — XBE naked draft (batch 353). */
#if defined(__clang__)
static void (*const b2043a4_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b2043a4_c20baa4)(void) = (void *)CMcpxBuffer_Play;

__attribute__((naked, noinline))
void CDirectSoundBuffer_PlayEx(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20baa4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundBuffer_PlayEx_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_PlayEx_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2043a4_c20368b), [c20baa4] "m"(b2043a4_c20baa4)
      : "memory");
}
#else
#error "CDirectSoundBuffer_PlayEx: clang naked draft required"
#endif


/* CDirectSoundBuffer_StopEx (0x2043e1) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b2043e1_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b2043e1_c20badd_tgt(void) { return; }
static void (*const b2043e1_c20badd)(void) = b2043e1_c20badd_tgt;
static void (*const b2043e1_c20b873)(void) = CMcpxBuffer_Stop;

__attribute__((naked, noinline))
void CDirectSoundBuffer_StopEx(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testb $3, %%al\n\t"
      "je .LCDirectSoundBuffer_StopEx_1\n\t"
      "shrl $1, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20badd]\n\t"
      "jmp .LCDirectSoundBuffer_StopEx_2\n\t"
      ".LCDirectSoundBuffer_StopEx_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b873]\n\t"
      ".LCDirectSoundBuffer_StopEx_2:\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCDirectSoundBuffer_StopEx_3\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_StopEx_3:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2043e1_c20368b), [c20badd] "m"(b2043e1_c20badd), [c20b873] "m"(b2043e1_c20b873)
      : "memory");
}
#else
#error "CDirectSoundBuffer_StopEx: clang naked draft required"
#endif


/* CDirectSoundBuffer_GetStatus (0x204437) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void (*const b204437_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b204437_c20b0ac)(void) = (void *)CMcpxBuffer_GetStatus;

__attribute__((naked, noinline))
void CDirectSoundBuffer_GetStatus(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b0ac]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundBuffer_GetStatus_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_GetStatus_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204437_c20368b), [c20b0ac] "m"(b204437_c20b0ac)
      : "memory");
}
#else
#error "CDirectSoundBuffer_GetStatus: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetLoopRegion (0x204468) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b204468_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b204468_c204388_tgt(void) { return; }
static void (*const b204468_c204388)(void) = b204468_c204388_tgt;
static void b204468_c20b856_tgt(void) { return; }
static void (*const b204468_c20b856)(void) = b204468_c20b856_tgt;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetLoopRegion(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "cmpl 0x50(%%ecx), %%eax\n\t"
      "jne .LCDirectSoundBuffer_SetLoopRegion_1\n\t"
      "cmpl 0x54(%%ecx), %%edx\n\t"
      "je .LCDirectSoundBuffer_SetLoopRegion_2\n\t"
      ".LCDirectSoundBuffer_SetLoopRegion_1:\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c204388]\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "call *%[c20b856]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCDirectSoundBuffer_SetLoopRegion_2:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDirectSoundBuffer_SetLoopRegion_3\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_SetLoopRegion_3:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204468_c20368b), [c204388] "m"(b204468_c204388), [c20b856] "m"(b204468_c20b856)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetLoopRegion: clang naked draft required"
#endif


/* CDirectSoundBuffer_GetCurrentPosition (0x2044b5) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b2044b5_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b2044b5_c20b0f7)(void) = (void *)CMcpxBuffer_GetCurrentPosition;

__attribute__((naked, noinline))
void CDirectSoundBuffer_GetCurrentPosition(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b0f7]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundBuffer_GetCurrentPosition_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_GetCurrentPosition_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2044b5_c20368b), [c20b0f7] "m"(b2044b5_c20b0f7)
      : "memory");
}
#else
#error "CDirectSoundBuffer_GetCurrentPosition: clang naked draft required"
#endif


/* CDirectSoundBuffer_Lock (0x2044ea) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void (*const b2044ea_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2044ea_c2044b5)(void) = CDirectSoundBuffer_GetCurrentPosition;

__attribute__((naked, noinline))
void CDirectSoundBuffer_Lock(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "testb $1, 0x24(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LCDirectSoundBuffer_Lock_1\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c2044b5]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LCDirectSoundBuffer_Lock_7\n\t"
      ".LCDirectSoundBuffer_Lock_1:\n\t"
      "testb $2, 0x24(%%ebp)\n\t"
      "je .LCDirectSoundBuffer_Lock_2\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl 0x4c(%%eax), %%eax\n\t"
      "jmp .LCDirectSoundBuffer_Lock_3\n\t"
      ".LCDirectSoundBuffer_Lock_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LCDirectSoundBuffer_Lock_3:\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl 0x48(%%ecx), %%ecx\n\t"
      "addl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl 0x4c(%%ecx), %%ecx\n\t"
      "subl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jb .LCDirectSoundBuffer_Lock_4\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".LCDirectSoundBuffer_Lock_4:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "je .LCDirectSoundBuffer_Lock_6\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCDirectSoundBuffer_Lock_6\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jae .LCDirectSoundBuffer_Lock_5\n\t"
      "movl 0x1c(%%esi), %%esi\n\t"
      "movl 0x48(%%esi), %%esi\n\t"
      "movl %%esi, (%%edx)\n\t"
      "subl (%%edi), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LCDirectSoundBuffer_Lock_6\n\t"
      ".LCDirectSoundBuffer_Lock_5:\n\t"
      "andl $0, (%%edx)\n\t"
      "andl $0, (%%ecx)\n\t"
      ".LCDirectSoundBuffer_Lock_6:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LCDirectSoundBuffer_Lock_7:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCDirectSoundBuffer_Lock_8\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_Lock_8:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2044ea_c20368b), [c2044b5] "m"(b2044ea_c2044b5)
      : "memory");
}
#else
#error "CDirectSoundBuffer_Lock: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetCurrentPosition (0x204590) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void (*const b204590_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b204590_c20b8d7)(void) = (void *)CMcpxBuffer_SetCurrentPosition;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetCurrentPosition(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "call *%[c20b8d7]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundBuffer_SetCurrentPosition_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_SetCurrentPosition_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204590_c20368b), [c20b8d7] "m"(b204590_c20b8d7)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetCurrentPosition: clang naked draft required"
#endif


/* CDirectSoundStream_GetInfo (0x20466c) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void (*const b20466c_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b20466c_c203815_tgt(void) { return; }
static void (*const b20466c_c203815)(void) = b20466c_c203815_tgt;

__attribute__((naked, noinline))
void CDirectSoundStream_GetInfo(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x14(%%esp), %%esi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "movl $0x15, (%%esi)\n\t"
      "movl 0x24(%%edi), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c203815]\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movl 0x20(%%edi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0xc(%%eax), %%eax\n\t"
      "andl $0, 0x8(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "popl %%ebx\n\t"
      "je .LCDirectSoundStream_GetInfo_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundStream_GetInfo_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20466c_c20368b), [c203815] "m"(b20466c_c203815)
      : "memory");
}
#else
#error "CDirectSoundStream_GetInfo: clang naked draft required"
#endif


/* CDirectSoundStream_Discontinuity (0x2046b7) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b2046b7_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b2046b7_c20c752)(void) = (void *)CMcpxStream_Discontinuity;

__attribute__((naked, noinline))
void CDirectSoundStream_Discontinuity(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20c752]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundStream_Discontinuity_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundStream_Discontinuity_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2046b7_c20368b), [c20c752] "m"(b2046b7_c20c752)
      : "memory");
}
#else
#error "CDirectSoundStream_Discontinuity: clang naked draft required"
#endif


/* CDirectSoundStream_Flush (0x2046e4) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b2046e4_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b2046e4_c20c3fe)(void) = (void *)CMcpxStream_Flush;

__attribute__((naked, noinline))
void CDirectSoundStream_Flush(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20c3fe]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundStream_Flush_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundStream_Flush_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2046e4_c20368b), [c20c3fe] "m"(b2046e4_c20c3fe)
      : "memory");
}
#else
#error "CDirectSoundStream_Flush: clang naked draft required"
#endif


/* CDirectSoundStream_GetStatus__r1 (0x204711) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b204711_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void b204711_c20bc71_tgt(void) { return; }
static void (*const b204711_c20bc71)(void) = b204711_c20bc71_tgt;

__attribute__((naked, noinline))
void CDirectSoundStream_GetStatus__r1(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20bc71]\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%esi\n\t"
      "je .LCDirectSoundStream_GetStatus__r1_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundStream_GetStatus__r1_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b204711_c20368b), [c20bc71] "m"(b204711_c20bc71)
      : "memory");
}
#else
#error "CDirectSoundStream_GetStatus__r1: clang naked draft required"
#endif


/* CDirectSoundStream_Process (0x204746) — XBE naked draft (batch 375). */
#if defined(__clang__)
static void b204746_c20bc71_tgt(void) { return; }
static void (*const b204746_c20bc71)(void) = b204746_c20bc71_tgt;
static void b204746_c20c636_tgt(void) { return; }
static void (*const b204746_c20c636)(void) = b204746_c20c636_tgt;

__attribute__((naked, noinline))
void CDirectSoundStream_Process(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "call *%[c20bc71]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCDirectSoundStream_Process_1\n\t"
      "movl $0x88780032, %%eax\n\t"
      "jmp .LCDirectSoundStream_Process_2\n\t"
      ".LCDirectSoundStream_Process_1:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "call *%[c20c636]\n\t"
      ".LCDirectSoundStream_Process_2:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20bc71] "m"(b204746_c20bc71), [c20c636] "m"(b204746_c20c636)
      : "memory");
}
#else
#error "CDirectSoundStream_Process: clang naked draft required"
#endif


/* CDirectSoundStream_Pause (0x20476e) — XBE naked draft (batch 385). */
#if defined(__clang__)
static void (*const b20476e_c20c050)(void) = (void *)CMcpxStream_Pause;

__attribute__((naked, noinline))
void CDirectSoundStream_Pause(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "call *%[c20c050]\n\t"
      "ret\n\t"
      :
      : [c20c050] "m"(b20476e_c20c050)
      : "memory");
}
#else
#error "CDirectSoundStream_Pause: clang naked draft required"
#endif


/* 0x0020497d */
void CDirectSoundBuffer_SetVolume(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00209880(0, 0); */
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetLFO();
}

/* 0x00204982 */
void CDirectSoundBuffer_SetPitch(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetPitch();
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00209880(0, 0); */
}

/* 0x00204987 */
void CDirectSoundBuffer_SetLFO(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetLFO();
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetEG();
}

/* 0x0020498c */
void CDirectSoundBuffer_SetEG(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetEG();
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetFilter();
}

/* 0x00204991 */
void CDirectSoundBuffer_SetFilter(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetFilter();
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00209880(0, 0); */
}

/* 0x00204996 */
void CDirectSoundBuffer_SetHeadroom(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00209880(0, 0); */
  DirectSoundEnterCriticalSection();
}

/* 0x0020499b */
void CDirectSoundBuffer_SetMixBinVolumes(void)
{
  int eax = 0;
  int ebx = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  /* relift: test dword ptr [ebp + 0xc], ebx -> je 0x2040b1 */
  /* relift: cmp dword ptr [ebp + 0x10], eax -> je 0x2040a8 */
  /* relift: test dword ptr [eax + 0x20], ebx -> je 0x2040bc */
  /* relift: cmp dword ptr [ebp - 4], 0x20 -> jb 0x204092 */
  /* relift: FUN_00209880(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ebp;
}

/* 0x002049a0 */
void CDirectSoundBuffer_SetAllParameters(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dParameters();
  DirectSoundEnterCriticalSection();
}

/* 0x002049a5 */
void CDirectSoundBuffer_SetConeAngles(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_0020a11d(0, 0, 0); */
  DirectSoundEnterCriticalSection();
}

/* CDirectSoundBuffer_SetConeOrientation (0x2049aa) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b2049aa_c204163)(void) = (void *)CDirectSoundVoice_SetConeOrientation;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetConeOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204163]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204163] "m"(b2049aa_c204163)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetConeOrientation: clang naked draft required"
#endif


/* 0x002049d3 */
void CDirectSoundBuffer_SetConeOutsideVolume(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dConeOutsideVolume();
  DirectSoundEnterCriticalSection();
}

/* CDirectSoundBuffer_SetMaxDistance (0x2049d8) — XBE naked draft (batch 362). */
#if defined(__clang__)
static void (*const b2049d8_c2041f0)(void) = (void *)CDirectSoundVoice_SetMaxDistance;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetMaxDistance(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c2041f0]\n\t"
      "ret\n\t"
      :
      : [c2041f0] "m"(b2049d8_c2041f0)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetMaxDistance: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetMinDistance (0x2049f0) — XBE naked draft (batch 362). */
#if defined(__clang__)
static void (*const b2049f0_c20422f)(void) = (void *)CDirectSoundVoice_SetMinDistance;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetMinDistance(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c20422f]\n\t"
      "ret\n\t"
      :
      : [c20422f] "m"(b2049f0_c20422f)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetMinDistance: clang naked draft required"
#endif


/* 0x00204a08 */
void CDirectSoundBuffer_SetMode(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dMode();
  DirectSoundEnterCriticalSection();
}

/* CDirectSoundBuffer_SetPosition (0x204a0d) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b204a0d_c2042a9)(void) = (void *)CDirectSoundVoice_SetPosition;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c2042a9]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2042a9] "m"(b204a0d_c2042a9)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetPosition: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetVelocity (0x204a36) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b204a36_c2042fb)(void) = (void *)CDirectSoundVoice_SetVelocity;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c2042fb]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2042fb] "m"(b204a36_c2042fb)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetVelocity: clang naked draft required"
#endif


/* 0x00204a5f */
void CDirectSoundBuffer_SetI3DL2Source(void)
{
  int eax = 0;

  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetI3DL2Source();
  /* test eax, eax -> jne 0x204397 */
  DirectSoundEnterCriticalSection();

  (void)eax;
}

/* CDirectSoundStream_SetPitch (0x204a64) — XBE naked draft (batch 381). */
#if defined(__clang__)
static void (*const b204a64_c203f32)(void) = (void *)CDirectSoundVoice_SetPitch;

__attribute__((naked, noinline))
void CDirectSoundStream_SetPitch(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f32]\n\t"
      "ret\n\t"
      :
      : [c203f32] "m"(b204a64_c203f32)
      : "memory");
}
#else
#error "CDirectSoundStream_SetPitch: clang naked draft required"
#endif


/* CDirectSoundStream_SetVolume (0x204a78) — XBE naked draft (batch 381). */
#if defined(__clang__)
static void (*const b204a78_c203f69)(void) = (void *)CDirectSoundVoice_SetVolume;

__attribute__((naked, noinline))
void CDirectSoundStream_SetVolume(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f69]\n\t"
      "ret\n\t"
      :
      : [c203f69] "m"(b204a78_c203f69)
      : "memory");
}
#else
#error "CDirectSoundStream_SetVolume: clang naked draft required"
#endif


/* CDirectSoundStream_SetLFO (0x204a8c) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b204a8c_c203fa3)(void) = (void *)CDirectSoundVoice_SetLFO;

__attribute__((naked, noinline))
void CDirectSoundStream_SetLFO(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fa3]\n\t"
      "ret\n\t"
      :
      : [c203fa3] "m"(b204a8c_c203fa3)
      : "memory");
}
#else
#error "CDirectSoundStream_SetLFO: clang naked draft required"
#endif


/* CDirectSoundStream_SetEG (0x204aa0) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b204aa0_c203fd4)(void) = (void *)CDirectSoundVoice_SetEG;

__attribute__((naked, noinline))
void CDirectSoundStream_SetEG(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fd4]\n\t"
      "ret\n\t"
      :
      : [c203fd4] "m"(b204aa0_c203fd4)
      : "memory");
}
#else
#error "CDirectSoundStream_SetEG: clang naked draft required"
#endif


/* CDirectSoundStream_SetFilter (0x204ab4) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b204ab4_c204005)(void) = (void *)CDirectSoundVoice_SetFilter;

__attribute__((naked, noinline))
void CDirectSoundStream_SetFilter(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204005]\n\t"
      "ret\n\t"
      :
      : [c204005] "m"(b204ab4_c204005)
      : "memory");
}
#else
#error "CDirectSoundStream_SetFilter: clang naked draft required"
#endif


/* CDirectSoundStream_SetHeadroom (0x204ac8) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b204ac8_c204036)(void) = (void *)CDirectSoundVoice_SetHeadroom;

__attribute__((naked, noinline))
void CDirectSoundStream_SetHeadroom(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204036]\n\t"
      "ret\n\t"
      :
      : [c204036] "m"(b204ac8_c204036)
      : "memory");
}
#else
#error "CDirectSoundStream_SetHeadroom: clang naked draft required"
#endif


/* CDirectSoundStream_SetMixBinVolumes_12 (0x204adc) — XBE naked draft (batch 379). */
#if defined(__clang__)
static void (*const b204adc_c204075)(void) = (void *)CDirectSoundVoice_SetMixBinVolumes;

__attribute__((naked, noinline))
void CDirectSoundStream_SetMixBinVolumes_12(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204075]\n\t"
      "ret\n\t"
      :
      : [c204075] "m"(b204adc_c204075)
      : "memory");
}
#else
#error "CDirectSoundStream_SetMixBinVolumes_12: clang naked draft required"
#endif


/* CDirectSoundStream_SetAllParameters (0x204af4) — XBE naked draft (batch 379). */
#if defined(__clang__)
static void (*const b204af4_c2040e9)(void) = (void *)CDirectSoundVoice_SetAllParameters;

__attribute__((naked, noinline))
void CDirectSoundStream_SetAllParameters(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2040e9]\n\t"
      "ret\n\t"
      :
      : [c2040e9] "m"(b204af4_c2040e9)
      : "memory");
}
#else
#error "CDirectSoundStream_SetAllParameters: clang naked draft required"
#endif


/* CDirectSoundStream_SetConeAngles (0x204b0c) — XBE naked draft (batch 377). */
#if defined(__clang__)
static void (*const b204b0c_c204124)(void) = (void *)CDirectSoundVoice_SetConeAngles;

__attribute__((naked, noinline))
void CDirectSoundStream_SetConeAngles(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c204124]\n\t"
      "ret\n\t"
      :
      : [c204124] "m"(b204b0c_c204124)
      : "memory");
}
#else
#error "CDirectSoundStream_SetConeAngles: clang naked draft required"
#endif


/* CDirectSoundStream_SetConeOrientation (0x204b28) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b204b28_c204163)(void) = (void *)CDirectSoundVoice_SetConeOrientation;

__attribute__((naked, noinline))
void CDirectSoundStream_SetConeOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c204163]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204163] "m"(b204b28_c204163)
      : "memory");
}
#else
#error "CDirectSoundStream_SetConeOrientation: clang naked draft required"
#endif


/* CDirectSoundStream_SetConeOutsideVolume (0x204b55) — XBE naked draft (batch 379). */
#if defined(__clang__)
static void (*const b204b55_c2041b5)(void) = (void *)CDirectSoundVoice_SetConeOutsideVolume;

__attribute__((naked, noinline))
void CDirectSoundStream_SetConeOutsideVolume(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2041b5]\n\t"
      "ret\n\t"
      :
      : [c2041b5] "m"(b204b55_c2041b5)
      : "memory");
}
#else
#error "CDirectSoundStream_SetConeOutsideVolume: clang naked draft required"
#endif


/* CDirectSoundStream_SetMaxDistance (0x204b6d) — XBE naked draft (batch 375). */
#if defined(__clang__)
static void (*const b204b6d_c2041f0)(void) = (void *)CDirectSoundVoice_SetMaxDistance;

__attribute__((naked, noinline))
void CDirectSoundStream_SetMaxDistance(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c2041f0]\n\t"
      "ret\n\t"
      :
      : [c2041f0] "m"(b204b6d_c2041f0)
      : "memory");
}
#else
#error "CDirectSoundStream_SetMaxDistance: clang naked draft required"
#endif


/* CDirectSoundStream_SetMinDistance (0x204b89) — XBE naked draft (batch 375). */
#if defined(__clang__)
static void (*const b204b89_c20422f)(void) = (void *)CDirectSoundVoice_SetMinDistance;

__attribute__((naked, noinline))
void CDirectSoundStream_SetMinDistance(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c20422f]\n\t"
      "ret\n\t"
      :
      : [c20422f] "m"(b204b89_c20422f)
      : "memory");
}
#else
#error "CDirectSoundStream_SetMinDistance: clang naked draft required"
#endif


/* CDirectSoundStream_SetMode (0x204ba5) — XBE naked draft (batch 379). */
#if defined(__clang__)
static void (*const b204ba5_c20426e)(void) = (void *)CDirectSoundVoice_SetMode;

__attribute__((naked, noinline))
void CDirectSoundStream_SetMode(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20426e]\n\t"
      "ret\n\t"
      :
      : [c20426e] "m"(b204ba5_c20426e)
      : "memory");
}
#else
#error "CDirectSoundStream_SetMode: clang naked draft required"
#endif


/* CDirectSoundStream_SetPosition (0x204bbd) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b204bbd_c2042a9)(void) = (void *)CDirectSoundVoice_SetPosition;

__attribute__((naked, noinline))
void CDirectSoundStream_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c2042a9]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2042a9] "m"(b204bbd_c2042a9)
      : "memory");
}
#else
#error "CDirectSoundStream_SetPosition: clang naked draft required"
#endif


/* CDirectSoundStream_SetVelocity (0x204bea) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b204bea_c2042fb)(void) = (void *)CDirectSoundVoice_SetVelocity;

__attribute__((naked, noinline))
void CDirectSoundStream_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c2042fb]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2042fb] "m"(b204bea_c2042fb)
      : "memory");
}
#else
#error "CDirectSoundStream_SetVelocity: clang naked draft required"
#endif


/* CDirectSoundStream_SetI3DL2Source (0x204c17) — XBE naked draft (batch 362). */
#if defined(__clang__)
static void (*const b204c17_c20434d)(void) = (void *)CDirectSoundVoice_SetI3DL2Source;

__attribute__((naked, noinline))
void CDirectSoundStream_SetI3DL2Source(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20434d]\n\t"
      "ret\n\t"
      :
      : [c20434d] "m"(b204c17_c20434d)
      : "memory");
}
#else
#error "CDirectSoundStream_SetI3DL2Source: clang naked draft required"
#endif


/* IDirectSound_GetCaps (0x204c5d) — XBE naked draft (batch 370). */
#if defined(__clang__)
static void (*const b204c5d_c2039b7)(void) = (void *)CDirectSound_GetCaps;

__attribute__((naked, noinline))
void IDirectSound_GetCaps(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2039b7]\n\t"
      "ret\n\t"
      :
      : [c2039b7] "m"(b204c5d_c2039b7)
      : "memory");
}
#else
#error "IDirectSound_GetCaps: clang naked draft required"
#endif


/* IDirectSound_GetSpeakerConfig (0x204c79) — XBE naked draft (batch 370). */
#if defined(__clang__)
static void (*const b204c79_c203a07)(void) = (void *)CDirectSound_GetSpeakerConfig;

__attribute__((naked, noinline))
void IDirectSound_GetSpeakerConfig(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203a07]\n\t"
      "ret\n\t"
      :
      : [c203a07] "m"(b204c79_c203a07)
      : "memory");
}
#else
#error "IDirectSound_GetSpeakerConfig: clang naked draft required"
#endif


/* IDirectSound_DownloadEffectsImage (0x204c95) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b204c95_c203a21)(void) = (void *)CDirectSound_DownloadEffectsImage;

__attribute__((naked, noinline))
void IDirectSound_DownloadEffectsImage(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203a21]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c203a21] "m"(b204c95_c203a21)
      : "memory");
}
#else
#error "IDirectSound_DownloadEffectsImage: clang naked draft required"
#endif


/* IDirectSound_GetEffectData (0x204cbc) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b204cbc_c203ab0)(void) = (void *)CDirectSound_GetEffectData;

__attribute__((naked, noinline))
void IDirectSound_GetEffectData(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203ab0]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c203ab0] "m"(b204cbc_c203ab0)
      : "memory");
}
#else
#error "IDirectSound_GetEffectData: clang naked draft required"
#endif


/* IDirectSound_SetEffectData (0x204ce3) — XBE naked draft (batch 364). */
#if defined(__clang__)
static void (*const b204ce3_c203a65)(void) = (void *)CDirectSound_SetEffectData;

__attribute__((naked, noinline))
void IDirectSound_SetEffectData(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203a65]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c203a65] "m"(b204ce3_c203a65)
      : "memory");
}
#else
#error "IDirectSound_SetEffectData: clang naked draft required"
#endif


/* IDirectSound_CommitEffectData (0x204d0d) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b204d0d_c203af2)(void) = CDirectSound_CommitEffectData;

__attribute__((naked, noinline))
void IDirectSound_CommitEffectData(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203af2]\n\t"
      "ret\n\t"
      :
      : [c203af2] "m"(b204d0d_c203af2)
      : "memory");
}
#else
#error "IDirectSound_CommitEffectData: clang naked draft required"
#endif


/* IDirectSound_EnableHeadphones (0x204d25) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b204d25_c203e0a)(void) = (void *)CDirectSound_EnableHeadphones;

__attribute__((naked, noinline))
void IDirectSound_EnableHeadphones(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203e0a]\n\t"
      "ret\n\t"
      :
      : [c203e0a] "m"(b204d25_c203e0a)
      : "memory");
}
#else
#error "IDirectSound_EnableHeadphones: clang naked draft required"
#endif


/* IDirectSound_SetMixBinHeadroom (0x204d41) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b204d41_c203b25)(void) = (void *)CDirectSound_SetMixBinHeadroom;

__attribute__((naked, noinline))
void IDirectSound_SetMixBinHeadroom(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203b25]\n\t"
      "ret\n\t"
      :
      : [c203b25] "m"(b204d41_c203b25)
      : "memory");
}
#else
#error "IDirectSound_SetMixBinHeadroom: clang naked draft required"
#endif


/* IDirectSound_SetAllParameters (0x204d61) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b204d61_c203b5a)(void) = (void *)CDirectSound_SetAllParameters;

__attribute__((naked, noinline))
void IDirectSound_SetAllParameters(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203b5a]\n\t"
      "ret\n\t"
      :
      : [c203b5a] "m"(b204d61_c203b5a)
      : "memory");
}
#else
#error "IDirectSound_SetAllParameters: clang naked draft required"
#endif


/* IDirectSound_SetDistanceFactor (0x204d81) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b204d81_c203b95)(void) = (void *)CDirectSound_SetDistanceFactor;

__attribute__((naked, noinline))
void IDirectSound_SetDistanceFactor(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203b95]\n\t"
      "ret\n\t"
      :
      : [c203b95] "m"(b204d81_c203b95)
      : "memory");
}
#else
#error "IDirectSound_SetDistanceFactor: clang naked draft required"
#endif


/* IDirectSound_SetDopplerFactor (0x204da5) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b204da5_c203bd4)(void) = (void *)CDirectSound_SetDopplerFactor;

__attribute__((naked, noinline))
void IDirectSound_SetDopplerFactor(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203bd4]\n\t"
      "ret\n\t"
      :
      : [c203bd4] "m"(b204da5_c203bd4)
      : "memory");
}
#else
#error "IDirectSound_SetDopplerFactor: clang naked draft required"
#endif


/* IDirectSound_SetOrientation (0x204dc9) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void (*const b204dc9_c203c52)(void) = CDirectSound_SetOrientation;

__attribute__((naked, noinline))
void IDirectSound_SetOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x24(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0x18, %%esp\n\t"
      "fstps 0x14(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "fstps 0x10(%%esp)\n\t"
      "negl %%ecx\n\t"
      "flds 0x18(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "fstps 0xc(%%esp)\n\t"
      "andl %%eax, %%ecx\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203c52]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c203c52] "m"(b204dc9_c203c52)
      : "memory");
}
#else
#error "IDirectSound_SetOrientation: clang naked draft required"
#endif


/* IDirectSound_SetPosition (0x204e13) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void (*const b204e13_c203cba)(void) = (void *)CDirectSound_SetPosition;

__attribute__((naked, noinline))
void IDirectSound_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203cba]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c203cba] "m"(b204e13_c203cba)
      : "memory");
}
#else
#error "IDirectSound_SetPosition: clang naked draft required"
#endif


/* IDirectSound_SetRolloffFactor (0x204e48) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b204e48_c203c13)(void) = (void *)CDirectSound_SetRolloffFactor;

__attribute__((naked, noinline))
void IDirectSound_SetRolloffFactor(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203c13]\n\t"
      "ret\n\t"
      :
      : [c203c13] "m"(b204e48_c203c13)
      : "memory");
}
#else
#error "IDirectSound_SetRolloffFactor: clang naked draft required"
#endif


/* IDirectSound_SetVelocity (0x204e6c) — XBE naked draft (batch 355). */
#if defined(__clang__)
static void (*const b204e6c_c203d0c)(void) = (void *)CDirectSound_SetVelocity;

__attribute__((naked, noinline))
void IDirectSound_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203d0c]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c203d0c] "m"(b204e6c_c203d0c)
      : "memory");
}
#else
#error "IDirectSound_SetVelocity: clang naked draft required"
#endif


/* IDirectSound_CommitDeferredSettings (0x204ea1) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b204ea1_c203da9)(void) = CDirectSound_CommitDeferredSettings;

__attribute__((naked, noinline))
void IDirectSound_CommitDeferredSettings(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203da9]\n\t"
      "ret\n\t"
      :
      : [c203da9] "m"(b204ea1_c203da9)
      : "memory");
}
#else
#error "IDirectSound_CommitDeferredSettings: clang naked draft required"
#endif


/* IDirectSound_GetTime (0x204eb9) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b204eb9_c203dd4)(void) = (void *)CDirectSound_GetTime;

__attribute__((naked, noinline))
void IDirectSound_GetTime(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203dd4]\n\t"
      "ret\n\t"
      :
      : [c203dd4] "m"(b204eb9_c203dd4)
      : "memory");
}
#else
#error "IDirectSound_GetTime: clang naked draft required"
#endif


/* IDirectSound_SetI3DL2Listener (0x204ed5) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void (*const b204ed5_c203d5e)(void) = (void *)CDirectSound_SetI3DL2Listener;

__attribute__((naked, noinline))
void IDirectSound_SetI3DL2Listener(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203d5e]\n\t"
      "ret\n\t"
      :
      : [c203d5e] "m"(b204ed5_c203d5e)
      : "memory");
}
#else
#error "IDirectSound_SetI3DL2Listener: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetLFO (0x204f5b) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b204f5b_c203fa3)(void) = (void *)CDirectSoundVoice_SetLFO;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetLFO(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203fa3]\n\t"
      "ret\n\t"
      :
      : [c203fa3] "m"(b204f5b_c203fa3)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetLFO: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetEG (0x204f77) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b204f77_c203fd4)(void) = (void *)CDirectSoundVoice_SetEG;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetEG(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c203fd4]\n\t"
      "ret\n\t"
      :
      : [c203fd4] "m"(b204f77_c203fd4)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetEG: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetFilter (0x204f93) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b204f93_c204005)(void) = (void *)CDirectSoundVoice_SetFilter;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetFilter(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204005]\n\t"
      "ret\n\t"
      :
      : [c204005] "m"(b204f93_c204005)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetFilter: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetHeadroom (0x204faf) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b204faf_c204036)(void) = (void *)CDirectSoundVoice_SetHeadroom;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetHeadroom(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204036]\n\t"
      "ret\n\t"
      :
      : [c204036] "m"(b204faf_c204036)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetHeadroom: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetMixBinVolumes_12 (0x204fcb) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b204fcb_c204075)(void) = (void *)CDirectSoundVoice_SetMixBinVolumes;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetMixBinVolumes_12(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204075]\n\t"
      "ret\n\t"
      :
      : [c204075] "m"(b204fcb_c204075)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetMixBinVolumes_12: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetAllParameters (0x204feb) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b204feb_c2040e9)(void) = (void *)CDirectSoundVoice_SetAllParameters;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetAllParameters(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2040e9]\n\t"
      "ret\n\t"
      :
      : [c2040e9] "m"(b204feb_c2040e9)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetAllParameters: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetConeAngles (0x20500b) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void (*const b20500b_c204124)(void) = (void *)CDirectSoundVoice_SetConeAngles;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetConeAngles(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204124]\n\t"
      "ret\n\t"
      :
      : [c204124] "m"(b20500b_c204124)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetConeAngles: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetConeOrientation (0x20502f) — XBE naked draft (batch 355). */
#if defined(__clang__)
static void (*const b20502f_c2049aa)(void) = (void *)CDirectSoundBuffer_SetConeOrientation;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetConeOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2049aa]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2049aa] "m"(b20502f_c2049aa)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetConeOrientation: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetConeOutsideVolume (0x205064) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b205064_c2041b5)(void) = (void *)CDirectSoundVoice_SetConeOutsideVolume;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetConeOutsideVolume(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2041b5]\n\t"
      "ret\n\t"
      :
      : [c2041b5] "m"(b205064_c2041b5)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetConeOutsideVolume: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetMaxDistance (0x205084) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b205084_c2049d8)(void) = (void *)CDirectSoundBuffer_SetMaxDistance;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetMaxDistance(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2049d8]\n\t"
      "ret\n\t"
      :
      : [c2049d8] "m"(b205084_c2049d8)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetMaxDistance: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetMinDistance (0x2050a8) — XBE naked draft (batch 359). */
#if defined(__clang__)
static void (*const b2050a8_c2049f0)(void) = (void *)CDirectSoundBuffer_SetMinDistance;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetMinDistance(void)
{
  __asm__ volatile(
      "pushl 0xc(%%esp)\n\t"
      "flds 0xc(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2049f0]\n\t"
      "ret\n\t"
      :
      : [c2049f0] "m"(b2050a8_c2049f0)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetMinDistance: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetMode (0x2050cc) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b2050cc_c20426e)(void) = (void *)CDirectSoundVoice_SetMode;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetMode(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20426e]\n\t"
      "ret\n\t"
      :
      : [c20426e] "m"(b2050cc_c20426e)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetMode: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetPosition (0x2050ec) — XBE naked draft (batch 355). */
#if defined(__clang__)
static void (*const b2050ec_c204a0d)(void) = (void *)CDirectSoundBuffer_SetPosition;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204a0d]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204a0d] "m"(b2050ec_c204a0d)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetPosition: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetVelocity (0x205121) — XBE naked draft (batch 355). */
#if defined(__clang__)
static void (*const b205121_c204a36)(void) = (void *)CDirectSoundBuffer_SetVelocity;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x10(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204a36]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204a36] "m"(b205121_c204a36)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetVelocity: clang naked draft required"
#endif


/* IDirectSoundBuffer_PlayEx (0x205156) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void (*const b205156_c2043a4)(void) = (void *)CDirectSoundBuffer_PlayEx;

__attribute__((naked, noinline))
void IDirectSoundBuffer_PlayEx(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2043a4]\n\t"
      "ret\n\t"
      :
      : [c2043a4] "m"(b205156_c2043a4)
      : "memory");
}
#else
#error "IDirectSoundBuffer_PlayEx: clang naked draft required"
#endif


/* IDirectSoundBuffer_StopEx (0x20517a) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void (*const b20517a_c2043e1)(void) = (void *)CDirectSoundBuffer_StopEx;

__attribute__((naked, noinline))
void IDirectSoundBuffer_StopEx(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2043e1]\n\t"
      "ret\n\t"
      :
      : [c2043e1] "m"(b20517a_c2043e1)
      : "memory");
}
#else
#error "IDirectSoundBuffer_StopEx: clang naked draft required"
#endif


/* IDirectSoundBuffer_GetStatus (0x2051be) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b2051be_c204437)(void) = (void *)CDirectSoundBuffer_GetStatus;

__attribute__((naked, noinline))
void IDirectSoundBuffer_GetStatus(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204437]\n\t"
      "ret\n\t"
      :
      : [c204437] "m"(b2051be_c204437)
      : "memory");
}
#else
#error "IDirectSoundBuffer_GetStatus: clang naked draft required"
#endif


/* IDirectSoundBuffer_GetCurrentPosition (0x2051da) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b2051da_c2044b5)(void) = (void *)CDirectSoundBuffer_GetCurrentPosition;

__attribute__((naked, noinline))
void IDirectSoundBuffer_GetCurrentPosition(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2044b5]\n\t"
      "ret\n\t"
      :
      : [c2044b5] "m"(b2051da_c2044b5)
      : "memory");
}
#else
#error "IDirectSoundBuffer_GetCurrentPosition: clang naked draft required"
#endif


/* IDirectSoundBuffer_Lock (0x205216) — XBE naked draft (batch 358). */
#if defined(__clang__)
static void (*const b205216_c2044ea)(void) = (void *)CDirectSoundBuffer_Lock;

__attribute__((naked, noinline))
void IDirectSoundBuffer_Lock(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x24(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x20(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "negl %%ecx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2044ea]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2044ea] "m"(b205216_c2044ea)
      : "memory");
}
#else
#error "IDirectSoundBuffer_Lock: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetI3DL2Source (0x205246) — XBE naked draft (batch 342). */
#if defined(__clang__)
static void (*const b205246_c20434d)(void) = CDirectSoundVoice_SetI3DL2Source;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetI3DL2Source(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20434d]\n\t"
      "ret\n\t"
      :
      : [c20434d] "m"(b205246_c20434d)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetI3DL2Source: clang naked draft required"
#endif


/* IDirectSoundStream_SetPitch (0x20527a) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b20527a_c203f32)(void) = (void *)CDirectSoundVoice_SetPitch;

__attribute__((naked, noinline))
void IDirectSoundStream_SetPitch(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203f32]\n\t"
      "ret\n\t"
      :
      : [c203f32] "m"(b20527a_c203f32)
      : "memory");
}
#else
#error "IDirectSoundStream_SetPitch: clang naked draft required"
#endif


/* IDirectSoundStream_SetLFO (0x20528e) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b20528e_c203fa3)(void) = (void *)CDirectSoundVoice_SetLFO;

__attribute__((naked, noinline))
void IDirectSoundStream_SetLFO(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fa3]\n\t"
      "ret\n\t"
      :
      : [c203fa3] "m"(b20528e_c203fa3)
      : "memory");
}
#else
#error "IDirectSoundStream_SetLFO: clang naked draft required"
#endif


/* IDirectSoundStream_SetEG (0x2052a2) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b2052a2_c203fd4)(void) = (void *)CDirectSoundVoice_SetEG;

__attribute__((naked, noinline))
void IDirectSoundStream_SetEG(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203fd4]\n\t"
      "ret\n\t"
      :
      : [c203fd4] "m"(b2052a2_c203fd4)
      : "memory");
}
#else
#error "IDirectSoundStream_SetEG: clang naked draft required"
#endif


/* IDirectSoundStream_SetFilter (0x2052b6) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b2052b6_c204005)(void) = (void *)CDirectSoundVoice_SetFilter;

__attribute__((naked, noinline))
void IDirectSoundStream_SetFilter(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204005]\n\t"
      "ret\n\t"
      :
      : [c204005] "m"(b2052b6_c204005)
      : "memory");
}
#else
#error "IDirectSoundStream_SetFilter: clang naked draft required"
#endif


/* IDirectSoundStream_SetHeadroom (0x2052ca) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b2052ca_c204036)(void) = (void *)CDirectSoundVoice_SetHeadroom;

__attribute__((naked, noinline))
void IDirectSoundStream_SetHeadroom(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204036]\n\t"
      "ret\n\t"
      :
      : [c204036] "m"(b2052ca_c204036)
      : "memory");
}
#else
#error "IDirectSoundStream_SetHeadroom: clang naked draft required"
#endif


/* 0x002052de */
void IDirectSoundStream_SetMixBinVolumes_12(void)
{
  CDirectSoundVoice_SetMixBinVolumes();
  CDirectSoundVoice_SetAllParameters();
  CDirectSoundVoice_SetConeAngles();
}

/* IDirectSoundStream_SetConeOrientation (0x2052ed) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b2052ed_c204b28)(void) = (void *)CDirectSoundStream_SetConeOrientation;

__attribute__((naked, noinline))
void IDirectSoundStream_SetConeOrientation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204b28]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204b28] "m"(b2052ed_c204b28)
      : "memory");
}
#else
#error "IDirectSoundStream_SetConeOrientation: clang naked draft required"
#endif


/* 0x0020534b */
void IDirectSoundStream_SetMode(void)
{
  CDirectSoundVoice_SetMode();
  CDirectSoundVoice_SetPosition();
}

/* IDirectSoundStream_SetPosition (0x205350) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b205350_c204bbd)(void) = (void *)CDirectSoundStream_SetPosition;

__attribute__((naked, noinline))
void IDirectSoundStream_SetPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204bbd]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204bbd] "m"(b205350_c204bbd)
      : "memory");
}
#else
#error "IDirectSoundStream_SetPosition: clang naked draft required"
#endif


/* IDirectSoundStream_SetVelocity (0x205379) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b205379_c204bea)(void) = (void *)CDirectSoundStream_SetVelocity;

__attribute__((naked, noinline))
void IDirectSoundStream_SetVelocity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $0xc, %%esp\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c204bea]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204bea] "m"(b205379_c204bea)
      : "memory");
}
#else
#error "IDirectSoundStream_SetVelocity: clang naked draft required"
#endif


/* 0x002053a2 */
void IDirectSoundStream_Pause(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  CMcpxStream_Pause();
  /* test edx, edx -> je 0x2047aa */
  /* relift: cmp eax, dword ptr [ecx + 4] -> jne 0x2047bf */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* DirectSoundDoWork (0x2053ac) — XBE naked draft (batch 355). */
#if defined(__clang__)
static void (*const b2053ac_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b2053ac_c203de3)(void) = (void *)CDirectSound_DoWork;

__attribute__((naked, noinline))
void DirectSoundDoWork(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x222ce0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LDirectSoundDoWork_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c203de3]\n\t"
      ".LDirectSoundDoWork_1:\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "je .LDirectSoundDoWork_2\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LDirectSoundDoWork_2:\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2053ac_c20368b), [c203de3] "m"(b2053ac_c203de3)
      : "memory");
}
#else
#error "DirectSoundDoWork: clang naked draft required"
#endif


/* CDirectSoundVoice_SetFrequency (0x2055a1) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void (*const b2055a1_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b2055a1_c20c857)(void) = XAudioCalculatePitch;
static void (*const b2055a1_c203f32)(void) = CDirectSoundVoice_SetPitch;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetFrequency(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCDirectSoundVoice_SetFrequency_1\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      ".LCDirectSoundVoice_SetFrequency_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c20c857]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c203f32]\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LCDirectSoundVoice_SetFrequency_2\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetFrequency_2:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2055a1_c20368b), [c20c857] "m"(b2055a1_c20c857), [c203f32] "m"(b2055a1_c203f32)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetFrequency: clang naked draft required"
#endif


/* CDirectSoundVoice_SetOutputBuffer (0x2055e4) — XBE naked draft (batch 324). */
#if defined(__clang__)
static void (*const b2055e4_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b2055e4_c2090ca_tgt(void) { return; }
static void (*const b2055e4_c2090ca)(void) = b2055e4_c2090ca_tgt;
static void b2055e4_c20552e_tgt(void) { return; }
static void (*const b2055e4_c20552e)(void) = b2055e4_c20552e_tgt;
static void b2055e4_c208f52_tgt(void) { return; }
static void (*const b2055e4_c208f52)(void) = b2055e4_c208f52_tgt;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetOutputBuffer(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "leal -0x1c(%%esi), %%eax\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "andl %%eax, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "je .LCDirectSoundVoice_SetOutputBuffer_2\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCDirectSoundVoice_SetOutputBuffer_1\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "call *%[c2090ca]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCDirectSoundVoice_SetOutputBuffer_2\n\t"
      ".LCDirectSoundVoice_SetOutputBuffer_1:\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c20552e]\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LCDirectSoundVoice_SetOutputBuffer_2\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "call *%[c208f52]\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LCDirectSoundVoice_SetOutputBuffer_2:\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "je .LCDirectSoundVoice_SetOutputBuffer_3\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetOutputBuffer_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2055e4_c20368b), [c2090ca] "m"(b2055e4_c2090ca), [c20552e] "m"(b2055e4_c20552e), [c208f52] "m"(b2055e4_c208f52)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetOutputBuffer: clang naked draft required"
#endif


/* CDirectSoundVoice_SetMixBins (0x205650) — XBE naked draft (batch 330). */
#if defined(__clang__)
static void (*const b205650_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b205650_c203f07_tgt(void) { return; }
static void (*const b205650_c203f07)(void) = b205650_c203f07_tgt;
static void (*const b205650_c2097a9)(void) = CMcpxVoiceClient_SetMixBins;
static void (*const b205650_c204075)(void) = CDirectSoundVoice_SetMixBinVolumes;

__attribute__((naked, noinline))
void CDirectSoundVoice_SetMixBins(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl 0x20(%%ecx), %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LCDirectSoundVoice_SetMixBins_1\n\t"
      "pushl %%edi\n\t"
      "call *%[c203f07]\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "call *%[c2097a9]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCDirectSoundVoice_SetMixBins_1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c204075]\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LCDirectSoundVoice_SetMixBins_1:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCDirectSoundVoice_SetMixBins_2\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundVoice_SetMixBins_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b205650_c20368b), [c203f07] "m"(b205650_c203f07), [c2097a9] "m"(b205650_c2097a9), [c204075] "m"(b205650_c204075)
      : "memory");
}
#else
#error "CDirectSoundVoice_SetMixBins: clang naked draft required"
#endif


/* CDirectSoundBufferSettings_SetBufferData (0x2056a8) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void b2056a8_c203664_tgt(void) { return; }
static void (*const b2056a8_c203664)(void) = b2056a8_c203664_tgt;
static void b2056a8_c203609_tgt(void) { return; }
static void (*const b2056a8_c203609)(void) = b2056a8_c203609_tgt;

__attribute__((naked, noinline))
void CDirectSoundBufferSettings_SetBufferData(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl $0x80000000, %%ebx\n\t"
      "testl %%ebx, 0xc(%%esi)\n\t"
      "pushl %%edi\n\t"
      "leal 0x48(%%esi), %%edi\n\t"
      "je .LCDirectSoundBufferSettings_SetBufferData_1\n\t"
      "andl $0, (%%edi)\n\t"
      "jmp .LCDirectSoundBufferSettings_SetBufferData_2\n\t"
      ".LCDirectSoundBufferSettings_SetBufferData_1:\n\t"
      "pushl %%edi\n\t"
      "call *%[c203664]\n\t"
      ".LCDirectSoundBufferSettings_SetBufferData_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4c(%%esi)\n\t"
      "je .LCDirectSoundBufferSettings_SetBufferData_4\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LCDirectSoundBufferSettings_SetBufferData_3\n\t"
      "orl %%ebx, 0xc(%%esi)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "jmp .LCDirectSoundBufferSettings_SetBufferData_4\n\t"
      ".LCDirectSoundBufferSettings_SetBufferData_3:\n\t"
      "andb $0x7f, 0xf(%%esi)\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c203609]\n\t"
      "movl %%eax, (%%edi)\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x7ff8fff2, %%eax\n\t"
      "addl $0x8007000e, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "js .LCDirectSoundBufferSettings_SetBufferData_5\n\t"
      ".LCDirectSoundBufferSettings_SetBufferData_4:\n\t"
      "movl 0x4c(%%esi), %%eax\n\t"
      "andl $0, 0x50(%%esi)\n\t"
      "movl %%eax, 0x54(%%esi)\n\t"
      ".LCDirectSoundBufferSettings_SetBufferData_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c203664] "m"(b2056a8_c203664), [c203609] "m"(b2056a8_c203609)
      : "memory");
}
#else
#error "CDirectSoundBufferSettings_SetBufferData: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetBufferData (0x205768) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void (*const b205768_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b205768_c20b46d_tgt(void) { return; }
static void (*const b205768_c20b46d)(void) = b205768_c20b46d_tgt;
static void (*const b205768_c2056a8)(void) = CDirectSoundBufferSettings_SetBufferData;
static void (*const b205768_c20ba90)(void) = CMcpxBuffer_SetBufferData;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetBufferData(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl 0x48(%%eax), %%edi\n\t"
      "jne .LCDirectSoundBuffer_SetBufferData_1\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpl 0x4c(%%eax), %%ecx\n\t"
      "je .LCDirectSoundBuffer_SetBufferData_2\n\t"
      ".LCDirectSoundBuffer_SetBufferData_1:\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "call *%[c20b46d]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCDirectSoundBuffer_SetBufferData_2\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c2056a8]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LCDirectSoundBuffer_SetBufferData_2\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCDirectSoundBuffer_SetBufferData_2\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LCDirectSoundBuffer_SetBufferData_2\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "call *%[c20ba90]\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LCDirectSoundBuffer_SetBufferData_2:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "je .LCDirectSoundBuffer_SetBufferData_3\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_SetBufferData_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b205768_c20368b), [c20b46d] "m"(b205768_c20b46d), [c2056a8] "m"(b205768_c2056a8), [c20ba90] "m"(b205768_c20ba90)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetBufferData: clang naked draft required"
#endif


/* CDirectSoundBuffer_Play (0x2057dd) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b2057dd_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b2057dd_c2043a4)(void) = (void *)CDirectSoundBuffer_PlayEx;

__attribute__((naked, noinline))
void CDirectSoundBuffer_Play(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl 0x18(%%esp)\n\t"
      "call *%[c2043a4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundBuffer_Play_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_Play_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b2057dd_c20368b), [c2043a4] "m"(b2057dd_c2043a4)
      : "memory");
}
#else
#error "CDirectSoundBuffer_Play: clang naked draft required"
#endif


/* CDirectSoundBuffer_Stop (0x20580f) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b20580f_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b20580f_c2043e1)(void) = (void *)CDirectSoundBuffer_StopEx;

__attribute__((naked, noinline))
void CDirectSoundBuffer_Stop(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c20368b]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c2043e1]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LCDirectSoundBuffer_Stop_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_Stop_1:\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b20580f_c20368b), [c2043e1] "m"(b20580f_c2043e1)
      : "memory");
}
#else
#error "CDirectSoundBuffer_Stop: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetNotificationPositions (0x20583f) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void b20583f_c203664_tgt(void) { return; }
static void (*const b20583f_c203664)(void) = b20583f_c203664_tgt;
static void b20583f_c203609_tgt(void) { return; }
static void (*const b20583f_c203609)(void) = b20583f_c203609_tgt;
static void b20583f_c204637_tgt(void) { return; }
static void (*const b20583f_c204637)(void) = b20583f_c204637_tgt;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetNotificationPositions(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl 0x8(%%esp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "addl $0x24, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c203664]\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%edi, 0x28(%%eax)\n\t"
      "je .LCDirectSoundBuffer_SetNotificationPositions_1\n\t"
      "pushl 0x18(%%esp)\n\t"
      "movl %%edi, %%eax\n\t"
      "shll $3, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203609]\n\t"
      "movl %%eax, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "js .LCDirectSoundBuffer_SetNotificationPositions_1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c204637]\n\t"
      ".LCDirectSoundBuffer_SetNotificationPositions_1:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c203664] "m"(b20583f_c203664), [c203609] "m"(b20583f_c203609), [c204637] "m"(b20583f_c204637)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetNotificationPositions: clang naked draft required"
#endif


/* CDirectSoundBuffer_SetOutputBuffer (0x205894) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b205894_c20368b)(void) = (void *)DirectSoundEnterCriticalSection;
static void (*const b205894_c2055e4)(void) = (void *)CDirectSoundVoice_SetOutputBuffer;

__attribute__((naked, noinline))
void CDirectSoundBuffer_SetOutputBuffer(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl 0x10(%%esp)\n\t"
      "call *%[c2055e4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LCDirectSoundBuffer_SetOutputBuffer_1\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundBuffer_SetOutputBuffer_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b205894_c20368b), [c2055e4] "m"(b205894_c2055e4)
      : "memory");
}
#else
#error "CDirectSoundBuffer_SetOutputBuffer: clang naked draft required"
#endif


/* CDirectSoundStream_AddRef (0x2059f9) — XBE naked draft (batch 373). */
#if defined(__clang__)
static void (*const b2059f9_c203936)(void) = (void *)DSound_CRefCount_AddRef;

__attribute__((naked, noinline))
void CDirectSoundStream_AddRef(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c203936]\n\t"
      "ret\n\t"
      :
      : [c203936] "m"(b2059f9_c203936)
      : "memory");
}
#else
#error "CDirectSoundStream_AddRef: clang naked draft required"
#endif


/* CDirectSoundStream_Release (0x205a09) — XBE naked draft (batch 374). */
#if defined(__clang__)
static void (*const b205a09_c20395b)(void) = (void *)DSound_CRefCount_Release;

__attribute__((naked, noinline))
void CDirectSoundStream_Release(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20395b]\n\t"
      "ret\n\t"
      :
      : [c20395b] "m"(b205a09_c20395b)
      : "memory");
}
#else
#error "CDirectSoundStream_Release: clang naked draft required"
#endif


/* CDirectSoundStream_SetOutputBuffer (0x205a19) — XBE naked draft (batch 342). */
#if defined(__clang__)
static void (*const b205a19_c20368b)(void) = DirectSoundEnterCriticalSection;
static void (*const b205a19_c2055e4)(void) = CDirectSoundVoice_SetOutputBuffer;

__attribute__((naked, noinline))
void CDirectSoundStream_SetOutputBuffer(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x18(%%eax)\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LCDirectSoundStream_SetOutputBuffer_1\n\t"
      "pushl 0x14(%%esp)\n\t"
      "addl $4, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c2055e4]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCDirectSoundStream_SetOutputBuffer_1:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDirectSoundStream_SetOutputBuffer_2\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSoundStream_SetOutputBuffer_2:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b205a19_c20368b), [c2055e4] "m"(b205a19_c2055e4)
      : "memory");
}
#else
#error "CDirectSoundStream_SetOutputBuffer: clang naked draft required"
#endif


/* 0x00205aa8 */
void CDirectSoundBuffer_SetFrequency(void)
{
  int eax = 0;

  DirectSoundEnterCriticalSection();
  /* test eax, eax -> jne 0x2055bf */
  XAudioCalculatePitch();
  CDirectSoundVoice_SetPitch();
  DirectSoundEnterCriticalSection();

  (void)eax;
}

/* 0x00205aad */
void CDirectSoundBuffer_SetMixBins(void)
{
  int ebx = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203f07(0); */
  CMcpxVoiceClient_SetMixBins();
  /* test ebx, ebx -> jl 0x20568e */
  CDirectSoundVoice_SetMixBinVolumes();
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x20569f */

  (void)ebx;
  (void)ebp;
}

/* CDirectSoundStream_SetFrequency (0x205ac7) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b205ac7_c2055a1)(void) = (void *)CDirectSoundVoice_SetFrequency;

__attribute__((naked, noinline))
void CDirectSoundStream_SetFrequency(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2055a1]\n\t"
      "ret\n\t"
      :
      : [c2055a1] "m"(b205ac7_c2055a1)
      : "memory");
}
#else
#error "CDirectSoundStream_SetFrequency: clang naked draft required"
#endif


/* CDirectSoundStream_SetMixBins (0x205adb) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b205adb_c205650)(void) = (void *)CDirectSoundVoice_SetMixBins;

__attribute__((naked, noinline))
void CDirectSoundStream_SetMixBins(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205650]\n\t"
      "ret\n\t"
      :
      : [c205650] "m"(b205adb_c205650)
      : "memory");
}
#else
#error "CDirectSoundStream_SetMixBins: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetFrequency (0x205aef) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b205aef_c2055a1)(void) = (void *)CDirectSoundVoice_SetFrequency;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetFrequency(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2055a1]\n\t"
      "ret\n\t"
      :
      : [c2055a1] "m"(b205aef_c2055a1)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetFrequency: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetOutputBuffer (0x205b0b) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b205b0b_c205894)(void) = (void *)CDirectSoundBuffer_SetOutputBuffer;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetOutputBuffer(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205894]\n\t"
      "ret\n\t"
      :
      : [c205894] "m"(b205b0b_c205894)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetOutputBuffer: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetMixBins (0x205b27) — XBE naked draft (batch 371). */
#if defined(__clang__)
static void (*const b205b27_c205650)(void) = (void *)CDirectSoundVoice_SetMixBins;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetMixBins(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0x8(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205650]\n\t"
      "ret\n\t"
      :
      : [c205650] "m"(b205b27_c205650)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetMixBins: clang naked draft required"
#endif


/* IDirectSoundBuffer_Stop (0x205b67) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b205b67_c20580f)(void) = CDirectSoundBuffer_Stop;

__attribute__((naked, noinline))
void IDirectSoundBuffer_Stop(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20580f]\n\t"
      "ret\n\t"
      :
      : [c20580f] "m"(b205b67_c20580f)
      : "memory");
}
#else
#error "IDirectSoundBuffer_Stop: clang naked draft required"
#endif


/* IDirectSoundBuffer_SetNotificationPositions (0x205b9f) — XBE naked draft (batch 368). */
#if defined(__clang__)
static void (*const b205b9f_c20583f)(void) = (void *)CDirectSoundBuffer_SetNotificationPositions;

__attribute__((naked, noinline))
void IDirectSoundBuffer_SetNotificationPositions(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl 0xc(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%esp)\n\t"
      "addl $-0x1c, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20583f]\n\t"
      "ret\n\t"
      :
      : [c20583f] "m"(b205b9f_c20583f)
      : "memory");
}
#else
#error "IDirectSoundBuffer_SetNotificationPositions: clang naked draft required"
#endif


/* 0x00205bd3 */
void IDirectSoundStream_SetOutputBuffer(void)
{
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* test edi, edi -> jl 0x205a42 */
  CDirectSoundVoice_SetOutputBuffer();
  /* test ebx, ebx -> je 0x205a51 */
  /* relift: FUN_00204925(0, 0); */
  /* test ecx, ecx -> je 0x205a7b */

  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* IDirectSoundStream_SetMixBins (0x205bd8) — XBE naked draft (batch 382). */
#if defined(__clang__)
static void (*const b205bd8_c205650)(void) = (void *)CDirectSoundVoice_SetMixBins;

__attribute__((naked, noinline))
void IDirectSoundStream_SetMixBins(void)
{
  __asm__ volatile(
      "pushl 0x8(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205650]\n\t"
      "ret\n\t"
      :
      : [c205650] "m"(b205bd8_c205650)
      : "memory");
}
#else
#error "IDirectSoundStream_SetMixBins: clang naked draft required"
#endif


/* CDirectSoundStream_Constructor (0x205e69) — XBE naked draft (batch 376). */
#if defined(__clang__)
static void b205e69_c205c86_tgt(void) { return; }
static void (*const b205e69_c205c86)(void) = b205e69_c205c86_tgt;

__attribute__((naked, noinline))
void CDirectSoundStream_Constructor(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0xc(%%esp)\n\t"
      "leal 0x4(%%esi), %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c205c86]\n\t"
      "movl $0x2c2658, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movl $0x2c2664, (%%esi)\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c205c86] "m"(b205e69_c205c86)
      : "memory");
}
#else
#error "CDirectSoundStream_Constructor: clang naked draft required"
#endif


/* CDirectSound_CreateSoundBuffer (0x205f6d) — XBE naked draft (batch 319). */
#if defined(__clang__)
static void (*const b205f6d_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b205f6d_c203609_tgt(void) { return; }
static void (*const b205f6d_c203609)(void) = b205f6d_c203609_tgt;
static void b205f6d_c205d52_tgt(void) { return; }
static void (*const b205f6d_c205d52)(void) = b205f6d_c205d52_tgt;
static void b205f6d_c205d8e_tgt(void) { return; }
static void (*const b205f6d_c205d8e)(void) = b205f6d_c205d8e_tgt;
static void b205f6d_c204821_tgt(void) { return; }
static void (*const b205f6d_c204821)(void) = b205f6d_c204821_tgt;

__attribute__((naked, noinline))
void CDirectSound_CreateSoundBuffer(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x30\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c203609]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LCDirectSound_CreateSoundBuffer_1\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c205d52]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCDirectSound_CreateSoundBuffer_1:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "js .LCDirectSound_CreateSoundBuffer_2\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c205d8e]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCDirectSound_CreateSoundBuffer_2\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "addl $0x1c, %%edi\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%edi, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LCDirectSound_CreateSoundBuffer_3\n\t"
      ".LCDirectSound_CreateSoundBuffer_2:\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204821]\n\t"
      ".LCDirectSound_CreateSoundBuffer_3:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDirectSound_CreateSoundBuffer_4\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_CreateSoundBuffer_4:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b205f6d_c20368b), [c203609] "m"(b205f6d_c203609), [c205d52] "m"(b205f6d_c205d52), [c205d8e] "m"(b205f6d_c205d8e), [c204821] "m"(b205f6d_c204821)
      : "memory");
}
#else
#error "CDirectSound_CreateSoundBuffer: clang naked draft required"
#endif


/* CDirectSound_CreateSoundStream (0x205fed) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void (*const b205fed_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b205fed_c203609_tgt(void) { return; }
static void (*const b205fed_c203609)(void) = b205fed_c203609_tgt;
static void (*const b205fed_c205e69)(void) = CDirectSoundStream_Constructor;
static void b205fed_c205eb6_tgt(void) { return; }
static void (*const b205fed_c205eb6)(void) = b205fed_c205eb6_tgt;
static void b205fed_c204837_tgt(void) { return; }
static void (*const b205fed_c204837)(void) = b205fed_c204837_tgt;

__attribute__((naked, noinline))
void CDirectSound_CreateSoundStream(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c20368b]\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x28\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c203609]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LCDirectSound_CreateSoundStream_1\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c205e69]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCDirectSound_CreateSoundStream_1:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "js .LCDirectSound_CreateSoundStream_2\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c205eb6]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LCDirectSound_CreateSoundStream_2\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "jmp .LCDirectSound_CreateSoundStream_3\n\t"
      ".LCDirectSound_CreateSoundStream_2:\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204837]\n\t"
      ".LCDirectSound_CreateSoundStream_3:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LCDirectSound_CreateSoundStream_4\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LCDirectSound_CreateSoundStream_4:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b205fed_c20368b), [c203609] "m"(b205fed_c203609), [c205e69] "m"(b205fed_c205e69), [c205eb6] "m"(b205fed_c205eb6), [c204837] "m"(b205fed_c204837)
      : "memory");
}
#else
#error "CDirectSound_CreateSoundStream: clang naked draft required"
#endif


/* IDirectSound_CreateSoundBuffer (0x2060d4) — XBE naked draft (batch 363). */
#if defined(__clang__)
static void (*const b2060d4_c205f6d)(void) = (void *)CDirectSound_CreateSoundBuffer;

__attribute__((naked, noinline))
void IDirectSound_CreateSoundBuffer(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205f6d]\n\t"
      "ret\n\t"
      :
      : [c205f6d] "m"(b2060d4_c205f6d)
      : "memory");
}
#else
#error "IDirectSound_CreateSoundBuffer: clang naked draft required"
#endif


/* IDirectSound_CreateSoundStream (0x2060f8) — XBE naked draft (batch 380). */
#if defined(__clang__)
static void (*const b2060f8_c205fed)(void) = (void *)CDirectSound_CreateSoundStream;

__attribute__((naked, noinline))
void IDirectSound_CreateSoundStream(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x10(%%esp)\n\t"
      "addl $-8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205fed]\n\t"
      "ret\n\t"
      :
      : [c205fed] "m"(b2060f8_c205fed)
      : "memory");
}
#else
#error "IDirectSound_CreateSoundStream: clang naked draft required"
#endif


/* DirectSoundCreate (0x206232) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void (*const b206232_c20368b)(void) = DirectSoundEnterCriticalSection;
static void b206232_c2047ca_tgt(void) { return; }
static void (*const b206232_c2047ca)(void) = b206232_c2047ca_tgt;
static void b206232_c203609_tgt(void) { return; }
static void (*const b206232_c203609)(void) = b206232_c203609_tgt;
static void b206232_c20545c_tgt(void) { return; }
static void (*const b206232_c20545c)(void) = b206232_c20545c_tgt;
static void b206232_c20611c_tgt(void) { return; }
static void (*const b206232_c20611c)(void) = b206232_c20611c_tgt;
static void b206232_c2047df_tgt(void) { return; }
static void (*const b206232_c2047df)(void) = b206232_c2047df_tgt;

__attribute__((naked, noinline))
void DirectSoundCreate(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c20368b]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x222ce0, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LDirectSoundCreate_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c2047ca]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jmp .LDirectSoundCreate_4\n\t"
      ".LDirectSoundCreate_1:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x1c\n\t"
      "call *%[c203609]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LDirectSoundCreate_2\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c20545c]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LDirectSoundCreate_2:\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0x7ff8fff2, %%esi\n\t"
      "addl $0x8007000e, %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "js .LDirectSoundCreate_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c20611c]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LDirectSoundCreate_3\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "addl $8, %%edi\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%edi, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LDirectSoundCreate_4\n\t"
      ".LDirectSoundCreate_3:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2047df]\n\t"
      ".LDirectSoundCreate_4:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LDirectSoundCreate_5\n\t"
      "pushl $0x222674\n\t"
      "call *0x253098\n\t"
      ".LDirectSoundCreate_5:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20368b] "m"(b206232_c20368b), [c2047ca] "m"(b206232_c2047ca), [c203609] "m"(b206232_c203609), [c20545c] "m"(b206232_c20545c), [c20611c] "m"(b206232_c20611c), [c2047df] "m"(b206232_c2047df)
      : "memory");
}
#else
#error "DirectSoundCreate: clang naked draft required"
#endif


/* DirectSoundCreateStream (0x20630e) — XBE naked draft (batch 384). */
#if defined(__clang__)
static void (*const b20630e_c206232)(void) = (void *)DirectSoundCreate;
static void (*const b20630e_c2060f8)(void) = (void *)IDirectSound_CreateSoundStream;
static void b20630e_c205a68_tgt(void) { return; }
static void (*const b20630e_c205a68)(void) = b20630e_c205a68_tgt;

__attribute__((naked, noinline))
void DirectSoundCreateStream(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c206232]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LDirectSoundCreateStream_1\n\t"
      "pushl $0\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c2060f8]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LDirectSoundCreateStream_1:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c205a68]\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c206232] "m"(b20630e_c206232), [c2060f8] "m"(b20630e_c2060f8), [c205a68] "m"(b20630e_c205a68)
      : "memory");
}
#else
#error "DirectSoundCreateStream: clang naked draft required"
#endif


/* CMcpxAPU_Commit3dSettings (0x206a5e) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void b206a5e_c207b73_tgt(void) { return; }
static void (*const b206a5e_c207b73)(void) = b206a5e_c207b73_tgt;
static void b206a5e_c20ab80_tgt(void) { return; }
static void (*const b206a5e_c20ab80)(void) = b206a5e_c20ab80_tgt;
static void b206a5e_c207aca_tgt(void) { return; }
static void (*const b206a5e_c207aca)(void) = b206a5e_c207aca_tgt;
static void b206a5e_c207876_tgt(void) { return; }
static void (*const b206a5e_c207876)(void) = b206a5e_c207876_tgt;
static void b206a5e_c2063cb_tgt(void) { return; }
static void (*const b206a5e_c2063cb)(void) = b206a5e_c2063cb_tgt;
static void b206a5e_c2063b8_tgt(void) { return; }
static void (*const b206a5e_c2063b8)(void) = b206a5e_c2063b8_tgt;
static void (*const b206a5e_c209e6d)(void) = CMcpxVoiceClient_Commit3dSettings;
static void b206a5e_c20639e_tgt(void) { return; }
static void (*const b206a5e_c20639e)(void) = b206a5e_c20639e_tgt;

__attribute__((naked, noinline))
void CMcpxAPU_Commit3dSettings(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x238, %%esp\n\t"
      "testb $1, 0x222d60\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LCMcpxAPU_Commit3dSettings_1\n\t"
      "orl $1, 0x222d60\n\t"
      "movl $0x108, 0x20f140\n\t"
      ".LCMcpxAPU_Commit3dSettings_1:\n\t"
      "addl $0x1b4, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl $0, %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LCMcpxAPU_Commit3dSettings_2:\n\t"
      ".byte 0x0f, 0xb1, 0x11\n\t"
      "jne .LCMcpxAPU_Commit3dSettings_2\n\t"
      "orl %%eax, 0x8(%%ebp)\n\t"
      "testb $0x26, 0x8(%%ebp)\n\t"
      "je .LCMcpxAPU_Commit3dSettings_3\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x170(%%eax)\n\t"
      "fmuls 0x168(%%eax)\n\t"
      "flds 0x174(%%eax)\n\t"
      "fmuls 0x164(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1b8(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x174(%%eax)\n\t"
      "fmuls 0x160(%%eax)\n\t"
      "flds 0x16c(%%eax)\n\t"
      "fmuls 0x168(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1bc(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x16c(%%eax)\n\t"
      "fmuls 0x164(%%eax)\n\t"
      "flds 0x170(%%eax)\n\t"
      "fmuls 0x160(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1c0(%%eax)\n\t"
      ".LCMcpxAPU_Commit3dSettings_3:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb $1, 0x9(%%ebp)\n\t"
      "je .LCMcpxAPU_Commit3dSettings_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LCMcpxAPU_Commit3dSettings_4\n\t"
      "movl $0x118, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x238(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207b73]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LCMcpxAPU_Commit3dSettings_4\n\t"
      "leal -0x238(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x184, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c20ab80]\n\t"
      "orl $4, -0x228(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "leal -0x228(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl 0xc(%%ecx)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207aca]\n\t"
      "pushl %%edi\n\t"
      "pushl 0x20f140\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%ecx)\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "call *%[c207aca]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0xd0(%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c207876]\n\t"
      ".LCMcpxAPU_Commit3dSettings_4:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c2063cb]\n\t"
      "jmp .LCMcpxAPU_Commit3dSettings_6\n\t"
      ".LCMcpxAPU_Commit3dSettings_5:\n\t"
      "pushl %%eax\n\t"
      "call *%[c2063b8]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $0xffffff34, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      ".LCMcpxAPU_Commit3dSettings_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x118, %%eax\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "jne .LCMcpxAPU_Commit3dSettings_5\n\t"
      "cmpl %%edi, -0x14(%%ebp)\n\t"
      "movl 0x2531b0, %%ebx\n\t"
      "je .LCMcpxAPU_Commit3dSettings_7\n\t"
      "movb -0x10(%%ebp), %%cl\n\t"
      "call *%%ebx\n\t"
      ".LCMcpxAPU_Commit3dSettings_7:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "jmp .LCMcpxAPU_Commit3dSettings_9\n\t"
      ".LCMcpxAPU_Commit3dSettings_8:\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0xcc(%%esi), %%ecx\n\t"
      "call *%[c209e6d]\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LCMcpxAPU_Commit3dSettings_9:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LCMcpxAPU_Commit3dSettings_8\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "jmp .LCMcpxAPU_Commit3dSettings_11\n\t"
      ".LCMcpxAPU_Commit3dSettings_10:\n\t"
      "pushl %%esi\n\t"
      "call *%[c20639e]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x11c(%%eax), %%ecx\n\t"
      "addl $0x118, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "leal -0xcc(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%ecx)\n\t"
      ".LCMcpxAPU_Commit3dSettings_11:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LCMcpxAPU_Commit3dSettings_10\n\t"
      "cmpl %%edi, -0x14(%%ebp)\n\t"
      "je .LCMcpxAPU_Commit3dSettings_12\n\t"
      "movb -0x10(%%ebp), %%cl\n\t"
      "call *%%ebx\n\t"
      ".LCMcpxAPU_Commit3dSettings_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c207b73] "m"(b206a5e_c207b73), [c20ab80] "m"(b206a5e_c20ab80), [c207aca] "m"(b206a5e_c207aca), [c207876] "m"(b206a5e_c207876), [c2063cb] "m"(b206a5e_c2063cb), [c2063b8] "m"(b206a5e_c2063b8), [c209e6d] "m"(b206a5e_c209e6d), [c20639e] "m"(b206a5e_c20639e)
      : "memory");
}
#else
#error "CMcpxAPU_Commit3dSettings: clang naked draft required"
#endif


/* CMcpxAPU_SetMixBinHeadroom (0x206dc4) — XBE naked draft (batch 327). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CMcpxAPU_SetMixBinHeadroom(void)
{
  __asm__ volatile(
      "xorl %%ecx, %%ecx\n\t"
      "movl $0xfe820200, %%eax\n\t"
      ".LCMcpxAPU_SetMixBinHeadroom_1:\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, 0x4(%%esp)\n\t"
      "je .LCMcpxAPU_SetMixBinHeadroom_3\n\t"
      ".LCMcpxAPU_SetMixBinHeadroom_2:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxAPU_SetMixBinHeadroom_2\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "andl $7, %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LCMcpxAPU_SetMixBinHeadroom_3:\n\t"
      "addl $4, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $0xfe820280, %%eax\n\t"
      "jl .LCMcpxAPU_SetMixBinHeadroom_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CMcpxAPU_SetMixBinHeadroom: clang naked draft required"
#endif


/* CMcpxAPU_Set3dParameters (0x207234) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b207234_c206a5e)(void) = (void *)CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_Set3dParameters(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $0x10\n\t"
      "popl %%ecx\n\t"
      "leal 0x144(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "orb $0xff, 0x1b4(%%eax)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_Set3dParameters_1\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_Set3dParameters_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b207234_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_Set3dParameters: clang naked draft required"
#endif


/* CMcpxAPU_Set3dDistanceFactor (0x207265) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b207265_c206a5e)(void) = CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_Set3dDistanceFactor(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $0x60, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x178(%%ecx)\n\t"
      "je .LCMcpxAPU_Set3dDistanceFactor_1\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_Set3dDistanceFactor_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b207265_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_Set3dDistanceFactor: clang naked draft required"
#endif


/* CMcpxAPU_Set3dDopplerFactor (0x207289) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b207289_c206a5e)(void) = CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_Set3dDopplerFactor(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $0x40, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x180(%%ecx)\n\t"
      "je .LCMcpxAPU_Set3dDopplerFactor_1\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_Set3dDopplerFactor_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b207289_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_Set3dDopplerFactor: clang naked draft required"
#endif


/* CMcpxAPU_Set3dRolloffFactor (0x2072ad) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b2072ad_c206a5e)(void) = CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_Set3dRolloffFactor(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $4, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x17c(%%ecx)\n\t"
      "je .LCMcpxAPU_Set3dRolloffFactor_1\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_Set3dRolloffFactor_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b2072ad_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_Set3dRolloffFactor: clang naked draft required"
#endif


/* CMcpxAPU_Set3dPosition (0x207309) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b207309_c206a5e)(void) = (void *)CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_Set3dPosition(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x148(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orb $0xff, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_Set3dPosition_1\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_Set3dPosition_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b207309_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_Set3dPosition: clang naked draft required"
#endif


/* CMcpxAPU_Set3dVelocity (0x207334) — XBE naked draft (batch 366). */
#if defined(__clang__)
static void (*const b207334_c206a5e)(void) = (void *)CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_Set3dVelocity(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x154(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orl $0x40, 0x1b4(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_Set3dVelocity_1\n\t"
      "pushl $0\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_Set3dVelocity_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b207334_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_Set3dVelocity: clang naked draft required"
#endif


/* CMcpxAPU_SetI3DL2Listener (0x20735f) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void (*const b20735f_c206a5e)(void) = CMcpxAPU_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxAPU_SetI3DL2Listener(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "leal 0x184(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "orw $0x180, 0x1b4(%%eax)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxAPU_SetI3DL2Listener_1\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c206a5e]\n\t"
      ".LCMcpxAPU_SetI3DL2Listener_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c206a5e] "m"(b20735f_c206a5e)
      : "memory");
}
#else
#error "CMcpxAPU_SetI3DL2Listener: clang naked draft required"
#endif


/* CMcpxVoiceClient_SetFilter (0x208da2) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void b208da2_c2063cb_tgt(void) { return; }
static void (*const b208da2_c2063cb)(void) = b208da2_c2063cb_tgt;

__attribute__((naked, noinline))
void CMcpxVoiceClient_SetFilter(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $0xffff, %%edx\n\t"
      "je .LCMcpxVoiceClient_SetFilter_1\n\t"
      "pushl $6\n\t"
      "popl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "jmp .LCMcpxVoiceClient_SetFilter_2\n\t"
      ".LCMcpxVoiceClient_SetFilter_1:\n\t"
      "movl 0xac(%%ebx), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x88(%%ebx), %%esi\n\t"
      "movb 0x2(%%esi), %%al\n\t"
      "andl $3, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal 0xa8(%%ebx), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movzwl 0x2(%%esi), %%esi\n\t"
      "shrl $0x12, %%eax\n\t"
      "andl $7, %%eax\n\t"
      "andl %%edx, %%ecx\n\t"
      "andl %%edx, %%edi\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movzwl 0xae(%%ebx), %%edi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      ".LCMcpxVoiceClient_SetFilter_2:\n\t"
      "movl 0xe0(%%ebx), %%edi\n\t"
      "testb $0x10, 0xc(%%edi)\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "je .LCMcpxVoiceClient_SetFilter_3\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LCMcpxVoiceClient_SetFilter_3\n\t"
      "pushl $3\n\t"
      "popl %%edi\n\t"
      ".LCMcpxVoiceClient_SetFilter_3:\n\t"
      "andl $7, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "andl $3, %%edi\n\t"
      "orl %%edi, %%eax\n\t"
      "movl 0x88(%%ebx), %%edi\n\t"
      "andl %%edx, %%ecx\n\t"
      "shll $0x10, %%eax\n\t"
      "andl $0xffe0ffff, %%edi\n\t"
      "shll $0x10, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "movl 0xe0(%%ebx), %%ecx\n\t"
      "orl %%edi, %%eax\n\t"
      "movl %%eax, 0x88(%%ebx)\n\t"
      "movl %%esi, 0xa8(%%ebx)\n\t"
      "testb $0x10, 0xc(%%ecx)\n\t"
      "je .LCMcpxVoiceClient_SetFilter_5\n\t"
      "cmpl $2, 0x58(%%ebx)\n\t"
      "jne .LCMcpxVoiceClient_SetFilter_4\n\t"
      "andl $0, 0xac(%%ebx)\n\t"
      "jmp .LCMcpxVoiceClient_SetFilter_7\n\t"
      ".LCMcpxVoiceClient_SetFilter_4:\n\t"
      "movl 0x13c(%%ebx), %%eax\n\t"
      "movl 0x138(%%ebx), %%esi\n\t"
      "jmp .LCMcpxVoiceClient_SetFilter_6\n\t"
      ".LCMcpxVoiceClient_SetFilter_5:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LCMcpxVoiceClient_SetFilter_6:\n\t"
      "shll $0x10, %%eax\n\t"
      "andl %%edx, %%esi\n\t"
      "orl %%esi, %%eax\n\t"
      "movl %%eax, 0xac(%%ebx)\n\t"
      ".LCMcpxVoiceClient_SetFilter_7:\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%edx\n\t"
      "testb %%dl, 0x8(%%ebx)\n\t"
      "je .LCMcpxVoiceClient_SetFilter_14\n\t"
      "movl 0x10(%%ecx), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxVoiceClient_SetFilter_14\n\t"
      "pushl $4\n\t"
      "popl %%eax\n\t"
      ".LCMcpxVoiceClient_SetFilter_8:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_8\n\t"
      "movl 0x10(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0xfe8202f8\n\t"
      ".LCMcpxVoiceClient_SetFilter_9:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_9\n\t"
      "movl %%edx, 0xfe8202fc\n\t"
      ".LCMcpxVoiceClient_SetFilter_10:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_10\n\t"
      "movl 0x88(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0xfe820318\n\t"
      ".LCMcpxVoiceClient_SetFilter_11:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_11\n\t"
      "movl 0xa8(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0xfe820374\n\t"
      ".LCMcpxVoiceClient_SetFilter_12:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_12\n\t"
      "movl 0xac(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0xfe820378\n\t"
      ".LCMcpxVoiceClient_SetFilter_13:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_13\n\t"
      "movl $0, 0xfe8202fc\n\t"
      "movl 0xe0(%%ebx), %%ecx\n\t"
      "movl 0x10(%%ecx), %%ecx\n\t"
      "movzwl 0x2(%%ecx), %%ecx\n\t"
      "incl %%esi\n\t"
      "decl %%ecx\n\t"
      "sarl $1, %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jb .LCMcpxVoiceClient_SetFilter_8\n\t"
      ".LCMcpxVoiceClient_SetFilter_14:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxVoiceClient_SetFilter_15\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxVoiceClient_SetFilter_15:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b208da2_c2063cb)
      : "memory");
}
#else
#error "CMcpxVoiceClient_SetFilter: clang naked draft required"
#endif


/* CMcpxVoiceClient_SetMixBins (0x2097a9) — XBE naked draft (batch 313). */
#if defined(__clang__)
static void b2097a9_c2063cb_tgt(void) { return; }
static void (*const b2097a9_c2063cb)(void) = b2097a9_c2063cb_tgt;
static void b2097a9_c207f35_tgt(void) { return; }
static void (*const b2097a9_c207f35)(void) = b2097a9_c207f35_tgt;
static void b2097a9_c207ecf_tgt(void) { return; }
static void (*const b2097a9_c207ecf)(void) = b2097a9_c207ecf_tgt;

__attribute__((naked, noinline))
void CMcpxVoiceClient_SetMixBins(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "testb $1, 0x8(%%esi)\n\t"
      "je .LCMcpxVoiceClient_SetMixBins_7\n\t"
      "pushl %%ebx\n\t"
      "leal 0x84(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c207f35]\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxVoiceClient_SetMixBins_6\n\t"
      "pushl %%edi\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl $4\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      ".LCMcpxVoiceClient_SetMixBins_1:\n\t"
      "cmpl %%edi, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetMixBins_1\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%eax, 0xfe8202f8\n\t"
      ".LCMcpxVoiceClient_SetMixBins_2:\n\t"
      "cmpl %%edi, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetMixBins_2\n\t"
      "movl $1, 0xfe8202fc\n\t"
      ".LCMcpxVoiceClient_SetMixBins_3:\n\t"
      "cmpl %%edi, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetMixBins_3\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0xfe820300\n\t"
      ".LCMcpxVoiceClient_SetMixBins_4:\n\t"
      "cmpl %%edi, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetMixBins_4\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c207ecf]\n\t"
      "movl %%eax, 0xfe820304\n\t"
      ".LCMcpxVoiceClient_SetMixBins_5:\n\t"
      "cmpl %%edi, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetMixBins_5\n\t"
      "addl %%edi, -0x4(%%ebp)\n\t"
      "movl $0, 0xfe8202fc\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "incl %%ebx\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jb .LCMcpxVoiceClient_SetMixBins_1\n\t"
      "popl %%edi\n\t"
      ".LCMcpxVoiceClient_SetMixBins_6:\n\t"
      "popl %%ebx\n\t"
      ".LCMcpxVoiceClient_SetMixBins_7:\n\t"
      "cmpl $0, -0x10(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_SetMixBins_8\n\t"
      "movb -0xc(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxVoiceClient_SetMixBins_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b2097a9_c2063cb), [c207f35] "m"(b2097a9_c207f35), [c207ecf] "m"(b2097a9_c207ecf)
      : "memory");
}
#else
#error "CMcpxVoiceClient_SetMixBins: clang naked draft required"
#endif


/* CMcpxVoiceClient_SetPitch (0x209961) — XBE naked draft (batch 315). */
#if defined(__clang__)
static void b209961_c2063cb_tgt(void) { return; }
static void (*const b209961_c2063cb)(void) = b209961_c2063cb_tgt;
static void (*const b209961_c209961)(void) = CMcpxVoiceClient_SetPitch;
static void b209961_c2081f6_tgt(void) { return; }
static void (*const b209961_c2081f6)(void) = b209961_c2081f6_tgt;

__attribute__((naked, noinline))
void CMcpxVoiceClient_SetPitch(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "testl $0x82000, 0xc(%%eax)\n\t"
      "je .LCMcpxVoiceClient_SetPitch_3\n\t"
      "leal 0xb4(%%esi), %%edi\n\t"
      "movl (%%edi), %%esi\n\t"
      "jmp .LCMcpxVoiceClient_SetPitch_2\n\t"
      ".LCMcpxVoiceClient_SetPitch_1:\n\t"
      "leal -0xd4(%%esi), %%ecx\n\t"
      "call *%[c209961]\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LCMcpxVoiceClient_SetPitch_2:\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jne .LCMcpxVoiceClient_SetPitch_1\n\t"
      "jmp .LCMcpxVoiceClient_SetPitch_6\n\t"
      ".LCMcpxVoiceClient_SetPitch_3:\n\t"
      "testb $1, 0x8(%%esi)\n\t"
      "je .LCMcpxVoiceClient_SetPitch_6\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c2081f6]\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxVoiceClient_SetPitch_6\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      ".LCMcpxVoiceClient_SetPitch_4:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetPitch_4\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, 0xfe8202f8\n\t"
      ".LCMcpxVoiceClient_SetPitch_5:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetPitch_5\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%edx, 0xfe82037c\n\t"
      "movl 0xe0(%%esi), %%edx\n\t"
      "movl 0x10(%%edx), %%edx\n\t"
      "movzwl 0x2(%%edx), %%edx\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "decl %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jb .LCMcpxVoiceClient_SetPitch_4\n\t"
      ".LCMcpxVoiceClient_SetPitch_6:\n\t"
      "cmpl $0, -0xc(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_SetPitch_7\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxVoiceClient_SetPitch_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b209961_c2063cb), [c209961] "m"(b209961_c209961), [c2081f6] "m"(b209961_c2081f6)
      : "memory");
}
#else
#error "CMcpxVoiceClient_SetPitch: clang naked draft required"
#endif


/* CMcpxVoiceClient_SetLFO (0x209c05) — XBE naked draft (batch 310). */
#if defined(__clang__)
static void b209c05_c2063cb_tgt(void) { return; }
static void (*const b209c05_c2063cb)(void) = b209c05_c2063cb_tgt;
static void b209c05_c208b9f_tgt(void) { return; }
static void (*const b209c05_c208b9f)(void) = b209c05_c208b9f_tgt;
static void b209c05_c208c03_tgt(void) { return; }
static void (*const b209c05_c208c03)(void) = b209c05_c208c03_tgt;

__attribute__((naked, noinline))
void CMcpxVoiceClient_SetLFO(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxVoiceClient_SetLFO_1\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c208b9f]\n\t"
      "jmp .LCMcpxVoiceClient_SetLFO_2\n\t"
      ".LCMcpxVoiceClient_SetLFO_1:\n\t"
      "cmpl $1, %%eax\n\t"
      "jne .LCMcpxVoiceClient_SetLFO_2\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c208c03]\n\t"
      ".LCMcpxVoiceClient_SetLFO_2:\n\t"
      "testb $1, 0x8(%%esi)\n\t"
      "je .LCMcpxVoiceClient_SetLFO_10\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxVoiceClient_SetLFO_10\n\t"
      "pushl $4\n\t"
      "popl %%eax\n\t"
      ".LCMcpxVoiceClient_SetLFO_3:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_3\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe8202f8\n\t"
      ".LCMcpxVoiceClient_SetLFO_4:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_4\n\t"
      "movl $1, 0xfe8202fc\n\t"
      "testb $2, 0x8(%%esi)\n\t"
      "jne .LCMcpxVoiceClient_SetLFO_7\n\t"
      ".LCMcpxVoiceClient_SetLFO_5:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_5\n\t"
      "movl 0x88(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820318\n\t"
      ".LCMcpxVoiceClient_SetLFO_6:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_6\n\t"
      "movl 0x9c(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820350\n\t"
      ".LCMcpxVoiceClient_SetLFO_7:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_7\n\t"
      "movl 0xa0(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe82036c\n\t"
      ".LCMcpxVoiceClient_SetLFO_8:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_8\n\t"
      "movl 0xa4(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820370\n\t"
      ".LCMcpxVoiceClient_SetLFO_9:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_9\n\t"
      "movl $0, 0xfe8202fc\n\t"
      "movl 0xe0(%%esi), %%edx\n\t"
      "movl 0x10(%%edx), %%edx\n\t"
      "movzwl 0x2(%%edx), %%edx\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jb .LCMcpxVoiceClient_SetLFO_3\n\t"
      ".LCMcpxVoiceClient_SetLFO_10:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_SetLFO_11\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxVoiceClient_SetLFO_11:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b209c05_c2063cb), [c208b9f] "m"(b209c05_c208b9f), [c208c03] "m"(b209c05_c208c03)
      : "memory");
}
#else
#error "CMcpxVoiceClient_SetLFO: clang naked draft required"
#endif


/* CMcpxVoiceClient_SetEG (0x209d16) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void b209d16_c2063cb_tgt(void) { return; }
static void (*const b209d16_c2063cb)(void) = b209d16_c2063cb_tgt;
static void b209d16_c208c60_tgt(void) { return; }
static void (*const b209d16_c208c60)(void) = b209d16_c208c60_tgt;
static void b209d16_c208d09_tgt(void) { return; }
static void (*const b209d16_c208d09)(void) = b209d16_c208d09_tgt;

__attribute__((naked, noinline))
void CMcpxVoiceClient_SetEG(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxVoiceClient_SetEG_1\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c208c60]\n\t"
      "jmp .LCMcpxVoiceClient_SetEG_2\n\t"
      ".LCMcpxVoiceClient_SetEG_1:\n\t"
      "cmpl $1, %%eax\n\t"
      "jne .LCMcpxVoiceClient_SetEG_2\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c208d09]\n\t"
      ".LCMcpxVoiceClient_SetEG_2:\n\t"
      "testb $1, 0x8(%%esi)\n\t"
      "je .LCMcpxVoiceClient_SetEG_12\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxVoiceClient_SetEG_12\n\t"
      "pushl $4\n\t"
      "popl %%eax\n\t"
      ".LCMcpxVoiceClient_SetEG_3:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_3\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe8202f8\n\t"
      ".LCMcpxVoiceClient_SetEG_4:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_4\n\t"
      "movl $1, 0xfe8202fc\n\t"
      ".LCMcpxVoiceClient_SetEG_5:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_5\n\t"
      "movl 0x88(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820318\n\t"
      ".LCMcpxVoiceClient_SetEG_6:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_6\n\t"
      "movl 0x8c(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820308\n\t"
      ".LCMcpxVoiceClient_SetEG_7:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_7\n\t"
      "movl 0x90(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe82030c\n\t"
      ".LCMcpxVoiceClient_SetEG_8:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_8\n\t"
      "movl 0x94(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820310\n\t"
      ".LCMcpxVoiceClient_SetEG_9:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_9\n\t"
      "movl 0x98(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe820314\n\t"
      ".LCMcpxVoiceClient_SetEG_10:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_10\n\t"
      "movl 0xa0(%%esi), %%edx\n\t"
      "movl %%edx, 0xfe82036c\n\t"
      ".LCMcpxVoiceClient_SetEG_11:\n\t"
      "cmpl %%eax, 0xfe820010\n\t"
      "jb .LCMcpxVoiceClient_SetEG_11\n\t"
      "movl $0, 0xfe8202fc\n\t"
      "movl 0xe0(%%esi), %%edx\n\t"
      "movl 0x10(%%edx), %%edx\n\t"
      "movzwl 0x2(%%edx), %%edx\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jb .LCMcpxVoiceClient_SetEG_3\n\t"
      ".LCMcpxVoiceClient_SetEG_12:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_SetEG_13\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxVoiceClient_SetEG_13:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b209d16_c2063cb), [c208c60] "m"(b209d16_c208c60), [c208d09] "m"(b209d16_c208d09)
      : "memory");
}
#else
#error "CMcpxVoiceClient_SetEG: clang naked draft required"
#endif


/* CMcpxVoiceClient_Commit3dSettings (0x209e6d) — XBE naked draft (batch 315). */
#if defined(__clang__)
static void b209e6d_c207dd4_tgt(void) { return; }
static void (*const b209e6d_c207dd4)(void) = b209e6d_c207dd4_tgt;
static void b209e6d_c209b4b_tgt(void) { return; }
static void (*const b209e6d_c209b4b)(void) = b209e6d_c209b4b_tgt;
static void b209e6d_c208a42_tgt(void) { return; }
static void (*const b209e6d_c208a42)(void) = b209e6d_c208a42_tgt;
static void b209e6d_c209880_tgt(void) { return; }
static void (*const b209e6d_c209880)(void) = b209e6d_c209880_tgt;
static void (*const b209e6d_c209961)(void) = CMcpxVoiceClient_SetPitch;
static void (*const b209e6d_c208da2)(void) = CMcpxVoiceClient_SetFilter;
static void b209e6d_c207df9_tgt(void) { return; }
static void (*const b209e6d_c207df9)(void) = b209e6d_c207df9_tgt;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Commit3dSettings(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c207dd4]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "orl %%ecx, 0x80(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "cmpb $3, %%cl\n\t"
      "jne .LCMcpxVoiceClient_Commit3dSettings_5\n\t"
      "addl $0x80, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl $0, %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LCMcpxVoiceClient_Commit3dSettings_1:\n\t"
      ".byte 0x0f, 0xb1, 0x11\n\t"
      "jne .LCMcpxVoiceClient_Commit3dSettings_1\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "call *%[c209b4b]\n\t"
      "testb $2, 0x8(%%ebp)\n\t"
      "je .LCMcpxVoiceClient_Commit3dSettings_2\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "call *%[c208a42]\n\t"
      ".LCMcpxVoiceClient_Commit3dSettings_2:\n\t"
      "testb $0xb4, 0x8(%%ebp)\n\t"
      "je .LCMcpxVoiceClient_Commit3dSettings_3\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "call *%[c209880]\n\t"
      ".LCMcpxVoiceClient_Commit3dSettings_3:\n\t"
      "testb $0x40, 0x8(%%ebp)\n\t"
      "je .LCMcpxVoiceClient_Commit3dSettings_4\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "call *%[c209961]\n\t"
      ".LCMcpxVoiceClient_Commit3dSettings_4:\n\t"
      "testb $0x80, 0x8(%%ebp)\n\t"
      "je .LCMcpxVoiceClient_Commit3dSettings_5\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c208da2]\n\t"
      ".LCMcpxVoiceClient_Commit3dSettings_5:\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c207df9]\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c207dd4] "m"(b209e6d_c207dd4), [c209b4b] "m"(b209e6d_c209b4b), [c208a42] "m"(b209e6d_c208a42), [c209880] "m"(b209e6d_c209880), [c209961] "m"(b209e6d_c209961), [c208da2] "m"(b209e6d_c208da2), [c207df9] "m"(b209e6d_c207df9)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Commit3dSettings: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dParameters (0x20a0ef) — XBE naked draft (batch 361). */
#if defined(__clang__)
static void (*const b20a0ef_c209e6d)(void) = (void *)CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dParameters(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $0x10\n\t"
      "popl %%ecx\n\t"
      "leal 0x1c(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "orb $0xff, 0x80(%%eax)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_Set3dParameters_1\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dParameters_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a0ef_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dParameters: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dConeOrientation (0x20a145) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b20a145_c209e6d)(void) = (void *)CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dConeOrientation(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x40(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orl $0x18, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_Set3dConeOrientation_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dConeOrientation_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a145_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dConeOrientation: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dConeOutsideVolume (0x20a16d) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b20a16d_c209e6d)(void) = CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dConeOutsideVolume(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $0x10, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x4c(%%ecx)\n\t"
      "je .LCMcpxVoiceClient_Set3dConeOutsideVolume_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dConeOutsideVolume_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a16d_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dConeOutsideVolume: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dMaxDistance (0x20a18e) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b20a18e_c209e6d)(void) = CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dMaxDistance(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $4, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x54(%%ecx)\n\t"
      "je .LCMcpxVoiceClient_Set3dMaxDistance_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dMaxDistance_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a18e_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dMaxDistance: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dMinDistance (0x20a1af) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b20a1af_c209e6d)(void) = CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dMinDistance(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orl $4, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x50(%%ecx)\n\t"
      "je .LCMcpxVoiceClient_Set3dMinDistance_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dMinDistance_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a1af_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dMinDistance: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dMode (0x20a1d0) — XBE naked draft (batch 350). */
#if defined(__clang__)
static void (*const b20a1d0_c209e6d)(void) = CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dMode(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "orb $0xff, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "movl %%eax, 0x58(%%ecx)\n\t"
      "je .LCMcpxVoiceClient_Set3dMode_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dMode_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a1d0_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dMode: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dPosition (0x20a1f1) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b20a1f1_c209e6d)(void) = (void *)CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dPosition(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x20(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orb $0xff, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_Set3dPosition_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dPosition_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a1f1_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dPosition: clang naked draft required"
#endif


/* CMcpxVoiceClient_Set3dVelocity (0x20a219) — XBE naked draft (batch 367). */
#if defined(__clang__)
static void (*const b20a219_c209e6d)(void) = (void *)CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_Set3dVelocity(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x2c(%%ecx), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "orl $0x40, 0x80(%%ecx)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_Set3dVelocity_1\n\t"
      "pushl $0\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_Set3dVelocity_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a219_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_Set3dVelocity: clang naked draft required"
#endif


/* CMcpxVoiceClient_SetI3DL2Source (0x20a241) — XBE naked draft (batch 343). */
#if defined(__clang__)
static void (*const b20a241_c209e6d)(void) = CMcpxVoiceClient_Commit3dSettings;

__attribute__((naked, noinline))
void CMcpxVoiceClient_SetI3DL2Source(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $9\n\t"
      "popl %%ecx\n\t"
      "leal 0x5c(%%eax), %%edi\n\t"
      "rep movsl\n\t"
      "orb $0x80, 0x80(%%eax)\n\t"
      "cmpl $0, 0x10(%%esp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxVoiceClient_SetI3DL2Source_1\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c209e6d]\n\t"
      ".LCMcpxVoiceClient_SetI3DL2Source_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      :
      : [c209e6d] "m"(b20a241_c209e6d)
      : "memory");
}
#else
#error "CMcpxVoiceClient_SetI3DL2Source: clang naked draft required"
#endif


/* CSensaura3d_GetFullHRTFFilterPair (0x20a2f5) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void b20a2f5_c207cc8_tgt(void) { return; }
static void (*const b20a2f5_c207cc8)(void) = b20a2f5_c207cc8_tgt;
static void b20a2f5_c207cb2_tgt(void) { return; }
static void (*const b20a2f5_c207cb2)(void) = b20a2f5_c207cb2_tgt;

__attribute__((naked, noinline))
void CSensaura3d_GetFullHRTFFilterPair(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fcomps 0x2533c0\n\t"
      "pushl %%esi\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LCSensaura3d_GetFullHRTFFilterPair_1\n\t"
      "fadds 0x254644\n\t"
      "jmp .LCSensaura3d_GetFullHRTFFilterPair_2\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_1:\n\t"
      "fsubs 0x254644\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_2:\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cc8]\n\t"
      "pushl $6\n\t"
      "cdq\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%esi\n\t"
      "shll $1, %%esi\n\t"
      "cmpl $-0x5a, %%esi\n\t"
      "jl .LCSensaura3d_GetFullHRTFFilterPair_3\n\t"
      "cmpl $0x5a, %%esi\n\t"
      "jle .LCSensaura3d_GetFullHRTFFilterPair_4\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_3:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_4:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      "cdq\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%edx, %%edi\n\t"
      "pushl %%ecx\n\t"
      "subl %%edx, %%edi\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cb2]\n\t"
      "cmpl $0x5a, %%edi\n\t"
      "movl $0xb4, %%ebx\n\t"
      "jne .LCSensaura3d_GetFullHRTFFilterPair_5\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LCSensaura3d_GetFullHRTFFilterPair_9\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_5:\n\t"
      "cmpl $0x3c, %%edi\n\t"
      "pushl %%ecx\n\t"
      "jle .LCSensaura3d_GetFullHRTFFilterPair_6\n\t"
      "fadds 0x254640\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cc8]\n\t"
      "pushl $0xc\n\t"
      "cdq\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "jmp .LCSensaura3d_GetFullHRTFFilterPair_8\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_6:\n\t"
      "cmpl $0x1e, %%edi\n\t"
      "jle .LCSensaura3d_GetFullHRTFFilterPair_7\n\t"
      "fadds 0x254644\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cc8]\n\t"
      "pushl $6\n\t"
      "cdq\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $1, %%ecx\n\t"
      "jmp .LCSensaura3d_GetFullHRTFFilterPair_8\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_7:\n\t"
      "fadds 0x2533ec\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cc8]\n\t"
      "pushl $3\n\t"
      "cdq\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_8:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LCSensaura3d_GetFullHRTFFilterPair_9\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jle .LCSensaura3d_GetFullHRTFFilterPair_10\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_9:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_10:\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LCSensaura3d_GetFullHRTFFilterPair_11\n\t"
      "cmpl $0x5a, %%ecx\n\t"
      "jle .LCSensaura3d_GetFullHRTFFilterPair_11\n\t"
      "subl %%ecx, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_11:\n\t"
      "leal 0x5a(%%esi), %%eax\n\t"
      "flds 0x8(%%ebp)\n\t"
      "cdq\n\t"
      "fcomps 0x2533c0\n\t"
      "pushl $6\n\t"
      "popl %%esi\n\t"
      "idivl %%esi\n\t"
      "pushl $3\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ecx, %%eax\n\t"
      "cdq\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "popl %%edi\n\t"
      "imull $0x1f, %%eax, %%eax\n\t"
      "addl %%eax, %%esi\n\t"
      "movzwl 0x220818(,%%esi,2), %%ecx\n\t"
      "fnstsw %%ax\n\t"
      "shll $5, %%ecx\n\t"
      "popl %%esi\n\t"
      "testb $1, %%ah\n\t"
      "popl %%ebx\n\t"
      "leal 0x20f258(%%ecx), %%eax\n\t"
      "jne .LCSensaura3d_GetFullHRTFFilterPair_12\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "leal 0x20f278(%%ecx), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "jmp .LCSensaura3d_GetFullHRTFFilterPair_13\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_12:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "leal 0x20f278(%%ecx), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      ".LCSensaura3d_GetFullHRTFFilterPair_13:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c207cc8] "m"(b20a2f5_c207cc8), [c207cb2] "m"(b20a2f5_c207cb2)
      : "memory");
}
#else
#error "CSensaura3d_GetFullHRTFFilterPair: clang naked draft required"
#endif


/* CSensaura3d_GetLiteHRTFFilterPair (0x20a431) — XBE naked draft (batch 315). */
#if defined(__clang__)
static void b20a431_c207cb2_tgt(void) { return; }
static void (*const b20a431_c207cb2)(void) = b20a431_c207cb2_tgt;
static void b20a431_c207cc8_tgt(void) { return; }
static void (*const b20a431_c207cc8)(void) = b20a431_c207cc8_tgt;

__attribute__((naked, noinline))
void CSensaura3d_GetLiteHRTFFilterPair(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cb2]\n\t"
      "fadds 0x2533ec\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c207cc8]\n\t"
      "cdq\n\t"
      "pushl $3\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0xb4, %%eax\n\t"
      "jl .LCSensaura3d_GetLiteHRTFFilterPair_1\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .LCSensaura3d_GetLiteHRTFFilterPair_2\n\t"
      ".LCSensaura3d_GetLiteHRTFFilterPair_1:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LCSensaura3d_GetLiteHRTFFilterPair_2:\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LCSensaura3d_GetLiteHRTFFilterPair_3\n\t"
      "cmpl $0x5a, %%ecx\n\t"
      "jle .LCSensaura3d_GetLiteHRTFFilterPair_3\n\t"
      "movl %%eax, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      ".LCSensaura3d_GetLiteHRTFFilterPair_3:\n\t"
      "subl %%ecx, %%eax\n\t"
      "flds 0x8(%%ebp)\n\t"
      "cdq\n\t"
      "fcomps 0x2533c0\n\t"
      "pushl $3\n\t"
      "popl %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "fnstsw %%ax\n\t"
      "shll $1, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "testb $1, %%ah\n\t"
      "leal 0x2216e0(%%ecx), %%eax\n\t"
      "jne .LCSensaura3d_GetLiteHRTFFilterPair_4\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "leal 0x221700(%%ecx), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "jmp .LCSensaura3d_GetLiteHRTFFilterPair_5\n\t"
      ".LCSensaura3d_GetLiteHRTFFilterPair_4:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "leal 0x221700(%%ecx), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      ".LCSensaura3d_GetLiteHRTFFilterPair_5:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c207cb2] "m"(b20a431_c207cb2), [c207cc8] "m"(b20a431_c207cc8)
      : "memory");
}
#else
#error "CSensaura3d_GetLiteHRTFFilterPair: clang naked draft required"
#endif


/* CMcpxBuffer_GetStatus (0x20b0ac) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void b20b0ac_c2063cb_tgt(void) { return; }
static void (*const b20b0ac_c2063cb)(void) = b20b0ac_c2063cb_tgt;

__attribute__((naked, noinline))
void CMcpxBuffer_GetStatus(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0, (%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "incl %%ecx\n\t"
      "testb %%cl, 0x8(%%esi)\n\t"
      "je .LCMcpxBuffer_GetStatus_1\n\t"
      "testl $0x10000002, 0x8(%%esi)\n\t"
      "je .LCMcpxBuffer_GetStatus_1\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "testb $0x10, 0x8(%%esi)\n\t"
      "je .LCMcpxBuffer_GetStatus_1\n\t"
      "movl $5, (%%eax)\n\t"
      ".LCMcpxBuffer_GetStatus_1:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxBuffer_GetStatus_2\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxBuffer_GetStatus_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b20b0ac_c2063cb)
      : "memory");
}
#else
#error "CMcpxBuffer_GetStatus: clang naked draft required"
#endif


/* CMcpxBuffer_GetCurrentPosition (0x20b0f7) — XBE naked draft (batch 310). */
#if defined(__clang__)
static void b20b0f7_c2063cb_tgt(void) { return; }
static void (*const b20b0f7_c2063cb)(void) = b20b0f7_c2063cb_tgt;
static void b20b0f7_c209228_tgt(void) { return; }
static void (*const b20b0f7_c209228)(void) = b20b0f7_c209228_tgt;
static void b20b0f7_c207ea8_tgt(void) { return; }
static void (*const b20b0f7_c207ea8)(void) = b20b0f7_c207ea8_tgt;

__attribute__((naked, noinline))
void CMcpxBuffer_GetCurrentPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "andl $3, %%eax\n\t"
      "cmpb $3, %%al\n\t"
      "jne .LCMcpxBuffer_GetCurrentPosition_4\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c209228]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxBuffer_GetCurrentPosition_1\n\t"
      "movl %%ebx, (%%eax)\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxBuffer_GetCurrentPosition_6\n\t"
      "pushl $0x20\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c207ea8]\n\t"
      "movl 0x148(%%esi), %%ecx\n\t"
      "movl 0x10(%%ecx), %%ecx\n\t"
      "movzwl 0xc(%%ecx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jae .LCMcpxBuffer_GetCurrentPosition_2\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_2:\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "testb $0x10, 0x8(%%esi)\n\t"
      "je .LCMcpxBuffer_GetCurrentPosition_3\n\t"
      "movl 0x148(%%esi), %%ecx\n\t"
      "movl 0x50(%%ecx), %%edx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "jb .LCMcpxBuffer_GetCurrentPosition_3\n\t"
      "movl 0x54(%%ecx), %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "jae .LCMcpxBuffer_GetCurrentPosition_3\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl 0x148(%%esi), %%eax\n\t"
      "movl 0x50(%%eax), %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "jmp .LCMcpxBuffer_GetCurrentPosition_6\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_3:\n\t"
      "movl 0x148(%%esi), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl 0x4c(%%ecx)\n\t"
      "movl %%edx, (%%edi)\n\t"
      "jmp .LCMcpxBuffer_GetCurrentPosition_6\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxBuffer_GetCurrentPosition_5\n\t"
      "movl 0x228(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LCMcpxBuffer_GetCurrentPosition_6\n\t"
      "movl 0x228(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_6:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxBuffer_GetCurrentPosition_7\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxBuffer_GetCurrentPosition_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b20b0f7_c2063cb), [c209228] "m"(b20b0f7_c209228), [c207ea8] "m"(b20b0f7_c207ea8)
      : "memory");
}
#else
#error "CMcpxBuffer_GetCurrentPosition: clang naked draft required"
#endif


/* CMcpxBuffer_Stop (0x20b873) — XBE naked draft (batch 353). */
#if defined(__clang__)
static void b20b873_c20af28_tgt(void) { return; }
static void (*const b20b873_c20af28)(void) = b20b873_c20af28_tgt;
static void b20b873_c20b3e6_tgt(void) { return; }
static void (*const b20b873_c20b3e6)(void) = b20b873_c20b3e6_tgt;

__attribute__((naked, noinline))
void CMcpxBuffer_Stop(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "orl 0x10(%%esp), %%eax\n\t"
      "movl %%ecx, %%esi\n\t"
      "je .LCMcpxBuffer_Stop_1\n\t"
      "pushl %%edi\n\t"
      "pushl 0x14(%%esp)\n\t"
      "pushl 0x14(%%esp)\n\t"
      "pushl $3\n\t"
      "call *%[c20af28]\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LCMcpxBuffer_Stop_2\n\t"
      ".LCMcpxBuffer_Stop_1:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20b3e6]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxBuffer_Stop_2:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20af28] "m"(b20b873_c20af28), [c20b3e6] "m"(b20b873_c20b3e6)
      : "memory");
}
#else
#error "CMcpxBuffer_Stop: clang naked draft required"
#endif


/* CMcpxBuffer_SetCurrentPosition (0x20b8d7) — XBE naked draft (batch 310). */
#if defined(__clang__)
static void b20b8d7_c20b4cc_tgt(void) { return; }
static void (*const b20b8d7_c20b4cc)(void) = b20b8d7_c20b4cc_tgt;
static void b20b8d7_c2082fe_tgt(void) { return; }
static void (*const b20b8d7_c2082fe)(void) = b20b8d7_c2082fe_tgt;
static void b20b8d7_c20af03_tgt(void) { return; }
static void (*const b20b8d7_c20af03)(void) = b20b8d7_c20af03_tgt;
static void b20b8d7_c2063cb_tgt(void) { return; }
static void (*const b20b8d7_c2063cb)(void) = b20b8d7_c2063cb_tgt;

__attribute__((naked, noinline))
void CMcpxBuffer_SetCurrentPosition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "andl $3, %%eax\n\t"
      "cmpb $3, %%al\n\t"
      "jne .LCMcpxBuffer_SetCurrentPosition_6\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "andl $0x13, %%eax\n\t"
      "cmpb $0x13, %%al\n\t"
      "jne .LCMcpxBuffer_SetCurrentPosition_1\n\t"
      "movl 0x148(%%esi), %%eax\n\t"
      "movl 0x54(%%eax), %%ecx\n\t"
      "addl 0x50(%%eax), %%ecx\n\t"
      "cmpl %%ecx, 0x8(%%ebp)\n\t"
      "jb .LCMcpxBuffer_SetCurrentPosition_1\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20b4cc]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LCMcpxBuffer_SetCurrentPosition_7\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_1:\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c2082fe]\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20af03]\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c2063cb]\n\t"
      "movl 0xe0(%%esi), %%eax\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movzwl 0x2(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "je .LCMcpxBuffer_SetCurrentPosition_4\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_2:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxBuffer_SetCurrentPosition_2\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, 0xfe8202f8\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_3:\n\t"
      "cmpl $4, 0xfe820010\n\t"
      "jb .LCMcpxBuffer_SetCurrentPosition_3\n\t"
      "movl %%edi, 0xfe8203d8\n\t"
      "movl 0xe0(%%esi), %%edx\n\t"
      "movl 0x10(%%edx), %%edx\n\t"
      "movzwl 0x2(%%edx), %%edx\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "decl %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jb .LCMcpxBuffer_SetCurrentPosition_2\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_4:\n\t"
      "cmpl $0, -0xc(%%ebp)\n\t"
      "popl %%edi\n\t"
      "je .LCMcpxBuffer_SetCurrentPosition_5\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_5:\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c2082fe]\n\t"
      "jmp .LCMcpxBuffer_SetCurrentPosition_7\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x228(%%esi)\n\t"
      ".LCMcpxBuffer_SetCurrentPosition_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c20b4cc] "m"(b20b8d7_c20b4cc), [c2082fe] "m"(b20b8d7_c2082fe), [c20af03] "m"(b20b8d7_c20af03), [c2063cb] "m"(b20b8d7_c2063cb)
      : "memory");
}
#else
#error "CMcpxBuffer_SetCurrentPosition: clang naked draft required"
#endif


/* CMcpxBuffer_SetBufferData (0x20ba90) — XBE naked draft (batch 368). */
#if defined(__clang__)


__attribute__((naked, noinline))
void CMcpxBuffer_SetBufferData(void)
{
  __asm__ volatile(
      "movl 0x148(%%ecx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb $4, 0xe(%%edx)\n\t"
      "jne .LCMcpxBuffer_SetBufferData_1\n\t"
      ".byte 0xe9, 0xf0, 0xf9, 0xff, 0xff\n\t"
      ".LCMcpxBuffer_SetBufferData_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "CMcpxBuffer_SetBufferData: clang naked draft required"
#endif


/* CMcpxBuffer_Play (0x20baa4) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void b20baa4_c20af28_tgt(void) { return; }
static void (*const b20baa4_c20af28)(void) = b20baa4_c20af28_tgt;
static void b20baa4_c20b4cc_tgt(void) { return; }
static void (*const b20baa4_c20b4cc)(void) = b20baa4_c20b4cc_tgt;

__attribute__((naked, noinline))
void CMcpxBuffer_Play(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "orl 0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, %%esi\n\t"
      "je .LCMcpxBuffer_Play_1\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl $2\n\t"
      "call *%[c20af28]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LCMcpxBuffer_Play_2\n\t"
      ".LCMcpxBuffer_Play_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20b4cc]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LCMcpxBuffer_Play_2:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c20af28] "m"(b20baa4_c20af28), [c20b4cc] "m"(b20baa4_c20b4cc)
      : "memory");
}
#else
#error "CMcpxBuffer_Play: clang naked draft required"
#endif


/* CMcpxStream_Pause (0x20c050) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void b20c050_c2063cb_tgt(void) { return; }
static void (*const b20c050_c2063cb)(void) = b20c050_c2063cb_tgt;
static void b20c050_c2082fe_tgt(void) { return; }
static void (*const b20c050_c2082fe)(void) = b20c050_c2082fe_tgt;

__attribute__((naked, noinline))
void CMcpxStream_Pause(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "cmpl $1, 0x8(%%ebp)\n\t"
      "jne .LCMcpxStream_Pause_1\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "orl $4, %%eax\n\t"
      "jmp .LCMcpxStream_Pause_2\n\t"
      ".LCMcpxStream_Pause_1:\n\t"
      "cmpl $0, 0x8(%%ebp)\n\t"
      "jne .LCMcpxStream_Pause_3\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".LCMcpxStream_Pause_2:\n\t"
      "movl %%esi, %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2082fe]\n\t"
      ".LCMcpxStream_Pause_3:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "je .LCMcpxStream_Pause_4\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxStream_Pause_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b20c050_c2063cb), [c2082fe] "m"(b20c050_c2082fe)
      : "memory");
}
#else
#error "CMcpxStream_Pause: clang naked draft required"
#endif


/* CMcpxStream_Flush (0x20c3fe) — XBE naked draft (batch 315). */
#if defined(__clang__)
static void b20c3fe_c2063cb_tgt(void) { return; }
static void (*const b20c3fe_c2063cb)(void) = b20c3fe_c2063cb_tgt;
static void b20c3fe_c20bbca_tgt(void) { return; }
static void (*const b20c3fe_c20bbca)(void) = b20c3fe_c20bbca_tgt;
static void b20c3fe_c2082ee_tgt(void) { return; }
static void (*const b20c3fe_c2082ee)(void) = b20c3fe_c2082ee_tgt;
static void b20c3fe_c20c3a7_tgt(void) { return; }
static void (*const b20c3fe_c20c3a7)(void) = b20c3fe_c20c3a7_tgt;
static void b20c3fe_c20c299_tgt(void) { return; }
static void (*const b20c3fe_c20c299)(void) = b20c3fe_c20c299_tgt;
static void b20c3fe_c20c098_tgt(void) { return; }
static void (*const b20c3fe_c20c098)(void) = b20c3fe_c20c098_tgt;
static void b20c3fe_c20c37c_tgt(void) { return; }
static void (*const b20c3fe_c20c37c)(void) = b20c3fe_c20c37c_tgt;

__attribute__((naked, noinline))
void CMcpxStream_Flush(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "testb $1, 0x8(%%esi)\n\t"
      "je .LCMcpxStream_Flush_5\n\t"
      "testb $2, 0x8(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "je .LCMcpxStream_Flush_2\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LCMcpxStream_Flush_1:\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20bbca]\n\t"
      "incl %%edi\n\t"
      "cmpl $3, %%edi\n\t"
      "jb .LCMcpxStream_Flush_1\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *0x10(%%eax)\n\t"
      "cmpl %%ebx, -0x8(%%ebp)\n\t"
      "je .LCMcpxStream_Flush_2\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxStream_Flush_2:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c2082ee]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl $0x80004004, %%edi\n\t"
      ".LCMcpxStream_Flush_3:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20c3a7]\n\t"
      "incl %%ebx\n\t"
      "cmpl $2, %%ebx\n\t"
      "jb .LCMcpxStream_Flush_3\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "leal 0x178(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20c299]\n\t"
      "movl 0x148(%%esi), %%eax\n\t"
      "andl $0, 0x218(%%esi)\n\t"
      "testb $4, 0xe(%%eax)\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LCMcpxStream_Flush_4\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20c098]\n\t"
      ".LCMcpxStream_Flush_4:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20c37c]\n\t"
      ".LCMcpxStream_Flush_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b20c3fe_c2063cb), [c20bbca] "m"(b20c3fe_c20bbca), [c2082ee] "m"(b20c3fe_c2082ee), [c20c3a7] "m"(b20c3fe_c20c3a7), [c20c299] "m"(b20c3fe_c20c299), [c20c098] "m"(b20c3fe_c20c098), [c20c37c] "m"(b20c3fe_c20c37c)
      : "memory");
}
#else
#error "CMcpxStream_Flush: clang naked draft required"
#endif


/* CMcpxStream_Discontinuity (0x20c752) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void b20c752_c2063cb_tgt(void) { return; }
static void (*const b20c752_c2063cb)(void) = b20c752_c2063cb_tgt;
static void (*const b20c752_c20c3fe)(void) = CMcpxStream_Flush;

__attribute__((naked, noinline))
void CMcpxStream_Discontinuity(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "andl $3, %%eax\n\t"
      "cmpb $3, %%al\n\t"
      "jne .LCMcpxStream_Discontinuity_7\n\t"
      "pushl %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "call *%[c2063cb]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal 0x178(%%esi), %%eax\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "sete %%cl\n\t"
      "movl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LCMcpxStream_Discontinuity_4\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal 0x160(%%esi), %%eax\n\t"
      ".LCMcpxStream_Discontinuity_1:\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LCMcpxStream_Discontinuity_2\n\t"
      "incl %%ecx\n\t"
      "addl $0x10, %%eax\n\t"
      "cmpl $2, %%ecx\n\t"
      "jb .LCMcpxStream_Discontinuity_1\n\t"
      "jmp .LCMcpxStream_Discontinuity_3\n\t"
      ".LCMcpxStream_Discontinuity_2:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LCMcpxStream_Discontinuity_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LCMcpxStream_Discontinuity_5\n\t"
      ".LCMcpxStream_Discontinuity_4:\n\t"
      "orl $0x20, 0x8(%%esi)\n\t"
      ".LCMcpxStream_Discontinuity_5:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "je .LCMcpxStream_Discontinuity_6\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      ".LCMcpxStream_Discontinuity_6:\n\t"
      "testl %%edi, %%edi\n\t"
      "popl %%edi\n\t"
      "je .LCMcpxStream_Discontinuity_7\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c20c3fe]\n\t"
      ".LCMcpxStream_Discontinuity_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c2063cb] "m"(b20c752_c2063cb), [c20c3fe] "m"(b20c752_c20c3fe)
      : "memory");
}
#else
#error "CMcpxStream_Discontinuity: clang naked draft required"
#endif


/* XAudioCalculatePitch (0x20c857) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void b20c857_c207dd4_tgt(void) { return; }
static void (*const b20c857_c207dd4)(void) = b20c857_c207dd4_tgt;
static void b20c857_c20c7ed_tgt(void) { return; }
static void (*const b20c857_c20c7ed)(void) = b20c857_c20c7ed_tgt;
static void b20c857_c207df9_tgt(void) { return; }
static void (*const b20c857_c207df9)(void) = b20c857_c207df9_tgt;

__attribute__((naked, noinline))
void XAudioCalculatePitch(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl $0xbb80, %%esi\n\t"
      "jne .LXAudioCalculatePitch_1\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LXAudioCalculatePitch_4\n\t"
      ".LXAudioCalculatePitch_1:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LXAudioCalculatePitch_2\n\t"
      "movl $0xffff8001, %%esi\n\t"
      "jmp .LXAudioCalculatePitch_4\n\t"
      ".LXAudioCalculatePitch_2:\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "call *%[c207dd4]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "jge .LXAudioCalculatePitch_3\n\t"
      "fadds 0x25fb8c\n\t"
      ".LXAudioCalculatePitch_3:\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c20c7ed]\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c207df9]\n\t"
      ".LXAudioCalculatePitch_4:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c207dd4] "m"(b20c857_c207dd4), [c20c7ed] "m"(b20c857_c20c7ed), [c207df9] "m"(b20c857_c207df9)
      : "memory");
}
#else
#error "XAudioCalculatePitch: clang naked draft required"
#endif


/* XAudioCreatePcmFormat (0x20ca62) — XBE naked draft (batch 344). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XAudioCreatePcmFormat(void)
{
  __asm__ volatile(
      "movl 0x10(%%esp), %%ecx\n\t"
      "movw 0x4(%%esp), %%ax\n\t"
      "movw 0xc(%%esp), %%dx\n\t"
      "movw %%ax, 0x2(%%ecx)\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movw %%dx, 0xe(%%ecx)\n\t"
      "movzwl %%dx, %%edx\n\t"
      "imull %%edx, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $8\n\t"
      "cdq\n\t"
      "popl %%edi\n\t"
      "idivl %%edi\n\t"
      "movl 0x10(%%esp), %%esi\n\t"
      "andw $0, 0x10(%%ecx)\n\t"
      "popl %%edi\n\t"
      "movl %%esi, 0x4(%%ecx)\n\t"
      "movw $1, (%%ecx)\n\t"
      "movw %%ax, 0xc(%%ecx)\n\t"
      "movzwl %%ax, %%eax\n\t"
      "imull %%esi, %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XAudioCreatePcmFormat: clang naked draft required"
#endif


/* XAudioCreateAdpcmFormat (0x20caac) — XBE naked draft (batch 358). */
#if defined(__clang__)
static void b20caac_c20c959_tgt(void) { return; }
static void (*const b20caac_c20c959)(void) = b20caac_c20c959_tgt;

__attribute__((naked, noinline))
void XAudioCreateAdpcmFormat(void)
{
  __asm__ volatile(
      "movl 0xc(%%esp), %%edx\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "movw $0x69, (%%edx)\n\t"
      "movw %%ax, 0x2(%%edx)\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movw $4, 0xe(%%edx)\n\t"
      "call *%[c20c959]\n\t"
      "movw %%ax, 0xc(%%edx)\n\t"
      "movzwl %%ax, %%eax\n\t"
      "imull %%esi, %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movw $2, 0x10(%%edx)\n\t"
      "movw $0x40, 0x12(%%edx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c20c959] "m"(b20caac_c20c959)
      : "memory");
}
#else
#error "XAudioCreateAdpcmFormat: clang naked draft required"
#endif


/* IsValidFormat (0x20cbad) — XBE naked draft (batch 334). */
#if defined(__clang__)
static void b20cbad_c20c9f8_tgt(void) { return; }
static void (*const b20cbad_c20c9f8)(void) = b20cbad_c20c9f8_tgt;
static void b20cbad_c20c983_tgt(void) { return; }
static void (*const b20cbad_c20c983)(void) = b20cbad_c20c983_tgt;

__attribute__((naked, noinline))
void IsValidFormat(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%ecx\n\t"
      "movzwl (%%ecx), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LIsValidFormat_2\n\t"
      "subl $0x68, %%eax\n\t"
      "je .LIsValidFormat_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LIsValidFormat_3\n\t"
      ".LIsValidFormat_1:\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20c9f8]\n\t"
      "jmp .LIsValidFormat_3\n\t"
      ".LIsValidFormat_2:\n\t"
      "pushl %%ecx\n\t"
      "call *%[c20c983]\n\t"
      ".LIsValidFormat_3:\n\t"
      "ret\n\t"
      :
      : [c20c9f8] "m"(b20cbad_c20c9f8), [c20c983] "m"(b20cbad_c20c983)
      : "memory");
}
#else
#error "IsValidFormat: clang naked draft required"
#endif


/* 0x002235c4 */
void GetLastError(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* ioctlsocket (0x223be7) — XBE naked draft (batch 345). */
#if defined(__clang__)
static void __stdcall (*const b223be7_c1d2268)(unsigned int error) = (void *)SetLastError;
static void b223be7_c22361e_tgt(void) { return; }
static void (*const b223be7_c22361e)(void) = b223be7_c22361e_tgt;
static void b223be7_c2236be_tgt(void) { return; }
static void (*const b223be7_c2236be)(void) = b223be7_c2236be_tgt;

__attribute__((naked, noinline))
void ioctlsocket(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Lioctlsocket_1\n\t"
      "cmpl %%ebx, 0x964(%%ecx)\n\t"
      "jg .Lioctlsocket_2\n\t"
      ".Lioctlsocket_1:\n\t"
      "pushl $0x276d\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lioctlsocket_13\n\t"
      ".Lioctlsocket_2:\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c22361e]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lioctlsocket_4\n\t"
      ".Lioctlsocket_3:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lioctlsocket_12\n\t"
      ".Lioctlsocket_4:\n\t"
      "cmpl $0x8004667e, 0xc(%%ebp)\n\t"
      "je .Lioctlsocket_9\n\t"
      "cmpl $0x4004667f, 0xc(%%ebp)\n\t"
      "je .Lioctlsocket_5\n\t"
      "movl $0x273a, %%ebx\n\t"
      "jmp .Lioctlsocket_10\n\t"
      ".Lioctlsocket_5:\n\t"
      "pushl %%edi\n\t"
      "call *0x2531b4\n\t"
      "testb $2, 0xc(%%esi)\n\t"
      "jne .Lioctlsocket_7\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jne .Lioctlsocket_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .Lioctlsocket_8\n\t"
      ".Lioctlsocket_6:\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lioctlsocket_8\n\t"
      "incl %%edx\n\t"
      "jmp .Lioctlsocket_8\n\t"
      ".Lioctlsocket_7:\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      ".Lioctlsocket_8:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movb %%al, %%cl\n\t"
      "call *0x2531b0\n\t"
      "popl %%edi\n\t"
      "jmp .Lioctlsocket_10\n\t"
      ".Lioctlsocket_9:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "movl $0x20000, %%eax\n\t"
      "andl %%eax, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xfffdffff\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c2236be]\n\t"
      ".Lioctlsocket_10:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl $0x2b434f53, 0x8(%%esi)\n\t"
      "je .Lioctlsocket_11\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .Lioctlsocket_3\n\t"
      ".Lioctlsocket_11:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lioctlsocket_12:\n\t"
      "popl %%esi\n\t"
      ".Lioctlsocket_13:\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b223be7_c1d2268), [c22361e] "m"(b223be7_c22361e), [c2236be] "m"(b223be7_c2236be)
      : "memory");
}
#else
#error "ioctlsocket: clang naked draft required"
#endif


/* listen (0x2240c3) — XBE naked draft (batch 353). */
#if defined(__clang__)
static void __stdcall (*const b2240c3_c1d2268)(unsigned int error) = (void *)SetLastError;
static void b2240c3_c22361e_tgt(void) { return; }
static void (*const b2240c3_c22361e)(void) = b2240c3_c22361e_tgt;
static void b2240c3_c22a590_tgt(void) { return; }
static void (*const b2240c3_c22a590)(void) = b2240c3_c22a590_tgt;

__attribute__((naked, noinline))
void listen(void)
{
  __asm__ volatile(
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Llisten_1\n\t"
      "cmpl $0, 0x964(%%edi)\n\t"
      "jg .Llisten_2\n\t"
      ".Llisten_1:\n\t"
      "pushl $0x276d\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Llisten_11\n\t"
      ".Llisten_2:\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c22361e]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Llisten_4\n\t"
      ".Llisten_3:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Llisten_10\n\t"
      ".Llisten_4:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testb $0x20, %%al\n\t"
      "je .Llisten_5\n\t"
      "movl $0x2748, %%eax\n\t"
      "jmp .Llisten_8\n\t"
      ".Llisten_5:\n\t"
      "testb $0x10, %%al\n\t"
      "jne .Llisten_6\n\t"
      "movl $0x2726, %%eax\n\t"
      "jmp .Llisten_8\n\t"
      ".Llisten_6:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c22a590]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Llisten_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Llisten_8\n\t"
      ".Llisten_7:\n\t"
      "pushl %%eax\n\t"
      "call *0x2531d0\n\t"
      ".Llisten_8:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x2b434f53, 0x8(%%esi)\n\t"
      "je .Llisten_9\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .Llisten_3\n\t"
      ".Llisten_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Llisten_10:\n\t"
      "popl %%esi\n\t"
      ".Llisten_11:\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b2240c3_c1d2268), [c22361e] "m"(b2240c3_c22361e), [c22a590] "m"(b2240c3_c22a590)
      : "memory");
}
#else
#error "listen: clang naked draft required"
#endif


/* bind (0x224881) — XBE naked draft (batch 340). */
#if defined(__clang__)
static void b224881_c22361e_tgt(void) { return; }
static void (*const b224881_c22361e)(void) = b224881_c22361e_tgt;
static void b224881_c223faa_tgt(void) { return; }
static void (*const b224881_c223faa)(void) = b224881_c223faa_tgt;
static void __stdcall (*const b224881_c1d2268)(unsigned int error) = (void *)SetLastError;

__attribute__((naked, noinline))
int bind(void *xnet __attribute__((unused)), unsigned int socket __attribute__((unused)), const void *name __attribute__((unused)), int namelen __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lbind_1\n\t"
      "cmpl $0, 0x964(%%edi)\n\t"
      "jg .Lbind_2\n\t"
      ".Lbind_1:\n\t"
      "pushl $0x276d\n\t"
      "jmp .Lbind_7\n\t"
      ".Lbind_2:\n\t"
      "pushl 0xc(%%esp)\n\t"
      "call *%[c22361e]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lbind_8\n\t"
      "testb $0x10, 0xc(%%esi)\n\t"
      "je .Lbind_3\n\t"
      "movl $0x2726, %%eax\n\t"
      "jmp .Lbind_6\n\t"
      ".Lbind_3:\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "cmpl $0, 0x4(%%ecx)\n\t"
      "je .Lbind_4\n\t"
      "movl $0x2741, %%eax\n\t"
      "jmp .Lbind_6\n\t"
      ".Lbind_4:\n\t"
      "pushl %%ecx\n\t"
      "movw 0x2(%%ecx), %%cx\n\t"
      "movl %%esp, %%eax\n\t"
      "movw %%cx, (%%eax)\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c223faa]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lbind_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lbind_6\n\t"
      ".Lbind_5:\n\t"
      "pushl %%eax\n\t"
      "call *0x2531d0\n\t"
      ".Lbind_6:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x2b434f53, 0x8(%%esi)\n\t"
      "je .Lbind_9\n\t"
      "pushl %%eax\n\t"
      ".Lbind_7:\n\t"
      "call *%[c1d2268]\n\t"
      ".Lbind_8:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lbind_10\n\t"
      ".Lbind_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lbind_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c22361e] "m"(b224881_c22361e), [c223faa] "m"(b224881_c223faa), [c1d2268] "m"(b224881_c1d2268)
      : "memory");
}
#else
#error "bind: clang naked draft required"
#endif


/* connect (0x224904) — XBE naked draft (batch 357). */
#if defined(__clang__)
static void __stdcall (*const b224904_c1d2268)(unsigned int error) = (void *)SetLastError;
static void b224904_c22361e_tgt(void) { return; }
static void (*const b224904_c22361e)(void) = b224904_c22361e_tgt;
static void b224904_c22c6b8_tgt(void) { return; }
static void (*const b224904_c22c6b8)(void) = b224904_c22c6b8_tgt;
static void b224904_c22bde3_tgt(void) { return; }
static void (*const b224904_c22bde3)(void) = b224904_c22bde3_tgt;
static void b224904_c224326_tgt(void) { return; }
static void (*const b224904_c224326)(void) = b224904_c224326_tgt;
static void b224904_c2236be_tgt(void) { return; }
static void (*const b224904_c2236be)(void) = b224904_c2236be_tgt;

__attribute__((naked, noinline))
int connect(void *xnet __attribute__((unused)), unsigned int socket __attribute__((unused)), const void *name __attribute__((unused)), int namelen __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "je .Lconnect_1\n\t"
      "cmpl %%esi, 0x964(%%ebx)\n\t"
      "jg .Lconnect_2\n\t"
      ".Lconnect_1:\n\t"
      "pushl $0x276d\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lconnect_13\n\t"
      ".Lconnect_2:\n\t"
      "pushl %%edi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c22361e]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .Lconnect_4\n\t"
      ".Lconnect_3:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lconnect_12\n\t"
      ".Lconnect_4:\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "testb $0x20, %%dl\n\t"
      "je .Lconnect_5\n\t"
      "testb $2, %%dl\n\t"
      "je .Lconnect_5\n\t"
      "movl $0x2748, %%eax\n\t"
      "jmp .Lconnect_8\n\t"
      ".Lconnect_5:\n\t"
      "testb $2, %%dl\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movw 0x2(%%ecx), %%cx\n\t"
      "movw %%cx, 0x8(%%ebp)\n\t"
      "movl %%ebx, %%ecx\n\t"
      "jne .Lconnect_6\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c22c6b8]\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .Lconnect_10\n\t"
      ".Lconnect_6:\n\t"
      "testl $0x20000, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "je .Lconnect_9\n\t"
      "call *%[c22bde3]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .Lconnect_7\n\t"
      "movl $0x80072733, %%esi\n\t"
      ".Lconnect_7:\n\t"
      "pushl %%esi\n\t"
      "call *0x2531d0\n\t"
      ".Lconnect_8:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x2b434f53, 0x8(%%edi)\n\t"
      "je .Lconnect_11\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .Lconnect_3\n\t"
      ".Lconnect_9:\n\t"
      "call *%[c22bde3]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .Lconnect_7\n\t"
      "pushl $0\n\t"
      "pushl $0x2000\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c224326]\n\t"
      "pushl $0x80\n\t"
      "pushl $-1\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c2236be]\n\t"
      ".Lconnect_10:\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .Lconnect_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lconnect_8\n\t"
      ".Lconnect_11:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lconnect_12:\n\t"
      "popl %%edi\n\t"
      ".Lconnect_13:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b224904_c1d2268), [c22361e] "m"(b224904_c22361e), [c22c6b8] "m"(b224904_c22c6b8), [c22bde3] "m"(b224904_c22bde3), [c224326] "m"(b224904_c224326), [c2236be] "m"(b224904_c2236be)
      : "memory");
}
#else
#error "connect: clang naked draft required"
#endif


/* socket (0x225021) — XBE naked draft (batch 335). */
#if defined(__clang__)
static void __stdcall (*const b225021_c1d2268)(unsigned int error) = (void *)SetLastError;
static void b225021_c224493_tgt(void) { return; }
static void (*const b225021_c224493)(void) = b225021_c224493_tgt;
static void b225021_c2236be_tgt(void) { return; }
static void (*const b225021_c2236be)(void) = b225021_c2236be_tgt;

__attribute__((naked, noinline))
int socket(void *xnet __attribute__((unused)), int af __attribute__((unused)), int type __attribute__((unused)), int protocol __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lsocket_1\n\t"
      "cmpl $0, 0x964(%%edi)\n\t"
      "jg .Lsocket_2\n\t"
      ".Lsocket_1:\n\t"
      "pushl $0x276d\n\t"
      "jmp .Lsocket_10\n\t"
      ".Lsocket_2:\n\t"
      "cmpl $0, 0x8(%%esp)\n\t"
      "je .Lsocket_3\n\t"
      "cmpl $2, 0x8(%%esp)\n\t"
      "je .Lsocket_3\n\t"
      "movl $0x273f, %%eax\n\t"
      "jmp .Lsocket_9\n\t"
      ".Lsocket_3:\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lsocket_4\n\t"
      "cmpl $1, %%ecx\n\t"
      "je .Lsocket_4\n\t"
      "cmpl $2, %%ecx\n\t"
      "je .Lsocket_4\n\t"
      "movl $0x273c, %%eax\n\t"
      "jmp .Lsocket_9\n\t"
      ".Lsocket_4:\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsocket_5\n\t"
      "cmpl $6, %%eax\n\t"
      "je .Lsocket_5\n\t"
      "cmpl $0x11, %%eax\n\t"
      "jne .Lsocket_8\n\t"
      ".Lsocket_5:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .Lsocket_6\n\t"
      "cmpl $0x11, %%eax\n\t"
      "sete %%cl\n\t"
      "incl %%ecx\n\t"
      ".Lsocket_6:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsocket_7\n\t"
      "cmpl $2, %%ecx\n\t"
      "setne %%al\n\t"
      "decl %%eax\n\t"
      "andl $0xb, %%eax\n\t"
      "addl $6, %%eax\n\t"
      ".Lsocket_7:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl $1, %%ecx\n\t"
      "sete %%dl\n\t"
      "movl %%edx, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl $6, %%eax\n\t"
      "sete %%dl\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .Lsocket_11\n\t"
      ".Lsocket_8:\n\t"
      "movl $0x273b, %%eax\n\t"
      ".Lsocket_9:\n\t"
      "pushl %%eax\n\t"
      ".Lsocket_10:\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lsocket_14\n\t"
      ".Lsocket_11:\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c224493]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsocket_12\n\t"
      "pushl $0x2747\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lsocket_13\n\t"
      ".Lsocket_12:\n\t"
      "pushl %%ebx\n\t"
      "call *0x2531b4\n\t"
      "pushl $0x1000000\n\t"
      "pushl $-1\n\t"
      "movl %%esi, %%ecx\n\t"
      "movb %%al, %%bl\n\t"
      "call *%[c2236be]\n\t"
      "leal 0x96c(%%edi), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movb %%bl, %%cl\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "call *0x2531b0\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%ebx\n\t"
      ".Lsocket_13:\n\t"
      "popl %%esi\n\t"
      ".Lsocket_14:\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b225021_c1d2268), [c224493] "m"(b225021_c224493), [c2236be] "m"(b225021_c2236be)
      : "memory");
}
#else
#error "socket: clang naked draft required"
#endif


/* recv (0x2256bb) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void __stdcall (*const b2256bb_c1d2268)(unsigned int error) = (void *)SetLastError;
static void b2256bb_c22361e_tgt(void) { return; }
static void (*const b2256bb_c22361e)(void) = b2256bb_c22361e_tgt;
static void b2256bb_c22530d_tgt(void) { return; }
static void (*const b2256bb_c22530d)(void) = b2256bb_c22530d_tgt;

__attribute__((naked, noinline))
int recv(void *xnet __attribute__((unused)), unsigned int socket __attribute__((unused)), char *buf __attribute__((unused)), int len __attribute__((unused)), int flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lrecv_1\n\t"
      "cmpl $0, 0x964(%%edi)\n\t"
      "jg .Lrecv_2\n\t"
      ".Lrecv_1:\n\t"
      "pushl $0x276d\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lrecv_9\n\t"
      ".Lrecv_2:\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c22361e]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrecv_4\n\t"
      ".Lrecv_3:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lrecv_8\n\t"
      ".Lrecv_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "andl $0, -0x18(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c22530d]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lrecv_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrecv_6\n\t"
      ".Lrecv_5:\n\t"
      "pushl %%eax\n\t"
      "call *0x2531d0\n\t"
      ".Lrecv_6:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x2b434f53, 0x8(%%esi)\n\t"
      "je .Lrecv_7\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .Lrecv_3\n\t"
      ".Lrecv_7:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".Lrecv_8:\n\t"
      "popl %%esi\n\t"
      ".Lrecv_9:\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b2256bb_c1d2268), [c22361e] "m"(b2256bb_c22361e), [c22530d] "m"(b2256bb_c22530d)
      : "memory");
}
#else
#error "recv: clang naked draft required"
#endif


/* send (0x2258a4) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void __stdcall (*const b2258a4_c1d2268)(unsigned int error) = (void *)SetLastError;
static void b2258a4_c22361e_tgt(void) { return; }
static void (*const b2258a4_c22361e)(void) = b2258a4_c22361e_tgt;
static void b2258a4_c2254cd_tgt(void) { return; }
static void (*const b2258a4_c2254cd)(void) = b2258a4_c2254cd_tgt;

__attribute__((naked, noinline))
int send(void *xnet __attribute__((unused)), unsigned int socket __attribute__((unused)), const char *buf __attribute__((unused)), int len __attribute__((unused)), int flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lsend_1\n\t"
      "cmpl $0, 0x964(%%edi)\n\t"
      "jg .Lsend_2\n\t"
      ".Lsend_1:\n\t"
      "pushl $0x276d\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lsend_9\n\t"
      ".Lsend_2:\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c22361e]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsend_4\n\t"
      ".Lsend_3:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .Lsend_8\n\t"
      ".Lsend_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "andl $0, -0x1c(%%ebp)\n\t"
      "andl $0, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%ecx\n\t"
      "movw $1, -0x14(%%ebp)\n\t"
      "call *%[c2254cd]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lsend_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lsend_6\n\t"
      ".Lsend_5:\n\t"
      "pushl %%eax\n\t"
      "call *0x2531d0\n\t"
      ".Lsend_6:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x2b434f53, 0x8(%%esi)\n\t"
      "je .Lsend_7\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .Lsend_3\n\t"
      ".Lsend_7:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      ".Lsend_8:\n\t"
      "popl %%esi\n\t"
      ".Lsend_9:\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b2258a4_c1d2268), [c22361e] "m"(b2258a4_c22361e), [c2254cd] "m"(b2258a4_c2254cd)
      : "memory");
}
#else
#error "send: clang naked draft required"
#endif


/* MU_Init (0x24b4e4) — XBE naked draft (batch 306). */
#if defined(__clang__)
static void b24b4e4_c24b75b_tgt(void) { return; }
static void (*const b24b4e4_c24b75b)(void) = b24b4e4_c24b75b_tgt;
static void (*const b24b4e4_c24b724)(void) = IUsbInit_GetMaxDeviceTypeCount;
static void b24b4e4_c24c4d3_tgt(void) { return; }
static void (*const b24b4e4_c24c4d3)(void) = b24b4e4_c24c4d3_tgt;
static void b24b4e4_c24b76e_tgt(void) { return; }
static void (*const b24b4e4_c24b76e)(void) = b24b4e4_c24b76e_tgt;

__attribute__((naked, noinline))
void MU_Init(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0xc04, %%ecx\n\t"
      "movl $0x4eb0b8, %%edi\n\t"
      "rep stosl\n\t"
      "movl $0x4eb0bc, %%eax\n\t"
      "pushl $0x60\n\t"
      "movl %%eax, 0x4eb0c0\n\t"
      "movl %%eax, 0x4eb0bc\n\t"
      "call *0x2531bc\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x18\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, 0x4ee0c4\n\t"
      "rep stosl\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "call *%[c24b75b]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LMU_Init_1\n\t"
      "movl $8, -0x8(%%ebp)\n\t"
      "jmp .LMU_Init_2\n\t"
      ".LMU_Init_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x24b218\n\t"
      "call *%[c24b724]\n\t"
      "pushl $8\n\t"
      "popl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jbe .LMU_Init_2\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LMU_Init_2:\n\t"
      "pushl $0x253024\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, -0x8(%%ebp)\n\t"
      "jbe .LMU_Init_5\n\t"
      ".LMU_Init_3:\n\t"
      "cmpl $9, %%esi\n\t"
      "leal 0x41(%%esi), %%eax\n\t"
      "ja .LMU_Init_4\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      ".LMU_Init_4:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movb %%al, 0xb(%%ecx)\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x3a\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x170\n\t"
      "pushl $0x24b250\n\t"
      "call *0x2531b8\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LMU_Init_5\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x18(%%eax), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl $0x5c\n\t"
      "popl %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "rep stosl\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl $4, 0xc(%%edx)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb $1, 0x1e(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "orl $4, 0x14(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0xffffffef, 0x14(%%eax)\n\t"
      "pushl %%edx\n\t"
      "call *%[c24c4d3]\n\t"
      "incl %%esi\n\t"
      "cmpl -0x8(%%ebp), %%esi\n\t"
      "jb .LMU_Init_3\n\t"
      ".LMU_Init_5:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x24b241\n\t"
      "popl %%esi\n\t"
      "jbe .LMU_Init_6\n\t"
      "shll $1, 0x24b247\n\t"
      ".LMU_Init_6:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x24b240\n\t"
      "call *%[c24b76e]\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c24b75b] "m"(b24b4e4_c24b75b), [c24b724] "m"(b24b4e4_c24b724), [c24c4d3] "m"(b24b4e4_c24c4d3), [c24b76e] "m"(b24b4e4_c24b76e)
      : "memory");
}
#else
#error "MU_Init: clang naked draft required"
#endif


/* IUsbInit_GetMaxDeviceTypeCount (0x24b724) — XBE naked draft (batch 329). */
#if defined(__clang__)


__attribute__((naked, noinline))
void IUsbInit_GetMaxDeviceTypeCount(void)
{
  __asm__ volatile(
      "movl 0x9c(%%ecx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LIUsbInit_GetMaxDeviceTypeCount_3\n\t"
      "movl 0x98(%%ecx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jbe .LIUsbInit_GetMaxDeviceTypeCount_2\n\t"
      "movl %%edx, %%esi\n\t"
      ".LIUsbInit_GetMaxDeviceTypeCount_1:\n\t"
      "movl (%%esi), %%edi\n\t"
      "cmpl 0xc(%%esp), %%edi\n\t"
      ".byte 0x74, 0x0f\n\t"
      "incl %%eax\n\t"
      "addl $8, %%esi\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LIUsbInit_GetMaxDeviceTypeCount_1\n\t"
      ".LIUsbInit_GetMaxDeviceTypeCount_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LIUsbInit_GetMaxDeviceTypeCount_3:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "IUsbInit_GetMaxDeviceTypeCount: clang naked draft required"
#endif


/* 0x0024ba93 */
void FUN_0024ba93(void)
{
  int ecx = 0;
  int edx = 0;

  /* relift: tail-call FUN_0024ba93(); */
  /* test ecx, ecx -> jle 0x24bb32 */
  /* cmp ecx, edx -> jl 0x24bb17 */

  (void)ecx;
  (void)edx;
}

/* XInitDevices (0x24bb54) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void b24bb54_c24fe14_tgt(void) { return; }
static void (*const b24bb54_c24fe14)(void) = b24bb54_c24fe14_tgt;
static void b24bb54_c24b970_tgt(void) { return; }
static void (*const b24bb54_c24b970)(void) = b24bb54_c24b970_tgt;
static void b24bb54_c24bc5b_tgt(void) { return; }
static void (*const b24bb54_c24bc5b)(void) = b24bb54_c24bc5b_tgt;
static void b24bb54_c24bab5_tgt(void) { return; }
static void (*const b24bb54_c24bab5)(void) = b24bb54_c24bab5_tgt;
static void b24bb54_c24bc67_tgt(void) { return; }
static void (*const b24bb54_c24bc67)(void) = b24bb54_c24bc67_tgt;

__attribute__((naked, noinline))
void XInitDevices(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xb4\n\t"
      "call *0x2531bc\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LXInitDevices_1\n\t"
      "pushl 0x14(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0x14(%%esp)\n\t"
      "call *%[c24fe14]\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LXInitDevices_2\n\t"
      ".LXInitDevices_1:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LXInitDevices_2:\n\t"
      "movl $0x24b204, %%eax\n\t"
      "movl $0x24b214, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "jae .LXInitDevices_5\n\t"
      ".LXInitDevices_3:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LXInitDevices_4\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LXInitDevices_4:\n\t"
      "addl $4, %%ebx\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "jb .LXInitDevices_3\n\t"
      ".LXInitDevices_5:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c24b970]\n\t"
      "leal 0xa4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c24bc5b]\n\t"
      "movzbl 0xa1(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movzbl 0xa0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x4ee178, %%ecx\n\t"
      "call *%[c24bab5]\n\t"
      "pushl %%esi\n\t"
      "call *0x253264\n\t"
      "andb $0, 0x4ee260\n\t"
      "call *%[c24bc67]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c24fe14] "m"(b24bb54_c24fe14), [c24b970] "m"(b24bb54_c24b970), [c24bc5b] "m"(b24bb54_c24bc5b), [c24bab5] "m"(b24bb54_c24bab5), [c24bc67] "m"(b24bb54_c24bc67)
      : "memory");
}
#else
#error "XInitDevices: clang naked draft required"
#endif


/* XInputOpen (0x24c143) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void b24c143_c24d291_tgt(void) { return; }
static void (*const b24c143_c24d291)(void) = b24c143_c24d291_tgt;
static void __stdcall (*const b24c143_c1d2268)(unsigned int error) = (void *)SetLastError;

__attribute__((naked, noinline))
void XInputOpen(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "cmpl $0x24b29c, 0x8(%%ebp)\n\t"
      "jne .LXInputOpen_1\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LXInputOpen_3\n\t"
      ".LXInputOpen_1:\n\t"
      "cmpl $0x24b2a8, 0x8(%%ebp)\n\t"
      "jne .LXInputOpen_2\n\t"
      "movb $1, %%cl\n\t"
      "jmp .LXInputOpen_3\n\t"
      ".LXInputOpen_2:\n\t"
      "cmpl $0x24b2b4, 0x8(%%ebp)\n\t"
      "jne .LXInputOpen_7\n\t"
      "movb $2, %%cl\n\t"
      ".LXInputOpen_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LXInputOpen_4\n\t"
      "movzbl %%cl, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "movl 0x24b374(,%%eax,8), %%eax\n\t"
      ".LXInputOpen_4:\n\t"
      "cmpl $1, 0x10(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "jne .LXInputOpen_5\n\t"
      "addl $0x10, %%edx\n\t"
      ".LXInputOpen_5:\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c24d291]\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "jne .LXInputOpen_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2268]\n\t"
      ".LXInputOpen_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "jmp .LXInputOpen_8\n\t"
      ".LXInputOpen_7:\n\t"
      "pushl $0x57\n\t"
      "call *%[c1d2268]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LXInputOpen_8:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c24d291] "m"(b24c143_c24d291), [c1d2268] "m"(b24c143_c1d2268)
      : "memory");
}
#else
#error "XInputOpen: clang naked draft required"
#endif


/* XInputClose (0x24c1b8) — XBE naked draft (batch 395). */
#if defined(__clang__)
static void (*const b24c1b8_c24d009)(void) = (void *)XID_fCloseDevice;

__attribute__((naked, noinline))
void XInputClose(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%ecx\n\t"
      "call *%[c24d009]\n\t"
      "ret\n\t"
      :
      : [c24d009] "m"(b24c1b8_c24d009)
      : "memory");
}
#else
#error "XInputClose: clang naked draft required"
#endif


/* XInputGetCapabilities (0x24c1c4) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void b24c1c4_c24dc24_tgt(void) { return; }
static void (*const b24c1c4_c24dc24)(void) = b24c1c4_c24dc24_tgt;
static void b24c1c4_c24d81f_tgt(void) { return; }
static void (*const b24c1c4_c24d81f)(void) = b24c1c4_c24d81f_tgt;

__attribute__((naked, noinline))
void XInputGetCapabilities(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "call *0x2531b4\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LXInputGetCapabilities_3\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "jne .LXInputGetCapabilities_3\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl $6\n\t"
      "popl %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "rep stosl\n\t"
      ".byte 0xaa\n\t"
      "movb 0xb(%%esi), %%al\n\t"
      "movb %%al, (%%edx)\n\t"
      "movzbl 0xa(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $3, %%eax\n\t"
      "testb $1, 0x24b37c(%%eax)\n\t"
      "je .LXInputGetCapabilities_1\n\t"
      "movl $5, -0x8(%%ebp)\n\t"
      "jmp .LXInputGetCapabilities_4\n\t"
      ".LXInputGetCapabilities_1:\n\t"
      "movl 0x24b370(%%eax), %%eax\n\t"
      "movzbl (%%eax), %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "leal 0x2(%%eax), %%ecx\n\t"
      "addl $0x13, %%edx\n\t"
      "movb %%bl, -0x18(%%ebp)\n\t"
      "movb $4, -0x16(%%ebp)\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movb $0x30, -0x48(%%ebp)\n\t"
      "movb $0x40, -0x47(%%ebp)\n\t"
      "movl $0x24ce52, -0x40(%%ebp)\n\t"
      "movl %%ebx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movb $2, -0x2c(%%ebp)\n\t"
      "movb $1, -0x2b(%%ebp)\n\t"
      "movb %%bl, -0x2a(%%ebp)\n\t"
      "movb $0xc1, -0x20(%%ebp)\n\t"
      "movb $1, -0x1f(%%ebp)\n\t"
      "movw $0x200, -0x1e(%%ebp)\n\t"
      "movzbw 0x5(%%esi), %%cx\n\t"
      "addl $2, %%eax\n\t"
      "movw %%ax, -0x1a(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "movw %%cx, -0x1c(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c24dc24]\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      "movl 0x2531ac, %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%edi\n\t"
      "call *0x2531b4\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%ebx, (%%eax)\n\t"
      "je .LXInputGetCapabilities_3\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "jne .LXInputGetCapabilities_3\n\t"
      "cmpl %%ebx, -0x44(%%ebp)\n\t"
      "jl .LXInputGetCapabilities_2\n\t"
      "movzbl 0xa(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "movl 0x24b36c(,%%eax,8), %%eax\n\t"
      "movzbl (%%eax), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "leal 0x2(%%eax), %%ecx\n\t"
      "addl $2, %%eax\n\t"
      "movb $0x30, -0x48(%%ebp)\n\t"
      "movb $0x40, -0x47(%%ebp)\n\t"
      "movl $0x24ce52, -0x40(%%ebp)\n\t"
      "movl %%ebx, -0x38(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movb $2, -0x2c(%%ebp)\n\t"
      "movb $1, -0x2b(%%ebp)\n\t"
      "movb %%bl, -0x2a(%%ebp)\n\t"
      "movb $0xc1, -0x20(%%ebp)\n\t"
      "movb $1, -0x1f(%%ebp)\n\t"
      "movw $0x100, -0x1e(%%ebp)\n\t"
      "movzbw 0x5(%%esi), %%cx\n\t"
      "movw %%ax, -0x1a(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "movw %%cx, -0x1c(%%ebp)\n\t"
      "movb %%bl, -0x18(%%ebp)\n\t"
      "movb $4, -0x16(%%ebp)\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c24dc24]\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%edi\n\t"
      "call *0x2531b4\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%ebx, (%%eax)\n\t"
      "je .LXInputGetCapabilities_3\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "jne .LXInputGetCapabilities_3\n\t"
      "cmpl %%ebx, -0x44(%%ebp)\n\t"
      "jge .LXInputGetCapabilities_4\n\t"
      ".LXInputGetCapabilities_2:\n\t"
      "pushl -0x44(%%ebp)\n\t"
      "call *%[c24d81f]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .LXInputGetCapabilities_4\n\t"
      ".LXInputGetCapabilities_3:\n\t"
      "movl $0x48f, -0x8(%%ebp)\n\t"
      ".LXInputGetCapabilities_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "movw %%bx, 0x1(%%eax)\n\t"
      "call *0x2531b0\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c24dc24] "m"(b24c1c4_c24dc24), [c24d81f] "m"(b24c1c4_c24d81f)
      : "memory");
}
#else
#error "XInputGetCapabilities: clang naked draft required"
#endif


/* XInputGetState (0x24c3b6) — XBE naked draft (batch 327). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XInputGetState(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *0x2531b4\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "cmpb $1, 0xa3(%%edx)\n\t"
      "jne .LXInputGetState_1\n\t"
      "pushl $0x57\n\t"
      "popl %%esi\n\t"
      "jmp .LXInputGetState_4\n\t"
      ".LXInputGetState_1:\n\t"
      "movl (%%edx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LXInputGetState_2\n\t"
      "testb $2, 0x4(%%ecx)\n\t"
      "je .LXInputGetState_3\n\t"
      ".LXInputGetState_2:\n\t"
      "movl $0x48f, %%ebx\n\t"
      ".LXInputGetState_3:\n\t"
      "movl 0x8(%%edx), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movzbl 0xa3(%%edx), %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "movl 0x24b36c(,%%ecx,8), %%ecx\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "leal 0x14(%%edx), %%esi\n\t"
      "movl %%ecx, %%edx\n\t"
      "addl $4, %%edi\n\t"
      "shrl $2, %%ecx\n\t"
      "rep movsl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "movl %%ebx, %%esi\n\t"
      "popl %%edi\n\t"
      ".LXInputGetState_4:\n\t"
      "movb %%al, %%cl\n\t"
      "call *0x2531b0\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XInputGetState: clang naked draft required"
#endif


/* XInputPoll (0x24c45f) — XBE naked draft (batch 351). */
#if defined(__clang__)
static void b24c45f_c24dc24_tgt(void) { return; }
static void (*const b24c45f_c24dc24)(void) = b24c45f_c24dc24_tgt;

__attribute__((naked, noinline))
void XInputPoll(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *0x2531b4\n\t"
      "movb %%al, %%bl\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "je .LXInputPoll_1\n\t"
      "testb $2, 0x4(%%ecx)\n\t"
      "jne .LXInputPoll_1\n\t"
      "testb $8, 0xa2(%%eax)\n\t"
      "jne .LXInputPoll_2\n\t"
      "cmpl %%esi, 0x4(%%eax)\n\t"
      "jne .LXInputPoll_2\n\t"
      "movl $1, 0x4(%%eax)\n\t"
      "movzbl 0xc(%%ecx), %%edx\n\t"
      "movl %%edx, 0x66(%%eax)\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "addl $0x52, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c24dc24]\n\t"
      "jmp .LXInputPoll_2\n\t"
      ".LXInputPoll_1:\n\t"
      "movl $0x48f, %%esi\n\t"
      ".LXInputPoll_2:\n\t"
      "movb %%bl, %%cl\n\t"
      "call *0x2531b0\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c24dc24] "m"(b24c45f_c24dc24)
      : "memory");
}
#else
#error "XInputPoll: clang naked draft required"
#endif


/* XGetDevices (0x24c932) — XBE naked draft (batch 379). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XGetDevices(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *0x2531b4\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "movl (%%edx), %%esi\n\t"
      "andl $0, 0x4(%%edx)\n\t"
      "movb %%al, %%cl\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "call *0x2531b0\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XGetDevices: clang naked draft required"
#endif


/* XGetDeviceChanges (0x24c954) — XBE naked draft (batch 321). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XGetDeviceChanges(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0x4(%%esi)\n\t"
      "jne .LXGetDeviceChanges_1\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jmp .LXGetDeviceChanges_2\n\t"
      ".LXGetDeviceChanges_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *0x2531b4\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "notl %%ecx\n\t"
      "andl (%%esi), %%ecx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "notl %%edx\n\t"
      "andl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "andl 0x8(%%esi), %%edi\n\t"
      "andl (%%esi), %%edi\n\t"
      "orl %%edi, %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "orl %%edi, (%%ebx)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "andl $0, 0x4(%%esi)\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movb %%al, %%cl\n\t"
      "call *0x2531b0\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "orl (%%ecx), %%eax\n\t"
      "popl %%edi\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "popl %%ebx\n\t"
      ".LXGetDeviceChanges_2:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XGetDeviceChanges: clang naked draft required"
#endif


/* XID_fCloseDevice (0x24d009) — XBE naked draft (batch 318). */
#if defined(__clang__)
static void b24d009_c24ce9d_tgt(void) { return; }
static void (*const b24d009_c24ce9d)(void) = b24d009_c24ce9d_tgt;

__attribute__((naked, noinline))
void XID_fCloseDevice(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *0x2531b4\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, (%%esi)\n\t"
      "movb %%al, %%cl\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "je .LXID_fCloseDevice_2\n\t"
      "cmpb $1, 0xa3(%%esi)\n\t"
      "jne .LXID_fCloseDevice_1\n\t"
      "movl 0x24b298, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LXID_fCloseDevice_1\n\t"
      "pushl %%esi\n\t"
      "call *0x4(%%eax)\n\t"
      ".LXID_fCloseDevice_1:\n\t"
      "orb $1, 0xa2(%%esi)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movb %%bl, -0x14(%%ebp)\n\t"
      "movb $4, -0x12(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl %%eax, 0x9e(%%esi)\n\t"
      "call *%[c24ce9d]\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "call *0x2531b0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531ac\n\t"
      "jmp .LXID_fCloseDevice_3\n\t"
      ".LXID_fCloseDevice_2:\n\t"
      "call *0x2531b0\n\t"
      ".LXID_fCloseDevice_3:\n\t"
      "movzbl 0xa3(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal 0x24b368(,%%eax,8), %%eax\n\t"
      "incb (%%eax)\n\t"
      "movl 0x4ee0d0, %%eax\n\t"
      "movl %%eax, 0xa4(%%esi)\n\t"
      "movl %%esi, 0x4ee0d0\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c24ce9d] "m"(b24d009_c24ce9d)
      : "memory");
}
#else
#error "XID_fCloseDevice: clang naked draft required"
#endif

