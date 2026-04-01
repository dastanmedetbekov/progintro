#include <stdio.h>

char* find(char *str, char *dest) {
    if (*dest == '\0') {
        return (char*)str;
    }

    for(; *str; str++) {
        int count = 0;

        char *s = str;
        char *t = dest;

        while(*s && *t && *s == *t) {
            s++;
            t++;
        }

        if (*t == '\0') {
            return (char*)str;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    for (int i = 2; i < argc; i++) {
        char* tester;
        tester = find(argv[i], argv[1]);
        if (tester != NULL) {
            printf("%s\n", argv[i]);
        }
    }
    printf("=+=+=+=\n");

    char *sub = argv[1];

    for (int i = 2; i < argc; i++) {
        int count = 0;
        char *pos = argv[i];
        while ((pos = find(pos, sub)) != NULL) {
            count++;
            pos++;
        }

        if (count > 0) {
            printf("%s: %d\n", argv[i], count);
        }
    }


    return 0;
}
