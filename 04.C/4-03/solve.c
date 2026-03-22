#include <stdio.h>

int i = 493;

int main() 
{
	printf("|%d|:|%6d|:|%-6d|:|%06d|:|%7.5d|\n", i, i, i, i, i);
	return 0;
}
