/*
    01-复杂度3 二分查找 (20分)
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);
int main()
{
    List L;
    ElementType X = 31;
    Position P;
    int arr[] = {12, 31, 55, 89, 101};
    L = ReadInput(arr, 5);
    P = BinarySearch(L, X);
    printf("%d\n", P);

    return 0;
}

List ReadInput(int arr[], int n)
{
    List L;
    L = malloc(sizeof(List));
    L->Last = 0; //避免野指针
    for (int i = 0; i < n; i++)
    {
        L->Data[i + 1] = arr[i];
        L->Last++;
    }
    return L;
}

//二分法，一个有序数组内，每次查找下标总量/2进行左右对比。
Position BinarySearch(List L, ElementType X)
{

    int left = 1, right = L->Last, mid;

    while (left <= right)
    {
        if (L->Data[left] == X)
            return left;
        if (L->Data[right] == X)
            return right;
        mid = (left + right) / 2;
        if (L->Data[mid] == X)
            return mid;
        if (L->Data[mid] < X)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return NotFound;
}