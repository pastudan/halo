/*
 * FUN_00075380 -- bitmap_extract: create a new bitmap entry in the group.
 *
 * Validates the source bitmap, determines format and mipmap count,
 * adds a new bitmap entry to the group's tag_block, copies registration
 * point, optionally smooths, then copies pixel data from source to dest.
 *
 * Source TU: bitmap_extract.c (assert strings confirm)
 * ABI: bitmap passed in EAX (@EAX), returns short (new bitmap index or -1).
 */
short FUN_00075380(void *bitmap )
{
  char *group;
  short bitmap_type;
  short bitmap_usage;
  short max_mipmaps;
  short mipmap_count;
  short new_bitmap_index;
  int format;
  unsigned char *flags_ptr;
  void *pixel_data;
  char *bitmap_data;
  char *bm;
  int pixel_size;
  int kb_size;
  char *format_str;

  bm = (char *)bitmap;

  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_extract.c", 0x487, 1);
    system_exit(-1);
  }

  format = FUN_00073fd0(bitmap);

  group = *(char **)0x33414c;
  bitmap_type = *(short *)(group + 0x0);
  bitmap_usage = *(short *)(group + 0x4);

  if (bitmap_type == 4 || bitmap_usage == 4) {
    mipmap_count = 0;
  } else {
    mipmap_count = (short)bitmap_get_max_mipmap_count(bitmap);

    if (*(short *)(group + 0x0) == 3 && mipmap_count >= 2) {
      mipmap_count = 2;
    }

    max_mipmaps = *(short *)(group + 0x4c);
    if (max_mipmaps > 0) {
      unsigned int limit = max_mipmaps - 1;
      if (limit <= (short)mipmap_count) {
        mipmap_count = limit;
      }
    }
  }

  new_bitmap_index = FUN_00077120(
    *(void **)0x33414c, *(short *)(bm + 0x4), *(short *)(bm + 0x6),
    *(short *)(bm + 0x8), *(short *)(bm + 0xa), format, (int)mipmap_count);

  *(short *)0x33415e = new_bitmap_index;

  if (new_bitmap_index == -1) {
    return new_bitmap_index;
  }

  pixel_data = FUN_00077590(bitmap);

  bitmap_data = (char *)tag_block_get_element(*(char **)0x33414c + 0x60,
                                              (int)new_bitmap_index, 0x30);

  group = *(char **)0x33414c;

  flags_ptr = (unsigned char *)(group + 0x6);
  if ((*flags_ptr & 0x8) != 0) {
    *(short *)(bitmap_data + 0x10) = (short)((*(short *)(bm + 0x10) + 1) / 2);
    *(short *)(bitmap_data + 0x12) = (short)((*(short *)(bm + 0x12) + 1) / 2);
  } else {
    *(int *)(bitmap_data + 0x10) = *(int *)(bm + 0x10);
  }

  if (pixel_data == 0) {
    return new_bitmap_index;
  }

  if (*(int *)((char *)pixel_data + 0x2c) == 0) {
    return new_bitmap_index;
  }

  group = *(char **)0x33414c;

  if (*(float *)(group + 0x44) > *(float *)0x2533c0) {
    switch (*(short *)(group + 0x0)) {
    case 0:
    case 1:
    case 2:
      bitmap_smooth(pixel_data, *(float *)(group + 0x44));
      break;
    case 3:
      crt_fprintf((void *)0x331050,
                  "### WARNING tried to smooth a sprite group",
                  (void *)0x261f2c);
      crt_fflush((void *)0x331050);
      break;
    case 4:
      crt_fprintf((void *)0x331050,
                  "### WARNING tried to smooth an interface-bitmap group",
                  (void *)0x261f2c);
      crt_fflush((void *)0x331050);
      break;
    default:
      display_assert("### ERROR unsupported bitmap group type",
                     "c:\\halo\\SOURCE\\bitmaps\\bitmap_extract.c", 0x4d0, 1);
      system_exit(-1);
    }
  }

  FUN_00074fb0(pixel_data, bitmap_data);

  if (*(short *)(bitmap_data + 0xa) == 1) {
    pixel_size = bitmap_get_pixel_data_size(bitmap_data);
    kb_size = (pixel_size + (((unsigned int)pixel_size >> 31) & 0x3ff)) >> 10;
    format_str =
      (char *)bitmap_format_get_string(*(short *)(bitmap_data + 0xc));
    crt_fprintf(
      (void *)0x331050, "bitmap created: #%dx#%dx#%d, %s, %dK-bytes\r\n",
      (int)*(short *)(bitmap_data + 0x4), (int)*(short *)(bitmap_data + 0x6),
      (int)*(short *)(bitmap_data + 0x8), format_str, kb_size);
    crt_fflush((void *)0x331050);
    return new_bitmap_index;
  }

  pixel_size = bitmap_get_pixel_data_size(bitmap_data);
  kb_size = (pixel_size + (((unsigned int)pixel_size >> 31) & 0x3ff)) >> 10;
  format_str = (char *)bitmap_format_get_string(*(short *)(bitmap_data + 0xc));
  crt_fprintf((void *)0x331050, "bitmap created: #%dx#%d, %s, %dK-bytes\r\n",
              (int)*(short *)(bitmap_data + 0x4),
              (int)*(short *)(bitmap_data + 0x6), format_str, kb_size);
  crt_fflush((void *)0x331050);

  return new_bitmap_index;
}

/*
 * FUN_00075630 -- 3D texture group extraction.
 *
 * Iterates over the pending bitmap array (base at DAT_00334134, count in
 * DAT_00334138). Groups consecutive entries with matching mip_count. For each
 * power-of-two group, creates a 3D bitmap, copies the slices into it via
 * bitmap_cube_map_face_extract, registers it with FUN_00075380, then frees
 * it. Logs warnings for incompatible-dimension or non-power-of-two groups.
 *
 * Returns 1 on success, 0 if a temporary bitmap allocation failed.
 */
char FUN_00075630(void)
{
  short mip_count;
  short width;
  short height;
  int outer;
  int slice_idx;
  char bvar4;
  char success;
  void *new_bitmap;
  short handle;
  void *tag_element;
  char *base;
  int i;

  success = 1;
  outer = 0;
  do {
    if ((short)outer >= *(short *)0x334138)
      break;
    base = *(char **)0x334134;
    mip_count = *(short *)(base + (short)outer * 0x10 + 4);
    width = *(short *)(*(char **)(base + (short)outer * 0x10) + 4);
    height = *(short *)(*(char **)(base + (short)outer * 0x10) + 6);
    slice_idx = 0;
    bvar4 = 0;

    while (*(short *)(base + ((short)outer + (short)slice_idx) * 0x10 + 4) ==
           mip_count) {
      if (*(short *)(*(char **)(base +
                                ((short)outer + (short)slice_idx) * 0x10) +
                     4) != width ||
          *(short *)(*(char **)(base +
                                ((short)outer + (short)slice_idx) * 0x10) +
                     6) != height) {
        bvar4 = 1;
      }
      slice_idx++;
      if (bvar4) {
        crt_fprintf((void *)0x331050,
                    "skipping 3D texture with incompatible slices\r\n");
        crt_fflush((void *)0x331050);
        goto next_group;
      }
    }

    if (slice_idx & (slice_idx - 1)) {
      crt_fprintf((void *)0x331050,
                  "skipping 3D texture with non power-of-two slice count\r\n");
      crt_fflush((void *)0x331050);
      goto next_group;
    }

    new_bitmap = bitmap_3d_new((unsigned short)width, (unsigned short)height,
                               (unsigned short)slice_idx, 0, 0xb);
    if (!new_bitmap || *(int *)((char *)new_bitmap + 0x2c) == 0) {
      error(2, "### ERROR extract: failed to allocate temporary bitmap");
      success = 0;
    } else {
      for (i = 0; (short)i < (short)slice_idx; i++) {
        bitmap_cube_map_face_extract(
          *(void **)(*(char **)0x334134 + ((short)outer + i) * 0x10),
          new_bitmap, 0, i);
      }
      *(short *)0x33415c = mip_count;
      handle = FUN_00075380(new_bitmap);
      if (handle != (short)-1) {
        tag_element = tag_block_get_element(*(char **)0x33414c + 0x54,
                                            (int)mip_count, 0x40);
        if (*(short *)((char *)tag_element + 0x20) == (short)-1) {
          *(short *)((char *)tag_element + 0x20) = handle;
          *(short *)((char *)tag_element + 0x22) = 1;
        } else {
          *(short *)((char *)tag_element + 0x22) += 1;
        }
      }
    }
    bitmap_delete(new_bitmap);

  next_group:
    outer += slice_idx;
  } while (success);
  return success;
}

/*
 * FUN_000766e0 -- bitmap extract: allocate and process all sequences.
 *
 * Iterates source bitmap rows (up to *(short*)(*(char**)0x334150+6) count),
 * allocating a new sequence element in the group's sequences block for each
 * run, initialising its frame range fields, then calling FUN_00076410 to
 * extract bitmaps into it. Returns 1 on full success, 0 on any failure.
 */
char FUN_000766e0(void)
{
  int local_8;
  int iVar3;
  short sVar2;
  char cVar1;

  cVar1 = 1;
  local_8 = 1;
  while (1) {
    if (*(short *)(*(char **)0x334150 + 6) <= (short)local_8)
      return cVar1;
    iVar3 = FUN_00073960(&local_8);
    FUN_00073a80();
    sVar2 = tag_block_add_element(*(char **)0x33414c + 0x54);
    if (sVar2 == -1) {
      error(2, "### ERROR extract: failed to allocate sequence");
      return 0;
    }
    *(short *)0x33415c = sVar2;
    *(void **)0x334158 =
      tag_block_get_element(*(char **)0x33414c + 0x54, (int)sVar2, 0x40);
    *(short *)(*(char **)0x334158 + 0x20) = (short)0xffff;
    *(short *)(*(char **)0x334158 + 0x22) = 0;
    cVar1 = FUN_00076410(local_8, (short)iVar3);
    local_8 = iVar3 + 1;
    if (!cVar1)
      return 0;
  }
}

/* FUN_00076a70 (0x76a70) — bitmap extract: compress color plate pixel data into
 * group buffer. Validates plate and group, allocates a temporary buffer,
 * compresses the pixel data using FUN_00119b40, reallocates to compressed size,
 * stores width/height/pointer in group, then calls FUN_00076790 to continue.
 * Source: bitmap_extract.c */
char FUN_00076a70(void *plate, void *group, int param_3)
{
  int size;
  void *t;

  if (!bitmap_verify(plate, 1)) {
    display_assert("bitmap_verify(plate, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_extract.c", 0x83, 1);
    system_exit(-1);
  }
  if (!group) {
    display_assert("group", "c:\\halo\\SOURCE\\bitmaps\\bitmap_extract.c", 0x84,
                   1);
    system_exit(-1);
  }

  size = bitmap_get_pixel_data_size(plate);
  *(unsigned short *)((char *)group + 0x18) =
    *(unsigned short *)((char *)plate + 4);
  *(unsigned short *)((char *)group + 0x1a) =
    *(unsigned short *)((char *)plate + 6);

  *(int *)((char *)group + 0x28) = (int)debug_malloc(
    size, 0, "c:\\halo\\SOURCE\\bitmaps\\bitmap_extract.c", 0x8a);
  if (*(int *)((char *)group + 0x28)) {
    if (FUN_00119b40((int)bitmap_mipmap_address(plate, 0), (unsigned int)size,
                     (unsigned int *)*(int *)((char *)group + 0x28),
                     &size, /* dup-args-ok: size is both source limit and output
                               capacity. */
                     (unsigned int)size)) {
      t = debug_realloc((void *)*(int *)((char *)group + 0x28), size,
                        "c:\\halo\\SOURCE\\bitmaps\\bitmap_extract.c", 0x90);
      if (t) {
        *(int *)((char *)group + 0x28) = (int)t;
        *(int *)((char *)group + 0x1c) = size;
        return FUN_00076790(group, param_3);
      }
      error(2, "### ERROR extract: failed to realloc color plate");
      return 0;
    }
    error(2, "### ERROR extract: failed to compress color plate");
    return 0;
  }
  error(2, "### ERROR extract: failed to allocate temporary buffer");
  return 0;
}

/*
 * FUN_00076bb0 -- bitmap tag_block element delete wrapper.
 *
 * Gets an element from a tag_block at the given index (element size 0x30),
 * then passes it to bitmap_delete.
 */
void FUN_00076bb0(void *tag_block, int index)
{
  void *element;

  element = tag_block_get_element(tag_block, index, 0x30);
  bitmap_delete(element);
}

/*
 * FUN_00076bd0 -- bitmap_group_postprocess: validate and initialize a bitmap
 * group tag.
 *
 * Called during tag loading. For each bitmap in the group: sets FORCE_POW2 flag
 * for interface bitmaps, verifies the bitmap, and registers it with the texture
 * cache. For each sequence: fixes up sprite-type bitmap indices and trims
 * trailing empty sequences. When DAT_00336194 is set (debug/validation mode),
 * emits diagnostic errors for malformed bitmaps, sequences, and sprites.
 *
 * Source TU: bitmap_utilities.c (confirmed by address placement)
 */
char FUN_00076bd0(int tag_index)
{
  char success;
  void *tag;
  void *bmp;
  void *seq;
  void *last_seq;
  void *next_seq;
  void *sprite;
  int *bitmaps_block;
  int *sequences_block;
  int *sprites_block;
  int bitmaps_count;
  int sequences_count;
  int sprites_count;
  int n;
  int i;
  int j;
  int w;
  int h;
  short first_bmp;
  short bmp_count;
  short bmp_idx;

  tag = tag_get(0x6269746d, tag_index);
  success = 1;

  /* Initialize bitmaps: set FORCE_POW2 for interface type, verify, register
   * with texture cache. */
  for (i = 0; i < *(int *)((char *)tag + 0x60); i++) {
    bmp = tag_block_get_element((int *)((char *)tag + 0x60), i, 0x30);
    if (*(short *)tag == 4) {
      /* interface bitmaps must be power-of-two: set FORCE_POW2 flag */
      *(unsigned char *)((char *)bmp + 0x0e) |= 0x10;
    }
    if (!bitmap_verify(bmp, 0)) {
      success = 0;
    } else {
      texture_cache_bitmap_new(tag_index, bmp);
    }
  }

  /* Fix up sequences: for sprite-type groups, clear first_bitmap_index and
   * bitmap_count fields if they are nonzero. */
  for (i = 0; i < *(int *)((char *)tag + 0x54); i++) {
    seq = tag_block_get_element((int *)((char *)tag + 0x54), i, 0x40);
    if (i < *(int *)((char *)tag + 0x54) - 1) {
      /* lookahead: touch next sequence element (side-effect order preservation)
       */
      tag_block_get_element((int *)((char *)tag + 0x54), i + 1, 0x40);
    }
    if (*(short *)tag == 3) {
      if (*(short *)((char *)seq + 0x20) || *(short *)((char *)seq + 0x22)) {
        seq = tag_block_get_element((int *)((char *)tag + 0x54), i, 0x40);
        *(short *)((char *)seq + 0x20) = 0;
        seq = tag_block_get_element((int *)((char *)tag + 0x54), i, 0x40);
        *(short *)((char *)seq + 0x22) = 0;
      }
    }
  }

  /* Trim trailing empty sequence: if the last sequence has bitmap_count == 0
   * and no sprites, shrink the sequences block by one. */
  n = *(int *)((char *)tag + 0x54);
  if (n > 0) {
    last_seq = tag_block_get_element((int *)((char *)tag + 0x54), n - 1, 0x40);
    if (*(short *)((char *)last_seq + 0x22) == 0 &&
        *(int *)((char *)last_seq + 0x34) == 0) {
      if (!tag_block_resize((int *)((char *)tag + 0x54), n - 1)) {
        error(0, "### FATAL_ERROR failed to fix bitmap group '%s'",
              tag_get_name(tag_index));
        success = 0;
      }
    }
  }

  /* Validation section: only active when DAT_00336194 is set. */
  if (*(uint8_t *)0x336194) {
    bitmaps_block = (int *)((char *)tag + 0x60);

    /* Check each bitmap for problematic formats and flags. */
    for (i = 0; i < *bitmaps_block; i++) {
      bmp = tag_block_get_element(bitmaps_block, i, 0x30);
      if (*(short *)((char *)bmp + 0x0c) == 3) {
        /* bitmap format is a8y8 -- must be fixed */
        error(2, "!!MUST BE FIXED: bitmap #%d of group '%s' has a8y8 format", i,
              tag_get_name(tag_index));
      }
      if (*(unsigned char *)((char *)bmp + 0x0e) & 0x10) {
        /* FORCE_POW2 flag set: check if actually power-of-two */
        w = (int)*(short *)((char *)bmp + 0x04);
        h = (int)*(short *)((char *)bmp + 0x06);
        if (!((w - 1) & w) && !((h - 1) & h)) {
          /* both dimensions are powers of two: linear bitmap does not need
           * forcing; flag is redundant/erroneous */
          error(2,
                "!!MUST BE FIXED: bitmap #%d of group '%s' is linear and "
                "power-of-two",
                i, tag_get_name(tag_index));
        }
      }
    }

    /* Check that the group has at least one bitmap. */
    bitmaps_count = *bitmaps_block;
    if (bitmaps_count < 1) {
      /* BUG (faithful reproduction): format and description were split into
       * two args by a missing string concatenation in the original source. */
      error(2, "!!MUST BE FIXED: ", "bitmap group '%s' has %d bitmaps",
            tag_get_name(tag_index), bitmaps_count);
    }

    /* Check that the group has at least one sequence, then validate each. */
    sequences_block = (int *)((char *)tag + 0x54);
    sequences_count = *(int *)((char *)tag + 0x54);
    if (sequences_count < 1) {
      /* BUG (faithful reproduction): same split-format bug as above. */
      error(2, "!!MUST BE FIXED: ", "bitmap group '%s' has %d sequences",
            tag_get_name(tag_index), sequences_count);
    }

    for (i = 0; i < *sequences_block; i++) {
      seq = tag_block_get_element(sequences_block, i, 0x40);
      next_seq = (i < *sequences_block - 1) ?
                   tag_block_get_element(sequences_block, i + 1, 0x40) :
                   (void *)0;

      if (*(short *)tag == 3) {
        /* sprites bitmap group */
        if (*(short *)((char *)seq + 0x20) == 0 &&
            *(short *)((char *)seq + 0x22) == 0) {
          /* sequence correctly has no direct bitmaps -- proceed to sprite
           * block check below */
        } else {
          error(2,
                "!!MUST BE FIXED: bitmap group '%s' (type=%d) sequence #%d"
                " doesn't know it's a sprite sequence",
                tag_get_name(tag_index), (int)*(short *)tag, i);
        }
      } else {
        /* non-sprite bitmap group: validate the bitmap range */
        first_bmp = *(short *)((char *)seq + 0x20);
        bmp_count = *(short *)((char *)seq + 0x22);
        bitmaps_count = *(int *)((char *)tag + 0x60);
        if (first_bmp >= 0 && (int)first_bmp < bitmaps_count &&
            bmp_count >= 1 &&
            (int)first_bmp + (int)bmp_count <= bitmaps_count) {
          /* Range is within bounds. Skip the warning if: the sequence is the
           * first starting at 0, or the next sequence starts exactly where
           * this one ends (contiguous allocation). */
          if ((i == 0 && first_bmp == 0) ||
              (next_seq != (void *)0 &&
               (int)*(short *)((char *)next_seq + 0x20) ==
                 (int)first_bmp + (int)bmp_count)) {
            goto skip_range_warning;
          }
        }
        error(2,
              "!!MUST BE FIXED: bitmap group '%s' sequence #%d"
              " references bitmaps [#%d..#%d]",
              tag_get_name(tag_index), i, (int)*(short *)((char *)seq + 0x20),
              (int)*(short *)((char *)seq + 0x20) +
                (int)*(short *)((char *)seq + 0x22));
      skip_range_warning:;
      }

      /* Check the sprite sub-block regardless of type. */
      sprites_block = (int *)((char *)seq + 0x34);
      sprites_count = *sprites_block;
      if (*(short *)tag == 3) {
        /* sprites group: must have at least one sprite per sequence */
        if (sprites_count < 1) {
          error(
            2, "!!MUST BE FIXED: bitmap group '%s' sequence #%d has %d sprites",
            tag_get_name(tag_index), i, sprites_count);
        } else {
          for (j = 0; j < sprites_count; j++) {
            sprite = tag_block_get_element(sprites_block, j, 0x20);
            bmp_idx = *(short *)sprite;
            bitmaps_count = *(int *)((char *)tag + 0x60);
            if (bmp_idx < 0 || (int)bmp_idx >= bitmaps_count) {
              error(2,
                    "!!MUST BE FIXED: bitmap group '%s' sequence #%d"
                    " sprite #%d references bitmap #%d",
                    tag_get_name(tag_index), i, j, (int)bmp_idx);
            }
          }
        }
      } else {
        /* non-sprite group: must have zero sprites per sequence */
        if (sprites_count > 0) {
          error(2,
                "!!MUST BE FIXED: bitmap group '%s' (type=%d) sequence #%d"
                " has %d sprites",
                tag_get_name(tag_index), (int)*(short *)tag, i, sprites_count);
        }
      }
    }
  }

  return success;
}

/*
 * FUN_00076ff0 -- get bitmap data element from a bitmap tag.
 *
 * Looks up a 'bitm' tag by index, then returns a pointer to the bitmap
 * data entry at the given bitmap_index within the tag's bitmap block
 * (offset 0x60, element size 0x30). Returns NULL on failure.
 */
void *FUN_00076ff0(int tag_index, short bitmap_index)
{
  int iVar1;
  void *uVar2;

  iVar1 = (int)tag_get(0x6269746d, tag_index);
  uVar2 = 0;
  if ((iVar1 != 0) && (bitmap_index >= 0)) {
    if ((int)bitmap_index < *(int *)(iVar1 + 0x60)) {
      uVar2 =
        tag_block_get_element((int *)(iVar1 + 0x60), (int)bitmap_index, 0x30);
    }
  }
  return uVar2;
}

/*
 * FUN_00077040 -- bitmap_group_get_bitmap: resolve sequence/frame index pair
 * to a bitmap data element in a 'bitm' tag.
 *
 * Walks the tag's sequence block to find the correct bitmap index, handling
 * direct-bitmap sequences (frame_count >= 1) and sprite sequences. Falls back
 * to frame_index if the resolved bitmap index is -1.
 *
 * Source TU: bitmap_group.c (assert strings confirm)
 */
void *FUN_00077040(int tag_index, short sequence_index, short frame_index)
{
  int tag;
  int sequence;
  short bitmap_idx;

  if (tag_index == -1)
    goto cleanup_null;
  if (sequence_index < 0 || frame_index < 0) {
    display_assert("sequence_index>=0 && frame_index>=0",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_group.c", 0x2a6, 1);
    system_exit(-1);
  }
  tag = (int)tag_get(0x6269746d, tag_index);
  if (tag == 0)
    goto cleanup_null;
  if (*(int *)(tag + 0x54) > 0) {
    sequence = (int)tag_block_get_element(
      (int *)(tag + 0x54), (int)sequence_index % *(int *)(tag + 0x54), 0x40);
    if (*(short *)(sequence + 0x22) > 0) {
      bitmap_idx =
        (short)((int)frame_index % (int)*(short *)(sequence + 0x22)) +
        *(short *)(sequence + 0x20);
      goto done;
    }
    if (*(int *)(sequence + 0x34) == 0)
      goto fallback;
    bitmap_idx = *(short *)tag_block_get_element((int *)(sequence + 0x34),
                                                 (int)frame_index, 0x20);
  done:
    if (bitmap_idx != -1)
      goto ret_check;
  }
fallback:
  bitmap_idx = frame_index;
ret_check:
  if (bitmap_idx < 0)
    goto cleanup_null;
  if ((int)bitmap_idx >= *(int *)(tag + 0x60))
    goto cleanup_null;
  return tag_block_get_element((int *)(tag + 0x60), (int)bitmap_idx, 0x30);
cleanup_null:
  return NULL;
}

/* FUN_00077590 (0x77590) — clone a bitmap: allocates a new bitmap of the same
 * type/format, copies pixel data from source to the clone, copies the flags
 * field (+0xe). */
void *FUN_00077590(void *bitmap)
{
  void *cloned;
  void *src_data;
  void *dst_data;
  int src_size;
  int dst_size;
  short type;

  if (bitmap == 0) {
    display_assert("source_bitmap",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x67, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)bitmap + 0x2c) == 0) {
    display_assert("source_bitmap->base_address",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x68, 1);
    system_exit(-1);
  }

  type = *(short *)((char *)bitmap + 0xa);
  cloned = 0;
  switch (type) {
  case 0:
    cloned = bitmap_2d_new(*(unsigned short *)((char *)bitmap + 4),
                           *(unsigned short *)((char *)bitmap + 6),
                           *(unsigned short *)((char *)bitmap + 0x14),
                           *(unsigned short *)((char *)bitmap + 0xc));
    break;
  case 1:
    cloned = bitmap_3d_new(*(unsigned short *)((char *)bitmap + 4),
                           *(unsigned short *)((char *)bitmap + 6),
                           *(unsigned short *)((char *)bitmap + 8),
                           *(unsigned short *)((char *)bitmap + 0x14),
                           *(unsigned short *)((char *)bitmap + 0xc));
    break;
  case 2:
    cloned = bitmap_cube_map_new(*(unsigned short *)((char *)bitmap + 4),
                                 *(unsigned short *)((char *)bitmap + 0x14),
                                 *(unsigned short *)((char *)bitmap + 0xc));
    break;
  default:
    display_assert("### ERROR unsupported bitmap type",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x83, 1);
    system_exit(-1);
    break;
  }

  if (cloned != 0 && *(int *)((char *)cloned + 0x2c) != 0) {
    src_data = bitmap_mipmap_address(bitmap, 0);
    dst_data = bitmap_mipmap_address(cloned, 0);
    src_size = bitmap_get_pixel_data_size(bitmap);
    dst_size = bitmap_get_pixel_data_size(cloned);
    if (src_size != dst_size) {
      display_assert(
        "bitmap_get_pixel_data_size(cloned_bitmap)==pixel_data_size",
        "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x8d, 1);
      system_exit(-1);
    }
    csmemcpy(dst_data, src_data, src_size);
    *(short *)((char *)cloned + 0xe) = *(short *)((char *)bitmap + 0xe);
    return cloned;
  }
  error(2, "### ERROR failed to allocate temporary bitmap");
  return cloned;
}

/*
 * FUN_00077720 -- box-filter 2x downscale for a 2D ARGB bitmap.
 *
 * Allocates a new ARGB (format 0xb) bitmap at (width/scale)x(height/scale),
 * averaging scale×scale source pixel blocks per output pixel.
 * Only includes non-transparent pixels in the average when alpha_weighted != 0.
 * brightness_adjust is added to the computed alpha channel value.
 *  = scale: box filter kernel size (must be >= 2).
 */
void *FUN_00077720(short scale , void *source_bitmap,
                   short brightness_adjust, char alpha_weighted)
{
  unsigned short src_width;
  int src_height;
  int kernel_x;
  int kernel_y;
  int new_width;
  int new_height;
  void *dst_bitmap;
  short dst_y;
  short dst_x;
  int src_y_base;
  int src_x_base;
  int inner_y;
  int inner_x;
  unsigned int *dst_pixel;
  unsigned int *src_pixel;
  unsigned int src_val;
  unsigned int src_alpha;
  int alpha_sum;
  int ch1_sum;
  int ch2_sum;
  int ch3_sum;
  int count;
  int half;
  int alpha_final;

  if (!bitmap_verify(source_bitmap, 1)) {
    display_assert("bitmap_verify(source_bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x105, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)source_bitmap + 0xa) != 0) {
    display_assert("source_bitmap->type==_bitmap_type_2d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x106, 1);
    system_exit(-1);
  }
  if (scale < 2) {
    display_assert("scale>1", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c",
                   0x107, 1);
    system_exit(-1);
  }

  src_width = *(unsigned short *)((char *)source_bitmap + 4);
  kernel_x = (int)(unsigned short)src_width;
  if (scale <= (short)src_width)
    kernel_x = (int)scale;

  src_height = (int)*(short *)((char *)source_bitmap + 6);
  kernel_y = src_height;
  if (scale <= (short)src_height)
    kernel_y = (int)scale;

  new_width = (int)(short)src_width / (int)(short)kernel_x;
  new_height = src_height / (int)(short)kernel_y;

  dst_bitmap = bitmap_2d_new((unsigned short)new_width,
                             (unsigned short)new_height, 0, 0xb);

  if (dst_bitmap == 0 || *(int *)((char *)dst_bitmap + 0x2c) == 0) {
    error(2, "### ERROR failed to allocate temporary bitmap");
    return dst_bitmap;
  }

  dst_y = 0;
  if (new_height > 0) {
    src_y_base = 0;
    do {
      if ((short)new_width > 0) {
        dst_x = 0;
        src_x_base = 0;
        do {
          alpha_sum = 0;
          ch1_sum = 0;
          ch2_sum = 0;
          ch3_sum = 0;
          count = 0;
          dst_pixel = (unsigned int *)bitmap_2d_address(dst_bitmap, dst_x,
                                                        (short)dst_y, 0);
          inner_y = 0;
          if ((short)kernel_y < 1)
            goto store_zero;
          do {
            inner_x = 0;
            if ((short)kernel_x > 0) {
              do {
                src_pixel = (unsigned int *)bitmap_2d_address(
                  source_bitmap, (short)(src_x_base + inner_x),
                  (short)(src_y_base + inner_y), 0);
                src_val = *src_pixel;
                src_alpha = src_val >> 0x18;
                if (src_alpha != 0 || alpha_weighted == '\0') {
                  alpha_sum += (int)src_alpha;
                  ch1_sum += (int)((src_val >> 0x10) & 0xff);
                  ch2_sum += (int)((src_val >> 0x8) & 0xff);
                  ch3_sum += (int)(src_val & 0xff);
                  count++;
                }
                inner_x++;
              } while ((short)inner_x < (short)kernel_x);
            }
            inner_y++;
          } while ((short)inner_y < (short)kernel_y);
          if (count == 0)
            goto store_zero;
          half = count / 2;
          alpha_final = (half + alpha_sum) / count + (int)brightness_adjust;
          if (alpha_final < 0)
            alpha_final = 0;
          else if (alpha_final > 0xff)
            alpha_final = 0xff;
          *dst_pixel =
            (unsigned int)((((ch1_sum + half) / count | alpha_final << 8) << 8 |
                            (half + ch2_sum) / count)
                             << 8 |
                           (ch3_sum + half) / count);
          goto skip_zero;
        store_zero:
          *dst_pixel = 0;
        skip_zero:
          dst_x++;
          src_x_base += kernel_x;
        } while ((short)dst_x < (short)new_width);
      }
      dst_y++;
      src_y_base += kernel_y;
      if ((short)dst_y >= (short)new_height)
        return dst_bitmap;
    } while (1);
  }
  return dst_bitmap;
}

/*
 * FUN_000779b0 -- box-filter downscale for a 3D (volume) ARGB bitmap.
 *
 * Allocates a new ARGB (format 0xb) 3D bitmap at
 * (width/scale)x(height/scale)x(depth/scale), averaging scale×scale×scale
 * source voxel blocks per output voxel. Only includes non-transparent voxels in
 * the average when alpha_weighted != 0. brightness_adjust is added to the
 * computed alpha channel value.
 *  = scale: box filter kernel size (must be >= 2).
 */
void *FUN_000779b0(short scale , void *source_bitmap,
                   short brightness_adjust, char alpha_weighted)
{
  unsigned short src_width;
  unsigned short src_height;
  unsigned short src_depth;
  int kernel_x;
  int kernel_y;
  int kernel_z;
  int new_width;
  int new_height;
  int new_depth;
  void *dst_bitmap;
  short dst_z;
  short dst_y;
  short dst_x;
  int src_z_base;
  int src_y_base;
  int src_x_base;
  int inner_z;
  int inner_y;
  int inner_x;
  unsigned int *dst_pixel;
  unsigned int *src_pixel;
  unsigned int src_val;
  unsigned int src_alpha;
  int alpha_sum;
  int ch1_sum;
  int ch2_sum;
  int ch3_sum;
  int count;
  int half;
  int alpha_final;
  short new_width_s;
  short new_height_s;
  short new_depth_s;

  if (!bitmap_verify(source_bitmap, 1)) {
    display_assert("bitmap_verify(source_bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x15d, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)source_bitmap + 0xa) != 1) {
    display_assert("source_bitmap->type==_bitmap_type_3d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x15e, 1);
    system_exit(-1);
  }
  if (scale < 2) {
    display_assert("scale>1", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c",
                   0x15f, 1);
    system_exit(-1);
  }

  src_width = *(unsigned short *)((char *)source_bitmap + 4);
  kernel_x = (int)(unsigned short)src_width;
  if (scale <= (short)src_width)
    kernel_x = (int)scale;

  src_height = *(unsigned short *)((char *)source_bitmap + 6);
  kernel_y = (int)(unsigned short)src_height;
  if (scale <= (short)src_height)
    kernel_y = (int)scale;

  src_depth = *(unsigned short *)((char *)source_bitmap + 8);
  kernel_z = (int)(unsigned short)src_depth;
  if (scale <= (short)src_depth)
    kernel_z = (int)scale;

  new_width = (int)(short)src_width / (int)(short)kernel_x;
  new_height = (int)(short)src_height / (int)(short)kernel_y;
  new_depth = (int)(short)src_depth / (int)(short)kernel_z;

  dst_bitmap =
    bitmap_3d_new((unsigned short)new_width, (unsigned short)new_height,
                  (unsigned short)new_depth, 0, 0xb);

  if (dst_bitmap == 0 || *(int *)((char *)dst_bitmap + 0x2c) == 0) {
    error(2, "### ERROR failed to allocate temporary bitmap");
    return dst_bitmap;
  }

  new_depth_s = (short)new_depth;
  dst_z = 0;
  if (new_depth_s > 0) {
    src_z_base = 0;
    do {
      new_height_s = (short)new_height;
      dst_y = 0;
      if (new_height_s > 0) {
        src_y_base = 0;
        do {
          new_width_s = (short)new_width;
          dst_x = 0;
          if (new_width_s > 0) {
            src_x_base = 0;
            do {
              alpha_sum = 0;
              ch1_sum = 0;
              ch2_sum = 0;
              ch3_sum = 0;
              count = 0;
              dst_pixel = (unsigned int *)bitmap_3d_address(
                dst_bitmap, dst_x, dst_y, (short)dst_z, 0);
              inner_z = 0;
              if ((short)kernel_z < 1)
                goto store_zero_3d;
              do {
                inner_y = 0;
                if ((short)kernel_y > 0) {
                  do {
                    inner_x = 0;
                    if ((short)kernel_x > 0) {
                      do {
                        src_pixel = (unsigned int *)bitmap_3d_address(
                          source_bitmap, (short)(src_x_base + inner_x),
                          (short)(src_y_base + inner_y),
                          (short)(src_z_base + inner_z), 0);
                        src_val = *src_pixel;
                        src_alpha = src_val >> 0x18;
                        if (src_alpha != 0 || alpha_weighted == '\0') {
                          alpha_sum += (int)src_alpha;
                          ch1_sum += (int)((src_val >> 0x10) & 0xff);
                          ch2_sum += (int)((src_val >> 0x8) & 0xff);
                          ch3_sum += (int)(src_val & 0xff);
                          count++;
                        }
                        inner_x++;
                      } while ((short)inner_x < (short)kernel_x);
                    }
                    inner_y++;
                  } while ((short)inner_y < (short)kernel_y);
                }
                inner_z++;
              } while ((short)inner_z < (short)kernel_z);
              if (count == 0)
                goto store_zero_3d;
              half = count / 2;
              alpha_final = (alpha_sum + half) / count + (int)brightness_adjust;
              if (alpha_final < 0)
                alpha_final = 0;
              else if (alpha_final > 0xff)
                alpha_final = 0xff;
              *dst_pixel =
                (unsigned int)((((ch1_sum + half) / count | alpha_final << 8)
                                  << 8 |
                                (half + ch2_sum) / count)
                                 << 8 |
                               (ch3_sum + half) / count);
              goto skip_zero_3d;
            store_zero_3d:
              *dst_pixel = 0;
            skip_zero_3d:
              dst_x++;
              src_x_base += kernel_x;
            } while ((short)dst_x < new_width_s);
          }
          dst_y++;
          src_y_base += kernel_y;
        } while ((short)dst_y < new_height_s);
      }
      src_z_base += kernel_z;
      dst_z++;
      if ((short)dst_z >= new_depth_s)
        return dst_bitmap;
    } while (1);
  }
  return dst_bitmap;
}

extern double floor(double);

/*
 * bitmap_fade (0x77e60) — Blend every pixel of a bitmap toward a solid color.
 *
 * fade_amount is a [0,1] intensity. If <= 0.0, the function is a no-op.
 * Each pixel channel is blended:
 *   result_n = (pixel_n * inv_alpha + color_n * alpha + 0x7f) >> 8
 * where alpha = (int)floor(clamped * 256.0f + 0.5f), inv_alpha = 256 - alpha.
 * Color channels: b0=blue(7:0), b1=green(15:8), b2=red(23:16), b3=alpha(31:24).
 *
 * Source: bitmap_utilities.obj, assert line 0x1f5 (501).
 */
void bitmap_fade(void *bitmap, unsigned int color, float fade_amount)
{
  float clamped;
  int alpha;
  int inv_alpha;
  int cb0, cb1, cb2, cb3;
  unsigned int *pixels;
  int count;
  int i;
  unsigned int pix;
  unsigned int r, g, b, a;

  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x1f5, 1);
    system_exit(-1);
  }

  if (fade_amount > 0.0f) {
    /* Clamp to [0, 1] using a local variable so MSVC emits all 3 fcomps */
    clamped = fade_amount;
    if (clamped < 0.0f) {
      clamped = 0.0f;
    } else if (clamped > 1.0f) {
      clamped = 1.0f;
    }

    /* alpha factor in [0, 256]; round-to-nearest via floor(x + 0.5) */
    alpha = (int)floor(clamped * 256.0f + 0.5f);
    inv_alpha = 0x100 - alpha;

    /* Pre-compute color_channel * alpha once before the pixel loop */
    cb2 = (int)((color >> 16) & 0xff) * alpha; /* red   */
    cb3 = (int)(color >> 24) * alpha; /* alpha */
    cb1 = (int)((color >> 8) & 0xff) * alpha; /* green */
    cb0 = (int)(color & 0xff) * alpha; /* blue  */

    pixels = (unsigned int *)bitmap_mipmap_address(bitmap, 0);
    count = bitmap_get_pixel_count(bitmap);

    for (i = 0; i < count; i++) {
      pix = pixels[i];
      r = ((pix >> 16) & 0xff) * inv_alpha;
      a = (pix >> 24) * inv_alpha;
      g = ((pix >> 8) & 0xff) * inv_alpha;
      b = (pix & 0xff) * inv_alpha;

      r = (r + cb2 + 0x7f) >> 8;
      a = (a + cb3 + 0x7f) >> 8;
      g = (g + cb1 + 0x7f) >> 8;
      b = (b + cb0 + 0x7f) >> 8;

      pixels[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }
  }
}

/*
 * FUN_00077ff0 -- 2D bitmap separable Gaussian filter.
 * Horizontal pass (pixels->tmp) then vertical pass (tmp->pixels).
 * Circular boundary wrapping. filter_coefficients: 2*filter_radius+1 entries.
 */
void FUN_00077ff0(void *bitmap, short filter_radius, short *filter_coefficients)
{
  unsigned int pix_size;
  void *pixels;
  void *tmp;
  short y, x;
  short k;
  short width;
  unsigned char shift;
  int rounding;
  int row_base;
  int wrap_x;
  int y_wrap;
  unsigned int count;
  short *kptr;
  unsigned int pix;
  int coeff;
  int a, r, g, b;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x250, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 10) != 0) {
    display_assert("bitmap->type==_bitmap_type_2d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x251, 1);
    system_exit(-1);
  }
  if (!filter_coefficients) {
    display_assert("filter_coefficients",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x252, 1);
    system_exit(-1);
  }
  if ((filter_radius <= *(short *)((char *)bitmap + 4)) &&
      (filter_radius <= *(short *)((char *)bitmap + 6))) {
    pix_size = (unsigned int)bitmap_get_pixel_data_size(bitmap);
    pixels = bitmap_mipmap_address(bitmap, 0);
    tmp = debug_malloc(pix_size, 0,
                       "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x25d);
    if (!tmp) {
      error(2, "### ERROR failed to allocate temporary buffer");
      return;
    }
    /* horizontal pass: pixels -> tmp */
    y = 0;
    if (0 < *(short *)((char *)bitmap + 6)) {
      width = *(short *)((char *)bitmap + 4);
      do {
        x = 0;
        if (0 < width) {
          shift = (unsigned char)filter_radius * 2;
          k = -filter_radius;
          rounding = 1 << (shift - 1);
          do {
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            if (k <= filter_radius) {
              row_base = (int)y * (int)width;
              wrap_x = (int)x + (int)k + (int)width;
              count = (unsigned int)(unsigned short)(filter_radius - k + 1);
              kptr = filter_coefficients + filter_radius + k;
              do {
                pix =
                  *(unsigned int *)((char *)pixels +
                                    ((short)(wrap_x % (int)width) + row_base) *
                                      4);
                coeff = (int)*kptr;
                a += (pix >> 24) * coeff;
                r += ((pix >> 16) & 0xff) * coeff;
                g += ((pix >> 8) & 0xff) * coeff;
                b += (pix & 0xff) * coeff;
                wrap_x++;
                count--;
                kptr++;
                width = *(short *)((char *)bitmap + 4);
              } while (count != 0);
            }
            *(unsigned int *)((char *)tmp +
                              ((int)width * (int)y + (int)x) * 4) =
              ((((rounding + a) >> shift) << 8 | (r + rounding) >> shift) << 8 |
               (rounding + g) >> shift)
                << 8 |
              (rounding + b) >> shift;
            width = *(short *)((char *)bitmap + 4);
            x++;
          } while (x < width);
        }
        y++;
      } while (y < *(short *)((char *)bitmap + 6));
    }
    /* vertical pass: tmp -> pixels */
    y = 0;
    if (0 < *(short *)((char *)bitmap + 6)) {
      width = *(short *)((char *)bitmap + 4);
      do {
        x = 0;
        if (0 < width) {
          shift = (unsigned char)filter_radius * 2;
          k = -filter_radius;
          rounding = 1 << (shift - 1);
          do {
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            if (k <= filter_radius) {
              y_wrap = (int)k + (int)*(short *)((char *)bitmap + 6) + (int)y;
              count = (unsigned int)(unsigned short)(filter_radius - k + 1);
              kptr = filter_coefficients + filter_radius + k;
              do {
                pix =
                  *(unsigned int *)((char *)tmp +
                                    ((short)(y_wrap %
                                             (int)*(short *)((char *)bitmap +
                                                             6)) *
                                       (int)width +
                                     (int)x) *
                                      4);
                coeff = (int)*kptr;
                a += (pix >> 24) * coeff;
                r += ((pix >> 16) & 0xff) * coeff;
                g += ((pix >> 8) & 0xff) * coeff;
                b += (pix & 0xff) * coeff;
                y_wrap++;
                count--;
                kptr++;
              } while (count != 0);
            }
            *(unsigned int *)((char *)pixels +
                              ((int)width * (int)y + (int)x) * 4) =
              ((((rounding + a) >> shift) << 8 | (rounding + r) >> shift) << 8 |
               (rounding + g) >> shift)
                << 8 |
              (rounding + b) >> shift;
            width = *(short *)((char *)bitmap + 4);
            x++;
          } while (x < width);
        }
        y++;
      } while (y < *(short *)((char *)bitmap + 6));
    }
    debug_free(tmp, "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x2a5);
    return;
  }
  crt_fprintf(
    (void *)0x331050,
    "### WARNING tried to smooth a bitmap with a filter which is too large\n");
  crt_fflush((void *)0x331050);
}

/*
 * FUN_00078460 -- 3D bitmap separable Gaussian filter.
 * X-pass (pixels->tmp), Y-pass (tmp->pixels), Z-pass (pixels->tmp),
 * then csmemcpy(pixels, tmp). Circular boundary wrapping.
 */
void FUN_00078460(void *bitmap, short filter_radius, short *filter_coefficients)
{
  char *bmp;
  unsigned int pix_size;
  void *pixels;
  void *tmp;
  short z, y, x;
  short k;
  short width;
  unsigned char shift;
  int rounding;
  int wrap;
  int row_base;
  unsigned int count;
  short *kptr;
  unsigned int pix;
  int coeff;
  int a, r, g, b;

  bmp = (char *)bitmap;
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x2ba, 1);
    system_exit(-1);
  }
  if (*(short *)(bmp + 10) != 1) {
    display_assert("bitmap->type==_bitmap_type_3d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x2bb, 1);
    system_exit(-1);
  }
  if (!filter_coefficients) {
    display_assert("filter_coefficients",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x2bc, 1);
    system_exit(-1);
  }
  if ((filter_radius <= *(short *)(bmp + 4)) &&
      (filter_radius <= *(short *)(bmp + 6)) &&
      (filter_radius <= *(short *)(bmp + 8))) {
    pix_size = (unsigned int)bitmap_get_pixel_data_size(bitmap);
    pixels = bitmap_mipmap_address(bitmap, 0);
    tmp = debug_malloc(pix_size, 0,
                       "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x2c7);
    if (!tmp) {
      error(2, "### ERROR failed to allocate temporary buffer");
      return;
    }
    /* X-pass: pixels -> tmp */
    z = 0;
    if (0 < *(short *)(bmp + 8)) {
      do {
        y = 0;
        if (0 < *(short *)(bmp + 6)) {
          width = *(short *)(bmp + 4);
          do {
            x = 0;
            if (0 < width) {
              shift = (unsigned char)filter_radius * 2;
              k = -filter_radius;
              rounding = 1 << (shift - 1);
              do {
                a = 0;
                r = 0;
                g = 0;
                b = 0;
                if (k <= filter_radius) {
                  row_base = (int)*(short *)(bmp + 6) * (int)z + (int)y;
                  wrap = (int)x + (int)k + (int)width;
                  count = (unsigned int)(unsigned short)(filter_radius - k + 1);
                  kptr = filter_coefficients + filter_radius + k;
                  do {
                    pix = *(unsigned int *)((char *)pixels +
                                            ((short)(wrap % (int)width) +
                                             row_base * (int)width) *
                                              4);
                    coeff = (int)*kptr;
                    a += (pix >> 24) * coeff;
                    r += ((pix >> 16) & 0xff) * coeff;
                    g += ((pix >> 8) & 0xff) * coeff;
                    b += (pix & 0xff) * coeff;
                    wrap++;
                    count--;
                    kptr++;
                    width = *(short *)(bmp + 4);
                  } while (count != 0);
                }
                *(unsigned int *)((char *)tmp +
                                  (((int)*(short *)(bmp + 6) * (int)z +
                                    (int)y) *
                                     (int)width +
                                   (int)x) *
                                    4) =
                  ((((rounding + a) >> shift) << 8 | (rounding + r) >> shift)
                     << 8 |
                   (rounding + g) >> shift)
                    << 8 |
                  (rounding + b) >> shift;
                width = *(short *)(bmp + 4);
                x++;
              } while (x < width);
            }
            y++;
          } while (y < *(short *)(bmp + 6));
        }
        z++;
      } while (z < *(short *)(bmp + 8));
    }
    /* Y-pass: tmp -> pixels */
    z = 0;
    if (0 < *(short *)(bmp + 8)) {
      do {
        y = 0;
        if (0 < *(short *)(bmp + 6)) {
          width = *(short *)(bmp + 4);
          do {
            x = 0;
            if (0 < width) {
              shift = (unsigned char)filter_radius * 2;
              k = -filter_radius;
              rounding = 1 << (shift - 1);
              do {
                a = 0;
                r = 0;
                g = 0;
                b = 0;
                if (k <= filter_radius) {
                  wrap = (int)y + (int)k + (int)*(short *)(bmp + 6);
                  count = (unsigned int)(unsigned short)(filter_radius - k + 1);
                  kptr = filter_coefficients + filter_radius + k;
                  do {
                    pix =
                      *(unsigned int *)((char *)tmp +
                                        (((short)(wrap %
                                                  (int)*(short *)(bmp + 6)) +
                                          (int)z * (int)*(short *)(bmp + 6)) *
                                           (int)width +
                                         (int)x) *
                                          4);
                    coeff = (int)*kptr;
                    a += (pix >> 24) * coeff;
                    r += ((pix >> 16) & 0xff) * coeff;
                    g += ((pix >> 8) & 0xff) * coeff;
                    b += (pix & 0xff) * coeff;
                    kptr++;
                    wrap++;
                    count--;
                  } while (count != 0);
                }
                *(unsigned int *)((char *)pixels +
                                  (((int)*(short *)(bmp + 6) * (int)z +
                                    (int)y) *
                                     (int)width +
                                   (int)x) *
                                    4) =
                  ((((rounding + a) >> shift) << 8 | (rounding + r) >> shift)
                     << 8 |
                   (rounding + g) >> shift)
                    << 8 |
                  (rounding + b) >> shift;
                width = *(short *)(bmp + 4);
                x++;
              } while (x < width);
            }
            y++;
          } while (y < *(short *)(bmp + 6));
        }
        z++;
      } while (z < *(short *)(bmp + 8));
    }
    /* Z-pass: pixels -> tmp */
    z = 0;
    if (0 < *(short *)(bmp + 8)) {
      do {
        y = 0;
        if (0 < *(short *)(bmp + 6)) {
          width = *(short *)(bmp + 4);
          do {
            x = 0;
            if (0 < width) {
              shift = (unsigned char)filter_radius * 2;
              k = -filter_radius;
              rounding = 1 << (shift - 1);
              do {
                a = 0;
                r = 0;
                g = 0;
                b = 0;
                if (k <= filter_radius) {
                  wrap = (int)*(short *)(bmp + 8) + (int)k + (int)z;
                  count = (unsigned int)(unsigned short)(filter_radius - k + 1);
                  kptr = filter_coefficients + filter_radius + k;
                  do {
                    pix =
                      *(unsigned int *)((char *)pixels +
                                        (((short)(wrap %
                                                  (int)*(short *)(bmp + 8)) *
                                            (int)*(short *)(bmp + 6) +
                                          (int)y) *
                                           (int)width +
                                         (int)x) *
                                          4);
                    coeff = (int)*kptr;
                    a += (pix >> 24) * coeff;
                    r += ((pix >> 16) & 0xff) * coeff;
                    g += ((pix >> 8) & 0xff) * coeff;
                    b += (pix & 0xff) * coeff;
                    kptr++;
                    wrap++;
                    count--;
                  } while (count != 0);
                }
                *(unsigned int *)((char *)tmp +
                                  (((int)*(short *)(bmp + 6) * (int)z +
                                    (int)y) *
                                     (int)width +
                                   (int)x) *
                                    4) =
                  ((((rounding + a) >> shift) << 8 | (rounding + r) >> shift)
                     << 8 |
                   (rounding + g) >> shift)
                    << 8 |
                  (rounding + b) >> shift;
                width = *(short *)(bmp + 4);
                x++;
              } while (x < width);
            }
            y++;
          } while (y < *(short *)(bmp + 6));
        }
        z++;
      } while (z < *(short *)(bmp + 8));
    }
    csmemcpy(pixels, tmp, pix_size);
    debug_free(tmp, "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x33e);
    return;
  }
  crt_fprintf(
    (void *)0x331050,
    "### WARNING tried to smooth a bitmap with a filter which is too large\n");
  crt_fflush((void *)0x331050);
}

/*
 * FUN_00078b80 -- cube_map smooth stub.
 *
 * Validates the bitmap (must be cube_map type) and the filter_coefficients
 * pointer, then prints a warning that smoothing a cube map is not supported
 * and returns without doing any work.
 *
 * ABI: bitmap passed in ESI (@ESI). Two stack params: filter_radius,
 * filter_coefficients.
 */
void FUN_00078b80(int filter_radius, short *filter_coefficients,
                  void *bitmap )
{
  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x353, 1);
    system_exit(-1);
  }

  /* assert bitmap->type == _bitmap_type_cube_map */
  if (*(short *)((char *)bitmap + 0xa) != 2) {
    display_assert("bitmap->type==_bitmap_type_cube_map",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x354, 1);
    system_exit(-1);
  }

  /* assert filter_coefficients != NULL */
  if (filter_coefficients == 0) {
    display_assert("filter_coefficients",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x355, 1);
    system_exit(-1);
  }

  crt_fprintf((void *)0x331050, "### WARNING tried to smooth a cube map",
              (void *)0x261f2c);
  crt_fflush((void *)0x331050);
}

/*
 * FUN_000790b0 -- 3D bitmap sharpen stub.
 *
 * Validates the bitmap (must be 3D type) and positive/negative table pointers,
 * then prints a warning that sharpening a 3D bitmap is not supported
 * and returns without doing any work.
 *
 * ABI: bitmap passed in ESI (@ESI). Three stack params: unused, positive_table,
 * negative_table.
 */
void FUN_000790b0(int unused, int positive_table, int negative_table,
                  void *bitmap )
{
  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3e2, 1);
    system_exit(-1);
  }

  /* assert bitmap->type == _bitmap_type_3d */
  if (*(short *)((char *)bitmap + 0xa) != 1) {
    display_assert("bitmap->type==_bitmap_type_3d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3e3, 1);
    system_exit(-1);
  }

  /* assert positive_table != NULL */
  if (positive_table == 0) {
    display_assert("positive_table",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3e4, 1);
    system_exit(-1);
  }

  /* assert negative_table != NULL */
  if (negative_table == 0) {
    display_assert("negative_table",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3e5, 1);
    system_exit(-1);
  }

  crt_fprintf((void *)0x331050, "### WARNING tried to sharpen a 3d bitmap",
              (void *)0x261f2c);
  crt_fflush((void *)0x331050);
}

/* FUN_00079180 (0x79180) — cube map sharpen stub. Validates bitmap (@esi) is
 * cube type, checks positive/negative table pointers, then prints warning and
 * returns. */
void FUN_00079180(int unused, int positive_table, int negative_table,
                  void *bitmap )
{
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3f3, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 0xa) != 2) {
    display_assert("bitmap->type==_bitmap_type_cube_map",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3f4, 1);
    system_exit(-1);
  }
  if (positive_table == 0) {
    display_assert("positive_table",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3f5, 1);
    system_exit(-1);
  }
  if (negative_table == 0) {
    display_assert("negative_table",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x3f6, 1);
    system_exit(-1);
  }
  crt_fprintf((void *)0x331050, "### WARNING tried to sharpen a cube map",
              (void *)0x261f2c);
  crt_fflush((void *)0x331050);
}

/* FUN_00079250 (0x79250) — 2D bitmap alpha-bleed: for each transparent pixel
 * (alpha==0), copies RGB from the first non-transparent neighbor found in the
 * 3x3 neighborhood. Runs `passes` iterations over the whole bitmap, writing
 * each pass into a temp buffer then memcpy'ing back.
 *  = passes (must be > 0). */
void FUN_00079250(short passes , void *bitmap)
{
  short width;
  short height;
  int size;
  unsigned int *temp_buf;
  unsigned int pass_counter;
  int y;
  int x;
  unsigned int *row_ptr;
  unsigned int pixel;
  void *dest;
  int dy;
  int iy;
  int dx;
  int ix;
  unsigned int *neighbor_ptr;
  char found;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x41d, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 0xa) != 0) {
    display_assert("bitmap->type==_bitmap_type_2d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x41e, 1);
    system_exit(-1);
  }
  if (passes <= 0) {
    display_assert("passes>0", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c",
                   0x41f, 1);
    system_exit(-1);
  }
  size = bitmap_get_pixel_data_size(bitmap);
  temp_buf = (unsigned int *)debug_malloc(
    size, 0, "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x422);
  if (temp_buf == NULL) {
    error(2, "### ERROR failed to allocate temporary buffer");
    return;
  }
  pass_counter = (unsigned int)(unsigned short)passes;
  if ((short)pass_counter > 0) {
    do {
      width = *(short *)((char *)bitmap + 4);
      height = *(short *)((char *)bitmap + 6);
      y = 0;
      if (height > 0) {
        do {
          row_ptr = (unsigned int *)bitmap_2d_address(bitmap, 0, y, 0);
          x = 0;
          if (width > 0) {
            do {
              pixel = *(unsigned int *)((unsigned char *)row_ptr + x * 4);
              if ((pixel & 0xff000000) == 0) {
                found = 0;
                dy = -1;
                iy = y - 1;
                do {
                  if (dy > 1)
                    break;
                  if (!found) {
                    dx = -1;
                    ix = x - 1;
                    do {
                      if (dx > 1)
                        break;
                      if ((short)ix >= 0 && (short)iy >= 0 &&
                          (short)ix < width && (short)iy < height) {
                        neighbor_ptr =
                          (unsigned int *)bitmap_2d_address(bitmap, ix, iy, 0);
                        if (*neighbor_ptr != 0) {
                          pixel = *neighbor_ptr & 0x00ffffff;
                          found = 1;
                        }
                      }
                      dx++;
                      ix++;
                    } while (!found);
                  }
                  dy++;
                  iy++;
                } while (!found);
              }
              *(unsigned int *)((unsigned char *)temp_buf + x * 4 +
                                (int)width * y * 4) = pixel;
              x++;
            } while ((short)x < width);
          }
          y++;
        } while ((short)y < height);
      }
      dest = bitmap_mipmap_address(bitmap, 0);
      csmemcpy(dest, temp_buf, size);
      pass_counter--;
    } while (pass_counter != 0);
  }
  debug_free(temp_buf, "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x462);
}

/*
 * FUN_00079590 -- cube_map alpha_bleed stub.
 *
 * Validates the bitmap (must be cube_map type) and that passes > 0,
 * then prints a warning that alpha-bleeding a cube map is not supported
 * and returns without doing any work.
 *
 * ABI: bitmap passed in ESI (@ESI). One stack param: passes (short).
 */
void FUN_00079590(short passes, void *bitmap )
{
  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x4a1, 1);
    system_exit(-1);
  }

  /* assert bitmap->type == _bitmap_type_cube_map */
  if (*(short *)((char *)bitmap + 0xa) != 2) {
    display_assert("bitmap->type==_bitmap_type_cube_map",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x4a2, 1);
    system_exit(-1);
  }

  /* assert passes > 0 */
  if (passes <= 0) {
    display_assert("passes>0", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c",
                   0x4a3, 1);
    system_exit(-1);
  }

  crt_fprintf((void *)0x331050,
              "### WARNING tried to alpha-bleed a cube map (skipping)");
  crt_fflush((void *)0x331050);
}

/*
 * FUN_00079630 -- cube_map height_map stub.
 *
 * Validates the bitmap (must be cube_map type) and that bump_height > 0.0f,
 * then prints a warning that using a cube map as a height map is not supported
 * and returns without doing any work.
 *
 * ABI: bitmap passed in ESI (@ESI). One stack param: bump_height (float).
 */
void FUN_00079630(float bump_height, void *bitmap )
{
  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x55c, 1);
    system_exit(-1);
  }

  /* assert bitmap->type == _bitmap_type_cube_map */
  if (*(short *)((char *)bitmap + 0xa) != 2) {
    display_assert("bitmap->type==_bitmap_type_cube_map",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x55d, 1);
    system_exit(-1);
  }

  /* assert bump_height > 0.0f */
  if (!(bump_height > *(float *)0x2533c0)) {
    display_assert("bump_height>0.0f",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x55e, 1);
    system_exit(-1);
  }

  crt_fprintf((void *)0x331050,
              "### WARNING tried to use a cube map as a height map\r\n");
  crt_fflush((void *)0x331050);
}

/*
 * real_rgb_color_brightness -- real_rgb_color_brightness: compute luminance of
 * an RGB color.
 *
 * Returns the dot product of the color with standard luminance coefficients
 * (0.299, 0.587, 0.114) stored at globals 0x2647c0-c8.
 */
float real_rgb_color_brightness(float *color)
{
  return color[0] * *(float *)0x2647c0 + color[1] * *(float *)0x2647c4 +
         color[2] * *(float *)0x2647c8;
}

float *bitmap_clone(float *rgb, float *hsv_out)
{
  float max_component;
  float min_component;
  float chroma;

  if (rgb[1] > rgb[2]) {
    max_component = rgb[1];
  } else {
    max_component = rgb[2];
  }
  if (max_component < rgb[0]) {
    max_component = rgb[0];
  } else {
    if (rgb[1] > rgb[2]) {
      max_component = rgb[1];
    } else {
      max_component = rgb[2];
    }
  }

  if (rgb[1] > rgb[2]) {
    min_component = rgb[2];
  } else {
    min_component = rgb[1];
  }
  if (min_component < rgb[0]) {
    if (rgb[1] > rgb[2]) {
      min_component = rgb[2];
    } else {
      min_component = rgb[1];
    }
  } else {
    min_component = rgb[0];
  }

  chroma = max_component - min_component;

  if (hsv_out == (float *)0) {
    display_assert("hsv", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c",
                   0x8b2, true);
    system_exit(-1);
  }
  if (rgb == hsv_out) {
    display_assert("rgb!=(real_rgb_color *)hsv",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x8b3,
                   true);
    system_exit(-1);
  }

  hsv_out[2] = max_component;
  if (max_component == *(float *)0x2533c0) {
    hsv_out[1] = *(float *)0x2533c0;
  } else {
    hsv_out[1] = chroma / max_component;
  }

  if (hsv_out[1] == *(float *)0x2533c0) {
    hsv_out[0] = 0.0f;
    return hsv_out;
  }
  if (rgb[0] == max_component) {
    hsv_out[0] = (rgb[1] - rgb[2]) / chroma;
  } else if (rgb[1] == max_component) {
    hsv_out[0] = (rgb[2] - rgb[0]) / chroma + *(float *)0x253f40;
  } else {
    hsv_out[0] = (rgb[0] - rgb[1]) / chroma + *(float *)0x2533d8;
  }
  hsv_out[0] = hsv_out[0] * *(float *)0x2647d4;
  if (hsv_out[0] < *(float *)0x2533c0)
    hsv_out[0] = hsv_out[0] + *(float *)0x2533c8;
  return hsv_out;
}

float *real_hsv_color_to_real_rgb_color(float *hsv, float *rgb_out)
{
  float scaled_hue;
  float f;
  float p;
  float q;
  float t;
  int sector;

  if (rgb_out == (float *)0) {
    display_assert("rgb", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c",
                   0x8df, true);
    system_exit(-1);
  }

  if (rgb_out == hsv) {
    display_assert("rgb!=(real_rgb_color *)hsv",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x8e1,
                   true);
    system_exit(-1);
  }

  if (hsv[1] == *(float *)0x2533c0) {
    rgb_out[0] = hsv[2];
    rgb_out[1] = hsv[2];
    rgb_out[2] = hsv[2];
    return rgb_out;
  }

  scaled_hue = hsv[0] * *(float *)0x254640;
  sector = (int)scaled_hue;
  if ((float)sector > scaled_hue)
    sector--;

  f = scaled_hue - (float)sector;
  p = (*(float *)0x2533c8 - hsv[1]) * hsv[2];
  q = (*(float *)0x2533c8 - f * hsv[1]) * hsv[2];
  t = (*(float *)0x2533c8 - (*(float *)0x2533c8 - f) * hsv[1]) * hsv[2];

  switch (sector) {
  case 0:
    rgb_out[0] = hsv[2];
    rgb_out[1] = t;
    rgb_out[2] = p;
    return rgb_out;
  case 1:
    rgb_out[0] = q;
    rgb_out[1] = hsv[2];
    rgb_out[2] = p;
    return rgb_out;
  case 2:
    rgb_out[0] = p;
    rgb_out[1] = hsv[2];
    rgb_out[2] = t;
    return rgb_out;
  case 3:
    rgb_out[0] = p;
    rgb_out[1] = q;
    rgb_out[2] = hsv[2];
    return rgb_out;
  case 4:
    rgb_out[0] = t;
    rgb_out[1] = p;
    rgb_out[2] = hsv[2];
    return rgb_out;
  case 5:
    rgb_out[0] = hsv[2];
    rgb_out[1] = p;
    rgb_out[2] = q;
    return rgb_out;
  default:
    return rgb_out;
  }
}

/*
 * argb_color_to_real_argb_color -- argb_color_to_real_argb_color: convert 4
 * unsigned shorts to 4 floats, scaled by 1/65535.
 *
 * Each component is zero-extended from ushort to int, then converted to float
 * and multiplied by the scale factor at 0x264154.
 */
void argb_color_to_real_argb_color(unsigned short *src, float *dst)
{
  int val;

  val = src[0];
  dst[0] = (float)val * *(float *)0x264154;
  val = src[1];
  dst[1] = (float)val * *(float *)0x264154;
  val = src[2];
  dst[2] = (float)val * *(float *)0x264154;
  val = src[3];
  dst[3] = (float)val * *(float *)0x264154;
}

/*
 * rgb_color_to_real_rgb_color -- rgb_color_to_real_rgb_color: convert 3
 * unsigned shorts to 3 floats, scaled by 1/65535.
 *
 * Same pattern as argb_color_to_real_argb_color but only 3 components.
 */
void rgb_color_to_real_rgb_color(unsigned short *src, float *dst)
{
  int val;

  val = src[0];
  dst[0] = (float)val * *(float *)0x264154;
  val = src[1];
  dst[1] = (float)val * *(float *)0x264154;
  val = src[2];
  dst[2] = (float)val * *(float *)0x264154;
}

/*
 * pixel32_to_real_argb_color -- pixel32_to_real_argb_color: extract ARGB from a
 * packed uint32 into 4 floats, scaled by 1/255.
 *
 * Byte layout: bits 31-24 = A, 23-16 = R, 15-8 = G, 7-0 = B.
 * Uses MSVC's unsigned-to-float pattern (FILD + TEST/JGE/FADD fixup).
 */
void pixel32_to_real_argb_color(unsigned int color, float *dst)
{
  unsigned int a, r, g, b;

  a = color >> 24;
  dst[0] = (float)a * *(float *)0x261518;
  r = (color >> 16) & 0xff;
  dst[1] = (float)r * *(float *)0x261518;
  g = (color >> 8) & 0xff;
  dst[2] = (float)g * *(float *)0x261518;
  b = color & 0xff;
  dst[3] = (float)b * *(float *)0x261518;
}

/*
 * pixel32_to_real_rgb_color -- pixel32_to_real_rgb_color: extract RGB from a
 * packed uint32 into 3 floats, scaled by 1/255.
 *
 * Byte layout: bits 23-16 = R, 15-8 = G, 7-0 = B (alpha ignored).
 * Uses MSVC's unsigned-to-float pattern (FILD + TEST/JGE/FADD fixup).
 */
void pixel32_to_real_rgb_color(unsigned int color, float *dst)
{
  unsigned int r, g, b;

  r = (color >> 16) & 0xff;
  dst[0] = (float)r * *(float *)0x261518;
  g = (color >> 8) & 0xff;
  dst[1] = (float)g * *(float *)0x261518;
  b = color & 0xff;
  dst[2] = (float)b * *(float *)0x261518;
}

bool valid_real_rgb_color(float *rgb)
{
  uint32_t component_bits;

  component_bits = *(uint32_t *)&rgb[0];
  if ((component_bits & 0x7f800000) == 0x7f800000)
    return false;

  component_bits = *(uint32_t *)&rgb[1];
  if ((component_bits & 0x7f800000) == 0x7f800000)
    return false;

  component_bits = *(uint32_t *)&rgb[2];
  if ((component_bits & 0x7f800000) == 0x7f800000)
    return false;

  if (rgb[0] >= *(float *)0x2533c0 && rgb[0] <= *(float *)0x2533c8 &&
      rgb[1] >= *(float *)0x2533c0 && rgb[1] <= *(float *)0x2533c8 &&
      rgb[2] >= *(float *)0x2533c0 && rgb[2] <= *(float *)0x2533c8)
    return true;

  return false;
}

/*
 * bitmap_shrink -- bitmap_shrink: dispatcher for bitmap mipmap shrinking.
 *
 * Validates the bitmap. If mipmap_count < 2, delegates to FUN_00077590.
 * Otherwise dispatches based on bitmap->type: 2D -> FUN_00077720,
 * 3D -> FUN_000779b0, cube_map -> FUN_00077cd0.
 * Returns a pointer to the shrunk bitmap (or NULL on error).
 */
void *bitmap_shrink(void *bitmap, short mipmap_count, int param_3, int param_4)
{
  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(source_bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0xe1, 1);
    system_exit(-1);
  }

  if (mipmap_count <= 1) {
    return FUN_00077590(bitmap);
  }

  switch (*(short *)((char *)bitmap + 0xa)) {
  case 0:
    return FUN_00077720((short)mipmap_count, bitmap, (short)param_3,
                        (char)param_4);
  case 1:
    return FUN_000779b0((short)mipmap_count, bitmap, (short)param_3,
                        (char)param_4);
  case 2:
    return FUN_00077cd0(bitmap, mipmap_count, param_3, param_4);
  default:
    display_assert("### ERROR unupported bitmap type",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0xf3, 1);
    system_exit(-1);
    return (void *)0;
  }
}

/*
 * bitmap_smooth (0x7b1b0) -- dispatcher for bitmap smoothing by type.
 *
 * Validates the bitmap, checks filter_size range, then builds a 1-D
 * Gaussian kernel of radius floor(smooth_factor) by iterating Pascal's
 * triangle accumulation into a 10-element short array at DAT_00334560.
 * Dispatches: type 0 -> FUN_00077ff0, type 1 -> FUN_00078460,
 * type 2 -> FUN_00078b80 (cube map, stub).
 */
void bitmap_smooth(void *pixel_data, float smooth_factor)
{
  short *psVar4;
  int filter_radius;
  int iVar5;
  unsigned int diameter;
  short *filter_table;

  filter_radius = (int)smooth_factor;

  if (!bitmap_verify(pixel_data, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x21e, 1);
    system_exit(-1);
  }

  if (smooth_factor > *(float *)0x253f34) {
    display_assert("filter_size<=(float)MAXIMUM_FILTER_SIZE",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x21f, 1);
    system_exit(-1);
  }

  if ((float)(int16_t)filter_radius <= *(float *)0x2533c0) {
    return;
  }

  filter_table = (short *)0x334560;
  csmemset(filter_table, 0, 0x14);
  if ((int16_t)(filter_radius * 2) >= 0) {
    diameter = (unsigned short)(filter_radius * 2 + 1);
    do {
      psVar4 = (short *)0x334572;
      iVar5 = 9;
      do {
        *psVar4 = *psVar4 + *(psVar4 - 1);
        psVar4 = psVar4 - 1;
        iVar5 = iVar5 - 1;
      } while (iVar5 != 0);
      diameter = diameter - 1;
      *(short *)0x334560 = 1;
    } while (diameter != 0);
  }

  switch ((int16_t)(*(short *)((char *)pixel_data + 0xa))) {
  case 0:
    FUN_00077ff0(pixel_data, filter_radius, filter_table);
    return;
  case 1:
    FUN_00078460(pixel_data, filter_radius, filter_table);
    return;
  case 2:
    FUN_00078b80(filter_radius, filter_table, pixel_data);
    return;
  default:
    display_assert("### ERROR unsupported bitmap type",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x244, 1);
    system_exit(-1);
    return;
  }
}

/*
 * bitmap_alpha_bleed -- bitmap_alpha_bleed: dispatcher for alpha bleed by
 * bitmap type.
 *
 * Validates the bitmap, checks that passes > 0, then dispatches based on
 * bitmap->type: 2D -> FUN_00079250, 3D -> FUN_00079480 (bitmap in EDI),
 * cube_map -> FUN_00079590 (bitmap in ESI).
 * On unsupported type, fires an assert.
 */
void bitmap_alpha_bleed(void *bitmap, short passes)
{
  /* bitmap_verify(bitmap, TRUE) */
  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x402, 1);
    system_exit(-1);
  }

  if (passes <= 0) {
    return;
  }

  switch (*(short *)((char *)bitmap + 0xa)) {
  case 0:
    FUN_00079250(passes, bitmap);
    break;
  case 1:
    FUN_00079480(passes, bitmap);
    break;
  case 2:
    FUN_00079590(passes, bitmap);
    break;
  default:
    display_assert("### ERROR unsupported bitmap type",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x410, 1);
    system_exit(-1);
    break;
  }
}
/* --- bitmap_utilities.obj batch drafts (2026-07-26) --- */

/* FUN_00075800 (0x75800) — readable C lift (restored pre-naked). */
void FUN_00075800(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp (int16_t)eax, word ptr [0x334138] -> jge 0x7597e */
  /* test edi, edi -> je 0x75868 */
  display_assert((char *)0x0026208c, (char *)0x002616f0, 1944, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ecx + 6] -> jne 0x7588c */
  bitmap_cube_map_new(0, 0, 11);
  crt_fprintf((void *)0x00331050, (char *)0x00262060);
  crt_fflush((void *)0x00331050);
  /* test edi, edi -> je 0x759fa */
  /* test eax, eax -> je 0x759fa */
  /* relift: cmp word ptr [esi + 4], (int16_t)ecx -> jne 0x759d9 */
  /* relift: cmp (int16_t)edx, word ptr [edi + 4] -> jne 0x759b8 */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 6] -> jne 0x759b8 */
  ((void(*)(void))bitmap_cube_map_face_insert)();
  /* test (char)eax, (char)eax -> je 0x7590b */
  bitmap_delete((void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x75961 */
  /* cmp (int16_t)ebx, 6 -> jne 0x75961 */
  FUN_00075380((void *)0);
  /* cmp (int16_t)ebx, -1 -> je 0x75954 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp word ptr [eax + 0x20], -1 -> jne 0x75950 */
  bitmap_delete((void *)(uintptr_t)edi);
  bitmap_delete((void *)(uintptr_t)ecx);
  /* test edi, edi -> je 0x759ae */
  /* test (char)eax, (char)eax -> je 0x759a5 */
  crt_fprintf((void *)0x00331050, (char *)0x00262030);
  crt_fflush((void *)0x00331050);
  bitmap_delete((void *)(uintptr_t)edi);
  crt_fprintf((void *)0x00331050, (char *)0x00261ffc);
  crt_fflush((void *)0x00331050);
  crt_fprintf((void *)0x00331050, (char *)0x00261fd0);
  crt_fflush((void *)0x00331050);
  /* test (char)eax, (char)eax -> jne 0x7590b */
  error(0, (char *)0x00261f98);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_00075a20 (0x75a20) — readable C lift (restored pre-naked). */
void FUN_00075a20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: cmp (int16_t)ebx, word ptr [0x334138] -> jge 0x75ad9 */
  /* test eax, eax -> je 0x75ad2 */
  /* relift: cmp word ptr [eax + 4], (int16_t)ecx -> jg 0x75ab9 */
  /* relift: cmp word ptr [eax + 6], (int16_t)ecx -> jle 0x75ad2 */
  error(0, (char *)0x00262210);
  /* test dl, dl -> jne 0x75a92 */
  /* test dl, dl -> je 0x75b1a */
  /* relift: test byte ptr [ecx + 6], 4 -> je 0x75af8 */
  error(0, (char *)0x00262188);
  FUN_000747d0();
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x1c] -> jge 0x75dc7 */
  bitmap_2d_new(0, 0, 0, 11);
  /* test eax, eax -> je 0x75d61 */
  FUN_00077510((void *)(uintptr_t)esi, 0);
  /* relift: cmp (int16_t)eax, word ptr [0x334138] -> jge 0x75d33 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  ((void(*)(void))FUN_0011fef0)();
  /* test (char)ebx, 8 -> jne 0x75c23 */
  /* relift: cmp word ptr [edx + 0x30], 1 -> jne 0x75c23 */
  /* cmp (int16_t)ecx, -1 -> jne 0x75ce5 */
  FUN_00072490();
  bitmap_delete((void *)(uintptr_t)ecx);
  FUN_00075380((void *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x75d74 */
  bitmap_delete((void *)(uintptr_t)esi);
  error(0, (char *)0x00262140);
  ((void(*)(void))FUN_0011fd10)();
  crt_fprintf((void *)0x00331050, (char *)0x00262110);
  crt_fflush((void *)0x00331050);
  ((void(*)(void))FUN_0011fe80)();
  /* test dl, dl -> je 0x75b23 */
  crt_fprintf((void *)0x00331050, (char *)0);
  crt_fflush((void *)0x00331050);
  crt_fprintf((void *)0x00331050, (char *)0x002620cc);
  crt_fflush((void *)0x00331050);
  error(0, (char *)0x002620a0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}



/* FUN_00075e70 (0x75e70) — readable C lift (restored pre-naked). */
void FUN_00075e70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0026184c, (char *)0x002616f0, 802, 0);
  system_exit(0);
  FUN_00073e40();
  /* test (char)eax, (char)eax -> je 0x762cd */
  bitmap_2d_new(0, 0, 0, 0);
  /* relift: test byte ptr [edx + 6], 8 -> je 0x75f1f */
  bitmap_2d_address((void *)(uintptr_t)ebx, 0, 0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x1a] -> jge 0x760be */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x75fc7 */
  /* cmp eax, ecx -> je 0x75fc5 */
  /* relift: cmp eax, dword ptr [0x334144] -> je 0x75fc5 */
  /* relift: cmp eax, dword ptr [0x334140] -> jne 0x75fc7 */
  /* relift: cmp word ptr [ecx + 4], 0 -> jne 0x76011 */
  /* test esi, 0xff000000 -> jne 0x76011 */
  /* test esi, 0xffffff -> je 0x76011 */
  /* test (char)eax, (char)eax -> jne 0x76011 */
  crt_fprintf((void *)0x00331050, (char *)0x002623f0);
  crt_fflush((void *)0x00331050);
  /* relift: cmp word ptr [ecx + 2], 0 -> jne 0x7607e */
  /* test edi, edi -> je 0x7605a */
  /* cmp edi, 0xff -> je 0x76056 */
  /* test (char)eax, (char)eax -> jne 0x76056 */
  crt_fprintf((void *)0x00331050, (char *)0x00262398);
  crt_fflush((void *)0x00331050);
  /* test edi, edi -> jne 0x76078 */
  /* cmp edx, eax -> je 0x76074 */
  /* test (char)eax, (char)eax -> jne 0x76078 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x76093 */
  /* cmp (int16_t)eax, 1 -> je 0x76093 */
  /* cmp (int16_t)eax, 2 -> jne 0x760a8 */
  /* relift: cmp word ptr [ecx], 4 -> jne 0x760a8 */
  error(0, (char *)0x00262358);
  /* test (int16_t)eax, (int16_t)eax -> je 0x7626a */
  /* cmp (int16_t)eax, 4 -> je 0x7626a */
  /* test (char)ecx, (char)ecx -> jne 0x76146 */
  /* cmp (int16_t)eax, 2 -> jne 0x76120 */
  FUN_00073b00();
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x002622c0);
  bitmap_delete((void *)(uintptr_t)ebx);
  /* cmp (int16_t)eax, 0x400 -> jge 0x7624d */
  /* relift: cmp word ptr [edx], 3 -> jne 0x76116 */
  tag_block_add_element((void *)(uintptr_t)eax);
  /* cmp (int16_t)edi, -1 -> je 0x76235 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  error(0, (char *)0x0026228c);
  error(0, (char *)0x00261798);
  FUN_00075380((void *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x7610d */
  /* relift: cmp word ptr [ecx + 0x20], -1 -> jne 0x7629e */
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x002617dc);
  crt_fprintf((void *)0x00331050, (char *)0x00262254);
  crt_fflush((void *)0x00331050);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_00076300 (0x76300) — readable C lift (restored pre-naked). */
void FUN_00076300(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)eax, (char)eax -> je 0x76336 */
  error(0, (char *)0x002624b8);
  /* cmp eax, 4 -> ja 0x763d3 */
  tag_block_add_element((void *)(uintptr_t)ecx);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* mem[0x00334158] = eax */
  FUN_00075e70();
  error(0, (char *)0x0026247c);
  error(0, (char *)0x00262444);
  display_assert((char *)0x00261ea0, (char *)0x002616f0, 422, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
}


/* FUN_00076410 (0x76410) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b76410_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b76410_exitfn)(int) = system_exit;
static void * (*const b76410_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static void (*const b76410_c75e70)(void) = FUN_00075e70;

__attribute__((naked, noinline))
char FUN_00076410(int param_1 __attribute__((unused)), short param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testw %%di, %%di\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jge .LFUN_00076410_1\n\t"
      "pushl $1\n\t"
      "pushl $0x234\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x26253c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076410_1:\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "cmpw %%di, %%si\n\t"
      "jge .LFUN_00076410_2\n\t"
      "pushl $1\n\t"
      "pushl $0x235\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x262530\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076410_2:\n\t"
      "movl 0x334150, %%eax\n\t"
      "cmpw 0x6(%%eax), %%si\n\t"
      "jle .LFUN_00076410_3\n\t"
      "pushl $1\n\t"
      "pushl $0x236\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x26250c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076410_3:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00076410_5\n\t"
      ".LFUN_00076410_4:\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "jmp .LFUN_00076410_5\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00076410_5:\n\t"
      "movl 0x334150, %%ecx\n\t"
      "cmpw 0x4(%%ecx), %%bx\n\t"
      "jge .LFUN_00076410_35\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw $0x7fff, -0xe(%%ebp)\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "movw $0x8000, -0xa(%%ebp)\n\t"
      "movw %%si, -0xc(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00076410_6:\n\t"
      "cmpw $2, %%di\n\t"
      "je .LFUN_00076410_20\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "jge .LFUN_00076410_15\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_00076410_7:\n\t"
      "movl 0x334150, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c940]\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x334140, %%ecx\n\t"
      "andl $0xffffff, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_00076410_8\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "jmp .LFUN_00076410_14\n\t"
      ".LFUN_00076410_8:\n\t"
      "cmpl 0x33413c, %%eax\n\t"
      "je .LFUN_00076410_14\n\t"
      "movswl %%di, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "je .LFUN_00076410_9\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00076410_10\n\t"
      "jmp .LFUN_00076410_14\n\t"
      ".LFUN_00076410_9:\n\t"
      "movl $1, %%edi\n\t"
      "movw %%bx, -0xe(%%ebp)\n\t"
      ".LFUN_00076410_10:\n\t"
      "movw -0x10(%%ebp), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jle .LFUN_00076410_11\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "jmp .LFUN_00076410_12\n\t"
      ".LFUN_00076410_11:\n\t"
      "movw -0x8(%%ebp), %%dx\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      ".LFUN_00076410_12:\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jle .LFUN_00076410_13\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      ".LFUN_00076410_13:\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "movw %%bx, -0xa(%%ebp)\n\t"
      ".LFUN_00076410_14:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "cmpw 0xc(%%ebp), %%si\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00076410_7\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00076410_16\n\t"
      ".LFUN_00076410_15:\n\t"
      "movb 0x334149, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00076410_17\n\t"
      ".LFUN_00076410_16:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00076410_17\n\t"
      "cmpw $1, %%di\n\t"
      "jmp .LFUN_00076410_18\n\t"
      ".LFUN_00076410_17:\n\t"
      "cmpw $1, %%di\n\t"
      "jne .LFUN_00076410_19\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      ".LFUN_00076410_18:\n\t"
      "jne .LFUN_00076410_19\n\t"
      "movl $2, %%edi\n\t"
      ".LFUN_00076410_19:\n\t"
      "movl 0x334150, %%ecx\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x4(%%ecx), %%bx\n\t"
      "jl .LFUN_00076410_6\n\t"
      ".LFUN_00076410_20:\n\t"
      "testw %%di, %%di\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "je .LFUN_00076410_34\n\t"
      "incw -0xa(%%ebp)\n\t"
      "movl 0x33414c, %%eax\n\t"
      "incw -0xc(%%ebp)\n\t"
      "testb $8, 0x6(%%eax)\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "je .LFUN_00076410_33\n\t"
      "movw %%dx, %%cx\n\t"
      "cmpw %%cx, %%di\n\t"
      "jge .LFUN_00076410_26\n\t"
      "movl -0xe(%%ebp), %%ebx\n\t"
      "jmp .LFUN_00076410_21\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00076410_21:\n\t"
      "movw -0xa(%%ebp), %%dx\n\t"
      "cmpw %%dx, -0xe(%%ebp)\n\t"
      "movl %%ebx, %%esi\n\t"
      "jge .LFUN_00076410_24\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00076410_22:\n\t"
      "movl 0x334150, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c940]\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x33413c, %%ecx\n\t"
      "andl $0xffffff, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_00076410_23\n\t"
      "incl %%esi\n\t"
      "cmpw -0xa(%%ebp), %%si\n\t"
      "jl .LFUN_00076410_22\n\t"
      "jmp .LFUN_00076410_24\n\t"
      ".LFUN_00076410_23:\n\t"
      "cmpw -0xa(%%ebp), %%si\n\t"
      "jl .LFUN_00076410_25\n\t"
      ".LFUN_00076410_24:\n\t"
      "incl %%edi\n\t"
      "cmpw -0xc(%%ebp), %%di\n\t"
      "jl .LFUN_00076410_21\n\t"
      ".LFUN_00076410_25:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_00076410_26:\n\t"
      "movw %%di, %%ax\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "addl $-2, %%edi\n\t"
      "cmpw %%ax, %%di\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "jl .LFUN_00076410_32\n\t"
      "movw -0x12(%%ebp), %%bx\n\t"
      ".LFUN_00076410_27:\n\t"
      "movl -0x16(%%ebp), %%esi\n\t"
      "cmpw %%bx, %%si\n\t"
      "jge .LFUN_00076410_30\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00076410_28:\n\t"
      "movl 0x334150, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c940]\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x33413c, %%ecx\n\t"
      "andl $0xffffff, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_00076410_29\n\t"
      "incl %%esi\n\t"
      "cmpw %%bx, %%si\n\t"
      "jl .LFUN_00076410_28\n\t"
      "jmp .LFUN_00076410_30\n\t"
      ".LFUN_00076410_29:\n\t"
      "cmpw %%bx, %%si\n\t"
      "jl .LFUN_00076410_31\n\t"
      ".LFUN_00076410_30:\n\t"
      "decl %%edi\n\t"
      "cmpw -0x18(%%ebp), %%di\n\t"
      "jge .LFUN_00076410_27\n\t"
      ".LFUN_00076410_31:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_00076410_32:\n\t"
      "incl %%edi\n\t"
      "movw %%di, -0x14(%%ebp)\n\t"
      ".LFUN_00076410_33:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "call *%[c75e70]\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      ".LFUN_00076410_34:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00076410_4\n\t"
      ".LFUN_00076410_35:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b76410_assert), [exitfn] "m"(b76410_exitfn), [c7c940] "m"(b76410_c7c940), [c75e70] "m"(b76410_c75e70)
      : "memory");
}
#else
#error "FUN_00076410: clang naked draft required"
#endif


/* bitmap_2d_sharpen (0x78c30) — XBE naked draft (batch 243). */
#if defined(__clang__)
static bool (*const b78c30_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b78c30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b78c30_exitfn)(int) = system_exit;
static int (*const b78c30_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;
static void * (*const b78c30_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void * (*const b78c30_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static void * (*const b78c30_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static void * (*const b78c30_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b78c30_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b78c30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void bitmap_2d_sharpen(void *bitmap __attribute__((unused)), float amount __attribute__((unused)), int positive_table __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_2d_sharpen_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38c\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261814\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_sharpen_1:\n\t"
      "cmpw $0, 0xa(%%ebx)\n\t"
      "je .Lbitmap_2d_sharpen_2\n\t"
      "pushl $1\n\t"
      "pushl $0x38d\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264334\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_sharpen_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lbitmap_2d_sharpen_3\n\t"
      "pushl $1\n\t"
      "pushl $0x38e\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2643d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_sharpen_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lbitmap_2d_sharpen_4\n\t"
      "pushl $1\n\t"
      "pushl $0x38f\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2643c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_sharpen_4:\n\t"
      "movl $3, %%eax\n\t"
      "cmpw %%ax, 0x4(%%ebx)\n\t"
      "jl .Lbitmap_2d_sharpen_22\n\t"
      "cmpw %%ax, 0x6(%%ebx)\n\t"
      "jl .Lbitmap_2d_sharpen_22\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7e040]\n\t"
      "pushl $0x398\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "je .Lbitmap_2d_sharpen_21\n\t"
      "movw 0x6(%%ebx), %%cx\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%edi, -0x38(%%ebp)\n\t"
      "jle .Lbitmap_2d_sharpen_20\n\t"
      ".Lbitmap_2d_sharpen_5:\n\t"
      "testw %%di, %%di\n\t"
      "leal -0x1(%%edi), %%eax\n\t"
      "jg .Lbitmap_2d_sharpen_6\n\t"
      "leal -0x1(%%ecx), %%eax\n\t"
      ".Lbitmap_2d_sharpen_6:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "jge .Lbitmap_2d_sharpen_7\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jmp .Lbitmap_2d_sharpen_8\n\t"
      ".Lbitmap_2d_sharpen_7:\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      ".Lbitmap_2d_sharpen_8:\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7c940]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c7c940]\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c7c940]\n\t"
      "movswl 0x4(%%ebx), %%ecx\n\t"
      "imull -0x34(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "leal (%%edx,%%ecx,4), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "leal 0x4(%%ecx), %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "addl $0x30, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      ".Lbitmap_2d_sharpen_9:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "shlw $2, %%cx\n\t"
      "addl %%edi, %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movzbl (%%ecx,%%edx,1), %%eax\n\t"
      "movswl (%%esi,%%eax,2), %%eax\n\t"
      "movzbl -0x4(%%edx), %%ecx\n\t"
      "movswl (%%ebx,%%ecx,2), %%ecx\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movzbl (%%eax,%%edx,1), %%eax\n\t"
      "movswl (%%esi,%%eax,2), %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movzbl (%%ebx,%%eax,1), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "movzbl (%%eax), %%eax\n\t"
      "movswl (%%esi,%%eax,2), %%eax\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movzbl (%%edx), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movzbl -0x4(%%eax,%%ebx,1), %%eax\n\t"
      "movswl (%%esi,%%eax,2), %%eax\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movzbl -0x4(%%eax,%%ebx,1), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movzbl -0x4(%%eax,%%ebx,1), %%eax\n\t"
      "movswl (%%esi,%%eax,2), %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "jns .Lbitmap_2d_sharpen_10\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .Lbitmap_2d_sharpen_11\n\t"
      ".Lbitmap_2d_sharpen_10:\n\t"
      "cmpl $0xff, %%ecx\n\t"
      "jle .Lbitmap_2d_sharpen_11\n\t"
      "movl $0xff, %%ecx\n\t"
      ".Lbitmap_2d_sharpen_11:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x28(%%ebp), %%ebx\n\t"
      "incl %%edi\n\t"
      "movb %%cl, (%%ebx,%%eax,1)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "incl %%edx\n\t"
      "incl %%eax\n\t"
      "cmpw $4, %%di\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .Lbitmap_2d_sharpen_9\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "shlw $2, %%cx\n\t"
      "subl $4, %%ecx\n\t"
      "cmpw %%cx, %%di\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jge .Lbitmap_2d_sharpen_15\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%edx,1), %%ebx\n\t"
      "movl %%ebx, -0x2c(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "leal -0x4(%%eax,%%ebx,1), %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "subl %%edi, %%ecx\n\t"
      "leal 0x4(%%eax,%%ebx,1), %%eax\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "subl %%ebx, %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "addl %%ecx, %%edi\n\t"
      ".Lbitmap_2d_sharpen_12:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movzbl (%%ecx,%%eax,1), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "movzbl -0x4(%%eax), %%ecx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movswl (%%ebx,%%ecx,2), %%ecx\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movzbl (%%edx,%%eax,1), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movzbl (%%ebx,%%edx,1), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movzbl -0x8(%%eax), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movzbl 0x4(%%edx), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "movzbl (%%edx), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movzbl (%%eax), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movzbl (%%edx), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "jns .Lbitmap_2d_sharpen_13\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .Lbitmap_2d_sharpen_14\n\t"
      ".Lbitmap_2d_sharpen_13:\n\t"
      "cmpl $0xff, %%ecx\n\t"
      "jle .Lbitmap_2d_sharpen_14\n\t"
      "movl $0xff, %%ecx\n\t"
      ".Lbitmap_2d_sharpen_14:\n\t"
      "movl -0x28(%%ebp), %%ebx\n\t"
      "movb %%cl, (%%ebx,%%edx,1)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "incl %%edx\n\t"
      "decl %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "jne .Lbitmap_2d_sharpen_12\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Lbitmap_2d_sharpen_15:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "cmpw %%cx, %%di\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jge .Lbitmap_2d_sharpen_19\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%edx,1), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal -0x4(%%eax,%%ecx,1), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lbitmap_2d_sharpen_16:\n\t"
      "movswl 0x4(%%ebx), %%ebx\n\t"
      "shlw $2, %%bx\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movzbl (%%edx,%%ecx,1), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "movzbl 0x4(%%eax), %%ecx\n\t"
      "movswl (%%ebx,%%ecx,2), %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movzbl (%%edx,%%eax,1), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movzbl (%%edx,%%eax,1), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movzbl 0x4(%%edx,%%ebx,1), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movzbl 0x4(%%edx,%%ebx,1), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movzbl 0x4(%%edx,%%ebx,1), %%edx\n\t"
      "movswl (%%esi,%%edx,2), %%edx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movzbl (%%edx), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movzbl (%%eax), %%ebx\n\t"
      "movswl (%%esi,%%ebx,2), %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "jns .Lbitmap_2d_sharpen_17\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .Lbitmap_2d_sharpen_18\n\t"
      ".Lbitmap_2d_sharpen_17:\n\t"
      "cmpl $0xff, %%ecx\n\t"
      "jle .Lbitmap_2d_sharpen_18\n\t"
      "movl $0xff, %%ecx\n\t"
      ".Lbitmap_2d_sharpen_18:\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      "incl %%edi\n\t"
      "movb %%cl, (%%ebx,%%edx,1)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "incl %%eax\n\t"
      "incl %%edx\n\t"
      "cmpw -0x20(%%ebp), %%di\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jl .Lbitmap_2d_sharpen_16\n\t"
      ".Lbitmap_2d_sharpen_19:\n\t"
      "movl -0x38(%%ebp), %%edi\n\t"
      "movw 0x6(%%ebx), %%cx\n\t"
      "incl %%edi\n\t"
      "cmpw %%cx, %%di\n\t"
      "movl %%edi, -0x38(%%ebp)\n\t"
      "jl .Lbitmap_2d_sharpen_5\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      ".Lbitmap_2d_sharpen_20:\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d000]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl $0x3d1\n\t"
      "pushl $0x2641f0\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_sharpen_21:\n\t"
      "pushl $0x2642f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lbitmap_2d_sharpen_22:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b78c30_c7d470), [assert] "m"(b78c30_assert), [exitfn] "m"(b78c30_exitfn), [c7e040] "m"(b78c30_c7e040), [c8ee60] "m"(b78c30_c8ee60), [c7c940] "m"(b78c30_c7c940), [c7d000] "m"(b78c30_c7d000), [c8e0b0] "m"(b78c30_c8e0b0), [c8ef70] "m"(b78c30_c8ef70), [c8f390] "m"(b78c30_c8f390)
      : "memory");
}
#else
#error "bitmap_2d_sharpen: clang naked draft required"
#endif


/* FUN_000796e0 (0x796e0) — validate 2D mipmap compress args then halt.
 *
 * Checks source (@edi) and destination (@esi) bitmaps and mip index (@bx),
 * then always display_assert(NULL, ..., 0x69f) — unimplemented body.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x63c-0x69f.
 */
void FUN_000796e0(short destination_mipmap_index /* @<bx> */,
                  void *destination_bitmap /* @<esi> */,
                  void *source_bitmap /* @<edi> */)
{
  unsigned short tmp;
  int value;

  if (!bitmap_verify(source_bitmap, 1)) {
    display_assert("bitmap_verify(source_bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x63c, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)source_bitmap + 0xa) != 0) {
    display_assert("source_bitmap->type==_bitmap_type_2d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x63d, 1);
    system_exit(-1);
  }
  if (!bitmap_verify(destination_bitmap, 0)) {
    display_assert("bitmap_verify(destination_bitmap, FALSE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x63f, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)destination_bitmap + 0xa) != 0) {
    display_assert("destination_bitmap->type==_bitmap_type_2d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x640, 1);
    system_exit(-1);
  }
  if (destination_mipmap_index < 0 ||
      destination_mipmap_index > *(short *)((char *)destination_bitmap + 0x14)) {
    display_assert("destination_mipmap_index>=0 && destination_mipmap_index<=destination_bitmap->mipmap_count",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x641, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)destination_bitmap + 4);
  if ((short)(tmp >> destination_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> destination_mipmap_index;
  if (value != (int)*(short *)((char *)source_bitmap + 4)) {
    display_assert("MAX(1, destination_bitmap->width >>destination_mipmap_index)==source_bitmap->width",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x642, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)destination_bitmap + 6);
  if ((short)(tmp >> destination_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> destination_mipmap_index;
  if (value != (int)*(short *)((char *)source_bitmap + 6)) {
    display_assert("MAX(1, destination_bitmap->height>>destination_mipmap_index)==source_bitmap->height",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x643, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)destination_bitmap + 8);
  if ((short)(tmp >> destination_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> destination_mipmap_index;
  if (value != (int)*(short *)((char *)source_bitmap + 8)) {
    display_assert("MAX(1, destination_bitmap->depth >>destination_mipmap_index)==source_bitmap->depth",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x644, 1);
    system_exit(-1);
  }

  if ((*(unsigned char *)((char *)destination_bitmap + 0xe) & 2) == 0) {
    display_assert("TEST_FLAG(destination_bitmap->flags, _bitmap_compressed_bit)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x645, 1);
    system_exit(-1);
  }

  display_assert((const char *)0, "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x69f, 1);
  system_exit(-1);
}


/* FUN_000798e0 (0x798e0) — XBE naked draft (batch 245). */
#if defined(__clang__)
static bool (*const b798e0_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b798e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b798e0_exitfn)(int) = system_exit;
static void * (*const b798e0_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static void (*const b798e0_c7e560)(void) = bitmap_3d_slice_insert;
static void (*const b798e0_c796e0)(void) = FUN_000796e0;
static void (*const b798e0_c7e7e0)(void *src_bitmap, void *dst_bitmap, int face, int slice) = bitmap_cube_map_face_extract;
static void (*const b798e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b798e0_c7c8f0)(void *) = bitmap_delete;

__attribute__((naked, noinline))
void FUN_000798e0(void *source_bitmap, void *destination_bitmap, short destination_mipmap_index, int unused)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $1, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000798e0_1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6af\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261aa4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_1:\n\t"
      "cmpw %%di, 0xa(%%ebx)\n\t"
      "je .LFUN_000798e0_2\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6b0\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x26424c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_2:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000798e0_3\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6b2\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261974\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_3:\n\t"
      "cmpw %%di, 0xa(%%esi)\n\t"
      "je .LFUN_000798e0_4\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6b3\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264638\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000798e0_5\n\t"
      "cmpw 0x14(%%esi), %%ax\n\t"
      "jle .LFUN_000798e0_6\n\t"
      ".LFUN_000798e0_5:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6b4\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2618e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "movw %%ax, %%cx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarw %%cl, %%di\n\t"
      "cmpw $1, %%di\n\t"
      "jge .LFUN_000798e0_7\n\t"
      "movl $1, %%edx\n\t"
      "jmp .LFUN_000798e0_8\n\t"
      ".LFUN_000798e0_7:\n\t"
      "movswl %%dx, %%edx\n\t"
      "movb %%al, %%cl\n\t"
      "sarl %%cl, %%edx\n\t"
      ".LFUN_000798e0_8:\n\t"
      "movswl 0x4(%%ebx), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_000798e0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x6b5\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2645b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_9:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "movw %%ax, %%cx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarw %%cl, %%di\n\t"
      "cmpw $1, %%di\n\t"
      "jge .LFUN_000798e0_10\n\t"
      "movl $1, %%edx\n\t"
      "jmp .LFUN_000798e0_11\n\t"
      ".LFUN_000798e0_10:\n\t"
      "movswl %%dx, %%edx\n\t"
      "movb %%al, %%cl\n\t"
      "sarl %%cl, %%edx\n\t"
      ".LFUN_000798e0_11:\n\t"
      "movswl 0x6(%%ebx), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_000798e0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x6b6\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264560\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_12:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%esi), %%dx\n\t"
      "movw %%ax, %%cx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarw %%cl, %%di\n\t"
      "cmpw $1, %%di\n\t"
      "jge .LFUN_000798e0_13\n\t"
      "movl $1, %%edx\n\t"
      "jmp .LFUN_000798e0_14\n\t"
      ".LFUN_000798e0_13:\n\t"
      "movswl %%dx, %%edx\n\t"
      "movb %%al, %%cl\n\t"
      "sarl %%cl, %%edx\n\t"
      ".LFUN_000798e0_14:\n\t"
      "movswl 0x8(%%ebx), %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_000798e0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x6b7\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_15:\n\t"
      "testb $2, 0xe(%%esi)\n\t"
      "jne .LFUN_000798e0_16\n\t"
      "pushl $1\n\t"
      "pushl $0x6b8\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2644c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000798e0_16:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%ebx), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%ebx), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7e0b0]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%ebx), %%dx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LFUN_000798e0_19\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000798e0_19\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000798e0_19\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000798e0_19\n\t"
      "cmpw $0, 0x8(%%ebx)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .LFUN_000798e0_20\n\t"
      "jmp .LFUN_000798e0_18\n\t"
      ".LFUN_000798e0_17:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000798e0_18:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7e560]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c796e0]\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c7e7e0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x8(%%edx), %%bx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jl .LFUN_000798e0_17\n\t"
      "jmp .LFUN_000798e0_20\n\t"
      ".LFUN_000798e0_19:\n\t"
      "pushl $0x264194\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000798e0_20:\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c8f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b798e0_c7d470), [assert] "m"(b798e0_assert), [exitfn] "m"(b798e0_exitfn), [c7e0b0] "m"(b798e0_c7e0b0), [c7e560] "m"(b798e0_c7e560), [c796e0] "m"(b798e0_c796e0), [c7e7e0] "m"(b798e0_c7e7e0), [c8f390] "m"(b798e0_c8f390), [c7c8f0] "m"(b798e0_c7c8f0)
      : "memory");
}
#else
#error "FUN_000798e0: clang naked draft required"
#endif


/* FUN_00079bb0 (0x79bb0) — XBE naked draft (batch 246). */
#if defined(__clang__)
static bool (*const b79bb0_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b79bb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b79bb0_exitfn)(int) = system_exit;
static void * (*const b79bb0_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static void (*const b79bb0_c7ea60)(void) = FUN_0007ea60;
static void (*const b79bb0_c796e0)(void) = FUN_000796e0;
static void (*const b79bb0_c7ece0)(void) = bitmap_cube_map_face_insert;
static void (*const b79bb0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b79bb0_c7c8f0)(void *) = bitmap_delete;

__attribute__((naked, noinline))
void FUN_00079bb0(void *source_bitmap, void *destination_bitmap, short destination_mipmap_index, int unused)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00079bb0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x6fa\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261aa4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_1:\n\t"
      "movl $2, %%ebx\n\t"
      "cmpw %%bx, 0xa(%%esi)\n\t"
      "je .LFUN_00079bb0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x6fb\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264274\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00079bb0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x6fd\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261974\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_3:\n\t"
      "cmpw %%bx, 0xa(%%edi)\n\t"
      "je .LFUN_00079bb0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x6fe\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_4:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_00079bb0_5\n\t"
      "cmpw 0x14(%%edi), %%bx\n\t"
      "jle .LFUN_00079bb0_6\n\t"
      ".LFUN_00079bb0_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x6ff\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2618e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00079bb0_7\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00079bb0_8\n\t"
      ".LFUN_00079bb0_7:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00079bb0_8:\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00079bb0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x700\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2645b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00079bb0_10\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00079bb0_11\n\t"
      ".LFUN_00079bb0_10:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00079bb0_11:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00079bb0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x701\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264560\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_12:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00079bb0_13\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00079bb0_14\n\t"
      ".LFUN_00079bb0_13:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00079bb0_14:\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00079bb0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x702\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_15:\n\t"
      "testb $2, 0xe(%%edi)\n\t"
      "jne .LFUN_00079bb0_16\n\t"
      "pushl $1\n\t"
      "pushl $0x703\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2644c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079bb0_16:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%esi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e0b0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xc(%%edx), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LFUN_00079bb0_18\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00079bb0_18\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00079bb0_18\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00079bb0_18\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00079bb0_17:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7ea60]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c796e0]\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c7ece0]\n\t"
      "addl $0x24, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpw $6, %%bx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jl .LFUN_00079bb0_17\n\t"
      "jmp .LFUN_00079bb0_19\n\t"
      ".LFUN_00079bb0_18:\n\t"
      "pushl $0x264194\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00079bb0_19:\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c8f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b79bb0_c7d470), [assert] "m"(b79bb0_assert), [exitfn] "m"(b79bb0_exitfn), [c7e0b0] "m"(b79bb0_c7e0b0), [c7ea60] "m"(b79bb0_c7ea60), [c796e0] "m"(b79bb0_c796e0), [c7ece0] "m"(b79bb0_c7ece0), [c8f390] "m"(b79bb0_c8f390), [c7c8f0] "m"(b79bb0_c7c8f0)
      : "memory");
}
#else
#error "FUN_00079bb0: clang naked draft required"
#endif


/* FUN_00079e70 (0x79e70) — XBE naked draft (batch 243). */
#if defined(__clang__)
static bool (*const b79e70_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b79e70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b79e70_exitfn)(int) = system_exit;
static void * (*const b79e70_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static short (*const b79e70_c7d780)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_height;
static short (*const b79e70_c7d6e0)(void *bitmap, int mipmap_index) = bitmap_mipmap_width;
static void (*const b79e70_c71890)(void) = FUN_00071890;
static void (*const b79e70_c717b0)(void) = FUN_000717b0;
static void (*const b79e70_c71400)(void) = FUN_00071400;
static void * (*const b79e70_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;

__attribute__((naked, noinline))
void FUN_00079e70(void *source_bitmap __attribute__((unused)), void *destination_bitmap __attribute__((unused)), short source_mipmap_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x64, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00079e70_1\n\t"
      "pushl $1\n\t"
      "pushl $0x766\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261b44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_1:\n\t"
      "cmpw $0, 0xa(%%esi)\n\t"
      "je .LFUN_00079e70_2\n\t"
      "pushl $1\n\t"
      "pushl $0x767\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264224\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_2:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_00079e70_3\n\t"
      "cmpw 0x14(%%esi), %%bx\n\t"
      "jle .LFUN_00079e70_4\n\t"
      ".LFUN_00079e70_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x768\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00079e70_5\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00079e70_6\n\t"
      ".LFUN_00079e70_5:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00079e70_6:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movswl 0x4(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00079e70_7\n\t"
      "pushl $1\n\t"
      "pushl $0x769\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264770\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00079e70_8\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00079e70_9\n\t"
      ".LFUN_00079e70_8:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00079e70_9:\n\t"
      "movswl 0x6(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00079e70_10\n\t"
      "pushl $1\n\t"
      "pushl $0x76a\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_00079e70_11\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00079e70_12\n\t"
      ".LFUN_00079e70_11:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_00079e70_12:\n\t"
      "movswl 0x8(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00079e70_13\n\t"
      "pushl $1\n\t"
      "pushl $0x76b\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2646d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_13:\n\t"
      "testb $2, 0xe(%%esi)\n\t"
      "jne .LFUN_00079e70_14\n\t"
      "pushl $1\n\t"
      "pushl $0x76c\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264694\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_14:\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00079e70_15\n\t"
      "pushl $1\n\t"
      "pushl $0x76e\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261c58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_15:\n\t"
      "cmpw $0, 0xa(%%edi)\n\t"
      "je .LFUN_00079e70_16\n\t"
      "pushl $1\n\t"
      "pushl $0x76f\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x26460c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00079e70_16:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c7d780]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, %%di\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jle .LFUN_00079e70_28\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".LFUN_00079e70_17:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d6e0]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jle .LFUN_00079e70_27\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      ".LFUN_00079e70_18:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "subl $0xe, %%eax\n\t"
      "je .LFUN_00079e70_21\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00079e70_20\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00079e70_19\n\t"
      "pushl $1\n\t"
      "pushl $0x78c\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261888\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00079e70_23\n\t"
      ".LFUN_00079e70_19:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c71890]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x10, %%esi\n\t"
      "jmp .LFUN_00079e70_22\n\t"
      ".LFUN_00079e70_20:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c717b0]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x10, %%esi\n\t"
      "jmp .LFUN_00079e70_22\n\t"
      ".LFUN_00079e70_21:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c71400]\n\t"
      "addl $8, %%esp\n\t"
      "addl $8, %%esi\n\t"
      ".LFUN_00079e70_22:\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".LFUN_00079e70_23:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00079e70_24:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00079e70_25\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00079e70_25:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movswl 0x4(%%eax), %%ecx\n\t"
      "cmpl %%ecx, -0x8(%%ebp)\n\t"
      "jge .LFUN_00079e70_26\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movswl 0x6(%%eax), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .LFUN_00079e70_26\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "leal (%%ebx,%%edx,1), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "leal (%%esi,%%edx,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c940]\n\t"
      "movswl %%di, %%edx\n\t"
      "movl -0x64(%%ebp,%%edx,4), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "incl %%edi\n\t"
      ".LFUN_00079e70_26:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "cmpw $4, %%si\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00079e70_25\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "incl %%ecx\n\t"
      "cmpw $4, %%bx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .LFUN_00079e70_24\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $4, %%eax\n\t"
      "addl $4, %%edx\n\t"
      "cmpw -0x20(%%ebp), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jl .LFUN_00079e70_18\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      ".LFUN_00079e70_27:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "addl $4, %%eax\n\t"
      "addl $4, %%edx\n\t"
      "cmpw %%di, %%ax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "jl .LFUN_00079e70_17\n\t"
      ".LFUN_00079e70_28:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b79e70_c7d470), [assert] "m"(b79e70_assert), [exitfn] "m"(b79e70_exitfn), [c7d000] "m"(b79e70_c7d000), [c7d780] "m"(b79e70_c7d780), [c7d6e0] "m"(b79e70_c7d6e0), [c71890] "m"(b79e70_c71890), [c717b0] "m"(b79e70_c717b0), [c71400] "m"(b79e70_c71400), [c7c940] "m"(b79e70_c7c940)
      : "memory");
}
#else
#error "FUN_00079e70: clang naked draft required"
#endif


/* FUN_0007a1e0 (0x7a1e0) — XBE naked draft (batch 245). */
#if defined(__clang__)
static bool (*const b7a1e0_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b7a1e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7a1e0_exitfn)(int) = system_exit;
static void * (*const b7a1e0_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static void (*const b7a1e0_c7e560)(void) = bitmap_3d_slice_insert;
static void (*const b7a1e0_c79e70)(void) = FUN_00079e70;
static void (*const b7a1e0_c7e7e0)(void *src_bitmap, void *dst_bitmap, int face, int slice) = bitmap_cube_map_face_extract;
static void (*const b7a1e0_c7c8f0)(void *) = bitmap_delete;
static void (*const b7a1e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0007a1e0(void *source_bitmap __attribute__((unused)), void *destination_bitmap __attribute__((unused)), short source_mipmap_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007a1e0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x7b0\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261b44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_1:\n\t"
      "cmpw $1, 0xa(%%edi)\n\t"
      "je .LFUN_0007a1e0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x7b1\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x26424c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_2:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0007a1e0_3\n\t"
      "cmpw 0x14(%%edi), %%bx\n\t"
      "jle .LFUN_0007a1e0_4\n\t"
      ".LFUN_0007a1e0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7b2\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_0007a1e0_5\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0007a1e0_6\n\t"
      ".LFUN_0007a1e0_5:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_0007a1e0_6:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0007a1e0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x7b3\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264770\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_0007a1e0_8\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0007a1e0_9\n\t"
      ".LFUN_0007a1e0_8:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_0007a1e0_9:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0007a1e0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x7b4\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_0007a1e0_11\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0007a1e0_12\n\t"
      ".LFUN_0007a1e0_11:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_0007a1e0_12:\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0007a1e0_13\n\t"
      "pushl $1\n\t"
      "pushl $0x7b5\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2646d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_13:\n\t"
      "testb $2, 0xe(%%edi)\n\t"
      "jne .LFUN_0007a1e0_14\n\t"
      "pushl $1\n\t"
      "pushl $0x7b6\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264694\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_14:\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007a1e0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x7b8\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261c58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_15:\n\t"
      "cmpw $1, 0xa(%%esi)\n\t"
      "je .LFUN_0007a1e0_16\n\t"
      "pushl $1\n\t"
      "pushl $0x7b9\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264638\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007a1e0_16:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%edi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e0b0]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%esi), %%dx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LFUN_0007a1e0_18\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0007a1e0_18\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0007a1e0_18\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0007a1e0_18\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x8(%%edx)\n\t"
      "jle .LFUN_0007a1e0_19\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0007a1e0_17:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e560]\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c79e70]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7e7e0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x2c, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw 0x8(%%eax), %%si\n\t"
      "jl .LFUN_0007a1e0_17\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c8f0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007a1e0_18:\n\t"
      "pushl $0x264194\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0007a1e0_19:\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c8f0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b7a1e0_c7d470), [assert] "m"(b7a1e0_assert), [exitfn] "m"(b7a1e0_exitfn), [c7e0b0] "m"(b7a1e0_c7e0b0), [c7e560] "m"(b7a1e0_c7e560), [c79e70] "m"(b7a1e0_c79e70), [c7e7e0] "m"(b7a1e0_c7e7e0), [c7c8f0] "m"(b7a1e0_c7c8f0), [c8f390] "m"(b7a1e0_c8f390)
      : "memory");
}
#else
#error "FUN_0007a1e0: clang naked draft required"
#endif


/* bitmap_2d_uncompress_from_mipmap (0x7a4a0) — XBE naked draft (batch 245). */
#if defined(__clang__)
static bool (*const b7a4a0_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b7a4a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7a4a0_exitfn)(int) = system_exit;
static void * (*const b7a4a0_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static void (*const b7a4a0_c7ea60)(void) = FUN_0007ea60;
static void (*const b7a4a0_c79e70)(void *, void *, short) = FUN_00079e70;
static void (*const b7a4a0_c7ece0)(void *, void *, int, int) = bitmap_cube_map_face_insert;
static void (*const b7a4a0_c7c8f0)(void *) = bitmap_delete;
static void (*const b7a4a0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void bitmap_2d_uncompress_from_mipmap(void *source_bitmap __attribute__((unused)), void *destination_bitmap __attribute__((unused)), short source_mipmap_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_2d_uncompress_from_mipmap_1\n\t"
      "pushl $1\n\t"
      "pushl $0x7f9\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261b44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_1:\n\t"
      "cmpw $2, 0xa(%%edi)\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_2\n\t"
      "pushl $1\n\t"
      "pushl $0x7fa\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264274\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_2:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lbitmap_2d_uncompress_from_mipmap_3\n\t"
      "cmpw 0x14(%%edi), %%bx\n\t"
      "jle .Lbitmap_2d_uncompress_from_mipmap_4\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7fb\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lbitmap_2d_uncompress_from_mipmap_5\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_2d_uncompress_from_mipmap_6\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_5:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_6:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_7\n\t"
      "pushl $1\n\t"
      "pushl $0x7fc\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264770\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lbitmap_2d_uncompress_from_mipmap_8\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_2d_uncompress_from_mipmap_9\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_8:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_9:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_10\n\t"
      "pushl $1\n\t"
      "pushl $0x7fd\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lbitmap_2d_uncompress_from_mipmap_11\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_2d_uncompress_from_mipmap_12\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_11:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_12:\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_13\n\t"
      "pushl $1\n\t"
      "pushl $0x7fe\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x2646d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_13:\n\t"
      "testb $2, 0xe(%%edi)\n\t"
      "jne .Lbitmap_2d_uncompress_from_mipmap_14\n\t"
      "pushl $1\n\t"
      "pushl $0x7ff\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264694\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_14:\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_2d_uncompress_from_mipmap_15\n\t"
      "pushl $1\n\t"
      "pushl $0x801\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261c58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_15:\n\t"
      "cmpw $2, 0xa(%%esi)\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_16\n\t"
      "pushl $1\n\t"
      "pushl $0x802\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_16:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%edi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e0b0]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%esi), %%dx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_18\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_18\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_18\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lbitmap_2d_uncompress_from_mipmap_18\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_17:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7ea60]\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c79e70]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7ece0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw $6, %%si\n\t"
      "jl .Lbitmap_2d_uncompress_from_mipmap_17\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c8f0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_uncompress_from_mipmap_18:\n\t"
      "pushl $0x264194\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c8f0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b7a4a0_c7d470), [assert] "m"(b7a4a0_assert), [exitfn] "m"(b7a4a0_exitfn), [c7e0b0] "m"(b7a4a0_c7e0b0), [c7ea60] "m"(b7a4a0_c7ea60), [c79e70] "m"(b7a4a0_c79e70), [c7ece0] "m"(b7a4a0_c7ece0), [c7c8f0] "m"(b7a4a0_c7c8f0), [c8f390] "m"(b7a4a0_c8f390)
      : "memory");
}
#else
#error "bitmap_2d_uncompress_from_mipmap: clang naked draft required"
#endif


/* rgb_color_to_hsv_color (0x7a780) — readable C lift (restored pre-naked). */
void rgb_color_to_hsv_color(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, 0x41 -> jne 0x7a7d5 */
  /* test (char)eax, 0x41 -> jne 0x7a7ee */
  /* test (char)eax, 0x41 -> jne 0x7a803 */
  /* test (char)eax, 0x41 -> jne 0x7a81b */
  /* test (char)eax, 0x41 -> jne 0x7a843 */
  /* test (char)eax, 0x41 -> jne 0x7a83e */
  display_assert((char *)0x002647f0, (char *)0x002641f0, 2130, 0);
  system_exit(0);
  /* cmp edi, esi -> jne 0x7a89b */
  display_assert((char *)0x002647d8, (char *)0x002641f0, 2131, 0);
  system_exit(0);
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();

  (void)eax;
  (void)esi;
  (void)edi;
}


/* hsv_color_to_rgb_color (0x7a970) — readable C lift (restored pre-naked). */
void hsv_color_to_rgb_color(void)
{
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002647f8, (char *)0x002641f0, 2182, 0);
  system_exit(0);
  /* cmp edi, esi -> jne 0x7aa04 */
  display_assert((char *)0x002647d8, (char *)0x002641f0, 2184, 0);
  system_exit(0);
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();

  (void)esi;
  (void)edi;
}


/* bitmap_sharpen (0x7b310) — build sharpen tables and dispatch by bitmap type.
 *
 * amount<=0 -> return. Else amount*100 clamped to [0,100], fill 256-entry
 * pos/neg tables at 0x334360/0x334160, then dispatch:
 *   2D -> bitmap_2d_sharpen(bitmap, amount, pos_table) with neg@esi
 *   3D -> FUN_000790b0(amount_bits, pos, neg, bitmap@esi)
 *   cube -> FUN_00079180(amount_bits, pos, neg, bitmap@esi)
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x361-0x37f.
 */
void bitmap_sharpen(void *bitmap, float amount)
{
  int scale;
  int weight;
  int i;
  int acc_pos;
  int acc_neg;
  short *pos_table;
  short *neg_table;
  short type;
  int amount_bits;
  int tmp;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x361, 1);
    system_exit(-1);
  }
  if (!(amount > *(float *)0x2533c0))
    return;

  /* ftol2(amount * 100.0f) */
  scale = (int)(amount * *(float *)0x253f00);
  if ((short)scale < 0)
    scale = 0;
  else if ((short)scale > 0x64)
    scale = 0x64;
  else
    scale = (short)scale;
  weight = 0x64 - scale;
  if (weight < 1)
    weight = 1;

  pos_table = (short *)0x334360;
  neg_table = (short *)0x334160;
  acc_pos = 0;
  acc_neg = 0;
  /* 0x100 iterations; store via (ecx+0x33435e) with ecx+=2 each pass */
  for (i = 0; i < 0x100; i++) {
    pos_table[i] = (short)(acc_pos / weight);
    acc_pos += 0x64;
    tmp = acc_neg;
    tmp = (tmp + (tmp >> 31 & 7)) >> 3; /* cdq; and edx,7; add; sar 3 */
    neg_table[i] = (short)(tmp / weight);
    acc_neg += scale;
  }

  type = *(short *)((char *)bitmap + 0xa);
  amount_bits = *(int *)&amount;
  if (type == 0) {
    register short *esi_neg asm("esi") = neg_table;
    bitmap_2d_sharpen(bitmap, amount, (int)pos_table);
    (void)esi_neg;
    return;
  }
  if (type == 1) {
    FUN_000790b0(amount_bits, (int)pos_table, (int)neg_table, bitmap);
    return;
  }
  if (type == 2) {
    FUN_00079180(amount_bits, (int)pos_table, (int)neg_table, bitmap);
    return;
  }
  display_assert("### ERROR unsupported bitmap type",
                 "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x37f, 1);
  system_exit(-1);
}


/* FUN_0007b510 (0x7b510) — readable C lift (restored pre-naked). */
void FUN_0007b510(float bump_height, void *bitmap)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7b545 */
  display_assert((char *)0x00261814, (char *)0x002641f0, 1231, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 0 -> je 0x7b56c */
  display_assert((char *)0x00264334, (char *)0x002641f0, 1232, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x7b59c */
  display_assert((char *)0x002644b0, (char *)0x002641f0, 1233, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  debug_malloc(eax, 0, (char *)0x002641f0, 1236);
  /* relift: cmp word ptr [esi + 4], (int16_t)edi -> jle 0x7b8e5 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* cmp eax, ecx -> jne 0x7b643 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x7b661 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* cmp ecx, edx -> jne 0x7b685 */
  bitmap_2d_address((void *)0, 0, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x7b750 */
  /* test (char)eax, 0x41 -> jne 0x7b750 */
  /* test (char)eax, 0x41 -> jne 0x7b76f */
  /* test (char)eax, 0x41 -> jne 0x7b7a2 */
  /* test (char)eax, 0x41 -> jne 0x7b7a2 */
  /* test (char)eax, 0x41 -> jne 0x7b7c1 */
  /* relift: cmp (int16_t)edi, word ptr [esi + 4] -> jl 0x7b600 */
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)0, 0);
  debug_free((void *)(uintptr_t)edi, (char *)0x002641f0, 1309);
  error(0, (char *)0x002642f0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_0007b940 (0x7b940) — 3D bitmap bump-height helper.
 *
 * Verifies bitmap (@ebx) is type 3D and bump_height>0, allocates a temporary
 * 2D bitmap, then for each depth slice: copy slice into temp, run 2D bump
 * helper (FUN_0007b510), copy back. Deletes the temp.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x52d-0x52f.
 */
void FUN_0007b940(float bump_height, void *bitmap /* @<ebx> */)
{
  void *temp;
  int slice;
  short depth;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x52d, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 0xa) != 1) {
    display_assert("bitmap->type==_bitmap_type_3d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x52e, 1);
    system_exit(-1);
  }
  if (!(bump_height > *(float *)0x2533c0)) {
    display_assert("bump_height>0.0f", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x52f, 1);
    system_exit(-1);
  }

  temp = bitmap_2d_new(*(unsigned short *)((char *)bitmap + 4),
                       *(unsigned short *)((char *)bitmap + 6), 0,
                       *(unsigned short *)((char *)bitmap + 0xc));
  if (temp == 0 || *(void **)((char *)temp + 0x2c) == 0) {
    error(2, "### ERROR failed to allocate temporary bitmap");
    bitmap_delete(temp);
    return;
  }

  depth = *(short *)((char *)bitmap + 8);
  if (depth > 0) {
    for (slice = 0; slice < depth; slice++) {
      bitmap_3d_slice_insert(bitmap, 0, slice, temp);
      FUN_0007b510(bump_height, temp);
      bitmap_cube_map_face_extract(temp, bitmap, 0, slice);
    }
  }
  bitmap_delete(temp);
}

/* --- bitmap_utilities.obj orphan shells (2026-07-26) --- */

/* FUN_00076790 (0x76790) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b76790_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b76790_exitfn)(int) = system_exit;
static void * (*const b76790_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b76790_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b76790_c1b9a90)(void *block, int count) = tag_block_resize;
static bool (*const b76790_c1b9ab0)(void *tag_data, int size) = tag_data_resize;
static void * (*const b76790_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static unsigned int (*const b76790_c119bb0)(unsigned int *buf, unsigned int size) = FUN_00119bb0;
static void * (*const b76790_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static bool (*const b76790_c119bf0)(unsigned int *param_1, unsigned int param_2, int param_3, unsigned int *param_4) = FUN_00119bf0;
static void (*const b76790_c73830)(void) = FUN_00073830;
static char (*const b76790_c766e0)(void) = FUN_000766e0;
static void (*const b76790_c76300)(void) = FUN_00076300;
static void (*const b76790_c7c8f0)(void *) = bitmap_delete;
static char (*const b76790_c75630)(void) = FUN_00075630;
static void (*const b76790_c75800)(void) = FUN_00075800;
static void (*const b76790_c75a20)(void) = FUN_00075a20;
static void (*const b76790_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
char FUN_00076790(void *group __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00076790_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb4\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x26276c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076790_1:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00076790_2\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .LFUN_00076790_3\n\t"
      ".LFUN_00076790_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xb5\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x26272c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076790_3:\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00076790_4\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_00076790_5\n\t"
      ".LFUN_00076790_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xb6\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x2626e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076790_5:\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00076790_6\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_00076790_7\n\t"
      ".LFUN_00076790_6:\n\t"
      "pushl $1\n\t"
      "pushl $0xb7\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x2626a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076790_7:\n\t"
      "pushl $0xba\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0\n\t"
      "pushl $0x4000\n\t"
      "movw $0, 0x334138\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x334134\n\t"
      "jne .LFUN_00076790_9\n\t"
      "pushl $0x262674\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00076790_8:\n\t"
      "pushl $0x262634\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00076790_19\n\t"
      ".LFUN_00076790_9:\n\t"
      "leal 0x60(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b9a90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00076790_8\n\t"
      "leal 0x54(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1b9a90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00076790_8\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1b9ab0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00076790_8\n\t"
      "movl $0, 0x334158\n\t"
      "movw $0xffff, 0x33415c\n\t"
      "movl %%esi, 0x33414c\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x1a(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x18(%%esi), %%cx\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7e0b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x334150\n\t"
      "je .LFUN_00076790_14\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c119bb0]\n\t"
      "movswl 0x1a(%%esi), %%ecx\n\t"
      "movswl 0x18(%%esi), %%edx\n\t"
      "imull %%edx, %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_00076790_10\n\t"
      "pushl $1\n\t"
      "pushl $0x104\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x2625e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076790_10:\n\t"
      "movl 0x334150, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7d000]\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c119bf0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00076790_13\n\t"
      "call *%[c73830]\n\t"
      "movb 0x334148, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x334154\n\t"
      "je .LFUN_00076790_11\n\t"
      "call *%[c766e0]\n\t"
      "jmp .LFUN_00076790_12\n\t"
      ".LFUN_00076790_11:\n\t"
      "call *%[c76300]\n\t"
      ".LFUN_00076790_12:\n\t"
      "movl 0x334150, %%edx\n\t"
      "pushl %%edx\n\t"
      "movb %%al, %%bl\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00076790_19\n\t"
      "movl 0x33414c, %%eax\n\t"
      "movswl (%%eax), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_00076790_18\n\t"
      "jmp *.LFUN_00076790_jt(,%%eax,4)\n\t"
      ".LFUN_00076790_13:\n\t"
      "pushl $0x2625a8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00076790_19\n\t"
      ".LFUN_00076790_14:\n\t"
      "pushl $0x262574\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00076790_19\n\t"
      ".LFUN_00076790_15:\n\t"
      "call *%[c75630]\n\t"
      "movb %%al, %%bl\n\t"
      "jmp .LFUN_00076790_19\n\t"
      ".LFUN_00076790_16:\n\t"
      "call *%[c75800]\n\t"
      "movb %%al, %%bl\n\t"
      "jmp .LFUN_00076790_19\n\t"
      ".LFUN_00076790_17:\n\t"
      "call *%[c75a20]\n\t"
      "movb %%al, %%bl\n\t"
      "jmp .LFUN_00076790_19\n\t"
      ".LFUN_00076790_18:\n\t"
      "pushl $1\n\t"
      "pushl $0x137\n\t"
      "pushl $0x2616f0\n\t"
      "pushl $0x261ea0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00076790_19:\n\t"
      "movl 0x334134, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00076790_20\n\t"
      "pushl $0x13d\n\t"
      "pushl $0x2616f0\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00076790_20:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00076790_jt:\n\t"
      ".long .LFUN_00076790_19\n\t"
      ".long .LFUN_00076790_15\n\t"
      ".long .LFUN_00076790_16\n\t"
      ".long .LFUN_00076790_17\n\t"
      ".long .LFUN_00076790_19\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b76790_assert), [exitfn] "m"(b76790_exitfn), [c8ee60] "m"(b76790_c8ee60), [c8f390] "m"(b76790_c8f390), [c1b9a90] "m"(b76790_c1b9a90), [c1b9ab0] "m"(b76790_c1b9ab0), [c7e0b0] "m"(b76790_c7e0b0), [c119bb0] "m"(b76790_c119bb0), [c7d000] "m"(b76790_c7d000), [c119bf0] "m"(b76790_c119bf0), [c73830] "m"(b76790_c73830), [c766e0] "m"(b76790_c766e0), [c76300] "m"(b76790_c76300), [c7c8f0] "m"(b76790_c7c8f0), [c75630] "m"(b76790_c75630), [c75800] "m"(b76790_c75800), [c75a20] "m"(b76790_c75a20), [c8ef70] "m"(b76790_c8ef70)
      : "memory");
}
#else
#error "FUN_00076790: clang naked draft required"
#endif


/* 0x77cd0 */
void *FUN_00077cd0(void *bitmap, short mipmap_count, int param_3, int param_4)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x77d08 */
  display_assert((char *)0x00261aa4, (char *)0x002641f0, 443, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 2 -> je 0x77d2f */
  display_assert((char *)0x00264274, (char *)0x002641f0, 444, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 1 -> jg 0x77d58 */
  display_assert((char *)0x0026421c, (char *)0x002641f0, 445, 0);
  system_exit(0);
  bitmap_cube_map_new(0, 0, 11);
  /* test eax, eax -> je 0x77e42 */
  bitmap_2d_new(0, 0, 0, 11);
  /* test ebx, ebx -> je 0x77e21 */
  /* test eax, eax -> je 0x77e21 */
  FUN_0007ea60(0, 0, 0, 0);
  FUN_00077720(0, (void *)(uintptr_t)eax, 0, 0);
  /* test esi, esi -> je 0x77dfc */
  /* test eax, eax -> je 0x77dfc */
  bitmap_cube_map_face_insert(0, 0, 0, 0);
  bitmap_delete((void *)(uintptr_t)esi);
  /* cmp (int16_t)edi, 6 -> jl 0x77dbe */
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x00264194);
  bitmap_delete((void *)(uintptr_t)ebx);
  error(0, (char *)0x00264194);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* FUN_00079480 (0x79480) — 3D bitmap alpha-bleed helper.
 *
 * Verifies bitmap (@edi) is type 3D and passes>0, allocates a temporary 2D
 * bitmap, then for each depth slice: copy slice into temp, run 2D alpha-bleed
 * (FUN_00079250), copy back. Deletes the temp.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x472-0x474.
 */
void FUN_00079480(short passes, void *bitmap /* @<edi> */)
{
  void *temp;
  int slice;
  short depth;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x472, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 0xa) != 1) {
    display_assert("bitmap->type==_bitmap_type_3d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x473, 1);
    system_exit(-1);
  }
  if (passes <= 0) {
    display_assert("passes>0", "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x474, 1);
    system_exit(-1);
  }

  temp = bitmap_2d_new(*(unsigned short *)((char *)bitmap + 4),
                       *(unsigned short *)((char *)bitmap + 6), 0,
                       *(unsigned short *)((char *)bitmap + 0xc));
  if (temp == 0 || *(void **)((char *)temp + 0x2c) == 0) {
    error(2, "### ERROR failed to allocate temporary bitmap");
    bitmap_delete(temp);
    return;
  }

  depth = *(short *)((char *)bitmap + 8);
  if (depth > 0) {
    for (slice = 0; slice < depth; slice++) {
      bitmap_3d_slice_insert(bitmap, 0, slice, temp);
      FUN_00079250(passes, temp);
      bitmap_cube_map_face_extract(temp, bitmap, 0, slice);
    }
  }
  bitmap_delete(temp);
}

