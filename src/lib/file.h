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

int farrename(const char far* old, const char far* new);
#pragma aux farrename = \
    ASM(push ds) \
    ASM(mov ds, dx) \
    ASM(mov dx, ax) \
    ASM(mov ah, DOS_FILE_RENAME) \
    ASM(int INTERRUPT_DOS) \
    ASM(mov ax, 0) \
    ASM(jnc end) \
    ASM(mov ax, -1) \
    ASM(end:) \
    ASM(pop ds) \
    parm [ax dx] [es di] \
    value [ax] \
    modify [ax dx];

int farmkdir(const char far* path);
#pragma aux farmkdir = \
    ASM(push ds) \
    ASM(mov ds, dx) \
    ASM(mov dx, ax) \
    ASM(mov ah, DOS_DIRECTORY_CREATE) \
    ASM(int INTERRUPT_DOS) \
    ASM(mov ax, -1) \
    ASM(jnc end) \
    ASM(xor ax, ax) \
    ASM(end:) \
    ASM(pop ds) \
    parm [ax dx] \
    value [ax] \
    modify [ax dx];
