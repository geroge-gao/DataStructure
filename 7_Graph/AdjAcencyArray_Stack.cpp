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
	GraphKind    kind;                     //ͼ�������־	

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
	if(G.kind==UDN||G.kind==UDG)//���������ͼ������������ɾ���Գ�ż��
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
 


//---------�ǵݹ�������������--------
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
typedef VertexType SElemType;

typedef struct SqStack{

	SElemType *base;//ջ��ָ��
	SElemType *top;//ջ��ָ��
	int size;
}SqStack;

void InitStack( SqStack &s)
{
	s.base=(SElemType*)malloc(STACK_INIT_SIZZE*sizeof(SElemType));
	if(s.base==NULL)printf("�ڴ�����ʧ��!");

	s.top=s.base;
	s.size=STACK_INIT_SIZZE;//��ǰջ�ĳ�
}

int StackEmpty(SqStack s)
{
	if(s.base==s.top)//��ջ������ջ�׵�ʱ��˵��ջΪ��
		return OK;
	return 0;
}

int Push(SqStack &s, SElemType e)
{
	if(s.top-s.base>STACK_INIT_SIZZE)
	{
		s.base=(SElemType*)realloc(s.base,(s.size+STACKINCREMENT)*sizeof(SElemType));//����ڴ��������·����ڴ�ռ�
		if(!s.base)exit(ERROR);//�ڴ����ʧ��

		s.top=s.base+STACK_INIT_SIZZE;//�Ѿ��������һ��
		s.size+=STACKINCREMENT;//����������

	}
	*(s.top++)=e;
	return OK;	
}

//���ջ��Ϊ�գ���ɾ��s��ջ��Ԫ�أ�����e����ֵ���ػ���
int Pop(SqStack &s,SElemType &e)
{
	
	if(s.base==s.top)return ERROR;
	e=*(--s.top);
	return OK;
	
}

int GetTop(SqStack s,SElemType &e)
{
	if(s.top==s.base)return ERROR;

	e=*(--s.top);
	return OK;
}

//�ؼ�����ջ��ʱ����ʽ��

Status DFSTraverse(MGraph &G,Status(*Visit)(int v))
{
	int i,j;
	SqStack s;
	VertexType v,w,t;
	InitStack(s);
	printf("������ȱ���Ϊ:");
	for(i=0;i<G.vexnum;i++)
		Visited[i]=FALSE;
	Push(s,G.vexs[0]);
	Visited[0]=TRUE;
	Visit(G.vexs[0]);
	while(!StackEmpty(s))
	{
		for(i=0;i<G.vexnum;i++){
			v=G.vexs[i];
			if(!Visited[i])
			{
				Visit(v);
				Visited[i]=TRUE;
			}
			w=FirstAdjVex(G,v);
			while(w>0)//������Ƚ��б���
			{
				if(!Visited[LocateVex(G,w)])
				{
					Visit(w);	
					Visited[LocateVex(G,w)]=TRUE;					
				} 
				j=LocateVex(G,FirstAdjVex(G,w));
				if(!Visited[j])//�����һ���ڽӵ��ѷ��ʣ��ͷ�����һ����һ�ڽӵ�
					w=FirstAdjVex(G,G.vexs[j]);
				else//������һ�����
				{
					t=FirstAdjVex(G,w);
					t =w=NextAdjVex(G,w,t);
					//�жϸ����Ƿ����е㶼�����ʣ��������������˳��ò�ѭ��
					if(Visited[LocateVex(G,w)]&&NextAdjVex(G,t,w)<=0)
						w=-1;
				}
			}
		}
		Pop(s,v);
	}	
	printf("\n");
	return OK;
}



int main()
{
	MGraph G;
	CreateUDN(G);
	PrintVex(G);
	DFSTraverse(G,Visit);
	return 0;
}