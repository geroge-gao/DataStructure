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

//�������Ĵ���
void CreateBiTree(BiThrTree &btt)
{
	char c;
	c=getchar();
	if(c=='#')
		btt=NULL;
	else
	{
		btt=(BiThrTree)malloc(sizeof(BiThrNode));
		btt->data=c;
		CreateBiTree(btt->lchild);
		CreateBiTree(btt->rchild);
	}
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

//�ݹ�ǰ�����

void PreOrderTraverse(BiThrTree btt)
{
	if(btt)
	{
		printf("%c %c %c\n",btt->data,btt->lchild->data,btt->rchild->data);
		PreOrderTraverse(btt->lchild);
		PreOrderTraverse(btt->rchild);
	}
}

//�ݹ��������

void InOrderTraverse(BiThrTree btt)
{
	if(btt)
	{
		InOrderTraverse(btt->lchild);
		printf("%c",btt->data);
		InOrderTraverse(btt->rchild);
	}
}

//�ݹ��������

void PostOrderTraverse(BiThrTree btt)
{
	if(btt)
	{
		PostOrderTraverse(btt->lchild);
		PostOrderTraverse(btt->rchild);
		printf("%c",btt->data);
	}
}

//��������������

void InThreading(BiThrTree p)
{
	BiThrTree pre;
	if(p)	
	{
		pre=p;//����ǰ�����
		InThreading(p->lchild);//������������

		if(!p->lchild)//ǰ�����
		{
			p->LTag=Thread;
			p->lchild=pre;
		}

		if(!pre->rchild)//��̽��
		{
			pre->RTag=Thread;
			pre->lchild=p;
		}

		pre=p;//����preָ��p��ǰ��
		InThreading(p->rchild);//������������
	}
}//InThreading

//����������������
Status InOrderTraverse(BiThrTree &btt,BiThrTree T)
{
	BiThrTree pre;
	btt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!btt)exit(OVERFLOW);//

	//����ͷ���
	btt->LTag=Link;
	btt->RTag=Link;

	if(!T)btt->lchild=btt;//���������Ϊ�գ�����ָ���ָ
	else
	{
		btt->lchild=T;
		pre=btt;
		InThreading(T);//���������������������

		//�����һ���ڵ�������
		pre->rchild=btt;
		pre->RTag=Thread;
		btt->rchild=pre;
	}
	return OK;
}


int main()
{
	BiThrTree bt,btt;
	CreateBiTree(bt);
	InOrderTraverse(btt,bt);
	PreOrderTraverse(bt);
	printf("\n");
	return 0;
}