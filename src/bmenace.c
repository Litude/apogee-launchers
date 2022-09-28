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
#include "lib/menu.h"
#include "lib/macro.h"
#include "lib/error.h"
#include "lib/memory.h"
#include "instruct/apogee.h"
#include "instruct/actions.h"
#include "version.h"

extern char **environ;
static char **args;

static const char* APOGEE_SHEET_PREFIX = "BM";
static const char* APOGEE_GAME_TITLE = "Bio Menace";

static const char* TXT_VERSION_11 = "v1.1";

static enum MAIN_ENTRY {
    MAIN_ENTRY_EP1,
    MAIN_ENTRY_EP2,
    MAIN_ENTRY_EP3,
    MAIN_ENTRY_INSTRUCTIONS,
    MAIN_ENTRY_QUIT,
    NUM_MAIN_ENTRIES,
};

static enum CUSTOM_SUPPORT_ACTIONS {
    CUSTOM_SUPPORT_ACTION_FREE_NOTE = CUSTOM_SUPPORT_ACTION_START,
    CUSTOM_SUPPORT_ACTION_BETA_DISCLAIMER,
    CUSTOM_SUPPORT_ACTION_BETA_NOTE,
    CUSTOM_SUPPORT_ACTION_BETA_PUBLIC_NOTE,
    CUSTOM_SUPPORT_ACTION_HELP_TXT,
    CUSTOM_SUPPORT_ACTION_HINT_TXT,
    NUM_TOTAL_SUPPORT_ACTIONS
};

static enum CUSTOM_SUPPORT_ENTIRES {
    CUSTOM_SUPPORT_ENTRY_FREE_NOTE,
    CUSTOM_SUPPORT_ENTRY_BETA_DISCLAIMER,
    CUSTOM_SUPPORT_ENTRY_BETA_NOTE,
    CUSTOM_SUPPORT_ENTRY_BETA_PUBLIC_NOTE,
};

static const char* CUSTOM_SUPPORT_ENTRY_NAMES[] = {
    "Freeware Release Notes",
    "Beta Disclaimer",
    "Beta Release Notes",
    "Beta Public Release Notes",
};

static const int SORT_ORDER[] = {
    CUSTOM_SUPPORT_ACTION_FREE_NOTE,
    CUSTOM_SUPPORT_ACTION_BETA_PUBLIC_NOTE,
    CUSTOM_SUPPORT_ACTION_BETA_DISCLAIMER,
    CUSTOM_SUPPORT_ACTION_BETA_NOTE,
    APOGEE_SUPPORT_ACTION_HELP,
    CUSTOM_SUPPORT_ACTION_HELP_TXT,
    APOGEE_SUPPORT_ACTION_HINT,
    CUSTOM_SUPPORT_ACTION_HINT_TXT,
};

static const char COPYRIGHT_STRING[] = "Copyright (c) 1993 - A game by Jim Norwood";
static const char COPYRIGHT_STRING_BETA[] = "Copyright (c) 1992  A Jim Norwood/Id Software Production";
static const char BETA_NOTE[] = "BETA VERSION -- DO NOT DISTRIBUTE !!";
static const char GMS_NOTE[] = "Distributed by Gold Medallion Software";
static const char BETA_PASSWORD[] = "slammer";

static const char* GAME_EXE_FILENAMES[] = {
    "BMENACE1.EXE",
    "BMENACE2.EXE",
    "BMENACE3.EXE",
    "BM1GM.EXE",
    "BM2GM.EXE",
    "BM3GM.EXE",
    "BHAZARD1.EXE",
    "BHAZARD2.EXE",
    "BHAZARD3.EXE",
};

static const int NUM_EXE_NAMES = ARRAY_LENGTH(GAME_EXE_FILENAMES);

static const char FILE_NAME_BETA_DISCLAIMER[] = "ORIGINAL\\README.TXT";
static const char FILE_NAME_BETA_DISCLAIMER_ALT[] = "README.TXT";
static const char FILE_NAME_BETA_NOTE[] = "ORIGINAL\\README2.TXT";
static const char FILE_NAME_BETA_NOTE_ALT[] = "README2.TXT";
static const char FILE_NAME_BETA_PUBLIC_NOTE[] = "RELEASE.TXT";

static const char FILE_NAME_FREEWARE_NOTE[] = "README.TXT";

static const char FILE_NAME_HELP_SHEET_TXT[] = "BM-HELP.TXT";
static const char FILE_NAME_HINT_SHEET_TXT[] = "BM-HINT.TXT";

static const char *betaDisclaimerFileName = FILE_NAME_BETA_DISCLAIMER;
static const char *betaNotesFileName = FILE_NAME_BETA_NOTE;
static const char *versionString = NULL;

static const char *ep1FileName = NULL;
static const char *ep2FileName = NULL;
static const char *ep3FileName = NULL;

#define BHAZARD_EP1_920715_SIZE 83840

#define BMENACE_EP1_V10S_SIZE 89160
#define BMENACE_EP1_V10R_SIZE 89270
#define BMENACE_EP2_V10R_SIZE 89245
#define BMENACE_EP3_V10R_SIZE 89062

#define BMENACE_EP1_V11S_SIZE 89166
#define BMENACE_EP1_V11R_SIZE 89274
#define BMENACE_EP2_V11R_SIZE 89231
#define BMENACE_EP3_V11R_SIZE 89048
#define BMENACE_EP1_V11F_SIZE 90046
#define BMENACE_EP2_V11F_SIZE 89921
#define BMENACE_EP3_V11F_SIZE 89754

#define BMENACE_EP1_GMSS_SIZE 90488

#define MAX_VISIBLE_INSTRUCTION_ITEMS 7

static enum GAME_VERSION {
    VERSION_UNKNOWN,
    VERSION_BETA,
    VERSION_10,
    VERSION_11,
    VERSION_11GMS,
};

static int mainSelection = 0;
static int supportSelection = 0;
static int supportScroll = 0;
static int maxScroll = 0;
static int visibleSupportEntries = 0;

static bool supportMenu = false;
static int gameVersion = VERSION_UNKNOWN;

static bool ep1Enabled = false;
static bool ep2Enabled = false;
static bool ep3Enabled = false;
static bool showInstructions = false;
static bool animationState = false;

static int menuEntries[NUM_MAIN_ENTRIES];
static menuEntry supportEntries[NUM_TOTAL_SUPPORT_ACTIONS];
static int validMenuEntries = 0;
static int validSupportEntries = 0;

static void detectGameExeTypes() {
    for (int i = 0; i < NUM_EXE_NAMES; ++i) {
        const char* filename = GAME_EXE_FILENAMES[i];
        long exeSize = fileSize(filename);
        if (exeSize != -1) {
            int episode = (i % 3) + 1;
            if (episode == 1) {
                switch (exeSize) {
                    case BHAZARD_EP1_920715_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_BETA);
                        break;
                    case BMENACE_EP1_V10R_SIZE:
                    case BMENACE_EP1_V10S_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_10);
                        break;
                    case BMENACE_EP1_V11S_SIZE:
                    case BMENACE_EP1_V11F_SIZE:
                    case BMENACE_EP1_V11R_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11);
                        break;
                    case BMENACE_EP1_GMSS_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11GMS);
                        break;
                    default:
                        break;
                }
                ep1Enabled = true;
                ep1FileName = filename;
            } else if (episode == 2) {
                switch (exeSize) {
                    case BMENACE_EP2_V10R_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_10);
                        break;
                    case BMENACE_EP2_V11F_SIZE:
                    case BMENACE_EP2_V11R_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11);
                        break;
                    default:
                        break;
                }
                ep2Enabled = true;
                ep2FileName = filename;
            } else if (episode == 3) {
                switch (exeSize) {
                    case BMENACE_EP3_V10R_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_10);
                        break;
                    case BMENACE_EP3_V11F_SIZE:
                    case BMENACE_EP3_V11R_SIZE:
                        gameVersion = MAX(gameVersion, VERSION_11);
                        break;
                    default:
                        break;
                }
                ep3Enabled = true;
                ep3FileName = filename;
            }
        }
    }
}

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
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP1;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP2;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP3;

    if (gameVersion == VERSION_BETA) {
        if (fileExists(FILE_NAME_BETA_PUBLIC_NOTE)) {
            supportEntries[validSupportEntries].name = CUSTOM_SUPPORT_ENTRY_NAMES[CUSTOM_SUPPORT_ENTRY_BETA_PUBLIC_NOTE];
            supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BETA_PUBLIC_NOTE;
            supportEntries[validSupportEntries].hotkey = 0;
            ++validSupportEntries;
        }
        if (fileExists(FILE_NAME_BETA_DISCLAIMER)) {
            supportEntries[validSupportEntries].name = CUSTOM_SUPPORT_ENTRY_NAMES[CUSTOM_SUPPORT_ENTRY_BETA_DISCLAIMER];
            supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BETA_DISCLAIMER;
            supportEntries[validSupportEntries].hotkey = 0;
            ++validSupportEntries;
            betaDisclaimerFileName = FILE_NAME_BETA_DISCLAIMER;
        } else if (fileExists(FILE_NAME_BETA_DISCLAIMER_ALT)) {
            supportEntries[validSupportEntries].name = CUSTOM_SUPPORT_ENTRY_NAMES[CUSTOM_SUPPORT_ENTRY_BETA_DISCLAIMER];
            supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BETA_DISCLAIMER;
            supportEntries[validSupportEntries].hotkey = 0;
            ++validSupportEntries;
            betaDisclaimerFileName = FILE_NAME_BETA_DISCLAIMER_ALT;
        }

        if (fileExists(FILE_NAME_BETA_NOTE)) {
            supportEntries[validSupportEntries].name = CUSTOM_SUPPORT_ENTRY_NAMES[CUSTOM_SUPPORT_ENTRY_BETA_NOTE];
            supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BETA_NOTE;
            supportEntries[validSupportEntries].hotkey = 0;
            ++validSupportEntries;
            betaNotesFileName = FILE_NAME_BETA_NOTE;
        } else if (fileExists(FILE_NAME_BETA_NOTE_ALT)) {
            supportEntries[validSupportEntries].name = CUSTOM_SUPPORT_ENTRY_NAMES[CUSTOM_SUPPORT_ENTRY_BETA_NOTE];
            supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_BETA_NOTE;
            supportEntries[validSupportEntries].hotkey = 0;
            ++validSupportEntries;
            betaNotesFileName = FILE_NAME_BETA_NOTE_ALT;
        }

    } else {
        if (fileExists(FILE_NAME_FREEWARE_NOTE)) { //TODO: Also version check?
            supportEntries[validSupportEntries].name = CUSTOM_SUPPORT_ENTRY_NAMES[CUSTOM_SUPPORT_ENTRY_FREE_NOTE];
            supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_FREE_NOTE;
            supportEntries[validSupportEntries].hotkey = 0;
            ++validSupportEntries;
        }
    }

    validSupportEntries += populateApogeeSupportEntries(&supportEntries[validSupportEntries], APOGEE_SHEET_PREFIX, 1 << APOGEE_SUPPORT_ACTION_INSTALL_HELP);

    if (fileExists(FILE_NAME_HELP_SHEET_TXT) && !findSupportEntry(APOGEE_SUPPORT_ACTION_HELP)) {
        supportEntries[validSupportEntries].name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_HELP];
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_HELP_TXT;
        supportEntries[validSupportEntries].hotkey = 0;
        ++validSupportEntries;
    }
    if (fileExists(FILE_NAME_HINT_SHEET_TXT) && !findSupportEntry(APOGEE_SUPPORT_ACTION_HINT)) {
        supportEntries[validSupportEntries].name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_HINT];
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_HINT_TXT;
        supportEntries[validSupportEntries].hotkey = 0;
        ++validSupportEntries;
    }

    sortSupportEntries();

    if (validSupportEntries > 1) {
        showInstructions = true;
        menuEntries[validMenuEntries++] = MAIN_ENTRY_INSTRUCTIONS;
    }
    menuEntries[validMenuEntries++] = MAIN_ENTRY_QUIT;

    maxScroll = validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? validSupportEntries - MAX_VISIBLE_INSTRUCTION_ITEMS : 0;
    visibleSupportEntries = (validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? MAX_VISIBLE_INSTRUCTION_ITEMS : validSupportEntries);
}

static void drawLogo(short y_start) {
    drawCenterTextLine(y_start + 0, TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLACK, "A P O G E E   S O F T W A R E   P R E S E N T S:");

    if (gameVersion == VERSION_BETA) {
        drawRawText(0, y_start + 1, " ÚÄÄÄÄÄ¿  ÚÄ¿ ÚÄÄÄÄÄÄ¿    ÚÄ¿  ÚÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄ¿  ");
        drawRawText(0, y_start + 2, " ÀÄÄÄÄÄÙ  ÀÄÙ ÀÄÄÄÄÄÄÙ    ÀÄÙ  ÀÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÙ  ");
        drawRawText(0, y_start + 3, " ÚÄÄÄÄÄÄ¿ ÚÄ¿ ÚÄ¿  ÚÄ¿    ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿   ÚÄÄ¿   ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄ¿  ÚÄ¿ ");
        drawRawText(0, y_start + 4, " ³ ÚÄÄ¿ ³ ³ ³ ³ ³  ³ ³    ³ ÚÄÄ¿ ³ ³ ÚÄÄ¿ ³ ÚÄÙÚÄÙ   ³ ÚÄÄ¿ ³ ³ ÚÄ¿ ÚÙ ³ ³  ³ ³ ");
        drawRawText(0, y_start + 5, " ³ ÀÄÄÙ ³ ³ ³ ³ ÀÄÄÙ ³    ³ ³  ³ ³ ³ ³  ³ ³ ³  ÀÄÄÄ¿ ³ ³  ³ ³ ³ ³ ³ ³  ³ ÀÄÄÙ ³ ");
        drawRawText(0, y_start + 6, " ÀÄÄÄÄÄÄÙ ÀÄÙ ÀÄÄÄÄÄÄÙ    ÀÄÙ  ÀÄÙ ÀÄÙ  ÀÄÙ ÀÄÄÄÄÄÄÙ ÀÄÙ  ÀÄÙ ÀÄÙ ÀÄÙ  ÀÄÄÄÄÄÄÙ ");

        //                                              'B'                            'I'                         'O'                         ' '                         'H'                                   'A'                                   'Z'                                    'A'                                 'R'                                        'D'
        setRawColorData(0, y_start + 1, "\x07\x09\x01\x01\x01\x01\x09\x0F\x07" "\x07\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x07\x07" "\x07\x09\x09\x0F\x07\x07\x09\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x09\x0F\x07" "\x07");
        setRawColorData(0, y_start + 2, "\x07\x0F\x09\x01\x01\x01\x01\x09\x07" "\x07\x0F\x09\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x07\x07" "\x07\x0F\x09\x09\x07\x07\x0F\x09\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x09\x07" "\x07");
        setRawColorData(0, y_start + 3, "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x01\x09\x0F" "\x07\x01\x09\x0F\x07\x07\x01\x09\x0F" "\x07\x07\x07" "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x07\x07\x01\x01\x09\x0F\x07\x07" "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x01\x09\x0F\x07\x07\x01\x09\x0F" "\x07");
        setRawColorData(0, y_start + 4, "\x07\x01\x07\x01\x01\x01\x01\x07\x09" "\x07\x01\x07\x09" "\x07\x01\x07\x09\x07\x07\x01\x07\x09" "\x07\x07\x07" "\x07\x01\x07\x01\x01\x01\x01\x07\x09" "\x07\x01\x07\x01\x01\x01\x01\x07\x09" "\x07\x01\x01\x01\x09\x01\x09\x07\x07" "\x07\x01\x07\x01\x01\x01\x01\x07\x09" "\x07\x01\x07\x01\x01\x01\x07\x01\x09" "\x07\x01\x07\x09\x07\x07\x01\x07\x09" "\x07");
        setRawColorData(0, y_start + 5, "\x07\x09\x07\x01\x01\x01\x01\x07\x01" "\x07\x09\x07\x01" "\x07\x09\x07\x01\x01\x01\x01\x07\x01" "\x07\x07\x07" "\x07\x09\x07\x01\x07\x07\x09\x07\x01" "\x07\x09\x07\x01\x07\x07\x09\x07\x01" "\x07\x09\x07\x07\x0F\x09\x01\x09\x0F" "\x07\x09\x07\x01\x07\x07\x09\x07\x01" "\x07\x09\x07\x01\x07\x09\x07\x01\x07" "\x07\x09\x07\x01\x01\x01\x01\x07\x01" "\x07");
        setRawColorData(0, y_start + 6, "\x07\x0F\x09\x01\x01\x01\x01\x01\x01" "\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x01\x01\x01\x01\x01" "\x07\x07\x07" "\x07\x0F\x09\x01\x07\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x07\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x07\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x07\x0F\x09\x01\x07" "\x07\x0F\x09\x01\x01\x01\x01\x01\x01" "\x07");
    } else {
        drawRawText(0, y_start + 1, " ÚÄÄÄÄÄ¿  ÚÄ¿ ÚÄÄÄÄÄÄ¿    ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄ¿  ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄÄÄÄÄÄ¿ ");
        drawRawText(0, y_start + 2, " ÀÄÄÄÄÄÙ  ÀÄÙ ÀÄÄÄÄÄÄÙ    ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ");
        drawRawText(0, y_start + 3, " ÚÄÄÄÄÄÄ¿ ÚÄ¿ ÚÄ¿  ÚÄ¿    ÚÄ¿Ú¿ÚÄ¿ ÚÄÄÄÄ¿   ÚÄ¿  ÚÄ¿ ÚÄÄÄÄÄÄ¿ ÚÄ¿      ÚÄÄÄÄ¿   ");
        drawRawText(0, y_start + 4, " ³ ÚÄÄ¿ ³ ³ ³ ³ ³  ³ ³    ³ ³ÀÙ³ ³ ³ ÚÄÄÙ   ³ ³  ³ ³ ³ ÚÄÄ¿ ³ ³ ³      ³ ÚÄÄÙ   ");
        drawRawText(0, y_start + 5, " ³ ÀÄÄÙ ³ ³ ³ ³ ÀÄÄÙ ³    ³ ³  ³ ³ ³ ÀÄÄÄÄ¿ ³ ³  ³ ³ ³ ³  ³ ³ ³ ÀÄÄÄÄ¿ ³ ÀÄÄÄÄ¿ ");
        drawRawText(0, y_start + 6, " ÀÄÄÄÄÄÄÙ ÀÄÙ ÀÄÄÄÄÄÄÙ    ÀÄÙ  ÀÄÙ ÀÄÄÄÄÄÄÙ ÀÄÙ  ÀÄÙ ÀÄÙ  ÀÄÙ ÀÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÙ ");

        //                                              'B'                            'I'                         'O'                         ' '                         'M'                                   'E'                                   'N'                                    'A'                                 'C'                                        'E'
        setRawColorData(0, y_start + 1, "\x07\x09\x01\x01\x01\x01\x09\x0F\x07" "\x07\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x07\x07" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x09\x0F\x07" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07\x09\x01\x01\x01\x01\x01\x09\x0F" "\x07");
        setRawColorData(0, y_start + 2, "\x07\x0F\x09\x01\x01\x01\x01\x09\x07" "\x07\x0F\x09\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x07\x07" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x09\x07" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07");
        setRawColorData(0, y_start + 3, "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x01\x09\x0F" "\x07\x01\x09\x0F\x07\x07\x01\x09\x0F" "\x07\x07\x07" "\x07\x01\x09\x0F\x09\x0F\x01\x09\x0F" "\x07\x01\x01\x01\x01\x09\x0F\x07\x07" "\x07\x01\x09\x0F\x07\x07\x01\x09\x0F" "\x07\x01\x01\x01\x01\x01\x01\x09\x0F" "\x07\x01\x09\x0F\x07\x07\x07\x07\x07" "\x07\x01\x01\x01\x01\x09\x0F\x07\x07" "\x07");
        setRawColorData(0, y_start + 4, "\x07\x01\x07\x01\x01\x01\x01\x07\x09" "\x07\x01\x07\x09" "\x07\x01\x07\x09\x07\x07\x01\x07\x09" "\x07\x07\x07" "\x07\x01\x07\x09\x0F\x09\x01\x07\x09" "\x07\x01\x07\x01\x01\x01\x09\x07\x07" "\x07\x01\x07\x09\x07\x07\x01\x07\x09" "\x07\x01\x07\x01\x01\x01\x01\x07\x09" "\x07\x01\x07\x09\x07\x07\x07\x07\x07" "\x07\x01\x07\x01\x01\x01\x09\x07\x07" "\x07");
        setRawColorData(0, y_start + 5, "\x07\x09\x07\x01\x01\x01\x01\x07\x01" "\x07\x09\x07\x01" "\x07\x09\x07\x01\x01\x01\x01\x07\x01" "\x07\x07\x07" "\x07\x09\x07\x01\x07\x07\x09\x07\x01" "\x07\x09\x07\x01\x01\x01\x01\x09\x0F" "\x07\x09\x07\x01\x07\x07\x09\x07\x01" "\x07\x09\x07\x01\x07\x07\x09\x07\x01" "\x07\x09\x07\x01\x01\x01\x01\x09\x0F" "\x07\x09\x07\x01\x01\x01\x01\x09\x0F" "\x07");
        setRawColorData(0, y_start + 6, "\x07\x0F\x09\x01\x01\x01\x01\x01\x01" "\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x01\x01\x01\x01\x01" "\x07\x07\x07" "\x07\x0F\x09\x01\x07\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x07\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x07\x07\x0F\x09\x01" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07\x0F\x09\x01\x01\x01\x01\x01\x09" "\x07");
    }


}

static void drawBackgroundGradient(short y_start) {
    drawHorizontalLine(y_start +  0, TEXTCOLOR_BLUE, '°');
    drawHorizontalLine(y_start +  1, TEXTCOLOR_BLUE, '±');
    drawHorizontalLine(y_start +  2, TEXTCOLOR_BLUE, '²');
    drawHorizontalLine(y_start +  3, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLUE, '°');
    drawHorizontalLine(y_start +  4, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLUE, '±');
    drawHorizontalLine(y_start +  5, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLUE, '²');
    drawHorizontalLine(y_start +  6, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLUE, '±');
    drawHorizontalLine(y_start +  7, TEXTCOLOR_LIGHTBLUE|BGCOLOR_BLUE, '°');
    drawHorizontalLine(y_start +  8, TEXTCOLOR_BLUE, '²');
    drawHorizontalLine(y_start +  9, TEXTCOLOR_BLUE, '±');
    drawHorizontalLine(y_start + 10, TEXTCOLOR_BLUE, '°');
}

static inline int getSupportMenuStartY() {
    return 11 - ((visibleSupportEntries | 0x1) >> 1);
}

static void drawSupportSelectionMarker() {
    drawColorChar(16, supportSelection == visibleSupportEntries ? 20 : getSupportMenuStartY() + 1 + supportSelection, TEXTCOLOR_WHITE|BGCOLOR_CYAN, animationState ? '\x07' : '\x09');
}

static void drawSupportMenu(bool updateSelectionOnly) {
    int startY = getSupportMenuStartY();
    if (updateSelectionOnly) {
        for (int i = 0; i < visibleSupportEntries; ++i) {
            drawColorChar(16, startY + 1 + i, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
        }
        drawColorChar(16, 20, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
        drawSupportSelectionMarker();
        return;
    }
    drawWindow(12, getSupportMenuStartY(),  56, (visibleSupportEntries | 0x1) + 2, TEXTCOLOR_LIGHTCYAN|BGCOLOR_CYAN, 0);
    for (int i = 0; i < visibleSupportEntries; ++i) {
        drawColorChar(16, startY + 1 + i, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
        drawTransText(18, startY + 1 + i, TEXTCOLOR_WHITE, supportEntries[supportScroll + i].name);
    }
    drawColorChar(16, 20, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
    drawTransText(18, 20, TEXTCOLOR_WHITE, "Back");
    drawSupportSelectionMarker();
    if (maxScroll) {
        drawColorChar(65, startY + 1, supportScroll > 0 ? TEXTCOLOR_WHITE|BGCOLOR_CYAN : TEXTCOLOR_LIGHTCYAN|BGCOLOR_CYAN, '\x18');
        drawColorChar(65, startY + MAX_VISIBLE_INSTRUCTION_ITEMS, supportScroll < maxScroll ? TEXTCOLOR_WHITE|BGCOLOR_CYAN : TEXTCOLOR_LIGHTCYAN|BGCOLOR_CYAN, '\x19');
    }
}

static void drawMainSelectionMarker() {
    int yPos = 0;
    if (showInstructions) {
        switch (mainSelection) {
            case 0:
                yPos = 11;
                break;
            case 1:
                yPos = 12;
                break;
            case 2:
                yPos = 13;
                break;
            case 3:
                yPos = 15;
                break;
            case 4:
                yPos = 20;
                break;
            default:
                break;
        }
    } else {
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
                yPos = 20;
                break;
            default:
                break;
        }
    }
    drawColorChar(16, yPos, TEXTCOLOR_WHITE|BGCOLOR_CYAN, animationState ? '\x07' : '\x09');
}

void drawSelectionMarker() {
    supportMenu ? drawSupportSelectionMarker() : drawMainSelectionMarker();
}

static void drawMainMenu(bool updateSelectionOnly) {
    int episodeOffset = showInstructions ? 0 : 1;
    drawColorChar(16, 11 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
    drawColorChar(16, 12 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
    drawColorChar(16, 13 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
    if (showInstructions) {
        drawColorChar(16, 15, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
    }
    drawColorChar(16, 20, TEXTCOLOR_WHITE|BGCOLOR_CYAN, ' ');
    drawMainSelectionMarker();
    if (updateSelectionOnly) return;

    drawTransText(14, showInstructions ? 9 : 10, TEXTCOLOR_WHITE, showInstructions ? "Make a Selection" : "Select An Episode");
    drawTransText(18, 11 + episodeOffset, ep1Enabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTCYAN, "Episode 1: Dr. Mangle's Lab");
    drawTransText(18, 12 + episodeOffset, ep2Enabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTCYAN, gameVersion == VERSION_BETA ? "Episode 2: The Black Forest" : "Episode 2: The Hidden Lab");
    drawTransText(18, 13 + episodeOffset, ep3Enabled ? TEXTCOLOR_WHITE : TEXTCOLOR_LIGHTCYAN, gameVersion == VERSION_BETA ? "Episode 3: The Final Fortress" : "Episode 3: Master Cain");
    if (showInstructions) {
        drawTransText(18, 15, TEXTCOLOR_WHITE, "Instructions");
    }
    drawTransText(18, 20, TEXTCOLOR_WHITE, "Quit");
}

static void drawActiveWindow() {
    supportMenu ?
        drawWindow(12, getSupportMenuStartY(),  56, (visibleSupportEntries | 0x1) + 2, TEXTCOLOR_LIGHTCYAN|BGCOLOR_CYAN, 0)
        :
        drawWindow(12, showInstructions ? 8 : 9, 56, showInstructions ? 9 : 7, TEXTCOLOR_LIGHTCYAN|BGCOLOR_CYAN, 0);
}

static void clearMenu() {
    drawBackgroundGradient(7);
    drawActiveWindow();
}

static void drawMenu(bool updateSelectionOnly) {
    supportMenu ? drawSupportMenu(updateSelectionOnly) : drawMainMenu(updateSelectionOnly);
}

void drawMainLayout() {
    clearScreen();
    showCaret(false);
    drawLogo(0);
    drawCenterTextLine(23, TEXTCOLOR_WHITE|BGCOLOR_BLACK, gameVersion == VERSION_BETA ? COPYRIGHT_STRING_BETA : COPYRIGHT_STRING);
    if (gameVersion == VERSION_BETA) {
        drawCenterTextLine(24, TEXTCOLOR_LIGHTRED|TEXT_FLASHING|BGCOLOR_BLACK, BETA_NOTE);
    } else if (gameVersion == VERSION_11GMS) {
        drawCenterTextLine(24, TEXTCOLOR_GRAY|BGCOLOR_BLACK, GMS_NOTE);
    }
    drawBackgroundGradient(7);
    drawActiveWindow();
    drawWindow(12, 19, 56, 3, TEXTCOLOR_LIGHTCYAN|BGCOLOR_CYAN, 0);
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
    unsigned short errorCode = spawnve(P_WAIT, path, (const char**)args, (const char**)environ);
    if (errorCode == -1) {
        cleanup();
        fprintf(stderr, EXEC_ERROR_MSG_F, path, strerror(errno));
    } else {
        // Extend end B800 screen to cover the whole screen, check that we actually got an end screen
        if ((*((char far *)0xb8000000) == '\xDD' || *((char far *)0xb8000000) == '\xB0') && *(char far *)(0xb8000000 + 2 * 80 * 24) == ' ') {
            scrollWindowDown(1);
            _hmemcpy((char far *)(0xb8000000), (char far *)(0xb8000000 + 2 * 80), 160);
            // The pattern is actually slightly different for the last line in ep 2 and 3, so copy from there instead
            _hmemcpy((char far *)(0xb8000000 + 2 * 80 * 24), (char far *)(0xb8000000 + 2 * 80 * 23), 160);
            showCaret(false);
        }
    }
    getPressedKey();
    drawMainLayout();
}
#endif

static void runBetaMainExe(const char* path) {
    char const *newArgs[3];
    char const **argp = newArgs; //, **arg = (const char**)args;
    // The beta does not start if given any excess arguments, so don't copy them
    *argp = path;
    ++argp;
    *argp = BETA_PASSWORD;
    ++argp;
    *argp = NULL;
    unsigned short errorCode = spawnve(P_WAIT, path, (const char**)newArgs, (const char**)environ);
    if (errorCode == -1) {
        cleanup();
        fprintf(stderr, EXEC_ERROR_MSG_F, path, strerror(errno));
        getPressedKey();
    } else if (errorCode) {
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
            drawMenu(true);
            break;
        case KEY_ARROW_DOWN:
            mainSelection = (mainSelection + 1) % validMenuEntries;
            drawMenu(true);
            break;
        case KEY_ENTER:
            switch (menuEntries[mainSelection]) {
                case MAIN_ENTRY_EP1:
                    if (ep1Enabled) {
                        #ifdef LOW_MEMORY
                            exit(1);
                        #else
                            if (gameVersion == VERSION_BETA) {
                                runBetaMainExe(ep1FileName);
                            } else {
                                runMainExe(ep1FileName);
                            }
                        #endif
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_EP2:
                    if (ep2Enabled) {
                        #ifdef LOW_MEMORY
                            exit(2);
                        #else
                            if (gameVersion == VERSION_BETA) {
                                runBetaMainExe(ep2FileName);
                            } else {
                                runMainExe(ep2FileName);
                            }
                        #endif
                    } else {
                        beep();
                    }
                    break;
                case MAIN_ENTRY_EP3:
                    if (ep3Enabled) {
                        #ifdef LOW_MEMORY
                            exit(3);
                        #else
                            if (gameVersion == VERSION_BETA) {
                                runBetaMainExe(ep3FileName);
                            } else {
                                runMainExe(ep3FileName);
                            }
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
                executeCommonSupportEntry(supportAction, APOGEE_GAME_TITLE, APOGEE_GAME_TITLE, versionString);
                return true;
            }
            switch (supportAction) {
                case CUSTOM_SUPPORT_ACTION_HELP_TXT:
                    showText(FILE_NAME_HELP_SHEET_TXT, "The Bio Menace Freeware Release On-Disk Technical Assistance File");
                    break;
                case CUSTOM_SUPPORT_ACTION_HINT_TXT:
                    showText(FILE_NAME_HINT_SHEET_TXT, "The Bio Menace Freeware Release On-Disk Hint Sheet");
                    break;
                case CUSTOM_SUPPORT_ACTION_FREE_NOTE:
                    showText(FILE_NAME_FREEWARE_NOTE, "The Bio Menace Freeware Release Notes");
                    break;
                case CUSTOM_SUPPORT_ACTION_BETA_DISCLAIMER:
                    showText(betaDisclaimerFileName, "The Bio-Hazard Beta Disclaimer");
                    break;
                case CUSTOM_SUPPORT_ACTION_BETA_NOTE:
                    showText(betaNotesFileName, "The Bio-Hazard Beta Release Notes");
                    break;
                case CUSTOM_SUPPORT_ACTION_BETA_PUBLIC_NOTE:
                    showText(FILE_NAME_BETA_PUBLIC_NOTE, "The Bio Menace Public Beta Release Notes");
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
        default:
            break;
    }
    return true;
}

int main(int argc, char *argv[]) {
    #ifdef LOW_MEMORY
        if (argc < 2) {
            printf("Run BMENACE.BAT instead!\n");
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
    while (running) {
        bool input = hasWaitingInput();
        if (input) {
            running = supportMenu ? handleSupportMenuInput() : handleMainMenuInput();
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
