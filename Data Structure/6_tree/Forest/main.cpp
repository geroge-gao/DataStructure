#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define Status int
#define OK 1
#define ERROR 0
typedef char ElemType;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchirld,*nextsibling;//
}CSNode,*Forest;


Status CreateBiTree(BiTree &bt);
Status PreOrderTraverse(BiTree bt);
Status InOrderTraverse(BiTree bt);
Status PostOrderTraverse(BiTree bt);
Status BT2Forest(BiTree bt,Forest &f);
Status Forest2BT(Forest F,BiTree &bt);

int main()
{
    BiTree bt;
    CreateBiTree(bt);
    PreOrderTraverse(bt);
    return 0;
}

Status CreateBiTree(BiTree &bt)
{
    char c;
    c=getchar();
    if(c=='#')
        bt=NULL;
    else
    {
        bt=(BiTNode*)malloc(sizeof(BiTNode));
        bt->data=c;
        CreateBiTree(bt->lchild);
        CreateBiTree(bt->rchild);
    }
}

Status PreOrderTraverse(BiTree bt)
{
    if(bt)
    {
        printf("%c",bt->data);
        PreOrderTraverse(bt->lchild);
        PreOrderTraverse(bt->rchild);
    }
    return OK;
}

Status InOrderTraverse(BiTree bt)
{
    if(bt)
    {
        InOrderTraverse(bt->lchild);
        printf("%c",bt->data);
        InOrderTraverse(bt->rchild);
    }
    return OK;
}

Status PostOrderTraverse(BiTree bt)
{
    if(bt)
    {
        PostOrderTraverse(bt->lchild);
        PostOrderTraverse(bt->rchild);
        printf("%c",bt->data);
    }
}

Status BT2Forest(BiTree bt,Forest &F)
{
    if(bt==NULL)
        F=NULL;
    else
    {
        F->data=bt->data;
        BT2Forest(bt->lchild,F->firstchirld);
        BT2Forest(bt->lchild,F->nextsibling);
    }
    return OK;
}

Status Forest2BT(Forest F,BiTree &bt)
{
    if(F=NULL)
        bt=NULL;
    else
    {
        bt->data=F->data;
        Forest2BT(F->firstchirld,bt->lchild);
        Forest2BT(F->nextsibling,bt->rchild);
    }
    return OK;
}
