// Create a heap using arrays
// Convert heap to min-heap & max-heap
// Extract elements from heap to implement sorting
// Heapify function - Which would heapify existing array of elements.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int array[10] = {1, 15, 2, 4, 6, 7, 8, 11, -1, -15};

typedef struct 
{
	int *array;
	int num_of_elements;
} _heap;

void build_max_heap(_heap *h, int root);
void build_min_heap(_heap *h, int root_index);
void heap_sort(_heap *h);
// Before calling this function do check on index, that it is not '0'
int get_parent(int index) 
{
	if (index == 0) {
		fprintf(stderr, "Invalid value for index: %d\n", index);
		exit(-1);
	}
	return ((int) ceil((float)index/2)) - 1;
}

int get_left_index(int index) 
{
	return 2*index + 1;
}

int get_right_index(int index) 
{
	return 2*index + 2;
}


void swap(int *array, int i, int j) 
{
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
//	printf("Swapping values at index %d & %d.\n", i, j);
	return;
}

// Max-Heap; Element at index i >= Children(i)
void max_heapify(_heap *h, int index) 
{
	int left_child_index = get_left_index(index);
	int right_child_index = get_right_index(index);
	int max_index = index;
	if (left_child_index >= h->num_of_elements)
		left_child_index = -1;
	
	if (right_child_index >= h->num_of_elements)
		right_child_index = -1;


	if (left_child_index != -1 && h->array[index] < h->array[left_child_index]) {
		max_index = left_child_index;
	} 
	if (right_child_index != -1 && h->array[max_index] < h->array[right_child_index]) {
		max_index = right_child_index;		
	}

	if (index == max_index) {
		return;
	}
	swap(h->array, index, max_index);
	build_max_heap(h, max_index);
	return;
}

// Input: Array of input elements
// num_of_elements: Number of input elements
// Returns array that is max-heapified. Free this space after utilizing this.
void build_max_heap(_heap *h, int root_index) 
{
	/*
		Start with last parent.
		Exchange with children if its value is less than that of either of children
		Call max-heapify on those children index
	*/
	int last_parent = get_parent(h->num_of_elements - 1); // parent of last node
	int i = last_parent;
	while (i >= root_index) {
		max_heapify(h, i);
		i--;
	}
}

void min_heapify(_heap *h, int curr_index) 
{
//	printf("Calling min_heapify at node: %d\n", curr_index);
	int left_child_index = get_left_index(curr_index);
	int right_child_index = get_right_index(curr_index);
	int min_index = curr_index;

	if (left_child_index >= h->num_of_elements) {
		left_child_index = -1;
	}

	if (right_child_index >= h->num_of_elements) {
		right_child_index = -1;
	}
	
	if (left_child_index != -1 && h->array[min_index] > h->array[left_child_index]) {
		min_index = left_child_index;
	}
	if (right_child_index != -1 && h->array[min_index] > h->array[right_child_index]) {
		min_index = right_child_index;
	}	

	if (min_index == curr_index) {
		return;	
	}
	
	swap(h->array, curr_index, min_index);
	build_min_heap(h, min_index);
	return;
}


void build_min_heap(_heap *h, int root_index) 
{
	/*
		Start from the last parent
		Work backwards
		Call min_heapify from last parent
		parent's value is less than or equals children's.
	*/
	int last_parent_index = get_parent(h->num_of_elements - 1);
	int i = last_parent_index;
	while (i >= root_index) {
		min_heapify(h, i);
		i--;	
	}		
}

void print_heap(_heap *h) 
{
	int i = 0;
	while(i < h->num_of_elements) {
		printf("%d\t", h->array[i]);
		i++;
	}
	printf("\n");
}

void heap_sort(_heap *h) 
{
// There are two approaches.
// Build max_heap and swap the root with last element in array
// build_max_heap from root till last but one element & repeat.

// In min_heap, take out root, print it
// build_min_heap again.
// Repeat. Just put largest element at end of array .. NAH!! not preferred.

// 1. Build max heap
	int size = h->num_of_elements;
	while (h->num_of_elements > 1) {
		build_max_heap(h, 0);
		swap(h->array, 0, h->num_of_elements -1);
		h->num_of_elements--;
	}
	h->num_of_elements = size;
	print_heap(h);
}

int main(int argc, char *argv[]) 
{
	_heap *h = (_heap *)calloc(sizeof(_heap), 1);
	h->array = array;
	h->num_of_elements = sizeof(array)/sizeof(int);
	
	// 1. build_max_heap
	build_max_heap(h, 0);
	print_heap(h);

	h->num_of_elements = sizeof(array)/sizeof(int);
	// 2. build min heap
	build_min_heap(h, 0);
	print_heap(h);

	// 3. heap sort
	heap_sort(h);
	return 0;
}

