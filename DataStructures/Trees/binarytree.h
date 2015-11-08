typedef struct _tree {
	int val;	
	struct _tree *left;
	struct _tree *right;
}tree;

typedef struct _StackNode {
	tree *val;
	struct _StackNode *prev;
}StackNode;

typedef struct _Stack {
	StackNode *top;
	int length;
}Stack;

int push(Stack *st, tree *t){

	if(t == NULL){
		return -1;
	}
	StackNode *n = (StackNode *)malloc(sizeof(StackNode));
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
	StackNode *temp = st->top;
	st->top = st->top->prev;
	free(temp);
	st->length--;
	return ret;
}

int isEmptyStack(Stack *st){
	if(st->top == NULL)
		return 1;
	return 0;
}

void inorder_nonrecursive(tree *root){
	//Left, Center, Right
	Stack *st = (Stack *)malloc(sizeof(Stack));
	st->length = 0;
	st->top = NULL;
	push(st,root);
	tree *temp = pop(st);	
	while(1){
		if(temp){
			push(st,temp);
			temp = temp->left;
		} else {
			if(isEmptyStack(st))
				return;

			temp = pop(st);
			printf("%d ", temp->val);
			if(temp->right != NULL){
				temp = temp->right;
			} else if (isEmptyStack(st)) {
				return;
			} else if(temp->right == NULL){
			
				temp = pop(st);
				printf("%d ",temp->val);
				temp = temp->right;
			}
		}
	}
	
}

/*This taken from Karumanchi*/
void postorder_nonrecursive(tree *root){
	
	Stack *st = (Stack *)malloc(sizeof(Stack));
	st->top = NULL;
	st->length = 0;
	while(1){
		if(root){
			push(st,root);
			root = root->left;
		} else {
			if(isEmptyStack(st)){
				return;
			} else if(st->top->val->right == NULL){
				root = pop(st);
				printf("%d ",root->val);
				if(root == st->top->val->right){
					printf("%d ", st->top->val->val);
					pop(st);
				}
			}
			if(!isEmptyStack(st)){
				root = st->top->val->right;
			} else
				root = NULL;
		}
	}
	free(st);
	st= NULL;
	return;
}

void preorder_nonrecursive(tree *t){
	//Center, Left, Right
	Stack *st = (Stack *)malloc(sizeof(Stack));
	st->top = NULL;
	st->length = 0;
	push(st,t);
	while(!isEmptyStack(st)){
		tree *temp = pop(st);
		printf("%d ",temp->val);		
		tree *left = temp->left;
		tree *right = temp->right;
		push(st,right);
		push(st,left);
	}
	free(st);
	st = NULL;
	return;
}
