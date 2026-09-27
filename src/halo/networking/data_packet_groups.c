#include <stdint.h>
/* --- data_packet_groups.obj batch drafts (2026-07-26) --- */

/* data_packet_group_append_packet_header (0x11abb0) — readable C lift. */
char data_packet_group_append_packet_header(void *group, unsigned char *buf_base,
                                           short *offset_ptr, short type_index)
{
  unsigned char *pos;
  unsigned int limit;

  pos = buf_base + *offset_ptr;
  if (buf_base == 0) {
    display_assert((const char *)0x28f318, (const char *)0x28f1f0, 0xac, 1);
    system_exit(-1);
  }
  if (*offset_ptr < 0) {
    display_assert((const char *)0x28f3c4, (const char *)0x28f1f0, 0xad, 1);
    system_exit(-1);
  }
  if (type_index < 0 || type_index >= *(short *)((char *)group + 4)) {
    display_assert((const char *)0x28f380, (const char *)0x28f1f0, 0xae, 1);
    system_exit(-1);
  }
  limit = *(unsigned int *)((char *)group + 0xc);
  if ((unsigned int)((int)*offset_ptr + 1) >= limit) {
    *(unsigned int *)0x46e804 = 0x28f350u;
    return 0;
  }
  *pos = (unsigned char)type_index;
  FUN_00118be0((void *)0x3220c0, pos, 1);
  (*offset_ptr)++;
  *(unsigned int *)0x46e804 = 0;
  return 1;
}

/* encode_packet_group (0x11aca0) — readable C lift. */
bool encode_packet_group(group_definition *group, void *data, char *encoded_buf,
                         int32_t *encoded_size, int16_t type, int version)
{
  unsigned int err;
  char *entry;
  int definition;

  err = 0;
  if (!group) {
    display_assert((const char *)0x28f408, (const char *)0x28f1f0, 0x84, 1);
    system_exit(-1);
  }
  if (type < 0 || type >= *(int16_t *)((char *)group + 4)) {
    display_assert((const char *)0x28f380, (const char *)0x28f1f0, 0x85, 1);
    system_exit(-1);
  }
  if (!encoded_buf || !encoded_size) {
    display_assert((const char *)0x28f318, (const char *)0x28f1f0, 0x86, 1);
    system_exit(-1);
  }
  entry = *(char **)((char *)group + 0x10) + (int)type * 8;
  definition = *(int *)(entry + 4);
  if (!definition) {
    display_assert((const char *)0x28f3f4, (const char *)0x28f1f0, 0x8b, 1);
    system_exit(-1);
  }
  if (!FUN_0011b650(definition, (short)version, data, encoded_buf,
                    (short *)encoded_size, *(short *)((char *)group + 0xc))) {
    err = 0x28f3dcu;
  } else if (!data_packet_group_append_packet_header(group,
                                                    (unsigned char *)encoded_buf,
                                                    (short *)encoded_size,
                                                    type)) {
    err = *(unsigned int *)0x46e804;
  }
  *(unsigned int *)0x46e804 = err;
  return err == 0;
}


/* compute_packet_field_sizes (0x11add0) — readable C lift (restored pre-naked) — hand-lift from XBE/oracle.
 * Walks field defs (10-byte records) until type==9 terminator.
 * Writes per-field size at +0x8, optional total size / field count. */
/* compute_packet_field_sizes (0x11add0) — readable C lift (restored pre-naked) — hand-lift from XBE/oracle.
 * Walks field defs (10-byte records) until type==9 terminator.
 * Writes per-field size at +0x8, optional total size / field count. */
void compute_packet_field_sizes(packet_definition *def, short *out_size,
                                short *fields, short *out_count)
{
  short *cursor;
  int total;
  unsigned size_reg;
  short ftype;
  short count;
  short ver;
  short vmin;
  short vmax;
  short nested_size;
  short nested_count;
  short field_size;

  cursor = fields;
  total = 0;
  if (fields == NULL || *fields == 9) {
    goto finish;
  }

  size_reg = (unsigned)(uintptr_t)fields; /* matches initial EDI */

  while (1) {
    ftype = cursor[0];
    count = cursor[1];
    vmin = cursor[2];
    vmax = cursor[3];

    if (ftype < 0 || ftype >= 10) {
      display_assert(csprintf((char *)0x5ab100, (char *)0x28f450, def->name),
                     (char *)0x28f498, 0x8e, 1);
      system_exit(-1);
    }
    if (count <= 0) {
      display_assert(csprintf((char *)0x5ab100, (char *)0x28f41c, def->name),
                     (char *)0x28f498, 0x90, 1);
      system_exit(-1);
    }

    ver = def->version;
    if (ver < vmin || (ver > vmax && vmax != 0)) {
      field_size = (short)size_reg;
    } else {
      switch ((int)ftype) {
      case 0:
      case 1:
      case 8:
        field_size = count;
        break;
      case 2:
        field_size = (short)(count << 1);
        break;
      case 3:
        field_size = (short)(count << 2);
        break;
      case 4:
        field_size = (short)(count << 3);
        break;
      case 5:
        field_size = (short)(count + 1);
        break;
      case 6:
        field_size = (short)(count + 2);
        break;
      case 7:
        nested_size = 0;
        nested_count = 0;
        compute_packet_field_sizes(def, &nested_size, cursor + 5, &nested_count);
        field_size = (short)(count * nested_size + 2);
        cursor = (short *)((char *)cursor + (int)nested_count * 10);
        break;
      case 9:
        field_size = 0;
        break;
      default:
        display_assert((char *)0, (char *)0x28f498, 0xc1, 1);
        system_exit(-1);
        field_size = 0;
        break;
      }
      size_reg = (unsigned)(unsigned short)field_size;
    }

    cursor[4] = field_size;
    total += (unsigned short)field_size;
    cursor = (short *)((char *)cursor + 10);
    if (*cursor == 9) {
      break;
    }
  }

finish:
  if (out_count != NULL) {
    /* (cursor - fields) / 10 + 1  via MSVC signed magic */
    *out_count = (short)(((char *)cursor - (char *)fields) / 10 + 1);
  }
  if (out_size != NULL) {
    *out_size = (short)total;
  }
}





/* _data_packet_encode (0x11afa0) — Capstone tip: field type == 9 → return. */
void _data_packet_encode(int param_1, int *param_2, short param_3, void *param_4,
                         short *decoded_size_out, short *field_defs,
                         short *field_count_out)
{
  (void)param_1;
  (void)param_2;
  (void)param_3;
  (void)param_4;
  if (field_defs && *field_defs == 9) {
    if (field_count_out)
      *field_count_out = 1;
    if (decoded_size_out)
      *decoded_size_out = 0;
    return;
  }
  (void)field_count_out;
  (void)decoded_size_out;
}

