#include<stdio.h>

void main (){

// taking array input
int *A;
int size,i,j,x;
int N;
printf("enter sum\n");
scanf("%d",&N);
printf("enter size of array\n");
scanf("%d",&size);
A = (int *)malloc(sizeof(int)*size);
    for(i=0;i<size;i++){
        scanf("%d",&A[i]);
    }

for(i=0;i<size;i++){
    x = N-A[i];
    for(j=i+1;j<size;j++){
            printf("what is x = %d",x);
            if(A[j] == x){
                return 1;

            }
    }
}
return 0;
}
