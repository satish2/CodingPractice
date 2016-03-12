//q==queue
#include<stdio.h>
#include<stdlib.h>
int Insert_q(int);
int del_q_elt(void);
int display();

typedef struct
{
	int elt;
	int size,length,head,tail;
}qu;

qu *q1;
const qu *q2 = q1;
int main()
{
	int size,choice,elt,i,j,elt2;
//making a new data type queue and stack
	printf("enter size of queue");
	scanf("%d",&size);
	while(1)
	{
   	printf("insert->1  delete->2  display->3  exit->4 \n");	
   	scanf("%d",&choice);
   	switch(choice)
   	{
   		case 1:printf("enter element to element \n");
   				scanf("%d",&elt);
   				q1++;
   				i=Insert_q(elt);
   				printf("i=%d \n",i);
   				break;
   		case 2:elt2=del_q_elt();
   					printf("elt2=%d \n",elt2);
   				break;
   		case 3:display();
   				break;
   		case 4:printf("exit");
   				 exit(0);
   				 break;
   	}
   }

return 0;
}		

int Insert_q(int i)
{
	int elt1; 
	q1=(qu *)malloc(1 * sizeof(qu));
	q1->elt = i;
	elt1=q1->elt;
	q1->length++;
	q1->size=sizeof(qu);
	printf("111=%d",q1->size);
	return elt1;
}
int del_q_elt()
{
	int elt2;
	q1->length--;
	elt2=q1->elt;
	free (q1);
	q1--;
	if(q1==NULL)
	printf("the tail\n");
	return elt2;
}	
int display()
{
	printf("q1->size = %d,q1->length= %d",q1->size,q1->length);
	return 0;
}	
	
