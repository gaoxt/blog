/*
    04-树7 二叉搜索树的操作集 (30分)
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    N = 10;
    int arr[] = {5, 8, 6, 2, 4, 1, 0, 10, 9, 7};
    for (i = 0; i < N; i++)
    {
        X = arr[i];
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    N = 5;
    int arr1[] = {6, 3, 10, 0, 5};
    for (i = 0; i < N; i++)
    {
        X = arr1[i];
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    N = 5;
    int arr2[] = {5, 7, 0, 10, 3};
    for (i = 0; i < N; i++)
    {
        X = arr2[i];
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
void InorderTraversal(BinTree BT)
{
    if (BT)
    {
        InorderTraversal(BT->Left);
        printf("%d", BT->Data);
        InorderTraversal(BT->Right);
    }
}

BinTree Insert(BinTree BST, ElementType X)
{
    if (!BST)
    {
        BST = malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else
    {
        if (X > BST->Data)
        {
            BST->Right = Insert(BST->Right, X);
        }
        else if (X < BST->Data)
        {
            BST->Left = Insert(BST->Left, X);
        }
    }
    return BST;
}

Position FindMin(BinTree BST)
{
    if (!BST)
        return NULL;
    else if (!BST->Left)
        return BST;
    else
        return FindMin(BST->Left);
}

Position FindMax(BinTree BST)
{
    if (BST)
        while (BST->Right)
            BST = BST->Right;

    return BST;
}

Position Find(BinTree BST, ElementType X)
{
    while (BST)
    {
        if (X > BST->Data)
        {
            BST = BST->Right;
        }
        else if (X < BST->Data)
        {
            BST = BST->Left;
        }
        else
        {
            return BST;
        }
    }
    return NULL;
}

BinTree Delete(BinTree BST, ElementType X)
{
    if (!BST)
    {
        printf("Not Found\n");
        return BST;
    }

    Position Tmp;
    if (X > BST->Data)
    {
        BST->Right = Delete(BST->Right, X);
    }
    else if (X < BST->Data)
    {
        BST->Left = Delete(BST->Left, X);
    }
    else
    {
        if (BST->Left && BST->Right)
        {
            Tmp = FindMin(BST->Right);
            BST->Data = Tmp->Data;
            BST->Right = Delete(BST->Right, BST->Data);
        }
        else
        {
            Tmp = BST;
            if (!BST->Left)
                BST = BST->Right;
            else if (!BST->Right)
                BST = BST->Left;
            free(Tmp);
        }
    }
    return BST;
}