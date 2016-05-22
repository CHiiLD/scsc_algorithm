#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

#define LEFT 1
#define RIGHT 2
#define FAIL 0
#define SUCESS 1
#define STACKSIZE 100

int push(int *stack, int *top, int dir)
{
    if (*top == STACKSIZE)
        return FAIL;

    stack[++(*top)] = dir;
    return 1;
}

int pop(int *stack, int *top)
{
    if (*top == -1)
        return FAIL;
    return stack[(*top)--];
}

int bin_addNodeCompletely(bnode **root, char data, int pos)
{
    int stack[STACKSIZE], top = -1;
    bnode *p = NULL;
    bnode *temp = (bnode *) malloc(sizeof(bnode));
    temp->data = data;
    temp->left = temp->right = NULL;

    if (pos == 1 && *root == NULL)
    {
        *root = temp;
        return SUCESS;
    }
    while (pos != 1)
    {
        push(stack, &top, pos % 2 ? RIGHT : LEFT);
        pos /= 2;
    }

    p = *root;
    while (pos = pop(stack, &top))
    {
        if (pos == LEFT && p->left)
            p = p->left;
        else if (pos == RIGHT && p->right)
            p = p->right;
        else if (pos == LEFT)
        {
            if (top == -1)
            {
                p->left = temp;
                return SUCESS;
            }
            else
                break;
        }
        else if (pos == RIGHT)
        {
            if (top == -1)
            {
                p->right = temp;
                return SUCESS;
            }
            else
                break;
        }
    }
    free(temp);
    return FAIL;
}
