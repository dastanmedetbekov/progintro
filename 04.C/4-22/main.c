#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum color { BLACK, RED };

struct node {
    enum color color;
    char *key;
    void *data;
    struct node *left;
    struct node *right;
};

struct tree {
    struct node *root;
    size_t count;
};

// functions

void tree_init(struct tree *s) {
    s->root = NULL;
    s->count = 0;
}

void node_init(struct node *s) {
    s->color = BLACK;
    s->key = NULL;
    s->data = NULL;
    s->left = NULL;
    s->right = NULL;
}

void* tree_search(struct tree *s, char *key_search) {
    struct node *current = s->root;
   
    while (current != NULL) {
        int n;
        n = strcmp(key_search, current->key);
        if (n == 0) {
            return current->data;
        }
        else if (n < 0) {
            current = current->left;
        }
        else if (n > 0) {
            current = current->right;
        }
    }
    return NULL;
}

void tree_insert(struct tree *s, char *key, void* data) {
    if (s->root == NULL) {
        struct node *new_node = malloc(sizeof(struct node));
        node_init(new_node);
        new_node->key = key;
        new_node->data = data;
        s->root = new_node;
        s->count++;
        return;
    }

    struct node *current = s->root;
    struct node *father;
    size_t l_or_r = 0;

    while (current != NULL)  {
        int n = strcmp(key, current->key);
        if (n == 0) {
            current->data = data;
            return;
        }
        else if (n < 0) {
            l_or_r = 1;
            father = current;
            current = current->left;
        }
        else if (n > 0) {
            l_or_r = 2;
            father = current;
            current = current->right;
        }
    }

    struct node *n_node = malloc(sizeof(struct node));
    node_init(n_node);
    n_node->key = key;
    n_node->data = data;
    if (l_or_r == 1) {
        father->left = n_node;
    }
    else if (l_or_r == 2) {
        father->right = n_node;
    }
    s->count++;
    return;
}

void node_destroy(struct node *s) {
    if (s == NULL) {
        return;
    }

    node_destroy(s->left);
    node_destroy(s->right);
    free(s->key);
    free(s->data);
    free(s);
}


void tree_destroy(struct tree *s) {
    node_destroy(s->root);
}

void inherit_printer(struct node *s) {
    if (s == NULL) {
        return;
    }
    inherit_printer(s->left);
    inherit_printer(s->right);
    int *year = (int *) s->data;
    printf("\n");
    printf("%s born in %d", s->key, *year);
}
    
void rotate_right(struct tree *s, struct node *y) {
    
    struct node *x = y->left;
    struct node *b = x->right;

    y->left = b;

    x->right = y;
}



int main() {
    struct tree main_tree;
    tree_init(&main_tree);
    int trash;
    for (int i = 0; i < 30; i++) {
        char buffer[20];
        sprintf(buffer, "%d", i);

        char *key_copy = malloc(strlen(buffer) + 1);
        strcpy(key_copy, buffer);

        int *year = malloc(sizeof(int));
        *year = i + 1998;

        tree_insert(&main_tree, key_copy, year);
    }
    inherit_printer(main_tree.root);
    tree_destroy(&main_tree);
    return 0;
}
