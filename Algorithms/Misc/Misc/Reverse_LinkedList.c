//reverse Linked List
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void println();


typedef struct node{
    int value;
    struct node *next;
}NODE;

void reverse(NODE *);
void changeLink(NODE *,NODE*);
void println(){
printf("\n");
}
NODE *head;
NODE *newHead;

void main(){
        //create linked list first and then send it for reversal
        NODE *current;
        int num,i;
        head = (NODE*)malloc(sizeof(NODE));
        head->value = rand();
        printf("enter number of nodes needed\n");
        scanf("%d",&num);
        current = head;
                for(i=1;i<num;i++){
                      NODE *n1;
                    n1 = (NODE*)malloc(sizeof(NODE));
                    current->next = n1;
                    n1->value = rand();
                    current = n1;
              }

              current->next = NULL;
        current = head;
        printf("original list is\n");
        traverse(head);
        reverse(head);
        printf("original list is \n");
        traverse(newHead);

}

int traverse(NODE *current){
        int count=0;
        while(current!=NULL){
                 printf("%d",current->value);
                 current = current->next;
        count++;
        }
        println();
        return count;
}
void reverse(NODE *current){

    if(current->next!=NULL){
        reverse(current->next);
   }
    else {
        newHead = current;
         return;
    }
         changeLink(current,current->next);
}

void changeLink(NODE *prevNode, NODE *current){
    current->next=prevNode;
    if(prevNode == head){
        prevNode->next = NULL;
    }
}
