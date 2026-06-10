#include <stdlib.h>
#include "rbt.h"

RBTree *rbt_create() {
    RBTree *T = malloc(sizeof(RBTree));
    T->nil = calloc(1, sizeof(Node));
    T->nil->color = BLACK;
    T->nil->left = T->nil->right = T->nil->parent = T->nil;
    T->root = T->nil;
    return T;
}

Node *tree_minimum(RBTree *T, Node *x) {
    while (x->left != T->nil) x = x->left;
    return x;
}

static void left_rotate(RBTree *T, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != T->nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil)        T->root = y;
    else if (x == x->parent->left)  x->parent->left = y;
    else                             x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void right_rotate(RBTree *T, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != T->nil) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil)        T->root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else                             x->parent->left = y;
    y->right = x;
    x->parent = y;
}

static void insert_fixup(RBTree *T, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { z = z->parent; left_rotate(T, z); }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(T, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { z = z->parent; right_rotate(T, z); }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rbt_insert(RBTree *T, int key) {
    Node *z = malloc(sizeof(Node));
    z->key = key; z->color = RED;
    z->left = z->right = z->parent = T->nil;
    Node *y = T->nil, *x = T->root;
    while (x != T->nil) {
        y = x;
        if (key < x->key)      x = x->left;
        else if (key > x->key) x = x->right;
        else { free(z); return; }
    }
    z->parent = y;
    if (y == T->nil)        T->root = z;
    else if (key < y->key)  y->left = z;
    else                     y->right = z;
    insert_fixup(T, z);
}

Node *rbt_search(RBTree *T, int key) {
    Node *x = T->root;
    while (x != T->nil) {
        if (key == x->key) return x;
        x = key < x->key ? x->left : x->right;
    }
    return NULL;
}

static void transplant(RBTree *T, Node *u, Node *v) {
    if (u->parent == T->nil)        T->root = v;
    else if (u == u->parent->left)  u->parent->left = v;
    else                             u->parent->right = v;
    v->parent = u->parent;
}

static void delete_fixup(RBTree *T, Node *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK; x->parent->color = RED;
                left_rotate(T, x->parent); w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED; x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK; w->color = RED;
                    right_rotate(T, w); w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK; w->right->color = BLACK;
                left_rotate(T, x->parent); x = T->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK; x->parent->color = RED;
                right_rotate(T, x->parent); w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED; x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK; w->color = RED;
                    left_rotate(T, w); w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK; w->left->color = BLACK;
                right_rotate(T, x->parent); x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void rbt_delete(RBTree *T, int key) {
    Node *z = rbt_search(T, key);
    if (!z) return;
    Node *y = z, *x;
    Color y_orig = y->color;
    if (z->left == T->nil) {
        x = z->right;
        transplant(T, z, z->right);
    } else if (z->right == T->nil) {
        x = z->left;
        transplant(T, z, z->left);
    } else {
        y = tree_minimum(T, z->right);
        y_orig = y->color;
        x = y->right;
        if (y != z->right) {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        } else {
            x->parent = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_orig == BLACK)
        delete_fixup(T, x);
}

static void free_nodes(RBTree *T, Node *x) {
    if (x == T->nil) return;
    free_nodes(T, x->left);
    free_nodes(T, x->right);
    free(x);
}

void rbt_free(RBTree *T) {
    free_nodes(T, T->root);
    free(T->nil);
    free(T);
}