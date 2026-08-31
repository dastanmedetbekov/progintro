#define BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int can_print(unsigned char c) {
    if (c>= 32 && c <= 126) return 1;
    if (c == '\n' || c == '\t') return 1;
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }

    int port = atoi(argv[1]);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sockfd < 0) {
        perror("socket error");
        return 1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind error");
        close(sockfd);
        return 1;
    }

    printf("Listening %d...\n", port);

    unsigned char buffer[BUF_SIZE];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (1) {
        ssize_t bytes_received = recvfrom(
            sockfd,
            buffer,
            BUF_SIZE,
            0,
            (struct sockaddr *)&client_addr,
            &client_len
        );

        if (bytes_received < 0) {
            perror("ERROR recvfrom");
            break;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        int client_port = ntohs(client_addr.sin_port);

        printf("\n[From %s:%d, len: %zd b]: ", client_ip, client_port, bytes_received);

        for (ssize_t i = 0; i < bytes_received; i++) {
            if (can_print(buffer[i])) {
                putchar(buffer[i]);
            } else {
                putchar('?'); 
            }
        }
        printf("\n");
    }

    close(sockfd);
    
    return 0;
}
