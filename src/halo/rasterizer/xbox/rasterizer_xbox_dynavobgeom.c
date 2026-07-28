#include <stdint.h>
void FUN_0016f910(int16_t profile);
void FUN_0016fa40(int16_t profile);
void FUN_00174ce0(void);
void FUN_00158ae0(int mode);
/*
 * rasterizer_xbox_dynavobgeom.c
 *
 * Dynamic visible-object geometry rasterizer (Xbox D3D8 path).
 * Source path (from binary):
 * c:\halo\SOURCE\rasterizer\xbox\rasterizer_xbox_dynavobgeom.c
 */

/* --- rasterizer_xbox_dynavobgeom.obj batch drafts (2026-07-26) --- */

/* FUN_0015dc10 (0x15dc10) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b15dc10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15dc10_exitfn)(int) = system_exit;
static int (*const b15dc10_c180050)(short param_1) = FUN_00180050;
static void __stdcall (*const b15dc10_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b15dc10_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b15dc10_c1e8920)(void) = (void *)D3DDevice_SetIndices;
static void (*const b15dc10_c1ecf90)(void) = (void *)D3DDevice_DrawIndexedVertices;
static void (*const b15dc10_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0015dc10(void *obj, int *out, int addend)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0015dc10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x337\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0015dc10_18\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_0015dc10_3\n\t"
      ".LFUN_0015dc10_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "jmp .LFUN_0015dc10_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_0015dc10_3:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0015dc10_17\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0015dc10_17\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015dc10_17\n\t"
      "movl 0x47dbe8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0015dc10_4\n\t"
      "pushl $1\n\t"
      "pushl $0x342\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0194\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_4:\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .LFUN_0015dc10_5\n\t"
      "pushl $1\n\t"
      "pushl $0x345\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a07f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_5:\n\t"
      "cmpl 0x47dbe0, %%edi\n\t"
      "jl .LFUN_0015dc10_6\n\t"
      "pushl $1\n\t"
      "pushl $0x346\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a07b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "leal (%%edi,%%edi,2), %%edi\n\t"
      "leal 0x47abe0(,%%edi,4), %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c180050]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0015dc10_7\n\t"
      "pushl $1\n\t"
      "pushl $0x34d\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_0015dc10_8\n\t"
      "pushl $1\n\t"
      "pushl $0x34e\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0770\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_8:\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "subl 0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jle .LFUN_0015dc10_9\n\t"
      "pushl $1\n\t"
      "pushl $0x34f\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015dc10_9:\n\t"
      "cmpl $0x2710, %%esi\n\t"
      "jle .LFUN_0015dc10_10\n\t"
      "movl $0x2710, %%esi\n\t"
      ".LFUN_0015dc10_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1eb2d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0015dc10_11\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015dc10_12\n\t"
      ".LFUN_0015dc10_11:\n\t"
      "pushl $0x2a09a8\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015dc10_12:\n\t"
      "movl 0x47dbe8, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e8920]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015dc10_13\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015dc10_14\n\t"
      ".LFUN_0015dc10_13:\n\t"
      "pushl $0x2a0950\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015dc10_14:\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl 0xc(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl 0x1fb494, %%eax\n\t"
      "leal (%%eax,%%edx,2), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal (%%esi,%%esi,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $5\n\t"
      "call *%[c1ecf90]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015dc10_15\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0015dc10_16\n\t"
      ".LFUN_0015dc10_15:\n\t"
      "pushl $0x2a0868\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015dc10_16:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "subl %%esi, %%eax\n\t"
      "addl %%esi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jg .LFUN_0015dc10_2\n\t"
      ".LFUN_0015dc10_17:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_0015dc10_18\n\t"
      "pushl $0x2a0820\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015dc10_18:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b15dc10_assert), [exitfn] "m"(b15dc10_exitfn), [c180050] "m"(b15dc10_c180050), [c1eb2d0] "m"(b15dc10_c1eb2d0), [c167ff0] "m"(b15dc10_c167ff0), [c1e8920] "m"(b15dc10_c1e8920), [c1ecf90] "m"(b15dc10_c1ecf90), [c8f390] "m"(b15dc10_c8f390)
      : "memory");
}
#else
#error "FUN_0015dc10: clang naked draft required"
#endif


/* FUN_0015de60 (0x15de60) — XBE naked draft (batch 306). */
#if defined(__clang__)
static void (*const b15de60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15de60_exitfn)(int) = system_exit;
static int (*const b15de60_c180050)(short param_1) = FUN_00180050;
static void __stdcall (*const b15de60_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b15de60_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b15de60_c1e8920)(void) = (void *)D3DDevice_SetIndices;
static void (*const b15de60_c1ecf90)(void) = (void *)D3DDevice_DrawIndexedVertices;
static void (*const b15de60_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0015de60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0015de60_1\n\t"
      "pushl $1\n\t"
      "pushl $0x37a\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0015de60_19\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      ".LFUN_0015de60_2:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0015de60_18\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0015de60_18\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015de60_18\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0015de60_18\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015de60_18\n\t"
      "movl 0x47dbe8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0015de60_3\n\t"
      "pushl $1\n\t"
      "pushl $0x387\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0194\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .LFUN_0015de60_4\n\t"
      "pushl $1\n\t"
      "pushl $0x38a\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a07f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_4:\n\t"
      "cmpl 0x47dbe0, %%edi\n\t"
      "jl .LFUN_0015de60_5\n\t"
      "pushl $1\n\t"
      "pushl $0x38b\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a07b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "leal (%%edi,%%edi,2), %%edi\n\t"
      "leal 0x47abe0(,%%edi,4), %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c180050]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%esi), %%cx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180050]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0015de60_6\n\t"
      "pushl $1\n\t"
      "pushl $0x393\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_6:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_0015de60_7\n\t"
      "pushl $1\n\t"
      "pushl $0x394\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0770\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_7:\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "subl 0xc(%%ebp), %%edx\n\t"
      "cmpl %%edx, %%esi\n\t"
      "jle .LFUN_0015de60_8\n\t"
      "pushl $1\n\t"
      "pushl $0x395\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015de60_8:\n\t"
      "cmpl $0x2710, %%esi\n\t"
      "jle .LFUN_0015de60_9\n\t"
      "movl $0x2710, %%esi\n\t"
      ".LFUN_0015de60_9:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c1eb2d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0015de60_10\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015de60_11\n\t"
      ".LFUN_0015de60_10:\n\t"
      "pushl $0x2a0bd8\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015de60_11:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c1eb2d0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015de60_12\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015de60_13\n\t"
      ".LFUN_0015de60_12:\n\t"
      "pushl $0x2a0b58\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015de60_13:\n\t"
      "movl 0x47dbe8, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e8920]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015de60_14\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015de60_15\n\t"
      ".LFUN_0015de60_14:\n\t"
      "pushl $0x2a0950\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015de60_15:\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl 0xc(%%ebp), %%eax\n\t"
      "movl 0x1fb494, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%ecx,%%eax,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $5\n\t"
      "call *%[c1ecf90]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015de60_16\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0015de60_17\n\t"
      ".LFUN_0015de60_16:\n\t"
      "pushl $0x2a0a70\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015de60_17:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "subl %%esi, %%eax\n\t"
      "addl %%esi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jg .LFUN_0015de60_2\n\t"
      ".LFUN_0015de60_18:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_0015de60_19\n\t"
      "pushl $0x2a0a28\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015de60_19:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b15de60_assert), [exitfn] "m"(b15de60_exitfn), [c180050] "m"(b15de60_c180050), [c1eb2d0] "m"(b15de60_c1eb2d0), [c167ff0] "m"(b15de60_c167ff0), [c1e8920] "m"(b15de60_c1e8920), [c1ecf90] "m"(b15de60_c1ecf90), [c8f390] "m"(b15de60_c8f390)
      : "memory");
}
#else
#error "FUN_0015de60: clang naked draft required"
#endif


/* FUN_0015e0f0 (0x15e0f0) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b15e0f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15e0f0_exitfn)(int) = system_exit;
static int (*const b15e0f0_c180050)(short param_1) = FUN_00180050;
static void __stdcall (*const b15e0f0_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b15e0f0_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b15e0f0_c1e8920)(void) = (void *)D3DDevice_SetIndices;
static void (*const b15e0f0_c1ecf90)(void) = (void *)D3DDevice_DrawIndexedVertices;
static void (*const b15e0f0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0015e0f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jne .LFUN_0015e0f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3c3\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0015e0f0_26\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_0015e0f0_2\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0015e0f0_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015e0f0_25\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0015e0f0_25\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0015e0f0_25\n\t"
      "movl 0x47dbe8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0015e0f0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3d1\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0194\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_0015e0f0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3d4\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a02d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_4:\n\t"
      "cmpl 0x47abd8, %%esi\n\t"
      "jl .LFUN_0015e0f0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x3d5\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0298\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_5:\n\t"
      "shll $4, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x476bd8, %%esi\n\t"
      "movw (%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180050]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl (%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edi\n\t"
      "leal 0x476ae8(,%%edi,4), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0015e0f0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x1f8\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x26276c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_6:\n\t"
      "cmpl $0x476b60, %%edi\n\t"
      "jne .LFUN_0015e0f0_7\n\t"
      "movl 0x325668, %%eax\n\t"
      "movl 0x47dbf0, %%ebx\n\t"
      "andl $1, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "jne .LFUN_0015e0f0_8\n\t"
      ".LFUN_0015e0f0_7:\n\t"
      "movl 0xc(%%edi), %%ebx\n\t"
      ".LFUN_0015e0f0_8:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_0015e0f0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x3df\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a04d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_9:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0015e0f0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x3e2\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a04a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_10:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .LFUN_0015e0f0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x3e3\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0438\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_11:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015e0f0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x3e6\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0e84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_12:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movw (%%edx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0015e0f0_13\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_0015e0f0_14\n\t"
      ".LFUN_0015e0f0_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x3e7\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0e30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e0f0_14:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "cmpl $0x2710, %%edi\n\t"
      "jle .LFUN_0015e0f0_15\n\t"
      "movl $0x2710, %%edi\n\t"
      ".LFUN_0015e0f0_15:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "call *%[c1eb2d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0015e0f0_16\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015e0f0_17\n\t"
      ".LFUN_0015e0f0_16:\n\t"
      "pushl $0x2a03e0\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e0f0_17:\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0xc(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e8920]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015e0f0_18\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015e0f0_19\n\t"
      ".LFUN_0015e0f0_18:\n\t"
      "pushl $0x2a0d98\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e0f0_19:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl 0x2a0098(,%%ecx,4), %%eax\n\t"
      "movl 0x1fb494, %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%edx\n\t"
      "movl 0x29f7e8(,%%eax,8), %%ecx\n\t"
      "imull %%edi, %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl 0x29f7ec(,%%eax,8), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ecf90]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015e0f0_20\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0015e0f0_21\n\t"
      ".LFUN_0015e0f0_20:\n\t"
      "pushl $0x2a0cc8\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e0f0_21:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl (%%esi), %%eax\n\t"
      "subl %%edi, %%edx\n\t"
      "subl $0, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .LFUN_0015e0f0_23\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0015e0f0_22\n\t"
      "pushl $1\n\t"
      "pushl $0x406\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0015e0f0_24\n\t"
      ".LFUN_0015e0f0_22:\n\t"
      "addl %%edi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0015e0f0_24\n\t"
      ".LFUN_0015e0f0_23:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%edi,%%edx,1), %%eax\n\t"
      "leal (%%eax,%%edi,2), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LFUN_0015e0f0_24:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0015e0f0_2\n\t"
      ".LFUN_0015e0f0_25:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_0015e0f0_26\n\t"
      "pushl $0x2a0c58\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e0f0_26:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b15e0f0_assert), [exitfn] "m"(b15e0f0_exitfn), [c180050] "m"(b15e0f0_c180050), [c1eb2d0] "m"(b15e0f0_c1eb2d0), [c167ff0] "m"(b15e0f0_c167ff0), [c1e8920] "m"(b15e0f0_c1e8920), [c1ecf90] "m"(b15e0f0_c1ecf90), [c8f390] "m"(b15e0f0_c8f390)
      : "memory");
}
#else
#error "FUN_0015e0f0: clang naked draft required"
#endif


/* FUN_0015e430 (0x15e430) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b15e430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15e430_exitfn)(int) = system_exit;
static int (*const b15e430_c180050)(short param_1) = FUN_00180050;
static void __stdcall (*const b15e430_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = (void *)D3DDevice_SetStreamSource;
static void (*const b15e430_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b15e430_c1e8920)(void) = (void *)D3DDevice_SetIndices;
static void (*const b15e430_c1ecf90)(void) = (void *)D3DDevice_DrawIndexedVertices;
static void (*const b15e430_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0015e430(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jne .LFUN_0015e430_1\n\t"
      "pushl $1\n\t"
      "pushl $0x427\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e430_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0015e430_19\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jmp .LFUN_0015e430_3\n\t"
      ".LFUN_0015e430_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".LFUN_0015e430_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0015e430_18\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015e430_18\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0015e430_18\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015e430_18\n\t"
      "movl 0x47dbe8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0015e430_4\n\t"
      "pushl $1\n\t"
      "pushl $0x431\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0194\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e430_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0015e430_5\n\t"
      "pushl $1\n\t"
      "pushl $0x436\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0e84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e430_5:\n\t"
      "movw (%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0015e430_6\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_0015e430_7\n\t"
      ".LFUN_0015e430_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x437\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0e30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015e430_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180050]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x2710, %%esi\n\t"
      "jle .LFUN_0015e430_8\n\t"
      "movl $0x2710, %%esi\n\t"
      ".LFUN_0015e430_8:\n\t"
      "movl 0x10(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c1eb2d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0015e430_9\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015e430_10\n\t"
      ".LFUN_0015e430_9:\n\t"
      "pushl $0x2a09a8\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e430_10:\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e8920]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015e430_11\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0015e430_12\n\t"
      ".LFUN_0015e430_11:\n\t"
      "pushl $0x2a0fa8\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e430_12:\n\t"
      "movswl (%%edi), %%eax\n\t"
      "movl 0x2a0098(,%%eax,4), %%eax\n\t"
      "movl 0x1fb494, %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%ecx,%%edx,2), %%ecx\n\t"
      "movl 0x29f7e8(,%%eax,8), %%edx\n\t"
      "imull %%esi, %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl 0x29f7ec(,%%eax,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ecf90]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0015e430_13\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0015e430_14\n\t"
      ".LFUN_0015e430_13:\n\t"
      "pushl $0x2a0ee8\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e430_14:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl (%%edi), %%eax\n\t"
      "subl %%esi, %%edx\n\t"
      "subl $0, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .LFUN_0015e430_16\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0015e430_15\n\t"
      "pushl $1\n\t"
      "pushl $0x459\n\t"
      "pushl $0x2a0110\n\t"
      "pushl $0x2a0c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0015e430_17\n\t"
      ".LFUN_0015e430_15:\n\t"
      "addl %%esi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0015e430_17\n\t"
      ".LFUN_0015e430_16:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal (%%esi,%%eax,1), %%ecx\n\t"
      "leal (%%ecx,%%esi,2), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_0015e430_17:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0015e430_2\n\t"
      ".LFUN_0015e430_18:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_0015e430_19\n\t"
      "pushl $0x2a0ea0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0015e430_19:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b15e430_assert), [exitfn] "m"(b15e430_exitfn), [c180050] "m"(b15e430_c180050), [c1eb2d0] "m"(b15e430_c1eb2d0), [c167ff0] "m"(b15e430_c167ff0), [c1e8920] "m"(b15e430_c1e8920), [c1ecf90] "m"(b15e430_c1ecf90), [c8f390] "m"(b15e430_c8f390)
      : "memory");
}
#else
#error "FUN_0015e430: clang naked draft required"
#endif


/* FUN_0015e650 (0x15e650) — readable C lift from XBE leaf.
 * Exactly one of (ptr0 / idx0) and (ptr1 / idx1) must be active. */
void FUN_0015e650(void *ptr0, int idx0, int a2, int a3, void *ptr1, int idx1)
{
  if (!ptr0) {
    if (idx0 == -1) {
      display_assert((char *)0x2a10b4, (char *)0x2a0110, 0x479, 1);
      system_exit(-1);
    }
  } else if (idx0 != -1) {
    display_assert((char *)0x2a107c, (char *)0x2a0110, 0x47a, 1);
    system_exit(-1);
  }
  if (!ptr1) {
    if (idx1 == -1) {
      display_assert((char *)0x2a1048, (char *)0x2a0110, 0x47d, 1);
      system_exit(-1);
    }
  } else if (idx1 != -1) {
    display_assert((char *)0x2a1014, (char *)0x2a0110, 0x47e, 1);
    system_exit(-1);
  }
  if (ptr0) {
    if (ptr1)
      ((void (*)(void *, int, int, void *))FUN_0015e430)(ptr0, a2, a3, ptr1);
    else
      ((void (*)(void *, int, int, int))FUN_0015e0f0)(ptr0, a2, a3, idx1);
  } else if (ptr1) {
    ((void (*)(int, int, int, void *))FUN_0015dc10)(idx0, a2, a3, ptr1);
  } else {
    ((void (*)(int, int, int, int))FUN_0015d8b0)(idx0, a2, a3, idx1);
  }
}



/* FUN_0015e770 (0x15e770) — readable C lift. */
int FUN_0015e770(int a, int b)
{
  ((void (__stdcall *)(int, int, int, int, int))D3DVertexBuffer_Lock)(a, b, 0, 0, 0);
  return 0;
}



/* FUN_0015e7a0 (0x15e7a0) — readable C lift. */
void FUN_0015e7a0(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
}

/* FUN_0015e7d0 (0x15e7d0) — readable C lift. */
int FUN_0015e7d0(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
  return 0;
}

/* FUN_0015e800 (0x15e800) — readable C lift (restored pre-naked). */
void FUN_0015e800(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x15e82c */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 93, 0);
  system_exit(0);
  ((void(*)(void))D3DDevice_CreateIndexBuffer)();
  /* test eax, eax -> jl 0x15e84f */
  FUN_00167ff0(0, (char *)0x002a1370);
  /* test eax, eax -> jne 0x15e86c */
  /* test (char)ebx, (char)ebx -> jne 0x15e889 */
  /* mem[0x0047dbe8] = 0 */
  error(0, (char *)0x002a1338);
  /* cmp (int16_t)ecx, 0xc -> jge 0x15e950 */
  FUN_00180050(0);
  D3DDevice_CreateVertexBuffer(eax, 520, 0, 0, (void *)(uintptr_t)edi);
  /* test (char)ebx, (char)ebx -> je 0x15e904 */
  /* test eax, eax -> jl 0x15e904 */
  FUN_00167ff0(0, (char *)0x002a1268);
  /* relift: cmp dword ptr [edi], 0 -> jne 0x15e91d */
  /* test (char)ebx, (char)ebx -> jne 0x15e936 */
  error(0, (char *)0x002a1230);
  /* test (char)ebx, (char)ebx -> je 0x15e9a8 */
  FUN_00180050(0);
  D3DDevice_CreateVertexBuffer(eax, 520, 0, 0, (void *)0);
  /* test eax, eax -> jl 0x15e97d */
  FUN_00167ff0(0, (char *)0x002a1128);
  /* test eax, eax -> jne 0x15e99a */
  /* test (char)ebx, (char)ebx -> jne 0x15e9b7 */
  /* mem[0x0047dbf0] = 0 */
  error(0, (char *)0x002a10ec);
  /* relift: FUN_e912e9e3(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}



/* FUN_0015e9e0 (0x15e9e0) — readable C lift. */
void FUN_0015e9e0(void)
{
  int *slot;
  int i;

  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a0110, 0x107, 1);
    system_exit(-1);
  }
  slot = (int *)0x476af4;
  for (i = 0xc; i != 0; i--) {
    if (*slot) {
      D3DResource_Release((void *)*slot);
      *slot = 0;
    }
    slot = (int *)((char *)slot + 0x14);
  }
  if (*(int *)0x47dbf0) {
    D3DResource_Release((void *)*(int *)0x47dbf0);
    *(int *)0x47dbf0 = 0;
  }
  if (*(int *)0x47dbe8) {
    D3DResource_Release((void *)*(int *)0x47dbe8);
    *(int *)0x47dbe8 = 0;
  }
}
/* FUN_0015ea70 (0x15ea70) — readable C lift. */
void *FUN_0015ea70(int idx)
{
  int *slot;
  int *heap;
  void *result;

  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a0110, 0x14b, 1);
    system_exit(-1);
  }
  if (idx == -1) {
    error(2, (const char *)0x2a1468);
    return 0;
  }
  if (idx < 0) {
    display_assert((char *)0x2a07f8, (char *)0x2a0110, 0x151, 1);
    system_exit(-1);
  }
  if (idx >= *(int *)0x47dbe0) {
    display_assert((char *)0x2a07b8, (char *)0x2a0110, 0x152, 1);
    system_exit(-1);
  }
  if (!*(int *)0x47dbe8) {
    display_assert((char *)0x2a0194, (char *)0x2a0110, 0x154, 1);
    system_exit(-1);
  }
  slot = (int *)(0x47abe0 + idx * 12);
  if (slot[1] <= 0) {
    display_assert((char *)0x2a14a4, (char *)0x2a0110, 0x158, 1);
    system_exit(-1);
  }
  heap = *(int **)0x47dbe8;
  result = (void *)(heap[1] + slot[0] * 6);
  slot[2] = (int)result;
  *(char *)0x47dbec = 0;
  return result;
}

/* FUN_0015eb90 (0x15eb90) — readable C lift. */
void FUN_0015eb90(int idx)
{
  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a0110, 0x175, 1);
    system_exit(-1);
  }
  if (idx == -1) {
    error(2, (const char *)0x2a14d0);
    return;
  }
  if (idx < 0) {
    display_assert((char *)0x2a07f8, (char *)0x2a0110, 0x179, 1);
    system_exit(-1);
  }
  if (idx >= *(int *)0x47dbe0) {
    display_assert((char *)0x2a07b8, (char *)0x2a0110, 0x17a, 1);
    system_exit(-1);
  }
  if (!*(int *)0x47dbe8) {
    display_assert((char *)0x2a0194, (char *)0x2a0110, 0x17c, 1);
    system_exit(-1);
  }
}
/* FUN_0015ec50 (0x15ec50) — readable C lift (restored pre-naked). */
int FUN_0015ec50(int dynamic_vertex_buffer_index)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x15ec81 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 519, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x325652], 0 -> jne 0x15ec9a */
  error(0, (char *)0x002a15d8);
  /* cmp esi, -1 -> je 0x15ee64 */
  /* test esi, esi -> jge 0x15ecca */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 535, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15ecf2 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 536, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ed1b */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 539, 0);
  system_exit(0);
  FUN_00180050(0);
  display_assert((char *)0x002a15b4, (char *)0x002a0110, 544, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0xc -> jl 0x15ed81 */
  display_assert((char *)0x002a1574, (char *)0x002a0110, 545, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15eda8 */
  display_assert((char *)0x002a154c, (char *)0x002a0110, 546, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x15edda */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp ebx, 0x476b60 -> jne 0x15edfb */
  /* test eax, eax -> jne 0x15ee28 */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 551, 0);
  system_exit(0);
  ((void(*)(void))D3DVertexBuffer_Lock)();
  error(0, (char *)0x002a1510);
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
}



/* FUN_0015ee80 (0x15ee80) — readable C lift (restored pre-naked). */
void FUN_0015ee80(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x15eeac */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 582, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15efde */
  /* test esi, esi -> jge 0x15eedd */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 588, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15ef05 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 589, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ef2e */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 591, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15ef45 */
  /* cmp (int16_t)eax, 0xc -> jl 0x15ef65 */
  display_assert((char *)0x002a1668, (char *)0x002a0110, 595, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x15ef96 */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp esi, 0x476b60 -> jne 0x15efb4 */
  /* test esi, esi -> jne 0x15efed */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 600, 0);
  system_exit(0);
  error(0, (char *)0x002a1628);
  /* cmp esi, 0x52 -> jge 0x15f00b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15f019 */
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x15f02e */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x15f03a */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x15f046 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15f052 */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x15f05e */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x15f06a */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x15f076 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15f082 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15f08e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15f09a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15f0a6 */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x15f0b5 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x15f0c4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15f0d3 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x15f0e2 */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x15f0f1 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x15f100 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x15f10f */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x15f11e */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x15f12d */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x15f13c */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x15f14b */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x15f15a */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x15f169 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x15f178 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x15f187 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x15f195 */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x15f1ac */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15f1b9 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x15f1c6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15f1d3 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x15f1e0 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_0015f1f0 (0x15f1f0) — readable C lift. */
void FUN_0015f1f0(void)
{
  FUN_0016f910(0x1b);
}



/* FUN_0015f540 (0x15f540) — readable C lift. */
void FUN_0015f540(void)
{
  display_assert((const char *)0x2a1704, (const char *)0x2a16c4, 0xff, 1);
  system_exit(-1);
}




/* FUN_0015f5e0 (0x15f5e0) — readable C lift. */
int FUN_0015f5e0(int a, int b, int c)
{
  ((void (__stdcall *)(int, int, int))(void *)D3DDevice_SetVertexData2f)(a, b, c);
  return 0;
}

/* FUN_0015f630 (0x15f630) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b15f630_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15f630_exitfn)(int) = system_exit;
static void * (*const b15f630_c184330)(void) = rasterizer_transparent_geometry_group_new;
static void * (*const b15f630_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b15f630_c17edd0)(void) = (void *)rasterizer_frame_statistics_count_static_vertices;
static void (*const b15f630_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0015f630(uint32_t source, uint32_t param, int arg3, int arg4, uint32_t handle, int subcount2, float *origin, uint32_t widget_flags)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_0015f630_1\n\t"
      "pushl $1\n\t"
      "pushl $0x26\n\t"
      "pushl $0x2a16c4\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015f630_1:\n\t"
      "cmpb %%bl, 0x3256d8\n\t"
      "je .LFUN_0015f630_10\n\t"
      "testb $0x20, 0x24(%%ebp)\n\t"
      "je .LFUN_0015f630_2\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpw $1, 0x24(%%eax)\n\t"
      "je .LFUN_0015f630_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2a\n\t"
      "pushl $0x2a16c4\n\t"
      "pushl $0x2a17a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015f630_2:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpw $1, 0x24(%%ecx)\n\t"
      "je .LFUN_0015f630_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x2a16c4\n\t"
      "pushl $0x2a1780\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015f630_3:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_0015f630_4\n\t"
      "pushl $1\n\t"
      "pushl $0x34\n\t"
      "pushl $0x2a16c4\n\t"
      "pushl $0x2a1774\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0015f630_4:\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c184330]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_0015f630_8\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x44(%%esi)\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x54(%%esi)\n\t"
      "movl %%edx, 0x50(%%esi)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%edx, 0x5c(%%esi)\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "movl %%ebx, 0x8(%%esi)\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movw %%bx, 0x10(%%esi)\n\t"
      "movw %%bx, 0x14(%%esi)\n\t"
      "movl %%ebx, 0x48(%%esi)\n\t"
      "movl %%ebx, 0x4c(%%esi)\n\t"
      "movl %%ebx, 0x58(%%esi)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "leal 0x74(%%esi), %%ecx\n\t"
      "flds 0x5a5bd8\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fstps 0x70(%%esi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "leal 0x80(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "movl %%ecx, 0x40(%%esi)\n\t"
      "movl %%ecx, 0x3c(%%esi)\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "movw %%cx, 0x94(%%esi)\n\t"
      "movw %%cx, 0x96(%%esi)\n\t"
      "movl %%ebx, 0x98(%%esi)\n\t"
      "movb %%bl, 0x9d(%%esi)\n\t"
      "cmpw $1, 0x24(%%eax)\n\t"
      "jne .LFUN_0015f630_5\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_0015f630_6\n\t"
      "flds 0x70(%%esi)\n\t"
      "fadds 0x25337c\n\t"
      "fstps 0x70(%%esi)\n\t"
      "jmp .LFUN_0015f630_6\n\t"
      ".LFUN_0015f630_5:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      ".LFUN_0015f630_6:\n\t"
      "movl %%ebx, 0x60(%%esi)\n\t"
      "movw %%bx, 0x64(%%esi)\n\t"
      "movl %%ebx, 0x68(%%esi)\n\t"
      "movl %%ebx, 0x6c(%%esi)\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .LFUN_0015f630_9\n\t"
      "movl 0x5a5504, %%esi\n\t"
      "movl 0x5a5508, %%edx\n\t"
      "movl 0x5a550c, %%ecx\n\t"
      "incl %%esi\n\t"
      "addl %%eax, %%edx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%esi, 0x5a5504\n\t"
      "movl %%edx, 0x5a5508\n\t"
      "jle .LFUN_0015f630_7\n\t"
      "movl %%eax, 0x5a550c\n\t"
      ".LFUN_0015f630_7:\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c17edd0]\n\t"
      "movl 0x5a5510, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "addl %%eax, %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x5a5510\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0015f630_8:\n\t"
      "cmpb %%bl, 0x47dbf6\n\t"
      "jne .LFUN_0015f630_9\n\t"
      "pushl $0x2a1744\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x47dbf6\n\t"
      ".LFUN_0015f630_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_0015f630_10:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b15f630_assert), [exitfn] "m"(b15f630_exitfn), [c184330] "m"(b15f630_c184330), [c1906b0] "m"(b15f630_c1906b0), [c17edd0] "m"(b15f630_c17edd0), [c8f390] "m"(b15f630_c8f390)
      : "memory");
}
#else
#error "FUN_0015f630: clang naked draft required"
#endif


/* FUN_0015f8e0 (0x15f8e0) — readable C lift (restored pre-naked). */
void FUN_0015f8e0(void *render_data, void *vertices)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ebx -> jne 0x15f915 */
  display_assert((char *)0x0029dc40, (char *)0x002a16c4, 756, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256da] */
  /* test (char)eax, (char)eax -> je 0x160433 */
  /* relift: cmp word ptr [0x5a5bc0], (int16_t)ebx -> jne 0x160433 */
  display_assert((char *)0x0029f510, (char *)0x002a16c4, 761, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0xc], ebx -> jne 0x15f97d */
  display_assert((char *)0x002a18a4, (char *)0x002a16c4, 763, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x14], ebx -> je 0x15f9a7 */
  /* relift: cmp dword ptr [esi + 0x10], ebx -> jne 0x15f9ac */
  display_assert((char *)0x002a1878, (char *)0x002a16c4, 765, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x10], ebx -> je 0x15f9d0 */
  /* relift: cmp dword ptr [esi], ebx -> je 0x15f9d0 */
  display_assert((char *)0x002a1840, (char *)0x002a16c4, 767, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_001580b0(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* cmp edx, ebx -> je 0x15fa6f */
  /* cmp edx, ebx -> je 0x15fa91 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  /* cmp eax, ebx -> je 0x15fc19 */
  /* cmp eax, ebx -> je 0x15fc32 */
  /* cmp eax, ebx -> je 0x15fc4d */
  /* cmp eax, ebx -> je 0x15fc63 */
  /* cmp eax, ebx -> je 0x15fc78 */
  /* cmp eax, ebx -> je 0x15fc8b */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x15fd8e */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp (int16_t)ebx, 3 -> jl 0x15fce1 */
  FUN_00178b40(0, 0, 0);
  /* test edi, edi -> je 0x15ffc7 */
  /* test (char)eax, (char)eax -> jne 0x15fdd0 */
  display_assert((char *)0x002a182c, (char *)0x002a16c4, 886, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x18], 0x3f800000 -> je 0x15fdf8 */
  display_assert((char *)0x002a1814, (char *)0x002a16c4, 887, ebx);
  system_exit(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x8001 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetTextureStageState(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = 0x11104 */
  /* mem[0x005a5ae8] = ecx */
  /* test (char)eax, 0x41 -> je 0x15fec2 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00159070(0.0f);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5ac0] = 0x12081208 */
  /* mem[0x005a5b48] = 0x1120e820 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5b0c] = ecx */
  /* mem[0x005a5ac4] = 0x6c200000 */
  /* mem[0x005a5b2c] = 0xc0 */
  /* mem[0x005a5b4c] = 0x3c011c02 */
  /* mem[0x005a5b78] = edx */
  /* mem[0x005a5af0] = eax */
  /* mem[0x005a5b10] = ecx */
  /* mem[0x005a5ac8] = 0x820b220 */
  /* mem[0x005a5b30] = edx */
  /* mem[0x005a5b7c] = edx */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5af4] = ecx */
  /* mem[0x005a5b14] = edx */
  /* mem[0x005a5acc] = 0x12201120 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0xc200120 */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ae0] = 0xc180000 */
  /* test eax, eax -> je 0x1603ae */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = eax */
  /* test ecx, ecx -> jne 0x160022 */
  /* test ecx, ecx -> jne 0x16003c */
  /* test eax, eax -> je 0x16008a */
  /* test eax, eax -> je 0x1600a2 */
  FUN_000d1c90((float *)(uintptr_t)eax);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1c90((float *)(uintptr_t)ecx);
  /* mem[0x005a5b08] = eax */
  FUN_000d1c90((float *)(uintptr_t)edx);
  /* mem[0x005a5aec] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5af8] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5afc] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5b00] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5b04] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x8010902 */
  /* mem[0x005a5ac0] = 0x18111912 */
  /* mem[0x005a5b4c] = 0xa010804 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ac4] = 0x1a111814 */
  /* mem[0x005a5b2c] = eax */
  /* cmp eax, 5 -> ja 0x160287 */
  /* mem[0x005a5b50] = 0xc200920 */
  /* mem[0x005a5ac8] = 0x1c201920 */
  /* mem[0x005a5b7c] = edi */
  /* mem[0x005a5b50] = 0xc20e920 */
  /* mem[0x005a5ac8] = 0x1c20f920 */
  /* mem[0x005a5b50] = 0xc090000 */
  /* mem[0x005a5b7c] = ebx */
  /* mem[0x005a5ac8] = 0x1c190000 */
  /* mem[0x005a5b30] = ebx */
  /* mem[0x005a5b7c] = 0x20c0 */
  /* mem[0x005a5b50] = 0xc090000 */
  /* mem[0x005a5ac8] = 0x1c190000 */
  /* mem[0x005a5b30] = edi */
  /* mem[0x005a5ac8] = 0x820a920 */
  /* mem[0x005a5b50] = 0x1920b820 */
  /* mem[0x005a5acc] = 0x1c1c0c0c */
  /* mem[0x005a5b34] = 0x24c00 */
  /* mem[0x005a5b54] = eax */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ad0] = 0x5c5c */
  /* mem[0x005a5b38] = 0x4d00 */
  /* mem[0x005a5b58] = eax */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5ad4] = eax */
  /* mem[0x005a5b3c] = edx */
  /* mem[0x005a5b5c] = 0x1ca01da0 */
  /* mem[0x005a5b88] = edx */
  /* mem[0x005a5b30] = edx */
  /* mem[0x005a5b7c] = edx */
  /* test eax, eax -> je 0x16038d */
  /* cmp eax, 4 -> ja 0x16038c */
  /* relift: cmp word ptr [esi + 0x84], 5 -> jne 0x1602d5 */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetRenderState_CullMode(2305);
  FUN_00178b40(0, 0, 0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, ecx);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp esi, 0x52 -> jge 0x16048b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x160499 */
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x1604ae */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x1604ba */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x1604c6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1604d2 */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x1604de */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x1604ea */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x1604f6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x160502 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16050e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16051a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x160526 */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x160535 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x160544 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x160553 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x160562 */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x160571 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x160580 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x16058f */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x16059e */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x1605ad */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x1605bc */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x1605cb */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x1605da */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x1605e9 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x1605f8 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x160607 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x160615 */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x16062c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x160639 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x160646 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x160653 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x160660 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();
  /* cmp esi, 0x52 -> jge 0x16068f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1606a2 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x1606bf */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x1606cf */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x1606df */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1606ef */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x1606ff */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x16070f */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x16071f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16072f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16073f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16074f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16075f */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x160772 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x160785 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x160798 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x1607ab */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x1607be */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x1607d1 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x1607e4 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x1607f7 */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x16080a */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x16081d */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x160830 */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x160843 */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x160856 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x160869 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x16087c */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x16088a */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  D3DDevice_SetTexture(ecx, (void *)(uintptr_t)eax);
  /* cmp edx, 0x16 -> jge 0x1608b0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1608c1 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x1608d2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1608e3 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x1608f0 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_00160920 (0x160920) — readable C lift. */
void FUN_00160920(void)
{
  FUN_0016fa40(3);
}



/* 0x160970 */
void _rasterizer_hud_end(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00160980 (0x160980) — readable C lift. */
void FUN_00160980(void)
{
  FUN_0016fa40(0xb);
}



/* FUN_00160bc0 (0x160bc0) — readable C lift. */
void FUN_00160bc0(void)
{
  FUN_0016fa40(0xd);
}



/* FUN_0015f200 (0x15f200) — readable C lift (profile thunk). */
void FUN_0015f200(void)
{
  FUN_0016fa40(27);
}

/* _rasterizer_hud_begin (0x160940) — readable C lift (profile thunk). */
void _rasterizer_hud_begin(void)
{
  FUN_0016fa40(5);
}

/* FUN_00160950 (0x160950) — readable C lift (profile thunk). */
void FUN_00160950(void)
{
  FUN_00158ae0(2);
  FUN_0016fa40(8);
}

/* _rasterizer_dynamic_lit_geometry_draw (0x1609a0) — readable C lift (profile thunk). */
void _rasterizer_dynamic_lit_geometry_draw(void)
{
  FUN_0016fa40(12);
}

/* FUN_00160be0 (0x160be0) — readable C lift (profile thunk). */
void FUN_00160be0(void)
{
  FUN_0016fa40(14);
}

/* FUN_00160bf0 (0x160bf0) — readable C lift (profile thunk). */
void FUN_00160bf0(void)
{
  FUN_0016f910(15);
}

/* FUN_00160c00 (0x160c00) — readable C lift (profile thunk). */
void FUN_00160c00(void)
{
  FUN_0016fa40(15);
}

/* FUN_00160bd0 (0x160bd0) — readable C lift (profile thunk). */
void FUN_00160bd0(void)
{
  FUN_0016f910(0xe);
}

/* FUN_00160c10 (0x160c10) — readable C lift (profile thunk). */
void FUN_00160c10(void)
{
  FUN_0016f910(0x10);
  FUN_00174ce0();
}

/* FUN_00160c20 (0x160c20) — readable C lift. */
void FUN_00160c20(void)
{
  FUN_001749b0();
  FUN_0016fa40(0x10);
}

/* FUN_00160c30 (0x160c30) — readable C lift. */
void FUN_00160c30(void)
{
  short mode;
  int bitmap;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x11, 1);
    system_exit(-1);
  }
  FUN_0016f910(3);
  mode = *(short *)0x3256bc;
  if (mode != 0 && mode != 2 && mode != 6 && mode != 3 && mode != 4 &&
      mode != 7 && mode != 5 && mode != 8)
    return;
  if (!*(unsigned char *)0x3256c9)
    return;

  bitmap = *(int *)(*(int *)0x476204 + 0x1c);
  rasterizer_set_texture_direct(3, bitmap, 0);

  D3DDevice_SetTextureStageState(3, 0xa, 3);
  D3DDevice_SetTextureStageState(3, 0xb, 3);
  D3DDevice_SetTextureStageState(3, 0xc, 3);
  D3DDevice_SetTextureStageState(3, 0xd, 2);
  D3DDevice_SetTextureStageState(3, 0xe, 2);
  D3DDevice_SetTextureStageState(3, 0xf, 2);

  D3DDevice_SetRenderState_CullMode(0x901);
  D3DDevice_SetRenderState_Simple(0x40358, 0x1010101);
  *(unsigned int *)0x1fb7a4 = 0x1010101;
  D3DDevice_SetRenderState_Simple(0x40304, 0);
  *(unsigned int *)0x1fb784 = 0;
  D3DDevice_SetRenderState_Simple(0x40340, 0x7f);
  *(unsigned int *)0x1fb78c = 0x7f;
  D3DDevice_SetRenderState_ZEnable(1);
  D3DDevice_SetRenderState_Simple(0x40354, 0x203);
  *(unsigned int *)0x1fb77c = 0x203;
  D3DDevice_SetRenderState_Simple(0x4035c, 1);
  *(unsigned int *)0x1fb798 = 1;
  D3DDevice_SetRenderState_ZBias(0);
}

/* FUN_00160dc0 (0x160dc0) — readable C lift. */
void FUN_00160dc0(void *bitmap)
{
  short mode;
  unsigned int v;
  unsigned int seed;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x44, 1);
    system_exit(-1);
  }
  mode = *(short *)0x3256bc;
  if (mode != 0 && mode != 2 && mode != 6 && mode != 3 && mode != 4 &&
      mode != 7 && mode != 5 && mode != 8)
    return;
  if (!*(unsigned char *)0x3256c9)
    return;

  if (bitmap) {
    rasterizer_set_texture_bitmap_data(2, bitmap);
    D3DDevice_SetTextureStageState(2, 0xa, 3);
    D3DDevice_SetTextureStageState(2, 0xb, 3);
    v = (*(unsigned char *)0x3256ed != 0) ? 2u : 1u;
    D3DDevice_SetTextureStageState(2, 0xd, v);
    v = (*(unsigned char *)0x3256ed != 0) ? 2u : 1u;
    D3DDevice_SetTextureStageState(2, 0xe, v);
    v = (*(unsigned char *)0x3256ed != 0) ? 2u : 1u;
    D3DDevice_SetTextureStageState(2, 0xf, v);
    *(unsigned char *)0x47dca4 = 0;
  } else {
    D3DDevice_SetTexture(2, 0);
    *(unsigned char *)0x47dca4 = 1;
  }

  mode = *(short *)0x3256b0;
  if (mode <= 0)
    return;
  if (mode == 2) {
    *(float *)0x47dca0 = *(float *)0x3256e4;
    *(float *)0x47dc9c = *(float *)0x3256e4;
    *(float *)0x47dc98 = *(float *)0x3256e4;
    return;
  }
  seed = (unsigned int)bitmap;
  *(float *)0x47dc98 = random_math_real(&seed);
  *(float *)0x47dc9c = random_math_real(&seed);
  *(float *)0x47dca0 = random_math_real(&seed);
}

/* FUN_00160f50 (0x160f50) — readable C lift (restored pre-naked). */
void FUN_00160f50(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 135, ebx);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* cmp (int16_t)eax, 9 -> jne 0x161693 */
  /* relift: cmp word ptr [eax], (int16_t)ebx -> jne 0x161ecc */
  /* cmp (int16_t)edx, 0x33 -> jge 0x161ecc */
  /* cmp eax, esi -> je 0x1612f8 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(edi);
  FUN_00178b40(37, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = edx */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* mem[0x005a5b94] = 3 */
  /* mem[0x005a5ae8] = 0xff0000 */
  /* mem[0x005a5b08] = 0xff */
  /* mem[0x005a5b48] = 0x4849484a */
  /* mem[0x005a5b74] = 0x30cd */
  /* mem[0x005a5b4c] = 0xc0c0d0d */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b50] = 0xc010d02 */
  /* mem[0x005a5b7c] = 0xc00 */
  /* mem[0x005a5ae0] = eax */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ae0] = edx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov (char)ecx, byte ptr [0x47dca4] */
  FUN_0015de60();
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x1616c6 */
  /* cmp (int16_t)eax, 2 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 6 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 3 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 4 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 7 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 5 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 8 -> jne 0x161ecc */
  /* relift: relift: mov (char)eax, byte ptr [0x3256c9] */
  /* test (char)eax, (char)eax -> je 0x161ecc */
  /* relift: cmp dword ptr [ebp + 8], edi -> jne 0x1616f6 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 347, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x1c], edi -> jne 0x161719 */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 348, ebx);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)edx, 0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)eax);
  FUN_00178b40(16, 0, 0);
  /* test (char)ebx, (char)eax -> je 0x161756 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256f4] */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = eax */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [edi + 0x180], (char)ebx -> je 0x161850 */
  SetTextureStageStateSmart(0, 13, 0);
  SetTextureStageStateSmart(0, 14, 0);
  SetTextureStageStateSmart(0, 13, 0);
  SetTextureStageStateSmart(0, 14, 0);
  SetTextureStageStateSmart(0, 15, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* relift: cmp dword ptr [edi + 0x260], esi -> jne 0x161989 */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* relift: relift: mov (char)ecx, byte ptr [0x47dca4] */
  /* relift: relift: mov (char)ecx, byte ptr [0x3256ec] */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5b74] = 0x208c */
  /* mem[0x005a5ac4] = 0x34201408 */
  /* mem[0x005a5b2c] = 0xc00 */
  /* mem[0x005a5ae0] = 0xa0f000c */
  /* mem[0x005a5ae4] = 0x1c011800 */
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b48] = ecx */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a199c, (char *)0x002a18c0, 448, ebx);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a196c, (char *)0x002a18c0, 449, ebx);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a1940, (char *)0x002a18c0, 450, ebx);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(edx, 0.0f);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(eax, 0.0f);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(ecx, 0.0f);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00012fb0((float *)(uintptr_t)eax, 0.0f, (float *)0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00012fb0((float *)(uintptr_t)edx, 0.0f, (float *)0);
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)0);
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)0);
  FUN_00012fb0((float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)eax);
  FUN_00012fb0((float *)(uintptr_t)eax, 0.0f, (float *)(uintptr_t)edx);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* relift: relift: mov dl, byte ptr [0x47dca4] */
  /* relift: relift: mov dl, byte ptr [0x3256ec] */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5b88] = eax */
  /* mem[0x005a5b98] = ecx */
  /* mem[0x005a5b94] = 0x11106 */
  /* mem[0x005a5ac0] = 0x1120b920 */
  /* mem[0x005a5b48] = 0x1920b120 */
  /* mem[0x005a5ac4] = 0xdcdccccc */
  /* mem[0x005a5b2c] = 0x24c00 */
  /* mem[0x005a5b4c] = edx */
  /* mem[0x005a5b78] = 0x2080 */
  /* mem[0x005a5af0] = 0xff0000 */
  /* mem[0x005a5b10] = 0xff00 */
  /* mem[0x005a5ac8] = 0x1c1c0920 */
  /* mem[0x005a5b30] = 0xc9 */
  /* mem[0x005a5b50] = 0x9010902 */
  /* mem[0x005a5b7c] = 0x30cd */
  /* mem[0x005a5acc] = 0x5c5c */
  /* mem[0x005a5b34] = 0x4c00 */
  /* mem[0x005a5b54] = 0xc010d02 */
  /* mem[0x005a5b80] = 0xd00 */
  /* mem[0x005a5ad0] = 0x34201408 */
  /* mem[0x005a5b58] = 0x11c0220 */
  /* mem[0x005a5b5c] = 0xc190d20 */
  /* mem[0x005a5ae0] = 0xa0f000c */
  /* mem[0x005a5ae4] = 0x1c011800 */
  FUN_00159070(0.0f);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  /* mem[0x005a5af4] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5b14] = eax */
  FUN_000d1dd0((float *)(uintptr_t)eax);
  /* mem[0x005a5af8] = eax */
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  /* mem[0x005a5b18] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edi);
  /* mem[0x005a5b6c] = eax */
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256b0] */
  /* cmp (int16_t)eax, (int16_t)ebx -> jne 0x161d7b */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* mem[0x005a5ae0] = 0x2004000c */
  /* cmp (int16_t)eax, 2 -> je 0x161d87 */
  /* cmp (int16_t)eax, 3 -> jne 0x161da3 */
  FUN_000d1dd0((void *)0x0047dc98);
  /* mem[0x005a5b70] = eax */
  /* mem[0x005a5ae0] = 0x2002000c */
  /* cmp eax, 8 -> ja 0x161e3c */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ac0] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 8 */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ac0] = 0x48402020 */
  /* mem[0x005a5b28] = 0x20d00 */
  /* mem[0x005a5b48] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0x1d */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ac0] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0x20 */
  display_assert((char *)0x002a1900, (char *)0x002a18c0, 575, ebx);
  system_exit(0);
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov (char)ebx, byte ptr [0x47dca4] */
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x161ecc */
  /* mem[0x005a542c] = eax */
  /* mem[0x005a5428] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5424] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_00161f00 (0x161f00) — readable C lift (restored pre-naked). */
void FUN_00161f00(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 627, esi);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1621be */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cb] */
  /* test (char)eax, (char)eax -> je 0x1621be */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(esi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18861 */
  /* mem[0x005a5b94] = 4 */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20c00 */
  /* mem[0x005a5b48] = 0x90a484b */
  /* mem[0x005a5b74] = ecx */
  /* mem[0x005a5b4c] = 0xc0d0000 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5b50] = 0xc1c0000 */
  /* mem[0x005a5b7c] = eax */
  /* mem[0x005a5b54] = 0xc010c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ae0] = 0xc010000 */
  /* mem[0x005a5ae4] = 0xd00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
  (void)esi;
}


/* FUN_001621c0 (0x1621c0) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void (*const b1621c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1621c0_exitfn)(int) = system_exit;
static void (*const b1621c0_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void __stdcall (*const b1621c0_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static float (*const b1621c0_c10a5e0)(int16_t function_type, float input) = FUN_0010a5e0;
static void (*const b1621c0_c109e90)(float *out, float yaw, float pitch, float roll) = FUN_00109e90;
static void (*const b1621c0_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static float (*const b1621c0_norm)(float *) = normalize3d;
static void __stdcall (*const b1621c0_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static unsigned int (*const b1621c0_cd1dd0)(float *color) = FUN_000d1dd0;
static void (*const b1621c0_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;

__attribute__((naked, noinline))
void FUN_001621c0(int object_handle)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x80, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001621c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2d3\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001621c0_1:\n\t"
      "cmpw $0, 0x3256bc\n\t"
      "jne .LFUN_001621c0_8\n\t"
      "movb 0x3256cb, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001621c0_8\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001621c0_2\n\t"
      "cmpl 0x5a37e0, %%esi\n\t"
      "jl .LFUN_001621c0_3\n\t"
      ".LFUN_001621c0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x2d9\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1a58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001621c0_3:\n\t"
      "imull $0x38, %%esi, %%esi\n\t"
      "addl $0x5a37e4, %%esi\n\t"
      "flds 0x34(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001621c0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2dc\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x29e134\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001621c0_4:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x70(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl $1\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xc, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl (%%esi), %%edx\n\t"
      "flds 0x90(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001621c0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x2ec\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1a30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001621c0_5:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0xa0(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001621c0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x2ed\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1a04\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001621c0_6:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "flds 0x98(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001621c0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x2ee\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a19dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001621c0_7:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0x5a5e18\n\t"
      "fdivs 0x90(%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8e(%%eax), %%dx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x255a54\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5a5e18\n\t"
      "fdivs 0xa0(%%eax)\n\t"
      "movswl 0x9e(%%eax), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x255a54\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movw 0x96(%%eax), %%cx\n\t"
      "flds 0x5a5e18\n\t"
      "addl $4, %%esp\n\t"
      "fdivs 0x98(%%eax)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x255a54\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109e90]\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109680]\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109680]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "addl $0x34, %%esp\n\t"
      "flds 0x253398\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "fdivs 0x34(%%esi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%ecx, -0x80(%%ebp)\n\t"
      "pushl $5\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x51\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "movl $0x3f800000, -0x64(%%ebp)\n\t"
      "movl $0x3f800000, -0x54(%%ebp)\n\t"
      "movl $0x3f800000, -0x44(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x3c(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0x3f800000, -0x34(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "addl $0x28, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[cd1dd0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x40a60, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%esi, 0x1fb6c0\n\t"
      "popl %%esi\n\t"
      ".LFUN_001621c0_8:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1621c0_assert), [exitfn] "m"(b1621c0_exitfn), [c155e80] "m"(b1621c0_c155e80), [c1e9410] "m"(b1621c0_c1e9410), [c10a5e0] "m"(b1621c0_c10a5e0), [c109e90] "m"(b1621c0_c109e90), [c109680] "m"(b1621c0_c109680), [norm] "m"(b1621c0_norm), [c1eb8d0] "m"(b1621c0_c1eb8d0), [cd1dd0] "m"(b1621c0_cd1dd0), [c1e9350] "m"(b1621c0_c1e9350)
      : "memory");
}
#else
#error "FUN_001621c0: clang naked draft required"
#endif


/* FUN_00162560 (0x162560) — readable C lift (restored pre-naked). */
void FUN_00162560(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16258f */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 819, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x16277d */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cb] */
  /* test (char)eax, (char)eax -> je 0x16277d */
  /* test edi, edi -> jne 0x1625d4 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 826, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 831, 0);
  system_exit(0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)edi);
  FUN_00178b40(49, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  FUN_000d1dd0((float *)(uintptr_t)esi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb744] = esi */
  ((void(*)(void))FUN_0015dc10)();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16277a */
  /* mem[0x005a5448] = eax */
  /* mem[0x005a5444] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5440] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_00162790 (0x162790) — readable C lift. */
void FUN_00162790(void)
{
  short mode;
  unsigned int color;
  unsigned int blend;
  unsigned int zwrite;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x399, 1);
    system_exit(-1);
  }
  FUN_0016f910(8);
  mode = *(short *)0x3256bc;
  if (mode != 0 && mode != 1 && mode != 3 && mode != 4 && mode != 7 &&
      mode != 5 && mode != 8)
    return;
  if (!*(unsigned char *)0x3256cc)
    return;

  D3DDevice_SetRenderState_CullMode(0x901);
  color = 0x10101;
  if (*(unsigned char *)0x3256f5)
    color += 0x1000000;
  D3DDevice_SetRenderState_Simple(0x40358, color);
  *(unsigned int *)0x1fb7a4 = color;
  D3DDevice_SetRenderState_Simple(0x40304, 1);
  *(unsigned int *)0x1fb784 = 1;
  blend = (mode == 1) ? 1u : 0x306u;
  D3DDevice_SetRenderState_Simple(0x40344, blend);
  *(unsigned int *)0x1fb790 = blend;
  zwrite = (mode == 1) ? 1u : 0u;
  D3DDevice_SetRenderState_Simple(0x40348, zwrite);
  *(unsigned int *)0x1fb794 = zwrite;
  D3DDevice_SetRenderState_Simple(0x40350, 0x8006);
  *(unsigned int *)0x1fb7c0 = 0x8006;
  D3DDevice_SetRenderState_Simple(0x40300, 0);
  *(unsigned int *)0x1fb788 = 0;
  D3DDevice_SetRenderState_ZEnable(mode != 1);
  D3DDevice_SetRenderState_Simple(0x40354, 0x202);
  *(unsigned int *)0x1fb77c = 0x202;
  D3DDevice_SetRenderState_Simple(0x4035c, 0);
  *(unsigned int *)0x1fb798 = 0;
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00158ae0(5);
}

/* FUN_00162920 (0x162920) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b162920_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b162920_exitfn)(int) = system_exit;
static void * (*const b162920_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static int (*const b162920_c190710)(void *shader) = shader_get_vertex_shader_permutation;
static void (*const b162920_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void (*const b162920_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void __stdcall (*const b162920_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void (*const b162920_c190a90)(void) = (void *)shader_environment_texture_animation_evaluate;
static void __stdcall (*const b162920_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static void *(*const b162920_memset)(void *, int, unsigned int) = csmemset;
static uint32_t (*const b162920_c159070)(float a1) = FUN_00159070;
static void (*const b162920_c156510)(void *state) = rasterizer_set_pixel_shader;
static void (*const b162920_c15dc10)(void) = (void *)FUN_0015dc10;
static void (*const b162920_c17edd0)(void) = (void *)rasterizer_frame_statistics_count_static_vertices;

__attribute__((naked, noinline))
void FUN_00162920(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00162920_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3c8\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00162920_1:\n\t"
      "movw 0x3256bc, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00162920_2\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_00162920_2\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_00162920_2\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_00162920_2\n\t"
      "cmpw $7, %%ax\n\t"
      "je .LFUN_00162920_2\n\t"
      "cmpw $5, %%ax\n\t"
      "je .LFUN_00162920_2\n\t"
      "cmpw $8, %%ax\n\t"
      "jne .LFUN_00162920_29\n\t"
      ".LFUN_00162920_2:\n\t"
      "movb 0x3256cc, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00162920_29\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00162920_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3d5\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a18b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00162920_3:\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1906b0]\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .LFUN_00162920_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3e3\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a19cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00162920_4:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c190710]\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x28\n\t"
      "call *%[c178b40]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0x94(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0xc4(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "call *%[c155e80]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0xd8(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "call *%[c155e80]\n\t"
      "movl (%%eax), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0x108(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl $3\n\t"
      "call *%[c155e80]\n\t"
      "movl (%%eax), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "testb $1, 0x6c(%%esi)\n\t"
      "je .LFUN_00162920_5\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movswl -0x2(%%ebp), %%ecx\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl -0x6(%%ebp), %%edx\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "fdivr %%st(1), %%st(0)\n\t"
      "movswl -0xe(%%ebp), %%ecx\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movswl %%di, %%edx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl -0x1a(%%ebp), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "fdivrs -0x4(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "fdivr %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fdivrs -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fdivr %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "fdivrs -0x4(%%ebp)\n\t"
      "jmp .LFUN_00162920_6\n\t"
      ".LFUN_00162920_5:\n\t"
      "flds 0x2533c8\n\t"
      "movl $0x3f800000, -0x18(%%ebp)\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      "movl $0x3f800000, -0x24(%%ebp)\n\t"
      ".LFUN_00162920_6:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl 0x5a5e18, %%eax\n\t"
      "fmuls 0xb4(%%esi)\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x20(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0xb4(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "movl $0x3f800000, -0x44(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "fmuls 0xc8(%%esi)\n\t"
      "movl $0x3f800000, -0x30(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0xc8(%%esi)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0xf8(%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls 0xf8(%%esi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "call *%[c190a90]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x54\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0xf0\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $0x8421, 0x5a5b98\n\t"
      "movl $3, 0x5a5b94\n\t"
      "movswl 0x2a(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl %%ebx, %%eax\n\t"
      "movl $0xc00, %%edi\n\t"
      "je .LFUN_00162920_9\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00162920_8\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00162920_7\n\t"
      "pushl $1\n\t"
      "pushl $0x479\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1b10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00162920_12\n\t"
      ".LFUN_00162920_7:\n\t"
      "movl $0x18200000, 0x5a5ac0\n\t"
      "movl $0xc0, 0x5a5b28\n\t"
      "movl $0x380a1809, 0x5a5b48\n\t"
      "movl %%ebx, 0x5a5b2c\n\t"
      "jmp .LFUN_00162920_11\n\t"
      ".LFUN_00162920_8:\n\t"
      "movl $0x381a1819, 0x5a5ac0\n\t"
      "movl $0x380a1809, 0x5a5b48\n\t"
      "movl %%ebx, 0x5a5b2c\n\t"
      "jmp .LFUN_00162920_10\n\t"
      ".LFUN_00162920_9:\n\t"
      "movl $0x3a1a1a19, 0x5a5ac0\n\t"
      "movl $0x3a0a1a09, 0x5a5b48\n\t"
      "movl $0x181c0000, 0x5a5ac4\n\t"
      "movl $0xc0, 0x5a5b2c\n\t"
      ".LFUN_00162920_10:\n\t"
      "movl %%edi, 0x5a5b28\n\t"
      ".LFUN_00162920_11:\n\t"
      "movl %%edi, 0x5a5b74\n\t"
      ".LFUN_00162920_12:\n\t"
      "movswl 0xb0(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_00162920_15\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00162920_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00162920_13\n\t"
      "pushl $1\n\t"
      "pushl $0x48b\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1ad4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00162920_17\n\t"
      ".LFUN_00162920_13:\n\t"
      "movl $0x8204c20, 0x5a5b4c\n\t"
      "jmp .LFUN_00162920_16\n\t"
      ".LFUN_00162920_14:\n\t"
      "movl $0x80c0000, 0x5a5b4c\n\t"
      "jmp .LFUN_00162920_16\n\t"
      ".LFUN_00162920_15:\n\t"
      "movl $0x80c080c, 0x5a5b4c\n\t"
      ".LFUN_00162920_16:\n\t"
      "movl %%edi, 0x5a5b78\n\t"
      ".LFUN_00162920_17:\n\t"
      "movl $0x1c1b0000, 0x5a5ac8\n\t"
      "movl $0xc0, 0x5a5b30\n\t"
      "movswl 0xf4(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_00162920_20\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00162920_19\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00162920_18\n\t"
      "pushl $1\n\t"
      "pushl $0x4a0\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1ad4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00162920_22\n\t"
      ".LFUN_00162920_18:\n\t"
      "movl $0xc204b20, 0x5a5b50\n\t"
      "jmp .LFUN_00162920_21\n\t"
      ".LFUN_00162920_19:\n\t"
      "movl $0xc0b0000, 0x5a5b50\n\t"
      "jmp .LFUN_00162920_21\n\t"
      ".LFUN_00162920_20:\n\t"
      "movl $0xc0b0c0b, 0x5a5b50\n\t"
      ".LFUN_00162920_21:\n\t"
      "movl %%edi, 0x5a5b7c\n\t"
      ".LFUN_00162920_22:\n\t"
      "movswl 0x3256bc, %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "movl $0x1c00, 0x5a5ae4\n\t"
      "ja .LFUN_00162920_26\n\t"
      "movzbl 0x162f78(%%eax), %%edx\n\t"
      "jmp *.LFUN_00162920_jt(,%%edx,4)\n\t"
      ".LFUN_00162920_23:\n\t"
      "movl $0xc, 0x5a5ae0\n\t"
      "jmp .LFUN_00162920_27\n\t"
      ".LFUN_00162920_24:\n\t"
      "pushl $0x3ea8f5c3\n\t"
      "call *%[c159070]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5b6c\n\t"
      "movl $0xc110000, 0x5a5ae0\n\t"
      "jmp .LFUN_00162920_27\n\t"
      ".LFUN_00162920_25:\n\t"
      "movl $0x1c, 0x5a5ae0\n\t"
      "jmp .LFUN_00162920_27\n\t"
      ".LFUN_00162920_26:\n\t"
      "pushl $1\n\t"
      "pushl $0x4b6\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1a94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00162920_27:\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[c156510]\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c15dc10]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .LFUN_00162920_28\n\t"
      "movl 0x5a5468, %%eax\n\t"
      "movl 0x5a5464, %%edx\n\t"
      "pushl %%esi\n\t"
      "incl %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x5a5468\n\t"
      "movl %%edx, 0x5a5464\n\t"
      "call *%[c17edd0]\n\t"
      "movl 0x5a5460, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a5460\n\t"
      ".LFUN_00162920_28:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00162920_29:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00162920_jt:\n\t"
      ".long .LFUN_00162920_23\n\t"
      ".long .LFUN_00162920_24\n\t"
      ".long .LFUN_00162920_25\n\t"
      ".long .LFUN_00162920_26\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b162920_assert), [exitfn] "m"(b162920_exitfn), [c1906b0] "m"(b162920_c1906b0), [c190710] "m"(b162920_c190710), [c178b40] "m"(b162920_c178b40), [c155e80] "m"(b162920_c155e80), [c1e9410] "m"(b162920_c1e9410), [c190a90] "m"(b162920_c190a90), [c1eb8d0] "m"(b162920_c1eb8d0), [memset] "m"(b162920_memset), [c159070] "m"(b162920_c159070), [c156510] "m"(b162920_c156510), [c15dc10] "m"(b162920_c15dc10), [c17edd0] "m"(b162920_c17edd0)
      : "memory");
}
#else
#error "FUN_00162920: clang naked draft required"
#endif


/* FUN_00162f90 (0x162f90) — readable C lift (restored pre-naked). */
void FUN_00162f90(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x162fb9 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1253, 0);
  system_exit(0);
  FUN_0016f910(11);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1631c8 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ce] */
  /* test (char)eax, (char)eax -> je 0x1631c8 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);

  (void)eax;
}


/* FUN_001631d0 (0x1631d0) — readable C lift (restored pre-naked). */
void FUN_001631d0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x163205 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1311, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163580 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ce] */
  /* test (char)eax, (char)eax -> je 0x163580 */
  /* test esi, esi -> jl 0x16322c */
  /* relift: cmp esi, dword ptr [0x5a37e0] -> jl 0x16324c */
  display_assert((char *)0x002a1a58, (char *)0x002a18c0, 1317, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x163285 */
  display_assert((char *)0x0029e134, (char *)0x002a18c0, 1320, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x163297 */
  normalize3d((float *)0);
  /* relift: relift: fld dword ptr [0x253398] */
  /* relift: relift: fld dword ptr [0x253398] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18c61 */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20400 */
  /* mem[0x005a5b48] = 0x484a0000 */
  /* mem[0x005a5b74] = 0x20c0 */
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5ac4] = 0x4a204a20 */
  /* mem[0x005a5b2c] = 0x20500 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b78] = 0x10d00 */
  /* mem[0x005a5ac8] = 0x2c120c11 */
  /* mem[0x005a5b30] = ecx */
  /* mem[0x005a5b50] = 0xcd4b0809 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5acc] = 0xd0d1415 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ad0] = 0x1d1d151c */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b58] = 0xc091c09 */
  /* mem[0x005a5b84] = 0x110cd */
  /* mem[0x005a5ad4] = 0x1d1d0000 */
  /* mem[0x005a5b3c] = 0xd0 */
  /* mem[0x005a5b5c] = 0xc150d1d */
  /* mem[0x005a5b88] = 0x10cd */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = 0x1d330d00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_00163590 (0x163590) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b163590_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b163590_exitfn)(int) = system_exit;
static float (*const b163590_c7a750)(float *color) = real_rgb_color_brightness;
static void (*const b163590_c1631d0)(void) = (void *)FUN_001631d0;
static void __stdcall (*const b163590_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static void (*const b163590_c155cf0)(int stage, int bitmap_tag_index, int frame_index) = rasterizer_set_texture_direct;
static void __stdcall (*const b163590_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void *(*const b163590_memset)(void *, int, unsigned int) = csmemset;
static void (*const b163590_c156510)(void *state) = rasterizer_set_pixel_shader;

__attribute__((naked, noinline))
void FUN_00163590(int object_handle)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00163590_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5c0\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00163590_1:\n\t"
      "cmpw $0, 0x3256bc\n\t"
      "jne .LFUN_00163590_7\n\t"
      "movb 0x3256ce, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00163590_7\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LFUN_00163590_2\n\t"
      "cmpl 0x5a37e0, %%edi\n\t"
      "jl .LFUN_00163590_3\n\t"
      ".LFUN_00163590_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x5c6\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1a58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00163590_3:\n\t"
      "movl %%edi, %%esi\n\t"
      "imull $0x38, %%esi, %%esi\n\t"
      "addl $0x5a37e4, %%esi\n\t"
      "flds 0x34(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00163590_4\n\t"
      "pushl $1\n\t"
      "pushl $0x5c9\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a1b40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00163590_4:\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl $0xbf800000, 0x1c(%%eax)\n\t"
      "je .LFUN_00163590_6\n\t"
      "cmpl $-1, 0x70(%%eax)\n\t"
      "jne .LFUN_00163590_5\n\t"
      "cmpl $-1, 0x88(%%eax)\n\t"
      "je .LFUN_00163590_6\n\t"
      ".LFUN_00163590_5:\n\t"
      "addl $0x28, %%esi\n\t"
      "pushl %%esi\n\t"
      "movw $1, 0x325170\n\t"
      "call *%[c7a750]\n\t"
      "fstps 0x47dca8\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1631d0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00163590_6:\n\t"
      "leal 0x28(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw $0, 0x325170\n\t"
      "call *%[c7a750]\n\t"
      "fstps 0x47dca8\n\t"
      "movl (%%esi), %%ecx\n\t"
      "flds 0x24(%%ecx)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "fdivrs 0x2533c8\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "pushl $5\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-0x51\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x3c(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0x3f800000, -0x34(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movl $0x3f800000, -0x24(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movl 0x476204, %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c155cf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $4\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $4\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $4\n\t"
      "movl $0xc, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $0xff, %%eax\n\t"
      "movl $0x18c41, 0x5a5b98\n\t"
      "movl $0x11006, 0x5a5b94\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "movl $0x4b204b20, 0x5a5ac0\n\t"
      "movl $0x20400, 0x5a5b28\n\t"
      "movl %%eax, 0x5a5aec\n\t"
      "movl $0xc00, %%ecx\n\t"
      "movl $0xd5, %%eax\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl $0x484a0000, 0x5a5b48\n\t"
      "movl $0x20c0, 0x5a5b74\n\t"
      "movl $0x4a204a20, 0x5a5ac4\n\t"
      "movl $0x20500, 0x5a5b2c\n\t"
      "movl $0x48cc8a40, 0x5a5b4c\n\t"
      "movl $0x10d00, 0x5a5b78\n\t"
      "movl $0x2c120c11, 0x5a5ac8\n\t"
      "movl %%ecx, 0x5a5b30\n\t"
      "movl $0xcd4b0809, 0x5a5b50\n\t"
      "movl $0x20d0, 0x5a5b7c\n\t"
      "movl $0xd0d1415, 0x5a5acc\n\t"
      "movl %%eax, 0x5a5b34\n\t"
      "movl $0x2c020c01, 0x5a5b54\n\t"
      "movl %%ecx, 0x5a5b80\n\t"
      "movl $0x1d1d151c, 0x5a5ad0\n\t"
      "movl %%eax, 0x5a5b38\n\t"
      "movl $0xc091c09, 0x5a5b58\n\t"
      "movl $0x110cd, 0x5a5b84\n\t"
      "movl $0x1d1d0000, 0x5a5ad4\n\t"
      "movl $0xd0, 0x5a5b3c\n\t"
      "movl $0xc150d1d, 0x5a5b5c\n\t"
      "movl $0x10cd, 0x5a5b88\n\t"
      "movl $0xc0f0000, 0x5a5ae0\n\t"
      "movl $0x1d200d00, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_00163590_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b163590_assert), [exitfn] "m"(b163590_exitfn), [c7a750] "m"(b163590_c7a750), [c1631d0] "m"(b163590_c1631d0), [c1eb8d0] "m"(b163590_c1eb8d0), [c155cf0] "m"(b163590_c155cf0), [c1e9410] "m"(b163590_c1e9410), [memset] "m"(b163590_memset), [c156510] "m"(b163590_c156510)
      : "memory");
}
#else
#error "FUN_00163590: clang naked draft required"
#endif


/* FUN_00163910 (0x163910) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b163910_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b163910_exitfn)(int) = system_exit;
static void * (*const b163910_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b163910_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void (*const b163910_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void __stdcall (*const b163910_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void (*const b163910_c190a90)(void) = (void *)shader_environment_texture_animation_evaluate;
static void __stdcall (*const b163910_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static uint32_t (*const b163910_c159070)(float a1) = FUN_00159070;
static unsigned int (*const b163910_cd1dd0)(float *color) = FUN_000d1dd0;
static void (*const b163910_c156510)(void *state) = rasterizer_set_pixel_shader;
static void (*const b163910_c15dc10)(void) = (void *)FUN_0015dc10;
static void (*const b163910_c17edd0)(void) = (void *)rasterizer_frame_statistics_count_static_vertices;

__attribute__((naked, noinline))
void FUN_00163910(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00163910_1\n\t"
      "pushl $1\n\t"
      "pushl $0x660\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00163910_1:\n\t"
      "cmpw $0, 0x3256bc\n\t"
      "jne .LFUN_00163910_9\n\t"
      "movb 0x3256ce, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00163910_9\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00163910_2\n\t"
      "pushl $1\n\t"
      "pushl $0x667\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a18b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00163910_2:\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "flds 0x290(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00163910_8\n\t"
      "flds 0x47dca8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00163910_8\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00163910_3\n\t"
      "pushl $1\n\t"
      "pushl $0x66d\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a19cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00163910_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x325170, %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%edi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x15\n\t"
      "call *%[c178b40]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x134(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x20, %%esp\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0x138(%%esi), %%ecx\n\t"
      "movl 0x13c(%%esi), %%edx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x5a5e18, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "movl $0x3f800000, -0x24(%%ebp)\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[c190a90]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x54\n\t"
      "call *%[c1eb8d0]\n\t"
      "flds 0x47dca8\n\t"
      "fmuls 0x290(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c159070]\n\t"
      "flds 0x47dca8\n\t"
      "movl %%eax, 0x5a5af0\n\t"
      "fmuls 0x290(%%esi)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c159070]\n\t"
      "leal 0x2a8(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x5a5b10\n\t"
      "call *%[cd1dd0]\n\t"
      "movl %%eax, 0x5a5af4\n\t"
      "leal 0x2b4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cd1dd0]\n\t"
      "movl %%eax, 0x5a5b14\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00163910_4\n\t"
      "movl $0x14a0000, 0x5a5b48\n\t"
      "movl $0x1cc8a40, 0x5a5b4c\n\t"
      "movl $0x20d9, 0x5a5b7c\n\t"
      "jmp .LFUN_00163910_5\n\t"
      ".LFUN_00163910_4:\n\t"
      "movl $0x484a0000, 0x5a5b48\n\t"
      "movl $0x48cc8a40, 0x5a5b4c\n\t"
      "movl $0x20d0, 0x5a5b7c\n\t"
      ".LFUN_00163910_5:\n\t"
      "movb 0x27c(%%esi), %%al\n\t"
      "andb $1, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x10000, %%eax\n\t"
      "addl $0x110cd, %%eax\n\t"
      "movl %%eax, 0x5a5b84\n\t"
      "testb $2, 0x27c(%%esi)\n\t"
      "je .LFUN_00163910_6\n\t"
      "movl $0x1d1d0000, %%ecx\n\t"
      "movl $0x11008, 0x5a5b94\n\t"
      "movl %%ecx, 0x5a5ad8\n\t"
      "movl $0xd0, %%eax\n\t"
      "movl %%ecx, 0x5a5adc\n\t"
      "jmp .LFUN_00163910_7\n\t"
      ".LFUN_00163910_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x11006, 0x5a5b94\n\t"
      "movl %%eax, 0x5a5ad8\n\t"
      "movl %%eax, 0x5a5adc\n\t"
      ".LFUN_00163910_7:\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%eax, 0x5a5b40\n\t"
      "movl %%eax, 0x5a5b44\n\t"
      "call *%[c156510]\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c15dc10]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .LFUN_00163910_8\n\t"
      "movl 0x5a5474, %%eax\n\t"
      "movl 0x5a5470, %%edx\n\t"
      "pushl %%esi\n\t"
      "incl %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x5a5474\n\t"
      "movl %%edx, 0x5a5470\n\t"
      "call *%[c17edd0]\n\t"
      "movl 0x5a546c, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a546c\n\t"
      ".LFUN_00163910_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00163910_9:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b163910_assert), [exitfn] "m"(b163910_exitfn), [c1906b0] "m"(b163910_c1906b0), [c178b40] "m"(b163910_c178b40), [c155e80] "m"(b163910_c155e80), [c1e9410] "m"(b163910_c1e9410), [c190a90] "m"(b163910_c190a90), [c1eb8d0] "m"(b163910_c1eb8d0), [c159070] "m"(b163910_c159070), [cd1dd0] "m"(b163910_cd1dd0), [c156510] "m"(b163910_c156510), [c15dc10] "m"(b163910_c15dc10), [c17edd0] "m"(b163910_c17edd0)
      : "memory");
}
#else
#error "FUN_00163910: clang naked draft required"
#endif


/* FUN_00163c40 (0x163c40) — readable C lift (restored pre-naked). */
void FUN_00163c40(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> jne 0x163c69 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1785, 0);
  system_exit(0);
  FUN_0016f910(12);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163fd2 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x163fd2 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x163fd2 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18c21 */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ae8] = 0x800000ff */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20400 */
  /* mem[0x005a5b48] = 0x484a0911 */
  /* mem[0x005a5b74] = 0x30c9 */
  /* mem[0x005a5aec] = 0xff */
  /* mem[0x005a5ac4] = 0x4a204a20 */
  /* mem[0x005a5b2c] = 0x20500 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b78] = 0x10d00 */
  /* mem[0x005a5ac8] = 0x2c120c11 */
  /* mem[0x005a5b30] = ecx */
  /* mem[0x005a5b50] = 0xcd4b0809 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5acc] = 0xd0d1415 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ad0] = 0x1d1d151c */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b58] = 0xc091c09 */
  /* mem[0x005a5b84] = 0x110cd */
  /* mem[0x005a5ad4] = 0x1d1d0000 */
  /* mem[0x005a5b3c] = 0xd0 */
  /* mem[0x005a5b5c] = 0xc150d1d */
  /* mem[0x005a5b88] = 0x10cd */
  /* mem[0x005a5b6c] = 0x80000000 */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = 0x1d110d00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
}


/* FUN_00163fe0 (0x163fe0) — readable C lift. */
void FUN_00163fe0(void *bitmap)
{
  int v;

  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a18c0, 0x752, 1);
    system_exit(-1);
  }
  if (*(short *)0x3256bc != 0)
    return;
  if (!*(unsigned char *)0x3256cf)
    return;
  if (!bitmap) {
    *(unsigned char *)0x47dca4 = 1;
    return;
  }
  rasterizer_set_texture_bitmap_data(1, bitmap);
  D3DDevice_SetTextureStageState(1, 0xa, 3);
  D3DDevice_SetTextureStageState(1, 0xb, 3);
  v = (*(unsigned char *)0x3256ed != 0) + 1;
  D3DDevice_SetTextureStageState(1, 0xd, v);
  v = (*(unsigned char *)0x3256ed != 0) + 1;
  D3DDevice_SetTextureStageState(1, 0xe, v);
  v = (*(unsigned char *)0x3256ed != 0) + 1;
  D3DDevice_SetTextureStageState(1, 0xf, v);
  *(unsigned char *)0x47dca4 = 0;
}
/* FUN_001640d0 (0x1640d0) — readable C lift (restored pre-naked). */
void FUN_001640d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x1640ff */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1915, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1643d5 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x1643d5 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x1643d5 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dca4] */
  /* test (char)eax, (char)eax -> jne 0x1643d5 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 1924, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1643d2 */
  /* relift: test byte ptr [esi + 0x27c], 4 -> je 0x1643d2 */
  FUN_00178b40(21, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  FUN_00159070(0.0f);
  /* mem[0x005a5af0] = eax */
  FUN_00159070(0.0f);
  /* mem[0x005a5b10] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5af4] = eax */
  FUN_000d1dd0((float *)(uintptr_t)eax);
  /* mem[0x005a5b14] = eax */
  /* relift: test byte ptr [esi + 0x28], 2 -> je 0x1642eb */
  /* mem[0x005a5b48] = 0x14a0911 */
  /* mem[0x005a5b4c] = 0x1cc8a40 */
  /* mem[0x005a5b7c] = 0x20d9 */
  /* mem[0x005a5b48] = 0x484a0911 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5b84] = ecx */
  /* relift: test byte ptr [esi + 0x27c], 2 -> je 0x164353 */
  /* mem[0x005a5b94] = 0x11008 */
  /* mem[0x005a5ad8] = ecx */
  /* mem[0x005a5adc] = ecx */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ad8] = eax */
  /* mem[0x005a5adc] = eax */
  /* mem[0x005a5b40] = eax */
  /* mem[0x005a5b44] = eax */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x1643d2 */
  /* mem[0x005a5480] = eax */
  /* mem[0x005a547c] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5478] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_001643e0 (0x1643e0) — readable C lift. */
void FUN_001643e0(void)
{
  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x815, 1);
    system_exit(-1);
  }
  FUN_0016f910(0xd);
  if (*(short *)0x3256bc != 0)
    return;
  if (!*(unsigned char *)0x3256d0)
    return;
  if (!*(unsigned char *)0x3256d2)
    return;
  if (*(short *)0x3256b0 != 0)
    return;

  D3DDevice_SetRenderState_CullMode(0x901);
  D3DDevice_SetRenderState_Simple(0x40358, 0x1000000);
  *(unsigned int *)0x1fb7a4 = 0x1000000;
  D3DDevice_SetRenderState_Simple(0x40304, 1);
  *(unsigned int *)0x1fb784 = 1;
  D3DDevice_SetRenderState_Simple(0x40344, 0x304);
  *(unsigned int *)0x1fb790 = 0x304;
  D3DDevice_SetRenderState_Simple(0x40348, 0);
  *(unsigned int *)0x1fb794 = 0;
  D3DDevice_SetRenderState_Simple(0x40350, 0x8006);
  *(unsigned int *)0x1fb7c0 = 0x8006;
  D3DDevice_SetRenderState_Simple(0x40300, 0);
  *(unsigned int *)0x1fb788 = 0;
  D3DDevice_SetRenderState_ZEnable(1);
  D3DDevice_SetRenderState_Simple(0x40354, 0x202);
  *(unsigned int *)0x1fb77c = 0x202;
  D3DDevice_SetRenderState_Simple(0x4035c, 0);
  *(unsigned int *)0x1fb798 = 0;
  D3DDevice_SetRenderState_ZBias(0);

  csmemset((void *)0x5a5ac0, 0, 0xf0);
  *(int *)0x5a5b98 = 1;
  *(int *)0x5a5b94 = 2;
  *(int *)0x5a5ae8 = 0x80b050;
  *(int *)0x5a5b48 = 0x8010000;
  *(int *)0x5a5b74 = 0x20c0;
  *(int *)0x5a5ac4 = 0x2c120c20;
  *(int *)0x5a5b2c = 0xc00;
  *(int *)0x5a5ae0 = 0;
  *(int *)0x5a5ae4 = 0x1c00;
  rasterizer_set_pixel_shader((void *)0x5a5ac0);
}

/* FUN_00164590 (0x164590) — readable C lift. */
void FUN_00164590(void *bitmap)
{
  int v;

  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a18c0, 0x848, 1);
    system_exit(-1);
  }
  if (*(short *)0x3256bc != 0)
    return;
  if (!*(unsigned char *)0x3256d0)
    return;
  if (!*(unsigned char *)0x3256d2)
    return;
  if (*(short *)0x3256b0 != 0)
    return;
  if (!bitmap) {
    *(unsigned char *)0x47dca4 = 1;
    return;
  }
  rasterizer_set_texture_bitmap_data(0, bitmap);
  D3DDevice_SetTextureStageState(0, 0xa, 3);
  D3DDevice_SetTextureStageState(0, 0xb, 3);
  v = (*(unsigned char *)0x3256ed != 0) + 1;
  D3DDevice_SetTextureStageState(0, 0xd, v);
  v = (*(unsigned char *)0x3256ed != 0) + 1;
  D3DDevice_SetTextureStageState(0, 0xe, v);
  v = (*(unsigned char *)0x3256ed != 0) + 1;
  D3DDevice_SetTextureStageState(0, 0xf, v);
  *(unsigned char *)0x47dca4 = 0;
}
/* FUN_00164690 (0x164690) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b164690_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b164690_exitfn)(int) = system_exit;
static void * (*const b164690_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b164690_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void __stdcall (*const b164690_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void (*const b164690_c155cf0)(int stage, int bitmap_tag_index, int frame_index) = rasterizer_set_texture_direct;
static void (*const b164690_c1584f0)(int stage, int target, int max_mipmap) = FUN_001584f0;
static void __stdcall (*const b164690_c1e96d0)(uint32_t mode) = (void *)D3DDevice_SetRenderState_CullMode;
static void (*const b164690_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b164690_c1ea290)(uint32_t enable) = (void *)D3DDevice_SetRenderState_ZEnable;
static void __stdcall (*const b164690_c1e98e0)(uint32_t value) = (void *)D3DDevice_SetRenderState_ZBias;
static void (*const b164690_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void (*const b164690_c190a90)(void) = (void *)shader_environment_texture_animation_evaluate;
static void __stdcall (*const b164690_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static void *(*const b164690_memset)(void *, int, unsigned int) = csmemset;
static unsigned int (*const b164690_cd1dd0)(float *color) = FUN_000d1dd0;
static uint32_t (*const b164690_c99530)(float alpha, float *color) = real_a_rgb_color_to_pixel32;
static void (*const b164690_c156510)(void *state) = rasterizer_set_pixel_shader;
static void (*const b164690_c15dc10)(void) = (void *)FUN_0015dc10;
static void (*const b164690_c17edd0)(void) = (void *)rasterizer_frame_statistics_count_static_vertices;

__attribute__((naked, noinline))
void FUN_00164690(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00164690_1\n\t"
      "pushl $1\n\t"
      "pushl $0x8df\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00164690_1:\n\t"
      "cmpw $0, 0x3256bc\n\t"
      "jne .LFUN_00164690_17\n\t"
      "movb 0x3256d1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00164690_17\n\t"
      "movb 0x5a5bc4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00164690_17\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .LFUN_00164690_17\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00164690_2\n\t"
      "pushl $1\n\t"
      "pushl $0x8e8\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a18b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00164690_2:\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x2d0(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00164690_16\n\t"
      "flds 0x2f4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00164690_3\n\t"
      "flds 0x2f8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00164690_16\n\t"
      ".LFUN_00164690_3:\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00164690_4\n\t"
      "pushl $1\n\t"
      "pushl $0x8ef\n\t"
      "pushl $0x2a18c0\n\t"
      "pushl $0x2a19cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00164690_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x134(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0x476204, %%edx\n\t"
      "movl 0x1c(%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c155cf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xc, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0x476204, %%ecx\n\t"
      "movl 0x1c(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl $2\n\t"
      "call *%[c155cf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xc, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $3\n\t"
      "call *%[c1584f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0x901\n\t"
      "call *%[c1e96d0]\n\t"
      "movl $0x10101, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $1, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl $0x10101, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x304, %%edx\n\t"
      "movl $0x40344, %%ecx\n\t"
      "movl $1, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "movl $1, %%edx\n\t"
      "movl $0x40348, %%ecx\n\t"
      "movl $0x304, 0x1fb790\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x8006, %%edx\n\t"
      "movl $0x40350, %%ecx\n\t"
      "movl $1, 0x1fb794\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl $0x8006, 0x1fb7c0\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $1\n\t"
      "movl $0, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "movl $0x202, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "movl $0x202, 0x1fb77c\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $0\n\t"
      "movl $0, 0x1fb798\n\t"
      "call *%[c1e98e0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0x33\n\t"
      "call *%[c178b40]\n\t"
      "movl 0x138(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl 0x13c(%%esi), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x5a5e18, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl $0x43a00000, -0x34(%%ebp)\n\t"
      "movl $0x43700000, -0x30(%%ebp)\n\t"
      "movl $0x3f800000, -0x2c(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0x3f800000, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "call *%[c190a90]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x54\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $0x8c61, 0x5a5b98\n\t"
      "movl $0x11005, 0x5a5b94\n\t"
      "movl 0x134(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00164690_14\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00164690_5\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00164690_7\n\t"
      ".LFUN_00164690_5:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00164690_6\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00164690_7\n\t"
      ".LFUN_00164690_6:\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00164690_7:\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00164690_8\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00164690_10\n\t"
      ".LFUN_00164690_8:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00164690_9\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00164690_10\n\t"
      ".LFUN_00164690_9:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00164690_10:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00164690_11\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00164690_13\n\t"
      ".LFUN_00164690_11:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00164690_12\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00164690_13\n\t"
      ".LFUN_00164690_12:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_00164690_13:\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "movl $0x4a410b0b, 0x5a5b48\n\t"
      "jmp .LFUN_00164690_15\n\t"
      ".LFUN_00164690_14:\n\t"
      "movl $0x49480b0b, 0x5a5b48\n\t"
      ".LFUN_00164690_15:\n\t"
      "movl $0xc0c0d0d, %%eax\n\t"
      "leal 0x2a8(%%esi), %%edx\n\t"
      "movl $0x20cd, 0x5a5b74\n\t"
      "movl %%eax, 0x5a5b4c\n\t"
      "movl $0xcd, 0x5a5b78\n\t"
      "movl %%eax, 0x5a5b50\n\t"
      "movl $0xd, 0x5a5b7c\n\t"
      "movl 0x2f4(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c99530]\n\t"
      "leal 0x2b4(%%esi), %%ecx\n\t"
      "movl %%eax, 0x5a5af4\n\t"
      "movl 0x2f8(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, 0x5a5b14\n\t"
      "movl $0xc00, %%eax\n\t"
      "movl %%eax, 0x5a5b34\n\t"
      "movl %%eax, 0x5a5b80\n\t"
      "movl %%eax, 0x5a5b84\n\t"
      "movl $0x2c120c11, 0x5a5acc\n\t"
      "movl $0x2c020c01, 0x5a5b54\n\t"
      "movl $0x2c0d0c0b, 0x5a5b58\n\t"
      "movl $0xc0f0000, 0x5a5ae0\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "andb $2, %%al\n\t"
      "negb %%al\n\t"
      "pushl $0x5a5ac0\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xffffffe8, %%eax\n\t"
      "addl $0x20, %%eax\n\t"
      "orl $0x1c00, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "movl %%eax, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c15dc10]\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .LFUN_00164690_16\n\t"
      "movl 0x5a5498, %%eax\n\t"
      "movl 0x5a5494, %%edx\n\t"
      "pushl %%esi\n\t"
      "incl %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x5a5498\n\t"
      "movl %%edx, 0x5a5494\n\t"
      "call *%[c17edd0]\n\t"
      "movl 0x5a5490, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a5490\n\t"
      ".LFUN_00164690_16:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00164690_17:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b164690_assert), [exitfn] "m"(b164690_exitfn), [c1906b0] "m"(b164690_c1906b0), [c155e80] "m"(b164690_c155e80), [c1e9410] "m"(b164690_c1e9410), [c155cf0] "m"(b164690_c155cf0), [c1584f0] "m"(b164690_c1584f0), [c1e96d0] "m"(b164690_c1e96d0), [c1e9350] "m"(b164690_c1e9350), [c1ea290] "m"(b164690_c1ea290), [c1e98e0] "m"(b164690_c1e98e0), [c178b40] "m"(b164690_c178b40), [c190a90] "m"(b164690_c190a90), [c1eb8d0] "m"(b164690_c1eb8d0), [memset] "m"(b164690_memset), [cd1dd0] "m"(b164690_cd1dd0), [c99530] "m"(b164690_c99530), [c156510] "m"(b164690_c156510), [c15dc10] "m"(b164690_c15dc10), [c17edd0] "m"(b164690_c17edd0)
      : "memory");
}
#else
#error "FUN_00164690: clang naked draft required"
#endif


/* FUN_00164cf0 (0x164cf0) — readable C lift (restored pre-naked). */
void FUN_00164cf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x164d1f */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2462, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x165418 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d2] */
  /* test (char)eax, (char)eax -> je 0x165418 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2470, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x164d83 */
  /* cmp (int16_t)edi, 2 -> jne 0x164d9c */
  /* relift: test byte ptr [esi + 0x28], 2 -> je 0x164d8e */
  /* relift: cmp dword ptr [esi + 0x134], -1 -> jne 0x164d9c */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x164dc6 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x165415 */
  /* relift: cmp dword ptr [esi + 0x330], -1 -> je 0x165415 */
  /* test eax, eax -> jne 0x164dfa */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 2495, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x164e05 */
  /* cmp (int16_t)edi, 3 -> jl 0x164e25 */
  display_assert((char *)0x002a1b78, (char *)0x002a18c0, 2496, 0);
  system_exit(0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_00178b40(42, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  display_assert((char *)0x002a1b50, (char *)0x002a18c0, 2592, 0);
  system_exit(0);
  /* mem[0x005a5b98] = 0x18c61 */
  /* mem[0x005a5b98] = 0x62e21 */
  /* mem[0x005a5ba0] = 0 */
  /* mem[0x005a5b9c] = 0x111 */
  /* mem[0x005a5b94] = 0x11005 */
  /* cmp (int16_t)edi, 2 -> je 0x1651f5 */
  /* relift: cmp dword ptr [esi + 0x134], -1 -> je 0x1651f5 */
  /* mem[0x005a5b48] = 0x49480b0b */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* test (char)eax, 0x41 -> jne 0x165237 */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* test (char)eax, 0x41 -> jne 0x16527c */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* test (char)eax, 0x41 -> jne 0x1652c1 */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5b48] = 0x4a410b0b */
  /* mem[0x005a5b4c] = eax */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5b74] = 0x20cd */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b7c] = 0xd */
  real_a_rgb_color_to_pixel32(0.0f, (float *)(uintptr_t)eax);
  /* mem[0x005a5af4] = eax */
  real_a_rgb_color_to_pixel32(0.0f, (float *)(uintptr_t)edx);
  /* mem[0x005a5b14] = eax */
  /* mem[0x005a5acc] = 0x2c120c11 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5b58] = 0x2c0d0c0b */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = ecx */
  rasterizer_set_pixel_shader((void *)0);
  /* relift: cmp word ptr [0x3256b0], 0 -> je 0x1653bb */
  /* cmp (int16_t)edi, 2 -> jne 0x1653bb */
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x165415 */
  /* mem[0x005a5498] = eax */
  /* mem[0x005a5494] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5490] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00165420 (0x165420) — readable C lift (restored pre-naked). */
void FUN_00165420(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, ebx -> jne 0x165452 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2699, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x3256d3], (char)ebx -> je 0x16576f */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2706, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x24], 3 -> jne 0x1654ae */
  display_assert((char *)0x002a1c44, (char *)0x002a18c0, 2707, 0);
  system_exit(0);
  ((void(*)(void))shader_type_is_valid_for_environment)();
  /* test (char)eax, (char)eax -> jne 0x1654e1 */
  display_assert((char *)0x002a1c0c, (char *)0x002a18c0, 2708, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0x165508 */
  display_assert((char *)0x002a1774, (char *)0x002a18c0, 2709, 0);
  system_exit(0);
  shader_is_decal((void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x165547 */
  /* mem[0x0047dc88] = ecx */
  rasterizer_transparent_geometry_group_new();
  /* cmp esi, ebx -> je 0x16574f */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* cmp eax, ebx -> jne 0x165612 */
  rasterizer_memory_pool_copy(0, 116);
  /* relift: cmp word ptr [edi + 0x24], 7 -> jne 0x1656e3 */
  FUN_001792C0(0);
  /* relift: cmp word ptr [edi + 0x24], 7 -> jne 0x1656e3 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)ecx, 8 -> je 0x1656e3 */
  /* relift: cmp dword ptr [ebp - 4], ebx -> je 0x1656c1 */
  display_assert((char *)0x002a1bcc, (char *)0x002a18c0, 2782, 0);
  system_exit(0);
  rasterizer_transparent_geometry_group_draw((void *)(uintptr_t)esi, 0);
  FUN_001845b0((void *)(uintptr_t)esi, 0);
  /* relift: cmp dword ptr [ebp - 4], ebx -> je 0x1656f2 */
  rasterizer_transparent_geometry_group_draw((void *)(uintptr_t)esi, 0);
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16576d */
  /* mem[0x005a54a8] = esi */
  /* mem[0x005a54a0] = edx */
  /* mem[0x005a54a4] = eax */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a549c] = ecx */
  /* relift: cmp byte ptr [0x47dcac], (char)ebx -> jne 0x16576d */
  error(0, (char *)0x002a1744);
  /* relift: relift: mov byte ptr [0x47dcac], 1 */
  /* cmp esi, 0x52 -> jge 0x16579b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1657a9 */
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x1657be */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x1657ca */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x1657d6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1657e2 */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x1657ee */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x1657fa */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x165806 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x165812 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16581e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16582a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x165836 */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x165845 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x165854 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x165863 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x165872 */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x165881 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x165890 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x16589f */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x1658ae */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x1658bd */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x1658cc */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x1658db */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x1658ea */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x1658f9 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x165908 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x165917 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x165925 */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x16593c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x165949 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x165956 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x165963 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x165970 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}



/* FUN_00165980 (0x165980) — readable C lift. */
int FUN_00165980(int a, int b, int c, int d, int e)
{
  D3DDevice_Clear((uint32_t)a, (void *)(unsigned)b, (uint32_t)c, (uint32_t)d, *(float *)&e, 0);
  return 0;
}



/* FUN_001659a0 (0x1659a0) — readable C lift. */
char FUN_001659a0(void)
{
  void *p;

  p = debug_malloc(0x5000, 0, (const char *)0x2a1cc8, 0xf8);
  *(void **)0x47df00 = p;
  *(unsigned int *)0x47df04 = 0;
  if (p)
    return 1;
  error(2, (const char *)0x2a1c70);
  return 0;
}


/* FUN_001659f0 (0x1659f0) — readable C lift. */
void FUN_001659f0(void)
{
  *(unsigned int *)0x47df04 = 0;
}

/* FUN_00165a00 (0x165a00) — readable C lift (ret thunk). */
void FUN_00165a00(void)
{
}


/* FUN_00165a10 (0x165a10) — readable C lift. */
void FUN_00165a10(void)
{
  void *p;

  p = *(void **)0x47df00;
  if (!p)
    return;
  debug_free(p, (const char *)0x2a1cc8, 0x117);
}



/* FUN_00165cb0 (0x165cb0) — readable C lift from XBE leaf. */
void FUN_00165cb0(void *shader, int unused, int a2, int a3, int a4, unsigned short *info)
{
  int perm;

  (void)unused;
  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a1cc8, 0x1a7, 1);
    system_exit(-1);
  }
  if (*(short *)0x3256bc != 0)
    return;
  if (!*(unsigned char *)0x3256d4)
    return;
  if (!shader) {
    display_assert((char *)0x2a18b8, (char *)0x2a1cc8, 0x1ae, 1);
    system_exit(-1);
  }
  FUN_001906b0(shader, 3);
  if (!info) {
    display_assert((char *)0x2a19cc, (char *)0x2a1cc8, 0x1b3, 1);
    system_exit(-1);
  }
  perm = shader_get_vertex_shader_permutation(shader);
  FUN_00178b40(6, (int)info[0], perm);
  ((void (*)(int, int, int, unsigned short *))FUN_0015dc10)(a2, a3, a4, info);
  if (*(short *)0x3256ba == 2) {
    int nverts;
    *(int *)0x5a54b4 = *(int *)0x5a54b4 + 1;
    *(int *)0x5a54b0 = *(int *)0x5a54b0 + a4;
    nverts = ((int (*)(int, int, int))rasterizer_frame_statistics_count_static_vertices)(a2, a3, a4);
    *(int *)0x5a54ac = *(int *)0x5a54ac + nverts;
  }
}



/* FUN_00165dd0 (0x165dd0) — readable C lift. */
void FUN_00165dd0(void)
{
  FUN_0016fa40(0x11);
}

/* FUN_00165de0 (0x165de0) — readable C lift. */
void FUN_00165de0(short index, float scale, float *out)
{
  float *row;

  row = (float *)(0x47ddfc + (int)index * 0x4c);
  if (index < 0 || index >= 4) {
    display_assert((const char *)0x2a1d18, (const char *)0x2a1cc8, 0x1e4, true);
    system_exit(-1);
  }
  if (!out) {
    display_assert((const char *)0x2a1d0c, (const char *)0x2a1cc8, 0x1e5, true);
    system_exit(-1);
  }
  out[0] = row[2] * row[0] * scale;
  out[1] = row[1] * row[2] * scale;
  out[2] = 0.0f;
}



/* FUN_00165ea0 (0x165ea0) — readable C lift. */
void FUN_00165ea0(int a0, short a1, int a2, int a3, int a4, int a5, int a6)
{
  int n;
  char *slot;
  int *obj;

  if (!*(unsigned char *)0x3256d5)
    return;
  if (*(short *)0x3256bc != 0)
    return;
  n = *(int *)0x47df04;
  if (n >= 0x80) {
    if (!*(unsigned char *)0x47df44) {
      error(2, (const char *)0x2a1d48, 0x80);
      *(unsigned char *)0x47df44 = 1;
    }
    return;
  }
  slot = (char *)(*(int *)0x47df00) + n * 0xa0;
  *(int *)0x47df04 = n + 1;
  *(int *)(slot + 0xc) = a0;
  *(int *)(slot + 0x48) = a2;
  *(short *)(slot + 0x10) = a1;
  *(int *)(slot + 0x44) = a3;
  *(int *)(slot + 0x58) = a5;
  *(int *)(slot + 0x50) = a4;
  *(int *)(slot + 0x4c) = 0;
  *(int *)(slot + 0x54) = a6;
  obj = *(int **)0x47df34;
  *(int *)(slot + 0x3c) = *(int *)((char *)obj + 0xc4);
  *(int *)(slot + 0x40) = *(int *)((char *)obj + 0xc8);
  if (!*(unsigned char *)0x47df38) {
    *(int *)0x47dcb4 = rasterizer_memory_pool_copy(
        *(int *)((char *)obj + 8), (int)*(short *)((char *)obj + 0xc) * 0x34);
    obj = *(int **)0x47df34;
    *(short *)0x47dcb0 = *(short *)((char *)obj + 0xc);
    *(unsigned char *)0x47df38 = 1;
  }
  *(int *)(slot + 0x60) = *(int *)0x47dcb4;
  *(short *)(slot + 0x64) = *(short *)0x47dcb0;
  *(int *)(slot + 0x68) = *(int *)0x47df3c;
  *(int *)(slot + 0x6c) = *(int *)0x47df40;
}
/* FUN_00165fc0 (0x165fc0) — readable C lift. */
void FUN_00165fc0(void)
{
  *(unsigned int *)0x47df34 = 0;
}

/* FUN_00165fd0 (0x165fd0) — readable C lift. */
void FUN_00165fd0(float *out, float f0, int a, int b, int c)
{
  out[0] = f0;
  *(int *)(out + 1) = a;
  *(int *)(out + 2) = b;
  *(int *)(out + 3) = c;
}

/* FUN_00166010 (0x166010) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void (*const b166010_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b166010_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00166010(void *obj, int *out, int addend)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movw 0x5a5bc2, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00166010_9\n\t"
      "cmpw $4, %%ax\n\t"
      "jge .LFUN_00166010_9\n\t"
      "pushl %%esi\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl 0x325668, %%eax\n\t"
      "cmpl 0x47df10(,%%esi,8), %%eax\n\t"
      "movb $0, 0x47df08(%%esi)\n\t"
      "jne .LFUN_00166010_1\n\t"
      "movl 0x32566c, %%ecx\n\t"
      "cmpl 0x47df14(,%%esi,8), %%ecx\n\t"
      "je .LFUN_00166010_6\n\t"
      ".LFUN_00166010_1:\n\t"
      "flds 0x5a5dec\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00166010_2\n\t"
      "pushl $1\n\t"
      "pushl $0x5c\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a1d90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166010_2:\n\t"
      "cmpw $0, 0x3256bc\n\t"
      "jne .LFUN_00166010_6\n\t"
      "movb 0x3256d5, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166010_6\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .LFUN_00166010_6\n\t"
      "movl 0x5a5df0, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00166010_6\n\t"
      "cmpw $0, 0x2(%%ecx)\n\t"
      "jle .LFUN_00166010_6\n\t"
      "cmpl $-1, 0x44(%%ecx)\n\t"
      "je .LFUN_00166010_6\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00166010_6\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00166010_6\n\t"
      "movw 0x5a5daa, %%dx\n\t"
      "andw $1, %%dx\n\t"
      "je .LFUN_00166010_3\n\t"
      "flds 0x5a5df4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00166010_6\n\t"
      ".LFUN_00166010_3:\n\t"
      "flds 0x5a5dd0\n\t"
      "movl 0x5a5dec, %%eax\n\t"
      "fmuls 0x5a5bd0\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "flds 0x5a5dcc\n\t"
      "fmuls 0x5a5bcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5dc8\n\t"
      "fmuls 0x5a5bc8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x5a5dd4\n\t"
      "flds 0x14(%%ecx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00166010_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253f44\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      ".LFUN_00166010_4:\n\t"
      "testw %%dx, %%dx\n\t"
      "je .LFUN_00166010_7\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x5a5df4\n\t"
      ".LFUN_00166010_5:\n\t"
      "fsts 0x47ddc4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00166010_6\n\t"
      "movb $1, 0x47df08(%%esi)\n\t"
      ".LFUN_00166010_6:\n\t"
      "movb 0x47df08(%%esi), %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00166010_7:\n\t"
      "fxch %%st(1)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsub %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstp %%st(1)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00166010_8\n\t"
      "movb 0x47df08(%%esi), %%al\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, 0x47ddc4\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00166010_8:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00166010_5\n\t"
      "movb $1, 0x47df08(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "movb 0x47df08(%%esi), %%al\n\t"
      "movl $0x3f800000, 0x47ddc4\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00166010_9:\n\t"
      "xorb %%al, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b166010_assert), [exitfn] "m"(b166010_exitfn)
      : "memory");
}
#else
#error "FUN_00166010: clang naked draft required"
#endif


/* FUN_00166210 (0x166210) — readable C lift (restored pre-naked). */
void FUN_00166210(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test ebx, ebx -> jne 0x16623a */
  display_assert((char *)0x002a1dd0, (char *)0x002a1cc8, 163, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x16625e */
  display_assert((char *)0x002a1dc8, (char *)0x002a1cc8, 164, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1663ee */
  /* relift: relift: fld dword ptr [0x2533c8] */
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)eax);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  /* test (char)eax, 1 -> jne 0x1663ed */
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_001d9e70(0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_seed_step((void *)(uintptr_t)eax);
  perpendicular2d((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx);
  /* relift: relift: fld dword ptr [0x2533c8] */
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}


/* FUN_00166400 (0x166400) — readable C lift (restored pre-naked). */
void FUN_00166400(void)
{
  int eax = 0;

  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x166439 */
  display_assert((char *)0x002a1e14, (char *)0x002a1cc8, 290, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5de8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16646c */
  display_assert((char *)0x0029f040, (char *)0x002a1cc8, 291, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16649f */
  display_assert((char *)0x0029f008, (char *)0x002a1cc8, 292, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1664c8 */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 293, 0);
  system_exit(0);
  FUN_0016f910(17);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x16688a */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d4] */
  /* test (char)eax, (char)eax -> je 0x16688a */
  /* relift: relift: fld dword ptr [0x5a5dd0] */
  /* relift: relift: fld dword ptr [0x5a5dcc] */
  /* relift: relift: fld dword ptr [0x5a5dc8] */
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* test (char)eax, 0x41 -> jne 0x166553 */
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* test (char)eax, 0x41 -> jne 0x166590 */
  /* relift: test byte ptr [0x5a5da8], 2 -> je 0x1665d2 */
  /* relift: relift: fcomp dword ptr [0x2546a0] */
  /* relift: cmp word ptr [0x47df30], 0x14 -> jge 0x1665d4 */
  error(0, (char *)0x002a1dd8);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* relift: relift: fld dword ptr [0x5a5db8] */
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b94] = 0x11002 */
  FUN_000d1e90(0.0f, 0.0f);
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* mem[0x005a5ae8] = eax */
  /* relift: relift: fld dword ptr [0x5a5de4] */
  FUN_000d1e90(0.0f, 0.0f);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5ac0] = 0x2191209 */
  /* mem[0x005a5b28] = 0xc00 */
  /* mem[0x005a5b48] = 0x11180118 */
  /* mem[0x005a5b74] = 0x48 */
  real_a_rgb_color_to_pixel32(0.0f, (void *)0x005a5dac);
  /* mem[0x005a5aec] = eax */
  FUN_000d1dd0((void *)0x005a5dd8);
  /* mem[0x005a5b0c] = eax */
  /* mem[0x005a5ac4] = 0x283c311c */
  /* mem[0x005a5b2c] = eax */
  /* mem[0x005a5b4c] = 0x108021c */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ae0] = 0xc3d000f */
  /* mem[0x005a5ae4] = 0xd243c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
}


/* FUN_00166890 (0x166890) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b166890_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b166890_exitfn)(int) = system_exit;
static void (*const b166890_c16f910)(int16_t profile) = FUN_0016f910;
static void (*const b166890_c166010)(void) = (void *)FUN_00166010;
static void *(*const b166890_tag)(int, int) = tag_get;
static void *(*const b166890_memset)(void *, int, unsigned int) = csmemset;
static unsigned int *(*const b166890_lseed)(void) = random_math_get_local_seed_address;
static float (*const b166890_rmreal)(unsigned int *) = random_math_real;
static void * (*const b166890_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b166890_c166210)(void) = (void *)FUN_00166210;
static void (*const b166890_c17cf00)(void) = (void *)FUN_0017cf00;
static void (*const b166890_c109150)(float *src, float *dst) = matrix_inverse;
static void (*const b166890_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static void (*const b166890_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static double (*const b166890_c1d9c2b)(double x) = floor;
static void (*const b166890_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static float (*const b166890_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static void (*const b166890_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void __stdcall (*const b166890_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static char (*const b166890_c1792d0)(void) = FUN_001792d0;
static void __stdcall (*const b166890_c1ea650)(uint32_t count, void *rects, uint32_t flags, uint32_t color, float z, uint32_t stencil) = (void *)D3DDevice_Clear;
static void __stdcall (*const b166890_c1e96d0)(uint32_t mode) = (void *)D3DDevice_SetRenderState_CullMode;
static void (*const b166890_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b166890_c1ea290)(uint32_t enable) = (void *)D3DDevice_SetRenderState_ZEnable;
static void __stdcall (*const b166890_c1e98e0)(uint32_t value) = (void *)D3DDevice_SetRenderState_ZBias;
static void (*const b166890_c155cf0)(int stage, int bitmap_tag_index, int frame_index) = rasterizer_set_texture_direct;
static void __stdcall (*const b166890_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void (*const b166890_c156510)(void *state) = rasterizer_set_pixel_shader;
static void * (*const b166890_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b166890_c1e9320)(void) = (void *)D3DDevice_SetRenderState_PSTextureModes;
static void (*const b166890_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void (*const b166890_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static short (*const b166890_c184610)(void *group) = FUN_00184610;
static void (*const b166890_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void (*const b166890_c156710)(void *a1) = rasterizer_set_model_skinning;
static void (*const b166890_c174510)(void *group, int a2) = FUN_00174510;
static void (*const b166890_c17ed90)(void) = (void *)FUN_0017ed90;

__attribute__((naked, noinline))
void FUN_00166890(int pass_index)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x180, %%esp\n\t"
      "pushl %%edi\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "je .LFUN_00166890_1\n\t"
      "cmpw $1, %%di\n\t"
      "je .LFUN_00166890_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1f3\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a20e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_1:\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00166890_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1f4\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_2:\n\t"
      "testw %%di, %%di\n\t"
      "movw %%di, 0x47ddc8\n\t"
      "jne .LFUN_00166890_3\n\t"
      "pushl $0x12\n\t"
      "call *%[c16f910]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00166890_3:\n\t"
      "call *%[c166010]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_58\n\t"
      "movswl 0x5a5bc2, %%eax\n\t"
      "flds 0x47ddc4\n\t"
      "fcomps 0x2533c0\n\t"
      "imull $0x4c, %%eax, %%eax\n\t"
      "addl $0x47ddd0, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x5a5df0, %%ebx\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_00166890_4\n\t"
      "pushl $1\n\t"
      "pushl $0x202\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a20c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_4:\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_00166890_33\n\t"
      "movswl 0x5a5bc2, %%eax\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "addl $0x47dcb8, %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movb 0x325172, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x7c(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "je .LFUN_00166890_8\n\t"
      "movl 0x44(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl $0x47dcb8, -0x14(%%ebp)\n\t"
      "movl $4, -0x24(%%ebp)\n\t"
      ".LFUN_00166890_5:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $0x4c\n\t"
      "leal 0x47ddd0(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%si, 0x2(%%ebx)\n\t"
      "jle .LFUN_00166890_7\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00166890_6:\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal 0x47dddc(%%ecx,%%eax,8), %%edi\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "fstps (%%edi)\n\t"
      "incl %%esi\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "cmpw 0x2(%%ebx), %%si\n\t"
      "jl .LFUN_00166890_6\n\t"
      ".LFUN_00166890_7:\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "pushl $0x34\n\t"
      "pushl $0x5a5bc8\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "addl $0x4c, %%edx\n\t"
      "addl $0x34, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jne .LFUN_00166890_5\n\t"
      "movb $0, 0x325172\n\t"
      ".LFUN_00166890_8:\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "addl $0x2c, %%esi\n\t"
      "call *%[c166210]\n\t"
      "movl 0x5a5e1c, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x5a5bc2, %%dx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17cf00]\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "call *%[c109150]\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5a5c2c\n\t"
      "call *%[c109850]\n\t"
      "movswl 0x5a5bc2, %%eax\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "pushl $0x34\n\t"
      "addl $0x47dcb8, %%eax\n\t"
      "pushl $0x5a5c2c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x2(%%ebx), %%ecx\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movw 0x5a5bfa, %%ax\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl 0x5a5bf4, %%edx\n\t"
      "subw 0x5a5bf6, %%ax\n\t"
      "movl 0x5a5bf8, %%ecx\n\t"
      "fdivr %%st(1), %%st(0)\n\t"
      "subl %%edx, %%ecx\n\t"
      "movswl %%cx, %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "flds 0x5a5bf0\n\t"
      "fmuls 0x253398\n\t"
      ".byte 0xd9, 0xf2\n\t"
      "fstp %%st(0)\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0xcc(%%ebp)\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "flds 0x255e94\n\t"
      "pushl %%eax\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "movl $0, -0xc8(%%ebp)\n\t"
      "movl $0, -0xc4(%%ebp)\n\t"
      "movl $0, -0xbc(%%ebp)\n\t"
      "fstps -0xc0(%%ebp)\n\t"
      "movl $0, -0xb4(%%ebp)\n\t"
      "movl $0, -0xac(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0xa8(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "movl $0, -0xa4(%%ebp)\n\t"
      "movl $0x3f000000, -0xa0(%%ebp)\n\t"
      "movl $0, -0x9c(%%ebp)\n\t"
      "movl $0, -0x98(%%ebp)\n\t"
      "movl $0, -0x94(%%ebp)\n\t"
      "movl $0x3f800000, -0x90(%%ebp)\n\t"
      "movl $0, -0x8c(%%ebp)\n\t"
      "movl $0, -0x88(%%ebp)\n\t"
      "movl $0, -0x84(%%ebp)\n\t"
      "movl $0x3f800000, -0x80(%%ebp)\n\t"
      "movl $0x3f800000, -0x30(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "flds 0x25eeac\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xb8(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fstps -0xb0(%%ebp)\n\t"
      "call *%[c109680]\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "flds -0x30(%%ebp)\n\t"
      "addl $0x44, %%esp\n\t"
      "fpatan\n\t"
      "fmuls 0x20(%%ebx)\n\t"
      "fchs\n\t"
      "fsubrs 0x4(%%esi)\n\t"
      "fsts 0x4(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fsin\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fcomps 0x25bb10\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00166890_14\n\t"
      "flds 0x28(%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fdivs -0x48(%%ebp)\n\t"
      "fmuls -0xd0(%%ebp)\n\t"
      "fsubrs 0x8(%%esi)\n\t"
      "fsts 0x8(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fistps -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00166890_9\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "movw (%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "decw %%cx\n\t"
      "movzwl %%cx, %%eax\n\t"
      "movswl 0x2(%%ebx), %%ecx\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movswl %%dx, %%edx\n\t"
      "jmp .LFUN_00166890_10\n\t"
      ".LFUN_00166890_9:\n\t"
      "jge .LFUN_00166890_11\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "movswl (%%esi), %%edx\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00166890_10:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fstps 0xc(%%esi,%%edx,8)\n\t"
      "leal 0xc(%%esi,%%edx,8), %%eax\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_00166890_11:\n\t"
      "movw (%%esi), %%dx\n\t"
      "movswl 0x2(%%ebx), %%ecx\n\t"
      "subw %%di, %%dx\n\t"
      "movzwl %%dx, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fsubrs 0x8(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fsts 0x8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "movw %%dx, (%%esi)\n\t"
      "jnp .LFUN_00166890_12\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00166890_13\n\t"
      ".LFUN_00166890_12:\n\t"
      "pushl %%ecx\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a2070\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x24, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00166890_13:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00166890_14:\n\t"
      "cmpw $0, 0x2(%%ebx)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_00166890_26\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0x3f36a7f0, -0x30(%%ebp)\n\t"
      "movl $0x3eaf34d7, -0x2c(%%ebp)\n\t"
      "movl $0x3f146dc6, -0x28(%%ebp)\n\t"
      ".LFUN_00166890_15:\n\t"
      "movl 0x44(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "je .LFUN_00166890_16\n\t"
      "movl 0x60(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00166890_17\n\t"
      ".LFUN_00166890_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x28d\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a203c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_17:\n\t"
      "flds 0x48(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00166890_24\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "fildl 0x60(%%edi)\n\t"
      "fmuls -0x34(%%ebp,%%eax,4)\n\t"
      "flds 0x5a5e18\n\t"
      "fdivs 0x48(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fstpl -0x1c(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9c2b]\n\t"
      "fsubrl -0x1c(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fcompl 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00166890_18\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .LFUN_00166890_20\n\t"
      ".LFUN_00166890_18:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl -0x1c(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9c2b]\n\t"
      "fsubrl -0x1c(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fcompl 0x2573d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00166890_19\n\t"
      "fldl 0x2573d8\n\t"
      "jmp .LFUN_00166890_20\n\t"
      ".LFUN_00166890_19:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl -0x1c(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9c2b]\n\t"
      "fsubrl -0x1c(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00166890_20:\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fstps -0x58(%%ebp,%%eax,4)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fistps -0x44(%%ebp)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "idivl 0x60(%%ecx)\n\t"
      "movl %%edx, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jge .LFUN_00166890_22\n\t"
      "movb 0x47df32, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00166890_21\n\t"
      "pushl $0x2a1ff8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movswl %%di, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2a1fe8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x5a5e18, %%eax\n\t"
      "flds 0x5a5e18\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a1fd8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x48(%%ebx)\n\t"
      "movl 0x48(%%ebx), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a1fc8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movswl -0xc(%%ebp), %%edi\n\t"
      "movl -0x34(%%ebp,%%edi,4), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "flds -0x34(%%ebp,%%edi,4)\n\t"
      "pushl %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a1fb8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a1fac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl -0x58(%%ebp,%%edi,4), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a1f94\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, 0x47df32\n\t"
      ".LFUN_00166890_21:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00166890_22:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x60(%%eax), %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_00166890_23\n\t"
      "pushl $1\n\t"
      "pushl $0x2aa\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a1f50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_23:\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "movw %%di, 0x47dd8c(,%%eax,2)\n\t"
      "jmp .LFUN_00166890_25\n\t"
      ".LFUN_00166890_24:\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "cdq\n\t"
      "idivl 0x60(%%edi)\n\t"
      "movl $0, -0x58(%%ebp,%%ecx,4)\n\t"
      "movw %%dx, 0x47dd8c(,%%ecx,2)\n\t"
      ".LFUN_00166890_25:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x2(%%ebx), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_00166890_15\n\t"
      ".LFUN_00166890_26:\n\t"
      "movw 0x2(%%ebx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_00166890_30\n\t"
      ".LFUN_00166890_27:\n\t"
      "movw (%%esi), %%dx\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "addw %%di, %%dx\n\t"
      "movzwl %%dx, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movswl %%di, %%edi\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fldl 0x2a1f48\n\t"
      "call *%[c1d9e70]\n\t"
      "fsubrl 0x2573d8\n\t"
      "fldl 0x28c8d0\n\t"
      "call *%[c1d9e70]\n\t"
      "flds 0x47ddc4\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      ".byte 0xde, 0xc9\n\t"
      "pushl %%eax\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "fdivs 0x8(%%ebx)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movswl -0x44(%%ebp), %%ecx\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x24(%%ebx)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "fsubrs 0xc(%%esi,%%ecx,8)\n\t"
      "fstps 0xc(%%esi,%%ecx,8)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x24(%%ebx)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "fsubrs 0x10(%%esi,%%ecx,8)\n\t"
      "fstps 0x10(%%esi,%%ecx,8)\n\t"
      "flds 0x48(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "leal (%%edi,%%edi,2), %%eax\n\t"
      "leal 0x47dd94(,%%eax,4), %%eax\n\t"
      "jnp .LFUN_00166890_28\n\t"
      "flds -0x58(%%ebp,%%ecx,4)\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps (%%eax)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(1)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_00166890_29\n\t"
      ".LFUN_00166890_28:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl $0, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl $0, 0x8(%%eax)\n\t"
      ".LFUN_00166890_29:\n\t"
      "flds 0xc(%%esi,%%ecx,8)\n\t"
      "shll $5, %%edi\n\t"
      "flds -0x4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "movl %%edx, -0x178(%%ebp,%%edi,1)\n\t"
      "leal -0x170(%%ebp,%%edi,1), %%eax\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x180(%%ebp,%%edi,1)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x17c(%%ebp,%%edi,1)\n\t"
      "fstps -0x174(%%ebp,%%edi,1)\n\t"
      "flds 0x10(%%esi,%%ecx,8)\n\t"
      "movw 0x2(%%ebx), %%cx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "fmuls 0x255964\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fstps 0xc(%%eax)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_00166890_27\n\t"
      ".LFUN_00166890_30:\n\t"
      "pushl $8\n\t"
      "leal -0x180(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x51\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $5\n\t"
      "leal -0xcc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x44\n\t"
      "call *%[c1eb8d0]\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fcomps 0x10(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00166890_31\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movb $0, 0x47dd89\n\t"
      "movb $0, 0x47dd88\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00166890_31:\n\t"
      "movl 0x5a5df0, %%edx\n\t"
      "movw (%%edx), %%cx\n\t"
      "movb %%cl, %%al\n\t"
      "notb %%al\n\t"
      "andb $1, %%al\n\t"
      "testb $2, %%cl\n\t"
      "movb %%al, 0x47dd89\n\t"
      "jne .LFUN_00166890_32\n\t"
      "movl 0x47df04, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_00166890_32\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "movb $1, 0x47dd88\n\t"
      "jmp .LFUN_00166890_34\n\t"
      ".LFUN_00166890_32:\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "movb $0, 0x47dd88\n\t"
      "jmp .LFUN_00166890_34\n\t"
      ".LFUN_00166890_33:\n\t"
      "movb 0x47dd89, %%al\n\t"
      ".LFUN_00166890_34:\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00166890_35\n\t"
      "movb 0x47dd88, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_57\n\t"
      ".LFUN_00166890_35:\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_00166890_39\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00166890_36\n\t"
      "testb $2, %%cl\n\t"
      "jne .LFUN_00166890_39\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00166890_38\n\t"
      ".LFUN_00166890_36:\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_00166890_37\n\t"
      "movl 0x47df04, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00166890_38\n\t"
      ".LFUN_00166890_37:\n\t"
      "call *%[c1792d0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_39\n\t"
      "movb 0x3256d6, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_39\n\t"
      ".LFUN_00166890_38:\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_00166890_40\n\t"
      ".LFUN_00166890_39:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_00166890_40:\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "setne %%cl\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%esi\n\t"
      "orl $0x80, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ea650]\n\t"
      "pushl $0x901\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "call *%[c1e96d0]\n\t"
      "movl $0x1000000, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl $0x1000000, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl %%esi, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $1\n\t"
      "movl %%esi, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "movw %%di, %%si\n\t"
      "negw %%si\n\t"
      "movl $0x40354, %%ecx\n\t"
      "sbbl %%esi, %%esi\n\t"
      "addl $0x203, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%di, %%di\n\t"
      "sete %%dl\n\t"
      "movl %%esi, 0x1fb77c\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "movl %%edx, %%esi\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $0\n\t"
      "movl %%esi, 0x1fb798\n\t"
      "call *%[c1e98e0]\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_00166890_41\n\t"
      "flds 0x8(%%ebx)\n\t"
      "movl $1, %%edi\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "pushl %%edi\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fdivrs 0x2533c8\n\t"
      "pushl $-0x54\n\t"
      "movl $0, -0x68(%%ebp)\n\t"
      "movl $0, -0x64(%%ebp)\n\t"
      "movl $0, -0x60(%%ebp)\n\t"
      "movl $0, -0x5c(%%ebp)\n\t"
      "movl $0, -0x58(%%ebp)\n\t"
      "movl $0, -0x54(%%ebp)\n\t"
      "movl $0, -0x50(%%ebp)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "flds 0x5a5bd4\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fmuls 0x5a5bd4\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls 0x5a5bd0\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls 0x5a5bcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jmp .LFUN_00166890_42\n\t"
      ".LFUN_00166890_41:\n\t"
      "movl $1, %%edi\n\t"
      ".LFUN_00166890_42:\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl 0x5a5df0, %%ecx\n\t"
      "movb (%%ecx), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00166890_43\n\t"
      "movl %%edi, 0x5a5b94\n\t"
      "movl $0x3300, 0x5a5ae4\n\t"
      "jmp .LFUN_00166890_47\n\t"
      ".LFUN_00166890_43:\n\t"
      "movl 0x476204, %%edx\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c155cf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "flds 0x10(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00166890_44\n\t"
      "pushl %%edi\n\t"
      "pushl $0x358\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a1f2c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_44:\n\t"
      "movl %%edi, 0x5a5b98\n\t"
      "movl %%edi, 0x5a5b94\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fdivs 0x10(%%ebx)\n\t"
      "movl $0x437f0000, -0x3c(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00166890_45\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00166890_46\n\t"
      ".LFUN_00166890_45:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x123\n\t"
      "pushl $0x269ffc\n\t"
      "pushl $0x269fe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00166890_46:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "shll $0x18, -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x5a5ae8\n\t"
      "movl $0x28110820, 0x5a5ac0\n\t"
      "movl $0xc00, 0x5a5b28\n\t"
      "movl $0x3c00, 0x5a5ae4\n\t"
      ".LFUN_00166890_47:\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[c156510]\n\t"
      "movb 0x47dd88, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_57\n\t"
      "movl 0x47df04, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .LFUN_00166890_56\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_00166890_48\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00166890_48:\n\t"
      "movl 0x47df00, %%ebx\n\t"
      "leal (%%eax,%%eax,4), %%esi\n\t"
      "shll $5, %%esi\n\t"
      "movl 0xc(%%esi,%%ebx,1), %%ecx\n\t"
      "movw 0x24(%%ecx), %%ax\n\t"
      "addl %%ebx, %%esi\n\t"
      "cmpw $4, %%ax\n\t"
      "jne .LFUN_00166890_50\n\t"
      "pushl $4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x28(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_00166890_51\n\t"
      "pushl $0x21\n\t"
      "call *%[c1e9320]\n\t"
      "pushl $4\n\t"
      "movl $0x15, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0xb0(%%ebx), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x10(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl $0xa, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl %%edi\n\t"
      "movl $0xb, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "flds 0x9c(%%ebx)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "pushl $2\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "pushl $-0x53\n\t"
      "flds 0xa0(%%ebx)\n\t"
      "movl $0, -0x64(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "movl $0, -0x60(%%ebp)\n\t"
      "movl $0, -0x5c(%%ebp)\n\t"
      "movl $0, -0x58(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "movl $0, -0x50(%%ebp)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_49\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jmp .LFUN_00166890_52\n\t"
      ".LFUN_00166890_49:\n\t"
      "pushl $0x2a1e90\n\t"
      "pushl $0\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00166890_52\n\t"
      ".LFUN_00166890_50:\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_00166890_51\n\t"
      "cmpw $8, %%ax\n\t"
      "jne .LFUN_00166890_52\n\t"
      ".LFUN_00166890_51:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9320]\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl $0x15, %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c1e9410]\n\t"
      ".LFUN_00166890_52:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c184610]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $5\n\t"
      "call *%[c178b40]\n\t"
      "movl 0x60(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00166890_53\n\t"
      "movw 0x64(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_00166890_53\n\t"
      "movw %%cx, -0x3c(%%ebp)\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "jmp .LFUN_00166890_54\n\t"
      ".LFUN_00166890_53:\n\t"
      "movl 0x31fc60, %%edx\n\t"
      "movw %%di, -0x3c(%%ebp)\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      ".LFUN_00166890_54:\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c156710]\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00166890_55\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c174510]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .LFUN_00166890_55\n\t"
      "movl 0x5a54d0, %%ecx\n\t"
      "movl 0x5a54cc, %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x5a54d0\n\t"
      "movl 0x50(%%esi), %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, 0x5a54cc\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ed90]\n\t"
      "movl 0x5a54c8, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a54c8\n\t"
      ".LFUN_00166890_55:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x47df04, %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00166890_48\n\t"
      ".LFUN_00166890_56:\n\t"
      "pushl $0\n\t"
      "movl $0x15, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00166890_57\n\t"
      "pushl $0x2a1e54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00166890_57:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00166890_58:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b166890_assert), [exitfn] "m"(b166890_exitfn), [c16f910] "m"(b166890_c16f910), [c166010] "m"(b166890_c166010), [tag] "m"(b166890_tag), [memset] "m"(b166890_memset), [lseed] "m"(b166890_lseed), [rmreal] "m"(b166890_rmreal), [c8e0b0] "m"(b166890_c8e0b0), [c166210] "m"(b166890_c166210), [c17cf00] "m"(b166890_c17cf00), [c109150] "m"(b166890_c109150), [c109850] "m"(b166890_c109850), [c109680] "m"(b166890_c109680), [c1d9c2b] "m"(b166890_c1d9c2b), [c8f390] "m"(b166890_c8f390), [c1d9e70] "m"(b166890_c1d9e70), [xfrmpt] "m"(b166890_xfrmpt), [c1eb8d0] "m"(b166890_c1eb8d0), [c1792d0] "m"(b166890_c1792d0), [c1ea650] "m"(b166890_c1ea650), [c1e96d0] "m"(b166890_c1e96d0), [c1e9350] "m"(b166890_c1e9350), [c1ea290] "m"(b166890_c1ea290), [c1e98e0] "m"(b166890_c1e98e0), [c155cf0] "m"(b166890_c155cf0), [c1e9410] "m"(b166890_c1e9410), [c156510] "m"(b166890_c156510), [c1906b0] "m"(b166890_c1906b0), [c1e9320] "m"(b166890_c1e9320), [c155e80] "m"(b166890_c155e80), [c167ff0] "m"(b166890_c167ff0), [c184610] "m"(b166890_c184610), [c178b40] "m"(b166890_c178b40), [c156710] "m"(b166890_c156710), [c174510] "m"(b166890_c174510), [c17ed90] "m"(b166890_c17ed90)
      : "memory");
}
#else
#error "FUN_00166890: clang naked draft required"
#endif


/* FUN_001677d0 (0x1677d0) — readable C lift from XBE leaf. */
void FUN_001677d0(void *shader, int unused, int a2, int a3, int a4, unsigned short *info)
{
  int perm;
  short mode;

  (void)unused;
  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a1cc8, 0x3dc, 1);
    system_exit(-1);
  }
  if (!((unsigned char (*)(void))FUN_00166010)())
    return;
  mode = *(short *)0x47ddc8;
  if (mode != 0 && mode != 1) {
    display_assert((char *)0x2a2180, (char *)0x2a1cc8, 0x3e0, 1);
    system_exit(-1);
  }
  if (!*(unsigned char *)0x47dd89)
    return;
  if (!*(int *)0x5a5df0) {
    display_assert((char *)0x2a215c, (char *)0x2a1cc8, 0x3e4, 1);
    system_exit(-1);
  }
  {
    short s = *(short *)0x5a5bc2;
    if (s < 0 || s >= 4) {
      display_assert((char *)0x2a20f8, (char *)0x2a1cc8, 0x3e5, 1);
      system_exit(-1);
    }
  }
  perm = shader_get_vertex_shader_permutation(shader);
  FUN_00178b40(8, (int)info[0], perm);
  ((void (*)(int, int, int, unsigned short *))FUN_0015dc10)(a2, a3, a4, info);
  if (*(short *)0x3256ba == 2) {
    int nverts;
    *(int *)0x5a54c0 = *(int *)0x5a54c0 + 1;
    *(int *)0x5a54bc = *(int *)0x5a54bc + a4;
    nverts = ((int (*)(int, int, int))rasterizer_frame_statistics_count_static_vertices)(a2, a3, a4);
    *(int *)0x5a54b8 = *(int *)0x5a54b8 + nverts;
  }
}



/* FUN_00167920 (0x167920) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b167920_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b167920_exitfn)(int) = system_exit;
static void (*const b167920_c166010)(void) = (void *)FUN_00166010;
static void (*const b167920_c155cf0)(int stage, int bitmap_tag_index, int frame_index) = rasterizer_set_texture_direct;
static void __stdcall (*const b167920_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void __stdcall (*const b167920_c1e96d0)(uint32_t mode) = (void *)D3DDevice_SetRenderState_CullMode;
static void (*const b167920_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b167920_c1ea290)(uint32_t enable) = (void *)D3DDevice_SetRenderState_ZEnable;
static void __stdcall (*const b167920_c1e98e0)(uint32_t value) = (void *)D3DDevice_SetRenderState_ZBias;
static void (*const b167920_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void *(*const b167920_memset)(void *, int, unsigned int) = csmemset;
static unsigned int (*const b167920_cd1dd0)(float *color) = FUN_000d1dd0;
static void (*const b167920_c156510)(void *state) = rasterizer_set_pixel_shader;
static void __stdcall (*const b167920_c1ed450)(uint32_t primitive_type) = (void *)D3DDevice_Begin;
static void __stdcall (*const b167920_c1ed320)(unsigned int reg, int a, int b) = (void *)D3DDevice_SetVertexData2s;
static void (*const b167920_c1ed490)(void) = (void *)D3DDevice_End;
static void (*const b167920_c16fa40)(int16_t profile) = FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00167920(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00167920_1\n\t"
      "pushl $1\n\t"
      "pushl $0x40c\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00167920_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c166010]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00167920_15\n\t"
      "movb 0x47dd89, %%al\n\t"
      "movl 0x5a5df0, %%esi\n\t"
      "pushl %%edi\n\t"
      "movswl 0x5a5bc2, %%edi\n\t"
      "imull $0x4c, %%edi, %%edi\n\t"
      "addl $0x47ddd0, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .LFUN_00167920_2\n\t"
      "movb 0x47dd88, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .LFUN_00167920_3\n\t"
      ".LFUN_00167920_2:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00167920_3:\n\t"
      "movw 0x47ddc8, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00167920_4\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_00167920_4\n\t"
      "pushl $1\n\t"
      "pushl $0x415\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a2180\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00167920_4:\n\t"
      "movl 0x5a5df0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00167920_5\n\t"
      "pushl $1\n\t"
      "pushl $0x417\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a215c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00167920_5:\n\t"
      "movw 0x5a5bc2, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00167920_6\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .LFUN_00167920_7\n\t"
      ".LFUN_00167920_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x418\n\t"
      "pushl $0x2a1cc8\n\t"
      "pushl $0x2a20f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00167920_7:\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00167920_10\n\t"
      "jmp .LFUN_00167920_9\n\t"
      ".LFUN_00167920_8:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_00167920_9:\n\t"
      "movw (%%edi), %%ax\n\t"
      "addw %%bx, %%ax\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movswl %%dx, %%edx\n\t"
      "movw 0x47dd8c(,%%edx,2), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c155cf0]\n\t"
      "movswl %%bx, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "incl %%ebx\n\t"
      "cmpw %%cx, %%bx\n\t"
      "jl .LFUN_00167920_8\n\t"
      ".LFUN_00167920_10:\n\t"
      "pushl $0x901\n\t"
      "call *%[c1e96d0]\n\t"
      "cmpw $0, 0x47ddc8\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "jne .LFUN_00167920_11\n\t"
      "testb %%bl, %%bl\n\t"
      "movl $0x1000000, %%edi\n\t"
      "jne .LFUN_00167920_12\n\t"
      ".LFUN_00167920_11:\n\t"
      "movl $0x10101, %%edi\n\t"
      ".LFUN_00167920_12:\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $1, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl %%edi, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "movb %%bl, %%dl\n\t"
      "negb %%dl\n\t"
      "movl $0x40344, %%ecx\n\t"
      "movl $1, 0x1fb784\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl $0x304, %%edx\n\t"
      "incl %%edx\n\t"
      "movl %%edx, %%edi\n\t"
      "call *%[c1e9350]\n\t"
      "movb %%bl, %%al\n\t"
      "negb %%al\n\t"
      "movl %%edi, 0x1fb790\n\t"
      "movl $0x40348, %%ecx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffffcff, %%eax\n\t"
      "addl $0x302, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x8006, %%edx\n\t"
      "movl $0x40350, %%ecx\n\t"
      "movl %%edi, 0x1fb794\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl $0x8006, 0x1fb7c0\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $0\n\t"
      "movl $0, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "pushl $0\n\t"
      "call *%[c1e98e0]\n\t"
      "pushl $0\n\t"
      "pushl $8\n\t"
      "pushl $0x26\n\t"
      "call *%[c178b40]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $3, %%ax\n\t"
      "setg %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "pushl $0x47dd94\n\t"
      "movl $0x11004, 0x5a5b94\n\t"
      "shll $5, %%ecx\n\t"
      "cmpw $2, %%ax\n\t"
      "setg %%dl\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw $1, %%ax\n\t"
      "setg %%dl\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "orl $1, %%ecx\n\t"
      "movl %%ecx, 0x5a5b98\n\t"
      "call *%[cd1dd0]\n\t"
      "pushl $0x47dda0\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "call *%[cd1dd0]\n\t"
      "pushl $0x47ddac\n\t"
      "movl %%eax, 0x5a5b08\n\t"
      "movl $0x8010902, 0x5a5b48\n\t"
      "movl $0x3089, 0x5a5b74\n\t"
      "call *%[cd1dd0]\n\t"
      "pushl $0x47ddb8\n\t"
      "movl %%eax, 0x5a5aec\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $0x28, %%esp\n\t"
      "movl %%eax, 0x5a5b0c\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $1, 0x2(%%esi)\n\t"
      "movl $0xc0, 0x5a5b2c\n\t"
      "setle %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0xa010b02, 0x5a5b4c\n\t"
      "movl $0x30ab, 0x5a5b78\n\t"
      "movl $0xc00, %%edi\n\t"
      "decl %%eax\n\t"
      "andl $9, %%eax\n\t"
      "addl $0x20, %%eax\n\t"
      "orl $0x2800, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "movl %%eax, 0x5a5ac4\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "setle %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0xd0, 0x5a5b30\n\t"
      "decl %%ecx\n\t"
      "andl $0xa, %%ecx\n\t"
      "addl $0x20, %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "cmpw $3, %%ax\n\t"
      "setle %%dl\n\t"
      "decl %%edx\n\t"
      "andl $0xb, %%edx\n\t"
      "addl $0x20, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5ac8\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $2, %%ax\n\t"
      "setle %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%edi, 0x5a5b7c\n\t"
      "movl $0x1c1d0000, 0x5a5acc\n\t"
      "movl $0xc0, 0x5a5b34\n\t"
      "decl %%ecx\n\t"
      "andl $0xa, %%ecx\n\t"
      "addl $0x20, %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "cmpw $3, %%ax\n\t"
      "setle %%dl\n\t"
      "decl %%edx\n\t"
      "andl $0xb, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw $2, %%ax\n\t"
      "setle %%dl\n\t"
      "decl %%edx\n\t"
      "andl $0xa, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "orl $0x20, %%ecx\n\t"
      "movl %%ecx, 0x5a5b50\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $1, %%ax\n\t"
      "setle %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%edi, 0x5a5b80\n\t"
      "popl %%edi\n\t"
      "decl %%ecx\n\t"
      "andl $9, %%ecx\n\t"
      "addl $0x20, %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "cmpw $1, %%ax\n\t"
      "setle %%dl\n\t"
      "decl %%edx\n\t"
      "andl $9, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "shll $8, %%ecx\n\t"
      "orl $0xc0020, %%ecx\n\t"
      "movl %%ecx, 0x5a5b54\n\t"
      "movl 0x1c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00167920_13\n\t"
      "movl %%esi, 0x5a5b6c\n\t"
      "jmp .LFUN_00167920_14\n\t"
      ".LFUN_00167920_13:\n\t"
      "pushl $0x5a5dd8\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5b6c\n\t"
      ".LFUN_00167920_14:\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl $0x8010f00, 0x5a5ae0\n\t"
      "movl $0xc011c00, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "addl $4, %%esp\n\t"
      "pushl $7\n\t"
      "call *%[c1ed450]\n\t"
      "movl $1, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "call *%[c1ed490]\n\t"
      "cmpw $0, 0x47ddc8\n\t"
      "jne .LFUN_00167920_16\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00167920_17\n\t"
      "movl $0x10101, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x305, %%edx\n\t"
      "movl $0x40344, %%ecx\n\t"
      "movl $0x10101, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x40348, %%ecx\n\t"
      "movl $0x305, 0x1fb790\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%esi, 0x1fb794\n\t"
      "call *%[memset]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%esi, 0x5a5b94\n\t"
      "call *%[c156510]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $7\n\t"
      "call *%[c1ed450]\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "call *%[c1ed320]\n\t"
      "call *%[c1ed490]\n\t"
      ".LFUN_00167920_15:\n\t"
      "cmpw $0, 0x47ddc8\n\t"
      "je .LFUN_00167920_17\n\t"
      ".LFUN_00167920_16:\n\t"
      "pushl $0x12\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00167920_17:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b167920_assert), [exitfn] "m"(b167920_exitfn), [c166010] "m"(b167920_c166010), [c155cf0] "m"(b167920_c155cf0), [c1e9410] "m"(b167920_c1e9410), [c1e96d0] "m"(b167920_c1e96d0), [c1e9350] "m"(b167920_c1e9350), [c1ea290] "m"(b167920_c1ea290), [c1e98e0] "m"(b167920_c1e98e0), [c178b40] "m"(b167920_c178b40), [memset] "m"(b167920_memset), [cd1dd0] "m"(b167920_cd1dd0), [c156510] "m"(b167920_c156510), [c1ed450] "m"(b167920_c1ed450), [c1ed320] "m"(b167920_c1ed320), [c1ed490] "m"(b167920_c1ed490), [c16fa40] "m"(b167920_c16fa40)
      : "memory");
}
#else
#error "FUN_00167920: clang naked draft required"
#endif


/* FUN_00167ee0 (0x167ee0) — readable C lift from XBE leaf. */
unsigned char FUN_00167ee0(float *obj)
{
  float *cam;
  float dx, dy, dz, dist;

  if (!*(unsigned char *)0x3256d5)
    return 0;
  if (*(short *)0x3256bc != 0)
    return 0;
  if (!((unsigned char (*)(void))FUN_00166010)())
    return 0;
  if (!obj) {
    display_assert((char *)0x29f510, (char *)0x2a1cc8, 0x499, 1);
    system_exit(-1);
  }
  cam = *(float **)0x5a5df0;
  if (!cam) {
    display_assert((char *)0x2a1dd0, (char *)0x2a1cc8, 0x49a, 1);
    system_exit(-1);
  }
  dx = obj[0xb4 / 4] - *(float *)0x5a5bc8;
  dy = obj[0xb8 / 4] - *(float *)0x5a5bcc;
  dz = obj[0xbc / 4] - *(float *)0x5a5bd0;
  dist = *(float *)0x5a5bd4 * dx + *(float *)0x5a5bd8 * dy + *(float *)0x5a5bdc * dz;
  if (!(dist < cam[2]))
    return 0;
  *(float **)0x47df34 = obj;
  *(unsigned char *)0x47df38 = 0;
  if (*(short *)0x3256ba == 2)
    *(int *)0x5a54c4 = *(int *)0x5a54c4 + 1;
  return 1;
}



/* FUN_00167ff0 (0x167ff0) — readable C lift (restored pre-naked). */
void FUN_00167ff0(int a1, const char *call_text)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  vsprintf((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* relift: FUN_00201c48(0, 0, 1023); */
  /* test eax, eax -> jge 0x168044 */
  csstrcpy((char *)(uintptr_t)ecx, (char *)0x002a240c);
  /* cmp edi, 0x8876081f -> jg 0x168114 */
  /* cmp edi, 0x88760819 -> jg 0x1680ce */
  /* cmp edi, 0x80070057 -> jg 0x16809c */
  /* cmp edi, 0x80004005 -> je 0x168088 */
  /* cmp edi, 0x8007000e -> jne 0x168178 */
  /* cmp edi, 0x8876017c -> je 0x1680ba */
  /* cmp edi, 0x88760818 -> jne 0x168178 */
  /* cmp eax, 4 -> ja 0x168178 */
  /* cmp eax, 0x4b -> ja 0x168178 */
  error(0, (char *)0x002a21a8);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}


/* FUN_00168230 (0x168230) — readable C lift. */
__attribute__((stdcall))
int FUN_00168230(int a, int b, int c, int d, int e)
{
  return D3DDevice_CreateTexture((uint32_t)a, (uint32_t)b, (uint32_t)c, (uint32_t)d, (uint32_t)e, 0, 0);
}

/* FUN_00168250 (0x168250) — readable C lift. */
__attribute__((stdcall))
int FUN_00168250(int a, int b, int c, int d, int e, int f)
{
  return D3DDevice_CreateVolumeTexture(a, b, c, d, e, f, 0, 0);
}

/* FUN_00168280 (0x168280) — readable C lift. */
__attribute__((stdcall))
int FUN_00168280(int a, int b, int c, int d)
{
  return D3DDevice_CreateCubeTexture(a, b, c, d, 0, 0);
}

/* FUN_001682c0 (0x1682c0) — readable C lift. */
int FUN_001682c0(int a, int b)
{
  D3DTexture_LockRect((void *)(unsigned)a, (unsigned int)b, 0, 0, 0);
  return 0;
}



/* FUN_00168300 (0x168300) — readable C lift. */
int FUN_00168300(int a, int b)
{
  ((void (__stdcall *)(int, int, int, int, int))D3DVolumeTexture_LockBox)(a, b, 0, 0, 0);
  return 0;
}



/* FUN_00168340 (0x168340) — readable C lift. */
int FUN_00168340(int a, int b, int c)
{
  D3DCubeTexture_LockRect(a, b, c, 0, 0, 0);
  return 0;
}



/* FUN_00168370 (0x168370) — readable C lift: create D3D texture for bitmap. */
unsigned char FUN_00168370(void *bitmap)
{
  short levels;
  short kind;
  unsigned int fmt;
  int hr;
  unsigned char ok;
  void **out_tex;

  ok = 1;
  if (!bitmap) {
    display_assert((const char *)0x263768, (const char *)0x2a27a8, 0x33, 1);
    system_exit(-1);
  }
  if (!(*(unsigned char *)((char *)bitmap + 0xe) & 1)) {
    display_assert((const char *)0x2a2760, (const char *)0x2a27a8, 0x34, 1);
    system_exit(-1);
  }
  levels = FUN_00183120(bitmap);
  *(short *)((char *)bitmap + 0x14) = levels;
  if (!*(int *)0x476ab0) {
    *(void **)((char *)bitmap + 0x28) = 0;
    return ok;
  }
  kind = *(short *)((char *)bitmap + 0xa);
  out_tex = (void **)((char *)bitmap + 0x28);
  if (kind == 0) {
    fmt = *(unsigned int *)(0x2a2428 + (int)*(short *)((char *)bitmap + 0xc) * 4);
    hr = ((int (__stdcall *)(int, int, int, int, int, int, void **))(void *)D3DDevice_CreateTexture)(
        (int)*(short *)((char *)bitmap + 4),
        (int)*(short *)((char *)bitmap + 6),
        (int)levels + 1,
        0,
        (int)fmt,
        1,
        out_tex);
    if (hr < 0) {
      ok = 0;
      FUN_00167ff0(hr, (const char *)0x2a24b0);
    } else {
      ok = 1;
    }
  } else if (kind == 1) {
    fmt = *(unsigned int *)(0x2a2428 + (int)*(short *)((char *)bitmap + 0xc) * 4);
    hr = ((int (__stdcall *)(int, int, int, int, int, int, int, void **))(void *)D3DDevice_CreateVolumeTexture)(
        (int)*(short *)((char *)bitmap + 4),
        (int)*(short *)((char *)bitmap + 6),
        (int)*(short *)((char *)bitmap + 8),
        (int)levels + 1,
        0,
        (int)fmt,
        1,
        out_tex);
    if (hr < 0) {
      ok = 0;
      FUN_00167ff0(hr, (const char *)0x2a2590);
    } else {
      ok = 1;
    }
  } else if (kind == 2) {
    fmt = *(unsigned int *)(0x2a2428 + (int)*(short *)((char *)bitmap + 0xc) * 4);
    hr = ((int (__stdcall *)(int, int, int, int, int, void **))(void *)D3DDevice_CreateCubeTexture)(
        (int)*(short *)((char *)bitmap + 4),
        (int)levels + 1,
        0,
        (int)fmt,
        1,
        out_tex);
    if (hr < 0) {
      ok = 0;
      FUN_00167ff0(hr, (const char *)0x2a2688);
    }
  } else {
    display_assert((const char *)0x261d30, (const char *)0x2a27a8, 0x5b, 1);
    system_exit(-1);
  }
  if (!*out_tex) {
    ok = 0;
  } else if (!ok) {
    /* keep texture null path below */
  }
  if (!ok || !*out_tex) {
    *out_tex = 0;
    error(2, (const char *)0x2a247c);
  }
  return ok;
}

/* FUN_00168500 (0x168500) — readable C lift (restored pre-naked). */
void FUN_00168500(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x002a27a8, 141, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1686b0 */
  /* test eax, eax -> je 0x1686b0 */
  /* test eax, eax -> je 0x1686b0 */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0x14] -> jg 0x16869c */
  D3DTexture_LockRect((void *)(uintptr_t)edx, ecx, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> jne 0x1685a6 */
  FUN_00167ff0(0, (char *)0x002a2890);
  error(0, (char *)0x002a286c);
  /* test eax, eax -> je 0x168588 */
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_width((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_get_height((void *)(uintptr_t)esi, 0);
  /* relift: test byte ptr [esi + 0xe], 2 -> je 0x1685f8 */
  bitmap_mipmap_get_pixel_data_size((void *)(uintptr_t)esi, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)edi, eax);
  bitmap_format_bits_per_pixel(0);
  display_assert((char *)0x002a2820, (char *)0x002a27a8, 177, 0);
  system_exit(0);
  rasterizer_xbox_bitmap_swizzle2d_long();
  rasterizer_xbox_bitmap_swizzle2d_word();
  rasterizer_xbox_bitmap_swizzle2d_byte();
  /* test (char)ebx, (char)ebx -> jne 0x1686af */
  error(0, (char *)0x002a27ec);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_001686c0 (0x1686c0) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b1686c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1686c0_exitfn)(int) = system_exit;
static void (*const b1686c0_c1edd80)(void) = (void *)D3DVolumeTexture_LockBox;
static void (*const b1686c0_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b1686c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b1686c0_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static short (*const b1686c0_c7d6e0)(void *bitmap, int mipmap_index) = bitmap_mipmap_width;
static short (*const b1686c0_c7d780)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_height;
static int (*const b1686c0_c7d820)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_depth;
static int (*const b1686c0_c7d960)(void *bitmap, int mipmap_index) = bitmap_mipmap_get_pixel_data_size;
static void * (*const b1686c0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static short (*const b1686c0_c7c840)(short format) = bitmap_format_bits_per_pixel;
static void (*const b1686c0_c182cf0)(void) = (void *)rasterizer_xbox_bitmap_swizzle3d_long;
static void (*const b1686c0_c182bd0)(void) = (void *)rasterizer_xbox_bitmap_swizzle3d_word;
static void (*const b1686c0_c182ac0)(void) = (void *)rasterizer_xbox_bitmap_swizzle3d_byte;

__attribute__((naked, noinline))
void FUN_001686c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "pushl %%ebx\n\t"
      "movb $1, %%bl\n\t"
      "jne .LFUN_001686c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xcb\n\t"
      "pushl $0x2a27a8\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001686c0_1:\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001686c0_15\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001686c0_15\n\t"
      "movl 0x28(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001686c0_15\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".LFUN_001686c0_2:\n\t"
      "cmpw 0x14(%%edi), %%si\n\t"
      "jg .LFUN_001686c0_12\n\t"
      "movl 0x28(%%edi), %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1edd80]\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001686c0_5\n\t"
      "pushl $0x2a2918\n\t"
      "pushl $0\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001686c0_3:\n\t"
      "pushl $0x2a286c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_001686c0_4:\n\t"
      "incl %%esi\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jne .LFUN_001686c0_2\n\t"
      "jmp .LFUN_001686c0_13\n\t"
      ".LFUN_001686c0_5:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001686c0_3\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d000]\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d6e0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c7d780]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c7d820]\n\t"
      "movb 0xe(%%edi), %%cl\n\t"
      "addl $0x20, %%esp\n\t"
      "testb $2, %%cl\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_001686c0_7\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001686c0_11\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      ".LFUN_001686c0_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d960]\n\t"
      "cdq\n\t"
      "idivl -0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "addl %%edx, %%ebx\n\t"
      "addl %%ecx, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001686c0_6\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001686c0_4\n\t"
      ".LFUN_001686c0_7:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c840]\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001686c0_10\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001686c0_9\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001686c0_8\n\t"
      "pushl $1\n\t"
      "pushl $0xf9\n\t"
      "pushl $0x2a27a8\n\t"
      "pushl $0x2a2820\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001686c0_4\n\t"
      ".LFUN_001686c0_8:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c182cf0]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001686c0_4\n\t"
      ".LFUN_001686c0_9:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c182bd0]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001686c0_4\n\t"
      ".LFUN_001686c0_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c182ac0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001686c0_11:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001686c0_4\n\t"
      ".LFUN_001686c0_12:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001686c0_14\n\t"
      ".LFUN_001686c0_13:\n\t"
      "pushl $0x2a27ec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001686c0_14:\n\t"
      "popl %%esi\n\t"
      ".LFUN_001686c0_15:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1686c0_assert), [exitfn] "m"(b1686c0_exitfn), [c1edd80] "m"(b1686c0_c1edd80), [c167ff0] "m"(b1686c0_c167ff0), [c8f390] "m"(b1686c0_c8f390), [c7d000] "m"(b1686c0_c7d000), [c7d6e0] "m"(b1686c0_c7d6e0), [c7d780] "m"(b1686c0_c7d780), [c7d820] "m"(b1686c0_c7d820), [c7d960] "m"(b1686c0_c7d960), [c8e0b0] "m"(b1686c0_c8e0b0), [c7c840] "m"(b1686c0_c7c840), [c182cf0] "m"(b1686c0_c182cf0), [c182bd0] "m"(b1686c0_c182bd0), [c182ac0] "m"(b1686c0_c182ac0)
      : "memory");
}
#else
#error "FUN_001686c0: clang naked draft required"
#endif


/* FUN_001688d0 (0x1688d0) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b1688d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1688d0_exitfn)(int) = system_exit;
static void (*const b1688d0_c1edd10)(void) = (void *)D3DCubeTexture_LockRect;
static void (*const b1688d0_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void (*const b1688d0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b1688d0_c7cdf0)(void *bitmap, short x, short y, short z, short mipmap_index) = bitmap_cube_map_address;
static short (*const b1688d0_c7d6e0)(void *bitmap, int mipmap_index) = bitmap_mipmap_width;
static short (*const b1688d0_c7d780)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_height;
static int (*const b1688d0_c7d960)(void *bitmap, int mipmap_index) = bitmap_mipmap_get_pixel_data_size;
static void * (*const b1688d0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static short (*const b1688d0_c7c840)(short format) = bitmap_format_bits_per_pixel;
static void (*const b1688d0_c1829f0)(void) = (void *)rasterizer_xbox_bitmap_swizzle2d_long;
static void (*const b1688d0_c182910)(void) = (void *)rasterizer_xbox_bitmap_swizzle2d_word;
static void (*const b1688d0_c182840)(void) = (void *)rasterizer_xbox_bitmap_swizzle2d_byte;

__attribute__((naked, noinline))
void FUN_001688d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%ebx\n\t"
      "movb $1, %%bl\n\t"
      "jne .LFUN_001688d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x114\n\t"
      "pushl $0x2a27a8\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001688d0_1:\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001688d0_15\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001688d0_15\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001688d0_15\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_001688d0_2\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_001688d0_2:\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "cmpw 0x14(%%esi), %%ax\n\t"
      "jg .LFUN_001688d0_12\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "je .LFUN_001688d0_6\n\t"
      ".LFUN_001688d0_3:\n\t"
      "cmpw $6, %%di\n\t"
      "jge .LFUN_001688d0_6\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl $0\n\t"
      "movswl %%di, %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x2a2470(,%%eax,2), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1edd10]\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001688d0_7\n\t"
      "pushl $0x2a29a8\n\t"
      "pushl $0\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001688d0_4:\n\t"
      "pushl $0x2a286c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_001688d0_5:\n\t"
      "incl %%edi\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "jne .LFUN_001688d0_3\n\t"
      ".LFUN_001688d0_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_001688d0_2\n\t"
      "jmp .LFUN_001688d0_13\n\t"
      ".LFUN_001688d0_7:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001688d0_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c7cdf0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c7d6e0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c7d780]\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "testb $2, 0xe(%%esi)\n\t"
      "je .LFUN_001688d0_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d960]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl $0x2aaaaaab, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001688d0_5\n\t"
      ".LFUN_001688d0_8:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7c840]\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001688d0_11\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001688d0_10\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001688d0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x13f\n\t"
      "pushl $0x2a27a8\n\t"
      "pushl $0x2a2820\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001688d0_5\n\t"
      ".LFUN_001688d0_9:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1829f0]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001688d0_5\n\t"
      ".LFUN_001688d0_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c182910]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001688d0_5\n\t"
      ".LFUN_001688d0_11:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c182840]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001688d0_5\n\t"
      ".LFUN_001688d0_12:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001688d0_14\n\t"
      ".LFUN_001688d0_13:\n\t"
      "pushl $0x2a27ec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001688d0_14:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001688d0_15:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1688d0_assert), [exitfn] "m"(b1688d0_exitfn), [c1edd10] "m"(b1688d0_c1edd10), [c167ff0] "m"(b1688d0_c167ff0), [c8f390] "m"(b1688d0_c8f390), [c7cdf0] "m"(b1688d0_c7cdf0), [c7d6e0] "m"(b1688d0_c7d6e0), [c7d780] "m"(b1688d0_c7d780), [c7d960] "m"(b1688d0_c7d960), [c8e0b0] "m"(b1688d0_c8e0b0), [c7c840] "m"(b1688d0_c7c840), [c1829f0] "m"(b1688d0_c1829f0), [c182910] "m"(b1688d0_c182910), [c182840] "m"(b1688d0_c182840)
      : "memory");
}
#else
#error "FUN_001688d0: clang naked draft required"
#endif


/* FUN_00168ae0 (0x168ae0) — readable C lift. */
void FUN_00168ae0(void *obj)
{
  void *p;

  texture_cache_bitmap_delete(obj);
  if (!obj)
    return;
  p = *(void **)((char *)obj + 0x28);
  if (!p)
    return;
  D3DResource_Release(p);
  *(void **)((char *)obj + 0x28) = 0;
}



/* FUN_00168b10 (0x168b10) — readable C lift. */
void FUN_00168b10(void *bitmap)
{
  int kind;

  if (!bitmap) {
    display_assert((char *)0x263768, (char *)0x2a27a8, 0x70, 1);
    system_exit(-1);
  }
  *(short *)0x325652 = 1;
  kind = (int)*(short *)((char *)bitmap + 0xa);
  if (kind == 0)
    FUN_00168500();
  else if (kind == 1)
    FUN_001686c0();
  else if (kind == 2)
    FUN_001688d0();
  else {
    display_assert((char *)0x261d30, (char *)0x2a27a8, 0x80, 1);
    system_exit(-1);
  }
  *(short *)0x325652 = 0;
}
/* FUN_00168bc0 (0x168bc0) — readable C lift. */
int FUN_00168bc0(int a, int b, int c)
{
  return ((int (__stdcall *)(int, int, int, int, int))(void *)D3DDevice_CreateVertexBuffer)(a, b, c, 0, 0);
}

/* FUN_00168be0 (0x168be0) — readable C lift. */
int FUN_00168be0(int a, int b, int c)
{
  return ((int (__stdcall *)(int, int, int, int, int))(void *)D3DDevice_CreateIndexBuffer)(a, b, c, 0, 0);
}

/* FUN_00168c40 (0x168c40) — readable C lift. */
int FUN_00168c40(int a, int b)
{
  ((void (__stdcall *)(int, int, int, int, int))D3DVertexBuffer_Lock)(a, b, 0, 0, 0);
  return 0;
}



/* FUN_00168c70 (0x168c70) — readable C lift. */
void FUN_00168c70(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
}

/* FUN_00168ca0 (0x168ca0) — readable C lift. */
int FUN_00168ca0(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
  return 0;
}

/* FUN_00168cd0 (0x168cd0) — readable C lift: create dynamic vertex buffer. */
unsigned char FUN_00168cd0(void *obj, short type, int count, void *src, int nbytes)
{
  short stride;
  unsigned char ok;
  int hr;
  void *vb;
  void *locked;

  stride = (short)FUN_00180050(type);
  if (!obj) {
    display_assert((const char *)0x2a19cc, (const char *)0x2a2b58, 0x18, 1);
    system_exit(-1);
  }
  if ((int)stride * count != nbytes && src) {
    display_assert((const char *)0x2a2b2c, (const char *)0x2a2b58, 0x19, 1);
    system_exit(-1);
  }
  ok = 1;
  if (count == 0)
    ok = 0;
  if (!*(int *)0x476ab0) {
    ok = 0;
  } else if (ok) {
    vb = 0;
    hr = D3DDevice_CreateVertexBuffer((unsigned)nbytes, 8, 0, 1, &vb);
    if (hr < 0) {
      ok = 0;
      FUN_00167ff0(hr, (const char *)0x2a2a90);
    } else {
      ok = 1;
    }
    if (!vb) {
      ok = 0;
      vb = 0;
    } else if (!ok) {
      vb = 0;
    }
    if (src) {
      if (!ok)
        goto fail;
      locked = 0;
      *(short *)0x325652 = 2;
      D3DVertexBuffer_Lock((int)vb, 0, nbytes, (int)&locked, 0);
      *(short *)0x325652 = 0;
      if (!locked) {
        ok = 0;
        locked = 0;
        goto fail;
      }
      csmemcpy(locked, src, (unsigned)nbytes);
      *(short *)obj = type;
      *(int *)((char *)obj + 4) = count;
      *(int *)((char *)obj + 8) = 0;
      *(void **)((char *)obj + 0xc) = src;
      *(void **)((char *)obj + 0x10) = vb;
      return 1;
    }
    if (ok)
      return ok;
  fail:
    csmemset(obj, 0, 0x14);
    error(2, (const char *)0x2a2a54);
  }
  return ok;
}

/* FUN_00168e40 (0x168e40) — readable C lift. */
void FUN_00168e40(void *obj)
{
  void *p;

  if (!obj)
    return;
  p = *(void **)((char *)obj + 0x10);
  if (!p)
    return;
  D3DResource_Release(p);
  *(void **)((char *)obj + 0x10) = 0;
}

/* FUN_00168e70 (0x168e70) — readable C lift from XBE leaf. */
unsigned char FUN_00168e70(void *obj, short type, int count, void *src)
{
  int nbytes;
  int hr;
  void *ib;
  unsigned char ok;

  if (!obj) {
    display_assert((char *)0x2a2c90, (char *)0x2a2b58, 0x73, 1);
    system_exit(-1);
  }
  if (!src) {
    display_assert((char *)0x2a2c84, (char *)0x2a2b58, 0x74, 1);
    system_exit(-1);
  }
  if (count <= 0) {
    display_assert((char *)0x257c5c, (char *)0x2a2b58, 0x75, 1);
    system_exit(-1);
  }
  if (type == 0)
    nbytes = count * 6;
  else if (type == 1)
    nbytes = count * 2 + 4;
  else {
    display_assert((char *)0x2a0c9c, (char *)0x2a2b58, 0x80, 1);
    system_exit(-1);
    nbytes = 0;
  }
  if (!*(int *)0x476ab0)
    goto fail;
  ib = 0;
  hr = ((int (__stdcall *)(int, int, int, int, void **))(void *)D3DDevice_CreateIndexBuffer)(
      nbytes, 8, 0x65, 1, &ib);
  if (hr < 0) {
    ok = 0;
    FUN_00167ff0(hr, (const char *)0x2a2ba0);
  } else {
    ok = 1;
  }
  if (!ib) {
    ok = 0;
    ib = 0;
    goto fail_clear;
  }
  if (!ok) {
    ib = 0;
    goto fail_clear;
  }
  if (!*(int *)((char *)ib + 4))
    goto fail;
  csmemcpy(*(void **)((char *)ib + 4), src, (unsigned)nbytes);
  *(short *)obj = type;
  *(int *)((char *)obj + 4) = count;
  *(void **)((char *)obj + 8) = src;
  *(void **)((char *)obj + 0xc) = ib;
  return 1;

fail:
  ok = 0;
fail_clear:
  csmemset(obj, 0, 0x10);
  error(2, (const char *)0x2a2c48);
  return ok;
}



/* _rasterizer_dynamic_unlit_geometry_draw (0x168fd0) — readable C lift. */
void _rasterizer_dynamic_unlit_geometry_draw(void *obj)
{
  void *p;

  if (!obj)
    return;
  p = *(void **)((char *)obj + 0xc);
  if (!p)
    return;
  D3DResource_Release(p);
  *(void **)((char *)obj + 0xc) = 0;
}


/* FUN_00169200 (0x169200) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b169200_xfrmpt)(float *, float *, float *) = matrix_transform_point;

__attribute__((naked, noinline))
void FUN_00169200(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fcomps 0x2533c0\n\t"
      "xorb %%cl, %%cl\n\t"
      "pushl %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00169200_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw 0x5a5bfa, %%si\n\t"
      "movl 0x5a5bf8, %%edi\n\t"
      "movl 0x5a5bf4, %%edx\n\t"
      "subw 0x5a5bf6, %%si\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a5c2c\n\t"
      "subl %%edx, %%edi\n\t"
      "call *%[xfrmpt]\n\t"
      "flds 0x5a5d84\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x5a5d74\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d64\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d94\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x5a5d88\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds 0x5a5d78\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d68\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d98\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "flds 0x5a5d60\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5a5d74\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00169200_2\n\t"
      "flds 0x5a5d8c\n\t"
      "movswl %%si, %%edx\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "flds 0x5a5d7c\n\t"
      "movswl %%di, %%eax\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d6c\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d9c\n\t"
      "fdivrs 0x2533c8\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "flds 0x5a5d80\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "flds 0x5a5d70\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d60\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d90\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds 0x2533c8\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fsubs 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%ebx)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00169200_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00169200_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "popl %%edi\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "popl %%esi\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x4(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00169200_2:\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00169200_3:\n\t"
      "popl %%edi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [xfrmpt] "m"(b169200_xfrmpt)
      : "memory");
}
#else
#error "FUN_00169200: clang naked draft required"
#endif


/* FUN_00169650 (0x169650) — readable C lift. */
int FUN_00169650(int a, int b, int c)
{
  ((void (__stdcall *)(int, int, int))(void *)D3DDevice_SetVertexData2f)(a, b, c);
  return 0;
}

/* FUN_00169670 (0x169670) — XBE naked draft (batch 372). */
#if defined(__clang__)
static void __stdcall (*const b169670_c1ed2c0)(uint32_t reg, float a, float b, float c, float d) = (void *)D3DDevice_SetVertexData4f;

__attribute__((naked, noinline))
void FUN_00169670(int a0, int a1, int a2, int a3, int a4, int a5)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ed2c0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1ed2c0] "m"(b169670_c1ed2c0)
      : "memory");
}
#else
#error "FUN_00169670: clang naked draft required"
#endif


/* FUN_001696d0 (0x1696d0) — readable C lift (restored pre-naked). */
void FUN_001696d0(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1696fd */
  display_assert((char *)0x0026184c, (char *)0x002a2ca0, 323, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x169726 */
  display_assert((char *)0x0029dc40, (char *)0x002a2ca0, 324, 0);
  system_exit(0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1010101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(38, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae8] = 0xc0000000 */
  /* mem[0x005a5ac0] = 0x19110000 */
  /* mem[0x005a5b28] = 0x100c0 */
  /* mem[0x005a5ae0] = 0x18 */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00158140(0, 0, 0, 0, 0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);

  (void)eax;
  (void)esi;
}


/* FUN_00169a50 (0x169a50) — readable C lift (restored pre-naked). */
void FUN_00169a50(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0x169a69 */
  /* cmp (int16_t)edi, 8 -> jl 0x169a89 */
  display_assert((char *)0x002a3090, (char *)0x002a2ca0, 427, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x169a97 */
  /* cmp (int16_t)esi, 8 -> jl 0x169ab7 */
  display_assert((char *)0x002a3048, (char *)0x002a2ca0, 428, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x169ae0 */
  display_assert((char *)0x0029dc40, (char *)0x002a2ca0, 429, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x169fb2 */
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(38, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5ae8] = 0xff000000 */
  /* mem[0x005a5ac0] = 0x8a009a0 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0xaa00ba0 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0x1c110c11 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ae0] = 0xc */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)edi, 4 -> jl 0x169d50 */
  FUN_00158140(0, 0, 0, 0, 0);
  /* mem[0x005a5ae8] = edx */
  rasterizer_set_pixel_shader((void *)0);
  D3DDevice_Begin(0);
  /* test (char)eax, (char)eax -> je 0x169e00 */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169e24 */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169e4e */
  FUN_00167ff0(0, (char *)0x002a2f48);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169e72 */
  FUN_00167ff0(0, (char *)0x002a2f04);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169e9c */
  FUN_00167ff0(0, (char *)0x002a2e88);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169ec0 */
  FUN_00167ff0(0, (char *)0x002a2e44);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169eea */
  FUN_00167ff0(0, (char *)0x002a2dc8);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169f0e */
  FUN_00167ff0(0, (char *)0x002a2d84);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169f38 */
  FUN_00167ff0(0, (char *)0x002a2d08);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x169f58 */
  FUN_00167ff0(0, (char *)0x0029f728);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x169fb2 */
  error(0, (char *)0x002a2cd8);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00169fd0 (0x169fd0) — readable C lift (restored pre-naked). */
void FUN_00169fd0(int *param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16a002 */
  display_assert((char *)0x0029dc40, (char *)0x002a2ca0, 583, 0);
  system_exit(0);
  normalize3d((float *)0);
  /* relift: relift: fld qword ptr [0x25b3f0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16a0a0 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  FUN_0017ffc0((float *)(uintptr_t)eax, edx);
  FUN_00169200();
  /* test (char)eax, (char)eax -> je 0x16a8ec */
  floor(0.0f);
  floor(0.0f);
  /* relift: relift: fld dword ptr [0x282d3c] */
  /* test (char)eax, 0x41 -> jne 0x16a8ec */
  /* test (char)eax, 0x41 -> jne 0x16a8ec */
  /* test (char)eax, 0x41 -> jne 0x16a8ec */
  FUN_00178b40(56, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1000000 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5b6c] = ebx */
  /* mem[0x005a5ae4] = 0x1100 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2f(ebx, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  FUN_00178b40(56, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1000000 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ac0] = 0x18200000 */
  /* mem[0x005a5b28] = 0x200c0 */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_End();
  FUN_001696d0();
  FUN_001696d0();
  FUN_00169a50();
  FUN_00178b40(56, 0, 0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  SetRenderStateSmart(67, 0x00010101);
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 770);
  SetRenderStateSmart(63, 0);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 1 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5ae8] = 0xb0b080 */
  /* mem[0x005a5b08] = 0xffffff */
  /* mem[0x005a5ac0] = 0x48200000 */
  /* mem[0x005a5b28] = 0xc0 */
  /* mem[0x005a5b4c] = 0x3c011c02 */
  /* mem[0x005a5b78] = 0xc00 */
  /* mem[0x005a5ae0] = 0xc080000 */
  /* mem[0x005a5ae4] = 0x1400 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  /* test (char)ebx, (char)ebx -> je 0x16a717 */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a74b */
  FUN_00167ff0(0, (char *)0x002a3280);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a76f */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a7a9 */
  FUN_00167ff0(0, (char *)0x002a3220);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a7cd */
  FUN_00167ff0(0, (char *)0x002a2f04);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a7fb */
  FUN_00167ff0(0, (char *)0x002a31c0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a81f */
  FUN_00167ff0(0, (char *)0x002a2e44);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a84d */
  FUN_00167ff0(0, (char *)0x002a3160);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a871 */
  FUN_00167ff0(0, (char *)0x002a2d84);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a896 */
  FUN_00167ff0(0, (char *)0x002a3100);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x16a8b4 */
  FUN_00167ff0(0, (char *)0x0029f728);
  error(0, (char *)0x002a30d4);
  /* cmp esi, 0x52 -> jge 0x16a91b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16a929 */
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x16a93e */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x16a94a */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x16a956 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16a962 */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x16a96e */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x16a97a */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x16a986 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16a992 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16a99e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16a9aa */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16a9b6 */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x16a9c5 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x16a9d4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16a9e3 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x16a9f2 */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x16aa01 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x16aa10 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x16aa1f */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x16aa2e */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x16aa3d */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x16aa4c */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x16aa5b */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x16aa6a */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x16aa79 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x16aa88 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x16aa97 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x16aaa5 */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x16aabc */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x16aac9 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x16aad6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x16aae3 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x16aaf0 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_0016ab00 (0x16ab00) — readable C lift (restored pre-naked). */
void FUN_0016ab00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)edi, 3 -> jl 0x16ab35 */
  display_assert((char *)0x002a3330, (char *)0x002a3380, 106, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x16ab40 */
  /* cmp (int16_t)ebx, 9 -> jl 0x16ab5d */
  display_assert((char *)0x002a32e8, (char *)0x002a3380, 107, 0);
  system_exit(0);
  /* mem[0x005a5af0] = eax */
  /* mem[0x005a5aec] = esi */
  /* mem[0x005a5b54] = edx */
  /* mem[0x005a5b60] = 0x8040b1d */
  /* mem[0x005a5b8c] = ecx */
  /* mem[0x005a5b64] = eax */
  /* mem[0x005a5b60] = ecx */
  /* mem[0x005a5b8c] = 0x800 */
  /* mem[0x005a5b64] = 0x8040b1d */
  /* mem[0x005a5b90] = ecx */
  /* mem[0x005a5ae0] = 0x330c0300 */
  /* mem[0x005a5ae4] = 0x1800 */
  /* mem[0x005a5afc] = edx */
  /* mem[0x005a5b1c] = eax */
  /* mem[0x005a5b6c] = edx */
  /* mem[0x005a5b70] = eax */
  /* mem[0x005a5ae0] = 0x340f010d */
  /* mem[0x005a5ae4] = 0xc111800 */
  /* relift: relift: mov (char)eax, byte ptr [0x325173] */
  /* test (char)eax, (char)eax -> je 0x16ada3 */
  /* mem[0x005a5b98] = 0x18421 */
  /* mem[0x005a5b94] = 0x11008 */
  /* mem[0x005a5ae8] = 0xff0000 */
  /* mem[0x005a5b08] = 0xff00 */
  /* mem[0x005a5ac0] = 0xa200000 */
  /* mem[0x005a5b28] = 0xc0 */
  /* mem[0x005a5b48] = 0xa020a01 */
  /* mem[0x005a5b74] = 0x30cd */
  /* mem[0x005a5ac4] = 0x1c200000 */
  /* mem[0x005a5b2c] = 0x90 */
  /* mem[0x005a5b4c] = 0x4200c01 */
  /* mem[0x005a5b78] = 0x400 */
  /* mem[0x005a5ac8] = 0xc200d15 */
  /* mem[0x005a5b30] = 0xcd */
  /* mem[0x005a5b50] = 0x3c201c01 */
  /* mem[0x005a5b7c] = ecx */
  /* mem[0x005a5b80] = 0x900 */
  /* mem[0x005a5b58] = 0xb05040c */
  /* mem[0x005a5b84] = 0xb4 */
  /* mem[0x005a5b5c] = 0x22014e1 */
  /* mem[0x005a5b88] = 0xd00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov byte ptr [0x325173], 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6c8] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6d4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6f4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb72c] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb738] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb764] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb73c] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb768] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb744] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb748] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6b8] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = esi */
  /* cmp esi, 0x52 -> jge 0x16af0f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16af22 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x16af3f */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x16af4f */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x16af5f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16af6f */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x16af7f */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x16af8f */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x16af9f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16afaf */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16afbf */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16afcf */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16afdf */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x16aff2 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x16b005 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16b018 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x16b02b */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x16b03e */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x16b051 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x16b064 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x16b077 */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x16b08a */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x16b09d */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x16b0b0 */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x16b0c3 */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x16b0d6 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x16b0e9 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x16b0fc */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x16b10a */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x16b120 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x16b131 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x16b142 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x16b153 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x16b160 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_0016b180 (0x16b180) — readable C lift. */
void FUN_0016b180(int flag)
{
  if (!*(unsigned char *)0x3256c4)
    return;
  *(unsigned char *)0x325173 = 1;
  *(unsigned char *)0x47e002 = (unsigned char)flag;
  if (flag)
    FUN_0016f910(1);
  else
    FUN_0016f910(2);
}



/* FUN_0016b1c0 (0x16b1c0) — readable C lift. */
void FUN_0016b1c0(void)
{
  int *p;

  if (!*(unsigned char *)0x3256c4)
    return;
  if (!*(int *)0x47dff8) {
    display_assert((char *)0x2a33b8, (char *)0x2a3380, 0x5d3, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x47e004)
    FUN_00165fc0();
  p = *(int **)0x47dff8;
  if (*(signed char *)p < 0) {
    if (!*(unsigned char *)0x47e005) {
      FUN_00158ae0(2);
      ((void(*)(void))rasterizer_set_frustum_z)();
    }
  }
  *(int *)0x47dff8 = 0;
}
/* FUN_0016b240 (0x16b240) — readable C lift. */
void FUN_0016b240(void)
{
  if (!*(unsigned char *)0x3256c4)
    return;
  if (*(unsigned char *)0x47e002)
    FUN_0016fa40(1);
  else
    FUN_0016fa40(2);
}



/* FUN_0016b270 (0x16b270) — readable C lift. */
void FUN_0016b270(int a0, float a1, float a2, float a3)
{
  char *g;

  g = *(char **)0x47e4d0;
  if (g) {
    *(int *)g = a0;
    *(float *)(g + 4) = a1;
    *(float *)(g + 8) = a2;
    *(float *)(g + 0xc) = a3;
  }
}

/* FUN_0016b2b0 (0x16b2b0) — readable C lift (restored pre-naked). */
void FUN_0016b2b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a3380, 245, ebx);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16beca */
  /* test eax, eax -> jne 0x16b31c */
  display_assert((char *)0x002a33b8, (char *)0x002a3380, 251, ebx);
  system_exit(0);
  display_assert((char *)0x002a18b8, (char *)0x002a3380, 252, ebx);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZBias(0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [esi + 0x28], 1 -> je 0x16b543 */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [esi + 0x28], 4 -> jne 0x16b65b */
  /* relift: relift: mov (char)eax, byte ptr [0x47e003] */
  /* test (char)eax, (char)eax -> je 0x16b637 */
  /* relift: cmp word ptr [eax + 0x50], 0 -> jle 0x16b647 */
  /* relift: cmp dword ptr [esi + 0x330], -1 -> jne 0x16b65b */
  /* test ebx, ebx -> je 0x16b66c */
  rasterizer_widget_draw_sprite2d(0);
  FUN_00178b40(10, 0, 0);
  /* relift: cmp word ptr [0x3256ba], 1 -> jl 0x16b69e */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x5a5dbc] */
  /* test (char)eax, 0x41 -> je 0x16b7d1 */
  display_assert((char *)0x002a3538, (char *)0x002a3380, 436, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16b804 */
  display_assert((char *)0x002a1e14, (char *)0x002a3380, 437, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5de8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16b837 */
  display_assert((char *)0x0029f040, (char *)0x002a3380, 438, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16b86a */
  display_assert((char *)0x0029f008, (char *)0x002a3380, 439, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d4] */
  /* test (char)eax, (char)eax -> je 0x16bd8f */
  /* relift: test byte ptr [ecx], 4 -> jne 0x16bd8f */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5dc8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16b8e6 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16b945 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: mov (char)eax, byte ptr [0x5a5da8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x5a5dd8] */
  /* relift: relift: fld dword ptr [0x5a5ddc] */
  /* relift: relift: fld dword ptr [0x5a5de0] */
  /* test (char)eax, 0x41 -> jne 0x16ba04 */
  /* test (char)eax, 0x41 -> jne 0x16ba3c */
  /* test (char)eax, 0x41 -> jne 0x16ba74 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16baa7 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16bad7 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16bb07 */
  /* relift: relift: fld dword ptr [0x5a5dac] */
  /* relift: relift: fld dword ptr [0x5a5db0] */
  /* relift: relift: fld dword ptr [0x5a5db4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bb4b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a3510, (char *)0x002a3380, 478, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bb8b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a34ec, (char *)0x002a3380, 479, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bbcb */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a34c8, (char *)0x002a3380, 480, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bc0b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a34a4, (char *)0x002a3380, 481, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bc4b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a3480, (char *)0x002a3380, 482, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bc8b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a345c, (char *)0x002a3380, 483, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bccb */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a342c, (char *)0x002a3380, 484, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bd0b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a33fc, (char *)0x002a3380, 485, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bd4b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a33cc, (char *)0x002a3380, 486, 0);
  system_exit(0);
  FUN_000d1c90((float *)(uintptr_t)edx);
  FUN_000d1dd0((float *)(uintptr_t)eax);
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  FUN_0016ab00();
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb720] = 0xa021819 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb74c] = 0x20cd */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = 0xc111a00 */
  ((void(*)(void))FUN_0015e650)();
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb720] = 0xa020a01 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb74c] = 0x30cd */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = 0xc111800 */
  /* mem[0x005a555c] = eax */
  /* mem[0x005a54e0] = edx */
  /* mem[0x005a54dc] = ecx */
  ((void(*)(void))FUN_0017ed90)();
  /* mem[0x005a54d8] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_0016bed0 (0x16bed0) — XBE naked draft (batch 318). */
#if defined(__clang__)
static void (*const b16bed0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b16bed0_exitfn)(int) = system_exit;
static void (*const b16bed0_c158ae0)(int mode) = FUN_00158ae0;
static void (*const b16bed0_c156c30)(float near_z, float far_z) = rasterizer_set_frustum_z;
static void (*const b16bed0_c156710)(void *a1) = rasterizer_set_model_skinning;
static void (*const b16bed0_c156ab0)(void *lighting) = rasterizer_set_model_lighting;
static void (*const b16bed0_c167ee0)(void) = (void *)FUN_00167ee0;

__attribute__((naked, noinline))
void FUN_0016bed0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x3256c4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0016bed0_11\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0016bed0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x24b\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x29f510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0016bed0_1:\n\t"
      "cmpb $0, (%%edi)\n\t"
      "pushl %%ebx\n\t"
      "movb 0xc(%%ebp), %%bl\n\t"
      "jns .LFUN_0016bed0_2\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0016bed0_2\n\t"
      "pushl $1\n\t"
      "call *%[c158ae0]\n\t"
      "movl 0x3256a0, %%eax\n\t"
      "movl 0x32569c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c156c30]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0016bed0_2:\n\t"
      "movb 0x3256f9, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, 0x47dff8\n\t"
      "movb $0, 0x47dffc\n\t"
      "movb %%bl, 0x47e005\n\t"
      "je .LFUN_0016bed0_3\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .LFUN_0016bed0_3\n\t"
      "movl $1, %%ecx\n\t"
      "cmpw %%cx, 0x8c(%%edi)\n\t"
      "jne .LFUN_0016bed0_3\n\t"
      "flds 0x90(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0016bed0_3\n\t"
      "movw %%cx, 0x47e000\n\t"
      "jmp .LFUN_0016bed0_5\n\t"
      ".LFUN_0016bed0_3:\n\t"
      "movl $2, %%eax\n\t"
      "cmpw %%ax, 0x8c(%%edi)\n\t"
      "jne .LFUN_0016bed0_4\n\t"
      "movw %%ax, 0x47e000\n\t"
      "jmp .LFUN_0016bed0_5\n\t"
      ".LFUN_0016bed0_4:\n\t"
      "movl 0x5a5550, %%ebx\n\t"
      "leal 0x8(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c156710]\n\t"
      "movl 0x5a5550, %%esi\n\t"
      "leal 0x10(%%edi), %%eax\n\t"
      "subl %%ebx, %%esi\n\t"
      "movl 0x5a5554, %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c156ab0]\n\t"
      "movl 0x5a5560, %%eax\n\t"
      "movl 0x5a5554, %%ecx\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, 0x5a5560\n\t"
      "movl 0x5a5564, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "subl %%ebx, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, 0x5a5564\n\t"
      "movw $0, 0x47e000\n\t"
      "popl %%esi\n\t"
      ".LFUN_0016bed0_5:\n\t"
      "cmpw $0, 0x5a5dc4\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0016bed0_7\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_0016bed0_7\n\t"
      "testb $0x40, %%al\n\t"
      "je .LFUN_0016bed0_6\n\t"
      "flds 0x5a5dd0\n\t"
      "fmuls 0x5a5bd0\n\t"
      "flds 0x5a5dcc\n\t"
      "fmuls 0x5a5bcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5dc8\n\t"
      "fmuls 0x5a5bc8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x5a5dd4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0016bed0_7\n\t"
      ".LFUN_0016bed0_6:\n\t"
      "movb $1, 0x47e003\n\t"
      "jmp .LFUN_0016bed0_8\n\t"
      ".LFUN_0016bed0_7:\n\t"
      "movb $0, 0x47e003\n\t"
      ".LFUN_0016bed0_8:\n\t"
      "movb 0x47e002, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0016bed0_9\n\t"
      "pushl %%edi\n\t"
      "call *%[c167ee0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, 0x47e004\n\t"
      "jne .LFUN_0016bed0_10\n\t"
      ".LFUN_0016bed0_9:\n\t"
      "movb $0, 0x47e004\n\t"
      ".LFUN_0016bed0_10:\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "popl %%edi\n\t"
      "jne .LFUN_0016bed0_11\n\t"
      "incl 0x5a54d4\n\t"
      ".LFUN_0016bed0_11:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b16bed0_assert), [exitfn] "m"(b16bed0_exitfn), [c158ae0] "m"(b16bed0_c158ae0), [c156c30] "m"(b16bed0_c156c30), [c156710] "m"(b16bed0_c156710), [c156ab0] "m"(b16bed0_c156ab0), [c167ee0] "m"(b16bed0_c167ee0)
      : "memory");
}
#else
#error "FUN_0016bed0: clang naked draft required"
#endif


/* FUN_0016c090 (0x16c090) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void * (*const b16c090_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b16c090_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b16c090_exitfn)(int) = system_exit;
static void (*const b16c090_c190a50)(void) = (void *)shader_type_is_valid_for_model;
static char (*const b16c090_c1908a0)(void *shader) = shader_is_decal;
static void * (*const b16c090_c184360)(void) = rasterizer_secondary_geometry_group_new;
static void * (*const b16c090_c184330)(void) = rasterizer_transparent_geometry_group_new;
static short (*const b16c090_c1844b0)(unsigned int group) = rasterizer_transparent_geometry_group_to_presorted_index;
static void (*const b16c090_c174ce0)(void) = (void *)FUN_00174ce0;
static void (*const b16c090_c174d10)(void *group, int dirty) = rasterizer_transparent_geometry_group_draw;
static void (*const b16c090_c1749b0)(void) = (void *)FUN_001749b0;
static void (*const b16c090_c182590)(int data, int size) = (void *)rasterizer_memory_pool_copy;
static void (*const b16c090_c17ed90)(void) = (void *)FUN_0017ed90;
static void (*const b16c090_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0016c090(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movb 0x3256c4, %%al\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "je .LFUN_0016c090_29\n\t"
      "movb 0x3256c5, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0016c090_29\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0016c090_1\n\t"
      "cmpw $4, 0x24(%%edi)\n\t"
      "jne .LFUN_0016c090_1\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_0016c090_1\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0016c090_2\n\t"
      ".LFUN_0016c090_1:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_0016c090_2:\n\t"
      "cmpw $1, 0x47e000\n\t"
      "jne .LFUN_0016c090_4\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0016c090_3\n\t"
      "cmpw $4, 0x24(%%edi)\n\t"
      "jne .LFUN_0016c090_3\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x28(%%eax)\n\t"
      "jne .LFUN_0016c090_4\n\t"
      ".LFUN_0016c090_3:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0016c090_5\n\t"
      ".LFUN_0016c090_4:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_0016c090_5:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0016c090_27\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0016c090_6\n\t"
      "pushl $1\n\t"
      "pushl $0x515\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x2a18b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0016c090_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x24(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c190a50]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0016c090_7\n\t"
      "pushl $1\n\t"
      "pushl $0x516\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x2a3618\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0016c090_7:\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0016c090_8\n\t"
      "pushl $1\n\t"
      "pushl $0x517\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x2a1774\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0016c090_8:\n\t"
      "movl 0x47dff8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0016c090_9\n\t"
      "pushl $1\n\t"
      "pushl $0x518\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x2a33b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0016c090_9:\n\t"
      "movl 0x47dff8, %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "je .LFUN_0016c090_11\n\t"
      "pushl %%edi\n\t"
      "call *%[c1908a0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0016c090_10\n\t"
      "orl $3, %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      ".LFUN_0016c090_10:\n\t"
      "testb $2, %%bl\n\t"
      "je .LFUN_0016c090_11\n\t"
      "movl $0x47df58, %%ebx\n\t"
      "movl $0xffffffff, 0x47dfe8\n\t"
      "jmp .LFUN_0016c090_15\n\t"
      ".LFUN_0016c090_11:\n\t"
      "cmpw $1, 0x47e000\n\t"
      "jne .LFUN_0016c090_12\n\t"
      "cmpw $4, 0x24(%%edi)\n\t"
      "je .LFUN_0016c090_12\n\t"
      "call *%[c184360]\n\t"
      "jmp .LFUN_0016c090_13\n\t"
      ".LFUN_0016c090_12:\n\t"
      "call *%[c184330]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_0016c090_13:\n\t"
      "movl 0x28(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LFUN_0016c090_14\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1844b0]\n\t"
      "movw %%ax, 0x8(%%esi)\n\t"
      "leal 0x94(%%ebx), %%edx\n\t"
      "leal 0x96(%%ebx), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".LFUN_0016c090_14:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0016c090_26\n\t"
      ".LFUN_0016c090_15:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x47dff8, %%eax\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ebx)\n\t"
      "cmpw $0, 0x8c(%%eax)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jne .LFUN_0016c090_16\n\t"
      "movl 0x24(%%ebp), %%esi\n\t"
      "movl $0, 0x8(%%ebx)\n\t"
      "movl (%%esi), %%esi\n\t"
      "leal 0x74(%%ebx), %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl 0x24(%%ebp), %%esi\n\t"
      "movl 0x4(%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ecx)\n\t"
      "movl 0x24(%%ebp), %%esi\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "movl %%esi, 0x8(%%ecx)\n\t"
      "jmp .LFUN_0016c090_18\n\t"
      ".LFUN_0016c090_16:\n\t"
      "movl 0x98(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_0016c090_17\n\t"
      "pushl $1\n\t"
      "pushl $0x54c\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x2a35e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x47dff8, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0016c090_17:\n\t"
      "movl 0x98(%%eax), %%edx\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "leal 0x9c(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "leal 0x74(%%ebx), %%edx\n\t"
      "movl %%edx, %%esi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      ".LFUN_0016c090_18:\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "movw %%cx, 0x10(%%ebx)\n\t"
      "movl %%edi, 0xc(%%ebx)\n\t"
      "leal 0x8c(%%eax), %%esi\n\t"
      "leal 0x14(%%ebx), %%edi\n\t"
      "movl $0xa, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x44(%%ebx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x48(%%ebx)\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x50(%%ebx)\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x54(%%ebx)\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x58(%%ebx)\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, 0x4c(%%ebx)\n\t"
      "movl %%esi, 0x5c(%%ebx)\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw $1, 0x47e000\n\t"
      "flds (%%edx)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "flds 0x4(%%edx)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "flds 0x8(%%edx)\n\t"
      "leal 0x80(%%ebx), %%edx\n\t"
      "fsubs 0x5a5bd0\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%edx)\n\t"
      "fchs\n\t"
      "fstps 0x70(%%ebx)\n\t"
      "movl 0xc4(%%eax), %%edx\n\t"
      "movl %%edx, 0x3c(%%ebx)\n\t"
      "movl 0xc8(%%eax), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ecx, 0x40(%%ebx)\n\t"
      "fstp %%st(0)\n\t"
      "movw %%di, 0x94(%%ebx)\n\t"
      "movw %%di, 0x96(%%ebx)\n\t"
      "jne .LFUN_0016c090_19\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "cmpw $4, 0x24(%%edx)\n\t"
      "je .LFUN_0016c090_19\n\t"
      "movl 0x98(%%eax), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "movl %%ecx, 0x98(%%ebx)\n\t"
      "jne .LFUN_0016c090_20\n\t"
      "pushl $1\n\t"
      "pushl $0x56d\n\t"
      "pushl $0x2a3380\n\t"
      "pushl $0x2a35ac\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x47dff8, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0016c090_20\n\t"
      ".LFUN_0016c090_19:\n\t"
      "movl %%esi, 0x98(%%ebx)\n\t"
      ".LFUN_0016c090_20:\n\t"
      "movb 0x5a5570, %%cl\n\t"
      "movb %%cl, 0x9d(%%ebx)\n\t"
      "testb $2, -0xc(%%ebp)\n\t"
      "je .LFUN_0016c090_21\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, 0x60(%%ebx)\n\t"
      "movw 0xc(%%eax), %%cx\n\t"
      "leal 0x10(%%eax), %%edx\n\t"
      "addl $0x84, %%eax\n\t"
      "movw %%cx, 0x64(%%ebx)\n\t"
      "movl %%edx, 0x68(%%ebx)\n\t"
      "movl %%eax, 0x6c(%%ebx)\n\t"
      "call *%[c174ce0]\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c174d10]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1749b0]\n\t"
      "movb $1, 0x325173\n\t"
      "jmp .LFUN_0016c090_23\n\t"
      ".LFUN_0016c090_21:\n\t"
      "movb 0x47dffc, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0016c090_22\n\t"
      "movswl 0xc(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c182590]\n\t"
      "movl %%eax, 0x47df54\n\t"
      "movl 0x47dff8, %%eax\n\t"
      "movw 0xc(%%eax), %%cx\n\t"
      "addl $0x10, %%eax\n\t"
      "pushl $0x74\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, 0x47df50\n\t"
      "call *%[c182590]\n\t"
      "movl 0x47dff8, %%edx\n\t"
      "addl $0x84, %%edx\n\t"
      "pushl $8\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x47df4c\n\t"
      "call *%[c182590]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, 0x47df48\n\t"
      "movb $1, 0x47dffc\n\t"
      ".LFUN_0016c090_22:\n\t"
      "movl 0x47df54, %%eax\n\t"
      "movw 0x47df50, %%cx\n\t"
      "movl 0x47df4c, %%edx\n\t"
      "movl %%eax, 0x60(%%ebx)\n\t"
      "movl 0x47df48, %%eax\n\t"
      "movw %%cx, 0x64(%%ebx)\n\t"
      "movl %%edx, 0x68(%%ebx)\n\t"
      "movl %%eax, 0x6c(%%ebx)\n\t"
      ".LFUN_0016c090_23:\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "jne .LFUN_0016c090_25\n\t"
      "movl 0x5a54f0, %%esi\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x5a54e8, %%edx\n\t"
      "movl 0x5a54ec, %%ecx\n\t"
      "incl %%esi\n\t"
      "addl %%eax, %%edx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%esi, 0x5a54f0\n\t"
      "movl %%edx, 0x5a54e8\n\t"
      "jle .LFUN_0016c090_24\n\t"
      "movl %%eax, 0x5a54ec\n\t"
      ".LFUN_0016c090_24:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17ed90]\n\t"
      "movl 0x5a54e4, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a54e4\n\t"
      ".LFUN_0016c090_25:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0016c090_26:\n\t"
      "movb 0x47e006, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0016c090_25\n\t"
      "pushl $0x2a1744\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movb $1, 0x47e006\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0016c090_27:\n\t"
      "movl 0x28(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0016c090_28\n\t"
      "movw $0xffff, 0x8(%%eax)\n\t"
      "movl $0, (%%eax)\n\t"
      "movl $0, 0x4(%%eax)\n\t"
      ".LFUN_0016c090_28:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0016c090_29:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1906b0] "m"(b16c090_c1906b0), [assert] "m"(b16c090_assert), [exitfn] "m"(b16c090_exitfn), [c190a50] "m"(b16c090_c190a50), [c1908a0] "m"(b16c090_c1908a0), [c184360] "m"(b16c090_c184360), [c184330] "m"(b16c090_c184330), [c1844b0] "m"(b16c090_c1844b0), [c174ce0] "m"(b16c090_c174ce0), [c174d10] "m"(b16c090_c174d10), [c1749b0] "m"(b16c090_c1749b0), [c182590] "m"(b16c090_c182590), [c17ed90] "m"(b16c090_c17ed90), [c8f390] "m"(b16c090_c8f390)
      : "memory");
}
#else
#error "FUN_0016c090: clang naked draft required"
#endif


/* FUN_0016c5a0 (0x16c5a0) — readable C lift (restored pre-naked). */
void FUN_0016c5a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16c5d2 */
  display_assert((char *)0x0029dc40, (char *)0x002a3380, 671, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16d9c9 */
  /* test eax, eax -> jne 0x16c608 */
  display_assert((char *)0x002a33b8, (char *)0x002a3380, 675, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16c62f */
  display_assert((char *)0x002a18b8, (char *)0x002a3380, 676, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax + 0x24], 0xa -> jne 0x16c694 */
  FUN_001906b0((void *)(uintptr_t)eax, 10);
  /* cmp (int16_t)eax, 1 -> jl 0x16c694 */
  /* cmp (int16_t)eax, 4 -> jg 0x16c694 */
  /* test ecx, ecx -> je 0x16c694 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0016c090();
  /* test esi, esi -> je 0x16c6e1 */
  rasterizer_memory_pool_alloc(0, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x47e000] */
  /* cmp (int16_t)eax, 1 -> jne 0x16c74f */
  /* relift: cmp word ptr [esi + 0x24], 4 -> je 0x16c717 */
  display_assert((char *)0x002a3974, (char *)0x002a3380, 729, 0);
  system_exit(0);
  FUN_0017cbd0(0, 0, 0, 0, 0, 0, 0, (float *)(uintptr_t)ecx, 0);
  FUN_001592e0(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x16d9b3 */
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x16c788 */
  FUN_0016b2b0();
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [0x47e000], 0 -> je 0x16c7cb */
  display_assert((char *)0x002a393c, (char *)0x002a3380, 771, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16c880 */
  /* relift: test byte ptr [ecx], 8 -> je 0x16c885 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZBias(edx);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  /* relift: test byte ptr [esi + 0x28], 4 -> jne 0x16c968 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

