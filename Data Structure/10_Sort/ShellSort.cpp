#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define OK 1
#define ERROR 0
#define SIZE 20

typedef struct{
    int key[SIZE];
    int length;
}SqList;

int dlta[]={5,3,1};
void CreateSqList(SqList &L,int N)
{
    L.length=N;
    for(int i=1;i<=L.length;i++)
        scanf("%d",&L.key[i]);
}

void ShellInsert(SqList &L,int dk)
{
    int temp;
    for(int i=1;i<=L.length-dk;i++)
        if(L.key[i]>L.key[i+dk])
        {
            temp=L.key[i];
            L.key[i]=L.key[i+dk];
            L.key[i+dk]=temp;
        }
}

void ShellSort(SqList &L,int t)
{
    for(int k=0;k<t;k++)
        ShellInsert(L,dlta[k]);
}

void Print(SqList L)
{
    for(int i=1;i<=L.length;i++)
        printf("%d ",L.key[i]);
    printf("\n");
}


int main()
{
    int t,N;
    SqList L;
    printf("输入元素个数:");
    scanf("%d",&N);
    CreateSqList(L,N);
    ShellSort(L,3);
    Print(L);
    return 0;
}
