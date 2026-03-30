#include <stdio.h>

int find_num(char *s) {

    for (int i = 0; s[i] != '\0'; i++) {
        if (!(s[i] >= '0' && s[i] <= '9')) {
            return 1;
        }
    }
    return 0;
}

void print_num_only(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!find_num(argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
}
