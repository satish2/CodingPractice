//get inorder successor of a node in tree
#include <stdio.h>
#include <stdlib.h>

bstnode *findNode(bstnode *root, int value){
	if(root == NULL) return NULL;
	if(root->data == value) return root;
	else if (root->data < value) return findNode(root->right, value);
	else return findNode(root->left, value);
}

bstnode *findMin(bstnode *root){
	if(root == NULL) return NULL;
	bstnode *temp = root;
	while(temp->left){
		temp = temp->left;
	}
	return temp;
}

bstnode *getSuccessor(bstnode *root, int value){
	bstnode *dst = findNode(root, value);
	if(dst == NULL) return NULL;
	if(dst->right) return findMin(dst->right);
	bstnode *prev = NULL, *temp = root;
	while(temp != NULL){
		if(temp->data > value){
			prev = temp;
			temp = temp->left;
			continue;
		}
		if(temp->data == value) break;
		temp = temp->right;
	}
	if(!prev) return prev;
	else return NULL;
}
