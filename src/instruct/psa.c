#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <process.h>
#include "../lib/file.h"
#include "../lib/output.h"
#include "../lib/input.h"
#include "../lib/text.h"
#include "../lib/error.h"
#include "../lib/menu.h"
#include "actions.h"

static enum CATALOG_NAME_TYPE {
    TYPE_PRICES_EXE,
    TYPE_RUNME_EXE,
    TYPE_CATALOG_EXE,
    TYPE_CATALOG_TXT,
    NUM_CATALOG_TYPES
};

static const char *CATALOG_NAMES[] = {
    "PRICES.EXE",
    "RUNME.EXE",
    "CATALOG.EXE",
    "CATALOG.TXT",
};

static enum ORDERFRM_NAME_TYPE {
    TYPE_REGISTER_FRM,
    TYPE_ORDER_FRM,
    NUM_ORDERFRM_TYPES
};

static const char *ORDERFRM_NAMES[] = {
    "REGISTER.FRM",
    "ORDER.FRM"
};

static enum LICENSE_NAME_TYPE {
    TYPE_DEALER_DOC,
    TYPE_VENDOR_DOC,
    NUM_LICENSE_TYPES
};

static const char *LICENSE_NAMES[] = {
    "DEALER.DOC",
    "VENDOR.DOC"
};

static const char* PSA_SUPPORT_ENTRY_NAMES[] = {
    "License Agreement",
    "Product Catalog",
    "Order Form"
};

static enum PSA_SUPPORT_ENTRIES {
    PSA_SUPPORT_ENTRY_LICENSE,
    PSA_SUPPORT_ENTRY_CATALOG,
    PSA_SUPPORT_ENTRY_ORDERFRM,
};



static const char FILE_NAME_FILE_LIST[] = "PSP.DOC";

void drawMainLayout();

static const char PSA_ORDERFRM_TITLE[] = "PRECISION SOFTWARE APPLICATIONS ORDER FORM";
static const char PSP_ORDERFRM_TITLE[] = "Precision Software Publishing Order Form";

static const char PSP_LICENSE_TITLE[] = "Precision Software Publishing License Agreement";

static const char PSA_LICENSE_SEPARATOR[] = "\n"
                                            "-------------------------------------------------------------------------------\n"
                                            "\n";

#define PSA_ORDERFRM_930413 4516
#define PSA_ORDERFRM_930603 4589

static int catalogType = -1;
static int orderFrmType = -1;
static int licenseType = -1;
static const char* orderFrmTitle = NULL;

bool hasPrecisionSoftwareCatalog() {
    int i;
    for (i = 0; i < NUM_CATALOG_TYPES; ++i) {
        if (fileExists(CATALOG_NAMES[i])) {
            catalogType = i;
            return true;
        }
    }
    return false;
}

bool hasPrecisionSoftwareOrderForm() {
    int i;
    long fsize;
    for (i = 0; i < NUM_ORDERFRM_TYPES; ++i) {
        fsize = fileSize(ORDERFRM_NAMES[i]);
        if (fsize != -1) {
            orderFrmType = i;
            if (fsize == PSA_ORDERFRM_930413 || fsize == PSA_ORDERFRM_930603) {
                orderFrmTitle = PSP_ORDERFRM_TITLE;
            } else {
                orderFrmTitle = PSA_ORDERFRM_TITLE;
            }
            return true;
        }
    }
    return false;
}

bool hasPrecisionSoftwareLicenseAgreement() {
    int i;
    for (i = 0; i < NUM_LICENSE_TYPES; ++i) {
        if (fileExists(LICENSE_NAMES[i])) {
            licenseType = i;
            return true;
        }
    }
    return false;
}

void showPrecisionSoftwareCatalog() {
    int errorCode;
    const char* fileName = CATALOG_NAMES[catalogType];
    cleanup();
    if (catalogType == TYPE_CATALOG_TXT) {
        storeTextStyle();
        setStyle(TEXTCOLOR_WHITE|BGCOLOR_BLUE, TEXTCOLOR_WHITE|BGCOLOR_BLACK, TEXT_LAYOUT_TRADITIONAL);
        showTextFile(fileName, "PRECISION SOFTWARE APPLICATIONS");
        restoreTextStyle();
    } else {
        errorCode = spawnl(P_WAIT, fileName, NULL);
        if (errorCode == -1) {
            fprintf(stderr, EXEC_ERROR_MSG_F, catalogType, strerror(errno));
            getPressedKey();
        }
    }
    drawMainLayout();    
}

void showPrecisionSoftwareOrderForm() {
    const char* fileName = ORDERFRM_NAMES[orderFrmType];
    cleanup();
    storeTextStyle();
    setStyle(TEXTCOLOR_WHITE|BGCOLOR_BLUE, TEXTCOLOR_WHITE|BGCOLOR_BLACK, TEXT_LAYOUT_TRADITIONAL);
    showTextFile(fileName, orderFrmTitle);
    restoreTextStyle();
    drawMainLayout();
}

void showPrecisionSoftwareLicenseAgreement() {
    const char* fileName = LICENSE_NAMES[licenseType];
    bool hasFileList = fileExists(FILE_NAME_FILE_LIST);
    cleanup();
    storeTextStyle();
    setStyle(TEXTCOLOR_WHITE|BGCOLOR_BLUE, TEXTCOLOR_WHITE|BGCOLOR_BLACK, TEXT_LAYOUT_TRADITIONAL);
    if (!hasFileList) {
        showTextFile(fileName, PSP_LICENSE_TITLE);
    } else {
        showTextFiles(PSP_LICENSE_TITLE, PSA_LICENSE_SEPARATOR, fileName, FILE_NAME_FILE_LIST, NULL);
    }
    restoreTextStyle();
    drawMainLayout();
}

int populatePrecisionSoftwareSupportEntries(menuEntry* entry, int skip) {
    int count = 0;
    if (!(skip & 1 << PSA_SUPPORT_ACTION_LICENSE) && hasPrecisionSoftwareLicenseAgreement()) {
        entry->name = PSA_SUPPORT_ENTRY_NAMES[PSA_SUPPORT_ENTRY_LICENSE];
        entry->actionId = PSA_SUPPORT_ACTION_LICENSE;
        entry->hotkey = KEY_L;
        ++entry;
        ++count;
    }
    if (!(skip & 1 << PSA_SUPPORT_ACTION_CATALOG) && hasPrecisionSoftwareCatalog()) {
        entry->name = PSA_SUPPORT_ENTRY_NAMES[PSA_SUPPORT_ENTRY_CATALOG];
        entry->actionId = PSA_SUPPORT_ACTION_CATALOG;
        entry->hotkey = KEY_P;
        ++entry;
        ++count;
    }
    if (!(skip & 1 << PSA_SUPPORT_ACTION_ORDERFRM) && hasPrecisionSoftwareOrderForm()) {
        entry->name = PSA_SUPPORT_ENTRY_NAMES[PSA_SUPPORT_ENTRY_ORDERFRM];
        entry->actionId = PSA_SUPPORT_ACTION_ORDERFRM;
        entry->hotkey = KEY_O;
        ++entry;
        ++count;
    }
    return count;
}

void executePrecisionSoftwareSupportEntry(int actionId) {
    switch (actionId) {
        case PSA_SUPPORT_ACTION_LICENSE:
            showPrecisionSoftwareLicenseAgreement();
            break;
        case PSA_SUPPORT_ACTION_CATALOG:
            showPrecisionSoftwareCatalog();
            break;
        case PSA_SUPPORT_ACTION_ORDERFRM:
            showPrecisionSoftwareOrderForm();
            break;
        default:
            break;
    }
}
