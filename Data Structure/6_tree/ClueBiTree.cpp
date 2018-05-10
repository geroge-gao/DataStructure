#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef enum PointerTag{Link,Thread};// Link == 0:ָ�룬Thread=1:����
typedef char TElemType;//��������
typedef int Status;

typedef struct BiThrNode{
	
	TElemType data;
	BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;//���ұ��

}BiThrNode,*BiThrTree;

//����һ��ȫ�ֱ���
BiThrTree pre=NULL;

//�������Ĵ���
Status CreateBiTree(BiThrTree &btt)
{
	char c;
	c=getchar();
	if(c=='#')
		btt=NULL;
	else
	{
		btt=(BiThrTree)malloc(sizeof(BiThrNode));
		btt->data=c;
		btt->LTag=Link;btt->RTag=Link;//Ϊ���ұ�ǩ���ó�ʼֵ
		CreateBiTree(btt->lchild);
		CreateBiTree(btt->rchild);
	}
	return OK;
}

Status Visit(TElemType e)
{
	if(e=='\0')
		return ERROR;
	else
	{
		printf("%c",e);
		return OK;
	}
}

void PreOrderTraverse(BiThrTree btt)//�ݹ�ǰ�����
{
	if(btt)
	{
		printf("%c",btt->data);
		PreOrderTraverse(btt->lchild);
		PreOrderTraverse(btt->rchild);
	}
}

void InOrderTraverse(BiThrTree btt)//�ݹ��������
{
	if(btt)
	{
		InOrderTraverse(btt->lchild);
		printf("%c",btt->data);
		InOrderTraverse(btt->rchild);
	}
}

void PostOrderTraverse(BiThrTree btt)//�ݹ��������
{
	if(btt)
	{
		PostOrderTraverse(btt->lchild);
		PostOrderTraverse(btt->rchild);
		printf("%c",btt->data);
	}
}

void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);//����������
		if(!p->lchild)//ǰȥ����
		{
			p->lchild=pre;
			p->LTag=Thread;
		}
		if(!pre->rchild)//��̽��
		{
			pre->rchild=p;
			pre->RTag=Thread;
		}
		pre=p;//����ǰ���ڵ�		
		//ע�������������һ�����ʱ��p=pre����ʱp->rchild��Ϊ�յģ����Եݹ���������һ�����û�гɹ���������
		InThreading(p->rchild);//����������
	}
}

Status InOrderThreading(BiThrTree &Thrt,BiThrTree T)//����������������
{
	Thrt=(BiThrTree)malloc(sizeof(BiThrNode));//����ͷ���
	if(!Thrt)return ERROR;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	Thrt->LTag=Link;
	if(!T)Thrt->lchild=Thrt;//����Ϊ�ձ�ָ���Լ�
	else
	{
		Thrt->lchild=T;
		Thrt->LTag=Link;
		pre=Thrt;//������һ�ڵ�
		InThreading(Thrt->lchild);
		pre->rchild=Thrt;//���һ�����������
		Thrt->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T,Status(Visit)(TElemType e))
{
	BiThrTree p=T->lchild;
	while(p!=T)//��������Ϊ�ջ��߱������ʱ��p=T
	{
		//��������������׽ڵ�������ǿյ�
		while(p->LTag==Link)//�ҵ�����
			p=p->lchild;
		if(!Visit(p->data))return ERROR;
		while(p->RTag==Thread&&p!=T)//�Һ���Ϊ��
		{
			p=p->rchild;//���ʺ�̽��
			Visit(p->data);
		}
		p=p->rchild;
	}
	return OK;
}//InOrderTraverse_Thr

int main()
{
	BiThrTree Thrt,T;
	CreateBiTree(T);
	printf("�������Ϊ:");
	InOrderThreading(Thrt,T);
	InOrderTraverse_Thr(Thrt,Visit);
	printf("\n");
	return 0;
}