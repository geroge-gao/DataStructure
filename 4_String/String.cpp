#include<iostream>
#include<stdio.h>
using namespace std;

#define MAXSTRLEN 255

#define TRUE 1
#define FALSE 0
#define Status int

typedef unsigned char String[MAXSTRLEN];

Status StrAssign(String &T,char *chars);//创建串
Status StrEmpty(String S);//判断串是否为空
Status StrCompare(String S,String T);//比较串
Status StrCopy(String &S,String T);//复制串
int StrLength(String S);//返回串的长度
Status Concat(String &T,String S1,String S2);//连接串
Status SubString(String &Sub,String S,int pos,int length);//替换串
int Index(String S,String T,int pos);
Status Replace(String &S,String T,String V);
Status StrInsert(String &S,int pos,String T);
Status StrDelete(String &S,int pos,int length);
void StrPrint(String S);
void DestoryString(String &S);

int main()
{
	String S;
	//测试赋值函数
	if(StrAssign(S,"abcd"))
	{
	//	printf("赋值成功\n");
		StrPrint(S);
	}
	//测试复制函数
	char t[20]="I like coding";
	String S1,T;
	StrAssign(T,t);
	if(StrCopy(S1,T))
	{
	//	printf("复制成功!\n");
		StrPrint(S1);
	}

	if(StrCompare(S,S1))
		printf("S和S1相等\n");
	else
		printf("S和S1不相等\n");

	String temp="";
	if(StrEmpty(temp))
		printf("temp为空字符串\n");
	else
		printf("temp不为空\n");
	printf("s的长度为%d\n",StrLength(S));

	String S2;
	if(Concat(S2,S,S1))
	{
		printf("连接成功  ");
		StrPrint(S2);
	}

	String s,V,ss;
	StrAssign(s,"bc");

	int pos=Index(S,s,1);
	printf("%d\n",pos);

	StrAssign(ss,"I am abcd haha ,you are a bitch");
	StrAssign(V,"heor");
	StrPrint(ss);
	if(Replace(ss,S,s))
	{
		printf("替换成功!:\n");
		StrPrint(ss);
	}

	//插入
	StrInsert(ss,2,s);
	StrPrint(ss);

	StrDelete(ss,2,2);
	StrPrint(ss);
	return 0;
}

Status StrAssign(String &T,char *chars)
{
	int m=strlen(chars);
	if(m>MAXSTRLEN)return FALSE;
	for(int i=0;i<m;i++)
		T[i+1]=chars[i];
	T[0]=m;
	return TRUE;
}

Status StrEmpty(String S)
{
	if(S[0]==0)
		return TRUE;
	return FALSE;
}

Status StrCompare(String S,String T)
{
	int i=1;
	if(S[0]==T[0])
		for(i=1;i<=S[0];i++)
			if(S[i]!=T[i])
				break;

	int n=S[0];
	if(i-1==n)
		return TRUE;
	return FALSE;
}

int StrLength(String S)
{
	return S[0];

}

Status StrCopy(String &S,String T)
{
	S[0]=T[0];
	for(int i=1;i<=S[0];i++)
		S[i]=T[i];
	return TRUE;
}

Status Concat(String &T,String S1,String S2)
{
	int uncut,i,j;
	if(S1[0]+S2[0]<=MAXSTRLEN)//如果没有截断
	{
		T[0]=S1[0]+S2[0];
		for(i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(j=1;j<=S2[0];j++)
			T[j+i-1]=S2[j];
		uncut=TRUE;
	}
	else if(S1[0]<MAXSTRLEN&&S1[0]+S2[0]>MAXSTRLEN)//部分截断
	{
		T[0]=MAXSTRLEN;
		for(i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(j=1;j+S1[0]<=MAXSTRLEN;j++)
			T[i++]=S2[j];
		uncut=FALSE;
	}
	else if(S1[0]>=MAXSTRLEN)
	{
		int i;
		T[0]=MAXSTRLEN;
		for(i=1;i<=MAXSTRLEN;i++)
			T[i]=S1[i];
		uncut=FALSE;
	}
	return uncut;
}

Status SubString(String &Sub,String S,int pos,int length)
{
	int flag=0;
	int i;
	if(length>S[0]-pos+1)return FALSE;
	Sub[0]=length;
	for(i=1;i<=length;i++)
		Sub[i]=S[i+pos-1];
	flag=1;
	return flag;
}

int Index(String S,String T,int pos)
{
	int m,n,i;
	String sub;
	if(pos>0)
	{
		n=StrLength(S);
		m=StrLength(T);
		for(i=pos;i<=n-m+1;i++)
		{
			if(SubString(sub,S,i,m))
				if(StrCompare(sub,T))
					return i;
		}

	}
	return FALSE;
}

Status Replace(String &S,String T,String V)
{
	int i,pos;
	if(S[0]<T[0]||S[0]<V[0])return FALSE;
	pos=Index(S,T,1);
	if(pos==0)
	{
		printf("替换错误!\n");
		return FALSE;
	}
	else
	{
		if(T[0]==V[0])
			for(i=pos;i<=V[0];i++)
				S[i]=V[i];
		else if(T[0]<V[0])
		{
			int length=V[0]-T[0];
			for(i=S[0];i>=pos+length-1;i--)
				S[i+length]=S[i];
			for(i=pos;i<=V[0];i++)
				S[i]=V[i];
		}
		else if(T[0]>=V[0])
		{
			int length = T[0]-V[0];
			int n=StrLength(V);
			int m=StrLength(S);
			StrPrint(V);
			for(i=pos;i<=pos+n-1;i++)
				S[i]=V[i-pos+1];
			for(;i<=m-length;i++)
				S[i]=S[i+length];
		}
	}
	return TRUE;
}

Status StrInsert(String &S,int pos,String T)
{
	int i,m,n;
	m=StrLength(T);
	n=StrLength(S);
	if(pos<=n)
	{
		for(i=n;i>=pos;i--)
			S[i+m]=S[i];
		for(i=1;i<=m;i++)
			S[pos+i-1]=T[i];
	}
	else
	{
		for(i=1;i<=m;i++)
			S[n+i]=T[i];
	}
	return TRUE;
}

Status StrDelete(String &S,int pos,int length)
{
	int m=StrLength(S);
	if(pos>m||length>m-pos+1)return FALSE;
	for(int i=pos;i<=m-length;i++)
		S[i]=S[i+length];
	return TRUE;
}

void StrPrint(String S)
{
	int n=S[0];
	for(int i=1;i<=n;i++)
		printf("%c",S[i]);
	printf("\n");
}



