#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JUSTINTRO printf("Takes an array with values 1,2,3,4,5 and initial tree with just root (0),\nprints \
preorder, postorder, inorder and levelorder traversals \n ******************\n");
#define INORDER printf("%-15s:","inorder");
#define PREORDER printf("%-15s:","preorder");
#define POSTORDER printf("%-15s:","postorder");
#define LEVELORDER printf("%-15s:","levelorder");

typedef struct _tree {
	int val;	
	struct _tree *left;
	struct _tree *right;
}tree;

typedef struct _Node {
	tree *treeNode;
	struct _Node *next;
}Node;

typedef struct _Queue{
	Node *head;
	Node *tail;
	int length;
}Queue;

int enqueue(Queue *q, tree *val){
	if(val == NULL)
		return -1;

	Node *n = (Node *)malloc(sizeof(Node));
	if(n == NULL){
		printf("Enqueue Failed\n");
		return -1;
	}
	n->treeNode = val;
	n->next = NULL;
	if(q->length == 0){
		q->head = q->tail = n;
		q->length++;
		return 0;
	}
	
	q->tail->next = n;
	q->tail = n;
	q->length++;
	return 0;
}

tree *dequeue(Queue *q){
	if(q->length == 0){
		return NULL;
	}
	Node *temp = q->head;
	tree *t = temp->treeNode;
	q->head = temp->next;
	q->length--;
	if(q->length == 0){
		q->head = q->tail = NULL;
	}

	free(temp);
	temp = NULL;
	return t;
}

int isEmpty(Queue *q){
	if(q->head == NULL){
		return 1;
	}
	return 0;
}

void levelOrder(tree *t){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->length = 0;
	q->head = q->tail = NULL;
	enqueue(q, t);
	while(!isEmpty(q)){
		tree *temp = dequeue(q);
		enqueue(q,temp->left);
		enqueue(q,temp->right);
		printf("%d ",temp->val);
	}
	free(q);
	q = NULL;
	return;
}

void preOrder(tree *t){
	//Center, Left, Right
	if(t){
		printf("%d ", t->val);
		preOrder(t->left);
		preOrder(t->right);
	}
	return;
}

void postOrder(tree *t){
	//Center, Left, Right
	if(t){
		postOrder(t->left);
		postOrder(t->right);
		printf("%d ", t->val);
	}
	return;
}

void inOrder(tree *t){
	//Center, Left, Right
	if(t){
		inOrder(t->left);
		printf("%d ", t->val);
		inOrder(t->right);

	}
	return;
}

void DeleteTree(tree *t){
	if(t == NULL){
		return;
	}
	DeleteTree(t->left);
	DeleteTree(t->right);
	free(t);
	t = NULL;
	return;
}

/*typedef struct _Node {
	tree *val;
	struct _Node *prev;
}Node;

typedef struct _Stack {
	Node *top;
	int length;
}Stack;

int push(Stack *st, tree *t){
	Node *n = (Node *)malloc(sizeof(Node));
	if(n == NULL){
		return -1;
	}
	n->val = t;
	n->prev = NULL;
	if(st->length == 0){
		st->top = n;
		st->length++;
		return 0;
	}
	n->prev = st->top;
	st->top = n;
	st->length++;
	return 0;
}

tree *pop(Stack *st){
	if(st->length == 0){
		return NULL;
	}
	tree *ret = st->top->val;
	Node *temp = st->top;
	st->top = st->top->prev;
	free(temp);
	st->length--;
	return ret;
}*/

void BuildTree(tree *tr, int *arr, int i, int N){
	//1 .Tree specifically does not have any rule. Can insert value at any place
	//2. For complete tree. 
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->length = 0;
	q->head = q->tail = NULL;
	tree *left, *right;
	while(i<N && tr!= NULL){
		left = (tree *)malloc(sizeof(tree));
		left->left = NULL;
		left->right = NULL;
		left->val = arr[i];
		tr->left = left;
		enqueue(q,left);
		if(i+1 < N){
			i++;
			right = (tree *)malloc(sizeof(tree));
			right->left = NULL;
			right->right = NULL;
			right->val = arr[i];
			tr->right = right;
			enqueue(q,right);
		}
		i++;
		tr = dequeue(q);
	}
	while(!isEmpty(q))
		dequeue(q);
	free(q);
	q = NULL;
}

int main(int argc, char *argv[]){
	tree *tr = (tree *)malloc(sizeof(tree));
	tr->left = NULL;
	tr->right = NULL;
	tr->val = 0;
	int arr[] = {1,2,3,4,5};
	BuildTree(tr,arr,0,5);

	JUSTINTRO

	PREORDER
	preOrder(tr);
	printf("\n");

	POSTORDER
	postOrder(tr);
	printf("\n");

	INORDER
	inOrder(tr);
	printf("\n");

	LEVELORDER
	levelOrder(tr);
	printf("\n");


	DeleteTree(tr);
}
