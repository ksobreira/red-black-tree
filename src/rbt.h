#ifndef RBT_H
#define RBT_H

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct {
    Node *root;
    Node *nil;
} RBTree;

RBTree *rbt_create();
void    rbt_insert(RBTree *T, int key);
Node   *rbt_search(RBTree *T, int key);
void    rbt_delete(RBTree *T, int key);
void    rbt_free(RBTree *T);
Node   *tree_minimum(RBTree *T, Node *x);

#endif