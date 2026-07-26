/* ui_widget_text_search_and_replace_function_invoke (0xf5290) — XBE naked draft (batch 95). */
#if defined(__clang__)
static void (*const bf5290_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf5290_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
wchar_t *ui_widget_text_search_and_replace_function_invoke(void *widget, unsigned short function_index)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lui_widget_text_search_and_replace_function_invoke_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2d\n\t"
      "pushl $0x28a748\n\t"
      "pushl $0x2832a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_text_search_and_replace_function_invoke_1:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lui_widget_text_search_and_replace_function_invoke_2\n\t"
      "cmpw $2, %%ax\n\t"
      "jae .Lui_widget_text_search_and_replace_function_invoke_2\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%esi\n\t"
      "call *0x31e5a4(,%%eax,4)\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_text_search_and_replace_function_invoke_2:\n\t"
      "movl $0x28a730, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf5290_assert), [exitfn] "m"(bf5290_exitfn)
      : "memory");
}
#else
#error "ui_widget_text_search_and_replace_function_invoke: clang naked draft required"
#endif

