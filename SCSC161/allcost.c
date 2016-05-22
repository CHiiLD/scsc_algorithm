//
// Created by 김아동 on 2016. 5. 23..
//

#include <stdio.h>
#include "allcost.h"

#define MAX_V 6
#define INF 10000

void allcosts(int cost[][MAX_V], int distance[][MAX_V], int n)
{
    /* 각 vertex에서 나머지 모든 vertex까지의 최단 경로를 계산.
    cost[][]: 인접 행렬, distance[][]: 경로의 거리를 저장 */
    int i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            distance[i][j] = cost[i][j];        // A-1[][]의 초기화
    for (k = 0; k < n; k++)            // A0부터 An-1까지 차례대로 생성
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (distance[i][k] + distance[k][j] < distance[i][j])
                    distance[i][j] = distance[i][k] + distance[k][j];

        for (i = 0; i < MAX_V; ++i)
        {
            for (j = 0; j < MAX_V; ++j)
            {
                if (distance[i][j] != INF)
                    printf("%d ", distance[i][j]);
                else
                    printf("%d ", -1);

            }
            printf("\n");
        }
        printf("\n======================\n");
    }
}

int runAllCost()
{
    int distance[MAX_V][MAX_V] = {0,};
    int cost[MAX_V][MAX_V] = {{0,   50,  45, 10,  25, INF}, //0
                              {INF, 0,   10, 15, INF, INF}, //1
                              {INF, INF, 0,  65,  30, INF}, //2
                              {30,  35,  45, 0,   15, INF}, //3
                              {INF, 20,  30, 35,  0,  INF}, //4
                              {58,  23,  33, INF, 3, 0}     //5
    };
    allcosts(cost, distance, MAX_V);
    return 0;
}