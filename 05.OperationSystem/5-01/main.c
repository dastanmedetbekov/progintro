#define _GNU_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    off64_t size = lseek64(fd, 0, SEEK_END);
    if (size == -1) {
        close(fd);
        printf("ERROR");
        return 1;
    }
    printf("%ld\n", size);
    close(fd);
    return 0;
}
