
//       author:gzj_1101
//       date:2015/7/29
//       time:16:54

#include<iostream>
#include<cstdio>
using namespace std;

#define OK 1
#define ERROR 0
#define Status int
#define MAXSIZE 12500

typedef int ElemType;

typedef struct{
    int i,j;//����Ԫ�ص����±�����±�
    ElemType e;
}Triple;

typedef struct{
    Triple data[MAXSIZE];
    int mu,nu,tu;//����������������ͷ���Ԫ�صĸ���
}TSMatrix;

Status CreateSMatrix(TSMatrix &M);//����ϡ�����M
void PrintSMaxtrix(TSMatrix M);//���ϡ�����
void DestorySMaxtrix(TSMatrix &M);//����ϡ�����
Status CopySMaxtrix(TSMatrix &T,TSMatrix M);//����ϵ������
Status AddSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status SubMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status MultSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status TransposeSMaktrix(TSMatrix &T,TSMatrix M);//ѹ��ת��
Status FastTransposeSMatrix(TSMatrix &T,TSMatrix M);//����ת��


int main()
{
    TSMatrix M,T;
    CreateSMatrix(M);
    PrintSMaxtrix(M);
    printf("��ת:\n");
    TransposeSMaktrix(T,M);
    PrintSMaxtrix(T);
    return 0;
}

Status CreateSMatrix(TSMatrix &M)
{
    printf("input mu,nu,tu:");
    scanf("%d%d%d",&M.mu,&M.nu,&M.tu);
    for(int k=1;k<=M.tu;k++)
        scanf("%d%d%d",&M.data[k].i,&M.data[k].j,&M.data[k].e);
    return OK;
}

void PrintSMaxtrix(TSMatrix M)
{
    printf("i  j  e\n");
    for(int k=1;k<=M.tu;k++)
        printf("%d  %d  %d\n",M.data[k].i,M.data[k].j,M.data[k].e);
}

void DestorySMaxtrix(TSMatrix &M)
{
    //
}

Status CopySMaxtrix(TSMatrix &T,TSMatrix M)
{
    T.mu=M.mu;
    T.nu=M.nu;
    T.tu=M.tu;
    for(int i=1;i<=T.tu;i++)
    {
        T.data[i].e=M.data[i].e;
        T.data[i].i=M.data[i].i;
        T.data[i].j=M.data[i].j;
    }

    return OK;
}

Status AddSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N)
{
    int j,k;
    int count=0;
    j=k=0;
    Q.mu=M.mu;
    Q.nu=M.nu;
    //ֻ����������
    while(j<=M.tu&&k<=N.tu)
    {
        if(M.data[j].i<N.data[j].i)
        {
            Q.data[count].e=M.data[j].e;
            Q.data[count].i=M.data[j].i;
            Q.data[count].j=M.data[j].j;
            j++;
            count++;
        }
        else if(M.data[j].i==N.data[k].i)
        {
            if(N.data[j].j<M.data[k].j)
            {
                Q.data[count].e = M.data[j].e;
                Q.data[count].i = M.data[j].i;
                Q.data[count].j = M.data[j].j;
                j++;
                count++;
            }
            else if(N.data[j].j==M.data[k].j)
            {
                Q.data[count].i = M.data[j].i;
                Q.data[count].j = M.data[j].j;
                Q.data[count].e=M.data[j].e+N.data[k].e;
                j++;
                k++;
                count++;
            }
            else
            {
                Q.data[count].e = N.data[k].e;
                Q.data[count].i = N.data[k].i;
                Q.data[count].j = N.data[k].j;
                k++;
                count++;
            }
        }
        else
        {
            Q.data[count].i=N.data[k].i;
            Q.data[count].j=N.data[k].j;
            Q.data[count].e=N.data[k].e;
            count++;
            k++;
        }
    }
    Q.tu=count;

    return OK;
}

Status SubMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N)
{
        int j,k;
    int count=0;
    j=k=1;
    Q.mu=M.mu;
    Q.nu=M.nu;
    //ֻ����������
    while(j<=M.tu&&k<=N.tu)
    {
        if(M.data[j].i<N.data[j].i)
        {
            Q.data[count].e=M.data[j].e;
            Q.data[count].i=M.data[j].i;
            Q.data[count].j=M.data[j].j;
            j++;
            count++;
        }
        else if(M.data[j].i==N.data[k].i)
        {
            if(N.data[j].j<M.data[k].j)
            {
                Q.data[count].e = M.data[j].e;
                Q.data[count].i = M.data[j].i;
                Q.data[count].j = M.data[j].j;
                j++;
                count++;
            }
            else if(N.data[j].j==M.data[k].j)
            {
                Q.data[count].i = M.data[j].i;
                Q.data[count].j = M.data[j].j;
                Q.data[count].e=M.data[j].e-N.data[k].e;
                j++;
                k++;
                count++;
            }
            else
            {
                Q.data[count].e = -N.data[k].e;
                Q.data[count].i = N.data[k].i;
                Q.data[count].j = N.data[k].j;
                k++;
                count++;
            }
        }
        else
        {
            Q.data[count].i=N.data[k].i;
            Q.data[count].j=N.data[k].j;
            Q.data[count].e=N.data[k].e;
            count++;
            k++;
        }
    }
    Q.tu=count;
    return OK;
}

Status TransposeSMaktrix(TSMatrix &T,TSMatrix M)//ѹ��ת��
{
    int count=0;
    T.mu=M.nu;
    T.nu=M.mu;
    T.tu=M.tu;
    if(T.tu)
        for(int col = 1; col <= T.mu; col++)
            for(int p = 1; p <= T.tu; p++)
                if(M.data[p].j == col)
                {
                    T.data[count].i = M.data[p].j;
                    T.data[count].j = M.data[p].i;
                    T.data[count].e = M.data[p].e;
                    count++;
                }

    return OK;
}//TransposeSMaktrix

Status FastTransposeSMatrix(TSMatrix &T,TSMatrix M)
{
    int col,q,num[100],cpot[100];
    T.tu=M.tu;
    T.mu=M.nu;
    T.nu=M.mu;
    if(T.tu)
    {
        for(int i=1;i<=M.mu;i++)num[i]=0;
        for(int i=0;i<T.tu;i++)++num[M.data[i].j];
        //���cpot��ֵ
        cpot[1]=1;//��һ�п���û��Ԫ�أ����Ƕ���ʵ�ʵĽ��û��Ӱ��
        for(int i=2;i<=T.tu;i++)
            cpot[i]=num[i-1]+cpot[i-1];
        for(int p=1;p<M.tu;p++)//p,q��ʾ�к��У���ʾ�����±�ʱ-1;
        {
            col=M.data[p].j;//�б����
            q=cpot[col];
            T.data[p-1].i=M.data[q-1].j;
            T.data[p-1].j=M.data[q-1].i;
        }



    }
    return OK;
}


