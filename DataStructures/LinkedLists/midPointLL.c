#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	struct _node *next;
	int data;	
}Node;

findMidLL(Node *head){
	if(head == NULL) return;
	Node *slow = head, *fast = head;
	while(fast != NULL){
		fast = fast->next;
		if(fast == NULL) break;
		fast = fast->next;
		if(fast == NULL) break;
		slow = slow->next;
	}
	return slow->data;
}

int main(int argc, char *argv[]){
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	Node *head = (Node *)malloc(sizeof(Node));
	head->data = arr[0];
	int i = 1;
	Node *curr = head;
	while(i<=9){
		curr->next = (Node *)malloc(sizeof(Node));
		curr = curr->next;
		curr->data = arr[i];
		i++;
	}
	printf("%d\n",findMidLL(head));
}
