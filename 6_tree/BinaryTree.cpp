//二叉树的链式存储
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
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

//初始化二叉树
//创建一个二叉树
Status CreateBiTree(BiTree &bt)
{
	char c;
	c=getchar();
	if(c=='#')
		bt=NULL;//输入空格就将字符置
	else
	{
		bt=(BiTree)malloc(sizeof(BiTNode));
		if(!bt)return ERROR;//申请内存失败
		bt->data=c;
		CreateBiTree(bt->lchild);//创建左结点
		CreateBiTree(bt->rchild);//创建右结点

	}
	return OK;
}

//前序遍历二叉树
void PreOrderTraverse(BiTree bt)
{
	if(bt)
	{
		printf("%c",bt->data);//将遍历的值打印出来
		PreOrderTraverse(bt->lchild);//先遍历左子树
		PreOrderTraverse(bt->rchild);//然后遍历右子树
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

void LevelOrderTraverse(BiTree bt)//借助于辅助栈
{
    queue<BiTree> q;
    BiTree t;
    q.push(bt);
    while(!q.empty())
    {
        t=q.front();
        q.pop();
        printf("%c",t->data);
        if(t->lchild)
            q.push(t->lchild);
        if(t->rchild)
            q.push(t->rchild);
    }
}

int main()
{
	BiTree t;
	CreateBiTree(t);
	printf("先序遍历为:");
	PreOrderTraverse(t);
	printf("\n");

	printf("中序遍历为:");
	InOrderTraverse(t);
	printf("\n");
	printf("后续遍历为:");
	PostOrderTraverse(t);
	printf("\n");
	printf("层序遍历为:");
	LevelOrderTraverse(t);
	printf("\n");
	return 0;
}
