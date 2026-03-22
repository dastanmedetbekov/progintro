#include <stdio.h>

int p = 0;
// deleted all old code to do the new thing
// sad cow ^-^

int counter(char *c) {
	if (*c == '\0')
		return 0;
	if (*c == ' ')
		p = p + 1;
    	return counter(c + 1);
}
int main()
{

	char *cow = "Hello I am currently searching place to eat more and more things, like grasses etc..";
	counter(cow);
    	printf("RESULT IS %d\n", p);
    	return 0;
}


