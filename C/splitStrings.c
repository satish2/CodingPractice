#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	int init_size = 10;
	char  *inp = (char *)malloc(sizeof(char)*init_size);
	int i=0;
	while(scanf("%c",&inp[i])!=EOF){
		i++;
		if(i >= init_size){
			inp = (char *)realloc(inp,init_size*2);
			init_size = init_size*2;
		}
	}
	printf("\nDone taking Input. Printing Processed Output:\n");
	int len = i;
	for(i=0;i<len;i++){
		if(inp[i] == ' ')
			inp[i] = '\n';
		putc(inp[i],stdout);
	}
	free(inp);
	return 0;

}
