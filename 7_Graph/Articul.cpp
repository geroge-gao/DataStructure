#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20

typedef char VerTexType[20];
typedef int Status;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    VerTexType data;
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

int count;
int visited[MAX_VERTEX_NUM];
int low[MAX_VERTEX_NUM];
int Visited[MAX_VERTEX_NUM];

Status LocateVex(ALGraph G,VerTexType v);
Status CreateALGraph(ALGraph &G,int m,int n);
void Print(ALGraph G);
void FindArticual(ALGraph G);
void DFSTraverse(ALGraph G,int v0);
int main()
{
    int m,n;
    ALGraph G;
    printf("输入节点数和弧度数:");
    scanf("%d%d",&m,&n);
    CreateALGraph(G,m,n);
    Print(G);
    FindArticual(G);
    return 0;
}

void Strcpy(VerTexType &a,VerTexType b)
{
    int length=0;
    length=strlen(b);
    for(int i=0;i<length;i++)
        a[i]=b[i];
    a[length]='\0';
}

Status CreateALGraph(ALGraph &G,int a,int b)
{
    VerTexType w,v;
    int m,n,i;
    int length;
    VerTexType c;
    ArcNode *p,*current,*t;
    G.vexnum=a;
    G.arcnum=b;
    printf("输入节点:\n");
    for(i=0;i<G.vexnum;i++)
    {
        scanf("%s",&c);
        strcpy(G.vertices[i].data,c);
        G.vertices[i].firstarc=NULL;
    }

    printf("请输入两个邻接点:\n");
    for(i=0;i<G.arcnum;i++)
    {
        scanf("%s%s",&v,&w);
        m=LocateVex(G,v);
        n=LocateVex(G,w);
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=n;
        t=current=G.vertices[m].firstarc;
        while(t&&t->adjvex<=n)
        {
            current=t;
            t=t->nextarc;
        }
        if(current==t)
		{
			p->nextarc=G.vertices[m].firstarc;
			G.vertices[m].firstarc=p;
		}
        else{
            p->nextarc=t;
            current->nextarc=p;
        }

        //创建对立弧
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=m;
        t=current=G.vertices[n].firstarc;
        while(t&&t->adjvex<=m)
        {
            current=t;
            t=t->nextarc;
        }

        if(t==current)
		{
			p->nextarc=G.vertices[n].firstarc;
			G.vertices[n].firstarc=p;
		}
        else
        {
            p->nextarc=t;
            current->nextarc=p;
        }
    }

	return OK;
}

Status LocateVex(ALGraph G,VerTexType v)
{
    for(int i=0;i<G.vexnum;i++)
        if(strcmp(G.vertices[i].data,v)==0)
            return i;
    return ERROR;
}

void Print(ALGraph G)
{
    ArcNode *p;
    for(int i=0;i<G.vexnum;i++)
    {
        printf("%s---(",G.vertices[i].data);
        for(p=G.vertices[i].firstarc;p;p=p->nextarc)
        {
            printf("%s ",G.vertices[p->adjvex].data);
        }
        printf(")\n");
    }
}

void FindArticual(ALGraph G)
{
    ArcNode *p;
    int w;
    count=1;

    for(int i=0;i<G.vexnum;i++)
    {
         visited[i]=0;
         Visited[i]=0;
    }
    visited[0]=1;

    p=G.vertices[0].firstarc;
    DFSTraverse(G,p->adjvex);
    if(count<G.vexnum)
    {
        printf("%s ",G.vertices[0].data);
        while(p->nextarc)
        {
            p=p->nextarc;
            w=p->adjvex;
            if(visited[w]==0)
                DFSTraverse(G,w);
        }
    }

}

void DFSTraverse(ALGraph G,int v0)
{
    int min;
    int w;
    ArcNode *p;
    visited[v0]=min=++count;
    for(p=G.vertices[v0].firstarc;p;p=p->nextarc)
    {
        w=p->adjvex;
        if(visited[w]==0)//节点没有被访问
        {
            DFSTraverse(G,w);
            if(low[w]<min)min=low[w];
            if(low[w]>=visited[v0]&&!Visited[v0])
            {
                printf("%s ",G.vertices[v0].data);
                Visited[v0]++;
            }
        }
        else if(visited[w]<min)
            min=visited[w];
    }
    low[v0]=min;
}





