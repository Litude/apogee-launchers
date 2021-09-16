#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <process.h>
#include <errno.h>
#include <string.h>
#include "lib/file.h"
#include "lib/text.h"
#include "lib/input.h"
#include "lib/output.h"
#include "lib/menu.h"
#include "lib/macro.h"
#include "lib/memory.h"
#include "lib/error.h"
#include "instruct/apogee.h"
#include "instruct/actions.h"
#include "version.h"

extern char** environ;
static char** args;

static const char* EMPTY_ENTRY = "                      ";

static const char* APOGEE_SHEET_PREFIX = "RAP";
static const char* APOGEE_GAME_TITLE = "Raptor";

static const char* TXT_VERSION_11 = "v1.1";
static const char* TXT_VERSION_12 = "v1.2";

static enum MAIN_ENTRY {
    MAIN_ENTRY_LAUNCH_GAME,
    MAIN_ENTRY_SETUP,
    MAIN_ENTRY_INSTRUCTIONS,
    MAIN_ENTRY_QUIT,
    NUM_MAIN_ENTRIES,
};

static const char* MENU_ENTRIES[] = {
    "Play",
    "Game Setup",
    "Instructions",
    "Quit"
};

static enum CUSTOM_SUPPORT_ACTIONS {
    CUSTOM_SUPPORT_ACTION_BETA_NOTE = CUSTOM_SUPPORT_ACTION_START,
    CUSTOM_SUPPORT_ACTION_BACK,
    NUM_TOTAL_SUPPORT_ACTIONS
};

#define RAPTOR_DEC93_SIZE 418704
#define RAPTOR_JAN94_SIZE 427991
#define RAPTOR_V10S_SIZE 411441
#define RAPTOR_V10R_SIZE 411445
#define RAPTOR_V11S_SIZE 437053
#define RAPTOR_V11R_SIZE 437057
#define RAPTOR_V12S_SIZE 474343
#define RAPTOR_V12R_SIZE 474359

static enum GAME_VERSION {
    VERSION_UNKNOWN,
    VERSION_BETA,
    VERSION_10,
    VERSION_11,
    VERSION_12
};

static int mainSelection = 0;
static int supportSelection = 0;
static bool supportMenu = false;
static int gameVersion = VERSION_UNKNOWN;

static const char FILE_GAME_EXE[] = "RAP.EXE";
static const char FILE_BETA_README[] = "README.1ST";

static const char* versionString = NULL;

static int menuEntries[NUM_MAIN_ENTRIES];
static int validMenuEntries = 0;
static int validSupportEntries = 0;
static menuEntry supportEntries[NUM_TOTAL_SUPPORT_ACTIONS];

static void populateMenuAvailability() {
    long exeSize = fileSize(FILE_GAME_EXE);
    switch (exeSize) {
        case RAPTOR_DEC93_SIZE:
        case RAPTOR_JAN94_SIZE:
            gameVersion = VERSION_BETA;
            break;
        case RAPTOR_V10S_SIZE:
        case RAPTOR_V10R_SIZE:
            gameVersion = VERSION_10;
            break;
        case RAPTOR_V11S_SIZE:
        case RAPTOR_V11R_SIZE:
            gameVersion = VERSION_11;
            versionString = TXT_VERSION_11;
            break;
        case RAPTOR_V12S_SIZE:
        case RAPTOR_V12R_SIZE:
            gameVersion = VERSION_12;
            versionString = TXT_VERSION_12;
            break;
        default:
            gameVersion = VERSION_UNKNOWN;
            break;
    }

    if (gameVersion == VERSION_BETA && fileExists(FILE_BETA_README)) {
        supportEntries[validSupportEntries].name = "Beta Release Notes";
        supportEntries[validSupportEntries].hotkey = 0;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BETA_NOTE;
        validSupportEntries++;
    }

    validSupportEntries += populateApogeeSupportEntries(&supportEntries[validSupportEntries], APOGEE_SHEET_PREFIX, 1 << APOGEE_SUPPORT_ACTION_INSTALL_HELP | 1 << APOGEE_SUPPORT_ACTION_HINT);

    for (int i = 0; i < validSupportEntries; ++i) {
        if (supportEntries[i].actionId == APOGEE_SUPPORT_ACTION_LICENSE) {
            supportEntries[i].name = "Software License";
        }
    }

    supportEntries[validSupportEntries].name = "Back";
    supportEntries[validSupportEntries].hotkey = 0;
    supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BACK;
    validSupportEntries++;

    menuEntries[validMenuEntries++] = MAIN_ENTRY_LAUNCH_GAME;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_SETUP;
    if (validSupportEntries > 1) {
        menuEntries[validMenuEntries++] = MAIN_ENTRY_INSTRUCTIONS;
    }
    menuEntries[validMenuEntries++] = MAIN_ENTRY_QUIT;
}

void drawLogo(short x_start, short y_start, bool subtitle, bool trademark) {
       drawColorText(x_start, y_start +  0,             TEXTCOLOR_BROWN, "   €€€€€            €            €€€€€€€€€€€€€€         €€€€€     ");
    drawTwoColorText(x_start, y_start +  1, TEXTCOLOR_BROWN|BGCOLOR_RED, "  ±±±±±±±±±        ±±±            ±±±±±±±±±±±±±±±     ±±±±±±±±±±  ");
    drawTwoColorText(x_start, y_start +  2, TEXTCOLOR_BROWN|BGCOLOR_RED, "  ∞∞     ∞∞∞      ∞∞∞ ∞      ∞∞∞∞∞     ∞∞∞           ∞∞∞∞     ∞∞∞ ");
    drawTwoColorText(x_start, y_start +  3, TEXTCOLOR_BROWN|BGCOLOR_RED, "  ∞∞      ∞∞∞    ∞∞∞  ∞∞    ∞∞∞  ∞∞∞   ∞∞∞   ∞∞∞∞∞∞   ∞∞∞       ∞∞");
       drawColorText(x_start, y_start +  4,               TEXTCOLOR_RED, "  ±±       ±±    ±±±  ±±±   ±±±   ±±±  ±±∞  ±±    ±±  ±±±      ±±±");
       drawColorText(x_start, y_start +  5,               TEXTCOLOR_RED, "  ±±     ±±±    ±±±    ±±   ±±±   ±±±  ±±±  ±±     ±± ±±±    ±±±± ");
       drawColorText(x_start, y_start +  6,               TEXTCOLOR_RED, "  ±±±±±±±±     ±±±   ±±±±   ±±±  ±±±   ±±±  ±±     ±± ±±±±±±±±±   ");
       drawColorText(x_start, y_start +  7,               TEXTCOLOR_RED, "  ±±  ±±±    ±±±±±±±±  ±±±  ±±±±±±±    ±±±   ±±±   ±± ±±±  ±±±    ");
       drawColorText(x_start, y_start +  8,               TEXTCOLOR_RED, " ≤≤≤   ≤≤≤    ≤≤≤      ≤≤≤  ≤≤≤        ≤≤±       ≤≤≤  ≤≤≤   ≤≤≤   ");
       drawColorText(x_start, y_start +  9,               TEXTCOLOR_RED, " ≤≤≤    ≤≤   ≤≤≤        ≤≤  ≤≤≤        ≤≤≤            ≤≤     ≤≤≤  ");
       drawColorText(x_start, y_start + 10,               TEXTCOLOR_RED, " ≤≤≤    ≤≤≤  ≤≤         ≤≤≤ ≤≤≤        ≤≤≤            ≤≤     ≤≤≤  ");
       drawColorText(x_start, y_start + 11,               TEXTCOLOR_RED, " ∞∞∞     ∞∞∞              ≤ ∞∞∞          ≤            ∞∞      ∞∞∞ ");
       drawColorText(x_start, y_start + 12,               TEXTCOLOR_RED, "∞∞∞      ∞∞∞                ∞∞                        ∞∞∞      ∞∞∞");
       drawColorText(x_start, y_start + 13,               TEXTCOLOR_RED, "          ∞∞∞                ∞                                  ∞∞");
       drawColorText(x_start, y_start + 14,               TEXTCOLOR_RED, "           ∞∞                ∞                                    ");

    // Only one character changes color mid-line, draw it separately
    drawColorChar(x_start + 41, y_start + 4, TEXTCOLOR_BROWN|BGCOLOR_RED, '∞');

    if (subtitle) {
        drawOverlayText(x_start + 15, y_start + 13, TEXTCOLOR_LIGHTBLUE, "C A L L   O F    T H E   S H A D O W S");
    }
    if (gameVersion == VERSION_BETA) {
        drawOverlayText(x_start + 15, y_start + 14, TEXTCOLOR_YELLOW|TEXT_FLASHING, "BETA  VERSION    DO  NOT  DISTRIBUTE!!");
    }
    if (trademark) {
        drawColorText(x_start + 67, y_start + 13, TEXTCOLOR_DARKGRAY, "(tm)");
    }
}

static void drawMainMenu(short x_start, short y_start) {
    int offset = validMenuEntries == 3 ? 1 : 0;
    for (int i = 0; i < validMenuEntries; ++i) {
        drawCenterText(y_start + i * 2 + offset, i == mainSelection ? TEXTCOLOR_LIGHTRED : TEXTCOLOR_RED, MENU_ENTRIES[menuEntries[i]]);
    }
}

static void drawSupportMenu(short x_start, short y_start) {
    int offset = MAX(4 - validSupportEntries, 0);
    int shiftAmount = validSupportEntries <= 4 ? 1 : 0;
    int lastPadding = validSupportEntries <= 6 && validSupportEntries > 4;
    for (int i = 0; i < validSupportEntries; ++i) {
        drawCenterText(offset + y_start + (i << shiftAmount) + (i == validSupportEntries - 1 ? lastPadding : 0), i == supportSelection ? TEXTCOLOR_LIGHTRED : TEXTCOLOR_RED, supportEntries[i].name);
    }
}

static void clearMenu() {
    drawRectangle(29, 17, 22, 8, BGCOLOR_BLACK);
}

static void drawMenu() {
    supportMenu ? drawSupportMenu(29, 17) : drawMainMenu(29, 17);
}

void drawMainLayout() {
    clearScreen();
    showCaret(false);
    drawLogo(6, 1, true, true);
    drawMenu(29, 16);
}

#ifndef RELEASE
static int getPressedMenuKey() {
    int keycode = getPressedKey();
    if (keycode == KEY_M) {
        showMemoryDebugInfo();
    }
    return keycode;
}
#else
    #define getPressedMenuKey() getPressedKey()
#endif

#ifndef LOW_MEMORY
static void extendEndScreen() {
    int firstPosition = *(int far *)((char far *)0xb8000000);
    int sharewarePosition = *(int far *)((char far *)0xb800000c);

    // Extend end B800 screen to cover the whole screen, check that we actually got an end screen
    // detect beta endscreen
    if (firstPosition == 0x01B0 && *(char far *)(0xb8000000 + 2 * 80 * 25) == ' ') {
        _hmemcpy((char far *)(0xb8000000 + 2 * 80 * 24), (char far *)(0xb8000000 + 2 * 80 * 23), 160);
        showCaret(false);
    // detect registered endscreen
    } else if (firstPosition == 0x19B0 && *(char far *)(0xb8000000 + 2 * 80 * 24) == ' ') {
        scrollWindowDown(1);
        _hmemcpy((char far *)(0xb8000000), (char far *)(0xb8000000 + 2 * 80), 160);
        // The pattern is actually slightly different for the last line in ep 2 and 3, so copy from there instead
        _hmemcpy((char far *)(0xb8000000 + 2 * 80 * 24), (char far *)(0xb8000000 + 2 * 80 * 23), 160);
        showCaret(false);
    // detect shareware endscreen
    } else if (sharewarePosition == 0x1F47 && *(char far *)(0xb8000000 + 2 * 80 * 24) == ' ') {
        scrollWindowDown(1);
        _hmemcpy((char far *)(0xb8000000), (char far *)(0xb8000000 + 2 * 80 * 23), 160);
        _hmemcpy((char far *)(0xb8000000 + 2 * 80 * 24), (char far *)(0xb8000000 + 2 * 80 * 23), 160);
        showCaret(false);
    }
}
#endif

static void runMainExe() {
    cleanup();
    #ifdef LOW_MEMORY
    if (gameVersion == VERSION_BETA) {
        exit(2);
    } else {
        exit(1);
    }
    #else
    if (gameVersion == VERSION_BETA) {
        setenv("CYGNUS", "BETA", true);
    }
    unsigned short errorCode = spawnve(P_WAIT, FILE_GAME_EXE, (const char**)args, (const char**)environ);
    if (errorCode == -1) {
        fprintf(stderr, EXEC_ERROR_MSG_F, FILE_GAME_EXE, strerror(errno));
    }
    if (gameVersion == VERSION_BETA) {
        setenv("CYGNUS", "", true);
    }
    // Some raptor versions send some keystrokes at the end, clear these
    clearInputBuffer();
    extendEndScreen();
    getPressedKey();
    drawMainLayout();
    #endif
}

static void runExe(const char* path) {
    cleanup();
    unsigned short errorCode = spawnl(P_WAIT, path, NULL);
    if (errorCode == -1) {
        fprintf(stderr, EXEC_ERROR_MSG_F, path, strerror(errno));
        getPressedKey();
    }
    drawMainLayout();
}

static void showText(const char* path, const char* title) {
    cleanup();
    showTextFile(path, title);
    drawMainLayout();
}

static bool handleMainMenuInput() {
    int character = getPressedMenuKey();
    switch (character) {
        case KEY_ARROW_UP:
            mainSelection = (mainSelection - 1 + validMenuEntries) % validMenuEntries;
            drawMenu();
            break;
        case KEY_ARROW_DOWN:
            mainSelection = (mainSelection + 1) % validMenuEntries;
            drawMenu();
            break;
        case KEY_ENTER:
            switch (menuEntries[mainSelection]) {
                case MAIN_ENTRY_LAUNCH_GAME:
                    runMainExe();
                    break;
                case MAIN_ENTRY_SETUP:
                    runExe("SETUP.EXE");
                    break;
                case MAIN_ENTRY_INSTRUCTIONS:
                    supportSelection = 0;
                    supportMenu = true;
                    clearMenu();
                    drawMenu();
                    break;
                case MAIN_ENTRY_QUIT:
                    return false;
            }
            break;
        case KEY_ESCAPE:
            return false;
        default:
            break;
    }
    return true;
}

static bool handleSupportMenuInput() {
    int supportAction;
    int character = getPressedMenuKey();
    switch (character) {
        case KEY_ARROW_UP:
            supportSelection = (supportSelection - 1 + validSupportEntries) % validSupportEntries;
            drawMenu();
            break;
        case KEY_ARROW_DOWN:
            supportSelection = (supportSelection + 1) % validSupportEntries;
            drawMenu();
            break;
        case KEY_ENTER:
            supportAction = supportEntries[supportSelection].actionId;
            if (supportAction < CUSTOM_SUPPORT_ACTION_START) {
                executeCommonSupportEntry(supportAction, APOGEE_GAME_TITLE, APOGEE_GAME_TITLE, versionString);
                return true;
            }
            switch (supportAction) {
                case CUSTOM_SUPPORT_ACTION_BETA_NOTE:
                    showText(FILE_BETA_README, "Raptor Beta Release Notes");
                    break;
                case CUSTOM_SUPPORT_ACTION_BACK:
                    supportMenu = false;
                    clearMenu();
                    drawMenu();
                    break;
                default:
                    break;
            }
            break;
        case KEY_ESCAPE:
            supportMenu = false;
            clearMenu();
            drawMenu();
            break;
        default:
            break;
    }
    return true;
}

int main(int argc, char *argv[]) {
    #ifdef LOW_MEMORY
        if (argc < 2) {
            printf("Run RAPTOR.BAT instead!\n");
            return EXIT_SUCCESS;
        }
        switch (argv[1][0]) {
            case '1':
                mainSelection = argv[1][0] - '1';
                break;
            default:
                printf("Illegal argument\n");
                return EXIT_FAILURE;
        }
    #endif

    bool running = true;
    args = argv;

    populateMenuAvailability();
    drawMainLayout();
    while (running) {
        running = supportMenu ? handleSupportMenuInput() : handleMainMenuInput();
    }
    cleanup();
    return EXIT_SUCCESS;
}
