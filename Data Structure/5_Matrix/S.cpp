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
    int i,j;//非零元素的行下标和列下标
    ElemType e;
}Triple;

typedef struct{
    Triple data[MAXSIZE];
    int rpos[100];
    int num[100];//记录每一行的非零元素
    int mu,nu,tu;//矩阵的行数，列数和非零元素的个数
}TSMatrix;

Status CreateSMatrix(TSMatrix &M);//创建稀疏矩阵M
void PrintSMaxtrix(TSMatrix M);//输出稀疏矩阵
void DestorySMaxtrix(TSMatrix &M);//销毁稀疏矩阵
Status CopySMaxtrix(TSMatrix &T,TSMatrix M);//复制系数矩阵
Status AddSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//矩阵相加
Status SubMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//矩阵相减
Status MultSMatrix(TSMatrix &Q,TSMatrix M,TSMatrix N);//矩阵相乘
Status MultSMatrix_(TSMatrix &Q,TSMatrix M,TSMatrix N);//矩阵相乘
Status TransposeSMaktrix(TSMatrix &T,TSMatrix M);//压缩转置
Status FastTransposeSMatrix(TSMatrix &T,TSMatrix M);//快速转置

int main()
{
    TSMatrix M,T,N,Q;
    printf("矩阵M:\n");
    CreateSMatrix(M);
    PrintSMaxtrix(M);
//    printf("矩阵N:\n");
    CreateSMatrix(N);
    AddSMatrix(Q,M,N);
    PrintSMaxtrix(Q);
    MultSMatrix_(Q,M,N);
    PrintSMaxtrix(Q);
//    printf("翻转:\n");
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

    //统计每一行非零元素的个数
    for( i=1;i<=M.mu;i++)
        M.num[i]=0;
    for( i=1;i<=M.tu;i++)
        M.num[M.data[i].i]++;
    //计算每一行非零元素的位置
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
    //只考虑行优先
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
    //如果其中一个先完成
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
    //只考虑行优先
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
    //如果其中一个先完成
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

Status TransposeSMaktrix(TSMatrix &T,TSMatrix M)//压缩转置
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
        //求出cpot的值

        cpot[1]=1;//第一列可能没有元素，但是对于实际的结果没有影响
        for(int i=2;i<=T.tu;i++)
            cpot[i]=num[i-1]+cpot[i-1];

  //默认按行排序，所以对于j相同的翻转之后还是应该在前面
        for(int p=1;p<=M.tu;p++)//p,q表示行和列，表示数组下标时-1;
        {
            col=M.data[p].j;
            q=cpot[col];
            T.data[q].i=M.data[p].j;
            T.data[q].j=M.data[p].i;
            T.data[q].e=M.data[p].e;
            cpot[col]++;//向后以一段元素
        }
    }
    return OK;
}

Status MultSMatrix_(TSMatrix& Q,TSMatrix M,TSMatrix N)//
{
    //code::blocks默认将变量赋值为零
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
    if(M.tu*N.tu!=0)//Q是非零矩阵
    {
        for(int i=1;i<=Q.nu;i++)
            ctemp[i]=0;

    }
    return OK;
}





