/* Cross-module XDK/CRT prototypes referenced from relifted amalgamation files. */
#pragma once

#include <stddef.h>

int __stdcall XapiFormatFATVolume(void *device_path);
void XcSHAInit(int ctx);
void XcSHAUpdate(int a, int b, int c);
void XcSHAFinal(int a, int b);
void ExQueryNonVolatileSetting(int a, int b, int c, int d);
void XcRC4Key(int a, int b, int c);
void XcRC4Crypt(int a, int b, int c);
void XcKeyTable(int a, int b);
void XcBlockCryptCBC(int a, int b, int c, int d);
void XcModExp(int a, int b, int c, int d);
void XcHMAC(int a, int b, int c, int d);
void XcDESKeyParity(int a, int b);
extern int DbgPrint(unsigned long fmt, ...);
void RtlUnwind(void *a, void *b, void *c, void *d);
