#include <stdio.h>
#include <stdlib.h>
// 2026-05-08

typedef struct {
    long long value; // for the number
    int count; // we need three
    int index; // index in the row to be right.
} number_tracker;

int main()
{
    long long val;
    int capacity = 10;
    int total_unique = 0;
    number_tracker *storage = malloc(capacity * sizeof(number_tracker));

    if (storage == NULL) {
        return 1;
    }
    
    // loop

    while(scanf("%lld", &val) != EOF) {
        int found = 0;
        for (int i = 0; i < total_unique; i++) 
        {
            if (storage[i].value == val)
            {
                storage[i].count++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            if (total_unique >= capacity)
            {
                capacity *= 2;
                storage = realloc(storage, capacity * sizeof(number_tracker));
                printf("REALLOC\n");
            }
            storage[total_unique].value = val;
            storage[total_unique].count = 1;
            storage[total_unique].index = total_unique;

            total_unique++;
        }
    }
    int current_streak = 0;

    for (int i = 0; i < total_unique; i++) {
        if (storage[i].count > current_streak) {
            current_streak = storage[i].count;
        }
    }

    for (int i = 0; i < total_unique; i++) 
    {
        if (storage[i].count == current_streak)
        {
            printf("%lld ", storage[i].value);
        }
    }
    printf("\n"); 

    free(storage);
    return 0;
}
