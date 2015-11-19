#include<iostream>
using namespace std;
 
typedef struct poly_node{

	float conf;//系数
	int expn;//指数
	poly_node *next;//指向下一结点
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

void AddPolyn(poly_point la,poly_point lb)
{
	poly_point pa,pb,qa;
	qa=la;
	pa=la->next;
	pb=lb->next;
	while(pa&&pb)
	{
		if(pa->expn>pb->expn)
		{
			qa=pa;
			pa=pa->next;
		}
		else if(pa->expn==pb->expn)
		{
			int sum=pa->conf+pb->conf;
			if(sum==0)
			{
				qa->next=pa->next;
				pa=pa->next;
				pb=pb->next;
			}
			else
			{
				pa->conf=sum;
				qa=pa;
				pa=pa->next;
				pb=pb->next;

			}
		}
		else if(pa->expn<pb->expn)
		{
			pb->next=pa;
			qa->next=pb->next;
			pb=pb->next;
		}
	}
	if(pb)
		qa->next=pb;//qa至关重要，一定要有一个节点保存上一个节点
}

void PrintPolyn(poly_point la)
{
	poly_point pa;
	for(pa=la->next;pa!=NULL;pa=pa->next)
		printf("(%.2f,%d)\n",pa->conf,pa->expn);
}	


int main()
{

	poly_point la,lb;
	int m,n;
	scanf("%d",&m);
	CreatePolyn(la,m);

	scanf("%d",&n);
	CreatePolyn(lb,n);

	AddPolyn(la,lb);
	PrintPolyn(la);
	return 0;
}