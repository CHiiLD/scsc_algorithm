//
// Created by 김아동 on 2016. 5. 22..
//

#include "gtest/gtest.h"

extern "C" {
#include "graphoper.h"
#include "binstar.h"
#include "binadd.h"
#include "topsort.h"
#include "allcost.h"
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

bnode *newBNodes(int cnt)
{
    int i;
    bnode *root = NULL;
    for (i = 0; i < cnt; ++i)
    {
        assert(bin_addNodeCompletely(&root, 48 + i, i + 1));
    }
    return root;
}

fsnode **newFSNodes()
{
    fsnode **list = (fsnode **) malloc(sizeof(fsnode *) * FSNODE_N);
    memset(list, NULL, sizeof(fsnode *) * FSNODE_N);

    graph_addNode(&list[0], 1);
    graph_addNode(&list[0], 2);
    graph_addNode(&list[1], 0);
    graph_addNode(&list[1], 3);
    graph_addNode(&list[1], 4);
    graph_addNode(&list[2], 0);
    graph_addNode(&list[2], 5);
    graph_addNode(&list[2], 6);
    graph_addNode(&list[3], 1);
    graph_addNode(&list[3], 7);
    graph_addNode(&list[4], 1);
    graph_addNode(&list[4], 7);
    graph_addNode(&list[5], 2);
    graph_addNode(&list[5], 7);
    graph_addNode(&list[6], 2);
    graph_addNode(&list[6], 7);
    graph_addNode(&list[7], 3);
    graph_addNode(&list[7], 4);
    graph_addNode(&list[7], 5);
    graph_addNode(&list[7], 6);
    return list;
}

TEST(TREE, tree_traversal)
{
    bnode *root = newBNodes(7);

    printf("중위순회\n");
    bin_inOrder(root);
    printf("\n");

    printf("전위순회\n");
    bin_preOrder(root);
    printf("\n");

    printf("후위순회\n");
    bin_postOrder(root);
    printf("\n");
}

TEST(TREE, tree_pretty_print)
{
    bnode *root = newBNodes(7);
    bin_printTree(root);
}

TEST(SEARCH, depth_first_search)
{
    int i;
    fsnode **list = newFSNodes();

    for (i = 0; i < FSNODE_N; i++)
    {
        printf("%d : ", i);
        graph_showList(list[i]);
    }
    graph_fsoper_init();
    graph_dfs(list, 0);
    printf("\n");
}

TEST(SEARCH, breath_first_search)
{
    int i;
    fsnode **list = newFSNodes();

    for (i = 0; i < FSNODE_N; i++)
    {
        printf("%d : ", i);
        graph_showList(list[i]);
    }
    graph_fsoper_init();
    graph_bfs(list, 0);
    printf("\n");
}

TEST(ALLCOST, allcost)
{
    runAllCost();
}

TEST(TOPSORT, topsort)
{
    runTopSort();
}