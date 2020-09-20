/*
    06-图3 六度空间 (30分)
    数组存储，BFS中for循环多次空数据，搜索效率较低，通过BFS搜索累计访问6以内层序的节点。
*/

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100 //最大顶点数

int G[MaxVertexNum][MaxVertexNum] = {0}, N, M;
int Visited[MaxVertexNum] = {0};

int BFS(int V);
void InitVisit();

int main()
{
    N = 10;
    M = 9;
    int u, v, i;
    int arr[9][2] = {{1, 2},
                     {2, 3},
                     {3, 4},
                     {4, 5},
                     {5, 6},
                     {6, 7},
                     {7, 8},
                     {8, 9},
                     {9, 10}};
    for (i = 0; i < M; i++)
    {
        v = arr[i][0];
        u = arr[i][1];
        v--;
        u--;
        G[u][v] = G[v][u] = 1;
    }

    double ratio;
    int count;
    for (i = 0; i < N; i++)
    {
        InitVisit();
        count = BFS(i);
        ratio = count * 1.0 / N * 100;
        printf("%d: %.2lf%%\n", i + 1, ratio);
    }
    return 0;
}

int BFS(int V)
{
    const int MAX_SIZE = 100;
    int Queue[MAX_SIZE];
    int first = -1, rear = -1;

    int count, level, last, tail;

    Visited[V] = 1;
    count = 1;
    level = 0;
    last = V;

    Queue[++rear] = V;   //入队
    while (first < rear) //当队不为空时
    {
        int F = Queue[++first]; //出队
        for (int i = 0; i < N; i++)
        {
            if (G[F][i] && !Visited[i])
            {
                Visited[F] = 1;
                Queue[++rear] = i; //入队并且更新tail开头
                tail = i;
                count++;
            }
        }
        //当前i层遍历完后，层序+1 和 更新下一层tail开头
        if (F == last)
        {
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
    return count;
}

void InitVisit()
{
    for (int i = 0; i < MaxVertexNum; i++)
        Visited[i] = 0;
}