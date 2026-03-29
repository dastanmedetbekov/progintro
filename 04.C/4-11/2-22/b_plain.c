#include <stdio.h>

int has_internal_duplicates(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        for (int j = i + 1; s[j] != '\0'; j++) {
            if (s[i] == s[j]) {
                return 1; 
            }
        }
    }
    return 0; 
}

void nodubl(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!has_internal_duplicates(argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
}
