#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
{
char data;
struct node *next;
};
int **arr;

struct node *list[10];
void adjmatrix(int total)
{
      int i,j;
      arr=(int **)malloc(sizeof(int)*total*total);
      if(arr==NULL)
      {
     	 	printf("\nMemory Cannot be Allocated");
      	return;
      }
      
      for(i=0;i<total;i++)
      {for(j=0;j<total;j++)
      {
	      printf("\nIs there Edge between %c & %c (0/1)",i+65,j+65);			
   	   scanf("%d",&arr[i][j]);
      }}
      printf("\nAdjacency Matrix\n\n\t");
      
      for(i=0;i<total;i++)
      printf("\t%c",i+65);
      
      for(i=0;i<total;i++)
      {
      	printf("\n\n\t%c",i+65);
	      for(j=0;j<total;j++)
   		   printf("\t%d",arr[i][j]);
      }
      getch();
}

struct node* addlast(struct node *list, char data)
{
	struct node *t,*s;
	s=(struct node*)malloc(sizeof(struct node));
	s->data=data;
	s->next=NULL;
	if(list==NULL)
	list=s;
	else
	{
		for(t=list;t->next!=NULL;t=t->next);
		t->next=s;
	}
return list;
}


void adjlist(int total)
{
	int i,j;
	struct node *t;
	for(i=0;i<total;i++)
	{
		for(j=0;j<total;j++)
		{
			if(arr[i][j]==1)
			list[i]=addlast(list[i],j+65);
		}
	}
	for(i=0;i<total;i++)
	{
		for(t=list[i];t!=NULL;t=t->next)
		printf("\n%c - %c",i+65,t->data);
	}
}

int main()
{
      int tot;
      clrscr();
      printf("\nEnter Total no of Nodes:");
      scanf("%d",&tot);
      adjmatrix(tot);
      adjlist(tot);
      getch();
} 