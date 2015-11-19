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
    RedType r[SIZE+1];
    int length;
}SqList;

int count=0;

void CreateSqList(SqList &L)
{
    int N;
    printf("输入元素个数:");
    scanf("%d",&N);
    L.length=N;
    for(int i=1;i<=N;i++)
        scanf("%d",&L.r[i].key);
}

int Partition(SqList &L,int low,int high)//最后返回的位置为枢轴的位置
{
    RedType t;
    L.r[0]=L.r[low];//设置枢轴
    while(low<high)
    {
        while(L.r[high].key>=L.r[0].key&&low<high)
            high--;
        L.r[low]=L.r[high];
        while(L.r[low].key<L.r[0].key&&low<high)
            low++;
        L.r[high]=L.r[low];
    }
    L.r[low]=L.r[0];
    return low;
}

void Print(SqList L)
{
    for(int i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
}

void Qsort(SqList &L,int low,int high)
{
    int i;
    if(low<high)
    {
        i=Partition(L,low,high);
        Qsort(L,low,i-1);
        Qsort(L,i+1,high);
        count++;
        printf("第%d趟排序:",count);
        Print(L);
    }
}

void QuickSort(SqList &L)
{
    Qsort(L,1,L.length);
}

int main()
{
    SqList L;
    CreateSqList(L);
    QuickSort(L);
    return 0;
}
