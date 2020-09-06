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
//前序递归遍历
void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
//中序递归遍历
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

/*
三种情况：
1.要删除的X是叶子结点，直接拿掉。
2.要删除的X有一个孩子，把X的上一个结点指向它的孙子结点。
3.要删除的X左右两边都有孩子，用右子树最小元或左子树最大元代替它。
*/
BinTree Delete(BinTree BST, ElementType X)
{
    if (!BST)
    {
        printf("Not Found\n");
        return BST;
    }

    Position Tmp;
    //删除结点X比当前结点Data大或小，通过递归找到X。
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
        //找到X后，发现X有左右子结点，找到右树最小元或左树最大元代替被删结点。
        if (BST->Left && BST->Right)
        {
            Tmp = FindMin(BST->Right);
            BST->Data = Tmp->Data;
            BST->Right = Delete(BST->Right, BST->Data);
        }
        else
        {
            Tmp = BST;
            //X有一个孩子的情况，BST直接指向下一个结点。
            if (!BST->Left)
                BST = BST->Right;
            else if (!BST->Right)
                BST = BST->Left;
            free(Tmp);
        }
    }
    return BST;
}