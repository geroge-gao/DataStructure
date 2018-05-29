#include<iostream>
using namespace std;

#define Status int 
#define OK 1
#define ERROR 0
#define STACK_SIZE 100
#define INCREMENT_SIZE 10

int MAZE[10][10]=
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,1,1,1,0,1,0},
	{0,1,1,0,1,1,1,0,1,0},
	{0,1,1,1,1,0,0,1,1,0},
	{0,1,0,0,0,1,1,1,1,0},
	{0,1,1,1,0,1,1,1,1,0},
	{0,1,0,1,1,1,0,1,1,0},
	{0,1,0,0,1,1,1,0,1,0},
	{0,0,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0}
};

typedef struct{
	int x;
	int y;
}PosType;

typedef struct{

	int ord;//通道块路径上面的序号
	PosType seat;//通道块在迷宫当中的坐标
	int di;//从此通道块向下一通道块所走的方向;
}SElemType;

typedef struct{

	SElemType *top;//栈顶元素
	SElemType *base;//栈底元素
	int size;	
}SqStack;

Status InitStack(SqStack &S);
void Push(SqStack &S,SElemType e);
void Pop(SqStack &S,SElemType &e);
Status StackEmpty(SqStack S);

//地图探索的操作
int Pass(PosType pos);
void FootPrint(PosType pos);
void MarkPrint(PosType pos);
PosType NextPos(PosType curpos,int di);
Status MazePath(PosType start,PosType end);
int Equals(PosType p1,PosType p2);


int main()
{
	int i,j;
	PosType start,end;
	start.x=start.y=1;
	end.x=end.y=8;

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			printf("%d ",MAZE[i][j]);
		printf("\n");
	}

	if(MazePath(start,end))
		printf("该迷宫存在解\n");
	else
		printf("该迷宫不存在解\n");

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			printf("%d ",MAZE[i][j]);
		printf("\n");
	}
	return 0;
}


Status InitStack(SqStack &S)
{
	S.base=(SElemType*)malloc(STACK_SIZE*sizeof(SElemType));
	if(!S.base)return ERROR;
	S.top=S.base;
	S.size=STACK_SIZE;
	return OK;
}

void Push(SqStack &S,SElemType e)
{
	if(S.top-S.base>=STACK_SIZE)
	{
		S.base=(SElemType*)realloc(S.base,(S.size+INCREMENT_SIZE)*sizeof(SElemType));
		S.top=S.base+S.size;
		S.size+=INCREMENT_SIZE;
	}
	*S.top++=e;
}

void Pop(SqStack &S,SElemType &e)
{
	if(S.base==S.top)exit(0);
	e=*(--S.top);
}

Status StackEmpty(SqStack S)
{
	if(S.base==S.top)
		return OK;
	else
		return ERROR;
}


int Pass(PosType pos)
{
	if(MAZE[pos.y][pos.x]==1)
		return OK;
	return ERROR;
}

void FootPrint(PosType pos)//留下足迹
{
	MAZE[pos.y][pos.x]=2;
}

void MarkPrint(PosType pos)
{ 
//	printf("(%d,%d)\n走不通\n",pos.y,pos.x);
	MAZE[pos.y][pos.x]=0;
}

PosType NextPos(PosType Curpos,int di)
{
	switch(di)
	{
	case 1:Curpos.x++;	break;//向东探索		
	case 2:Curpos.y++;break;
	case 3:Curpos.y--;break;	
	case 4:Curpos.x--;break;
	}
	return Curpos;
}

int Equals(PosType p1,PosType p2)
{
	if(p1.x==p2.x&&p1.y==p2.y)
		return OK;
	else
		return ERROR;
}

Status MazePath(PosType start,PosType end)
{
	SqStack S;
	PosType curpos;
	SElemType e;
	int curstep=1;
	curpos=start;
	InitStack(S);
	do{
		if(Pass(curpos))//当前位置可通
		{
			FootPrint(curpos);
			e.ord=curstep;
			e.seat=curpos;
			e.di=1;
			Push(S,e);
			if(Equals(curpos,end))return OK;
			curpos=NextPos(curpos,1);
			curstep++;
		}else//如果当前位置不可通
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);
				while(e.di==4&&!StackEmpty(S))//留下不能通过的标记，并且退回一格
				{
					MarkPrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);//换下一个方向进行探索
					curpos=NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));
	return ERROR;;
}






