#include<stdio.h>
#include<stdlib.h>

#define LH 1//左高
#define EH 0//等高
#define RH -1//右高
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef int Boolean;

typedef struct BSTNode{
    ElemType data;
    int bf;//节点的平衡因子
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

void R_Rotate(BSTree &p);
void L_Rotate(BSTree &p);
void LeftBalance(BSTree &T);
void RightBalance(BSTree &T);
Status InsertAVL(BSTree &T,ElemType e,Boolean &taller);
void PreOrderTraverse(BSTree p);

int main()
{
    BSTree T=NULL;
    int n,m;
    Boolean taller;
    printf("输入二叉树节点数:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m);
        InsertAVL(T,m,taller);
    }
    PreOrderTraverse(T);
    return 0;
}



Status InsertAVL(BSTree &T,ElemType e,Boolean &taller)
{
    if(!T)
    {
        T=(BSTNode*)malloc(sizeof(BSTNode));
        if(!T)exit(0);
        T->data=e;
        T->lchild=T->rchild=NULL;
        taller=TRUE;
        T->bf=EH;
    }
    else
    {
        if(e==T->data)//子树没有增长
        {
            taller=FALSE;
            return FALSE;
        }
        else if(e<T->data)
        {
            if(InsertAVL(T->lchild,e,taller))
                if(taller)
                {
                    switch (T->bf)
                    {
                    case LH:
                        LeftBalance(T);
                        taller=FALSE;
                        break;
                    case EH:
                        T->bf=LH;
                        taller=TRUE;
                        break;
                    case RH:
                        T->bf=EH;
                        taller=FALSE;
                        break;
                    }

                }
        }
        else
        {
            if(InsertAVL(T->rchild, e, taller))
                if(taller)
                {
                    switch(T->bf)
                    {
                    case LH:
                        T->bf = EH;
                        taller = FALSE;
                        break;

                    case EH:
                        T->bf = RH;
                        taller = TRUE;
                        break;

                    case RH:
                        RightBalance(T);
                        break;
                    }
                }
        }
    }
    return OK;
}

void LeftBalance(BSTree &T)
{
    BSTree lc,rd;
    lc=T->lchild;
    switch (lc->bf)//因为要平衡，所以平衡因子不可能为0
    {
    case LH:
        T->bf=lc->bf=EH;
        R_Rotate(T);
        break;
    case RH:
       T->bf=lc->bf=EH;
       L_Rotate(T->lchild);
       R_Rotate(T);
    }

}


void RightBalance(BSTree &T)
{
    BSTree rc,ld;
    rc=T->rchild;
    switch (rc->bf)
    {
    case LH:
        ld=rc->lchild;
        T->bf=rc->bf=ld->bf;
        R_Rotate(T->rchild);
        L_Rotate(T);
        break;
    case RH:
        T->bf=rc->bf=EH;
        L_Rotate(T);
        break;
    }

}

void R_Rotate(BSTree &p)
{
    BSTree rc;
    rc=p->lchild;
    p->lchild=rc->rchild;
    rc->rchild=p;
    p=rc;
}

void L_Rotate(BSTree &p)
{
    BSTree lc;
    lc=p->rchild;
    p->rchild=lc->lchild;
    lc->lchild=p;
    p=lc;
}

void PreOrderTraverse(BSTree p)
{
    if(p)
    {
        printf("%d ",p->data);
        PreOrderTraverse(p->lchild);
        PreOrderTraverse(p->rchild);
    }
}



