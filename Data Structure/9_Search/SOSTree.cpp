#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
using namespace std;

#define Status int
#define OK 1
#define ERROR -1

typedef char S;
typedef struct{
    S data;
    int weight;
}ElemType;

typedef struct{
    ElemType *elem;
    int length;
}SSTable;

typedef struct BiTNode{

	ElemType data;
	struct BiTNode *lchild,*rchild;

}BiTNode,*BiTree;

typedef BiTree SOSTree;

void CreateSSTable(SSTable &ST,int n);
void FindSW(float sw[],SSTable ST);
Status CreateSOSTree(SOSTree &T,SSTable ST);
void SecondOptimal(BiTree &T,ElemType R[],float sw[],int low,int high);
void PreOrderTraverse(BiTree bt);//先序遍历

int main()
{
    SSTable ST;
    SOSTree T;
    int n;
    printf("输入元素个数:");
    scanf("%d",&n);
    CreateSSTable(ST,n);
    CreateSOSTree(T,ST);
    PreOrderTraverse(T);
    return 0;
}

void CreateSSTable(SSTable &ST,int n)
{
    ST.elem=(ElemType*)malloc((n+1)*sizeof(ElemType));
    if(!ST.elem)
    {
        printf("CreateSSTable Error");
        exit(0);
    }
    for(int i=1;i<=n;i++)
    {
        cin>>ST.elem[i].data>>ST.elem[i].weight;
    }
    ST.length=n;
}

void FindSW(float sw[],SSTable ST)
{
    for(int i=1;i<=ST.length;i++)
        sw[i]=0;
    for(int i=1;i<=ST.length;i++)
        for(int j=1;j<=i;j++)
            sw[i]+=ST.elem[j].weight;

}

Status CreateSOSTree(SOSTree &T,SSTable ST)
{
    float *sw;
    sw=new float[ST.length];
    if(ST.length==0)
        T=NULL;
    else
    {
        FindSW(sw,ST);
        SecondOptimal(T,ST.elem,sw,1,ST.length);
    }
    return OK;
}

void SecondOptimal(BiTree &T,ElemType R[],float sw[],int low,int high)
{
    float min=fabs(sw[high]-sw[low]);
    float dw=sw[high]+sw[low-1];
    int i=low;
    for(int j=1;j<=high;j++)
        if(fabs(dw-sw[j]-sw[j-1])<min)
        {
            min=fabs(dw-sw[j]-sw[j-1]);
            i=j;
        }

        T=(BiTree)malloc(sizeof(BiTNode));
        T->data.data=R[i].data;
        T->data.weight=R[i].weight;
        if(i==low)
            T->lchild=NULL;
        else
        {
            SecondOptimal(T->lchild,R,sw,low,i-1);
        }

        if(i==high)
            T->rchild=NULL;
        else
            SecondOptimal(T->rchild,R,sw,i+1,high);
}

void PreOrderTraverse(BiTree bt)
{
    if(bt)
    {
        printf("%c",bt->data.data);
        PreOrderTraverse(bt->lchild);
        PreOrderTraverse(bt->rchild);
    }
}


