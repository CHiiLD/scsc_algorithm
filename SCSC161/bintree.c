#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void bin_insertNode(bnode **root, int data)
{
    bnode *temp = (bnode *) malloc(sizeof(bnode));
    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;

    if (*root == NULL)
    {
        *root = temp;
        return;
    }
    bin_insertAtParent(*root, temp);
}

void bin_insertAtParent(bnode *node, bnode *child)
{
    if (node->data > child->data)
    {
        if (node->left)
            bin_insertAtParent(node->left, child);
        else
            node->left = child;
    }
    else
    {
        if (node->right)
            bin_insertAtParent(node->right, child);
        else
            node->right = child;
    }
}

//전위순회
void bin_preOrder(bnode *node)
{
    if (node == NULL)
        return;
    printf("%c ", node->data);
    if (node->left)
        bin_preOrder(node->left);
    if (node->right)
        bin_preOrder(node->right);
}

//중위순회
void bin_inOrder(bnode *node)
{
    if (node == NULL)
        return;
    if (node->left)
        bin_inOrder(node->left);
    printf("%c ", node->data);
    if (node->right)
        bin_inOrder(node->right);
}

//후위순회
void bin_postOrder(bnode *node)
{
    if (node == NULL)
        return;
    if (node->left)
        bin_postOrder(node->left);
    if (node->right)
        bin_postOrder(node->right);
    printf("%c ", node->data);
}