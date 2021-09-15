#include <string.h>
#include <stdbool.h>
#include "output.h"
#include "intrpt.h"

void drawColorChar(int x, int y, int color, char character) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    video[0] = character;
    video[1] = color;
}

void farDrawTextLine(int y, int color, const char huge *string) {
    int i = 0;
    char far *video = (char far *)0xb8000000 + 2 * 80 * y;
    while( string && string[i] != '\0' )
    {
        video[2*i] = string[i];
        video[2*i+1] = color;
        ++i;
    }
    while (i < 80) {
        video[2*i] = ' ';
        video[2*i+1] = color;
        ++i;
    }
}

void drawTextLine(int y, int color, const char *string) {
    drawIndentTextLine(y, 0, color, string);
}

void drawIndentTextLine(int y, int x, int color, const char *string) {
    int i = 0;
    char far *video = (char far *)0xb8000000 + 2 * 80 * y;
    while (i < x) {
        video[2*i] = ' ';
        video[2*i+1] = color;
        ++i;
    }
    while( string && *string )
    {
        video[2*i] = *string++;
        video[2*i+1] = color;
        ++i;
    }
    while (i < 80) {
        video[2*i] = ' ';
        video[2*i+1] = color;
        ++i;
    }
}

void drawWideHighlightText(int x, int y, int width, int highlightColor, int normalColor, const char* string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    int i = 0;
    while (i++ < width) {
        *video++ = *string++;
        *video++ = highlightColor;
    }
    while (*string) {
        *video++ = *string++;
        *video++ = normalColor;
    }
}

void drawHighlightText(int x, int y, int highlightColor, int normalColor, const char* string) {
    drawWideHighlightText(x, y, 1, highlightColor, normalColor, string);
    // char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    // *video++ = *string++;
    // *video++ = highlightColor;
    // while (*string) {
    //     *video++ = *string++;
    //     *video++ = normalColor;
    // }
}

void drawLetterHighlightText(int x, int y, int highlightColor, int normalColor, const char letter, const char* string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    *video++ = letter;
    *video++ = highlightColor;
    *video++ = ')';
    *video++ = highlightColor;
    *video++ = ' ';
    *video++ = highlightColor;
    while (*string) {
        *video++ = *string++;
        *video++ = normalColor;
    }
}

void drawHorizontalLine(int y, int color, char character) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y;
    int i;
    for (i = 0; i < 80; ++i) {
        *video++ = character;
        *video++ = color;
    }
}

void drawVerticalLine(int x, int color, char character) {
    char far *video = (char far *)0xb8000000 + 2 * x;
    int i;
    for (i = 0; i < 25; ++i) {
        *video++ = character;
        *video++ = color;
        video += 2 * 79;
    }
}

void drawCenterTextLine(int y, int color, const char *string) {
    char buffer[81];

    size_t length = strlen(string);
    int i = 0;
    int padding = 0;
    padding = (80 - length) / 2;
    for (i = 0; i < padding; ++i) {
        buffer[i] = ' ';
    }
    memset(buffer, ' ', padding);
    strcpy(buffer + padding, string);
    drawTextLine(y, color, buffer);
    buffer[80] = '\0';
}

void drawCenterText(int y, int color, const char *string) {
    size_t length = strlen(string);
    int i = 0;
    int padding = 0;
    padding = (80 - length) / 2;
    drawColorText(padding, y, color, string);
}

void drawTransText(int x, int y, int color, const char *string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    while (*string) {
        *video++ = *string++;
        *video++ = (*video & ~0x0F) | color;
    }
}

void drawTransChar(int x, int y, int color, char character) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    *video++ = character;
    *video = (*video & ~0x0F) | color;
}

void drawRightAlignedTransText(int x, int y, int width, int color, const char *string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    int i = 0;
    int padding = width - strlen(string);
    for (i = 0; i < padding; ++i) {
        *video++ = ' ';
        video++;
    }
    while (*string) {
        *video++ = *string++;
        *video++ = (*video & ~0x0F) | color;
    }
}

void drawColorText(int x, int y, int color, const char* string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    while (*string) {
        *video++ = *string++;
        *video++ = color;
    }
}

void drawRawText(int x, int y, const char* string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    while (*string) {
        *video++ = *string++;
        *video++;
    }
}

void setRawColorData(int x, int y, const char* string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    while (*string) {
        *video++;
        *video++ = *string++;
    }
}

void drawTwoColorText(int x, int y, int color, const char* string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    while (*string) {
        if (*string == ' ') {
            *video++ = *string++;
            *video++ = TEXTCOLOR_GRAY|BGCOLOR_BLACK;
        } else {
            *video++ = *string++;
            *video++ = color;
        }
    }
}

void drawOverlayText(int x, int y, int color, const char *string) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    while (*string) {
        if (*string == ' ') {
            video += 2;
            string++;
        } else {
            *video++ = *string++;
            *video++ = (*video & ~0x0F) | color;
        }
    }
}

void drawRectangle(int x, int y, int width, int height, int color) {
    int ix, iy;
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    int skip = (80 - width) * 2;
    for (iy = 0; iy < height; ++iy) {
        for (ix = 0; ix < width; ++ix) {
            *video++ = ' ';
            *video++ = color;
        }
        video += skip;
    }
}

void drawWindow(int x, int y, int width, int height, int color, WINDOW_BORDER_STYLE style) {
    int ix, iy;
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    int skip = (80 - width) * 2;
    unsigned char topLeft, topRight, bottomLeft, bottomRight, horizontal, vertical;
    if (style == BORDER_DOUBLE) {
        topLeft = 'É';
        topRight = '»';
        bottomLeft = 'È';
        bottomRight = '¼';
        horizontal = 'Í';
        vertical = 'º';
    } else {
        topLeft = 'Ú';
        topRight = '¿';
        bottomLeft = 'À';
        bottomRight = 'Ù';
        horizontal = 'Ä';
        vertical = '³';
    }
    for (ix = 0; ix < width; ++ix) {
        *video++ = horizontal;
        *video++ = color;
    }
    video += skip;
    for (iy = 1; iy < height - 1; ++iy) {
        *video++ = vertical;
        *video++ = color;
        for (ix = 1; ix < width - 1; ++ix) {
            *video++ = ' ';
            *video++ = color;
        }
        *video++ = vertical;
        *video++ = color;
        video += skip;
    }
    for (ix = 0; ix < width; ++ix) {
        *video++ = horizontal;
        *video++ = color;
    }
    drawColorChar(x, y, color, topLeft);
    drawColorChar(x + width - 1, y, color, topRight);
    drawColorChar(x, y + height - 1, color, bottomLeft);
    drawColorChar(x + width - 1, y + height - 1, color, bottomRight);
}

void setBlockColor(int x, int y, int color) {
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    video++;
    *video++ = color;
}

void setAreaColor(int x, int y, int width, int height, int color) {
    int ix, iy;
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    for (iy = 0; iy < height; ++iy) {
        for (ix = 0; ix < width; ++ix) {
            video++;
            *video++ = color;
        }
        video += (80 - width) * 2;
    }
}

void setBackgroundColor(int color) {
    setAreaColor(0, 0, 80, 25, BGCOLOR_BLUE);
}

void setAreaTextColor(int x, int y, int width, int height, int color) {
    int ix, iy;
    char far *video = (char far *)0xb8000000 + 2 * 80 * y + 2 * x;
    for (iy = 0; iy < height; ++iy) {
        for (ix = 0; ix < width; ++ix) {
            video++;
            *video++ = (*video & ~0x0F) | color;
        }
        video += 80 * 2;
    }
}

void showCaret(bool show) {
    int flags = show ? 0x0607 : 0x2607;
    _asm {
        mov ah, BIOS_VIDEO_CARET_SHAPE
        mov cx, flags
        int INTERRUPT_BIOS_VIDEO
    }
}

void moveCaret(unsigned char x, unsigned char y) {
    _asm {
        mov bh, 0
        mov dh, y
        mov dl, x
        mov ah, BIOS_VIDEO_CARET_POSITION
        int INTERRUPT_BIOS_VIDEO
    }
}

void clearScreen() {
    _asm {
        mov ah, BIOS_VIDEO_MODE
        mov al, 0x03
        int INTERRUPT_BIOS_VIDEO
    }
}

void setFullColorMode(bool enable) {
    unsigned char input = enable? 0 : 1;
    _asm {
        mov ax, 0x1003
        mov bl, input
        mov bh, 0
        int INTERRUPT_BIOS_VIDEO
    }
}

void cleanup() {
    showCaret(true);
    clearScreen();
}

void beep() {
    _asm {
        mov dl, 0x07
        mov ah, DOS_WRITE_STDOUT
        int INTERRUPT_DOS
    }
}

unsigned int printerPortCount() {
    unsigned int count;
    _asm {
        int INTERRUPT_BIOS_EQUIPMENT
        mov count, ax
    }
    return count >> 14;
}

int printerInitialize(int printer) {
    unsigned char status;
    _asm {
        mov ah, BIOS_PRINTER_INITIALIZE
        mov dx, printer
        int INTERRUPT_BIOS_PRINTER
        mov status, ah
    }
    return status;
}

int printerGetStatus(int printer) {
    unsigned char status;
    _asm {
        mov ah, BIOS_PRINTER_STATUS
        mov dx, printer
        int INTERRUPT_BIOS_PRINTER
        mov status, ah
    }
    return status;
}

int printerWriteCharacter(int c, int printer) {
    unsigned char cast = (unsigned char)c;
    unsigned char status;
    _asm {
        mov ah, BIOS_PRINTER_WRITE
        mov al, cast
        mov dx, printer
        int INTERRUPT_BIOS_PRINTER
        mov status, ah
    }
    return status;
}
