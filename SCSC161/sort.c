//
// Created by 김아동 on 2016. 6. 1..
//

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
            while (list[i] < pivot && i <= right);
            do
                j--;
            while (list[j] > pivot && j >= 0);
            if (i < j)
                swap(&list[i], &list[j]);

        } while (i < j);
        swap(&list[left], &list[j]);
        quickSort(list, left, j - 1);
        quickSort(list, j + 1, right);
    }

//    int *arr = list;
//    int i = left, j = right;
//    int pivot = arr[(left + right) / 2];
//
//    while (i <= j)
//    {
//        while (arr[i] < pivot)
//            i++;
//        while (arr[j] > pivot)
//            j--;
//        if (i <= j)
//        {
//            swap(&arr[i], &arr[j]);
//            i++;
//            j--;
//        }
//    }
//    if (left < j)
//        quickSort(arr, left, j);
//    if (i < right)
//        quickSort(arr, i, right);
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

void adjust(int *list, int root, int n)
{
    int temp, child, rootkey;
    temp = list[root];
    rootkey = list[root];
    child = 2 * root;
    while (child <= n)
    {
        if ((child < n) && (list[child] < list[child + 1]))
            child++;
        if (rootkey > list[child])
        {
            break;
        }
        else
        {
            list[child / 2] = list[child];
            child *= 2;
        }
    }
    list[child / 2] = temp;
}

void heapSort(int *list, int n)
{
    int i;
    for (i = n / 2; i > 0; --i)
        adjust(list, i, n);
    for (i = n - 1; i > 0; --i)
    {
        swap(&list[1], &list[i + 1]);
        adjust(list, 1, i);
    }
}