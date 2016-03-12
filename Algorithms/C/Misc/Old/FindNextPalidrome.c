#include <stdio.h>
#include <math.h>
int findNextPalindrome(int);
int checkPalindrome(int);

int main6 (){
	int number;
	while(1){
		printf("Enter Number  whose next palidrome has to be found: ");
		scanf("%d",&number);
		if(number == -1)
			break;
		if(checkPalindrome(number) == 1)
			printf("isPalidrome=true\n");
		else
			printf("Next Palindrome is %d\n",findNextPalindrome(number));
	}
	
	return 0;
}

int findNextPalindrome(int number){
	double x = 10.0;
	return addEleven(number);
}

int addEleven(int number){
	double x = 10.0;
	number = number + 11;
	int numOfDigits = findNumberOfDigits(number);
	int firstDigit = number/(int)ceil(pow(x,(double)(numOfDigits-1)));
	int lastDigit = number%10;
	number = number + firstDigit - lastDigit;
	
	if(checkPalindrome(number)==1){
		return number;
	} else
		return addEleven(number);
		
}

int checkPalindrome(int number){
	double x = 10;
	if(number/10 == 0)
		return 1;
	int numOfDigits = findNumberOfDigits(number);
	
	if(numOfDigits == 2){
		if(number%11== 0)
			return 1; 
	}
	
	if(number/(int)pow(x,(double)(numOfDigits-1)) != number%10)
		return 0;
	number = number - ((number%10)*(int)pow(x,(double)(numOfDigits-1)) + number%10);
	number = number/10;
	return checkPalindrome(number);
}

int findNumberOfDigits(int num){
	int count = 1,i = 10;
	while (1){
		if(num/i ==0)
				break;
		count++;
		i *= 10;
	}
	return count;
}