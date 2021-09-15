#include <stdbool.h>
#include "intrpt.h"

#define KEY_ESCAPE 0x01
#define KEY_BACKSPACE 0x0E
#define KEY_ENTER 0x1C
#define KEY_SPACEBAR 0x39

#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_0 0x0B

#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25

#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C

#define KEY_HOME 0xE047
#define KEY_PAGE_UP 0xE049
#define KEY_END 0xE04F
#define KEY_PAGE_DOWN 0xE051
#define KEY_ARROW_UP 0xE048
#define KEY_ARROW_LEFT 0xE04B
#define KEY_ARROW_RIGHT 0xE04D
#define KEY_ARROW_DOWN 0xE050

struct keystroke {
    int scancode;
    unsigned char character;
};

extern const char KEYCHAR_MAP[];

int getPressedKey();
struct keystroke getPressedKeyDetailed();

bool hasWaitingInput();
#pragma aux hasWaitingInput = \
    ASM(xor cl, cl) \
    ASM(mov ah, BIOS_KEYBOARD_EXTENDED_STATUS) \
    ASM(int INTERRUPT_BIOS_KEYBOARD) \
    ASM(jz end) \
    ASM(mov cl, 1) \
    ASM(end:) \
    value [cl] \
    modify [ax];

long getTime();
#pragma aux getTime = \
    ASM(mov ah, DOS_GET_TIME) \
    ASM(int INTERRUPT_DOS) \
    value [cx dx] \
    modify [ah];
