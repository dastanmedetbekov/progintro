#include <stdio.h>

int p = 0;

void counter(char *c) 
{
	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] == ' ') {
			p = p + 1;	
		}
	}
}

int main()
{

	char *cow = "Hello I am currently searching place to eat more and more things, like grasses etc..";
	counter(cow);
    	printf("RESULT IS %d\n", p);
    	return 0;
}


