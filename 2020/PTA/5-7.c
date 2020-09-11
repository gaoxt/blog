/*
    05-树7 堆中的路径 (25分)
    解题思路：构建最小堆，打印路径。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1001
#define MINH -10001
int H[MAXN], size;

void Create();
void Insert(int X);

int main()
{
    int i, j, n, m, x;
    int arr[] = {46, 23, 26, 24, 10};
    int arr1[] = {5, 4, 3};
    Create();
    for (i = 0; i < 5; i++)
    {
        Insert(arr[i]);
    }
    for (i = 0; i < 3; i++)
    {
        j = arr1[i];
        //先打印查询位置的值
        printf("%d ", H[j]);
        //再打印它的父亲，沿根方向输出各结点，根的位置是1。
        while (j > 1)
        {
            j /= 2;
            printf("%d ", H[j]);
        }
        printf("\n");
    }
    return 0;
}

//设置空堆
void Create()
{
    size = 0;
    //设定 岗哨，Insert中H[i/2]无需判别下标越界。
    H[0] = MINH;
}

void Insert(int X)
{
    int i;
    //不断比较父结点[i/2]的位置，如果比X大，当前i得往前挪。
    for (i = ++size; H[i / 2] > X; i /= 2)
        H[i] = H[i / 2];
    //当前父结点比X小时，赋值给X。
    H[i] = X;
}