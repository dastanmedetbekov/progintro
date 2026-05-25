#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t lenght;
    size_t capacity;
} sequence_digit;

typedef struct {
    sequence_digit *sequences;
    size_t count;
    size_t capacity;
} sequence_list;

void init_seq(sequence_digit *s) {
    s->data = NULL;
    s->lenght = 0;
    s->capacity = 0;
}

void append_char_seq(sequence_digit *s, char c) {
    if (s->capacity == 0) {
        s->capacity = 4;
        s->data = realloc(s->data, s->capacity * sizeof(char));
    }
    else if (s->lenght >= s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(char));
    }
    s->data[s->lenght] = c;
    s->lenght++;
}

void init_list(sequence_list *l) {
    l->sequences = NULL;
    l->count = 0;
    l->capacity = 0;
}

void append_list(sequence_list *l, sequence_digit s) {
    if (l->capacity == 0) {
        l->capacity = 4;
        l->sequences = realloc(l->sequences, l->capacity * sizeof(sequence_digit));
    }
    else if (l->count >= l->capacity) {
        l->capacity *= 2;
        l->sequences = realloc(l->sequences, l->capacity * sizeof(sequence_digit));
    }
    l->sequences[l->count] = s;
    l->count++;
}

void free_seq(sequence_digit *s) {
    if (s->data != NULL) {
        free(s->data);
        s->data = NULL;
    }
    s->lenght = 0;
    s->capacity = 0;
}

void free_list(sequence_list *l) {
    if (l->sequences != NULL) {
        for (size_t i = 0; i < l->count; i++) {
            free_seq(&(l->sequences[i]));
        }
        free(l->sequences);
        l->sequences = NULL;
    }
    l->count = 0;
    l->capacity = 0;
}

void print_list(sequence_list *l) {
    for (size_t i = 0; i < l->count; i++) {
        for (size_t j = 0; j < l->sequences[i].lenght; j++) {
            putchar(l->sequences[i].data[j]);
        }
        if (i < l->count - 1) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int main() {
    int ch;
    sequence_list list;
    sequence_digit current_seq;

    init_list(&list);
    init_seq(&current_seq);

    size_t max_len = 0;
    int in_seq = 0;

    while ((ch = getchar()) != EOF) {
        if (ch >= '0' && ch <= '9') {
            append_char_seq(&current_seq, (char)ch);
            in_seq = 1;
        }
        else {
            if (in_seq) {
                if (current_seq.lenght > max_len) {
                    free_list(&list); 
                    init_list(&list);
                    max_len = current_seq.lenght;
                    append_list(&list, current_seq);
                }
                else if (current_seq.lenght == max_len && max_len > 0) {
                    append_list(&list, current_seq);
                }
                else {
                    free_seq(&current_seq); 
                }
                init_seq(&current_seq);
                in_seq = 0;
            }

            if (ch == '\n') {
                if (list.count > 0) {
                    print_list(&list);
                }
                free_list(&list);
                init_list(&list);
                max_len = 0;
            }
        }
    }

    if (in_seq) {
        if (current_seq.lenght > max_len) {
            free_list(&list);
            init_list(&list);
            max_len = current_seq.lenght;
            append_list(&list, current_seq);
        } else if (current_seq.lenght == max_len && max_len > 0) {
            append_list(&list, current_seq);
        } else {
            free_seq(&current_seq);
        }
    }

    if (list.count > 0) {
        print_list(&list);
    }

    free_list(&list);
    return 0;
}
