#include <stdio.h>

QUICKSORT(int *A,int low,int high) {
	
	int *indices = EQ-PARTITION(A, low, high);
	QUICKSORT(A,low,indices[0]-1);
	QUICKSORT(A,indices[1]+1,high);
	
}

EQ-PARTITION(A, p ,r) {
	
	int j = p; k = r;
	int pivot = A[p];
	int i = p;
	while (i <= k) {
		if(A[i] < pivot) {
			swap (A[j],A[i]);
			i++;
			j++;
		} else if (A[i] > pivot) {
			swap(A[k],A[i]);
			k--;
		} else
			i++;
	}
	return j & k;
}

