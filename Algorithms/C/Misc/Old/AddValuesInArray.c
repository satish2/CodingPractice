//NOTES
/*
 * In case if you are doing increment/decrement operations of Pointer and you want to access previous address
 * you can do <datatype> *B = A like in this case. But assigning it to B must be done after memory allocation since
 * value assigned when initialized or declared changes after memory allocation is done.
 * 1 Increment value of pointer is always sizeof(<Datatype>).
 */

#include <stdio.h>
#include <stdlib.h>

int main2(int argc, char** argv){
	int *A,n=10,i=3,answer=0;
	printf("Before memory allocation A is %d\n",(int)A);
	printf("Enter size of array\n");
	scanf("%d",&n);
	A = (int *)malloc(n*sizeof(int));
	int *B=A;
	printf("After memory allocation A is %d\n",(int)A);
	
	for (i=0;i<n;i++){
		scanf("%d",A);
		A++;
	}
	printf("After memory allocation and adding values by incrementing A is %d and B is %d\n",(int)A,(int)B);
	for(i=0;i<n;i++){
		answer += *B;
		B++;
	}
	printf("%d\n",answer);
	return 0;
}