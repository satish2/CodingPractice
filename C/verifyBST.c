//verify is tree is BST ?
#include <stdio.h>
#define true 1
#define false 0
#define INTEGER_MIN 1<<31
static int flag = 0;
void isBST(bstnode *root){
	static int prev	= INTEGER_MIN;
	if(root){
		if(!isBST(root->left)) return false;
		if(root->data < prev) return false;
		prev = root;
		return isBST(root->right);
	}
	return true;
}

int main(int argc, char *argv[]){
	
	isBST(root);
	if(flag) printf("FALSE");
	else printf("TRUE");
}
/*
 * #include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
struct node
{
    int data;
    struct node* left;
    struct node* right;
};
 
int isBST(struct node* node) 
{ 
  return(isBSTUtil(node, INT_MIN, INT_MAX)); 
} 
 
int isBSTUtil(struct node* node, int min, int max) 
{ 
  if (node==NULL) 
     return 1;
       
  if (node->data < min || node->data > max) 
     return 0; 
 
  return
    isBSTUtil(node->left, min, node->data-1) &&  // Allow only distinct values
    isBSTUtil(node->right, node->data+1, max);  // Allow only distinct values
} 
 
struct node* newNode(int data)
{
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
 
  return(node);
}
 
int main()
{
  struct node *root = newNode(4);
  root->left        = newNode(2);
  root->right       = newNode(5);
  root->left->left  = newNode(1);
  root->left->right = newNode(3); 
 
  if(isBST(root))
    printf("Is BST");
  else
    printf("Not a BST");
     
  getchar();
  return 0;
}  
 */
