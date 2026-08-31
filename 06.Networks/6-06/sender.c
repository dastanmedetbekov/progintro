#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Starting: %s <IP> <port> <msg>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    char *message = argv[3];

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("ERROR socket");
        return 1;
    }

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &dest_addr.sin_addr);

    ssize_t sent = sendto(
        sockfd,
        message,
        strlen(message),
        0,
        (struct sockaddr *)&dest_addr,
        sizeof(dest_addr)
    );

    if (sent < 0) {
        perror("ERROR sendto");
    } else {
        printf("Sent %zd b.\n", sent);
    }

    close(sockfd);
    return 0;
}
