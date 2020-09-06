/*
    02-线性结构1 两个有序链表序列的合并 (15分)
*/
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
    //把头除外的链指给pa、pb
    pa = L1->Next;
    pb = L2->Next;
    pc = L;
    while (pa && pb)
    {
        //比较两头链数据，每次给L追加较小的数，直到pa或pb某个遍历完。
        if (pa->Data <= pb->Data)
        {
            pc->Next = pa; //为L追加已下移的数据(给L织毛衣)
            pc = pa;       //pc进位，方便pc->Next指向下一个。
            pa = pa->Next; //指针下移
        }
        else
        {
            pc->Next = pb;
            pc = pb;
            pb = pb->Next;
        }
    }
    //pa遍历比较完了，说明pb中还有大的数据，追加到L后。
    pc->Next = pa ? pa : pb;
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}