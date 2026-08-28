#include <stdio.h>
#include <arpa/inet.h>
#include <stdint.h>


int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    
    uint32_t ip;
    int res = inet_pton(AF_INET, argv[1], &ip);
    if (res != 1) {
        return 1;
    }

    ip = ntohl(ip);

    for (int len = 0; len <= 32; len++) {
        uint32_t mask = (len == 0) ? 0 : (0xFFFFFFFFU << (32 - len));

        uint32_t net = ip & mask;

        uint32_t net_be = htonl(net);

        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &net_be, str, sizeof(str));

        printf("%s/%d\n", str, len);
    }

    return 0;
}
