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

//创建一个全局变量
BiThrTree pre=NULL;

//二叉树的创建
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
		btt->LTag=Link;btt->RTag=Link;//为左右标签设置初始值
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

void PreOrderTraverse(BiThrTree btt)//递归前序遍历
{
	if(btt)
	{
		printf("%c",btt->data);
		PreOrderTraverse(btt->lchild);
		PreOrderTraverse(btt->rchild);
	}
}

void InOrderTraverse(BiThrTree btt)//递归中序遍历
{
	if(btt)
	{
		InOrderTraverse(btt->lchild);
		printf("%c",btt->data);
		InOrderTraverse(btt->rchild);
	}
}

void PostOrderTraverse(BiThrTree btt)//递归后续遍历
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
		InThreading(p->lchild);//线索化左树
		if(!p->lchild)//前去线索
		{
			p->lchild=pre;
			p->LTag=Thread;
		}
		if(!pre->rchild)//后继结点
		{
			pre->rchild=p;
			pre->RTag=Thread;
		}
		pre=p;//保存前驱节点		
		//注意在线索化最后一个结点时，p=pre，此时p->rchild是为空的，所以递归结束，最后一个结点没有成功被线索化
		InThreading(p->rchild);//线索化右树
	}
}

Status InOrderThreading(BiThrTree &Thrt,BiThrTree T)//中序线索化二叉树
{
	Thrt=(BiThrTree)malloc(sizeof(BiThrNode));//创建头结点
	if(!Thrt)return ERROR;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	Thrt->LTag=Link;
	if(!T)Thrt->lchild=Thrt;//左结点为空便指向自己
	else
	{
		Thrt->lchild=T;
		Thrt->LTag=Link;
		pre=Thrt;//保存上一节点
		InThreading(Thrt->lchild);
		pre->rchild=Thrt;//最后一个结点线索化
		Thrt->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T,Status(Visit)(TElemType e))
{
	BiThrTree p=T->lchild;
	while(p!=T)//当二叉树为空或者便利完成时，p=T
	{
		//由于中序遍历，首节点的左孩子是空的
		while(p->LTag==Link)//找到左孩子
			p=p->lchild;
		if(!Visit(p->data))return ERROR;
		while(p->RTag==Thread&&p!=T)//右孩子为空
		{
			p=p->rchild;//访问后继结点
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
	printf("先序遍历为:");
	InOrderThreading(Thrt,T);
	InOrderTraverse_Thr(Thrt,Visit);
	printf("\n");
	return 0;
}