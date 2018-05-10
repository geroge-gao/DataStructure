#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
#define SElemType char 

typedef struct SqStack{

	SElemType *base;//ջ��ָ��
	SElemType *top;//ջ��ָ��
	int size;
}SqStack;

//��ʼ��һ��ջ
int InitStack( SqStack &s)
{
	s.base=(SElemType*)malloc(STACK_INIT_SIZZE*sizeof(SElemType));
	if(s.base==NULL)return ERROR;

	s.top=s.base;//����ջ��Ϊ��
	s.size=STACK_INIT_SIZZE;//��ǰջ�ĳ���

	return OK;

	
}

int StackEmpty(SqStack s)
{
//	if(s.base==s.top)//��ջ������ջ�׵�ʱ��˵��ջΪ��
//		return OK;
//	return ERROR;
	return s.top==s.base;
}

//��ջ
int Push(SqStack &s, SElemType e)
{
	if(s.top-s.base>STACK_INIT_SIZZE)
	{
		s.base=(SElemType*)realloc(s.base,(s.size+STACKINCREMENT)*sizeof(SElemType));//����ڴ��������·����ڴ�ռ�
		if(!s.base)exit(ERROR);//�ڴ����ʧ��
		s.top=s.base+STACK_INIT_SIZZE;
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