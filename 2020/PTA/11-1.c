/*
    11-散列1 电话聊天狂人 (25分)
    三种解法：
    1.排序，读入所有11位号码进行排序，扫描有序数组统计号码出现次数，更新最大次。 缺点：动态插入效率低。
    2.直接映射，为每个唯一号码创建空数组，初始化0，插入时数值累计1次，扫描出累加值最多的。 缺点：2x10^10x2bytes约等37GB。
    3.间接映射，分析号码规律，取后5位做散列，碰撞则用分离链法表示。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 12 //C语言中 字符串结尾 占一个位

typedef struct ListNode *Position;
typedef struct HTable *HashTable;
struct ListNode
{
    char data[N];  //电话号码
    Position next; //下一个指针
    int count;     //计数器
};
struct HTable
{
    int size;      //表 最大长度
    Position list; //指向链表头结点的数组
};
HashTable CreatTable(int n);
void Insert(HashTable H, char *key);
void Solve(HashTable H);
int NextPrime(int n);

int main()
{
    int i, n = 4;
    HashTable H;
    //最大为2n的空间。
    H = CreatTable(n * 2);
    char arr[8][N] = {"13005711862", "13588625832",
                      "13505711862", "13088625832",
                      "13588625832", "18087925832",
                      "15005713862", "13588625832"};
    for (i = 0; i < 2 * n; i++)
    {
        Insert(H, arr[i]);
    }
    Solve(H);
    return 0;
}

HashTable CreatTable(int n)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct HTable));
    H->size = NextPrime(n);
    H->list = (Position)malloc(H->size * sizeof(struct ListNode));
    //初始化H，别留空，好习惯。
    for (i = 0; i < H->size; i++)
    {
        H->list[i].data[0] = '\0';
        H->list[i].next = NULL;
        H->list[i].count = 0;
    }
    return H;
}

void Insert(HashTable H, char *key)
{
    Position p, NewCall;
    int index;
    /*
        Key % P 除留余数法
        atoi()字符强转整数
        key+6  key指第1位，+6表示从第7位开始，取后5位号码。
    */
    index = (atoi(key + 6)) % H->size;
    //从链表第1个结点开始
    p = H->list[index].next;
    //链表没到末尾，并且Key没找到时。
    while (p && strcmp(p->data, key))
    {
        p = p->next;
    }

    //找到则自增，没找到则插入新号码。
    if (p)
        p->count++;
    else
    {
        NewCall = (Position)malloc(sizeof(struct ListNode));
        //把key复制给NewCall
        strcpy(NewCall->data, key);
        NewCall->count = 1;
        //切换为最新的链表头
        NewCall->next = H->list[index].next;
        H->list[index].next = NewCall;
    }
}

void Solve(HashTable H)
{
    int i, max = 0, num;
    char min[N];
    Position p;
    //扫描 H整个 散列表 中的链表
    for (i = 0; i < H->size; i++)
    {
        //从头结点0 的下一个结点开始循环
        p = H->list[i].next;
        while (p)
        {
            // 更新最大的通话次数
            if (p->count > max)
            {
                max = p->count;
                strcpy(min, p->data);
                num = 1;
            }
            else if (p->count == max)
            {
                //狂人计数
                num++;
                //更新狂人的最小手机号码，strcmp按ASCII比较两个字符串
                if (strcmp(p->data, min) < 0)
                    strcpy(min, p->data);
            }
            p = p->next;
        }
    }
    //狂人有多个的时，更新最小号码 + 统计人数。
    if (num == 1)
        printf("%s %d\n", min, max);
    else
        printf("%s %d %d\n", min, max, num);
}

//获取长度为n的一个素数
int NextPrime(int n)
{
    int i, j;
    n = (n % 2) ? n + 2 : n + 1; //从大于n的下一个奇数开始
    for (i = n;; i += 2)
    {
        for (j = 3; j * j <= i && i % j; j++)
            ;
        if (j * j > i)
            break;
    }
    return i;
}