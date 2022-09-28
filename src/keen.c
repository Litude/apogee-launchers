#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <process.h>
#include "lib/output.h"
#include "lib/input.h"
#include "lib/file.h"
#include "lib/text.h"
#include "lib/macro.h"
#include "lib/error.h"
#include "instruct/apogee.h"
#include "instruct/idsoft.h"
#include "instruct/psa.h"
#include "instruct/actions.h"
#include "version.h"

extern char **environ;
static char **args;

static const char* APOGEE_SHEET_PREFIX = "CK";
static const char* APOGEE_GAME_TITLE = "Commander Keen:Invasion of the Vorticons";

static const char* STRING_VERSION_131 = "v1.31";

static enum MAIN_ENTRY {
    MAIN_ENTRY_EP1,
    MAIN_ENTRY_EP2,
    MAIN_ENTRY_EP3,
    MAIN_ENTRY_INSTRUCTIONS,
    MAIN_ENTRY_QUIT,
    NUM_MAIN_ENTRIES,
};

static enum CUSTOM_SUPPORT_ACTIONS {
    CUSTOM_SUPPORT_ACTION_README = CUSTOM_SUPPORT_ACTION_START,
    CUSTOM_SUPPORT_ACTION_UPCOMING_GAMES,
    NUM_TOTAL_SUPPORT_ACTIONS
};

static const char ENTRY_README_NAME[] = "Readme";
static const char ENTRY_UPCOMING_GAMES_NAME[] = "Upcoming Games";

static const char COPYRIGHT_STRING_1990[] = "Copyright 1990 ID Software";
static const char COPYRIGHT_STRING_1991[] = "Copyright 1991 ID Software";
static const char DIST_ASP[] = "Published by Apogee Software";
static const char DIST_AGCT[] = "Distributed by Advanced Gravis Computer Technology";
static const char DIST_PSA[] = "Distributed by Precision Software Applications";
static const char EP1_STRING[] = "Marooned on Mars";
static const char EP2_STRING[] = "The Earth Explodes";
static const char EP3_STRING[] = "Keen Must Die!";

static const char* GAME_EXE_FILENAMES[] = {
    "KEEN1.EXE",
    "KEEN2.EXE",
    "KEEN3.EXE",
};

static const int NUM_EXE_NAMES = ARRAY_LENGTH(GAME_EXE_FILENAMES);

static const char FILE_NAME_SHAREWARE_README[] = "KEEN1.DOC";
static const char FILE_NAME_UPCOMING_GAMES[] = "KEEN3.DOC";

static char ANIMATION_STATES[] = { '|', '/', '-', '\\' };

static const char *versionString = NULL;

static const int STAR_COLORS[] = {
    TEXTCOLOR_DARKGRAY, TEXTCOLOR_GRAY, TEXTCOLOR_WHITE, TEXTCOLOR_GRAY
};

#define KEEN_EP1_901120_SIZE 79322
#define KEEN_EP1_901203_SIZE 43622

#define KEEN_EP1_V11_SIZE 51226
#define KEEN_EP1_V13_SIZE 50774
#define KEEN_EP1_V131_SIZE 51190
#define KEEN_EP1_V132_SIZE 51959
#define KEEN_EP1_V134_SIZE 49684

#define KEEN_EP2_V11_SIZE 58307
#define KEEN_EP2_V13_SIZE 57951
#define KEEN_EP2_V131_SIZE 58335
// #define KEEN_EP2_V134_SIZE 0

#define KEEN_EP3_V11_SIZE 61619
// #define KEEN_EP3_V13_SIZE 0
#define KEEN_EP3_V131_SIZE 61599
#define KEEN_EP3_V134_SIZE 58735

#define KEEN1_DOC_9112_SIZE 2266

static enum GAME_VERSION {
    VERSION_UNKNOWN,
    VERSION_BETA,
    VERSION_11,
    VERSION_13,
    VERSION_131,
    VERSION_132,
    VERSION_134
};

#define MAX_VISIBLE_INSTRUCTION_ITEMS 5

static int mainSelection = 0;
static int supportSelection = 0;
static bool supportMenu = false;
static int supportScroll = 0;
static int maxScroll = 0;
static int visibleSupportEntries = 0;

static int gameVersion = VERSION_UNKNOWN;

static bool ep1Enabled = false;
static bool ep2Enabled = false;
static bool ep3Enabled = false;
static bool showInstructions = false;
static unsigned int animationState = 0;
static unsigned int starState = 0;

static int menuEntries[NUM_MAIN_ENTRIES];
static menuEntry supportEntries[NUM_TOTAL_SUPPORT_ACTIONS];
static int validMenuEntries = 0;
static int validSupportEntries = 0;
static int supportXOffset = 0;

static int readmeStyle = TEXTCOLOR_CYAN|BGCOLOR_BLACK;

static void detectGameExeTypes() {
    for (int i = 0; i < NUM_EXE_NAMES; ++i) {
        const char* filename = GAME_EXE_FILENAMES[i];
        long exeSize = fileSize(filename);
        if (exeSize != -1) {
            int episode = (i % 3) + 1;
            if (episode == 1) {
                switch (exeSize) {
                    case KEEN_EP1_901120_SIZE:
                    case KEEN_EP1_901203_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_BETA);
                        break;
                    case KEEN_EP1_V11_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11);
                        break;
                    case KEEN_EP1_V13_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_13);
                        break;
                    case KEEN_EP1_V131_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_131);
                        versionString = STRING_VERSION_131;
                        break;
                    case KEEN_EP1_V132_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_132);
                        break;
                    case KEEN_EP1_V134_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_134);
                        break;
                    default:
                        break;
                }
                ep1Enabled = true;
            } else if (episode == 2) {
                switch (exeSize) {
                    case KEEN_EP2_V11_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11);
                        break;
                    case KEEN_EP2_V13_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_13);
                        break;
                    case KEEN_EP2_V131_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_131);
                        versionString = STRING_VERSION_131;
                        break;
                    // case KEEN_EP2_V134_SIZE:
                    //     gameVersion = MAX(gameVersion, VERSION_134);
                    //     break;
                    default:
                        break;
                }
                ep2Enabled = true;
            } else if (episode == 3) {
                switch (exeSize) {
                    case KEEN_EP3_V11_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11);
                        break;
                    // case KEEN_EP3_V13_SIZE:
                    //     gameVersion = MAX(gameVersion, VERSION_13);
                    //     break;
                    case KEEN_EP3_V131_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_131);
                        versionString = STRING_VERSION_131;
                        break;
                    case KEEN_EP3_V134_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_134);
                        break;
                    default:
                        break;
                }
                ep3Enabled = true;
            }
        }
    }
}

static void populateMenuAvailability() {
    detectGameExeTypes();
    
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP1;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP2;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP3;

    long readmeSize = fileSize(FILE_NAME_SHAREWARE_README);
    if (readmeSize != -1) {
        supportEntries[validSupportEntries].name = ENTRY_README_NAME;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_README;
        supportEntries[validSupportEntries].hotkey = KEY_R;
        ++validSupportEntries;
        if (readmeSize == KEEN1_DOC_9112_SIZE) {
            readmeStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
        }
    }

    if (fileExists(FILE_NAME_UPCOMING_GAMES)) {
        supportEntries[validSupportEntries].name = ENTRY_UPCOMING_GAMES_NAME;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_UPCOMING_GAMES;
        supportEntries[validSupportEntries].hotkey = KEY_U;
        ++validSupportEntries;
    }

    if (gameVersion == VERSION_134) {
        validSupportEntries += populatePrecisionSoftwareSupportEntries(&supportEntries[validSupportEntries], 0);
    } else {
        validSupportEntries += populateIdSoftwareSupportEntries(&supportEntries[validSupportEntries], 0);
        validSupportEntries += populateApogeeSupportEntries(&supportEntries[validSupportEntries], APOGEE_SHEET_PREFIX, 1 << APOGEE_SUPPORT_ACTION_HELP);
    }

    if (validSupportEntries) {
        showInstructions = true;
        menuEntries[validMenuEntries++] = MAIN_ENTRY_INSTRUCTIONS;

        int longest = 0;
        int current = 0;
        for (int i = 0; i < validSupportEntries; ++i) {
            current = strlen(supportEntries[i].name);
            if (current > longest) {
                longest = current;
            }
        }
        supportXOffset = -(longest >> 1);
        supportXOffset = MAX(supportXOffset, -12);
    }
    menuEntries[validMenuEntries++] = MAIN_ENTRY_QUIT;

    maxScroll = validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? validSupportEntries - MAX_VISIBLE_INSTRUCTION_ITEMS : 0;
    visibleSupportEntries = (validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? MAX_VISIBLE_INSTRUCTION_ITEMS : validSupportEntries);
}

void drawLogo(short x_start, short y_start) {
    drawOverlayText(10, y_start + 0, TEXTCOLOR_WHITE,     " ÉÍÍ»                                     Ë  Ë              ");
    drawOverlayText(10, y_start + 1, TEXTCOLOR_WHITE,     " º                                        º É¼              ");
    drawOverlayText(10, y_start + 2, TEXTCOLOR_WHITE,     " º    ÉÍ» ÉË» ÉË» ÉÍ» Ë» Ë ËÍ» ËÍ» ËÍ»    ÌÍ¹  ËÍ» ËÍ» Ë» Ë ");
    drawOverlayText(10, y_start + 3, TEXTCOLOR_WHITE,     " º    º º º º º º ÌÍ¹ ºÈ»º º º ÌÍ  ÌÍ¹    º È» ÌÍ  ÌÍ  ºÈ»º ");
    drawOverlayText(10, y_start + 4, TEXTCOLOR_WHITE,     " ÈÍÍ¼ ÈÍ¼ Ê Ê Ê Ê Ê Ê Ê È¼ ÊÍ¼ ÊÍ¼ Ê È    Ê  Ê ÊÍ¼ ÊÍ¼ Ê È¼ ");
    drawOverlayText(10, y_start + 5, TEXTCOLOR_WHITE,     "ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹");
    drawOverlayText(10, y_start + 6, TEXTCOLOR_LIGHTBLUE, "      I N V A S I O N   O F   T H E   V O R T I C O N S     ");
}

void drawBackground(int i) {
    int state0 = STAR_COLORS[(i + 0) & 0x3];
    int state1 = STAR_COLORS[(i + 1) & 0x3];
    int state2 = STAR_COLORS[(i + 2) & 0x3];
    int state3 = STAR_COLORS[(i + 3) & 0x3];
    drawColorChar( 3, 2, state2, 'ù');
    drawColorChar( 6, 4, state3, 'ù');
    drawColorChar(30, 1, state3, 'ù');
    drawColorChar( 3, 9, state3, 'ù');
    drawColorChar( 5, 7, state2, 'ù');
    drawColorChar(19, 0, state2, 'ù');
    drawColorChar(20, 8, state3, 'ù');
    drawColorChar(65, 0, state3, 'ù');
    drawColorChar(73, 2, state2, 'ù');
    drawColorChar(75, 5, state1, 'ù');
    drawColorChar(57, 7, state1, 'ù');
    drawColorChar(73, 4, state2, 'ù');
    drawColorChar( 5, 10, state1, 'ù');
    drawColorChar( 5, 15, state1, 'ù');
    drawColorChar( 3, 17, state2, 'ù');
    drawColorChar( 5, 17, state3, 'ù');
    drawColorChar(15, 11, state2, 'ù');
    drawColorChar(15, 18, state3, 'ù');
    drawColorChar(45, 10, state3, 'ù');
    drawColorChar(63, 17, state1, 'ù');
    drawColorChar(59, 14, state2, 'ù');
    drawColorChar(34, 19, state2, 'ù');
    drawColorChar(64, 12, state2, 'ù');
    drawColorChar(20, 12, state0, 'ù');
    drawColorChar( 5, 23, state2, 'ù');
    drawColorChar(26, 27, state1, 'ù');
    drawColorChar(38, 24, state1, 'ù');
    drawColorChar(45, 21, state2, 'ù');
    drawColorChar(19, 16, state2, 'ù');
    drawColorChar(47, 18, state3, 'ù');
    drawColorChar(58, 18, state3, 'ù');
    drawColorChar(72, 10, state3, 'ù');
    drawColorChar(75, 12, state2, 'ù');
    drawColorChar(78, 13, state0, 'ù');
    drawColorChar(69, 15, state0, 'ù');
    drawColorChar(76, 17, state3, 'ù');
    drawColorChar(77, 18, state2, 'ù');
    drawColorChar(78, 21, state2, 'ù');
}

void drawGlobe(x_start, y_start) {
    drawOverlayText(x_start, y_start + 0, TEXTCOLOR_BLUE|BGCOLOR_BLACK, "          ÜÜÜÛÛÛÛÛÛÛÛÛÜÜÜ          ");
    drawOverlayText(x_start, y_start + 1, TEXTCOLOR_BLUE|BGCOLOR_BLACK, "      ÜÜÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÜÜ      ");
    drawOverlayText(x_start, y_start + 2, TEXTCOLOR_GREEN|BGCOLOR_BLUE, "    ÜÿÿÿÿÿÿÿÜÿÿÿÜÜÿÿÜÿÜÿÜÿÿÿÿÿÜ    ");
    drawOverlayText(x_start, y_start + 3, TEXTCOLOR_GREEN|BGCOLOR_BLUE, "   ÜÿÿÿÿÿÜÜÜÜÛÿÛÜÛÛÛÛÛÛÛÛÜÜÿÿÿÿÿ   ");
    drawOverlayText(x_start, y_start + 4, TEXTCOLOR_GREEN|BGCOLOR_BLUE, " ÛÛÛÛÿÿÿÛÛÛÛÛÛÛÜßÛÛßÛßÛÛÛÛßÿÿÿÿÿÛÛ ");
    drawOverlayText(x_start, y_start + 5, TEXTCOLOR_GREEN|BGCOLOR_BLUE, "ÛÛÛßÿÿÿÿÿßÛÛÛÛÛÛÛÜßÛÜÛÛÛÛÛÿÿÿÿÿÿÿßß");
    setBlockColor(x_start + 4, y_start + 2, TEXTCOLOR_BLUE|BGCOLOR_BLACK);
    setBlockColor(x_start + 30, y_start + 2, TEXTCOLOR_BLUE|BGCOLOR_BLACK);
}

void drawStarship() {
    int x_start = 2;
    int y_start = 19;

    drawRawText(x_start, y_start + 0, "               ÜÛÛÛÛÜßßÛÛÛÛÜÜÜÜ      ßßÛÛÛÜ");
    drawRawText(x_start, y_start + 1, "ÜÜßßßßßßßßßßßßÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛßßßÛÛÛÛßß ");
    drawRawText(x_start, y_start + 2, " ßÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛßßßßßßÛÛÛÛÛÛÛÛÛÛÛÛÛ     ");
    drawRawText(x_start, y_start + 3, "     ßßßßßÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛß       ");
    drawRawText(x_start, y_start + 4, "          ÜÜÜÜÜÛßÛÛÛÛÛÛÛÛÛÛÛßßßß           ");


    setRawColorData(x_start + 15, y_start + 0, "\x09\x09\x09\x09\x09\x19\x1F\x1F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x07\x07\x07\x07\x07\x07\x0F\x0F\x0F\x0F\x0F\x0F");
    setRawColorData(x_start, y_start + 1, "\x0F\x0F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x7F\x7F\x7F"); //\x07\x07\x07\x07\x07\x07");
    setRawColorData(x_start + 19, y_start + 2, "\x7F\x7F\x7F\x7F\x7F\x7F");
    setRawColorData(x_start + 10, y_start + 4, "\x0F\x0F\x0F\x0F\x0F\x7F\x7F");
}

void drawStripes() {
    int y_start = 19;
    int x_start = 0;
    drawColorText(x_start + 47, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, "ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ");
    drawColorText(x_start + 57, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BLUE, "ÜÜÜÜÜÜÜÜÜ");

    drawColorChar(x_start + 37, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_GRAY, 'Ü');
    drawColorText(x_start + 38, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, "ÜÜÜÜÜÜÜÜÜ");
    drawColorText(x_start + 47, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_BLUE, "ÜÜÜÜÜÜÜÜÜÜÜÜÜÜ");
    drawColorChar(x_start + 57, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_GREEN, 'Ü');
    drawColorChar(x_start + 59, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_GREEN, 'Ü');
    drawColorText(x_start + 61, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_GREEN, "ÜÜÜÜÜÜÜÜ");
    drawColorText(x_start + 69, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_BLUE, "ÜÜÜÜÜÜÜ");
    drawColorText(x_start + 76, y_start + 3, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, "ÜÜÜÜ");

    drawColorText(x_start + 32, y_start + 4, TEXTCOLOR_YELLOW|BGCOLOR_GRAY, "ÜÜ");
    drawColorText(x_start + 34, y_start + 4, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, "ÜÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");

}

void drawBottomGraphic() {
    drawStarship();
    drawGlobe(44, 19);
    drawStripes();
}

static inline int getSupportMenuStartY() {
    return 12 - ((visibleSupportEntries | 0x1) >> 1);
}

static void drawSupportSelectionMarker() {
    int y = getSupportMenuStartY();
    drawColorChar(36 + supportXOffset, supportSelection == visibleSupportEntries ? y + visibleSupportEntries + 2 : y + 1 + supportSelection, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ANIMATION_STATES[animationState]);
}

static void drawSupportMenu(bool updateSelectionOnly) {
    int y = getSupportMenuStartY();
    if (updateSelectionOnly) {
        for (int i = 0; i < visibleSupportEntries; ++i) {
            drawColorChar(36 + supportXOffset, y + 1 + i, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
        }
        drawColorChar(36 + supportXOffset, y + visibleSupportEntries + 2, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
        return;
    }

    drawRectangle(24, 10, 32, 8, BGCOLOR_BLACK);
    for (int i = 0; i < visibleSupportEntries; ++i) {
        drawColorChar(36 + supportXOffset, y + 1 + i, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
        drawLetterHighlightText(38 + supportXOffset, y + 1 + i, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTPURPLE, KEYCHAR_MAP[supportEntries[supportScroll + i].hotkey], supportEntries[supportScroll + i].name);
    }
    drawColorChar(36 + supportXOffset, y + visibleSupportEntries + 2, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
    drawLetterHighlightText(38 + supportXOffset, y + visibleSupportEntries + 2, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTCYAN, 'B', "Back");
    drawSupportSelectionMarker();
    if (supportScroll > 0) {
        drawCenterText(y, TEXTCOLOR_WHITE, "...");
    }
    if (supportScroll < maxScroll) {
        drawCenterText(y + MAX_VISIBLE_INSTRUCTION_ITEMS + 1, TEXTCOLOR_WHITE, "...");
    }
}

static void drawMainSelectionMarker() {
    int yPos = 0;
    if (showInstructions) {
        switch (mainSelection) {
            case 0:
                yPos = 12;
                break;
            case 1:
                yPos = 13;
                break;
            case 2:
                yPos = 14;
                break;
            case 3:
                yPos = 16;
                break;
            case 4:
                yPos = 17;
                break;
            default:
                break;
        }
    } else {
        switch (mainSelection) {
            case 0:
                yPos = 13;
                break;
            case 1:
                yPos = 14;
                break;
            case 2:
                yPos = 15;
                break;
            case 3:
                yPos = 17;
                break;
            default:
                break;
        }
    }
    drawColorChar(28, yPos, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ANIMATION_STATES[animationState]);
}

void drawSelectionMarker() {
    supportMenu ? drawSupportSelectionMarker() : drawMainSelectionMarker();
}

static void drawMainMenu(bool updateSelectionOnly) {
    drawCenterText(11, TEXTCOLOR_YELLOW, "-- SELECT AN EPISODE --");
    int episodeOffset = showInstructions ? -1 : 0;
    drawColorChar(28, 13 + episodeOffset, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
    drawColorChar(28, 14 + episodeOffset, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
    drawColorChar(28, 15 + episodeOffset, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
    drawColorChar(28, 17, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
    if (showInstructions) {
        drawColorChar(28, 16, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLACK, ' ');
    }
    drawMainSelectionMarker();
    if (updateSelectionOnly) return;

    ep1Enabled ?
        drawLetterHighlightText(30, 13 + episodeOffset, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTPURPLE, '1', EP1_STRING)
        :
        drawLetterHighlightText(30, 13 + episodeOffset, TEXTCOLOR_PURPLE, TEXTCOLOR_PURPLE, '1', EP1_STRING);
    ep2Enabled ?
        drawLetterHighlightText(30, 14 + episodeOffset, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTPURPLE, '2', EP2_STRING)
        :
        drawLetterHighlightText(30, 14 + episodeOffset, TEXTCOLOR_PURPLE, TEXTCOLOR_PURPLE, '2', EP2_STRING);
    ep3Enabled ?
        drawLetterHighlightText(30, 15 + episodeOffset, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTPURPLE, '3', EP3_STRING)
        :
        drawLetterHighlightText(30, 15 + episodeOffset, TEXTCOLOR_PURPLE, TEXTCOLOR_PURPLE, '3', EP3_STRING);
    if (showInstructions) {
        drawLetterHighlightText(30, 16, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTPURPLE, 'I', "Instructions");
    }
    drawLetterHighlightText(30, 17, TEXTCOLOR_LIGHTRED, TEXTCOLOR_LIGHTCYAN, 'Q', "Quit");
}

static void clearMenu() {
    drawRectangle(24, 10, 32, 8, BGCOLOR_BLACK);
}

static void drawMenu(bool updateSelectionOnly) {
    supportMenu ? drawSupportMenu(updateSelectionOnly) : drawMainMenu(updateSelectionOnly);
}

static void findMainSelection(int menuEntry) {
    int i;
    bool success = false;
    for (i = 0; i < validMenuEntries; ++i) {
        if (menuEntries[i] == menuEntry) {
            success = true;
            break;
        }
    }
    if (success) {
        mainSelection = i;
        drawMenu(true);
    }
}

const char* getPublisherString() {
    switch (gameVersion) {
        case VERSION_132:
            return DIST_AGCT;
        case VERSION_134:
            return DIST_PSA;
        default:
            return DIST_ASP;
    }
}

void drawMainLayout() {
    clearScreen();
    showCaret(false);
    drawLogo(10, 0);
    drawCenterText(8, TEXTCOLOR_WHITE, gameVersion >= VERSION_131 ? COPYRIGHT_STRING_1991 : COPYRIGHT_STRING_1990);
    drawCenterText(9, TEXTCOLOR_GRAY, getPublisherString());
    drawBottomGraphic();
    drawBackground(starState);
    drawMenu(false);
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
static void runMainExe(const char* path) {
    cleanup();
    unsigned short errorCode = spawnve(P_WAIT, path, (const char**)args, (const char**)environ);
    if (errorCode == -1) {
        fprintf(stderr, EXEC_ERROR_MSG_F, path, strerror(errno));
    }
    getPressedKey();
    drawMainLayout();
}
#endif

static void showText(const char* path, const char* title, int textStyle) {
    cleanup();
    storeTextStyle();
    setStyle(textStyle, TEXTCOLOR_BLACK|BGCOLOR_GRAY, TEXT_LAYOUT_TRADITIONAL);
    showTextFile(path, title);
    restoreTextStyle();
    drawMainLayout();
}

static bool handleMainMenuInput() {
    int character = getPressedMenuKey();
    switch (character) {
        case KEY_ARROW_UP:
            mainSelection = (mainSelection - 1 + validMenuEntries) % validMenuEntries;
            drawMenu(true);
            break;
        case KEY_ARROW_DOWN:
            mainSelection = (mainSelection + 1) % validMenuEntries;
            drawMenu(true);
            break;
        case KEY_1:
            findMainSelection(MAIN_ENTRY_EP1);
            break;
        case KEY_2:
            findMainSelection(MAIN_ENTRY_EP2);
            break;
        case KEY_3:
            findMainSelection(MAIN_ENTRY_EP3);
            break;
        case KEY_I:
            findMainSelection(MAIN_ENTRY_INSTRUCTIONS);
            break;
        case KEY_Q:
            findMainSelection(MAIN_ENTRY_QUIT);
            break;
        case KEY_ENTER:
            switch (menuEntries[mainSelection]) {
                case MAIN_ENTRY_EP1:
                    if (ep1Enabled) {
                        #ifdef LOW_MEMORY
                            cleanup();
                            exit(1);
                        #else
                            runMainExe(GAME_EXE_FILENAMES[0]);
                        #endif
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_EP2:
                    if (ep2Enabled) {
                        #ifdef LOW_MEMORY
                            cleanup();
                            exit(2);
                        #else
                            runMainExe(GAME_EXE_FILENAMES[1]);
                        #endif
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_EP3:
                    if (ep3Enabled) {
                        #ifdef LOW_MEMORY
                            cleanup();
                            exit(3);
                        #else
                            runMainExe(GAME_EXE_FILENAMES[2]);
                        #endif
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_INSTRUCTIONS:
                    supportMenu = true;
                    clearMenu();
                    drawMenu(false);
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
            // If we are jumping from back to last instruction
            if (supportSelection == visibleSupportEntries) {
                supportScroll = maxScroll;
                --supportSelection;
                drawMenu(false);
            } else if (!supportSelection && supportScroll) {
                --supportScroll;
                drawMenu(false);
            } else {
                supportSelection = (supportSelection - 1 + (visibleSupportEntries + 1)) % (visibleSupportEntries + 1);
                drawMenu(true);
            }
            break;
        case KEY_ARROW_DOWN:
            if (supportSelection == MAX_VISIBLE_INSTRUCTION_ITEMS - 1 && supportScroll < maxScroll) {
                ++supportScroll;
                drawMenu(false);
            } else if (supportSelection == visibleSupportEntries) {
                supportSelection = 0;
                supportScroll = 0;
                drawMenu(false);
            } else {
                supportSelection = (supportSelection + 1) % (visibleSupportEntries + 1);
                drawMenu(true);
            }
            break;
        case KEY_ENTER:
            if (supportSelection == visibleSupportEntries) {
                supportMenu = false;
                clearMenu();
                drawMenu(false);
                return true;
            }
            supportAction = supportEntries[supportSelection + supportScroll].actionId;
            if (supportAction < CUSTOM_SUPPORT_ACTION_START) {
                executeCommonSupportEntry(supportAction, "COMMANDER KEEN", APOGEE_GAME_TITLE, versionString);
                return true;
            }
            switch (supportAction) {
                case CUSTOM_SUPPORT_ACTION_README:
                    showText(FILE_NAME_SHAREWARE_README, "COMMANDER KEEN: INVASION OF THE VORTICONS", readmeStyle);
                    break;
                case CUSTOM_SUPPORT_ACTION_UPCOMING_GAMES:
                    showText(FILE_NAME_UPCOMING_GAMES, "COMING SOON FROM APOGEE SOFTWARE PRODUCTIONS & ID SOFTWARE", TEXTCOLOR_CYAN|BGCOLOR_BLACK);
                    break;
                default:
                    break;
            }
            break;
        case KEY_ESCAPE:
            supportMenu = false;
            clearMenu();
            drawMenu(false);
            break;
        case KEY_B:
            supportSelection = visibleSupportEntries;
            drawMenu(true);
        default:
            for (int i = 0; i < validSupportEntries; ++i) {
                if (supportEntries[i].hotkey == character) {
                    int difference = i - supportScroll;
                    if (difference >= 0) {
                        if (difference < MAX_VISIBLE_INSTRUCTION_ITEMS) {
                            supportSelection = difference;
                            drawMenu(true);
                        } else {
                            supportSelection = MAX_VISIBLE_INSTRUCTION_ITEMS - 1;
                            supportScroll = i - (MAX_VISIBLE_INSTRUCTION_ITEMS - 1);
                            drawMenu(false);
                        }
                    } else if (difference < 0) {
                        supportSelection = 0;
                        supportScroll = i;
                        drawMenu(false);
                    }
                    break;
                }
            }
            break;
    }
    return true;
}

int main(int argc, char *argv[]) {
    #ifdef LOW_MEMORY
        if (argc < 2) {
            printf("Run KEEN.BAT instead!\n");
            return EXIT_SUCCESS;
        }
        switch (argv[1][0]) {
            case '1':
            case '2':
            case '3':
                mainSelection = argv[1][0] - '1';
                break;
            default:
                printf("Illegal argument\n");
                return EXIT_FAILURE;
        }
    #endif

    args = argv;
    
    populateMenuAvailability();
    drawMainLayout();

    bool running = true;
    long updateTime = getTime();
    long starUpdateTime = updateTime;
    while (running) {
        bool input = hasWaitingInput();
        if (input) {
            running = supportMenu ? handleSupportMenuInput() : handleMainMenuInput();
        } else {
            long currentTime = getTime();
            if (currentTime < updateTime || currentTime - updateTime > 20) {
                updateTime = currentTime;
                animationState = (animationState + 1) & 0x03;
                drawSelectionMarker();
            }
            if (currentTime < starUpdateTime || currentTime - starUpdateTime > 15) {
                starUpdateTime = currentTime;
                drawBackground(++starState);
            }
        }
    }
    cleanup();
    return 0;
}
