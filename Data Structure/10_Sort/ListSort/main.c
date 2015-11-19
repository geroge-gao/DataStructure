#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
#define OK 1
#define ERROR 0

typedef int KeyType;
typedef int InfoType;
typedef int Status;

typedef struct{
    KeyType key;//关键字项
    InfoType otherinfo;//其他数据项
}RedType;

typedef struct{
    RedType rc;//记录项
    int   next;//指针项
}SLNode;       //表节点项

typedef struct{
    SLNode r[SIZE];    //0号元素作为表头节点
    int     length;    //链表当前长度
}SLinkListType;        //静态链表类型

Status CreateSLT(SLinkListType &SL,int N)
{
    SL.length=N;
    printf("请输入要排序序列:");
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&SL.r[i].rc.key);
        SL.r[i].next=0;
    }
    SL.r[0].next=0;
    SL.r[0].rc.key=INT_MAX;//将零号元素赋值为最大值
    return OK;
}

void Link_Sort(SLinkListType& SL)
{
    //将第一个节点加入循环链表当中
    int p,q;
    SL.r[0].next=1;
    SL.r[1].next=0;
    for(int i=2;i<=SL.length;i++)
    {
        p=SL.r[0].next;
        while(p)
        {
            q=p;
            if(SL.r[p].rc.key < SL.r[i].rc.key)
            {
                q = p;
                p = SL.r[p].next;
            }
            else if(SL.r[p].rc.key>=SL.r[i].rc.key)
            {
                SL.r[i].next=p;
                SL.r[q].next=q;
            }
        }
    }
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
