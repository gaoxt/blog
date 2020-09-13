/*
    06-图1 列出连通集 (25分)
    建立邻接矩阵，遍历一遍DFS和BFS。
*/
#include <stdio.h>
#include <stdlib.h>

// 队列的定义
typedef int ElementType;
typedef struct QNode *Queue;
typedef int Position;
struct QNode
{
    ElementType *Data;    // 存储元素的数组
    Position Front, Rear; // 队列的头、尾指针
    int MaxSize;          // 队列最大容量
};

// 图的邻接矩阵表示法
#define MaxVertexNum 100 // 最大顶点数设为100
#define INFINITY 65535   // ∞设为双字节无符号整数的最大值65535
#define MAXSIZE 100
typedef int Vertex;     // 用顶点下标表示顶点,为整型
typedef int WeightType; // 边的权值设为整型
int Visited_BFS[MaxVertexNum];
int Visited_DFS[MaxVertexNum];

// 边的定义
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

// 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                   // 顶点数
    int Ne;                                   // 边数
    WeightType G[MaxVertexNum][MaxVertexNum]; // 邻接矩阵
};
typedef PtrToGNode MGraph;

void InsertEdge(MGraph Graph, Edge E);
int AddQ(Queue Q, ElementType X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
ElementType DeleteQ(Queue Q);

int IsEdge(MGraph Graph, Vertex V, Vertex W);
void Visit(Vertex V);
MGraph BuildGraph();
MGraph CreateGraph(int VertexNum);

void ListComponents_BFS(MGraph Graph);
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex));
void ListComponents_DFS(MGraph Graph);
void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex));

int main()
{
    MGraph G = BuildGraph();
    ListComponents_DFS(G);
    ListComponents_BFS(G);
    return 0;
}

void ListComponents_DFS(MGraph Graph)
{
    Vertex i;
    for (i = 0; i < Graph->Nv; i++)
    {
        if (!Visited_DFS[i])
        {
            printf("{");
            DFS(Graph, i, Visit);
            printf(" }");
            printf("\n");
        }
    }
}

void ListComponents_BFS(MGraph Graph)
{
    Vertex i;
    for (i = 0; i < Graph->Nv; i++)
    {
        if (!Visited_BFS[i])
        {
            printf("{");
            BFS(Graph, i, Visit);
            printf(" }");
            printf("\n");
        }
    }
}

void Visit(Vertex V)
{
    printf(" %d", V);
}

Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
int AddQ(Queue Q, ElementType X)
{
    if (IsFull(Q))
    {
        printf("队列满");
        return 0;
    }
    else
    {
        Q->Rear = (Q->Rear + 1) % Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return 1;
    }
}
int IsFull(Queue Q)
{
    return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

int IsEmpty(Queue Q)
{
    return (Q->Front == Q->Rear);
}

ElementType DeleteQ(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("队列空");
        return 0;
    }
    else
    {
        Q->Front = (Q->Front + 1) % Q->MaxSize;
        return Q->Data[Q->Front];
    }
}

MGraph CreateGraph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv = 8, i;
    Graph = CreateGraph(Nv);
    Graph->Ne = 6;
    if (Graph->Ne != 0)
    {
        int arr[6][2] = {{0, 7},
                         {0, 1},
                         {2, 0},
                         {4, 1},
                         {2, 4},
                         {3, 5}};
        E = (Edge)malloc(sizeof(struct ENode));
        for (i = 0; i < Graph->Ne; i++)
        {
            E->V1 = arr[i][0];
            E->V2 = arr[i][1];
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

// IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。
int IsEdge(MGraph Graph, Vertex V, Vertex W)
{
    return Graph->G[V][W] < INFINITY ? 1 : 0;
}

/*
    Breadth First Search
    *Visit 是个指向函数的指针，返回类型void，参数类型Vertex
*/
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{
    Queue Q;
    Vertex V, W;

    Q = CreateQueue(MAXSIZE);
    Visit(S);
    Visited_BFS[S] = 1;
    AddQ(Q, S);
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);
        for (W = 0; W < Graph->Nv; W++)
            if (!Visited_BFS[W] && IsEdge(Graph, V, W))
            {
                Visit(W);
                Visited_BFS[W] = 1;
                AddQ(Q, W);
            }
    }
}

//Depth First Search
void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex))
{
    Vertex W;
    Visited_DFS[V] = 1;
    Visit(V);
    for (W = 0; W < Graph->Nv; W++)
    {
        if (Graph->G[V][W] == 1 && !Visited_DFS[W])
        {
            DFS(Graph, W, Visit);
        }
    }
}