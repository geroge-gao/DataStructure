#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
 
typedef struct Sqlist{
	int r[MAXSIZE+1];
	int length;
}Sqlist;

int initSq(Sqlist &L,int n)
{
	int i;
	L.length=n;
	if(L.length>MAXSIZE)
		return 0;
	for(i=1;i<=L.length;i++)
		scanf("%d",&L.r[i]);

	return 1;
}

int LT(int a,int b)
{
	if(a<b)
		return 1;
	return 0;
}

void InsertSort(Sqlist &L)
{
	int i,j;
	for(i=2;i<=L.length;i++)
	{
		if(LT(L.r[i],L.r[i-1]))
		{
			L.r[0]=L.r[i];
			L.r[i]=L.r[i-1];
			for(j=i-2;(LT(L.r[0],L.r[j]));--j)	
				L.r[j+1]=L.r[j];
			L.r[j+1]=L.r[0];
		}
	}
}

void BinserSort(Sqlist &L)
{
	int i,j;
	int m,high,low;
	for(i=2;i<=L.length;i++)
	{
		L.r[0]=L.r[i];
		low=1;
		high=i-1;
		while(low<=high)
		{
			m=(high+low)/2;
			if(LT(L.r[0],L.r[m]))
				high=m-1;
			else
				low=m+1;

			for(j=i-1;j>=high+1;--j)
				L.r[high+1]=L.r[0];
		}
	}
}

void Print(Sqlist L)
{
	int i;
	for(i=1;i<=L.length;i++)
		printf("%d ",L.r[i]);
	printf("\n");
}

int main()
{
	Sqlist L;
	int n;
	scanf("%d",&n);
	initSq(L,n);
	Print(L);
	return 0;
}
