//errors in line 14 and 76
#include<stdio.h>
void mergesort(int a[],int,int);
int partition(int *a,int,int);
void insertsort(int a[],int,int);
void quickmerge(int *,int ,int);
volatile int size;
int main()
{
	int i;
 	int low=0;					
        int high ;
	scanf("%d",&size);					//size is size of given array
	int a[size];
        high=size-1;						/*error*/
	for(i=0;i<size;i++)
	{
 		scanf("%d",&a[i]);				//inputting numbers into our array
 	}
	mergesort(a,low,high);					//calling mergesort to sort array
for(i=0;i<size;i++)
{
  printf("%d \t",a[i]);
}
return 0;
}
void mergesort(int b[],int c,int d)
{
 int mid;							//mid is middle element of array of size d and c is position 
 mid=(c+d)/2;							//of lowest element of array	
 if((d-c)>1)
 {
  mergesort(b,c,mid);
  mergesort(b,mid+1,d);
  quickmerge(b,c,d);
 }
}
void quickmerge(int *A, int p, int r)
{
	int index;
	if(p>=r) return;
	index = partition(A,p,r);
	quickmerge(A,p,index-1);			//pivot finally settles in correct place...
	quickmerge(A,index+1,r);
}	
int partition(int *A,int p,int r)
{
	int pivot,i,k,j,temp;
	pivot=A[p];
	i=p;
	j=r;
	while(i<j)
	{
		while(A[i]<pivot&&i<j)i++;
		while(A[j]>pivot&&i<j)j--;
		if (i<j)
		{
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      printf("In partition:i = %d, j = %d	\t pivot=%d\n", i,j,pivot);
      for (k=p; k<=r; k++) 
      printf("%d, ", A[k]);
      printf("\n");
      if(A[i]==A[j])
      j--;
      }
    }
    return i;
}
