#include<stdio.h>
int partition(int *A,int p,int r)
{
	int pivot,i,k,j,temp,m,mid;
	mid=(p+r)/2;
	pivot=A[mid];
	int count,count1;

	while(i<j)
	{
		
		while(A[i]<pivot&&i<j)
		 i++;
		while(A[j]>pivot&&i<j)
		 j--;
		if (i<j)
		{
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      count--;
      count1++;
      if(A[i]==A[j])
      j-- ;
      }
      
    }
    count = count+i;
    return i;
    printf("count=%d \n",count);
}
void quicksort(int *A, int p, int r)
{
	int index;
	if(p>=r) return;
	index = partition(A,p,r);
	quicksort(A,p,index-1);			//pivot finally settles in correct place...
	quicksort(A,index+1,r);
}
int main()
{ 
   int n, i,j;
	scanf("%d", &n);
	int A[n];
	for (i=0; i<n; i++) scanf("%d", &A[i]);
	printf("\n");
	quicksort(A,0,n-1);
	for (i=0; i<n; i++) printf("%d ", A[i]);
	printf("\n");
	return 0;
}
