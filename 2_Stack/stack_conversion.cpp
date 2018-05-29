#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
#define SElemType int

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
	if(s.top-s.base>STACK_INIT_SIZZE)
	{
		s.base=(SElemType*)realloc(s.base,(s.size+STACKINCREMENT)*sizeof(SElemType));//如果内存满了重新分配内存空间
		if(!s.base)exit(ERROR);//内存分配失败
		s.top=s.base+STACK_INIT_SIZZE;
		s.size+=STACKINCREMENT;//将容量扩大

	}
	*(s.top++)=e;

	return OK;	
}

//出栈
int Pop(SqStack &s,SElemType &e)
{
	//如果栈表不为空，则删除s的栈顶元素，并用e将其值返回回来
	if(s.base==s.top)return ERROR;
	e=*(--s.top);
	return OK;
	
}

//将十进制转换成任意进制输出
void conversion(SqStack &s)
{
	InitStack(s);
	int n,m;
	scanf("%d",&n);//输入要被转换的数

	printf("输入要转换的进制:");
	scanf("%d",&m);

	while(n)
	{
		Push(s,n%m);
		n/=m;
	}
}

void visit(SElemType e)
{
	printf("%d",e);
}

//将栈遍历输出
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

	SqStack s;
	conversion(s);
	StackTrqaverse(s);
	printf("\n");

	return 0;
}