#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int number;
    int data;
    struct Node* next;
}node_t;

int main() {
    node_t* head = NULL;
    node_t* current = NULL;
    int val;
    int counter = 1;

    while (scanf("%d", &val) == 1) 
    {
        node_t* new_node = (node_t*)malloc(sizeof(node_t));

        if (new_node == NULL) {
            printf("error: no free memory\n");
            return 1;
        }

        new_node->number = counter++;
        new_node->data = val;
        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
            current = head;
        }
        else
        {
            current->next = new_node;
            current = new_node;
        }
    }
    // comming to the head to make new itarations
    current = head;

    int last, first;
    int is_last_changed = 1;
    while(current != NULL) {
        first = current->data;
        if (is_last_changed == 1) {
            last = first;
            is_last_changed = 0;
        } else {
            int difference = abs(last - first);
            if (difference < 5) {
                printf ("%d, %d\n", last, first);
            }
            last = first;
        }
        current = current->next;
    }
    current = head;

    while (current != NULL) {
        node_t* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;

        

    return 0;
}
