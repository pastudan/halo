/* ui_widget_text_search_and_replace_function_invoke (0xf5290) — readable C lift from XBE leaf. */
wchar_t *ui_widget_text_search_and_replace_function_invoke(void *widget, unsigned short function_index)
{
  extern char DAT_002832a8[];
  extern char DAT_0028a748[];
  wchar_t *(*fn)(void *);

  if (widget == 0) {
    display_assert(DAT_002832a8, DAT_0028a748, 0x2d, true);
    system_exit(-1);
  }
  if ((short)function_index < 0 || function_index >= 2)
    return (wchar_t *)0x28a730;
  fn = ((wchar_t *(**)(void *))0x31e5a4)[function_index];
  return fn(widget);
}


