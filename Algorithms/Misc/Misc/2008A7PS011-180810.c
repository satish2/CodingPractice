#include<stdio.h>
#include<string.h>
void quicksort(int *did,char ena[][11],int *gsal,int low,int high);
void quicksort1(int *did,char ena[][11],int *gsal,int low,int high);
int partition(int *A,char B[][11],int *C,int p,int r);
int partition1(int *A,char B[][11],int *C,int p,int r);
int main()
{
 	int depid[4];
	int gsalary[4];
	char ename[4][11];
	int i;	
	printf("enter employee details \n");
	for(i=0;i<4;i++)
	{
		printf("enter department id\n");
		scanf("%d",&depid[i]);
		printf("enter ename\n");
		scanf("%s",&ename[i]);
		printf("enter gsalary\n");
		scanf("%d",&gsalary[i]);
	}
//sorting by id nuimber
	quicksort(depid,ename,gsalary,0,3);
	quicksort1(depid,ename,gsalary,0,3);
	printf("department id\temployee name\temployee gross salary \n");
	for(i=0;i<4;i++)
	{
		 printf(" %d \t %s \t %d \t \n",depid[i],ename[i],gsalary[i]);
	}
	return 0;
	}
void quicksort(int *depid,char ena[][11],int *gsal,int low,int high)
{
	int piv;
	if(low>=high) return;
	piv = partition(depid,ena,gsal,low,high);
	quicksort(depid,ena,gsal,low,piv);
	quicksort(depid,ena,gsal,piv+1,high);
}
int partition(int *A,char B[][11],int *C,int p,int r)
{
	int pivot,i,j,temp1,temp3;
	char temp2[11];
	int count,count1;
	pivot=A[p];
	i=p;
	j=r;
	while(i<j)
	{
		while(A[i]<pivot&&i<j)i++;			
		while(A[j]>pivot&&i<j)j--;			
		if (i<j)
      { 
		temp1 = A[i];
		A[i] = A[j];
		A[j] = temp1;
		strcpy(temp2,B[i]);
		strcpy(B[i],B[j]);
		strcpy(B[j],temp2);
		temp3 = C[i];
		C[i] = C[j];
		C[j] = temp3;
		if(A[i]==A[j])
		j--;											//this line is important

		}
	  }
	  count = count + i;
return i;
}
//SORTING BY NAME ONLY IF THEY POSSESS SAME ID's
void quicksort1(int *depid,char ena[][11],int *gsal,int low,int high)
{
	int piv;
	if(low>=high) return;
	piv = partition1(depid,ena,gsal,low,high);
	quicksort1(depid,ena,gsal,low,piv);
	quicksort1(depid,ena,gsal,piv+1,high);
}
int partition1(int *A,char B[][11],int *C,int p,int r)
{
	int i,k,j,l,temp1,temp3;
	char temp2[11];
	char pivot[11];
	strcpy(pivot,B[p]);
	i=p;
	j=r;
	while(i<j && A[i]==A[j])											//allowing only people with same id's
	{
		
		while((k=strcmp(B[i],pivot))<0 && i<j)i++;				//this comparision went wrong
			
		while((l=strcmp(B[j],pivot))>0 && i<j)j--;					//this comparision went wrong
		if (i<j)
       		{
		strcpy(temp2,B[i]);							
		strcpy(B[i],B[j]);					
		strcpy(B[j],temp2);		
		/*temp1 = A[i];
		A[i] = A[j];
		A[j] = temp1;*/
		temp3 = C[i];
		C[i] = C[j];
		C[j] = temp3;
		l=strcmp(B[j],B[i]);
		if (l==0)
		j--;											//this line is important
		 }
	    }
return i;
}
/*
why j-- after swapping
consider 1	8	2	9	4
pivot is 1
8	2	9	4
pivot is 8
4	2	9	8

it becomes into [4	2	9] and 	[8]
4	2	9
2	4	9
[2]	[4	9]

*/

