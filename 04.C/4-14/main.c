#include <stdio.h>

void clean_spaces(char *s) {
    int j = 0;;
    for (int i = 0; s[i] != '\0'; i++) {
        if (i[s] != ' ') {
            j[s] = i[s];
            j++;
        }
    }
    j[s] = '\0';
}

int main() {
    char str[] = "Hell o W o r l d th is the game ! ! ! !";
    clean_spaces(str);
    printf("%s\n", str);

}
