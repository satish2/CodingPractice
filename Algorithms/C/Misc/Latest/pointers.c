#include <stdio.h>
#include <stdlib.h>
#define $NEWLINE printf("\n");
int main(){
	int a[2] = {1,2};
	int *b = &a[0]; //Pointer to an integer, here it is address of a[0], can increment b to get a[1];
	int i = 0;
	for(;i<2;i++){
		printf("%d\t",*b);
		b++;
	}
	$NEWLINE

	int *c[2]; //Array of integer pointers
	c[0] = &a[0];
	c[1] = &a[1];
	for(i=0;i<2;i++){
		printf("%d\t",*c[i]);
	}
	$NEWLINE
	int (*d)[2]; //Pointer to an array of integers of size 2
	d = &a;
	for(i=0;i<2;i++){
//		printf("addr = %d \t",(*d)[i]); //Prints values
		printf("addr = %d \t",&(*d)[i]); //Prints addresses
	}
	d++;
	//After incrementing, it will point to next byte after above array block
	printf("after incrementing = %d",*d);
	$NEWLINE
	//c & e are same!! 
	int *e = (int *)calloc(10,sizeof(int)); //e points to a first element in block of size 10*integers.
	for(i=0;i<10;i++){
		printf("%d\t",e[i]);
	}
	$NEWLINE
	return 0;
}
