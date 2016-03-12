#include<stdio.h>
int main()
{
	int a,b,c;
	printf("enter base \t");
	scanf("%d",&a);
	c=a;
	printf("enter power \t");
	scanf("%d",&b);
	if(b==0)
	printf("it is 1");
	else
	{for(int i=0;i<b-1;i++)
	a=a*c;
	printf("\n %d",a);
	}
	return 0;
}