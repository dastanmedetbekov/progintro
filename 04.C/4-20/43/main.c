#include <stdio.h>
#include <stdlib.h>

// I will use old code from 4.20->2.42 to solve this task
// I will just change the way it prints strokes.

static char *grow_char_buffer(char *old_buf, size_t old_cap, size_t new_cap)
{
    char *new_buf = malloc(new_cap * sizeof(char));
    if (new_buf == NULL) {
        exit(1);
    }
    size_t i;
    for (i = 0; i < old_cap; i++) {
        new_buf[i] = old_buf[i];
    }
    free(old_buf);
    return new_buf;
}

static char **grow_words_array(char **old_arr, size_t old_cap, size_t new_cap)
{
    char **new_arr = malloc(new_cap * sizeof(char *));
    if (new_arr == NULL) {
        exit(1);
    }

    size_t i;
    for (i = 0; i < old_cap; i++) {
        new_arr[i] = old_arr[i];
    }
    free(old_arr);
    return new_arr;
}

static void finish_word(char **word_buf, size_t *word_len, size_t *word_cap, char ***words, size_t *words_count, size_t *words_cap)
{
    if (*word_len + 1 > *word_cap) {
        size_t new_cap = (*word_cap == 0) ? 1 : (*word_cap) * 2;
        *word_buf = grow_char_buffer(*word_buf, *word_cap, new_cap);
        *word_cap = new_cap;
    }
    (*word_buf)[*word_len] = '\0';

    if (*words_count + 1 > *words_cap) {
        size_t new_wcap = (*words_cap == 0) ? 1 : (*words_cap) * 2;
        *words = grow_words_array(*words, *words_cap, new_wcap);
        *words_cap = new_wcap;
    }
    (*words)[*words_count] = *word_buf;
    (*words_count)++;
    
    *word_buf = NULL;
    *word_len = 0;
    *word_cap = 0;
}

// should write this here
size_t my_strlen(const char *str); 

static void flush_vertical_line(char **words, size_t words_count)
{
    
    putchar('\n');

    size_t max_len = 0;
    // for checking max len
    for (int i = 0; i < words_count; i++) {
        size_t temp = my_strlen(words[i]);
        if (temp > max_len) {
            max_len = temp;
        }
    }
    for (size_t i = 0; i < max_len; i++) 
    {
        for (size_t y = 0; y < words_count; y++) {
            
            if (my_strlen(words[y]) > i) {
                putchar(words[y][i]);
            }
            else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}


size_t my_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}



int main(void)
{
    int c;

    char *word_buf = NULL;   
    size_t word_len = 0;     
    size_t word_cap = 0;     

    char **words = NULL;     
    size_t words_count = 0;
    size_t words_cap = 0;

    int in_word = 0;         

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            if (in_word) {
                finish_word(&word_buf, &word_len, &word_cap,
                            &words, &words_count, &words_cap);
                in_word = 0;
            }

            flush_vertical_line(words, words_count);
            for (size_t i = 0; i < words_count; i++) {
                free(words[i]);
            }
            free(words);
            words = NULL;
            words_count = 0;
            words_cap = 0;
        }
        else if (c == ' ' || c == '\t') {
            if (in_word) {
                finish_word(&word_buf, &word_len, &word_cap,
                            &words, &words_count, &words_cap);
                in_word = 0;
            }
        }
        else {
            if (word_len + 1 > word_cap) {
                size_t new_cap = (word_cap == 0) ? 1 : word_cap * 2;
                word_buf = grow_char_buffer(word_buf, word_cap, new_cap);
                word_cap = new_cap;
            }
            word_buf[word_len] = (char)c;
            word_len++;
            in_word = 1;
        }
    }

    if (in_word) {
        finish_word(&word_buf, &word_len, &word_cap,
                    &words, &words_count, &words_cap);
    }
    if (words_count > 0) {
        flush_vertical_line(words, words_count);
        for (size_t i = 0; i < words_count; i++) {
            free(words[i]);
        }
        free(words);
    }

    return 0;
} 
