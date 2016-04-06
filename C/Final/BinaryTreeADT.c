//BinaryTreeADT.c

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef struct _node {
	int data;
	struct _node *left;
	struct _node *right;
}btnode;

typedef struct _qnode {
	btnode *data;
	struct _qnode *next;
}qnode;

typedef struct _q{
	qnode *head;
	qnode *tail;
}Queue;

Queue *CreateQueue(){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	if(!q) return NULL;
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void enqueue(Queue *q, btnode *node){
	qnode *newnode = (qnode *)malloc(sizeof(qnode));
	newnode->data = node;
	newnode->next = NULL;
	if(q->head == NULL){
		q->head = q->tail = newnode;
		return;
	}
	q->tail->next = newnode;
	q->tail = newnode;
	return;	
}

btnode *dequeue(Queue *q){
	if(q->head == NULL) return NULL;
	qnode *tmp = q->head;
	q->head = q->head->next;
	btnode *ret = tmp->data; 
	free(tmp);
	return ret;
}

int isEmpty(Queue *q){
	if(q->head == NULL) return true;
	return false;
}

btnode *add(btnode *root, int data){
	btnode *newnode = (btnode *)malloc(sizeof(btnode));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	if(root == NULL){
		return newnode;
	}
	Queue *q = CreateQueue();
	enqueue(q, root);
	while(!isEmpty(q)){
		btnode *tmp = dequeue(q);
		if(!tmp->left){
			tmp->left = newnode;
			break;
		}  
		if(!tmp->right){
			tmp->right = newnode;
			break;
		} 
		enqueue(q, tmp->left);
		enqueue(q, tmp->right);
	}
	while(!isEmpty(q)){
		dequeue(q);
	}
	free(q);
	return root;
}

void printTree(btnode *root){
	if(root == NULL) return;
	printTree(root->left);
	printf("%d\t", root->data);
	printTree(root->right);
}

btnode *findNode(btnode *root, int value){
	Queue *q = CreateQueue();
	enqueue(q, root);
	btnode *tmp = NULL;
	while(!isEmpty(q)){
		tmp = dequeue(q);
		if(tmp->data == value) break;
		if(tmp->left)
			enqueue(q, tmp->left);
		if(tmp->right)
			enqueue(q, tmp->right);
		tmp = NULL;
	}
	while(!isEmpty(q)){
		dequeue(q);
	}
	free(q);
	return tmp;
}

btnode *findParent(btnode *root, int value, int *isLeft){
	if(root->data == value) return NULL;
	btnode *parent = NULL;
	Queue *q = CreateQueue();
	enqueue(q, root);
	while(!isEmpty(q)){
		btnode *tmp = dequeue(q);
		if(tmp->left && tmp->left->data == value) {
			parent = tmp;
			*isLeft = 1;
			break;
		}
		if(tmp->right && tmp->right->data == value) {
			parent = tmp;
			break;
		}
		if(tmp->left) enqueue(q, tmp->left);	
		if(tmp->right) enqueue(q, tmp->right);
	}
	while(!isEmpty(q)){
		dequeue(q);
	}
	free(q);
	return parent;
}

void deleteTree(btnode *root){
	if(!root) return;
	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
}

int isLeaf(btnode *node){
	return (node->left == NULL && node->right == NULL);
}

int isHalfNode(btnode *node){
	return (node->left == NULL && node->right != NULL) ||  (node->left != NULL && node->right == NULL);
}

btnode *deleteNode(btnode *root, int value){
	int isLeft = 0;
	btnode *victim = findNode(root, value);
	btnode *vic_parent = findParent(root, value, &isLeft);
	if(victim == NULL) return root;
	else if (victim == root && isLeaf(victim)){
		free(victim);
		return NULL;
	} else if (victim == root && isHalfNode(victim)){
		if(victim->left) root = victim->left;
		else root = victim->right;
		free(victim);
		return root;
	} else if(isHalfNode(victim)){
		if(victim->left) {
			if(isLeft) vic_parent->left = victim->left;
			else vic_parent->right = victim->left;
		} else {
			if(isLeft) vic_parent->left = victim->right;
			else vic_parent->right = victim->right;
		}
		free(victim);
		return root;
	} else if (isLeaf(victim)){
		printf("\nClearing leaf with parent %d\n", vic_parent->data);
		if(isLeft) vic_parent->left = NULL;
		else vic_parent->right = NULL;
		free(victim);
		return root;
	}

	Queue *q = CreateQueue();
	enqueue(q, root);
	btnode *tmp = NULL;
	while(!isEmpty(q)){
		tmp = dequeue(q);
		if(tmp->left) enqueue(q, tmp->left);
		if(tmp->right) enqueue(q, tmp->right);
	}
	free(q);
	int isLeftLastNode = 0;
	btnode *lastnode = tmp;
	btnode *lastnodeparent = findParent(root, tmp->data, &isLeftLastNode);
	if (lastnodeparent == victim){
		lastnode->left = victim->left;
		free(victim);
		if(vic_parent == NULL){
			root = lastnode;
		} else {
			if(isLeft) vic_parent->left = lastnode;
			else vic_parent->right = lastnode;
		}
	} else {
		lastnode->left = victim->left;
		lastnode->right = victim->right;
		free(victim);
		if(vic_parent == NULL){
			root = lastnode;
		} else {
			if(isLeft) vic_parent->left = lastnode;
			else vic_parent->right = lastnode;
		}
		if(isLeftLastNode) lastnodeparent->left = NULL;
		else	lastnodeparent->right = NULL;			
	}
	return root;
}

void printLevelOrderTraversal(btnode *root){
	if(root == NULL) return;
	printf("Level order Traversal: \n");
	Queue *q = CreateQueue();
	enqueue(q, root);
	enqueue(q, NULL);
	while(!isEmpty(q)){
		btnode *tmp = dequeue(q);
		if(tmp == NULL){
			if(!isEmpty(q)){
				printf("\n");
				enqueue(q, NULL);
			}
		} else {
			printf("%d\t", tmp->data);
			if(tmp->left) enqueue(q, tmp->left);
			if(tmp->right) enqueue(q, tmp->right);			
		}
	}
	printf("\n");
}

int main(int argc, char **argv){
	btnode *root = NULL;
	int i = 0;
	for(i=0; i< 10; i++){
		root = add(root, i);
	}
	printLevelOrderTraversal(root);
	root = deleteNode(root,4);
	printLevelOrderTraversal(root);
	root = deleteNode(root,3);
	printLevelOrderTraversal(root);
	root = deleteNode(root,7);
	printLevelOrderTraversal(root);
	root = deleteNode(root,1);
	printLevelOrderTraversal(root);
	root = deleteNode(root,0);
	printLevelOrderTraversal(root);
	root = deleteNode(root,6);
	printLevelOrderTraversal(root);
	root = deleteNode(root,2);
	printLevelOrderTraversal(root);
	root = deleteNode(root,9);
	printLevelOrderTraversal(root);
	root = deleteNode(root,5);
	printLevelOrderTraversal(root);
	root = deleteNode(root,8);
	printLevelOrderTraversal(root);
	deleteTree(root);
	printf("\n");
	return 0;
}
