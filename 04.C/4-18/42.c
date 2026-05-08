#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **words; 
    int count;      
    int capacity;  
} word_list;

int main() 
{
    int c;
    word_list list = {NULL, 0, 0};
    char *current_word = NULL;
    int word_len = 0;
    int word_cap = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n')
        {
            if (current_word != NULL)
            {
                current_word[word_len] = '\0';

                if (list.count >= list.capacity)
                {
                    list.capacity = (list.capacity == 0) ? 10 : list.capacity * 2;
                    list.words = realloc(list.words, list.capacity * sizeof(char *));
                }
                list.words[list.count++] = current_word;

                current_word = NULL;
                word_len = 0;
                word_cap = 0;
            }
            if (c == '\n')
            {
                for (int i = list.count - 1; i >= 0; i--) {
                    printf("%s%s", list.words[i], (i == 0) ? "" : " ");
                }
                printf("\n");
                
                for (int i = 0; i < list.count; i++) {
                    free(list.words[i]);
                }
                free(list.words);
                
                list.words = NULL;
                list.count = 0;
                list.capacity = 0;
            }
        } 
        else 
        {
            if (word_len + 1 >= word_cap)
            {
                word_cap = (word_cap == 0) ? 10 : word_cap * 2;
                current_word = realloc(current_word, word_cap * sizeof(char));
            }
            current_word[word_len++] = (char)c;
        }
    }
    if (current_word) free(current_word);
    for (int i = 0; i < list.count; i++) free(list.words[i]);
    free(list.words);

    return 0;
}
