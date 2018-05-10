#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef enum PointerTag{Link,Thread};// Link == 0:指针，Thread=1:线索

typedef char TElemType;//数据类型
typedef int Status;

typedef struct BiThrNode{

	TElemType data;
	BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;//左右标点

}BiThrNode,*BiThrTree;

//二叉树的创建
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

//递归前序遍历

void PreOrderTraverse(BiThrTree btt)
{
	if(btt)
	{
		printf("%c %c %c\n",btt->data,btt->lchild->data,btt->rchild->data);
		PreOrderTraverse(btt->lchild);
		PreOrderTraverse(btt->rchild);
	}
}

//递归中序遍历

void InOrderTraverse(BiThrTree btt)
{
	if(btt)
	{
		InOrderTraverse(btt->lchild);
		printf("%c",btt->data);
		InOrderTraverse(btt->rchild);
	}
}

//递归后续遍历

void PostOrderTraverse(BiThrTree btt)
{
	if(btt)
	{
		PostOrderTraverse(btt->lchild);
		PostOrderTraverse(btt->rchild);
		printf("%c",btt->data);
	}
}

//二叉树的线索化

void InThreading(BiThrTree p)
{
	BiThrTree pre;
	if(p)	
	{
		pre=p;//保存前驱结点
		InThreading(p->lchild);//左子树线索化

		if(!p->lchild)//前驱结点
		{
			p->LTag=Thread;
			p->lchild=pre;
		}

		if(!pre->rchild)//后继结点
		{
			pre->RTag=Thread;
			pre->lchild=p;
		}

		pre=p;//保持pre指向p的前驱
		InThreading(p->rchild);//线索化右子树
	}
}//InThreading

//中序线索化二叉树
Status InOrderTraverse(BiThrTree &btt,BiThrTree T)
{
	BiThrTree pre;
	btt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!btt)exit(OVERFLOW);//

	//建立头结点
	btt->LTag=Link;
	btt->RTag=Link;

	if(!T)btt->lchild=btt;//如果二叉树为空，则做指针回指
	else
	{
		btt->lchild=T;
		pre=btt;
		InThreading(T);//中序遍历建立中序线索化

		//将最后一个节点线索化
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