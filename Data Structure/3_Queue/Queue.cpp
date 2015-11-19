#include<iostream>
using namespace std;

#define QElemType int
#define OK 1
#define ERROR 0

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;


typedef struct Queue{

	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针

}Queue;

int InitQueue(Queue &q)
{
	q.front=(QueuePtr)malloc(sizeof(QNode));
	q.rear=q.front;
	if(!q.front) return ERROR;//申请内存失败
	q.front->next=NULL;//一定要将初始值设为空
	return OK;
	
}

//入队
int EnQueue(Queue &q,QElemType e)
{
	 QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	 if(!p)return ERROR;//申请失败
	 p->data=e;
	 p->next=NULL;
	 q.rear->next=p;
	 q.rear=p;
	 return OK;
	 
}

//出队列
int DeQueue(Queue &q,QElemType &e)
{
	QueuePtr p;
	if(q.front==q.rear)return ERROR;//此时队列为空.
	p=q.front->next;
	e=p->data;
	q.front->next=p->next; //保存队尾的指针域       
	if(q.rear==p)//如果只剩下一位时
	q.rear=q.front;
	free(p);
	
	return OK;
}	

//清空队

int DestroyQueue(Queue &q)
{
	QueuePtr p;
	while(q.front!=q.rear)
	{
		p=q.front->next;
		q.front=p->next;
		if(p==q.rear)q.rear=q.front;
		free(p);
	}

	if(q.front==q.rear)
		return OK;
	return ERROR;
}

//判断队列是否为空
int QueueEmpty(Queue q)
{
	if(q.front==q.rear)
		return OK;
	return ERROR;
}

//得到栈头
int GetHead(Queue &q,QElemType &e)
{
	if(q.front==q.rear)return ERROR;
	e=q.front->next->data;
	return OK;
	      
}

//栈如果从不是引用
int QueueLength(Queue q)
{
	int length=0;
	while(q.front->next!=NULL)
	{
		length++;
		q.front=q.front->next;
	}
	return length;
}



int main()
{
	int n;
	Queue q;
	QElemType e;
	
	InitQueue(q);

	for(int i=0;i<5;i++)
	{
		scanf("%d",&n);
		EnQueue(q,n);
	}

	//test队列的长度
	printf("队列的长度为:%d\n",QueueLength(q));

//	while(q.front->next!=NULL)
//	{
//		QueuePtr p;
//		p=q.front->next;
//		q.front->next=p->next;
//		printf("%d ",p->data);
//	}

	
	printf("\n");
	//test删除

	while(QueueLength(q))
	{
		DeQueue(q,e);
		printf("%d ",e);
	}

	if(QueueEmpty(q))
		printf("队列已被清空!\n");


	

	return 0;
}
