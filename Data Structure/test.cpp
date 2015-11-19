#include<iostream>
using namespace std;

#define INIT_LIST 100
#define LIST_ADD 10 
#define OK 1
#define ERROR 0

typedef int ElemType ;

typedef struct{
	ElemType *elem;
	int length;
	int lengthsize;
}Sqlist;

//初始化创建一个线性表
int InitList(Sqlist &l)
{
	l.elem=(ElemType*)malloc(INIT_LIST*sizeof(ElemType));
	if(!l.elem) exit(ERROR);//内存申请失败
	l.length=0;//当前线性表单中的元素为0
	l.lengthsize=INIT_LIST;//初始化线性表的容量
	return OK;
}

//向象线性表单中插入数据
 ListInsert(Sqlist &l,int i,ElemType e)
{
	//在线性表当中创建第一个元素
	if(l.length==0)
	{
		l.elem[0]=e;
		l.length++;
		return OK;
	}
	if(i<1||i>l.length+1)return ERROR;//输入i的值不合法

	if(l.length>=l.lengthsize){
		ElemType *a=(ElemType*)realloc(l.elem,(LIST_ADD+l.lengthsize)*sizeof(ElemType));
	
		l.elem=a;
		if(!a)exit(ERROR);//重新申请内存失败
		l.lengthsize+=LIST_ADD;//扩展线性表的容量
	}

	else{

		int t=0;
		for(int i=0;i<l.length;i++)
			if(e==l.elem[i])
				t++;
		if(t==0)
		{
			ElemType *p=&(l.elem[i-1]);
			for(ElemType *q=&(l.elem[l.length-1]);q>=p;--q)
			{
				*(q+1)=*q;
			}
			l.elem[i-1]=e;
			l.length++;
		}
	
	}
	return OK;
}	

int ListDelete(Sqlist &l,int i,ElemType &e)
{
	if(i<1||i>l.length)return ERROR;//输出的i的值不合法，抛出错误
	
	//首先取出要删除的位置的地址
	ElemType *p=&l.elem[i-1];
	e=*p;//返回被删除数的值
	for(++p;p<=&(l.elem[l.length-1]);p++)
	{
		*(p-1)=*p;
	}
	l.length--;
	return OK;

}

int compare(ElemType e1,ElemType e2)//判断两个元素是否相等
{
	if(e1==e2)
		return OK;
	return ERROR;
}

int LocalElem(Sqlist l,ElemType e)//返回要查询的数据在线性表当中的位置，如果没有返回错误
{
	for(int i=0;i<l.length;i++)
		if(compare(l.elem[i],e))
		{
			return i+1;
		}

	return ERROR;
}
void GetElem(Sqlist l,int i,ElemType &e)
{
	if(i<1||i>l.length)
		printf("i的数据不合法!\n");
	//用e将线性表当中的第i位数据返回
	e=l.elem[i-1];
}


//函数还没有测试
void MergList(Sqlist la,Sqlist lb,Sqlist &lc)
{
	InitList(lc);
	int k=1,l=1,k1,l1;
	//按照大小顺序一次在在两个线性表当中将数据取出来，将其出入lc当中
	while(k<=la.length&&l<lb.length)
	{
		k1=la.elem[k-1];
		l1=lb.elem[l-1];
		if(k1<=l1)
		{
			ListInsert(lc,lc.length+1,k1);
			k++;
		}
		else
		{
			ListInsert(lc,lc.length+1,l1);
			l++;
		}
	}
	
	//可能存在一个线性表先遍历完的情况
	//lb先遍历完
	while(k<=la.length)
	{
		ListInsert(lc,lc.length,la.elem[k-1]);
		k++;
	}

	//la先遍历完
	while(l<=lb.length)
	{
		ListInsert(lc,lc.length,lb.elem[l-1]);
		l++;
	}
//	return OK;
}

void Union(Sqlist &la, Sqlist lb)
{
	for(int i=0;i<lb.length;i++)
		ListInsert(la,la.length,lb.elem[i]);
}

int main()
{

	Sqlist la,lb;
	int i,j;
	if(InitList(la)&&InitList(lb))printf("线性表创建成功!\n");

	for(i=0;i<10;i++)
		ListInsert(la,la.length,i+1);
	for(j=0;j<10;j+=2)
		ListInsert(lb,lb.length,j+2);

		//输出线性表
	for(i=0;i<la.length;i++)
		printf("%d ",la.elem[i]);
	printf("\n");
	for(i=0;i<lb.length;i++)
		printf("%d ",lb.elem[i]);
	printf("\n");

	Union(la,lb);

	printf("合并之后线性表la的值为:\n");
	for(i=0;i<la.length;i++)
		printf("%d ",la.elem[i]);
	printf("\n");
	
	return 0;
}