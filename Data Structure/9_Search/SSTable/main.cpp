#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define Status int
#define OK 1
#define ERROR -1

typedef int ElemType;
typedef struct{
    ElemType *elem;
    int length;
}SSTable;


void CreateSSTable(SSTable &ST)
{
    int n;
    printf("输入元素的个数:");
    scanf("%d",&n);
    ST.elem=(ElemType*)malloc((n+1)*sizeof(ElemType));
    for(int i=1;i<=n;i++)
        scanf("%d",&ST.elem[i]);
    ST.length=n;
}

void SortSSTable(SSTable &ST)
{
    ElemType e;
    for(int i=1;i<=ST.length;i++)
        for(int j=1;j<=ST.length-i;j++)
            if(ST.elem[i]<ST.elem[j])
            {
                e=ST.elem[i];
                ST.elem[i]=ST.elem[j];
                ST.elem[j]=e;
            }
}

Status Search_Sq(SSTable ST,ElemType key)
{
    ST.elem[0]=key;
    for(int i=ST.length;ST.elem[i]!=key;i--)
        return i;
}

Status Search_Bin(SSTable ST,ElemType e)
{
    int low,high,mid;
    low=1;
    high=ST.length;

    while(low<high)
    {
        mid=(low+high)/2;
        if(e>ST.elem[mid])
            low=mid+1;
        else if(e<ST.elem[mid])
            high=mid-1;
        else
            return mid;
    }
    return ERROR;
}


int main()
{
    SSTable ST;
    ElemType e;
    CreateSSTable(ST);
    printf("输入要查找的数:");
    scanf("%d",&e);
    if(Search_Sq( ST,e))
        printf("查找成功!\n");
    else
        printf("不存在该元素\n");
    SortSSTable(ST);
    for(int i=1;i<=ST.length;i++)
        printf("%d",ST.elem[i]);
    printf("\n");
    if(Search_Bin(ST,e)>=0)
        printf("二分查找成功!\n");
    else
        printf("二分查找失败!\n");
    return 0;
}
