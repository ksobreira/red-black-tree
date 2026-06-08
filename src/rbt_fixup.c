#include "rbt.h"

void rbt_insert_fixup(RBTree *T, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            // Pai é filho ESQUERDO do avô
            Node *y = z->parent->parent->right; // tio

            if (y->color == RED) {
                // Caso 1: tio é RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Caso 2: nó é filho direito
                    z = z->parent;
                    left_rotate(T, z);
                }
                // Caso 3: nó é filho esquerdo
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(T, z->parent->parent);
            }
        } else {
            // Pai é filho DIREITO do avô (espelho)
            Node *y = z->parent->parent->left; // tio

            if (y->color == RED) {
                // Caso 1 espelho
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Caso 2 espelho
                    z = z->parent;
                    right_rotate(T, z);
                }
                // Caso 3 espelho
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK; // raiz sempre BLACK
}

void rbt_delete_fixup(RBTree *T, Node *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right; // irmão

            if (w->color == RED) {
                // Caso 1: irmão é RED
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // Caso 2: filhos do irmão são BLACK
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // Caso 3: filho direito do irmão é BLACK
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(T, w);
                    w = x->parent->right;
                }
                // Caso 4: filho direito do irmão é RED
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(T, x->parent);
                x = T->root;
            }
        } else {
            // Espelho
            Node *w = x->parent->left;

            if (w->color == RED) {
                // Caso 1 espelho
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                // Caso 2 espelho
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // Caso 3 espelho
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(T, w);
                    w = x->parent->left;
                }
                // Caso 4 espelho
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}