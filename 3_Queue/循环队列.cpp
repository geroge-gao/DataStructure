//循环队列:利用顺序栈实现



#include<iostream>
using namespace std;
#define MAXQSIZE 100
#define QElemType int
#define OK 1
#define ERROR 0

//定义循环队列
//循环队列的好处是可以充分的利用存储空间
typedef struct SqQueue{

	QElemType *base;
	int front;//游标，在顺序队列当中能起到指针的作用
	int rear;//注意尾指针指的是最后一位元素的后一位

}SqQueue;

int InitQueue(SqQueue &q)
{
	q.base=(QElemType*)malloc(sizeof(QElemType));
	if(!q.base)return ERROR;
	q.front=q.rear=0;
	return OK;
}

int QueueLength(SqQueue sq)
{
	return (sq.rear-sq.front+MAXQSIZE)%MAXQSIZE;//由于循环队列留一个空格避免当只剩下一个元素时头指针指向为指针
}

//入队

int EnQueue(SqQueue &sq,QElemType e)
{
	if((sq.rear+1%MAXQSIZE)==sq.front)return ERROR;//栈满,返回值为false
	
	sq.base[sq.rear]=e;
	sq.rear=(sq.rear+1)%MAXQSIZE;
	return OK;
}

//删除队列
 int DeQueue(SqQueue &sq,QElemType &e)
 {
	 if(sq.front==sq.rear)return ERROR;//如果栈空返回错误

	 e=sq.base[sq.front];
	 sq.front=(sq.front+1)%MAXQSIZE;//rear>maxqsize的情况
	 return OK;
 
 }


int main()
{
	SqQueue sq;
	InitQueue(sq);

	int n;
	QElemType m,e;
	printf("要入队列数据的个数:");
	scanf("%d",&n);

	//入队操作
	for(int i=0;i<n;i++)
	{
		scanf("%d",&m);
		EnQueue(sq,m);
	}
	//test length;
//	printf("队列的长度为:%d\n",QueueLength(sq));

	//出队操作


	while(QueueLength(sq))
	{
		DeQueue(sq,e);
		printf("%d ",e);
	}
	printf("\n");

	if(sq.front==sq.rear)
		printf("队列已被清空!\n");

	return 0;
}