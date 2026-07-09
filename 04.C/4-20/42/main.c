#include <stdio.h>
#include <stdlib.h>

static char *grow_char_buffer(char *old_buf, size_t old_cap, size_t new_cap)
{
    char *new_buf = malloc(new_cap * sizeof(char));
    if (new_buf == NULL) {
        exit(1);
    }
    size_t i;
    for (i = 0; i < old_cap; i++) {
        new_buf[i] = old_buf[i]);
    }
    free(old_buf);
    return new_buf;
}

static char **grow_words_array(char **old_arr, size_t old_cap, sizi_t new_cap)
{
    char **new_arr = malloc(new_cap * sizeof(char *));
    
