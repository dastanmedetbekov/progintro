#include <stdio.h>

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No arguments provided\n");
        return 0;
    }

    find_longest(argc, argv);
    
    write_int("MAX LEN: ", max_len);
    write_str("THE LONGEST ARGUMENT IS: ", argv[max_len_i]);

    return 0;
}
