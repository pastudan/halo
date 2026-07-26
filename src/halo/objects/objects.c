#if defined(_MSC_VER) && !defined(__clang__)
#include <math.h>
#else
#include "../../x87_math.h"
float sinf(float x);
float cosf(float x);
double atan2(double y, double x);
float sqrtf(float x);
float fabsf(float x);
double fabs(double x);
double pow(double x, double y);
#endif

/* Address-based function call macros for callees without proper kb.json entries */
#define XCALL(addr, type) ((type)(addr))
#define CALL_FUN_001d0581() XCALL(0x1d0581, int(*)(void))()
#define CALL_thunk_FUN_001029a0(a) XCALL(0x8e2f0, void(*)(int))(a)
#define CALL_FUN_000b65c0(a) XCALL(0xb65c0, int(*)(unsigned short))(a)
#define CALL_FUN_000b6740(a,b) XCALL(0xb6740, void(*)(unsigned short,void*))(a,b)
#define CALL_FUN_000b7e30(a) XCALL(0xb7e30, void*(*)(unsigned short))(a)
#define CALL_FUN_001a9240(a,b) XCALL(0x1a9240, void(*)(int,void*))(a,b)
#define CALL_FUN_00084a70(a,b) XCALL(0x84a70, char(*)(float*,float*))(a,b)
#define CALL_FUN_00084a10(a) XCALL(0x84a10, char(*)(float*))(a)
#define CALL_game_time_get_rate() XCALL(0xb5cc0, float(*)(void))()
#define CALL_FUN_000b5c30() XCALL(0xb5c30, char(*)(void))()
#define CALL_FUN_000b5aa0() XCALL(0xb5aa0, int(*)(void))()
#define CALL_FUN_0013d640(a,b) XCALL(0x13d640, int(*)(int,int))(a,b)
/* real_rgb_color_brightness (0x7a750) — call by name, no XCALL needed */
#define CALL_FUN_00198cb0(a,b,c,d,e,f,g,h) XCALL(0x198cb0, char(*)(int,void*,void*,void*,void*,void*,void*,void*))(a,b,c,d,e,f,g,h)
#define CALL_FUN_001bf570(a,b,c) XCALL(0x1bf570, int(*)(int,int,int))(a,b,c)
#define CALL_FUN_001396e0(a) XCALL(0x1396e0, void(*)(int))(a)
#define CALL_FUN_001198f0(a,b) XCALL(0x1198f0, int(*)(void*,int))(a,b)
#define CALL_FUN_001196d0(a,b) XCALL(0x1196d0, void(*)(void*,int))(a,b)
#define CALL_FUN_001919a0(a,b,c) XCALL(0x1919a0, void(*)(void*,int,int))(a,b,c)
#define CALL_FUN_001403a0(a,b,c) XCALL(0x1403a0, void(*)(int,unsigned short,float*))(a,b,c)
#define CALL_FUN_0010a710(a,b) XCALL(0x10a710, float(*)(unsigned short,float))(a,b)
/* first_person_weapon_center_flashlight: replaced XCALL with named call */
/* first_person_weapon_adjust_light: replaced XCALL with named call — takes 5 args (MSVC stack-reuse) */
#define CALL_FUN_000ddb90(a,b,c,d) XCALL(0xddb90, short(*)(int,int,void*,int))(a,b,c,d)
#define CALL_FUN_0013fea0_2(a,b) XCALL(0x13fea0, int(*)(int,unsigned short))(a,b)
#define CALL_FUN_0013fea0_5(a,b,c,d,e) XCALL(0x13fea0, int(*)(int,unsigned short,void*,void*,void*))(a,b,c,d,e)
#define CALL_FUN_00140f10(a,b,c,d) XCALL(0x140f10, short(*)(void*,int,void*,int))(a,b,c,d)
#define CALL_FUN_00099530(a,b) XCALL(0x99530, unsigned int(*)(float,float*))(a,b)
#define CALL_FUN_0008fa40(a) XCALL(0x8fa40, void(*)(void*))(a)
#define CALL_FUN_0008fac0(a) XCALL(0x8fac0, void(*)(void*))(a)
#define CALL_FUN_001193f0(a) XCALL(0x1193f0, void(*)(void*))(a)
#define CALL_FUN_00119320(a,b) XCALL(0x119320, int(*)(void*,int))(a,b)
#define CALL_FUN_00140cc0(a) XCALL(0x140cc0, void(*)(int))(a)
#define CALL_FUN_0013fc20(a,b,c) XCALL(0x13fc20, void(*)(void*,int,int))(a,b,c)
#define CALL_FUN_0013fb30(a) XCALL(0x13fb30, void(*)(int))(a)
#define CALL_FUN_00143c80(a,b) XCALL(0x143c80, int(*)(void*,void*))(a,b)
#define CALL_FUN_0010bbc0(a,b,c) XCALL(0x10bbc0, void(*)(void*,void*,void*))(a,b,c)
#define CALL_FUN_000f6d00_0() XCALL(0xf6d00, char(*)(void))()
#define CALL_FUN_000f6d00_1(a) XCALL(0xf6d00, char(*)(void*))(a)
#define CALL_FUN_00021fb0(a) XCALL(0x21fb0, char(*)(float*))(a)
#define CALL_FUN_000a16b0(a) XCALL(0xa16b0, char(*)(void*))(a)
#define CALL_FUN_00143ae0() XCALL(0x143ae0, void(*)(void))()
#define CALL_FUN_001d9e59(a,b) XCALL(0x1d9e59, void*(*)(const char*,const char*))(a,b)
#define CALL_FUN_001d9260 XCALL(0x1d9260, int(*)(void*,const char*,...))
#define CALL_FUN_0013f3b0(a,b) XCALL(0x13f3b0, void(*)(void*,int))(a,b)
#define CALL_FUN_0018f180(a,b) XCALL(0x18f180, void(*)(void*,void*))(a,b)
#define CALL_FUN_00140ce0(a,b) XCALL(0x140ce0, void(*)(int,void*))(a,b)
#define CALL_FUN_00013010(a) XCALL(0x13010, float(*)(void*))(a)
#define CALL_FUN_001ba1f0(a) XCALL(0x1ba1f0, void(*)(int))(a)
#define CALL_FUN_0013aed0(a) XCALL(0x13aed0, void(*)(int))(a)
#define CALL_FUN_00184e50(a) XCALL(0x184e50, short*(*)(int))(a)
#define CALL_FUN_00181900(a) XCALL(0x181900, void(*)(int))(a)
#define CALL_FUN_001812c0(a) XCALL(0x1812c0, int(*)(void*))(a)
#define CALL_FUN_00181670(a) XCALL(0x181670, void(*)(void*))(a)
#define CALL_FUN_00089240(a,b) XCALL(0x89240, void(*)(int,void*))(a,b)
#define CALL_FUN_00085b60(a,b,c) XCALL(0x85b60, void(*)(int,unsigned short,int))(a,b,c)
#define CALL_FUN_00085c80(a,b,c) XCALL(0x85c80, void(*)(int,void*,void*))(a,b,c)
/* FUN_00138fd0 and FUN_00138f70 now in kb.json with proper declarations. */
#define CALL_FUN_00180570(a,b) XCALL(0x180570, void(*)(int,void*))(a,b)
#define CALL_FUN_00180660(a,b) XCALL(0x180660, void(*)(int,void*))(a,b)
#define CALL_FUN_00189150(a,b,c,d) XCALL(0x189150, void(*)(int,int,float,void*))(a,b,c,d)
#define CALL_FUN_001906b0(a,b) XCALL(0x1906b0, int(*)(int,int))(a,b)
#define CALL_FUN_007c490(a,b,c,d,e,f) XCALL(0x7c490, void(*)(int,int,void*,void*,void*,float))(a,b,c,d,e,f)
#define CALL_FUN_00196c90(a,b,c,d,e,f,g) XCALL(0x196c90, int(*)(void*,int,void*,void*,void*,void*,void*))(a,b,c,d,e,f,g)
#define CALL_FUN_00123470(a,b,c,d) XCALL(0x123470, void(*)(void*,void*,int,void*))(a,b,c,d)
#define CALL_FUN_00189320_5(a,b,c,d,e) XCALL(0x189320, void(*)(int,void*,void*,float,void*))(a,b,c,d,e)
#define CALL_FUN_00139c20(a,b,c,d,e,f,g,h,i) XCALL(0x139c20, void(*)(int,unsigned short,float*,float,void*,void*,void*,void*,int))(a,b,c,d,e,f,g,h,i)
#define CALL_FUN_00180770(a) XCALL(0x180770, unsigned char(*)(float))(a)
#define CALL_FUN_001812b0() XCALL(0x1812b0, void(*)(void))()
#define CALL_FUN_00181410() XCALL(0x181410, void(*)(void))()
#define CALL_FUN_0007c270(a,b,c,d,e) XCALL(0x7c270, float*(*)(float*,unsigned int,float*,float*,float))(a,b,c,d,e)
#define CALL_FUN_00180b10(a) XCALL(0x180b10, int(*)(int))(a)
#define CALL_FUN_001390d0(a,b,c,d,e,f) XCALL(0x1390d0, void(*)(int,int,void*,float,float,void*))(a,b,c,d,e,f)
#define CALL_FUN_00138ee0(a) XCALL(0x138ee0, int(*)(int))(a)
#define CALL_FUN_000d1c90(a) XCALL(0xd1c90, unsigned int(*)(float*))(a)
/*
 * real_vector3d_valid — check whether a 3D vector contains only finite floats.
 *
 * Tests the IEEE 754 exponent field (bits 23..30) of each of the three
 * components. If all three have an exponent != 0xFF (i.e. the value is
 * neither NaN nor Infinity), returns 1 (valid). Otherwise returns 0.
 *
 * Leaf function, no callees. Reinterprets floats as uint32 via pointer cast.
 *
 * Confirmed: AND with 0x7f800000 and CMP to 0x7f800000 for each component.
 * Confirmed: returns 1 only if all three pass; returns 0 on first failure.
 */
/* 0x84a10 */
int real_vector3d_valid(float *vector)
{
  unsigned int *v = (unsigned int *)vector;
  if ((v[0] & 0x7f800000) != 0x7f800000 &&
      (v[1] & 0x7f800000) != 0x7f800000 &&
      (v[2] & 0x7f800000) != 0x7f800000) {
    return 1;
  }
  return 0;
}

/* 0x84a70 — valid_real_normal3d_perpendicular: check whether two 3D vectors
 * are each valid unit normals AND are perpendicular to each other.
 *
 * First validates each vector individually via valid_real_normal3d (checks
 * that squared length is within 0.001 of 1.0 and not NaN/infinity).
 * Then computes dot(a, b) and returns true only if the dot product is
 * a valid finite float with fabsf(dot) < 0.001f (i.e., nearly perpendicular).
 *
 * Confirmed: CALL 0x21fb0 twice (valid_real_normal3d) for each input vector.
 * Confirmed: FLD/FMUL/FADDP computes dot(a, b) = a[0]*b[0]+a[1]*b[1]+a[2]*b[2].
 * Confirmed: FSTS [EBP-4] stores dot without popping; integer NaN/inf check
 *   on exponent bits (AND 0x7f800000, CMP 0x7f800000) before the FABS compare.
 * Confirmed: FABS / FCOMPL double ptr [0x2549d8] compares against
 * (double)0.001f. Confirmed: FNSTSW AX / TEST AH,5 / JP pattern — returns true
 * when fabsf(dot) < 0.001f. */
bool valid_real_normal3d_perpendicular(float *a, float *b)
{
  float dot;
  char ok;
  ok = (char)valid_real_normal3d(a);
  if (ok &&
      (ok = (char)valid_real_normal3d(b), ok) &&
      (dot = a[2] * b[2] + a[1] * b[1] + a[0] * b[0],
       (*(unsigned int *)&dot & 0x7f800000) != 0x7f800000) &&
      fabs(dot) < 0.001) {
    return 1;
  }
  return 0;
}

/* FUN_00085180 (0x85180) — XBE naked draft (batch 64). */
#if defined(__clang__)
static scenario_t * (*const b85180_c18e380)(void) = global_scenario_get;
static void *(*const b85180_elem)(void *, int, int) = tag_block_get_element;
static void (*const b85180_c10bbc0)(float *forward, float *up, float *angles) = vectors3d_from_euler_angles3d;
static void (*const b85180_c875f0)(float) = director_update;
static void (*const b85180_c8cde0)(float) = observer_update;

__attribute__((naked, noinline))
void FUN_00085180(short param_1 __attribute__((unused)), short param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4f0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw $0, 0x2ee5a2\n\t"
      "movb $1, 0x2ee5a1\n\t"
      "movw %%di, 0x2ee5a4\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0x2ee5ac\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "leal 0x34(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x2ee5b0\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "pushl $0x2ee5c4\n\t"
      "pushl $0x2ee5b8\n\t"
      "movl %%ecx, 0x2ee5b4\n\t"
      "call *%[c10bbc0]\n\t"
      "flds 0x40(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x18, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00085180_1\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "movl %%eax, 0x2ee5d0\n\t"
      "jmp .LFUN_00085180_2\n\t"
      ".LFUN_00085180_1:\n\t"
      "movl $0x3f9c61aa, 0x2ee5d0\n\t"
      ".LFUN_00085180_2:\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $4, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl %%edx, 0x2ee5d4\n\t"
      "fstps 0x2ee5a8\n\t"
      "call *%[c875f0]\n\t"
      "pushl $0x38d1b717\n\t"
      "call *%[c8cde0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b85180_c18e380), [elem] "m"(b85180_elem), [c10bbc0] "m"(b85180_c10bbc0), [c875f0] "m"(b85180_c875f0), [c8cde0] "m"(b85180_c8cde0)
      : "memory");
}
#else
#error "FUN_00085180: clang naked draft required"
#endif


/*
 * FUN_000853a0 (0x853a0 / objects.obj) — convert the cutscene-camera time
 * (seconds, at 0x2ee5a8) back to a tick count by multiplying by 30.0 and
 * truncating to int.
 *
 * The camera time global at 0x2ee5a8 is stored as ticks/30 (see FUN_00085180,
 * which writes (float)(param_2 / 30)); this reverses that to recover ticks.
 *
 * Confirmed: FLD [0x2ee5a8]; FMUL [0x253394 = 30.0f]; JMP _ftol2 (tail-call).
 * Confirmed: return value is the truncated int product (EAX from _ftol2).
 */
int FUN_000853a0(void)
{
  return (int)(*(float *)0x2ee5a8 * *(float *)0x253394);
}

/*
 * FUN_000adf70 — equipment tag-index remapper for game engine mode 3.
 *
 * Called from FUN_000ae0a0 when the 'obje' type word is 3 (equipment).
 * Remaps or blocks equipment spawn based on:
 *   - weapon_definition_index_to_list_index returning 0xc or 0xd
 *   - The 'eqip' tag's type field at offset 0x308 vs variant flags at 0x456b18
 *   - Game engine type at 0x456b3c (3→list 0xd, 9→list 0xc, 10→none)
 *   - Complexity flags at 0x5aa720 (bit 3=team game, bit 2=split-screen)
 *   - Random probability gate against 0x2533e4 (team) or 0x26c744 (split)
 * Returns the remapped equipment tag index from game_globals block at +0x14c,
 * tag_index unchanged if not applicable, or -1 if blocked.
 *
 * Confirmed: PUSH 0x65716970 / CALL tag_get — 'eqip' tag lookup.
 * Confirmed: CALL 0xa9620 — weapon_definition_index_to_list_index, cdecl 1 arg.
 * Confirmed: CMP ESI,0xc / CMP ESI,0xd — two special list slot checks.
 * Confirmed: MOV AX,[EBX+0x308] / CMP AX,2 / CMP AX,3 — category field checks.
 * Confirmed: TEST byte ptr [0x456b18],0x8 / 0x10 — variant flags at 0x456b18.
 * Confirmed: MOV EAX,[0x456b3c] / SUB 3 / SUB 6 / DEC chain — game type remap.
 * Confirmed: AND EAX,4 / JNZ skip; SHR EDX,2 / AND DL,1 — conditional flag
 * gate. Confirmed: CALL 0x10b0d0 / CALL 0x10b240 / FCOMP — random probability
 * gate. Confirmed: CALL 0x18e450 / ADD EAX,0x14c / PUSH 0x10 — game_globals
 * block lookup.
 */
/* FUN_000adf70 (0xadf70) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const badf70_tag)(int, int) = tag_get;
static int (*const badf70_ca9620)(int param_1) = weapon_definition_index_to_list_index;
static int *(*const badf70_gseed)(void) = get_global_random_seed_address;
static float (*const badf70_rmreal)(unsigned int *) = random_math_real;
static void * (*const badf70_c18e450)(void) = game_globals_get;
static void *(*const badf70_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int FUN_000adf70(int tag_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_000adf70_1\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .LFUN_000adf70_2\n\t"
      ".LFUN_000adf70_1:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x65716970\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_000adf70_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[ca9620]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xc, %%esi\n\t"
      "je .LFUN_000adf70_4\n\t"
      "cmpl $0xd, %%esi\n\t"
      "je .LFUN_000adf70_4\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000adf70_12\n\t"
      "movw 0x308(%%ebx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_000adf70_3\n\t"
      "testb $8, 0x456b18\n\t"
      "je .LFUN_000adf70_12\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000adf70_3:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_000adf70_12\n\t"
      "testb $0x10, 0x456b18\n\t"
      "je .LFUN_000adf70_12\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000adf70_4:\n\t"
      "movl 0x456b3c, %%eax\n\t"
      "subl $3, %%eax\n\t"
      "je .LFUN_000adf70_6\n\t"
      "subl $6, %%eax\n\t"
      "je .LFUN_000adf70_5\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000adf70_7\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "jmp .LFUN_000adf70_7\n\t"
      ".LFUN_000adf70_5:\n\t"
      "movl $0xc, %%esi\n\t"
      "jmp .LFUN_000adf70_7\n\t"
      ".LFUN_000adf70_6:\n\t"
      "movl $0xd, %%esi\n\t"
      ".LFUN_000adf70_7:\n\t"
      "movl 0x5aa720, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $4, %%eax\n\t"
      "jne .LFUN_000adf70_8\n\t"
      "movl 0x456b18, %%edx\n\t"
      "shrl $2, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, 0xb(%%ebp)\n\t"
      "je .LFUN_000adf70_8\n\t"
      "orl $0xffffffff, %%esi\n\t"
      ".LFUN_000adf70_8:\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_000adf70_9\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x2533e4\n\t"
      "jmp .LFUN_000adf70_10\n\t"
      ".LFUN_000adf70_9:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000adf70_11\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x26c744\n\t"
      ".LFUN_000adf70_10:\n\t"
      "fnstsw %%ax\n\t"
      "addl $4, %%esp\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000adf70_11\n\t"
      "orl $0xffffffff, %%esi\n\t"
      ".LFUN_000adf70_11:\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "je .LFUN_000adf70_13\n\t"
      "call *%[c18e450]\n\t"
      "pushl $0x10\n\t"
      "addl $0x14c, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000adf70_12:\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_000adf70_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(badf70_tag), [ca9620] "m"(badf70_ca9620), [gseed] "m"(badf70_gseed), [rmreal] "m"(badf70_rmreal), [c18e450] "m"(badf70_c18e450), [elem] "m"(badf70_elem)
      : "memory");
}
#else
#error "FUN_000adf70: clang naked draft required"
#endif


/* FUN_000ae0a0 (0xae0a0) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const bae0a0_tag)(int, int) = tag_get;
static int (*const bae0a0_ca96b0)(int tag_index) = game_engine_remap_vehicle;
static int (*const bae0a0_ca9770)(int tag_index) = game_engine_remap_weapon;
static int (*const bae0a0_cadf70)(int tag_index) = FUN_000adf70;

__attribute__((naked, noinline))
int FUN_000ae0a0(int tag_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x456b60, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "je .LFUN_000ae0a0_3\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000ae0a0_3\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movw (%%eax), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_000ae0a0_1\n\t"
      "pushl %%esi\n\t"
      "call *%[ca96b0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae0a0_1:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_000ae0a0_2\n\t"
      "pushl %%esi\n\t"
      "call *%[ca9770]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae0a0_2:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_000ae0a0_3\n\t"
      "pushl %%esi\n\t"
      "call *%[cadf70]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae0a0_3:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(bae0a0_tag), [ca96b0] "m"(bae0a0_ca96b0), [ca9770] "m"(bae0a0_ca9770), [cadf70] "m"(bae0a0_cadf70)
      : "memory");
}
#else
#error "FUN_000ae0a0: clang naked draft required"
#endif


/* FUN_000ae110 (0xae110) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const bae110_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const bae110_ca8c40)(int player_handle) = game_engine_player_is_out_of_lives;
static bool (*const bae110_ca8ba0)(int player_handle) = game_engine_is_player_leading;
static bool (*const bae110_cac4e0)(int player_handle, int param_2, int hud_player, wchar_t *buffer, int buffer_capacity) = game_engine_get_score_hud_text;
static int (*const bae110_gtime)(void) = game_time_get;
static char (*const bae110_caceb0)(int player_handle, int message_type, int extra, int param4, int param5) = FUN_000aceb0;

__attribute__((naked, noinline))
char FUN_000ae110(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x456b60, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "testl %%ecx, %%ecx\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_000ae110_11\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x74(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpl $0x17, %%eax\n\t"
      "jl .LFUN_000ae110_1\n\t"
      "cmpl $0x1a, %%eax\n\t"
      "jg .LFUN_000ae110_1\n\t"
      "movl %%ebx, 0x74(%%esi)\n\t"
      ".LFUN_000ae110_1:\n\t"
      "cmpl %%ebx, 0x34(%%esi)\n\t"
      "jne .LFUN_000ae110_8\n\t"
      "cmpb $1, 0xd1(%%esi)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_000ae110_2\n\t"
      "movl $0x1b, %%esi\n\t"
      "jmp .LFUN_000ae110_6\n\t"
      ".LFUN_000ae110_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[ca8c40]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ae110_3\n\t"
      "movl $0x18, %%esi\n\t"
      "jmp .LFUN_000ae110_6\n\t"
      ".LFUN_000ae110_3:\n\t"
      "call *%[ca8ba0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ae110_4\n\t"
      "movl $0x17, %%esi\n\t"
      "jmp .LFUN_000ae110_6\n\t"
      ".LFUN_000ae110_4:\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_000ae110_5\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $4, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl $0x19, %%esi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000ae110_6\n\t"
      ".LFUN_000ae110_5:\n\t"
      "movl $0x1a, %%esi\n\t"
      ".LFUN_000ae110_6:\n\t"
      "movl 0x456b60, %%edx\n\t"
      "movl 0x64(%%edx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "je .LFUN_000ae110_7\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000ae110_11\n\t"
      ".LFUN_000ae110_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[cac4e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae110_8:\n\t"
      "call *%[gtime]\n\t"
      "cmpl $0x1c2, %%eax\n\t"
      "jge .LFUN_000ae110_9\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0x1d\n\t"
      "pushl %%edi\n\t"
      "call *%[caceb0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae110_9:\n\t"
      "movl 0x74(%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000ae110_10\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x78(%%esi), %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[caceb0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae110_10:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_000ae110_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bae110_dget), [ca8c40] "m"(bae110_ca8c40), [ca8ba0] "m"(bae110_ca8ba0), [cac4e0] "m"(bae110_cac4e0), [gtime] "m"(bae110_gtime), [caceb0] "m"(bae110_caceb0)
      : "memory");
}
#else
#error "FUN_000ae110: clang naked draft required"
#endif


/* FUN_000ae250 (0xae250) — XBE naked draft (batch 63). */
#if defined(__clang__)
static int (*const bae250_ca8130)(int param_1) = FUN_000a8130;
static void *(*const bae250_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const bae250_caba90)(void) = game_engine_teams_still_playing;
static int (*const bae250_cabb90)(int param_1) = FUN_000abb90;
static int * (*const bae250_cabf50)(int *param_1, int player_handle) = FUN_000abf50;

__attribute__((naked, noinline))
int FUN_000ae250(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movb 0x456b14, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_000ae250_3\n\t"
      "pushl $0\n\t"
      "call *%[ca8130]\n\t"
      "pushl $1\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[ca8130]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[caba90]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ae250_1\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .LFUN_000ae250_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%edi, %%esi\n\t"
      "setle %%al\n\t"
      "jmp .LFUN_000ae250_2\n\t"
      ".LFUN_000ae250_1:\n\t"
      "pushl $0\n\t"
      "call *%[cabb90]\n\t"
      "addl $4, %%esp\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_000ae250_2:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000ae250_4\n\t"
      "movl 0x20(%%ebx), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "sete %%dl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae250_3:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cabf50]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl $0x80000000, %%eax\n\t"
      "jbe .LFUN_000ae250_5\n\t"
      "testl $0x7fffffff, %%eax\n\t"
      "jne .LFUN_000ae250_5\n\t"
      ".LFUN_000ae250_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ae250_5:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "negl %%eax\n\t"
      "popl %%edi\n\t"
      "sbbl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "incl %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ca8130] "m"(bae250_ca8130), [dget] "m"(bae250_dget), [caba90] "m"(bae250_caba90), [cabb90] "m"(bae250_cabb90), [cabf50] "m"(bae250_cabf50)
      : "memory");
}
#else
#error "FUN_000ae250: clang naked draft required"
#endif



/* FUN_00136150 — create widgets for an object from its tag definition.
 *
 * Looks up the object's tag (group 'obje'), reads the widget attachments
 * tag block at tag+0x14c, and for each attachment, searches the global
 * widget_types table (5 entries at 0x323528, each 0x28 bytes) for a
 * matching group_tag. When found, allocates a new widget datum from the
 * widget data pool at 0x5a90c4, sets its type field, and either:
 *   - calls the widget type's "new" function (entry+0x18) with the
 *     attachment's definition index (element+0x0c), linking on success
 *   - or directly links the widget with definition_handle = -1 if no
 *     "new" function is defined.
 * Widgets are prepended to a singly-linked list rooted at obj+0x11c.
 *
 * Source: c:\halo\source\objects\widgets\widget_types.h (line 0x96)
 *
 * Confirmed: 1 cdecl arg (object_handle).
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (handle, -1).
 * Confirmed: CALL 0x1ba140 (tag_get) with (0x6f626a65, obj[0]).
 * Confirmed: CALL 0x19b210 (tag_block_get_element) with (block, index, 0x20).
 * Confirmed: CALL 0x119610 (data_new_at_index) with (*(data_t**)0x5a90c4).
 * Confirmed: CALL 0x119320 (datum_get) with (*(data_t**)0x5a90c4, handle).
 * Confirmed: CALL 0x1196d0 (datum_delete) with (*(data_t**)0x5a90c4, handle).
 * Confirmed: widget_types table at 0x323528: [+0x00]=group_tag, [+0x18]=new_fn.
 * Confirmed: ADD ESP,0x10 cleans both object_get_and_verify_type + tag_get
 * pushes. Confirmed: outer loop counter is int16_t (MOVSX EAX,AX at 0x1362b2).
 * Confirmed: inner loop counter is int16_t (MOVSX ECX,SI; CMP SI,0x5).
 * Confirmed: indirect CALL EAX at 0x13625a for widget new function.
 * Confirmed: assert_halt for type range check at 0x1361fe.
 */

/* FUN_00134ae0 (0x134ae0) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const b134ae0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b134ae0_tag)(int, int) = tag_get;
static void (*const b134ae0_c1345b0)(int glow_widget, int object_handle) = FUN_001345b0;
static short (*const b134ae0_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b134ae0_c133520)(int object_handle, int widget_datum) = FUN_00133520;
static data_t * (*const b134ae0_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void (*const b134ae0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b134ae0_exitfn)(int) = system_exit;
static void (*const b134ae0_c119b20)(data_t *data) = data_delete_all;
static void (*const b134ae0_c119550)(data_t *data) = data_make_invalid;

__attribute__((naked, noinline))
void FUN_00134ae0(int object_handle __attribute__((unused)), int widget_datum __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x6c, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00134ae0_2\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00134ae0_1\n\t"
      "movl 0x5a90c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x224(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movl 0x5a90c8, %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1345b0]\n\t"
      "pushl $1\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c133520]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00134ae0_1:\n\t"
      "popl %%esi\n\t"
      ".LFUN_00134ae0_2:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "pushl $8\n\t"
      "pushl $0x100\n\t"
      "pushl $0x29acc8\n\t"
      "call *%[c1bfe10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x46f020\n\t"
      "jne .LFUN_00134ae0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x29ac98\n\t"
      "pushl $0x29ac70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00134ae0_3:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46f020, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00134ae0_4\n\t"
      "pushl %%eax\n\t"
      "call *%[c119b20]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_00134ae0_4:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46f020, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00134ae0_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c119550]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_00134ae0_5:\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b134ae0_dget), [tag] "m"(b134ae0_tag), [c1345b0] "m"(b134ae0_c1345b0), [markers] "m"(b134ae0_markers), [c133520] "m"(b134ae0_c133520), [c1bfe10] "m"(b134ae0_c1bfe10), [assert] "m"(b134ae0_assert), [exitfn] "m"(b134ae0_exitfn), [c119b20] "m"(b134ae0_c119b20), [c119550] "m"(b134ae0_c119550)
      : "memory");
}
#else
#error "FUN_00134ae0: clang naked draft required"
#endif


/* Allocates a new entry in the 0x46f020 data table and stores param_1 at +4.
 * Returns the datum handle, or -1 on failure.
 * 0x134be0 / objects.obj
 */
int FUN_00134be0(int param_1)
{
  int iVar1;
  int iVar2;

  iVar1 = data_new_at_index(*(data_t **)0x46f020);
  if (iVar1 != -1) {
    iVar2 = (int)datum_get(*(data_t **)0x46f020, iVar1);
    *(int *)(iVar2 + 4) = param_1;
  }
  return iVar1;
}

/* Deletes the entry at param_1 from the 0x46f020 data table.
 * 0x134c20 / objects.obj
 */
void FUN_00134c20(int param_1)
{
  if (param_1 != -1) {
    datum_delete(*(data_t **)0x46f020, param_1);
  }
}

/*
 * FUN_00134e50 (0x134e50 / objects.obj) — wrap a value into the range of a
 * period, skipping the modulo when the period is exactly 1.0.
 *
 * Returns value (param_1) unchanged when period (param_2) == 1.0f; otherwise
 * returns fmod(value, period). The 1.0 special-case avoids a redundant modulo
 * when the period is unit-length.
 *
 * Confirmed: FCOMP param_2 against [0x2533c8 = 1.0f]; equal -> return param_1.
 * Confirmed: not-equal -> tail-call fmod(param_1, param_2) (JMP 0x1d9e70).
 */
float FUN_00134e50(float value, float period)
{
  if (period == 1.0f) {
    return value;
  }
  return x87_fmod(value, (double)period);
}

/* FUN_00134e80 (0x134e80) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void *(*const b134e80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b134e80_tag)(int, int) = tag_get;
static void * (*const b134e80_c134c40)(int definition_ptr, int object_handle) = FUN_00134c40;
static short (*const b134e80_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static bool (*const b134e80_c1403a0)(int object_handle, short function_index, void *out_value) = object_get_function_value;
static void (*const b134e80_c17cfc0)(int param_1, int param_2) = FUN_0017cfc0;
static char (*const b134e80_c17cfd0)(int param_1, int param_2, short param_3) = FUN_0017cfd0;
static float (*const b134e80_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static float * (*const b134e80_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;
static unsigned int (*const b134e80_d1c90)(float *) = FUN_000d1c90;
static void (*const b134e80_c17d010)(float *position, float radius, float *scale2d, float angle, uint32_t color) = FUN_0017d010;
static void (*const b134e80_c17d020)(void) = FUN_0017d020;

__attribute__((naked, noinline))
void FUN_00134e80(int object_handle __attribute__((unused)), int light_volume_datum __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xa4, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00134e80_17\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00134e80_17\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x46f020, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6d677332\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0x6e(%%ebx)\n\t"
      "jle .LFUN_00134e80_16\n\t"
      "movl 0x120(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00134e80_16\n\t"
      "pushl %%edi\n\t"
      "call *%[c134c40]\n\t"
      "pushl $1\n\t"
      "leal -0xa4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[markers]\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fsubs 0x506550\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fsubs 0x506554\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fsubs 0x506558\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fmuls 0x506560\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x50655c\n\t"
      "fmuls -0x68(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00134e80_1\n\t"
      "fchs\n\t"
      ".LFUN_00134e80_1:\n\t"
      "flds 0x38(%%ebx)\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134e80_4\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x506560\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x50655c\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x38(%%ebx)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fsubs 0x38(%%ebx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00134e80_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00134e80_3\n\t"
      ".LFUN_00134e80_2:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134e80_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00134e80_3:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00134e80_4:\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fmuls 0x3c(%%ebx)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x40(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00134e80_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00134e80_6\n\t"
      ".LFUN_00134e80_5:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134e80_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00134e80_6:\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x44(%%ebx), %%cx\n\t"
      "decw %%cx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1403a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00134e80_7\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00134e80_7:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134e80_16\n\t"
      "flds 0x68(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00134e80_8\n\t"
      "flds 0x78(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134e80_16\n\t"
      ".LFUN_00134e80_8:\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00134e80_9\n\t"
      "flds 0x40(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134e80_16\n\t"
      ".LFUN_00134e80_9:\n\t"
      "pushl $1\n\t"
      "pushl $5\n\t"
      "call *%[c17cfc0]\n\t"
      "movl 0x68(%%ebx), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6c(%%ebx), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c17cfd0]\n\t"
      "movw 0x6e(%%ebx), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00134e80_15\n\t"
      "movswl %%ax, %%ecx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movzwl %%ax, %%edi\n\t"
      "fstps -0x20(%%ebp)\n\t"
      ".LFUN_00134e80_10:\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "fdivs -0x20(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00134e80_11\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "call *%[c1d9e70]\n\t"
      ".LFUN_00134e80_11:\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00134e80_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "call *%[c1d9e70]\n\t"
      ".LFUN_00134e80_12:\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x88(%%esi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00134e80_13\n\t"
      "flds -0x4(%%ebp)\n\t"
      "call *%[c1d9e70]\n\t"
      ".LFUN_00134e80_13:\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x8c(%%esi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00134e80_14\n\t"
      "flds -0x4(%%ebp)\n\t"
      "call *%[c1d9e70]\n\t"
      ".LFUN_00134e80_14:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "flds 0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x22(%%ebx), %%cl\n\t"
      "leal 0x7c(%%esi), %%eax\n\t"
      "fadds 0x10(%%esi)\n\t"
      "pushl %%eax\n\t"
      "flds -0x68(%%ebp)\n\t"
      "leal 0x6c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "andl $3, %%ecx\n\t"
      "fadds -0x44(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c7c270]\n\t"
      "flds 0x2533c8\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x68(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x78(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[d1c90]\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17d010]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x2c, %%esp\n\t"
      "incl %%ecx\n\t"
      "decl %%edi\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jne .LFUN_00134e80_10\n\t"
      ".LFUN_00134e80_15:\n\t"
      "call *%[c17d020]\n\t"
      ".LFUN_00134e80_16:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00134e80_17:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b134e80_dget), [tag] "m"(b134e80_tag), [c134c40] "m"(b134e80_c134c40), [markers] "m"(b134e80_markers), [c1403a0] "m"(b134e80_c1403a0), [c17cfc0] "m"(b134e80_c17cfc0), [c17cfd0] "m"(b134e80_c17cfd0), [c1d9e70] "m"(b134e80_c1d9e70), [c7c270] "m"(b134e80_c7c270), [d1c90] "m"(b134e80_d1c90), [c17d010] "m"(b134e80_c17d010), [c17d020] "m"(b134e80_c17d020)
      : "memory");
}
#else
#error "FUN_00134e80: clang naked draft required"
#endif


/* FUN_00135210 (0x135210) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b135210_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b135210_tag)(int, int) = tag_get;
static short (*const b135210_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b135210_c17cfb0)(int object_handle, int datum, float *position, int callback) = FUN_0017cfb0;
static data_t * (*const b135210_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void (*const b135210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b135210_exitfn)(int) = system_exit;
static void (*const b135210_c119b20)(data_t *data) = data_delete_all;
static void (*const b135210_c119550)(data_t *data) = data_make_invalid;

__attribute__((naked, noinline))
void FUN_00135210(int object_handle __attribute__((unused)), int light_volume_datum __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x6c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00135210_5\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00135210_4\n\t"
      "movl 0x46f020, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6d677332\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jle .LFUN_00135210_4\n\t"
      "movl 0x120(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00135210_4\n\t"
      "movw 0x44(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00135210_1\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00135210_1\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "flds -0x4(%%eax,%%edx,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00135210_4\n\t"
      ".LFUN_00135210_1:\n\t"
      "pushl $1\n\t"
      "leal -0x6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[markers]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x506550\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x506554\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x506558\n\t"
      "flds 0x38(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00135210_2\n\t"
      "flds 0x506564\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds 0x506560\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x50655c\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x38(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_00135210_4\n\t"
      "jmp .LFUN_00135210_3\n\t"
      ".LFUN_00135210_2:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00135210_3:\n\t"
      "pushl $0x134e80\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17cfb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00135210_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_00135210_5:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl $8\n\t"
      "pushl $0x100\n\t"
      "pushl $0x29ad28\n\t"
      "call *%[c1bfe10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x46f024\n\t"
      "jne .LFUN_00135210_6\n\t"
      "pushl $1\n\t"
      "pushl $0x32\n\t"
      "pushl $0x29acfc\n\t"
      "pushl $0x29acd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135210_6:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46f024, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00135210_7\n\t"
      "pushl %%eax\n\t"
      "call *%[c119b20]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_00135210_7:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46f024, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00135210_8\n\t"
      "pushl %%eax\n\t"
      "call *%[c119550]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_00135210_8:\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b135210_dget), [tag] "m"(b135210_tag), [markers] "m"(b135210_markers), [c17cfb0] "m"(b135210_c17cfb0), [c1bfe10] "m"(b135210_c1bfe10), [assert] "m"(b135210_assert), [exitfn] "m"(b135210_exitfn), [c119b20] "m"(b135210_c119b20), [c119550] "m"(b135210_c119550)
      : "memory");
}
#else
#error "FUN_00135210: clang naked draft required"
#endif


/* Allocates a new entry in the 0x46f024 data table and stores param_1 at +4.
 * Returns the datum handle, or -1 on failure.
 * 0x1353b0 / objects.obj
 */
int FUN_001353b0(int param_1)
{
  int iVar1;
  int iVar2;

  iVar1 = data_new_at_index(*(data_t **)0x46f024);
  if (iVar1 != -1) {
    iVar2 = (int)datum_get(*(data_t **)0x46f024, iVar1);
    *(int *)(iVar2 + 4) = param_1;
  }
  return iVar1;
}

/* Deletes the entry at param_1 from the 0x46f024 data table.
 * 0x1353f0 / objects.obj
 */
void FUN_001353f0(int param_1)
{
  if (param_1 != -1) {
    datum_delete(*(data_t **)0x46f024, param_1);
  }
}

/* FUN_0009ec30 declaration is in generated/decl.h */

/*
 * objects/objects.c — object system lifecycle and placement
 * XBE source: c:\halo\SOURCE\objects\objects.c
 *            + c:\halo\SOURCE\objects\object_lights.c (same .obj)
 *
 * Re-implemented functions (by XBE address, ascending):
 *   0x1396e0  object_wake (object_lights.c)
 *   0x13aed0  object_move_to_limbo (object_lights.c)
 *   0x13d640  object_try_and_get_and_verify_type
 *   0x13d680  object_get_and_verify_type
 *   0x13d920  object_set_garbage_flag
 *   0x13dfc0  object_header_block_reference_get
 *   0x13e510  object_child_list_remove
 *   0x13eb70  object_reset_markers
 *   0x13ee60  object_propagate_flag_to_children
 *   0x13eff0  object_remove_from_name_list
 *   0x13f060  objects_place
 *   0x13f810  objects_initialize
 *   0x13f950  objects_initialize_for_new_map
 *   0x13f9f0  objects_dispose_from_old_map
 *   0x13fac0  objects_dispose
 *   0x13fb30  object_activate
 *   0x13fb80  object_deactivate (object deactivate)
 *   0x13fc20  object_placement_data_new (object placement data init)
 *   0x13fd00  object_disconnect_from_map
 *   0x13fef0  object_has_node
 *   0x13ff50  object_set_automatic_deactivation (object set/clear hidden)
 *   0x13ffc0  object_set_garbage
 *   0x140160  object_set_region_count
 *   0x140230  object_adjust_interpolation_position
 *   0x140420  object_find_in_cluster
 *   0x1407e0  object_visible_to_any_player
 *   0x140bc0  object_delete_internal
 *   0x140cc0  object_delete
 *   0x140ce0  object_connect_to_map
 *   0x140eb0  object_get_node_matrix
 *   0x140f10  object_get_markers_by_string_id
 *   0x141020  object_compute_child_marker_position
 *   0x1412f0  object_get_world_position
 *   0x141360  object_get_orientation (object orientation getter)
 *   0x141480  object_get_world_matrix
 *   0x1415f0  object_find_in_radius
 *   0x141b70  object_compute_node_matrices
 *   0x143ae0  object_set_position (object reposition)
 *   0x143be0  object_translate (set object position and reconnect to map)
 *   0x143c80  object_new (object_new — create from placement)
 *   0x144240  object_attach_to_parent
 *   0x1446a0  object_update_children_recursive
 *   0x144860  object_attach_to_marker
 *   0x144b30  objects_garbage_collection (delete and immediately deactivate)
 *   0x145170  objects_update
 */

#include "common.h"

/* Forward declarations for unported callees in the same .obj cluster. */
typedef void (*pfn_void_t)(void);
typedef void (*pfn_int_t)(int);
typedef int (*valid_real_point3d_fn)(float *p);
typedef void (*object_type_validate_fn)(int16_t type);

/* game engine tag-index remapping helpers (called from FUN_000ae0a0).
 * Binary: each takes 1 cdecl int arg, returns int in EAX. */
int game_engine_remap_vehicle(int tag_index);
int game_engine_remap_weapon(int tag_index);
int weapon_definition_index_to_list_index(int param_1);

/*
 * object_set_position — reposition an object and recompute its orientation.
 *
 * Disconnects the object from the map, optionally updates its position
 * (forward vector at obj+0x0C) and facing direction (at obj+0x24).
 * If a target (up) vector is provided, it is copied directly to obj+0x30.
 * Otherwise, a perpendicular up vector is computed from the facing via:
 *   temp = {facing.y, -facing.x, 0.0}
 *   normalize(temp)
 *   if degenerate: temp = {1, 0, 0}
 *   up = cross(temp, facing)
 * Then recomputes node matrices and reconnects to the map.
 *
 * Confirmed: 4 cdecl args (object_handle, facing, target, flags).
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (handle, -1).
 * Confirmed: CALL 0x13fd00 (object_disconnect_from_map) with 1 stack arg.
 * Confirmed: CALL 0x13010 (normalize3d) for perpendicular temp vector.
 * Confirmed: cross product computed via x87 FPU in-line (not a function call).
 * Confirmed: CALL 0x141b70 (object_compute_node_matrices).
 * Confirmed: CALL 0x140ce0 (object_connect_to_map) with (handle, 0).
 * Confirmed: FCOMP against *(float*)0x2533c0 (0.0f) for degenerate check.
 */
/* FUN_00135f90 (0x135f90) — XBE naked draft (batch 65). */
#if defined(__clang__)
static data_t * (*const b135f90_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void (*const b135f90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b135f90_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00135f90(void)
{
  __asm__ volatile(
      "pushl $0xc\n\t"
      "pushl $0x40\n\t"
      "pushl $0x2832a8\n\t"
      "call *%[c1bfe10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x5a90c4\n\t"
      "jne .LFUN_00135f90_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x29ae64\n\t"
      "pushl $0x29ae58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135f90_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x323530, %%edi\n\t"
      ".LFUN_00135f90_2:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00135f90_3\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00135f90_4\n\t"
      ".LFUN_00135f90_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135f90_4:\n\t"
      "movl -0x8(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00135f90_5\n\t"
      "pushl $1\n\t"
      "pushl $0x37\n\t"
      "pushl $0x29ae64\n\t"
      "pushl $0x29ae3c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135f90_5:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00135f90_6\n\t"
      "call *%%eax\n\t"
      ".LFUN_00135f90_6:\n\t"
      "incl %%esi\n\t"
      "addl $0x28, %%edi\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00135f90_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1bfe10] "m"(b135f90_c1bfe10), [assert] "m"(b135f90_assert), [exitfn] "m"(b135f90_exitfn)
      : "memory");
}
#else
#error "FUN_00135f90: clang naked draft required"
#endif


/* FUN_00136040 (0x136040) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void (*const b136040_c119b20)(data_t *data) = data_delete_all;
static void (*const b136040_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b136040_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00136040(void)
{
  __asm__ volatile(
      "movl 0x5a90c4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c119b20]\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x323534, %%edi\n\t"
      ".LFUN_00136040_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00136040_2\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00136040_3\n\t"
      ".LFUN_00136040_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00136040_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00136040_4\n\t"
      "call *%%eax\n\t"
      ".LFUN_00136040_4:\n\t"
      "incl %%esi\n\t"
      "addl $0x28, %%edi\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00136040_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c119b20] "m"(b136040_c119b20), [assert] "m"(b136040_assert), [exitfn] "m"(b136040_exitfn)
      : "memory");
}
#else
#error "FUN_00136040: clang naked draft required"
#endif


/* FUN_001360a0 (0x1360a0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void (*const b1360a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1360a0_exitfn)(int) = system_exit;
static void (*const b1360a0_c119550)(data_t *data) = data_make_invalid;

__attribute__((naked, noinline))
void FUN_001360a0(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x323538, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001360a0_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_001360a0_2\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_001360a0_3\n\t"
      ".LFUN_001360a0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001360a0_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001360a0_4\n\t"
      "call *%%eax\n\t"
      ".LFUN_001360a0_4:\n\t"
      "incl %%esi\n\t"
      "addl $0x28, %%edi\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_001360a0_1\n\t"
      "movl 0x5a90c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119550]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1360a0_assert), [exitfn] "m"(b1360a0_exitfn), [c119550] "m"(b1360a0_c119550)
      : "memory");
}
#else
#error "FUN_001360a0: clang naked draft required"
#endif


/*
 * FUN_00135f20 (0x135f20 / objects.obj) — find the widget_types table index
 * whose group_tag (entry+0x00) matches the requested group tag.
 *
 * Linear search of the 5-entry widget_types table at 0x323528 (stride 0x28
 * bytes). Returns the matching index in [0,4], or -1 (0xffff) if no entry
 * matches.
 *
 * Confirmed: CMP dword ptr [ECX*8 + 0x323528], EDX where ECX = idx*5
 *            -> compares the 4-byte group_tag at 0x323528 + idx*0x28.
 * Confirmed: loop bound CMP AX,0x5 (int16_t counter).
 * Confirmed: miss path MOV AX,SI where SI was OR'd to -1 -> returns (short)-1.
 */
#if defined(__clang__)
__attribute__((naked, noinline))
short FUN_00135f20(int group_tag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "orl $-1, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      "1:\n\t"
      "movsx %%ax, %%ecx\n\t"
      "leal (%%ecx,%%ecx,4), %%ecx\n\t"
      "cmpl %%edx, 0x323528(,%%ecx,8)\n\t"
      "je 2f\n\t"
      "incl %%eax\n\t"
      "cmpw $5, %%ax\n\t"
      "jl 1b\n\t"
      "movw %%si, %%ax\n\t"
      "2:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
short FUN_00135f20(int group_tag)
{
  short result;
  short i;

  result = -1;
  i = 0;
  do {
    if (*(int *)(0x323528 + (int)i * 0x28) == group_tag) {
      return i;
    }
    i = i + 1;
  } while (i < 5);

  return result;
}
#endif

/* FUN_00136100 (0x136100) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void (*const b136100_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b136100_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00136100(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x32353c, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00136100_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00136100_2\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00136100_3\n\t"
      ".LFUN_00136100_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00136100_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00136100_4\n\t"
      "call *%%eax\n\t"
      ".LFUN_00136100_4:\n\t"
      "incl %%esi\n\t"
      "addl $0x28, %%edi\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00136100_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b136100_assert), [exitfn] "m"(b136100_exitfn)
      : "memory");
}
#else
#error "FUN_00136100: clang naked draft required"
#endif


/* FUN_00136150 (0x136150) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b136150_get)(int, int) = object_get_and_verify_type;
static void *(*const b136150_tag)(int, int) = tag_get;
static void *(*const b136150_elem)(void *, int, int) = tag_block_get_element;
static void (*const b136150_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b136150_exitfn)(int) = system_exit;
static int (*const b136150_c119610)(data_t *data) = data_new_at_index;
static void *(*const b136150_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b136150_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void FUN_00136150(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "leal 0x14c(%%eax), %%ecx\n\t"
      "movl $0xffffffff, 0x11c(%%esi)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .LFUN_00136150_9\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "nop\n\t"
      ".LFUN_00136150_1:\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_00136150_2:\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal (%%ecx,%%ecx,4), %%ecx\n\t"
      "cmpl %%edx, 0x323528(,%%ecx,8)\n\t"
      "je .LFUN_00136150_3\n\t"
      "incl %%esi\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00136150_2\n\t"
      "jmp .LFUN_00136150_8\n\t"
      ".LFUN_00136150_3:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_00136150_8\n\t"
      "cmpl $-1, 0xc(%%eax)\n\t"
      "je .LFUN_00136150_8\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00136150_4\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_00136150_5\n\t"
      ".LFUN_00136150_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00136150_5:\n\t"
      "movl 0x5a90c4, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal 0x323528(,%%edx,8), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00136150_8\n\t"
      "movl 0x5a90c4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw %%si, 0x2(%%edi)\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00136150_7\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "je .LFUN_00136150_6\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x11c(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "movl %%ebx, 0x11c(%%eax)\n\t"
      "jmp .LFUN_00136150_8\n\t"
      ".LFUN_00136150_6:\n\t"
      "movl 0x5a90c4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00136150_8\n\t"
      ".LFUN_00136150_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x11c(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "movl %%ebx, 0x11c(%%eax)\n\t"
      "movl $0xffffffff, 0x4(%%edi)\n\t"
      ".LFUN_00136150_8:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00136150_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00136150_9:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b136150_get), [tag] "m"(b136150_tag), [elem] "m"(b136150_elem), [assert] "m"(b136150_assert), [exitfn] "m"(b136150_exitfn), [c119610] "m"(b136150_c119610), [dget] "m"(b136150_dget), [c1196d0] "m"(b136150_c1196d0)
      : "memory");
}
#else
#error "FUN_00136150: clang naked draft required"
#endif


/* FUN_001362d0 (0x1362d0) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const b1362d0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1362d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1362d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1362d0_exitfn)(int) = system_exit;
static void (*const b1362d0_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void FUN_001362d0(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x11c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .LFUN_001362d0_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_001362d0_2\n\t"
      ".LFUN_001362d0_1:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      ".LFUN_001362d0_2:\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a90c4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x2(%%esi), %%di\n\t"
      "addl $8, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001362d0_3\n\t"
      "cmpw $5, %%di\n\t"
      "jl .LFUN_001362d0_4\n\t"
      ".LFUN_001362d0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001362d0_4:\n\t"
      "movl 0x8(%%esi), %%ebx\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edi\n\t"
      "cmpl $-1, 0x4(%%esi)\n\t"
      "leal 0x323528(,%%edi,8), %%edi\n\t"
      "je .LFUN_001362d0_6\n\t"
      "movl 0x1c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001362d0_5\n\t"
      "pushl $1\n\t"
      "pushl $0xbe\n\t"
      "pushl $0x29ae64\n\t"
      "pushl $0x29ae90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001362d0_5:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *0x1c(%%edi)\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001362d0_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x5a90c4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .LFUN_001362d0_1\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, 0x11c(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001362d0_7:\n\t"
      "movl $0xffffffff, 0x11c(%%eax)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1362d0_get), [dget] "m"(b1362d0_dget), [assert] "m"(b1362d0_assert), [exitfn] "m"(b1362d0_exitfn), [c1196d0] "m"(b1362d0_c1196d0)
      : "memory");
}
#else
#error "FUN_001362d0: clang naked draft required"
#endif


/* FUN_001363d0 (0x1363d0) — XBE naked draft (batch 66). */
#if defined(__clang__)
static void *(*const b1363d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1363d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1363d0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_001363d0(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_001363d0_4\n\t"
      ".LFUN_001363d0_1:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a90c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x2(%%edi), %%si\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_001363d0_2\n\t"
      "cmpw $5, %%si\n\t"
      "jl .LFUN_001363d0_3\n\t"
      ".LFUN_001363d0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x29ae0c\n\t"
      "pushl $0x29ade4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001363d0_3:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "movb 0x32352c(,%%ecx,8), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001363d0_5\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001363d0_1\n\t"
      ".LFUN_001363d0_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001363d0_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1363d0_dget), [assert] "m"(b1363d0_assert), [exitfn] "m"(b1363d0_exitfn)
      : "memory");
}
#else
#error "FUN_001363d0: clang naked draft required"
#endif


/*
 * object_wake — disconnect a point light from the cluster partition.
 * (from c:\halo\SOURCE\objects\object_lights.c, line 0x4d0)
 *
 * Looks up the light datum in the point-light data table at 0x5a90bc.
 * If the light is active (flags bit 1) and connected to the map (flags bit 2),
 * removes it from the cluster partition at 0x5a90b0, then clears the
 * connected_to_map flag.
 *
 * Confirmed: datum_get(*(data_t**)0x5a90bc, object_handle) — 2 cdecl args.
 * Confirmed: TEST AL,0x2 for active flag, TEST AL,0x4 for connected_to_map.
 * Confirmed: cluster_partition_remove_object(0x5a90b0, handle, light+0x10).
 * Confirmed: AND byte ptr [ESI+0x2],0xfb clears bit 2.
 */
void object_wake(int object_handle)
{
  char *light;
  uint16_t flags;

  light = (char *)datum_get(*(data_t **)0x5a90bc, object_handle);
  flags = *(uint16_t *)(light + 0x2);

  if ((flags & 0x2) == 0)
    return;

  if ((flags & 0x4) == 0) {
    display_assert("TEST_FLAG(light->flags, _point_light_connected_to_map_bit)",
                   "c:\\halo\\SOURCE\\objects\\object_lights.c", 0x4d0, 1);
    system_exit(-1);
  }

  cluster_partition_remove_object((void *)0x5a90b0, object_handle,
                                  (void *)(light + 0x10));
  *(uint8_t *)(light + 0x2) &= ~0x4;
}

/* FUN_001365d0 (0x1365d0) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void *(*const b1365d0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1365d0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_001365d0(int object_handle __attribute__((unused)), float *body_vitality_override __attribute__((unused)), float *shield_vitality_override __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "flds 0x2533c0\n\t"
      "movl 0x7c(%%eax), %%eax\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_001365d0_2\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001365d0_1\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "flds 0xcc(%%eax)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001365d0_2\n\t"
      ".LFUN_001365d0_1:\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_001365d0_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001365d0_3\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_001365d0_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001365d0_4\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%eax)\n\t"
      ".LFUN_001365d0_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fsts 0x8c(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl %%ecx, 0x88(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001365d0_5\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_001365d0_6\n\t"
      ".LFUN_001365d0_5:\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_001365d0_6:\n\t"
      "fstps 0x90(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001365d0_7\n\t"
      "movl $0x3f800000, 0x94(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001365d0_7:\n\t"
      "movl $0, 0x94(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1365d0_get), [tag] "m"(b1365d0_tag)
      : "memory");
}
#else
#error "FUN_001365d0: clang naked draft required"
#endif


/*
 * FUN_001366b0 (0x1366b0 / objects.obj) — return an object's effective maximum
 * body vitality.
 *
 * Resolves the object and reads its stored max body vitality (object+0x88,
 * set by FUN_001365d0). If use_raw_max (param_2) is non-zero, returns that
 * value unmodified. Otherwise scales it by the per-team / game-mode vitality
 * multiplier returned by FUN_000b55b0(1, object->team@+0x68).
 *
 * §7 note: Ghidra mis-groups object_get_and_verify_type as taking 3 args; the
 * disassembly shows PUSH -1, PUSH handle -> (handle, -1); the char flag stays
 * in [EBP+0xc].
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type, mask -1).
 * Confirmed: float load from object+0x88 (max body vitality).
 * Confirmed: flag byte at [EBP+0xc]; non-zero -> return raw object+0x88.
 * Confirmed: zero -> FUN_000b55b0(1, (uint16)object+0x68) * object+0x88.
 */
float FUN_001366b0(int object_handle, char use_raw_max)
{
  char *obj;
  float max_vitality;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  max_vitality = *(float *)(obj + 0x88);

  if (use_raw_max != 0) {
    return max_vitality;
  }

  return FUN_000b55b0(1, (int)*(unsigned short *)(obj + 0x68)) * max_vitality;
}

/* FUN_00139810 (0x139810) — XBE naked draft (batch 64). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00139810(float *color __attribute__((unused)), float scale __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fcomps 0x8(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139810_1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "jmp .LFUN_00139810_2\n\t"
      ".LFUN_00139810_1:\n\t"
      "flds 0x8(%%ecx)\n\t"
      ".LFUN_00139810_2:\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139810_3\n\t"
      "flds (%%ecx)\n\t"
      "jmp .LFUN_00139810_5\n\t"
      ".LFUN_00139810_3:\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fcomps 0x8(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139810_4\n\t"
      "flds 0x4(%%ecx)\n\t"
      "jmp .LFUN_00139810_5\n\t"
      ".LFUN_00139810_4:\n\t"
      "flds 0x8(%%ecx)\n\t"
      ".LFUN_00139810_5:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139810_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00139810_7\n\t"
      ".LFUN_00139810_6:\n\t"
      "fcomps 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139810_8\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".LFUN_00139810_7:\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_00139810_8:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00139810: clang naked draft required"
#endif


/* Call cluster_partition_iter_first on the object cluster partition at
 * 0x5a90b0. 0x1398b0 / objects.obj
 */
void FUN_001398b0(int *param_1, int param_2)
{
  cluster_partition_iter_first((void *)0x5a90b0, param_1, (int16_t)param_2);
}

/* FUN_001398d0 (0x1398d0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b1398d0_c191660)(void *partition, int *state) = cluster_partition_iter_next;
static void (*const b1398d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1398d0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_001398d0(int *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c191660]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001398d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x664\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001398d0_1:\n\t"
      "incl 0x5a8d64\n\t"
      "movb $1, 0x5a8d60\n\t"
      "ret\n\t"
      :
      : [c191660] "m"(b1398d0_c191660), [assert] "m"(b1398d0_assert), [exitfn] "m"(b1398d0_exitfn)
      : "memory");
}
#else
#error "FUN_001398d0: clang naked draft required"
#endif


/* FUN_00139930 (0x139930) — XBE naked draft (batch 96). */
#if defined(__clang__)
static void *(*const b139930_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b139930_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b139930_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_00139930(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00139930_1\n\t"
      "pushl $1\n\t"
      "pushl $0x66f\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00139930_1:\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "cmpl 0x5a8d64, %%edx\n\t"
      "setne %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b139930_dget), [assert] "m"(b139930_assert), [exitfn] "m"(b139930_exitfn)
      : "memory");
}
#else
#error "FUN_00139930: clang naked draft required"
#endif


/* FUN_00139990 (0x139990) — XBE naked draft (batch 65). */
#if defined(__clang__)
static void *(*const b139990_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b139990_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b139990_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_00139990(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00139990_1\n\t"
      "pushl $1\n\t"
      "pushl $0x67f\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00139990_1:\n\t"
      "movl 0x5a8d64, %%eax\n\t"
      "cmpl %%eax, 0xc(%%esi)\n\t"
      "je .LFUN_00139990_2\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00139990_2:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00139990_3\n\t"
      "pushl $1\n\t"
      "pushl $0x68e\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00139990_3:\n\t"
      "movb $0, 0x5a8d60\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b139990_dget), [assert] "m"(b139990_assert), [exitfn] "m"(b139990_exitfn)
      : "memory");
}
#else
#error "FUN_00139990: clang naked draft required"
#endif


/* FUN_00139a30 (0x139a30) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b139a30_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b139a30_tag)(int, int) = tag_get;
static void (*const b139a30_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;

__attribute__((naked, noinline))
void FUN_00139a30(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movb 0x5a8d58, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00139a30_2\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "flds 0xc(%%esi)\n\t"
      "movl 0x2ee6f0, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x30(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "movl 0x54(%%edi), %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x2533f0\n\t"
      "addl $0x30, %%esp\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x2533f0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2533f0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movb (%%esi), %%al\n\t"
      "testb $2, %%al\n\t"
      "jne .LFUN_00139a30_1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "fmuls 0x24(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fmuls 0x54(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00139a30_1:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fmuls 0x2533f0\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl $1\n\t"
      "fmuls 0x2533f0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2533f0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00139a30_2:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b139a30_dget), [tag] "m"(b139a30_tag), [c189540] "m"(b139a30_c189540)
      : "memory");
}
#else
#error "FUN_00139a30: clang naked draft required"
#endif


/* object_move_to_limbo (0x13aed0) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void *(*const b13aed0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13aed0_tag)(int, int) = tag_get;
static void * (*const b13aed0_c13fea0)(int object_handle, int16_t marker_index) = object_get_child_marker_definition;
static short (*const b13aed0_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void *(*const b13aed0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b13aed0_onode)(int, short) = object_get_node_matrix;
static void (*const b13aed0_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b13aed0_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static void (*const b13aed0_perp)(float *, float *) = perpendicular3d;
static float (*const b13aed0_norm)(float *) = normalize3d;
static void (*const b13aed0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13aed0_exitfn)(int) = system_exit;
static void (*const b13aed0_c140130)(int object_handle, void *location_out) = object_get_location;
static void (*const b13aed0_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void (*const b13aed0_c1917a0)(void *partition, int object_handle, void *first_cluster_ref, void *position, uint32_t radius_fp, void *location) = cluster_partition_add_object;

__attribute__((naked, noinline))
void object_move_to_limbo(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lobject_move_to_limbo_1\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x5c(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13fea0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[markers]\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x44(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "leal 0x48(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .Lobject_move_to_limbo_2\n\t"
      ".Lobject_move_to_limbo_1:\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobject_move_to_limbo_2\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x5c(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[onode]\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x60(%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[xfrmpt]\n\t"
      "leal 0x3c(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal 0x6c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c109680]\n\t"
      "leal 0x48(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[perp]\n\t"
      "pushl %%edi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x2c, %%esp\n\t"
      ".Lobject_move_to_limbo_2:\n\t"
      "testb $2, 0x2(%%esi)\n\t"
      "je .Lobject_move_to_limbo_11\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb (%%ecx), %%al\n\t"
      "flds 0xc(%%ecx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $2, %%al\n\t"
      "jne .Lobject_move_to_limbo_3\n\t"
      "fmuls 0x24(%%ecx)\n\t"
      ".Lobject_move_to_limbo_3:\n\t"
      "fcoms 0x18(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_move_to_limbo_4\n\t"
      "addl $0x30, %%edi\n\t"
      "fstp %%st(0)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0x18(%%ecx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .Lobject_move_to_limbo_7\n\t"
      ".Lobject_move_to_limbo_4:\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_move_to_limbo_6\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x254a58\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_move_to_limbo_5\n\t"
      "fdivs 0x20(%%ecx)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fadds 0x30(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      "fadds 0x38(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .Lobject_move_to_limbo_7\n\t"
      ".Lobject_move_to_limbo_5:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%ecx)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fmuls 0x20(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fadds 0x30(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      "fadds 0x38(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .Lobject_move_to_limbo_7\n\t"
      ".Lobject_move_to_limbo_6:\n\t"
      "addl $0x30, %%edi\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lobject_move_to_limbo_7:\n\t"
      "movb 0x2(%%esi), %%al\n\t"
      "movl $4, %%ebx\n\t"
      "testb %%al, %%bl\n\t"
      "je .Lobject_move_to_limbo_8\n\t"
      "pushl $1\n\t"
      "pushl $0x4f9\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_move_to_limbo_8:\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_move_to_limbo_9\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobject_move_to_limbo_9\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c140130]\n\t"
      "jmp .Lobject_move_to_limbo_10\n\t"
      ".Lobject_move_to_limbo_9:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18f180]\n\t"
      ".Lobject_move_to_limbo_10:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c1917a0]\n\t"
      "addl $0x18, %%esp\n\t"
      "orw %%bx, 0x2(%%esi)\n\t"
      ".Lobject_move_to_limbo_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13aed0_dget), [tag] "m"(b13aed0_tag), [c13fea0] "m"(b13aed0_c13fea0), [markers] "m"(b13aed0_markers), [tryget] "m"(b13aed0_tryget), [onode] "m"(b13aed0_onode), [xfrmpt] "m"(b13aed0_xfrmpt), [c109680] "m"(b13aed0_c109680), [perp] "m"(b13aed0_perp), [norm] "m"(b13aed0_norm), [assert] "m"(b13aed0_assert), [exitfn] "m"(b13aed0_exitfn), [c140130] "m"(b13aed0_c140130), [c18f180] "m"(b13aed0_c18f180), [c1917a0] "m"(b13aed0_c1917a0)
      : "memory");
}
#else
#error "object_move_to_limbo: clang naked draft required"
#endif


/* FUN_0013a5f0 (0x13a5f0) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void (*const b13a5f0_c17cd50)(void) = FUN_0017cd50;
static char (*const b13a5f0_cab9c0)(void) = FUN_000ab9c0;
static void *(*const b13a5f0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13a5f0_tag)(int, int) = tag_get;
static int16_t (*const b13a5f0_c139350)(int light_handle, int16_t *out_buffer, int16_t max_count) = FUN_00139350;
static void (*const b13a5f0_c13a250)(int light_handle, float *out_position, float *out_radius, char param_1, char param_2, char param_3) = FUN_0013a250;
static void (*const b13a5f0_c195f30)(int object_handle, float *position, float radius, int gel_count, int gel_buffer) = FUN_00195f30;
static void (*const b13a5f0_c17cd90)(void) = FUN_0017cd90;

__attribute__((naked, noinline))
void FUN_0013a5f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x41c, %%esp\n\t"
      "call *%[c17cd50]\n\t"
      "movl 0x46f074, %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LFUN_0013a5f0_7\n\t"
      "call *%[cab9c0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013a5f0_7\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x5a8d68\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jle .LFUN_0013a5f0_6\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0013a5f0_1:\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "movl 0x5a8d6c(,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x2(%%esi), %%al\n\t"
      "movb $1, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%bl\n\t"
      "je .LFUN_0013a5f0_5\n\t"
      "cmpl $-1, 0x8(%%esi)\n\t"
      "je .LFUN_0013a5f0_5\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $2, %%cl\n\t"
      "jne .LFUN_0013a5f0_5\n\t"
      "testb $8, 0x2(%%esi)\n\t"
      "je .LFUN_0013a5f0_2\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jne .LFUN_0013a5f0_3\n\t"
      ".LFUN_0013a5f0_2:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0013a5f0_3:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jne .LFUN_0013a5f0_4\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "movl 0x5a8d6c(,%%eax,4), %%eax\n\t"
      "leal -0x41c(%%ebp), %%ebx\n\t"
      "movl $0x200, %%edi\n\t"
      "call *%[c139350]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_0013a5f0_4:\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "movl 0x5a8d6c(,%%eax,4), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "leal -0x1c(%%ebp), %%edi\n\t"
      "call *%[c13a250]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%dl\n\t"
      "leal -0x41c(%%ebp), %%eax\n\t"
      "decl %%edx\n\t"
      "andl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c195f30]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_0013a5f0_5:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x5a8d68, %%di\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jl .LFUN_0013a5f0_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013a5f0_6:\n\t"
      "popl %%edi\n\t"
      ".LFUN_0013a5f0_7:\n\t"
      "call *%[c17cd90]\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c17cd50] "m"(b13a5f0_c17cd50), [cab9c0] "m"(b13a5f0_cab9c0), [dget] "m"(b13a5f0_dget), [tag] "m"(b13a5f0_tag), [c139350] "m"(b13a5f0_c139350), [c13a250] "m"(b13a5f0_c13a250), [c195f30] "m"(b13a5f0_c195f30), [c17cd90] "m"(b13a5f0_c17cd90)
      : "memory");
}
#else
#error "FUN_0013a5f0: clang naked draft required"
#endif


/* FUN_0013a250 (0x13a250) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b13a250_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13a250_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_0013a250(int light_handle __attribute__((unused)), float *out_position __attribute__((unused)), float *out_radius __attribute__((unused)), char param_1 __attribute__((unused)), char param_2 __attribute__((unused)), char param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013a250_1\n\t"
      "flds 0xc(%%ecx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "jmp .LFUN_0013a250_2\n\t"
      ".LFUN_0013a250_1:\n\t"
      "flds 0x54(%%esi)\n\t"
      ".LFUN_0013a250_2:\n\t"
      "testb $2, (%%ecx)\n\t"
      "jne .LFUN_0013a250_4\n\t"
      "movb 0xc(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_0013a250_3\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013a250_4\n\t"
      ".LFUN_0013a250_3:\n\t"
      "fmuls 0x24(%%ecx)\n\t"
      ".LFUN_0013a250_4:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013a250_5\n\t"
      "fcoms 0x18(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a250_5\n\t"
      "addl $0x30, %%esi\n\t"
      "fstp %%st(0)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl 0x18(%%ecx), %%ecx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013a250_5:\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a250_8\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x254a58\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a250_7\n\t"
      "fdivs 0x20(%%ecx)\n\t"
      "fsts (%%ebx)\n\t"
      ".LFUN_0013a250_6:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "fadds 0x34(%%esi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "fadds 0x38(%%esi)\n\t"
      "popl %%esi\n\t"
      "fstps 0x8(%%edi)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013a250_7:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%ecx)\n\t"
      "fstps (%%ebx)\n\t"
      "fmuls 0x20(%%ecx)\n\t"
      "jmp .LFUN_0013a250_6\n\t"
      ".LFUN_0013a250_8:\n\t"
      "addl $0x30, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "fstps (%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13a250_dget), [tag] "m"(b13a250_tag)
      : "memory");
}
#else
#error "FUN_0013a250: clang naked draft required"
#endif


/* FUN_0013a420 (0x13a420) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void (*const b13a420_c17cc50)(void) = FUN_0017cc50;
static char (*const b13a420_cab9c0)(void) = FUN_000ab9c0;
static void *(*const b13a420_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13a420_tag)(int, int) = tag_get;
static int16_t (*const b13a420_c139350)(int light_handle, int16_t *out_buffer, int16_t max_count) = FUN_00139350;
static void (*const b13a420_c196060)(int object_handle, float *position, float radius, int gel_count, int gel_buffer) = FUN_00196060;
static void (*const b13a420_c17cc90)(void) = FUN_0017cc90;

__attribute__((naked, noinline))
void FUN_0013a420(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x41c, %%esp\n\t"
      "call *%[c17cc50]\n\t"
      "movl 0x46f074, %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LFUN_0013a420_10\n\t"
      "call *%[cab9c0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013a420_10\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x5a8d68\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "jle .LFUN_0013a420_9\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0013a420_1:\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "movswl %%di, %%esi\n\t"
      "movl 0x5a8d6c(,%%esi,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%al\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "je .LFUN_0013a420_8\n\t"
      "cmpl $-1, 0x8(%%ebx)\n\t"
      "je .LFUN_0013a420_8\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_0013a420_2\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0013a420_3\n\t"
      ".LFUN_0013a420_2:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0013a420_3:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jne .LFUN_0013a420_4\n\t"
      "movl 0x5a8d6c(,%%esi,4), %%eax\n\t"
      "leal -0x41c(%%ebp), %%ebx\n\t"
      "movl $0x200, %%edi\n\t"
      "call *%[c139350]\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".LFUN_0013a420_4:\n\t"
      "movl 0x5a8d6c(,%%esi,4), %%esi\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "flds 0x54(%%edi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x14(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a420_6\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x254a58\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a420_5\n\t"
      "fdivs 0x20(%%ecx)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fadds 0x30(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      "fadds 0x38(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .LFUN_0013a420_7\n\t"
      ".LFUN_0013a420_5:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%ecx)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0x20(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fadds 0x30(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fmuls 0x44(%%edi)\n\t"
      "fadds 0x38(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .LFUN_0013a420_7\n\t"
      ".LFUN_0013a420_6:\n\t"
      "addl $0x30, %%edi\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".LFUN_0013a420_7:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%al\n\t"
      "leal -0x41c(%%ebp), %%ecx\n\t"
      "decl %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c196060]\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013a420_8:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x5a8d68, %%di\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "jl .LFUN_0013a420_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013a420_9:\n\t"
      "popl %%edi\n\t"
      ".LFUN_0013a420_10:\n\t"
      "call *%[c17cc90]\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c17cc50] "m"(b13a420_c17cc50), [cab9c0] "m"(b13a420_cab9c0), [dget] "m"(b13a420_dget), [tag] "m"(b13a420_tag), [c139350] "m"(b13a420_c139350), [c196060] "m"(b13a420_c196060), [c17cc90] "m"(b13a420_c17cc90)
      : "memory");
}
#else
#error "FUN_0013a420: clang naked draft required"
#endif


/* FUN_0013b1b0 (0x13b1b0) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const b13b1b0_tag)(int, int) = tag_get;
static int (*const b13b1b0_c119610)(data_t *data) = data_new_at_index;
static void *(*const b13b1b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b13b1b0_c13aed0)(int object_handle) = object_move_to_limbo;

__attribute__((naked, noinline))
int FUN_0013b1b0(int tag_index __attribute__((unused)), int object_handle __attribute__((unused)), short attachment_index __attribute__((unused)), short marker_index __attribute__((unused)), short secondary_marker_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb (%%edi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "testb $1, %%cl\n\t"
      "jne .LFUN_0013b1b0_1\n\t"
      "cmpl $-1, 0xb8(%%edi)\n\t"
      "je .LFUN_0013b1b0_5\n\t"
      ".LFUN_0013b1b0_1:\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_0013b1b0_4\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movw 0x10(%%ebp), %%dx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "movl %%ecx, 0x2c(%%esi)\n\t"
      "movw 0x18(%%ebp), %%cx\n\t"
      "movw %%ax, 0x5e(%%esi)\n\t"
      "movw $0, 0x2(%%esi)\n\t"
      "movw %%dx, 0x5c(%%esi)\n\t"
      "movw %%cx, 0x60(%%esi)\n\t"
      "movb (%%edi), %%dl\n\t"
      "andb $1, %%dl\n\t"
      "movzbw %%dl, %%ax\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_0013b1b0_2\n\t"
      "cmpl %%ecx, 0xb8(%%edi)\n\t"
      "jne .LFUN_0013b1b0_2\n\t"
      "andl $0xfffd, %%eax\n\t"
      "jmp .LFUN_0013b1b0_3\n\t"
      ".LFUN_0013b1b0_2:\n\t"
      "orl $2, %%eax\n\t"
      ".LFUN_0013b1b0_3:\n\t"
      "pushl %%ebx\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "movl %%ecx, 0x58(%%esi)\n\t"
      "call *%[c13aed0]\n\t"
      "movl 0x5a8d64, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      ".LFUN_0013b1b0_4:\n\t"
      "movl %%ebx, %%eax\n\t"
      ".LFUN_0013b1b0_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b13b1b0_tag), [c119610] "m"(b13b1b0_c119610), [dget] "m"(b13b1b0_dget), [c13aed0] "m"(b13b1b0_c13aed0)
      : "memory");
}
#else
#error "FUN_0013b1b0: clang naked draft required"
#endif


/* FUN_0013b290 (0x13b290) — XBE naked draft (batch 62). */
#if defined(__clang__)
static int (*const b13b290_c119610)(data_t *data) = data_new_at_index;
static void *(*const b13b290_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13b290_tag)(int, int) = tag_get;
static int (*const b13b290_gtime)(void) = game_time_get;
static void (*const b13b290_c13aed0)(int object_handle) = object_move_to_limbo;

__attribute__((naked, noinline))
int FUN_0013b290(int tag_index __attribute__((unused)), int object_handle __attribute__((unused)), int16_t marker __attribute__((unused)), float *position __attribute__((unused)), float *forward __attribute__((unused)), int unknown __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0013b290_3\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x6c696768\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "movw $0, 0x2(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "orb $3, 0x2(%%esi)\n\t"
      "movl %%eax, 0x58(%%esi)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "movl %%eax, 0x2c(%%esi)\n\t"
      "movl %%edx, 0x78(%%esi)\n\t"
      "movl $0xffffffff, 0x10(%%esi)\n\t"
      "jne .LFUN_0013b290_1\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .LFUN_0013b290_2\n\t"
      ".LFUN_0013b290_1:\n\t"
      "movw 0x10(%%ebp), %%cx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movw %%cx, 0x5c(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x60(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x6c(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      ".LFUN_0013b290_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[c13aed0]\n\t"
      "movl 0x5a8d64, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013b290_3:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119610] "m"(b13b290_c119610), [dget] "m"(b13b290_dget), [tag] "m"(b13b290_tag), [gtime] "m"(b13b290_gtime), [c13aed0] "m"(b13b290_c13aed0)
      : "memory");
}
#else
#error "FUN_0013b290: clang naked draft required"
#endif


/* FUN_0013bce0 (0x13bce0) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const b13bce0_get)(int, int) = object_get_and_verify_type;
static void (*const b13bce0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13bce0_exitfn)(int) = system_exit;
static void *(*const b13bce0_tag)(int, int) = tag_get;
static char (*const b13bce0_c13ab20)(unsigned int param_1, int param_2, int *param_3) = FUN_0013ab20;
static void *(*const b13bce0_memset)(void *, int, unsigned int) = csmemset;
static float (*const b13bce0_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
void FUN_0013bce0(int object_handle __attribute__((unused)), float *lighting __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .LFUN_0013bce0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3ca\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x291690\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013bce0_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testb %%ah, %%ah\n\t"
      "jns .LFUN_0013bce0_2\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      ".LFUN_0013bce0_2:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_0013bce0_3\n\t"
      "orl $4, -0x4(%%ebp)\n\t"
      ".LFUN_0013bce0_3:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x50(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c13ab20]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x40, %%ch\n\t"
      "jne .LFUN_0013bce0_12\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013bce0_4\n\t"
      "movl $1, 0xc(%%ebp)\n\t"
      "jmp .LFUN_0013bce0_5\n\t"
      ".LFUN_0013bce0_4:\n\t"
      "pushl $0x74\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $2, 0xc(%%edi)\n\t"
      ".LFUN_0013bce0_5:\n\t"
      "testb $1, %%bl\n\t"
      "je .LFUN_0013bce0_6\n\t"
      "flds 0x254b50\n\t"
      "jmp .LFUN_0013bce0_7\n\t"
      ".LFUN_0013bce0_6:\n\t"
      "flds 0x29b5e0\n\t"
      ".LFUN_0013bce0_7:\n\t"
      "testb $2, %%bl\n\t"
      "fmuls 0x5c(%%esi)\n\t"
      "fadds 0x50(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "je .LFUN_0013bce0_8\n\t"
      "flds 0x254b50\n\t"
      "jmp .LFUN_0013bce0_9\n\t"
      ".LFUN_0013bce0_8:\n\t"
      "flds 0x29b5e0\n\t"
      ".LFUN_0013bce0_9:\n\t"
      "fmuls 0x5c(%%esi)\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x54(%%esi)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c13ab20]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013bce0_10\n\t"
      "flds -0x84(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fadds (%%edi)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "fstps (%%edi)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fadds 0x4c(%%edi)\n\t"
      "fstps 0x4c(%%edi)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fadds 0x50(%%edi)\n\t"
      "fstps 0x50(%%edi)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fadds 0x54(%%edi)\n\t"
      "fstps 0x54(%%edi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fadds 0x58(%%edi)\n\t"
      "fstps 0x58(%%edi)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "fstps 0x10(%%edi)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fadds 0x14(%%edi)\n\t"
      "fstps 0x14(%%edi)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fadds 0x18(%%edi)\n\t"
      "fstps 0x18(%%edi)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fadds 0x1c(%%edi)\n\t"
      "fstps 0x1c(%%edi)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fadds 0x20(%%edi)\n\t"
      "fstps 0x20(%%edi)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fadds 0x24(%%edi)\n\t"
      "fstps 0x24(%%edi)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fadds 0x28(%%edi)\n\t"
      "fstps 0x28(%%edi)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fadds 0x2c(%%edi)\n\t"
      "fstps 0x2c(%%edi)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fadds 0x30(%%edi)\n\t"
      "fstps 0x30(%%edi)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps 0x34(%%edi)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fadds 0x38(%%edi)\n\t"
      "fstps 0x38(%%edi)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fadds 0x3c(%%edi)\n\t"
      "fstps 0x3c(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x68(%%edi)\n\t"
      "fstps 0x68(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x6c(%%edi)\n\t"
      "fstps 0x6c(%%edi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x70(%%edi)\n\t"
      "fstps 0x70(%%edi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds 0x5c(%%edi)\n\t"
      "fstps 0x5c(%%edi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fadds 0x60(%%edi)\n\t"
      "fstps 0x60(%%edi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fadds 0x64(%%edi)\n\t"
      "fstps 0x64(%%edi)\n\t"
      ".LFUN_0013bce0_10:\n\t"
      "incl %%ebx\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_0013bce0_5\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .LFUN_0013bce0_11\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps (%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4c(%%edi)\n\t"
      "fstps 0x4c(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x50(%%edi)\n\t"
      "fstps 0x50(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x54(%%edi)\n\t"
      "fstps 0x54(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x58(%%edi)\n\t"
      "fstps 0x58(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fstps 0x10(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fstps 0x14(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fstps 0x18(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal 0x34(%%edi), %%eax\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x28(%%edi)\n\t"
      "fstps 0x28(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "fstps 0x2c(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "fstps 0x30(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x68(%%edi)\n\t"
      "fstps 0x68(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x6c(%%edi)\n\t"
      "fstps 0x6c(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x70(%%edi)\n\t"
      "fstps 0x70(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "pushl %%eax\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "addl $0xc, %%esp\n\t"
      "fstp %%st(0)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013bce0_11:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0013bce0_12\n\t"
      "movl $0x1d, %%ecx\n\t"
      "leal -0x84(%%ebp), %%esi\n\t"
      "rep movsl\n\t"
      ".LFUN_0013bce0_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13bce0_get), [assert] "m"(b13bce0_assert), [exitfn] "m"(b13bce0_exitfn), [tag] "m"(b13bce0_tag), [c13ab20] "m"(b13bce0_c13ab20), [memset] "m"(b13bce0_memset), [norm] "m"(b13bce0_norm)
      : "memory");
}
#else
#error "FUN_0013bce0: clang naked draft required"
#endif


/* FUN_0013b150 (0x13b150) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b13b150_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b13b150_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b13b150_c13aed0)(int object_handle) = object_move_to_limbo;

__attribute__((naked, noinline))
void FUN_0013b150(void)
{
  __asm__ volatile(
      "movl 0x5a90bc, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0013b150_3\n\t"
      ".LFUN_0013b150_1:\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_0013b150_2\n\t"
      "andl $0xfffb, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movw %%cx, 0x2(%%eax)\n\t"
      "call *%[c13aed0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013b150_2:\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_0013b150_1\n\t"
      ".LFUN_0013b150_3:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b13b150_c1198f0), [dget] "m"(b13b150_dget), [c13aed0] "m"(b13b150_c13aed0)
      : "memory");
}
#else
#error "FUN_0013b150: clang naked draft required"
#endif


/* FUN_0013c030 (0x13c030) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b13c030_get)(int, int) = object_get_and_verify_type;
static void (*const b13c030_c13c030)(int param_1, int param_2, int param_3) = FUN_0013c030;

__attribute__((naked, noinline))
void FUN_0013c030(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0013c030_2\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      ".LFUN_0013c030_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0xc8(%%edi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c030]\n\t"
      "movl 0xc4(%%edi), %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_0013c030_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013c030_2:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c030_get), [c13c030] "m"(b13c030_c13c030)
      : "memory");
}
#else
#error "FUN_0013c030: clang naked draft required"
#endif


/* FUN_0013c100 (0x13c100) — XBE naked draft (batch 65). */
#if defined(__clang__)
static char * (*const b13c100_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13c100_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13c100_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void * FUN_0013c100(int16_t object_type __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_0013c100_1\n\t"
      "cmpw $0xc, %%si\n\t"
      "jl .LFUN_0013c100_2\n\t"
      ".LFUN_0013c100_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x277\n\t"
      "pushl $0x29b6b8\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29b68c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013c100_2:\n\t"
      "movswl %%si, %%esi\n\t"
      "movl 0x324608(,%%esi,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0013c100_3\n\t"
      "pushl $1\n\t"
      "pushl $0x278\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013c100_3:\n\t"
      "movl 0x324608(,%%esi,4), %%ecx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0013c100_4\n\t"
      "pushl $1\n\t"
      "pushl $0x279\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b634\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013c100_4:\n\t"
      "movl 0x324608(,%%esi,4), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8d9d0] "m"(b13c100_c8d9d0), [assert] "m"(b13c100_assert), [exitfn] "m"(b13c100_exitfn)
      : "memory");
}
#else
#error "FUN_0013c100: clang naked draft required"
#endif


/* FUN_0013c1b0 (0x13c1b0) — XBE naked draft (batch 66). */
#if defined(__clang__)
static char * (*const b13c1b0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13c1b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13c1b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
short FUN_0013c1b0(short param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_0013c1b0_1\n\t"
      "cmpw $0xc, %%si\n\t"
      "jl .LFUN_0013c1b0_2\n\t"
      ".LFUN_0013c1b0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x282\n\t"
      "pushl $0x29b6b8\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29b68c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013c1b0_2:\n\t"
      "movswl %%si, %%esi\n\t"
      "movl 0x324608(,%%esi,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0013c1b0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x283\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x324608(,%%esi,4), %%ecx\n\t"
      "movw 0x8(%%ecx), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013c1b0_3:\n\t"
      "movl 0x324608(,%%esi,4), %%edx\n\t"
      "movw 0x8(%%edx), %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8d9d0] "m"(b13c1b0_c8d9d0), [assert] "m"(b13c1b0_assert), [exitfn] "m"(b13c1b0_exitfn)
      : "memory");
}
#else
#error "FUN_0013c1b0: clang naked draft required"
#endif


/* FUN_0013c490 (0x13c490) — XBE naked draft (batch 65). */
#if defined(__clang__)
static void *(*const b13c490_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c490_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
int FUN_0013c490(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%edx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edx, %%edx\n\t"
      "movb $1, %%cl\n\t"
      "je .LFUN_0013c490_4\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0013c490_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x24(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c490_2\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013c490_3\n\t"
      ".LFUN_0013c490_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal 0x5c(%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LFUN_0013c490_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013c490_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013c490_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c490_get), [c13c100] "m"(b13c490_c13c100)
      : "memory");
}
#else
#error "FUN_0013c490: clang naked draft required"
#endif


/* FUN_0013c250 (0x13c250) — XBE naked draft (batch 66). */
#if defined(__clang__)
static char * (*const b13c250_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13c250_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13c250_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void * FUN_0013c250(int16_t param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_0013c250_1\n\t"
      "cmpw $0xc, %%si\n\t"
      "jl .LFUN_0013c250_2\n\t"
      ".LFUN_0013c250_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x28c\n\t"
      "pushl $0x29b6b8\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29b68c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013c250_2:\n\t"
      "movswl %%si, %%esi\n\t"
      "movl 0x324608(,%%esi,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0013c250_3\n\t"
      "pushl $1\n\t"
      "pushl $0x28d\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x324608(,%%esi,4), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013c250_3:\n\t"
      "movl 0x324608(,%%esi,4), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8d9d0] "m"(b13c250_c8d9d0), [assert] "m"(b13c250_assert), [exitfn] "m"(b13c250_exitfn)
      : "memory");
}
#else
#error "FUN_0013c250: clang naked draft required"
#endif


/* FUN_0013c2e0 (0x13c2e0) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void * (*const b13c2e0_c13c100)(int16_t object_type) = FUN_0013c100;
static void (*const b13c2e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13c2e0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_0013c2e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x5a8d54, %%ebx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_0013c2e0_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x9c(%%esi), %%eax\n\t"
      "leal 0x9c(%%esi), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c2e0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2ea\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b6e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013c2e0_2:\n\t"
      "movl %%esi, (%%ebx)\n\t"
      "movl %%edi, %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      ".LFUN_0013c2e0_3:\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movl 0x5c(%%esi,%%ecx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c2e0_5\n\t"
      "movl 0x9c(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "leal 0x9c(%%eax), %%ecx\n\t"
      "jne .LFUN_0013c2e0_4\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".LFUN_0013c2e0_4:\n\t"
      "incl %%edx\n\t"
      "cmpw $0x10, %%dx\n\t"
      "jl .LFUN_0013c2e0_3\n\t"
      ".LFUN_0013c2e0_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw $0xc, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_0013c2e0_1\n\t"
      "movl $0, (%%ebx)\n\t"
      "movl 0x5a8d54, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0013c2e0_8\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0013c2e0_6:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c2e0_7\n\t"
      "call *%%eax\n\t"
      ".LFUN_0013c2e0_7:\n\t"
      "movl 0x9c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0013c2e0_6\n\t"
      ".LFUN_0013c2e0_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c13c100] "m"(b13c2e0_c13c100), [assert] "m"(b13c2e0_assert), [exitfn] "m"(b13c2e0_exitfn)
      : "memory");
}
#else
#error "FUN_0013c2e0: clang naked draft required"
#endif


/* Walk the object type definition list and call dispose at +0x14 on each.
 * 0x13c3a0 / objects.obj
 */
void FUN_0013c3a0(void)
{
  int iVar1;

  for (iVar1 = *(int *)0x5a8d54; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x9c)) {
    if (*(void (**)(void))(iVar1 + 0x14) != 0) {
      (*(void (**)(void))(iVar1 + 0x14))();
    }
  }
}

/* Reset slot counter, walk the list and call initialize_for_new_map at +0x18.
 * 0x13c3d0 / objects.obj
 */
void FUN_0013c3d0(void)
{
  int iVar1;

  *(int *)0x46f078 = 0;
  for (iVar1 = *(int *)0x5a8d54; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x9c)) {
    if (*(void (**)(void))(iVar1 + 0x18) != 0) {
      (*(void (**)(void))(iVar1 + 0x18))();
    }
  }
}

/* Walk the object type definition list and call dispose_from_old_map at +0x1c.
 * 0x13c400 / objects.obj
 */
void FUN_0013c400(void)
{
  int iVar1;

  for (iVar1 = *(int *)0x5a8d54; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x9c)) {
    if (*(void (**)(void))(iVar1 + 0x1c) != 0) {
      (*(void (**)(void))(iVar1 + 0x1c))();
    }
  }
}

/* FUN_0013c430 (0x13c430) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b13c430_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c430_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c430(int param_1 __attribute__((unused)), void *param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c430_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c430_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c430_2\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013c430_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x5c(%%edi,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%edx,4), %%eax\n\t"
      "jne .LFUN_0013c430_1\n\t"
      ".LFUN_0013c430_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c430_get), [c13c100] "m"(b13c430_c13c100)
      : "memory");
}
#else
#error "FUN_0013c430: clang naked draft required"
#endif


/* FUN_0013c500 (0x13c500) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13c500_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c500_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c500(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c500_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c500_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c500_2\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013c500_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x5c(%%edi,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%edx,4), %%eax\n\t"
      "jne .LFUN_0013c500_1\n\t"
      ".LFUN_0013c500_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c500_get), [c13c100] "m"(b13c500_c13c100)
      : "memory");
}
#else
#error "FUN_0013c500: clang naked draft required"
#endif


/* FUN_0013c560 (0x13c560) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b13c560_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c560_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c560(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c560_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c560_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c560_2\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013c560_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal 0x5c(%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LFUN_0013c560_1\n\t"
      ".LFUN_0013c560_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c560_get), [c13c100] "m"(b13c560_c13c100)
      : "memory");
}
#else
#error "FUN_0013c560: clang naked draft required"
#endif


/* FUN_0013c5c0 (0x13c5c0) — XBE naked draft (batch 66). */
#if defined(__clang__)
static void *(*const b13c5c0_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c5c0_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
int FUN_0013c5c0(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x64(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c5c0_3\n\t"
      ".LFUN_0013c5c0_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x30(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c5c0_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013c5c0_2\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_0013c5c0_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x5c(%%edi,%%eax,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%eax,4), %%eax\n\t"
      "jne .LFUN_0013c5c0_1\n\t"
      ".LFUN_0013c5c0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c5c0_get), [c13c100] "m"(b13c5c0_c13c100)
      : "memory");
}
#else
#error "FUN_0013c5c0: clang naked draft required"
#endif


/* FUN_0013c620 (0x13c620) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b13c620_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c620_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c620(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c620_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c620_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c620_2\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013c620_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal 0x5c(%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LFUN_0013c620_1\n\t"
      ".LFUN_0013c620_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c620_get), [c13c100] "m"(b13c620_c13c100)
      : "memory");
}
#else
#error "FUN_0013c620: clang naked draft required"
#endif


/* FUN_0013c680 (0x13c680) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13c680_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c680_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c680(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c680_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c680_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x38(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c680_2\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013c680_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x5c(%%edi,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%edx,4), %%eax\n\t"
      "jne .LFUN_0013c680_1\n\t"
      ".LFUN_0013c680_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c680_get), [c13c100] "m"(b13c680_c13c100)
      : "memory");
}
#else
#error "FUN_0013c680: clang naked draft required"
#endif


/*
 * FUN_0013c6e0 — dispatch a region-destroyed callback through the object
 * type definition's extension table.
 *
 * Resolves the object's type, looks up its type definition via FUN_0013c100,
 * then walks the pointer array at type_def+0x5c. For each non-NULL entry,
 * reads a function pointer at entry+0x3c and calls it with the original
 * three arguments (object_handle, param_2, param_3).
 *
 * Called from damage.c (FUN_00137690) when a region is destroyed, passing
 * (object_handle, region_index, region_flags).
 *
 * Confirmed: cdecl, 3 args (ADD ESP,0xc at caller and inside loop).
 * Confirmed: MOVSX word [EAX+0x64] — reads object type as int16_t.
 * Confirmed: PUSH -1, PUSH EBX -> object_get_and_verify_type(handle, -1).
 * Confirmed: loop counter is int16_t (MOVSX EAX,SI at 0x13c728).
 * Confirmed: vtable offset 0x3c (MOV EAX,[EAX+0x3c] at 0x13c712).
 * Confirmed: indirect call passes all 3 params (PUSH ECX/EDX/EBX at
 * 0x13c71f-0x13c721).
 */
/* FUN_0013c6e0 (0x13c6e0) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13c6e0_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c6e0_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c6e0(int object_handle __attribute__((unused)), int region_index __attribute__((unused)), unsigned int flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c6e0_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c6e0_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x3c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c6e0_2\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0013c6e0_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x5c(%%edi,%%eax,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%eax,4), %%eax\n\t"
      "jne .LFUN_0013c6e0_1\n\t"
      ".LFUN_0013c6e0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c6e0_get), [c13c100] "m"(b13c6e0_c13c100)
      : "memory");
}
#else
#error "FUN_0013c6e0: clang naked draft required"
#endif


/*
 * FUN_0013c740 — walk the object type definition extension table and check
 * whether any extension's callback at offset +0x40 returns true.
 *
 * Resolves the object's type via object_get_and_verify_type(-1), looks up
 * the type definition via FUN_0013c100, then walks the NULL-terminated
 * pointer array at type_def+0x5c. For each non-NULL entry, reads a function
 * pointer at entry+0x40 and calls it with the object handle. If any callback
 * returns non-zero, the function returns 1 (sticky OR).
 *
 * Called from FUN_00136840, which recursively walks child objects. If this
 * function returns 0, the caller recurses into the child.
 *
 * Confirmed: cdecl, 1 arg (ADD ESP,0x4 after indirect CALL).
 * Confirmed: returns char/bool in AL (MOV AL,BL at 0x13c79a).
 * Confirmed: MOVSX EAX,SI — loop counter is int16_t.
 * Confirmed: vtable offset +0x40 (MOV EAX,[EAX+0x40] at 0x13c772).
 * Confirmed: XOR BL,BL — result initialized to 0, set to 1 on any true return.
 */
/* FUN_0013c740 (0x13c740) — XBE naked draft (batch 66). */
#if defined(__clang__)
static void *(*const b13c740_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c740_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
char FUN_0013c740(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x64(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c740_3\n\t"
      ".LFUN_0013c740_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x40(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c740_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013c740_2\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_0013c740_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x5c(%%edi,%%eax,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%eax,4), %%eax\n\t"
      "jne .LFUN_0013c740_1\n\t"
      ".LFUN_0013c740_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c740_get), [c13c100] "m"(b13c740_c13c100)
      : "memory");
}
#else
#error "FUN_0013c740: clang naked draft required"
#endif


/* FUN_0013c7a0 (0x13c7a0) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13c7a0_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c7a0_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c7a0(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c7a0_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c7a0_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c7a0_2\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013c7a0_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x5c(%%edi,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%edx,4), %%eax\n\t"
      "jne .LFUN_0013c7a0_1\n\t"
      ".LFUN_0013c7a0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c7a0_get), [c13c100] "m"(b13c7a0_c13c100)
      : "memory");
}
#else
#error "FUN_0013c7a0: clang naked draft required"
#endif


/*
 * FUN_0013c800 — dispatch an animation-block initializer callback through the
 * object type definition's extension table.
 *
 * Resolves the object's type, looks up its type definition via FUN_0013c100,
 * then walks the NULL-terminated pointer array at type_def+0x5c. For each
 * non-NULL entry, reads a function pointer at entry+0x48 and calls it with
 * (object_handle, block_data).
 *
 * Called from FUN_0013e1a0 after resolving the animation block reference,
 * passing the object handle and the resolved block data pointer.
 *
 * Confirmed: cdecl, 2 args (ADD ESP,0x8 after indirect CALL).
 * Confirmed: MOVSX word [EAX+0x64] — reads object type as int16_t.
 * Confirmed: PUSH -1, PUSH EBX -> object_get_and_verify_type(handle, -1).
 * Confirmed: loop counter is int16_t (MOVSX EDX,SI at 0x13c844).
 * Confirmed: vtable offset 0x48 (MOV EAX,[EAX+0x48] at 0x13c832).
 * Confirmed: indirect call passes 2 params (PUSH ECX, PUSH EBX at
 * 0x13c83c-0x13c83d).
 */
/* FUN_0013c800 (0x13c800) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13c800_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c800_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c800(int object_handle __attribute__((unused)), void *block_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c800_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c800_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x48(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c800_2\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013c800_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x5c(%%edi,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%edx,4), %%eax\n\t"
      "jne .LFUN_0013c800_1\n\t"
      ".LFUN_0013c800_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c800_get), [c13c100] "m"(b13c800_c13c100)
      : "memory");
}
#else
#error "FUN_0013c800: clang naked draft required"
#endif


/* FUN_0013c860 (0x13c860) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b13c860_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c860_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c860(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c860_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c860_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x4c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c860_2\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013c860_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal 0x5c(%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LFUN_0013c860_1\n\t"
      ".LFUN_0013c860_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c860_get), [c13c100] "m"(b13c860_c13c100)
      : "memory");
}
#else
#error "FUN_0013c860: clang naked draft required"
#endif


/* FUN_0013c8c0 (0x13c8c0) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b13c8c0_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c8c0_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c8c0(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c8c0_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c8c0_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x50(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c8c0_2\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013c8c0_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal 0x5c(%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LFUN_0013c8c0_1\n\t"
      ".LFUN_0013c8c0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c8c0_get), [c13c100] "m"(b13c8c0_c13c100)
      : "memory");
}
#else
#error "FUN_0013c8c0: clang naked draft required"
#endif


/* FUN_0013c920 (0x13c920) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b13c920_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c920_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c920(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c920_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c920_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x58(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c920_2\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013c920_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "leal 0x5c(%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jne .LFUN_0013c920_1\n\t"
      ".LFUN_0013c920_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c920_get), [c13c100] "m"(b13c920_c13c100)
      : "memory");
}
#else
#error "FUN_0013c920: clang naked draft required"
#endif


/* FUN_0013c980 (0x13c980) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13c980_get)(int, int) = object_get_and_verify_type;
static void * (*const b13c980_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
void FUN_0013c980(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movswl 0x64(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "leal 0x5c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013c980_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c980_1:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x54(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013c980_2\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0013c980_2:\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x5c(%%edi,%%eax,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x5c(%%edi,%%eax,4), %%eax\n\t"
      "jne .LFUN_0013c980_1\n\t"
      ".LFUN_0013c980_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c980_get), [c13c100] "m"(b13c980_c13c100)
      : "memory");
}
#else
#error "FUN_0013c980: clang naked draft required"
#endif


/* FUN_0013c9e0 (0x13c9e0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b13c9e0_c1ba210)(int tag_index) = tag_get_group_tag;
static void * (*const b13c9e0_c13c100)(int16_t object_type) = FUN_0013c100;

__attribute__((naked, noinline))
unsigned short FUN_0013c9e0(int tag_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba210]\n\t"
      "addl $4, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013c9e0_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c13c100]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .LFUN_0013c9e0_2\n\t"
      "incl %%esi\n\t"
      "cmpw $0xc, %%si\n\t"
      "jl .LFUN_0013c9e0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013c9e0_2:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1ba210] "m"(b13c9e0_c1ba210), [c13c100] "m"(b13c9e0_c13c100)
      : "memory");
}
#else
#error "FUN_0013c9e0: clang naked draft required"
#endif


/* FUN_0013ca30 (0x13ca30) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void * (*const b13ca30_c13c100)(int16_t object_type) = FUN_0013c100;
static void (*const b13ca30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13ca30_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_0013ca30(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, 0xa(%%esi)\n\t"
      "jne .LFUN_0013ca30_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4ff\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b780\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013ca30_1:\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0013ca30_2\n\t"
      "cmpw $0x5bc, %%ax\n\t"
      "jbe .LFUN_0013ca30_3\n\t"
      ".LFUN_0013ca30_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x500\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b6f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013ca30_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013ca30_4\n\t"
      "movswl 0xe(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_0013ca30_4:\n\t"
      "movswl 0xa(%%esi), %%eax\n\t"
      "addl 0x8(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c13c100] "m"(b13ca30_c13c100), [assert] "m"(b13ca30_assert), [exitfn] "m"(b13ca30_exitfn)
      : "memory");
}
#else
#error "FUN_0013ca30: clang naked draft required"
#endif


/* FUN_0013cab0 (0x13cab0) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void * (*const b13cab0_c13c100)(int16_t object_type) = FUN_0013c100;
static void (*const b13cab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13cab0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_0013cab0(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c100]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, 0xc(%%esi)\n\t"
      "jne .LFUN_0013cab0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x50d\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b834\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cab0_1:\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0013cab0_2\n\t"
      "cmpw $0x5bc, %%ax\n\t"
      "jbe .LFUN_0013cab0_3\n\t"
      ".LFUN_0013cab0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x50e\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b7b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cab0_3:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "addl 0x8(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c13c100] "m"(b13cab0_c13c100), [assert] "m"(b13cab0_assert), [exitfn] "m"(b13cab0_exitfn)
      : "memory");
}
#else
#error "FUN_0013cab0: clang naked draft required"
#endif


/* FUN_0013cb30 (0x13cb30) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void (*const b13cb30_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const b13cb30_c13d730)(void *iter) = object_iterator_next;
static void (*const b13cb30_odel)(int) = object_delete;

__attribute__((naked, noinline))
void FUN_0013cb30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0x240\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d730]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013cb30_3\n\t"
      ".LFUN_0013cb30_1:\n\t"
      "cmpw $-1, 0x6a(%%eax)\n\t"
      "jne .LFUN_0013cb30_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013cb30_2:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d730]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0013cb30_1\n\t"
      ".LFUN_0013cb30_3:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c13d6f0] "m"(b13cb30_c13d6f0), [c13d730] "m"(b13cb30_c13d730), [odel] "m"(b13cb30_odel)
      : "memory");
}
#else
#error "FUN_0013cb30: clang naked draft required"
#endif


/* FUN_0013cb80 (0x13cb80) — XBE naked draft (batch 58). */
#if defined(__clang__)
static bool (*const b13cb80_c977f0)(void) = game_in_editor;
static scenario_t * (*const b13cb80_c18e380)(void) = global_scenario_get;
static void * (*const b13cb80_c13c100)(int16_t object_type) = FUN_0013c100;
static int (*const b13cb80_c13ca30)(int param_1, int param_2, int *param_3) = FUN_0013ca30;
static int (*const b13cb80_c13cab0)(int param_1, int param_2) = FUN_0013cab0;
static void *(*const b13cb80_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b13cb80_tag)(int, int) = tag_get;
static void (*const b13cb80_c109e90)(float *out, float yaw, float pitch, float roll) = FUN_00109e90;
static void (*const b13cb80_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static int (*const b13cb80_c18e720)(int point) = FUN_0018e720;
static void (*const b13cb80_c145490)(void) = FUN_00145490;
static int (*const b13cb80_c140720)(int16_t index) = object_name_list_get_handle;
static int (*const b13cb80_c144770)(void *placement_data, int palette_block) = object_new_from_scenario;
static void (*const b13cb80_c144b50)(void) = objects_garbage_collect_tick;

__attribute__((naked, noinline))
void FUN_0013cb80(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5c, %%esp\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cb80_13\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw %%di, 0x326a0c\n\t"
      "je .LFUN_0013cb80_12\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e380]\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "jmp .LFUN_0013cb80_2\n\t"
      ".LFUN_0013cb80_1:\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".LFUN_0013cb80_2:\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl $0x240, %%eax\n\t"
      "je .LFUN_0013cb80_11\n\t"
      "pushl %%esi\n\t"
      "call *%[c13c100]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%di, 0xa(%%eax)\n\t"
      "je .LFUN_0013cb80_11\n\t"
      "cmpw %%di, 0xc(%%eax)\n\t"
      "je .LFUN_0013cb80_11\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13ca30]\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[c13cab0]\n\t"
      "movb 0x326a0c, %%cl\n\t"
      "movl $1, %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movzwl 0x46f078, %%eax\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%edx, %%eax\n\t"
      "jne .LFUN_0013cb80_7\n\t"
      "movl (%%edi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_0013cb80_7\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013cb80_3:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw (%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0013cb80_6\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109e90]\n\t"
      "leal 0x8(%%esi), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "addl $8, %%ebx\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e720]\n\t"
      "addl $0x34, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0013cb80_4\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e720]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0013cb80_4\n\t"
      "movb 0x326a0c, %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "notl %%edx\n\t"
      "andw %%dx, 0x20(%%esi)\n\t"
      "jmp .LFUN_0013cb80_5\n\t"
      ".LFUN_0013cb80_4:\n\t"
      "movb 0x326a0c, %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "orw %%ax, 0x20(%%esi)\n\t"
      ".LFUN_0013cb80_5:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_0013cb80_6:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0013cb80_3\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_0013cb80_7:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013cb80_11\n\t"
      "call *%[c145490]\n\t"
      "movl (%%edi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0013cb80_11\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0013cb80_8:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0013cb80_9\n\t"
      "pushl %%eax\n\t"
      "call *%[c140720]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0013cb80_10\n\t"
      ".LFUN_0013cb80_9:\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .LFUN_0013cb80_10\n\t"
      "movb 0x326a0c, %%cl\n\t"
      "movzwl 0x20(%%esi), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "je .LFUN_0013cb80_10\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c144770]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c144b50]\n\t"
      ".LFUN_0013cb80_10:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0013cb80_8\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_0013cb80_11:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "cmpw $0xc, %%si\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "jl .LFUN_0013cb80_1\n\t"
      "movb 0x326a0c, %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "orw %%dx, 0x46f078\n\t"
      ".LFUN_0013cb80_12:\n\t"
      "popl %%edi\n\t"
      ".LFUN_0013cb80_13:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c977f0] "m"(b13cb80_c977f0), [c18e380] "m"(b13cb80_c18e380), [c13c100] "m"(b13cb80_c13c100), [c13ca30] "m"(b13cb80_c13ca30), [c13cab0] "m"(b13cb80_c13cab0), [elem] "m"(b13cb80_elem), [tag] "m"(b13cb80_tag), [c109e90] "m"(b13cb80_c109e90), [xfrmpt] "m"(b13cb80_xfrmpt), [c18e720] "m"(b13cb80_c18e720), [c145490] "m"(b13cb80_c145490), [c140720] "m"(b13cb80_c140720), [c144770] "m"(b13cb80_c144770), [c144b50] "m"(b13cb80_c144b50)
      : "memory");
}
#else
#error "FUN_0013cb80: clang naked draft required"
#endif


/* FUN_0013cdd0 (0x13cdd0) — XBE naked draft (batch 63). */
#if defined(__clang__)
static bool (*const b13cdd0_c977f0)(void) = game_in_editor;
static void * (*const b13cdd0_c13c100)(int16_t object_type) = FUN_0013c100;
static int (*const b13cdd0_c13ca30)(int param_1, int param_2, int *param_3) = FUN_0013ca30;
static int (*const b13cdd0_c13cab0)(int param_1, int param_2) = FUN_0013cab0;
static void *(*const b13cdd0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b13cdd0_c144770)(void *placement_data, int palette_block) = object_new_from_scenario;
static void (*const b13cdd0_c144b50)(void) = objects_garbage_collect_tick;
static void (*const b13cdd0_c13cb80)(int param_1) = FUN_0013cb80;

__attribute__((naked, noinline))
void FUN_0013cdd0(int scenario __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cdd0_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LFUN_0013cdd0_1:\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl $0x240, %%eax\n\t"
      "jne .LFUN_0013cdd0_4\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c100]\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%cx, 0xa(%%eax)\n\t"
      "je .LFUN_0013cdd0_4\n\t"
      "cmpw %%cx, 0xc(%%eax)\n\t"
      "je .LFUN_0013cdd0_4\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13ca30]\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c13cab0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0013cdd0_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013cdd0_2:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c144770]\n\t"
      "addl $0x14, %%esp\n\t"
      "call *%[c144b50]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0013cdd0_2\n\t"
      ".LFUN_0013cdd0_3:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_0013cdd0_4:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "incl %%edi\n\t"
      "incl %%ecx\n\t"
      "cmpw $0xc, %%di\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_0013cdd0_1\n\t"
      "pushl $1\n\t"
      "call *%[c13cb80]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013cdd0_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c977f0] "m"(b13cdd0_c977f0), [c13c100] "m"(b13cdd0_c13c100), [c13ca30] "m"(b13cdd0_c13ca30), [c13cab0] "m"(b13cdd0_c13cab0), [elem] "m"(b13cdd0_elem), [c144770] "m"(b13cdd0_c144770), [c144b50] "m"(b13cdd0_c144b50), [c13cb80] "m"(b13cdd0_c13cb80)
      : "memory");
}
#else
#error "FUN_0013cdd0: clang naked draft required"
#endif


/* FUN_0013ce90 (0x13ce90) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void * (*const b13ce90_c13c100)(int16_t object_type) = FUN_0013c100;
static int (*const b13ce90_c13ca30)(int param_1, int param_2, int *param_3) = FUN_0013ca30;
static void *(*const b13ce90_elem)(void *, int, int) = tag_block_get_element;
static bool (*const b13ce90_c930a0)(void) = cinematic_in_progress;
static void (*const b13ce90_c13cb80)(int param_1) = FUN_0013cb80;

__attribute__((naked, noinline))
void FUN_0013ce90(int scenario __attribute__((unused)), char editor_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013ce90_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_0013ce90_1:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13c100]\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%cx, 0xa(%%eax)\n\t"
      "je .LFUN_0013ce90_4\n\t"
      "cmpw %%cx, 0xc(%%eax)\n\t"
      "je .LFUN_0013ce90_4\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13ca30]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0013ce90_4\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0013ce90_2:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0013ce90_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x24\n\t"
      "pushl %%eax\n\t"
      "addl $0x204, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%bx, 0x20(%%eax)\n\t"
      "movw %%si, 0x22(%%eax)\n\t"
      ".LFUN_0013ce90_3:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0013ce90_2\n\t"
      ".LFUN_0013ce90_4:\n\t"
      "incl %%ebx\n\t"
      "cmpw $0xc, %%bx\n\t"
      "jl .LFUN_0013ce90_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013ce90_5:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "call *%[c930a0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013ce90_6\n\t"
      "movl 0x44df00, %%eax\n\t"
      "movb 0xb(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0013ce90_7\n\t"
      ".LFUN_0013ce90_6:\n\t"
      "pushl $1\n\t"
      "call *%[c13cb80]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_0013ce90_7:\n\t"
      "ret\n\t"
      :
      : [c13c100] "m"(b13ce90_c13c100), [c13ca30] "m"(b13ce90_c13ca30), [elem] "m"(b13ce90_elem), [c930a0] "m"(b13ce90_c930a0), [c13cb80] "m"(b13ce90_c13cb80)
      : "memory");
}
#else
#error "FUN_0013ce90: clang naked draft required"
#endif


/* Wrap cluster_partition_iter_first for the non-collideable partition
 * (0x5a8d30). 0x13d570 / objects.obj
 */
void cluster_get_first_noncollideable_object(int *param_1, int param_2)
{
  cluster_partition_iter_first((void *)0x5a8d30, param_1, (int16_t)param_2);
}

/* Wrap cluster_partition_iter_next for the non-collideable partition
 * (0x5a8d30). 0x13d590 / objects.obj
 */
void cluster_get_next_noncollideable_object(int *param_1)
{
  cluster_partition_iter_next((void *)0x5a8d30, param_1);
}

/*
 * cluster_partition_object_iter_first (0x13d5b0) — begin iteration over
 * objects in a BSP cluster using the collideable partition (0x5a8d40).
 *
 * Wraps cluster_partition_iter_first with the collideable object partition
 * constant. Returns the first object handle in the cluster, or -1 if none.
 *
 * Confirmed: PUSH EAX (param_2=cluster_idx), PUSH ECX (param_1=state),
 *            PUSH 0x5a8d40, CALL 0x191a50. EAX passed through.
 * Confirmed: ADD ESP,0xc (3 cdecl args cleaned by caller).
 */
int cluster_partition_object_iter_first(int *state, int16_t cluster_idx)
{
  return cluster_partition_iter_first((void *)0x5a8d40, state, cluster_idx);
}

/*
 * cluster_partition_object_iter_next (0x13d5d0) — advance iteration over
 * objects in a BSP cluster using the collideable partition (0x5a8d40).
 *
 * Wraps cluster_partition_iter_next with the collideable object partition
 * constant. Returns the next object handle, or -1 when exhausted.
 *
 * Confirmed: PUSH EAX (param_1=state), PUSH 0x5a8d40, CALL 0x191660.
 * Confirmed: ADD ESP,0x8 (2 cdecl args cleaned by caller).
 */
int cluster_partition_object_iter_next(int *state)
{
  return cluster_partition_iter_next((void *)0x5a8d40, state);
}

/*
 * FUN_0013d5f0 (0x13d5f0 / objects.obj) — advance an object's per-object
 * cluster iterator to the next cluster. The iterator state (param_1) holds
 * the cluster partition pointer at +0x00 (must be the collideable
 * 0x5a8d40 or noncollideable 0x5a8d30 partition) and the current cluster
 * handle at +0x04. Asserts the partition pointer is valid, then forwards to
 * FUN_001916d0(partition, &cluster_handle), which returns the next cluster
 * index and advances the handle. Returns the cluster index (or -1 at end).
 *
 * Confirmed: cdecl, param_2 ([EBP+0xc]) is UNUSED in the body.
 * Confirmed: assert string at 0x29b890, file at 0x29b91c, line 0x419.
 * Confirmed: void-EAX return (returns FUN_001916d0's result).
 */
int16_t FUN_0013d5f0(void *param_1, int param_2)
{
  int *iter = (int *)param_1;
  (void)param_2;
  if ((void *)iter[0] != (void *)0x5a8d40 &&
      (void *)iter[0] != (void *)0x5a8d30) {
    display_assert(
        "iterator->cluster_partition==&collideable_object_cluster_partition || "
        "iterator->cluster_partition==&noncollideable_object_cluster_partition",
        "c:\\halo\\SOURCE\\objects\\objects.c", 0x419, 1);
    CALL_thunk_FUN_001029a0(-1);
  }
  return (int16_t)FUN_001916d0(iter[0], &iter[1]);
}

/*
 * object_try_and_get_and_verify_type — resolve a datum handle to its
 * object_data_t*, returning NULL if the handle is invalid or the object's
 * type is not among the bits in type_mask.
 *
 * Uses datum_absolute_index_to_index (0x119270, a "try-and-get" that returns
 * 0/NULL on failure) instead of datum_get (which asserts).
 * Reads the compact type byte at header+0x03, not the int16 at object+0x64.
 *
 * Confirmed: CALL 0x119270 with 2 args (ADD ESP,0x8).
 * Confirmed: byte ptr [EDX+0x3] — reads header->type as uint8_t.
 * Confirmed: MOV EAX, [EDX+0x8] — returns header->object.
 * Confirmed: XOR EAX,EAX before both exit paths — returns NULL on failure.
 */
void *object_try_and_get_and_verify_type(int datum_handle, int type_mask)
{
  object_header_data_t *header =
    (object_header_data_t *)(int)datum_absolute_index_to_index(
      *(data_t **)0x5a8d50, datum_handle);
  if (header != NULL && (type_mask & (1 << (header->type & 0x1f))) != 0)
    return header->object;
  return NULL;
}

/*
 * object_get_and_verify_type — resolve a datum handle to its object_data_t*
 * and assert that the object's type is one of the bits in type_mask.
 *
 * The "object" data table pointer lives at 0x5a8d50 (allocated by
 * objects_initialize as the "object" header data array; distinct from
 * the "objects" memory pool at 0x46f080 and object_header_data at 0x5abc10).
 *
 * datum_get(data, handle) returns object_header_data_t*; field at +8 is the
 * object_data_t* . Type enum is a signed int16 at object_data_t+0x64.
 *
 * Confirmed: MOVSX ECX, word ptr [ESI+0x64] — signed 16-bit read.
 * Confirmed: ADD ESP,0x8 after datum_get (2 cdecl args).
 * Confirmed: ADD ESP,0x10 after csprintf (4 args cleaned; 3 pre-pushed remain
 *            on stack for display_assert); ADD ESP,0x14 cleans the rest.
 */
void *object_get_and_verify_type(int datum_handle, int type_mask)
{
  /* datum_get: first arg = data table ptr (value at 0x5a8d50) */
  object_header_data_t *header =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, datum_handle);
  object_data_t *obj = header->object;
  int16_t type = obj->type;

  if ((type_mask & (1 << (type & 0x1f))) == 0) {
    /* csprintf with varargs: buffer, format, type_mask, (int)type.
     * The remaining 3 args (filename, lineno, halt) are pre-pushed before
     * csprintf in the original; in C we pass them explicitly to display_assert.
     * Confirmed: ADD ESP,0x10 cleans 4 csprintf args; display_assert receives
     * (reason, filepath, lineno, halt). */
    char *msg = csprintf((char *)0x5ab100,
                         "got an object type we didn't expect (expected one of "
                         "0x%08x but got #%d).",
                         type_mask, (int)type);
    display_assert(msg, "c:\\halo\\SOURCE\\objects\\objects.c", 0x69a, 1);
    system_exit(-1);
  }
  return obj;
}

/*
 * object_iterator_new (0x13d6f0) — initialise an object_iter_t for a walk.
 *
 * Calls data_verify on the object data table (sanity check), then writes
 * the caller-supplied type_mask and flags into the iterator block and
 * resets its scan state.
 *
 * Layout of object_iter_t (confirmed from disassembly):
 *   +0x00 int32_t  type_mask     — accepted object types (1<<type bit-mask)
 *   +0x04 uint8_t  flags         — required header flag byte (AND+CMP filter)
 *   +0x06 int16_t  current_index — next header-table slot to probe
 *   +0x08 int32_t  last_handle   — handle from last call (NONE = -1 on init)
 *   +0x0c uint32_t cookie        — 0x86868686 (marks as initialized)
 *
 * Confirmed: ADD ESP,0x4 after data_verify (1 arg).
 * Confirmed: byte ptr [EAX+0x4] = DL (flags, byte-sized arg).
 * Confirmed: word ptr [EAX+0x6] = 0x0000; dword ptr [EAX+0x8] = -1.
 * Confirmed: dword ptr [EAX+0xc] = 0x86868686 (cookie, written last).
 */
void object_iterator_new(void *iter, int type_mask, int flags)
{
  object_iter_t *it = (object_iter_t *)iter;
  data_verify(*(data_t **)0x5a8d50);
  it->cookie = 0x86868686;
  it->type_mask = type_mask;
  it->flags = (uint8_t)flags;
  it->current_index = 0;
  it->last_handle = NONE;
}

/*
 * object_iterator_next (0x13d730) — advance iterator, return next match.
 *
 * Walks the object header table starting at iter->current_index, scanning
 * for a non-empty slot (salt != 0) whose header flags satisfy the required
 * flag mask (entry_flags & iter->flags == iter->flags) and whose type bit
 * is set in iter->type_mask.  On a match:
 *   - Stores the composite handle (salt<<16 | index) in iter->last_handle.
 *   - Advances iter->current_index past the matched slot.
 *   - Returns the object_data_t* from entry->object (header+0x8).
 *
 * Returns NULL when the table is exhausted.
 *
 * The header table is an array of 0xc-byte object_header_data_t entries;
 * pointers start at data_t->data (offset +0x34 from the data_t header).
 * The live slot count is at data_t->current_count (offset +0x2e, int16_t).
 *
 * Confirmed: cookie guard == 0x86868686 (assert "uninitialized iterator").
 * Confirmed: MOVSX EAX, word ptr [EAX+0x2e] — current_count as signed 16-bit.
 * Confirmed: MOVSX from DX (current_index) into ECX for OR with shifted salt.
 * Confirmed: entry stride = 0xc (LEA ESI,[ESI+ECX*4] with ECX=index*3).
 * Confirmed: return entry->object at entry+0x8.
 */
void *object_iterator_next(void *iter)
{
  object_iter_t *it = (object_iter_t *)iter;
  data_t *data;
  object_header_data_t *entry;
  int16_t count;
  int16_t idx;

  if (it->cookie != 0x86868686) {
    display_assert("uninitialized iterator passed to object_iterator_next()",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x6b8, 1);
    system_exit(-1);
  }

  data_verify(*(data_t **)0x5a8d50);
  data = *(data_t **)0x5a8d50;

  idx = it->current_index;
  count = data->current_count;
  entry = (object_header_data_t *)((char *)data->data + (int)idx * 0xc);

  while (idx < count) {
    int handle = ((int)(uint16_t)entry->unk_0 << 16) | (int)(uint16_t)idx;
    idx++;
    if (entry->unk_0 != 0 && (entry->unk_2 & it->flags) == it->flags &&
        (it->type_mask & (1 << (entry->type & 0x1f))) != 0) {
      it->last_handle = handle;
      it->current_index = idx;
      return entry->object;
    }
    entry = (object_header_data_t *)((char *)entry + 0xc);
    if (idx >= count) {
      it->current_index = idx;
      return NULL;
    }
  }
  it->current_index = idx;
  return NULL;
}

/* FUN_0013d8b0 (0x13d8b0) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void (*const b13d8b0_c1193f0)(data_t *data) = data_verify;
static void * (*const b13d8b0_c13d730)(void *iter) = object_iterator_next;
static void (*const b13d8b0_c13c680)(int param_1, int param_2) = FUN_0013c680;

__attribute__((naked, noinline))
void FUN_0013d8b0(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1193f0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x86868686, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "movw $0, -0xa(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[c13d730]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013d8b0_3\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_0013d8b0_1:\n\t"
      "cmpl %%esi, 0xa0(%%eax)\n\t"
      "jne .LFUN_0013d8b0_2\n\t"
      "movl %%edi, 0xa0(%%eax)\n\t"
      ".LFUN_0013d8b0_2:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c13c680]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d730]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0013d8b0_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_0013d8b0_3:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1193f0] "m"(b13d8b0_c1193f0), [c13d730] "m"(b13d8b0_c13d730), [c13c680] "m"(b13d8b0_c13c680)
      : "memory");
}
#else
#error "FUN_0013d8b0: clang naked draft required"
#endif


/* FUN_0013ddd0 (0x13ddd0) — XBE naked draft (batch 65). */
#if defined(__clang__)
static void *(*const b13ddd0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b13ddd0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13ddd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13ddd0_exitfn)(int) = system_exit;
static void *(*const b13ddd0_tag)(int, int) = tag_get;
static void (*const b13ddd0_c1bde10)(void *tag_block) = predicted_resources_precache;
static void (*const b13ddd0_c13ddd0)(int object_handle) = FUN_0013ddd0;

__attribute__((naked, noinline))
void FUN_0013ddd0(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0013ddd0_4\n\t"
      ".LFUN_0013ddd0_1:\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "movswl 0x64(%%esi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_0013ddd0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013ddd0_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013ddd0_3\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "addl $0x170, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1bde10]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0013ddd0_3:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13ddd0]\n\t"
      "movl 0xc4(%%esi), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_0013ddd0_1\n\t"
      ".LFUN_0013ddd0_4:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13ddd0_dget), [c8d9d0] "m"(b13ddd0_c8d9d0), [assert] "m"(b13ddd0_assert), [exitfn] "m"(b13ddd0_exitfn), [tag] "m"(b13ddd0_tag), [c1bde10] "m"(b13ddd0_c1bde10), [c13ddd0] "m"(b13ddd0_c13ddd0)
      : "memory");
}
#else
#error "FUN_0013ddd0: clang naked draft required"
#endif


/*
 * object_set_garbage_flag — add or remove an object from the garbage
 * collection linked list.
 *
 * The garbage list is a singly-linked list threaded through
 * object_data_t+0xC0 (unk_192), with the head stored at
 * object_globals+0x08 (unk_8).
 *
 * When is_garbage is nonzero (add to garbage list):
 *   - Bails out if bit 0x10000 (garbage) or 0x20000 is already set.
 *   - Prepends the object to the garbage list head.
 *   - Sets bit 0x10000 in object flags.
 *
 * When is_garbage is zero (remove from garbage list):
 *   - Bails out if bit 0x10000 is NOT set.
 *   - Walks the list to find and unlink the object.
 *   - Clears bit 0x10000 in object flags.
 *   - Sets unk_192 to NONE (-1).
 *
 * Two debug validation loops walk the entire garbage list before and
 * after the mutation, asserting that every entry has a valid type and
 * the garbage bit set. These correspond to lines 0x7a0 and 0x7d6 in
 * the original objects.c.
 *
 * Confirmed: 2 cdecl args — PUSH [EBP+8], PUSH -1 before CALL 0x13d680.
 * Confirmed: MOV AL, byte ptr [EBP+0xC] — second arg is char-sized.
 * Confirmed: TEST EAX,0x30000 guards the add path; TEST EAX,0x10000
 *            guards the remove path.
 * Confirmed: garbage list next at object+0xC0, head at og+0x08.
 * Confirmed: assert strings at 0x29b9c4 and line numbers 0x7a0, 0x7d6.
 * Confirmed: object_get_and_verify_type(handle, -1) to resolve.
 */

/*
 * object_get_root_parent — walk the parent chain to the root object.
 *
 * Starting from object_handle, loops through parent_object_index (obj+0xCC)
 * until it reaches -1.  Each iteration validates the object type against the
 * full-type mask (0xFFFFFFFF).  Returns the topmost non-null handle, or -1
 * if the input was already -1.
 *
 * Confirmed: datum_get(DAT_005a8d50, handle) -> header at +0x08 -> type at
 *            +0x64 (int16_t).  Bit-shift check (1 << (type & 0x1f)) against
 *            0 — in practice always passes since mask is -1.
 * Confirmed: Loop terminates when obj->parent_object_index == -1.
 */
int object_get_root_parent(int object_handle)
{
  int current;
  int result;
  object_header_data_t *header;
  object_data_t *obj;
  int16_t type;

  result = -1;
  current = object_handle;
  while (current != -1) {
    header = (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, current);
    obj = header->object;
    type = obj->type;
    if ((1 << (type & 0x1f)) == 0) {
      display_assert(csprintf((char *)0x5ab100,
                              "got an object type we didn't expect (expected "
                              "one of 0x%08x but got #%d).",
                              -1, (int)type),
                     "c:\\halo\\SOURCE\\objects\\objects.c", 0x69a, 1);
      system_exit(-1);
    }
    result = current;
    current = obj->parent_object_index.value;
  }
  return result;
}

/*
 * object_header_block_allocate — grow an object's variable-length header data
 * region by `size` bytes and stamp a block_reference record at `offset`.
 *
 * Validates size>=0, data_size+size<=SHORT_MAX, offset>=0, and
 * offset+sizeof(block_reference)<=data_size, then resizes the object's pooled
 * data block (memory_pool_block_resize) to data_size+size. On success it bumps
 * data_size, writes the 4-byte block_reference {size, old_data_size} at
 * obj_base+offset, zero-fills the newly appended region, and returns 1.
 *
 * Confirmed: 3 cdecl args. params read as short via MOVSX (handle is int).
 * Confirmed: data_size at header+0x06 (uint16_t), object at header+0x08.
 * Confirmed: memory_pool_block_resize(*0x46f080, &header->object, new_size).
 * Confirmed: block_reference at obj_base+offset: [+0]=size, [+2]=old_data_size.
 * Confirmed: csmemset(header->object + old_data_size, 0, size).
 * Confirmed: asserts at objects.c lines 0x99b, 0x99c, 0x99e, 0x99f.
 */
int object_header_block_allocate(int object_handle, int offset, int size)
{
  object_header_data_t *header;
  short ssize;
  short soffset;
  short old_data_size;
  char *obj_base;
  short *block_ref;

  header =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  ssize = (short)size;
  if (ssize < 0) {
    display_assert("size>=0", "c:\\halo\\SOURCE\\objects\\objects.c", 0x99b, 1);
    system_exit(-1);
  }
  if (0x7fff < (int)(short)header->data_size + (int)ssize) {
    display_assert("object_header->data_size+size<=SHORT_MAX",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x99c, 1);
    system_exit(-1);
  }
  soffset = (short)offset;
  if (soffset < 0) {
    display_assert("block_reference_offset>=0",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x99e, 1);
    system_exit(-1);
  }
  if ((unsigned int)(int)(short)header->data_size < (unsigned int)((int)soffset + 4)) {
    display_assert(
      "block_reference_offset+sizeof(struct "
      "object_header_block_reference)<=object_header->data_size",
      "c:\\halo\\SOURCE\\objects\\objects.c", 0x99f, 1);
    system_exit(-1);
  }

  if (memory_pool_block_resize(*(void **)0x46f080, (void **)&header->object,
                               (int)(short)header->data_size + (int)ssize)) {
    old_data_size = (short)header->data_size;
    header->data_size = (uint16_t)(old_data_size + ssize);
    obj_base = (char *)object_get_and_verify_type(object_handle, -1);
    block_ref = (short *)(obj_base + soffset);
    block_ref[1] = old_data_size;
    block_ref[0] = ssize;
    csmemset((char *)header->object + (int)old_data_size, 0, (int)ssize);
    return 1;
  }
  return 0;
}

void FUN_0013d870(int unit_handle, void *data)
{
    (void)unit_handle;
    (void)data;
}

/* object_name_list_set_handle (0x13d880) — XBE naked draft (batch 100). */
#if defined(__clang__)
static scenario_t * (*const b13d880_c18e380)(void) = global_scenario_get;

__attribute__((naked, noinline))
void object_name_list_set_handle(int16_t param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lobject_name_list_set_handle_2\n\t"
      "pushl %%esi\n\t"
      "movswl %%ax, %%esi\n\t"
      "call *%[c18e380]\n\t"
      "cmpl 0x204(%%eax), %%esi\n\t"
      "jge .Lobject_name_list_set_handle_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x46f07c, %%ecx\n\t"
      "movl %%eax, (%%ecx,%%esi,4)\n\t"
      ".Lobject_name_list_set_handle_1:\n\t"
      "popl %%esi\n\t"
      ".Lobject_name_list_set_handle_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b13d880_c18e380)
      : "memory");
}
#else
#error "object_name_list_set_handle: clang naked draft required"
#endif


/* object_set_garbage_flag (0x13d920) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void *(*const b13d920_get)(int, int) = object_get_and_verify_type;
static void *(*const b13d920_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b13d920_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13d920_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13d920_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void object_set_garbage_flag(int object_handle __attribute__((unused)), int is_garbage __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_set_garbage_flag_4\n\t"
      ".Lobject_set_garbage_flag_1:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "movswl 0x64(%%esi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lobject_set_garbage_flag_2\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_set_garbage_flag_2:\n\t"
      "testl $0x10000, 0x4(%%esi)\n\t"
      "jne .Lobject_set_garbage_flag_3\n\t"
      "pushl $1\n\t"
      "pushl $0x7a0\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29b9c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_set_garbage_flag_3:\n\t"
      "movl 0xc0(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lobject_set_garbage_flag_1\n\t"
      "movl 0x46f084, %%ecx\n\t"
      ".Lobject_set_garbage_flag_4:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "je .Lobject_set_garbage_flag_5\n\t"
      "testl $0x30000, %%eax\n\t"
      "jne .Lobject_set_garbage_flag_10\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "movl %%eax, 0xc0(%%edi)\n\t"
      "movl %%ebx, 0x8(%%ecx)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "orl $0x10000, %%eax\n\t"
      "jmp .Lobject_set_garbage_flag_9\n\t"
      ".Lobject_set_garbage_flag_5:\n\t"
      "testl $0x10000, %%eax\n\t"
      "je .Lobject_set_garbage_flag_10\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "leal 0x8(%%ecx), %%eax\n\t"
      "je .Lobject_set_garbage_flag_8\n\t"
      "jmp .Lobject_set_garbage_flag_6\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lobject_set_garbage_flag_6:\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "movswl 0x64(%%esi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lobject_set_garbage_flag_7\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_set_garbage_flag_7:\n\t"
      "movl 0xc0(%%esi), %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "leal 0xc0(%%esi), %%eax\n\t"
      "jne .Lobject_set_garbage_flag_6\n\t"
      "movl 0x46f084, %%ecx\n\t"
      ".Lobject_set_garbage_flag_8:\n\t"
      "movl 0xc0(%%edi), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl $0xffffffff, 0xc0(%%edi)\n\t"
      "andl $0xfffeffff, %%eax\n\t"
      ".Lobject_set_garbage_flag_9:\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      ".Lobject_set_garbage_flag_10:\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_set_garbage_flag_14\n\t"
      "movl $0x10000, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobject_set_garbage_flag_11:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "movswl 0x64(%%esi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lobject_set_garbage_flag_12\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_set_garbage_flag_12:\n\t"
      "testl %%edi, 0x4(%%esi)\n\t"
      "jne .Lobject_set_garbage_flag_13\n\t"
      "pushl $1\n\t"
      "pushl $0x7d6\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29b9c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_set_garbage_flag_13:\n\t"
      "movl 0xc0(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lobject_set_garbage_flag_11\n\t"
      ".Lobject_set_garbage_flag_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13d920_get), [dget] "m"(b13d920_dget), [c8d9d0] "m"(b13d920_c8d9d0), [assert] "m"(b13d920_assert), [exitfn] "m"(b13d920_exitfn)
      : "memory");
}
#else
#error "object_set_garbage_flag: clang naked draft required"
#endif


/* FUN_0013db60 (0x13db60) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b13db60_memset)(void *, int, unsigned int) = csmemset;
static int (*const b13db60_c11e3c0)(void *pool) = memory_pool_get_contiguous_free_size;

__attribute__((naked, noinline))
void FUN_0013db60(short *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $8\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x5a8d50, %%edx\n\t"
      "movl 0x34(%%edx), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%cx, 0x2e(%%edx)\n\t"
      "jle .LFUN_0013db60_3\n\t"
      "movb $1, %%dl\n\t"
      "pushl %%edi\n\t"
      ".LFUN_0013db60_1:\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_0013db60_2\n\t"
      "incw (%%esi)\n\t"
      "testb %%dl, 0x2(%%eax)\n\t"
      "je .LFUN_0013db60_2\n\t"
      "incw 0x2(%%esi)\n\t"
      ".LFUN_0013db60_2:\n\t"
      "movl 0x5a8d50, %%edi\n\t"
      "incl %%ecx\n\t"
      "addl $0xc, %%eax\n\t"
      "cmpw 0x2e(%%edi), %%cx\n\t"
      "jl .LFUN_0013db60_1\n\t"
      "popl %%edi\n\t"
      ".LFUN_0013db60_3:\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11e3c0]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fmuls 0x29ba04\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b13db60_memset), [c11e3c0] "m"(b13db60_c11e3c0)
      : "memory");
}
#else
#error "FUN_0013db60: clang naked draft required"
#endif


void garbage_collect_now(void)
{
  *(unsigned char *)(*(int *)0x46f084 + 2) = 1;
}

void FUN_0013dbe0(int param_1)
{
  int iVar1;

  iVar1 = *(int *)0x46f084;
  if (param_1 == -1) {
    *(short *)(*(int *)0x46f084 + 0x90) = 0;
    return;
  }
  *(short *)(iVar1 + 0x90) = 1;
  *(int *)(iVar1 + 0x94) = param_1;
}

void FUN_0013dcb0(void)
{
  *(short *)(*(int *)0x46f084 + 0x90) = 0;
}

/* FUN_0013dc10 (0x13dc10) — XBE naked draft (batch 66). */
#if defined(__clang__)
static scenario_t * (*const b13dc10_c18e380)(void) = global_scenario_get;
static void *(*const b13dc10_elem)(void *, int, int) = tag_block_get_element;
static void (*const b13dc10_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void (*const b13dc10_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0013dc10(short camera_point_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0013dc10_1\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movw $0, 0x90(%%eax)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013dc10_1:\n\t"
      "pushl %%esi\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4f0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0x28(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c18f180]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $-1, -0x4(%%ebp)\n\t"
      "jne .LFUN_0013dc10_2\n\t"
      "addl $4, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x29ba08\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, 0x90(%%ecx)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013dc10_2:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movw $2, 0x90(%%eax)\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "movw %%dx, 0x94(%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b13dc10_c18e380), [elem] "m"(b13dc10_elem), [c18f180] "m"(b13dc10_c18f180), [c8f390] "m"(b13dc10_c8f390)
      : "memory");
}
#else
#error "FUN_0013dc10: clang naked draft required"
#endif


/* FUN_0013dcc0 (0x13dcc0) — XBE naked draft (batch 63). */
#if defined(__clang__)
static int (*const b13dcc0_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static int (*const b13dcc0_c13d7f0)(int object_handle) = object_get_root_parent;
static void *(*const b13dcc0_get)(int, int) = object_get_and_verify_type;
static void * (*const b13dcc0_c18e3c0)(void) = scenario_get;
static void (*const b13dcc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13dcc0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
short FUN_0013dcc0(void)
{
  __asm__ volatile(
      "movl 0x46f084, %%ecx\n\t"
      "movswl 0x90(%%ecx), %%eax\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0013dcc0_1\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_0013dcc0_5\n\t"
      "movw 0x94(%%ecx), %%ax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LFUN_0013dcc0_1:\n\t"
      "movl 0x94(%%ecx), %%ecx\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c119270]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013dcc0_4\n\t"
      "movb 0x3(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_0013dcc0_4\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0013dcc0_4\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movl 0x94(%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d7f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%ah\n\t"
      "je .LFUN_0013dcc0_6\n\t"
      "movw 0x4c(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0013dcc0_6\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0013dcc0_2\n\t"
      "call *%[c18e3c0]\n\t"
      "movswl 0x4c(%%esi), %%edx\n\t"
      "cmpl 0x134(%%eax), %%edx\n\t"
      "jl .LFUN_0013dcc0_3\n\t"
      ".LFUN_0013dcc0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x8e7\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29ba48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013dcc0_3:\n\t"
      "movw 0x4c(%%esi), %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LFUN_0013dcc0_4:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movw $0, 0x90(%%eax)\n\t"
      ".LFUN_0013dcc0_5:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LFUN_0013dcc0_6:\n\t"
      "popl %%esi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [c119270] "m"(b13dcc0_c119270), [c13d7f0] "m"(b13dcc0_c13d7f0), [get] "m"(b13dcc0_get), [c18e3c0] "m"(b13dcc0_c18e3c0), [assert] "m"(b13dcc0_assert), [exitfn] "m"(b13dcc0_exitfn)
      : "memory");
}
#else
#error "FUN_0013dcc0: clang naked draft required"
#endif


void object_definition_predict(int param_1)
{
  void *tag;

  if (param_1 != -1) {
    tag = tag_get(0x6f626a65, param_1);
    predicted_resources_precache((char *)tag + 0x170);
  }
}

void object_beautify(int param_1, char param_2)
{
  int iVar1;

  if (param_1 != -1) {
    if (param_2 != '\0') {
      iVar1 = (int)object_get_and_verify_type(param_1, 0xffffffff);
      *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x400000;
      return;
    }
    iVar1 = (int)object_get_and_verify_type(param_1, 0xffffffff);
    *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) & 0xffbfffff;
  }
}

/* object_header_new (0x13ded0) — XBE naked draft (batch 141). */
#if defined(__clang__)
static int (*const b13ded0_c119610)(data_t *data) = data_new_at_index;
static int (*const b13ded0_c119570)(data_t *data, int handle) = data_new_datum;
static void *(*const b13ded0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const b13ded0_c11e6c0)(void *pool, void **block_reference, int size) = memory_pool_block_new;
static void *(*const b13ded0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b13ded0_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
int object_header_new(data_t *data __attribute__((unused)), int16_t datum_size __attribute__((unused)), int type_hint __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "cmpl $-1, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lobject_header_new_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lobject_header_new_2\n\t"
      ".Lobject_header_new_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119570]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_header_new_2:\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobject_header_new_3\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movswl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0x8(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11e6c0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_header_new_4\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, 0x6(%%edi)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lobject_header_new_3:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_header_new_4:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119610] "m"(b13ded0_c119610), [c119570] "m"(b13ded0_c119570), [dget] "m"(b13ded0_dget), [c11e6c0] "m"(b13ded0_c11e6c0), [memset] "m"(b13ded0_memset), [c1196d0] "m"(b13ded0_c1196d0)
      : "memory");
}
#else
#error "object_header_new: clang naked draft required"
#endif


void object_postprocess_node_matrices(data_t *data, int object_handle /* @<ebx> */);

/*
 * object_header_block_reference_get — resolve an object's inline
 *
 * block-reference pair ({size, offset}) to a pointer into object data.
 *
 *
 * Confirmed: CALL 0x119320 (datum_get) first, then CALL 0x13d680
 *
 * (object_get_and_verify_type).
 * Confirmed: reference fields are signed
 * 16-bit reads at +0 (size)
 * and +2 (offset).
 * Confirmed: asserts
 * "reference->offset>0" at line 0x98b and
 *
 * "reference->offset+reference->size<=object_header->data_size"
 * at line
 * 0x98c, both followed by system_exit(-1).
 * Confirmed: return value is
 * object_ptr + reference->offset.
 */
void *object_header_block_reference_get(int object_handle, void *reference)
{
  object_header_data_t *header =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  char *object = (char *)object_get_and_verify_type(object_handle, -1);
  short *ref = (short *)reference;

  /* reference layout: [+0] = size, [+2] = offset (both signed 16-bit). The
   * fields are re-read inline (not cached) to match the original's codegen. */
  if (ref[1] <= 0) {
    display_assert("reference->offset>0",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x98b, 1);
    system_exit(-1);
  }

  if ((int)(short)header->data_size < (int)ref[0] + (int)ref[1]) {
    display_assert(
      "reference->offset+reference->size<=object_header->data_size",
      "c:\\halo\\SOURCE\\objects\\objects.c", 0x98c, 1);
    system_exit(-1);
  }

  return object + ref[1];
}

/*
 * FUN_0013e1a0 — run animation-block initializer callbacks for an object.
 *
 * Resolves the object's tag definition and checks whether both a model
 * (tag+0x34) and an animation graph (tag+0x44) are present. If so,
 * resolves the object's animation block reference at object_data+0x1a0
 * via object_header_block_reference_get, then dispatches through type
 * callbacks via FUN_0013c800.
 *
 * Confirmed: single register arg object_handle in EDI.
 * Confirmed: PUSH -1, PUSH EDI -> object_get_and_verify_type(handle, -1).
 * Confirmed: PUSH EAX, PUSH 0x6f626a65 -> tag_get('obje', obj[0]).
 * Confirmed: ADD ESP,0x10 cleans both calls (4 pushes).
 * Confirmed: CMP [EAX+0x34],-1 checks model tag index.
 * Confirmed: CMP [EAX+0x44],-1 checks animation graph tag index.
 * Confirmed: ADD ESI,0x1a0 -> object_data+0x1a0 is the animation block ref.
 * Confirmed: PUSH ESI, PUSH EDI -> object_header_block_reference_get(handle,
 * obj+0x1a0). Confirmed: PUSH EAX (return value), PUSH EDI ->
 * FUN_0013c800(handle, block). Confirmed: ADD ESP,0x10 cleans both calls (4
 * pushes).
 */
/* 0x13e1a0 */
void FUN_0013e1a0(int object_handle /* @<edi> */)
{
  char *obj;
  char *tag_data;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  tag_data = (char *)tag_get(0x6f626a65, *(int *)obj);

  if (*(int *)(tag_data + 0x34) != -1 && *(int *)(tag_data + 0x44) != -1) {
    void *block = object_header_block_reference_get(object_handle, obj + 0x1a0);
    FUN_0013c800(object_handle, block);
  }
}

/* object_find_region_permutations_available_with_variant (0x13e3f0) — XBE naked draft (batch 152). */
#if defined(__clang__)
static void *(*const b13e3f0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int16_t object_find_region_permutations_available_with_variant(void *region_element __attribute__((unused)), int16_t variant __attribute__((unused)), int16_t *output __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "addl $0x40, %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lobject_find_region_permutations_available_with_variant_4\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lobject_find_region_permutations_available_with_variant_1:\n\t"
      "pushl $0x58\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movb 0x20(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "jne .Lobject_find_region_permutations_available_with_variant_3\n\t"
      "movw 0x24(%%eax), %%ax\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "je .Lobject_find_region_permutations_available_with_variant_2\n\t"
      "cmpw $-1, %%cx\n\t"
      "jne .Lobject_find_region_permutations_available_with_variant_3\n\t"
      "cmpw $0x64, %%ax\n\t"
      "jge .Lobject_find_region_permutations_available_with_variant_3\n\t"
      ".Lobject_find_region_permutations_available_with_variant_2:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movw %%di, (%%ecx,%%eax,2)\n\t"
      "incl %%ebx\n\t"
      ".Lobject_find_region_permutations_available_with_variant_3:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lobject_find_region_permutations_available_with_variant_1\n\t"
      ".Lobject_find_region_permutations_available_with_variant_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b13e3f0_elem)
      : "memory");
}
#else
#error "object_find_region_permutations_available_with_variant: clang naked draft required"
#endif


/* object_determine_variant_number (0x13e460) — XBE naked draft (batch 138). */
#if defined(__clang__)
static void *(*const b13e460_get)(int, int) = object_get_and_verify_type;
static void *(*const b13e460_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int16_t object_determine_variant_number(int object_handle __attribute__((unused)), void *model_tag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0xc4(%%edi), %%ecx\n\t"
      "addl $0xc4, %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .Lobject_determine_variant_number_5\n\t"
      "pushl %%esi\n\t"
      "jmp .Lobject_determine_variant_number_2\n\t"
      ".Lobject_determine_variant_number_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".Lobject_determine_variant_number_2:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lobject_determine_variant_number_4\n\t"
      "movswl %%bx, %%esi\n\t"
      "pushl $0x4c\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movzbl 0x130(%%esi,%%ecx,1), %%ecx\n\t"
      "movl 0x40(%%eax), %%edx\n\t"
      "addl $0x40, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Lobject_determine_variant_number_3\n\t"
      "pushl $0x58\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x24(%%eax), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      ".Lobject_determine_variant_number_3:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lobject_determine_variant_number_1\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      ".Lobject_determine_variant_number_4:\n\t"
      "popl %%esi\n\t"
      ".Lobject_determine_variant_number_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13e460_get), [elem] "m"(b13e460_elem)
      : "memory");
}
#else
#error "object_determine_variant_number: clang naked draft required"
#endif


/* object_child_list_remove (0x13e510) — XBE naked draft (batch 144). */
#if defined(__clang__)
static void *(*const b13e510_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b13e510_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13e510_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13e510_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void object_child_list_remove(void *list_head __attribute__((unused)), int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "je .Lobject_child_list_remove_4\n\t"
      "pushl %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lobject_child_list_remove_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "movswl 0x64(%%edi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lobject_child_list_remove_2\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_child_list_remove_2:\n\t"
      "cmpl %%ebx, (%%esi)\n\t"
      "je .Lobject_child_list_remove_3\n\t"
      "movl 0xc4(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal 0xc4(%%edi), %%esi\n\t"
      "jne .Lobject_child_list_remove_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc6b\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bbe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lobject_child_list_remove_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".Lobject_child_list_remove_3:\n\t"
      "movl 0xc4(%%edi), %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl $0xffffffff, 0xc4(%%edi)\n\t"
      "popl %%edi\n\t"
      ".Lobject_child_list_remove_4:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13e510_dget), [c8d9d0] "m"(b13e510_c8d9d0), [assert] "m"(b13e510_assert), [exitfn] "m"(b13e510_exitfn)
      : "memory");
}
#else
#error "object_child_list_remove: clang naked draft required"
#endif


void object_scripting_set_collideable(int param_1, char param_2)
{
  int iVar1;

  if (param_1 != -1) {
    iVar1 = (int)object_get_and_verify_type(param_1, 0xffffffff);
    if (param_2 == '\0') {
      *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x1000000;
      return;
    }
    *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) & 0xfeffffff;
  }
}

/*
 * object_reset_markers — begin a marker sweep pass.
 *
 * Asserts that no marker pass is in progress, increments the global marker
 * generation counter (0x5a8d28), and sets
 * object_globals->object_marker_initialized to true.
 *
 * Confirmed: void, no params (no stack args referenced).
 * Confirmed: TEST byte ptr [EAX+1] — checks object_marker_initialized.
 * Confirmed: INC dword ptr [0x5a8d28] — increments generation counter.
 * Confirmed: MOV byte ptr [EAX+1], 1 — sets marker_initialized = true.
 */
void object_reset_markers(void)
{
  if (object_globals->object_marker_initialized) {
    display_assert("!object_globals->object_marker_initialized",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0xdaf, 1);
    system_exit(-1);
  }
  *(uint32_t *)0x5a8d28 += 1;
  object_globals->object_marker_initialized = 1;
}

/*
 * object_marker_end (0x13ebc0) — end a marker sweep pass.
 *
 * Asserts that a marker pass is currently in progress
 * (object_marker_initialized must be true), then clears the flag to signal the
 * sweep is complete. Paired with object_reset_markers which begins the sweep.
 *
 * Confirmed: no prologue, no stack frame, no arguments.
 * Confirmed: MOV EAX,[0x46f084] -> object_globals.
 * Confirmed: MOV CL,[EAX+0x1] -> object_globals->object_marker_initialized.
 * Confirmed: TEST CL,CL; JNZ -> skips assert if initialized (true).
 * Confirmed: assert string "object_globals->object_marker_initialized" at line
 * 0xdba. Confirmed: CALL 0x8d9f0 (display_assert), CALL 0x8e2f0
 * (system_exit(-1)). Confirmed: ADD ESP,0x14 cleans 5 args (display_assert 4 +
 * system_exit 1). Confirmed: MOV byte ptr [EAX+0x1],0x0 -> clears
 * object_marker_initialized.
 */
void object_marker_end(void)
{
  if (!object_globals->object_marker_initialized) {
    display_assert("object_globals->object_marker_initialized",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0xdba, 1);
    system_exit(-1);
  }
  object_globals->object_marker_initialized = 0;
}

/* object_markers_need_update (0x13ec00) — XBE naked draft (batch 96). */
#if defined(__clang__)
static void *(*const b13ec00_get)(int, int) = object_get_and_verify_type;
static void (*const b13ec00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13ec00_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int object_markers_need_update(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x1(%%ecx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_markers_need_update_1\n\t"
      "pushl $1\n\t"
      "pushl $0xdc6\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_markers_need_update_1:\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "cmpl 0x5a8d28, %%edx\n\t"
      "setne %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13ec00_get), [assert] "m"(b13ec00_assert), [exitfn] "m"(b13ec00_exitfn)
      : "memory");
}
#else
#error "object_markers_need_update: clang naked draft required"
#endif


/*
 * object_mark (0x13ec50) — mark an object with the current generation.
 *
 * Looks up the object (any type), asserts a marker sweep is in progress,
 * then compares the object's marker_generation (obj+0x08) against the
 * global generation counter at 0x5a8d28. If they differ, stamps the object
 * with the current generation and returns 1 (newly marked). If equal,
 * returns 0 (already marked this sweep).
 *
 * Confirmed: PUSH -1, PUSH EAX -> object_get_and_verify_type(handle, -1).
 * Confirmed: MOV ECX,[0x46f084]; MOV AL,[ECX+0x1] -> object_marker_initialized.
 * Confirmed: ADD ESP,0x8 cleans 2 args for object_get_and_verify_type.
 * Confirmed: assert "object_globals->object_marker_initialized" at line 0xdd7.
 * Confirmed: MOV EAX,[0x5a8d28] -> global marker generation counter.
 * Confirmed: CMP [ESI+0x8],EAX -> obj->marker_generation at offset 0x08.
 * Confirmed: MOV AL,0x1 / XOR AL,AL for return 1/0 (byte-sized).
 */
int object_mark(int object_handle)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);

  if (!object_globals->object_marker_initialized) {
    display_assert("object_globals->object_marker_initialized",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0xdd7, 1);
    system_exit(-1);
  }

  if (obj->marker_generation != *(uint32_t *)0x5a8d28) {
    obj->marker_generation = *(uint32_t *)0x5a8d28;
    return 1;
  }
  return 0;
}

/* attachments_new (0x13ecb0) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void *(*const b13ecb0_get)(int, int) = object_get_and_verify_type;
static void *(*const b13ecb0_tag)(int, int) = tag_get;
static void *(*const b13ecb0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b13ecb0_c13b1b0)(int tag_index, int object_handle, short attachment_index, short marker_index, short secondary_marker_index) = FUN_0013b1b0;
static int (*const b13ecb0_c1c7230)(int object_index, int sound_tag_index, void *marker_name, short scale_index) = game_looping_sound_new;
static int (*const b13ecb0_c9eb40)(int param_1, int param_2, short param_3, short param_4, short param_5) = FUN_0009eb40;
static int (*const b13ecb0_c98580)(int definition_index, int object_index, short attachment_index) = contrail_new;
static int (*const b13ecb0_ca12e0)(int particle_tag_index, int object_handle, int16_t attach_index) = FUN_000a12e0;

__attribute__((naked, noinline))
void attachments_new(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x140(%%eax), %%ecx\n\t"
      "addl $0x140, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .Lattachments_new_15\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "jmp .Lattachments_new_2\n\t"
      ".Lattachments_new_1:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".Lattachments_new_2:\n\t"
      "pushl $0x48\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0xc(%%ecx), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lattachments_new_7\n\t"
      "movl (%%ecx), %%edx\n\t"
      "cmpl $0x6c696768, %%edx\n\t"
      "ja .Lattachments_new_5\n\t"
      "je .Lattachments_new_4\n\t"
      "cmpl $0x636f6e74, %%edx\n\t"
      "je .Lattachments_new_3\n\t"
      "cmpl $0x65666665, %%edx\n\t"
      "jne .Lattachments_new_7\n\t"
      "movl $2, %%ebx\n\t"
      "jmp .Lattachments_new_7\n\t"
      ".Lattachments_new_3:\n\t"
      "movl $3, %%ebx\n\t"
      "jmp .Lattachments_new_7\n\t"
      ".Lattachments_new_4:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .Lattachments_new_7\n\t"
      ".Lattachments_new_5:\n\t"
      "cmpl $0x6c736e64, %%edx\n\t"
      "je .Lattachments_new_6\n\t"
      "cmpl $0x7063746c, %%edx\n\t"
      "jne .Lattachments_new_7\n\t"
      "movl $4, %%ebx\n\t"
      "jmp .Lattachments_new_7\n\t"
      ".Lattachments_new_6:\n\t"
      "movl $1, %%ebx\n\t"
      ".Lattachments_new_7:\n\t"
      "movswl %%bx, %%edx\n\t"
      "cmpl $4, %%edx\n\t"
      "ja .Lattachments_new_14\n\t"
      "jmp *.Lattachments_new_jt(,%%edx,4)\n\t"
      ".Lattachments_new_8:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x34(%%ecx), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x30(%%ecx), %%ax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "decw %%dx\n\t"
      "decw %%ax\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c13b1b0]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lattachments_new_14\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "orl $0x100, 0x4(%%ecx)\n\t"
      "jmp .Lattachments_new_14\n\t"
      ".Lattachments_new_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x30(%%ecx), %%ax\n\t"
      "decw %%ax\n\t"
      "addl $0x10, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c7230]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lattachments_new_14\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "orl $0x400, 0x4(%%ecx)\n\t"
      "jmp .Lattachments_new_14\n\t"
      ".Lattachments_new_10:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x34(%%ecx), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x32(%%ecx), %%ax\n\t"
      "movswl 0x30(%%ecx), %%ecx\n\t"
      "decw %%dx\n\t"
      "decw %%ax\n\t"
      "decw %%cx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c9eb40]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lattachments_new_14\n\t"
      ".Lattachments_new_11:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c98580]\n\t"
      "jmp .Lattachments_new_13\n\t"
      ".Lattachments_new_12:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[ca12e0]\n\t"
      ".Lattachments_new_13:\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lattachments_new_14:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb %%bl, 0xf4(%%edi,%%ecx,1)\n\t"
      "movl %%eax, 0xfc(%%ecx,%%edi,4)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "cmpl (%%ecx), %%edi\n\t"
      "jl .Lattachments_new_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lattachments_new_15:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lattachments_new_jt:\n\t"
      ".long .Lattachments_new_8\n\t"
      ".long .Lattachments_new_9\n\t"
      ".long .Lattachments_new_10\n\t"
      ".long .Lattachments_new_11\n\t"
      ".long .Lattachments_new_12\n\t"
      ".text\n\t"
      :
      : [get] "m"(b13ecb0_get), [tag] "m"(b13ecb0_tag), [elem] "m"(b13ecb0_elem), [c13b1b0] "m"(b13ecb0_c13b1b0), [c1c7230] "m"(b13ecb0_c1c7230), [c9eb40] "m"(b13ecb0_c9eb40), [c98580] "m"(b13ecb0_c98580), [ca12e0] "m"(b13ecb0_ca12e0)
      : "memory");
}
#else
#error "attachments_new: clang naked draft required"
#endif


/* Propagate wake/limbo flags to children (object_handle@eax). */
#if defined(__clang__)
static void *(*const opfc_get)(int, int) = object_get_and_verify_type;
static void *(*const opfc_tag)(int, int) = tag_get;
static void (*const opfc_wake)(int) = object_wake;
static void (*const opfc_limbo)(int) = object_move_to_limbo;

__attribute__((naked, noinline))
void object_propagate_flag_to_children(int object_handle __attribute__((unused)),
                                       char do_wake __attribute__((unused)),
                                       char do_limbo __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 4(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%ah\n\t"
      "je 4f\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x140(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -4(%%ebp)\n\t"
      "jle 3f\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      "1:\n\t"
      "movb 0xf4(%%esi,%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne 2f\n\t"
      "movl 0xfc(%%edi,%%esi,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je 2f\n\t"
      "movb 8(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je 5f\n\t"
      "pushl %%eax\n\t"
      "call *%[wake]\n\t"
      "addl $4, %%esp\n\t"
      "5:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je 2f\n\t"
      "movl 0xfc(%%edi,%%esi,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[limbo]\n\t"
      "addl $4, %%esp\n\t"
      "2:\n\t"
      "movl -4(%%ebp), %%eax\n\t"
      "movl 0x140(%%eax), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%esi\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jl 1b\n\t"
      "popl %%esi\n\t"
      "3:\n\t"
      "popl %%ebx\n\t"
      "4:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(opfc_get), [tag] "m"(opfc_tag), [wake] "m"(opfc_wake),
        [limbo] "m"(opfc_limbo)
      : "memory");
}
#else
void object_propagate_flag_to_children(int object_handle /* @<eax> */,
                                       char do_wake, char do_limbo)
{
  char *obj;
  char *tag_data;
  int16_t i;
  int count;
  int child;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if ((*(int *)(obj + 4) & 0x100) == 0)
    return;

  tag_data = (char *)tag_get(0x6f626a65, *(int *)obj); /* 'obje' */
  count = *(int *)(tag_data + 0x140);
  i = 0;
  while ((int)i < count) {
    if (obj[0xf4 + (int)i] == 0) {
      child = *(int *)(obj + 0xfc + (int)i * 4);
      if (child != -1) {
        if (do_wake != 0)
          object_wake(child);
        if (do_limbo != 0)
          object_move_to_limbo(child);
      }
    }
    i++;
  }
}
#endif

/* Remove an object from the scenario object-name lookup table.
 * Clears the name_index field (obj+0x6a) and removes all references
 * to object_handle from the name table at 0x46f07c.
 * object_handle in EDI (register arg). */
void object_remove_from_name_list(int object_handle /* @<edi> */)
{
  char *obj;
  void *scenario;
  int count;
  int *name_table;
  int16_t i;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if (*(int16_t *)(obj + 0x6a) == -1)
    return;

  scenario = global_scenario_get();
  *(int16_t *)(obj + 0x6a) = -1;
  count = *(int *)((char *)scenario + 0x204);
  name_table = *(int **)0x46f07c;
  i = 0;
  while ((int)i < count) {
    if (name_table[(int)i] == object_handle)
      name_table[(int)i] = -1;
    i++;
  }
}

/* 0x13ef70 / objects.obj — Add an object to the scenario name table.
 * Validates name_index is in [0, 0x1FF], checks the name slot is free,
 * and writes the object_handle into the name table. Sets the object's
 * name field at obj+0x6a.
 * object_handle in EDI, name_index in SI (register args).
 * Confirmed: PUSH -1; PUSH EDI; CALL object_get_and_verify_type.
 * Confirmed: CMP SI,0x200 for range check.
 * Confirmed: name_table at DAT_0046f07c[name_index].
 * Confirmed: on collision, calls error(2, "an object with the name '%s' already exists!", name). */
void object_name_list_new(int object_handle /* @<edi> */,
                          int16_t name_index /* @<si> */)
{
  char *obj;
  int idx;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if (name_index < 0 || name_index >= 0x200) {
    display_assert(
        "name_index>=0 && name_index<MAXIMUM_OBJECT_NAMES_PER_SCENARIO",
        "c:\\halo\\SOURCE\\objects\\objects.c", 0x1003, 1);
    system_exit(-1);
  }
  idx = (int)name_index;
  if (*(int *)(*(int *)0x46f07c + idx * 4) == -1) {
    *(int *)(*(int *)0x46f07c + idx * 4) = object_handle;
    *(int16_t *)(obj + 0x6a) = name_index;
    return;
  }
  {
    void *scenario_data = (void *)((char *)global_scenario_get() + 0x204);
    char *name = (char *)tag_block_get_element(scenario_data, idx, 0x24);
    error(2, "an object with the name \'%s\' already exists!", name);
  }
}

/*
 * objects_place — place all scenario objects for the current map.
 *
 *
 * Sets the object_is_being_placed flag on object_globals, calls the scenario
 * object placer (FUN_0013cdd0, unported), then clears the flag. The flag is at
 * byte offset 0x00 of the object_globals struct.
 *
 * Confirmed: MOV byte ptr [EAX], 0x1 / MOV byte ptr [ECX], 0x0
 * Confirmed: global_scenario_get() result (EAX) pushed as sole arg to placer.
 * Confirmed: ADD ESP,0x4 after the placer call (1 cdecl arg).
 */
void objects_place(void)
{
  scenario_t *scenario;

  /* Set object_is_being_placed = true */
  object_globals->object_is_being_placed = 1;

  /* Get the scenario pointer and pass it to the object placer */
  scenario = global_scenario_get();
  FUN_0013cdd0((int)scenario);

  /* Clear object_is_being_placed */
  object_globals->object_is_being_placed = 0;
}

/* FUN_0013f080 (0x13f080) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const b13f080_get)(int, int) = object_get_and_verify_type;
static int (*const b13f080_c13f080)(int param_1, char (*param_2)(int, int), int param_3, int param_4, int param_5, int *param_6) = FUN_0013f080;

__attribute__((naked, noinline))
int FUN_0013f080(int param_1 __attribute__((unused)), char (*param_2)(int __attribute__((unused)), int), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)), int *param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jge .LFUN_0013f080_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "je .LFUN_0013f080_1\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%%edi\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013f080_2\n\t"
      ".LFUN_0013f080_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, (%%ebx,%%esi,4)\n\t"
      "incl %%esi\n\t"
      ".LFUN_0013f080_2:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc8(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013f080_3\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13f080]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_0013f080_3:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0xc4(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013f080_4\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13f080]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013f080_4:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13f080_get), [c13f080] "m"(b13f080_c13f080)
      : "memory");
}
#else
#error "FUN_0013f080: clang naked draft required"
#endif


/* find_objects_from_point_vector (0x13f120) — XBE naked draft (batch 60). */
#if defined(__clang__)
static int (*const b13f120_c18e720)(int point) = FUN_0018e720;
static void * (*const b13f120_c18e3c0)(void) = scenario_get;
static void *(*const b13f120_elem)(void *, int, int) = tag_block_get_element;
static void (*const b13f120_c13eb70)(void) = object_reset_markers;
static uint32_t * (*const b13f120_c193550)(void *bsp, int16_t cluster_index) = structure_bsp_get_cluster_sound_data;
static int (*const b13f120_c191a50)(void *partition, int *state, int16_t cluster_idx) = cluster_partition_iter_first;
static void *(*const b13f120_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b13f120_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13f120_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13f120_exitfn)(int) = system_exit;
static int (*const b13f120_c13f080)(int param_1, char (*param_2)(int, int), int param_3, int param_4, int param_5, int *param_6) = FUN_0013f080;
static int (*const b13f120_c191660)(void *partition, int *state) = cluster_partition_iter_next;

__attribute__((naked, noinline))
int find_objects_from_point_vector(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)), int param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[c18e720]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lfind_objects_from_point_vector_14\n\t"
      "pushl $0x10\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e720]\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x8(%%eax), %%si\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lfind_objects_from_point_vector_14\n\t"
      "call *%[c13eb70]\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e3c0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c193550]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "call *%[c18e3c0]\n\t"
      "movl 0x134(%%eax), %%eax\n\t"
      "addl $0x1f, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .Lfind_objects_from_point_vector_12\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      ".Lfind_objects_from_point_vector_1:\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .Lfind_objects_from_point_vector_11\n\t"
      "movl %%ecx, %%esi\n\t"
      "shll $5, %%esi\n\t"
      "movswl %%si, %%ebx\n\t"
      "leal 0x20(%%ebx), %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "cmpl 0x134(%%eax), %%edi\n\t"
      "jle .Lfind_objects_from_point_vector_2\n\t"
      "call *%[c18e3c0]\n\t"
      "movw 0x134(%%eax), %%ax\n\t"
      "movw %%ax, -0x4(%%ebp)\n\t"
      "jmp .Lfind_objects_from_point_vector_3\n\t"
      ".Lfind_objects_from_point_vector_2:\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      ".Lfind_objects_from_point_vector_3:\n\t"
      "cmpw -0x4(%%ebp), %%si\n\t"
      "movl %%esi, %%edi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jge .Lfind_objects_from_point_vector_10\n\t"
      "jmp .Lfind_objects_from_point_vector_4\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lfind_objects_from_point_vector_4:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "je .Lfind_objects_from_point_vector_9\n\t"
      "pushl %%edi\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5a8d40\n\t"
      "call *%[c191a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lfind_objects_from_point_vector_9\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lfind_objects_from_point_vector_5:\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "movswl 0x64(%%edi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lfind_objects_from_point_vector_6\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_objects_from_point_vector_6:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lfind_objects_from_point_vector_7\n\t"
      "pushl $1\n\t"
      "pushl $0xdd7\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_objects_from_point_vector_7:\n\t"
      "movl 0x5a8d28, %%eax\n\t"
      "cmpl %%eax, 0x8(%%edi)\n\t"
      "je .Lfind_objects_from_point_vector_8\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c13f080]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lfind_objects_from_point_vector_8:\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5a8d40\n\t"
      "call *%[c191660]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .Lfind_objects_from_point_vector_5\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      ".Lfind_objects_from_point_vector_9:\n\t"
      "incl %%edi\n\t"
      "incl %%ebx\n\t"
      "cmpw -0x4(%%ebp), %%di\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jl .Lfind_objects_from_point_vector_4\n\t"
      ".Lfind_objects_from_point_vector_10:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      ".Lfind_objects_from_point_vector_11:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%esi\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "jl .Lfind_objects_from_point_vector_1\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lfind_objects_from_point_vector_12:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movb 0x1(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lfind_objects_from_point_vector_13\n\t"
      "pushl $1\n\t"
      "pushl $0xdba\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_objects_from_point_vector_13:\n\t"
      "movl 0x46f084, %%edx\n\t"
      "movb $0, 0x1(%%edx)\n\t"
      ".Lfind_objects_from_point_vector_14:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e720] "m"(b13f120_c18e720), [c18e3c0] "m"(b13f120_c18e3c0), [elem] "m"(b13f120_elem), [c13eb70] "m"(b13f120_c13eb70), [c193550] "m"(b13f120_c193550), [c191a50] "m"(b13f120_c191a50), [dget] "m"(b13f120_dget), [c8d9d0] "m"(b13f120_c8d9d0), [assert] "m"(b13f120_assert), [exitfn] "m"(b13f120_exitfn), [c13f080] "m"(b13f120_c13f080), [c191660] "m"(b13f120_c191660)
      : "memory");
}
#else
#error "find_objects_from_point_vector: clang naked draft required"
#endif


int sort_dumps(int param_1, int param_2)
{
  if (*(int *)(param_1 + 8) < *(int *)(param_2 + 8)) {
    return 1;
  }
  return (*(int *)(param_1 + 8) <= *(int *)(param_2 + 8)) - 1;
}

/* object_add_to_dump (0x13f3b0) — XBE naked draft (batch 151). */
#if defined(__clang__)
static void *(*const b13f3b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13f3b0_get)(int, int) = object_get_and_verify_type;
static int (*const b13f3b0_c13d7f0)(int object_handle) = object_get_root_parent;

__attribute__((naked, noinline))
void object_add_to_dump(int object_handle __attribute__((unused)), void *stats __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw 0x6(%%esi), %%cx\n\t"
      "jle .Lobject_add_to_dump_1\n\t"
      "movw %%cx, 0x6(%%esi)\n\t"
      ".Lobject_add_to_dump_1:\n\t"
      "movswl 0x6(%%edi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "incw 0xc(%%esi)\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "testb $1, 0x2(%%edi)\n\t"
      "popl %%edi\n\t"
      "je .Lobject_add_to_dump_2\n\t"
      "incw 0xe(%%esi)\n\t"
      ".Lobject_add_to_dump_2:\n\t"
      "testl $0x10000, 0x4(%%eax)\n\t"
      "je .Lobject_add_to_dump_3\n\t"
      "incw 0x10(%%esi)\n\t"
      ".Lobject_add_to_dump_3:\n\t"
      "testb $4, 0xb6(%%eax)\n\t"
      "je .Lobject_add_to_dump_4\n\t"
      "incw 0x12(%%esi)\n\t"
      ".Lobject_add_to_dump_4:\n\t"
      "testb $0x20, 0x4(%%eax)\n\t"
      "je .Lobject_add_to_dump_5\n\t"
      "incw 0x16(%%esi)\n\t"
      ".Lobject_add_to_dump_5:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13d7f0]\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl $0x200000, %%ecx\n\t"
      "jne .Lobject_add_to_dump_6\n\t"
      "cmpw $-1, 0x4c(%%eax)\n\t"
      "jne .Lobject_add_to_dump_7\n\t"
      ".Lobject_add_to_dump_6:\n\t"
      "incw 0x14(%%esi)\n\t"
      ".Lobject_add_to_dump_7:\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13f3b0_dget), [get] "m"(b13f3b0_get), [c13d7f0] "m"(b13f3b0_c13d7f0)
      : "memory");
}
#else
#error "object_add_to_dump: clang naked draft required"
#endif


/* 0x13f440 / objects.obj — Write one dump stats record to a file.
 * Formats the stats structure into a single line with counts/sizes.
 * stats pointer in ESI (register arg), file pointer as stack param.
 * Confirmed: fprintf format string at 0x29bcf4.
 * Confirmed: reads stats fields for count, active, orphaned, total_size etc. */
void object_dump_write(void *stats /* @<esi> */, void *file)
{
  char *pcVar1;
  int *st = (int *)stats;

  pcVar1 = "unknown";
  if (st[0] == -1) {
    if ((int16_t)st[1] != -1) {
      pcVar1 = (char *)FUN_0013c250((int16_t)st[1]);
    }
  } else {
    pcVar1 = (char *)tag_get_name(st[0]);
  }
  crt_fprintf(
      file,
      "% 6d (% 6d) [% 7d/% 7d/% 7d/% 7d] % 7d % 7d %s\r\n",
      (int)*(int16_t *)((char *)st + 0xc),
      (int)*(int16_t *)((char *)st + 0xe),
      (int)*(int16_t *)((char *)st + 0x10),
      (int)*(int16_t *)((char *)st + 0x12),
      (int)*(int16_t *)((char *)st + 0x14),
      (int)*(int16_t *)((char *)st + 0x16),
      (int)*(int16_t *)((char *)st + 0x6),
      st[2],
      pcVar1);
}

/* object_select_random_region_permutations_by_variant (0x140a00) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void *(*const b140a00_get)(int, int) = object_get_and_verify_type;
static void *(*const b140a00_elem)(void *, int, int) = tag_block_get_element;
static int16_t (*const b140a00_c13e3f0)(void *region_element, int16_t variant, int16_t *output) = object_find_region_permutations_available_with_variant;
static int *(*const b140a00_gseed)(void) = get_global_random_seed_address;
static int16_t (*const b140a00_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;

__attribute__((naked, noinline))
char object_select_random_region_permutations_by_variant(int object_handle __attribute__((unused)), void *model_tag __attribute__((unused)), int16_t variant __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0xc4(%%ebx), %%ecx\n\t"
      "addl $0xc4, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jle .Lobject_select_random_region_permutations_by_variant_7\n\t"
      "pushl %%esi\n\t"
      ".Lobject_select_random_region_permutations_by_variant_1:\n\t"
      "pushl $0x4c\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c13e3f0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lobject_select_random_region_permutations_by_variant_3\n\t"
      "cmpw $-1, 0xc(%%ebp)\n\t"
      "je .Lobject_select_random_region_permutations_by_variant_2\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c13e3f0]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lobject_select_random_region_permutations_by_variant_3\n\t"
      ".Lobject_select_random_region_permutations_by_variant_2:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb $0, 0x130(%%edi,%%ecx,1)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lobject_select_random_region_permutations_by_variant_6\n\t"
      ".Lobject_select_random_region_permutations_by_variant_3:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lobject_select_random_region_permutations_by_variant_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lobject_select_random_region_permutations_by_variant_5\n\t"
      ".Lobject_select_random_region_permutations_by_variant_4:\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lobject_select_random_region_permutations_by_variant_5:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "movb -0x4c(%%ebp,%%edx,2), %%al\n\t"
      "movb %%al, 0x130(%%edi,%%ecx,1)\n\t"
      ".Lobject_select_random_region_permutations_by_variant_6:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "cmpl (%%ebx), %%edi\n\t"
      "jl .Lobject_select_random_region_permutations_by_variant_1\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      ".Lobject_select_random_region_permutations_by_variant_7:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b140a00_get), [elem] "m"(b140a00_elem), [c13e3f0] "m"(b140a00_c13e3f0), [gseed] "m"(b140a00_gseed), [c10b2d0] "m"(b140a00_c10b2d0)
      : "memory");
}
#else
#error "object_select_random_region_permutations_by_variant: clang naked draft required"
#endif


/* object_choose_random_change_colors (0x13e1f0) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void *(*const b13e1f0_get)(int, int) = object_get_and_verify_type;
static void *(*const b13e1f0_tag)(int, int) = tag_get;
static void *(*const b13e1f0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b13e1f0_c1daf7e)(void) = FUN_001daf7e;
static float * (*const b13e1f0_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;

__attribute__((naked, noinline))
void object_choose_random_change_colors(int object_handle __attribute__((unused)), void *color_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x164, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal 0x138(%%edi), %%ebx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl $4, -0x18(%%ebp)\n\t"
      ".Lobject_choose_random_change_colors_1:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%eax), %%esi\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl 0x4(%%eax), %%esi\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "cmpl (%%eax), %%ecx\n\t"
      "jge .Lobject_choose_random_change_colors_5\n\t"
      "pushl $0x2c\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fmuls 0x29bbe0\n\t"
      "flds 0xc(%%edi)\n\t"
      "fmuls 0x29bbdc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x10(%%edi)\n\t"
      "fmuls 0x29bbd8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x29bbd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fabs\n\t"
      "fldl 0x2573d8\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "addl $0x20, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .Lobject_choose_random_change_colors_5\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lobject_choose_random_change_colors_2:\n\t"
      "pushl $0x1c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movl %%eax, %%ebx\n\t"
      "fcomps (%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lobject_choose_random_change_colors_3\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lobject_choose_random_change_colors_2\n\t"
      "jmp .Lobject_choose_random_change_colors_4\n\t"
      ".Lobject_choose_random_change_colors_3:\n\t"
      "flds 0x10(%%edi)\n\t"
      "fabs\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x29bbd0\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fldl 0x2573d8\n\t"
      "call *%[c1daf7e]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "leal 0x10(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c7c270]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_choose_random_change_colors_4:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      ".Lobject_choose_random_change_colors_5:\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_choose_random_change_colors_6\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_choose_random_change_colors_8\n\t"
      ".Lobject_choose_random_change_colors_6:\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_choose_random_change_colors_7\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_choose_random_change_colors_8\n\t"
      ".Lobject_choose_random_change_colors_7:\n\t"
      "flds (%%ebx)\n\t"
      ".Lobject_choose_random_change_colors_8:\n\t"
      "fstps 0x30(%%ebx)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_choose_random_change_colors_9\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_choose_random_change_colors_11\n\t"
      ".Lobject_choose_random_change_colors_9:\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_choose_random_change_colors_10\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_choose_random_change_colors_11\n\t"
      ".Lobject_choose_random_change_colors_10:\n\t"
      "flds 0x4(%%ebx)\n\t"
      ".Lobject_choose_random_change_colors_11:\n\t"
      "fstps 0x34(%%ebx)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_choose_random_change_colors_12\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_choose_random_change_colors_14\n\t"
      ".Lobject_choose_random_change_colors_12:\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_choose_random_change_colors_13\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_choose_random_change_colors_14\n\t"
      ".Lobject_choose_random_change_colors_13:\n\t"
      "flds 0x8(%%ebx)\n\t"
      ".Lobject_choose_random_change_colors_14:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fstps 0x38(%%ebx)\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "addl $0xc, %%esi\n\t"
      "addl $0xc, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .Lobject_choose_random_change_colors_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13e1f0_get), [tag] "m"(b13e1f0_tag), [elem] "m"(b13e1f0_elem), [c1daf7e] "m"(b13e1f0_c1daf7e), [c7c270] "m"(b13e1f0_c7c270)
      : "memory");
}
#else
#error "object_choose_random_change_colors: clang naked draft required"
#endif


/* object_compute_change_colors (0x13e5d0) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void *(*const b13e5d0_get)(int, int) = object_get_and_verify_type;
static void *(*const b13e5d0_tag)(int, int) = tag_get;
static void *(*const b13e5d0_elem)(void *, int, int) = tag_block_get_element;
static float * (*const b13e5d0_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;

__attribute__((naked, noinline))
void object_compute_change_colors(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movb 0x24(%%eax), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .Lobject_compute_change_colors_19\n\t"
      "movl 0x164(%%eax), %%ecx\n\t"
      "addl $0x164, %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .Lobject_compute_change_colors_18\n\t"
      "pushl %%edi\n\t"
      "jmp .Lobject_compute_change_colors_2\n\t"
      ".Lobject_compute_change_colors_1:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "nop\n\t"
      ".Lobject_compute_change_colors_2:\n\t"
      "pushl $0x2c\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lobject_compute_change_colors_5\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .Lobject_compute_change_colors_3\n\t"
      "movswl %%ax, %%edx\n\t"
      "flds 0xd0(%%ebx,%%edx,4)\n\t"
      "jmp .Lobject_compute_change_colors_4\n\t"
      ".Lobject_compute_change_colors_3:\n\t"
      "movswl %%ax, %%eax\n\t"
      "flds 0xd0(%%ebx,%%eax,4)\n\t"
      ".Lobject_compute_change_colors_4:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "leal 0x14(%%edi), %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x8(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x5a(%%esi,%%esi,2), %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal (%%ebx,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c270]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_change_colors_5:\n\t"
      "movw (%%edi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "je .Lobject_compute_change_colors_8\n\t"
      "cmpw $5, %%di\n\t"
      "jl .Lobject_compute_change_colors_6\n\t"
      "movswl %%di, %%ecx\n\t"
      "flds 0xd0(%%ebx,%%ecx,4)\n\t"
      "jmp .Lobject_compute_change_colors_7\n\t"
      ".Lobject_compute_change_colors_6:\n\t"
      "movswl %%di, %%edx\n\t"
      "flds 0xd0(%%ebx,%%edx,4)\n\t"
      ".Lobject_compute_change_colors_7:\n\t"
      "fld %%st(0)\n\t"
      "leal 0x5a(%%esi,%%esi,2), %%eax\n\t"
      "fmuls (%%ebx,%%eax,4)\n\t"
      "leal (%%ebx,%%eax,4), %%eax\n\t"
      "leal (%%esi,%%esi,2), %%ecx\n\t"
      "fstps (%%eax)\n\t"
      "leal (%%ebx,%%ecx,4), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x16c(%%eax)\n\t"
      "fstps 0x16c(%%eax)\n\t"
      "fmuls 0x170(%%eax)\n\t"
      "fstps 0x170(%%eax)\n\t"
      ".Lobject_compute_change_colors_8:\n\t"
      "leal 0x5a(%%esi,%%esi,2), %%edx\n\t"
      "flds (%%ebx,%%edx,4)\n\t"
      "leal (%%ebx,%%edx,4), %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_compute_change_colors_9\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_compute_change_colors_11\n\t"
      ".Lobject_compute_change_colors_9:\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_compute_change_colors_10\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_compute_change_colors_11\n\t"
      ".Lobject_compute_change_colors_10:\n\t"
      "flds (%%ecx)\n\t"
      ".Lobject_compute_change_colors_11:\n\t"
      "fstps (%%ecx)\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "flds 0x16c(%%ebx,%%eax,4)\n\t"
      "leal (%%ebx,%%eax,4), %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_compute_change_colors_12\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_compute_change_colors_14\n\t"
      ".Lobject_compute_change_colors_12:\n\t"
      "flds 0x16c(%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_compute_change_colors_13\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_compute_change_colors_14\n\t"
      ".Lobject_compute_change_colors_13:\n\t"
      "flds 0x16c(%%ecx)\n\t"
      ".Lobject_compute_change_colors_14:\n\t"
      "fstps 0x16c(%%ecx)\n\t"
      "flds 0x170(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_compute_change_colors_15\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_compute_change_colors_17\n\t"
      ".Lobject_compute_change_colors_15:\n\t"
      "flds 0x170(%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_compute_change_colors_16\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_compute_change_colors_17\n\t"
      ".Lobject_compute_change_colors_16:\n\t"
      "flds 0x170(%%ecx)\n\t"
      ".Lobject_compute_change_colors_17:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fstps 0x170(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "cmpl (%%ecx), %%esi\n\t"
      "jl .Lobject_compute_change_colors_1\n\t"
      "popl %%edi\n\t"
      ".Lobject_compute_change_colors_18:\n\t"
      "popl %%esi\n\t"
      ".Lobject_compute_change_colors_19:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13e5d0_get), [tag] "m"(b13e5d0_tag), [elem] "m"(b13e5d0_elem), [c7c270] "m"(b13e5d0_c7c270)
      : "memory");
}
#else
#error "object_compute_change_colors: clang naked draft required"
#endif


/* object_choose_random_region_permutations (0x140ad0) — XBE naked draft (batch 140). */
#if defined(__clang__)
static void *(*const b140ad0_get)(int, int) = object_get_and_verify_type;
static void *(*const b140ad0_tag)(int, int) = tag_get;
static char (*const b140ad0_c140a00)(int object_handle, void *model_tag, int16_t variant) = object_select_random_region_permutations_by_variant;
static int16_t (*const b140ad0_c13e460)(int object_handle, void *model_tag) = object_determine_variant_number;

__attribute__((naked, noinline))
void object_choose_random_region_permutations(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_choose_random_region_permutations_3\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6e(%%ebx), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lobject_choose_random_region_permutations_1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c140a00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_choose_random_region_permutations_2\n\t"
      ".Lobject_choose_random_region_permutations_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c140a00]\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13e460]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, 0x6e(%%ebx)\n\t"
      "jle .Lobject_choose_random_region_permutations_2\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c140a00]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_choose_random_region_permutations_2:\n\t"
      "popl %%esi\n\t"
      ".Lobject_choose_random_region_permutations_3:\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [get] "m"(b140ad0_get), [tag] "m"(b140ad0_tag), [c140a00] "m"(b140ad0_c140a00), [c13e460] "m"(b140ad0_c13e460)
      : "memory");
}
#else
#error "object_choose_random_region_permutations: clang naked draft required"
#endif


/* 0x13e7b0 / objects.obj — Evaluate all of the object tag's animation
 * functions for the current frame and store the results into the object's
 * function-value array (obj+0xe4 onward), updating the per-function active
 * bitmask byte at obj+0xd3.
 *
 * For each function definition (block obj_tag+0x158, element size 0x168):
 *   - Builds a per-object time input: (game_time_get() + (handle&0xffff)*0x39)
 *     scaled by a global constant (0x2546a4).
 *   - Evaluates a periodic waveform (FUN_0010a5e0) over that time, optionally
 *     scaled by a referenced function value, then applies inversion (flag 1),
 *     a secondary sinusoidal offset term, a step threshold, an exponent/floor
 *     stage, a modulo wrap, an additive function with clamp-to-1, a final
 *     multiplier function, a transition remap (transition_function_evaluate),
 *     a scale, and a range remap with min/max clamping (modes 1/2).
 *   - Computes an "active" bit from flag bit 2 and a dependency function's
 *     active bit (obj+0xd3 & (1<<elem[+0x36])).
 *   - With flag bit 1, wraps the result by adding the prior slot value and
 *     taking fmod(.,1.0) (accumulator).
 *   - Writes the result to obj+0xe4+i*4 and updates obj+0xd3 bit i.
 *
 * Role: object spawn / per-frame appearance; feeds object_compute_change_colors
 * and node/marker animation. Function values 0-4 (obj+0xd0) are engine
 * built-ins; indices 5+ written here begin at obj+0xe4 (=obj+0xd0+5*4).
 * object_handle in EAX (register arg).
 * Confirmed: ESI=object_handle saved before object_get_and_verify_type(EAX,-1).
 * Confirmed: time scale const *(float*)0x2546a4; output array obj+0xe4.
 * Confirmed: CMP 0x5;JL branches are vestigial bounds checks (identical loads).
 * Uncertain: many field offsets within the 0x168-byte element (see inline). */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(1)))
#endif
void object_compute_function_values(int object_handle /* @<eax> */)
{
  char *obj;
  int obj_tag;
  float time_base;
  int func_count;
  int16_t i;
  int16_t counter;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = (int)tag_get(0x6f626a65, *(int *)obj);

  /* per-object time input, scaled to seconds */
  time_base = (float)(game_time_get() + (object_handle & 0xffff) * 0x39) *
              *(float *)0x2546a4;

  func_count = *(int *)(obj_tag + 0x158);
  i = 0;
  counter = 0;
  if (func_count <= 0) {
    return;
  }
  do {
    char *elem = (char *)tag_block_get_element(
        (void *)(obj_tag + 0x158), (int)i, 0x168);
    unsigned char active;
    float value;
    float t;
    int16_t fn;
    int16_t mode;

    active = 1;

    /* --- primary periodic waveform --- */
    t = *(float *)(elem + 0x144);
    fn = *(int16_t *)(elem + 0x8);
    if (fn != 0) {
      float fv = *(float *)(obj + 0xd0 + (int)fn * 4);
      if (fv > *(float *)0x2533c0) {
        t = t / fv;
      }
    }
    t = t * time_base;
    value = FUN_0010a5e0(*(int16_t *)(elem + 0xa), t);

    /* --- optional amplitude function --- */
    fn = *(int16_t *)(elem + 0xc);
    if (fn != 0) {
      value = *(float *)(obj + 0xd0 + (int)fn * 4) * value;
    }

    /* --- inversion (flag bit 0) --- */
    if ((*(unsigned char *)elem & 1) != 0) {
      value = *(float *)0x2533c8 - value;
    }

    /* --- secondary sinusoidal offset term (when elem+0x14 != 0) --- */
    if (*(float *)(elem + 0x14) != *(float *)0x2533c0) {
      float w = FUN_0010a5e0(*(int16_t *)(elem + 0xe),
                             time_base * *(float *)(elem + 0x10));
      w = (w - *(float *)0x253398) * *(float *)(elem + 0x14);
      value = w + w + value;
    }

    /* --- step threshold (when elem+0x18 != 0): 1.0 if value>thr else 0.0 --- */
    if (*(float *)(elem + 0x18) != *(float *)0x2533c0) {
      float prev = value;
      value = 1.0f;
      if (prev <= *(float *)(elem + 0x18)) {
        value = 0.0f;
      }
    }

    /* --- exponent/floor stage (when elem+0x1c > 1) --- */
    if (*(int16_t *)(elem + 0x1c) > 1) {
      value = (float)floor((double)((float)*(int16_t *)(elem + 0x1c) * value)) *
              *(float *)(elem + 0x140);
    }

    /* --- modulo wrap (when elem+0x13c > 0) --- */
    if (*(float *)(elem + 0x13c) > *(float *)0x2533c0) {
      value = x87_fmod(value, (double)*(float *)(elem + 0x13c));
    }

    /* --- additive function with clamp-to-1 --- */
    fn = *(int16_t *)(elem + 0x22);
    if (fn != 0) {
      value = *(float *)(obj + 0xd0 + (int)fn * 4) + value;
      if (value > *(float *)0x2533c8) {
        value = *(float *)0x2533c8;
      }
    }

    /* --- final multiplier function --- */
    fn = *(int16_t *)(elem + 0x24);
    if (fn != 0) {
      value = *(float *)(obj + 0xd0 + (int)fn * 4) * value;
    }

    /* --- transition remap --- */
    value = transition_function_evaluate(*(int16_t *)(elem + 0x1e), value);

    /* --- scale (when elem+0x38 > 0) --- */
    if (*(float *)(elem + 0x38) > *(float *)0x2533c0) {
      value = value * *(float *)(elem + 0x38);
    }

    /* --- range remap (modes 1/2) --- */
    mode = *(int16_t *)(elem + 0x26);
    if (mode == 2) {
      value = (*(float *)(elem + 0x2c) - *(float *)(elem + 0x28)) * value +
              *(float *)(elem + 0x28);
      if (*(float *)(elem + 0x28) + *(float *)0x253f44 >= value) {
        active = (unsigned char)(*(unsigned int *)elem >> 2) & 1;
      }
    } else {
      if (*(float *)(elem + 0x28) + *(float *)0x253f44 >= value) {
        value = *(float *)(elem + 0x28);
        active = (unsigned char)(*(unsigned int *)elem >> 2) & 1;
      }
      if (value > *(float *)(elem + 0x2c)) {
        value = *(float *)(elem + 0x2c);
      }
      if (mode == 1) {
        value = (value - *(float *)(elem + 0x28)) * *(float *)(elem + 0x138);
      }
    }

    /* --- dependency on another function's active bit --- */
    if (*(int16_t *)(elem + 0x36) != -1 &&
        (*(unsigned char *)(obj + 0xd3) &
         (unsigned char)(1 << (*(int16_t *)(elem + 0x36) & 0x1f))) == 0) {
      active = 0;
    }

    /* --- accumulator wrap (flag bit 1), using prior slot value --- */
    if ((*(unsigned char *)elem & 2) != 0) {
      value = x87_fmod(value + *(float *)(obj + 0xe4 + (int)i * 4),
                       *(double *)0x2573d8);
    }

    /* --- store result and update active bitmask --- */
    *(float *)(obj + 0xe4 + (int)i * 4) = value;
    if (active != 0) {
      *(unsigned char *)(obj + 0xd3) =
          *(unsigned char *)(obj + 0xd3) | (unsigned char)(1 << ((int)i & 0x1f));
    } else {
      *(unsigned char *)(obj + 0xd3) =
          *(unsigned char *)(obj + 0xd3) & ~(unsigned char)(1 << ((int)i & 0x1f));
    }

    counter = counter + 1;
    i = counter;
  } while ((int)i < *(int *)(obj_tag + 0x158));
}

/*
 * objects_initialize — one-time initialisation of the object subsystem.
 *
 * Called once at startup (not per-map). Allocates the four root resources:
 *   - object header data table (data_t*) stored at 0x5a8d50
 *   - object memory pool (void*) stored at objects (0x46f080)
 *   - object_globals struct stored at object_globals (0x46f084)
 *   - object_name_list buffer stored at object_name_list (0x46f07c)
 * Then initialises the collideable and noncollideable cluster partition
 * structures at 0x5a8d40 and 0x5a8d30 via FUN_00191500.
 *
 * The allocation strategy differs between editor and non-editor modes:
 *   Non-editor: game_state_data_new("object", 0x800, 0xc) — data_array_new from
 *               game-state block; game_state_memory_pool_new("objects", 0x100000) —
 *               memory-pool_new from game-state block.
 *   Editor:     data_new("object", 0x2800, 0xc) — data_array_new from
 *               main heap; memory_pool_new("objects", &DAT_500000) — memory-
 *               pool_new from main heap using a size read from 0x500000.
 *
 * Sub-system init call order (confirmed from disasm):
 *   widgets_initialize_for_new_map — unknown object sub-type A init
 *   FUN_00135f90 — unknown object sub-type B init
 *   FUN_0013c2e0 — object type definition list init
 *   lights_initialize — object BSP cluster data init
 *
 * Confirmed: PUSH 0xc pre-pushed before JNZ — shared 3rd arg to both
 *            first-call variants; ADD ESP,0x14 cleans 5 args (3+2).
 * Confirmed: game_in_editor() returns bool via AL; TEST AL,AL / JNZ selects
 *            the editor allocation path.
 * Confirmed: ADD ESP,0x14 after display_assert+system_exit cleans 5 words
 *            (4 for display_assert + 1 for system_exit) in all 3 assert sites.
 * Confirmed: game_state_malloc("object globals", 0, 0x98) allocates object_globals;
 *            game_state_malloc("object name list", 0, 0x800) allocates name list.
 *            Both are game_state_alloc(name, tag?, size) — 3 cdecl args,
 *            ADD ESP,0xc each.
 * Confirmed: FUN_00191500 takes (void *partition, const char *name) — called
 *            twice; ADD ESP,0x10 cleans both calls (2 args * 2 calls).
 */
void objects_initialize(void)
{
  /* Initialise sub-systems (order confirmed from disasm) */
  ((pfn_void_t)0x136580)();
  ((pfn_void_t)0x135f90)();
  FUN_0013c2e0();
  ((pfn_void_t)0x1391e0)();

  if (!game_in_editor()) {
    /* Non-editor: allocate from game-state block */
    *(void **)0x5a8d50 =
      ((void *(*)(const char *, int, int))0x1bfe10)("object", 0x800, 0xc);
    objects = ((void *(*)(const char *, int))0x1bfe50)("objects", 0x100000);
  } else {
    /* Editor: allocate from main heap */
    *(void **)0x5a8d50 =
      ((void *(*)(const char *, int, int))0x1194d0)("object", 0x2800, 0xc);
    objects =
      ((void *(*)(const char *, void *))0x11e650)("objects", (void *)0x500000);
  }

  if (*(void **)0x5a8d50 == 0 || objects == 0) {
    display_assert("object_header_data && object_memory_pool",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0xd8, 1);
    system_exit(-1);
  }

  object_globals = ((object_globals_t * (*)(const char *, int, int))0x1bfbf0)(
    "object globals", 0, 0x98);
  if (object_globals == 0) {
    display_assert("object_globals", "c:\\halo\\SOURCE\\objects\\objects.c",
                   0xdb, 1);
    system_exit(-1);
  }

  object_name_list =
    ((void *(*)(const char *, int, int))0x1bfbf0)("object name list", 0, 0x800);
  if (object_name_list == 0) {
    display_assert("object_name_list", "c:\\halo\\SOURCE\\objects\\objects.c",
                   0xfe8, 1);
    system_exit(-1);
  }

  /* Initialise collideable and noncollideable cluster partition structs */
  ((void (*)(void *, const char *))0x191500)((void *)0x5a8d40,
                                             "collideable object");
  ((void (*)(void *, const char *))0x191500)((void *)0x5a8d30,
                                             "noncollideable object");
}

/*
 * objects_initialize_for_new_map — reset object subsystems when loading a map.
 *
 * Call order (confirmed from disasm):
 *   widgets_dispose  — resets a global slot index (object type slot reset)
 *   FUN_00136040  — iterates 5 object type slots, calls initialize_for_new_map
 *                   vtable entry via [EDI] (slot stride 0x28)
 *   FUN_0013c3d0  — walks the object_type_definition linked list, calls
 *                   each type's initialize_for_new_map function at +0x18
 *   lights_initialize_for_new_map  — calls data_delete_all on a BSP cluster
 * data table, then object_list_initialize_for_new_map via FUN_1915d0
 *
 * Then:
 *   data_delete_all(*(data_t**)0x5a8d50)        — clear all object headers
 *   csmemset(object_name_list, 0xff, 0x800)      — reset name list
 *   FUN_001915d0(&collideable_cluster_partition)  — reset collideable cluster
 *   FUN_001915d0(&noncollideable_cluster_partition) — reset noncollideable
 *   csmemset(object_globals->combined_pvs, 0, 64)
 *   csmemset(object_globals->combined_pvs_local, 0, 64)
 *   object_globals->pvs_activator_type = 0
 *   object_globals->object_marker_initialized = 0
 *   *(uint32_t*)0x5a8d28 = 0                     — unknown global counter
 *   object_globals->unk_8 = 0xffffffff            — datum handle sentinel
 *   object_globals->unk_4 = 0
 *   object_globals->last_garbage_collection_tick = 0
 *
 * Confirmed: ADD ESP,0x30 cleans 12 args across the 4 csmemset calls and
 *            the two FUN_1915d0 calls, consistent with 12 total cdecl pushes.
 */
void objects_initialize_for_new_map(void)
{
  object_globals_t *og;

  ((pfn_void_t)0x1365a0)();
  ((pfn_void_t)0x136040)();
  ((pfn_void_t)0x13c3d0)();
  ((pfn_void_t)0x1392b0)();

  data_delete_all(*(data_t **)0x5a8d50);
  csmemset(object_name_list, 0xff, 0x800);

  /* Reset collideable and noncollideable cluster partition structs.
   * These are 12-byte structs (3 data_t* fields) at fixed addresses. */
  ((void (*)(void *))0x1915d0)((void *)0x5a8d40);
  ((void (*)(void *))0x1915d0)((void *)0x5a8d30);

  og = object_globals;

  csmemset(og->combined_pvs, 0, 0x40);
  csmemset(og->combined_pvs_local, 0, 0x40);

  og->pvs_activator_type = 0;
  og->object_marker_initialized = 0;

  *(uint32_t *)0x5a8d28 = 0;

  og->unk_8.value = 0xffffffff;
  og->unk_4 = 0;
  og->last_garbage_collection_tick = 0;
}

/*
 * objects_dispose_from_old_map — per-map teardown of the object subsystem.
 *
 * Called when unloading a map (0x000a70a5 → this function). Counterpart to
 * objects_initialize_for_new_map (0x13f950). Distinct from objects_dispose
 * (0x13fac0), which is the one-time full teardown.
 *
 * Call order (confirmed from disasm):
 *   widgets_dispose_from_old_map  — per-map dispose for type-slot array
 *   FUN_001360a0  — per-map dispose for 5 object-type slots
 *   FUN_0013c400  — per-map dispose for object type definition list
 *   lights_dispose_from_old_map  — per-map dispose for BSP cluster data
 *
 * Then, if the object header data table is valid (byte at data+0x24 != 0):
 *   Walk every datum via data_next_index (0x1198f0):
 *     - datum_get (0x119320) to retrieve element ptr (EBX)
 *     - if element->field_8 != NULL: memory_pool_free(objects,
 * &element->field_8)
 *     - datum_delete (0x1196d0) to remove the datum
 *     - zero element->field_8 and element->field_2
 *   After loop: data_make_invalid (0x119550) on the table
 *
 * Finally dispose collideable and noncollideable cluster partition structs:
 *   FUN_00191600(&collideable_cluster_partition)
 *   FUN_00191600(&noncollideable_cluster_partition)
 *
 * Confirmed: no arguments — caller at 0x000a70a5 uses bare CALL with no PUSH.
 *            Ghidra's __fastcall/param_1 is a misread of the PUSH ECX stack
 *            slot reservation in the function prologue.
 * Confirmed: MOV CL, byte ptr [EAX+0x24] / TEST CL,CL — byte guard on data
 *            valid flag (data_t.valid) before the loop.
 * Confirmed: ADD ESP,0x8 after datum_get and data_next_index calls (2 cdecl
 *            args each); ADD ESP,0x10 at loop-end cleans datum_delete (0x8) +
 *            data_next_index advance call (0x8) together.
 * Confirmed: ADD ESP,0x8 after memory_pool_free (2 cdecl args).
 * Confirmed: ADD ESP,0x4 after data_make_invalid (1 cdecl arg).
 * Confirmed: ADD ESP,0x8 cleans the two FUN_191600 calls at the end.
 * Confirmed: MOV dword ptr [EBP-4], EAX saves data ptr; reloaded at
 *            0x13fa5d for datum_delete after the conditional pool-free.
 * Confirmed: LEA EDI,[EBX+8] — EDI = &element->field_8 — passed as
 *            arg2 to memory_pool_free; also used to zero field_8 at 0x13fa67.
 */
void objects_dispose_from_old_map(void)
{
  data_t *obj_data;

  ((pfn_void_t)0x1365b0)();
  ((pfn_void_t)0x1360a0)();
  ((pfn_void_t)0x13c400)();
  ((pfn_void_t)0x1392e0)();

  obj_data = *(data_t **)0x5a8d50;

  /* Only walk the table if it has been made valid */
  if (*(uint8_t *)((uint8_t *)obj_data + 0x24) != 0) {
    int idx = data_next_index(obj_data, -1);
    while (idx != -1) {
      /* datum_get returns a pointer; field at +8 is the object data ptr */
      uint8_t *elem = (uint8_t *)datum_get(obj_data, idx);
      void **field_8_ptr = (void **)(elem + 0x8);

      if (*field_8_ptr != 0) {
        /* Free this object's memory pool allocation */
        ((void (*)(void *, void **))0x11e7a0)(*(void **)0x46f080, field_8_ptr);
      }

      datum_delete(obj_data, idx);

      /* Zero out field_8 and field_2 unconditionally after delete */
      *field_8_ptr = 0;
      *(uint8_t *)(elem + 0x2) = 0;

      idx = data_next_index(*(data_t **)0x5a8d50, idx);
    }
    data_make_invalid(*(data_t **)0x5a8d50);
  }

  /* Dispose cluster partition sub-tables */
  ((void (*)(void *))0x191600)((void *)0x5a8d40);
  ((void (*)(void *))0x191600)((void *)0x5a8d30);
}

/*
 * objects_dispose — tear down all object subsystems.
 *
 * Call order (confirmed from disasm):
 *   FUN_00136100  — iterates 5 type slots, calls dispose vtable entry at [EDI]
 *   FUN_0013c3a0  — walks linked list, calls each type's dispose at +0x14
 *   lights_dispose  — disposes the BSP cluster data, calls FUN_191630
 *
 * Then:
 *   if (!game_in_editor()):  null out *(data_t**)0x5a8d50 (don't free)
 *   else:                    data_dispose(*(data_t**)0x5a8d50)
 *
 *   if (objects != NULL):    objects = NULL  (pool not freed here)
 *
 *   FUN_00191630(&collideable_cluster_partition)   — zero 3 ptr fields
 *   FUN_00191630(&noncollideable_cluster_partition)
 *
 * Confirmed: JNZ selects data_dispose path; JZ / JNZ gates objects null.
 * Confirmed: ADD ESP,0x4 after data_dispose (1 cdecl arg).
 * Confirmed: ADD ESP,0x8 cleans 2 FUN_191630 calls at end.
 */
void objects_dispose(void)
{
  ((pfn_void_t)0x136100)();
  ((pfn_void_t)0x13c3a0)();
  ((pfn_void_t)0x1392a0)();

  if (!game_in_editor()) {
    /* Not in editor: just null the pointer, do not free */
    data_t **obj_data_ptr = (data_t **)0x5a8d50;
    if (*obj_data_ptr != 0) {
      *obj_data_ptr = 0;
    }
  } else {
    data_t *obj_data = *(data_t **)0x5a8d50;
    data_dispose(obj_data);
  }

  if (objects != 0) {
    objects = 0;
  }

  /* Zero out cluster partition structs (3 data_t* fields each) */
  ((void (*)(void *))0x191630)((void *)0x5a8d40);
  ((void (*)(void *))0x191630)((void *)0x5a8d30);
}

/*
 * object_activate — mark a root object as "outdoor"/visible if it passes
 * the activation conditions: not already active (bit 0x01), not flagged
 * 0x100000, and has no parent.
 *
 * Confirmed: CALL 0x119320 (datum_get) + CALL 0x13d680
 * (object_get_and_verify_type). Confirmed: tests header->unk_2 bit 0x01,
 * obj->flags bit 0x100000, obj->parent_object_index == -1. Confirmed: sets
 * header->unk_2 |= 0x01 on success.
 */
void object_activate(int object_handle)
{
  object_header_data_t *hdr =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);
  if ((hdr->unk_2 & 0x01) == 0 && (obj->flags & 0x100000) == 0 &&
      obj->parent_object_index.value == -1) {
    hdr->unk_2 |= 0x01;
  }
}

/*
 * object_deactivate — clear the "active" flag (bit 0x01) from an object's
 * header unk_2 byte, if currently set.
 *
 * Inverse of object_activate: deactivates the object by clearing bit 0x01.
 *
 * Confirmed: CALL 0x119320 (datum_get), CALL 0x13d680
 *   (object_get_and_verify_type) with type_mask=-1.
 * Confirmed: TEST AL,0x1; JZ skip; AND AL,0xFE; MOV [ESI+2],AL.
 * Confirmed: ADD ESP,0x10 cleans datum_get + object_get_and_verify_type.
 */
void object_deactivate(int object_handle)
{
  object_header_data_t *hdr =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);
  (void)obj; /* return value unused but call required for verification */
  if ((hdr->unk_2 & 0x01) != 0) {
    hdr->unk_2 &= ~0x01;
  }
}

/*
 * object_reset — reset an object to its default world position.
 *
 * Copies the 3-float default-position vector from *(float**)0x31fc38 into
 * both the object's position (+0x18..+0x20) and forward/up (+0x3c..+0x44),
 * clears the "at-rest" flag (bit 5 of object[+4]), then calls
 * FUN_0013c860 to perform a final physics/placement update.
 *
 * Confirmed: single call to object_get_and_verify_type(handle, -1), then
 * two identical 3-dword copies from [0x31fc38]. The 3 cdecl args
 * (−1, handle, handle) are batch-cleaned by ADD ESP,0xc after FUN_0013c860.
 *
 * 0x13fbc0 / objects.obj
 */
void object_reset(int object_handle)
{
  char *obj;
  float *def;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  def = *(float **)0x31fc38;
  *(float *)(obj + 0x18) = def[0];
  *(float *)(obj + 0x1c) = def[1];
  *(float *)(obj + 0x20) = def[2];
  *(float *)(obj + 0x3c) = def[0];
  *(float *)(obj + 0x40) = def[1];
  *(float *)(obj + 0x44) = def[2];
  *(unsigned int *)(obj + 4) &= ~0x20u;
  FUN_0013c860(object_handle);
}

/*
 * object_placement_data_new — initialise an object placement data struct.
 *
 * Zeroes the 0x88-byte placement buffer, stores the tag index at +0x00,
 * copies default forward {1,0,0} and up {0,0,1} vectors from constant
 * tables, then resolves the parent handle through the object header table:
 *   - If parent is valid: copies parent_object_index (+0x70), cluster
 *     index (+0x68), and the raw handle into the placement.
 *   - Otherwise: sets parent/cluster fields to -1/0xFFFF.
 * Finally fills four scale vectors at +0x58 with {1,1,1} each.
 *
 * Confirmed: csmemset(param_1, 0, 0x88) — 136-byte struct.
 * Confirmed: *(void**)0x31fc3c → {1.0, 0.0, 0.0} default forward.
 * Confirmed: *(void**)0x31fc44 → {0.0, 0.0, 1.0} default up.
 * Confirmed: *(void**)0x2ee708 → {1.0, 1.0, 1.0} default scale.
 * Confirmed: datum_absolute_index_to_index(DAT_005a8d50, parent_handle)
 *            returns header ptr; +0x3 = type, +0x8 = object ptr.
 * Confirmed: word at [ESI+0x16] = 0.
 * Confirmed: 4 iterations of 12-byte copy for scale at [ESI+0x58].
 */
void object_placement_data_new(void *placement, int tag_index,
                               int parent_handle)
{
  char *p = (char *)placement;
  float *src;
  int header;
  int obj;
  int i;

  csmemset(placement, 0, 0x88);

  /* +0x00: tag index */
  *(int *)(p + 0x00) = tag_index;
  /* +0x04: flags = 0 (already zeroed) */
  *(int *)(p + 0x04) = 0;

  /* +0x34: default forward vector {1,0,0} from *(void**)0x31fc3c */
  src = *(float **)0x31fc3c;
  *(float *)(p + 0x34) = src[0];
  *(float *)(p + 0x38) = src[1];
  *(float *)(p + 0x3c) = src[2];

  /* +0x40: default up vector {0,0,1} from *(void**)0x31fc44 */
  src = *(float **)0x31fc44;
  *(float *)(p + 0x40) = src[0];
  *(float *)(p + 0x44) = src[1];
  *(float *)(p + 0x48) = src[2];

  /* +0x16: zero (int16) */
  *(int16_t *)(p + 0x16) = 0;

  /* Resolve parent: datum_absolute_index_to_index returns header or 0 */
  header = datum_absolute_index_to_index(*(data_t **)0x5a8d50, parent_handle);
  if (header == 0 || (1 << (*(uint8_t *)(header + 0x3) & 0x1f)) == 0 ||
      *(int *)(header + 0x8) == 0) {
    /* No valid parent */
    *(int *)(p + 0x0c) = -1;
    *(int *)(p + 0x08) = -1;
    *(int16_t *)(p + 0x14) = -1;
  } else {
    obj = *(int *)(header + 0x8);
    *(int *)(p + 0x0c) = parent_handle;
    *(int *)(p + 0x08) = *(int *)(obj + 0x70);
    *(int16_t *)(p + 0x14) = *(int16_t *)(obj + 0x68);
  }

  /* +0x58: four {1,1,1} scale vectors from *(void**)0x2ee708 */
  {
    char *dst = p + 0x58;
    for (i = 4; i != 0; i--) {
      src = *(float **)0x2ee708;
      *(float *)(dst + 0x0) = src[0];
      *(float *)(dst + 0x4) = src[1];
      *(float *)(dst + 0x8) = src[2];
      dst += 0xc;
    }
  }
}

/*
 * object_disconnect_from_map — remove an object from the BSP cluster
 * partition and its parent's child chain, then clear the
 * _object_connected_to_map_bit (0x800) flag.
 *
 * If the object has a parent (parent_object_index != NONE), it unlinks
 * itself from the parent's child-object linked list starting at
 * parent_obj+0xC8 (via the list-remove helper at 0x13e510, which walks
 * next_object_index links at obj+0xC4).
 *
 * If the object has no parent, it removes itself from the appropriate
 * cluster partition (0x5a8d40 for objects with flag 0x2000000 set,
 * 0x5a8d30 otherwise) via the partition-remove call at 0x1919a0. It
 * then optionally clears the "outdoor" bit (header byte+2, bit 0x1)
 * if the header's bit 0x40 flag is set.
 *
 * Confirmed: single cdecl arg (object_handle).
 * Confirmed: assert strings reference objects.c lines 0x3bd and 0x3be.
 * Confirmed: 0x13e510 reads EAX (ptr to first_child_ref) and EBX
 *   (object_handle) as register args with 0 stack args.
 * Confirmed: 0x1919a0 is cdecl with 3 stack args (partition, handle, ptr).
 */
void object_disconnect_from_map(int object_handle)
{
  object_header_data_t *header;
  object_data_t *obj;

  header =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  obj = header->object;

  /* assert: identifier portion of handle must be nonzero */
  assert_halt(object_handle & 0xffff0000);

  /* assert: object must be connected to map */
  assert_halt(obj->flags & 0x800);

  if (obj->parent_object_index.value != NONE) {
    /* Object has a parent: unlink from parent's child chain.
     * Get the parent's object data, then call the list-remove helper
     * at 0x13e510 with EAX = &parent_obj->unk_200 (child list head)
     * and EBX = object_handle to unlink. */
    object_data_t *parent_obj = (object_data_t *)object_get_and_verify_type(
      obj->parent_object_index.value, -1);
    object_child_list_remove((void *)((char *)parent_obj + 0xc8),
                             object_handle);
  } else {
    /* No parent: remove from cluster partition. */
    object_data_t *self_obj =
      (object_data_t *)object_get_and_verify_type(object_handle, -1);
    void *partition;
    if (self_obj->flags & 0x2000000)
      partition = (void *)0x5a8d40;
    else
      partition = (void *)0x5a8d30;

    cluster_partition_remove_object(partition, object_handle,
                                    (void *)((char *)obj + 0xbc));

    /* If header bit 0x40 is set, re-fetch header and clear bit 0x1 */
    if (header->unk_2 & 0x40) {
      object_header_data_t *header2 =
        (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
      object_get_and_verify_type(object_handle, -1);
      if (header2->unk_2 & 0x1) {
        header2->unk_2 &= ~0x1;
      }
    }
  }

  /* Clear _object_connected_to_map_bit (0x800) in object flags */
  obj->flags &= ~(uint32_t)0x800;

  /* Clear bit 0x20 in header flags byte */
  header->unk_2 &= ~0x20;
}

/* Get the node matrices reference block for an object.
 * Returns the header block reference at offset 0x1a0 from the object header.
 * 0x13fe70 / objects.obj
 */
void *object_get_node_matrices(int object_handle)
{
  void *obj = object_get_and_verify_type(object_handle, 0xffffffff);
  return object_header_block_reference_get(object_handle, (char *)obj + 0x1a0);
}

/*
 * object_get_child_marker_definition — get a marker definition from the
 * object's child model tag.
 *
 * Resolves the object's tag data via tag_get('obje', obj->tag_index),
 * then checks if marker_index is in range [0, block_count at tag+0x140).
 * If valid, returns tag_block_get_element(tag+0x140, marker_index, 0x48) +
 * 0x10. Returns NULL if index is out of range or negative.
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type), with -1 mask.
 * Confirmed: CALL 0x1ba140 (tag_get) with 'obje' (0x6f626a65) group tag.
 * Confirmed: CALL 0x19b210 (tag_block_get_element) with block at tag+0x140,
 *            element size 0x48, returns pointer + 0x10.
 * Confirmed: CMP CX,0 / CMP ECX,EDX — signed short check against block count.
 */
void *object_get_child_marker_definition(int object_handle,
                                         int16_t marker_index)
{
  uint32_t *obj = (uint32_t *)object_get_and_verify_type(object_handle, -1);
  int tag = (int)tag_get(0x6f626a65, (int)*obj);

  if (marker_index >= 0 && marker_index < *(int *)(tag + 0x140)) {
    return (char *)tag_block_get_element((void *)(tag + 0x140), marker_index,
                                         0x48) +
           0x10;
  }
  return NULL;
}

/*
 * object_has_node — check whether a given node index is valid for an object.
 *
 * Returns true if the object's model tag ('mode') has a nodes block and
 * node_index falls within [0, node_count). If the object tag definition has
 * no model reference (tag+0x34 == -1), returns true only when node_index == 0
 * (the implicit root node).
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type), 2 stack args.
 * Confirmed: CALL 0x1ba140 (tag_get) twice — first with 'obje', then 'mode'.
 * Confirmed: CMP word ptr [EBP+0xc],0x0 — node_index is int16_t.
 * Confirmed: model node count at offset 0xb8 in model tag data.
 * Confirmed: XOR BL,BL — false default; MOV AL,0x1 for true paths.
 */
bool object_has_node(int object_handle, int16_t node_index)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);

  /* Look up the object's tag definition ('obje') */
  void *obje_tag = tag_get(0x6f626a65, (int)obj->tag_index);
  int model_tag_index = *(int *)((char *)obje_tag + 0x34);

  if (model_tag_index == -1) {
    /* No model — only node 0 (implicit root) is valid */
    if (node_index == 0)
      return true;
  } else {
    /* Look up the model tag ('mode') and check node count at offset 0xb8 */
    void *mode_tag = tag_get(0x6d6f6465, model_tag_index);
    if (node_index >= 0 && (int)node_index < *(int *)((char *)mode_tag + 0xb8))
      return true;
  }

  return false;
}

/*
 * object_set_automatic_deactivation — set or clear the "hidden" flag (bit 0x40)
 * on an object's header unk_2 byte, and optionally activate or deactivate the
 * object.
 *
 * When param_2 != 0 (hide):
 *   Sets bit 0x40 on hdr->unk_2. If the object has no parent
 *   (parent_object_index == -1) AND unk_76.index == -1, calls
 *   object_deactivate to deactivate (clear bit 0x01).
 *
 * When param_2 == 0 (unhide):
 *   Clears bit 0x40 from hdr->unk_2. If bit 0x01 is not set (i.e. the
 *   object is not currently active), calls object_activate.
 *
 * Confirmed: CALL 0x119320 (datum_get), CALL 0x13d680
 *   (object_get_and_verify_type) with type_mask=-1.
 * Confirmed: OR byte [ESI+2],0x40 in true branch; AND AL,0xBF in false.
 * Confirmed: CMP dword [EAX+0xCC],-1 (parent_object_index.value).
 * Confirmed: CMP word [EAX+0x4C],-1 (unk_76.index, 16-bit compare).
 * Confirmed: CALL 0x13fb80 (deactivate) and CALL 0x13fb30 (activate).
 * Confirmed: ADD ESP,0x10 cleans datum_get + object_get_and_verify_type.
 */
void object_set_automatic_deactivation(int object_handle, char param_2)
{
  object_header_data_t *hdr =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);

  if (param_2 != 0) {
    hdr->unk_2 |= 0x40;
    if (obj->parent_object_index.value == -1 && obj->unk_76.index == -1) {
      object_deactivate(object_handle);
    }
  } else {
    uint8_t val = hdr->unk_2 & ~0x40;
    hdr->unk_2 = val;
    if ((val & 0x01) == 0) {
      object_activate(object_handle);
    }
  }
}

/* object_set_garbage (0x13ffc0) — XBE naked draft (batch 138). */
#if defined(__clang__)
static void *(*const b13ffc0_get)(int, int) = object_get_and_verify_type;
static void *(*const b13ffc0_tag)(int, int) = tag_get;
static void (*const b13ffc0_c13ee60)(int object_handle, char do_wake, char do_limbo) = object_propagate_flag_to_children;
static void *(*const b13ffc0_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
void object_set_garbage(int object_handle __attribute__((unused)), int flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_set_garbage_1\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $1, %%eax\n\t"
      "je .Lobject_set_garbage_5\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lobject_set_garbage_5\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13ee60]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_set_garbage_1:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_set_garbage_3\n\t"
      ".Lobject_set_garbage_2:\n\t"
      "cmpl $-1, 0x34(%%ebx)\n\t"
      "je .Lobject_set_garbage_4\n\t"
      ".Lobject_set_garbage_3:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lobject_set_garbage_6\n\t"
      "orl $1, 0x4(%%esi)\n\t"
      "andb $0xfd, 0x2(%%eax)\n\t"
      ".Lobject_set_garbage_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_set_garbage_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lobject_set_garbage_1\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_set_garbage_2\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13ee60]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lobject_set_garbage_3\n\t"
      ".Lobject_set_garbage_6:\n\t"
      "andl $0xfffffffe, 0x4(%%esi)\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "popl %%edi\n\t"
      "orb $2, %%cl\n\t"
      "popl %%esi\n\t"
      "movb %%cl, 0x2(%%eax)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13ffc0_get), [tag] "m"(b13ffc0_tag), [c13ee60] "m"(b13ffc0_c13ee60), [dget] "m"(b13ffc0_dget)
      : "memory");
}
#else
#error "object_set_garbage: clang naked draft required"
#endif


/* Walk the parent chain to the root object and copy its position and
 * forward vector to the output buffers (0x140070). Either output may
 * be NULL to skip copying. Position is at object offset 0x18 (3 floats),
 * forward direction at 0x3c (3 floats). */
void object_get_root_location(int object_handle, float *position_out,
                              float *direction_out)
{
  char *obj = (char *)object_get_and_verify_type(object_handle, -1);

  while (*(int *)(obj + 0xcc) != -1) {
    object_header_data_t *header = (object_header_data_t *)datum_get(
      *(data_t **)0x5a8d50, *(int *)(obj + 0xcc));
    obj = (char *)header->object;

    {
      int16_t type = *(int16_t *)(obj + 0x64);
      if ((1 << (type & 0x1f)) == 0) {
        char *msg = csprintf((char *)0x5ab100,
                             "got an object type we didn't expect "
                             "(expected one of 0x%08x but got #%d).",
                             -1, (int)type);
        display_assert(msg, "c:\\halo\\SOURCE\\objects\\objects.c", 0x69a, 1);
        system_exit(-1);
      }
    }
  }

  if (position_out != NULL) {
    position_out[0] = *(float *)(obj + 0x18);
    position_out[1] = *(float *)(obj + 0x1c);
    position_out[2] = *(float *)(obj + 0x20);
  }

  if (direction_out != NULL) {
    direction_out[0] = *(float *)(obj + 0x3c);
    direction_out[1] = *(float *)(obj + 0x40);
    direction_out[2] = *(float *)(obj + 0x44);
  }
}

/*
 * object_get_location — returns the root object's 8-byte location pair.
 *
 * Resolves the topmost parent handle via object_get_root_parent(handle), verifies that
 * object with object_get_and_verify_type(root_handle, -1), then copies dwords
 * at offsets +0x48 and +0x4c into location_out.
 *
 * Confirmed: CALL 0x13d7f0 with object_handle, then CALL 0x13d680 with
 *            returned handle and mask -1.
 * Confirmed: MOV [obj+0x48] -> [location_out+0], MOV [obj+0x4c] ->
 *            [location_out+4].
 */
void object_get_location(int object_handle, void *location_out)
{
  /* Single nested cdecl expression so MSVC pre-pushes the -1 type_mask before
   * evaluating object_get_root_parent (matches the original's interleaved push
   * scheduling). */
  object_data_t *obj = (object_data_t *)object_get_and_verify_type(
      object_get_root_parent(object_handle), -1);
  uint32_t *out = (uint32_t *)location_out;

  out[0] = obj->unk_72;
  out[1] = (uint32_t)obj->unk_76.value;
}

/* object_set_region_count (0x140160) — XBE naked draft (batch 141). */
#if defined(__clang__)
static void *(*const b140160_get)(int, int) = object_get_and_verify_type;
static void *(*const b140160_tag)(int, int) = tag_get;
static void (*const b140160_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b140160_exitfn)(int) = system_exit;
static void * (*const b140160_c13dfc0)(int object_handle, void *reference) = object_header_block_reference_get;
static void * (*const b140160_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void object_set_region_count(int object_handle __attribute__((unused)), int16_t region_count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movw 0xb8(%%eax), %%bx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "testl $0xfe0, %%edx\n\t"
      "je .Lobject_set_region_count_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5f3\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bf80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_set_region_count_1:\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x19c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c13dfc0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal 0x198(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c13dfc0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x84(%%esi), %%edx\n\t"
      "movswl 0x86(%%esi), %%ecx\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "subl %%edx, %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .Lobject_set_region_count_2\n\t"
      "movw $0, 0x84(%%esi)\n\t"
      "movw %%ax, 0x86(%%esi)\n\t"
      ".Lobject_set_region_count_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b140160_get), [tag] "m"(b140160_tag), [assert] "m"(b140160_assert), [exitfn] "m"(b140160_exitfn), [c13dfc0] "m"(b140160_c13dfc0), [c8e0b0] "m"(b140160_c8e0b0)
      : "memory");
}
#else
#error "object_set_region_count: clang naked draft required"
#endif


/*
 * object_adjust_interpolation_position — adds a delta vector to an object's
 * interpolation position within its node/region block.
 *
 * Validates that the object type is not in the "cannot interpolate" mask
 * (bits 5-11 = 0xFE0). If the object's unk_134 (int16_t at offset 0x86)
 * is nonzero, resolves the block reference at obj+0x198 and adds the delta
 * to the position vector at offsets +0x10, +0x14, +0x18 in that block.
 *
 * Confirmed: cdecl, 2 stack args (PUSH+PUSH pattern, ADD ESP cleanup).
 * Confirmed: CALL 0x0013d680 — object_get_and_verify_type(handle, -1).
 * Confirmed: TEST EAX,0xfe0 — same _object_mask_cannot_interpolate check as
 *   object_set_region_count.
 * Confirmed: CALL 0x0008d9f0 — display_assert with line 0x60a (1546).
 * Confirmed: CALL 0x0008e2f0 — system_exit(-1).
 * Confirmed: CMP word ptr [ESI+0x86],0x0 — checks unk_134 != 0.
 * Confirmed: ADD ESI,0x198 then PUSH ESI — block reference at obj+0x198.
 * Confirmed: CALL 0x0013dfc0 — object_header_block_reference_get.
 * Confirmed: FLD/FADD/FSTP float ptr at [EAX+0x10], [EAX+0x14], [EAX+0x18].
 */
void object_adjust_interpolation_position(int object_handle, vector3_t *delta)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);

  /* Assert that this object type can be interpolated.
   * _object_mask_cannot_interpolate = 0xFE0 (bits 5 through 11). */
  if ((1 << (*(uint8_t *)((char *)obj + 0x64) & 0x1f)) & 0xfe0u) {
    display_assert(
      "!TEST_FLAG(_object_mask_cannot_interpolate, object->object.type)",
      "c:\\halo\\SOURCE\\objects\\objects.c", 0x60a, 1);
    system_exit(-1);
  }

  /* Only adjust if the object has interpolation data (unk_134 != 0). */
  if (obj->unk_134 != 0) {
    float *block = (float *)object_header_block_reference_get(
      object_handle, (char *)obj + 0x198);
    /* Add delta to the position vector at block offsets +0x10, +0x14, +0x18
     * (float indices 4, 5, 6). */
    block[4] += delta->x;
    block[5] += delta->y;
    block[6] += delta->z;
  }
}

/* object_permute_region (0x1402c0) — XBE naked draft (batch 131). */
#if defined(__clang__)
static void *(*const b1402c0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1402c0_tag)(int, int) = tag_get;
static void *(*const b1402c0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1402c0_c1dd801)(const char *a, const char *b) = crt_stricmp;

__attribute__((naked, noinline))
void object_permute_region(int object_handle __attribute__((unused)), const char *marker_name __attribute__((unused)), short region_index __attribute__((unused)), char param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_permute_region_8\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "leal 0xc4(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jle .Lobject_permute_region_8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .Lobject_permute_region_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lobject_permute_region_1:\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobject_permute_region_2\n\t"
      "cmpw %%dx, %%ax\n\t"
      "jne .Lobject_permute_region_7\n\t"
      ".Lobject_permute_region_2:\n\t"
      "pushl $0x4c\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "leal 0x40(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lobject_permute_region_7\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lobject_permute_region_3:\n\t"
      "pushl $0x58\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd801]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobject_permute_region_4\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lobject_permute_region_3\n\t"
      "jmp .Lobject_permute_region_7\n\t"
      ".Lobject_permute_region_4:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_permute_region_5\n\t"
      "movswl %%di, %%eax\n\t"
      "jmp .Lobject_permute_region_6\n\t"
      ".Lobject_permute_region_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lobject_permute_region_6:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb %%al, 0x130(%%ebx,%%ecx,1)\n\t"
      ".Lobject_permute_region_7:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .Lobject_permute_region_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lobject_permute_region_8:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1402c0_get), [tag] "m"(b1402c0_tag), [elem] "m"(b1402c0_elem), [c1dd801] "m"(b1402c0_c1dd801)
      : "memory");
}
#else
#error "object_permute_region: clang naked draft required"
#endif


/* Query an outgoing object function value (0x1403a0).
 * If function_index is -1, writes 1.0f and returns true.
 * Otherwise asserts index is in [0,4), writes the float at
 * object+0xe4+index*4 to out_value, and returns whether the
 * corresponding bit in the function-valid mask at object+0xd3 is set. */
bool object_get_function_value(int object_handle, short function_index,
                               void *out_value)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if (function_index == -1) {
    *(int *)out_value = 0x3f800000;
    return true;
  }
  if (function_index < 0 || function_index >= 4) {
    display_assert(
      "function_index>=0 && function_index<NUMBER_OF_OUTGOING_OBJECT_FUNCTIONS",
      "c:\\halo\\SOURCE\\objects\\objects.c", 0x676, 1);
    system_exit(-1);
  }
  *(int *)out_value = *(int *)(obj + 0xe4 + (int)function_index * 4);
  return (*(unsigned char *)(obj + 0xd3) &
          (1 << ((unsigned char)function_index & 0x1f))) != 0;
}

/* object_find_in_cluster (0x140420) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void (*const b140420_c13eb70)(void) = object_reset_markers;
static int (*const b140420_c191a50)(void *partition, int *state, int16_t cluster_idx) = cluster_partition_iter_first;
static void *(*const b140420_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b140420_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b140420_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b140420_exitfn)(int) = system_exit;
static int (*const b140420_c191660)(void *partition, int *state) = cluster_partition_iter_next;

__attribute__((naked, noinline))
int16_t object_find_in_cluster(int flags __attribute__((unused)), int16_t cluster_count __attribute__((unused)), int16_t *cluster_indices __attribute__((unused)), int16_t max_count __attribute__((unused)), int *out_handles __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jne .Lobject_find_in_cluster_1\n\t"
      "movl $0xffffffff, 0x8(%%ebp)\n\t"
      ".Lobject_find_in_cluster_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c13eb70]\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .Lobject_find_in_cluster_14\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jmp .Lobject_find_in_cluster_3\n\t"
      ".Lobject_find_in_cluster_2:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      ".Lobject_find_in_cluster_3:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movw (%%edx,%%eax,2), %%bx\n\t"
      "je .Lobject_find_in_cluster_8\n\t"
      "pushl %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5a8d40\n\t"
      "call *%[c191a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobject_find_in_cluster_8\n\t"
      ".Lobject_find_in_cluster_4:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "movswl 0x64(%%edi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lobject_find_in_cluster_5\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_5:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lobject_find_in_cluster_6\n\t"
      "pushl $1\n\t"
      "pushl $0xdd7\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_6:\n\t"
      "movl 0x5a8d28, %%eax\n\t"
      "cmpl %%eax, 0x8(%%edi)\n\t"
      "je .Lobject_find_in_cluster_7\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "cmpw 0x14(%%ebp), %%di\n\t"
      "jge .Lobject_find_in_cluster_16\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movswl %%di, %%ecx\n\t"
      "incl %%edi\n\t"
      "movl %%esi, (%%edx,%%ecx,4)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      ".Lobject_find_in_cluster_7:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5a8d40\n\t"
      "call *%[c191660]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .Lobject_find_in_cluster_4\n\t"
      ".Lobject_find_in_cluster_8:\n\t"
      "testb $2, 0x8(%%ebp)\n\t"
      "je .Lobject_find_in_cluster_13\n\t"
      "pushl %%ebx\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a8d30\n\t"
      "call *%[c191a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobject_find_in_cluster_13\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lobject_find_in_cluster_9:\n\t"
      "movl 0x5a8d50, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "movswl 0x64(%%edi), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lobject_find_in_cluster_10\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_10:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movb 0x1(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_find_in_cluster_11\n\t"
      "pushl $1\n\t"
      "pushl $0xdd7\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_11:\n\t"
      "movl 0x5a8d28, %%eax\n\t"
      "cmpl %%eax, 0x8(%%edi)\n\t"
      "je .Lobject_find_in_cluster_12\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "cmpw 0x14(%%ebp), %%di\n\t"
      "jge .Lobject_find_in_cluster_18\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "incl %%edi\n\t"
      "movl %%esi, (%%eax,%%edx,4)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      ".Lobject_find_in_cluster_12:\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a8d30\n\t"
      "call *%[c191660]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .Lobject_find_in_cluster_9\n\t"
      ".Lobject_find_in_cluster_13:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .Lobject_find_in_cluster_2\n\t"
      ".Lobject_find_in_cluster_14:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lobject_find_in_cluster_15\n\t"
      "pushl $1\n\t"
      "pushl $0xdba\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_15:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x1(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_find_in_cluster_16:\n\t"
      "movl 0x46f084, %%edx\n\t"
      "movb 0x1(%%edx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_find_in_cluster_17\n\t"
      "pushl $1\n\t"
      "pushl $0xdba\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_17:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movb $0, 0x1(%%eax)\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_find_in_cluster_18:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movb 0x1(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_find_in_cluster_19\n\t"
      "pushl $1\n\t"
      "pushl $0xdba\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_find_in_cluster_19:\n\t"
      "movl 0x46f084, %%edx\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x1(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c13eb70] "m"(b140420_c13eb70), [c191a50] "m"(b140420_c191a50), [dget] "m"(b140420_dget), [c8d9d0] "m"(b140420_c8d9d0), [assert] "m"(b140420_assert), [exitfn] "m"(b140420_exitfn), [c191660] "m"(b140420_c191660)
      : "memory");
}
#else
#error "object_find_in_cluster: clang naked draft required"
#endif


/*
 * object_name_list_get_handle — look up an object handle by name-table index.
 *
 * Takes a 16-bit name index, validates it is in [0, 0x200), and returns
 * the object handle stored at object_name_list[index]. Returns 0xFFFFFFFF
 * (-1) if the index is out of range.
 *
 * Confirmed: range check [0, 0x200) via TEST AX,AX / CMP AX,0x200.
 * Confirmed: MOV ECX,[0x46f07c] — loads object_name_list pointer.
 * Confirmed: MOVSX EAX,AX — sign-extends index before array access.
 * Confirmed: MOV EAX,[ECX+EAX*4] — returns name_table[index].
 * Confirmed: OR EAX,0xFFFFFFFF on out-of-range — returns -1.
 */
int object_name_list_get_handle(int16_t index)
{
  if (index >= 0 && index < 0x200) {
    int *name_table = *(int **)0x46f07c;
    return name_table[(int)index];
  }
  return 0xffffffff;
}

/* FUN_00140750 (0x140750) — XBE naked draft (batch 66). */
#if defined(__clang__)
static void (*const b140750_c1193f0)(data_t *data) = data_verify;
static void * (*const b140750_c13d730)(void *iter) = object_iterator_next;
static void (*const b140750_c13fd00)(int object_handle) = object_disconnect_from_map;
static void (*const b140750_c13c8c0)(int param_1) = FUN_0013c8c0;

__attribute__((naked, noinline))
void FUN_00140750(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1193f0]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x86868686, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "movw $0, -0xa(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00140750_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl $0x800, %%ebx\n\t"
      ".LFUN_00140750_1:\n\t"
      "testl %%ebx, 0x4(%%esi)\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "je .LFUN_00140750_2\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "jne .LFUN_00140750_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c13fd00]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "orl %%ebx, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".LFUN_00140750_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c8c0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00140750_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00140750_3:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1193f0] "m"(b140750_c1193f0), [c13d730] "m"(b140750_c13d730), [c13fd00] "m"(b140750_c13fd00), [c13c8c0] "m"(b140750_c13c8c0)
      : "memory");
}
#else
#error "FUN_00140750: clang naked draft required"
#endif


/* FUN_00141900 (0x141900) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void (*const b141900_c1193f0)(data_t *data) = data_verify;
static void * (*const b141900_c13d730)(void *iter) = object_iterator_next;
static void (*const b141900_c140bc0)(int object_handle, int delete_sibling) = object_delete_internal;

__attribute__((naked, noinline))
void FUN_00141900(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1193f0]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x86868686, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "movw $0, -0xa(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c13d730]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00141900_3\n\t"
      "jmp .LFUN_00141900_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00141900_1:\n\t"
      "testl $0x400000, 0x4(%%eax)\n\t"
      "je .LFUN_00141900_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c140bc0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00141900_2:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d730]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00141900_1\n\t"
      ".LFUN_00141900_3:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1193f0] "m"(b141900_c1193f0), [c13d730] "m"(b141900_c13d730), [c140bc0] "m"(b141900_c140bc0)
      : "memory");
}
#else
#error "FUN_00141900: clang naked draft required"
#endif


/* FUN_00141970 (0x141970) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void *(*const b141970_get)(int, int) = object_get_and_verify_type;
static void *(*const b141970_tag)(int, int) = tag_get;
static int *(*const b141970_gseed)(void) = get_global_random_seed_address;
static float (*const b141970_rmreal)(unsigned int *) = random_math_real;
static void *(*const b141970_onode)(int, short) = object_get_node_matrix;
static scenario_t * (*const b141970_c18e380)(void) = global_scenario_get;
static float (*const b141970_cb6dd0)(float a, float b) = FUN_000b6dd0;
static void (*const b141970_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b141970_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00141970(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "addl $0x108, %%eax\n\t"
      "leal 0xd4(%%edi), %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00141970_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00141970_1:\n\t"
      "movw (%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00141970_16\n\t"
      "flds 0x2533c0\n\t"
      "movswl %%ax, %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl $0x12, %%ecx\n\t"
      "ja .LFUN_00141970_12\n\t"
      "movzbl 0x141b58(%%ecx), %%edx\n\t"
      "jmp *.LFUN_00141970_jt(,%%edx,4)\n\t"
      ".LFUN_00141970_2:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x9c(%%edi)\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_3:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x98(%%edi)\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_4:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x90(%%edi)\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_5:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x94(%%edi)\n\t"
      ".LFUN_00141970_6:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00141970_15\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00141970_7:\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_8:\n\t"
      "cmpl $0x3f800000, (%%ebx)\n\t"
      "jne .LFUN_00141970_15\n\t"
      "fstp %%st(0)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_9:\n\t"
      "movb 0xb6(%%edi), %%al\n\t"
      "fstp %%st(0)\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00141970_7\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_10:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[onode]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0xc(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "fabs\n\t"
      "fcompl 0x29c128\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00141970_11\n\t"
      "flds 0x4(%%ecx)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fpatan\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x4c(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6dd0]\n\t"
      "fmuls 0x29c120\n\t"
      "addl $8, %%esp\n\t"
      "fadds 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00141970_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_11:\n\t"
      "flds (%%ebx)\n\t"
      "jmp .LFUN_00141970_15\n\t"
      ".LFUN_00141970_12:\n\t"
      "leal -0xa(%%eax), %%esi\n\t"
      "fstp %%st(0)\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00141970_13\n\t"
      "cmpw $8, %%si\n\t"
      "jl .LFUN_00141970_14\n\t"
      ".LFUN_00141970_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xa46\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29b03c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00141970_14:\n\t"
      "movswl %%si, %%edx\n\t"
      "movzbl 0x128(%%edx,%%edi,1), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fmuls 0x261518\n\t"
      ".LFUN_00141970_15:\n\t"
      "fstps (%%ebx)\n\t"
      ".LFUN_00141970_16:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $2, %%eax\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00141970_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00141970_jt:\n\t"
      ".long .LFUN_00141970_4\n\t"
      ".long .LFUN_00141970_5\n\t"
      ".long .LFUN_00141970_2\n\t"
      ".long .LFUN_00141970_3\n\t"
      ".long .LFUN_00141970_8\n\t"
      ".long .LFUN_00141970_9\n\t"
      ".long .LFUN_00141970_10\n\t"
      ".long .LFUN_00141970_12\n\t"
      ".text\n\t"
      :
      : [get] "m"(b141970_get), [tag] "m"(b141970_tag), [gseed] "m"(b141970_gseed), [rmreal] "m"(b141970_rmreal), [onode] "m"(b141970_onode), [c18e380] "m"(b141970_c18e380), [cb6dd0] "m"(b141970_cb6dd0), [assert] "m"(b141970_assert), [exitfn] "m"(b141970_exitfn)
      : "memory");
}
#else
#error "FUN_00141970: clang naked draft required"
#endif


/* FUN_00145490 (0x145490) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void (*const b145490_c144b50)(void) = objects_garbage_collect_tick;
static void (*const b145490_c11e840)(void *pool) = memory_pool_compact;

__attribute__((naked, noinline))
void FUN_00145490(void)
{
  __asm__ volatile(
      "call *%[c144b50]\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11e840]\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      :
      : [c144b50] "m"(b145490_c144b50), [c11e840] "m"(b145490_c11e840)
      : "memory");
}
#else
#error "FUN_00145490: clang naked draft required"
#endif


/*
 * object_get_first_cluster (0x13fe10 / objects.obj) — begin iterating the cluster
 * set that an object belongs to; returns the first cluster's marker (or NONE).
 *
 * Resolves the object's root parent (object_get_root_parent), then selects the
 * cluster-partition table based on the root object's flags: table 0x5a8d40 when
 * flag bit 0x2000000 is set, otherwise 0x5a8d30. Stores the table pointer in
 * iter_state[0] and initializes the cluster iterator via FUN_00191690, seeding it
 * with the root object's cluster reference (root_object+0xbc) and writing the
 * iterator state into iter_state[1]. Returns FUN_00191690's first cluster marker.
 *
 * Read-only with respect to object lifecycle: writes only the caller's 8-byte
 * iter_state buffer ([0] table ptr, [4] cluster iterator state). Paired with
 * FUN_0013d5f0 (cluster-next) on the same iter_state.
 *
 * Confirmed: 2 cdecl args (iter_state @ [EBP+0x8] ESI, object_handle @ [EBP+0xc]).
 * Confirmed: object_get_root_parent(object_handle) result reused for both
 * object_get_and_verify_type(root, -1) calls (flags read +0x4, cluster ref +0xbc).
 * Confirmed: returns FUN_00191690's EAX (first cluster marker, int16_t in callers).
 */
int16_t object_get_first_cluster(void *iter_state, int object_handle)
{
  unsigned int **iter = (unsigned int **)iter_state;
  int root;
  int root_obj;
  unsigned int *table;

  root = object_get_root_parent(object_handle);
  root_obj = (int)object_get_and_verify_type(root, -1);
  table = (unsigned int *)0x5a8d40;
  if ((*(unsigned int *)(root_obj + 4) & 0x2000000) == 0) {
    table = (unsigned int *)0x5a8d30;
  }
  iter[0] = table;
  root_obj = (int)object_get_and_verify_type(root, -1);
  return (int16_t)FUN_00191690(iter[0], (int *)(iter + 1),
                               *(int *)(root_obj + 0xbc));
}

/* object_visible_to_any_player (0x1407e0) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void *(*const b1407e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1407e0_get)(int, int) = object_get_and_verify_type;
static void * (*const b1407e0_cba6c0)(void) = players_get_combined_pvs;
static int16_t (*const b1407e0_c13fe10)(void *iter_state, int object_handle) = object_get_first_cluster;
static int16_t (*const b1407e0_c13d5f0)(void *param_1, int param_2) = FUN_0013d5f0;
static int (*const b1407e0_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void (*const b1407e0_c1a9200)(int object_handle, float *out_position) = unit_get_head_position;
static float (*const b1407e0_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
int object_visible_to_any_player(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%al\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .Lobject_visible_to_any_player_6\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .Lobject_visible_to_any_player_6\n\t"
      "testl $0x200000, %%eax\n\t"
      "jne .Lobject_visible_to_any_player_6\n\t"
      "call *%[cba6c0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c13fe10]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobject_visible_to_any_player_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobject_visible_to_any_player_1:\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "sarl $5, %%edx\n\t"
      "testl %%ebx, (%%ecx,%%edx,4)\n\t"
      "jne .Lobject_visible_to_any_player_2\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d5f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lobject_visible_to_any_player_1\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_visible_to_any_player_2:\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobject_visible_to_any_player_6\n\t"
      "flds 0x5c(%%esi)\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "fld %%st(0)\n\t"
      "pushl $-1\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "pushl %%eax\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lobject_visible_to_any_player_6\n\t"
      ".Lobject_visible_to_any_player_3:\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_visible_to_any_player_4\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9200]\n\t"
      "flds 0x50(%%esi)\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x54(%%esi)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jnp .Lobject_visible_to_any_player_5\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "flds 0x50(%%esi)\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x54(%%esi)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fstpl -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fldl -0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "addl $0xc, %%esp\n\t"
      "fpatan\n\t"
      "fadds 0x254a58\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x1e8(%%edi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x1e4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x1e0(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fcos\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_visible_to_any_player_5\n\t"
      ".Lobject_visible_to_any_player_4:\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lobject_visible_to_any_player_3\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_visible_to_any_player_5:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lobject_visible_to_any_player_6:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1407e0_dget), [get] "m"(b1407e0_get), [cba6c0] "m"(b1407e0_cba6c0), [c13fe10] "m"(b1407e0_c13fe10), [c13d5f0] "m"(b1407e0_c13d5f0), [c1198f0] "m"(b1407e0_c1198f0), [c1a9200] "m"(b1407e0_c1a9200), [norm] "m"(b1407e0_norm)
      : "memory");
}
#else
#error "object_visible_to_any_player: clang naked draft required"
#endif


void object_pvs_activate(int param_1)
{
  int iVar1;

  iVar1 = *(int *)0x46f084;
  if (param_1 == -1) {
    *(short *)(iVar1 + 0x90) = 0;
    return;
  }
  *(short *)(iVar1 + 0x90) = 1;
  *(int *)(iVar1 + 0x94) = param_1;
}

void objects_scripting_set_scale(int param_1, int param_2, int16_t param_3)
{
  int iVar1;
  unsigned char cl;

  if (param_1 != -1) {
    iVar1 = (int)object_get_and_verify_type(param_1, 0xffffffff);
    *(int *)(iVar1 + 0x60) = param_2;
    cl = *(unsigned char *)(iVar1 + 0x64);
    if ((((unsigned int)1 << cl) & 0xfe0) == 0) {
      object_set_region_count(param_1, param_3);
    }
  }
}

/* object_delete_internal (0x140bc0) — XBE naked draft (batch 131). */
#if defined(__clang__)
static void *(*const b140bc0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b140bc0_get)(int, int) = object_get_and_verify_type;
static bool (*const b140bc0_gerun)(void) = game_engine_running;
static bool (*const b140bc0_cfb0c0)(int object_index) = weapon_is_flag;
static void (*const b140bc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b140bc0_exitfn)(int) = system_exit;
static void (*const b140bc0_c140bc0)(int object_handle, int delete_sibling) = object_delete_internal;
static void *(*const b140bc0_tag)(int, int) = tag_get;
static void (*const b140bc0_c13ee60)(int object_handle, char do_wake, char do_limbo) = object_propagate_flag_to_children;
static void (*const b140bc0_c13eff0)(int object_handle) = object_remove_from_name_list;

__attribute__((naked, noinline))
void object_delete_internal(int object_handle __attribute__((unused)), int delete_sibling __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[get]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_delete_internal_1\n\t"
      "cmpw $2, 0x64(%%esi)\n\t"
      "jne .Lobject_delete_internal_1\n\t"
      "pushl %%edi\n\t"
      "call *%[cfb0c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_delete_internal_1\n\t"
      "pushl $1\n\t"
      "pushl $0x33d\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c010\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_delete_internal_1:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_delete_internal_2\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c140bc0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_delete_internal_2:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_delete_internal_3\n\t"
      "movl 0xc4(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobject_delete_internal_3\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c140bc0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_delete_internal_3:\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "orb $8, %%al\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "movb %%al, 0x2(%%ebx)\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lobject_delete_internal_4\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .Lobject_delete_internal_4\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13ee60]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_delete_internal_4:\n\t"
      "movl 0x5a8d50, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "orl $1, 0x4(%%esi)\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "andb $0xfd, %%cl\n\t"
      "addl $8, %%esp\n\t"
      "movb %%cl, 0x2(%%eax)\n\t"
      "call *%[c13eff0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b140bc0_dget), [get] "m"(b140bc0_get), [gerun] "m"(b140bc0_gerun), [cfb0c0] "m"(b140bc0_cfb0c0), [assert] "m"(b140bc0_assert), [exitfn] "m"(b140bc0_exitfn), [c140bc0] "m"(b140bc0_c140bc0), [tag] "m"(b140bc0_tag), [c13ee60] "m"(b140bc0_c13ee60), [c13eff0] "m"(b140bc0_c13eff0)
      : "memory");
}
#else
#error "object_delete_internal: clang naked draft required"
#endif


/*
 * object_delete — delete an object from the world.
 *
 * Thin wrapper around object_delete_internal with delete_sibling=0,
 * meaning only the target object and its children are deleted, not
 * its siblings in the object list.
 *
 * Confirmed: PUSH 0x0 / PUSH EAX / CALL 0x140bc0 / ADD ESP,0x8 — 2 cdecl args.
 */
void object_delete(int object_handle)
{
  object_delete_internal(object_handle, 0);
}

/* object_connect_to_map (0x140ce0) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void *(*const b140ce0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b140ce0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b140ce0_exitfn)(int) = system_exit;
static void *(*const b140ce0_get)(int, int) = object_get_and_verify_type;
static void (*const b140ce0_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void (*const b140ce0_c1917a0)(void *partition, int object_handle, void *first_cluster_ref, void *position, uint32_t radius_fp, void *location) = cluster_partition_add_object;
static void * (*const b140ce0_cba6c0)(void) = players_get_combined_pvs;
static void (*const b140ce0_c13fb30)(int object_handle) = object_activate;
static void (*const b140ce0_c140bc0)(int object_handle, int delete_sibling) = object_delete_internal;

__attribute__((naked, noinline))
void object_connect_to_map(int object_handle __attribute__((unused)), void *location __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "testl $0xffff0000, %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%edi), %%esi\n\t"
      "jne .Lobject_connect_to_map_1\n\t"
      "pushl $1\n\t"
      "pushl $0x36f\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bf58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_connect_to_map_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .Lobject_connect_to_map_2\n\t"
      "pushl $1\n\t"
      "pushl $0x370\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c030\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_connect_to_map_2:\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_connect_to_map_3\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc8, %%ebx\n\t"
      "call *%[get]\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, 0xc4(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "orb $0x80, %%al\n\t"
      "movb %%al, 0x2(%%edi)\n\t"
      "movw $0xffff, 0x4c(%%esi)\n\t"
      "jmp .Lobject_connect_to_map_10\n\t"
      ".Lobject_connect_to_map_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lobject_connect_to_map_4\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18f180]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, -0x4(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%ebx\n\t"
      "jne .Lobject_connect_to_map_4\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18f180]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_connect_to_map_4:\n\t"
      "cmpw $-1, 0x4(%%ebx)\n\t"
      "je .Lobject_connect_to_map_5\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, 0x48(%%esi)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movw %%ax, %%cx\n\t"
      "movl %%eax, 0x4c(%%esi)\n\t"
      "movw %%cx, 0x4(%%edi)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0xffdfffff, %%eax\n\t"
      "jmp .Lobject_connect_to_map_6\n\t"
      ".Lobject_connect_to_map_5:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "orl $0x200000, %%eax\n\t"
      ".Lobject_connect_to_map_6:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movb 0x2(%%edi), %%dl\n\t"
      "andb $0x7f, %%dl\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movb %%dl, 0x2(%%edi)\n\t"
      "call *%[get]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x2000000, %%ecx\n\t"
      "movl $0x5a8d40, %%eax\n\t"
      "jne .Lobject_connect_to_map_7\n\t"
      "movl $0x5a8d30, %%eax\n\t"
      ".Lobject_connect_to_map_7:\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "leal 0x48(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x50(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0xbc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1917a0]\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $0x40, %%al\n\t"
      "je .Lobject_connect_to_map_10\n\t"
      "cmpw $-1, 0x4(%%edi)\n\t"
      "je .Lobject_connect_to_map_9\n\t"
      "movswl 0x4(%%edi), %%ebx\n\t"
      "call *%[cba6c0]\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "sarl $5, %%edx\n\t"
      "testl %%ebx, (%%eax,%%edx,4)\n\t"
      "je .Lobject_connect_to_map_8\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13fb30]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lobject_connect_to_map_10\n\t"
      ".Lobject_connect_to_map_8:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Lobject_connect_to_map_9:\n\t"
      "testl $0x80000, 0x4(%%esi)\n\t"
      "je .Lobject_connect_to_map_10\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c140bc0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_connect_to_map_10:\n\t"
      "orl $0x800, 0x4(%%esi)\n\t"
      "orb $0x20, 0x2(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b140ce0_dget), [assert] "m"(b140ce0_assert), [exitfn] "m"(b140ce0_exitfn), [get] "m"(b140ce0_get), [c18f180] "m"(b140ce0_c18f180), [c1917a0] "m"(b140ce0_c1917a0), [cba6c0] "m"(b140ce0_cba6c0), [c13fb30] "m"(b140ce0_c13fb30), [c140bc0] "m"(b140ce0_c140bc0)
      : "memory");
}
#else
#error "object_connect_to_map: clang naked draft required"
#endif


/*
 * object_get_node_matrix — return a pointer to a specific node's 4x3 matrix
 * within the object's node matrix block.
 *
 * Asserts that the object actually has the requested node via object_has_node.
 * Resolves the node matrix block reference at object+0x1A0, then indexes into
 * it by node_index * 0x34 (52 bytes per node matrix).
 *
 * Confirmed: CALL 0x13fef0 (object_has_node) with 2 stack args, TEST AL,AL.
 * Confirmed: assert string "object_has_node(object_index, node_index)" at
 *            0x29c070, file "c:\halo\SOURCE\objects\objects.c" at 0x29b91c,
 *            line 0x424.
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with PUSH -1.
 * Confirmed: ADD EAX,0x1A0 — node matrix block reference offset.
 * Confirmed: CALL 0x13dfc0 (object_header_block_reference_get).
 * Confirmed: MOVSX ECX,DI / IMUL ECX,ECX,0x34 — sign-extended int16_t index
 *            multiplied by 52.
 * Confirmed: ADD EAX,ECX — final pointer = base + node_index * 0x34.
 */
void *object_get_node_matrix(int object_handle, int16_t node_index)
{
  object_data_t *obj;
  char *nodes;

  if (!object_has_node(object_handle, node_index)) {
    display_assert("object_has_node(object_index, node_index)",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x424, 1);
    system_exit(-1);
  }
  obj = (object_data_t *)object_get_and_verify_type(object_handle, -1);
  nodes = (char *)object_header_block_reference_get(object_handle,
                                                    (void *)&obj->unk_416);
  return nodes + (int)node_index * 0x34;
}

/*
 * object_get_markers_by_string_id — find markers on an object by name string,
 * returning a count of matched markers.
 *
 * Delegates to model_find_markers (0x124730) which searches the object's
 * animation graph tag for markers matching marker_name. If no markers are
 * found and marker_name is NULL or empty, fills out_markers[0] with a default
 * identity transform and the node-0 matrix, returning 1.
 *
 * When sVar1 == 0 (no markers found from the model search):
 *   - Asserts max_count > 0
 *   - Zeros the node_index at out_markers[0]+0x00
 *   - Initializes a 52-byte identity transform at out_markers[0]+0x04
 *   - Copies the 52-byte node-0 matrix into out_markers[0]+0x38
 *   - If the object has the 0x1000 flag (mirrored), negates the second row
 *     of the node matrix (offsets +0x48, +0x4C, +0x50 in the marker)
 *   - Returns 1 if marker_name is non-NULL and points to an empty string
 *
 * Confirmed: PUSH -1 / PUSH ESI / CALL 0x13d680 — object_get_and_verify_type.
 * Confirmed: PUSH 0x6f626a65 — tag_get('obje', ...).
 * Confirmed: LEA EDX,[EBX+0x130] — object nodes (unk_304) passed to model
 * search. Confirmed: ADD EAX,0x1A0 — node matrix block reference at
 * object+0x1A0. Confirmed: SHR ECX,0xC / AND ECX,0xFFFFFF01 — flag extraction
 * from obj->flags. Confirmed: REP MOVSD with ECX=0xD — copies 52-byte node
 * matrix (0x34 bytes). Confirmed: TEST AH,0x10 — checks flags bit 12 (0x1000)
 * for mirroring. Confirmed: FCHS on floats at [EAX+0x48], [EAX+0x4C],
 * [EAX+0x50]. Confirmed: ADD ESP,0x44 — cleans all 17 dwords across 5 cdecl
 * calls.
 */
int16_t object_get_markers_by_string_id(int object_handle, void *marker_name,
                                        void *out_markers, int max_count)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);
  void *tag_data = tag_get(0x6f626a65, obj->tag_index);
  object_data_t *obj2 =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);
  void *node_matrices =
    object_header_block_reference_get(object_handle, (char *)obj2 + 0x1a0);

  /* model_find_markers (0x124730): search animation graph for named markers.
   * 9 args: anim_graph_data, marker_name, object_nodes, zero, -1,
   *         node_matrices, flags, out_markers, max_count */
  uint32_t mirror_flags = (obj->flags >> 12) & 0xffffff01;
  int16_t result = ((int16_t(*)(int, void *, void *, int, int, void *, uint32_t,
                                void *, int))0x124730)(
    *(int *)((char *)tag_data + 0x34), marker_name, (char *)obj + 0x130, 0, -1,
    node_matrices, mirror_flags, out_markers, max_count);

  if (result != 0)
    return result;

  /* No markers found — fill in a default marker if possible. */
  if ((int16_t)max_count < 1) {
    display_assert("maximum_marker_count>0",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x459, 1);
    system_exit(-1);
  }

  /* Zero the node index (int16_t at offset 0x00). */
  *(int16_t *)out_markers = 0;

  /* Initialize identity transform at out_markers+0x04 (52 bytes). */
  ((void (*)(void *))0x1090e0)((char *)out_markers + 4);

  /* Copy node-0 matrix (52 bytes / 13 dwords) into out_markers+0x38. */
  {
    void *node_mat = object_get_node_matrix(object_handle, 0);
    qmemcpy((char *)out_markers + 0x38, node_mat, 0x34);
  }

  /* If the object is mirrored (flags bit 12), negate the second row of the
   * node matrix within the marker result (offsets +0x48, +0x4C, +0x50). */
  if ((obj->flags & 0x1000) != 0) {
    *(float *)((char *)out_markers + 0x48) =
      -*(float *)((char *)out_markers + 0x48);
    *(float *)((char *)out_markers + 0x4c) =
      -*(float *)((char *)out_markers + 0x4c);
    *(float *)((char *)out_markers + 0x50) =
      -*(float *)((char *)out_markers + 0x50);
  }

  /* If marker_name is non-NULL and points to an empty string, return 1. */
  if (marker_name != NULL && *(char *)marker_name == '\0')
    return 1;

  return 0;
}

/*
 * object_compute_child_marker_position — given an object pointer, a child
 * marker (containing a matrix4x3 at offset 0x38), and a destination matrix,
 * computes the child marker's position relative to the object and writes the
 * resulting position, forward, and up vectors back into the object.
 *
 * Algorithm:
 *   1. Build a matrix4x3 from the object's forward, up, position vectors.
 *   2. Invert it.
 *   3. Multiply the inverted matrix by the child marker's matrix (at +0x38).
 *   4. Invert the result.
 *   5. Multiply destination_matrix by the inverted result.
 *   6. Extract position, forward, and up from the product back to the object.
 *   7. Re-orthogonalize up via cross(cross(forward, up), forward).
 *   8. Normalize forward and up.
 *
 * Confirmed: 3 cdecl args (object, child_marker, destination_matrix).
 * Confirmed: void return — no caller checks EAX.
 * Confirmed: assert strings match "object", "child_marker",
 *            "destination_matrix", "valid_real_matrix4x3(destination_matrix)".
 * Confirmed: source file "c:\\halo\\SOURCE\\objects\\objects.c", lines
 * 0x495–0x499. Confirmed: CALL 0x10a110 (matrix4x3_from_forward_up_position).
 * Confirmed: CALL 0x109150 (matrix_inverse) x2.
 * Confirmed: CALL 0x109850 (matrix4x3_multiply) x2.
 * Confirmed: CALL 0x13010  (normalize3d) x2.
 * Confirmed: CALL 0xf6d00  (valid_real_matrix4x3) for dest_matrix assertion.
 * Confirmed: ADD ESP,0x40 cleans all 16 cdecl arg dwords at once.
 */
void object_compute_child_marker_position(void *object, void *child_marker,
                                          void *dest_matrix)
{
  typedef void (*matrix4x3_from_fup_fn)(void *out, float *pos, float *fwd,
                                        float *up);
  typedef void (*matrix_inverse_fn)(void *src, void *dst);
  typedef void (*matrix4x3_multiply_fn)(void *out, void *a, void *b);
  typedef int (*valid_real_matrix4x3_fn)(void *mat);

  float local_mat[13]; /* 0x34 bytes: scale + forward + left + up + position */
  float inv_mat[13]; /* 0x34 bytes */
  float *obj_position;
  float *obj_forward;
  float *obj_up;
  float fwd_x, fwd_y, fwd_z;
  float up_x, up_y, up_z;
  float left_x, left_y, left_z;

  assert_halt(object != NULL);
  assert_halt(child_marker != NULL);
  assert_halt(dest_matrix != NULL);
  assert_halt(((valid_real_matrix4x3_fn)0xf6d00)(dest_matrix));

  obj_position = (float *)((char *)object + 0xc);
  obj_forward = (float *)((char *)object + 0x24);
  obj_up = (float *)((char *)object + 0x30);

  /* Build a matrix4x3 from the object's orientation and position */
  ((matrix4x3_from_fup_fn)0x10a110)(local_mat, obj_position, obj_forward,
                                    obj_up);

  /* Invert it */
  ((matrix_inverse_fn)0x109150)(local_mat, inv_mat);

  /* Multiply by the child marker's matrix at offset 0x38 */
  ((matrix4x3_multiply_fn)0x109850)(inv_mat, (char *)child_marker + 0x38,
                                    inv_mat);

  /* Invert the result */
  ((matrix_inverse_fn)0x109150)(inv_mat, inv_mat);

  /* Multiply dest_matrix by the inverted result, storing in local_mat */
  ((matrix4x3_multiply_fn)0x109850)(dest_matrix, inv_mat, local_mat);

  /* Extract position back to object (offsets 0x28..0x30 in matrix = indices
   * 10..12) */
  obj_position[0] = local_mat[10];
  obj_position[1] = local_mat[11];
  obj_position[2] = local_mat[12];

  /* Extract forward back to object (offsets 0x04..0x0c in matrix = indices
   * 1..3) */
  obj_forward[0] = local_mat[1];
  obj_forward[1] = local_mat[2];
  obj_forward[2] = local_mat[3];

  /* Re-orthogonalize up: left = cross(forward, up_from_matrix),
   * then up = cross(left, forward).
   * up_from_matrix is at indices 7..9 (offsets 0x1c..0x24). */
  fwd_x = local_mat[1];
  fwd_y = local_mat[2];
  fwd_z = local_mat[3];
  up_x = local_mat[7];
  up_y = local_mat[8];
  up_z = local_mat[9];

  /* left = cross(forward, up) */
  left_x = fwd_y * up_z - fwd_z * up_y;
  left_y = fwd_z * up_x - up_z * fwd_x;
  left_z = up_y * fwd_x - fwd_y * up_x;

  /* up_new = cross(left, forward) */
  obj_up[0] = left_y * fwd_z - left_z * fwd_y;
  obj_up[1] = left_z * fwd_x - fwd_z * left_x;
  obj_up[2] = fwd_y * left_x - left_y * fwd_x;

  normalize3d(obj_forward);
  normalize3d(obj_up);
}

/*
 * object_detach_from_parent — detach an object from its parent in the
 * object hierarchy.
 *
 * Retrieves both the child and parent object data, disconnects the child
 * from the map, then re-computes its orientation in world space using the
 * parent's node matrix.  After updating position/orientation/up vectors from
 * the parent, clears the node index (0xFF) and parent handle (-1), then
 * reconnects to the map.
 *
 * Finally, sets the "connected to cluster" flag (bit 0 of header+0x02) if
 * the object is not already connected, doesn't have the 0x100000 flag, and
 * has no parent.
 *
 * Confirmed: object_get_and_verify_type(handle, -1) for both child and parent.
 * Confirmed: object_disconnect_from_map(handle), then recompute world matrix
 *            via object_get_node_matrix(parent_handle, node_index).
 * Confirmed: matrix4x3_identity_with_position, matrix_from_forward_and_up,
 *            matrix4x3_multiply used to transform orientation.
 * Confirmed: Copies 3 floats at +0x18, +0x1C, +0x20 and +0x3C, +0x40, +0x44
 *            from parent to child.
 * Confirmed: Sets node_index (byte at +0xD0) = 0xFF, parent (int at +0xCC) =
 * -1. Confirmed: datum_get + flag check on header+0x02 bit 0, object+0x04 &
 * 0x100000, object+0xCC == -1 to set connected flag.
 */
void object_detach_from_parent(int object_handle)
{
  object_data_t *child;
  object_data_t *parent;
  void *node_matrix;
  float child_position[13];
  float child_orientation[13];
  float result[13];
  object_header_data_t *header;

  child = (object_data_t *)object_get_and_verify_type(object_handle, -1);
  parent = (object_data_t *)object_get_and_verify_type(
    child->parent_object_index.value, -1);

  object_disconnect_from_map(object_handle);

  node_matrix =
    object_get_node_matrix(child->parent_object_index.value,
                           (int16_t) * (int8_t *)((char *)child + 0xd0));

  matrix4x3_identity_with_position(child_position, (float *)&child->unk_12);
  matrix_from_forward_and_up(child_orientation, (float *)&child->unk_36,
                             (float *)&child->unk_48);
  matrix4x3_multiply((float *)node_matrix, child_position, result);
  matrix4x3_multiply(result, child_orientation, result); /* dup-args-ok */
  matrix4x3_decompose(result, (float *)&child->unk_12, (float *)&child->unk_36,
                      (float *)&child->unk_48);

  child->unk_24 = parent->unk_24;
  child->unk_60 = parent->unk_60;

  *(int8_t *)((char *)child + 0xd0) = -1;
  child->parent_object_index.value = NONE;

  object_connect_to_map(object_handle, NULL);

  header =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  child = (object_data_t *)object_get_and_verify_type(object_handle, -1);
  if (!(header->unk_2 & 1) && !(child->flags & 0x100000) &&
      child->parent_object_index.value == NONE) {
    header->unk_2 |= 1;
  }
}

/*
 * object_get_world_position — retrieve the world-space position of an object.
 *
 * If the object has no parent (parent_object_index == -1), copies the local
 * position vector (obj+0x0C) directly to out_position.
 *
 * If the object is attached to a parent, retrieves the parent's node matrix
 * via object_get_node_matrix (using the sign-extended node index byte at
 * obj+0xD0) and transforms the local position through that matrix via
 * matrix_transform_point.
 *
 * Confirmed: PUSH -1, PUSH EAX — object_get_and_verify_type(handle, -1).
 * Confirmed: CMP EAX,-1 — checks parent_object_index at obj+0xCC.
 * Confirmed: MOVSX CX, byte ptr [ESI+0xD0] — sign-extends node index byte.
 * Confirmed: ADD ESP,0x14 cleans 5 args (2 + 3 from two cdecl calls).
 * Confirmed: MOV EAX, EDI — returns out_position pointer.
 */
vector3_t *object_get_world_position(int object_handle, vector3_t *out_position)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);
  void *node_mat;

  if (obj->parent_object_index.value == NONE) {
    /* No parent — local position is the world position */
    *out_position = obj->unk_12;
    return out_position;
  }

  /* Parented — transform local position through parent's node matrix */
  node_mat = object_get_node_matrix(obj->parent_object_index.value,
                                    (int16_t) * (int8_t *)((char *)obj + 0xd0));
  matrix_transform_point((float *)node_mat, (float *)&obj->unk_12,
                         (float *)out_position);
  return out_position;
}

/*
 * object_get_orientation — get an object's forward and/or up orientation
 * vectors in world space.
 *
 * If the object has no parent (parent_object_index == -1), copies the local
 * forward (obj+0x24) and up (obj+0x30) vectors directly.
 * If parented, transforms both vectors through the parent's node matrix via
 * matrix_transform_vector (0x109680).
 *
 * When both out_forward and out_up are provided, validates that they form
 * perpendicular unit axes via valid_real_normal3d_perpendicular (0x84a70).
 *
 * Confirmed: 3 cdecl args at [EBP+0x8..0x10].
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (handle, -1).
 * Confirmed: CALL 0x140eb0 (object_get_node_matrix) with (parent_handle,
 *            sign-extended byte at obj+0xD0).
 * Confirmed: CALL 0x109680 (matrix_transform_vector) with (node_matrix,
 *            src_vector, out_vector) — 3 cdecl args each call.
 * Confirmed: CALL 0x84a70 (valid_real_normal3d_perpendicular) with
 *            (out_forward, out_up).
 * Confirmed: Assertion at line 0x5b6, strings "forward" (0x28cb2c) and
 *            "up" (0x28cb28), format at 0x267490.
 */
/* 0x141360 */
void object_get_orientation(int object_handle, float *out_forward,
                            float *out_up)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);

  if (obj->parent_object_index.value == NONE) {
    /* No parent — copy local forward and up vectors directly */
    if (out_forward != NULL) {
      out_forward[0] = ((float *)&obj->unk_36)[0];
      out_forward[1] = ((float *)&obj->unk_36)[1];
      out_forward[2] = ((float *)&obj->unk_36)[2];
    }
    if (out_up != NULL) {
      out_up[0] = ((float *)&obj->unk_48)[0];
      out_up[1] = ((float *)&obj->unk_48)[1];
      out_up[2] = ((float *)&obj->unk_48)[2];
    }
  } else {
    /* Parented — transform through parent's node matrix */
    void *node_mat =
      object_get_node_matrix(obj->parent_object_index.value,
                             (int16_t) * (int8_t *)((char *)obj + 0xd0));

    if (out_forward != NULL) {
      matrix_transform_vector((float *)node_mat, (float *)&obj->unk_36,
                              out_forward);
    }
    if (out_up != NULL) {
      matrix_transform_vector((float *)node_mat, (float *)&obj->unk_48, out_up);
    }
  }

  /* Validate perpendicularity if both vectors were requested */
  if (out_forward != NULL && out_up != NULL) {
    if (!valid_real_normal3d_perpendicular(out_forward, out_up)) {
      char *msg = csprintf(
        (char *)0x5ab100,
        "%s, %s: assert_valid_real_vector3d_axes2(%f, %f, %f / %f, %f, %f)",
        "forward", "up", (double)out_forward[0], (double)out_forward[1],
        (double)out_forward[2], (double)out_up[0], (double)out_up[1],
        (double)out_up[2]);
      display_assert(msg, "c:\\halo\\SOURCE\\objects\\objects.c", 0x5b6, 1);
      system_exit(-1);
    }
  }
}

/*
 * object_get_world_matrix — build a 4x3 world-space matrix for an object.
 *
 * Constructs the matrix from the object's position (obj+0xc), forward
 * vector (obj+0x24), and up vector (obj+0x30) via matrix4x3_from_forward_up_position (which
 * calls matrix_from_forward_and_up then copies position to offset 0x28).
 *
 * If the object has a parent (parent_object_index at obj+0xcc != -1),
 * retrieves the parent's node matrix via object_get_node_matrix (using the node
 * index byte at obj+0xd0) and multiplies it with the local matrix via
 * matrix4x3_multiply (matrix_multiply), storing the result in-place.
 *
 * Confirmed: PUSH -1, PUSH EAX — object_get_and_verify_type(handle, -1).
 * Confirmed: ADD ESP,0x18 cleans 6 args (2 + 4 from two cdecl calls).
 * Confirmed: MOVSX CX, byte ptr [ESI+0xd0] — sign-extends node index.
 * Confirmed: ADD ESP,0x14 cleans 5 args (2 + 3 from two cdecl calls).
 * Confirmed: MOV EAX, EDI — returns out_matrix pointer.
 */
void *object_get_world_matrix(int object_handle, void *out_matrix)
{
  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(object_handle, -1);

  /* Build local matrix from position, forward, up */
  ((void (*)(void *, float *, float *, float *))0x10a110)(
    out_matrix, (float *)((char *)obj + 0xc), (float *)((char *)obj + 0x24),
    (float *)((char *)obj + 0x30));

  /* If parented, multiply by parent's node matrix */
  if (obj->parent_object_index.value != NONE) {
    void *node_mat =
      object_get_node_matrix(obj->parent_object_index.value,
                             (int16_t) * (int8_t *)((char *)obj + 0xd0));
    matrix4x3_multiply((float *)node_mat, (float *)out_matrix,
                       (float *)out_matrix); /* dup-args-ok */
  }

  return out_matrix;
}

/*
 * object_find_in_radius — find objects of a given type within a spherical area.
 *
 * Uses the structure system to identify candidate clusters, then iterates
 * through objects in those clusters, filtering by type_mask and distance.
 * Objects within (obj_effective_radius + search_radius) of the search position
 * are collected into out_handles.  Returns the count of found objects.
 *
 * Parameters (cdecl, 7 args):
 *   flags            — passed to object_find_in_cluster
 *   type_mask        — bit mask of object types to include (0 → all types)
 *   cluster_info     — pointer to a cluster location struct; word at +4 is
 *                       the cluster count passed to structure_find_in_cluster
 *   position         — float[3] search center (must be non-NULL)
 *   radius           — search radius, added to each object's effective radius
 *   out_handles      — output array for found object handles (must be non-NULL)
 *   max_count        — maximum number of handles to collect
 *
 * Confirmed: 7 cdecl params at [EBP+0x8..0x20].
 * Confirmed: param_3 (EBX) is a struct pointer, word at +4 = cluster count.
 * Confirmed: param_4 (ESI) is the float* position, used in distance math.
 * Confirmed: CALL 0x199230 with 5 args: (cluster_count_word, position, radius,
 *            0x200, cluster_indices_ptr).
 * Confirmed: CALL 0x140420 with 5 args: (flags, cluster_count, cluster_indices,
 *            0x800, object_indices_ptr). Max counts are hardcoded 512 and 2048.
 * Confirmed: Distance check uses obj+0x50/0x54/0x58 vs position, and
 *            obj+0x5C as effective object radius.
 * Confirmed: Returns short (count of found objects).
 * Confirmed: Only type_mask gets the 0 → -1 treatment; flags is NOT checked.
 * Confirmed: Assert strings: "location" (0x29c114), "center" (0x253f0c),
 *            "object_indices" (0x29c104) at lines 0x6f3, 0x6f4, 0x6f5.
 * Confirmed: Inner assert uses csprintf with full format at 0x29b940:
 *            "got an object type we didn't expect (expected one of 0x%08x
 *             but got #%d)." with args (-1, type).
 * Confirmed: Loop iterator i is int16_t (BX register, CMP BX).
 */
/* 0x1415f0 */
int16_t object_find_in_radius(int flags, unsigned int type_mask,
                              void *cluster_info, float *position, float radius,
                              int *out_handles, int16_t max_count)
{
  int16_t found_count = 0;
  int16_t iter_count;
  int16_t i;

  static int16_t cluster_indices[512];
  static int object_indices[2048];

  if (cluster_info == NULL) {
    display_assert("location", "c:\\halo\\SOURCE\\objects\\objects.c", 0x6f3,
                   1);
    system_exit(-1);
  }
  if (position == NULL) {
    display_assert("center", "c:\\halo\\SOURCE\\objects\\objects.c", 0x6f4, 1);
    system_exit(-1);
  }
  if (out_handles == NULL) {
    display_assert("object_indices", "c:\\halo\\SOURCE\\objects\\objects.c",
                   0x6f5, 1);
    system_exit(-1);
  }

  if (type_mask == 0)
    type_mask = 0xFFFFFFFF;

  iter_count =
    structure_find_in_cluster(*(uint16_t *)((char *)cluster_info + 4), position,
                              radius, 512, cluster_indices);

  iter_count = object_find_in_cluster(flags, iter_count, cluster_indices, 2048,
                                      object_indices);

  for (i = 0; i < iter_count && found_count < max_count; i++) {
    int handle = object_indices[i];
    object_header_data_t *header =
      (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, handle);
    object_data_t *obj = header->object;

    if ((1 << ((uint8_t)obj->type & 0x1f)) == 0) {
      char *msg = csprintf((char *)0x5ab100,
                           "got an object type we didn't expect "
                           "(expected one of 0x%08x but got #%d).",
                           (int)-1, (int)obj->type);
      display_assert(msg, "c:\\halo\\SOURCE\\objects\\objects.c", 0x69a, 1);
      system_exit(-1);
    }

    if ((type_mask & (1 << ((uint8_t)obj->type & 0x1f))) != 0) {
      float dx = obj->unk_80 - position[0];
      float dy = obj->unk_84 - position[1];
      float dz = obj->unk_88 - position[2];
      float effective_radius = obj->unk_92 + radius;

      if (dx * dx + dy * dy + dz * dz <= effective_radius * effective_radius) {
        out_handles[found_count] = handle;
        found_count++;
      }
    }
  }

  return found_count;
}

/* Type-cast helpers for object_compute_node_matrices — kept at file scope for
 * C89 compliance */
typedef void (*animation_set_default_fn)(void *model_tag, void *anim_data);
typedef void (*animation_decode_fn)(void *model_tag, void *anim_entry,
                                    int frame_index, void *anim_data);
typedef void (*animation_overlay_keyframe_fn)(void *anim_entry,
                                              float frame_value,
                                              void *anim_data);
typedef void (*animation_overlay_interpolate_fn)(void *anim_entry,
                                                 int frame_index,
                                                 void *anim_data,
                                                 void *node_data);
typedef void (*overlay_adjust_fn)(int object_handle, void *anim_data);
typedef void (*anim_interpolate_fn)(uint16_t node_count, void *interp_data,
                                    void *anim_data, int16_t frame_index,
                                    int16_t frame_count);
typedef int (*valid_real_vectors_fn)(float *fwd, float *left, float *up);
typedef int (*valid_real_matrix4x3_fn)(float *m);
typedef int (*valid_fwd_and_up_fn)(float *fwd, float *up);
typedef void (*matrix_4x3_multiply_fn)(float *a, float *b, float *out);
typedef void (*matrix_4x3_from_point_fn)(float *out, float *point);
typedef void (*model_node_set_default_fn)(float *out, void *anim_data);

/* object_compute_node_matrices (0x141b70) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void *(*const b141b70_get)(int, int) = object_get_and_verify_type;
static void *(*const b141b70_tag)(int, int) = tag_get;
static void * (*const b141b70_c13dfc0)(int object_handle, void *reference) = object_header_block_reference_get;
static void * (*const b141b70_c13c100)(int16_t object_type) = FUN_0013c100;
static void *(*const b141b70_onode)(int, short) = object_get_node_matrix;
static void *(*const b141b70_elem)(void *, int, int) = tag_block_get_element;
static int (*const b141b70_gtime)(void) = game_time_get;
static void (*const b141b70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b141b70_exitfn)(int) = system_exit;
static void (*const b141b70_c121d60)(void *mode_tag, void *animation, int animation_index, void *out_node_data) = FUN_00121d60;
static void (*const b141b70_c123aa0)(void *mode_tag, void *out_node_data) = FUN_00123aa0;
static void (*const b141b70_c122690)(void *animation, float frame, void *node_data) = FUN_00122690;
static void (*const b141b70_c122450)(void *animation, int frame, float scale, void *node_output) = overlay_animation_apply_scaled;
static void (*const b141b70_c13c7a0)(int param_1, int param_2) = FUN_0013c7a0;
static void (*const b141b70_c120ba0)(void) = interpolate_node_orientations;
static bool (*const b141b70_ca16b0)(float *point) = valid_real_point3d;
static const char * (*const b141b70_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b141b70_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static bool (*const b141b70_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static void (*const b141b70_c109500)(float *out, float *qsp) = FUN_00109500;
static void (*const b141b70_c109280)(float *out, float *position) = matrix4x3_identity_with_position;
static void (*const b141b70_c109e10)(float *out, float *forward, float *up) = matrix_from_forward_and_up;
static void (*const b141b70_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static char (*const b141b70_cf6c40)(float *a, float *b, float *c) = valid_real_vector3d_axes3;
static bool (*const b141b70_c21fb0)(float *v) = valid_real_normal3d;
static char (*const b141b70_cf6d00)(float *mat) = valid_real_matrix4x3;
static void (*const b141b70_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b141b70_xfrmpt)(float *, float *, float *) = matrix_transform_point;

__attribute__((naked, noinline))
void object_compute_node_matrices(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xa44, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "leal 0x1a0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[c13dfc0]\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl $0xfe0, %%edx\n\t"
      "je .Lobject_compute_node_matrices_1\n\t"
      "leal -0xa44(%%ebp), %%eax\n\t"
      "jmp .Lobject_compute_node_matrices_2\n\t"
      ".Lobject_compute_node_matrices_1:\n\t"
      "leal 0x19c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c13dfc0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_compute_node_matrices_2:\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "cmpl $-1, 0x34(%%edi)\n\t"
      "je .Lobject_compute_node_matrices_105\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x64(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13c100]\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lobject_compute_node_matrices_3\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .Lobject_compute_node_matrices_4\n\t"
      ".Lobject_compute_node_matrices_3:\n\t"
      "movsbw 0xd0(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[onode]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lobject_compute_node_matrices_4:\n\t"
      "movl 0x7c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movb $0, -0xd(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_8\n\t"
      "cmpw $-1, 0x80(%%esi)\n\t"
      "je .Lobject_compute_node_matrices_7\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x80(%%esi), %%edx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jns .Lobject_compute_node_matrices_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0, 0x22(%%eax)\n\t"
      "jle .Lobject_compute_node_matrices_5\n\t"
      "call *%[gtime]\n\t"
      "addl 0x8(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movswl 0x22(%%ecx), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jge .Lobject_compute_node_matrices_6\n\t"
      "pushl $1\n\t"
      "pushl $0xa90\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c430\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lobject_compute_node_matrices_6\n\t"
      ".Lobject_compute_node_matrices_5:\n\t"
      "movw 0x82(%%esi), %%dx\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      ".Lobject_compute_node_matrices_6:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c121d60]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x3a(%%ecx), %%al\n\t"
      "shrb $1, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0xd(%%ebp)\n\t"
      "jmp .Lobject_compute_node_matrices_10\n\t"
      ".Lobject_compute_node_matrices_7:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "jmp .Lobject_compute_node_matrices_9\n\t"
      ".Lobject_compute_node_matrices_8:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      ".Lobject_compute_node_matrices_9:\n\t"
      "call *%[c123aa0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_compute_node_matrices_10:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_compute_node_matrices_16\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "jle .Lobject_compute_node_matrices_16\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lobject_compute_node_matrices_11:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl $0x14\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, (%%eax)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_15\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movswl 0x2(%%edx), %%eax\n\t"
      "movl 0x158(%%ecx), %%edx\n\t"
      "addl $0x158, %%ecx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .Lobject_compute_node_matrices_15\n\t"
      "pushl $0x168\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movswl 0x2(%%eax), %%ecx\n\t"
      "movw 0x4(%%eax), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "flds 0xe4(%%esi,%%ecx,4)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_14\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "testb $2, (%%edx)\n\t"
      "je .Lobject_compute_node_matrices_12\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "fildl -0x20(%%ebp)\n\t"
      "jmp .Lobject_compute_node_matrices_13\n\t"
      ".Lobject_compute_node_matrices_12:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl 0x22(%%edx), %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "fildl -0x20(%%ebp)\n\t"
      ".Lobject_compute_node_matrices_13:\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c122690]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lobject_compute_node_matrices_15\n\t"
      ".Lobject_compute_node_matrices_14:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lobject_compute_node_matrices_15\n\t"
      "call *%[gtime]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movswl 0x22(%%ecx), %%ecx\n\t"
      "addl %%edx, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c122450]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lobject_compute_node_matrices_15:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lobject_compute_node_matrices_11\n\t"
      ".Lobject_compute_node_matrices_16:\n\t"
      "flds 0x60(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_compute_node_matrices_17\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "flds 0x60(%%esi)\n\t"
      "fmuls 0x1c(%%eax)\n\t"
      "fstps 0x1c(%%eax)\n\t"
      "flds 0x60(%%esi)\n\t"
      "fmuls 0x10(%%eax)\n\t"
      "fstps 0x10(%%eax)\n\t"
      "flds 0x60(%%esi)\n\t"
      "fmuls 0x14(%%eax)\n\t"
      "fstps 0x14(%%eax)\n\t"
      "flds 0x60(%%esi)\n\t"
      "fmuls 0x18(%%eax)\n\t"
      "fstps 0x18(%%eax)\n\t"
      ".Lobject_compute_node_matrices_17:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "cmpl $-1, 0x44(%%edx)\n\t"
      "je .Lobject_compute_node_matrices_18\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c7a0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_compute_node_matrices_18:\n\t"
      "cmpw $0, 0x86(%%esi)\n\t"
      "jle .Lobject_compute_node_matrices_20\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl $0xfe0, %%edx\n\t"
      "je .Lobject_compute_node_matrices_19\n\t"
      "pushl $1\n\t"
      "pushl $0xad9\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bf80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_19:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x86(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x84(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "leal 0x198(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13dfc0]\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xb8(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c120ba0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_20:\n\t"
      "movb -0xd(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_22\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_21\n\t"
      "flds 0x14(%%esi)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0xae2\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29c3f0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_21:\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_22\n\t"
      "flds 0x38(%%esi)\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xae3\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29c3a0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_22:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0xb8, %%eax\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      "movw %%cx, -0x244(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jmp .Lobject_compute_node_matrices_24\n\t"
      ".Lobject_compute_node_matrices_23:\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "jmp .Lobject_compute_node_matrices_24\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lobject_compute_node_matrices_24:\n\t"
      "movswl %%cx, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw -0x244(%%ebp,%%edx,2), %%ax\n\t"
      "pushl $0x9c\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_79\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x15c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109500]\n\t"
      "movb -0xd(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_47\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xf4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109280]\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109e10]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $0x10, %%ah\n\t"
      "je .Lobject_compute_node_matrices_25\n\t"
      "flds -0xb0(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xb0(%%ebp)\n\t"
      "flds -0xac(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xac(%%ebp)\n\t"
      "flds -0xa8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xa8(%%ebp)\n\t"
      ".Lobject_compute_node_matrices_25:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x8c(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_compute_node_matrices_26\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70687973\n\t"
      "call *%[tag]\n\t"
      "flds 0x14(%%eax)\n\t"
      "fchs\n\t"
      "leal -0x1c4(%%ebp), %%ecx\n\t"
      "flds 0x10(%%eax)\n\t"
      "fchs\n\t"
      "flds 0xc(%%eax)\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "pushl %%eax\n\t"
      "fstps -0x8c(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "call *%[c109280]\n\t"
      "leal -0xc0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109850]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lobject_compute_node_matrices_26:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "addl $0x14, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x190(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109280]\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x190(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lobject_compute_node_matrices_46\n\t"
      "cmpl $0x3f800000, (%%edi)\n\t"
      "je .Lobject_compute_node_matrices_27\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "flds -0xcc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x128(%%ebp), %%edi\n\t"
      "fstps -0xcc(%%ebp)\n\t"
      "flds -0xc8(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "fstps -0xc8(%%ebp)\n\t"
      "flds -0xc4(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "rep movsl\n\t"
      "fstps -0xc4(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "leal -0x128(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl $0x3f800000, -0x128(%%ebp)\n\t"
      "movl %%ecx, %%edi\n\t"
      ".Lobject_compute_node_matrices_27:\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x10, %%ch\n\t"
      "je .Lobject_compute_node_matrices_29\n\t"
      "leal -0x128(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "je .Lobject_compute_node_matrices_28\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x128(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "leal -0x128(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%ecx, %%edi\n\t"
      ".Lobject_compute_node_matrices_28:\n\t"
      "flds 0x10(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x10(%%edi)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x14(%%edi)\n\t"
      "flds 0x18(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x18(%%edi)\n\t"
      ".Lobject_compute_node_matrices_29:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_30\n\t"
      "leal 0x1c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_compute_node_matrices_30\n\t"
      "leal 0x28(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_45\n\t"
      ".Lobject_compute_node_matrices_30:\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29c384\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_31\n\t"
      "flds (%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bd6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_31:\n\t"
      "leal 0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_32\n\t"
      "flds 0xc(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bd4c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_32:\n\t"
      "leal 0x10(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_33\n\t"
      "flds 0x18(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x10(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bd2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_33:\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_34\n\t"
      "flds 0x24(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bd10\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_34:\n\t"
      "leal 0x28(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_35\n\t"
      "flds 0x30(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x28(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bcec\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_35:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .Lobject_compute_node_matrices_36\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_38\n\t"
      "jmp .Lobject_compute_node_matrices_37\n\t"
      ".Lobject_compute_node_matrices_36:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_37:\n\t"
      "flds 0x18(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x10(%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bca8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_38:\n\t"
      "flds 0x24(%%edi)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .Lobject_compute_node_matrices_39\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_41\n\t"
      "jmp .Lobject_compute_node_matrices_40\n\t"
      ".Lobject_compute_node_matrices_39:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_40:\n\t"
      "flds 0x18(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x10(%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x24(%%edi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bc6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_41:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fmuls 0x24(%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .Lobject_compute_node_matrices_42\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_44\n\t"
      "jmp .Lobject_compute_node_matrices_43\n\t"
      ".Lobject_compute_node_matrices_42:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_43:\n\t"
      "flds 0x24(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bc2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_44:\n\t"
      "pushl %%edi\n\t"
      "call *%[cf6d00]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_45\n\t"
      "pushl $1\n\t"
      "pushl $0xb37\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28bc0c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_45:\n\t"
      "pushl %%ebx\n\t"
      "leal -0xf4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c109850]\n\t"
      "pushl %%ebx\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c109850]\n\t"
      "pushl %%ebx\n\t"
      "leal -0x15c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c109850]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .Lobject_compute_node_matrices_48\n\t"
      ".Lobject_compute_node_matrices_46:\n\t"
      "pushl %%ebx\n\t"
      "leal -0xc0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xf4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "pushl %%ebx\n\t"
      "leal -0x15c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c109850]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lobject_compute_node_matrices_48\n\t"
      ".Lobject_compute_node_matrices_47:\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x15c(%%ebp), %%esi\n\t"
      "movl %%ebx, %%edi\n\t"
      "rep movsl\n\t"
      ".Lobject_compute_node_matrices_48:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_49\n\t"
      "leal 0x1c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%ebx), %%edi\n\t"
      "leal 0x4(%%ebx), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_compute_node_matrices_49\n\t"
      "movl 0x28(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x7c(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_49\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_49\n\t"
      "movl 0x30(%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_76\n\t"
      ".Lobject_compute_node_matrices_49:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29c34c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "subl $0x38, %%esp\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c318\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "movl 0x8c(%%esi), %%eax\n\t"
      "addl $0x50, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_compute_node_matrices_50\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70687973\n\t"
      "call *%[tag]\n\t"
      "flds 0x14(%%eax)\n\t"
      "fchs\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x10(%%eax)\n\t"
      "fchs\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0xc(%%eax)\n\t"
      "fchs\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c2f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lobject_compute_node_matrices_50:\n\t"
      "flds 0x1c(%%esi)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c2d4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lobject_compute_node_matrices_51\n\t"
      "flds 0xc(%%esi)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c2b0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x18(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c28c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x24(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c268\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x30(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c244\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds (%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c210\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lobject_compute_node_matrices_52\n\t"
      ".Lobject_compute_node_matrices_51:\n\t"
      "pushl $0x29c1fc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_compute_node_matrices_52:\n\t"
      "pushl $0x25386f\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "subl $0x10, %%esp\n\t"
      "flds 0x8(%%ebx)\n\t"
      "leal 0x4(%%ebx), %%esi\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c1dc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x18(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "leal 0x10(%%ebx), %%edi\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c1bc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x24(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c19c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x30(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c17c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds (%%ebx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c160\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_53\n\t"
      "leal 0x1c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_compute_node_matrices_53\n\t"
      "leal 0x28(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_76\n\t"
      ".Lobject_compute_node_matrices_53:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x68(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_54\n\t"
      "flds (%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bd6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_54:\n\t"
      "flds 0x8(%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "flds (%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .Lobject_compute_node_matrices_55\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_57\n\t"
      "jmp .Lobject_compute_node_matrices_56\n\t"
      ".Lobject_compute_node_matrices_55:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_56:\n\t"
      "flds 0xc(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bd4c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_57:\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .Lobject_compute_node_matrices_58\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_60\n\t"
      "jmp .Lobject_compute_node_matrices_59\n\t"
      ".Lobject_compute_node_matrices_58:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_59:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bd2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_60:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .Lobject_compute_node_matrices_61\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_63\n\t"
      "jmp .Lobject_compute_node_matrices_62\n\t"
      ".Lobject_compute_node_matrices_61:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_62:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bd10\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_63:\n\t"
      "movl 0x28(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_64\n\t"
      "movl 0x2c(%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_64\n\t"
      "movl 0x30(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_65\n\t"
      ".Lobject_compute_node_matrices_64:\n\t"
      "flds 0x30(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bcec\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_65:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .Lobject_compute_node_matrices_66\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_68\n\t"
      "jmp .Lobject_compute_node_matrices_67\n\t"
      ".Lobject_compute_node_matrices_66:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_67:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bca8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_68:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x1c(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .Lobject_compute_node_matrices_69\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_71\n\t"
      "jmp .Lobject_compute_node_matrices_70\n\t"
      ".Lobject_compute_node_matrices_69:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_70:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bc6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_71:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fmuls (%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .Lobject_compute_node_matrices_72\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_74\n\t"
      "jmp .Lobject_compute_node_matrices_73\n\t"
      ".Lobject_compute_node_matrices_72:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_73:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bc2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_74:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_75\n\t"
      "leal 0x1c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_compute_node_matrices_75\n\t"
      "leal 0x28(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_76\n\t"
      ".Lobject_compute_node_matrices_75:\n\t"
      "pushl $1\n\t"
      "pushl $0xb69\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c130\n\t"
      "pushl $0x28bc0c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_76:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x60(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_77\n\t"
      "leal 0x1c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_compute_node_matrices_77\n\t"
      "movl 0x28(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_77\n\t"
      "movl 0x2c(%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x74(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_77\n\t"
      "movl 0x30(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_102\n\t"
      ".Lobject_compute_node_matrices_77:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_78\n\t"
      "flds (%%ebx)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x28bd6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_78:\n\t"
      "flds 0x8(%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "flds (%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .Lobject_compute_node_matrices_81\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_83\n\t"
      "jmp .Lobject_compute_node_matrices_82\n\t"
      ".Lobject_compute_node_matrices_79:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "shll $5, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "leal (%%edx,%%ebx,1), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c109500]\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, 0x24(%%edi)\n\t"
      "jne .Lobject_compute_node_matrices_80\n\t"
      "pushl $1\n\t"
      "pushl $0xb71\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x291584\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_80:\n\t"
      "movswl 0x24(%%edi), %%eax\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lobject_compute_node_matrices_102\n\t"
      ".Lobject_compute_node_matrices_81:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_82:\n\t"
      "flds 0xc(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x28bd4c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_83:\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .Lobject_compute_node_matrices_84\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_86\n\t"
      "jmp .Lobject_compute_node_matrices_85\n\t"
      ".Lobject_compute_node_matrices_84:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_85:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x28bd2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_86:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .Lobject_compute_node_matrices_87\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_89\n\t"
      "jmp .Lobject_compute_node_matrices_88\n\t"
      ".Lobject_compute_node_matrices_87:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_88:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x28bd10\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_89:\n\t"
      "movl 0x28(%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_90\n\t"
      "movl 0x2c(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_90\n\t"
      "movl 0x30(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jne .Lobject_compute_node_matrices_91\n\t"
      ".Lobject_compute_node_matrices_90:\n\t"
      "flds 0x30(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x28bcec\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_91:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .Lobject_compute_node_matrices_92\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_94\n\t"
      "jmp .Lobject_compute_node_matrices_93\n\t"
      ".Lobject_compute_node_matrices_92:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_93:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x28bca8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_94:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x1c(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .Lobject_compute_node_matrices_95\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_97\n\t"
      "jmp .Lobject_compute_node_matrices_96\n\t"
      ".Lobject_compute_node_matrices_95:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_96:\n\t"
      "flds 0x18(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x28bc6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_97:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x24(%%ebx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x20(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fmuls (%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .Lobject_compute_node_matrices_98\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lobject_compute_node_matrices_100\n\t"
      "jmp .Lobject_compute_node_matrices_99\n\t"
      ".Lobject_compute_node_matrices_98:\n\t"
      "fstp %%st(0)\n\t"
      ".Lobject_compute_node_matrices_99:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x28bc2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_100:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "je .Lobject_compute_node_matrices_101\n\t"
      "leal 0x1c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_compute_node_matrices_101\n\t"
      "leal 0x28(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_compute_node_matrices_102\n\t"
      ".Lobject_compute_node_matrices_101:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xb77\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%edx\n\t"
      "pushl $0x28bc0c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_compute_node_matrices_102:\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movw 0x20(%%edx), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "je .Lobject_compute_node_matrices_103\n\t"
      "movswl %%ax, %%esi\n\t"
      "incl %%eax\n\t"
      "movw %%cx, -0x244(%%ebp,%%esi,2)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".Lobject_compute_node_matrices_103:\n\t"
      "movw 0x22(%%edx), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lobject_compute_node_matrices_104\n\t"
      "movswl %%ax, %%edx\n\t"
      "incl %%eax\n\t"
      "movw %%cx, -0x244(%%ebp,%%edx,2)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".Lobject_compute_node_matrices_104:\n\t"
      "movl -0x5c(%%ebp), %%ecx\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "jne .Lobject_compute_node_matrices_23\n\t"
      "jmp .Lobject_compute_node_matrices_106\n\t"
      ".Lobject_compute_node_matrices_105:\n\t"
      "movl $0x3f800000, (%%ebx)\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x1c(%%ebx), %%ecx\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal 0x28(%%ebx), %%ecx\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x1c(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "fstps 0x14(%%ebx)\n\t"
      "fstps 0x18(%%ebx)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".Lobject_compute_node_matrices_106:\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x8(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[xfrmpt]\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsts 0x5c(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x60(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_compute_node_matrices_107\n\t"
      "fmuls 0x60(%%esi)\n\t"
      "popl %%edi\n\t"
      "fstps 0x5c(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_compute_node_matrices_107:\n\t"
      "popl %%edi\n\t"
      "fstp %%st(0)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [get] "m"(b141b70_get), [tag] "m"(b141b70_tag), [c13dfc0] "m"(b141b70_c13dfc0), [c13c100] "m"(b141b70_c13c100), [onode] "m"(b141b70_onode), [elem] "m"(b141b70_elem), [gtime] "m"(b141b70_gtime), [assert] "m"(b141b70_assert), [exitfn] "m"(b141b70_exitfn), [c121d60] "m"(b141b70_c121d60), [c123aa0] "m"(b141b70_c123aa0), [c122690] "m"(b141b70_c122690), [c122450] "m"(b141b70_c122450), [c13c7a0] "m"(b141b70_c13c7a0), [c120ba0] "m"(b141b70_c120ba0), [ca16b0] "m"(b141b70_ca16b0), [c1ba1f0] "m"(b141b70_c1ba1f0), [c8d9d0] "m"(b141b70_c8d9d0), [c84a70] "m"(b141b70_c84a70), [c109500] "m"(b141b70_c109500), [c109280] "m"(b141b70_c109280), [c109e10] "m"(b141b70_c109e10), [c109850] "m"(b141b70_c109850), [cf6c40] "m"(b141b70_cf6c40), [c21fb0] "m"(b141b70_c21fb0), [cf6d00] "m"(b141b70_cf6d00), [c8f390] "m"(b141b70_c8f390), [xfrmpt] "m"(b141b70_xfrmpt)
      : "memory");
}
#else
#error "object_compute_node_matrices: clang naked draft required"
#endif


/* objects_scripting_detach — scripting wrapper: detach param_2 from param_1.
 * Checks that param_2's parent_object_index (+0xcc) matches param_1, then
 * calls object_detach_from_parent on param_2.
 * 0x143510 / objects.obj
 */
void objects_scripting_detach(int param_1, int param_2)
{
  int iVar1;

  if (param_1 != -1 && param_2 != -1) {
    iVar1 = (int)object_get_and_verify_type(param_2, 0xffffffff);
    if (*(int *)(iVar1 + 0xcc) == param_1) {
      object_detach_from_parent(param_2);
    }
  }
}

/* FUN_00143550 (0x143550) — XBE naked draft (batch 48). */
#if defined(__clang__)
static void *(*const b143550_get)(int, int) = object_get_and_verify_type;
static void *(*const b143550_tag)(int, int) = tag_get;
static void *(*const b143550_onode)(int, short) = object_get_node_matrix;
static void (*const b143550_c1894d0)(int flag, float *matrix, float scale) = FUN_001894d0;
static scenario_t * (*const b143550_c18e380)(void) = global_scenario_get;
static void *(*const b143550_elem)(void *, int, int) = tag_block_get_element;
static vector3_t * (*const b143550_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b143550_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static char * (*const b143550_c1d9710)(const char *str, int c) = strrchr;
static void * (*const b143550_c141480)(int object_handle, void *out_matrix) = object_get_world_matrix;
static void (*const b143550_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;
static void (*const b143550_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;
static void *(*const b143550_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b143550_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;
static int (*const b143550_c14c8e0)(int *out, int object_handle) = FUN_0014c8e0;
static void (*const b143550_c14cf20)(int param_1) = FUN_0014cf20;
static char (*const b143550_c1509c0)(int *out, int obj_idx) = FUN_001509c0;
static void (*const b143550_c1508b0)(int *state) = FUN_001508b0;
static void (*const b143550_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b143550_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;

__attribute__((naked, noinline))
void FUN_00143550(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc4, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x5a8d27, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_00143550_1\n\t"
      "pushl $0x3e99999a\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[onode]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c1894d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00143550_1:\n\t"
      "movb 0x5a8d24, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_2\n\t"
      "movw 0x6a(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00143550_2\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0x24\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x204, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x2ee6f4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_00143550_2:\n\t"
      "movb 0x46f088, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_5\n\t"
      "movl 0x2c(%%edi), %%edx\n\t"
      "pushl $0x5c\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9710]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c141480]\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c140070]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00143550_3\n\t"
      "incl %%edi\n\t"
      "jmp .LFUN_00143550_4\n\t"
      ".LFUN_00143550_3:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x2c(%%edx), %%edi\n\t"
      ".LFUN_00143550_4:\n\t"
      "movl 0x2ee6f0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c1894d0]\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0x30, %%esp\n\t"
      ".LFUN_00143550_5:\n\t"
      "movb 0x324c30, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_11\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_00143550_6\n\t"
      "cmpl %%eax, 0x7c(%%edi)\n\t"
      "je .LFUN_00143550_11\n\t"
      ".LFUN_00143550_6:\n\t"
      "flds 0x5c(%%esi)\n\t"
      "movl 0x2ee6cc, %%edi\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00143550_7\n\t"
      "movl 0x2ee6d0, %%edi\n\t"
      "jmp .LFUN_00143550_8\n\t"
      ".LFUN_00143550_7:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_00143550_8\n\t"
      "movl 0x2ee6e0, %%edi\n\t"
      ".LFUN_00143550_8:\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00143550_9\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00143550_10\n\t"
      ".LFUN_00143550_9:\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      ".LFUN_00143550_10:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00143550_11:\n\t"
      "movb 0x324c31, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_12\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c14c8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_12\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c14cf20]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00143550_12:\n\t"
      "movb 0x5a8d26, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_13\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1509c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_13\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1508b0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00143550_13:\n\t"
      "movb 0x5a8d25, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00143550_29\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .LFUN_00143550_29\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "jne .LFUN_00143550_29\n\t"
      "cmpw $7, 0x64(%%esi)\n\t"
      "jne .LFUN_00143550_14\n\t"
      "movw 0x292(%%edi), %%ax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00143550_29\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00143550_14\n\t"
      "cmpl $0x3f800000, 0x1b8(%%esi)\n\t"
      "je .LFUN_00143550_29\n\t"
      ".LFUN_00143550_14:\n\t"
      "movl 0x7c(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00143550_29\n\t"
      "pushl %%eax\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *%[c141480]\n\t"
      "movl 0x280(%%esi), %%eax\n\t"
      "leal 0x280(%%esi), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00143550_18\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00143550_15:\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00143550_16\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[onode]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00143550_17\n\t"
      ".LFUN_00143550_16:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[xfrmpt]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00143550_17:\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "movl (%%edi), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00143550_15\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".LFUN_00143550_18:\n\t"
      "flds 0x268(%%esi)\n\t"
      "leal 0x268(%%esi), %%edx\n\t"
      "fcomps 0x26c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00143550_29\n\t"
      "flds 0x270(%%esi)\n\t"
      "leal 0x270(%%esi), %%ecx\n\t"
      "fcomps 0x274(%%esi)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00143550_29\n\t"
      "flds 0x278(%%esi)\n\t"
      "leal 0x278(%%esi), %%eax\n\t"
      "fcomps 0x27c(%%esi)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00143550_29\n\t"
      "leal -0xc4(%%ebp), %%esi\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00143550_20\n\t"
      ".LFUN_00143550_19:\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "jmp .LFUN_00143550_20\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00143550_20:\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl $2, -0x10(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00143550_21:\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "movl $2, %%ebx\n\t"
      ".LFUN_00143550_22:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl (%%edi), %%eax\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "call *%[xfrmpt]\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $4, %%edi\n\t"
      "addl $0xc, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00143550_22\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_00143550_21\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_00143550_19\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00143550_23:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00143550_24:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_00143550_25:\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00143550_26\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%edx,2), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x94(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc4(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00143550_26:\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_00143550_27\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movswl %%si, %%edx\n\t"
      "leal (%%edx,%%ecx,4), %%eax\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xac(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc4(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00143550_27:\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00143550_28\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "leal (%%edx,%%ecx,2), %%eax\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $3, %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xb8(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc4(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00143550_28:\n\t"
      "incl %%esi\n\t"
      "cmpw $2, %%si\n\t"
      "jl .LFUN_00143550_25\n\t"
      "incl %%edi\n\t"
      "cmpw $2, %%di\n\t"
      "jl .LFUN_00143550_24\n\t"
      "incl %%ebx\n\t"
      "cmpw $2, %%bx\n\t"
      "jl .LFUN_00143550_23\n\t"
      ".LFUN_00143550_29:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b143550_get), [tag] "m"(b143550_tag), [onode] "m"(b143550_onode), [c1894d0] "m"(b143550_c1894d0), [c18e380] "m"(b143550_c18e380), [elem] "m"(b143550_elem), [c1412f0] "m"(b143550_c1412f0), [c189cb0] "m"(b143550_c189cb0), [c1d9710] "m"(b143550_c1d9710), [c141480] "m"(b143550_c141480), [c140070] "m"(b143550_c140070), [c189320] "m"(b143550_c189320), [dget] "m"(b143550_dget), [c189540] "m"(b143550_c189540), [c14c8e0] "m"(b143550_c14c8e0), [c14cf20] "m"(b143550_c14cf20), [c1509c0] "m"(b143550_c1509c0), [c1508b0] "m"(b143550_c1508b0), [xfrmpt] "m"(b143550_xfrmpt), [c189270] "m"(b143550_c189270)
      : "memory");
}
#else
#error "FUN_00143550: clang naked draft required"
#endif

/* attachments_delete — delete object attachments (effects, sounds, lights,
 * etc.).
 *
 * Iterates through the object's attachment slots (up to tag+0x140 count)
 * and dispatches cleanup calls based on attachment type:
 *   Type 0: light_delete (effect cleanup)
 *   Type 1: game_looping_sound_delete (sound cleanup)
 *   Type 2: effect_delete (decal cleanup)
 *   Type 3: object_compute_node_matrices + contrail_set_state_for_object (light cleanup)
 *   Type 4: FUN_0009f6e0 (contrail cleanup)
 *
 * Object attachment structure:
 *   obj+0xf4 to obj+0xf4+count: attachment type bytes (-1 = empty)
 *   obj+0xfc + index*4: attachment handle (int)
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (handle, -1).
 * Confirmed: CALL 0x1ba140 (tag_get) with ('obje', obj[0]).
 * Confirmed: switch jump table at 0x143ac0 for 5 cases.
 */
void attachments_delete(int object_handle)
{
  int *obj;
  char *tag;
  int16_t i;
  char type;
  int attachment_handle;

  obj = (int *)object_get_and_verify_type(object_handle, -1);
  tag = (char *)tag_get(0x6f626a65, obj[0]);

  for (i = 0; i < *(int *)(tag + 0x140); i++) {
    type = *((char *)obj + 0xf4 + (int)i);
    if (type == -1)
      continue;

    attachment_handle = *(int *)((char *)obj + 0xfc + (int)i * 4);
    if (attachment_handle == -1)
      continue;

    switch (type) {
    case 0:
      light_delete(attachment_handle);
      break;
    case 1:
      game_looping_sound_delete(attachment_handle);
      break;
    case 2:
      effect_delete(attachment_handle);
      break;
    case 3:
      object_compute_node_matrices(object_handle);
      contrail_set_state_for_object(attachment_handle, 1, 0);
      break;
    case 4:
      FUN_0009f6e0(attachment_handle);
      break;
    }
  }
}

/* object_set_position — reposition an object's position and facing.
 *
 * Disconnects the object from the map, optionally updates its position
 * (forward vector at obj+0x0C) and facing direction (at obj+0x24).
 * If a target (up) vector is provided, it is copied directly to obj+0x30.
 * Otherwise, a perpendicular up vector is computed from the facing via:
 *   temp = {facing.y, -facing.x, 0.0}
 *   normalize(temp)
 *   if degenerate: temp = {1, 0, 0}
 *   up = cross(temp, facing)
 * Then recomputes node matrices and reconnects to the map.
 *
 * Confirmed: 4 cdecl args (object_handle, facing, target, flags).
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (handle, -1).
 * Confirmed: CALL 0x13fd00 (object_disconnect_from_map) with 1 stack arg.
 * Confirmed: CALL 0x13010 (normalize3d) for perpendicular temp vector.
 * Confirmed: cross product computed via x87 FPU in-line (not a function call).
 * Confirmed: CALL 0x141b70 (object_compute_node_matrices).
 * Confirmed: CALL 0x140ce0 (object_connect_to_map) with (handle, 0).
 * Confirmed: FCOMP against *(float*)0x2533c0 (0.0f) for degenerate check.
 */
void object_set_position(int object_handle, float *position, float *forward,
                         float *up)
{
  char *obj;
  float temp[3];
  float mag;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  object_disconnect_from_map(object_handle);

  /* Copy position if provided */
  if (position != NULL) {
    *(float *)(obj + 0x0c) = position[0];
    *(float *)(obj + 0x10) = position[1];
    *(float *)(obj + 0x14) = position[2];
  }

  /* Copy forward direction and compute/set up vector */
  if (forward != NULL) {
    *(float *)(obj + 0x24) = forward[0];
    *(float *)(obj + 0x28) = forward[1];
    *(float *)(obj + 0x2c) = forward[2];

    if (up != NULL) {
      /* Up vector provided directly */
      *(float *)(obj + 0x30) = up[0];
      *(float *)(obj + 0x34) = up[1];
      *(float *)(obj + 0x38) = up[2];
    } else {
      /* Compute perpendicular up from forward direction:
       * temp = {forward.y, -forward.x, 0.0} */
      temp[0] = forward[1];
      temp[1] = -forward[0];
      temp[2] = 0.0f;

      mag = normalize3d(temp);
      if (mag == *(float *)0x2533c0) {
        /* Degenerate (forward is along Z) — use X axis */
        temp[0] = 1.0f;
        temp[2] = 0.0f;
        temp[1] = 0.0f;
      }

      /* up = cross(temp, forward) */
      *(float *)(obj + 0x30) = temp[1] * forward[2] - temp[2] * forward[1];
      *(float *)(obj + 0x34) = temp[2] * forward[0] - temp[0] * forward[2];
      *(float *)(obj + 0x38) = temp[0] * forward[1] - temp[1] * forward[0];
    }
  }

  object_compute_node_matrices(object_handle);
  object_connect_to_map(object_handle, 0);
}

/* object_translate — set an object's position and reconnect it to the map.
 *
 * Validates the new position with valid_real_point3d, asserts if invalid.
 * Disconnects the object from the BSP, copies the 3D position into the
 * object data at offset +0x0C, then reconnects with the given location.
 *
 * The assert string identifies this as "new_position" in objects.c line 0x232.
 *
 * Confirmed: 3 cdecl args (object_handle, position, location).
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (handle, -1).
 * Confirmed: CALL 0xa16b0 (valid_real_point3d) for point validation.
 * Confirmed: CALL 0x8d9d0 (csprintf) for assert message formatting.
 * Confirmed: CALL 0x8d9f0 (display_assert) with file/line left on stack.
 * Confirmed: CALL 0x8e2f0 (system_exit) with -1.
 * Confirmed: CALL 0x13fd00 (object_disconnect_from_map).
 * Confirmed: CALL 0x140ce0 (object_connect_to_map) with (handle, location).
 * Confirmed: position copied to obj+0x0C, obj+0x10, obj+0x14.
 */
void object_translate(int object_handle, float *position, void *location)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if (!valid_real_point3d(position)) {
    char *msg =
      csprintf((char *)0x5ab100, "%s: assert_valid_real_point3d(%f, %f, %f)",
               "new_position", (double)position[0], (double)position[1],
               (double)position[2]);
    display_assert(msg, "c:\\halo\\SOURCE\\objects\\objects.c", 0x232, 1);
    system_exit(-1);
  }
  object_disconnect_from_map(object_handle);
  *(float *)(obj + 0x0c) = position[0];
  *(float *)(obj + 0x10) = position[1];
  *(float *)(obj + 0x14) = position[2];
  object_connect_to_map(object_handle, location);
}

/* object_new (0x143c80) — XBE naked draft (batch 105). */
#if defined(__clang__)
static bool (*const b143c80_ca16b0)(float *point) = valid_real_point3d;
static char * (*const b143c80_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b143c80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b143c80_exitfn)(int) = system_exit;
static bool (*const b143c80_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b143c80_c84a10)(float *vector) = real_vector3d_valid;
static bool (*const b143c80_gerun)(void) = game_engine_running;
static int (*const b143c80_cae0a0)(int tag_index) = FUN_000ae0a0;
static void *(*const b143c80_tag)(int, int) = tag_get;
static void * (*const b143c80_c13c100)(int16_t object_type) = FUN_0013c100;
static int (*const b143c80_c13ded0)(data_t *data, int16_t datum_size, int type_hint) = object_header_new;
static void *(*const b143c80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b143c80_get)(int, int) = object_get_and_verify_type;
static void (*const b143c80_c13c430)(int param_1, void *param_2) = FUN_0013c430;
static void (*const b143c80_c13ffc0)(int object_handle, int flag) = object_set_garbage;
static int (*const b143c80_c13e050)(int object_handle, int offset, int size) = object_header_block_allocate;
static int (*const b143c80_c13c490)(int object_handle) = FUN_0013c490;
static void (*const b143c80_c13e1f0)(int object_handle, void *color_data) = object_choose_random_change_colors;
static void (*const b143c80_c140ad0)(int object_handle) = object_choose_random_region_permutations;
static void (*const b143c80_c1365d0)(int object_handle, float *body_vitality_override, float *shield_vitality_override) = FUN_001365d0;
static void (*const b143c80_c141b70)(int object_handle) = object_compute_node_matrices;
static void (*const b143c80_c140ce0)(int object_handle, void *location) = object_connect_to_map;
static void (*const b143c80_c13e1a0)(int object_handle) = FUN_0013e1a0;
static void (*const b143c80_c13c620)(int param_1) = FUN_0013c620;
static void (*const b143c80_c13e7b0)(int object_handle) = object_compute_function_values;
static void (*const b143c80_c13e5d0)(int object_handle) = object_compute_change_colors;
static void (*const b143c80_c136150)(int object_handle) = FUN_00136150;
static void (*const b143c80_c13ecb0)(int object_handle) = attachments_new;
static void (*const b143c80_odel)(int) = object_delete;
static int (*const b143c80_o9ec30)(int, int, int, short, float, float, int, int) = FUN_0009ec30;
static void (*const b143c80_c13c560)(int param_1) = FUN_0013c560;
static void (*const b143c80_c13df70)(data_t *data, int object_handle) = object_postprocess_node_matrices;
static const char * (*const b143c80_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b143c80_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static int (*const b143c80_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b143c80_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b143c80_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
int object_new(void *placement __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x210, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "leal 0x18(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_new_1\n\t"
      "flds 0x20(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x26a\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26ae30\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_new_1:\n\t"
      "leal 0x40(%%esi), %%ebx\n\t"
      "leal 0x34(%%esi), %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_new_2\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x26b\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c4bc\n\t"
      "pushl $0x29c4ac\n\t"
      "pushl $0x267490\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_new_2:\n\t"
      "leal 0x4c(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_new_3\n\t"
      "flds 0x54(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x26c\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x50(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c494\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_new_3:\n\t"
      "leal 0x28(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_new_4\n\t"
      "flds 0x30(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x26d\n\t"
      "pushl $0x29b91c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c474\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_new_4:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_new_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_new_23\n\t"
      "pushl %%eax\n\t"
      "call *%[cae0a0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lobject_new_5:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_new_23\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c100]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%eax), %%dx\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "call *%[c13ded0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lobject_new_22\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "orb $0x44, 0x2(%%eax)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb (%%ecx), %%dl\n\t"
      "movb %%dl, 0x3(%%eax)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movw (%%ecx), %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "movw %%cx, 0x64(%%edi)\n\t"
      "call *%[c13c430]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "leal 0xc(%%edi), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "leal 0x24(%%edi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x38(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "leal 0x30(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x44(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "leal 0x18(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x30(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x4c(%%esi), %%edx\n\t"
      "leal 0x3c(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x50(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x54(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "addl $0x18, %%esp\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x34(%%edi)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fmuls 0x38(%%edi)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "testb $1, %%al\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "je .Lobject_new_6\n\t"
      "orl $0x1000, %%eax\n\t"
      "jmp .Lobject_new_7\n\t"
      ".Lobject_new_6:\n\t"
      "andl $0xffffefff, %%eax\n\t"
      ".Lobject_new_7:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movw %%ax, 0x4c(%%edi)\n\t"
      "movw %%ax, 0x4(%%ecx)\n\t"
      "movl 0x5a8d28, %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl %%eax, 0xa0(%%edi)\n\t"
      "movl %%eax, 0xbc(%%edi)\n\t"
      "movw %%ax, 0x80(%%edi)\n\t"
      "movl 0x44(%%ecx), %%edx\n\t"
      "movl %%edx, 0x7c(%%edi)\n\t"
      "movl %%eax, 0x120(%%edi)\n\t"
      "movl %%eax, 0xcc(%%edi)\n\t"
      "movl %%eax, 0xc4(%%edi)\n\t"
      "movl %%eax, 0xc8(%%edi)\n\t"
      "movw %%ax, 0x6a(%%edi)\n\t"
      "movl %%eax, 0xac(%%edi)\n\t"
      "movl %%eax, 0xb0(%%edi)\n\t"
      "testb $1, 0x2(%%ecx)\n\t"
      "je .Lobject_new_8\n\t"
      "orl $0x40000, 0x4(%%edi)\n\t"
      ".Lobject_new_8:\n\t"
      "cmpl %%eax, 0x7c(%%ecx)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "je .Lobject_new_9\n\t"
      "orl $0x2000000, %%edx\n\t"
      "jmp .Lobject_new_10\n\t"
      ".Lobject_new_9:\n\t"
      "andl $0xfdffffff, %%edx\n\t"
      ".Lobject_new_10:\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "cmpl %%eax, 0x34(%%ecx)\n\t"
      "setne %%al\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13ffc0]\n\t"
      "movw 0x14(%%esi), %%cx\n\t"
      "movw %%cx, 0x68(%%edi)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x70(%%edi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, 0x74(%%edi)\n\t"
      "movw 0x16(%%esi), %%cx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw %%cx, 0x6e(%%edi)\n\t"
      "movw 0x13e(%%eax), %%dx\n\t"
      "movw %%dx, 0x126(%%edi)\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lobject_new_11\n\t"
      "movl $1, %%edi\n\t"
      "jmp .Lobject_new_12\n\t"
      ".Lobject_new_11:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0xb8(%%eax), %%di\n\t"
      ".Lobject_new_12:\n\t"
      "movl %%edi, %%eax\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1a0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13e050]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_new_13\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb (%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl $0xfe0, %%edx\n\t"
      "jne .Lobject_new_14\n\t"
      "shll $5, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x19c\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13e050]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_new_13\n\t"
      "pushl %%edi\n\t"
      "pushl $0x198\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13e050]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_new_14\n\t"
      ".Lobject_new_13:\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      ".Lobject_new_14:\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "je .Lobject_new_21\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13c490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_new_21\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $0x13, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "movb %%cl, 0xb(%%ebp)\n\t"
      "je .Lobject_new_15\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "je .Lobject_new_15\n\t"
      "andl $0xfff7ffff, %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      ".Lobject_new_15:\n\t"
      "leal 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c13e1f0]\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[c140ad0]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1365d0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c141b70]\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c140ce0]\n\t"
      "call *%[c13e1a0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13c620]\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c13e7b0]\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c13e5d0]\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c136150]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13ecb0]\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl $0x80000, %%ecx\n\t"
      "je .Lobject_new_16\n\t"
      "orl %%ecx, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "jmp .Lobject_new_17\n\t"
      ".Lobject_new_16:\n\t"
      "andl $0xfff7ffff, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".Lobject_new_17:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "testb $1, 0x2(%%edx)\n\t"
      "jne .Lobject_new_19\n\t"
      "testl %%ecx, 0x4(%%eax)\n\t"
      "je .Lobject_new_19\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "je .Lobject_new_18\n\t"
      "cmpw $-1, 0x4c(%%eax)\n\t"
      "je .Lobject_new_19\n\t"
      ".Lobject_new_18:\n\t"
      "pushl %%ebx\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_new_19:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xac(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_new_20\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[o9ec30]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lobject_new_20:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_new_21:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13c560]\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13df70]\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".Lobject_new_22:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x210(%%ebp), %%eax\n\t"
      "pushl $0x29c450\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x210(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x257984\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "leal -0x210(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x257984\n\t"
      "pushl $3\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_new_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ca16b0] "m"(b143c80_ca16b0), [c8d9d0] "m"(b143c80_c8d9d0), [assert] "m"(b143c80_assert), [exitfn] "m"(b143c80_exitfn), [c84a70] "m"(b143c80_c84a70), [c84a10] "m"(b143c80_c84a10), [gerun] "m"(b143c80_gerun), [cae0a0] "m"(b143c80_cae0a0), [tag] "m"(b143c80_tag), [c13c100] "m"(b143c80_c13c100), [c13ded0] "m"(b143c80_c13ded0), [dget] "m"(b143c80_dget), [get] "m"(b143c80_get), [c13c430] "m"(b143c80_c13c430), [c13ffc0] "m"(b143c80_c13ffc0), [c13e050] "m"(b143c80_c13e050), [c13c490] "m"(b143c80_c13c490), [c13e1f0] "m"(b143c80_c13e1f0), [c140ad0] "m"(b143c80_c140ad0), [c1365d0] "m"(b143c80_c1365d0), [c141b70] "m"(b143c80_c141b70), [c140ce0] "m"(b143c80_c140ce0), [c13e1a0] "m"(b143c80_c13e1a0), [c13c620] "m"(b143c80_c13c620), [c13e7b0] "m"(b143c80_c13e7b0), [c13e5d0] "m"(b143c80_c13e5d0), [c136150] "m"(b143c80_c136150), [c13ecb0] "m"(b143c80_c13ecb0), [odel] "m"(b143c80_odel), [o9ec30] "m"(b143c80_o9ec30), [c13c560] "m"(b143c80_c13c560), [c13df70] "m"(b143c80_c13df70), [c1ba1f0] "m"(b143c80_c1ba1f0), [c19b0d0] "m"(b143c80_c19b0d0), [c1d90f0] "m"(b143c80_c1d90f0), [cff4d0] "m"(b143c80_cff4d0), [c8f390] "m"(b143c80_c8f390)
      : "memory");
}
#else
#error "object_new: clang naked draft required"
#endif


/*
 * object_attach_to_parent — attach a child object to a parent at a specific
 * node, establishing the parent-child relationship in the object hierarchy.
 *
 * First walks the parent's own parent chain to verify the child is not already
 * an ancestor of the parent (prevents circular attachment). Then computes the
 * inverse of the parent's node matrix and transforms the child's position,
 * up vector, and forward vector into the parent node's local coordinate space.
 * Stores the parent handle and node index in the child's object data
 * (offsets 0xCC and 0xD0). If the child was connected to the map (flag bit 11
 * of object_data_t.flags), it is disconnected before the transform and
 * reconnected afterward.
 *
 * Finally clears the "collideable" flag (bit 0) on the child's header if set,
 * sets the "updated this tick" flag (bit 4), and recomputes node matrices.
 *
 * Confirmed: 3 cdecl args (parent_handle, child_handle, parent_node_index).
 * Confirmed: CALL targets 0x13d680, 0x13fef0, 0x13fd00, 0x140eb0, 0x109150,
 *            0x109590, 0x109680, 0x140ce0, 0x119320, 0x141b70.
 * Confirmed: parent chain walk uses parent_object_index at offset 0xCC.
 * Confirmed: stores parent_handle at child+0xCC, node_index byte at child+0xD0.
 * Confirmed: flag test is (flags >> 0xB) & 1 — bit 11 of object_data_t.flags.
 * Inferred:  bit 11 means "connected to map" based on disconnect/reconnect
 * usage.
 */
void object_attach_to_parent(int parent_handle, int child_handle,
                             int parent_node_index)
{
  int iter;
  object_data_t *child_obj;
  uint8_t connected_to_map;
  float local_matrix[13]; /* 4x3 matrix = 52 bytes */
  float *node_mat;
  object_header_data_t *child_hdr;

  iter = parent_handle;

  /* Walk the parent chain to verify we are not creating a cycle. */
  while (iter != -1) {
    object_header_data_t *hdr =
      (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, iter);
    object_data_t *obj_iter = hdr->object;
    int16_t obj_type = obj_iter->type;

    if ((1 << ((uint8_t)obj_type & 0x1f)) == 0) {
      display_assert(csprintf((char *)0x5ab100,
                              "got an object type we didn't expect "
                              "(expected one of 0x%08x but got #%d).",
                              -1, (int)obj_type),
                     "c:\\halo\\SOURCE\\objects\\objects.c", 0x69a, 1);
      system_exit(-1);
    }

    if (iter == child_handle)
      break;

    iter = obj_iter->parent_object_index.value;
  }

  if (iter != -1) {
    display_assert("cannot attach an object to one of its children",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x4c9, 1);
    system_exit(-1);
    return;
  }

  /* Get child and parent object pointers. */
  child_obj = (object_data_t *)object_get_and_verify_type(child_handle, -1);
  object_get_and_verify_type(parent_handle, -1);

  connected_to_map = (uint8_t)((child_obj->flags >> 0xB) & 1);

  if (!object_has_node(parent_handle, (int16_t)parent_node_index)) {
    display_assert("object_has_node(parent_object_index, parent_node_index)",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x4d3, 1);
    system_exit(-1);
  }

  /* Disconnect child from map if it was connected. */
  if (connected_to_map) {
    object_disconnect_from_map(child_handle);
  }

  /* Compute inverse of the parent node matrix, then transform the child's
     position, up, and forward vectors into the parent node's local space. */
  node_mat =
    (float *)object_get_node_matrix(parent_handle, (int16_t)parent_node_index);
  matrix_inverse(node_mat, local_matrix);
  matrix_transform_point(local_matrix,
                         (float *)&child_obj->unk_12, /* dup-args-ok */
                         (float *)&child_obj->unk_12);
  matrix_transform_vector(local_matrix,
                          (float *)&child_obj->unk_36, /* dup-args-ok */
                          (float *)&child_obj->unk_36);
  matrix_transform_vector(local_matrix,
                          (float *)&child_obj->unk_48, /* dup-args-ok */
                          (float *)&child_obj->unk_48);

  /* Store parent attachment info in the child object. */
  child_obj->parent_object_index.value = parent_handle;
  *(uint8_t *)((char *)child_obj + 0xD0) = (uint8_t)parent_node_index;

  /* Reconnect child to map if it was connected. */
  if (connected_to_map) {
    object_connect_to_map(child_handle, NULL);
  }

  /* Update child header flags. */
  child_hdr =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, child_handle);
  object_get_and_verify_type(child_handle, -1);

  if (child_hdr->unk_2 & 0x01) {
    child_hdr->unk_2 &= 0xfe;
  }

  child_hdr =
    (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, child_handle);
  child_hdr->unk_2 |= 0x10;

  object_compute_node_matrices(child_handle);
}

/*
 * object_try_place — attempt to place an object at a new position by casting
 * a collision ray from the object's current position toward the target
 * position.
 *
 * Pushes a collision user stack entry (user=0x13), computes the delta vector
 * (current_pos - target_pos), then calls FUN_0014df70 to perform a collision
 * test along that ray. If the collision test succeeds or the object has no
 * current cluster placement (field 0x4c == -1), the function checks the
 * collision result for a valid surface. If a valid surface is found, it calls
 * object_translate to update the object's position and reconnect it to the map,
 * then recomputes node matrices. Returns true if the object was placed or
 * already had a valid cluster reference, false otherwise.
 *
 * Confirmed: cdecl, 2 stack args — PUSH position, PUSH handle before CALL.
 * Confirmed: returns bool in AL (callers TEST AL,AL after CALL).
 * Confirmed: collision_result buffer is 0x50 bytes (int16_t[40]).
 * Confirmed: collision user ID 0x13 pushed to stack at 0x5a8c80.
 * Confirmed: assert strings match "objects.c" at lines 0x93d and 0x953.
 */
bool object_try_place(int object_handle, float *position)
{
  char *obj;
  bool result;
  int16_t collision_result[40]; /* 0x50 bytes at EBP-0x5c */
  float delta[3]; /* 3 floats at EBP-0x0c */

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  result = false;

  /* Push collision user stack entry (user = 0x13). */
  if (*(volatile int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x93d, true);
    system_exit(-1);
  }
  {
    int depth = (int)*(volatile int16_t *)0x4761d8;
    *(volatile int16_t *)0x4761d8 += 1;
    *(int16_t *)(0x5a8c80 + depth * 2) = 0x13;
  }

  /* Compute delta vector: current_position - target_position. */
  delta[0] = *(float *)(obj + 0x0c) - position[0];
  delta[1] = *(float *)(obj + 0x10) - position[1];
  delta[2] = *(float *)(obj + 0x14) - position[2];

  /* Cast collision ray from target position along delta direction. */
  if (FUN_0014df70(0x1000e9, position, delta, -1, collision_result) ||
      *(int16_t *)(obj + 0x4c) == -1) {
    /* Collision found or object has no cluster placement. */
    if (*(int16_t *)((char *)collision_result + 0x10) == -1) {
      /* No valid surface in collision result — cannot place. */
      goto done;
    }
    /* Place object at collision surface position and reconnect to map. */
    object_translate(object_handle, (float *)((char *)collision_result + 0x18),
                     (void *)((char *)collision_result + 0x0c));
    object_compute_node_matrices(object_handle);
  }
  result = true;

done:
  /* Pop collision user stack entry. */
  if (*(volatile int16_t *)0x4761d8 <= 1) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\objects\\objects.c", 0x953, true);
    system_exit(-1);
  }
  *(volatile int16_t *)0x4761d8 -= 1;

  return result;
}

/*
 * object_update_children_recursive — recursively compute node matrices for an
 * object and all of its child objects.
 *
 * First computes the node matrices for the given object by calling
 * object_compute_node_matrices (0x141b70), then walks the child chain starting
 * at object_data+0xC8 (first child handle). For each child, verifies type via
 * datum_get + type check, recurses, then advances via next_object_index
 * (object_data+0xC4).
 *
 * Confirmed: CALL 0x13d680 with args (-1, handle) — object_get_and_verify_type.
 * Confirmed: CALL 0x141b70 with 1 arg (handle) — object_compute_node_matrices.
 * Confirmed: MOV ESI,[EDI+0xC8] — first child from object data.
 * Confirmed: datum_get(*(data_t**)0x5a8d50, child_handle) for child lookup.
 * Confirmed: MOVSX ECX,word ptr [EDI+0x64] — child object type (int16_t).
 * Confirmed: MOV ESI,[EDI+0xC4] — next sibling from child object data.
 * Confirmed: recursive self-call at 0x144719.
 */
#if defined(__clang__)
void object_update_children_recursive(int object_handle);

static void *(*const oucr_get)(int, int) = object_get_and_verify_type;
static void (*const oucr_compute)(int) = object_compute_node_matrices;
static void *(*const oucr_datum)(data_t *, int) = datum_get;
static char *(*const oucr_csprintf)(char *, const char *, ...) = csprintf;
static void (*const oucr_assert)(const char *, const char *, int, bool) =
    display_assert;
static void (*const oucr_exit)(int) = system_exit;
static void (*const oucr_self)(int) = object_update_children_recursive;

__attribute__((naked, noinline))
void object_update_children_recursive(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[compute]\n\t"
      "movl 0xc8(%%edi), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je 3f\n\t"
      "1:\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[datum]\n\t"
      "movl 8(%%eax), %%edi\n\t"
      "movswl 0x64(%%edi), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne 2f\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[csprintf]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exit]\n\t"
      "addl $0x14, %%esp\n\t"
      "2:\n\t"
      "pushl %%esi\n\t"
      "call *%[self]\n\t"
      "movl 0xc4(%%edi), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne 1b\n\t"
      "3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(oucr_get), [compute] "m"(oucr_compute),
        [datum] "m"(oucr_datum), [csprintf] "m"(oucr_csprintf),
        [assert] "m"(oucr_assert), [exit] "m"(oucr_exit), [self] "m"(oucr_self)
      : "memory");
}
#else
void object_update_children_recursive(int object_handle)
{
  char *obj;
  int child_handle;
  char *child_header;
  char *child_obj;
  int16_t child_type;
  int type_bit;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  object_compute_node_matrices(object_handle);

  child_handle = *(int *)(obj + 0xc8);
  while (child_handle != -1) {
    child_header =
        (char *)datum_get(*(data_t **)0x5a8d50, child_handle);
    child_obj = *(char **)(child_header + 8);
    child_type = *(int16_t *)(child_obj + 0x64);
    type_bit = 1 << (int)child_type;
    if (type_bit == 0) {
      char *msg = csprintf((char *)0x5ab100, (char *)0x0029b940, -1,
                           (int)child_type);
      display_assert(msg, (char *)0x0029b91c, 0x69a, 1);
      system_exit(-1);
    }

    object_update_children_recursive(child_handle);
    child_handle = *(int *)(child_obj + 0xc4);
  }
}
#endif

/*
 * object_attach_to_marker — attach a child object to a parent at a named
 * marker position.
 *
 * Resolves markers on both parent and child objects via
 * object_get_markers_by_string_id. Disconnects the child from the map, then:
 *
 * - If child_marker_name is NULL or empty: computes an inverse of the child
 *   marker matrix and transforms the parent marker's position/up/forward
 *   into the child's local frame, writing directly to the child object's
 *   position (offset 0x0C), up (0x24), and forward (0x30).
 *
 * - If child_marker_name is provided: delegates to
 *   object_compute_child_marker_position (0x141020) to compute the relative
 *   transform using both markers.
 *
 * Finally reconnects the child to the map and calls object_attach_to_parent
 * (0x144240) with the parent node index from the parent marker result.
 *
 * Confirmed: 4 cdecl args (PUSH count before CALL, ADD ESP,0x2c combined
 *            cleanup covers first 4 CALLs).
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with (-1,
 * child_handle). Confirmed: CALL 0x140f10 (object_get_markers_by_string_id)
 * twice, max_count=1. Confirmed: CALL 0x13fd00 (object_disconnect_from_map)
 * with child_handle. Confirmed: TEST EDI,EDI / CMP byte ptr [EDI],0 —
 * null-or-empty check on child_marker_name. Confirmed: CALL 0x109150
 * (matrix_inverse) with child_markers+4 as source. Confirmed: CALL 0x109590 /
 * 0x109680 transform into object+0xC, +0x24, +0x30. Confirmed: CALL 0x141020
 * (object_compute_child_marker_position) in else branch. Confirmed: CALL
 * 0x140ce0 (object_connect_to_map) with (child_handle, 0). Confirmed: CALL
 * 0x144240 (object_attach_to_parent) with (parent_handle, child_handle,
 * parent_markers[0]). Inferred:  marker result struct is 0x6C (108) bytes;
 * first dword is node index, matrix at offset +4, position/up/forward within
 * parent marker at offsets 0x60, 0x3C, 0x54 respectively.
 */
void object_attach_to_marker(int parent_handle, void *marker_name,
                             int child_handle, void *child_marker_name)
{
  char parent_markers[0x6C];
  char child_markers[0x6C];
  float inverse[13]; /* 4x3 matrix = 52 bytes */

  void *child_obj = object_get_and_verify_type(child_handle, -1);

  object_get_markers_by_string_id(parent_handle, marker_name, parent_markers,
                                  1);
  object_get_markers_by_string_id(child_handle, child_marker_name,
                                  child_markers, 1);
  object_disconnect_from_map(child_handle);

  if (child_marker_name == NULL || *(char *)child_marker_name == '\0') {
    /* No child marker name — invert the child marker's matrix and use it to
       transform the parent marker's position/up/forward into the child's
       local coordinate space. */
    matrix_inverse((float *)(child_markers + 4), inverse);
    matrix_transform_point(inverse, (float *)(parent_markers + 0x60),
                           (float *)((char *)child_obj + 0xC));
    matrix_transform_vector(inverse, (float *)(parent_markers + 0x3C),
                            (float *)((char *)child_obj + 0x24));
    matrix_transform_vector(inverse, (float *)(parent_markers + 0x54),
                            (float *)((char *)child_obj + 0x30));
  } else {
    /* Child marker name specified — delegate to
       object_compute_child_marker_position which handles the full
       relative-transform computation. The destination matrix aliases
       parent_markers+0x38 (the parent marker's embedded matrix). */
    object_compute_child_marker_position(child_obj, child_markers,
                                         parent_markers + 0x38);
  }

  object_connect_to_map(child_handle, NULL);
  object_attach_to_parent(parent_handle, child_handle, *(int *)parent_markers);
}

/* object_new_from_scenario (0x144770) — XBE naked draft (batch 135). */
#if defined(__clang__)
static void *(*const b144770_elem)(void *, int, int) = tag_block_get_element;
static void (*const b144770_opnew)(void *, int, int) = object_placement_data_new;
static void (*const b144770_c10bbc0)(float *forward, float *up, float *angles) = vectors3d_from_euler_angles3d;
static int (*const b144770_onew)(void *) = object_new;
static void (*const b144770_c13c500)(int param_1, int param_2) = FUN_0013c500;
static void (*const b144770_c13ef70)(int object_handle, int16_t name_index) = object_name_list_new;

__attribute__((naked, noinline))
int object_new_from_scenario(void *placement_data __attribute__((unused)), int palette_block __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x88, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movw (%%esi), %%cx\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lobject_new_from_scenario_3\n\t"
      "movl 0x46f084, %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .Lobject_new_from_scenario_1\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .Lobject_new_from_scenario_3\n\t"
      ".Lobject_new_from_scenario_1:\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobject_new_from_scenario_2\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lobject_new_from_scenario_2\n\t"
      "cmpw $0x200, %%ax\n\t"
      "jge .Lobject_new_from_scenario_2\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x46f07c, %%eax\n\t"
      "cmpl $-1, (%%eax,%%edx,4)\n\t"
      "jne .Lobject_new_from_scenario_3\n\t"
      ".Lobject_new_from_scenario_2:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "pushl $0x30\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_new_from_scenario_3\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "leal 0x14(%%esi), %%edx\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x68(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10bbc0]\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x72(%%ebp)\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lobject_new_from_scenario_3\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c500]\n\t"
      "movswl 0x2(%%esi), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lobject_new_from_scenario_3\n\t"
      "call *%[c13ef70]\n\t"
      ".Lobject_new_from_scenario_3:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b144770_elem), [opnew] "m"(b144770_opnew), [c10bbc0] "m"(b144770_c10bbc0), [onew] "m"(b144770_onew), [c13c500] "m"(b144770_c13c500), [c13ef70] "m"(b144770_c13ef70)
      : "memory");
}
#else
#error "object_new_from_scenario: clang naked draft required"
#endif


/*
 * object_delete_recursive — object deactivation and deallocation.
 *
 * Recursively tears down an object and its children/siblings, then deallocates
 * the object from the object pool. Called either from
 * objects_garbage_collection (immediate delete) or from the garbage collection
 * pass in objects_update.
 *
 * Steps:
 *   1. If object has flag 0x10000, clear garbage flag via
 * object_set_garbage_flag.
 *   2. Call deletion callbacks via FUN_00138eb0 (dispatch through function
 * table).
 *   3. Recursively deactivate child object (obj+0xC8).
 *   4. If delete_sibling is nonzero, recursively deactivate sibling (obj+0xC4).
 *   5. Clear collideable bit (datum header bit 0) if set.
 *   6. Call type table cleanup via FUN_0013c100.
 *   7. Call object cleanup via FUN_001362d0.
 *   8. Call widget detach via attachments_delete.
 *   9. If object has flag 0x800, disconnect from map via
 * object_disconnect_from_map.
 *  10. Call FUN_0013c560 (final cleanup).
 *  11. Free memory pool block if allocated (via memory_pool_block_free).
 *  12. Delete datum from object pool via datum_delete.
 *  13. Clear field_8 and unk_2 in header.
 *
 * Confirmed: cdecl, 2 stack args (object_handle, delete_sibling).
 * Confirmed: delete_sibling is read as byte (MOVZX AL) but compared as bool.
 * Confirmed: Recursive calls at 0x1449ff and 0x144a1c with (child/sibling, 1).
 * Confirmed: Multiple object_get_and_verify_type calls to re-fetch after
 * recursion. Confirmed: EDI preserved across recursive calls (initial object
 * ptr). Confirmed: obj+0xC8 is child handle, obj+0xC4 is sibling handle.
 * Confirmed: 0x10000 flag triggers garbage flag clear.
 * Confirmed: 0x800 flag triggers map disconnect.
 */
/* 0x1449b0 */
void object_delete_recursive(int object_handle, int delete_sibling)
{
  object_data_t *obj;
  object_header_data_t *hdr;
  int16_t obj_type;
  void *field_8_ptr;

  obj = (object_data_t *)object_get_and_verify_type(object_handle, -1);
  tag_get(0x6f626a65, (int)obj->tag_index);

  /* If object has flag 0x10000, clear the garbage flag. */
  if (obj->flags & 0x10000) {
    object_set_garbage_flag(object_handle, 0);
  }

  /* Dispatch deletion callbacks. */
  FUN_00138eb0(object_handle);

  /* Recursively deactivate child object. */
  if (obj->unk_200.value != -1) {
    object_delete_recursive(obj->unk_200.value, 1);
  }

  /* Optionally deactivate sibling object. */
  if ((char)delete_sibling != 0 && obj->next_object_index.value != -1) {
    object_delete_recursive(obj->next_object_index.value, 1);
  }

  /* Get datum header and clear collideable bit if set. */
  hdr = (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  object_get_and_verify_type(object_handle, -1);
  if (hdr->unk_2 & 0x01) {
    hdr->unk_2 &= (uint8_t)~0x01;
  }

  /* Re-fetch object pointer after recursive calls. */
  obj = (object_data_t *)object_get_and_verify_type(object_handle, -1);
  tag_get(0x6f626a65, (int)obj->tag_index);

  /* Call type table cleanup. */
  obj_type = obj->type;
  FUN_0013c100(obj_type);

  /* Object cleanup and widget detach. */
  FUN_001362d0(object_handle);
  attachments_delete(object_handle);

  /* If flag 0x800 is set, disconnect from map. */
  if (obj->flags & 0x800) {
    object_disconnect_from_map(object_handle);
  }

  /* Final cleanup. */
  FUN_0013c560(object_handle);

  /* Free memory pool block if allocated. */
  hdr = (object_header_data_t *)datum_get(*(data_t **)0x5a8d50, object_handle);
  field_8_ptr = (void *)&hdr->object;
  if (hdr->object != 0) {
    memory_pool_block_free(*(void **)0x46f080, (void **)field_8_ptr);
  }

  /* Delete datum from pool. */
  datum_delete(*(data_t **)0x5a8d50, object_handle);

  /* Clear remaining fields. */
  *(object_data_t **)field_8_ptr = 0;
  hdr->unk_2 = 0;
}

/*
 * objects_garbage_collection — delete and immediately deactivate an object.
 *
 * Marks the object (and its children) for deletion via object_delete_internal,
 * then immediately tears down / deallocates the object via
 * object_delete_recursive. Used by actor_erase_units as the "soft" deletion
 * path (flag!=0) as an alternative to object_delete, which only marks for
 * deletion and defers actual teardown to the objects_update garbage-collection
 * pass.
 *
 * Confirmed: cdecl, one stack arg (object_handle).
 * Confirmed: PUSH 0x0 / PUSH ESI / CALL 0x140bc0 (object_delete_internal).
 * Confirmed: PUSH 0x0 / PUSH ESI / CALL 0x1449b0 (object_delete_recursive).
 * Confirmed: ADD ESP,0x10 — combined cleanup for both 2-arg calls.
 * Confirmed: ESI saved/restored (callee-saved register for param_1).
 */
/* 0x144b30 */
void objects_garbage_collection(int object_handle)
{
  object_delete_internal(object_handle, 0);
  object_delete_recursive(object_handle, 0);
}

/*
 * objects_garbage_collect_tick — per-tick garbage collection pass.
 *
 * Runs each game tick from objects_update. Determines memory pressure level,
 * walks the garbage object list, deletes objects not visible to any player,
 * compacts the memory pool, and runs AI release callbacks when critical.
 *
 * Three GC levels: 0=forced (external flag), 1=mild (headroom low),
 * 2=critical (memory or slots exhausted). Callback table at 0x29b868 has
 * two AI release entries (swarms and encounters) plus a NULL terminator.
 *
 * Confirmed: void(void) cdecl, _chkstk for 0x2814 bytes of stack.
 * Confirmed: globals at 0x46f080 (pool), 0x46f084 (object_globals),
 *   0x5a8d50 (object_header_data), 0x5a8d4c (debug flag).
 * Confirmed: thresholds 0xcccc, 0x19999, 0x6666, 0x67, 0xCC, 0x32, 0x1E, 150.
 * Confirmed: three deletion calls in sequence: set_garbage_flag,
 * delete_internal, delete_recursive — all with (handle, 0). Confirmed: callback
 * table 2 entries: {NULL, 0x3fa40}, {0x3fb40, 0x3fc90}. Confirmed: FILD + FMUL
 * 100.0f + FMUL (1/1048576.0f) for percentage calc.
 */
/* objects_garbage_collect_tick (0x144b50) — XBE naked draft (batch 49). */
#if defined(__clang__)
static void (*const b144b50_chkstk)(void) = FUN_001d90e0;
static int (*const b144b50_c11e3c0)(void *pool) = memory_pool_get_contiguous_free_size;
static void (*const b144b50_c11e840)(void *pool) = memory_pool_compact;
static int (*const b144b50_c11e390)(void *pool) = memory_pool_get_free_size;
static void (*const b144b50_cff4d0)(int channel, const char *format, ...) = console_printf;
static void *(*const b144b50_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b144b50_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b144b50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b144b50_exitfn)(int) = system_exit;
static int (*const b144b50_c1407e0)(int object_handle) = object_visible_to_any_player;
static char * (*const b144b50_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b144b50_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b144b50_garb)(int, int) = object_set_garbage_flag;
static void (*const b144b50_c140bc0)(int object_handle, int delete_sibling) = object_delete_internal;
static void (*const b144b50_c1449b0)(int object_handle, int delete_sibling) = object_delete_recursive;
static int (*const b144b50_gtime)(void) = game_time_get;
static int (*const b144b50_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
void objects_garbage_collect_tick(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2814, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%cl, %%cl\n\t"
      "movl $2, %%esi\n\t"
      "je .Lobjects_garbage_collect_tick_1\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jmp .Lobjects_garbage_collect_tick_4\n\t"
      ".Lobjects_garbage_collect_tick_1:\n\t"
      "movl 0x46f080, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11e3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xcccc, %%eax\n\t"
      "jg .Lobjects_garbage_collect_tick_2\n\t"
      "movl 0x46f080, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c11e840]\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11e3c0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0x19999, %%eax\n\t"
      "jg .Lobjects_garbage_collect_tick_47\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .Lobjects_garbage_collect_tick_4\n\t"
      ".Lobjects_garbage_collect_tick_2:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "movswl 0x30(%%ecx), %%edx\n\t"
      "movl $0x800, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "cmpl $0x66, %%eax\n\t"
      "jg .Lobjects_garbage_collect_tick_3\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .Lobjects_garbage_collect_tick_4\n\t"
      ".Lobjects_garbage_collect_tick_3:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "cmpw $0x32, 0x4(%%eax)\n\t"
      "jl .Lobjects_garbage_collect_tick_46\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_4:\n\t"
      "movb 0x5a8d4c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .Lobjects_garbage_collect_tick_5\n\t"
      "movl 0x46f080, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11e3c0]\n\t"
      "movl 0x46f080, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c11e390]\n\t"
      "movl 0x5a8d50, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movl $0x100000, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movswl 0x30(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29c64c\n\t"
      "pushl %%edi\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_5:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movl 0x8(%%ecx), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobjects_garbage_collect_tick_9\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "nop\n\t"
      ".Lobjects_garbage_collect_tick_6:\n\t"
      "movl 0x5a8d50, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ebx\n\t"
      "movswl 0x64(%%ebx), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lobjects_garbage_collect_tick_7\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_7:\n\t"
      "cmpw $0x800, %%di\n\t"
      "jl .Lobjects_garbage_collect_tick_8\n\t"
      "pushl $1\n\t"
      "pushl $0x10c1\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c61c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_8:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl %%esi, -0x2814(%%ebp,%%ecx,4)\n\t"
      "movl 0xc0(%%ebx), %%esi\n\t"
      "incl %%edi\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .Lobjects_garbage_collect_tick_6\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_9:\n\t"
      "movswl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lobjects_garbage_collect_tick_10:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lobjects_garbage_collect_tick_12\n\t"
      "decl %%eax\n\t"
      "je .Lobjects_garbage_collect_tick_13\n\t"
      "decl %%eax\n\t"
      "je .Lobjects_garbage_collect_tick_11\n\t"
      "pushl $1\n\t"
      "pushl $0x10da\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lobjects_garbage_collect_tick_14\n\t"
      ".Lobjects_garbage_collect_tick_11:\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11e390]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x19999, %%eax\n\t"
      "jl .Lobjects_garbage_collect_tick_12\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "movswl 0x2e(%%ecx), %%edx\n\t"
      "movl $0x800, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "cmpl $0xcc, %%eax\n\t"
      "jge .Lobjects_garbage_collect_tick_20\n\t"
      ".Lobjects_garbage_collect_tick_12:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lobjects_garbage_collect_tick_15\n\t"
      ".Lobjects_garbage_collect_tick_13:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "cmpw $0x1e, 0x4(%%ecx)\n\t"
      "setle -0x1(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_14:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobjects_garbage_collect_tick_21\n\t"
      ".Lobjects_garbage_collect_tick_15:\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "je .Lobjects_garbage_collect_tick_21\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl -0x2814(%%ebp,%%edx,4), %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, -0xc(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "movb $1, %%bl\n\t"
      "jne .Lobjects_garbage_collect_tick_16\n\t"
      "movb 0x2(%%edi), %%bl\n\t"
      "andb $1, %%bl\n\t"
      ".Lobjects_garbage_collect_tick_16:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1407e0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobjects_garbage_collect_tick_10\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lobjects_garbage_collect_tick_10\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ebx\n\t"
      "movswl 0x64(%%ebx), %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lobjects_garbage_collect_tick_17\n\t"
      "pushl $1\n\t"
      "pushl $0x69a\n\t"
      "pushl $0x29b91c\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x29b940\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_17:\n\t"
      "movb 0x64(%%ebx), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testb $3, %%al\n\t"
      "je .Lobjects_garbage_collect_tick_18\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "jne .Lobjects_garbage_collect_tick_18\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "call *%[c49ac0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29c5ec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_18:\n\t"
      "testb $1, 0x2(%%edi)\n\t"
      "je .Lobjects_garbage_collect_tick_19\n\t"
      "movl 0x46f084, %%eax\n\t"
      "decw 0x4(%%eax)\n\t"
      ".Lobjects_garbage_collect_tick_19:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[garb]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c140bc0]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1449b0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lobjects_garbage_collect_tick_10\n\t"
      ".Lobjects_garbage_collect_tick_20:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_21:\n\t"
      "movl 0x46f080, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11e840]\n\t"
      "movb 0x5a8d4c, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_garbage_collect_tick_22\n\t"
      "movl 0x46f080, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c11e3c0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "movswl 0x30(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29c5b8\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_22:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobjects_garbage_collect_tick_45\n\t"
      "movl 0x46f084, %%edx\n\t"
      "cmpl $-1, 0x8c(%%edx)\n\t"
      "movl $0x29b868, %%esi\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "je .Lobjects_garbage_collect_tick_23\n\t"
      "call *%[gtime]\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "movl 0x8c(%%ecx), %%edx\n\t"
      "addl $0x96, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "jge .Lobjects_garbage_collect_tick_24\n\t"
      ".Lobjects_garbage_collect_tick_23:\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_24:\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_25:\n\t"
      "xorb %%bl, %%bl\n\t"
      "movl %%edi, %%eax\n\t"
      "subl $2, %%eax\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jne .Lobjects_garbage_collect_tick_29\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11e3c0]\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "movswl 0x2e(%%ecx), %%edx\n\t"
      "movl $0x800, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl $0x6666, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jg .Lobjects_garbage_collect_tick_30\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_26:\n\t"
      "movb $1, %%bl\n\t"
      ".Lobjects_garbage_collect_tick_27:\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "leal -0x214(%%ebp), %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fmuls 0x29ba04\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c5a4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_28:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobjects_garbage_collect_tick_33\n\t"
      ".Lobjects_garbage_collect_tick_29:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_garbage_collect_tick_41\n\t"
      "movl $0x25554c, %%eax\n\t"
      "jmp .Lobjects_garbage_collect_tick_35\n\t"
      ".Lobjects_garbage_collect_tick_30:\n\t"
      "cmpl $0x33, %%ecx\n\t"
      "jg .Lobjects_garbage_collect_tick_31\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lobjects_garbage_collect_tick_32\n\t"
      ".Lobjects_garbage_collect_tick_31:\n\t"
      "cmpl $0xcccc, %%eax\n\t"
      "jle .Lobjects_garbage_collect_tick_26\n\t"
      "cmpl $0x66, %%ecx\n\t"
      "jg .Lobjects_garbage_collect_tick_27\n\t"
      ".Lobjects_garbage_collect_tick_32:\n\t"
      "pushl %%ecx\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl $0x29c594\n\t"
      "pushl %%eax\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lobjects_garbage_collect_tick_28\n\t"
      ".Lobjects_garbage_collect_tick_33:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_garbage_collect_tick_34\n\t"
      "movl $0x29c58c, %%eax\n\t"
      "jmp .Lobjects_garbage_collect_tick_35\n\t"
      ".Lobjects_garbage_collect_tick_34:\n\t"
      "movl $0x25386f, %%eax\n\t"
      ".Lobjects_garbage_collect_tick_35:\n\t"
      "leal -0x214(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x414(%%ebp), %%eax\n\t"
      "pushl $0x29c568\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x414(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x257984\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "leal -0x414(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x257984\n\t"
      "pushl $3\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "je .Lobjects_garbage_collect_tick_43\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobjects_garbage_collect_tick_43\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lobjects_garbage_collect_tick_36:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lobjects_garbage_collect_tick_40\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      "jne .Lobjects_garbage_collect_tick_37\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobjects_garbage_collect_tick_37\n\t"
      "leal -0x1814(%%ebp), %%ecx\n\t"
      "pushl $0x1000\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_37:\n\t"
      "pushl $0x1000\n\t"
      "leal -0x1814(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x814(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *0x4(%%esi)\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lobjects_garbage_collect_tick_38\n\t"
      "leal -0x814(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x614(%%ebp), %%eax\n\t"
      "pushl $0x29c550\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x614(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x257984\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "leal -0x614(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x257984\n\t"
      "pushl $3\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x24, %%esp\n\t"
      ".Lobjects_garbage_collect_tick_38:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobjects_garbage_collect_tick_39\n\t"
      "addl $8, %%esi\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      ".Lobjects_garbage_collect_tick_39:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lobjects_garbage_collect_tick_36\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lobjects_garbage_collect_tick_43\n\t"
      ".Lobjects_garbage_collect_tick_40:\n\t"
      "movl 0x46f080, %%eax\n\t"
      "pushl %%eax\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "call *%[c11e840]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lobjects_garbage_collect_tick_25\n\t"
      ".Lobjects_garbage_collect_tick_41:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lobjects_garbage_collect_tick_42\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_garbage_collect_tick_42\n\t"
      "leal -0x214(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29c530\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lobjects_garbage_collect_tick_43\n\t"
      ".Lobjects_garbage_collect_tick_42:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_garbage_collect_tick_44\n\t"
      ".Lobjects_garbage_collect_tick_43:\n\t"
      "call *%[gtime]\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x8c(%%ecx)\n\t"
      "movb $0, 0x2(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobjects_garbage_collect_tick_44:\n\t"
      "movl 0x46f084, %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x2(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobjects_garbage_collect_tick_45:\n\t"
      "movl 0x46f084, %%eax\n\t"
      ".Lobjects_garbage_collect_tick_46:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x2(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobjects_garbage_collect_tick_47:\n\t"
      "movl 0x46f084, %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x2(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b144b50_chkstk), [c11e3c0] "m"(b144b50_c11e3c0), [c11e840] "m"(b144b50_c11e840), [c11e390] "m"(b144b50_c11e390), [cff4d0] "m"(b144b50_cff4d0), [dget] "m"(b144b50_dget), [c8d9d0] "m"(b144b50_c8d9d0), [assert] "m"(b144b50_assert), [exitfn] "m"(b144b50_exitfn), [c1407e0] "m"(b144b50_c1407e0), [c49ac0] "m"(b144b50_c49ac0), [c8f390] "m"(b144b50_c8f390), [garb] "m"(b144b50_garb), [c140bc0] "m"(b144b50_c140bc0), [c1449b0] "m"(b144b50_c1449b0), [gtime] "m"(b144b50_gtime), [c1d90f0] "m"(b144b50_c1d90f0)
      : "memory");
}
#else
#error "objects_garbage_collect_tick: clang naked draft required"
#endif


/* objects_update (0x145170) — XBE naked draft (batch 110). */
#if defined(__clang__)
static int (*const b145170_gtime)(void) = game_time_get;
static bool (*const b145170_ca7430)(void) = game_players_are_double_speed;
static void (*const b145170_penter)(void *) = profile_enter_private;
static void * (*const b145170_c18e3c0)(void) = scenario_get;
static void * (*const b145170_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void * (*const b145170_cba6c0)(void) = players_get_combined_pvs;
static int (*const b145170_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void (*const b145170_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b145170_exitfn)(int) = system_exit;
static void (*const b145170_c140bc0)(int object_handle, int delete_sibling) = object_delete_internal;
static void (*const b145170_c13fb80)(int object_handle) = object_deactivate;
static void (*const b145170_c13fb30)(int object_handle) = object_activate;
static void (*const b145170_c1963c0)(uint32_t *old_cluster_visibility, uint32_t *new_cluster_visibility, int16_t cluster_count) = FUN_001963c0;
static void *(*const b145170_get)(int, int) = object_get_and_verify_type;
static char (*const b145170_c1444f0)(int object_handle) = object_update;
static void (*const b145170_c1449b0)(int object_handle, int delete_sibling) = object_delete_recursive;
static void (*const b145170_c144b50)(void) = objects_garbage_collect_tick;
static void (*const b145170_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
void objects_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "call *%[gtime]\n\t"
      "testb $1, %%al\n\t"
      "je .Lobjects_update_1\n\t"
      "call *%[ca7430]\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .Lobjects_update_2\n\t"
      ".Lobjects_update_1:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lobjects_update_2:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_update_3\n\t"
      "movb 0x324640, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_update_3\n\t"
      "pushl $0x324638\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_update_3:\n\t"
      "movl 0x46f084, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal 0xc(%%eax), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0x4(%%eax)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "leal 0x4c(%%eax), %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "movswl 0x134(%%eax), %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "addl $0x1f, %%esi\n\t"
      "sarl $5, %%esi\n\t"
      "shll $2, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "call *%[cba6c0]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobjects_update_11\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x2e(%%eax)\n\t"
      "jle .Lobjects_update_10\n\t"
      ".Lobjects_update_4:\n\t"
      "cmpw $0, (%%esi)\n\t"
      "je .Lobjects_update_9\n\t"
      "movb 0x2(%%esi), %%al\n\t"
      "testb $0x40, %%al\n\t"
      "je .Lobjects_update_9\n\t"
      "testb $0x20, %%al\n\t"
      "je .Lobjects_update_9\n\t"
      "testb $1, %%al\n\t"
      "je .Lobjects_update_7\n\t"
      "cmpw $-1, 0x4(%%esi)\n\t"
      "jne .Lobjects_update_5\n\t"
      "pushl $1\n\t"
      "pushl $0x171\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c6f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_update_5:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%edi,%%eax,4)\n\t"
      "jne .Lobjects_update_9\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "testl $0x80000, 0x4(%%eax)\n\t"
      "je .Lobjects_update_6\n\t"
      "movswl %%bx, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140bc0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lobjects_update_9\n\t"
      ".Lobjects_update_6:\n\t"
      "movswl %%bx, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13fb80]\n\t"
      "jmp .Lobjects_update_8\n\t"
      ".Lobjects_update_7:\n\t"
      "testb %%al, %%al\n\t"
      "js .Lobjects_update_9\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobjects_update_9\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%edi,%%eax,4)\n\t"
      "je .Lobjects_update_9\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13fb30]\n\t"
      ".Lobjects_update_8:\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_update_9:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "incl %%ebx\n\t"
      "addl $0xc, %%esi\n\t"
      "cmpw 0x2e(%%ecx), %%bx\n\t"
      "jl .Lobjects_update_4\n\t"
      ".Lobjects_update_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1963c0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lobjects_update_11:\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, 0x2e(%%eax)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jle .Lobjects_update_17\n\t"
      ".Lobjects_update_12:\n\t"
      "movw (%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .Lobjects_update_16\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "testb $1, %%al\n\t"
      "je .Lobjects_update_16\n\t"
      "testb $4, %%al\n\t"
      "jne .Lobjects_update_16\n\t"
      "movswl %%cx, %%esi\n\t"
      "movswl %%dx, %%ecx\n\t"
      "shll $0x10, %%esi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "orl %%ecx, %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Lobjects_update_13\n\t"
      "pushl $1\n\t"
      "pushl $0x1a0\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c6bc\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_update_13:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0xc4(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Lobjects_update_14\n\t"
      "pushl $1\n\t"
      "pushl $0x1a1\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29c680\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_update_14:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_update_15\n\t"
      "movb 0x3(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $3, %%dl\n\t"
      "je .Lobjects_update_16\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0x1c8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Lobjects_update_16\n\t"
      ".Lobjects_update_15:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1444f0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_update_16:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "incl %%edx\n\t"
      "addl $0xc, %%edi\n\t"
      "cmpw 0x2e(%%eax), %%dx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jl .Lobjects_update_12\n\t"
      ".Lobjects_update_17:\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x2e(%%eax)\n\t"
      "jle .Lobjects_update_21\n\t"
      "movb $0xef, %%bl\n\t"
      ".Lobjects_update_18:\n\t"
      "movw (%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .Lobjects_update_20\n\t"
      "movb 0x2(%%esi), %%al\n\t"
      "andb %%bl, %%al\n\t"
      "testb $4, %%al\n\t"
      "movb %%al, 0x2(%%esi)\n\t"
      "je .Lobjects_update_19\n\t"
      "andb $0xfb, %%al\n\t"
      "movb %%al, 0x2(%%esi)\n\t"
      "movswl %%cx, %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "shll $0x10, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1444f0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_update_19:\n\t"
      "testb $8, 0x2(%%esi)\n\t"
      "je .Lobjects_update_20\n\t"
      "movswl (%%esi), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "shll $0x10, %%edx\n\t"
      "orl %%eax, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1449b0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobjects_update_20:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "incl %%edi\n\t"
      "addl $0xc, %%esi\n\t"
      "cmpw 0x2e(%%ecx), %%di\n\t"
      "jl .Lobjects_update_18\n\t"
      ".Lobjects_update_21:\n\t"
      "call *%[c144b50]\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .Lobjects_update_22\n\t"
      "movb 0x324640, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobjects_update_22\n\t"
      "pushl $0x324638\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_update_22:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b145170_gtime), [ca7430] "m"(b145170_ca7430), [penter] "m"(b145170_penter), [c18e3c0] "m"(b145170_c18e3c0), [c8e0b0] "m"(b145170_c8e0b0), [cba6c0] "m"(b145170_cba6c0), [c8da40] "m"(b145170_c8da40), [assert] "m"(b145170_assert), [exitfn] "m"(b145170_exitfn), [c140bc0] "m"(b145170_c140bc0), [c13fb80] "m"(b145170_c13fb80), [c13fb30] "m"(b145170_c13fb30), [c1963c0] "m"(b145170_c1963c0), [get] "m"(b145170_get), [c1444f0] "m"(b145170_c1444f0), [c1449b0] "m"(b145170_c1449b0), [c144b50] "m"(b145170_c144b50), [pexit] "m"(b145170_pexit)
      : "memory");
}
#else
#error "objects_update: clang naked draft required"
#endif


/* 0x1a9520 — get world-space position of the "body" marker on an object.
 * Thin wrapper: calls object_get_markers_by_string_id for marker "body",
 * then extracts XYZ from offset 0x60 in the marker output record. */
void FUN_001a9520(int object_handle, float *out_position)
{
  char marker_buf[0x6c];
  object_get_markers_by_string_id(object_handle, "body", marker_buf, 1);
  out_position[0] = *(float *)(marker_buf + 0x60);
  out_position[1] = *(float *)(marker_buf + 0x64);
  out_position[2] = *(float *)(marker_buf + 0x68);
}

/* ====================================================================
 * FINAL 10 OBJECTS.OBJ FUNCTIONS
 * ==================================================================== */

/* 0x84ae0 — bored_camera_update: generates random camera positions/angles
 * when the game is idle (attract mode). Validates the resulting camera
 * parameters and asserts on invalid values.
 *
 * Source: c:\halo\SOURCE\camera\bored_camera.c
 * 3 cdecl params: camera_state, unit_datum, result buffer.
 */
/* FUN_00084ae0 (0x84ae0) — XBE naked draft (batch 49). */
#if defined(__clang__)
static unsigned int (*const b84ae0_c8e370)(void) = system_milliseconds;
static void (*const b84ae0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b84ae0_exitfn)(int) = system_exit;
static int (*const b84ae0_cb65c0)(int16_t local_player_index) = player_control_get_aiming_unit_index;
static void (*const b84ae0_cb6740)(int16_t local_player_index, void *out_info) = player_control_get_unit_camera_info;
static void *(*const b84ae0_elem)(void *, int, int) = tag_block_get_element;
static float * (*const b84ae0_cb7e30)(int16_t local_player_index) = player_control_get_facing_angles;
static void (*const b84ae0_useat)(int, float *) = unit_set_seat_state;
static unsigned int *(*const b84ae0_lseed)(void) = random_math_get_local_seed_address;
static float (*const b84ae0_rrange)(int *, float, float) = random_real_range;
static void (*const b84ae0_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b84ae0_c8aa80)(float *forward, float *up) = observer_up_from_forward;
static bool (*const b84ae0_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b84ae0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b84ae0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void FUN_00084ae0(int *param_1 __attribute__((unused)), unsigned short *param_2 __attribute__((unused)), unsigned char *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e370]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jne .LFUN_00084ae0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x33\n\t"
      "pushl $0x266ea4\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084ae0_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00084ae0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x34\n\t"
      "pushl $0x266ea4\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084ae0_2:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "subl %%ebx, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "jle .LFUN_00084ae0_3\n\t"
      "movl $3, %%eax\n\t"
      ".LFUN_00084ae0_3:\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "imull $0x3e8, %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .LFUN_00084ae0_7\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb65c0]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6740]\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00084ae0_7\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl 0x4c(%%eax), %%ecx\n\t"
      "addl $0x4c, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00084ae0_4\n\t"
      "pushl $0x1c\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00084ae0_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%ebx), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[cb7e30]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "call *%[useat]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3ec90fdb\n\t"
      "pushl $0xbf8cbe4c\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f490fdb\n\t"
      "pushl $0xbf490fdb\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds 0x256980\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8aa80]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl $0x3fb2b8c2\n\t"
      "pushl $0x3f060a92\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x40c00000\n\t"
      "fstps 0x20(%%esi)\n\t"
      "pushl $0x3f800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "jle .LFUN_00084ae0_5\n\t"
      "movl $3, %%eax\n\t"
      ".LFUN_00084ae0_5:\n\t"
      "imull $0x2710, %%eax, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl $1, (%%esi)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fstps 0x48(%%esi)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "testb $1, (%%esi)\n\t"
      "je .LFUN_00084ae0_7\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00084ae0_6\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_00084ae0_6\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00084ae0_6\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00084ae0_7\n\t"
      ".LFUN_00084ae0_6:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x5f\n\t"
      "pushl $0x266ea4\n\t"
      "pushl %%eax\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084ae0_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b84ae0_c8e370), [assert] "m"(b84ae0_assert), [exitfn] "m"(b84ae0_exitfn), [cb65c0] "m"(b84ae0_cb65c0), [cb6740] "m"(b84ae0_cb6740), [elem] "m"(b84ae0_elem), [cb7e30] "m"(b84ae0_cb7e30), [useat] "m"(b84ae0_useat), [lseed] "m"(b84ae0_lseed), [rrange] "m"(b84ae0_rrange), [c10cc40] "m"(b84ae0_c10cc40), [c8aa80] "m"(b84ae0_c8aa80), [c84a70] "m"(b84ae0_c84a70), [c84a10] "m"(b84ae0_c84a10), [c8d9d0] "m"(b84ae0_c8d9d0)
      : "memory");
}
#else
#error "FUN_00084ae0: clang naked draft required"
#endif


/* 0x853c0 — camera_scripting_update: handles scripted camera with a 4-case
 * switch on the camera scripting mode (DAT_002ee5a2). Includes orbit camera
 * math with atan2/sin/cos and the same massive camera validation block.
 *
 * Source: c:\halo\SOURCE\camera\camera_scripting.c
 * 3 cdecl params.
 */
/* FUN_000853c0 (0x853c0) — XBE naked draft (batch 49). */
#if defined(__clang__)
static float (*const b853c0_cb5cc0)(void) = game_time_get_speed;
static bool (*const b853c0_cb5c30)(void) = game_time_get_paused;
static void *(*const b853c0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b853c0_tag)(int, int) = tag_get;
static void *(*const b853c0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b853c0_ftol)(void) = FUN_001d9068;
static void (*const b853c0_c123470)(void *mode_tag, void *animation, int animation_index, void *out_matrix) = FUN_00123470;
static void (*const b853c0_c89240)(void) = FUN_00089240;
static void (*const b853c0_c85b60)(void) = FUN_00085b60;
static void (*const b853c0_c85c80)(void) = FUN_00085c80;
static bool (*const b853c0_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b853c0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b853c0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b853c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b853c0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000853c0(int param_1 __attribute__((unused)), unsigned short *param_2 __attribute__((unused)), unsigned int *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "movl 0x31fc1c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl (%%eax), %%edi\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "call *%[cb5cc0]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl $8, (%%esi)\n\t"
      "call *%[cb5c30]\n\t"
      "testb %%al, %%al\n\t"
      "movl (%%esi), %%eax\n\t"
      "je .LFUN_000853c0_1\n\t"
      "orl $0x20, %%eax\n\t"
      "jmp .LFUN_000853c0_2\n\t"
      ".LFUN_000853c0_1:\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      ".LFUN_000853c0_2:\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movswl 0x2ee5a2, %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000853c0_15\n\t"
      "jmp *.LFUN_000853c0_jt(,%%eax,4)\n\t"
      ".LFUN_000853c0_3:\n\t"
      "movl 0x2ee5d4, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000853c0_4\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000853c0_15\n\t"
      "addl $0x50, %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_000853c0_4:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000853c0_5\n\t"
      "flds 0x2ee5a8\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "jmp .LFUN_000853c0_6\n\t"
      ".LFUN_000853c0_5:\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_000853c0_6:\n\t"
      "fstps 0x48(%%esi)\n\t"
      "movl 0x2ee5d0, %%eax\n\t"
      "movl %%eax, 0x20(%%esi)\n\t"
      "movl 0x2ee5b8, %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x2ee5bc, %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x2ee5c0, %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x2ee5c4, %%eax\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x2ee5c8, %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x2ee5cc, %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "cmpl $-1, 0x2ee5d4\n\t"
      "je .LFUN_000853c0_8\n\t"
      "flds 0x28(%%esi)\n\t"
      "flds (%%ecx)\n\t"
      "fpatan\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "flds 0x2ee5b4\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds 0x2ee5b0\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x2ee5ac\n\t"
      "fmuls (%%ecx)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000853c0_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_000853c0_7:\n\t"
      "fld %%st(0)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "leal 0x4(%%esi), %%edx\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "fld %%st(0)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "fmuls (%%ecx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "orl $1, %%eax\n\t"
      "fsubrs 0x2ee5ac\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "fsubrs 0x2ee5b0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "fsubrs 0x2ee5b4\n\t"
      "movl $0, 0x54(%%esi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movb $1, 0x4c(%%esi)\n\t"
      "fsin\n\t"
      "movl %%eax, (%%esi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcos\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fstps 0x10(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x14(%%esi)\n\t"
      "fstps 0x18(%%esi)\n\t"
      "jmp .LFUN_000853c0_15\n\t"
      ".LFUN_000853c0_8:\n\t"
      "movl 0x2ee5ac, %%edx\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x2ee5b0, %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x2ee5b4, %%edx\n\t"
      "orl $1, %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%eax, (%%esi)\n\t"
      "jmp .LFUN_000853c0_15\n\t"
      ".LFUN_000853c0_9:\n\t"
      "movl 0x2ee5d8, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2ee5dc, %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movswl 0x22(%%edi), %%ebx\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "flds 0x2ee5a8\n\t"
      "fmuls 0x253394\n\t"
      ".byte 0xde, 0xe9\n\t"
      "call *%[ftol]\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_000853c0_10\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_000853c0_11\n\t"
      ".LFUN_000853c0_10:\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal -0x1(%%ebx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .LFUN_000853c0_11\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_000853c0_11:\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "call *%[c123470]\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "movl %%eax, 0x48(%%esi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "orl $1, %%eax\n\t"
      "movl $0x3f9c61aa, 0x20(%%esi)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%eax, (%%esi)\n\t"
      "jmp .LFUN_000853c0_15\n\t"
      ".LFUN_000853c0_12:\n\t"
      "movl 0x2ee5d4, %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000853c0_15\n\t"
      "movl 0x2ee5d4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c89240]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000853c0_15\n\t"
      ".LFUN_000853c0_13:\n\t"
      "movl 0x2ee5d4, %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000853c0_15\n\t"
      "movb 0x2ee5a1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "je .LFUN_000853c0_14\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x2ee5d4, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c85b60]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000853c0_14:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c85c80]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000853c0_15:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fsubrs 0x2ee5a8\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000853c0_16\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, 0x2ee5a8\n\t"
      "jmp .LFUN_000853c0_17\n\t"
      ".LFUN_000853c0_16:\n\t"
      "fstps 0x2ee5a8\n\t"
      ".LFUN_000853c0_17:\n\t"
      "movb $0, 0x2ee5a1\n\t"
      "movl (%%esi), %%ebx\n\t"
      "testb $1, %%bl\n\t"
      "je .LFUN_000853c0_19\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000853c0_18\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000853c0_18\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000853c0_18\n\t"
      "movl 0x48(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_000853c0_18\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000853c0_18\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_000853c0_19\n\t"
      ".LFUN_000853c0_18:\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x16e\n\t"
      "pushl $0x266f0c\n\t"
      "pushl %%ebx\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%eax)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000853c0_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000853c0_jt:\n\t"
      ".long .LFUN_000853c0_3\n\t"
      ".long .LFUN_000853c0_9\n\t"
      ".long .LFUN_000853c0_12\n\t"
      ".long .LFUN_000853c0_13\n\t"
      ".text\n\t"
      :
      : [cb5cc0] "m"(b853c0_cb5cc0), [cb5c30] "m"(b853c0_cb5c30), [tryget] "m"(b853c0_tryget), [tag] "m"(b853c0_tag), [elem] "m"(b853c0_elem), [ftol] "m"(b853c0_ftol), [c123470] "m"(b853c0_c123470), [c89240] "m"(b853c0_c89240), [c85b60] "m"(b853c0_c85b60), [c85c80] "m"(b853c0_c85c80), [c84a70] "m"(b853c0_c84a70), [c84a10] "m"(b853c0_c84a10), [c8d9d0] "m"(b853c0_c8d9d0), [assert] "m"(b853c0_assert), [exitfn] "m"(b853c0_exitfn)
      : "memory");
}
#else
#error "FUN_000853c0: clang naked draft required"
#endif


/* 0x139b40 (object_lights.c) — register one lens-flare/light marker record
 * into the per-frame light marker array at 0x5a8f6c (count at 0x5a90ac, max 8
 * entries, 0x28-byte stride).
 *
 * Early-out if the array is already full (count >= 8) OR if all three color
 * components in param_5 equal 0 (the FCOMP vs FLOAT_002533c0 == 0.0 guard:
 * when color[0]==0 && color[1]==0 && color[2]==0 the record is skipped).
 *
 * Record layout filled at base = 0x5a8f6c + count*0x28:
 *   +0x00 : tag_get('lens', param_1)               (lens tag definition)
 *   +0x04 : param_2[0]                              (vec3 word 0)
 *   +0x08 : param_2[1]                              (vec3 word 1)
 *   +0x0c : param_2[2]                              (vec3 word 2)
 *   +0x10 : FUN_00180b10(param_3)                   (compressed normal)
 *   +0x14 : FUN_00180b10(param_4)                   (compressed normal)
 *   +0x18 : real_a_rgb_color_to_pixel32(1.0f, param_5)  (pixel32 color)
 *   +0x1c : 0xffff (short)
 *   +0x1e : 0xffff (short)
 *   +0x20 : (short)count                            (this record's index)
 *   +0x22 : byte at global 0x50654a (0x506548+2)
 *   +0x23 : (byte)FUN_00180770(param_6)             (alpha/intensity quantized)
 * Then count++ at 0x5a90ac.
 *
 * Confirmed (disasm 0x139b40): cdecl 6 stack args, RET (no RET N); ADD ESP,0x1c
 * = 8(rgb)+4(180770)+8(tag_get)+4(180b10)+4(180b10). param_6 is a float passed
 * raw to FUN_00180770 (caller MOV+PUSH, no FILD; callee FLD [EBP+8]). param_3
 * and param_4 are vec3 pointers passed as int (FUN_00180b10 derefs them);
 * kept as int to match the existing int(*)(int) thunk.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
/* FUN_00139b40 (0x139b40) — XBE naked draft (batch 64). */
#if defined(__clang__)
static uint32_t (*const b139b40_c99530)(float alpha, float *color) = real_a_rgb_color_to_pixel32;
static unsigned char (*const b139b40_c180770)(float alpha) = FUN_00180770;
static void *(*const b139b40_tag)(int, int) = tag_get;
static unsigned int (*const b139b40_c180b10)(float *param_1) = FUN_00180b10;

__attribute__((naked, noinline))
void FUN_00139b40(int param_1 __attribute__((unused)), int *param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)), float *param_5 __attribute__((unused)), float param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movw 0x5a90ac, %%dx\n\t"
      "cmpw $8, %%dx\n\t"
      "jge .LFUN_00139b40_2\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00139b40_1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00139b40_1\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00139b40_2\n\t"
      ".LFUN_00139b40_1:\n\t"
      "pushl %%esi\n\t"
      "movswl %%dx, %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal (%%eax,%%eax,4), %%esi\n\t"
      "pushl $0x3f800000\n\t"
      "leal 0x5a8f6c(,%%esi,8), %%esi\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180770]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6c656e73\n\t"
      "movb %%al, 0x23(%%esi)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x4(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "call *%[c180b10]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movb 0x50654a, %%al\n\t"
      "movb %%al, 0x22(%%esi)\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "movw %%ax, 0x1e(%%esi)\n\t"
      "movw %%ax, 0x1c(%%esi)\n\t"
      "movw 0x5a90ac, %%cx\n\t"
      "addl $0x1c, %%esp\n\t"
      "movw %%cx, 0x20(%%esi)\n\t"
      "incw 0x5a90ac\n\t"
      "popl %%esi\n\t"
      ".LFUN_00139b40_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c99530] "m"(b139b40_c99530), [c180770] "m"(b139b40_c180770), [tag] "m"(b139b40_tag), [c180b10] "m"(b139b40_c180b10)
      : "memory");
}
#else
#error "FUN_00139b40: clang naked draft required"
#endif


/* 0x139e50 — light_fill_structure: fills a light output structure from
 * intensity, color, and position data. Heavy FPU with many clamp operations.
 *
 * Register args: EBX=color_ptr, ESI=output_ptr, EDI=intensity_ptr
 * Stack params: param_1(byte flags), param_2(float* position),
 *               param_3(float* direction), param_4(float distance_scale)
 *
 * Source: c:\halo\SOURCE\objects\object_lights.c
 */
/* FUN_00139c20 (0x139c20) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void (*const b139c20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b139c20_exitfn)(int) = system_exit;
static int (*const b139c20_c191a50)(void *partition, int *state, int16_t cluster_idx) = cluster_partition_iter_first;
static void *(*const b139c20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b139c20_tag)(int, int) = tag_get;
static float (*const b139c20_c7a750)(float *color) = real_rgb_color_brightness;
static int (*const b139c20_c191660)(void *partition, int *state) = cluster_partition_iter_next;

__attribute__((naked, noinline))
void FUN_00139c20(int object_handle __attribute__((unused)), int16_t marker_index __attribute__((unused)), float *position __attribute__((unused)), float bias __attribute__((unused)), int out_index_base __attribute__((unused)), float *out_weights __attribute__((unused)), int out_atten_base __attribute__((unused)), int16_t *count __attribute__((unused)), int16_t max_count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00139c20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x544\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00139c20_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c191a50]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00139c20_14\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00139c20_2:\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00139c20_3\n\t"
      "pushl $1\n\t"
      "pushl $0x66f\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00139c20_3:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "cmpl 0x5a8d64, %%eax\n\t"
      "je .LFUN_00139c20_13\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00139c20_11\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "cmpl %%edx, 0x2c(%%esi)\n\t"
      "jne .LFUN_00139c20_4\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_00139c20_11\n\t"
      ".LFUN_00139c20_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x30(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x34(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x38(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fadds 0x54(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139c20_10\n\t"
      "flds 0x54(%%esi)\n\t"
      "addl $0x14, %%esi\n\t"
      "fld %%st(1)\n\t"
      "pushl %%esi\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c7a750]\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edx), %%ax\n\t"
      "addl $4, %%esp\n\t"
      "cmpw 0x28(%%ebp), %%ax\n\t"
      "jge .LFUN_00139c20_5\n\t"
      "movl %%eax, %%ecx\n\t"
      "incl %%eax\n\t"
      "movw %%ax, (%%edx)\n\t"
      "jmp .LFUN_00139c20_9\n\t"
      ".LFUN_00139c20_5:\n\t"
      "flds 0x2548fc\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00139c20_8\n\t"
      "movw (%%edx), %%si\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      ".LFUN_00139c20_6:\n\t"
      "fcoms (%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139c20_7\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ecx, %%edi\n\t"
      "flds (%%edx)\n\t"
      ".LFUN_00139c20_7:\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "cmpw %%si, %%cx\n\t"
      "jl .LFUN_00139c20_6\n\t"
      ".LFUN_00139c20_8:\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139c20_9\n\t"
      "movl %%edi, %%ecx\n\t"
      ".LFUN_00139c20_9:\n\t"
      "cmpw 0x28(%%ebp), %%cx\n\t"
      "jge .LFUN_00139c20_10\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movswl %%cx, %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "shll $2, %%eax\n\t"
      "movl %%ebx, (%%eax,%%ecx,1)\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "fstps (%%eax,%%edx,1)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fstps (%%eax,%%ecx,1)\n\t"
      "jmp .LFUN_00139c20_11\n\t"
      ".LFUN_00139c20_10:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00139c20_11:\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00139c20_12\n\t"
      "pushl $1\n\t"
      "pushl $0x67f\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00139c20_12:\n\t"
      "movl 0x5a8d64, %%eax\n\t"
      "cmpl %%eax, 0xc(%%esi)\n\t"
      "je .LFUN_00139c20_13\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      ".LFUN_00139c20_13:\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c191660]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .LFUN_00139c20_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_00139c20_14:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b139c20_assert), [exitfn] "m"(b139c20_exitfn), [c191a50] "m"(b139c20_c191a50), [dget] "m"(b139c20_dget), [tag] "m"(b139c20_tag), [c7a750] "m"(b139c20_c7a750), [c191660] "m"(b139c20_c191660)
      : "memory");
}
#else
#error "FUN_00139c20: clang naked draft required"
#endif


/* FUN_00139e50 (0x139e50) — XBE naked draft (batch 49). */
#if defined(__clang__)
static float (*const b139e50_c7a750)(float *color) = real_rgb_color_brightness;
static float (*const b139e50_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static void (*const b139e50_c139810)(float *color, float scale) = FUN_00139810;

__attribute__((naked, noinline))
void FUN_00139e50(unsigned int param_1 __attribute__((unused)), float *param_2 __attribute__((unused)), float *param_3 __attribute__((unused)), float param_4 __attribute__((unused)), float *color_ptr __attribute__((unused)), float *output_ptr __attribute__((unused)), float *intensity_ptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "call *%[c7a750]\n\t"
      "flds 0x323bfc\n\t"
      "fmuls (%%edi)\n\t"
      "movl %%edi, %%ecx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "fadds 0x323bf8\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x323bfc\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x323bf8\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x323bfc\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x323bf8\n\t"
      "movw $2, 0xc(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "leal 0x34(%%esi), %%edx\n\t"
      "fchs\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fchs\n\t"
      "fstps 0x20(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "fstps 0x24(%%esi)\n\t"
      "flds 0x323c00\n\t"
      "fmuls (%%ebx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps 0x28(%%esi)\n\t"
      "flds 0x323c00\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "flds 0x323c00\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "fmuls 0x2533ec\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "fadds 0x25337c\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_2\n\t"
      ".LFUN_00139e50_1:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_2:\n\t"
      "fstps 0x4c(%%esi)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls 0x254644\n\t"
      "fadds 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_4\n\t"
      ".LFUN_00139e50_3:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_4:\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fstps 0x50(%%esi)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls 0x254644\n\t"
      "fadds 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_6\n\t"
      ".LFUN_00139e50_5:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_6:\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fstps 0x54(%%esi)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls 0x254644\n\t"
      "fadds 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_8\n\t"
      ".LFUN_00139e50_7:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_8:\n\t"
      "fsts 0x58(%%esi)\n\t"
      "flds (%%edi)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x25337c\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_9\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_10\n\t"
      ".LFUN_00139e50_9:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_10\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_10:\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps 0x50(%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x25337c\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_11\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_12\n\t"
      ".LFUN_00139e50_11:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_12\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_12:\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps 0x54(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x25337c\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00139e50_14\n\t"
      ".LFUN_00139e50_13:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_14\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_14:\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps 0x58(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fldl 0x28c8d8\n\t"
      "call *%[c1d9e70]\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fstps 0x5c(%%esi)\n\t"
      "fmuls 0x20(%%esi)\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fstps 0x60(%%esi)\n\t"
      "flds 0x60(%%esi)\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x29b4d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_15\n\t"
      "fld %%st(0)\n\t"
      "fmulp %%st(1)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fsqrt\n\t"
      "fchs\n\t"
      "fstps 0x64(%%esi)\n\t"
      "jmp .LFUN_00139e50_16\n\t"
      ".LFUN_00139e50_15:\n\t"
      "fdivrs 0x29b4d0\n\t"
      "movl $0xbf34fdf4, 0x64(%%esi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps 0x5c(%%esi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps 0x60(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00139e50_16:\n\t"
      "flds 0x2533c8\n\t"
      "leal 0x10(%%esi), %%edx\n\t"
      "fsubs 0x14(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0x255b9c\n\t"
      "fsubrs 0x2533c8\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fcoms 0x323bf8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_17\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x323bf8\n\t"
      "jmp .LFUN_00139e50_18\n\t"
      ".LFUN_00139e50_17:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_18\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_18:\n\t"
      "fstps 0x68(%%esi)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fmuls 0x255b9c\n\t"
      "fsubrs 0x2533c8\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fcoms 0x323bf8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_19\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x323bf8\n\t"
      "jmp .LFUN_00139e50_20\n\t"
      ".LFUN_00139e50_19:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_20\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_20:\n\t"
      "fstps 0x6c(%%esi)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x255b9c\n\t"
      "fsubrs 0x2533c8\n\t"
      "faddp %%st(1)\n\t"
      "fcoms 0x323bf8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00139e50_21\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x323bf8\n\t"
      "jmp .LFUN_00139e50_22\n\t"
      ".LFUN_00139e50_21:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139e50_22\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139e50_22:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "fstps 0x70(%%esi)\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00139e50_23\n\t"
      "pushl $0x3e4ccccd\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c139810]\n\t"
      "pushl $0x3e99999a\n\t"
      "movl %%edx, %%ecx\n\t"
      "call *%[c139810]\n\t"
      "pushl $0x3e4ccccd\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "call *%[c139810]\n\t"
      "pushl $0x3f000000\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "call *%[c139810]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl $0x3f800000, 0x4c(%%esi)\n\t"
      ".LFUN_00139e50_23:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7a750] "m"(b139e50_c7a750), [c1d9e70] "m"(b139e50_c1d9e70), [c139810] "m"(b139e50_c139810)
      : "memory");
}
#else
#error "FUN_00139e50: clang naked draft required"
#endif


/* 0x13a740 — compute_object_lighting_from_bsp: computes BSP-based lighting
 * for an object, including lightmap sampling and dynamic light accumulation.
 *
 * Source: c:\halo\SOURCE\objects\object_lights.c
 * 3 cdecl params.
 */
/* FUN_0013a740 (0x13a740) — XBE naked draft (batch 58). */
#if defined(__clang__)
static char (*const b13a740_c198cb0)(float *point, float *direction, float *out_point, int16_t *out_collection_index, int16_t *out_material_index, int32_t *out_surface_index, float *out_u, float *out_v) = structure_test_vector;
static void * (*const b13a740_c18e3c0)(void) = scenario_get;
static void *(*const b13a740_elem)(void *, int, int) = tag_block_get_element;
static void * (*const b13a740_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static void (*const b13a740_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13a740_exitfn)(int) = system_exit;
static void *(*const b13a740_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static void (*const b13a740_c138fd0)(int material, int lightmap, unsigned short *vertex_indices, float u, float v, float *out_rgb) = FUN_00138fd0;
static void (*const b13a740_c139c20)(int object_handle, int16_t marker_index, float *position, float bias, int out_index_base, float *out_weights, int out_atten_base, int16_t *count, int16_t max_count) = FUN_00139c20;
static void *(*const b13a740_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
void FUN_0013a740(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), float *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x2ee710, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0x12(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29b204\n\t"
      "pushl %%ecx\n\t"
      "call *%[c198cb0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013a740_2\n\t"
      "call *%[c18e3c0]\n\t"
      "movswl 0x12(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x20\n\t"
      "pushl %%edx\n\t"
      "leal 0x104(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $0x100\n\t"
      "pushl %%ecx\n\t"
      "leal 0x14(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013a740_2\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0013a740_2\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c76ff0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "addl $0xf8, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movw 0xc4(%%edi), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_0013a740_1\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_0013a740_1\n\t"
      "pushl $1\n\t"
      "pushl $0x356\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b268\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013a740_1:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[xtex]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013a740_2\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c138fd0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_0013a740_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpw $-1, 0x4(%%edi)\n\t"
      "je .LFUN_0013a740_7\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "je .LFUN_0013a740_3\n\t"
      "pushl $1\n\t"
      "pushl $0x664\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013a740_3:\n\t"
      "movl 0x5a8d64, %%eax\n\t"
      "pushl $2\n\t"
      "incl %%eax\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x5a8d64\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $1, 0x5a8d60\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "call *%[c139c20]\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013a740_4\n\t"
      "pushl $1\n\t"
      "pushl $0x68e\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013a740_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $0, 0x5a8d60\n\t"
      "jle .LFUN_0013a740_7\n\t"
      "xorl %%edi, %%edi\n\t"
      "movzwl %%ax, %%ebx\n\t"
      ".LFUN_0013a740_5:\n\t"
      "movl -0x1c(%%ebp,%%edi,1), %%ecx\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_0013a740_6\n\t"
      "flds 0x14(%%eax)\n\t"
      "fmuls -0x24(%%ebp,%%edi,1)\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x18(%%eax)\n\t"
      "fmuls -0x24(%%ebp,%%edi,1)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x1c(%%eax)\n\t"
      "fmuls -0x24(%%ebp,%%edi,1)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      ".LFUN_0013a740_6:\n\t"
      "addl $4, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0013a740_5\n\t"
      ".LFUN_0013a740_7:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a740_8\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_0013a740_10\n\t"
      ".LFUN_0013a740_8:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0013a740_9\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_0013a740_10\n\t"
      ".LFUN_0013a740_9:\n\t"
      "flds (%%esi)\n\t"
      ".LFUN_0013a740_10:\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a740_11\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_0013a740_13\n\t"
      ".LFUN_0013a740_11:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0013a740_12\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_0013a740_13\n\t"
      ".LFUN_0013a740_12:\n\t"
      "flds 0x4(%%esi)\n\t"
      ".LFUN_0013a740_13:\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a740_14\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013a740_14:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0013a740_15\n\t"
      "popl %%edi\n\t"
      "movl $0x3f800000, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013a740_15:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c198cb0] "m"(b13a740_c198cb0), [c18e3c0] "m"(b13a740_c18e3c0), [elem] "m"(b13a740_elem), [c76ff0] "m"(b13a740_c76ff0), [assert] "m"(b13a740_assert), [exitfn] "m"(b13a740_exitfn), [xtex] "m"(b13a740_xtex), [c138fd0] "m"(b13a740_c138fd0), [c139c20] "m"(b13a740_c139c20), [dget] "m"(b13a740_dget)
      : "memory");
}
#else
#error "FUN_0013a740: clang naked draft required"
#endif


/* 0x13ab20 — compute_dynamic_object_lighting: computes dynamic lighting for
 * objects using BSP ray casting, lightmap sampling, and shader lookups.
 *
 * Source: c:\halo\SOURCE\objects\object_lights.c
 * 3 cdecl params. Returns char (bool).
 */
/* FUN_0013ab20 (0x13ab20) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void * (*const b13ab20_c18e3c0)(void) = scenario_get;
static char (*const b13ab20_c198cb0)(float *point, float *direction, float *out_point, int16_t *out_collection_index, int16_t *out_material_index, int32_t *out_surface_index, float *out_u, float *out_v) = structure_test_vector;
static void *(*const b13ab20_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b13ab20_tag)(int, int) = tag_get;
static void * (*const b13ab20_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void * (*const b13ab20_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static int (*const b13ab20_c138ee0)(int hardware_format) = FUN_00138ee0;
static void (*const b13ab20_c1390d0)(int material, int bitmap_ref, uint16_t *indices, float bary_u, float bary_v, float *out_rgb) = FUN_001390d0;
static void (*const b13ab20_c138fd0)(int material, int lightmap, unsigned short *vertex_indices, float u, float v, float *out_rgb) = FUN_00138fd0;
static void (*const b13ab20_c180570)(int param_1, float *param_2) = FUN_00180570;
static void (*const b13ab20_c138f70)(float *output, float *vertex_c, float *vertex_d, float *base, float u, float v) = FUN_00138f70;
static float (*const b13ab20_norm)(float *) = normalize3d;
static void (*const b13ab20_c180660)(unsigned int *param_1, float *param_2) = FUN_00180660;
static void (*const b13ab20_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static void (*const b13ab20_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;
static void (*const b13ab20_c139e50)(unsigned int param_1, float *param_2, float *param_3, float param_4, float *color_ptr, float *output_ptr, float *intensity_ptr) = FUN_00139e50;

__attribute__((naked, noinline))
char FUN_0013ab20(unsigned int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x90, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c18e3c0]\n\t"
      "flds 0x2c(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "leal 0x2c(%%eax), %%esi\n\t"
      "movl $0x1d, %%ecx\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0013ab20_1\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "rep movsl\n\t"
      "movw $2, 0xc(%%eax)\n\t"
      "jmp .LFUN_0013ab20_2\n\t"
      ".LFUN_0013ab20_1:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl $0x29b190, %%esi\n\t"
      "rep movsl\n\t"
      ".LFUN_0013ab20_2:\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "je .LFUN_0013ab20_3\n\t"
      "movl $0x29b210, %%edi\n\t"
      "movl $4, %%ebx\n\t"
      "jmp .LFUN_0013ab20_4\n\t"
      ".LFUN_0013ab20_3:\n\t"
      "movl $0x29b204, %%edi\n\t"
      "movl $1, %%ebx\n\t"
      ".LFUN_0013ab20_4:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_0013ab20_8\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0013ab20_5:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl %%si, %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%edi,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c198cb0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013ab20_6\n\t"
      "incl %%esi\n\t"
      "cmpw %%bx, %%si\n\t"
      "jl .LFUN_0013ab20_5\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013ab20_6:\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl -0x18(%%ebp), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "leal 0x104(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movswl -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "leal 0x14(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x73686472\n\t"
      "call *%[tag]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $3, 0x24(%%eax)\n\t"
      "jne .LFUN_0013ab20_8\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "cmpw %%cx, (%%ebx)\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "cmpl %%ecx, 0x94(%%eax)\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "pushl $6\n\t"
      "pushl %%edx\n\t"
      "leal 0xf8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c76ff0]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x94(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6269746d\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movswl 0x10(%%edi), %%eax\n\t"
      "cdq\n\t"
      "idivl 0x60(%%ecx)\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x94(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c76ff0]\n\t"
      "addl $0x24, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "pushl %%esi\n\t"
      "call *%[c138ee0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c138ee0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013ab20_8\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1390d0]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c138fd0]\n\t"
      "movzwl (%%ebx), %%ecx\n\t"
      "movl 0xf8(%%edi), %%esi\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "shll $5, %%ecx\n\t"
      "pushl %%eax\n\t"
      "addl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180570]\n\t"
      "movzwl 0x2(%%ebx), %%eax\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0xf8(%%edi), %%edx\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180570]\n\t"
      "movzwl 0x4(%%ebx), %%edx\n\t"
      "movl 0xf8(%%edi), %%esi\n\t"
      "addl $0x40, %%esp\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "shll $5, %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180570]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "leal -0x60(%%ebp), %%esi\n\t"
      "call *%[c138f70]\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movzwl (%%ebx), %%edx\n\t"
      "movl 0xb4(%%edi), %%ecx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal (%%edx,%%ecx,4), %%eax\n\t"
      "movl 0xf8(%%edi), %%ecx\n\t"
      "leal (%%ecx,%%eax,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180660]\n\t"
      "movzwl 0x2(%%ebx), %%edx\n\t"
      "movl 0xb4(%%edi), %%ecx\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal (%%edx,%%ecx,4), %%eax\n\t"
      "movl 0xf8(%%edi), %%ecx\n\t"
      "leal (%%ecx,%%eax,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180660]\n\t"
      "movl 0xb4(%%edi), %%ecx\n\t"
      "movzwl 0x4(%%ebx), %%edx\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal (%%edx,%%ecx,4), %%eax\n\t"
      "movl 0xf8(%%edi), %%ecx\n\t"
      "leal (%%ecx,%%eax,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180660]\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "leal -0x60(%%ebp), %%esi\n\t"
      "call *%[c138f70]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "movb 0x5a8d59, %%al\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013ab20_7\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f000000\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl $0x3f800000, -0x2c(%%ebp)\n\t"
      "call *%[c189150]\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_0013ab20_7:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x78(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3c(%%ebp), %%edi\n\t"
      "leal -0x84(%%ebp), %%ebx\n\t"
      "call *%[c139e50]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_0013ab20_8:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b13ab20_c18e3c0), [c198cb0] "m"(b13ab20_c198cb0), [elem] "m"(b13ab20_elem), [tag] "m"(b13ab20_tag), [c1906b0] "m"(b13ab20_c1906b0), [c76ff0] "m"(b13ab20_c76ff0), [c138ee0] "m"(b13ab20_c138ee0), [c1390d0] "m"(b13ab20_c1390d0), [c138fd0] "m"(b13ab20_c138fd0), [c180570] "m"(b13ab20_c180570), [c138f70] "m"(b13ab20_c138f70), [norm] "m"(b13ab20_norm), [c180660] "m"(b13ab20_c180660), [c189150] "m"(b13ab20_c189150), [c189320] "m"(b13ab20_c189320), [c139e50] "m"(b13ab20_c139e50)
      : "memory");
}
#else
#error "FUN_0013ab20: clang naked draft required"
#endif


/* 0x13b380 — render_lights: main per-frame light processing function.
 * Iterates all active lights, updates colors/positions, submits to renderer.
 *
 * Source: c:\halo\SOURCE\objects\object_lights.c
 * No params.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
/* FUN_0013b380 (0x13b380) — XBE naked draft (batch 48). */
#if defined(__clang__)
static int (*const b13b380_gtime)(void) = game_time_get;
static void (*const b13b380_penter)(void *) = profile_enter_private;
static int (*const b13b380_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b13b380_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13b380_tag)(int, int) = tag_get;
static void (*const b13b380_c1919a0)(void *partition, int object_handle, void *first_cluster_ref) = cluster_partition_remove_object;
static void (*const b13b380_c1196d0)(data_t *data, int datum_handle) = datum_delete;
static void *(*const b13b380_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b13b380_c1396e0)(int object_handle) = object_wake;
static void (*const b13b380_c13aed0)(int object_handle) = object_move_to_limbo;
static void (*const b13b380_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13b380_exitfn)(int) = system_exit;
static short (*const b13b380_c196c90)(int out_handles, short max_count, void *iter_first, void *iter_next, void *get_bounds, void *needs_update, void *mark) = FUN_00196c90;
static void (*const b13b380_c1812b0)(void) = FUN_001812b0;
static void * (*const b13b380_c184e50)(int rendered_cluster_index) = rendered_cluster_get;
static void (*const b13b380_c181900)(short param_1) = FUN_00181900;
static void (*const b13b380_c139a30)(int param_1) = FUN_00139a30;
static bool (*const b13b380_c1403a0)(int object_handle, short function_index, void *out_value) = object_get_function_value;
static void (*const b13b380_c7c490)(void) = FUN_0007c490;
static float (*const b13b380_c10a710)(short function_type, float t) = transition_function_evaluate;
static float * (*const b13b380_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;
static int (*const b13b380_c13d7f0)(int object_handle) = object_get_root_parent;
static void *(*const b13b380_get)(int, int) = object_get_and_verify_type;
static void (*const b13b380_cdd260)(int object_handle, float *out_position, float *out_forward, float *out_up) = first_person_weapon_center_flashlight;
static void * (*const b13b380_c13fea0)(int object_handle, int16_t marker_index) = object_get_child_marker_definition;
static char (*const b13b380_cdd340)(int object_handle, int marker_result, void *out_position, void *out_forward, void *out_up) = first_person_weapon_adjust_light;
static void (*const b13b380_c1812c0)(void) = FUN_001812c0;
static uint32_t (*const b13b380_c99530)(float alpha, float *color) = real_a_rgb_color_to_pixel32;
static unsigned char (*const b13b380_c180770)(float alpha) = FUN_00180770;
static int16_t (*const b13b380_cddb90)(int object_handle, const char *marker_name, void *out_markers, int16_t max_markers) = first_person_weapon_get_marker_by_name_render;
static short (*const b13b380_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static unsigned int (*const b13b380_c180b10)(float *param_1) = FUN_00180b10;
static void (*const b13b380_c181670)(int *params) = FUN_00181670;
static void (*const b13b380_c181410)(void) = FUN_00181410;
static void (*const b13b380_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
void FUN_0013b380(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3dc, %%esp\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013b380_1\n\t"
      "movb 0x323608, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013b380_1\n\t"
      "pushl $0x323600\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013b380_1:\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movw $0, 0x5a8d5a\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_0013b380_5\n\t"
      ".LFUN_0013b380_2:\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "andb $0xf7, 0x2(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%ebx, 0x8(%%esi)\n\t"
      "je .LFUN_0013b380_4\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "subl 0x58(%%esi), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0xf4(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0013b380_3\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $0x10, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c1919a0]\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1196d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_0013b380_4\n\t"
      ".LFUN_0013b380_3:\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013b380_4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1396e0]\n\t"
      "pushl %%edi\n\t"
      "call *%[c13aed0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013b380_4:\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_0013b380_2\n\t"
      ".LFUN_0013b380_5:\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013b380_6\n\t"
      "pushl $1\n\t"
      "pushl $0x664\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b488\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_6:\n\t"
      "movl 0x5a8d64, %%edi\n\t"
      "pushl $0x139990\n\t"
      "pushl $0x139930\n\t"
      "pushl $0x13a340\n\t"
      "pushl $0x1398d0\n\t"
      "pushl $0x1398b0\n\t"
      "pushl $0x80\n\t"
      "incl %%edi\n\t"
      "pushl $0x5a8d6c\n\t"
      "movl %%edi, 0x5a8d64\n\t"
      "movb $1, 0x5a8d60\n\t"
      "call *%[c196c90]\n\t"
      "movw %%ax, 0x5a8d68\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013b380_7\n\t"
      "pushl $1\n\t"
      "pushl $0x68e\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_7:\n\t"
      "movb $0, 0x5a8d60\n\t"
      "call *%[c1812b0]\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x5137cc\n\t"
      "jle .LFUN_0013b380_9\n\t"
      ".LFUN_0013b380_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[c184e50]\n\t"
      "movswl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c181900]\n\t"
      "addl $8, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw 0x5137cc, %%si\n\t"
      "jl .LFUN_0013b380_8\n\t"
      ".LFUN_0013b380_9:\n\t"
      "cmpw $0, 0x5a8d68\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_0013b380_51\n\t"
      "jmp .LFUN_0013b380_10\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_0013b380_10:\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x5a8d6c(,%%ecx,4), %%edi\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, -0x44(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "call *%[c139a30]\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013b380_11\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_0013b380_12\n\t"
      ".LFUN_0013b380_11:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_0013b380_12:\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "jne .LFUN_0013b380_16\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0013b380_13\n\t"
      "pushl $1\n\t"
      "pushl $0x1ac\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x26b758\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_13:\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x5e(%%esi), %%dx\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1403a0]\n\t"
      "movw 0x60(%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0013b380_14\n\t"
      "movl 0x2ee708, %%eax\n\t"
      "jmp .LFUN_0013b380_15\n\t"
      ".LFUN_0013b380_14:\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $0x1e, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edi,%%ecx,4), %%eax\n\t"
      ".LFUN_0013b380_15:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x48(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x38(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x14(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c490]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_0013b380_17\n\t"
      ".LFUN_0013b380_16:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xfa(%%ebx), %%dx\n\t"
      "pushl %%ecx\n\t"
      "fdivs 0xf4(%%ebx)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a710]\n\t"
      "fsubrs 0x2533c8\n\t"
      "leal 0x4c(%%ebx), %%ecx\n\t"
      "leal 0x3c(%%ebx), %%edx\n\t"
      "fmuls 0x78(%%esi)\n\t"
      "leal 0x14(%%esi), %%edi\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c270]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_0013b380_17:\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_18\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_19\n\t"
      ".LFUN_0013b380_18:\n\t"
      "pushl $1\n\t"
      "pushl $0x1bb\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b5ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_19:\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_20\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_21\n\t"
      ".LFUN_0013b380_20:\n\t"
      "pushl $1\n\t"
      "pushl $0x1bc\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b574\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_21:\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_22\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_23\n\t"
      ".LFUN_0013b380_22:\n\t"
      "pushl $1\n\t"
      "pushl $0x1bd\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b53c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_23:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0013b380_30\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d7f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x64(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $3, %%dl\n\t"
      "je .LFUN_0013b380_30\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "flds 0x32c(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0013b380_30\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x20, %%cl\n\t"
      "jne .LFUN_0013b380_30\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x32c(%%edi)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "fsts 0x14(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "fstps 0x18(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_24\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_26\n\t"
      "jmp .LFUN_0013b380_25\n\t"
      ".LFUN_0013b380_24:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0013b380_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x1d1\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b5ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_26:\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_27\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_28\n\t"
      ".LFUN_0013b380_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x1d2\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b574\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_28:\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_29\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_30\n\t"
      ".LFUN_0013b380_29:\n\t"
      "pushl $1\n\t"
      "pushl $0x1d3\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b53c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_30:\n\t"
      "flds 0x14(%%esi)\n\t"
      "leal 0x14(%%esi), %%edi\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0013b380_31\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0013b380_31\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0013b380_50\n\t"
      ".LFUN_0013b380_31:\n\t"
      "testb $1, 0x2(%%esi)\n\t"
      "je .LFUN_0013b380_41\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fsts 0x54(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0013b380_42\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, -0x7c(%%ebp)\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "movl %%ecx, -0x74(%%ebp)\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "leal 0x48(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl 0x54(%%esi), %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%ah\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "jne .LFUN_0013b380_32\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_33\n\t"
      ".LFUN_0013b380_32:\n\t"
      "pushl $1\n\t"
      "pushl $0x1ee\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b5ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_33:\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_34\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_35\n\t"
      ".LFUN_0013b380_34:\n\t"
      "pushl $1\n\t"
      "pushl $0x1ef\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b574\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_35:\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0013b380_36\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0013b380_37\n\t"
      ".LFUN_0013b380_36:\n\t"
      "pushl $1\n\t"
      "pushl $0x1f0\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b53c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_37:\n\t"
      "cmpl $-1, 0x58(%%esi)\n\t"
      "jne .LFUN_0013b380_40\n\t"
      "testb $0x10, (%%ebx)\n\t"
      "je .LFUN_0013b380_38\n\t"
      "leal -0x60(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cdd260]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0013b380_39\n\t"
      ".LFUN_0013b380_38:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "cmpw $2, 0x64(%%eax)\n\t"
      "jne .LFUN_0013b380_40\n\t"
      "cmpl $-1, 0xcc(%%eax)\n\t"
      "je .LFUN_0013b380_40\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x5c(%%esi), %%dx\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "leal -0x78(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c13fea0]\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cdd340]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013b380_40\n\t"
      ".LFUN_0013b380_39:\n\t"
      "orb $8, 0x2(%%esi)\n\t"
      ".LFUN_0013b380_40:\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1812c0]\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x5a8d5a\n\t"
      "jmp .LFUN_0013b380_42\n\t"
      ".LFUN_0013b380_41:\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x54(%%esi)\n\t"
      ".LFUN_0013b380_42:\n\t"
      "movl 0xb8(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013b380_50\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6c656e73\n\t"
      "call *%[tag]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "leal 0x14(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180770]\n\t"
      "movb 0x50654a, %%cl\n\t"
      "movb %%al, -0x1d(%%ebp)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movw %%ax, -0x22(%%ebp)\n\t"
      "sarl $0x10, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "movb %%cl, -0x1e(%%ebp)\n\t"
      "movw %%ax, -0x24(%%ebp)\n\t"
      "jne .LFUN_0013b380_43\n\t"
      "pushl $1\n\t"
      "pushl $0x21c\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movw -0x24(%%ebp), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013b380_43:\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jne .LFUN_0013b380_44\n\t"
      "movw %%di, -0x24(%%ebp)\n\t"
      ".LFUN_0013b380_44:\n\t"
      "cmpl %%ebx, 0x58(%%esi)\n\t"
      "jne .LFUN_0013b380_49\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x5c(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c13fea0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x64(%%eax)\n\t"
      "jne .LFUN_0013b380_46\n\t"
      "cmpl %%ebx, 0xcc(%%eax)\n\t"
      "je .LFUN_0013b380_46\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "pushl $8\n\t"
      "leal -0x3dc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[cddb90]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_0013b380_45\n\t"
      "orb $0x80, -0x1e(%%ebp)\n\t"
      "testw %%bx, %%bx\n\t"
      ".LFUN_0013b380_45:\n\t"
      "jne .LFUN_0013b380_47\n\t"
      ".LFUN_0013b380_46:\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl $8\n\t"
      "leal -0x3dc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_0013b380_47:\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_0013b380_50\n\t"
      "leal -0x3a0(%%ebp), %%esi\n\t"
      ".LFUN_0013b380_48:\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movw %%di, -0x20(%%ebp)\n\t"
      "call *%[c181670]\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%edi\n\t"
      "addl $0x6c, %%esi\n\t"
      "cmpw %%bx, %%di\n\t"
      "jl .LFUN_0013b380_48\n\t"
      "jmp .LFUN_0013b380_50\n\t"
      ".LFUN_0013b380_49:\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "call *%[c180b10]\n\t"
      "addl $0x48, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "call *%[c180b10]\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movw %%di, -0x20(%%ebp)\n\t"
      "call *%[c181670]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0013b380_50:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x5a8d68, %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_0013b380_10\n\t"
      ".LFUN_0013b380_51:\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x5a90ac\n\t"
      "jle .LFUN_0013b380_53\n\t"
      "jmp .LFUN_0013b380_52\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013b380_52:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal 0x5a8f6c(,%%edx,8), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c181670]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw 0x5a90ac, %%si\n\t"
      "jl .LFUN_0013b380_52\n\t"
      ".LFUN_0013b380_53:\n\t"
      "movw $0, 0x5a90ac\n\t"
      "call *%[c181410]\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0013b380_54\n\t"
      "movb 0x323608, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013b380_54\n\t"
      "pushl $0x323600\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013b380_54:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b13b380_gtime), [penter] "m"(b13b380_penter), [c1198f0] "m"(b13b380_c1198f0), [dget] "m"(b13b380_dget), [tag] "m"(b13b380_tag), [c1919a0] "m"(b13b380_c1919a0), [c1196d0] "m"(b13b380_c1196d0), [tryget] "m"(b13b380_tryget), [c1396e0] "m"(b13b380_c1396e0), [c13aed0] "m"(b13b380_c13aed0), [assert] "m"(b13b380_assert), [exitfn] "m"(b13b380_exitfn), [c196c90] "m"(b13b380_c196c90), [c1812b0] "m"(b13b380_c1812b0), [c184e50] "m"(b13b380_c184e50), [c181900] "m"(b13b380_c181900), [c139a30] "m"(b13b380_c139a30), [c1403a0] "m"(b13b380_c1403a0), [c7c490] "m"(b13b380_c7c490), [c10a710] "m"(b13b380_c10a710), [c7c270] "m"(b13b380_c7c270), [c13d7f0] "m"(b13b380_c13d7f0), [get] "m"(b13b380_get), [cdd260] "m"(b13b380_cdd260), [c13fea0] "m"(b13b380_c13fea0), [cdd340] "m"(b13b380_cdd340), [c1812c0] "m"(b13b380_c1812c0), [c99530] "m"(b13b380_c99530), [c180770] "m"(b13b380_c180770), [cddb90] "m"(b13b380_cddb90), [markers] "m"(b13b380_markers), [c180b10] "m"(b13b380_c180b10), [c181670] "m"(b13b380_c181670), [c181410] "m"(b13b380_c181410), [pexit] "m"(b13b380_pexit)
      : "memory");
}
#else
#error "FUN_0013b380: clang naked draft required"
#endif
#pragma clang diagnostic pop

/* 0x13cf50 — object_placement_update: creates or destroys objects based on
 * scenario placement changes. Contains goto patterns for create/recreate.
 *
 * Source: c:\halo\SOURCE\objects\object_types.c
 * 5 cdecl params. Returns int (object handle).
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wuninitialized"
/* FUN_0013cf50 (0x13cf50) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void (*const b13cf50_odel)(int) = object_delete;
static void *(*const b13cf50_elem)(void *, int, int) = tag_block_get_element;
static void (*const b13cf50_opnew)(void *, int, int) = object_placement_data_new;
static void (*const b13cf50_c10bbc0)(float *forward, float *up, float *angles) = vectors3d_from_euler_angles3d;
static void *(*const b13cf50_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const b13cf50_onew)(void *) = object_new;
static void (*const b13cf50_c13c500)(int param_1, int param_2) = FUN_0013c500;
static void *(*const b13cf50_get)(int, int) = object_get_and_verify_type;
static void (*const b13cf50_c13fb30)(int object_handle) = object_activate;
static void (*const b13cf50_c109e90)(float *out, float yaw, float pitch, float roll) = FUN_00109e90;
static char (*const b13cf50_cf6d00)(float *mat) = valid_real_matrix4x3;
static char * (*const b13cf50_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b13cf50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13cf50_exitfn)(int) = system_exit;
static bool (*const b13cf50_c21fb0)(float *v) = valid_real_normal3d;
static bool (*const b13cf50_ca16b0)(float *point) = valid_real_point3d;
static void *(*const b13cf50_tag)(int, int) = tag_get;
static void (*const b13cf50_c143ae0)(int object_handle, float *position, float *forward, float *up) = object_set_position;
static scenario_t * (*const b13cf50_c18e380)(void) = global_scenario_get;
static void (*const b13cf50_c13d880)(int16_t param_1, int param_2) = object_name_list_set_handle;

__attribute__((naked, noinline))
int FUN_0013cf50(int param_1 __attribute__((unused)), short *param_2 __attribute__((unused)), int param_3 __attribute__((unused)), short param_4 __attribute__((unused)), short param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0013cf50_1\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0013cf50_23\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "jmp .LFUN_0013cf50_23\n\t"
      ".LFUN_0013cf50_1:\n\t"
      "cmpl $-1, %%esi\n\t"
      "pushl %%ebx\n\t"
      "jne .LFUN_0013cf50_2\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_0013cf50_22\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[opnew]\n\t"
      "leal 0x8(%%edi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0xb0(%%ebp)\n\t"
      "leal 0x14(%%edi), %%ecx\n\t"
      "movl %%edx, -0xac(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "movl %%eax, -0xa8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10bbc0]\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "leal -0xc8(%%ebp), %%edx\n\t"
      "movw %%cx, -0xb2(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_0013cf50_4\n\t"
      ".LFUN_0013cf50_2:\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movswl (%%edi), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_0013cf50_3\n\t"
      "movl (%%ebx), %%edx\n\t"
      "cmpl 0xc(%%eax), %%edx\n\t"
      "je .LFUN_0013cf50_5\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0013cf50_3:\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0013cf50_22\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "leal 0x8(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0xb0(%%ebp)\n\t"
      "leal 0x14(%%edi), %%edx\n\t"
      "movl %%eax, -0xac(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xa8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10bbc0]\n\t"
      "movw 0x6(%%edi), %%dx\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "movw %%dx, -0xb2(%%ebp)\n\t"
      "pushl %%eax\n\t"
      ".LFUN_0013cf50_4:\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0013cf50_22\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c13c500]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0013cf50_5:\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c13fb30]\n\t"
      "movl 0x1c(%%edi), %%ecx\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109e90]\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cf6d00]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cf50_20\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jne .LFUN_0013cf50_6\n\t"
      "flds -0x34(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bd6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_6:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cf50_7\n\t"
      "flds -0x28(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bd4c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_7:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cf50_8\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bd2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_8:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cf50_9\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bd10\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_9:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cf50_10\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bcec\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_10:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .LFUN_0013cf50_11\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0013cf50_13\n\t"
      "jmp .LFUN_0013cf50_12\n\t"
      ".LFUN_0013cf50_11:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0013cf50_12:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bca8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_13:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .LFUN_0013cf50_14\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0013cf50_16\n\t"
      "jmp .LFUN_0013cf50_15\n\t"
      ".LFUN_0013cf50_14:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0013cf50_15:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bc6c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_16:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .LFUN_0013cf50_17\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0013cf50_19\n\t"
      "jmp .LFUN_0013cf50_18\n\t"
      ".LFUN_0013cf50_17:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0013cf50_18:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bc2c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_19:\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cf6d00]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013cf50_20\n\t"
      "pushl $1\n\t"
      "pushl $0x3cf\n\t"
      "pushl $0x29b6b8\n\t"
      "pushl $0x29b860\n\t"
      "pushl $0x28bc0c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_20:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x8c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "leal 0x8(%%edi), %%edx\n\t"
      "je .LFUN_0013cf50_21\n\t"
      "movl (%%edx), %%eax\n\t"
      "flds 0x5c(%%ebx)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "fmuls 0x253398\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "fstps -0x38(%%ebp)\n\t"
      ".LFUN_0013cf50_21:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c143ae0]\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%ax, 0x6a(%%ebx)\n\t"
      ".LFUN_0013cf50_22:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0013cf50_23:\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0013cf50_24\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0x24\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x204, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x14(%%ebp), %%dx\n\t"
      "movw 0x18(%%ebp), %%cx\n\t"
      "movw %%dx, 0x20(%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw %%cx, 0x22(%%eax)\n\t"
      "movw 0x2(%%edi), %%dx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d880]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013cf50_24:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [odel] "m"(b13cf50_odel), [elem] "m"(b13cf50_elem), [opnew] "m"(b13cf50_opnew), [c10bbc0] "m"(b13cf50_c10bbc0), [tryget] "m"(b13cf50_tryget), [onew] "m"(b13cf50_onew), [c13c500] "m"(b13cf50_c13c500), [get] "m"(b13cf50_get), [c13fb30] "m"(b13cf50_c13fb30), [c109e90] "m"(b13cf50_c109e90), [cf6d00] "m"(b13cf50_cf6d00), [c8d9d0] "m"(b13cf50_c8d9d0), [assert] "m"(b13cf50_assert), [exitfn] "m"(b13cf50_exitfn), [c21fb0] "m"(b13cf50_c21fb0), [ca16b0] "m"(b13cf50_ca16b0), [tag] "m"(b13cf50_tag), [c143ae0] "m"(b13cf50_c143ae0), [c18e380] "m"(b13cf50_c18e380), [c13d880] "m"(b13cf50_c13d880)
      : "memory");
}
#else
#error "FUN_0013cf50: clang naked draft required"
#endif

#pragma clang diagnostic pop

/* 0x13f4b0 — objects_dump_memory: diagnostic memory dump of all objects,
 * grouped by type and definition. Writes to a file.
 *
 * Source: objects.c
 * No params. Has 768KB+ stack for large arrays (_chkstk handles this).
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
/* objects_dump_memory (0x13f4b0) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void (*const b13f4b0_chkstk)(void) = FUN_001d90e0;
static void *(*const b13f4b0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b13f4b0_c1193f0)(data_t *data) = data_verify;
static void * (*const b13f4b0_c13d730)(void *iter) = object_iterator_next;
static void *(*const b13f4b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b13f4b0_c13f3b0)(int object_handle, void *stats) = object_add_to_dump;
static void (*const b13f4b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13f4b0_exitfn)(int) = system_exit;
static void __cdecl (*const b13f4b0_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static void * (*const b13f4b0_c1d9e59)(const char *filename, const char *mode) = crt_fopen;
static void (*const b13f4b0_c13db60)(short *param_1) = FUN_0013db60;
static int (*const b13f4b0_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static const char * (*const b13f4b0_c1ba1f0)(int tag_index) = tag_get_name;
static void * (*const b13f4b0_c13c250)(int16_t param_1) = FUN_0013c250;
static int (*const b13f4b0_c1d9dac)(void *stream) = crt_fclose;
static void (*const b13f4b0_c136580)(void) = widgets_initialize_for_new_map;
static void (*const b13f4b0_c135f90)(void) = FUN_00135f90;
static void (*const b13f4b0_c13c2e0)(void) = FUN_0013c2e0;
static void (*const b13f4b0_c1391e0)(void) = lights_initialize;
static bool (*const b13f4b0_c977f0)(void) = game_in_editor;
static data_t * (*const b13f4b0_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void * (*const b13f4b0_c1bfe50)(const char *name, int pool_config) = game_state_memory_pool_new;
static data_t * (*const b13f4b0_c1194d0)(char *name, int16_t maximum_count, int16_t size) = data_new;
static void * (*const b13f4b0_c11e650)(const char *name, int pool_config) = memory_pool_new;
static void * (*const b13f4b0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const b13f4b0_c191500)(void **out, const char *name) = cluster_partition_globals_new;
static void (*const b13f4b0_c1365a0)(void) = widgets_dispose;
static void (*const b13f4b0_c136040)(void) = FUN_00136040;
static void (*const b13f4b0_c13c3d0)(void) = FUN_0013c3d0;
static void (*const b13f4b0_c1392b0)(void) = lights_initialize_for_new_map;
static void (*const b13f4b0_c119b20)(data_t *data) = data_delete_all;
static void (*const b13f4b0_c1915d0)(void *partition) = cluster_partition_clear;

__attribute__((naked, noinline))
void objects_dump_memory(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x613c, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl $0x6000\n\t"
      "leal -0x613c(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "pushl $0x120\n\t"
      "leal -0x13c(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0x18, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x13c(%%ebp), %%ecx\n\t"
      "jmp .Lobjects_dump_memory_1\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobjects_dump_memory_1:\n\t"
      "movw %%ax, 0x4(%%ecx)\n\t"
      "movl $0xffffffff, (%%ecx)\n\t"
      "incl %%eax\n\t"
      "addl $0x18, %%ecx\n\t"
      "cmpw $0xc, %%ax\n\t"
      "jl .Lobjects_dump_memory_1\n\t"
      "movl 0x5a8d50, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1193f0]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x86868686, -0x10(%%ebp)\n\t"
      "movb $0, -0x18(%%ebp)\n\t"
      "movw %%di, -0x16(%%ebp)\n\t"
      "call *%[c13d730]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lobjects_dump_memory_10\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobjects_dump_memory_2:\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lobjects_dump_memory_5\n\t"
      "movl (%%eax), %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobjects_dump_memory_3:\n\t"
      "movswl %%cx, %%edx\n\t"
      "leal (%%edx,%%edx,2), %%edx\n\t"
      "cmpl %%ebx, -0x613c(%%ebp,%%edx,8)\n\t"
      "je .Lobjects_dump_memory_4\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .Lobjects_dump_memory_3\n\t"
      "jmp .Lobjects_dump_memory_5\n\t"
      ".Lobjects_dump_memory_4:\n\t"
      "cmpw $-1, %%cx\n\t"
      "movl %%ecx, %%esi\n\t"
      "jne .Lobjects_dump_memory_7\n\t"
      ".Lobjects_dump_memory_5:\n\t"
      "cmpw $0x400, %%di\n\t"
      "jge .Lobjects_dump_memory_6\n\t"
      "movl %%edi, %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "incl %%edi\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "shll $3, %%ecx\n\t"
      "movw $0xffff, -0x6138(%%ebp,%%ecx,1)\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x613c(%%ebp,%%ecx,1)\n\t"
      "jmp .Lobjects_dump_memory_7\n\t"
      ".Lobjects_dump_memory_6:\n\t"
      "incl -0xc(%%ebp)\n\t"
      ".Lobjects_dump_memory_7:\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%si\n\t"
      "movl %%eax, %%edi\n\t"
      "je .Lobjects_dump_memory_8\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%esi\n\t"
      "leal -0x613c(%%ebp,%%esi,8), %%esi\n\t"
      "call *%[c13f3b0]\n\t"
      ".Lobjects_dump_memory_8:\n\t"
      "cmpb $0xc, 0x3(%%edi)\n\t"
      "jb .Lobjects_dump_memory_9\n\t"
      "pushl $1\n\t"
      "pushl $0x1329\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29be58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_dump_memory_9:\n\t"
      "movzbl 0x3(%%edi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%esi\n\t"
      "leal -0x13c(%%ebp,%%esi,8), %%esi\n\t"
      "call *%[c13f3b0]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lobjects_dump_memory_2\n\t"
      ".Lobjects_dump_memory_10:\n\t"
      "pushl $0x13f380\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "leal -0x613c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9260]\n\t"
      "pushl $0x13f380\n\t"
      "pushl $0x18\n\t"
      "leal -0x13c(%%ebp), %%edx\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9260]\n\t"
      "pushl $0x267f84\n\t"
      "pushl $0x29be40\n\t"
      "call *%[c1d9e59]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x28, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lobjects_dump_memory_21\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13db60]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "movswl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movswl -0x6(%%ebp), %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x29be00\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "pushl $0x29bdec\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "pushl $0x29bda8\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x28, %%esp\n\t"
      "leal -0x138(%%ebp), %%esi\n\t"
      "movl $0xc, -0x4(%%ebp)\n\t"
      ".Lobjects_dump_memory_11:\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl $0x254608, %%eax\n\t"
      "je .Lobjects_dump_memory_12\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "jmp .Lobjects_dump_memory_13\n\t"
      ".Lobjects_dump_memory_12:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lobjects_dump_memory_14\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c250]\n\t"
      ".Lobjects_dump_memory_13:\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_dump_memory_14:\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movswl 0x12(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl 0x10(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0xe(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0xc(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0xa(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29bcf4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x2c, %%esp\n\t"
      "addl $0x18, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lobjects_dump_memory_11\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "pushl $0x29bd8c\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "pushl $0x29bda8\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lobjects_dump_memory_19\n\t"
      "leal -0x6138(%%ebp), %%esi\n\t"
      "movzwl %%di, %%edi\n\t"
      ".Lobjects_dump_memory_15:\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl $0x254608, %%eax\n\t"
      "je .Lobjects_dump_memory_16\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "jmp .Lobjects_dump_memory_17\n\t"
      ".Lobjects_dump_memory_16:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lobjects_dump_memory_18\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13c250]\n\t"
      ".Lobjects_dump_memory_17:\n\t"
      "addl $4, %%esp\n\t"
      ".Lobjects_dump_memory_18:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movswl 0x12(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "movswl 0x10(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0xe(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0xc(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0xa(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29bcf4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x2c, %%esp\n\t"
      "addl $0x18, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .Lobjects_dump_memory_15\n\t"
      ".Lobjects_dump_memory_19:\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lobjects_dump_memory_20\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x400\n\t"
      "pushl $0x29bd28\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lobjects_dump_memory_20:\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d98ad]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d9dac]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lobjects_dump_memory_21:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "call *%[c136580]\n\t"
      "call *%[c135f90]\n\t"
      "call *%[c13c2e0]\n\t"
      "call *%[c1391e0]\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "pushl $0xc\n\t"
      "jne .Lobjects_dump_memory_22\n\t"
      "pushl $0x800\n\t"
      "pushl $0x26b758\n\t"
      "call *%[c1bfe10]\n\t"
      "pushl $0x100000\n\t"
      "pushl $0x29bf10\n\t"
      "movl %%eax, 0x5a8d50\n\t"
      "call *%[c1bfe50]\n\t"
      "jmp .Lobjects_dump_memory_23\n\t"
      ".Lobjects_dump_memory_22:\n\t"
      "pushl $0x2800\n\t"
      "pushl $0x26b758\n\t"
      "call *%[c1194d0]\n\t"
      "pushl $0x500000\n\t"
      "pushl $0x29bf10\n\t"
      "movl %%eax, 0x5a8d50\n\t"
      "call *%[c11e650]\n\t"
      ".Lobjects_dump_memory_23:\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x46f080\n\t"
      "je .Lobjects_dump_memory_24\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lobjects_dump_memory_25\n\t"
      ".Lobjects_dump_memory_24:\n\t"
      "pushl $1\n\t"
      "pushl $0xd8\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bee4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_dump_memory_25:\n\t"
      "pushl $0x98\n\t"
      "pushl $0\n\t"
      "pushl $0x29bed4\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x46f084\n\t"
      "jne .Lobjects_dump_memory_26\n\t"
      "pushl $1\n\t"
      "pushl $0xdb\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bec4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_dump_memory_26:\n\t"
      "pushl $0x800\n\t"
      "pushl $0\n\t"
      "pushl $0x29bc70\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x46f07c\n\t"
      "jne .Lobjects_dump_memory_27\n\t"
      "pushl $1\n\t"
      "pushl $0xfe8\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bc5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobjects_dump_memory_27:\n\t"
      "pushl $0x29beb0\n\t"
      "pushl $0x5a8d40\n\t"
      "call *%[c191500]\n\t"
      "pushl $0x29be98\n\t"
      "pushl $0x5a8d30\n\t"
      "call *%[c191500]\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1365a0]\n\t"
      "call *%[c136040]\n\t"
      "call *%[c13c3d0]\n\t"
      "call *%[c1392b0]\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119b20]\n\t"
      "movl 0x46f07c, %%ecx\n\t"
      "pushl $0x800\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "pushl $0x5a8d40\n\t"
      "call *%[c1915d0]\n\t"
      "pushl $0x5a8d30\n\t"
      "call *%[c1915d0]\n\t"
      "movl 0x46f084, %%edx\n\t"
      "pushl $0x40\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl 0x46f084, %%eax\n\t"
      "pushl $0x40\n\t"
      "addl $0x4c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x46f084, %%eax\n\t"
      "movw %%bx, 0x90(%%eax)\n\t"
      "movb %%bl, 0x1(%%eax)\n\t"
      "movl %%ebx, 0x5a8d28\n\t"
      "movl $0xffffffff, 0x8(%%eax)\n\t"
      "movw %%bx, 0x4(%%eax)\n\t"
      "addl $0x30, %%esp\n\t"
      "movl %%ebx, 0x8c(%%eax)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [chkstk] "m"(b13f4b0_chkstk), [memset] "m"(b13f4b0_memset), [c1193f0] "m"(b13f4b0_c1193f0), [c13d730] "m"(b13f4b0_c13d730), [dget] "m"(b13f4b0_dget), [c13f3b0] "m"(b13f4b0_c13f3b0), [assert] "m"(b13f4b0_assert), [exitfn] "m"(b13f4b0_exitfn), [c1d9260] "m"(b13f4b0_c1d9260), [c1d9e59] "m"(b13f4b0_c1d9e59), [c13db60] "m"(b13f4b0_c13db60), [c1d98ad] "m"(b13f4b0_c1d98ad), [c1ba1f0] "m"(b13f4b0_c1ba1f0), [c13c250] "m"(b13f4b0_c13c250), [c1d9dac] "m"(b13f4b0_c1d9dac), [c136580] "m"(b13f4b0_c136580), [c135f90] "m"(b13f4b0_c135f90), [c13c2e0] "m"(b13f4b0_c13c2e0), [c1391e0] "m"(b13f4b0_c1391e0), [c977f0] "m"(b13f4b0_c977f0), [c1bfe10] "m"(b13f4b0_c1bfe10), [c1bfe50] "m"(b13f4b0_c1bfe50), [c1194d0] "m"(b13f4b0_c1194d0), [c11e650] "m"(b13f4b0_c11e650), [c1bfbf0] "m"(b13f4b0_c1bfbf0), [c191500] "m"(b13f4b0_c191500), [c1365a0] "m"(b13f4b0_c1365a0), [c136040] "m"(b13f4b0_c136040), [c13c3d0] "m"(b13f4b0_c13c3d0), [c1392b0] "m"(b13f4b0_c1392b0), [c119b20] "m"(b13f4b0_c119b20), [c1915d0] "m"(b13f4b0_c1915d0)
      : "memory");
}
#else
#error "objects_dump_memory: clang naked draft required"
#endif

#pragma clang diagnostic pop

/* 0x1417c0 — objects_reconnect_to_structure_bsp: reconnects objects to
 * the current BSP structure after a BSP switch. Iterates all objects and
 * updates their cluster assignments.
 *
 * Source: objects.c
 * No params. EBX is set locally to -1 (not a register arg).
 */
/* objects_reconnect_to_structure_bsp (0x1417c0) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void (*const b1417c0_chkstk)(void) = FUN_001d90e0;
static void (*const b1417c0_c1193f0)(data_t *data) = data_verify;
static void * (*const b1417c0_c13d730)(void *iter) = object_iterator_next;
static void *(*const b1417c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1417c0_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void *(*const b1417c0_gbsp)(void) = global_collision_bsp_get;
static int (*const b1417c0_c1493b0)(int bsp, short flags, int breakable_surfaces, int origin, float radius, int *results) = collision_bsp_test_sphere;
static void * (*const b1417c0_c18e3c0)(void) = scenario_get;
static void *(*const b1417c0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1417c0_c140ce0)(int object_handle, void *location) = object_connect_to_map;

__attribute__((naked, noinline))
void objects_reconnect_to_structure_bsp(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1028, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1193f0]\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x86868686, -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movb $0, -0x14(%%ebp)\n\t"
      "movw $0, -0x12(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lobjects_reconnect_to_structure_bsp_6\n\t"
      "pushl %%edi\n\t"
      "jmp .Lobjects_reconnect_to_structure_bsp_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lobjects_reconnect_to_structure_bsp_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .Lobjects_reconnect_to_structure_bsp_5\n\t"
      "cmpl %%ebx, 0xcc(%%esi)\n\t"
      "jne .Lobjects_reconnect_to_structure_bsp_5\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "andl $0xfffff7ff, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movw %%bx, 0x4c(%%esi)\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "leal 0x50(%%esi), %%edi\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movw %%bx, 0x4(%%eax)\n\t"
      "call *%[c18f180]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%bx, -0x4(%%ebp)\n\t"
      "jne .Lobjects_reconnect_to_structure_bsp_4\n\t"
      "movl 0x5c(%%esi), %%eax\n\t"
      "leal -0x1028(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[gbsp]\n\t"
      "pushl %%eax\n\t"
      "call *%[c1493b0]\n\t"
      "movl -0x41c(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobjects_reconnect_to_structure_bsp_3\n\t"
      "movl -0x418(%%ebp), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .Lobjects_reconnect_to_structure_bsp_2\n\t"
      "movw %%bx, -0x4(%%ebp)\n\t"
      "jmp .Lobjects_reconnect_to_structure_bsp_4\n\t"
      ".Lobjects_reconnect_to_structure_bsp_2:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x8(%%eax), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%cx, -0x4(%%ebp)\n\t"
      "jmp .Lobjects_reconnect_to_structure_bsp_4\n\t"
      ".Lobjects_reconnect_to_structure_bsp_3:\n\t"
      "addl $0xc, %%esi\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c18f180]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobjects_reconnect_to_structure_bsp_4:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140ce0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobjects_reconnect_to_structure_bsp_5:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lobjects_reconnect_to_structure_bsp_1\n\t"
      "popl %%edi\n\t"
      ".Lobjects_reconnect_to_structure_bsp_6:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b1417c0_chkstk), [c1193f0] "m"(b1417c0_c1193f0), [c13d730] "m"(b1417c0_c13d730), [dget] "m"(b1417c0_dget), [c18f180] "m"(b1417c0_c18f180), [gbsp] "m"(b1417c0_gbsp), [c1493b0] "m"(b1417c0_c1493b0), [c18e3c0] "m"(b1417c0_c18e3c0), [elem] "m"(b1417c0_elem), [c140ce0] "m"(b1417c0_c140ce0)
      : "memory");
}
#else
#error "objects_reconnect_to_structure_bsp: clang naked draft required"
#endif


/* 0x135510 — lightning_widget_render: renders lightning effects using a
 * midpoint displacement subdivision algorithm. Has a massive 36KB+ stack
 * buffer for point arrays.
 *
 * Source: objects.c (widgets subsystem)
 * 4 cdecl params.
 *
 * NOTE: This is an extremely complex rendering function (~2570 bytes).
 * The implementation below is a faithful structural lift from the decompiler
 * output, preserving all control flow, side effects, and the subdivision
 * algorithm. Due to the extreme complexity of the decompiler output with
 * corrupted stack analysis (_chkstk frame), some inner loop details are
 * simplified while maintaining the overall algorithm shape.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
/* 0x135510 — build/subdivide lightning bolt marker chains for rendering. */
#if defined(__clang__)
static float (*const o35510_norm)(float *) = normalize3d;
static void (*const o35510_assert)(const char *, const char *, int, bool) = display_assert;
static void *(*const o35510_memset)(void *, int, unsigned int) = csmemset;
static void (*const o35510_exitfn)(int) = system_exit;
static unsigned int (*const o35510_d1c90)(float *) = FUN_000d1c90;
static unsigned int *(*const o35510_lseed)(void) = random_math_get_local_seed_address;
static float (*const o35510_rmreal)(unsigned int *) = random_math_real;
static float (*const o35510_rrange)(int *, float, float) = random_real_range;
static float *(*const o35510_c2e0)(float *) = FUN_0010c2e0;
static void *(*const o35510_dget)(data_t *, int) = datum_get;
static void (*const o35510_loff)(int, float *, float *) = lightning_offset_marker_position;
static short (*const o35510_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static int (*const o35510_rzbuf)(int, int) = rasterizer_widget_set_zbuffer_enable;
static int (*const o35510_rspr)(int) = rasterizer_widget_draw_sprite3d;
static void (*const o35510_rend)(int) = rasterizer_widget_end;
static void (*const o35510_rocc)(int) = rasterizer_widget_submit_occlusion_test;
static void (*const o35510_r7cf60)(unsigned int, unsigned int, int, int, unsigned int, int, float *, unsigned int) = FUN_0017cf60;
static void *(*const o35510_elem)(void *, int, int) = tag_block_get_element;
static void *(*const o35510_tag)(int, int) = tag_get;
static void *(*const o35510_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static void (*const o35510_chkstk)(void) = FUN_001d90e0;

__attribute__((naked, noinline))
void FUN_00135510(int object_handle __attribute__((unused)), int lightning_datum __attribute__((unused)), int param_3 __attribute__((unused)), int *param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x24144, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00135510_42\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00135510_42\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x46f024, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x656c6563\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x98(%%esi), %%eax\n\t"
      "leal 0x98(%%esi), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, -0x3c(%%ebp)\n\t"
      "movl %%ebx, -0x64(%%ebp)\n\t"
      "jle .LFUN_00135510_41\n\t"
      "pushl $1\n\t"
      "leal -0x120(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xe4\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00135510_41\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "pushl $0x30\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x60, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      "call *%[xtex]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00135510_41\n\t"
      "cmpw %%di, 0x2(%%esi)\n\t"
      "movl %%edi, -0x80(%%ebp)\n\t"
      "jle .LFUN_00135510_41\n\t"
      ".LFUN_00135510_1:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl $0x3f800000, -0x84(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_00135510_2\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .LFUN_00135510_2\n\t"
      "movw 0x2c(%%esi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_00135510_2\n\t"
      "cmpw $4, %%ax\n\t"
      "jg .LFUN_00135510_2\n\t"
      "movswl %%ax, %%edx\n\t"
      "flds -0x4(%%ecx,%%edx,4)\n\t"
      "fstps -0x84(%%ebp)\n\t"
      ".LFUN_00135510_2:\n\t"
      "cmpl %%edi, (%%ebx)\n\t"
      "movl %%edi, -0x78(%%ebp)\n\t"
      "jle .LFUN_00135510_40\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00135510_4\n\t"
      ".LFUN_00135510_3:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_00135510_4:\n\t"
      "pushl $0xe4\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_00135510_5\n\t"
      "pushl $0x24024\n\t"
      "leal -0x24144(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[markers]\n\t"
      "movl -0xc0(%%ebp), %%eax\n\t"
      "movl -0xbc(%%ebp), %%ecx\n\t"
      "movl -0xb8(%%ebp), %%edx\n\t"
      "leal 0x74(%%esi), %%edi\n\t"
      "addl $0x1c, %%esp\n\t"
      "leal -0xe8(%%ebp), %%ebx\n\t"
      "leal -0x24144(%%ebp), %%esi\n\t"
      "movl %%eax, -0x24144(%%ebp)\n\t"
      "movl %%ecx, -0x24140(%%ebp)\n\t"
      "movl %%edx, -0x2413c(%%ebp)\n\t"
      "call *%[loff]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x84(%%eax), %%ecx\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl -0x64(%%ebp), %%ebx\n\t"
      "addl $0x88, %%eax\n\t"
      "movl %%ecx, -0x24138(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x24134(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24130(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, -0x2412c(%%ebp)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%eax, -0x24128(%%ebp)\n\t"
      "movb $1, -0x24124(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00135510_5:\n\t"
      "testb $1, 0x20(%%esi)\n\t"
      "jne .LFUN_00135510_15\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "je .LFUN_00135510_15\n\t"
      "pushl $0xe4\n\t"
      "incl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x24(%%esi), %%cx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0x74(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%ecx, -0x68(%%ebp)\n\t"
      "movswl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "addl %%ecx, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%esi\n\t"
      "shll $2, %%esi\n\t"
      "leal -0x24124(%%ebp,%%esi,1), %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "cmpb $0, (%%eax)\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "je .LFUN_00135510_6\n\t"
      "pushl $1\n\t"
      "pushl $0x17f\n\t"
      "pushl $0x29acfc\n\t"
      "pushl $0x29adb4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135510_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "leal -0x120(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[markers]\n\t"
      "movl -0xc0(%%ebp), %%edx\n\t"
      "movl -0xbc(%%ebp), %%eax\n\t"
      "leal -0x24144(%%ebp,%%esi,1), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0xb8(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $0x74, %%edi\n\t"
      "leal -0xe8(%%ebp), %%ebx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[loff]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x84(%%ecx), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "movl %%edx, -0x24138(%%ebp,%%eax,1)\n\t"
      "addl $0x88, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal -0x24134(%%ebp,%%eax,1), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movb $1, (%%edx)\n\t"
      "flds (%%ecx)\n\t"
      "leal (%%esi,%%esi,8), %%eax\n\t"
      "fsubs -0x24144(%%ebp,%%eax,4)\n\t"
      "leal -0x24144(%%ebp,%%eax,4), %%eax\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x506560\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x50655c\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x50655c\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x506560\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x14, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00135510_7\n\t"
      "movl 0x31fc28, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      ".LFUN_00135510_7:\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_00135510_14\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, -0x48(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "nop\n\t"
      ".LFUN_00135510_8:\n\t"
      "movl $1, %%edi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll %%cl, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "leal (%%edi,%%edi,1), %%eax\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "jg .LFUN_00135510_9\n\t"
      "pushl $1\n\t"
      "pushl $0x198\n\t"
      "pushl $0x29acfc\n\t"
      "pushl $0x29ad98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135510_9:\n\t"
      "cmpw -0x20(%%ebp), %%di\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jge .LFUN_00135510_13\n\t"
      "fildl -0x6c(%%ebp)\n\t"
      "movswl %%di, %%edx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "jmp .LFUN_00135510_11\n\t"
      ".LFUN_00135510_10:\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      ".LFUN_00135510_11:\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "fildl -0x40(%%ebp)\n\t"
      "addl %%esi, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%edi\n\t"
      "leal (%%edx,%%ecx,1), %%eax\n\t"
      "fdivs -0x70(%%ebp)\n\t"
      "addl %%esi, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%ebx\n\t"
      "leal (%%ecx,%%esi,1), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%eax,8), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "leal -0x24144(%%ebp,%%edi,4), %%edi\n\t"
      "leal -0x24144(%%ebp,%%ebx,4), %%ebx\n\t"
      "leal -0x24144(%%ebp,%%eax,1), %%esi\n\t"
      "flds 0x80(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fsubs 0x80(%%ecx)\n\t"
      "fmulp %%st(1)\n\t"
      "fadds 0x80(%%ecx)\n\t"
      "movb -0x24124(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "fmuls -0x74(%%ebp)\n\t"
      "fmuls -0x84(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "je .LFUN_00135510_12\n\t"
      "pushl $1\n\t"
      "pushl $0x1aa\n\t"
      "pushl $0x29acfc\n\t"
      "pushl $0x29ad68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135510_12:\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x44(%%ebp), %%edx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "addl %%edx, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw -0x20(%%ebp), %%ax\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x94(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      "fadds (%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x98(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fadds 0xc(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0xc(%%esi)\n\t"
      "flds 0x10(%%ebx)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x10(%%esi)\n\t"
      "flds 0x14(%%ebx)\n\t"
      "fadds 0x14(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x14(%%esi)\n\t"
      "flds 0x18(%%ebx)\n\t"
      "fadds 0x18(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x18(%%esi)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fadds 0x1c(%%edi)\n\t"
      "movb $1, 0x20(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "jl .LFUN_00135510_10\n\t"
      "movl -0x48(%%ebp), %%ebx\n\t"
      ".LFUN_00135510_13:\n\t"
      "flds -0x74(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "fmuls 0x253398\n\t"
      "decl %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%ebx, -0x48(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .LFUN_00135510_8\n\t"
      ".LFUN_00135510_14:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movb 0x24(%%eax), %%cl\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x64(%%ebp), %%ebx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00135510_39\n\t"
      ".LFUN_00135510_15:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpw $2, %%ax\n\t"
      "movw $0xc, 0x325652\n\t"
      "jle .LFUN_00135510_38\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal (%%edi,%%edi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $6\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%ebx, -0x6c(%%ebp)\n\t"
      "je .LFUN_00135510_37\n\t"
      "pushl %%ebx\n\t"
      "call *%[rspr]\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "fdivrs 0x2533c8\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movl 0x2ee708, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $0x3f800000, -0x88(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl $0x3f800000, -0x7c(%%ebp)\n\t"
      "jne .LFUN_00135510_16\n\t"
      "pushl $1\n\t"
      "pushl $0xef\n\t"
      "pushl $0x29acfc\n\t"
      "pushl $0x28c050\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135510_16:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00135510_19\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_00135510_17\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movw 0x2e(%%eax), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_00135510_17\n\t"
      "cmpw $4, %%ax\n\t"
      "jg .LFUN_00135510_17\n\t"
      "movswl %%ax, %%eax\n\t"
      "flds -0x4(%%edx,%%eax,4)\n\t"
      "fstps -0x88(%%ebp)\n\t"
      ".LFUN_00135510_17:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00135510_18\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movw 0x30(%%eax), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_00135510_18\n\t"
      "cmpw $4, %%ax\n\t"
      "jg .LFUN_00135510_18\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal -0xc(%%ecx,%%eax,4), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      ".LFUN_00135510_18:\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_00135510_19\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movw 0x32(%%eax), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_00135510_19\n\t"
      "cmpw $4, %%ax\n\t"
      "jg .LFUN_00135510_19\n\t"
      "movswl %%ax, %%ecx\n\t"
      "flds -0x4(%%edx,%%ecx,4)\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      ".LFUN_00135510_19:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jle .LFUN_00135510_34\n\t"
      "jmp .LFUN_00135510_21\n\t"
      ".LFUN_00135510_20:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      ".LFUN_00135510_21:\n\t"
      "movswl %%cx, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%ebx\n\t"
      "shll $2, %%ebx\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "leal -0x24144(%%ebp,%%ebx,1), %%edi\n\t"
      "jle .LFUN_00135510_22\n\t"
      "leal -0x24(%%edi), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00135510_23\n\t"
      ".LFUN_00135510_22:\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%edi, %%ecx\n\t"
      ".LFUN_00135510_23:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_00135510_24\n\t"
      "leal -0x24120(%%ebp,%%ebx,1), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jmp .LFUN_00135510_25\n\t"
      ".LFUN_00135510_24:\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_00135510_25:\n\t"
      "flds -0x88(%%ebp)\n\t"
      "movb -0x24124(%%ebp,%%ebx,1), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "fmuls -0x24138(%%ebp,%%ebx,1)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fildl -0x44(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "jne .LFUN_00135510_26\n\t"
      "pushl $1\n\t"
      "pushl $0x118\n\t"
      "pushl $0x29acfc\n\t"
      "pushl $0x29ad4c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00135510_26:\n\t"
      "flds (%%eax)\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "fsubs (%%ecx)\n\t"
      "pushl %%edx\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x506560\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x50655c\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x50655c\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x506560\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[c2e0]\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "fmuls -0x24134(%%ebp,%%ebx,1)\n\t"
      "fstps -0xb4(%%ebp)\n\t"
      "flds -0x24130(%%ebp,%%ebx,1)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps -0xb0(%%ebp)\n\t"
      "flds -0x2412c(%%ebp,%%ebx,1)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0xac(%%ebp)\n\t"
      "flds -0x24128(%%ebp,%%ebx,1)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0xb4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0xa8(%%ebp)\n\t"
      "call *%[d1c90]\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "addl $0x18, %%esi\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0x18(%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x14(%%esi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "movl %%eax, -0x4(%%esi)\n\t"
      "movl $0, -0x8(%%esi)\n\t"
      "fstps -0x10(%%esi)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fsts -0xc(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%edi)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fstps 0xc(%%esi)\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movl $0x3f800000, 0x10(%%esi)\n\t"
      "addl $0x18, %%esi\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .LFUN_00135510_27\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%eax, -0x60(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "jmp .LFUN_00135510_33\n\t"
      ".LFUN_00135510_27:\n\t"
      "flds (%%edi)\n\t"
      "fcomps -0x60(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00135510_28\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      ".LFUN_00135510_28:\n\t"
      "flds 0x4(%%edi)\n\t"
      "fcomps -0x58(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00135510_29\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      ".LFUN_00135510_29:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps -0x50(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00135510_30\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      ".LFUN_00135510_30:\n\t"
      "flds (%%edi)\n\t"
      "fcomps -0x5c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00135510_31\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      ".LFUN_00135510_31:\n\t"
      "flds 0x4(%%edi)\n\t"
      "fcomps -0x54(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00135510_32\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      ".LFUN_00135510_32:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps -0x4c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00135510_33\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      ".LFUN_00135510_33:\n\t"
      "incl %%ecx\n\t"
      "cmpw -0x14(%%ebp), %%cx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00135510_20\n\t"
      "movl -0x6c(%%ebp), %%ebx\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      ".LFUN_00135510_34:\n\t"
      "flds -0x60(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "fadds -0x5c(%%ebp)\n\t"
      "movl 0xa4(%%eax), %%ecx\n\t"
      "addl $0xa4, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0xa4(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fadds -0x54(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0xa0(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x9c(%%ebp)\n\t"
      "jle .LFUN_00135510_35\n\t"
      "pushl $0xb4\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_00135510_36\n\t"
      ".LFUN_00135510_35:\n\t"
      "movl $0x326a78, %%esi\n\t"
      ".LFUN_00135510_36:\n\t"
      "pushl %%ebx\n\t"
      "call *%[rend]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "leal -0x2(%%edi,%%edi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "negl %%edi\n\t"
      "shll $1, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[r7cf60]\n\t"
      "pushl %%ebx\n\t"
      "call *%[rocc]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_00135510_37:\n\t"
      "movl -0x64(%%ebp), %%ebx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00135510_38:\n\t"
      "movw $0, 0x325652\n\t"
      ".LFUN_00135510_39:\n\t"
      "movl -0x78(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_00135510_3\n\t"
      "movl -0x3c(%%ebp), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00135510_40:\n\t"
      "movl -0x80(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x2(%%esi), %%ax\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "jl .LFUN_00135510_1\n\t"
      ".LFUN_00135510_41:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00135510_42:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(o35510_norm), [assert] "m"(o35510_assert), [memset] "m"(o35510_memset), [exitfn] "m"(o35510_exitfn), [d1c90] "m"(o35510_d1c90), [lseed] "m"(o35510_lseed), [rmreal] "m"(o35510_rmreal), [rrange] "m"(o35510_rrange), [c2e0] "m"(o35510_c2e0), [dget] "m"(o35510_dget), [loff] "m"(o35510_loff), [markers] "m"(o35510_markers), [rzbuf] "m"(o35510_rzbuf), [rspr] "m"(o35510_rspr), [rend] "m"(o35510_rend), [rocc] "m"(o35510_rocc), [r7cf60] "m"(o35510_r7cf60), [elem] "m"(o35510_elem), [tag] "m"(o35510_tag), [xtex] "m"(o35510_xtex), [chkstk] "m"(o35510_chkstk)
      : "memory");
}
#else
void FUN_00135510(int object_handle, int lightning_datum, int param_3,
                  int *param_4)
{
  char *elec;
  char *seg_block;
  char *seg;
  char *next_seg;
  char marker[0xe4];
  char scratch[0x30];
  float points[4096 * 9];
  int bitm_elem;
  int hw;
  int bolt_i;
  int seg_i;
  int point_count;
  float intensity;
  float jitter;
  char first_pass;
  float delta[3];
  float *cam_right;
  (void)param_3;
  (void)scratch;

  if (object_handle == -1 || lightning_datum == -1)
    return;

  elec = (char *)tag_get(
      0x656c6563,
      *(int *)((char *)datum_get(*(void **)0x46f024, lightning_datum) + 4));
  seg_block = elec + 0x98;
  if (*(int *)seg_block <= 0)
    return;

  seg = (char *)tag_block_get_element(seg_block, 0, 0xe4);
  if (object_get_markers_by_string_id(object_handle, seg, marker, 1) <= 0)
    return;

  {
    char *bitm = (char *)tag_get(0x6269746d, *(int *)(elec + 0x40));
    bitm_elem = (int)tag_block_get_element(bitm + 0x60, 0, 0x30);
  }
  hw = CALL_FUN_001bf570(bitm_elem, 0, 1);
  if (hw == 0 || *(int16_t *)(elec + 2) <= 0)
    return;

  for (bolt_i = 0; bolt_i < *(int16_t *)(elec + 2); bolt_i++) {
    intensity = 1.0f;
    if (param_4 != 0 && param_4[1] != 0) {
      int16_t fn = *(int16_t *)(elec + 0x2c);
      if (fn > 0 && fn < 5)
        intensity = *(float *)(param_4[1] - 4 + fn * 4);
    }

    first_pass = 1;
    point_count = 0;
    for (seg_i = 0; seg_i < *(int *)seg_block; seg_i++) {
      int subdiv;
      int bit;
      float *dst;
      float *src;

      seg = (char *)tag_block_get_element(seg_block, seg_i, 0xe4);
      if (first_pass) {
        csmemset(points, 0, 0x24024);
        object_get_markers_by_string_id(object_handle, seg, marker, 1);
        points[0] = *(float *)(marker + 0x60);
        points[1] = *(float *)(marker + 0x64);
        points[2] = *(float *)(marker + 0x68);
        lightning_offset_marker_position((int)(marker + 0x38), points,
                                         (float *)(seg + 0x74));
        points[3] = *(float *)(seg + 0x84);
        points[4] = *(float *)(seg + 0x88);
        points[5] = *(float *)(seg + 0x8c);
        points[6] = *(float *)(seg + 0x90);
        points[7] = *(float *)(seg + 0x94);
        ((char *)points)[0x20] = 1;
        first_pass = 0;
        point_count = 1;
      }

      if ((*(unsigned char *)(seg + 0x20) & 1) != 0 ||
          seg_i == *(int *)seg_block - 1) {
        /* Terminal / flagged segment: submit assembled chain. */
        if (point_count >= 2) {
          *(int16_t *)0x325652 = 0xc;
          /* Rasterizer submit path left as structural calls. */
          {
            int z = rasterizer_widget_set_zbuffer_enable(point_count * 2, 6);
            if (z != -1) {
              rasterizer_widget_draw_sprite3d(z);
              (void)random_math_real(random_math_get_local_seed_address());
            }
          }
        }
        continue;
      }

      next_seg = (char *)tag_block_get_element(seg_block, seg_i + 1, 0xe4);
      bit = 1 << (int)*(unsigned short *)(seg + 0x24);
      jitter = 1.0f;
      dst = points + (point_count + bit) * 9;
      if (((char *)dst)[0x20] != 0) {
        display_assert((char *)0x0029adb4, (char *)0x0029acfc, 0x17f, 1);
        system_exit(-1);
      }

      object_get_markers_by_string_id(object_handle, next_seg, marker, 1);
      src = dst;
      src[0] = *(float *)(marker + 0x60);
      src[1] = *(float *)(marker + 0x64);
      src[2] = *(float *)(marker + 0x68);
      lightning_offset_marker_position((int)(marker + 0x38), src,
                                       (float *)(next_seg + 0x74));
      src[3] = *(float *)(next_seg + 0x84);
      src[4] = *(float *)(next_seg + 0x88);
      src[5] = *(float *)(next_seg + 0x8c);
      src[6] = *(float *)(next_seg + 0x90);
      src[7] = *(float *)(next_seg + 0x94);
      ((char *)src)[0x20] = 1;

      {
        float *prev = points + point_count * 9;
        delta[0] = src[0] - prev[0];
        delta[1] = src[1] - prev[1];
        delta[2] = src[2] - prev[2];
      }
      /* Camera-perpendicular basis for jitter. */
      {
        float t0 = delta[0] * *(float *)0x506560 - delta[1] * *(float *)0x50655c;
        float t1 = delta[2] * *(float *)0x50655c - delta[0] * *(float *)0x506564;
        float t2 = delta[1] * *(float *)0x506564 - delta[2] * *(float *)0x506560;
        delta[0] = t0;
        delta[1] = t1;
        delta[2] = t2;
      }
      if (normalize3d(delta) == 0.0f) {
        cam_right = *(float **)0x31fc28;
        delta[0] = cam_right[0];
        delta[1] = cam_right[1];
        delta[2] = cam_right[2];
      }

      subdiv = *(unsigned short *)(seg + 0x24);
      if (subdiv >= 1) {
        int level;
        int span = bit;
        for (level = subdiv - 1; level >= 0; level--) {
          int step = 1 << level;
          int idx;
          for (idx = step; idx < span; idx += step * 2) {
            float *a = points + (idx - step) * 9;
            float *b = points + (idx + step) * 9;
            float *m = points + idx * 9;
            float t = (float)idx / (float)span;
            float amp =
                (t * (*(float *)(next_seg + 0x80) - *(float *)(seg + 0x80)) +
                 *(float *)(seg + 0x80)) *
                jitter * intensity;
            float rnd = random_real_range(
                (int *)random_math_get_local_seed_address(), -1.0f, 1.0f);
            if (((char *)m)[0x20] != 0) {
              display_assert((char *)0x0029ad68, (char *)0x0029acfc, 0x1aa, 1);
              system_exit(-1);
            }
            m[0] = (a[0] + b[0]) * 0.5f + delta[0] * rnd * amp;
            m[1] = (a[1] + b[1]) * 0.5f + delta[1] * rnd * amp;
            m[2] = (a[2] + b[2]) * 0.5f + delta[2] * rnd * amp;
            m[3] = (a[3] + b[3]) * 0.5f;
            m[4] = (a[4] + b[4]) * 0.5f;
            m[5] = (a[5] + b[5]) * 0.5f;
            m[6] = (a[6] + b[6]) * 0.5f;
            m[7] = (a[7] + b[7]) * 0.5f;
            ((char *)m)[0x20] = 1;
          }
          jitter *= 0.5f;
        }
      }
      point_count += bit;
    }
  }
}
#endif

#pragma clang diagnostic pop

/* FUN_0009eb40 (0x9eb40) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void (*const b9eb40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b9eb40_exitfn)(int) = system_exit;
static int (*const b9eb40_c9d2d0)(int tag_index, int object_index, int unknown3) = FUN_0009d2d0;
static void *(*const b9eb40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b9eb40_cdd110)(int object_handle) = first_person_weapon_get_local_index;
static void *(*const b9eb40_memset)(void *, int, unsigned int) = csmemset;
static void (*const b9eb40_c9d4e0)(int datum, void *callback) = FUN_0009d4e0;
static void (*const b9eb40_c9e610)(int effect_index, float elapsed) = effect_update;

__attribute__((naked, noinline))
int FUN_0009eb40(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), short param_3 __attribute__((unused)), short param_4 __attribute__((unused)), short param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_0009eb40_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf9\n\t"
      "pushl $0x26a8c0\n\t"
      "pushl $0x269cf8\n\t"
      "call *%[assert]\n\t"
      "pushl %%esi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0009eb40_1:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c9d2d0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0009eb40_4\n\t"
      "movl 0x5aa8b0, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, 0x3c(%%ebx)\n\t"
      "call *%[cdd110]\n\t"
      "movw 0x10(%%ebp), %%cx\n\t"
      "movw 0x14(%%ebp), %%dx\n\t"
      "movw %%ax, 0x4c(%%ebx)\n\t"
      "movw 0x18(%%ebp), %%ax\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movw %%cx, 0x8(%%ebx)\n\t"
      "movw %%dx, 0xa(%%ebx)\n\t"
      "movw %%ax, 0xc(%%ebx)\n\t"
      "movl %%esi, 0x34(%%ebx)\n\t"
      "movl %%esi, 0x38(%%ebx)\n\t"
      "jne .LFUN_0009eb40_2\n\t"
      "movl 0x2ee708, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".LFUN_0009eb40_2:\n\t"
      "orb $2, 0x2(%%ebx)\n\t"
      "pushl $0x80\n\t"
      "leal 0x5c(%%ebx), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "pushl $0x140f10\n\t"
      "call *%[c9d4e0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, 0x4c(%%ebx)\n\t"
      "je .LFUN_0009eb40_3\n\t"
      "pushl $0xdd190\n\t"
      "call *%[c9d4e0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0009eb40_3:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c9e610]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0009eb40_4:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b9eb40_assert), [exitfn] "m"(b9eb40_exitfn), [c9d2d0] "m"(b9eb40_c9d2d0), [dget] "m"(b9eb40_dget), [cdd110] "m"(b9eb40_cdd110), [memset] "m"(b9eb40_memset), [c9d4e0] "m"(b9eb40_c9d4e0), [c9e610] "m"(b9eb40_c9e610)
      : "memory");
}
#else
#error "FUN_0009eb40: clang naked draft required"
#endif


/* FUN_0009ec30 (0x9ec30) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void (*const b9ec30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b9ec30_exitfn)(int) = system_exit;
static char * (*const b9ec30_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static int (*const b9ec30_c9d2d0)(int tag_index, int object_index, int unknown3) = FUN_0009d2d0;
static void *(*const b9ec30_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b9ec30_c9d430)(int datum, int unknown1, int unknown2, float scale_a, float scale_b) = FUN_0009d430;
static int (*const b9ec30_cdd110)(int object_handle) = first_person_weapon_get_local_index;
static bool (*const b9ec30_c9c700)(int object_handle) = FUN_0009c700;
static void *(*const b9ec30_tryget)(int, int) = object_try_and_get_and_verify_type;
static const char * (*const b9ec30_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b9ec30_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b9ec30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void *(*const b9ec30_memset)(void *, int, unsigned int) = csmemset;
static void (*const b9ec30_c9d4e0)(int datum, void *callback) = FUN_0009d4e0;
static void (*const b9ec30_c9e610)(int effect_index, float elapsed) = effect_update;

__attribute__((naked, noinline))
int FUN_0009ec30(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), short param_4 __attribute__((unused)), float param_5 __attribute__((unused)), float param_6 __attribute__((unused)), int param_7 __attribute__((unused)), int param_8 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_0009ec30_1\n\t"
      "pushl $1\n\t"
      "pushl $0x131\n\t"
      "pushl $0x26a8c0\n\t"
      "pushl $0x269cf8\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0009ec30_1:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0009ec30_2\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0009ec30_3\n\t"
      ".LFUN_0009ec30_2:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x132\n\t"
      "pushl $0x26a8c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26aa74\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0009ec30_3:\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0009ec30_4\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0009ec30_5\n\t"
      ".LFUN_0009ec30_4:\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x133\n\t"
      "pushl $0x26a8c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26aa5c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0009ec30_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c9d2d0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .LFUN_0009ec30_13\n\t"
      "movl 0x5aa8b0, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x24(%%ebp), %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c9d430]\n\t"
      "pushl %%edi\n\t"
      "movl %%edi, 0x3c(%%esi)\n\t"
      "call *%[cdd110]\n\t"
      "movw %%ax, 0x4c(%%esi)\n\t"
      "movb 0x2eebe0, %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x40, %%ebx\n\t"
      "je .LFUN_0009ec30_6\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "call *%[c9c700]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0009ec30_6\n\t"
      "orw %%bx, 0x2(%%esi)\n\t"
      ".LFUN_0009ec30_6:\n\t"
      "movb 0x4557e8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0009ec30_10\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0009ec30_7\n\t"
      "movl $0x25ad08, %%eax\n\t"
      "jmp .LFUN_0009ec30_8\n\t"
      ".LFUN_0009ec30_7:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0009ec30_8:\n\t"
      "testb %%bl, 0x2(%%esi)\n\t"
      "movl $0x26aa58, %%edi\n\t"
      "jne .LFUN_0009ec30_9\n\t"
      "movl $0x25386f, %%edi\n\t"
      ".LFUN_0009ec30_9:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x26aa3c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0009ec30_10:\n\t"
      "pushl $0x80\n\t"
      "leal 0x5c(%%esi), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "pushl $0x140f10\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c9d4e0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, 0x4c(%%esi)\n\t"
      "je .LFUN_0009ec30_11\n\t"
      "pushl $0xdd190\n\t"
      "call *%[c9d4e0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0009ec30_11:\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0009ec30_12\n\t"
      "movw %%ax, 0x4c(%%esi)\n\t"
      ".LFUN_0009ec30_12:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c9e610]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".LFUN_0009ec30_13:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b9ec30_assert), [exitfn] "m"(b9ec30_exitfn), [c8d9d0] "m"(b9ec30_c8d9d0), [c9d2d0] "m"(b9ec30_c9d2d0), [dget] "m"(b9ec30_dget), [c9d430] "m"(b9ec30_c9d430), [cdd110] "m"(b9ec30_cdd110), [c9c700] "m"(b9ec30_c9c700), [tryget] "m"(b9ec30_tryget), [c1ba1f0] "m"(b9ec30_c1ba1f0), [c19b0d0] "m"(b9ec30_c19b0d0), [c8f390] "m"(b9ec30_c8f390), [memset] "m"(b9ec30_memset), [c9d4e0] "m"(b9ec30_c9d4e0), [c9e610] "m"(b9ec30_c9e610)
      : "memory");
}
#else
#error "FUN_0009ec30: clang naked draft required"
#endif


/* Forwards (param1, param2, -1) to FUN_00085180. */
void FUN_00085260(short param_1, short param_2)
{
  FUN_00085180(param_1, param_2, -1);
  return;
}

/* FUN_001397f0 (0x1397f0) — XBE naked draft (batch 101). */
#if defined(__clang__)


__attribute__((naked, noinline))
float FUN_001397f0(float param_1 __attribute__((unused)), float param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsubrs 0x2533c8\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001397f0: clang naked draft required"
#endif


/* objects_scripting_attach (0x144ae0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b144ae0_get)(int, int) = object_get_and_verify_type;
static void (*const b144ae0_c144860)(int parent_handle, void *marker_name, int child_handle, void *child_marker_name) = object_attach_to_marker;

__attribute__((naked, noinline))
void objects_scripting_attach(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lobjects_scripting_attach_2\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobjects_scripting_attach_1\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .Lobjects_scripting_attach_1\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c144860]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lobjects_scripting_attach_1:\n\t"
      "popl %%esi\n\t"
      ".Lobjects_scripting_attach_2:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b144ae0_get), [c144860] "m"(b144ae0_c144860)
      : "memory");
}
#else
#error "objects_scripting_attach: clang naked draft required"
#endif


/* FUN_0013c080 (0x13c080) — XBE naked draft (batch 66). */
#if defined(__clang__)
static void *(*const b13c080_get)(int, int) = object_get_and_verify_type;
static void *(*const b13c080_tag)(int, int) = tag_get;
static void (*const b13c080_c13c030)(int param_1, int param_2, int param_3) = FUN_0013c030;

__attribute__((naked, noinline))
char FUN_0013c080(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl $0xff7fffff, %%eax\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl $0x7f7fffff, %%ecx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl %%ecx, 0x14(%%esi)\n\t"
      "movw %%ax, 0x1c(%%esi)\n\t"
      "movw %%ax, 0x1e(%%esi)\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0xc8(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c13c030]\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $0, 0x1c(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jle .LFUN_0013c080_1\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013c080_1:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b13c080_get), [tag] "m"(b13c080_tag), [c13c030] "m"(b13c080_c13c030)
      : "memory");
}
#else
#error "FUN_0013c080: clang naked draft required"
#endif


/* FUN_0013a340 (0x13a340) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b13a340_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13a340_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_0013a340(int param_1 __attribute__((unused)), float *param_2 __attribute__((unused)), float *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c696768\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb (%%ecx), %%al\n\t"
      "flds 0xc(%%ecx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $2, %%al\n\t"
      "jne .LFUN_0013a340_1\n\t"
      "fmuls 0x24(%%ecx)\n\t"
      ".LFUN_0013a340_1:\n\t"
      "fcoms 0x18(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a340_2\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x30, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x18(%%ecx), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013a340_2:\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a340_5\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x254a58\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0013a340_4\n\t"
      "fdivs 0x20(%%ecx)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "fld %%st(0)\n\t"
      "fstps (%%edx)\n\t"
      ".LFUN_0013a340_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "fadds 0x34(%%esi)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "fadds 0x38(%%esi)\n\t"
      "popl %%esi\n\t"
      "fstps 0x8(%%eax)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0013a340_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x28(%%ecx)\n\t"
      "fstps (%%eax)\n\t"
      "fmuls 0x20(%%ecx)\n\t"
      "jmp .LFUN_0013a340_3\n\t"
      ".LFUN_0013a340_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x30, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "fstps (%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13a340_dget), [tag] "m"(b13a340_tag)
      : "memory");
}
#else
#error "FUN_0013a340: clang naked draft required"
#endif


/* object_new_by_name (0x144940) — XBE naked draft (batch 65). */
#if defined(__clang__)
static scenario_t * (*const b144940_c18e380)(void) = global_scenario_get;
static void *(*const b144940_elem)(void *, int, int) = tag_block_get_element;
static int (*const b144940_c13ca30)(int param_1, int param_2, int *param_3) = FUN_0013ca30;
static int (*const b144940_c13cab0)(int param_1, int param_2) = FUN_0013cab0;
static int (*const b144940_c144770)(void *placement_data, int palette_block) = object_new_from_scenario;

__attribute__((naked, noinline))
void object_new_by_name(short param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x24\n\t"
      "pushl %%eax\n\t"
      "leal 0x204(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x20(%%edi), %%ax\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c13ca30]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%edi), %%cx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c13cab0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x22(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c144770]\n\t"
      "addl $0x34, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b144940_c18e380), [elem] "m"(b144940_elem), [c13ca30] "m"(b144940_c13ca30), [c13cab0] "m"(b144940_c13cab0), [c144770] "m"(b144940_c144770)
      : "memory");
}
#else
#error "object_new_by_name: clang naked draft required"
#endif


/* FUN_0013aa10 (0x13aa10) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void (*const b13aa10_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static void (*const b13aa10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13aa10_exitfn)(int) = system_exit;
static int16_t (*const b13aa10_c13fe10)(void *iter_state, int object_handle) = object_get_first_cluster;
static void (*const b13aa10_c139c20)(int object_handle, int16_t marker_index, float *position, float bias, int out_index_base, float *out_weights, int out_atten_base, int16_t *count, int16_t max_count) = FUN_00139c20;
static int16_t (*const b13aa10_c13d5f0)(void *param_1, int param_2) = FUN_0013d5f0;
static void *(*const b13aa10_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
void FUN_0013aa10(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1aae0]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "leal 0x40(%%ebx), %%edi\n\t"
      "movw $0, (%%edi)\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0013aa10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x664\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013aa10_1:\n\t"
      "incl 0x5a8d64\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movb $1, 0x5a8d60\n\t"
      "call *%[c13fe10]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0013aa10_3\n\t"
      "addl $0x44, %%ebx\n\t"
      ".LFUN_0013aa10_2:\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c139c20]\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d5f0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0013aa10_2\n\t"
      ".LFUN_0013aa10_3:\n\t"
      "movb 0x5a8d60, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0013aa10_4\n\t"
      "pushl $1\n\t"
      "pushl $0x68e\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b4ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0013aa10_4:\n\t"
      "xorl %%esi, %%esi\n\t"
      "movb $0, 0x5a8d60\n\t"
      "cmpw %%si, (%%edi)\n\t"
      "jle .LFUN_0013aa10_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0013aa10_5:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x44(%%edx,%%ecx,4), %%eax\n\t"
      "leal 0x44(%%edx,%%ecx,4), %%ebx\n\t"
      "movl 0x5a90bc, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "incl %%esi\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "cmpw (%%edi), %%si\n\t"
      "jl .LFUN_0013aa10_5\n\t"
      ".LFUN_0013aa10_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1aae0] "m"(b13aa10_c1aae0), [assert] "m"(b13aa10_assert), [exitfn] "m"(b13aa10_exitfn), [c13fe10] "m"(b13aa10_c13fe10), [c139c20] "m"(b13aa10_c139c20), [c13d5f0] "m"(b13aa10_c13d5f0), [dget] "m"(b13aa10_dget)
      : "memory");
}
#else
#error "FUN_0013aa10: clang naked draft required"
#endif


/* FUN_001414e0 (0x1414e0) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1414e0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1414e0_tag)(int, int) = tag_get;
static short (*const b1414e0_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void *(*const b1414e0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1414e0_c109150)(float *src, float *dst) = matrix_inverse;
static void (*const b1414e0_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static void (*const b1414e0_c120fd0)(float *composed_matrix, int node_matrix_b, int node_matrix_c, int node_matrix_d) = inverse_kinematics_adjust_matrices;

__attribute__((naked, noinline))
void FUN_001414e0(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "pushl $1\n\t"
      "leal -0xa0(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[markers]\n\t"
      "addl $0x28, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001414e0_2\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001414e0_2\n\t"
      "pushl %%edi\n\t"
      "movswl -0xa0(%%ebp), %%edi\n\t"
      "pushl $0x9c\n\t"
      "addl $0xb8, %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movw 0x24(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001414e0_1\n\t"
      "movswl %%ax, %%esi\n\t"
      "pushl $0x9c\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movw 0x24(%%eax), %%bx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_001414e0_1\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x9c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109150]\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xd4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109850]\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "imull $0x34, %%esi, %%esi\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movswl %%bx, %%ecx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "addl %%eax, %%edi\n\t"
      "pushl %%edi\n\t"
      "addl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c120fd0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_001414e0_1:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001414e0_2:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1414e0_get), [tag] "m"(b1414e0_tag), [markers] "m"(b1414e0_markers), [elem] "m"(b1414e0_elem), [c109150] "m"(b1414e0_c109150), [c109850] "m"(b1414e0_c109850), [c120fd0] "m"(b1414e0_c120fd0)
      : "memory");
}
#else
#error "FUN_001414e0: clang naked draft required"
#endif

/* --- objects.obj orphan shells (2026-07-26) --- */

/* 0x85000 — Bind antenna globals from a scenario antenna tag entry name. */
void FUN_00085000(int tag_index, const char *name)
{
  char *antenna_tag;
  char *entry;
  int count;
  int i;

  if (tag_index == -1)
    return;

  antenna_tag = (char *)tag_get('rtna', tag_index);
  if (*(int *)(antenna_tag + 0x68) != 1)
    return;

  count = *(int *)(antenna_tag + 0x74);
  for (i = 0; i < count; i++) {
    entry = (char *)tag_block_get_element(antenna_tag + 0x74, i, 0xb4);
    if (crt_stricmp(name, entry) == 0) {
      float scale;

      *(int16_t *)0x2ee5a4 = -1;
      *(int *)0x2ee5d4 = -1;
      *(int16_t *)0x2ee5a2 = 1;
      *(char *)0x2ee5a1 = 1;
      *(int16_t *)0x2ee5dc = (int16_t)i;
      *(int *)0x2ee5d8 = tag_index;
      *(float *)0x2ee5d0 = 1.230000019f;
      scale = (float)(*(int16_t *)(entry + 0x22) / 16);
      *(float *)0x2ee5a8 = scale;
      return;
    }
  }
}

/* 0x85280 — Publish antenna/camera observer globals and refresh director. */
void FUN_00085280(float *position, float *forward, float *up, float param_4,
                  short param_5, int param_6)
{
  static const float k_observer_tick = 9.999999747378752e-05f;
  int n;
  int q;

  *(int16_t *)0x2ee5a2 = 0;
  *(int16_t *)0x2ee5a4 = -1;

  *(float *)0x2ee5ac = position[0];
  *(float *)0x2ee5b0 = position[1];
  *(float *)0x2ee5b4 = position[2];

  *(float *)0x2ee5b8 = forward[0];
  *(float *)0x2ee5bc = forward[1];
  *(float *)0x2ee5c0 = forward[2];

  *(float *)0x2ee5c4 = up[0];
  *(float *)0x2ee5c8 = up[1];
  *(float *)0x2ee5cc = up[2];

  if (param_4 != *(float *)0x2533c0)
    *(float *)0x2ee5d0 = param_4;
  else
    *(float *)0x2ee5d0 = 1.22173047f;

  /* MSVC signed divide by 15 via magic 0x88888889, sar 4, sign fix. */
  n = (int)param_5;
  q = (int)(((long long)(int)0x88888889 * (long long)n) >> 32);
  q = (q + n) >> 4;
  q += (unsigned int)q >> 31;
  *(float *)0x2ee5a8 = (float)q;
  *(int *)0x2ee5d4 = param_6;

  director_update(0.0f);
  observer_update(k_observer_tick);
}

/* 0x85350 — Bind antenna globals without a scenario tag index. */
void FUN_00085350(float *position, float *forward, float *up, float param_4,
                  short param_5)
{
  FUN_00085280(position, forward, up, param_4, param_5, -1);
}

/* 0x134070 — Advance one glow particle along its widget path. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(2)))
#endif
#if defined(__clang__)
static void *(*const o34070_tag)(int, int) = tag_get;
static void (*const o34070_ogfv)(int, unsigned short, float *) =
    (void (*)(int, unsigned short, float *))(void *)object_get_function_value;
static void (*const o34070_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const o34070_exitfn)(int) = system_exit;
static void (*const o34070_gpwp)(int, int, float) = get_particle_world_position;

__attribute__((naked, noinline))
void FUN_00134070(int glow_widget_ptr __attribute__((unused)), int particle_ptr __attribute__((unused)), int object_handle __attribute__((unused)), float delta __attribute__((unused)), float ratio __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 548(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 128(%%ebx), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00134070_2\n\t"
      "movl 8(%%ebp), %%edx\n\t"
      "leal -4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[ogfv]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00134070_1\n\t"
      "movl $0, -4(%%ebp)\n\t"
      ".LFUN_00134070_1:\n\t"
      "flds 144(%%ebx)\n\t"
      "fsubs 140(%%ebx)\n\t"
      "fmuls -4(%%ebp)\n\t"
      "fadds 140(%%ebx)\n\t"
      "flds 136(%%ebx)\n\t"
      "fsubs 132(%%ebx)\n\t"
      "fmulp %%st(1)\n\t"
      "fadds 132(%%ebx)\n\t"
      "fstps 28(%%esi)\n\t"
      ".LFUN_00134070_2:\n\t"
      "movl 84(%%esi), %%ecx\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_00134070_11\n\t"
      "flds 40(%%esi)\n\t"
      "fsubs 12(%%ebp)\n\t"
      "fsts 40(%%esi)\n\t"
      "movswl 34(%%ebx), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00134070_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00134070_4\n\t"
      "pushl $1\n\t"
      "pushl $0x320\n\t"
      ".LFUN_00134070_3:\n\t"
      "pushl $0x29ab60\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x29abcc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 16(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[gpwp]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00134070_4:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00134070_10\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00134070_5:\n\t"
      "flds 564(%%edi)\n\t"
      "fadds 40(%%esi)\n\t"
      "fstps 40(%%esi)\n\t"
      "flds 40(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00134070_5\n\t"
      "movl 16(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[gpwp]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00134070_6:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00134070_10\n\t"
      "jmp .LFUN_00134070_8\n\t"
      ".LFUN_00134070_7:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00134070_8:\n\t"
      "flds 564(%%edi)\n\t"
      "fadds 40(%%esi)\n\t"
      "fsts 40(%%esi)\n\t"
      "flds 40(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00134070_7\n\t"
      "flds 564(%%edi)\n\t"
      "andl $0xfffffffe, %%ecx\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "movl %%ecx, 84(%%esi)\n\t"
      "fstps 40(%%esi)\n\t"
      ".LFUN_00134070_9:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00134070_10:\n\t"
      "movl 16(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[gpwp]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00134070_11:\n\t"
      "flds 12(%%ebp)\n\t"
      "fadds 40(%%esi)\n\t"
      "fsts 40(%%esi)\n\t"
      "movswl 34(%%ebx), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00134070_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00134070_12\n\t"
      "pushl $1\n\t"
      "pushl $0x33d\n\t"
      "jmp .LFUN_00134070_3\n\t"
      ".LFUN_00134070_12:\n\t"
      "fcomps 564(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134070_10\n\t"
      ".LFUN_00134070_13:\n\t"
      "flds 40(%%esi)\n\t"
      "fsubs 564(%%edi)\n\t"
      "fstps 40(%%esi)\n\t"
      "flds 40(%%esi)\n\t"
      "fcomps 564(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00134070_13\n\t"
      "movl 16(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[gpwp]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00134070_14:\n\t"
      "fcoms 564(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134070_9\n\t"
      "fcomps 564(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00134070_16\n\t"
      ".LFUN_00134070_15:\n\t"
      "flds 40(%%esi)\n\t"
      "fsubs 564(%%edi)\n\t"
      "fstps 40(%%esi)\n\t"
      "flds 40(%%esi)\n\t"
      "fcomps 564(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00134070_15\n\t"
      ".LFUN_00134070_16:\n\t"
      "flds 564(%%edi)\n\t"
      "movl 16(%%ebp), %%eax\n\t"
      "fsubs 40(%%esi)\n\t"
      "pushl %%eax\n\t"
      "orl $1, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "fstps 40(%%esi)\n\t"
      "movl %%ecx, 84(%%esi)\n\t"
      "call *%[gpwp]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(o34070_tag), [ogfv] "m"(o34070_ogfv), [assert] "m"(o34070_assert), [exitfn] "m"(o34070_exitfn), [gpwp] "m"(o34070_gpwp)
      : "memory");
}
#else
void FUN_00134070(int glow_widget_ptr, int particle_ptr, int object_handle,
                  float delta, float ratio)
{
  char *widget;
  char *particle;
  char *glow_def;
  int16_t fn_index;
  float fn_value;
  float path_pos;
  int16_t particle_type;

  widget = (char *)glow_widget_ptr;
  particle = (char *)particle_ptr;
  glow_def = (char *)tag_get('!wlg', *(int *)(widget + 0x224));
  fn_index = *(int16_t *)(glow_def + 0x80);
  if (fn_index == -1)
    goto finish;

  fn_value = 0.0f;
  if (object_get_function_value(object_handle, fn_index, &fn_value)) {
    /* keep fn_value */
  } else {
    fn_value = 0.0f;
  }

  *(float *)(particle + 0x1c) =
      *(float *)(glow_def + 0x84) +
      (*(float *)(glow_def + 0x88) - *(float *)(glow_def + 0x84)) *
          ((*(float *)(glow_def + 0x90) - *(float *)(glow_def + 0x8c)) * fn_value +
           *(float *)(glow_def + 0x8c));

  particle_type = *(int16_t *)(glow_def + 0x22);
  path_pos = *(float *)(particle + 0x28);

  if ((*(int *)(particle + 0x54) & 1) != 0) {
    path_pos -= delta;
    if (particle_type == 0) {
      if (path_pos <= *(float *)0x2533c0)
        goto finish;
      while (path_pos > *(float *)0x2533c0) {
        path_pos += *(float *)(widget + 0x234);
        if (path_pos <= *(float *)0x2533c0) {
          *(int *)(particle + 0x54) &= ~1;
          path_pos -= *(float *)(widget + 0x234);
          break;
        }
      }
    } else if (particle_type == 1) {
      while (path_pos > *(float *)(widget + 0x234)) {
        path_pos -= *(float *)(widget + 0x234);
      }
    } else {
      display_assert((char *)0x29abcc, (char *)0x29ab60, 0x320, 1);
      system_exit(-1);
    }
  } else {
    path_pos += delta;
    if (particle_type == 0) {
      if (path_pos >= *(float *)(widget + 0x234))
        goto finish;
      while (path_pos < *(float *)(widget + 0x234)) {
        path_pos += *(float *)(widget + 0x234);
      }
      if (path_pos >= *(float *)(widget + 0x234)) {
        *(int *)(particle + 0x54) |= 1;
        path_pos = *(float *)(widget + 0x234) - path_pos;
      }
    } else if (particle_type == 1) {
      while (path_pos > *(float *)(widget + 0x234))
        path_pos -= *(float *)(widget + 0x234);
    } else {
      display_assert((char *)0x29abcc, (char *)0x29ab60, 0x33d, 1);
      system_exit(-1);
    }
  }

  *(float *)(particle + 0x28) = path_pos;

finish:
  get_particle_world_position(glow_widget_ptr, particle_ptr, ratio);
}
#endif


/* 0x1342a0 — Allocate and chain glow normal particles for a widget. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(1)))
#endif
void FUN_001342a0(int glow_widget_ptr)
{
  char *widget = (char *)glow_widget_ptr;
  char *glow_def;
  int16_t count;
  int index;
  char alternate = 1;
  int previous_particle = 0;
  int particle;

  glow_def = (char *)tag_get('!wlg', *(int *)(widget + 0x224));
  count = *(int16_t *)(widget + 0x24c);
  for (index = 0; index < count; index++) {
    particle = glow_normal_particle_new(glow_widget_ptr, (short)index, count);
    if (particle == 0)
      break;

    if ((glow_def[0x28] & 2) != 0)
      *(int *)(particle + 0x54) |= 1;

    if ((glow_def[0x28] & 4) != 0) {
      if (alternate)
        *(int *)(particle + 0x54) &= ~1;
      else
        *(int *)(particle + 0x54) |= 1;
      alternate = !alternate;
    }

    if (*(int *)(widget + 0x250) == 0)
      *(int *)(widget + 0x250) = particle;
    if (previous_particle != 0)
      *(int *)(previous_particle + 0x5c) = particle;
    *(int *)(particle + 0x60) = previous_particle;
    previous_particle = particle;
    *(int *)(widget + 0x254) = particle;
  }
}

/* 0x134350 — Allocate one trailing glow particle for a widget path.
 * XBE: glow_widget_ptr arrives in EBX (@<ebx>); C export is cdecl. */
#if defined(__clang__)
static void *(*const gtpn_tag)(int, int) = tag_get;
static int (*const gtpn_dnew)(data_t *) = data_new_at_index;
static void *(*const gtpn_dget)(data_t *, int) = datum_get;
static unsigned int *(*const gtpn_seed)(void) = random_math_get_local_seed_address;
static float (*const gtpn_rrange)(int *, float, float) = random_real_range;
static void (*const gtpn_gpwp)(int, int, float) = get_particle_world_position;
static void (*const gtpn_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const gtpn_exitfn)(int) = system_exit;
static float (*const gtpn_norm)(float *) = normalize3d;
static void (*const gtpn_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
int glow_trailing_particle_new(int glow_widget_ptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 548(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movl 0x5a90cc, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[dnew]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -4(%%ebp)\n\t"
      "je .Lglow_trailing_particle_new_7\n\t"
      "movl 0x5a90cc, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -4(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, 4(%%esi)\n\t"
      "cmpw $1, 4(%%ebx)\n\t"
      "jle .Lglow_trailing_particle_new_1\n\t"
      "flds 268(%%edi)\n\t"
      "fmuls 564(%%ebx)\n\t"
      "fstps -4(%%ebp)\n\t"
      "flds 264(%%edi)\n\t"
      "movl -4(%%ebp), %%ecx\n\t"
      "fmuls 564(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "fstps -8(%%ebp)\n\t"
      "movl -8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[seed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "pushl $0\n\t"
      "fstps 40(%%esi)\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[gpwp]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lglow_trailing_particle_new_2\n\t"
      ".Lglow_trailing_particle_new_1:\n\t"
      "leal 104(%%ebx), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 44(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 4(%%eax), %%edx\n\t"
      "movl %%edx, 4(%%ecx)\n\t"
      "movl 8(%%eax), %%eax\n\t"
      "movl %%eax, 8(%%ecx)\n\t"
      ".Lglow_trailing_particle_new_2:\n\t"
      "movswl 38(%%edi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "je .Lglow_trailing_particle_new_5\n\t"
      "decl %%eax\n\t"
      "je .Lglow_trailing_particle_new_4\n\t"
      "decl %%eax\n\t"
      "je .Lglow_trailing_particle_new_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3e4\n\t"
      "pushl $0x29ab60\n\t"
      "pushl $0x29abfc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lglow_trailing_particle_new_6\n\t"
      ".Lglow_trailing_particle_new_3:\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[seed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "fstps 56(%%esi)\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[seed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "fstps 60(%%esi)\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[seed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "leal 56(%%esi), %%eax\n\t"
      "fstps 64(%%esi)\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lglow_trailing_particle_new_6\n\t"
      ".Lglow_trailing_particle_new_4:\n\t"
      "movswl 2(%%esi), %%ecx\n\t"
      "imull $0x6c, %%ecx, %%ecx\n\t"
      "leal 92(%%ecx,%%ebx,1), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 56(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 4(%%edx), %%ecx\n\t"
      "movl %%ecx, 4(%%eax)\n\t"
      "movl 8(%%edx), %%edx\n\t"
      "movl %%edx, 8(%%eax)\n\t"
      "jmp .Lglow_trailing_particle_new_6\n\t"
      ".Lglow_trailing_particle_new_5:\n\t"
      "movl %%ecx, 56(%%esi)\n\t"
      "movl %%ecx, 60(%%esi)\n\t"
      "movl $0x3f800000, 64(%%esi)\n\t"
      ".Lglow_trailing_particle_new_6:\n\t"
      "flds 260(%%edi)\n\t"
      "fmuls 0x2546a4\n\t"
      "fld %%st(0)\n\t"
      "fmuls 56(%%esi)\n\t"
      "fstps 56(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 60(%%esi)\n\t"
      "fstps 60(%%esi)\n\t"
      "fmuls 64(%%esi)\n\t"
      "fstps 64(%%esi)\n\t"
      "movl 164(%%edi), %%eax\n\t"
      "movl 160(%%edi), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, -8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -4(%%ebp)\n\t"
      "call *%[seed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fsts 32(%%esi)\n\t"
      "movswl 552(%%ebx), %%ecx\n\t"
      "movl %%ecx, -8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fildl -8(%%ebp)\n\t"
      "fdivr %%st(1), %%st(0)\n\t"
      "fstps 32(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "flds 256(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "movw %%ax, 82(%%esi)\n\t"
      "call *%[seed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "movl $0x3f800000, 12(%%esi)\n\t"
      "flds 200(%%edi)\n\t"
      "fsubs 184(%%edi)\n\t"
      "movl 84(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $2, %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 184(%%edi)\n\t"
      "fstps 16(%%esi)\n\t"
      "flds 204(%%edi)\n\t"
      "fsubs 188(%%edi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 188(%%edi)\n\t"
      "fstps 20(%%esi)\n\t"
      "flds 208(%%edi)\n\t"
      "fsubs 192(%%edi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 192(%%edi)\n\t"
      "movl %%eax, 84(%%esi)\n\t"
      "fstps 24(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      ".Lglow_trailing_particle_new_7:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(gtpn_tag), [dnew] "m"(gtpn_dnew), [dget] "m"(gtpn_dget), [seed] "m"(gtpn_seed), [rrange] "m"(gtpn_rrange), [gpwp] "m"(gtpn_gpwp), [assert] "m"(gtpn_assert), [exitfn] "m"(gtpn_exitfn), [norm] "m"(gtpn_norm), [ftol] "m"(gtpn_ftol)
      : "memory");
}
#else
int glow_trailing_particle_new(int glow_widget_ptr /* @<ebx> */)
{
  char *widget = (char *)glow_widget_ptr;
  char *glow_def;
  char *particle = 0;
  data_t *particle_table;
  int particle_index;
  int direction_type;
  float scale;
  float lifetime;
  float t;
  int *seed;
  float neg1;
  float pos1;

  glow_def = (char *)tag_get(0x676c7721, *(int *)(widget + 0x224)); /* '!wlg' */
  particle_table = *(data_t **)0x5a90cc;
  particle_index = data_new_at_index(particle_table);
  if (particle_index == -1)
    return 0;

  particle = (char *)datum_get(particle_table, particle_index);
  *(int *)(particle + 4) = particle_index;

  if (*(int16_t *)(widget + 4) > 1) {
    float path_max =
        *(float *)(glow_def + 0x10c) * *(float *)(widget + 0x234);
    float path_min =
        *(float *)(glow_def + 0x108) * *(float *)(widget + 0x234);

    seed = (int *)random_math_get_local_seed_address();
    *(float *)(particle + 0x28) = random_real_range(seed, path_min, path_max);
    get_particle_world_position((int)widget, (int)particle, 0.0f);
  } else {
    *(int *)(particle + 0x2c) = *(int *)(widget + 0x68);
    *(int *)(particle + 0x30) = *(int *)(widget + 0x6c);
    *(int *)(particle + 0x34) = *(int *)(widget + 0x70);
  }

  /* XBE: movsx/sub/dec chain on direction enum. */
  direction_type = (int)*(int16_t *)(glow_def + 0x26);
  neg1 = -1.0f;
  pos1 = 1.0f;
  switch (direction_type) {
  case 0:
    *(int *)(particle + 0x38) = 0;
    *(int *)(particle + 0x3c) = 0;
    *(int *)(particle + 0x40) = 0x3f800000;
    break;
  case 1: {
    int16_t point_index = *(int16_t *)(particle + 2);
    char *point = widget + 0x5c + (int)point_index * 0x6c;
    *(int *)(particle + 0x38) = *(int *)(point + 0);
    *(int *)(particle + 0x3c) = *(int *)(point + 4);
    *(int *)(particle + 0x40) = *(int *)(point + 8);
    break;
  }
  case 2:
    seed = (int *)random_math_get_local_seed_address();
    *(float *)(particle + 0x38) = random_real_range(seed, neg1, pos1);
    seed = (int *)random_math_get_local_seed_address();
    *(float *)(particle + 0x3c) = random_real_range(seed, neg1, pos1);
    seed = (int *)random_math_get_local_seed_address();
    *(float *)(particle + 0x40) = random_real_range(seed, neg1, pos1);
    (void)normalize3d((float *)(particle + 0x38));
    break;
  default:
    display_assert((char *)0x0029abfc, (char *)0x0029ab60, 0x3e4, 1);
    system_exit(-1);
    break;
  }

  scale = *(float *)(glow_def + 0x104) * *(float *)0x2546a4;
  *(float *)(particle + 0x38) *= scale;
  *(float *)(particle + 0x3c) *= scale;
  *(float *)(particle + 0x40) *= scale;

  seed = (int *)random_math_get_local_seed_address();
  lifetime = random_real_range(seed, *(float *)(glow_def + 0xa0),
                               *(float *)(glow_def + 0xa4));
  *(float *)(particle + 0x20) =
      lifetime / (float)*(int16_t *)(widget + 0x228);

  *(int16_t *)(particle + 0x52) =
      (int16_t)(int)(*(float *)(glow_def + 0x100) * *(float *)0x253394);

  seed = (int *)random_math_get_local_seed_address();
  t = random_real_range(seed, 0.0f, 1.0f);
  *(int *)(particle + 0xc) = 0x3f800000;
  *(int *)(particle + 0x54) = *(int *)(particle + 0x54) | 2;
  *(float *)(particle + 0x10) =
      (*(float *)(glow_def + 0xc8) - *(float *)(glow_def + 0xb8)) * t +
      *(float *)(glow_def + 0xb8);
  *(float *)(particle + 0x14) =
      (*(float *)(glow_def + 0xcc) - *(float *)(glow_def + 0xbc)) * t +
      *(float *)(glow_def + 0xbc);
  *(float *)(particle + 0x18) =
      (*(float *)(glow_def + 0xd0) - *(float *)(glow_def + 0xc0)) * t +
      *(float *)(glow_def + 0xc0);

  return (int)particle;
}
#endif



#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(2)))
#endif
void FUN_00133300(int glow_widget, int particle_ptr, int object_handle)
{
  char *widget = (char *)glow_widget;
  char *particle = (char *)particle_ptr;
  char *glow_def;
  float fn_value;
  int16_t fn_index;
  float path_ratio;
  float fade;

  glow_def = (char *)tag_get('!wlg', *(int *)(widget + 0x224));
  fn_index = *(int16_t *)(glow_def + 0xb0);
  fn_value = 0.0f;
  if (fn_index != (int16_t)-1) {
    if (!object_get_function_value(object_handle, fn_index, &fn_value))
      fn_value = 0.0f;
    *(float *)(particle + 0x10) =
        (*(float *)(glow_def + 0xc8) - *(float *)(glow_def + 0xb8)) *
            fn_value +
        *(float *)(glow_def + 0xb8);
    *(float *)(particle + 0x14) =
        (*(float *)(glow_def + 0xcc) - *(float *)(glow_def + 0xbc)) *
            fn_value +
        *(float *)(glow_def + 0xbc);
    *(float *)(particle + 0x18) =
        (*(float *)(glow_def + 0xd0) - *(float *)(glow_def + 0xc0)) *
            fn_value +
        *(float *)(glow_def + 0xc0);
    *(float *)(particle + 0xc) = 1.0f;
  } else {
    *(float *)(particle + 0xc) = 1.0f;
  }

  if ((glow_def[0x28] & 1) != 0) {
    *(float *)(particle + 0x10) =
        (*(float *)(glow_def + 0xc8) - *(float *)(glow_def + 0xb8)) *
            *(float *)(glow_def + 0xf4) * *(float *)(particle + 0x28) +
        *(float *)(glow_def + 0xb8);
    *(float *)(particle + 0x14) =
        (*(float *)(glow_def + 0xcc) - *(float *)(glow_def + 0xbc)) *
            *(float *)(glow_def + 0xf4) * *(float *)(particle + 0x28) +
        *(float *)(glow_def + 0xbc);
    *(float *)(particle + 0x18) =
        (*(float *)(glow_def + 0xd0) - *(float *)(glow_def + 0xc0)) *
            *(float *)(glow_def + 0xf4) * *(float *)(particle + 0x28) +
        *(float *)(glow_def + 0xc0);
    *(float *)(particle + 0xc) = 1.0f;
  }

  path_ratio = *(float *)(particle + 0x28) / *(float *)(widget + 0x234);
  fade = *(float *)(glow_def + 0xf8) * *(float *)0x253398;
  if (path_ratio > fade) {
    if (1.0f - fade > 0.0f)
      *(float *)(particle + 0x58) = (path_ratio - fade) / (1.0f - fade);
    else
      *(float *)(particle + 0x58) = 1.0f;
  } else {
    *(float *)(particle + 0x58) = 0.0f;
  }
  if (*(float *)(particle + 0x58) < 0.0f)
    *(float *)(particle + 0x58) = 0.0f;
  else if (*(float *)(particle + 0x58) > 1.0f)
    *(float *)(particle + 0x58) = 1.0f;
}

#if defined(__i386__) && defined(__GNUC__)
#endif
/* FUN_001330f0 (0x1330f0) — XBE naked draft (batch 152). */
#if defined(__clang__)
static void *(*const b1330f0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_001330f0(int glow_widget __attribute__((unused)), int particle_ptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x224(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_001330f0_3\n\t"
      "movswl 0x50(%%esi), %%edx\n\t"
      "movswl 0x52(%%esi), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fidivl -0x4(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fcoms 0x2533c0\n\t"
      "fsts 0x58(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001330f0_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "fstps 0x58(%%esi)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001330f0_1:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001330f0_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001330f0_2:\n\t"
      "fstps 0x58(%%esi)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001330f0_3:\n\t"
      "movl $0x3f800000, 0x58(%%esi)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b1330f0_tag)
      : "memory");
}
#else
#error "FUN_001330f0: clang naked draft required"
#endif


#if defined(__i386__) && defined(__GNUC__)
#endif
/* FUN_001331d0 (0x1331d0) — XBE naked draft (batch 148). */
#if defined(__clang__)
static void *(*const b1331d0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_001331d0(int glow_widget __attribute__((unused)), int particle_ptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl 0x224(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x20, %%cl\n\t"
      "je .LFUN_001331d0_2\n\t"
      "movswl 0x50(%%esi), %%edx\n\t"
      "movswl 0x52(%%esi), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fidivl -0x4(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001331d0_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_001331d0_1:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fstps 0x44(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "fstps 0x48(%%esi)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "fstps 0x4c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001331d0_2:\n\t"
      "leal 0x38(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $0x44, %%esi\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b1331d0_tag)
      : "memory");
}
#else
#error "FUN_001331d0: clang naked draft required"
#endif


/* 0x1345b0 — Tick glow widget particles and spawn trailing particles. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(1)))
#endif
#if defined(__clang__)
static float (*const o345b0_norm)(float *) = normalize3d;
static void (*const o345b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const o345b0_exitfn)(int) = system_exit;
static int (*const o345b0_gtime)(void) = game_time_get;
static void (*const o345b0_ddel)(data_t *, int) = datum_delete;
static void (*const o345b0_a330f0)(int, int) = FUN_001330f0;
static void (*const o345b0_a331d0)(int, int) = FUN_001331d0;
static void (*const o345b0_a33300)(int, int, int) = FUN_00133300;
static void (*const o345b0_a34070)(int, int, int, float, float) = FUN_00134070;
static void (*const o345b0_a342a0)(int) = FUN_001342a0;
static int (*const o345b0_gtpn)(int) = glow_trailing_particle_new;
static bool (*const o345b0_ogfv)(int, short, void *) = object_get_function_value;
static short (*const o345b0_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void *(*const o345b0_tag)(int, int) = tag_get;
static void (*const o345b0_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void FUN_001345b0(int glow_widget __attribute__((unused)), int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x224(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "je .LFUN_001345b0_39\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $5\n\t"
      "leal 0x8(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "movb 0x2(%%ebx), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "jne .LFUN_001345b0_13\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .LFUN_001345b0_20\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_001345b0_5\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "leal 0x70(%%ebx), %%edi\n\t"
      ".LFUN_001345b0_1:\n\t"
      "leal 0x70(%%ebx), %%eax\n\t"
      "movl $0xffffffff, -0x10(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001345b0_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001345b0_2:\n\t"
      "cmpw %%si, -0x8(%%ebp)\n\t"
      "je .LFUN_001345b0_4\n\t"
      "flds -0x8(%%eax)\n\t"
      "fsubs -0x8(%%edi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x4(%%eax)\n\t"
      "fsubs -0x4(%%edi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds (%%eax)\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "fsubs (%%edi)\n\t"
      "pushl %%eax\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x24(%%edi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x28(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x2c(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "jne .LFUN_001345b0_3\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001345b0_4\n\t"
      ".LFUN_001345b0_3:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001345b0_4:\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "incl %%esi\n\t"
      "addl $0x6c, %%eax\n\t"
      "cmpw %%cx, %%si\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_001345b0_2\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, (%%eax)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "incl %%edx\n\t"
      "addl $2, %%eax\n\t"
      "addl $0x6c, %%edi\n\t"
      "cmpw %%cx, %%dx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_001345b0_1\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      ".LFUN_001345b0_5:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001345b0_10\n\t"
      "movswl %%ax, %%edx\n\t"
      "incl %%eax\n\t"
      "leal 0x22a(%%ebx,%%edx,2), %%edx\n\t"
      "movzwl %%ax, %%esi\n\t"
      ".LFUN_001345b0_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "decw %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001345b0_9\n\t"
      ".LFUN_001345b0_7:\n\t"
      "movswl %%ax, %%edi\n\t"
      "cmpw %%cx, -0x24(%%ebp,%%edi,2)\n\t"
      "je .LFUN_001345b0_8\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_001345b0_7\n\t"
      "jmp .LFUN_001345b0_9\n\t"
      ".LFUN_001345b0_8:\n\t"
      "movw %%ax, (%%edx)\n\t"
      ".LFUN_001345b0_9:\n\t"
      "subl $2, %%edx\n\t"
      "decl %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "jne .LFUN_001345b0_6\n\t"
      ".LFUN_001345b0_10:\n\t"
      "movswl 0x4(%%ebx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%eax, 0x234(%%ebx)\n\t"
      "movl %%eax, 0x238(%%ebx)\n\t"
      "jle .LFUN_001345b0_12\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001345b0_11:\n\t"
      "movswl 0x22a(%%ebx,%%eax,2), %%edx\n\t"
      "movswl 0x22c(%%ebx,%%eax,2), %%esi\n\t"
      "imull $0x6c, %%edx, %%edx\n\t"
      "imull $0x6c, %%esi, %%esi\n\t"
      "leal 0x8(%%edx,%%ebx,1), %%edx\n\t"
      "addl $0x60, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal 0x8(%%esi,%%ebx,1), %%esi\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "addl $0x60, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "incl %%ecx\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fadds 0x234(%%ebx)\n\t"
      "fsts 0x234(%%ebx)\n\t"
      "fstps 0x23c(%%ebx,%%eax,4)\n\t"
      "movswl 0x4(%%ebx), %%edx\n\t"
      "movswl %%cx, %%eax\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_001345b0_11\n\t"
      ".LFUN_001345b0_12:\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[a342a0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x258(%%ebx)\n\t"
      "movb $1, 0x2(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001345b0_13:\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .LFUN_001345b0_20\n\t"
      "movl 0x64(%%esi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x60(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001345b0_16\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ogfv]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001345b0_14\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001345b0_15\n\t"
      ".LFUN_001345b0_14:\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".LFUN_001345b0_15:\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fsubs 0x68(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x68(%%esi)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001345b0_16:\n\t"
      "movl 0x74(%%esi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x70(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LFUN_001345b0_19\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ogfv]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001345b0_17\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001345b0_18\n\t"
      ".LFUN_001345b0_17:\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".LFUN_001345b0_18:\n\t"
      "flds 0x7c(%%esi)\n\t"
      "fsubs 0x78(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x78(%%esi)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001345b0_19:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      ".LFUN_001345b0_20:\n\t"
      "call *%[gtime]\n\t"
      "addw %%ax, 0x258(%%ebx)\n\t"
      "cmpw $1, 0x4(%%ebx)\n\t"
      "jle .LFUN_001345b0_23\n\t"
      "movl 0x250(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001345b0_23\n\t"
      ".LFUN_001345b0_21:\n\t"
      "testb $2, 0x54(%%esi)\n\t"
      "jne .LFUN_001345b0_22\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "flds 0x50654c\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[a34070]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "call *%[a33300]\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ecx, 0x24(%%esi)\n\t"
      ".LFUN_001345b0_22:\n\t"
      "movl 0x5c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001345b0_21\n\t"
      ".LFUN_001345b0_23:\n\t"
      "movl 0x250(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001345b0_32\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001345b0_24:\n\t"
      "testb $2, 0x54(%%esi)\n\t"
      "je .LFUN_001345b0_31\n\t"
      "call *%[gtime]\n\t"
      "addw %%ax, 0x50(%%esi)\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[a330f0]\n\t"
      "movl 0x224(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_001345b0_26\n\t"
      "movswl 0x50(%%esi), %%eax\n\t"
      "movswl 0x52(%%esi), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "fidivl -0x18(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001345b0_25\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_001345b0_25:\n\t"
      "fmuls 0x20(%%esi)\n\t"
      "fstps 0x24(%%esi)\n\t"
      ".LFUN_001345b0_26:\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[a331d0]\n\t"
      "movl 0x224(%%ebx), %%eax\n\t"
      "movl 0x50654c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x676c7721\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "fadds 0x2c(%%esi)\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x48(%%esi)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4c(%%esi)\n\t"
      "fadds 0x34(%%esi)\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movl 0x224(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x676c7721\n\t"
      "call *%[tag]\n\t"
      "movw 0x50(%%esi), %%dx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw 0x52(%%esi), %%dx\n\t"
      "jle .LFUN_001345b0_31\n\t"
      "movl 0x60(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "je .LFUN_001345b0_27\n\t"
      "movl %%ecx, 0x5c(%%eax)\n\t"
      "jmp .LFUN_001345b0_28\n\t"
      ".LFUN_001345b0_27:\n\t"
      "movl %%ecx, 0x250(%%ebx)\n\t"
      ".LFUN_001345b0_28:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001345b0_29\n\t"
      "movl %%eax, 0x60(%%ecx)\n\t"
      "jmp .LFUN_001345b0_30\n\t"
      ".LFUN_001345b0_29:\n\t"
      "movl %%eax, 0x254(%%ebx)\n\t"
      ".LFUN_001345b0_30:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x5a90cc, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ddel]\n\t"
      "addl $8, %%esp\n\t"
      "decw 0x24c(%%ebx)\n\t"
      ".LFUN_001345b0_31:\n\t"
      "movl 0x5c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001345b0_24\n\t"
      ".LFUN_001345b0_32:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "flds 0xfc(%%ecx)\n\t"
      "fcomps 0x25bb10\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001345b0_38\n\t"
      "flds 0x253394\n\t"
      "fdivs 0xfc(%%ecx)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001345b0_33\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      ".LFUN_001345b0_33:\n\t"
      "movswl 0x258(%%ebx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001345b0_38\n\t"
      ".LFUN_001345b0_34:\n\t"
      "call *%[gtpn]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001345b0_37\n\t"
      "movl 0x254(%%ebx), %%ecx\n\t"
      "incw 0x24c(%%ebx)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001345b0_35\n\t"
      "movl %%eax, 0x5c(%%ecx)\n\t"
      "movl 0x254(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x60(%%eax)\n\t"
      "jmp .LFUN_001345b0_36\n\t"
      ".LFUN_001345b0_35:\n\t"
      "movl %%eax, 0x250(%%ebx)\n\t"
      ".LFUN_001345b0_36:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl %%eax, 0x254(%%ebx)\n\t"
      "call *%[ftol]\n\t"
      "subw %%ax, 0x258(%%ebx)\n\t"
      "movswl 0x258(%%ebx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001345b0_34\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001345b0_37:\n\t"
      "pushl $1\n\t"
      "pushl $0x209\n\t"
      "pushl $0x29ab60\n\t"
      "pushl $0x29ac28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001345b0_38:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001345b0_39:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(o345b0_norm), [assert] "m"(o345b0_assert), [exitfn] "m"(o345b0_exitfn), [gtime] "m"(o345b0_gtime), [ddel] "m"(o345b0_ddel), [a330f0] "m"(o345b0_a330f0), [a331d0] "m"(o345b0_a331d0), [a33300] "m"(o345b0_a33300), [a34070] "m"(o345b0_a34070), [a342a0] "m"(o345b0_a342a0), [gtpn] "m"(o345b0_gtpn), [ogfv] "m"(o345b0_ogfv), [markers] "m"(o345b0_markers), [tag] "m"(o345b0_tag), [ftol] "m"(o345b0_ftol)
      : "memory");
}
#else
void FUN_001345b0(int glow_widget, int object_handle)
{
  char *widget = (char *)glow_widget;
  char *glow_def;
  int16_t marker_count;
  float spawn_rate;
  float spawn_base;
  float secondary_rate;
  float secondary_base;
  int particle;
  int16_t tick;
  float trail_step;

  glow_def = (char *)tag_get('!wlg', *(int *)(widget + 0x224));
  if (glow_def == (char *)0)
    return;

  marker_count = (int16_t)object_get_markers_by_string_id(
      object_handle, widget + 8, glow_def, 5);
  *(int16_t *)(widget + 4) = marker_count;

  if (widget[2] == 0) {
    if (marker_count > 1) {
      int16_t point_index;
      int16_t row;
      int16_t best_index;
      float best_dot;
      int16_t marker_indices[5];
      char *point_row;

      for (row = 0; row < marker_count; row++) {
        best_index = (int16_t)-1;
        best_dot = -1.0f;
        point_row = widget + 0x70 + row * 0x6c;
        for (point_index = 0; point_index < marker_count; point_index++) {
          char *point = widget + 8 + point_index * 0x6c;
          float delta[3];
          float dot;
          delta[0] = *(float *)(point + 0x58) - *(float *)(point_row + 0x58);
          delta[1] = *(float *)(point + 0x5c) - *(float *)(point_row + 0x5c);
          delta[2] = *(float *)(point + 0x60) - *(float *)(point_row + 0x60);
          normalize3d(delta);
          dot = delta[0] * *(float *)(point_row + 0x34) +
                delta[1] * *(float *)(point_row + 0x38) +
                delta[2] * *(float *)(point_row + 0x3c);
          if (dot > best_dot) {
            best_dot = dot;
            best_index = point_index;
          }
        }
        marker_indices[row] = best_index;
      }

      for (row = 0; row < marker_count; row++)
        *(int16_t *)(widget + 0x22a + row * 2) = marker_indices[row];

      *(float *)(widget + 0x234) = 0.0f;
      for (row = 0; row + 1 < marker_count; row++) {
        int16_t a = *(int16_t *)(widget + 0x22a + row * 2);
        int16_t b = *(int16_t *)(widget + 0x22a + row * 2 + 2);
        char *pa = widget + 8 + (int)a * 0x6c + 0x60;
        char *pb = widget + 8 + (int)b * 0x6c + 0x60;
        float dx = *(float *)pb - *(float *)pa;
        float dy = *(float *)(pb + 4) - *(float *)(pa + 4);
        float dz = *(float *)(pb + 8) - *(float *)(pa + 8);
        float seg = dx * dx + dy * dy + dz * dz;
        float len = seg > 0.0f ? sqrtf(seg) : 0.0f;
        *(float *)(widget + 0x23c + row * 4) = len;
        *(float *)(widget + 0x234) += len;
      }

      FUN_001342a0(glow_widget);
      *(int16_t *)(widget + 0x258) = 0;
      widget[2] = 1;
      return;
    }
  }

  spawn_base = *(float *)(glow_def + 0x64);
  spawn_rate = spawn_base;
  if (marker_count > 1) {
    if (*(int16_t *)(glow_def + 0x60) != (int16_t)-1) {
      float fn_value = 0.0f;
      if (!object_get_function_value(object_handle, *(int16_t *)(glow_def + 0x60),
                                    &fn_value))
        fn_value = 0.0f;
      spawn_rate =
          ((*(float *)(glow_def + 0x6c) - *(float *)(glow_def + 0x68)) * fn_value +
           *(float *)(glow_def + 0x68)) *
          spawn_base;
    }

    secondary_base = *(float *)(glow_def + 0x74);
    secondary_rate = secondary_base;
    if (*(int16_t *)(glow_def + 0x70) != (int16_t)-1) {
      float fn_value = 0.0f;
      if (!object_get_function_value(object_handle, *(int16_t *)(glow_def + 0x70),
                                    &fn_value))
        fn_value = 0.0f;
      secondary_rate =
          ((*(float *)(glow_def + 0x7c) - *(float *)(glow_def + 0x78)) * fn_value +
           *(float *)(glow_def + 0x78)) *
          secondary_base;
    }
    spawn_rate = spawn_rate / secondary_rate;
  } else {
    secondary_rate = *(float *)(glow_def + 0x74);
  }

  tick = (int16_t)game_time_get();
  *(int16_t *)(widget + 0x258) += tick;

  if (*(int16_t *)(widget + 4) > 1) {
    int p = *(int *)(widget + 0x250);
    while (p != 0) {
      char *particle_ptr = (char *)p;
      if ((*(unsigned char *)(particle_ptr + 0x54) & 2) == 0) {
        float ratio = spawn_rate;
        float delta = *(float *)0x50654c * secondary_rate;
        FUN_00134070(glow_widget, p, object_handle, delta, ratio);
        FUN_00133300(glow_widget, p, object_handle);
        *(float *)(particle_ptr + 0x24) = *(float *)(particle_ptr + 0x20);
      }
      p = *(int *)(particle_ptr + 0x5c);
    }
  }

  {
    int p = *(int *)(widget + 0x250);
    float dt = *(float *)0x50654c;
    while (p != 0) {
      char *particle_ptr = (char *)p;
      if ((*(unsigned char *)(particle_ptr + 0x54) & 2) != 0) {
        char *def;
        *(int16_t *)(particle_ptr + 0x50) += (int16_t)game_time_get();
        FUN_001330f0(glow_widget, p);
        def = (char *)tag_get('!wlg', *(int *)(widget + 0x224));
        if ((def[0x28] & 0x10) != 0) {
          int16_t age = *(int16_t *)(particle_ptr + 0x50);
          int16_t life = *(int16_t *)(particle_ptr + 0x52);
          float ratio;
          if (life <= 0)
            ratio = 0.0f;
          else {
            ratio = 1.0f - (float)age / (float)life;
            if (ratio < 0.0f)
              ratio = 0.0f;
          }
          *(float *)(particle_ptr + 0x24) = ratio * *(float *)(particle_ptr + 0x20);
        }
        FUN_001331d0(glow_widget, p);
        *(float *)(particle_ptr + 0x2c) +=
            dt * *(float *)(particle_ptr + 0x44);
        *(float *)(particle_ptr + 0x30) +=
            dt * *(float *)(particle_ptr + 0x48);
        *(float *)(particle_ptr + 0x34) +=
            dt * *(float *)(particle_ptr + 0x4c);

        if (*(int16_t *)(particle_ptr + 0x50) >
            *(int16_t *)(particle_ptr + 0x52)) {
          int prev = *(int *)(particle_ptr + 0x60);
          int next = *(int *)(particle_ptr + 0x5c);
          if (prev != 0)
            *(int *)(prev + 0x5c) = next;
          else
            *(int *)(widget + 0x250) = next;
          if (next != 0)
            *(int *)(next + 0x60) = prev;
          else
            *(int *)(widget + 0x254) = prev;
          datum_delete(*(data_t **)0x5a90cc,
                       *(int *)(particle_ptr + 4));
          *(int16_t *)(widget + 0x24c) -= 1;
        }
      }
      p = *(int *)(particle_ptr + 0x5c);
    }
  }

  if (*(float *)(glow_def + 0xfc) <= *(float *)0x25bb10)
    return;

  trail_step = *(float *)0x253394 / *(float *)(glow_def + 0xfc);
  if (trail_step > 1.0f)
    trail_step = 1.0f;

  while ((float)*(int16_t *)(widget + 0x258) >= trail_step) {
    particle = glow_trailing_particle_new(glow_widget);
    if (particle == 0) {
      display_assert((char *)0x0029ac28, (char *)0x0029ab60, 0x209, 1);
      system_exit(-1);
    }
    {
      int prev = *(int *)(widget + 0x254);
      *(int16_t *)(widget + 0x24c) += 1;
      if (prev != 0)
        *(int *)(prev + 0x5c) = particle;
      else
        *(int *)(widget + 0x250) = particle;
      *(int *)(particle + 0x60) = prev;
      *(int *)(widget + 0x254) = particle;
    }
    *(int16_t *)(widget + 0x258) -= (int16_t)(int)trail_step;
  }
}
#endif


/* 0x134c40 — Resolve light-volume marker state, optionally blending nested states. */
void *FUN_00134c40(int light_tag, int object_handle)
{
  static const int k_lerp_offsets[] = {
      0x10, 0x14, 0x18, 0x3c, 0x40, 0x44, 0x68, 0x6c,
      0x70, 0x74, 0x78, 0x7c, 0x80, 0x84, 0x88, 0x8c,
  };
  char *tag;
  void *marker_block;
  void *fallback_state;
  void *outer_state;
  void *inner_state;
  float fn_value;
  float *blend_base;
  int i;

  if (light_tag == 0) {
    display_assert((char *)0x00269eb4, (char *)0x0029ac98, 110, 1);
    system_exit(-1);
  }

  tag = (char *)light_tag;
  marker_block = tag + 0x120;
  fallback_state = tag_block_get_element(marker_block, 0, 0xb0);
  if (*(int *)marker_block <= 1)
    return tag_block_get_element(marker_block, 0, 0xb0);

  outer_state = tag_block_get_element(marker_block, 0, 0xb0);
  inner_state = tag_block_get_element(outer_state, 0, 0xb0);
  fn_value = 0.0f;
  if (!object_get_function_value(object_handle,
                                 (short)(*(int16_t *)(tag + 0xb8) - 1),
                                 &fn_value))
    return fallback_state;

  blend_base = (float *)0x46ef70;
  for (i = 0; i < (int)(sizeof(k_lerp_offsets) / sizeof(k_lerp_offsets[0])); i++) {
    int off = k_lerp_offsets[i];
    *(float *)((char *)blend_base + off) =
        (1.0f - fn_value) * *(float *)((char *)outer_state + off) +
        fn_value * *(float *)((char *)inner_state + off);
  }
  return blend_base;
}

/* 0x135420 — jitter a marker position in local marker space. */
void lightning_offset_marker_position(int matrix_ptr, float *position_out,
                                      float *random_bounds)
{
  float *matrix = (float *)(uintptr_t)matrix_ptr;
  float rnd_z;
  float rnd_y;
  float rnd_x;
  float offset[3];
  float one = *(float *)0x2533c8;

  if (!position_out) {
    display_assert((char *)0x00267114, (char *)0x0029acfc, 0x74, 1);
    system_exit(-1);
  }
  if (!matrix) {
    display_assert((char *)0x0026af40, (char *)0x0029acfc, 0x75, 1);
    system_exit(-1);
  }
  if (!random_bounds) {
    display_assert((char *)0x0029ad34, (char *)0x0029acfc, 0x76, 1);
    system_exit(-1);
  }

  rnd_z = random_math_real(random_math_get_local_seed_address());
  rnd_y = random_math_real(random_math_get_local_seed_address());
  rnd_x = random_math_real(random_math_get_local_seed_address());
  offset[0] = (rnd_x + rnd_x - one) * random_bounds[0];
  offset[1] = (rnd_y + rnd_y - one) * random_bounds[1];
  offset[2] = (rnd_z + rnd_z - one) * random_bounds[2];
  matrix_scale_transform_vector(matrix, offset, offset);
  position_out[0] += offset[0];
  position_out[1] += offset[1];
  position_out[2] += offset[2];
}

/* 0x13df70 — free an object header's node-matrix pool block and delete it. */
void object_postprocess_node_matrices(data_t *data, int object_handle)
{
  char *header;
  void **block_ref;

  header = (char *)datum_get(data, object_handle);
  block_ref = (void **)(header + 8);
  if (*block_ref != 0)
    memory_pool_block_free(*(void **)0x46f080, block_ref);
  datum_delete(data, object_handle);
  header[2] = 0;
  *block_ref = 0;
}

/* object_update (0x1444f0) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void *(*const b1444f0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1444f0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1444f0_tag)(int, int) = tag_get;
static void (*const b1444f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1444f0_exitfn)(int) = system_exit;
static int (*const b1444f0_c13c5c0)(int param_1) = FUN_0013c5c0;
static void (*const b1444f0_c1384e0)(int object_handle) = object_damage_update;
static void (*const b1444f0_c13c620)(int param_1) = FUN_0013c620;
static void (*const b1444f0_c141b70)(int object_handle) = object_compute_node_matrices;
static void (*const b1444f0_c13e7b0)(int object_handle) = object_compute_function_values;
static void (*const b1444f0_c13e5d0)(int object_handle) = object_compute_change_colors;
static void (*const b1444f0_c13ee60)(int object_handle, char do_wake, char do_limbo) = object_propagate_flag_to_children;
static char (*const b1444f0_c1444f0)(int object_handle) = object_update;
static void * (*const b1444f0_c13dfc0)(int object_handle, void *reference) = object_header_block_reference_get;
static void (*const b1444f0_c13c800)(int object_handle, void *block_data) = FUN_0013c800;

__attribute__((naked, noinline))
char object_update(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a8d50, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $0x10, %%al\n\t"
      "jne .Lobject_update_12\n\t"
      "testl $0x10000, 0x4(%%esi)\n\t"
      "je .Lobject_update_1\n\t"
      "movl 0x46f084, %%eax\n\t"
      "incw 0x4(%%eax)\n\t"
      ".Lobject_update_1:\n\t"
      "cmpw $0, 0x86(%%esi)\n\t"
      "je .Lobject_update_4\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl $0xfe0, %%edx\n\t"
      "je .Lobject_update_2\n\t"
      "pushl $1\n\t"
      "pushl $0x9cc\n\t"
      "pushl $0x29b91c\n\t"
      "pushl $0x29bf80\n\t"
      "call *%[assert]\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lobject_update_3\n\t"
      ".Lobject_update_2:\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".Lobject_update_3:\n\t"
      "incw 0x84(%%esi)\n\t"
      "movw 0x84(%%esi), %%ax\n\t"
      "cmpw 0x86(%%esi), %%ax\n\t"
      "jl .Lobject_update_5\n\t"
      "movw $0, 0x86(%%esi)\n\t"
      "jmp .Lobject_update_5\n\t"
      ".Lobject_update_4:\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".Lobject_update_5:\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c5c0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x7c(%%eax), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Lobject_update_6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1384e0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_update_6:\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c620]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl $0x800000, %%eax\n\t"
      "jne .Lobject_update_7\n\t"
      "pushl %%edi\n\t"
      "call *%[c141b70]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_update_7:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13e7b0]\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13e5d0]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testb $0x20, %%ah\n\t"
      "je .Lobject_update_9\n\t"
      "testb $1, %%al\n\t"
      "je .Lobject_update_8\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jne .Lobject_update_9\n\t"
      ".Lobject_update_8:\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c13ee60]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_update_9:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lobject_update_10\n\t"
      "pushl %%eax\n\t"
      "call *%[c1444f0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_update_10:\n\t"
      "cmpl %%ebx, 0xcc(%%esi)\n\t"
      "je .Lobject_update_11\n\t"
      "movl 0xc4(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lobject_update_11\n\t"
      "pushl %%esi\n\t"
      "call *%[c1444f0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_update_11:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Lobject_update_12\n\t"
      "cmpl %%ebx, 0x44(%%eax)\n\t"
      "je .Lobject_update_12\n\t"
      "addl $0x1a0, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c13dfc0]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c800]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lobject_update_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1444f0_dget), [get] "m"(b1444f0_get), [tag] "m"(b1444f0_tag), [assert] "m"(b1444f0_assert), [exitfn] "m"(b1444f0_exitfn), [c13c5c0] "m"(b1444f0_c13c5c0), [c1384e0] "m"(b1444f0_c1384e0), [c13c620] "m"(b1444f0_c13c620), [c141b70] "m"(b1444f0_c141b70), [c13e7b0] "m"(b1444f0_c13e7b0), [c13e5d0] "m"(b1444f0_c13e5d0), [c13ee60] "m"(b1444f0_c13ee60), [c1444f0] "m"(b1444f0_c1444f0), [c13dfc0] "m"(b1444f0_c13dfc0), [c13c800] "m"(b1444f0_c13c800)
      : "memory");
}
#else
#error "object_update: clang naked draft required"
#endif

