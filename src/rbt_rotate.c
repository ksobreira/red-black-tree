#include "rbt.h"

void left_rotate(RBTree *T, Node *x){
    Node *y = x->right;             // y é o filho direito de x
    x->right = y->left;             // a subarvore esquerda de y vai para a direita de x

    if(y->left != T->nil)
      y->left->parent = x;
    
    y->parent = x->parent;          // paide x passa a ser pai de y


    if(x->parent == T->nil)
      T->root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;                    // x fica filho esquerdo de y
    x->parent = y;
}

void right_rotate(RBTree *T, Node *x){
    Node *y = x->left;              // y é filho esquerdo de x
    x->left = y->right;             // a subarvore direita de y vai para a esquerda de x

    if(y->right != T->nil)
      y->right->parent = x;
    
    y->parent = x->parent;

    if(x->parent == T->nil)
      T->root = y;
    else if (x == x->parent->right)
      x->parent->right = x;
    else
      x->parent->left = x;

    y->parent = x;               // x fica filho direito de y   
    x->parent = y;
}