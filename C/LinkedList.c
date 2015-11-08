#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define concat(a,b) a#b

//void mergeSort(struct node *);
//void quickSort(struct node *);
//void selectionSort(struct node *);

struct node {

 struct node *next;
 struct node *prev;
 int value;
 char *name;
};


void insertionSort(struct node *head){

	int a[10] = {10,9,8,7,6,5,4,3,2,1};
	int i=0,j=0;
	for (i=1; i<10;i++){
	 j = i;
	 if(a[j] < a[j-1]){
	 	int temp = a[j];
	 	while(temp < a[j-1]){
			a[j] = a[j-1];
			j--;
		 	}
		 a[j] = temp;	
		}
	}
	
	for(i=0;i<10;i++){
		printf("%d\t",i);
	}
	printf("\n");
}

void mergeSort(int *a, int low,int high, int *b){
	
	int i=0;
	if(high-low >= 1) {
		mergeSort(a,low,(low+high)/2,b);
		mergeSort(a,(low+high)/2+1,high,b);
	}
	merge(*a,low,high,(low+high)/2);
}

void merge(int *a,int low,int high, int mid, int *b){
	while(low < mid) {
		if(a[low] > a[mid+1]){
							
		}	
	}
}

int main(int argc, char *argv[]){

	struct node *head;
	char defaultname[10] = "hello";
	char *temp = (char *) malloc(10*sizeof(char));
	int i=0;

	head = (struct node *) malloc(sizeof(struct node));
	struct node *root = head;
	head->next = 0;
	head->prev = 0;
	head->value = 0;
	head->name = (char *) malloc(10*sizeof(char));
	strcpy(head->name,defaultname);
	printf("value = %d \n", head->value);

	for (i=1; i< 10; i++){
		head->next = (struct node *) malloc(sizeof(struct node));

		head->next->name = (char *) malloc(100*sizeof(char));
		head->value = 10-i;
		sprintf(temp,"%d",i);
		head->next->name = strcat(defaultname,temp);
		head->next->prev = head;

		head = head->next;
	}

	while(root->next != NULL){
		printf("value = %d \n",root->value);
		root = root->next;
	}
	insertionSort(head);
	int a[10] = {10,9,8,7,6,5,4,3,2,1};
	int b[10];
	mergeSort(a,0,9,b);
}
