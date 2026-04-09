#include <stdio.h>
#include <stdlib.h>

struct item {
    int x;
    struct item *next;
};

struct item *ukaz(int *arr, int n) {
    if (n <= 0) return NULL;
    struct item *node = malloc(sizeof(struct item));
    node->x = *arr;
    node->next = ukaz(arr + 1, n - 1);
    return node;
}

int find_len(struct item *head) {
    if (head == NULL) return 0;
    return 1 + find_len(head->next);
}

void free_list(struct item *head) {
    if (head == NULL) return;
    free_list(head->next);
    free(head);
}

void fill_arr(struct item *head, int *arr, int i) {
    if (head == NULL) return;
    arr[i] = head->x;
    fill_arr(head->next, arr, i + 1);
}

int *bigger(struct item *head) {
    int len = find_len(head);
    int *arr = malloc(sizeof(int) * (len + 1));
    arr[0] = len;
    fill_arr(head, arr, 1);
    return arr;
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
