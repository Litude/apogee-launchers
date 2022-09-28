#include <stdio.h>
#include <stdbool.h>
#include "intrpt.h"
#include "input.h"
#include "macro.h"


const unsigned char KEYCHAR_MAP[] = {
    '\0', '\e',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9', '10',  '-',  '=', '\b', '\t',
     'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',  'O',  'P',  '[',  ']', '\n', '\0',  'A',  'S',
     'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';', '\'',  '`', '\0', '\\',  'Z',  'X',  'C',  'V',
     'B',  'N',  'M',  ',',  '.',  '/', '\0'
};

int getPressedKey() {
    int scancode = 0;
    _asm {
        mov ah, BIOS_KEYBOARD_EXTENDED_CHARACTER
        int INTERRUPT_BIOS_KEYBOARD
        mov byte ptr [scancode], ah
        cmp al, 0xE0
        jnz end
        mov byte ptr [scancode+1], al
        end:
    }
    return scancode;
}

struct keystroke getPressedKeyDetailed() {
    unsigned char scancode, character;
    struct keystroke result;
    _asm {
        mov ah, BIOS_KEYBOARD_EXTENDED_CHARACTER
        int INTERRUPT_BIOS_KEYBOARD
        mov scancode, ah
        mov character, al
    }
    result.scancode = character == 0xE0 ? 0xE000 | (int)scancode : scancode;
    result.character = character == 0xE0 ? 0 : character;
    return result;
}

// bool hasWaitingInput() {
//     unsigned int waiting = 0;
//     _asm {
//         mov ah, BIOS_KEYBOARD_EXTENDED_STATUS 
//         int INTERRUPT_BIOS_KEYBOARD
//         mov dx, 0
//         jz end
//         mov dx, 1
//         end:
//         mov waiting, dx
//     }
//     return waiting;
// }
