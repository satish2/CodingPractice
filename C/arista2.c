#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// your code goes here
	int (*a)[5];
	int *b[5];
	int i = 0;
	int array[5] = {0,1,2,3,4};
	a = array;
	
	for(i=0; i<5; i++)
		b[i] = &array[i];
		
	printf("%d\n",a);
	printf("%d\n",++a);
	
	for(i=0; i<5; i++){
		printf("%d\t ", *b);
	    (*b)++;
	}
	
	return 0;
}

