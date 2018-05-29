#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

//huffman编码树和Huffmancode的存储结构

typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;
int temp[100];

void Select(HuffmanTree HT,int n,int &s1,int &s2)
{
    int min;

    for(int i = 1; i <= n; i++)
        if(!temp[i])
        {
            min = HT[i].weight;
            break;
        }

    for(int i = 1; i <= n; i++)
        if(HT[i].weight <= min && !temp[i])
        {
            min = HT[i].weight;
        }

    for(int i = 1; i <= n; i++)
        if(!temp[i] && HT[i].weight == min)
        {
            s1 = i;
            temp[i] = 1;
            break;

        }

    for(int i = 1; i <= n; i++) //确定一个不没有被访问的数
        if(!temp[i])
        {
            min = HT[i].weight;
            break;
        }

    for(int i = 1; i <= n; i++)
        if(!temp[i] && HT[i].weight <= min)
        {
            min = HT[i].weight;
        }

    //找到最小的数
    for(int i = 1; i <= n; i++)
        if(!temp[i]&&HT[i].weight == min)
        {
            s2 = i;
            temp[i] = 1;
            break;
        }
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
    int m,start,i,s1,s2,parent;
    char *cd;
    HuffmanTree p;
    if(n<1)exit(0);
    m=2*n-1;//m为所有结点的个数
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for(p=HT+1,i=1;i<=n;i++,p++)//初始化前面n个结点
    {
        p->lchild=0;
        p->rchild=0;
        p->weight=w[i];
        p->parent=0;
    }

    for(;i<=m;i++,p++)
    {
        p->lchild=0;
        p->rchild=0;
        p->weight=0;
        p->parent=0;
    }

    for(i=n+1;i<=m;i++)
    {
        Select(HT,i-1,s1,s2);
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }

    HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
    cd=(char*)malloc(n*sizeof(char));
    cd[n-1]='\0';
    //丛叶子结点到根逆向求每一个字符的Huffman编码
    for(i=1;i<=n;i++)
    {
        start=n-1;
        for(int c=i,parent=HT[i].parent;parent!=0;c=parent,parent=HT[c].parent)
        {
            if(HT[parent].lchild==c)
                cd[--start]='0';
            else if(HT[parent].rchild==c)
                cd[--start]='1';
        }
        HC[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
}//HuffmanCoding

void ShowCode(HuffmanTree ht,HuffmanCode hc,int n)
{
    for(int i=1;i<=n;i++)
    {
        printf("%d  %s\n",ht[i].weight,hc[i]);
    }
}


int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int *w,n;
    scanf("%d",&n);
    w=new int[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    HuffmanCoding(HT,HC,w,n);
    ShowCode(HT,HC,n);
    return 0;
}


