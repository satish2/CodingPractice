//anagram check
#include "sort.h"
#include <stdio.h>

int main (int argc, char *argv[]){
	
	if(argc < 3){
		printf("please enter both the string to check for anagrams as ang <string1> <string2>\n");
		return;
	}
	char *str1 = argv[1];
	char *str2 = argv[2];
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if(len1 == len2){
		mergesort(str1, 0, len1-1);
		mergesort(str2, 0, len2-1);
		if(strcmp(str1,str2) == 0) {
			printf("TRUE!!\n");
			return 0;
		}
	}
	printf("FALSE!!\n");
	return -1;
}
