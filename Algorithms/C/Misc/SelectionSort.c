#include <stdio.h>

void swap (int *A,int assumedPosition,int minPosition){
	int temp = A[minPosition];
	A[minPosition] = A[assumedPosition];
	A[assumedPosition] = temp;
}

int mainSelect (int argc,char** argv){
	
	int i,j,n;
	int *A;
	printf("Enter size of array :");
	scanf("%d",&n);
	A = (int *)malloc(sizeof(int)*n);
	printf("\nenter elements of array: ");
	for (i = 0; i< n;i++){
		scanf("%d",&A[i]);
	}
	for (j=0;j<n-1;j++){
		int minIndex = j;
		//SelectSort
		for (i=j+1;i<n;i++){
			if(A[i] < A[minIndex]){
				minIndex = i;
			}	
		}
		if(j != minIndex)
			swap(A,j,minIndex);
	}
	printf("\n");
	for (i = 0; i< n;i++){
		printf("%d\t",A[i]);
	}
}

