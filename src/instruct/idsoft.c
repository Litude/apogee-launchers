#include "../lib/input.h"
#include "../lib/output.h"
#include "../lib/file.h"
#include "../lib/text.h"
#include "../lib/menu.h"
#include "actions.h"

#define ID_VENDOR_LETTER_SIZE 1221

static const char* IDSOFT_SUPPORT_ENTRY_NAMES[] = {
    "Greetings from Id Software",
    "Vendor Letter",
};

static enum IDSOFT_SUPPORT_ENTRIES {
    IDSOFT_SUPPORT_ENTRY_GREETINGS,
    IDSOFT_SUPPORT_ENTRY_VENDOR_LETTER,
};

static const char VENDOR_LETTER_FILENAME[] = "VENDOR.DOC";
static const char GREETINGS_FILENAME[] = "READ1ST.TXT";

void drawMainLayout();

int populateIdSoftwareSupportEntries(menuEntry* entry, int skip) {
    int count = 0;
    if (!(skip & 1 << IDSOFT_SUPPORT_ACTION_GREETINGS) && fileExists(GREETINGS_FILENAME)) {
        entry->name = IDSOFT_SUPPORT_ENTRY_NAMES[IDSOFT_SUPPORT_ENTRY_GREETINGS];
        entry->actionId = IDSOFT_SUPPORT_ACTION_GREETINGS;
        entry->hotkey = KEY_G;
        ++entry;
        ++count;
    }
    if (!(skip & 1 << IDSOFT_SUPPORT_ACTION_VENDOR_LETTER) && fileSize(VENDOR_LETTER_FILENAME) == ID_VENDOR_LETTER_SIZE) {
        entry->name = IDSOFT_SUPPORT_ENTRY_NAMES[IDSOFT_SUPPORT_ENTRY_VENDOR_LETTER];
        entry->actionId = IDSOFT_SUPPORT_ACTION_VENDOR_LETTER;
        entry->hotkey = KEY_V;
        ++entry;
        ++count;
    }
    return count;
}

void executeIdSoftwareSupportEntry(int actionId) {
    cleanup();
    storeTextStyle();
    setStyle(TEXTCOLOR_WHITE|BGCOLOR_BLACK, TEXTCOLOR_WHITE|BGCOLOR_BLUE, TEXT_LAYOUT_TRADITIONAL);
    switch (actionId) {
        case IDSOFT_SUPPORT_ACTION_GREETINGS:
            showTextFile(GREETINGS_FILENAME, "Greetings from Id Software");
            break;
        case IDSOFT_SUPPORT_ACTION_VENDOR_LETTER:
            showTextFile(VENDOR_LETTER_FILENAME, "Vendor Letter from Id Software");
            break;
    }
    restoreTextStyle();
    drawMainLayout();
}
