#include <stdio.h>

double m[] = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0};
double *p = &m[2];

int main() {
    printf("%g\n", *p);
    printf("%g\n", *(p+1));
    printf("%g\n", 3[p]);
}
