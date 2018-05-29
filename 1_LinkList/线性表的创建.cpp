#include<iostream>
using namespace std;

#define LIST_INIT_SIZE 100//���Ա�洢�ռ�ĳ�ʼ����ֵ
#define lr 10//���Ա�洢�ռ�ķ�������
#define OK 1
#define ERROR 0

//����Ԫ�ص�����
typedef int ElemType;

typedef struct{
  ElemType *elem;
  int length;//��ǰ�ĳ���
  int size;//��ǰ����洢����

} Sqlist;

//����һ�����Ա�
int InitList(Sqlist &l)
{
	//Ϊ���Ա�����100���洢�ռ�
	l.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!l.elem)
	{
		exit(0);
	}

	l.length=0;//��ǰ�����е�Ԫ��Ϊ��
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

//������Ա�
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

//�������Ա�ǰ�ĳ���
int ListLenght(Sqlist l)
{
	return l.length;
}

//�õ����Ա��еĵ�I��Ԫ��
void GetElem(Sqlist l,int i,ElemType &e)
{
	e=l.elem[i-1];
}

//�ж�e�Ƿ������Ա��У�������λ�÷��ػ���
//int LocateElem(Sqlist l,ElemType e,Status (*compare)(ElemType e1,ElemType e2))
int LocateElem(Sqlist l,ElemType e)
{
	for(int i=0;i<l.length;i++)
		if(compare(l.elem[i],e))
			return i+1;
	return ERROR;
}

//���ص�ǰ�ڵ��ǰ��
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

//���ص�ǰ�ڵ�ĺ���
void NextElem(Sqlist l,ElemType cur_e,ElemType &next_e)
{
	if(cur_e!=l.elem[l.length-1])
		for(int i=0;i<l.length;i++)
			if(cur_e==l.elem[i])
				next_e=l.elem[i+1];
	else
		next_e=NULL;

}

//�����Ա��в���һ������
int ListInsert(Sqlist &l,int i,ElemType e)
{
	ElemType *p;
	if(i<1||i>l.length+1)
		return ERROR;
	//�����Ա�Ϊ�յ�ʱ�������������ִ���
//	else
//	{
//		for(int j=l.length;j>=i;j--)
//			l.elem[j]=l.elem[j-1];
//		l.elem[i-1]=e;	
//	}

	//����ڴ����ˣ������������ڴ�;
	if(l.length>=l.size){
		 p=(ElemType*)realloc(l.elem,(l.size+lr)*sizeof(ElemType));
	}

	//
	if(!p) exit(ERROR);//�����ڴ�ʧ��

	l.elem=p;//�µ�ַ
	l.size+=lr;

	for(int j=l.length;j>i;j--)
		l.elem[j]=l.elem[j-1];

	l.elem[i-1]=e;

	l.length++;

	return OK;

}





//ɾ�����Ա��е�Ԫ��
void Listdelete(Sqlist &l,int i,ElemType &e)
{
	//�Ƚ�����Ҫ��ֵ��ֵ��e��Ȼ�������Ա���ɾ����ֵ
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

	//�ж����Ա��Ƿ�Ϊ��
	if(ListEmpty(l)==2)
	ListInsert(l,0,e);
	ListInsert(l,1,e1);
	//����һ�����Ա�
	for(int i=0;i<6;i++)
		ListInsert(l,2,i+1);

    
	//printf("%d \n",l.elem[0]);
	return 0;
}