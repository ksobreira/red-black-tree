#include "rbt.h"

//Retorna o menor nó com a menor chave a partir de "X"
Node *tree_minimum(RBTree *T, Node *x) {
    while(x->left != T->nil)
        x = x->left;
    return x;    
}

// Substitui uma subárvore por outra dentro da estrutura, mantendo a integridade das ligações pai-filho (subárvore enraizada em u pela enraizada em v)
void rbt_transplant(RBTree *T, Node *u, Node *v){
    if(u->parent == T->nil)
        T->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else 
        u->parent->right = v;
    
    v->parent = u->parent;   
}