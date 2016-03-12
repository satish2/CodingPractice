#include<stdio.h>
int main()
{
	char a[20];
	int i=0;
	while(i<20)
	{
		scanf("%c",&a[i]);
	if(a[i]>=65 && a[i]<=90)
	printf("a[%d] is upper \n",i);
	if(a[i]>=97 && a[i]<=122)
	printf("a[%d] is lower \n",i);
	if(a[i]>=48 && a[i]<=57)
	printf("a[%d] is digit \n",i);
	i=i+1;
	}
	return 0;
}	