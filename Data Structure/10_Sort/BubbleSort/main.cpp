#include <iostream>
using namespace std;

void BubbleSort(int a[], int N)
{
    int t;

    for(int i = 0; i < N - 1; i++)
    {
        for(int j = 0; j < N - i; j++)
            if(a[j] > a[j + 1])
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }

        printf("第%d趟排序后:", i + 1);

        for(int j = 0; j < N; j++)
        {
            printf("%d ", a[j]);
        }

        printf("\n");
    }
}

int main()
{
    int N;
    int a[20];
    printf("输入元素个数:");
    scanf("%d", &N);

    for(int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }

    BubbleSort(a, N);
    return 0;
}
