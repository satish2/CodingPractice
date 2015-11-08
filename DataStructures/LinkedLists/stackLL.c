#include <stdio.h>

struct stacknode{
	
	int value;
	struct stacknode *next;

}

int pop(struct **top){
	
	if(isEmptyStack(top)){
		return -1;
	}

	int value = *top->value;
	struct stacknode *temp;
	temp = *top;
	*top = *top->next;
	free(temp);
	return data;
}

int isEmptyStack(struct stacknode **top){
	return (*top == NULL);
}

int createStack(){
	return NULL;
}

int push(struct stacknode **top, int value){
	struct stacknode *newnode = (struct stacknode *)malloc(sizeof(stacknode));
	if(!newnode){
		return NULL;
	}
	newnode->value = value;
	newnode->next = *top;
	*top = newnode;
	return 0;
}

int deleteStack(struct stacknode **top){
	
	if(*top == NULL){
		return 0;
	}
	struct stacknode *temp;
	while(*top->next != NULL){
		temp = *top->next;
		*top->next = *temp->next;
		free(temp);
	}
	free(*top);
}

int top(struct stacknode **top){
	if(isEmptyStack(top)){
		return -1;
	}
	return *top->value;
}
