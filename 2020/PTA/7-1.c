/*
    7-1 还原二叉树 (8分)
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 50

int GetHeight(char *a, char *b, int len)
{
    int i, LH, RH;
    if (len == 0)
        return 0;
    else
    {
        for (i = 0; i < len; ++i)
            //通过先序根 每次找到 中序 的根结点位置
            if (b[i] == a[0])
                break;

        //求左右子树高度
        LH = GetHeight(a + 1, b, i);
        RH = GetHeight(a + 1 + i, b + 1 + i, len - i - 1);
        //取左右子树较大的深度(+1表示根)
        return (LH > RH ? LH : RH) + 1;
    }
}
/*
    先序遍历：根左右 ABDFGHIEC
    中序遍历：左根右 FDHGIBEAC
    第一轮
    先序：根A 左BDFGHIE 右C
    中序：左FDHGIBE 根A 右C
    第二轮
    先序：根B 左DFGHI 右E
    中序：左FDHGI 根B 右E
    第三轮
    先序：根D 左F 右GHI
    中序：左F 根D 右HGI
    第四轮
    先序：根G 左H 右I
    中序：左H 根G 右I

    解题思路：
    1.求树高 得先求 左右子树高度
    2.通过先序+中序还原左右子树高度进行比较。
*/
int main()
{
    int n = 9;
    char arr1[MAXN] = "ABDFGHIEC";
    char arr2[MAXN] = "FDHGIBEAC";
    printf("%d", GetHeight(arr1, arr2, n));

    return 0;
}