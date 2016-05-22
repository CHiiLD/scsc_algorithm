//
// Created by 김아동 on 2016. 5. 23..
//

#include <stdlib.h>
#include <printf.h>
#include <string.h>
#include <assert.h>
#include "graphoper.h"

#define FALSE    0
#define TRUE     1
short int visited[FSNODE_N];
int rear = -1;
int front = -1;
int queue[FSNODE_N];

void graph_addNode(fsnode **head, int vert)
{
    fsnode *p = *head;
    fsnode *temp = (fsnode *) malloc(sizeof(fsnode));
    temp->link = NULL;
    temp->vert = vert;
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    while (p->link)
        p = p->link;
    p->link = temp;
}

void graph_showList(fsnode *node)
{
    while (node)
    {
        printf("%d%s", node->vert, node->link ? " => " : "");
        node = node->link;
    }
    printf("\n");
}

void graph_dfs(fsnode **graph, int vert)
{
    fsnode *w;
    visited[vert] = TRUE;
    printf("%5d", vert);
    for (w = graph[vert]; w; w = w->link)
        if (!visited[w->vert])
            graph_dfs(graph, w->vert);
}


void graph_fsoper_init()
{
    memset(visited, FALSE, sizeof(short int) * FSNODE_N);
    memset(queue, FALSE, sizeof(int) * FSNODE_N);
    rear = -1;
    front = -1;
}

void addq(int vert)
{
    if (rear == FSNODE_N - 1)
        assert(0);
    queue[++rear] = vert;
}

int deleteq()
{
    if (front == rear)
        assert(0);
    return queue[++front];
}

void graph_bfs(fsnode **graph, int vert)
{
    fsnode *w;
    visited[vert] = TRUE;
    printf("%5d", vert);
    addq(vert);
    while (front != FSNODE_N - 1)
    {
        vert = deleteq();
        for (w = graph[vert]; w != NULL; w = w->link)
        {
            if (visited[w->vert] == FALSE)
            {
                printf("%5d", w->vert);
                addq(w->vert);
                visited[w->vert] = TRUE;
            }
        }
    }
}