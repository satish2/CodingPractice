#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void perm(char *str, int index);
void swap(char *, int, int);

int main (int argc, char *argv[]){
	
	int iter = 0;
	char *inp = (char *)malloc(10*sizeof(char));
	memset(inp,'\0',10);
	printf("Enter string of less than ten characters: ");
	scanf("%s",inp);
	perm(inp, 0);
	return 0;
}

void perm(char *str, int str_pos){
	
	int len = strlen(str) - str_pos;
	if(len ==2){
		printf("%s\n",str);
		swap(str, str_pos,str_pos+1);
		printf("%s\n",str);
		swap(str, str_pos,str_pos+1);
		return;
	}

	int iter = 0;
	while(1){
		perm(str,str_pos+1);
		if(str_pos != str_pos+iter)
			swap(str,str_pos,str_pos + iter);
		iter = iter+1;
		if(iter >= len)
			break;
		swap(str,str_pos,str_pos+iter);
	}
}

void swap(char *str, int indx1,int indx2){
	if(indx1 == indx2)
		return;
	char tmp = str[indx1];
	str[indx1] = str[indx2];
	str[indx2] = tmp;
}

