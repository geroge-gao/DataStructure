#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1

typedef int InfoType;
typedef int VertexType;
typedef int Status;
typedef enum{DG , DN, UDG, UDN} GraphKind;//{有向图，有向网，无向图，无向网}

typedef struct ArcNode{//弧结构
	int         adjvex;     //保存链表中顶点的值
	struct ArcNode *nextarc;//指向下一个顶点
	InfoType    info;      //存储该弧的有关信息，如权重之类
}ArcNode;

typedef struct VNode{//顶点向量
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{//图结构

	AdjList vertices;
	int   vexnum;//顶点数
	int   arcnum;//弧数
//	GraphKind   kind;//图的种类
}ALGraph;

Status LocateVex(ALGraph G,VertexType v);


Status CreateUDN(ALGraph &G)//创建无向网
{
	int IncInfo;
	int i,j,k;
	VertexType v,w;
	ArcNode *p,*t;
	InfoType info;//权值

	printf("请输入顶点数、弧数和弧的相关信息:");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("请输入元素:\n");
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%d",&G.vertices[i].data);//创建定点数组
		G.vertices[i].firstarc=NULL;
	}

	printf("请输入两个邻接点:\n");
	t=G.vertices[i].firstarc;
	for(i=0;i<G.arcnum;i++)//创建链表
	{
		//注意i不能与之间的变量同名
		scanf("%d%d%d",&v,&w,&info);
		k=LocateVex(G,v);
		j=LocateVex(G,w);
		p=(ArcNode*)malloc(sizeof(ArcNode));
		if(!p)return ERROR;
		p->adjvex=w;//保存数值
		p->nextarc=G.vertices[k].firstarc;
		G.vertices[k].firstarc=p;
		if(IncInfo)p->info=info;
		p=(ArcNode*)malloc(sizeof(ArcNode));//创建对称弧
		p->adjvex=v;
		p->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p;
	}
	//创建对称弧
	return OK;
}

//Status CreateGraph(ALGraph &G)//创建图的种类
//{
//	printf("请选择创建图的类型:\n");
//	printf("0创建有向图\n1创建有向网\n");
//	printf("2创建无向图\n3创建无向网\n");

//	printf("请输入:");
//	scanf("%d",&G.kind);
//	switch(G.kind)
//	{
//	case DG: return  CreateDG(G);
//	case DN: return  CreateDN(G);
//	case UDG:return CreateUDG(G);
//	case UDN:return CreateUDN(G);
//	}
//	return OK;
//}

Status LocateVex(ALGraph G,VertexType v)
{
	for(int i=0;i<G.vexnum;i++)
		if(G.vertices[i].data==v)
			return i;
	return ERROR;
}

Status GetVex(ALGraph G,int v)//返回v的某个顶点
{
	if(v>=G.arcnum||v<0)
		exit(ERROR);
	return G.vertices[v].data;
}

Status FirstAdjVex(ALGraph &G,VertexType v)
{
	int i=LocateVex(G,v);
	if(i>=0&&i<G.vexnum)
		if(G.vertices[i].firstarc)
			return G.vertices[i].firstarc->adjvex;
	return ERROR;
}

Status NextAdjVex(ALGraph &G,VertexType v,VertexType w)
{
	int i;
	i=LocateVex(G,v);
	ArcNode *p=G.vertices[i].firstarc;
	while(p)
	{
		if(p->adjvex==w&&p&&p->nextarc)//将w的后一个邻接表输出
			return p->nextarc->adjvex;
        p=p->nextarc;
	}
//	if(!p)//w没有下一个邻接点或者v没有邻结点
//        return ERROR;
    return ERROR;
}

Status InsertVex(ALGraph &G,VertexType v)//插入v
{
	if(G.vexnum==MAX_VERTEX_NUM)return ERROR;
	G.vertices[G.vexnum].data=v;
	G.vertices[G.vexnum].firstarc=NULL;
	G.vexnum++;
	return OK;
}

Status DeleteVex(ALGraph &G,VertexType v)
{
	int i,j,m;
	ArcNode *p,*current,*temp,*t;
	i=LocateVex(G,v);
	p=G.vertices[i].firstarc;
	while(p)//删除该顶点所在的链表
	{
		current=p;//保存上一个节点
		m=current->adjvex;
		p=p->nextarc;
		G.vertices[i].firstarc=p;
		free(current);
		j=LocateVex(G,m);
		temp=G.vertices[j].firstarc;

		while(temp->adjvex!=v&&temp)
        {
            t=temp;
            temp=temp->nextarc;
        }
        //找到反射弧
        if(temp==G.vertices[j].firstarc)
        {
            G.vertices[j].firstarc=temp->nextarc;
            free(temp);
            temp=NULL;
        }
        else if(temp)//在中部或者尾部
        {
            t->nextarc=temp->nextarc;
            free(temp);
            temp=NULL;
        }
        else
            return ERROR;
	}

	//然后删掉数组当中的数
	for(int k=i;k<G.vexnum-1;k++)
		G.vertices[k]=G.vertices[k+1];
	G.vexnum--;
	return OK;
}

Status InsertArc(ALGraph &G,VertexType v,VertexType w)//双向插入
{
	int i,j;
	ArcNode *p,*q,*r,*current;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	if(i==ERROR||j==ERROR)return ERROR;//没有找到
	else
	{
		p=G.vertices[i].firstarc;
		r=G.vertices[j].firstarc;

		q=(ArcNode*)malloc(sizeof(ArcNode));
		if(!q)return ERROR;
		q->adjvex=w;
		while(p)
        {
            current=p;
            p=p->nextarc;
        }
        if(p==current)
        {
            q->nextarc=G.vertices[i].firstarc;
            G.vertices[i].firstarc=q;
        }
        else
        {
            q->nextarc=current->nextarc;
            current->nextarc=q;
        }

		current=r;//创建反向弧
		while(r)
		{
			current=r;
			r=r->nextarc;
		}
		q=(ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex=v;
		if(!q)return ERROR;
		if(current==r)
        {
            q->nextarc=G.vertices[j].firstarc;
            G.vertices[j].firstarc=q;
        }
        else
        {
            q->nextarc=current->nextarc;
            current->nextarc=q;
        }

	}
	return OK;
}

Status DeleteArc(ALGraph &G,VertexType v,VertexType w)
{
	int i,j;
	ArcNode *p,*q,*current;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	p=G.vertices[i].firstarc;
	q=G.vertices[j].firstarc;
	current=p;
	while(p&&p->adjvex!=w)//找到w结点
	{
		current=p;
		p=p->nextarc;
	}
	if(!p)return ERROR;//找不到w输入的关系为错
	if(p==G.vertices[i].firstarc)
		G.vertices[i].firstarc=p->nextarc;
	else
		current->nextarc=p->nextarc;
	free(p);//释放掉w的内存

	current=q;//删除反向弧
	while(q&&q->adjvex!=v)//找到v结点
	{
		current=q;
		q=q->nextarc;
	}
	if(!q)return ERROR;
	if(G.vertices[j].firstarc==q)
		G.vertices[j].firstarc=q->nextarc;
	else
		current->nextarc=q->nextarc;
	free(q);

	return OK;
}

void PrintVex(ALGraph &G)
{
	int i;
	ArcNode *p;
	printf("邻接表为:\n");
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		printf("%d ",G.vertices[i].data);
		while(p)
		{
			printf("%d ",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}

int main()
{
	ALGraph G;
	VertexType v,w;
	printf("---------一无向网为例-------=---\n");
	CreateUDN(G);
	PrintVex(G);
//	printf("第二个节点的邻接点为%d\n",FirstAdjVex(G,2));
//	printf("输出v2为头结点的链表中v4的邻接点%d\n",NextAdjVex(G,2,4));
	scanf("%d",&v);
	if(DeleteVex(G,v))
		PrintVex(G);

	printf("创建一个新弧:");
	scanf("%d%d",&v,&w);
	if(InsertArc(G,v,w)==OK)
		PrintVex(G);
	scanf("%d%d",&v,&w);
	DeleteArc(G,v,w);
	PrintVex(G);
	return 0;
}
