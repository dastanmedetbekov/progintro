#include <stdio.h>

int c, first, second, i;

void zero() {
    first = 0;
    second = 0;
    i = 0;
}

void match() {
    if (i == 2) {
        putchar(first);
        putchar(second);
    }
}

int main() {
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ') {
            match();
            putchar(c);
            zero();
        } else {
            ++i;
            if (i == 1) first = c;
            else if (i == 2) second = c;
        }
    }
    match(); 
    return 0;
}
