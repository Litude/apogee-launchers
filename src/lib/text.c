#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#include "output.h"
#include "input.h"
#include "file.h"
#include "text.h"
#include "memory.h"

#define DISPLAYED_LINES 22
#define TEXT_WRAP_WIDTH 80
#define LINES_PER_PAGE 60 // Default, if text file has page breaks they will be used instead

#define INITIAL_LINE_ALLOC 80
#define ADDITIONAL_LINE_ALLOC 40

#define PAGE_INPUT_MAX_LENGTH 3
#define SEARCH_INPUT_MAX_LENGTH 30
#define FILENAME_INPUT_MAX_LENGTH 12

#define ALLOC_FUNC(size) farmalloc(size)
#define CALLOC_FUNC(nmemb, size) farcalloc(nmemb, size)
#define REALLOC_FUNC(ptr, size) farrealloc(ptr, size)
#define FREE_FUNC(ptr) farfree(ptr)

static enum INPUT_MODE {
    INPUT_MODE_DEFAULT,
    INPUT_MODE_PAGE_INPUT,
    INPUT_MODE_SEARCH_INPUT,
    INPUT_MODE_FILENAME_INPUT
};

static enum LINE_BREAK_TYPE {
    LINE_BREAK_NONE,
    LINE_BREAK_CRLF,
    LINE_BREAK_LF,
};

static unsigned int allocatedlines = 0;
static unsigned int displayedline = 0;
static unsigned int numlines = 0;
static int extraspace = 0;
static unsigned int numpages = 0;
static char huge* far* lines = NULL; 
static unsigned int far *pagebreaks = NULL;
static char huge *textbuffer = NULL;
static bool parsing = false;
static unsigned int progress = 0;
static int inputmode = INPUT_MODE_DEFAULT;
static char pageInput[PAGE_INPUT_MAX_LENGTH + 1];
static char searchInput[SEARCH_INPUT_MAX_LENGTH + 1];
static char filenameInput[FILENAME_INPUT_MAX_LENGTH + 1];
static int caretPosition = 0;

static int textStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
static int legendTextColor = TEXTCOLOR_BLACK;
static int legendBgColor = BGCOLOR_GRAY;
static int layout = TEXT_LAYOUT_TRADITIONAL;
static char const* titleText = NULL;

static int storedTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
static int storedLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
static int storedLayout = TEXT_LAYOUT_TRADITIONAL;

static char LEGEND_OLD[] = " ESC-Quit \xB3 \x18\x19 PgUp PgDn Home End \xB3 #-Page F-Find P-Print";
static char LEGEND_NEW[] = " Up Dn PgUp PgDn Home End   #-Page  F-Find  P-Print                    ESC-Exit";

static char LEGEND_SEARCH[] = " Text to Search For: ";
static char LEGEND_PAGE[] = " Enter Page Number: ";
static char LEGEND_FILENAME[] = " Enter Filename: ";

static char LEGEND_SEARCH_STATUS_SEARCHING[] = " Searching...";
static char LEGEND_SEARCH_STATUS_FOUND[] = " SPACE BAR to Continue Search.  Any other key to quit.";
static char LEGEND_SEARCH_STATUS_NOTHING[] = " Search found no match.  Press any key.";

static char PRINTER_STATUS_NO_PRINTER[] = " No printer detected.  Print to file (Y/N)?";
static char PRINTER_STATUS_PRINTING[] = " Printing page %d...";
static char PRINTER_STATUS_DONE[] = " Printing finished.  Press any key.";
static char PRINTER_STATUS_ERROR_EXISTS[] = " Error: File already exists.  Press any key.";
static char PRINTER_STATUS_ERROR_NAME_INVALID[] = " Error: Filename is invalid.  Press any key.";
static char PRINTER_STATUS_ERROR_FILE_UNKNOWN[] = " Error: Opening file failed.  Press any key.";
static char PRINTER_OUTPUT_PREFIX[] = " Output to";

static char PROGRESS_STATES[] = { '|', '/', '-', '\\' };

void storeTextStyle() {
    storedTextStyle = textStyle;
    storedLegendStyle = legendTextColor|legendBgColor;
    storedLayout = layout;
}

void restoreTextStyle() {
    textStyle = storedTextStyle;
    legendTextColor = storedLegendStyle & 0x0F;
    legendBgColor = storedLegendStyle & 0xF0;
    layout = storedLayout;
}

// Use the intense opposite of the bg color as the legend text color
static int getDisabledLegendTextColor() {
    return legendBgColor & 0x80 ? ((unsigned int)legendBgColor >> 4) & 0x0F : ((unsigned int)legendBgColor >> 4) | 0x08;
}

static int getHighlightColor() {
    return layout == TEXT_LAYOUT_MODERN ? legendTextColor|legendBgColor : TEXTCOLOR_BLACK|BGCOLOR_WHITE;
}

static void drawLegend() {
    if (layout == TEXT_LAYOUT_MODERN) {
        drawIndentTextLine(0, 1, legendTextColor|legendBgColor, titleText);
        drawTextLine(24, legendTextColor|legendBgColor, LEGEND_NEW);
    } else {
        drawCenterTextLine(0, legendTextColor|legendBgColor, titleText);
        drawTextLine(24, legendTextColor|legendBgColor, LEGEND_OLD);
    }
    if (parsing) {
        if (layout == TEXT_LAYOUT_MODERN) {
            setAreaTextColor(22, 24, 29, 1, getDisabledLegendTextColor());
        } else {
            setAreaTextColor(30, 24, 3, 1, getDisabledLegendTextColor());
            setAreaTextColor(36, 24, 21, 1, getDisabledLegendTextColor());
        }
    }
}

static void drawText() {
    int i;
    for (i = 0; i <= DISPLAYED_LINES; ++i) {
        farDrawTextLine(i + 1, textStyle, lines[displayedline + i]);
    }
}

static unsigned int getCurrentPage() {
    int i = 0;
    if (pagebreaks) {
        for (i = 1; i <= pagebreaks[0]; ++i) {
            if ((long)pagebreaks[i] > ((long)displayedline + DISPLAYED_LINES)) {
                return i;
            }
        }
        return i;
    } else {
        return (displayedline + DISPLAYED_LINES) / LINES_PER_PAGE + 1;
    }
}

static unsigned int getNumPages() {
    int i = 0, line = 0, page = 0;
    if (pagebreaks) {
        i = pagebreaks[0];
        line = pagebreaks[i];
        while (line >= numlines) {
            pagebreaks[0]--;
            i = pagebreaks[0];
            line = pagebreaks[i];
        }
        return pagebreaks[0] + 1;
    } else {
        return numlines / LINES_PER_PAGE + 1;
        //page = (numlines % LINES_PER_PAGE) < DISPLAYED_LINES ? numlines / LINES_PER_PAGE : (numlines / LINES_PER_PAGE + 1);
        // return page ? page : 1;
    }
}

static void drawProgress() {
    char progressText[20];
    int y = layout == TEXT_LAYOUT_MODERN ? 0 : 24;
    unsigned int currentPage = getCurrentPage();
    if (parsing) {
        drawTransText(68, y, legendTextColor, "Loading...");
        drawTransChar(78, y, legendTextColor, PROGRESS_STATES[progress >> 3]);
    } else {
        sprintf(progressText, "Page %u of %u", currentPage, numpages);
        drawRightAlignedTransText(63, y, 16, legendTextColor, progressText);
    }
}

static void decrementDisplayedLine(int count) {
    if (numlines < DISPLAYED_LINES) return;
    if (displayedline >= count) {
        displayedline -= count;
    } else {
        displayedline = 0;
    }
    drawText();
    drawProgress();
}

static void incrementDisplayedLine(int count) {
    if (numlines < DISPLAYED_LINES) return;
    if ((long)numlines - (long)(displayedline + count + DISPLAYED_LINES) > 0) {
        displayedline += count;
    } else {
        displayedline = numlines - DISPLAYED_LINES;
    }
    drawText();
    drawProgress();
}

static void jumpToPage(int page) {
    if (page > numpages) return;
    if (pagebreaks) {
        displayedline = page > 1 ? pagebreaks[page - 1] : 0;
    } else {
        displayedline = LINES_PER_PAGE * (page - 1);
    }
    if (displayedline + DISPLAYED_LINES >= numlines) {
        displayedline = numlines - DISPLAYED_LINES;
    }
    drawText();
    drawProgress();
}

static void setDisplayedLine(unsigned int newLine) {
    if ((long)numlines - (long)(newLine + DISPLAYED_LINES) > 0) {
        displayedline = newLine;
    } else {
        displayedline = numlines - DISPLAYED_LINES;
    }
    drawText();
    drawProgress();
}

static char getData(char huge* filebuffer, long i) {
    char result = filebuffer[i];
    // Map ISO NBSP, page break and EOF to whitespace
    switch (result) {
        case '\xA0': // ISO NBSP
        case '\x1A': // EOF
            return ' ';
        case '\x96': // ISO soft hyphen
            return '-';
        default:
            return result;
    }
}

static int isLineBreak(char huge* filebuffer, long filesize, long i) {
    if (i < filesize && getData(filebuffer, i) == '\n') {
        return LINE_BREAK_LF;
    } else if (i + 1 < filesize && getData(filebuffer, i) == '\r' && getData(filebuffer, i + 1) == '\n') {
        return LINE_BREAK_CRLF;
    } else {
        return LINE_BREAK_NONE;
    }
}

static void findNextLastWhiteSpace(long *i, long filesize, char huge* filebuffer) {
    int linebreak;
    long j = *i;
    ++j;
    while (j < filesize && getData(filebuffer, j) == ' ') {
        ++extraspace;
        ++j;
    }
    --j;
    --extraspace;
    linebreak = isLineBreak(filebuffer, filesize, j + 1);
    if (linebreak == LINE_BREAK_CRLF) {
        j += 2;
        extraspace += 2;
    } else if (linebreak == LINE_BREAK_LF) {
        ++extraspace;
        ++j;
    }
    *i = j;
}

static void findNextLastCharacter(long *i, long filesize, char huge* filebuffer, char character) {
    long j = *i;
    ++j;
    while (j < filesize && getData(filebuffer, j) == character) {
        ++extraspace;
        ++j;
    }
    if (getData(filebuffer, j) == '\r') {
        ++extraspace;
        ++j;
    }
    if (getData(filebuffer, j) == '\n') {
        ++extraspace;
        ++j;
    }
    --j;
    --extraspace;
    *i = j;
}

static bool reallocateIfNeeded() {
    char huge* far* linesNew;
    if (numlines >= allocatedlines - 1) {
        linesNew = REALLOC_FUNC(lines, (allocatedlines + ADDITIONAL_LINE_ALLOC) * sizeof(char huge*));
        allocatedlines += ADDITIONAL_LINE_ALLOC;
        if (!linesNew) return false;
        lines = linesNew;
    }
    return true;
}

void setDefaultViewMode() {
    inputmode = INPUT_MODE_DEFAULT;
    showCaret(false);
    drawLegend();
    drawProgress();
}

void updatePageInputText(int value) {
    size_t length = strlen(pageInput);
    int i;
    if (length < PAGE_INPUT_MAX_LENGTH && caretPosition < PAGE_INPUT_MAX_LENGTH) {
        for (i = PAGE_INPUT_MAX_LENGTH; i > caretPosition; --i) {
            pageInput[i] = pageInput[i - 1];
        }
        pageInput[caretPosition++] = (unsigned char)value + 0x30;
        drawTransText(sizeof(LEGEND_PAGE) - 1, 24, legendTextColor, pageInput);
        moveCaret(sizeof(LEGEND_PAGE) - 1 + caretPosition, 24);
    }
}

void updateSearchInputText(char value) {
    size_t length = strlen(searchInput);
    int i;
    if (length < SEARCH_INPUT_MAX_LENGTH && caretPosition < SEARCH_INPUT_MAX_LENGTH) {
        for (i = SEARCH_INPUT_MAX_LENGTH; i > caretPosition; --i) {
            searchInput[i] = searchInput[i - 1];
        }
        searchInput[caretPosition++] = value;
        drawTransText(sizeof(LEGEND_SEARCH) - 1, 24, legendTextColor, searchInput);
        moveCaret(sizeof(LEGEND_SEARCH) - 1 + caretPosition, 24);
    }
}

void updateFileNameInputText(char value) {
    size_t length = strlen(filenameInput);
    int i;
    if (length < FILENAME_INPUT_MAX_LENGTH && caretPosition < FILENAME_INPUT_MAX_LENGTH) {
        for (i = FILENAME_INPUT_MAX_LENGTH; i > caretPosition; --i) {
            filenameInput[i] = filenameInput[i - 1];
        }
        filenameInput[caretPosition++] = value;
        drawTransText(sizeof(LEGEND_FILENAME) - 1, 24, legendTextColor, filenameInput);
        moveCaret(sizeof(LEGEND_FILENAME) - 1 + caretPosition, 24);
    }
}

void removePageInputText() {
    size_t length = strlen(pageInput);
    int i;
    if (length && caretPosition) {
        --caretPosition;
        for (i = caretPosition; i < PAGE_INPUT_MAX_LENGTH; ++i) {
            pageInput[i] = pageInput[i + 1];
        }
        drawTransChar(sizeof(LEGEND_PAGE) - 1 + length - 1, 24, legendTextColor, ' ');
        drawTransText(sizeof(LEGEND_PAGE) - 1, 24, legendTextColor, pageInput);
        moveCaret(sizeof(LEGEND_PAGE) - 1 + caretPosition, 24);
    }
}

void removeSearchInputText() {
    size_t length = strlen(searchInput);
    int i;
    if (length && caretPosition) {
        --caretPosition;
        for (i = caretPosition; i < SEARCH_INPUT_MAX_LENGTH; ++i) {
            searchInput[i] = searchInput[i + 1];
        }
        drawTransChar(sizeof(LEGEND_SEARCH) - 1 + length - 1, 24, legendTextColor, ' ');
        drawTransText(sizeof(LEGEND_SEARCH) - 1, 24, legendTextColor, searchInput);
        moveCaret(sizeof(LEGEND_SEARCH) - 1 + caretPosition, 24);
    }
}

void removeFilenameInputText() {
    size_t length = strlen(filenameInput);
    int i;
    if (length && caretPosition) {
        --caretPosition;
        for (i = caretPosition; i < FILENAME_INPUT_MAX_LENGTH; ++i) {
            filenameInput[i] = filenameInput[i + 1];
        }
        drawTransChar(sizeof(LEGEND_FILENAME) - 1 + length - 1, 24, legendTextColor, ' ');
        drawTransText(sizeof(LEGEND_FILENAME) - 1, 24, legendTextColor, filenameInput);
        moveCaret(sizeof(LEGEND_FILENAME) - 1 + caretPosition, 24);
    }
}

void activateSearchMode() {
    inputmode = INPUT_MODE_SEARCH_INPUT;
    moveCaret(sizeof(LEGEND_SEARCH) - 1, 24);
    showCaret(true);
    drawTextLine(24, legendTextColor|legendBgColor, LEGEND_SEARCH);
    drawProgress();
    searchInput[0] = '\0';
    caretPosition = 0;
}

void handlePageInput(int initial) {
    if (inputmode != INPUT_MODE_PAGE_INPUT) {
        inputmode = INPUT_MODE_PAGE_INPUT;
        moveCaret(sizeof(LEGEND_PAGE) - 1, 24);
        showCaret(true);
        drawTextLine(24, legendTextColor|legendBgColor, LEGEND_PAGE);
        drawProgress();
        pageInput[0] = '\0';
        caretPosition = 0;
    }
    updatePageInputText(initial > 9 ? 0 : initial);
}

void performTextSearch() {
    unsigned int i;
    size_t length = strlen(searchInput);
    long ptrOffset = 0;
    char huge* prevSearch = NULL;
    showCaret(false);
    if (!length) {
        setDefaultViewMode();
    } else {
        drawTextLine(24, legendTextColor|legendBgColor, LEGEND_SEARCH_STATUS_SEARCHING);
        for (i = displayedline; i < numlines; ++i) {
            while (true) {
                prevSearch = _hstristr(lines[i] + ptrOffset, searchInput);
                if (prevSearch) {
                    ptrOffset = prevSearch - lines[i] + 1;
                    setDisplayedLine(i > 0 ? i - 1 : 0);
                    setAreaColor(prevSearch - lines[i], i - displayedline + 1, length, 1, getHighlightColor());
                    drawTextLine(24, legendTextColor|legendBgColor, LEGEND_SEARCH_STATUS_FOUND);
                    drawProgress();
                    if (getPressedKey() != KEY_SPACEBAR) {
                        drawText();
                        setDefaultViewMode();
                        return;
                    }
                } else {
                    ptrOffset = 0;
                    break;
                }
            }
        }
        if (!prevSearch) {
            drawTextLine(24, legendTextColor|legendBgColor, LEGEND_SEARCH_STATUS_NOTHING);
            drawText();
            getPressedKey();
            setDefaultViewMode();
            drawLegend();
            drawProgress();
        }
    }
}

void parsePageInput() {
    int page = atoi(pageInput);
    if (!pageInput[0]) {
        setDefaultViewMode();
    } else if (page > 0 && page <= numpages) {
        setDefaultViewMode();
        jumpToPage(page);
    } else {
        beep();
    }
}

void moveCaretLeft() {
    if (inputmode == INPUT_MODE_SEARCH_INPUT) {
        if (caretPosition > 0) {
            --caretPosition;
            moveCaret(sizeof(LEGEND_SEARCH) - 1 + caretPosition, 24);
        }
    } else if (inputmode == INPUT_MODE_PAGE_INPUT) {
        if (caretPosition > 0) {
            --caretPosition;
            moveCaret(sizeof(LEGEND_PAGE) - 1 + caretPosition, 24);
        }
    } else if (inputmode == INPUT_MODE_FILENAME_INPUT) {
        if (caretPosition > 0) {
            --caretPosition;
            moveCaret(sizeof(LEGEND_FILENAME) - 1 + caretPosition, 24);
        }
    }
}

void moveCaretRight() {
    if (inputmode == INPUT_MODE_SEARCH_INPUT) {
        if (caretPosition < strlen(searchInput)) {
            ++caretPosition;
            moveCaret(sizeof(LEGEND_SEARCH) - 1 + caretPosition, 24);
        }
    } else if (inputmode == INPUT_MODE_PAGE_INPUT) {
        if (caretPosition < strlen(pageInput)) {
            ++caretPosition;
            moveCaret(sizeof(LEGEND_PAGE) - 1 + caretPosition, 24);
        }
    } else if (inputmode == INPUT_MODE_FILENAME_INPUT) {
        if (caretPosition < strlen(filenameInput)) {
            ++caretPosition;
            moveCaret(sizeof(LEGEND_FILENAME) - 1 + caretPosition, 24);
        }
    }
}

void writeToTextFile(_FFILE* file, char* textBuffer) {
    unsigned long i, j;
    char huge* character;
    int currentPage = 1;
    sprintf(textBuffer, PRINTER_STATUS_PRINTING, currentPage);
    drawTextLine(24, legendTextColor|legendBgColor, textBuffer);
    for (i = 0; i < numlines; ++i) {
        if (pagebreaks) {
            if (pagebreaks[currentPage] == i) {
                farfputc('\f', file);
                ++currentPage;
                sprintf(textBuffer, PRINTER_STATUS_PRINTING, currentPage);
                drawTextLine(24, legendTextColor|legendBgColor, textBuffer);
            }
        } else {
            if (i && i % LINES_PER_PAGE == 0) {
                farfputc('\f', file);
                ++currentPage;
                sprintf(textBuffer, PRINTER_STATUS_PRINTING, currentPage);
                drawTextLine(24, legendTextColor|legendBgColor, textBuffer);
            }
        }
        for (character = lines[i]; *character; ++character) {
            farfputc(*character, file);
        }
        farfputc('\r', file);
        farfputc('\n', file);
    }
    farfputc('\f', file);
    farfclose(file);
    drawTextLine(24, legendTextColor|legendBgColor, PRINTER_STATUS_DONE);
    getPressedKey();
}

bool validateFilenameEntry(const char* filename, char* textBuffer) {
    int error = 0;
    if (!fileNameValid(filenameInput)) {
        error = 1;
    } else if (fileExists(filenameInput)) {
        error = 2;
    }
    if (error) {
        showCaret(false);
        drawTextLine(24, legendTextColor|legendBgColor, error == 1 ? PRINTER_STATUS_ERROR_NAME_INVALID : PRINTER_STATUS_ERROR_EXISTS);
        getPressedKey();
        showCaret(true);
        drawTextLine(24, legendTextColor|legendBgColor, LEGEND_FILENAME);
        drawTransText(sizeof(LEGEND_FILENAME) - 1, 24, legendTextColor, filenameInput);
        return false;
    } else {
        return true;
    }

}

void outputToTextFile(char* textBuffer) {
    struct keystroke keypress;
    _FFILE* outputFile;
    inputmode = INPUT_MODE_FILENAME_INPUT;
    moveCaret(sizeof(LEGEND_FILENAME) - 1, 24);
    showCaret(true);
    drawTextLine(24, legendTextColor|legendBgColor, LEGEND_FILENAME);
    filenameInput[0] = '\0';
    caretPosition = 0;
    while (true) {
        keypress = getPressedKeyDetailed();
        if (isprint(keypress.character)) {
            updateFileNameInputText(keypress.character);
        } else {
            switch (keypress.scancode) {
                case KEY_ESCAPE:
                    setDefaultViewMode();
                    return;
                case KEY_ARROW_LEFT:
                    moveCaretLeft();
                    break;
                case KEY_ARROW_RIGHT:
                    moveCaretRight();
                    break;
                case KEY_BACKSPACE:
                    removeFilenameInputText();
                    break;
                case KEY_ENTER:
                    if (!filenameInput[0]) {
                        setDefaultViewMode();
                        return;
                    } else {
                        if (validateFilenameEntry(filenameInput, textBuffer)) {
                            showCaret(false);
                            outputFile = farfopen(filenameInput, "w");
                            if (outputFile) {
                                writeToTextFile(outputFile, textBuffer);
                                return;
                            } else {
                                showCaret(false);
                                drawTextLine(24, legendTextColor|legendBgColor, PRINTER_STATUS_ERROR_FILE_UNKNOWN);
                                getPressedKey();
                                showCaret(true);
                                drawTextLine(24, legendTextColor|legendBgColor, LEGEND_FILENAME);
                                drawTransText(sizeof(LEGEND_FILENAME) - 1, 24, legendTextColor, filenameInput);
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

}

void printFile(int printerPort, char* textBuffer) {
    unsigned long i, j;
    char huge* character;
    int currentPage = 1;
    sprintf(textBuffer, PRINTER_STATUS_PRINTING, currentPage);
    drawTextLine(24, legendTextColor|legendBgColor, textBuffer);
    for (i = 0; i < numlines; ++i) {
        if (pagebreaks) {
            if (pagebreaks[currentPage] == i) {
                printerWriteCharacter('\f', printerPort);
                ++currentPage;
                sprintf(textBuffer, PRINTER_STATUS_PRINTING, currentPage);
                drawTextLine(24, legendTextColor|legendBgColor, textBuffer);
            }
        } else {
            if (i && i % LINES_PER_PAGE == 0) {
                printerWriteCharacter('\f', printerPort);
                ++currentPage;
                sprintf(textBuffer, PRINTER_STATUS_PRINTING, currentPage);
                drawTextLine(24, legendTextColor|legendBgColor, textBuffer);
            }
        }
        for (character = lines[i]; *character; ++character) {
            printerWriteCharacter(*character, printerPort);
        }
        printerWriteCharacter('\r', printerPort);
        printerWriteCharacter('\n', printerPort);
    }
    printerWriteCharacter('\f', printerPort);
    drawTextLine(24, legendTextColor|legendBgColor, PRINTER_STATUS_DONE);
    getPressedKey();
}

void activatePrintMode() {
    bool portStatus[4];
    bool anyPrinter = false;
    char statusBuffer[60];
    char lptBuffer[10];
    int i;
    int keypress;
    // int initStatus = printerInitialize(0);
    int portCount = printerPortCount();
    for (i = 0; i < portCount; ++i) {
        portStatus[i] = (printerGetStatus(i) & 0x10) != 0;
        anyPrinter = anyPrinter || portStatus[i];
    }
    // printf("ports: %d, p1: 0x%02x p2: 0x%02x p3: 0x%02x p4: 0x%02x\n", portCount, portStatus[0], portStatus[1], portStatus[2], portStatus[3]);
    if (anyPrinter) {
        strcpy(statusBuffer, PRINTER_OUTPUT_PREFIX);
        for (i = 0; i < portCount; ++i) {
            sprintf(lptBuffer, " %d-LPT%d", i+1, i+1);
            strcat(statusBuffer, lptBuffer);
            if (i < portCount - 1) {
                strcat(statusBuffer, ",");
            }
        }
        strcat(statusBuffer, " or F-File?");
        drawTextLine(24, legendTextColor|legendBgColor, statusBuffer);
        while (true) {
            keypress = getPressedKey();
            if (keypress == KEY_1 && portStatus[0]) {
                printFile(0, &statusBuffer);
                break;
            } else if (keypress == KEY_2 && portStatus[1]) {
                printFile(1, &statusBuffer);
                break;
            } else if (keypress == KEY_3 && portStatus[2]) {
                printFile(2, &statusBuffer);
                break;
            } else if (keypress == KEY_4 && portStatus[3]) {
                printFile(3, &statusBuffer);
                break;
            } else if (keypress == KEY_F) {
                outputToTextFile(&statusBuffer);
                break;
            }
        }

    } else {
        drawTextLine(24, legendTextColor|legendBgColor, PRINTER_STATUS_NO_PRINTER);
        while (true) {
            keypress = getPressedKey();
            if (keypress == KEY_Y) {
                outputToTextFile(&statusBuffer);
                break;
            } else if (keypress == KEY_N) {
                break;
            }
        }
    }
    drawLegend();

    // printf("ports: %d, p1: 0x%02x p2: 0x%02x p3: 0x%02x p4: 0x%02x\n", portCount, status1, status2, status3, status4);
}

static bool handleInput(bool parsing) {
    int scancode;
    struct keystroke keypress;
    if (inputmode == INPUT_MODE_SEARCH_INPUT) {
        keypress = getPressedKeyDetailed();
        // printf("Got character c: %x scan: %x\n", keypress.character, keypress.scancode);
        if (isprint(keypress.character)) {
            updateSearchInputText(keypress.character);
            // printf("Is print\n");
            return true;
        } else {
            scancode = keypress.scancode;
        }
    } else {
        scancode = getPressedKey();
    }
    switch (scancode) {
        case KEY_ARROW_UP:
            decrementDisplayedLine(1);
            break;
        case KEY_ARROW_DOWN:
            incrementDisplayedLine(1);
            break;
        case KEY_ARROW_LEFT:
            moveCaretLeft();
            break;
        case KEY_ARROW_RIGHT:
            moveCaretRight();
            break;
        case KEY_HOME:
            decrementDisplayedLine(numlines);
            break;
        case KEY_END:
            !parsing ? incrementDisplayedLine(numlines) : beep();
            break;
        case KEY_PAGE_UP:
            decrementDisplayedLine(DISPLAYED_LINES);
            break;
        case KEY_PAGE_DOWN:
            incrementDisplayedLine(DISPLAYED_LINES);
            break;
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_0:
            if (!parsing) {
                if (numpages > 10) {
                    handlePageInput(scancode - KEY_1 + 1);
                } else {
                    jumpToPage(scancode - KEY_1 + 1);
                }
            } else {
                beep();
            }
            break;
        case KEY_F:
            if (!parsing) {
                activateSearchMode();
            } else {
                beep();
            }
            break;
        case KEY_P:
            if (!parsing) {
                activatePrintMode();
            } else {
                beep();
            }
            break;
        case KEY_ENTER:
            if (inputmode == INPUT_MODE_PAGE_INPUT) {
                parsePageInput();
            } else if (inputmode == INPUT_MODE_SEARCH_INPUT) {
                performTextSearch();
            }
            break;
        case KEY_ESCAPE:
            if (inputmode != INPUT_MODE_DEFAULT) {
                setDefaultViewMode();
            } else {
                return false;
            }
            break;
        case KEY_BACKSPACE:
            if (inputmode == INPUT_MODE_PAGE_INPUT) {
                removePageInputText();
            } else if (inputmode == INPUT_MODE_SEARCH_INPUT) {
                removeSearchInputText();
            }
            break;
    }
    return true;
}

static bool handleParseInterfaceUpdate(bool *rendered) {
    if (numlines > 24) {
        if (!*rendered) {
            drawText();
            *rendered = true;
        } else if (!(numlines & 7)) {
            progress = (progress + 1) & 31;
            drawProgress();
            if (hasWaitingInput()) {
                return handleInput(true);
            }
        }
    }
    return true;
}

static bool runParseLoop(char huge* filebuffer, long filesize, char huge* textbuffer) {
    long i = 0, j = 0;
    long bufferindex = 0;
    int linelength = 0;
    char huge* spaceptr;
    bool rendered = false;
    char entry;
    int linebreak;
    unsigned int far* newPages;
    unsigned char numPageBreaks;
    lines[0] = textbuffer;
    for (i = 0; i < filesize; ++i) {
        entry = getData(filebuffer, i);
        // Treat only 0A as line break, ignore 0D
        // Compatibility with UNIX line endings as a bonus
        if (entry == '\r') {
            ++extraspace;
            continue;
        } else if (entry == '\n') {
            textbuffer[bufferindex++] = '\0';
            if (!reallocateIfNeeded()) return false;
            linelength = 0;
            spaceptr = NULL;
            lines[++numlines] = (char huge*)&textbuffer[bufferindex];
            if (!handleParseInterfaceUpdate(&rendered)) return false;
        } else if (entry == '\f') {
            if (!pagebreaks) {
                pagebreaks = ALLOC_FUNC(16 * sizeof(unsigned int));
                if (pagebreaks) {
                    pagebreaks[0] = 0;
                }
            }
            if (pagebreaks) {
                numPageBreaks = pagebreaks[0];
                if (numPageBreaks % 16 == 15) {
                    newPages = REALLOC_FUNC(pagebreaks, (numPageBreaks + 17) * sizeof(unsigned int));
                    if (newPages) {
                        pagebreaks = newPages;
                    } else {
                        FREE_FUNC(pagebreaks);
                        pagebreaks = NULL;
                        return ' ';
                    }
                }
                pagebreaks[numPageBreaks + 1] = numlines + (linelength == 0 ? 0 : 1);
                pagebreaks[0]++;
            }
            ++extraspace;
            
        } else {
            if (entry == ' ') {
                spaceptr = &textbuffer[bufferindex];
            }
            textbuffer[bufferindex++] = entry;
            ++linelength;
            if (linelength == TEXT_WRAP_WIDTH) {
                if (!reallocateIfNeeded()) return false;

                // If the next character is a line break, skip it and continue as normal
                if (linebreak = isLineBreak(filebuffer, filesize, i + 1)) {
                    spaceptr = NULL;
                    textbuffer[bufferindex++] = '\0';
                    lines[++numlines] = &textbuffer[bufferindex];
                    linelength = 0;
                    if (linebreak == LINE_BREAK_CRLF) {
                        ++extraspace;
                        i += 2;
                    } else {
                        ++i;
                    }
                    if (!handleParseInterfaceUpdate(&rendered)) return false;

                } else if (i + 1 < filesize && isspace(getData(filebuffer, i + 1))) {
                    textbuffer[bufferindex++] = '\0';
                    lines[++numlines] = &textbuffer[bufferindex];
                    linelength = 0;
                    ++i;
                    findNextLastWhiteSpace(&i, filesize, filebuffer);
                    if (!handleParseInterfaceUpdate(&rendered)) return false;

                } else if (spaceptr) {
                    // If current character is whitespace, wrap at next non-whitespace
                    // Else wrap at previous non-white space
                    *spaceptr = '\0';
                    lines[++numlines] = spaceptr + 1;
                    linelength = &textbuffer[bufferindex] - spaceptr;
                    spaceptr = NULL;

                    // Skip until next character
                    if (isspace(entry)) {
                        findNextLastWhiteSpace(&i, filesize, filebuffer);
                    }
                    if (!handleParseInterfaceUpdate(&rendered)) return false;
                } else {
                    // If there's a long line of all the same character, truncate it to a single line
                    // Most likely a single line of - or = characters
                    textbuffer[bufferindex++] = '\0';
                    for (j = 0; j < TEXT_WRAP_WIDTH && lines[numlines][j] == entry; ++j);
                    if (j == TEXT_WRAP_WIDTH) {
                        findNextLastCharacter(&i, filesize, filebuffer, entry);
                    }
                    lines[++numlines] = &textbuffer[bufferindex];
                    linelength = 0;
                    --extraspace;
                    if (!extraspace) {
                        //TODO: We could reallocate...
                        printf("RAN OUT OF EXTRA SPACE!\n");
                        getPressedKey();
                        return false;
                    }
                    if (!handleParseInterfaceUpdate(&rendered)) return false;
                }
            }
        }
    }
    textbuffer[bufferindex] = '\0';
    numpages = getNumPages();
    return true;
}

void setStyle(int newTextStyle, int newLegendStyle, int newLayout) {
    textStyle = newTextStyle;
    legendTextColor = newLegendStyle & 0x0F;
    legendBgColor = newLegendStyle & 0xF0;
    layout = newLayout;
}

static void clearStaticValues(const char* title) {
    titleText = title;
    allocatedlines = INITIAL_LINE_ALLOC;
    extraspace = 128;
    lines = NULL;
    pagebreaks = NULL;
    textbuffer = NULL;
    numlines = 0;
    displayedline = 0;
    numpages = 0;
    parsing = true;
    progress = 0;
    inputmode = INPUT_MODE_DEFAULT;
    pageInput[0] = '\0';
    searchInput[0] = '\0';
}


static void runMainLoop() {
    bool running = true;
    int character = 0;

    drawLegend();
    drawText();
    drawProgress();
    while (running) {
        if (!handleInput(false)) {
            running = false;
        }
    }

    if (textbuffer) {
        FREE_FUNC(textbuffer);
        textbuffer = NULL;
    }
    if (lines) {
        FREE_FUNC(lines);
        lines = NULL;
    }
    if (pagebreaks) {
        FREE_FUNC(pagebreaks);
        pagebreaks = NULL;
    }
}

static void startExecution(char huge* inputBuffer, long bufferSize, const char* title, bool freeBuffer) {
    clearStaticValues(title);

    textbuffer = ALLOC_FUNC(bufferSize + extraspace);
    if (!textbuffer) goto cleanup;

    // Need to ensure the first 22 are zero so short files are displayed correctly
    lines = CALLOC_FUNC(allocatedlines, sizeof(char huge*));
    if (!lines) goto cleanup;

    setFullColorMode(true);
    showCaret(false);
    drawLegend();
    drawText();
    drawProgress();
    lines[0] = textbuffer;
    if (!runParseLoop(inputBuffer, bufferSize, textbuffer)) goto cleanup;
    parsing = false;

    if (freeBuffer) {
        FREE_FUNC(inputBuffer);
        inputBuffer = NULL;
    }

    runMainLoop();

    cleanup:
    if (lines) {
        FREE_FUNC(lines);
        lines = NULL;
    }
    if (textbuffer) {
        FREE_FUNC(textbuffer);
        textbuffer = NULL;
    }
    if (pagebreaks) {
        FREE_FUNC(pagebreaks);
        pagebreaks = NULL;
    }
    if (freeBuffer && inputBuffer) {
        FREE_FUNC(inputBuffer);
        inputBuffer = NULL;
    }

    cleanup();
}

void showTextBuffer(char* buffer, int bufferSize, const char* title) {
    startExecution(buffer, bufferSize, title, true);
}

void showTextFiles(const char* title, const char* separator, ...) {
    const char* next = NULL;
    char huge* buffer = NULL, huge* newBuffer;
    long bsize = 0;
    long fsize = 0, cursize = 0;
    _FFILE* fptr;
    size_t separatorlen = strlen(separator);
    va_list args;
    va_start(args, separator);
    next = va_arg(args, const char*);
    while (true) {
        fsize = fileSize(next);
        newBuffer = REALLOC_FUNC(buffer, cursize + fsize + separatorlen);
        if (newBuffer) {
            buffer = newBuffer;
        } else {
            FREE_FUNC(buffer);
            return;
        }
        fptr = farfopen(next, "rb");
        if (fptr) {
            farfread(buffer + cursize, 1, fsize, fptr);
            cursize += fsize;
            farfclose(fptr);
        } else {
            FREE_FUNC(buffer);
            return;
        }
        next = va_arg(args, const char*);
        if (next == NULL) break;
        if (separatorlen) {
            _hmemcpy(buffer + cursize, separator, separatorlen);
            cursize += separatorlen;
        }
    }
    va_end(args);
    startExecution(buffer, cursize, title, true);
}

void showTextFile(const char* path, const char* title) {
    _FFILE* handle = NULL;
    char huge *filebuffer = NULL;
    long filesize = 0;
    unsigned long readcount = 0;
    handle = farfopen(path, "rb");
    if (!handle) {
        return;
    }

    farfseek(handle, 0, SEEK_END);
    filesize = farftell(handle);
    farfseek(handle, 0, SEEK_SET);

    filebuffer = ALLOC_FUNC(filesize);
    if (!filebuffer) {
        farfclose(handle);
        return;
    };

    readcount = farfread(filebuffer, 1, filesize, handle);
    if (readcount != filesize) {
        FREE_FUNC(filebuffer);
        farfclose(handle);
        return;
    }

    farfclose(handle);
    handle = NULL;

    startExecution(filebuffer, filesize, title, true);
}
