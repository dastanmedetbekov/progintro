#include <stdio.h>
#include <stdlib.h>

static char *grow_char_buffer(char *old_buf, size_t old_cap, size_t new_cap)
{
    char *new_buf = malloc(new_cap * sizeof(char));
    // checking if there any NEW_BUF
    if (new_buf == NULL) {
        fprintf(stderr, "ERROR\n"); // error printer
        exit(1);
    }
    size_t i; // creating I to use it on FOR.
    for (i = 0; i < old_cap; i++) {
        new_buf[i] = old_buf[i];
    }
    // I changed it from memcpy to for
    free(old_buf);
    return new_buf;
}

// adding words to words array and if there no place to put new words it gets new place to grow
static char **grow_words_array(char **old_arr, size_t old_cap, size_t new_cap)
{
    char **new_arr = malloc(new_cap * sizeof(char *));
    if (new_arr == NULL) {
        fprintf(stderr, "ERROR\n");
        exit(1);
    }
    size_t i;
    for (i = 0; i < old_cap; i++) {
        new_arr[i] = old_arr[i];
    }
    free(old_arr);
    return new_arr;
}

static void finish_word(char **word_buf, size_t *word_len, size_t *word_cap,
                         char ***words, size_t *words_count, size_t *words_cap)
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

static void flush_line(char **words, size_t words_count)
{
    size_t i;
    for (i = words_count; i > 0; i--) {
        printf("%s", words[i - 1]);
        if (i - 1 > 0) {
            printf(" ");
        }
    }
    printf("\n");

    for (i = 0; i < words_count; i++) {
        free(words[i]);
    }
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

            flush_line(words, words_count);
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
        flush_line(words, words_count);
        free(words);
    }

    return 0;
}
