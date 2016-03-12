#include<stdio.h>
int main()
{
	int n,size;
	printf("enter size of string");
	scanf("%d",&n);
	char c[n];
	size=n;
	printf("\n enter of string \t");
	scanf("%s",c);
	for(int i=0;i<size;i++)
	{printf("%c",c[n-1]);
	n--;}
	return 0;
}