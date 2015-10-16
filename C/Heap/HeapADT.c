#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP 1
#define MIN_HEAP 0

typedef struct _heap{
	int capacity; //max capacity of heap
	int length; //number of elements in heap
	int *arr; //points to array that contain heap elements
	int heap_type; //1 - MAX_HEAP 0-MIN_HEAP
}heap;

void printInputArray(int *arr,int arrLen);
int build_heap(int *array, heap *hp, int array_size);
void heapify(int nodeIndex,heap *hp);
int getParentIndex(int i, heap *hp);
int getLeftChildIndex(int i, heap *hp);
int getRightChildIndex(int i, heap *hp);
void heapsort(heap *h);
void DeleteElement(heap *hp, int val);
void printLeaves(heap *h);

void printInputArray(int *array,int capacity){
	int i;
	for(i=0;i<capacity;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}

int build_heap(int *array, heap *h, int n){
	if(h == NULL)
		return -1;
	while(n >= h->capacity){
		h->arr = (int *)realloc(h->arr,h->capacity*2);
		h->capacity = h->capacity*2;
	}
	if(!h->arr){
		printf("Memory Allocation Failed\n");
		return;
	}
		
	int i=0;	
	for(i=0;i<n;i++){
		h->arr[i] = array[i];
	}
	h->length = i;
	for(i=(h->length-1)/2-1;i>=0;i--){
		heapify(i,h);
	}
		
		
}

/*
 * It goes down from nodeIndex swapping current node with max of its childNode
 * 
*/
void heapify(int nodeIndex,heap *hp){
//	printf("percolating at = %2d : ",nodeIndex);
	int lChild = getLeftChildIndex(nodeIndex,hp);
	int rChild = getRightChildIndex(nodeIndex,hp);
//	printf("leftCh: %2d, rightCh:%2d :",hp->arr[lChild],hp->arr[rChild]);
	int curr = nodeIndex;
	int max = curr;
	if(lChild != -1 && hp->arr[max] < hp->arr[lChild])
		max = lChild;
	if(rChild != -1 && hp->arr[max] < hp->arr[rChild])
		max = rChild;

	if(max != curr){
		int temp = hp->arr[max];
		hp->arr[max] = hp->arr[curr];
		hp->arr[curr] = temp;
//		printInputArray(hp->arr,hp->length);	
		heapify(max,hp);
	}
}	

int getParentIndex(int i, heap *hp){
	int len = hp->length;
	if(i<=0 || i>=len)
		return -1;
	
	return (i-1)/2;
}

int getLeftChildIndex(int i, heap *hp){
	int len = hp->length;
	int left = 2*i+1;
	if(left>=len || left <= 0)
		return -1;
	return left;
}

int getRightChildIndex(int i, heap *hp){
	int len = hp->length;
	int right = 2*i+2;
	if(right>=len || right <= 0)
		return -1;
	return right;
}

/*
	Take MAX element at root and put it at the end, decrease length, so that 
	it will always replace value at root with length-1.
	This is in-place sort.
	Replace last with first!
*/

void heapsort(heap *h){
	int temp;
	int i = h->length-1;
	int old_len = h->length;
	for(;h->length > 0;){
		//Swap first with Last		
//		printf("Swapping %d with %d\n",h->arr[h->length-1],h->arr[0]);
		temp = h->arr[h->length-1];
		h->arr[h->length-1] = h->arr[0];
		h->arr[0] = temp;

		h->length--;
		heapify(0, h);
//		printf("h->length = %2d: ",h->length);
//		printInputArray(h->arr,h->length);
	}
	h->length = old_len;
}

void printLeaves(heap *hp){
	int lastParent = ((hp->length-1)-1)/2;
	int i = lastParent+1;
	for(;i<hp->length;i++)
		printf("%d ",hp->arr[i]);
	printf("\n");
	return;
}

void DeleteElement(heap *hp, int val){
	//Level Order Traversal
	int length = hp->length;
	int i;
	for(i=0;i<length;i++){
		if(hp->arr[i] == val){
			int temp = hp->arr[length-1];
			hp->arr[length-1] = hp->arr[i];
			hp->arr[i] = temp;
			//At hp->length-1 is the element that is not needed.
			hp->length--;
			break;
		}
	}
	int j = i;
	for(;j>=0;){
		heapify(j,hp);
		j = getParentIndex(j,hp);
	}
}

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Invalid arguments. Usage: ./heap <capactiyOfHeap> <inputArraySize>\n");
		return 0;
	}
	int i=0,capacity = strtoimax(argv[1],NULL,10);
	int inp_arr_len = strtoimax(argv[2],NULL,10);

	heap *myheap = (heap*)malloc(sizeof(heap));
	myheap->capacity = capacity;
	myheap->length = 0;
	myheap->arr = (int *)calloc(capacity,sizeof(int));
	myheap->heap_type = MAX_HEAP;

	FILE *fd = fopen("heapIntArray.txt","r");
	int *inp_arr = (int *)calloc(inp_arr_len,sizeof(int));
	while(fscanf(fd,"%d",&inp_arr[i]) != EOF){
		i++;
	}
	build_heap(inp_arr,myheap,inp_arr_len);
	printf("%-11s : ","Heap");
	printInputArray(myheap->arr,myheap->length);
	
	printf("%-11s : ","Leaves");
	printLeaves(myheap);

	DeleteElement(myheap,10);
	printf("%-11s : ","Deleted 10");
	printInputArray(myheap->arr,myheap->length);

	heapsort(myheap);
	printf("%-11s : ","Sorted");
	printInputArray(myheap->arr,myheap->length);

	free(myheap);
	return 0;
}
