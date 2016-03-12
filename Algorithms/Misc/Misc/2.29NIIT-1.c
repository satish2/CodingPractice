#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,d;
	int c=2;
	int count=0;
	printf("enter any number \n");
	scanf("%d",&a);
	for(b=0;b<=sqrt(a);b++)
	{
		 d=a%c;
		 if(d==0)
		 count++;
		 c++;
	}
	if(count == 0)
	printf("prime :) \n");	 
	else
	printf("not :( \n");
	return 0;
}	