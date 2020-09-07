/*
    04-树4 是否同一棵二叉搜索树 (25分)
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
    int v;
    Tree Left, Right;
    int flag;
};

//创建一个数据值为V的新节点
Tree NewNode(int V)
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T->Left = T->Right = NULL;
    T->flag = 0;
    return T;
}

//向T中插入数据值为V的节点
Tree Insert(Tree T, int V)
{
    if (!T)
        T = NewNode(V);
    else
    {
        if (V > T->v)
            T->Right = Insert(T->Right, V);
        else
            T->Left = Insert(T->Left, V);
    }
    return T;
}

//创建含有N个节点的二叉搜索树
Tree MakeTree(int N)
{
    Tree T;
    int i, V;

    scanf("%d", &V);
    T = NewNode(V);
    for (i = 1; i < N; i++)
    {
        scanf("%d", &V);
        T = Insert(T, V);
    }
    return T;
}

//检查一个序列中的一个数是否合法
int check(Tree T, int V)
{
    if (T->flag)
    {
        if (V < T->v)
            return check(T->Left, V);
        else if (V > T->v)
            return check(T->Right, V);
        //T->flag为1，并且V==T->v，则说明节点重复了
        else
            return 0;
    }
    else
    {
        //对于从上至下遇到的第一个没被访问过的节点
        //如果值相等，则符合题意
        if (V == T->v)
        {
            T->flag = 1;
            return 1;
        }
        //如果值不相等，则说明不是同一棵二叉搜索树
        else
            return 0;
    }
}

//接收一个待判定序列，并按顺序逐个检查
int Judge(Tree T, int N)
{
    //此处flag为1说明有错误，即两棵二叉搜索树不一样
    int i, V, flag = 0;

    scanf("%d", &V);
    if (V != T->v)
        flag = 1; //有错误
    else
        T->flag = 1; //被标记已经访问过
    for (i = 1; i < N; i++)
    {
        scanf("%d", &V);
        if ((!flag) && (!check(T, V)))
            flag = 1;
    }
    if (flag)
        return 0;
    else
        return 1;
}

//将T中各节点flag归零
void ResetT(Tree T)
{
    if (T->Left)
        ResetT(T->Left);
    if (T->Right)
        ResetT(T->Right);
    T->flag = 0;
}

//释放T所占用的内存空间
void FreeTree(Tree T)
{
    if (T->Left)
        FreeTree(T->Left);
    if (T->Right)
        FreeTree(T->Right);
    free(T);
}

int main(void)
{
    int N, L, i;
    Tree T;

    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        T = MakeTree(N);
        for (i = 0; i < L; i++)
        {
            if (Judge(T, N))
                printf("Yes\n");
            else
                printf("No\n");
            ResetT(T);
        }
        FreeTree(T);
        scanf("%d", &N);
    }

    return 0;
}