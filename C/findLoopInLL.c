//
#include <stdio.h>
#include <stdlib.h>
typedef struct llnode {
	int data;
	struct llnode *next;
}node;

int findLoop(node *head){
	
	node *slow = head, *fast = head;
	while(fast){
		if(fast->next)
			fast = fast->next->next;
		else
			return 0;
		slow = slow->next;
		if(!fast && fast == slow) return 1;
	}
	if(!fast) return 0;
}

int main(){
	node *head = (node *)malloc(sizeof(node));
	findLoop(head);
}
