#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void rotate_matrix(int rows, int cols);
int a[4][4] = {0};

void print(){
	int i,j;
	for(i=0; i<4; i++){
		for(j=0;j<4;j++)
			printf("%d \t",a[i][j]);
		printf("\n");
	}
	printf("******************\n");
}

void rotate_matrix(int rows, int cols){
	
	int i=0, j=0;
	int n = rows;	
	int f = rows/2;
	int c = cols/2;
	for(i=0;i<f;i++){
		for(j=0;j<c;j++){
			int temp = a[i][j];
			a[i][j] = a[n-1-j][i];
			a[n-1-j][i] = a[n-1-i][n-1-j];
			a[n-1-i][n-1-j] = a[j][n-1-i];
			a[j][n-1-i] = temp;
			print();
		}
	}
}

int main(int argc, char *argv[]){
	
	int i = 0,j=0;
	for(i=0; i<4; i++){
		for(j=0;j<4;j++)
			scanf("%d",&a[i][j]);
	}

	printf("------AFTER-------\n");
	rotate_matrix(4,4);
/*
	for(i=0; i<4; i++){
		for(j=0;j<4;j++)
			printf("%d \t",a[i][j]);
		printf("\n");
	}
*/
}

