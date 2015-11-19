#include<iostream>
#include<stdio.h>
#include<stdarg.h>
using namespace std;

#define MAX_ARRAY_DIM 8
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType * base;   //����Ԫ�ػ�ַ����InitArray����
    int      dim;      //����ά��
    int   *   bounds;   //����ά���ַ����InitArray���䣬�����ܹ��ĺ���
    int   *   constrant;   //����ӳ����������ַ
} Array;

Status InitArray(Array & A, int dim,...); //������Ӧ�ĺ�����������OK
Status DestoryArray(Array & A); //��������A
Status Assign(Array & A, ElemType e, ...); //��ʾ�������n����
Status Value(Array & A, ElemType e,int off ...);//������ֵΪ��ָ���ĺ���
Status Locate(Array & A, va_list ap, int & off);//���������е�Ԫ�أ����ַ

int main()
{
    Array A;
    int dim=2;
	int off;
	va_list ap;
    if(InitArray(A,dim,3,3))
        printf("init success\n");
	else
		printf("init failed\n");
	
	Assign(A,9,1,2,3,4,5,6,7,8,9);

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			printf("%d ",A.base[3*i+j]);
		printf("\n");
	}

    return 0;
}

Status InitArray(Array & A, int dim, ...)
{
    int elemtotal, n;
    va_list ap;

    if(dim < 1 || dim > MAX_ARRAY_DIM)
    {
        return ERROR;
    }

    A.dim = dim;
    A.bounds = (int *)malloc(dim * sizeof(int));

    if(!A.bounds)
    {
        exit(0);
    }

    elemtotal = 1;
    va_start(ap, dim);

    for(int i = 0; i < dim; i++)
    {
//        scanf("%d", &n);
        A.bounds[i] = va_arg(ap, int);
        if(A.bounds[i] < 0)
        {
            return 0;    //���
        }

        elemtotal *= A.bounds[i];
    }

    A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));

    if(!A.base)
    {
        exit(0);
    }

    A.constrant = (int *)malloc(dim * sizeof(int));

    if(!A.constrant)
    {
        exit(0);
    }

    //nγ�����Ѱַ��ʽ
    A.constrant[dim-1]=1;
    for(int k = dim - 2; k >= 0; k--)
    {
        A.constrant[k] = A.bounds[k + 1] * A.constrant[k + 1];
    }

    return OK;
}

Status DestoryArray(Array & A)
{
    if(!A.base)
    {
        return ERROR;
    }

    free(A.base);
    A.base = NULL;

    if(!A.bounds)
    {
        return ERROR;
    }

    free(A.bounds);
    A.bounds = NULL;

    if(!A.constrant)
    {
        return ERROR;
    }

    free(A.constrant);
    A.constrant = NULL;
    return OK;
}

Status Locate(Array & A, va_list ap, int & off)
{
    int ind;
	off=0;
    for(int i = 0; i < A.dim ; i++)
    {
        ind = va_arg(ap, int);//����ջ���Ƚ����

        if(ind < 0 || ind >= A.bounds[i])
        {
            return ERROR;
        }

        off += A.constrant[i] * ind;
    }

    return OK;
}

Status Value(Array &A,ElemType e,int off,...)
{
    va_list ap;
    va_start(ap,e);
    int result;
    result=Locate(A,ap,off);
    if(result<=0)
        return result;
    e=*(A.base+off);
    return OK;
}

Status Assign(Array &A,ElemType e,...)
{
    va_list ap;
    int result;
	int off;
    va_start(ap,e);
//	result=Locate(A,ap,off);
  //  if(result<=0)return result;
 //   *(A.base+off)=e;

	for(int i=0;i<A.bounds[0];i++)
		for(int j=0;j<A.bounds[1];j++)
			A.base[3*i+j]=va_arg(ap,int);
    return OK;
}




