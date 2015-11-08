#include <stdio.h>
#include "satish.h"


int main (int argc, char* argv){
	int values[] = {4,3,2,5,7,1,9,8,6,10};
	struct node *head = makeLinkedList(values);
	printf("Done making Linked Lit \n");
	printLinkedList(head);
	struct node *newHead = sortLinkedList(head);
	printLinkedList(newHead);
}
