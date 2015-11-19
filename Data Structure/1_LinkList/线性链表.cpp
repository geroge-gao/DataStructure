#include<iostream>
using namespace std;

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
} LNode,*LinkList;

//����һ������
int CreateList(LinkList &l,int n)
{
	l=(LinkList)malloc(sizeof(LNode));//����ͷ���
	l->data=0;
	l->next=NULL;//���ڴ������ĳ���
	if(l==NULL)return ERROR;
	

	printf("��������:");
	for(int i=0;i<n;i++)
	{
		//����һ�����
		LinkList p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
	
		p->next=l->next;//���նѵķ�ʽ��������
		l->next=p;
		l->data++;//����Ľڵ���+1

	}
	return OK;
}

//����Ĳ�ѯ
int GetElem(LinkList l,int i,ElemType &e)
{
	if(i<1||i>l->data)
	{
		printf("n���������벻�Ϸ�!\n");
		return ERROR;
	}
	else
	{
		LinkList  p=l->next;//pΪ��Ԫ���
		int j=1;
		//��ֹi��������ĳ���
		while(p&&j<i)
		{
			p=p->next;
			j++;
		}

		e=p->data;
	}
	return OK;
}

//����Ĳ�������
int ListInsert(LinkList &l,int i,ElemType e)
{
	if(i<1||i>l->data)
	{   
		printf("�����i�����ݲ��Ϸ�!\n");
		return ERROR;
	}
	else
	{
		int j=1;
		LinkList p=(LinkList)malloc(sizeof(LNode));//��e������һ���ڵ�
		p->data=e;
		LinkList m=l->next;//��ȡ�������Ԫ���
		while(m&&j<i-1)//������
		{
			m=m->next;
			j++;
		}
		p->next=m->next;
		m->next=p;
		l->data++;//�����ͷ������ֵ+1'
		return OK;
	}
}

//int ListInsert(LinkList &l,ElemType e)
//{
//	LinkList p=l->next,current=p;
//	if(l->data>1)
//	{
//		while(p->data<e)
//		{
//			current=p;
//			p=p->next;
//		}
		
//		LinkList t=(LinkList)malloc(sizeof(LNode));
//		t->data=e;
//		t->next=p;
//		current->next=t;
//		l->data++;
//		return OK;
//	}
	//����������ֻ��һ��Ԫ�ص�ʱ��
//	else if(l->data==1)
//	{
//		LinkList p=l->next;
//		if(e<=p->data)
//		{
///			LinkList t=(LinkList)malloc(sizeof(LNode));
//			t->data=e;
//			l->next=t;
//			t->next=p;
//		}
//		else if(e>p->data)
//		{
//			LinkList t=(LinkList)malloc(sizeof(LNode));
//			t->data=e;
//			p->next=t;
//		}
		
//	}
//	return OK;
//}

//ɾ����i��Ԫ��,������ֵ��e����

void deleteList(LinkList &l,int i,ElemType &e)
{
		if(i<1||i>l->data)
			printf("�����i�����ݲ��Ϸ�!\n");
		LinkList p=l->next;
		GetElem(l,i,e);
		int a;
		GetElem(l,i-1,a);
		while(p->next!=NULL)//�ҵ���iλԪ��ǰ���һλ
		{
			if(a==p->data)
				break;
			p=p->next;
		}
		p->next=p->next->next;
		l->data--;
	
}

//�ϲ�����
void MergeList(LinkList &la,LinkList lb)
{
	LinkList pa=la->next,pb=lb->next,p,current=pa;;
	LinkList head=pa;
	while(pa&&pb)
	{
		
		if(pa->data<pb->data)
		{
			current=pa;
			pa=pa->next;
			if(pa!=NULL&&pa->data>pb->data)
			{
				p=pb;
				current->next=p;
				pb=pb->next;//�ڸô�����������
				p->next=pa;
				pa=p;
				la->data++;
			}
			else if(pa->data<pb->data&&pa->next==NULL)
			{
				pa->next=pb;
				pb=pb->next;
				while(pb)
					la->data++;
			}
		}else
		{
			if(head==pa)
			{
				p=pb;
				p->next=pa;
				la->next=pa;
				pa=pa->next;
			}

		}
	}
}

int main()
{

//	LinkList l;
//	int n;
//	scanf("%d",&n);
//  	if(CreateList(l,n))printf("���Ա����ɹ�!\n");
//	else printf("���Ա���ʧ��!\n");

//	LinkList p=l->next;

//	for(;p!=NULL;p=p->next)
//	{
//		printf("%d ",p->data);
//	}
//	printf("\n");

//	printf("�����ѯ��λ��:");
//	int m;
//	ElemType e;
//	scanf("%d",&m);
//	if(GetElem(l,m,e))
//		printf("%d\n",e);

//	scanf("%d%d",&m,&n);
//	if(ListInsert(l,m,n))printf("�������ݳɹ�!\n");
//	
//	for( p=l->next;p!=NULL;p=p->next)
//		printf("%d ",p->data);
//	printf("\n");

//	printf("������ɾ���ڼ�λ��:");
//	scanf("%d",&n);
//	int m;
//	deleteList(l,n,m);
//	printf("��ɾ������Ϊ%d\n",m);

//	for( p=l->next;p!=NULL;p=p->next)
//		printf("%d ",p->data);
//	printf("\n");

	LinkList la,lb;

	int m,n;
	printf("����������la��ֵ:");
	scanf("%d",&m);
	CreateList(la,m);

	for(LinkList p=la->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");


	//���

	printf("����������lb:");
	scanf("%d",&n);
	CreateList(lb,n);

	for( p=lb->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");

	
	MergeList(la,lb);

	LinkList t=la->next;
	for(;t!=NULL;t=t->next)
		printf("%d ",t->data);
	return 0;
}