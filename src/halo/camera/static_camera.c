/* --- static_camera.obj batch drafts (2026-07-26) --- */

/* FUN_0008d410 (0x8d410) — readable C lift (restored pre-naked). */
void FUN_0008d410(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x8d439 */
  display_assert((char *)0x00266e9c, (char *)0x002676d8, 36, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x8d45d */
  display_assert((char *)0x0025b57c, (char *)0x002676d8, 37, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x8d481 */
  display_assert((char *)0x0025f120, (char *)0x002676d8, 38, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x8d827 */
  /* relift: test byte ptr [esi], 1 -> je 0x8d826 */
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  /* test (char)eax, 1 -> jne 0x8d76e */
  csprintf((char *)0x005ab100, (char *)0x00266e08);

  (void)eax;
  (void)esi;
  (void)edi;
}

