/*
    06-图3 六度空间 (30分)
    六度空间较为稀疏，用邻接表存储，指针判断下一个，效率高，通过BFS搜索累计访问6以内层序的节点。
*/

#include <stdio.h>
#include <stdlib.h>

//MGraph定义的程序头
#define MaxVertexNum 100 //最大顶点数
typedef int Vertex;      //用顶点下标表示顶点

//LGraph边的定义
typedef struct ENode *PtrToNode;
struct ENode
{
    Vertex V1, V2; //有向边<V1,V2>
};
typedef PtrToNode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        /* 邻接点下标 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
} AdjList[MaxVertexNum];     /* AdjList是邻接表类型 */

// LGraph 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;    /* 顶点数 */
    int Ne;    /* 边数   */
    AdjList G; /* 邻接表 */
};
typedef PtrToGNode LGraph; //以邻接表方式存储的图类型

LGraph CreateGraph(int VertexNum);
LGraph BuildGraph();
void InsertEdge(LGraph Graph, Edge E);
void SDS(LGraph Graph);
int BFS(LGraph G, Vertex V);
void InitVisit();
int Visited[MaxVertexNum];

int main()
{
    LGraph G = BuildGraph();
    SDS(G);
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    int Nv = 10, i;
    Graph = CreateGraph(Nv);
    Graph->Ne = 9;
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        int arr[9][2] = {{1, 2},
                         {2, 3},
                         {3, 4},
                         {4, 5},
                         {5, 6},
                         {6, 7},
                         {7, 8},
                         {8, 9},
                         {9, 10}};
        for (i = 0; i < Graph->Ne; i++)
        {
            E->V1 = arr[i][0];
            E->V2 = arr[i][1];
            E->V1--;
            E->V2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

LGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */

    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

void SDS(LGraph Graph)
{
    double ratio;
    int count;
    for (int V = 0; V < Graph->Nv; V++)
    {
        InitVisit();
        count = BFS(Graph, V);
        ratio = count * 1.0 / Graph->Nv * 100;
        printf("%d: %.2lf%%\n", V + 1, ratio);
    }
}

int BFS(LGraph G, Vertex V)
{
    const int MAX_SIZE = 100;
    int Queue[MAX_SIZE];
    int first = -1, rear = -1;

    PtrToAdjVNode p;
    int count, level, last, tail;
    Visited[V] = 1;
    count = 1;
    level = 0;
    last = V;

    Queue[++rear] = V;   //入队
    while (first < rear) //当队不为空时
    {
        int F = Queue[++first]; //出队
        for (p = G->G[F].FirstEdge; p; p = p->Next)
        {
            if (!Visited[p->AdjV])
            {
                Visited[F] = 1;
                Queue[++rear] = p->AdjV; //入队
                count++;
                tail = p->AdjV;
            }
        }
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