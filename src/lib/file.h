#include <stdbool.h>
#include "types.h"
#include "intrpt.h"

typedef int _FFILE;

bool fileExists(const char far* path);
long fileSize(const char far* path);
bool directoryExists(const char far* path);
bool fileNameValid(const char* name);
unsigned int checksum(const char* path);
unsigned int checksumPartial(const char* path, long offset, unsigned int max);
_FFILE *farfopen(const char* pathname, const char* mode);
unsigned long farfread(void huge* ptr, unsigned long size, unsigned long nmemb, _FFILE* stream);
int farfputc(int c, _FFILE* stream);
int farfseek(_FFILE* stream, long offset, int whence);
long farftell(_FFILE* stream);
int farfclose(_FFILE* stream);
int rename(const char* old, const char* new);
#pragma aux rename = \
    ASM(push ds) \
    ASM(mov ds, ax) \
    ASM(mov ah, DOS_FILE_RENAME) \
    ASM(int INTERRUPT_DOS) \
    ASM(mov ax, 0) \
    ASM(jnc end) \
    ASM(mov ax, -1) \
    ASM(end:) \
    ASM(pop ds) \
    parm [ax dx] [es di] \
    value [ax];

int mkdir(const char far* path);
#pragma aux mkdir = \
    ASM(push ds) \
    ASM(mov ds, ax) \
    ASM(mov ah, DOS_DIRECTORY_CREATE) \
    ASM(int INTERRUPT_DOS) \
    ASM(mov ax, -1) \
    ASM(jnc end) \
    ASM(xor ax, ax) \
    ASM(end:) \
    ASM(pop ds) \
    parm [ax dx] \
    value [ax];
