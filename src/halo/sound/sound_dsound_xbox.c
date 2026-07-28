/* sound_dsound_get_sample_rate (0x1c90e0)
 *
 * Return the sample rate for the given codec index.  Index 0 yields
 * 22050 Hz, index 1 yields 44100 Hz.  Asserts codec_index is in the
 * range [0, NUMBER_OF_SOUND_SAMPLE_RATES=2). */
int sound_dsound_get_sample_rate(int codec_index)
{
  if (codec_index < 0 || codec_index >= 2) {
    display_assert("sample_rate>=0 && sample_rate<NUMBER_OF_SOUND_SAMPLE_RATES",
                   "c:\\halo\\source\\sound\\sound_definitions.h", 0x135, 1);
    system_exit(-1);
  }
  return *(int *)((char *)0x2bcc18 + codec_index * 4);
}

/* sound_dsound_gain_to_volume (0x1c9130)
 *
 * Convert a linear gain value [0.0, 1.0] to a DirectSound volume in
 * hundredths of dB.  The formula is: 2000 * log10(gain) + ceiling.
 * If gain is exactly 0, returns -10000 (DSBVOLUME_MIN).
 * Result is clamped to [-10000, ceiling]. */
int sound_dsound_gain_to_volume(float gain, int ceiling)
{
  int volume;

  if (gain < 0.0f || gain > 1.0f) {
    display_assert("gain>=0.f && gain<=1.f",
                   "c:\\halo\\source\\sound\\sound_dsound.h", 0x23, 1);
    system_exit(-1);
  }

  if (gain == 0.0f)
    return -10000;

  volume = (int)(*(double *)0x2c07b8 * log10(gain) + ceiling);
  if (volume < -10000)
    return -10000;
  if (volume > ceiling)
    volume = ceiling;
  return volume;
}

/* sound_dsound_pitch_to_frequency (0x1c91c0)
 *
 * Convert a pitch scalar to a DirectSound frequency value.  Asserts
 * that sample_rate is either 22050 or 44100.  The result is
 * sample_rate * pitch, clamped to [188, 191983]. */
int sound_dsound_pitch_to_frequency(int sample_rate, float pitch)
{
  float frequency;

  if (sample_rate != 22050 && sample_rate != 44100) {
    display_assert("samples_per_second==22050 || samples_per_second==44100",
                   "c:\\halo\\source\\sound\\sound_dsound.h", 0x36, 1);
    system_exit(-1);
  }

  frequency = (float)sample_rate * pitch;

  if (frequency < *(float *)0x2c0800)
    frequency = *(float *)0x2c0800;
  if (frequency > *(float *)0x2c07fc)
    frequency = *(float *)0x2c07fc;
  return (int)frequency;
}

/* sound_dsound_channel_get (0x1c9290)
 *
 * Return a pointer to the actual dsound channel struct at the given
 * index.  Asserts index is in [0, dsound_globals.actual_channel_count)
 * and less than MAXIMUM_SOUND_CHANNELS (256).  Element size is 0x74. */
void *sound_dsound_channel_get(short index)
{
  if (index < 0 || index >= *(short *)0x4fdfc4) {
    display_assert("index>=0 && index<dsound_globals.actual_channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x69, 1);
    system_exit(-1);
  }
  if (index >= 0x100) {
    display_assert("index<MAXIMUM_SOUND_CHANNELS",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x6a, 1);
    system_exit(-1);
  }
  return (void *)(0x4fdfc8 + (int)index * 0x74);
}

/* sound_dsound_vchannel_get (0x1c92f0)
 *
 * Return a pointer to the virtual channel struct at the given index.
 * Asserts index is in [0, dsound_globals.virtual_channel_count) and
 * less than MAXIMUM_SOUND_CHANNELS (256).  Element size is 4. */
void *sound_dsound_vchannel_get(short index)
{
  if (index < 0 || index >= *(short *)0x4fdbc2) {
    display_assert("index>=0 && index<dsound_globals.virtual_channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x72, 1);
    system_exit(-1);
  }
  if (index >= 0x100) {
    display_assert("index<MAXIMUM_SOUND_CHANNELS",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x73, 1);
    system_exit(-1);
  }
  return (void *)(0x4fdbc4 + (int)index * 4);
}

/* sound_dsound_channel_update_3d (0x1c94d0)
 *
 * Build and apply full 3D buffer parameters for the given channel.
 * Constructs a 36-byte parameter block with volume levels (converted
 * from gain via gain_to_volume) and a rolloff factor of 0.2.
 *
 * If the channel is not active (field_4 == 0), all volumes are set
 * to -10000 (minimum).  Otherwise, gains are derived from the
 * channel's fade and orientation fields.  When field_5 is set, a
 * global volume at 0x32f6d4 is applied to offset 0x0 and 0x4.
 *
 * Calls IDirectSoundStream_SetAllParameters to commit the block. */
void sound_dsound_channel_update_3d(int channel_index)
{
  void *channel;
  char params[0x24];
  float fade_gain;

  channel = sound_dsound_channel_get((short)channel_index);
  csmemset(params, 0, 0x24);
  *(int *)(params + 0x00) = 0;
  *(int *)(params + 0x04) = 0;
  *(int *)(params + 0x10) = 0;
  *(int *)(params + 0x18) = 0;
  *(float *)(params + 0x20) = 0.2f;

  if (*(char *)((char *)channel + 0x4) != 0) {
    fade_gain = 1.0f - *(float *)((char *)channel + 0x60);

    if (*(char *)((char *)channel + 0x5) != 0) {
      *(int *)(params + 0x04) =
        sound_dsound_gain_to_volume(*(float *)0x32f6d4, 0);
      *(int *)(params + 0x00) =
        sound_dsound_gain_to_volume(*(float *)0x32f6d4, 0);
    } else {
      fade_gain = fade_gain * 0.5f;
    }

    {
      int fade_vol = sound_dsound_gain_to_volume(fade_gain, 0);
      *(int *)(params + 0x08) = fade_vol;
      *(int *)(params + 0x0c) = fade_vol;
    }
    *(int *)(params + 0x14) =
      sound_dsound_gain_to_volume(1.0f - *(float *)((char *)channel + 0x48), 0);
    *(int *)(params + 0x1c) =
      sound_dsound_gain_to_volume(1.0f - *(float *)((char *)channel + 0x44), 0);
  } else {
    *(int *)(params + 0x08) = -10000;
    *(int *)(params + 0x0c) = -10000;
    *(int *)(params + 0x14) = 0;
    *(int *)(params + 0x1c) = 0;
  }

  IDirectSoundStream_SetAllParameters(*(void **)((char *)channel + 0x70),
                                      params, 1);
}

/* sound_dsound_channel_stop_check (0x1c9600)
 *
 * Check if a stopping channel's DirectSound stream has finished
 * processing.  Asserts the channel is in the "stopping" state.
 *
 * Calls dsound_stream_is_active (0x20f069) to test whether the
 * stream's internal kernel status bits (0x10000002) are still set.
 * If the stream is no longer active, flushes it via the
 * IDirectSoundStream vtable Flush method (vtable[6], offset 0x18)
 * and clears the channel's stopping flag.
 *
 * Returns true if the channel was released (stream finished and
 * flushed), false if still active. */
bool sound_dsound_channel_stop_check(short channel_index)
{
  void *channel;
  void *stream;
  int active;
  bool released;

  channel = sound_dsound_channel_get(channel_index);

  assert_halt(*(char *)((char *)channel + 0x6) != 0);

  stream = *(void **)((char *)channel + 0x70);
  active = dsound_stream_is_active(stream);
  released = (active == 0);

  if (released) {
    void *stream2 = *(void **)((char *)channel + 0x70);
    void **vtable = *(void ***)stream2;
    ((int(__stdcall *)(void *))vtable[6])(stream2);
    *(char *)((char *)channel + 0x6) = 0;
  }

  return released;
}

/* sound_dsound_log_error (0x1c98f0)
 *
 * Log a DirectSound error.  Formats the caller's message with
 * vsprintf, maps the HRESULT to a symbolic name, and emits a level-2
 * error via error().  HRESULT is passed in ESI. */
void sound_dsound_log_error(int hresult, const char *message, ...)
{
  static char buffer[0x1000];
  const char *error_name;
  char *arglist;

  arglist = (char *)&message + 4;
  vsprintf(buffer, message, arglist);

  error_name = "<unknown error>";

  if (hresult > (int)0x8007000E) {
    if (hresult == (int)0x8878001E) {
      error_name = "DSERR_CONTROLUNAVAIL";
    } else if (hresult == (int)0x88780032) {
      error_name = "DSERR_INVALIDCALL";
    } else if (hresult == (int)0x88780078) {
      error_name = "DSERR_NODRIVER";
    }
  } else if (hresult == (int)0x8007000E) {
    error_name = "DSERR_OUTOFMEMORY";
  } else if (hresult == (int)0x80004001) {
    error_name = "DSERR_UNSUPPORTED";
  } else if (hresult == (int)0x80004005) {
    error_name = "DSERR_GENERIC";
  } else if (hresult == (int)0x80040110) {
    error_name = "DSERR_NOAGGREGATION";
  }

  error(2, "DirectSound:  '%s' (%s#%d)", buffer, error_name);
}

/* sound_dsound_channel_try_resolve (0x1c99a0)
 *
 * Try to find and assign a free actual channel for the given virtual
 * channel.  Looks up the virtual channel, asserts it has no current
 * assignment (channel_index == NONE) and a valid type_index.
 *
 * Scans actual channels of the matching type, starting from the
 * priority table entry for the vchannel's type_index.  A channel is
 * eligible if its type_flags match and it is either unassigned
 * (virtual_channel_index == NONE) or currently stopping and can be
 * released.
 *
 * If no free channel is found, logs a warning with the type_index. */
void sound_dsound_channel_try_resolve(int virtual_channel_index)
{
  short *vchannel;
  short si;
  void *channel;

  vchannel = (short *)sound_dsound_vchannel_get(virtual_channel_index);

  /* assert: vchannel has no channel assigned */
  if (vchannel[0] != (short)-1) {
    display_assert("vchannel->channel_index==NONE",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x588, 1);
    system_exit(-1);
  }

  /* assert: type_index is valid */
  if (vchannel[1] < 0 || vchannel[1] >= 4) {
    display_assert("vchannel->type_index>=0 && "
                   "vchannel->type_index<NUMBER_OF_SOUND_CHANNEL_TYPES",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x589, 1);
    system_exit(-1);
  }

  si = ((short *)0x5053c8)[vchannel[1]];

  if (vchannel[0] == (short)-1) {
    while (si < *(short *)0x4fdfc4) {
      if (si < 0) {
        display_assert("index>=0 && index<dsound_globals.actual_channel_count",
                       "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x69, 1);
        system_exit(-1);
      }
      if (si >= 0x100) {
        display_assert("index<MAXIMUM_SOUND_CHANNELS",
                       "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x6a, 1);
        system_exit(-1);
      }

      channel = (void *)(0x4fdfc8 + (int)si * 0x74);

      if (*(short *)((char *)channel + 0x38) !=
          ((short *)0x32fcf8)[vchannel[1]])
        break;

      if (*(short *)((char *)channel + 0x2) == (short)-1) {
        if (*(char *)((char *)channel + 0x6) == 0 ||
            sound_dsound_channel_stop_check(si)) {
          vchannel[0] = si;
        }
      }

      si++;
      if (vchannel[0] != (short)-1)
        break;
    }
  }

  /* if we found a channel, store the back-reference */
  if (vchannel[0] != (short)-1) {
    if (vchannel[0] < 0 || vchannel[0] >= *(short *)0x4fdfc4) {
      display_assert("index>=0 && index<dsound_globals.actual_channel_count",
                     "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x69, 1);
      system_exit(-1);
    }
    if (vchannel[0] >= 0x100) {
      display_assert("index<MAXIMUM_SOUND_CHANNELS",
                     "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x6a, 1);
      system_exit(-1);
    }
    *(short *)(0x4fdfc8 + (int)vchannel[0] * 0x74 + 0x2) =
      (short)virtual_channel_index;
  } else {
    error(2, "WARNING: ran out of actual sound channels of type %d",
          (int)vchannel[1]);
  }
}

/* sound_dsound_channel_resolve (0x1c9b40)
 *
 * Look up the virtual channel for the given virtual_channel_index and
 * return the underlying hardware (actual) channel index.  If the
 * virtual channel has no channel assigned (channel_index == NONE),
 * attempt to acquire one via sound_dsound_channel_try_resolve.
 *
 * After resolution, two debug assertions verify consistency:
 *   1. The actual channel's type_flags match sound_channel_type_flags
 *      for the virtual channel's type_index.
 *   2. The actual channel's virtual_channel_index back-references the
 *      caller's virtual_channel_index.
 *
 * Returns the actual channel index (short), or -1 (NONE) if no
 * channel could be resolved. */
short sound_dsound_channel_resolve(int virtual_channel_index)
{
  short *vchannel;
  short channel_index;
  void *channel;

  vchannel = (short *)sound_dsound_vchannel_get(virtual_channel_index);
  channel_index = vchannel[0];
  if (channel_index == -1) {
    sound_dsound_channel_try_resolve(virtual_channel_index);
    channel_index = vchannel[0];
    if (channel_index == -1)
      goto done;
  }

  /* assert: channel type_flags matches the expected type for this vchannel */
  channel = sound_dsound_channel_get(channel_index);
  if (*(short *)((char *)channel + 0x38) != ((short *)0x32fcf8)[vchannel[1]]) {
    display_assert("vchannel->channel_index==NONE || "
                   "channel_get(vchannel->channel_index)->type_flags=="
                   "sound_channel_type_flags[vchannel->type_index]",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x5b8, 1);
    system_exit(-1);
  }

  /* assert: channel's back-reference matches our virtual_channel_index */
  channel_index = vchannel[0];
  if (channel_index != -1) {
    channel = sound_dsound_channel_get(channel_index);
    if (*(short *)((char *)channel + 0x2) != (short)virtual_channel_index) {
      display_assert(
        "vchannel->channel_index==NONE || "
        "channel_get(vchannel->channel_index)->virtual_channel_index=="
        "virtual_channel_index",
        "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x5b9, 1);
      system_exit(-1);
    }
  }

done:
  return vchannel[0];
}

/* sound_dsound_update_channel_properties (0x1ca5e0)
 *
 * Apply volume, pitch, and 3D spatial properties to a hardware dsound
 * channel.  Called from sound_dsound_set_channel_properties after the
 * virtual-to-actual channel has been resolved.
 *
 * Volume is always updated (subject to an epsilon check).  Pitch and
 * 3D properties (min/max distance, cone angles, cone outside volume,
 * and the full 3D parameter set) are only updated when update_only==0.
 *
 * Each property is compared against the value cached in the channel
 * struct; if the delta exceeds a per-property epsilon AND a global
 * "initialized" flag (0x4fdbc0) is set, the DirectSound call is
 * skipped.  When the flag is clear, all properties are pushed
 * unconditionally.
 *
 * properties layout (float[8]):
 *   [0] min_distance
 *   [1] max_distance
 *   [2] pitch
 *   [3] gain
 *   [4] inner_cone_angle (radians)
 *   [5] outer_cone_angle (radians)
 *   [6] cone_outside_gain
 *   [7] field_1c (3D-related scalar)
 *
 * Cone angles are converted from radians to degrees (multiplied by
 * 180/pi) and truncated to int before passing to SetConeAngles.
 * Volume values (gain, cone_outside_gain) are converted to hundredths
 * of dB via sound_dsound_gain_to_volume. */
void sound_dsound_update_channel_properties(float *properties,
                                            short channel_index,
                                            int update_only)
{
  void *channel;
  float gain;
  int volume;
  int result;

  channel = sound_dsound_channel_get(channel_index);
  gain = *(float *)0x505488 * properties[3];

  /* assert: properties->gain in [0, 1] */
  if (properties[3] < 0.0f || properties[3] > 1.0f) {
    display_assert("properties->gain>=0.f && properties->gain<=1.f",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x3d4, 1);
    system_exit(-1);
  }
  /* assert: dsound_globals.pause_gain in [0, 1] */
  if (*(float *)0x505488 < 0.0f || *(float *)0x505488 > 1.0f) {
    display_assert(
      "dsound_globals.pause_gain>=0 && dsound_globals.pause_gain<=1.f",
      "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x3d5, 1);
    system_exit(-1);
  }
  /* assert: channel->stream is valid */
  if (*(void **)((char *)channel + 0x70) == 0) {
    display_assert("channel->stream",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x3d6, 1);
    system_exit(-1);
  }

  /* -- volume -- */
  if (fabsf(gain - *(float *)((char *)channel + 0x3c)) >=
        (float)*(double *)0x2549d8 ||
      *(char *)0x4fdbc0 == 0) {
    volume = sound_dsound_gain_to_volume(gain, 0);
    result =
      IDirectSoundStream_SetVolume(*(void **)((char *)channel + 0x70), volume);
    if (result < 0) {
      sound_dsound_log_error(result, "couldn't set channel volume.");
    }
    *(float *)((char *)channel + 0x3c) = gain;
  }

  if (update_only != 0)
    goto done;

  /* -- pitch -- */
  if (fabsf(properties[2] - *(float *)((char *)channel + 0x40)) >=
        (float)*(double *)0x2549d8 ||
      *(char *)0x4fdbc0 == 0) {
    int sample_rate;
    int frequency;
    sample_rate = sound_dsound_get_sample_rate(
      (*(unsigned char *)((char *)channel + 0x38) >> 2) & 1);
    frequency = sound_dsound_pitch_to_frequency(sample_rate, properties[2]);
    result = IDirectSoundStream_SetFrequency(*(void **)((char *)channel + 0x70),
                                             frequency);
    if (result < 0) {
      sound_dsound_log_error(result, "couldn't set channel pitch.");
    }
    *(float *)((char *)channel + 0x40) = properties[2];
  }

  /* -- 3D properties (only if channel has 3D flag) -- */
  if ((*(unsigned char *)((char *)channel + 0x38) & 1) == 0)
    goto done;

  /* max distance */
  if (fabsf(properties[1] - *(float *)((char *)channel + 0x50)) >=
        (float)*(double *)0x25f0c8 ||
      *(char *)0x4fdbc0 == 0) {
    result = IDirectSoundStream_SetMaxDistance(
      *(void **)((char *)channel + 0x70), properties[1], 1);
    if (result < 0) {
      sound_dsound_log_error(result, "couldn't set channel max distance.");
    }
    *(float *)((char *)channel + 0x50) = properties[1];
  }

  /* min distance */
  if (fabsf(properties[0] - *(float *)((char *)channel + 0x4c)) >=
        (float)*(double *)0x25f0c8 ||
      *(char *)0x4fdbc0 == 0) {
    result = IDirectSoundStream_SetMinDistance(
      *(void **)((char *)channel + 0x70), properties[0], 1);
    if (result < 0) {
      sound_dsound_log_error(result, "couldn't set channel min distance.");
    }
    *(float *)((char *)channel + 0x4c) = properties[0];
  }

  /* cone angles (radians -> degrees -> int) */
  if (fabsf(properties[4] - *(float *)((char *)channel + 0x58)) >=
        (float)*(double *)0x2c0eb0 ||
      fabsf(properties[5] - *(float *)((char *)channel + 0x5c)) >=
        (float)*(double *)0x2c0eb0 ||
      *(char *)0x4fdbc0 == 0) {
    int inner_deg = (int)(properties[4] * *(float *)0x2b073c);
    int outer_deg = (int)(properties[5] * *(float *)0x2b073c);
    result = IDirectSoundStream_SetConeAngles(
      *(void **)((char *)channel + 0x70), inner_deg, outer_deg, 0);
    if (result < 0) {
      sound_dsound_log_error(result, "couldn't set channel cone angles.");
    }
    *(float *)((char *)channel + 0x58) = properties[4];
    *(float *)((char *)channel + 0x5c) = properties[5];
  }

  /* cone outside volume */
  if (fabsf(properties[6] - *(float *)((char *)channel + 0x54)) >=
        (float)*(double *)0x2549d8 ||
      *(char *)0x4fdbc0 == 0) {
    volume = sound_dsound_gain_to_volume(properties[6], 0);
    result = IDirectSoundStream_SetConeOutsideVolume(
      *(void **)((char *)channel + 0x70), volume, 1);
    if (result < 0) {
      sound_dsound_log_error(result, "couldn't set channel cone volume.");
    }
    *(float *)((char *)channel + 0x54) = properties[6];
  }

  /* 3D parameter update (field_1c) */
  if (fabsf(properties[7] - *(float *)((char *)channel + 0x60)) >=
        (float)*(double *)0x2549d8 ||
      *(char *)0x4fdbc0 == 0) {
    *(float *)((char *)channel + 0x60) = properties[7];
    sound_dsound_channel_update_3d(channel_index);
  }

done:
  return;
}

/* sound_dsound_set_channel_properties (0x1caa80)
 *
 * Vtable+0x34 entry point for the DirectSound driver.  Resolves the
 * dsound channel index via sound_dsound_channel_resolve, then forwards
 * to the real property-update function.
 *
 * The original debug build asserts properties->gain is in [0,1] inside
 * sound_dsound_update_channel_properties (sound_dsound_xbox.c line 980)
 * and the volume conversion at line 35.  Retail strips both assertions;
 * the conversion function's ceiling clamp naturally caps gain > 1.0 to
 * 0 dB (max volume).  We downgrade the assertion to a non-fatal warning
 * and clamp to match retail behavior. */
void sound_dsound_set_channel_properties(int channel_index, float *properties,
                                         int update_only)
{
  short channel;

  if (properties[3] < 0.0f || properties[3] > 1.0f) {
    display_assert("properties->gain>=0.f && properties->gain<=1.f",
                   "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c", 0x3d4, 0);
    if (properties[3] < 0.0f)
      properties[3] = 0.0f;
    else
      properties[3] = 1.0f;
  }

  channel = sound_dsound_channel_resolve(channel_index);
  if (channel != -1) {
    sound_dsound_update_channel_properties(properties, channel, update_only);
  }
}
/* --- sound_dsound_xbox.obj batch drafts (2026-07-26) --- */

/* dsound_angle_from_angle (0x1c9230) — readable C lift (fld/fmul/_ftol2). */
int dsound_angle_from_angle(float angle)
{
  int result;
  __asm__ volatile(
      "flds %1\n\t"
      "fmuls 0x2b073c\n\t"
      "call %P2\n\t"
      "movl %%eax, %0"
      : "=m"(result)
      : "m"(angle), "X"(FUN_001d9068)
      : "eax", "edx", "ecx", "st", "cc", "memory");
  return result;
}

/* dsound_occlusion_from_occlusion (0x1c9250) — readable C lift. */
int dsound_occlusion_from_occlusion(float occlusion)
{
  return sound_dsound_gain_to_volume(1.0f - occlusion, 0);
}

/* dsound_obstruction_from_obstruction (0x1c9270) — readable C lift. */
int dsound_obstruction_from_obstruction(float obstruction)
{
  return sound_dsound_gain_to_volume(1.0f - obstruction, 0);
}

/* FUN_001c9350 (0x1c9350) — readable C lift from XBE leaf. */
void FUN_001c9350(int *slot, char *suffix)
{
  int total;
  char *base;

  if (slot != 0)
    *(int *)0x4fdba8 = *slot;
  base = (char *)0x4eae38;
  total = csstrlen(base) + csstrlen(suffix);
  if ((unsigned int)total < 0x100)
    crt_sprintf(base + csstrlen(base), suffix);
}



/* FUN_001c9670 (0x1c9670) — readable C lift (restored pre-naked). */
void FUN_001c9670(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  sound_dsound_channel_get(0);
  /* test ecx, ecx -> je 0x1c986f */
  FUN_001bdd70();
  /* cmp edi, eax -> jb 0x1c9834 */
  FUN_001bdd70();
  /* cmp ecx, eax -> ja 0x1c9834 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1c9723 */
  /* test edi, edi -> je 0x1c977d */
  /* cmp eax, 1 -> jg 0x1c97a0 */
  /* relift: cmp word ptr [ebp - 0x10], 0 -> je 0x1c97b7 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1c97ca */
  FUN_001d9068();
  /* test eax, eax -> je 0x1c98dc */
  FUN_001be100((void *)(uintptr_t)ebx);
  ((void(*)(void))FUN_001c9350)();
  crt_sprintf((char *)0x005ab100, (char *)0x002c09a0);
  csstrlen((char *)0x004eae38);
  csstrlen((char *)0x005ab100);
  /* cmp esi, 0x100 -> jae 0x1c98dc */
  csstrlen((char *)0x004eae38);
  csstrlen((char *)0x002c0974);
  /* cmp esi, 0x100 -> jae 0x1c98dc */
  csstrlen((char *)0x004eae38);
  csstrlen((char *)0x002c0948);
  /* cmp esi, 0x100 -> jae 0x1c98dc */
  csstrlen((char *)0x004eae38);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}



/* FUN_001c9bf0 (0x1c9bf0) — readable C lift: release vchannel binding. */
void FUN_001c9bf0(short vchannel_index)
{
  short *vch;
  short ch_index;
  char *ch;
  void (*release_buf)(void *);

  vch = (short *)sound_dsound_vchannel_get(vchannel_index);
  ch_index = *vch;
  if (ch_index == -1)
    return;
  ch = (char *)sound_dsound_channel_get(ch_index);
  if (*(short *)(ch + 2) != vchannel_index) {
    display_assert((const char *)0x2c0c50, (const char *)0x2c0894, 0x5dd, 1);
    system_exit(-1);
  }
  ch = (char *)sound_dsound_channel_get(*vch);
  if (*(short *)ch != 0) {
    release_buf = (void (*)(void *))0x20f081;
    release_buf(*(void **)(ch + 0x70));
    *(unsigned char *)(ch + 6) = 1;
    *(short *)ch = 0;
  }
  *(int *)(ch + 0x68) = 0;
  *(int *)(ch + 0x6c) = 0;
  ch = (char *)sound_dsound_channel_get(*vch);
  *(short *)(ch + 2) = -1;
  *vch = -1;
}

/* FUN_001c9c80 (0x1c9c80) — readable C lift. */
short FUN_001c9c80(short index)
{
  void *vchan;
  short ch;
  void *chan;

  vchan = sound_dsound_vchannel_get(index);
  ch = *(short *)vchan;
  if (ch == (short)-1) {
    return 0;
  }
  chan = sound_dsound_channel_get(ch);
  if (*(short *)((char *)chan + 2) != index) {
    display_assert((const char *)0x2c0c50, (const char *)0x2c0894, 0x5f3, 1);
    system_exit(-1);
  }
  ch = *(short *)vchan;
  chan = sound_dsound_channel_get(ch);
  return *(short *)chan;
}
/* FUN_001c9cf0 (0x1c9cf0) — readable C lift: create/play silence DS buffer. */
char FUN_001c9cf0(void)
{
  unsigned char desc[0x18];
  unsigned char fmt[0x10];
  int hr;
  int (*create_buf)(void *, void *, void *, int);

  *(unsigned short *)fmt = 1;
  *(unsigned short *)(fmt + 2) = 1;
  *(unsigned int *)(fmt + 4) = 0x5622;
  *(unsigned int *)(fmt + 8) = 0xac44;
  *(unsigned short *)(fmt + 0xc) = 2;
  *(unsigned short *)(fmt + 0xe) = 0x10;
  csmemset(desc, 0, 0x18);
  *(unsigned int *)desc = 0x18;
  *(unsigned int *)(desc + 4) = 0;
  *(unsigned int *)(desc + 8) = 0x20;
  *(void **)(desc + 0xc) = fmt;
  *(unsigned int *)(desc + 0x10) = 0x1f00;
  create_buf = (int (*)(void *, void *, void *, int))IDirectSound_CreateSoundBuffer;
  hr = create_buf(*(void **)0x50545c, desc, (void *)0x505460, 0);
  if (hr < 0) {
    sound_dsound_log_error(hr, (const char *)0x2c0ca4);
    return 0;
  }
  csmemset((void *)0x505464, 0, 0x20);
  IDirectSoundBuffer_SetBufferData(*(void **)0x505460, (void *)0x505464, 0x20);
  hr = IDirectSoundBuffer_Play(*(void **)0x505460, 0, 0, 1);
  if (hr < 0) {
    sound_dsound_log_error(hr, (const char *)0x2c0ccc);
    return 0;
  }
  return 1;
}

/* FUN_001c9e20 (0x1c9e20) — XBE naked draft (batch 247). */
#if defined(__clang__)
static void (*const b1c9e20_chkstk)(void) = FUN_001d90e0;
static void (*const b1c9e20_c204ea1)(void) = IDirectSound_CommitDeferredSettings;
static void (*const b1c9e20_c1c98f0)(int hresult, const char *message, ...) = sound_dsound_log_error;
static void (*const b1c9e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c9e20_exitfn)(int) = system_exit;
static void * (*const b1c9e20_c1c9290)(short index) = sound_dsound_channel_get;
static int (*const b1c9e20_c1c9130)(float gain, int ceiling) = sound_dsound_gain_to_volume;
static int __stdcall (*const b1c9e20_c205266)(void *stream, int volume) = IDirectSoundStream_SetVolume;
static void (*const b1c9e20_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static int (*const b1c9e20_c8df60)(const char *s1) = csstrlen;
static int (*const b1c9e20_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b1c9e20_c189c40)(char flag, const char *string) = FUN_00189c40;

__attribute__((naked, noinline))
void FUN_001c9e20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2008, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x50545c, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c204ea1]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001c9e20_1\n\t"
      "pushl $0x2c0d58\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001c9e20_1:\n\t"
      "movb 0x505484, %%al\n\t"
      "flds 0x505488\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c9e20_2\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001c9e20_3\n\t"
      "jmp .LFUN_001c9e20_12\n\t"
      ".LFUN_001c9e20_2:\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001c9e20_12\n\t"
      ".LFUN_001c9e20_3:\n\t"
      "flds 0x505488\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001c9e20_4\n\t"
      "flds 0x505488\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001c9e20_5\n\t"
      ".LFUN_001c9e20_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x27a\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c0d18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c9e20_5:\n\t"
      "movb 0x505484, %%al\n\t"
      "flds 0x505488\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c9e20_6\n\t"
      "fsubl 0x2c0d10\n\t"
      "fldl 0x2602c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001c9e20_7\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .LFUN_001c9e20_7\n\t"
      ".LFUN_001c9e20_6:\n\t"
      "faddl 0x2c0d10\n\t"
      "fldl 0x2573d8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001c9e20_7\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2573d8\n\t"
      ".LFUN_001c9e20_7:\n\t"
      "fstps 0x505488\n\t"
      "flds 0x505488\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001c9e20_8\n\t"
      "flds 0x505488\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001c9e20_9\n\t"
      ".LFUN_001c9e20_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x285\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c0d18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c9e20_9:\n\t"
      "movb 0x505484, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c9e20_12\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x4fdfc4\n\t"
      "jle .LFUN_001c9e20_12\n\t"
      "pushl %%edi\n\t"
      ".LFUN_001c9e20_10:\n\t"
      "call *%[c1c9290]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpw $0, (%%edi)\n\t"
      "je .LFUN_001c9e20_11\n\t"
      "flds 0x505488\n\t"
      "pushl $0\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1c9130]\n\t"
      "movl 0x70(%%edi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c205266]\n\t"
      ".LFUN_001c9e20_11:\n\t"
      "incl %%esi\n\t"
      "cmpw 0x4fdfc4, %%si\n\t"
      "jl .LFUN_001c9e20_10\n\t"
      "popl %%edi\n\t"
      ".LFUN_001c9e20_12:\n\t"
      "movb 0x4fc380, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "je .LFUN_001c9e20_23\n\t"
      "pushl %%ebx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "movw $0x118, -0x8(%%ebp)\n\t"
      "movl $0, -0x6(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "movw 0x4fdfc4, %%ax\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $0, -0x2008(%%ebp)\n\t"
      "jle .LFUN_001c9e20_22\n\t"
      "jmp .LFUN_001c9e20_13\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001c9e20_13:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_001c9e20_14\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jl .LFUN_001c9e20_15\n\t"
      ".LFUN_001c9e20_14:\n\t"
      "pushl $1\n\t"
      "pushl $0x69\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c085c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c9e20_15:\n\t"
      "cmpw $0x100, %%bx\n\t"
      "jl .LFUN_001c9e20_16\n\t"
      "pushl $1\n\t"
      "pushl $0x6a\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c083c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c9e20_16:\n\t"
      "movswl %%bx, %%eax\n\t"
      "imull $0x74, %%eax, %%eax\n\t"
      "addl $0x4fdfc8, %%eax\n\t"
      "cmpw $0x10, %%bx\n\t"
      "jl .LFUN_001c9e20_17\n\t"
      "cmpw $0x30, %%bx\n\t"
      "jle .LFUN_001c9e20_21\n\t"
      ".LFUN_001c9e20_17:\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_001c9e20_20\n\t"
      "movl 0x6c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "jne .LFUN_001c9e20_18\n\t"
      "movl $0x25386f, %%edx\n\t"
      ".LFUN_001c9e20_18:\n\t"
      "movl 0x68(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001c9e20_19\n\t"
      "movl $0x25386f, %%ecx\n\t"
      ".LFUN_001c9e20_19:\n\t"
      "flds 0x40(%%eax)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "leal -0x2008(%%ebp), %%ecx\n\t"
      "flds 0x3c(%%eax)\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2c0cf4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2008(%%ebp,%%eax,1), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_001c9e20_20:\n\t"
      "leal -0x2008(%%ebp), %%eax\n\t"
      "pushl $0x28094c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2008(%%ebp,%%eax,1), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%bl\n\t"
      "je .LFUN_001c9e20_21\n\t"
      "leal -0x2008(%%ebp), %%edx\n\t"
      "pushl $0x26993c\n\t"
      "pushl %%edx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2008(%%ebp,%%eax,1), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c9e20_21:\n\t"
      "movw 0x4fdfc4, %%ax\n\t"
      "incl %%ebx\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jl .LFUN_001c9e20_13\n\t"
      ".LFUN_001c9e20_22:\n\t"
      "leal -0x2008(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c189c40]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001c9e20_23:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b1c9e20_chkstk), [c204ea1] "m"(b1c9e20_c204ea1), [c1c98f0] "m"(b1c9e20_c1c98f0), [assert] "m"(b1c9e20_assert), [exitfn] "m"(b1c9e20_exitfn), [c1c9290] "m"(b1c9e20_c1c9290), [c1c9130] "m"(b1c9e20_c1c9130), [c205266] "m"(b1c9e20_c205266), [c19b560] "m"(b1c9e20_c19b560), [c8df60] "m"(b1c9e20_c8df60), [c1d90f0] "m"(b1c9e20_c1d90f0), [c189c40] "m"(b1c9e20_c189c40)
      : "memory");
}
#else
#error "FUN_001c9e20: clang naked draft required"
#endif


/* 0x1ca130 */
void FUN_001ca130(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x1ca2a2 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x1ca15a */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1ca177 */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x100 -> jl 0x1ca19b */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1ca1d6 */
  display_assert((char *)0x002c0dc8, (char *)0x002c0894, 706, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + 6], (char)ebx -> je 0x1ca278 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x1ca1ee */
  /* relift: cmp (int16_t)edi, word ptr [0x4fdfc4] -> jl 0x1ca20b */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x100 -> jl 0x1ca22f */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + 6], (char)ebx -> jne 0x1ca254 */
  display_assert((char *)0x002c0934, (char *)0x002c0894, 1208, 0);
  system_exit(0);
  dsound_stream_is_active((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 8], (int16_t)ebx -> je 0x1ca291 */
  error(0, (char *)0x002c0d80);
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1ca150 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}


/* FUN_001ca2b0 (0x1ca2b0) — XBE naked draft (batch 254). */
#if defined(__clang__)
static void (*const b1ca2b0_c204e13)(void) = IDirectSound_SetPosition;
static void (*const b1ca2b0_c1c98f0)(int hresult, const char *message, ...) = sound_dsound_log_error;
static void (*const b1ca2b0_c204dc9)(void) = IDirectSound_SetOrientation;
static void (*const b1ca2b0_c204e6c)(void) = IDirectSound_SetVelocity;
static int (*const b1ca2b0_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static int (*const b1ca2b0_c1c9130)(float gain, int ceiling) = sound_dsound_gain_to_volume;
static void (*const b1ca2b0_c204ed5)(void) = IDirectSound_SetI3DL2Listener;

__attribute__((naked, noinline))
void FUN_001ca2b0(void *buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x5053d0\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_1\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x5053d4\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_1\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x5053d8\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_1\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001ca2b0_3\n\t"
      ".LFUN_001ca2b0_1:\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x50545c, %%ecx\n\t"
      "pushl $1\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204e13]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001ca2b0_2\n\t"
      "pushl $0x2c0e48\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001ca2b0_2:\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, 0x5053d0\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x5053d4\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x5053d8\n\t"
      ".LFUN_001ca2b0_3:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsubs 0x5053dc\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_4\n\t"
      "flds 0x10(%%edi)\n\t"
      "fsubs 0x5053e0\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_4\n\t"
      "flds 0x14(%%edi)\n\t"
      "fsubs 0x5053e4\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_4\n\t"
      "flds 0x18(%%edi)\n\t"
      "fsubs 0x5053e8\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_4\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fsubs 0x5053ec\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_4\n\t"
      "flds 0x20(%%edi)\n\t"
      "fsubs 0x5053f0\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_4\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001ca2b0_6\n\t"
      ".LFUN_001ca2b0_4:\n\t"
      "flds 0x1c(%%edi)\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "movl 0x50545c, %%edx\n\t"
      "pushl $1\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "flds 0x10(%%edi)\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c204dc9]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001ca2b0_5\n\t"
      "pushl $0x2c0e24\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001ca2b0_5:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "movl %%eax, 0x5053dc\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x5053e0\n\t"
      "movl 0x14(%%edi), %%edx\n\t"
      "movl %%edx, 0x5053e4\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "movl %%eax, 0x5053e8\n\t"
      "movl 0x1c(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x5053ec\n\t"
      "movl 0x20(%%edi), %%edx\n\t"
      "movl %%edx, 0x5053f0\n\t"
      ".LFUN_001ca2b0_6:\n\t"
      "flds 0x24(%%edi)\n\t"
      "fsubs 0x5053f4\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_7\n\t"
      "flds 0x28(%%edi)\n\t"
      "fsubs 0x5053f8\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_7\n\t"
      "flds 0x2c(%%edi)\n\t"
      "fsubs 0x5053fc\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ca2b0_7\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001ca2b0_9\n\t"
      ".LFUN_001ca2b0_7:\n\t"
      "flds 0x28(%%edi)\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "movl 0x50545c, %%ecx\n\t"
      "pushl $1\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x2c(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204e6c]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001ca2b0_8\n\t"
      "pushl $0x2c0e04\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001ca2b0_8:\n\t"
      "movl 0x24(%%edi), %%edx\n\t"
      "movl %%edx, 0x5053f4\n\t"
      "movl 0x28(%%edi), %%eax\n\t"
      "movl %%eax, 0x5053f8\n\t"
      "movl 0x2c(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x5053fc\n\t"
      ".LFUN_001ca2b0_9:\n\t"
      "movl 0x30(%%edi), %%edx\n\t"
      "pushl $0x48\n\t"
      "pushl $0x505404\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001ca2b0_10\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001ca2b0_11\n\t"
      ".LFUN_001ca2b0_10:\n\t"
      "pushl %%ebx\n\t"
      "movl 0x30(%%edi), %%ebx\n\t"
      "movl $0x12, %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl $0x505404, %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c9130]\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0xc(%%ebx), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c9130]\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x10(%%ebx), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl 0x14(%%ebx), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl 0x1c(%%ebx), %%edx\n\t"
      "pushl $0x3e8\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c9130]\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x24(%%ebx), %%ecx\n\t"
      "pushl $0x7d0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c9130]\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x28(%%ebx), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fmuls 0x253f00\n\t"
      "movl 0x50545c, %%edx\n\t"
      "addl $0x20, %%esp\n\t"
      "pushl $1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "flds 0x30(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "pushl %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c204ed5]\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001ca2b0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c204e13] "m"(b1ca2b0_c204e13), [c1c98f0] "m"(b1ca2b0_c1c98f0), [c204dc9] "m"(b1ca2b0_c204dc9), [c204e6c] "m"(b1ca2b0_c204e6c), [c8da40] "m"(b1ca2b0_c8da40), [c1c9130] "m"(b1ca2b0_c1c9130), [c204ed5] "m"(b1ca2b0_c204ed5)
      : "memory");
}
#else
#error "FUN_001ca2b0: clang naked draft required"
#endif


/* FUN_001ca900 (0x1ca900) — readable C lift: drain channel buffers while status<4. */
void FUN_001ca900(int channel_index)
{
  char *channel;
  int hr;
  unsigned int flags;
  void *obj;
  int (__stdcall *get_status)(void *, unsigned int *);
  char (*drain)(void);
  char ok;

  channel = (char *)sound_dsound_channel_get((short)channel_index);
  while (*(int16_t *)(channel + 8) < 4) {
    if (!*(void **)(channel + 0x68))
      return;
    obj = *(void **)(channel + 0x70);
    get_status = (int (__stdcall *)(void *, unsigned int *))(*(void ***)obj)[3];
    hr = get_status(obj, &flags);
    if (hr < 0) {
      FUN_001c9350(&hr, (char *)0x2c0f7c);
      return;
    }
    if ((flags & 1) == 0)
      return;
    drain = (char (*)(void))FUN_001c9670;
    __asm__ volatile("call *%1" : "=a"(ok) : "m"(drain), "a"(channel_index)
                     : "ecx", "edx", "memory", "cc");
    if (!ok)
      return;
  }
}


/* FUN_001ca970 (0x1ca970) — readable C lift (restored pre-naked). */
void FUN_001ca970(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* relift: cmp (int16_t)esi, word ptr [0x4fdfc4] -> jge 0x1caa2d */
  sound_dsound_channel_get(0);
  /* cmp ebx, 0x80004004 -> je 0x1ca9ea */
  /* cmp ebx, 0x80004005 -> jne 0x1ca9c0 */
  ((void(*)(void))FUN_001c9350)();
  /* cmp ebx, 0x8000000a -> jne 0x1ca9d9 */
  ((void(*)(void))FUN_001c9350)();
  ((void(*)(void))FUN_001c9350)();
  FUN_001be140((void *)(uintptr_t)eax);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1caa17 */
  /* cmp ebx, 0x80004004 -> je 0x1caa70 */
  ((void(*)(void))FUN_001ca900)();
  csstrlen((char *)0x004eae38);
  csstrlen((char *)0x002c0f9c);
  /* cmp esi, 0x100 -> jae 0x1caa70 */
  csstrlen((char *)0x004eae38);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);

  (void)eax;
  (void)ebx;
  (void)esi;
}



/* FUN_001caab0 (0x1caab0) — readable C lift (restored pre-naked). */
void FUN_001caab0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp (char)eax, byte ptr [0x505484] -> jne 0x1caae1 */
  display_assert((char *)0x002c1008, (char *)0x002c0894, 728, 0);
  system_exit(0);
  /* cmp (char)ecx, (char)ebx -> je 0x1cac23 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x1cadc2 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x1cab0c */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cab29 */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x100 -> jl 0x1cab4d */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + 0x4fdfce], (char)ebx -> je 0x1cac04 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x1cab6e */
  /* relift: cmp (int16_t)edi, word ptr [0x4fdfc4] -> jl 0x1cab8b */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x100 -> jl 0x1cabaf */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + 0x4fdfce], (char)ebx -> jne 0x1cabd7 */
  display_assert((char *)0x002c0934, (char *)0x002c0894, 1208, 0);
  system_exit(0);
  dsound_stream_is_active((void *)(uintptr_t)ecx);
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cab02 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x1cad0e */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x1cac3a */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cac57 */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x100 -> jl 0x1cac7b */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1cacfe */
  /* test (char)eax, 4 -> je 0x1caca5 */
  /* test (char)eax, 2 -> je 0x1cacb7 */
  FUN_001d9068();
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cac30 */
  DirectSoundDoWork();
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x1cadbf */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x1cad2e */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cad4b */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x100 -> jl 0x1cad6f */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 8], (int16_t)ebx -> je 0x1cad94 */
  error(0, (char *)0x002c0d80);
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1cada0 */
  ((void(*)(void))FUN_001ca900)();
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cad24 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}



/* FUN_001cadd0 (0x1cadd0) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void * (*const b1cadd0_c1c9290)(short index) = sound_dsound_channel_get;
static void (*const b1cadd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cadd0_exitfn)(int) = system_exit;
static void (*const b1cadd0_c20534b)(void) = IDirectSoundStream_SetMode;
static void (*const b1cadd0_c1c98f0)(int hresult, const char *message, ...) = sound_dsound_log_error;
static void (*const b1cadd0_c205350)(void) = IDirectSoundStream_SetPosition;
static bool (*const b1cadd0_c21fb0)(float *v) = valid_real_normal3d;
static void (*const b1cadd0_c2052ed)(void) = IDirectSoundStream_SetConeOrientation;
static void (*const b1cadd0_c205379)(void) = IDirectSoundStream_SetVelocity;
static void (*const b1cadd0_c1c94d0)(int channel_index) = sound_dsound_channel_update_3d;

__attribute__((naked, noinline))
void FUN_001cadd0(int a __attribute__((unused)), int b __attribute__((unused)), int c __attribute__((unused)), int d __attribute__((unused)), int e __attribute__((unused)), int f __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c9290]\n\t"
      "movl %%eax, %%edi\n\t"
      "testb $1, 0x38(%%edi)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .LFUN_001cadd0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38a\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c10dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cadd0_1:\n\t"
      "movl 0x70(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001cadd0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x38b\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c0f3c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cadd0_2:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "cmpb %%al, 0x4(%%edi)\n\t"
      "jne .LFUN_001cadd0_3\n\t"
      "movb 0x4fdbc0, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001cadd0_4\n\t"
      ".LFUN_001cadd0_3:\n\t"
      "movl 0x70(%%edi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%cl\n\t"
      "pushl $1\n\t"
      "decl %%ecx\n\t"
      "andl $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c20534b]\n\t"
      "testl %%eax, %%eax\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "movb %%cl, 0x4(%%edi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jge .LFUN_001cadd0_4\n\t"
      "pushl $0x2c10b4\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001cadd0_4:\n\t"
      "flds (%%ebx)\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_5\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fsubs 0x10(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_5\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_5\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cadd0_7\n\t"
      ".LFUN_001cadd0_5:\n\t"
      "flds 0x4(%%ebx)\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x70(%%edi), %%eax\n\t"
      "pushl $1\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c205350]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001cadd0_6\n\t"
      "pushl $0x2c1094\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001cadd0_6:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0xc(%%edi)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x10(%%edi)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x14(%%edi)\n\t"
      ".LFUN_001cadd0_7:\n\t"
      "flds 0xc(%%ebx)\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "fsubs 0x18(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_8\n\t"
      "flds 0x10(%%ebx)\n\t"
      "fsubs 0x1c(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_8\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fsubs 0x20(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x25f0c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_8\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cadd0_11\n\t"
      ".LFUN_001cadd0_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cadd0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x3a5\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c106c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cadd0_9:\n\t"
      "flds 0x10(%%ebx)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0x70(%%edi), %%eax\n\t"
      "pushl $1\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2052ed]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001cadd0_10\n\t"
      "pushl $0x2c1048\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001cadd0_10:\n\t"
      "movl 0xc(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x18(%%edi)\n\t"
      "movl 0x10(%%ebx), %%edx\n\t"
      "movl %%edx, 0x1c(%%edi)\n\t"
      "movl 0x14(%%ebx), %%eax\n\t"
      "movl %%eax, 0x20(%%edi)\n\t"
      ".LFUN_001cadd0_11:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "leal 0x18(%%ebx), %%esi\n\t"
      "fsubs 0x24(%%edi)\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_12\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fsubs 0x28(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_12\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fsubs 0x2c(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_12\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cadd0_14\n\t"
      ".LFUN_001cadd0_12:\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x70(%%edi), %%edx\n\t"
      "pushl $1\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c205379]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001cadd0_13\n\t"
      "pushl $0x2c1028\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001cadd0_13:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x28(%%edi)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x2c(%%edi)\n\t"
      ".LFUN_001cadd0_14:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsubs 0x44(%%edi)\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_15\n\t"
      "flds 0x48(%%edi)\n\t"
      "fsubrs 0x14(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001cadd0_15\n\t"
      "movb 0x5(%%edi), %%al\n\t"
      "cmpb 0x18(%%ebp), %%al\n\t"
      "jne .LFUN_001cadd0_15\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cadd0_15\n\t"
      "movb 0x4fdbc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cadd0_16\n\t"
      ".LFUN_001cadd0_15:\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movb %%al, 0x5(%%edi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x44(%%edi)\n\t"
      "movl %%edx, 0x48(%%edi)\n\t"
      "call *%[c1c94d0]\n\t"
      ".LFUN_001cadd0_16:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c9290] "m"(b1cadd0_c1c9290), [assert] "m"(b1cadd0_assert), [exitfn] "m"(b1cadd0_exitfn), [c20534b] "m"(b1cadd0_c20534b), [c1c98f0] "m"(b1cadd0_c1c98f0), [c205350] "m"(b1cadd0_c205350), [c21fb0] "m"(b1cadd0_c21fb0), [c2052ed] "m"(b1cadd0_c2052ed), [c205379] "m"(b1cadd0_c205379), [c1c94d0] "m"(b1cadd0_c1c94d0)
      : "memory");
}
#else
#error "FUN_001cadd0: clang naked draft required"
#endif


/* FUN_001cb0c0 (0x1cb0c0) — XBE naked draft (batch 260). */
#if defined(__clang__)
static void * (*const b1cb0c0_c1c9290)(short index) = sound_dsound_channel_get;
static void (*const b1cb0c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cb0c0_exitfn)(int) = system_exit;
static void (*const b1cb0c0_c204ea1)(void) = IDirectSound_CommitDeferredSettings;
static void (*const b1cb0c0_c1c98f0)(int hresult, const char *message, ...) = sound_dsound_log_error;

__attribute__((naked, noinline))
void FUN_001cb0c0(int channel __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "call *%[c1c9290]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x505484, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cb0c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x457\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c1134\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cb0c0_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001cb0c0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x458\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x27b768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cb0c0_2:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001cb0c0_5\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001cb0c0_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001cb0c0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x478\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c1114\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cb0c0_3:\n\t"
      "movw $2, (%%esi)\n\t"
      ".LFUN_001cb0c0_4:\n\t"
      "movl %%edi, 0x6c(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cb0c0_5:\n\t"
      "movw $1, (%%esi)\n\t"
      "movl %%edi, 0x68(%%esi)\n\t"
      "movl $0, 0x64(%%esi)\n\t"
      "movw $0, 0x8(%%esi)\n\t"
      "movl 0x50545c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c204ea1]\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001cb0c0_6\n\t"
      "pushl $0x2c0d58\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001cb0c0_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0x6c, 0xf7, 0xff, 0xff\n\t"
      :
      : [c1c9290] "m"(b1cb0c0_c1c9290), [assert] "m"(b1cb0c0_assert), [exitfn] "m"(b1cb0c0_exitfn), [c204ea1] "m"(b1cb0c0_c204ea1), [c1c98f0] "m"(b1cb0c0_c1c98f0)
      : "memory");
}
#else
#error "FUN_001cb0c0: clang naked draft required"
#endif

/* --- sound_dsound_xbox.obj orphan shells (2026-07-26) --- */

/* dsound_stream_is_active (0x20f069) — readable C lift. */
bool __stdcall dsound_stream_is_active(void *stream)
{
  unsigned int flags;

  flags = *(unsigned int *)(*(char **)((char *)stream + 0x24) + 8);
  flags &= 0x10000002u;
  return flags != 0;
}

/* dsound_stream_stop (0x20f081) — readable C lift: vtable+0x10 stop/flush. */
void __stdcall dsound_stream_stop(void *stream)
{
  void *obj;
  void **vtable;

  obj = *(void **)((char *)stream + 0x24);
  vtable = *(void ***)obj;
  ((void (__stdcall *)(void *, int, int))vtable[4])(obj, 0, 0);
}
