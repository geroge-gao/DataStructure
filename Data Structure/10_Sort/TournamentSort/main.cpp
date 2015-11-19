#include <iostream>
#include<math.h>
using namespace std;

#define SIZE 30

typedef int Type;

typedef struct
{
    Type data;//数据值
    int index;//节点在满二叉树中顺序号
    int active;//节点参选标志，1:参选；0不参选
} DataNode;

int PowerOfTow(int n)
{
    int t = 1;

    while(t <= n)
    {
        t *= 2;
    }

    return t;
}

void UpdateTree(DataNode *tree,int i)
{
    int j;
    if(i%2==0)
        tree[i/2]=tree[i+1];//对手在右边
    else
        tree[(i-1)/2]=tree[i-1];//对手在左边
    i/=2;
    while(i>=2)
    {
        if(i%2==0)
            j=i+1;
        else
            j=i-1;
        if(!tree[i].active||!tree[j].active)
            if(tree[i].active)//i可参选
                tree[i/2]=tree[i];
            else
                tree[j/2]=tree[j];
        else//
        {
            if(tree[i].data<tree[j].data)
                tree[i/2]=tree[i];
            else
                tree[j/2]=tree[j];
        }
        i=i/2;
    }
}//UpdateTree

void TournamentSort(Type a[], int N)
{
    int i;
    int BottomRowSize = PowerOfTow(N);
    int TreeSize = 2 * BottomRowSize - 1;
    int loadindex = BottomRowSize - 1;

    DataNode tree[SIZE];

    //向胜利书外节点赋值
    int j=0;
    for(i = loadindex+1; i <=TreeSize; i++)
    {
        tree[i].index = i;
        if(i < TreeSize)
        {
            tree[i].data = a[j++];
            tree[i].active = 1;
        }
        else
        {
            tree[i].data = INT_MAX;
            tree[i].active = 0;
        }
    }
    i=BottomRowSize;
    while(i)
    {
        j=i;
        while(j<2*i-1)
        {
            if(!tree[j+1].active||tree[j].data<tree[j+1].data)
                tree[j/2]=tree[j];
            else
                tree[j/2]=tree[j+1];
            j+=2;
        }
        i=i/2;
    }
    for(int t=0;t<N;t++)
    {
        a[t]=tree[1].data;
        tree[tree[1].index].active=0;
        UpdateTree(tree,tree[1].index);
    }
}//TournamentSort

int main()
{
    int N;
    Type a[SIZE];
    printf("输入元素个数:");
    scanf("%d", &N);

    for(int i = 0; i < N; i++)
        scanf("%d",&a[i]);
    TournamentSort(a,N);
    for(int t=0;t<N;t++)
        printf("%d ",a[t]);
    return 0;
}
