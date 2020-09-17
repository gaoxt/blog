/*
    03-树1 树的同构 (25分)
    通过数组建立两棵二叉树，递归的判断子树是否同构。
*/
#include <stdio.h>

#define Tree int
typedef struct TreeNode
{
    Tree Data;
    Tree Left, Right;
} TNode;

TNode T1[10], T2[10];
Tree BuildTree(TNode T[], char arr[8][3][1], int N); //创建树
int Isomorphic(int R1, int R2);                      //判断树是否同构

int main()
{
    Tree R1, R2;
    char arr[8][3][1] = {
        {"A", "1", "2"},
        {"B", "3", "4"},
        {"C", "5", "-"},
        {"D", "-", "-"},
        {"E", "6", "-"},
        {"G", "7", "-"},
        {"F", "-", "-"},
        {"H", "-", "-"}};
    R1 = BuildTree(T1, arr, 8);
    char arr2[8][3][1] = {
        {"G", "-", "4"},
        {"B", "7", "6"},
        {"F", "-", "-"},
        {"A", "5", "1"},
        {"H", "-", "-"},
        {"C", "0", "-"},
        {"D", "-", "-"},
        {"E", "2", "-"}};
    R2 = BuildTree(T2, arr2, 8);
    if (Isomorphic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

//构建树并返回根节点位置
Tree BuildTree(TNode T[], char arr[8][3][1], int N)
{
    int root = -1;
    if (N)
    {
        int i;
        int check[N]; //设定一个check，记录遍历完后的0，也就是root。
        for (i = 0; i < N; i++)
            check[i] = 0;
        for (i = 0; i < N; i++)
        {
            char cl, cr;
            T[i].Data = arr[i][0][0];
            cl = arr[i][1][0];
            cr = arr[i][2][0];
            if (cl != '-')
            {
                //ascii计算，cl如果是'2'则是50，'0'是48，字符相减'0'得cl的整数。
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else
                T[i].Left = -1;

            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else
                T[i].Right = -1;
        }
        for (i = 0; i < N; i++)
        {
            if (!check[i])
                break;
        }
        root = i;
    }
    return root;
}

int Isomorphic(int R1, int R2)
{
    if (R1 == -1 && R2 == -1) //如果两颗树均为空，认为他们同构
        return 1;
    if ((R1 == -1 && R2 != -1) || (R1 != -1 && R2 == -1)) //如果两棵树只有一颗为空，认为他们不同构
        return 0;
    if (T1[R1].Data != T2[R2].Data) //如果两棵树根结点的值都不同，则不同构
        return 0;
    if (T1[R1].Left == -1 && T2[R2].Left == -1) //l两棵树左边子树都为空就去递归的找他们的右子树
        return Isomorphic(T1[R1].Right, T2[R2].Right);
    //如果左子树相同且左子树数据也相同
    if ((T1[R1].Left != -1 && T2[R2].Left != -1) && (T1[T1[R1].Left].Data == T2[T2[R2].Left].Data))
    {
        return Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right); //然后递归的进入左右子树去判断是否同构
    }
    else
    { //如果两个左子树有为空的或者两个左子树数据不相同，就交换左右子树递归的去判断
        return Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left);
    }
}
