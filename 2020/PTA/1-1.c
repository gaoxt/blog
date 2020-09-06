/*
    01-复杂度1 最大子列和问题 (20分)
*/
#include <stdio.h>

//1.暴力破解，算出所有子列和，取最大。
int maxSubSum1(int a[], int N)
{
    int thisSum = 0, maxSum = 0;
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = i; j < N; j++)
        {
            //i到j的最大和
            thisSum = 0;
            //K循环的作用是暴力计算从i开始加到j的和。
            for (k = i; k <= j; k++)
            {
                thisSum += a[k];
            }
            if (thisSum > maxSum)
            {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

//2.暴力破解优化版，取消k循环，用a[j]++代替 k从头开始 计算出子列和。
int maxSubSum2(int a[], int N)
{
    int thisSum = 0, maxSum = 0;
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        thisSum = 0;
        for (j = i; j < N; j++)
        {
            thisSum += a[j];
            if (thisSum > maxSum)
            {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

//3.分支法，数据分割，合成治。分而治之。递归的分割数组，找到左右两边的递归和，再找到跨越边界的和 进行对比。
int maxSubSum3(int List[], int N)
{ /* 保持与前2种算法相同的函数接口 */
    return DivideAndConquer(List, 0, N - 1);
}

int DivideAndConquer(int List[], int left, int right)
{                                            /* 分治法求List[left]到List[right]的最大子列和 */
    int MaxLeftSum, MaxRightSum;             /* 存放左右子问题的解 */
    int MaxLeftBorderSum, MaxRightBorderSum; /*存放跨分界线的结果*/

    int LeftBorderSum, RightBorderSum;
    int center, i;

    if (left == right)
    { /* 递归的终止条件，子列只有1个数字 */
        if (List[left] > 0)
            return List[left];
        else
            return 0;
    }

    /* 下面是"分"的过程 */
    center = (left + right) / 2; /* 找到中分点 */
    /* 递归求得两边子列的最大和 */
    MaxLeftSum = DivideAndConquer(List, left, center);
    MaxRightSum = DivideAndConquer(List, center + 1, right);

    /* 下面求跨分界线的最大子列和 */
    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for (i = center; i >= left; i--)
    { /* 从中线向左扫描 */
        LeftBorderSum += List[i];
        if (LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    } /* 左边扫描结束 */

    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for (i = center + 1; i <= right; i++)
    { /* 从中线向右扫描 */
        RightBorderSum += List[i];
        if (RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    } /* 右边扫描结束 */

    /* 下面返回"治"的结果 */
    return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int Max3(int A, int B, int C)
{ /* 返回3个整数中的最大值 */
    return A > B ? A > C ? A : C : B > C ? B : C;
}

// 4.在线处理，即时处理。充分利用了子列和是负数就抛弃的技巧。
int maxSubSum4(int a[], int N)
{
    int thisSum = 0, maxSum = 0;
    for (int i = 0; i < N; i++)
    {
        thisSum += a[i];
        if (thisSum < 0)
            thisSum = 0;
        else if (thisSum > maxSum)
            maxSum = thisSum;
    }
    return maxSum;
}

int main()
{
    int N = 6;
    int arr[] = {-2, 11, -4, 13, -5, -2};
    printf("%d\n", maxSubSum4(arr, N));
}