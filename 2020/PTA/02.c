#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    int arr[] = {1, 3, 5};
    L1 = Read(arr, 3);
    int arr1[] = {2, 4, 6, 8, 10};
    L2 = Read(arr1, 5);
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Read(int arr[], int n)
{
    List L = (List)malloc(sizeof(PtrToNode));
    L->Next = NULL;
    if (n)
    {
        List r = L; //通过r记录表尾所在位置
        for (int i = 0; i < n; i++)
        {
            List s = (List)malloc(sizeof(struct Node));
            s->Data = arr[i];
            r->Next = s; //尾插法
            r = s;       //更新最新的表尾为s
        }
        r->Next = NULL;
    }
    return L;
}

void Print(List L)
{
    if (!L->Next)
        printf("NULL");
    while (L->Next)
    {
        L = L->Next;
        printf("%d ", L->Data);
    }
    printf("\n");
}

List Merge(List L1, List L2)
{
    List pa, pb, pc, L;
    L = (List)malloc(sizeof(struct Node));
    pa = L1->Next;
    pb = L2->Next;
    pc = L;
    while (pa && pb)
    {
        if (pa->Data <= pb->Data)
        {
            pc->Next = pa;
            pc = pa;
            pa = pa->Next;
        }
        else
        {
            pc->Next = pb;
            pc = pb;
            pb = pb->Next;
        }
    }
    pc->Next = pa ? pa : pb;
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}