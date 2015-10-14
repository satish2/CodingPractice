//Implementing Queue with two stacks
#include <stdio.h>
#include <stdlib.h>
typedef struct _Node {
	int data;
	struct _Node *prev;
}node, Node;

typedef struct {
	Node *top;
	int length;
}Stack;

int pop(Stack *st){
	
	if(st->length == 0){
		return -1;
	}

	int ret = st->top->data;
	Node *tmp = st->top;
	st->top = tmp->prev;
	free(tmp);
	st->length--;
	return ret;
}

void push(Stack *st, int data){

	node *newNode = (node *)malloc(sizeof(node));
	newNode->data = data;
	newNode->prev = NULL;
	if(st->length == 0){
		st->top = newNode;
		st->length++;
		return;
	}
	newNode->prev = st->top;
	st->top = newNode;	
	st->length++;
	return;
}

void enqueue(Stack *pushStack, int data){
	push(pushStack, data);
}

int dequeue(Stack *popStack, Stack *pushStack){
	if(popStack->length == 0){
		while(pushStack->length != 0){
			int data = pop(pushStack);
			push(popStack, data);
		}
		return pop(popStack);
	}
	return pop(popStack);
}

int main(){
	
	Stack *stack1 = (Stack *)malloc(sizeof(Stack));
	Stack *stack2 = (Stack *)malloc(sizeof(Stack));
	stack1->top = NULL;
	stack1->length = 0;
	stack2->top = NULL;
	stack2->length = 0;
	int i = 0;	
	for(i=0; i<10; i++){
		enqueue(stack2, i);		
	}
	for(i=0; i<10; i++){
		printf("%d\t",dequeue(stack1, stack2));		
	}
	printf("\n");
	while(stack1->length != 0){
		pop(stack1);
	}
	while(stack2->length != 0){
		pop(stack2);
	}
	free(stack1);
	free(stack2);
}
