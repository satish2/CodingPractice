#include<stdio.h>


int pow(int,int);

void main(){
printf("\n final answer is %d\n",pow(5,12));
}

int pow(int M,int n){
static int multiplications = 0;
if(n==0)return 1;

    if(n%2==0){
        printf("multiplication = %d\n",multiplications);
      multiplications = multiplications+1;
      return (pow(M,n/2)*pow(M,n/2));
    }
    else{
        printf("multiplication = %d\n",multiplications);
        multiplications = multiplications+2;
      return (M*pow(M,n/2)*pow(M,n/2));
    }

}
