//
// Created by 김아동 on 2016. 5. 22..
//

#include "gtest/gtest.h"

extern "C" {
#include <math.h>
#include "graphoper.h"
#include "binstar.h"
#include "binadd.h"
#include "topsort.h"
#include "allcost.h"
#include "sort.h"
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
    memset(list, 0, sizeof(fsnode *) * FSNODE_N);

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

int *createDescendingValues(int cnt)
{
    int i;
    int *array = (int *) malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; ++i)
        array[cnt - i - 1] = i;
    return array;
}

int *createValuesRandomly(int cnt)
{
    int i, j, temp;
    int *array = (int *) malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; ++i)
        array[i] = i;

    for (i = 0; i < cnt - 1; i++)
    {
        j = i + rand() / (RAND_MAX / (cnt - i) + 1);
        temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
    return array;
}

int *copyArrayValues(int *arr, int n)
{
    int *cpy = (int *) malloc(sizeof(int) * n);
    memcpy(cpy, arr, sizeof(int) * n);
    return cpy;
}

TEST(SORT, insertion)
{
    const int COUNT = 10;
    int i, *after, *before;
    before = createValuesRandomly(COUNT);
    after = copyArrayValues(before, COUNT);

    insertionSort(after, COUNT);

    printf("before|after\n");
    for (i = 0; i < COUNT; ++i)
        printf("%d%7d\n", before[i], after[i]);

    free(after);
    free(before);
}

TEST(SORT, quick)
{
    const int COUNT = 10;
    int i, *after, *before;
    before = createValuesRandomly(COUNT);
    after = copyArrayValues(before, COUNT);

    quickSort(after, 0, COUNT - 1);

    printf("before|after\n");
    for (i = 0; i < COUNT; ++i)
        printf("%d%7d\n", before[i], after[i]);

    free(after);
    free(before);
}

TEST(SORT, merge)
{
    const int COUNT = 11;
    int i, *after, *before;
    int extra[COUNT];
    before = createValuesRandomly(COUNT);
    after = copyArrayValues(before, COUNT);

    mergeSort(after, extra, COUNT - 1);

    printf("before|after\n");
    for (i = 1; i < COUNT; ++i)
        printf("%d%7d\n", before[i], after[i]);

    free(after);
    free(before);
}

TEST(SORT, selection)
{
    const int COUNT = 10;
    int i, *after, *before;
    before = createValuesRandomly(COUNT);
    after = copyArrayValues(before, COUNT);

    selectionSort(after, COUNT);

    printf("before|after\n");
    for (i = 0; i < COUNT; ++i)
        printf("%d%7d\n", before[i], after[i]);

    free(after);
    free(before);
}

TEST(SORT, performance_random)
{
    const int IDX = 2;
    const int TEST_COUNT = 15;
    const int COUNT = pow(IDX, TEST_COUNT); //2^15
    int *clone, *origin, *extra, n;
    int degree = 1;
    time_t start;
    double result[4];

    origin = createValuesRandomly(COUNT);
    clone = (int *) malloc(sizeof(int) * COUNT);
    extra = (int *) malloc(sizeof(int) * COUNT);

    printf("%s\t%s\t%s\t%s\t%s\n", "개수", "선택정렬", "삽입정렬", "퀵정렬", "합병정렬");
    for (n = pow(IDX, degree++); n <= COUNT; n = pow(IDX, degree++))
    {
        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        selectionSort(clone, n);
        result[0] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        insertionSort(clone, n);
        result[1] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        quickSort(clone, 0, n - 1);
        result[2] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        mergeSort(clone, extra, n - 1);
        result[3] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        printf("%d\t%lf\t%lf\t%lf\t%lf\n", n, result[0], result[1], result[2], result[3]);
    }

    free(clone);
    free(origin);
    free(extra);
}

TEST(SORT, performance_descending_order)
{
    const int IDX = 2;
    const int TEST_COUNT = 15;
    const int COUNT = pow(IDX, TEST_COUNT); //2^15
    int *clone, *origin, *extra, n;
    int degree = 1;
    time_t start;
    double result[4];

    origin = createDescendingValues(COUNT);
    clone = (int *) malloc(sizeof(int) * COUNT);
    extra = (int *) malloc(sizeof(int) * COUNT);

    printf("%s\t%s\t%s\t%s\t%s\n", "개수", "선택정렬", "삽입정렬", "퀵정렬", "합병정렬");
    for (n = pow(IDX, degree++); n <= COUNT; n = pow(IDX, degree++))
    {
        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        selectionSort(clone, n);
        result[0] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        insertionSort(clone, n);
        result[1] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        quickSort(clone, 0, n - 1);
        result[2] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        memcpy(clone, origin, sizeof(int) * COUNT);
        start = clock();
        mergeSort(clone, extra, n - 1);
        result[3] = (double) (clock() - start) / (CLOCKS_PER_SEC / 1000);

        printf("%d\t%lf\t%lf\t%lf\t%lf\n", n, result[0], result[1], result[2], result[3]);
    }

    free(clone);
    free(origin);
    free(extra);
}