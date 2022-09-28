#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    unsigned char* data;
    long i;
    long capacity;
    long size;
} bufferstream;

static bool ensurecapacity(bufferstream* stream, size_t writeSize) {
    unsigned char* newData;
    long additionalCapacity = stream->i - stream->capacity + writeSize;
    if (additionalCapacity > 0) {
        additionalCapacity = additionalCapacity > 256 ? additionalCapacity : 256;
        newData = realloc(stream->data, stream->capacity + additionalCapacity);
        if (newData) {
            memset(&newData[stream->capacity], 0, additionalCapacity);
            stream->capacity += additionalCapacity;
            stream->data = newData;
            return true;
        } else {
            return false;
        }
    }
    return true;
}

bufferstream* bsopen(long capacity) {
    bufferstream* stream = malloc(sizeof(bufferstream));
    if (!stream) {
        return NULL;
    }
    stream->i = 0;
    stream->size = 0;
    if (capacity > 0) {
        stream->data = calloc(capacity, 1);
        if (!stream->data) {
            free(stream);
            return NULL;
        }
    } else {
        stream->data = NULL;
    }
    stream->capacity = capacity;
    return stream;
}

int bsclose(bufferstream* stream) {
    if (stream->data) {
        free(stream->data);
        stream->data = NULL;
    }
    free(stream);
    return 0;
}

int bsseek(bufferstream* stream, long offset, int whence) {
    unsigned char* newData;
    if (whence == SEEK_SET) {
        stream->i = offset;
    } else if (whence == SEEK_CUR) {
        stream->i += offset;
    } else if (whence == SEEK_END) {
        stream->i = stream->size + offset;
    }
    return 0;
}

long bstell(bufferstream* stream) {
    return stream->i;
}

int bsputw(int w, bufferstream* stream) {
    if (!ensurecapacity(stream, sizeof(w))) {
        return EOF;
    }
    stream->data[stream->i++] = (unsigned char)((int)w >> 8);
    stream->data[stream->i++] = w & 0xFF;
    if (stream->i > stream->size) stream->size = stream->i;
    return 0;
}

int bsputc(int c, bufferstream* stream) {
    if (!ensurecapacity(stream, 1)) {
        return EOF;
    }
    stream->data[stream->i++] = c & 0xFF;
    if (stream->i > stream->size) stream->size = stream->i;
    return 1;
}

int bsgetc(bufferstream* stream) {
    if (stream->i < stream->size) {
        return stream->data[stream->i++];
    } else {
        return EOF;
    }
}

size_t bswrite(const void *ptr, size_t size, size_t nmemb, bufferstream* stream) {
    unsigned const char* dataPtr = (unsigned const char*)ptr;
    unsigned long total = size * nmemb;
    unsigned i = 0;
    if (!ensurecapacity(stream, total)) {
        return 0;
    }
    for (i = 0; i < total; ++i) {
        stream->data[stream->i++] = dataPtr[i];
    }
    if (stream->i > stream->size) stream->size = stream->i;
    return (size_t)total;
}

size_t bsread(void *ptr, size_t size, size_t nmemb, bufferstream* stream) {
    unsigned char* dataPtr = (unsigned char*)ptr;
    unsigned long total = size * nmemb;
    unsigned i = 0;
    for (i = 0; i < total && stream->i < stream->size; ++i) {
        dataPtr[i] = stream->data[stream->i++];
    }
    return i / size;
}

bufferstream* bsinput(const char* path) {
    FILE* fp = fopen(path, "rb");
    bufferstream* stream = NULL;
    long read = 0, previous = 0, filesize = 0;
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    stream = bsopen(filesize);
    if (!stream) {
        fclose(fp);
        return NULL;
    }

    while (read < filesize) {
        previous = fread(&stream->data[read], 1, filesize - read, fp);
        if (previous) {
            read += previous;
        } else {
            fclose(fp);
            bsclose(stream);
            return NULL;
        }
    }
    stream->size = filesize;

    fclose(fp);
    return stream;
}


bool bsoutput(bufferstream* stream, const char* path) {
    FILE* fp = fopen(path, "wb");
    long written = 0, previous = 0;
    if (!fp) return false;
    while (written < stream->size) {
        previous = fwrite(stream->data, 1, stream->size - written, fp);
        if (previous) {
            written += previous;
        } else {
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}
