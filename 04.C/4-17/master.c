#include <stdio.h>
#include <stdlib.h>

struct item {
    int x;
    struct item *next;
}

struct item *ukaz(int *arr, int n) {
    struct item *last = NULL;
    struct item *first = NULL;
    // place for RECURSIVE
    return first;
}

int find_len(struct item *head) {
    struct item *p = head;
    int counter = 0;
    // Place for recursive
}

void free_list(struct item *head) {
    struct item *p = head;
    // place for recursive
}   

int *bigger(struct item *head) {
    int len = 0; 
    len = find_len(head);
    int *arr = malloc(sizeof(int) * (len + 1));
    arr[0] = len;
    struct item *p = head;
    // recursive
    return arr;
}
