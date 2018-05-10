#include<stdio.h>
#include<stdlib.h>

#define m 3
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef  int Status;
typedef int KeyType;

int  Min =m/2+m%2;

typedef struct BTNode{
    int keynum;
    struct BTNode *parent;//父节点
    KeyType key[m+1];//关键字
    struct BTNode *ptr[m+1];//孩子节点
}BTNode,*BTree;

typedef struct{
    BTNode *pt;//指向找到的结点
    int i;//关键字序号
    int tag;//1:查找成功;2:查找失败
}Result;

Status InitBTree(BTree &bt);
int Search(BTree bt,KeyType K);
Result& SearchBTree(BTree T,KeyType K);
Status Insert(BTree &p,int i,KeyType K,BTree ap);
Status split(BTree &p,int s,BTree &ap);
Status NewRoot(BTree &T,BTree &q,KeyType K,BTree &ap);
Status InsertBTree(BTree &T,KeyType K,BTree q,int i);
Status CreateBTree(BTree &bt,KeyType *a,int N);
void Successor(BTree &p,int i,BTree &q);//
void Remove(BTree &p,int i);
void Restore(BTree &p,int i);
void MoveRight(BTree &p,int i);
void MoveLeft(BTree &p,int i);
void Combine(BTree &p,int i);
int RecDelete(BTree &p,KeyType K);
void DeleteBTree(BTree &p,KeyType K);
void PrintBTree(BTree);

int main()
{
    int N,a[20];
    BTree bt=NULL;
	KeyType K;
	Result r;
    printf("元素个数:");
    scanf("%d",&N);
    printf("输入元素序列:");
    for(int i=0;i<N;i++)
        scanf("%d",&a[i]);
    CreateBTree(bt,a,N);
	PrintBTree(bt);
	printf("输入删除关键字:");
	scanf("%d",&K);
	DeleteBTree(bt,K);
	PrintBTree(bt);

    return 0;
}

Status InitBTree(BTree &bt)
{
    bt->keynum=0;
    for(int i=0;i<=m;i++)
    {
        bt->key[i]=0;
        bt->ptr[i]=NULL;
    }
    bt->parent=NULL;
	return OK;
}

int Search(BTree bt,KeyType K)
{
	if(K<bt->key[1])
		return 0;
	if(K>=bt->key[bt->keynum])
		return bt->keynum;
    for(int i=1;i<=bt->keynum-1;i++)
        if(bt->key[i]<=K&&bt->key[i+1]>K)
			return i;
	if(bt->keynum==0)
		return 0;
}

Result& SearchBTree(BTree T,KeyType K)
{
    BTree p=T,q=NULL;
    Result result;
    int i=0,found=FALSE;
    while(p&&!found)
    {
        i=Search(p,K);
        if(i>0&&p->key[i]==K)
            found=TRUE;
        else
        {
            q=p;
            p=p->ptr[i];
        }
    }

    result.i=i;
    if(found==TRUE)
    {
        result.pt=p;
        result.tag=1;
    }else
    {
        result.pt=q;
        result.tag=0;
    }
    return result;
}

Status Insert(BTree &p,int i,KeyType K,BTree ap)
{
	if(i==p->keynum)
	{
		p->key[i+1]=K;
		p->ptr[i+1]=ap;
		if(ap)
			ap->parent=p;
		p->keynum++;
	}
	else
	{
		p->keynum++;
		for(int t=p->keynum;t>=i+2;t--)
		{
			p->key[t]=p->key[t-1];
			p->ptr[t]=p->ptr[t-1];
		}
		p->key[i+1]=K;
		p->ptr[i+1]=ap;
		if(ap)
			ap->parent=p;
	}

    return OK;
}

Status split(BTree &p,int s,BTree &ap)
{
    int t=0;
    ap=(BTree)malloc(sizeof(BTNode));
    if(!ap)
    {
        printf("malloc error");
        return ERROR;
    }
    InitBTree(ap);
    for(int i = s + 1; i <= p->keynum; i++)
    {
        ap->key[i - s] = p->key[i];
        ap->ptr[i - s] = p->ptr[i];
		if(ap->ptr[i-s])
			ap->ptr[i-s]->parent=ap;
    }
	ap->ptr[0]=p->ptr[s];
	if(ap->ptr[0])
		ap->ptr[0]->parent=ap;
	ap->keynum=p->keynum-s;
    //初始化前面的一段内容
	for(int j=s;j<=p->keynum;j++)
	{
		p->key[j]=0;
		p->ptr[j]=NULL;
	}	
	p->keynum=s-1;
    return OK;
}

Status NewRoot(BTree &T,BTree &q,KeyType K, BTree &ap)
{
    int s,i;
    if(!T)//当根节点为空的之后
    {
        T=(BTree)malloc(sizeof(BTNode));
        if(!T)return ERROR;
        InitBTree(T);
        T->key[1]=K;
		T->keynum++;
    }
    else//返回到最上面的顶点
    {
        s=T->keynum/2+T->keynum%2;
		q=(BTree)malloc(sizeof(BTNode));
		if(!q)return ERROR;
		InitBTree(q);
		q->key[1]=K;
		q->ptr[0]=T;
		q->ptr[1]=ap;
		q->keynum++;
		T->parent=q;
		if(ap)
			ap->parent=q;
		T=q;
    }
    return OK;
}

Status InsertBTree(BTree &T,KeyType K,BTree q,int i)
{
    KeyType x=K;
    BTree ap=NULL;
    int finished=FALSE;
    int s;

    while(q&&!finished)
    {
        Insert(q,i,x,ap);
        if(q->keynum<m)
            finished=TRUE;
        else
        {
            s=m/2+m%2;
			x=q->key[s];
            split(q,s,ap);
            q=q->parent;
            if(q)
                i=Search(q,x);
        }
    }
    if(!finished)//分裂到最高结点，或者T为空树
        NewRoot(T,q,x,ap);
    return OK;
}

//创建一个B-Tree
Status CreateBTree(BTree &bt,KeyType *a,int N)
{
    Result result;
    for(int i=0;i<N;i++)
    {
        result=SearchBTree(bt,a[i]);
        if(!result.tag)//B-Tree中没有该节点，插入
			InsertBTree(bt,a[i],result.pt,result.i);
    }
    return OK;
}

void PrintBTree(BTree bt)
{
    if(bt)
    {
        for(int i=1;i<=bt->keynum;i++)
            printf("%d ",bt->key[i]);
        printf("\n");
        for(int t=0;t<=bt->keynum;t++)
            PrintBTree(bt->ptr[t]);
    }
}

void DeleteBTree(BTree &bt,KeyType K)
{
    BTree p;
    if(RecDelete(bt,K)==0)
        printf("关键字%d不在B-树中\n",K);
    else
    {
		printf("删除成功!\n");
		if(bt->keynum==0)
		{
			p=bt;
			bt=bt->ptr[0];
			free(p);
		}		
    }
}

int RecDelete(BTree &p,KeyType K)
{
    int i,j,found;
    BTree q,t=NULL,s;
    Result r;
	KeyType P;
    if(p==NULL)
        return 0;
    else
    {
        r=SearchBTree(p,K);
        i=r.i;
        q=r.pt;
        if(r.tag==1)//找到了该节点
        {
            if(q->ptr[i-1])//该节点为非叶子节点
            {
                Successor(q,i,t);//将该节点删除后，从q.ptr[i]中将最小的位置给他
				P=t->key[1];
				Remove(t,1);
			    if(t->keynum<Min-1)
				{
				   j=Search(t->parent,P);
                   Restore(t->parent,j);
				}
				
            }
            else
            {
                t=q->parent;
                j=Search(t,K);
                Remove(q,i);//删除叶子节点中的关键字
                if(q->keynum<Min-1)
                    Restore(t,j);
            }
        }
    }
	return r.tag;
}

void Successor(BTree &p,int i,BTree &q)
{
	BTree t;
    for(q=p->ptr[i];q!=NULL;t=q,q=q->ptr[0])
		p->key[i]=q->key[1];
	q=t;
}

void Remove(BTree &p,int i)
{
    for(int j=i;j<=p->keynum;j++)
    {
        p->key[i]=p->key[i+1];
        p->ptr[i]=p->ptr[i+1];
    }
	p->key[p->keynum]=0;
	p->ptr[p->keynum]=NULL;
    --p->keynum;
}

void Restore(BTree &p,int i)
{
    //shan删除关键字后，调整整个B-
    if(i==0)
    {
        if(p->ptr[1]->keynum>Min-1)
            MoveLeft(p,i);
        else
            Combine(p,1);
    }
    else if(i==p->keynum)
    {
        if(p->ptr[p->keynum-1]->keynum>Min-1)
            MoveRight(p,i);
        else
            Combine(p,p->keynum);
    }
    else//其他情况即为既有左子树，又有右子树
    {
        if(p->ptr[i+1]->keynum>Min-1)
            MoveLeft(p,i);
        else if(p->ptr[i-1]->keynum>Min-1)
            MoveRight(p,i);
        else
            Combine(p,i);
    }

}

void MoveRight(BTree &p,int i)
{
    BTree q;
    q=p->ptr[i];
    q->keynum++;
    for(int t=q->keynum;t>=2;t--)
    {
        q->key[t]=q->key[t-1];
        q->ptr[t]=q=q->ptr[t-1];
    }
    q->ptr[1]=q->ptr[0];
    q->key[1]=p->key[i];
    q=p->ptr[i-1];
    p->key[i]=q->key[q->keynum];
    q->key[q->keynum]=0;
    q->ptr[q->keynum]=NULL;
    q->keynum--;
}

void MoveLeft(BTree &p,int i)
{
    BTree q;
    q=p->ptr[i];
    q->keynum++;
    q->key[q->keynum]=p->key[i+1];
    q=p->ptr[i+1];
    p->key[i+1]=q->key[1];
    for(int t=1;t<=q->keynum-1;t++)
    {
        q->key[t]=q->key[t+1];
        q->ptr[t]=q->ptr[t+1];
    }
    q->key[q->keynum]=0;
    q->keynum--;
}

void Combine(BTree &p,int i)
{
	int c;
    BTree q;
    BTree l;
	q=p->ptr[i];
	l=p->ptr[i-1];
	l->keynum++;
	l->key[l->keynum]=p->key[i];
	//合并两个叶子节点
	for(c=l->keynum+1;c<=l->keynum+q->keynum;c++)
		l->key[c]=q->key[c-l->keynum];
	l->keynum+=q->keynum;
	//删除父节点中分割的关键字
	for(c=i;c<=p->keynum-1;c++)
	{
		p->key[c]=p->key[c+1];
		p->ptr[c]=p->ptr[c+1];
	}
	p->key[p->keynum]=0;
	p->ptr[p->keynum]=NULL;
	p->keynum--;
    free(q);
}
