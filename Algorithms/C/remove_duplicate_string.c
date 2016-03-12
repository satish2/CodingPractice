//Remove duplicate characters from the string
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	int  i=0, j=1, k=1;
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
//	bool set[255] = false;
//	set[inp[i]] = true;
	while(i < len){
		j = i + 1;
		k = j;
		while(j <len){
			printf("i = %d, j= %d, k = %d \n", i,j,k);
			if(inp[i] != inp[j]) {
				k++;
			}
			j++;
			if(k!=j){
				inp[k] = inp[j];
			}
		}
	len = strlen(inp);
	i++;
	}
	printf("Ans = %s \n",inp);
	
}

