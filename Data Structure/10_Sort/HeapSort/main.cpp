#include <iostream>

using namespace std;

#define SIZE 20

typedef int KeyType;

typedef struct
{
    KeyType key;
} RedType;

typedef struct
{
    RedType r[SIZE + 1];
    int length;
} SqList;

typedef SqList HeapType;

void HeapAdjust(HeapType & H, int s, int m)
{
    RedType rc;
    rc=H.r[s];
    for(int j=2*s;j<=m;j++)
    {
        if(j<m&&H.r[j].key<H.r[j+1].key)
            j++;
        if(rc.key>H.r[j].key)
            break;
        H.r[s]=H.r[j];
        s=j;
    }
    H.r[s]=rc;
}

void HeapSort(HeapType & H)
{
    int temp;
    for(int i=H.length/2;i>0;i--)
        HeapAdjust(H,i,H.length);
	for(int j=H.length;j>1;j--)
	{
		temp=H.r[1].key;
		H.r[1].key=H.r[j].key;
		H.r[j].key=temp;
		HeapAdjust(H,1,j-1);
	}

}

int main()
{
    int N;
    HeapType H;
    printf("输入元素个数:");
    scanf("%d", &N);
    H.length = N;

    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &H.r[i].key);
    }

    HeapSort(H);
	for(int j=1;j<=H.length;j++)
		printf("%d ",H.r[j].key);
	printf("\n");
}

// 49 38 65 97 76 13 27 49
