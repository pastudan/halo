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

/* decode_string — copy a string from source into the state buffer (0x11a230).
 * Source: data_encoding.c line 0xb6. */
bool FUN_0011a230(int *state, const char *source, short max_length)
{
  short string_length;
  int dest;

  string_length = strnlen(source, (int)max_length);
  dest = *state + state[1];
  if (state[2] < (int)string_length + 1 + state[1]) {
    display_assert("state->offset+string_length+1<=state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0xb6, 1);
    system_exit(-1);
  }
  if ((state[1] + 1 + (int)string_length <= state[2]) &&
      ((char)state[3] == '\0')) {
    csstrncpy((char *)dest, source, (int)string_length);
    *(char *)((int)string_length + dest) = 0;
    state[1] = state[1] + (int)string_length + 1;
    return (char)state[3] == '\0';
  }
  *(char *)(state + 3) = 1;
  return (char)state[3] == '\0';
}

/* decode_state_new — initialize a decode state struct (0x11a2d0).
 * Source: data_encoding.c line 0xcc. */
void FUN_0011a2d0(int *state, void *buffer, int buffer_size)
{
  if (buffer == NULL) {
    display_assert("buffer",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0xcc, 1);
    system_exit(-1);
  }
  if (buffer_size < 0) {
    display_assert("buffer_size>=0",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0xcd, 1);
    system_exit(-1);
  }
  csmemset(state, 0, 0x10);
  *state = (int)buffer;
  state[2] = buffer_size;
}

/* decode_structures — byte-swap structures in-place in the buffer (0x11a340).
 * Source: data_encoding.c line 0xde. */
int FUN_0011a340(int *state, short count, void *bs_definition)
{
  short total_size;
  int result;

  if (((state == NULL) || (*state == 0) || (state[1] < 0)) ||
      (state[2] < state[1])) {
    display_assert("state && state->buffer && state->offset>=0 && "
                   "state->offset<=state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0xde, 1);
    system_exit(-1);
  }
  if (count < 0) {
    display_assert("structure_count>=0",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0xdf, 1);
    system_exit(-1);
  }
  if (bs_definition == NULL) {
    display_assert("bs_definition",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0xe0, 1);
    system_exit(-1);
  }
  total_size = *(short *)((char *)bs_definition + 4) * count;
  if (((int)total_size + state[1] <= state[2]) && ((char)state[3] == '\0')) {
    result = *state + state[1];
    if (total_size != 0) {
      byte_swap_structures(bs_definition, (void *)result, (int)count);
      state[1] = state[1] + (int)total_size;
    }
    return result;
  }
  *(char *)(state + 3) = 1;
  return 0;
}

/* decode_raw_data — byte-swap raw elements in the buffer (0x11a430).
 * Source: data_encoding.c line 0x100. */
__declspec(noinline) int FUN_0011a430(int *state, short count, int element_size)
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

/* decode_byte — read a single byte from the decode buffer (0x11a560).
 * Source: data_encoding.c. */
__declspec(noinline) unsigned char FUN_0011a560(int *state)
{
  int new_offset;
  unsigned char *ptr;

  if (((state == NULL) || (*state == 0) || (state[1] < 0)) ||
      (state[2] < state[1])) {
    display_assert("state && state->buffer && state->offset>=0 && "
                   "state->offset<=state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x100, 1);
    system_exit(-1);
  }
  new_offset = state[1] + 1;
  if ((state[2] < new_offset) || ((char)state[3] != '\0')) {
    *(unsigned char *)(state + 3) = 1;
  }
  else {
    ptr = (unsigned char *)(*state + state[1]);
    state[1] = new_offset;
    if (ptr != NULL) {
      return *ptr;
    }
  }
  return 0;
}

/* decode_short — read and byte-swap a 16-bit value from the buffer (0x11a5d0).
 * Source: data_encoding.c. */
short FUN_0011a5d0(int *state)
{
  short *ptr;

  if (((state == NULL) || (*state == 0) || (state[1] < 0)) ||
      (state[2] < state[1])) {
    display_assert("state && state->buffer && state->offset>=0 && "
                   "state->offset<=state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x100, 1);
    system_exit(-1);
  }
  if ((state[2] < state[1] + 2) || ((char)state[3] != '\0')) {
    *(unsigned char *)(state + 3) = 1;
  }
  else {
    ptr = (short *)(*state + state[1]);
    byte_swap_raw(ptr, 1, -2);
    state[1] = state[1] + 2;
    if (ptr != NULL) {
      return *ptr;
    }
  }
  return 0;
}

/* decode_long — read and byte-swap a 32-bit value from the buffer (0x11a650).
 * Source: data_encoding.c. */
int FUN_0011a650(int *state)
{
  int *ptr;

  if (((state == NULL) || (*state == 0) || (state[1] < 0)) ||
      (state[2] < state[1])) {
    display_assert("state && state->buffer && state->offset>=0 && "
                   "state->offset<=state->buffer_size",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x100, 1);
    system_exit(-1);
  }
  if ((state[2] < state[1] + 4) || ((char)state[3] != '\0')) {
    *(unsigned char *)(state + 3) = 1;
  }
  else {
    ptr = (int *)(*state + state[1]);
    byte_swap_raw(ptr, 1, -4);
    state[1] = state[1] + 4;
    if (ptr != NULL) {
      return *ptr;
    }
  }
  return 0;
}

/* decode_long_long — read and byte-swap an 8-byte value (0x11a6d0).
 * Source: data_encoding.c. Wrapper around decode_raw_data(state, 1, -8). */
int64_t FUN_0011a6d0(int *state)
{
  int64_t *ptr;

  ptr = (int64_t *)FUN_0011a430(state, 1, -8);
  if (ptr != NULL) {
    return *ptr;
  }
  return 0;
}

/* decode_value — width-adaptive read based on maximum_value (0x11a700).
 * Source: data_encoding.c line 0x141. */
__declspec(noinline) unsigned int FUN_0011a700(int *state, int maximum_value)
{
  if (maximum_value < 1) {
    display_assert("maximum_value>0",
                   "c:\\halo\\SOURCE\\memory\\data_encoding.c", 0x141, 1);
    system_exit(-1);
  }
  if (maximum_value < 0x100) {
    return (unsigned int)FUN_0011a560(state) & 0xff;
  }
  if (maximum_value < 0x10000) {
    return (unsigned int)(unsigned short)FUN_0011a5d0(state);
  }
  return (unsigned int)FUN_0011a650(state);
}

/* decode_element_array — read count + structures from buffer (0x11a770).
 * Source: data_encoding.c line 0x15c. */
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

/* decode_string_read — scan for NUL-terminated string in buffer (0x11a8e0).
 * Source: data_encoding.c. */
__declspec(noinline) char *FUN_0011a8e0(int *state, unsigned short max_length)
{
  int offset;
  short scan_count;
  char *base;

  offset = state[1];
  base = (char *)(*state + offset);
  scan_count = 0;
  if (offset >= state[2])
    goto overflow;
  while (state[1] + (int)scan_count < state[2]) {
    if (base[(int)scan_count] == '\0') {
      state[1] = (int)scan_count + 1 + offset;
      return base;
    }
    scan_count = scan_count + 1;
  }
overflow:
  *(unsigned char *)(state + 3) = 1;
  return NULL;
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

/* decode_packet_group — decode an encoded packet from a group (0x11aa40).
 * Source: data_packet_groups.c lines 0x49-0x4d. */
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
static int (*const b11b2a0_c11a430)(int *state, short count, int element_size) = FUN_0011a430;
static void * (*const b11b2a0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static char * (*const b11b2a0_c11a8e0)(int *state, unsigned short max_length) = FUN_0011a8e0;
static char * (*const b11b2a0_c8dff0)(char *destination, const char *source) = csstrcpy;
static unsigned int (*const b11b2a0_c11a700)(int *state, int maximum_value) = FUN_0011a700;
static void (*const b11b2a0_c11add0)(packet_definition *def, short *param_2, short *param_3, short *param_4) = compute_packet_field_sizes;
static void (*const b11b2a0_c11b2a0)(int definition, int *decode_state, unsigned short version, unsigned short *output, short *decoded_size_out, short *field_defs, short *field_count_out) = FUN_0011b2a0;
static void *(*const b11b2a0_memset)(void *, int, unsigned int) = csmemset;

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


/* encode_packet — encode a data struct into a packet buffer (0x11b650).
 * Source: data_packets.c lines 0x3d-0x3f. */
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

/* decode_packet — decode an encoded packet into a data struct (0x11b750).
 * Source: data_packets.c lines 0x5f-0x61. */
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

/* Initialize a hashtable header.
 * Source: c:\halo\SOURCE\memory\hashtable.c lines 0x29-0x2c (41-44).
 * Asserts: table non-NULL, key_size>0, element_size>0, 0<load_factor<=1.
 * Byte layout of *table (all offsets confirmed from disassembly):
 *   +0x00 int16  key_size
 *   +0x02 int16  element_size
 *   +0x04 int16  count = 0
 *   +0x06 int16  sentinel = -1 (0xffff)
 *   +0x08 float  load_factor
 *   +0x10 dword  param_5
 *   +0x14 dword  param_6
 *   +0x18 dword  0
 *   +0x1c       array header (passed to array_new with key_size+element_size)
 */
void hashtable_new(void *table, short key_size, short element_size,
                   float load_factor, int param_5, int param_6)
{
  char *t;

  if (table == NULL) {
    display_assert("table", "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x29, 1);
    system_exit(-1);
  }
  if (key_size < 1) {
    display_assert("key_size>0", "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x2a,
                   1);
    system_exit(-1);
  }
  if (element_size < 1) {
    display_assert("element_size>0", "c:\\halo\\SOURCE\\memory\\hashtable.c",
                   0x2b, 1);
    system_exit(-1);
  }
  if (!(load_factor > 0.0f && load_factor <= 1.0f)) {
    display_assert("load_factor>0 && load_factor<=1",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x2c, 1);
    system_exit(-1);
  }
  t = (char *)table;
  *(float *)(t + 0x08) = load_factor;
  *(int *)(t + 0x10) = param_5;
  *(int *)(t + 0x14) = param_6;
  *(short *)(t + 0x00) = key_size;
  *(short *)(t + 0x02) = element_size;
  *(short *)(t + 0x04) = 0;
  *(short *)(t + 0x06) = (short)-1;
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

/* hashtable_dispose — validate and dispose a hashtable (0x11b960).
 *
 * Original source: c:\halo\SOURCE\memory\hashtable.c lines 0x6e (110)–0x74
 * (116).
 *
 * Validates the hashtable (null check, key_size>0, element_size>0,
 * load_factor in (0,1], and — when a capacity slot index is set — that the
 * slot count matches 2^slot_index).  On failure fires display_assert with the
 * hashtable_valid predicate string and halts.
 *
 * On success: disposes the embedded array at t+0x1c via FUN_00117cf0, then
 * frees the optional data block at t+0x18 via debug_free if non-NULL.
 *
 * Struct layout (from hashtable_new, offsets are byte offsets):
 *   t+0x00  short   key_size
 *   t+0x02  short   element_size
 *   t+0x04  short   (zero-init)
 *   t+0x06  short   slot_index (-1 when no capacity allocated)
 *   t+0x08  float   load_factor
 *   t+0x0c  int     user_data (set by hashtable_set_user_data)
 *   t+0x10  int     param_5
 *   t+0x14  int     param_6
 *   t+0x18  int     optional data block pointer (freed here)
 *   t+0x1c  []      embedded array header (disposed here)
 *   t+0x20  int     capacity field inside array header (checked when
 *                   slot_index != -1)
 */
void hashtable_dispose(short *table)
{
  char *t;

  if (table == NULL || *table < 1 || table[1] < 1 ||
      !(*(float *)((char *)table + 0x08) > 0.0f &&
        *(float *)((char *)table + 0x08) <= 1.0f) ||
      (table[3] != -1 &&
       (1 << ((unsigned char)table[3] & 0x1f)) != *(int *)((char *)table + 0x20))) {
    display_assert("hashtable_valid(table)",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x6e, 1);
    system_exit(-1);
  }
  t = (char *)table;
  FUN_00117cf0((int *)(t + 0x1c));
  if (*(int *)(t + 0x18) != 0) {
    debug_free(*(void **)(t + 0x18), "c:\\halo\\SOURCE\\memory\\hashtable.c",
               0x74);
  }
}

/* hashtable_hash — default hash function using small primes (0x11ba00).
 * Source: hashtable.c. */
int FUN_0011ba00(unsigned char *key, unsigned int key_size)
{
  int hash;
  short prime_index;

  hash = 0;
  prime_index = 0;
  if (key_size != 0) {
    do {
      if (prime_index == 0xf) {
        prime_index = 0;
        key_size = key_size - 0xf;
      }
      hash = hash + (int)hashtable_primes[prime_index] * (unsigned short)*key;
      prime_index = prime_index + 1;
      key = key + 1;
    } while ((unsigned int)(int)prime_index < key_size);
  }
  return hash;
}

/* hashtable_find_slot — probe for a key in the table (0x11ba50).
 * Source: hashtable.c. Takes table via @ESI register arg. */
int FUN_0011ba50(short *table, void *key, unsigned short *slot_index_out)
{
  unsigned short hash_val;
  short slot;
  int probe_count;
  int element_ptr;
  int cmp_result;
  int found;

  probe_count = 0;
  if (*(int *)(table + 8) != 0) {
    hash_val = (unsigned short)(*(int (**)(int, void *))(table + 8))(
      *(int *)(table + 6), key);
  }
  else {
    hash_val = (unsigned short)FUN_0011ba00((unsigned char *)key,
                                            (unsigned int)*table);
  }
  slot = (short)((unsigned short)(table[0x10] - 1) & hash_val);
  while (1) {
    if ((*(unsigned int *)(*(int *)(table + 0xc) + ((int)slot >> 5) * 4) &
         (1 << ((unsigned char)slot & 0x1f))) == 0) {
      *slot_index_out = (unsigned short)slot;
      return 0;
    }
    if (table[2] <= (short)probe_count) break;
    if (*(int *)(table + 10) != 0) {
      element_ptr = array_get_element((int *)(table + 0xe), (int)slot,
                                      (int)table[1]);
      found = (*(int (**)(int, int, void *))(table + 10))(
        *(int *)(table + 6), element_ptr, key);
    }
    else {
      element_ptr = array_get_element((int *)(table + 0xe), (int)slot,
                                      (int)table[1]);
      cmp_result = csmemcmp((void *)element_ptr, key, (int)*table);
      found = cmp_result == 0;
    }
    if (found != 0) {
      *slot_index_out = (unsigned short)slot;
      return 1;
    }
    probe_count = probe_count + 1;
    slot = (short)((int)(slot + 1) & (int)(table[0x10] - 1));
  }
  *slot_index_out = (unsigned short)slot;
  return 0;
}

/* hashtable_find — look up a key, return pointer to value (0x11bb70).
 * Source: hashtable.c line 0x4d. */
int FUN_0011bb70(short *table, void *key)
{
  short *psVar1;
  char found;
  int element_ptr;
  short slot;

  psVar1 = table;
  if ((((table == NULL) || (*table < 1)) || (table[1] < 1)) ||
      (((*(float *)(table + 4) <= 0.0f) ||
        (*(float *)(table + 4) > 1.0f)) ||
       ((table[3] != -1 &&
         ((1 << ((unsigned char)table[3] & 0x1f)) !=
          *(int *)(table + 0x10)))))) {
    display_assert("hashtable_valid(table)",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0x4d, 1);
    system_exit(-1);
  }
  if (psVar1[2] != 0) {
    found = (char)FUN_0011ba50(psVar1, key, (unsigned short *)&slot);
    if (found != '\0') {
      element_ptr = array_get_element((int *)(psVar1 + 0xe), (int)slot,
                                      (int)psVar1[1]);
      return element_ptr + *psVar1;
    }
  }
  return 0;
}

/* FUN_0011bc20 (0x11bc20) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void (*const b11bc20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11bc20_exitfn)(int) = system_exit;
static int (*const b11bc20_c11ba50)(short *table, void *key, unsigned short *slot_index_out) = FUN_0011ba50;
static int (*const b11bc20_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b11bc20_c11ba00)(unsigned char *key, unsigned int key_size) = FUN_0011ba00;
static void * (*const b11bc20_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_0011bc20(short *table __attribute__((unused)), void *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0011bc20_1\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jle .LFUN_0011bc20_1\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_0011bc20_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0011bc20_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011bc20_1\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011bc20_2\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "je .LFUN_0011bc20_2\n\t"
      ".LFUN_0011bc20_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xc3\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011bc20_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0011bc20_3\n\t"
      "pushl $1\n\t"
      "pushl $0xc4\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x265ba4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011bc20_3:\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11ba50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011bc20_12\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x20(%%esi), %%di\n\t"
      "decw %%di\n\t"
      "incl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl $1, %%eax\n\t"
      "andl %%edx, %%edi\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movswl %%di, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%eax, (%%edx,%%ecx,4)\n\t"
      "je .LFUN_0011bc20_11\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0011bc20_4:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0011bc20_5\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%%ecx\n\t"
      "jmp .LFUN_0011bc20_6\n\t"
      ".LFUN_0011bc20_5:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c11ba00]\n\t"
      ".LFUN_0011bc20_6:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x20(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "decw %%ax\n\t"
      "andl %%ecx, %%eax\n\t"
      "cmpw %%di, %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "jge .LFUN_0011bc20_8\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jl .LFUN_0011bc20_7\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .LFUN_0011bc20_9\n\t"
      ".LFUN_0011bc20_7:\n\t"
      "cmpw %%di, %%ax\n\t"
      ".LFUN_0011bc20_8:\n\t"
      "jle .LFUN_0011bc20_10\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jge .LFUN_0011bc20_9\n\t"
      "cmpw %%di, %%cx\n\t"
      "jge .LFUN_0011bc20_10\n\t"
      ".LFUN_0011bc20_9:\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      ".LFUN_0011bc20_10:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%esi), %%cx\n\t"
      "decw %%cx\n\t"
      "incl %%edi\n\t"
      "movl $1, %%edx\n\t"
      "andl %%ecx, %%edi\n\t"
      "movswl %%di, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "jne .LFUN_0011bc20_4\n\t"
      ".LFUN_0011bc20_11:\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal (%%eax,%%edx,4), %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "notl %%edx\n\t"
      "andl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011bc20_12:\n\t"
      "pushl $1\n\t"
      "pushl $0xe1\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f6b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11bc20_assert), [exitfn] "m"(b11bc20_exitfn), [c11ba50] "m"(b11bc20_c11ba50), [c117ee0] "m"(b11bc20_c117ee0), [c11ba00] "m"(b11bc20_c11ba00), [c8e0b0] "m"(b11bc20_c8e0b0)
      : "memory");
}
#else
#error "FUN_0011bc20: clang naked draft required"
#endif


/* hashtable_put — insert a key into a slot (0x11be10).
 * Source: hashtable.c line 0xf1. Takes table via @EAX register arg. */
int FUN_0011be10(short *table, void *key)
{
  unsigned int *bitmap_word;
  char found;
  int element_ptr;
  short slot;

  found = (char)FUN_0011ba50(table, key, (unsigned short *)&slot);
  if (found != '\0') {
    display_assert("putting key already in hashtable",
                   "c:\\halo\\SOURCE\\memory\\hashtable.c", 0xf1, 1);
    system_exit(-1);
    return 0;
  }
  element_ptr = array_get_element((int *)(table + 0xe), (int)slot,
                                  (int)table[1]);
  csmemcpy((void *)element_ptr, key, (int)*table);
  bitmap_word = (unsigned int *)(*(int *)(table + 0xc) +
                ((int)slot >> 5) * 4);
  *bitmap_word = *bitmap_word | (1 << ((unsigned char)slot & 0x1f));
  table[2] = table[2] + 1;
  return *table + element_ptr;
}

/* FUN_0011beb0 (0x11beb0) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void (*const b11beb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11beb0_exitfn)(int) = system_exit;
static void * (*const b11beb0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b11beb0_c117b20)(int *table, int element_size) = array_new;
static int (*const b11beb0_c117b90)(int *array, int new_count) = array_resize;
static void *(*const b11beb0_memset)(void *, int, unsigned int) = csmemset;
static int (*const b11beb0_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b11beb0_c11be10)(short *table, void *key) = FUN_0011be10;
static void * (*const b11beb0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b11beb0_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b11beb0_c117cf0)(int *table) = FUN_00117cf0;

__attribute__((naked, noinline))
int FUN_0011beb0(short *table __attribute__((unused)), short growth_bits __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $0, (%%esi)\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_0011beb0_1\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_0011beb0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0011beb0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011beb0_1\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011beb0_2\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_0011beb0_2\n\t"
      ".LFUN_0011beb0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x86\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011beb0_2:\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jg .LFUN_0011beb0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x87\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f724\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011beb0_3:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl $0x10, %%eax\n\t"
      "jl .LFUN_0011beb0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x88\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f6f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011beb0_4:\n\t"
      "addw %%di, 0x6(%%esi)\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "pushl $0x8f\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0\n\t"
      "movswl %%ax, %%ebx\n\t"
      "leal 0x1f(%%ebx), %%edi\n\t"
      "sarl $5, %%edi\n\t"
      "shll $2, %%edi\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0x4(%%esi)\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "je .LFUN_0011beb0_11\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117b20]\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117b90]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011beb0_10\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0011beb0_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0011beb0_5:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, (%%ebx,%%ecx,4)\n\t"
      "je .LFUN_0011beb0_6\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movswl (%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%ecx\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c11be10]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011beb0_6:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0011beb0_5\n\t"
      "jmp .LFUN_0011beb0_8\n\t"
      ".LFUN_0011beb0_7:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      ".LFUN_0011beb0_8:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0011beb0_9\n\t"
      "pushl $0xa8\n\t"
      "pushl $0x28f678\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011beb0_9:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117cf0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011beb0_10:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $0xb0\n\t"
      "pushl $0x28f678\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011beb0_12\n\t"
      ".LFUN_0011beb0_11:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_0011beb0_12:\n\t"
      "movw -0x8(%%ebp), %%dx\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw %%dx, 0x6(%%esi)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x18(%%esi)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11beb0_assert), [exitfn] "m"(b11beb0_exitfn), [c8ee60] "m"(b11beb0_c8ee60), [c117b20] "m"(b11beb0_c117b20), [c117b90] "m"(b11beb0_c117b90), [memset] "m"(b11beb0_memset), [c117ee0] "m"(b11beb0_c117ee0), [c11be10] "m"(b11beb0_c11be10), [c8e0b0] "m"(b11beb0_c8e0b0), [c8ef70] "m"(b11beb0_c8ef70), [c117cf0] "m"(b11beb0_c117cf0)
      : "memory");
}
#else
#error "FUN_0011beb0: clang naked draft required"
#endif


/* hashtable_insert — validate, grow if needed, then put (0x11c0f0).
 * Source: hashtable.c line 0x5d. */
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

/* lra_cache_is_active — check if cache has active blocks (0x11c1b0). */
int FUN_0011c1b0(int cache)
{
  if (*(int *)(cache + 0x2c) != 0 &&
      *(int *)(*(int *)(cache + 0x2c) + 0xc) != 0) {
    return 1;
  }
  return 0;
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

/* lra_cache_validate_block — validate a block header (0x11c210).
 * Register args: @EBX = cache, @ESI = block header. */
void FUN_0011c210(int cache, int block)
{
  unsigned int cache_size;
  int block_size;
  int block_offset;
  int next_offset;

  if ((((*(unsigned int *)(block + 4) & 0xfffffffc) == 0x41626c68) &&
       (block_size = *(int *)(block + 8), block_size >= 0)) &&
      (cache_size = *(unsigned int *)(cache + 0x20),
       block_size < (int)cache_size)) {
    block_offset = block - *(int *)(cache + 0x24);
    if ((block_offset >= 0) &&
        (block_size + block_offset <= (int)cache_size)) {
      if (*(int *)(block + 0xc) == 0) {
        next_offset = 0;
      }
      else {
        next_offset = *(int *)(block + 0xc) - *(int *)(cache + 0x24);
        if (next_offset < 0) goto corrupt;
      }
      if (next_offset + 0x10U <= cache_size) {
        return;
      }
    }
  }
corrupt:
  display_assert(
    csprintf(error_string_buffer,
             "lra cache %s @%p block @%p appears to be corrupt",
             (char *)cache, (void *)cache, (void *)block),
    "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x18e, 1);
  system_exit(-1);
}

/* lra_cache_validate — validate cache struct integrity (0x11c290).
 * Register arg: @EAX = cache. */
void FUN_0011c290(int cache)
{
  if (cache == 0) {
    display_assert("cache",
                   "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x198, 1);
    system_exit(-1);
  }
  if (((*(int *)(cache + 0x38) != 0x6c726163) ||
       (*(int *)(cache + 0x24) == 0)) ||
      (*(int *)(cache + 0x20) < 0)) {
    display_assert(
      csprintf(error_string_buffer,
               "lra cache %s @%p appears to be corrupt",
               (char *)cache, (void *)cache),
      "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x1a2, 1);
    system_exit(-1);
  }
  if (*(int *)(cache + 0x2c) != 0) {
    FUN_0011c210(cache, *(int *)(cache + 0x2c));
  }
}

/* lra_cache_new — allocate and initialize a cache (0x11c310).
 * Source: lra_cache.c lines 0x56-0x7e. */
int FUN_0011c310(const char *name, int size, void (*lock_proc)(void *, int),
                 void (*unlock_proc)(void *), void *base_address)
{
  int cache;
  char owns_buffer;

  cache = (int)debug_malloc(0x3c, 0,
    "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x56);
  if (size < 0) {
    display_assert("size>=0",
                   "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x58, 1);
    system_exit(-1);
  }
  if (lock_proc == NULL || unlock_proc == NULL) {
    lock_proc = (void (*)(void *, int))FUN_0011c1d0;
    unlock_proc = (void (*)(void *))FUN_0011c1e0;
  }
  if (cache != 0) {
    owns_buffer = 0;
    if (base_address == NULL) {
      base_address = debug_malloc(size, 0,
        "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x66);
      owns_buffer = 1;
      if (base_address == NULL) {
        debug_free((void *)cache,
                   "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x7e);
        return 0;
      }
    }
    if (((unsigned int)base_address & 3) != 0) {
      display_assert("!((long)base_address&3)",
                     "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x6b, 1);
      system_exit(-1);
    }
    csmemset((void *)cache, 0, 0x3c);
    csstrncpy((char *)cache, name, 0x1f);
    *(char *)(cache + 0x1f) = 0;
    *(int *)(cache + 0x20) = size;
    *(void **)(cache + 0x24) = base_address;
    *(int *)(cache + 0x2c) = 0;
    *(int *)(cache + 0x38) = 0x6c726163;
    *(char *)(cache + 0x28) = owns_buffer;
    *(void (**)(void *, int))(cache + 0x30) = lock_proc;
    *(void (**)(void *))(cache + 0x34) = unlock_proc;
    FUN_0011c290(cache);
  }
  return cache;
}

/* lra_cache_dispose — free a cache and its buffer (0x11c430).
 * Source: lra_cache.c lines 0x8c-0x8d. */
void FUN_0011c430(int cache)
{
  FUN_0011c290(cache);
  if (*(char *)(cache + 0x28) != '\0') {
    debug_free(*(void **)(cache + 0x24),
               "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x8c);
  }
  debug_free((void *)cache,
             "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x8d);
}

/* lra_cache_flush — unlock all blocks and clear the list (0x11c480).
 * Source: lra_cache.c. */
void FUN_0011c480(int cache)
{
  int *block;

  FUN_0011c290(cache);
  if (*(int *)(cache + 0x2c) != 0 &&
      (block = *(int **)(cache + 0x24), block != NULL)) {
    do {
      if ((*(unsigned char *)(block + 1) & 2) == 0) {
        (*(void (**)(int))(cache + 0x34))(*block);
        block[1] = (block[1] & ~1) | 2;
      }
      block = (int *)block[3];
    } while (block != NULL);
    *(int *)(cache + 0x2c) = 0;
    return;
  }
  *(int *)(cache + 0x2c) = 0;
}

/* lra_cache_unlock_block — release a specific block (0x11c4d0).
 * Source: lra_cache.c line 0x11a. */
void FUN_0011c4d0(int cache, void *pointer)
{
  int block_header;

  if (pointer == NULL) {
    display_assert("pointer",
                   "c:\\halo\\SOURCE\\memory\\lra_cache.c", 0x11a, 1);
    system_exit(-1);
  }
  block_header = (int)pointer - 0x10;
  FUN_0011c290(cache);
  FUN_0011c210(cache, block_header);
  if ((*(unsigned char *)(block_header + 4) & 2) == 0) {
    (*(void (**)(int))(cache + 0x34))(*(int *)block_header);
    *(unsigned int *)(block_header + 4) =
      (*(unsigned int *)(block_header + 4) & ~1U) | 2;
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
    void *msg = (void *)create_message(3, (int)encoded_buf, encoded_size,
                                       (int)s_network_game_message_buffer, 0x604);
    if (msg == NULL) {
      network_game_log("create_message() failed");
    }
    return msg;
  }
}
