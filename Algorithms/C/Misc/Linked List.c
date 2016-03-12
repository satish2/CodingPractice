// Aim s to Create a Linked List
// involves creation of Struct that acts as a node
#include <stdio.h>

 typedef struct NODE{
    int data;
    struct NODE *next;
 }n;



void main(){

    n head;
    n tail;
    int check;
    int i;
    printf("enter any number");
    scanf("%d",&check);
    for(i=0;i<check;i++){

        if(check == 0){
            return;
        }
        else{
            head.data = i;
            n node1;
                if(i!=check-1){
                        head.next = &node1;
                        head = node1;
                }
                else break;
        }

    }
    head.next = NULL;
    tail = head;
    printf("%d", tail.data);
    return;

}
