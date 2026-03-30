#include <stdio.h> 

int is_latin(char *s) {
    for (int i = 1; s[i] != '\0'; i++) {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')) {
            return 0;
        }
    }
    return 1;
}

void print_latin_only(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if(!is_latin(argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
}
