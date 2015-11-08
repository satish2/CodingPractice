#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PriorityQueue{
	int *arr;
	int len;
	int cap;
}PQ;

void build_heap(PQ *p, int *array){
	int i = 0;
	for(;i<p->len;i++){
		p->arr[i] = array[i];
	}
	return;
}

int getParentIndex(PQ *p, int i){	
	if(i<=0 || i>=p->len){
		return -1;
	}
	return (i-1)/2;
}

int getLeftChildIndex(PQ *p, int i){
	int left = 2*i+1;
	if(left >= p->len)
		return -1;
	return left;
}

int getRightChildIndex(PQ *p, int i){
	int right = 2*i+2;
	if(right >= p->len)
		return -1;
	return right;
}

void heapify(PQ *p, int i){
	int lci = getLeftChildIndex(p,i);
	int rci = getRightChildIndex(p,i);
	int max = i;
	if(lci != -1 && p->arr[max] < p->arr[lci]){
		max = lci;
	} 
 	if(rci != -1 && p->arr[max] < p->arr[rci]){
		max = rci;		
	}
	if(max != i){
		int temp = p->arr[i];
		p->arr[i] = p->arr[max];
		p->arr[max] = temp;
		heapify(p,max);
	}
}

void insert(PQ *p, int val){
	int len = p->len;
	if(p->len+1 >= p->cap){
		while(p->len+1 >= p->cap){
			p->cap = 2*p->cap;
		}
		p->arr = (int *)realloc(p->arr, sizeof(int)*(p->cap));
	}
	p->arr[len] = val;
	p->len++;
	int i = getParentIndex(p,len);
	while(i >= 0){
		heapify(p,i);
		i = getParentIndex(p, i);
	}
}

int delete(PQ *p, int val){
	//First search for the value and then delete
	int index = find(p,val);
	int len = p->len;
	
	if(index == -1){
		printf("element does not exist \n");
		return -1;
	}
	int temp = p->arr[index];
	p->arr[index] = p->arr[len-1];
	p->arr[len-1] = temp;
	p->len--;
	//Swapped last element with the one we want to delete. Heapifying modifed Priority Queue.
	heapify(p,index);
}

int find(PQ *p, int val){
	int i,len = p->len;
	for(i=0;i<len;i++){
		if(p->arr[i] == val)
			return i;
	}
	return -1;
}

void printPQ(PQ *p){
	int i = 0;
	for(;i<p->len;i++){
		printf("%d ", p->arr[i]);
	}
	printf("\n");
}

void DeleteHeap(PQ *p){
	if(!p) {
		return;
	}
	free(p->arr);
	free(p);
	p = NULL;
	return;
}

void preorder(PQ *p, int index){
	//0 -> root
	//Center, Left, Right
	if(index == -1){
		return;
	}
	if(index < p->len){
		printf("%d ",p->arr[index]);
		preorder(p, getLeftChildIndex(p,index));
		preorder(p, getRightChildIndex(p,index));
	}
	return;
}

void postorder(PQ *p, int index){
	//Left, Right, Center
	if(index == -1)
		return;
	if(index < p->len){
		postorder(p,getLeftChildIndex(p,index));
		postorder(p,getRightChildIndex(p,index));
		printf("%d ", p->arr[index]);
	}
	return;
}

void inorder(PQ *p, int index){
	//Left, Center, Right
	if(index == -1)
		return;
	if(index < p->len){
		inorder(p,getLeftChildIndex(p,index));
		printf("%d ", p->arr[index]);
		inorder(p,getRightChildIndex(p,index));
	}
	return;
}

void heapsort(PQ *p){
	int old_len = p->len;
	int len = p->len;
	while(len > 0){
		int top = p->arr[0];
		p->arr[0] = p->arr[len-1];
		p->arr[len-1] = top;
		len = --p->len;
		heapify(p,0);
	}
	p->len = old_len;
	return;
}

void mergeheaps(PQ *p1, PQ *p2){
	int newlength = p1->len + p2->len;
	if(p1->cap < newlength){
		while(p1->cap < newlength){
			p1->cap = 2*p1->cap;
		}
		p1->arr = (int *)realloc(p1->arr, p1->cap * sizeof(int));
	}

	int i, j=p1->len;
	for(i=0; i< p2->len; i++){
		p1->arr[j+i] = p2->arr[i];
	}
	p1->len = newlength;
	for(i = (newlength-1)/2; i >= 0; i--){
		heapify(p1,i);
	}
}

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Usage: ./a.out <capacity of Prio Queue> <No. Of Elements to be copied>\n");
		return 0;
	}
	int i=0;
	PQ *p = (PQ *)malloc(sizeof(PQ));
	p->len = 0;
	p->cap = strtoimax(argv[1],NULL,10);
	int inp_size = strtoimax(argv[2],NULL,10);
	FILE *fd = fopen("init.txt","r");
	while(inp_size >= p->cap){
		p->cap = 2*p->cap;
	}
	p->arr = (int *)calloc(p->cap,sizeof(int));	
	int *array = (int *)calloc(inp_size,sizeof(int));

	while(fscanf(fd,"%d",&(array[i])) != EOF){
		i++;
	}
	p->len = i;
	build_heap(p,array);
	printf("%-15s: ","Input");
	printPQ(p);
//1. Heapify and print
	i = getParentIndex(p,p->len-1);
	while(i >= 0){
		heapify(p,i);	
		i--;	
	}
	printf("%-15s: ","Heapified");
	printPQ(p);
//2. Insert and print
	insert(p,10);
	printf("%-15s: ","Inserted 10");
	printPQ(p);
//3. Delete and print
	delete(p,9);
	printf("%-15s: ","Deleted 9");
	printPQ(p);

//4. Pre-Order Traversal
	printf("%-15s: ","PreOrder");
	preorder(p,0);
	printf("\n");
//5. Post-Order Traversal
	printf("%-15s: ","PostOrder");
	postorder(p,0);
	printf("\n");
//6. In-Order Traversal
	printf("%-15s: ","InOrder");
	inorder(p,0);
	printf("\n");

//{ Merge Two Heaps
	int array_2[5] = {20,21,22,23,24};
	PQ *p2 = (PQ *)malloc(sizeof(PQ));
	p2->cap = 5;
	p2->len = 5;
	p2->arr = (int *)malloc(sizeof(int)*p2->cap);
	build_heap(p2,array_2);
	mergeheaps(p,p2);
	printf("%-15s: ","Merged");
	printPQ(p);
//}	

// Heap Sort
	heapsort(p);
	printf("%-15s: ","Sorted");
	printPQ(p);
//Destroy Heap
	DeleteHeap(p);
}
