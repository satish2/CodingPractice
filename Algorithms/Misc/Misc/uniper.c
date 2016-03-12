#include<stdio.h>
#include<stdlib.h>
int permuten(int *b,int x);
void swap(int ,int);
int permuten(int *b,int x);
int *b;
int n;
void swap(int d,int c)
{
  int  temp;
  temp=b[c];
  b[c]=b[d];
  b[d]=temp;
} 

int permuten(int *b,int x)
{
 int i=x;
 int j;
 if(x<=n-2)
 {
  permuten(b,x+1);
  for(;i<n;i++)
  {
     swap(x-1,i);
     permuten(b,x+1);
     swap(x-1,i);
  } 
 }
 else
 {
       for(j=0;j<n;j++)
       {
       	printf("%d \t",b[j]);
       }
       	printf("\n");
	    	swap(n-2,n-1);
       for(j=0;j<n;j++)
       {
       	printf("%d \t",b[j]);
       }
       	swap(n-2,n-1);
       printf("\n");
      	 
 }	 
return 0;
}

int main()
{
int i,k;
printf("how many integers u want to permute");
scanf("%d",&n);
b = (int *)malloc(n* sizeof(int));
printf("enter array elements");
for(k=0;k<n;k++)
{
 	scanf("%d",&b[k]);	
}	
permuten(b,2);
for(i=1;i<n && n>2 ;i++)
{
 swap(0,i);
 permuten(b,2);
 swap(0,i);
}
return 0;
}

