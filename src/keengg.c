#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <process.h>
#include "lib/args.h"
#include "lib/output.h"
#include "lib/input.h"
#include "lib/file.h"
#include "lib/text.h"
#include "lib/memory.h"
#include "lib/menu.h"
#include "lib/macro.h"
#include "instruct/apogee.h"
#include "instruct/idsoft.h"
#include "instruct/actions.h"
#include "dopefish.h"
#include "version.h"

extern char **environ;
static const char **args;

static const char* APOGEE_SHEET_PREFIX = "GG";
static const char* APOGEE_GAME_TITLE_OLD = "COMMANDER KEEN: GOODBYE, GALAXY!";
static const char* APOGEE_GAME_TITLE = "Commander Keen:Goodbye, Galaxy";
static const char* ID_GAME_TITLE = "Commander Keen: Goodbye, Galaxy!";

static const char* TXT_VERSION_14 = "v1.4";

static enum MAIN_ENTRY {
    MAIN_ENTRY_EP4,
    MAIN_ENTRY_EP5,
    MAIN_ENTRY_INSTRUCTIONS,
    MAIN_ENTRY_QUIT,
    NUM_MAIN_ENTRIES,
};

static enum VIDEO_MODE_ENTRY {
    VIDEO_MODE_ENTRY_CGA,
    VIDEO_MODE_ENTRY_EGA,
    VIDEO_MODE_ENTRY_BACK,
    NUM_VIDEO_MODE_ENTRIES
};

static enum VIDEO_MODE {
    VIDEO_MODE_UNKNOWN,
    VIDEO_MODE_CGA,
    VIDEO_MODE_EGA
};

static enum CUSTOM_SUPPORT_ACTIONS {
    CUSTOM_SUPPORT_ACTION_README = CUSTOM_SUPPORT_ACTION_START,
    CUSTOM_SUPPORT_ACTION_HINT_TXT,
    NUM_TOTAL_SUPPORT_ACTIONS
};

static const int SORT_ORDER[] = {
    CUSTOM_SUPPORT_ACTION_README,
    IDSOFT_SUPPORT_ACTION_GREETINGS,
    IDSOFT_SUPPORT_ACTION_VENDOR_LETTER,
    APOGEE_SUPPORT_ACTION_INSTALL_HELP,
    APOGEE_SUPPORT_ACTION_HINT,
    CUSTOM_SUPPORT_ACTION_HINT_TXT,
};

static const char ENTRY_README_NAME[] = "Readme";

static const char COPYRIGHT_1991[] = "Copyright 1991 Id Software Inc.";
static const char COPYRIGHT_1992[] = "Copyright 1992 Id Software Inc.";
static const char DISTRIBUTE_ASP[] = "Distributed by Apogee Software Productions";
static const char DISTRIBUTE_FGC[] = "Distributed by FormGen Corporation";
static const char DISTRIBUTE_GTS[] = "BROUGHT TO YOU BY GOODTIMES SOFTWARE!";
static const char EXEC_ERROR_F[] = "Error when executing %s: %s\n";

static const char EPISODE4_TITLE[] = "Episode IV: Secret of the Oracle";
static const char EPISODE5_TITLE[] = "Episode V: The Armageddon Machine";

static enum GAME_EXE_FILENAME_TYPES {
    GAME_EXE_KEEN,
    GAME_EXE_KEEN4E,
    GAME_EXE_KEEN4C,
    GAME_EXE_KEEN4,
    GAME_EXE_KEEN5E,
    GAME_EXE_KEEN5C,
    GAME_EXE_KEEN5,
    NUM_EXE_NAMES
};

static const char* GAME_EXE_FILENAMES[] = {
    "KEEN.EXE",
    "KEEN4E.EXE",
    "KEEN4C.EXE",
    "KEEN4.EXE",
    "KEEN5E.EXE",
    "KEEN5C.EXE",
    "KEEN5.EXE"
};

static const char FILE_NAME_README[] = "README.DOC";
static const char FILE_NAME_HINT_SHEET_TXT[] = "CK-HINTS.TXT";

static const char DIRECTORY_NAME_EGASAVE[] = "EGASAVE";
static const char DIRECTORY_NAME_CGASAVE[] = "CGASAVE";
static const char FILE_NAME_VIDEO_CONFIG[] = "CONFIG.CKG";

static const char FILE_NAME_SAVE_PREFIX[] = "SAVEGAM";
static const char* FILE_NAME_SAVE_SUFFIXES[] = {
    ".CK4",
    ".CK5"
};
static const char FILE_NAME_CONFIG_PREFIX[] = "CONFIG";

static const char DIRECTORY_PREFIX_CURRENT[] = "";
static const char DIRECTORY_PREFIX_EGASAVE[] = "EGASAVE\\";
static const char DIRECTORY_PREFIX_CGASAVE[] = "CGASAVE\\";

static const char *versionString = NULL;

static const int SECRET_PATTERN[] = { KEY_D, KEY_O, KEY_P, KEY_E, KEY_F, KEY_I, KEY_S, KEY_H };
static int pressedKeys[ARRAY_LENGTH(SECRET_PATTERN)];
static int secretIndex = 0;

#define KEENGG_EP4_DEMO_EGA_SIZE 98578

#define KEENGG_EP4_V10_EGA_SIZE 102355
#define KEENGG_EP4_V11_EGA_SIZE 102730
#define KEENGG_EP4_V12_EGA_SIZE 103224
#define KEENGG_EP4_V14_EGA_SIZE 105108
#define KEENGG_EP4_V14FG_EGA_SIZE 105140
#define KEENGG_EP4_V14GT_EGA_SIZE 106178

#define KEENGG_EP4_V10_OR_V11_CGA_SIZE 96019
#define KEENGG_EP4_V10_CGA_SCSUM 13645
#define KEENGG_EP4_V11_CGA_SCSUM 22215
// #define KEENGG_EP4_V10_CGA_CSUM 41771
// #define KEENGG_EP4_V11_CGA_CSUM 13494
// #define KEENGG_EP4_V12_CGA_SIZE 0
#define KEENGG_EP4_V14_OR_V14FG_CGA_SIZE 98007
// #define KEENGG_EP4_V14_CGA_CSUM 58569
// #define KEENGG_EP4_V14FG_CGA_CSUM 20288
#define KEENGG_EP4_V14_CGA_SCSUM 27160
#define KEENGG_EP4_V14FG_CGA_SCSUM 9661


#define KEENGG_EP5_V10_EGA_SIZE 104445
#define KEENGG_EP5_V14_EGA_SIZE 106417
#define KEENGG_EP5_V14GT_EGA_SIZE 107611

// #define KEENGG_EP5_V10_CGA_SIZE 0
#define KEENGG_EP5_V14_CGA_SIZE 98880

#define README_ID_VER_SIZE 1196

#define MAX_VISIBLE_INSTRUCTION_ITEMS 6

static enum GAME_VERSION {
    VERSION_UNKNOWN,
    VERSION_DEMO,
    VERSION_10,
    VERSION_11,
    VERSION_12,
    VERSION_14,
    VERSION_14FG,
    VERSION_14GT
};

typedef enum {
    MENU_MAIN,
    MENU_SUPPORT,
    MENU_VIDEOMODE
} MENU_TYPE;

static int mainSelection = 0;
static int videoSelection = 0;

static int supportSelection = 0;
static int supportScroll = 0;
static int maxScroll = 0;
static int visibleSupportEntries = 0;

static MENU_TYPE activeMenu = MENU_MAIN;
static int gameVersion = VERSION_UNKNOWN;

static const char* ep4CgaFileName = NULL;
static const char* ep4EgaFileName = NULL;
static const char* ep5CgaFileName = NULL;
static const char* ep5EgaFileName = NULL;
static bool ep4Enabled = false;
static bool ep5Enabled = false;
static bool cgaAndEgaExists = false;
static bool showInstructions = false;
static bool animationState = false;

static int menuEntries[NUM_MAIN_ENTRIES];
static menuEntry supportEntries[NUM_TOTAL_SUPPORT_ACTIONS];
static int validMenuEntries = 0;
static int validSupportEntries = 0;

static bool readmeIdStyle = false;

static int selectedEpisode = -1;

#ifdef LOW_MEMORY
static int exitCodeForFileName(const char* filename) {
    for (int i = 0; i < NUM_EXE_NAMES; ++i) {
        if (!strcmp(GAME_EXE_FILENAMES[i], filename)) {
            return i + 1;
        }
    }
    return 0xFF;
}
#endif

static void sortSupportEntries() {
    int nextPos = 0;
    menuEntry temp;
    for (int i = 0; i < ARRAY_LENGTH(SORT_ORDER); ++i) {
        for (int j = nextPos; j < validSupportEntries; ++j) {
            if (supportEntries[j].actionId == SORT_ORDER[i]) {
                if (j != nextPos) {
                    temp = supportEntries[j];
                    memmove(&supportEntries[nextPos+1], &supportEntries[nextPos], (j - nextPos) * sizeof(menuEntry));
                    supportEntries[nextPos] = temp;
                }
                ++nextPos;
                break;
            }
        }
    }
}

static bool detectKnownExe(long exeSize, const char* filename) {
    unsigned int csum;
    switch (exeSize) {
        case KEENGG_EP4_DEMO_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_DEMO);
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP4_V10_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_10);
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP4_V11_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_11);
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP4_V10_OR_V11_CGA_SIZE:
            csum = checksumPartial(filename, 0, 32000);
            if (csum == KEENGG_EP4_V10_CGA_SCSUM) {
                gameVersion = MAX(gameVersion, VERSION_10);
                ep4CgaFileName = filename;
                return true;
            } else if (csum == KEENGG_EP4_V11_CGA_SCSUM) {
                gameVersion = MAX(gameVersion, VERSION_11);
                ep4CgaFileName = filename;
                return true;
            }
            return false;
        case KEENGG_EP4_V12_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_12);
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP5_V10_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_12); // v1.0 Ep5 equals v1.2 Ep4
            ep5EgaFileName = filename;
            return true;
        case KEENGG_EP4_V14_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_14);
            versionString = TXT_VERSION_14;
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP5_V14_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_14);
            versionString = TXT_VERSION_14;
            ep5EgaFileName = filename;
            return true;
        case KEENGG_EP5_V14_CGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_14);
            versionString = TXT_VERSION_14;
            ep5CgaFileName = filename;
            return true;
        case KEENGG_EP4_V14_OR_V14FG_CGA_SIZE:
            // These only differ at the end
            csum = checksumPartial(filename, 66112, 31895);
            if (csum == KEENGG_EP4_V14_CGA_SCSUM) {
                gameVersion = MAX(gameVersion, VERSION_14);
                versionString = TXT_VERSION_14;
                ep4CgaFileName = filename;
                return true;
            } else if (csum == KEENGG_EP4_V14FG_CGA_SCSUM) {
                gameVersion = MAX(gameVersion, VERSION_14FG);
                ep4CgaFileName = filename;
                return true;
            }
            return false;
        case KEENGG_EP4_V14FG_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_14FG);
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP4_V14GT_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_14GT);
            ep4EgaFileName = filename;
            return true;
        case KEENGG_EP5_V14GT_EGA_SIZE:
            gameVersion = MAX(gameVersion, VERSION_14GT);
            ep5EgaFileName = filename;
            return true;
        default:
            return false;
    }
}

static void detectGameExeTypes() {
    for (int i = 0; i < NUM_EXE_NAMES; ++i) {
        const char* filename = GAME_EXE_FILENAMES[i];
        long exeSize = fileSize(filename);
        if (exeSize != -1) {
            if (!detectKnownExe(exeSize, filename)) {
                switch (i) {
                    case GAME_EXE_KEEN4: // This could be CGA (as in FormGen), but probably not
                    case GAME_EXE_KEEN4E:
                        ep4EgaFileName = filename;
                        break;
                    case GAME_EXE_KEEN4C:
                        ep4CgaFileName = filename;
                        break;
                    case GAME_EXE_KEEN5:
                    case GAME_EXE_KEEN5E:
                        ep5EgaFileName = filename;
                        break;
                    case GAME_EXE_KEEN5C:
                        ep5CgaFileName = filename;
                        break;
                    case GAME_EXE_KEEN: // ignore this because name is too generic
                    default:
                        break;
                }
            }
        }
    }
    ep4Enabled = ep4EgaFileName || ep4CgaFileName;
    ep5Enabled = ep5EgaFileName || ep5CgaFileName;
    cgaAndEgaExists = ((ep4EgaFileName || ep5EgaFileName) && (ep4CgaFileName || ep5CgaFileName)) || hasArgument("forcevideo", args);
}

static void moveFiles(const char* src, const char* dst) {
    char srcBuffer[30], dstBuffer[30], num[2], fileName[13];
    num[1] = '\0';
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i <= 5; ++i) {
            num[0] = '0' + i;
            strcpy(fileName, FILE_NAME_SAVE_PREFIX);
            strcat(fileName, num);
            strcat(fileName, FILE_NAME_SAVE_SUFFIXES[j]);
            strcpy(srcBuffer, src);
            strcat(srcBuffer, fileName);
            strcpy(dstBuffer, dst);
            strcat(dstBuffer, fileName);
            farrename(srcBuffer, dstBuffer);
        }
        strcpy(fileName, FILE_NAME_CONFIG_PREFIX);
        strcat(fileName, FILE_NAME_SAVE_SUFFIXES[j]);
        strcpy(srcBuffer, src);
        strcat(srcBuffer, fileName);
        strcpy(dstBuffer, dst);
        strcat(dstBuffer, fileName);
        farrename(srcBuffer, dstBuffer);
    }
}

static bool findSupportEntry(int actionId) {
    for (int i = 0; i < validSupportEntries; ++i) {
        if (supportEntries[i].actionId == actionId) {
            return true;
        }
    }
    return false;
}

static void populateMenuAvailability() {
    detectGameExeTypes();

    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP4;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP5;

    long readmeSize = fileSize(FILE_NAME_README);
    if (readmeSize != -1) {
        supportEntries[validSupportEntries].name = ENTRY_README_NAME;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_README;
        supportEntries[validSupportEntries].hotkey = 0;
        ++validSupportEntries;
    }

    if (readmeSize == README_ID_VER_SIZE) {
        readmeIdStyle = true;
    }

    validSupportEntries += populateIdSoftwareSupportEntries(&supportEntries[validSupportEntries], 0);
    validSupportEntries += populateApogeeSupportEntries(&supportEntries[validSupportEntries], APOGEE_SHEET_PREFIX, 1 << APOGEE_SUPPORT_ACTION_HELP);

    if (fileExists(FILE_NAME_HINT_SHEET_TXT) && !findSupportEntry(APOGEE_SUPPORT_ACTION_HINT)) {
        supportEntries[validSupportEntries].name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_HINT];
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_HINT_TXT;
        supportEntries[validSupportEntries].hotkey = 0;
        ++validSupportEntries;
    }

    sortSupportEntries();

    if (validSupportEntries) {
        showInstructions = true;
        menuEntries[validMenuEntries++] = MAIN_ENTRY_INSTRUCTIONS;
    }
    menuEntries[validMenuEntries++] = MAIN_ENTRY_QUIT;

    maxScroll = validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? validSupportEntries - MAX_VISIBLE_INSTRUCTION_ITEMS : 0;
    visibleSupportEntries = (validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? MAX_VISIBLE_INSTRUCTION_ITEMS : validSupportEntries);
}

static void drawLogo(int x_start, int y_start) {
    drawColorText(x_start - 1, y_start - 1, TEXTCOLOR_BLACK|BGCOLOR_BLUE, " ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹ ");
    drawRectangle(x_start - 1, y_start, 62, 4, BGCOLOR_BLACK);
    drawColorChar(x_start - 1, y_start - 1, TEXTCOLOR_BLUE|BGCOLOR_BLACK, '≤');
    drawColorChar(x_start + 60, y_start - 1, TEXTCOLOR_BLUE|BGCOLOR_BLACK, '≤');
    drawColorChar(x_start - 1, y_start + 3, TEXTCOLOR_BLACK|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 60, y_start + 3, TEXTCOLOR_BLACK|BGCOLOR_BLUE, 'ﬂ');

    drawColorText(x_start, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, " ‹ﬂﬂ‹ ‹ﬂﬂ‹ ‹ﬂ‹ﬂ‹ ‹ﬂ‹ﬂ‹ ‹ﬂ‹ ‹ﬂ‹ ‹ﬂ‹ ‹ﬂﬂ ‹ﬂ‹  € € ‹ﬂﬂ ‹ﬂﬂ ‹ﬂ‹ ");
    drawColorText(x_start, y_start + 1, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, " €    €  € € € € € € € €ﬂ€ € € € € €ﬂﬂ €ﬂ‹  €ﬂ‹ €ﬂﬂ €ﬂﬂ € € ");
    drawColorText(x_start, y_start + 2, TEXTCOLOR_YELLOW|BGCOLOR_BLACK, " ﬂ‹‹ﬂ ﬂ‹‹ﬂ € € € € € € € € € € €‹ﬂ ﬂ‹‹ € €  € € ﬂ‹‹ ﬂ‹‹ € € ");

    drawColorChar(x_start +  2, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    drawColorChar(x_start +  7, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 26, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLACK, '‹');
    // drawColorChar(x_start + 30, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLACK, '‹');
    drawColorChar(x_start + 36, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 38, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLACK, '‹');
    drawColorChar(x_start + 43, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLACK, '‹');
    drawColorChar(x_start + 45, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLACK, '‹');
    drawColorChar(x_start + 49, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    drawColorChar(x_start + 53, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 55, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLACK, '‹');
    drawOverlayText(x_start, y_start + 1, TEXTCOLOR_BROWN,                           "€  ﬂ €  € € € € € € € €   € € € € €   €    €   €   €   € € ");
    drawOverlayText(x_start, y_start + 2, TEXTCOLOR_BROWN,                           "€    €    € € € € € € € € € € €   €   € €  € € €   €   € € ");
    drawOverlayText(x_start, y_start + 3, TEXTCOLOR_BROWN|BGCOLOR_BLACK,             " ﬂﬂ   ﬂﬂ  ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂﬂ   ﬂﬂ ﬂ ﬂ  ﬂ ﬂ  ﬂﬂ  ﬂﬂ ﬂ ﬂ ");

    // drawColorChar(x_start +  2, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start +  7, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 26, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 30, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 36, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 38, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 43, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 45, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 49, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 53, y_start + 0, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    // drawColorChar(x_start + 55, y_start + 0, TEXTCOLOR_BROWN|BGCOLOR_BLUE, '‹');
    // drawOverlayText(x_start, y_start + 1, TEXTCOLOR_BROWN,             "€  ﬂ €  € € € € € € € €   € € € € €   €    €   €   €   € € ");
    // drawOverlayText(x_start, y_start + 2, TEXTCOLOR_BROWN,             "€    €    € € € € € € € € € € €   €   € €  € € €   €   € € ");
    // drawOverlayText(x_start, y_start + 3, TEXTCOLOR_BROWN|BGCOLOR_BLUE,             " ﬂﬂ   ﬂﬂ  ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂ ﬂﬂ   ﬂﬂ ﬂ ﬂ  ﬂ ﬂ  ﬂﬂ  ﬂﬂ ﬂ ﬂ ");
    drawColorChar(x_start + 24, y_start + 1, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    drawColorChar(x_start + 36, y_start + 1, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    drawColorChar(x_start + 49, y_start + 1, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');
    drawColorChar(x_start + 53, y_start + 1, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, 'ﬂ');

    drawColorChar(x_start + 8, y_start + 2, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, '‹');
    drawColorChar(x_start + 32, y_start + 2, TEXTCOLOR_YELLOW|BGCOLOR_BROWN, '‹');

    // drawHorizontalLine(y_start + 4, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, 'ƒ');


    drawRectangle(x_start, y_start + 5, 60, 2, BGCOLOR_PURPLE);
    drawColorText(x_start + 2, y_start + 4, TEXTCOLOR_WHITE|BGCOLOR_BLUE,   " ‹‹  ‹   ‹  ‹‹  ‹‹  ‹ ‹  ‹‹     ‹‹  ‹  ‹    ‹  ‹ ‹ ‹ ‹ ‹");
    drawColorText(x_start + 2, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, "€ ‹ € € € € € € €‹€ ﬂ‹ﬂ €‹     € ‹ €‹€ €   €‹€ ﬂ‹ﬂ ﬂ‹ﬂ €");
    drawColorText(x_start + 2, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, "ﬂ‹€ ﬂ‹ﬂ ﬂ‹ﬂ €‹ﬂ €‹ﬂ  €  ﬂ‹‹ ﬂ› ﬂ‹€ € € €‹‹ € € € €  €  ‹");

    drawColorText(x_start +  0, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, "ﬂﬂ");
    drawColorChar(x_start +  2, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start +  5, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start +  6, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start +  8, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start +  9, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 10, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 12, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 13, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 16, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 17, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 20, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 21, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 22, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 24, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 25, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 26, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 29, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 30, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 32, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 33, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 36, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 38, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 40, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 44, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 46, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 48, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 50, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 52, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 53, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 55, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorChar(x_start + 56, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');
    drawColorText(x_start + 58, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, "ﬂﬂ");
    // drawColorChar(x_start + 18, y_start + 6, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, 'ﬂ');

    // drawRectangle(x_start, y_start + 5, 60, 2, BGCOLOR_PURPLE);
    // drawColorText(x_start + 2, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, "‹ﬂﬂ ‹ﬂ‹ ‹ﬂ‹ €ﬂ‹ €ﬂ‹ € € ‹ﬂﬂ    ‹ﬂﬂ ‹ﬂ‹ €   ‹ﬂ‹ € € € € €");
    // drawColorText(x_start +  0, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, "‹‹");
    // drawColorChar(x_start +  2, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start +  5, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start +  6, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start +  8, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start +  9, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 10, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 12, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 13, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 16, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 17, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 20, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 21, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 23, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 25, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 26, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorText(x_start + 29, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, "‹‹‹‹");
    // drawColorChar(x_start + 33, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 36, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 37, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 39, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 40, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorText(x_start + 42, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, "‹‹‹");
    // drawColorChar(x_start + 45, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 47, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 48, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 50, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 52, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 54, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 56, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 58, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');
    // drawColorChar(x_start + 59, y_start + 5, TEXTCOLOR_PURPLE|BGCOLOR_BLUE, '‹');

    // // drawColorText(x_start + 2, y_start + 5, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, "‹ﬂﬂ ‹ﬂ‹ ‹ﬂ‹ €ﬂ‹ €ﬂ‹ € € ‹ﬂﬂ    ‹ﬂﬂ ‹ﬂ‹ €   ‹ﬂ‹ € € € € €");
    // drawColorText(x_start + 2, y_start + 6, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, "€ € € € € € € € €ﬂ€  €  €ﬂ     € € €ﬂ€ €   €ﬂ€ ‹ﬂ‹  €  ﬂ");
    // drawColorText(x_start + 2, y_start + 7, TEXTCOLOR_WHITE|BGCOLOR_BLUE,   " ﬂﬂ  ﬂ   ﬂ  ﬂﬂ  ﬂﬂ   ﬂ   ﬂﬂ ﬂ›  ﬂﬂ ﬂ ﬂ ﬂﬂﬂ ﬂ ﬂ ﬂ ﬂ  ﬂ  ﬂ");

}

static void drawBackgroundGradient() {
    setBackgroundColor(BGCOLOR_BLUE);
    drawVerticalLine( 0, TEXTCOLOR_BLUE, ' ');
    drawVerticalLine( 1, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine( 1, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine( 2, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine( 3, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine( 4, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine( 5, TEXTCOLOR_BLUE, '±');
    drawVerticalLine( 6, TEXTCOLOR_BLUE, '±');
    drawVerticalLine( 7, TEXTCOLOR_BLUE, '±');
    drawVerticalLine( 8, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine( 9, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine(10, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine(11, TEXTCOLOR_BLUE, '≤');

    drawVerticalLine(68, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine(69, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine(70, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine(71, TEXTCOLOR_BLUE, '≤');
    drawVerticalLine(72, TEXTCOLOR_BLUE, '±');
    drawVerticalLine(73, TEXTCOLOR_BLUE, '±');
    drawVerticalLine(74, TEXTCOLOR_BLUE, '±');
    drawVerticalLine(75, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine(76, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine(77, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine(78, TEXTCOLOR_BLUE, '∞');
    drawVerticalLine(79, TEXTCOLOR_BLUE, ' ');

}

static void drawSupportSelectionMarker() {
    drawColorChar(16, supportSelection == visibleSupportEntries ? 22 : 13 + supportSelection, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, animationState ? '\x07' : '\x09');
}

static void drawSupportMenu(bool updateSelectionOnly) {
    if (updateSelectionOnly) {
        for (int i = 0; i < visibleSupportEntries; ++i) {
            drawColorChar(16, 13 + i, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
        }
        drawColorChar(16, 22, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
        drawSupportSelectionMarker();
        return;
    }
    drawWindow(12, 12,  56, visibleSupportEntries + 2, TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, BORDER_DOUBLE);
    for (int i = 0; i < visibleSupportEntries; ++i) {
        drawColorChar(16, 13 + i, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
        drawTransText(18, 13 + i, TEXTCOLOR_WHITE, supportEntries[supportScroll + i].name);
    }
    drawColorChar(16, 22, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    drawTransText(18, 22, TEXTCOLOR_WHITE, "Back");
    drawSupportSelectionMarker();
    if (maxScroll) {
        drawColorChar(65, 13, supportScroll > 0 ? TEXTCOLOR_WHITE|BGCOLOR_PURPLE : TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, '\x18');
        drawColorChar(65, 12 + MAX_VISIBLE_INSTRUCTION_ITEMS, supportScroll < maxScroll ? TEXTCOLOR_WHITE|BGCOLOR_PURPLE : TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, '\x19');
    }
}

static void drawVideoModeSelectionMarker() {
    int yPos = 0;
    switch (videoSelection) {
        case 0:
            yPos = 17;
            break;
        case 1:
            yPos = 18;
            break;
        case 2:
            yPos = 22;
            break;
        default:
            break;
    }
    drawColorChar(16, yPos, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, animationState ? '\x07' : '\x09');
}

static void drawVideoModeMenu(bool updateSelectionOnly) {
    drawColorChar(16, 17, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    drawColorChar(16, 18, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    drawColorChar(16, 22, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    drawVideoModeSelectionMarker();
    if (updateSelectionOnly) return;

    bool cgaEnabled = selectedEpisode == 4 && ep4CgaFileName || selectedEpisode == 5 && ep5CgaFileName;
    bool egaEnabled = selectedEpisode == 4 && ep4EgaFileName || selectedEpisode == 5 && ep5EgaFileName;

    drawColorText(14, 13, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, selectedEpisode == 4 ? EPISODE4_TITLE : EPISODE5_TITLE);
    drawColorText(12, 14, TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, "«ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ∂");
    drawTransText(14, 15, TEXTCOLOR_WHITE, "Select a Video Mode");
    drawTransText(18, 17, cgaEnabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTPURPLE, "CGA");
    drawRightAlignedTransText(56, 17, 10, TEXTCOLOR_LIGHTPURPLE, "4 Colors");
    drawTransText(18, 18, egaEnabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTPURPLE, "EGA/VGA");
    drawRightAlignedTransText(56, 18, 10, TEXTCOLOR_LIGHTPURPLE, "16 Colors");
    drawTransText(18, 22, TEXTCOLOR_WHITE, "Back");
}

static void drawMainSelectionMarker() {
    int yPos = 0;
    if (showInstructions) {
        switch (mainSelection) {
            case 0:
                yPos = 15;
                break;
            case 1:
                yPos = 16;
                break;
            case 2:
                yPos = 18;
                break;
            case 3:
                yPos = 22;
                break;
            default:
                break;
        }
    } else {
        switch (mainSelection) {
            case 0:
                yPos = 15;
                break;
            case 1:
                yPos = 16;
                break;
            case 2:
                yPos = 22;
                break;
            default:
                break;
        }
    }
    drawColorChar(16, yPos, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, animationState ? '\x07' : '\x09');
}

void drawSelectionMarker() {
    if (activeMenu == MENU_MAIN) {
        drawMainSelectionMarker();
    } else if (activeMenu == MENU_VIDEOMODE) {
        drawVideoModeSelectionMarker();
    } else {
        drawSupportSelectionMarker();
    }
}

static void drawMainMenu(bool updateSelectionOnly) {
    drawColorChar(16, 15, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    drawColorChar(16, 16, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    if (showInstructions) {
        drawColorChar(16, 18, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    }
    drawColorChar(16, 22, TEXTCOLOR_WHITE|BGCOLOR_PURPLE, ' ');
    drawMainSelectionMarker();
    if (updateSelectionOnly) return;

    drawTransText(14, 13, TEXTCOLOR_WHITE, showInstructions ? "Make a Selection" : "Select An Episode");
    drawTransText(18, 15, ep4Enabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTPURPLE, EPISODE4_TITLE);
    drawTransText(18, 16, ep5Enabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTPURPLE, EPISODE5_TITLE);
    if (showInstructions) {
        drawTransText(18, 18, TEXTCOLOR_WHITE, "Instructions");
    }
    drawTransText(18, 22, TEXTCOLOR_WHITE, "Quit");
}

static void drawActiveWindow() {
    if (activeMenu == MENU_MAIN) {
        drawWindow(12, 12, 56, showInstructions ? 8 : 6, TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, BORDER_DOUBLE);
    } else if (activeMenu == MENU_VIDEOMODE) {
        drawWindow(12, 12, 56, 8, TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, BORDER_DOUBLE);
    } else {
        drawWindow(12, 12, 56, visibleSupportEntries + 2, TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, BORDER_DOUBLE);
    }
}

static void clearMenu() {
    drawRectangle(12, 11, 56, 10, BGCOLOR_BLUE);
    drawActiveWindow();
}

static void drawMenu(bool updateSelectionOnly) {
    if (activeMenu == MENU_MAIN) {
        drawMainMenu(updateSelectionOnly);
    } else if (activeMenu == MENU_VIDEOMODE) {
        drawVideoModeMenu(updateSelectionOnly);
    } else {
        drawSupportMenu(updateSelectionOnly);
    }
}


static void updateVideoModeConfig(int videoMode) {
    FILE* cfgFp = fopen(FILE_NAME_VIDEO_CONFIG, "w");
    if (cfgFp) {
        fputc(videoMode, cfgFp);
        fclose(cfgFp);
    }
}

static void showVideoModeError() {
    drawWindow(12, 12, 56, 8, TEXTCOLOR_YELLOW|BGCOLOR_RED, BORDER_DOUBLE);
    beep();
    drawCenterText(13, TEXTCOLOR_YELLOW|BGCOLOR_RED|TEXT_FLASHING, "ERROR! ERROR! ERROR!");
    drawColorText(14, 15, TEXTCOLOR_WHITE|BGCOLOR_RED, "Saved games or config files have been detected in");
    drawColorText(14, 16, TEXTCOLOR_WHITE|BGCOLOR_RED, "the current directory. These are incompatible across");
    drawColorText(14, 17, TEXTCOLOR_WHITE|BGCOLOR_RED, "video modes. Please move them to the appropriate");
    drawColorText(14, 18, TEXTCOLOR_WHITE|BGCOLOR_RED, "CGASAVE/EGASAVE directory and restart the launcher.");
    getPressedKey();
    clearMenu();
    drawMenu(false);
}

static bool configureVideoMode(int videoMode) {
    int currentMode = VIDEO_MODE_UNKNOWN;
    FILE* cfgFp = fopen(FILE_NAME_VIDEO_CONFIG, "r");
    if (cfgFp) {
        currentMode = fgetc(cfgFp);
        fclose(cfgFp);
        cfgFp = NULL;
    }
    if (currentMode == videoMode) return true;
    if (currentMode != VIDEO_MODE_CGA && currentMode != VIDEO_MODE_EGA && (fileExists("SAVEGAM?.CK?") || fileExists("CONFIG.CK4") || fileExists("CONFIG.CK5"))) {
        showVideoModeError();
        return false;
    }

    if (currentMode == VIDEO_MODE_EGA) {
        moveFiles(DIRECTORY_PREFIX_CURRENT, DIRECTORY_PREFIX_EGASAVE);
    } else if (currentMode == VIDEO_MODE_CGA) {
        moveFiles(DIRECTORY_PREFIX_CURRENT, DIRECTORY_PREFIX_CGASAVE);
    }

    if (videoMode == VIDEO_MODE_EGA) {
        moveFiles(DIRECTORY_PREFIX_EGASAVE, DIRECTORY_PREFIX_CURRENT);
    } else if (videoMode == VIDEO_MODE_CGA) {
        moveFiles(DIRECTORY_PREFIX_CGASAVE, DIRECTORY_PREFIX_CURRENT);
    }
    updateVideoModeConfig(videoMode);
    return true;
}

static const char* getDistributionString() {
    if (gameVersion == VERSION_14GT) {
        return DISTRIBUTE_GTS;
    } else if (gameVersion == VERSION_14FG || gameVersion == VERSION_DEMO) {
        return DISTRIBUTE_FGC;
    } else {
        return DISTRIBUTE_ASP;
    }
}

void drawMainLayout() {
    clearScreen();
    drawBackgroundGradient();
    drawLogo(10, 1);
    drawCenterText(9, TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLUE, gameVersion >= VERSION_14 ? COPYRIGHT_1992 : COPYRIGHT_1991);
    drawCenterText(10, TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLUE, getDistributionString());
    if (gameVersion == VERSION_DEMO) {
        drawCenterText(24, TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLUE, "SPECIAL DEMO VERSION 1.0");
    }
    drawActiveWindow();
    drawWindow(12, 21, 56, 3, TEXTCOLOR_LIGHTPURPLE|BGCOLOR_PURPLE, BORDER_DOUBLE);
    drawMenu(false);
    moveCaret(0, 24);
}

static int getPressedMenuKey() {
    int keycode = getPressedKey();
    bool match = true;
    pressedKeys[secretIndex] = keycode;
    secretIndex = (secretIndex + 1) % ARRAY_LENGTH(pressedKeys);
    for (int i = 0; i < ARRAY_LENGTH(pressedKeys); ++i) {
        if (SECRET_PATTERN[i] != pressedKeys[(secretIndex + i) % ARRAY_LENGTH(pressedKeys)]) {
            match = false;
            break;
        }
    }
    if (match) {
        clearScreen();
        showCaret(false);
        setRawData(0, 1, DOPEFISH_IMAGE, ARRAY_LENGTH(DOPEFISH_IMAGE));
        getPressedKey();
        drawMainLayout();
    }
    #ifndef RELEASE
    if (keycode == KEY_M) {
        showMemoryDebugInfo();
    }
    #endif
    return keycode;
}

#ifndef LOW_MEMORY
static void runMainExe(const char* path) {
    unsigned short errorCode = spawnve(P_WAIT, path, args, (const char**)environ);
    if (errorCode == -1) {
        cleanup();
        fprintf(stderr, EXEC_ERROR_F, path, strerror(errno));
    } else {
        // Extend end B800 screen to also cover last line, check that we actually got an end screen
        if (*((char far *)(0xb8000000 + 2)) == '∞') {
            if (gameVersion == VERSION_14GT) {
                for (int i = !strcmp(path, "KEEN4.EXE") ? 15 : 7; i <= 24; ++i) {
                    _hmemcpy((char far *)(0xb8000000 + 2 * 80 * i), (char far *)0xb8000000, 160);
                }
            }
            else {
                _hmemcpy((char far *)(0xb8000000 + 2 * 80 * 24), (char far *)0xb8000000, 160);
            }
            moveCaret(0, 24);
        }
        activeMenu = MENU_MAIN;
    }
    getPressedKey();
    drawMainLayout();
}
#endif

static void showText(const char* path, const char* title) {
    cleanup();
    showTextFile(path, title);
    drawMainLayout();
}

static void performModeSetup() {
    if (!directoryExists(DIRECTORY_NAME_EGASAVE)) {
        farmkdir(DIRECTORY_NAME_EGASAVE);
    }
    if (!directoryExists(DIRECTORY_NAME_CGASAVE)) {
        farmkdir(DIRECTORY_NAME_CGASAVE);
    }
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
        case KEY_ENTER:
            switch (menuEntries[mainSelection]) {
                case MAIN_ENTRY_EP4:
                    if (ep4Enabled) {
                        if (!cgaAndEgaExists) {
                            #ifdef LOW_MEMORY
                                exit(exitCodeForFileName(ep4EgaFileName ? ep4EgaFileName : ep4CgaFileName));
                            #else
                                runMainExe(ep4EgaFileName ? ep4EgaFileName : ep4CgaFileName);
                            #endif
                        } else {
                            performModeSetup();
                            videoSelection = 0;
                            selectedEpisode = 4;
                            activeMenu = MENU_VIDEOMODE;
                            clearMenu();
                            drawMenu(false);
                        }
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_EP5:
                    if (ep5Enabled) {
                        if (!cgaAndEgaExists) {
                            #ifdef LOW_MEMORY
                                exit(exitCodeForFileName(ep5EgaFileName ? ep5EgaFileName : ep5CgaFileName));
                            #else
                                runMainExe(ep5EgaFileName ? ep5EgaFileName : ep5CgaFileName);
                            #endif
                        } else {
                            performModeSetup();
                            videoSelection = 0;
                            selectedEpisode = 5;
                            activeMenu = MENU_VIDEOMODE;
                            clearMenu();
                            drawMenu(false);
                        }
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_INSTRUCTIONS:
                    supportScroll = 0;
                    supportSelection = 0;
                    activeMenu = MENU_SUPPORT;
                    clearMenu();
                    drawMenu(false);
                    break;
                case MAIN_ENTRY_QUIT:
                    return false;
                default:
                    break;
            }
            break;
        case KEY_ESCAPE:
            return false;
        default:
            break;
    }
    return true;
}

static bool handleVideoModeMenuInput() {
    int character = getPressedMenuKey();
    switch (character) {
        case KEY_ARROW_UP:
            videoSelection = (videoSelection - 1 + 3) % NUM_VIDEO_MODE_ENTRIES;
            drawMenu(true);
            break;
        case KEY_ARROW_DOWN:
            videoSelection = (videoSelection + 1) % NUM_VIDEO_MODE_ENTRIES;
            drawMenu(true);
            break;
        case KEY_ENTER:
            switch (videoSelection) {
                case VIDEO_MODE_ENTRY_CGA:
                    if (selectedEpisode == 4 ? ep4CgaFileName : ep5CgaFileName) {
                        if (configureVideoMode(VIDEO_MODE_CGA)) {
                            #ifdef LOW_MEMORY
                                exit(exitCodeForFileName(selectedEpisode == 4 ? ep4CgaFileName : ep5CgaFileName));
                            #else
                                runMainExe(selectedEpisode == 4 ? ep4CgaFileName : ep5CgaFileName);
                            #endif
                        }
                    } else {
                        beep();
                    }
                    break;
                case VIDEO_MODE_ENTRY_EGA:
                    if (selectedEpisode == 4 ? ep4EgaFileName : ep5EgaFileName) {
                        if (configureVideoMode(VIDEO_MODE_EGA)) {
                            #ifdef LOW_MEMORY
                                exit(exitCodeForFileName(selectedEpisode == 4 ? ep4EgaFileName : ep5EgaFileName));
                            #else
                                runMainExe(selectedEpisode == 4 ? ep4EgaFileName : ep5EgaFileName);
                            #endif
                        }
                    } else {
                        beep();
                    }
                    break;
                case VIDEO_MODE_ENTRY_BACK:
                    activeMenu = MENU_MAIN;
                    clearMenu();
                    drawMenu(false);
                    break;
                default:
                    break;
            }
            break;
        case KEY_ESCAPE:
            activeMenu = MENU_MAIN;
            clearMenu();
            drawMenu(false);
            break;
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
                activeMenu = MENU_MAIN;
                clearMenu();
                drawMenu(false);
                return true;
            }
            supportAction = supportEntries[supportSelection + supportScroll].actionId;
            if (supportAction < CUSTOM_SUPPORT_ACTION_START) {
                executeCommonSupportEntry(supportAction, APOGEE_GAME_TITLE_OLD, APOGEE_GAME_TITLE, versionString);
                return true;
            }
            switch (supportAction) {
                case CUSTOM_SUPPORT_ACTION_README:
                    if (readmeIdStyle) {
                        storeTextStyle();
                        setStyle(TEXTCOLOR_WHITE|BGCOLOR_BLACK, TEXTCOLOR_WHITE|BGCOLOR_BLUE, TEXT_LAYOUT_TRADITIONAL);
                    }
                    showText(FILE_NAME_README, readmeIdStyle ? ID_GAME_TITLE: APOGEE_GAME_TITLE_OLD);
                    if (readmeIdStyle) {
                        restoreTextStyle();
                    }
                    break;
                case CUSTOM_SUPPORT_ACTION_HINT_TXT:
                    showText(FILE_NAME_HINT_SHEET_TXT, "COMMANDER KEEN: GOODBYE, GALAXY! HINT SHEET");
                    break;
                default:
                    break;
            }
            break;
        case KEY_ESCAPE:
            activeMenu = MENU_MAIN;
            clearMenu();
            drawMenu(false);
            break;
        default:
            break;
    }
    return true;
}

static bool handleInput() {
    if (activeMenu == MENU_MAIN) {
        return handleMainMenuInput();
    } else if (activeMenu == MENU_VIDEOMODE) {
        return handleVideoModeMenuInput();
    } else {
        return handleSupportMenuInput();
    }
}

int main(int argc, const char *argv[]) {
    #ifdef LOW_MEMORY
        if (argc < 2) {
            printf("Run KEENGG.BAT instead!\n");
            return EXIT_SUCCESS;
        }
        switch (argv[1][0]) {
            case '1':
            case '2':
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

    long updateTime = getTime();
    bool running = true;
    while (running) {
        bool input = hasWaitingInput();
        if (input) {
            running = handleInput();
        } else {
            long currentTime = getTime();
            if (currentTime < updateTime || currentTime - updateTime > 200) {
                updateTime = currentTime;
                animationState = !animationState;
                drawSelectionMarker();
            }
        }
    }
    cleanup();
    return 0;
}
