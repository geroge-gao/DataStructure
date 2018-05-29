#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZZE 100
#define STACKINCREMENT 10
#define SElemType int

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

	s.top=s.base;
	s.size=STACK_INIT_SIZZE;//��ǰջ�ĳ���

	return OK;

	
}

int StackEmpty(SqStack s)
{
	if(s.base==s.top)//��ջ������ջ�׵�ʱ��˵��ջΪ��
		return OK;
	return ERROR;
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

//��ջ
int Pop(SqStack &s,SElemType &e)
{
	//���ջ��Ϊ�գ���ɾ��s��ջ��Ԫ�أ�����e����ֵ���ػ���
	if(s.base==s.top)return ERROR;
	e=*(--s.top);
	return OK;
	
}

//��ʮ����ת��������������
void conversion(SqStack &s)
{
	InitStack(s);
	int n,m;
	scanf("%d",&n);//����Ҫ��ת������

	printf("����Ҫת���Ľ���:");
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

//��ջ�������
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