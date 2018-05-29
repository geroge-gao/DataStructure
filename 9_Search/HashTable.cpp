#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define SUCCESS 1
#define UNSUCESS 0
#define DUPLICATE -1
#define NULLKEY 0//无标记符号
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)>(b))
#define LQ(a,b) ((a)<(B))
#define OK 1
#define ERROR 0

typedef int Status;
typedef int Boolean;
typedef int KeyType;

typedef struct{
    KeyType key;
    int ord;
}ElemType;

int hashsize[]={11,19,29,37};

int m=0;;//全局变量，初始化哈希表的容量值

typedef struct{
    ElemType *elem;
    int count;
    int sizeindex;
}HashTable;

Status CreateHash(HashTable &H);
void collision(int &p,int d);//线性探测再散列
int Hash(KeyType K);//哈希函数
Status SearchHashTable(HashTable H,KeyType K,int &p,int &c);
Status ReCreateHashTable(HashTable &H);
Status InsertHash(HashTable &H,ElemType e);
void TraverseHash(HashTable H);//按顺序遍历哈希表

int main()
{
   ElemType r[10]={{11,1},{1,2},{12,3},{22,4},{23,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
   HashTable h;
   int i,p;
   Status j;
   KeyType k;
   CreateHash(h);
   for(int i=0;i<10;i++)
      InsertHash(h,r[i]);
   TraverseHash(h);
   return 0;
}

Status CreateHash(HashTable &H)
{
    H.count=0;
    H.sizeindex=0;
    m=hashsize[0];
    H.elem=(ElemType*)malloc(m*sizeof(ElemType));
    if(!H.elem)
    {
        exit(0);
    }
    for(int i=0;i<m;i++)
    {
        H.elem[i].key=NULLKEY;
        H.elem[i].ord=0;
    }
    return OK;
}

int Hash(KeyType K)
{
    return K%m;
}

void collision(int &p,int d)
{
    p=(p+d)%m;
}

Status SearchHashTable(HashTable H,KeyType K,int &p,int &c)
{
    p=Hash(K);
    while(H.elem[p].key!=NULL&&!EQ(K,H.elem[p].key))
    {
        if(c<m)
            collision(p,++c);
        else
            break;
    }
    if(EQ(K,H.elem[p].key))
        return SUCCESS;
    return UNSUCESS;
}

Status InsertHash(HashTable &H,ElemType e)
{
    int c=0,p;
    if(SearchHashTable(H,e.key,p,c))
        return DUPLICATE;//表中已有重复的元素
    else if(c<hashsize[H.sizeindex]/2)//冲突次数没有冲突次数没有达到上限
    {
        H.elem[p]=e;
        H.count++;
        return OK;
    }
    else
    {
        ReCreateHashTable(H);
    }

}

Status ReCreateHashTable(HashTable &H)
{
    int i,count=H.count;
    ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
    p=elem;
    printf("重建哈希表\n");
    for(i=0;i<m;i++)
        if(H.elem[i].key!=NULLKEY)
            elem[i]=p[i]=H.elem[i];
    H.count=0;
    H.sizeindex++;
    m=hashsize[H.sizeindex];
    p=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
    if(!p)
        exit(0);
    for(int j=hashsize[H.sizeindex];j<hashsize[H.sizeindex-1];j++)
        p[j].key=NULLKEY;
    H.elem=p;
    return OK;
}

void TraverseHash(HashTable H)
{
    for(int i=0;i<m;i++)
        if(H.elem[i].key!=NULLKEY)
            printf("%d ",H.elem[i].key);
}


