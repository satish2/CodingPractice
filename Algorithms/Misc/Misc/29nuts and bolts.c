//giving a count a non negatve value intially and incrementing involves swapping ..so better to decrement and give count initially zero value..
//it does notinvolve any swapping because they are always less than pivot and "while(A[i]<pivot&&i<j)i++;" statement just discludes it...gr8
//pivot always  greater than zero.:) :) :D
#include<stdio.h>
#include<stdlib.h>
int i1;
int nutsz[6]= {1,2,78,4,5,6};
int boltsz[6] = {6,5,90,3,2,1};
int partition(int *A,int pivot,int p,int r)
{
	int i,k,j,temp;
	int count=0;
	i=p;
	j=r;
	while(i<j)
	{
		count--;
		while(A[i]<pivot&&i<j)i++;
		while(A[j]>pivot&&i<j)j--;
		if (i<j && A[i] != A[j])
		{
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      printf("In partition:i = %d, j = %d\n", i,j);
      for (k=p; k<=r; k++) 
      printf("%d, ", A[k]);
      printf("\n");
      
      } 
    	else if(A[i]==A[j])
     	j--;
    }
    if(A[i]==pivot)
    {printf("1....matched are %d %d position of element is %d \n",pivot,A[i],i);
    A[i]=count;
    nutsz[i1]=count;}
    return (i);
}

int main()
{
	int i2;
	int index=0;
	int index1=0;
	for(i1=0;i1<=5;i1++)
	{
		printf("index =%d\n",index);
		index=partition(boltsz,nutsz[i1],0,5);
	}
	//unmatched pairs are
	for(i2=0;i2<6;i2++)
	{
		if(boltsz[i2]>0  )
		printf("boltsz=%d",boltsz[i2]);	
	}	
	for(i2=0;i2<6;i2++)
	{
		if(nutsz[i2]>0)
		printf("nutsz=%d",nutsz[i2]);	
	}
return 0;
}	
