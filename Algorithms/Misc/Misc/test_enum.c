#include<stdio.h>

/*void main(static int i){
    i = 0;
    enum DAY  {monday,tuesday};
    enum DAY day;
    day = monday;
    printf("%d\n",day);
}*/
#include <stdio.h>
#define MAX 5

void sumIt(void);

int main()
{
   int i =0;

   printf("Enter 5 numbers to be summed\n");

   for(i = 0; i<MAX; ++i)
         sumIt();

   printf("Program completed\n");

    getchar();
    return 0;
}

void sumIt(void)
{
    static int sum = 0;
     int num;
    printf("\ntill now sum is %d\n", sum);
     printf("\nEnter a number: ");
     scanf("%d", &num);

     sum+=num;

     printf("The current sum is: %d",sum);

}
