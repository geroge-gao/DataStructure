#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

#define OK 1
#define ERROR 0
#define Status int

typedef struct
{
    char * ch; //若为空串，按长度分配
    int length;
} HString;

//广义线性表的定义

typedef HString AtomType;

typedef enum {ATOM, LIST} ElemTag; //ATOM==0:原子,LIST==1:子表
typedef struct GLNode
{
    ElemTag   tag;//公共部分,用于区分原子节点和表结点
    union
    {
        AtomType atom;//原子节点的值域
        struct
        {
            GLNode * hp; //指向表头元素
            GLNode * tp; //指向下一元素
        } ptr;
    };
} * GList;

void StrInit(HString & S);
Status StrAssign(HString & T, char * chars);
int StrLength(HString S);
int StrCompare(HString S, HString T);
Status StrCopy(HString & S, HString T);
Status ClearString(HString & S);
Status Concat(HString & S, HString S1, HString S2);
int StrEmpty(HString S);
Status SubString(HString S, int pos, int length);
void StrPrint(HString S);
Status server(HString & str, HString & hstr);

Status InitGList(GList & L);
Status CreateGList(GList & L, HString S);
void DestoryGList(GList & L);
Status CopyGList(GList & T, GList L);
int GListDepth(GList L);
int GListLength(GList L);
Status GListEmpty(GList L);
Status GetHead(GList L, GList & e);
Status GetTail(GList L, GList & e);
Status InsertFirst_GL(GList & L, AtomType & e);
void DeleteFirst_GL(GList & L, AtomType & e);
void Traverse_GL(GList L);


int main()
{
    HString S;
    GList L;
    StrInit(S);
    StrAssign(S, "((),(e),(a,(b,c,d)))");
    StrPrint(S);
    CreateGList(L, S);
    cout << "深度" << GListDepth(L) << endl;
    cout << "长度:" << GListLength(L) << endl;
    Traverse_GL(L);
    cout<<endl;
    return 0;
}


void StrInit(HString & S)
{
    S.ch = NULL;
    S.length = 0;
}

Status StrAssign(HString & T, char * chars)
{
    int n;
    n = strlen(chars);

    if(T.ch)
    {
        free(T.ch);
    }

    if(n == 0)
    {
        T.ch = NULL;
    }
    else
    {
        T.ch = (char *)malloc((n + 1) * sizeof(char));

        if(!T.ch)
        {
            exit(ERROR);
        }

        for(int i = 0; i < n; i++)
        {
            T.ch[i] = chars[i];
        }

        T.ch[n] = '\0';
        T.length = n;

    }

    return OK;
}

int StrLength(HString S)
{
    return S.length;
}

int StrCompare(HString S, HString T)
{
//  if(strcmp(S,T)>0)   //这种方法不行，因为字符串结尾没有终结符，所以不能够比较
//      return 1;
//  else if(strcmp(S,T)==0)
//      return 0;
//  else
//      return -1;

    for(int i = 0; i < S.length && i < T.length; i++)
        if(S.ch[i] != T.ch[i])
        {
            return S.ch[i] - T.ch[i];
        }

    return S.length - T.length;
}

Status StrCopy(HString & S, HString T)
{
    StrInit(S);
    S.ch = (char *)malloc(T.length * sizeof(char));

    if(!S.ch)
    {
        return ERROR;
    }

    S.length = T.length;

    for(int i = 0; i < T.length; i++)
    {
        S.ch[i] = T.ch[i];
    }

    S.ch[S.length] = '\0';
    return OK;
}

Status ClearString(HString & S)
{
    if(S.ch)
    {
        free(S.ch);
        S.ch = NULL;
    }

    S.length = 0;
    return OK;
}

Status Concat(HString & S, HString S1, HString S2)
{
    int i;

    if(S.ch)
    {
        free(S.ch);
    }

    S.ch = (char *)malloc((S1.length + S2.length) * sizeof(char));

    if(!S.ch)
    {
        return ERROR;    //申请内存失败;
    }

    S.length = S1.length + S1.length;

    for(i = 0; i < S1.length; i++)
    {
        S.ch[i] = S1.ch[i];
    }

    for(i = 0; i < S2.length; i++)
    {
        S.ch[i + S1.length] = S2.ch[i];
    }

    return OK;
}

int StrEmpty(HString S)
{
    if(S.length == 0)
    {
        return OK;
    }

    return 0;
}

Status SubString(HString & T, HString S, int pos, int length)
{
    StrInit(T);
    T.ch = (char *)malloc((length + 1) * sizeof(char));
    int t = pos + length;

    if(t > S.length)
    {
        exit(0);
    }

    for(int i = pos; i < pos + length; i++)
    {
        T.ch[i - pos] = S.ch[i];
    }

    T.length = length;
    T.ch[length] = '\0';
    return OK;
}

void StrPrint(HString S)
{
    for(int i = 0; i < S.length; i++)
    {
        printf("%c", S.ch[i]);
    }

    printf("\n");
}

Status server(HString & str, HString & hstr)
{
    int i = 0, k = 0, n = str.length;
    HString ch;

    do
    {
        SubString(ch, str, i, 1);

        if(ch.ch[0] == '(')
        {
            k++;
        }
        else
            if(ch.ch[0] == ')')
            {
                k--;
            }

        i++;
    }
    while(i < n && (ch.ch[0] != ',' || k != 0));

    if(i < n)
    {
        SubString(hstr, str, 0, i - 1);
        SubString(str, str, i, n - i);
    }
    else
    {
        StrCopy(hstr, str);
        ClearString(str);
    }

    return OK;
}

Status InitGList(GList & L)
{
    L->tag = ATOM;
    StrInit(L->atom);
    L->ptr.hp = NULL;
    L->ptr.tp = NULL;
    return OK;
}

Status CreateGList(GList & L, HString S)
{
    HString emp, sub, hsub, temp;
    GLNode * p, *q;
    StrInit(emp);
    StrInit(hsub);
    StrInit(temp);
    StrAssign(emp, "()");

    if(StrCompare(S, emp) == 0)
    {
        L = NULL;
    }
    else
    {
        L = (GLNode *)malloc(sizeof(GLNode));

        if(!L)
        {
            exit(0);
        }

        if(S.length == 1)
        {
            L->atom = S;
            L->tag = ATOM;
        }
        else
        {
            L->tag = LIST;
            p = L;
            SubString(sub, S, 1, S.length - 2);

            do
            {
                server(sub, hsub); //将表以逗号分隔开
                CreateGList(p->ptr.hp, hsub);
                q = p;

                if(!StrEmpty(sub))
                {
                    p = (GLNode *)malloc(sizeof(GLNode));
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
            }
            while(!StrEmpty(sub)); //表尾不为空

            q->ptr.tp = NULL;
        }
    }

    return OK;
}

void DestoryGList(GList & L)
{
    GList p, q, temp;

    if(L)
    {
        p = L->ptr.hp;
        q = L->ptr.tp;
        free(L);
        L = NULL;
    }

    DestoryGList(p);
    DestoryGList(q);
}

Status CopyGList(GList & T, GList L) //类似二叉树的遍历
{
    if(!L)
    {
        T = NULL;
    }
    else
    {
        T = (GLNode *)malloc(sizeof(GLNode));

        if(!T)
        {
            exit(0);
        }

        T->tag = L->tag;

        if(L->tag == ATOM)
        {
            T->atom = L->atom;
        }

        CopyGList(T->ptr.hp, L->ptr.hp);
        CopyGList(T->ptr.tp, L->ptr.tp);
    }

    return OK;
}

int GListDepth(GList L)
{
    int dep;
    int max = 0;
    GLNode * p;

    if(!L)
    {
        return 1;    //空表深度为1
    }

    if(L->tag == ATOM)
    {
        return 0;    //原子深度为0
    }

    for(max = 0, p = L; p; p = p->ptr.tp)
    {
        dep = GListDepth(p->ptr.hp);

        if(dep > max)
        {
            max = dep;
        }
    }

    return max + 1;
}

int GListLength(GList L)
{
    GLNode * p;
    int length = 0;

    for(p = L; p; p = p->ptr.tp)
    {
        length++;
    }

    return length;
}

Status GListEmpty(GList L)
{
    if(L)
    {
        return 0;
    }

    return 1;
}

Status GetHead(GList L, GList & e)
{
    if(GListEmpty(L))
    {
        e = NULL;
    }
    else
    {
        CopyGList(e, L->ptr.hp);
    }

    return OK;
}

Status GetTail(GList L, GList & e)
{
    GLNode * p;

    if(GListEmpty(L))
    {
        e = NULL;
    }
    else
    {
        p = L;

        while(p->ptr.tp)
        {
            p = p->ptr.tp;
        }

        CopyGList(e, p);
    }

    return OK;

}

Status InsertFirst_GL(GList & L, AtomType e)
{
    GLNode * p,*q;
    p=(GLNode*)malloc(sizeof(GLNode));
    if(!p)return ERROR;
    p->tag=LIST;
    p->ptr.tp=L;
    L=p;
    p->ptr.hp=(GLNode*)malloc(sizeof(GLNode));
    if(!p->ptr.hp)return ERROR;
    p->tag=ATOM;
    p->atom=e;
    return OK;
}

void Visit(AtomType e)
{
    StrPrint(e);
}

void Traverse_GL(GList L)
{
    GLNode *p,*q;
    if(L->tag==ATOM)
        Visit(L->atom);
    else
    {
        p=L->ptr.hp;
        q=L->ptr.tp;
        if(p)
            Traverse_GL(p);
        if(q)
            Traverse_GL(q);
    }
}











