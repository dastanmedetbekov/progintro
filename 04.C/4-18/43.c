#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t lenght;
    size_t capacity;
} Word;

typedef struct {
    Word *words;
    size_t count;
    size_t capacity;
} Line;

void init_word(Word *w) {
    w->data = NULL;
    w->lenght = 0;
    w->capacity = 0;
}

void append_char(Word *w, char c) {
    if (w->capacity == 0) {
        w->capacity = 4;
        w->data = realloc(w->data, w->capacity * sizeof(char));
    }
    else if (w->lenght >= w->capacity) {
        w->capacity *= 2;
        w->data = realloc(w->data, w->capacity * sizeof(char));
    }

    w->data[w->lenght] = c;
    w->lenght++;
}

void init_line(Line *l) {
    l->words = NULL;
    l->count = 0;
    l->capacity = 0;
}

void append_word(Line *l, Word w) {
    if (l->capacity == 0) {
        l->capacity = 4;
        l->words = realloc(l->words, l->capacity * sizeof(Word));
    }
    else if (l->count >= l->capacity) {
        l->capacity *= 2;
        l->words = realloc(l->words, l->capacity * sizeof(Word));
    }

    l->words[l->count] = w;
    l->count++;
}

void free_word(Word *w) {
    if (w->data != NULL) {
        free(w->data);
        w->data = NULL;
    }
    w->lenght = 0;
    w->capacity = 0;
}

void free_line(Line *l) {
    if (l->words != NULL) {
        for (size_t i = 0; i < l->count; i++) {
            free_word(&(l->words[i]));
        }
        free(l->words);
        l->words = NULL;
    }
    l->count = 0;
    l->capacity = 0;
}

void print_vertical(Line *l) {
    if (l->count == 0) return;
    size_t max_len = 0;
    for (size_t i = 0; i < l->count; i++) {
        if (l->words[i].lenght > max_len) {
            max_len = l->words[i].lenght;
        }
    }
    for (size_t i = 0; i < max_len; i++) {
        for (size_t j = 0; j < l->count; j++) {
            if (i < l->words[j].lenght) {
                putchar(l->words[j].data[i]);
            }
            else {
                putchar (' ');
            }
        }
        putchar('\n');
    }
}

int main() {
    int ch;
    Line line;
    Word current_word;

    init_line(&line);
    init_word(&current_word);
    int in_word = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t') {
            if (in_word) {
                append_word(&line, current_word);
                init_word(&current_word);
                in_word = 0;
            }
        }
        else if (ch == '\n') {
            if (in_word) {
                append_word(&line, current_word);
                init_word(&current_word);
                in_word = 0;
            }
            print_vertical(&line);
            free_line(&line);
            init_line(&line);
        }
        else {
            append_char(&current_word, (char)ch);
            in_word = 1;
        }
    }

    if (in_word) {
        append_word(&line, current_word);
    }
    if (line.count > 0) {
        print_vertical(&line);
        free_line(&line);
    }

    return 0;
}
