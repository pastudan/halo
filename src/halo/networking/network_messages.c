/* ========================================================================
 * data_encoding.c — Decode-side encoding state helpers
 * Original source: c:\halo\SOURCE\memory\data_encoding.c
 *
 * Encoding state struct (16 bytes, int[4]):
 *   [0] = buffer pointer
 *   [1] = current offset
 *   [2] = buffer_size
 *   [3] = overflow flag (byte at low byte of word [3])
 * ======================================================================== */

#define byte_swap_raw \
  ((void (*)(void *, int, int))0x118620)

#define byte_swap_structures \
  ((void (*)(void *, void *, int))0x118be0)

#define encode_state_new \
  ((void (*)(int *, int, int))0x119c50)

#define encode_raw_data \
  ((int (*)(int *, int, short, int))0x119cc0)

#define encode_packet_fields \
  ((void (*)(int, int *, short, void *, short, int, short *))0x11afa0)

#define csstrcpy \
  ((char *(*)(char *, const char *))0x8dff0)

#define array_get_element \
  ((int (*)(int *, int, int))0x117ee0)

#define array_reset \
  ((void (*)(int *, int))0x117b20)

#define array_dispose \
  ((void (*)(int *))0x117cf0)

/* packet_header byte-swap definition at 0x3220c0 */
#define packet_header_bs_def ((void *)0x3220c0)

/* hash primes table at 0x3220d4 */
#define hashtable_primes ((short *)0x3220d4)

/* last decode error string global at 0x46e804 */
#define s_last_decode_error (*(char **)0x46e804)

/* FUN_0011a230 (0x11a230) — readable C lift. */
extern char DAT_0028eef8[];
extern char DAT_0028f010[];

bool FUN_0011a230(int *state, const char *source, short max_length)
{
  short len;
  int used;
  char *dest;

  len = (short)strnlen(source, (int)max_length);
  used = state[1];
  dest = (char *)state[0] + used;
  if (used + (int)len + 1 > state[2]) {
    display_assert(DAT_0028f010, DAT_0028eef8, 0xb6, true);
    system_exit(-1);
  }
  if (used + (int)len + 1 <= state[2] && *(unsigned char *)((char *)state + 0xc) == 0) {
    csstrncpy(dest, source, (unsigned)len);
    dest[len] = 0;
    state[1] = state[1] + (int)len + 1;
    return *(unsigned char *)((char *)state + 0xc) == 0;
  }
  *(unsigned char *)((char *)state + 0xc) = 1;
  return 0;
}

/* FUN_0011a2d0 (0x11a2d0) — readable C lift from XBE leaf. */
void FUN_0011a2d0(int *state, void *buffer, int buffer_size)
{
  extern char DAT_00267900[];
  extern char DAT_0028eef8[];
  extern char DAT_0028edb4[];

  if (buffer == 0) {
    display_assert(DAT_00267900, DAT_0028eef8, 0xcc, true);
    system_exit(-1);
  }
  if (buffer_size < 0) {
    display_assert(DAT_0028edb4, DAT_0028eef8, 0xcd, true);
    system_exit(-1);
  }
  csmemset(state, 0, 0x10);
  state[0] = (int)buffer;
  state[2] = buffer_size;
}




/* FUN_0011a340 (0x11a340) — readable C lift.
 *
 * Byte-swap `count` structures described by bs_definition into the encode
 * state's buffer when they fit; otherwise set the overflow flag and return 0.
 */
int FUN_0011a340(int *state, short count, void *bs_definition)
{
  int offset;
  int bytes;
  int dest;

  if (state == NULL || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0xde, true);
    system_exit(-1);
  }
  if (count < 0) {
    display_assert((const char *)0x28f044, (const char *)0x28eef8, 0xdf, true);
    system_exit(-1);
  }
  if (bs_definition == NULL) {
    display_assert((const char *)0x28ef80, (const char *)0x28eef8, 0xe0, true);
    system_exit(-1);
  }

  offset = state[1];
  /* Original uses 16-bit IMULW; truncate then sign-extend. */
  bytes = (int)(int16_t)(*(int16_t *)((char *)bs_definition + 4) * count);
  if (offset + bytes > state[2] || *((char *)state + 0xc) != 0) {
    *((char *)state + 0xc) = 1;
    return 0;
  }

  dest = state[0] + offset;
  if ((int16_t)bytes != 0) {
    FUN_00118be0(bs_definition, (void *)(uintptr_t)dest, count);
    state[1] = offset + bytes;
  }
  return dest;
}


/* FUN_0011a430 (0x11a430) — readable C lift (restored pre-naked). */
 int FUN_0011a430(int *state, short count, int element_size)
{
  int byte_count;
  int result;

  if (((state == NULL) || (*state == 0) || (state[1] < 0)) ||
      (state[2] < state[1])) {
    display_assert("state && state->buffer && state->offset>=0 && "
                   "state->offset<=state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x100, 1);
    system_exit(-1);
  }
  if (count < 0) {
    display_assert("count>=0",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x101, 1);
    system_exit(-1);
  }
  switch (element_size) {
  case 1:
    byte_count = (int)count;
    break;
  case -8:
    byte_count = (int)count << 3;
    break;
  case -4:
    byte_count = (int)count << 2;
    break;
  case -2:
    byte_count = (int)count << 1;
    break;
  default:
    display_assert(NULL,
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x109, 1);
    system_exit(-1);
    byte_count = (int)count;
    break;
  }
  if ((state[1] + byte_count <= state[2]) && ((char)state[3] == '\0')) {
    result = *state + state[1];
    if (element_size != 1) {
      byte_swap_raw((void *)result, (int)count, element_size);
    }
    state[1] = state[1] + byte_count;
    return result;
  }
  *(char *)(state + 3) = 1;
  return 0;
}


/* FUN_0011a560 (0x11a560) — readable C lift from XBE leaf.
 * Read next byte from a bounded buffer cursor. */
unsigned char FUN_0011a560(int *state)
{
  extern char DAT_0028f058[];
  extern char DAT_0028eef8[];
  int offset;
  int limit;
  unsigned char *base;
  int next;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert(DAT_0028f058, DAT_0028eef8, 0x100, true);
    system_exit(-1);
  }
  offset = state[1];
  limit = state[2];
  next = offset + 1;
  if (next > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  base = (unsigned char *)state[0];
  state[1] = next;
  if (base + offset == 0)
    return 0;
  return base[offset];
}



/* FUN_0011a5d0 (0x11a5d0) — readable C lift.
 * Read next int16 from a bounded buffer cursor (with byte-swap). */
short FUN_0011a5d0(int *state)
{
  extern char DAT_0028f058[];
  extern char DAT_0028eef8[];
  int offset;
  int limit;
  short *ptr;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert(DAT_0028f058, DAT_0028eef8, 0x100, true);
    system_exit(-1);
  }
  offset = state[1];
  limit = state[2];
  if (offset + 2 > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  ptr = (short *)((char *)state[0] + offset);
  FUN_00118620(ptr, 1, -2);
  state[1] = offset + 2;
  if (ptr == 0)
    return 0;
  return *ptr;
}



/* FUN_0011a650 (0x11a650) — readable C lift.
 * Read next int32 from a bounded buffer cursor (with byte-swap). */
int FUN_0011a650(int *state)
{
  extern char DAT_0028f058[];
  extern char DAT_0028eef8[];
  int offset;
  int limit;
  int *ptr;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert(DAT_0028f058, DAT_0028eef8, 0x100, true);
    system_exit(-1);
  }
  offset = state[1];
  limit = state[2];
  if (offset + 4 > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  ptr = (int *)((char *)state[0] + offset);
  FUN_00118620(ptr, 1, -4);
  state[1] = offset + 4;
  if (ptr == 0)
    return 0;
  return *ptr;
}



/* FUN_0011a6d0 (0x11a6d0) — readable C lift. */
unsigned long long FUN_0011a6d0(int *state)
{
  int *pair;

  pair = (int *)FUN_0011a430(state, 1, -8);
  if (pair == NULL)
    return 0;
  return ((unsigned long long)(unsigned int)pair[1] << 32) | (unsigned int)pair[0];
}

/* FUN_0011a700 (0x11a700) — readable C lift. */
unsigned int FUN_0011a700(int *state, int maximum_value)
{
  if (maximum_value <= 0) {
    display_assert((const char *)0x28ef70, (const char *)0x28eef8, 0x141, 1);
    system_exit(-1);
  }
  if (maximum_value <= 0xff)
    return (unsigned int)FUN_0011a560(state);
  if (maximum_value <= 0xffff)
    return (unsigned int)(int)FUN_0011a5d0(state);
  return (unsigned int)FUN_0011a650(state);
}

/* FUN_0011a770 (0x11a770) — readable C lift (restored pre-naked). */
void *FUN_0011a770(int *state, int element_size_type, unsigned int *element_count_ref,
                   int maximum_element_count, void *bs_definition)
{
  short sVar1;
  unsigned int count;
  void *result;

  if (((state == NULL) || (*state == 0) || (state[1] < 0)) ||
      (state[2] <= state[1])) {
    display_assert("state && state->buffer && state->offset>=0 && "
                   "state->offset<state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x15c, 1);
    system_exit(-1);
  }
  if (element_count_ref == NULL) {
    display_assert("element_count_reference",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x15d, 1);
    system_exit(-1);
  }
  if (maximum_element_count < 1) {
    display_assert("maximum_element_count>0",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x15e, 1);
    system_exit(-1);
  }
  if (bs_definition == NULL) {
    display_assert("bs_definition",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x15f, 1);
    system_exit(-1);
  }
  switch (element_size_type) {
  case 1:
    count = FUN_0011a560(state) & 0xff;
    break;
  case -2:
    sVar1 = FUN_0011a5d0(state);
    count = (unsigned int)(int)sVar1;
    break;
  case -4:
    count = (unsigned int)FUN_0011a650(state);
    break;
  case -8:
    count = (unsigned int)(int)FUN_0011a6d0(state);
    break;
  default:
    display_assert(NULL,
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x172, 1);
    system_exit(-1);
    count = *element_count_ref;
    break;
  }
  if (((char)state[3] == '\0') && ((int)count >= 0) &&
      ((int)count <= maximum_element_count)) {
    *element_count_ref = count;
    result = (void *)FUN_0011a340(state, (short)count, bs_definition);
    return result;
  }
  return NULL;
}



/* FUN_0011a8e0 (0x11a8e0) — readable C lift. */
char *FUN_0011a8e0(int *state, unsigned short max_length)
{
  char *result;
  int size;
  int offset;
  short len;
  int idx;

  (void)max_length;
  offset = state[1];
  size = state[2];
  result = (char *)state[0] + offset;
  len = 0;
  if (offset >= size) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  idx = 0;
  for (;;) {
    if (result[idx] == 0) {
      state[1] = offset + (int)len + 1;
      return result;
    }
    len++;
    idx = (int)len;
    if (offset + idx >= size) {
      *((unsigned char *)state + 0xc) = 1;
      return 0;
    }
  }
}


/* ========================================================================
 * Already-ported: verify_packet_group_definitions (0x11a930)
 * ======================================================================== */

void verify_packet_group_definitions(group_definition *group)
{
  short i;

  for (i = 0; i < group->packet_count; i++) {
    packet_entry *entry = &group->packets[i];

    if (entry->definition != NULL) {
      assert_halt(entry->packet_class >= 0 &&
                  entry->packet_class < group->packet_class_count);
      assert_halt(entry->definition->size <=
                  group->maximum_decoded_packet_size);
      assert_halt((uint32_t)(entry->definition->size + sizeof(packet_header)) <=
                  (uint32_t)group->maximum_encoded_packet_size);
      verify_packet_definition(entry->definition);
    }
  }
}

/* network_messages.c — Network game packet group initialization.
 *
 * Corresponds to network_messages.obj.
 * initialize_network_game_packets at 0x12b640 is a thin wrapper that calls
 * verify_packet_group_definitions (0x11a930) with the global
 * s_network_game_messages_group (0x323510).
 *
 * verify_packet_group_definitions iterates the packet entries in the given
 * group, validates class bounds and size constraints, then calls
 * verify_packet_definition on each non-NULL definition.
 *
 * verify_packet_definition at 0x11b540 validates a single packet_definition:
 * checks non-NULL, size >= 0, version >= 0, name and fields non-NULL, then
 * (if not yet validated) computes total field sizes and confirms they match
 * the declared size. Sets validated = 1 after success.
 *
 * Original source: c:\halo\SOURCE\memory\data_packet_groups.c lines 0x28-0x2a
 * verify_packet_definition source: c:\halo\SOURCE\memory\data_packets.c lines
 * 0x20-0x2b
 */

/* compute_packet_field_sizes at 0x11add0 — not yet ported (data_packets.c) */
#define compute_packet_field_sizes \
  ((void (*)(packet_definition *, short *, short *, short *))0x11add0)

void verify_packet_definition(packet_definition *def)
{
  short computed_size;
  short field_count;

  if (def == NULL) {
    display_assert("packet_definition",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x20, 1);
    system_exit(-1);
  }
  if (def->size < 0) {
    display_assert("packet_definition->size>=0",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x21, 1);
    system_exit(-1);
  }
  if (def->version < 0) {
    display_assert("packet_definition->version>=0",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x22, 1);
    system_exit(-1);
  }
  if (def->name == NULL || def->fields == NULL) {
    display_assert("packet_definition->name && packet_definition->fields",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x23, 1);
    system_exit(-1);
  }
  if (!def->validated) {
    compute_packet_field_sizes(def, &computed_size, def->fields, &field_count);
    if (computed_size != def->size) {
      display_assert(csprintf(error_string_buffer,
                              "packet '%s' fields added up to #%d bytes but "
                              "should have been #%d bytes.",
                              def->name, (int)computed_size, (int)def->size),
                     "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x2b, 1);
      system_exit(-1);
    }
    def->validated = 1;
  }
}

/* ========================================================================
 * data_packet_groups.c — Packet group decode
 * ======================================================================== */

/* FUN_0011aa40 (0x11aa40) — readable C lift (restored pre-naked). */
bool FUN_0011aa40(int group, void *decoded_packet, char *encoded_packet,
                  short *encoded_packet_size, short *packet_type,
                  short *packet_version, short expected_packet_class)
{
  char *header_ptr;
  int packets_array;
  int definition;
  char packet_type_byte;
  char *error_msg;

  error_msg = NULL;
  if (decoded_packet == NULL) {
    display_assert("decoded_packet",
                   "c:\\halo\\SOURCE\\memory\\data_packet_groups.c", 0x49, 1);
    system_exit(-1);
  }
  if (encoded_packet == NULL || encoded_packet_size == NULL) {
    display_assert("encoded_packet && encoded_packet_size",
                   "c:\\halo\\SOURCE\\memory\\data_packet_groups.c", 0x4a, 1);
    system_exit(-1);
  }
  if (packet_type == NULL || packet_version == NULL) {
    display_assert("packet_type && packet_version",
                   "c:\\halo\\SOURCE\\memory\\data_packet_groups.c", 0x4b, 1);
    system_exit(-1);
  }
  if (expected_packet_class < 0 ||
      *(short *)(group + 6) <= expected_packet_class) {
    display_assert("expected_packet_class>=0 && "
                   "expected_packet_class<group_definition->packet_class_count",
                   "c:\\halo\\SOURCE\\memory\\data_packet_groups.c", 0x4d, 1);
    system_exit(-1);
  }
  if (*encoded_packet_size == 0) {
    error_msg = "got packet with no header";
  }
  else {
    header_ptr = (char *)(*encoded_packet_size - 1 + (int)encoded_packet);
    byte_swap_structures(packet_header_bs_def, header_ptr, 1);
    packet_type_byte = *header_ptr;
    if (packet_type_byte < 0 ||
        *(short *)(group + 4) <= (short)packet_type_byte) {
      error_msg = "got packet with bad type";
    }
    else {
      packets_array = *(int *)(group + 0x10);
      if (*(short *)(packets_array + (int)packet_type_byte * 8) ==
          expected_packet_class) {
        *encoded_packet_size = *encoded_packet_size - 1;
        definition = *(int *)(packets_array + (int)packet_type_byte * 8 + 4);
        if (definition != 0) {
          if (!FUN_0011b750(definition, (int)encoded_packet,
                            *encoded_packet_size, (int)decoded_packet,
                            (unsigned short *)packet_version, 0)) {
            error_msg = "got packet which wouldn't decode";
            goto done;
          }
        }
        *packet_type = (short)*header_ptr;
      }
      else {
        error_msg = "got packet with mismatched class";
      }
    }
  }
done:
  s_last_decode_error = error_msg;
  return error_msg == NULL;
}


/* ========================================================================
 * data_packets.c — Packet field encode/decode
 * ======================================================================== */

/* FUN_0011b2a0 (0x11b2a0) — XBE naked draft (batch 82). */
#if defined(__clang__)
static int (*const b11b2a0_c11a430)(int *state, short count, int element_size) = (void *)FUN_0011a430;
static void * (*const b11b2a0_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static char * (*const b11b2a0_c11a8e0)(int *state, unsigned short max_length) = (void *)FUN_0011a8e0;
static char * (*const b11b2a0_c8dff0)(char *destination, const char *source) = (void *)csstrcpy;
static unsigned int (*const b11b2a0_c11a700)(int *state, int maximum_value) = (void *)FUN_0011a700;
static void (*const b11b2a0_c11add0)(packet_definition *def, short *param_2, short *param_3, short *param_4) = (void *)compute_packet_field_sizes;
static void (*const b11b2a0_c11b2a0)(int definition, int *decode_state, unsigned short version, unsigned short *output, short *decoded_size_out, short *field_defs, short *field_count_out) = (void *)FUN_0011b2a0;
static void *(*const b11b2a0_memset)(void *, int, unsigned int) = (void *)csmemset;

__attribute__((naked, noinline))
void FUN_0011b2a0(int definition __attribute__((unused)), int *decode_state __attribute__((unused)), unsigned short version __attribute__((unused)), unsigned short *output __attribute__((unused)), short *decoded_size_out __attribute__((unused)), short *field_defs __attribute__((unused)), short *field_count_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpw $9, (%%eax)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "je .LFUN_0011b2a0_11\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".LFUN_0011b2a0_1:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpw 0x4(%%esi), %%cx\n\t"
      "jl .LFUN_0011b2a0_20\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jle .LFUN_0011b2a0_2\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0011b2a0_20\n\t"
      ".LFUN_0011b2a0_2:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_0011b2a0_10\n\t"
      "jmp *.LFUN_0011b2a0_jt(,%%eax,4)\n\t"
      ".LFUN_0011b2a0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-2\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_5:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-4\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-8\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "shll $3, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_7:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_8:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a700]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movw %%bx, (%%ecx)\n\t"
      "call *%[c11a430]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_9\n\t"
      "movswl %%bx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011b2a0_9:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_0011b2a0_10:\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "addl $0xa, %%esi\n\t"
      "cmpw $9, (%%esi)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "jne .LFUN_0011b2a0_1\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      ".LFUN_0011b2a0_11:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0011b2a0_12\n\t"
      "subl %%eax, %%esi\n\t"
      "movl $0x66666667, %%eax\n\t"
      "imull %%esi\n\t"
      "sarl $2, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "leal 0x1(%%edx,%%eax,1), %%edx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      ".LFUN_0011b2a0_12:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_13\n\t"
      "subl 0x14(%%ebp), %%ebx\n\t"
      "movw %%bx, (%%eax)\n\t"
      ".LFUN_0011b2a0_13:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011b2a0_14:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_15:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a700]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xa(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[c11add0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0011b2a0_16\n\t"
      "cmpw 0x2(%%esi), %%bx\n\t"
      "jle .LFUN_0011b2a0_17\n\t"
      ".LFUN_0011b2a0_16:\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LFUN_0011b2a0_17:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw %%bx, (%%eax)\n\t"
      "leal 0x2(%%eax), %%ebx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0011b2a0_19\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0011b2a0_18:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "leal 0xa(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c11b2a0]\n\t"
      "movswl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "addl %%ecx, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_0011b2a0_18\n\t"
      ".LFUN_0011b2a0_19:\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal (%%esi,%%edx,2), %%esi\n\t"
      "jmp .LFUN_0011b2a0_9\n\t"
      ".LFUN_0011b2a0_20:\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0011b2a0_jt:\n\t"
      ".long .LFUN_0011b2a0_3\n\t"
      ".long .LFUN_0011b2a0_4\n\t"
      ".long .LFUN_0011b2a0_5\n\t"
      ".long .LFUN_0011b2a0_6\n\t"
      ".long .LFUN_0011b2a0_7\n\t"
      ".long .LFUN_0011b2a0_8\n\t"
      ".long .LFUN_0011b2a0_15\n\t"
      ".long .LFUN_0011b2a0_14\n\t"
      ".text\n\t"
      :
      : [c11a430] "m"(b11b2a0_c11a430), [c8e0b0] "m"(b11b2a0_c8e0b0), [c11a8e0] "m"(b11b2a0_c11a8e0), [c8dff0] "m"(b11b2a0_c8dff0), [c11a700] "m"(b11b2a0_c11a700), [c11add0] "m"(b11b2a0_c11add0), [c11b2a0] "m"(b11b2a0_c11b2a0), [memset] "m"(b11b2a0_memset)
      : "memory");
}
#else
#error "FUN_0011b2a0: clang naked draft required"
#endif


/* FUN_0011b650 (0x11b650) — readable C lift (restored pre-naked). */
bool FUN_0011b650(int definition, short version, void *data,
                  char *buffer, short *buffer_size_out,
                  short maximum_buffer_size)
{
  int encode_state[4];
  char version_byte;

  if (definition == 0) {
    display_assert("packet_definition",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x3d, 1);
    system_exit(-1);
  }
  if (buffer == 0 || buffer_size_out == NULL) {
    display_assert("buffer && buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x3e, 1);
    system_exit(-1);
  }
  if (maximum_buffer_size < 0) {
    display_assert("maximum_buffer_size>=0",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x3f, 1);
    system_exit(-1);
  }
  verify_packet_definition((packet_definition *)definition);
  encode_state_new(encode_state, (int)buffer, (int)maximum_buffer_size);
  if (version == -1) {
    version = *(short *)(definition + 10);
  }
  if (0 < *(short *)(definition + 10)) {
    version_byte = (char)version;
    encode_raw_data(encode_state, (int)&version_byte, 1, 1);
  }
  encode_packet_fields(definition, encode_state, version, data, 0,
                       *(int *)(definition + 0xc), 0);
  *buffer_size_out = (short)encode_state[1];
  return (char)encode_state[3] == '\0';
}


/* FUN_0011b750 (0x11b750) — readable C lift (restored pre-naked). */
bool FUN_0011b750(int definition, int encoded_packet, short encoded_packet_size,
                  int decoded_packet, unsigned short *version_out,
                  short *bytes_consumed_out)
{
  unsigned char version_byte;
  unsigned short version;
  bool result;
  int decode_state[4];

  result = 0;
  if (encoded_packet == 0) {
    display_assert("encoded_packet",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x5f, 1);
    system_exit(-1);
  }
  if (decoded_packet == 0) {
    display_assert("decoded_packet",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x60, 1);
    system_exit(-1);
  }
  if (encoded_packet_size < 0) {
    display_assert("encoded_packet_size>=0",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x61, 1);
    system_exit(-1);
  }
  verify_packet_definition((packet_definition *)definition);
  FUN_0011a2d0(decode_state, (void *)encoded_packet,
               (int)encoded_packet_size);
  if (*(short *)(definition + 10) == 0) {
    version = 0;
  }
  else {
    version_byte = FUN_0011a560(decode_state);
    version = (unsigned short)version_byte;
  }
  if ((short)version <= *(short *)(definition + 10)) {
    FUN_0011b2a0(definition, decode_state, version,
                 (unsigned short *)decoded_packet, 0,
                 *(short **)(definition + 0xc), 0);
    result = 1;
    if ((char)decode_state[3] == '\0') goto done;
  }
  result = 0;
done:
  if (version_out != NULL) {
    *version_out = version;
  }
  if (bytes_consumed_out != NULL) {
    *bytes_consumed_out = (short)decode_state[1];
  }
  return result;
}


/* ========================================================================
 * hashtable.c — Hash table implementation
 * ======================================================================== */

/* hashtable_new (0x11b850) — readable C lift.
 *
 * Initialise a hashtable header and its inline array storage. Requires
 * table != NULL, key_size > 0, element_size > 0, and 0 < load_factor <= 1.
 */
void hashtable_new(void *table, short key_size, short element_size, float load_factor,
                   int param_5, int param_6)
{
  char *t = (char *)table;

  if (table == NULL) {
    display_assert((const char *)0x28f670, (const char *)0x28f678, 0x29, true);
    system_exit(-1);
  }
  if (key_size <= 0) {
    display_assert((const char *)0x28f664, (const char *)0x28f678, 0x2a, true);
    system_exit(-1);
  }
  if (element_size <= 0) {
    display_assert((const char *)0x28e9ac, (const char *)0x28f678, 0x2b, true);
    system_exit(-1);
  }
  if (!(load_factor > *(float *)0x2533c0 && load_factor <= *(float *)0x2533c8)) {
    display_assert((const char *)0x28f644, (const char *)0x28f678, 0x2c, true);
    system_exit(-1);
  }

  *(float *)(t + 8) = load_factor;
  *(int *)(t + 0x10) = param_5;
  *(int *)(t + 0x14) = param_6;
  *(int16_t *)(t + 0) = key_size;
  *(int16_t *)(t + 2) = element_size;
  *(int16_t *)(t + 4) = 0;
  *(int16_t *)(t + 6) = (int16_t)0xffff;
  array_new((int *)(t + 0x1c), (int)key_size + (int)element_size);
  *(int *)(t + 0x18) = 0;
}


/* hashtable_set_user_data — store a user-data/callback value at offset 0x0c
 * of the hashtable header (0x11b950).
 *
 * Original source: c:\halo\SOURCE\memory\hashtable.c
 * Offset 0x0c sits between the load_factor float (0x08) and the param_5 field
 * (0x10) established by hashtable_new.  This is a simple field setter with no
 * validation.
 */
void hashtable_set_user_data(void *table, int user_data)
{
  char *t = (char *)table;
  *(int *)(t + 0x0c) = user_data;
}

/* hashtable_dispose (0x11b960) — readable C lift. */
extern char DAT_0028f678[];
extern char DAT_0028f69c[];

void hashtable_dispose(short *table)
{
  float load;
  int shift;
  void *ptr;
  char ok;

  ok = 0;
  if (table != NULL && table[0] > 0 && table[1] > 0) {
    load = *(float *)((char *)table + 8);
    if (load > *(float *)0x2533c0 && load <= *(float *)0x2533c8) {
      shift = (int)*(short *)((char *)table + 6);
      if (shift == -1 || (1 << (shift & 0xff)) == *(int *)((char *)table + 0x20))
        ok = 1;
    }
  }
  if (!ok) {
    display_assert(DAT_0028f69c, DAT_0028f678, 0x6e, true);
    system_exit(-1);
  }
  FUN_00117cf0((int *)((char *)table + 0x1c));
  ptr = *(void **)((char *)table + 0x18);
  if (ptr != NULL)
    debug_free(ptr, DAT_0028f678, 0x74);
}

/* FUN_0011ba00 (0x11ba00) — readable C lift. */
int FUN_0011ba00(unsigned char *key, unsigned int key_size)
{
  unsigned int remain;
  int hash;
  short idx;
  unsigned char *p;
  int term;
  unsigned short byte_v;
  int prime;

  remain = key_size;
  hash = 0;
  idx = 0;
  if (remain == 0)
    return 0;
  p = key;
  for (;;) {
    if (idx == 15) {
      idx = 0;
      remain -= 15;
    }
    byte_v = *p;
    prime = (int)hashtable_primes[idx];
    prime = (prime & ~0xffff) | (unsigned short)((unsigned short)prime * byte_v);
    hash += prime;
    idx++;
    p++;
    term = (int)idx;
    if ((unsigned int)term >= remain)
      break;
  }
  return hash;
}


/* FUN_0011ba50 (0x11ba50) — XBE naked draft (batch 84). */
#if defined(__clang__)
static int (*const b11ba50_c11ba00)(unsigned char *key, unsigned int key_size) = (void *)FUN_0011ba00;
static int (*const b11ba50_c117ee0)(int *array, int index, int element_size) = (void *)FUN_00117ee0;
static int (*const b11ba50_c8da40)(const void *a, const void *b, int size) = (void *)csmemcmp;

__attribute__((naked, noinline))
int FUN_0011ba50(short *table __attribute__((unused)), void *key __attribute__((unused)), unsigned short *slot_index_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_0011ba50_1\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "jmp .LFUN_0011ba50_2\n\t"
      ".LFUN_0011ba50_1:\n\t"
      "movswl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11ba00]\n\t"
      ".LFUN_0011ba50_2:\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x18(%%esi), %%ebx\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x20(%%esi), %%di\n\t"
      "decw %%di\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl $1, %%edx\n\t"
      "andl %%eax, %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, (%%ebx,%%ecx,4)\n\t"
      "je .LFUN_0011ba50_6\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0011ba50_3:\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "cmpw 0x4(%%esi), %%dx\n\t"
      "jge .LFUN_0011ba50_8\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "je .LFUN_0011ba50_4\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x14(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "movzbl %%al, %%eax\n\t"
      "jmp .LFUN_0011ba50_5\n\t"
      ".LFUN_0011ba50_4:\n\t"
      "movswl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_0011ba50_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011ba50_7\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%esi), %%cx\n\t"
      "incl %%edi\n\t"
      "decw %%cx\n\t"
      "movl $1, %%edx\n\t"
      "andl %%ecx, %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl 0x18(%%esi), %%ebx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, (%%ebx,%%ecx,4)\n\t"
      "jne .LFUN_0011ba50_3\n\t"
      ".LFUN_0011ba50_6:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw %%di, (%%edx)\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011ba50_7:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movw %%di, (%%ecx)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011ba50_8:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw %%di, (%%eax)\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11ba00] "m"(b11ba50_c11ba00), [c117ee0] "m"(b11ba50_c117ee0), [c8da40] "m"(b11ba50_c8da40)
      : "memory");
}
#else
#error "FUN_0011ba50: clang naked draft required"
#endif


/* FUN_0011bb70 (0x11bb70) — readable C lift. */
int FUN_0011bb70(short *table, void *key)
{
  unsigned short slot;
  float load;
  unsigned short bits;
  int bad;
  int *elem;
  bad = 0;
  if (table == 0)
    bad = 1;
  else if (table[0] <= 0 || table[1] <= 0)
    bad = 1;
  else {
    load = *(float *)((char *)table + 8);
    if (!(load > *(float *)0x2533c0 && load <= *(float *)0x2533c8))
      bad = 1;
    bits = *(unsigned short *)((char *)table + 6);
    if (bits != (unsigned short)-1 && (1 << (bits & 31)) != *(int *)((char *)table + 0x20))
      bad = 1;
  }
  if (bad) {
    display_assert((const char *)0x28f69c, (const char *)0x28f678, 0x4d, 1);
    system_exit(-1);
  }
  if (table[2] == 0)
    return 0;
  if (!FUN_0011ba50(table, key, &slot))
    return 0;
  elem = (int *)FUN_00117ee0((int *)((char *)table + 0x1c), (int)(short)slot, (int)table[1]);
  return (int)((char *)elem + (int)table[0]);
}

/* FUN_0011bc20 (0x11bc20) — readable C lift (restored pre-naked). */
void FUN_0011bc20(short *table, void *key)
{
  unsigned int *bitmap_word;
  unsigned int bit_mask;
  short *psVar3;
  char found;
  unsigned short next_slot;
  int next_element;
  unsigned short key_hash;
  short removed_slot;
  int cur_pos;

  psVar3 = table;
  if (((((table == NULL) || (*table < 1)) || (table[1] < 1)) ||
       ((*(float *)(table + 4) <= 0.0f) ||
        (*(float *)(table + 4) > 1.0f))) ||
      ((table[3] != -1 &&
        ((1 << ((unsigned short)table[3] & 0x1f)) !=
         *(int *)(table + 0x10))))) {
    display_assert("hashtable_valid(table)",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0xc3, 1);
    system_exit(-1);
  }
  if (key == NULL) {
    display_assert("key",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0xc4, 1);
    system_exit(-1);
  }
  found = (char)FUN_0011ba50(psVar3, key, (unsigned short *)&removed_slot);
  if (found == '\0') {
    display_assert("removing key not in hashtable",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0xe1, 1);
    system_exit(-1);
    return;
  }
  next_slot = (unsigned short)((int)(removed_slot + 1) &
              (int)(unsigned short)(psVar3[0x10] - 1));
  cur_pos = (int)(short)next_slot;
  bit_mask = *(unsigned int *)(*(int *)(psVar3 + 0xc) +
             (cur_pos >> 5) * 4) & (1 << ((unsigned char)next_slot & 0x1f));
  while (bit_mask != 0) {
    next_element = array_get_element((int *)(psVar3 + 0xe), cur_pos,
                                     (int)psVar3[1]);
    if (*(int *)(psVar3 + 8) == 0) {
      key_hash = (unsigned short)FUN_0011ba00(
        (unsigned char *)next_element, (unsigned int)*psVar3);
    }
    else {
      key_hash = (unsigned short)(*(int (**)(int, int))(psVar3 + 8))(
        *(int *)(psVar3 + 6), next_element);
    }
    key_hash = (unsigned short)(psVar3[0x10] - 1) & key_hash;
    if ((short)key_hash < (short)next_slot) {
      if ((short)removed_slot < (short)key_hash) {
        goto no_shift;
      }
      if ((short)removed_slot < (short)next_slot) {
        goto do_shift;
      }
    } else if ((short)key_hash > (short)next_slot) {
      if ((short)removed_slot >= (short)key_hash) {
        goto do_shift;
      }
      if ((short)removed_slot < (short)next_slot) {
        goto do_shift;
      }
    }
    goto no_shift;
    do_shift:
    {
      int src_element;
      int dst_element;
      src_element = array_get_element((int *)(psVar3 + 0xe), cur_pos,
                                      (int)psVar3[1]);
      dst_element = array_get_element((int *)(psVar3 + 0xe), (int)removed_slot,
                                      (int)psVar3[1]);
      csmemcpy((void *)dst_element, (void *)src_element,
               *(int *)(psVar3 + 0xe));
      removed_slot = (short)next_slot;
    }
    no_shift:
    (void)0;
    next_slot = (unsigned short)((int)(next_slot + 1) &
                (int)(unsigned short)(psVar3[0x10] - 1));
    cur_pos = (int)(short)next_slot;
    bit_mask = *(unsigned int *)(*(int *)(psVar3 + 0xc) +
               (cur_pos >> 5) * 4) & (1 << ((unsigned char)next_slot & 0x1f));
  }
  bitmap_word = (unsigned int *)(*(int *)(psVar3 + 0xc) +
                ((int)removed_slot >> 5) * 4);
  *bitmap_word = *bitmap_word & ~(1 << ((unsigned char)removed_slot & 0x1f));
}



/* FUN_0011be10 (0x11be10) — readable C lift. */
int FUN_0011be10(short *table /* @<eax> */, void *key)
{
  unsigned short slot;
  int dest;
  unsigned int *bits;
  unsigned int mask;
  int idx;

  if (FUN_0011ba50(table, key, &slot)) {
    display_assert((const char *)0x28f6d4, (const char *)0x28f678, 0xf1, 1);
    system_exit(-1);
    return 0;
  }
  dest = FUN_00117ee0((int *)(table + 0xe), (int)slot, (int)table[1]);
  csmemcpy((void *)dest, key, (unsigned int)(int)table[0]);
  idx = (int)slot;
  bits = (unsigned int *)(*(unsigned int *)(table + 0xc) + (unsigned int)((idx >> 5) * 4));
  mask = 1u << (idx & 0x1f);
  *bits |= mask;
  table[2] = (short)((int)table[2] + 1);
  return dest + (int)table[0];
}

/* FUN_0011beb0 (0x11beb0) — readable C lift (restored pre-naked). */
int FUN_0011beb0(short *table, short growth_bits)
{
  short *array_hdr;
  unsigned short old_capacity_bits;
  short old_count;
  int old_bitmap;
  int old_array_data;
  int old_array_capacity;
  int old_array_p2;
  int new_capacity;
  int bitmap_bytes;
  int new_bitmap;
  int i;
  short idx;
  int element_ptr;
  int dest_ptr;

  old_count = table[2];
  old_bitmap = *(int *)(table + 0xc);
  array_hdr = table + 0xe;
  old_capacity_bits = (unsigned short)table[3];
  old_array_data = *(int *)array_hdr;
  old_array_capacity = *(int *)(table + 0x10);
  old_array_p2 = *(int *)(table + 0x12);
  if (((*table < 1) || (table[1] < 1)) ||
      ((*(float *)(table + 4) <= 0.0f) ||
       (*(float *)(table + 4) > 1.0f) ||
       ((old_capacity_bits != 0xffff &&
         ((1 << ((unsigned char)old_capacity_bits & 0x1f)) !=
          *(int *)(table + 0x10)))))) {
    display_assert("hashtable_valid(table)",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x86, 1);
    system_exit(-1);
  }
  if (growth_bits < 1) {
    display_assert("growth_bits>0",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x87, 1);
    system_exit(-1);
  }
  if ((int)growth_bits + (int)table[3] > 0xf) {
    display_assert("table->capacity_bits+growth_bits<SHORT_BITS",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x88, 1);
    system_exit(-1);
  }
  table[3] = table[3] + growth_bits;
  new_capacity = (int)(short)(1 << ((unsigned char)table[3] & 0x1f));
  bitmap_bytes = ((new_capacity + 0x1f) >> 5) << 2;
  table[2] = 0;
  new_bitmap = (int)debug_malloc(bitmap_bytes, 0,
    "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x8f);
  *(int *)(table + 0xc) = new_bitmap;
  if (new_bitmap != 0) {
    array_reset((int *)array_hdr, *(int *)array_hdr);
    if (array_resize((int *)array_hdr, new_capacity)) {
      csmemset((void *)*(int *)(table + 0xc), 0, bitmap_bytes);
      if (0 < old_array_capacity) {
        idx = 0;
        i = 0;
        do {
          if ((*(unsigned int *)(old_bitmap + (i >> 5) * 4) &
               (1 << ((unsigned char)i & 0x1f))) != 0) {
            element_ptr = array_get_element(&old_array_data, i,
                                            old_array_data);
            dest_ptr = FUN_0011be10(table, (void *)element_ptr);
            csmemcpy((void *)dest_ptr,
                     (void *)(element_ptr + *table),
                     (int)table[1]);
          }
          idx = idx + 1;
          i = (int)idx;
        } while (i < old_array_capacity);
      }
      if (old_bitmap != 0) {
        debug_free((void *)old_bitmap,
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0xa8);
      }
      array_dispose(&old_array_data);
      return 1;
    }
    debug_free((void *)*(int *)(table + 0xc),
               "c:\\halo\\SOURCE\\memory\\hashtable.c", 0xb0);
  }
  table[3] = (short)old_capacity_bits;
  table[2] = old_count;
  *(int *)(table + 0xc) = old_bitmap;
  *(int *)array_hdr = old_array_data;
  *(int *)(table + 0x10) = old_array_capacity;
  *(int *)(table + 0x12) = old_array_p2;
  return 0;
}



/* FUN_0011c0f0 (0x11c0f0) — readable C lift (restored pre-naked). */
int FUN_0011c0f0(short *table, void *key)
{
  char grew;
  int result;

  if (((((table == NULL) || (*table < 1)) || (table[1] < 1)) ||
       ((*(float *)(table + 4) <= 0.0f) ||
        (*(float *)(table + 4) > 1.0f))) ||
      ((table[3] != -1 &&
        ((1 << ((unsigned char)table[3] & 0x1f)) !=
         *(int *)(table + 0x10))))) {
    display_assert("hashtable_valid(table)",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x5d, 1);
    system_exit(-1);
  }
  if ((table[3] == -1) ||
      ((float)*(int *)(table + 0x10) * *(float *)(table + 4) <=
       (float)(int)table[2])) {
    grew = (char)FUN_0011beb0(table, (short)((table[3] == -1) + 1));
    if (grew == '\0') {
      return 0;
    }
  }
  result = FUN_0011be10(table, key);
  return result;
}


/* ========================================================================
 * lra_cache.c — LRU/LRA cache implementation
 * Original source: c:\halo\SOURCE\memory\lra_cache.c
 *
 * Cache struct (0x3c bytes):
 *   +0x00 char[0x20]  name (null-terminated, max 0x1f chars)
 *   +0x20 int         size (total buffer size)
 *   +0x24 void*       base_address (buffer pointer)
 *   +0x28 byte        owns_buffer
 *   +0x2c void*       head_block
 *   +0x30 void(*)(void*,int)  lock_proc
 *   +0x34 void(*)(void*)      unlock_proc
 *   +0x38 int         magic = 0x6c726163 ("lrac")
 *
 * Block header (0x10 bytes, prepended to user data):
 *   +0x00 int         user_data
 *   +0x04 int         flags (bit 0 = in_use, bit 1 = freed/unlocked)
 *   +0x08 int         size
 *   +0x0c void*       next_block
 * ======================================================================== */

/* FUN_0011c1b0 (0x11c1b0) — readable C lift. */
int FUN_0011c1b0(int cache)
{
  int *inner = *(int **)((char *)cache + 0x2c);
  if (inner == 0) {
    return 0;
  }
  if (inner[3] == 0) {
    return 0;
  }
  return 1;
}

/* lra_cache_default_lock — default lock callback (0x11c1d0). */
void FUN_0011c1d0(int *ptr, int user_data)
{
  *ptr = user_data;
}

/* lra_cache_default_unlock — default unlock callback (0x11c1e0). */
void FUN_0011c1e0(int *ptr)
{
  *ptr = 0;
}

/* FUN_0011c210 (0x11c210) — readable C lift. */
extern char DAT_0028f734[];
extern char DAT_0028f768[];

void FUN_0011c210(int cache, int block)
{
  unsigned int magic;
  int size;
  int base;
  int limit;
  int ptr;
  char *msg;

  magic = *(unsigned int *)((char *)block + 4) & 0xfffffffcU;
  if (magic == 0x41626c68U) {
    size = *(int *)((char *)block + 8);
    if (size >= 0) {
      limit = *(int *)((char *)cache + 0x20);
      if (size < limit) {
        base = *(int *)((char *)cache + 0x24);
        ptr = (int)block - base;
        if (ptr >= 0 && size + ptr <= limit) {
          ptr = *(int *)((char *)block + 0xc);
          if (ptr == 0)
            ptr = 0;
          else {
            ptr = ptr - base;
            if (ptr < 0 || (unsigned)(ptr + 0x10) > (unsigned)limit)
              goto bad;
          }
          return;
        }
      }
    }
  }
bad:
  msg = csprintf((char *)0x5ab100, DAT_0028f734, cache, cache, block);
  display_assert(msg, DAT_0028f768, 0x18e, true);
  system_exit(-1);
}

/* FUN_0011c290 (0x11c290) — readable C lift. */
extern char DAT_0028f768[];
extern char DAT_0028f78c[];
extern char DAT_0028f7b4[];

void FUN_0011c290(int cache)
{
  char *msg;

  if (cache == 0) {
    display_assert(DAT_0028f7b4, DAT_0028f768, 0x198, true);
    system_exit(-1);
  }
  if (*(int *)((char *)cache + 0x38) != 0x6c726163
      || *(int *)((char *)cache + 0x24) == 0
      || *(int *)((char *)cache + 0x20) < 0) {
    msg = csprintf((char *)0x5ab100, DAT_0028f78c, cache, cache);
    display_assert(msg, DAT_0028f768, 0x1a2, true);
    system_exit(-1);
  }
  if (*(int *)((char *)cache + 0x2c) != 0)
    FUN_0011c210(cache, *(int *)((char *)cache + 0x2c));
}

/* FUN_0011c310 (0x11c310) — readable C lift.
 *
 * Allocate and initialise an lra_cache header. Optional lock/unlock default to
 * FUN_0011c1d0/FUN_0011c1e0; optional base_address is allocated when NULL.
 */
int FUN_0011c310(const char *name, int size, void (*lock_proc)(void *, int),
                 void (*unlock_proc)(void *), void *base_address)
{
  char *cache;
  void *base;
  char owns_buffer;

  cache = (char *)debug_malloc(0x3c, false, (const char *)0x28f768, 0x56);
  if (size < 0) {
    display_assert((const char *)0x267a80, (const char *)0x28f768, 0x58, true);
    system_exit(-1);
  }
  if (lock_proc == NULL || unlock_proc == NULL) {
    lock_proc = (void (*)(void *, int))0x11c1d0;
    unlock_proc = (void (*)(void *))0x11c1e0;
  }
  if (cache == NULL)
    return 0;

  base = base_address;
  owns_buffer = 0;
  if (base == NULL) {
    base = debug_malloc((uint32_t)size, false, (const char *)0x28f768, 0x66);
    owns_buffer = 1;
    if (base == NULL) {
      debug_free(cache, (const char *)0x28f768, 0x7e);
      return 0;
    }
  }
  if (((uintptr_t)base & 3) != 0) {
    display_assert((const char *)0x28f7bc, (const char *)0x28f768, 0x6b, true);
    system_exit(-1);
  }

  csmemset(cache, 0, 0x3c);
  csstrncpy(cache, name, 0x1f);
  cache[0x1f] = 0;
  *(int *)(cache + 0x20) = size;
  *(void **)(cache + 0x24) = base;
  cache[0x28] = owns_buffer;
  *(int *)(cache + 0x2c) = 0;
  *(void (**)(void *, int))(cache + 0x30) = lock_proc;
  *(void (**)(void *))(cache + 0x34) = unlock_proc;
  *(int *)(cache + 0x38) = 0x6c726163;
  FUN_0011c290((int)cache);
  return (int)cache;
}


/* FUN_0011c430 (0x11c430) — readable C lift. */
extern char DAT_0028f768[];
void FUN_0011c430(void *cache)
{
  FUN_0011c290((int)cache);
  if (*((char *)cache + 0x28) != 0)
    debug_free(*(void **)((char *)cache + 0x24), DAT_0028f768, 0x8c);
  debug_free(cache, DAT_0028f768, 0x8d);
}

/* FUN_0011c480 (0x11c480) — readable C lift from XBE leaf. */
void FUN_0011c480(int cache)
{
  unsigned char *c;
  unsigned char *node;
  void (*cb)(int);

  c = (unsigned char *)cache;
  FUN_0011c290(cache);
  if (*(int *)(c + 0x2c) == 0 || *(int *)(c + 0x24) == 0) {
    *(int *)(c + 0x2c) = 0;
    return;
  }
  for (node = *(unsigned char **)(c + 0x24); node != 0;
       node = *(unsigned char **)(node + 0xc)) {
    if ((node[4] & 2) == 0) {
      cb = *(void (**)(int))(c + 0x34);
      cb(*(int *)node);
      *(int *)(node + 4) = (*(int *)(node + 4) & ~1) | 2;
    }
  }
  *(int *)(c + 0x2c) = 0;
}

/* FUN_0011c4d0 (0x11c4d0) — readable C lift from XBE leaf. */
void FUN_0011c4d0(int cache, void *pointer)
{
  extern char DAT_00267eec[];
  extern char DAT_0028f768[];
  unsigned char *hdr;
  void (*fn)(int);

  if (pointer == 0) {
    display_assert(DAT_00267eec, DAT_0028f768, 0x11a, true);
    system_exit(-1);
  }
  hdr = (unsigned char *)pointer - 0x10;
  FUN_0011c290(cache);
  FUN_0011c210(cache, (int)hdr);
  if ((*(int *)(hdr + 4) & 2) == 0) {
    fn = *(void (**)(int))((char *)cache + 0x34);
    fn(*(int *)hdr);
    *(int *)(hdr + 4) = (*(int *)(hdr + 4) & ~1) | 2;
  }
}




/* ========================================================================
 * Already-ported: initialize_network_game_packets (0x12b640)
 * ======================================================================== */

void initialize_network_game_packets(void)
{
  verify_packet_group_definitions(&s_network_game_messages_group);
}

/* Static 0x604-byte output buffer for encode_network_game_message (0x46e8d0).
 * Passed as the pre-allocated destination to create_message(); only one caller
 * exists so this is safe as a module-level static. */
static char s_network_game_message_buffer[0x604];

/* encode_network_game_message — validate, encode and wrap a typed network
 * game message struct into a transmittable message packet (0x12b700).
 *
 * Validates that message_struct_size matches the expected size for the given
 * type, encodes the struct into a 1536-byte stack buffer using the global
 * packet group definition, then wraps the encoded bytes in a message header
 * and returns a pointer to the resulting message, or NULL on failure.
 */
void *encode_network_game_message(int type, void *data,
                                  int16_t message_struct_size)
{
  char encoded_buf[0x600];
  int32_t encoded_size;
  const char *assertion;
  int assertion_line;

  encoded_size = 0x600;

  switch ((int16_t)type) {
  case 0:
    if (message_struct_size == 0xc)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_broadcast_game_search)";
    assertion_line = 0xa0;
    break;
  case 1:
    if (message_struct_size == 8)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_ping)";
    assertion_line = 0xa1;
    break;
  case 2:
    if (message_struct_size == 0x114)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_game_advertise)";
    assertion_line = 0xa4;
    break;
  case 3:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_pong)";
    assertion_line = 0xa5;
    break;
  case 4:
    if (message_struct_size == 8)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_machine_accepted)";
    assertion_line = 0xa8;
    break;
  case 5:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_machine_rejected)";
    assertion_line = 0xa9;
    break;
  case 6:
    if (message_struct_size == 0x434)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_game_settings_update)";
    assertion_line = 0xaa;
    break;
  case 7:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_pregame_countdown)";
    assertion_line = 0xab;
    break;
  case 8:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_begin_game)";
    assertion_line = 0xad;
    break;
  case 9:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_graceful_game_exit_pregame)";
    assertion_line = 0xae;
    break;
  case 10:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_pregame_keep_alive)";
    assertion_line = 0xac;
    break;
  case 11:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_postgame_keep_alive)";
    assertion_line = 0xb1;
    break;
  case 12:
    if (message_struct_size == 0x50)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_join_game_request)";
    assertion_line = 0xb4;
    break;
  case 13:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_add_player_request_pregame)";
    assertion_line = 0xb5;
    break;
  case 14:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_remove_player_"
                "request_pregame)";
    assertion_line = 0xb6;
    break;
  case 15:
    if (message_struct_size == 0x44)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_settings_request)";
    assertion_line = 0xb7;
    break;
  case 16:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_player_settings_request)";
    assertion_line = 0xb8;
    break;
  case 17:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_game_start_request)";
    assertion_line = 0xb9;
    break;
  case 18:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_graceful_game_exit_pregame)";
    assertion_line = 0xba;
    break;
  case 19:
    if (message_struct_size == 0x100)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_map_is_precached_pregame)";
    assertion_line = 0xbb;
    break;
  case 20:
    if (message_struct_size == 0x210)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_game_update)";
    assertion_line = 0xbe;
    break;
  case 21:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_add_player_ingame)";
    assertion_line = 0xbf;
    break;
  case 22:
    if (message_struct_size == 0x24)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_remove_player_ingame)";
    assertion_line = 0xc0;
    break;
  case 23:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_game_over)";
    assertion_line = 0xc1;
    break;
  case 24:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_loaded)";
    assertion_line = 0xc4;
    break;
  case 25:
    if (message_struct_size == 0x88)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_game_update)";
    assertion_line = 0xc5;
    break;
  case 26:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_add_player_request_ingame)";
    assertion_line = 0xc6;
    break;
  case 27:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_remove_player_"
                "request_ingame)";
    assertion_line = 0xc7;
    break;
  case 28:
    if (message_struct_size == 0x10)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_host_crashed_cry_for_help)";
    assertion_line = 0xc9;
    break;
  case 29:
    if (message_struct_size == 0x10)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_join_new_host)";
    assertion_line = 0xca;
    break;
  case 30:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_switch_to_pregame)";
    assertion_line = 0xcd;
    break;
  case 31:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_graceful_game_exit_postgame)";
    assertion_line = 0xce;
    break;
  case 32:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_remove_player_"
                "request_postgame)";
    assertion_line = 0xd1;
    break;
  case 33:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_switch_to_pregame)";
    assertion_line = 0xd2;
    break;
  case 34:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_graceful_game_exit_postgame)";
    assertion_line = 0xd3;
    break;
  default:
    assertion = "unknown network game message structure type";
    assertion_line = 0xd5;
    break;
  }

  display_assert(assertion, "c:\\halo\\SOURCE\\networking\\network_messages.c",
                 assertion_line, 1);
  system_exit(-1);

size_ok:
  if (data == NULL || (int16_t)encoded_size < 1) {
    display_assert("message_struct && encoded_message && encoded_message_size "
                   "&& (*encoded_message_size>0)",
                   "c:\\halo\\SOURCE\\networking\\network_messages.c", 0x161,
                   1);
    system_exit(-1);
  }

  if (!encode_packet_group(&s_network_game_messages_group, data, encoded_buf,
                           &encoded_size, type, 1)) {
    network_game_log("encode_network_game_message() failed");
    return NULL;
  }

  {
    void *msg = (void *)create_message(3, encoded_buf, encoded_size,
                                       s_network_game_message_buffer, 0x604);
    if (msg == NULL) {
      network_game_log("create_message() failed");
    }
    return msg;
  }
}
