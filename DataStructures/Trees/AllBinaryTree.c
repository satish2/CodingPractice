#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	
#define MIN_VALUE -1000000
#define true 1
#define false 0
#define MAXOF(a,b) (((a) > (b)) ? (a) : (b))

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

int isLeftExists(int i, int limit){
	return (limit >= (2*i+1));
}

int isRightExists(int i, int limit){
	return (limit >= (2*i+2));
}

void makeTree(tree_node *root){
	int i = 0;
	int limit = 10;
	Queue *q = (Queue *)malloc(sizeof(Queue));
	if(!q) return;
	q->head = q->tail = NULL;
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
			if(isLeftExists(tmp->data, limit)){
				tmp->left = (tree_node *)malloc(sizeof(tree_node));
				tmp->left->left = NULL;
				tmp->left->right = NULL;
				tmp->left->data = ++i;//rand()%10;
				enqueue(q, tmp->left);
			}
			if(isRightExists(tmp->data, limit)){
				tmp->right = (tree_node *)malloc(sizeof(tree_node));
				tmp->right->left = NULL;
				tmp->right->right = NULL;
				tmp->right->data = ++i;//rand()%10;
				enqueue(q, tmp->right);
			}
		}
	}
	free(q);
}

void inorder_traversal(tree_node *root){
	if(root == NULL) return;
	inorder_traversal(root->left);
	printf("%d\t",root->data);
	inorder_traversal(root->right);
}

int find_max(tree_node *root){
	if(root == NULL) return MIN_VALUE;
	int max = root->data;
	int left = find_max(root->left);
	int right = find_max(root->right);
	if(max < left){
		max = left;
	}
	if(max < right){
		max = right;
	}
	return max;
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

void DeleteTree(tree_node *root){
	if(root == NULL) return;
	DeleteTree(root->left);
	DeleteTree(root->right);
	free(root);
	root = NULL;
}

int height_of_tree(tree_node *root){
	if(root == NULL) return 0;
	int leftHeight = height_of_tree(root->left);
	int rightHeight = height_of_tree(root->right);
	return MAXOF(leftHeight, rightHeight) + 1;
}

int isStructurallyIdentical(tree_node *root1, tree_node *root2){
	if(root1 == NULL && root2 == NULL) return true;
	if(root1 == NULL || root2 == NULL) return false;
	return isStructurallyIdentical(root1->left, root2->left) && isStructurallyIdentical(root1->right, root2->right);
}

/*Print All Paths from Root to Leaf - Karumanchi problem 20 (trees)*/
void printPaths(tree_node *root, int *paths, int level){
	paths[level] = root->data;
	if(root->left == NULL && root->right == NULL){
		int i = 0;
		printf("Path : ");
		for(; i <= level; i++){
			printf("%d\t", paths[i]);
		}
		printf("\n");
		return;
	}
	level++;
	printPaths(root->left, paths, level);
	printPaths(root->right, paths, level);
	return;
}

void printArray(int *paths, int sum, int stIndex, int endIndex){
	printf("Path with sum = %d is :", sum);
	int i = stIndex;
	for(; i<= endIndex; i++) printf("%d\t",paths[i]);
	printf("\n");
}

void PrintAllPathExists(tree_node *root, int *paths, int level, int sum){
	if(root == NULL) return;
	paths[level] = root->data;
	int i = level, tmp_sum = 0;
	for(; i>= 0; i--){
		tmp_sum += paths[i];
		if(tmp_sum == sum){
			printArray(paths, sum, i, level);
		}
	}
	level++;
	PrintAllPathExists(root->left, paths, level, sum);
	PrintAllPathExists(root->right, paths, level, sum);
}

int isPathWithSumExists(tree_node *root, int sum){
	if(root == NULL) {
		return (sum == 0);
	}
	return isPathWithSumExists(root->left, (sum - root->data)) || isPathWithSumExists(root->right, (sum - root->data));
}

void printAllPathsToLeaf(tree_node* root){
	if(root == NULL) return;
	printf("All Paths to Leaf\n");
	int height = height_of_tree(root);
	int *paths = (int *)malloc(sizeof(int)*height);
	printPaths(root, paths, 0);
	printf("Path with sum = 11 starting from root till a leaf exists ? %d\n",isPathWithSumExists(root, 11));
	PrintAllPathExists(root, paths, 0 ,4);
	free(paths);
	return;
}

void MakeAMirror(tree_node *root1, tree_node *root3){
	if(root1 == NULL) return;
	root3->data = root1->data;

	if(root1->right != NULL){
		root3->left = (tree_node *)malloc(sizeof(tree_node));
		root3->left->data = root1->right->data;
		root3->left->left = NULL;
		root3->left->right = NULL;
		MakeAMirror(root1->right, root3->left);
	} 
	if(root1->left != NULL){
		root3->right = (tree_node *)malloc(sizeof(tree_node));
		root3->right->data = root1->left->data;
		root3->right->left = NULL;
		root3->right->left = NULL;
		MakeAMirror(root1->left, root3->right);
	}
}

int diameterOfTree(tree_node *root){
	if(root == NULL) return 0;
	int ldiameter = diameterOfTree(root->left);
	int rdiameter = diameterOfTree(root->right);
	int lHeight = height_of_tree(root->left);
	int rHeight = height_of_tree(root->right);
	return MAXOF((lHeight + rHeight + 1), MAXOF(ldiameter, rdiameter));
}

tree_node *findLCA(tree_node *root, tree_node *node1, tree_node *node2){
	if(root == NULL) return NULL;
	if(root == node1 || root == node2) return root;
	tree_node *left = findLCA(root->left, node1, node2);
	tree_node *right = findLCA(root->right, node1, node2);
	if(left && right) return root;
	else return (left != NULL ? left : right);
}

void printPreOrder(tree_node *root){
	if(root == NULL) return;
	printf("%d\t", root->data);
	printPreOrder(root->left);
	printPreOrder(root->right);
	return;
}

int main(int argc, char **argv){
	srand(time(NULL));
	tree_node *root = (tree_node *)malloc(sizeof(tree_node));
	root->data = 0;//rand()%10;
	makeTree(root);
	printf("PreOrder:");
	printPreOrder(root);
	printf("\n");

	printf("Inorder traversal: ");
	inorder_traversal(root);
	printf("\n");
/*	printf("Max in tree = %d\n",find_max(root));
	printf("Reverse Level Order :");
	printReverseLevelOrder(root);
	printf("Height of tree = %d\n",height_of_tree(root));
*/
	tree_node *root1 = root;
	tree_node *root2 = (tree_node *)malloc(sizeof(tree_node));
	root2->left = root2->right = NULL;
	root2->data = 0;
	makeTree(root2);
	printf("Are they structurally identical = %d\n",isStructurallyIdentical(root1, root2));

	tree_node *root3 = (tree_node *)malloc(sizeof(tree_node));
	root3->left = root3->right = NULL;
	MakeAMirror(root1, root3);

	printf("Inorder traversal of Mirrored Tree :");
	inorder_traversal(root3);
	printf("\n");

	printf("Diameter of tree = %d\n", diameterOfTree(root1));
	printAllPathsToLeaf(root1);

	DeleteTree(root1);
	DeleteTree(root2);
	DeleteTree(root3);

	return 0;
}
