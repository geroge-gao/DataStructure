#include<iostream>
using namespace std;

#define LIST_INIT_SIZE 100//线性表存储空间的初始分配值
#define lr 10//线性表存储空间的分配增量
#define OK 1
#define ERROR 0

//定义元素的类型
typedef int ElemType;

typedef struct{
  ElemType *elem;
  int length;//当前的长度
  int size;//当前分配存储容量

} Sqlist;

//创建一个线性表
int InitList(Sqlist &l)
{
	//为线性表申请100个存储空间
	l.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!l.elem)
	{
		exit(0);
	}

	l.length=0;//当前链表中的元素为零
	l.size=LIST_INIT_SIZE;
	return OK;
}


int compare(ElemType e1,ElemType e2)
{
	if(e1==e2)
		return OK;
	else
		return ERROR;
}

//清除线性表
void ClearList(Sqlist &l)
{
	l.length=0;
//	return OK;
}

void destoryList(Sqlist &l)
{
	delete []l.elem;
}


int ListEmpty(Sqlist &l)
{
	if(l.size!=0)
		return ERROR;
	else
		return OK;
}

//返回线性表当前的长度
int ListLenght(Sqlist l)
{
	return l.length;
}

//得到线性表中的第I个元素
void GetElem(Sqlist l,int i,ElemType &e)
{
	e=l.elem[i-1];
}

//判断e是否在线性表当中，并将其位置返回回来
//int LocateElem(Sqlist l,ElemType e,Status (*compare)(ElemType e1,ElemType e2))
int LocateElem(Sqlist l,ElemType e)
{
	for(int i=0;i<l.length;i++)
		if(compare(l.elem[i],e))
			return i+1;
	return ERROR;
}

//返回当前节点的前驱
void PriorElem(Sqlist l,ElemType cur_e,ElemType &pre_e)
{
	if(l.elem[0]!=cur_e)
	{
		for(int i=0;i<l.length;i++)
			if(l.elem[i]==cur_e)
				pre_e=l.elem[i-1];

	}
	else 
		pre_e=NULL;
}

//返回当前节点的后驱
void NextElem(Sqlist l,ElemType cur_e,ElemType &next_e)
{
	if(cur_e!=l.elem[l.length-1])
		for(int i=0;i<l.length;i++)
			if(cur_e==l.elem[i])
				next_e=l.elem[i+1];
	else
		next_e=NULL;

}

//在线性表当中插入一个数据
int ListInsert(Sqlist &l,int i,ElemType e)
{
	ElemType *p;
	if(i<1||i>l.length+1)
		return ERROR;
	//当线性表不为空的时候，往里面插入出现错误
//	else
//	{
//		for(int j=l.length;j>=i;j--)
//			l.elem[j]=l.elem[j-1];
//		l.elem[i-1]=e;	
//	}

	//如果内存满了，就重新申请内存;
	if(l.length>=l.size){
		 p=(ElemType*)realloc(l.elem,(l.size+lr)*sizeof(ElemType));
	}

	//
	if(!p) exit(ERROR);//申请内存失败

	l.elem=p;//新地址
	l.size+=lr;

	for(int j=l.length;j>i;j--)
		l.elem[j]=l.elem[j-1];

	l.elem[i-1]=e;

	l.length++;

	return OK;

}





//删除线性表当中的元素
void Listdelete(Sqlist &l,int i,ElemType &e)
{
	//先将所需要的值赋值给e，然后在线性表当中删除该值
	e=l.elem[i-1];
	for(int k=i-1;k<l.length;k++)
		l.elem[k]=l.elem[k+1];

	l.length--;		
}

int main()
{
	Sqlist l;
	int s=0;
	ElemType e=3;
	ElemType e1=2;

	
	InitList(l);

	//判断线性表是否为空
	if(ListEmpty(l)==2)
	ListInsert(l,0,e);
	ListInsert(l,1,e1);
	//创建一个线性表
	for(int i=0;i<6;i++)
		ListInsert(l,2,i+1);

    
	//printf("%d \n",l.elem[0]);
	return 0;
}