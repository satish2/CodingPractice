#include <stdio.h>

typedef struct dllnode {
	
	int value;
	struct dllnode *prev;
	struct dllnode *next;

}DLL_t;

int main (int argc, char* argv[]){
	
	//implement a doubly linked list
	int i = 0;
	scanf("%d", &i);	
	InsertDLLNode(&head,i);
}

struct clnode {
	
	int value;
	struct clnode *next;
}



InsertATendincll(struct clnode **head){
	
	struct clnode *newNode = (struct clnode *)malloc(sizeof(clnode));
	newNode->value = 10;
	newNode->next = newNode; //mistake
	if(*head == NULL){
		*head = newNode;
		return;
	}
	curr = *head;
	while (curr->next != *head){
		curr = curr->next;
	}
	curr->next = newNode;
	newNode->next = *head;
//	*head = newNode //This makes newNode beginning of cll and this inserting at the beginning of cll.
	return;
}

DeleteatendofCLL(struct clnode **head){
	struct cllnode *curr,*prev;
	if(*head == NULL){
		return;
	}
	curr = *head;
	while(curr->next != *head){
		prev = curr;
		curr = curr->next;
	}
	prev->next = *head;
	free(curr);
	//if deleting first node
	temp = *head;	
	curr->next = *head->next;
	*head = curr->next;
	free(temp);
}

void deleteDLLNode(struct dllnode **head, int pos){
	int k = 1;
	struct dllnode *curr,*temp;
	if(*head == NULL){
		return;
	} 
	if(pos == 1){
		free(*head);
		return;
	} else {
		curr = *head;
		while(k< pos -1 && (curr->next != NULL)){
			curr = curr->next;
			k++;
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
		return;
	}
}



void InsertDLLNode(struct dllnode **head, int pos) {
	
//	*head <-- it is head node
	int k = 1;
	struct dllnode *curr;
	struct dllnode *newNode = (struct dllnode *)malloc (sizeof(dllnode));
	newNode->value = 10;
	newNode->prev = NULL;
	newNOde->next = NULL;
	if(*head == NULL){
		*head = newNode;
		return;
	}
	if(pos == 1){
		newNode->next = *head;
		newNode->prev = NULL;
		*head->prev = newNode;
		*head = newNode;
	} else {
		curr = *head;
		while ( k < pos - 1 && (curr->next != NULL)){
			curr = curr->next;
			k++;
		}
		//once it reaches position 'pos', loop condition fails. 
		if(curr->next == NULL) { //end of linked list
			curr->next = newNode;
			newNode->prev = curr;
			newNode->next = NULL;
			return;
		} else { //in middle
			curr->next->prev = newNode;
			newNode->next = curr->next;
			newNode->prev = curr;
			curr->next = newNode;
			return;
		}
	}
}
