#include <stdio.h>

int get_and_zero(int *p) 
{
	int old_value = *p;
	*p = 0;
	return old_value;
}

int main() 
{
	int integer = 5;
	printf("This is %d\n", get_and_zero(&integer));
	printf("Old is now is %d\n", integer); 
}
