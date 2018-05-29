#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
#define SElemType int

//顺序存储结构的栈
typedef struct SqStack{

	SElemType *base;//栈底指针
	SElemType *top;//栈顶指针
	int size;
}SqStack;

//初始化一个栈
int InitStack( SqStack &s)
{
	s.base=(SElemType*)malloc(STACK_INIT_SIZZE*sizeof(SElemType));
	if(s.base==NULL)return ERROR;

	s.top=s.base;
	s.size=STACK_INIT_SIZZE;//当前栈的长度

	return OK;	
}

int StackEmpty(SqStack s)
{
	if(s.base==s.top)//当栈顶等于栈底的时候说明栈为空
		return OK;
	return ERROR;
}

//入栈
int Push(SqStack &s, SElemType e)
{
	if(s.top-s.base>=STACK_INIT_SIZZE)
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

void DestoryStack(SqStack &s)
{
	free(s.base);
}

int StackLength(SqStack s)
{
	return s.size;
}

int GetTop(SqStack s,SElemType &e)
{
	if(s.top==s.base)return ERROR;

	e=*(--s.top);
	return OK;
}

void visit(SElemType e)
{
	printf("%d ",e);
}

//从栈底到栈顶吗，将每一个元素都遍历到

int StackTrqaverse( SqStack s)
{
	if(s.base==s.top)return OK;

	while(s.base!=s.top)
	{
		visit(*(--s.top));
	}

	return ERROR;

}


int main()
{

	int n,m;
	SqStack s;
	printf("请输入将压入栈中的个数:");
	scanf("%d",&n);

	InitStack(s);//初始化栈
	for(int i=0;i<n;i++)
	{
		scanf("%d",&m);
		Push(s,m);
	}

	StackTrqaverse(s);
	printf("\n");

	return 0;

	
}