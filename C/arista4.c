#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define rows 20000
#define columns 30000
int array1[rows][columns] = {0};

void func1(){
	int i = 0;
	int j = 0;
	for(; i<rows;i++)
		for(j=0;j<columns;j++)
			array1[i][j] = 0;
}

void func2(){
	int i = 0;
	int j = 0;
	for(; i<columns;i++)
		for(j=0;j<rows;j++)
			array1[j][i] = 0;
	
}


int main(void) {
	// your code goes here
    struct timeval start, end;
	gettimeofday(&start, NULL);
	func1();
	gettimeofday(&end, NULL);
	printf("total time taken func1: = %ld\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	func2();
	gettimeofday(&end1, NULL);
	printf("total time taken func2: = %ld\n", ((end1.tv_sec * 1000000 + end1.tv_usec) - (start1.tv_sec * 1000000 + start1.tv_usec)));
	return 0;
}

