#include<stdio.h>
#include<stdlib.h>

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef enum{DG , DN, UDG, UDN} GraphKind;//{����ͼ��������������ͼ��������}
typedef int VRType;
typedef char InfoType;
typedef int VertexType;//��������
typedef int Status;

typedef struct ArcCell{

	VRType adj;          //��Ȩͼ��ʾ0��1����Ȩ��Ȩֵ
	InfoType *info;      //�û��������Ϣָ��
	//int visit;

}ArcCell,AdjMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct {//�ڽ�ͼ�ṹ

	VertexType   vexs[MAX_VERTEX_NUM];     //��������
	AdjMaxtrix   arcs;                     //�ڽӾ���
	int          vexnum;                   //��ǰ������
	int    		 arcnum;                   //������
//raphKind    kind;                     //ͼ�������־	

}MGraph;


Status LocateVex(MGraph G,VertexType v);


Status CreateUDN(MGraph &G)//������
{
	int IncInfo;
	int i,j,k;
	int v1,v2;
	int w;//Ȩ��
	printf("�����뵱ǰ�������ͻ�����,�Լ����������Ϣ:");

	scanf("%d%d",&G.vexnum,&G.arcnum);//���IncInfo����ʾ��û����Ϣ
	scanf("%d",&IncInfo);

	printf("���������붥��:\n");
	for(i=0;i<G.vexnum;i++)
		scanf("%d",&G.vexs[i]); //���춥����������

	for(i=0;i<G.vexnum;i++)//��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j].adj=0;
			G.arcs[i][j].info=NULL;
		}
	
	printf("�����������ڽӵ㼰��Ȩ��\n");
	for(k=0;k<G.arcnum;k++)//���ݻ��������붥��
	{
		scanf("%d%d%d",&v1,&v2,&w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G.arcs[i][j].adj=w;//��v1��v2����Ȩ��
		G.arcs[j][i].adj=w;
		if(IncInfo)
			scanf("%c",&(*(G.arcs[i][j].info)));
	}	
	return OK;
}//CreateUDN

Status LocateVex(MGraph G,VertexType v)//�õ���ǰ��������λ��
{
	for(int i=0;i<G.vexnum;i++)
		if(G.vexs[i]==v)
			return i;

	return ERROR;
}


Status GetVex(MGraph G,int v)//����v��ĳ������
{
	if(v>=G.arcnum||v<0)
		exit(ERROR);
	return G.vexs[v];
}

Status FirstAdjVex(MGraph &G, VertexType v)//����Ϊ�ĵ�һ���ڽӶ�������к�
{
	int i=LocateVex(G,v);
	for(int k=0;k<G.vexnum;k++)
		if(G.arcs[i][k].adj==1)
			return G.vexs[k];
	return ERROR;
}

Status NextAdjVex(MGraph G,VertexType v,VertexType w)//����w�ĵ���һ���ڽӶ���
{
	int i=LocateVex(G,v);
	int k=LocateVex(G,w);
	for(int j=k;j<G.vexnum;j++)
		if(G.arcs[i][j].adj==1&&j>k)
			return G.vexs[j];

	return ERROR;
}

Status InsertVex(MGraph &G,VertexType v)//��Gͼ��������
{
	int i;
	if(G.vexnum==MAX_VERTEX_NUM)//�������
		return ERROR;
	else
		G.vexs[G.vexnum]=v;
	G.vexnum++;//������+1

	for( i=0;i<G.vexnum;i++)//���������г�ʼ��
		G.arcs[G.vexnum-1][i].adj=0;

	for( i=0;i<G.vexnum;i++)//���������г�ʼ��
		G.arcs[i][G.vexnum-1].adj=0;

	return OK;
}

void  DeleteVex(MGraph &G,VertexType v)//ɾ�����v,�������ͼ��������
{
	int loc=LocateVex(G,v);
	int i,j;

	for(j=0;j<G.vexnum;j++)//ɾ����صĻ�
			if(G.arcs[loc][j].adj==1)
				G.arcnum--;

	for(i=0;i<G.vexnum;i++)//�����ڵ���ɾ��
		for(j=loc;j<G.vexnum-1;j++)
			G.arcs[i][j]=G.arcs[i][j+1];
		
		

	for(i=loc;i<G.vexnum-1;i++)
		for(j=0;j<G.vexnum-1;j++)
			G.arcs[i][j]=G.arcs[i+1][j];
		
	for(i=loc;i<G.vexnum-1;i++)
		G.vexs[i]=G.vexs[i+1];

	G.vexnum--;//�������һ
}


void InsertArc(MGraph &G,VertexType v,VertexType w)//��Gͼ�����<v,w>����
{
	int i,j;//��ȡw��v�ھ����е�λ��
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	G.arcs[i][j].adj=1;
	G.arcs[j][i].adj=1;//�Գƻ�
}
void DeleteArc(MGraph &G,VertexType v,VertexType w)
{
	//ɾ����<v,w>,��G�����������ɾ���Գƻ�<w,v>
	int i,j;
	G.vexnum-=2;
	G.arcnum-=1;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	G.arcs[i][j].adj=0; 
	G.arcs[j][i].adj=0;
	
}

void PrintVex(MGraph G)
{
	printf("�ڽӾ���Ϊ:\n");
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
			printf("%d ",G.arcs[i][j].adj);
		printf("\n");
	}
}

int Visited[MAX_VERTEX_NUM];//��־����

Status Visit(VertexType v)
{
	printf("%d ",v);
	return OK;
}



//-------------�����������н��������������-------------

typedef VertexType QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;


typedef struct Queue{

	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ��

}Queue;

int InitQueue(Queue &q)
{
	q.front=(QueuePtr)malloc(sizeof(QNode));
	q.rear=q.front;
	if(!q.front) return ERROR;//�����ڴ�ʧ��
	q.front->next=NULL;//һ��Ҫ����ʼֵ��Ϊ��
	return OK;
	
}

//���
int EnQueue(Queue &q,QElemType e)
{
	 QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	 if(!p)return ERROR;//����ʧ��
	 p->data=e;
	 p->next=NULL;
	 q.rear->next=p;
	 q.rear=p;
	 return OK;
	 
}

//������
int DeQueue(Queue &q,QElemType &e)
{
	QueuePtr p;
	if(q.front==q.rear)return ERROR;//��ʱ����Ϊ��.
	p=q.front->next;
	e=p->data;
	q.front->next=p->next; //�����β��ָ����       
	if(q.rear==p)//���ֻʣ��һλʱ
	q.rear=q.front;
	free(p);
	
	return OK;
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(Queue q)
{
	if(q.front==q.rear)
		return OK;
	return 0;
}

//�õ���ͷ
int GetHead(Queue &q,QElemType &e)
{
	if(q.front==q.rear)return ERROR;
	e=q.front->next->data;
	return OK;
	      
}

Status BFSTraverse(MGraph G,Status(*Visit)(int v))
{
	Queue q;
	QElemType e;
	int i,j;	

	for(i=0;i<G.vexnum;i++)
		Visited[i]=FALSE;

	if(!InitQueue(q))return ERROR;
	EnQueue(q,G.vexs[0]);//����һ���������
	Visited[0]=TRUE;

	printf("������ȱ���:");
	while(!QueueEmpty(q))
	{
		GetHead(q,e);
		i=LocateVex(G,e);
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[i][j].adj!=0)
				if(!Visited[j])				
				{
					Visited[j]=TRUE;
					EnQueue(q,G.vexs[j]);
				}
		DeQueue(q,e);
		Visit(e);
	}
	printf("\n");
	return OK;
}

int main()
{
	MGraph G;
	CreateUDN(G);
	PrintVex(G);
	BFSTraverse(G,Visit);
	return 0;
}	

