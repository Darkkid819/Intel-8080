#include <stdio.h>
#include <string.h>

#define SDL_MAIN_HANDLED

#include "hexdump.h"
#include "disassembler.h"
#include "emulator.h"
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <option> <ROM file>\n", argv[0]);
        printf("Options:\n");
        printf("  dump        Hex dump the ROM file\n");
        printf("  disassemble Disassemble the ROM file\n");
        printf("  run         Run the ROM on the CPU\n");
        return 1;
    }

    const char *option = argv[1];
    const char *filename = argv[2];

    if (!strcmp(option, "dump")) {
        return hexdump(filename);
    } else if (!strcmp(option, "disassemble")) {
        disassembleROM(filename);
        return 0;
    } else if (!strcmp(option, "run")) {
        initializeIO();
        Emulator emulator;
        initializeEmulator(&emulator);
        runEmulator(&emulator);
        freeEmulator(&emulator);
        shutdownIO();
        return 0;
    } else {
        printf("Unknown option: %s\n", option);
        return 1;
    }
}
