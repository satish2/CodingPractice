//merge sort and quick sort comes uner divide and conquer algos
/*
3 functions main whcih will take array input and pass it to mergesort and then to merger function


*/
#include<stdio.h>
void mergesort(int* , int, int);

void merge(int*, int,int,int);


void main(){
 int *A,i,j,temp,N;
 printf("enter size of array,N \n");
 scanf("%d",&N);
  printf("enter elements of array\n");
  A = (int *)malloc(sizeof(int)*N);
  for(i = 0; i<N;i++){
      scanf("%d",&A[i]);
    }
  mergesort(A,0,N-1);
  print_array(A,0,N-1);
}
void mergesort(int* A,int left, int right){


    int split_pos;
    if(right>left){
     split_pos = (left+right)/2;
    mergesort(A,left,split_pos);
    mergesort(A,split_pos+1,right);
    merge(A,left,split_pos,right);
    }
    else
    return;
}

void merge(int *A, int left, int split_pos, int right){
    int k;

    int left_array = split_pos - left + 1;
    int right_array = right - split_pos;
    int array1[left_array];
    int array2[right_array];

    int i =0;
    int j = 0;
    for(i=0;i<left_array;i++){array1[i]= A[left+i];}
    for(i=0;i<right_array;i++){array2[i]= A[split_pos+i+1];}
    i=0;
    j=0;

    for(k =left; k<=right;k++){
        if(j==right_array){
        A[k]= array1[i];
        i++;
        }
        else if(i==left_array){
        A[k]= array2[j];
        j++;
        }
        else if(array1[i]>array2[j]){
        A[k] = array2[j];
        j++;
        }
        else{
        A[k] = array1[i];
        i++;
        }
    }

}

void print_array(int* A,int left,int right){
    int i = left;
    for( ;i<=right;i++){
        printf("%d\t", A[i]);
    }
    printf("\n");
}
