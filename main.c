
#include <stdio.h>
#include "commands.h"


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    copy(argv[1], argv[2]);
    return 0;
}