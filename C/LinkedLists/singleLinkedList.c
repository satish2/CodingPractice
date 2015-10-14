//Single Linked Lists.
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	struct ListNode *next;
	int val;
}lnode;

//whose length is unknown
void makeLL(lnode **head, int *values){
	lnode *curr = *head;
	int i = 0;
	for (i=0; i<10;i++){
		curr->val = values[i];
		if(i==9){
			break;
		}
		curr->next = (lnode *) malloc(sizeof(lnode));
		curr = curr->next;
	}
	curr->next = NULL;
}

void printLL(lnode **head){
	lnode *curr = *head;
	int i = 0;
	while(curr!=NULL){
		printf("%d \t",curr->val);
		curr = curr->next;
	}
	printf("\n");
}

//insert_node_LL,delete_node_LL
void insertLL(lnode **head, int value, int position){
	lnode *newnode = (lnode *)malloc(sizeof(lnode));
	newnode->val = value;
	if(!newnode){
		printf("Memory Error, could not create newnode");
		return;
	}
	if(position == 1){ //head Node
		newnode->next = *head;
		head = &newnode;
	} else {
		int i = 0;
		lnode *prev, *curr;
		curr = *head;
		for (i=0; i<position-1 && curr!=NULL;i++){
			prev = curr;
			curr = curr->next;
		}
		if(curr == NULL) { //reached last node
			prev->next = newnode;
			newnode->next = NULL;
		} else {
			prev->next = newnode;
			newnode->next = curr;
		}
	}
}

void deleteLL(lnode **head, int position){
	lnode *prev,*curr;
	curr = *head;
	if(curr == NULL){
		printf("list is empty\n");
	}
	if(position == 1){ //removing head node
		*head = curr->next;
		free(curr);
	} else {
		int i=0;
		for (i=0;i<position-1 && curr != NULL;i++){
			prev = curr;
			curr = curr->next;
		}
		if(curr == NULL){
			printf("position does not exist\n");
		} else {
			prev->next = curr->next;
			free(curr);
		}
	}
}

int main (int argc, char *argv){
	int values[] = {1,2,3,4,5,6,7,8,9,10};
	lnode *head = (lnode *) malloc(sizeof(lnode));
	makeLL(&head,values);
	printLL(&head);
	insertLL(&head,23,4);
	printf("after inserting	 \n");
	printLL(&head);
	deleteLL(&head,4);
	printf("after deleting \n");
	printLL(&head);
	return 0;
}
