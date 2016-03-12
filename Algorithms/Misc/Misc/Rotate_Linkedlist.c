
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}NODE;

void main(){

    NODE *head,*current,*prevNode;
    int n,i;
    printf("tell total number of nodes to be created\n");
    scanf("%d",&n);
    head = (NODE *)malloc(sizeof(NODE));
    head->value = 0;
    current = head;
    for (i = 1 ;i<n;i++){
            NODE *n1;
            n1 =(NODE *)malloc(sizeof(NODE));
            current->next = n1;
            n1->value= i;
            current = n1;
    }
    current->next = NULL;

    current = head;
    while(current->next!=NULL){
            printf("%d",current->value);
            prevNode = current;
            current = current->next;
            printf("prevNode = %d , currentNode = %d\n",prevNode->value,current->value);
    }
    //ROTATE
    current->next = head;
    prevNode->next = NULL;
    printf("\n%d ",prevNode->value);

}
