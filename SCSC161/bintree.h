#ifndef __BINTREE_H__
#define __BINTREE_H__

typedef struct __binary_tree_node
{
    int data;
    struct __binary_tree_node *left;
    struct __binary_tree_node *right;
} bnode;

void bin_insertNode(bnode **root, int data);

void bin_insertAtParent(bnode *node, bnode *child);

//전위순회
void bin_preOrder(bnode *node);

//중위순회
void bin_inOrder(bnode *node);

//후위순회
void bin_postOrder(bnode *node);

#endif //__BINTREE_H__
