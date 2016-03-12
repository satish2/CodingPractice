#include <stdio.h>

int main7(){
	
	int A[5] = {5,2,1,3,4};
	int j,i;
	for (j=1;j<5;j++){
		int key = A[j];
		i = j-1;
		while(i>=0 && A[i]>key){
				A[i+1] = A[i];
				i--;
		}
		A[i+1] = key;
	}
	
	for (j=0;j<5;j++){
		printf("%d \t",A[j]);
	}
	
	return 0;
}