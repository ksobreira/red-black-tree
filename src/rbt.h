#ifndef RBT_H
#define RBT_H

typedef enum {RED, BLACK}   Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct {
    Node *root;
    Node *nil;
} RBTree;

// rbt.c
RBTree *rbt_create();
void    rbt_insert(RBTree *T, int key);
Node   *rbt_search(RBTree *T, int key);
void    rbt_delete(RBTree *T, int key);
void    rbt_free(RBTree *T);

//rbt.routate.c
void left_routate(RBTree *T, Node *x);
void right_routate(RBTree *T, Node *x);

//rbt.fixup.c
void rbt_insert_fixup(RBTree *T, Node *z);
void rbt_delete_fixup(RBTree *T, Node *x);

//rbt.utils.c
Node *tree_minimum(RBTree *T, Node *x);
void rbt_transplant(RBTree *T, Node *u, Node *v)

#endif
