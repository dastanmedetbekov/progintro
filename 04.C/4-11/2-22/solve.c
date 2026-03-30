#include <stdio.h>
#include "c_plain.h"
#include "b_plain.h"
#include "d_plain.h"
#include "e_plain.h"
#include "f_plain.h"
#include "g_plain.h"

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
    // A
    printf("A) find the longest one\n");
    find_longest(argc, argv);
    write_int("MAX LEN: ", max_len);
    write_str("THE LONGEST ARGUMENT IS ", argv[max_len_i]);
    // B
    printf("B) no dublicates\n");
    nodubl(argc, argv);
    // C
    printf("C) finding arguments with a @ and no matter how many dots\n");
    print_dom_dots(argc, argv);
    // D
    printf("D) finding only argument containing only same number\n");
    print_num_only(argc, argv);
    // E
    printf("E) has same char\n");
    print_sim_only(argc, argv);
    // F
    printf("F) has latin\n");
    print_latin_only(argc, argv);
    // G
    printf("G) has one or more same characters with first argumunt\n");
    print_same_with_first_only(argc, argv);

    return 0;
}
