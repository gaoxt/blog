/*
    09-排序1 排序 (25分)
    简单排序 之 冒泡和插入(稳定，相同无Swap)
    区别：冒泡两数交换需要三步(比较、临时值、交换)，插入是直接往后错位(比较、交换)，所以在逆序对较少情况下，效率较高。
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

void Bubble_sort(ElementType A[], int N);
void Insert_sort(ElementType A[], int N);
void Print(ElementType A[], int N);

int main()
{
    int N = 11;
    int A[] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
    Bubble_sort(A, N);
    int A2[] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
    Insert_sort(A2, N);
    return 0;
}

void Bubble_sort(ElementType A[], int N)
{
    int P, i, Tmp, flag;
    //重复冒泡的过程，每次-1，直到数组为空。
    for (P = N - 1; P >= 0; P--)
    {
        flag = 0;
        //每趟冒泡交换相邻的两个数，大的往后放。
        for (i = 0; i < P; i++)
        {
            if (A[i] > A[i + 1])
            {
                Tmp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = Tmp;
                flag = 1;
            }
        }
        //完全有序没有Swap，则跳出。
        if (flag == 0)
            break;
    }
    Print(A, N);
}

void Insert_sort(ElementType A[], int N)
{
    int P, i, Tmp;
    //从第2张牌开始排序，直到最后。
    for (P = 1; P < N; P++)
    {
        Tmp = A[P]; //摸下张牌
        //如果当前牌比下张牌大，则交换位置。
        for (i = P; i > 0 && A[i - 1] > Tmp; i--)
            A[i] = A[i - 1];
        A[i] = Tmp;
    }
    Print(A, N);
}

void Print(ElementType A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
