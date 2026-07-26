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


/* 0x001e8b10 */
void D3DDevice_FlushVertexCache(void)
{
  XMETAL_StartPush();
}

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

/* 0x001eeac0 */
void D3D_GetAdapterIdentifier(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

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


/* 0x001eecf0 */
void D3D_GetDeviceCaps(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x1eed00 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eed0f */
  D3DDevice_GetDeviceCaps((void *)(uintptr_t)eax);

  (void)eax;
}

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

