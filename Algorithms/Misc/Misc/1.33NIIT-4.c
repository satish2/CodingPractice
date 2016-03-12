#include<stdio.h>
int main()
{
	char a[20];
	int i=0;
	char temp;
	int max,min;
	
	while(i<25)
	{
		scanf("%c",&a[i]);
	   max=a[0];
	   min=a[0];
	   if(a[i]>max)
	   {
		   temp=max;
		   max=a[i];
		   a[i]=temp;
		}   
		if(a[i]<min)
		{
			temp=min;
		   min=a[i];
		   a[i]=temp;
		}  
	   i=i+1;
	}
	printf("%c is greatest",max);
	printf("\n %c is least",min);
	return 0;
}	