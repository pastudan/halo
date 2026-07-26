IMPL = r"""/* --- sound_manager.obj batch2 drafts (2026-07-25) --- */

static float sound_source_distance_sq(void *source)
{
  float *p = (float *)((char *)source + 0xc);
  return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
}

static float sound_source_distance(void *source)
{
  return xbox_sqrtf(sound_source_distance_sq(source));
}

static float sound_listener_distance_sq(int channel_index, void *source)
{
  void *listener = sound_listener_get((short)channel_index);
  float *lp = (float *)((char *)listener + 0x2c);
  float *sp = (float *)((char *)source + 0xc);
  float dx = lp[0] - sp[0];
  float dy = lp[1] - sp[1];
  float dz = lp[2] - sp[2];
  return dx * dx + dy * dy + dz * dz;
}

static float sound_listener_distance(int channel_index, void *source)
{
  return xbox_sqrtf(sound_listener_distance_sq(channel_index, source));
}

void FUN_001be1b0(int cache_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  if (entry[4] != 0 || entry[5] != 0) {
    char *perm = *(char **)(entry + 8);
    int perm_index = *(int *)(perm + 0x3c);
    const char *name = tag_get_name(perm_index);
    csprintf((char *)0x5ab100, (char *)0x2b93e0, name);
    display_assert((char *)0x2b9288, "c:\\halo\\SOURCE\\cache\\xbox_sound_cache.c",
                   0x141, 1);
    system_exit(-1);
  }
  {
    char *perm = *(char **)(entry + 8);
    if (*(int *)(perm + 0x2c) != cache_handle) {
      display_assert((char *)0x2b9288, "c:\\halo\\SOURCE\\cache\\xbox_sound_cache.c",
                     0x144, 1);
      system_exit(-1);
    }
    *(int *)(perm + 0x2c) = -1;
    *(int *)(perm + 0x30) = 0;
  }
  datum_delete(*(data_t **)0x4e9368, cache_handle);
}

void *FUN_001be270(int cache_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  char *perm = *(char **)(entry + 8);
  const char *name = tag_get_name(*(int *)(perm + 0x3c));
  crt_sprintf((char *)0x4e9268, (char *)0x2b9424, name);
  return (void *)0x4e9268;
}

void FUN_001be2b0(void *perm_entry /* @<esi> */)
{
  char *perm = (char *)perm_entry;
  int block_index = FUN_0011de10(*(void **)0x4e9370, *(unsigned int *)(perm + 0x40));
  if (block_index == -1)
    return;
  {
    int addr = lruv_block_get_address(*(void **)0x4e9370, block_index);
    int cache_handle = data_new_datum(*(data_t **)0x4e9368, block_index);
    char *entry = (char *)datum_get(*(data_t **)0x4e9368, block_index);
    if (cache_handle != block_index) {
      display_assert((char *)0x2b9288, "c:\\halo\\SOURCE\\cache\\xbox_sound_cache.c",
                     0x170, 1);
      system_exit(-1);
    }
    *(int *)(perm + 0x2c) = block_index;
    *(int *)(perm + 0x30) = addr + *(int *)0x4e936c;
    *(char **)(entry + 8) = perm;
    cache_file_read(*(int *)(perm + 0x40), *(int *)(perm + 0x34),
                    *(unsigned int *)(perm + 0x48), (int)(entry + 2), perm, 0);
  }
}

void FUN_001c7b40(void)
{
  void *scenario = scenario_get();
  int cluster_count = *(int *)((char *)scenario + 0x134);
  int table_bytes = (((cluster_count + 0x1f) >> 5) << 2);
  csmemset((void *)0x5054a0, 0, table_bytes);
  {
    short player_index;
    for (player_index = 0; player_index < 4; player_index++) {
      int pi = local_player_get_player_index(player_index);
      if (pi == -1)
        continue;
      void *camera = observer_get_camera((unsigned short)player_index);
      if (*(int16_t *)((char *)camera + 0x10) == -1)
        continue;
      {
        int cluster;
        for (cluster = 0; cluster < cluster_count; cluster++) {
          uint8_t enc = structure_bsp_cluster_sound_encoding(scenario,
                                                             *(int16_t *)((char *)camera + 0x10),
                                                             (int16_t)cluster);
          int enc_val = (int)(enc & 0x7f);
          float scaled = (float)enc_val * *(float *)0x256148;
          if (scaled <= *(float *)0x2642a0) {
            int word_index = cluster >> 5;
            int bit = 1 << (cluster & 0x1f);
            *(uint32_t *)(0x5054a0 + word_index * 4) |= (uint32_t)bit;
          }
        }
      }
    }
  }
}

int FUN_001c8700(void *state, int sample_count, int16_t *out, void *track,
                 void *bitstream)
{
  char *st = (char *)state;
  int bits_left = *(int *)st;
  char *in_ptr = st + 8;
  int samples = sample_count;
  if (samples == 0)
    return bits_left + bits_left;
  if (bitstream) {
    char *bs = (char *)bitstream;
    if (*(int *)bs == 0) {
      *(int *)bs = bits_left;
      *(int16_t *)(bs + 8) = *(int16_t *)(st + 4);
      *(int16_t *)(bs + 0xa) = 0;
    }
    {
      int16_t value = *(int16_t *)(bs + 8);
      int consumed = *(int *)(bs + 4);
      int avail = *(int *)bs - consumed;
      char *src = in_ptr + (consumed >> 1);
      int16_t step_index = *(int16_t *)(bs + 0xa);
      char use_high_nibble = (char)(~(char)consumed & 1);
      int out_count = sample_count;
      int16_t *dst = out;
      void *tbl_hi = (void *)0x2bc710;
      void *tbl_lo = (void *)0x2bc6d0;
      while (out_count > 0 && avail > 0 && track) {
        uint8_t nibble_byte = *(uint8_t *)src;
        int table_index = (int)step_index;
        int delta = *(int *)(4 * table_index + (int)tbl_hi);
        delta >>= 3;
        if (use_high_nibble)
          nibble_byte >>= 4;
        {
          uint8_t nibble = nibble_byte & 0xf;
          int bit = 4;
          while (bit) {
            if (nibble & bit)
              delta += *(int *)(4 * table_index + (int)tbl_hi);
            bit >>= 1;
            delta >>= 1;
          }
          if (nibble & 8)
            delta = -delta;
        }
        value = (int16_t)(value + (int16_t)delta);
        if (value < (int16_t)0x8000)
          value = (int16_t)0x8000;
        else if (value > 0x7fff)
          value = 0x7fff;
        {
          int step = *(int *)(4 * (int)nibble + (int)tbl_lo);
          step_index = (int16_t)(step_index + step);
          if (step_index < 0)
            step_index = 0;
          else if (step_index > 0x58)
            step_index = 0x58;
        }
        *dst = value;
        if (use_high_nibble) {
          src++;
          avail--;
        }
        use_high_nibble = (char)!use_high_nibble;
        dst++;
        out_count--;
        consumed++;
        if (track)
          (*(int *)(bs + 4))++;
      }
      if (bitstream) {
        *(int16_t *)(bs + 8) = value;
        *(int16_t *)(bs + 0xa) = step_index;
      }
      bits_left = *(int *)bs - *(int *)(bs + 4);
    }
  }
  return bits_left + bits_left;
}

void sound_is_active(int sound_index)
{
  FUN_00118be0((void *)0x32ecf4, (void *)(intptr_t)sound_index, 1);
}

void FUN_001c8ee0(void *pitch_range)
{
  char *range = (char *)pitch_range;
  int16_t played = *(int16_t *)(range + 0x2c);
  uint32_t mask = (1u << (played & 0x1f)) - 1u;
  if ((~*(uint32_t *)(range + 0x34) & mask) == 0) {
    *(uint32_t *)(range + 0x34) = 0;
    if (played > 1) {
      uint8_t bit = *(uint8_t *)(range + 0x38);
      *(uint32_t *)(range + 0x34) = 1u << bit;
    }
  }
}

void FUN_001cb1a0(int channel_index, int param)
{
  short resolved = sound_dsound_channel_resolve(channel_index);
  if (resolved != -1)
    ((void (*)(int))0x1cb0c0)(resolved);
}

void FUN_001cb1d0(int channel_index, int a, int b, int c, int d, int e)
{
  short resolved = sound_dsound_channel_resolve(channel_index);
  if (resolved != -1)
    ((void (*)(int, int, int, int, int))0x1cadd0)(resolved, a, b, c, d);
}

char FUN_001cb210(short channel_index /* @<ax> */, unsigned char flags /* @<bl> */)
{
  char desc[0x80];
  char buf[0x34];
  char stereo_buf[0x2c];
  void *channel = sound_dsound_channel_get(channel_index);
  csmemset(desc, 0, 0x80);
  *(uint16_t *)((char *)channel + 0x38) = (uint16_t)flags;
  *(int16_t *)((char *)channel + 2) = -1;
  ((char *)channel)[6] = 0;
  *(int *)((char *)channel + 0x68) = 0;
  *(int *)((char *)channel + 0x6c) = 0;
  {
    int block_align;
    int16_t format;
    int16_t channels;
    int16_t bits;
    int16_t rate_idx;
    if (flags & 8) {
      block_align = *(int *)0x2bcc1c * 4;
      format = 1;
      channels = 2;
      rate_idx = 0x10;
      bits = 4;
    } else {
      int codec = ((flags & 2) != 0) ? 2 : 1;
      format = 0x69;
      channels = 4;
      rate_idx = (int16_t)codec;
      bits = 2;
      block_align = sound_dsound_get_sample_rate((flags >> 2) & 1);
      block_align = (block_align >> 6) * (int)rate_idx * 4;
    }
    csmemset(buf, 0, 0x18);
    *(int *)(buf + 0x10) = block_align;
    *(int *)(buf + 0x14) = 0;
    *(int *)(buf + 0) = (int)(intptr_t)(buf + 0x1c);
    *(int *)(buf + 4) = (flags & 1) ? 0x10 : 0;
    *(int *)(buf + 8) = 0x1ca970;
    *(int *)(buf + 0xc) = (int)channel_index;
    if (((int (*)(int, void *, void *, void *))0x2060f8)(
            0, (char *)channel + 0x70, buf, *(void **)0x50545c) < 0) {
      sound_dsound_log_error(-1, (char *)0x2c114c);
      return 0;
    }
    if (flags & 1) {
      csmemset(stereo_buf, 0, 0x2c);
      {
        float *listener = (float *)0x31fc3c;
        ((void (*)(void *, int, int, int, int, int))0x1cadd0)(
            stereo_buf, 0, 0, 0, (int)channel_index, 0);
      }
    } else {
      int caps;
      ((void (*)(int *, void *))0x204c79)(&caps, *(void **)0x50545c);
      if (caps & 0x10000) {
        if (flags & 2) {
          ((int (*)(int, float))0x1c9130)(0, 1.0f);
          ((int (*)(int, float))0x1c9130)(0, 1.0f);
          ((int (*)(int, float))0x1c9130)(0, 0.5f);
        } else {
          ((int (*)(int, float))0x1c9130)(0, 0.5f);
          ((int (*)(int, float))0x1c9130)(0, 0.5f);
        }
      } else if (!(flags & 2)) {
        ((int (*)(int, float))0x1c9130)(0, 0.5f);
        ((int (*)(int, float))0x1c9130)(0, 0.5f);
      }
      ((void (*)(void *, int, void *))0x2052de)(*(void **)channel, 7,
                                                 (void *)0x2bc710);
      ((void (*)(void *, int, void *))0x205bd8)(*(void **)channel, 3,
                                                 stereo_buf);
    }
    csmemset(desc, 0, 0x20);
    *(float *)desc = 1.0f;
    *(float *)(desc + 4) = 1.0f;
    ((void (*)(void *, int))0x1ca5e0)(desc, (int)channel_index);
    return 1;
  }
}

char FUN_001cb4c0(void *driver_caps)
{
  char ok = 0;
  *(char *)0x4fdbc0 = 0;
  *(char *)0x505484 = 0;
  *(float *)0x505488 = 1.0f;
  *(int *)0x505460 = 0;
  if (!driver_caps) {
    display_assert((char *)0x280f94, "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c",
                   0xea, 1);
    system_exit(-1);
  }
  if (((int (*)(void *, int, int))0x206232)(*(void **)0x50545c, 0, 0) < 0)
    goto fail;
  {
    int wf[4];
    int a, b;
    if (((int (*)(void *, int *))0x204c5d)(*(void **)0x50545c, wf) < 0)
      goto fail_caps;
    *(int *)0x50544c = wf[0];
    *(int *)0x505450 = wf[1];
    *(int *)0x505454 = wf[2];
    *(int *)0x505458 = wf[3];
    if (((int (*)(void *, int))0x204d81)(*(void **)0x50545c, 0x4043126f) < 0)
      goto fail_pri;
    if (((int (*)(void *, float))0x204e48)(*(void **)0x50545c, 1.0f) < 0)
      goto fail_vol;
  }
  {
    char buf[0x34];
    csmemset(buf, 0, 0x34);
    if (((int (*)(void *, int, void *, int, void *, int *, int *))0x204c95)(
            *(void **)0x50545c, (void *)0x2bccf0, 0x3a5c, &a, &b, buf) < 0) {
      sound_dsound_log_error(-1, (char *)0x2c11fc);
    }
    ((void (*)(void *, int, int))0x204d41)(*(void **)0x50545c, 0, 0x7fffffff);
    ((void (*)(void))0x2038df)();
    ((void (*)(void *))0x1ca2b0)(buf);
  }
  {
    char *caps = (char *)driver_caps;
    int bus;
    for (bus = 0; bus < 4; bus++) {
      int16_t *counts = (int16_t *)(caps + 0xa + bus * 2);
      int16_t j;
      char created = 1;
      for (j = 0; j < *counts; j++) {
        *(int16_t *)0x4fdbc2 += 1;
        if (created) {
          void *ch = ((void *(*)(void))0x1c92f0)();
          if (j < 0 || j >= 4) {
            display_assert((char *)0x2c08f8, "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c",
                           0x1a6, 1);
            system_exit(-1);
          }
          *(int16_t *)((char *)ch + 2) = -1;
          *(int16_t *)ch = j;
          created = 1;
        } else {
          created = 0;
        }
      }
    }
    {
      int16_t *table = (int16_t *)0x5053c6;
      int16_t *src = (int16_t *)((char *)caps + 2);
      int group;
      for (group = 0; group < 4; group++) {
        int16_t k;
        char group_ok = 0;
        for (k = 0; k < src[group]; k++) {
          *(int16_t *)0x4fdfc4 += 1;
          if (group_ok) {
            if (FUN_001cb210(k, 0))
              group_ok = 1;
            else
              group_ok = 0;
          }
        }
        if (group_ok)
          ok = 1;
      }
    }
  }
  if (ok)
    ((void (*)(void))0x1c9cf0)();
  return ok;
fail_vol:
fail_pri:
fail_caps:
fail:
  return 0;
}

void FUN_001cb820(void)
{
  if (*(char *)0x4eaf40) {
    (*(void (**)(void))(*(int *)0x4eaf48 + 8))();
    data_make_invalid(*(data_t **)0x4fdba4);
    data_make_invalid(*(data_t **)0x4fdba0);
    *(char *)0x4eaf40 = 0;
  }
  if (*(data_t **)0x4fdba4)
    data_dispose(*(data_t **)0x4fdba4);
  if (*(data_t **)0x4fdba0)
    data_dispose(*(data_t **)0x4fdba0);
  FUN_001bde90();
}

void sound_reconnect_to_structure_bsp(void)
{
  if (*(char *)0x4eaf40 && *(char *)0x4eaf41) {
    int index = data_next_index(*(data_t **)0x4fdba4, -1);
    while (index != -1) {
      char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
      if (*(int16_t *)(entry + 0x14) == 1) {
        scenario_location_from_point(entry + 0x20, entry + 0x44);
      }
      index = data_next_index(*(data_t **)0x4fdba4, index);
    }
  }
}

float FUN_001cbc20(float t)
{
  return *(float *)0x2c1288 * t;
}

char FUN_001cbc40(int sound_handle /* @<ebx> */)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  int16_t channel = *(int16_t *)(entry + 0x8c);
  if (channel != -1) {
    if (channel < 0 || channel >= *(int16_t *)0x4eb0b4) {
      display_assert((char *)0x2c1294, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x428, 1);
      system_exit(-1);
    }
    if (*(int *)(0x4fc3a0 + (int)channel * 0x18) != sound_handle) {
      display_assert((char *)0x2c1360, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x59f, 1);
      system_exit(-1);
    }
  }
  if (!(*(uint8_t *)(entry + 4) & 1)) {
    void (*update)(int, void *, void *) = *(void (**)(int, void *, void *))(entry + 0x10);
    if (update && *(int *)(entry + 0x84) < *(int *)0x4eaf4c) {
      if (!update(*(int *)(entry + 0xc), entry + 0x54, entry + 0x14)) {
        if (*(int16_t *)(entry + 2) == 0) {
          void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
          void *class_def = sound_class_get_definition(*(int16_t *)((char *)tag + 4));
          if (!((char *)class_def)[8])
            *(int *)(entry + 0x10) = 0;
          else
            return 0;
        } else {
          return 0;
        }
      }
    }
  }
  return 1;
}

char FUN_001cc1c0(int looping_handle, void *out)
{
  char *src = (char *)datum_absolute_index_to_index(*(data_t **)0x4fdba0,
                                                    looping_handle);
  if (!src)
    return 0;
  csmemcpy(out, src + 0xc, 0x40);
  return 1;
}

char FUN_001cc200(int looping_handle, void *source, void *position)
{
  char *src = (char *)datum_absolute_index_to_index(*(data_t **)0x4fdba0,
                                                    looping_handle);
  char *dst = (char *)position;
  if (!src)
    return 0;
  *(int *)(dst + 0x38) = *(int *)(src + 0x44);
  *(int *)(dst + 0x3c) = *(int *)(src + 0x48);
  if (*(int16_t *)(src + 0xc) != 0) {
    csmemcpy(dst + 0x24, src + 0x30, 0xc);
    csmemcpy(dst + 0x18, src + 0x24, 0xc);
    *(int *)(dst + 0x30) = *(int *)(src + 0x3c);
    *(int *)(dst + 0x34) = *(int *)(src + 0x40);
  } else {
    csmemcpy(dst + 0x18, *(void **)0x31fc3c, 0xc);
    csmemcpy(dst + 0x24, *(void **)0x31fc38, 0xc);
  }
  csmemcpy(dst + 0xc, source, 0xc);
  if (*(int16_t *)dst == 1) {
    *(float *)(dst + 0xc) += *(float *)(src + 0x18);
    *(float *)(dst + 0x10) += *(float *)(src + 0x1c);
    *(float *)(dst + 0x14) += *(float *)(src + 0x20);
  }
  return 1;
}

void FUN_001cc2f0(int sound_handle /* @<eax> */, int tag_index /* @<esi> */)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  if (*(int *)(entry + 8) != tag_index)
    *(int *)(entry + 0x98) = tag_index;
}

int FUN_001cc440(int source /* @<edi> */)
{
  int index = data_next_index(*(data_t **)0x4fdba0, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba0, index);
    if (*(int *)(entry + 8) == source)
      return index;
    index = data_next_index(*(data_t **)0x4fdba0, index);
  }
  return -1;
}

void FUN_001cc4f0(int sound_handle)
{
  if (*(char *)0x4fc382) {
    char buf[0x200];
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
    void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
    float priority = sound_get_default_priority(*(int *)(entry + 8));
    float min_dist = sound_class_get_min_distance(*(int *)(entry + 8));
    float gain_a = *(float *)(entry + 0x4c);
    float gain_b = *(float *)(entry + 0x50);
    FUN_00189540(0, entry + 0x20, priority, (void *)0x2ee6e0);
    FUN_00189540(0, entry + 0x20, min_dist, (void *)0x2ee6d0);
    crt_sprintf(buf, (char *)0x2c1538, tag_get_name(*(int *)(entry + 8)),
                (double)gain_a, (double)gain_b);
    FUN_00189cb0(0, entry + 0x20, buf, *(int *)0x2ee6c4);
  }
}

void FUN_001cc5b0(int sound_tag_index, void *source)
{
  if (*(char *)0x4fc381 && *(int16_t *)source == 1) {
    void *lsnd = tag_get(0x6c736e64, sound_tag_index);
    char *pitch_block = (char *)lsnd + 0x3c;
    float min_dist = 0.0f;
    float priority = 0.0f;
    int i;
    for (i = 0; i < *(int *)pitch_block; i++) {
      char *elem = (char *)tag_block_get_element(pitch_block, i, 0xa0);
      if (*(int *)(elem + 0x4c) != -1) {
        min_dist = sound_class_get_min_distance(*(int *)(elem + 0x4c));
        priority = sound_get_default_priority(*(int *)(elem + 0x4c));
        if (min_dist <= *(float *)0x2533c0)
          break;
      }
    }
    {
      char *track_block = (char *)lsnd + 0x48;
      for (i = 0; i < *(int *)track_block; i++) {
        char *elem = (char *)tag_block_get_element(track_block, i, 0x68);
        if (*(int *)(elem + 0xc) != -1) {
          min_dist = sound_class_get_min_distance(*(int *)(elem + 0xc));
          priority = sound_get_default_priority(*(int *)(elem + 0xc));
        }
      }
    }
    {
      char *pos = (char *)source + 0xc;
      const char *name = tag_get_name(sound_tag_index);
      FUN_00189cb0(0, pos, (void *)name, *(int *)0x2ee6c4);
      FUN_00189540(0, pos, priority, (void *)0x2ee6dc);
      FUN_00189540(0, pos, min_dist, (void *)0x2ee6d8);
    }
  }
}

void sound_initialize(void **driver_out)
{
  *(char *)0x4eaf40 = 0;
  *(char *)0x4eaf41 = 1;
  FUN_001cf820(driver_out);
  ((void (*)(void))0x1be3e0)();
  csmemcpy((void *)0x4eb068, (void *)0x2c1220, 0x12 * 4);
  *(float *)0x4eb0b0 = 1.0f;
  if (driver_out) {
    int16_t driver_id = *(int16_t *)driver_out;
    if (driver_id >= 0 && driver_id < 2) {
      void *driver = *(void **)(0x32f6dc + (int)driver_id * 4);
      if (driver && *(int16_t *)driver == driver_id) {
        data_t *sounds = data_new((char *)0x2c1590, 0x200, 0xac);
        data_t *looping = data_new((char *)0x2c1580, 0x80, 0xe4);
        *(data_t **)0x4fdba4 = sounds;
        *(data_t **)0x4fdba0 = looping;
        if (sounds && looping &&
            ((char (*)(void *)) * (void (**)(void *))((char *)driver + 4))(
                driver_out)) {
          data_delete_all(sounds);
          data_delete_all(looping);
          {
            int16_t *counts = (int16_t *)driver_out;
            int16_t *cursor = (int16_t *)0x32fcf8;
            int group;
            for (group = 0; group < 4; group++) {
              int16_t total = *(int16_t *)0x4eb0b4 + counts[group];
              if (total > 0x100) {
                display_assert((char *)0x2c1544, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                               0x168, 1);
                system_exit(-1);
              }
              *(int16_t *)0x4eb0b4 = total;
              {
                int16_t j;
                for (j = 0; j < counts[group]; j++) {
                  char *slot = (char *)sound_channel_get(j);
                  *(int *)slot = -1;
                  *(int16_t *)(slot + 4) = cursor[group];
                  *(int *)(slot + 0x10) = 0;
                  *(int *)(slot + 0x14) = 0;
                }
              }
              cursor += 1;
            }
          }
          *(char *)0x4eaf40 = 1;
        }
      }
    }
  }
}

float FUN_001ccbe0(int channel_index /* @<eax> */, void *source /* @<edi> */)
{
  switch (*(int16_t *)source) {
  case 0:
    return *(float *)0x2533c0;
  case 1:
    if (!*(char *)sound_listener_get((short)channel_index)) {
      display_assert((char *)0x2c1624, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x574, 1);
      system_exit(-1);
    }
    return sound_listener_distance_sq(channel_index, source);
  case 2:
    return sound_source_distance_sq(source);
  default:
    display_assert((char *)0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x57a, 1);
    system_exit(-1);
    return 0.0f;
  }
}

float FUN_001ccca0(int channel_index /* @<eax> */, void *source /* @<edi> */)
{
  switch (*(int16_t *)source) {
  case 0:
    return *(float *)0x2533c0;
  case 1:
    if (!*(char *)sound_listener_get((short)channel_index)) {
      display_assert((char *)0x2c1624, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x58d, 1);
      system_exit(-1);
    }
    return sound_listener_distance(channel_index, source);
  case 2:
    return sound_source_distance(source);
  default:
    display_assert((char *)0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x593, 1);
    system_exit(-1);
    return 0.0f;
  }
}

char sound_update_time(int sound_a /* @<eax> */, int sound_b /* @<edi> */,
                       float threshold)
{
  char *entry_a = (char *)datum_get(*(data_t **)0x4fdba4, sound_a);
  void *tag_a = tag_get(0x736e6421, *(int *)(entry_a + 8));
  char *entry_b = (char *)datum_get(*(data_t **)0x4fdba4, sound_b);
  void *tag_b = tag_get(0x736e6421, *(int *)(entry_b + 8));
  if (sound_b != sound_a) {
    display_assert((char *)0x2c1648, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                   0x763, 1);
    system_exit(-1);
  }
  {
    void *class_a = sound_class_get_definition(*(int16_t *)((char *)tag_a + 4));
    void *class_b = sound_class_get_definition(*(int16_t *)((char *)tag_b + 4));
    if (*(int16_t *)((char *)class_a + 0xa) <= *(int16_t *)((char *)class_b + 0xa))
      return 1;
    if (*(int16_t *)((char *)class_a + 0xa) == *(int16_t *)((char *)class_b + 0xa)) {
      float dist = FUN_001ccbe0(*(int16_t *)(entry_b + 6), entry_b + 0x14);
      if ((dist <= threshold) == 0)
        return 0;
    }
    return 1;
  }
}

int FUN_001cd190(int sound_tag_index /* @<eax> */, void *track, void *source)
{
  if (!*(char *)0x4eaf40 || !*(char *)0x4eaf41)
    return -1;
  {
    int index = data_new_at_index(*(data_t **)0x4fdba0);
    if (index == -1)
      return -1;
    char *entry = (char *)datum_get(*(data_t **)0x4fdba0, index);
    void *lsnd = tag_get(0x6c736e64, sound_tag_index);
    *(int *)(entry + 4) = sound_tag_index;
    *(int *)(entry + 8) = *(int *)source;
    *(int16_t *)(entry + 0x50) = 0;
    entry[0x4e] = 0;
    if (*(int *)((char *)lsnd + 0x48) <= 0)
      return index;
    {
      char *block = (char *)lsnd + 0x48;
      int i = 0;
      for (;;) {
        char *elem = (char *)tag_block_get_element(block, i, 0x68);
        if (*(int *)(elem + 0xc) == -1) {
          if (++i >= *(int *)block)
            return index;
          continue;
        }
        {
          float *seed = random_math_get_local_seed_address();
          float r = random_real_range((int *)seed, *(float *)(elem + 0x10),
                                      *(float *)(elem + 0x14));
          float span = *(float *)((char *)lsnd + 0x10) - *(float *)((char *)lsnd + 4);
          int start_ms = (int)(float)(r * span * *(float *)0x254cb8 +
                                      (float)*(int *)0x4eaf4c);
          *(int *)(entry + 0x54 + i * 4) = start_ms;
        }
        if (++i >= *(int *)block)
          return index;
      }
    }
  }
}

void FUN_001cd390(void *track_entry /* @<edi> */, float *out /* @<esi> */)
{
  float r1 = random_real_range((int *)random_math_get_local_seed_address(),
                               *(float *)((char *)track_entry + 0x60),
                               *(float *)((char *)track_entry + 0x64));
  if (r1 > *(float *)0x2533c0) {
    float *defaults = (float *)0x31fc38;
    out[0] = defaults[0];
    out[1] = defaults[1];
    out[2] = defaults[2];
    return;
  }
  {
    float r2 = random_real_range((int *)random_math_get_local_seed_address(),
                                 *(float *)((char *)track_entry + 0x58),
                                 *(float *)((char *)track_entry + 0x5c));
    float r3 = random_real_range((int *)random_math_get_local_seed_address(),
                                 *(float *)((char *)track_entry + 0x50),
                                 *(float *)((char *)track_entry + 0x54));
    float vec[3];
    angles_to_vector(vec, out);
    out[0] = vec[0] * r1;
    out[1] = vec[1] * r1;
    out[2] = vec[2] * r1;
  }
}

void sound_stop_impulse_by_source_and_definition(int source, int definition)
{
  int index = data_next_index(*(data_t **)0x4fdba4, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
    if (*(int16_t *)(entry + 2) == 0 && *(int *)(entry + 0xc) == source &&
        *(int *)(entry + 8) == definition) {
      sound_stop_impulse(index);
      return;
    }
    index = data_next_index(*(data_t **)0x4fdba4, index);
  }
}

void sound_stop_all(void)
{
  if (*(char *)0x4eaf40) {
    int index = data_next_index(*(data_t **)0x4fdba4, -1);
    while (index != -1) {
      sound_stop_channel(index);
      index = data_next_index(*(data_t **)0x4fdba4, index);
    }
    data_make_valid(*(data_t **)0x4fdba0);
    (*(void (**)(void))(*(int *)0x4eaf48 + 0x2c))();
  }
  *(int *)0x4eaf44 = 0;
}

void FUN_001cd690(void)
{
  char all_dead = players_are_all_dead();
  int index = data_next_index(*(data_t **)0x4fdba4, -1);
  char music_active = 0;
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
    void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
    int16_t channel = *(int16_t *)(entry + 0x8c);
    if (channel == -1 || !sound_channel_update_status(channel) ||
        *(int16_t *)(entry + 2) == 2 || *(int16_t *)(entry + 2) == 3) {
      if (FUN_001cbc40(index)) {
        float priority = sound_get_default_priority(*(int *)(entry + 8));
        int16_t allocated = sound_allocate_channel(entry + 0x14, priority);
        FUN_001cc4f0(index);
        {
          int16_t class_index = *(int16_t *)((char *)tag + 4);
          if (class_index == 0x2c || class_index == 0x2e || class_index == 0x2f)
            music_active = 1;
        }
        if (allocated == -1) {
          if (!(entry[4] & 4))
            sound_start_fade(0, -1.0f, *(int *)0x2c127c, index);
          entry[4] |= 4;
        } else {
          *(int16_t *)(entry + 6) = allocated;
          if (entry[4] & 4) {
            sound_start_fade(0, -1.0f, index, *(int *)0x2c1280);
            entry[4] &= ~4;
          }
        }
        if (all_dead) {
          if (*(int16_t *)((char *)tag + 4) == 0x2c && *(int16_t *)(entry + 0x8c) != -1)
            sound_start_fade(0, -1.0f, *(int *)0x2c1284, index);
          else if (*(int16_t *)((char *)tag + 4) == 0x2e &&
                   *(int16_t *)(entry + 0x8c) == -1)
            ;
        }
      } else {
        sound_stop_channel(index);
      }
    } else {
      sound_stop_channel(index);
    }
    index = data_next_index(*(data_t **)0x4fdba4, index);
  }
  if (music_active) {
    float step = *(float *)0x4eaf50 * *(float *)0x25bc08;
    float target = *(float *)0x32f6d8 - *(float *)0x4eb0b0;
    if (-step <= target && target <= step)
      *(float *)0x4eb0b0 += target;
    else if (target > step)
      *(float *)0x4eb0b0 += step;
  } else {
    float step = *(float *)0x4eaf50 * *(float *)0x2c16d0;
    float target = *(float *)0x2533c8 - *(float *)0x4eb0b0;
    if (-step <= target && target <= step)
      *(float *)0x4eb0b0 += target;
    else
      *(float *)0x4eb0b0 += step;
  }
}

short FUN_001cd8b0(int sound_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
  short best = -1;
  float best_dist = 0.0f;
  short channel = *(int16_t *)(entry + 6);
  float ref_dist = FUN_001ccbe0(channel, entry + 0x14);
  short count = *(int16_t *)0x4eb0b4;
  short i;
  for (i = 0; i < count; i++) {
    int16_t enc = *(int16_t *)(0x4fc3a4 + (int)i * 8);
    char ok = 1;
    if ((enc >> 3) & 1) != (*(int16_t *)((char *)tag + 0x6e) == 0))
      ok = 0;
    if (((enc >> 1) & 1) != (*(int16_t *)((char *)tag + 0x6c) == 0))
      ok = 0;
    if (((enc >> 2) & 1) != (*(int16_t *)((char *)tag + 6) == 0))
      ok = 0;
    if (!(enc & 2)) {
      if ((~enc & 1) != (*(int16_t *)(entry + 0x14) == 0))
        ok = 0;
    }
    if (ok) {
      int other = *(int *)(0x4fc3a0 + (int)i * 0x18);
      if (other == -1)
        return i;
      if (sound_update_time(other, sound_handle, ref_dist)) {
        if (best != -1) {
          char *other_entry = (char *)datum_get(*(data_t **)0x4fdba4, other);
          float d = FUN_001ccbe0(*(int16_t *)(other_entry + 6), other_entry + 0x14);
          if (!sound_update_time(sound_handle, other, d))
            continue;
        }
        best = i;
        best_dist = FUN_001ccbe0(channel, entry + 0x14);
      }
    }
  }
  return best;
}

char sound_refresh_looping(int sound_tag_index, void *source, void *track,
                           short track_type)
{
  char created = 0;
  char *src = (char *)source;
  if (*(int16_t *)src != 0) {
    if (!valid_real_normal3d(src + 0x18)) {
      display_assert((char *)0x2c17c0, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x2f4, 1);
      system_exit(-1);
    }
  }
  FUN_001cc5b0(sound_tag_index, source);
  if (!*(char *)0x4eaf40 || !*(char *)0x4eaf41)
    return 0;
  {
    int looping_index = FUN_001cc440(sound_tag_index);
    if (looping_index == -1) {
      if (track_type == 2)
        return 0;
      looping_index = FUN_001cd190(sound_tag_index, track, source);
      created = 1;
      if (looping_index == -1)
        return 0;
    }
    {
      char *loop = (char *)datum_get(*(data_t **)0x4fdba0, looping_index);
      void *lsnd = tag_get(0x6c736e64, sound_tag_index);
      if (*(int *)(loop + 4) != sound_tag_index) {
        display_assert((char *)0x2c1860, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                       0x30e, 1);
        system_exit(-1);
      }
      csmemcpy(loop + 0xc, source, 0x40);
      loop[0x4c] = *(char *)0x4eaf54;
      if (track_type != 2 && loop[0x4e] && *(int16_t *)(loop + 0x50) == 0) {
        datum_delete(*(data_t **)0x4fdba0, looping_index);
        return 1;
      }
      if (!FUN_001cc200(looping_index, track, loop + 0xc))
        return 0;
      if (*(int16_t *)(loop + 0x52) == 2)
        return 1;
      {
        int i;
        char *tracks = (char *)lsnd + 0x48;
        for (i = 0; i < *(int *)tracks; i++) {
          char *elem = (char *)tag_block_get_element(tracks, i, 0x68);
          if (*(int *)(loop + 0x54 + i * 4) < *(int *)0x4eaf4c &&
              *(int *)(elem + 0xc) != -1) {
            float out[3];
            float params[3];
            int16_t mode = *(int16_t *)(loop + 0xc) == 0 ? 2 : 1;
            params[0] = *(float *)(elem + 0x18);
            params[1] = *(float *)(elem + 0x10);
            params[2] = *(float *)(elem + 0x14);
            FUN_001cd390(elem, out);
            if (!FUN_001cc200(looping_index, params, out))
              return 0;
            if (*(int *)(loop + 0x10) != (int)0x1cc200)
              sound_start(*(int *)(elem + 0xc), out, *(int *)(loop + 8), 0, 0, 0);
          }
        }
      }
      return 1;
    }
  }
}

void FUN_001ce9c0(void)
{
  if (!game_in_progress())
    return;
  {
    short player_index;
    char *flags = (char *)0x4eaf59;
    for (player_index = 0; player_index < 4; player_index++) {
      if (player_index < 0 || player_index >= 4) {
        display_assert((char *)0x2c12f4, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                       0x430, 1);
        system_exit(-1);
      }
      {
        int pi = local_player_get_player_index(player_index);
        if (pi == -1)
          continue;
        void *camera = observer_get_camera((unsigned short)player_index);
        if (!camera) {
          display_assert((char *)0x266e9c, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                         0x4ef, 1);
          system_exit(-1);
        }
        {
          char was_outside = flags[-1];
          char outside;
          outside = FUN_0018f3e0(camera + 0xc, camera, (int16_t *)(camera + 0x2c));
          flags[0] = outside;
          if (outside != was_outside) {
            void *globals = game_globals_get();
            globals = (char *)globals + 0xf8;
            if (outside) {
              if (*(int *)globals > 0) {
                char *elem = (char *)tag_block_get_element(globals, 0, 0x10);
                if (*(int *)(elem + 0xc) != -1)
                  sound_start(*(int *)(elem + 0xc), 0, 0, 0, 0, -1);
              }
            } else if (*(int *)globals > 1) {
              char *elem = (char *)tag_block_get_element(globals, 1, 0x10);
              if (*(int *)(elem + 0xc) != -1)
                sound_start(*(int *)(elem + 0xc), 0, 0, 0, 0, -1);
            }
          }
          csmemcpy((char *)sound_listener_get(player_index) + 0x2c, camera + 0x2c,
                   0xc);
        }
      }
    }
  }
}

short FUN_001cebb0(int sound_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  int16_t channel = *(int16_t *)(entry + 0x8c);
  if (channel != -1) {
    if (channel < 0 || channel >= *(int16_t *)0x4eb0b4) {
      display_assert((char *)0x2c1294, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x428, 1);
      system_exit(-1);
    }
    if (*(int *)(0x4fc3a0 + (int)channel * 0x18) != sound_handle) {
      display_assert((char *)0x2c1890, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x6d0, 1);
      system_exit(-1);
    }
    return channel;
  }
  {
    void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
    void *class_def = sound_class_get_definition(*(int16_t *)((char *)tag + 4));
    if (!((char *)class_def)[8] || *(int *)(entry + 0xc) == -1)
      return -1;
    {
      short i;
      short count = *(int16_t *)0x4eb0b4;
      for (i = 0; i < count; i++) {
        int other = *(int *)(0x4fc3a0 + (int)i * 0x18);
        if (other == -1)
          continue;
        {
          char *other_entry = (char *)datum_get(*(data_t **)0x4fdba4, other);
          if (*(int *)(other_entry + 0xc) != *(int *)(entry + 0xc))
            continue;
          void *other_tag = tag_get(0x736e6421, *(int *)(other_entry + 8));
          void *other_class =
            sound_class_get_definition(*(int16_t *)((char *)other_tag + 4));
          if (((char *)other_class)[8])
            return FUN_001cd8b0(sound_handle);
        }
      }
    }
    return -1;
  }
}

void FUN_001cf100(void)
{
  int index = data_next_index(*(data_t **)0x4fdba0, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba0, index);
    void *lsnd = tag_get(0x6c736e64, *(int *)(entry + 4));
    if (entry[0x4c] != *(char *)0x4eaf54) {
      datum_delete(*(data_t **)0x4fdba0, index);
    } else if (*(int16_t *)(entry + 0x52) != 2) {
      char *tracks = (char *)lsnd + 0x48;
      int i;
      for (i = 0; i < *(int *)tracks; i++) {
        char *elem = (char *)tag_block_get_element(tracks, i, 0x68);
        if (*(int *)(entry + 0x54 + i * 4) >= *(int *)0x4eaf4c ||
            *(int *)(elem + 0xc) == -1)
          continue;
        {
          char flags = *(char *)(elem + 0x1c);
          if ((flags & 1) && entry[0x4d])
            continue;
          if ((flags & 2) && !entry[0x4d])
            continue;
          {
            float out[3];
            float params[3];
            int16_t mode = *(int16_t *)(entry + 0xc) == 0 ? 2 : 1;
            params[0] = mode;
            params[1] = *(float *)(elem + 0x18);
            params[2] = *(float *)(elem + 0x10);
            FUN_001cd390(elem, out);
            FUN_001cc200(index, params, out);
            sound_start(*(int *)(elem + 0xc), out, *(int *)(entry + 8),
                        *(int *)(entry + 0x10), 0, 0);
          }
        }
      }
    }
    index = data_next_index(*(data_t **)0x4fdba0, index);
  }
}

void FUN_001cf360(void)
{
  int index = data_next_index(*(data_t **)0x4fdba4, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
    if (*(int *)(entry + 0x84) > *(int *)0x4eaf4c)
      break;
    if (*(int16_t *)(entry + 0x8c) == -1) {
      void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
      char *perm = (char *)tag_block_get_element((char *)tag + 0x98,
                                                 *(int16_t *)(entry + 0x8e), 0x48);
      perm = (char *)tag_block_get_element(perm + 0x3c, *(int16_t *)(entry + 0x90), 0x7c);
      if (!((int (*)(void *))0x1be550)(perm)) {
        void *tag2 = tag_get(0x736e6421, *(int *)(entry + 8));
        int16_t enc = *(int16_t *)((char *)tag2 + 4);
        void *class_def = sound_class_get_definition(enc);
        switch (*(int16_t *)((char *)class_def + 0xc)) {
        case 0: {
          char *pr = (char *)tag_block_get_element((char *)tag2 + 0x98,
                                                    *(int16_t *)(entry + 0x8e), 0x48);
          char *pe = (char *)tag_block_get_element(pr + 0x3c,
                                                   *(int16_t *)(entry + 0x90), 0x7c);
          if (*(int16_t *)(pe + 0x3a) == -1)
            *(int16_t *)(pe + 0x3a) = *(int16_t *)(entry + 0x90);
          sound_stop_channel(index);
          break;
        }
        case 1:
          sound_stop_channel(index);
          break;
        default:
          display_assert((char *)0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x679,
                         1);
          system_exit(-1);
        }
      }
    }
    index = data_next_index(*(data_t **)0x4fdba4, index);
  }
}

void FUN_001cf820(void **out)
{
  *out = (void *)0x32fce4;
}"""
