#include <stdio.h>

int put_sum(int *p, int *q, int *w) 
{
	int sum = *p + *q + *w;
	*p = sum;
	*q = sum;
	*w = sum;
	return sum;
}

int main() 
{
	int a = 5;
	int b = 27;
	int c = 5345;
	printf("A = %d, B = %d, C = %d\n", a, b, c);
	printf("%d is the sum of 3 values\n", put_sum(&a, &b, &c));
	printf("A is %d, B is %d, C is %d\n", a, b, c);
	printf("WE CAN`T KNOW WHERE IS OLD SYMBOLS\n");
}
