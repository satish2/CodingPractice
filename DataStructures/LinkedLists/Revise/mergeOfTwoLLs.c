//Find merging point of two linkedlists
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *next;
}Node;

typedef struct _stackNode {
	Node *node;
	struct _stackNode *next;
}stacknode;

typedef struct _stack {
	stacknode *top;
	int length;
}Stack;

void push(Stack *stack, Node *node){
		stacknode *newnode = (stacknode *)malloc(sizeof(stacknode));
		newnode->node = node;
		newnode->next = NULL;
		if(stack->top == NULL){
			stack->top = newnode;
		} else {
			newnode->next = stack->top;
			stack->top = newnode;
		}
		stack->length++;
}

Node* pop(Stack *stack){
		if(stack->length == 0){
			return NULL;
		}
		stacknode *ret = stack->top;
		stack->top = ret->next;
		stack->length--;
		return ret->node;
}

void findMergeLL(Node *head1, Node *head2){
	Stack *stack1 = (Stack *)malloc(sizeof(Stack));
	stack1->top = NULL;
	stack1->length = 0;

	Stack *stack2 = (Stack *)malloc(sizeof(Stack));
	stack2->top = NULL;
	stack2->length = 0;

	Node *curr = head1;
	while(curr){
		push(stack1, curr);
		curr = curr->next;
	}
	curr = head2;
	while(curr){
		push(stack2, curr);
		curr = curr->next;
	}

	Node *prev=NULL, *pop1, *pop2;
	pop1 = pop(stack1);
	pop2 = pop(stack2);
	printf("pop1 value = %d, pop2 value = %d\n",pop1->data, pop2->data);
	while(pop1 == pop2){
		prev = pop1;
		pop1 = pop(stack1);
		pop2 = pop(stack2);
	}
	if(prev!= NULL){
		printf("Node at which both linkedlists merge = %d\n", prev->data);
		printf("Different Nodes ll1 = %d, ll2 = %d\n",pop1->data, pop2->data);
	}
	else
		printf("Node at which both linkedlists merge is None\n");
}


int main(int argc, char *argv[]){
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	int arr_1[10] = {11,12,13,14,15,16,17,18,19,20};
	Node *head1 = (Node *)malloc(sizeof(Node));
	Node *head2 = (Node *)malloc(sizeof(Node));
	Node *curr = head1;
	Node *merged;
	int i = 0;
	while(1){
		curr->data = arr[i];

		i++;
		if(i == 10)
			break;

		if(i == 5){
			merged = curr;
			printf("Merged Value after condition = %d\n",merged->data);
		}

		Node* newnode = (Node *)malloc(sizeof(Node));
		newnode->next = NULL;

		curr->next = newnode;
		curr = curr->next;
	}

	curr = head2;
	i = 0;
	while(1){
		curr->data = arr_1[i];
		i++;
		if(i == 10)
			break;
		Node* newnode = (Node *)malloc(sizeof(Node));
		newnode->next = NULL;
		curr->next = newnode;
		curr = curr->next;
	}
	printf("Merged Value = %d\n",merged->data);
	Node *curr2 = merged;
	printf("CHECK:: Merged Next Value = %d\n",curr2->next->data);
	if(curr2){
		curr->next = curr2;
	}
	findMergeLL(head1, head2);
}
