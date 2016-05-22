#include <math.h>
#include <stdio.h>
#include "bintree.h"
#include "binstar.h"

void printGap(int a)
{
    int i;
    for (i = 0; i < a; i++)
        printf(" ");
}

int getLevel(int n)
{
    int i;
    for (i = 1; n; i++)
        n = n / 2;
    return i;
}

void bin_printStar(int level)
{
    int i, j, end, gap, cnt = 0;

    for (i = 0; i < level; ++i)
    {
        gap = pow(2, level - i) - 1;
        printGap(gap / 2);
        end = pow(2, i);
        for (j = 0; j < end; ++j)
        {
            printf("*");
            printGap(gap);
        }
        printf("\n");
    }
}

int setArray(bnode *node, char buff[], int pos)
{
    static int bestPos;
    if (pos == 1)
        bestPos = 0;
    if (node)
    {
        if (bestPos < pos)
            bestPos = pos;
        buff[pos - 1] = node->data;
        setArray(node->left, buff, pos * 2);
        setArray(node->right, buff, pos * 2 + 1);
    }
    return bestPos;
}

void bin_printTree(bnode *root)
{
    char buff[1024] = {0,};
    int i, j, end, gap, cnt = 0, bestPos = 0, level;
    bestPos = setArray(root, buff, 1);
    level = getLevel(bestPos);
    for (i = 0; i < level; i++)
    {
        gap = pow(2, level - i) - 1;
        printGap(gap / 2);
        end = pow(2, i);
        for (j = 0; j < end; j++)
        {
            printf("%c", buff[cnt++]);
            printGap(gap);
        }
        printf("\n");
    }
    printf("\n");
}