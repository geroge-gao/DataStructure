#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define OK 1
#define ERROR 0

typedef int Status;
typedef int KeyType;
typedef char InfoType;

typedef struct{
    KeyType key;
    InfoType otherinfo;
}RcdType;

typedef struct{
    RcdType   rc;//记录项
    int     next;//指针项
}SLNode;

typedef struct{
    SLNode r[SIZE];//0号元素为表头节点
    int length;
}SLinkListType;

void TowInsertSort(SLinkListType &L)
{

}

int main()
{
    printf("Hello world!\n");
    return 0;
}

