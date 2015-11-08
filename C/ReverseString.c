//String Reversal
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	int i,j;
	char *name = (char *)calloc(6,sizeof(char));
	printf("Give string that should be reversed \n");
	scanf("%s", name);
	int len = strlen(name);
	for(i=len-1,j=0;i>j; j++,i--){
		char tmp = name[i];
		name[i] = name[j];
		name[j] = tmp;
	}
	printf("Reverseed String = %s\n", name);
	char *test = "satish";
	printf("%c", *(test+6));
}
