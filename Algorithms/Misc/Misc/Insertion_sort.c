// this does insertion sort
/*
6 4 1 3 2
4 6 1 3 2
4 1 6 3 2 -> 1 4 6 3 2
1 4 3 6 2 -> 1 3 4 6 2
1 3 4 2 6 -> 1 3 2 4 6 -> 1 2 3 4 6

*/
#include<stdio.h>
void main(){

    int *A, N, i, j,temp;
    N =0;
    printf("enter N, size of array \n");
    scanf("%d",&N);
    if(N!=0)
    A = (int *)malloc(N*sizeof(int));
    else
        return;
    printf("enter Array elements \n");
    for ( i = 0; i<N ; i++)
    {
        scanf("%d",&A[i]);
    }

    for ( i = 1 ; i<N;i++)
    {
        temp = A[i];
        j = i-1;
        while ( j>=0 && temp < A[j]){
        A[j+1]=A[j];
        j = j-1;
        }
        A[j+1]=temp;
        printf(" Iteration %d -> sequence \n", i);
        print_sq(N,A);
    }

    return;
}
void print_sq(int N, int* A){
    int i;
for(i = 0; i<N;i++)
        printf("A[%d] =  %d \n", i ,A[i]);
    return;
}
