#include <stdio.h>

int main9 (int argc,char** argv) {
	
	int A[10] = {0},i,x;
	printf("Enter Array in which input has to be searced\n");
	for (i = 0; i< 10 ; i++){
		scanf("%d",&A[i]);
	}
	printf("\nEnter number to be searched\n");
	scanf("%d",&x);
	for(i=0;i<10;i++){
		if(x == A[i]){
			printf("Found the number at index = %d",i+1);
			break;
		}
	}
	
	return 0;
}