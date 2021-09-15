#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "types.h"
#include "bstream.h"
#include "unlzexe.h"

static const int EXE_MAGIC1 = 0x5A4D; // MZ
static const int EXE_MAGIC2 = 0x4D5A; // ZM

static const char ASC2COM_SIGNATURE[] = "ASC2COM  V1.75";

#define EXE_HEADER_SIZE_OFFSET 0x08
#define ASC2COM_SIGNATURE_OFFSET 0x127
#define ASC2COM_DATA_OFFSET 0x1B5

#define LZEXE_COMPRESSED_RELOCATION_TABLE_ADDRESS 0x158

static bool reallocatePrintMeBuffer(int* buffersize, char** buffer) {
    char* newBuffer = NULL;
    *buffersize += 64;
    newBuffer = realloc(*buffer, *buffersize);
    if (!newBuffer) {
        free(buffer);
        return false;
    } else {
        *buffer = newBuffer;
        return true;
    }
}

static char* parseBufferStream(bufferstream* bsp, int* parseSize) {
    int i = 0;
    int buffersize = 64; // base size
    int count = 0;
    int entry = 0;
    uint16_t headersize = 0;
    uint16_t header = 0;
    char signatureBuffer[15];
    char* buffer = NULL;

    bsseek(bsp, 0, SEEK_END);
    buffersize += bstell(bsp);
    buffer = malloc(buffersize);

    if (!buffer) {
        bsclose(bsp);
        return NULL;
    }
    bsseek(bsp, 0, SEEK_SET);

    // Check if the file has been converted to an EXE file and if so, skip the header
    if (!bsread(&header, sizeof(uint16_t), 1, bsp)) {
        free(buffer);
        bsclose(bsp);
        return NULL;
    }
    if (header == EXE_MAGIC1 || header == EXE_MAGIC2) {
        bsseek(bsp, EXE_HEADER_SIZE_OFFSET, SEEK_SET);
        if (!bsread(&headersize, sizeof(uint16_t), 1, bsp)) {
            free(buffer);
            bsclose(bsp);
            return NULL;
        }
        headersize <<= 4; // Size is in paragraphs, i.e. 16 bytes
    }

    bsseek(bsp, headersize + ASC2COM_SIGNATURE_OFFSET, SEEK_SET);
    if (bsread(signatureBuffer, sizeof(char), sizeof(signatureBuffer) - 1, bsp) != sizeof(signatureBuffer) - 1) {
            free(buffer);
            bsclose(bsp);
            return NULL;
    }
    signatureBuffer[sizeof(signatureBuffer) - 1] = '\0';
    if (strcmp(signatureBuffer, ASC2COM_SIGNATURE)) {
        fprintf(stderr, "ASC2COM V1.75 signature mismatch!\n");
        free(buffer);
        bsclose(bsp);
        return NULL;
    }

    bsseek(bsp, headersize + ASC2COM_DATA_OFFSET, SEEK_SET);
    while (true) {
        count = bsgetc(bsp);
        if (count == EOF) {
            if (buffersize <= i + 2) {
                if (!reallocatePrintMeBuffer(&buffersize, &buffer)) {
                    bsclose(bsp);
                    return NULL;
                }
            }
            buffer[i++] = '\x1A';
            buffer[i] = '\0';
            *parseSize = i;
            break;
        }

        if (buffersize <= i + count) { // Make sure there's room
            if (!reallocatePrintMeBuffer(&buffersize, &buffer)) {
                bsclose(bsp);
                return NULL;
            }
        }

        while (count > 0) {
            entry = bsgetc(bsp);
            if (entry == '\x09') {
                if (buffersize <= (i + 8 + count)) {
                    if (!reallocatePrintMeBuffer(&buffersize, &buffer)) {
                        bsclose(bsp);
                        return NULL;
                    }
                }
                memset(&buffer[i], ' ', 8);
                i += 8;
            } else {
                buffer[i++] = entry;
            }
            count--;
        }
        buffer[i++] = '\r';
        buffer[i++] = '\n';
    }

    return buffer;
}

char* parsePrintMe(const char* path, int* parseSize) {
    char* formBuffer;
    bufferstream* buffer = isCompressed(path) ? performUnpack(path) : bsinput(path);
    if (!buffer) {
        return NULL;
    }
    formBuffer = parseBufferStream(buffer, parseSize);
    bsclose(buffer);
    return formBuffer;
}
