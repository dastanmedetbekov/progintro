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
        new_buf[i] = old_buf[i]);
    }
    free(old_buf);
    return new_buf;
}

static char **grow_words_array(char **old_arr, size_t old_cap, sizi_t new_cap)
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

int main(void) {

}
    
