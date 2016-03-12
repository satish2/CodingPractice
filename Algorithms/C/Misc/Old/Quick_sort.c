//
#include<stdio.h>

void main(){
    int *A,N,i=0,j,temp,size=0;
    A = (int *)malloc(sizeof(int)*100);
    FILE *fp;
    fp=fopen("input.txt","r");
    while((A[i]=getw(fp))!=EOF)
    {
        size++;
        printf("%d", A[i]);
    }

    quicksort(A,0,size-1);
    printf("median of the API's is %d",A[size/2]);
    //print_array(A,0,N-1);

}

void print_array(int *A,int left,int right){
    int i;
    for(i=left;i<=right;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
}

void quicksort(int *A,int left, int right){
    print_array(A,left,right);
    int pivot = A[left];
    int i,j;
    if(left<right){
    i = left+1;
    j = right;
    while(i<=j){
        while(A[i]<=pivot && i <= right) i++;
        while(A[j]>pivot && j >= left) j--;
        if(i<j)swap(&A[i],&A[j]);
    }
    swap(&A[left],&A[j]);
    quicksort(A,left,j-1);
    quicksort(A,j+1,right);
    }
}
void swap(int *I, int *J){
    int temp = *J;
    *J = *I;
    *I= temp;

}
