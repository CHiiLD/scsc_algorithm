//
// Created by 김아동 on 2016. 5. 23..
//

#ifndef __GRAPHOPER_H__
#define __GRAPHOPER_H__

#define FSNODE_N 8

typedef struct __graph_first_search_node
{
    int vert;
    struct __binary_tree_node *link;
} fsnode;

void graph_addNode(fsnode **head, int vert);

void graph_showList(fsnode *node);

void graph_fsoper_init();

void graph_dfs(fsnode **graph, int vert);

void graph_bfs(fsnode **graph, int vert);

#endif //__GRAPHOPER_H__
