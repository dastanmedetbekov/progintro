#include <stdio.h>

int main(int argc, char **argv) {
    if (argv[1] == NULL) {
        printf("There is no a file");
        return 1;
    }

    FILE *file = fopen(argv[1], "w");
    
    if (file == NULL) {
        printf("There is no a file");
        return 1;
    }

    fputs("Humpty Dumpty sat on a wall,\nHumpty Dumpty had a great fall.\nAll the king's horses and all the king's men\nCouldn't put Humpty together again.\n", file);

    if (fclose(file) == 0) {
        return 0;
    }
    else {
        printf("Can't close the file");
        return 1;
    }

    return 0;
}
