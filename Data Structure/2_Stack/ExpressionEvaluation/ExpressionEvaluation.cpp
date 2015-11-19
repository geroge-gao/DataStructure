#include<iostream>
using namespace std;

#define OK 1
#define ERROR -1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define Status int
#define ElemType char
#define OPSETSIZE 8

typedef struct Operand{//操作数

	double *base;//栈底指针
	double *top;//栈顶指针
	int size;
}Operand;

typedef struct Operator{

	char *base;//栈底指针
	char *top;//栈顶指针
	int size;
}Operator;

Status InitOprd(Operand &oprd)
{
	oprd.base=(double*)malloc(STACK_INIT_SIZE*sizeof(double));
	if(oprd.base==NULL)return ERROR;
	oprd.top=oprd.base;
	oprd.size=STACK_INIT_SIZE;
	return OK;
}

Status InitOprt(Operator &oprt)
{
	oprt.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(oprt.base==NULL)return ERROR;
	oprt.top=oprt.base;
	oprt.size=STACK_INIT_SIZE;
	return OK;
}

Status PushOprd(Operand &oprd,double e)
{
	if(oprd.top-oprd.base>STACK_INIT_SIZE)
	{
		oprd.base=(double*)realloc(oprd.base,(oprd.size+STACKINCREMENT)*sizeof(double));
		if(oprd.base==NULL)exit(0);
		oprd.top=oprd.base+STACK_INIT_SIZE;
		oprd.size+=STACKINCREMENT;
	}
	*oprd.top=e;
	oprd.top++;
	return OK;
}

Status PushOprt(Operator &oprt,ElemType e)
{
	if(oprt.top-oprt.base>STACK_INIT_SIZE)
	{
		oprt.base=(char*)realloc(oprt.base,(oprt.size+STACKINCREMENT)*sizeof(char));
		oprt.top=oprt.base+STACK_INIT_SIZE;
		oprt.size+=STACKINCREMENT;
	}
	*(oprt.top)=e;
	oprt.top++;
	return OK;
}


Status PopOprd(Operand &oprd,double &e)
{
	if(oprd.base==oprd.top)return ERROR;
	e=*(--oprd.top);
	return OK;
}

Status PopOprt(Operator &oprt,ElemType &e)
{
	if(oprt.base==oprt.top)return ERROR;
	e=*(--oprt.top);
	return OK;
}

char getOprdTop(Operand oprd)
{
	ElemType e;
	if(oprd.base==oprd.top)return ERROR;
	e=*(--oprd.top);
	return e;

}


char getOprtTop(Operator oprt)
{
	ElemType e;
	if(oprt.base==oprt.top)return ERROR;
	e=*(--oprt.top);
	return e;
}

char getOprtBase(Operator oprt)
{
	ElemType e;
	if(oprt.base==oprt.top) return ERROR;
	e=*(oprt.base);
	return e;
}

int getOprtSize(Operator oprt)
{
	int i=0;
	if(oprt.base==oprt.top)return 0;

	while(oprt.base!=oprt.top)
	{
		oprt.base++;
		i++;
	}

	return i;
}

int getOprdSize(Operand oprd)
{
	int i=0;
	if(oprd.base==oprd.top)return 0;

	while(oprd.base!=oprd.top)
	{
		oprd.base++;
		i++;
	}

	return i;
}


unsigned char Prior[8][8] = {   //运算符优先级表
  	  '>','>','<','<','<','>','>','>',
	  '>','>','<','<','<','>','>','>',
	  '>','>','>','>','<','>','>','>',
	  '>','>','>','>','<','>','>','>',
	  '<','<','<','<','<','=',' ','>',
	  '>','>','>','>',' ','>','>','>',
	  '<','<','<','<','<',' ','=','>',
	  '<','<','<','<','<','<','<','='
};	

char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#','\n'};

int ReturnOpOrd(char op,char* TestOp)
{
	for(int i=0;i<OPSETSIZE;i++)
		if(op==TestOp[i])
			return i;
	return 0;
}

int In(char op,char* TestOp)
{
	int find=0;
	for(int i=0;i<OPSETSIZE;i++)
		if(op==TestOp[i])
			find=1;

	return find;
}

char Precede(char op1,char op2)//比较运算符的优先级
{
	return Prior[ReturnOpOrd(op1,OPSET)][ReturnOpOrd(op2,OPSET)];
}

double Operate(double a,char op,double b)
{
	switch(op){
	case '+':return a+b;break;
	case '-':return a-b;break;
	case '*':return a*b;break;
	case '/':return a/b;break;
		
	}
}

double EvaluateExpression(Operand &oprd,Operator &oprt)
{
	char c;
	c=getchar();

	while(c!='\n'||getOprtSize(oprt)!=0)//执行到最后操作符栈只剩下换行符
	{
		if(!In(c,OPSET))
		{
			c=c-'0';
			PushOprd(oprd,c);
			c=getchar();
		}
		else//如果是操作符
		{
			if(getOprtSize(oprt)==0)//判断栈是否为空
			{
				PushOprt(oprt,c);
				c=getchar();
			}
			else
			{
				switch(Precede(getOprtTop(oprt),c)){
				case '>':
					double a,b;
					if(PopOprd(oprd,a))
						if(PopOprd(oprd,b))
						{
							char operate;
							PopOprt(oprt,operate);
							PushOprd(oprd,Operate(b,operate,a));
						}
				break;
				case '=':
					char ss;
					PopOprt(oprt,ss);
					c=getchar();
					break;
				case '<':
					PushOprt(oprt,c);
					c=getchar();
					break;
				}
			}
		}
	}
	double result;
	PopOprd(oprd,result);
	printf("%lf\n",result);
	return result;
}

main()
{
	Operand oprd;
	Operator oprt;
	InitOprt(oprt);
	InitOprd(oprd);
	EvaluateExpression(oprd,oprt);
	return 0;	
}