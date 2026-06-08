#include <stdlib.h>
#include "rbt.h"

// Cria a árvore com o nó sentinela NIL
RBTree *rbt_create() {
    RBTree *T = malloc(sizeof(RBTree));

    T->nil = malloc(sizeof(Node));
    T->nil->color = BLACK;
    T->nil->left = T->nil->right = T->nil->parent = T->nil;

    T->root = T->nil;
    return T;
}

// Inserção
void rbt_insert(RBTree *T, int key) {
    Node *z = malloc(sizeof(Node));
    z->key = key;
    z->color = RED;
    z->left = z->right = z->parent = T->nil;

    Node *y = T->nil;
    Node *x = T->root;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == T->nil)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    rbt_insert_fixup(T, z);
}

// Busca
Node *rbt_search(RBTree *T, int key) {
    Node *x = T->root;
    while (x != T->nil) {
        if (key == x->key)
            return x;
        else if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return NULL; // não encontrado
}

// Remoção
void rbt_delete(RBTree *T, int key) {
    Node *z = rbt_search(T, key);
    if (z == NULL) return; // chave não existe

    Node *y = z;
    Node *x;
    Color y_original_color = y->color;

    if (z->left == T->nil) {
        x = z->right;
        rbt_transplant(T, z, z->right);
    } else if (z->right == T->nil) {
        x = z->left;
        rbt_transplant(T, z, z->left);
    } else {
        y = tree_minimum(T, z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            rbt_transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbt_transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK)
        rbt_delete_fixup(T, x);
}

// Libera memória recursivamente
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