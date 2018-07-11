#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 	10
void swap(int *array, int i, int j);
int partition(int *array, int st, int end);
void quicksort(int *, int, int);

void swap(int *array, int i, int j) {
	int temp = array[j];
	array[j] = array[i];
	array[i] = temp;
	return;
}

// Insertion Sort
// Merge Sort


/*
Insertion Sort:
Imagine a deck of cards on top of table.
1. Take the first card and hold it.
2. From second card onwards, we will compare with previous cards in hand and put in appropriate place.
3. Loop-Invariant: Always the cards in hand are sorted. 
*/

void insertion_sort(int *array, int len) {
	int j = 1;
	for (; j < len; j++) {
		int i = j - 1;
		int key = array[j];
		while (i >= 0) {
			if (array[i] > key) {
				array[i+1] = array[i];
				i--;
			} else {
				break;
			}
		}
		array[i+1] = key;
	}
}

void print_array(int *array, int len) {
	int iter = 0;
	printf ("Sorted Array : ");
	for ( iter = 0; iter < len; iter ++) {
		printf("%d \t", array[iter]);
	}
	printf("\n");
}


void merge(int *array, int lo, int mid, int hi) {
	int lsize = mid - lo;
	int rsize = hi - mid + 1;
	
	int *left = (int *) malloc(lsize*sizeof(int));
	int *right = (int *) malloc(rsize*sizeof(int));
	memset(left, 0, lsize);
	memset(right, 0, rsize);
	
	int i, j, k;
	i=j=0;
	k=lo;
	for (; i < lsize; i++, k++){
		left[i] = array[k];
	}
	for (j = 0; j < rsize; j++, k++) {
		right[j] = array[k];
	}
	i=j=0;
	k=lo;
	while ( i<lsize && j<rsize) {
		if (left[i] <= right[j]) {
			array[k] = left[i];
			i++;
		} else {
			array[k] = right[j];
			j++;
		}	
		k++;
	}
	while (i < lsize) {
		array[k] = left[i];
		i++;
		k++;
	}
	while (j < rsize) {
		array[k] = right[j];
		j++;
		k++;
	}
	free(left);
	free(right);
}

void merge_sort(int *array, int lo, int hi) {
	if (lo >= hi) {
		return;
	}
	int mid = lo + (int )ceil((hi - lo + 1)/2);
	merge_sort(array, lo, mid-1);
	merge_sort(array, mid, hi);
	merge(array, lo, mid, hi);
}

/*
 * Quicksort:
 * First partition the incoming array by selecting a pivot element
 * Call quicksort on left and right subarrays recursively.
 * Base condition: Array of size 1 or 0
 */

/*
 * pivot: Iterate from left to right. Any value less than pivot. Don't swap
 * If greater swap!!
 */
int partition(int *array, int st, int end) {
	printf("Partitioning on st = %d and end=%d.\n", st, end);
	int pi = end; // pi = pivot_index;
	int pivot = array[pi];
	// j = current element we are considering
        // i = index of last element that was lesser than pivot
	int i = st - 1;
	int j = st;
	while(j < end) {
        	if (array[j] > pivot) { // current element greater than pivot
			// do nothing!!
		} else { // current element lesser than pivot. Move current element to index i+1 denotes.
			swap(array, i+1, j);
			i++;
		}
		j++;
  	}
	swap(array, i+1, pi);
	return (i+1);
}


void quicksort(int *array, int st, int end) {
   if (st >= end) {
   	return;
   }
   int pi = partition(array, st, end); // pi = pivot_index
   // element at pi is at corrent position. Other elements should be used in comparisons.
   quicksort(array, st, pi-1);
   quicksort(array, pi+1, end);
}

// Counting sort:
/*
Idea is to count the number of elements less than certain value and put that element at count+1 index in array
Assumptions:
It is assumed that elements in array lie within ray 0 -> k. This sorting takes O(n) time where n >= k
Takes linear time. Stable sort i.e., preserves the order of elements in array.
*/
void countingsort (int *A, int st, int end) {
	// Assuming range to be within 0 -> 20
	int k = 0; // k always denotes the position of element in array C[]. This array is to maintain count.
	int iter = 0;
	int B[MAX_LEN] = {0};
	int C[21] = {0};
	for (iter = 0; iter <= 20; iter++) {
		C[iter] = 0;
	}
	// 1. Count the number of elements with same value.
	for (iter = st; iter <= end; iter++) {
		C[A[iter]] += 1;
	}
	// 2. Now, have count of all elements that are less than or equals 'iter'.
	for (iter = st+1; iter <= 20; iter++) {
		C[iter] += C[iter-1];
	}
	// 3. Have a separate array B, which will have sorted array.
	for (iter = st; iter <= end; iter++) {
		B[C[A[iter]]-1] = A[iter];
		C[A[iter]]--;
	}
	print_array(B, end+1);
}


int main (int argc, char *argv[]) {
	printf("Please enter %d elements separated: \t", MAX_LEN);
	int iter = 0;
	int choice = 0;
	int array[MAX_LEN];
	memset(array, 0, sizeof(array));
	for (iter = 0 ; iter < MAX_LEN; iter++) {
		scanf("%d", &array[iter]);
	}
		
	printf("Please enter corresponding value for insertion method to use: \n");
	printf("Insertion sort = 0.\n");
	printf("Merge sort = 1.\n");
	printf("Quick sort = 2.\n");
	printf("Counting sort = 3.\n");
	printf("Choice : ");
	scanf("%d", &choice);
	switch (choice) {
		case 0 : {
			insertion_sort(array, MAX_LEN);
			print_array(array, MAX_LEN);
			break;
		}
		case 1 : {
			merge_sort(array, 0, MAX_LEN-1);
			print_array(array, MAX_LEN);
			break;
		}
		case 2:  {
			printf("Using quicksort:\n");
			quicksort(array, 0, MAX_LEN-1);
			print_array(array, MAX_LEN);
			break;
		}
		case 3: {
			printf("Using counting sort:\n");
			countingsort(array, 0, MAX_LEN-1);
			break;
		}
		default : {
			merge_sort(array, 0, MAX_LEN-1);
			print_array(array, MAX_LEN);
		}
	}	
}
