/* 0x1b9930 — tag_loaded: linear search for a loaded tag by group/name.
 * Returns tag index from tag instance +0x0c on match; otherwise -1.
 * Requires cache tags to be available (byte flag at 0x4e4d00). If the
 * global tag-instance table pointer (0x5054f0) is NULL while tags are
 * enabled, asserts and exits. Comparison uses case-insensitive CRT
 * string compare (__stricmp). */
int tag_loaded(int group_tag, const char *name, ...)
{
  int tag_count;
  int *entry;
  short index;

  if (*(uint8_t *)0x4e4d00 == 0) {
    return -1;
  }

  if (*(int **)0x5054f0 == 0) {
    display_assert("global_tag_instances",
                   "c:\\halo\\SOURCE\\cache\\cache_files.c", 0x127, true);
    system_exit(-1);
  }

  tag_count = *(int *)(*(int *)0x4e5504 + 0xc);
  if (tag_count <= 0) {
    return -1;
  }

  index = 0;
  do {
    entry = (int *)((int)*(int **)0x5054f0 + ((int)index << 5));
    if (entry[0] == group_tag &&
        crt_stricmp(name, (const char *)entry[4]) == 0) {
      return entry[3];
    }

    index = (short)(index + 1);
  } while ((int)index < tag_count);

  return -1;
}

/* 0x1ba140 — tag_get: resolve a tag handle and return its base/data
 * pointer. Calls 0x1b9bf0 (tag_instance_resolve) with the 16-bit tag
 * index in EDI (hidden register param); that helper returns a pointer
 * to the tag instance record. The record stores the tag's own group
 * at +0, parent group at +4, grandparent group at +8, and data pointer
 * at +0x14. The group check accepts a match at any of the three levels
 * (supports parent-group lookups). Asserts if the group doesn't match
 * or if the data pointer is NULL. */
void *tag_get(int group_tag, int tag_index)
{
  int _edi = tag_index;
  int *entry;

  asm volatile("movl $0x1b9bf0, %%ecx\n\t"
               "call *%%ecx"
               : "+D"(_edi), "=a"(entry)
               :
               : "ecx", "edx", "memory", "cc");

  if (entry[0] != group_tag && entry[1] != group_tag && entry[2] != group_tag) {
    error(2, "expected tag group %08x but got %08x for datum %08x",
          group_tag, entry[0], tag_index);
    display_assert("expected tag group mismatch",
                   "c:\\halo\\SOURCE\\cache\\cache_files.c", 0xf7, true);
    system_exit(-1);
  }
  if (entry[5] == 0) {
    display_assert("can't get() a tag with a base address!",
                   "c:\\halo\\SOURCE\\cache\\cache_files.c", 0xfb, true);
    system_exit(-1);
  }
  return (void *)entry[5];
}

/* 0x1ba1f0 — tag_get_name: return the name string for a tag by index.
 * Calls tag_instance_resolve (0x1b9bf0) with the tag index in EDI,
 * then reads the name pointer at offset +0x10 of the tag instance record. */
const char *tag_get_name(int tag_index)
{
  int _edi = tag_index;
  int *entry;

  asm volatile("movl $0x1b9bf0, %%ecx\n\t"
               "call *%%ecx"
               : "+D"(_edi), "=a"(entry)
               :
               : "ecx", "edx", "memory", "cc");

  return (const char *)entry[4];
}

/* 0x1ba210 — tag_get_group_tag: return the primary group tag (4CC class
 * identifier) for a tag by index. Calls tag_instance_resolve (0x1b9bf0)
 * with the tag index in EDI, then reads the group tag at offset +0x00
 * of the tag instance record. */
int tag_get_group_tag(int tag_index)
{
  int *entry;

  entry = tag_instance_resolve(tag_index);
  return entry[0];
}
/* --- tags.obj batch drafts (2026-07-26) --- */

/* 0x1b9fa0 */
void FUN_001b9fa0(void)
{

}

/* 0x1ba0c0 */
void FUN_001ba0c0(void *element)
{
  (void)element;
}

/* 0x1ba250 */
void FUN_001ba250(void)
{

}

/* 0x1ba290 */
void FUN_001ba290(void)
{

}

/* 0x1ba2f0 */
void FUN_001ba2f0(int buffer, int size, int dest_file, int dest_file_size, const char *source_file_name)
{
  (void)buffer;
  (void)size;
  (void)dest_file;
  (void)dest_file_size;
  (void)source_file_name;
}

/* 0x1ba5d0 */
void FUN_001ba5d0(void)
{

}

/* 0x1ba660 */
void cache_copy_compressed_alloc(void)
{

}

/* 0x1ba6c0 */
void FUN_001ba6c0(void)
{

}

/* 0x1ba710 */
void FUN_001ba710(void)
{

}

/* 0x1ba7c0 */
void cache_copy_initialize_and_fill_with_garbage(void)
{

}

/* 0x1ba8b0 */
void FUN_001ba8b0(void)
{

}

/* 0x1ba930 */
void FUN_001ba930(void)
{

}

/* 0x1ba9d0 */
void FUN_001ba9d0(void)
{

}

/* 0x1baa50 */
void FUN_001baa50(void)
{

}

/* 0x1bab60 */
void FUN_001bab60(void)
{

}

/* 0x1bac00 */
void FUN_001bac00(void)
{

}

/* 0x1bac70 */
void FUN_001bac70(void)
{

}

/* 0x1baca0 */
void FUN_001baca0(void)
{

}

/* 0x1badc0 */
void cache_copy_get_status(void)
{

}

/* 0x1baf50 */
void FUN_001baf50(void)
{

}

/* 0x1bafa0 */
void FUN_001bafa0(void)
{

}

/* 0x1bb190 */
void FUN_001bb190(void)
{

}

/* 0x1bb2d0 */
void FUN_001bb2d0(void)
{

}
