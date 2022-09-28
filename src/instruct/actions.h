// Don't add a header guard here, multiple inclusions of this would probably result in a bad executeCommonSupportEntry

enum APOGEE_SUPPORT_ACTION {
    APOGEE_SUPPORT_ACTION_INSTALL_HELP,
    APOGEE_SUPPORT_ACTION_HELP,
    APOGEE_SUPPORT_ACTION_HINT,
    APOGEE_SUPPORT_ACTION_LICENSE,
    APOGEE_SUPPORT_ACTION_CATALOG,
    APOGEE_SUPPORT_ACTION_DEALERS,
    APOGEE_SUPPORT_ACTION_SWCBBS,
    APOGEE_SUPPORT_ACTION_ORDERFRM,
    NUM_APOGEE_SUPPORT_ACTIONS,
};

enum IDSOFT_SUPPORT_ACTION {
    IDSOFT_SUPPORT_ACTION_GREETINGS = NUM_APOGEE_SUPPORT_ACTIONS,
    IDSOFT_SUPPORT_ACTION_VENDOR_LETTER,
    NUM_IDSOFT_SUPPORT_ACTIONS,
};

enum PSA_SUPPORT_ACTION {
    PSA_SUPPORT_ACTION_LICENSE = NUM_IDSOFT_SUPPORT_ACTIONS,
    PSA_SUPPORT_ACTION_CATALOG,
    PSA_SUPPORT_ACTION_ORDERFRM,
    NUM_PSA_SUPPORT_ACTIONS,
};

#define CUSTOM_SUPPORT_ACTION_START NUM_PSA_SUPPORT_ACTIONS

inline void executeCommonSupportEntry(int actionId, const char* oldName, const char* fullName, const char* version) {
    #ifdef INSTRUCTIONS_APOGEE
        if (actionId < NUM_APOGEE_SUPPORT_ACTIONS) {
            executeApogeeSupportEntry(actionId, oldName, fullName, version);
        } else
    #endif
    #ifdef INSTRUCTIONS_IDSOFT
        if (actionId >= NUM_APOGEE_SUPPORT_ACTIONS && actionId < NUM_IDSOFT_SUPPORT_ACTIONS) {
            executeIdSoftwareSupportEntry(actionId);
        } else
    #endif
    #ifdef INSTRUCTIONS_PSA
        if (actionId >= NUM_IDSOFT_SUPPORT_ACTIONS && actionId < NUM_PSA_SUPPORT_ACTIONS) {
            executePrecisionSoftwareSupportEntry(actionId);
        } else
    #endif
    {}
}
