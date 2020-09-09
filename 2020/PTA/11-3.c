/*
    11-散列3 QQ帐户的申请与登陆 (25分)
    解法：间接映射，取后qq号做散列，碰撞则用分离链法表示。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 200000
typedef struct ListNode *Position;
typedef struct HTable *HashTable;
struct ListNode
{
    char account[15], password[20]; //Q号和密码
    Position next;                  //下一个指针
};
struct HTable
{
    int size;      //表 最大长度
    Position list; //指向链表头结点的数组
};

HashTable CreatTable(int n);
void Insert(HashTable H, char account[], char password[]);
Position Find(HashTable H, char account[]);
int NextPrime(int n);
int main()
{
    int n = 5;
    char c, account[15], password[20];
    HashTable H = CreatTable(n);

    char arr[5][3][20] = {{"L", "1234567890", "myQQ@qq.com"},
                          {"N", "1234567890", "myQQ@qq.com"},
                          {"N", "1234567890", "myQQ@qq.com"},
                          {"L", "1234567890", "myQQ@qq"},
                          {"L", "1234567890", "myQQ@qq.com"}};
    for (int i = 0; i < n; i++)
    {

        c = arr[i][0][0];
        strcpy(account, arr[i][1]);
        strcpy(password, arr[i][2]);
        if (c == 'N')
            Insert(H, account, password);
        else if (c == 'L')
        {
            Position p = Find(H, account);
            if (!p)
                printf("ERROR: Not Exist\n");
            else
            {
                if (strcmp(p->password, password) == 0)
                    printf("Login: OK\n");
                else
                    printf("ERROR: Wrong PW\n");
            }
        }
    }
    return 0;
}

int isprime(int x)
{
    int i;
    for (i = 2; i * i <= x; i++)
        if (x % i == 0)
            return 0;
    return 1;
}
//获取长度为n的一个素数
int nextprime(int n)
{
    if (n == 1)
        return 2;
    int x = n % 2 == 1 ? n : n + 1;
    while (x <= MAXSIZE)
    {
        if (isprime(x))
            return x;
        x += 2;
    }
}

HashTable CreatTable(int n)
{
    HashTable h = (HashTable)malloc(sizeof(struct HTable));
    h->size = nextprime(n);
    h->list = (Position)malloc(h->size * sizeof(struct ListNode));
    int i;
    for (i = 0; i < h->size; i++)
    {
        h->list[i].account[0] = h->list[i].password[0] = '\0';
        h->list[i].next = NULL;
    }
    return h;
}

//除留余数法
int Hash(int x, int p)
{
    return x % p;
}

Position Find(HashTable H, char account[])
{
    //从Q号第4位开始取余
    int pos = Hash(atoi(account + 3), H->size);
    Position p = H->list[pos].next;
    //链表没到末尾，并且Q号没找到时。
    while (p && strcmp(p->account, account) != 0)
        p = p->next;
    return p;
}

void Insert(HashTable H, char account[], char password[])
{
    Position p = Find(H, account);
    if (!p)
    {
        Position newAccount = (Position)malloc(sizeof(struct ListNode));
        strcpy(newAccount->account, account);
        strcpy(newAccount->password, password);
        int pos = Hash(atoi(account + 3), H->size);
        newAccount->next = H->list[pos].next; /* 新元素插入表头 */
        H->list[pos].next = newAccount;
        printf("New: OK\n");
    }
    else
        printf("ERROR: Exist\n");
}