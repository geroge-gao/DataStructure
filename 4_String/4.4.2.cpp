#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define Boolean int
#define MaxBookNum 1000    //����ֻ��1000������������
#define MaxKeyNum  2500    //��������������
#define MaxLineLen  500    //��Ŀ������󳤶�
#define MaxWordNum  10     //�ʱ���������

#define Status int

typedef struct{
	char *ch;
	int length;
}HString;

typedef struct{
	char  *item[100];   //�ַ�������
	int   last;        //�ʱ�ĳ���
}WordListType;     //�������������Ԫ�����ͺ�����

typedef int ElemType;

typedef struct List{
	HString  bno;
	List *next;
}List,*LinkList;

typedef struct{
	HString    Key;//�ؼ���
	LinkList   bnolist;//����������������
}IdxTermType;//����������

typedef struct{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxListType;   //����������

char *buf;              //��Ŀ��������
WordListType wdlist;    //�ʱ�,��������Ĺؼ���
int count=1;            //��¼�ؼ��ֵ�����
HString bno;

//���Ļ�������
Status StrInit(HString &S);
Status StrAssign(HString &S,char *chars);
int StrLength(HString &S);
int StrCompare(HString S,HString T);
void Concat(HString &S,HString T);
void StrCopy(HString &S,HString T);
Status StrInsert(HString &S,int pos,int T);
Status StrDelete(HString &S,int pos,int length);

void StrPrint(HString S);

//����Ļ�������
void InitList(LinkList &list);
Status Add(LinkList &list,HString bno);
void Delete(LinkList &list,HString bno);

//��wd���شʱ�wdlist�е�i���ؼ���
void GetWord(int i,HString &wd);
//����������������ؼ�����ͬ��λ�ã�����У�b
int Locate(IdxListType &idxlist,HString wd,Boolean &b);
//��������idxlist�ĵ�i�����ؼ���wd�����ҳ�ʼ��������л�������
void InsertNewKey(IdxListType &idxlist,int i,HString wd);
//��������idxlist��i����� bno��Ϊ����
Status InsertBook(IdxListType &idxlist,int i,ElemType bno);
//�жϵ�ǰ�ؼ����Ƿ��Ѵ���
Status Exists(char *s);


//��ʼ��������
void InitIdxList(IdxListType &idxlist);
//��buf����ȡ��Ŀ�Ĺؼ��֣����ʱ�wdlist����Ŵ���bno
void ExtractKeyWord();
//���ļ��ж�ȡһ����Ŀ��Ϣ����Ŀ������buf;
void GetLine(IdxListType &idxlist);
//�����ɵ�������idxlist������ļ�g
void PutText(IdxListType &idxlist,char *t);
//�����bno�������ؼ��ְ��ʵ��˳�����������
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

//����Ļ�������
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


void GetWord(int i,HString &wd)//��0����Ϊ��
{
	char *p;
	p=*(wdlist.item+i);
	StrAssign(wd,p);//���ɹؼ����ַ���
}

int Locate(IdxListType idxlist,HString wd,Boolean &b)
{
	for(int i=1;i<=idxlist.last;i++)
		if(StrCompare(idxlist.item[i].Key,wd)==0)
		{
			b=TRUE;
			return i;
		}
	return FALSE;//û�иĹؼ�
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


//��������Ļ�������
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
	if(n)//����Ѿ�����
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
	//��������
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






