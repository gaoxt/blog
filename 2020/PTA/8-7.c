/*
    08-图7 公路村村通 (30分)
    最小生成树，贪心算法 之 Prim算法
*/
#include <stdio.h>
#include <stdlib.h>

//MGraph定义的程序头
#define MaxVertexNum 1000 //最大顶点数
#define INFINITY 3000     //无穷大的最短路径，无符号整数
typedef int Vertex;       //用顶点下标表示顶点
typedef int WeightType;   //边的权值类型
#define ERROR -1

//MGraph LGraph边的定义
typedef struct ENode *PtrToNode;
struct ENode
{
    Vertex V1, V2;     //有向边<V1,V2>
    WeightType Weight; //权重
};
typedef PtrToNode Edge;

//MGraph图结点的定义
typedef struct GNode *PtrToGNode;

struct GNode
{
    int Nv;                                   //顶点数
    int Ne;                                   //边数
    WeightType G[MaxVertexNum][MaxVertexNum]; //邻接矩阵
};

typedef PtrToGNode MGraph; //以邻接矩阵存储的图类型

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
} AdjList[MaxVertexNum];     /* AdjList是邻接表类型 */

// LGraph 图结点的定义
typedef struct LGNode *PtrToLGNode;
struct LGNode
{
    int Nv;    /* 顶点数 */
    int Ne;    /* 边数   */
    AdjList G; /* 邻接表 */
};
typedef PtrToLGNode LGraph; //以邻接表方式存储的图类型

MGraph CreateGraph(int VertexNum);
LGraph CreateLGraph(int VertexNum);

MGraph BuildGraph();
void InsertEdge(MGraph Graph, Edge E);
void InsertLGEdge(LGraph Graph, Edge E);
Vertex FindMinDist(MGraph Graph, WeightType dist[]);
int Prim(MGraph Graph, LGraph MST);

int main()
{
    LGraph MST;
    MGraph MG = BuildGraph();
    printf("%d", Prim(MG, MST));
}

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv = 6, i;
    Graph = CreateGraph(Nv);
    Graph->Ne = 15;
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        int arr[15][3] = {{1, 2, 5},
                          {1, 3, 3},
                          {1, 4, 7},
                          {1, 5, 4},
                          {1, 6, 2},
                          {2, 3, 4},
                          {2, 4, 6},
                          {2, 5, 2},
                          {2, 6, 6},
                          {3, 4, 6},
                          {3, 5, 1},
                          {3, 6, 1},
                          {4, 5, 10},
                          {4, 6, 8},
                          {5, 6, 3}};
        for (i = 0; i < Graph->Ne; i++)
        {
            E->V1 = arr[i][0];
            E->V2 = arr[i][1];
            E->Weight = arr[i][2];

            //城市从1开始的，矩阵里是从0开始，需要--;
            E->V1--;
            E->V2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
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
        }
    }
    return Graph;
}
LGraph CreateLGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */

    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct LGNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    //插入边<V1,V2>
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

void InsertLGEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}

/* 邻接矩阵存储 - Prim最小生成树算法 */
Vertex FindMinDist(MGraph Graph, WeightType dist[])
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    WeightType MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; V++)
    {
        if (dist[V] != 0 && dist[V] < MinDist)
        {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V;          /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV;        /* 返回对应的顶点下标 */
    else
        return ERROR; /* 若这样的顶点不存在，返回-1作为标记 */
}

int Prim(MGraph Graph, LGraph MST)
{ /* 将最小生成树保存为邻接表存储的图MST，返回最小权重和 */
    WeightType dist[MaxVertexNum], TotalWeight;
    Vertex parent[MaxVertexNum], V, W;
    int VCount;
    Edge E;

    /* 初始化。默认初始点下标是0 */
    for (V = 0; V < Graph->Nv; V++)
    {
        /* 这里假设若V到W没有直接的边，则Graph->G[V][W]定义为INFINITY */
        dist[V] = Graph->G[0][V];
        parent[V] = 0; /* 暂且定义所有顶点的父结点都是初始点0 */
    }
    TotalWeight = 0; /* 初始化权重和     */
    VCount = 0;      /* 初始化收录的顶点数 */
    /* 创建包含所有顶点但没有边的图。注意用邻接表版本 */
    MST = CreateLGraph(Graph->Nv);
    E = (Edge)malloc(sizeof(struct ENode)); /* 建立空的边结点 */

    /* 将初始点0收录进MST */
    dist[0] = 0;
    VCount++;
    parent[0] = -1; /* 当前树根是0 */

    while (1)
    {
        V = FindMinDist(Graph, dist);
        /* V = 未被收录顶点中dist最小者 */
        if (V == ERROR) /* 若这样的V不存在 */
            break;      /* 算法结束 */

        /* 将V及相应的边<parent[V], V>收录进MST */
        E->V1 = parent[V];
        E->V2 = V;
        E->Weight = dist[V];
        InsertLGEdge(MST, E);
        TotalWeight += dist[V];
        dist[V] = 0;
        VCount++;

        for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
            if (dist[W] != 0 && Graph->G[V][W] < INFINITY)
            {
                /* 若W是V的邻接点并且未被收录 */
                if (Graph->G[V][W] < dist[W])
                {
                    /* 若收录V使得dist[W]变小 */
                    dist[W] = Graph->G[V][W]; /* 更新dist[W] */
                    parent[W] = V;            /* 更新树 */
                }
            }
    }                       /* while结束*/
    if (VCount < Graph->Nv) /* MST中收的顶点不到|V|个 */
        TotalWeight = ERROR;
    return TotalWeight; /* 算法执行完毕，返回最小权重和或错误标记 */
}