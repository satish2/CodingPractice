#include <stdio.h>

int main5(){
	
	int number;
	scanf("%d",&number);
	int answer = 0;
	answer = getAnswer(number);
	printf("Sum is %d",answer);
	return 0;							
}

int getAnswer (int num){
	int retVal;
	if((num/10) == 0)
		retVal = num;
	else
		retVal = num%10 + getAnswer(num/10);
	return retVal;
}