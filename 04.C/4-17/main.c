#include <stdio.h>
#include <stdlib.h>

struct item {
    int x;
    struct item *next;
};

struct item *ukaz(int *arr, int n) {
    struct item *last = NULL;
    struct item *first = NULL;
    for (int i = 0; i < n; i++) {
        struct item *ptr = malloc(sizeof(struct item));
        ptr->x = arr[i];
        if (first == NULL) {
            first = ptr;
            last = ptr;
        }
        else {
            last->next=ptr;
            last = ptr;
        }
        last->next = NULL;
    }
    return first;
}

int find_len(struct item *head);

int *bigger(struct item *head) {
    int len = 0;
    len = find_len(head);
    int *arr = malloc(sizeof(int) * (len + 1));
    arr[0] = len;
    struct item *p = head;
    for(int i = 1; p != NULL; i++) {
        arr[i] = p->x;
        p = p->next;
    }
    return arr;
}

int find_len(struct item *head) {
    struct item *p = head;
    int counter = 0;
    for (int i = 0; p != NULL; i++) {
        p = p->next;
        counter++;
    }
    return counter;
}

void free_list(struct item *head) {
    struct item *p = head;
    while (p != NULL) {
        struct item *next = p->next; 
        free(p);                    
        p = next;                    
    }
}
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct item *list = ukaz(arr, n);
    int *result = bigger(list);

    printf("List length: %d\n", result[0]);
    printf("Elements: ");
    for (int i = 1; i <= result[0]; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    free_list(list);
    return 0;
}
