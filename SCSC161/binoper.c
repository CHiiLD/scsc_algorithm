#include "binoper.h"
#include "stdlib.h"
#include "assert.h"
#include "binstar.h"

bnode *bin_copy(bnode *origin)
{
    bnode *temp = NULL;
    if (origin != NULL)
    {
        temp = (bnode *) malloc(sizeof(bnode));
        temp->left = bin_copy(origin->left);
        temp->right = bin_copy(origin->right);
        temp->data = origin->data;
    }
    return temp;
}

bnode *bin_mirrorCopy(bnode *origin)
{
    bnode *temp = NULL;
    if (origin != NULL)
    {
        temp = (bnode *) malloc(sizeof(bnode));
        temp->left = bin_mirrorCopy(origin->right);
        temp->right = bin_mirrorCopy(origin->left);
        temp->data = origin->data;
    }
    return temp;
}

int bin_equal(bnode *expect, bnode *actual)
{
    return ((!expect && !actual) ||
            (expect && actual && (expect->data == actual->data) && bin_equal(expect->left, actual->left) &&
             bin_equal(expect->right, actual->right)));
}

void bin_bintreeOperTest()
{
    //1.create tree
    bnode *root1 = NULL;
    bnode *root2 = NULL, *root3 = NULL;
    assert(bin_addNodeCompletely(&root1, '1', 1));
    assert(bin_addNodeCompletely(&root1, '2', 2));
    assert(bin_addNodeCompletely(&root1, '3', 3));
    assert(bin_addNodeCompletely(&root1, '4', 4));
    assert(bin_addNodeCompletely(&root1, '5', 5));
    assert(bin_addNodeCompletely(&root1, '6', 6));
    assert(bin_addNodeCompletely(&root1, '7', 7));
    //2.copy tree and print
    root2 = bin_copy(root1);
    bin_printTree(root1);
    //3.mirror copy
    root3 = bin_mirrorCopy(root1);
    bin_printTree(root3);
    //4.equal test
    assert(bin_equal(root1, root2));
    //5.equal test
    assert(!bin_equal(root1, root3));
}
