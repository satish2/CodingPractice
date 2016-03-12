#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef union
{
	int e1;
	char *e2;
	float e3;
}element;	
struct node
{
	element *data;
	struct node *link;
}          ;
struct node  *top;

void main()
{
void push(element,char *);
void display();
int pop();
int wish, num,will,a;
char *num1,*type;
float num2;
wish = 1;
top = NULL;
clrscr();
printf("Program for Stack as Linked List demo. .\n");
while(wish == 1)
	{
	printf("Main Menu 1.Enter data in stack 2.Delete from stack\n ");
	scanf("%d",&will);
	switch(will)
		{
		case 1:
			printf("Enter the numerical data\n");
			scanf("%d",&num);
			push(num,"integer");
			printf("Enter the string data\n");
			scanf("%s",num1);
			push(num1,"character");
			printf("Enter the floating point data\n");
			scanf("%f",&num2);
			push(num2,"floating");
			display();
			break;
		case 2:
			a=pop();
			printf("Value returned from top of the stack is %d\n",a);
			break;
		default:
			printf("Invalid choice\n");
		}
	printf("Do you want to continue, press 1\n");
	scanf("%d",&wish);
	}
}


void push(element y,char type[])
{
int q;
struct node *x;
x=malloc(sizeof(struct node));
//printf(" Address of newly created node x is %d\n",x);
q=strcmp(type,"integer");
if(q=0)
x->data->e1 = y;
else if(!(strcmp(type,"character"))
x->(data->e2) = y;
else (!(strcmp(type,"floating"))
x->data->e3 = y;

x->link = top;
top = x;

}
void display()
{
int i =0;
struct node * temp;
temp = top;

	while(temp!=NULL)
	{
	printf("Item No. %d  :  Data %d    Link %d\n ",i++,temp->data,temp->link);
	temp=temp->link;
	}
}

///	THIS FUNCTION REMOVES TOP NODE FROM  THE STACK AND RETURNS ITS VALUE///

int pop()
{
  int a;
  if(top==NULL)
  {printf("		STACK EMPTY...");
   return 0;
   }
  else
  {
  a=top->data;
  printf("The value returned is %d ",a);
  free(top);
  top=top->link;
  return (a);
  }
}
