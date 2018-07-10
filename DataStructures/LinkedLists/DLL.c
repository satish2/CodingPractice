//Double Linked List
#include <stdio.h>
#include <stdlib.h>

typedef struct DLNode {
	struct DLNode *next;
	struct DLNode *prev;
	int value;
}dlnode;

int iter = 0;


void printDLL(dlnode **head){
	iter = 0;
	dlnode *curr = *head;
	while(curr != NULL){
		printf("%d \t",curr->value);
		curr = curr->next;
	}
	printf("\n");
}

//Go till the position of node to be deleted, once we have that node in curr, modify nodes on either sides.
void deleteDLL(dlnode **head, int pos){
	dlnode *curr = *head;
	dlnode *temp;
	if(!(*head)){
		printf("Invalid Linked List \n");
	}

	if(pos == 1){
		*head = curr->next;
		(*head)->prev = NULL;
		free(curr);
		return;
	} else {
		int i=1;
		for (i=1; i<(pos) && curr->next != NULL; i++){
			curr = curr->next;
		}
		if(curr->next == NULL){
			temp = curr->prev;
			temp->next = NULL;
			free(curr);
		} else {
			temp = curr->prev;
			temp->next = curr->next;
			curr->next->prev = temp;
			free(curr);
		}
	}
}

//Go till the position prior to the one give, there modift next pointers and adjacent nodes' pointers to have this value
void insertDLL(dlnode **head, int value, int pos){
	dlnode *newNode = (dlnode *)malloc(sizeof(dlnode));
	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	dlnode *b4pos = *head;
	if(!(*head)){
		*head = newNode;
		return; 
	}

	if(pos == 1){
		b4pos->prev = newNode;
		newNode->next = b4pos;
		*head = newNode;
		return;
	} else {
		int i=1;
		for (i=1;i<pos-1 && b4pos->next!=NULL; i++){
			b4pos = b4pos->next;
		}
		if(b4pos->next == NULL){
			b4pos->next = newNode;
			newNode->prev = b4pos;
			newNode->next = b4pos->next;
			return;
		} else {
			b4pos->next->prev = newNode;
			newNode->prev = b4pos;
			newNode->next = b4pos->next;
			b4pos->next = newNode;			
			return;
		}
	}
}

int main (int *argc, char **argv){
	int values[] = {1,2,3,4,5,6,7,8,9,10};
	dlnode *head = (dlnode *)malloc(sizeof(dlnode));
	dlnode *curr = head;
	dlnode *prev = NULL;
	for (iter=0;iter<10;iter++){
		curr->value = values[iter];
		if (iter==9){
			break;
		}
		curr->prev = prev;
		curr->next = (dlnode *)malloc(sizeof(dlnode));
		prev = curr;
		curr = curr->next;
	}
	printDLL(&head);
	insertDLL(&head,23,10);
	printDLL(&head);
	deleteDLL(&head,10);
	printDLL(&head);
	return 0;
}

