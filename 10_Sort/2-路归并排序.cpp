#include <iostream>
#include<stdlib.h>
using namespace std;

void Merge(int *a,int s,int m,int n)
{
	int temp[20];
	int i=s,q=s;
	int j=m+1;
	while(i<=m&&j<=n)
	{
		if(a[i]<a[j])
			temp[q++]=a[i++];
		else
			temp[q++]=a[j++];
	}

	while(i<=m)
		temp[q++]=a[i++];
	while(j<=n)
		temp[q++]=a[j++];
	for(int k=s;k<=n;k++)
		a[k]=temp[k];
}

void MSort(int *a,int s,int t)
{
    int m;
    if(s==t)
        return;
    else
    {
        m=(s+t)/2;
        MSort(a,s,m);
        MSort(a,m+1,t);
        Merge(a,s,m,t);
    }
}

void MergeSort(int a[],int N)
{
    MSort(a,1,N);
}

int main()
{
    int a[20],N,b[20];
    printf("输入元素个数:");
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        scanf("%d",&a[i]);
    MergeSort(a,N);
    for(int t=1;t<=N;t++)
        printf("%d ",a[t]);
    printf("\n");
    return 0;
}

// 49 38 65 97 13 27 76
