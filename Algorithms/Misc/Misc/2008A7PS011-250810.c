#include<stdio.h>
void quicksort(int *num,int chr[],int low,int high);
int partition(int *A,int B[],int p,int r);
volatile int n;
int main()
{
	int i,j,n,k;
	printf("enter how many numbers to be sorted");
	scanf("%d",&n); 	
	int num[n];
	int index[n];	
	for(i=0;i<n;i++)
	{
		printf("enter number \n");
		scanf("%d",&num[i]);
		
	}
	for(i=0;i<n;i++)			//for above entered array index or serial nos are given by next for loop
	{
		printf("enter a number that acts as its position in initial array\n");	
		scanf("%d",&index[i]);
}
	quicksort(num,index,0,n-1);	
	for(i=0;i<n;i++)
	{
		 printf(" %d \t %d\n",num[i],index[i]);
	}
	return 0;
	}
void quicksort(int *num,int index[],int low,int high)
{
	int piv;
	if(low>=high) return;
	piv = partition(num,index,low,high);
	quicksort(num,index,low,piv-1);
	quicksort(num,index,piv+1,high);
}
int partition(int *A,int B[],int p,int r)
{
	int pivot,i,j,temp1,k;				//B is serial number
	int temp2;
	pivot=A[r];
	i=r;
	j=p;
	while(i>j)
	{
		while(A[i]>pivot&&i>j)
		  i--;
		while(A[j]<pivot&&i>j)
		 j++;
		if (i>j)
		      { 
			temp1 = A[i];
			A[i] = A[j];
			A[j] = temp1;
			temp2=B[i];
			B[i]=B[j];
			B[j]=temp2;
			/*if(A[i]==A[j])
			{
			i--;}*/								//here problem is if at all i do not write this line loop goes on unnecessary one more time,
													//in case of pivot=a[i]=a[j] and index already in order...
													//then it swaps as loop goes on 1 extra time and then again swap occurs based on index.. 
			if(A[i]==A[j] && B[i]<B[j])		//HERE IF EQUAL NUMBERS ARE SWAPPED THEY ARE AGAIN SWAPPED 									//BASED ON THEIR SERIAL/INDEX NUMBER
			{temp1 = A[i];
			A[i] = A[j];
			A[j] = temp1;
			temp2=B[i];
			B[i]=B[j];
			B[j]=temp2;
			i--;}
			printf("In partition:j = %d, i = %d	\t pivot=%d\n", j,i,pivot);
      			for (k=0; k<=r; k++) 
      			printf("%d, ", A[k]);
			printf("\n");	
		      }	
							
	  }
return i;
}


/*
enter how many numbers to be sorted5
enter number 
4
enter number 
1
enter number 
3
enter number 
1
enter number 
5
enter a number that acts as its position in initial array
1
enter a number that acts as its position in initial array
2
enter a number that acts as its position in initial array
3
enter a number that acts as its position in initial array
4
enter a number that acts as its position in initial array
5
In partition:j = 0, i = 3		 pivot=1		//iteration 1
1, 1, 3, 4, 
In partition:j = 0, i = 1		 pivot=1		//iteration 2
1, 1, 3, 4, 
In partition:j = 0, i = 0		 pivot=1		//iteration 3
1, 1, 3, 4, 
 1 	 2
 1 	 4
 3 	 3
 4 	 1
 5 	 5
here in this problem serial number of multiple 1s show that A2 occured before A4 and also A3 did not change its position from beginning to end shown by iteration 1 to 3...it happens only if it is already in its own position as per sorted array.
In examples like 1,4,5,3,4,5 last number 5[position =6] does not change its position from starting to end. 

*/

