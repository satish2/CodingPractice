//rotate bits
#include<stdio.h>
int rotate(int, int);

int rotate(int num,int n)
{
    int right1 = num>>n;
    int left1 = num<<(8*sizeof(int)-n);
    printf("%d ",right1);
    printf("%d \n",left1);
    return (right1 | left1);
}

void main(){

int a;
printf("%d\n",rotate(5,2));
printf("sizeofint = %d\n",sizeof(int));
printf("sizeofint = %d\n",sizeof(char));
printf("sizeofint = %d\n",sizeof(float));
printf("sizeofint = %d\n",sizeof(double));
printf("sizeofint = %d\n", a=5);

}
