#include <stdio.h>

char find(char *s, char *dest) {

}

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    for (int i = 3; i < argc; i++) {
        find(argv[i], argv[2]);
    }


    return 0;
}
