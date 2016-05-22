//
// Created by rians on 2016-05-18.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 6

struct __simple_node
{
    int vertex;
    struct __simple_node *link;
};

typedef struct
{
    int count;
    struct __simple_node *link;
} hdnodes;

hdnodes graph[MAX];

int stack[MAX] = {0,};
int stack_index = -1;

void add_stack(int i)
{
    stack[++stack_index] = i;
}

int stack_empty()
{
    return stack_index == -1;
}

int delete_stack()
{
    return stack[stack_index--];
}

void topsortWithStack(hdnodes graph[], int n)
{
    int i, j, k, top = -1;
    struct __simple_node *ptr = NULL;

    for (i = 0; i < n; ++i)
    {
        if (graph[i].count == 0)
        {
            add_stack(i);
        }
    }
    for (i = 0; i < n; ++i)
    {
        if (stack_empty())
        {
            assert(0);
        }
        else
        {
            j = delete_stack(i);
            printf("v%d ", j);
            for (ptr = graph[j].link; ptr != NULL; ptr = ptr->link)
            {
                k = ptr->vertex;
                graph[k].count--;
                if (graph[k].count == 0)
                    add_stack(k);
            }
        }
    }
    printf("\n");
}

void topsortWithoutStack(hdnodes graph[], int n)
{
    int i, j, k, top = -1;
    struct __simple_node *ptr = NULL;

    for (i = 0; i < n; ++i)
    {
        if (graph[i].count == 0)
        {
            graph[i].count = top;
            top = i;
        }
    }
    for (i = 0; i < n; ++i)
    {
        if (top == -1)
        {
            assert(0);
        }
        else
        {
            j = top;
            top = graph[top].count; //스택에서 제거
            printf("v%d ", j);
            for (ptr = graph[j].link; ptr != NULL; ptr = ptr->link)
            {
                //선행자 정점들의 카운트 감소
                k = ptr->vertex;
                graph[k].count--;

                //새로운 정점을 스택에 삽입
                if (graph[k].count == 0)
                {
                    graph[k].count = top;
                    top = k;
                }
            }
        }
    }
    printf("\n");
}

struct __simple_node *createNode(int data)
{
    struct __simple_node *newNode = (struct __simple_node *) malloc(sizeof(struct __simple_node));
    newNode->vertex = data;
    newNode->link = NULL;
    return newNode;
}

void attach(struct __simple_node *root, int data)
{
    struct __simple_node *newNode = createNode(data);
    while (root->link != NULL)
        root = root->link;
    root->link = newNode;
}

void initGraph()
{
    int i, cnt;
    struct __simple_node *temp;
    for (i = 0; i < MAX; ++i)
    {
        graph[i].link = createNode(i);
        graph[i].count = 0;
    }

    attach(graph[0].link, 1);
    attach(graph[0].link, 2);
    attach(graph[0].link, 3);
    attach(graph[1].link, 4);
    attach(graph[2].link, 4);
    attach(graph[2].link, 5);
    attach(graph[3].link, 5);
    attach(graph[3].link, 4);

    graph[0].count = 0;
    graph[1].count = 1;
    graph[2].count = 1;
    graph[3].count = 1;
    graph[4].count = 3;
    graph[5].count = 2;

    for (i = 0; i < MAX; ++i)
    {
        cnt = 0;
        temp = graph[i].link;
        printf("index %d:", i);
        while (temp != NULL)
        {
            printf(" %d", temp->vertex);
            cnt++;
            temp = temp->link;
        }
        printf("\n");
    }
}

void runTopSort()
{
    initGraph();
    topsortWithStack(graph, MAX);
}