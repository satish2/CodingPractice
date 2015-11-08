//Remove duplicate characters from the string
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Idea is 'i' denotes the variable with character that we are setting in ASCII array
 * 'k' denotes the position till where there are unique characters.
 * It is important to have null character at the end of given input string.
 */

void myprint(char *, int);

void myprint(char *inp, int k){
	int iter = 0;
	printf("Till k = %d \t", k);
	for(iter = 0; iter < k; iter ++){
		printf("%c",inp[iter]);
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	
	int  i=0, k=1;
	printf("Input Test String = ");
	char *inp = (char *)malloc(10*sizeof(char));
	memset(inp,'\0',10);
	scanf("%s", inp);

	int len = strlen(inp);
	if(len < 2){
		if(len != 0)
			printf("Ans = %s", inp);
		return 0;
	}
	int set[255] = {0};
	set[inp[i]] = 1;
	i++;
	while(i < len){
		if(!set[inp[i]]){
			set[inp[i]] = 1;
			k++;
		}
		i++;
		if(k!=i)
		 inp[k] = inp[i];
		//myprint(inp,k);
	}
	printf("Ans = %s \n",inp);
}

