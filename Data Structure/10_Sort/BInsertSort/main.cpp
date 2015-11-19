#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define Status int
typedef int KeyType;
typedef char InfoType;//����������,��������

typedef struct{
    KeyType key;
    InfoType info;
}RedType;

typedef struct{
    RedType r[MAXSIZE+1];//r[0]���ò���
    int length;
}SqList;

Status CreateSqList(SqList &L,int N)
{
    L.length=N;
    if(L.length>MAXSIZE)
        return ERROR;
    for(int i=1;i<=N;i++)
        scanf("%d",&L.r[i].key);
    return OK;
}

void Print(SqList L)
{
    for(int i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
}

void BInsertSort(SqList &L)//������������
{
    //�����۰����򣬶��������н�������
    int low,high;
    int mid;
    //˼����������۰��������������������ҵ����ʵ�λ��
    for(int i=2;i<=L.length;i++)
    {
        L.r[0]=L.r[i];
        low=1,high=i-1;
        while(low<=high)
        {
            mid=(low+high)/2;
            if(L.r[0].key<L.r[mid].key)
                high=mid-1;
            else
                low=mid+1;
        }
        //��Ҫ�����λ��Ϊhigh+1
        for(int j=i-1;j>=high+1;j--)
            L.r[j+1]=L.r[j];
        L.r[high+1]=L.r[0];
        printf("��%d������  ������:%d\n",i-1,L.r[0].key);
        Print(L);
    }
}

void TwoInsertSort(SqList &L)
{
    RedType d[L.length+1];

}


int main()
{
    SqList L;
    int N;
    printf("Ԫ�ظ���:");
    scanf("%d",&N);
    CreateSqList(L,N);
    BInsertSort(L);
    return 0;
}
