//����������ʽ�洢
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define Status int
#define OK 1
#define ERROR 0
#define MAX_TREE_SIZE 100

typedef int ElemType;


typedef struct BiTNode{

	ElemType data;
	struct BiTNode *lchild,*rchild;

}BiTNode,*BiTree;

//��ʼ��������
//����һ��������
Status CreateBiTree(BiTree &bt)
{
	char c;
	c=getchar();
	if(c=='#')
		bt=NULL;//����ո�ͽ��ַ���
	else
	{
		bt=(BiTree)malloc(sizeof(BiTNode));
		if(!bt)return ERROR;//�����ڴ�ʧ��
		bt->data=c;
		CreateBiTree(bt->lchild);//��������
		CreateBiTree(bt->rchild);//�����ҽ��

	}
	return OK;
}

//ǰ�����������
void PreOrderTraverse(BiTree bt)
{
	if(bt)
	{
		printf("%c",bt->data);//��������ֵ��ӡ����
		PreOrderTraverse(bt->lchild);//�ȱ���������
		PreOrderTraverse(bt->rchild);//Ȼ�����������
	}
}

void InOrderTraverse(BiTree bt)
{
	if(bt)
	{
		InOrderTraverse(bt->lchild);
		printf("%c",bt->data);
		InOrderTraverse(bt->rchild);
	}
}

void PostOrderTraverse(BiTree bt)
{
	if(bt)
	{
		PostOrderTraverse(bt->lchild);
		PostOrderTraverse(bt->rchild);
		printf("%c",bt->data);
	}
}

int main()
{

	BiTree t;
	CreateBiTree(t);
	printf("�������Ϊ:");
	PreOrderTraverse(t);
	printf("\n");
	printf("�������Ϊ:");
	InOrderTraverse(t);
	printf("\n");
	printf("��������Ϊ:");
	PostOrderTraverse(t);
	printf("\n");

	return 0;
}
