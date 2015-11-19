#include<iostream>
using namespace std;
#define OK 1
#define ERROR -1
#define MAX_VERTEX_NUM 110
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int VertextType;

//定义图的结构

typedef struct ArcNode //创建弧
{
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode //创建点
{
    VertextType data;
    ArcNode *firstarc;

} VNode,AdjList[MAX_VERTEX_NUM];

typedef struct //创建图
{
    AdjList vertices;
    int vexnum;
    int arcnum;
    int count;
} Graph;

//定义栈
typedef struct SqStack
{
    VertextType *base;
    VertextType *top;
    int stacksize;
} SqStack;

int LocateVex(Graph G,VertextType v);
int CreateGraph(Graph &G,int m,int n);
int search(Graph G,VertextType v);
void FindInDegree(Graph G);//获取结点的度
//栈的相关操作
int InitStack(SqStack &S);
int GetTop(SqStack S,VertextType v);
int Push(SqStack &S,VertextType &v);
int Pop(SqStack &S,VertextType &v);
int StackEmpty(SqStack S);

int indegree[110]= {0};

int TopologicalSort(Graph G)
{
    SqStack S;
    int count=0,i,temp;
    VertextType v;
    ArcNode *p;
    FindInDegree(G);
    InitStack(S);
    for(i=0; i<G.vexnum; i++) //将入度为零的进栈
        if(!indegree[i])
            Push(S,G.vertices[i].data);

    while(!StackEmpty(S))
    {
        Pop(S,v);
        count++;
        i=LocateVex(G,v);
        for(p=G.vertices[i].firstarc; p; p=p->nextarc)
        {
            if(p)
            {
                temp=LocateVex(G,p->adjvex);
                indegree[temp]--;
                if(!indegree[temp])
                    Push(S,p->adjvex);
            }
        }
    }

    if(count<G.vexnum)//存在环
        return 1;
    else
        return 0;
}


int main()
{
    int m,n;
    Graph G;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        CreateGraph(G,m,n);
        if(TopologicalSort(G))
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}

int CreateGraph(Graph &G,int m,int n)
{
    int i,k;
    int temp=0;
    VertextType w,v;
    ArcNode *p;
    G.vexnum=m;
    G.arcnum=n;
    for(i=0; i<G.vexnum; i++)
    {
        G.vertices[i].firstarc=NULL;
    }
    G.count=0;
    for(i=0; i<G.arcnum; i++)
    {
        scanf("%d%d",&w,&v);
        if(search(G,w)==-1)
        {
            G.vertices[temp++].data=w;
            G.count++;
        }
        if(search(G,v)==-1)
        {
            G.vertices[temp++].data=v;
            G.count++;
        }
        k=LocateVex(G,w);
        p=(ArcNode*)malloc(sizeof(ArcNode));
        if(!p)return ERROR;
        p->adjvex=v;
        p->nextarc=G.vertices[k].firstarc;
        G.vertices[k].firstarc=p;
    }
    return OK;
}

int LocateVex(Graph G,VertextType v)
{
    for(int i=0; i<G.vexnum; i++)
        if(G.vertices[i].data==v)
            return i;
    return -1;
}



void FindInDegree(Graph G)
{
    ArcNode *p;
    for(int i=0; i<G.vexnum; i++)
    {
        for(p=G.vertices[i].firstarc; p; p=p->nextarc)
            if(p)
            {
                int k=LocateVex(G,p->adjvex);
                indegree[k]++;
            }
    }
}

int search(Graph G,VertextType v)
{
    for(int i=0; i<G.count; i++)
        if(v==G.vertices[i].data)
            return i;
    return -1;
}

/*---------------华丽的分隔符------------- */

int InitStack(SqStack &S)
{
    S.base=(VertextType*)malloc(STACK_INIT_SIZE*sizeof(VertextType));
    if(!S.base)
    {
        return ERROR;
        exit(0);
    }
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}//InitStack

int Push(SqStack &S,VertextType &v)
{
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(VertextType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(VertextType));
        if(!S.base)return ERROR;
        S.top=S.base+S.stacksize;
        S.stacksize=S.stacksize+STACKINCREMENT;
    }
    *S.top++=v;
    return OK;
}

int Pop(SqStack &S,VertextType &v)
{
    if(S.base==S.top)return ERROR;
    v=*--S.top;
    return OK;
}

int StackEmpty(SqStack S)
{
    if(S.base==S.top)
        return 1;
    return 0;
}

