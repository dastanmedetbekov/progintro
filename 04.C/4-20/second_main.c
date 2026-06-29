#include <stdio.h>
#include <stdlib.h>

void das_malloc(char **str_ptr, size_t *capacity_ptr, size_t current_length) {
    *capacity_ptr = (*capacity_ptr) * 2;
    char *new_str = malloc(*capacity_ptr * sizeof(char));
    if (new_str == NULL) {
        return 1;
    }

    memcpy(new_str, *str_ptr, current_length);
    free(*str_ptr);
    *str_ptr = new_str;
}

void print_reverse(char **words, size_t count) {
    for (size_t i = count; i > 0; i--) {
        printf("%s ", words[i - 1]);
        free(words[i - 1]);
    }
    printf("\n");
}

int main() {
    return 0;
}
