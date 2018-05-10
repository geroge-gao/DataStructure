#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
#define SElemType char 

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

	s.top=s.base;//设置栈表为空
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
	int i=0;
	while(s.base!=s.top)
	{
		i++;
		s.top--;
	}

	return i;
}


//判断输入的数据是否匹配
int Match(char s[],SqStack &l)
{
	printf("%s\n",s);
	int i,j=0;
	int length=strlen(s);
	char *a=new char[];
	for(i=0;i<length;i++)
	{
		if(StackEmpty(l))
		{
			if(s[i]==')'||s[i]==']')
				return ERROR;
			else if(s[i]=='('||s[i]=='[')
				Push(l,s[i]);
		}
		else if(!StackEmpty(l))
		{
			if(s[i]==')')
				if(*(l.top-1)=='(')
					Pop(l,a[j++]);//将该括号弹出栈
			if(s[i]==']')
				if(*(l.top-1)=='[')
					Pop(l,a[j++]);
			if(s[i]=='('||s[i]=='[')
				Push(l,s[i]);
		}
	}
	if(StackEmpty(l))
		return OK;
	return ERROR;
	
}

int main()
{
	SqStack l;
	char s[100];
	scanf("%s",&s);
	InitStack(l);
	if(Match(s,l))
		printf("括号是匹配的!\n");
	else
		printf("括号不匹配!\n");
	if(l.top==l.base)
		printf("栈已经被清空!\n");
	return 0;
}
