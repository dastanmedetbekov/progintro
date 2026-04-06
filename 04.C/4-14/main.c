#include <stdio.h>

int main() {
    char c;
    printf("HELLO! please, write!\n");
    while((c = getchar()) != '\n') {
        if (c != ' ') {
            putchar(c);
        }
    }
    return 0;

}
