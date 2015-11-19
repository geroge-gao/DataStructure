//ѭ������:����˳��ջʵ��



#include<iostream>
using namespace std;
#define MAXQSIZE 100
#define QElemType int
#define OK 1
#define ERROR 0

//����ѭ������
//ѭ�����еĺô��ǿ��Գ�ֵ����ô洢�ռ�
typedef struct SqQueue{

	QElemType *base;
	int front;//�α꣬��˳����е�������ָ�������
	int rear;//ע��βָ��ָ�������һλԪ�صĺ�һλ

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
	return (sq.rear-sq.front+MAXQSIZE)%MAXQSIZE;//����ѭ��������һ���ո���⵱ֻʣ��һ��Ԫ��ʱͷָ��ָ��Ϊָ��
}

//���

int EnQueue(SqQueue &sq,QElemType e)
{
	if((sq.rear+1%MAXQSIZE)==sq.front)return ERROR;//ջ��,����ֵΪfalse
	
	sq.base[sq.rear]=e;
	sq.rear=(sq.rear+1)%MAXQSIZE;
	return OK;
}

//ɾ������
 int DeQueue(SqQueue &sq,QElemType &e)
 {
	 if(sq.front==sq.rear)return ERROR;//���ջ�շ��ش���

	 e=sq.base[sq.front];
	 sq.front=(sq.front+1)%MAXQSIZE;//rear>maxqsize�����
	 return OK;
 
 }


int main()
{
	SqQueue sq;
	InitQueue(sq);

	int n;
	QElemType m,e;
	printf("Ҫ��������ݵĸ���:");
	scanf("%d",&n);

	//��Ӳ���
	for(int i=0;i<n;i++)
	{
		scanf("%d",&m);
		EnQueue(sq,m);
	}
	//test length;
//	printf("���еĳ���Ϊ:%d\n",QueueLength(sq));

	//���Ӳ���


	while(QueueLength(sq))
	{
		DeQueue(sq,e);
		printf("%d ",e);
	}
	printf("\n");

	if(sq.front==sq.rear)
		printf("�����ѱ����!\n");

	return 0;
}