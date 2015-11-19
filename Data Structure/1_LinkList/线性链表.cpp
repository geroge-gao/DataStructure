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

//创建一个链表
int CreateList(LinkList &l,int n)
{
	l=(LinkList)malloc(sizeof(LNode));//创建头结点
	l->data=0;
	l->next=NULL;//用于存放链表的长度
	if(l==NULL)return ERROR;
	

	printf("输入数据:");
	for(int i=0;i<n;i++)
	{
		//创建一个结点
		LinkList p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
	
		p->next=l->next;//按照堆的方式排列起来
		l->next=p;
		l->data++;//链表的节点数+1

	}
	return OK;
}

//链表的查询
int GetElem(LinkList l,int i,ElemType &e)
{
	if(i<1||i>l->data)
	{
		printf("n的数据输入不合法!\n");
		return ERROR;
	}
	else
	{
		LinkList  p=l->next;//p为首元结点
		int j=1;
		//防止i大于链表的长度
		while(p&&j<i)
		{
			p=p->next;
			j++;
		}

		e=p->data;
	}
	return OK;
}

//链表的插入数据
int ListInsert(LinkList &l,int i,ElemType e)
{
	if(i<1||i>l->data)
	{   
		printf("输入的i的数据不合法!\n");
		return ERROR;
	}
	else
	{
		int j=1;
		LinkList p=(LinkList)malloc(sizeof(LNode));//将e建立成一个节点
		p->data=e;
		LinkList m=l->next;//获取链表的首元结点
		while(m&&j<i-1)//将数据
		{
			m=m->next;
			j++;
		}
		p->next=m->next;
		m->next=p;
		l->data++;//插入后头结点的数值+1'
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
	//当链表里面只有一个元素的时候
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

//删除第i个元素,并将其值用e返回

void deleteList(LinkList &l,int i,ElemType &e)
{
		if(i<1||i>l->data)
			printf("输入的i的数据不合法!\n");
		LinkList p=l->next;
		GetElem(l,i,e);
		int a;
		GetElem(l,i-1,a);
		while(p->next!=NULL)//找到第i位元素前面的一位
		{
			if(a==p->data)
				break;
			p=p->next;
		}
		p->next=p->next->next;
		l->data--;
	
}

//合并链表
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
				pb=pb->next;//在该处出现了问题
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
//  	if(CreateList(l,n))printf("线性表创建成功!\n");
//	else printf("线性表创建失败!\n");

//	LinkList p=l->next;

//	for(;p!=NULL;p=p->next)
//	{
//		printf("%d ",p->data);
//	}
//	printf("\n");

//	printf("输入查询的位数:");
//	int m;
//	ElemType e;
//	scanf("%d",&m);
//	if(GetElem(l,m,e))
//		printf("%d\n",e);

//	scanf("%d%d",&m,&n);
//	if(ListInsert(l,m,n))printf("插入数据成功!\n");
//	
//	for( p=l->next;p!=NULL;p=p->next)
//		printf("%d ",p->data);
//	printf("\n");

//	printf("请问想删除第几位数:");
//	scanf("%d",&n);
//	int m;
//	deleteList(l,n,m);
//	printf("被删除的数为%d\n",m);

//	for( p=l->next;p!=NULL;p=p->next)
//		printf("%d ",p->data);
//	printf("\n");

	LinkList la,lb;

	int m,n;
	printf("请输入链表la的值:");
	scanf("%d",&m);
	CreateList(la,m);

	for(LinkList p=la->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");


	//输出

	printf("请输入链表lb:");
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