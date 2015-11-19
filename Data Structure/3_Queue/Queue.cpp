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

	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ��

}Queue;

int InitQueue(Queue &q)
{
	q.front=(QueuePtr)malloc(sizeof(QNode));
	q.rear=q.front;
	if(!q.front) return ERROR;//�����ڴ�ʧ��
	q.front->next=NULL;//һ��Ҫ����ʼֵ��Ϊ��
	return OK;
	
}

//���
int EnQueue(Queue &q,QElemType e)
{
	 QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	 if(!p)return ERROR;//����ʧ��
	 p->data=e;
	 p->next=NULL;
	 q.rear->next=p;
	 q.rear=p;
	 return OK;
	 
}

//������
int DeQueue(Queue &q,QElemType &e)
{
	QueuePtr p;
	if(q.front==q.rear)return ERROR;//��ʱ����Ϊ��.
	p=q.front->next;
	e=p->data;
	q.front->next=p->next; //�����β��ָ����       
	if(q.rear==p)//���ֻʣ��һλʱ
	q.rear=q.front;
	free(p);
	
	return OK;
}	

//��ն�

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

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(Queue q)
{
	if(q.front==q.rear)
		return OK;
	return ERROR;
}

//�õ�ջͷ
int GetHead(Queue &q,QElemType &e)
{
	if(q.front==q.rear)return ERROR;
	e=q.front->next->data;
	return OK;
	      
}

//ջ����Ӳ�������
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

	//test���еĳ���
	printf("���еĳ���Ϊ:%d\n",QueueLength(q));

//	while(q.front->next!=NULL)
//	{
//		QueuePtr p;
//		p=q.front->next;
//		q.front->next=p->next;
//		printf("%d ",p->data);
//	}

	
	printf("\n");
	//testɾ��

	while(QueueLength(q))
	{
		DeQueue(q,e);
		printf("%d ",e);
	}

	if(QueueEmpty(q))
		printf("�����ѱ����!\n");


	

	return 0;
}
