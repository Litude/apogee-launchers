#include <string.h>
#include "args.h"

bool hasArgument(const char* argument, const char** args) {
    for (int i = 1;; ++i) {
        const char* current = args[i];
        if (current) {
            // Skip prefix character
            if (current[0] == '/' || current[0] == '-') {
                current = &current[1];
            }
            if (!stricmp(current, argument)) {
                return true;
            }
        }
        else {
            break;
        }
    }
    return false;
}
