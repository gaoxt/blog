/*
    KMP 串的模式匹配 (25分)
    解题思路：
    1.直接使用strstr()函数匹配，T=O(n*m)
    2.分析pattern，可以从末尾开始匹配，最好可达 T=O(n)，但是最差也是 T=O(n*m)。
    3.模式匹配中最出名之一KMP算法 T=O(n+m)
    传统匹配是逐字匹配，string会不断回溯与pattern进行匹配。
    KMP是利用pattern的特性，match分析出最长小子串，跳跃子串匹配，并且string不会回溯，指针只往前走一次。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Position;
#define NotFound -1
Position KMP(char *string, char *pattern);
void BuildMatch(char *pattern, int *match);

int main()
{
    int n = 3;
    char string[101] = {"abcabcabcabcacabxy"};
    char pattern[3][101] = {"abcabcacab", "cabcabcd", "abcabcabcabcacabxyz"};
    for (int i = 0; i < n; i++)
    {
        Position p = KMP(string, pattern[i]);
        if (p != NotFound)
        {
            if (i == n - 1)
            {
                printf("%s", (char *)string + p);
            }
            else
            {
                printf("%s\n", (char *)string + p);
            }
        }
        else
        {
            if (i == n - 1)
            {
                printf("Not Found");
            }
            else
            {
                printf("Not Found\n");
            }
        }
    }
    return 0;
}

//为所有pattern下标，标记match，形成PMT(Partial Match Table)部分匹配表
void BuildMatch(char *pattern, int *match)
{
    Position i, j;
    int m = strlen(pattern);
    match[0] = -1;

    /*
        j指pattern的每个下标，初始化match为-1表示前面没有重复。
        遍历pattern，如果发现重复字符则把match进行计数。
    */
    for (j = 1; j < m; j++)
    {
        //i最大为j-1
        i = match[j - 1];
        //匹配不上，并且i为合法下标时，不断回退pattern，回退次数不超过match累计的次数。
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            i = match[i];
        //pattern[i+1]下一个串开头 与当前串匹配，则标记pattern的下标累计+1。
        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}

Position KMP(char *string, char *pattern)
{
    int n = strlen(string);
    int m = strlen(pattern);
    Position s, p, *match;

    if (n < m)
        return NotFound;
    //match定义为Position数组下标可以通用 任何类型的串
    match = (Position *)malloc(sizeof(Position) * m);
    BuildMatch(pattern, match);
    s = p = 0;
    while (s < n && p < m)
    {
        //s和p的指针同时位移，直到不相等。
        if (string[s] == pattern[p])
        {
            s++;
            p++;
        }
        /*
            p=0时，p的第一个字符与s的第一个字符不匹配，s++指针下移。
            p>0避免段错误。
            不相等的时候，回溯指针p，match[p - 1]表示匹配子串尾部，+1表示匹配子串的下一个。
        */
        else if (p > 0)
            p = match[p - 1] + 1;
        else
            s++;
    }
    //p==m 表示 p指针已经到了p中match的末尾，则返回s的长度 减去 match子串的长度。
    return (p == m) ? (s - m) : NotFound;
}