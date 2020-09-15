/*
    10-排序4 统计工龄 (20分)
    思路：排序后数组计数、桶排序
*/

#include <stdio.h>
#include <stdlib.h>
#define maxage 51

typedef int ElementType;
void Bucket_sort(ElementType A[], int N);

int main()
{
    int N = 8;
    int A[] = {10, 2, 0, 5, 7, 2, 5, 2};
    Bucket_sort(A, N);
    return 0;
}

void Bucket_sort(ElementType A[], int N)
{
    int count[maxage] = {0};
    for (int i = 0; i < N; i++)
    {
        if (count[A[i]])
        {
            count[A[i]] += 1;
        }
        else
        {
            count[A[i]] = 1;
        }
    }
    for (int i = 0; i < maxage; i++)
    {
        if (count[i] > 0)
        {
            printf("%d:%d\n", i, count[i]);
        }
    }
}
