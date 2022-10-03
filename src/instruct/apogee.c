#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "../lib/exeparse.h"
#include "../lib/input.h"
#include "../lib/memory.h"
#include "../lib/file.h"
#include "../lib/output.h"
#include "../lib/text.h"
#include "../lib/error.h"
#include "../lib/menu.h"
#include "actions.h"

static const char SWCBBS_FILENAME[] = "SWCBBS.EXE";
static const char LICENSE_FILENAME[] = "LICENSE.DOC";
static const char VENDOR_FILENAME[] = "VENDOR.DOC";
static const char INSTALLHELP_FILENAME[] = "INSTALL.EXE";

static const char CATALOG_TITLE_ASP_CAPS[] = "APOGEE SOFTWARE PRODUCTIONS CATALOG";
static const char CATALOG_TITLE_CAPS[] = "APOGEE SOFTWARE CATALOG";
static const char ORDERFRM_TITLE_CAPS[] = "APOGEE SOFTWARE ORDER FORM";
static const char ORDERFRM_TITLE_SHORT[] = "Apogee Order Form";
static const char ORDERFRM_TITLE[] = "Apogee Software Order Form";
static const char ORDERFRM_TITLE_AP3DR[] = "Apogee/3D Realms Order Form";
static const char FOREIGN_TITLE_CAPS[] = "FOREIGN DEALERS LISTING";

static const char THE_PREFIX[] = "The";
static const char TXT_LICENSE_AGREEMENT[] = "License Agreement";
static const char TXT_SHAREWARE[] = "Shareware";
static const char TXT_SOFTWARE[] = "Software";
static const char TXT_SHAREWARE_DIST_AGREEMENT[] = "Apogee Software Shareware Distribution Agreement";

#define SHAREWARE_DIST_LIC_SIZE 7427

static const char SINGLE_SEPARATOR[] = "-";
static const char DOUBLE_SEPARATOR[] = "--";

static const char MONTH_JAN[] = "JAN.";
static const char MONTH_FEB[] = "FEB.";
static const char MONTH_MAR[] = "MAR.";
static const char MONTH_APR[] = "APR.";
static const char MONTH_MAY[] = "MAY";
static const char MONTH_JUN[] = "JUN.";
static const char MONTH_JUL[] = "JUL.";
static const char MONTH_AUG[] = "AUG.";
static const char MONTH_SEP[] = "SEP.";
static const char MONTH_OCT[] = "OCT.";
static const char MONTH_NOV[] = "NOV.";
static const char MONTH_DEC[] = "DEC.";

static const char MONTH_JANUARY[] = "JANUARY";
static const char MONTH_FEBRUARY[] = "FEBRUARY";
static const char MONTH_MARCH[] = "MARCH";
static const char MONTH_APRIL[] = "APRIL";
// static const char MONTH_MAY[] = "MAY"; //DUPE
static const char MONTH_JUNE[] = "JUNE";
static const char MONTH_JULY[] = "JULY";
static const char MONTH_AUGUST[] = "AUGUST";
static const char MONTH_SEPTEMBER[] = "SEPTEMBER";
static const char MONTH_OCTOBER[] = "OCTOBER";
static const char MONTH_NOVEMBER[] = "NOVEMBER";
static const char MONTH_DECEMBER[] = "DECEMBER";

static const char MONTH_LJANUARY[] = "January";
static const char MONTH_LFEBRUARY[] = "February";
static const char MONTH_LMARCH[] = "March";
static const char MONTH_LAPRIL[] = "April";
static const char MONTH_LMAY[] = "May";
static const char MONTH_LJUNE[] = "June";
static const char MONTH_LJULY[] = "July";
static const char MONTH_LAUGUST[] = "August";
static const char MONTH_LSEPTEMBER[] = "September";
static const char MONTH_LOCTOBER[] = "October";
static const char MONTH_LNOVEMBER[] = "November";
static const char MONTH_LDECEMBER[] = "December";

// static const char YEAR_1988[] = "1988";
static const char YEAR_1989[] = "1989";
static const char YEAR_1990[] = "1990";
static const char YEAR_1991[] = "1991";
static const char YEAR_1992[] = "1992";
static const char YEAR_1993[] = "1993";
static const char YEAR_1994[] = "1994";
static const char YEAR_1995[] = "1995";
static const char YEAR_1996[] = "1996";
static const char YEAR_1997[] = "1997";
static const char YEAR_1998[] = "1998";
static const char YEAR_1999[] = "1999";
static const char YEAR_2000[] = "2000";
static const char YEAR_2001[] = "2001";
static const char YEAR_2002[] = "2002";
static const char YEAR_2003[] = "2003";
// static const char YEAR_2004[] = "2004";
static const char YEAR_2005[] = "2005";
static const char YEAR_2006[] = "2006";
// static const char YEAR_2007[] = "2007";
// static const char YEAR_2008[] = "2008";
static const char YEAR_2009[] = "2009";

static const char DATE_1ST[] = "1,";
// static const char DATE_2ND[] = "2,";
// static const char DATE_3RD[] = "3,";
static const char DATE_4TH[] = "4,";
static const char DATE_5TH[] = "5,";
static const char DATE_6TH[] = "6,";
static const char DATE_7TH[] = "7,";
// static const char DATE_8TH[] = "8,";
// static const char DATE_9TH[] = "9,";
static const char DATE_10TH[] = "10,";
// static const char DATE_11TH[] = "11,";
// static const char DATE_12TH[] = "12,";
// static const char DATE_13TH[] = "13,";
// static const char DATE_14TH[] = "14,";
// static const char DATE_15TH[] = "15,";
// static const char DATE_16TH[] = "16,";
static const char DATE_17TH[] = "17,";
static const char DATE_18TH[] = "18,";
// static const char DATE_19TH[] = "19,";
// static const char DATE_20TH[] = "20,";
static const char DATE_21ST[] = "21,";
// static const char DATE_22ND[] = "22,";
// static const char DATE_23RD[] = "23,";
static const char DATE_24TH[] = "24,";
// static const char DATE_25TH[] = "25,";
static const char DATE_26TH[] = "26,";
// static const char DATE_27TH[] = "27,";
// static const char DATE_28TH[] = "28,";
// static const char DATE_29TH[] = "29,";
// static const char DATE_30TH[] = "30,";
static const char DATE_31ST[] = "31,";

static const char SUF_EDITION[] = "EDITION";
static const char SUF_UPDATED[] = "(UPDATED)";
static const char SUF_LEDITION[] = "Edition";
static const char SUF_LREVISION[] = "Revision";

static char catalogTitleBuffer[80];
static char orderFrmTitleBuffer[80];

// Entries that should be discarded
#define CATALOG_INSTALLER_920527_SIZE 26997
#define CATALOG_INSTALLER_920527_CSUM 63444
#define CATALOG_INSTALLER_920625_SIZE 27498
#define CATALOG_INSTALLER_920625_CSUM 27850
#define CATALOG_INSTALLER_921020_SIZE 19843
#define CATALOG_INSTALLER_921020_CSUM 22055
#define CATALOG_INSTALLER_921101_SIZE 24748
#define CATALOG_INSTALLER_921101_CSUM 35459
#define CATALOG_ACTUAL_DOC_890829 12230

// Try treating all names (except README.TXT) as equal so name is not that important
#define CATALOG_TXT_881201 7854  // Only one for README.TXT check
#define CATALOG_TXT_890829 10178
#define CATALOG_TXT_900204 16002
#define CATALOG_TXT_900227 17189
#define CATALOG_TXT_900317 19117
#define CATALOG_TXT_900401 22125
#define CATALOG_TXT_900808 33324
#define CATALOG_TXT_901112 25832
#define CATALOG_TXT_901210 29092
#define CATALOG_TXT_901214 29373
#define CATALOG_TXT_910129 25730
// #define CATALOG_TXT_910501 25730 // This is identical to 910129
#define CATALOG_TXT_920524 54907
#define CATALOG_TXT_920625 56063
#define CATALOG_TXT_921020 33381
#define CATALOG_TXT_921101 49625
#define CATALOG_TXT_930128 52499

#define ORDERFRM_910129 1520
#define ORDERFRM_910501 1595
#define ORDERFRM_911001 2034 // APOGEE SOFTWARE ORDER FORM -- OCT. 1991
// #define ORDERFRM_911023 2034 // This is identical to 911001
#define ORDERFRM_911104 1954 // APOGEE SOFTWARE ORDER FORM -- NOV. 1991
#define ORDERFRM_911121 2346 // APOGEE SOFTWARE ORDER FORM -- DECEMBER 1991 EDITION
#define ORDERFRM_920203 2282 // APOGEE SOFTWARE ORDER FORM -- FEB. 1992
#define ORDERFRM_920301 2358 // APOGEE SOFTWARE ORDER FORM -- MARCH 1992
#define ORDERFRM_920328 2260 // APOGEE SOFTWARE ORDER FORM -- APRIL 1992 EDITION
#define ORDERFRM_920417_OR_920505 2440
#define ORDERFRM_920417_CHKSUM 50238 //APOGEE SOFTWARE ORDER FORM -- APRIL 1992
#define ORDERFRM_920505_CHKSUM 60159 //APOGEE SOFTWARE ORDER FORM -- MAY 1992 EDITION
#define ORDERFRM_920522 2564 // APOGEE SOFTWARE ORDER FORM -- JUNE 1992 EDITION
#define ORDERFRM_921001 2655 // APOGEE SOFTWARE ORDER FORM -- OCTOBER 1992 EDITION
#define ORDERFRM_930128_OR_930201 2855
#define ORDERFRM_930128_CHKSUM 22592 // APOGEE SOFTWARE ORDER FORM -- JANUARY 1993 EDITION
#define ORDERFRM_930201_CHKSUM 22847 // APOGEE SOFTWARE ORDER FORM -- FEB 1993
#define ORDERFRM_930401 2931 // APOGEE SOFTWARE ORDER FORM -- APRIL 1993
// #define ORDERFRM_930410 2931 // IDENTICAL
// #define ORDERFRM_930511 2931 // IDENTICAL
#define ORDERFRM_930518 3283 // Apogee Software Productions Order Form - May 18, 1993
#define ORDERFRM_930726 3407 // The Apogee Software Productions Order Form - July 26, 1993
#define ORDERFRM_930803 3321 // The Apogee Software Order Form - August 1, 1993
#define ORDERFRM_930905 3364 // The Apogee Software Order Form - September 5, 1993 Edition
#define ORDERFRM_931117 3538 // The Apogee Software Order Form - November 17, 1993 Edition
#define ORDERFRM_931201 5984 // The Apogee Software Order Form - December 1, 1993 Edition
#define ORDERFRM_931202 6228 // The Apogee Software Order Form - December 1, 1993 Edition

// #define ORDERFRM_940201 6228 // IDENTICAL
#define ORDERFRM_940401 6237 // APOGEE SOFTWARE ORDER FORM - APRIL 1994
#define ORDERFRM_940601 5833 // APOGEE SOFTWARE ORDER FORM - JUNE 1994
#define ORDERFRM_940715 5913 // APOGEE SOFTWARE ORDER FORM - JULY 1994
#define ORDERFRM_941001 5987 // Apogee Order Form - October 1994
#define ORDERFRM_941017 5906 // Apogee Order Form - October 1994
#define ORDERFRM_941101 5992 // Apogee Order Form - November 1994
#define ORDERFRM_941221 5993 // Apogee Software Order Form - December 1994

#define ORDERFRM_950201 5679 // Apogee Software Order Form - February 1995
// #define ORDERFRM_950601 5679 // IDENTICAL
#define ORDERFRM_950801 5680 // Apogee Software, Ltd. Order Form - Aug '95
#define ORDERFRM_951101 5757 // Apogee Software Order Form - November 1995

#define ORDERFRM_960101 5911 // Apogee Software Order Form - January 1996
// #define ORDERFRM_960501 5911 // IDENTICAL
// #define ORDERFRM_960701 5911 // IDENTICAL
#define ORDERFRM_960901 5988 // Apogee Software Order Form - Sept. 1996
#define ORDERFRM_961201 6095 // Apogee Software Order Form - December 1996

// 1997
#define ORDERFRM_970522 5990 // Apogee Software Order Form - May 1997

// 1998
#define ORDERFRM_980421_OR_981205 5714
#define ORDERFRM_980421_CHKSUM 1958 // Apogee/3D Realms Order Form - May 1998
#define ORDERFRM_981205_CHKSUM 4419 // Apogee/3D Realms Order Form - December 1998

// 1999
#define ORDERFRM_990805 5606 // Apogee/3D Realms Order Form - August 1999
#define ORDERFRM_991102 5726 // Apogee/3D Realms Order Form - November 1999

// 2000
#define ORDERFRM_000402 5819 // Apogee/3D Realms Order Form - April 2000
#define ORDERFRM_000421 5700 // Apogee/3D Realms Order Form - April 21, 2000 Revision
#define ORDERFRM_000804 5777 // Apogee/3D Realms Order Form - August 4, 2000 Revision
#define ORDERFRM_001004 5699 // Apogee/3D Realms Order Form - October 4, 2000 Revision

// 2001
#define ORDERFRM_010307 5620 // Apogee/3D Realms Order Form - March 7, 2001 Revision
#define ORDERFRM_010424 5544 // Apogee/3D Realms Order Form - April 24, 2001 Revision
#define ORDERFRM_010521 5681 // Apogee/3D Realms Order Form - May 21, 2001 Revision
#define ORDERFRM_010731 5622 // Apogee/3D Realms Order Form - July 31, 2001 Revision
#define ORDERFRM_011017A 5548 // Apogee/3D Realms Order Form - October 17, 2001 Revision
#define ORDERFRM_011017B 5598 // Apogee/3D Realms Order Form - October 17, 2001 Revision

// 2002
#define ORDERFRM_020507 5287 // Apogee/3D Realms Order Form - May 7, 2002 Revision
#define ORDERFRM_021126_OR_021218 5138
#define ORDERFRM_021126_CHKSUM 19365 // Apogee/3D Realms Order Form - November 26, 2002 Revision
#define ORDERFRM_021218_CHKSUM 24258 // Apogee/3D Realms Order Form - December 18, 2002 Revision

#define ORDERFRM_031106 4902 // Apogee/3D Realms Order Form - Nov 6, 2003 Revision
#define ORDERFRM_050921 4693 // Apogee/3D Realms Order Form - SEP 21, 2005 Revision
#define ORDERFRM_051021 4941 // Apogee/3D Realms Order Form - OCT 21, 2005 Revision
#define ORDERFRM_060509_OR_090310 4710
#define ORDERFRM_060509_CHKSUM 52523 // Apogee/3D Realms Order Form - MAY 09, 2006 Revision
#define ORDERFRM_090310_CHKSUM 65326 // Apogee/3D Realms Order Form - MAR 10, 2009 Revision


#define PRINTME_910525 2005
#define PRINTME_910801 1691 // LZ compressed
#define PRINTME_910801U 2578 // UNLZEXE uncompressed

#define PRINTME_910525_OFFSET 0x1B5
#define PRINTME_910801_OFFSET 0x3B5

#define MICROFX_CATALOG 10791 // Called README.TXT
#define ID_VENDOR_LETTER_SIZE 1221 // Called VENDOR.DOC, not valid license
#define ID_VENDOR_LETTER_CSUM 58226

#define INSTALLHELP_SIZE 4971

static enum {
    TYPE_CATALOG_EXE,
    TYPE_CATALOG_DOC,
    TYPE_CATALOG_TXT,
    TYPE_READALL_TXT,
    TYPE_README_TXT,
    NUM_CATALOG_TYPES
} CATALOG_NAME_TYPE;

static const char *CATALOG_NAMES[] = {
    "CATALOG.EXE",
    "CATALOG.DOC",
    "CATALOG.TXT",
    "READALL.TXT",
    "README.TXT"
};

static enum {
    TYPE_ORDERFRM_TXT,
    TYPE_ORDER_FRM,
    TYPE_PRINTME_EXE,
    NUM_ORDERFRM_TYPES
} ORDERFRM_NAME_TYPE;

static const char *ORDERFRM_NAMES[] = {
    "ORDER.FRM",
    "ORDERFRM.TXT",
    "PRINTME.EXE"
};

static enum {
    TYPE_DEALERS_EXE,
    TYPE_FOREIGN_DOC,
    NUM_DEALERS_TYPES
} DEALERS_NAME_TYPE;

static const char *DEALERS_NAMES[] = {
    "DEALERS.EXE",
    "FOREIGN.DOC"
};

static const char HINTSHEET_SUFFIX[] = "HINT.EXE";
static const char HELPSHEET_SUFFIX[] = "HELP.EXE";

const char* APOGEE_SUPPORT_ENTRY_NAMES[] = {
    "Installation Help",
    "Technical Help",
    "Hint Sheet",
    "License Agreement",
    "Apogee Catalog",
    "Worldwide Dealers List",
    "Software Creations BBS",
    "Order Form"
};

static int catalogType = -1;
static const char *catalogFileName = NULL;
static int catalogTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
static int catalogLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
// static int catalogLayout = TEXT_LAYOUT_TRADITIONAL;

static int orderFrmType = -1;
static const char *orderFrmFileName = NULL;
static int orderFrmTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
static int orderFrmLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
static int orderFrmLayout = TEXT_LAYOUT_TRADITIONAL;

static int dealersType = -1;
static const char *dealersFileName = NULL;

static char helpSheetName[13];
static char hintSheetName[13];

void drawMainLayout();

static void createTitle(char* buffer, ...) {
    char* next = NULL;
    va_list args;
    va_start(args, buffer);
    next = va_arg(args, char*);
    strcpy(buffer, next);
    next = va_arg(args, char*);
    while (next != NULL) {
        if (*next) { // Empty strings can be used for skipping
            strcat(buffer, " ");
            strcat(buffer, next);
        }
        next = va_arg(args, char*);
    }

    va_end(args);
}

void setOldRedCyanCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLUE;
    catalogLegendStyle = TEXTCOLOR_YELLOW|BGCOLOR_RED;
}

void setOldPurpleGreenCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_LIGHTGREEN|BGCOLOR_BLUE;
    catalogLegendStyle = TEXTCOLOR_YELLOW|BGCOLOR_PURPLE;
}

void setOldPurpleCyanCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLUE;
    catalogLegendStyle = TEXTCOLOR_YELLOW|BGCOLOR_PURPLE;
}

void setOldBlackWhiteCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLACK;
    catalogLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
}

void setOldBlackGrayCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_GRAY|BGCOLOR_BLACK;
    catalogLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
}

void setOldDarkCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_CYAN|BGCOLOR_BLACK;
    catalogLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
}

void setOldDarkGreenCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLACK;
    catalogLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GREEN;
}

void setBasicCatalogTextStyle() {
    catalogTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
    catalogLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
}

bool hasApogeeCatalog() {
    long size = 0;
    int i = 0;
    for (i = 0; i < NUM_CATALOG_TYPES; ++i) {
        size = fileSize(CATALOG_NAMES[i]);
        if (size != -1) {
            switch (i) {
                case TYPE_CATALOG_EXE: {
                    // Don't want any false positives here, but checksum only calculated once if size matches --> should not occur often
                    if (
                        (size != CATALOG_INSTALLER_920527_SIZE || checksum(CATALOG_NAMES[i]) != CATALOG_INSTALLER_920527_CSUM) &&
                        (size != CATALOG_INSTALLER_920625_SIZE || checksum(CATALOG_NAMES[i]) != CATALOG_INSTALLER_920625_CSUM) &&
                        (size != CATALOG_INSTALLER_921020_SIZE || checksum(CATALOG_NAMES[i]) != CATALOG_INSTALLER_921020_CSUM) &&
                        (size != CATALOG_INSTALLER_921101_SIZE || checksum(CATALOG_NAMES[i]) != CATALOG_INSTALLER_921101_CSUM)
                    ) {
                        catalogFileName = CATALOG_NAMES[i];
                        catalogType = TYPE_CATALOG_EXE;
                        return true;
                    }
                    break;
                }
                case TYPE_README_TXT:
                    // Skip if size doesn't match, else fall through
                    if (size != CATALOG_TXT_881201) break;
                case TYPE_CATALOG_DOC:
                    // Skip if size matches, else fall through
                    if (size == CATALOG_ACTUAL_DOC_890829) break;
                case TYPE_CATALOG_TXT:
                case TYPE_READALL_TXT:
                    catalogType = TYPE_CATALOG_TXT;
                    catalogFileName = CATALOG_NAMES[i];
                    switch (size) {
                        case CATALOG_TXT_881201:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_ASP_CAPS, DOUBLE_SEPARATOR, MONTH_JAN, YEAR_1989, NULL);
                            setOldRedCyanCatalogTextStyle();
                            break;
                        case CATALOG_TXT_890829:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_ASP_CAPS, DOUBLE_SEPARATOR, MONTH_AUG, YEAR_1989, NULL);
                            setOldPurpleGreenCatalogTextStyle();
                            break;
                        case CATALOG_TXT_900204:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_ASP_CAPS, DOUBLE_SEPARATOR, MONTH_FEB, YEAR_1990, NULL);
                            setOldPurpleCyanCatalogTextStyle();
                            break;
                        case CATALOG_TXT_900227:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_ASP_CAPS, DOUBLE_SEPARATOR, MONTH_MAR, YEAR_1990, NULL);
                            setOldBlackWhiteCatalogTextStyle();
                            break;
                        case CATALOG_TXT_900317:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_ASP_CAPS, DOUBLE_SEPARATOR, MONTH_MAR, YEAR_1990, SUF_UPDATED, NULL);
                            setOldBlackWhiteCatalogTextStyle();
                            break;
                        case CATALOG_TXT_900401:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_ASP_CAPS, DOUBLE_SEPARATOR, MONTH_APR, YEAR_1990, NULL);
                            setOldBlackGrayCatalogTextStyle();
                            break;
                        case CATALOG_TXT_900808:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_AUG, YEAR_1990, NULL);
                            setOldDarkCatalogTextStyle();
                            break;
                        case CATALOG_TXT_901112:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_NOV, YEAR_1990, NULL);
                            setOldDarkCatalogTextStyle();
                            break;
                        case CATALOG_TXT_901210:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_DEC, YEAR_1990, NULL);
                            setOldDarkCatalogTextStyle();
                            break;
                        case CATALOG_TXT_901214:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_DEC, YEAR_1990, SUF_UPDATED, NULL);
                            setOldDarkCatalogTextStyle();
                            break;
                        case CATALOG_TXT_910129:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_FEB, YEAR_1991, NULL);
                            setOldDarkGreenCatalogTextStyle();
                            break;
                        case CATALOG_TXT_920524:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_JUNE, YEAR_1992, SUF_EDITION, NULL);
                            setBasicCatalogTextStyle();
                            break;
                        case CATALOG_TXT_920625:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_JULY, YEAR_1992, SUF_EDITION, NULL);
                            setBasicCatalogTextStyle();
                            break;
                        case CATALOG_TXT_921020:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_OCTOBER, YEAR_1992, SUF_EDITION, NULL);
                            setBasicCatalogTextStyle();
                            break;
                        case CATALOG_TXT_921101:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_NOVEMBER, YEAR_1992, SUF_EDITION, NULL);
                            setBasicCatalogTextStyle();
                            break;
                        case CATALOG_TXT_930128:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_JANUARY, YEAR_1993, SUF_EDITION, NULL);
                            setBasicCatalogTextStyle();
                            break;
                        default:
                            createTitle(catalogTitleBuffer, CATALOG_TITLE_CAPS, NULL);
                            setBasicCatalogTextStyle();
                            break;
                    }
                    return true;
                default:
                    break;
            }
        }
    }
    return false;
}

void setOldBlueRedOrderFrmTextStyle() {
    orderFrmTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
    orderFrmLegendStyle = TEXTCOLOR_YELLOW|BGCOLOR_RED;
    orderFrmLayout = TEXT_LAYOUT_TRADITIONAL;
}

void setOldDarkOrderFrmTextStyle() {
    orderFrmTextStyle = TEXTCOLOR_CYAN|BGCOLOR_BLACK;
    orderFrmLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
    orderFrmLayout = TEXT_LAYOUT_TRADITIONAL;
}

void setOldDarkGreenOrderFrmTextStyle() {
    orderFrmTextStyle = TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLACK;
    orderFrmLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GREEN;
    orderFrmLayout = TEXT_LAYOUT_TRADITIONAL;
}

void setBasicOrderFrmTextStyle() {
    orderFrmTextStyle = TEXTCOLOR_WHITE|BGCOLOR_BLUE;
    orderFrmLegendStyle = TEXTCOLOR_BLACK|BGCOLOR_GRAY;
    orderFrmLayout = TEXT_LAYOUT_TRADITIONAL;
}

void setModernOrderFrmTextStyle() {
    orderFrmTextStyle = TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLACK;
    orderFrmLegendStyle = TEXTCOLOR_LIGHTCYAN|BGCOLOR_BLUE;
    orderFrmLayout = TEXT_LAYOUT_MODERN;
}

bool hasApogeeOrderForm() {
    long size = 0;
    unsigned int csum = 0;
    int i = 0;
    for (i = 0; i < NUM_ORDERFRM_TYPES; ++i) {
        size = fileSize(ORDERFRM_NAMES[i]);
        if (size != -1) {
            switch (i) {
                case TYPE_ORDERFRM_TXT:
                case TYPE_ORDER_FRM: {
                    orderFrmType = TYPE_ORDER_FRM;
                    orderFrmFileName = ORDERFRM_NAMES[i];
                    switch (size) {
                        case ORDERFRM_910129:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_FEB, YEAR_1991, NULL);
                            setOldDarkGreenOrderFrmTextStyle();
                            break;
                        case ORDERFRM_910501:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_MAY, YEAR_1991, NULL);
                            setOldBlueRedOrderFrmTextStyle();
                            break;
                        case ORDERFRM_911001:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_OCT, YEAR_1991, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_911104:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_NOV, YEAR_1991, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_911121:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_DECEMBER, YEAR_1991, SUF_EDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_920203:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_FEB, YEAR_1992, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_920301:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_MARCH, YEAR_1992, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_920328:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_APRIL, YEAR_1992, SUF_EDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_920417_OR_920505:
                            csum = checksum(orderFrmFileName);
                            if (csum == ORDERFRM_920417_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_APRIL, YEAR_1992, NULL);
                            } else if (csum == ORDERFRM_920505_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_MAY, YEAR_1992, SUF_EDITION, NULL);
                            } else {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, NULL);
                            }
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_920522:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_JUNE, YEAR_1992, SUF_EDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_921001:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_OCTOBER, YEAR_1992, SUF_EDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_930128_OR_930201:
                            csum = checksum(orderFrmFileName);
                            if (csum == ORDERFRM_930128_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_JANUARY, YEAR_1993, SUF_EDITION, NULL);
                            } else if (csum == ORDERFRM_930201_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, "FEB", YEAR_1993, NULL);
                            } else {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, NULL);
                            }
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_930401:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_APRIL, YEAR_1993, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_930518:
                            createTitle(orderFrmTitleBuffer, "Apogee Software Productions Order Form", SINGLE_SEPARATOR, MONTH_LMAY, DATE_18TH, YEAR_1993, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_930726:
                            createTitle(orderFrmTitleBuffer, "The Apogee Software Productions Order Form", SINGLE_SEPARATOR, MONTH_LJULY, DATE_26TH, YEAR_1993, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_930803:
                            createTitle(orderFrmTitleBuffer, THE_PREFIX, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LAUGUST, DATE_1ST, YEAR_1993, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_930905:
                            createTitle(orderFrmTitleBuffer, THE_PREFIX, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LSEPTEMBER, DATE_5TH, YEAR_1993, SUF_LEDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_931117:
                            createTitle(orderFrmTitleBuffer, THE_PREFIX, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LNOVEMBER, DATE_17TH, YEAR_1993, SUF_LEDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_931201:
                        case ORDERFRM_931202:
                            createTitle(orderFrmTitleBuffer, THE_PREFIX, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LDECEMBER, DATE_1ST, YEAR_1993, SUF_LEDITION, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_940401:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, SINGLE_SEPARATOR, MONTH_APRIL, YEAR_1994, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_940601:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, SINGLE_SEPARATOR, MONTH_JUNE, YEAR_1994, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_940715:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, SINGLE_SEPARATOR, MONTH_JULY, YEAR_1994, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_941001:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_SHORT, SINGLE_SEPARATOR, MONTH_LOCTOBER, YEAR_1994, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_941101:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_SHORT, SINGLE_SEPARATOR, MONTH_LNOVEMBER, YEAR_1994, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                        case ORDERFRM_941221:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LDECEMBER, YEAR_1994, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_950201:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LFEBRUARY, YEAR_1995, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_950801:
                            createTitle(orderFrmTitleBuffer, "Apogee Software, Ltd. Order Form", SINGLE_SEPARATOR, "Aug '95", NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_951101:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LNOVEMBER, YEAR_1995, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_960101:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LJANUARY, YEAR_1996, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_960901:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, "Sept.", YEAR_1996, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_961201:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LDECEMBER, YEAR_1996, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_970522:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE, SINGLE_SEPARATOR, MONTH_LMAY, YEAR_1997, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_980421_OR_981205:
                            csum = checksum(orderFrmFileName);
                            if (csum == ORDERFRM_980421_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LMAY, YEAR_1998, NULL);
                                setModernOrderFrmTextStyle();
                            } else if (csum == ORDERFRM_981205_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LDECEMBER, YEAR_1998, NULL);
                                setModernOrderFrmTextStyle();
                            } else {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, NULL);
                                setBasicOrderFrmTextStyle();
                            }
                            break;
                        case ORDERFRM_990805:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LAUGUST, YEAR_1999, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_991102:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LNOVEMBER, YEAR_1999, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_000402:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LAPRIL, YEAR_2000, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_000421:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LAPRIL, DATE_21ST, YEAR_2000, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_000804:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LAUGUST, DATE_4TH, YEAR_2000, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_001004:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LOCTOBER, DATE_4TH, YEAR_2000, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_010307:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LMARCH, DATE_7TH, YEAR_2001, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_010424:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LAPRIL, DATE_24TH, YEAR_2001, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_010521:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LMAY, DATE_21ST, YEAR_2001, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_010731:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LJULY, DATE_31ST, YEAR_2001, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_011017A:
                        case ORDERFRM_011017B:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LOCTOBER, DATE_17TH, YEAR_2001, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_020507:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LMAY, DATE_7TH, YEAR_2002, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_021126_OR_021218:
                            csum = checksum(orderFrmFileName);
                            if (csum == ORDERFRM_021126_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LNOVEMBER, DATE_26TH, YEAR_2002, SUF_LREVISION, NULL);
                                setModernOrderFrmTextStyle();
                            } else if (csum == ORDERFRM_021218_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, MONTH_LDECEMBER, DATE_18TH, YEAR_2002, SUF_LREVISION, NULL);
                                setModernOrderFrmTextStyle();
                            } else {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, NULL);
                                setBasicOrderFrmTextStyle();
                            }
                            break;
                        case ORDERFRM_031106:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, "Nov", DATE_6TH, YEAR_2003, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_050921:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, "SEP", DATE_21ST, YEAR_2005, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_051021:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, "OCT", DATE_21ST, YEAR_2005, SUF_LREVISION, NULL);
                            setModernOrderFrmTextStyle();
                            break;
                        case ORDERFRM_060509_OR_090310:
                            csum = checksum(orderFrmFileName);
                            if (csum == ORDERFRM_060509_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, "MAY", "09,", YEAR_2006, SUF_LREVISION, NULL);
                                setModernOrderFrmTextStyle();
                            } else if (csum == ORDERFRM_090310_CHKSUM) {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_AP3DR, SINGLE_SEPARATOR, "MAR", DATE_10TH, YEAR_2009, SUF_LREVISION, NULL);
                                setModernOrderFrmTextStyle();
                            } else {
                                createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, NULL);
                                setBasicOrderFrmTextStyle();
                            }
                            break;
                        default:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, NULL);
                            setBasicOrderFrmTextStyle();
                            break;
                    }
                    return true;
                }
                case TYPE_PRINTME_EXE: {
                    switch (size) {
                        case PRINTME_910525:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_JUNE, YEAR_1991, NULL);
                            setOldBlueRedOrderFrmTextStyle();
                            orderFrmType = TYPE_PRINTME_EXE;
                            orderFrmFileName = ORDERFRM_NAMES[i];
                            return true;
                            break;
                        case PRINTME_910801:
                        case PRINTME_910801U:
                            createTitle(orderFrmTitleBuffer, ORDERFRM_TITLE_CAPS, DOUBLE_SEPARATOR, MONTH_AUGUST, YEAR_1991, NULL);
                            setOldDarkOrderFrmTextStyle();
                            orderFrmType = TYPE_PRINTME_EXE;
                            orderFrmFileName = ORDERFRM_NAMES[i];
                            return true;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    return false;
}

void showApogeeCatalog() {
    unsigned short errorCode;
    if (catalogFileName != NULL) {
        cleanup();
        switch (catalogType) {
            case TYPE_CATALOG_EXE:
                errorCode = spawnl(P_WAIT, catalogFileName, NULL);
                if (errorCode == -1) {
                    fprintf(stderr, EXEC_ERROR_MSG_F, catalogType, strerror(errno));
                    getPressedKey();
                }
                break;
            case TYPE_CATALOG_TXT:
                storeTextStyle();
                setStyle(catalogTextStyle, catalogLegendStyle, TEXT_LAYOUT_TRADITIONAL);
                showTextFile(catalogFileName, catalogTitleBuffer);
                restoreTextStyle();
                break;
            default:
                break;
        }
        drawMainLayout();
    }
}

void showApogeeOrderForm() {
    char* printBuffer = NULL;
    int bufferSize = 0;
    if (orderFrmFileName != NULL) {
        cleanup();
        storeTextStyle();
        setStyle(orderFrmTextStyle, orderFrmLegendStyle, orderFrmLayout);
        if (orderFrmType == TYPE_ORDER_FRM) {
            showTextFile(orderFrmFileName, orderFrmTitleBuffer);
        } else if (orderFrmType == TYPE_PRINTME_EXE) {
            printBuffer = parsePrintMe(orderFrmFileName, &bufferSize);
            if (printBuffer) {
                showTextBuffer(printBuffer, bufferSize, orderFrmTitleBuffer);
                free(printBuffer);
            }
        }
        restoreTextStyle();
        drawMainLayout();
    }
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

bool hasApogeeBBSInfo() {
    return fileExists(SWCBBS_FILENAME);
}

void showApogeeBBSInfo() {
    runExe(SWCBBS_FILENAME);
}

int hasApogeeDealersList() {
    for (int i = 0; i < NUM_DEALERS_TYPES; ++i) {
        if (fileExists(DEALERS_NAMES[i])) {
            dealersFileName = DEALERS_NAMES[i];
            dealersType = i;
            return i + 1;
        }
    }
    return false;
}

void showApogeeDealersList(const char* gameName) {
    char titleBuffer[80];
    if (dealersFileName != NULL) {
        if (dealersType == TYPE_DEALERS_EXE) {
            runExe(dealersFileName);
        } else if (dealersType == TYPE_FOREIGN_DOC) {
            cleanup();
            storeTextStyle();
            setStyle(TEXTCOLOR_CYAN|BGCOLOR_BLACK, TEXTCOLOR_BLACK|BGCOLOR_GRAY, TEXT_LAYOUT_TRADITIONAL);
            if (gameName != NULL) {
                strcpy(titleBuffer, gameName);
                strupr(titleBuffer);
                strcat(titleBuffer, " ");
                strcat(titleBuffer, FOREIGN_TITLE_CAPS);
            } else {
                strcpy(titleBuffer, gameName);
            }
            showTextFile(dealersFileName, titleBuffer);
            restoreTextStyle();
            drawMainLayout();
        }
    }
}

bool hasApogeeInstallationHelp() {
    return fileSize(INSTALLHELP_FILENAME) == INSTALLHELP_SIZE;
}

void showApogeeInstallationHelp() {
    runExe(INSTALLHELP_FILENAME);
}

static bool checkForSheet(const char* prefix, const char* suffix, char* dest) {
    char buffer[14];
    if (strlen(prefix) <= 3) {
        strcpy(buffer, prefix);
        strcat(buffer, "-");
        strcat(buffer, suffix);
        if (fileExists(buffer)) {
            strcpy(dest, buffer);
            return true;
        }
    }
    strcpy(buffer, prefix);
    strcat(buffer, suffix);
    if (fileExists(buffer)) {
        strcpy(dest, buffer);
        return true;
    }
    return false;
}

bool hasHintSheet(const char* prefix) {
    return checkForSheet(prefix, HINTSHEET_SUFFIX, hintSheetName);
}

bool hasHelpSheet(const char* prefix) {
    return checkForSheet(prefix, HELPSHEET_SUFFIX, helpSheetName);
}

void showHintSheet() {
    runExe(hintSheetName);
}

void showHelpSheet() {
    runExe(helpSheetName);
}

bool hasLicenseAgreement() {
    if (fileExists(LICENSE_FILENAME)) {
        return true;
    }
    long vendorSize = fileSize(VENDOR_FILENAME);
    if (vendorSize != -1 && (vendorSize != ID_VENDOR_LETTER_SIZE || checksum(VENDOR_FILENAME) != ID_VENDOR_LETTER_CSUM) && !fileExists("PSP.DOC")) {
        return true;
    }
    return false;
}

void showLicenseAgreement(const char *gameTitle, const char* version) {
    char buffer[80];
    long licenseSize = fileSize(LICENSE_FILENAME);
    long vendorSize = fileSize(VENDOR_FILENAME);
    cleanup();
    if (licenseSize == SHAREWARE_DIST_LIC_SIZE) {
        strcpy(buffer, TXT_SHAREWARE_DIST_AGREEMENT);
        showTextFile(LICENSE_FILENAME, buffer);
    } else if (licenseSize != -1 || vendorSize != -1) {
        createTitle(buffer, THE_PREFIX, gameTitle, version ? version : "", licenseSize != -1 ? TXT_SOFTWARE : TXT_SHAREWARE, TXT_LICENSE_AGREEMENT, NULL);
        showTextFile(licenseSize != -1 ? LICENSE_FILENAME : VENDOR_FILENAME, buffer);
    }
    drawMainLayout();
}

int populateApogeeSupportEntries(menuEntry* entry, const char* sheetPrefix, int skip) {
    int count = 0;
    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_INSTALL_HELP) && hasApogeeInstallationHelp()) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_INSTALL_HELP];
        entry->hotkey = KEY_I;
        entry->actionId = APOGEE_SUPPORT_ACTION_INSTALL_HELP;
        ++entry;
        ++count;
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_HELP) && sheetPrefix && hasHelpSheet(sheetPrefix)) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_HELP];
        entry->hotkey = KEY_T;
        entry->actionId = APOGEE_SUPPORT_ACTION_HELP;
        ++entry;
        ++count;
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_HINT) && sheetPrefix && hasHintSheet(sheetPrefix)) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_HINT];
        entry->hotkey = KEY_H;
        entry->actionId = APOGEE_SUPPORT_ACTION_HINT;
        ++entry;
        ++count;
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_LICENSE) && hasLicenseAgreement()) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_LICENSE];
        entry->hotkey = KEY_L;
        entry->actionId = APOGEE_SUPPORT_ACTION_LICENSE;
        ++entry;
        ++count;
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_CATALOG) && hasApogeeCatalog()) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_CATALOG];
        entry->hotkey = KEY_A;
        entry->actionId = APOGEE_SUPPORT_ACTION_CATALOG;
        ++entry;
        ++count;
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_DEALERS)) {
        int dealersType = hasApogeeDealersList();
        if (dealersType == 1) {
            entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_DEALERS];
            entry->hotkey = KEY_W;
            entry->actionId = APOGEE_SUPPORT_ACTION_DEALERS;
            ++entry;
            ++count;
        } else if (dealersType == 2) {
            entry->name = "Foreign Dealers";
            entry->hotkey = KEY_F;
            entry->actionId = APOGEE_SUPPORT_ACTION_DEALERS;
            ++entry;
            ++count;
        }
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_SWCBBS) && hasApogeeBBSInfo()) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_SWCBBS];
        entry->hotkey = KEY_S;
        entry->actionId = APOGEE_SUPPORT_ACTION_SWCBBS;
        ++entry;
        ++count;
    }

    if (!(skip & 1 << APOGEE_SUPPORT_ACTION_ORDERFRM) && hasApogeeOrderForm()) {
        entry->name = APOGEE_SUPPORT_ENTRY_NAMES[APOGEE_SUPPORT_ACTION_ORDERFRM];
        entry->hotkey = KEY_O;
        entry->actionId = APOGEE_SUPPORT_ACTION_ORDERFRM;
        ++entry;
        ++count;
    }
    return count;
}

void executeApogeeSupportEntry(int actionId, const char* oldName, const char* fullName, const char* version) {
    switch (actionId) {
        case APOGEE_SUPPORT_ACTION_INSTALL_HELP:
            showApogeeInstallationHelp();
            return;
        case APOGEE_SUPPORT_ACTION_HELP:
            showHelpSheet();
            return;
        case APOGEE_SUPPORT_ACTION_HINT:
            showHintSheet();
            return;
        case APOGEE_SUPPORT_ACTION_LICENSE:
            showLicenseAgreement(fullName, version);
            return;
        case APOGEE_SUPPORT_ACTION_CATALOG:
            showApogeeCatalog();
            return;
        case APOGEE_SUPPORT_ACTION_DEALERS:
            showApogeeDealersList(oldName);
            return;
        case APOGEE_SUPPORT_ACTION_SWCBBS:
            showApogeeBBSInfo();
            return;
        case APOGEE_SUPPORT_ACTION_ORDERFRM:
            showApogeeOrderForm();
            return;
    }
}

#ifndef RELEASE
void showMemoryDebugInfo() {
    cleanup();
    heapdump();
    getPressedKey();
    cleanup();
    mcbdump();
    getPressedKey();
    drawMainLayout();
}
#endif
