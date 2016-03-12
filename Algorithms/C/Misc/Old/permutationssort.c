#include<stdio.h>
#include<stdlib.h>
int permuten(int *b,int x);
void swap(int ,int);
int permuten(int *b,int x);
void quicksort(int *b,int, int);
int partition(int *b,int ,int);
int *b,*a;
int n;
int count=1;
int check=0;
int partition(int *A,int p,int r)
{
	int pivot,i,k,j,temp;
	pivot=A[p];
	i=p;
	j=r;
	while(i<j)
	{	check++;
		while(A[i]<pivot&&i<j){check++;
		i++;}
		while(A[j]>pivot&&i<j){check++;
		j--;}
		if (i<j && A[i]!=A[j])
		{check++;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      }
     if(A[i]==A[j])
      j--;
    }
    return i;
}
void quicksort(int *A, int p, int r)
{
	int index;
	if(p>=r) return;
	index = partition(A,p,r);
	quicksort(A,p,index-1);
	quicksort(A,index+1,r);
}
//
void swap(int d,int c)
{
  int  temp;
  temp=b[c];
  b[c]=b[d];
  b[d]=temp;
} 
//
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
     	for(j=0;j<n;j++)a[j]=b[j];
		 printf("count = sa %d ti\n",count);	
       count++;	    	
	    quicksort(a,0,n-1);
	   printf("check=gb %d gb \n",check);
	   	check=0;
	   for (j=0; j<n; j++) printf("%d ", a[j]);
	    printf("\n");
	    swap(n-2,n-1);
       for(j=0;j<n;j++)
       {
       	printf("%d \t",b[j]);
       }
       printf("\n");
       printf("count = xz %d yp\n",count);	
       count++;
       for(j=0;j<n;j++)a[j]=b[j];
       quicksort(a,0,n-1);
      printf("check=qw %d qw\n",check);
      	check=0;
      for (j=0; j<n; j++) printf("%d ", a[j]);	 
       swap(n-2,n-1);
       printf("\n");
 }	 
return 0;
}
//
int main()
{
int i,k;
printf("how many integers u want to permute");
scanf("%d",&n);
b = (int *)malloc(n* sizeof(int));
a = (int *)malloc(n* sizeof(int));
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

