//
// Created by 김아동 on 2016. 6. 1..
//

//삽입정렬 구현 , 퀵정렬 구현, 병합정렬 구현 ... 4가지 정렬을 이용하여 데이터 별 정렬시간을 측정하고 분석할 것. 각 정렬의 성능을 그래프로 나타내고 비교.

#include "sort.h"

void selectionSort(int *list, int n)
{
    int *index = list;
    int i, j, min, temp;
    for (i = 0; i < n; i++)
    {
        min = index[i];
        temp = -1;
        for (j = i; j < n - 1; j++)
        {
            if (min > index[j + 1])
            {
                min = index[j + 1];
                temp = j + 1;
            }
        }
        if (temp != -1)
        {
            index[temp] = index[i];
            index[i] = min;
        }
    }
}

void insert(int key, int list[], int idx)
{
    int i;
    for (i = idx - 1; list[i] > key; --i)
        list[i + 1] = list[i];
    list[++i] = key;
}

void insertionSort(int *list, int n)
{
    int j;
    for (j = 1; j < n; j++)
        insert(list[j], list, j);
}

void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

void quickSort(int *list, int left, int right)
{
    int pivot, i, j;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = list[left];
        do
        {
            do
                i++;
            while (list[i] < pivot);
            do
                j--;
            while (list[j] > pivot);
            if (i < j)
                swap(&list[i], &list[j]);

        } while (i < j);
    }
    else
        return;
    swap(&list[left], &list[j]);
    quickSort(list, left, j - 1);
    quickSort(list, j + 1, right);
}

void merge(int *initList, int *mergeList, int i, int m, int n)
{
    //정렬된 initList[i:m]과 정렬된mergeList[m+1:n] mergeList[i:n]에 정렬되서 합병됨
    int m2, i2, t;
    m2 = m + 1;
    i2 = i;

    while (i <= m && m2 <= n)
    {
        if (initList[i] <= initList[m2])
            mergeList[i2++] = initList[i++];
        else
            mergeList[i2++] = initList[m2++];
    }
    if (i > m)
        for (t = m2; t <= n; t++)
            mergeList[t] = initList[t];
    else
        for (t = i; t <= m; t++)
            mergeList[i2 + t - i] = initList[t];
}

void mergePass(int *initList, int *mergeList, int n, int s)
{
    int i, j;
    for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
    {
        merge(initList, mergeList, i, i + s - 1, i + 2 * s - 1);
    }
    if (i + s - 1 < n)
    {
        merge(initList, mergeList, i, i + s - 1, n);
    }
    else
    {
        for (j = i; j <= n; j++)
            mergeList[j] = initList[j];
    }
}

void mergeSort(int *list, int *extra, int n)
{
    int s = 1;
    while (s < n)
    {
        mergePass(list, extra, n, s);
        s *= 2;
        mergePass(extra, list, n, s);
        s *= 2;
    }
}