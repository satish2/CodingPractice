#include<stdio.h>
#include<stdlib.h>
int permuten(int *b,int x);
void swap(int ,int);
int permuten(int *b,int x);
int *b,*a;
int n;
int comprv(int,int);
int compare(int );
void coppy()
{int k;
for(k=0;k<n;k++)
      {
      	a[k]=b[k];	
      }
}
int compare(int cl,int ch)
{ int i;
	for(i=cl;i<ch;i++)
	{if(a[ch]==a[i])
	return 0;}
	return 1;
}

void swap(int d,int c)
{
  int  temp;
  temp=b[c];
  b[c]=b[d];
  b[d]=temp;
} 

//take care that it does not swap with same value again and again by comparing it with previous values that were swapped
int permuten(int *b,int x)
{
 int i=x;
 int j;
 if(x<=n-2)
 {
  permuten(b,x+1);
  for(;i<n;i++)
  {
     if(compare(x-1,i)){swap(x-1,i);
     coppy();
     permuten(b,x+1);
     swap(x-1,i);
     coppy();}
  } 
 }
 else
 {
       for(j=0;j<n;j++)
       {
       	printf("%d \t",b[j]);
       }
       	printf("\n");
	    	if(b[n-2]!=b[n-1]){
		   swap(n-2,n-1);
		   coppy();
       for(j=0;j<n;j++)
       {
       	printf("%d \t",b[j]);
       }
       	swap(n-2,n-1);
       	coppy();}
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
a=(int *)malloc(n* sizeof(int));
printf("enter array elements");
for(k=0;k<n;k++)
{
 	scanf("%d",&b[k]);	
}	
for(k=0;k<n;k++)
{
 	a[k]=b[k];	
}
permuten(b,2);
for(i=1;i<n && n>2 ;i++)
{
 if(compare(0,i)){
	 swap(0,i);
      coppy();
 permuten(b,2);
 swap(0,i);
    coppy();
   }
}
return 0;
}
	

