#include <stdio.h>

int main(int argc, char **argv) {
    if (argv[1] == NULL) {
        return 0;
    }

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        return 1;
    }
    
    char buffer[256];
    
    while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
        fputs(buffer, file);
    }
    fclose(file);
    return 0;
}
