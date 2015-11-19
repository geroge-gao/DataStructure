#include<iostream>
using namespace std;

#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef int InfoType;
typedef int VertexType;
typedef int Status;
typedef enum{DG , DN, UDG, UDN} GraphKind;//{有向图，有向网，无向图，无向网}

typedef struct ArcNode{//弧结构

	int         adjvex;     //保存链表中顶点的值
	struct ArcNode *nextarc;//指向下一个顶点
	InfoType    info;      //存储该弧的有关信息，如权重之类

}ArcNode,*ArcTNode;

typedef struct VNode{//顶点向量

	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点弧的指针
    ArcNode *current;//保存当前节点

}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{//图结构

	AdjList vertices;
	int   vexnum;//顶点数
	int   arcnum;//弧数
	GraphKind   kind;//图的种类
}ALGraph;

Status LocateVex(ALGraph G,VertexType v);


Status CreateUDN(ALGraph &G)//创建无向网
{
	int IncInfo;
	int i,j,k;
	VertexType v,w;
	ArcNode *p;
	InfoType info;//权值

	printf("请输入顶点数、弧数和弧的相关信息:");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("请输入元素:\n");
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%d",&G.vertices[i].data);//创建定点数组
		G.vertices[i].firstarc=NULL;
		G.vertices[i].current=G.vertices[i].firstarc;
		
	}

		printf("请输入两个邻接点:\n");		

	for(i=0;i<G.arcnum;i++)//创建链表
	{
		//注意i不能与之间的变量同名
		scanf("%d%d%d",&v,&w,&info);
		k=LocateVex(G,v);
		j=LocateVex(G,w);
		if(!G.vertices[k].firstarc)//如果链表头为空，创建第一个节点
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			if(!p)return ERROR;
			p->adjvex=w;
			if(IncInfo)p->info=info;
			p->nextarc=G.vertices[k].firstarc;
			G.vertices[k].current=G.vertices[k].firstarc=p;
		}
		else
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			if(!p)return ERROR;
			p->adjvex=w;
			if(IncInfo)p->info=info;
			p->nextarc=G.vertices[k].current->nextarc;
			G.vertices[k].current->nextarc=p;
			G.vertices[k].current=p;		
		}

		if(!G.vertices[j].firstarc)//创建反射弧的第一个借点
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			if(!p)return ERROR;
			p->adjvex=v;
			if(IncInfo)p->info=info;
			p->nextarc=G.vertices[j].firstarc;
			G.vertices[j].current=G.vertices[j].firstarc=p;
		}
		else
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			if(!p)return ERROR;
			p->adjvex=v;
			if(IncInfo)p->info=info;
			p->nextarc=G.vertices[k].current->nextarc;
			G.vertices[j].current->nextarc=p;
			G.vertices[j].current=p;	
		}
	} 
	//创建对称弧

	return OK;
}

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
	if(!p)//w没有下一个邻接点或者v没有邻结点
		return ERROR;
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
	int i,j;
	ArcNode *p,*current,*temp,*t;
	i=LocateVex(G,v);
	p=G.vertices[i].firstarc;
	while(p)//删除该顶点所在的链表
	{		
		j=LocateVex(G,p->adjvex);
		current=p;//保存上一个节点
		p=p->nextarc;
		G.vertices[i].firstarc=p;
		free(current);
		temp=G.vertices[j].firstarc;

		while(temp)//找出反向弧
		{
			//注意只是删除一个节点
			if(temp->adjvex==v)//存在就将其删除
			{
				if(temp==G.vertices[j].firstarc)//结点在表头
				{
					G.vertices[j].firstarc=temp->nextarc;
					free(temp);
					temp=NULL;
				}
				else if(temp->nextarc)//结点在表中
				{
					t->nextarc=temp->nextarc;
					free(temp);
					temp=NULL;
				}
				else //结点在表尾
				{
					t->nextarc=NULL;
					free(temp);
					temp=NULL;
				}	
				
			}
			if(temp)
			{
				t=temp;
				temp=temp->nextarc;
			}
		}

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
		while(p)//加上一条弧
		{
			current=p;
			p=p->nextarc;
		}		
		q=(ArcNode*)malloc(sizeof(ArcNode));
		if(!q)return ERROR;
		q->adjvex=w;
		if(!G.vertices[i].firstarc)//如果没有邻接点
		{
			q->nextarc=NULL;
			G.vertices[i].firstarc=q;
		}
		else
		{
			q->nextarc=p;
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
		if(!G.vertices[j].firstarc)
		{
			q->nextarc=NULL;
			G.vertices[j].firstarc=q;
		}
		else
		{
			current->nextarc=q;
			q->nextarc=r;;
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


//--------广度优先搜索--------

int Visited[MAX_VERTEX_NUM];//标志数组

Status Visit(VertexType v)
{
	printf("%d ",v);
	return OK;
}

//-------------创建辅助队列进行深度优先搜索-------------

typedef VertexType QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;


typedef struct Queue{

	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针

}Queue;

int InitQueue(Queue &q)
{
	q.front=(QueuePtr)malloc(sizeof(QNode));
	q.rear=q.front;
	if(!q.front) return 0;//申请内存失败
	q.front->next=NULL;//一定要将初始值设为空
	return OK;
	
}

//入队
int EnQueue(Queue &q,QElemType e)
{
	 QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	 if(!p)return ERROR;//申请失败
	 p->data=e;
	 p->next=NULL;
	 q.rear->next=p;
	 q.rear=p;
	 return OK;
	 
}

//出队列
int DeQueue(Queue &q,QElemType &e)
{
	QueuePtr p;
	if(q.front==q.rear)return ERROR;//此时队列为空.
	p=q.front->next;
	e=p->data;
	q.front->next=p->next; //保存队尾的指针域       
	if(q.rear==p)//如果只剩下一位时
	q.rear=q.front;
	free(p);
	
	return OK;
}

//判断队列是否为空
int QueueEmpty(Queue q)
{
	if(q.front==q.rear)
		return OK;
	return 0;
}

//得到对头
int GetHead(Queue &q,QElemType &e)
{
	if(q.front==q.rear)return ERROR;
	e=q.front->next->data;
	return OK;
	      
}

Status BFSTraverse(ALGraph G,Status(*Visit)(int v),VertexType v)
{
	Queue q;
	QElemType e;
	ArcNode *p;
	int i,j;	

	for(i=0;i<G.vexnum;i++)
		Visited[i]=FALSE;

	if(!InitQueue(q))return ERROR;
	j=LocateVex(G,v);
	EnQueue(q,G.vertices[j].data);//将第一个顶点入队
	Visited[j]=TRUE;

	printf("广度优先遍历:");
	while(!QueueEmpty(q))
	{
		GetHead(q,e);
		i=LocateVex(G,e);
		p=G.vertices[i].firstarc;
		while(p)
		{
			i=LocateVex(G,p->adjvex);
			if(!Visited[i])
			{
				EnQueue(q,p->adjvex);
				Visited[i]=TRUE;
			}
			p=p->nextarc;
		}
		DeQueue(q,e);
		Visit(e);
	}
	
	printf("\n");
	return OK;
}

int main()
{
	ALGraph G;
	VertexType v;
	CreateUDN(G);
	PrintVex(G);
	printf("请输入想作为首节点遍历的点:");
	scanf("%d",&v);
	BFSTraverse(G,Visit,v);
	return 0;
}