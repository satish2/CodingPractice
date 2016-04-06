//checkPalindrome
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv){
	char *string = argv[1];
	int i = 0;
	int j = strlen(string)-1;
	while(i < j){
		if(string[i] != string[j]){
			printf("Not Palindrome\n");
			return -1;
		}
		i++;	
		j--;
	}
	if(strlen(string) == 0 || strlen(string) == 1) {
		printf("Not palindome\n");
		return -1;	
	}
	printf("Yes Palindrome\n");
	return 0;
}
