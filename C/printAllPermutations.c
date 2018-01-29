//printAllPermutations
#include <stdio.h>
#include <string.h>

swap(char *str, int pos1, int pos2){
	char temp = str[pos1];
	str[pos1] = str[pos2];
	str[pos2] = temp;
}

void permutations(char *string, int st){
	
	int length = strlen(string) - st;
	if(length == 2){
		printf("%s\n",string);
		swap(string, st, st + 1);
		printf("%s\n",string);	
		swap(string, st, st  +1);
		return;
	}
	int iter = 0;
	while(1){
		permutations(string, st + 1);
		if(iter != 0) swap(string, st, st+iter);
		iter++;
		if(iter >= length)break;
		swap(string, st, st+iter);
	}
}

int main(int argc, char **argv){
	char *string = argv[1];
	permutations(string,0);
	return 0;
}
