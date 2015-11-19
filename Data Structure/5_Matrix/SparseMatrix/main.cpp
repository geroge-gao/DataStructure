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
    int rpos[100];
    int num[100];//��¼ÿһ�еķ���Ԫ��
    int mu,nu,tu;//����������������ͷ���Ԫ�صĸ���
}TSMatrix;

Status CreateSMatrix(TSMatrix &M);//����ϡ�����M
void PrintSMaxtrix(TSMatrix M);//���ϡ�����
void DestorySMaxtrix(TSMatrix &M);//����ϡ�����
Status CopySMaxtrix(TSMatrix &T,TSMatrix M);//����ϵ������
Status AddSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status SubMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status MultSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status MultSMatrix_(TSMatrix &Q,TSMatrix M,TSMatrix N);//�������
Status TransposeSMaktrix(TSMatrix &T,TSMatrix M);//ѹ��ת��
Status FastTransposeSMatrix(TSMatrix &T,TSMatrix M);//����ת��

int main()
{
    TSMatrix M,T,N,Q;
    printf("����M:\n");
    CreateSMatrix(M);
    PrintSMaxtrix(M);
//    printf("����N:\n");
    CreateSMatrix(N);
    AddSMatrix(Q,M,N);
    PrintSMaxtrix(Q);
    MultSMatrix_(Q,M,N);
    PrintSMaxtrix(Q);
//    printf("��ת:\n");
    FastTransposeSMatrix(T,M);
    PrintSMaxtrix(T);
    return 0;
}

Status CreateSMatrix(TSMatrix &M)
{
	int i;
    printf("input mu,nu,tu:");
    scanf("%d%d%d",&M.mu,&M.nu,&M.tu);
    for(int k=1;k<=M.tu;k++)
        scanf("%d%d%d",&M.data[k].i,&M.data[k].j,&M.data[k].e);

    //ͳ��ÿһ�з���Ԫ�صĸ���
    for( i=1;i<=M.mu;i++)
        M.num[i]=0;
    for( i=1;i<=M.tu;i++)
        M.num[M.data[i].i]++;
    //����ÿһ�з���Ԫ�ص�λ��
    for( i=1;i<=M.mu;i++)
        M.rpos[i]=0;
    if(M.num[M.mu]==0)
        M.rpos[M.mu]=M.tu+1;
    else
        M.rpos[M.mu]=M.tu-M.num[M.mu]+1;
    for( i=M.mu;i>=2;i--)
        if(i!=1&&M.rpos[i]==1)
        {
            M.rpos[i-1]=0;
            break;
        }
        else
            M.rpos[i-1]=M.rpos[i]-M.num[i-1];

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
    int t,k;
    int count=1;
    t=k=1;
    Q.mu=M.mu;
    Q.nu=M.nu;
    //ֻ����������
    while(t<=M.tu&&k<=N.tu)
    {
        if(M.data[t].i<N.data[k].i)
        {
            Q.data[count].e=M.data[t].e;
            Q.data[count].i=M.data[t].i;
            Q.data[count].j=M.data[t].j;
            t++;
        }
        else if(M.data[t].i==N.data[k].i)
        {
            if(M.data[t].j<N.data[k].j)
            {
                Q.data[count].e = M.data[t].e;
                Q.data[count].i = M.data[t].i;
                Q.data[count].j = M.data[t].j;
                t++;
            }
            else if(M.data[t].j==N.data[k].j)
            {
                Q.data[count].i = M.data[t].i;
                Q.data[count].j = M.data[t].j;
                Q.data[count].e=M.data[t].e+N.data[k].e;
                t++;
                k++;
            }
            else
            {
                Q.data[count].e = N.data[k].e;
                Q.data[count].i = N.data[k].i;
                Q.data[count].j = N.data[k].j;
                k++;
            }
        }
        else
        {
            Q.data[count].i=N.data[k].i;
            Q.data[count].j=N.data[k].j;
            Q.data[count].e=N.data[k].e;
            k++;
        }
        count++;
    }
    //�������һ�������
    if(t > M.tu)
        for(int i = k; i <= N.tu; i++)
        {
            Q.data[count].i = N.data[i].i;
            Q.data[count].j = N.data[i].j;
            Q.data[count].e = N.data[i].e;
        count++;
        }
    else
        for(int i=t;i<=M.tu;i++)
        {
            Q.data[count].e=M.data[i].e;
            Q.data[count].i=M.data[i].i;
            Q.data[count].j=M.data[i].j;
            count++;
        }
    Q.tu=count-1;

    return OK;
}

Status SubMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N)
{
     int t,k;
    int count=1;
    t=k=1;
    Q.mu=M.mu;
    Q.nu=M.nu;
    //ֻ����������
    while(t<=M.tu&&k<=N.tu)
    {
        if(M.data[t].i<N.data[k].i)
        {
            Q.data[count].e=M.data[t].e;
            Q.data[count].i=M.data[t].i;
            Q.data[count].j=M.data[t].j;
            t++;
        }
        else if(M.data[t].i==N.data[k].i)
        {
            if(M.data[t].j<N.data[k].j)
            {
                Q.data[count].e = M.data[t].e;
                Q.data[count].i = M.data[t].i;
                Q.data[count].j = M.data[t].j;
                t++;
            }
            else if(M.data[t].j==N.data[k].j)
            {
                Q.data[count].i = M.data[t].i;
                Q.data[count].j = M.data[t].j;
                Q.data[count].e=M.data[t].e-N.data[k].e;
                t++;
                k++;
            }
            else
            {
                Q.data[count].e = -N.data[k].e;
                Q.data[count].i = N.data[k].i;
                Q.data[count].j = N.data[k].j;
                k++;
            }
        }
        else
        {
            Q.data[count].i=N.data[k].i;
            Q.data[count].j=N.data[k].j;
            Q.data[count].e=-N.data[k].e;
            k++;
        }
        count++;
    }
    //�������һ�������
    if(t > M.tu)
        for(int i = k; i <= N.tu; i++)
        {
            Q.data[count].i = N.data[i].i;
            Q.data[count].j = N.data[i].j;
            Q.data[count].e = -N.data[i].e;
            count++;
        }
    else
        for(int i=t;i<=M.tu;i++)
        {
            Q.data[count].e=M.data[i].e;
            Q.data[count].i=M.data[i].i;
            Q.data[count].j=M.data[i].j;
            count++;
        }
    Q.tu=count-1;

    return OK;
}

Status TransposeSMaktrix(TSMatrix &T,TSMatrix M)//ѹ��ת��
{
    int count=1;
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
        for(int i=1;i<=T.tu;i++)++num[M.data[i].j];
        //���cpot��ֵ

        cpot[1]=1;//��һ�п���û��Ԫ�أ����Ƕ���ʵ�ʵĽ��û��Ӱ��
        for(int i=2;i<=T.tu;i++)
            cpot[i]=num[i-1]+cpot[i-1];

  //Ĭ�ϰ����������Զ���j��ͬ�ķ�ת֮����Ӧ����ǰ��
        for(int p=1;p<=M.tu;p++)//p,q��ʾ�к��У���ʾ�����±�ʱ-1;
        {
            col=M.data[p].j;
            q=cpot[col];
            T.data[q].i=M.data[p].j;
            T.data[q].j=M.data[p].i;
            T.data[q].e=M.data[p].e;
            cpot[col]++;//�����һ��Ԫ��
        }
    }
    return OK;
}

Status MultSMatrix_(TSMatrix& Q,TSMatrix M,TSMatrix N)//
{
    //code::blocksĬ�Ͻ�������ֵΪ��
    int count=1;
    for(int i=1;i<=M.tu;i++)
        for(int j=1;j<=N.tu;j++)
            if(M.data[i].j==N.data[j].i)
            {
                Q.data[count].i=M.data[i].i;
                Q.data[count].j=N.data[j].j;
                Q.data[count].e+=M.data[i].e*N.data[j].e;
                count++;
            }
    Q.tu=--count;
    printf("%d\n",Q.tu);
    for(int i=1;i<=Q.tu;i++)
        for(int j=i+1;j<=Q.tu;j++)
            if(Q.data[i].i==Q.data[j].i&&Q.data[i].j==Q.data[j].j)
                for(int k=j;k<=Q.tu-1;k++)
                {
                    Q.data[k]=Q.data[k+1];
                    Q.tu--;
                }
    return OK;
}

Status MultSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N)
{
    int ctemp[100],p,q,row,bcol;
    if(M.nu!=N.mu)return ERROR;
    Q.mu=M.mu;
    Q.nu=N.nu;
    Q.tu=0;
    if(M.tu*N.tu!=0)//Q�Ƿ������
    {
        for(int i=1;i<=Q.nu;i++)
            ctemp[i]=0;

    }
    return OK;
}





