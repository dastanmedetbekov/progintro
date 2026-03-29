#include <stdio.h>
#include "c_plain.h"

int max_len = 0;
int max_len_i = 0;

void write_int(char *str, int b) {
    printf("%s %d\n", str, b);
}

void write_str(char *str, char *val) {
    printf("%s %s\n", str, val);
}

int get_len(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

void find_longest(int argc, char *argv[]) {
    for (int a = 1; a < argc; a++) {
        int current_len = get_len(argv[a]);
        if (current_len > max_len) {
            max_len = current_len;
            max_len_i = a;
        }
    }
}


// BBBBBBBBBBBB
//
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No arguments provided\n");
        return 0;
    }

    find_longest(argc, argv);
    nodubl(argc, argv);
    // C
    print_dom_dots(argc, argv);
    
    write_int("MAX LEN: ", max_len);
    write_str("THE LONGEST ARGUMENT IS: ", argv[max_len_i]);

    return 0;
}
