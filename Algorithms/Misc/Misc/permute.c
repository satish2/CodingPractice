//permutations of 4 numbers
//what if we have many ???
//permute 5???
//done but universal ????
#include<stdio.h>
#include<stdlib.h>
int b[]={1,2,3,4,5};
 int permute2(int *a);
 int permute3(int *a);
 int permute4(int *a);
 void swap(int ,int);

 void swap(int d,int c)
 {
  int  temp;
  temp=b[c];
  b[c]=b[d];
  b[d]=temp;
 } 

int permute2(int *a)
{
 int i;
 for(i=0;i<5;i++)
 {
 printf("%d \t",b[i]);
 }
 printf("\n");
 swap(3,4);
 for(i=0;i<5;i++)
 {
 printf("%d \t",b[i]);
 }
 swap(3,4);
 printf("\n");
}
//

//		
int permute3(int *b)
{ int i;

 permute2(b);
for(i=3;i<5;i++)
 {
  swap(2,i);
   permute2(b);
  swap(2,i);
 } 
}
//
int permute4(int *b)
{
 int i;
 permute3(b);
 for(i=2;i<5;i++)
 {
  swap(1,i);
   permute3(b);
  swap(1,i);
 } 
} 
//
int main()
{
int i;
 permute4(b);
  for(i=1;i<5;i++)
 {
  swap(0,i);
   permute4(b);
  swap(0,i);
 } 
 return 0;
} 
