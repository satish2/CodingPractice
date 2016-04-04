//all permutations of word
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0

void swap(char *string, int st, int end){
	char temp = string[end];
	string[end] = string[st];
	string[st] = temp;
}

void printAllPermutations(char *string, int stIndex){
	int length = strlen(string) - stIndex;
	if(length == 2){
		printf("%s\n", string);
		swap(string, stIndex, stIndex + 1);
		printf("%s\n", string);
		swap(string, stIndex, stIndex + 1);
		return;
	}
	int i = 0;
	while(true){
		printAllPermutations(string, stIndex + 1);		
		if(i != 0)
			swap(string, stIndex, stIndex + i); //UNDO SWAP STEP
		i++;		
		if(i >= length) break;
		swap(string, stIndex, stIndex + i);
	}
	return;
}

int main(int argc, char *argv[]){
	char *string = (char *)calloc(10, sizeof(char));
	strcpy(string, "1235");
	printAllPermutations(string, 0);
}
