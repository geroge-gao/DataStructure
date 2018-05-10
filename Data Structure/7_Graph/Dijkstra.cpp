#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1


typedef int VRType;
typedef char InfoType;
typedef char VertexType[20];//向量类型
typedef int Status;

int Visited[MAX_VERTEX_NUM];//标志数组

typedef struct ArcCell{

	VRType adj;          //无权图表示0和1，有权是权值
//	InfoType info;      //该弧的相关信息指针
	//int visit;

}ArcCell,AdjMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct {//邻接图结构

	VertexType   vexs[MAX_VERTEX_NUM];     //顶点向量
	AdjMaxtrix   arcs;                     //邻接矩阵
	int          vexnum;                   //当前顶点数
	int    		 arcnum;                   //弧度数

}MGraph;

Status LocateVex(MGraph G,VertexType v);
Status CreateGraph(MGraph &G,int m,int n);
void PrintGrraph(MGraph G);
void ShortestPath_DIJ(MGraph G,int v0);
void ShortestPath_FLOYD(MGraph G,int m);

int main()
{
    int m,n;
    char c[20];
    MGraph G;
    printf("输入节点数和弧数:");
    scanf("%d%d",&m,&n);
    CreateGraph(G,m,n);
    scanf("%s",c);
    m=LocateVex(G,c);
    ShortestPath_DIJ(G,m);
    ShortestPath_FLOYD(G,m);
    return 0;
}

Status CreateGraph(MGraph &G,int m,int n)
{
    VertexType w,v;
    int p,q,info;
    G.vexnum=m;
    G.arcnum=n;
    printf("输入顶点:\n");
    for(int i=0;i<G.vexnum;i++)
        scanf("%s",&G.vexs[i]);

    for(int i=0;i<G.vexnum;i++)
        for(int j=0;j<G.vexnum;j++)
            G.arcs[i][j].adj=INT_MAX;
    printf("输入弧及其权重:\n");
    for(int i=0;i<G.arcnum;i++)
    {
        scanf("%s%s%d",&w,&v,&info);
        p=LocateVex(G,w);
        q=LocateVex(G,v);
        if(p<0||q<0)
            return ERROR;
        G.arcs[p][q].adj=info;
    }
    return OK;
}

int LocateVex(MGraph G,VertexType v)
{
    for(int i=0;i<G.vexnum;i++)
        if(strcmp(G.vexs[i],v)==0)
            return i;
    return ERROR;
}

void PrintGrraph(MGraph G)
{
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            printf("%12d",G.arcs[i][j].adj);
        printf("\n");
    }
}

void ShortestPath_DIJ(MGraph G,int v0)
{
    int Final[MAX_VERTEX_NUM],D[MAX_VERTEX_NUM];
    int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM],min,t;
    for(int i=0;i<G.vexnum;i++)
    {
        Final[i]=FALSE;
        D[i]=G.arcs[v0][i].adj;
        for(int j=0;j<G.vexnum;j++)
            P[i][j]=FALSE;
        if(D[i]<INT_MAX)//设置空路径
        {
            P[i][v0]=TRUE;
            P[i][i]=TRUE;//表示将第二个点也纳入了最短路径的集合
        }
    }

    D[v0]=0;
    Final[v0]=TRUE;
    for(int i=1;i<G.vexnum;i++)
    {
        min=INT_MAX;
        for(int j=0;j<G.vexnum;j++)
            if(!Final[j]&&D[j]<min)//找出当前最短路径
            {
                t=j;
                min=D[j];
            }

        Final[t]=TRUE;//将当前点加入最短路径点集
        for(int j=0;j<G.vexnum;j++)
            if(!Final[j]&&min+G.arcs[t][j].adj<D[j]&&G.arcs[t][j].adj<INT_MAX)
            {
                D[j]=min+G.arcs[t][j].adj;
                P[j][j]=P[t][j];
                for(int m=0;m<G.vexnum;m++)
                    P[j][m]=P[t][m];
                P[j][j]=TRUE;
                P[j][t]=TRUE;
            }
    }

    for(int i=0;i<G.vexnum;i++)
    {
        if(Final[i]&&i!=v0)
        {
            printf("%s->%s的最短路径为:%d\n",G.vexs[v0],G.vexs[i],D[i]);
            for(int j=0;j<G.vexnum;j++)
            {
                if(P[i][j])
                    printf("%s ",G.vexs[j]);
            }
            printf("\n");
        }
    }

}

void ShortestPath_FLOYD(MGraph G,int m)
{
    int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    for(int v=0;v<G.vexnum;v++)
    {
        for(int w=0;w<G.vexnum;w++)
        {
            D[v][w] = G.arcs[v][w].adj;
            for(int u = 0; u < G.vexnum; u++)
            {
                P[v][w][u] = FALSE;
            }
            if(D[v][w] < INT_MAX)
            {
                P[v][w][v] = TRUE;
                P[v][w][w] = TRUE;
            }

        }
    }

    for(int v=0;v<G.vexnum;v++)
        for(int w=0;w<G.vexnum;w++)
            for(int u=0;u<G.vexnum;u++)
            {
                if(D[v][u]<INT_MAX&&D[u][w]<INT_MAX&&D[v][u]+D[u][w]<D[v][w])
                {
                    D[v][w]=D[v][u]+D[u][w];
                    for(int i=0;i<G.vexnum;i++)
                        P[v][w][i]=P[v][u][i]||P[u][w][i];
                }
            }
    for(int i=0;i<G.vexnum;i++)
        if(D[m][i]<INT_MAX)
        {
            printf("%s->%s的最短路径为:%d\n",G.vexs[m],G.vexs[i],D[m][i]);
            for(int j=0;j<G.vexnum;j++)
            {
                if(P[m][i][j])
                    printf("%s ",G.vexs[j]);
            }
            printf("\n");
        }


}
