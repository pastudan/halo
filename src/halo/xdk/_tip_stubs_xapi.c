/* Tip-only compile unit for XDK IAT-thunk Unicorn proofs. */
void NtYieldExecution(void)
{
  ((void (*)(void))*(void **)0x2530c8)();
}

void MmFreeSystemMemory(void)
{
  ((void (*)(void))*(void **)0x2531a4)();
}

void KeQueryPerformanceCounter(void)
{
  ((void (*)(void))*(void **)0x253204)();
}

void KeQueryPerformanceFrequency(void)
{
  ((void (*)(void))*(void **)0x253208)();
}

void MmAllocateContiguousMemoryEx(void)
{
  ((void (*)(void))*(void **)0x25320c)();
}

void MmSetAddressProtect(void)
{
  ((void (*)(void))*(void **)0x253214)();
}

void NtDuplicateObject(void)
{
  ((void (*)(void))*(void **)0x253094)();
}

void RtlLeaveCriticalSection(void)
{
  ((void (*)(void))*(void **)0x253098)();
}

void RtlEnterCriticalSection(void)
{
  ((void (*)(void))*(void **)0x25309c)();
}

void ObfDereferenceObject(void)
{
  ((void (*)(void))*(void **)0x2530a0)();
}

void KeSetBasePriorityThread(void)
{
  ((void (*)(void))*(void **)0x2530a4)();
}

void ObReferenceObjectByHandle(void)
{
  ((void (*)(void))*(void **)0x2530a8)();
}

void KeQueryBasePriorityThread(void)
{
  ((void (*)(void))*(void **)0x2530b0)();
}

void KeSetDisableBoostThread(void)
{
  ((void (*)(void))*(void **)0x2530b4)();
}

void NtSuspendThread(void)
{
  ((void (*)(void))*(void **)0x2530b8)();
}

void NtResumeThread(void)
{
  ((void (*)(void))*(void **)0x2530bc)();
}

void RtlRaiseException(void)
{
  ((void (*)(void))*(void **)0x2530c0)();
}

void NtQueueApcThread(void)
{
  ((void (*)(void))*(void **)0x2530c4)();
}

void PsTerminateSystemThread(void)
{
  ((void (*)(void))*(void **)0x2530cc)();
}

void PsCreateSystemThreadEx(void)
{
  ((void (*)(void))*(void **)0x2530d4)();
}

void NtCreateEvent(void)
{
  ((void (*)(void))*(void **)0x2530d8)();
}

void ObOpenObjectByName(void)
{
  ((void (*)(void))*(void **)0x2530dc)();
}

void NtSetEvent(void)
{
  ((void (*)(void))*(void **)0x2530e8)();
}

void NtPulseEvent(void)
{
  ((void (*)(void))*(void **)0x2530f0)();
}

void NtCreateSemaphore(void)
{
  ((void (*)(void))*(void **)0x2530f4)();
}

void NtReleaseSemaphore(void)
{
  ((void (*)(void))*(void **)0x2530fc)();
}

/* MmQueryAllocationSize (0x1d3717) — Capstone tip: IAT jmp [0x253210]. */
void MmQueryAllocationSize(void)
{
  ((void (*)(void))*(void **)0x253210)();
}

/* NtClearEvent (0x1d8c42) — Capstone tip: IAT jmp [0x2530ec]. */
void NtClearEvent(void)
{
  ((void (*)(void))*(void **)0x2530ec)();
}

/* NtCreateMutant (0x1d8c5a) — Capstone tip: IAT jmp [0x253100]. */
void NtCreateMutant(void)
{
  ((void (*)(void))*(void **)0x253100)();
}

/* NtReleaseMutant (0x1d8c60) — Capstone tip: IAT jmp [0x253108]. */
void NtReleaseMutant(void)
{
  ((void (*)(void))*(void **)0x253108)();
}

/* NtWaitForSingleObjectEx (0x1d8c66) — Capstone tip: IAT jmp [0x25310c]. */
void NtWaitForSingleObjectEx(void)
{
  ((void (*)(void))*(void **)0x25310c)();
}

/* NtSignalAndWaitForSingleObjectEx (0x1d8c6c) — Capstone tip: IAT jmp [0x253110]. */
void NtSignalAndWaitForSingleObjectEx(void)
{
  ((void (*)(void))*(void **)0x253110)();
}

/* NtWaitForMultipleObjectsEx (0x1d8c72) — Capstone tip: IAT jmp [0x253114]. */
void NtWaitForMultipleObjectsEx(void)
{
  ((void (*)(void))*(void **)0x253114)();
}

/* KeDelayExecutionThread (0x1d8c78) — Capstone tip: IAT jmp [0x253118]. */
void KeDelayExecutionThread(void)
{
  ((void (*)(void))*(void **)0x253118)();
}

/* NtCreateTimer (0x1d8c7e) — Capstone tip: IAT jmp [0x25311c]. */
void NtCreateTimer(void)
{
  ((void (*)(void))*(void **)0x25311c)();
}

/* NtSetTimerEx (0x1d8c84) — Capstone tip: IAT jmp [0x253124]. */
void NtSetTimerEx(void)
{
  ((void (*)(void))*(void **)0x253124)();
}

/* NtCancelTimer (0x1d8c8a) — Capstone tip: IAT jmp [0x253128]. */
void NtCancelTimer(void)
{
  ((void (*)(void))*(void **)0x253128)();
}

/* RtlFreeAnsiString (0x1d8c90) — Capstone tip: IAT jmp [0x25312c]. */
void RtlFreeAnsiString(void)
{
  ((void (*)(void))*(void **)0x25312c)();
}

/* RtlUnicodeStringToAnsiString (0x1d8c96) — Capstone tip: IAT jmp [0x253130]. */
void RtlUnicodeStringToAnsiString(void)
{
  ((void (*)(void))*(void **)0x253130)();
}

/* RtlInitUnicodeString (0x1d8c9c) — Capstone tip: IAT jmp [0x253134]. */
void RtlInitUnicodeString(void)
{
  ((void (*)(void))*(void **)0x253134)();
}

/* RtlTimeToTimeFields (0x1d8ca2) — Capstone tip: IAT jmp [0x253138]. */
void RtlTimeToTimeFields(void)
{
  ((void (*)(void))*(void **)0x253138)();
}

/* RtlTimeFieldsToTime (0x1d8cae) — Capstone tip: IAT jmp [0x253144]. */
void RtlTimeFieldsToTime(void)
{
  ((void (*)(void))*(void **)0x253144)();
}

/* NtAllocateVirtualMemory (0x1d8cb4) — Capstone tip: IAT jmp [0x253148]. */
void NtAllocateVirtualMemory(void)
{
  ((void (*)(void))*(void **)0x253148)();
}

/* NtFreeVirtualMemory (0x1d8cba) — Capstone tip: IAT jmp [0x25314c]. */
void NtFreeVirtualMemory(void)
{
  ((void (*)(void))*(void **)0x25314c)();
}

/* NtProtectVirtualMemory (0x1d8cc0) — Capstone tip: IAT jmp [0x253150]. */
void NtProtectVirtualMemory(void)
{
  ((void (*)(void))*(void **)0x253150)();
}

/* NtQueryVirtualMemory (0x1d8cc6) — Capstone tip: IAT jmp [0x253154]. */
void NtQueryVirtualMemory(void)
{
  ((void (*)(void))*(void **)0x253154)();
}

/* MmQueryStatistics (0x1d8ccc) — Capstone tip: IAT jmp [0x253158]. */
void MmQueryStatistics(void)
{
  ((void (*)(void))*(void **)0x253158)();
}

/* NtSetInformationFile (0x1d8cd2) — Capstone tip: IAT jmp [0x25315c]. */
void NtSetInformationFile(void)
{
  ((void (*)(void))*(void **)0x25315c)();
}

/* NtQueryFullAttributesFile (0x1d8cde) — Capstone tip: IAT jmp [0x253164]. */
void NtQueryFullAttributesFile(void)
{
  ((void (*)(void))*(void **)0x253164)();
}

/* FscSetCacheSize (0x1d8ce4) — Capstone tip: IAT jmp [0x253168]. */
void FscSetCacheSize(void)
{
  ((void (*)(void))*(void **)0x253168)();
}

/* FscGetCacheSize (0x1d8cea) — Capstone tip: IAT jmp [0x25316c]. */
void FscGetCacheSize(void)
{
  ((void (*)(void))*(void **)0x25316c)();
}

/* NtQueryDirectoryFile (0x1d8cf0) — Capstone tip: IAT jmp [0x253170]. */
void NtQueryDirectoryFile(void)
{
  ((void (*)(void))*(void **)0x253170)();
}

/* NtWaitForSingleObject (0x1d8cf6) — Capstone tip: IAT jmp [0x253174]. */
void NtWaitForSingleObject(void)
{
  ((void (*)(void))*(void **)0x253174)();
}

/* NtReadFile (0x1d8cfc) — Capstone tip: IAT jmp [0x253178]. */
void NtReadFile(void)
{
  ((void (*)(void))*(void **)0x253178)();
}

/* NtQueryInformationFile (0x1d8d08) — Capstone tip: IAT jmp [0x253180]. */
void NtQueryInformationFile(void)
{
  ((void (*)(void))*(void **)0x253180)();
}

/* NtFlushBuffersFile (0x1d8d14) — Capstone tip: IAT jmp [0x253188]. */
void NtFlushBuffersFile(void)
{
  ((void (*)(void))*(void **)0x253188)();
}

/* NtUserIoApcDispatcher (0x1d8d1a) — Capstone tip: IAT jmp [0x25318c]. */
void NtUserIoApcDispatcher(void)
{
  ((void (*)(void))*(void **)0x25318c)();
}

/* NtReadFileScatter (0x1d8d2c) — Capstone tip: IAT jmp [0x253198]. */
void NtReadFileScatter(void)
{
  ((void (*)(void))*(void **)0x253198)();
}

/* NtCreateFile (0x1d8d38) — Capstone tip: IAT jmp [0x2531a0]. */
void NtCreateFile(void)
{
  ((void (*)(void))*(void **)0x2531a0)();
}

/* MmAllocateSystemMemory (0x1d8d44) — Capstone tip: IAT jmp [0x2531a8]. */
void MmAllocateSystemMemory(void)
{
  ((void (*)(void))*(void **)0x2531a8)();
}

/* KeWaitForSingleObject (0x1d8d4a) — Capstone tip: IAT jmp [0x2531ac]. */
void KeWaitForSingleObject(void)
{
  ((void (*)(void))*(void **)0x2531ac)();
}

/* KfLowerIrql (0x1d8d50) — Capstone tip: IAT jmp [0x2531b0]. */
void KfLowerIrql(void)
{
  ((void (*)(void))*(void **)0x2531b0)();
}

/* KeRaiseIrqlToDpcLevel (0x1d8d56) — Capstone tip: IAT jmp [0x2531b4]. */
void KeRaiseIrqlToDpcLevel(void)
{
  ((void (*)(void))*(void **)0x2531b4)();
}

/* IoCreateDevice (0x1d8d5c) — Capstone tip: IAT jmp [0x2531b8]. */
void IoCreateDevice(void)
{
  ((void (*)(void))*(void **)0x2531b8)();
}

/* ExAllocatePool (0x1d8d62) — Capstone tip: IAT jmp [0x2531bc]. */
void ExAllocatePool(void)
{
  ((void (*)(void))*(void **)0x2531bc)();
}

/* KeSetEvent (0x1d8d68) — Capstone tip: IAT jmp [0x2531c0]. */
void KeSetEvent(void)
{
  ((void (*)(void))*(void **)0x2531c0)();
}

/* KeInitializeTimerEx (0x1d8d6e) — Capstone tip: IAT jmp [0x2531c4]. */
void KeInitializeTimerEx(void)
{
  ((void (*)(void))*(void **)0x2531c4)();
}

/* KeInitializeDpc (0x1d8d74) — Capstone tip: IAT jmp [0x2531c8]. */
void KeInitializeDpc(void)
{
  ((void (*)(void))*(void **)0x2531c8)();
}

/* IoInvalidDeviceRequest (0x1d8d7a) — Capstone tip: IAT jmp [0x2531cc]. */
void IoInvalidDeviceRequest(void)
{
  ((void (*)(void))*(void **)0x2531cc)();
}

/* RtlNtStatusToDosError (0x1d8d80) — Capstone tip: IAT jmp [0x2531d0]. */
void RtlNtStatusToDosError(void)
{
  ((void (*)(void))*(void **)0x2531d0)();
}

/* NtCreateIoCompletion (0x1d8d86) — Capstone tip: IAT jmp [0x2531d4]. */
void NtCreateIoCompletion(void)
{
  ((void (*)(void))*(void **)0x2531d4)();
}

/* NtSetIoCompletion (0x1d8d8c) — Capstone tip: IAT jmp [0x2531d8]. */
void NtSetIoCompletion(void)
{
  ((void (*)(void))*(void **)0x2531d8)();
}

/* NtRemoveIoCompletion (0x1d8d92) — Capstone tip: IAT jmp [0x2531dc]. */
void NtRemoveIoCompletion(void)
{
  ((void (*)(void))*(void **)0x2531dc)();
}

/* KeSetTimer (0x1d8d98) — Capstone tip: IAT jmp [0x2531e0]. */
void KeSetTimer(void)
{
  ((void (*)(void))*(void **)0x2531e0)();
}

/* KeCancelTimer (0x1d8d9e) — Capstone tip: IAT jmp [0x2531e4]. */
void KeCancelTimer(void)
{
  ((void (*)(void))*(void **)0x2531e4)();
}

/* MmPersistContiguousMemory (0x1d8da4) — Capstone tip: IAT jmp [0x2531e8]. */
void MmPersistContiguousMemory(void)
{
  ((void (*)(void))*(void **)0x2531e8)();
}

/* MmAllocateContiguousMemory (0x1d8daa) — Capstone tip: IAT jmp [0x2531ec]. */
void MmAllocateContiguousMemory(void)
{
  ((void (*)(void))*(void **)0x2531ec)();
}

/* HalReturnToFirmware (0x1d8db6) — Capstone tip: IAT jmp [0x2531f8]. */
void HalReturnToFirmware(void)
{
  ((void (*)(void))*(void **)0x2531f8)();
}

/* NtQuerySymbolicLinkObject (0x1d8dbc) — Capstone tip: IAT jmp [0x2531fc]. */
void NtQuerySymbolicLinkObject(void)
{
  ((void (*)(void))*(void **)0x2531fc)();
}

/* NtOpenSymbolicLinkObject (0x1d8dc2) — Capstone tip: IAT jmp [0x253200]. */
void NtOpenSymbolicLinkObject(void)
{
  ((void (*)(void))*(void **)0x253200)();
}

/* IoCreateSymbolicLink (0x1d8dec) — Capstone tip: IAT jmp [0x253220]. */
void IoCreateSymbolicLink(void)
{
  ((void (*)(void))*(void **)0x253220)();
}

/* IoDeleteSymbolicLink (0x1d8df2) — Capstone tip: IAT jmp [0x253224]. */
void IoDeleteSymbolicLink(void)
{
  ((void (*)(void))*(void **)0x253224)();
}

/* RtlFillMemoryUlong (0x1d8e10) — Capstone tip: IAT jmp [0x253244]. */
void RtlFillMemoryUlong(void)
{
  ((void (*)(void))*(void **)0x253244)();
}

/* RtlCompareMemoryUlong (0x1d8e16) — Capstone tip: IAT jmp [0x253248]. */
void RtlCompareMemoryUlong(void)
{
  ((void (*)(void))*(void **)0x253248)();
}

/* RtlCompareMemory (0x1d8e1c) — Capstone tip: IAT jmp [0x25324c]. */
void RtlCompareMemory(void)
{
  ((void (*)(void))*(void **)0x25324c)();
}

/* RtlInitializeCriticalSection (0x1d8e22) — Capstone tip: IAT jmp [0x253250]. */
void RtlInitializeCriticalSection(void)
{
  ((void (*)(void))*(void **)0x253250)();
}

/* IoStartPacket (0x1d8e28) — Capstone tip: IAT jmp [0x253258]. */
void IoStartPacket(void)
{
  ((void (*)(void))*(void **)0x253258)();
}

/* IofCompleteRequest (0x1d8e2e) — Capstone tip: IAT jmp [0x25325c]. */
void IofCompleteRequest(void)
{
  ((void (*)(void))*(void **)0x25325c)();
}

/* IoStartNextPacket (0x1d8e34) — Capstone tip: IAT jmp [0x253260]. */
void IoStartNextPacket(void)
{
  ((void (*)(void))*(void **)0x253260)();
}

/* ExFreePool (0x1d8e3a) — Capstone tip: IAT jmp [0x253264]. */
void ExFreePool(void)
{
  ((void (*)(void))*(void **)0x253264)();
}

/* IoMarkIrpMustComplete (0x1d8e40) — Capstone tip: IAT jmp [0x253268]. */
void IoMarkIrpMustComplete(void)
{
  ((void (*)(void))*(void **)0x253268)();
}

/* HalIsResetOrShutdownPending (0x1d8e46) — Capstone tip: IAT jmp [0x25326c]. */
void HalIsResetOrShutdownPending(void)
{
  ((void (*)(void))*(void **)0x25326c)();
}

/* KeQueryInterruptTime (0x1d8e4c) — Capstone tip: IAT jmp [0x253270]. */
void KeQueryInterruptTime(void)
{
  ((void (*)(void))*(void **)0x253270)();
}

/* HalInitiateShutdown (0x1d8e52) — Capstone tip: IAT jmp [0x253274]. */
void HalInitiateShutdown(void)
{
  ((void (*)(void))*(void **)0x253274)();
}

/* HalGetInterruptVector (0x1d8e58) — Capstone tip: IAT jmp [0x253278]. */
void HalGetInterruptVector(void)
{
  ((void (*)(void))*(void **)0x253278)();
}

/* KfRaiseIrql (0x1d8e5e) — Capstone tip: IAT jmp [0x25327c]. */
void KfRaiseIrql(void)
{
  ((void (*)(void))*(void **)0x25327c)();
}

/* HalRegisterShutdownNotification (0x1d8e64) — Capstone tip: IAT jmp [0x253280]. */
void HalRegisterShutdownNotification(void)
{
  ((void (*)(void))*(void **)0x253280)();
}

/* KeConnectInterrupt (0x1d8e6a) — Capstone tip: IAT jmp [0x253284]. */
void KeConnectInterrupt(void)
{
  ((void (*)(void))*(void **)0x253284)();
}

/* KeInitializeInterrupt (0x1d8e70) — Capstone tip: IAT jmp [0x253288]. */
void KeInitializeInterrupt(void)
{
  ((void (*)(void))*(void **)0x253288)();
}

/* KeStallExecutionProcessor (0x1d8e76) — Capstone tip: IAT jmp [0x25328c]. */
void KeStallExecutionProcessor(void)
{
  ((void (*)(void))*(void **)0x25328c)();
}

/* RtlEqualString (0x1d8e7c) — Capstone tip: IAT jmp [0x253290]. */
void RtlEqualString(void)
{
  ((void (*)(void))*(void **)0x253290)();
}

/* XeLoadSection (0x1d8e82) — Capstone tip: IAT jmp [0x253294]. */
void XeLoadSection(void)
{
  ((void (*)(void))*(void **)0x253294)();
}

/* XeUnloadSection (0x1d8e88) — Capstone tip: IAT jmp [0x253298]. */
void XeUnloadSection(void)
{
  ((void (*)(void))*(void **)0x253298)();
}

/* MmGetPhysicalAddress (0x1d8e8e) — Capstone tip: IAT jmp [0x25329c]. */
void MmGetPhysicalAddress(void)
{
  ((void (*)(void))*(void **)0x25329c)();
}

/* MmLockUnlockBufferPages (0x1d8e94) — Capstone tip: IAT jmp [0x2532a0]. */
void MmLockUnlockBufferPages(void)
{
  ((void (*)(void))*(void **)0x2532a0)();
}

/* KeInsertQueueDpc (0x1d8e9a) — Capstone tip: IAT jmp [0x2532a4]. */
void KeInsertQueueDpc(void)
{
  ((void (*)(void))*(void **)0x2532a4)();
}

/* MmLockUnlockPhysicalPage (0x1d8ea0) — Capstone tip: IAT jmp [0x2532a8]. */
void MmLockUnlockPhysicalPage(void)
{
  ((void (*)(void))*(void **)0x2532a8)();
}

/* AvGetSavedDataAddress (0x1d8ea6) — Capstone tip: IAT jmp [0x2532ac]. */
void AvGetSavedDataAddress(void)
{
  ((void (*)(void))*(void **)0x2532ac)();
}

/* AvSendTVEncoderOption (0x1d8eac) — Capstone tip: IAT jmp [0x2532b0]. */
void AvSendTVEncoderOption(void)
{
  ((void (*)(void))*(void **)0x2532b0)();
}

/* AvSetDisplayMode (0x1d8eb2) — Capstone tip: IAT jmp [0x2532b4]. */
void AvSetDisplayMode(void)
{
  ((void (*)(void))*(void **)0x2532b4)();
}

/* AvSetSavedDataAddress (0x1d8eb8) — Capstone tip: IAT jmp [0x2532b8]. */
void AvSetSavedDataAddress(void)
{
  ((void (*)(void))*(void **)0x2532b8)();
}

/* KeDisconnectInterrupt (0x1d8ec4) — Capstone tip: IAT jmp [0x2532c0]. */
void KeDisconnectInterrupt(void)
{
  ((void (*)(void))*(void **)0x2532c0)();
}

/* MmClaimGpuInstanceMemory (0x1d8eca) — Capstone tip: IAT jmp [0x2532c4]. */
void MmClaimGpuInstanceMemory(void)
{
  ((void (*)(void))*(void **)0x2532c4)();
}

/* ExQueryPoolBlockSize (0x1d8ed0) — Capstone tip: IAT jmp [0x2532c8]. */
void ExQueryPoolBlockSize(void)
{
  ((void (*)(void))*(void **)0x2532c8)();
}

/* ExAllocatePoolWithTag (0x1d8ed6) — Capstone tip: IAT jmp [0x2532cc]. */
void ExAllocatePoolWithTag(void)
{
  ((void (*)(void))*(void **)0x2532cc)();
}

/* KeRemoveQueueDpc (0x1d8edc) — Capstone tip: IAT jmp [0x2532d0]. */
void KeRemoveQueueDpc(void)
{
  ((void (*)(void))*(void **)0x2532d0)();
}

/* KeSynchronizeExecution (0x1d8ee2) — Capstone tip: IAT jmp [0x2532d4]. */
void KeSynchronizeExecution(void)
{
  ((void (*)(void))*(void **)0x2532d4)();
}

/* KeSaveFloatingPointState (0x1d8ee8) — Capstone tip: IAT jmp [0x2532d8]. */
void KeSaveFloatingPointState(void)
{
  ((void (*)(void))*(void **)0x2532d8)();
}

/* KeRestoreFloatingPointState (0x1d8eee) — Capstone tip: IAT jmp [0x2532dc]. */
void KeRestoreFloatingPointState(void)
{
  ((void (*)(void))*(void **)0x2532dc)();
}

/* PhyGetLinkState (0x1d8ef4) — Capstone tip: IAT jmp [0x2532e0]. */
void PhyGetLinkState(void)
{
  ((void (*)(void))*(void **)0x2532e0)();
}

/* PhyInitialize (0x1d8efa) — Capstone tip: IAT jmp [0x2532e4]. */
void PhyInitialize(void)
{
  ((void (*)(void))*(void **)0x2532e4)();
}

/* KeWaitForMultipleObjects (0x1d8f00) — Capstone tip: IAT jmp [0x2532e8]. */
void KeWaitForMultipleObjects(void)
{
  ((void (*)(void))*(void **)0x2532e8)();
}

/* KeSetTimerEx (0x1d8f12) — Capstone tip: IAT jmp [0x2532f4]. */
void KeSetTimerEx(void)
{
  ((void (*)(void))*(void **)0x2532f4)();
}

/* KeBugCheck (0x1e657e) — Capstone tip: IAT jmp [0x253318]. */
void KeBugCheck(void)
{
  ((void (*)(void))*(void **)0x253318)();
}

/* RtlAnsiStringToUnicodeString (0x1e658a) — Capstone tip: IAT jmp [0x253320]. */
void RtlAnsiStringToUnicodeString(void)
{
  ((void (*)(void))*(void **)0x253320)();
}

/* IDirectSoundBuffer_Unlock (0x203877) — Capstone tip: xor eax,eax; ret 0x14. */
int __stdcall IDirectSoundBuffer_Unlock(int a0, int a1, int a2, int a3, int a4)
{
  return 0;
}

/* ===== denser Capstone tips (track-a worktree) ===== */

/* QueueUserAPC (0x1cfb73) — Capstone tip: NtQueueApcThread → status≥0 bool. */
int __stdcall QueueUserAPC(void *pfn, void *thread, void *ctx)
{
  int status = ((int (__stdcall *)(void *, void *, void *, void *, int))*(void **)0x2530c4)(
      thread, (void *)0x1cfb68, pfn, ctx, 0);
  return status >= 0;
}

/* D3DBaseTexture_GetLevelCount (0x1e76b0) — Capstone tip: (byte[tex+0xe])&0xf. */
unsigned int __stdcall D3DBaseTexture_GetLevelCount(void *tex)
{
  return *(unsigned char *)((char *)tex + 0xe) & 0xf;
}

/* D3DDevice_GetVertexShaderSize (0x1eb540) — Capstone tip: null out → ret; else copy +0xf. */
void __stdcall D3DDevice_GetVertexShaderSize(void *shader, unsigned int *out_size)
{
  if (out_size)
    *out_size = *(unsigned *)((char *)shader + 0xf);
}

/* D3DDevice_GetDeviceCaps (0x1e69f0) — Capstone tip: memcpy 0x35 dwords from 0x3301f8. */
void __stdcall D3DDevice_GetDeviceCaps(void *caps)
{
  unsigned *dst = (unsigned *)caps;
  unsigned *src = (unsigned *)0x3301f8;
  int i;
  for (i = 0; i < 0x35; i++)
    dst[i] = src[i];
}

/* D3D_GetDeviceCaps (0x1eecf0) — Capstone tip: bad adapter/type HRESULT; else fill. */
int __stdcall D3D_GetDeviceCaps(void *adapter, unsigned int devtype, void *caps)
{
  if (adapter)
    return (int)0x8876086c;
  if (devtype != 1)
    return (int)0x8876086b;
  D3DDevice_GetDeviceCaps(caps);
  return 0;
}

/* DirectSoundGetSampleTime (0x2038d9) — Capstone tip: read MMIO 0xfe80200c. */
unsigned int DirectSoundGetSampleTime(void)
{
  return *(unsigned *)0xfe80200c;
}

/* DirectSoundEnterCriticalSection (0x20368b) — Capstone tip: IRQL≠0 → 0; else EnterCS. */
int DirectSoundEnterCriticalSection(void)
{
  unsigned char irql;
  __asm__ volatile("movb %%fs:0x24, %0" : "=r"(irql));
  if (irql)
    return 0;
  ((void (__stdcall *)(void *))*(void **)0x25309c)((void *)0x222674);
  return 1;
}

/* CDirectSound_GetTime (0x203dd4) — Capstone tip: KeQueryInterruptTime IAT → 0. */
int __stdcall CDirectSound_GetTime(void *this_ptr, void *out_time)
{
  (void)this_ptr;
  ((void (__stdcall *)(void *))*(void **)0x25313c)(out_time);
  return 0;
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

/* XGetDevices (0x24c932) — Capstone tip: raise/lower IRQL around device bitmap. */
unsigned int __stdcall XGetDevices(void *out)
{
  unsigned bits;
  unsigned char irql;
  void *raise_fn = *(void **)0x2531b4;
  void *lower_fn = *(void **)0x2531b0;
  __asm__ volatile("call *%[fn]" : "=a"(irql) : [fn] "r"(raise_fn) : "memory", "ecx", "edx");
  bits = *(unsigned *)out;
  ((unsigned *)out)[1] = 0;
  ((unsigned *)out)[2] = bits;
  __asm__ volatile("movb %[irql], %%cl; call *%[fn]" :: [irql] "r"(irql), [fn] "r"(lower_fn) : "memory", "eax", "ecx", "edx");
  return bits;
}

/* D3DDevice_GetPixelShader (0x1ec160) — Capstone tip: device+0x414 → *out. */
void __stdcall D3DDevice_GetPixelShader(void **out_shader)
{
  void *dev = *(void **)0x1fe6a0;
  *out_shader = *(void **)((char *)dev + 0x414);
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

/* D3DDevice_BlockUntilVerticalBlank (0x1e7110) — Capstone tip: KeWaitForSingleObject. */
void D3DDevice_BlockUntilVerticalBlank(void)
{
  char *dev = *(char **)0x1fe6a0;
  *(unsigned *)(dev + 0x24f4) = 0;
  ((void (__stdcall *)(void *, int, int, int, int))*(void **)0x2531ac)(dev + 0x24f0, 6, 1, 0, 0);
}

/* D3DDevice_GetProjectionViewportMatrix (0x1e7140) — Capstone tip: copy 16 floats. */
void __stdcall D3DDevice_GetProjectionViewportMatrix(void *out)
{
  unsigned *dst = (unsigned *)out;
  unsigned *src = (unsigned *)(*(char **)0x1fe6a0 + 0x5a0);
  int i;
  for (i = 0; i < 0x10; i++)
    dst[i] = src[i];
}

/* D3DDevice_GetTransform (0x1e6ce0) — Capstone tip: copy matrix by type. */
void __stdcall D3DDevice_GetTransform(unsigned int type, void *matrix_out)
{
  unsigned *dst = (unsigned *)matrix_out;
  unsigned *src = (unsigned *)(*(char **)0x1fe6a0 + ((type + 0x22) << 6));
  int i;
  for (i = 0; i < 0x10; i++)
    dst[i] = src[i];
}

/* FUN_001d03ee (0x1d03ee) — Capstone tip: expand 4 bytes → 4 words + NUL. */
void __stdcall FUN_001d03ee(unsigned char *src, unsigned short *dst)
{
  int i;
  for (i = 0; i < 4; i++)
    dst[i] = src[i];
  dst[4] = 0;
}

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

