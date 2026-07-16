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
    struct node *parent;
};

struct tree {
    struct node *root;
    size_t count;
};

void tree_init(struct tree *s) {
    s->root = NULL;
    s->count = 0;
}

void node_init(struct node *s) {
    s->color = RED;
    s->key = NULL;
    s->data = NULL;
    s->left = NULL;
    s->right = NULL;
    s->parent = NULL;
}

void* tree_search(struct tree *s, char *key_search) {
    struct node *current = s->root;
    while (current != NULL) {
        int n = strcmp(key_search, current->key);
        if (n == 0) {
            return current->data;
        } else if (n < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void rotate_left(struct tree *s, struct node *y) {
    struct node *x = y->right;
    struct node *b = x->left;

    y->right = b;
    if (b != NULL) {
        b->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == NULL) {
        s->root = x;
    } else if (y->parent->left == y) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->left = y;
    y->parent = x;
}

void rotate_right(struct tree *s, struct node *y) {
    struct node *x = y->left;
    struct node *b = x->right;

    y->left = b;
    if (b != NULL) {
        b->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == NULL) {
        s->root = x;
    } else if (y->parent->left == y) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void tree_insert_fixup(struct tree *s, struct node *node) {
    while (node->parent != NULL && node->parent->color == RED) {
        struct node *parent = node->parent;
        struct node *grandparent = parent->parent;

        if (parent == grandparent->left) {
            struct node *uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotate_left(s, node);
                    parent = node->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotate_right(s, grandparent);
            }
        } else {
            struct node *uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotate_right(s, node);
                    parent = node->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotate_left(s, grandparent);
            }
        }
    }
    s->root->color = BLACK;
}

void tree_insert(struct tree *s, char *key, void *data) {
    struct node *current = s->root;
    struct node *parent = NULL;
    size_t l_or_r = 0;

    while (current != NULL) {
        int n = strcmp(key, current->key);
        if (n == 0) {
            current->data = data;
            return;
        } else if (n < 0) {
            l_or_r = 1;
            parent = current;
            current = current->left;
        } else {
            l_or_r = 2;
            parent = current;
            current = current->right;
        }
    }

    struct node *n_node = malloc(sizeof(struct node));
    node_init(n_node);
    n_node->key = key;
    n_node->data = data;
    n_node->parent = parent;

    if (parent == NULL) {
        s->root = n_node;
    } else if (l_or_r == 1) {
        parent->left = n_node;
    } else {
        parent->right = n_node;
    }

    s->count++;
    tree_insert_fixup(s, n_node);
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
    s->root = NULL;
    s->count = 0;
}

void inherit_printer(struct node *s) {
    if (s == NULL) {
        return;
    }
    inherit_printer(s->left);
    int *year = (int *) s->data;
    printf("%s born in %d (%s)\n", s->key, *year, s->color == RED ? "RED" : "BLACK");
    inherit_printer(s->right);
}

int check_rb(struct node *n, int *bh, int *ok) {
    if (n == NULL) {
        *bh = 1;
        return 1;
    }
    if (n->color == RED) {
        if ((n->left && n->left->color == RED) || (n->right && n->right->color == RED)) {
            printf("VIOLATION: two consecutive red nodes at key %s\n", n->key);
            *ok = 0;
        }
    }
    int bh_left, bh_right;
    check_rb(n->left, &bh_left, ok);
    check_rb(n->right, &bh_right, ok);
    if (bh_left != bh_right) {
        printf("VIOLATION: different black height at key %s (%d vs %d)\n", n->key, bh_left, bh_right);
        *ok = 0;
    }
    *bh = bh_left + (n->color == BLACK ? 1 : 0);
    return 1;
}

int main() {
    struct tree main_tree;
    tree_init(&main_tree);

    for (int i = 0; i < 30; i++) {
        char buffer[20];
        sprintf(buffer, "%03d", i);
        char *key_copy = malloc(strlen(buffer) + 1);
        strcpy(key_copy, buffer);
        int *year = malloc(sizeof(int));
        *year = i + 1998;
        tree_insert(&main_tree, key_copy, year);
    }

    inherit_printer(main_tree.root);

    printf("\nIs root black? %s\n", main_tree.root->color == BLACK ? "yes" : "NO");

    int bh, ok = 1;
    check_rb(main_tree.root, &bh, &ok);
    printf("Tree is %s\n", ok ? "VALID red-black tree" : "INVALID");

    char *found = (char*) tree_search(&main_tree, "015");
    printf("\nSearch \"015\": %s\n", found ? "found" : "not found");

    tree_destroy(&main_tree);
    return 0;
}
