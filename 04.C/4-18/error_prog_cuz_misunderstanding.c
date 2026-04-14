#include <stdio.h>

int checker(char *src, char checked) {
    for (int i = 0; src[i] != '\0'; i++) {
        if (checked == src[i]) {
            return 1;
        }
    }
}

char tenten[10];

int main() 
{
    // vars
    long var;
    char buf[32];
    int massive_num = 0;
    char massive_con[10];
    
    // main functionf. first getting in and transform to char, so can 
    scanf("%ld", &var);
    sprintf(buf, "%ld", var);

    // first iteration
    for (int i = 0; buf[i] != '\0'; i++) {
        counter = 0;
        // second iteration
        for (int j = 0; buf[j] != '\0'; j++) {
            if(buf[i] == buf[j]) {
                ++counter;
            }
            if(counter > 3) {
                break;
            }
        }
        if (counter == 3 && checker(massive_num, buf[i]) == 0) {
            putchar(buf[i]);
            massive_con[massive_num] = buf[i];
        }
    }
    return 0;
}
