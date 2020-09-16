/*
    07-图6 旅游规划 (25分)
*/

#include <stdio.h>
#include <stdlib.h>
//MGraph定义的程序头
#define MaxVertexNum 100 //最大顶点数
#define INFINITY 65535   //无穷大的最短路径，无符号整数
typedef int Vertex;      //用顶点下标表示顶点
typedef int WeightType;  /* 边的权值设为整型 */
#define ERROR -1

//边的定义
typedef struct ENode *PtrToNode;
struct ENode
{
    Vertex V1, V2;   //有向边<V1,V2>
    WeightType dist; //距离
    WeightType cost; //费用
};
typedef PtrToNode Edge;

//圆结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                      //顶点数
    int Ne;                                      //边数
    WeightType G[MaxVertexNum][MaxVertexNum];    //邻接矩阵-存长度
    WeightType cost[MaxVertexNum][MaxVertexNum]; //邻接矩阵-存费用
};

typedef PtrToGNode MGraph; //以邻接矩阵存储的图类型
MGraph CreateGraph(int VertexNum);
MGraph BuildGraph();
void InsertEdge(MGraph Graph, Edge E);
Vertex FindMinDist(MGraph Graph, int dist[], int collected[]);
void Dijkstra(MGraph Graph, int dist[], int cost[], Vertex S);

int main()
{
    int dist[MaxVertexNum] = {INFINITY};
    int cost[MaxVertexNum] = {INFINITY};
    int strpos = 0;
    int despos = 3;
    MGraph G = BuildGraph();
    Dijkstra(G, dist, cost, strpos);
    printf("%d %D\n", dist[despos], cost[despos]);
    return 0;
}

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv = 4, i;
    Graph = CreateGraph(Nv);
    Graph->Ne = 5;
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        int arr[5][4] = {{0, 1, 1, 20}, {1, 3, 2, 30}, {0, 3, 4, 10}, {0, 2, 2, 20}, {2, 3, 1, 20}};
        for (i = 0; i < Graph->Ne; i++)
        {
            E->V1 = arr[i][0];
            E->V2 = arr[i][1];
            E->dist = arr[i][2];
            E->cost = arr[i][3];
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    //插入边<V1,V2>
    Graph->G[E->V1][E->V2] = E->dist;
    Graph->G[E->V2][E->V1] = E->dist;
    Graph->cost[E->V1][E->V2] = E->cost;
    Graph->cost[E->V2][E->V1] = E->cost;
}

MGraph CreateGraph(int VertexNum)
{
    //初始化一个有VertexNum个顶点 但没有边的 图
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    //初始化邻接矩阵，默认顶点编号为0，到(Graph->Nv - 1)
    for (V = 0; V < Graph->Nv; V++)
    {
        for (W = 0; W < Graph->Nv; W++)
        {
            Graph->G[V][W] = INFINITY;
            Graph->cost[V][W] = INFINITY;
        }
    }
    return Graph;
}

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; V++)
    {
        if (collected[V] == 0 && dist[V] < MinDist)
        {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V;          /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV;        /* 返回对应的顶点下标 */
    else
        return ERROR; /* 若这样的顶点不存在，返回错误标记 */
}

void Dijkstra(MGraph Graph, int dist[], int cost[], Vertex S)
{
    int collected[MaxVertexNum];
    Vertex V, W;

    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
    for (V = 0; V < Graph->Nv; V++)
    {
        dist[V] = Graph->G[S][V];
        cost[V] = Graph->cost[S][V];
        collected[V] = 0;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    cost[S] = 0;
    collected[S] = 1;

    while (1)
    {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist(Graph, dist, collected);
        if (V == ERROR)                 /* 若这样的V不存在 */
            break;                      /* 算法结束 */
        collected[V] = 1;               /* 收录V */
        for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未被收录 */
            if (collected[W] == 0 && Graph->G[V][W] < INFINITY)
            {
                if (Graph->G[V][W] < 0) /* 若有负边 */
                    return;
                /* 若收录V使得dist[W]变小 */
                if (dist[V] + Graph->G[V][W] < dist[W])
                {
                    dist[W] = dist[V] + Graph->G[V][W]; //更新dist[W]
                    cost[W] = cost[V] + Graph->cost[V][W];
                }
                else if ((dist[V] + Graph->G[V][W] == dist[W]) &&
                         (cost[W] > cost[V] + Graph->cost[V][W])) //若路径长度相等 取最小cost的
                {
                    cost[W] = cost[V] + Graph->cost[V][W];
                }
            }
    }
}