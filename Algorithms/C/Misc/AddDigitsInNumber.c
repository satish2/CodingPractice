#include <stdio.h>

int main4() {
	int number=0,ansr=0;
	
	printf("Enter Number :");
	scanf ("%d", &number);
	while(number/10 != 0){
		ansr += number%10;	
		number = number/10;

	}
	ansr += number%10;	
	printf("%d \n",ansr);
	return 0;
}
