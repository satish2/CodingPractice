#include <stdio.h>

int main(void) {
	// your code goes here
	int a = 4;
	char *b = (char *)&a;
	int i = 0, j = sizeof(int)-1;
	printf("Before swapping = %x\n",a);
	for(; i<j; i++,j--){
		printf("swapping %x with %x\n",b[i],b[j]);
		char temp = b[i];
		b[i] = b[j];
		b[j] = temp;
	}
	int c = *(int*)b;
	printf("%x\n",c);
	return 0;
}
00 00 00 04
04 00 00 00

