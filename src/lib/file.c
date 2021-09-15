#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "intrpt.h"
#include "file.h"
#include "memory.h"
#include "input.h"
#include "types.h"

#pragma pack(push, 1)
struct FileInfoRec {
    BYTE reserved[21];
    BYTE bAttr;
    WORD rTime;
    WORD rDate;
    DWORD lSize;
    char szFilespec[13];
};
#pragma pack(pop)

enum FileAttribute {
    ATTRIBUTE_READ_ONLY = 1 << 0,
    ATTRIBUTE_HIDDEN    = 1 << 1,
    ATTRIBUTE_SYSTEM    = 1 << 2,
    ATTRIBUTE_VOLUME    = 1 << 3,
    ATTRIBUTE_DIRECTORY = 1 << 4,
    ATTRIBUTR_ARCHIVE   = 1 << 5
};

static volatile const struct FileInfoRec far* dtaPtr = NULL;

const struct FileInfoRec far* getdta();
#pragma aux getdta = \
    ASM(mov ah, DOS_GET_DTA) \
    ASM(int INTERRUPT_DOS) \
    value [es bx];

bool fileNameValid(const char* name) {
    int i = 0, namel = 0, extl = 0;
    const char* p = name;
    bool extension = false;
    while (*p) {
        if (*p == '.') {
            if (extension) return false;
            extension = true;
        } else {
            extension ? ++extl : ++namel;
        }
        ++p;
    }
    return extl <= 3 && namel <= 8;
}

static bool findFirstFile(const char far* path, int attributes, bool updateDta) {
    // const char far* fPath = (const char far*)path;
    int segAddress = FP_SEG(path);
    int offAddress = FP_OFF(path);
    int error = 0;
    _asm {
        push ds
        mov ah, DOS_FIND_FIRST_FILE
        mov ds, segAddress
        mov dx, offAddress
        mov cx, attributes
        int INTERRUPT_DOS
        jnc end
        mov error, ax
        end:
        pop ds
    }
    if (updateDta) {
        dtaPtr = getdta();
    }
    return error ? false : true;
}

long fileSize(const char far* path) {
    // const struct FileInfoRec far*;
    if (findFirstFile(path, 0, true)) {
        return dtaPtr->bAttr & (ATTRIBUTE_DIRECTORY | ATTRIBUTE_SYSTEM | ATTRIBUTE_VOLUME) ? -1 : dtaPtr->lSize;
    } else {
        return -1;
    }
}

bool fileExists(const char far* path) {
    return fileSize(path) != -1;
}

bool directoryExists(const char far* path) {
    if (findFirstFile(path, ATTRIBUTE_DIRECTORY, false)) {
        return true;
    } else {
        return false;
    }
}

unsigned int checksum(const char* path) {
    unsigned int checksum = 0;
    unsigned int ch = 0;
    FILE* fp = fopen(path, "rb");
    if (!fp) return 0;

    for (ch = getc(fp); ch != EOF; ch = getc(fp)) {
        checksum = (checksum >> 1) + ((checksum & 1) << 15);
        checksum += ch;
    }
    fclose(fp);

    return checksum;
}

unsigned int checksumPartial(const char* path, long offset, unsigned int max) {
    unsigned int checksum = 0;
    unsigned int ch = 0;
    unsigned int count = 0;
    FILE* fp = fopen(path, "rb");
    if (!fp) return 0;
    if (offset) {
        fseek(fp, offset, SEEK_SET);
    }

    for (ch = getc(fp); ch != EOF && count++ < max; ch = getc(fp)) {
        checksum = (checksum >> 1) + ((checksum & 1) << 15);
        checksum += ch;
    }
    fclose(fp);

    return checksum;
}

static _FFILE *createFile(const char far* pathname);
#pragma aux createFile = \
    ASM(push ds) \
    ASM(mov ds, ax) \
    ASM(mov ah, DOS_FILE_CREATE) \
    ASM(int INTERRUPT_DOS) \
    ASM(jnc end) \
    ASM(mov ax, 0) \
    ASM(end:) \
    ASM(pop ds) \
    parm [ax dx] \
    value [ax];

_FFILE *farfopen(const char* pathname, const char* mode) {
    _FFILE* file = NULL;
    const char far* pathFar = (const char far*)pathname;
    int pathSeg = FP_SEG(pathFar);
    int pathOff = FP_OFF(pathFar);
    int error = 0;
    unsigned char accessMode = 0;
    bool read = false, write = false, append = false;
    const char* p = mode;
    while (*p) {
        if (*p == 'r') read = true;
        else if (*p == 'w') write = true;
        ++p;
    }
    if (write) return createFile(pathname);
    if (read && write) accessMode = 2;
    else if (write) accessMode = 1;
    else if (read) accessMode = 0;
    _asm {
        push ds
        mov ah, DOS_FILE_OPEN
        mov al, 0
        mov ds, pathSeg
        mov dx, pathOff
        int INTERRUPT_DOS
        jnc end
        mov error, ax
        mov ax, 0
        end:
        mov file, ax
        pop ds
    }
    return file;
}

unsigned long farfread(void huge* ptr, unsigned long size, unsigned long nmemb, _FFILE* stream) {
    unsigned int buffSeg, buffOff;
    int error = 0;
    unsigned int count = 0, read = 0;
    unsigned long offset = 0;
    unsigned long remaining = size * nmemb;

    while (remaining) {
        count = (unsigned long)remaining > USHRT_MAX ? USHRT_MAX : remaining;
        buffSeg = FP_SEG((char huge*)ptr + offset);
        buffOff = FP_OFF((char huge*)ptr + offset);
        _asm {
            push ds
            mov ah, DOS_FILE_READ
            mov bx, stream
            mov cx, count
            mov ds, buffSeg
            mov dx, buffOff
            int INTERRUPT_DOS
            jnc end
            mov error, ax
            mov ax, 0
            end:
            mov read, ax
            pop ds
        }
        if (error) {
            break;
        } else {
            remaining -= read;
            offset += read;
        }

    }
    return offset;
}

int farfputc(int c, _FFILE* stream) {
    char far* ptr = (char far*)&c;
    unsigned int buffSeg = FP_SEG(ptr);
    unsigned int buffOff = FP_OFF(ptr);
    int error = 0, written = 0;
    _asm {
        push ds
        mov bx, stream
        mov cx, 1
        mov ah, DOS_FILE_WRITE
        mov ds, buffSeg
        mov dx, buffOff
        int INTERRUPT_DOS
        mov written, ax
        jnc end
        mov error, ax
        end:
        pop ds
    }
    if (error || written != 1) return EOF;
    return c;
}

int farfseek(_FFILE* stream, long offset, int whence) {
    unsigned char twhence = whence;
    unsigned int high, low, error = 0;
    low = (int)offset;
    high = (int)(long)(offset >> 16);
    _asm {
        mov ah, DOS_FILE_SEEK
        mov bx, stream
        mov al, twhence
        mov cx, 0
        mov dx, 0
        int INTERRUPT_DOS
        jnc end
        mov error, ax
        end:
    }
    return error ? -1 : 0;
}

long farftell(_FFILE* stream) {
    unsigned int low = 0, high = 0;
    long result = 0;
    _asm {
        mov ah, DOS_FILE_SEEK
        mov al, 1
        mov cx, 0
        mov dx, 0
        mov bx, stream
        int INTERRUPT_DOS
        mov high, dx
        mov low, ax
    }
    result = (long)high << 16;
    result |= low;
    return result;
}

int farfclose(_FFILE* stream) {
    int result = 0;
    _asm {
        mov ah, DOS_FILE_CLOSE
        mov bx, stream
        int INTERRUPT_DOS
        jnc end
        mov result, ax
        end:
    }
    if (result) {
        result = EOF;
    }
    return result;
}
