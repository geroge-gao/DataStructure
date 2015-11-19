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
//	if(s.base==s.top)//当栈顶等于栈底的时候说明栈为空
//		return OK;
//	return ERROR;
	return s.top==s.base;
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

void ClearStack(SqStack &l)
{
	l.top=l.base;
}


int LineEdit(char s[],SqStack &l)
{
	int length=strlen(s);
	int i,j=0;
	char *a=new char[];
	for(i=0;i<length;i++)
	{
		if(StackEmpty(l))
		{
			if(s[i]!='@'||s[i]!='#')
				Push(l,s[i]);
			else 
				return ERROR;
		}
		else if(!StackEmpty(l))
		{
			if(s[i]=='#')
				Pop(l,a[j++]);
			else if(s[i]=='@')
				while(!StackEmpty(l))
				{
					Pop(l,a[j++]);
				}
			else 
				Push(l,s[i]);
		}
	}
	return OK;
}

int main()
{
	SqStack l;
	InitStack(l);
	char a[100];
	scanf("%s",&a);
	LineEdit(a,l);

	while(!StackEmpty(l))
	{
		printf("%c",*l.base++);
	}

	printf("\n");

	return 0;
}