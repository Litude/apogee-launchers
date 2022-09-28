#include <stdbool.h>
#include "../lib/menu.h"

#define INSTRUCTIONS_PSA

int populatePrecisionSoftwareSupportEntries(menuEntry* entry, int skip);
void executePrecisionSoftwareSupportEntry(int actionId);
bool hasPrecisionSoftwareCatalog();
bool hasPrecisionSoftwareOrderForm();
bool hasPrecisionSoftwareLicenseAgreement();
void showPrecisionSoftwareCatalog();
void showPrecisionSoftwareOrderForm();
void showPrecisionSoftwareLicenseAgreement();
