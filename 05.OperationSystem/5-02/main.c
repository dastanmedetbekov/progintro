#include <stdio.h>
#include <stdlib.h>

#define SIXTYFOUR 64

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("error, no accepted value\n");
        return 1;
    }
    
    printf("%s\n", argv[1]);

    return 0;
}

