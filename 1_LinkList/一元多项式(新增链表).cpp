#include<iostream>
using namespace std;
 
typedef struct poly_node{

	float conf;//系数
	int expn;//指数
	poly_node *next;
}poly_node,*poly_point;

void CreatePolyn(poly_point &la,int n)
{
	poly_point p,pa;
	la=(poly_point)malloc(sizeof(poly_node));//注意要为首结点申请内存单元
	la->next=NULL;
	pa=la;


	for(int i=0;i<n;i++)
	{
		p=(poly_point)malloc(sizeof(poly_node));
		scanf("%f %d",&p->conf,&p->expn);
		p->next=pa->next;
		pa->next=p;
		pa=pa->next;
	}

}

void AddPolyn(poly_point la,poly_point lb,poly_point &lc)//将相加后的结果放在另一条上面
{
	poly_point pa,pb,pc;
	lc=la;
	pc=lc;
	pa=la->next;
	pb=lb->next;
	while(pa&&pb)
	{
		if(pa->expn>pb->expn)
		{
			pc->next=pa;
			pc=pc->next;
			pa=pa->next;
		}
		else if(pa->expn==pb->expn)
		{
			float sum=pa->conf+pb->conf;
			if(sum==0)//如果系数相同就将其删除
			{
				pa=pa->next;
				pb=pb->next;
			}
			else
			{
				poly_point p=(poly_point)malloc(sizeof(poly_node));
				p->expn=pa->expn;
				p->conf=sum;
				p->next=NULL;
				pc->next=p;
				pc=pc->next;
				pa=pa->next;
				pb=pb->next;
				
			}
		}
		else if(pa->expn<pb->expn)
		{
			pc->next=pb;
			pb=pb->next;
			pc=pc->next;
		}
	}

	pc->next=pa?pa:pb;//pc始终是链表当中的·最后一个
}

void PrintPolyn(poly_point la)
{
	poly_point pa;
	for(pa=la->next;pa!=NULL;pa=pa->next)
		printf("(%.2f,%d)\n",pa->conf,pa->expn);
}	

int PolynLength(poly_point p)//返回a与b的长度
{
	int length=0;
	poly_point a;
	for(a=p->next;a!=NULL;a=a->next)
		length++;
	return length;
}

void DestoryPolyn(poly_point &p)//利用遍历清空链表
{
	poly_point l;
	while(p!=NULL)
	{
		l=p->next;
		free(p);
		p=l;
	}
}
int main()
{

	poly_point la,lb,lc;
	int n,m;
	scanf("%d",&m);
	CreatePolyn(la,m);

	scanf("%d",&n);
	CreatePolyn(lb,n);
	if(la&&lb)//初始化成功!
		printf("初始化成功!\n");

	AddPolyn(la,lb,lc);

	PrintPolyn(lc);
	DestoryPolyn(lc);
	if(lc==NULL)
		printf("链表已经被清空\n");

	return 0;
}