#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define OK 1
#define ERROR -1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

Status SearchBST(BiTree T,ElemType e,BiTree f,BiTree &p);//f为上一个节点的子结点,保存返回的结点
Status InsertBST(BiTree &T,ElemType e);
Status Delete(BiTree p,BiTree &q);
Status DeleteBST(BiTree &T,ElemType e,BiTree &p);
void PreOrderTraverse(BiTree bt);

int main()
{
    ElemType a[20],m;
    BiTree bt=NULL,p=NULL;
    int n;
    printf("请输入元素个数:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
        InsertBST(bt,a[i]);
    PreOrderTraverse(bt);
    printf("\n输入查找元素:");
    scanf("%d",&n);
    if(SearchBST(bt,n,NULL,p))
    {
        printf("查找成功!\n");
    }
    else
        printf("查找失败!\n");

    printf("输入删除元素:");
    scanf("%d",&m);
    DeleteBST(bt,m,p);
    PreOrderTraverse(bt);
    printf("\n");
    return 0;
}

Status SearchBST(BiTree T,ElemType e,BiTree f,BiTree &p)
{
    if(!T)
    {
        p=f;//保存上一个结点
        return FALSE;
    }
    if(T->data>e)
        SearchBST(T->lchild,e,T,p);
    else if(T->data<e)
        SearchBST(T->rchild,e,T,p);
    else
    {
        p=T;
        return OK;
    }
}

Status InsertBST(BiTree &T,ElemType e)
{
    BiTree p,s;
    if(!SearchBST(T,e,NULL,p))
    {
        s=(BiTNode*)malloc(sizeof(BiTNode));
        if(!s)
        {
            printf("Insert Error\n");
            exit(0);
        }
        s->data=e;
        s->lchild=s->rchild=NULL;
        if(!p)
            T=s;
        else if(p->data>e)
            p->lchild=s;
        else if(p->data<e)
            p->rchild=s;
        return OK;
    }

    return FALSE;
}

Status DeleteBST(BiTree &T,ElemType e,BiTree &p)
{
    if(!T)
        return FALSE;
    else
    {
        if(T->data==e)
            return Delete(T,p);
        else if(T->data>e)
            return DeleteBST(T->lchild,e,T);
        else
            return DeleteBST(T->rchild,e,T);
    }
}

Status Delete(BiTree p,BiTree &q)
{
    BiTNode *s,*t,*m;
    if(q)
    {
        if(p==q->lchild)
        {
            t=q->lchild;
            if(!t->lchild)
            {
                q->lchild=t->rchild;
                free(t);
            }
            else if(!t->rchild)
            {
                q->lchild=t->lchild;
                free(t);
            }
            else
            {
                m=t;
                s=t->lchild;
                while(s->rchild)
                {
                    m=s;
                    s=s->rchild;
                }
                t->data=s->data;
                if(m!=t)
                    m->rchild=s->lchild;
                else
                    t->lchild=s->lchild;
                free(s);
            }
        }
        else
        {
            t=q->rchild;
            if(!t->lchild)
            {
                q->rchild=t->rchild;
                free(t);
            }
            else if(!t->rchild)
            {
                q->rchild=t->lchild;
                free(t);
            }
            else
            {
                m=t;
                s=t->lchild;
                while(s->rchild)
                {
                    m=s;
                    s=s->rchild;
                }
                t->data=m->data;
                if(m!=t)
                    m->rchild=s->lchild;
                else
                    t->lchild=s->lchild;
                free(s);
            }
        }
    }
	return OK;
}

void PreOrderTraverse(BiTree bt)
{
    if(bt)
    {
        printf("%d ",bt->data);
        PreOrderTraverse(bt->lchild);
        PreOrderTraverse(bt->rchild);
    }
}
