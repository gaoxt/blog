/*
    06-图1 列出连通集 (25分)
    建立二维数组，遍历一遍DFS和BFS。
*/
#include <stdio.h>
#include <stdlib.h>

#define N 15

void ListComponents_DFS();
void ListComponents_BFS();
void DFS(int V);
void BFS(int V);
void InitVisit();

int n = 8;
int Visited[N];
int G[N][N] = {0};

int main()
{
    int E = 6;

    for (int i = 0; i < E; i++)
    {
        int a, b;
        int arr[6][2] = {{0, 7},
                         {0, 1},
                         {2, 0},
                         {4, 1},
                         {2, 4},
                         {3, 5}};
        a = arr[i][0];
        b = arr[i][1];
        G[b][a] = G[a][b] = 1;
    }
    ListComponents_DFS();
    InitVisit();
    ListComponents_BFS();

    return 0;
}

void ListComponents_DFS()
{
    for (int V = 0; V < n; V++)
        if (!Visited[V])
        {
            printf("{ ");
            DFS(V);
            printf("}\n");
        }
}

void ListComponents_BFS()
{
    for (int V = 0; V < n; V++)
        if (!Visited[V])
        {
            printf("{ ");
            BFS(V);
            printf("}\n");
        }
}

void DFS(int V)
{
    Visited[V] = 1;
    printf("%d ", V);
    for (int i = 0; i < n; i++)
    {
        if (G[V][i] && !Visited[i])
            DFS(i);
    }
}

void BFS(int V)
{
    const int MAX_SIZE = 100;
    int Queue[MAX_SIZE];
    int first = -1, last = -1;

    Queue[++last] = V; //入队
    Visited[V] = 1;
    while (first < last) //当队不为空时
    {
        int F = Queue[++first]; //出队
        printf("%d ", F);
        for (int i = 0; i < n; i++)
        {
            if (G[F][i] && !Visited[i])
            {
                Queue[++last] = i; //入队
                Visited[i] = 1;
            }
        }
    }
}

void InitVisit()
{
    for (int i = 0; i < N; i++)
        Visited[i] = 0;
}