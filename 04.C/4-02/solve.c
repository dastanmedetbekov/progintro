#include <stdio.h>

enum en25 { alpha = 25, beta, gamma = beta * 10, delta };

int main() 
{
	printf("alpha is %d\n", alpha);
	printf("beta is %d\n", beta);
	printf("gamma is beta * 10 is %d\n", gamma);
	printf("delta is %d\n", delta);
	return 0;
}
