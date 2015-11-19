#include<iostream>
#include<cstring>
using namespace std;
#define OK 1
#define ERROR 0
#define SSIZE 100
#define Status int
#define OVERFLOW 0

typedef struct{
	char *ch;//若为空串，按长度分配
	int length;
}HString;

void StrInit(HString &S);
Status StrAssign(HString &T,char *chars);
int StrLength(HString S);
int StrCompare(HString S,HString T);
Status ClearString(HString &S);
Status Concat(HString &S,HString S1,HString S2);
HString SubString(HString S,int pos,int length);
void StrPrint(HString S);

int main()
{
	int n;
	char a[100]="abc",b[100]="bcd";
	HString S,T,SS;
	StrInit(S);
	StrInit(T);
	StrInit(SS);
	StrAssign(S,a);
	StrAssign(T,b);
	n=StrCompare(S,T);
	if(n>0)
		printf("S>H\n");
	else if(n==0)
		printf("S=H\n");
	else
		printf("S<H\n");
	//连接操作
	if(Concat(SS,S,T))
		StrPrint(SS);
	else
		printf("连接失败!\n");

	HString V;
	V=SubString(SS,1,3);
	StrPrint(V);
	return 0;
}

void StrInit(HString &S)
{
	S.ch=NULL;
	S.length=0;
}

Status StrAssign(HString &T,char *chars)
{
	int n;
	n=strlen(chars);
	if(T.ch)free(T.ch);
	if(n==0)
	{
		T.ch=NULL;
		T.length=0;
	}
	else
	{
		T.ch=(char*)malloc(n*sizeof(char));
		if(!T.ch)exit(ERROR);
		for(int i=0;i<n;i++)
			T.ch[i]=chars[i];
		T.length=n;
	}
	return OK;
}

int StrLength(HString S)
{
	return S.length;
}

int StrCompare(HString S,HString T)
{
//	if(strcmp(S,T)>0)   //这种方法不行，因为字符串结尾没有终结符，所以不能够比较
//		return 1;
//	else if(strcmp(S,T)==0)
//		return 0;
//	else
//		return -1;

	for(int i=0;i<S.length&&i<T.length;i++)
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	return S.length-T.length;
}

Status ClearString(HString &S)
{
	if(S.ch)
	{
		free(S.ch);
		S.ch=NULL;
	}
	S.length=0;
	return OK;
}

Status Concat(HString &S,HString S1,HString S2)
{
	int i;
	if(S.ch)free(S.ch);
	S.ch=(char*)malloc((S1.length+S2.length)*sizeof(char));
	if(!S.ch)return ERROR;//申请内存失败;
	S.length=S1.length+S1.length;
	for(i=0;i<S1.length;i++)
		S.ch[i]=S1.ch[i];	
	for(i=0;i<S2.length;i++)
		S.ch[i+S1.length]=S2.ch[i];
	return OK;
}

HString SubString(HString S,int pos,int length)
{
	HString T;
	StrInit(T);
	T.ch=(char*)malloc(length*sizeof(char));
	if(pos+length+1>S.length)exit(0);
	for(int i=pos;i<pos+length;i++)
		T.ch[i-pos]=S.ch[i];
	T.length=length;
	return T;
		
}
void StrPrint(HString S)
{
	for(int i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

