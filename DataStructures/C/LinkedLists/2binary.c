//print given decimal to binary
//print given decimal (with .<something>) to binary

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void print_with_padding(char *a, char sign, int msb);
int main(int argc, char*argv[]){
	
	int in = 0, iter = 0;
	char sign= '0';
	printf("give integer that should be converted to binary: ");
	scanf("%d", &in);
	//Since integer is 32-bit, we need to print 32-bit binary
	while (in != 0){
		sign = in > 0 ? '0':'1';
		in = abs(in);	
		char a[33] ={'\0'};
		int msb = (int)(log10((double)in)/(log10((double)2)))+1;
		for (iter = 31; iter>(31-msb); iter--){
			a[iter] = '0' + in%2;
			in = in/2;
		}
		print_with_padding(a,sign,msb);
		printf("%s\t",a);
		printf("length = %d \n", strlen(a));
		printf("give integer that should be converted to binary: ");
		scanf("%d", &in);
	}
}

void print_with_padding(char *a, char sign, int msb){
		
	int iter = 0;
	a[iter] = sign;
	for (iter = 31-msb; iter >0; iter--){
		a[iter] = '0';
	}
}
