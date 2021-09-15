#include <stddef.h>
#include "../version.h"

#define FP_SEG(__p) ((unsigned)((unsigned long)(void __far*)(__p) >> 16))
#define FP_OFF(__p) ((unsigned)(__p))
#define MK_FP(__s,__o) (((unsigned short)(__s)):>((void __near *)(__o)))

void far* farmalloc(unsigned long size);
void far* farcalloc(unsigned long nmemb, unsigned long size);
void farfree(void far* ptr);
void far* farrealloc(void far* ptr, unsigned long size);
char huge *_hstristr(const char huge *haystack, const char huge *needle);
void huge* _hmemcpy(void huge* dest, const void huge* src, unsigned long n);
void huge* _hmemset(void huge* s, int c, unsigned long n);

#ifndef RELEASE
void heapdump();
void mcbdump();
#endif
