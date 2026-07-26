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
void D3DCubeTexture_LockRect(void);
void D3DVolumeTexture_LockBox(void);
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
int D3DSurface_LockRect(void *surface, void *locked_rect, void *rect, uint32_t flags);
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

void QueueUserAPC(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001cfbab */
void ExitThread(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  XapiCallThreadNotifyRoutines();
  /* test eax, eax -> jl 0x1cfbfd */
  /* relift: cmp byte ptr [ecx + 4], 0 -> je 0x1cfbe8 */
  XapiSetLastNTError(0);
  /* mem[0x00632a2c] = ecx */
  /* cmp eax, ebx -> jl 0x1cfc97 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [esp + 0xc], 0 -> je 0x1cfcd4 */
  /* mem[0x0032fd20] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x001cfcf4 */
void XapiThreadStartup(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* test ecx, ecx -> je 0x1cfd59 */
  XapiCallThreadNotifyRoutines();
  XapiCallThreadNotifyRoutines();
  UnhandledExceptionFilter();
  /* test eax, eax -> jne 0x1cfd9b */
  /* test eax, eax -> jge 0x1cfdd9 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x1cfe0b */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1cfe42 */
  /* cmp eax, 0x40000000 -> jne 0x1cfe36 */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1cfe61 */
  /* test eax, eax -> jge 0x1cfea3 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cfebf */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cfedd */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ecx;
  (void)ebp;
}

/* 0x001cfee8 */
void PulseEvent(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> jl 0x1cfefd */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x1cff26 */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1cff57 */
  /* cmp eax, 0x40000000 -> jne 0x1cff4b */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1cff76 */
  /* test eax, eax -> jge 0x1cffb8 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cffda */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1d0003 */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1d0031 */
  /* cmp eax, 0x40000000 -> jne 0x1d0025 */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d0050 */
  /* test eax, eax -> jge 0x1d0092 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d00ae */
  XapiSetLastNTError(0);
  FUN_001d4436();
  /* test eax, eax -> jl 0x1d00ef */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1d00f8 */
  /* cmp eax, 0x101 -> je 0x1d00cd */
  XapiSetLastNTError(0);
  FUN_001d4436();
  /* test eax, eax -> jl 0x1d0136 */
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x1d013f */
  /* cmp eax, 0x101 -> je 0x1d0111 */
  XapiSetLastNTError(0);
  /* cmp ecx, 0x40 -> jbe 0x1d0164 */
  XapiSetLastNTError(0xc000000d);
  FUN_001d4436();
  /* test eax, eax -> jl 0x1d01b4 */
  /* relift: cmp dword ptr [ebp + 0x18], 0 -> je 0x1d01bd */
  /* cmp eax, 0x101 -> je 0x1d018c */
  XapiSetLastNTError(0);
  FUN_001d4436();
  /* test esi, esi -> jne 0x1d01e9 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d0202 */
  /* cmp eax, 0x101 -> je 0x1d01e9 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1d0234 */
  XapiFormatObjectAttributes();
  /* test eax, eax -> jl 0x1d0268 */
  /* cmp eax, 0x40000000 -> jne 0x1d025c */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d0287 */
  /* test eax, eax -> jge 0x1d02c9 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d02fd */
  XapiSetLastNTError(0);
  /* cmp eax, 0x40000025 -> jne 0x1d0308 */
  SetLastError(0);
  /* test eax, eax -> jge 0x1d0330 */
  XapiSetLastNTError(0);
  FUN_001d00b9();
  FUN_001d0144();
  SleepEx(0, 0);
  /* test dl, dl -> jne 0x1d037e */
  /* test esi, esi -> jge 0x1d03d3 */
  OutputDebugStringA();
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
  FUN_001d0447();
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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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

/* 0x001e6a10 */
void D3DDevice_GetCreationParameters(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6a50 */
void D3DDevice_SetGammaRamp(void)
{
  /* relift: FUN_001eff04(0); */
}

/* 0x001e6ab0 */
void D3DDevice_GetGammaRamp(void)
{
  D3D_CreateTexture();
}

/* 0x001e6b10 */
void D3DDevice_CreateVolumeTexture(void)
{
  D3D_CreateTexture();
}

/* 0x001e6b40 */
void D3DDevice_CreateCubeTexture(void)
{
  D3D_CreateTexture();
  /* relift: FUN_001ef330(0, 0, 0, 0); */
}

/* 0x001e6ba0 */
void D3DDevice_CreateImageSurface(void)
{
  /* relift: FUN_001ef330(0, 0, 0, 0); */
}

/* 0x001e6bc0 */
void D3DDevice_SetRenderState(void)
{
  int edx = 0;
  int esi = 0;

  D3DDevice_SetRenderStateNotInline();
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

/* 0x001e6d10 */
void D3DDevice_MultiplyTransform(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: FUN_001f2340(0, 0, 0); */
  D3DDevice_SetTransform(esi, (void *)(uintptr_t)eax);

  (void)eax;
  (void)esi;
}

/* 0x001e6d60 */
void D3DDevice_GetViewport(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6d80 */
void D3DDevice_SetMaterial(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6db0 */
void D3DDevice_GetMaterial(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6dd0 */
void D3DDevice_SetBackMaterial(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6e00 */
void D3DDevice_GetBackMaterial(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6e30 */
void D3DDevice_GetLight(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6e60 */
void D3DDevice_GetLightEnable(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6ed0 */
void D3DDevice_SwitchTexture(void)
{
  int eax = 0;

  /* relift: cmp eax, dword ptr [0x1fbb14] -> jae 0x1e6ef5 */
  /* mem[0x001fbb10] = eax */
  CDevice_MakeSpace();

  (void)eax;
}

/* 0x001e6f30 */
void D3DDevice_AddRef(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e6f50 */
void D3DDevice_Release(void)
{
  int eax = 0;

  /* cmp eax, 1 -> jne 0x1e6f7e */
  /* relift: FUN_001f3a90(0, 0); */
  /* mem[0x001fe6a4] = eax */
  /* mem[0x001fe6a0] = eax */

  (void)eax;
}

/* 0x001e6fa0 */
void D3DDevice_BlockOnFence(void)
{
  int eax = 0;

  D3D_BlockOnTime(eax, 0);

  (void)eax;
}

/* 0x001e6fb0 */
void D3DDevice_KickPushBuffer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e7030 */
void D3DDevice_GetVisibilityTestResult(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> je 0x1e707e */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_Clear(edx, (void *)(uintptr_t)ecx, eax, edx, 0.0f, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x001e70e0 */
void D3DDevice_SetVerticalBlankCallback(void)
{
  int eax = 0;

  D3DDevice_SetViewport((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x001e7140 */
void D3DDevice_GetProjectionViewportMatrix(void)
{
  D3DDevice_SetRenderStateNotInline();
}

/* 0x001e7180 */
void D3DDevice_GetModelView(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e7200 */
void D3DDevice_GetTile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e7230 */
void D3DDevice_GetScissors(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e72a0 */
void D3DDevice_SetFlickerFilter(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e72c0 */
void D3DDevice_SetSoftDisplayFilter(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e73a0 */
void D3DDevice_InsertFence(void)
{
  D3D_SetFence();
}

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

/* 0x001e76b0 */
void D3DBaseTexture_GetLevelCount(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x001e79d0 */
void D3DDevice_GetDisplayMode(void)
{
  /* relift: FUN_001f4840(0); */
}

/* 0x001e7a30 */
void D3DDevice_Reset(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* test eax, eax -> je 0x1e7d6b */
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp eax, dword ptr [ecx + 0x21b8] -> jae 0x1e7dc1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001e7de0 */
void D3DDevice_CopyRects(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x001e8250 */
void D3DDevice_GetRenderTarget(void)
{
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001ed8f0(0); */
}

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

/* 0x001e8400 */
void D3DDevice_SetLight(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x001e85e0 */
void D3DDevice_LightEnable(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp ebx, dword ptr [esi + 0x484] -> jae 0x1e860a */
  /* relift: test byte ptr [ecx + eax + 0x68], 1 -> jne 0x1e8650 */
  D3DDevice_SetLight();
  /* cmp eax, ecx -> je 0x1e868a */
  /* test eax, eax -> jne 0x1e8678 */
  /* test eax, eax -> je 0x1e86b0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x001e86c0 */
void D3DDevice_GetTexture2(void)
{
  int eax = 0;
  int ebp = 0;

  /* test eax, eax -> je 0x1e86ea */
  /* relift: FUN_001ed8f0(0); */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  XMETAL_StartPush();
  /* relift: FUN_001ed8b0(0, 0); */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1e87ff */
  /* relift: FUN_001e77d0(0); */
  /* cmp eax, ebp -> je 0x1e884e */
  /* test eax, eax -> je 0x1e888a */
  /* relift: FUN_001ed8f0(0); */

  (void)eax;
  (void)ebp;
}

/* 0x001e88a0 */
void D3DDevice_SetPalette(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x1e88df */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* relift: FUN_001ed8b0(0, 0); */
  XMETAL_StartPush();

  (void)eax;
}

/* 0x001e8920 */
void D3DDevice_SetIndices(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0x1e8940 */
  /* relift: FUN_001ed8b0(0); */
  /* mem[0x001fb494] = eax */
  /* mem[0x001fb494] = 0 */
  /* test eax, eax -> je 0x1e8998 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x1e89df */
  /* relift: FUN_001ed8f0(0); */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x001e8a00 */
void D3DDevice_IsBusy(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e8a40 */
void D3DDevice_BeginVisibilityTest(void)
{
  XMETAL_StartPush();
}

/* 0x001e8a70 */
void D3DDevice_EndVisibilityTest(void)
{
  int esi = 0;

  /* relift: FUN_001e6fc0(0, 0); */
  /* test esi, esi -> jne 0x1e8a8a */
  XMETAL_StartPush();
  CDevice_KickOff();

  (void)esi;
}

/* 0x001e8ad0 */
void D3DDevice_GetDisplayFieldStatus(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001e8b10 */
void D3DDevice_FlushVertexCache(void)
{
  XMETAL_StartPush();
}

/* 0x001e8b40 */
void D3DDevice_SetModelView(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x001e8d30 */
void D3DDevice_SetTile(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001e9000 */
void D3DDevice_SetScissors(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001e92f0 */
void D3DDevice_SetRenderState_MultiSampleType(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* mem[0x001fb8b0] = ecx */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x001e9320 */
void D3DDevice_SetRenderState_PSTextureModes(void)
{
  int eax = 0;
  int ecx = 0;

  /* mem[0x001fb868] = ecx */
  /* relift: cmp eax, dword ptr [0x1fbb14] -> jae 0x1e936c */
  /* mem[0x001fbb10] = eax */
  CDevice_MakeSpace();

  (void)eax;
  (void)ecx;
}

/* 0x001e93a0 */
void D3DDevice_SetRenderStateNotInline(void)
{
  int esi = 0;
  int edi = 0;

  /* cmp esi, 0x52 -> jge 0x1e93c9 */
  D3DDevice_SetRenderState_Simple(edi, 0);
  /* cmp esi, 0x74 -> jge 0x1e93ea */

  (void)esi;
  (void)edi;
}

/* 0x001e9400 */
void D3DDevice_SetRenderState2(void)
{
  int esi = 0;

  D3DDevice_SetRenderStateNotInline();
  /* mem[0x001fbb18] = esi */
  /* relift: FUN_001f3c30(0, 0); */

  (void)esi;
}

/* 0x001e9620 */
void D3DDevice_SetRenderState_EdgeAntiAlias(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb8a4] = ecx */

  (void)ecx;
}

/* 0x001e9650 */
void D3DDevice_SetRenderState_ShadowFunc(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb8b4] = ecx */

  (void)ecx;
}

/* 0x001e9680 */
void D3DDevice_SetRenderState_FogColor(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb870] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb894] = ecx */
  /* mem[0x001fb894] = ecx */

  (void)ecx;
}

/* 0x001e9740 */
void D3DDevice_SetRenderState_FrontFace(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb890] = ecx */

  (void)ecx;
}

/* 0x001e9780 */
void D3DDevice_SetRenderState_NormalizeNormals(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb880] = ecx */

  (void)ecx;
}

/* 0x001e97b0 */
void D3DDevice_SetRenderState_TextureFactor(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1e97ef */
  XMETAL_StartPush();
  /* mem[0x001fb898] = eax */
  /* mem[0x001fb898] = eax */

  (void)eax;
}

/* 0x001e9800 */
void D3DDevice_SetRenderState_LineWidth(void)
{
  int ebx = 0;
  int edi = 0;

  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edi, 0x1ff -> jbe 0x1e983f */
  XMETAL_StartPush();
  /* mem[0x001fb8b8] = ebx */

  (void)ebx;
  (void)edi;
}

/* 0x001e9860 */
void D3DDevice_SetRenderState_Dxt1NoiseEnable(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* cmp dl, 0x20 -> jne 0x1e9889 */
  /* cmp edi, ecx -> je 0x1e98cb */
  XMETAL_StartPush();
  /* mem[0x001fb8bc] = ebx */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

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

/* 0x001e9960 */
void D3DDevice_SetRenderState_LogicOp(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* test ecx, ecx -> jne 0x1e998d */
  /* mem[0x001fb8a0] = ecx */
  /* mem[0x001fb8a0] = ecx */

  (void)ecx;
}

/* 0x001e99b0 */
void D3DDevice_SetRenderState_FillMode(uint32_t value)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb874] = ecx */

  (void)ecx;
}

/* 0x001e99f0 */
void D3DDevice_SetRenderState_BackFillMode(void)
{
  int eax = 0;
  int esi = 0;

  /* mem[0x001fb878] = eax */
  XMETAL_StartPush();
  /* mem[0x001fb874] = esi */

  (void)eax;
  (void)esi;
}

/* 0x001e9a40 */
void D3DDevice_SetRenderState_TwoSidedLighting(void)
{
  int eax = 0;
  int esi = 0;

  /* mem[0x001fb87c] = eax */
  XMETAL_StartPush();
  /* mem[0x001fb874] = esi */

  (void)eax;
  (void)esi;
}

/* 0x001e9aa0 */
void D3DDevice_SetRenderState_VertexBlend(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* mem[0x001fb86c] = ecx */

  (void)ecx;
}

/* 0x001e9ae0 */
void D3DDevice_SetTextureState_TexCoordIndex(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> je 0x1e9b22 */
  /* cmp ecx, 0x10000 -> jne 0x1e9b44 */
  /* cmp ecx, 0x30000 -> je 0x1e9b52 */
  /* cmp ecx, 0x40000 -> je 0x1e9b4b */
  /* test edx, edx -> jne 0x1e9b6e */
  /* test eax, eax -> je 0x1e9b6e */
  XMETAL_StartPush();

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x001e9bc0 */
void D3DDevice_SetTextureState_BumpEnv(void)
{
  XMETAL_StartPush();
  XMETAL_StartPush();
}

/* 0x001e9c60 */
void D3DDevice_SetTextureState_ColorKeyColor(void)
{
  XMETAL_StartPush();
}

/* 0x001e9cb0 */
void D3DDevice_SetTextureStageStateNotInline(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp eax, 0x1c -> jne 0x1e9cf9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp eax, 0x1d -> jne 0x1e9d10 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001ea1c0 */
void D3D_CommonSetDebugRegisters(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> je 0x1ea227 */
  XMETAL_StartPush();
  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1ea2b6 */
  /* test edx, edx -> je 0x1ea2b6 */
  /* mem[0x001fb884] = ecx */
  /* cmp ecx, 2 -> jne 0x1ea2f8 */
  D3D_UpdateProjectionViewportTransform();
  /* relift: FUN_001eb6f0(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9f80(0, 0); */

  (void)eax;
  (void)ecx;
  (void)edx;
}

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

/* 0x001ea3f0 */
void D3DDevice_SetRenderState_YuvEnable(void)
{
  int eax = 0;

  /* mem[0x001fb8c0] = eax */
  XMETAL_StartPush();
  /* relift: FUN_001e9f80(0, 0); */

  (void)eax;
}

/* 0x001ea420 */
void D3DDevice_SetRenderState_OcclusionCullEnable(void)
{
  int eax = 0;
  int edx = 0;

  /* mem[0x001fb8c4] = eax */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea447 */
  /* test edx, edx -> je 0x1ea46a */
  /* test edx, edx -> je 0x1ea467 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea46a */

  (void)eax;
  (void)edx;
}

/* 0x001ea480 */
void D3DDevice_SetRenderState_StencilCullEnable(void)
{
  int eax = 0;
  int edx = 0;

  /* mem[0x001fb8c8] = eax */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea4a7 */
  /* test edx, edx -> je 0x1ea4ca */
  /* test edx, edx -> je 0x1ea4c7 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea4ca */

  (void)eax;
  (void)edx;
}

/* 0x001ea4e0 */
void D3DDevice_SetRenderState_RopZCmpAlwaysRead(void)
{
  int eax = 0;

  /* mem[0x001fb8cc] = eax */
  D3D_CommonSetDebugRegisters();

  (void)eax;
}

/* 0x001ea500 */
void D3DDevice_SetRenderState_RopZRead(void)
{
  int eax = 0;

  /* mem[0x001fb8d0] = eax */
  D3D_CommonSetDebugRegisters();

  (void)eax;
}

/* 0x001ea520 */
void D3DDevice_SetRenderState_DoNotCullUncompressed(void)
{
  int eax = 0;

  /* mem[0x001fb8d4] = eax */
  D3D_CommonSetDebugRegisters();

  (void)eax;
}

/* 0x001ea540 */
void D3DDevice_SetRenderState_MultiSampleAntiAlias(void)
{
  int eax = 0;

  /* mem[0x001fb8a8] = eax */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */

  (void)eax;
}

/* 0x001ea590 */
void D3DDevice_SetRenderState_MultiSampleMask(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* mem[0x001fb8ac] = eax */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x001eac90 */
void D3DDevice_GetShaderConstantMode(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eaf70 */
void D3DDevice_CreateVertexShader(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001eb0b0 */
void D3DDevice_GetVertexShader(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eb0d0 */
void D3DDevice_GetVertexShaderConstant(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eb110 */
void D3DDevice_GetVertexShaderInput(void)
{
  int ecx = 0;
  int edi = 0;

  /* test ecx, ecx -> je 0x1eb135 */
  /* test edi, edi -> je 0x1eb160 */
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  /* relift: FUN_001ef590(0, 0); */

  (void)ecx;
  (void)edi;
}

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

/* 0x001eb3b0 */
void D3DDevice_RunVertexStateShader(void)
{
  int ecx = 0;

  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1eb3e6 */

  (void)ecx;
}

/* 0x001eb400 */
void D3DDevice_LoadVertexShader(void)
{
  int eax = 0;

  /* test (char)eax, 0x10 -> jne 0x1eb421 */
  /* relift: FUN_001eab60(0, 0); */
  /* relift: FUN_001efe30(0, 0); */

  (void)eax;
}

/* 0x001eb460 */
void D3DDevice_LoadVertexShaderProgram(void)
{
  int ecx = 0;

  /* test (char)ecx, 0x10 -> jne 0x1eb495 */
  /* relift: FUN_001efe30(0, 0); */
  /* relift: FUN_001eac20(0); */

  (void)ecx;
}

/* 0x001eb4d0 */
void D3DDevice_SelectVertexShader(void)
{
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  XMETAL_StartPush();
}

/* 0x001eb540 */
void D3DDevice_GetVertexShaderSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eb560 */
void D3DDevice_GetVertexShaderType(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eb590 */
void D3DDevice_SetShaderConstantMode(void)
{
  XMETAL_StartPush();
  /* relift: FUN_001ef590(0, 0); */
  /* relift: FUN_001ef590(0, 0x00400880, 0x001f9f48); */
  /* relift: FUN_001ef590(0, 0x004008c0, 0x001f9f48); */
  /* relift: FUN_001ef590(0, 0x00400900, 0x001f9f48); */
  XMETAL_StartPush();
  /* relift: FUN_001eac20(0); */
}

/* 0x001eb6d0 */
void D3DDevice_DeleteVertexShader(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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
  /* relift: FUN_001eaa20(0, 0); */
  /* test (char)eax, 4 -> je 0x1eb860 */
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001eb6f0(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001eb8d0 */
void D3DDevice_SetVertexShaderConstant(int register_index, const void *data, uint32_t count)
{
  int eax = 0;

  /* relift: FUN_001efe30(0, 0); */
  /* cmp eax, 0x20 -> jle 0x1eb94e */
  /* cmp eax, 0x20 -> jg 0x1eb935 */

  (void)eax;
}

/* 0x001eb970 */
void D3DDevice_GetVertexShaderDeclaration(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001ebda0 */
void D3DDevice_GetVertexShaderFunction(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001ebe60 */
void D3DDevice_SetVertexShaderInput(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x001ec0b0 */
void D3DDevice_CreatePixelShader(void)
{
  int eax = 0;

  FUN_001d0bb9(0, 252);
  /* test eax, eax -> jne 0x1ec0c8 */

  (void)eax;
}

/* 0x001ec100 */
void D3DDevice_DeletePixelShader(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001ec160 */
void D3DDevice_GetPixelShader(void)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;

  /* test (char)eax, 0x41 -> jne 0x1ec19b */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edi, 4 -> jb 0x1ec471 */
  /* cmp ebx, edi -> jae 0x1ec532 */
  D3DDevice_SetRenderStateNotInline();

  (void)eax;
  (void)ebx;
  (void)edi;
}

/* 0x001ec5c0 */
void D3DDevice_SetPixelShader(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  D3DDevice_SetRenderState_TextureFactor();
  XMETAL_StartPush();
  /* relift: FUN_001e9d40(0, 0); */
  XMETAL_StartPush();
  /* test esi, esi -> jne 0x1ec67f */
  /* relift: FUN_001e9d40(0, 0); */
  /* test ecx, ecx -> je 0x1ec749 */
  /* relift: test byte ptr [ebx + 0xc], 0x10 -> jne 0x1ec76f */
  /* mem[0x001fb868] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x001ec780 */
void D3DDevice_SetPixelShaderConstant(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x001ecc70 */
void D3DDevice_DrawVerticesUP(void)
{
  int eax = 0;
  int ecx = 0;

  CDevice_SetStateUP();
  XMETAL_StartPush();
  /* cmp eax, ecx -> jb 0x1ecd06 */
  /* relift: FUN_001efe30(0, 0); */
  /* test eax, eax -> je 0x1ecd6e */
  /* test (char)eax, 0x10 -> je 0x1ecd95 */
  D3D_SetFence();

  (void)eax;
  (void)ecx;
}

/* 0x001ecdb0 */
void D3DDevice_DrawIndexedVerticesUP(void)
{
  int eax = 0;
  int ecx = 0;

  CDevice_SetStateUP();
  XMETAL_StartPush();
  /* cmp eax, ecx -> jb 0x1ece37 */
  /* relift: FUN_001efe30(0); */
  /* test (char)eax, 0x10 -> je 0x1eced1 */
  D3D_SetFence();

  (void)eax;
  (void)ecx;
}

/* 0x001ecef0 */
void D3DDevice_DrawVertices(uint32_t primitive_type, uint32_t start_vertex, uint32_t vertex_count)
{
  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0, 0); */
}

/* 0x001ecf90 */
void D3DDevice_DrawIndexedVertices(void)
{
  int eax = 0;
  int edx = 0;

  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0); */
  /* test eax, eax -> je 0x1ed035 */
  /* cmp edx, 0x3e -> jb 0x1ed062 */
  /* relift: FUN_001efe30(0, 516); */
  D3D_SetFence();

  (void)eax;
  (void)edx;
}

/* 0x001ed200 */
void D3DDevice_PrimeVertexCache(void)
{
  int ecx = 0;

  CDevice_SetStateVB();
  XMETAL_StartPush();
  XMETAL_StartPush();
  XMETAL_StartPush();
  /* cmp ecx, -1 -> jne 0x1ed2dd */
  XMETAL_StartPush();

  (void)ecx;
}

/* 0x001ed360 */
void D3DDevice_SetVertexData4s(void)
{
  XMETAL_StartPush();
}

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

/* 0x001ed570 */
void D3DResource_GetType(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x001edc20 */
void D3DTexture_GetSurfaceLevel(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef2a0(0, 0, 0, 0); */
  Lock2DSurface((void *)(uintptr_t)ecx, 0, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x001edcb0 */
void D3DCubeTexture_GetCubeMapSurface(void)
{
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef2a0(0, 0, 0, 0); */
}

/* 0x001edd10 */
void D3DCubeTexture_LockRect(void)
{
  int eax = 0;

  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* test eax, eax -> je 0x1f4578 */

  (void)eax;
}

/* 0x001edd80 */
void D3DVolumeTexture_LockBox(void)
{
  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
}

/* 0x001eddd0 */
void D3D_CreateTexture(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* relift: test dword ptr [esp + 0x20], 0x10000 -> je 0x1ede24 */
  FUN_001d0bb9(64, 20);
  /* test esi, esi -> je 0x1ede55 */
  /* test eax, eax -> jne 0x1ede60 */
  LocalFree((void *)(uintptr_t)esi);

  (void)eax;
  (void)esi;
}

/* 0x001edea0 */
void D3D_SetPushBufferSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001edec0 */
void Direct3D_CreateDevice(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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

/* 0x001eeac0 */
void D3D_GetAdapterIdentifier(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eeaf0 */
void D3D_GetAdapterModeCount(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x001eeb90 */
void D3D_EnumAdapterModes(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x001eecf0 */
void D3D_GetDeviceCaps(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x1eed00 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eed0f */
  D3DDevice_GetDeviceCaps((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x001eed40 */
void D3D_GetAdapterDisplayMode(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> je 0x1eed50 */
  /* test ecx, ecx -> jne 0x1eed71 */
  /* relift: FUN_001f4840(0); */
  /* test eax, eax -> je 0x1eedd0 */
  /* cmp ecx, eax -> je 0x1eede5 */
  /* relift: cmp dword ptr [esp + 0x14], eax -> jne 0x1eedf3 */

  (void)eax;
  (void)ecx;
}

/* 0x001eee20 */
void D3D_CheckDeviceFormat(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eeea0 */
void Direct3D_CheckDeviceMultiSampleType(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001eef80 */
void D3DDevice_CreateIndexBuffer(void)
{
  int eax = 0;

  FUN_001d0bb9(0, eax);
  /* test eax, eax -> jne 0x1eef9b */

  (void)eax;
}

/* 0x001eefe0 */
void D3DPalette_Lock(void)
{
  D3D_BlockOnResource();
  /* relift: FUN_001ed7c0(0); */
}

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

/* 0x001ef100 */
void D3DVertexBuffer_Lock(void)
{
  XMETAL_StartPush();
  D3D_BlockOnResource();
  /* relift: FUN_001ed7c0(0); */
}

/* 0x001ef150 */
void D3DVertexBuffer_GetDesc(void)
{
  D3DResource_GetType();
}

/* 0x001ef170 */
void D3DDevice_CreatePalette(void)
{
  int eax = 0;
  int edi = 0;

  FUN_001d0bb9(64, 12);
  /* test edi, edi -> jne 0x1ef189 */
  /* test eax, eax -> jne 0x1ef1be */
  LocalFree((void *)(uintptr_t)edi);

  (void)eax;
  (void)edi;
}

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

/* 0x001ef200 */
int D3DSurface_LockRect(void *surface, void *locked_rect, void *rect, uint32_t flags)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001ef890 */
void D3DDevice_IsFencePending(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001ef8c0 */
void D3DDevice_InsertCallback(uint32_t type, void *callback, uint32_t context)
{
  XMETAL_StartPush();
}

/* 0x001ef930 */
void CDevice_KickOff(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001ef9e0 */
void D3D_SetFence(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  XMETAL_StartPush();
  /* test (char)ebx, 2 -> jne 0x1efa6d */
  CDevice_KickOff();
  /* cmp ecx, edx -> jae 0x1efb3f */
  /* cmp esi, eax -> jne 0x1efabc */
  /* relift: tail-call D3D_SetFence(); */
  /* relift: FUN_001ef7e0(0, 0); */
  /* relift: FUN_001ef770(0, 0); */
  /* cmp eax, 0x8000 -> jb 0x1efb27 */
  /* relift: FUN_001ef860(0, 0); */
  /* relift: FUN_001ef770(0, 0); */
  /* cmp eax, 0x8000 -> jae 0x1efb45 */
  /* relift: FUN_001ef860(0, 0); */
  /* cmp eax, esi -> jb 0x1efb34 */
  /* test eax, eax -> jne 0x1efb51 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001efb70 */
void CDevice_MakeSpace(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  D3D_BlockOnTime(ecx, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001efd80 */
void D3D_BlockOnResource(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test eax, eax -> je 0x1efdfe */
  /* test edi, edi -> je 0x1efdc6 */
  /* relift: FUN_001ed870(0); */
  /* test eax, eax -> je 0x1efdc4 */
  D3D_BlockOnTime(edx, 0);
  /* relift: FUN_001ed870(0); */
  D3D_BlockOnTime(ecx, 0);
  D3D_BlockOnTime(edi, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x001efe10 */
void XMETAL_StartPush(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x001f02d0 */
void D3D_UpdateProjectionViewportTransform(void)
{
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: FUN_001f2340(0, 0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001ef590(0, 0); */
}

/* 0x001f05e0 */
void D3D_LazySetPointParams(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* relift: tail-call D3D_LazySetPointParams(); */
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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f1bc0 */
void CDevice_SetStateVB(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f1eb0 */
void CDevice_SetStateUP(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f30c0 */
void CDevice_FreeFrameBuffers(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x001f31c0 */
void CDevice_InitializeFrameBuffers(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* relift: tail-call CDevice_InitializeFrameBuffers(); */
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
  D3D_KickOffAndWaitForIdle();
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
  /* cmp ecx, 0xc -> je 0x1f3da5 */
  /* cmp ecx, 0xd -> jbe 0x1f3da7 */
  /* cmp ecx, 0xf -> ja 0x1f3da7 */
  /* cmp eax, 3 -> je 0x1f3deb */
  /* cmp eax, 0x1c -> je 0x1f3deb */
  /* relift: cmp eax, dword ptr [ecx*4 + 0x1f9da0] -> jbe 0x1f3e32 */
  /* cmp ecx, 0x10 -> jb 0x1f3e20 */
  /* cmp eax, 0x1b -> ja 0x1f3ed5 */
  /* test ecx, ecx -> je 0x1f3f0c */
  /* cmp ecx, 7 -> ja 0x1f3f1d */
  /* cmp dl, 0x20 -> je 0x1f3f06 */
  /* cmp eax, 7 -> ja 0x1f3fc8 */
  /* test eax, eax -> jne 0x1f40f9 */
  /* cmp esi, 0xc -> je 0x1f408f */
  /* cmp esi, 0xd -> jbe 0x1f4091 */
  /* cmp esi, 0xf -> ja 0x1f4091 */
  /* cmp ebx, eax -> jle 0x1f40a0 */
  /* cmp ebx, edx -> jle 0x1f40af */
  /* cmp esi, 0xc -> je 0x1f40da */
  /* cmp esi, 0xd -> jle 0x1f40d0 */
  /* cmp esi, 0xf -> jg 0x1f40d0 */
  D3DResource_GetType();
  /* test (char)eax, 0x40 -> je 0x1f418d */
  /* relift: cmp eax, dword ptr [edx + 0x2154] -> jne 0x1f41ad */
  /* test (char)eax, 0x30 -> je 0x1f41ad */
  /* relift: FUN_001f3ff0(0, 0, 0, 0); */
  D3DResource_GetType();
  /* relift: FUN_001f3ff0(0, 0, 0, 0); */
  /* relift: FUN_001ed7c0(0, 0, 0); */
  /* cmp eax, 0xc -> je 0x1f42cc */
  /* cmp eax, 0xd -> jbe 0x1f42ce */
  /* cmp eax, 0xf -> ja 0x1f42ce */
  /* relift: cmp dword ptr [esp + 0x10], ecx -> jbe 0x1f431d */
  /* test eax, eax -> jbe 0x1f434a */
  /* test eax, eax -> jbe 0x1f4357 */
  /* test ecx, ecx -> je 0x1f43d6 */
  /* test edi, edi -> jbe 0x1f43c7 */
  /* test edx, edx -> jbe 0x1f43cc */
  /* cmp edi, eax -> ja 0x1f43f9 */
  /* cmp ecx, 0xc -> je 0x1f442d */
  /* cmp ecx, 0xd -> jle 0x1f441a */
  /* cmp ecx, 0xf -> jg 0x1f441a */
  /* test (char)ebx, 0x20 -> jne 0x1f44b0 */
  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* test eax, eax -> je 0x1f4578 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f4590 */
void Lock3DSurface(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* cmp edi, 0xc -> je 0x1f46b2 */
  /* cmp edi, 0xd -> jbe 0x1f4667 */
  /* cmp edi, 0xf -> jbe 0x1f46b2 */
  /* relift: FUN_001f3cc0(0, 0); */
  /* relift: FUN_001f3cc0(0, 0); */
  /* relift: FUN_001f3cc0(0, 0); */
  /* cmp edi, 0xd -> jbe 0x1f46f4 */
  /* cmp edi, 0xf -> ja 0x1f46f4 */
  /* cmp esi, ecx -> jbe 0x1f4717 */
  /* cmp edx, ecx -> jbe 0x1f4748 */
  /* test edx, edx -> jbe 0x1f476f */
  /* test ebp, ebp -> jbe 0x1f4774 */
  /* test ecx, 0x10000 -> je 0x1f4851 */
  /* test ecx, 0x200000 -> je 0x1f485e */
  /* test ecx, 0x1000000 -> je 0x1f486d */
  /* test ecx, 0x2000000 -> je 0x1f487d */

  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f4880 */
void CMiniport_GetDisplayCapabilities(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [0x1fb468], eax -> jne 0x1f4899 */
  /* relift: tail-call CMiniport_GetDisplayCapabilities(); */
  /* cmp ebp, 0x8f4 -> jb 0x1f48c7 */
  /* cmp edx, eax -> jae 0x1f490d */
  /* relift: cmp ecx, dword ptr [esp + 0x14] -> je 0x1f490d */
  /* cmp edx, eax -> jb 0x1f48f5 */
  /* relift: FUN_001f3cd0(0, 0, 0, 0); */
  /* relift: FUN_001f3dd0(0); */
  /* relift: FUN_001f489f(0, 0); */
  /* relift: tail-call CMiniport_GetDisplayCapabilities(); */
  /* relift: cmp dword ptr [ebp - 0xc], 4 -> jne 0x1f498e */
  /* relift: cmp dword ptr [ebp + 0x10], eax -> je 0x1f49b1 */
  /* relift: cmp dword ptr [ebp + 0x10], 0x32 -> je 0x1f49aa */
  /* relift: cmp dword ptr [ebp + 0x10], 0x3c -> jne 0x1f49b1 */
  /* relift: cmp dword ptr [ebp - 0xc], 4 -> jne 0x1f49d1 */
  /* relift: test dword ptr [ebp - 0x14], edi -> jne 0x1f49d1 */
  /* test edi, 0xe0000 -> jne 0x1f4a4b */
  /* relift: cmp eax, dword ptr [ebp + 8] -> jne 0x1f4a4b */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jne 0x1f4a4b */
  /* test (char)eax, 1 -> jne 0x1f4a4b */
  /* test (char)eax, 1 -> jne 0x1f4a4b */
  /* test (char)eax, 1 -> jne 0x1f4a4b */
  /* test eax, edi -> je 0x1f4a4b */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x1f4a62 */
  /* relift: test byte ptr [ebp - 4], 0x20 -> je 0x1f4a3d */
  /* test edi, 0x200000 -> jne 0x1f4a62 */
  /* relift: test byte ptr [ebp - 4], 0x40 -> je 0x1f4a4b */
  /* test edi, 0x200000 -> je 0x1f4a62 */
  /* relift: cmp eax, dword ptr [ebp - 0x18] -> je 0x1f49be */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x001f4aa0 */
void CMiniport_IsFlipPending(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test ecx, ecx -> jne 0x1f4b12 */
  /* test ecx, ecx -> je 0x1f4bd7 */
  /* test eax, eax -> je 0x1f4bd7 */
  /* test eax, 0x1000000 -> je 0x1f4bb4 */
  /* relift: cmp dword ptr [esi + ecx*8 + 0x1b4], 1 -> jne 0x1f4b8b */
  /* relift: cmp dword ptr [esi + 4], 2 -> jne 0x1f4b7c */
  /* test (char)eax, 1 -> je 0x1f4b8b */
  /* mem[0x001fe6b4] = ecx */
  /* cmp eax, 0x80000000 -> jne 0x1f4bb4 */
  /* relift: test dword ptr [esi + 0x208], 0x200000 -> je 0x1f4bb4 */
  /* relift: FUN_001efe80(0); */
  /* cmp eax, ebx -> jne 0x1f4cc0 */
  /* relift: cmp dword ptr [esi + 4], 2 -> jne 0x1f4c31 */
  /* test (char)ebx, (char)eax -> je 0x1f4cc0 */
  /* relift: FUN_001efe80(0, 0); */
  /* relift: cmp dword ptr [esi + ebp*4 + 0x814], ebx -> jne 0x1f4c84 */
  /* relift: FUN_001eff04(0); */
  /* relift: test dword ptr [edi + 0x100], 0x1000000 -> jne 0x1f4cc0 */
  /* test eax, eax -> je 0x1f4d09 */
  /* test (char)ecx, 1 -> je 0x1f4d37 */
  /* cmp edx, -1 -> je 0x1f4d8d */
  /* cmp edx, -1 -> jne 0x1f4d60 */
  /* relift: cmp dword ptr [esp + 0x14], 0x308 -> jne 0x1f4db6 */
  /* relift: FUN_001efe80(0); */
  /* relift: cmp dword ptr [esi + edi*4 + 0x814], 1 -> jne 0x1f4e38 */
  /* relift: FUN_001eff04(0); */
  /* relift: FUN_001f4d40(0, 0); */
  /* relift: FUN_001ef860(0, 0); */
  /* relift: FUN_001f6135(0, 0); */
  /* test edx, edx -> jne 0x1f5010 */
  /* relift: FUN_001f8d2e(0); */
  /* test (char)ebx, 0x10 -> je 0x1f5033 */
  /* test ebx, 0x100000 -> je 0x1f505b */
  /* test dl, 0x40 -> je 0x1f505b */
  /* test ebx, ebx -> je 0x1f510a */
  /* cmp ebx, 0x1000000 -> je 0x1f510a */
  /* test (char)ebx, 0x10 -> je 0x1f509c */
  /* test ecx, ecx -> jne 0x1f5092 */
  /* test edx, edx -> je 0x1f50f1 */
  /* test (char)ebx, 1 -> jne 0x1f50ad */
  /* test ebx, 0x100000 -> je 0x1f50f1 */
  /* cmp ebp, 0x100 -> jne 0x1f50d9 */
  /* relift: FUN_001f4dc0(0, 0); */
  DbgPrint(0x001fb2d8, 0, 0, 0);
  /* test ebx, 0x10000 -> je 0x1f510a */
  /* test ecx, ecx -> jne 0x1f5100 */
  /* test eax, 0x1000000 -> je 0x1f5161 */
  /* test (char)ebx, dl -> je 0x1f51b0 */
  /* test (char)eax, 0x10 -> je 0x1f519e */
  /* test (char)edx, 0x10 -> je 0x1f521a */
  DbgPrint(0x001fb360, 0);
  DbgPrint(0x001fb354, 0);
  DbgPrint(0x001fb348, 0);
  /* cmp eax, ecx -> je 0x1f521a */
  /* test (char)eax, 0x10 -> je 0x1f528a */
  /* test (char)eax, 0x10 -> jne 0x1f5263 */
  /* relift: cmp dword ptr [esi + 0x2100], edi -> jne 0x1f5263 */
  /* relift: cmp dword ptr [esi + 0x400100], edi -> je 0x1f5247 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* relift: test dword ptr [esi + 0x100], 0x1000000 -> je 0x1f525a */
  /* relift: FUN_001f4be0(0, 0); */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f5230 */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f528a */
  /* relift: test byte ptr [esi + 0x2500], 0x10 -> jne 0x1f5270 */
  /* relift: cmp dword ptr [esi + 0x2100], edi -> jne 0x1f529e */
  /* test esi, 0x100000 -> je 0x1f52f0 */
  /* test esi, 0x1000000 -> je 0x1f5301 */
  /* relift: FUN_001f4be0(0, 0); */
  /* test esi, 0x1000 -> je 0x1f5312 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* test esi, 0x100 -> jne 0x1f5323 */
  /* relift: test byte ptr [ebp + 0x2080], 1 -> je 0x1f532c */
  /* relift: FUN_001f5130(0, 0); */
  /* test esi, 0x10000 -> je 0x1f5349 */
  /* relift: test byte ptr [eax + 0x8100], 1 -> je 0x1f5349 */
  /* test edi, edi -> jne 0x1f52d0 */
  FUN_001d0bb9(64, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f5390 */
void D3D_AllocContiguousMemory(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  XPhysicalAlloc(ecx, 0, eax, 1028);
  /* test eax, eax -> je 0x1f53c1 */
  /* cmp edi, 0x2000 -> ja 0x1f54c7 */
  XMETAL_StartPush();
  /* test esi, esi -> jne 0x1f5504 */
  CDevice_KickOff();
  /* relift: cmp ebx, dword ptr [esi] -> jne 0x1f5596 */
  /* relift: cmp edi, dword ptr [esi + 4] -> jne 0x1f5596 */
  /* relift: FUN_001ef520(0, 0); */
  /* relift: cmp ebx, dword ptr [esi] -> jne 0x1f5596 */
  /* relift: cmp edi, dword ptr [esi + 4] -> je 0x1f5588 */
  /* cmp edx, edi -> jae 0x1f55c5 */
  /* relift: FUN_001ef520(0, 0); */
  /* cmp eax, ebx -> jb 0x1f55b0 */
  /* cmp ecx, edi -> jb 0x1f55b0 */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1f56c7 */
  XMETAL_StartPush();
  /* cmp ecx, 0x100 -> jb 0x1f570a */
  /* relift: FUN_001f8127(0, 0, 0, 0); */
  /* relift: FUN_001f82b4(0); */
  /* mem[0xfd001804] = eax */
  /* mem[0xfd600140] = 0 */
  /* mem[0xfd009140] = 0 */
  /* relift: FUN_001f7660(0, 0, 0, 0); */
  /* test edx, edx -> je 0x1f58f4 */
  /* test edx, edx -> je 0x1f591b */
  /* cmp ecx, ebp -> ja 0x1f594e */
  /* cmp ebx, ebp -> jbe 0x1f5962 */
  /* relift: FUN_001f77c7(0, 0); */
  /* relift: FUN_001f78c5(0, 0); */
  /* relift: FUN_001f56e3(0); */
  /* relift: FUN_001f7994(0, 0); */
  /* relift: FUN_001f79ca(0, 0); */
  /* relift: FUN_001f79fa(0, 0); */
  /* relift: FUN_001f7ddc(0, 0); */
  /* relift: cmp word ptr [ebp - 0x18], 0x7c6 -> jle 0x1f5a2c */
  /* test (char)ecx, 3 -> jne 0x1f5a64 */
  /* relift: cmp word ptr [ebp - 0x16], 2 -> jle 0x1f5a64 */
  /* relift: FUN_001f8ed2(0, 0); */
  /* relift: FUN_001f8e51(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f5b5b */
void CMiniport_CreateCtxDmaObject(void)
{
  int eax = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: FUN_001f5b01(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp - 4], 2 -> je 0x1f5bdd */
  /* relift: cmp dword ptr [ebp - 4], 3 -> jne 0x1f5bd1 */
  /* relift: cmp dword ptr [ebp - 4], 1 -> jne 0x1f5bdd */
  /* relift: FUN_001f834f(0, 0); */
  /* relift: FUN_001f82ed(0, 0); */
  /* relift: FUN_001f5786(0); */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f5cec */
  /* relift: test byte ptr [esi + 0x2400], 0x10 -> je 0x1f5cec */
  /* relift: test byte ptr [esi + 0x3220], 0x10 -> je 0x1f5d18 */
  /* relift: FUN_001f5130(0, 0); */
  /* relift: cmp dword ptr [esi + 0x400100], 0 -> je 0x1f5d03 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* relift: test dword ptr [esi + 0x100], 0x1000000 -> je 0x1f5cd1 */
  /* relift: FUN_001f4be0(0, 0); */
  /* relift: test byte ptr [eax], 0x10 -> jne 0x1f5d2e */
  /* relift: cmp eax, dword ptr [esp + 4] -> jb 0x1f5d40 */

  (void)eax;
  (void)esi;
  (void)ebp;
}

/* 0x001f5d4d */
void CMiniport_InitHardware(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_001f5850(0, 0); */
  /* test eax, eax -> jne 0x1f5dc3 */
  /* relift: FUN_001f587b(0, 0); */
  /* test eax, eax -> je 0x1f5dbc */
  /* test (char)eax, (char)eax -> jne 0x1f5e01 */
  /* relift: FUN_001f58bc(0, 0); */
  /* test eax, eax -> je 0x1f5dfd */
  /* cmp eax, edx -> jb 0x1f5e3e */
  /* relift: FUN_001f59c6(0, 0); */
  /* relift: FUN_001f5ccb(0, 0, 0, 0); */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [ecx] -> jne 0x1f5f0f */
  /* relift: cmp eax, dword ptr [ecx + 0x400908] -> jne 0x1f5f0f */
  /* test eax, 0xffffc000 -> jne 0x1f5f0f */
  /* relift: test dword ptr [ebp + 0x18], ecx -> je 0x1f6060 */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [esi + edi*4 + 0x400980] -> jne 0x1f5fff */
  /* relift: cmp dword ptr [ebp + 0x20], 0 -> je 0x1f6060 */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [edi] -> jne 0x1f604b */
  /* relift: FUN_001f5ccb(0, 0, 0, 0); */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [ecx] -> jne 0x1f60bc */
  /* test eax, eax -> jne 0x1f615a */
  /* relift: FUN_001f6073(0, 0); */
  /* relift: cmp dword ptr [ebp - 4], 8 -> jl 0x1f615d */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f6193 */
  /* relift: test byte ptr [esi + 0x2400], 0x10 -> je 0x1f6193 */
  /* relift: test byte ptr [esi + 0x3220], 0x10 -> je 0x1f61be */
  /* relift: FUN_001f5130(0, 0); */
  /* relift: cmp dword ptr [esi + 0x400100], ebx -> je 0x1f61a9 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* relift: test dword ptr [esi + 0x100], 0x1000000 -> je 0x1f6178 */
  /* relift: FUN_001f4be0(0, 0); */
  /* relift: test byte ptr [eax], 0x10 -> jne 0x1f61c6 */
  /* relift: FUN_001f7ae3(0); */
  /* relift: cmp dword ptr [edi + 0x108], ebx -> je 0x1f6251 */
  /* relift: cmp dword ptr [ebp - 4], 0x80 -> jb 0x1f622e */
  /* relift: FUN_001f8d2e(0); */
  /* test ebx, ebx -> je 0x1f634f */
  /* test eax, eax -> jne 0x1f636c */
  /* test ecx, ecx -> je 0x1f63bf */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* cmp eax, 0xcafebeef -> jne 0x1f661a */
  /* relift: FUN_001f6310(0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0); */
  /* test edi, edi -> jne 0x1f6744 */
  /* relift: cmp dword ptr [edi + 0x1fb528], 1 -> je 0x1f6715 */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* test eax, eax -> je 0x1f68c4 */
  /* relift: cmp dword ptr [eax + 0x1fb498], 0x16 -> je 0x1f68c4 */
  /* cmp edi, ecx -> jne 0x1f6936 */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6440(0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f64b0(0, 0); */
  /* cmp eax, 1 -> jne 0x1f6ac9 */
  /* test edi, edi -> jne 0x1f6aa1 */
  /* relift: FUN_001f6510(0, 0); */
  /* relift: FUN_001f6570(0, 0); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f65d0(0xcafebeef); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f66b0(0, 0); */
  /* relift: FUN_001f6770(0, 0); */
  /* relift: FUN_001f67d0(0, 0); */
  /* cmp edi, ecx -> jne 0x1f6a9b */
  /* relift: FUN_001f6820(0, 0, 0, 0); */
  /* test ebx, ebx -> je 0x1f6bcf */
  /* test eax, eax -> jne 0x1f6bec */
  /* test ecx, ecx -> je 0x1f6c50 */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* cmp eax, 0xcafebeef -> jne 0x1f6eac */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* test ebx, ebx -> jne 0x1f6fe3 */
  /* relift: cmp dword ptr [0x1fb518], 1 -> je 0x1f6fb2 */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* test ecx, ecx -> jne 0x1f7101 */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* test eax, eax -> je 0x1f7321 */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6cd0(0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6d40(0, 0); */
  /* relift: FUN_001f6da0(0, 0); */
  /* relift: FUN_001f6e00(0, 0); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6e60(0xcafebeef); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6f50(0, 0); */
  /* relift: FUN_001f7010(0); */
  /* relift: FUN_001f7080(0); */
  /* cmp eax, 1 -> jne 0x1f7573 */
  /* cmp edi, ebx -> jne 0x1f754b */
  /* relift: FUN_001f7010(0); */
  /* relift: FUN_001f70f0(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f7180(0, 0); */
  /* relift: FUN_001f71e0(0, 0); */
  /* cmp edi, ebx -> jne 0x1f7541 */
  /* relift: FUN_001f7240(0, 0, 0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f9165 */
void D3D_ClearStateBlockFlags(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001f91a1 */
void D3DDevice_BeginStateBlock(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x001f91af */
void D3DDevice_Suspend(void)
{
  int eax = 0;
  int ecx = 0;

  CDevice_SetStateVB();
  D3DDevice_SetMaterial();
  D3DDevice_SetBackMaterial();
  D3DDevice_GetLightEnable();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_DeleteVertexShader();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetIndices();
  D3DDevice_DeletePixelShader();
  D3DDevice_SetPixelShaderConstant();

  (void)eax;
  (void)ecx;
}

/* 0x001f92f0 */
void D3D_RecordStateBlock(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test esi, esi -> je 0x1f9354 */
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp dword ptr [ebp - 0xc], ecx -> jb 0x1f932a */
  /* test (char)eax, (char)eax -> je 0x1f9387 */
  /* test esi, esi -> je 0x1f9385 */
  /* test (char)eax, (char)eax -> je 0x1f93af */
  /* test esi, esi -> je 0x1f93ad */
  /* test esi, esi -> je 0x1f93e2 */
  /* relift: FUN_001ed8f0(0); */
  /* test esi, esi -> je 0x1f9428 */
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp dword ptr [ebp - 0x14], 0xc0 -> jb 0x1f93ed */
  /* relift: cmp dword ptr [edi + 0x414], 0 -> je 0x1f9481 */
  /* test esi, esi -> je 0x1f947a */
  /* cmp ecx, 0x10 -> jb 0x1f944c */
  /* cmp ecx, 0x60 -> jb 0x1f94cd */
  /* test esi, esi -> je 0x1f94c6 */
  /* cmp ecx, 0xc0 -> jb 0x1f949c */
  /* test (char)ecx, (char)ecx -> je 0x1f950c */
  /* relift: cmp dword ptr [edi + 0x414], 0 -> jne 0x1f94f6 */
  /* cmp eax, 0x38 -> jbe 0x1f950c */
  /* cmp eax, 0x74 -> je 0x1f950c */
  /* test esi, esi -> je 0x1f9509 */
  /* cmp eax, 0x90 -> jb 0x1f94dc */
  /* test (char)ecx, (char)ecx -> je 0x1f9548 */
  /* test esi, esi -> je 0x1f9545 */
  /* cmp eax, 4 -> jb 0x1f9527 */
  /* relift: cmp dword ptr [ebp - 0x14], 0x20 -> jb 0x1f951f */
  /* test (char)eax, (char)eax -> je 0x1f95a5 */
  /* test esi, esi -> je 0x1f959e */
  /* cmp edx, 0xa -> jb 0x1f9576 */
  /* test (char)eax, (char)eax -> je 0x1f95e1 */
  /* test esi, esi -> je 0x1f95de */
  /* test (char)eax, (char)eax -> je 0x1f9613 */
  /* test esi, esi -> je 0x1f9610 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x1f9641 */
  /* test esi, esi -> je 0x1f963e */
  /* relift: cmp dword ptr [edi + 0x484], edx -> jbe 0x1f9695 */
  /* relift: test byte ptr [eax], 2 -> je 0x1f9685 */
  /* test esi, esi -> je 0x1f967e */
  /* relift: cmp edx, dword ptr [edi + 0x484] -> jb 0x1f965a */
  /* relift: cmp dword ptr [edi + 0x484], 0 -> jbe 0x1f96e1 */
  /* relift: test byte ptr [eax], 4 -> je 0x1f96cc */
  /* test esi, esi -> je 0x1f96c9 */
  D3DDevice_GetLightEnable();
  /* relift: cmp eax, dword ptr [edi + 0x484] -> jb 0x1f96ab */
  /* test esi, esi -> jne 0x1f9709 */
  FUN_001d0bb9(esi, ebx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f971e */
void D3DDevice_ApplyStateBlock(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  D3DDevice_SetTexture(0, (void *)0);
  /* relift: cmp ebx, dword ptr [edi] -> jb 0x1f9731 */
  /* relift: cmp dword ptr [edi + 4], ebp -> je 0x1f9752 */
  D3DDevice_SetPixelShader();
  /* relift: cmp dword ptr [edi + 8], ebp -> je 0x1f9761 */
  D3DDevice_SetVertexShader(0);
  /* relift: cmp dword ptr [edi + 0xc], ebp -> je 0x1f9773 */
  D3DDevice_SetIndices();
  /* relift: cmp dword ptr [edi + 0x10], ebp -> jbe 0x1f9790 */
  D3DDevice_SetStreamSource(0, (void *)0, 0);
  /* relift: cmp ebx, dword ptr [edi + 0x10] -> jb 0x1f977a */
  /* relift: cmp dword ptr [edi + 0x14], ebp -> jbe 0x1f97ad */
  D3DDevice_SetPixelShaderConstant();
  /* relift: cmp ebx, dword ptr [edi + 0x14] -> jb 0x1f9797 */
  /* relift: cmp dword ptr [edi + 0x18], ebp -> jbe 0x1f97ce */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* relift: cmp ebx, dword ptr [edi + 0x18] -> jb 0x1f97b4 */
  /* relift: cmp dword ptr [edi + 0x1c], ebp -> jbe 0x1f97f3 */
  /* relift: cmp dword ptr [eax*4 + 0x1fb698], ecx -> je 0x1f97ea */
  D3DDevice_SetRenderStateNotInline();
  /* relift: cmp ebx, dword ptr [edi + 0x1c] -> jb 0x1f97d5 */
  /* relift: cmp dword ptr [edi + 0x20], ebp -> jbe 0x1f9825 */
  /* relift: cmp dword ptr [ebp*4 + 0x1fb498], eax -> je 0x1f981a */
  D3DDevice_SetTextureStageStateNotInline();
  /* relift: cmp ebx, dword ptr [edi + 0x20] -> jb 0x1f97fa */
  /* relift: cmp dword ptr [edi + 0x24], ebp -> jbe 0x1f9840 */
  D3DDevice_SetTransform(0, (void *)(uintptr_t)eax);
  /* relift: cmp ebx, dword ptr [edi + 0x24] -> jb 0x1f982c */
  /* relift: cmp dword ptr [edi + 0x28], ebp -> je 0x1f984e */
  D3DDevice_SetViewport((void *)(uintptr_t)esi);
  /* relift: cmp dword ptr [edi + 0x2c], ebp -> je 0x1f985c */
  D3DDevice_SetMaterial();
  /* relift: cmp dword ptr [edi + 0x30], ebp -> je 0x1f986a */
  D3DDevice_SetBackMaterial();
  /* relift: cmp dword ptr [edi + 0x34], ebp -> jbe 0x1f9885 */
  D3DDevice_SetLight();
  /* relift: cmp ebx, dword ptr [edi + 0x34] -> jb 0x1f9871 */
  /* relift: cmp dword ptr [edi + 0x38], ebp -> jbe 0x1f989f */
  D3DDevice_LightEnable();
  /* relift: cmp ebx, dword ptr [edi + 0x38] -> jb 0x1f988c */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x001f98a6 */
void D3DDevice_CaptureStateBlock(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  D3DResource_Release((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x1f98e9 */
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp eax, dword ptr [esi] -> jb 0x1f98c6 */
  /* relift: cmp dword ptr [esi + 4], 0 -> je 0x1f991f */
  /* test eax, eax -> je 0x1f990b */
  D3DDevice_DeletePixelShader();
  /* test eax, eax -> je 0x1f991a */
  /* relift: cmp dword ptr [esi + 8], 0 -> je 0x1f994b */
  /* test (char)eax, 1 -> je 0x1f9931 */
  D3DDevice_DeleteVertexShader();
  /* test (char)eax, 1 -> je 0x1f9946 */
  /* relift: cmp dword ptr [esi + 0xc], 0 -> je 0x1f9982 */
  /* test eax, eax -> je 0x1f995e */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x1f9971 */
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp dword ptr [esi + 0x10], 0 -> jbe 0x1f99d1 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* relift: FUN_001ed8f0(0); */
  /* relift: cmp eax, dword ptr [esi + 0x10] -> jb 0x1f998c */
  /* relift: cmp ecx, dword ptr [eax + 0x14] -> jb 0x1f99e1 */
  /* relift: cmp dword ptr [esi + 0x18], ecx -> jbe 0x1f9a38 */
  /* relift: cmp ecx, dword ptr [eax + 0x18] -> jb 0x1f9a13 */
  /* relift: cmp dword ptr [esi + 0x1c], ecx -> jbe 0x1f9a56 */
  /* relift: cmp eax, dword ptr [esi + 0x1c] -> jb 0x1f9a41 */
  /* relift: cmp dword ptr [esi + 0x20], ecx -> jbe 0x1f9a78 */
  /* relift: cmp eax, dword ptr [esi + 0x20] -> jb 0x1f9a5d */
  /* relift: cmp dword ptr [esi + 0x24], ecx -> jbe 0x1f9aa5 */
  /* relift: cmp eax, dword ptr [ecx + 0x24] -> jb 0x1f9a82 */
  /* relift: cmp dword ptr [esi + 0x28], 0 -> je 0x1f9ac1 */
  /* relift: cmp dword ptr [esi + 0x2c], 0 -> je 0x1f9add */
  /* relift: cmp dword ptr [esi + 0x30], 0 -> je 0x1f9af9 */
  /* relift: cmp dword ptr [esi + 0x34], edx -> jbe 0x1f9b31 */
  /* relift: cmp edx, dword ptr [eax + 0x34] -> jb 0x1f9b06 */
  /* relift: cmp dword ptr [esi + 0x38], edi -> jbe 0x1f9b4c */
  D3DDevice_GetLightEnable();
  /* relift: cmp edi, dword ptr [esi + 0x38] -> jb 0x1f9b38 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x001f9b53 */
void D3DDevice_DeleteStateBlock(void)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, ebp -> je 0x1f9b76 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* relift: cmp ebx, dword ptr [edi] -> jb 0x1f9b66 */
  /* relift: cmp dword ptr [edi + 4], ebp -> je 0x1f9b8f */
  /* cmp eax, ebp -> je 0x1f9b8f */
  D3DDevice_DeletePixelShader();
  /* relift: cmp dword ptr [edi + 8], ebp -> je 0x1f9ba3 */
  /* test (char)eax, 1 -> je 0x1f9ba3 */
  D3DDevice_DeleteVertexShader();
  /* relift: cmp dword ptr [edi + 0xc], ebp -> je 0x1f9bb8 */
  /* cmp eax, ebp -> je 0x1f9bb8 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* relift: cmp dword ptr [edi + 0x10], ebp -> jbe 0x1f9bd7 */
  /* cmp eax, ebp -> je 0x1f9bd1 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* relift: cmp ebx, dword ptr [edi + 0x10] -> jb 0x1f9bc2 */
  LocalFree((void *)(uintptr_t)edi);

  (void)eax;
  (void)ebx;
  (void)edi;
  (void)ebp;
}

/* 0x001f9be4 */
void D3DDevice_CreateStateBlock(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp dword ptr [esi + 0x484], edx -> jbe 0x1f9d01 */
  /* test (char)eax, 1 -> je 0x1f9c24 */
  /* relift: cmp edx, dword ptr [esi + 0x484] -> jb 0x1f9c19 */
  D3D_ClearStateBlockFlags();
  /* relift: cmp dword ptr [esp + 0xc], 2 -> jne 0x1f9c8e */
  /* relift: relift: mov byte ptr [0x1fe6c4], 1 */
  /* cmp ecx, 4 -> jb 0x1f9c6f */
  /* relift: relift: mov byte ptr [0x1fe6c5], 1 */
  /* cmp ecx, 4 -> jb 0x1f9cb7 */
  /* relift: cmp dword ptr [esi + 0x484], edx -> jbe 0x1f9d01 */
  /* test (char)eax, 1 -> je 0x1f9cf2 */
  /* relift: cmp edx, dword ptr [esi + 0x484] -> jb 0x1f9ce7 */
  D3D_RecordStateBlock();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x001f9d0f */
void D3DDevice_EndStateBlock(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1f9d41 */
  D3DDevice_CreateStateBlock();
  D3DDevice_ApplyStateBlock();
  D3DDevice_DeleteStateBlock();
  /* relift: relift: mov byte ptr [0xa300001e], (char)eax */
  /* mem[0xa420001e] = eax */

  (void)eax;
  (void)ebp;
}

/* 0x0020368b */
void DirectSoundEnterCriticalSection(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, (char)eax -> je 0x20369a */
  /* relift: tail-call DirectSoundEnterCriticalSection(); */
  /* relift: cmp dword ptr [ecx], 0 -> je 0x2036d3 */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* test eax, eax -> je 0x20377c */
  /* test eax, eax -> je 0x20378d */
  /* test eax, eax -> je 0x20379e */
  CMcpxAPU_Commit3dSettings();
  /* relift: FUN_00207be4(0, 0, 0, 0); */
  /* test eax, eax -> jl 0x2037d4 */
  /* relift: FUN_00207876(0, 0); */

  (void)eax;
  (void)ecx;
}

/* 0x0020380b */
void CMcpxAPU_ServiceDeferredCommandsLow(void)
{
  int esi = 0;
  int ebp = 0;

  /* test esi, esi -> je 0x20740c */
  /* relift: test byte ptr [esi + 8], 4 -> jne 0x20740c */
  /* relift: FUN_00207392(0); */
  /* relift: FUN_002071ac(0, 0); */
  /* relift: FUN_00207032(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x207440 */

  (void)esi;
  (void)ebp;
}

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

/* 0x0020384b */
void IDirectSound_AddRef(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x00203861 */
void IDirectSound_Release(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x00203877 */
void IDirectSoundBuffer_Unlock(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x00203881 */
void IDirectSoundBuffer_AddRef(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x00203897 */
void IDirectSoundBuffer_Release(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x002038d9 */
void DirectSoundGetSampleTime(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x002038df */
void DirectSoundUseFullHRTF(void)
{
  DirectSoundEnterCriticalSection();
  /* mem[0x00222d64] = 0x20a2f5 */
}

/* 0x002038fe */
void DirectSoundUseLightHRTF(void)
{
  DirectSoundEnterCriticalSection();
  /* mem[0x00222d64] = 0x20a431 */
}

/* 0x00203936 */
void DSound_CRefCount_AddRef(void)
{
  DirectSoundEnterCriticalSection();
}

/* 0x0020395b */
void DSound_CRefCount_Release(void)
{
  int eax = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* test edi, edi -> je 0x203987 */
  /* test eax, eax -> je 0x2039aa */

  (void)eax;
  (void)edi;
}

/* 0x002039b7 */
void CDirectSound_GetCaps(void)
{
  int ebx = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* relift: FUN_0020376b(0, 0, 0); */
  /* test edi, edi -> jl 0x2039f0 */
  /* test ebx, ebx -> je 0x2039ff */

  (void)ebx;
  (void)edi;
}

/* 0x00203a07 */
void CDirectSound_GetSpeakerConfig(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x00203a21 */
void CDirectSound_DownloadEffectsImage(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203995(0); */
  /* relift: FUN_002037ad(0, 0, 0); */
}

/* 0x00203a65 */
void CDirectSound_SetEffectData(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00207aca(0, 0, 0, 0); */
}

/* 0x00203ab0 */
void CDirectSound_GetEffectData(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00207b73(0, 0, 0, 0); */
}

/* 0x00203af2 */
void CDirectSound_CommitEffectData(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00207876(0, 0); */
}

/* 0x00203b25 */
void CDirectSound_SetMixBinHeadroom(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_SetMixBinHeadroom();
}

/* 0x00203b5a */
void CDirectSound_SetAllParameters(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Set3dParameters();
}

/* 0x00203b95 */
void CDirectSound_SetDistanceFactor(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Set3dDistanceFactor();
}

/* 0x00203bd4 */
void CDirectSound_SetDopplerFactor(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Set3dDopplerFactor();
}

/* 0x00203c13 */
void CDirectSound_SetRolloffFactor(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Set3dRolloffFactor();
}

/* 0x00203c52 */
void CDirectSound_SetOrientation(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_002072d1(0, 0, 0); */
}

/* 0x00203cba */
void CDirectSound_SetPosition(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Set3dPosition();
}

/* 0x00203d0c */
void CDirectSound_SetVelocity(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Set3dVelocity();
}

/* 0x00203d5e */
void CDirectSound_SetI3DL2Listener(void)
{
  int ecx = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* relift: cmp dword ptr [ecx + 0xc], -1 -> jne 0x203d7b */
  CMcpxAPU_SetI3DL2Listener();
  /* test edi, edi -> je 0x203da2 */

  (void)ecx;
  (void)edi;
}

/* 0x00203da9 */
void CDirectSound_CommitDeferredSettings(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxAPU_Commit3dSettings();
}

/* 0x00203dd4 */
void CDirectSound_GetTime(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x00203de3 */
void CDirectSound_DoWork(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_002073d9(0, 0); */
}

/* 0x00203e0a */
void CDirectSound_EnableHeadphones(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  /* cmp ecx, edx -> je 0x203ebf */
  /* relift: FUN_00206df8(0); */
  /* test edi, edi -> jl 0x203ebe */
  /* cmp ecx, -1 -> je 0x203ebe */
  /* relift: FUN_00207b73(0, 0, 0, 52); */
  /* test edi, edi -> jl 0x203ebe */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x203e99 */
  /* relift: FUN_00207aca(0, 0, 0, 52); */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x203ed0 */
  /* relift: test byte ptr [ecx + 0xc], 0x10 -> je 0x203f16 */
  /* test eax, eax -> jne 0x203f2c */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x00203f32 */
void CDirectSoundVoice_SetPitch(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetPitch();
}

/* 0x00203f69 */
void CDirectSoundVoice_SetVolume(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00209880(0, 0); */
}

/* 0x00203fa3 */
void CDirectSoundVoice_SetLFO(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetLFO();
}

/* 0x00203fd4 */
void CDirectSoundVoice_SetEG(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetEG();
}

/* 0x00204005 */
void CDirectSoundVoice_SetFilter(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetFilter();
}

/* 0x00204036 */
void CDirectSoundVoice_SetHeadroom(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00209880(0, 0); */
}

/* 0x00204075 */
void CDirectSoundVoice_SetMixBinVolumes(void)
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

/* 0x002040e9 */
void CDirectSoundVoice_SetAllParameters(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dParameters();
}

/* 0x00204124 */
void CDirectSoundVoice_SetConeAngles(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_0020a11d(0, 0, 0); */
}

/* 0x00204163 */
void CDirectSoundVoice_SetConeOrientation(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dConeOrientation();
}

/* 0x002041b5 */
void CDirectSoundVoice_SetConeOutsideVolume(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dConeOutsideVolume();
}

/* 0x002041f0 */
void CDirectSoundVoice_SetMaxDistance(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dMaxDistance();
}

/* 0x0020422f */
void CDirectSoundVoice_SetMinDistance(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dMinDistance();
}

/* 0x0020426e */
void CDirectSoundVoice_SetMode(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dMode();
}

/* 0x002042a9 */
void CDirectSoundVoice_SetPosition(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dPosition();
}

/* 0x002042fb */
void CDirectSoundVoice_SetVelocity(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dVelocity();
}

/* 0x0020434d */
void CDirectSoundVoice_SetI3DL2Source(void)
{
  int eax = 0;

  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_SetI3DL2Source();
  /* test eax, eax -> jne 0x204397 */

  (void)eax;
}

/* 0x002043a4 */
void CDirectSoundBuffer_PlayEx(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxBuffer_Play();
}

/* 0x002043e1 */
void CDirectSoundBuffer_StopEx(void)
{
  int eax = 0;

  DirectSoundEnterCriticalSection();
  /* test (char)eax, 3 -> je 0x20440d */
  /* relift: FUN_0020badd(0, 0, 0); */
  CMcpxBuffer_Stop();

  (void)eax;
}

/* 0x00204437 */
void CDirectSoundBuffer_GetStatus(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxBuffer_GetStatus();
}

/* 0x00204468 */
void CDirectSoundBuffer_SetLoopRegion(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  DirectSoundEnterCriticalSection();
  /* relift: cmp eax, dword ptr [ecx + 0x50] -> jne 0x20448d */
  /* relift: cmp edx, dword ptr [ecx + 0x54] -> je 0x20449e */
  /* relift: FUN_00204388(0, 0); */
  /* relift: FUN_0020b856(0, 0); */
  /* test ebx, ebx -> je 0x2044ad */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x002044b5 */
void CDirectSoundBuffer_GetCurrentPosition(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxBuffer_GetCurrentPosition();
}

/* 0x002044ea */
void CDirectSoundBuffer_Lock(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  CDirectSoundBuffer_GetCurrentPosition();
  /* relift: test byte ptr [ebp + 0x24], 2 -> je 0x204526 */
  /* test ecx, ecx -> je 0x204575 */
  /* cmp ebx, eax -> jae 0x20456f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)ebp;
}

/* 0x00204590 */
void CDirectSoundBuffer_SetCurrentPosition(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  CMcpxBuffer_SetCurrentPosition();
  /* relift: cmp dword ptr [esi + 0x24], edi -> je 0x204600 */
  /* relift: cmp dword ptr [esi + 0x28], edi -> jbe 0x204600 */
  /* cmp ecx, ebx -> jb 0x2045f9 */
  /* cmp ecx, edx -> jae 0x2045ff */
  /* relift: cmp edi, dword ptr [esi + 0x28] -> jb 0x2045d8 */
  /* relift: cmp dword ptr [edi + 0x24], 0 -> je 0x204633 */
  /* test esi, esi -> jbe 0x204632 */
  /* relift: cmp dword ptr [eax - 8], -1 -> jne 0x204632 */
  /* test esi, esi -> jbe 0x204665 */
  /* relift: cmp edi, dword ptr [ecx] -> jbe 0x20465f */
  /* relift: FUN_00203704(0, 0); */
  /* cmp edx, esi -> jb 0x204644 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x0020466c */
void CDirectSoundStream_GetInfo(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203815(0, 0); */
}

/* 0x002046b7 */
void CDirectSoundStream_Discontinuity(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxStream_Discontinuity();
}

/* 0x002046e4 */
void CDirectSoundStream_Flush(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxStream_Flush();
}

/* 0x00204711 */
void CDirectSoundStream_GetStatus__r1(void)
{
  DirectSoundEnterCriticalSection();
  /* relift: FUN_0020bc71(0, 0); */
}

/* 0x00204746 */
void CDirectSoundStream_Process(void)
{
  int eax = 0;

  /* relift: FUN_0020bc71(0); */
  /* test eax, eax -> jne 0x20475e */
  /* relift: FUN_0020c636(0); */

  (void)eax;
}

/* 0x0020476e */
void CDirectSoundStream_Pause(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  CMcpxStream_Pause();
  /* test edx, edx -> je 0x2047aa */
  /* relift: cmp eax, dword ptr [ecx + 4] -> jne 0x2047bf */
  /* test esi, esi -> je 0x2047d9 */
  /* test ecx, ecx -> je 0x2047f2 */
  /* test ecx, ecx -> je 0x204808 */
  /* test ecx, ecx -> je 0x20481e */
  /* test ecx, ecx -> je 0x204834 */
  /* test ecx, ecx -> je 0x20484a */
  /* test esi, esi -> je 0x20485c */
  /* test esi, esi -> je 0x204871 */
  /* test ecx, ecx -> je 0x20488a */
  /* test ecx, ecx -> je 0x2048a0 */
  /* test esi, esi -> je 0x2048b2 */
  /* test esi, esi -> je 0x2048c7 */
  /* test ecx, ecx -> je 0x2048e0 */
  /* test ecx, ecx -> je 0x2048f6 */
  /* test ecx, ecx -> je 0x20490c */
  /* test ecx, ecx -> je 0x204922 */
  /* test edx, edx -> je 0x204949 */
  /* test edi, edi -> je 0x204968 */
  /* test ebx, ebx -> je 0x204968 */
  /* cmp edi, edx -> jne 0x204962 */
  /* cmp ebx, esi -> jne 0x20496d */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

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

/* 0x002049aa */
void CDirectSoundBuffer_SetConeOrientation(void)
{
  CDirectSoundVoice_SetConeOrientation();
}

/* 0x002049d3 */
void CDirectSoundBuffer_SetConeOutsideVolume(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dConeOutsideVolume();
  DirectSoundEnterCriticalSection();
}

/* 0x002049d8 */
void CDirectSoundBuffer_SetMaxDistance(void)
{
  CDirectSoundVoice_SetMaxDistance();
}

/* 0x002049f0 */
void CDirectSoundBuffer_SetMinDistance(void)
{
  CDirectSoundVoice_SetMinDistance();
}

/* 0x00204a08 */
void CDirectSoundBuffer_SetMode(void)
{
  DirectSoundEnterCriticalSection();
  CMcpxVoiceClient_Set3dMode();
  DirectSoundEnterCriticalSection();
}

/* 0x00204a0d */
void CDirectSoundBuffer_SetPosition(void)
{
  CDirectSoundVoice_SetPosition();
}

/* 0x00204a36 */
void CDirectSoundBuffer_SetVelocity(void)
{
  CDirectSoundVoice_SetVelocity();
}

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

/* 0x00204a64 */
void CDirectSoundStream_SetPitch(void)
{
  CDirectSoundVoice_SetPitch();
}

/* 0x00204a78 */
void CDirectSoundStream_SetVolume(void)
{
  CDirectSoundVoice_SetVolume();
}

/* 0x00204a8c */
void CDirectSoundStream_SetLFO(void)
{
  CDirectSoundVoice_SetLFO();
}

/* 0x00204aa0 */
void CDirectSoundStream_SetEG(void)
{
  CDirectSoundVoice_SetEG();
}

/* 0x00204ab4 */
void CDirectSoundStream_SetFilter(void)
{
  CDirectSoundVoice_SetFilter();
}

/* 0x00204ac8 */
void CDirectSoundStream_SetHeadroom(void)
{
  CDirectSoundVoice_SetHeadroom();
}

/* 0x00204adc */
void CDirectSoundStream_SetMixBinVolumes_12(void)
{
  CDirectSoundVoice_SetMixBinVolumes();
}

/* 0x00204af4 */
void CDirectSoundStream_SetAllParameters(void)
{
  CDirectSoundVoice_SetAllParameters();
}

/* 0x00204b0c */
void CDirectSoundStream_SetConeAngles(void)
{
  CDirectSoundVoice_SetConeAngles();
}

/* 0x00204b28 */
void CDirectSoundStream_SetConeOrientation(void)
{
  CDirectSoundVoice_SetConeOrientation();
}

/* 0x00204b55 */
void CDirectSoundStream_SetConeOutsideVolume(void)
{
  CDirectSoundVoice_SetConeOutsideVolume();
}

/* 0x00204b6d */
void CDirectSoundStream_SetMaxDistance(void)
{
  CDirectSoundVoice_SetMaxDistance();
}

/* 0x00204b89 */
void CDirectSoundStream_SetMinDistance(void)
{
  CDirectSoundVoice_SetMinDistance();
}

/* 0x00204ba5 */
void CDirectSoundStream_SetMode(void)
{
  CDirectSoundVoice_SetMode();
}

/* 0x00204bbd */
void CDirectSoundStream_SetPosition(void)
{
  CDirectSoundVoice_SetPosition();
}

/* 0x00204bea */
void CDirectSoundStream_SetVelocity(void)
{
  CDirectSoundVoice_SetVelocity();
}

/* 0x00204c17 */
void CDirectSoundStream_SetI3DL2Source(void)
{
  CDirectSoundVoice_SetI3DL2Source();
  IDirectSound_AddRef();
  IDirectSound_AddRef();
}

/* 0x00204c5d */
void IDirectSound_GetCaps(void)
{
  CDirectSound_GetCaps();
}

/* 0x00204c79 */
void IDirectSound_GetSpeakerConfig(void)
{
  CDirectSound_GetSpeakerConfig();
}

/* 0x00204c95 */
void IDirectSound_DownloadEffectsImage(void)
{
  CDirectSound_DownloadEffectsImage();
}

/* 0x00204cbc */
void IDirectSound_GetEffectData(void)
{
  CDirectSound_GetEffectData();
}

/* 0x00204ce3 */
void IDirectSound_SetEffectData(void)
{
  CDirectSound_SetEffectData();
}

/* 0x00204d0d */
void IDirectSound_CommitEffectData(void)
{
  CDirectSound_CommitEffectData();
}

/* 0x00204d25 */
void IDirectSound_EnableHeadphones(void)
{
  CDirectSound_EnableHeadphones();
}

/* 0x00204d41 */
void IDirectSound_SetMixBinHeadroom(void)
{
  CDirectSound_SetMixBinHeadroom();
}

/* 0x00204d61 */
void IDirectSound_SetAllParameters(void)
{
  CDirectSound_SetAllParameters();
}

/* 0x00204d81 */
void IDirectSound_SetDistanceFactor(void)
{
  CDirectSound_SetDistanceFactor();
}

/* 0x00204da5 */
void IDirectSound_SetDopplerFactor(void)
{
  CDirectSound_SetDopplerFactor();
}

/* 0x00204dc9 */
void IDirectSound_SetOrientation(void)
{
  CDirectSound_SetOrientation();
}

/* 0x00204e13 */
void IDirectSound_SetPosition(void)
{
  CDirectSound_SetPosition();
}

/* 0x00204e48 */
void IDirectSound_SetRolloffFactor(void)
{
  CDirectSound_SetRolloffFactor();
}

/* 0x00204e6c */
void IDirectSound_SetVelocity(void)
{
  CDirectSound_SetVelocity();
}

/* 0x00204ea1 */
void IDirectSound_CommitDeferredSettings(void)
{
  CDirectSound_CommitDeferredSettings();
}

/* 0x00204eb9 */
void IDirectSound_GetTime(void)
{
  CDirectSound_GetTime();
}

/* 0x00204ed5 */
void IDirectSound_SetI3DL2Listener(void)
{
  CDirectSound_SetI3DL2Listener();
  IDirectSoundBuffer_AddRef();
  IDirectSoundBuffer_AddRef();
  CDirectSoundVoice_SetVolume();
  CDirectSoundVoice_SetPitch();
}

/* 0x00204f5b */
void IDirectSoundBuffer_SetLFO(void)
{
  CDirectSoundVoice_SetLFO();
}

/* 0x00204f77 */
void IDirectSoundBuffer_SetEG(void)
{
  CDirectSoundVoice_SetEG();
}

/* 0x00204f93 */
void IDirectSoundBuffer_SetFilter(void)
{
  CDirectSoundVoice_SetFilter();
}

/* 0x00204faf */
void IDirectSoundBuffer_SetHeadroom(void)
{
  CDirectSoundVoice_SetHeadroom();
}

/* 0x00204fcb */
void IDirectSoundBuffer_SetMixBinVolumes_12(void)
{
  CDirectSoundVoice_SetMixBinVolumes();
}

/* 0x00204feb */
void IDirectSoundBuffer_SetAllParameters(void)
{
  CDirectSoundVoice_SetAllParameters();
}

/* 0x0020500b */
void IDirectSoundBuffer_SetConeAngles(void)
{
  CDirectSoundVoice_SetConeAngles();
}

/* 0x0020502f */
void IDirectSoundBuffer_SetConeOrientation(void)
{
  CDirectSoundBuffer_SetConeOrientation();
}

/* 0x00205064 */
void IDirectSoundBuffer_SetConeOutsideVolume(void)
{
  CDirectSoundVoice_SetConeOutsideVolume();
}

/* 0x00205084 */
void IDirectSoundBuffer_SetMaxDistance(void)
{
  CDirectSoundBuffer_SetMaxDistance();
}

/* 0x002050a8 */
void IDirectSoundBuffer_SetMinDistance(void)
{
  CDirectSoundBuffer_SetMinDistance();
}

/* 0x002050cc */
void IDirectSoundBuffer_SetMode(void)
{
  CDirectSoundVoice_SetMode();
}

/* 0x002050ec */
void IDirectSoundBuffer_SetPosition(void)
{
  CDirectSoundBuffer_SetPosition();
}

/* 0x00205121 */
void IDirectSoundBuffer_SetVelocity(void)
{
  CDirectSoundBuffer_SetVelocity();
}

/* 0x00205156 */
void IDirectSoundBuffer_PlayEx(void)
{
  CDirectSoundBuffer_PlayEx();
}

/* 0x0020517a */
void IDirectSoundBuffer_StopEx(void)
{
  CDirectSoundBuffer_StopEx();
  CDirectSoundBuffer_SetLoopRegion();
}

/* 0x002051be */
void IDirectSoundBuffer_GetStatus(void)
{
  CDirectSoundBuffer_GetStatus();
}

/* 0x002051da */
void IDirectSoundBuffer_GetCurrentPosition(void)
{
  CDirectSoundBuffer_GetCurrentPosition();
  CDirectSoundBuffer_SetCurrentPosition();
}

/* 0x00205216 */
void IDirectSoundBuffer_Lock(void)
{
  CDirectSoundBuffer_Lock();
}

/* 0x00205246 */
void IDirectSoundBuffer_SetI3DL2Source(void)
{
  CDirectSoundVoice_SetI3DL2Source();
  CDirectSoundVoice_SetVolume();
}

/* 0x0020527a */
void IDirectSoundStream_SetPitch(void)
{
  CDirectSoundVoice_SetPitch();
}

/* 0x0020528e */
void IDirectSoundStream_SetLFO(void)
{
  CDirectSoundVoice_SetLFO();
}

/* 0x002052a2 */
void IDirectSoundStream_SetEG(void)
{
  CDirectSoundVoice_SetEG();
}

/* 0x002052b6 */
void IDirectSoundStream_SetFilter(void)
{
  CDirectSoundVoice_SetFilter();
}

/* 0x002052ca */
void IDirectSoundStream_SetHeadroom(void)
{
  CDirectSoundVoice_SetHeadroom();
}

/* 0x002052de */
void IDirectSoundStream_SetMixBinVolumes_12(void)
{
  CDirectSoundVoice_SetMixBinVolumes();
  CDirectSoundVoice_SetAllParameters();
  CDirectSoundVoice_SetConeAngles();
}

/* 0x002052ed */
void IDirectSoundStream_SetConeOrientation(void)
{
  CDirectSoundStream_SetConeOrientation();
  CDirectSoundStream_SetMaxDistance();
  CDirectSoundStream_SetMinDistance();
}

/* 0x0020534b */
void IDirectSoundStream_SetMode(void)
{
  CDirectSoundVoice_SetMode();
  CDirectSoundVoice_SetPosition();
}

/* 0x00205350 */
void IDirectSoundStream_SetPosition(void)
{
  CDirectSoundStream_SetPosition();
}

/* 0x00205379 */
void IDirectSoundStream_SetVelocity(void)
{
  CDirectSoundStream_SetVelocity();
}

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

/* 0x002053ac */
void DirectSoundDoWork(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* test eax, eax -> je 0x2053c3 */
  CDirectSound_DoWork();
  /* relift: FUN_00203664(0); */
  /* cmp ecx, 2 -> ja 0x205422 */
  /* test eax, 0xfffc0000 -> je 0x205427 */
  FUN_001d4507();
  /* relift: FUN_00203995(0); */
  /* relift: FUN_00203664(0); */
  /* mem[0x00222ce0] = eax */
  /* relift: FUN_002047f5(0, 0); */
  /* relift: FUN_0020480b(0); */
  /* relift: FUN_0020484d(0, 0, 0); */
  /* test (char)eax, 0x10 -> jne 0x2054cb */
  /* cmp ecx, edi -> je 0x2054e8 */
  /* relift: FUN_0020cb4b(0); */
  /* relift: FUN_00203f07(0, 0); */
  XAudioCalculatePitch();
  /* relift: FUN_00204821(0, 0); */
  /* relift: FUN_00204862(0); */
  /* relift: FUN_0020478b(0, 0); */
  /* relift: FUN_002047df(0); */
  /* relift: FUN_00204877(0); */
  /* relift: FUN_0020488d(0); */
  /* relift: FUN_002048a3(0, 0); */
  /* relift: FUN_002048b8(0); */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x002055a1 */
void CDirectSoundVoice_SetFrequency(void)
{
  int eax = 0;

  DirectSoundEnterCriticalSection();
  /* test eax, eax -> jne 0x2055bf */
  XAudioCalculatePitch();
  CDirectSoundVoice_SetPitch();

  (void)eax;
}

/* 0x002055e4 */
void CDirectSoundVoice_SetOutputBuffer(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  /* cmp esi, eax -> je 0x205636 */
  /* test eax, eax -> je 0x20561f */
  /* relift: FUN_002090ca(0, 0); */
  /* test ebx, ebx -> jl 0x205636 */
  /* relift: FUN_0020552e(0); */
  /* test esi, esi -> je 0x205636 */
  /* relift: FUN_00208f52(0, 0); */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x205647 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0x00205650 */
void CDirectSoundVoice_SetMixBins(void)
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

/* 0x002056a8 */
void CDirectSoundBufferSettings_SetBufferData(void)
{
  int ecx = 0;
  int edi = 0;

  /* relift: FUN_00203664(0); */
  /* test ecx, ecx -> je 0x2056e5 */
  /* relift: FUN_00203609(0, 0); */
  DirectSoundEnterCriticalSection();
  /* relift: FUN_002048cd(0); */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_002048e3(0); */
  /* test edi, edi -> je 0x205755 */

  (void)ecx;
  (void)edi;
}

/* 0x00205768 */
void CDirectSoundBuffer_SetBufferData(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  /* relift: cmp edi, dword ptr [eax + 0x48] -> jne 0x20578f */
  /* relift: cmp ecx, dword ptr [eax + 0x4c] -> je 0x2057c3 */
  /* relift: FUN_0020b46d(0, 0); */
  /* test ebx, ebx -> jl 0x2057c3 */
  CDirectSoundBufferSettings_SetBufferData();
  /* test ebx, ebx -> jl 0x2057c3 */
  /* test edi, edi -> je 0x2057c3 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x2057c3 */
  CMcpxBuffer_SetBufferData();
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x2057d4 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
  (void)ebp;
}

/* 0x002057dd */
void CDirectSoundBuffer_Play(void)
{
  DirectSoundEnterCriticalSection();
  CDirectSoundBuffer_PlayEx();
}

/* 0x0020580f */
void CDirectSoundBuffer_Stop(void)
{
  DirectSoundEnterCriticalSection();
  CDirectSoundBuffer_StopEx();
}

/* 0x0020583f */
void CDirectSoundBuffer_SetNotificationPositions(void)
{
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00203609(0); */
  /* relift: FUN_00204637(0, 0); */
}

/* 0x00205894 */
void CDirectSoundBuffer_SetOutputBuffer(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  CDirectSoundVoice_SetOutputBuffer();
  DirectSoundEnterCriticalSection();
  /* cmp edi, eax -> je 0x20593e */
  /* relift: FUN_002045c1(0, 0, 0); */
  CDirectSoundBuffer_GetStatus();
  /* test eax, eax -> jl 0x20593b */
  /* cmp edi, ecx -> jb 0x20591b */
  /* cmp edi, edx -> jae 0x20591b */
  /* relift: FUN_002045c1(0, 0, 0); */
  /* relift: FUN_002045c1(0, 0, 0); */
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00204605(0); */
  /* relift: FUN_002054a8(0, 0, 0, *(int *)((char *)esi + 0x14)); */
  /* test eax, eax -> jl 0x2059a8 */
  DirectSoundEnterCriticalSection();
  /* relift: FUN_002048f9(0); */
  /* relift: FUN_0020490f(0); */
  /* test edi, edi -> je 0x2059e9 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x002059f9 */
void CDirectSoundStream_AddRef(void)
{
  DSound_CRefCount_AddRef();
}

/* 0x00205a09 */
void CDirectSoundStream_Release(void)
{
  DSound_CRefCount_Release();
}

/* 0x00205a19 */
void CDirectSoundStream_SetOutputBuffer(void)
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
  IDirectSound_Release();
  /* test ecx, ecx -> je 0x205a91 */
  IDirectSoundBuffer_Release();

  (void)ebx;
  (void)ecx;
  (void)edi;
}

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

/* 0x00205ac7 */
void CDirectSoundStream_SetFrequency(void)
{
  CDirectSoundVoice_SetFrequency();
}

/* 0x00205adb */
void CDirectSoundStream_SetMixBins(void)
{
  CDirectSoundVoice_SetMixBins();
}

/* 0x00205aef */
void IDirectSoundBuffer_SetFrequency(void)
{
  CDirectSoundVoice_SetFrequency();
}

/* 0x00205b0b */
void IDirectSoundBuffer_SetOutputBuffer(void)
{
  CDirectSoundBuffer_SetOutputBuffer();
}

/* 0x00205b27 */
void IDirectSoundBuffer_SetMixBins(void)
{
  CDirectSoundVoice_SetMixBins();
  CDirectSoundBuffer_Play();
}

/* 0x00205b67 */
void IDirectSoundBuffer_Stop(void)
{
  CDirectSoundBuffer_Stop();
  CDirectSoundBuffer_SetBufferData();
}

/* 0x00205b9f */
void IDirectSoundBuffer_SetNotificationPositions(void)
{
  CDirectSoundBuffer_SetNotificationPositions();
  CDirectSoundVoice_SetFrequency();
}

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

/* 0x00205bd8 */
void IDirectSoundStream_SetMixBins(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  CDirectSoundVoice_SetMixBins();
  /* relift: FUN_0020547e(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x205c09 */
  /* relift: FUN_00203664(0); */
  DirectSoundEnterCriticalSection();
  DSound_CRefCount_Release();
  /* cmp esi, 1 -> jne 0x205c36 */
  /* relift: FUN_00205a7e(0); */
  /* test ebx, ebx -> je 0x205c45 */
  /* relift: FUN_0020552e(0); */
  /* relift: test dword ptr [esi + 0xc], 0x82000 -> jne 0x205c75 */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020480b(0); */
  /* relift: FUN_002047ca(0, 0); */
  /* relift: FUN_00205a59(0); */
  /* relift: FUN_00205547(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x205cce */
  /* relift: FUN_00203664(0); */
  CDirectSoundBufferSettings_SetBufferData();
  /* relift: FUN_002054a8(0, 0, *(int *)((char *)esi + 0xc), *(int *)((char *)esi + 0x10)); */
  /* test eax, eax -> jl 0x205d4d */
  /* test ecx, 0x80000 -> je 0x205d30 */
  /* test (char)ecx, 0x20 -> je 0x205d3c */
  /* test esi, esi -> je 0x205d4d */
  CDirectSoundBufferSettings_SetBufferData();
  /* relift: FUN_00205c86(0, 0); */
  /* relift: FUN_0020571a(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x205d87 */
  /* relift: FUN_00203664(0); */
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203609(92, 0); */
  /* test eax, eax -> je 0x205dba */
  /* relift: FUN_00205cff(0, 0, 0); */
  /* test edi, edi -> jl 0x205e34 */
  /* relift: test byte ptr [ebx + 5], 1 -> je 0x205e04 */
  /* relift: FUN_002070d6(*(int *)((char *)esi + 0x1c), 0, 0, 0); */
  /* test edi, edi -> jl 0x205e34 */
  /* relift: FUN_00205580(0, 0, *(int *)((char *)esi + 0x1c)); */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x205e46 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00205e69 */
void CDirectSoundStream_Constructor(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_00205c86(0, 0, 0); */
  /* relift: FUN_002059b0(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x205eae */
  /* relift: FUN_00203664(0); */
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203609(84, 0); */
  /* test eax, eax -> je 0x205ee1 */
  /* relift: FUN_00205979(0, 0, 0); */
  /* test edi, edi -> jl 0x205f49 */
  /* relift: FUN_00207141(*(int *)((char *)esi + 0x20), 0, *(int *)((char *)ebx + 0x10), 0); */
  /* test edi, edi -> jl 0x205f49 */
  /* relift: FUN_00205580(0, *(int *)((char *)esi + 0x20)); */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x205f5b */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00205f6d */
void CDirectSound_CreateSoundBuffer(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203609(48, 0); */
  /* cmp eax, edi -> je 0x205f94 */
  /* relift: FUN_00205d52(0); */
  /* relift: FUN_00205d8e(0, 0); */
  /* test esi, esi -> jl 0x205fcc */
  /* relift: FUN_00204821(0); */
  /* test ebx, ebx -> je 0x205fe4 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x00205fed */
void CDirectSound_CreateSoundStream(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203609(40, 0); */
  /* cmp eax, edi -> je 0x206014 */
  CDirectSoundStream_Constructor();
  /* relift: FUN_00205eb6(0, 0); */
  /* test esi, esi -> jl 0x206041 */
  /* relift: FUN_00204837(0); */
  /* test ebx, ebx -> je 0x206059 */
  /* relift: FUN_00205c4d(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20607f */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00205ce5(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x2060a3 */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00205c4d(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x2060cd */
  /* relift: FUN_00203664(0); */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x002060d4 */
void IDirectSound_CreateSoundBuffer(void)
{
  CDirectSound_CreateSoundBuffer();
}

/* 0x002060f8 */
void IDirectSound_CreateSoundStream(void)
{
  int eax = 0;
  int esi = 0;
  int ebp = 0;

  CDirectSound_CreateSoundStream();
  DirectSoundEnterCriticalSection();
  /* relift: FUN_00203609(20, 0); */
  /* test eax, eax -> je 0x206140 */
  /* relift: FUN_002053f9(0, 0); */
  /* relift: FUN_00203609(3704, 0); */
  /* test eax, eax -> je 0x20617c */
  /* relift: FUN_00206eb2(0, 0); */
  /* relift: FUN_0020763c(0); */
  /* test esi, esi -> jl 0x20620e */
  /* relift: cmp dword ptr [ebp + 8], 1 -> jae 0x20620e */
  CDirectSound_CreateSoundBuffer();
  /* test esi, esi -> jl 0x206204 */
  IDirectSoundBuffer_SetBufferData((void *)(uintptr_t)eax, (void *)0x0020f0c8, 64);
  /* test esi, esi -> jl 0x206204 */
  IDirectSoundBuffer_Play((void *)(uintptr_t)eax, 0, 0, 0);
  /* test esi, esi -> jge 0x2061bf */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x20621f */

  (void)eax;
  (void)esi;
  (void)ebp;
}

/* 0x00206232 */
void DirectSoundCreate(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  DirectSoundEnterCriticalSection();
  /* cmp eax, edi -> je 0x206265 */
  /* relift: FUN_002047ca(0); */
  /* relift: FUN_00203609(28, 0); */
  /* cmp eax, edi -> je 0x20627a */
  /* relift: FUN_0020545c(0, 0); */
  /* relift: FUN_0020611c(0); */
  /* test esi, esi -> jl 0x2062af */
  /* relift: FUN_002047df(0); */
  /* test ebx, ebx -> je 0x2062c7 */
  /* relift: tail-call DirectSoundCreate(); */
  /* test edi, edi -> jl 0x2062fe */
  IDirectSound_CreateSoundBuffer();
  /* relift: FUN_00205a68(0); */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x0020630e */
void DirectSoundCreateStream(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* cmp edx, esi -> je 0x2066fa */
  /* cmp ecx, edx -> je 0x206723 */
  /* test eax, 0x82000 -> je 0x20670f */
  /* mem[0x00222690] = eax */
  /* relift: FUN_0020d152(0); */
  /* mem[0xfe801324] = eax */
  /* mem[0xfe801334] = eax */
  /* relift: FUN_0020d152(0); */
  /* test eax, eax -> je 0x206787 */
  /* relift: cmp eax, dword ptr [0x222690] -> jne 0x20676e */
  /* relift: FUN_0020672a(0, 0, 0); */
  /* cmp eax, edi -> jne 0x2067d3 */
  /* cmp edi, ebx -> jne 0x2067be */
  /* relift: cmp dword ptr [eax], eax -> je 0x206806 */
  /* relift: FUN_0020639e(0); */
  /* cmp eax, ebx -> jne 0x2067e9 */
  /* relift: FUN_0020d780(0, 0, 0, 0); */
  /* relift: FUN_0020d118(0); */
  /* cmp edi, ebx -> jne 0x206907 */
  /* relift: cmp dword ptr [ebp - 8], ebx -> je 0x206935 */
  /* relift: cmp dword ptr [ebp - 0x1c], ecx -> jne 0x206972 */
  /* relift: cmp dword ptr [ebp - 0x20], ecx -> jne 0x20697e */
  /* relift: cmp dword ptr [ebp - 0x14], ecx -> je 0x2069fa */
  /* relift: cmp dword ptr [ebp - 0xc], ecx -> je 0x2069e4 */
  /* cmp edi, ecx -> jne 0x2069ec */
  /* relift: cmp dword ptr [ebp - 0x18], ecx -> je 0x206a13 */
  /* relift: cmp dword ptr [ebp - 0xc], ecx -> jne 0x206a07 */
  /* relift: FUN_0020639e(0); */
  /* relift: test dword ptr [esi + 8], 0x10000000 -> je 0x206a38 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00206a5e */
void CMcpxAPU_Commit3dSettings(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* mem[0x0020f140] = 0x108 */
  /* relift: test byte ptr [ebp + 8], 0x26 -> je 0x206b0e */
  /* relift: test byte ptr [ebp + 9], 1 -> je 0x206bc5 */
  /* cmp ecx, -1 -> je 0x206bc5 */
  /* relift: FUN_00207b73(0, 0, 0, 0); */
  /* test eax, eax -> jl 0x206bc5 */
  /* relift: FUN_0020ab80(0); */
  /* relift: FUN_00207aca(*(int *)((char *)ecx + 0xc), 16, 0, 0); */
  /* relift: FUN_00207aca(*(int *)((char *)ecx + 0xc), 0, 0, 0); */
  /* relift: FUN_00207876(0, 0); */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_002063b8(0); */
  /* relift: cmp dword ptr [eax], eax -> jne 0x206bdb */
  CMcpxVoiceClient_Commit3dSettings();
  /* cmp esi, eax -> jne 0x206c1d */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_0020639e(0); */
  /* cmp esi, eax -> jne 0x206c3e */
  /* relift: cmp dword ptr [ebp - 0x14], edi -> je 0x206c7c */
  /* relift: test byte ptr [eax + 8], 2 -> jne 0x206ca2 */
  /* relift: FUN_0020639e(0, 0); */
  /* cmp eax, esi -> jne 0x206ce6 */
  /* test ebx, ebx -> je 0x206d04 */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* relift: cmp eax, dword ptr [ebp - 4] -> jg 0x206d7c */
  /* relift: cmp eax, dword ptr [ebp - 8] -> ja 0x206d7c */
  /* relift: FUN_0020639e(0); */
  /* cmp esi, edi -> jne 0x206d40 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x206daa */
  /* mem[0xfe820280] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00206dc4 */
void CMcpxAPU_SetMixBinHeadroom(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: test dword ptr [esp + 4], edx -> je 0x206de8 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x206dd6 */
  /* cmp eax, 0xfe820280 -> jl 0x206dcb */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* cmp ecx, edx -> je 0x206e31 */
  /* cmp ebx, 2 -> je 0x206e54 */
  /* cmp ecx, edx -> je 0x206e54 */
  /* relift: cmp dword ptr [ebp + 8], eax -> je 0x206e7c */
  CMcpxVoiceClient_Commit3dSettings();
  /* cmp esi, edi -> jne 0x206e66 */
  /* relift: FUN_00206d25(0, 0); */
  /* relift: FUN_00206476(0, 0); */
  /* relift: FUN_0020391d(0, 0, 0); */
  /* relift: FUN_0020cc90(0, 0); */
  /* relift: FUN_0020d988(0, 0); */
  /* relift: relift: fld dword ptr [0x253f00] */
  /* relift: FUN_00206476(0, 0, 0, 0); */
  /* relift: cmp dword ptr [0x222cf0], 0 -> je 0x207065 */
  /* relift: cmp word ptr [edi], 0x13 -> jne 0x20708a */
  /* relift: cmp word ptr [ebx], 0x13 -> jne 0x2070a2 */
  /* relift: cmp dword ptr [edi], ebx -> je 0x2070b8 */
  /* relift: FUN_0020d92d(0, 0); */
  /* relift: FUN_0020d731(0, 0); */
  /* relift: FUN_00203609(560, 0, 0, 0); */
  /* test eax, eax -> je 0x2070fa */
  /* relift: FUN_0020af71(0); */
  /* relift: FUN_0020ba21(0, 0, 0); */
  /* test esi, esi -> jl 0x207130 */
  /* relift: FUN_002048cd(0); */
  /* relift: FUN_00203609(544, 0, 0, 0); */
  /* test eax, eax -> je 0x207165 */
  /* relift: FUN_0020bbe4(0); */
  /* relift: FUN_0020c0d2(0, 0, 0); */
  /* test esi, esi -> jl 0x20719b */
  /* relift: FUN_002048f9(0); */
  /* relift: test byte ptr [esi + 0x5f4], 8 -> je 0x2071d4 */
  /* relift: FUN_00206844(0, 0); */
  /* relift: test byte ptr [esi + 0x5f4], 0x40 -> je 0x2071e4 */
  /* relift: FUN_0020678c(0, 0); */
  /* relift: test byte ptr [esi + 0x5f4], 1 -> jne 0x2071c4 */
  /* relift: cmp dword ptr [edx], edx -> je 0x207231 */
  /* relift: FUN_00206870(0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00207234 */
void CMcpxAPU_Set3dParameters(void)
{
  CMcpxAPU_Commit3dSettings();
}

/* 0x00207265 */
void CMcpxAPU_Set3dDistanceFactor(void)
{
  CMcpxAPU_Commit3dSettings();
}

/* 0x00207289 */
void CMcpxAPU_Set3dDopplerFactor(void)
{
  CMcpxAPU_Commit3dSettings();
}

/* 0x002072ad */
void CMcpxAPU_Set3dRolloffFactor(void)
{
  CMcpxAPU_Commit3dSettings();
  CMcpxAPU_Commit3dSettings();
}

/* 0x00207309 */
void CMcpxAPU_Set3dPosition(void)
{
  CMcpxAPU_Commit3dSettings();
}

/* 0x00207334 */
void CMcpxAPU_Set3dVelocity(void)
{
  CMcpxAPU_Commit3dSettings();
}

/* 0x0020735f */
void CMcpxAPU_SetI3DL2Listener(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  CMcpxAPU_Commit3dSettings();
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test (char)eax, 2 -> je 0x2073c0 */
  /* relift: FUN_00206d0a(0, 0); */
  /* relift: FUN_00206ca8(0, 0); */
  /* test esi, esi -> je 0x20740c */
  /* relift: test byte ptr [esi + 8], 4 -> jne 0x20740c */
  /* relift: FUN_00207392(0); */
  /* relift: FUN_002071ac(0, 0); */
  /* relift: FUN_00207032(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x207440 */
  /* relift: FUN_00203664(0); */
  /* relift: cmp dword ptr [ecx + 0x1c8], 0 -> jne 0x207469 */
  /* relift: test dword ptr [eax + edx + 4], 0x800000 -> jne 0x207469 */
  /* test ecx, ecx -> ja 0x2074b2 */
  /* relift: cmp eax, dword ptr [ebp - 8] -> jl 0x207533 */
  /* relift: cmp eax, dword ptr [ebp - 0xc] -> jbe 0x207533 */
  /* relift: FUN_00207392(0); */
  /* cmp eax, edx -> je 0x207506 */
  /* cmp ebx, edi -> jg 0x207502 */
  /* cmp ebx, ecx -> ja 0x207502 */
  /* cmp eax, edx -> jne 0x2074ec */
  /* relift: cmp esi, dword ptr [edx] -> jne 0x207537 */
  /* relift: cmp dword ptr [esp + 4], 0x8000 -> jne 0x207553 */
  /* relift: FUN_00207447(0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_00206c83(0, 0); */
  /* relift: FUN_0020746c(0, 0); */
  /* test edi, edi -> je 0x207589 */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x207598 */
  /* relift: FUN_00207540(0, 0); */
  /* relift: FUN_0020d18c(0); */
  /* relift: FUN_0020d18c(0); */
  /* mem[0xfe801000] = ebx */
  /* test (char)ebx, 0x10 -> je 0x20760f */
  /* relift: FUN_002075a0(0, 0); */
  /* test (char)ebx, 0x48 -> je 0x207625 */
  /* relift: FUN_002075e7(0, 0); */
  /* relift: FUN_0020d780(0, 0, 0, 0); */
  /* test ebx, ebx -> jl 0x20773a */
  /* test ebx, ebx -> jl 0x20773a */
  /* test ebx, ebx -> jl 0x20773a */
  /* relift: FUN_0020d118(0); */
  /* relift: FUN_00206daa(0); */
  /* test ebx, ebx -> jl 0x20773a */
  CMcpxAPU_SetMixBinHeadroom();
  /* test ebx, ebx -> jl 0x20773a */
  CMcpxAPU_SetMixBinHeadroom();
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00203609(0, 0, 0, 0); */
  /* cmp eax, edi -> je 0x2077d9 */
  /* relift: FUN_00203609(40, 0); */
  /* cmp eax, edi -> je 0x207804 */
  /* relift: FUN_0020dc40(0, 0); */
  /* relift: FUN_0020dc83(516); */
  /* cmp ecx, edi -> je 0x20782a */
  /* relift: FUN_0020dd89(0, 0, 0); */
  /* cmp ecx, edx -> jbe 0x207864 */
  /* test edx, edx -> je 0x2078d7 */
  /* relift: cmp dword ptr [eax + 0x10], 0 -> jne 0x2078a4 */
  /* relift: FUN_0020dd34(0, 0, 0); */
  /* relift: FUN_0020dd34(0, 0, 0); */
  /* test ecx, ecx -> je 0x207924 */
  /* relift: FUN_00203664(0); */
  /* test ecx, ecx -> je 0x20793c */
  FUN_001ddda3();
  /* relift: FUN_0020dc60(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20795c */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00207928(0); */
  (void)0;
  /* relift: FUN_0020ddb1(0); */
  /* test eax, eax -> jl 0x207ac3 */
  /* relift: FUN_0020dfc2(0); */
  /* relift: FUN_0020e097(0, 0, 0); */
  /* test eax, eax -> jle 0x207a16 */
  /* test eax, eax -> jl 0x207ac3 */
  /* relift: cmp dword ptr [esi], 0 -> jbe 0x207aa4 */
  /* relift: FUN_0020e097(0, 0, 0, 0); */
  /* test eax, eax -> jle 0x207a51 */
  /* test eax, eax -> jl 0x207ac3 */
  /* relift: cmp eax, dword ptr [esi] -> jb 0x207a2e */
  /* relift: FUN_0020784f(0, 0, 0, 0); */
  /* test eax, eax -> jl 0x207b6e */
  /* relift: FUN_0020dd89(0); */
  /* relift: cmp dword ptr [ebp + 0x18], 0 -> je 0x207b35 */
  /* cmp eax, 0x8000 -> je 0x207b5e */
  /* cmp edx, esi -> jae 0x207b53 */
  /* cmp eax, ecx -> jbe 0x207b5e */
  /* cmp eax, esi -> jb 0x207b64 */
  /* relift: FUN_0020784f(0, 0, 0); */
  /* test eax, eax -> jl 0x207ba9 */
  /* test ecx, ecx -> je 0x207bc1 */
  /* relift: FUN_0020793f(0); */
  /* relift: FUN_00207bad(0, 0); */
  /* relift: FUN_00207909(0); */
  /* relift: FUN_00207928(0); */
  /* relift: FUN_0020dd89(2072, 0, 0); */
  /* relift: FUN_00207963(0); */
  /* test eax, eax -> jl 0x207c76 */
  /* test ecx, ecx -> je 0x207c6e */
  /* test (char)eax, 1 -> je 0x207cc5 */
  /* relift: relift: fcomp dword ptr [0x2c26ac] */
  /* relift: relift: fcomp dword ptr [0x2c26a8] */
  /* test (char)eax, 1 -> jne 0x207cfa */
  /* test eax, eax -> jge 0x207d14 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2548fc] */
  /* relift: FUN_00207d25(0, 0); */
  /* test eax, eax -> je 0x207df8 */
  /* test eax, eax -> jne 0x207df8 */
  /* test eax, eax -> je 0x207e16 */
  /* relift: FUN_00207dd4(0); */
  /* relift: FUN_00207e35(0, 0); */
  /* relift: FUN_0020c7ed(0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x207f23 */
  /* relift: FUN_002065d7(0); */
  /* test ecx, ecx -> je 0x207f5a */
  /* test ecx, ecx -> je 0x207f5a */
  /* cmp edx, 8 -> jae 0x207f7c */
  /* test eax, esi -> je 0x207f76 */
  /* cmp ecx, 0x20 -> jb 0x207f63 */
  /* cmp edx, 8 -> jae 0x207f97 */
  /* test eax, esi -> jne 0x207f91 */
  /* cmp ecx, 0x20 -> jb 0x207f7e */
  /* cmp ecx, 0xf -> jb 0x207fa3 */
  /* cmp ecx, 0x1f -> jb 0x207fbf */
  /* cmp eax, 8 -> jb 0x207fe7 */
  /* relift: cmp dword ptr [ecx + 0x20], 0 -> je 0x20802b */
  /* test eax, edx -> je 0x20804d */
  /* cmp ecx, 0x20 -> jb 0x208041 */
  /* cmp ecx, eax -> jb 0x20811a */
  /* cmp ecx, edx -> jae 0x20811a */
  /* relift: cmp dword ptr [ebx + 0x20], 0 -> jne 0x208122 */
  /* test eax, eax -> jg 0x208140 */
  /* cmp edi, 0x20 -> jb 0x208134 */
  /* relift: FUN_00207dd4(0, 0, 0, 0); */
  /* test ecx, 0x82000 -> je 0x20821b */
  /* relift: FUN_00207ee4(0, 0); */
  /* test eax, eax -> je 0x208256 */
  /* test ecx, ecx -> je 0x208256 */
  /* relift: test byte ptr [eax + 0xc], 0x10 -> je 0x208256 */
  /* relift: FUN_00207ee4(0, 0); */
  /* cmp esi, eax -> jg 0x208268 */
  /* cmp esi, eax -> jge 0x20826a */
  /* relift: FUN_00207df9(0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* cmp (char)eax, 3 -> jne 0x2082dc */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x2082b2 */
  /* mem[0xfe82012c] = edx */
  /* cmp ecx, edx -> jb 0x2082b2 */
  /* relift: test byte ptr [ecx + 8], 1 -> je 0x2082fd */
  /* relift: test dword ptr [ecx + 8], 0x10000000 -> jne 0x2082f4 */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* cmp eax, edi -> je 0x208391 */
  /* cmp (char)eax, 3 -> jne 0x20838a */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x208357 */
  /* mem[0xfe820140] = ebx */
  /* cmp edx, ebx -> jb 0x208357 */
  /* relift: FUN_00207d63(0); */
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* relift: FUN_00207cb2(0, 0); */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* relift: FUN_00207cb2(0, 0); */
  /* relift: FUN_00207cb2(0, 0); */
  /* test (char)eax, 0x41 -> jne 0x208574 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2c26b4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> je 0x20867d */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x20867d */
  FUN_001d9068();
  /* cmp eax, ecx -> jge 0x208684 */
  /* relift: FUN_00207d25(0, 0); */
  /* relift: FUN_00207d25(0, 0); */
  /* test edx, edx -> jge 0x20873d */
  /* test (char)eax, 1 -> jne 0x208758 */
  /* cmp edx, ecx -> jae 0x20878b */
  /* cmp eax, 1 -> jae 0x208797 */
  FUN_001d9068();
  /* cmp eax, edx -> jge 0x2087d9 */
  /* cmp edx, 2 -> je 0x208821 */
  /* cmp ecx, 0x10000 -> je 0x208821 */
  /* relift: FUN_00207cb2(0, 0); */
  /* relift: FUN_00207cb2(0, 0); */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x208899 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x253398] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x208907 */
  /* relift: FUN_00207cc8(0, 0); */
  /* relift: FUN_00207cc8(0, 0); */
  /* cmp edx, ecx -> jge 0x208965 */
  /* test eax, eax -> jg 0x2088fe */
  /* cmp eax, ecx -> jge 0x208973 */
  /* relift: relift: fld dword ptr [0x20f1a0] */
  /* test (char)eax, 0x41 -> jne 0x2089ce */
  /* relift: relift: fcomp dword ptr [0x253f34] */
  /* test (char)eax, 0x41 -> jne 0x208a1c */
  /* relift: FUN_0020a9b9(0); */
  /* cmp ecx, 2 -> je 0x208a77 */
  /* cmp eax, 0x10000 -> je 0x208a77 */
  /* relift: FUN_00207e65(0, 0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x208ab7 */
  /* mem[0xfe820160] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x208b04 */
  /* relift: cmp dword ptr [ebp - 4], 0xfe82043c -> jl 0x208ae5 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x208b4b */
  /* relift: cmp dword ptr [0xfe820010], ebx -> jb 0x208b54 */
  /* mem[0xfe82043c] = eax */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: cmp dword ptr [0xfe820010], ebx -> jb 0x208b6b */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], ebx -> jb 0x208b7b */
  /* mem[0xfe82031c] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00208da2 */
void CMcpxVoiceClient_SetFilter(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_002063cb(0, 0, 0); */
  /* test edi, edi -> jne 0x208e26 */
  /* relift: test byte ptr [ecx + 0xc], 0x10 -> je 0x208e7e */
  /* relift: cmp dword ptr [ebx + 0x58], 2 -> jne 0x208e70 */
  /* relift: test byte ptr [ebx + 8], dl -> je 0x208f3a */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x208eb3 */
  /* mem[0xfe8202f8] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x208ec4 */
  /* mem[0xfe8202fc] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x208ed2 */
  /* mem[0xfe820318] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x208ee6 */
  /* mem[0xfe820374] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x208efa */
  /* mem[0xfe820378] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x208f0e */
  /* mem[0xfe8202fc] = 0 */
  /* cmp esi, ecx -> jb 0x208eb3 */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* cmp eax, ebx -> jne 0x208f78 */
  /* cmp (char)eax, 3 -> jne 0x208f8e */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x2090b4 */
  /* relift: FUN_00207f35(0, 0); */
  /* relift: FUN_00208000(0); */
  /* relift: FUN_002081f6(0); */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x208ff9 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20900b */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20901d */
  /* mem[0xfe820300] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20902d */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209042 */
  /* mem[0xfe820360] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209053 */
  /* mem[0xfe820364] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209064 */
  /* mem[0xfe820368] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209075 */
  /* mem[0xfe82037c] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209085 */
  /* mem[0xfe8202fc] = 0 */
  /* cmp ebx, eax -> jb 0x208ff9 */
  /* relift: FUN_002063cb(0, 0); */
  /* cmp eax, ebx -> je 0x209213 */
  /* relift: cmp dword ptr [eax + 0x20], ebx -> je 0x209213 */
  /* relift: FUN_0020639e(0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x209213 */
  /* relift: FUN_00207f35(0, 0); */
  /* relift: FUN_00208000(0); */
  /* relift: FUN_002081f6(0); */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209157 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209169 */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20917b */
  /* mem[0xfe820300] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20918b */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2091a0 */
  /* mem[0xfe820360] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2091b1 */
  /* mem[0xfe820364] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2091c2 */
  /* mem[0xfe820368] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2091d3 */
  /* mem[0xfe82037c] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2091e3 */
  /* mem[0xfe8202fc] = 0 */
  /* cmp ebx, eax -> jb 0x209157 */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: test byte ptr [esi + 8], (char)eax -> je 0x209294 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x209240 */
  /* mem[0xfe8202f8] = ecx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x209252 */
  /* mem[0xfe8202fc] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x209270 */
  /* mem[0xfe8202fc] = 0 */
  /* relift: FUN_00207ea8(0); */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x2092a5 */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x209328 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x2092ec */
  /* mem[0xfe8202f8] = edi */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x2092fb */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* cmp edi, eax -> jb 0x2092ec */
  /* test esi, esi -> je 0x20934d */
  /* relift: FUN_0020391d(0, 0, 0, 0); */
  /* relift: FUN_0020933e(0); */
  /* relift: FUN_002090ca(0); */
  /* relift: FUN_0020639e(0); */
  /* relift: FUN_002047f5(0); */
  /* relift: FUN_0020488d(0); */
  /* relift: FUN_002048b8(0, 0); */
  /* cmp ecx, 8 -> je 0x209500 */
  /* cmp ecx, 0x10 -> je 0x2094f9 */
  /* cmp ecx, 0x18 -> je 0x2094f0 */
  /* cmp ecx, 0x20 -> jne 0x209500 */
  /* relift: cmp word ptr [ecx + 2], 1 -> je 0x209511 */
  /* relift: test dword ptr [eax + 0xc], ecx -> je 0x209524 */
  /* relift: cmp dword ptr [esp + 0xc], 0 -> je 0x209546 */
  /* relift: test dword ptr [eax + 0xc], ecx -> je 0x209554 */
  /* relift: test dword ptr [eax + 0xc], 0x82000 -> jne 0x20956b */
  /* relift: test byte ptr [eax + 0xc], 0x10 -> je 0x209590 */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: test byte ptr [esi + 8], 1 -> jne 0x209793 */
  /* relift: FUN_002064d5(0); */
  /* relift: FUN_00207f35(0, 0); */
  /* relift: FUN_00208000(0); */
  /* relift: FUN_002081f6(0); */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209618 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20962a */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20963f */
  /* mem[0xfe820318] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209652 */
  /* mem[0xfe820308] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209665 */
  /* mem[0xfe82030c] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209678 */
  /* mem[0xfe820310] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20968b */
  /* mem[0xfe820314] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20969e */
  /* mem[0xfe820350] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2096b1 */
  /* mem[0xfe82036c] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2096c4 */
  /* mem[0xfe820370] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2096d7 */
  /* mem[0xfe820374] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2096ea */
  /* mem[0xfe820378] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2096fd */
  /* mem[0xfe820300] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20970d */
  /* mem[0xfe820360] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20971e */
  /* mem[0xfe820364] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20972f */
  /* mem[0xfe820368] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209740 */
  /* mem[0xfe82037c] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209750 */
  /* mem[0xfe82031c] = 0xffff */
  /* cmp ebx, eax -> jb 0x209618 */
  /* relift: test byte ptr [eax + 0xc], 0x10 -> je 0x209793 */
  /* relift: FUN_00208a42(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x002097a9 */
void CMcpxVoiceClient_SetMixBins(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: FUN_002063cb(0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x20986c */
  /* relift: FUN_00207f35(0, 0, 0); */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x2097f6 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x209808 */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20981a */
  /* mem[0xfe820300] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20982a */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], edi -> jb 0x20983f */
  /* mem[0xfe8202fc] = 0 */
  /* cmp ebx, eax -> jb 0x2097f6 */
  /* relift: FUN_002063cb(0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x20994d */
  /* relift: FUN_00208000(0); */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x2098c6 */
  /* mem[0xfe8202f8] = edi */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x2098d6 */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x2098e8 */
  /* mem[0xfe820360] = edi */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x2098fa */
  /* mem[0xfe820364] = edi */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x20990c */
  /* mem[0xfe820368] = edi */
  /* relift: cmp dword ptr [0xfe820010], ecx -> jb 0x20991e */
  /* mem[0xfe8202fc] = 0 */
  /* cmp eax, edi -> jb 0x2098c6 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x00209961 */
void CMcpxVoiceClient_SetPitch(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_002063cb(0, 0); */
  /* relift: test dword ptr [eax + 0xc], 0x82000 -> je 0x20999f */
  /* relift: tail-call CMcpxVoiceClient_SetPitch(); */
  /* cmp esi, edi -> jne 0x20998c */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x209a04 */
  /* relift: FUN_002081f6(0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x2099c8 */
  /* mem[0xfe8202f8] = edx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x2099d9 */
  /* mem[0xfe82037c] = edx */
  /* cmp ecx, edx -> jb 0x2099c8 */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x209b39 */
  /* relift: test dword ptr [esi + 8], 0x10000002 -> je 0x209b39 */
  /* relift: FUN_002063cb(0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x209a6b */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x209a7b */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x209a97 */
  /* mem[0xfe820128] = eax */
  /* cmp edi, eax -> jb 0x209a6b */
  /* relift: cmp byte ptr [esi + 0xdc], 0xff -> jne 0x209adf */
  /* relift: FUN_0020639e(0); */
  /* test eax, eax -> je 0x209b29 */
  /* test edi, edi -> je 0x209b29 */
  /* cmp (char)ecx, 3 -> je 0x209b29 */
  /* cmp eax, edx -> jne 0x209b0e */
  /* relift: FUN_0020b3e6(0, 0); */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x209b46 */
  /* relift: FUN_002082ee(0, 0); */
  /* relift: FUN_00207dd4(0, 0, 0); */
  /* relift: cmp dword ptr [ebx + 0x58], 2 -> je 0x209bca */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x209b6d */
  /* relift: FUN_002083a6(0, 0); */
  /* relift: test byte ptr [ebp + 8], 2 -> je 0x209b7a */
  /* relift: FUN_002083fd(0, 0); */
  /* relift: test byte ptr [ebp + 8], 4 -> je 0x209b87 */
  /* relift: FUN_002085ef(0, 0); */
  /* relift: test byte ptr [ebp + 8], 8 -> je 0x209b94 */
  /* relift: FUN_00208686(0, 0); */
  /* relift: test byte ptr [ebp + 8], 0x10 -> je 0x209ba1 */
  /* relift: FUN_00208729(0, 0); */
  /* relift: test byte ptr [ebp + 8], 0x20 -> je 0x209bae */
  /* relift: FUN_002087dc(0, 0); */
  /* relift: test byte ptr [ebp + 8], 0x40 -> je 0x209bbb */
  /* relift: FUN_00208976(0, 0); */
  /* relift: test byte ptr [ebp + 8], 0x80 -> je 0x209bf8 */
  /* relift: FUN_00208a1e(0, 0); */
  /* relift: FUN_00207df9(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00209c05 */
void CMcpxVoiceClient_SetLFO(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x209c28 */
  /* relift: FUN_00208b9f(0); */
  /* cmp eax, 1 -> jne 0x209c35 */
  /* relift: FUN_00208c03(0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x209d00 */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209c5b */
  /* mem[0xfe8202f8] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209c6c */
  /* mem[0xfe8202fc] = 1 */
  /* relift: test byte ptr [esi + 8], 2 -> jne 0x209cac */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209c84 */
  /* mem[0xfe820318] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209c98 */
  /* mem[0xfe820350] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209cac */
  /* mem[0xfe82036c] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209cc0 */
  /* mem[0xfe820370] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209cd4 */
  /* mem[0xfe8202fc] = 0 */
  /* cmp ecx, edx -> jb 0x209c5b */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x00209d16 */
void CMcpxVoiceClient_SetEG(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x209d39 */
  /* relift: FUN_00208c60(0); */
  /* cmp eax, 1 -> jne 0x209d46 */
  /* relift: FUN_00208d09(0); */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x209e33 */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209d6c */
  /* mem[0xfe8202f8] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209d7d */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209d8f */
  /* mem[0xfe820318] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209da3 */
  /* mem[0xfe820308] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209db7 */
  /* mem[0xfe82030c] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209dcb */
  /* mem[0xfe820310] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209ddf */
  /* mem[0xfe820314] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209df3 */
  /* mem[0xfe82036c] = edx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x209e07 */
  /* mem[0xfe8202fc] = 0 */
  /* cmp ecx, edx -> jb 0x209d6c */
  /* relift: FUN_0020946f(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x209e66 */
  /* relift: FUN_00203664(0); */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x00209e6d */
void CMcpxVoiceClient_Commit3dSettings(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_00207dd4(0, 0); */
  /* cmp (char)ecx, 3 -> jne 0x209ef5 */
  /* relift: FUN_00209b4b(0); */
  /* relift: test byte ptr [ebp + 8], 2 -> je 0x209ec9 */
  /* relift: FUN_00208a42(0, 0); */
  /* relift: test byte ptr [ebp + 8], 0xb4 -> je 0x209ed7 */
  /* relift: FUN_00209880(0, 0); */
  /* relift: test byte ptr [ebp + 8], 0x40 -> je 0x209ee5 */
  CMcpxVoiceClient_SetPitch();
  /* relift: test byte ptr [ebp + 8], 0x80 -> je 0x209ef5 */
  CMcpxVoiceClient_SetFilter();
  /* relift: FUN_00207df9(0, 0); */
  /* relift: test byte ptr [esi + 8], 2 -> jne 0x20a0ec */
  /* relift: FUN_002082ee(0, 0); */
  /* relift: test byte ptr [eax + 0xc], 0x10 -> je 0x209f30 */
  /* relift: tail-call CMcpxVoiceClient_Commit3dSettings(); */
  /* relift: FUN_002063cb(0, 0); */
  /* test eax, eax -> je 0x209f55 */
  /* test eax, eax -> je 0x209f55 */
  /* relift: FUN_0020b4cc(0); */
  /* relift: cmp dword ptr [0xfe820010], 0x80 -> jb 0x209f55 */
  /* relift: FUN_00207e8a(0, 0, 0); */
  /* cmp edi, 4 -> jl 0x209f6e */
  /* relift: test byte ptr [esi + 8], 0x80 -> je 0x209f8d */
  /* relift: FUN_002066b7(0, 0, 0); */
  /* test ecx, ecx -> je 0x209fc7 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a028 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a036 */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a049 */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a05f */
  /* mem[0xfe820120] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a070 */
  /* mem[0xfe820124] = ebx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a07f */
  /* mem[0xfe820140] = edi */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20a08e */
  /* mem[0xfe8202fc] = 0 */
  /* relift: FUN_00206669(0, 0, 0); */
  /* relift: cmp dword ptr [0xfe820010], 0x80 -> jb 0x20a0c4 */
  /* relift: cmp dword ptr [ebp - 0x1c], 0 -> je 0x20a0e9 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020a0ef */
void CMcpxVoiceClient_Set3dParameters(void)
{
  CMcpxVoiceClient_Commit3dSettings();
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a145 */
void CMcpxVoiceClient_Set3dConeOrientation(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a16d */
void CMcpxVoiceClient_Set3dConeOutsideVolume(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a18e */
void CMcpxVoiceClient_Set3dMaxDistance(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a1af */
void CMcpxVoiceClient_Set3dMinDistance(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a1d0 */
void CMcpxVoiceClient_Set3dMode(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a1f1 */
void CMcpxVoiceClient_Set3dPosition(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a219 */
void CMcpxVoiceClient_Set3dVelocity(void)
{
  CMcpxVoiceClient_Commit3dSettings();
}

/* 0x0020a241 */
void CMcpxVoiceClient_SetI3DL2Source(void)
{
  CMcpxVoiceClient_Commit3dSettings();
  /* relift: FUN_0020a26f(0, 0); */
  /* relift: relift: fcomp dword ptr [0x2c2100] */
  FUN_001d9068();
}

/* 0x0020a2f5 */
void CSensaura3d_GetFullHRTFFilterPair(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x20a317 */
  /* relift: FUN_00207cc8(0, 0); */
  /* cmp esi, -0x5a -> jl 0x20a33a */
  /* cmp esi, 0x5a -> jle 0x20a33c */
  /* relift: FUN_00207cb2(0, 0); */
  /* relift: FUN_00207cc8(0, 0); */
  /* cmp edi, 0x1e -> jle 0x20a3a1 */
  /* relift: FUN_00207cc8(0, 0); */
  /* relift: FUN_00207cc8(0, 0); */
  /* test ecx, ecx -> jl 0x20a3c0 */
  /* cmp ecx, ebx -> jle 0x20a3c2 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x20a3d1 */
  /* cmp ecx, 0x5a -> jle 0x20a3d1 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020a431 */
void CSensaura3d_GetLiteHRTFFilterPair(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_00207cb2(0, 0); */
  /* relift: FUN_00207cc8(0, 0); */
  /* cmp ecx, eax -> jle 0x20a467 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x20a478 */
  /* cmp ecx, 0x5a -> jle 0x20a478 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x254e04] */
  FUN_001d9068();
  /* relift: cmp dword ptr [ebp + 0xc], 0x20f240 -> jl 0x20a4fa */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x20f1ac] */
  FUN_001d9068();
  /* cmp edi, 0x20f200 -> jl 0x20a569 */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x20f1ac] */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x20f1ac] */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x2c26dc] */
  FUN_001d9068();
  /* test eax, eax -> jge 0x20a63a */
  FUN_001d9068();
  /* cmp ebx, 0x20f208 -> jl 0x20a624 */
  FUN_001d9068();
  /* cmp edi, 0x20f20c -> jl 0x20a65d */
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  /* cmp esi, 0x20f220 -> jl 0x20a698 */
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x222620] */
  /* test eax, eax -> jne 0x20a77c */
  /* relift: cmp dword ptr [ebp + 0xc], eax -> jne 0x20a791 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x20a791 */
  /* relift: FUN_0020a2b1(0, 0); */
  /* relift: FUN_0020a2b1(0); */
  /* relift: FUN_0020a2b1(0); */
  /* relift: FUN_0020a734(0, 0); */
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  /* relift: cmp dword ptr [ebp + 8], 0xffffd8f0 -> jle 0x20a8c8 */
  /* relift: cmp dword ptr [ebp + 0xc], eax -> je 0x20a8c8 */
  /* relift: relift: fld dword ptr [0x222624] */
  /* relift: FUN_0020a2b1(0, 0); */
  /* test (char)eax, 1 -> jne 0x20a8bd */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x2c26b0] */
  /* relift: FUN_0020a734(0, 0); */
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  FUN_001d9068();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2c26dc] */
  FUN_001d9068();
  /* relift: FUN_0020a734(0, 0); */
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x20f1a8] */
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x20aa50 */
  /* relift: relift: fcomp dword ptr [0x2c2100] */
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  /* relift: relift: fld dword ptr [0x2c26b0] */
  /* relift: FUN_0020a842(0, 0); */
  /* relift: relift: fld dword ptr [0x2c26b0] */
  /* relift: FUN_0020a842(0, *(int *)((char *)edi + 0xc)); */
  /* relift: FUN_0020a924(0, 0); */
  /* relift: FUN_0020a924(0, *(int *)((char *)esi + 0x160)); */
  /* relift: FUN_0020a924(0, 0); */
  /* relift: relift: fld dword ptr [0x25bb10] */
  /* relift: relift: fld dword ptr [0x253f40] */
  /* relift: relift: fcomp dword ptr [0x2b4ee4] */
  /* test (char)eax, 0x41 -> jne 0x20ac14 */
  /* relift: FUN_0020a6f8(0); */
  /* relift: FUN_0020a8cc(0, 0); */
  /* relift: FUN_0020a2b1(0); */
  /* relift: FUN_0020a558(0); */
  /* relift: FUN_0020a58f(0); */
  /* relift: FUN_0020a2b1(0); */
  /* relift: FUN_0020a5b8(0); */
  /* relift: FUN_0020a5eb(0); */
  /* relift: FUN_0020a4c1(0); */
  /* relift: FUN_0020aab2(0); */
  /* relift: FUN_0020a684(0); */
  /* cmp edx, ecx -> jbe 0x20adea */
  FUN_001d9068();
  FUN_001d9068();
  /* relift: cmp dword ptr [ecx], edx -> jbe 0x20ae1c */
  /* relift: cmp dword ptr [esi + 0x160], eax -> jbe 0x20ae39 */
  /* cmp ecx, edx -> jle 0x20ae56 */
  /* cmp ecx, edi -> jge 0x20ae5c */
  /* relift: cmp dword ptr [esp + 8], 0 -> je 0x20aed7 */
  /* relift: FUN_0020aeb6(0, 0); */
  /* relift: FUN_00207556(0); */
  /* relift: FUN_00207392(0); */
  /* relift: FUN_00209353(0, 0); */
  /* cmp ecx, edx -> jb 0x20af8e */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b009 */
  /* mem[0xfe8202f8] = edx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b01a */
  /* mem[0xfe8203a0] = esi */
  /* cmp ecx, edx -> jb 0x20b009 */
  /* relift: test byte ptr [esi + 8], 0x40 -> je 0x20b0aa */
  /* relift: test byte ptr [eax + 0xe], 8 -> jne 0x20b0aa */
  /* test eax, eax -> je 0x20b0a9 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020b0ac */
void CMcpxBuffer_GetStatus(void)
{
  int ecx = 0;
  int esi = 0;

  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: test byte ptr [esi + 8], (char)ecx -> je 0x20b0e1 */
  /* relift: test dword ptr [esi + 8], 0x10000002 -> je 0x20b0e1 */
  /* relift: test byte ptr [esi + 8], 0x10 -> je 0x20b0e1 */

  (void)ecx;
  (void)esi;
}

/* 0x0020b0f7 */
void CMcpxBuffer_GetCurrentPosition(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* cmp (char)eax, 3 -> jne 0x20b18c */
  /* relift: FUN_00209228(0, 0); */
  /* test eax, eax -> je 0x20b125 */
  /* test edi, edi -> je 0x20b1aa */
  /* relift: FUN_00207ea8(32); */
  /* cmp eax, ecx -> jae 0x20b148 */
  /* relift: test byte ptr [esi + 8], 0x10 -> je 0x20b17d */
  /* cmp ebx, edx -> jb 0x20b17d */
  /* cmp ebx, edx -> jae 0x20b17d */
  /* test eax, eax -> je 0x20b19b */
  /* test eax, eax -> je 0x20b1aa */
  /* relift: cmp dword ptr [esi + 0x14c], 0 -> je 0x20b1f0 */
  /* relift: tail-call CMcpxBuffer_GetCurrentPosition(); */
  /* test eax, eax -> jl 0x20b1f0 */
  /* relift: test dword ptr [esi + 8], 0x10000002 -> jne 0x20b214 */
  /* test eax, eax -> je 0x20b20b */
  /* relift: FUN_0020af57(0); */
  /* relift: FUN_0020aee5(0, 0, 0, 0); */
  /* cmp ebx, edi -> je 0x20b24e */
  /* relift: test byte ptr [eax + 0xe], 4 -> je 0x20b24e */
  /* relift: FUN_0020af28(0, 0, 0, 0); */
  /* test esi, esi -> je 0x20b263 */
  /* relift: FUN_0020af57(0); */
  /* cmp edi, 2 -> jb 0x20b277 */
  /* relift: FUN_0020b05a(0, 0); */
  /* relift: test byte ptr [esi + 8], 0x40 -> jne 0x20b2f2 */
  /* relift: FUN_0020b05a(0, 0); */
  /* relift: cmp word ptr [eax + 0x12], (int16_t)edi -> jbe 0x20b35f */
  /* relift: FUN_0020d2c6(0, 0, 0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b322 */
  /* mem[0xfe820804] = ecx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b33d */
  /* mem[0xfe820808] = eax */
  /* cmp edi, eax -> jb 0x20b313 */
  /* relift: FUN_0020afb7(0); */
  /* relift: test byte ptr [edi + 8], 0x40 -> jne 0x20b3e4 */
  /* test eax, edx -> jne 0x20b3b0 */
  /* cmp esi, 0x1e -> jbe 0x20b39f */
  /* relift: FUN_00207ea8(32); */
  CDirectSoundBufferSettings_SetBufferData();
  /* relift: FUN_0020afb7(2047, 0, 0); */
  /* cmp (char)eax, 3 -> jne 0x20b435 */
  /* relift: test dword ptr [eax + 0xc], 0x82000 -> jne 0x20b413 */
  /* relift: tail-call CMcpxBuffer_GetCurrentPosition(); */
  /* relift: FUN_0020b269(0, 0); */
  /* relift: FUN_0020b1c2(0, 0); */
  /* relift: FUN_0020b269(0, 0); */
  /* relift: FUN_0020af57(0); */
  /* cmp edi, 5 -> jb 0x20b44a */
  /* relift: FUN_002048e3(0); */
  /* relift: test byte ptr [eax + 0xe], 4 -> je 0x20b483 */
  /* relift: FUN_0020b269(0, 0); */
  /* relift: FUN_0020b05a(0, 0); */
  /* relift: FUN_00209596(0, 0); */
  /* test edi, edi -> jl 0x20b4c7 */
  /* test (char)eax, 0x20 -> jne 0x20b4c7 */
  /* relift: FUN_0020b383(0, 0); */
  /* relift: FUN_0020b295(0, 0); */
  /* relift: FUN_0020b493(0); */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_0020af03(0); */
  /* relift: FUN_0020af03(0); */
  /* relift: FUN_0020af03(0, 0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b576 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b586 */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b599 */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b5b2 */
  /* mem[0xfe8203dc] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b5c3 */
  /* mem[0xfe8203a4] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b5d4 */
  /* mem[0xfe8202fc] = 0 */
  /* cmp edi, eax -> jb 0x20b576 */
  /* relift: test byte ptr [esi + 8], 2 -> jne 0x20b618 */
  /* relift: FUN_0020af03(*(int *)((char *)esi + 0x228)); */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20b6ec */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b64c */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b65c */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b66f */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b688 */
  /* mem[0xfe820360] = 0xffffffff */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b69a */
  /* mem[0xfe820364] = 0xffffffff */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b6ac */
  /* mem[0xfe820368] = 0xffffffff */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b6be */
  /* mem[0xfe8202fc] = 0 */
  /* cmp edi, eax -> jb 0x20b64c */
  /* relift: cmp dword ptr [ebp - 0x18], 0 -> je 0x20b6fb */
  /* relift: FUN_0020af57(0); */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20b828 */
  /* relift: test dword ptr [eax], 0x100000 -> jne 0x20b727 */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_00208000(0); */
  /* relift: cmp dword ptr [ebp + 8], 0 -> jne 0x20b74f */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b768 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b778 */
  /* mem[0xfe8202fc] = 1 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b78b */
  /* relift: FUN_00207ecf(0); */
  /* mem[0xfe820304] = eax */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b7a4 */
  /* mem[0xfe820360] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b7b6 */
  /* mem[0xfe820364] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b7c8 */
  /* mem[0xfe820368] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b7da */
  /* mem[0xfe8203d8] = ecx */
  /* relift: cmp dword ptr [0xfe820010], eax -> jb 0x20b7eb */
  /* mem[0xfe8202fc] = 0 */
  /* cmp ebx, eax -> jb 0x20b768 */
  /* relift: cmp dword ptr [ebp - 0x18], 0 -> je 0x20b828 */
  /* relift: cmp dword ptr [esi + 0x14c], eax -> je 0x20b84e */
  /* relift: FUN_0020af28(0, 0, 0, 0); */
  /* cmp dl, 3 -> jne 0x20b872 */
  /* relift: FUN_0020b4cc(0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020b873 */
void CMcpxBuffer_Stop(void)
{
  int eax = 0;
  int edi = 0;

  /* relift: FUN_0020af28(0, 0, 0, 0); */
  /* cmp eax, edi -> jne 0x20b8a0 */
  /* relift: FUN_0020b3e6(0, 0); */
  /* cmp (char)eax, 0x13 -> jne 0x20b8c9 */
  /* relift: FUN_0020b4cc(0); */
  /* test edi, edi -> jl 0x20b8d0 */
  /* relift: FUN_00208280(0, 0); */

  (void)eax;
  (void)edi;
}

/* 0x0020b8d7 */
void CMcpxBuffer_SetCurrentPosition(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (char)eax, 3 -> jne 0x20b9ab */
  /* cmp (char)eax, 0x13 -> jne 0x20b921 */
  /* relift: cmp dword ptr [ebp + 8], ecx -> jb 0x20b921 */
  /* relift: FUN_0020b4cc(0); */
  /* relift: FUN_002082fe(0, 0); */
  /* relift: FUN_0020af03(0); */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b957 */
  /* mem[0xfe8202f8] = edx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20b968 */
  /* mem[0xfe8203d8] = edi */
  /* cmp ecx, edx -> jb 0x20b957 */
  /* relift: FUN_002082fe(0); */
  /* relift: FUN_0020b8a7(0); */
  /* relift: FUN_0020b3e6(0, 0); */
  /* relift: FUN_0020b4cc(0); */
  /* relift: FUN_0020b269(0, 0); */
  /* relift: FUN_0020b1c2(0, 0); */
  /* relift: FUN_0020b439(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20ba1a */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020b254(0, 0); */
  /* relift: FUN_002094a6(0, 0); */
  /* test eax, eax -> jl 0x20ba8c */
  /* test edx, 0x40000 -> jne 0x20ba8c */
  /* test edx, 0x82000 -> jne 0x20ba85 */
  /* relift: cmp dword ptr [ecx + 0x48], 0 -> je 0x20ba8c */
  /* relift: cmp dword ptr [ecx + 0x4c], 0 -> je 0x20ba8c */
  /* relift: FUN_0020b493(0, 0); */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x0020ba90 */
void CMcpxBuffer_SetBufferData(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x0020baa4 */
void CMcpxBuffer_Play(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_0020af28(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x20bad5 */
  /* relift: FUN_0020b4cc(0); */
  /* relift: FUN_0020af28(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x20bb0e */
  /* relift: FUN_0020b8a7(0); */
  /* test eax, eax -> je 0x20bb2d */
  /* test eax, eax -> je 0x20bb3a */
  /* test ecx, ecx -> je 0x20bb4f */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x20bb6d */
  /* test eax, eax -> je 0x20bb7d */
  /* relift: FUN_00207556(0); */
  /* relift: FUN_00207392(0); */
  /* relift: FUN_00209353(0, 0); */
  /* cmp ecx, 3 -> jb 0x20bc3c */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test edi, edi -> jne 0x20bce4 */
  /* test edi, edi -> jne 0x20bce4 */
  /* cmp ecx, 2 -> jb 0x20bcce */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20bcf3 */
  /* relift: test byte ptr [eax + 0xe], 4 -> je 0x20bd25 */
  /* relift: FUN_0020bb9b(0, 0, 0, 0); */
  /* test eax, eax -> je 0x20bd60 */
  /* relift: FUN_00207ea8(65535); */
  /* relift: cmp dword ptr [edi + 8], 0x10 -> jae 0x20bea9 */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x20bd93 */
  /* relift: FUN_0020d24f(0); */
  /* relift: FUN_0020af03(0); */
  /* relift: FUN_00207ea8(0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20be2e */
  /* mem[0xfe820190] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20be44 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20be5a */
  /* relift: cmp dword ptr [ebp - 0x10], eax -> jb 0x20be03 */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jb 0x20bd79 */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jb 0x20bec9 */
  /* relift: FUN_0020639e(0); */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20bf05 */
  /* mem[0xfe8202f8] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20bf2b */
  /* mem[0xfe820320] = eax */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20bf51 */
  /* mem[0xfe82035c] = eax */
  /* relift: cmp dword ptr [ebp - 4], eax -> jb 0x20bf05 */
  /* relift: FUN_00207e8a(0, 0); */
  /* relift: test byte ptr [eax + 0xf], 0x40 -> jne 0x20bfb7 */
  /* relift: FUN_0020bb9b(0, 0, 0, 0); */
  /* cmp (char)eax, 0xf -> jne 0x20bfd0 */
  /* relift: FUN_002082fe(0); */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_0020639e(0); */
  /* relift: FUN_0020bb3d(0, *(int *)((char *)esi + 0xc), *(int *)((char *)edi + 0x14c), *(int *)((char *)edi + 0x150)); */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020c050 */
void CMcpxStream_Pause(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp + 8], 1 -> jne 0x20c06e */
  /* relift: cmp dword ptr [ebp + 8], 0 -> jne 0x20c082 */
  /* relift: FUN_002082fe(0); */
  /* relift: FUN_0020bbca(0); */
  /* cmp edi, 2 -> jb 0x20c0a6 */
  /* test esi, esi -> je 0x20c0cc */
  /* relift: FUN_002094a6(0, 0, 0, 0); */
  /* relift: FUN_0020c0bd(0); */
  /* cmp ecx, 8 -> je 0x20c151 */
  /* cmp ecx, 0x10 -> je 0x20c14a */
  /* cmp ecx, 0x18 -> je 0x20c141 */
  /* cmp ecx, 0x20 -> jne 0x20c151 */
  /* relift: FUN_00203609(0); */
  /* relift: cmp dword ptr [ecx + 0x48], ebx -> jbe 0x20c1f9 */
  /* relift: cmp eax, dword ptr [ecx + 0x48] -> jb 0x20c1bd */
  /* relift: test byte ptr [eax + 0xe], 4 -> jne 0x20c20f */
  /* relift: FUN_00209596(0, 0); */
  /* relift: cmp dword ptr [ebx], 0 -> jne 0x20c290 */
  /* cmp edi, eax -> je 0x20c27f */
  /* relift: FUN_0020bb9b(0, *(int *)((char *)edi + 0x28), *(int *)((char *)edi + 0x2c), 0); */
  /* test eax, eax -> jne 0x20c27f */
  /* relift: FUN_0020bd28(0, 0); */
  /* test eax, eax -> je 0x20c27f */
  /* relift: cmp dword ptr [ebx], 0x10 -> jb 0x20c237 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x20c28f */
  /* relift: FUN_0020bed3(0); */
  /* relift: cmp eax, dword ptr [ebp + 8] -> je 0x20c2bf */
  /* relift: test byte ptr [eax + 0xf], 0x40 -> je 0x20c333 */
  /* cmp (char)eax, 2 -> jae 0x20c328 */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_002063b8(0); */
  /* relift: cmp dword ptr [eax], eax -> jne 0x20c2e8 */
  /* relift: cmp dword ptr [ebp - 0x14], 0 -> je 0x20c314 */
  /* relift: FUN_0020bfd7(0, 0); */
  /* cmp eax, ecx -> jne 0x20c31c */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_002063b8(0); */
  /* relift: cmp dword ptr [eax], eax -> jne 0x20c33d */
  /* relift: cmp dword ptr [ebp - 0x14], 0 -> je 0x20c378 */
  /* cmp (char)eax, 3 -> je 0x20c390 */
  /* relift: FUN_0020bbca(0); */
  /* relift: FUN_0020c299(0, 0x8000000a, 0); */
  /* relift: cmp dword ptr [ebx], 0 -> je 0x20c3f9 */
  /* relift: FUN_0020c299(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020c3fe */
void CMcpxStream_Flush(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: test byte ptr [esi + 8], 1 -> je 0x20c49c */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_0020bbca(0); */
  /* cmp edi, 3 -> jb 0x20c424 */
  /* relift: cmp dword ptr [ebp - 8], ebx -> je 0x20c449 */
  /* relift: FUN_002082ee(0, 0); */
  /* relift: FUN_0020c3a7(0, 0, 0); */
  /* cmp ebx, 2 -> jb 0x20c457 */
  /* relift: FUN_0020c299(0, 0, 0); */
  /* relift: FUN_0020c098(0, 0); */
  /* relift: FUN_0020c37c(0, 0); */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_0020aee5(0, 0); */
  /* test eax, eax -> je 0x20c4f6 */
  /* relift: FUN_0020c3a7(0, 0, 0); */
  /* relift: FUN_0020c219(0); */
  /* test eax, eax -> je 0x20c526 */
  /* relift: cmp dword ptr [ebp - 8], 0 -> jne 0x20c4bf */
  /* relift: cmp dword ptr [ebp - 0x10], eax -> jne 0x20c53b */
  /* relift: cmp dword ptr [ebp - 0x18], eax -> je 0x20c549 */
  /* cmp (char)eax, 3 -> jne 0x20c5c3 */
  /* relift: FUN_0020aee5(0, 0, 0); */
  /* test eax, eax -> jne 0x20c578 */
  /* cmp edi, 2 -> jb 0x20c562 */
  /* relift: FUN_0020c4a1(0, 0); */
  /* test eax, eax -> jne 0x20c5c2 */
  /* relift: cmp dword ptr [eax], 0 -> jne 0x20c5c2 */
  /* cmp ecx, 2 -> jb 0x20c58e */
  /* cmp (char)eax, 0x23 -> jne 0x20c5af */
  /* relift: FUN_0020bcf9(0, 0); */
  /* cmp (char)eax, 3 -> jne 0x20c5c2 */
  /* relift: FUN_002082fe(0); */
  /* relift: FUN_0020c4a1(0, 0); */
  /* relift: FUN_0020c098(0, 0); */
  /* relift: FUN_0020c37c(0, 0); */
  /* relift: FUN_0020bbca(0, 0, 0); */
  /* cmp edi, 3 -> jb 0x20c5f9 */
  /* relift: tail-call CMcpxStream_Flush(); */
  /* relift: FUN_0020c098(0, 0); */
  /* relift: FUN_0020490f(0); */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020bb1f(0, 0); */
  /* relift: FUN_0020bbca(0); */
  /* relift: FUN_00209596(0, 0); */
  /* relift: FUN_002063cb(0, 0); */
  /* relift: FUN_002063b8(0); */
  /* test eax, eax -> je 0x20c6c9 */
  /* test eax, eax -> jl 0x20c6c9 */
  /* test ecx, ecx -> jb 0x20c6c9 */
  /* test eax, eax -> je 0x20c6e4 */
  /* relift: FUN_002063cb(0, 0); */
  /* cmp eax, ecx -> je 0x20c724 */
  /* cmp edi, esi -> jg 0x20c724 */
  /* cmp edi, edx -> ja 0x20c724 */
  /* cmp eax, ecx -> jne 0x20c70e */
  /* relift: FUN_0020c4a1(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0020c752 */
void CMcpxStream_Discontinuity(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (char)eax, 3 -> jne 0x20c7bd */
  /* relift: FUN_002063cb(0); */
  /* test edi, edi -> je 0x20c79e */
  /* relift: cmp dword ptr [eax], 0 -> jne 0x20c798 */
  /* cmp ecx, 2 -> jb 0x20c788 */
  /* test edi, edi -> jne 0x20c7a2 */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20c7b1 */
  CMcpxStream_Flush();
  /* relift: FUN_0020c5ed(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20c7df */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00207dd4(0, 0); */
  /* relift: relift: fld dword ptr [0x2c26b0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: FUN_00207df9(0, 0); */

  (void)eax;
  (void)ecx;
  (void)edi;
  (void)ebp;
}

/* 0x0020c857 */
void XAudioCalculatePitch(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, 0xbb80 -> jne 0x20c86b */
  /* test esi, esi -> jne 0x20c876 */
  /* relift: FUN_00207dd4(0, 0); */
  /* relift: FUN_0020c7ed(0, 0); */
  /* relift: FUN_00207df9(0, 0); */
  /* relift: cmp word ptr [eax], 1 -> jne 0x20c8c4 */
  /* relift: FUN_0020c8a8(0, 0x80000000, 0, 0); */
  /* relift: FUN_0020c8a8(0, 0x40000000); */
  /* relift: FUN_0020c8a8(0, 0, 0, 0); */
  /* relift: FUN_0020c8a8(0, 0); */
  /* cmp ecx, eax -> je 0x20c94d */
  /* relift: cmp word ptr [ecx], (int16_t)edi -> je 0x20c992 */
  /* cmp (int16_t)edx, 1 -> je 0x20c9b0 */
  /* cmp (int16_t)edx, 2 -> je 0x20c9b0 */
  /* cmp (int16_t)edx, 4 -> je 0x20c9b0 */
  /* cmp (int16_t)edx, 6 -> je 0x20c9b0 */
  /* cmp (int16_t)eax, 8 -> je 0x20c9c2 */
  /* cmp (int16_t)eax, 0x10 -> je 0x20c9c2 */
  /* cmp esi, 0xbc -> jb 0x20c9d6 */
  /* cmp esi, 0x2edef -> jbe 0x20c9d8 */
  /* cmp eax, ecx -> je 0x20c9f2 */
  /* relift: cmp word ptr [edx], 0x69 -> je 0x20ca08 */
  /* relift: cmp word ptr [edx + 0x10], 2 -> je 0x20ca11 */
  /* cmp (int16_t)ecx, 1 -> jb 0x20ca21 */
  /* cmp (int16_t)ecx, 2 -> jbe 0x20ca23 */
  /* cmp eax, 0xbc -> jb 0x20ca34 */
  /* cmp eax, 0x2edef -> jbe 0x20ca36 */
  /* relift: cmp word ptr [edx + 0xe], 4 -> je 0x20ca3f */
  /* cmp (int16_t)eax, 0x40 -> je 0x20ca4d */
  /* relift: FUN_0020c959(0, 0); */
  /* relift: cmp (int16_t)eax, word ptr [edx + 0xc] -> je 0x20ca5c */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x0020ca62 */
void XAudioCreatePcmFormat(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x0020caac */
void XAudioCreateAdpcmFormat(void)
{
  int ebx = 0;
  int edx = 0;

  /* relift: FUN_0020c959(0, 64, 0); */
  /* test ebx, ebx -> je 0x20cb45 */
  /* relift: FUN_0020c8a8(0, 0x80000000, 0, 0); */
  /* relift: FUN_0020c8a8(0, 0x40000000); */
  /* relift: FUN_0020caf0(0, 0); */
  /* test edx, edx -> je 0x20cba5 */

  (void)ebx;
  (void)edx;
}

/* 0x0020cbad */
void IsValidFormat(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_0020c9f8(0); */
  /* relift: FUN_0020c983(0); */
  /* test ebx, ebx -> je 0x20cc34 */
  /* test eax, eax -> je 0x20cc5e */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020e2b3(0); */
  /* cmp eax, 0x8000 -> jb 0x20ccae */
  /* mem[0xfe80202c] = eax */
  /* mem[0xfe802038] = eax */
  /* mem[0xfe80203c] = eax */
  /* mem[0xfe802030] = eax */
  /* mem[0xfe802034] = eax */
  /* mem[0xfe80115c] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20ccff */
  /* mem[0xfe8202a4] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd11 */
  /* mem[0xfe8202b0] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd1e */
  /* mem[0xfe8202a0] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd2b */
  /* mem[0xfe8202a8] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd38 */
  /* mem[0xfe8202ac] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd45 */
  /* mem[0xfe820804] = 0x7ff */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd57 */
  /* mem[0xfe820808] = eax */
  /* relift: cmp dword ptr [0xfe820010], edx -> jb 0x20cd6a */
  /* mem[0xfe8202c0] = 0x9070806 */
  /* mem[0xfe802044] = eax */
  /* mem[0xfe83ff00] = edi */
  /* mem[0xfe83ff04] = edi */
  /* mem[0xfe8020d8] = eax */
  /* mem[0xfe801148] = eax */
  /* mem[0xfe803024] = edi */
  /* mem[0xfe803028] = edx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20cdce */
  /* mem[0xfe821800] = ebx */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20cde0 */
  /* mem[0xfe821808] = eax */
  /* relift: cmp dword ptr [ebp - 4], 2 -> jb 0x20cdc8 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20ce07 */
  /* mem[0xfe821000] = edi */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20ce16 */
  /* mem[0xfe821004] = edx */
  /* relift: FUN_00203609(64, 0); */
  /* cmp eax, edi -> je 0x20ce40 */
  /* relift: FUN_00207799(0); */
  /* relift: FUN_002077c0(0, 0); */
  /* mem[0xfe83fffc] = eax */
  /* mem[0xfe83ff10] = ecx */
  /* mem[0xfe83ff14] = 0xff */
  /* mem[0xfe80302c] = eax */
  /* mem[0xfe80303c] = eax */
  /* mem[0xfe80304c] = eax */
  /* mem[0xfe80305c] = eax */
  /* mem[0xfe83fffc] = 3 */
  /* mem[0xfe85fffc] = 1 */
  /* relift: FUN_00203609(16, 0); */
  /* cmp eax, ebx -> je 0x20ced9 */
  /* relift: FUN_0020ee0b(0); */
  /* relift: FUN_0020ef09(*(int *)((char *)esi + 0xc8)); */
  /* mem[0xfe80204c] = eax */
  /* mem[0xfe85ff00] = ebx */
  /* mem[0xfe85ff04] = ebx */
  /* mem[0xfe8020e0] = eax */
  /* relift: cmp dword ptr [ebp - 4], edi -> jb 0x20cf46 */
  /* relift: cmp dword ptr [ebp + 8], ebx -> je 0x20d01a */
  /* relift: FUN_0020ee9c(0, 8192); */
  /* relift: FUN_0020eec4(0, 16384); */
  /* relift: FUN_002078f2(0, 0); */
  /* cmp ecx, 2 -> je 0x20d01a */
  /* cmp eax, 0x10000 -> je 0x20d01a */
  /* relift: FUN_0020ee21(0, 0); */
  /* mem[0xfe85ff5c] = ebx */
  /* mem[0xfe85ff10] = 1 */
  /* mem[0xfe85fffc] = 3 */
  /* relift: FUN_0020ec10(0, 0, 0, 0); */
  /* test ebx, ebx -> jl 0x20d111 */
  /* relift: FUN_0020e5cb(0, 0); */
  /* cmp ebx, eax -> jl 0x20d111 */
  /* relift: FUN_0020e84e(0, 0, 0); */
  /* test ebx, ebx -> jl 0x20d111 */
  /* relift: FUN_0020e631(0, 8192); */
  /* relift: FUN_0020e5cb(0, 0); */
  /* cmp ebx, edi -> jl 0x20d111 */
  /* relift: FUN_0020e84e(0, 0, 0); */
  /* cmp ebx, edi -> jl 0x20d111 */
  /* cmp eax, 0x10000 -> jne 0x20d0f6 */
  /* relift: FUN_0020e631(0); */
  /* relift: FUN_0020e631(0, 8192); */
  /* relift: FUN_0020e4cf(0x02000000); */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* mem[0xfe801004] = ecx */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20d14e */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* mem[0xfe801510] = ecx */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20d188 */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* mem[0xfe801100] = ecx */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20d1e6 */
  /* relift: FUN_002063cb(0, 0, 0); */
  /* mem[0xfe802000] = ecx */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20d24b */
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x20d2bf */
  /* relift: cmp esi, dword ptr [ebp + 0xc] -> jae 0x20d2b5 */
  /* cmp ebx, eax -> jne 0x20d2af */
  /* relift: cmp esi, dword ptr [ebp + 0xc] -> jb 0x20d296 */
  /* relift: FUN_0020d24f(0, 0, 0, 0); */
  /* cmp ecx, edx -> jb 0x20d2f0 */
  /* relift: FUN_0020cbda(0, 0, 0, 0); */
  /* relift: test byte ptr [0x222d88], 1 -> jne 0x20d365 */
  /* mem[0x0022263c] = eax */
  /* mem[0xfe802008] = eax */
  /* mem[0xfe802010] = eax */
  /* mem[0xfe802014] = ecx */
  /* mem[0xfe802018] = eax */
  /* mem[0xfe802020] = ecx */
  /* mem[0xfe802024] = eax */
  /* mem[0xfe802028] = eax */
  /* mem[0xfe80402c] = ecx */
  /* mem[0xfe80403c] = 0x3800 */
  /* test dl, dl -> jne 0x20d454 */
  /* test dl, dl -> je 0x20d454 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20d3ee */
  /* mem[0xfe82010c] = 0 */
  /* test esi, esi -> je 0x20d438 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20d40c */
  /* mem[0xfe820104] = 2 */
  /* test eax, eax -> je 0x20d454 */
  /* relift: cmp byte ptr [esi + 0xf], 1 -> jne 0x20d421 */
  /* relift: cmp dword ptr [0xfe820010], 4 -> jb 0x20d441 */
  /* mem[0xfe82010c] = 1 */
  /* relift: FUN_00207bc4(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20d479 */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020f062(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20d49d */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020eb80(0, 0); */
  /* relift: FUN_0020e70e(0, 0); */
  /* relift: FUN_0020e70e(0, 0); */
  /* relift: FUN_0020d3bd(0); */
  /* relift: FUN_0020d118(0); */
  /* relift: FUN_0020d152(0); */
  /* relift: FUN_0020d18c(0); */
  /* relift: FUN_0020d1ea(0); */
  /* mem[0xfe802054] = eax */
  /* mem[0xfe802060] = eax */
  /* mem[0xfe80206c] = eax */
  /* mem[0xfe802058] = eax */
  /* mem[0xfe802064] = eax */
  /* mem[0xfe802070] = eax */
  /* mem[0xfe802058] = ecx */
  /* mem[0xfe802064] = edx */
  /* mem[0xfe802070] = esi */
  /* mem[0xfe80205c] = eax */
  /* mem[0xfe802068] = eax */
  /* mem[0xfe802074] = eax */
  /* mem[0xfe83fffc] = ebx */
  /* mem[0xfe85fffc] = 1 */
  /* mem[0xfe801004] = 0xafa */
  /* mem[0xfe801100] = 0x88 */
  /* mem[0xfe802000] = edx */
  /* mem[0xfe801500] = edx */
  /* mem[0xfe801504] = 0x8000 */
  /* mem[0xfe801508] = 0x800040 */
  /* mem[0xfe80150c] = edx */
  /* relift: FUN_0020d349(0); */
  /* mem[0xfe801104] = 0xff */
  /* mem[0xfe801108] = 0x3f */
  /* mem[0xfe80111c] = 0x7f */
  /* mem[0xfe801124] = 0x1fff */
  /* mem[0xfe801138] = 0x7ff */
  /* mem[0xfe801158] = 0x20 */
  /* mem[0xfe80112c] = edx */
  /* mem[0xfe801130] = eax */
  /* mem[0xfe801140] = edx */
  /* mem[0xfe801144] = eax */
  /* mem[0xfe801150] = edx */
  /* mem[0xfe801154] = eax */
  /* relift: FUN_0020d152(0); */
  /* relift: FUN_0020d18c(0); */
  /* relift: FUN_0020d18c(0); */
  /* relift: FUN_0020d1ea(0); */
  /* cmp edx, 8 -> jb 0x20d6b5 */
  /* test eax, eax -> jl 0x20d6ff */
  /* relift: FUN_0020d303(0, 0, 0, 0); */
  /* cmp esi, 0xe -> jb 0x20d6e2 */
  /* test ecx, ecx -> je 0x20d717 */
  /* relift: FUN_0020d45c(0); */
  /* test ecx, ecx -> je 0x20d72e */
  /* relift: FUN_0020d480(0); */
  /* relift: FUN_0020d703(0, 0, 0, 0); */
  /* relift: FUN_0020d71a(0); */
  /* relift: FUN_0020cc3b(0); */
  /* relift: FUN_0020480b(0); */
  /* relift: FUN_0020d4a4(0); */
  /* test edi, edi -> je 0x20d7bf */
  /* relift: FUN_0020484d(0); */
  /* relift: FUN_0020d63b(0, 0); */
  /* test ebx, ebx -> jl 0x20d834 */
  /* relift: FUN_0020d570(0, 0); */
  /* test edi, edi -> je 0x20d7e3 */
  /* relift: FUN_0020cca8(0, 0); */
  /* relift: FUN_0020d042(0, 0); */
  /* test ebx, ebx -> jl 0x20d834 */
  /* test edi, edi -> jne 0x20d7f6 */
  /* relift: FUN_0020cd7d(0); */
  /* relift: FUN_0020cea7(0); */
  /* relift: FUN_0020d1ea(0); */
  /* relift: FUN_0020e7d4(0); */
  /* relift: FUN_0020e7d4(0); */
  /* test edi, edi -> jne 0x20d854 */
  /* relift: FUN_0020782d(0, 0); */
  /* relift: FUN_0020d731(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20d87a */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020cc3b(0); */
  /* test edx, edx -> je 0x20d8c3 */
  /* relift: cmp eax, dword ptr [ecx + 4] -> jne 0x20d8d7 */
  /* test edx, edx -> je 0x20d904 */
  /* test edi, edi -> je 0x20d922 */
  /* test ebx, ebx -> je 0x20d922 */
  /* cmp edi, edx -> jne 0x20d91c */
  /* cmp ebx, esi -> jne 0x20d927 */
  /* relift: FUN_0020d88d(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20d972 */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020d8e1(0, 0); */
  /* relift: FUN_0020d938(0); */
  /* relift: FUN_0020d88d(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20d9bd */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020cbda(0); */
  /* relift: FUN_0020d979(*(int *)((char *)esi + 0x20)); */
  /* cmp eax, 1 -> jbe 0x20da47 */
  /* relift: FUN_0020d979(0); */
  /* relift: cmp (int16_t)edx, word ptr [ebx + 0x14] -> ja 0x20dae9 */
  /* test eax, eax -> je 0x20dae9 */
  /* cmp (int16_t)ecx, (int16_t)edx -> jb 0x20da80 */
  /* test edi, edi -> je 0x20da7e */
  /* relift: cmp word ptr [edi + 0x12], (int16_t)ecx -> jbe 0x20da80 */
  /* test eax, eax -> jne 0x20da6b */
  /* test edi, edi -> je 0x20dae9 */
  /* relift: FUN_0020d8a7(0, 0); */
  /* relift: FUN_0020d979(0); */
  /* cmp (int16_t)eax, (int16_t)ecx -> jbe 0x20dace */
  /* relift: FUN_0020d8a7(0); */
  /* relift: FUN_0020d979(0); */
  /* relift: FUN_0020d8a7(0, 0, 0, 0); */
  /* relift: FUN_0020d979(0); */
  /* cmp edx, ecx -> jne 0x20db2d */
  /* cmp edx, ecx -> jne 0x20db4a */
  /* test eax, eax -> jne 0x20db17 */
  /* relift: FUN_0020d8a7(0); */
  /* relift: FUN_0020d979(0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test esi, esi -> je 0x20dbd6 */
  /* relift: cmp ebx, dword ptr [esi + 0xc] -> jne 0x20dbc6 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x12] -> jbe 0x20dbcd */
  /* test esi, esi -> jne 0x20dbbb */
  /* test esi, esi -> je 0x20dbd6 */
  /* relift: FUN_0020da50(0); */
  /* test esi, esi -> je 0x20dbeb */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20dbfa */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_0020daf0(0); */
  /* test eax, eax -> je 0x20dc81 */
  /* test ecx, ecx -> je 0x20dc81 */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020d2c6(0, 0, 0); */
  /* mem[0xfe802040] = eax */
  /* mem[0xfe8020d4] = eax */
  /* mem[0xfe802048] = eax */
  /* mem[0xfe8020dc] = eax */
  /* mem[0xfe8020d4] = edx */
  /* relift: cmp dword ptr [ebx + 0x1c], ecx -> jae 0x20de75 */
  /* relift: FUN_00203609(0, 0); */
  /* cmp eax, edi -> jbe 0x20de4b */
  /* mem[0xfe8020d4] = eax */
  /* relift: FUN_00203664(0); */
  /* mem[0x00222d90] = esi */
  /* mem[0x00222d94] = edx */
  /* relift: FUN_0020de7e(0x49de12ba, 0x7fa49bca, 0, 0); */
  /* relift: FUN_0020de7e(0, 0, 0, 0); */
  /* relift: FUN_0020dfc2(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp + 0x18], ebx -> je 0x20e025 */
  /* cmp ecx, 8 -> jb 0x20e014 */
  /* relift: FUN_0020de7e(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp + 0x18], ebx -> je 0x20e041 */
  /* relift: cmp dword ptr [ebp + 0x10], ebx -> jbe 0x20e08e */
  /* relift: FUN_0020de7e(0, 0, 0, 0); */
  /* relift: FUN_0020dfc2(0, 0, 0); */
  /* relift: cmp dword ptr [ebp + 0x18], edi -> je 0x20e0e0 */
  /* cmp eax, edi -> je 0x20e0f7 */
  /* cmp eax, edi -> jne 0x20e0ec */
  /* relift: FUN_0020de7e(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp + 0x18], edi -> je 0x20e111 */
  /* relift: cmp dword ptr [ebp + 0x10], edi -> jbe 0x20e15e */
  /* relift: FUN_0020de7e(0, 0, 0, 0); */
  /* relift: FUN_00203609(0, 0); */
  /* relift: FUN_00203664(0); */
  /* mem[0x00222c68] = eax */
  /* test eax, eax -> je 0x20e2e1 */
  /* relift: test byte ptr [0xfec00134], 1 -> jne 0x20e2c7 */
  /* mem[0xfec0012c] = eax */
  /* test (char)eax, 8 -> je 0x20e310 */
  /* mem[0xfec0012c] = eax */
  /* test eax, eax -> je 0x20e330 */
  /* relift: test dword ptr [0xfec00130], esi -> je 0x20e317 */
  /* relift: FUN_0020e2bb(0, 0); */
  /* test eax, eax -> je 0x20e389 */
  /* mem[0xfec00130] = ecx */
  /* relift: FUN_0020e2bb(0, 0); */
  /* test eax, eax -> je 0x20e3a6 */
  /* relift: FUN_0020e38c(0, 0, 0, 0); */
  /* test eax, eax -> je 0x20e3d5 */
  /* relift: FUN_0020e355(0, 0); */
  /* test eax, eax -> je 0x20e3d5 */
  /* relift: cmp (int16_t)esi, word ptr [ebp + 0xa] -> je 0x20e3d5 */
  /* relift: FUN_0020e38c(19, 0, 0); */
  /* test eax, eax -> jne 0x20e3ee */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: cmp byte ptr [ebp + 0xc], 0 -> je 0x20e484 */
  /* relift: test byte ptr [esi + 0xc], 1 -> je 0x20e46c */
  /* relift: cmp dword ptr [ebp + 0x10], eax -> je 0x20e49e */
  /* relift: cmp dword ptr [ebp + 0x14], eax -> je 0x20e4b2 */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: cmp dword ptr [esi], 1 -> jne 0x20e4ef */
  /* mem[0xfec0017c] = eax */
  /* relift: cmp byte ptr [eax - 0x13ffefc], dl -> jne 0x20e550 */
  /* cmp eax, edx -> ja 0x20e54c */
  /* cmp edi, edx -> je 0x20e574 */
  /* cmp (char)eax, 2 -> jae 0x20e587 */
  /* cmp edx, eax -> jb 0x20e580 */
  /* relift: FUN_0020e341(0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_00203609(48, 0); */
  /* test ecx, ecx -> je 0x20e61b */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20e62a */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test (char)eax, 2 -> je 0x20e651 */
  /* relift: FUN_0020e43d(0, 0, 0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_0020e631(0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* test (char)ecx, (char)ecx -> jne 0x20e740 */
  /* relift: cmp dword ptr [esi], 1 -> jne 0x20e75a */
  /* mem[0xfec0017c] = eax */
  /* relift: FUN_0020e43d(0, 0, 0, 0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_0020e40b(0, 0); */
  /* relift: FUN_0020e70e(0, 0); */
  /* relift: FUN_0020e43d(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp + 8], edi -> je 0x20e7c0 */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: test byte ptr [eax - 0x13ffefa], 1 -> je 0x20e7fd */
  /* relift: FUN_0020e70e(0, 0); */
  /* relift: cmp dword ptr [ebp + 8], -1 -> je 0x20e80d */
  /* relift: FUN_0020e58f(0); */
  /* relift: FUN_0020e631(0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_0020cbda(256, 4096, 0, 0); */
  /* relift: FUN_0020cbda(8192, 4096, 0, 0); */
  /* test edi, edi -> jl 0x20e8db */
  /* relift: FUN_0020e70e(0, 0); */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x20e8ea */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_0020e783(0); */
  /* relift: FUN_0020cc3b(0); */
  /* relift: FUN_0020cc3b(0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: test byte ptr [esi + 0xc], 2 -> jne 0x20e95d */
  /* relift: FUN_0020e831(*(int *)((char *)esi + 0x20), 8192); */
  /* cmp (char)ecx, (char)ebx -> je 0x20e9ba */
  /* cmp (char)ecx, 2 -> jbe 0x20e9bd */
  /* relift: FUN_0020e43d(0, 0, 0); */
  /* cmp eax, ebx -> je 0x20e9ba */
  /* relift: FUN_0020e783(0, 0); */
  /* relift: test dword ptr [eax + edi], ecx -> je 0x20ea58 */
  /* test eax, eax -> je 0x20ea58 */
  /* relift: test byte ptr [esi + 8], 1 -> je 0x20ea3d */
  /* relift: FUN_0020e96f(0, 0); */
  /* relift: cmp dword ptr [ebp - 8], 2 -> jb 0x20e9fd */
  /* relift: test byte ptr [ebp - 4], 3 -> je 0x20ea85 */
  /* mem[0xfec00130] = ecx */
  /* relift: cmp byte ptr [esi], 0 -> je 0x20eade */
  /* relift: cmp dword ptr [edi], 0 -> je 0x20eadb */
  /* relift: FUN_0020e96f(0, 0); */
  /* test ebx, ebx -> jne 0x20eaa1 */
  /* relift: FUN_0020e8f3(0, 0); */
  /* relift: test byte ptr [ebp + 8], 1 -> je 0x20eb15 */
  /* relift: FUN_00203664(0); */
  /* relift: FUN_0020e9c6(0, 0); */
  /* relift: FUN_0020ea9a(0, 0); */
  /* test ecx, ecx -> je 0x20eb4d */
  /* relift: FUN_0020eaf8(0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: FUN_0020eb39(0); */
  /* relift: FUN_002063cb(0, 0, 0, 0); */
  /* relift: cmp dword ptr [0x222c70], ebx -> je 0x20ebad */
  /* mem[0x00222c70] = ebx */
  /* relift: cmp word ptr [esi], 0x13 -> jne 0x20ebc0 */
  /* relift: cmp dword ptr [esi], ebx -> je 0x20ebd1 */
  /* relift: FUN_0020eb50(0); */
  /* cmp esi, 2 -> jb 0x20ebd3 */
  /* relift: FUN_0020eb80(0, 0); */
  /* relift: FUN_0020eb80(0, 0); */
  /* relift: FUN_0020e2e8(0, 0, 0); */
  /* test eax, eax -> jne 0x20ec30 */
  /* relift: FUN_0020e3da(0, 0); */
  /* test ebx, ebx -> jl 0x20ece7 */
  /* relift: test byte ptr [edi + 8], 1 -> jne 0x20ec6e */
  /* test ebx, ebx -> jl 0x20ece6 */
  /* relift: FUN_0020e38c(0, 0); */
  /* test eax, eax -> jne 0x20ecba */
  /* test ebx, ebx -> jl 0x20ece6 */
  /* relift: FUN_0020e38c(12, 2056); */
  /* test eax, eax -> jne 0x20ecd0 */
  /* test ebx, ebx -> jl 0x20ece6 */
  /* relift: FUN_002078db(0, 0); */
  /* relift: FUN_0020d303(0); */
  /* relift: FUN_0020d303(0); */
  /* relift: FUN_00203609(40, 0); */
  /* cmp eax, ebx -> je 0x20ef6e */
  /* relift: FUN_0020dc40(0, 0); */
  /* relift: FUN_0020dc83(0); */
  /* relift: FUN_0020dd89(0, 0x00632de0, 800); */
  /* relift: FUN_0020dd89(1536, 0, 1408); */
  /* relift: FUN_0020ed6d(0, 0, 0); */
  /* relift: FUN_0020dd89(0); */
  /* cmp ebx, 6 -> jb 0x20efc0 */
  /* relift: FUN_0020dd89(0); */
  /* relift: FUN_0020dd89(1024); */
  /* relift: FUN_0020ee25(0x00010000); */
  /* relift: FUN_00207bad(0); */
  /* relift: cmp ebx, dword ptr [ebx - 0x2d] -> jl 0x20f202 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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

/* 0x00223be7 */
void ioctlsocket(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp ecx, ebx -> je 0x223bf9 */
  /* relift: cmp dword ptr [ecx + 0x964], ebx -> jg 0x223c0b */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* cmp esi, ebx -> jne 0x223c22 */
  /* relift: cmp dword ptr [ebp + 0xc], 0x8004667e -> je 0x223c72 */
  /* relift: cmp dword ptr [ebp + 0xc], 0x4004667f -> je 0x223c3b */
  /* relift: test byte ptr [esi + 0xc], 2 -> jne 0x223c5f */
  /* cmp edi, edx -> jne 0x223c55 */
  /* test edx, edx -> jne 0x223c62 */
  /* relift: FUN_002236be(0xfffdffff, 0); */
  SetLastError(ebx);
  /* cmp esi, eax -> jle 0x223cc3 */
  /* test esi, esi -> jg 0x223cca */
  /* cmp edx, eax -> jle 0x223cdd */
  /* test edx, edx -> jg 0x223ce3 */
  /* relift: cmp byte ptr [ecx + 0x7c], 1 -> jbe 0x223d04 */
  /* relift: cmp edx, dword ptr [ecx + 0x5c] -> jge 0x223d04 */
  /* test ecx, ecx -> je 0x223d6c */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jle 0x223d6c */
  /* relift: FUN_0022361e(0, 0); */
  /* test edx, edx -> je 0x223dec */
  /* relift: cmp dword ptr [ebp + 0xc], 0xffff -> je 0x223d73 */
  /* cmp ecx, eax -> jg 0x223e40 */
  /* cmp ecx, 0xffffff7f -> je 0x223e27 */
  /* cmp ecx, -5 -> je 0x223e1f */
  /* cmp ecx, ebx -> je 0x223e12 */
  /* cmp ecx, edi -> je 0x223e07 */
  /* cmp ecx, 0x20 -> je 0x223df4 */
  /* cmp ecx, 0x80 -> jne 0x223e8d */
  /* relift: test byte ptr [edx + 0xc], (char)ebx -> je 0x223e8d */
  SetLastError(0);
  /* test (char)ebx, (char)eax -> jne 0x223e8d */
  /* relift: test byte ptr [edx + 0xc], (char)ebx -> je 0x223e8d */
  /* relift: test byte ptr [edx + 0xc], 2 -> je 0x223e8d */
  /* test (char)eax, 2 -> je 0x223e8d */
  /* relift: cmp dword ptr [esi], edi -> jae 0x223dc9 */
  /* test ecx, ecx -> je 0x223eca */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jg 0x223ed1 */
  /* relift: FUN_0022361e(0); */
  /* test edx, edx -> je 0x223f29 */
  /* relift: test byte ptr [edx + 0xc], 0x10 -> jne 0x223eed */
  SetLastError(eax);
  /* test ecx, ecx -> je 0x223f40 */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jg 0x223f47 */
  /* relift: FUN_0022361e(0); */
  /* test edx, edx -> je 0x223fa0 */
  /* relift: test byte ptr [edx + 0xc], 0x20 -> jne 0x223f63 */
  SetLastError(eax);
  /* test eax, eax -> jle 0x22401f */
  /* relift: cmp dword ptr [eax], 0x1387 -> jb 0x224013 */
  /* test esi, esi -> je 0x2240ab */
  /* test (char)eax, 0x10 -> je 0x22406b */
  /* test (char)ecx, 1 -> jne 0x224068 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp + 0xc] -> jne 0x224068 */
  /* test ecx, eax -> jne 0x224083 */
  /* test ecx, edi -> jne 0x224083 */
  /* test edi, 0x40000 -> je 0x224083 */
  /* test esi, esi -> je 0x2240ab */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jg 0x223ff3 */
  /* relift: FUN_002236be(0, 16); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x002240c3 */
void listen(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edi, edi -> je 0x2240d3 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x2240e2 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2240f7 */
  /* test (char)eax, 0x20 -> je 0x224105 */
  /* test (char)eax, 0x10 -> jne 0x224110 */
  /* relift: FUN_0022a590(0, 0); */
  /* test eax, eax -> jl 0x224124 */
  SetLastError(eax);
  /* test edx, edx -> je 0x22415e */
  /* relift: cmp dword ptr [ebx], eax -> je 0x2241c4 */
  /* relift: cmp edx, dword ptr [ebp + 0x10] -> jl 0x2241b3 */
  /* relift: cmp edx, dword ptr [ebp + 0x10] -> jne 0x2241e6 */
  /* relift: FUN_0022361e(0); */
  xapi_GetLastError();
  /* relift: cmp eax, dword ptr [ebp - 0x10] -> jl 0x224194 */
  /* test (char)eax, 2 -> je 0x2242d2 */
  /* relift: cmp dword ptr [esi + 0x40], 0 -> jge 0x22425e */
  /* cmp ebx, ecx -> jne 0x224257 */
  /* relift: FUN_0022a8d5(0, 0); */
  /* test (char)ecx, 0x20 -> je 0x2242f3 */
  /* relift: cmp eax, dword ptr [esi + 0x58] -> jae 0x2242ad */
  /* test eax, ebx -> je 0x2242f3 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jl 0x2242f3 */
  /* relift: FUN_002236be(0, 128); */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x224314 */
  /* relift: FUN_002236be(0xffff03ff, 0); */
  /* relift: FUN_00224223(0, 0, 0, 0); */
  /* test eax, eax -> je 0x224347 */
  __allmul();
  /* relift: FUN_002236be(0, 0); */
  /* test esi, esi -> jl 0x22439e */
  /* relift: cmp edx, dword ptr [ebp + 0x14] -> jne 0x224415 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 8] -> jne 0x224415 */
  /* relift: cmp edx, dword ptr [ebp + 0xc] -> je 0x2243f9 */
  /* test edx, edx -> jne 0x224415 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 0x10] -> je 0x224409 */
  /* test (int16_t)edx, (int16_t)edx -> jne 0x224415 */
  /* test edi, edi -> je 0x224427 */
  /* cmp edi, ebx -> jae 0x224415 */
  /* test edx, edx -> je 0x224464 */
  /* relift: cmp dword ptr [esp + 4], 0 -> je 0x224476 */
  /* cmp (char)ecx, 0xe0 -> jne 0x224490 */
  /* cmp eax, -1 -> je 0x224490 */
  /* relift: cmp dword ptr [ecx + 0x968], edx -> jb 0x2244cf */
  /* relift: FUN_00226013(0, 0); */
  /* cmp edx, ebx -> je 0x2245fe */
  /* cmp edx, ebx -> je 0x2245fe */
  /* relift: cmp dword ptr [ebp + 8], ebx -> je 0x2245e7 */
  /* relift: FUN_00226045(0, 0); */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jle 0x22466e */
  /* relift: FUN_0022361e(0, 0); */
  /* test edi, edi -> jne 0x224680 */
  SetLastError(10093);
  /* relift: cmp dword ptr [ebp + 0xc], 6 -> je 0x22480a */
  /* relift: cmp dword ptr [ebp + 0xc], 0xffff -> jne 0x224801 */
  /* cmp ecx, 0xffffff7f -> je 0x22477a */
  /* cmp ecx, -5 -> je 0x224755 */
  /* cmp ecx, 4 -> je 0x224737 */
  /* cmp ecx, 0x20 -> je 0x224711 */
  /* cmp ecx, 0x80 -> jne 0x2247ae */
  /* relift: test byte ptr [edi + 0xc], 2 -> je 0x2247ae */
  /* relift: test byte ptr [edi + 0xc], 2 -> jne 0x2247ae */
  /* relift: FUN_002236be(0xfffeffff, 0); */
  /* relift: test dword ptr [edi + 0xc], eax -> je 0x224745 */
  /* test esi, esi -> jne 0x224763 */
  /* relift: test dword ptr [edi + 0xc], eax -> je 0x22476a */
  /* test esi, esi -> je 0x22476a */
  /* relift: test byte ptr [edi + 0xc], 2 -> je 0x2247ae */
  /* relift: FUN_00223caf(0, *(int *)((char *)edi + 0x58), 0); */
  /* relift: test byte ptr [edi + 0xc], 2 -> je 0x224816 */
  /* relift: FUN_002236be(0xffefffff, 0); */
  SetLastError(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00224881 */
int bind(void *xnet, unsigned int socket, const void *name, int namelen)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0x224892 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x224899 */
  /* relift: FUN_0022361e(0); */
  /* test esi, esi -> je 0x2248f8 */
  /* relift: test byte ptr [esi + 0xc], 0x10 -> je 0x2248b5 */
  /* relift: cmp dword ptr [ecx + 4], 0 -> je 0x2248c6 */
  /* relift: FUN_00223faa(0, 0); */
  /* test eax, eax -> jl 0x2248e0 */
  SetLastError(eax);
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x00224904 */
int connect(void *xnet, unsigned int socket, const void *name, int namelen)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp ebx, esi -> je 0x224919 */
  /* relift: cmp dword ptr [ebx + 0x964], esi -> jg 0x22492b */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* cmp edi, esi -> jne 0x224942 */
  /* test dl, 0x20 -> je 0x224956 */
  /* test dl, 2 -> je 0x224956 */
  /* relift: FUN_0022c6b8(0, 0, 0); */
  /* relift: FUN_0022bde3(0, 0); */
  /* test esi, esi -> jl 0x224997 */
  SetLastError(eax);
  /* relift: FUN_0022bde3(0, 0); */
  /* test esi, esi -> jl 0x224997 */
  /* relift: FUN_00224326(0, 8192, 0); */
  /* relift: FUN_002236be(0, 128); */
  /* test esi, esi -> jl 0x224997 */
  /* cmp edi, esi -> je 0x224a0c */
  /* relift: cmp dword ptr [edi + 0x964], esi -> jg 0x224a1e */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test ebx, ebx -> jne 0x224a35 */
  /* relift: test byte ptr [ebx + 0xc], 2 -> je 0x224adf */
  /* relift: cmp byte ptr [ebx + 0x7c], 1 -> jne 0x224adf */
  /* relift: FUN_0022a904(0, 0); */
  /* test esi, esi -> jne 0x224a84 */
  /* relift: test byte ptr [ebx + 0xe], 2 -> jne 0x224a8a */
  /* relift: FUN_00224326(0, 4096, 0); */
  /* test eax, eax -> je 0x224a49 */
  /* test eax, eax -> jl 0x224a93 */
  /* test esi, esi -> je 0x224ae6 */
  /* relift: FUN_002236be(0, 0x01000000); */
  /* test ecx, ecx -> je 0x224ae6 */
  /* test edx, edx -> je 0x224ae6 */
  SetLastError(0);
  /* relift: cmp dword ptr [ecx + 0x964], edi -> jg 0x224b42 */
  SetLastError(10093);
  /* cmp eax, edi -> je 0x224b6b */
  SetLastError(10022);
  /* cmp eax, 1 -> jne 0x224bba */
  /* test eax, eax -> je 0x224df4 */
  /* relift: FUN_00224145(socket, 0, 0, 54272); */
  /* test ebx, ebx -> jne 0x224dfd */
  /* relift: FUN_00224145(name, 0, 0, 10240); */
  /* test ebx, ebx -> jne 0x224dfd */
  /* relift: FUN_00224145(namelen, 0, 0, 32768); */
  /* test ebx, ebx -> jne 0x224dfd */
  /* test esi, esi -> je 0x224d69 */
  __allmul();
  __allmul();
  /* relift: cmp dword ptr [ebp + 8], ebx -> jle 0x224cf6 */
  /* relift: FUN_00224223(0, 0, 0); */
  /* test eax, eax -> jne 0x224cf6 */
  /* relift: cmp eax, dword ptr [ebp + 8] -> jl 0x224cc5 */
  /* relift: cmp dword ptr [ebp + 0x18], eax -> jne 0x224d72 */
  /* cmp ebx, 3 -> jle 0x224d38 */
  /* test edx, edx -> je 0x224d2d */
  /* test eax, eax -> jl 0x224d58 */
  /* cmp eax, ebx -> jl 0x224d72 */
  /* cmp eax, 0x102 -> je 0x224d72 */
  /* cmp eax, ecx -> je 0x224d7d */
  /* cmp eax, ecx -> je 0x224d86 */
  /* cmp eax, ecx -> je 0x224d8f */
  /* relift: FUN_00224223(0, 0, 0); */
  /* test eax, eax -> je 0x224de8 */
  /* cmp edi, edx -> jae 0x224dd3 */
  /* relift: cmp dword ptr [ecx], ebx -> je 0x224dd1 */
  /* cmp edi, edx -> jb 0x224dc5 */
  /* cmp edi, edx -> jne 0x224de5 */
  /* cmp edx, 0x40 -> jae 0x224de5 */
  /* test eax, eax -> jle 0x224e36 */
  /* test edi, edi -> je 0x224e2e */
  /* relift: cmp dword ptr [esi], 0 -> je 0x224e2e */
  /* relift: FUN_002236be(0xffff03ff, 0); */
  /* relift: cmp dword ptr [ebp - 0x10], eax -> je 0x224e52 */
  /* relift: cmp dword ptr [ebp - 0x10], 0 -> je 0x224e52 */
  /* relift: cmp dword ptr [ebp - 4], eax -> je 0x224e65 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x224e65 */
  /* relift: cmp dword ptr [ebp - 0xc], eax -> je 0x224e78 */
  /* relift: cmp dword ptr [ebp - 0xc], 0 -> je 0x224e78 */
  /* test ebx, ebx -> je 0x224e82 */
  /* relift: cmp dword ptr [ebx + 0x20], 0 -> je 0x224e9e */
  /* test eax, eax -> jne 0x224eb0 */
  /* cmp eax, ecx -> jne 0x224ebb */
  /* test eax, eax -> jne 0x224ed3 */
  /* relift: cmp eax, dword ptr [esi + 0x58] -> jae 0x224f31 */
  /* test eax, eax -> jne 0x224f5e */
  /* cmp esi, eax -> je 0x22501d */
  /* relift: cmp dword ptr [edi + 0x30], esi -> jne 0x224fe9 */
  /* relift: cmp dword ptr [edi + 0x20], esi -> jne 0x224ff1 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x00225021 */
int socket(void *xnet, int af, int type, int protocol)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edi, edi -> je 0x225031 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x225038 */
  /* relift: cmp dword ptr [esp + 8], 0 -> je 0x22504d */
  /* relift: cmp dword ptr [esp + 8], 2 -> je 0x22504d */
  /* test ecx, ecx -> je 0x225066 */
  /* cmp ecx, 1 -> je 0x225066 */
  /* cmp ecx, 2 -> je 0x225066 */
  /* test eax, eax -> je 0x225078 */
  /* cmp eax, 6 -> je 0x225078 */
  /* cmp eax, 0x11 -> jne 0x2250aa */
  /* test ecx, ecx -> jne 0x225083 */
  /* test eax, eax -> jne 0x225094 */
  /* cmp ecx, edx -> je 0x2250ba */
  SetLastError(eax);
  /* relift: FUN_00224493(0, 0, 0); */
  /* test esi, esi -> jne 0x2250da */
  SetLastError(10055);
  /* relift: FUN_002236be(0, 0x01000000); */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x20), 0); */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x30), 0); */
  /* relift: FUN_00223b1b(0); */
  /* relift: FUN_00223b00(0); */
  /* relift: cmp dword ptr [edi], edi -> jne 0x225150 */
  /* test eax, eax -> je 0x225182 */
  /* relift: FUN_002267c6(0); */
  /* test ebx, ebx -> je 0x2251da */
  /* relift: cmp dword ptr [ebx + 0x964], 0 -> jg 0x2251e4 */
  /* relift: FUN_0022361e(0); */
  /* relift: cmp dword ptr [esi + 0xc], edi -> jne 0x22524b */
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x22524b */
  WaitForSingleObject(*(int *)((char *)esi + 0x10), 0);
  /* relift: FUN_00224fcf(0, 0, 0); */
  /* cmp eax, edi -> je 0x22526a */
  /* test eax, eax -> jl 0x225271 */
  SetLastError(eax);
  /* test ebp, ebp -> je 0x2252aa */
  /* relift: cmp dword ptr [ebp + 0x964], 0 -> jg 0x2252b9 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2252ce */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x20), 0); */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x30), 0); */
  /* test (char)eax, 0x20 -> jne 0x22533d */
  /* test (char)eax, 0x10 -> jne 0x22533d */
  /* test (char)eax, 8 -> je 0x225358 */
  /* test eax, eax -> je 0x225388 */
  /* test eax, eax -> jne 0x225388 */
  /* cmp eax, edx -> je 0x2253f8 */
  /* relift: cmp dword ptr [ebp + 8], edx -> je 0x2253ce */
  /* test ecx, 0x20000 -> je 0x2253ea */
  /* cmp esi, edx -> je 0x2253e0 */
  /* relift: cmp byte ptr [ebx + 0x7c], 7 -> jae 0x2253f8 */
  /* relift: FUN_0022c458(0, 0); */
  /* relift: FUN_0022af86(0, 0); */
  /* cmp esi, 0x800703e5 -> jne 0x225498 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> jne 0x2254c4 */
  __allmul();
  /* relift: cmp dword ptr [ebp - 0x14], esi -> jne 0x225485 */
  /* relift: FUN_00224fcf(0, 0, 0x8007274c); */
  /* test eax, eax -> je 0x2254c4 */
  /* relift: cmp dword ptr [esi + 0x14], 0 -> jne 0x2254f3 */
  /* test (char)eax, 4 -> je 0x22550e */
  /* test eax, eax -> je 0x225544 */
  /* test eax, eax -> jne 0x225544 */
  /* relift: cmp eax, dword ptr [edi + 0x58] -> jb 0x225581 */
  /* test ebx, ebx -> je 0x225595 */
  /* relift: FUN_00224f01(0, 0); */
  /* cmp ebx, eax -> je 0x2255ef */
  /* test ebx, ebx -> jl 0x2255c6 */
  /* relift: FUN_0022c517(0, 0); */
  /* relift: test byte ptr [edi + 0xe], 2 -> jne 0x2255b8 */
  /* relift: cmp dword ptr [edi + 0x30], 0 -> jne 0x2255b8 */
  /* relift: FUN_00224326(0, 2048, *(int *)((char *)edi + 0x50)); */
  /* test eax, eax -> jge 0x225581 */
  /* relift: FUN_0022b612(0, 0); */
  /* cmp eax, ecx -> je 0x2255ed */
  /* relift: FUN_0022bd4e(0, af); */
  /* relift: FUN_002236be(0, 0x0400000c); */
  /* relift: FUN_00225114(0); */
  /* relift: test byte ptr [ecx + 0xf], 1 -> je 0x225689 */
  /* relift: FUN_002236be(0, 0x02000000); */
  /* relift: FUN_00224606(0); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x002256bb */
int recv(void *xnet, unsigned int socket, char *buf, int len, int flags)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0x2256d1 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x2256e0 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2256f4 */
  /* relift: FUN_0022530d(0, 0); */
  /* test eax, eax -> jl 0x225728 */
  SetLastError(eax);
  /* test ebx, ebx -> je 0x225761 */
  /* relift: cmp dword ptr [ebx + 0x964], 0 -> jg 0x225770 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test edi, edi -> jne 0x225784 */
  /* relift: FUN_0022530d(0, 0, 0); */
  SetLastError(eax);
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jg 0x22580f */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test ebx, ebx -> jne 0x225823 */
  /* relift: FUN_0022530d(0, 0); */
  SetLastError(eax);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x002258a4 */
int send(void *xnet, unsigned int socket, const char *buf, int len, int flags)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;
  int lift_a28 = 0;
  int lift_a5 = 0;

  /* test edi, edi -> je 0x2258ba */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x2258c9 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2258dd */
  /* relift: FUN_002254cd(0, 0); */
  /* test eax, eax -> jl 0x225914 */
  SetLastError(eax);
  /* test edi, edi -> je 0x22594d */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x22595c */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x225970 */
  /* relift: FUN_002233b8(0, 0); */
  /* relift: FUN_002254cd(0, 0); */
  /* test eax, eax -> jl 0x2259ad */
  SetLastError(eax);
  /* relift: cmp dword ptr [ebx + 0x964], 0 -> jg 0x2259f1 */
  /* relift: FUN_0022361e(0); */
  /* test esi, esi -> je 0x225ac9 */
  /* relift: FUN_002233b8(0, 0); */
  /* test (char)ecx, 2 -> jne 0x225a91 */
  /* test edi, edi -> je 0x225a91 */
  /* test eax, eax -> je 0x225a8a */
  /* relift: cmp word ptr [edi + 2], 0 -> je 0x225a8a */
  /* cmp dl, 0xe0 -> jne 0x225a4e */
  /* cmp eax, -1 -> jne 0x225a8a */
  /* cmp (char)eax, 0x7f -> jne 0x225a59 */
  /* cmp eax, 0x100007f -> jne 0x225a8a */
  /* cmp eax, -1 -> jne 0x225a6d */
  /* test ecx, 0x10000 -> jne 0x225a6d */
  /* test (char)ecx, 0x10 -> jne 0x225a85 */
  /* relift: FUN_00223faa(0); */
  /* test eax, eax -> jl 0x225ab1 */
  /* relift: FUN_002254cd(0, 0); */
  /* test eax, eax -> jl 0x225ab1 */
  SetLastError(eax);
  /* relift: test byte ptr [edi + 3], 2 -> je 0x225b25 */
  /* relift: FUN_00225601(0, 0); */
  /* cmp eax, esi -> jne 0x225af2 */
  /* relift: FUN_00225601(0, 0); */
  /* cmp eax, esi -> jne 0x225b0a */
  /* test edi, edi -> je 0x225b37 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x225b46 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x225b5b */
  /* relift: FUN_00224606(0); */
  /* relift: FUN_002236be(0xfeffffff, 0); */
  /* relift: FUN_00225601(0, 0); */
  /* test eax, eax -> jge 0x225b72 */
  /* test eax, eax -> je 0x225b72 */
  SetLastError(eax);
  /* relift: FUN_002257e7(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x225c0a */
  /* relift: FUN_002259cf(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x225c73 */
  /* relift: FUN_002297f4(0, 0); */
  /* relift: FUN_00225ad7(0, 0); */
  /* relift: FUN_0022955c(0x20000000); */
  /* relift: FUN_00227b03(0, 0); */
  /* relift: cmp eax, dword ptr [esp + 8] -> je 0x225d50 */
  /* test eax, eax -> jne 0x225d3d */
  /* relift: cmp dword ptr [ecx + 4], eax -> jne 0x225d6a */
  /* test ecx, ecx -> jne 0x225d74 */
  /* cmp edi, edx -> je 0x225dd1 */
  /* relift: cmp esi, dword ptr [edi + 8] -> jbe 0x225dd1 */
  /* relift: cmp esi, dword ptr [ecx + 8] -> jb 0x225db9 */
  /* relift: cmp esi, dword ptr [eax + 8] -> jae 0x225dfd */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: cmp ebx, dword ptr [eax + 8] -> jb 0x225e3c */
  /* cmp eax, esi -> jne 0x225e1a */
  /* test edx, edx -> je 0x225e60 */
  /* test eax, eax -> je 0x225e7f */
  /* test (char)eax, (char)eax -> jne 0x225e7f */
  /* cmp eax, 5 -> ja 0x225f51 */
  /* relift: cmp dword ptr [ecx], ecx -> jne 0x225f65 */
  /* cmp eax, 5 -> jbe 0x225f44 */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 4] -> jbe 0x225f6c */
  /* cmp eax, ecx -> jne 0x225fbc */
  /* relift: FUN_00225f13(0, 0); */
  /* test edx, edx -> je 0x226040 */
  /* relift: cmp byte ptr [edx + 1], (char)ebx -> jne 0x226090 */
  /* relift: cmp byte ptr [edx + 1], (char)ebx -> jne 0x2260b1 */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x2260c5 */
  /* cmp (int16_t)eax, (int16_t)edx -> ja 0x2260d5 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* relift: FUN_002295b8(0, 484); */
  /* test eax, eax -> jge 0x226174 */
  /* test eax, eax -> jge 0x2261a8 */
  /* relift: cmp dword ptr [ebp - 0x54], edx -> jne 0x2261d2 */
  /* relift: cmp dword ptr [ebp - 0x24c], ecx -> jb 0x2261d2 */
  /* relift: cmp dword ptr [ebp - 0x248], ecx -> jae 0x2261e7 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  XcSHAInit(0);
  XcSHAUpdate(0, 0, 0);
  XcSHAFinal(0, 0);
  XcRC4Key(0, 0, 0);
  /* relift: cmp dword ptr [ebp - 4], esi -> je 0x2262bf */
  XcRC4Crypt(0, 20, 0);
  /* relift: FUN_00225e40(0, 0); */
  XcRC4Crypt(0, 0, 0);
  /* relift: FUN_002262c4(0, 0, 0, 0); */
  /* relift: FUN_00225d20(0, 0); */
  /* relift: cmp dword ptr [esi], 0 -> jne 0x226366 */
  /* test (char)ecx, 1 -> je 0x22639a */
  /* cmp (char)ecx, 0x80 -> jne 0x2263af */
  /* cmp (char)ecx, 0xc0 -> jne 0x2263c6 */
  /* relift: FUN_00225e03(0, 0); */
  /* relift: FUN_00226045(0, 0); */
  /* relift: FUN_00225d20(0, 0); */
  /* relift: FUN_00226412(0); */
  /* relift: cmp dword ptr [esi], 0 -> jne 0x226432 */
  /* test eax, eax -> je 0x226472 */
  /* cmp eax, -1 -> je 0x226472 */
  /* cmp (char)eax, 0xe0 -> je 0x226472 */
  /* cmp ecx, 0x7f -> je 0x226472 */
  /* relift: FUN_0022955c(32, 0, 0, 0); */
  /* test eax, eax -> je 0x22649e */
  /* cmp (char)ecx, 0xb -> je 0x22649e */
  /* cmp (char)ecx, 0x2a -> je 0x22649e */
  /* test (char)eax, (char)eax -> jne 0x2264d3 */
  /* cmp (char)eax, (char)ecx -> jae 0x2264e1 */
  /* cmp (char)eax, (char)ecx -> ja 0x2264dd */
  /* relift: FUN_002260fb(0, 0); */
  /* relift: FUN_0022955c(64); */
  /* test esi, esi -> jne 0x226555 */
  /* relift: FUN_0022955c(128); */
  /* relift: test byte ptr [esi], 0x80 -> je 0x22660b */
  /* test eax, eax -> je 0x22660b */
  /* relift: test byte ptr [esi], 0x40 -> je 0x22661d */
  /* relift: FUN_0022955c(512); */
  /* test (char)edx, 2 -> je 0x226671 */
  /* relift: FUN_00225f13(0, 0); */
  /* test eax, eax -> je 0x226718 */
  /* test edx, edx -> jne 0x2266e5 */
  /* relift: FUN_00225d34(0, 0, 0); */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: FUN_00226412(0); */
  /* relift: FUN_00226771(0); */
  /* test eax, eax -> jne 0x2267f2 */
  /* relift: FUN_00226045(0); */
  /* test edx, edx -> ja 0x226808 */
  XcKeyTable(0, 0);
  XcBlockCryptCBC(0, 0, 0, 0);
  /* relift: cmp dword ptr [eax], 0 -> je 0x2268b8 */
  /* relift: FUN_00225d7d(0, 0, 0, 0); */
  /* relift: FUN_00226361(0); */
  XcModExp(0, 0, 0, 0);
  XcHMAC(0, 16, 0, 17);
  XcHMAC(0, 0, 0, 0);
  XcDESKeyParity(0, 0);
  /* relift: cmp dword ptr [ebp + 0x7c], 0 -> je 0x2269d9 */
  /* relift: FUN_00226302(0); */
  /* cmp ecx, -1 -> je 0x226cb3 */
  /* cmp ebx, 0x14 -> jb 0x226cb3 */
  /* cmp eax, ebx -> ja 0x226cb3 */
  /* relift: cmp word ptr [esi + 2], (int16_t)eax -> je 0x226cb3 */
  /* relift: cmp word ptr [esi], (int16_t)eax -> je 0x226cb3 */
  /* test (int16_t)edx, 0x102 -> jne 0x226c9f */
  /* relift: test byte ptr [edx + 5], 1 -> je 0x226cb3 */
  /* relift: FUN_0022ca10(0, 0, 12, 0); */
  /* relift: FUN_0022ca10(0); */
  /* cmp eax, 0xffff -> jne 0x226cb3 */
  /* relift: FUN_0022c06d(0, 0, 0, socket); */
  /* relift: FUN_00226771(*(int *)((char *)esi + 0x8ac)); */
  /* relift: cmp dword ptr [edi], 0 -> ja 0x226d2d */
  /* relift: FUN_002267c6(0); */
  /* relift: cmp edi, dword ptr [ecx + 0x8a4] -> jne 0x226dbf */
  /* test eax, eax -> je 0x226db7 */
  /* cmp eax, edx -> je 0x226dfc */
  /* relift: cmp ebx, dword ptr [eax + 0x10] -> je 0x226de1 */
  /* cmp eax, edx -> jne 0x226dcf */
  /* relift: FUN_0022644c(0); */
  /* test eax, eax -> jne 0x226e36 */
  /* relift: test byte ptr [ebp + 0x14], 4 -> je 0x226f28 */
  /* relift: FUN_0022644c(0, 0); */
  /* test eax, eax -> je 0x226f28 */
  /* test eax, ecx -> jne 0x226f28 */
  /* cmp eax, edi -> je 0x226ea6 */
  /* relift: cmp dword ptr [eax + 0x14], ebx -> jne 0x226ea0 */
  /* test ebx, ebx -> jne 0x226ef0 */
  /* relift: cmp edx, dword ptr [ebp + 0x10] -> je 0x226ef0 */
  /* relift: FUN_00226013(28, 0x3754454e); */
  /* test eax, eax -> je 0x226f27 */
  /* cmp ebx, esi -> ja 0x226f17 */
  /* relift: cmp (int16_t)edx, word ptr [ecx + 0xe] -> jb 0x226f17 */
  /* cmp ecx, edi -> jne 0x226efc */
  /* cmp eax, ecx -> je 0x226f75 */
  /* relift: cmp edi, dword ptr [esp + 0x14] -> jne 0x226f64 */
  /* relift: cmp edi, dword ptr [esp + 0x18] -> je 0x226f6c */
  /* relift: FUN_00226d51(0); */
  /* relift: FUN_0022644c(0, 0); */
  /* test eax, eax -> je 0x226fea */
  /* relift: FUN_0022644c(0, 0); */
  /* test eax, eax -> je 0x226fea */
  /* cmp ecx, eax -> jne 0x226fea */
  /* relift: FUN_00226d7c(0); */
  /* test eax, eax -> je 0x226fea */
  /* relift: cmp ecx, dword ptr [ebp + 0xc] -> je 0x226fd3 */
  /* relift: FUN_002267c6(0); */
  /* relift: FUN_00226e13(0); */
  XcHMAC(0, 16, 0, 0);
  /* relift: FUN_002262c4(0, 96); */
  XcModExp(0, 0x0022dd48, 0, 0x0022dce8);
  /* relift: FUN_002267f6(0); */
  /* test eax, eax -> je 0x22705e */
  /* cmp (int16_t)ecx, (int16_t)eax -> jne 0x227076 */
  /* test esi, esi -> je 0x227105 */
  /* test ebx, ebx -> je 0x227104 */
  /* test (char)ebx, (char)ebx -> jne 0x227104 */
  /* cmp edx, ecx -> jae 0x227104 */
  /* relift: cmp dword ptr [eax], ebx -> je 0x227104 */
  /* relift: cmp dword ptr [edi], 0 -> je 0x227120 */
  /* relift: FUN_002268c8(0); */
  /* relift: FUN_002270cd(socket, 0, 0); */
  /* relift: cmp byte ptr [edi + 0x14], 3 -> jb 0x2271b7 */
  /* relift: FUN_00226302(0, 0); */
  XcHMAC(0, 0, 0, 0);
  /* relift: FUN_00226829(0, 0); */
  /* relift: FUN_0022cb4c(0, 0); */
  /* test eax, eax -> je 0x22720a */
  /* relift: FUN_0022cb58(0, 0); */
  /* test eax, eax -> je 0x22721a */
  /* relift: FUN_0022cb64(0, 0); */
  /* test eax, eax -> je 0x22722a */
  /* relift: FUN_0022cb71(0, 0); */
  /* test eax, eax -> je 0x22723a */
  /* relift: FUN_00229dea(0, 0); */
  /* test eax, eax -> jl 0x2273b6 */
  /* relift: FUN_0022955c(0x00100000); */
  /* relift: FUN_0022da72(0, 0); */
  /* test eax, eax -> jl 0x2273b6 */
  /* test edx, edx -> je 0x227307 */
  XcHMAC(0, 16, 0, 17);
  XcHMAC(0, 16, 0, 17);
  XcDESKeyParity(0, 0);
  /* relift: FUN_002262c4(0, 0); */
  /* relift: FUN_002262c4(0, 0); */
  /* relift: FUN_0022ca10(0, 0, 0); */
  /* test (char)eax, 3 -> jne 0x227451 */
  /* test (char)eax, 4 -> je 0x2274a3 */
  /* relift: FUN_0022ca10(0); */
  /* relift: FUN_0022ca10(0); */
  /* relift: FUN_0022ca10(0); */
  /* relift: FUN_0022ca10(0); */
  /* relift: cmp eax, dword ptr [ebx + 0x248] -> je 0x227513 */
  /* cmp (char)eax, 0x7f -> je 0x227513 */
  /* cmp eax, -1 -> je 0x227513 */
  /* test esi, esi -> je 0x2274cb */
  /* test eax, eax -> je 0x2274df */
  /* relift: test byte ptr [eax + 0xc], 1 -> je 0x2274fb */
  /* relift: FUN_002267c6(0); */
  /* relift: FUN_00226d7c(0); */
  /* test esi, esi -> je 0x2274ef */
  /* test eax, eax -> jne 0x2274fb */
  /* relift: test byte ptr [eax + 0xc], 8 -> jne 0x227507 */
  /* test esi, esi -> jne 0x227513 */
  /* relift: FUN_002267c6(0); */
  /* relift: FUN_002297b4(0, 0); */
  /* test eax, eax -> je 0x22754b */
  /* cmp eax, esi -> je 0x22754b */
  /* relift: FUN_00226d51(0, 0); */
  /* relift: FUN_002267f6(0); */
  /* relift: cmp dword ptr [edx], 0 -> je 0x2275d5 */
  /* cmp eax, ecx -> jne 0x2275ce */
  /* relift: FUN_00227109(0); */
  /* cmp eax, ebx -> jne 0x2275d5 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x227616 */
  /* relift: FUN_002271bf(socket); */
  /* test edi, edi -> je 0x227621 */
  /* test (char)ebx, (char)ebx -> jne 0x227640 */
  /* relift: FUN_002270cd(0); */
  /* test edi, edi -> je 0x227650 */
  /* test edi, edi -> je 0x22765b */
  /* test edi, edi -> je 0x22766c */
  /* test ecx, ecx -> je 0x227680 */
  /* relift: FUN_0022644c(0, 0); */
  /* test eax, eax -> jne 0x2276be */
  /* test eax, eax -> je 0x2276f6 */
  /* relift: FUN_0022637e(0); */
  /* relift: FUN_00226e13(0, 0, 0, 0); */
  /* relift: FUN_00227525(0, 0); */
  /* relift: FUN_00226302(0, 0, 0, 0); */
  /* relift: test byte ptr [eax + 6], 0x80 -> je 0x2278be */
  /* test ebx, ebx -> jne 0x227882 */
  /* relift: FUN_002262c4(socket, 0); */
  /* relift: FUN_00226829(0, 0, 0, 0); */
  /* test ebx, ebx -> je 0x2278be */
  XcHMAC(0, 16, 0, 0);
  /* relift: FUN_002273bb(0, 0); */
  /* relift: FUN_0022662b(0x7354454e); */
  /* relift: FUN_00226cba(0, 0, 17); */
  /* cmp (char)ecx, 1 -> jne 0x2279b0 */
  /* relift: FUN_002271bf(0); */
  XcHMAC(0, 0, 0, 0);
  /* relift: FUN_002273bb(0, 0); */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: FUN_002262c4(0, 0); */
  /* relift: FUN_002278f6(0); */
  /* relift: FUN_00225d04(0); */
  /* relift: FUN_002268c8(0); */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: FUN_002278f6(0); */
  /* relift: test byte ptr [esi + 2], 0x10 -> je 0x227b41 */
  /* relift: FUN_0022cb7d(0); */
  /* relift: FUN_00227525(0, 0); */
  /* relift: FUN_00226d21(0, 0); */
  /* test eax, eax -> je 0x227b40 */
  /* relift: FUN_0022955c(0x01000000); */
  /* cmp (char)eax, 0x7f -> je 0x227bc9 */
  /* relift: cmp eax, dword ptr [edi + 0x248] -> je 0x227bc9 */
  /* test (char)edx, 1 -> je 0x227bac */
  /* relift: FUN_002270cd(0); */
  /* test eax, eax -> je 0x227bdd */
  /* relift: FUN_00227746(0, 0, 0); */
  /* relift: FUN_00227a6b(0, 0); */
  /* relift: test word ptr [esi + 6], (int16_t)eax -> je 0x227bdd */
  /* relift: FUN_002273bb(0, 0); */
  /* relift: FUN_002297b4(0); */
  /* relift: FUN_00226cba(0, socket, buf, 0); */
  /* relift: FUN_00227b55(0, len); */
  /* relift: cmp dword ptr [ebx], 0 -> je 0x227c46 */
  /* test eax, eax -> jne 0x227c4e */
  /* relift: cmp word ptr [ecx + 0x956], 0 -> jne 0x227c68 */
  /* relift: FUN_00225d20(0, 0); */
  /* relift: FUN_00227b55(0, 0); */
  /* relift: cmp dword ptr [esi], 0 -> jne 0x227cda */
  /* relift: FUN_00225d7d(0, 0, 0, 0); */
  /* relift: FUN_002262c4(0, 0); */
  /* relift: FUN_00227ccd(0); */
  /* relift: cmp dword ptr [ebp + 0x14], 0xa4 -> jne 0x228028 */
  /* test eax, eax -> je 0x228028 */
  /* relift: FUN_002267f6(0); */
  /* test eax, eax -> jne 0x227d95 */
  /* relift: FUN_002270cd(0); */
  /* relift: cmp dword ptr [ebp - 8], edx -> jne 0x227de4 */
  XcHMAC(0, 16, 0, 152);
  /* relift: cmp byte ptr [eax], 0xc -> jne 0x228028 */
  /* relift: cmp byte ptr [ebx + 0x85], 0 -> jne 0x228028 */
  /* relift: cmp dword ptr [ebp - 0x14], edx -> jne 0x227f58 */
  /* relift: FUN_0022687e(0, 0); */
  /* relift: FUN_00227c25(0); */
  /* test ebx, ebx -> je 0x228028 */
  /* relift: cmp ecx, dword ptr [ebx + 0x1c] -> jl 0x228028 */
  /* relift: cmp ecx, dword ptr [ebx + 0x18] -> jbe 0x228028 */
  /* test eax, eax -> jg 0x228028 */
  /* relift: FUN_002268c8(0); */
  /* relift: FUN_002262c4(0, 0); */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: FUN_002268fa(0, 0, 0, 0); */
  /* relift: FUN_002278f6(0); */
  /* relift: cmp byte ptr [eax + 0x14], 2 -> jne 0x228028 */
  /* relift: FUN_00227cf5(0); */
  /* relift: cmp ecx, dword ptr [eax + 0x1c] -> jl 0x228028 */
  /* relift: cmp ecx, dword ptr [eax + 0x18] -> jbe 0x228028 */
  /* cmp (char)ecx, 1 -> je 0x227fb8 */
  /* cmp (char)ecx, 3 -> jne 0x228028 */
  /* relift: cmp byte ptr [eax + 0x14], 1 -> jne 0x228000 */
  /* relift: FUN_002262c4(0); */
  /* relift: FUN_002268fa(0, 0); */
  /* relift: FUN_00225d7d(0); */
  /* relift: FUN_00227ccd(0, 0); */
  /* relift: FUN_0022687e(0, socket); */
  /* test eax, eax -> jne 0x2280a0 */
  /* relift: FUN_002267f6(socket); */
  /* test eax, eax -> jne 0x22808a */
  /* relift: FUN_00227c25(0, 0); */
  /* test eax, eax -> jne 0x2280a0 */
  /* cmp ecx, eax -> je 0x2280e5 */
  /* cmp ecx, -1 -> jne 0x22839d */
  /* relift: cmp word ptr [edi], 0x20c -> jne 0x22839a */
  /* cmp ecx, 0x10 -> jb 0x22839a */
  /* relift: FUN_00227d26(0, 0, 0, 0); */
  /* test (char)ecx, 3 -> jne 0x22839a */
  /* relift: cmp dword ptr [ebp + 0x14], 0x20 -> jb 0x22839a */
  /* relift: cmp dword ptr [ebp - 8], edi -> je 0x2281e6 */
  /* relift: FUN_002270cd(0); */
  /* relift: cmp byte ptr [eax + 0x14], 2 -> jb 0x22839a */
  /* cmp esi, 0x20 -> jae 0x22824a */
  /* relift: test dword ptr [ecx + 0xc], eax -> jne 0x22839a */
  XcHMAC(0, 16, 0, 0);
  /* relift: cmp dword ptr [ebp - 0x18], edi -> je 0x2282b2 */
  /* cmp ecx, eax -> jne 0x22839a */
  /* relift: FUN_00226829(0, 0, 0, 0); */
  /* cmp (char)eax, 0x11 -> je 0x2282c5 */
  /* cmp (char)eax, 6 -> jne 0x22839a */
  /* relift: cmp dword ptr [ebp + 0x14], ecx -> jb 0x22839a */
  /* test (char)eax, (char)eax -> jbe 0x2282f2 */
  /* relift: cmp byte ptr [esi], (char)eax -> jne 0x2282e7 */
  /* cmp eax, edi -> jne 0x22839a */
  /* relift: cmp dword ptr [ebp - 8], edi -> jne 0x22835a */
  /* cmp eax, 0x20 -> jae 0x22830e */
  /* cmp eax, 0x3f -> jb 0x22831f */
  /* relift: cmp byte ptr [eax + 0x14], 4 -> je 0x22835d */
  /* relift: FUN_00227cf5(0); */
  /* relift: FUN_002283a1(0, 0); */
  /* relift: FUN_00226bfc(0, 0); */
  /* cmp ecx, edi -> jne 0x228490 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x228490 */
  /* relift: cmp word ptr [esi], 0 -> je 0x228490 */
  /* cmp (int16_t)eax, 0x20c -> jne 0x228415 */
  /* relift: FUN_002280bb(0, 0, 0, 0); */
  /* cmp eax, 0x1000000 -> je 0x228490 */
  /* test (char)ecx, 2 -> jne 0x22847f */
  /* relift: cmp word ptr [esi + 6], 0 -> je 0x22845c */
  /* relift: FUN_0022ca10(0, 0, 12, 0); */
  /* relift: FUN_0022ca10(0); */
  /* cmp eax, 0xffff -> jne 0x228490 */
  /* relift: cmp word ptr [esi + 2], 0x4400 -> jne 0x228476 */
  /* relift: FUN_0022d797(0, 0, 0); */
  /* relift: test byte ptr [eax + 5], 1 -> je 0x228490 */
  /* relift: FUN_0022c925(0, 0, 0, 0); */
  /* cmp (char)ecx, 0x40 -> jne 0x228630 */
  /* cmp eax, ebx -> ja 0x228630 */
  /* cmp ebx, ecx -> ja 0x228630 */
  /* relift: FUN_0022ca10(0, 0, 0); */
  /* cmp eax, 0xffff -> jne 0x228630 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x228630 */
  /* relift: cmp word ptr [ebp - 8], 0 -> je 0x22855d */
  /* relift: cmp dword ptr [ebp + 8], -1 -> jne 0x228630 */
  /* test edx, edx -> je 0x228630 */
  /* cmp edx, -1 -> je 0x228630 */
  /* test (char)eax, 2 -> jne 0x2285ba */
  /* relift: cmp byte ptr [ebp + 8], 0x7f -> je 0x228630 */
  /* cmp dl, 0x7f -> je 0x228630 */
  /* cmp edx, ecx -> je 0x228630 */
  /* relift: cmp word ptr [ebp - 8], 0 -> jne 0x2285ba */
  /* relift: cmp dword ptr [ebp + 8], -1 -> je 0x2285ba */
  /* relift: cmp ecx, dword ptr [ebp + 8] -> je 0x2285ba */
  /* relift: cmp dword ptr [ebp + 8], 0x1000000 -> jne 0x228630 */
  /* relift: cmp byte ptr [esi + 9], 0x11 -> jne 0x228630 */
  /* relift: test word ptr [esi + 6], 0xff3f -> je 0x2285d6 */
  /* test (char)eax, 3 -> jne 0x228630 */
  /* relift: FUN_00228637(0, 0, 0, 0); */
  /* cmp dl, 0x11 -> jne 0x228600 */
  /* relift: FUN_002283a1(0); */
  /* cmp dl, 6 -> jne 0x22861f */
  /* relift: FUN_00226bfc(0); */
  /* cmp dl, 1 -> jne 0x228630 */
  /* relift: FUN_0022db9d(0, 0, 0, 0); */
  /* relift: cmp dword ptr [ebx + 0x28], eax -> jne 0x2286a3 */
  /* relift: cmp edx, dword ptr [edi + 0xc] -> jne 0x2286a3 */
  /* relift: cmp edx, dword ptr [edi + 0x10] -> je 0x2286aa */
  /* test ebx, ebx -> jne 0x22868e */
  /* test ebx, ebx -> jne 0x22877b */
  /* relift: cmp dword ptr [esi + 0x8b4], eax -> jae 0x2288ee */
  /* relift: FUN_0022662b(0x6d54454e, 1600, 0, 0); */
  /* cmp ebx, eax -> je 0x2288ee */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: FUN_00225d04(0); */
  /* test eax, eax -> jbe 0x228796 */
  /* cmp eax, edx -> jne 0x2288e6 */
  /* cmp edx, ecx -> ja 0x2288e6 */
  /* relift: cmp dword ptr [ebp - 0x14], 0 -> je 0x2287fc */
  /* test ecx, ecx -> jne 0x228817 */
  /* relift: cmp dword ptr [ebx + 0x3c], eax -> jae 0x2288e6 */
  /* relift: cmp ecx, dword ptr [ebp - 0xc] -> jne 0x2288e6 */
  /* test ecx, ecx -> je 0x22884f */
  /* cmp eax, ecx -> ja 0x2288e3 */
  /* relift: cmp dword ptr [ebx + 0x3c], eax -> jae 0x228857 */
  /* relift: cmp dword ptr [ebp - 8], eax -> jae 0x228886 */
  /* relift: cmp dword ptr [ebp + 0xc], eax -> jb 0x22885c */
  /* cmp ecx, edx -> je 0x2288ee */
  /* cmp eax, edx -> je 0x2288ee */
  /* relift: cmp edi, dword ptr [ebx + 0x38] -> jne 0x2288ee */
  /* relift: FUN_0022ca10(0, 0, *(int *)((char *)ebx + 0x2c)); */
  /* relift: FUN_00228497(0); */
  /* relift: FUN_00226771(0); */
  /* mem[0xfef00110] = eax */
  /* mem[0xfef00084] = eax */
  /* mem[0xfef00094] = eax */
  /* mem[0xfef00144] = 3 */
  /* mem[0xfef00110] = 0 */
  /* mem[0xfef00094] = 0 */
  /* mem[0xfef00084] = 0 */
  /* relift: test byte ptr [0xfef00098], 1 -> jne 0x22895e */
  /* relift: test byte ptr [0xfef00088], 1 -> je 0x228966 */
  /* test ebx, ebx -> jne 0x22894b */
  /* mem[0xfef00144] = 4 */
  /* relift: test byte ptr [0xfef00144], 8 -> jne 0x228982 */
  /* test edi, edi -> jne 0x228970 */
  /* mem[0xfef00144] = 0 */
  /* mem[0xfef00004] = eax */
  /* relift: cmp ebx, dword ptr [esi + 0x1f0] -> je 0x228a29 */
  /* relift: FUN_0022891d(0, 0); */
  /* test edi, edi -> jne 0x228a12 */
  /* relift: FUN_002288f5(0, 0); */
  /* test (char)ebx, 1 -> je 0x228a23 */
  /* relift: FUN_0022955c(0x80000000); */
  /* test eax, eax -> je 0x228a40 */
  /* test eax, eax -> jne 0x228a61 */
  /* relift: FUN_002263ec(0); */
  /* test ecx, ecx -> je 0x228a89 */
  /* relift: FUN_0022955c(4096); */
  /* test ecx, ecx -> je 0x228ab8 */
  /* relift: cmp dword ptr [ecx], -1 -> jne 0x228b04 */
  /* relift: cmp word ptr [ecx + 4], 0xffff -> jne 0x228b04 */
  /* relift: cmp dword ptr [ecx + 0xe], 0x3aaaa -> jne 0x228b19 */
  /* relift: cmp word ptr [ecx + 0x12], (int16_t)eax -> jne 0x228b19 */
  /* relift: cmp eax, dword ptr [ecx + 0x208] -> jne 0x228b3b */
  /* relift: cmp eax, dword ptr [ecx + 0x224] -> jne 0x228b55 */
  /* relift: FUN_00228990(0, 0); */
  /* test ecx, 0x10000 -> je 0x228cbb */
  /* test ecx, 0x40000000 -> je 0x228be4 */
  /* cmp edx, 0x20000000 -> jne 0x228cbb */
  /* relift: test byte ptr [esi + 1], 0x10 -> je 0x228cbb */
  /* test edx, edx -> jbe 0x228c1e */
  /* cmp edx, 0x2a -> jb 0x228cb5 */
  /* cmp (int16_t)ecx, 0x5dc -> ja 0x228c5e */
  /* relift: cmp word ptr [eax + 0x12], 0 -> jne 0x228cb5 */
  /* relift: cmp dword ptr [esi], -1 -> jne 0x228c78 */
  /* relift: cmp word ptr [esi + 4], 0xffff -> jne 0x228c78 */
  /* relift: FUN_00229cc0(0, 0); */
  /* relift: cmp eax, dword ptr [esi + 0x224] -> jne 0x228cd2 */
  /* test esi, esi -> je 0x228d86 */
  /* relift: cmp ebx, dword ptr [edi + 0x208] -> jne 0x228d21 */
  /* relift: test byte ptr [ebx + 7], 0x80 -> jne 0x228d86 */
  /* relift: FUN_00225d20(0, 0); */
  /* relift: cmp ebx, dword ptr [edi + 0x208] -> jne 0x228d41 */
  /* relift: cmp dword ptr [eax], 0 -> je 0x228dad */
  /* relift: cmp ecx, dword ptr [edi + 0x200] -> jge 0x228dad */
  /* test ecx, ecx -> je 0x228de1 */
  /* relift: FUN_00225d04(0, 0); */
  /* relift: cmp ebx, dword ptr [edi + 0x208] -> jne 0x228e9c */
  /* mem[0xfef00144] = 1 */
  /* test (char)ecx, 4 -> je 0x228f1d */
  /* test eax, ecx -> jne 0x228f1d */
  /* relift: FUN_0022955c(0); */
  /* relift: test byte ptr [esi + 1], 8 -> je 0x228eec */
  /* test ecx, ecx -> je 0x228efc */
  /* relift: cmp byte ptr [0x4ee4d0], 0 -> je 0x228f10 */
  /* relift: FUN_00228ebc(0); */
  /* relift: FUN_0022955c(16384); */
  /* relift: test byte ptr [ebx + 1], 4 -> je 0x228f85 */
  /* relift: cmp dword ptr [edi], 0 -> je 0x228f73 */
  /* relift: FUN_00225d20(0); */
  /* relift: FUN_00226412(0); */
  /* relift: cmp dword ptr [edi], 0 -> jne 0x228f46 */
  /* relift: FUN_00228ebc(0, 0); */
  /* relift: FUN_00229cc0(0, 0); */
  /* relift: FUN_002289a9(0, 0); */
  /* mem[0xfef00180] = esi */
  /* test (char)ebx, 4 -> je 0x229044 */
  /* mem[0xfef00144] = 2 */
  /* relift: FUN_00228b9a(0, 0); */
  /* relift: FUN_00228cee(0, 0); */
  /* mem[0xfef00004] = 0x5f */
  /* mem[0xfef00144] = 1 */
  /* relift: FUN_00229007(0, 0); */
  /* relift: FUN_00226475(0, 0); */
  /* cmp eax, edi -> jl 0x2294fd */
  /* relift: cmp dword ptr [ecx], edi -> je 0x229115 */
  /* relift: cmp dword ptr [edx + 4], 0x58424436 -> je 0x2290ce */
  /* cmp eax, edi -> jl 0x2294fb */
  /* relift: FUN_0022955c(1024); */
  /* relift: cmp dword ptr [ebp - 0x10], edi -> je 0x2294f9 */
  /* relift: FUN_0022955c(1024); */
  /* relift: FUN_0022891d(0, 0); */
  /* mem[0xfef00144] = 0x10 */
  /* mem[0xfef00144] = edi */
  /* mem[0xfef00184] = edi */
  /* mem[0xfef00004] = edi */
  /* mem[0xfef00200] = edi */
  /* mem[0xfef00008] = edi */
  /* mem[0xfef0010c] = edi */
  /* mem[0xfef00110] = edi */
  /* relift: cmp dword ptr [eax], ecx -> jbe 0x229206 */
  /* relift: cmp dword ptr [eax], ecx -> jbe 0x22921f */
  /* cmp esi, edi -> jne 0x22924a */
  /* relift: cmp eax, dword ptr [ecx + 0x224] -> jbe 0x2292de */
  FUN_001d4464();
  /* test eax, eax -> jne 0x22931f */
  /* relift: cmp dword ptr [ebp - 0xc], 6 -> je 0x22934f */
  /* relift: FUN_002262c4(0, 0); */
  /* mem[0xfef000a8] = eax */
  /* mem[0xfef000ac] = eax */
  /* mem[0xfef000b8] = 0xffffffff */
  /* mem[0xfef000bc] = eax */
  /* mem[0xfef000b0] = 0xffffffff */
  /* mem[0xfef000b4] = eax */
  /* mem[0xfef00090] = 0x5ee */
  /* mem[0xfef0008c] = 0x7f0020 */
  /* mem[0xfef00080] = 0x3b0f3e */
  /* relift: FUN_002262c4(0, 0); */
  /* mem[0xfef0009c] = eax */
  /* mem[0xfef000a0] = 0x16070f */
  /* mem[0xfef000a4] = 0x16 */
  /* mem[0xfef00100] = ecx */
  /* mem[0xfef00104] = ecx */
  /* mem[0xfef00108] = ecx */
  /* mem[0xfef00140] = eax */
  /* mem[0xfef0013c] = eax */
  /* mem[0xfef00188] = 0x1040000 */
  /* mem[0xfef0018c] = 0x105 */
  /* cmp eax, esi -> jl 0x2294fb */
  /* relift: FUN_002289a9(0, 0); */
  /* relift: FUN_002288f5(0, 0); */
  /* mem[0xfef00184] = edi */
  /* mem[0xfef00004] = 0x5f */
  /* test (char)eax, (char)eax -> jne 0x2294ce */
  /* relift: FUN_0022955c(2048); */
  /* relift: cmp dword ptr [eax + 4], edx -> jb 0x22953e */
  /* cmp eax, esi -> jne 0x229566 */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  FUN_001d0581();
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x22966d */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  xbox_query_global_memory_status((void *)(uintptr_t)eax);
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  FUN_001d3739();
  /* test eax, eax -> je 0x2296f8 */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  ExQueryNonVolatileSetting(65535, 0, 0, 256);
  /* test eax, eax -> jl 0x22972c */
  /* relift: FUN_00229512(0, socket); */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00229512(0, 0); */
  /* relift: FUN_00225cef(0, 0); */
  /* relift: FUN_00225d04(0, 0); */
  /* relift: FUN_0022975e(0, 0); */
  /* test ecx, eax -> jne 0x22980e */
  /* relift: FUN_0022955c(0); */
  /* relift: FUN_0022662b(0x6a54454e, 7744, 28, 0); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)lift_a28;
  (void)lift_a5;
}

/* 0x0024b4e4 */
void MU_Init(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* mem[0x004eb0c0] = eax */
  /* mem[0x004eb0bc] = eax */
  /* mem[0x004ee0c4] = edi */
  /* relift: FUN_0024b75b(0, 0); */
  /* test eax, eax -> je 0x24b535 */
  IUsbInit_GetMaxDeviceTypeCount();
  /* relift: cmp dword ptr [ebp - 8], esi -> jbe 0x24b5d5 */
  /* test eax, eax -> jl 0x24b5d5 */
  /* relift: FUN_0024c4d3(0); */
  /* relift: cmp esi, dword ptr [ebp - 8] -> jb 0x24b565 */
  /* relift: relift: mov byte ptr [0x24b241], (char)eax */
  /* relift: FUN_0024b76e(0x0024b240); */
  /* relift: cmp dword ptr [0x24b308], 0 -> jne 0x24b721 */
  /* mem[0x0024b308] = 1 */
  /* relift: relift: mov word ptr [0x4ee0c8], 4 */
  /* relift: FUN_0024b75b(0, 0); */
  /* test eax, eax -> jne 0x24b66c */
  IUsbInit_GetMaxDeviceTypeCount();
  /* relift: relift: mov byte ptr [0x24b368], (char)eax */
  IUsbInit_GetMaxDeviceTypeCount();
  /* relift: relift: mov byte ptr [0x24b380], (char)eax */
  IUsbInit_GetMaxDeviceTypeCount();
  /* relift: relift: mov byte ptr [0x24b398], (char)eax */
  /* cmp ebx, eax -> jbe 0x24b692 */
  /* mem[0x004ee0d0] = ecx */
  /* mem[0x004ee0d0] = ecx */
  /* mem[0x004ee0cc] = eax */
  /* cmp edx, eax -> jb 0x24b6e5 */
  /* relift: relift: mov byte ptr [0x24b2fd], (char)ebx */
  /* relift: FUN_0024b76e(0x0024b2fc); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0024b724 */
void IUsbInit_GetMaxDeviceTypeCount(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edx, edx -> je 0x24b752 */
  /* relift: cmp edi, dword ptr [esp + 0xc] -> je 0x24b755 */
  /* cmp eax, ecx -> jb 0x24b73e */
  /* relift: cmp (char)eax, byte ptr [ecx] -> jbe 0x24b76d */
  /* cmp (char)eax, 4 -> jbe 0x24b7d5 */
  /* relift: FUN_0024b76e(0); */
  /* relift: cmp (char)eax, byte ptr [ebx + 2] -> jbe 0x24b7e0 */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b837 */
  /* relift: cmp (char)eax, byte ptr [esi + 3] -> jbe 0x24b806 */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b823 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x24b7f1 */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b88e */
  /* relift: cmp (char)eax, byte ptr [esi + 4] -> jbe 0x24b85d */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b87a */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x24b848 */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b8e5 */
  /* relift: cmp (char)eax, byte ptr [esi + 5] -> jbe 0x24b8b4 */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b8d1 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x24b89f */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b93c */
  /* relift: cmp (char)eax, byte ptr [esi + 8] -> jbe 0x24b90b */
  /* relift: cmp dword ptr [ebp + 8], 4 -> jae 0x24b928 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x24b8f6 */
  /* relift: cmp (char)eax, byte ptr [ecx] -> jbe 0x24b94b */
  /* relift: cmp (char)eax, byte ptr [ecx] -> jbe 0x24b95a */
  /* relift: cmp (char)eax, byte ptr [ecx + 0xa1] -> jbe 0x24b9b7 */
  /* relift: cmp (char)eax, byte ptr [ecx + 0xa1] -> jbe 0x24b9c8 */
  /* relift: cmp byte ptr [ecx + 0xb0], 0xd -> jae 0x24ba65 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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

/* 0x0024bb54 */
void XInitDevices(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> je 0x24bb79 */
  /* relift: FUN_0024fe14(0, 0); */
  /* test eax, eax -> je 0x24bb95 */
  /* cmp ebx, edi -> jb 0x24bb8b */
  /* relift: FUN_0024b970(0, 0); */
  /* relift: FUN_0024bc5b(0); */
  /* relift: FUN_0024bab5(0); */
  /* relift: FUN_0024bc67(0, 0); */
  /* test esi, esi -> je 0x24bc56 */
  /* relift: FUN_0024e953(0, 0); */
  /* relift: FUN_0024bcb5(0, 0); */
  /* relift: FUN_0024beb0(0, 0); */
  /* relift: cmp byte ptr [eax + 5], 0xa1 -> je 0x24bca7 */
  /* relift: FUN_0024bbe2(0, 1232); */
  /* relift: FUN_0024c0d6(0, 0, 0); */
  /* relift: FUN_0024c0e1(0); */
  /* relift: FUN_0024c075(0, 0); */
  /* relift: FUN_0024be00(0, 0); */
  /* relift: relift: mov word ptr [0x4ee318], 6 */
  /* relift: test byte ptr [ebp - 8], 1 -> je 0x24be6f */
  /* cmp edx, edi -> jb 0x24be5c */
  /* relift: FUN_0025110a(0, 0); */
  /* cmp ecx, edx -> jae 0x24bf04 */
  /* mem[0x00632900] = ecx */
  /* mem[0x00632904] = esi */
  /* mem[0x00632908] = edx */
  /* mem[0x0063292c] = edi */
  /* mem[0x00632928] = edx */
  /* mem[0x00632928] = esi */
  /* mem[0x00632908] = esi */
  /* relift: cmp eax, dword ptr [ebx + 4] -> jb 0x24bf78 */
  /* mem[0x00632908] = esi */
  /* relift: cmp eax, dword ptr [ebx] -> jb 0x24bfa3 */
  /* mem[0x0063290c] = edx */
  /* mem[0x00632910] = esi */
  /* relift: FUN_002512ed(0); */
  /* relift: cmp edi, dword ptr [ebp - 0xc] -> jbe 0x24bfd0 */
  /* mem[0x00632914] = eax */
  /* mem[0x00632918] = edx */
  /* mem[0x0063291c] = 0x3e8 */
  /* relift: relift: mov word ptr [0x632920], (int16_t)eax */
  /* relift: relift: mov word ptr [0x632924], (int16_t)eax */
  /* cmp (int16_t)eax, (int16_t)edx -> je 0x24c046 */
  /* relift: relift: mov word ptr [0x632924], (int16_t)eax */
  /* relift: relift: mov (int16_t)eax, word ptr [0x632924] */
  /* relift: relift: mov (int16_t)ecx, word ptr [0x632920] */
  /* relift: relift: mov word ptr [0x632922], (int16_t)ecx */
  /* relift: relift: mov word ptr [0x632926], (int16_t)eax */
  /* relift: FUN_0024fead(0, 0, 0); */
  /* test esi, ecx -> je 0x24c10a */
  /* relift: test dword ptr [edx + 4], esi -> jne 0x24c103 */
  /* cmp edx, 2 -> je 0x24c13e */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0024c143 */
void XInputOpen(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 8], 0x24b29c -> jne 0x24c158 */
  /* relift: cmp dword ptr [ebp + 8], 0x24b2a8 -> jne 0x24c165 */
  /* relift: cmp dword ptr [ebp + 8], 0x24b2b4 -> jne 0x24c1ab */
  /* test eax, eax -> jne 0x24c184 */
  /* relift: FUN_0024d291(0, 0); */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x24c1a6 */
  SetLastError(eax);
  SetLastError(87);

  (void)eax;
  (void)ebp;
}

/* 0x0024c1b8 */
void XInputClose(void)
{
  XID_fCloseDevice();
}

/* 0x0024c1c4 */
void XInputGetCapabilities(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp esi, ebx -> je 0x24c395 */
  /* relift: test byte ptr [esi + 4], 2 -> jne 0x24c395 */
  /* relift: test byte ptr [eax + 0x24b37c], 1 -> je 0x24c223 */
  /* relift: FUN_0024dc24(0); */
  /* relift: cmp dword ptr [eax], ebx -> je 0x24c395 */
  /* relift: test byte ptr [esi + 4], 2 -> jne 0x24c395 */
  /* relift: cmp dword ptr [ebp - 0x44], ebx -> jl 0x24c388 */
  /* relift: FUN_0024dc24(0); */
  /* relift: cmp dword ptr [eax], ebx -> je 0x24c395 */
  /* relift: test byte ptr [esi + 4], 2 -> jne 0x24c395 */
  /* relift: cmp dword ptr [ebp - 0x44], ebx -> jge 0x24c39c */
  /* relift: FUN_0024d81f(0); */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0x0024c3b6 */
void XInputGetState(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* relift: cmp byte ptr [edx + 0xa3], 1 -> jne 0x24c3d2 */
  /* test ecx, ecx -> je 0x24c3de */
  /* relift: test byte ptr [ecx + 4], 2 -> je 0x24c3e3 */
  /* relift: cmp byte ptr [eax], 1 -> jne 0x24c43b */
  /* relift: FUN_0024d0ae(0, 0); */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x0024c45f */
void XInputPoll(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp ecx, esi -> je 0x24c4a4 */
  /* relift: test byte ptr [ecx + 4], 2 -> jne 0x24c4a4 */
  /* relift: test byte ptr [eax + 0xa2], 8 -> jne 0x24c4a9 */
  /* relift: cmp dword ptr [eax + 4], esi -> jne 0x24c4a9 */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> je 0x24c4d2 */
  /* mem[0x004eb0b8] = ecx */
  /* mem[0x004eb0b8] = edx */
  /* relift: FUN_0024d981(0, 0, 0); */
  /* cmp eax, 0x10 -> jb 0x24c516 */
  /* relift: FUN_0024d90b(0, 0, 0); */
  /* cmp eax, ebx -> je 0x24c57f */
  /* relift: FUN_0024d90b(0, 0, 0); */
  /* cmp eax, ebx -> je 0x24c57f */
  /* relift: FUN_0024d7ec(0); */
  /* relift: FUN_0024d811(0, 0); */
  /* relift: FUN_0024d815(0); */
  /* relift: FUN_0024eff0(0x80000400); */
  /* test eax, 0x20000 -> je 0x24c5e1 */
  /* test eax, 0x10000 -> je 0x24c61a */
  /* relift: FUN_0024dc24(0); */
  /* relift: test byte ptr [esi + 0xc], 2 -> je 0x24c65d */
  /* relift: FUN_0024ec32(0, 0); */
  /* test edx, eax -> jne 0x24c67c */
  /* relift: FUN_0024c591(0); */
  /* relift: FUN_0024d7e8(0); */
  /* test ecx, ecx -> je 0x24c6a4 */
  /* test (char)eax, 4 -> jne 0x24c6a4 */
  /* relift: FUN_0024c663(0, 0); */
  /* relift: FUN_0024ec32(0, 0); */
  /* relift: FUN_0024c663(0, 0); */
  /* relift: FUN_0024c4d3(0); */
  /* relift: FUN_0024c4b8(0, 0); */
  /* cmp esi, ebx -> jne 0x24c75c */
  /* relift: FUN_0024c4d3(0, 0); */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> jl 0x24c881 */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> jl 0x24c881 */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> jl 0x24c881 */
  /* relift: FUN_0024d88d(0); */
  /* cmp ecx, eax -> jne 0x24c8ae */
  /* relift: FUN_0024c6b2(0, 0); */
  crt_sprintf((char *)0, (char *)0x00253034);
  /* mem[0x0024b25c] = eax */
  /* mem[0x0024b260] = eax */
  /* mem[0x0024b26c] = eax */
  /* mem[0x0024b270] = eax */
  /* mem[0x0024b274] = eax */
  /* mem[0x0024b278] = eax */
  /* mem[0x0024b27c] = eax */
  /* mem[0x0024b280] = eax */
  /* mem[0x0024b28c] = eax */
  /* mem[0x0024b290] = eax */
  /* relift: cmp byte ptr [esp + 0xc], 0 -> je 0x24c926 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x0024c932 */
void XGetDevices(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x0024c954 */
void XGetDeviceChanges(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [esi + 4], eax -> jne 0x24c96e */
  /* mem[0x004ee0d0] = ecx */
  /* mem[0x004ee0d0] = eax */
  /* relift: FUN_0024d7d5(0x004ee0e8); */
  /* relift: FUN_0024d7ec(0, 0); */
  /* relift: FUN_0024ec32(0, 0); */
  /* relift: test byte ptr [eax + 4], 1 -> je 0x24ca9d */
  /* relift: FUN_0024d981(0, 0); */
  /* cmp eax, ebp -> jne 0x24ca9d */
  /* relift: cmp byte ptr [eax + 0xa], (char)ecx -> jne 0x24ca9d */
  /* test (char)ecx, 8 -> je 0x24ca9d */
  /* test (char)ecx, 2 -> jne 0x24ca9d */
  /* relift: cmp (int16_t)eax, word ptr [0x4ee0c8] -> jb 0x24ca5e */
  /* relift: FUN_0024dc24(0, 0); */
  /* test eax, eax -> jl 0x24cb5a */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> jl 0x24cb5a */
  /* relift: test byte ptr [ecx], 2 -> je 0x24cb5a */
  /* relift: cmp byte ptr [edi + 9], 0 -> je 0x24cb5a */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> jl 0x24cb5a */
  /* relift: cmp dword ptr [esi + 0xc], edi -> je 0x24cbb7 */
  /* relift: cmp dword ptr [esi + 0x10], edi -> je 0x24cbe2 */
  /* relift: FUN_0024dc24(0); */
  /* relift: test byte ptr [eax + 4], 2 -> je 0x24cbf4 */
  /* relift: FUN_0024ca23(0, 0); */
  /* relift: test byte ptr [esi + 0xa2], 1 -> je 0x24cc0b */
  /* relift: test byte ptr [ebx + 4], 2 -> jne 0x24cca8 */
  /* relift: cmp dword ptr [esi + 4], eax -> jl 0x24cc60 */
  /* relift: test byte ptr [edi + 0xa2], 8 -> je 0x24cca7 */
  /* relift: FUN_0024dc24(0); */
  /* relift: test byte ptr [ebx + 4], 2 -> jne 0x24cd32 */
  /* relift: test byte ptr [esi + 0xa2], 1 -> jne 0x24cd32 */
  /* relift: cmp dword ptr [edi + 4], 0 -> jl 0x24cd2a */
  /* relift: FUN_0024dc24(0); */
  /* relift: FUN_0024dc24(0); */
  /* relift: FUN_0024ee12(0, 0); */
  /* relift: cmp byte ptr [edx + eax + 2], 0 -> jne 0x24cd73 */
  /* cmp eax, 7 -> jle 0x24cd65 */
  /* test edx, edx -> je 0x24cdbe */
  /* relift: FUN_0024d81f(0, 0, 0); */
  /* relift: test byte ptr [ecx + 4], 2 -> jne 0x24ce39 */
  /* relift: cmp dword ptr [esi + 4], 0 -> jl 0x24ce30 */
  /* relift: FUN_0024dc24(0); */
  /* relift: FUN_0024cdbf(0, 0); */
  /* relift: FUN_0024d815(0); */
  /* relift: FUN_0024eff0(0); */
  /* test (char)eax, 4 -> jne 0x24ceba */
  /* relift: FUN_0024cb5f(0); */
  /* relift: test byte ptr [eax + 4], 2 -> je 0x24cede */
  /* relift: cmp dword ptr [ecx + 4], 0xc0000004 -> jne 0x24cf37 */
  /* relift: cmp byte ptr [ecx + 1], 0x41 -> jne 0x24cf37 */
  /* relift: FUN_0024dc24(0); */
  /* relift: FUN_0024cdbf(0, 0); */
  /* relift: relift: mov byte ptr [0x4ee0e8], 0x30 */
  /* relift: relift: mov byte ptr [0x4ee0e9], 0x40 */
  /* mem[0x004ee0f0] = 0x24ce63 */
  /* mem[0x004ee0f4] = esi */
  /* mem[0x004ee0f8] = eax */
  /* mem[0x004ee100] = eax */
  /* mem[0x004ee0fc] = eax */
  /* relift: relift: mov byte ptr [0x4ee104], (char)eax */
  /* relift: relift: mov byte ptr [0x4ee105], 1 */
  /* relift: relift: mov byte ptr [0x4ee106], (char)eax */
  /* relift: relift: mov byte ptr [0x4ee110], 0x21 */
  /* relift: relift: mov byte ptr [0x4ee111], 0xa */
  /* relift: relift: mov word ptr [0x4ee112], (int16_t)eax */
  /* relift: relift: mov word ptr [0x4ee114], (int16_t)ecx */
  /* relift: relift: mov word ptr [0x4ee116], (int16_t)eax */
  /* relift: FUN_0024c9eb(0, 0); */
  /* relift: FUN_0024dc24(0x004ee0e8); */
  /* relift: FUN_0024d7e8(0); */
  /* test ecx, ecx -> je 0x24cffe */
  /* relift: cmp byte ptr [esi + 0xa], 1 -> jne 0x24cff4 */
  /* test eax, eax -> je 0x24cff4 */
  /* relift: FUN_0024ce9d(0, 0); */
  /* relift: FUN_0024ca23(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x0024d009 */
void XID_fCloseDevice(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp byte ptr [esi + 0xa3], 1 -> jne 0x24d03a */
  /* cmp eax, ebx -> je 0x24d03a */
  /* relift: FUN_0024ce9d(0, 0); */
  /* mem[0x004ee0d0] = esi */
  /* relift: test byte ptr [edi + 4], 2 -> jne 0x24d1c4 */
  /* relift: cmp byte ptr [edi + 0xd], 0 -> jne 0x24d0e7 */
  /* test eax, eax -> je 0x24d107 */
  /* test eax, eax -> jge 0x24d10b */
  /* relift: cmp (char)eax, byte ptr [esi + 0x41] -> jae 0x24d116 */
  /* relift: FUN_0024dc24(0); */
  /* relift: FUN_0024d81f(0); */
  /* relift: cmp word ptr [0x4ee0de], 0x1d -> jne 0x24d269 */
  /* relift: FUN_0024d905(0, 0); */
  /* relift: cmp byte ptr [eax + 5], 3 -> jne 0x24d269 */
  /* relift: cmp byte ptr [eax + 7], 1 -> jne 0x24d269 */
  /* relift: FUN_0024c9eb(0, 0); */
  /* relift: FUN_0024dc24(0x004ee0e8); */
  /* relift: FUN_0024d7ec(0); */
  /* relift: FUN_0024eff0(0x80000400); */
  /* relift: FUN_0024ca46(0, 0); */
  /* relift: cmp dword ptr [esi + 0xe], edi -> je 0x24d2e4 */
  /* test (char)eax, (char)eax -> jne 0x24d304 */
  /* mem[0x004ee0d0] = eax */
  /* relift: FUN_0024cab4(0, 0); */
  /* test eax, eax -> jl 0x24d4b5 */
  /* relift: FUN_0024dc24(0); */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}
