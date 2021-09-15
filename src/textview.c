#include <stdio.h>
#include <stdlib.h>
#include "lib/text.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: TEXTVIEW [TEXTFILE]\n");
        return EXIT_SUCCESS;
    }

    showTextFile(argv[1], argv[1]);
    return EXIT_SUCCESS;
}
