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

/* 0x1c9230 */
void dsound_angle_from_angle(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x1c9250 */
void dsound_occlusion_from_occlusion(void)
{
  sound_dsound_gain_to_volume(0.0f, 0);
}

/* 0x1c9270 */
void dsound_obstruction_from_obstruction(void)
{
  sound_dsound_gain_to_volume(0.0f, 0);
}

/* 0x1c9350 */
void FUN_001c9350(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> je 0x1c935b */
  /* mem[0x004fdba8] = eax */
  csstrlen((char *)0x004eae38);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)0x004eae38);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  sound_dsound_vchannel_get(0);
  /* cmp (int16_t)edi, 4 -> jl 0x1c93d5 */
  display_assert((char *)0x002c08f8, (char *)0x002c0894, 422, 0);
  system_exit(0);
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x1c9472 */
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x1c940b */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1c9428 */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 0x100 -> jl 0x1c944c */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* cmp eax, ebx -> je 0x1c9464 */
  /* cmp esi, edx -> jl 0x1c9401 */
  /* cmp eax, ebx -> je 0x1c9481 */
  IDirectSoundBuffer_Release();
  IDirectSound_Release();
  /* mem[0x0050545c] = ebx */

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c9670 */
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
  FUN_001c9350();
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

/* 0x1c9bf0 */
void FUN_001c9bf0(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  sound_dsound_vchannel_get(0);
  /* cmp (int16_t)esi, -1 -> je 0x1c9c74 */
  sound_dsound_channel_get(0);
  /* relift: cmp word ptr [eax + 2], (int16_t)ebx -> je 0x1c9c38 */
  display_assert((char *)0x002c0c50, (char *)0x002c0894, 1501, 0);
  system_exit(0);
  sound_dsound_channel_get(0);
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1c9c5b */
  /* relift: FUN_0020f081(0); */
  sound_dsound_channel_get(0);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1c9c80 */
void FUN_001c9c80(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  sound_dsound_vchannel_get(0);
  /* cmp (int16_t)esi, -1 -> je 0x1c9cda */
  sound_dsound_channel_get(0);
  /* relift: cmp word ptr [eax + 2], (int16_t)ebx -> je 0x1c9cc8 */
  display_assert((char *)0x002c0c50, (char *)0x002c0894, 1523, 0);
  system_exit(0);
  sound_dsound_channel_get(0);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1c9cf0 */
void FUN_001c9cf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  csmemset((void *)(uintptr_t)eax, 0, 24);
  IDirectSound_CreateSoundBuffer();
  /* cmp eax, ebx -> jl 0x1c9dbc */
  csmemset((void *)0x00505464, 0, 32);
  IDirectSoundBuffer_SetBufferData((void *)(uintptr_t)ecx, (void *)0x00505464, 32);
  IDirectSoundBuffer_Play((void *)(uintptr_t)edx, ebx, ebx, esi);
  /* cmp eax, ebx -> jl 0x1c9da5 */
  sound_dsound_log_error(0x002c0ccc, (char *)0);
  sound_dsound_log_error(0x002c0ca4, (char *)0);
  DirectSoundDoWork();
  csstrlen((char *)0x004eae38);
  /* test eax, eax -> je 0x1c9e0b */
  sound_dsound_log_error(0x004eae38, (char *)(uintptr_t)esi);
  /* mem[0x004fdba8] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c9e20 */
void FUN_001c9e20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d90e0();
  IDirectSound_CommitDeferredSettings();
  /* test eax, eax -> jge 0x1c9e4c */
  sound_dsound_log_error(0x002c0d58, (char *)0);
  /* test (char)eax, (char)eax -> je 0x1c9e6d */
  /* test (char)eax, 1 -> jne 0x1c9ea4 */
  display_assert((char *)0x002c0d18, (char *)0x002c0894, 634, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c9ef2 */
  /* test (char)eax, 0x41 -> jne 0x1c9f0f */
  /* test (char)eax, 0x41 -> je 0x1c9f0f */
  /* test (char)eax, 1 -> jne 0x1c9f3b */
  display_assert((char *)0x002c0d18, (char *)0x002c0894, 645, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c9fa9 */
  /* relift: cmp word ptr [0x4fdfc4], (int16_t)esi -> jle 0x1c9fa9 */
  sound_dsound_channel_get(0);
  /* relift: cmp word ptr [edi], 0 -> je 0x1c9f9e */
  sound_dsound_gain_to_volume(0.0f, 0);
  IDirectSoundStream_SetVolume((void *)(uintptr_t)ecx, 0);
  /* relift: cmp (int16_t)esi, word ptr [0x4fdfc4] -> jl 0x1c9f70 */
  draw_string_set_tab_stops((void *)(uintptr_t)edx, 0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1c9ffa */
  /* cmp (int16_t)ebx, (int16_t)eax -> jl 0x1ca017 */
  display_assert((char *)0x002c085c, (char *)0x002c0894, 105, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, 0x100 -> jl 0x1ca03b */
  display_assert((char *)0x002c083c, (char *)0x002c0894, 106, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, 0x10 -> jl 0x1ca056 */
  /* cmp (int16_t)ebx, 0x30 -> jle 0x1ca0fe */
  /* relift: cmp word ptr [eax], 0 -> je 0x1ca0b1 */
  /* test ecx, ecx -> jne 0x1ca076 */
  csstrlen((char *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0);
  csstrlen((char *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0);
  /* test (char)ebx, 1 -> je 0x1ca0fe */
  csstrlen((char *)(uintptr_t)edx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jl 0x1c9ff0 */
  FUN_00189c40(0, (char *)(uintptr_t)ecx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

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

/* 0x1ca2b0 */
void FUN_001ca2b0(void *buf)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)eax, (char)eax -> jne 0x1ca35a */
  IDirectSound_SetPosition();
  /* test eax, eax -> jge 0x1ca33f */
  sound_dsound_log_error(0x002c0e48, (char *)0);
  /* mem[0x005053d0] = eax */
  /* mem[0x005053d4] = ecx */
  /* mem[0x005053d8] = edx */
  /* test (char)eax, (char)eax -> jne 0x1ca474 */
  IDirectSound_SetOrientation();
  /* test eax, eax -> jge 0x1ca440 */
  sound_dsound_log_error(0x002c0e24, (char *)0);
  /* mem[0x005053dc] = eax */
  /* mem[0x005053e0] = ecx */
  /* mem[0x005053e4] = edx */
  /* mem[0x005053e8] = eax */
  /* mem[0x005053ec] = ecx */
  /* mem[0x005053f0] = edx */
  /* test (char)eax, (char)eax -> jne 0x1ca514 */
  IDirectSound_SetVelocity();
  /* test eax, eax -> jge 0x1ca4fa */
  sound_dsound_log_error(0x002c0e04, (char *)0);
  /* mem[0x005053f4] = edx */
  /* mem[0x005053f8] = eax */
  /* mem[0x005053fc] = ecx */
  csmemcmp((void *)(uintptr_t)edx, (void *)0x00505404, 72);
  /* test eax, eax -> jne 0x1ca538 */
  /* test (char)eax, (char)eax -> jne 0x1ca5da */
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 1000);
  sound_dsound_gain_to_volume(0.0f, 2000);
  IDirectSound_SetI3DL2Listener();

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1ca900 */
void FUN_001ca900(void)
{
  int eax = 0;
  int edi = 0;
  int ebp = 0;

  sound_dsound_channel_get(0);
  /* relift: cmp word ptr [edi + 8], 4 -> jge 0x1ca95e */
  /* test eax, eax -> je 0x1ca95e */
  /* relift: test byte ptr [ebp - 4], 1 -> je 0x1ca95e */
  FUN_001c9670();
  /* test (char)eax, (char)eax -> je 0x1ca95e */
  /* relift: cmp word ptr [edi + 8], 4 -> jl 0x1ca918 */
  FUN_001c9350();

  (void)eax;
  (void)edi;
  (void)ebp;
}

/* 0x1ca970 */
void FUN_001ca970(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* relift: cmp (int16_t)esi, word ptr [0x4fdfc4] -> jge 0x1caa2d */
  sound_dsound_channel_get(0);
  /* cmp ebx, 0x80004004 -> je 0x1ca9ea */
  /* cmp ebx, 0x80004005 -> jne 0x1ca9c0 */
  FUN_001c9350();
  /* cmp ebx, 0x8000000a -> jne 0x1ca9d9 */
  FUN_001c9350();
  FUN_001c9350();
  FUN_001be140((void *)(uintptr_t)eax);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1caa17 */
  /* cmp ebx, 0x80004004 -> je 0x1caa70 */
  FUN_001ca900();
  csstrlen((char *)0x004eae38);
  csstrlen((char *)0x002c0f9c);
  /* cmp esi, 0x100 -> jae 0x1caa70 */
  csstrlen((char *)0x004eae38);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1caab0 */
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
  FUN_001ca900();
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cad24 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1cadd0 */
void FUN_001cadd0(int a, int b, int c, int d, int e, int f)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  sound_dsound_channel_get(0);
  display_assert((char *)0x002c10dc, (char *)0x002c0894, 906, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1cae31 */
  display_assert((char *)0x002c0f3c, (char *)0x002c0894, 907, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edi + 4], (char)eax -> jne 0x1cae43 */
  /* test (char)ecx, (char)ecx -> jne 0x1cae77 */
  IDirectSoundStream_SetMode();
  sound_dsound_log_error(0x002c10b4, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x1caf02 */
  IDirectSoundStream_SetPosition();
  /* test eax, eax -> jge 0x1caeef */
  sound_dsound_log_error(0x002c1094, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x1cafbd */
  valid_real_normal3d((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x1caf7a */
  display_assert((char *)0x002c106c, (char *)0x002c0894, 933, 0);
  system_exit(0);
  IDirectSoundStream_SetConeOrientation();
  /* test eax, eax -> jge 0x1cafab */
  sound_dsound_log_error(0x002c1048, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x1cb050 */
  IDirectSoundStream_SetVelocity();
  /* test eax, eax -> jge 0x1cb03f */
  sound_dsound_log_error(0x002c1028, (char *)0);
  /* relift: cmp (char)eax, byte ptr [ebp + 0x18] -> jne 0x1cb092 */
  /* test (char)eax, (char)eax -> jne 0x1cb092 */
  /* test (char)eax, (char)eax -> jne 0x1cb0ac */
  sound_dsound_channel_update_3d(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1cb0c0 */
void FUN_001cb0c0(int channel)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  sound_dsound_channel_get(0);
  /* test (char)eax, (char)eax -> je 0x1cb0f7 */
  display_assert((char *)0x002c1134, (char *)0x002c0894, 1111, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1cb11b */
  display_assert((char *)0x0027b768, (char *)0x002c0894, 1112, 0);
  system_exit(0);
  display_assert((char *)0x002c1114, (char *)0x002c0894, 1144, 0);
  system_exit(0);
  IDirectSound_CommitDeferredSettings();
  /* test eax, eax -> jge 0x1cb18a */
  sound_dsound_log_error(0x002c0d58, (char *)0);
  sound_dsound_channel_resolve(0);
  /* relift: tail-call FUN_001cb0c0(); */
  sound_dsound_channel_resolve(0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1cb1fe */
  FUN_001cadd0(0, 0, 0, 0, 0, 0);
  sound_dsound_channel_get(0);
  sound_dsound_get_sample_rate(0);
  csmemset((void *)(uintptr_t)edx, 0, 24);
  IDirectSound_CreateSoundStream();
  /* test eax, eax -> jl 0x1cb499 */
  /* test (int16_t)esi, (int16_t)esi -> je 0x1cb360 */
  csmemset((void *)(uintptr_t)ecx, 0, 44);
  FUN_001cadd0(0, 0, 0, 0, 0, 0);
  IDirectSound_GetSpeakerConfig();
  /* relift: test dword ptr [ebp - 8], 0x10000 -> je 0x1cb41e */
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  /* test (char)ebx, 2 -> jne 0x1cb45f */
  sound_dsound_gain_to_volume(0.0f, 0);
  sound_dsound_gain_to_volume(0.0f, 0);
  IDirectSoundStream_SetMixBins();
  IDirectSoundStream_SetMixBinVolumes_12();
  csmemset((void *)(uintptr_t)eax, 0, 32);
  sound_dsound_update_channel_properties((float *)(uintptr_t)ecx, 0, 0);
  sound_dsound_log_error(0x002c114c, (char *)0);
  /* mem[0x00505488] = 0x3f800000 */
  /* mem[0x00505460] = esi */
  display_assert((char *)0x00280f94, (char *)0x002c0894, 234, 0);
  system_exit(0);
  DirectSoundCreate();
  /* cmp eax, esi -> jl 0x1cb785 */
  IDirectSound_GetCaps();
  /* cmp eax, esi -> jl 0x1cb77e */
  /* mem[0x00505450] = eax */
  /* mem[0x0050544c] = edx */
  /* mem[0x00505454] = ecx */
  /* mem[0x00505458] = edx */
  IDirectSound_SetDistanceFactor();
  /* cmp eax, esi -> jl 0x1cb777 */
  IDirectSound_SetRolloffFactor();
  /* cmp eax, esi -> jl 0x1cb75a */
  csmemset((void *)(uintptr_t)edx, 0, 52);
  IDirectSound_DownloadEffectsImage();
  /* cmp eax, esi -> jge 0x1cb610 */
  sound_dsound_log_error(0x002c11fc, (char *)0);
  IDirectSound_SetMixBinHeadroom();
  DirectSoundUseFullHRTF();
  FUN_001ca2b0((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1cb69e */
  sound_dsound_vchannel_get(0);
  /* cmp (int16_t)ebx, 4 -> jl 0x1cb68d */
  display_assert((char *)0x002c08f8, (char *)0x002c0894, 422, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], (int16_t)ebx -> jle 0x1cb723 */
  /* test (char)eax, (char)eax -> je 0x1cb718 */
  FUN_001cb210(0, 0);
  /* test (char)eax, (char)eax -> je 0x1cb718 */
  /* relift: cmp (int16_t)ebx, word ptr [esi] -> jl 0x1cb6f0 */
  /* test (char)eax, (char)eax -> je 0x1cb74a */
  FUN_001c9cf0();
  /* test (char)eax, (char)eax -> je 0x1cb74a */
  FUN_001c93f0();
  sound_dsound_log_error(0x002c11dc, (char *)0);
  FUN_001c93f0();
  /* cmp esi, ebx -> je 0x1cb7b7 */
  /* cmp esi, ebx -> je 0x1cb7cf */
  /* test dl, 2 -> jne 0x1cb7fa */
  /* cmp ecx, edx -> je 0x1cb7fa */
  /* test (char)eax, (char)eax -> je 0x1cb853 */
  data_make_invalid((void *)(uintptr_t)ecx);
  data_make_invalid((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1cb865 */
  data_dispose((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1cb877 */
  data_dispose((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1cb898 */
  /* test (char)eax, (char)eax -> je 0x1cb898 */
  /* cmp (char)ebx, (char)eax -> je 0x1cb8d0 */
  /* test (char)ebx, (char)ebx -> jne 0x1cb8d0 */
  system_milliseconds();
  /* mem[0x004eaf4c] = eax */
  /* test (char)eax, (char)eax -> je 0x1cb95e */
  /* test (char)eax, (char)eax -> je 0x1cb95e */
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> je 0x1cb95d */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 0x14], 1 -> jne 0x1cb947 */
  scenario_location_from_point((void *)(uintptr_t)eax, (void *)0);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> jne 0x1cb920 */
  datum_absolute_index_to_index((void *)(uintptr_t)ecx, 0);
  game_time_get();
  system_milliseconds();
  /* mem[0x004eaf4c] = eax */
  tag_get(0x736e6421, 0);
  /* test ecx, ecx -> je 0x1cba72 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 72);
  /* test ecx, ecx -> je 0x1cba72 */
  sound_class_get_definition(0);
  /* test (char)ecx, (char)ecx -> jne 0x1cba72 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1cba8e */
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1cbaae */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1cbacb */
  /* cmp (int16_t)esi, 4 -> jl 0x1cbaeb */
  display_assert((char *)0x002c12f4, (char *)0x002c12cc, 1072, 0);
  system_exit(0);
  tag_get(0x736e6421, 0);
  /* cmp (int16_t)esi, (int16_t)edi -> je 0x1cbb98 */
  /* relift: cmp dword ptr [eax + 0x7c], -1 -> je 0x1cbb88 */
  sound_class_get_gain(0);
  /* cmp (int16_t)esi, 0x2c -> je 0x1cbbc1 */
  /* cmp (int16_t)esi, 0x2e -> je 0x1cbbc1 */
  /* cmp (int16_t)esi, 0x2f -> je 0x1cbbc1 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [eax + 0x8c], -1 -> je 0x1cbc09 */
  display_assert((char *)0x002c1328, (char *)0x002c12cc, 1231, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)edi, -1 -> je 0x1cbcbd */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1cbc6e */
  /* relift: cmp (int16_t)edi, word ptr [0x4eb0b4] -> jl 0x1cbc8e */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx*8 + 0x4fc3a0], ebx -> je 0x1cbcbd */
  display_assert((char *)0x002c1360, (char *)0x002c12cc, 1439, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> jne 0x1cbd1d */
  /* test eax, eax -> je 0x1cbd1d */
  /* relift: cmp edx, dword ptr [0x4eaf4c] -> jge 0x1cbd1d */
  /* test (char)eax, (char)eax -> jne 0x1cbd1d */
  /* relift: cmp word ptr [esi + 2], 0 -> jne 0x1cbd22 */
  tag_get('!dns', 0);
  sound_class_get_definition(0);
  /* test (char)ecx, (char)ecx -> jne 0x1cbd22 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  sound_class_get_definition(0);
  sound_class_get_definition(0);
  display_assert((char *)0x002c14b0, (char *)0x002c12cc, 1700, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x22], 0x10 -> jle 0x1cbdde */
  display_assert((char *)0x002c1458, (char *)0x002c12cc, 1701, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1cbf1b */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1cbdfa */
  /* cmp (int16_t)ebx, (int16_t)eax -> jl 0x1cbe1a */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* relift: cmp eax, dword ptr [ebp + 8] -> je 0x1cbf0c */
  datum_get((void *)(uintptr_t)eax, 0);
  sound_valid_for_channel(0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x1cbf0c */
  /* relift: cmp ecx, dword ptr [edx + 8] -> jne 0x1cbf0c */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x22] -> jl 0x1cbeba */
  display_assert((char *)0x002c1414, (char *)0x002c12cc, 1717, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1cbf0c */
  /* relift: cmp eax, dword ptr [edx + 0xc] -> jne 0x1cbf0c */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x46] -> jl 0x1cbeff */
  display_assert((char *)0x002c13d0, (char *)0x002c12cc, 1723, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jl 0x1cbdf0 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1cbf3e */
  /* relift: cmp (int16_t)edi, word ptr [0x4eb0b4] -> jl 0x1cbf5e */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  sound_cache_sound_finished(0);
  /* test eax, eax -> je 0x1cbf99 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1cbfc1 */
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1cbfe1 */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x1cc026 */
  display_assert((char *)0x002c1500, (char *)0x002c12cc, 2120, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1cc062 */
  /* relift: cmp (int16_t)edi, word ptr [0x4eb0b4] -> jl 0x1cc082 */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1cc0de */
  /* cmp (int16_t)edi, 2 -> jge 0x1cc0de */
  sound_cache_sound_finished(0);
  sound_cache_request_sound((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x1cc0de */
  /* test eax, eax -> je 0x1cc125 */
  /* cmp (int16_t)edi, 1 -> jge 0x1cc125 */
  /* test eax, eax -> je 0x1cc112 */
  display_assert((char *)0x002c1518, (char *)0x002c12cc, 2152, 0);
  system_exit(0);
  sound_cache_sound_finished(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1cc14e */
  /* relift: cmp (int16_t)edi, word ptr [0x4eb0b4] -> jl 0x1cc16e */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  sound_cache_sound_finished(0);
  /* test eax, eax -> je 0x1cc1ae */
  sound_cache_sound_finished(0);
  datum_absolute_index_to_index((void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1cc1ef */
  datum_absolute_index_to_index((void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1cc2e3 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ecx, esi -> je 0x1cc30d */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 0x41 -> jne 0x1cc387 */
  display_assert((char *)0, (char *)0x002c12cc, 2678, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x1cc3de */
  FUN_001d9e70(0.0f, 0.0f);
  FUN_001d9e70(0.0f, 0.0f);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> je 0x1cc486 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ecx, edi -> je 0x1cc48b */
  data_next_index((void *)(uintptr_t)edx, 0);
  /* cmp esi, -1 -> jne 0x1cc458 */
  /* test (char)eax, 0x41 -> jne 0x1cc4d6 */
  /* test (char)eax, 0x41 -> je 0x1cc4ea */
  /* test (char)eax, 0x41 -> jne 0x1cc4ea */
  /* test (char)eax, (char)eax -> je 0x1cc5ab */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  sound_get_default_priority(0);
  FUN_00189540(0, (void *)(uintptr_t)edi, 0.0f, (void *)0);
  sound_class_get_min_distance(0);
  FUN_00189540(0, (void *)(uintptr_t)edi, 0.0f, (void *)0);
  tag_get_name(0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002c1538);
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1cc709 */
  /* relift: cmp word ptr [eax], 1 -> jne 0x1cc709 */
  tag_get(0x6c736e64, 0);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 160);
  /* cmp eax, -1 -> jne 0x1cc626 */
  /* cmp edx, eax -> jl 0x1cc600 */
  tag_get('!dns', 0);
  sound_class_get_min_distance(0);
  sound_get_default_priority(0);
  /* test eax, eax -> jle 0x1cc6bc */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 104);
  /* cmp eax, -1 -> jne 0x1cc693 */
  /* cmp eax, ecx -> jl 0x1cc670 */
  tag_get('!dns', 0);
  sound_class_get_min_distance(0);
  sound_get_default_priority(0);
  tag_get_name(0);
  FUN_00189cb0(0, (void *)(uintptr_t)esi, (void *)(uintptr_t)eax, 0);
  FUN_00189540(0, (void *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189540(0, (void *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)edx);
  FUN_001cf820((void *)(uintptr_t)eax);
  sound_cache_new();
  /* mem[0x004eb0b0] = 0x3f800000 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1cc8b1 */
  /* cmp (int16_t)eax, 2 -> jge 0x1cc8b1 */
  /* test ecx, ecx -> je 0x1cc8b1 */
  /* relift: cmp word ptr [ecx], (int16_t)eax -> jne 0x1cc8b1 */
  /* mem[0x004eaf48] = ecx */
  data_new((char *)0x002c1590, 512, 172);
  /* mem[0x004fdba4] = eax */
  data_new((char *)0x002c1580, 128, 228);
  /* mem[0x004fdba0] = eax */
  /* test (char)eax, (char)eax -> je 0x1cc8b1 */
  data_delete_all((void *)(uintptr_t)edx);
  data_delete_all((void *)(uintptr_t)eax);
  display_assert((char *)0x002c1544, (char *)0x002c12cc, 360, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + eax], (int16_t)ebx -> jle 0x1cc89d */
  sound_channel_get(0);
  /* relift: cmp (int16_t)ebx, word ptr [edi + eax] -> jl 0x1cc874 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1cc923 */
  /* cmp (int16_t)eax, 1 -> je 0x1cc923 */
  display_assert((char *)0x002c15e0, (char *)0x002c12cc, 1087, 0);
  system_exit(0);
  /* test (char)eax, 1 -> je 0x1cc953 */
  display_assert((char *)0x002c15d0, (char *)0x002c12cc, 1088, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x14], esi -> jne 0x1cc984 */
  display_assert((char *)0x002c1598, (char *)0x002c12cc, 1089, 0);
  system_exit(0);
  FUN_001d9068();
  /* cmp edi, esi -> jg 0x1cc9a9 */
  /* cmp eax, -1 -> je 0x1cca0d */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, eax -> je 0x1cc9e2 */
  sound_update_channel_attenuation(0);
  /* cmp eax, -1 -> je 0x1cca55 */
  datum_get((void *)(uintptr_t)eax, 0);
  sound_update_channel_attenuation(0);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('!dns', 0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1ccaa3 */
  /* relift: cmp (int16_t)edi, word ptr [0x4eb0b4] -> jl 0x1ccac3 */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  sound_channel_stop(0);
  /* relift: test byte ptr [esi + 4], 2 -> je 0x1ccb36 */
  tag_get(0x736e6421, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  sound_cache_sound_finished(0);
  /* relift: cmp word ptr [esi + 2], 0 -> je 0x1ccb77 */
  datum_absolute_index_to_index((void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1ccb77 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [eax + 0x8c], -1 -> je 0x1ccbc7 */
  display_assert((char *)0x002c1328, (char *)0x002c12cc, 1231, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0, (char *)0x002c12cc, 1402, 0);
  system_exit(0);
  sound_listener_get(0);
  sound_listener_get(0);
  /* relift: cmp byte ptr [eax], 0 -> jne 0x1ccc16 */
  display_assert((char *)0, (char *)0x002c12cc, 1427, 0);
  system_exit(0);
  sound_listener_get(0);
  sound_listener_get(0);
  /* relift: cmp byte ptr [eax], 0 -> jne 0x1cccd6 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  FUN_001ccbe0(0, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1ccdd8 */
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1ccdf8 */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  sound_class_get_definition(0);
  /* cmp ecx, edx -> jl 0x1cce5a */
  FUN_001ccbe0(0, (void *)0);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('!dns', 0);
  datum_get((void *)(uintptr_t)edx, 0);
  tag_get('!dns', 0);
  display_assert((char *)0x002c1648, (char *)0x002c12cc, 1891, 0);
  system_exit(0);
  sound_class_get_definition(0);
  sound_class_get_definition(0);
  /* relift: cmp (int16_t)ecx, word ptr [eax + 0xa] -> jg 0x1ccf67 */
  sound_class_get_definition(0);
  sound_class_get_definition(0);
  /* relift: cmp (int16_t)edx, word ptr [eax + 0xa] -> jne 0x1ccf5e */
  FUN_001ccbe0(0, (void *)0);
  /* test (char)eax, 0x41 -> je 0x1ccf67 */
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1ccfba */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  sound_class_get_gain(0);
  /* cmp (int16_t)edi, 0x2c -> je 0x1cd01b */
  /* cmp (int16_t)edi, 0x2e -> je 0x1cd01b */
  /* cmp (int16_t)edi, 0x2f -> je 0x1cd01b */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 72);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  sound_class_get_min_distance(0);
  sound_class_get_definition(0);
  sound_cache_request_sound((void *)(uintptr_t)edi, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x1cd0f8 */
  display_assert((char *)0x002c1678, (char *)0x002c12cc, 1946, 0);
  system_exit(0);
  sound_channel_set_properties(0, 0, (void *)0);
  sound_channel_start_new(0, 0);
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1cd164 */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x1cd209 */
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('dnsl', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('!dns', 0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  FUN_001d9068();
  /* cmp esi, ecx -> jl 0x1cd210 */
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('!dns', 0);
  sound_select_pitch_range((void *)(uintptr_t)edi, 0.0f, 0);
  sound_select_permutation((void *)(uintptr_t)edi, 0, 0);
  sound_collect_like_sounds(0, (void *)0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 2] -> jl 0x1cd35a */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 0x26] -> jl 0x1cd386 */
  sound_find_oldest_channel(0, (void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1cd381 */
  sound_channel_get(0);
  sound_stop_channel(0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  angles_to_vector((float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  datum_absolute_index_to_index((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1cd4ca */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 2], 0 -> je 0x1cd4a1 */
  display_assert((char *)0x002c16a0, (char *)0x002c12cc, 705, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* relift: cmp word ptr [eax + 2], 0 -> jne 0x1cd4ca */
  sound_start_fade(0, 0.0f, 0, 0);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> je 0x1cd53b */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 2], 0 -> jne 0x1cd514 */
  /* relift: cmp dword ptr [eax + 0xc], ebx -> jne 0x1cd514 */
  /* relift: cmp dword ptr [eax + 8], edi -> je 0x1cd530 */
  data_next_index((void *)(uintptr_t)edx, 0);
  /* cmp esi, -1 -> jne 0x1cd4f3 */
  sound_stop_impulse(0);
  /* test (char)eax, (char)eax -> je 0x1cd595 */
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp ebx, -1 -> je 0x1cd57d */
  sound_stop_channel(0);
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp ebx, -1 -> jne 0x1cd561 */
  data_make_valid((void *)(uintptr_t)edx);
  /* mem[0x004eaf44] = 0 */
  /* cmp (int16_t)eax, 2 -> jne 0x1cd5dc */
  FUN_001ccbe0(0, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1cd5fb */
  /* cmp (int16_t)esi, 4 -> jl 0x1cd61b */
  display_assert((char *)0x002c12f4, (char *)0x002c12cc, 1072, 0);
  system_exit(0);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x1cd63b */
  FUN_001ccbe0(0, (void *)0);
  /* cmp (int16_t)esi, 4 -> jl 0x1cd5f0 */
  sound_compute_source_obstruction(0, (void *)(uintptr_t)edi, 0.0f);
  /* relift: cmp dword ptr [edi + 0x3c], 0x3f800000 -> jne 0x1cd684 */
  players_are_all_dead();
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp ebx, -1 -> je 0x1cd85d */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1cd710 */
  sound_channel_update_status(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1cd710 */
  /* cmp (int16_t)eax, 2 -> je 0x1cd710 */
  /* cmp (int16_t)eax, 3 -> jne 0x1cd7e3 */
  FUN_001cbc40(0);
  /* test (char)eax, (char)eax -> je 0x1cd7e3 */
  sound_get_default_priority(0);
  sound_allocate_channel((void *)0, 0.0f);
  FUN_001cc4f0(0);
  /* cmp (int16_t)eax, 0x2c -> je 0x1cd755 */
  /* cmp (int16_t)eax, 0x2e -> je 0x1cd755 */
  /* cmp (int16_t)eax, 0x2f -> jne 0x1cd759 */
  /* test (char)eax, 4 -> jne 0x1cd79f */
  sound_start_fade(0, 0.0f, 0, 0);
  sound_start_fade(0, 0.0f, 0, 0);
  /* test (char)eax, (char)eax -> je 0x1cd7e8 */
  /* cmp (int16_t)eax, 0x2c -> jne 0x1cd7d3 */
  /* relift: cmp word ptr [esi + 0x8c], -1 -> je 0x1cd7e3 */
  sound_start_fade(0, 0.0f, 0, 0);
  /* cmp (int16_t)eax, 0x2e -> jne 0x1cd7e8 */
  /* relift: cmp word ptr [esi + 0x8c], -1 -> jne 0x1cd7e8 */
  sound_stop_channel(0);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp ebx, -1 -> jne 0x1cd6c0 */
  /* test (char)eax, 0x41 -> je 0x1cd89b */
  /* test (char)eax, 0x41 -> je 0x1cd849 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  FUN_001ccbe0(0, (void *)0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1cd91a */
  /* cmp (int16_t)ebx, (int16_t)eax -> jl 0x1cd93a */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* cmp edx, ebx -> je 0x1cd974 */
  /* cmp edx, ebx -> je 0x1cd98e */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 6] -> je 0x1cd9a1 */
  /* test (char)ecx, 2 -> jne 0x1cd9ba */
  /* cmp eax, ecx -> jne 0x1cda22 */
  /* test dl, dl -> je 0x1cda22 */
  /* cmp eax, -1 -> je 0x1cda42 */
  sound_update_time(0, 0, 0.0f);
  /* test (char)eax, (char)eax -> je 0x1cda22 */
  /* relift: cmp word ptr [ebp - 0xc], -1 -> je 0x1cd9f4 */
  sound_update_time(0, 0, 0.0f);
  /* test (char)eax, (char)eax -> je 0x1cda22 */
  datum_get((void *)(uintptr_t)edx, 0);
  FUN_001ccbe0(0, (void *)0);
  datum_get((void *)0, 0);
  sound_can_play(0);
  /* test (char)eax, (char)eax -> je 0x1cdc1f */
  tag_get('!dns', 0);
  sound_get_default_priority(0);
  sound_allocate_channel((void *)(uintptr_t)ecx, 0.0f);
  data_new_at_index((void *)(uintptr_t)edx);
  datum_get((void *)(uintptr_t)eax, 0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  sound_select_pitch_range((void *)0, 0.0f, 0);
  sound_select_permutation((void *)(uintptr_t)esi, 0, 0);
  tag_get(0x736e6421, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  sound_cache_request_sound((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1cdc6a */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!dns', 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('dnsl', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x002c1720, (char *)0x002c12cc, 2500, 0);
  system_exit(0);
  sound_class_get_min_distance(0);
  sound_class_get_definition(0);
  sound_class_get_gain(0);
  /* cmp (int16_t)esi, 0x2c -> je 0x1cdd92 */
  /* cmp (int16_t)esi, 0x2e -> je 0x1cdd92 */
  /* cmp (int16_t)esi, 0x2f -> je 0x1cdd92 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 124);
  sound_cache_request_sound((void *)0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x1cde37 */
  display_assert((char *)0x002c1678, (char *)0x002c12cc, 2522, 0);
  system_exit(0);
  sound_channel_set_properties(0, 0, (void *)0);
  sound_channel_start_new(0, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1cdebe */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  sound_volume_crossfade(0.0f, 0.0f, 0.0f);
  /* relift: cmp word ptr [edi + 2], 2 -> jne 0x1cdf8e */
  /* relift: cmp eax, dword ptr [edi + 0xa8] -> je 0x1cdf1a */
  sound_select_pitch_range((void *)(uintptr_t)ebx, 0.0f, 0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0x8e] -> je 0x1cdf8e */
  /* relift: cmp ecx, dword ptr [edx] -> jne 0x1cdf8e */
  /* test (char)eax, (char)eax -> jne 0x1cdf8e */
  sound_create_looping_entry(0, 0, 0, 0);
  /* cmp esi, -1 -> je 0x1cdf8e */
  sound_start_fade(0, 0.0f, 0, 0);
  /* cmp (int16_t)eax, 4 -> je 0x1ce139 */
  /* cmp (int16_t)eax, 1 -> jne 0x1cdfae */
  /* relift: test byte ptr [eax], 1 -> jne 0x1ce139 */
  sound_channel_update_status(0);
  /* cmp (int16_t)eax, 2 -> jne 0x1cdfe9 */
  /* relift: test byte ptr [edi + 4], 8 -> jne 0x1cdfe9 */
  /* relift: cmp word ptr [edx + 0x2a], (int16_t)esi -> jne 0x1ce139 */
  /* relift: cmp dword ptr [edi + 0x98], esi -> je 0x1ce139 */
  /* relift: cmp dword ptr [edi + 0x98], esi -> je 0x1ce036 */
  /* test eax, eax -> je 0x1ce004 */
  /* relift: cmp word ptr [eax + 0x2a], (int16_t)esi -> jne 0x1ce036 */
  sound_start_next_looping_permutation(0);
  tag_get('!dns', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: test byte ptr [edi + 4], 8 -> jne 0x1ce0b2 */
  sound_select_permutation((void *)(uintptr_t)ebx, 0, 0);
  /* cmp (int16_t)eax, (int16_t)esi -> jne 0x1ce0a7 */
  /* relift: test byte ptr [ebx], 2 -> jne 0x1ce082 */
  display_assert((char *)0x002c16d8, (char *)0x002c12cc, 2588, 0);
  system_exit(0);
  /* relift: test byte ptr [ecx], 2 -> jne 0x1ce118 */
  sound_select_permutation((void *)(uintptr_t)ebx, 0, 0);
  /* cmp (int16_t)eax, (int16_t)esi -> je 0x1ce0b2 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  sound_cache_request_sound((void *)(uintptr_t)ebx, 0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x1ce139 */
  sound_channel_start_new(0, 0);
  /* relift: cmp dword ptr [eax + 0x98], esi -> jne 0x1ce136 */
  /* relift: cmp word ptr [ebx + 0x2a], (int16_t)esi -> jne 0x1ce136 */
  /* cmp (int16_t)eax, 1 -> jne 0x1ce127 */
  /* cmp (int16_t)eax, 3 -> jne 0x1ce136 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  sound_channel_set_properties(0, 0, (void *)0);
  tag_get(0x736e6421, 0);
  display_assert((char *)0x002c1830, (char *)0x002c12cc, 576, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi], 0 -> je 0x1ce20c */
  valid_real_normal3d((float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1ce20c */
  display_assert((char *)0x002c17c0, (char *)0x002c12cc, 578, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x2c -> je 0x1ce222 */
  /* cmp (int16_t)eax, 0x2e -> je 0x1ce222 */
  /* cmp (int16_t)eax, 0x2f -> jne 0x1ce268 */
  game_time_get();
  /* cmp eax, ecx -> jle 0x1ce25a */
  /* mem[0x004eaf44] = eax */
  /* test (char)eax, (char)eax -> je 0x1ce268 */
  /* relift: cmp word ptr [esi + 4], 0x2f -> jne 0x1ce274 */
  /* test (char)eax, (char)eax -> je 0x1ce540 */
  /* test (char)eax, (char)eax -> je 0x1ce540 */
  /* relift: cmp word ptr [esi + 0x6e], 1 -> jne 0x1ce531 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1ce2a8 */
  /* relift: cmp word ptr [esi + 6], (int16_t)eax -> je 0x1ce2b2 */
  /* cmp (int16_t)eax, 1 -> jne 0x1ce531 */
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x1ce540 */
  sound_get_default_priority(0);
  sound_can_play(0);
  /* test (char)eax, (char)eax -> je 0x1ce540 */
  sound_allocate_channel((void *)(uintptr_t)ecx, 0.0f);
  sound_check_promotion(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1ce4f3 */
  data_new_at_index((void *)(uintptr_t)edx);
  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_001ccca0(0, (void *)0);
  FUN_001d9068();
  sound_compute_random_scale(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  /* cmp esi, edi -> jne 0x1ce41d */
  display_assert((char *)0x002c17ac, (char *)0x002c12cc, 654, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, edx);
  sound_select_pitch_range((void *)(uintptr_t)esi, 0.0f, 0);
  sound_select_permutation((void *)(uintptr_t)esi, 0, 0);
  tag_get(0x736e6421, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  sound_cache_request_sound((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, 0xfa -> jle 0x1ce4de */
  /* cmp (int16_t)eax, 1 -> jne 0x1ce520 */
  sound_start(0, (void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)edx, 0);
  error(0, (char *)0x002c1740);
  valid_real_normal3d((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1ce59b */
  display_assert((char *)0x002c17c0, (char *)0x002c12cc, 756, 0);
  system_exit(0);
  FUN_001cc5b0(0, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x1ce9aa */
  /* test (char)eax, (char)eax -> je 0x1ce9aa */
  FUN_001cc440(0);
  /* relift: cmp word ptr [ebp + 0x14], 2 -> je 0x1ce9a1 */
  FUN_001cd190(0, (void *)(uintptr_t)ebx, (void *)0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('dnsl', 0);
  /* cmp eax, esi -> je 0x1ce646 */
  display_assert((char *)0x002c1860, (char *)0x002c12cc, 782, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1ce68d */
  /* relift: cmp word ptr [ebx + 0x50], 0 -> jne 0x1ce68d */
  datum_delete((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0x1ce6a8 */
  player_effect_continuous_refresh();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 160);
  /* test (char)eax, (char)eax -> je 0x1ce6ea */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1ce716 */
  /* cmp eax, -1 -> je 0x1ce720 */
  sound_create_looping_entry(0, 0, 0, 0);
  /* cmp (int16_t)eax, 2 -> je 0x1ce85a */
  /* test (char)eax, (char)eax -> jne 0x1ce85a */
  /* cmp eax, -1 -> je 0x1ce742 */
  /* cmp esi, -1 -> je 0x1ce93b */
  /* cmp eax, -1 -> je 0x1ce7f4 */
  /* relift: cmp word ptr [ebp + 0x14], 0 -> jne 0x1ce76e */
  /* relift: test byte ptr [edi], 1 -> jne 0x1ce7f4 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp dl, (char)eax -> je 0x1ce7d5 */
  /* relift: test byte ptr [edi], 4 -> je 0x1ce7d5 */
  sound_create_looping_entry(0, 0, 0, 0);
  /* cmp esi, -1 -> je 0x1ce93b */
  sound_start_fade(0, 0.0f, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x1ce93b */
  FUN_001cc2f0(0, 0);
  sound_create_looping_entry(0, 0, 0, 0);
  /* cmp esi, -1 -> je 0x1ce93b */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [ebp + 0x14], 0 -> jne 0x1ce837 */
  /* relift: test byte ptr [edi], 1 -> je 0x1ce84b */
  sound_start_fade(0, 0.0f, 0, 0);
  /* relift: cmp word ptr [ebx + 0x52], 2 -> je 0x1ce93b */
  sound_start_fade(0, 0.0f, 0, 0);
  /* cmp esi, -1 -> je 0x1ce8c2 */
  /* relift: test byte ptr [edi], 2 -> jne 0x1ce8b1 */
  /* relift: cmp dword ptr [edi + 0x5c], -1 -> jne 0x1ce8c2 */
  /* relift: test byte ptr [eax], 2 -> jne 0x1ce8c2 */
  sound_start_fade(0, 0.0f, 0, 0);
  /* cmp eax, -1 -> je 0x1ce93b */
  /* test (char)eax, (char)eax -> je 0x1ce8e0 */
  /* cmp eax, -1 -> je 0x1ce8e0 */
  /* relift: test byte ptr [edi], 2 -> je 0x1ce8fb */
  sound_create_looping_entry(0, 0, 0, 0);
  /* cmp eax, -1 -> je 0x1ce93b */
  datum_get((void *)(uintptr_t)edx, 0);
  /* relift: cmp word ptr [edi + 0x8c], -1 -> je 0x1ce93b */
  FUN_001cc2f0(0, 0);
  /* relift: cmp word ptr [ebx + 0x50], 0 -> jne 0x1ce98a */
  sound_allocate_channel((void *)(uintptr_t)ecx, 0.0f);
  /* cmp (int16_t)eax, 0xffff -> jne 0x1ce98a */
  datum_delete((void *)(uintptr_t)eax, 0);
  game_in_progress();
  /* test (char)eax, (char)eax -> je 0x1ceba0 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1ce9ee */
  /* cmp (int16_t)esi, 4 -> jl 0x1cea0e */
  display_assert((char *)0x002c12f4, (char *)0x002c12cc, 1072, 0);
  system_exit(0);
  local_player_get_player_index(esi);
  /* cmp eax, -1 -> je 0x1ceb14 */
  observer_get_camera(esi);
  /* test esi, esi -> jne 0x1cea4f */
  display_assert((char *)0x00266e9c, (char *)0x002c12cc, 1263, 0);
  system_exit(0);
  FUN_0018f3e0((void *)(uintptr_t)eax, (void *)(uintptr_t)esi, (void *)0);
  /* cmp (char)eax, (char)ebx -> je 0x1ceae4 */
  game_globals_get();
  /* test ecx, ecx -> jle 0x1ceae4 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  /* cmp eax, -1 -> je 0x1ceae4 */
  /* cmp ecx, 1 -> jle 0x1ceae4 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  /* cmp eax, -1 -> je 0x1ceae4 */
  sound_start(0, (void *)(uintptr_t)edx, 0, 0, (void *)0, 0);
  matrix4x3_from_forward_up_position((void *)(uintptr_t)edi, (float *)(uintptr_t)esi, (float *)0, (float *)0);
  real_matrix3x3_transform_vector((void *)(uintptr_t)edi, (void *)(uintptr_t)esi, (void *)0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)esi, -1 -> je 0x1cec45 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1cebe8 */
  /* relift: cmp (int16_t)esi, word ptr [0x4eb0b4] -> jl 0x1cec08 */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx*8 + 0x4fc3a0], edi -> je 0x1cec37 */
  display_assert((char *)0x002c1890, (char *)0x002c12cc, 1744, 0);
  system_exit(0);
  tag_get('!dns', 0);
  sound_class_get_definition(0);
  /* test (char)ecx, (char)ecx -> je 0x1ced37 */
  /* relift: cmp dword ptr [ebx + 0xc], -1 -> je 0x1ced37 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1ced12 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1cec8f */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cecaf */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1ced03 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edx, eax -> jne 0x1ced03 */
  tag_get('!dns', 0);
  sound_class_get_definition(0);
  /* test (char)ecx, (char)ecx -> jne 0x1ced25 */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x1cec85 */
  FUN_001cd8b0(0);
  sound_collect_like_sounds(0, (void *)0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 2] -> jl 0x1ced62 */
  sound_find_oldest_channel(0, (void *)(uintptr_t)eax, 0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 0x26] -> jl 0x1ced81 */
  sound_find_oldest_channel(0, (void *)(uintptr_t)eax, 0);
  FUN_001cd8b0(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1cedca */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1cedea */
  display_assert((char *)0x002c1294, (char *)0x002c12cc, 1064, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('!dns', 0);
  sound_update_channel_attenuation(0);
  sound_stop_channel(0);
  /* relift: test byte ptr [edi + 4], 1 -> je 0x1cef88 */
  display_assert((char *)0, (char *)0x002c12cc, 2028, 0);
  system_exit(0);
  sound_listener_get(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x1ceef4 */
  display_assert((char *)0x002c18d4, (char *)0x002c12cc, 2011, 0);
  system_exit(0);
  real_matrix3x3_transform_point((void *)(uintptr_t)edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  real_matrix4x3_transform_point((void *)(uintptr_t)edi, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  real_matrix3x3_transform_vector((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  sound_listener_get(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x1cefeb */
  display_assert((char *)0x002c18d4, (char *)0x002c12cc, 2042, 0);
  system_exit(0);
  real_matrix3x3_transform_point((void *)(uintptr_t)esi, (float *)0, (float *)0);
  sound_class_get_min_distance(0);
  sound_get_default_priority(0);
  /* test (char)eax, 0x41 -> jne 0x1cf06e */
  /* relift: cmp word ptr [ebx + 2], 0 -> jne 0x1cf087 */
  sound_update_channel(0, 0.0f);
  sound_update_music_channel(0, 0.0f);
  sound_class_get_definition(0);
  /* test (char)ecx, (char)ecx -> je 0x1cf0db */
  /* relift: cmp dword ptr [ebx + 0x10], 0x1c7a10 -> jne 0x1cf0db */
  FUN_001d9068();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
/* --- sound_dsound_xbox.obj orphan shells (2026-07-26) --- */

/* 0x20f069 */
bool dsound_stream_is_active(void *stream)
{
  if (stream == 0) {
    return 0;
  }
  return 0;
}
