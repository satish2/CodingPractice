//Circular Linked List
#include <stdio.h>
#include <stdlib.h>

/*
 * 1. Print length of CLL
 * 2. Print elements of CLL
 * 3. Insert at the end and also beginning of CLL
 * 4. Delete at the end and also beginning of CLL
*/

typedef struct CLNode{
	int val;	
	struct CLNode *next;
}clnode;

void insertCLL(clnode **head, int val, int pos){
	clnode *newNode = (clnode *)malloc(sizeof(clnode));
	newNode->val = val;
	newNode->next = NULL;
	clnode *lastNode;
	clnode *curr = *head;
	int length = 1;
	do {
		curr = curr->next;
		length++;
	}while(curr->next != *head);
	lastNode = curr;
	if(pos == 1){
		newNode->next = *head;
		lastNode->next = newNode;
		*head = newNode;
	} else {
		curr = *head;
		int i = 1;
		for (i=1; i<pos-1 && i<=length;i++){
			curr = curr->next;
		}
		clnode *tmp = curr->next;
		curr->next = newNode;
		newNode->next = tmp;
	}
}

void deleteCLL(clnode **head, int pos){

	if (!(*head)){
		printf("invalid CLL");
		return;
	}
	int length = 1;
	clnode *lastNode, *curr;
	curr = *head;
	do {
		curr = curr->next;
		length++;
	}while(curr->next != *head);
	lastNode = curr;
	if (pos == 1){
		curr = *head;
		lastNode->next = curr->next;
		*head = curr->next;
		free(curr);
		return;
	} else {
		int i = 1;
		curr = *head;
		for (i=1; i<(pos-1) && i<length;i++){
			curr = curr->next;
		}
		//delete curr->next;
		clnode *tmp2 = curr->next;
		clnode *tmp = tmp2->next;
		curr->next = tmp;
		free(tmp2);
		return;
	}
	
}

void makeCLL(clnode **head, int count, int *values){
	clnode *curr = *head;
	int i = 0;
	for(i=0; i<count; i++){
		curr->val = values[i];
		if(i+1 != count){
			curr->next = (clnode *)malloc(sizeof(clnode));
			curr = curr->next;
		}	
	}
	curr->next = *head;	
}

void printCLL(clnode **head){
	clnode *curr = *head;
	int length = 0;
	do {
		printf("%d \t",curr->val);
		curr = curr->next;
		length++;
	} while(curr != *head);		
	printf("\nLength = %d\n", length);
	return;	
}

int main (int argc, char *argv[]){
	int values[] = {1,2,3,4,5,6,7,8,9,10};
	clnode *head = (clnode *)malloc(sizeof(clnode));
	makeCLL(&head,10,values);
	printCLL(&head);
	insertCLL(&head,23,11);
	printCLL(&head);
	deleteCLL(&head,1);
	printCLL(&head);
}
