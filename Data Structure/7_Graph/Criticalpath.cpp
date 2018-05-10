#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
using namespace std;

#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20

typedef char VerTexType[20];
typedef int Status;
typedef int InfoType;
typedef int SElemType;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
    InfoType info;
}ArcNode;

typedef struct VNode{
    VerTexType data;
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;



//顺序存储结构的栈
typedef struct SqStack{

	SElemType *base;//栈底指针
	SElemType *top;//栈顶指针
	int size;
}SqStack;

int count;
int indegree[MAX_VERTEX_NUM];
int Visited[MAX_VERTEX_NUM];
int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];

int InitSqStack(SqStack &S);
int StackEmpty(SqStack S);
int Push(SqStack &S,SElemType e);
int Pop(SqStack &S,SElemType &e);


Status LocateVex(ALGraph G,VerTexType v);
Status CreateALGraph(ALGraph &G,int m,int n);
void Print(ALGraph G);
void FindInDegree(ALGraph G);
Status TopologicalOrder(ALGraph G, SqStack &T);
Status CriticalPath(ALGraph G);


int main()
{
    ALGraph G;
    int m,n;
    printf("输入顶点数和弧数:");
    scanf("%d%d",&m,&n);
    CreateALGraph(G,m,n);
    CriticalPath(G);
    return 0;
}

int InitSqStack(SqStack &S)
{
    S.base=(SElemType*)malloc(20*sizeof(SElemType));
    if(!S.base)return ERROR;
    S.top=S.base;
    S.size=20;
    return OK;
}

int StackEmpty(SqStack S)
{
    if(S.base==S.top)
        return 1;
    return 0;
}

int Push(SqStack &S,SElemType e)
{
    if(S.top-S.base>=S.size)
    {
        S.base=(SElemType*)realloc(S.base,(S.size+5)*sizeof(SElemType));
        S.top=S.base+S.size;
        S.size+=5;
    }
    *S.top++=e;
    return OK;
}

int Pop(SqStack &S,SElemType &e)
{
    if(StackEmpty(S))
        return ERROR;
    e=*(--S.top);
    return OK;
}

Status CreateALGraph(ALGraph &G,int a,int b)
{
    VerTexType w,v;
    int m,n,i;
    int length,info;
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
        scanf("%s%s%d",&v,&w,&info);
        m=LocateVex(G,v);
        n=LocateVex(G,w);
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=n;
        p->info=info;
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

void FindInDegree(ALGraph G)
{
    ArcNode *p;
    int w;
    for(int i=0;i<G.vexnum;i++)
    {
        for(p=G.vertices[i].firstarc;p;p=p->nextarc)
        {
            w=p->adjvex;
            indegree[w]++;
        }
    }
}

Status TopologicalOrder(ALGraph G,SqStack &T)
{
    SqStack S;
    int j,k,count=0;
    ArcNode *p;
    InitSqStack(S);
    FindInDegree(G);
    for(int i=0;i<G.vexnum;i++)
        if(!indegree[i])
        {
            Push(S,i);
        }
    while(!StackEmpty(S))
    {
        Pop(S,j);
        Push(T,j);
        ++count;
        for(p=G.vertices[j].firstarc;p;p=p->nextarc)
        {
            k=p->adjvex;
            --indegree[k];
            if(indegree[k]==0)
                Push(S,k);
            if(ve[j]+p->info>ve[k])
                ve[k]=ve[j]+p->info;
        }

    }
    if(count<G.vexnum)
        return ERROR;
    return OK;
}

Status CriticalPath(ALGraph G)
{
    SqStack T;
    int j,w,temp;
    ArcNode *p;
    InitSqStack(T);
    for(int i=0;i<G.vexnum;i++)
    {
        ve[i]=0;
        vl[i]=0;
    }
    if(!TopologicalOrder(G,T))
        return ERROR;
    for(int i=0;i<G.vexnum;i++)
        vl[i]=ve[i];
    while(!StackEmpty(T))//逆向拓扑排序求各个节点
    {
        Pop(T,j);
        for(p=G.vertices[j].firstarc;p;p=p->nextarc)
        {
            w=p->adjvex;
            if(vl[w]-p->info>vl[j])
                vl[j]=vl[w]-p->info;
        }
    }

    vl[0]=0;
    printf("关键路径:");
    for(int i=0;i<G.vexnum;i++)
    {
        if(ve[i]==vl[i])
            printf("%s ",G.vertices[i].data);
    }


    return OK;
}


