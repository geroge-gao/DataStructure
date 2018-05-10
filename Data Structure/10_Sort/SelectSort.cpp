#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define OK 1
#define ERROR 0
#define SIZE 20
typedef int KeyType;

typedef struct{
    KeyType key;
}RedType;

typedef struct{
    RedType r[SIZE];
    int length;
}SqList;

void CreateSqList(SqList &L,int N)
{
    L.length=N;
    for(int i=1;i<=L.length;i++)
        scanf("%d",&L.r[i].key);
}

int SelectMinKey(SqList &L,int i)
{
    int Min=L.r[i].key;
    for(int j=i;j<=L.length;j++)
        if(L.r[j].key<Min)
            Min=L.r[j].key;
    for(int j=i;j<=L.length;j++)
        if(L.r[j].key==Min)
            return j;
    return ERROR;
}

void SelectSort(SqList &L)
{
    int j,t;
    for(int i=1;i<L.length;i++)
    {
        j=SelectMinKey(L,i);
        if(i!=j)
        {
            t=L.r[i].key;
            L.r[i].key=L.r[j].key;
            L.r[j].key=t;
        }
    }
}

void Print(SqList L)
{
    for(int i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
}

int main()
{
   SqList L;
   int N;
   printf("输入元素个数:");
   scanf("%d",&N);
   CreateSqList(L,N);
   SelectSort(L);
   Print(L);
    return 0;
}
