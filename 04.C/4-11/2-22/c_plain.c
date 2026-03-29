#include <stdio.h>
// For solving c questions
int find_dom_dots(char *s) {
    int dom_count = 0;
    int dot_count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '@') dom_count++;
        if (s[i] == '.') dot_count++;
    }

    return (dom_count == 1 && dot_count >= 1);
}

void print_dom_dots(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (find_dom_dots(argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
}
