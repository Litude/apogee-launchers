#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "memory.h"
#include "intrpt.h"
#include "types.h"
#include "input.h"

#ifndef RELEASE
    #include <stdio.h>
    #include <process.h>
    #include <malloc.h>
#endif

#pragma pack(push, 1)
struct MCB {
    BYTE bSignature;
    WORD wOwnerID;
    WORD wSizeParas;
    BYTE res[3];
    BYTE szOwnerName[8];
};
#pragma pack(pop)
typedef struct MCB huge *PTRMCB;

void far* farmalloc(unsigned long size) {
    unsigned int numBlocks = (unsigned long)(size + 15) >> 4;
    unsigned int allocSegment = 0;
    void far *pointer = NULL;
    _asm {
        mov ah, DOS_MEMORY_ALLOCATE
        mov bx, numBlocks
        int INTERRUPT_DOS
        jc end
        mov allocSegment, ax
        end:
    }
    if (allocSegment) {
        pointer = MK_FP(allocSegment, 0);
        return pointer;
    } else {
        return NULL;
    }
}

void far* farcalloc(unsigned long nmemb, unsigned long size) {
    unsigned long total = nmemb * (unsigned long)size;
    void far* ptr = farmalloc(total);
    if (ptr) {
        if (total > USHRT_MAX || (unsigned long)FP_OFF(ptr) + total > 0xFFFF) {
            _hmemset(ptr, 0, total);
        } else {
            _fmemset(ptr, 0, total);
        }
        return ptr;
    } else {
        return NULL;
    }
}

void farfree(void far* ptr) {
    int segment = FP_SEG(ptr);
    int error = 0;
    if (ptr == NULL) return;
    _asm {
        mov ah, DOS_MEMORY_FREE
        mov es, segment
        int INTERRUPT_DOS
        jnc end
        mov error, ax
        end:
    }
}

void far* farrealloc(void far* ptr, unsigned long size) {
    unsigned int numBlocks = (unsigned long)(size + 15) >> 4;
    void far* newPtr;
    int segment = FP_SEG(ptr);
    int error = 0;
    struct MCB huge* mcbPtr;
    if (ptr == NULL) return farmalloc(size);
    _asm {
        mov ah, DOS_MEMORY_REALLOCATE
        mov es, segment
        mov bx, numBlocks
        int INTERRUPT_DOS
        jnc end
        mov error, ax
        end:
    }
    if (error) {
        mcbPtr = (struct MCB huge*)((char huge*)ptr - 16);
        if (mcbPtr->bSignature != 'M' && mcbPtr->bSignature != 'Z') return NULL;
        newPtr = farmalloc(size);
        if (newPtr) {
            _hmemcpy(newPtr, ptr, mcbPtr->wSizeParas << 4);
            farfree(ptr);
            return newPtr;
        }
    }
    return ptr;
}

void huge* _hmemset(void huge* s, int c, unsigned long n) {
    long i;
    char huge* charS;
    for (i = 0; i < n; ++i) {
        *charS++ = (unsigned char)c;
    }
    return s;
}

void huge* _hmemcpy(void huge* dest, const void huge* src, unsigned long n) {
    const char huge* s = src;
    char huge* d;
    for (d = dest; n; --n) {
        *d++ = *s++;
    }
    return dest;
}

char huge *_hstristr(const char huge *haystack, const char huge *needle) {
    unsigned long i;
    int c = tolower((unsigned char)*needle);
    if (c == '\0')
        return (char huge*)haystack;
    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == c) {
            for (i = 0;;) {
                if (needle[++i] == '\0')
                    return (char huge*)haystack;
                if (tolower((unsigned char)haystack[i]) != tolower((unsigned char)needle[i]))
                    break;
            }
        }
    }
    return NULL;
}

#ifndef RELEASE
unsigned long freememoryavailable() {
    unsigned int paras;
    unsigned long result = 0;
    _asm {
        mov ah, DOS_MEMORY_ALLOCATE
        mov bx, 0xFFFF
        int INTERRUPT_DOS
        mov paras, bx
        end:
    }
    result = ((unsigned long)paras) << 4;
    return result;
}

void heapdump() {
    struct _heapinfo h_info;
    int heap_status, used = 0;
    size_t usedsize = 0;

    printf("Memory available: %u\n", _memavl());
    h_info._pentry = NULL;
    for(;;) {
        heap_status = _heapwalk( &h_info );
        if( heap_status != _HEAPOK ) break;
        printf( "  %s block at %Fp of size %4.4X\n",
        (h_info._useflag == _USEDENTRY ? "USED" : "FREE"),
        h_info._pentry, h_info._size );
        if (h_info._useflag == _USEDENTRY) {
            ++used;
            usedsize += h_info._size;
        };
    }

    switch( heap_status ) {
        case _HEAPEND:
        printf( "OK - end of heap\n" );
        break;
        case _HEAPEMPTY:
        printf( "OK - heap is empty\n" );
        break;
        case _HEAPBADBEGIN:
        printf( "ERROR - heap is damaged\n" );
        break;
        case _HEAPBADPTR:
        printf( "ERROR - bad pointer to heap\n" );
        break;
        case _HEAPBADNODE:
        printf( "ERROR - bad node in heap\n" );
    }
    printf("%d blocks in use totaling %4.4X\n", used, usedsize);
}

static void far *ffmcb(void) {
    int varseg;
    int varoff;
    unsigned far *segmptr;
    _asm {
        mov ah, DOS_GET_VARIABLES
        int INTERRUPT_DOS
        mov varseg, es
        mov varoff, bx
    }
    segmptr = MK_FP(varseg,varoff - 2);
    return MK_FP(*segmptr, 0);
}

static void prn_header (void) {
    printf ("===================================================");
    puts   ("================");
    puts   ("MCB MCB  ID PID      MB PAR- ENV  OWNER");
    puts   ("NO. SEG            SIZE ENT  BLK?");
    printf ("===================================================");
    puts   ("================");
}


static void prn_pid_own (unsigned pid,unsigned parent) {
    unsigned far *envsegptr;  /* Pointer to seg address of environment*/
    char far *envptr;         /* Pointer to pid's environment         */
    unsigned far *envsizeptr; /* Pointer to envsize word below        */
    unsigned envsize;         /* Size of pid's environment            */

    static unsigned char ccnum = 0;
    static unsigned prev_pid = 0xFFFF;

    switch (pid)
    {
        /* Assign owner names for two special cases                  */
        case 0 : puts ("FREE MEMORY CONTROL BLOCK");return;
        case 8 : puts ("IBMDOS.COM/MSDOS.SYS");return;
    }

    envsegptr = (unsigned far *) MK_FP (pid,0x2C);

    envptr = (char far *) MK_FP (*envsegptr,0);
    envsizeptr = (unsigned  far *) MK_FP(*envsegptr-1,0x3);
    envsize = *envsizeptr*16;

    if (pid == parent)
    {
        if (prev_pid != pid) ccnum++;
        printf ("COMMAND.COM COPY #%-2u\n",ccnum);

        prev_pid = pid;        /* Save current pid - will be previous   */
        return;                /*  in the next call to this function    */
    }

    while (envsize)
    {
        while (--envsize && *envptr++);
        if (!*envptr && *(unsigned far *) (envptr+1) == 0x1)
        {
        envptr +=3;           /* Correct pattern found (00 00 01 00) */
        break;                /* so point envptr to owner string     */
        }
    }

    if (envsize)
    {
        while(*envptr) putchar(*envptr++);
        putchar('\n');
    }
    else
        puts ("UNKNOWN OWNER");
}

static void prn_mcb (PTRMCB pm) {
    static cnt = 0;
    static mcbnum = 1;
    unsigned parid;
    unsigned mcbseg;
    char envf;
    unsigned envseg;

    /* Get parent id located at pid:16H                              */
    parid = * (unsigned far *) MK_FP (pm->wOwnerID,0x16);

    mcbseg = FP_SEG (pm);    /* Segment address of the MCB            */

    envseg = * (unsigned far *) MK_FP(pm->wOwnerID,0x2C);
    envf = mcbseg+1 ==  envseg ? 'Y' : 'N';
    if (parid == pm->wOwnerID) cnt++;
    if (!envseg && cnt == 2) envf = 'Y';

    printf("%2.2u%06.4X%2.1c%06.4X%7lu%5.4X %-5.1c",
    mcbnum++,mcbseg,pm->bSignature,pm->wOwnerID,(long) pm->wSizeParas*16,parid,envf);


    prn_pid_own(pm->wOwnerID,parid);
}

void mcbdump() {
    PTRMCB ptrmcb;
    ptrmcb = (PTRMCB) ffmcb();
    prn_header ();
    prn_mcb(ptrmcb);
    
    do {
        ptrmcb += ptrmcb->wSizeParas + 1;   /* Get pointer to next MCB       */
        prn_mcb(ptrmcb);               /* Print out information for MCB */
    } while (ptrmcb->bSignature == 'M');  /* as long as not at end of chain*/
                                    /*Print out final decoration.    */
    printf ("========================================================");
    puts   ("===========");
    printf("Free memory available for allocation: %lu\n", freememoryavailable());
}

#endif
