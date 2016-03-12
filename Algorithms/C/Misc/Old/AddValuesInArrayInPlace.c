//NOTES
/*
 * Either it can be done like in AddValuesInArray code or like in this where I have one variable which 
 * has the initial value of A (before incrementing) stored in B
 * OR
 * it can be done via changing A's value by subtracting A - (SIZEOFARRAY)
 * should not multiply SIZEOFARRAY and SIZEOFDATATYPE as in case of pointers,
 * subtractions happen in units of sizeofdatatype automatically
 * i.e., A-4 = A-4*(SIZEOFDATAYPE);
 */

#include <stdio.h>
#include <stdlib.h>

int main3(int argc, char** argv){
	int *A,n=10,i=3,answer=0;
	printf("Before memory allocation A is %d\n",(int)A);
	printf("Enter size of array\n");
	scanf("%d",&n);
	A = (int *)malloc(n*sizeof(int));
	//int B = A;
	printf("After memory allocation A is %d\n",(int)A);
	
	for (i=0;i<n;i++){
		scanf("%d",A);
		A++;
	}
	printf("After memory allocation and adding values by incrementing A is %d \n",(int)A);
	A = A - n;
	printf("After memory allocation and adding values by subtracting its size A is %d\n",(int)A);
	for(i=0;i<n;i++){
		answer += *A;
		A++;
	}
	printf("%d\n",answer);
	return 0;
}