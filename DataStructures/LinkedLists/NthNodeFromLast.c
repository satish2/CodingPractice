#include <stdio.h>
#include "satish_sll.h"

lnode *findNthNodeFromLast(lnode *head, int pos);

int main (int argc, char *argv[]){
	
	int values[] = {1,2,3,4,5,6,7,8,9,10};
	int pos = 0;
	lnode *head = (lnode *)malloc(sizeof(lnode));
	makeLL(&head,values);
	printf("Enter position from lastNode value: ");
	scanf("%d",&pos);
	lnode *NthNodeFromLast = findNthNodeFromLast(head,pos);
	if(NthNodeFromLast != NULL)
		printf("%d\n", NthNodeFromLast->val);
	return 0;
}

//Here first Node from Last Node is the last node.
//What if 0th node from last should be last node, then ith node from last is (i+1)th node.
lnode *findNthNodeFromLast(lnode *head, int pos){
	if(pos == 0 || pos < 0){
		printf("Invalid Position\n");
		return NULL;
	}
	lnode *tmp, *nthpos;
	tmp = head;
	if(head == NULL){
		printf("invalid linked list");
		return NULL;
	}
	int count = 0;
	while(tmp!= NULL){
		count ++;
		tmp = tmp->next;
		if(pos - count == 0)
			nthpos = head;
		else if(pos - count < 0){
			nthpos = nthpos->next;
		}
	}
	if(nthpos)
		return nthpos;
}

lnode *findNthNodeFromLast_ZeroIndexing(lnode *head, int pos){
	lnode *tmp, *nthpos;
	tmp = head;
	if(head == NULL || pos < 0){
		printf("invalid linked list or invalid position");
		return NULL;
	}
	int count = 0;
	while(tmp!= NULL){
		tmp = tmp->next;
		if(pos - count == 0)
			nthpos = head;
		else if(pos - count < 0){
			nthpos = nthpos->next;
		}
		count ++;
	}
	if(nthpos)
		return nthpos;
}
