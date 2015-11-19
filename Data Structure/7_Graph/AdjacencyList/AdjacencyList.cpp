#include<iostream>
using namespace std;

#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1

typedef int InfoType;
typedef int VertexType;
typedef int Status;
typedef enum{DG , DN, UDG, UDN} GraphKind;//{����ͼ��������������ͼ��������}

typedef struct ArcNode{//���ṹ

	int         adjvex;     //���������ж����ֵ
	struct ArcNode *nextarc;//ָ����һ������
	InfoType    info;      //�洢�û����й���Ϣ����Ȩ��֮��

}ArcNode;

typedef struct VNode{//��������

	VertexType data;//������Ϣ
	ArcNode *firstarc;//ָ���һ�������ö��㻡��ָ��

}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{//ͼ�ṹ

	AdjList vertices;
	int   vexnum;//������
	int   arcnum;//����
	GraphKind   kind;//ͼ������
}ALGraph;

Status LocateVex(ALGraph G,VertexType v);


Status CreateUDN(ALGraph &G)//����������
{
	int IncInfo;
	int i,j,k;
	VertexType v,w;
	ArcNode *p,*t;
	InfoType info;//Ȩֵ

	printf("�����붥�����������ͻ��������Ϣ:");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("������Ԫ��:\n");
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%d",&G.vertices[i].data);//������������
		G.vertices[i].firstarc=NULL;
	}

	printf("�����������ڽӵ�:\n");
	t=G.vertices[i].firstarc;
	for(i=0;i<G.arcnum;i++)//��������
	{
		//ע��i������֮��ı���ͬ��
		scanf("%d%d%d",&v,&w,&info);
		k=LocateVex(G,v);
		j=LocateVex(G,w);
		p=(ArcNode *)malloc(sizeof(ArcNode));
		if(!p)return ERROR;
		p->adjvex=w;//������ֵ
		p->nextarc=G.vertices[k].firstarc;
		G.vertices[k].firstarc=p;
		if(IncInfo)p->info=info;
		p=(ArcNode*)malloc(sizeof(ArcNode));//�����Գƻ�
		p->adjvex=v;
		p->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p;
	} 
	//�����Գƻ�

	return OK;
}

//Status CreateGraph(ALGraph &G)//����ͼ������
//{
//	printf("��ѡ�񴴽�ͼ������:\n");
//	printf("0��������ͼ\n1����������\n");
//	printf("2��������ͼ\n3����������\n");
	
//	printf("������:");
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

Status GetVex(ALGraph G,int v)//����v��ĳ������
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
		if(p->adjvex==w&&p&&p->nextarc)//��w�ĺ�һ���ڽӱ����
			return p->nextarc->adjvex;	
	}
	if(!p)//wû����һ���ڽӵ����vû���ڽ��
		return ERROR;
	return ERROR;
}

Status InsertVex(ALGraph &G,VertexType v)//����v
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
	while(p)//ɾ���ö������ڵ�����
	{		
		j=LocateVex(G,p->adjvex);
		current=p;//������һ���ڵ�
		p=p->nextarc;
		G.vertices[i].firstarc=p;
		free(current);
		temp=G.vertices[j].firstarc;

		while(temp)//�ҳ�����
		{
			//ע��ֻ��ɾ��һ���ڵ�
			if(temp->adjvex==v)//���ھͽ���ɾ��
			{
				if(temp==G.vertices[j].firstarc)//����ڱ�ͷ
				{
					G.vertices[j].firstarc=temp->nextarc;
					free(temp);
					temp=NULL;
				}
				else if(temp->nextarc)//����ڱ���
				{
					t->nextarc=temp->nextarc;
					free(temp);
					temp=NULL;
				}
				else //����ڱ�β
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

	//Ȼ��ɾ�����鵱�е���
	for(int k=i;k<G.vexnum-1;k++)
		G.vertices[k]=G.vertices[k+1];
	G.vexnum--;
	return OK;
}

Status InsertArc(ALGraph &G,VertexType v,VertexType w)//˫�����
{
	int i,j;
	ArcNode *p,*q,*r,*current;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	if(i==ERROR||j==ERROR)return ERROR;//û���ҵ�
	else
	{
		p=G.vertices[i].firstarc;
		r=G.vertices[j].firstarc;
		while(p)//����һ����
		{
			current=p;
			p=p->nextarc;
		}		
		q=(ArcNode*)malloc(sizeof(ArcNode));
		if(!q)return ERROR;
		q->adjvex=w;
		if(!G.vertices[i].firstarc)//���û���ڽӵ�
		{
			q->nextarc=NULL;
			G.vertices[i].firstarc=q;
		}
		else
		{
			q->nextarc=p;
			current->nextarc=q;
		}

		current=r;//��������
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
	while(p&&p->adjvex!=w)//�ҵ�w���
	{
		current=p;
		p=p->nextarc;
	}
	if(!p)return ERROR;//�Ҳ���w����Ĺ�ϵΪ��
	if(p==G.vertices[i].firstarc)
		G.vertices[i].firstarc=p->nextarc;	
	else
		current->nextarc=p->nextarc;
	free(p);//�ͷŵ�w���ڴ�	

	current=q;//ɾ������
	while(q&&q->adjvex!=v)//�ҵ�v���
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
	printf("�ڽӱ�Ϊ:\n");
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
	printf("---------һ������Ϊ��-------=---\n");
	CreateUDN(G);
	PrintVex(G);
//	printf("�ڶ����ڵ���ڽӵ�Ϊ%d\n",FirstAdjVex(G,2));
//	printf("���v2Ϊͷ����������v4���ڽӵ�%d\n",NextAdjVex(G,2,4));
	scanf("%d",&v);
	if(DeleteVex(G,v))
		PrintVex(G);

	printf("����һ���»�:");
	scanf("%d%d",&v,&w);
	if(InsertArc(G,v,w)==OK)
		PrintVex(G);
	scanf("%d%d",&v,&w);
	DeleteArc(G,v,w);
	PrintVex(G);
	return 0;
}