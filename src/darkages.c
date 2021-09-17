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
#include "instruct/actions.h"
#include "version.h"

extern char **environ;
static char **args;

static const char* APOGEE_SHEET_PREFIX = "DA";
static const char* APOGEE_GAME_TITLE = "Dark Ages";
static const char* APOGEE_GAME_TITLE_CAPS = "DARK AGES";

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
    CUSTOM_SUPPORT_ACTION_COPYRIGHT,
    CUSTOM_SUPPORT_ACTION_FREE_NOTE,
    NUM_TOTAL_SUPPORT_ACTIONS
};

static const char ENTRY_README_NAME[] = "Readme";
static const char ENTRY_COPYRIGHT_NAME[] = "Copyright Notice";
static const char ENTRY_FREE_NOTE_NAME[] = "Freeware Release Notes";

static const char EP1_STRING[] = "Prince of Destiny";
static const char EP2_STRING[] = "The Undead Kingdom";
static const char EP3_STRING[] = "Dungeons of Doom";

static const char* GAME_EXE_FILENAMES[] = {
    "DA1.EXE",
    "DA2.EXE",
    "DA3.EXE",
};

static const int NUM_EXE_NAMES = ARRAY_LENGTH(GAME_EXE_FILENAMES);

static const char FILE_NAME_README[] = "DA1.DOC";
static const char FILE_NAME_COPYRIGHT[] = "COPYRITE.TXT";
static const char FILE_NAME_FREE_NOTE[] = "README.TXT";

static int ANIMATION_STATES[] = {
    TEXTCOLOR_WHITE|BGCOLOR_RED,
    TEXTCOLOR_WHITE|BGCOLOR_RED,
    TEXTCOLOR_WHITE|BGCOLOR_RED,
    TEXTCOLOR_GRAY|BGCOLOR_RED,
    TEXTCOLOR_DARKGRAY|BGCOLOR_RED,
    TEXTCOLOR_GRAY|BGCOLOR_RED,
    TEXTCOLOR_WHITE|BGCOLOR_RED,
    TEXTCOLOR_WHITE|BGCOLOR_RED
};

#define MAX_VISIBLE_INSTRUCTION_ITEMS 7

static int mainSelection = 0;
static int supportSelection = 0;
static bool supportMenu = false;
static int supportScroll = 0;
static int maxScroll = 0;
static int visibleSupportEntries = 0;

static bool ep1Enabled = false;
static bool ep2Enabled = false;
static bool ep3Enabled = false;
static bool showInstructions = false;
static unsigned int animationState = 0;

static int menuEntries[NUM_MAIN_ENTRIES];
static menuEntry supportEntries[NUM_TOTAL_SUPPORT_ACTIONS];
static int validMenuEntries = 0;
static int validSupportEntries = 0;

unsigned char DA_LOGO[] = {
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  'ß', 0x0E,  'Ü', 0x0E,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  'Ü', 0x0E,
    'ß', 0x0E,  'ß', 0x6E,  'Ü', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x06,  ' ', 0x06,  'Ü', 0x0E,  'Ü', 0x0E,
    'Ü', 0x0E,  'Û', 0x0E,  'Û', 0x0E,  'Û', 0x0E,  'Û', 0x0E,  'Û', 0x0E, 'Û', 0x0E,  'Û', 0x0E,  'Ü', 0x0E,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, 'Û', 0x0E,  'Ü', 0x06,  'ß', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    'Û', 0x0E,  'Ü', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x06,  'Û', 0x0E, 'ß', 0x6E,  'Û', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x06,
    'Û', 0x0E,  'Û', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x0E, 'Û', 0x0E,  'Ü', 0x0E,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  'Û', 0x0E,  'Ü', 0x06,  'Û', 0x0E,  'Ü', 0x06,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x06,  ' ', 0x06,  'ß', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  'ß', 0x06,  'Û', 0x0E,  'Ü', 0x06, ' ', 0x06,  ' ', 0x06,  'Ü', 0x0E,  'Ü', 0x0E,  'Ü', 0x0E,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, 'Ü', 0x0E,  'Ü', 0x0E,  ' ', 0x0E,  ' ', 0x0E,  'Û', 0x0E,  'Û', 0x06,
    'Ü', 0x0E,  'Û', 0x0E,  'ß', 0x6E,  'Ü', 0x06,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  'Ü', 0x0E,  'Û', 0x0E,  'Ü', 0x06,  'ß', 0x06,  'Û', 0x0E, 'Ü', 0x6E,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  'Ü', 0x0E,  'Ü', 0x0E,  ' ', 0x0E,  ' ', 0x0E,  ' ', 0x0E, ' ', 0x0E,  'Ü', 0x0E,  'Ü', 0x0E,  'Ü', 0x0E,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  'Ü', 0x0E,  'Ü', 0x0E,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  'Û', 0x0E,  'Û', 0x06, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    'Û', 0x0E,  'Û', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Ü', 0x06,  'ß', 0x06, 'ß', 0x06,  'Û', 0x0E,  'Ü', 0x06,  ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,
    'Ü', 0x0E,  'ß', 0x0E,  'Ü', 0x06,  'ß', 0x06,  'ß', 0x06,  ' ', 0x06, 'Û', 0x0E,  'Û', 0x0E,  'Ü', 0x06,  'ß', 0x06,  'ß', 0x06,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  'ß', 0x0E, 'Ü', 0x0E,  'Ü', 0x0E,  'Û', 0x0E,  'ß', 0x6E,  'Û', 0x06,  'ß', 0x06,
    ' ', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06,  ' ', 0x06, ' ', 0x06,  'Ü', 0x0E,  'ß', 0x0E,  'Ü', 0x06,  'ß', 0x06,  'Û', 0x0E,
    'Ü', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Ü', 0x06,  'ß', 0x06,  'Ü', 0x6E, 'Û', 0x0E,  'Ü', 0x06,  ' ', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Ü', 0x0E,
    'ß', 0x06,  'ß', 0x0E,  'Ü', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    'Û', 0x0E,  'Û', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06,  'Û', 0x0E,
    'Û', 0x06,  ' ', 0x06,  'Ü', 0x0E,  'Û', 0x0E,  'Ü', 0x6E,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06,  ' ', 0x06,
    ' ', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Û', 0x06,  'Û', 0x0E,  'Ü', 0x06, 'Ü', 0x0E,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  'Ü', 0x0E,  'Û', 0x0E,  'ß', 0x6E,  'ß', 0x6E, 'Ü', 0x0E,  ' ', 0x0E,  ' ', 0x0E,  ' ', 0x0E,  'Û', 0x0E,  'Û', 0x0E,
    'Ü', 0x06,  ' ', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06, 'Ü', 0x0E,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06,  'Û', 0x0E,  'Ü', 0x6E,
    'ß', 0x0E,  'Ü', 0x06,  'Ü', 0x6E,  'ß', 0x06,  ' ', 0x06,  'Ü', 0x0E, ' ', 0x0E,  'ß', 0x0E,  'ß', 0x6E,  'Ü', 0x0E,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0E,  ' ', 0x0E,  ' ', 0x0E,  'Ü', 0x0E,  ' ', 0x0E,  ' ', 0x0E, ' ', 0x0E,  'Û', 0x0E,  'ß', 0x6E,  'Û', 0x06,  ' ', 0x06,  ' ', 0x06,
    ' ', 0x06,  ' ', 0x06,  'Ü', 0x0E,  'ß', 0x0E,  'Ü', 0x06,  'ß', 0x06, ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,  'ß', 0x6E,  'Ü', 0x06,  'ß', 0x0E,
    'Û', 0x06,  'ß', 0x06,  ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,  'Û', 0x06, ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,  'Û', 0x06,
    'ß', 0x0E,  'ß', 0x6E,  'Ü', 0x06,  'ß', 0x06,  ' ', 0x06,  ' ', 0x06, ' ', 0x06,  ' ', 0x06,  'Ü', 0x0E,  'Û', 0x0E,  'ß', 0x6E,  'Û', 0x06,
    'ß', 0x06,  ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,  'Ü', 0x0E,  'Ü', 0x0E, 'Û', 0x0E,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,
    'Ü', 0x6E,  'ß', 0x0E,  'Ü', 0x06,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06, ' ', 0x06,  'ß', 0x0E,  'ß', 0x6E,  'ß', 0x6E,  'Ü', 0x06,  'ß', 0x06,
    ' ', 0x06,  ' ', 0x06,  'ß', 0x0E,  'ß', 0x6E,  'ß', 0x6E,  'Ü', 0x06, 'ß', 0x06,  ' ', 0x0F,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,
    'ß', 0x0E,  'ß', 0x6E,  'ß', 0x6E,  'Û', 0x0E,  'Û', 0x0E,  'Û', 0x0E, 'Û', 0x0E,  'Û', 0x0E,  'Û', 0x0E,  'ß', 0x6E,  'Ü', 0x06,  'ß', 0x06,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  'ß', 0x06, 'ß', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  'ß', 0x06,  'Û', 0x0E,  'Û', 0x0E,  'Û', 0x06,  ' ', 0x06, ' ', 0x06,  'Ü', 0x0E,  ' ', 0x0E,  'ß', 0x06,  ' ', 0x06,  'Û', 0x0E,
    'Û', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x06,  ' ', 0x06, ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,
    'ß', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x06,  'ß', 0x06, ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,
    ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06, ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0B,  ' ', 0x0B, ' ', 0x0B,  ' ', 0x0B,  ' ', 0x0B,  ' ', 0x0B,  ' ', 0x0B,  'ß', 0x0E,
    'ß', 0x6E,  'Ü', 0x06,  ' ', 0x06,  'ß', 0x0E,  'Ü', 0x6E,  'Ü', 0x0E, 'ß', 0x0E,  'Ü', 0x06,  'ß', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06, ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,
    ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x06, ' ', 0x06,  ' ', 0x06,  ' ', 0x06,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,
    ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F, ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0F,  ' ', 0x0A,  ' ', 0x0A,
    ' ', 0x0A,  'ß', 0x06,  'ß', 0x06
};

static void populateMenuAvailability() {
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP1;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP2;
    menuEntries[validMenuEntries++] = MAIN_ENTRY_EP3;

    if (fileExists(GAME_EXE_FILENAMES[0])) {
        ep1Enabled = true;
    }
    if (fileExists(GAME_EXE_FILENAMES[1])) {
        ep2Enabled = true;
    }

    if (fileExists(GAME_EXE_FILENAMES[2])) {
        ep3Enabled = true;
    }

    if (fileExists(FILE_NAME_README)) {
        supportEntries[validSupportEntries].name = ENTRY_README_NAME;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_README;
        supportEntries[validSupportEntries].hotkey = KEY_R;
        ++validSupportEntries;
    }

    if (fileExists(FILE_NAME_COPYRIGHT)) {
        supportEntries[validSupportEntries].name = ENTRY_COPYRIGHT_NAME;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_COPYRIGHT;
        supportEntries[validSupportEntries].hotkey = KEY_C;
        ++validSupportEntries;
    }

    if (fileExists(FILE_NAME_FREE_NOTE)) {
        supportEntries[validSupportEntries].name = ENTRY_FREE_NOTE_NAME;
        supportEntries[validSupportEntries].actionId = CUSTOM_SUPPORT_ACTION_FREE_NOTE;
        supportEntries[validSupportEntries].hotkey = KEY_F;
        ++validSupportEntries;
    }

    validSupportEntries += populateApogeeSupportEntries(&supportEntries[validSupportEntries], APOGEE_SHEET_PREFIX, 1 << APOGEE_SUPPORT_ACTION_HELP);

    if (validSupportEntries) {
        showInstructions = true;
        menuEntries[validMenuEntries++] = MAIN_ENTRY_INSTRUCTIONS;
    }
    menuEntries[validMenuEntries++] = MAIN_ENTRY_QUIT;

    maxScroll = validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? validSupportEntries - MAX_VISIBLE_INSTRUCTION_ITEMS : 0;
    visibleSupportEntries = (validSupportEntries > MAX_VISIBLE_INSTRUCTION_ITEMS ? MAX_VISIBLE_INSTRUCTION_ITEMS : validSupportEntries);
}

void drawLogo(int y_start) {
    setRawData(0, y_start, DA_LOGO, ARRAY_LENGTH(DA_LOGO));
}

static inline int getSupportMenuStartY() {
    return 16 - ((visibleSupportEntries | 0x1) >> 1);
}

static void drawSupportSelectionMarker() {
    int y = getSupportMenuStartY();
    drawColorChar(27, supportSelection == visibleSupportEntries ? y + visibleSupportEntries + 2 : y + 1 + supportSelection, ANIMATION_STATES[animationState], '\x10');
}

static void drawSupportMenu(bool updateSelectionOnly) {
    int y = getSupportMenuStartY();
    if (updateSelectionOnly) {
        for (int i = 0; i < visibleSupportEntries; ++i) {
            drawColorChar(27, y + 1 + i, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
        }
        drawColorChar(27, y + visibleSupportEntries + 2, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
        return;
    }

    drawBevelWindow(24, y - 1, 32, visibleSupportEntries + 6, TEXTCOLOR_BLUE, TEXTCOLOR_LIGHTBLUE, BGCOLOR_RED, 0);
    for (int i = 0; i < visibleSupportEntries; ++i) {
        drawColorChar(27, y + 1 + i, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
        drawLetterHighlightText(28, y + 1 + i, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, KEYCHAR_MAP[supportEntries[supportScroll + i].hotkey], supportEntries[supportScroll + i].name);
    }
    drawColorChar(27, y + visibleSupportEntries + 2, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
    drawLetterHighlightText(28, y + visibleSupportEntries + 2, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, 'B', "Back");
    drawSupportSelectionMarker();
    if (supportScroll < maxScroll) {
        drawCenterText(y + MAX_VISIBLE_INSTRUCTION_ITEMS + 1, TEXTCOLOR_WHITE|BGCOLOR_RED, "...");
    }
}

static void drawMainSelectionMarker() {
    int yPos = 0;
    if (showInstructions) {
        switch (mainSelection) {
            case 0:
                yPos = 16;
                break;
            case 1:
                yPos = 17;
                break;
            case 2:
                yPos = 18;
                break;
            case 3:
                yPos = 20;
                break;
            case 4:
                yPos = 22;
                break;
            default:
                break;
        }
    } else {
        switch (mainSelection) {
            case 0:
                yPos = 17;
                break;
            case 1:
                yPos = 18;
                break;
            case 2:
                yPos = 19;
                break;
            case 3:
                yPos = 21;
                break;
            default:
                break;
        }
    }
    drawColorChar(27, yPos, ANIMATION_STATES[animationState], '\x10');
}

void drawSelectionMarker() {
    supportMenu ? drawSupportSelectionMarker() : drawMainSelectionMarker();
}

static void drawMainMenu(bool updateSelectionOnly) {
    int episodeOffset = showInstructions ? 0 : 1;
    drawColorChar(27, 16 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
    drawColorChar(27, 17 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
    drawColorChar(27, 18 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
    drawColorChar(27, 22 - episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
    if (showInstructions) {
        drawColorChar(27, 20, TEXTCOLOR_WHITE|BGCOLOR_RED, ' ');
    }
    drawMainSelectionMarker();
    if (updateSelectionOnly) return;

    drawBevelWindow(24, 12 + episodeOffset, 32, 13 - 2 * episodeOffset, TEXTCOLOR_BLUE, TEXTCOLOR_LIGHTBLUE, BGCOLOR_RED, 0);
    drawCenterText(14 + episodeOffset, TEXTCOLOR_LIGHTGREEN|BGCOLOR_RED, "Volume Selection");

    ep1Enabled ?
        drawLetterHighlightText(28, 16 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, '1', EP1_STRING)
        :
        drawLetterHighlightText(28, 16 + episodeOffset, TEXTCOLOR_LIGHTRED|BGCOLOR_RED, TEXTCOLOR_LIGHTRED|BGCOLOR_RED, '1', EP1_STRING);
    ep2Enabled ?
        drawLetterHighlightText(28, 17 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, '2', EP2_STRING)
        :
        drawLetterHighlightText(28, 17 + episodeOffset, TEXTCOLOR_LIGHTRED|BGCOLOR_RED, TEXTCOLOR_LIGHTRED|BGCOLOR_RED, '2', EP2_STRING);
    ep3Enabled ?
        drawLetterHighlightText(28, 18 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, '3', EP3_STRING)
        :
        drawLetterHighlightText(28, 18 + episodeOffset, TEXTCOLOR_LIGHTRED|BGCOLOR_RED, TEXTCOLOR_LIGHTRED|BGCOLOR_RED, '3', EP3_STRING);
    if (showInstructions) {
        drawLetterHighlightText(28, 20 + episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, 'I', "Instructions");
    }
    drawLetterHighlightText(28, 22 - episodeOffset, TEXTCOLOR_WHITE|BGCOLOR_RED, TEXTCOLOR_LIGHTCYAN|BGCOLOR_RED, 'Q', "Quit");
}

static void clearMenu() {
    drawRectangle(24, 12, 32, 13, BGCOLOR_BLACK);
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

void drawMainLayout() {
    clearScreen();
    showCaret(false);
    drawLogo(1);
    drawCenterText(9, TEXTCOLOR_LIGHTCYAN, "by Todd Replogle");
    drawCenterText(10, TEXTCOLOR_LIGHTGREEN, "Copyright 1991 (c) Scenario Software");
    drawCenterText(11, TEXTCOLOR_WHITE, "Published by Apogee Software Productions");
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
                executeCommonSupportEntry(supportAction, APOGEE_GAME_TITLE_CAPS, APOGEE_GAME_TITLE, NULL);
                return true;
            }
            switch (supportAction) {
                case CUSTOM_SUPPORT_ACTION_README:
                    showText(FILE_NAME_README, APOGEE_GAME_TITLE_CAPS, TEXTCOLOR_CYAN|BGCOLOR_BLACK);
                    break;
                case CUSTOM_SUPPORT_ACTION_COPYRIGHT:
                    showText(FILE_NAME_COPYRIGHT, "COPYRIGHT NOTICE", TEXTCOLOR_CYAN|BGCOLOR_BLACK);
                    break;
                case CUSTOM_SUPPORT_ACTION_FREE_NOTE:
                    showText(FILE_NAME_FREE_NOTE, "Dark Ages Freeware Release Notes", TEXTCOLOR_WHITE|BGCOLOR_BLUE);
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
            printf("Run DARKAGES.BAT instead!\n");
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
            if (currentTime < updateTime || currentTime - updateTime > 10) {
                updateTime = currentTime;
                animationState = (animationState + 1) & 0x07;
                drawSelectionMarker();
            }
        }
    }
    cleanup();
    return 0;
}
