#include <stdio.h>
typedef struct {
    char _dummy;
} bufferstream;

bufferstream* bsopen(long capacity);
int bsclose(bufferstream* stream);
int bsseek(bufferstream* stream, long offset, int whence);
long bstell(bufferstream* stream);
int bsputw(int w, bufferstream* stream);
int bsputc(int c, bufferstream* stream);
int bsgetc(bufferstream* stream);
size_t bswrite(const void *ptr, size_t size, size_t nmemb, bufferstream* stream);
size_t bsread(void *ptr, size_t size, size_t nmemb, bufferstream* stream);
bufferstream* bsinput(const char* path);
bool bsoutput(bufferstream* stream, const char* path);
