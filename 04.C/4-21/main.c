#include <stdio.h>
#include <stdlib.h>

struct stackdbl 
{
    size_t capacity;
    size_t count;
    double *dbl_p;
};

void stackdbl_init(struct stackdbl *s) {
    s->capacity = 10;
    s->count = 0;
    s->dbl_p = malloc(s->capacity * sizeof(double));
    if (s->dbl_p == NULL) {
        printf("ERROR, MALLOC");
        exit(1);
    }
    
}

void stackdbl_destroy(struct stackdbl *s) {
    free(s->dbl_p);
    s->capacity = 0;
    s->count = 0;
    s->dbl_p = NULL;
}

void stackdbl_push(struct stackdbl *s, double number)
{
    if (s->capacity <= s->count) {
        double *new_dbl_p = malloc((s->capacity * 2) * sizeof(double));
        if (new_dbl_p == NULL) {
            printf("ERROR, MALLOC");
            exit(1);
        }

        size_t i;
        for (i = 0; i < s->capacity; i++) {
            new_dbl_p[i] = s->dbl_p[i];
        }

        free(s->dbl_p);
        s->dbl_p = new_dbl_p;
        s->capacity *= 2;
    }

    s->dbl_p[s->count] = number;
    s->count++;

}

int stackdbl_empty(struct stackdbl *s) {
    if (s->count == 0 || s->capacity == 0 || s->dbl_p == NULL) {
        return 1;
    }
    return 0;
}

double stackdbl_pop(struct stackdbl *s) {
    double number;
    int i = stackdbl_empty(s);

    if (i == 1) {
        exit(1);
    }

    s->count -= 1;
    number = s->dbl_p[s->count];
    s->dbl_p[s->count] = 0.0;

    return number;
}

int main() {
    struct stackdbl s;
    stackdbl_init(&s);
    stackdbl_push(&s, 0.100);
    stackdbl_push(&s, 100.21);
    printf("%.2f\n", stackdbl_pop(&s));

    // better test
    
    for (int j = 0; j < 15; j++) {
        stackdbl_push(&s, j * 1.5);
    }
    while (!stackdbl_empty(&s)) {
        printf("%.2f\n", stackdbl_pop(&s));
    }
    stackdbl_destroy(&s);

    return 0;
}
