/* ========================================================================
 * message_header.c — Message header, encryption, key agreement, prime sieve
 * Original source: c:\halo\SOURCE\bungie_net\common\message_header.c
 *                  c:\halo\SOURCE\bungie_net\common\message_encryption.c
 *                  c:\halo\SOURCE\bungie_net\common\key_agreement.c
 *                  c:\halo\SOURCE\bungie_net\common\prime_numbers.c
 * ======================================================================== */
#include "../../common.h"

/* key_agreement_peek_packet_type (0x80530) — XBE naked draft (batch 77). */
#if defined(__clang__)
static void (*const b80530_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80530_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int key_agreement_peek_packet_type(unsigned char *msgptr __attribute__((unused)), unsigned short msg_size __attribute__((unused)), unsigned char *packet_type __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "je .Lkey_agreement_peek_packet_type_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lkey_agreement_peek_packet_type_2\n\t"
      ".Lkey_agreement_peek_packet_type_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xc4\n\t"
      "pushl $0x265b5c\n\t"
      "pushl $0x265ba8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lkey_agreement_peek_packet_type_2:\n\t"
      "movzwl 0xc(%%ebp), %%ecx\n\t"
      "movb -0x1(%%ecx,%%esi,1), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb (%%esi), %%al\n\t"
      "movb %%cl, (%%edi)\n\t"
      "andl $3, %%eax\n\t"
      "testb $2, %%al\n\t"
      "je .Lkey_agreement_peek_packet_type_4\n\t"
      "movb (%%esi), %%dl\n\t"
      "shrb $2, %%dl\n\t"
      "andb $3, %%dl\n\t"
      "cmpb $3, %%dl\n\t"
      "jne .Lkey_agreement_peek_packet_type_4\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lkey_agreement_peek_packet_type_3\n\t"
      "cmpb $1, %%cl\n\t"
      "jne .Lkey_agreement_peek_packet_type_4\n\t"
      ".Lkey_agreement_peek_packet_type_3:\n\t"
      "popl %%edi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lkey_agreement_peek_packet_type_4:\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80530_assert), [exitfn] "m"(b80530_exitfn)
      : "memory");
}
#else
#error "key_agreement_peek_packet_type: clang naked draft required"
#endif


/* key_message_xor_keystream (0x807d0) — XBE naked draft (batch 77). */
#if defined(__clang__)


__attribute__((naked, noinline))
void key_message_xor_keystream(int msg __attribute__((unused)), int len __attribute__((unused)), int keystream __attribute__((unused)), int key_len __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edx, %%edx\n\t"
      "pushl %%esi\n\t"
      "movl $1, %%esi\n\t"
      "jle .Lkey_message_xor_keystream_4\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lkey_message_xor_keystream_1:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movb (%%eax,%%ebx,1), %%bl\n\t"
      "xorb (%%ecx,%%edi,1), %%bl\n\t"
      "addl %%esi, %%eax\n\t"
      "notb %%bl\n\t"
      "movb %%bl, (%%ecx,%%edi,1)\n\t"
      "incl %%ecx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .Lkey_message_xor_keystream_2\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lkey_message_xor_keystream_3\n\t"
      ".Lkey_message_xor_keystream_2:\n\t"
      "negl %%esi\n\t"
      "addl %%esi, %%eax\n\t"
      ".Lkey_message_xor_keystream_3:\n\t"
      "cmpl 0xc(%%ebp), %%ecx\n\t"
      "jl .Lkey_message_xor_keystream_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lkey_message_xor_keystream_4:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "key_message_xor_keystream: clang naked draft required"
#endif


/* tea_encrypt (0x80820) — XBE naked draft (batch 77). */
#if defined(__clang__)


__attribute__((naked, noinline))
void tea_encrypt(unsigned int *v __attribute__((unused)), unsigned int *w __attribute__((unused)), int *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl (%%esi), %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl $0x20, 0x8(%%ebp)\n\t"
      ".Ltea_encrypt_1:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $5, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "movl %%ecx, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%ebx, %%edi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "xorl %%edi, %%esi\n\t"
      "subl $0x61c88647, %%edx\n\t"
      "leal (%%edx,%%ecx,1), %%edi\n\t"
      "xorl %%edi, %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "shrl $5, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%ebx, %%edi\n\t"
      "xorl %%edi, %%esi\n\t"
      "leal (%%edx,%%eax,1), %%edi\n\t"
      "xorl %%edi, %%esi\n\t"
      "addl %%esi, %%ecx\n\t"
      "decl 0x8(%%ebp)\n\t"
      "jne .Ltea_encrypt_1\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "tea_encrypt: clang naked draft required"
#endif


/* tea_decrypt (0x808b0) — XBE naked draft (batch 77). */
#if defined(__clang__)


__attribute__((naked, noinline))
void tea_decrypt(unsigned int *v __attribute__((unused)), unsigned int *w __attribute__((unused)), int *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl (%%esi), %%edi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "movl $0xc6ef3720, %%edx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "movl $0x20, 0x8(%%ebp)\n\t"
      ".Ltea_decrypt_1:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $5, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "movl %%ecx, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%ebx, %%edi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "xorl %%edi, %%esi\n\t"
      "leal (%%edx,%%ecx,1), %%edi\n\t"
      "xorl %%edi, %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "shrl $5, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%ebx, %%edi\n\t"
      "xorl %%edi, %%esi\n\t"
      "leal (%%edx,%%eax,1), %%edi\n\t"
      "xorl %%edi, %%esi\n\t"
      "subl %%esi, %%ecx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0x61c88647, %%edx\n\t"
      "decl %%esi\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "jne .Ltea_decrypt_1\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "tea_decrypt: clang naked draft required"
#endif


/* build_message_header (0x80b40) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void (*const b80b40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80b40_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void build_message_header(unsigned short *header __attribute__((unused)), unsigned short length __attribute__((unused)), unsigned char type __attribute__((unused)), unsigned char flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lbuild_message_header_1\n\t"
      "pushl $1\n\t"
      "pushl $0x43\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265cc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbuild_message_header_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpw $0xfff, %%di\n\t"
      "jbe .Lbuild_message_header_2\n\t"
      "pushl $1\n\t"
      "pushl $0x45\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265c94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbuild_message_header_2:\n\t"
      "movb 0x10(%%ebp), %%bl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb (%%esi), %%al\n\t"
      "shll $4, %%edi\n\t"
      "andl $0xf, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "testb %%bl, %%bl\n\t"
      "movw %%ax, (%%esi)\n\t"
      "jbe .Lbuild_message_header_3\n\t"
      "cmpb $4, %%bl\n\t"
      "jb .Lbuild_message_header_4\n\t"
      ".Lbuild_message_header_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x46\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265c64\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbuild_message_header_4:\n\t"
      "andb $3, %%bl\n\t"
      "movzbw %%bl, %%cx\n\t"
      "movb 0x14(%%ebp), %%bl\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%esi), %%dx\n\t"
      "shll $2, %%ecx\n\t"
      "andl $0xfff3, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "cmpb $3, %%bl\n\t"
      "movw %%cx, (%%esi)\n\t"
      "jbe .Lbuild_message_header_5\n\t"
      "pushl $1\n\t"
      "pushl $0x47\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265bec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbuild_message_header_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "movzbw %%bl, %%cx\n\t"
      "popl %%edi\n\t"
      "andl $0xfffc, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80b40_assert), [exitfn] "m"(b80b40_exitfn)
      : "memory");
}
#else
#error "build_message_header: clang naked draft required"
#endif


/* byte_swap_message_header (0x80c20) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void (*const b80c20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80c20_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void byte_swap_message_header(unsigned short *header __attribute__((unused)), int byte_order __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lbyte_swap_message_header_1\n\t"
      "pushl $1\n\t"
      "pushl $0x50\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265d1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbyte_swap_message_header_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "jne .Lbyte_swap_message_header_2\n\t"
      "movw (%%esi), %%ax\n\t"
      "movzbw %%ah, %%cx\n\t"
      "movb %%al, %%ch\n\t"
      "movw %%cx, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbyte_swap_message_header_2:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lbyte_swap_message_header_3\n\t"
      "movw (%%esi), %%ax\n\t"
      "movzbw %%ah, %%dx\n\t"
      "movb %%al, %%dh\n\t"
      "movw %%dx, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbyte_swap_message_header_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x5e\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265d00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80c20_assert), [exitfn] "m"(b80c20_exitfn)
      : "memory");
}
#else
#error "byte_swap_message_header: clang naked draft required"
#endif


/* create_message (0x80ca0) — XBE naked draft (batch 77). */
#if defined(__clang__)
static void (*const b80ca0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80ca0_exitfn)(int) = system_exit;
static void * (*const b80ca0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b80ca0_c80b40)(unsigned short *header, unsigned short length, unsigned char type, unsigned char flags) = build_message_header;
static void * (*const b80ca0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
int create_message(int type __attribute__((unused)), int payload __attribute__((unused)), unsigned int payload_len __attribute__((unused)), int buffer __attribute__((unused)), unsigned short buffer_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x2(%%ebx), %%edi\n\t"
      "je .Lcreate_message_1\n\t"
      "movzwl 0x18(%%ebp), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .Lcreate_message_2\n\t"
      "pushl $1\n\t"
      "pushl $0x29\n\t"
      "pushl $0x265ccc\n\t"
      "pushl $0x265d24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lcreate_message_2\n\t"
      ".Lcreate_message_1:\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x265ccc\n\t"
      "movswl %%di, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lcreate_message_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lcreate_message_3\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c80b40]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lcreate_message_3\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x2(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lcreate_message_3:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80ca0_assert), [exitfn] "m"(b80ca0_exitfn), [c8ee60] "m"(b80ca0_c8ee60), [c80b40] "m"(b80ca0_c80b40), [c8e0b0] "m"(b80ca0_c8e0b0)
      : "memory");
}
#else
#error "create_message: clang naked draft required"
#endif


/* prime_compare (0x80d30) — XBE naked draft (batch 78). */
#if defined(__clang__)


__attribute__((naked, noinline))
int prime_compare(unsigned int *a __attribute__((unused)), unsigned int *b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jbe .Lprime_compare_1\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprime_compare_1:\n\t"
      "sbbl %%eax, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "prime_compare: clang naked draft required"
#endif


/* Global: pointer to key_agreement_packets group definition at 0x2ee588. */
#define key_agreement_group ((void *)0x2ee588)

/* key_agreement_build_message (0x803d0) — XBE naked draft (batch 77). */
#if defined(__clang__)
static bool (*const b803d0_c11aca0)(group_definition *group, void *data, char *encoded_buf, int32_t *encoded_size, int16_t type, int one) = encode_packet_group;
static int (*const b803d0_c80ca0)(int type, int payload, unsigned int payload_len, int buffer, unsigned short buffer_size) = create_message;

__attribute__((naked, noinline))
unsigned short * key_agreement_build_message(short type __attribute__((unused)), void *data __attribute__((unused)), int buffer __attribute__((unused)), unsigned short buffer_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x84(%%ebp)\n\t"
      "movl $0x1f, %%ecx\n\t"
      "leal -0x83(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      "pushl $1\n\t"
      "stosb\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2ee588\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x80, -0x4(%%ebp)\n\t"
      "call *%[c11aca0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lkey_agreement_build_message_1\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "call *%[c80ca0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lkey_agreement_build_message_2\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%eax), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "andl $0xfffe, %%edx\n\t"
      "orl $2, %%edx\n\t"
      "movw %%dx, (%%eax)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lkey_agreement_build_message_1:\n\t"
      "movl %%esi, %%eax\n\t"
      ".Lkey_agreement_build_message_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11aca0] "m"(b803d0_c11aca0), [c80ca0] "m"(b803d0_c80ca0)
      : "memory");
}
#else
#error "key_agreement_build_message: clang naked draft required"
#endif


/* message_encrypt (0x80940) — XBE naked draft (batch 77). */
#if defined(__clang__)
static void (*const b80940_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80940_exitfn)(int) = system_exit;
static void (*const b80940_c80820)(unsigned int *v, unsigned int *w, int *key) = tea_encrypt;
static void (*const b80940_c807d0)(int msg, int len, int keystream, int key_len) = key_message_xor_keystream;

__attribute__((naked, noinline))
void message_encrypt(unsigned short *msgptr __attribute__((unused)), unsigned int *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Lmessage_encrypt_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lmessage_encrypt_2\n\t"
      ".Lmessage_encrypt_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x1f\n\t"
      "pushl $0x265c2c\n\t"
      "pushl $0x265c1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmessage_encrypt_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb %%al, %%bl\n\t"
      "shrw $4, %%ax\n\t"
      "andl $3, %%ebx\n\t"
      "testb $1, %%bl\n\t"
      "jne .Lmessage_encrypt_7\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "subb $2, %%al\n\t"
      "subl $2, %%ecx\n\t"
      "shrl $3, %%ecx\n\t"
      "addl $2, %%esi\n\t"
      "andl $7, %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .Lmessage_encrypt_4\n\t"
      "movzwl %%cx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "nop\n\t"
      ".Lmessage_encrypt_3:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c80820]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $8, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lmessage_encrypt_3\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".Lmessage_encrypt_4:\n\t"
      "testw %%dx, %%dx\n\t"
      "je .Lmessage_encrypt_5\n\t"
      "pushl $8\n\t"
      "movswl %%dx, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c807d0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lmessage_encrypt_5:\n\t"
      "orl $1, %%ebx\n\t"
      "cmpw $3, %%bx\n\t"
      "jbe .Lmessage_encrypt_6\n\t"
      "pushl $1\n\t"
      "pushl $0x4c\n\t"
      "pushl $0x265c2c\n\t"
      "pushl $0x265bec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmessage_encrypt_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "andl $0xfffc, %%ecx\n\t"
      "orl %%ebx, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      ".Lmessage_encrypt_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80940_assert), [exitfn] "m"(b80940_exitfn), [c80820] "m"(b80940_c80820), [c807d0] "m"(b80940_c807d0)
      : "memory");
}
#else
#error "message_encrypt: clang naked draft required"
#endif


/* message_decrypt (0x80a40) — XBE naked draft (batch 77). */
#if defined(__clang__)
static void (*const b80a40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b80a40_exitfn)(int) = system_exit;
static void (*const b80a40_c808b0)(unsigned int *v, unsigned int *w, int *key) = tea_decrypt;
static void (*const b80a40_c807d0)(int msg, int len, int keystream, int key_len) = key_message_xor_keystream;

__attribute__((naked, noinline))
void message_decrypt(unsigned short *msgptr __attribute__((unused)), unsigned int *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Lmessage_decrypt_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lmessage_decrypt_2\n\t"
      ".Lmessage_decrypt_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x58\n\t"
      "pushl $0x265c2c\n\t"
      "pushl $0x265c1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmessage_decrypt_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb %%al, %%bl\n\t"
      "shrw $4, %%ax\n\t"
      "andl $3, %%ebx\n\t"
      "testb $1, %%bl\n\t"
      "je .Lmessage_decrypt_7\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "subb $2, %%al\n\t"
      "subl $2, %%ecx\n\t"
      "shrl $3, %%ecx\n\t"
      "addl $2, %%esi\n\t"
      "andl $7, %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .Lmessage_decrypt_4\n\t"
      "movzwl %%cx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "nop\n\t"
      ".Lmessage_decrypt_3:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c808b0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $8, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lmessage_decrypt_3\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".Lmessage_decrypt_4:\n\t"
      "testw %%dx, %%dx\n\t"
      "je .Lmessage_decrypt_5\n\t"
      "pushl $8\n\t"
      "movswl %%dx, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c807d0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lmessage_decrypt_5:\n\t"
      "andl $0xfffe, %%ebx\n\t"
      "cmpw $3, %%bx\n\t"
      "jbe .Lmessage_decrypt_6\n\t"
      "pushl $1\n\t"
      "pushl $0x83\n\t"
      "pushl $0x265c2c\n\t"
      "pushl $0x265bec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmessage_decrypt_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "andl $0xfffc, %%ecx\n\t"
      "orl %%ebx, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      ".Lmessage_decrypt_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b80a40_assert), [exitfn] "m"(b80a40_exitfn), [c808b0] "m"(b80a40_c808b0), [c807d0] "m"(b80a40_c807d0)
      : "memory");
}
#else
#error "message_decrypt: clang naked draft required"
#endif


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

/* 0x80210 */
void FUN_00080210(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp edi, ebx -> jne 0x80246 */
  display_assert((char *)0x00265a90, (char *)0x00265a54, 124, 0);
  system_exit(0);
  /* cmp eax, 4 -> jb 0x80250 */
  /* cmp ecx, 8 -> jb 0x80280 */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 79, 0);
  system_exit(0);
  FUN_0007ffe0();
  FUN_0007ff40();
  /* test eax, eax -> je 0x80311 */
  /* test eax, eax -> je 0x80320 */
  /* cmp (char)eax, 3 -> je 0x8036a */
  display_assert((char *)0x00265b18, (char *)0x00265b5c, 77, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x80380 */
void FUN_00080380(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)edx, (char *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x803b0 */
void FUN_000803b0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  encode_packet_group((void *)0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x80470 */
void FUN_00080470(void)
{
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> je 0x80482 */
  /* test ebx, ebx -> je 0x80482 */
  /* test edi, edi -> jne 0x804a2 */
  display_assert((char *)0x00265b90, (char *)0x00265b5c, 162, 0);
  system_exit(0);
  key_agreement_build_message(0, (void *)(uintptr_t)edx, 0, 0);

  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x804e0 */
void FUN_000804e0(void)
{
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x8050a */
  display_assert((char *)0x00265ba4, (char *)0x00265b5c, 179, 0);
  system_exit(0);
  key_agreement_build_message(0, (void *)(uintptr_t)ecx, 0, 0);

  (void)ecx;
  (void)esi;
}

/* 0x805a0 */
void FUN_000805a0(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_00081170();
  FUN_00081250();
  FUN_00080470();
  /* test esi, esi -> je 0x8060c */
  byte_swap_message_header((void *)0, 0);
  send_endpoint((void *)(uintptr_t)edx, (char *)(uintptr_t)esi, 0);
  /* cmp eax, edi -> je 0x80615 */

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x80620 */
void FUN_00080620(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0x8064c */
  /* test ebx, ebx -> je 0x8064c */
  /* test eax, eax -> jne 0x8066c */
  display_assert((char *)0x00265bc0, (char *)0x00265b5c, 261, 0);
  system_exit(0);
  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)esi, (void *)0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x807ad */
  FUN_00081300();
  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)esi, (void *)0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x807ad */
  FUN_00081410();
  FUN_00081410();
  FUN_00081250();
  FUN_000804e0();
  /* test esi, esi -> je 0x807ad */
  byte_swap_message_header((void *)0, 0);
  send_endpoint((void *)(uintptr_t)ecx, (char *)(uintptr_t)esi, 0);
  /* cmp eax, edi -> jne 0x807ad */
  FUN_00081300();
  verify_packet_group_definitions((void *)0x002ee588);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x80eb0 */
void FUN_00080eb0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  sieve_of_eratosthenes(ecx, (void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x80eef */
  FUN_00081410();
  debug_free((void *)(uintptr_t)esi, (char *)0x00265d54, 137);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x80f00 */
void FUN_00080f00(void)
{
  int eax = 0;
  int esi = 0;

  display_assert((char *)0x0025f120, (char *)0x00265d54, 150, 0);
  system_exit(0);
  sieve_of_eratosthenes(65535, (void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x80f8a */
  FUN_00081410();
  debug_free((void *)(uintptr_t)esi, (char *)0x00265d54, 137);
  FUN_000800d0();
  FUN_0007ff40();

  (void)eax;
  (void)esi;
}

/* 0x80fc0 */
void FUN_00080fc0(void)
{
  int eax = 0;
  int ebx = 0;

  /* test (char)ebx, 1 -> je 0x81020 */
  FUN_000800d0();
  FUN_00080210();
  FUN_000800d0();
  FUN_00080210();
  /* test ebx, ebx -> jne 0x80ff4 */
  /* test eax, eax -> ja 0x8105c */
  /* cmp eax, -1 -> jbe 0x8107c */
  display_assert((char *)0x00265d88, (char *)0x00265da0, 95, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
}

/* 0x81090 */
void FUN_00081090(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, 2 -> ja 0x810b2 */
  display_assert((char *)0x00265de0, (char *)0x00265da0, 112, 0);
  system_exit(0);
  /* cmp ebx, eax -> jb 0x810d6 */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 113, 0);
  system_exit(0);
  /* cmp edi, esi -> jb 0x810f7 */
  display_assert((char *)0x00265dd4, (char *)0x00265da0, 114, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x81110 */
void FUN_00081110(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, 2 -> ja 0x81138 */
  display_assert((char *)0x00265de0, (char *)0x00265da0, 133, 0);
  system_exit(0);
  /* cmp edi, eax -> jb 0x8115f */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 134, 0);
  system_exit(0);
  FUN_00080eb0();
  FUN_00080eb0();
  FUN_00081410();
  FUN_00081410();
  /* cmp eax, ecx -> jb 0x8120c */
  display_assert((char *)0x00265e08, (char *)0x00265da0, 162, 0);
  system_exit(0);
  /* cmp eax, edx -> jb 0x81236 */
  display_assert((char *)0x00265de4, (char *)0x00265da0, 163, 0);
  system_exit(0);
  FUN_00081090();
  error(0, (char *)0x00265e2c);
  display_assert((char *)0x00265de0, (char *)0x00265da0, 133, 0);
  system_exit(0);
  /* cmp ebx, ecx -> jb 0x8138a */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 134, 0);
  system_exit(0);
  FUN_00080fc0();
  error(0, (char *)0x00265e68);
  /* test (char)eax, (char)eax -> jne 0x81434 */
  crt_time((void *)0);
  FUN_001d9cf9();
  rand();
  FUN_001d9068();
  /* test ebx, ebx -> je 0x8149e */
  /* test edi, edi -> jne 0x814bb */
  display_assert((char *)0x00265ef0, (char *)0x00265f08, 46, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x814db */
  crt_time((void *)0);
  FUN_001d9cf9();
  rand();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
