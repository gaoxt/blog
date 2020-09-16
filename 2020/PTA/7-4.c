/*
    07-图4 哈利·波特的考试 (25分)
    解题思路：求多源最短路径，Floyd算法。
    1.建立一个无向网图
    2.用Floyd算法算出任意两点间的最短路径
    3.扫描每个顶点到最短路径的最大值
    4.比较所有最大值里面求出最小值即 最短路径。
*/

#include <stdio.h>
#include <stdlib.h>

//MGraph定义的程序头
#define MaxVertexNum 100 //最大顶点数
#define INFINITY 65535   //无穷大的最短路径，无符号整数
typedef int Vertex;      //用顶点下标表示顶点
typedef int WeighType;   //边的权值类型

//边的定义
typedef struct ENode *PtrToNode;
struct ENode
{
    Vertex V1, V2;    //有向边<V1,V2>
    WeighType Weight; //权重
};
typedef PtrToNode Edge;

//圆结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                  //顶点数
    int Ne;                                  //边数
    WeighType G[MaxVertexNum][MaxVertexNum]; //邻接矩阵
};
typedef PtrToGNode MGraph; //以邻接矩阵存储的图类型
void FindAnimal(MGraph Graph);
MGraph CreateGraph(int VertexNum);
MGraph BuildGraph();
void InsertEdge(MGraph Graph, Edge E);
void Floyd(MGraph Graph, WeighType D[][MaxVertexNum]);
int FindMaxDist(WeighType D[][MaxVertexNum], Vertex i, int N);

int main()
{
    MGraph G = BuildGraph();
    FindAnimal(G);
    return 0;
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

void InsertEdge(MGraph Graph, Edge E)
{
    //插入边<V1,V2>
    Graph->G[E->V1][E->V2] = E->Weight;
    //若是无向图，还要插入边<V2,V1>
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv = 6, i;
    Graph = CreateGraph(Nv);
    Graph->Ne = 11;
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        int arr[11][3] = {{3, 4, 70},
                          {1, 2, 1},
                          {5, 4, 50},
                          {2, 6, 50},
                          {5, 6, 60},
                          {1, 3, 70},
                          {4, 6, 60},
                          {3, 6, 80},
                          {5, 1, 100},
                          {2, 4, 60},
                          {5, 2, 80}};
        for (i = 0; i < Graph->Ne; i++)
        {
            E->V1 = arr[i][0];
            E->V2 = arr[i][1];
            E->Weight = arr[i][2];

            //动物编号从1开始的，矩阵里是从0开始，需要--;
            E->V1--;
            E->V2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

void Floyd(MGraph Graph, WeighType D[][MaxVertexNum])
{
    Vertex i, j, k;
    for (i = 0; i < Graph->Nv; i++)
    {
        for (j = 0; j < Graph->Nv; j++)
        {
            //初始化邻接矩阵
            D[i][j] = Graph->G[i][j];
            // path[i][j] = -1; //要求输出最短路径的话增加path记录
        }
    }
    //通过k这个上标，检查每对D[i][j]的值。
    for (k = 0; k < Graph->Nv; k++)
    {
        for (i = 0; i < Graph->Nv; i++)
        {

            for (j = 0; j < Graph->Nv; j++)
            {
                //如果D[i][k]+D[k][j]更小，也就是路径更短，则更新。
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    // if (i == j && D[i][j] < 0) // 若发现负值圈(从i到j一圈下来是个负数)，则无法计算正确结果。
                    //     return false;
                    // path[i][j] = k;  //递归的打印从i到k，k到j的路径,最短路径D[i][k]+k+D[k][j]
                }
            }
        }
    }
}

void FindAnimal(MGraph Graph)
{
    WeighType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    Vertex Animal, i;

    Floyd(Graph, D);

    //先定义一个无穷大的最短路径
    MinDist = INFINITY;
    for (i = 0; i < Graph->Nv; i++)
    {
        //找出第i个动物 到 其他动物 最长的距离
        MaxDist = FindMaxDist(D, i, Graph->Nv);
        //返回无穷大说明，从i开始 至少有个动物无法到达。
        if (MaxDist == INFINITY)
        {
            printf("0\n");
            return;
        }
        //如果找到最长距离 更小的动物，则更新为当前距离，记录动物编号。
        if (MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = i + 1;
        }
    }
    printf("%d %d\n", Animal, MinDist);
}

int FindMaxDist(WeighType D[][MaxVertexNum], Vertex i, int N)
{
    WeighType MaxDist;
    Vertex j;
    //初始化为一个最小值0
    MaxDist = 0;
    //找出动物i到其他动物j的最大距离。
    for (j = 0; j < N; j++)
    {
        //i!=j 跳过对角元
        if (i != j && D[i][j] > MaxDist)
            MaxDist = D[i][j];
    }
    return MaxDist;
}