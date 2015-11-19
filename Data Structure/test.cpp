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

//��ʼ������һ�����Ա�
int InitList(Sqlist &l)
{
	l.elem=(ElemType*)malloc(INIT_LIST*sizeof(ElemType));
	if(!l.elem) exit(ERROR);//�ڴ�����ʧ��
	l.length=0;//��ǰ���Ա��е�Ԫ��Ϊ0
	l.lengthsize=INIT_LIST;//��ʼ�����Ա������
	return OK;
}

//�������Ա��в�������
 ListInsert(Sqlist &l,int i,ElemType e)
{
	//�����Ա��д�����һ��Ԫ��
	if(l.length==0)
	{
		l.elem[0]=e;
		l.length++;
		return OK;
	}
	if(i<1||i>l.length+1)return ERROR;//����i��ֵ���Ϸ�

	if(l.length>=l.lengthsize){
		ElemType *a=(ElemType*)realloc(l.elem,(LIST_ADD+l.lengthsize)*sizeof(ElemType));
	
		l.elem=a;
		if(!a)exit(ERROR);//���������ڴ�ʧ��
		l.lengthsize+=LIST_ADD;//��չ���Ա������
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
	if(i<1||i>l.length)return ERROR;//�����i��ֵ���Ϸ����׳�����
	
	//����ȡ��Ҫɾ����λ�õĵ�ַ
	ElemType *p=&l.elem[i-1];
	e=*p;//���ر�ɾ������ֵ
	for(++p;p<=&(l.elem[l.length-1]);p++)
	{
		*(p-1)=*p;
	}
	l.length--;
	return OK;

}

int compare(ElemType e1,ElemType e2)//�ж�����Ԫ���Ƿ����
{
	if(e1==e2)
		return OK;
	return ERROR;
}

int LocalElem(Sqlist l,ElemType e)//����Ҫ��ѯ�����������Ա��е�λ�ã����û�з��ش���
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
		printf("i�����ݲ��Ϸ�!\n");
	//��e�����Ա��еĵ�iλ���ݷ���
	e=l.elem[i-1];
}


//������û�в���
void MergList(Sqlist la,Sqlist lb,Sqlist &lc)
{
	InitList(lc);
	int k=1,l=1,k1,l1;
	//���մ�С˳��һ�������������Ա��н�����ȡ�������������lc����
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
	
	//���ܴ���һ�����Ա��ȱ���������
	//lb�ȱ�����
	while(k<=la.length)
	{
		ListInsert(lc,lc.length,la.elem[k-1]);
		k++;
	}

	//la�ȱ�����
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
	if(InitList(la)&&InitList(lb))printf("���Ա����ɹ�!\n");

	for(i=0;i<10;i++)
		ListInsert(la,la.length,i+1);
	for(j=0;j<10;j+=2)
		ListInsert(lb,lb.length,j+2);

		//������Ա�
	for(i=0;i<la.length;i++)
		printf("%d ",la.elem[i]);
	printf("\n");
	for(i=0;i<lb.length;i++)
		printf("%d ",lb.elem[i]);
	printf("\n");

	Union(la,lb);

	printf("�ϲ�֮�����Ա�la��ֵΪ:\n");
	for(i=0;i<la.length;i++)
		printf("%d ",la.elem[i]);
	printf("\n");
	
	return 0;
}