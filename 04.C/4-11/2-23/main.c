#include <stdio.h>

void print_words(char *s)
{
    int in_word = 0;
    int count = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != ' ' && in_word == 0)
        {
            count++;
            in_word = 1;
        }
        else if (s[i] == ' ')
        {
            in_word = 0;
        }
    }

    printf("%d\n", count);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    print_words(argv[1]);
    return 0;
}
