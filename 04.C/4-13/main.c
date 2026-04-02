#include <stdio.h>

long long n, m;

void looperman() {
    for (int i = 0; ; i++) {

    }
}

void get_char() {
    printf("Please, write where we should start to count: ");
    scanf("%lld", &n);
    printf("\n Please, write where we should stop to count: ");
    scanf("%lld", &m);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    n = argv[1];
    m = argv[2];
}
