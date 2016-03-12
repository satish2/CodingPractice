//FIND MIN IN ARRYA AND THEN SWAP IT WITH 1ST POSITION AND RE-ITERATE WITH 2ND POSITION
/*
3 1 2 6 4
1 3 2 6 4
1 2 3 6 4
1 2 3 6 4
1 2 3 4 6
*/
#include<stdio.h>
void print_sq(int, int*);


void main(){
 int *A,N,i,j,temp,min;
 N=0;
 printf("enter Size of array, N\n");
 scanf("%d",&N);
 printf("enter elements of array\n");

 if(N!=0)
 A = (int *)malloc(N*sizeof(int));
 else
 return;

 for(i=0;i<N;i++){
    scanf("%d",&A[i]);
 }

//MAIN ALGO
int min_pos = 0;
for(i=0;i<N;i++){
    min = A[i];
    for(j=i+1;j<N;j++){
        if(A[j]<min) {min_pos = j;min = A[j];}
    }
    //after 1st position, swap min with 1st position
    temp = A[min_pos];
    A[min_pos] = A[i];
    A[i] = temp;
    printf("after iteration %d and min is %d\n ",i,min);
    print_sq(N,A);
    }
}

void print_sq(int N, int* A){
    int i;
    for(i = 0;i<N;i++)printf("A[%d] = %d\n",i,A[i]);
    return;
}


