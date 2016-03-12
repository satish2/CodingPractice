#include<stdio.h>
void print_sq(int , int* );
int insertionsort(int *,int,int);
int median(int *,int);
int main(){
//initialization

int *A;
int size,i,j,x;

printf("enter size of array\n");
scanf("%d",&size);
A = (int *)malloc(sizeof(int)*size);
    for(i=0;i<size;i++){
        scanf("%d",&A[i]);
    }

// main logic
//divide Array into each of 5 parts
median(A,size);

}

int insertionsort(int *A,int left,int right)
{
int i,temp,j;
    for ( i = left+1;i<right;i++)
    {
        temp = A[i];
        j = i-1;
        while ( j>=0 && temp < A[j]){
        A[j+1]=A[j];
        j = j-1;
        }
        A[j+1]=temp;
        //printf(" Iteration %d -> sequence \n", i);
        //print_sq(N,A);
    }
    //printf("after inse_srt\n");
    //print_sq(right-1,A);
    return A[left+2];
}

int median(int *A,int size){

    if(size == 1)
    {
        printf("median is %d",A[0]);
        return 0;
    }
    else if(size == 2)
    {
        printf("median is %d", A[0]);
        return 0;
    }

int med_Array;
    if(size%5==0)
    {
        med_Array= (size/5);
    }
    else
    {
        med_Array=(size/5)+1;
    }
int B[med_Array];
int k=0;
int left = 0;
int right = 4;
    while(right<size){
               //insertion sort for this array and find a[left+2]
        B[k] =insertionsort(A,left,right+1);
        k++;
        left = left+5;
        right = left+5;
    }
    if(right >= size){
    B[med_Array-1] =insertionsort(A,left,size);
    }
print_sq(med_Array,B);
median(B,med_Array);
return 1;
}

void print_sq(int N, int* B){
    int i;
for(i = 0; i<N;i++)
        printf("B[%d] =  %d \n", i ,B[i]);
    return;
}
