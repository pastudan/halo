/* --- bink.obj batch drafts (2026-07-26) --- */

/* 0x22df80 */
int __stdcall BinkSoundUseDirectSound(void *dsound_proc, void *dsound_handle)
{
  (void)dsound_proc;
  (void)dsound_handle;
  return 0;
}

/* 0x22e320 */
void __stdcall BinkSetMemory(unsigned int size)
{
  (void)size;
}

/* 0x22e530 */
int __stdcall BinkCopyToBuffer(void *bink_handle, void *dest, int pitch, int height, int x, int y, unsigned int flags)
{
  (void)bink_handle;
  (void)dest;
  (void)pitch;
  (void)height;
  (void)x;
  (void)y;
  (void)flags;
  return 0;
}

/* 0x22eb40 */
int __stdcall BinkDoFrame(void *bink_handle)
{
  (void)bink_handle;
  return 0;
}

/* 0x22f1e0 */
int __stdcall BinkWait(void *bink_handle)
{
  (void)bink_handle;
  return 0;
}

/* 0x22f480 */
void __stdcall BinkGetSummary(void *bink_handle, void *summary)
{
  (void)bink_handle;
  (void)summary;
}

/* 0x22f650 */
void __stdcall BinkGetFrameBuffersInfo(void *bink_handle, void *frame_info, unsigned int frame_count)
{
  (void)bink_handle;
  (void)frame_info;
  (void)frame_count;
}

/* 0x230390 */
void *__stdcall BinkOpen(const char *filename, unsigned int flags)
{
  (void)filename;
  (void)flags;
  return NULL;
}

/* 0x230ff0 */
int __stdcall BinkNextFrame(void *bink_handle)
{
  (void)bink_handle;
  return 0;
}

/* 0x231220 */
void __stdcall BinkClose(void *bink_handle)
{
  (void)bink_handle;
}

/* 0x231490 */
void __stdcall BinkSetSoundSystem(void *open_proc, void *close_proc)
{
  (void)open_proc;
  (void)close_proc;
}
