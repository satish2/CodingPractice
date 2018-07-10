#include <stdio.h>
#include <stdlib.h>
#define NEWLINE printf("\n");

typedef struct btnode {
	int data;
	struct btnode *left;
	struct btnode *right;
}tree_node;

typedef struct q_node {
	tree_node *data;
	struct q_node *next;
}node;

typedef struct queue{
	node *head;
	node *tail;
}Queue;

typedef struct st_node {
	tree_node *data;
	struct st_node *prev;	
}stack_node;

typedef struct stack {
	struct st_node *top;
}Stack;

int isEmptyStack(Stack *st){
	return (st->top == NULL);
}

void push(Stack *st, tree_node *data){
	stack_node *newnode = (stack_node *) malloc(sizeof(stack_node));
	newnode->data = data;
	newnode->prev = NULL;
	if(st->top == NULL){
		st->top = newnode;
		return;
	}
	newnode->prev = st->top;
	st->top = newnode;
	return;
}

tree_node *pop(Stack *st){
	if(st->top == NULL) return NULL;
	stack_node *tmp = st->top;
	tree_node *ret = tmp->data;
	st->top = tmp->prev;
	free(tmp);
	return ret;
}

void enqueue(Queue *q, tree_node *tnode){
	node *newnode = (node *)malloc(sizeof(node));
	newnode->data = tnode;
	newnode->next = NULL;
	if(q->head == NULL){
		q->head = q->tail = newnode;
		return;
	}
	q->tail->next = newnode;
	q->tail = newnode;
	return;
}

tree_node *dequeue(Queue *q){
	if(q->head == NULL){
		return NULL;
	}
	node *tmp = q->head;
	tree_node *ret = tmp->data;
	q->head = q->head->next;
	free(tmp);
	return ret;
}

int isEmpty(Queue *q){
	return (q->head == NULL);
}

Stack *CreateStack(){
	Stack *st = (Stack *)malloc(sizeof(Stack));
	st->top = NULL;
	return st;
}

Queue *CreateQueue(){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->head = q->tail = NULL;
	return q;
}

void printReverseLevelOrder(tree_node *root){
	Stack *st = CreateStack();
	Queue *q = CreateQueue();
	enqueue(q, root);
	enqueue(q, NULL);
	while(!isEmpty(q)){
		tree_node *tmp = dequeue(q);
		if(tmp == NULL){
			//level changed
			if(!isEmpty(q)){
				enqueue(q, NULL);
			}
		} else {
			push(st, tmp);
			if(tmp->left != NULL)			
				enqueue(q, tmp->left);
			if(tmp->right != NULL)			
				enqueue(q, tmp->right);
		}
	}
	while(!isEmptyStack(st)){
		printf("%d \t", pop(st)->data);
	}
	printf("\n");
	free(q);
	free(st);
}

void printPreOrder(tree_node *root){
	if(root == NULL) return;
	printf("%d\t", root->data);
	printPreOrder(root->left);
	printPreOrder(root->right);
	return;
}
/*--------------------------Following contains new code, above is same as the one in AllBinaryTree--------------*/

/*
 * 
 * Given PreOrder and Inorder traversal, construct binary tree 
 * prearray[0] -> root, in Inorder, left to indexofroot is left tree and to its right is righttree
 */

tree_node *makeTree(int *preorder, int *inorder, int prest, int preend, int inst, int inend){
	if(prest > preend || inst > inend) return NULL;
	tree_node *root = (tree_node *)malloc(sizeof(tree_node));
	root->left = root->right = NULL;
	root->data = preorder[prest];
	int offset = inst, root_inorder_index = 0;
	for(; offset < inend; offset++){
		if(inorder[offset] == root->data)
			break;
	}

	//inst to offset-1 marks left subtree, offset+1 to inend marks right subtree
	//Number of nodes in left subtree is (offset - inst)
	//NUmber of nodes in right subtree is (inend - offset)

	if(offset - inst > 0){
		root->left = makeTree(preorder, inorder, prest+1, prest + (offset - inst), inst, offset - 1);		
	}
	if(inend - offset > 0){
		root->right = makeTree(preorder, inorder, prest + (offset-inst + 1), preend, offset+1, inend);		
	}
	return root;
}

void VerticalSumInBinaryTree(tree_node *root, int level){
	if(root == NULL) return;
	hashtable[level] += root->data;
	VerticalSumInBinaryTree(root->left, level -1);
	VerticalSumInBinaryTree(root->right, level + 1);
}

int max (int a, int b){
	return a > b ? a : b;
}

int height(tree_node *root){
	if(root == NULL) return 0;
	return max(height(root->left), height(root->right)) + 1;
}

int diameterOfTree(tree_node *root){
	if(root == NULL) return 0;
	int ldia = diameterOfTree(root->left);
	int rdia = diameterOfTree(root->right);
	int lhei = height(root->left);
	int rhei = height(root->right);
	return max((lhei + rhei + 1), max(ldia,rdia));
}

int main(int argc, char **argv){
/*	int a = 0;
	printf("Location of a in stack = %x ", &a);
	printf("Location of argc = %x ", &argc);
	printf("Location of argv = %x", *argv);
	NEWLINE*/

	int preorder[11] = {0,1,3,7,8,4,9,10,2,5,6};
	int inorder[11] = {7,3,8,1,9,4,10,0,5,2,6};
	tree_node *root = makeTree(preorder, inorder, 0, 10, 0, 10);
	printf("pre-order :");	
	printPreOrder(root);
	NEWLINE	
	printf("Reverse Level Order :");
	printReverseLevelOrder(root);
	NEWLINE
	
	VerticalSumInBinaryTree(root,0);

	return 0;
}
