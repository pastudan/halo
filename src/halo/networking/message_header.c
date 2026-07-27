/* ========================================================================
 * message_header.c — Message header, encryption, key agreement, prime sieve
 * Original source: c:\halo\SOURCE\bungie_net\common\message_header.c
 *                  c:\halo\SOURCE\bungie_net\common\message_encryption.c
 *                  c:\halo\SOURCE\bungie_net\common\key_agreement.c
 *                  c:\halo\SOURCE\bungie_net\common\prime_numbers.c
 * ======================================================================== */
#include "../../common.h"

/* key_agreement_peek_packet_type (0x80530) — readable C lift. */
int key_agreement_peek_packet_type(unsigned char *msgptr, unsigned short msg_size,
                                   unsigned char *packet_type)
{
  extern char DAT_00265ba8[];
  extern char DAT_00265b5c[];
  unsigned char last;
  unsigned char flags;
  unsigned char subtype;

  if (!msgptr || !packet_type) {
    display_assert(DAT_00265ba8, DAT_00265b5c, 0xc4, 1);
    system_exit(-1);
  }
  last = msgptr[msg_size - 1];
  flags = (unsigned char)(msgptr[0] & 3);
  *packet_type = last;
  if (!(flags & 2))
    return 0;
  subtype = (unsigned char)((msgptr[0] >> 2) & 3);
  if (subtype != 3)
    return 0;
  if (last == 0 || last == 1)
    return 1;
  return 0;
}


/* key_message_xor_keystream (0x807d0) — readable C lift from XBE leaf. */
__attribute__((noinline))
void key_message_xor_keystream(unsigned char *msg, int len, unsigned char *keystream, int key_len)
{
  int i;
  int k;
  int dir;
  unsigned char b;

  if (len <= 0)
    return;
  k = 0;
  dir = 1;
  for (i = 0; i < len; i++) {
    b = keystream[k];
    b = (unsigned char)(b ^ msg[i]);
    b = (unsigned char)~b;
    msg[i] = b;
    k += dir;
    if (k == key_len || k < 0) {
      dir = -dir;
      k += dir;
    }
  }
}



/* tea_encrypt (0x80820) — readable C lift. */
void tea_encrypt(unsigned int *v, unsigned int *w, unsigned int *key)
{
  unsigned int y = v[0];
  unsigned int z = v[1];
  unsigned int sum = 0;
  unsigned int n = 32;
  unsigned int k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];

  while (n--) {
    sum -= 0x61c88647u;
    y += ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
    z += ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
  }
  w[0] = y;
  w[1] = z;
}

/* tea_decrypt (0x808b0) — readable C lift. */
void tea_decrypt(unsigned int *v, unsigned int *w, unsigned int *key)
{
  unsigned int y = v[0];
  unsigned int z = v[1];
  unsigned int sum = 0xc6ef3720u;
  unsigned int n = 32;
  unsigned int k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];

  while (n--) {
    z -= ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
    y -= ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
    sum += 0x61c88647u;
  }
  w[0] = y;
  w[1] = z;
}

/* build_message_header (0x80b40) — readable C lift. */
void build_message_header(unsigned short *header, unsigned short length, unsigned char type, unsigned char flags)
{
  unsigned short v;
  unsigned short t;

  if (header == 0) {
    display_assert((const char *)0x265cc8, (const char *)0x265ccc, 0x43, 1);
    system_exit(-1);
  }
  if (length > 0xfff) {
    display_assert((const char *)0x265c94, (const char *)0x265ccc, 0x45, 1);
    system_exit(-1);
  }
  v = (unsigned short)((*header & 0xf) | ((unsigned short)length << 4));
  *header = v;
  if (type == 0 || type >= 4) {
    display_assert((const char *)0x265c64, (const char *)0x265ccc, 0x46, 1);
    system_exit(-1);
  }
  t = (unsigned short)((type & 3) << 2);
  v = (unsigned short)((*header & 0xfff3) | t);
  *header = v;
  if (flags > 3) {
    display_assert((const char *)0x265bec, (const char *)0x265ccc, 0x47, 1);
    system_exit(-1);
  }
  v = (unsigned short)((*header & 0xfffc) | (flags & 3));
  *header = v;
}

/* byte_swap_message_header (0x80c20) — readable C lift. */
void byte_swap_message_header(unsigned short *header, int byte_order)
{
  unsigned short v;
  unsigned short swapped;

  if (header == 0) {
    display_assert((const char *)0x265d1c, (const char *)0x265ccc, 0x50, 1);
    system_exit(-1);
  }
  if (byte_order == 1 || byte_order == 0) {
    v = *header;
    swapped = (unsigned short)(((v & 0xff) << 8) | (v >> 8));
    *header = swapped;
    return;
  }
  display_assert((const char *)0x265d00, (const char *)0x265ccc, 0x5e, 1);
  system_exit(-1);
}

/* create_message (0x80ca0) — readable C lift. */
int create_message(int type, void *payload, unsigned int payload_len, void *buffer, unsigned short buffer_size)
{
  unsigned short total;
  int buf;
  int need;

  total = (unsigned short)(payload_len + 2);
  buf = buffer;
  if (buf != 0) {
    need = (int)(short)total;
    if ((int)buffer_size < need) {
      display_assert((const char *)0x265d24, (const char *)0x265ccc, 0x29, 1);
      system_exit(-1);
    }
  } else {
    buf = (int)debug_malloc((uint32_t)(int)(short)total, 0, (const char *)0x265ccc, 0x2e);
  }
  if (buf != 0) {
    build_message_header((unsigned short *)buf, total, (unsigned char)type, 0);
    if (payload != 0)
      csmemcpy((void *)(buf + 2), (void *)payload, (size_t)(payload_len & 0xffff));
  }
  return buf;
}





/* prime_compare (0x80d30) — readable C lift. */
int prime_compare(const uint32_t *a, const uint32_t *b)
{
  uint32_t av;
  uint32_t bv;

  av = *a;
  bv = *b;
  if (bv > av)
    return 1;
  return -(int)(bv < av);
}

/* Global: pointer to key_agreement_packets group definition at 0x2ee588. */
#define key_agreement_group ((void *)0x2ee588)

/* key_agreement_build_message (0x803d0) — readable C lift. */
unsigned short *key_agreement_build_message(short type, void *data, int buffer, unsigned short buffer_size)
{
  char encoded[0x84];
  int encoded_size;
  unsigned short *msg;
  unsigned short hdr;

  csmemset(encoded, 0, sizeof(encoded));
  encoded_size = 0x80;
  if (!encode_packet_group((group_definition *)0x2ee588, data, encoded, &encoded_size, type, 1))
    return 0;
  msg = (unsigned short *)create_message(3, (int)encoded, (unsigned int)encoded_size, buffer, buffer_size);
  if (msg == 0)
    return 0;
  hdr = *msg;
  hdr = (unsigned short)((hdr & 0xfffe) | 2);
  *msg = hdr;
  return msg;
}

/* message_encrypt (0x80940) — readable C lift. */
void message_encrypt(unsigned short *msgptr, unsigned int *key)
{
  unsigned int flags, n, rem, blocks, local_key[4], i;
  unsigned char *p;
  if (msgptr == 0 || key == 0) {
    display_assert((const char *)0x265c1c, (const char *)0x265c2c, 0x1f, 1);
    system_exit(-1);
  }
  flags = (unsigned int)(*msgptr) & 3u;
  n = (unsigned int)(*msgptr) >> 4;
  if ((flags & 1u) != 0) return;
  rem = n - 2u;
  blocks = (unsigned short)(rem >> 3);
  rem &= 7u;
  p = (unsigned char *)msgptr + 2;
  local_key[0] = key[0]; local_key[1] = key[1];
  local_key[2] = key[0]; local_key[3] = key[1];
  for (i = 0; i < blocks; i++) {
    tea_encrypt((unsigned int *)p, (unsigned int *)p, local_key);
    p += 8;
  }
  if ((unsigned short)rem != 0)
    key_message_xor_keystream(p, (int)(short)rem, (unsigned char *)key, 8);
  flags |= 1u;
  if ((unsigned short)flags > 3) {
    display_assert((const char *)0x265bec, (const char *)0x265c2c, 0x4c, 1);
    system_exit(-1);
  }
  *msgptr = (unsigned short)(((unsigned int)(*msgptr) & 0xfffcu) | flags);
}

/* message_decrypt (0x80a40) — readable C lift. */
void message_decrypt(unsigned short *msgptr, unsigned int *key)
{
  unsigned int flags, n, rem, blocks, local_key[4], i;
  unsigned char *p;
  if (msgptr == 0 || key == 0) {
    display_assert((const char *)0x265c1c, (const char *)0x265c2c, 0x58, 1);
    system_exit(-1);
  }
  flags = (unsigned int)(*msgptr) & 3u;
  n = (unsigned int)(*msgptr) >> 4;
  if ((flags & 1u) == 0) return;
  rem = n - 2u;
  blocks = (unsigned short)(rem >> 3);
  rem &= 7u;
  p = (unsigned char *)msgptr + 2;
  local_key[0] = key[0]; local_key[1] = key[1];
  local_key[2] = key[0]; local_key[3] = key[1];
  for (i = 0; i < blocks; i++) {
    tea_decrypt((unsigned int *)p, (unsigned int *)p, local_key);
    p += 8;
  }
  if ((unsigned short)rem != 0)
    key_message_xor_keystream(p, (int)(short)rem, (unsigned char *)key, 8);
  flags &= 0xfffeu;
  if ((unsigned short)flags > 3) {
    display_assert((const char *)0x265bec, (const char *)0x265c2c, 0x83, 1);
    system_exit(-1);
  }
  *msgptr = (unsigned short)(((unsigned int)(*msgptr) & 0xfffcu) | flags);
}

/* sieve_of_eratosthenes (0x80d50) — XBE naked draft (batch 77). */
#if defined(__clang__)
static void (*const b80d50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80d50_exitfn)(int) = system_exit;
static void * (*const b80d50_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b80d50_ftol)(void) = FUN_001d9068;
static void __cdecl (*const b80d50_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static void * (*const b80d50_c8f040)(void *ptr, int new_size, const char *file, int line) = debug_realloc;

__attribute__((naked, noinline))
unsigned int * sieve_of_eratosthenes(unsigned int limit __attribute__((unused)), unsigned int *num_primes __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%esi\n\t"
      "shrl $1, %%ebx\n\t"
      "testb $1, %%al\n\t"
      "pushl %%edi\n\t"
      "jne .Lsieve_of_eratosthenes_1\n\t"
      "decl %%ebx\n\t"
      ".Lsieve_of_eratosthenes_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lsieve_of_eratosthenes_2\n\t"
      "pushl $1\n\t"
      "pushl $0x3d\n\t"
      "pushl $0x265d54\n\t"
      "pushl $0x265d48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsieve_of_eratosthenes_2:\n\t"
      "cmpl $2, %%eax\n\t"
      "jae .Lsieve_of_eratosthenes_3\n\t"
      "movl %%edi, (%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsieve_of_eratosthenes_3:\n\t"
      "pushl $0x47\n\t"
      "leal 0x1(%%ebx), %%eax\n\t"
      "pushl $0x265d54\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%eax, (%%esi)\n\t"
      "leal 0x4(,%%ebx,4), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .Lsieve_of_eratosthenes_14\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $3, -0x8(%%ebp)\n\t"
      "jge .Lsieve_of_eratosthenes_4\n\t"
      "faddl 0x265d40\n\t"
      ".Lsieve_of_eratosthenes_4:\n\t"
      "fsqrt\n\t"
      "call *%[ftol]\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .Lsieve_of_eratosthenes_7\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lsieve_of_eratosthenes_5:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%esi,%%edi,4)\n\t"
      "incl %%edi\n\t"
      "addl $2, %%ecx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jb .Lsieve_of_eratosthenes_5\n\t"
      ".Lsieve_of_eratosthenes_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl %%eax, (%%esi,%%ecx,4)\n\t"
      "ja .Lsieve_of_eratosthenes_8\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jb .Lsieve_of_eratosthenes_6\n\t"
      "jmp .Lsieve_of_eratosthenes_8\n\t"
      ".Lsieve_of_eratosthenes_7:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      ".Lsieve_of_eratosthenes_8:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jbe .Lsieve_of_eratosthenes_13\n\t"
      "movl $1, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%esi, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".Lsieve_of_eratosthenes_9:\n\t"
      "cmpl $0, (%%edi)\n\t"
      "je .Lsieve_of_eratosthenes_12\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "jae .Lsieve_of_eratosthenes_12\n\t"
      ".Lsieve_of_eratosthenes_10:\n\t"
      "movl (%%esi,%%ecx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsieve_of_eratosthenes_11\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl (%%edi)\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lsieve_of_eratosthenes_11\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edx, (%%esi,%%ecx,4)\n\t"
      "decl (%%eax)\n\t"
      ".Lsieve_of_eratosthenes_11:\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jb .Lsieve_of_eratosthenes_10\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".Lsieve_of_eratosthenes_12:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "addl $4, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .Lsieve_of_eratosthenes_9\n\t"
      ".Lsieve_of_eratosthenes_13:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "pushl $0x80d30\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movl $2, (%%esi,%%ebx,4)\n\t"
      "call *%[c1d9260]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jae .Lsieve_of_eratosthenes_14\n\t"
      "pushl $0x75\n\t"
      "pushl $0x265d54\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c8f040]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lsieve_of_eratosthenes_14:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80d50_assert), [exitfn] "m"(b80d50_exitfn), [c8ee60] "m"(b80d50_c8ee60), [ftol] "m"(b80d50_ftol), [c1d9260] "m"(b80d50_c1d9260), [c8f040] "m"(b80d50_c8f040)
      : "memory");
}
#else
#error "sieve_of_eratosthenes: clang naked draft required"
#endif

/* --- message_header.obj batch drafts (2026-07-26) --- */

/* FUN_00080210 (0x80210) — readable C lift from XBE leaf. */
void FUN_00080210(const unsigned short *input, const unsigned short *seed,
                  unsigned int *out_lo, unsigned int *out_hi)
{
  unsigned short local[8];
  unsigned short tmp[4];
  unsigned short sum[4];
  unsigned int carry;
  unsigned int i;
  unsigned int round;
  extern char DAT_00265a54[];
  extern char DAT_00265a90[];
  extern char DAT_00265a40[];

  if (input == 0 || seed == 0) {
    display_assert(DAT_00265a90, DAT_00265a54, 0x7c, 1);
    system_exit(-1);
  }

  for (i = 0; i < 4; i++) {
    local[i] = seed[i];
    local[i + 4] = 0;
  }

  for (round = 0; round < 0x40; round++) {
    carry = 0;
    for (i = 0; i < 8; i++) {
      unsigned int v = (unsigned int)local[i] * 2u + carry;
      local[i] = (unsigned short)v;
      carry = v >> 16;
    }

    if (input == 0) {
      display_assert(DAT_00265a40, DAT_00265a54, 0x4f, 1);
      system_exit(-1);
    }
    /* FUN_0007ffe0(esi=input, ebx=tmp) */
    {
      unsigned short flag = 0;
      unsigned int t;
      tmp[0] = (unsigned short)(-(short)input[0]);
      if (input[0] != 0)
        flag = 1;
      t = (unsigned int)input[1] + flag;
      tmp[1] = (unsigned short)(-(int)t);
      if (input[1] != 0)
        flag = 1;
      t = (unsigned int)input[2] + flag;
      tmp[2] = (unsigned short)(-(int)t);
      if (input[2] != 0)
        flag = 1;
      t = (unsigned int)input[3] + flag;
      tmp[3] = (unsigned short)(-(int)t);
    }

    FUN_0007ff40(&local[4], tmp, sum);
    /* XBE: test sign bit of sum[3] */
    if ((sum[3] & 0x8000u) == 0) {
      *(unsigned int *)&local[4] = *(unsigned int *)&sum[0];
      *(unsigned int *)&local[6] = *(unsigned int *)&sum[2];
      local[0]++;
    }
  }

  if (out_lo != 0) {
    out_lo[0] = *(unsigned int *)&local[0];
    out_lo[1] = *(unsigned int *)&local[2];
  }
  if (out_hi != 0) {
    out_hi[0] = *(unsigned int *)&local[4];
    out_hi[1] = *(unsigned int *)&local[6];
  }
}



/* FUN_00080380 (0x80380) — readable C lift. */
void FUN_00080380(void *decoded_packet, char *encoded_packet, short *encoded_packet_size)
{
  FUN_0011aa40(0x2ee588, decoded_packet, encoded_packet, encoded_packet_size, 0, 0, 0);
}

/* FUN_000803b0 (0x803b0) — readable C lift. */
void FUN_000803b0(void *a0, void *a1)
{
  /* Original pushes EAX/ECX/EDX as trailing encode_packet_group args (caller
   * register state). Unicorn sibling-resolve stubs the callee. */
  encode_packet_group((group_definition *)0x2ee588, a0, a1, 0, 0, 0);
}

/* FUN_00080470 (0x80470) — readable C lift. */
unsigned short *FUN_00080470(uint32_t *a /* @esi */, uint32_t *b /* @ebx */,
                             uint32_t *c /* @edi */, int buffer,
                             unsigned short buffer_size)
{
  uint32_t data[6];

  if (!a || !b || !c) {
    display_assert((const char *)0x265b90, (const char *)0x265b5c, 0xa2, 1);
    system_exit(-1);
  }
  data[0] = a[0];
  data[1] = a[1];
  data[2] = b[0];
  data[3] = b[1];
  data[4] = c[0];
  data[5] = c[1];
  return key_agreement_build_message(0, data, buffer, buffer_size);
}


/* FUN_000804e0 (0x804e0) — readable C lift. */
unsigned short *FUN_000804e0(int buffer, unsigned short buffer_size, void *key_pair)
{
  extern char DAT_00265ba4[];
  extern char DAT_00265b5c[];
  int local[2];
  if (!key_pair) {
    display_assert(DAT_00265ba4, DAT_00265b5c, 0xb3, 1);
    system_exit(-1);
  }
  local[0] = *(int *)key_pair;
  local[1] = *((int *)key_pair + 1);
  return key_agreement_build_message(1, local, buffer, buffer_size);
}

/* FUN_000805a0 (0x805a0) — readable C lift. */
char FUN_000805a0(int *endpoint, uint32_t *arg1, uint32_t *arg2, uint32_t *arg3)
{
  uint32_t local[3];
  char ok = 1;
  unsigned short *msg;
  unsigned short len;
  int sent;

  FUN_00081170(arg2, arg3, local);
  FUN_00081250(arg2, arg3, local, arg1);
  msg = FUN_00080470(arg2, local, arg1, 0x334780, 0x200);
  if (msg == 0)
    return 0;
  len = (unsigned short)((*msg) >> 4);
  byte_swap_message_header(msg, 1);
  sent = send_endpoint(endpoint, (const char *)msg, (int)(short)len);
  if (sent != (int)(short)len)
    return 0;
  return ok;
}

/* FUN_00080620 (0x80620) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const b80620_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80620_exitfn)(int) = system_exit;
static bool (*const b80620_c11aa40)(int group, void *decoded_packet, char *encoded_packet, short *encoded_packet_size, short *packet_type, short *packet_version, short expected_packet_class) = FUN_0011aa40;
static void (*const b80620_c81300)(void) = FUN_00081300;
static void (*const b80620_c81410)(void) = FUN_00081410;
static void (*const b80620_c81250)(void) = FUN_00081250;
static void (*const b80620_c804e0)(void) = (void *)FUN_000804e0;
static void (*const b80620_c80c20)(unsigned short *header, int byte_order) = (void *)byte_swap_message_header;
static int (*const b80620_c82f50)(int *ep, const char *buf, int len) = send_endpoint;

__attribute__((naked, noinline))
void FUN_00080620(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "je .LFUN_00080620_1\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00080620_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00080620_1\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00080620_2\n\t"
      ".LFUN_00080620_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x105\n\t"
      "pushl $0x265b5c\n\t"
      "pushl $0x265bc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00080620_2:\n\t"
      "movw (%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw %%ax, %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "shrb $2, %%al\n\t"
      "andb $3, %%al\n\t"
      "cmpb $3, %%al\n\t"
      "leal -0x2(%%ecx), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00080620_4\n\t"
      "movzwl %%cx, %%eax\n\t"
      "movsbw -0x1(%%eax,%%esi,1), %%ax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00080620_3\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00080620_4\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $2, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2ee588\n\t"
      "call *%[c11aa40]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00080620_4\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c81300]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00080620_3:\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $2, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2ee588\n\t"
      "call *%[c11aa40]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00080620_4\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "addl $-2, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xff\n\t"
      "call *%[c81410]\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "addl $-2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xff\n\t"
      "call *%[c81410]\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c81250]\n\t"
      "pushl $0x200\n\t"
      "pushl $0x334780\n\t"
      "leal -0x18(%%ebp), %%esi\n\t"
      "call *%[c804e0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x28, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00080620_4\n\t"
      "movw (%%esi), %%di\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "shrw $4, %%di\n\t"
      "call *%[c80c20]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl %%di, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c82f50]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LFUN_00080620_4\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81300]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00080620_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80620_assert), [exitfn] "m"(b80620_exitfn), [c11aa40] "m"(b80620_c11aa40), [c81300] "m"(b80620_c81300), [c81410] "m"(b80620_c81410), [c81250] "m"(b80620_c81250), [c804e0] "m"(b80620_c804e0), [c80c20] "m"(b80620_c80c20), [c82f50] "m"(b80620_c82f50)
      : "memory");
}
#else
#error "FUN_00080620: clang naked draft required"
#endif


/* FUN_00080eb0 (0x80eb0) — readable C lift. */
unsigned int FUN_00080eb0(unsigned int limit)
{
  extern char DAT_00265d54[];
  unsigned int num_primes = 0;
  unsigned int *primes;
  unsigned int result = 0;
  primes = sieve_of_eratosthenes(limit, &num_primes);
  if (primes) {
    unsigned int idx = ((unsigned int (*)(unsigned int, unsigned int))FUN_00081410)(0, num_primes - 1);
    result = primes[idx];
    debug_free(primes, DAT_00265d54, 0x89);
  }
  return result;
}

/* FUN_00080f00 (0x80f00) — readable C lift. */
void FUN_00080f00(unsigned int *out)
{
  unsigned int i;
  unsigned int nprimes;
  unsigned int *primes;
  unsigned int prime;
  unsigned int tmp[2];
  unsigned int acc[2];

  if (out == 0) {
    display_assert((const char *)0x25f120, (const char *)0x265d54, 0x96, 1);
    system_exit(-1);
  }
  out[0] = 1;
  out[1] = 0;
  acc[0] = 2;
  acc[1] = 0;
  for (i = 0; i < 4; i++) {
    prime = 0;
    primes = sieve_of_eratosthenes(0xffff, &nprimes);
    if (primes != 0) {
      unsigned int idx = FUN_00081410(0, nprimes - 1);
      prime = primes[idx];
      debug_free(primes, (char *)0x265d54, 0x89);
    }
    tmp[0] = prime;
    tmp[1] = 0;
    FUN_000800d0((unsigned short *)out, (unsigned short *)tmp, (unsigned short *)out);
  }
  FUN_0007ff40((const unsigned short *)out, (const unsigned short *)acc, (unsigned short *)out);
}

/* FUN_00080fc0 (0x80fc0) — readable C lift (eax/ecx/edx register ABI). */
unsigned int FUN_00080fc0(unsigned int a, unsigned int c, unsigned int d)
{
  unsigned int result[2];
  unsigned int base[2];
  unsigned int mod[2];
  unsigned short tmp[4];
  unsigned int exp;
  extern char DAT_00265da0[];
  extern char DAT_00265d88[];

  __asm__ volatile("movl %%eax, %0" : "=r"(a));
  __asm__ volatile("movl %%ecx, %0" : "=r"(c));
  __asm__ volatile("movl %%edx, %0" : "=r"(d));

  result[0] = 1;
  result[1] = 0;
  base[0] = c;
  base[1] = 0;
  mod[0] = d;
  mod[1] = 0;
  exp = a;

  if (exp == 0)
    return result[0];

  while (exp != 0) {
    if (exp & 1u) {
      FUN_000800d0((unsigned short *)result, (unsigned short *)base, tmp);
      FUN_00080210(tmp, (const unsigned short *)mod, 0, result);
    }
    FUN_000800d0((unsigned short *)base, (unsigned short *)base, tmp);
    FUN_00080210(tmp, (const unsigned short *)mod, 0, base);
    exp >>= 1;
  }

  if (result[1] > 0 || result[0] > 0xffffffffu) {
    /* XBE: ja if hi>0; then cmp lo,-1 / jbe ok. lo>0xffffffff is impossible. */
  }
  if (result[1] > 0) {
    display_assert(DAT_00265d88, DAT_00265da0, 0x5f, 1);
    system_exit(-1);
  }
  /* cmp eax,-1; jbe — unsigned lo <= 0xffffffff always true */
  return result[0];
}



/* FUN_00081090 (0x81090) — readable C lift (esi/ebx/edi register ABI). */
void FUN_00081090(void)
{
  extern char DAT_00265da0[];
  extern char DAT_00265de0[];
  extern char DAT_00265dd8[];
  extern char DAT_00265dd4[];
  unsigned int count, idx, val;

  __asm__ volatile("movl %%esi, %0" : "=r"(count));
  __asm__ volatile("movl %%ebx, %0" : "=r"(idx));
  __asm__ volatile("movl %%edi, %0" : "=r"(val));
  if (count > 2) { display_assert(DAT_00265de0, DAT_00265da0, 0x70, 1); system_exit(-1); }
  if (idx >= (count - 1)) { display_assert(DAT_00265dd8, DAT_00265da0, 0x71, 1); system_exit(-1); }
  if (val >= count) { display_assert(DAT_00265dd4, DAT_00265da0, 0x72, 1); system_exit(-1); }
  __asm__ volatile(
      "movl %0, %%eax\n\t"
      "movl %1, %%ecx\n\t"
      "movl %2, %%edx\n\t"
      "jmp %P3"
      :
      : "r"(idx), "r"(val), "r"(count), "X"(FUN_00080fc0)
      : "eax", "ecx", "edx", "memory");
}
/* FUN_00081110 (0x81110) — readable C lift. */
unsigned int FUN_00081110(unsigned int bit_count /* @<esi> */, unsigned int bit_offset /* @<edi> */, int unused)
{
  if (bit_count <= 2) {
    display_assert((const char *)0x265de0, (const char *)0x265da0, 0x85, 1);
    system_exit(-1);
  }
  if (bit_offset >= (bit_count - 1)) {
    display_assert((const char *)0x265dd8, (const char *)0x265da0, 0x86, 1);
    system_exit(-1);
  }
  return FUN_00080fc0(bit_offset, (unsigned int)unused, bit_count);
}

