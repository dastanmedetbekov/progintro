#include <stdio.h>

int find_sim(char *s) {
    char first = s[0];

    for (int i = 1; s[i] != '\0'; i++) {
        if (s[i] != first) {
            return 1;
        }
    }
    return 0;
}

void print_sim_only(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!find_sim(argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
}
