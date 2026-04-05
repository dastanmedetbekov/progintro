#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    long long N = atoll(argv[1]);
    long long M = atoll(argv[2]);

    if (N > M) {
        return 0;
    }

    long long current_pos = 0;
    long long i = 1;
    char buffer[64];

    while (current_pos < M) {
        long long square = i * i;
        sprintf(buffer, "%lld", square);
        int len = strlen(buffer);

        for (int j = 0; j < len; j++) {
            current_pos++;
            if (current_pos >= N && current_pos <= M) {
                putchar(buffer[j]);
            }
            if (current_pos >= M) {
                break;
            }
        }
        i++;
    }

    putchar('\n');
    return 0;
}
