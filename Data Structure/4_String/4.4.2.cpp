#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define Boolean int
#define MaxBookNum 1000    //假设只对1000本书做引索表
#define MaxKeyNum  2500    //引索表的最大容量
#define MaxLineLen  500    //数目串的最大长度
#define MaxWordNum  10     //词表的最大容量

#define Status int

typedef struct{
	char *ch;
	int length;
}HString;

typedef struct{
	char  *item[100];   //字符串数组
	int   last;        //词表的长度
}WordListType;     //定义链表的数据元素类型和整形

typedef int ElemType;

typedef struct List{
	HString  bno;
	List *next;
}List,*LinkList;

typedef struct{
	HString    Key;//关键词
	LinkList   bnolist;//存放书号引索的链表
}IdxTermType;//引索项类型

typedef struct{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxListType;   //引索表类型

char *buf;              //书目串缓存区
WordListType wdlist;    //词表,存放书名的关键字
int count=1;            //记录关键字的条数
HString bno;

//串的基本操作
Status StrInit(HString &S);
Status StrAssign(HString &S,char *chars);
int StrLength(HString &S);
int StrCompare(HString S,HString T);
void Concat(HString &S,HString T);
void StrCopy(HString &S,HString T);
Status StrInsert(HString &S,int pos,int T);
Status StrDelete(HString &S,int pos,int length);

void StrPrint(HString S);

//链表的基本操作
void InitList(LinkList &list);
Status Add(LinkList &list,HString bno);
void Delete(LinkList &list,HString bno);

//用wd返回词表wdlist中第i个关键字
void GetWord(int i,HString &wd);
//返回在引索表中与关键字相同的位置，如果有，b
int Locate(IdxListType &idxlist,HString wd,Boolean &b);
//在引索表idxlist的第i项插入关键词wd，并且初始化书号序列化引索链
void InsertNewKey(IdxListType &idxlist,int i,HString wd);
//在引索表idxlist第i项插入 bno作为引索
Status InsertBook(IdxListType &idxlist,int i,ElemType bno);
//判断当前关键字是否已存在
Status Exists(char *s);


//初始化引索表
void InitIdxList(IdxListType &idxlist);
//从buf中提取书目的关键字，到词表wdlist，书号存入bno
void ExtractKeyWord();
//从文件中读取一个书目信息到书目缓冲区buf;
void GetLine(IdxListType &idxlist);
//将生成的引索表idxlist输出到文件g
void PutText(IdxListType &idxlist,char *t);
//将书号bno的书名关键字按词典的顺序插入引索表
void InsIdxlist(IdxListType &idxlist,ElemType bno);
int Find(IdxListType idxlist,char *s);

int main()
{
	IdxListType idxlist;
	InitIdxList(idxlist);
	GetLine(idxlist);
	return 0;
}

Status StrInit(HString &S)
{
	if(S.ch!=NULL)
		S.ch=NULL;
	S.length=0;
	return TRUE;
}

Status StrAssign(HString &S,char *chars)
{
	int length;
	StrInit(S);
	length=strlen(chars);
	S.ch=(char*)malloc(length*sizeof(char));
	if(!S.ch)return FALSE;
	for(int i=0;i<length;i++)
		S.ch[i]=chars[i];
	S.ch[i]='\0';
	S.length=length;
	return TRUE;
}

int StrLength(HString S)
{
	return S.length;
}

Status StrCompare(HString S,HString T)
{
	for(int i=0;i<S.length&&i<T.length;i++)
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	return S.length-T.length;
}

void StrCopy(HString &S,HString T)
{
	if(S.ch)free(S.ch);
	S.ch=(char*)malloc(T.length*sizeof(char));
	for(int i=0;i<T.length;i++)
		S.ch[i]=T.ch[i];
	S.ch[i]='\0';
	S.length=T.length;
}

void Concat(HString &S,HString T)
{
	for(int i=S.length;i<S.length+T.length;i++)
		S.ch[i]=T.ch[i-S.length];
	S.length=S.length+T.length;
	S.ch[S.length]='\0';
}

Status StrInsert(HString &S,int pos,HString &T)
{
	int i;
	for(i=S.length-1;i>=pos;i--)
		S.ch[i+T.length]=S.ch[i];
	for(i=pos;i<pos+T.length;i++)
		S.ch[i]=T.ch[i-pos];
	return TRUE;
}

Status StrDelete(HString &S,int pos,int length)
{
	int lastp=pos+length;
	if(lastp+1>S.length)
		return FALSE;
	for(int i=pos+length;i<S.length;i++)
		S.ch[i-length]=S.ch[i];
	return TRUE;
}



void StrPrint(HString S)
{
	for(int i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

//链表的基本操作
void InitList(LinkList &list)
{
	StrAssign(list->bno,"");
	list->next=NULL;
}
Status Add(LinkList &list,HString bno)
{
	LinkList p;
	p=(LinkList)malloc(sizeof(List));
	if(!p)return FALSE;
	StrCopy(p->bno,bno);
	p->next=list->next;
	list->next=p;
	return TRUE;
}

void Delete(LinkList &list,HString wd)
{
	LinkList current,p;
	current=p=list->next;
	while(StrCompare(wd,p->bno)!=0)
	{
		current=p;
		p=p->next;
	}
	if(p==NULL)
		printf("Delete Error\n");
	else
	{
		if(p==list->next)
		{
			list->next=p->next;
			free(p);
		}
		else
		{
			current->next=p->next;
			free(p);
		}
		
	}
}


void GetWord(int i,HString &wd)//第0项置为空
{
	char *p;
	p=*(wdlist.item+i);
	StrAssign(wd,p);//生成关键字字符串
}

int Locate(IdxListType idxlist,HString wd,Boolean &b)
{
	for(int i=1;i<=idxlist.last;i++)
		if(StrCompare(idxlist.item[i].Key,wd)==0)
		{
			b=TRUE;
			return i;
		}
	return FALSE;//没有改关键
}

void InsertNewKey(IdxListType &idxlist,int i,HString wd)
{
	for(int j=idxlist.last;j>=i;j--)
		idxlist.item[j+1]=idxlist.item[j];
	StrCopy(idxlist.item[i].Key,wd);
	InitList(idxlist.item[i].bnolist);
	idxlist.last++;
}

Status InsertBook(IdxListType &idxlist,int i,HString bno)
{
	LinkList p;
	if(i>idxlist.last)
		return FALSE;
	p=(LinkList)malloc(sizeof(List));
	if(!p)return FALSE;
	StrCopy(p->bno,bno);
	p->next=NULL;
	Add(idxlist.item[i].bnolist,bno);
	return TRUE;
}

Status Exists(char *s)
{
	for(int i=1;i<=wdlist.last;i++)
		if(strcmp(wdlist.item[i],s)==0)
			return TRUE;
	return FALSE;
}


//对引索表的基本操作
void InitIdxList(IdxListType &idxlist)
{
	for(int i=0;i<100;i++)
	{
		idxlist.item[i].bnolist=(LinkList)malloc(sizeof(List));
		StrAssign(idxlist.item[i].bnolist->bno,"");
		idxlist.item[i].bnolist->next=NULL;
		StrAssign(idxlist.item[i].Key,"");
	}
	idxlist.last=0;
}

void PutText(IdxListType &idxlist,HString bno,char *t)
{
	int n=0;
//	n=Find(idxlist,t);
	for(int i=1;i<=idxlist.last;i++)
		if(strcmp(idxlist.item[i].Key.ch,t)==0)
			n=i;
	if(n)//如果已经存在
	{
		LinkList q=(LinkList)malloc(sizeof(List));
		if(!q)exit(0);
		StrInit(q->bno);
		StrCopy(q->bno,bno);
		q->next=idxlist.item[n].bnolist->next;
		idxlist.item[n].bnolist->next=q;
		
	}
	else
	{
		strcpy(idxlist.item[count].Key.ch,t);
		idxlist.item[count].Key.length=strlen(t);
		LinkList q=(LinkList)malloc(sizeof(List));
		if(!q)exit(0);
		StrInit(q->bno);
		StrCopy(q->bno,bno);
		q->next=idxlist.item[count].bnolist->next;
		idxlist.item[count].bnolist->next=q;
		idxlist.last++;
	}
}

void ExtExtractKeyWord(IdxListType &idxlist)
{
	int k=0,p=0,j=0;
	HString wd,bno;
	char *a,*b,*t;
	LinkList pt;
	a=(char*)malloc(100*sizeof(char));
	b=(char*)malloc(100*sizeof(char));
	int n=strlen(buf);
	for(int i=0;i<n;i++)
	{
		if(buf[i]>='0'&&buf[i]<='9')
			a[k++]=buf[i];
		else
			b[j++]=buf[i];
	}

	a[k]='\0';
	b[j]='\0';
	int length=strlen(a);
	StrInit(bno);
	StrAssign(bno,a);

	p=0;
	t=(char*)malloc(20*sizeof(char));
	if(!t)exit(0);
	for(k=0;k<j;k++)
	{
		if((b[k]>='a'&&b[k]<='z')||(b[k]>='A'&&b[k]<='Z'))
		{
			t[p++]=b[k];
			if(b[k]!=' '&&(b[k+1]==' '||b[k+1]=='\n'))
			{
				t[p]='\0';				
				if(strcmp(t,"to")&&strcmp(t,"an")&&strcmp(t,"a")&&strcmp(t,"to")&&strcmp(t,"The")&&strcmp(t,"of")&&strcmp(t,"and"))
				{
					PutText(idxlist,bno,t);
					p=0;
					if(!Exists(t))
					{
						wdlist.item[count]=(char*)malloc((p+1)*sizeof(char));
						strcpy(wdlist.item[count],t);
						wdlist.last++;
						count++;
					}
				}				
			}			
		}
		if(b[k]=' '&&b[k+1]==' ')
			p=0;
	}	
}


void GetLine(IdxListType &idxlist)
{
	FILE *f;
	int k=0,j;
	char m[100];
	f=fopen("E:\\Book.txt","r");
	buf=(char*)malloc(100*sizeof(char));
	if(!buf)exit(0);
	while(fgets(buf,100,f)!=NULL)
		ExtExtractKeyWord(idxlist);
	//保存数据
	FILE *fb;
	fb=fopen("E:\\tt.txt","w+");
	for(int i=1;i<=idxlist.last;i++)
	{
		for(j=0;j<idxlist.item[i].Key.length;j++)
			m[j]=idxlist.item[i].Key.ch[j];
		m[j++]=' ';
		LinkList p=idxlist.item[i].bnolist->next;
		while(p!=NULL)
		{
			for(k=j;k<j+p->bno.length;k++)
				m[k]=p->bno.ch[k-j];
			m[k]=' ';
			j=k+1;
			p=p->next;
		}
		m[k++]='\n';
		m[k]='\0';
		fwrite(m,sizeof(char),strlen(m),fb);
	}

}

int Find(IdxListType idxlist,char *t)
{
	for(int i=1;i<=idxlist.last;i++)
		if(strcmp(idxlist.item[i].Key.ch,t)==0)
			return i;
	return 0;
}






