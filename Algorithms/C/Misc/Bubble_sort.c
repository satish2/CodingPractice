//Bubble Sort
/*
3 1 2 6 4
1 3 2 6 4
1 2 3 6 4
1 2 3 6 4
1 2 3 4 6
*/
#include<stdio.h>
void swap(int*, int*);

void main(){
 int *A,N,i,j,temp;
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

   //MAIN ALGO PART
         int swapcount = 0;
         do{
            swapcount = 0;
            for (i=1;i<N;i++){

                    if(A[i]<A[i-1]){
                        temp =  A[i-1];
                        A[i-1] = A[i];
                        A[i] = temp;
                        swapcount++;
               }

            }
                    printf("iteration\n");
                    print_sq(N,A);
        }while(swapcount!=0);

return;
}

void print_sq(int N, int* A){
    int i;
for(i = 0; i<N;i++)
        printf("A[%d] =  %d \n", i ,A[i]);
    return;
}

