#include <stdio.h>

int is_same(char *first, char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        for (int j = 0; first[j] != '\0'; j++) {
            if (first[j] == s[i]) {
                return 0;
            }
        }
    }
    return 1;
}

void print_same_with_first_only(int argc, char **argv) {
    char *first;

    for (int i = 1; i < argc; i++) {
        if (i == 1) {
            first = argv[i];
        }
        else if (!is_same(first, argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
}
