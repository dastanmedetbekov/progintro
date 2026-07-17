#include <stdio.h>

int main(int argc, char **argv) {
    if (argv[1] == NULL) {
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        return 1;
    }
    
    char buffer[256];
    
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        fputs(buffer, stdout);
    }
    fclose(file);
    return 0;
}
