/* --- data_packet_groups.obj batch drafts (2026-07-26) --- */

/* 0x11abb0 */
void data_packet_group_append_packet_header(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0028f318, (char *)0x0028f1f0, 172, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi], 0 -> jge 0x11ac12 */
  display_assert((char *)0x0028f3c4, (char *)0x0028f1f0, 173, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x11ac24 */
  /* relift: cmp (int16_t)ebx, word ptr [eax + 4] -> jl 0x11ac44 */
  display_assert((char *)0x0028f380, (char *)0x0028f1f0, 174, 0);
  system_exit(0);
  /* cmp ecx, eax -> jae 0x11ac7d */
  FUN_00118be0((void *)0x003220c0, (void *)(uintptr_t)esi, 0);
  /* mem[0x0046e804] = eax */
  /* mem[0x0046e804] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x11aca0 */
bool encode_packet_group(group_definition *group, void *data, char *encoded_buf, int32_t *encoded_size, int16_t type, int one)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0028f408, (char *)0x0028f1f0, 132, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x11ace3 */
  /* relift: cmp (int16_t)esi, word ptr [edi + 4] -> jl 0x11ad03 */
  display_assert((char *)0x0028f380, (char *)0x0028f1f0, 133, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x11ad11 */
  /* test eax, eax -> jne 0x11ad31 */
  display_assert((char *)0x0028f318, (char *)0x0028f1f0, 134, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x11ad61 */
  display_assert((char *)0x0028f3f4, (char *)0x0028f1f0, 139, 0);
  system_exit(0);
  FUN_0011b650(0, 0, (void *)(uintptr_t)ecx, (char *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x11ada2 */
  data_packet_group_append_packet_header();
  /* test (char)eax, (char)eax -> jne 0x11ada9 */
  /* mem[0x0046e804] = eax */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x11add0 */
void compute_packet_field_sizes(packet_definition *def, short *param_2, short *param_3, short *param_4)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0x11ae03 */
  /* cmp (int16_t)eax, 0xa -> jl 0x11ae34 */
  csprintf((char *)0x005ab100, (char *)0x0028f450);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], 0 -> jg 0x11ae6c */
  csprintf((char *)0x005ab100, (char *)0x0028f41c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [esi + 4] -> jl 0x11af20 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jle 0x11ae8c */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x11af20 */
  /* cmp eax, 9 -> ja 0x11af03 */
  /* relift: tail-call compute_packet_field_sizes(); */
  display_assert((char *)0, (char *)0x0028f498, 193, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x11af5d */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x11afa0 */
void _data_packet_encode(int param_1, int *param_2, short param_3, void *param_4, short param_5, int param_6, short *param_7)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp (int16_t)ecx, word ptr [esi + 4] -> jl 0x11b199 */
  /* cmp (int16_t)ecx, (int16_t)eax -> jle 0x11afe0 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x11b199 */
  /* cmp eax, 8 -> ja 0x11b190 */
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  FUN_0011a230((void *)(uintptr_t)ebx, (char *)(uintptr_t)edi, 0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x11b063 */
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jle 0x11b083 */
  display_assert((char *)0x0028f4f0, (char *)0x0028f498, 253, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x11b08e */
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jle 0x11b090 */
  FUN_00119df0((void *)(uintptr_t)ebx, 0, 0);
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  compute_packet_field_sizes((void *)(uintptr_t)edx, (void *)0, (void *)(uintptr_t)eax, (void *)0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x11b0ff */
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jle 0x11b11f */
  display_assert((char *)0x0028f4c0, (char *)0x0028f498, 281, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x11b12a */
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jle 0x11b12c */
  FUN_00119df0((void *)(uintptr_t)ebx, 0, 0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x11b181 */
  /* relift: tail-call _data_packet_encode(); */
  /* cmp eax, 8 -> ja 0x11b1e7 */
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  FUN_00119cc0((void *)(uintptr_t)ebx, 0, 0, 0);
  FUN_00119df0((void *)(uintptr_t)ebx, 0, 0);
  display_assert((char *)0, (char *)0x0028f498, 324, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x11b23d */
  /* test eax, eax -> je 0x11b24a */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 4] -> jl 0x11b50a */
  /* cmp (int16_t)ecx, (int16_t)eax -> jle 0x11b2e0 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x11b50a */
  /* cmp eax, 7 -> ja 0x11b407 */
  FUN_0011a430((void *)(uintptr_t)edi, 0, 0);
  /* test eax, eax -> je 0x11b407 */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, ecx);
  FUN_0011a430((void *)(uintptr_t)edi, 0, 0);
  /* test eax, eax -> je 0x11b407 */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, ecx);
  FUN_0011a430((void *)(uintptr_t)edi, 0, 0);
  /* test eax, eax -> je 0x11b407 */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, ecx);
  FUN_0011a430((void *)(uintptr_t)edi, 0, 0);
  /* test eax, eax -> je 0x11b407 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
