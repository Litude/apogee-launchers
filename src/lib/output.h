#include "intrpt.h"

#define TEXTCOLOR_BLACK 0
#define TEXTCOLOR_BLUE 1
#define TEXTCOLOR_GREEN 2
#define TEXTCOLOR_CYAN 3
#define TEXTCOLOR_RED 4
#define TEXTCOLOR_PURPLE 5
#define TEXTCOLOR_BROWN 6
#define TEXTCOLOR_GRAY 7
#define TEXTCOLOR_DARKGRAY 8
#define TEXTCOLOR_LIGHTBLUE 9
#define TEXTCOLOR_LIGHTGREEN 10
#define TEXTCOLOR_LIGHTCYAN 11
#define TEXTCOLOR_LIGHTRED 12
#define TEXTCOLOR_LIGHTPURPLE 13
#define TEXTCOLOR_YELLOW 14
#define TEXTCOLOR_WHITE 15

#define BGCOLOR_BLACK 0 << 4
#define BGCOLOR_BLUE 1 << 4
#define BGCOLOR_GREEN 2 << 4
#define BGCOLOR_CYAN 3 << 4
#define BGCOLOR_RED 4 << 4
#define BGCOLOR_PURPLE 5 << 4
#define BGCOLOR_BROWN 6 << 4
#define BGCOLOR_GRAY 7 << 4

// Require full color mode
#define BGCOLOR_DARKGRAY 8 << 4
#define BGCOLOR_LIGHTBLUE 9 << 4
#define BGCOLOR_LIGHTGREEN 10 << 4
#define BGCOLOR_LIGHTCYAN 11 << 4
#define BGCOLOR_LIGHTRED 12 << 4
#define BGCOLOR_LIGHTPURPLE 13 << 4
#define BGCOLOR_YELLOW 14 << 4
#define BGCOLOR_WHITE 15 << 4

// Doesn't work in full color mode
#define TEXT_FLASHING 1 << 7

typedef enum {
    BORDER_SINGLE,
    BORDER_DOUBLE
} WINDOW_BORDER_STYLE;

void drawColorChar(int x, int y, int color, char character);
void drawCenterText(int y, int color, const char *string);
void drawCenterTextLine(int y, int color, const char *string);
void farDrawTextLine(int y, int color, const char huge *string);
void drawTextLine(int y, int color, const char *string);
void drawIndentTextLine(int y, int x, int color, const char *string);
void drawColorText(int x, int y, int color, const char* string);
void drawTwoColorText(int x, int y, int color, const char* string);
void drawTransText(int x, int y, int color, const char *string);
void drawTransChar(int x, int y, int color, char character);
void drawRightAlignedTransText(int x, int y, int width, int color, const char *string);
void drawOverlayText(int x, int y, int color, const char *string);
void drawHorizontalLine(int y, int color, char character);
void drawVerticalLine(int x, int color, char character);
void drawRectangle(int x, int y, int width, int height, int color);
void drawWindow(int x, int y, int width, int height, int color, WINDOW_BORDER_STYLE style);
void drawRawText(int x, int y, const char* string);
void setRawColorData(int x, int y, const char* string);
void drawWideHighlightText(int x, int y, int width, int highlightColor, int normalColor, const char* string);
void drawHighlightText(int x, int y, int highlightColor, int normalColor, const char* string);
void drawLetterHighlightText(int x, int y, int highlightColor, int normalColor, const char letter, const char* string);
void setBackgroundColor(int color);
void setBlockColor(int x, int y, int color);
void setAreaColor(int x, int y, int width, int height, int color);
void setAreaTextColor(int x, int y, int width, int height, int color);
void showCaret(bool show);
void moveCaret(unsigned char x, unsigned char y);
void clearScreen();
void cleanup();
void setFullColorMode(bool enable);
void beep();
unsigned int printerPortCount();
int printerInitialize(int printer);
int printerGetStatus(int printer);
int printerWriteCharacter(int c, int printer);

void scrollWindowDown(unsigned char numlines);
#pragma aux scrollWindowDown = \
    ASM(mov ah, BIOS_VIDEO_SCROLL_DOWN) \
    ASM(xor bh, bh) \
    ASM(xor cx, cx) \
    ASM(mov dh, 24) \
    ASM(mov dl, 79) \
    ASM(int INTERRUPT_BIOS_VIDEO) \
    parm [al] \
    modify [ax bx cx dx];

void setRawData(int x, int y, unsigned char* data, int length);
#pragma aux setRawData = \
    ASM(mov di, dx) \
    ASM(shl di, 2) \
    ASM(add di, dx) \
    ASM(shl di, 5) \
    ASM(shl ax, 1) \
    ASM(add di, ax) \
    ASM(mov si, bx) \
    ASM(mov ax, 0xB800) \
    ASM(mov es, ax) \
    ASM(rep movsb) \
    parm [ax] [dx] [bx] [cx] \
    modify [es di si];
