#include <stdbool.h>
#include "../lib/menu.h"
#include "../version.h"

#define INSTRUCTIONS_APOGEE

extern const char* APOGEE_SUPPORT_ENTRY_NAMES[];

int populateApogeeSupportEntries(menuEntry* entry, const char* sheetPrefix, int skip);
void executeApogeeSupportEntry(int actionId, const char* oldName, const char* fullName, const char* version);
bool hasApogeeCatalog();
void showApogeeCatalog();
bool hasApogeeOrderForm();
void showApogeeOrderForm();
bool hasApogeeBBSInfo();
void showApogeeBBSInfo();
int hasApogeeDealersList();
void showApogeeDealersList(const char* gameName);
bool hasApogeeInstallationHelp();
void showApogeeInstallationHelp();
bool hasHintSheet(const char* prefix);
bool hasHelpSheet(const char* prefix);
void showHintSheet();
void showHelpSheet();
bool hasLicenseAgreement();
void showLicenseAgreement(const char *gameTitle, const char* version);
#ifndef RELEASE
void showMemoryDebugInfo();
#endif
