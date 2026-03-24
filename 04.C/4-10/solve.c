#include <stdio.h>

// arguments counter = argc
// arguments massiv = argv
int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			printf("%s \n", argv[i]);
		}
	}
	return 0;
}
