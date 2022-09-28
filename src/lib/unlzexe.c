#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "types.h"
#include "bstream.h"

#define getw(a) _getw(a)

#define EXE_MAGIC1 0x5A4D
#define EXE_MAGIC2 0x4D5A

#define LZEXE_COMPRESSED_RELOCATION_TABLE_ADDRESS 0x158

typedef struct {
    WORD e_magic;                     // Magic number
    WORD e_cblp;                      // Bytes on last page of file
    WORD e_cp;                        // Pages in file
    WORD e_crlc;                      // Relocations
    WORD e_cparhdr;                   // Size of header in paragraphs
    WORD e_minalloc;                  // Minimum extra paragraphs needed
    WORD e_maxalloc;                  // Maximum extra paragraphs needed
    WORD e_ss;                        // Initial (relative) SS value
    WORD e_sp;                        // Initial SP value
    WORD e_csum;                      // Checksum
    WORD e_ip;                        // Initial IP value
    WORD e_cs;                        // Initial (relative) CS value
    WORD e_lfarlc;                    // File address of relocation table
    WORD e_ovno;                      // Overlay number
    WORD e_res[2];                    // Reserved words
} IMAGE_DOS_HEADER;

typedef struct {
    WORD e_ip;                        // Initial IP value
    WORD e_cs;                        // Initial (relative) CS value
    WORD e_sp;                        // Initial SP value
    WORD e_ss;                        // Initial (relative) SS value
    WORD e_clmc;                      // Size of compressed load module in paragraphs
    WORD e_clmi;                      // Size increase load module in paragraphs
    WORD e_cde;                       // Size of decompressor with compressed relocation table in bytes
    WORD e_csum;                      // Check sum of decompresser with compressd relocation table
} LZEXE_INFO;

typedef struct {
    FILE  *fp;
    WORD  buf;
    BYTE  count;
} bitstream;

static long loadsize;

/* get compress information bit by bit */
void initbits(bitstream *p, FILE *filep){
    p->fp = filep;
    p->count = 0x10;
    p->buf = getw(filep);
}

int getbit(bitstream *p) {
    int b;
    b = p->buf & 1;
    if (--p->count == 0) {
        (p->buf) = getw(p->fp);
        p->count = 0x10;
    } else {
        p->buf >>= 1;
    }
    
    return b;
}

bool isCompressed(const char* path) {
    IMAGE_DOS_HEADER header;
    FILE* inputFile = fopen(path, "rb");
    if (!inputFile) return false;
    
    if (fread(&header, 1, sizeof(IMAGE_DOS_HEADER), inputFile) != sizeof(IMAGE_DOS_HEADER)) {
        fclose(inputFile);
        return false;
    }
    fclose(inputFile);

    if ((header.e_magic != EXE_MAGIC1 && header.e_magic != EXE_MAGIC2) || header.e_cparhdr != 2 || header.e_ovno != 0)
        return false;
    if (header.e_lfarlc == 0x1c && !memcmp(&header.e_res, "LZ91", sizeof(header.e_res))) {
        return true;
    }
    return false;
    
}

static bool readHeader(FILE *inputFile, IMAGE_DOS_HEADER* inputHeader, IMAGE_DOS_HEADER* outputHeader) {
    if (fread(inputHeader, 1, sizeof(IMAGE_DOS_HEADER), inputFile) != sizeof(IMAGE_DOS_HEADER))
        return false;

    memcpy(outputHeader, inputHeader, sizeof(IMAGE_DOS_HEADER));

    if ((inputHeader->e_magic != EXE_MAGIC1 && inputHeader->e_magic != EXE_MAGIC2) || inputHeader->e_cparhdr != 2 || inputHeader->e_ovno != 0)
        return false;
    if (inputHeader->e_lfarlc == 0x1c && !memcmp(&inputHeader->e_res, "LZ91", sizeof(inputHeader->e_res))) {
        return true;
    }
    return false;
}

/* for LZEXE ver 0.91*/
static bool reloc91(FILE *inputFile, bufferstream *outputFile, long fpos, IMAGE_DOS_HEADER* outputHeader) {
    WORD span;
    WORD rel_count = 0;
    WORD rel_seg,rel_off;

    fseek(inputFile, fpos + LZEXE_COMPRESSED_RELOCATION_TABLE_ADDRESS, SEEK_SET);
    rel_off = 0;
    rel_seg = 0;
    for(;;) {
        if (feof(inputFile) || ferror(inputFile)) return false;
        if ((span = getc(inputFile)) == 0) {
            span = getw(inputFile);
            if (span == 0){
                rel_seg += 0x0fff;
                continue;
            } else if (span == 1){
                break;
            }
        }
        rel_off += span;
        rel_seg += (rel_off & ~0x0f) >> 4;
        rel_off &= 0x0f;
        bsputw(rel_off, outputFile);
        bsputw(rel_seg, outputFile);
        rel_count++;
    }
    outputHeader->e_crlc = rel_count;
    return true;
}

/*-------------------------------------------*/
/* make relocation table */
static bool makeRelocationTable(FILE *inputFile, bufferstream *outputFile, IMAGE_DOS_HEADER* inputHeader, IMAGE_DOS_HEADER* outputHeader, LZEXE_INFO* packInfo) {
    long fpos;
    int i;

    fpos = (long)(inputHeader->e_cs + inputHeader->e_cparhdr) << 4;		/* goto CS:0000 */

    fseek(inputFile, fpos, SEEK_SET);
    fread(packInfo, sizeof(LZEXE_INFO), 1, inputFile);
    outputHeader->e_ip = packInfo->e_ip;		/* IP */
    outputHeader->e_cs = packInfo->e_cs;		/* CS */
    outputHeader->e_sp = packInfo->e_sp;		/* SP */
    outputHeader->e_ss = packInfo->e_ss;		/* SS */
    /* inf[4]:size of compressed load module (PARAGRAPH)*/
    /* inf[5]:increase of load module size (PARAGRAPH)*/
    /* inf[6]:size of decompressor with  compressed relocation table (BYTE) */
    /* inf[7]:check sum of decompresser with compressd relocation table(Ver.0.90) */

    outputHeader->e_lfarlc = 0x1C;		/* start position of relocation table */
    bsseek(outputFile, 0x1C, SEEK_SET);
    i = reloc91(inputFile, outputFile, fpos, outputHeader);

    if (!i) {
        return false;
    }

    fpos = bstell(outputFile);
    i = fpos & 0x1ff;
    if (i) {
        i = 0x200 - i;
    }
    outputHeader->e_cparhdr = (fpos + i) >> 4;
    
    for(; i > 0; i--)
        bsputc(0, outputFile);
    return true;
}

/*---------------------*/
/* decompressor routine */
static bool unpack(FILE *inputFile, bufferstream *outputFile, IMAGE_DOS_HEADER* inputHeader, IMAGE_DOS_HEADER* outputHeader, LZEXE_INFO* packInfo) {
    int len;
    int span;
    long fpos;
    bitstream bits;
    BYTE *data, *p;
    data = malloc(0x4500);
    if (!data) return false;
    p = data;
    
    fpos = (long)(inputHeader->e_cs - packInfo->e_clmc + inputHeader->e_cparhdr) << 4;
    fseek(inputFile, fpos, SEEK_SET);
    fpos = (long)outputHeader->e_cparhdr << 4;
    bsseek(outputFile, fpos, SEEK_SET);
    initbits(&bits, inputFile);
    for (;;) {
        if (ferror(inputFile)) {
            free(data);
            return false;
        }
        if (p - data > 0x4000){
            bswrite(data, sizeof data[0], 0x2000, outputFile);
            p -= 0x2000;
            memcpy(data, data + 0x2000, p - data);
        }
        if (getbit(&bits)) {
            *p++ = getc(inputFile);
            continue;
        }
        if (!getbit(&bits)) {
            len = getbit(&bits) << 1;
            len |= getbit(&bits);
            len += 2;
            span = getc(inputFile) | 0xff00;
        } else {
            span = (BYTE)getc(inputFile);
            len = getc(inputFile);
            span |= ((len & ~0x07)<<5) | 0xe000;
            len = (len & 0x07)+2; 
            if (len == 2) {
                len = getc(inputFile);

                if (len == 0)
                    break;    /* end mark of compreesed load module */

                if (len == 1)
                    continue; /* segment change */
                else
                    len++;
            }
        }
        for(; len > 0; len--, p++){
            *p = *(p + span);
        }
    }
    if (p != data)
        bswrite(data, sizeof data[0], p - data, outputFile);
    loadsize = bstell(outputFile) - fpos;
    free(data);
    return true;
}

static void writeHeader(bufferstream *outputFile, IMAGE_DOS_HEADER* inputHeader, IMAGE_DOS_HEADER* outputHeader, LZEXE_INFO* packInfo) {
    if (inputHeader->e_maxalloc != 0) {
        outputHeader->e_minalloc -= packInfo->e_clmi + ((packInfo->e_cde + 16 - 1 ) >> 4) + 9;
        if (inputHeader->e_maxalloc != 0xFFFF) {
            outputHeader->e_maxalloc -= (inputHeader->e_minalloc - outputHeader->e_minalloc);
        }
    }
    outputHeader->e_cblp = (loadsize + (outputHeader->e_cparhdr << 4)) & 0x1FF;
    outputHeader->e_cp = (loadsize + (outputHeader->e_cparhdr << 4) + 0x1FF) >> 9;
    bsseek(outputFile, 0L, SEEK_SET);
    bswrite(outputHeader, sizeof(WORD), 0x0E, outputFile);
}


bufferstream* performUnpack(const char* path) {
    IMAGE_DOS_HEADER inputHeader, outputHeader;
    LZEXE_INFO packInfo;
    bufferstream* outputBuffer;
    long fpos;
    FILE *inputFile = fopen(path, "rb");
    if (!inputFile) {
        return NULL;
    }
    if (!readHeader(inputFile, &inputHeader, &outputHeader)){
        fclose(inputFile);
        return NULL;
    }
    fpos = (long)(inputHeader.e_cs + inputHeader.e_cparhdr) << 4;		/* goto CS:0000 */
    fseek(inputFile, fpos, SEEK_SET);
    fread(&packInfo, sizeof(LZEXE_INFO), 1, inputFile);
    outputBuffer = bsopen(((packInfo.e_clmc + packInfo.e_clmi) << 4) * 1);
    if (!outputBuffer) {
        fclose(inputFile);
        return NULL;
    }


    if (!makeRelocationTable(inputFile, outputBuffer, &inputHeader, &outputHeader, &packInfo)) {
        fclose(inputFile);
        bsclose(outputBuffer);
        return NULL;
    }
    if (!unpack(inputFile, outputBuffer, &inputHeader, &outputHeader, &packInfo)) {
        fclose(inputFile);
        bsclose(outputBuffer);
        return NULL;
    }
    fclose(inputFile);
    writeHeader(outputBuffer, &inputHeader, &outputHeader, &packInfo);

    return outputBuffer;
    
}
