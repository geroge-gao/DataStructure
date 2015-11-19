#include<stdio.h>
#include<stdlib.h>

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef enum{DG , DN, UDG, UDN} GraphKind;//{有向图，有向网，无向图，无向网}
typedef int VRType;
typedef char InfoType;
typedef int VertexType;//向量类型
typedef int Status;

typedef struct ArcCell{

	VRType adj;          //无权图表示0和1，有权是权值
	InfoType *info;      //该弧的相关信息指针
	//int visit;

}ArcCell,AdjMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct {//邻接图结构

	VertexType   vexs[MAX_VERTEX_NUM];     //顶点向量
	AdjMaxtrix   arcs;                     //邻接矩阵
	int          vexnum;                   //当前顶点数
	int    		 arcnum;                   //弧度数
	GraphKind    kind;                     //图的种类标志	

}MGraph;


Status LocateVex(MGraph G,VertexType v);


Status CreateUDN(MGraph &G)//无向网
{
	int IncInfo;
	int i,j,k;
	int v1,v2;
	int w;//权重
	printf("请输入当前顶点数和弧度数,以及弧的相关信息:");

	scanf("%d%d",&G.vexnum,&G.arcnum);//如果IncInfo，表示弧没有信息
	scanf("%d",&IncInfo);

	printf("请依次输入顶点:\n");
	for(i=0;i<G.vexnum;i++)
		scanf("%d",&G.vexs[i]); //构造顶点向量矩阵

	for(i=0;i<G.vexnum;i++)//初始化邻接矩阵
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j].adj=0;
			G.arcs[i][j].info=NULL;
		}
	
	printf("请输入两个邻接点及其权重\n");
	for(k=0;k<G.arcnum;k++)//根据弧度数输入顶点
	{
		scanf("%d%d%d",&v1,&v2,&w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G.arcs[i][j].adj=w;//给v1和v2赋上权重
		G.arcs[j][i].adj=w;
		if(IncInfo)
			scanf("%c",&(*(G.arcs[i][j].info)));
	}	
	return OK;
}//CreateUDN

Status LocateVex(MGraph G,VertexType v)//得到当前顶点矩阵的位置
{
	for(int i=0;i<G.vexnum;i++)
		if(G.vexs[i]==v)
			return i;

	return ERROR;
}


Status GetVex(MGraph G,int v)//返回v的某个顶点
{
	if(v>=G.arcnum||v<0)
		exit(ERROR);
	return G.vexs[v];
}

Status FirstAdjVex(MGraph &G, VertexType v)//返回为的第一个邻接顶点的序列号
{
	int i=LocateVex(G,v);
	for(int k=0;k<G.vexnum;k++)
		if(G.arcs[i][k].adj==1)
			return G.vexs[k];
	return ERROR;
}

Status NextAdjVex(MGraph G,VertexType v,VertexType w)//返回w的的下一个邻接顶点
{
	int i=LocateVex(G,v);
	int k=LocateVex(G,w);
	for(int j=k;j<G.vexnum;j++)
		if(G.arcs[i][j].adj==1&&j>k)
			return G.vexs[j];
	return ERROR;
}

Status InsertVex(MGraph &G,VertexType v)//在G图中新添结点
{
	int i;
	if(G.vexnum==MAX_VERTEX_NUM)//矩阵存满
		return ERROR;
	else
		G.vexs[G.vexnum]=v;
	G.vexnum++;//顶点数+1

	for( i=0;i<G.vexnum;i++)//将新增的行初始化
		G.arcs[G.vexnum-1][i].adj=0;

	for( i=0;i<G.vexnum;i++)//将新增的列初始化
		G.arcs[i][G.vexnum-1].adj=0;

	return OK;
}


void  DeleteVex(MGraph &G,VertexType v)//删除结点v,针对无向图和无向网
{
	int loc=LocateVex(G,v);
	int i,j;

	for(j=0;j<G.vexnum;j++)//删掉相关的弧
			if(G.arcs[loc][j].adj==1)
				G.arcnum--;

	for(i=0;i<G.vexnum;i++)//将所在的列删除
		for(j=loc;j<G.vexnum-1;j++)
			G.arcs[i][j]=G.arcs[i][j+1];
		
		

	for(i=loc;i<G.vexnum-1;i++)
		for(j=0;j<G.vexnum-1;j++)
			G.arcs[i][j]=G.arcs[i+1][j];
		
	for(i=loc;i<G.vexnum-1;i++)
		G.vexs[i]=G.vexs[i+1];

	G.vexnum--;//结点数减一
}


void InsertArc(MGraph &G,VertexType v,VertexType w)//在G图中添加<v,w>序列
{
	int i,j;//获取w和v在矩阵当中的位置
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	G.arcs[i][j].adj=1;
	G.arcs[j][i].adj=1;//对称弧
}
void DeleteArc(MGraph &G,VertexType v,VertexType w)
{
	//删除弧<v,w>,若G是无向的则还需删除对称弧<w,v>
	int i,j;
	G.vexnum-=2;
	G.arcnum-=1;
	i=LocateVex(G,v);
	j=LocateVex(G,w);
	G.arcs[i][j].adj=0; 
	if(G.kind==UDN||G.kind==UDG)//如果是无向图或者无向网，删除对称偶序
		G.arcs[j][i].adj=0;
	
}

void PrintVex(MGraph G)
{
	printf("邻接矩阵为:\n");
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
			printf("%d ",G.arcs[i][j].adj);
		printf("\n");
	}
}

int Visited[MAX_VERTEX_NUM];//标志数组


Status Visit(VertexType v)
{
	printf("%d ",v);
	return OK;
}
 


//---------非递归的深度优先搜索--------
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
typedef VertexType SElemType;

typedef struct SqStack{

	SElemType *base;//栈底指针
	SElemType *top;//栈顶指针
	int size;
}SqStack;

void InitStack( SqStack &s)
{
	s.base=(SElemType*)malloc(STACK_INIT_SIZZE*sizeof(SElemType));
	if(s.base==NULL)printf("内存申请失败!");

	s.top=s.base;
	s.size=STACK_INIT_SIZZE;//当前栈的长
}

int StackEmpty(SqStack s)
{
	if(s.base==s.top)//当栈顶等于栈底的时候说明栈为空
		return OK;
	return 0;
}

int Push(SqStack &s, SElemType e)
{
	if(s.top-s.base>STACK_INIT_SIZZE)
	{
		s.base=(SElemType*)realloc(s.base,(s.size+STACKINCREMENT)*sizeof(SElemType));//如果内存满了重新分配内存空间
		if(!s.base)exit(ERROR);//内存分配失败

		s.top=s.base+STACK_INIT_SIZZE;//已经到了最后一个
		s.size+=STACKINCREMENT;//将容量扩大

	}
	*(s.top++)=e;
	return OK;	
}

//如果栈表不为空，则删除s的栈顶元素，并用e将其值返回回来
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

//关键，入栈的时候访问结点

Status DFSTraverse(MGraph &G,Status(*Visit)(int v))
{
	int i,j;
	SqStack s;
	VertexType v,w,t;
	InitStack(s);
	printf("深度优先遍历为:");
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
			while(w>0)//按照深度进行遍历
			{
				if(!Visited[LocateVex(G,w)])
				{
					Visit(w);	
					Visited[LocateVex(G,w)]=TRUE;					
				} 
				j=LocateVex(G,FirstAdjVex(G,w));
				if(!Visited[j])//如果第一个邻接点已访问，就访问下一个第一邻接点
					w=FirstAdjVex(G,G.vexs[j]);
				else//访问下一个结点
				{
					t=FirstAdjVex(G,w);
					t =w=NextAdjVex(G,w,t);
					//判断该行是否所有点都被访问，若果都被访问退出该层循环
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