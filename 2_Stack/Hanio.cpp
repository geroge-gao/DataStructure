#include<iostream>
using namespace std;

int c=0;     

void move(char x,int n,char y)
{
	printf("%d Move disk %d from %c to %c\n",++c,n,x,y);
}
void hanio(int n,char x,char y,char z)
{
	if(n==1)
		move(x,1,z);
	else
	{
		hanio(n-1,x,z,y);
		move(x,n,z);
		hanio(n-1,y,x,z);
	}
}
int main()
{
	char a='x';
	char b='y';
	char c='z';
	int n;
	printf("要搬动的汉诺塔层数:");
	scanf("%d",&n);

	hanio(n,a,b,c);
	return 0;
}