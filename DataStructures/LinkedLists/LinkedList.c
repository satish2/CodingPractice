#include <stdio.h>
#include "satish.h"

#define UNSWAPPED 0
#define SWAPPED 1

void swapNode(struct node *node1, struct node *node2);
int compare(struct node *node1, struct node *node2);

struct node* makeLinkedList(int *values) {

	struct node *head=NULL, *prev=NULL, *current=NULL;
	
	while (*values != NULL) {
		printf("making LinkedList \n");
		current = (node_t*) malloc(sizeof(node_t));
		if (prev != NULL)
			prev->next = current;
		else
			head = current;
			
		current->data = *values;
		current->next = NULL;
		prev = current;
		values++;
	}
	return head;
}

void printLinkedList(struct node *head) {
	if (head == NULL) {
		printf("Invalid Linked List");
		return;
	}
	struct node *current = head;
	while (current != NULL) {
		printf("%d\n", current->data);
		current = current->next;
	}
}

struct node* sortLinkedList(struct node *head){
	
	if(head == NULL)
		return NULL;
	
	/*
	 * Current NOde..
	 * head Node.. 
	 * compare all value with head node. Always head is assumed to be min node.
	 */
	
}	

int compare(struct node *node1, struct node *node2){
	printf("Comparing %d and %d ",node1->data, node2->data);
	if(node1->data > node2->data){
		printf("returning -1\n");
		return -1;
	}
		
	else if(node1->data <= node2->data){
		printf("returning 0\n");
		return 0;
	}

}

void swapNode(struct node *node1, struct node *node2){
	struct node *temp;
	temp = node2->next;
	node2->next = node1;
	node1->next = temp;
}
